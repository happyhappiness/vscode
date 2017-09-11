      learner.SetCacheData(dcache);
      
      // add training set to evaluation set if needed
      if( eval_train != 0 ) {
        devalall.push_back(data);
        eval_data_names.push_back(std::string("train"));
      }
    }
  }
  inline void InitLearner(void) {
    if (model_in != "NULL"){
      utils::FileStream fi(utils::FopenCheck(model_in.c_str(), "rb"));
      learner.LoadModel(fi);
      fi.Close();
    } else {
      utils::Assert(task == "train", "model_in not specified");
      learner.InitModel();
    }
  }
  inline void TaskTrain(void) {
    const time_t start = time(NULL);
    unsigned long elapsed = 0;
    learner.CheckInit(data);
    for (int i = 0; i < num_round; ++i) {
      elapsed = (unsigned long)(time(NULL) - start);
      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
      learner.UpdateOneIter(i, *data); 
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      fprintf(stderr, "%s\n", res.c_str());
      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
