      utils::Assert(saved_offset[i] == rptr[i+1], "some block not write out");
    }
  }
  /*! \brief content must be in wb+ */
  template<typename Comparator>
  inline void SortRows(Comparator comp, size_t step) {
    for (size_t i = 0; i < rptr.size() - 1; i += step) {
      bst_omp_uint begin = static_cast<bst_omp_uint>(i);
      bst_omp_uint end = static_cast<bst_omp_uint>(std::min(rptr.size(), i + step));
      if (rptr[end] != rptr[begin]) {
        fo->Seek(begin_data + rptr[begin] * sizeof(IndexType));
        buffer_data.resize(rptr[end] - rptr[begin]);
        fo->Read(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
        // do parallel sorting
        #pragma omp parallel for schedule(static)
        for (bst_omp_uint j = begin; j < end; ++j){
          std::sort(&buffer_data[0] + rptr[j] - rptr[begin],
                    &buffer_data[0] + rptr[j+1] - rptr[begin],
                    comp);
        }
        fo->Seek(begin_data + rptr[begin] * sizeof(IndexType));
        fo->Write(BeginPtr(buffer_data), (rptr[end] - rptr[begin]) * sizeof(IndexType));
      }
    }
  }
 protected:
  inline void WriteBuffer(void) {
    SizeType start = 0;
