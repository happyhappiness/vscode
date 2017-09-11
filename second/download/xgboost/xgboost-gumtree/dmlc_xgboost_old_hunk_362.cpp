    leaf_vector.resize(param.num_nodes * param.size_leaf_vector); 
    return nd;
  }
  // delete a tree node
  inline void DeleteNode(int nid) {
    utils::Assert(nid >= param.num_roots, "can not delete root");
    deleted_nodes.push_back(nid);
    nodes[nid].set_parent(-1);
    ++param.num_deleted;
  }

