inline void FindSplit(int depth,
                        const std::vector<bst_gpair> &gpair,
                        DMatrix *p_fmat,
                        RegTree *p_tree) {
    const bst_uint num_feature = p_tree->param.num_feature;
    // get the best split condition for each node
    std::vector<SplitEntry> sol(qexpand.size());
    bst_omp_uint nexpand = static_cast<bst_omp_uint>(qexpand.size());
    #pragma omp parallel for schedule(dynamic, 1)
    for (bst_omp_uint wid = 0; wid < nexpand; ++wid) {
      const int nid = qexpand[wid];
      CHECK_EQ(node2workindex[nid], static_cast<int>(wid));
      SplitEntry &best = sol[wid];
      for (bst_uint fid = 0; fid < num_feature; ++fid) {
        unsigned base = (wid * p_tree->param.num_feature + fid) * 3;
        EnumerateSplit(summary_array[base + 0],
                       summary_array[base + 1],
                       summary_array[base + 2],
                       node_stats[nid], fid, &best);
      }
    }
    // get the best result, we can synchronize the solution
    for (bst_omp_uint wid = 0; wid < nexpand; ++wid) {
      const int nid = qexpand[wid];
      const SplitEntry &best = sol[wid];
      // set up the values
      p_tree->stat(nid).loss_chg = best.loss_chg;
      this->SetStats(nid, node_stats[nid], p_tree);
      // now we know the solution in snode[nid], set split
      if (best.loss_chg > rt_eps) {
        p_tree->AddChilds(nid);
        (*p_tree)[nid].set_split(best.split_index(),
                                 best.split_value, best.default_left());
        // mark right child as 0, to indicate fresh leaf
        (*p_tree)[(*p_tree)[nid].cleft()].set_leaf(0.0f, 0);
        (*p_tree)[(*p_tree)[nid].cright()].set_leaf(0.0f, 0);
      } else {
        (*p_tree)[nid].set_leaf(p_tree->stat(nid).base_weight * param.eta);
      }
    }
  }