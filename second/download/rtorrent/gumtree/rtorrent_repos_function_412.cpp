virtual bool operator () (Download* d1, Download* d2) const {
    return d1->download()->name() < d2->download()->name();
  }