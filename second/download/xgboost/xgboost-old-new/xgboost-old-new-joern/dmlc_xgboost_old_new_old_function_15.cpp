inline void UpdateBufferByPosition(IFMatrix *p_fmat,
                                     int64_t buffer_offset,
                                     int bst_group,
                                     const tree::RegTree &new_tree,
                                     const int* leaf_position) {
    const std::vector<bst_uint> &rowset = p_fmat->buffered_rowset();
    const bst_omp_uint ndata = static_cast<bst_omp_uint>(rowset.size());
    #pragma omp parallel for schedule(static)
    for (bst_omp_uint i = 0; i < ndata; ++i) {
      const bst_uint ridx = rowset[i];
      const int64_t bid = mparam.BufferOffset(buffer_offset + ridx, bst_group);
      const int tid = leaf_position[ridx];
      utils::Assert(pred_counter[bid] == trees.size(), "cached buffer not up to date");
      utils::Assert(tid >= 0, "invalid leaf position");
      pred_buffer[bid] += new_tree[tid].leaf_value();
      for (int i = 0; i < mparam.size_leaf_vector; ++i) {
        pred_buffer[bid + i + 1] += new_tree.leafvec(tid)[i];
      }
      pred_counter[bid] += tparam.num_parallel_tree;
    }
  }