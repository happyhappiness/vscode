static int valueFromExpr(
  sqlite3 *db,                    /* The database connection */
  Expr *pExpr,                    /* The expression to evaluate */
  u8 enc,                         /* Encoding to use */
  u8 affinity,                    /* Affinity to use */
  sqlite3_value **ppVal,          /* Write the new value here */
  struct ValueNewStat4Ctx *pCtx   /* Second argument for valueNew() */
){
  int op;
  char *zVal = 0;
  sqlite3_value *pVal = 0;
  int negInt = 1;
  const char *zNeg = "";
  int rc = SQLITE_OK;

  assert( pExpr!=0 );
  while( (op = pExpr->op)==TK_UPLUS || op==TK_SPAN ) pExpr = pExpr->pLeft;
  if( NEVER(op==TK_REGISTER) ) op = pExpr->op2;

  /* Compressed expressions only appear when parsing the DEFAULT clause
  ** on a table column definition, and hence only when pCtx==0.  This
  ** check ensures that an EP_TokenOnly expression is never passed down
  ** into valueFromFunction(). */
  assert( (pExpr->flags & EP_TokenOnly)==0 || pCtx==0 );

  if( op==TK_CAST ){
    u8 aff = sqlite3AffinityType(pExpr->u.zToken,0);
    rc = valueFromExpr(db, pExpr->pLeft, enc, aff, ppVal, pCtx);
    testcase( rc!=SQLITE_OK );
    if( *ppVal ){
      sqlite3VdbeMemCast(*ppVal, aff, SQLITE_UTF8);
      sqlite3ValueApplyAffinity(*ppVal, affinity, SQLITE_UTF8);
    }
    return rc;
  }

  /* Handle negative integers in a single step.  This is needed in the
  ** case when the value is -9223372036854775808.
  */
  if( op==TK_UMINUS
   && (pExpr->pLeft->op==TK_INTEGER || pExpr->pLeft->op==TK_FLOAT) ){
    pExpr = pExpr->pLeft;
    op = pExpr->op;
    negInt = -1;
    zNeg = "-";
  }

  if( op==TK_STRING || op==TK_FLOAT || op==TK_INTEGER ){
    pVal = valueNew(db, pCtx);
    if( pVal==0 ) goto no_mem;
    if( ExprHasProperty(pExpr, EP_IntValue) ){
      sqlite3VdbeMemSetInt64(pVal, (i64)pExpr->u.iValue*negInt);
    }else{
      zVal = sqlite3MPrintf(db, "%s%s", zNeg, pExpr->u.zToken);
      if( zVal==0 ) goto no_mem;
      sqlite3ValueSetStr(pVal, -1, zVal, SQLITE_UTF8, SQLITE_DYNAMIC);
    }
    if( (op==TK_INTEGER || op==TK_FLOAT ) && affinity==SQLITE_AFF_BLOB ){
      sqlite3ValueApplyAffinity(pVal, SQLITE_AFF_NUMERIC, SQLITE_UTF8);
    }else{
      sqlite3ValueApplyAffinity(pVal, affinity, SQLITE_UTF8);
    }
    if( pVal->flags & (MEM_Int|MEM_Real) ) pVal->flags &= ~MEM_Str;
    if( enc!=SQLITE_UTF8 ){
      rc = sqlite3VdbeChangeEncoding(pVal, enc);
    }
  }else if( op==TK_UMINUS ) {
    /* This branch happens for multiple negative signs.  Ex: -(-5) */
    if( SQLITE_OK==valueFromExpr(db,pExpr->pLeft,enc,affinity,&pVal,pCtx) 
     && pVal!=0
    ){
      sqlite3VdbeMemNumerify(pVal);
      if( pVal->flags & MEM_Real ){
        pVal->u.r = -pVal->u.r;
      }else if( pVal->u.i==SMALLEST_INT64 ){
        pVal->u.r = -(double)SMALLEST_INT64;
        MemSetTypeFlag(pVal, MEM_Real);
      }else{
        pVal->u.i = -pVal->u.i;
      }
      sqlite3ValueApplyAffinity(pVal, affinity, enc);
    }
  }else if( op==TK_NULL ){
    pVal = valueNew(db, pCtx);
    if( pVal==0 ) goto no_mem;
    sqlite3VdbeMemNumerify(pVal);
  }
#ifndef SQLITE_OMIT_BLOB_LITERAL
  else if( op==TK_BLOB ){
    int nVal;
    assert( pExpr->u.zToken[0]=='x' || pExpr->u.zToken[0]=='X' );
    assert( pExpr->u.zToken[1]=='\'' );
    pVal = valueNew(db, pCtx);
    if( !pVal ) goto no_mem;
    zVal = &pExpr->u.zToken[2];
    nVal = sqlite3Strlen30(zVal)-1;
    assert( zVal[nVal]=='\'' );
    sqlite3VdbeMemSetStr(pVal, sqlite3HexToBlob(db, zVal, nVal), nVal/2,
                         0, SQLITE_DYNAMIC);
  }
#endif

#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  else if( op==TK_FUNCTION && pCtx!=0 ){
    rc = valueFromFunction(db, pExpr, enc, affinity, &pVal, pCtx);
  }
#endif

  *ppVal = pVal;
  return rc;

no_mem:
  sqlite3OomFault(db);
  sqlite3DbFree(db, zVal);
  assert( *ppVal==0 );
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( pCtx==0 ) sqlite3ValueFree(pVal);
#else
  assert( pCtx==0 ); sqlite3ValueFree(pVal);
#endif
  return SQLITE_NOMEM_BKPT;
}