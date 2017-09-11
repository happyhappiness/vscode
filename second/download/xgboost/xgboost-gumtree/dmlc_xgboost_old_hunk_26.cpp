      std::fill(weight.begin(), weight.end(), 0.0f);
    }
    // save the model to file
    inline void SaveModel(utils::IStream &fo) const { // NOLINT(*)
      fo.Write(&param, sizeof(Param));
      fo.Write(weight);
    }
    // load model from file
    inline void LoadModel(utils::IStream &fi) { // NOLINT(*)
      utils::Assert(fi.Read(&param, sizeof(Param)) != 0, "Load LinearBooster");
      fi.Read(&weight);
    }
    // model bias
    inline float* bias(void) {
