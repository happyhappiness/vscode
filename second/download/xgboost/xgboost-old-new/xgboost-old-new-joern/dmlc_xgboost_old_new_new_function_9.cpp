inline void LoadModel(dmlc::Stream* fi) {
      CHECK_EQ(fi->Read(&param, sizeof(param)), sizeof(param));
      fi->Read(&weight);
    }