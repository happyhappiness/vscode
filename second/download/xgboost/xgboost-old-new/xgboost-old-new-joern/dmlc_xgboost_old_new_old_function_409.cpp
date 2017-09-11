inline void WriteBuffer(void) {
    SizeType start = 0;
    for (size_t i = 1; i < buffer_rptr.size(); ++i) {
      size_t rlen = buffer_rptr[i];
      buffer_rptr[i] = start;
      start += rlen;
    }
    for (size_t i = 0; i < buffer_temp.size(); ++i) {
      SizeType &rp = buffer_rptr[buffer_temp[i].first + 1];
      buffer_data[rp++] = buffer_temp[i].second;
    }
    // write out
    for (size_t i = 0; i < buffer_rptr.size(); ++i) {
      size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
      if (nelem != 0) {
        utils::Assert(saved_offset[i] < rptr[i+1], "data exceed bound");
        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + begin_data);
        fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
        saved_offset[i] += nelem;
      }
    }
  }