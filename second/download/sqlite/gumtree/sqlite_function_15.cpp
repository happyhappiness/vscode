static int fts3FunctionArg(
  sqlite3_context *pContext,      /* SQL function call context */
  const char *zFunc,              /* Function name */
  sqlite3_value *pVal,            /* argv[0] passed to function */
  Fts3Cursor **ppCsr              /* OUT: Store cursor handle here */
){
  int rc;
  *ppCsr = (Fts3Cursor*)sqlite3_value_pointer(pVal, "fts3cursor");
  if( (*ppCsr)!=0 ){
    rc = SQLITE_OK;
  }else{
    char *zErr = sqlite3_mprintf("illegal first argument to %s", zFunc);
    sqlite3_result_error(pContext, zErr, -1);
    sqlite3_free(zErr);
    rc = SQLITE_ERROR;
  }
  return rc;
}