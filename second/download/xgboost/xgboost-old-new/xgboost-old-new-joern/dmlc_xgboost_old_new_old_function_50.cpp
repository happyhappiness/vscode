virtual void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
                                  IFMatrix *p_fmat,
                                  const BoosterInfo &info,
                                  const std::vector<bst_uint> &fset,
                                  const RegTree &tree) {
    // fill in reverse map
    feat2workindex.resize(tree.param.num_feature);
    std::fill(feat2workindex.begin(), feat2workindex.end(), -1);
    freal_set.clear();
    for (size_t i = 0; i < fset.size(); ++i) {
      if (feat_helper.Type(fset[i]) == 2) {
        feat2workindex[fset[i]] = static_cast<int>(freal_set.size());
        freal_set.push_back(fset[i]);
      } else {
        feat2workindex[fset[i]] = -2;
      }
    }
    this->GetNodeStats(gpair, *p_fmat, tree, info,
                       &thread_stats, &node_stats);
    sketchs.resize(this->qexpand.size() * freal_set.size());
    for (size_t i = 0; i < sketchs.size(); ++i) {
      sketchs[i].Init(info.num_row, this->param.sketch_eps);
    }
    // intitialize the summary array
    summary_array.resize(sketchs.size());
    // setup maximum size
    unsigned max_size = this->param.max_sketch_size();
    for (size_t i = 0; i < sketchs.size(); ++i) {
      summary_array[i].Reserve(max_size);
    }
    // if it is C++11, use lazy evaluation for Allreduce
#if __cplusplus >= 201103L
    auto lazy_get_summary = [&]()
#endif
        {
      // get smmary
      thread_sketch.resize(this->get_nthread());
      // number of rows in
      const size_t nrows = p_fmat->buffered_rowset().size();
      // start accumulating statistics
      utils::IIterator<ColBatch> *iter = p_fmat->ColIterator(freal_set);
      iter->BeforeFirst();
      while (iter->Next()) {
        const ColBatch &batch = iter->Value();
        // start enumeration
        const bst_omp_uint nsize = static_cast<bst_omp_uint>(batch.size);
        #pragma omp parallel for schedule(dynamic, 1)
        for (bst_omp_uint i = 0; i < nsize; ++i) {
          int offset = feat2workindex[batch.col_index[i]];
          if (offset >= 0) {
            this->UpdateSketchCol(gpair, batch[i], tree,
                                  node_stats,
                                  freal_set, offset,
                                  batch[i].length == nrows,
                                  &thread_sketch[omp_get_thread_num()]);
          }
        }
      }
      for (size_t i = 0; i < sketchs.size(); ++i) {
        utils::WXQuantileSketch<bst_float, bst_float>::SummaryContainer out;
        sketchs[i].GetSummary(&out);
        summary_array[i].SetPrune(out, max_size);
      }
      utils::Assert(summary_array.size() == sketchs.size(), "shape mismatch");
    };
    if (summary_array.size() != 0) {
      size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
#if __cplusplus >= 201103L
      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size(), lazy_get_summary);
#else
      sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
#endif
    }
    // now we get the final result of sketch, setup the cut
    this->wspace.cut.clear();
    this->wspace.rptr.clear();
    this->wspace.rptr.push_back(0);
    for (size_t wid = 0; wid < this->qexpand.size(); ++wid) {
      for (size_t i = 0; i < fset.size(); ++i) {
        int offset = feat2workindex[fset[i]];
        if (offset >= 0) {
          const WXQSketch::Summary &a = summary_array[wid * freal_set.size() + offset];
          for (size_t i = 1; i < a.size; ++i) {
            bst_float cpt = a.data[i].value - rt_eps;
            if (i == 1 || cpt > this->wspace.cut.back()) {
              this->wspace.cut.push_back(cpt);
            }
          }
          // push a value that is greater than anything
          if (a.size != 0) {
            bst_float cpt = a.data[a.size - 1].value;
            // this must be bigger than last value in a scale
            bst_float last = cpt + fabs(cpt) + rt_eps;
            this->wspace.cut.push_back(last);
          }
          this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
        } else {
          utils::Assert(offset == -2, "BUG in mark");
          bst_float cpt = feat_helper.MaxValue(fset[i]);
          this->wspace.cut.push_back(cpt + fabs(cpt) + rt_eps);
          this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
        }
      }
      // reserve last value for global statistics
      this->wspace.cut.push_back(0.0f);
      this->wspace.rptr.push_back(static_cast<unsigned>(this->wspace.cut.size()));
    }
    utils::Assert(this->wspace.rptr.size() ==
                  (fset.size() + 1) * this->qexpand.size() + 1,
                  "cut space inconsistent");
  }