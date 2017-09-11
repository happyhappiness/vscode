    }
  }
  inline void SyncNodeStats(void) {
    utils::Assert(qexpand.size() != 0, "qexpand must not be empty");
    std::vector<SKStats> tmp(qexpand.size());
    for (size_t i = 0; i < qexpand.size(); ++i) {
      tmp[i] = node_stats[qexpand[i]];
    }
    stats_reducer.Allreduce(BeginPtr(tmp), tmp.size());
    for (size_t i = 0; i < qexpand.size(); ++i) {
      node_stats[qexpand[i]] = tmp[i];
    }
  }
  inline void FindSplit(int depth,
                        const std::vector<bst_gpair> &gpair,
                        IFMatrix *p_fmat,
                        const BoosterInfo &info,
                        RegTree *p_tree) {
    const bst_uint num_feature = p_tree->param.num_feature;
    // get the best split condition for each node
