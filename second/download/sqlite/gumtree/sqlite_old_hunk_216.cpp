      assert( eDest==SRT_Discard );
      break;
    }
#endif
  }

  /* Jump to the end of the loop if the LIMIT is reached.
  */
  if( p->iLimit ){
    assert( pOrderBy==0 );  /* If there is an ORDER BY, the call to
                            ** pushOntoSorter() would have cleared p->iLimit */
    sqlite3VdbeAddOp2(v, OP_AddImm, p->iLimit, -1);
    sqlite3VdbeAddOp2(v, OP_IfZero, p->iLimit, iBreak);
  }
}

/*
** Given an expression list, generate a KeyInfo structure that records
** the collating sequence for each expression in that expression list.
**
** If the ExprList is an ORDER BY or GROUP BY clause then the resulting
** KeyInfo structure is appropriate for initializing a virtual index to
** implement that clause.  If the ExprList is the result set of a SELECT
** then the KeyInfo structure is appropriate for initializing a virtual
** index to implement a DISTINCT test.
**
** Space to hold the KeyInfo structure is obtain from malloc.  The calling
** function is responsible for seeing that this structure is eventually
** freed.  Add the KeyInfo structure to the P4 field of an opcode using
** P4_KEYINFO_HANDOFF is the usual way of dealing with this.
*/
static KeyInfo *keyInfoFromExprList(Parse *pParse, ExprList *pList){
  sqlite3 *db = pParse->db;
  int nExpr;
  KeyInfo *pInfo;
  struct ExprList_item *pItem;
  int i;

  nExpr = pList->nExpr;
  pInfo = sqlite3DbMallocZero(db, sizeof(*pInfo) + nExpr*(sizeof(CollSeq*)+1) );
  if( pInfo ){
    pInfo->aSortOrder = (u8*)&pInfo->aColl[nExpr];
    pInfo->nField = (u16)nExpr;
    pInfo->enc = ENC(db);
    pInfo->db = db;
    for(i=0, pItem=pList->a; i<nExpr; i++, pItem++){
      CollSeq *pColl;
      pColl = sqlite3ExprCollSeq(pParse, pItem->pExpr);
      if( !pColl ){
        pColl = db->pDfltColl;
      }
      pInfo->aColl[i] = pColl;
      pInfo->aSortOrder[i] = pItem->sortOrder;
    }
  }
  return pInfo;
}


/*
** If the inner loop was generated using a non-null pOrderBy argument,
** then the results were placed in a sorter.  After the loop is terminated
** we need to run the sorter and output the results.  The following
** routine generates the code needed to do that.
*/
static void generateSortTail(
  Parse *pParse,    /* Parsing context */
  Select *p,        /* The SELECT statement */
  Vdbe *v,          /* Generate code into this VDBE */
  int nColumn,      /* Number of columns of data */
  SelectDest *pDest /* Write the sorted results here */
){
  int addrBreak = sqlite3VdbeMakeLabel(v);     /* Jump here to exit loop */
  int addrContinue = sqlite3VdbeMakeLabel(v);  /* Jump here for next cycle */
  int addr;
  int iTab;
  int pseudoTab = 0;
  ExprList *pOrderBy = p->pOrderBy;

  int eDest = pDest->eDest;
  int iParm = pDest->iParm;

  int regRow;
  int regRowid;

  iTab = pOrderBy->iECursor;
  if( eDest==SRT_Output || eDest==SRT_Coroutine ){
    pseudoTab = pParse->nTab++;
    sqlite3VdbeAddOp3(v, OP_OpenPseudo, pseudoTab, eDest==SRT_Output, nColumn);
  }
  addr = 1 + sqlite3VdbeAddOp2(v, OP_Sort, iTab, addrBreak);
  codeOffset(v, p, addrContinue);
  regRow = sqlite3GetTempReg(pParse);
  regRowid = sqlite3GetTempReg(pParse);
  sqlite3VdbeAddOp3(v, OP_Column, iTab, pOrderBy->nExpr + 1, regRow);
  switch( eDest ){
    case SRT_Table:
    case SRT_EphemTab: {
      testcase( eDest==SRT_Table );
      testcase( eDest==SRT_EphemTab );
      sqlite3VdbeAddOp2(v, OP_NewRowid, iParm, regRowid);
      sqlite3VdbeAddOp3(v, OP_Insert, iParm, regRow, regRowid);
      sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case SRT_Set: {
      assert( nColumn==1 );
      sqlite3VdbeAddOp4(v, OP_MakeRecord, regRow, 1, regRowid, &p->affinity, 1);
      sqlite3ExprCacheAffinityChange(pParse, regRow, 1);
      sqlite3VdbeAddOp2(v, OP_IdxInsert, iParm, regRowid);
      break;
    }
    case SRT_Mem: {
      assert( nColumn==1 );
      sqlite3ExprCodeMove(pParse, regRow, iParm, 1);
      /* The LIMIT clause will terminate the loop for us */
      break;
    }
#endif
    default: {
      int i;
      assert( eDest==SRT_Output || eDest==SRT_Coroutine ); 
      testcase( eDest==SRT_Output );
      testcase( eDest==SRT_Coroutine );
      sqlite3VdbeAddOp2(v, OP_Integer, 1, regRowid);
      sqlite3VdbeAddOp3(v, OP_Insert, pseudoTab, regRow, regRowid);
      for(i=0; i<nColumn; i++){
        assert( regRow!=pDest->iMem+i );
        sqlite3VdbeAddOp3(v, OP_Column, pseudoTab, i, pDest->iMem+i);
      }
      if( eDest==SRT_Output ){
        sqlite3VdbeAddOp2(v, OP_ResultRow, pDest->iMem, nColumn);
        sqlite3ExprCacheAffinityChange(pParse, pDest->iMem, nColumn);
      }else{
        sqlite3VdbeAddOp1(v, OP_Yield, pDest->iParm);
      }
      break;
    }
  }
  sqlite3ReleaseTempReg(pParse, regRow);
  sqlite3ReleaseTempReg(pParse, regRowid);

  /* LIMIT has been implemented by the pushOntoSorter() routine.
  */
  assert( p->iLimit==0 );

  /* The bottom of the loop
  */
  sqlite3VdbeResolveLabel(v, addrContinue);
  sqlite3VdbeAddOp2(v, OP_Next, iTab, addr);
  sqlite3VdbeResolveLabel(v, addrBreak);
  if( eDest==SRT_Output || eDest==SRT_Coroutine ){
    sqlite3VdbeAddOp2(v, OP_Close, pseudoTab, 0);
  }
}

/*
** Return a pointer to a string containing the 'declaration type' of the
** expression pExpr. The string may be treated as static by the caller.
**
** The declaration type is the exact datatype definition extracted from the
** original CREATE TABLE statement if the expression is a column. The
** declaration type for a ROWID field is INTEGER. Exactly when an expression
** is considered a column can be complex in the presence of subqueries. The
** result-set expression in all of the following SELECT statements is 
** considered a column by this function.
