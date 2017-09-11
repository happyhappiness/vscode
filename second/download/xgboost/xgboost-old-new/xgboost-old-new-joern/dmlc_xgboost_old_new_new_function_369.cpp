inline void TaskTrain(void) {
    const time_t start = time(NULL);
    unsigned long elapsed = 0;
    learner.CheckInit(data);
    for (int i = 0; i < num_round; ++i) {
      elapsed = (unsigned long)(time(NULL) - start);
      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
      learner.UpdateOneIter(i, *data); 
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      if (silent < 1) {
        fprintf(stderr, "%s\n", res.c_str());
      }
      if (save_period != 0 && (i + 1) % save_period == 0) {
        this->SaveModel(i);
      }
      elapsed = (unsigned long)(time(NULL) - start);
    }
    // always save final round
    if ((save_period == 0 || num_round % save_period != 0) && model_out != "NONE") {
      if (model_out == "NULL"){
        this->SaveModel(num_round - 1);
      } else {
        this->SaveModel(model_out.c_str());
      }
    }
    if (!silent){
      printf("\nupdating end, %lu sec in all\n", elapsed);
    }
  }