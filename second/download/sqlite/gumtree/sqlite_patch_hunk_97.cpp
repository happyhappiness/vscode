     *pMask = mask;
   }
   return (mask ? pList : 0);
 }
 
 /*
-** Convert the pStep->zTarget string into a SrcList and return a pointer
+** Convert the pStep->target token into a SrcList and return a pointer
 ** to that SrcList.
 **
 ** This routine adds a specific database name, if needed, to the target when
 ** forming the SrcList.  This prevents a trigger in one database from
 ** referring to a target in another database.  An exception is when the
 ** trigger is in TEMP in which case it can refer to any other database it
 ** wants.
 */
 static SrcList *targetSrcList(
   Parse *pParse,       /* The parsing context */
   TriggerStep *pStep   /* The trigger containing the target token */
 ){
-  sqlite3 *db = pParse->db;
   int iDb;             /* Index of the database to use */
   SrcList *pSrc;       /* SrcList to be returned */
 
-  pSrc = sqlite3SrcListAppend(db, 0, 0, 0);
+  pSrc = sqlite3SrcListAppend(pParse->db, 0, &pStep->target, 0);
   if( pSrc ){
     assert( pSrc->nSrc>0 );
-    pSrc->a[pSrc->nSrc-1].zName = sqlite3DbStrDup(db, pStep->zTarget);
-    iDb = sqlite3SchemaToIndex(db, pStep->pTrig->pSchema);
+    assert( pSrc->a!=0 );
+    iDb = sqlite3SchemaToIndex(pParse->db, pStep->pTrig->pSchema);
     if( iDb==0 || iDb>=2 ){
-      const char *zDb;
-      assert( iDb<db->nDb );
-      zDb = db->aDb[iDb].zDbSName;
-      pSrc->a[pSrc->nSrc-1].zDatabase =  sqlite3DbStrDup(db, zDb);
+      sqlite3 *db = pParse->db;
+      assert( iDb<pParse->db->nDb );
+      pSrc->a[pSrc->nSrc-1].zDatabase = sqlite3DbStrDup(db, db->aDb[iDb].zName);
     }
   }
   return pSrc;
 }
 
 /*
-** Generate VDBE code for the statements inside the body of a single 
-** trigger.
+** Generate VDBE code for zero or more statements inside the body of a
+** trigger.  
 */
 static int codeTriggerProgram(
   Parse *pParse,            /* The parser context */
   TriggerStep *pStepList,   /* List of statements inside the trigger body */
-  int orconf                /* Conflict algorithm. (OE_Abort, etc) */  
+  int orconfin              /* Conflict algorithm. (OE_Abort, etc) */  
 ){
-  TriggerStep *pStep;
+  TriggerStep * pTriggerStep = pStepList;
+  int orconf;
   Vdbe *v = pParse->pVdbe;
   sqlite3 *db = pParse->db;
 
-  assert( pParse->pTriggerTab && pParse->pToplevel );
-  assert( pStepList );
+  assert( pTriggerStep!=0 );
   assert( v!=0 );
-  for(pStep=pStepList; pStep; pStep=pStep->pNext){
-    /* Figure out the ON CONFLICT policy that will be used for this step
-    ** of the trigger program. If the statement that caused this trigger
-    ** to fire had an explicit ON CONFLICT, then use it. Otherwise, use
-    ** the ON CONFLICT policy that was specified as part of the trigger
-    ** step statement. Example:
-    **
-    **   CREATE TRIGGER AFTER INSERT ON t1 BEGIN;
-    **     INSERT OR REPLACE INTO t2 VALUES(new.a, new.b);
-    **   END;
-    **
-    **   INSERT INTO t1 ... ;            -- insert into t2 uses REPLACE policy
-    **   INSERT OR IGNORE INTO t1 ... ;  -- insert into t2 uses IGNORE policy
-    */
-    pParse->eOrconf = (orconf==OE_Default)?pStep->orconf:(u8)orconf;
-    assert( pParse->okConstFactor==0 );
-
-    switch( pStep->op ){
+  sqlite3VdbeAddOp2(v, OP_ContextPush, 0, 0);
+  VdbeComment((v, "begin trigger %s", pStepList->pTrig->name));
+  while( pTriggerStep ){
+    sqlite3ExprCacheClear(pParse);
+    orconf = (orconfin == OE_Default)?pTriggerStep->orconf:orconfin;
+    pParse->trigStack->orconf = orconf;
+    switch( pTriggerStep->op ){
       case TK_UPDATE: {
-        sqlite3Update(pParse, 
-          targetSrcList(pParse, pStep),
-          sqlite3ExprListDup(db, pStep->pExprList, 0), 
-          sqlite3ExprDup(db, pStep->pWhere, 0), 
-          pParse->eOrconf
-        );
+        SrcList *pSrc;
+        pSrc = targetSrcList(pParse, pTriggerStep);
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
+        sqlite3Update(pParse, pSrc,
+                sqlite3ExprListDup(db, pTriggerStep->pExprList, 0), 
+                sqlite3ExprDup(db, pTriggerStep->pWhere, 0), orconf);
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
         break;
       }
       case TK_INSERT: {
-        sqlite3Insert(pParse, 
-          targetSrcList(pParse, pStep),
-          sqlite3SelectDup(db, pStep->pSelect, 0), 
-          sqlite3IdListDup(db, pStep->pIdList), 
-          pParse->eOrconf
-        );
+        SrcList *pSrc;
+        pSrc = targetSrcList(pParse, pTriggerStep);
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
+        sqlite3Insert(pParse, pSrc,
+          sqlite3ExprListDup(db, pTriggerStep->pExprList, 0), 
+          sqlite3SelectDup(db, pTriggerStep->pSelect, 0), 
+          sqlite3IdListDup(db, pTriggerStep->pIdList), orconf);
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
         break;
       }
       case TK_DELETE: {
-        sqlite3DeleteFrom(pParse, 
-          targetSrcList(pParse, pStep),
-          sqlite3ExprDup(db, pStep->pWhere, 0)
-        );
+        SrcList *pSrc;
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
+        pSrc = targetSrcList(pParse, pTriggerStep);
+        sqlite3DeleteFrom(pParse, pSrc, 
+                          sqlite3ExprDup(db, pTriggerStep->pWhere, 0));
+        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
         break;
       }
-      default: assert( pStep->op==TK_SELECT ); {
-        SelectDest sDest;
-        Select *pSelect = sqlite3SelectDup(db, pStep->pSelect, 0);
-        sqlite3SelectDestInit(&sDest, SRT_Discard, 0);
-        sqlite3Select(pParse, pSelect, &sDest);
-        sqlite3SelectDelete(db, pSelect);
+      default: assert( pTriggerStep->op==TK_SELECT ); {
+        Select *ss = sqlite3SelectDup(db, pTriggerStep->pSelect, 0);
+        if( ss ){
+          SelectDest dest;
+
+          sqlite3SelectDestInit(&dest, SRT_Discard, 0);
+          sqlite3Select(pParse, ss, &dest);
+          sqlite3SelectDelete(db, ss);
+        }
         break;
       }
     } 
-    if( pStep->op!=TK_SELECT ){
-      sqlite3VdbeAddOp0(v, OP_ResetCount);
-    }
+    pTriggerStep = pTriggerStep->pNext;
   }
+  sqlite3VdbeAddOp2(v, OP_ContextPop, 0, 0);
+  VdbeComment((v, "end trigger %s", pStepList->pTrig->name));
 
   return 0;
 }
 
-#ifdef SQLITE_ENABLE_EXPLAIN_COMMENTS
-/*
-** This function is used to add VdbeComment() annotations to a VDBE
-** program. It is not used in production code, only for debugging.
-*/
-static const char *onErrorText(int onError){
-  switch( onError ){
-    case OE_Abort:    return "abort";
-    case OE_Rollback: return "rollback";
-    case OE_Fail:     return "fail";
-    case OE_Replace:  return "replace";
-    case OE_Ignore:   return "ignore";
-    case OE_Default:  return "default";
-  }
-  return "n/a";
-}
-#endif
-
-/*
-** Parse context structure pFrom has just been used to create a sub-vdbe
-** (trigger program). If an error has occurred, transfer error information
-** from pFrom to pTo.
-*/
-static void transferParseError(Parse *pTo, Parse *pFrom){
-  assert( pFrom->zErrMsg==0 || pFrom->nErr );
-  assert( pTo->zErrMsg==0 || pTo->nErr );
-  if( pTo->nErr==0 ){
-    pTo->zErrMsg = pFrom->zErrMsg;
-    pTo->nErr = pFrom->nErr;
-    pTo->rc = pFrom->rc;
-  }else{
-    sqlite3DbFree(pFrom->db, pFrom->zErrMsg);
-  }
-}
-
-/*
-** Create and populate a new TriggerPrg object with a sub-program 
-** implementing trigger pTrigger with ON CONFLICT policy orconf.
-*/
-static TriggerPrg *codeRowTrigger(
-  Parse *pParse,       /* Current parse context */
-  Trigger *pTrigger,   /* Trigger to code */
-  Table *pTab,         /* The table pTrigger is attached to */
-  int orconf           /* ON CONFLICT policy to code trigger program with */
-){
-  Parse *pTop = sqlite3ParseToplevel(pParse);
-  sqlite3 *db = pParse->db;   /* Database handle */
-  TriggerPrg *pPrg;           /* Value to return */
-  Expr *pWhen = 0;            /* Duplicate of trigger WHEN expression */
-  Vdbe *v;                    /* Temporary VM */
-  NameContext sNC;            /* Name context for sub-vdbe */
-  SubProgram *pProgram = 0;   /* Sub-vdbe for trigger program */
-  Parse *pSubParse;           /* Parse context for sub-vdbe */
-  int iEndTrigger = 0;        /* Label to jump to if WHEN is false */
-
-  assert( pTrigger->zName==0 || pTab==tableOfTrigger(pTrigger) );
-  assert( pTop->pVdbe );
-
-  /* Allocate the TriggerPrg and SubProgram objects. To ensure that they
-  ** are freed if an error occurs, link them into the Parse.pTriggerPrg 
-  ** list of the top-level Parse object sooner rather than later.  */
-  pPrg = sqlite3DbMallocZero(db, sizeof(TriggerPrg));
-  if( !pPrg ) return 0;
-  pPrg->pNext = pTop->pTriggerPrg;
-  pTop->pTriggerPrg = pPrg;
-  pPrg->pProgram = pProgram = sqlite3DbMallocZero(db, sizeof(SubProgram));
-  if( !pProgram ) return 0;
-  sqlite3VdbeLinkSubProgram(pTop->pVdbe, pProgram);
-  pPrg->pTrigger = pTrigger;
-  pPrg->orconf = orconf;
-  pPrg->aColmask[0] = 0xffffffff;
-  pPrg->aColmask[1] = 0xffffffff;
-
-  /* Allocate and populate a new Parse context to use for coding the 
-  ** trigger sub-program.  */
-  pSubParse = sqlite3StackAllocZero(db, sizeof(Parse));
-  if( !pSubParse ) return 0;
-  memset(&sNC, 0, sizeof(sNC));
-  sNC.pParse = pSubParse;
-  pSubParse->db = db;
-  pSubParse->pTriggerTab = pTab;
-  pSubParse->pToplevel = pTop;
-  pSubParse->zAuthContext = pTrigger->zName;
-  pSubParse->eTriggerOp = pTrigger->op;
-  pSubParse->nQueryLoop = pParse->nQueryLoop;
-
-  v = sqlite3GetVdbe(pSubParse);
-  if( v ){
-    VdbeComment((v, "Start: %s.%s (%s %s%s%s ON %s)", 
-      pTrigger->zName, onErrorText(orconf),
-      (pTrigger->tr_tm==TRIGGER_BEFORE ? "BEFORE" : "AFTER"),
-        (pTrigger->op==TK_UPDATE ? "UPDATE" : ""),
-        (pTrigger->op==TK_INSERT ? "INSERT" : ""),
-        (pTrigger->op==TK_DELETE ? "DELETE" : ""),
-      pTab->zName
-    ));
-#ifndef SQLITE_OMIT_TRACE
-    sqlite3VdbeChangeP4(v, -1, 
-      sqlite3MPrintf(db, "-- TRIGGER %s", pTrigger->zName), P4_DYNAMIC
-    );
-#endif
-
-    /* If one was specified, code the WHEN clause. If it evaluates to false
-    ** (or NULL) the sub-vdbe is immediately halted by jumping to the 
-    ** OP_Halt inserted at the end of the program.  */
-    if( pTrigger->pWhen ){
-      pWhen = sqlite3ExprDup(db, pTrigger->pWhen, 0);
-      if( SQLITE_OK==sqlite3ResolveExprNames(&sNC, pWhen) 
-       && db->mallocFailed==0 
-      ){
-        iEndTrigger = sqlite3VdbeMakeLabel(v);
-        sqlite3ExprIfFalse(pSubParse, pWhen, iEndTrigger, SQLITE_JUMPIFNULL);
-      }
-      sqlite3ExprDelete(db, pWhen);
-    }
-
-    /* Code the trigger program into the sub-vdbe. */
-    codeTriggerProgram(pSubParse, pTrigger->step_list, orconf);
-
-    /* Insert an OP_Halt at the end of the sub-program. */
-    if( iEndTrigger ){
-      sqlite3VdbeResolveLabel(v, iEndTrigger);
-    }
-    sqlite3VdbeAddOp0(v, OP_Halt);
-    VdbeComment((v, "End: %s.%s", pTrigger->zName, onErrorText(orconf)));
-
-    transferParseError(pParse, pSubParse);
-    if( db->mallocFailed==0 ){
-      pProgram->aOp = sqlite3VdbeTakeOpArray(v, &pProgram->nOp, &pTop->nMaxArg);
-    }
-    pProgram->nMem = pSubParse->nMem;
-    pProgram->nCsr = pSubParse->nTab;
-    pProgram->token = (void *)pTrigger;
-    pPrg->aColmask[0] = pSubParse->oldmask;
-    pPrg->aColmask[1] = pSubParse->newmask;
-    sqlite3VdbeDelete(v);
-  }
-
-  assert( !pSubParse->pAinc       && !pSubParse->pZombieTab );
-  assert( !pSubParse->pTriggerPrg && !pSubParse->nMaxArg );
-  sqlite3ParserReset(pSubParse);
-  sqlite3StackFree(db, pSubParse);
-
-  return pPrg;
-}
-    
-/*
-** Return a pointer to a TriggerPrg object containing the sub-program for
-** trigger pTrigger with default ON CONFLICT algorithm orconf. If no such
-** TriggerPrg object exists, a new object is allocated and populated before
-** being returned.
-*/
-static TriggerPrg *getRowTrigger(
-  Parse *pParse,       /* Current parse context */
-  Trigger *pTrigger,   /* Trigger to code */
-  Table *pTab,         /* The table trigger pTrigger is attached to */
-  int orconf           /* ON CONFLICT algorithm. */
-){
-  Parse *pRoot = sqlite3ParseToplevel(pParse);
-  TriggerPrg *pPrg;
-
-  assert( pTrigger->zName==0 || pTab==tableOfTrigger(pTrigger) );
-
-  /* It may be that this trigger has already been coded (or is in the
-  ** process of being coded). If this is the case, then an entry with
-  ** a matching TriggerPrg.pTrigger field will be present somewhere
-  ** in the Parse.pTriggerPrg list. Search for such an entry.  */
-  for(pPrg=pRoot->pTriggerPrg; 
-      pPrg && (pPrg->pTrigger!=pTrigger || pPrg->orconf!=orconf); 
-      pPrg=pPrg->pNext
-  );
-
-  /* If an existing TriggerPrg could not be located, create a new one. */
-  if( !pPrg ){
-    pPrg = codeRowTrigger(pParse, pTrigger, pTab, orconf);
-  }
-
-  return pPrg;
-}
-
-/*
-** Generate code for the trigger program associated with trigger p on 
-** table pTab. The reg, orconf and ignoreJump parameters passed to this
-** function are the same as those described in the header function for
-** sqlite3CodeRowTrigger()
-*/
-void sqlite3CodeRowTriggerDirect(
-  Parse *pParse,       /* Parse context */
-  Trigger *p,          /* Trigger to code */
-  Table *pTab,         /* The table to code triggers from */
-  int reg,             /* Reg array containing OLD.* and NEW.* values */
-  int orconf,          /* ON CONFLICT policy */
-  int ignoreJump       /* Instruction to jump to for RAISE(IGNORE) */
-){
-  Vdbe *v = sqlite3GetVdbe(pParse); /* Main VM */
-  TriggerPrg *pPrg;
-  pPrg = getRowTrigger(pParse, p, pTab, orconf);
-  assert( pPrg || pParse->nErr || pParse->db->mallocFailed );
-
-  /* Code the OP_Program opcode in the parent VDBE. P4 of the OP_Program 
-  ** is a pointer to the sub-vdbe containing the trigger program.  */
-  if( pPrg ){
-    int bRecursive = (p->zName && 0==(pParse->db->flags&SQLITE_RecTriggers));
-
-    sqlite3VdbeAddOp4(v, OP_Program, reg, ignoreJump, ++pParse->nMem,
-                      (const char *)pPrg->pProgram, P4_SUBPROGRAM);
-    VdbeComment(
-        (v, "Call: %s.%s", (p->zName?p->zName:"fkey"), onErrorText(orconf)));
-
-    /* Set the P5 operand of the OP_Program instruction to non-zero if
-    ** recursive invocation of this trigger program is disallowed. Recursive
-    ** invocation is disallowed if (a) the sub-program is really a trigger,
-    ** not a foreign key action, and (b) the flag to enable recursive triggers
-    ** is clear.  */
-    sqlite3VdbeChangeP5(v, (u8)bRecursive);
-  }
-}
-
 /*
-** This is called to code the required FOR EACH ROW triggers for an operation
-** on table pTab. The operation to code triggers for (INSERT, UPDATE or DELETE)
-** is given by the op parameter. The tr_tm parameter determines whether the
-** BEFORE or AFTER triggers are coded. If the operation is an UPDATE, then
-** parameter pChanges is passed the list of columns being modified.
+** This is called to code FOR EACH ROW triggers.
+**
+** When the code that this function generates is executed, the following 
+** must be true:
 **
-** If there are no triggers that fire at the specified time for the specified
-** operation on pTab, this function is a no-op.
+** 1. No cursors may be open in the main database.  (But newIdx and oldIdx
+**    can be indices of cursors in temporary tables.  See below.)
 **
-** The reg argument is the address of the first in an array of registers 
-** that contain the values substituted for the new.* and old.* references
-** in the trigger program. If N is the number of columns in table pTab
-** (a copy of pTab->nCol), then registers are populated as follows:
+** 2. If the triggers being coded are ON INSERT or ON UPDATE triggers, then
+**    a temporary vdbe cursor (index newIdx) must be open and pointing at
+**    a row containing values to be substituted for new.* expressions in the
+**    trigger program(s).
 **
-**   Register       Contains
-**   ------------------------------------------------------
-**   reg+0          OLD.rowid
-**   reg+1          OLD.* value of left-most column of pTab
-**   ...            ...
-**   reg+N          OLD.* value of right-most column of pTab
-**   reg+N+1        NEW.rowid
-**   reg+N+2        OLD.* value of left-most column of pTab
-**   ...            ...
-**   reg+N+N+1      NEW.* value of right-most column of pTab
+** 3. If the triggers being coded are ON DELETE or ON UPDATE triggers, then
+**    a temporary vdbe cursor (index oldIdx) must be open and pointing at
+**    a row containing values to be substituted for old.* expressions in the
+**    trigger program(s).
 **
-** For ON DELETE triggers, the registers containing the NEW.* values will
-** never be accessed by the trigger program, so they are not allocated or 
-** populated by the caller (there is no data to populate them with anyway). 
-** Similarly, for ON INSERT triggers the values stored in the OLD.* registers
-** are never accessed, and so are not allocated by the caller. So, for an
-** ON INSERT trigger, the value passed to this function as parameter reg
-** is not a readable register, although registers (reg+N) through 
-** (reg+N+N+1) are.
+** If they are not NULL, the piOldColMask and piNewColMask output variables
+** are set to values that describe the columns used by the trigger program
+** in the OLD.* and NEW.* tables respectively. If column N of the 
+** pseudo-table is read at least once, the corresponding bit of the output
+** mask is set. If a column with an index greater than 32 is read, the
+** output mask is set to the special value 0xffffffff.
 **
-** Parameter orconf is the default conflict resolution algorithm for the
-** trigger program to use (REPLACE, IGNORE etc.). Parameter ignoreJump
-** is the instruction that control should jump to if a trigger program
-** raises an IGNORE exception.
 */
-void sqlite3CodeRowTrigger(
+int sqlite3CodeRowTrigger(
   Parse *pParse,       /* Parse context */
   Trigger *pTrigger,   /* List of triggers on table pTab */
   int op,              /* One of TK_UPDATE, TK_INSERT, TK_DELETE */
   ExprList *pChanges,  /* Changes list for any UPDATE OF triggers */
   int tr_tm,           /* One of TRIGGER_BEFORE, TRIGGER_AFTER */
   Table *pTab,         /* The table to code triggers from */
-  int reg,             /* The first in an array of registers (see above) */
+  int newIdx,          /* The indice of the "new" row to access */
+  int oldIdx,          /* The indice of the "old" row to access */
   int orconf,          /* ON CONFLICT policy */
-  int ignoreJump       /* Instruction to jump to for RAISE(IGNORE) */
+  int ignoreJump,      /* Instruction to jump to for RAISE(IGNORE) */
+  u32 *piOldColMask,   /* OUT: Mask of columns used from the OLD.* table */
+  u32 *piNewColMask    /* OUT: Mask of columns used from the NEW.* table */
 ){
-  Trigger *p;          /* Used to iterate through pTrigger list */
+  Trigger *p;
+  sqlite3 *db = pParse->db;
+  TriggerStack trigStackEntry;
+
+  trigStackEntry.oldColMask = 0;
+  trigStackEntry.newColMask = 0;
 
-  assert( op==TK_UPDATE || op==TK_INSERT || op==TK_DELETE );
-  assert( tr_tm==TRIGGER_BEFORE || tr_tm==TRIGGER_AFTER );
-  assert( (op==TK_UPDATE)==(pChanges!=0) );
+  assert(op == TK_UPDATE || op == TK_INSERT || op == TK_DELETE);
+  assert(tr_tm == TRIGGER_BEFORE || tr_tm == TRIGGER_AFTER );
+
+  assert(newIdx != -1 || oldIdx != -1);
 
   for(p=pTrigger; p; p=p->pNext){
+    int fire_this = 0;
 
     /* Sanity checking:  The schema for the trigger and for the table are
     ** always defined.  The trigger must be in the same schema as the table
     ** or else it must be a TEMP trigger. */
     assert( p->pSchema!=0 );
     assert( p->pTabSchema!=0 );
-    assert( p->pSchema==p->pTabSchema 
-         || p->pSchema==pParse->db->aDb[1].pSchema );
+    assert( p->pSchema==p->pTabSchema || p->pSchema==db->aDb[1].pSchema );
 
     /* Determine whether we should code this trigger */
-    if( p->op==op 
-     && p->tr_tm==tr_tm 
-     && checkColumnOverlap(p->pColumns, pChanges)
+    if( 
+      p->op==op && 
+      p->tr_tm==tr_tm && 
+      checkColumnOverlap(p->pColumns,pChanges)
     ){
-      sqlite3CodeRowTriggerDirect(pParse, p, pTab, reg, orconf, ignoreJump);
+      TriggerStack *pS;      /* Pointer to trigger-stack entry */
+      for(pS=pParse->trigStack; pS && p!=pS->pTrigger; pS=pS->pNext){}
+      if( !pS ){
+        fire_this = 1;
+      }
+#if 0    /* Give no warning for recursive triggers.  Just do not do them */
+      else{
+        sqlite3ErrorMsg(pParse, "recursive triggers not supported (%s)",
+            p->name);
+        return SQLITE_ERROR;
+      }
+#endif
     }
-  }
-}
+ 
+    if( fire_this ){
+      int endTrigger;
+      Expr * whenExpr;
+      AuthContext sContext;
+      NameContext sNC;
 
-/*
-** Triggers may access values stored in the old.* or new.* pseudo-table. 
-** This function returns a 32-bit bitmask indicating which columns of the 
-** old.* or new.* tables actually are used by triggers. This information 
-** may be used by the caller, for example, to avoid having to load the entire
-** old.* record into memory when executing an UPDATE or DELETE command.
-**
-** Bit 0 of the returned mask is set if the left-most column of the
-** table may be accessed using an [old|new].<col> reference. Bit 1 is set if
-** the second leftmost column value is required, and so on. If there
-** are more than 32 columns in the table, and at least one of the columns
-** with an index greater than 32 may be accessed, 0xffffffff is returned.
-**
-** It is not possible to determine if the old.rowid or new.rowid column is 
-** accessed by triggers. The caller must always assume that it is.
-**
-** Parameter isNew must be either 1 or 0. If it is 0, then the mask returned
-** applies to the old.* table. If 1, the new.* table.
-**
-** Parameter tr_tm must be a mask with one or both of the TRIGGER_BEFORE
-** and TRIGGER_AFTER bits set. Values accessed by BEFORE triggers are only
-** included in the returned mask if the TRIGGER_BEFORE bit is set in the
-** tr_tm parameter. Similarly, values accessed by AFTER triggers are only
-** included in the returned mask if the TRIGGER_AFTER bit is set in tr_tm.
-*/
-u32 sqlite3TriggerColmask(
-  Parse *pParse,       /* Parse context */
-  Trigger *pTrigger,   /* List of triggers on table pTab */
-  ExprList *pChanges,  /* Changes list for any UPDATE OF triggers */
-  int isNew,           /* 1 for new.* ref mask, 0 for old.* ref mask */
-  int tr_tm,           /* Mask of TRIGGER_BEFORE|TRIGGER_AFTER */
-  Table *pTab,         /* The table to code triggers from */
-  int orconf           /* Default ON CONFLICT policy for trigger steps */
-){
-  const int op = pChanges ? TK_UPDATE : TK_DELETE;
-  u32 mask = 0;
-  Trigger *p;
+#ifndef SQLITE_OMIT_TRACE
+      sqlite3VdbeAddOp4(pParse->pVdbe, OP_Trace, 0, 0, 0,
+                        sqlite3MPrintf(db, "-- TRIGGER %s", p->name),
+                        P4_DYNAMIC);
+#endif
+      memset(&sNC, 0, sizeof(sNC));
+      sNC.pParse = pParse;
 
-  assert( isNew==1 || isNew==0 );
-  for(p=pTrigger; p; p=p->pNext){
-    if( p->op==op && (tr_tm&p->tr_tm)
-     && checkColumnOverlap(p->pColumns,pChanges)
-    ){
-      TriggerPrg *pPrg;
-      pPrg = getRowTrigger(pParse, p, pTab, orconf);
-      if( pPrg ){
-        mask |= pPrg->aColmask[isNew];
+      /* Push an entry on to the trigger stack */
+      trigStackEntry.pTrigger = p;
+      trigStackEntry.newIdx = newIdx;
+      trigStackEntry.oldIdx = oldIdx;
+      trigStackEntry.pTab = pTab;
+      trigStackEntry.pNext = pParse->trigStack;
+      trigStackEntry.ignoreJump = ignoreJump;
+      pParse->trigStack = &trigStackEntry;
+      sqlite3AuthContextPush(pParse, &sContext, p->name);
+
+      /* code the WHEN clause */
+      endTrigger = sqlite3VdbeMakeLabel(pParse->pVdbe);
+      whenExpr = sqlite3ExprDup(db, p->pWhen, 0);
+      if( db->mallocFailed || sqlite3ResolveExprNames(&sNC, whenExpr) ){
+        pParse->trigStack = trigStackEntry.pNext;
+        sqlite3ExprDelete(db, whenExpr);
+        return 1;
       }
+      sqlite3ExprIfFalse(pParse, whenExpr, endTrigger, SQLITE_JUMPIFNULL);
+      sqlite3ExprDelete(db, whenExpr);
+
+      codeTriggerProgram(pParse, p->step_list, orconf); 
+
+      /* Pop the entry off the trigger stack */
+      pParse->trigStack = trigStackEntry.pNext;
+      sqlite3AuthContextPop(&sContext);
+
+      sqlite3VdbeResolveLabel(pParse->pVdbe, endTrigger);
     }
   }
-
-  return mask;
+  if( piOldColMask ) *piOldColMask |= trigStackEntry.oldColMask;
+  if( piNewColMask ) *piNewColMask |= trigStackEntry.newColMask;
+  return 0;
 }
-
 #endif /* !defined(SQLITE_OMIT_TRIGGER) */
