inline void SetCacheData(const std::vector<DMatrix*>& mats) {
    utils::Assert(cache_.size() == 0, "can only call cache data once");
    // assign buffer index
    size_t buffer_size = 0;
    for (size_t i = 0; i < mats.size(); ++i) {
      bool dupilicate = false;
      for (size_t j = 0; j < i; ++j) {
        if (mats[i] == mats[j]) dupilicate = true;
      }
      if (dupilicate) continue;
      // set mats[i]'s cache learner pointer to this
      mats[i]->cache_learner_ptr_ = this;
      cache_.push_back(CacheEntry(mats[i], buffer_size, mats[i]->info.num_row()));
      buffer_size += mats[i]->info.num_row();
    }
    char str_temp[25];
    utils::SPrintf(str_temp, sizeof(str_temp), "%lu",
                   static_cast<unsigned long>(buffer_size)); // NOLINT(*)
    this->SetParam("num_pbuffer", str_temp);
    this->pred_buffer_size = buffer_size;
  }