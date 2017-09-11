void Predict(DMatrix* p_fmat,
               int64_t buffer_offset,
               std::vector<float>* out_preds,
               unsigned ntree_limit) override {
    const MetaInfo& info = p_fmat->info();
    int nthread;
    #pragma omp parallel
    {
      nthread = omp_get_num_threads();
    }
    InitThreadTemp(nthread);
    std::vector<float> &preds = *out_preds;
    const size_t stride = p_fmat->info().num_row * mparam.num_output_group;
    preds.resize(stride * (mparam.size_leaf_vector+1));
    // start collecting the prediction
    dmlc::DataIter<RowBatch>* iter = p_fmat->RowIterator();

    iter->BeforeFirst();
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
      // parallel over local batch
      const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
      #pragma omp parallel for schedule(static)
      for (bst_omp_uint i = 0; i < nsize; ++i) {
        const int tid = omp_get_thread_num();
        RegTree::FVec &feats = thread_temp[tid];
        int64_t ridx = static_cast<int64_t>(batch.base_rowid + i);
        CHECK_LT(static_cast<size_t>(ridx), info.num_row);
        // loop over output groups
        for (int gid = 0; gid < mparam.num_output_group; ++gid) {
          this->Pred(batch[i],
                     buffer_offset < 0 ? -1 : buffer_offset + ridx,
                     gid, info.GetRoot(ridx), &feats,
                     &preds[ridx * mparam.num_output_group + gid], stride,
                     ntree_limit);
        }
      }
    }
  }