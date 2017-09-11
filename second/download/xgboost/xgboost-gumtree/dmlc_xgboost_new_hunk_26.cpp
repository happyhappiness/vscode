      std::fill(weight.begin(), weight.end(), 0.0f);
    }
    // save the model to file
    inline void SaveModel(dmlc::Stream* fo) const {
      fo->Write(&param, sizeof(param));
      fo->Write(weight);
    }
    // load model from file
    inline void LoadModel(dmlc::Stream* fi) {
      CHECK_EQ(fi->Read(&param, sizeof(param)), sizeof(param));
      fi->Read(&weight);
    }
    // model bias
    inline float* bias(void) {
