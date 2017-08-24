{
      this->argv_[i] = other.argv_[i] ? strdup(other.argv_[i]) : 0;
    }