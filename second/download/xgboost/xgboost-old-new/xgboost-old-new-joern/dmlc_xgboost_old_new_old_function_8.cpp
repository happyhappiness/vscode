virtual void PredictLeaf(IFMatrix *p_fmat,
                           const BoosterInfo &info,
                           std::vector<float> *out_preds,
                           unsigned ntree_limit = 0) {
    utils::Error("gblinear does not support predict leaf index");
  }