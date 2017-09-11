    }
  }

  virtual void Predict(IFMatrix *p_fmat,
                       int64_t buffer_offset,
                       const BoosterInfo &info,
                       std::vector<float> *out_preds,
                       unsigned ntree_limit = 0) {
    utils::Check(ntree_limit == 0,
                 "GBLinear::Predict ntrees is only valid for gbtree predictor");
    std::vector<float> &preds = *out_preds;
    preds.resize(0);
    // start collecting the prediction
    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
    const int ngroup = model.param.num_output_group;
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
      utils::Assert(batch.base_rowid * ngroup == preds.size(),
                    "base_rowid is not set correctly");
      // output convention: nrow * k, where nrow is number of rows
      // k is number of group
      preds.resize(preds.size() + batch.size * ngroup);
