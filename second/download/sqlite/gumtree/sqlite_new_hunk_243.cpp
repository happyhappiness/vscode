#endif

  return rc;
}

/* 
** This routine checks that the sqlite3.nVdbeActive count variable
** matches the number of vdbe's in the list sqlite3.pVdbe that are
** currently active. An assertion fails if the two counts do not match.
** This is an internal self-check only - it is not an essential processing
** step.
**
** This is a no-op if NDEBUG is defined.
*/
#ifndef NDEBUG
static void checkActiveVdbeCnt(sqlite3 *db){
  Vdbe *p;
  int cnt = 0;
  int nWrite = 0;
  int nRead = 0;
  p = db->pVdbe;
  while( p ){
    if( sqlite3_stmt_busy((sqlite3_stmt*)p) ){
      cnt++;
      if( p->readOnly==0 ) nWrite++;
      if( p->bIsReader ) nRead++;
    }
    p = p->pNext;
  }
  assert( cnt==db->nVdbeActive );
  assert( nWrite==db->nVdbeWrite );
  assert( nRead==db->nVdbeRead );
}
#else
#define checkActiveVdbeCnt(x)
#endif

/*
** If the Vdbe passed as the first argument opened a statement-transaction,
** close it now. Argument eOp must be either SAVEPOINT_ROLLBACK or
** SAVEPOINT_RELEASE. If it is SAVEPOINT_ROLLBACK, then the statement
** transaction is rolled back. If eOp is SAVEPOINT_RELEASE, then the 
** statement transaction is committed.
**
** If an IO error occurs, an SQLITE_IOERR_XXX error code is returned. 
** Otherwise SQLITE_OK.
*/
static SQLITE_NOINLINE int vdbeCloseStatement(Vdbe *p, int eOp){
  sqlite3 *const db = p->db;
  int rc = SQLITE_OK;
  int i;
  const int iSavepoint = p->iStatement-1;

  assert( eOp==SAVEPOINT_ROLLBACK || eOp==SAVEPOINT_RELEASE);
  assert( db->nStatement>0 );
  assert( p->iStatement==(db->nStatement+db->nSavepoint) );

  for(i=0; i<db->nDb; i++){ 
    int rc2 = SQLITE_OK;
    Btree *pBt = db->aDb[i].pBt;
    if( pBt ){
      if( eOp==SAVEPOINT_ROLLBACK ){
        rc2 = sqlite3BtreeSavepoint(pBt, SAVEPOINT_ROLLBACK, iSavepoint);
      }
      if( rc2==SQLITE_OK ){
        rc2 = sqlite3BtreeSavepoint(pBt, SAVEPOINT_RELEASE, iSavepoint);
      }
      if( rc==SQLITE_OK ){
        rc = rc2;
      }
    }
  }
  db->nStatement--;
  p->iStatement = 0;

  if( rc==SQLITE_OK ){
    if( eOp==SAVEPOINT_ROLLBACK ){
      rc = sqlite3VtabSavepoint(db, SAVEPOINT_ROLLBACK, iSavepoint);
    }
    if( rc==SQLITE_OK ){
      rc = sqlite3VtabSavepoint(db, SAVEPOINT_RELEASE, iSavepoint);
    }
  }

  /* If the statement transaction is being rolled back, also restore the 
  ** database handles deferred constraint counter to the value it had when 
  ** the statement transaction was opened.  */
  if( eOp==SAVEPOINT_ROLLBACK ){
    db->nDeferredCons = p->nStmtDefCons;
    db->nDeferredImmCons = p->nStmtDefImmCons;
  }
  return rc;
}
int sqlite3VdbeCloseStatement(Vdbe *p, int eOp){
  if( p->db->nStatement && p->iStatement ){
    return vdbeCloseStatement(p, eOp);
  }
  return SQLITE_OK;
}


/*
** This function is called when a transaction opened by the database 
** handle associated with the VM passed as an argument is about to be 
** committed. If there are outstanding deferred foreign key constraint
** violations, return SQLITE_ERROR. Otherwise, SQLITE_OK.
**
** If there are outstanding FK violations and this function returns 
** SQLITE_ERROR, set the result of the VM to SQLITE_CONSTRAINT_FOREIGNKEY
** and write an error message to it. Then return SQLITE_ERROR.
*/
#ifndef SQLITE_OMIT_FOREIGN_KEY
int sqlite3VdbeCheckFk(Vdbe *p, int deferred){
  sqlite3 *db = p->db;
  if( (deferred && (db->nDeferredCons+db->nDeferredImmCons)>0) 
   || (!deferred && p->nFkConstraint>0) 
  ){
    p->rc = SQLITE_CONSTRAINT_FOREIGNKEY;
    p->errorAction = OE_Abort;
    sqlite3VdbeError(p, "FOREIGN KEY constraint failed");
    return SQLITE_ERROR;
  }
  return SQLITE_OK;
}
#endif

/*
** This routine is called the when a VDBE tries to halt.  If the VDBE
** has made changes and is in autocommit mode, then commit those
