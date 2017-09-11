  }
  inline void InitLearner(void) {
    if (model_in != "NULL") {
      learner.LoadModel(model_in.c_str());
    } else {
      utils::Assert(task == "train", "model_in not specified");
      learner.InitModel();
