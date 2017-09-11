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
