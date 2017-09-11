      }
    }
  }
  void Predict(const SparseBatch::Inst &inst,
               std::vector<float> *out_preds,
               unsigned ntree_limit,
               unsigned root_index) override {
    const int ngroup = model.param.num_output_group;
    for (int gid = 0; gid < ngroup; ++gid) {
      this->Pred(inst, dmlc::BeginPtr(*out_preds));
    }
  }
  void PredictLeaf(DMatrix *p_fmat,
                   std::vector<float> *out_preds,
                   unsigned ntree_limit) override {
    LOG(FATAL) << "gblinear does not support predict leaf index";
  }

  std::vector<std::string> Dump2Text(const FeatureMap& fmap, int option) override {
    std::stringstream fo("");
    fo << "bias:\n";
    for (int i = 0; i < model.param.num_output_group; ++i) {
