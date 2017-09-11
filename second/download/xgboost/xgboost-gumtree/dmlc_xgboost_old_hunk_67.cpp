    /*! \brief reserved part */
    int reserved[31];
    /*! \brief constructor */
    Param(void) {
      max_depth = 0;
      size_leaf_vector = 0;
      std::memset(reserved, 0, sizeof(reserved));
    }
    /*!
     * \brief set parameters from outside
     * \param name name of the parameter
     * \param val  value of the parameter
     */
    inline void SetParam(const char *name, const char *val) {
      using namespace std;
      if (!strcmp("num_roots", name)) num_roots = atoi(val);
      if (!strcmp("num_feature", name)) num_feature = atoi(val);
      if (!strcmp("size_leaf_vector", name)) size_leaf_vector = atoi(val);
    }
  };
  /*! \brief tree node */
  class Node {
   public:
    Node(void) : sindex_(0) {}
    /*! \brief index of left child */
    inline int cleft(void) const {
      return this->cleft_;
    }
    /*! \brief index of right child */
    inline int cright(void) const {
      return this->cright_;
    }
    /*! \brief index of default child when feature is missing */
    inline int cdefault(void) const {
      return this->default_left() ? this->cleft() : this->cright();
    }
    /*! \brief feature index of split condition */
    inline unsigned split_index(void) const {
      return sindex_ & ((1U << 31) - 1U);
    }
    /*! \brief when feature is unknown, whether goes to left child */
    inline bool default_left(void) const {
      return (sindex_ >> 31) != 0;
    }
    /*! \brief whether current node is leaf node */
    inline bool is_leaf(void) const {
      return cleft_ == -1;
    }
    /*! \brief get leaf value of leaf node */
    inline float leaf_value(void) const {
      return (this->info_).leaf_value;
    }
    /*! \brief get split condition of the node */
    inline TSplitCond split_cond(void) const {
      return (this->info_).split_cond;
    }
    /*! \brief get parent of the node */
    inline int parent(void) const {
      return parent_ & ((1U << 31) - 1);
    }
    /*! \brief whether current node is left child */
    inline bool is_left_child(void) const {
      return (parent_ & (1U << 31)) != 0;
    }
    /*! \brief whether this node is deleted */
    inline bool is_deleted(void) const {
      return sindex_ == std::numeric_limits<unsigned>::max();
    }
    /*! \brief whether current node is root */
    inline bool is_root(void) const {
      return parent_ == -1;
    }
    /*!
