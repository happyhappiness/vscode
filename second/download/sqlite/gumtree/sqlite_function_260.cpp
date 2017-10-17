static void snippetFunc(
  sqlite3_context *pContext,
  int argc,
  sqlite3_value **argv
){
  fulltext_cursor *pCursor;
  if( argc<1 ) return;
  if( sqlite3_value_type(argv[0])!=SQLITE_BLOB ||
      sqlite3_value_bytes(argv[0])!=sizeof(pCursor) ){
    sqlite3_result_error(pContext, "illegal first argument to html_snippet",-1);
  }else{
    const char *zStart = "<b>";
    const char *zEnd = "</b>";
    const char *zEllipsis = "<b>...</b>";
    memcpy(&pCursor, sqlite3_value_blob(argv[0]), sizeof(pCursor));
    if( argc>=2 ){
      zStart = (const char*)sqlite3_value_text(argv[1]);
      if( argc>=3 ){
        zEnd = (const char*)sqlite3_value_text(argv[2]);
        if( argc>=4 ){
          zEllipsis = (const char*)sqlite3_value_text(argv[3]);
        }
      }
    }
    snippetAllOffsets(pCursor);
    snippetText(pCursor, zStart, zEnd, zEllipsis);
    sqlite3_result_text(pContext, pCursor->snippet.zSnippet,
                        pCursor->snippet.nSnippet, SQLITE_STATIC);
  }
}