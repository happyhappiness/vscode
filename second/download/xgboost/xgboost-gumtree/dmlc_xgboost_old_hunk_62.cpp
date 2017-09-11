    #pragma omp parallel for schedule(dynamic, 1)
    for (bst_omp_uint wid = 0; wid < nexpand; ++wid) {
      const int nid = qexpand[wid];
      utils::Assert(node2workindex[nid] == static_cast<int>(wid),
                    "node2workindex inconsistent");
      SplitEntry &best = sol[wid];
      for (bst_uint fid = 0; fid < num_feature; ++fid) {
        unsigned base = (wid * p_tree->param.num_feature + fid) * 3;
