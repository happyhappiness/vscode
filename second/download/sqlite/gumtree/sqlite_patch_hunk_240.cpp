 **    May you do good and not evil.
 **    May you find forgiveness for yourself and forgive others.
 **    May you share freely, never taking more than you give.
 **
 *************************************************************************
 ** This file contains code used for creating, destroying, and populating
-** a VDBE (or an "sqlite3_stmt" as it is known to the outside world.)  Prior
-** to version 2.8.7, all this code was combined into the vdbe.c source file.
-** But that file was getting too big so this subroutines were split out.
-**
-** $Id: vdbeaux.c,v 1.460 2009/06/09 18:58:53 shane Exp $
+** a VDBE (or an "sqlite3_stmt" as it is known to the outside world.) 
 */
 #include "sqliteInt.h"
 #include "vdbeInt.h"
 
-
-
-/*
-** When debugging the code generator in a symbolic debugger, one can
-** set the sqlite3VdbeAddopTrace to 1 and all opcodes will be printed
-** as they are added to the instruction stream.
-*/
-#ifdef SQLITE_DEBUG
-int sqlite3VdbeAddopTrace = 0;
-#endif
-
-
 /*
 ** Create a new virtual database engine.
 */
-Vdbe *sqlite3VdbeCreate(sqlite3 *db){
+Vdbe *sqlite3VdbeCreate(Parse *pParse){
+  sqlite3 *db = pParse->db;
   Vdbe *p;
-  p = sqlite3DbMallocZero(db, sizeof(Vdbe) );
+  p = sqlite3DbMallocRawNN(db, sizeof(Vdbe) );
   if( p==0 ) return 0;
+  memset(&p->aOp, 0, sizeof(Vdbe)-offsetof(Vdbe,aOp));
   p->db = db;
   if( db->pVdbe ){
     db->pVdbe->pPrev = p;
   }
   p->pNext = db->pVdbe;
   p->pPrev = 0;
   db->pVdbe = p;
   p->magic = VDBE_MAGIC_INIT;
+  p->pParse = pParse;
+  pParse->pVdbe = p;
+  assert( pParse->aLabel==0 );
+  assert( pParse->nLabel==0 );
+  assert( pParse->nOpAlloc==0 );
+  assert( pParse->szOpAlloc==0 );
+  sqlite3VdbeAddOp2(p, OP_Init, 0, 1);
   return p;
 }
 
 /*
-** Remember the SQL string for a prepared statement.
+** Change the error string stored in Vdbe.zErrMsg
 */
-void sqlite3VdbeSetSql(Vdbe *p, const char *z, int n, int isPrepareV2){
-  if( p==0 ) return;
-#ifdef SQLITE_OMIT_TRACE
-  if( !isPrepareV2 ) return;
-#endif
-  assert( p->zSql==0 );
-  p->zSql = sqlite3DbStrNDup(p->db, z, n);
-  p->isPrepareV2 = isPrepareV2 ? 1 : 0;
+void sqlite3VdbeError(Vdbe *p, const char *zFormat, ...){
+  va_list ap;
+  sqlite3DbFree(p->db, p->zErrMsg);
+  va_start(ap, zFormat);
+  p->zErrMsg = sqlite3VMPrintf(p->db, zFormat, ap);
+  va_end(ap);
 }
 
 /*
-** Return the SQL associated with a prepared statement
+** Remember the SQL string for a prepared statement.
 */
-const char *sqlite3_sql(sqlite3_stmt *pStmt){
-  Vdbe *p = (Vdbe *)pStmt;
-  return (p->isPrepareV2 ? p->zSql : 0);
+void sqlite3VdbeSetSql(Vdbe *p, const char *z, int n, u8 prepFlags){
+  if( p==0 ) return;
+  p->prepFlags = prepFlags;
+  if( (prepFlags & SQLITE_PREPARE_SAVESQL)==0 ){
+    p->expmask = 0;
+  }
+  assert( p->zSql==0 );
+  p->zSql = sqlite3DbStrNDup(p->db, z, n);
 }
 
 /*
 ** Swap all content between two VDBE structures.
 */
 void sqlite3VdbeSwap(Vdbe *pA, Vdbe *pB){
   Vdbe tmp, *pTmp;
   char *zTmp;
+  assert( pA->db==pB->db );
   tmp = *pA;
   *pA = *pB;
   *pB = tmp;
   pTmp = pA->pNext;
   pA->pNext = pB->pNext;
   pB->pNext = pTmp;
   pTmp = pA->pPrev;
   pA->pPrev = pB->pPrev;
   pB->pPrev = pTmp;
   zTmp = pA->zSql;
   pA->zSql = pB->zSql;
   pB->zSql = zTmp;
-  pB->isPrepareV2 = pA->isPrepareV2;
-}
-
-#ifdef SQLITE_DEBUG
-/*
-** Turn tracing on or off
-*/
-void sqlite3VdbeTrace(Vdbe *p, FILE *trace){
-  p->trace = trace;
+  pB->expmask = pA->expmask;
+  pB->prepFlags = pA->prepFlags;
+  memcpy(pB->aCounter, pA->aCounter, sizeof(pB->aCounter));
+  pB->aCounter[SQLITE_STMTSTATUS_REPREPARE]++;
 }
-#endif
 
 /*
-** Resize the Vdbe.aOp array so that it is at least one op larger than 
-** it was.
+** Resize the Vdbe.aOp array so that it is at least nOp elements larger 
+** than its current size. nOp is guaranteed to be less than or equal
+** to 1024/sizeof(Op).
 **
 ** If an out-of-memory error occurs while resizing the array, return
-** SQLITE_NOMEM. In this case Vdbe.aOp and Vdbe.nOpAlloc remain 
+** SQLITE_NOMEM. In this case Vdbe.aOp and Parse.nOpAlloc remain 
 ** unchanged (this is so that any opcodes already allocated can be 
 ** correctly deallocated along with the rest of the Vdbe).
 */
-static int growOpArray(Vdbe *p){
+static int growOpArray(Vdbe *v, int nOp){
   VdbeOp *pNew;
+  Parse *p = v->pParse;
+
+  /* The SQLITE_TEST_REALLOC_STRESS compile-time option is designed to force
+  ** more frequent reallocs and hence provide more opportunities for 
+  ** simulated OOM faults.  SQLITE_TEST_REALLOC_STRESS is generally used
+  ** during testing only.  With SQLITE_TEST_REALLOC_STRESS grow the op array
+  ** by the minimum* amount required until the size reaches 512.  Normal
+  ** operation (without SQLITE_TEST_REALLOC_STRESS) is to double the current
+  ** size of the op array or add 1KB of space, whichever is smaller. */
+#ifdef SQLITE_TEST_REALLOC_STRESS
+  int nNew = (p->nOpAlloc>=512 ? p->nOpAlloc*2 : p->nOpAlloc+nOp);
+#else
   int nNew = (p->nOpAlloc ? p->nOpAlloc*2 : (int)(1024/sizeof(Op)));
-  pNew = sqlite3DbRealloc(p->db, p->aOp, nNew*sizeof(Op));
+  UNUSED_PARAMETER(nOp);
+#endif
+
+  /* Ensure that the size of a VDBE does not grow too large */
+  if( nNew > p->db->aLimit[SQLITE_LIMIT_VDBE_OP] ){
+    sqlite3OomFault(p->db);
+    return SQLITE_NOMEM;
+  }
+
+  assert( nOp<=(1024/sizeof(Op)) );
+  assert( nNew>=(p->nOpAlloc+nOp) );
+  pNew = sqlite3DbRealloc(p->db, v->aOp, nNew*sizeof(Op));
   if( pNew ){
-    p->nOpAlloc = sqlite3DbMallocSize(p->db, pNew)/sizeof(Op);
-    p->aOp = pNew;
+    p->szOpAlloc = sqlite3DbMallocSize(p->db, pNew);
+    p->nOpAlloc = p->szOpAlloc/sizeof(Op);
+    v->aOp = pNew;
   }
-  return (pNew ? SQLITE_OK : SQLITE_NOMEM);
+  return (pNew ? SQLITE_OK : SQLITE_NOMEM_BKPT);
+}
+
+#ifdef SQLITE_DEBUG
+/* This routine is just a convenient place to set a breakpoint that will
+** fire after each opcode is inserted and displayed using
+** "PRAGMA vdbe_addoptrace=on".
+*/
+static void test_addop_breakpoint(void){
+  static int n = 0;
+  n++;
 }
+#endif
 
 /*
 ** Add a new instruction to the list of instructions current in the
 ** VDBE.  Return the address of the new instruction.
 **
 ** Parameters:
