int sqlite3Fts3InitTokenizer(
  Fts3Hash *pHash,                /* Tokenizer hash table */
  const char *zArg,               /* Tokenizer name */
  sqlite3_tokenizer **ppTok,      /* OUT: Tokenizer (if applicable) */
  char **pzErr                    /* OUT: Set to malloced error message */
){
  int rc;
  char *z = (char *)zArg;
  int n = 0;
  char *zCopy;
  char *zEnd;                     /* Pointer to nul-term of zCopy */
  sqlite3_tokenizer_module *m;

  zCopy = sqlite3_mprintf("%s", zArg);
  if( !zCopy ) return SQLITE_NOMEM;
  zEnd = &zCopy[strlen(zCopy)];

  z = (char *)sqlite3Fts3NextToken(zCopy, &n);
  if( z==0 ){
    assert( n==0 );
    z = zCopy;
  }
  z[n] = '\0';
  sqlite3Fts3Dequote(z);

  m = (sqlite3_tokenizer_module *)sqlite3Fts3HashFind(pHash,z,(int)strlen(z)+1);
  if( !m ){
    sqlite3Fts3ErrMsg(pzErr, "unknown tokenizer: %s", z);
    rc = SQLITE_ERROR;
  }else{
    char const **aArg = 0;
    int iArg = 0;
    z = &z[n+1];
    while( z<zEnd && (NULL!=(z = (char *)sqlite3Fts3NextToken(z, &n))) ){
      int nNew = sizeof(char *)*(iArg+1);
      char const **aNew = (const char **)sqlite3_realloc((void *)aArg, nNew);
      if( !aNew ){
        sqlite3_free(zCopy);
        sqlite3_free((void *)aArg);
        return SQLITE_NOMEM;
      }
      aArg = aNew;
      aArg[iArg++] = z;
      z[n] = '\0';
      sqlite3Fts3Dequote(z);
      z = &z[n+1];
    }
    rc = m->xCreate(iArg, aArg, ppTok);
    assert( rc!=SQLITE_OK || *ppTok );
    if( rc!=SQLITE_OK ){
      sqlite3Fts3ErrMsg(pzErr, "unknown tokenizer");
    }else{
      (*ppTok)->pModule = m; 
    }
    sqlite3_free((void *)aArg);
  }

  sqlite3_free(zCopy);
  return rc;
}