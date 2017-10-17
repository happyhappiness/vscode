    int s = (int)(x.s + 0.5);
    x.s = s;
  }
  x.tz = 0;
  x.validJD = 0;
  computeJD(&x);
  t = x.iJD/1000 - 21086676*(i64)10000;
#ifdef HAVE_LOCALTIME_R
  {
    struct tm sLocal;
    localtime_r(&t, &sLocal);
    y.Y = sLocal.tm_year + 1900;
    y.M = sLocal.tm_mon + 1;
    y.D = sLocal.tm_mday;
    y.h = sLocal.tm_hour;
    y.m = sLocal.tm_min;
    y.s = sLocal.tm_sec;
  }
#elif defined(HAVE_LOCALTIME_S)
  {
    struct tm sLocal;
    localtime_s(&sLocal, &t);
    y.Y = sLocal.tm_year + 1900;
    y.M = sLocal.tm_mon + 1;
    y.D = sLocal.tm_mday;
    y.h = sLocal.tm_hour;
    y.m = sLocal.tm_min;
    y.s = sLocal.tm_sec;
  }
#else
  {
    struct tm *pTm;
    sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER));
    pTm = localtime(&t);
    y.Y = pTm->tm_year + 1900;
    y.M = pTm->tm_mon + 1;
    y.D = pTm->tm_mday;
    y.h = pTm->tm_hour;
    y.m = pTm->tm_min;
    y.s = pTm->tm_sec;
    sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER));
  }
#endif
  y.validYMD = 1;
  y.validHMS = 1;
  y.validJD = 0;
  y.validTZ = 0;
  computeJD(&y);
  return y.iJD - x.iJD;
}
#endif /* SQLITE_OMIT_LOCALTIME */

/*
** Process a modifier to a date-time stamp.  The modifiers are
** as follows:
**
**     NNN days
**     NNN hours
**     NNN minutes
