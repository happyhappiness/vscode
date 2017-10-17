  ** cid:        Column id (numbered from left to right, starting at 0)
  ** name:       Column name
  ** type:       Column declaration type.
  ** notnull:    True if 'NOT NULL' is part of column declaration
  ** dflt_value: The default value for the column, if any.
  */
  if( sqlite3StrICmp(zLeft, "table_info")==0 && zRight ){
    Table *pTab;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pTab = sqlite3FindTable(db, zRight, zDb);
    if( pTab ){
      int i;
      int nHidden = 0;
      Column *pCol;
      sqlite3VdbeSetNumCols(v, 6);
      pParse->nMem = 6;
      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "cid", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "type", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 3, COLNAME_NAME, "notnull", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 4, COLNAME_NAME, "dflt_value", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 5, COLNAME_NAME, "pk", SQLITE_STATIC);
      sqlite3ViewGetColumnNames(pParse, pTab);
      for(i=0, pCol=pTab->aCol; i<pTab->nCol; i++, pCol++){
        if( IsHiddenColumn(pCol) ){
          nHidden++;
          continue;
        }
        sqlite3VdbeAddOp2(v, OP_Integer, i-nHidden, 1);
        sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pCol->zName, 0);
        sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
           pCol->zType ? pCol->zType : "", 0);
        sqlite3VdbeAddOp2(v, OP_Integer, (pCol->notNull ? 1 : 0), 4);
        if( pCol->zDflt ){
          sqlite3VdbeAddOp4(v, OP_String8, 0, 5, 0, (char*)pCol->zDflt, 0);
        }else{
          sqlite3VdbeAddOp2(v, OP_Null, 0, 5);
        }
        sqlite3VdbeAddOp2(v, OP_Integer, pCol->isPrimKey, 6);
        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 6);
      }
    }
  }else

  if( sqlite3StrICmp(zLeft, "index_info")==0 && zRight ){
    Index *pIdx;
    Table *pTab;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pIdx = sqlite3FindIndex(db, zRight, zDb);
    if( pIdx ){
      int i;
      pTab = pIdx->pTable;
      sqlite3VdbeSetNumCols(v, 3);
      pParse->nMem = 3;
      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seqno", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "cid", SQLITE_STATIC);
      sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "name", SQLITE_STATIC);
      for(i=0; i<pIdx->nColumn; i++){
        int cnum = pIdx->aiColumn[i];
        sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
        sqlite3VdbeAddOp2(v, OP_Integer, cnum, 2);
        assert( pTab->nCol>cnum );
        sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, pTab->aCol[cnum].zName, 0);
        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
      }
    }
  }else

  if( sqlite3StrICmp(zLeft, "index_list")==0 && zRight ){
    Index *pIdx;
    Table *pTab;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pTab = sqlite3FindTable(db, zRight, zDb);
    if( pTab ){
      v = sqlite3GetVdbe(pParse);
      pIdx = pTab->pIndex;
      if( pIdx ){
        int i = 0; 
        sqlite3VdbeSetNumCols(v, 3);
        pParse->nMem = 3;
        sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "unique", SQLITE_STATIC);
        while(pIdx){
          sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
          sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pIdx->zName, 0);
          sqlite3VdbeAddOp2(v, OP_Integer, pIdx->onError!=OE_None, 3);
          sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
          ++i;
          pIdx = pIdx->pNext;
        }
      }
    }
  }else

  if( sqlite3StrICmp(zLeft, "database_list")==0 ){
    int i;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    sqlite3VdbeSetNumCols(v, 3);
    pParse->nMem = 3;
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "file", SQLITE_STATIC);
    for(i=0; i<db->nDb; i++){
      if( db->aDb[i].pBt==0 ) continue;
      assert( db->aDb[i].zName!=0 );
      sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, db->aDb[i].zName, 0);
      sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
           sqlite3BtreeGetFilename(db->aDb[i].pBt), 0);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
    }
  }else

  if( sqlite3StrICmp(zLeft, "collation_list")==0 ){
    int i = 0;
    HashElem *p;
    sqlite3VdbeSetNumCols(v, 2);
    pParse->nMem = 2;
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
    for(p=sqliteHashFirst(&db->aCollSeq); p; p=sqliteHashNext(p)){
      CollSeq *pColl = (CollSeq *)sqliteHashData(p);
      sqlite3VdbeAddOp2(v, OP_Integer, i++, 1);
      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pColl->zName, 0);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 2);
    }
  }else
#endif /* SQLITE_OMIT_SCHEMA_PRAGMAS */

#ifndef SQLITE_OMIT_FOREIGN_KEY
  if( sqlite3StrICmp(zLeft, "foreign_key_list")==0 && zRight ){
    FKey *pFK;
    Table *pTab;
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pTab = sqlite3FindTable(db, zRight, zDb);
    if( pTab ){
      v = sqlite3GetVdbe(pParse);
      pFK = pTab->pFKey;
      if( pFK ){
        int i = 0; 
        sqlite3VdbeSetNumCols(v, 8);
        pParse->nMem = 8;
        sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "id", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "seq", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "table", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 3, COLNAME_NAME, "from", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 4, COLNAME_NAME, "to", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 5, COLNAME_NAME, "on_update", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 6, COLNAME_NAME, "on_delete", SQLITE_STATIC);
        sqlite3VdbeSetColName(v, 7, COLNAME_NAME, "match", SQLITE_STATIC);
        while(pFK){
          int j;
          for(j=0; j<pFK->nCol; j++){
            char *zCol = pFK->aCol[j].zCol;
            char *zOnUpdate = (char *)actionName(pFK->updateConf);
            char *zOnDelete = (char *)actionName(pFK->deleteConf);
            sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
            sqlite3VdbeAddOp2(v, OP_Integer, j, 2);
            sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, pFK->zTo, 0);
            sqlite3VdbeAddOp4(v, OP_String8, 0, 4, 0,
                              pTab->aCol[pFK->aCol[j].iFrom].zName, 0);
            sqlite3VdbeAddOp4(v, zCol ? OP_String8 : OP_Null, 0, 5, 0, zCol, 0);
            sqlite3VdbeAddOp4(v, OP_String8, 0, 6, 0, zOnUpdate, 0);
            sqlite3VdbeAddOp4(v, OP_String8, 0, 7, 0, zOnDelete, 0);
            sqlite3VdbeAddOp4(v, OP_String8, 0, 8, 0, "NONE", 0);
            sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 8);
          }
          ++i;
          pFK = pFK->pNextFrom;
        }
      }
    }
  }else
#endif /* !defined(SQLITE_OMIT_FOREIGN_KEY) */

#ifndef NDEBUG
  if( sqlite3StrICmp(zLeft, "parser_trace")==0 ){
    if( zRight ){
      if( getBoolean(zRight) ){
        sqlite3ParserTrace(stderr, "parser: ");
      }else{
        sqlite3ParserTrace(0, 0);
      }
    }
  }else
#endif

  /* Reinstall the LIKE and GLOB functions.  The variant of LIKE
  ** used will be case sensitive or not depending on the RHS.
  */
  if( sqlite3StrICmp(zLeft, "case_sensitive_like")==0 ){
    if( zRight ){
      sqlite3RegisterLikeFunctions(db, getBoolean(zRight));
    }
  }else

#ifndef SQLITE_INTEGRITY_CHECK_ERROR_MAX
# define SQLITE_INTEGRITY_CHECK_ERROR_MAX 100
#endif

#ifndef SQLITE_OMIT_INTEGRITY_CHECK
  /* Pragma "quick_check" is an experimental reduced version of 
  ** integrity_check designed to detect most database corruption
  ** without most of the overhead of a full integrity-check.
  */
  if( sqlite3StrICmp(zLeft, "integrity_check")==0
   || sqlite3StrICmp(zLeft, "quick_check")==0 
  ){
    int i, j, addr, mxErr;

    /* Code that appears at the end of the integrity check.  If no error
    ** messages have been generated, output OK.  Otherwise output the
    ** error message
    */
    static const VdbeOpList endCode[] = {
      { OP_AddImm,      1, 0,        0},    /* 0 */
      { OP_IfNeg,       1, 0,        0},    /* 1 */
      { OP_String8,     0, 3,        0},    /* 2 */
      { OP_ResultRow,   3, 1,        0},
    };

    int isQuick = (zLeft[0]=='q');

    /* Initialize the VDBE program */
    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
    pParse->nMem = 6;
    sqlite3VdbeSetNumCols(v, 1);
    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "integrity_check", SQLITE_STATIC);

    /* Set the maximum error count */
    mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
    if( zRight ){
      mxErr = atoi(zRight);
      if( mxErr<=0 ){
        mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
      }
    }
    sqlite3VdbeAddOp2(v, OP_Integer, mxErr, 1);  /* reg[1] holds errors left */

    /* Do an integrity check on each database file */
    for(i=0; i<db->nDb; i++){
      HashElem *x;
      Hash *pTbls;
      int cnt = 0;

      if( OMIT_TEMPDB && i==1 ) continue;

      sqlite3CodeVerifySchema(pParse, i);
      addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1); /* Halt if out of errors */
      sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
      sqlite3VdbeJumpHere(v, addr);

      /* Do an integrity check of the B-Tree
      **
      ** Begin by filling registers 2, 3, ... with the root pages numbers
      ** for all tables and indices in the database.
      */
      pTbls = &db->aDb[i].pSchema->tblHash;
      for(x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
        Table *pTab = sqliteHashData(x);
        Index *pIdx;
        sqlite3VdbeAddOp2(v, OP_Integer, pTab->tnum, 2+cnt);
        cnt++;
        for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
          sqlite3VdbeAddOp2(v, OP_Integer, pIdx->tnum, 2+cnt);
          cnt++;
        }
      }

      /* Make sure sufficient number of registers have been allocated */
      if( pParse->nMem < cnt+4 ){
        pParse->nMem = cnt+4;
      }

      /* Do the b-tree integrity checks */
      sqlite3VdbeAddOp3(v, OP_IntegrityCk, 2, cnt, 1);
      sqlite3VdbeChangeP5(v, (u8)i);
      addr = sqlite3VdbeAddOp1(v, OP_IsNull, 2);
      sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
         sqlite3MPrintf(db, "*** in database %s ***\n", db->aDb[i].zName),
         P4_DYNAMIC);
      sqlite3VdbeAddOp3(v, OP_Move, 2, 4, 1);
      sqlite3VdbeAddOp3(v, OP_Concat, 4, 3, 2);
      sqlite3VdbeAddOp2(v, OP_ResultRow, 2, 1);
      sqlite3VdbeJumpHere(v, addr);

      /* Make sure all the indices are constructed correctly.
      */
      for(x=sqliteHashFirst(pTbls); x && !isQuick; x=sqliteHashNext(x)){
        Table *pTab = sqliteHashData(x);
        Index *pIdx;
        int loopTop;

        if( pTab->pIndex==0 ) continue;
        addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);  /* Stop if out of errors */
        sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
        sqlite3VdbeJumpHere(v, addr);
        sqlite3OpenTableAndIndices(pParse, pTab, 1, OP_OpenRead);
        sqlite3VdbeAddOp2(v, OP_Integer, 0, 2);  /* reg(2) will count entries */
        loopTop = sqlite3VdbeAddOp2(v, OP_Rewind, 1, 0);
        sqlite3VdbeAddOp2(v, OP_AddImm, 2, 1);   /* increment entry count */
        for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
          int jmp2;
          static const VdbeOpList idxErr[] = {
            { OP_AddImm,      1, -1,  0},
            { OP_String8,     0,  3,  0},    /* 1 */
            { OP_Rowid,       1,  4,  0},
            { OP_String8,     0,  5,  0},    /* 3 */
            { OP_String8,     0,  6,  0},    /* 4 */
            { OP_Concat,      4,  3,  3},
            { OP_Concat,      5,  3,  3},
            { OP_Concat,      6,  3,  3},
            { OP_ResultRow,   3,  1,  0},
            { OP_IfPos,       1,  0,  0},    /* 9 */
            { OP_Halt,        0,  0,  0},
          };
          sqlite3GenerateIndexKey(pParse, pIdx, 1, 3, 1);
          jmp2 = sqlite3VdbeAddOp3(v, OP_Found, j+2, 0, 3);
          addr = sqlite3VdbeAddOpList(v, ArraySize(idxErr), idxErr);
          sqlite3VdbeChangeP4(v, addr+1, "rowid ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+3, " missing from index ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+4, pIdx->zName, P4_STATIC);
          sqlite3VdbeJumpHere(v, addr+9);
          sqlite3VdbeJumpHere(v, jmp2);
        }
        sqlite3VdbeAddOp2(v, OP_Next, 1, loopTop+1);
        sqlite3VdbeJumpHere(v, loopTop);
        for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
          static const VdbeOpList cntIdx[] = {
             { OP_Integer,      0,  3,  0},
             { OP_Rewind,       0,  0,  0},  /* 1 */
             { OP_AddImm,       3,  1,  0},
             { OP_Next,         0,  0,  0},  /* 3 */
             { OP_Eq,           2,  0,  3},  /* 4 */
             { OP_AddImm,       1, -1,  0},
             { OP_String8,      0,  2,  0},  /* 6 */
             { OP_String8,      0,  3,  0},  /* 7 */
             { OP_Concat,       3,  2,  2},
             { OP_ResultRow,    2,  1,  0},
          };
          addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);
          sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
          sqlite3VdbeJumpHere(v, addr);
          addr = sqlite3VdbeAddOpList(v, ArraySize(cntIdx), cntIdx);
          sqlite3VdbeChangeP1(v, addr+1, j+2);
          sqlite3VdbeChangeP2(v, addr+1, addr+4);
          sqlite3VdbeChangeP1(v, addr+3, j+2);
          sqlite3VdbeChangeP2(v, addr+3, addr+2);
          sqlite3VdbeJumpHere(v, addr+4);
          sqlite3VdbeChangeP4(v, addr+6, 
                     "wrong # of entries in index ", P4_STATIC);
          sqlite3VdbeChangeP4(v, addr+7, pIdx->zName, P4_STATIC);
        }
      } 
    }
    addr = sqlite3VdbeAddOpList(v, ArraySize(endCode), endCode);
    sqlite3VdbeChangeP2(v, addr, -mxErr);
    sqlite3VdbeJumpHere(v, addr+1);
    sqlite3VdbeChangeP4(v, addr+2, "ok", P4_STATIC);
  }else
#endif /* SQLITE_OMIT_INTEGRITY_CHECK */

#ifndef SQLITE_OMIT_UTF16
  /*
  **   PRAGMA encoding
  **   PRAGMA encoding = "utf-8"|"utf-16"|"utf-16le"|"utf-16be"
