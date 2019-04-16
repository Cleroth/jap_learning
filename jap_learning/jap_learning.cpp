
class App : public BaseApp {
	using BaseApp::BaseApp;

	struct KanjiKotoba {
		String kanji, hiragana, meaning;
	};
	using KanjiLesson = Vector<KanjiKotoba>;

	enum class LessonType { InputReading, SelectMeaning, };

	void OnStart()
	{
		Con::Line();
		SetupExercises();
		SelectProfile();
	}

	void SetupExercises()
	{
		_kanji_lessons[u8"Ｃ－１～３"] = Vector<KanjiKotoba>{
			{u8"安心", u8"あんしん" , "relief"                   },
			{u8"安全", u8"あんぜん" , "safety"                   },
			{u8"安物", u8"やすもの" , "cheap/poor article"       },
			{u8"一家", u8"いっか"  , "one family"               },
			{u8"一晩", u8"ひとばん" , "One night"                },
			{u8"飲食", u8"いんしょく", "Eating and drinking"      },
			{u8"右折", u8"うせつ"  , "Turn right/right turn"    },
			{u8"左右", u8"さゆう"  , "Left and right"           },
			{u8"右手", u8"みぎて"  , "Right hand"               },
			{u8"左手", u8"ひだりて" , "Left hand"                },
			{u8"雨季", u8"うき"   , "Rainy season"             },
			{u8"大雨", u8"おおあめ" , "Heavy rain"               },
			{u8"円周", u8"えんしゅう", "Circumference"            },
			{u8"円高", u8"えんだか" , "Strenghtening of t he yen"},
			{u8"火事", u8"かじ"   , "Fire (accident)"     },
			{u8"消火", u8"しょうか",	"Extinguish fire"   },
			{u8"花火", u8"はなび",		"Fireworks"         },
			{u8"以下", u8"いか"	,		"... and below"     },
			{u8"以上", u8"いじょう",	"... and above"     },

		};
	}

	int Choice(String query, const Vector<String> & list)
	{
		Con::Line(Con::Color::Yellow, query);
		Con::SetColor(Con::Color::Dark_Green);
		for(auto i : Iterate(list))
		{
			Con::Line("{:>4}: {}", int(i + 1), list[i]);
		}

		int i = -1;
		std::cin >> i;
		return i;
	}

	void OnTick() override
	{
		Con::Line(Con::Color::Yellow, u8"ようこそ、{}！ Choose what to do:", _profile);
		Con::SetColor(Con::Color::Dark_Green);
		Con::Line(u8"  0: Select profile");
		Con::Line(u8"  1: 漢字レッスン　（かんじ）");
		//Con::Line(u8"  2: 言葉　（ことば）");
		Con::Line(u8"  q: Quit");

		int i;
		std::cin >> i;
		if(!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			Close();
			return;
		}

		switch(i)
		{
		case 0:	SelectProfile(); break;
		case 1:	SelectKanjiLesson(); break;
		}
		Con::Line();
	}

	void SelectKanjiLesson()
	{
		Vector<String> lessons;
		for(const auto & l : _kanji_lessons)
			lessons += l.first;

		int idx = Choice("Select lesson", lessons);
		idx--;

		if(idx >= (int)lessons.Size())
			return;

		DoKanjiLesson(_kanji_lessons.At(lessons[idx]));
	}

	void DoKanjiLesson(const KanjiLesson & lesson)
	{
		struct Answer {
			uint idx;
			uint correct = 0, incorrect = 0;
			auto GetTotal() const { return correct + incorrect; }
			double Percent() const
			{
				auto total = GetTotal();
				if(total == 0)
					return 0;
				return (double)correct / total;
			}
			bool operator<(const Answer & rhs) const
			{
				return Percent() * GetTotal() < rhs.Percent() * rhs.GetTotal();
			}
		};
		Vector<Answer> answers;

		try
		{
			for(auto i : Iterate(lesson))
				answers += Answer{i};

			uint last = -1;

			while(1)
			{
				std::shuffle(answers.begin(), answers.end(), Random::BitsRng{});
				answers.Sort();

				auto & a = answers[answers[0].idx != last ? 0 : 1];
				const auto & kotoba = lesson[a.idx];

				Con::Line(Con::Color::Dark_White, u8"Reading of {}", kotoba.kanji);

				String in;
				do
				{
					in = GetInput();
				} while(in.empty());

				if(in == kotoba.hiragana)
				{
					a.correct++;
					Con::Line(Con::Color::Green, "Correct. {} - {}", kotoba.kanji, kotoba.meaning);
				}
				else
				{
					a.incorrect++;
					Con::Line(Con::Color::Red, "Incorrect. Reading was: {}", kotoba.hiragana);
				}

				last = a.idx;
				Con::Line();
			}
		}
		catch(...) {}

		Con::Line(Con::Color::Yellow, "Answers:");
		for(const auto & a : answers)
		{
			Con::Line("  {:>3}/{:>3} ({:>3}%) - {}",
						 a.correct, a.GetTotal(), int(a.Percent() * 100 + 0.5),
						 lesson[a.idx].kanji);
		}
	}

	void SelectProfile()
	{
		auto & profile_list = (*_config)["profiles"];
		if(profile_list.empty())
		{
			SetProfile();
		}
		else
		{
			Vector<String> profiles;

			for(auto p : json::iterator_wrapper(profile_list))
				profiles += p.key();

			uint idx;
			do
			{
				idx = Choice("Select profile", profiles);
				Con::Line(Con::Color::Green, "{:>4}: New Profile", profiles.Size() + 1);
				if(idx == -1)
					return;
				idx--;

				if(idx == profiles.Size())
					SetProfile();
			} while(idx >= profiles.Size() && _profile.empty());

			if(_profile.empty())
				SetProfile(profiles[idx]);
		}
		Con::Line();
	}
	void SetProfile(String profile = {})
	{
		if(profile.empty())
		{
			Con::Write("Enter new profile name: ");
			std::cin >> profile;

			if(profile.empty())
				return;
		}

		_profile = profile;
		_profile_cfg = &(*_config)["profiles"][_profile];
		if(_profile_cfg->is_null())
			*_profile_cfg = json::object();
	}

	String GetInput()
	{
		constexpr size_t MAX_INPUT_LENGTH = 255;

		wchar_t wstr[MAX_INPUT_LENGTH];
		char mb_str[MAX_INPUT_LENGTH * 3 + 1];

		unsigned long read;
		void *con = GetStdHandle(STD_INPUT_HANDLE);

		ReadConsole(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

		int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
		if(size == 0)
			throw Exception("");
		mb_str[size] = 0;

		String str = mb_str;
		auto it = std::remove_if(str.begin(), str.end(), [](char c) {
			return c == '\n' || c == '\r'; });
		str.erase(it, str.end());

		if(str == u8"ｓ" || str == u8"ｑ")
			throw Exception("");
		return str;
	}

	json * _profile_cfg = nullptr;
	String _profile;

	OrderedMap<String, KanjiLesson> _kanji_lessons;
};
/*

int main()
{

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	wchar_t wstr[MAX_INPUT_LENGTH];
	char mb_str[MAX_INPUT_LENGTH * 3 + 1];

	unsigned long read;
	void *con = GetStdHandle(STD_INPUT_HANDLE);

	ReadConsole(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size] = 0;

	//std::cout << mb_str;
	//std::cout << format(u8"漢字 #{}", 3);
	//std::printf("ENTERED: %s\n", mb_str);

	return 0;
}*/

int main()
{
	BaseApp::sUtf8 = true;
	App app{"Japanese Learning"};
	app.Run();
}