  int *aRoot,   /* An array of root pages numbers for individual trees */
  int nRoot,    /* Number of entries in aRoot[] */
  int mxErr,    /* Stop reporting errors after this many */
  int *pnErr    /* Write number of errors seen to this variable */
){
  Pgno i;
  int nRef;
  IntegrityCk sCheck;
  BtShared *pBt = p->pBt;
  char zErr[100];

  sqlite3BtreeEnter(p);
  nRef = sqlite3PagerRefcount(pBt->pPager);
  if( lockBtreeWithRetry(p)!=SQLITE_OK ){
    *pnErr = 1;
    sqlite3BtreeLeave(p);
    return sqlite3DbStrDup(0, "cannot acquire a read lock on the database");
  }
  sCheck.pBt = pBt;
  sCheck.pPager = pBt->pPager;
  sCheck.nPage = pagerPagecount(sCheck.pBt);
  sCheck.mxErr = mxErr;
  sCheck.nErr = 0;
  sCheck.mallocFailed = 0;
  *pnErr = 0;
  if( sCheck.nPage==0 ){
    unlockBtreeIfUnused(pBt);
    sqlite3BtreeLeave(p);
    return 0;
  }
  sCheck.anRef = sqlite3Malloc( (sCheck.nPage+1)*sizeof(sCheck.anRef[0]) );
  if( !sCheck.anRef ){
    unlockBtreeIfUnused(pBt);
    *pnErr = 1;
    sqlite3BtreeLeave(p);
    return 0;
  }
  for(i=0; i<=sCheck.nPage; i++){ sCheck.anRef[i] = 0; }
  i = PENDING_BYTE_PAGE(pBt);
  if( i<=sCheck.nPage ){
    sCheck.anRef[i] = 1;
  }
  sqlite3StrAccumInit(&sCheck.errMsg, zErr, sizeof(zErr), 20000);

  /* Check the integrity of the freelist
  */
  checkList(&sCheck, 1, get4byte(&pBt->pPage1->aData[32]),
            get4byte(&pBt->pPage1->aData[36]), "Main freelist: ");

  /* Check all the tables.
  */
  for(i=0; (int)i<nRoot && sCheck.mxErr; i++){
    if( aRoot[i]==0 ) continue;
#ifndef SQLITE_OMIT_AUTOVACUUM
    if( pBt->autoVacuum && aRoot[i]>1 ){
      checkPtrmap(&sCheck, aRoot[i], PTRMAP_ROOTPAGE, 0, 0);
    }
#endif
    checkTreePage(&sCheck, aRoot[i], "List of tree roots: ");
  }

  /* Make sure every page in the file is referenced
  */
  for(i=1; i<=sCheck.nPage && sCheck.mxErr; i++){
#ifdef SQLITE_OMIT_AUTOVACUUM
    if( sCheck.anRef[i]==0 ){
      checkAppendMsg(&sCheck, 0, "Page %d is never used", i);
    }
#else
    /* If the database supports auto-vacuum, make sure no tables contain
    ** references to pointer-map pages.
    */
    if( sCheck.anRef[i]==0 && 
       (PTRMAP_PAGENO(pBt, i)!=i || !pBt->autoVacuum) ){
      checkAppendMsg(&sCheck, 0, "Page %d is never used", i);
    }
    if( sCheck.anRef[i]!=0 && 
       (PTRMAP_PAGENO(pBt, i)==i && pBt->autoVacuum) ){
      checkAppendMsg(&sCheck, 0, "Pointer map page %d is referenced", i);
    }
#endif
  }

  /* Make sure this analysis did not leave any unref() pages.
  ** This is an internal consistency check; an integrity check
  ** of the integrity check.
  */
  unlockBtreeIfUnused(pBt);
  if( NEVER(nRef != sqlite3PagerRefcount(pBt->pPager)) ){
    checkAppendMsg(&sCheck, 0, 
      "Outstanding page count goes from %d to %d during this analysis",
      nRef, sqlite3PagerRefcount(pBt->pPager)
    );
  }

  /* Clean  up and report errors.
  */
  sqlite3BtreeLeave(p);
  sqlite3_free(sCheck.anRef);
  if( sCheck.mallocFailed ){
    sqlite3StrAccumReset(&sCheck.errMsg);
    *pnErr = sCheck.nErr+1;
    return 0;
  }
  *pnErr = sCheck.nErr;
  if( sCheck.nErr==0 ) sqlite3StrAccumReset(&sCheck.errMsg);
  return sqlite3StrAccumFinish(&sCheck.errMsg);
}
#endif /* SQLITE_OMIT_INTEGRITY_CHECK */

/*
** Return the full pathname of the underlying database file.
**
** The pager filename is invariant as long as the pager is
** open so it is safe to access without the BtShared mutex.
*/
const char *sqlite3BtreeGetFilename(Btree *p){
  assert( p->pBt->pPager!=0 );
  return sqlite3PagerFilename(p->pBt->pPager);
}

/*
** Return the pathname of the journal file for this database. The return
** value of this routine is the same regardless of whether the journal file
** has been created or not.
