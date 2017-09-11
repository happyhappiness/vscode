const Type& type(size_t idx) const {
    utils::Assert(idx < names_.size(), "utils::FMap::type feature index exceed bound");
    return types_[idx];
  }