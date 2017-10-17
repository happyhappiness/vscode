 ** restored.
 *****************************************************************************/
     }
 
 #ifdef VDBE_PROFILE
     {
-      u64 endTime = sqlite3Hwtime();
-      if( endTime>start ) pOrigOp->cycles += endTime - start;
-      pOrigOp->cnt++;
+      u64 elapsed = sqlite3Hwtime() - start;
+      pOp->cycles += elapsed;
+      pOp->cnt++;
+#if 0
+        fprintf(stdout, "%10llu ", elapsed);
+        sqlite3VdbePrintOp(stdout, origPc, &p->aOp[origPc]);
+#endif
     }
 #endif
 
     /* The following code adds nothing to the actual functionality
     ** of the program.  It is only here for testing and debugging.
     ** On the other hand, it does burn CPU cycles every time through
     ** the evaluator loop.  So we can leave it out when NDEBUG is defined.
     */
 #ifndef NDEBUG
-    assert( pOp>=&aOp[-1] && pOp<&aOp[p->nOp-1] );
+    assert( pc>=-1 && pc<p->nOp );
 
 #ifdef SQLITE_DEBUG
-    if( db->flags & SQLITE_VdbeTrace ){
-      u8 opProperty = sqlite3OpcodeProperty[pOrigOp->opcode];
-      if( rc!=0 ) printf("rc=%d\n",rc);
-      if( opProperty & (OPFLG_OUT2) ){
-        registerTrace(pOrigOp->p2, &aMem[pOrigOp->p2]);
+    if( p->trace ){
+      if( rc!=0 ) fprintf(p->trace,"rc=%d\n",rc);
+      if( opProperty & OPFLG_OUT2_PRERELEASE ){
+        registerTrace(p->trace, pOp->p2, pOut);
       }
       if( opProperty & OPFLG_OUT3 ){
-        registerTrace(pOrigOp->p3, &aMem[pOrigOp->p3]);
+        registerTrace(p->trace, pOp->p3, pOut);
       }
     }
 #endif  /* SQLITE_DEBUG */
 #endif  /* NDEBUG */
   }  /* The end of the for(;;) loop the loops through opcodes */
 
   /* If we reach this point, it means that execution is finished with
   ** an error of some kind.
   */
-abort_due_to_error:
-  if( db->mallocFailed ) rc = SQLITE_NOMEM_BKPT;
+vdbe_error_halt:
   assert( rc );
-  if( p->zErrMsg==0 && rc!=SQLITE_IOERR_NOMEM ){
-    sqlite3VdbeError(p, "%s", sqlite3ErrStr(rc));
-  }
   p->rc = rc;
-  sqlite3SystemError(db, rc);
-  testcase( sqlite3GlobalConfig.xLog!=0 );
-  sqlite3_log(rc, "statement aborts at %d: [%s] %s", 
-                   (int)(pOp - aOp), p->zSql, p->zErrMsg);
   sqlite3VdbeHalt(p);
-  if( rc==SQLITE_IOERR_NOMEM ) sqlite3OomFault(db);
+  if( rc==SQLITE_IOERR_NOMEM ) db->mallocFailed = 1;
   rc = SQLITE_ERROR;
-  if( resetSchemaOnFault>0 ){
-    sqlite3ResetOneSchema(db, resetSchemaOnFault-1);
-  }
 
   /* This is the only way out of this procedure.  We have to
   ** release the mutexes on btrees that were acquired at the
   ** top. */
 vdbe_return:
-  testcase( nVmStep>0 );
-  p->aCounter[SQLITE_STMTSTATUS_VM_STEP] += (int)nVmStep;
-  sqlite3VdbeLeave(p);
-  assert( rc!=SQLITE_OK || nExtraDelete==0 
-       || sqlite3_strlike("DELETE%",p->zSql,0)!=0 
-  );
+  sqlite3BtreeMutexArrayLeave(&p->aMutex);
   return rc;
 
   /* Jump to here if a string or blob larger than SQLITE_MAX_LENGTH
   ** is encountered.
   */
 too_big:
-  sqlite3VdbeError(p, "string or blob too big");
+  sqlite3SetString(&p->zErrMsg, db, "string or blob too big");
   rc = SQLITE_TOOBIG;
-  goto abort_due_to_error;
+  goto vdbe_error_halt;
 
   /* Jump to here if a malloc() fails.
   */
 no_mem:
-  sqlite3OomFault(db);
-  sqlite3VdbeError(p, "out of memory");
-  rc = SQLITE_NOMEM_BKPT;
-  goto abort_due_to_error;
+  db->mallocFailed = 1;
+  sqlite3SetString(&p->zErrMsg, db, "out of memory");
+  rc = SQLITE_NOMEM;
+  goto vdbe_error_halt;
+
+  /* Jump to here for an SQLITE_MISUSE error.
+  */
+abort_due_to_misuse:
+  rc = SQLITE_MISUSE;
+  /* Fall thru into abort_due_to_error */
+
+  /* Jump to here for any other kind of fatal error.  The "rc" variable
+  ** should hold the error number.
+  */
+abort_due_to_error:
+  assert( p->zErrMsg==0 );
+  if( db->mallocFailed ) rc = SQLITE_NOMEM;
+  if( rc!=SQLITE_IOERR_NOMEM ){
+    sqlite3SetString(&p->zErrMsg, db, "%s", sqlite3ErrStr(rc));
+  }
+  goto vdbe_error_halt;
 
   /* Jump to here if the sqlite3_interrupt() API sets the interrupt
   ** flag.
   */
 abort_due_to_interrupt:
   assert( db->u1.isInterrupted );
-  rc = db->mallocFailed ? SQLITE_NOMEM_BKPT : SQLITE_INTERRUPT;
+  rc = SQLITE_INTERRUPT;
   p->rc = rc;
-  sqlite3VdbeError(p, "%s", sqlite3ErrStr(rc));
-  goto abort_due_to_error;
+  sqlite3SetString(&p->zErrMsg, db, "%s", sqlite3ErrStr(rc));
+  goto vdbe_error_halt;
 }
