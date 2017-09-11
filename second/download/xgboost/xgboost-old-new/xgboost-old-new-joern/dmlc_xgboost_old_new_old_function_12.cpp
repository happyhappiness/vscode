virtual void InitModel(void) {
    pred_buffer.clear(); pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
    utils::Assert(mparam.num_trees == 0, "GBTree: model already initialized");
    utils::Assert(trees.size() == 0, "GBTree: model already initialized");
  }