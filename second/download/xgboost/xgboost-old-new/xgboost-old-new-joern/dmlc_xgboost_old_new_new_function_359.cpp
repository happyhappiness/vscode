inline void CheckValid(void) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      utils::Assert(rmax >= rmin + wmin, "relation constraint");
    }