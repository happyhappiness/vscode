inline void CheckValid(RType eps = 0) const {
      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
      if (!(rmax - rmin - wmin > -eps)) {
        printf("rmax=%f, rmin=%f, wmin=%f, plus=%f, v=%f\n", 
               rmax, rmin, wmin, rmin+wmin, value);
      }
      utils::Assert(rmax- rmin - wmin > -eps  , "relation constraint: min/max");
    }