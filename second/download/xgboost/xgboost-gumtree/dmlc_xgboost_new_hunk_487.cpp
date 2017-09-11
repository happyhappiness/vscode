    leaf_vector.resize(param.num_nodes * param.size_leaf_vector); 
    return nd;
  }
  // delete a tree node, keep the parent field to allow trace back
  inline void DeleteNode(int nid) {
    utils::Assert(nid >= param.num_roots, "can not delete root");
    deleted_nodes.push_back(nid);
    nodes[nid].mark_delete();
    ++param.num_deleted;
  }

