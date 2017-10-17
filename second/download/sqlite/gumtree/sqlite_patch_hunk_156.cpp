 struct analysisInfo {
   sqlite3 *db;
   const char *zDatabase;
 };
 
 /*
+** The first argument points to a nul-terminated string containing a
+** list of space separated integers. Read the first nOut of these into
+** the array aOut[].
+*/
+static void decodeIntArray(
+  char *zIntArray,       /* String containing int array to decode */
+  int nOut,              /* Number of slots in aOut[] */
+  tRowcnt *aOut,         /* Store integers here */
+  LogEst *aLog,          /* Or, if aOut==0, here */
+  Index *pIndex          /* Handle extra flags for this index, if not NULL */
+){
+  char *z = zIntArray;
+  int c;
+  int i;
+  tRowcnt v;
+
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( z==0 ) z = "";
+#else
+  assert( z!=0 );
+#endif
+  for(i=0; *z && i<nOut; i++){
+    v = 0;
+    while( (c=z[0])>='0' && c<='9' ){
+      v = v*10 + c - '0';
+      z++;
+    }
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+    if( aOut ) aOut[i] = v;
+    if( aLog ) aLog[i] = sqlite3LogEst(v);
+#else
+    assert( aOut==0 );
+    UNUSED_PARAMETER(aOut);
+    assert( aLog!=0 );
+    aLog[i] = sqlite3LogEst(v);
+#endif
+    if( *z==' ' ) z++;
+  }
+#ifndef SQLITE_ENABLE_STAT3_OR_STAT4
+  assert( pIndex!=0 ); {
+#else
+  if( pIndex ){
+#endif
+    pIndex->bUnordered = 0;
+    pIndex->noSkipScan = 0;
+    while( z[0] ){
+      if( sqlite3_strglob("unordered*", z)==0 ){
+        pIndex->bUnordered = 1;
+      }else if( sqlite3_strglob("sz=[0-9]*", z)==0 ){
+        pIndex->szIdxRow = sqlite3LogEst(sqlite3Atoi(z+3));
+      }else if( sqlite3_strglob("noskipscan*", z)==0 ){
+        pIndex->noSkipScan = 1;
+      }
+#ifdef SQLITE_ENABLE_COSTMULT
+      else if( sqlite3_strglob("costmult=[0-9]*",z)==0 ){
+        pIndex->pTable->costMult = sqlite3LogEst(sqlite3Atoi(z+9));
+      }
+#endif
+      while( z[0]!=0 && z[0]!=' ' ) z++;
+      while( z[0]==' ' ) z++;
+    }
+  }
+}
+
+/*
 ** This callback is invoked once for each index when reading the
 ** sqlite_stat1 table.  
 **
-**     argv[0] = name of the index
-**     argv[1] = results of analysis - on integer for each column
+**     argv[0] = name of the table
+**     argv[1] = name of the index (might be NULL)
+**     argv[2] = results of analysis - on integer for each column
+**
+** Entries for which argv[1]==NULL simply record the number of rows in
+** the table.
 */
 static int analysisLoader(void *pData, int argc, char **argv, char **NotUsed){
   analysisInfo *pInfo = (analysisInfo*)pData;
   Index *pIndex;
-  int i, c;
-  unsigned int v;
+  Table *pTable;
   const char *z;
 
-  assert( argc==2 );
+  assert( argc==3 );
   UNUSED_PARAMETER2(NotUsed, argc);
 
-  if( argv==0 || argv[0]==0 || argv[1]==0 ){
+  if( argv==0 || argv[0]==0 || argv[2]==0 ){
     return 0;
   }
-  pIndex = sqlite3FindIndex(pInfo->db, argv[0], pInfo->zDatabase);
-  if( pIndex==0 ){
+  pTable = sqlite3FindTable(pInfo->db, argv[0], pInfo->zDatabase);
+  if( pTable==0 ){
     return 0;
   }
-  z = argv[1];
-  for(i=0; *z && i<=pIndex->nColumn; i++){
-    v = 0;
-    while( (c=z[0])>='0' && c<='9' ){
-      v = v*10 + c - '0';
-      z++;
+  if( argv[1]==0 ){
+    pIndex = 0;
+  }else if( sqlite3_stricmp(argv[0],argv[1])==0 ){
+    pIndex = sqlite3PrimaryKeyIndex(pTable);
+  }else{
+    pIndex = sqlite3FindIndex(pInfo->db, argv[1], pInfo->zDatabase);
+  }
+  z = argv[2];
+
+  if( pIndex ){
+    tRowcnt *aiRowEst = 0;
+    int nCol = pIndex->nKeyCol+1;
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+    /* Index.aiRowEst may already be set here if there are duplicate 
+    ** sqlite_stat1 entries for this index. In that case just clobber
+    ** the old data with the new instead of allocating a new array.  */
+    if( pIndex->aiRowEst==0 ){
+      pIndex->aiRowEst = (tRowcnt*)sqlite3MallocZero(sizeof(tRowcnt) * nCol);
+      if( pIndex->aiRowEst==0 ) sqlite3OomFault(pInfo->db);
     }
-    pIndex->aiRowEst[i] = v;
-    if( *z==' ' ) z++;
+    aiRowEst = pIndex->aiRowEst;
+#endif
+    pIndex->bUnordered = 0;
+    decodeIntArray((char*)z, nCol, aiRowEst, pIndex->aiRowLogEst, pIndex);
+    pIndex->hasStat1 = 1;
+    if( pIndex->pPartIdxWhere==0 ){
+      pTable->nRowLogEst = pIndex->aiRowLogEst[0];
+      pTable->tabFlags |= TF_HasStat1;
+    }
+  }else{
+    Index fakeIdx;
+    fakeIdx.szIdxRow = pTable->szTabRow;
+#ifdef SQLITE_ENABLE_COSTMULT
+    fakeIdx.pTable = pTable;
+#endif
+    decodeIntArray((char*)z, 1, 0, &pTable->nRowLogEst, &fakeIdx);
+    pTable->szTabRow = fakeIdx.szIdxRow;
+    pTable->tabFlags |= TF_HasStat1;
   }
+
   return 0;
 }
 
 /*
-** Load the content of the sqlite_stat1 table into the index hash tables.
+** If the Index.aSample variable is not NULL, delete the aSample[] array
+** and its contents.
+*/
+void sqlite3DeleteIndexSamples(sqlite3 *db, Index *pIdx){
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( pIdx->aSample ){
+    int j;
+    for(j=0; j<pIdx->nSample; j++){
+      IndexSample *p = &pIdx->aSample[j];
+      sqlite3DbFree(db, p->p);
+    }
+    sqlite3DbFree(db, pIdx->aSample);
+  }
+  if( db && db->pnBytesFreed==0 ){
+    pIdx->nSample = 0;
+    pIdx->aSample = 0;
+  }
+#else
+  UNUSED_PARAMETER(db);
+  UNUSED_PARAMETER(pIdx);
+#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
+}
+
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+/*
+** Populate the pIdx->aAvgEq[] array based on the samples currently
+** stored in pIdx->aSample[]. 
+*/
+static void initAvgEq(Index *pIdx){
+  if( pIdx ){
+    IndexSample *aSample = pIdx->aSample;
+    IndexSample *pFinal = &aSample[pIdx->nSample-1];
+    int iCol;
+    int nCol = 1;
+    if( pIdx->nSampleCol>1 ){
+      /* If this is stat4 data, then calculate aAvgEq[] values for all
+      ** sample columns except the last. The last is always set to 1, as
+      ** once the trailing PK fields are considered all index keys are
+      ** unique.  */
+      nCol = pIdx->nSampleCol-1;
+      pIdx->aAvgEq[nCol] = 1;
+    }
+    for(iCol=0; iCol<nCol; iCol++){
+      int nSample = pIdx->nSample;
+      int i;                    /* Used to iterate through samples */
+      tRowcnt sumEq = 0;        /* Sum of the nEq values */
+      tRowcnt avgEq = 0;
+      tRowcnt nRow;             /* Number of rows in index */
+      i64 nSum100 = 0;          /* Number of terms contributing to sumEq */
+      i64 nDist100;             /* Number of distinct values in index */
+
+      if( !pIdx->aiRowEst || iCol>=pIdx->nKeyCol || pIdx->aiRowEst[iCol+1]==0 ){
+        nRow = pFinal->anLt[iCol];
+        nDist100 = (i64)100 * pFinal->anDLt[iCol];
+        nSample--;
+      }else{
+        nRow = pIdx->aiRowEst[0];
+        nDist100 = ((i64)100 * pIdx->aiRowEst[0]) / pIdx->aiRowEst[iCol+1];
+      }
+      pIdx->nRowEst0 = nRow;
+
+      /* Set nSum to the number of distinct (iCol+1) field prefixes that
+      ** occur in the stat4 table for this index. Set sumEq to the sum of 
+      ** the nEq values for column iCol for the same set (adding the value 
+      ** only once where there exist duplicate prefixes).  */
+      for(i=0; i<nSample; i++){
+        if( i==(pIdx->nSample-1)
+         || aSample[i].anDLt[iCol]!=aSample[i+1].anDLt[iCol] 
+        ){
+          sumEq += aSample[i].anEq[iCol];
+          nSum100 += 100;
+        }
+      }
+
+      if( nDist100>nSum100 && sumEq<nRow ){
+        avgEq = ((i64)100 * (nRow - sumEq))/(nDist100 - nSum100);
+      }
+      if( avgEq==0 ) avgEq = 1;
+      pIdx->aAvgEq[iCol] = avgEq;
+    }
+  }
+}
+
+/*
+** Look up an index by name.  Or, if the name of a WITHOUT ROWID table
+** is supplied instead, find the PRIMARY KEY index for that table.
+*/
+static Index *findIndexOrPrimaryKey(
+  sqlite3 *db,
+  const char *zName,
+  const char *zDb
+){
+  Index *pIdx = sqlite3FindIndex(db, zName, zDb);
+  if( pIdx==0 ){
+    Table *pTab = sqlite3FindTable(db, zName, zDb);
+    if( pTab && !HasRowid(pTab) ) pIdx = sqlite3PrimaryKeyIndex(pTab);
+  }
+  return pIdx;
+}
+
+/*
+** Load the content from either the sqlite_stat4 or sqlite_stat3 table 
+** into the relevant Index.aSample[] arrays.
+**
+** Arguments zSql1 and zSql2 must point to SQL statements that return
+** data equivalent to the following (statements are different for stat3,
+** see the caller of this function for details):
+**
+**    zSql1: SELECT idx,count(*) FROM %Q.sqlite_stat4 GROUP BY idx
+**    zSql2: SELECT idx,neq,nlt,ndlt,sample FROM %Q.sqlite_stat4
+**
+** where %Q is replaced with the database name before the SQL is executed.
+*/
+static int loadStatTbl(
+  sqlite3 *db,                  /* Database handle */
+  int bStat3,                   /* Assume single column records only */
+  const char *zSql1,            /* SQL statement 1 (see above) */
+  const char *zSql2,            /* SQL statement 2 (see above) */
+  const char *zDb               /* Database name (e.g. "main") */
+){
+  int rc;                       /* Result codes from subroutines */
+  sqlite3_stmt *pStmt = 0;      /* An SQL statement being run */
+  char *zSql;                   /* Text of the SQL statement */
+  Index *pPrevIdx = 0;          /* Previous index in the loop */
+  IndexSample *pSample;         /* A slot in pIdx->aSample[] */
+
+  assert( db->lookaside.bDisable );
+  zSql = sqlite3MPrintf(db, zSql1, zDb);
+  if( !zSql ){
+    return SQLITE_NOMEM_BKPT;
+  }
+  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
+  sqlite3DbFree(db, zSql);
+  if( rc ) return rc;
+
+  while( sqlite3_step(pStmt)==SQLITE_ROW ){
+    int nIdxCol = 1;              /* Number of columns in stat4 records */
+
+    char *zIndex;   /* Index name */
+    Index *pIdx;    /* Pointer to the index object */
+    int nSample;    /* Number of samples */
+    int nByte;      /* Bytes of space required */
+    int i;          /* Bytes of space required */
+    tRowcnt *pSpace;
+
+    zIndex = (char *)sqlite3_column_text(pStmt, 0);
+    if( zIndex==0 ) continue;
+    nSample = sqlite3_column_int(pStmt, 1);
+    pIdx = findIndexOrPrimaryKey(db, zIndex, zDb);
+    assert( pIdx==0 || bStat3 || pIdx->nSample==0 );
+    /* Index.nSample is non-zero at this point if data has already been
+    ** loaded from the stat4 table. In this case ignore stat3 data.  */
+    if( pIdx==0 || pIdx->nSample ) continue;
+    if( bStat3==0 ){
+      assert( !HasRowid(pIdx->pTable) || pIdx->nColumn==pIdx->nKeyCol+1 );
+      if( !HasRowid(pIdx->pTable) && IsPrimaryKeyIndex(pIdx) ){
+        nIdxCol = pIdx->nKeyCol;
+      }else{
+        nIdxCol = pIdx->nColumn;
+      }
+    }
+    pIdx->nSampleCol = nIdxCol;
+    nByte = sizeof(IndexSample) * nSample;
+    nByte += sizeof(tRowcnt) * nIdxCol * 3 * nSample;
+    nByte += nIdxCol * sizeof(tRowcnt);     /* Space for Index.aAvgEq[] */
+
+    pIdx->aSample = sqlite3DbMallocZero(db, nByte);
+    if( pIdx->aSample==0 ){
+      sqlite3_finalize(pStmt);
+      return SQLITE_NOMEM_BKPT;
+    }
+    pSpace = (tRowcnt*)&pIdx->aSample[nSample];
+    pIdx->aAvgEq = pSpace; pSpace += nIdxCol;
+    for(i=0; i<nSample; i++){
+      pIdx->aSample[i].anEq = pSpace; pSpace += nIdxCol;
+      pIdx->aSample[i].anLt = pSpace; pSpace += nIdxCol;
+      pIdx->aSample[i].anDLt = pSpace; pSpace += nIdxCol;
+    }
+    assert( ((u8*)pSpace)-nByte==(u8*)(pIdx->aSample) );
+  }
+  rc = sqlite3_finalize(pStmt);
+  if( rc ) return rc;
+
+  zSql = sqlite3MPrintf(db, zSql2, zDb);
+  if( !zSql ){
+    return SQLITE_NOMEM_BKPT;
+  }
+  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
+  sqlite3DbFree(db, zSql);
+  if( rc ) return rc;
+
+  while( sqlite3_step(pStmt)==SQLITE_ROW ){
+    char *zIndex;                 /* Index name */
+    Index *pIdx;                  /* Pointer to the index object */
+    int nCol = 1;                 /* Number of columns in index */
+
+    zIndex = (char *)sqlite3_column_text(pStmt, 0);
+    if( zIndex==0 ) continue;
+    pIdx = findIndexOrPrimaryKey(db, zIndex, zDb);
+    if( pIdx==0 ) continue;
+    /* This next condition is true if data has already been loaded from 
+    ** the sqlite_stat4 table. In this case ignore stat3 data.  */
+    nCol = pIdx->nSampleCol;
+    if( bStat3 && nCol>1 ) continue;
+    if( pIdx!=pPrevIdx ){
+      initAvgEq(pPrevIdx);
+      pPrevIdx = pIdx;
+    }
+    pSample = &pIdx->aSample[pIdx->nSample];
+    decodeIntArray((char*)sqlite3_column_text(pStmt,1),nCol,pSample->anEq,0,0);
+    decodeIntArray((char*)sqlite3_column_text(pStmt,2),nCol,pSample->anLt,0,0);
+    decodeIntArray((char*)sqlite3_column_text(pStmt,3),nCol,pSample->anDLt,0,0);
+
+    /* Take a copy of the sample. Add two 0x00 bytes the end of the buffer.
+    ** This is in case the sample record is corrupted. In that case, the
+    ** sqlite3VdbeRecordCompare() may read up to two varints past the
+    ** end of the allocated buffer before it realizes it is dealing with
+    ** a corrupt record. Adding the two 0x00 bytes prevents this from causing
+    ** a buffer overread.  */
+    pSample->n = sqlite3_column_bytes(pStmt, 4);
+    pSample->p = sqlite3DbMallocZero(db, pSample->n + 2);
+    if( pSample->p==0 ){
+      sqlite3_finalize(pStmt);
+      return SQLITE_NOMEM_BKPT;
+    }
+    if( pSample->n ){
+      memcpy(pSample->p, sqlite3_column_blob(pStmt, 4), pSample->n);
+    }
+    pIdx->nSample++;
+  }
+  rc = sqlite3_finalize(pStmt);
+  if( rc==SQLITE_OK ) initAvgEq(pPrevIdx);
+  return rc;
+}
+
+/*
+** Load content from the sqlite_stat4 and sqlite_stat3 tables into 
+** the Index.aSample[] arrays of all indices.
+*/
+static int loadStat4(sqlite3 *db, const char *zDb){
+  int rc = SQLITE_OK;             /* Result codes from subroutines */
+
+  assert( db->lookaside.bDisable );
+  if( sqlite3FindTable(db, "sqlite_stat4", zDb) ){
+    rc = loadStatTbl(db, 0,
+      "SELECT idx,count(*) FROM %Q.sqlite_stat4 GROUP BY idx", 
+      "SELECT idx,neq,nlt,ndlt,sample FROM %Q.sqlite_stat4",
+      zDb
+    );
+  }
+
+  if( rc==SQLITE_OK && sqlite3FindTable(db, "sqlite_stat3", zDb) ){
+    rc = loadStatTbl(db, 1,
+      "SELECT idx,count(*) FROM %Q.sqlite_stat3 GROUP BY idx", 
+      "SELECT idx,neq,nlt,ndlt,sqlite_record(sample) FROM %Q.sqlite_stat3",
+      zDb
+    );
+  }
+
+  return rc;
+}
+#endif /* SQLITE_ENABLE_STAT3_OR_STAT4 */
+
+/*
+** Load the content of the sqlite_stat1 and sqlite_stat3/4 tables. The
+** contents of sqlite_stat1 are used to populate the Index.aiRowEst[]
+** arrays. The contents of sqlite_stat3/4 are used to populate the
+** Index.aSample[] arrays.
+**
+** If the sqlite_stat1 table is not present in the database, SQLITE_ERROR
+** is returned. In this case, even if SQLITE_ENABLE_STAT3/4 was defined 
+** during compilation and the sqlite_stat3/4 table is present, no data is 
+** read from it.
+**
+** If SQLITE_ENABLE_STAT3/4 was defined during compilation and the 
+** sqlite_stat4 table is not present in the database, SQLITE_ERROR is
+** returned. However, in this case, data is read from the sqlite_stat1
+** table (if it is present) before returning.
+**
+** If an OOM error occurs, this function always sets db->mallocFailed.
+** This means if the caller does not care about other errors, the return
+** code may be ignored.
 */
 int sqlite3AnalysisLoad(sqlite3 *db, int iDb){
   analysisInfo sInfo;
   HashElem *i;
   char *zSql;
-  int rc;
+  int rc = SQLITE_OK;
+  Schema *pSchema = db->aDb[iDb].pSchema;
 
   assert( iDb>=0 && iDb<db->nDb );
   assert( db->aDb[iDb].pBt!=0 );
-  assert( sqlite3BtreeHoldsMutex(db->aDb[iDb].pBt) );
 
   /* Clear any prior statistics */
-  for(i=sqliteHashFirst(&db->aDb[iDb].pSchema->idxHash);i;i=sqliteHashNext(i)){
+  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
+  for(i=sqliteHashFirst(&pSchema->tblHash); i; i=sqliteHashNext(i)){
+    Table *pTab = sqliteHashData(i);
+    pTab->tabFlags &= ~TF_HasStat1;
+  }
+  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
     Index *pIdx = sqliteHashData(i);
-    sqlite3DefaultRowEst(pIdx);
+    pIdx->hasStat1 = 0;
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+    sqlite3DeleteIndexSamples(db, pIdx);
+    pIdx->aSample = 0;
+#endif
   }
 
-  /* Check to make sure the sqlite_stat1 table existss */
+  /* Load new statistics out of the sqlite_stat1 table */
   sInfo.db = db;
-  sInfo.zDatabase = db->aDb[iDb].zName;
-  if( sqlite3FindTable(db, "sqlite_stat1", sInfo.zDatabase)==0 ){
-     return SQLITE_ERROR;
+  sInfo.zDatabase = db->aDb[iDb].zDbSName;
+  if( sqlite3FindTable(db, "sqlite_stat1", sInfo.zDatabase)!=0 ){
+    zSql = sqlite3MPrintf(db, 
+        "SELECT tbl,idx,stat FROM %Q.sqlite_stat1", sInfo.zDatabase);
+    if( zSql==0 ){
+      rc = SQLITE_NOMEM_BKPT;
+    }else{
+      rc = sqlite3_exec(db, zSql, analysisLoader, &sInfo, 0);
+      sqlite3DbFree(db, zSql);
+    }
   }
 
+  /* Set appropriate defaults on all indexes not in the sqlite_stat1 table */
+  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
+  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
+    Index *pIdx = sqliteHashData(i);
+    if( !pIdx->hasStat1 ) sqlite3DefaultRowEst(pIdx);
+  }
 
-  /* Load new statistics out of the sqlite_stat1 table */
-  zSql = sqlite3MPrintf(db, "SELECT idx, stat FROM %Q.sqlite_stat1",
-                        sInfo.zDatabase);
-  if( zSql==0 ){
-    rc = SQLITE_NOMEM;
-  }else{
-    (void)sqlite3SafetyOff(db);
-    rc = sqlite3_exec(db, zSql, analysisLoader, &sInfo, 0);
-    (void)sqlite3SafetyOn(db);
-    sqlite3DbFree(db, zSql);
-    if( rc==SQLITE_NOMEM ) db->mallocFailed = 1;
+  /* Load the statistics from the sqlite_stat4 table. */
+#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
+  if( rc==SQLITE_OK && OptimizationEnabled(db, SQLITE_Stat34) ){
+    db->lookaside.bDisable++;
+    rc = loadStat4(db, sInfo.zDatabase);
+    db->lookaside.bDisable--;
+  }
+  for(i=sqliteHashFirst(&pSchema->idxHash); i; i=sqliteHashNext(i)){
+    Index *pIdx = sqliteHashData(i);
+    sqlite3_free(pIdx->aiRowEst);
+    pIdx->aiRowEst = 0;
+  }
+#endif
+
+  if( rc==SQLITE_NOMEM ){
+    sqlite3OomFault(db);
   }
   return rc;
 }
 
 
 #endif /* SQLITE_OMIT_ANALYZE */
