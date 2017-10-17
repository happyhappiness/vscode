    MEM5LINK(x)->prev = i;
  }
  mem5.aiFreelist[iLogsize] = i;
}

/*
** If the STATIC_MEM mutex is not already held, obtain it now. The mutex
** will already be held (obtained by code in malloc.c) if
** sqlite3GlobalConfig.bMemStat is true.
*/
static void memsys5Enter(void){
  if( sqlite3GlobalConfig.bMemstat==0 && mem5.mutex==0 ){
    mem5.mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_MEM);
  }
  sqlite3_mutex_enter(mem5.mutex);
}
static void memsys5Leave(void){
  sqlite3_mutex_leave(mem5.mutex);
}

/*
** Return the size of an outstanding allocation, in bytes.  The
** size returned omits the 8-byte header overhead.  This only
** works for chunks that are currently checked out.
*/
static int memsys5Size(void *p){
  int iSize = 0;
  if( p ){
    int i = ((u8 *)p-mem5.zPool)/mem5.nAtom;
    assert( i>=0 && i<mem5.nBlock );
    iSize = mem5.nAtom * (1 << (mem5.aCtrl[i]&CTRL_LOGSIZE));
  }
  return iSize;
}

/*
** Find the first entry on the freelist iLogsize.  Unlink that
** entry and return its index. 
*/
static int memsys5UnlinkFirst(int iLogsize){
  int i;
  int iFirst;

  assert( iLogsize>=0 && iLogsize<=LOGMAX );
  i = iFirst = mem5.aiFreelist[iLogsize];
  assert( iFirst>=0 );
  while( i>0 ){
    if( i<iFirst ) iFirst = i;
    i = MEM5LINK(i)->next;
  }
  memsys5Unlink(iFirst, iLogsize);
  return iFirst;
}

/*
** Return a block of memory of at least nBytes in size.
** Return NULL if unable.
*/
static void *memsys5MallocUnsafe(int nByte){
  int i;           /* Index of a mem5.aPool[] slot */
  int iBin;        /* Index into mem5.aiFreelist[] */
  int iFullSz;     /* Size of allocation rounded up to power of 2 */
  int iLogsize;    /* Log2 of iFullSz/POW2_MIN */

  /* Keep track of the maximum allocation request.  Even unfulfilled
  ** requests are counted */
  if( (u32)nByte>mem5.maxRequest ){
    mem5.maxRequest = nByte;
  }

  /* Round nByte up to the next valid power of two */
  for(iFullSz=mem5.nAtom, iLogsize=0; iFullSz<nByte; iFullSz *= 2, iLogsize++){}

  /* Make sure mem5.aiFreelist[iLogsize] contains at least one free
  ** block.  If not, then split a block of the next larger power of
  ** two in order to create a new free block of size iLogsize.
  */
  for(iBin=iLogsize; mem5.aiFreelist[iBin]<0 && iBin<=LOGMAX; iBin++){}
  if( iBin>LOGMAX ) return 0;
  i = memsys5UnlinkFirst(iBin);
  while( iBin>iLogsize ){
    int newSize;

    iBin--;
    newSize = 1 << iBin;
    mem5.aCtrl[i+newSize] = CTRL_FREE | iBin;
    memsys5Link(i+newSize, iBin);
  }
  mem5.aCtrl[i] = iLogsize;

  /* Update allocator performance statistics. */
  mem5.nAlloc++;
  mem5.totalAlloc += iFullSz;
  mem5.totalExcess += iFullSz - nByte;
  mem5.currentCount++;
  mem5.currentOut += iFullSz;
  if( mem5.maxCount<mem5.currentCount ) mem5.maxCount = mem5.currentCount;
  if( mem5.maxOut<mem5.currentOut ) mem5.maxOut = mem5.currentOut;

  /* Return a pointer to the allocated memory. */
  return (void*)&mem5.zPool[i*mem5.nAtom];
}

/*
** Free an outstanding memory allocation.
*/
static void memsys5FreeUnsafe(void *pOld){
  u32 size, iLogsize;
  int iBlock;             

  /* Set iBlock to the index of the block pointed to by pOld in 
  ** the array of mem5.nAtom byte blocks pointed to by mem5.zPool.
  */
  iBlock = ((u8 *)pOld-mem5.zPool)/mem5.nAtom;

  /* Check that the pointer pOld points to a valid, non-free block. */
  assert( iBlock>=0 && iBlock<mem5.nBlock );
  assert( ((u8 *)pOld-mem5.zPool)%mem5.nAtom==0 );
  assert( (mem5.aCtrl[iBlock] & CTRL_FREE)==0 );

  iLogsize = mem5.aCtrl[iBlock] & CTRL_LOGSIZE;
  size = 1<<iLogsize;
  assert( iBlock+size-1<(u32)mem5.nBlock );

  mem5.aCtrl[iBlock] |= CTRL_FREE;
  mem5.aCtrl[iBlock+size-1] |= CTRL_FREE;
  assert( mem5.currentCount>0 );
  assert( mem5.currentOut>=(size*mem5.nAtom) );
  mem5.currentCount--;
  mem5.currentOut -= size*mem5.nAtom;
  assert( mem5.currentOut>0 || mem5.currentCount==0 );
  assert( mem5.currentCount>0 || mem5.currentOut==0 );

  mem5.aCtrl[iBlock] = CTRL_FREE | iLogsize;
  while( iLogsize<LOGMAX ){
    int iBuddy;
    if( (iBlock>>iLogsize) & 1 ){
      iBuddy = iBlock - size;
    }else{
      iBuddy = iBlock + size;
    }
    assert( iBuddy>=0 );
    if( (iBuddy+(1<<iLogsize))>mem5.nBlock ) break;
    if( mem5.aCtrl[iBuddy]!=(CTRL_FREE | iLogsize) ) break;
    memsys5Unlink(iBuddy, iLogsize);
    iLogsize++;
    if( iBuddy<iBlock ){
      mem5.aCtrl[iBuddy] = CTRL_FREE | iLogsize;
      mem5.aCtrl[iBlock] = 0;
