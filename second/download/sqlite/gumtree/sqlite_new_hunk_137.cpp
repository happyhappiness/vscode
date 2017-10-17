    goto exprtest_out;
  }
  for(ii=0; ii<nCol; ii++){
    azCol[ii] = (char *)sqlite3_value_text(argv[ii+2]);
  }

  if( sqlite3_user_data(context) ){
    char *zDummy = 0;
    rc = sqlite3Fts3ExprParse(
        pTokenizer, 0, azCol, 0, nCol, nCol, zExpr, nExpr, &pExpr, &zDummy
    );
    assert( rc==SQLITE_OK || pExpr==0 );
    sqlite3_free(zDummy);
  }else{
    rc = fts3ExprParseUnbalanced(
        pTokenizer, 0, azCol, 0, nCol, nCol, zExpr, nExpr, &pExpr
    );
  }

  if( rc!=SQLITE_OK && rc!=SQLITE_NOMEM ){
    sqlite3Fts3ExprFree(pExpr);
    sqlite3_result_error(context, "Error parsing expression", -1);
  }else if( rc==SQLITE_NOMEM || !(zBuf = exprToString(pExpr, 0)) ){
    sqlite3_result_error_nomem(context);
  }else{
    sqlite3_result_text(context, zBuf, -1, SQLITE_TRANSIENT);
    sqlite3_free(zBuf);
  }

  sqlite3Fts3ExprFree(pExpr);

exprtest_out:
  if( pModule && pTokenizer ){
    rc = pModule->xDestroy(pTokenizer);
  }
  sqlite3_free(azCol);
}

/*
** Register the query expression parser test function fts3_exprtest() 
** with database connection db. 
*/
int sqlite3Fts3ExprInitTestInterface(sqlite3* db){
  int rc = sqlite3_create_function(
      db, "fts3_exprtest", -1, SQLITE_UTF8, 0, fts3ExprTest, 0, 0
  );
  if( rc==SQLITE_OK ){
    rc = sqlite3_create_function(db, "fts3_exprtest_rebalance", 
        -1, SQLITE_UTF8, (void *)1, fts3ExprTest, 0, 0
    );
  }
  return rc;
}

#endif
#endif /* !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3) */
