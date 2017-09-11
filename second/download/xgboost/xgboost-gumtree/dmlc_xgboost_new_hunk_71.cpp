  /*!
   * \brief get maximum depth
   */
  inline int MaxDepth() {
    int maxd = 0;
    for (int i = 0; i < param.num_roots; ++i) {
      maxd = std::max(maxd, MaxDepth(i));
    }
    return maxd;
  }
  /*! \brief number of extra nodes besides the root */
  inline int num_extra_nodes() const {
    return param.num_nodes - param.num_roots - param.num_deleted;
  }
};

/*! \brief node statistics used in regression tree */
