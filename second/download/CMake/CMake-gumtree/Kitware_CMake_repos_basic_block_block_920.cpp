(cc = 0; cc < argc; ++cc) {
    delete[](*argv)[cc];
  }