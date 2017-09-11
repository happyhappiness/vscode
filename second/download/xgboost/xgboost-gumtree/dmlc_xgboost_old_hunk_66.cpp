  typedef TNodeStat  NodeStat;
  /*! \brief auxiliary statistics of node to help tree building */
  typedef TSplitCond SplitCond;
  /*! \brief parameters of the tree */
  struct TreeParam {
    /*! \brief number of start root */
    int num_roots;
    /*! \brief total number of nodes */
    int num_nodes;
    /*!\brief number of deleted nodes */
    int num_deleted;
    /*! \brief maximum depth, this is a statistics of the tree */
    int max_depth;
    /*! \brief  number of features used for tree construction */
    int num_feature;
    /*!
     * \brief leaf vector size, used for vector tree
     * used to store more than one dimensional information in tree
     */
    int size_leaf_vector;
    /*! \brief reserved part */
    int reserved[31];
    /*! \brief constructor */
    TreeParam() {
      // assert compact alignment
      static_assert(sizeof(TreeParam) == (31 + 6) * sizeof(int),
                    "TreeParam: 64 bit align");
      std::memset(this, 0, sizeof(TreeParam));
      num_nodes = num_roots = 1;
    }
  };
  /*! \brief tree node */
  class Node {
   public:
