inline std::vector<float>& GetInfo(const char *field) {
    if (!strcmp(field, "label")) return labels;
    if (!strcmp(field, "weight")) return weights;
    if (!strcmp(field, "base_margin")) return base_margin;
    utils::Error("unknown field %s", field);
    return labels;
  }