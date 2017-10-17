** to some integer key column of a table B-Tree. In this case, use an
** intkey B-Tree to store the set of IN(...) values instead of the usual
** (slower) variable length keys B-Tree.
**
** If rMayHaveNull is non-zero, that means that the operation is an IN
** (not a SELECT or EXISTS) and that the RHS might contains NULLs.
** Furthermore, the IN is in a WHERE clause and that we really want
** to iterate over the RHS of the IN operator in order to quickly locate
** all corresponding LHS elements.  All this routine does is initialize
** the register given by rMayHaveNull to NULL.  Calling routines will take
** care of changing this register value to non-NULL if the RHS is NULL-free.
**
** If rMayHaveNull is zero, that means that the subquery is being used
** for membership testing only.  There is no need to initialize any
** registers to indicate the presense or absence of NULLs on the RHS.
*/
#ifndef SQLITE_OMIT_SUBQUERY
void sqlite3CodeSubselect(
  Parse *pParse,          /* Parsing context */
  Expr *pExpr,            /* The IN, SELECT, or EXISTS operator */
  int rMayHaveNull,       /* Register that records whether NULLs exist in RHS */
  int isRowid             /* If true, LHS of IN operator is a rowid */
){
  int testAddr = 0;                       /* One-time test address */
  Vdbe *v = sqlite3GetVdbe(pParse);
  if( NEVER(v==0) ) return;
  sqlite3ExprCachePush(pParse);

  /* This code must be run in its entirety every time it is encountered
  ** if any of the following is true:
  **
  **    *  The right-hand side is a correlated subquery
  **    *  The right-hand side is an expression list containing variables
  **    *  We are inside a trigger
  **
  ** If all of the above are false, then we can run this code just once
  ** save the results, and reuse the same result on subsequent invocations.
  */
  if( !ExprHasAnyProperty(pExpr, EP_VarSelect) && !pParse->trigStack ){
    int mem = ++pParse->nMem;
    sqlite3VdbeAddOp1(v, OP_If, mem);
    testAddr = sqlite3VdbeAddOp2(v, OP_Integer, 1, mem);
    assert( testAddr>0 || pParse->db->mallocFailed );
  }

  switch( pExpr->op ){
    case TK_IN: {
      char affinity;
      KeyInfo keyInfo;
      int addr;        /* Address of OP_OpenEphemeral instruction */
      Expr *pLeft = pExpr->pLeft;

      if( rMayHaveNull ){
        sqlite3VdbeAddOp2(v, OP_Null, 0, rMayHaveNull);
      }

      affinity = sqlite3ExprAffinity(pLeft);

      /* Whether this is an 'x IN(SELECT...)' or an 'x IN(<exprlist>)'
      ** expression it is handled the same way. A virtual table is 
      ** filled with single-field index keys representing the results
      ** from the SELECT or the <exprlist>.
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
      addr = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, pExpr->iTable, !isRowid);
      memset(&keyInfo, 0, sizeof(keyInfo));
      keyInfo.nField = 1;

      if( ExprHasProperty(pExpr, EP_xIsSelect) ){
        /* Case 1:     expr IN (SELECT ...)
        **
        ** Generate code to write the results of the select into the temporary
        ** table allocated and opened above.
        */
        SelectDest dest;
        ExprList *pEList;

        assert( !isRowid );
        sqlite3SelectDestInit(&dest, SRT_Set, pExpr->iTable);
        dest.affinity = (u8)affinity;
        assert( (pExpr->iTable&0x0000FFFF)==pExpr->iTable );
        if( sqlite3Select(pParse, pExpr->x.pSelect, &dest) ){
          return;
        }
        pEList = pExpr->x.pSelect->pEList;
        if( ALWAYS(pEList!=0 && pEList->nExpr>0) ){ 
          keyInfo.aColl[0] = sqlite3BinaryCompareCollSeq(pParse, pExpr->pLeft,
              pEList->a[0].pExpr);
        }
      }else if( pExpr->x.pList!=0 ){
        /* Case 2:     expr IN (exprlist)
        **
        ** For each expression, build an index key from the evaluation and
        ** store it in the temporary table. If <expr> is a column, then use
        ** that columns affinity when building index keys. If <expr> is not
        ** a column, use numeric affinity.
        */
        int i;
        ExprList *pList = pExpr->x.pList;
        struct ExprList_item *pItem;
        int r1, r2, r3;

        if( !affinity ){
          affinity = SQLITE_AFF_NONE;
        }
        keyInfo.aColl[0] = sqlite3ExprCollSeq(pParse, pExpr->pLeft);

        /* Loop through each expression in <exprlist>. */
        r1 = sqlite3GetTempReg(pParse);
        r2 = sqlite3GetTempReg(pParse);
        sqlite3VdbeAddOp2(v, OP_Null, 0, r2);
        for(i=pList->nExpr, pItem=pList->a; i>0; i--, pItem++){
          Expr *pE2 = pItem->pExpr;

          /* If the expression is not constant then we will need to
          ** disable the test that was generated above that makes sure
          ** this code only executes once.  Because for a non-constant
          ** expression we need to rerun this code each time.
          */
          if( testAddr && !sqlite3ExprIsConstant(pE2) ){
            sqlite3VdbeChangeToNoop(v, testAddr-1, 2);
            testAddr = 0;
          }

          /* Evaluate the expression and insert it into the temp table */
          r3 = sqlite3ExprCodeTarget(pParse, pE2, r1);
          if( isRowid ){
            sqlite3VdbeAddOp2(v, OP_MustBeInt, r3, sqlite3VdbeCurrentAddr(v)+2);
            sqlite3VdbeAddOp3(v, OP_Insert, pExpr->iTable, r2, r3);
          }else{
            sqlite3VdbeAddOp4(v, OP_MakeRecord, r3, 1, r2, &affinity, 1);
            sqlite3ExprCacheAffinityChange(pParse, r3, 1);
            sqlite3VdbeAddOp2(v, OP_IdxInsert, pExpr->iTable, r2);
          }
        }
        sqlite3ReleaseTempReg(pParse, r1);
        sqlite3ReleaseTempReg(pParse, r2);
      }
      if( !isRowid ){
        sqlite3VdbeChangeP4(v, addr, (void *)&keyInfo, P4_KEYINFO);
      }
      break;
    }

    case TK_EXISTS:
    case TK_SELECT:
    default: {
      /* If this has to be a scalar SELECT.  Generate code to put the
      ** value of this select in a memory cell and record the number
      ** of the memory cell in iColumn.  If this is an EXISTS, write
      ** an integer 0 (not exists) or 1 (exists) into a memory cell
      ** and record that memory cell in iColumn.
      */
      static const Token one = { "1", 1 };  /* Token for literal value 1 */
      Select *pSel;                         /* SELECT statement to encode */
      SelectDest dest;                      /* How to deal with SELECt result */

      testcase( pExpr->op==TK_EXISTS );
      testcase( pExpr->op==TK_SELECT );
      assert( pExpr->op==TK_EXISTS || pExpr->op==TK_SELECT );

      assert( ExprHasProperty(pExpr, EP_xIsSelect) );
      pSel = pExpr->x.pSelect;
      sqlite3SelectDestInit(&dest, 0, ++pParse->nMem);
      if( pExpr->op==TK_SELECT ){
        dest.eDest = SRT_Mem;
        sqlite3VdbeAddOp2(v, OP_Null, 0, dest.iParm);
        VdbeComment((v, "Init subquery result"));
      }else{
        dest.eDest = SRT_Exists;
        sqlite3VdbeAddOp2(v, OP_Integer, 0, dest.iParm);
        VdbeComment((v, "Init EXISTS result"));
      }
      sqlite3ExprDelete(pParse->db, pSel->pLimit);
      pSel->pLimit = sqlite3PExpr(pParse, TK_INTEGER, 0, 0, &one);
      if( sqlite3Select(pParse, pSel, &dest) ){
        return;
      }
      pExpr->iColumn = (i16)dest.iParm;
      ExprSetIrreducible(pExpr);
      break;
    }
  }

  if( testAddr ){
    sqlite3VdbeJumpHere(v, testAddr-1);
  }
  sqlite3ExprCachePop(pParse, 1);

  return;
}
#endif /* SQLITE_OMIT_SUBQUERY */

/*
** Duplicate an 8-byte value
*/
static char *dup8bytes(Vdbe *v, const char *in){
  char *out = sqlite3DbMallocRaw(sqlite3VdbeDb(v), 8);
  if( out ){
    memcpy(out, in, 8);
  }
  return out;
}

/*
** Generate an instruction that will put the floating point
** value described by z[0..n-1] into register iMem.
**
** The z[] string will probably not be zero-terminated.  But the 
** z[n] character is guaranteed to be something that does not look
** like the continuation of the number.
*/
static void codeReal(Vdbe *v, const char *z, int negateFlag, int iMem){
  if( ALWAYS(z!=0) ){
    double value;
    char *zV;
    sqlite3AtoF(z, &value);
    if( sqlite3IsNaN(value) ){
      sqlite3VdbeAddOp2(v, OP_Null, 0, iMem);
    }else{
      if( negateFlag ) value = -value;
      zV = dup8bytes(v, (char*)&value);
      sqlite3VdbeAddOp4(v, OP_Real, 0, iMem, 0, zV, P4_REAL);
    }
  }
}


/*
** Generate an instruction that will put the integer describe by
** text z[0..n-1] into register iMem.
**
** The z[] string will probably not be zero-terminated.  But the 
** z[n] character is guaranteed to be something that does not look
** like the continuation of the number.
*/
static void codeInteger(Vdbe *v, Expr *pExpr, int negFlag, int iMem){
  if( pExpr->flags & EP_IntValue ){
    int i = pExpr->u.iValue;
    if( negFlag ) i = -i;
    sqlite3VdbeAddOp2(v, OP_Integer, i, iMem);
  }else{
    const char *z = pExpr->u.zToken;
    assert( z!=0 );
    if( sqlite3FitsIn64Bits(z, negFlag) ){
      i64 value;
      char *zV;
      sqlite3Atoi64(z, &value);
      if( negFlag ) value = -value;
      zV = dup8bytes(v, (char*)&value);
      sqlite3VdbeAddOp4(v, OP_Int64, 0, iMem, 0, zV, P4_INT64);
    }else{
      codeReal(v, z, negFlag, iMem);
    }
  }
}

/*
** Clear a cache entry.
*/
static void cacheEntryClear(Parse *pParse, struct yColCache *p){
  if( p->tempReg ){
    if( pParse->nTempReg<ArraySize(pParse->aTempReg) ){
      pParse->aTempReg[pParse->nTempReg++] = p->iReg;
    }
    p->tempReg = 0;
  }
}


/*
** Record in the column cache that a particular column from a
