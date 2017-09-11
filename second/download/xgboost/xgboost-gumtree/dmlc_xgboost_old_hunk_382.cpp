    if (!need_data_rank) rabit::Init(argc, argv);
    if (rabit::IsDistributed()) {
      std::string pname = rabit::GetProcessorName();
      printf("start %s:%d\n", pname.c_str(), rabit::GetRank());
    }
    if (rabit::IsDistributed()) {
      this->SetParam("data_split", "col");
