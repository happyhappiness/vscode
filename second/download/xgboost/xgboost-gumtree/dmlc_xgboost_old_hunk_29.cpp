                 ntree_limit);
    }
  }
  virtual void PredictLeaf(IFMatrix *p_fmat,
                           const BoosterInfo &info,
                           std::vector<float> *out_preds,
                           unsigned ntree_limit) {
    int nthread;
    #pragma omp parallel
    {
      nthread = omp_get_num_threads();
    }
    InitThreadTemp(nthread);
    this->PredPath(p_fmat, info, out_preds, ntree_limit);
  }
  virtual std::vector<std::string> DumpModel(const utils::FeatMap& fmap, int option) {
    std::vector<std::string> dump;
    for (size_t i = 0; i < trees.size(); i++) {
      dump.push_back(trees[i]->DumpModel(fmap, option&1));
    }
    return dump;
  }

 protected:
  // clear the model
  inline void Clear(void) {
    for (size_t i = 0; i < trees.size(); ++i) {
      delete trees[i];
    }
    for (size_t i = 0; i < updaters.size(); ++i) {
      delete updaters[i];
    }
    updaters.clear();
    trees.clear();
    pred_buffer.clear();
    pred_counter.clear();
  }
  // initialize updater before using them
  inline void InitUpdater(void) {
    if (tparam.updater_initialized != 0) return;
    for (size_t i = 0; i < updaters.size(); ++i) {
      delete updaters[i];
    }
    updaters.clear();
    std::string tval = tparam.updater_seq;
    char *pstr;
    pstr = std::strtok(&tval[0], ",");
    while (pstr != NULL) {
      updaters.push_back(tree::CreateUpdater(pstr));
      for (size_t j = 0; j < cfg.size(); ++j) {
        // set parameters
        updaters.back()->SetParam(cfg[j].first.c_str(), cfg[j].second.c_str());
      }
      pstr = std::strtok(NULL, ",");
    }
    tparam.updater_initialized = 1;
  }
  // do group specific group
  inline std::vector<tree::RegTree*>
  BoostNewTrees(const std::vector<bst_gpair> &gpair,
                IFMatrix *p_fmat,
                int64_t buffer_offset,
                const BoosterInfo &info,
                int bst_group) {
    std::vector<tree::RegTree *> new_trees;
    this->InitUpdater();
    // create the trees
    for (int i = 0; i < tparam.num_parallel_tree; ++i) {
      new_trees.push_back(new tree::RegTree());
      for (size_t j = 0; j < cfg.size(); ++j) {
        new_trees.back()->param.SetParam(cfg[j].first.c_str(), cfg[j].second.c_str());
      }
      new_trees.back()->InitModel();
    }
    // update the trees
    for (size_t i = 0; i < updaters.size(); ++i) {
      updaters[i]->Update(gpair, p_fmat, info, new_trees);
    }
    // optimization, update buffer, if possible
    // this is only under distributed column mode
    // for safety check of lazy checkpoint
    if (
        buffer_offset >= 0 &&
        new_trees.size() == 1 && updaters.size() > 0 &&
        updaters.back()->GetLeafPosition() != NULL) {
      utils::Check(info.num_row == p_fmat->buffered_rowset().size(),
                   "distributed mode is not compatible with prob_buffer_row");
      this->UpdateBufferByPosition(p_fmat,
                                   buffer_offset, bst_group,
                                   *new_trees[0],
                                   updaters.back()->GetLeafPosition());
    }
    return new_trees;
  }
  // commit new trees all at once
  inline void CommitModel(const std::vector<tree::RegTree*> &new_trees, int bst_group) {
    for (size_t i = 0; i < new_trees.size(); ++i) {
      trees.push_back(new_trees[i]);
      tree_info.push_back(bst_group);
    }
    mparam.num_trees += static_cast<int>(new_trees.size());
  }
  // update buffer by pre-cached position
  inline void UpdateBufferByPosition(IFMatrix *p_fmat,
                                     int64_t buffer_offset,
                                     int bst_group,
                                     const tree::RegTree &new_tree,
                                     const int* leaf_position) {
    const std::vector<bst_uint> &rowset = p_fmat->buffered_rowset();
    const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
    #pragma omp parallel for schedule(static)
    for (bst_omp_uint i = 0; i < ndata; ++i) {
      const bst_uint ridx = rowset[i];
      const int64_t bid = mparam.BufferOffset(buffer_offset + ridx, bst_group);
      const int tid = leaf_position[ridx];
      utils::Assert(pred_counter[bid] == trees.size(), "cached buffer not up to date");
      utils::Assert(tid >= 0, "invalid leaf position");
      pred_buffer[bid] += new_tree[tid].leaf_value();
      for (int i = 0; i < mparam.size_leaf_vector; ++i) {
        pred_buffer[bid + i + 1] += new_tree.leafvec(tid)[i];
