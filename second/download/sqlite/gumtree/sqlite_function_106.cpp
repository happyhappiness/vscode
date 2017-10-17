int sqlite3CodeSubselect(
  Parse *pParse,          /* Parsing context */
  Expr *pExpr,            /* The IN, SELECT, or EXISTS operator */
  int rHasNullFlag,       /* Register that records whether NULLs exist in RHS */
  int isRowid             /* If true, LHS of IN operator is a rowid */
){
  int jmpIfDynamic = -1;                      /* One-time test address */
  int rReg = 0;                           /* Register storing resulting */
  Vdbe *v = sqlite3GetVdbe(pParse);
  if( NEVER(v==0) ) return 0;
  sqlite3ExprCachePush(pParse);

  /* The evaluation of the IN/EXISTS/SELECT must be repeated every time it
  ** is encountered if any of the following is true:
  **
  **    *  The right-hand side is a correlated subquery
  **    *  The right-hand side is an expression list containing variables
  **    *  We are inside a trigger
  **
  ** If all of the above are false, then we can run this code just once
  ** save the results, and reuse the same result on subsequent invocations.
  */
  if( !ExprHasProperty(pExpr, EP_VarSelect) ){
    jmpIfDynamic = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
  }

#ifndef SQLITE_OMIT_EXPLAIN
  if( pParse->explain==2 ){
    char *zMsg = sqlite3MPrintf(pParse->db, "EXECUTE %s%s SUBQUERY %d",
        jmpIfDynamic>=0?"":"CORRELATED ",
        pExpr->op==TK_IN?"LIST":"SCALAR",
        pParse->iNextSelectId
    );
    sqlite3VdbeAddOp4(v, OP_Explain, pParse->iSelectId, 0, 0, zMsg, P4_DYNAMIC);
  }
#endif

  switch( pExpr->op ){
    case TK_IN: {
      int addr;                   /* Address of OP_OpenEphemeral instruction */
      Expr *pLeft = pExpr->pLeft; /* the LHS of the IN operator */
      KeyInfo *pKeyInfo = 0;      /* Key information */
      int nVal;                   /* Size of vector pLeft */
      
      nVal = sqlite3ExprVectorSize(pLeft);
      assert( !isRowid || nVal==1 );

      /* Whether this is an 'x IN(SELECT...)' or an 'x IN(<exprlist>)'
      ** expression it is handled the same way.  An ephemeral table is 
      ** filled with index keys representing the results from the 
      ** SELECT or the <exprlist>.
      **
      ** If the 'x' expression is a column value, or the SELECT...
      ** statement returns a column value, then the affinity of that
      ** column is used to build the index keys. If both 'x' and the
      ** SELECT... statement are columns, then numeric affinity is used
      ** if either column has NUMERIC or INTEGER affinity. If neither
      ** 'x' nor the SELECT... statement are columns, then numeric affinity
      ** is used.
      */
      pExpr->iTable = pParse->nTab++;
      addr = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, 
          pExpr->iTable, (isRowid?0:nVal));
      pKeyInfo = isRowid ? 0 : sqlite3KeyInfoAlloc(pParse->db, nVal, 1);

      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
        /* Case 1:     expr IN (SELECT ...)
        **
        ** Generate code to write the results of the select into the temporary
        ** table allocated and opened above.
        */
        Select *pSelect = pExpr->x.pSelect;
        ExprList *pEList = pSelect->pEList;

        assert( !isRowid );
        /* If the LHS and RHS of the IN operator do not match, that
        ** error will have been caught long before we reach this point. */
        if( ALWAYS(pEList->nExpr==nVal) ){
          SelectDest dest;
          int i;
          sqlite3SelectDestInit(&dest, SRT_Set, pExpr->iTable);
          dest.zAffSdst = exprINAffinity(pParse, pExpr);
          pSelect->iLimit = 0;
          testcase( pSelect->selFlags & SF_Distinct );
          testcase( pKeyInfo==0 ); /* Caused by OOM in sqlite3KeyInfoAlloc() */
          if( sqlite3Select(pParse, pSelect, &dest) ){
            sqlite3DbFree(pParse->db, dest.zAffSdst);
            sqlite3KeyInfoUnref(pKeyInfo);
            return 0;
          }
          sqlite3DbFree(pParse->db, dest.zAffSdst);
          assert( pKeyInfo!=0 ); /* OOM will cause exit after sqlite3Select() */
          assert( pEList!=0 );
          assert( pEList->nExpr>0 );
          assert( sqlite3KeyInfoIsWriteable(pKeyInfo) );
          for(i=0; i<nVal; i++){
            Expr *p = sqlite3VectorFieldSubexpr(pLeft, i);
            pKeyInfo->aColl[i] = sqlite3BinaryCompareCollSeq(
                pParse, p, pEList->a[i].pExpr
            );
          }
        }
      }else if( ALWAYS(pExpr->x.pList!=0) ){
        /* Case 2:     expr IN (exprlist)
        **
        ** For each expression, build an index key from the evaluation and
        ** store it in the temporary table. If <expr> is a column, then use
        ** that columns affinity when building index keys. If <expr> is not
        ** a column, use numeric affinity.
        */
        char affinity;            /* Affinity of the LHS of the IN */
        int i;
        ExprList *pList = pExpr->x.pList;
        struct ExprList_item *pItem;
        int r1, r2, r3;

        affinity = sqlite3ExprAffinity(pLeft);
        if( !affinity ){
          affinity = SQLITE_AFF_BLOB;
        }
        if( pKeyInfo ){
          assert( sqlite3KeyInfoIsWriteable(pKeyInfo) );
          pKeyInfo->aColl[0] = sqlite3ExprCollSeq(pParse, pExpr->pLeft);
        }

        /* Loop through each expression in <exprlist>. */
        r1 = sqlite3GetTempReg(pParse);
        r2 = sqlite3GetTempReg(pParse);
        if( isRowid ) sqlite3VdbeAddOp2(v, OP_Null, 0, r2);
        for(i=pList->nExpr, pItem=pList->a; i>0; i--, pItem++){
          Expr *pE2 = pItem->pExpr;
          int iValToIns;

          /* If the expression is not constant then we will need to
          ** disable the test that was generated above that makes sure
          ** this code only executes once.  Because for a non-constant
          ** expression we need to rerun this code each time.
          */
          if( jmpIfDynamic>=0 && !sqlite3ExprIsConstant(pE2) ){
            sqlite3VdbeChangeToNoop(v, jmpIfDynamic);
            jmpIfDynamic = -1;
          }

          /* Evaluate the expression and insert it into the temp table */
          if( isRowid && sqlite3ExprIsInteger(pE2, &iValToIns) ){
            sqlite3VdbeAddOp3(v, OP_InsertInt, pExpr->iTable, r2, iValToIns);
          }else{
            r3 = sqlite3ExprCodeTarget(pParse, pE2, r1);
            if( isRowid ){
              sqlite3VdbeAddOp2(v, OP_MustBeInt, r3,
                                sqlite3VdbeCurrentAddr(v)+2);
              VdbeCoverage(v);
              sqlite3VdbeAddOp3(v, OP_Insert, pExpr->iTable, r2, r3);
            }else{
              sqlite3VdbeAddOp4(v, OP_MakeRecord, r3, 1, r2, &affinity, 1);
              sqlite3ExprCacheAffinityChange(pParse, r3, 1);
              sqlite3VdbeAddOp4Int(v, OP_IdxInsert, pExpr->iTable, r2, r3, 1);
            }
          }
        }
        sqlite3ReleaseTempReg(pParse, r1);
        sqlite3ReleaseTempReg(pParse, r2);
      }
      if( pKeyInfo ){
        sqlite3VdbeChangeP4(v, addr, (void *)pKeyInfo, P4_KEYINFO);
      }
      break;
    }

    case TK_EXISTS:
    case TK_SELECT:
    default: {
      /* Case 3:    (SELECT ... FROM ...)
      **     or:    EXISTS(SELECT ... FROM ...)
      **
      ** For a SELECT, generate code to put the values for all columns of
      ** the first row into an array of registers and return the index of
      ** the first register.
      **
      ** If this is an EXISTS, write an integer 0 (not exists) or 1 (exists)
      ** into a register and return that register number.
      **
      ** In both cases, the query is augmented with "LIMIT 1".  Any 
      ** preexisting limit is discarded in place of the new LIMIT 1.
      */
      Select *pSel;                         /* SELECT statement to encode */
      SelectDest dest;                      /* How to deal with SELECT result */
      int nReg;                             /* Registers to allocate */

      testcase( pExpr->op==TK_EXISTS );
      testcase( pExpr->op==TK_SELECT );
      assert( pExpr->op==TK_EXISTS || pExpr->op==TK_SELECT );
      assert( ExprHasProperty(pExpr, EP_xIsSelect) );

      pSel = pExpr->x.pSelect;
      nReg = pExpr->op==TK_SELECT ? pSel->pEList->nExpr : 1;
      sqlite3SelectDestInit(&dest, 0, pParse->nMem+1);
      pParse->nMem += nReg;
      if( pExpr->op==TK_SELECT ){
        dest.eDest = SRT_Mem;
        dest.iSdst = dest.iSDParm;
        dest.nSdst = nReg;
        sqlite3VdbeAddOp3(v, OP_Null, 0, dest.iSDParm, dest.iSDParm+nReg-1);
        VdbeComment((v, "Init subquery result"));
      }else{
        dest.eDest = SRT_Exists;
        sqlite3VdbeAddOp2(v, OP_Integer, 0, dest.iSDParm);
        VdbeComment((v, "Init EXISTS result"));
      }
      sqlite3ExprDelete(pParse->db, pSel->pLimit);
      pSel->pLimit = sqlite3ExprAlloc(pParse->db, TK_INTEGER,
                                  &sqlite3IntTokens[1], 0);
      pSel->iLimit = 0;
      pSel->selFlags &= ~SF_MultiValue;
      if( sqlite3Select(pParse, pSel, &dest) ){
        return 0;
      }
      rReg = dest.iSDParm;
      ExprSetVVAProperty(pExpr, EP_NoReduce);
      break;
    }
  }

  if( rHasNullFlag ){
    sqlite3SetHasNullFlag(v, pExpr->iTable, rHasNullFlag);
  }

  if( jmpIfDynamic>=0 ){
    sqlite3VdbeJumpHere(v, jmpIfDynamic);
  }
  sqlite3ExprCachePop(pParse);

  return rReg;
}