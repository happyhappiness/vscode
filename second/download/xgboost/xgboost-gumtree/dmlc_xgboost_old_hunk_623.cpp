    fclose(fi);
    return true;
  }
  // try to load weight information from file, if exists
  inline bool TryLoadWeight(const char* fname, bool silent = false) {
    FILE *fi = fopen64(fname, "r");
    if (fi == NULL) return false;
    float wt;
    while (fscanf(fi, "%f", &wt) == 1) {
      weights.push_back(wt);
    }
    if (!silent) {
      printf("loading weight from %s\n", fname);
    }
    fclose(fi);
    return true;
