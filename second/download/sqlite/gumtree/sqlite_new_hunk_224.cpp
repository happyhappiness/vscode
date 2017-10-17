    p->nColumn = nCol;
    for(i=0; i<nCol; i++){
      z = sqlite3_mprintf("%s", colv[i]);
      if( z==0 ) goto malloc_failed;
      p->azResult[p->nData++] = z;
    }
  }else if( (int)p->nColumn!=nCol ){
    sqlite3_free(p->zErrMsg);
    p->zErrMsg = sqlite3_mprintf(
       "sqlite3_get_table() called with two or more incompatible queries"
    );
    p->rc = SQLITE_ERROR;
    return 1;
