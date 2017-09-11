inline void SaveModel(dmlc::Stream* fo) const {
    CHECK_EQ(param.num_nodes, static_cast<int>(nodes.size()));
    CHECK_EQ(param.num_nodes, static_cast<int>(stats.size()));
    fo->Write(&param, sizeof(TreeParam));
    CHECK_NE(param.num_nodes, 0);
    fo->Write(BeginPtr(nodes), sizeof(Node) * nodes.size());
    fo->Write(BeginPtr(stats), sizeof(NodeStat) * nodes.size());
    if (param.size_leaf_vector != 0) fo->Write(leaf_vector);
  }