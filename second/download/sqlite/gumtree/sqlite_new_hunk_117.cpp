**
** This instruction causes the VM to halt.
*/
case OP_AutoCommit: {
  int desiredAutoCommit;
  int iRollback;
  int turnOnAC;

  desiredAutoCommit = pOp->p1;
  iRollback = pOp->p2;
  turnOnAC = desiredAutoCommit && !db->autoCommit;
  assert( desiredAutoCommit==1 || desiredAutoCommit==0 );
  assert( desiredAutoCommit==1 || iRollback==0 );
  assert( db->activeVdbeCnt>0 );  /* At least this one VM is active */

  if( turnOnAC && iRollback && db->activeVdbeCnt>1 ){
    /* If this instruction implements a ROLLBACK and other VMs are
    ** still running, and a transaction is active, return an error indicating
    ** that the other VMs must complete first. 
    */
    sqlite3SetString(&p->zErrMsg, db, "cannot rollback transaction - "
        "SQL statements in progress");
    rc = SQLITE_BUSY;
  }else if( turnOnAC && !iRollback && db->writeVdbeCnt>1 ){
    /* If this instruction implements a COMMIT and other VMs are writing
    ** return an error indicating that the other VMs must complete first. 
    */
    sqlite3SetString(&p->zErrMsg, db, "cannot commit transaction - "
        "SQL statements in progress");
    rc = SQLITE_BUSY;
  }else if( desiredAutoCommit!=db->autoCommit ){
    if( iRollback ){
      assert( desiredAutoCommit==1 );
      sqlite3RollbackAll(db);
      db->autoCommit = 1;
    }else{
      db->autoCommit = (u8)desiredAutoCommit;
      if( sqlite3VdbeHalt(p)==SQLITE_BUSY ){
        p->pc = pc;
        db->autoCommit = (u8)(1-desiredAutoCommit);
        p->rc = rc = SQLITE_BUSY;
        goto vdbe_return;
      }
    }
    assert( db->nStatement==0 );
    sqlite3CloseSavepoints(db);
    if( p->rc==SQLITE_OK ){
      rc = SQLITE_DONE;
    }else{
      rc = SQLITE_ERROR;
    }
    goto vdbe_return;
  }else{
    sqlite3SetString(&p->zErrMsg, db,
        (!desiredAutoCommit)?"cannot start a transaction within a transaction":(
        (iRollback)?"cannot rollback - no transaction is active":
                   "cannot commit - no transaction is active"));
         
    rc = SQLITE_ERROR;
  }
  break;
}

/* Opcode: Transaction P1 P2 * * *
**
** Begin a transaction.  The transaction ends when a Commit or Rollback
** opcode is encountered.  Depending on the ON CONFLICT setting, the
** transaction might also be rolled back if an error is encountered.
**
** P1 is the index of the database file on which the transaction is
** started.  Index 0 is the main database file and index 1 is the
** file used for temporary tables.  Indices of 2 or more are used for
** attached databases.
**
** If P2 is non-zero, then a write-transaction is started.  A RESERVED lock is
** obtained on the database file when a write-transaction is started.  No
** other process can start another write transaction while this transaction is
** underway.  Starting a write transaction also creates a rollback journal. A
** write transaction must be started before any changes can be made to the
** database.  If P2 is 2 or greater then an EXCLUSIVE lock is also obtained
** on the file.
**
** If P2 is zero, then a read-lock is obtained on the database file.
*/
case OP_Transaction: {
  int i;
  Btree *pBt;

  i = pOp->p1;
  assert( i>=0 && i<db->nDb );
  assert( (p->btreeMask & (1<<i))!=0 );
  pBt = db->aDb[i].pBt;

  if( pBt ){
    rc = sqlite3BtreeBeginTrans(pBt, pOp->p2);
    if( rc==SQLITE_BUSY ){
      p->pc = pc;
      p->rc = rc = SQLITE_BUSY;
      goto vdbe_return;
    }
    if( rc!=SQLITE_OK && rc!=SQLITE_READONLY /* && rc!=SQLITE_BUSY */ ){
      goto abort_due_to_error;
    }
  }
  break;
}

/* Opcode: ReadCookie P1 P2 P3 * *
**
** Read cookie number P3 from database P1 and write it into register P2.
