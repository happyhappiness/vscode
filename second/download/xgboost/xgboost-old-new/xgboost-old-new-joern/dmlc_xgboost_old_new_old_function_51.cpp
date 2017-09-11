virtual void ResetPosAndPropose(const std::vector<bst_gpair> &gpair,
                                  IFMatrix *p_fmat,
                                  const BoosterInfo &info,
                                  const std::vector <bst_uint> &fset,
                                  const RegTree &tree) {
    // initialize the data structure
    int nthread = BaseMaker::get_nthread();
    sketchs.resize(this->qexpand.size() * tree.param.num_feature);
    for (size_t i = 0; i < sketchs.size(); ++i) {
      sketchs[i].Init(info.num_row, this->param.sketch_eps);
    }
    // start accumulating statistics
    utils::IIterator<RowBatch> *iter = p_fmat->RowIterator();
    iter->BeforeFirst();
    while (iter->Next()) {
      const RowBatch &batch = iter->Value();
      // parallel convert to column major format
      utils::ParallelGroupBuilder<SparseBatch::Entry> builder(&col_ptr, &col_data, &thread_col_ptr);
      builder.InitBudget(tree.param.num_feature, nthread);

      const bst_omp_uint nbatch = static_cast<bst_omp_uint>(batch.size);
      #pragma omp parallel for schedule(static)
      for (bst_omp_uint i = 0; i < nbatch; ++i) {
        RowBatch::Inst inst = batch[i];
        const bst_uint ridx = static_cast<bst_uint>(batch.base_rowid + i);
        int nid = this->position[ridx];
        if (nid >= 0) {
          if (!tree[nid].is_leaf()) {
            this->position[ridx] = nid = HistMaker<TStats>::NextLevel(inst, tree, nid);
          }
          if (this->node2workindex[nid] < 0) {
            this->position[ridx] = ~nid;
          } else {
            for (bst_uint j = 0; j < inst.length; ++j) {
              builder.AddBudget(inst[j].index, omp_get_thread_num());
            }
          }
        }
      }
      builder.InitStorage();
      #pragma omp parallel for schedule(static)
      for (bst_omp_uint i = 0; i < nbatch; ++i) {
        RowBatch::Inst inst = batch[i];
        const bst_uint ridx = static_cast<bst_uint>(batch.base_rowid + i);
        const int nid = this->position[ridx];
        if (nid >= 0) {
          for (bst_uint j = 0; j < inst.length; ++j) {
            builder.Push(inst[j].index,
                         SparseBatch::Entry(nid, inst[j].fvalue),
                         omp_get_thread_num());
          }
        }
      }
      // start putting things into sketch
      const bst_omp_uint nfeat = col_ptr.size() - 1;
      #pragma omp parallel for schedule(dynamic, 1)
      for (bst_omp_uint k = 0; k < nfeat; ++k) {
        for (size_t i = col_ptr[k]; i < col_ptr[k+1]; ++i) {
          const SparseBatch::Entry &e = col_data[i];
          const int wid = this->node2workindex[e.index];
          sketchs[wid * tree.param.num_feature + k].Push(e.fvalue, gpair[e.index].hess);
        }
      }
    }
    // setup maximum size
    unsigned max_size = this->param.max_sketch_size();
    // synchronize sketch
    summary_array.resize(sketchs.size());
    for (size_t i = 0; i < sketchs.size(); ++i) {
      utils::WQuantileSketch<bst_float, bst_float>::SummaryContainer out;
      sketchs[i].GetSummary(&out);
      summary_array[i].Reserve(max_size);
      summary_array[i].SetPrune(out, max_size);
    }

    size_t nbytes = WXQSketch::SummaryContainer::CalcMemCost(max_size);
    sreducer.Allreduce(BeginPtr(summary_array), nbytes, summary_array.size());
    // now we get the final result of sketch, setup the cut
    this->wspace.cut.clear();
    this->wspace.rptr.clear();
    this->wspace.rptr.push_back(0);
    for (size_t wid = 0; wid < this->qexpand.size(); ++wid) {
      for (int fid = 0; fid < tree.param.num_feature; ++fid) {
        const WXQSketch::Summary &a = summary_array[wid * tree.param.num_feature + fid];
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
        this->wspace.rptr.push_back(this->wspace.cut.size());
      }
      // reserve last value for global statistics
      this->wspace.cut.push_back(0.0f);
      this->wspace.rptr.push_back(this->wspace.cut.size());
    }
    utils::Assert(this->wspace.rptr.size() ==
                  (tree.param.num_feature + 1) * this->qexpand.size() + 1,
                  "cut space inconsistent")