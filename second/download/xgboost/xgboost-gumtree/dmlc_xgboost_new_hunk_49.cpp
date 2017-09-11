  //  ------class member helpers---------
  /*! \brief initialize temp data structure */
  inline void InitData(const std::vector<bst_gpair> &gpair,
                       const DMatrix &fmat,
                       const RegTree &tree) {
    CHECK_EQ(tree.param.num_nodes, tree.param.num_roots)
        << "TreeMaker: can only grow new tree";
    const std::vector<unsigned> &root_index =  fmat.info().root_index;
    {
      // setup position
      position.resize(gpair.size());
