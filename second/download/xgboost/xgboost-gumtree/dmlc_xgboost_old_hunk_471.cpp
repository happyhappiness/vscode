        data[size++] = src.data[src.size - 1];
      }
    }
    inline void SetCombine(const Summary &sa,
                           const Summary &sb) {
      utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
