inline void Finalize(void) {
    this->WriteBuffer();
    for (size_t i = 0; i < saved_offset.size(); ++i) {
      utils::Assert(saved_offset[i] == rptr[i+1], "some block not write out");
    }
  }