inline void CheckValid(RType eps = 0) const {
      CHECK(rmin >= 0 && rmax >= 0 && wmin >= 0) << "nonneg constraint";
      CHECK(rmax- rmin - wmin > -eps) <<  "relation constraint: min/max";
    }