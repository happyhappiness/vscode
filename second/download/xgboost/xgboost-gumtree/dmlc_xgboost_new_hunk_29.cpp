                 ntree_limit);
    }
  }
  void PredictLeaf(DMatrix* p_fmat,
                   std::vector<float>* out_preds,
                   unsigned ntree_limit) {
    int nthread;
    #pragma omp parallel
    {
      nthread = omp_get_num_threads();
    }
    InitThreadTemp(nthread);
    this->PredPath(p_fmat, out_preds, ntree_limit);
  }
  std::vector<std::string> Dump2Text(const FeatureMap& fmap, int option) {
    std::vector<std::string> dump;
    for (size_t i = 0; i < trees.size(); i++) {
      dump.push_back(trees[i]->Dump2Text(fmap, option & 1));
    }
    return dump;
  }

 protected:
  // initialize updater before using them
  inline void InitUpdater() {
    if (updaters.size() != 0) return;
    std::string tval = tparam.updater_seq;
    char *pstr;
    pstr = std::strtok(&tval[0], ",");
    while (pstr != nullptr) {
      std::unique_ptr<TreeUpdater> up(TreeUpdater::Create(pstr));
      up->Init(this->cfg);
      updaters.push_back(std::move(up));
      pstr = std::strtok(nullptr, ",");
    }
  }
  // do group specific group
  inline void
  BoostNewTrees(const std::vector<bst_gpair> &gpair,
                DMatrix *p_fmat,
                int64_t buffer_offset,
                int bst_group,
                std::vector<std::unique_ptr<RegTree> >* ret) {
    this->InitUpdater();
    std::vector<RegTree*> new_trees;
    ret->clear();
    // create the trees
    for (int i = 0; i < tparam.num_parallel_tree; ++i) {
      std::unique_ptr<RegTree> ptr(new RegTree());
      ptr->param.InitAllowUnknown(this->cfg);
      ptr->InitModel();
      new_trees.push_back(ptr.get());
      ret->push_back(std::move(ptr));
    }
    // update the trees
    for (auto& up : updaters) {
      up->Update(gpair, p_fmat, new_trees);
    }
    // optimization, update buffer, if possible
    // this is only under distributed column mode
    // for safety check of lazy checkpoint
    if (buffer_offset >= 0 &&
        new_trees.size() == 1 && updaters.size() > 0 &&
        updaters.back()->GetLeafPosition() != nullptr) {
      CHECK_EQ(p_fmat->info().num_row, p_fmat->buffered_rowset().size());
      this->UpdateBufferByPosition(p_fmat,
                                   buffer_offset,
                                   bst_group,
                                   *new_trees[0],
                                   updaters.back()->GetLeafPosition());
    }
  }
  // commit new trees all at once
  inline void CommitModel(std::vector<std::unique_ptr<RegTree> >&& new_trees,
                          int bst_group) {
    for (size_t i = 0; i < new_trees.size(); ++i) {
      trees.push_back(std::move(new_trees[i]));
      tree_info.push_back(bst_group);
    }
    mparam.num_trees += static_cast<int>(new_trees.size());
  }
  // update buffer by pre-cached position
  inline void UpdateBufferByPosition(DMatrix *p_fmat,
                                     int64_t buffer_offset,
                                     int bst_group,
                                     const RegTree &new_tree,
                                     const int* leaf_position) {
    const std::vector<bst_uint>& rowset = p_fmat->buffered_rowset();
    const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
    #pragma omp parallel for schedule(static)
    for (bst_omp_uint i = 0; i < ndata; ++i) {
      const bst_uint ridx = rowset[i];
      const int64_t bid = mparam.BufferOffset(buffer_offset + ridx, bst_group);
      const int tid = leaf_position[ridx];
      CHECK_EQ(pred_counter[bid], trees.size());
      CHECK_GE(tid, 0);
      pred_buffer[bid] += new_tree[tid].leaf_value();
      for (int i = 0; i < mparam.size_leaf_vector; ++i) {
        pred_buffer[bid + i + 1] += new_tree.leafvec(tid)[i];
