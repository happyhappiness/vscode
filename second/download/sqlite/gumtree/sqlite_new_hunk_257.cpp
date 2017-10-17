** restored.
*****************************************************************************/
    }

#ifdef VDBE_PROFILE
    {
      u64 endTime = sqlite3Hwtime();
      if( endTime>start ) pOrigOp->cycles += endTime - start;
      pOrigOp->cnt++;
    }
#endif

    /* The following code adds nothing to the actual functionality
    ** of the program.  It is only here for testing and debugging.
    ** On the other hand, it does burn CPU cycles every time through
    ** the evaluator loop.  So we can leave it out when NDEBUG is defined.
    */
#ifndef NDEBUG
    assert( pOp>=&aOp[-1] && pOp<&aOp[p->nOp-1] );

#ifdef SQLITE_DEBUG
    if( db->flags & SQLITE_VdbeTrace ){
      u8 opProperty = sqlite3OpcodeProperty[pOrigOp->opcode];
      if( rc!=0 ) printf("rc=%d\n",rc);
      if( opProperty & (OPFLG_OUT2) ){
        registerTrace(pOrigOp->p2, &aMem[pOrigOp->p2]);
      }
      if( opProperty & OPFLG_OUT3 ){
        registerTrace(pOrigOp->p3, &aMem[pOrigOp->p3]);
      }
    }
#endif  /* SQLITE_DEBUG */
#endif  /* NDEBUG */
  }  /* The end of the for(;;) loop the loops through opcodes */

  /* If we reach this point, it means that execution is finished with
  ** an error of some kind.
  */
abort_due_to_error:
  if( db->mallocFailed ) rc = SQLITE_NOMEM_BKPT;
  assert( rc );
  if( p->zErrMsg==0 && rc!=SQLITE_IOERR_NOMEM ){
    sqlite3VdbeError(p, "%s", sqlite3ErrStr(rc));
  }
  p->rc = rc;
  sqlite3SystemError(db, rc);
  testcase( sqlite3GlobalConfig.xLog!=0 );
  sqlite3_log(rc, "statement aborts at %d: [%s] %s", 
                   (int)(pOp - aOp), p->zSql, p->zErrMsg);
  sqlite3VdbeHalt(p);
  if( rc==SQLITE_IOERR_NOMEM ) sqlite3OomFault(db);
  rc = SQLITE_ERROR;
  if( resetSchemaOnFault>0 ){
    sqlite3ResetOneSchema(db, resetSchemaOnFault-1);
  }

  /* This is the only way out of this procedure.  We have to
  ** release the mutexes on btrees that were acquired at the
  ** top. */
vdbe_return:
  testcase( nVmStep>0 );
  p->aCounter[SQLITE_STMTSTATUS_VM_STEP] += (int)nVmStep;
  sqlite3VdbeLeave(p);
  assert( rc!=SQLITE_OK || nExtraDelete==0 
       || sqlite3_strlike("DELETE%",p->zSql,0)!=0 
  );
  return rc;

  /* Jump to here if a string or blob larger than SQLITE_MAX_LENGTH
  ** is encountered.
  */
too_big:
  sqlite3VdbeError(p, "string or blob too big");
  rc = SQLITE_TOOBIG;
  goto abort_due_to_error;

  /* Jump to here if a malloc() fails.
  */
no_mem:
  sqlite3OomFault(db);
  sqlite3VdbeError(p, "out of memory");
  rc = SQLITE_NOMEM_BKPT;
  goto abort_due_to_error;

  /* Jump to here if the sqlite3_interrupt() API sets the interrupt
  ** flag.
  */
abort_due_to_interrupt:
  assert( db->u1.isInterrupted );
  rc = db->mallocFailed ? SQLITE_NOMEM_BKPT : SQLITE_INTERRUPT;
  p->rc = rc;
  sqlite3VdbeError(p, "%s", sqlite3ErrStr(rc));
  goto abort_due_to_error;
}
