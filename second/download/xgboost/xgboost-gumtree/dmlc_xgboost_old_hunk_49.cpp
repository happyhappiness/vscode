  //  ------class member helpers---------
  /*! \brief initialize temp data structure */
  inline void InitData(const std::vector<bst_gpair> &gpair,
                       const IFMatrix &fmat,
                       const std::vector<unsigned> &root_index,
                       const RegTree &tree) {
    utils::Assert(tree.param.num_nodes == tree.param.num_roots,
                  "TreeMaker: can only grow new tree");
    {
      // setup position
      position.resize(gpair.size());
