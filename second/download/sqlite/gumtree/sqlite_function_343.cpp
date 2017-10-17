static int checkTreePage(
  IntegrityCk *pCheck,  /* Context for the sanity check */
  int iPage,            /* Page number of the page to check */
  char *zParentContext  /* Parent context */
){
  MemPage *pPage;
  int i, rc, depth, d2, pgno, cnt;
  int hdr, cellStart;
  int nCell;
  u8 *data;
  BtShared *pBt;
  int usableSize;
  char zContext[100];
  char *hit = 0;

  sqlite3_snprintf(sizeof(zContext), zContext, "Page %d: ", iPage);

  /* Check that the page exists
  */
  pBt = pCheck->pBt;
  usableSize = pBt->usableSize;
  if( iPage==0 ) return 0;
  if( checkRef(pCheck, iPage, zParentContext) ) return 0;
  if( (rc = sqlite3BtreeGetPage(pBt, (Pgno)iPage, &pPage, 0))!=0 ){
    if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ) pCheck->mallocFailed = 1;
    checkAppendMsg(pCheck, zContext,
       "unable to get the page. error code=%d", rc);
    return 0;
  }
  if( (rc = sqlite3BtreeInitPage(pPage))!=0 ){
    assert( rc==SQLITE_CORRUPT );  /* The only possible error from InitPage */
    checkAppendMsg(pCheck, zContext, 
                   "sqlite3BtreeInitPage() returns error code %d", rc);
    releasePage(pPage);
    return 0;
  }

  /* Check out all the cells.
  */
  depth = 0;
  for(i=0; i<pPage->nCell && pCheck->mxErr; i++){
    u8 *pCell;
    u32 sz;
    CellInfo info;

    /* Check payload overflow pages
    */
    sqlite3_snprintf(sizeof(zContext), zContext,
             "On tree page %d cell %d: ", iPage, i);
    pCell = findCell(pPage,i);
    sqlite3BtreeParseCellPtr(pPage, pCell, &info);
    sz = info.nData;
    if( !pPage->intKey ) sz += (int)info.nKey;
    assert( sz==info.nPayload );
    if( (sz>info.nLocal) 
     && (&pCell[info.iOverflow]<=&pPage->aData[pBt->usableSize])
    ){
      int nPage = (sz - info.nLocal + usableSize - 5)/(usableSize - 4);
      Pgno pgnoOvfl = get4byte(&pCell[info.iOverflow]);
#ifndef SQLITE_OMIT_AUTOVACUUM
      if( pBt->autoVacuum ){
        checkPtrmap(pCheck, pgnoOvfl, PTRMAP_OVERFLOW1, iPage, zContext);
      }
#endif
      checkList(pCheck, 0, pgnoOvfl, nPage, zContext);
    }

    /* Check sanity of left child page.
    */
    if( !pPage->leaf ){
      pgno = get4byte(pCell);
#ifndef SQLITE_OMIT_AUTOVACUUM
      if( pBt->autoVacuum ){
        checkPtrmap(pCheck, pgno, PTRMAP_BTREE, iPage, zContext);
      }
#endif
      d2 = checkTreePage(pCheck, pgno, zContext);
      if( i>0 && d2!=depth ){
        checkAppendMsg(pCheck, zContext, "Child page depth differs");
      }
      depth = d2;
    }
  }
  if( !pPage->leaf ){
    pgno = get4byte(&pPage->aData[pPage->hdrOffset+8]);
    sqlite3_snprintf(sizeof(zContext), zContext, 
                     "On page %d at right child: ", iPage);
#ifndef SQLITE_OMIT_AUTOVACUUM
    if( pBt->autoVacuum ){
      checkPtrmap(pCheck, pgno, PTRMAP_BTREE, iPage, 0);
    }
#endif
    checkTreePage(pCheck, pgno, zContext);
  }
 
  /* Check for complete coverage of the page
  */
  data = pPage->aData;
  hdr = pPage->hdrOffset;
  hit = sqlite3PageMalloc( pBt->pageSize );
  if( hit==0 ){
    pCheck->mallocFailed = 1;
  }else{
    u16 contentOffset = get2byte(&data[hdr+5]);
    if (contentOffset > usableSize) {
      checkAppendMsg(pCheck, 0, 
                     "Corruption detected in header on page %d",iPage,0);
      goto check_page_abort;
    }
    memset(hit+contentOffset, 0, usableSize-contentOffset);
    memset(hit, 1, contentOffset);
    nCell = get2byte(&data[hdr+3]);
    cellStart = hdr + 12 - 4*pPage->leaf;
    for(i=0; i<nCell; i++){
      int pc = get2byte(&data[cellStart+i*2]);
      u16 size = 1024;
      int j;
      if( pc<=usableSize ){
        size = cellSizePtr(pPage, &data[pc]);
      }
      if( (pc+size-1)>=usableSize || pc<0 ){
        checkAppendMsg(pCheck, 0, 
            "Corruption detected in cell %d on page %d",i,iPage,0);
      }else{
        for(j=pc+size-1; j>=pc; j--) hit[j]++;
      }
    }
    for(cnt=0, i=get2byte(&data[hdr+1]); i>0 && i<usableSize && cnt<10000; 
           cnt++){
      int size = get2byte(&data[i+2]);
      int j;
      if( (i+size-1)>=usableSize || i<0 ){
        checkAppendMsg(pCheck, 0,  
            "Corruption detected in cell %d on page %d",i,iPage,0);
      }else{
        for(j=i+size-1; j>=i; j--) hit[j]++;
      }
      i = get2byte(&data[i]);
    }
    for(i=cnt=0; i<usableSize; i++){
      if( hit[i]==0 ){
        cnt++;
      }else if( hit[i]>1 ){
        checkAppendMsg(pCheck, 0,
          "Multiple uses for byte %d of page %d", i, iPage);
        break;
      }
    }
    if( cnt!=data[hdr+7] ){
      checkAppendMsg(pCheck, 0, 
          "Fragmented space is %d byte reported as %d on page %d",
          cnt, data[hdr+7], iPage);
    }
  }
check_page_abort:
  if (hit) sqlite3PageFree(hit);

  releasePage(pPage);
  return depth+1;
}