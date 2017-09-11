inline void InitData(const std::vector<bst_gpair>& gpair,
                         const DMatrix& fmat,
                         const RegTree& tree) {
      CHECK_EQ(tree.param.num_nodes, tree.param.num_roots)
          << "ColMaker: can only grow new tree";
      const std::vector<unsigned>& root_index = fmat.info().root_index;
      const std::vector<bst_uint>& rowset = fmat.buffered_rowset();
      {
        // setup position
        position.resize(gpair.size());
        if (root_index.size() == 0) {
          for (size_t i = 0; i < rowset.size(); ++i) {
            position[rowset[i]] = 0;
          }
        } else {
          for (size_t i = 0; i < rowset.size(); ++i) {
            const bst_uint ridx = rowset[i];
            position[ridx] = root_index[ridx];
            CHECK_LT(root_index[ridx], (unsigned)tree.param.num_roots);
          }
        }
        // mark delete for the deleted datas
        for (size_t i = 0; i < rowset.size(); ++i) {
          const bst_uint ridx = rowset[i];
          if (gpair[ridx].hess < 0.0f) position[ridx] = ~position[ridx];
        }
        // mark subsample
        if (param.subsample < 1.0f) {
          std::bernoulli_distribution coin_flip(param.subsample);
          auto& rnd = common::GlobalRandom();
          for (size_t i = 0; i < rowset.size(); ++i) {
            const bst_uint ridx = rowset[i];
            if (gpair[ridx].hess < 0.0f) continue;
            if (!coin_flip(rnd)) position[ridx] = ~position[ridx];
          }
        }
      }
      {
        // initialize feature index
        unsigned ncol = static_cast<unsigned>(fmat.info().num_col);
        for (unsigned i = 0; i < ncol; ++i) {
          if (fmat.GetColSize(i) != 0) {
            feat_index.push_back(i);
          }
        }
        unsigned n = static_cast<unsigned>(param.colsample_bytree * feat_index.size());
        std::shuffle(feat_index.begin(), feat_index.end(), common::GlobalRandom());
        CHECK_GT(n, 0)
            << "colsample_bytree=" << param.colsample_bytree
            << " is too small that no feature can be included";
        feat_index.resize(n);
      }
      {
        // setup temp space for each thread
        #pragma omp parallel
        {
          this->nthread = omp_get_num_threads();
        }
        // reserve a small space
        stemp.clear();
        stemp.resize(this->nthread, std::vector<ThreadEntry>());
        for (size_t i = 0; i < stemp.size(); ++i) {
          stemp[i].clear(); stemp[i].reserve(256);
        }
        snode.reserve(256);
      }
      {
        // expand query
        qexpand_.reserve(256); qexpand_.clear();
        for (int i = 0; i < tree.param.num_roots; ++i) {
          qexpand_.push_back(i);
        }
      }
    }