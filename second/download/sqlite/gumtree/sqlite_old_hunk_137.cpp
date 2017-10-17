    goto exprtest_out;
  }
  for(ii=0; ii<nCol; ii++){
    azCol[ii] = (char *)sqlite3_value_text(argv[ii+2]);
  }

  rc = sqlite3Fts3ExprParse(
      pTokenizer, azCol, nCol, nCol, zExpr, nExpr, &pExpr
  );
  if( rc==SQLITE_NOMEM ){
    sqlite3_result_error_nomem(context);
    goto exprtest_out;
  }else if( rc==SQLITE_OK ){
    char zBuf[4096];
    exprToString(pExpr, zBuf);
    sqlite3_result_text(context, zBuf, -1, SQLITE_TRANSIENT);
    sqlite3Fts3ExprFree(pExpr);
  }else{
    sqlite3_result_error(context, "Error parsing expression", -1);
  }

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
void sqlite3Fts3ExprInitTestInterface(sqlite3* db){
  sqlite3_create_function(
      db, "fts3_exprtest", -1, SQLITE_UTF8, 0, fts3ExprTest, 0, 0
  );
}

#endif
#endif /* !defined(SQLITE_CORE) || defined(SQLITE_ENABLE_FTS3) */
