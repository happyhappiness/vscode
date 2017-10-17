 ** the way through and which will need to undo some writes without having to
 ** rollback the whole transaction.  For operations where all constraints
 ** can be checked before any changes are made to the database, it is never
 ** necessary to undo a write and the checkpoint should not be set.
 */
 void sqlite3BeginWriteOperation(Parse *pParse, int setStatement, int iDb){
-  Parse *pToplevel = sqlite3ParseToplevel(pParse);
   sqlite3CodeVerifySchema(pParse, iDb);
-  DbMaskSet(pToplevel->writeMask, iDb);
-  pToplevel->isMultiWrite |= setStatement;
-}
-
-/*
-** Indicate that the statement currently under construction might write
-** more than one entry (example: deleting one row then inserting another,
-** inserting multiple rows in a table, or inserting a row and index entries.)
-** If an abort occurs after some of these writes have completed, then it will
-** be necessary to undo the completed writes.
-*/
-void sqlite3MultiWrite(Parse *pParse){
-  Parse *pToplevel = sqlite3ParseToplevel(pParse);
-  pToplevel->isMultiWrite = 1;
-}
-
-/* 
-** The code generator calls this routine if is discovers that it is
-** possible to abort a statement prior to completion.  In order to 
-** perform this abort without corrupting the database, we need to make
-** sure that the statement is protected by a statement transaction.
-**
-** Technically, we only need to set the mayAbort flag if the
-** isMultiWrite flag was previously set.  There is a time dependency
-** such that the abort must occur after the multiwrite.  This makes
-** some statements involving the REPLACE conflict resolution algorithm
-** go a little faster.  But taking advantage of this time dependency
-** makes it more difficult to prove that the code is correct (in 
-** particular, it prevents us from writing an effective
-** implementation of sqlite3AssertMayAbort()) and so we have chosen
-** to take the safe route and skip the optimization.
-*/
-void sqlite3MayAbort(Parse *pParse){
-  Parse *pToplevel = sqlite3ParseToplevel(pParse);
-  pToplevel->mayAbort = 1;
-}
-
-/*
-** Code an OP_Halt that causes the vdbe to return an SQLITE_CONSTRAINT
-** error. The onError parameter determines which (if any) of the statement
-** and/or current transaction is rolled back.
-*/
-void sqlite3HaltConstraint(
-  Parse *pParse,    /* Parsing context */
-  int errCode,      /* extended error code */
-  int onError,      /* Constraint type */
-  char *p4,         /* Error message */
-  i8 p4type,        /* P4_STATIC or P4_TRANSIENT */
-  u8 p5Errmsg       /* P5_ErrMsg type */
-){
-  Vdbe *v = sqlite3GetVdbe(pParse);
-  assert( (errCode&0xff)==SQLITE_CONSTRAINT );
-  if( onError==OE_Abort ){
-    sqlite3MayAbort(pParse);
-  }
-  sqlite3VdbeAddOp4(v, OP_Halt, errCode, onError, 0, p4, p4type);
-  sqlite3VdbeChangeP5(v, p5Errmsg);
-}
-
-/*
-** Code an OP_Halt due to UNIQUE or PRIMARY KEY constraint violation.
-*/
-void sqlite3UniqueConstraint(
-  Parse *pParse,    /* Parsing context */
-  int onError,      /* Constraint type */
-  Index *pIdx       /* The index that triggers the constraint */
-){
-  char *zErr;
-  int j;
-  StrAccum errMsg;
-  Table *pTab = pIdx->pTable;
-
-  sqlite3StrAccumInit(&errMsg, pParse->db, 0, 0, 200);
-  if( pIdx->aColExpr ){
-    sqlite3XPrintf(&errMsg, "index '%q'", pIdx->zName);
-  }else{
-    for(j=0; j<pIdx->nKeyCol; j++){
-      char *zCol;
-      assert( pIdx->aiColumn[j]>=0 );
-      zCol = pTab->aCol[pIdx->aiColumn[j]].zName;
-      if( j ) sqlite3StrAccumAppend(&errMsg, ", ", 2);
-      sqlite3StrAccumAppendAll(&errMsg, pTab->zName);
-      sqlite3StrAccumAppend(&errMsg, ".", 1);
-      sqlite3StrAccumAppendAll(&errMsg, zCol);
-    }
-  }
-  zErr = sqlite3StrAccumFinish(&errMsg);
-  sqlite3HaltConstraint(pParse, 
-    IsPrimaryKeyIndex(pIdx) ? SQLITE_CONSTRAINT_PRIMARYKEY 
-                            : SQLITE_CONSTRAINT_UNIQUE,
-    onError, zErr, P4_DYNAMIC, P5_ConstraintUnique);
-}
-
-
-/*
-** Code an OP_Halt due to non-unique rowid.
-*/
-void sqlite3RowidConstraint(
-  Parse *pParse,    /* Parsing context */
-  int onError,      /* Conflict resolution algorithm */
-  Table *pTab       /* The table with the non-unique rowid */ 
-){
-  char *zMsg;
-  int rc;
-  if( pTab->iPKey>=0 ){
-    zMsg = sqlite3MPrintf(pParse->db, "%s.%s", pTab->zName,
-                          pTab->aCol[pTab->iPKey].zName);
-    rc = SQLITE_CONSTRAINT_PRIMARYKEY;
-  }else{
-    zMsg = sqlite3MPrintf(pParse->db, "%s.rowid", pTab->zName);
-    rc = SQLITE_CONSTRAINT_ROWID;
+  pParse->writeMask |= 1<<iDb;
+  if( setStatement && pParse->nested==0 ){
+    /* Every place where this routine is called with setStatement!=0 has
+    ** already successfully created a VDBE. */
+    assert( pParse->pVdbe );
+    sqlite3VdbeAddOp1(pParse->pVdbe, OP_Statement, iDb);
   }
-  sqlite3HaltConstraint(pParse, rc, onError, zMsg, P4_DYNAMIC,
-                        P5_ConstraintUnique);
 }
 
 /*
 ** Check to see if pIndex uses the collating sequence pColl.  Return
 ** true if it does and false if it does not.
 */
 #ifndef SQLITE_OMIT_REINDEX
 static int collationMatch(const char *zColl, Index *pIndex){
   int i;
   assert( zColl!=0 );
   for(i=0; i<pIndex->nColumn; i++){
     const char *z = pIndex->azColl[i];
-    assert( z!=0 || pIndex->aiColumn[i]<0 );
-    if( pIndex->aiColumn[i]>=0 && 0==sqlite3StrICmp(z, zColl) ){
+    assert( z!=0 );
+    if( 0==sqlite3StrICmp(z, zColl) ){
       return 1;
     }
   }
   return 0;
 }
 #endif
