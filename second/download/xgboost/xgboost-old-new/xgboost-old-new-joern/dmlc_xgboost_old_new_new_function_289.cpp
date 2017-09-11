inline void CheckSameAs(const Rec &b) {
    if (rmax != b.rmax || rmin != b.rmin || fabs(rsum - b.rsum) > 1e-6) {
      utils::Error("[%d] TestReducer check failure", sync::GetRank());
    }
  }