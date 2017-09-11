inline void SaveModel(utils::IStream &fo) const {
    utils::Assert(param.num_nodes == static_cast<int>(nodes.size()),
                  "Tree::SaveModel");
    utils::Assert(param.num_nodes == static_cast<int>(stats.size()),
                  "Tree::SaveModel");
    fo.Write(&param, sizeof(Param));
    fo.Write(&nodes[0], sizeof(Node) * nodes.size());
    fo.Write(&stats[0], sizeof(NodeStat) * nodes.size());
    if (param.size_leaf_vector != 0) fo.Write(leaf_vector);
  }