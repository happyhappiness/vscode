    inline void Add(bst_float fv,
                    bst_gpair gstats) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      CHECK_NE(istart, hist.size);
      hist.data[istart].Add(gstats);
    }
  };
  // sketch type used for this
  typedef common::WXQuantileSketch<bst_float, bst_float> WXQSketch;
  // initialize the work set of tree
  void InitWorkSet(DMatrix *p_fmat,
                   const RegTree &tree,
                   std::vector<bst_uint> *p_fset) override {
    feat_helper.InitByCol(p_fmat, tree);
    feat_helper.SampleCol(this->param.colsample_bytree, p_fset);
  }
  // code to create histogram
  void CreateHist(const std::vector<bst_gpair> &gpair,
                  DMatrix *p_fmat,
                  const std::vector<bst_uint> &fset,
                  const RegTree &tree) override {
    const MetaInfo &info = p_fmat->info();
    // fill in reverse map
    feat2workindex.resize(tree.param.num_feature);
    std::fill(feat2workindex.begin(), feat2workindex.end(), -1);
