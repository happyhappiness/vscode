static void testFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  fts3Hash *pHash;
  sqlite3_tokenizer_module *p;
  sqlite3_tokenizer *pTokenizer = 0;
  sqlite3_tokenizer_cursor *pCsr = 0;

  const char *zErr = 0;

  const char *zName;
  int nName;
  const char *zInput;
  int nInput;

  const char *zArg = 0;

  const char *zToken;
  int nToken;
  int iStart;
  int iEnd;
  int iPos;

  Tcl_Obj *pRet;

  assert( argc==2 || argc==3 );

  nName = sqlite3_value_bytes(argv[0]);
  zName = (const char *)sqlite3_value_text(argv[0]);
  nInput = sqlite3_value_bytes(argv[argc-1]);
  zInput = (const char *)sqlite3_value_text(argv[argc-1]);

  if( argc==3 ){
    zArg = (const char *)sqlite3_value_text(argv[1]);
  }

  pHash = (fts3Hash *)sqlite3_user_data(context);
  p = (sqlite3_tokenizer_module *)sqlite3Fts3HashFind(pHash, zName, nName+1);

  if( !p ){
    char *zErr = sqlite3_mprintf("unknown tokenizer: %s", zName);
    sqlite3_result_error(context, zErr, -1);
    sqlite3_free(zErr);
    return;
  }

  pRet = Tcl_NewObj();
  Tcl_IncrRefCount(pRet);

  if( SQLITE_OK!=p->xCreate(zArg ? 1 : 0, &zArg, &pTokenizer) ){
    zErr = "error in xCreate()";
    goto finish;
  }
  pTokenizer->pModule = p;
  if( SQLITE_OK!=p->xOpen(pTokenizer, zInput, nInput, &pCsr) ){
    zErr = "error in xOpen()";
    goto finish;
  }
  pCsr->pTokenizer = pTokenizer;

  while( SQLITE_OK==p->xNext(pCsr, &zToken, &nToken, &iStart, &iEnd, &iPos) ){
    Tcl_ListObjAppendElement(0, pRet, Tcl_NewIntObj(iPos));
    Tcl_ListObjAppendElement(0, pRet, Tcl_NewStringObj(zToken, nToken));
    zToken = &zInput[iStart];
    nToken = iEnd-iStart;
    Tcl_ListObjAppendElement(0, pRet, Tcl_NewStringObj(zToken, nToken));
  }

  if( SQLITE_OK!=p->xClose(pCsr) ){
    zErr = "error in xClose()";
    goto finish;
  }
  if( SQLITE_OK!=p->xDestroy(pTokenizer) ){
    zErr = "error in xDestroy()";
    goto finish;
  }

finish:
  if( zErr ){
    sqlite3_result_error(context, zErr, -1);
  }else{
    sqlite3_result_text(context, Tcl_GetString(pRet), -1, SQLITE_TRANSIENT);
  }
  Tcl_DecrRefCount(pRet);
}