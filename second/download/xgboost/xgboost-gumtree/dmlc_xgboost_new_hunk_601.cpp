    fclose(fi);
    return true;
  }
  inline std::vector<float>& GetFloatInfo(const char *field) {
    if (!strcmp(field, "label")) return labels;
    if (!strcmp(field, "weight")) return weights;
    if (!strcmp(field, "base_margin")) return base_margin;
    utils::Error("unknown field %s", field);
    return labels;
  }
  inline const std::vector<float>& GetFloatInfo(const char *field) const {
    return ((MetaInfo*)this)->GetFloatInfo(field);
  }
  inline std::vector<unsigned> &GetUIntInfo(const char *field) {
    if (!strcmp(field, "root_index")) return info.root_index;
    if (!strcmp(field, "fold_index")) return info.fold_index;
    utils::Error("unknown field %s", field);
    return info.root_index;
  }
  inline const std::vector<unsigned> &GetUIntInfo(const char *field) const {
    return ((MetaInfo*)this)->GetUIntInfo(field);
  }
  // try to load weight information from file, if exists
  inline bool TryLoadFloatInfo(const char *field, const char* fname, bool silent = false) {
    std::vector<float> &weights = this->GetFloatInfo(field);
    FILE *fi = fopen64(fname, "r");
    if (fi == NULL) return false;
    float wt;
