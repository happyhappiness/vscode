 
 /*
 ** Create a new PCache object. Storage space to hold the object
 ** has already been allocated and is passed in as the p pointer. 
 ** The caller discovers how much space needs to be allocated by 
 ** calling sqlite3PcacheSize().
+**
+** szExtra is some extra space allocated for each page.  The first
+** 8 bytes of the extra space will be zeroed as the page is allocated,
+** but remaining content will be uninitialized.  Though it is opaque
+** to this module, the extra space really ends up being the MemPage
+** structure in the pager.
 */
-void sqlite3PcacheOpen(
+int sqlite3PcacheOpen(
   int szPage,                  /* Size of every page */
   int szExtra,                 /* Extra space associated with each page */
   int bPurgeable,              /* True if pages are on backing store */
   int (*xStress)(void*,PgHdr*),/* Call to try to make pages clean */
   void *pStress,               /* Argument to xStress */
   PCache *p                    /* Preallocated space for the PCache */
 ){
   memset(p, 0, sizeof(PCache));
-  p->szPage = szPage;
+  p->szPage = 1;
   p->szExtra = szExtra;
+  assert( szExtra>=8 );  /* First 8 bytes will be zeroed */
   p->bPurgeable = bPurgeable;
+  p->eCreate = 2;
   p->xStress = xStress;
   p->pStress = pStress;
-  p->nMax = 100;
+  p->szCache = 100;
+  p->szSpill = 1;
+  pcacheTrace(("%p.OPEN szPage %d bPurgeable %d\n",p,szPage,bPurgeable));
+  return sqlite3PcacheSetPageSize(p, szPage);
 }
 
 /*
 ** Change the page size for PCache object. The caller must ensure that there
 ** are no outstanding page references when this function is called.
 */
-void sqlite3PcacheSetPageSize(PCache *pCache, int szPage){
-  assert( pCache->nRef==0 && pCache->pDirty==0 );
-  if( pCache->pCache ){
-    sqlite3GlobalConfig.pcache.xDestroy(pCache->pCache);
-    pCache->pCache = 0;
+int sqlite3PcacheSetPageSize(PCache *pCache, int szPage){
+  assert( pCache->nRefSum==0 && pCache->pDirty==0 );
+  if( pCache->szPage ){
+    sqlite3_pcache *pNew;
+    pNew = sqlite3GlobalConfig.pcache2.xCreate(
+                szPage, pCache->szExtra + ROUND8(sizeof(PgHdr)),
+                pCache->bPurgeable
+    );
+    if( pNew==0 ) return SQLITE_NOMEM_BKPT;
+    sqlite3GlobalConfig.pcache2.xCachesize(pNew, numberOfCachePages(pCache));
+    if( pCache->pCache ){
+      sqlite3GlobalConfig.pcache2.xDestroy(pCache->pCache);
+    }
+    pCache->pCache = pNew;
+    pCache->szPage = szPage;
+    pcacheTrace(("%p.PAGESIZE %d\n",pCache,szPage));
   }
-  pCache->szPage = szPage;
+  return SQLITE_OK;
 }
 
 /*
 ** Try to obtain a page from the cache.
+**
+** This routine returns a pointer to an sqlite3_pcache_page object if
+** such an object is already in cache, or if a new one is created.
+** This routine returns a NULL pointer if the object was not in cache
+** and could not be created.
+**
+** The createFlags should be 0 to check for existing pages and should
+** be 3 (not 1, but 3) to try to create a new page.
+**
+** If the createFlag is 0, then NULL is always returned if the page
+** is not already in the cache.  If createFlag is 1, then a new page
+** is created only if that can be done without spilling dirty pages
+** and without exceeding the cache size limit.
+**
+** The caller needs to invoke sqlite3PcacheFetchFinish() to properly
+** initialize the sqlite3_pcache_page object and convert it into a
+** PgHdr object.  The sqlite3PcacheFetch() and sqlite3PcacheFetchFinish()
+** routines are split this way for performance reasons. When separated
+** they can both (usually) operate without having to push values to
+** the stack on entry and pop them back off on exit, which saves a
+** lot of pushing and popping.
 */
-int sqlite3PcacheFetch(
+sqlite3_pcache_page *sqlite3PcacheFetch(
   PCache *pCache,       /* Obtain the page from this cache */
   Pgno pgno,            /* Page number to obtain */
-  int createFlag,       /* If true, create page if it does not exist already */
-  PgHdr **ppPage        /* Write the page here */
+  int createFlag        /* If true, create page if it does not exist already */
 ){
-  PgHdr *pPage = 0;
   int eCreate;
+  sqlite3_pcache_page *pRes;
 
   assert( pCache!=0 );
-  assert( pgno>0 );
-
-  /* If the pluggable cache (sqlite3_pcache*) has not been allocated,
-  ** allocate it now.
+  assert( pCache->pCache!=0 );
+  assert( createFlag==3 || createFlag==0 );
+  assert( pCache->eCreate==((pCache->bPurgeable && pCache->pDirty) ? 1 : 2) );
+
+  /* eCreate defines what to do if the page does not exist.
+  **    0     Do not allocate a new page.  (createFlag==0)
+  **    1     Allocate a new page if doing so is inexpensive.
+  **          (createFlag==1 AND bPurgeable AND pDirty)
+  **    2     Allocate a new page even it doing so is difficult.
+  **          (createFlag==1 AND !(bPurgeable AND pDirty)
   */
-  if( !pCache->pCache && createFlag ){
-    sqlite3_pcache *p;
-    int nByte;
-    nByte = pCache->szPage + pCache->szExtra + sizeof(PgHdr);
-    p = sqlite3GlobalConfig.pcache.xCreate(nByte, pCache->bPurgeable);
-    if( !p ){
-      return SQLITE_NOMEM;
-    }
-    sqlite3GlobalConfig.pcache.xCachesize(p, pCache->nMax);
-    pCache->pCache = p;
-  }
-
-  eCreate = createFlag ? 1 : 0;
-  if( eCreate && (!pCache->bPurgeable || !pCache->pDirty) ){
-    eCreate = 2;
-  }
-  if( pCache->pCache ){
-    pPage = sqlite3GlobalConfig.pcache.xFetch(pCache->pCache, pgno, eCreate);
-  }
+  eCreate = createFlag & pCache->eCreate;
+  assert( eCreate==0 || eCreate==1 || eCreate==2 );
+  assert( createFlag==0 || pCache->eCreate==eCreate );
+  assert( createFlag==0 || eCreate==1+(!pCache->bPurgeable||!pCache->pDirty) );
+  pRes = sqlite3GlobalConfig.pcache2.xFetch(pCache->pCache, pgno, eCreate);
+  pcacheTrace(("%p.FETCH %d%s (result: %p)\n",pCache,pgno,
+               createFlag?" create":"",pRes));
+  return pRes;
+}
 
-  if( !pPage && eCreate==1 ){
-    PgHdr *pPg;
+/*
+** If the sqlite3PcacheFetch() routine is unable to allocate a new
+** page because no clean pages are available for reuse and the cache
+** size limit has been reached, then this routine can be invoked to 
+** try harder to allocate a page.  This routine might invoke the stress
+** callback to spill dirty pages to the journal.  It will then try to
+** allocate the new page and will only fail to allocate a new page on
+** an OOM error.
+**
+** This routine should be invoked only after sqlite3PcacheFetch() fails.
+*/
+int sqlite3PcacheFetchStress(
+  PCache *pCache,                 /* Obtain the page from this cache */
+  Pgno pgno,                      /* Page number to obtain */
+  sqlite3_pcache_page **ppPage    /* Write result here */
+){
+  PgHdr *pPg;
+  if( pCache->eCreate==2 ) return 0;
 
+  if( sqlite3PcachePagecount(pCache)>pCache->szSpill ){
     /* Find a dirty page to write-out and recycle. First try to find a 
     ** page that does not require a journal-sync (one with PGHDR_NEED_SYNC
     ** cleared), but if that is not possible settle for any other 
     ** unreferenced dirty page.
-    */
-    expensive_assert( pcacheCheckSynced(pCache) );
+    **
+    ** If the LRU page in the dirty list that has a clear PGHDR_NEED_SYNC
+    ** flag is currently referenced, then the following may leave pSynced
+    ** set incorrectly (pointing to other than the LRU page with NEED_SYNC
+    ** cleared). This is Ok, as pSynced is just an optimization.  */
     for(pPg=pCache->pSynced; 
         pPg && (pPg->nRef || (pPg->flags&PGHDR_NEED_SYNC)); 
         pPg=pPg->pDirtyPrev
     );
+    pCache->pSynced = pPg;
     if( !pPg ){
       for(pPg=pCache->pDirtyTail; pPg && pPg->nRef; pPg=pPg->pDirtyPrev);
     }
     if( pPg ){
       int rc;
+#ifdef SQLITE_LOG_CACHE_SPILL
+      sqlite3_log(SQLITE_FULL, 
+                  "spill page %d making room for %d - cache used: %d/%d",
+                  pPg->pgno, pgno,
+                  sqlite3GlobalConfig.pcache.xPagecount(pCache->pCache),
+                numberOfCachePages(pCache));
+#endif
+      pcacheTrace(("%p.SPILL %d\n",pCache,pPg->pgno));
       rc = pCache->xStress(pCache->pStress, pPg);
+      pcacheDump(pCache);
       if( rc!=SQLITE_OK && rc!=SQLITE_BUSY ){
         return rc;
       }
     }
-
-    pPage = sqlite3GlobalConfig.pcache.xFetch(pCache->pCache, pgno, 2);
   }
+  *ppPage = sqlite3GlobalConfig.pcache2.xFetch(pCache->pCache, pgno, 2);
+  return *ppPage==0 ? SQLITE_NOMEM_BKPT : SQLITE_OK;
+}
 
-  if( pPage ){
-    if( !pPage->pData ){
-      memset(pPage, 0, sizeof(PgHdr) + pCache->szExtra);
-      pPage->pExtra = (void*)&pPage[1];
-      pPage->pData = (void *)&((char *)pPage)[sizeof(PgHdr) + pCache->szExtra];
-      pPage->pCache = pCache;
-      pPage->pgno = pgno;
-    }
-    assert( pPage->pCache==pCache );
-    assert( pPage->pgno==pgno );
-    assert( pPage->pExtra==(void *)&pPage[1] );
+/*
+** This is a helper routine for sqlite3PcacheFetchFinish()
+**
+** In the uncommon case where the page being fetched has not been
+** initialized, this routine is invoked to do the initialization.
+** This routine is broken out into a separate function since it
+** requires extra stack manipulation that can be avoided in the common
+** case.
+*/
+static SQLITE_NOINLINE PgHdr *pcacheFetchFinishWithInit(
+  PCache *pCache,             /* Obtain the page from this cache */
+  Pgno pgno,                  /* Page number obtained */
+  sqlite3_pcache_page *pPage  /* Page obtained by prior PcacheFetch() call */
+){
+  PgHdr *pPgHdr;
+  assert( pPage!=0 );
+  pPgHdr = (PgHdr*)pPage->pExtra;
+  assert( pPgHdr->pPage==0 );
+  memset(&pPgHdr->pDirty, 0, sizeof(PgHdr) - offsetof(PgHdr,pDirty));
+  pPgHdr->pPage = pPage;
+  pPgHdr->pData = pPage->pBuf;
+  pPgHdr->pExtra = (void *)&pPgHdr[1];
+  memset(pPgHdr->pExtra, 0, 8);
+  pPgHdr->pCache = pCache;
+  pPgHdr->pgno = pgno;
+  pPgHdr->flags = PGHDR_CLEAN;
+  return sqlite3PcacheFetchFinish(pCache,pgno,pPage);
+}
 
-    if( 0==pPage->nRef ){
-      pCache->nRef++;
-    }
-    pPage->nRef++;
-    if( pgno==1 ){
-      pCache->pPage1 = pPage;
-    }
+/*
+** This routine converts the sqlite3_pcache_page object returned by
+** sqlite3PcacheFetch() into an initialized PgHdr object.  This routine
+** must be called after sqlite3PcacheFetch() in order to get a usable
+** result.
+*/
+PgHdr *sqlite3PcacheFetchFinish(
+  PCache *pCache,             /* Obtain the page from this cache */
+  Pgno pgno,                  /* Page number obtained */
+  sqlite3_pcache_page *pPage  /* Page obtained by prior PcacheFetch() call */
+){
+  PgHdr *pPgHdr;
+
+  assert( pPage!=0 );
+  pPgHdr = (PgHdr *)pPage->pExtra;
+
+  if( !pPgHdr->pPage ){
+    return pcacheFetchFinishWithInit(pCache, pgno, pPage);
   }
-  *ppPage = pPage;
-  return (pPage==0 && eCreate) ? SQLITE_NOMEM : SQLITE_OK;
+  pCache->nRefSum++;
+  pPgHdr->nRef++;
+  assert( sqlite3PcachePageSanity(pPgHdr) );
+  return pPgHdr;
 }
 
 /*
 ** Decrement the reference count on a page. If the page is clean and the
-** reference count drops to 0, then it is made elible for recycling.
+** reference count drops to 0, then it is made eligible for recycling.
 */
-void sqlite3PcacheRelease(PgHdr *p){
+void SQLITE_NOINLINE sqlite3PcacheRelease(PgHdr *p){
   assert( p->nRef>0 );
-  p->nRef--;
-  if( p->nRef==0 ){
-    PCache *pCache = p->pCache;
-    pCache->nRef--;
-    if( (p->flags&PGHDR_DIRTY)==0 ){
+  p->pCache->nRefSum--;
+  if( (--p->nRef)==0 ){
+    if( p->flags&PGHDR_CLEAN ){
       pcacheUnpin(p);
     }else{
-      /* Move the page to the head of the dirty list. */
-      pcacheRemoveFromDirtyList(p);
-      pcacheAddToDirtyList(p);
+      pcacheManageDirtyList(p, PCACHE_DIRTYLIST_FRONT);
     }
   }
 }
 
 /*
 ** Increase the reference count of a supplied page by 1.
 */
 void sqlite3PcacheRef(PgHdr *p){
   assert(p->nRef>0);
+  assert( sqlite3PcachePageSanity(p) );
   p->nRef++;
+  p->pCache->nRefSum++;
 }
 
 /*
 ** Drop a page from the cache. There must be exactly one reference to the
 ** page. This function deletes that reference, so after it returns the
 ** page pointed to by p is invalid.
 */
 void sqlite3PcacheDrop(PgHdr *p){
-  PCache *pCache;
   assert( p->nRef==1 );
+  assert( sqlite3PcachePageSanity(p) );
   if( p->flags&PGHDR_DIRTY ){
-    pcacheRemoveFromDirtyList(p);
+    pcacheManageDirtyList(p, PCACHE_DIRTYLIST_REMOVE);
   }
-  pCache = p->pCache;
-  pCache->nRef--;
-  if( p->pgno==1 ){
-    pCache->pPage1 = 0;
-  }
-  sqlite3GlobalConfig.pcache.xUnpin(pCache->pCache, p, 1);
+  p->pCache->nRefSum--;
+  sqlite3GlobalConfig.pcache2.xUnpin(p->pCache->pCache, p->pPage, 1);
 }
 
 /*
 ** Make sure the page is marked as dirty. If it isn't dirty already,
 ** make it so.
 */
 void sqlite3PcacheMakeDirty(PgHdr *p){
-  p->flags &= ~PGHDR_DONT_WRITE;
   assert( p->nRef>0 );
-  if( 0==(p->flags & PGHDR_DIRTY) ){
-    p->flags |= PGHDR_DIRTY;
-    pcacheAddToDirtyList( p);
+  assert( sqlite3PcachePageSanity(p) );
+  if( p->flags & (PGHDR_CLEAN|PGHDR_DONT_WRITE) ){    /*OPTIMIZATION-IF-FALSE*/
+    p->flags &= ~PGHDR_DONT_WRITE;
+    if( p->flags & PGHDR_CLEAN ){
+      p->flags ^= (PGHDR_DIRTY|PGHDR_CLEAN);
+      pcacheTrace(("%p.DIRTY %d\n",p->pCache,p->pgno));
+      assert( (p->flags & (PGHDR_DIRTY|PGHDR_CLEAN))==PGHDR_DIRTY );
+      pcacheManageDirtyList(p, PCACHE_DIRTYLIST_ADD);
+    }
+    assert( sqlite3PcachePageSanity(p) );
   }
 }
 
 /*
 ** Make sure the page is marked as clean. If it isn't clean already,
 ** make it so.
 */
 void sqlite3PcacheMakeClean(PgHdr *p){
-  if( (p->flags & PGHDR_DIRTY) ){
-    pcacheRemoveFromDirtyList(p);
-    p->flags &= ~(PGHDR_DIRTY|PGHDR_NEED_SYNC);
+  assert( sqlite3PcachePageSanity(p) );
+  if( ALWAYS((p->flags & PGHDR_DIRTY)!=0) ){
+    assert( (p->flags & PGHDR_CLEAN)==0 );
+    pcacheManageDirtyList(p, PCACHE_DIRTYLIST_REMOVE);
+    p->flags &= ~(PGHDR_DIRTY|PGHDR_NEED_SYNC|PGHDR_WRITEABLE);
+    p->flags |= PGHDR_CLEAN;
+    pcacheTrace(("%p.CLEAN %d\n",p->pCache,p->pgno));
+    assert( sqlite3PcachePageSanity(p) );
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
+  pcacheTrace(("%p.CLEAN-ALL\n",pCache));
   while( (p = pCache->pDirty)!=0 ){
     sqlite3PcacheMakeClean(p);
   }
 }
 
 /*
+** Clear the PGHDR_NEED_SYNC and PGHDR_WRITEABLE flag from all dirty pages.
+*/
+void sqlite3PcacheClearWritable(PCache *pCache){
+  PgHdr *p;
+  pcacheTrace(("%p.CLEAR-WRITEABLE\n",pCache));
+  for(p=pCache->pDirty; p; p=p->pDirtyNext){
+    p->flags &= ~(PGHDR_NEED_SYNC|PGHDR_WRITEABLE);
+  }
+  pCache->pSynced = pCache->pDirtyTail;
+}
+
+/*
 ** Clear the PGHDR_NEED_SYNC flag from all dirty pages.
 */
 void sqlite3PcacheClearSyncFlags(PCache *pCache){
   PgHdr *p;
   for(p=pCache->pDirty; p; p=p->pDirtyNext){
     p->flags &= ~PGHDR_NEED_SYNC;
