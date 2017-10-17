 ** use.  sqlite3SafetyCheckSickOrOk() allows a db pointer that failed to
 ** open properly and is not fit for general use but which can be
 ** used as an argument to sqlite3_errmsg() or sqlite3_close().
 */
 int sqlite3SafetyCheckOk(sqlite3 *db){
   u32 magic;
-  if( db==0 ) return 0;
+  if( db==0 ){
+    logBadConnection("NULL");
+    return 0;
+  }
   magic = db->magic;
-  if( magic!=SQLITE_MAGIC_OPEN 
-#ifdef SQLITE_DEBUG
-     && magic!=SQLITE_MAGIC_BUSY
-#endif
-  ){
+  if( magic!=SQLITE_MAGIC_OPEN ){
+    if( sqlite3SafetyCheckSickOrOk(db) ){
+      testcase( sqlite3GlobalConfig.xLog!=0 );
+      logBadConnection("unopened");
+    }
     return 0;
   }else{
     return 1;
   }
 }
 int sqlite3SafetyCheckSickOrOk(sqlite3 *db){
   u32 magic;
   magic = db->magic;
   if( magic!=SQLITE_MAGIC_SICK &&
       magic!=SQLITE_MAGIC_OPEN &&
-      magic!=SQLITE_MAGIC_BUSY ) return 0;
-  return 1;
+      magic!=SQLITE_MAGIC_BUSY ){
+    testcase( sqlite3GlobalConfig.xLog!=0 );
+    logBadConnection("invalid");
+    return 0;
+  }else{
+    return 1;
+  }
+}
+
+/*
+** Attempt to add, substract, or multiply the 64-bit signed value iB against
+** the other 64-bit signed integer at *pA and store the result in *pA.
+** Return 0 on success.  Or if the operation would have resulted in an
+** overflow, leave *pA unchanged and return 1.
+*/
+int sqlite3AddInt64(i64 *pA, i64 iB){
+#if GCC_VERSION>=5004000 && !defined(__INTEL_COMPILER)
+  return __builtin_add_overflow(*pA, iB, pA);
+#else
+  i64 iA = *pA;
+  testcase( iA==0 ); testcase( iA==1 );
+  testcase( iB==-1 ); testcase( iB==0 );
+  if( iB>=0 ){
+    testcase( iA>0 && LARGEST_INT64 - iA == iB );
+    testcase( iA>0 && LARGEST_INT64 - iA == iB - 1 );
+    if( iA>0 && LARGEST_INT64 - iA < iB ) return 1;
+  }else{
+    testcase( iA<0 && -(iA + LARGEST_INT64) == iB + 1 );
+    testcase( iA<0 && -(iA + LARGEST_INT64) == iB + 2 );
+    if( iA<0 && -(iA + LARGEST_INT64) > iB + 1 ) return 1;
+  }
+  *pA += iB;
+  return 0; 
+#endif
+}
+int sqlite3SubInt64(i64 *pA, i64 iB){
+#if GCC_VERSION>=5004000 && !defined(__INTEL_COMPILER)
+  return __builtin_sub_overflow(*pA, iB, pA);
+#else
+  testcase( iB==SMALLEST_INT64+1 );
+  if( iB==SMALLEST_INT64 ){
+    testcase( (*pA)==(-1) ); testcase( (*pA)==0 );
+    if( (*pA)>=0 ) return 1;
+    *pA -= iB;
+    return 0;
+  }else{
+    return sqlite3AddInt64(pA, -iB);
+  }
+#endif
+}
+int sqlite3MulInt64(i64 *pA, i64 iB){
+#if GCC_VERSION>=5004000 && !defined(__INTEL_COMPILER)
+  return __builtin_mul_overflow(*pA, iB, pA);
+#else
+  i64 iA = *pA;
+  if( iB>0 ){
+    if( iA>LARGEST_INT64/iB ) return 1;
+    if( iA<SMALLEST_INT64/iB ) return 1;
+  }else if( iB<0 ){
+    if( iA>0 ){
+      if( iB<SMALLEST_INT64/iA ) return 1;
+    }else if( iA<0 ){
+      if( iB==SMALLEST_INT64 ) return 1;
+      if( iA==SMALLEST_INT64 ) return 1;
+      if( -iA>LARGEST_INT64/-iB ) return 1;
+    }
+  }
+  *pA = iA*iB;
+  return 0;
+#endif
+}
+
+/*
+** Compute the absolute value of a 32-bit signed integer, of possible.  Or 
+** if the integer has a value of -2147483648, return +2147483647
+*/
+int sqlite3AbsInt32(int x){
+  if( x>=0 ) return x;
+  if( x==(int)0x80000000 ) return 0x7fffffff;
+  return -x;
+}
+
+#ifdef SQLITE_ENABLE_8_3_NAMES
+/*
+** If SQLITE_ENABLE_8_3_NAMES is set at compile-time and if the database
+** filename in zBaseFilename is a URI with the "8_3_names=1" parameter and
+** if filename in z[] has a suffix (a.k.a. "extension") that is longer than
+** three characters, then shorten the suffix on z[] to be the last three
+** characters of the original suffix.
+**
+** If SQLITE_ENABLE_8_3_NAMES is set to 2 at compile-time, then always
+** do the suffix shortening regardless of URI parameter.
+**
+** Examples:
+**
+**     test.db-journal    =>   test.nal
+**     test.db-wal        =>   test.wal
+**     test.db-shm        =>   test.shm
+**     test.db-mj7f3319fa =>   test.9fa
+*/
+void sqlite3FileSuffix3(const char *zBaseFilename, char *z){
+#if SQLITE_ENABLE_8_3_NAMES<2
+  if( sqlite3_uri_boolean(zBaseFilename, "8_3_names", 0) )
+#endif
+  {
+    int i, sz;
+    sz = sqlite3Strlen30(z);
+    for(i=sz-1; i>0 && z[i]!='/' && z[i]!='.'; i--){}
+    if( z[i]=='.' && ALWAYS(sz>i+4) ) memmove(&z[i+1], &z[sz-3], 4);
+  }
+}
+#endif
+
+/* 
+** Find (an approximate) sum of two LogEst values.  This computation is
+** not a simple "+" operator because LogEst is stored as a logarithmic
+** value.
+** 
+*/
+LogEst sqlite3LogEstAdd(LogEst a, LogEst b){
+  static const unsigned char x[] = {
+     10, 10,                         /* 0,1 */
+      9, 9,                          /* 2,3 */
+      8, 8,                          /* 4,5 */
+      7, 7, 7,                       /* 6,7,8 */
+      6, 6, 6,                       /* 9,10,11 */
+      5, 5, 5,                       /* 12-14 */
+      4, 4, 4, 4,                    /* 15-18 */
+      3, 3, 3, 3, 3, 3,              /* 19-24 */
+      2, 2, 2, 2, 2, 2, 2,           /* 25-31 */
+  };
+  if( a>=b ){
+    if( a>b+49 ) return a;
+    if( a>b+31 ) return a+1;
+    return a+x[a-b];
+  }else{
+    if( b>a+49 ) return b;
+    if( b>a+31 ) return b+1;
+    return b+x[b-a];
+  }
+}
+
+/*
+** Convert an integer into a LogEst.  In other words, compute an
+** approximation for 10*log2(x).
+*/
+LogEst sqlite3LogEst(u64 x){
+  static LogEst a[] = { 0, 2, 3, 5, 6, 7, 8, 9 };
+  LogEst y = 40;
+  if( x<8 ){
+    if( x<2 ) return 0;
+    while( x<8 ){  y -= 10; x <<= 1; }
+  }else{
+#if GCC_VERSION>=5004000
+    int i = 60 - __builtin_clzll(x);
+    y += i*10;
+    x >>= i;
+#else
+    while( x>255 ){ y += 40; x >>= 4; }  /*OPTIMIZATION-IF-TRUE*/
+    while( x>15 ){  y += 10; x >>= 1; }
+#endif
+  }
+  return a[x&7] + y - 10;
+}
+
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+/*
+** Convert a double into a LogEst
+** In other words, compute an approximation for 10*log2(x).
+*/
+LogEst sqlite3LogEstFromDouble(double x){
+  u64 a;
+  LogEst e;
+  assert( sizeof(x)==8 && sizeof(a)==8 );
+  if( x<=1 ) return 0;
+  if( x<=2000000000 ) return sqlite3LogEst((u64)x);
+  memcpy(&a, &x, 8);
+  e = (a>>52) - 1022;
+  return e*10;
+}
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
+
+#if defined(SQLITE_ENABLE_STMT_SCANSTATUS) || \
+    defined(SQLITE_ENABLE_STAT3_OR_STAT4) || \
+    defined(SQLITE_EXPLAIN_ESTIMATED_ROWS)
+/*
+** Convert a LogEst into an integer.
+**
+** Note that this routine is only used when one or more of various
+** non-standard compile-time options is enabled.
+*/
+u64 sqlite3LogEstToInt(LogEst x){
+  u64 n;
+  n = x%10;
+  x /= 10;
+  if( n>=5 ) n -= 2;
+  else if( n>=1 ) n -= 1;
+#if defined(SQLITE_ENABLE_STMT_SCANSTATUS) || \
+    defined(SQLITE_EXPLAIN_ESTIMATED_ROWS)
+  if( x>60 ) return (u64)LARGEST_INT64;
+#else
+  /* If only SQLITE_ENABLE_STAT3_OR_STAT4 is on, then the largest input
+  ** possible to this routine is 310, resulting in a maximum x of 31 */
+  assert( x<=60 );
+#endif
+  return x>=3 ? (n+8)<<(x-3) : (n+8)>>(3-x);
+}
+#endif /* defined SCANSTAT or STAT4 or ESTIMATED_ROWS */
+
+/*
+** Add a new name/number pair to a VList.  This might require that the
+** VList object be reallocated, so return the new VList.  If an OOM
+** error occurs, the original VList returned and the
+** db->mallocFailed flag is set.
+**
+** A VList is really just an array of integers.  To destroy a VList,
+** simply pass it to sqlite3DbFree().
+**
+** The first integer is the number of integers allocated for the whole
+** VList.  The second integer is the number of integers actually used.
+** Each name/number pair is encoded by subsequent groups of 3 or more
+** integers.
+**
+** Each name/number pair starts with two integers which are the numeric
+** value for the pair and the size of the name/number pair, respectively.
+** The text name overlays one or more following integers.  The text name
+** is always zero-terminated.
+**
+** Conceptually:
+**
+**    struct VList {
+**      int nAlloc;   // Number of allocated slots 
+**      int nUsed;    // Number of used slots 
+**      struct VListEntry {
+**        int iValue;    // Value for this entry
+**        int nSlot;     // Slots used by this entry
+**        // ... variable name goes here
+**      } a[0];
+**    }
+**
+** During code generation, pointers to the variable names within the
+** VList are taken.  When that happens, nAlloc is set to zero as an 
+** indication that the VList may never again be enlarged, since the
+** accompanying realloc() would invalidate the pointers.
+*/
+VList *sqlite3VListAdd(
+  sqlite3 *db,           /* The database connection used for malloc() */
+  VList *pIn,            /* The input VList.  Might be NULL */
+  const char *zName,     /* Name of symbol to add */
+  int nName,             /* Bytes of text in zName */
+  int iVal               /* Value to associate with zName */
+){
+  int nInt;              /* number of sizeof(int) objects needed for zName */
+  char *z;               /* Pointer to where zName will be stored */
+  int i;                 /* Index in pIn[] where zName is stored */
+
+  nInt = nName/4 + 3;
+  assert( pIn==0 || pIn[0]>=3 );  /* Verify ok to add new elements */
+  if( pIn==0 || pIn[1]+nInt > pIn[0] ){
+    /* Enlarge the allocation */
+    int nAlloc = (pIn ? pIn[0]*2 : 10) + nInt;
+    VList *pOut = sqlite3DbRealloc(db, pIn, nAlloc*sizeof(int));
+    if( pOut==0 ) return pIn;
+    if( pIn==0 ) pOut[1] = 2;
+    pIn = pOut;
+    pIn[0] = nAlloc;
+  }
+  i = pIn[1];
+  pIn[i] = iVal;
+  pIn[i+1] = nInt;
+  z = (char*)&pIn[i+2];
+  pIn[1] = i+nInt;
+  assert( pIn[1]<=pIn[0] );
+  memcpy(z, zName, nName);
+  z[nName] = 0;
+  return pIn;
+}
+
+/*
+** Return a pointer to the name of a variable in the given VList that
+** has the value iVal.  Or return a NULL if there is no such variable in
+** the list
+*/
+const char *sqlite3VListNumToName(VList *pIn, int iVal){
+  int i, mx;
+  if( pIn==0 ) return 0;
+  mx = pIn[1];
+  i = 2;
+  do{
+    if( pIn[i]==iVal ) return (char*)&pIn[i+2];
+    i += pIn[i+1];
+  }while( i<mx );
+  return 0;
+}
+
+/*
+** Return the number of the variable named zName, if it is in VList.
+** or return 0 if there is no such variable.
+*/
+int sqlite3VListNameToNum(VList *pIn, const char *zName, int nName){
+  int i, mx;
+  if( pIn==0 ) return 0;
+  mx = pIn[1];
+  i = 2;
+  do{
+    const char *z = (const char*)&pIn[i+2];
+    if( strncmp(z,zName,nName)==0 && z[nName]==0 ) return pIn[i];
+    i += pIn[i+1];
+  }while( i<mx );
+  return 0;
 }
