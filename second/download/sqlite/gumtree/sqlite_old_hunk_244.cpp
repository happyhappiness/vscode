  **
  ** Then the internal cache might have been left in an inconsistent
  ** state.  We need to rollback the statement transaction, if there is
  ** one, or the complete transaction if there is no statement transaction.
  */

  if( p->db->mallocFailed ){
    p->rc = SQLITE_NOMEM;
  }
  closeAllCursorsExceptActiveVtabs(p);
  if( p->magic!=VDBE_MAGIC_RUN ){
    return SQLITE_OK;
  }
  checkActiveVdbeCnt(db);

  /* No commit or rollback needed if the program never started */
  if( p->pc>=0 ){
    int mrc;   /* Primary error code from p->rc */
    int eStatementOp = 0;
    int isSpecialError;            /* Set to true if a 'special' error */

    /* Lock all btrees used by the statement */
    sqlite3VdbeMutexArrayEnter(p);

    /* Check for one of the special errors */
    mrc = p->rc & 0xff;
    isSpecialError = mrc==SQLITE_NOMEM || mrc==SQLITE_IOERR
                     || mrc==SQLITE_INTERRUPT || mrc==SQLITE_FULL;
    if( isSpecialError ){
      /* If the query was read-only, we need do no rollback at all. Otherwise,
      ** proceed with the special handling.
      */
      if( !p->readOnly || mrc!=SQLITE_INTERRUPT ){
        if( p->rc==SQLITE_IOERR_BLOCKED && p->usesStmtJournal ){
          eStatementOp = SAVEPOINT_ROLLBACK;
          p->rc = SQLITE_BUSY;
        }else if( (mrc==SQLITE_NOMEM || mrc==SQLITE_FULL)
                   && p->usesStmtJournal ){
          eStatementOp = SAVEPOINT_ROLLBACK;
        }else{
          /* We are forced to roll back the active transaction. Before doing
          ** so, abort any other statements this handle currently has active.
          */
          invalidateCursorsOnModifiedBtrees(db);
          sqlite3RollbackAll(db);
          sqlite3CloseSavepoints(db);
          db->autoCommit = 1;
        }
      }
    }
  
    /* If the auto-commit flag is set and this is the only active writer 
    ** VM, then we do either a commit or rollback of the current transaction. 
    **
    ** Note: This block also runs if one of the special errors handled 
    ** above has occurred. 
    */
    if( !sqlite3VtabInSync(db) 
     && db->autoCommit 
     && db->writeVdbeCnt==(p->readOnly==0) 
     && (db->flags & SQLITE_CommitBusy)==0
    ){
      if( p->rc==SQLITE_OK || (p->errorAction==OE_Fail && !isSpecialError) ){
        /* The auto-commit flag is true, and the vdbe program was 
        ** successful or hit an 'OR FAIL' constraint. This means a commit 
        ** is required.
        */
        rc = vdbeCommit(db, p);
        if( rc==SQLITE_BUSY ){
          sqlite3BtreeMutexArrayLeave(&p->aMutex);
          return SQLITE_BUSY;
        }else if( rc!=SQLITE_OK ){
          p->rc = rc;
          sqlite3RollbackAll(db);
        }else{
          sqlite3CommitInternalChanges(db);
        }
      }else{
        sqlite3RollbackAll(db);
      }
      db->nStatement = 0;
    }else if( eStatementOp==0 ){
      if( p->rc==SQLITE_OK || p->errorAction==OE_Fail ){
        eStatementOp = SAVEPOINT_RELEASE;
      }else if( p->errorAction==OE_Abort ){
        eStatementOp = SAVEPOINT_ROLLBACK;
      }else{
        invalidateCursorsOnModifiedBtrees(db);
        sqlite3RollbackAll(db);
        sqlite3CloseSavepoints(db);
        db->autoCommit = 1;
      }
    }
  
    /* If eStatementOp is non-zero, then a statement transaction needs to
    ** be committed or rolled back. Call sqlite3VdbeCloseStatement() to
    ** do so. If this operation returns an error, and the current statement
    ** error code is SQLITE_OK or SQLITE_CONSTRAINT, then set the error
    ** code to the new value.
    */
    if( eStatementOp ){
      rc = sqlite3VdbeCloseStatement(p, eStatementOp);
      if( rc && (p->rc==SQLITE_OK || p->rc==SQLITE_CONSTRAINT) ){
        p->rc = rc;
        sqlite3DbFree(db, p->zErrMsg);
        p->zErrMsg = 0;
      }
    }
  
    /* If this was an INSERT, UPDATE or DELETE and no statement transaction
    ** has been rolled back, update the database connection change-counter. 
    */
    if( p->changeCntOn && p->pc>=0 ){
      if( eStatementOp!=SAVEPOINT_ROLLBACK ){
        sqlite3VdbeSetChanges(db, p->nChange);
      }else{
        sqlite3VdbeSetChanges(db, 0);
      }
      p->nChange = 0;
    }
  
    /* Rollback or commit any schema changes that occurred. */
    if( p->rc!=SQLITE_OK && db->flags&SQLITE_InternChanges ){
      sqlite3ResetInternalSchema(db, 0);
      db->flags = (db->flags | SQLITE_InternChanges);
    }

    /* Release the locks */
    sqlite3BtreeMutexArrayLeave(&p->aMutex);
  }

  /* We have successfully halted and closed the VM.  Record this fact. */
  if( p->pc>=0 ){
    db->activeVdbeCnt--;
    if( !p->readOnly ){
      db->writeVdbeCnt--;
    }
    assert( db->activeVdbeCnt>=db->writeVdbeCnt );
  }
  p->magic = VDBE_MAGIC_HALT;
  checkActiveVdbeCnt(db);
  if( p->db->mallocFailed ){
    p->rc = SQLITE_NOMEM;
  }

  /* If the auto-commit flag is set to true, then any locks that were held
  ** by connection db have now been released. Call sqlite3ConnectionUnlocked() 
  ** to invoke any required unlock-notify callbacks.
  */
  if( db->autoCommit ){
    sqlite3ConnectionUnlocked(db);
  }

  assert( db->activeVdbeCnt>0 || db->autoCommit==0 || db->nStatement==0 );
  return SQLITE_OK;
}


/*
** Each VDBE holds the result of the most recent sqlite3_step() call
** in p->rc.  This routine sets that result back to SQLITE_OK.
*/
void sqlite3VdbeResetStepResult(Vdbe *p){
  p->rc = SQLITE_OK;
}

/*
** Clean up a VDBE after execution but do not delete the VDBE just yet.
** Write any error messages into *pzErrMsg.  Return the result code.
**
** After this routine is run, the VDBE should be ready to be executed
** again.
**
** To look at it another way, this routine resets the state of the
** virtual machine from VDBE_MAGIC_RUN or VDBE_MAGIC_HALT back to
** VDBE_MAGIC_INIT.
*/
int sqlite3VdbeReset(Vdbe *p){
  sqlite3 *db;
  db = p->db;

  /* If the VM did not run to completion or if it encountered an
  ** error, then it might not have been halted properly.  So halt
  ** it now.
  */
  (void)sqlite3SafetyOn(db);
  sqlite3VdbeHalt(p);
  (void)sqlite3SafetyOff(db);

  /* If the VDBE has be run even partially, then transfer the error code
  ** and error message from the VDBE into the main database structure.  But
  ** if the VDBE has just been set to run but has not actually executed any
  ** instructions yet, leave the main database error information unchanged.
  */
  if( p->pc>=0 ){
    if( p->zErrMsg ){
      sqlite3BeginBenignMalloc();
      sqlite3ValueSetStr(db->pErr,-1,p->zErrMsg,SQLITE_UTF8,SQLITE_TRANSIENT);
      sqlite3EndBenignMalloc();
      db->errCode = p->rc;
      sqlite3DbFree(db, p->zErrMsg);
      p->zErrMsg = 0;
    }else if( p->rc ){
      sqlite3Error(db, p->rc, 0);
    }else{
      sqlite3Error(db, SQLITE_OK, 0);
    }
  }else if( p->rc && p->expired ){
    /* The expired flag was set on the VDBE before the first call
    ** to sqlite3_step(). For consistency (since sqlite3_step() was
    ** called), set the database error in this case as well.
    */
    sqlite3Error(db, p->rc, 0);
    sqlite3ValueSetStr(db->pErr, -1, p->zErrMsg, SQLITE_UTF8, SQLITE_TRANSIENT);
    sqlite3DbFree(db, p->zErrMsg);
    p->zErrMsg = 0;
  }

  /* Reclaim all memory used by the VDBE
  */
  Cleanup(p);

  /* Save profiling information from this VDBE run.
  */
#ifdef VDBE_PROFILE
  {
    FILE *out = fopen("vdbe_profile.out", "a");
    if( out ){
      int i;
      fprintf(out, "---- ");
      for(i=0; i<p->nOp; i++){
        fprintf(out, "%02x", p->aOp[i].opcode);
      }
      fprintf(out, "\n");
      for(i=0; i<p->nOp; i++){
        fprintf(out, "%6d %10lld %8lld ",
           p->aOp[i].cnt,
           p->aOp[i].cycles,
           p->aOp[i].cnt>0 ? p->aOp[i].cycles/p->aOp[i].cnt : 0
        );
        sqlite3VdbePrintOp(out, i, &p->aOp[i]);
      }
      fclose(out);
    }
  }
#endif
  p->magic = VDBE_MAGIC_INIT;
  return p->rc & db->errMask;
}
 
/*
** Clean up and delete a VDBE after execution.  Return an integer which is
** the result code.  Write any error message text into *pzErrMsg.
*/
int sqlite3VdbeFinalize(Vdbe *p){
  int rc = SQLITE_OK;
  if( p->magic==VDBE_MAGIC_RUN || p->magic==VDBE_MAGIC_HALT ){
    rc = sqlite3VdbeReset(p);
    assert( (rc & p->db->errMask)==rc );
  }else if( p->magic!=VDBE_MAGIC_INIT ){
    return SQLITE_MISUSE;
  }
  sqlite3VdbeDelete(p);
  return rc;
}

/*
** Call the destructor for each auxdata entry in pVdbeFunc for which
** the corresponding bit in mask is clear.  Auxdata entries beyond 31
** are always destroyed.  To destroy all auxdata entries, call this
** routine with mask==0.
*/
void sqlite3VdbeDeleteAuxData(VdbeFunc *pVdbeFunc, int mask){
  int i;
  for(i=0; i<pVdbeFunc->nAux; i++){
    struct AuxData *pAux = &pVdbeFunc->apAux[i];
    if( (i>31 || !(mask&(((u32)1)<<i))) && pAux->pAux ){
      if( pAux->xDelete ){
        pAux->xDelete(pAux->pAux);
      }
      pAux->pAux = 0;
    }
  }
}

/*
** Delete an entire VDBE.
*/
void sqlite3VdbeDelete(Vdbe *p){
  int i;
  sqlite3 *db;

  if( p==0 ) return;
  db = p->db;
  if( p->pPrev ){
    p->pPrev->pNext = p->pNext;
  }else{
    assert( db->pVdbe==p );
    db->pVdbe = p->pNext;
  }
  if( p->pNext ){
    p->pNext->pPrev = p->pPrev;
  }
  if( p->aOp ){
    Op *pOp = p->aOp;
    for(i=0; i<p->nOp; i++, pOp++){
      freeP4(db, pOp->p4type, pOp->p4.p);
#ifdef SQLITE_DEBUG
      sqlite3DbFree(db, pOp->zComment);
#endif     
    }
  }
  releaseMemArray(p->aVar, p->nVar);
  sqlite3DbFree(db, p->aLabel);
  releaseMemArray(p->aColName, p->nResColumn*COLNAME_N);
  sqlite3DbFree(db, p->aColName);
  sqlite3DbFree(db, p->zSql);
  p->magic = VDBE_MAGIC_DEAD;
  sqlite3DbFree(db, p->aOp);
  sqlite3DbFree(db, p->pFree);
  sqlite3DbFree(db, p);
}

/*
** If a MoveTo operation is pending on the given cursor, then do that
** MoveTo now.  Return an error code.  If no MoveTo is pending, this
** routine does nothing and returns SQLITE_OK.
*/
int sqlite3VdbeCursorMoveto(VdbeCursor *p){
  if( p->deferredMoveto ){
    int res, rc;
#ifdef SQLITE_TEST
    extern int sqlite3_search_count;
#endif
    assert( p->isTable );
    rc = sqlite3BtreeMovetoUnpacked(p->pCursor, 0, p->movetoTarget, 0, &res);
    if( rc ) return rc;
    p->lastRowid = keyToInt(p->movetoTarget);
    p->rowidIsValid = ALWAYS(res==0) ?1:0;
    if( NEVER(res<0) ){
      rc = sqlite3BtreeNext(p->pCursor, &res);
      if( rc ) return rc;
    }
#ifdef SQLITE_TEST
    sqlite3_search_count++;
#endif
    p->deferredMoveto = 0;
    p->cacheStatus = CACHE_STALE;
  }else if( p->pCursor ){
    int hasMoved;
    int rc = sqlite3BtreeCursorHasMoved(p->pCursor, &hasMoved);
    if( rc ) return rc;
    if( hasMoved ){
      p->cacheStatus = CACHE_STALE;
      p->nullRow = 1;
    }
  }
  return SQLITE_OK;
}

/*
** The following functions:
