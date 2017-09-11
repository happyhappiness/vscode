inline void LoadModel(utils::IStream &fi) {
    utils::Check(fi.Read(&param, sizeof(Param)) > 0,
                 "TreeModel: wrong format");
    nodes.resize(param.num_nodes); stats.resize(param.num_nodes);
    utils::Check(fi.Read(&nodes[0], sizeof(Node) * nodes.size()) > 0,
                 "TreeModel: wrong format");
    utils::Check(fi.Read(&stats[0], sizeof(NodeStat) * stats.size()) > 0,
                 "TreeModel: wrong format");
    if (param.size_leaf_vector != 0) {
      utils::Check(fi.Read(&leaf_vector), "TreeModel: wrong format");
    }
    // chg deleted nodes
    deleted_nodes.resize(0);
    for (int i = param.num_roots; i < param.num_nodes; i ++) {
      if (nodes[i].is_root()) deleted_nodes.push_back(i);
    }
    utils::Assert(static_cast<int>(deleted_nodes.size()) == param.num_deleted,
                  "number of deleted nodes do not match");
  }