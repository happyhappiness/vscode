int sqlite3NotPureFunc(sqlite3_context *pCtx){
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( pCtx->pVdbe==0 ) return 1;
#endif
  if( pCtx->pVdbe->aOp[pCtx->iOp].opcode==OP_PureFunc ){
    sqlite3_result_error(pCtx, 
       "non-deterministic function in index expression or CHECK constraint",
       -1);
    return 0;
  }
  return 1;
}