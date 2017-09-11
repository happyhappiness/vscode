inline void DeleteNode(int nid) {
    CHECK_GE(nid, param.num_roots);
    deleted_nodes.push_back(nid);
    nodes[nid].mark_delete();
    ++param.num_deleted;
  }