  explicit ConfigIterator(const char *fname) : ConfigStreamReader(fi) {
    fi.open(fname);
    if (fi.fail()) {
      LOG(FATAL) << "cannot open file " << fname;
    }
    ConfigReaderBase::Init();
  }
