  std::vector<bst_float> leaf_vector;
  // allocate a new node,
  // !!!!!! NOTE: may cause BUG here, nodes.resize
  inline int AllocNode(void) {
    if (param.num_deleted != 0) {
      int nd = deleted_nodes.back();
      deleted_nodes.pop_back();
      --param.num_deleted;
      return nd;
    }
    int nd = param.num_nodes++;
    utils::Check(param.num_nodes < std::numeric_limits<int>::max(),
                 "number of nodes in the tree exceed 2^31");
    nodes.resize(param.num_nodes);
    stats.resize(param.num_nodes);
    leaf_vector.resize(param.num_nodes * param.size_leaf_vector);
    return nd;
  }
  // delete a tree node, keep the parent field to allow trace back
  inline void DeleteNode(int nid) {
    utils::Assert(nid >= param.num_roots, "can not delete root");
    deleted_nodes.push_back(nid);
    nodes[nid].mark_delete();
    ++param.num_deleted;
