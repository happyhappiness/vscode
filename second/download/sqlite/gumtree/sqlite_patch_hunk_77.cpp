   z = sqlite3VMPrintf(db, zFormat, ap);
   va_end(ap);
   return z;
 }
 
 /*
+** Like sqlite3MPrintf(), but call sqlite3DbFree() on zStr after formatting
+** the string and before returnning.  This routine is intended to be used
+** to modify an existing string.  For example:
+**
+**       x = sqlite3MPrintf(db, x, "prefix %s suffix", x);
+**
+*/
+char *sqlite3MAppendf(sqlite3 *db, char *zStr, const char *zFormat, ...){
+  va_list ap;
+  char *z;
+  va_start(ap, zFormat);
+  z = sqlite3VMPrintf(db, zFormat, ap);
+  va_end(ap);
+  sqlite3DbFree(db, zStr);
+  return z;
+}
+
+/*
 ** Print into memory obtained from sqlite3_malloc().  Omit the internal
 ** %-conversion extensions.
 */
 char *sqlite3_vmprintf(const char *zFormat, va_list ap){
   char *z;
   char zBase[SQLITE_PRINT_BUF_SIZE];
   StrAccum acc;
-
-#ifdef SQLITE_ENABLE_API_ARMOR  
-  if( zFormat==0 ){
-    (void)SQLITE_MISUSE_BKPT;
-    return 0;
-  }
-#endif
 #ifndef SQLITE_OMIT_AUTOINIT
   if( sqlite3_initialize() ) return 0;
 #endif
-  sqlite3StrAccumInit(&acc, 0, zBase, sizeof(zBase), SQLITE_MAX_LENGTH);
-  sqlite3VXPrintf(&acc, zFormat, ap);
+  sqlite3StrAccumInit(&acc, zBase, sizeof(zBase), SQLITE_MAX_LENGTH);
+  sqlite3VXPrintf(&acc, 0, zFormat, ap);
   z = sqlite3StrAccumFinish(&acc);
   return z;
 }
 
 /*
 ** Print into memory obtained from sqlite3_malloc()().  Omit the internal
