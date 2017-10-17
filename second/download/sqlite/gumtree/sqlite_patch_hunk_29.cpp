 #ifndef SQLITE_OMIT_INTEGRITY_CHECK
 /*
 ** Append a message to the error message string.
 */
 static void checkAppendMsg(
   IntegrityCk *pCheck,
+  char *zMsg1,
   const char *zFormat,
   ...
 ){
   va_list ap;
   if( !pCheck->mxErr ) return;
   pCheck->mxErr--;
   pCheck->nErr++;
   va_start(ap, zFormat);
   if( pCheck->errMsg.nChar ){
     sqlite3StrAccumAppend(&pCheck->errMsg, "\n", 1);
   }
-  if( pCheck->zPfx ){
-    sqlite3XPrintf(&pCheck->errMsg, pCheck->zPfx, pCheck->v1, pCheck->v2);
+  if( zMsg1 ){
+    sqlite3StrAccumAppend(&pCheck->errMsg, zMsg1, -1);
   }
-  sqlite3VXPrintf(&pCheck->errMsg, zFormat, ap);
+  sqlite3VXPrintf(&pCheck->errMsg, 1, zFormat, ap);
   va_end(ap);
-  if( pCheck->errMsg.accError==STRACCUM_NOMEM ){
+  if( pCheck->errMsg.mallocFailed ){
     pCheck->mallocFailed = 1;
   }
 }
 #endif /* SQLITE_OMIT_INTEGRITY_CHECK */
 
 #ifndef SQLITE_OMIT_INTEGRITY_CHECK
-
-/*
-** Return non-zero if the bit in the IntegrityCk.aPgRef[] array that
-** corresponds to page iPg is already set.
-*/
-static int getPageReferenced(IntegrityCk *pCheck, Pgno iPg){
-  assert( iPg<=pCheck->nPage && sizeof(pCheck->aPgRef[0])==1 );
-  return (pCheck->aPgRef[iPg/8] & (1 << (iPg & 0x07)));
-}
-
-/*
-** Set the bit in the IntegrityCk.aPgRef[] array that corresponds to page iPg.
-*/
-static void setPageReferenced(IntegrityCk *pCheck, Pgno iPg){
-  assert( iPg<=pCheck->nPage && sizeof(pCheck->aPgRef[0])==1 );
-  pCheck->aPgRef[iPg/8] |= (1 << (iPg & 0x07));
-}
-
-
 /*
 ** Add 1 to the reference count for page iPage.  If this is the second
 ** reference to the page, add an error message to pCheck->zErrMsg.
-** Return 1 if there are 2 or more references to the page and 0 if
+** Return 1 if there are 2 ore more references to the page and 0 if
 ** if this is the first reference to the page.
 **
 ** Also check that the page number is in bounds.
 */
-static int checkRef(IntegrityCk *pCheck, Pgno iPage){
+static int checkRef(IntegrityCk *pCheck, Pgno iPage, char *zContext){
   if( iPage==0 ) return 1;
   if( iPage>pCheck->nPage ){
-    checkAppendMsg(pCheck, "invalid page number %d", iPage);
+    checkAppendMsg(pCheck, zContext, "invalid page number %d", iPage);
     return 1;
   }
-  if( getPageReferenced(pCheck, iPage) ){
-    checkAppendMsg(pCheck, "2nd reference to page %d", iPage);
+  if( pCheck->anRef[iPage]==1 ){
+    checkAppendMsg(pCheck, zContext, "2nd reference to page %d", iPage);
     return 1;
   }
-  setPageReferenced(pCheck, iPage);
-  return 0;
+  return  (pCheck->anRef[iPage]++)>1;
 }
 
 #ifndef SQLITE_OMIT_AUTOVACUUM
 /*
 ** Check that the entry in the pointer-map for page iChild maps to 
 ** page iParent, pointer type ptrType. If not, append an error message
 ** to pCheck.
 */
 static void checkPtrmap(
   IntegrityCk *pCheck,   /* Integrity check context */
   Pgno iChild,           /* Child page number */
   u8 eType,              /* Expected pointer map type */
-  Pgno iParent           /* Expected pointer map parent page number */
+  Pgno iParent,          /* Expected pointer map parent page number */
+  char *zContext         /* Context description (used for error msg) */
 ){
   int rc;
   u8 ePtrmapType;
   Pgno iPtrmapParent;
 
   rc = ptrmapGet(pCheck->pBt, iChild, &ePtrmapType, &iPtrmapParent);
   if( rc!=SQLITE_OK ){
     if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ) pCheck->mallocFailed = 1;
-    checkAppendMsg(pCheck, "Failed to read ptrmap key=%d", iChild);
+    checkAppendMsg(pCheck, zContext, "Failed to read ptrmap key=%d", iChild);
     return;
   }
 
   if( ePtrmapType!=eType || iPtrmapParent!=iParent ){
-    checkAppendMsg(pCheck,
+    checkAppendMsg(pCheck, zContext, 
       "Bad ptr map entry key=%d expected=(%d,%d) got=(%d,%d)", 
       iChild, eType, iParent, ePtrmapType, iPtrmapParent);
   }
 }
 #endif
 
