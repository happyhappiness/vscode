void sqlite3GenerateConstraintChecks(
  Parse *pParse,       /* The parser context */
  Table *pTab,         /* The table being inserted or updated */
  int *aRegIdx,        /* Use register aRegIdx[i] for index i.  0 for unused */
  int iDataCur,        /* Canonical data cursor (main table or PK index) */
  int iIdxCur,         /* First index cursor */
  int regNewData,      /* First register in a range holding values to insert */
  int regOldData,      /* Previous content.  0 for INSERTs */
  u8 pkChng,           /* Non-zero if the rowid or PRIMARY KEY changed */
  u8 overrideError,    /* Override onError to this if not OE_Default */
  int ignoreDest,      /* Jump to this label on an OE_Ignore resolution */
  int *pbMayReplace,   /* OUT: Set to true if constraint may cause a replace */
  int *aiChng          /* column i is unchanged if aiChng[i]<0 */
){
  Vdbe *v;             /* VDBE under constrution */
  Index *pIdx;         /* Pointer to one of the indices */
  Index *pPk = 0;      /* The PRIMARY KEY index */
  sqlite3 *db;         /* Database connection */
  int i;               /* loop counter */
  int ix;              /* Index loop counter */
  int nCol;            /* Number of columns */
  int onError;         /* Conflict resolution strategy */
  int addr1;           /* Address of jump instruction */
  int seenReplace = 0; /* True if REPLACE is used to resolve INT PK conflict */
  int nPkField;        /* Number of fields in PRIMARY KEY. 1 for ROWID tables */
  int ipkTop = 0;      /* Top of the rowid change constraint check */
  int ipkBottom = 0;   /* Bottom of the rowid change constraint check */
  u8 isUpdate;         /* True if this is an UPDATE operation */
  u8 bAffinityDone = 0;  /* True if the OP_Affinity operation has been run */

  isUpdate = regOldData!=0;
  db = pParse->db;
  v = sqlite3GetVdbe(pParse);
  assert( v!=0 );
  assert( pTab->pSelect==0 );  /* This table is not a VIEW */
  nCol = pTab->nCol;
  
  /* pPk is the PRIMARY KEY index for WITHOUT ROWID tables and NULL for
  ** normal rowid tables.  nPkField is the number of key fields in the 
  ** pPk index or 1 for a rowid table.  In other words, nPkField is the
  ** number of fields in the true primary key of the table. */
  if( HasRowid(pTab) ){
    pPk = 0;
    nPkField = 1;
  }else{
    pPk = sqlite3PrimaryKeyIndex(pTab);
    nPkField = pPk->nKeyCol;
  }

  /* Record that this module has started */
  VdbeModuleComment((v, "BEGIN: GenCnstCks(%d,%d,%d,%d,%d)",
                     iDataCur, iIdxCur, regNewData, regOldData, pkChng));

  /* Test all NOT NULL constraints.
  */
  for(i=0; i<nCol; i++){
    if( i==pTab->iPKey ){
      continue;        /* ROWID is never NULL */
    }
    if( aiChng && aiChng[i]<0 ){
      /* Don't bother checking for NOT NULL on columns that do not change */
      continue;
    }
    onError = pTab->aCol[i].notNull;
    if( onError==OE_None ) continue;  /* This column is allowed to be NULL */
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
      case OE_Abort:
        sqlite3MayAbort(pParse);
        /* Fall through */
      case OE_Rollback:
      case OE_Fail: {
        char *zMsg = sqlite3MPrintf(db, "%s.%s", pTab->zName,
                                    pTab->aCol[i].zName);
        sqlite3VdbeAddOp3(v, OP_HaltIfNull, SQLITE_CONSTRAINT_NOTNULL, onError,
                          regNewData+1+i);
        sqlite3VdbeAppendP4(v, zMsg, P4_DYNAMIC);
        sqlite3VdbeChangeP5(v, P5_ConstraintNotNull);
        VdbeCoverage(v);
        break;
      }
      case OE_Ignore: {
        sqlite3VdbeAddOp2(v, OP_IsNull, regNewData+1+i, ignoreDest);
        VdbeCoverage(v);
        break;
      }
      default: {
        assert( onError==OE_Replace );
        addr1 = sqlite3VdbeAddOp1(v, OP_NotNull, regNewData+1+i);
           VdbeCoverage(v);
        sqlite3ExprCode(pParse, pTab->aCol[i].pDflt, regNewData+1+i);
        sqlite3VdbeJumpHere(v, addr1);
        break;
      }
    }
  }

  /* Test all CHECK constraints
  */
#ifndef SQLITE_OMIT_CHECK
  if( pTab->pCheck && (db->flags & SQLITE_IgnoreChecks)==0 ){
    ExprList *pCheck = pTab->pCheck;
    pParse->iSelfTab = -(regNewData+1);
    onError = overrideError!=OE_Default ? overrideError : OE_Abort;
    for(i=0; i<pCheck->nExpr; i++){
      int allOk;
      Expr *pExpr = pCheck->a[i].pExpr;
      if( aiChng && checkConstraintUnchanged(pExpr, aiChng, pkChng) ) continue;
      allOk = sqlite3VdbeMakeLabel(v);
      sqlite3ExprIfTrue(pParse, pExpr, allOk, SQLITE_JUMPIFNULL);
      if( onError==OE_Ignore ){
        sqlite3VdbeGoto(v, ignoreDest);
      }else{
        char *zName = pCheck->a[i].zName;
        if( zName==0 ) zName = pTab->zName;
        if( onError==OE_Replace ) onError = OE_Abort; /* IMP: R-15569-63625 */
        sqlite3HaltConstraint(pParse, SQLITE_CONSTRAINT_CHECK,
                              onError, zName, P4_TRANSIENT,
                              P5_ConstraintCheck);
      }
      sqlite3VdbeResolveLabel(v, allOk);
    }
    pParse->iSelfTab = 0;
  }
#endif /* !defined(SQLITE_OMIT_CHECK) */

  /* If rowid is changing, make sure the new rowid does not previously
  ** exist in the table.
  */
  if( pkChng && pPk==0 ){
    int addrRowidOk = sqlite3VdbeMakeLabel(v);

    /* Figure out what action to take in case of a rowid collision */
    onError = pTab->keyConf;
    if( overrideError!=OE_Default ){
      onError = overrideError;
    }else if( onError==OE_Default ){
      onError = OE_Abort;
    }

    if( isUpdate ){
      /* pkChng!=0 does not mean that the rowid has changed, only that
      ** it might have changed.  Skip the conflict logic below if the rowid
      ** is unchanged. */
      sqlite3VdbeAddOp3(v, OP_Eq, regNewData, addrRowidOk, regOldData);
      sqlite3VdbeChangeP5(v, SQLITE_NOTNULL);
      VdbeCoverage(v);
    }

    /* If the response to a rowid conflict is REPLACE but the response
    ** to some other UNIQUE constraint is FAIL or IGNORE, then we need
    ** to defer the running of the rowid conflict checking until after
    ** the UNIQUE constraints have run.
    */
    if( onError==OE_Replace && overrideError!=OE_Replace ){
      for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
        if( pIdx->onError==OE_Ignore || pIdx->onError==OE_Fail ){
          ipkTop = sqlite3VdbeAddOp0(v, OP_Goto);
          break;
        }
      }
    }

    /* Check to see if the new rowid already exists in the table.  Skip
    ** the following conflict logic if it does not. */
    sqlite3VdbeAddOp3(v, OP_NotExists, iDataCur, addrRowidOk, regNewData);
    VdbeCoverage(v);

    /* Generate code that deals with a rowid collision */
    switch( onError ){
      default: {
        onError = OE_Abort;
        /* Fall thru into the next case */
      }
      case OE_Rollback:
      case OE_Abort:
      case OE_Fail: {
        sqlite3RowidConstraint(pParse, onError, pTab);
        break;
      }
      case OE_Replace: {
        /* If there are DELETE triggers on this table and the
        ** recursive-triggers flag is set, call GenerateRowDelete() to
        ** remove the conflicting row from the table. This will fire
        ** the triggers and remove both the table and index b-tree entries.
        **
        ** Otherwise, if there are no triggers or the recursive-triggers
        ** flag is not set, but the table has one or more indexes, call 
        ** GenerateRowIndexDelete(). This removes the index b-tree entries 
        ** only. The table b-tree entry will be replaced by the new entry 
        ** when it is inserted.  
        **
        ** If either GenerateRowDelete() or GenerateRowIndexDelete() is called,
        ** also invoke MultiWrite() to indicate that this VDBE may require
        ** statement rollback (if the statement is aborted after the delete
        ** takes place). Earlier versions called sqlite3MultiWrite() regardless,
        ** but being more selective here allows statements like:
        **
        **   REPLACE INTO t(rowid) VALUES($newrowid)
        **
        ** to run without a statement journal if there are no indexes on the
        ** table.
        */
        Trigger *pTrigger = 0;
        if( db->flags&SQLITE_RecTriggers ){
          pTrigger = sqlite3TriggersExist(pParse, pTab, TK_DELETE, 0, 0);
        }
        if( pTrigger || sqlite3FkRequired(pParse, pTab, 0, 0) ){
          sqlite3MultiWrite(pParse);
          sqlite3GenerateRowDelete(pParse, pTab, pTrigger, iDataCur, iIdxCur,
                                   regNewData, 1, 0, OE_Replace, 1, -1);
        }else{
#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
          if( HasRowid(pTab) ){
            /* This OP_Delete opcode fires the pre-update-hook only. It does
            ** not modify the b-tree. It is more efficient to let the coming
            ** OP_Insert replace the existing entry than it is to delete the
            ** existing entry and then insert a new one. */
            sqlite3VdbeAddOp2(v, OP_Delete, iDataCur, OPFLAG_ISNOOP);
            sqlite3VdbeAppendP4(v, pTab, P4_TABLE);
          }
#endif /* SQLITE_ENABLE_PREUPDATE_HOOK */
          if( pTab->pIndex ){
            sqlite3MultiWrite(pParse);
            sqlite3GenerateRowIndexDelete(pParse, pTab, iDataCur, iIdxCur,0,-1);
          }
        }
        seenReplace = 1;
        break;
      }
      case OE_Ignore: {
        /*assert( seenReplace==0 );*/
        sqlite3VdbeGoto(v, ignoreDest);
        break;
      }
    }
    sqlite3VdbeResolveLabel(v, addrRowidOk);
    if( ipkTop ){
      ipkBottom = sqlite3VdbeAddOp0(v, OP_Goto);
      sqlite3VdbeJumpHere(v, ipkTop);
    }
  }

  /* Test all UNIQUE constraints by creating entries for each UNIQUE
  ** index and making sure that duplicate entries do not already exist.
  ** Compute the revised record entries for indices as we go.
  **
  ** This loop also handles the case of the PRIMARY KEY index for a
  ** WITHOUT ROWID table.
  */
  for(ix=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, ix++){
    int regIdx;          /* Range of registers hold conent for pIdx */
    int regR;            /* Range of registers holding conflicting PK */
    int iThisCur;        /* Cursor for this UNIQUE index */
    int addrUniqueOk;    /* Jump here if the UNIQUE constraint is satisfied */

    if( aRegIdx[ix]==0 ) continue;  /* Skip indices that do not change */
    if( bAffinityDone==0 ){
      sqlite3TableAffinity(v, pTab, regNewData+1);
      bAffinityDone = 1;
    }
    iThisCur = iIdxCur+ix;
    addrUniqueOk = sqlite3VdbeMakeLabel(v);

    /* Skip partial indices for which the WHERE clause is not true */
    if( pIdx->pPartIdxWhere ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, aRegIdx[ix]);
      pParse->iSelfTab = -(regNewData+1);
      sqlite3ExprIfFalseDup(pParse, pIdx->pPartIdxWhere, addrUniqueOk,
                            SQLITE_JUMPIFNULL);
      pParse->iSelfTab = 0;
    }

    /* Create a record for this index entry as it should appear after
    ** the insert or update.  Store that record in the aRegIdx[ix] register
    */
    regIdx = aRegIdx[ix]+1;
    for(i=0; i<pIdx->nColumn; i++){
      int iField = pIdx->aiColumn[i];
      int x;
      if( iField==XN_EXPR ){
        pParse->iSelfTab = -(regNewData+1);
        sqlite3ExprCodeCopy(pParse, pIdx->aColExpr->a[i].pExpr, regIdx+i);
        pParse->iSelfTab = 0;
        VdbeComment((v, "%s column %d", pIdx->zName, i));
      }else{
        if( iField==XN_ROWID || iField==pTab->iPKey ){
          x = regNewData;
        }else{
          x = iField + regNewData + 1;
        }
        sqlite3VdbeAddOp2(v, iField<0 ? OP_IntCopy : OP_SCopy, x, regIdx+i);
        VdbeComment((v, "%s", iField<0 ? "rowid" : pTab->aCol[iField].zName));
      }
    }
    sqlite3VdbeAddOp3(v, OP_MakeRecord, regIdx, pIdx->nColumn, aRegIdx[ix]);
    VdbeComment((v, "for %s", pIdx->zName));
#ifdef SQLITE_ENABLE_NULL_TRIM
    if( pIdx->idxType==2 ) sqlite3SetMakeRecordP5(v, pIdx->pTable);
#endif

    /* In an UPDATE operation, if this index is the PRIMARY KEY index 
    ** of a WITHOUT ROWID table and there has been no change the
    ** primary key, then no collision is possible.  The collision detection
    ** logic below can all be skipped. */
    if( isUpdate && pPk==pIdx && pkChng==0 ){
      sqlite3VdbeResolveLabel(v, addrUniqueOk);
      continue;
    }

    /* Find out what action to take in case there is a uniqueness conflict */
    onError = pIdx->onError;
    if( onError==OE_None ){ 
      sqlite3VdbeResolveLabel(v, addrUniqueOk);
      continue;  /* pIdx is not a UNIQUE index */
    }
    if( overrideError!=OE_Default ){
      onError = overrideError;
    }else if( onError==OE_Default ){
      onError = OE_Abort;
    }

    /* Collision detection may be omitted if all of the following are true:
    **   (1) The conflict resolution algorithm is REPLACE
    **   (2) The table is a WITHOUT ROWID table
    **   (3) There are no secondary indexes on the table
    **   (4) No delete triggers need to be fired if there is a conflict
    **   (5) No FK constraint counters need to be updated if a conflict occurs.
    */ 
    if( (ix==0 && pIdx->pNext==0)                   /* Condition 3 */
     && pPk==pIdx                                   /* Condition 2 */
     && onError==OE_Replace                         /* Condition 1 */
     && ( 0==(db->flags&SQLITE_RecTriggers) ||      /* Condition 4 */
          0==sqlite3TriggersExist(pParse, pTab, TK_DELETE, 0, 0))
     && ( 0==(db->flags&SQLITE_ForeignKeys) ||      /* Condition 5 */
         (0==pTab->pFKey && 0==sqlite3FkReferences(pTab)))
    ){
      sqlite3VdbeResolveLabel(v, addrUniqueOk);
      continue;
    }

    /* Check to see if the new index entry will be unique */
    sqlite3VdbeAddOp4Int(v, OP_NoConflict, iThisCur, addrUniqueOk,
                         regIdx, pIdx->nKeyCol); VdbeCoverage(v);

    /* Generate code to handle collisions */
    regR = (pIdx==pPk) ? regIdx : sqlite3GetTempRange(pParse, nPkField);
    if( isUpdate || onError==OE_Replace ){
      if( HasRowid(pTab) ){
        sqlite3VdbeAddOp2(v, OP_IdxRowid, iThisCur, regR);
        /* Conflict only if the rowid of the existing index entry
        ** is different from old-rowid */
        if( isUpdate ){
          sqlite3VdbeAddOp3(v, OP_Eq, regR, addrUniqueOk, regOldData);
          sqlite3VdbeChangeP5(v, SQLITE_NOTNULL);
          VdbeCoverage(v);
        }
      }else{
        int x;
        /* Extract the PRIMARY KEY from the end of the index entry and
        ** store it in registers regR..regR+nPk-1 */
        if( pIdx!=pPk ){
          for(i=0; i<pPk->nKeyCol; i++){
            assert( pPk->aiColumn[i]>=0 );
            x = sqlite3ColumnOfIndex(pIdx, pPk->aiColumn[i]);
            sqlite3VdbeAddOp3(v, OP_Column, iThisCur, x, regR+i);
            VdbeComment((v, "%s.%s", pTab->zName,
                         pTab->aCol[pPk->aiColumn[i]].zName));
          }
        }
        if( isUpdate ){
          /* If currently processing the PRIMARY KEY of a WITHOUT ROWID 
          ** table, only conflict if the new PRIMARY KEY values are actually
          ** different from the old.
          **
          ** For a UNIQUE index, only conflict if the PRIMARY KEY values
          ** of the matched index row are different from the original PRIMARY
          ** KEY values of this row before the update.  */
          int addrJump = sqlite3VdbeCurrentAddr(v)+pPk->nKeyCol;
          int op = OP_Ne;
          int regCmp = (IsPrimaryKeyIndex(pIdx) ? regIdx : regR);
  
          for(i=0; i<pPk->nKeyCol; i++){
            char *p4 = (char*)sqlite3LocateCollSeq(pParse, pPk->azColl[i]);
            x = pPk->aiColumn[i];
            assert( x>=0 );
            if( i==(pPk->nKeyCol-1) ){
              addrJump = addrUniqueOk;
              op = OP_Eq;
            }
            sqlite3VdbeAddOp4(v, op, 
                regOldData+1+x, addrJump, regCmp+i, p4, P4_COLLSEQ
            );
            sqlite3VdbeChangeP5(v, SQLITE_NOTNULL);
            VdbeCoverageIf(v, op==OP_Eq);
            VdbeCoverageIf(v, op==OP_Ne);
          }
        }
      }
    }

    /* Generate code that executes if the new index entry is not unique */
    assert( onError==OE_Rollback || onError==OE_Abort || onError==OE_Fail
        || onError==OE_Ignore || onError==OE_Replace );
    switch( onError ){
      case OE_Rollback:
      case OE_Abort:
      case OE_Fail: {
        sqlite3UniqueConstraint(pParse, onError, pIdx);
        break;
      }
      case OE_Ignore: {
        sqlite3VdbeGoto(v, ignoreDest);
        break;
      }
      default: {
        Trigger *pTrigger = 0;
        assert( onError==OE_Replace );
        sqlite3MultiWrite(pParse);
        if( db->flags&SQLITE_RecTriggers ){
          pTrigger = sqlite3TriggersExist(pParse, pTab, TK_DELETE, 0, 0);
        }
        sqlite3GenerateRowDelete(pParse, pTab, pTrigger, iDataCur, iIdxCur,
            regR, nPkField, 0, OE_Replace,
            (pIdx==pPk ? ONEPASS_SINGLE : ONEPASS_OFF), iThisCur);
        seenReplace = 1;
        break;
      }
    }
    sqlite3VdbeResolveLabel(v, addrUniqueOk);
    if( regR!=regIdx ) sqlite3ReleaseTempRange(pParse, regR, nPkField);
  }
  if( ipkTop ){
    sqlite3VdbeGoto(v, ipkTop+1);
    sqlite3VdbeJumpHere(v, ipkBottom);
  }
  
  *pbMayReplace = seenReplace;
  VdbeModuleComment((v, "END: GenCnstCks(%d)", seenReplace));
}