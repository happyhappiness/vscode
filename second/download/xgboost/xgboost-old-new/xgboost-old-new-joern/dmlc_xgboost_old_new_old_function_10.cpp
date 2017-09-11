virtual void SaveModel(utils::IStream &fo, bool with_pbuffer) const { // NOLINT(*)
    utils::Assert(mparam.num_trees == static_cast<int>(trees.size()), "GBTree");
    if (with_pbuffer) {
      fo.Write(&mparam, sizeof(ModelParam));
    } else {
      ModelParam p = mparam;
      p.num_pbuffer = 0;
      fo.Write(&p, sizeof(ModelParam));
    }
    for (size_t i = 0; i < trees.size(); ++i) {
      trees[i]->SaveModel(fo);
    }
    if (tree_info.size() != 0) {
      fo.Write(BeginPtr(tree_info), sizeof(int) * tree_info.size());
    }
    if (mparam.num_pbuffer != 0 && with_pbuffer) {
      fo.Write(BeginPtr(pred_buffer), pred_buffer.size() * sizeof(float));
      fo.Write(BeginPtr(pred_counter), pred_counter.size() * sizeof(unsigned));
    }
  }