inline void LoadModel(dmlc::Stream* fi) {
    CHECK_EQ(fi->Read(&param, sizeof(TreeParam)), sizeof(TreeParam));
    nodes.resize(param.num_nodes);
    stats.resize(param.num_nodes);
    CHECK_NE(param.num_nodes, 0);
    CHECK_EQ(fi->Read(dmlc::BeginPtr(nodes), sizeof(Node) * nodes.size()),
             sizeof(Node) * nodes.size());
    CHECK_EQ(fi->Read(dmlc::BeginPtr(stats), sizeof(NodeStat) * stats.size()),
             sizeof(NodeStat) * stats.size());
    if (param.size_leaf_vector != 0) {
      CHECK(fi->Read(&leaf_vector));
    }
    // chg deleted nodes
    deleted_nodes.resize(0);
    for (int i = param.num_roots; i < param.num_nodes; ++i) {
      if (nodes[i].is_deleted()) deleted_nodes.push_back(i);
    }
    CHECK_EQ(static_cast<int>(deleted_nodes.size()), param.num_deleted);
  }