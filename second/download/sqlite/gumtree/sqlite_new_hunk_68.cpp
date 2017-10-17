
/*
** Create a new PCache object. Storage space to hold the object
** has already been allocated and is passed in as the p pointer. 
** The caller discovers how much space needs to be allocated by 
** calling sqlite3PcacheSize().
*/
void sqlite3PcacheOpen(
  int szPage,                  /* Size of every page */
  int szExtra,                 /* Extra space associated with each page */
  int bPurgeable,              /* True if pages are on backing store */
  int (*xStress)(void*,PgHdr*),/* Call to try to make pages clean */
  void *pStress,               /* Argument to xStress */
  PCache *p                    /* Preallocated space for the PCache */
){
  memset(p, 0, sizeof(PCache));
  p->szPage = szPage;
  p->szExtra = szExtra;
  p->bPurgeable = bPurgeable;
  p->xStress = xStress;
  p->pStress = pStress;
  p->nMax = 100;
}

/*
** Change the page size for PCache object. The caller must ensure that there
** are no outstanding page references when this function is called.
*/
void sqlite3PcacheSetPageSize(PCache *pCache, int szPage){
  assert( pCache->nRef==0 && pCache->pDirty==0 );
  if( pCache->pCache ){
    sqlite3GlobalConfig.pcache.xDestroy(pCache->pCache);
    pCache->pCache = 0;
  }
  pCache->szPage = szPage;
}

/*
** Try to obtain a page from the cache.
*/
int sqlite3PcacheFetch(
  PCache *pCache,       /* Obtain the page from this cache */
  Pgno pgno,            /* Page number to obtain */
  int createFlag,       /* If true, create page if it does not exist already */
  PgHdr **ppPage        /* Write the page here */
){
  PgHdr *pPage = 0;
  int eCreate;

  assert( pCache!=0 );
  assert( pgno>0 );

  /* If the pluggable cache (sqlite3_pcache*) has not been allocated,
  ** allocate it now.
  */
  if( !pCache->pCache && createFlag ){
    sqlite3_pcache *p;
    int nByte;
    nByte = pCache->szPage + pCache->szExtra + sizeof(PgHdr);
    p = sqlite3GlobalConfig.pcache.xCreate(nByte, pCache->bPurgeable);
    if( !p ){
      return SQLITE_NOMEM;
    }
    sqlite3GlobalConfig.pcache.xCachesize(p, pCache->nMax);
    pCache->pCache = p;
  }

  eCreate = createFlag ? 1 : 0;
  if( eCreate && (!pCache->bPurgeable || !pCache->pDirty) ){
    eCreate = 2;
  }
  if( pCache->pCache ){
    pPage = sqlite3GlobalConfig.pcache.xFetch(pCache->pCache, pgno, eCreate);
  }

  if( !pPage && eCreate==1 ){
    PgHdr *pPg;

    /* Find a dirty page to write-out and recycle. First try to find a 
    ** page that does not require a journal-sync (one with PGHDR_NEED_SYNC
    ** cleared), but if that is not possible settle for any other 
    ** unreferenced dirty page.
    */
    expensive_assert( pcacheCheckSynced(pCache) );
    for(pPg=pCache->pSynced; 
        pPg && (pPg->nRef || (pPg->flags&PGHDR_NEED_SYNC)); 
        pPg=pPg->pDirtyPrev
    );
    if( !pPg ){
      for(pPg=pCache->pDirtyTail; pPg && pPg->nRef; pPg=pPg->pDirtyPrev);
    }
    if( pPg ){
      int rc;
      rc = pCache->xStress(pCache->pStress, pPg);
      if( rc!=SQLITE_OK && rc!=SQLITE_BUSY ){
        return rc;
      }
    }

    pPage = sqlite3GlobalConfig.pcache.xFetch(pCache->pCache, pgno, 2);
  }

  if( pPage ){
    if( !pPage->pData ){
      memset(pPage, 0, sizeof(PgHdr) + pCache->szExtra);
      pPage->pExtra = (void*)&pPage[1];
      pPage->pData = (void *)&((char *)pPage)[sizeof(PgHdr) + pCache->szExtra];
      pPage->pCache = pCache;
      pPage->pgno = pgno;
    }
    assert( pPage->pCache==pCache );
    assert( pPage->pgno==pgno );
    assert( pPage->pExtra==(void *)&pPage[1] );

    if( 0==pPage->nRef ){
      pCache->nRef++;
    }
    pPage->nRef++;
    if( pgno==1 ){
      pCache->pPage1 = pPage;
    }
  }
  *ppPage = pPage;
  return (pPage==0 && eCreate) ? SQLITE_NOMEM : SQLITE_OK;
}

/*
** Decrement the reference count on a page. If the page is clean and the
** reference count drops to 0, then it is made elible for recycling.
*/
void sqlite3PcacheRelease(PgHdr *p){
  assert( p->nRef>0 );
  p->nRef--;
  if( p->nRef==0 ){
    PCache *pCache = p->pCache;
    pCache->nRef--;
    if( (p->flags&PGHDR_DIRTY)==0 ){
      pcacheUnpin(p);
    }else{
      /* Move the page to the head of the dirty list. */
      pcacheRemoveFromDirtyList(p);
      pcacheAddToDirtyList(p);
    }
  }
}

/*
** Increase the reference count of a supplied page by 1.
*/
void sqlite3PcacheRef(PgHdr *p){
  assert(p->nRef>0);
  p->nRef++;
}

/*
** Drop a page from the cache. There must be exactly one reference to the
** page. This function deletes that reference, so after it returns the
** page pointed to by p is invalid.
*/
void sqlite3PcacheDrop(PgHdr *p){
  PCache *pCache;
  assert( p->nRef==1 );
  if( p->flags&PGHDR_DIRTY ){
    pcacheRemoveFromDirtyList(p);
  }
  pCache = p->pCache;
  pCache->nRef--;
  if( p->pgno==1 ){
    pCache->pPage1 = 0;
  }
  sqlite3GlobalConfig.pcache.xUnpin(pCache->pCache, p, 1);
}

/*
** Make sure the page is marked as dirty. If it isn't dirty already,
** make it so.
*/
void sqlite3PcacheMakeDirty(PgHdr *p){
  p->flags &= ~PGHDR_DONT_WRITE;
  assert( p->nRef>0 );
  if( 0==(p->flags & PGHDR_DIRTY) ){
    p->flags |= PGHDR_DIRTY;
    pcacheAddToDirtyList( p);
  }
}

/*
** Make sure the page is marked as clean. If it isn't clean already,
** make it so.
*/
void sqlite3PcacheMakeClean(PgHdr *p){
  if( (p->flags & PGHDR_DIRTY) ){
    pcacheRemoveFromDirtyList(p);
    p->flags &= ~(PGHDR_DIRTY|PGHDR_NEED_SYNC);
    if( p->nRef==0 ){
      pcacheUnpin(p);
    }
  }
}

/*
** Make every page in the cache clean.
*/
void sqlite3PcacheCleanAll(PCache *pCache){
  PgHdr *p;
  while( (p = pCache->pDirty)!=0 ){
    sqlite3PcacheMakeClean(p);
  }
}

/*
** Clear the PGHDR_NEED_SYNC flag from all dirty pages.
*/
void sqlite3PcacheClearSyncFlags(PCache *pCache){
  PgHdr *p;
  for(p=pCache->pDirty; p; p=p->pDirtyNext){
    p->flags &= ~PGHDR_NEED_SYNC;
