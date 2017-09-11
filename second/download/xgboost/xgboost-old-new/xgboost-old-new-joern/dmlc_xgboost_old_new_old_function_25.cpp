inline void CheckValid(RType eps = 0) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      utils::Assert(rmax- rmin - wmin > -eps, "relation constraint: min/max");
    }