static void generateError(sqlite3_context *pContext,
                          const char *prefix, const char *msg){
  char buf[512];
  if( msg==NULL ) msg = sqlite3_errmsg(sqlite3_context_db_handle(pContext));
  sqlite3_snprintf(sizeof(buf), buf, "%s: %s", prefix, msg);
  sqlite3_result_error(pContext, buf, -1);
}