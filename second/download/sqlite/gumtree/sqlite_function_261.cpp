static void snippetOffsetsFunc(
  sqlite3_context *pContext,
  int argc,
  sqlite3_value **argv
){
  fulltext_cursor *pCursor;
  if( argc<1 ) return;
  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
    sqlite3_result_error(pContext, "illegal first argument to offsets",-1);
  }else{
    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
    snippetAllOffsets(pCursor);
    snippetOffsetText(&pCursor->snippet);
    sqlite3_result_text(pContext,
                        pCursor->snippet.zOffset, pCursor->snippet.nOffset,
                        SQLITE_STATIC);
  }
}