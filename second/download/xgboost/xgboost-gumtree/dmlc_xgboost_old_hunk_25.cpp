      }
    }
  }
  virtual void Predict(const SparseBatch::Inst &inst,
                       std::vector<float> *out_preds,
                       unsigned ntree_limit,
                       unsigned root_index) {
    const int ngroup = model.param.num_output_group;
    for (int gid = 0; gid < ngroup; ++gid) {
      this->Pred(inst, BeginPtr(*out_preds));
    }
  }
  virtual void PredictLeaf(IFMatrix *p_fmat,
                           const BoosterInfo &info,
                           std::vector<float> *out_preds,
                           unsigned ntree_limit = 0) {
    utils::Error("gblinear does not support predict leaf index");
  }
  virtual std::vector<std::string> DumpModel(const utils::FeatMap& fmap, int option) {
    std::stringstream fo("");
    fo << "bias:\n";
    for (int i = 0; i < model.param.num_output_group; ++i) {
