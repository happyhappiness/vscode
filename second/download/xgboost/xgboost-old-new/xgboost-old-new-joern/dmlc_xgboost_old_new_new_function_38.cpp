inline int Type(bst_uint fid) const {
      CHECK_LT(fid * 2 + 1, fminmax.size())
          << "FeatHelper fid exceed query bound ";
      bst_float a = fminmax[fid * 2];
      bst_float b = fminmax[fid * 2 + 1];
      if (a == -std::numeric_limits<bst_float>::max()) return 0;
      if (-a == b) {
        return 1;
      } else {
        return 2;
      }
    }