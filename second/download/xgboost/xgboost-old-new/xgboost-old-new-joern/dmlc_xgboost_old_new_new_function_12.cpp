void InitModel() override {
    CHECK(mparam.num_trees == 0 && trees.size() == 0)
        << "Model has already been initialized.";
    pred_buffer.clear();
    pred_counter.clear();
    pred_buffer.resize(mparam.PredBufferSize(), 0.0f);
    pred_counter.resize(mparam.PredBufferSize(), 0);
  }