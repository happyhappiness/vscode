inline void SyncNodeStats(void) {
    CHECK_NE(qexpand.size(), 0);
    std::vector<SKStats> tmp(qexpand.size());
    for (size_t i = 0; i < qexpand.size(); ++i) {
      tmp[i] = node_stats[qexpand[i]];
    }
    stats_reducer.Allreduce(dmlc::BeginPtr(tmp), tmp.size());
    for (size_t i = 0; i < qexpand.size(); ++i) {
      node_stats[qexpand[i]] = tmp[i];
    }
  }