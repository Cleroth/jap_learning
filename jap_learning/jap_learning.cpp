class App : public BaseApp {
	using BaseApp::BaseApp;

	struct KanjiKotoba {
		String kanji, hiragana, meaning;
	};

	void OnStart()
	{
		Con::Line();
		SetupExercises();
		SelectProfile();
	}

	void SetupExercises() {
		_kanji_lessons[u8"Ｃ－１～３"] = Vector<KanjiKotoba>{
			{u8"安心", u8"あんしん", "relief"},
			{u8"安全", u8"あんぜん", "safety"},
			{u8"安物", u8"やすもの", "cheap/poor article"},
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

	json * _profile_cfg = nullptr;
	String _profile;

	OrderedMap<String, Vector<KanjiKotoba>> _kanji_lessons;
};


int main()
{
	BaseApp::sUtf8 = true;
	App app{"Japanese Learning"};
	app.Run();
}
