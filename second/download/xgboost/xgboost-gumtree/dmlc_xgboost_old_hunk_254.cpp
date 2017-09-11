                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
                  param.num_deleted, deleted_nodes.size(), param.num_nodes);
  }
  /*! 
   * \brief save model to stream
   * \param fo output stream
   */
  inline void SaveModel(utils::IStream &fo) const {
    utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
                  "Tree::SaveModel");
    utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
                  "Tree::SaveModel");
    fo.Write(&param, sizeof(Param));
    utils::Assert(param.num_nodes != 0, "invalid model"); 
    fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
    fo.Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
    if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
  }
  /*! 
   * \brief add child nodes to node
   * \param nid node id to add childs
   */
