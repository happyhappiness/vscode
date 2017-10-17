 ** See also: Destroy
 */
 case OP_Clear: {
   int nChange;
  
   nChange = 0;
-  assert( p->readOnly==0 );
-  assert( DbMaskTest(p->btreeMask, pOp->p2) );
+  assert( (p->btreeMask & (1<<pOp->p2))!=0 );
   rc = sqlite3BtreeClearTable(
       db->aDb[pOp->p2].pBt, pOp->p1, (pOp->p3 ? &nChange : 0)
   );
   if( pOp->p3 ){
     p->nChange += nChange;
     if( pOp->p3>0 ){
-      assert( memIsValid(&aMem[pOp->p3]) );
-      memAboutToChange(p, &aMem[pOp->p3]);
-      aMem[pOp->p3].u.i += nChange;
+      p->aMem[pOp->p3].u.i += nChange;
     }
   }
-  if( rc ) goto abort_due_to_error;
   break;
 }
 
-/* Opcode: ResetSorter P1 * * * *
+/* Opcode: CreateTable P1 P2 * * *
+**
+** Allocate a new table in the main database file if P1==0 or in the
+** auxiliary database file if P1==1 or in an attached database if
+** P1>1.  Write the root page number of the new table into
+** register P2
 **
-** Delete all contents from the ephemeral table or sorter
-** that is open on cursor P1.
+** The difference between a table and an index is this:  A table must
+** have a 4-byte integer key and can have arbitrary data.  An index
+** has an arbitrary key but no data.
 **
-** This opcode only works for cursors used for sorting and
-** opened with OP_OpenEphemeral or OP_SorterOpen.
+** See also: CreateIndex
 */
-case OP_ResetSorter: {
-  VdbeCursor *pC;
- 
-  assert( pOp->p1>=0 && pOp->p1<p->nCursor );
-  pC = p->apCsr[pOp->p1];
-  assert( pC!=0 );
-  if( isSorter(pC) ){
-    sqlite3VdbeSorterReset(db, pC->uc.pSorter);
-  }else{
-    assert( pC->eCurType==CURTYPE_BTREE );
-    assert( pC->isEphemeral );
-    rc = sqlite3BtreeClearTableOfCursor(pC->uc.pCursor);
-    if( rc ) goto abort_due_to_error;
-  }
-  break;
-}
-
-/* Opcode: CreateBtree P1 P2 P3 * *
-** Synopsis: r[P2]=root iDb=P1 flags=P3
+/* Opcode: CreateIndex P1 P2 * * *
+**
+** Allocate a new index in the main database file if P1==0 or in the
+** auxiliary database file if P1==1 or in an attached database if
+** P1>1.  Write the root page number of the new table into
+** register P2.
 **
-** Allocate a new b-tree in the main database file if P1==0 or in the
-** TEMP database file if P1==1 or in an attached database if
-** P1>1.  The P3 argument must be 1 (BTREE_INTKEY) for a rowid table
-** it must be 2 (BTREE_BLOBKEY) for a index or WITHOUT ROWID table.
-** The root page number of the new b-tree is stored in register P2.
+** See documentation on OP_CreateTable for additional information.
 */
-case OP_CreateBtree: {          /* out2 */
+case OP_CreateIndex:            /* out2-prerelease */
+case OP_CreateTable: {          /* out2-prerelease */
   int pgno;
+  int flags;
   Db *pDb;
 
-  pOut = out2Prerelease(p, pOp);
   pgno = 0;
-  assert( pOp->p3==BTREE_INTKEY || pOp->p3==BTREE_BLOBKEY );
   assert( pOp->p1>=0 && pOp->p1<db->nDb );
-  assert( DbMaskTest(p->btreeMask, pOp->p1) );
-  assert( p->readOnly==0 );
+  assert( (p->btreeMask & (1<<pOp->p1))!=0 );
   pDb = &db->aDb[pOp->p1];
   assert( pDb->pBt!=0 );
-  rc = sqlite3BtreeCreateTable(pDb->pBt, &pgno, pOp->p3);
-  if( rc ) goto abort_due_to_error;
+  if( pOp->opcode==OP_CreateTable ){
+    /* flags = BTREE_INTKEY; */
+    flags = BTREE_LEAFDATA|BTREE_INTKEY;
+  }else{
+    flags = BTREE_ZERODATA;
+  }
+  rc = sqlite3BtreeCreateTable(pDb->pBt, &pgno, flags);
   pOut->u.i = pgno;
+  MemSetTypeFlag(pOut, MEM_Int);
   break;
 }
 
-/* Opcode: SqlExec * * * P4 *
-**
-** Run the SQL statement or statements specified in the P4 string.
-*/
-case OP_SqlExec: {
-  db->nSqlExec++;
-  rc = sqlite3_exec(db, pOp->p4.z, 0, 0, 0);
-  db->nSqlExec--;
-  if( rc ) goto abort_due_to_error;
-  break;
-}
-
-/* Opcode: ParseSchema P1 * * P4 *
+/* Opcode: ParseSchema P1 P2 * P4 *
 **
 ** Read and parse all entries from the SQLITE_MASTER table of database P1
-** that match the WHERE clause P4. 
+** that match the WHERE clause P4.  P2 is the "force" flag.   Always do
+** the parsing if P2 is true.  If P2 is false, then this routine is a
+** no-op if the schema is not currently loaded.  In other words, if P2
+** is false, the SQLITE_MASTER table is only parsed if the rest of the
+** schema is already loaded into the symbol table.
 **
 ** This opcode invokes the parser to create a new virtual machine,
 ** then runs the new virtual machine.  It is thus a re-entrant opcode.
 */
 case OP_ParseSchema: {
   int iDb;
   const char *zMaster;
   char *zSql;
   InitData initData;
 
-  /* Any prepared statement that invokes this opcode will hold mutexes
-  ** on every btree.  This is a prerequisite for invoking 
-  ** sqlite3InitCallback().
-  */
-#ifdef SQLITE_DEBUG
-  for(iDb=0; iDb<db->nDb; iDb++){
-    assert( iDb==1 || sqlite3BtreeHoldsMutex(db->aDb[iDb].pBt) );
-  }
-#endif
-
   iDb = pOp->p1;
   assert( iDb>=0 && iDb<db->nDb );
-  assert( DbHasProperty(db, iDb, DB_SchemaLoaded) );
-  /* Used to be a conditional */ {
-    zMaster = MASTER_NAME;
+
+  /* If pOp->p2 is 0, then this opcode is being executed to read a
+  ** single row, for example the row corresponding to a new index
+  ** created by this VDBE, from the sqlite_master table. It only
+  ** does this if the corresponding in-memory schema is currently
+  ** loaded. Otherwise, the new index definition can be loaded along
+  ** with the rest of the schema when it is required.
+  **
+  ** Although the mutex on the BtShared object that corresponds to
+  ** database iDb (the database containing the sqlite_master table
+  ** read by this instruction) is currently held, it is necessary to
+  ** obtain the mutexes on all attached databases before checking if
+  ** the schema of iDb is loaded. This is because, at the start of
+  ** the sqlite3_exec() call below, SQLite will invoke 
+  ** sqlite3BtreeEnterAll(). If all mutexes are not already held, the
+  ** iDb mutex may be temporarily released to avoid deadlock. If 
+  ** this happens, then some other thread may delete the in-memory 
+  ** schema of database iDb before the SQL statement runs. The schema
+  ** will not be reloaded becuase the db->init.busy flag is set. This
+  ** can result in a "no such table: sqlite_master" or "malformed
+  ** database schema" error being returned to the user.
+  */
+  assert( sqlite3BtreeHoldsMutex(db->aDb[iDb].pBt) );
+  sqlite3BtreeEnterAll(db);
+  if( pOp->p2 || DbHasProperty(db, iDb, DB_SchemaLoaded) ){
+    zMaster = SCHEMA_TABLE(iDb);
     initData.db = db;
     initData.iDb = pOp->p1;
     initData.pzErrMsg = &p->zErrMsg;
     zSql = sqlite3MPrintf(db,
-       "SELECT name, rootpage, sql FROM '%q'.%s WHERE %s ORDER BY rowid",
-       db->aDb[iDb].zDbSName, zMaster, pOp->p4.z);
+       "SELECT name, rootpage, sql FROM '%q'.%s WHERE %s",
+       db->aDb[iDb].zName, zMaster, pOp->p4.z);
     if( zSql==0 ){
-      rc = SQLITE_NOMEM_BKPT;
+      rc = SQLITE_NOMEM;
     }else{
+      (void)sqlite3SafetyOff(db);
       assert( db->init.busy==0 );
       db->init.busy = 1;
       initData.rc = SQLITE_OK;
       assert( !db->mallocFailed );
       rc = sqlite3_exec(db, zSql, sqlite3InitCallback, &initData, 0);
       if( rc==SQLITE_OK ) rc = initData.rc;
-      sqlite3DbFreeNN(db, zSql);
+      sqlite3DbFree(db, zSql);
       db->init.busy = 0;
+      (void)sqlite3SafetyOn(db);
     }
   }
-  if( rc ){
-    sqlite3ResetAllSchemasOfConnection(db);
-    if( rc==SQLITE_NOMEM ){
-      goto no_mem;
-    }
-    goto abort_due_to_error;
+  sqlite3BtreeLeaveAll(db);
+  if( rc==SQLITE_NOMEM ){
+    goto no_mem;
   }
   break;  
 }
 
-#if !defined(SQLITE_OMIT_ANALYZE)
+#if !defined(SQLITE_OMIT_ANALYZE) && !defined(SQLITE_OMIT_PARSER)
 /* Opcode: LoadAnalysis P1 * * * *
 **
 ** Read the sqlite_stat1 table for database P1 and load the content
 ** of that table into the internal index hash table.  This will cause
 ** the analysis to be used when preparing all subsequent queries.
 */
 case OP_LoadAnalysis: {
   assert( pOp->p1>=0 && pOp->p1<db->nDb );
   rc = sqlite3AnalysisLoad(db, pOp->p1);
-  if( rc ) goto abort_due_to_error;
   break;  
 }
-#endif /* !defined(SQLITE_OMIT_ANALYZE) */
+#endif /* !defined(SQLITE_OMIT_ANALYZE) && !defined(SQLITE_OMIT_PARSER)  */
 
 /* Opcode: DropTable P1 * * P4 *
 **
 ** Remove the internal (in-memory) data structures that describe
 ** the table named P4 in database P1.  This is called after a table
-** is dropped from disk (using the Destroy opcode) in order to keep 
-** the internal representation of the
+** is dropped in order to keep the internal representation of the
 ** schema consistent with what is on disk.
 */
 case OP_DropTable: {
   sqlite3UnlinkAndDeleteTable(db, pOp->p1, pOp->p4.z);
   break;
 }
 
 /* Opcode: DropIndex P1 * * P4 *
 **
 ** Remove the internal (in-memory) data structures that describe
 ** the index named P4 in database P1.  This is called after an index
-** is dropped from disk (using the Destroy opcode)
-** in order to keep the internal representation of the
+** is dropped in order to keep the internal representation of the
 ** schema consistent with what is on disk.
 */
 case OP_DropIndex: {
   sqlite3UnlinkAndDeleteIndex(db, pOp->p1, pOp->p4.z);
   break;
 }
 
 /* Opcode: DropTrigger P1 * * P4 *
 **
 ** Remove the internal (in-memory) data structures that describe
 ** the trigger named P4 in database P1.  This is called after a trigger
-** is dropped from disk (using the Destroy opcode) in order to keep 
-** the internal representation of the
+** is dropped in order to keep the internal representation of the
 ** schema consistent with what is on disk.
 */
 case OP_DropTrigger: {
   sqlite3UnlinkAndDeleteTrigger(db, pOp->p1, pOp->p4.z);
   break;
 }
 
 
 #ifndef SQLITE_OMIT_INTEGRITY_CHECK
-/* Opcode: IntegrityCk P1 P2 P3 P4 P5
+/* Opcode: IntegrityCk P1 P2 P3 * P5
 **
 ** Do an analysis of the currently open database.  Store in
 ** register P1 the text of an error message describing any problems.
 ** If no problems are found, store a NULL in register P1.
 **
-** The register P3 contains one less than the maximum number of allowed errors.
+** The register P3 contains the maximum number of allowed errors.
 ** At most reg(P3) errors will be reported.
 ** In other words, the analysis stops as soon as reg(P1) errors are 
 ** seen.  Reg(P1) is updated with the number of errors remaining.
 **
-** The root page numbers of all tables in the database are integers
-** stored in P4_INTARRAY argument.
+** The root page numbers of all tables in the database are integer
+** stored in reg(P1), reg(P1+1), reg(P1+2), ....  There are P2 tables
+** total.
 **
 ** If P5 is not zero, the check is done on the auxiliary database
 ** file, not the main database file.
 **
 ** This opcode is used to implement the integrity_check pragma.
 */
 case OP_IntegrityCk: {
   int nRoot;      /* Number of tables to check.  (Number of root pages.) */
   int *aRoot;     /* Array of rootpage numbers for tables to be checked */
+  int j;          /* Loop counter */
   int nErr;       /* Number of errors reported */
   char *z;        /* Text of the error report */
   Mem *pnErr;     /* Register keeping track of errors remaining */
-
-  assert( p->bIsReader );
+  
   nRoot = pOp->p2;
-  aRoot = pOp->p4.ai;
   assert( nRoot>0 );
-  assert( aRoot[0]==nRoot );
-  assert( pOp->p3>0 && pOp->p3<=(p->nMem+1 - p->nCursor) );
-  pnErr = &aMem[pOp->p3];
+  aRoot = sqlite3DbMallocRaw(db, sizeof(int)*(nRoot+1) );
+  if( aRoot==0 ) goto no_mem;
+  assert( pOp->p3>0 && pOp->p3<=p->nMem );
+  pnErr = &p->aMem[pOp->p3];
   assert( (pnErr->flags & MEM_Int)!=0 );
   assert( (pnErr->flags & (MEM_Str|MEM_Blob))==0 );
-  pIn1 = &aMem[pOp->p1];
+  pIn1 = &p->aMem[pOp->p1];
+  for(j=0; j<nRoot; j++){
+    aRoot[j] = (int)sqlite3VdbeIntValue(&pIn1[j]);
+  }
+  aRoot[j] = 0;
   assert( pOp->p5<db->nDb );
-  assert( DbMaskTest(p->btreeMask, pOp->p5) );
-  z = sqlite3BtreeIntegrityCheck(db->aDb[pOp->p5].pBt, &aRoot[1], nRoot,
-                                 (int)pnErr->u.i+1, &nErr);
+  assert( (p->btreeMask & (1<<pOp->p5))!=0 );
+  z = sqlite3BtreeIntegrityCheck(db->aDb[pOp->p5].pBt, aRoot, nRoot,
+                                 (int)pnErr->u.i, &nErr);
+  sqlite3DbFree(db, aRoot);
+  pnErr->u.i -= nErr;
   sqlite3VdbeMemSetNull(pIn1);
   if( nErr==0 ){
     assert( z==0 );
   }else if( z==0 ){
     goto no_mem;
   }else{
-    pnErr->u.i -= nErr-1;
     sqlite3VdbeMemSetStr(pIn1, z, -1, SQLITE_UTF8, sqlite3_free);
   }
   UPDATE_MAX_BLOBSIZE(pIn1);
   sqlite3VdbeChangeEncoding(pIn1, encoding);
   break;
 }
 #endif /* SQLITE_OMIT_INTEGRITY_CHECK */
 
 /* Opcode: RowSetAdd P1 P2 * * *
-** Synopsis: rowset(P1)=r[P2]
 **
-** Insert the integer value held by register P2 into a RowSet object
+** Insert the integer value held by register P2 into a boolean index
 ** held in register P1.
 **
 ** An assertion fails if P2 is not an integer.
 */
-case OP_RowSetAdd: {       /* in1, in2 */
-  pIn1 = &aMem[pOp->p1];
-  pIn2 = &aMem[pOp->p2];
-  assert( (pIn2->flags & MEM_Int)!=0 );
-  if( (pIn1->flags & MEM_RowSet)==0 ){
-    sqlite3VdbeMemSetRowSet(pIn1);
-    if( (pIn1->flags & MEM_RowSet)==0 ) goto no_mem;
+case OP_RowSetAdd: {       /* in2 */
+  Mem *pIdx;
+  Mem *pVal;
+  assert( pOp->p1>0 && pOp->p1<=p->nMem );
+  pIdx = &p->aMem[pOp->p1];
+  assert( pOp->p2>0 && pOp->p2<=p->nMem );
+  pVal = &p->aMem[pOp->p2];
+  assert( (pVal->flags & MEM_Int)!=0 );
+  if( (pIdx->flags & MEM_RowSet)==0 ){
+    sqlite3VdbeMemSetRowSet(pIdx);
+    if( (pIdx->flags & MEM_RowSet)==0 ) goto no_mem;
   }
-  sqlite3RowSetInsert(pIn1->u.pRowSet, pIn2->u.i);
+  sqlite3RowSetInsert(pIdx->u.pRowSet, pVal->u.i);
   break;
 }
 
 /* Opcode: RowSetRead P1 P2 P3 * *
-** Synopsis: r[P3]=rowset(P1)
 **
-** Extract the smallest value from the RowSet object in P1
-** and put that value into register P3.
-** Or, if RowSet object P1 is initially empty, leave P3
+** Extract the smallest value from boolean index P1 and put that value into
+** register P3.  Or, if boolean index P1 is initially empty, leave P3
 ** unchanged and jump to instruction P2.
 */
-case OP_RowSetRead: {       /* jump, in1, out3 */
+case OP_RowSetRead: {       /* jump, out3 */
+  Mem *pIdx;
   i64 val;
-
-  pIn1 = &aMem[pOp->p1];
-  if( (pIn1->flags & MEM_RowSet)==0 
-   || sqlite3RowSetNext(pIn1->u.pRowSet, &val)==0
+  assert( pOp->p1>0 && pOp->p1<=p->nMem );
+  CHECK_FOR_INTERRUPT;
+  pIdx = &p->aMem[pOp->p1];
+  pOut = &p->aMem[pOp->p3];
+  if( (pIdx->flags & MEM_RowSet)==0 
+   || sqlite3RowSetNext(pIdx->u.pRowSet, &val)==0
   ){
     /* The boolean index is empty */
-    sqlite3VdbeMemSetNull(pIn1);
-    VdbeBranchTaken(1,2);
-    goto jump_to_p2_and_check_for_interrupt;
+    sqlite3VdbeMemSetNull(pIdx);
+    pc = pOp->p2 - 1;
   }else{
     /* A value was pulled from the index */
-    VdbeBranchTaken(0,2);
-    sqlite3VdbeMemSetInt64(&aMem[pOp->p3], val);
+    assert( pOp->p3>0 && pOp->p3<=p->nMem );
+    sqlite3VdbeMemSetInt64(pOut, val);
   }
-  goto check_for_interrupt;
+  break;
 }
 
 /* Opcode: RowSetTest P1 P2 P3 P4
-** Synopsis: if r[P3] in rowset(P1) goto P2
 **
 ** Register P3 is assumed to hold a 64-bit integer value. If register P1
 ** contains a RowSet object and that RowSet object contains
 ** the value held in P3, jump to register P2. Otherwise, insert the
 ** integer in P3 into the RowSet and continue on to the
 ** next opcode.
 **
-** The RowSet object is optimized for the case where sets of integers
-** are inserted in distinct phases, which each set contains no duplicates.
-** Each set is identified by a unique P4 value. The first set
-** must have P4==0, the final set must have P4==-1, and for all other sets
-** must have P4>0.
+** The RowSet object is optimized for the case where successive sets
+** of integers, where each set contains no duplicates. Each set
+** of values is identified by a unique P4 value. The first set
+** must have P4==0, the final set P4=-1.  P4 must be either -1 or
+** non-negative.  For non-negative values of P4 only the lower 4
+** bits are significant.
 **
 ** This allows optimizations: (a) when P4==0 there is no need to test
-** the RowSet object for P3, as it is guaranteed not to contain it,
+** the rowset object for P3, as it is guaranteed not to contain it,
 ** (b) when P4==-1 there is no need to insert the value, as it will
 ** never be tested for, and (c) when a value that is part of set X is
 ** inserted, there is no need to search to see if the same value was
 ** previously inserted as part of set X (only if it was previously
 ** inserted as part of some other set).
 */
 case OP_RowSetTest: {                     /* jump, in1, in3 */
   int iSet;
   int exists;
 
-  pIn1 = &aMem[pOp->p1];
-  pIn3 = &aMem[pOp->p3];
   iSet = pOp->p4.i;
   assert( pIn3->flags&MEM_Int );
 
   /* If there is anything other than a rowset object in memory cell P1,
   ** delete it now and initialize P1 with an empty rowset
   */
