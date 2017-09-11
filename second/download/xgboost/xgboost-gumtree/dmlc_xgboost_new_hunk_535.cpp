      size_t nelem = buffer_rptr[i+1] - buffer_rptr[i];
      if (nelem != 0) {
        utils::Assert(saved_offset[i] < rptr[i+1], "data exceed bound");
        fo->Seek((rptr[i] + saved_offset[i]) * sizeof(IndexType) + begin_data);
        fo->Write(&buffer_data[0] + buffer_rptr[i], nelem * sizeof(IndexType));
        saved_offset[i] += nelem;
      }
