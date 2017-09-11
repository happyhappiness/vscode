inline void InitData(const std::vector<bst_gpair> &gpair,
                       const DMatrix &fmat,
                       const RegTree &tree) {
    CHECK_EQ(tree.param.num_nodes, tree.param.num_roots)
        << "TreeMaker: can only grow new tree";
    const std::vector<unsigned> &root_index =  fmat.info().root_index;
    {
      // setup position
      position.resize(gpair.size());
      if (root_index.size() == 0) {
        std::fill(position.begin(), position.end(), 0);
      } else {
        for (size_t i = 0; i < position.size(); ++i) {
          position[i] = root_index[i];
          CHECK_LT(root_index[i], (unsigned)tree.param.num_roots)
              << "root index exceed setting";
        }
      }
      // mark delete for the deleted datas
      for (size_t i = 0; i < position.size(); ++i) {
        if (gpair[i].hess < 0.0f) position[i] = ~position[i];
      }
      // mark subsample
      if (param.subsample < 1.0f) {
        std::bernoulli_distribution coin_flip(param.subsample);
        auto& rnd = common::GlobalRandom();
        for (size_t i = 0; i < position.size(); ++i) {
          if (gpair[i].hess < 0.0f) continue;
          if (!coin_flip(rnd)) position[i] = ~position[i];
        }
      }
    }
    {
      // expand query
      qexpand.reserve(256); qexpand.clear();
      for (int i = 0; i < tree.param.num_roots; ++i) {
        qexpand.push_back(i);
      }
      this->UpdateNode2WorkIndex(tree);
    }
  }