virtual void Load(Stream *fi) {
    uint64_t sz;
    utils::Assert(fi->Read(&sz, sizeof(sz)) != 0,
                 "Read pickle string");
    p_str->resize(sz);
    if (sz != 0) {
      utils::Assert(fi->Read(&(*p_str)[0], sizeof(char) * sz) != 0,
                    "Read pickle string");
    }
  }