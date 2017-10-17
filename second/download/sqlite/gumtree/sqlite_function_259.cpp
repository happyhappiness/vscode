static int constructVtab(
  sqlite3 *db,              /* The SQLite database connection */
  fts3Hash *pHash,          /* Hash table containing tokenizers */
  TableSpec *spec,          /* Parsed spec information from parseSpec() */
  sqlite3_vtab **ppVTab,    /* Write the resulting vtab structure here */
  char **pzErr              /* Write any error message here */
){
  int rc;
  int n;
  fulltext_vtab *v = 0;
  const sqlite3_tokenizer_module *m = NULL;
  char *schema;

  char const *zTok;         /* Name of tokenizer to use for this fts table */
  int nTok;                 /* Length of zTok, including nul terminator */

  v = (fulltext_vtab *) sqlite3_malloc(sizeof(fulltext_vtab));
  if( v==0 ) return SQLITE_NOMEM;
  CLEAR(v);
  /* sqlite will initialize v->base */
  v->db = db;
  v->zDb = spec->zDb;       /* Freed when azColumn is freed */
  v->zName = spec->zName;   /* Freed when azColumn is freed */
  v->nColumn = spec->nColumn;
  v->azContentColumn = spec->azContentColumn;
  spec->azContentColumn = 0;
  v->azColumn = spec->azColumn;
  spec->azColumn = 0;

  if( spec->azTokenizer==0 ){
    return SQLITE_NOMEM;
  }

  zTok = spec->azTokenizer[0]; 
  if( !zTok ){
    zTok = "simple";
  }
  nTok = strlen(zTok)+1;

  m = (sqlite3_tokenizer_module *)sqlite3Fts3HashFind(pHash, zTok, nTok);
  if( !m ){
    *pzErr = sqlite3_mprintf("unknown tokenizer: %s", spec->azTokenizer[0]);
    rc = SQLITE_ERROR;
    goto err;
  }

  for(n=0; spec->azTokenizer[n]; n++){}
  if( n ){
    rc = m->xCreate(n-1, (const char*const*)&spec->azTokenizer[1],
                    &v->pTokenizer);
  }else{
    rc = m->xCreate(0, 0, &v->pTokenizer);
  }
  if( rc!=SQLITE_OK ) goto err;
  v->pTokenizer->pModule = m;

  /* TODO: verify the existence of backing tables foo_content, foo_term */

  schema = fulltextSchema(v->nColumn, (const char*const*)v->azColumn,
                          spec->zName);
  rc = sqlite3_declare_vtab(db, schema);
  sqlite3_free(schema);
  if( rc!=SQLITE_OK ) goto err;

  memset(v->pFulltextStatements, 0, sizeof(v->pFulltextStatements));

  /* Indicate that the buffer is not live. */
  v->nPendingData = -1;

  *ppVTab = &v->base;
  FTSTRACE(("FTS3 Connect %p\n", v));

  return rc;

err:
  fulltext_vtab_destroy(v);
  return rc;
}