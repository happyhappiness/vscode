      buffer_data[rp++] = buffer_temp[i].second;
    }
    // write out
    for (size_t i = 0; i < buffer_rptr.size() - 1; ++i) {
      size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
      if (nelem != 0) {
        utils::Assert(saved_offset[i] + nelem <= rptr[i+1], "data exceed bound");
        fo->Seek(saved_offset[i] * sizeof(IndexType) + begin_data);
        fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
        saved_offset[i] += nelem;
      }
