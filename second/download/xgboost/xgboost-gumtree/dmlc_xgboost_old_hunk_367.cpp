        this->SetParam(name, val);
      }
    }
    this->InitData();
    this->InitLearner();
    if (task == "dump") {
      this->TaskDump(); return 0;
    }
