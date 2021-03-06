﻿
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
			{u8"安心", u8"あんしん" , "relief"},
			{u8"安全", u8"あんぜん" , "safety"},
			{u8"安物", u8"やすもの" , "cheap/poor article"},
			{u8"一家", u8"いっか"  , "one family"},
			{u8"一晩", u8"ひとばん" , "One night"},
			{u8"飲食", u8"いんしょく", "Eating and drinking"},
			{u8"右折", u8"うせつ"  , "Turn right/right turn"},
			{u8"左折", u8"させつ"  , "Turn left/left turn"},
			{u8"左右", u8"さゆう"  , "Left and right"},
			{u8"右手", u8"みぎて"  , "Right hand"},
			{u8"左手", u8"ひだりて" , "Left hand"},
			{u8"雨季", u8"うき"   , "Rainy season"},
			{u8"大雨", u8"おおあめ" , "Heavy rain"},
			{u8"円周", u8"えんしゅう", "Circumference"},
			{u8"円高", u8"えんだか" , "Strenghtening of the yen"},
			{u8"火事", u8"かじ"   , "Fire (accident)"},
			{u8"消火", u8"しょうか",	"Extinguish fire"},
			{u8"花火", u8"はなび",		"Fireworks"},
			{u8"以下", u8"いか"	,		"... and below"},
			{u8"以上", u8"いじょう",	"... and above"},
		};

		_kanji_lessons[u8"Ｃ－９～１２"] = Vector<KanjiKotoba>{
			{u8"高価", u8"こうか" , u8"high price (な形容詞)"},
			{u8"高波", u8"たかなみ" , "high wave"},
			{u8"国産", u8"こくさん" , u8"国でできた物"},
			{u8"国民", u8"こくみん" , "nationality"},
			{u8"北国", u8"きたぐに" , "northern provinces"},
			{u8"今回", u8"こんかい" , "this time"},
			{u8"今頃", u8"いまごろ" , "around this time"},
			{u8"左折", u8"させつ" , "left turn"},
			{u8"左利き", u8"ひだりきき" , "left-handedness"},
			{u8"三角", u8"さんかく" , "triangle/triangular"},
			{u8"三日月", u8"みかづき" , "crescent moon"},
			{u8"火山", u8"かざん" , "volcano"},
			{u8"山盛り", u8"やまもり" , "mountain-sized serving"},
			{u8"四季", u8"しき" , "four seasons"},
			{u8"四つ角", u8"よつかど" , "crossing"},
			{u8"遺伝子", u8"いでんし" , "gene"},
			{u8"扇子", u8"せんす" , "folding fan"},
			{u8"子供", u8"こども" , "child"},
			{u8"耳鼻科", u8"じびか" , ""},
			{u8"初耳", u8"はつみみ" , ""},
			{u8"時期", u8"じき" , ""},
			{u8"時々", u8"ときどき" , ""},
			{u8"時計", u8"とけい" , ""},
			{u8"七五三", u8"しちごさん" , ""},
			{u8"車庫", u8"しゃこ" , ""},
			{u8"車輪", u8"しゃりん" , ""},
			{u8"社会", u8"しゃかい" , ""},
			{u8"神社", u8"じんじゃ" , ""},
			{u8"歌手", u8"かしゅ" , ""},
			{u8"手紙", u8"てがみ" , ""},
			{u8"週休二日制", u8"しゅうきゅうふつかせい" , ""},
			{u8"週末", u8"しゅうまつ" , ""},
			{u8"十分", u8"じゅうぶん" , ""},
		};

		_kanji_lessons[u8"Ｄ－49～50"] = Vector<KanjiKotoba>{
			{u8"所", u8"ところ" , "place"},
			{u8"住所", u8"じゅうしょ" , "address"},
			{u8"近所", u8"きんじょ" , "neighbourhood"},
			{u8"台所", u8"だいどころ" , "kitchen"},
			{u8"暑い", u8"あつい" , ""},
			{u8"残暑", u8"ざんしょ" , "lingering summer heat"},
			{u8"猛暑", u8"もうしょ" , "fierce heat"},
			{u8"会場", u8"かいじょう" , ""},
			{u8"場合", u8"ばあい" , ""},
			{u8"場所", u8"ばしょ" , ""},
			{u8"乗る", u8"のる" , ""},
			{u8"乗客", u8"じょうきゃく" , ""},
			{u8"乗用車", u8"じょうようしゃ" , ""},
			{u8"色", u8"いろ" , ""},
			{u8"特色", u8"とくしょく" , ""},
			{u8"景色", u8"けしき" , ""},
			{u8"顔色", u8"かおいろ" , ""},
			{u8"森林", u8"しんりん" , ""},
			{u8"森", u8"もり" , ""},
			{u8"心", u8"こころ" , ""},
			{u8"心臓", u8"しんぞう" , ""},
			{u8"心配", u8"しんぱい" , ""},
			{u8"親", u8"おや" , ""},
			{u8"親友", u8"しんゆう" , "close friend"},
			{u8"親子", u8"おやこ" , ""},
		};

		_kanji_lessons[u8"Ｄ－５１～５２"] = Vector<KanjiKotoba>{
			{u8"", u8"" , ""},
			{u8"", u8"" , ""},
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
		constexpr uint kGoalTotal = 3;
		constexpr double kGoalPct = 0.85; // ~= 6/7

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
			double GetScore() const 
			{
				auto total = GetTotal();
				if(total == 0)
					return 0;

				auto score = ((double)correct - incorrect);
				score *= abs((double)correct / total - 0.5) * 2;
				return score;
			}
			bool operator<(const Answer & rhs) const
			{
				return GetScore() < rhs.GetScore();
			}
		};

		Vector<Answer> answers;
		struct ScoreCount {
			ScoreCount() {}
			ScoreCount(bool inf) : total(std::numeric_limits<double>::max()),
				pct(total), score(total) {}
			double total = 0, pct = 0, score = 0;
		};

		auto getMin = [&]{
			ScoreCount ret(true);

			for(const auto & a : answers)
			{
				if(a.GetTotal() < ret.total)
					ret.total = a.GetTotal();
				if(a.Percent() < ret.pct)
					ret.pct = a.Percent();
				if(a.GetScore() < ret.score)
					ret.score = a.GetScore();
			}
			return ret;
		};

		auto getAvg = [&] {
			ScoreCount ret;

			for(const auto & a : answers)
			{
				ret.total += a.GetTotal();
				ret.pct += a.Percent();
				ret.score += a.GetScore();
			}

			ret.total /= (double)answers.Size();
			ret.pct /= (double)answers.Size();
			ret.score /= (double)answers.Size();
			return ret;
		};

		auto printScores = [&] {
			auto min = getMin();
			auto avg = getAvg();
			system("cls");
			Con::Line(Con::Color::Yellow, format("Min: {}% | {} | {}    Avg: {}% | {} | {}     Goal (Min): {}% | {} | {}",
															 min.pct * 100, min.total, min.score,
															 avg.pct * 100, avg.total, avg.score,
															 kGoalPct   * 100, kGoalTotal, 0
			));
			Con::Line();
		};


		try
		{
			for(auto i : Iterate(lesson))
				answers += Answer{i};

			uint last = -1;
			printScores();

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
					printScores();
					Con::Line(Con::Color::Green, "Correct. {} - {}", kotoba.kanji, kotoba.meaning);

					auto min = getMin();
					if(min.total >= kGoalTotal && min.pct >= kGoalPct)
					{
						Con::Line(Con::Color::Green, "Goal accomplished!");
						throw Exception("");
					}
				}
				else
				{
					a.incorrect++;
					printScores();
					Con::Line(Con::Color::Red, "Incorrect. Reading was: {} - {}", kotoba.hiragana, kotoba.meaning);
				}

				last = a.idx;
				Con::Line();
			}
		}
		catch(...) {}

		Con::Line(Con::Color::Yellow, "Answers:");
		for(const auto & a : answers)
		{
			Con::SetColor(Con::Color::Dark_Green);
			Con::Line("  {:>2}/{:>2} ({:>3}%,{:>4.1}):  {}",
						 a.correct, a.GetTotal(), int(a.Percent() * 100 + 0.5), a.GetScore(),
						 lesson[a.idx].kanji);
		}
		system("pause");
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