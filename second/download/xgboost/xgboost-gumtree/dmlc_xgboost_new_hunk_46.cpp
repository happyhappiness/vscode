     */
    inline void SetMerge(const Summary *begin,
                         const Summary *end) {
      CHECK(begin < end) << "can not set combine to empty instance";
      size_t len = end - begin;
      if (len == 1) {
        this->Reserve(begin[0].size);
