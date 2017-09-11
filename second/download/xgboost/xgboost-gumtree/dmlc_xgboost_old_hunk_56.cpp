    inline void Add(bst_float fv,
                    bst_gpair gstats) {
      while (istart < hist.size && !(fv < hist.cut[istart])) ++istart;
      utils::Assert(istart != hist.size, "the bound variable must be max");
      hist.data[istart].Add(gstats);
    }
  };
  // sketch type used for this
  typedef utils::WXQuantileSketch<bst_float, bst_float> WXQSketch;
  // initialize the work set of tree
  virtual void InitWorkSet(IFMatrix *p_fmat,
                           const RegTree &tree,
                           std::vector<bst_uint> *p_fset) {
    feat_helper.InitByCol(p_fmat, tree);
    feat_helper.SampleCol(this->param.colsample_bytree, p_fset);
  }
  // code to create histogram
  virtual void CreateHist(const std::vector<bst_gpair> &gpair,
                          IFMatrix *p_fmat,
                          const BoosterInfo &info,
                          const std::vector<bst_uint> &fset,
                          const RegTree &tree) {
    // fill in reverse map
    feat2workindex.resize(tree.param.num_feature);
    std::fill(feat2workindex.begin(), feat2workindex.end(), -1);
