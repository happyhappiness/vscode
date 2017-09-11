      learner.SetCacheData(dcache);
      
      // add training set to evaluation set if needed
      if (eval_train != 0) {
        devalall.push_back(data);
        eval_data_names.push_back(std::string("train"));
      }
    }
  }
  inline void InitLearner(void) {
    if (model_in != "NULL") {
      learner.LoadModel(model_in.c_str());
    } else {
      utils::Assert(task == "train", "model_in not specified");
      learner.InitModel();
    }
  }
  inline void TaskTrain(void) {
    int version = rabit::LoadCheckPoint(&learner);
    if (version == 0) this->InitLearner();
    const time_t start = time(NULL);
    unsigned long elapsed = 0;
    learner.CheckInit(data);

    bool allow_lazy = learner.AllowLazyCheckPoint();
    for (int i = version / 2; i < num_round; ++i) {
      elapsed = (unsigned long)(time(NULL) - start);
      if (version % 2 == 0) { 
        if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
        learner.UpdateOneIter(i, *data);
        if (allow_lazy) {
          rabit::LazyCheckPoint(&learner);
        } else {
          rabit::CheckPoint(&learner);
        }
        version += 1;
      }
      utils::Assert(version == rabit::VersionNumber(), "consistent check");
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      if (rabit::IsDistributed()){
        if (rabit::GetRank() == 0) {
          rabit::TrackerPrintf("%s\n", res.c_str());
        }
      } else {
        if (silent < 2) {
          fprintf(stderr, "%s\n", res.c_str());
        }
      }
      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      if (allow_lazy) {
        rabit::LazyCheckPoint(&learner);
      } else {
        rabit::CheckPoint(&learner);
      }
      version += 1;
      utils::Assert(version == rabit::VersionNumber(), "consistent check");
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
