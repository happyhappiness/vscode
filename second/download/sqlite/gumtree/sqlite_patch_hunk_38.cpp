     int s = (int)(x.s + 0.5);
     x.s = s;
   }
   x.tz = 0;
   x.validJD = 0;
   computeJD(&x);
-  t = (time_t)(x.iJD/1000 - 21086676*(i64)10000);
-  if( osLocaltime(&t, &sLocal) ){
-    sqlite3_result_error(pCtx, "local time unavailable", -1);
-    *pRc = SQLITE_ERROR;
-    return 0;
+  t = x.iJD/1000 - 21086676*(i64)10000;
+#ifdef HAVE_LOCALTIME_R
+  {
+    struct tm sLocal;
+    localtime_r(&t, &sLocal);
+    y.Y = sLocal.tm_year + 1900;
+    y.M = sLocal.tm_mon + 1;
+    y.D = sLocal.tm_mday;
+    y.h = sLocal.tm_hour;
+    y.m = sLocal.tm_min;
+    y.s = sLocal.tm_sec;
+  }
+#elif defined(HAVE_LOCALTIME_S)
+  {
+    struct tm sLocal;
+    localtime_s(&sLocal, &t);
+    y.Y = sLocal.tm_year + 1900;
+    y.M = sLocal.tm_mon + 1;
+    y.D = sLocal.tm_mday;
+    y.h = sLocal.tm_hour;
+    y.m = sLocal.tm_min;
+    y.s = sLocal.tm_sec;
+  }
+#else
+  {
+    struct tm *pTm;
+    sqlite3_mutex_enter(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER));
+    pTm = localtime(&t);
+    y.Y = pTm->tm_year + 1900;
+    y.M = pTm->tm_mon + 1;
+    y.D = pTm->tm_mday;
+    y.h = pTm->tm_hour;
+    y.m = pTm->tm_min;
+    y.s = pTm->tm_sec;
+    sqlite3_mutex_leave(sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MASTER));
   }
-  y.Y = sLocal.tm_year + 1900;
-  y.M = sLocal.tm_mon + 1;
-  y.D = sLocal.tm_mday;
-  y.h = sLocal.tm_hour;
-  y.m = sLocal.tm_min;
-  y.s = sLocal.tm_sec;
+#endif
   y.validYMD = 1;
   y.validHMS = 1;
   y.validJD = 0;
-  y.rawS = 0;
   y.validTZ = 0;
-  y.isError = 0;
   computeJD(&y);
-  *pRc = SQLITE_OK;
   return y.iJD - x.iJD;
 }
 #endif /* SQLITE_OMIT_LOCALTIME */
 
 /*
-** The following table defines various date transformations of the form
-**
-**            'NNN days'
-**
-** Where NNN is an arbitrary floating-point number and "days" can be one
-** of several units of time.
-*/
-static const struct {
-  u8 eType;           /* Transformation type code */
-  u8 nName;           /* Length of th name */
-  char *zName;        /* Name of the transformation */
-  double rLimit;      /* Maximum NNN value for this transform */
-  double rXform;      /* Constant used for this transform */
-} aXformType[] = {
-  { 0, 6, "second", 464269060800.0, 86400000.0/(24.0*60.0*60.0) },
-  { 0, 6, "minute", 7737817680.0,   86400000.0/(24.0*60.0)      },
-  { 0, 4, "hour",   128963628.0,    86400000.0/24.0             },
-  { 0, 3, "day",    5373485.0,      86400000.0                  },
-  { 1, 5, "month",  176546.0,       30.0*86400000.0             },
-  { 2, 4, "year",   14713.0,        365.0*86400000.0            },
-};
-
-/*
 ** Process a modifier to a date-time stamp.  The modifiers are
 ** as follows:
 **
 **     NNN days
 **     NNN hours
 **     NNN minutes
