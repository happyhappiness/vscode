  }
  inline void SetCombine(const GKSummary &sa,
                         const GKSummary &sb) {
    utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
    const Entry *a = sa.data, *a_end = sa.data + sa.size;
    const Entry *b = sb.data, *b_end = sb.data + sb.size;
