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
