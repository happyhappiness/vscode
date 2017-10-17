int sqlite3_win32_compact_heap(LPUINT pnLargest){
  int rc = SQLITE_OK;
  UINT nLargest = 0;
  HANDLE hHeap;

  winMemAssertMagic();
  hHeap = winMemGetHeap();
  assert( hHeap!=0 );
  assert( hHeap!=INVALID_HANDLE_VALUE );
#if !SQLITE_OS_WINRT && defined(SQLITE_WIN32_MALLOC_VALIDATE)
  assert( osHeapValidate(hHeap, SQLITE_WIN32_HEAP_FLAGS, NULL) );
#endif
#if !SQLITE_OS_WINCE && !SQLITE_OS_WINRT
  if( (nLargest=osHeapCompact(hHeap, SQLITE_WIN32_HEAP_FLAGS))==0 ){
    DWORD lastErrno = osGetLastError();
    if( lastErrno==NO_ERROR ){
      sqlite3_log(SQLITE_NOMEM, "failed to HeapCompact (no space), heap=%p",
                  (void*)hHeap);
      rc = SQLITE_NOMEM_BKPT;
    }else{
      sqlite3_log(SQLITE_ERROR, "failed to HeapCompact (%lu), heap=%p",
                  osGetLastError(), (void*)hHeap);
      rc = SQLITE_ERROR;
    }
  }
#else
  sqlite3_log(SQLITE_NOTFOUND, "failed to HeapCompact, heap=%p",
              (void*)hHeap);
  rc = SQLITE_NOTFOUND;
#endif
  if( pnLargest ) *pnLargest = nLargest;
  return rc;
}