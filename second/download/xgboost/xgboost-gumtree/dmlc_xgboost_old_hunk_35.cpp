  explicit ConfigIterator(const char *fname) : ConfigStreamReader(fi) {
    fi.open(fname);
    if (fi.fail()) {
      utils::Error("cannot open file %s", fname);
    }
    ConfigReaderBase::Init();
  }
