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
      // parallel over local batch
      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
      #pragma omp parallel for schedule(static)
      for (bst_omp_uint i = 0; i < nsize; ++i) {
        const size_t ridx = batch.base_rowid + i;
        // loop over output groups
        for (int gid = 0; gid < ngroup; ++gid) {
          this->Pred(batch[i], &preds[ridx * ngroup]);
        }
      }
    }
  }