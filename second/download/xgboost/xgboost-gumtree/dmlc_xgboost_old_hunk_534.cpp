      utils::Assert(saved_offset[i] == rptr[i+1], "some block not write out");
    }
  }
  
 protected:
  inline void WriteBuffer(void) {
    SizeType start = 0;
