 **
 ** The Incrblob.nByte field is fixed for the lifetime of the Incrblob
 ** so no mutex is required for access.
 */
 int sqlite3_blob_bytes(sqlite3_blob *pBlob){
   Incrblob *p = (Incrblob *)pBlob;
-  return p ? p->nByte : 0;
+  return (p && p->pStmt) ? p->nByte : 0;
+}
+
+/*
+** Move an existing blob handle to point to a different row of the same
+** database table.
+**
+** If an error occurs, or if the specified row does not exist or does not
+** contain a blob or text value, then an error code is returned and the
+** database handle error code and message set. If this happens, then all 
+** subsequent calls to sqlite3_blob_xxx() functions (except blob_close()) 
+** immediately return SQLITE_ABORT.
+*/
+int sqlite3_blob_reopen(sqlite3_blob *pBlob, sqlite3_int64 iRow){
+  int rc;
+  Incrblob *p = (Incrblob *)pBlob;
+  sqlite3 *db;
+
+  if( p==0 ) return SQLITE_MISUSE_BKPT;
+  db = p->db;
+  sqlite3_mutex_enter(db->mutex);
+
+  if( p->pStmt==0 ){
+    /* If there is no statement handle, then the blob-handle has
+    ** already been invalidated. Return SQLITE_ABORT in this case.
+    */
+    rc = SQLITE_ABORT;
+  }else{
+    char *zErr;
+    rc = blobSeekToRow(p, iRow, &zErr);
+    if( rc!=SQLITE_OK ){
+      sqlite3ErrorWithMsg(db, rc, (zErr ? "%s" : 0), zErr);
+      sqlite3DbFree(db, zErr);
+    }
+    assert( rc!=SQLITE_SCHEMA );
+  }
+
+  rc = sqlite3ApiExit(db, rc);
+  assert( rc==SQLITE_OK || p->pStmt==0 );
+  sqlite3_mutex_leave(db->mutex);
+  return rc;
 }
 
 #endif /* #ifndef SQLITE_OMIT_INCRBLOB */
