    fclose(fi);
    return true;
  }
  inline std::vector<float>& GetInfo(const char *field) {
    if (!strcmp(field, "label")) return labels;
    if (!strcmp(field, "weight")) return weights;
    if (!strcmp(field, "base_margin")) return base_margin;
    utils::Error("unknown field %s", field);
    return labels;
  }
  inline const std::vector<float>& GetInfo(const char *field) const {
    return ((MetaInfo*)this)->GetInfo(field);
  }
  // try to load weight information from file, if exists
  inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
    std::vector<float> &weights = this->GetInfo(field);       
    FILE *fi = fopen64(fname, "r");
    if (fi == NULL) return false;
    float wt;
    while (fscanf(fi, "%f", &wt) == 1) {
      weights.push_back(wt);
    }
    if (!silent) {
      printf("loading %s from %s\n", field, fname);
    }
    fclose(fi);
    return true;
