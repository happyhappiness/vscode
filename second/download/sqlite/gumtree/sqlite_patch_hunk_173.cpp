   if( p->pWhere ) return 0;              /* Has no WHERE clause */
   pSrc = p->pSrc;
   assert( pSrc!=0 );
   if( pSrc->nSrc!=1 ) return 0;          /* Single term in FROM clause */
   if( pSrc->a[0].pSelect ) return 0;     /* FROM is not a subquery or view */
   pTab = pSrc->a[0].pTab;
-  if( NEVER(pTab==0) ) return 0;
+  assert( pTab!=0 );
   assert( pTab->pSelect==0 );            /* FROM clause is not a view */
   if( IsVirtual(pTab) ) return 0;        /* FROM clause not a virtual table */
   pEList = p->pEList;
-  if( pEList->nExpr!=1 ) return 0;       /* One column in the result set */
-  if( pEList->a[0].pExpr->op!=TK_COLUMN ) return 0; /* Result is a column */
-  return 1;
+  assert( pEList!=0 );
+  /* All SELECT results must be columns. */
+  for(i=0; i<pEList->nExpr; i++){
+    Expr *pRes = pEList->a[i].pExpr;
+    if( pRes->op!=TK_COLUMN ) return 0;
+    assert( pRes->iTable==pSrc->a[0].iCursor );  /* Not a correlated subquery */
+  }
+  return p;
 }
 #endif /* SQLITE_OMIT_SUBQUERY */
 
+#ifndef SQLITE_OMIT_SUBQUERY
+/*
+** Generate code that checks the left-most column of index table iCur to see if
+** it contains any NULL entries.  Cause the register at regHasNull to be set
+** to a non-NULL value if iCur contains no NULLs.  Cause register regHasNull
+** to be set to NULL if iCur contains one or more NULL values.
+*/
+static void sqlite3SetHasNullFlag(Vdbe *v, int iCur, int regHasNull){
+  int addr1;
+  sqlite3VdbeAddOp2(v, OP_Integer, 0, regHasNull);
+  addr1 = sqlite3VdbeAddOp1(v, OP_Rewind, iCur); VdbeCoverage(v);
+  sqlite3VdbeAddOp3(v, OP_Column, iCur, 0, regHasNull);
+  sqlite3VdbeChangeP5(v, OPFLAG_TYPEOFARG);
+  VdbeComment((v, "first_entry_in(%d)", iCur));
+  sqlite3VdbeJumpHere(v, addr1);
+}
+#endif
+
+
+#ifndef SQLITE_OMIT_SUBQUERY
+/*
+** The argument is an IN operator with a list (not a subquery) on the 
+** right-hand side.  Return TRUE if that list is constant.
+*/
+static int sqlite3InRhsIsConstant(Expr *pIn){
+  Expr *pLHS;
+  int res;
+  assert( !ExprHasProperty(pIn, EP_xIsSelect) );
+  pLHS = pIn->pLeft;
+  pIn->pLeft = 0;
+  res = sqlite3ExprIsConstant(pIn);
+  pIn->pLeft = pLHS;
+  return res;
+}
+#endif
+
 /*
 ** This function is used by the implementation of the IN (...) operator.
-** It's job is to find or create a b-tree structure that may be used
-** either to test for membership of the (...) set or to iterate through
-** its members, skipping duplicates.
+** The pX parameter is the expression on the RHS of the IN operator, which
+** might be either a list of expressions or a subquery.
+**
+** The job of this routine is to find or create a b-tree object that can
+** be used either to test for membership in the RHS set or to iterate through
+** all members of the RHS set, skipping duplicates.
+**
+** A cursor is opened on the b-tree object that is the RHS of the IN operator
+** and pX->iTable is set to the index of that cursor.
 **
-** The index of the cursor opened on the b-tree (database table, database index 
-** or ephermal table) is stored in pX->iTable before this function returns.
 ** The returned value of this function indicates the b-tree type, as follows:
 **
-**   IN_INDEX_ROWID - The cursor was opened on a database table.
-**   IN_INDEX_INDEX - The cursor was opened on a database index.
-**   IN_INDEX_EPH -   The cursor was opened on a specially created and
-**                    populated epheremal table.
-**
-** An existing b-tree may only be used if the SELECT is of the simple
-** form:
-**
-**     SELECT <column> FROM <table>
-**
-** If the prNotFound parameter is 0, then the b-tree will be used to iterate
-** through the set members, skipping any duplicates. In this case an
-** epheremal table must be used unless the selected <column> is guaranteed
-** to be unique - either because it is an INTEGER PRIMARY KEY or it
-** has a UNIQUE constraint or UNIQUE index.
-**
-** If the prNotFound parameter is not 0, then the b-tree will be used 
-** for fast set membership tests. In this case an epheremal table must 
-** be used unless <column> is an INTEGER PRIMARY KEY or an index can 
-** be found with <column> as its left-most column.
+**   IN_INDEX_ROWID      - The cursor was opened on a database table.
+**   IN_INDEX_INDEX_ASC  - The cursor was opened on an ascending index.
+**   IN_INDEX_INDEX_DESC - The cursor was opened on a descending index.
+**   IN_INDEX_EPH        - The cursor was opened on a specially created and
+**                         populated epheremal table.
+**   IN_INDEX_NOOP       - No cursor was allocated.  The IN operator must be
+**                         implemented as a sequence of comparisons.
+**
+** An existing b-tree might be used if the RHS expression pX is a simple
+** subquery such as:
+**
+**     SELECT <column1>, <column2>... FROM <table>
+**
+** If the RHS of the IN operator is a list or a more complex subquery, then
+** an ephemeral table might need to be generated from the RHS and then
+** pX->iTable made to point to the ephemeral table instead of an
+** existing table.
+**
+** The inFlags parameter must contain exactly one of the bits
+** IN_INDEX_MEMBERSHIP or IN_INDEX_LOOP.  If inFlags contains
+** IN_INDEX_MEMBERSHIP, then the generated table will be used for a
+** fast membership test.  When the IN_INDEX_LOOP bit is set, the
+** IN index will be used to loop over all values of the RHS of the
+** IN operator.
+**
+** When IN_INDEX_LOOP is used (and the b-tree will be used to iterate
+** through the set members) then the b-tree must not contain duplicates.
+** An epheremal table must be used unless the selected columns are guaranteed
+** to be unique - either because it is an INTEGER PRIMARY KEY or due to
+** a UNIQUE constraint or index.
+**
+** When IN_INDEX_MEMBERSHIP is used (and the b-tree will be used 
+** for fast set membership tests) then an epheremal table must 
+** be used unless <columns> is a single INTEGER PRIMARY KEY column or an 
+** index can be found with the specified <columns> as its left-most.
+**
+** If the IN_INDEX_NOOP_OK and IN_INDEX_MEMBERSHIP are both set and
+** if the RHS of the IN operator is a list (not a subquery) then this
+** routine might decide that creating an ephemeral b-tree for membership
+** testing is too expensive and return IN_INDEX_NOOP.  In that case, the
+** calling routine should implement the IN operator using a sequence
+** of Eq or Ne comparison operations.
 **
 ** When the b-tree is being used for membership tests, the calling function
-** needs to know whether or not the structure contains an SQL NULL 
-** value in order to correctly evaluate expressions like "X IN (Y, Z)".
-** If there is a chance that the b-tree might contain a NULL value at
+** might need to know whether or not the RHS side of the IN operator
+** contains a NULL.  If prRhsHasNull is not a NULL pointer and 
+** if there is any chance that the (...) might contain a NULL value at
 ** runtime, then a register is allocated and the register number written
-** to *prNotFound. If there is no chance that the b-tree contains a
-** NULL value, then *prNotFound is left unchanged.
+** to *prRhsHasNull. If there is no chance that the (...) contains a
+** NULL value, then *prRhsHasNull is left unchanged.
 **
-** If a register is allocated and its location stored in *prNotFound, then
-** its initial value is NULL. If the b-tree does not remain constant
-** for the duration of the query (i.e. the SELECT that generates the b-tree
-** is a correlated subquery) then the value of the allocated register is
-** reset to NULL each time the b-tree is repopulated. This allows the
-** caller to use vdbe code equivalent to the following:
-**
-**   if( register==NULL ){
-**     has_null = <test if data structure contains null>
-**     register = 1
-**   }
+** If a register is allocated and its location stored in *prRhsHasNull, then
+** the value in that register will be NULL if the b-tree contains one or more
+** NULL values, and it will be some non-NULL value if the b-tree contains no
+** NULL values.
+**
+** If the aiMap parameter is not NULL, it must point to an array containing
+** one element for each column returned by the SELECT statement on the RHS
+** of the IN(...) operator. The i'th entry of the array is populated with the
+** offset of the index column that matches the i'th column returned by the
+** SELECT. For example, if the expression and selected index are:
 **
-** in order to avoid running the <test if data structure contains null>
-** test more often than is necessary.
+**   (?,?,?) IN (SELECT a, b, c FROM t1)
+**   CREATE INDEX i1 ON t1(b, c, a);
+**
+** then aiMap[] is populated with {2, 0, 1}.
 */
 #ifndef SQLITE_OMIT_SUBQUERY
-int sqlite3FindInIndex(Parse *pParse, Expr *pX, int *prNotFound){
+int sqlite3FindInIndex(
+  Parse *pParse,             /* Parsing context */
+  Expr *pX,                  /* The right-hand side (RHS) of the IN operator */
+  u32 inFlags,               /* IN_INDEX_LOOP, _MEMBERSHIP, and/or _NOOP_OK */
+  int *prRhsHasNull,         /* Register holding NULL status.  See notes */
+  int *aiMap                 /* Mapping from Index fields to RHS fields */
+){
   Select *p;                            /* SELECT to the right of IN operator */
   int eType = 0;                        /* Type of RHS table. IN_INDEX_* */
   int iTab = pParse->nTab++;            /* Cursor of the RHS table */
-  int mustBeUnique = (prNotFound==0);   /* True if RHS must be unique */
+  int mustBeUnique;                     /* True if RHS must be unique */
+  Vdbe *v = sqlite3GetVdbe(pParse);     /* Virtual machine being coded */
+
+  assert( pX->op==TK_IN );
+  mustBeUnique = (inFlags & IN_INDEX_LOOP)!=0;
+
+  /* If the RHS of this IN(...) operator is a SELECT, and if it matters 
+  ** whether or not the SELECT result contains NULL values, check whether
+  ** or not NULL is actually possible (it may not be, for example, due 
+  ** to NOT NULL constraints in the schema). If no NULL values are possible,
+  ** set prRhsHasNull to 0 before continuing.  */
+  if( prRhsHasNull && (pX->flags & EP_xIsSelect) ){
+    int i;
+    ExprList *pEList = pX->x.pSelect->pEList;
+    for(i=0; i<pEList->nExpr; i++){
+      if( sqlite3ExprCanBeNull(pEList->a[i].pExpr) ) break;
+    }
+    if( i==pEList->nExpr ){
+      prRhsHasNull = 0;
+    }
+  }
 
   /* Check to see if an existing table or index can be used to
   ** satisfy the query.  This is preferable to generating a new 
-  ** ephemeral table.
-  */
-  p = (ExprHasProperty(pX, EP_xIsSelect) ? pX->x.pSelect : 0);
-  if( ALWAYS(pParse->nErr==0) && isCandidateForInOpt(p) ){
+  ** ephemeral table.  */
+  if( pParse->nErr==0 && (p = isCandidateForInOpt(pX))!=0 ){
     sqlite3 *db = pParse->db;              /* Database connection */
-    Expr *pExpr = p->pEList->a[0].pExpr;   /* Expression <column> */
-    int iCol = pExpr->iColumn;             /* Index of column <column> */
-    Vdbe *v = sqlite3GetVdbe(pParse);      /* Virtual machine being coded */
-    Table *pTab = p->pSrc->a[0].pTab;      /* Table <table>. */
-    int iDb;                               /* Database idx for pTab */
-   
-    /* Code an OP_VerifyCookie and OP_TableLock for <table>. */
+    Table *pTab;                           /* Table <table>. */
+    i16 iDb;                               /* Database idx for pTab */
+    ExprList *pEList = p->pEList;
+    int nExpr = pEList->nExpr;
+
+    assert( p->pEList!=0 );             /* Because of isCandidateForInOpt(p) */
+    assert( p->pEList->a[0].pExpr!=0 ); /* Because of isCandidateForInOpt(p) */
+    assert( p->pSrc!=0 );               /* Because of isCandidateForInOpt(p) */
+    pTab = p->pSrc->a[0].pTab;
+
+    /* Code an OP_Transaction and OP_TableLock for <table>. */
     iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
     sqlite3CodeVerifySchema(pParse, iDb);
     sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);
 
-    /* This function is only called from two places. In both cases the vdbe
-    ** has already been allocated. So assume sqlite3GetVdbe() is always
-    ** successful here.
-    */
-    assert(v);
-    if( iCol<0 ){
-      int iMem = ++pParse->nMem;
-      int iAddr;
-      sqlite3VdbeUsesBtree(v, iDb);
-
-      iAddr = sqlite3VdbeAddOp1(v, OP_If, iMem);
-      sqlite3VdbeAddOp2(v, OP_Integer, 1, iMem);
+    assert(v);  /* sqlite3GetVdbe() has always been previously called */
+    if( nExpr==1 && pEList->a[0].pExpr->iColumn<0 ){
+      /* The "x IN (SELECT rowid FROM table)" case */
+      int iAddr = sqlite3VdbeAddOp0(v, OP_Once);
+      VdbeCoverage(v);
 
       sqlite3OpenTable(pParse, iTab, iDb, pTab, OP_OpenRead);
       eType = IN_INDEX_ROWID;
 
       sqlite3VdbeJumpHere(v, iAddr);
     }else{
       Index *pIdx;                         /* Iterator variable */
+      int affinity_ok = 1;
+      int i;
 
-      /* The collation sequence used by the comparison. If an index is to
-      ** be used in place of a temp-table, it must be ordered according
-      ** to this collation sequence.  */
-      CollSeq *pReq = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pExpr);
-
-      /* Check that the affinity that will be used to perform the 
-      ** comparison is the same as the affinity of the column. If
-      ** it is not, it is not possible to use any index.
-      */
-      char aff = comparisonAffinity(pX);
-      int affinity_ok = (pTab->aCol[iCol].affinity==aff||aff==SQLITE_AFF_NONE);
+      /* Check that the affinity that will be used to perform each 
+      ** comparison is the same as the affinity of each column in table
+      ** on the RHS of the IN operator.  If it not, it is not possible to
+      ** use any index of the RHS table.  */
+      for(i=0; i<nExpr && affinity_ok; i++){
+        Expr *pLhs = sqlite3VectorFieldSubexpr(pX->pLeft, i);
+        int iCol = pEList->a[i].pExpr->iColumn;
+        char idxaff = sqlite3TableColumnAffinity(pTab,iCol); /* RHS table */
+        char cmpaff = sqlite3CompareAffinity(pLhs, idxaff);
+        testcase( cmpaff==SQLITE_AFF_BLOB );
+        testcase( cmpaff==SQLITE_AFF_TEXT );
+        switch( cmpaff ){
+          case SQLITE_AFF_BLOB:
+            break;
+          case SQLITE_AFF_TEXT:
+            /* sqlite3CompareAffinity() only returns TEXT if one side or the
+            ** other has no affinity and the other side is TEXT.  Hence,
+            ** the only way for cmpaff to be TEXT is for idxaff to be TEXT
+            ** and for the term on the LHS of the IN to have no affinity. */
+            assert( idxaff==SQLITE_AFF_TEXT );
+            break;
+          default:
+            affinity_ok = sqlite3IsNumericAffinity(idxaff);
+        }
+      }
 
-      for(pIdx=pTab->pIndex; pIdx && eType==0 && affinity_ok; pIdx=pIdx->pNext){
-        if( (pIdx->aiColumn[0]==iCol)
-         && sqlite3FindCollSeq(db, ENC(db), pIdx->azColl[0], 0)==pReq
-         && (!mustBeUnique || (pIdx->nColumn==1 && pIdx->onError!=OE_None))
-        ){
-          int iMem = ++pParse->nMem;
-          int iAddr;
-          char *pKey;
+      if( affinity_ok ){
+        /* Search for an existing index that will work for this IN operator */
+        for(pIdx=pTab->pIndex; pIdx && eType==0; pIdx=pIdx->pNext){
+          Bitmask colUsed;      /* Columns of the index used */
+          Bitmask mCol;         /* Mask for the current column */
+          if( pIdx->nColumn<nExpr ) continue;
+          /* Maximum nColumn is BMS-2, not BMS-1, so that we can compute
+          ** BITMASK(nExpr) without overflowing */
+          testcase( pIdx->nColumn==BMS-2 );
+          testcase( pIdx->nColumn==BMS-1 );
+          if( pIdx->nColumn>=BMS-1 ) continue;
+          if( mustBeUnique ){
+            if( pIdx->nKeyCol>nExpr
+             ||(pIdx->nColumn>nExpr && !IsUniqueIndex(pIdx))
+            ){
+              continue;  /* This index is not unique over the IN RHS columns */
+            }
+          }
   
-          pKey = (char *)sqlite3IndexKeyinfo(pParse, pIdx);
-          iDb = sqlite3SchemaToIndex(db, pIdx->pSchema);
-          sqlite3VdbeUsesBtree(v, iDb);
-
-          iAddr = sqlite3VdbeAddOp1(v, OP_If, iMem);
-          sqlite3VdbeAddOp2(v, OP_Integer, 1, iMem);
+          colUsed = 0;   /* Columns of index used so far */
+          for(i=0; i<nExpr; i++){
+            Expr *pLhs = sqlite3VectorFieldSubexpr(pX->pLeft, i);
+            Expr *pRhs = pEList->a[i].pExpr;
+            CollSeq *pReq = sqlite3BinaryCompareCollSeq(pParse, pLhs, pRhs);
+            int j;
   
-          sqlite3VdbeAddOp4(v, OP_OpenRead, iTab, pIdx->tnum, iDb,
-                               pKey,P4_KEYINFO_HANDOFF);
-          VdbeComment((v, "%s", pIdx->zName));
-          eType = IN_INDEX_INDEX;
-
-          sqlite3VdbeJumpHere(v, iAddr);
-          if( prNotFound && !pTab->aCol[iCol].notNull ){
-            *prNotFound = ++pParse->nMem;
+            assert( pReq!=0 || pRhs->iColumn==XN_ROWID || pParse->nErr );
+            for(j=0; j<nExpr; j++){
+              if( pIdx->aiColumn[j]!=pRhs->iColumn ) continue;
+              assert( pIdx->azColl[j] );
+              if( pReq!=0 && sqlite3StrICmp(pReq->zName, pIdx->azColl[j])!=0 ){
+                continue;
+              }
+              break;
+            }
+            if( j==nExpr ) break;
+            mCol = MASKBIT(j);
+            if( mCol & colUsed ) break; /* Each column used only once */
+            colUsed |= mCol;
+            if( aiMap ) aiMap[i] = j;
           }
-        }
-      }
-    }
+  
+          assert( i==nExpr || colUsed!=(MASKBIT(nExpr)-1) );
+          if( colUsed==(MASKBIT(nExpr)-1) ){
+            /* If we reach this point, that means the index pIdx is usable */
+            int iAddr = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);
+#ifndef SQLITE_OMIT_EXPLAIN
+            sqlite3VdbeAddOp4(v, OP_Explain, 0, 0, 0,
+              sqlite3MPrintf(db, "USING INDEX %s FOR IN-OPERATOR",pIdx->zName),
+              P4_DYNAMIC);
+#endif
+            sqlite3VdbeAddOp3(v, OP_OpenRead, iTab, pIdx->tnum, iDb);
+            sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
+            VdbeComment((v, "%s", pIdx->zName));
+            assert( IN_INDEX_INDEX_DESC == IN_INDEX_INDEX_ASC+1 );
+            eType = IN_INDEX_INDEX_ASC + pIdx->aSortOrder[0];
+  
+            if( prRhsHasNull ){
+#ifdef SQLITE_ENABLE_COLUMN_USED_MASK
+              i64 mask = (1<<nExpr)-1;
+              sqlite3VdbeAddOp4Dup8(v, OP_ColumnsUsed, 
+                  iTab, 0, 0, (u8*)&mask, P4_INT64);
+#endif
+              *prRhsHasNull = ++pParse->nMem;
+              if( nExpr==1 ){
+                sqlite3SetHasNullFlag(v, iTab, *prRhsHasNull);
+              }
+            }
+            sqlite3VdbeJumpHere(v, iAddr);
+          }
+        } /* End loop over indexes */
+      } /* End if( affinity_ok ) */
+    } /* End if not an rowid index */
+  } /* End attempt to optimize using an index */
+
+  /* If no preexisting index is available for the IN clause
+  ** and IN_INDEX_NOOP is an allowed reply
+  ** and the RHS of the IN operator is a list, not a subquery
+  ** and the RHS is not constant or has two or fewer terms,
+  ** then it is not worth creating an ephemeral table to evaluate
+  ** the IN operator so return IN_INDEX_NOOP.
+  */
+  if( eType==0
+   && (inFlags & IN_INDEX_NOOP_OK)
+   && !ExprHasProperty(pX, EP_xIsSelect)
+   && (!sqlite3InRhsIsConstant(pX) || pX->x.pList->nExpr<=2)
+  ){
+    eType = IN_INDEX_NOOP;
   }
 
   if( eType==0 ){
-    /* Could not found an existing able or index to use as the RHS b-tree.
+    /* Could not find an existing table or index to use as the RHS b-tree.
     ** We will have to generate an ephemeral table to do the job.
     */
+    u32 savedNQueryLoop = pParse->nQueryLoop;
     int rMayHaveNull = 0;
     eType = IN_INDEX_EPH;
-    if( prNotFound ){
-      *prNotFound = rMayHaveNull = ++pParse->nMem;
-    }else if( pX->pLeft->iColumn<0 && !ExprHasAnyProperty(pX, EP_xIsSelect) ){
-      eType = IN_INDEX_ROWID;
+    if( inFlags & IN_INDEX_LOOP ){
+      pParse->nQueryLoop = 0;
+      if( pX->pLeft->iColumn<0 && !ExprHasProperty(pX, EP_xIsSelect) ){
+        eType = IN_INDEX_ROWID;
+      }
+    }else if( prRhsHasNull ){
+      *prRhsHasNull = rMayHaveNull = ++pParse->nMem;
     }
     sqlite3CodeSubselect(pParse, pX, rMayHaveNull, eType==IN_INDEX_ROWID);
+    pParse->nQueryLoop = savedNQueryLoop;
   }else{
     pX->iTable = iTab;
   }
+
+  if( aiMap && eType!=IN_INDEX_INDEX_ASC && eType!=IN_INDEX_INDEX_DESC ){
+    int i, n;
+    n = sqlite3ExprVectorSize(pX->pLeft);
+    for(i=0; i<n; i++) aiMap[i] = i;
+  }
   return eType;
 }
 #endif
 
+#ifndef SQLITE_OMIT_SUBQUERY
+/*
+** Argument pExpr is an (?, ?...) IN(...) expression. This 
+** function allocates and returns a nul-terminated string containing 
+** the affinities to be used for each column of the comparison.
+**
+** It is the responsibility of the caller to ensure that the returned
+** string is eventually freed using sqlite3DbFree().
+*/
+static char *exprINAffinity(Parse *pParse, Expr *pExpr){
+  Expr *pLeft = pExpr->pLeft;
+  int nVal = sqlite3ExprVectorSize(pLeft);
+  Select *pSelect = (pExpr->flags & EP_xIsSelect) ? pExpr->x.pSelect : 0;
+  char *zRet;
+
+  assert( pExpr->op==TK_IN );
+  zRet = sqlite3DbMallocRaw(pParse->db, nVal+1);
+  if( zRet ){
+    int i;
+    for(i=0; i<nVal; i++){
+      Expr *pA = sqlite3VectorFieldSubexpr(pLeft, i);
+      char a = sqlite3ExprAffinity(pA);
+      if( pSelect ){
+        zRet[i] = sqlite3CompareAffinity(pSelect->pEList->a[i].pExpr, a);
+      }else{
+        zRet[i] = a;
+      }
+    }
+    zRet[nVal] = '\0';
+  }
+  return zRet;
+}
+#endif
+
+#ifndef SQLITE_OMIT_SUBQUERY
+/*
+** Load the Parse object passed as the first argument with an error 
+** message of the form:
+**
+**   "sub-select returns N columns - expected M"
+*/   
+void sqlite3SubselectError(Parse *pParse, int nActual, int nExpect){
+  const char *zFmt = "sub-select returns %d columns - expected %d";
+  sqlite3ErrorMsg(pParse, zFmt, nActual, nExpect);
+}
+#endif
+
+/*
+** Expression pExpr is a vector that has been used in a context where
+** it is not permitted. If pExpr is a sub-select vector, this routine 
+** loads the Parse object with a message of the form:
+**
+**   "sub-select returns N columns - expected 1"
+**
+** Or, if it is a regular scalar vector:
+**
+**   "row value misused"
+*/   
+void sqlite3VectorErrorMsg(Parse *pParse, Expr *pExpr){
+#ifndef SQLITE_OMIT_SUBQUERY
+  if( pExpr->flags & EP_xIsSelect ){
+    sqlite3SubselectError(pParse, pExpr->x.pSelect->pEList->nExpr, 1);
+  }else
+#endif
+  {
+    sqlite3ErrorMsg(pParse, "row value misused");
+  }
+}
+
 /*
-** Generate code for scalar subqueries used as an expression
-** and IN operators.  Examples:
+** Generate code for scalar subqueries used as a subquery expression, EXISTS,
+** or IN operators.  Examples:
 **
 **     (SELECT a FROM b)          -- subquery
 **     EXISTS (SELECT a FROM b)   -- EXISTS subquery
 **     x IN (4,5,11)              -- IN operator with list on right-hand side
 **     x IN (SELECT a FROM b)     -- IN operator with subquery on the right
 **
