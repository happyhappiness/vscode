** P2. Otherwise, fall through to the next instruction.
*/
case OP_IncrVacuum: {        /* jump */
  Btree *pBt;

  assert( pOp->p1>=0 && pOp->p1<db->nDb );
  assert( (p->btreeMask & (1<<pOp->p1))!=0 );
  pBt = db->aDb[pOp->p1].pBt;
  rc = sqlite3BtreeIncrVacuum(pBt);
  if( rc==SQLITE_DONE ){
    pc = pOp->p2 - 1;
    rc = SQLITE_OK;
  }
  break;
}
#endif

/* Opcode: Expire P1 * * * *
**
** Cause precompiled statements to become expired. An expired statement
** fails with an error code of SQLITE_SCHEMA if it is ever executed 
** (via sqlite3_step()).
** 
** If P1 is 0, then all SQL statements become expired. If P1 is non-zero,
** then only the currently executing statement is affected. 
*/
case OP_Expire: {
  if( !pOp->p1 ){
    sqlite3ExpirePreparedStatements(db);
  }else{
    p->expired = 1;
  }
  break;
}

#ifndef SQLITE_OMIT_SHARED_CACHE
/* Opcode: TableLock P1 P2 P3 P4 *
**
** Obtain a lock on a particular table. This instruction is only used when
** the shared-cache feature is enabled. 
**
** If P1 is  the index of the database in sqlite3.aDb[] of the database
** on which the lock is acquired.  A readlock is obtained if P3==0 or
** a write lock if P3==1.
**
** P2 contains the root-page of the table to lock.
**
** P4 contains a pointer to the name of the table being locked. This is only
** used to generate an error message if the lock cannot be obtained.
*/
case OP_TableLock: {
  int p1;
  u8 isWriteLock;

  p1 = pOp->p1; 
  isWriteLock = (u8)pOp->p3;
  assert( p1>=0 && p1<db->nDb );
  assert( (p->btreeMask & (1<<p1))!=0 );
  assert( isWriteLock==0 || isWriteLock==1 );
  rc = sqlite3BtreeLockTable(db->aDb[p1].pBt, pOp->p2, isWriteLock);
  if( (rc&0xFF)==SQLITE_LOCKED ){
    const char *z = pOp->p4.z;
    sqlite3SetString(&p->zErrMsg, db, "database table is locked: %s", z);
  }
  break;
}
#endif /* SQLITE_OMIT_SHARED_CACHE */

#ifndef SQLITE_OMIT_VIRTUALTABLE
