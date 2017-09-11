    }
  }

  void Predict(DMatrix *p_fmat,
               int64_t buffer_offset,
               std::vector<float> *out_preds,
               unsigned ntree_limit) override {
    CHECK_EQ(ntree_limit, 0)
        << "GBLinear::Predict ntrees is only valid for gbtree predictor";
    std::vector<float> &preds = *out_preds;
    preds.resize(0);
    // start collecting the prediction
    dmlc::DataIter<RowBatch> *iter = p_fmat->RowIterator();
    const int ngroup = model.param.num_output_group;
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
      CHECK_EQ(batch.base_rowid * ngroup, preds.size());
      // output convention: nrow * k, where nrow is number of rows
      // k is number of group
      preds.resize(preds.size() + batch.size * ngroup);
