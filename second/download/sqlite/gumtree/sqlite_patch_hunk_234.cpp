 
 /*
 ** Return the number of bytes that will be needed to store the given
 ** 64-bit integer.
 */
 int sqlite3VarintLen(u64 v){
-  int i = 0;
-  do{
-    i++;
-    v >>= 7;
-  }while( v!=0 && ALWAYS(i<9) );
+  int i;
+  for(i=1; (v >>= 7)!=0; i++){ assert( i<10 ); }
   return i;
 }
 
 
 /*
 ** Read or write a four-byte big-endian integer value.
 */
 u32 sqlite3Get4byte(const u8 *p){
-  return (p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3];
+#if SQLITE_BYTEORDER==4321
+  u32 x;
+  memcpy(&x,p,4);
+  return x;
+#elif SQLITE_BYTEORDER==1234 && GCC_VERSION>=4003000
+  u32 x;
+  memcpy(&x,p,4);
+  return __builtin_bswap32(x);
+#elif SQLITE_BYTEORDER==1234 && MSVC_VERSION>=1300
+  u32 x;
+  memcpy(&x,p,4);
+  return _byteswap_ulong(x);
+#else
+  testcase( p[0]&0x80 );
+  return ((unsigned)p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3];
+#endif
 }
 void sqlite3Put4byte(unsigned char *p, u32 v){
+#if SQLITE_BYTEORDER==4321
+  memcpy(p,&v,4);
+#elif SQLITE_BYTEORDER==1234 && GCC_VERSION>=4003000
+  u32 x = __builtin_bswap32(v);
+  memcpy(p,&x,4);
+#elif SQLITE_BYTEORDER==1234 && MSVC_VERSION>=1300
+  u32 x = _byteswap_ulong(v);
+  memcpy(p,&x,4);
+#else
   p[0] = (u8)(v>>24);
   p[1] = (u8)(v>>16);
   p[2] = (u8)(v>>8);
   p[3] = (u8)v;
+#endif
 }
 
 
 
-#if !defined(SQLITE_OMIT_BLOB_LITERAL) || defined(SQLITE_HAS_CODEC)
 /*
 ** Translate a single byte of Hex into an integer.
-** This routinen only works if h really is a valid hexadecimal
+** This routine only works if h really is a valid hexadecimal
 ** character:  0..9a..fA..F
 */
-static u8 hexToInt(int h){
+u8 sqlite3HexToInt(int h){
   assert( (h>='0' && h<='9') ||  (h>='a' && h<='f') ||  (h>='A' && h<='F') );
 #ifdef SQLITE_ASCII
   h += 9*(1&(h>>6));
 #endif
 #ifdef SQLITE_EBCDIC
   h += 9*(1&~(h>>4));
 #endif
   return (u8)(h & 0xf);
 }
-#endif /* !SQLITE_OMIT_BLOB_LITERAL || SQLITE_HAS_CODEC */
 
 #if !defined(SQLITE_OMIT_BLOB_LITERAL) || defined(SQLITE_HAS_CODEC)
 /*
 ** Convert a BLOB literal of the form "x'hhhhhh'" into its binary
 ** value.  Return a pointer to its binary value.  Space to hold the
 ** binary value has been obtained from malloc and must be freed by
 ** the calling routine.
 */
 void *sqlite3HexToBlob(sqlite3 *db, const char *z, int n){
   char *zBlob;
   int i;
 
-  zBlob = (char *)sqlite3DbMallocRaw(db, n/2 + 1);
+  zBlob = (char *)sqlite3DbMallocRawNN(db, n/2 + 1);
   n--;
   if( zBlob ){
     for(i=0; i<n; i+=2){
-      zBlob[i/2] = (hexToInt(z[i])<<4) | hexToInt(z[i+1]);
+      zBlob[i/2] = (sqlite3HexToInt(z[i])<<4) | sqlite3HexToInt(z[i+1]);
     }
     zBlob[i/2] = 0;
   }
   return zBlob;
 }
 #endif /* !SQLITE_OMIT_BLOB_LITERAL || SQLITE_HAS_CODEC */
 
-
-/*
-** Change the sqlite.magic from SQLITE_MAGIC_OPEN to SQLITE_MAGIC_BUSY.
-** Return an error (non-zero) if the magic was not SQLITE_MAGIC_OPEN
-** when this routine is called.
-**
-** This routine is called when entering an SQLite API.  The SQLITE_MAGIC_OPEN
-** value indicates that the database connection passed into the API is
-** open and is not being used by another thread.  By changing the value
-** to SQLITE_MAGIC_BUSY we indicate that the connection is in use.
-** sqlite3SafetyOff() below will change the value back to SQLITE_MAGIC_OPEN
-** when the API exits. 
-**
-** This routine is a attempt to detect if two threads use the
-** same sqlite* pointer at the same time.  There is a race 
-** condition so it is possible that the error is not detected.
-** But usually the problem will be seen.  The result will be an
-** error which can be used to debug the application that is
-** using SQLite incorrectly.
-**
-** Ticket #202:  If db->magic is not a valid open value, take care not
-** to modify the db structure at all.  It could be that db is a stale
-** pointer.  In other words, it could be that there has been a prior
-** call to sqlite3_close(db) and db has been deallocated.  And we do
-** not want to write into deallocated memory.
-*/
-#ifdef SQLITE_DEBUG
-int sqlite3SafetyOn(sqlite3 *db){
-  if( db->magic==SQLITE_MAGIC_OPEN ){
-    db->magic = SQLITE_MAGIC_BUSY;
-    assert( sqlite3_mutex_held(db->mutex) );
-    return 0;
-  }else if( db->magic==SQLITE_MAGIC_BUSY ){
-    db->magic = SQLITE_MAGIC_ERROR;
-    db->u1.isInterrupted = 1;
-  }
-  return 1;
-}
-#endif
-
 /*
-** Change the magic from SQLITE_MAGIC_BUSY to SQLITE_MAGIC_OPEN.
-** Return an error (non-zero) if the magic was not SQLITE_MAGIC_BUSY
-** when this routine is called.
-*/
-#ifdef SQLITE_DEBUG
-int sqlite3SafetyOff(sqlite3 *db){
-  if( db->magic==SQLITE_MAGIC_BUSY ){
-    db->magic = SQLITE_MAGIC_OPEN;
-    assert( sqlite3_mutex_held(db->mutex) );
-    return 0;
-  }else{
-    db->magic = SQLITE_MAGIC_ERROR;
-    db->u1.isInterrupted = 1;
-    return 1;
-  }
+** Log an error that is an API call on a connection pointer that should
+** not have been used.  The "type" of connection pointer is given as the
+** argument.  The zType is a word like "NULL" or "closed" or "invalid".
+*/
+static void logBadConnection(const char *zType){
+  sqlite3_log(SQLITE_MISUSE, 
+     "API call with %s database connection pointer",
+     zType
+  );
 }
-#endif
 
 /*
 ** Check to make sure we have a valid db pointer.  This test is not
 ** foolproof but it does provide some measure of protection against
 ** misuse of the interface such as passing in db pointers that are
 ** NULL or which have been previously closed.  If this routine returns
