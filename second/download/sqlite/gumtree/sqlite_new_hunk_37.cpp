** the way through and which will need to undo some writes without having to
** rollback the whole transaction.  For operations where all constraints
** can be checked before any changes are made to the database, it is never
** necessary to undo a write and the checkpoint should not be set.
*/
void sqlite3BeginWriteOperation(Parse *pParse, int setStatement, int iDb){
  sqlite3CodeVerifySchema(pParse, iDb);
  pParse->writeMask |= 1<<iDb;
  if( setStatement && pParse->nested==0 ){
    /* Every place where this routine is called with setStatement!=0 has
    ** already successfully created a VDBE. */
    assert( pParse->pVdbe );
    sqlite3VdbeAddOp1(pParse->pVdbe, OP_Statement, iDb);
  }
}

/*
** Check to see if pIndex uses the collating sequence pColl.  Return
** true if it does and false if it does not.
*/
#ifndef SQLITE_OMIT_REINDEX
static int collationMatch(const char *zColl, Index *pIndex){
  int i;
  assert( zColl!=0 );
  for(i=0; i<pIndex->nColumn; i++){
    const char *z = pIndex->azColl[i];
    assert( z!=0 );
    if( 0==sqlite3StrICmp(z, zColl) ){
      return 1;
    }
  }
  return 0;
}
#endif
