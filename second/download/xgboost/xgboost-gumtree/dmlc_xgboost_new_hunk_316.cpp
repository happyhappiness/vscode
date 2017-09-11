      this->SetParam("silent", "1");
      save_period = 0;
    }
    // initialized the result
    rabit::Init(argc, argv);
    if (rabit::IsDistributed()) {
      std::string pname = rabit::GetProcessorName();
      fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
    }
    if (rabit::IsDistributed() && data_split == "NONE") {
      this->SetParam("dsplit", "row");
    }    
    if (rabit::GetRank() != 0) {
      this->SetParam("silent", "2");
    }    
    this->InitData();

    if (task == "train") {
      // if task is training, will try recover from checkpoint
      this->TaskTrain();
