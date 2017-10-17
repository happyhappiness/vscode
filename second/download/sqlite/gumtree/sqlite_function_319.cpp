static int loadStatTbl(
  sqlite3 *db,                  /* Database handle */
  int bStat3,                   /* Assume single column records only */
  const char *zSql1,            /* SQL statement 1 (see above) */
  const char *zSql2,            /* SQL statement 2 (see above) */
  const char *zDb               /* Database name (e.g. "main") */
){
  int rc;                       /* Result codes from subroutines */
  sqlite3_stmt *pStmt = 0;      /* An SQL statement being run */
  char *zSql;                   /* Text of the SQL statement */
  Index *pPrevIdx = 0;          /* Previous index in the loop */
  IndexSample *pSample;         /* A slot in pIdx->aSample[] */

  assert( db->lookaside.bDisable );
  zSql = sqlite3MPrintf(db, zSql1, zDb);
  if( !zSql ){
    return SQLITE_NOMEM_BKPT;
  }
  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  sqlite3DbFree(db, zSql);
  if( rc ) return rc;

  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    int nIdxCol = 1;              /* Number of columns in stat4 records */

    char *zIndex;   /* Index name */
    Index *pIdx;    /* Pointer to the index object */
    int nSample;    /* Number of samples */
    int nByte;      /* Bytes of space required */
    int i;          /* Bytes of space required */
    tRowcnt *pSpace;

    zIndex = (char *)sqlite3_column_text(pStmt, 0);
    if( zIndex==0 ) continue;
    nSample = sqlite3_column_int(pStmt, 1);
    pIdx = findIndexOrPrimaryKey(db, zIndex, zDb);
    assert( pIdx==0 || bStat3 || pIdx->nSample==0 );
    /* Index.nSample is non-zero at this point if data has already been
    ** loaded from the stat4 table. In this case ignore stat3 data.  */
    if( pIdx==0 || pIdx->nSample ) continue;
    if( bStat3==0 ){
      assert( !HasRowid(pIdx->pTable) || pIdx->nColumn==pIdx->nKeyCol+1 );
      if( !HasRowid(pIdx->pTable) && IsPrimaryKeyIndex(pIdx) ){
        nIdxCol = pIdx->nKeyCol;
      }else{
        nIdxCol = pIdx->nColumn;
      }
    }
    pIdx->nSampleCol = nIdxCol;
    nByte = sizeof(IndexSample) * nSample;
    nByte += sizeof(tRowcnt) * nIdxCol * 3 * nSample;
    nByte += nIdxCol * sizeof(tRowcnt);     /* Space for Index.aAvgEq[] */

    pIdx->aSample = sqlite3DbMallocZero(db, nByte);
    if( pIdx->aSample==0 ){
      sqlite3_finalize(pStmt);
      return SQLITE_NOMEM_BKPT;
    }
    pSpace = (tRowcnt*)&pIdx->aSample[nSample];
    pIdx->aAvgEq = pSpace; pSpace += nIdxCol;
    for(i=0; i<nSample; i++){
      pIdx->aSample[i].anEq = pSpace; pSpace += nIdxCol;
      pIdx->aSample[i].anLt = pSpace; pSpace += nIdxCol;
      pIdx->aSample[i].anDLt = pSpace; pSpace += nIdxCol;
    }
    assert( ((u8*)pSpace)-nByte==(u8*)(pIdx->aSample) );
  }
  rc = sqlite3_finalize(pStmt);
  if( rc ) return rc;

  zSql = sqlite3MPrintf(db, zSql2, zDb);
  if( !zSql ){
    return SQLITE_NOMEM_BKPT;
  }
  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  sqlite3DbFree(db, zSql);
  if( rc ) return rc;

  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    char *zIndex;                 /* Index name */
    Index *pIdx;                  /* Pointer to the index object */
    int nCol = 1;                 /* Number of columns in index */

    zIndex = (char *)sqlite3_column_text(pStmt, 0);
    if( zIndex==0 ) continue;
    pIdx = findIndexOrPrimaryKey(db, zIndex, zDb);
    if( pIdx==0 ) continue;
    /* This next condition is true if data has already been loaded from 
    ** the sqlite_stat4 table. In this case ignore stat3 data.  */
    nCol = pIdx->nSampleCol;
    if( bStat3 && nCol>1 ) continue;
    if( pIdx!=pPrevIdx ){
      initAvgEq(pPrevIdx);
      pPrevIdx = pIdx;
    }
    pSample = &pIdx->aSample[pIdx->nSample];
    decodeIntArray((char*)sqlite3_column_text(pStmt,1),nCol,pSample->anEq,0,0);
    decodeIntArray((char*)sqlite3_column_text(pStmt,2),nCol,pSample->anLt,0,0);
    decodeIntArray((char*)sqlite3_column_text(pStmt,3),nCol,pSample->anDLt,0,0);

    /* Take a copy of the sample. Add two 0x00 bytes the end of the buffer.
    ** This is in case the sample record is corrupted. In that case, the
    ** sqlite3VdbeRecordCompare() may read up to two varints past the
    ** end of the allocated buffer before it realizes it is dealing with
    ** a corrupt record. Adding the two 0x00 bytes prevents this from causing
    ** a buffer overread.  */
    pSample->n = sqlite3_column_bytes(pStmt, 4);
    pSample->p = sqlite3DbMallocZero(db, pSample->n + 2);
    if( pSample->p==0 ){
      sqlite3_finalize(pStmt);
      return SQLITE_NOMEM_BKPT;
    }
    if( pSample->n ){
      memcpy(pSample->p, sqlite3_column_blob(pStmt, 4), pSample->n);
    }
    pIdx->nSample++;
  }
  rc = sqlite3_finalize(pStmt);
  if( rc==SQLITE_OK ) initAvgEq(pPrevIdx);
  return rc;
}