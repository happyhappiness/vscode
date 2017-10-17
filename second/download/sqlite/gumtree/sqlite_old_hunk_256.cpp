** If P2==1 then no insert is performed.  argv[0] is the rowid of
** a row to delete.
**
** P1 is a boolean flag. If it is set to true and the xUpdate call
** is successful, then the value returned by sqlite3_last_insert_rowid() 
** is set to the value of the rowid for the row just inserted.
*/
case OP_VUpdate: {
  sqlite3_vtab *pVtab;
  sqlite3_module *pModule;
  int nArg;
  int i;
  sqlite_int64 rowid;
  Mem **apArg;
  Mem *pX;

  pVtab = pOp->p4.pVtab;
  pModule = (sqlite3_module *)pVtab->pModule;
  nArg = pOp->p2;
  assert( pOp->p4type==P4_VTAB );
  if( pModule->xUpdate==0 ){
    sqlite3SetString(&p->zErrMsg, db, "read-only table");
    rc = SQLITE_ERROR;
  }else{
    apArg = p->apArg;
    pX = &p->aMem[pOp->p3];
    for(i=0; i<nArg; i++){
      storeTypeInfo(pX, 0);
      apArg[i] = pX;
      pX++;
    }
    if( sqlite3SafetyOff(db) ) goto abort_due_to_misuse;
    sqlite3VtabLock(pVtab);
    rc = pModule->xUpdate(pVtab, nArg, apArg, &rowid);
    sqlite3DbFree(db, p->zErrMsg);
    p->zErrMsg = pVtab->zErrMsg;
    pVtab->zErrMsg = 0;
    sqlite3VtabUnlock(db, pVtab);
    if( sqlite3SafetyOn(db) ) goto abort_due_to_misuse;
    if( pOp->p1 && rc==SQLITE_OK ){
      assert( nArg>1 && apArg[0] && (apArg[0]->flags&MEM_Null) );
      db->lastRowid = rowid;
    }
    p->nChange++;
  }
  break;
}
#endif /* SQLITE_OMIT_VIRTUALTABLE */

#ifndef  SQLITE_OMIT_PAGER_PRAGMAS
/* Opcode: Pagecount P1 P2 * * *
**
** Write the current number of pages in database P1 to memory cell P2.
*/
case OP_Pagecount: {            /* out2-prerelease */
  int p1;
  int nPage;
  Pager *pPager;

  p1 = pOp->p1; 
  pPager = sqlite3BtreePager(db->aDb[p1].pBt);
  rc = sqlite3PagerPagecount(pPager, &nPage);
  if( rc==SQLITE_OK ){
    pOut->flags = MEM_Int;
    pOut->u.i = nPage;
  }
  break;
}
#endif

#ifndef SQLITE_OMIT_TRACE
/* Opcode: Trace * * * P4 *
**
** If tracing is enabled (by the sqlite3_trace()) interface, then
** the UTF-8 string contained in P4 is emitted on the trace callback.
*/
case OP_Trace: {
  char *zTrace;

  zTrace = (pOp->p4.z ? pOp->p4.z : p->zSql);
  if( zTrace ){
    if( db->xTrace ){
      db->xTrace(db->pTraceArg, zTrace);
    }
#ifdef SQLITE_DEBUG
    if( (db->flags & SQLITE_SqlTrace)!=0 ){
      sqlite3DebugPrintf("SQL-trace: %s\n", zTrace);
    }
#endif /* SQLITE_DEBUG */
  }
  break;
}
#endif


/* Opcode: Noop * * * * *
**
** Do nothing.  This instruction is often useful as a jump
** destination.
*/
