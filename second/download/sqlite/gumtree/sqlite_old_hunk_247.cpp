**
** The Incrblob.nByte field is fixed for the lifetime of the Incrblob
** so no mutex is required for access.
*/
int sqlite3_blob_bytes(sqlite3_blob *pBlob){
  Incrblob *p = (Incrblob *)pBlob;
  return p ? p->nByte : 0;
}

#endif /* #ifndef SQLITE_OMIT_INCRBLOB */
