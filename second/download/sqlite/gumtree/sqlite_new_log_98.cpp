checkAppendMsg(&sCheck, 0, 
      "Outstanding page count goes from %d to %d during this analysis",
      nRef, sqlite3PagerRefcount(pBt->pPager)
    );