  }
  // initialize the manager
  inline void Init(void) {
    // single node mode
    if (master_uri == "NULL") return;
    utils::Assert(links.size() == 0, "can only call Init once");
