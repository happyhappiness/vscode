  inline void TaskTrain(void) {
    int version = rabit::LoadCheckPoint(&learner);
    if (version == 0) this->InitLearner();

    const time_t start = time(NULL);
    unsigned long elapsed = 0;
    learner.CheckInit(data);
    for (int i = version; i < num_round; ++i) {
      elapsed = (unsigned long)(time(NULL) - start);
      if (!silent) printf("boosting round %d, %lu sec elapsed\n", i, elapsed);
      learner.UpdateOneIter(i, *data); 
      std::string res = learner.EvalOneIter(i, devalall, eval_data_names);
      if (rabit::IsDistributed()){
        if (rabit::GetRank() == 0) {
