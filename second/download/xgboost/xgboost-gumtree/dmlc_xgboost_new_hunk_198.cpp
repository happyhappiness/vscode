      nodes[i].set_parent(-1);
    }
  }
  /*!
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
