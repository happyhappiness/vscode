    *pMask = mask;
  }
  return (mask ? pList : 0);
}

/*
** Convert the pStep->target token into a SrcList and return a pointer
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
  int iDb;             /* Index of the database to use */
  SrcList *pSrc;       /* SrcList to be returned */

  pSrc = sqlite3SrcListAppend(pParse->db, 0, &pStep->target, 0);
  if( pSrc ){
    assert( pSrc->nSrc>0 );
    assert( pSrc->a!=0 );
    iDb = sqlite3SchemaToIndex(pParse->db, pStep->pTrig->pSchema);
    if( iDb==0 || iDb>=2 ){
      sqlite3 *db = pParse->db;
      assert( iDb<pParse->db->nDb );
      pSrc->a[pSrc->nSrc-1].zDatabase = sqlite3DbStrDup(db, db->aDb[iDb].zName);
    }
  }
  return pSrc;
}

/*
** Generate VDBE code for zero or more statements inside the body of a
** trigger.  
*/
static int codeTriggerProgram(
  Parse *pParse,            /* The parser context */
  TriggerStep *pStepList,   /* List of statements inside the trigger body */
  int orconfin              /* Conflict algorithm. (OE_Abort, etc) */  
){
  TriggerStep * pTriggerStep = pStepList;
  int orconf;
  Vdbe *v = pParse->pVdbe;
  sqlite3 *db = pParse->db;

  assert( pTriggerStep!=0 );
  assert( v!=0 );
  sqlite3VdbeAddOp2(v, OP_ContextPush, 0, 0);
  VdbeComment((v, "begin trigger %s", pStepList->pTrig->name));
  while( pTriggerStep ){
    sqlite3ExprCacheClear(pParse);
    orconf = (orconfin == OE_Default)?pTriggerStep->orconf:orconfin;
    pParse->trigStack->orconf = orconf;
    switch( pTriggerStep->op ){
      case TK_UPDATE: {
        SrcList *pSrc;
        pSrc = targetSrcList(pParse, pTriggerStep);
        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
        sqlite3Update(pParse, pSrc,
                sqlite3ExprListDup(db, pTriggerStep->pExprList, 0), 
                sqlite3ExprDup(db, pTriggerStep->pWhere, 0), orconf);
        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
        break;
      }
      case TK_INSERT: {
        SrcList *pSrc;
        pSrc = targetSrcList(pParse, pTriggerStep);
        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
        sqlite3Insert(pParse, pSrc,
          sqlite3ExprListDup(db, pTriggerStep->pExprList, 0), 
          sqlite3SelectDup(db, pTriggerStep->pSelect, 0), 
          sqlite3IdListDup(db, pTriggerStep->pIdList), orconf);
        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
        break;
      }
      case TK_DELETE: {
        SrcList *pSrc;
        sqlite3VdbeAddOp2(v, OP_ResetCount, 0, 0);
        pSrc = targetSrcList(pParse, pTriggerStep);
        sqlite3DeleteFrom(pParse, pSrc, 
                          sqlite3ExprDup(db, pTriggerStep->pWhere, 0));
        sqlite3VdbeAddOp2(v, OP_ResetCount, 1, 0);
        break;
      }
      default: assert( pTriggerStep->op==TK_SELECT ); {
        Select *ss = sqlite3SelectDup(db, pTriggerStep->pSelect, 0);
        if( ss ){
          SelectDest dest;

          sqlite3SelectDestInit(&dest, SRT_Discard, 0);
          sqlite3Select(pParse, ss, &dest);
          sqlite3SelectDelete(db, ss);
        }
        break;
      }
    } 
    pTriggerStep = pTriggerStep->pNext;
  }
  sqlite3VdbeAddOp2(v, OP_ContextPop, 0, 0);
  VdbeComment((v, "end trigger %s", pStepList->pTrig->name));

  return 0;
}

/*
** This is called to code FOR EACH ROW triggers.
**
** When the code that this function generates is executed, the following 
** must be true:
**
** 1. No cursors may be open in the main database.  (But newIdx and oldIdx
**    can be indices of cursors in temporary tables.  See below.)
**
** 2. If the triggers being coded are ON INSERT or ON UPDATE triggers, then
**    a temporary vdbe cursor (index newIdx) must be open and pointing at
**    a row containing values to be substituted for new.* expressions in the
**    trigger program(s).
**
** 3. If the triggers being coded are ON DELETE or ON UPDATE triggers, then
**    a temporary vdbe cursor (index oldIdx) must be open and pointing at
**    a row containing values to be substituted for old.* expressions in the
**    trigger program(s).
**
** If they are not NULL, the piOldColMask and piNewColMask output variables
** are set to values that describe the columns used by the trigger program
** in the OLD.* and NEW.* tables respectively. If column N of the 
** pseudo-table is read at least once, the corresponding bit of the output
** mask is set. If a column with an index greater than 32 is read, the
** output mask is set to the special value 0xffffffff.
**
*/
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
#endif /* !defined(SQLITE_OMIT_TRIGGER) */
