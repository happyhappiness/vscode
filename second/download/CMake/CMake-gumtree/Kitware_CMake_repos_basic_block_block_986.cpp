(i = 0; i < this->argv_.size(); i++) {
      free(this->argv_[i]);
    }