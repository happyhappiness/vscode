int sqlite3CodeRowTrigger(
  Parse *pParse,       /* Parse context */
  Trigger *pTrigger,   /* List of triggers on table pTab */
  int op,              /* One of TK_UPDATE, TK_INSERT, TK_DELETE */
  ExprList *pChanges,  /* Changes list for any UPDATE OF triggers */
  int tr_tm,           /* One of TRIGGER_BEFORE, TRIGGER_AFTER */
  Table *pTab,         /* The table to code triggers from */
  int newIdx,          /* The indice of the "new" row to access */
  int oldIdx,          /* The indice of the "old" row to access */
  int orconf,          /* ON CONFLICT policy */
  int ignoreJump,      /* Instruction to jump to for RAISE(IGNORE) */
  u32 *piOldColMask,   /* OUT: Mask of columns used from the OLD.* table */
  u32 *piNewColMask    /* OUT: Mask of columns used from the NEW.* table */
){
  Trigger *p;
  sqlite3 *db = pParse->db;
  TriggerStack trigStackEntry;

  trigStackEntry.oldColMask = 0;
  trigStackEntry.newColMask = 0;

  assert(op == TK_UPDATE || op == TK_INSERT || op == TK_DELETE);
  assert(tr_tm == TRIGGER_BEFORE || tr_tm == TRIGGER_AFTER );

  assert(newIdx != -1 || oldIdx != -1);

  for(p=pTrigger; p; p=p->pNext){
    int fire_this = 0;

    /* Sanity checking:  The schema for the trigger and for the table are
    ** always defined.  The trigger must be in the same schema as the table
    ** or else it must be a TEMP trigger. */
    assert( p->pSchema!=0 );
    assert( p->pTabSchema!=0 );
    assert( p->pSchema==p->pTabSchema || p->pSchema==db->aDb[1].pSchema );

    /* Determine whether we should code this trigger */
    if( 
      p->op==op && 
      p->tr_tm==tr_tm && 
      checkColumnOverlap(p->pColumns,pChanges)
    ){
      TriggerStack *pS;      /* Pointer to trigger-stack entry */
      for(pS=pParse->trigStack; pS && p!=pS->pTrigger; pS=pS->pNext){}
      if( !pS ){
        fire_this = 1;
      }
#if 0    /* Give no warning for recursive triggers.  Just do not do them */
      else{
        sqlite3ErrorMsg(pParse, "recursive triggers not supported (%s)",
            p->name);
        return SQLITE_ERROR;
      }
#endif
    }
 
    if( fire_this ){
      int endTrigger;
      Expr * whenExpr;
      AuthContext sContext;
      NameContext sNC;

#ifndef SQLITE_OMIT_TRACE
      sqlite3VdbeAddOp4(pParse->pVdbe, OP_Trace, 0, 0, 0,
                        sqlite3MPrintf(db, "-- TRIGGER %s", p->name),
                        P4_DYNAMIC);
#endif
      memset(&sNC, 0, sizeof(sNC));
      sNC.pParse = pParse;

      /* Push an entry on to the trigger stack */
      trigStackEntry.pTrigger = p;
      trigStackEntry.newIdx = newIdx;
      trigStackEntry.oldIdx = oldIdx;
      trigStackEntry.pTab = pTab;
      trigStackEntry.pNext = pParse->trigStack;
      trigStackEntry.ignoreJump = ignoreJump;
      pParse->trigStack = &trigStackEntry;
      sqlite3AuthContextPush(pParse, &sContext, p->name);

      /* code the WHEN clause */
      endTrigger = sqlite3VdbeMakeLabel(pParse->pVdbe);
      whenExpr = sqlite3ExprDup(db, p->pWhen, 0);
      if( db->mallocFailed || sqlite3ResolveExprNames(&sNC, whenExpr) ){
        pParse->trigStack = trigStackEntry.pNext;
        sqlite3ExprDelete(db, whenExpr);
        return 1;
      }
      sqlite3ExprIfFalse(pParse, whenExpr, endTrigger, SQLITE_JUMPIFNULL);
      sqlite3ExprDelete(db, whenExpr);

      codeTriggerProgram(pParse, p->step_list, orconf); 

      /* Pop the entry off the trigger stack */
      pParse->trigStack = trigStackEntry.pNext;
      sqlite3AuthContextPop(&sContext);

      sqlite3VdbeResolveLabel(pParse->pVdbe, endTrigger);
    }
  }
  if( piOldColMask ) *piOldColMask |= trigStackEntry.oldColMask;
  if( piNewColMask ) *piNewColMask |= trigStackEntry.newColMask;
  return 0;
}