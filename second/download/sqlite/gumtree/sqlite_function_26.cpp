static void optimizeFunc(sqlite3_context *pContext,
                         int argc, sqlite3_value **argv){
  fulltext_cursor *pCursor;
  if( argc>1 ){
    sqlite3_result_error(pContext, "excess arguments to optimize()",-1);
  }else if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
            sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
    sqlite3_result_error(pContext, "illegal first argument to optimize",-1);
  }else{
    fulltext_vtab *v;
    int i, rc, iMaxLevel;
    OptLeavesReader *readers;
    int nReaders;
    LeafWriter writer;
    sqlite3_stmt *s;

    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
    v = cursor_vtab(pCursor);

    /* Flush any buffered updates before optimizing. */
    rc = flushPendingTerms(v);
    if( rc!=SQLITE_OK ) goto err;

    rc = segdir_count(v, &nReaders, &iMaxLevel);
    if( rc!=SQLITE_OK ) goto err;
    if( nReaders==0 || nReaders==1 ){
      sqlite3_result_text(pContext, "Index already optimal", -1,
                          SQLITE_STATIC);
      return;
    }

    rc = sql_get_statement(v, SEGDIR_SELECT_ALL_STMT, &s);
    if( rc!=SQLITE_OK ) goto err;

    readers = sqlite3_malloc(nReaders*sizeof(readers[0]));
    if( readers==NULL ) goto err;

    /* Note that there will already be a segment at this position
    ** until we call segdir_delete() on iMaxLevel.
    */
    leafWriterInit(iMaxLevel, 0, &writer);

    i = 0;
    while( (rc = sqlite3_step(s))==SQLITE_ROW ){
      sqlite_int64 iStart = sqlite3_column_int64(s, 0);
      sqlite_int64 iEnd = sqlite3_column_int64(s, 1);
      const char *pRootData = sqlite3_column_blob(s, 2);
      int nRootData = sqlite3_column_bytes(s, 2);

      assert( i<nReaders );
      rc = leavesReaderInit(v, -1, iStart, iEnd, pRootData, nRootData,
                            &readers[i].reader);
      if( rc!=SQLITE_OK ) break;

      readers[i].segment = i;
      i++;
    }

    /* If we managed to successfully read them all, optimize them. */
    if( rc==SQLITE_DONE ){
      assert( i==nReaders );
      rc = optimizeInternal(v, readers, nReaders, &writer);
    }

    while( i-- > 0 ){
      leavesReaderDestroy(&readers[i].reader);
    }
    sqlite3_free(readers);

    /* If we've successfully gotten to here, delete the old segments
    ** and flush the interior structure of the new segment.
    */
    if( rc==SQLITE_OK ){
      for( i=0; i<=iMaxLevel; i++ ){
        rc = segdir_delete(v, i);
        if( rc!=SQLITE_OK ) break;
      }

      if( rc==SQLITE_OK ) rc = leafWriterFinalize(v, &writer);
    }

    leafWriterDestroy(&writer);

    if( rc!=SQLITE_OK ) goto err;

    sqlite3_result_text(pContext, "Index optimized", -1, SQLITE_STATIC);
    return;

    /* TODO(shess): Error-handling needs to be improved along the
    ** lines of the dump_ functions.
    */
 err:
    {
      char buf[512];
      sqlite3_snprintf(sizeof(buf), buf, "Error in optimize: %s",
                       sqlite3_errmsg(sqlite3_context_db_handle(pContext)));
      sqlite3_result_error(pContext, buf, -1);
    }
  }
}