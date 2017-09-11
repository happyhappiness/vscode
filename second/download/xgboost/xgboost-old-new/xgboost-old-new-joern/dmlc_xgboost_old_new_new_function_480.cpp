inline std::vector<unsigned> &GetUIntInfo(const char *field) {
    if (!strcmp(field, "root_index")) return info.root_index;
    if (!strcmp(field, "fold_index")) return info.fold_index;
    utils::Error("unknown field %s", field);
    return info.root_index;
  }