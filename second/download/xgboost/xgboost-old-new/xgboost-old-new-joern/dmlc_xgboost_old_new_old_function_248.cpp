inline int Run(int argc, char *argv[]) {
    if (argc < 2) {
      printf("Usage: <config>\n");
      return 0;
    }
    utils::ConfigIterator itr(argv[1]);
    while (itr.Next()) {
      this->SetParam(itr.name(), itr.val());
    }
    for (int i = 2; i < argc; ++i) {
      char name[256], val[256];
      if (sscanf(argv[i], "%[^=]=%s", name, val) == 2) {
        this->SetParam(name, val);
      }
    }
    this->InitData();
    this->InitLearner();
    if (task == "dump") {
      this->TaskDump(); return 0;
    }
    if (task == "eval") {
      this->TaskEval(); return 0;
    }
    if (task == "pred") {
      this->TaskPred();
    } else {
      this->TaskTrain();
    }
    return 0;
  }