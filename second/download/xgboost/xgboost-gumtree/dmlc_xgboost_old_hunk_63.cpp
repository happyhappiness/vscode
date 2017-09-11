
   protected:
    // initialize temp data structure
    inline void InitData(const std::vector<bst_gpair> &gpair,
                         const IFMatrix &fmat,
                         const std::vector<unsigned> &root_index,
                         const RegTree &tree) {
      utils::Assert(tree.param.num_nodes == tree.param.num_roots,
                    "ColMaker: can only grow new tree");
      const std::vector<bst_uint> &rowset = fmat.buffered_rowset();
      {
        // setup position
        position.resize(gpair.size());
