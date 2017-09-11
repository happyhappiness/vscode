   * \brief load model from stream
   * \param fi input stream
   */
  inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
    utils::Check(fi.Read(&param, sizeof(Param)) > 0,
                 "TreeModel: wrong format");
    nodes.resize(param.num_nodes); stats.resize(param.num_nodes);
    utils::Assert(param.num_nodes != 0, "invalid model");
    utils::Check(fi.Read(BeginPtr(nodes), sizeof(Node) * nodes.size()) > 0,
                 "TreeModel: wrong format");
    utils::Check(fi.Read(BeginPtr(stats), sizeof(NodeStat) * stats.size()) > 0,
                 "TreeModel: wrong format");
    if (param.size_leaf_vector != 0) {
      utils::Check(fi.Read(&leaf_vector), "TreeModel: wrong format");
    }
    // chg deleted nodes
    deleted_nodes.resize(0);
    for (int i = param.num_roots; i < param.num_nodes; ++i) {
      if (nodes[i].is_deleted()) deleted_nodes.push_back(i);
    }
    utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
                  "number of deleted nodes do not match, num_deleted=%d, dnsize=%lu, num_nodes=%d",
                  param.num_deleted, deleted_nodes.size(), param.num_nodes);
  }
  /*!
   * \brief save model to stream
   * \param fo output stream
   */
  inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
    utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
                  "TreeModel::SaveModel");
    utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
                  "TreeModel::SaveModel");
    fo.Write(&param, sizeof(Param));
    utils::Assert(param.num_nodes != 0, "invalid model");
    fo.Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
    fo.Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
    if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
  }
  /*!
   * \brief add child nodes to node
