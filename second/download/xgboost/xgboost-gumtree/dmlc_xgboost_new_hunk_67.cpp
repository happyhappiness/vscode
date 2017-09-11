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
    Node() : sindex_(0) {
      // assert compact alignment
      static_assert(sizeof(Node) == 4 * sizeof(int) + sizeof(Info),
                    "Node: 64 bit align");
    }
    /*! \brief index of left child */
    inline int cleft() const {
      return this->cleft_;
    }
    /*! \brief index of right child */
    inline int cright() const {
      return this->cright_;
    }
    /*! \brief index of default child when feature is missing */
    inline int cdefault() const {
      return this->default_left() ? this->cleft() : this->cright();
    }
    /*! \brief feature index of split condition */
    inline unsigned split_index() const {
      return sindex_ & ((1U << 31) - 1U);
    }
    /*! \brief when feature is unknown, whether goes to left child */
    inline bool default_left() const {
      return (sindex_ >> 31) != 0;
    }
    /*! \brief whether current node is leaf node */
    inline bool is_leaf() const {
      return cleft_ == -1;
    }
    /*! \brief get leaf value of leaf node */
    inline float leaf_value() const {
      return (this->info_).leaf_value;
    }
    /*! \brief get split condition of the node */
    inline TSplitCond split_cond() const {
      return (this->info_).split_cond;
    }
    /*! \brief get parent of the node */
    inline int parent() const {
      return parent_ & ((1U << 31) - 1);
    }
    /*! \brief whether current node is left child */
    inline bool is_left_child() const {
      return (parent_ & (1U << 31)) != 0;
    }
    /*! \brief whether this node is deleted */
    inline bool is_deleted() const {
      return sindex_ == std::numeric_limits<unsigned>::max();
    }
    /*! \brief whether current node is root */
    inline bool is_root() const {
      return parent_ == -1;
    }
    /*!
