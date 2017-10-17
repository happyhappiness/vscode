void sqlite3GenerateConstraintChecks(
  Parse *pParse,      /* The parser context */
  Table *pTab,        /* the table into which we are inserting */
  int baseCur,        /* Index of a read/write cursor pointing at pTab */
  int regRowid,       /* Index of the range of input registers */
  int *aRegIdx,       /* Register used by each index.  0 for unused indices */
  int rowidChng,      /* True if the rowid might collide with existing entry */
  int isUpdate,       /* True for UPDATE, False for INSERT */
  int overrideError,  /* Override onError to this if not OE_Default */
  int ignoreDest,     /* Jump to this label on an OE_Ignore resolution */
  int *pbMayReplace   /* OUT: Set to true if constraint may cause a replace */
){
  int i;              /* loop counter */
  Vdbe *v;            /* VDBE under constrution */
  int nCol;           /* Number of columns */
  int onError;        /* Conflict resolution strategy */
  int j1;             /* Addresss of jump instruction */
  int j2 = 0, j3;     /* Addresses of jump instructions */
  int regData;        /* Register containing first data column */
  int iCur;           /* Table cursor number */
  Index *pIdx;         /* Pointer to one of the indices */
  int seenReplace = 0; /* True if REPLACE is used to resolve INT PK conflict */
  int hasTwoRowids = (isUpdate && rowidChng);

  v = sqlite3GetVdbe(pParse);
  assert( v!=0 );
  assert( pTab->pSelect==0 );  /* This table is not a VIEW */
  nCol = pTab->nCol;
  regData = regRowid + 1;


  /* Test all NOT NULL constraints.
  */
  for(i=0; i<nCol; i++){
    if( i==pTab->iPKey ){
      continue;
    }
    onError = pTab->aCol[i].notNull;
    if( onError==OE_None ) continue;
    if( overrideError!=OE_Default ){
      onError = overrideError;
    }else if( onError==OE_Default ){
      onError = OE_Abort;
    }
    if( onError==OE_Replace && pTab->aCol[i].pDflt==0 ){
      onError = OE_Abort;
    }
    assert( onError==OE_Rollback || onError==OE_Abort || onError==OE_Fail
        || onError==OE_Ignore || onError==OE_Replace );
    switch( onError ){
      case OE_Rollback:
      case OE_Abort:
      case OE_Fail: {
        char *zMsg;
        j1 = sqlite3VdbeAddOp3(v, OP_HaltIfNull,
                                  SQLITE_CONSTRAINT, onError, regData+i);
        zMsg = sqlite3MPrintf(pParse->db, "%s.%s may not be NULL",
                              pTab->zName, pTab->aCol[i].zName);
        sqlite3VdbeChangeP4(v, -1, zMsg, P4_DYNAMIC);
        break;
      }
      case OE_Ignore: {
        sqlite3VdbeAddOp2(v, OP_IsNull, regData+i, ignoreDest);
        break;
      }
      default: {
        assert( onError==OE_Replace );
        j1 = sqlite3VdbeAddOp1(v, OP_NotNull, regData+i);
        sqlite3ExprCode(pParse, pTab->aCol[i].pDflt, regData+i);
        sqlite3VdbeJumpHere(v, j1);
        break;
      }
    }
  }

  /* Test all CHECK constraints
  */
#ifndef SQLITE_OMIT_CHECK
  if( pTab->pCheck && (pParse->db->flags & SQLITE_IgnoreChecks)==0 ){
    int allOk = sqlite3VdbeMakeLabel(v);
    pParse->ckBase = regData;
    sqlite3ExprIfTrue(pParse, pTab->pCheck, allOk, SQLITE_JUMPIFNULL);
    onError = overrideError!=OE_Default ? overrideError : OE_Abort;
    if( onError==OE_Ignore ){
      sqlite3VdbeAddOp2(v, OP_Goto, 0, ignoreDest);
    }else{
      sqlite3VdbeAddOp2(v, OP_Halt, SQLITE_CONSTRAINT, onError);
    }
    sqlite3VdbeResolveLabel(v, allOk);
  }
#endif /* !defined(SQLITE_OMIT_CHECK) */

  /* If we have an INTEGER PRIMARY KEY, make sure the primary key
  ** of the new record does not previously exist.  Except, if this
  ** is an UPDATE and the primary key is not changing, that is OK.
  */
  if( rowidChng ){
    onError = pTab->keyConf;
    if( overrideError!=OE_Default ){
      onError = overrideError;
    }else if( onError==OE_Default ){
      onError = OE_Abort;
    }
    
    if( onError!=OE_Replace || pTab->pIndex ){
      if( isUpdate ){
        j2 = sqlite3VdbeAddOp3(v, OP_Eq, regRowid, 0, regRowid-1);
      }
      j3 = sqlite3VdbeAddOp3(v, OP_NotExists, baseCur, 0, regRowid);
      switch( onError ){
        default: {
          onError = OE_Abort;
          /* Fall thru into the next case */
        }
        case OE_Rollback:
        case OE_Abort:
        case OE_Fail: {
          sqlite3VdbeAddOp4(v, OP_Halt, SQLITE_CONSTRAINT, onError, 0,
                           "PRIMARY KEY must be unique", P4_STATIC);
          break;
        }
        case OE_Replace: {
          sqlite3GenerateRowIndexDelete(pParse, pTab, baseCur, 0);
          seenReplace = 1;
          break;
        }
        case OE_Ignore: {
          assert( seenReplace==0 );
          sqlite3VdbeAddOp2(v, OP_Goto, 0, ignoreDest);
          break;
        }
      }
      sqlite3VdbeJumpHere(v, j3);
      if( isUpdate ){
        sqlite3VdbeJumpHere(v, j2);
      }
    }
  }

  /* Test all UNIQUE constraints by creating entries for each UNIQUE
  ** index and making sure that duplicate entries do not already exist.
  ** Add the new records to the indices as we go.
  */
  for(iCur=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, iCur++){
    int regIdx;
    int regR;

    if( aRegIdx[iCur]==0 ) continue;  /* Skip unused indices */

    /* Create a key for accessing the index entry */
    regIdx = sqlite3GetTempRange(pParse, pIdx->nColumn+1);
    for(i=0; i<pIdx->nColumn; i++){
      int idx = pIdx->aiColumn[i];
      if( idx==pTab->iPKey ){
        sqlite3VdbeAddOp2(v, OP_SCopy, regRowid, regIdx+i);
      }else{
        sqlite3VdbeAddOp2(v, OP_SCopy, regData+idx, regIdx+i);
      }
    }
    sqlite3VdbeAddOp2(v, OP_SCopy, regRowid, regIdx+i);
    sqlite3VdbeAddOp3(v, OP_MakeRecord, regIdx, pIdx->nColumn+1, aRegIdx[iCur]);
    sqlite3IndexAffinityStr(v, pIdx);
    sqlite3ExprCacheAffinityChange(pParse, regIdx, pIdx->nColumn+1);

    /* Find out what action to take in case there is an indexing conflict */
    onError = pIdx->onError;
    if( onError==OE_None ){ 
      sqlite3ReleaseTempRange(pParse, regIdx, pIdx->nColumn+1);
      continue;  /* pIdx is not a UNIQUE index */
    }
    if( overrideError!=OE_Default ){
      onError = overrideError;
    }else if( onError==OE_Default ){
      onError = OE_Abort;
    }
    if( seenReplace ){
      if( onError==OE_Ignore ) onError = OE_Replace;
      else if( onError==OE_Fail ) onError = OE_Abort;
    }
    

    /* Check to see if the new index entry will be unique */
    regR = sqlite3GetTempReg(pParse);
    sqlite3VdbeAddOp2(v, OP_SCopy, regRowid-hasTwoRowids, regR);
    j3 = sqlite3VdbeAddOp4(v, OP_IsUnique, baseCur+iCur+1, 0,
                           regR, SQLITE_INT_TO_PTR(regIdx),
                           P4_INT32);
    sqlite3ReleaseTempRange(pParse, regIdx, pIdx->nColumn+1);

    /* Generate code that executes if the new index entry is not unique */
    assert( onError==OE_Rollback || onError==OE_Abort || onError==OE_Fail
        || onError==OE_Ignore || onError==OE_Replace );
    switch( onError ){
      case OE_Rollback:
      case OE_Abort:
      case OE_Fail: {
        int j;
        StrAccum errMsg;
        const char *zSep;
        char *zErr;

        sqlite3StrAccumInit(&errMsg, 0, 0, 200);
        errMsg.db = pParse->db;
        zSep = pIdx->nColumn>1 ? "columns " : "column ";
        for(j=0; j<pIdx->nColumn; j++){
          char *zCol = pTab->aCol[pIdx->aiColumn[j]].zName;
          sqlite3StrAccumAppend(&errMsg, zSep, -1);
          zSep = ", ";
          sqlite3StrAccumAppend(&errMsg, zCol, -1);
        }
        sqlite3StrAccumAppend(&errMsg,
            pIdx->nColumn>1 ? " are not unique" : " is not unique", -1);
        zErr = sqlite3StrAccumFinish(&errMsg);
        sqlite3VdbeAddOp4(v, OP_Halt, SQLITE_CONSTRAINT, onError, 0, zErr, 0);
        sqlite3DbFree(errMsg.db, zErr);
        break;
      }
      case OE_Ignore: {
        assert( seenReplace==0 );
        sqlite3VdbeAddOp2(v, OP_Goto, 0, ignoreDest);
        break;
      }
      default: {
        assert( onError==OE_Replace );
        sqlite3GenerateRowDelete(pParse, pTab, baseCur, regR, 0);
        seenReplace = 1;
        break;
      }
    }
    sqlite3VdbeJumpHere(v, j3);
    sqlite3ReleaseTempReg(pParse, regR);
  }

  if( pbMayReplace ){
    *pbMayReplace = seenReplace;
  }
}