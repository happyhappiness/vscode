void SaveModel(dmlc::Stream* fo) const override {
    CHECK_EQ(mparam.num_trees, static_cast<int>(trees.size()));
    // not save predict buffer.
    GBTreeModelParam p = mparam;
    p.num_pbuffer = 0;
    fo->Write(&p, sizeof(p));
    for (size_t i = 0; i < trees.size(); ++i) {
      trees[i]->SaveModel(fo);
    }
    if (tree_info.size() != 0) {
      fo->Write(dmlc::BeginPtr(tree_info), sizeof(int) * tree_info.size());
    }
  }