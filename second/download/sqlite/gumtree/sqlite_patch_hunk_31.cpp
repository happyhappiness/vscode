   int *aRoot,   /* An array of root pages numbers for individual trees */
   int nRoot,    /* Number of entries in aRoot[] */
   int mxErr,    /* Stop reporting errors after this many */
   int *pnErr    /* Write number of errors seen to this variable */
 ){
   Pgno i;
+  int nRef;
   IntegrityCk sCheck;
   BtShared *pBt = p->pBt;
-  int savedDbFlags = pBt->db->flags;
   char zErr[100];
-  VVA_ONLY( int nRef );
 
   sqlite3BtreeEnter(p);
-  assert( p->inTrans>TRANS_NONE && pBt->inTransaction>TRANS_NONE );
-  VVA_ONLY( nRef = sqlite3PagerRefcount(pBt->pPager) );
-  assert( nRef>=0 );
+  nRef = sqlite3PagerRefcount(pBt->pPager);
+  if( lockBtreeWithRetry(p)!=SQLITE_OK ){
+    *pnErr = 1;
+    sqlite3BtreeLeave(p);
+    return sqlite3DbStrDup(0, "cannot acquire a read lock on the database");
+  }
   sCheck.pBt = pBt;
   sCheck.pPager = pBt->pPager;
-  sCheck.nPage = btreePagecount(sCheck.pBt);
+  sCheck.nPage = pagerPagecount(sCheck.pBt);
   sCheck.mxErr = mxErr;
   sCheck.nErr = 0;
   sCheck.mallocFailed = 0;
-  sCheck.zPfx = 0;
-  sCheck.v1 = 0;
-  sCheck.v2 = 0;
-  sCheck.aPgRef = 0;
-  sCheck.heap = 0;
-  sqlite3StrAccumInit(&sCheck.errMsg, 0, zErr, sizeof(zErr), SQLITE_MAX_LENGTH);
-  sCheck.errMsg.printfFlags = SQLITE_PRINTF_INTERNAL;
+  *pnErr = 0;
   if( sCheck.nPage==0 ){
-    goto integrity_ck_cleanup;
+    unlockBtreeIfUnused(pBt);
+    sqlite3BtreeLeave(p);
+    return 0;
   }
-
-  sCheck.aPgRef = sqlite3MallocZero((sCheck.nPage / 8)+ 1);
-  if( !sCheck.aPgRef ){
-    sCheck.mallocFailed = 1;
-    goto integrity_ck_cleanup;
-  }
-  sCheck.heap = (u32*)sqlite3PageMalloc( pBt->pageSize );
-  if( sCheck.heap==0 ){
-    sCheck.mallocFailed = 1;
-    goto integrity_ck_cleanup;
+  sCheck.anRef = sqlite3Malloc( (sCheck.nPage+1)*sizeof(sCheck.anRef[0]) );
+  if( !sCheck.anRef ){
+    unlockBtreeIfUnused(pBt);
+    *pnErr = 1;
+    sqlite3BtreeLeave(p);
+    return 0;
   }
-
+  for(i=0; i<=sCheck.nPage; i++){ sCheck.anRef[i] = 0; }
   i = PENDING_BYTE_PAGE(pBt);
-  if( i<=sCheck.nPage ) setPageReferenced(&sCheck, i);
+  if( i<=sCheck.nPage ){
+    sCheck.anRef[i] = 1;
+  }
+  sqlite3StrAccumInit(&sCheck.errMsg, zErr, sizeof(zErr), 20000);
 
   /* Check the integrity of the freelist
   */
-  sCheck.zPfx = "Main freelist: ";
   checkList(&sCheck, 1, get4byte(&pBt->pPage1->aData[32]),
-            get4byte(&pBt->pPage1->aData[36]));
-  sCheck.zPfx = 0;
+            get4byte(&pBt->pPage1->aData[36]), "Main freelist: ");
 
   /* Check all the tables.
   */
-  testcase( pBt->db->flags & SQLITE_CellSizeCk );
-  pBt->db->flags &= ~SQLITE_CellSizeCk;
   for(i=0; (int)i<nRoot && sCheck.mxErr; i++){
-    i64 notUsed;
     if( aRoot[i]==0 ) continue;
 #ifndef SQLITE_OMIT_AUTOVACUUM
     if( pBt->autoVacuum && aRoot[i]>1 ){
-      checkPtrmap(&sCheck, aRoot[i], PTRMAP_ROOTPAGE, 0);
+      checkPtrmap(&sCheck, aRoot[i], PTRMAP_ROOTPAGE, 0, 0);
     }
 #endif
-    checkTreePage(&sCheck, aRoot[i], &notUsed, LARGEST_INT64);
+    checkTreePage(&sCheck, aRoot[i], "List of tree roots: ");
   }
-  pBt->db->flags = savedDbFlags;
 
   /* Make sure every page in the file is referenced
   */
   for(i=1; i<=sCheck.nPage && sCheck.mxErr; i++){
 #ifdef SQLITE_OMIT_AUTOVACUUM
-    if( getPageReferenced(&sCheck, i)==0 ){
-      checkAppendMsg(&sCheck, "Page %d is never used", i);
+    if( sCheck.anRef[i]==0 ){
+      checkAppendMsg(&sCheck, 0, "Page %d is never used", i);
     }
 #else
     /* If the database supports auto-vacuum, make sure no tables contain
     ** references to pointer-map pages.
     */
-    if( getPageReferenced(&sCheck, i)==0 && 
+    if( sCheck.anRef[i]==0 && 
        (PTRMAP_PAGENO(pBt, i)!=i || !pBt->autoVacuum) ){
-      checkAppendMsg(&sCheck, "Page %d is never used", i);
+      checkAppendMsg(&sCheck, 0, "Page %d is never used", i);
     }
-    if( getPageReferenced(&sCheck, i)!=0 && 
+    if( sCheck.anRef[i]!=0 && 
        (PTRMAP_PAGENO(pBt, i)==i && pBt->autoVacuum) ){
-      checkAppendMsg(&sCheck, "Pointer map page %d is referenced", i);
+      checkAppendMsg(&sCheck, 0, "Pointer map page %d is referenced", i);
     }
 #endif
   }
 
+  /* Make sure this analysis did not leave any unref() pages.
+  ** This is an internal consistency check; an integrity check
+  ** of the integrity check.
+  */
+  unlockBtreeIfUnused(pBt);
+  if( NEVER(nRef != sqlite3PagerRefcount(pBt->pPager)) ){
+    checkAppendMsg(&sCheck, 0, 
+      "Outstanding page count goes from %d to %d during this analysis",
+      nRef, sqlite3PagerRefcount(pBt->pPager)
+    );
+  }
+
   /* Clean  up and report errors.
   */
-integrity_ck_cleanup:
-  sqlite3PageFree(sCheck.heap);
-  sqlite3_free(sCheck.aPgRef);
+  sqlite3BtreeLeave(p);
+  sqlite3_free(sCheck.anRef);
   if( sCheck.mallocFailed ){
     sqlite3StrAccumReset(&sCheck.errMsg);
-    sCheck.nErr++;
+    *pnErr = sCheck.nErr+1;
+    return 0;
   }
   *pnErr = sCheck.nErr;
   if( sCheck.nErr==0 ) sqlite3StrAccumReset(&sCheck.errMsg);
-  /* Make sure this analysis did not leave any unref() pages. */
-  assert( nRef==sqlite3PagerRefcount(pBt->pPager) );
-  sqlite3BtreeLeave(p);
   return sqlite3StrAccumFinish(&sCheck.errMsg);
 }
 #endif /* SQLITE_OMIT_INTEGRITY_CHECK */
 
 /*
-** Return the full pathname of the underlying database file.  Return
-** an empty string if the database is in-memory or a TEMP database.
+** Return the full pathname of the underlying database file.
 **
 ** The pager filename is invariant as long as the pager is
 ** open so it is safe to access without the BtShared mutex.
 */
 const char *sqlite3BtreeGetFilename(Btree *p){
   assert( p->pBt->pPager!=0 );
-  return sqlite3PagerFilename(p->pBt->pPager, 1);
+  return sqlite3PagerFilename(p->pBt->pPager);
 }
 
 /*
 ** Return the pathname of the journal file for this database. The return
 ** value of this routine is the same regardless of whether the journal file
 ** has been created or not.
