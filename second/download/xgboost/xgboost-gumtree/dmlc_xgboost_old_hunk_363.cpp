    }
    // chg deleted nodes
    deleted_nodes.resize(0);
    for (int i = param.num_roots; i < param.num_nodes; i ++) {
      if (nodes[i].is_root()) deleted_nodes.push_back(i);
    }
    utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
                  "number of deleted nodes do not match");
  }
  /*! 
   * \brief save model to stream
