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