int sqlite3_blob_reopen(sqlite3_blob *pBlob, sqlite3_int64 iRow){
  int rc;
  Incrblob *p = (Incrblob *)pBlob;
  sqlite3 *db;

  if( p==0 ) return SQLITE_MISUSE_BKPT;
  db = p->db;
  sqlite3_mutex_enter(db->mutex);

  if( p->pStmt==0 ){
    /* If there is no statement handle, then the blob-handle has
    ** already been invalidated. Return SQLITE_ABORT in this case.
    */
    rc = SQLITE_ABORT;
  }else{
    char *zErr;
    rc = blobSeekToRow(p, iRow, &zErr);
    if( rc!=SQLITE_OK ){
      sqlite3ErrorWithMsg(db, rc, (zErr ? "%s" : 0), zErr);
      sqlite3DbFree(db, zErr);
    }
    assert( rc!=SQLITE_SCHEMA );
  }

  rc = sqlite3ApiExit(db, rc);
  assert( rc==SQLITE_OK || p->pStmt==0 );
  sqlite3_mutex_leave(db->mutex);
  return rc;
}