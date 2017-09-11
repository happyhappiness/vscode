        data[size++] = src.data[src.size - 1];
      }
    }
    /*! 
     * \brief set current summary to be merged summary of sa and sb
     * \param sa first input summary to be merged
     * \param sb second input summar to be merged
     */
    inline void SetCombine(const Summary &sa,
                           const Summary &sb) {
      utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
