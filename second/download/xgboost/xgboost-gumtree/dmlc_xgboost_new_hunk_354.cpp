        this->SetParam(name, val);
      }
    }
    // do not save anything when save to stdout
    if (model_out == "stdout" || name_pred == "stdout") {
      this->SetParam("silent", "1");
      save_period = 0;
    }
    // whether need data rank
    bool need_data_rank = strchr(train_path.c_str(), '%') != NULL;
    // if need data rank in loading, initialize rabit engine before load data
    // otherwise, initialize rabit engine after loading data
    // lazy initialization of rabit engine can be helpful in speculative execution
    if (need_data_rank) rabit::Init(argc, argv);
    this->InitData();
    if (!need_data_rank) rabit::Init(argc, argv);
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
    if (task == "train") {
      // if task is training, will try recover from checkpoint
      this->TaskTrain();
      return 0;
    } else {
      this->InitLearner();
    }
    if (task == "dump") {
      this->TaskDump(); return 0;
    }
