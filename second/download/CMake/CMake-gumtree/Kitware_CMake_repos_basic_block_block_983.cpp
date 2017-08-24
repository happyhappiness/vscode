(size_t i = 0; i < this->argv_.size(); i++) {
    this->argv_[i] = other.argv_[i] ? strdup(other.argv_[i]) : 0;
  }