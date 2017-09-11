  inline void TaskTrain(void) {
    const time_t start = time(NULL);
    unsigned long elapsed = 0;
    for (int i = 0; i < num_round; ++i) {
      elapsed = (unsigned long)(time(NULL) - start);
      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
      learner.UpdateOneIter(i,data); 
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      fprintf(stderr, "%s\n", res.c_str());
      if (save_period != 0 && (i + 1) % save_period == 0) {
