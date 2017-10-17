   sqlite3_step(pRtree->pWriteRowid);
   rc = sqlite3_reset(pRtree->pWriteRowid);
   *piRowid = sqlite3_last_insert_rowid(pRtree->db);
   return rc;
 }
 
-#ifndef NDEBUG
-static int hashIsEmpty(Rtree *pRtree){
-  int ii;
-  for(ii=0; ii<HASHSIZE; ii++){
-    assert( !pRtree->aHash[ii] );
-  }
-  return 1;
-}
-#endif
-
 /*
-** The xUpdate method for rtree module virtual tables.
+** Remove the entry with rowid=iDelete from the r-tree structure.
 */
-int rtreeUpdate(
-  sqlite3_vtab *pVtab, 
-  int nData, 
-  sqlite3_value **azData, 
-  sqlite_int64 *pRowid
-){
-  Rtree *pRtree = (Rtree *)pVtab;
-  int rc = SQLITE_OK;
+static int rtreeDeleteRowid(Rtree *pRtree, sqlite3_int64 iDelete){
+  int rc;                         /* Return code */
+  RtreeNode *pLeaf = 0;           /* Leaf node containing record iDelete */
+  int iCell;                      /* Index of iDelete cell in pLeaf */
+  RtreeNode *pRoot = 0;           /* Root node of rtree structure */
 
-  rtreeReference(pRtree);
 
-  assert(nData>=1);
-  assert(hashIsEmpty(pRtree));
+  /* Obtain a reference to the root node to initialize Rtree.iDepth */
+  rc = nodeAcquire(pRtree, 1, 0, &pRoot);
 
-  /* If azData[0] is not an SQL NULL value, it is the rowid of a
-  ** record to delete from the r-tree table. The following block does
-  ** just that.
+  /* Obtain a reference to the leaf node that contains the entry 
+  ** about to be deleted. 
   */
-  if( sqlite3_value_type(azData[0])!=SQLITE_NULL ){
-    i64 iDelete;                /* The rowid to delete */
-    RtreeNode *pLeaf;           /* Leaf node containing record iDelete */
-    int iCell;                  /* Index of iDelete cell in pLeaf */
-    RtreeNode *pRoot;
-
-    /* Obtain a reference to the root node to initialise Rtree.iDepth */
-    rc = nodeAcquire(pRtree, 1, 0, &pRoot);
+  if( rc==SQLITE_OK ){
+    rc = findLeafNode(pRtree, iDelete, &pLeaf, 0);
+  }
 
-    /* Obtain a reference to the leaf node that contains the entry 
-    ** about to be deleted. 
-    */
+  /* Delete the cell in question from the leaf node. */
+  if( rc==SQLITE_OK ){
+    int rc2;
+    rc = nodeRowidIndex(pRtree, pLeaf, iDelete, &iCell);
     if( rc==SQLITE_OK ){
-      iDelete = sqlite3_value_int64(azData[0]);
-      rc = findLeafNode(pRtree, iDelete, &pLeaf);
+      rc = deleteCell(pRtree, pLeaf, iCell, 0);
     }
-
-    /* Delete the cell in question from the leaf node. */
+    rc2 = nodeRelease(pRtree, pLeaf);
     if( rc==SQLITE_OK ){
-      int rc2;
-      iCell = nodeRowidIndex(pRtree, pLeaf, iDelete);
-      rc = deleteCell(pRtree, pLeaf, iCell, 0);
-      rc2 = nodeRelease(pRtree, pLeaf);
-      if( rc==SQLITE_OK ){
-        rc = rc2;
-      }
+      rc = rc2;
     }
+  }
 
-    /* Delete the corresponding entry in the <rtree>_rowid table. */
+  /* Delete the corresponding entry in the <rtree>_rowid table. */
+  if( rc==SQLITE_OK ){
+    sqlite3_bind_int64(pRtree->pDeleteRowid, 1, iDelete);
+    sqlite3_step(pRtree->pDeleteRowid);
+    rc = sqlite3_reset(pRtree->pDeleteRowid);
+  }
+
+  /* Check if the root node now has exactly one child. If so, remove
+  ** it, schedule the contents of the child for reinsertion and 
+  ** reduce the tree height by one.
+  **
+  ** This is equivalent to copying the contents of the child into
+  ** the root node (the operation that Gutman's paper says to perform 
+  ** in this scenario).
+  */
+  if( rc==SQLITE_OK && pRtree->iDepth>0 && NCELL(pRoot)==1 ){
+    int rc2;
+    RtreeNode *pChild;
+    i64 iChild = nodeGetRowid(pRtree, pRoot, 0);
+    rc = nodeAcquire(pRtree, iChild, pRoot, &pChild);
     if( rc==SQLITE_OK ){
-      sqlite3_bind_int64(pRtree->pDeleteRowid, 1, iDelete);
-      sqlite3_step(pRtree->pDeleteRowid);
-      rc = sqlite3_reset(pRtree->pDeleteRowid);
+      rc = removeNode(pRtree, pChild, pRtree->iDepth-1);
     }
-
-    /* Check if the root node now has exactly one child. If so, remove
-    ** it, schedule the contents of the child for reinsertion and 
-    ** reduce the tree height by one.
-    **
-    ** This is equivalent to copying the contents of the child into
-    ** the root node (the operation that Gutman's paper says to perform 
-    ** in this scenario).
-    */
-    if( rc==SQLITE_OK && pRtree->iDepth>0 ){
-      if( rc==SQLITE_OK && NCELL(pRoot)==1 ){
-        RtreeNode *pChild;
-        i64 iChild = nodeGetRowid(pRtree, pRoot, 0);
-        rc = nodeAcquire(pRtree, iChild, pRoot, &pChild);
-        if( rc==SQLITE_OK ){
-          rc = removeNode(pRtree, pChild, pRtree->iDepth-1);
-        }
-        if( rc==SQLITE_OK ){
-          pRtree->iDepth--;
-          writeInt16(pRoot->zData, pRtree->iDepth);
-          pRoot->isDirty = 1;
-        }
-      }
+    rc2 = nodeRelease(pRtree, pChild);
+    if( rc==SQLITE_OK ) rc = rc2;
+    if( rc==SQLITE_OK ){
+      pRtree->iDepth--;
+      writeInt16(pRoot->zData, pRtree->iDepth);
+      pRoot->isDirty = 1;
     }
+  }
 
-    /* Re-insert the contents of any underfull nodes removed from the tree. */
-    for(pLeaf=pRtree->pDeleted; pLeaf; pLeaf=pRtree->pDeleted){
-      if( rc==SQLITE_OK ){
-        rc = reinsertNodeContent(pRtree, pLeaf);
-      }
-      pRtree->pDeleted = pLeaf->pNext;
-      sqlite3_free(pLeaf);
+  /* Re-insert the contents of any underfull nodes removed from the tree. */
+  for(pLeaf=pRtree->pDeleted; pLeaf; pLeaf=pRtree->pDeleted){
+    if( rc==SQLITE_OK ){
+      rc = reinsertNodeContent(pRtree, pLeaf);
     }
+    pRtree->pDeleted = pLeaf->pNext;
+    sqlite3_free(pLeaf);
+  }
 
-    /* Release the reference to the root node. */
-    if( rc==SQLITE_OK ){
-      rc = nodeRelease(pRtree, pRoot);
+  /* Release the reference to the root node. */
+  if( rc==SQLITE_OK ){
+    rc = nodeRelease(pRtree, pRoot);
+  }else{
+    nodeRelease(pRtree, pRoot);
+  }
+
+  return rc;
+}
+
+/*
+** Rounding constants for float->double conversion.
+*/
+#define RNDTOWARDS  (1.0 - 1.0/8388608.0)  /* Round towards zero */
+#define RNDAWAY     (1.0 + 1.0/8388608.0)  /* Round away from zero */
+
+#if !defined(SQLITE_RTREE_INT_ONLY)
+/*
+** Convert an sqlite3_value into an RtreeValue (presumably a float)
+** while taking care to round toward negative or positive, respectively.
+*/
+static RtreeValue rtreeValueDown(sqlite3_value *v){
+  double d = sqlite3_value_double(v);
+  float f = (float)d;
+  if( f>d ){
+    f = (float)(d*(d<0 ? RNDAWAY : RNDTOWARDS));
+  }
+  return f;
+}
+static RtreeValue rtreeValueUp(sqlite3_value *v){
+  double d = sqlite3_value_double(v);
+  float f = (float)d;
+  if( f<d ){
+    f = (float)(d*(d<0 ? RNDTOWARDS : RNDAWAY));
+  }
+  return f;
+}
+#endif /* !defined(SQLITE_RTREE_INT_ONLY) */
+
+/*
+** A constraint has failed while inserting a row into an rtree table. 
+** Assuming no OOM error occurs, this function sets the error message 
+** (at pRtree->base.zErrMsg) to an appropriate value and returns
+** SQLITE_CONSTRAINT.
+**
+** Parameter iCol is the index of the leftmost column involved in the
+** constraint failure. If it is 0, then the constraint that failed is
+** the unique constraint on the id column. Otherwise, it is the rtree
+** (c1<=c2) constraint on columns iCol and iCol+1 that has failed.
+**
+** If an OOM occurs, SQLITE_NOMEM is returned instead of SQLITE_CONSTRAINT.
+*/
+static int rtreeConstraintError(Rtree *pRtree, int iCol){
+  sqlite3_stmt *pStmt = 0;
+  char *zSql; 
+  int rc;
+
+  assert( iCol==0 || iCol%2 );
+  zSql = sqlite3_mprintf("SELECT * FROM %Q.%Q", pRtree->zDb, pRtree->zName);
+  if( zSql ){
+    rc = sqlite3_prepare_v2(pRtree->db, zSql, -1, &pStmt, 0);
+  }else{
+    rc = SQLITE_NOMEM;
+  }
+  sqlite3_free(zSql);
+
+  if( rc==SQLITE_OK ){
+    if( iCol==0 ){
+      const char *zCol = sqlite3_column_name(pStmt, 0);
+      pRtree->base.zErrMsg = sqlite3_mprintf(
+          "UNIQUE constraint failed: %s.%s", pRtree->zName, zCol
+      );
     }else{
-      nodeRelease(pRtree, pRoot);
+      const char *zCol1 = sqlite3_column_name(pStmt, iCol);
+      const char *zCol2 = sqlite3_column_name(pStmt, iCol+1);
+      pRtree->base.zErrMsg = sqlite3_mprintf(
+          "rtree constraint failed: %s.(%s<=%s)", pRtree->zName, zCol1, zCol2
+      );
     }
   }
 
-  /* If the azData[] array contains more than one element, elements
-  ** (azData[2]..azData[argc-1]) contain a new record to insert into
-  ** the r-tree structure.
+  sqlite3_finalize(pStmt);
+  return (rc==SQLITE_OK ? SQLITE_CONSTRAINT : rc);
+}
+
+
+
+/*
+** The xUpdate method for rtree module virtual tables.
+*/
+static int rtreeUpdate(
+  sqlite3_vtab *pVtab, 
+  int nData, 
+  sqlite3_value **azData, 
+  sqlite_int64 *pRowid
+){
+  Rtree *pRtree = (Rtree *)pVtab;
+  int rc = SQLITE_OK;
+  RtreeCell cell;                 /* New cell to insert if nData>1 */
+  int bHaveRowid = 0;             /* Set to 1 after new rowid is determined */
+
+  rtreeReference(pRtree);
+  assert(nData>=1);
+
+  cell.iRowid = 0;  /* Used only to suppress a compiler warning */
+
+  /* Constraint handling. A write operation on an r-tree table may return
+  ** SQLITE_CONSTRAINT for two reasons:
+  **
+  **   1. A duplicate rowid value, or
+  **   2. The supplied data violates the "x2>=x1" constraint.
+  **
+  ** In the first case, if the conflict-handling mode is REPLACE, then
+  ** the conflicting row can be removed before proceeding. In the second
+  ** case, SQLITE_CONSTRAINT must be returned regardless of the
+  ** conflict-handling mode specified by the user.
   */
-  if( rc==SQLITE_OK && nData>1 ){
-    /* Insert a new record into the r-tree */
-    RtreeCell cell;
+  if( nData>1 ){
     int ii;
-    RtreeNode *pLeaf;
 
-    /* Populate the cell.aCoord[] array. The first coordinate is azData[3]. */
-    assert( nData==(pRtree->nDim*2 + 3) );
+    /* Populate the cell.aCoord[] array. The first coordinate is azData[3].
+    **
+    ** NB: nData can only be less than nDim*2+3 if the rtree is mis-declared
+    ** with "column" that are interpreted as table constraints.
+    ** Example:  CREATE VIRTUAL TABLE bad USING rtree(x,y,CHECK(y>5));
+    ** This problem was discovered after years of use, so we silently ignore
+    ** these kinds of misdeclared tables to avoid breaking any legacy.
+    */
+    assert( nData<=(pRtree->nDim2 + 3) );
+
+#ifndef SQLITE_RTREE_INT_ONLY
     if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
-      for(ii=0; ii<(pRtree->nDim*2); ii+=2){
-        cell.aCoord[ii].f = (float)sqlite3_value_double(azData[ii+3]);
-        cell.aCoord[ii+1].f = (float)sqlite3_value_double(azData[ii+4]);
+      for(ii=0; ii<nData-4; ii+=2){
+        cell.aCoord[ii].f = rtreeValueDown(azData[ii+3]);
+        cell.aCoord[ii+1].f = rtreeValueUp(azData[ii+4]);
         if( cell.aCoord[ii].f>cell.aCoord[ii+1].f ){
-          rc = SQLITE_CONSTRAINT;
+          rc = rtreeConstraintError(pRtree, ii+1);
           goto constraint;
         }
       }
-    }else{
-      for(ii=0; ii<(pRtree->nDim*2); ii+=2){
+    }else
+#endif
+    {
+      for(ii=0; ii<nData-4; ii+=2){
         cell.aCoord[ii].i = sqlite3_value_int(azData[ii+3]);
         cell.aCoord[ii+1].i = sqlite3_value_int(azData[ii+4]);
         if( cell.aCoord[ii].i>cell.aCoord[ii+1].i ){
-          rc = SQLITE_CONSTRAINT;
+          rc = rtreeConstraintError(pRtree, ii+1);
           goto constraint;
         }
       }
     }
 
-    /* Figure out the rowid of the new row. */
-    if( sqlite3_value_type(azData[2])==SQLITE_NULL ){
-      rc = newRowid(pRtree, &cell.iRowid);
-    }else{
+    /* If a rowid value was supplied, check if it is already present in 
+    ** the table. If so, the constraint has failed. */
+    if( sqlite3_value_type(azData[2])!=SQLITE_NULL ){
       cell.iRowid = sqlite3_value_int64(azData[2]);
-      sqlite3_bind_int64(pRtree->pReadRowid, 1, cell.iRowid);
-      if( SQLITE_ROW==sqlite3_step(pRtree->pReadRowid) ){
-        sqlite3_reset(pRtree->pReadRowid);
-        rc = SQLITE_CONSTRAINT;
-        goto constraint;
+      if( sqlite3_value_type(azData[0])==SQLITE_NULL
+       || sqlite3_value_int64(azData[0])!=cell.iRowid
+      ){
+        int steprc;
+        sqlite3_bind_int64(pRtree->pReadRowid, 1, cell.iRowid);
+        steprc = sqlite3_step(pRtree->pReadRowid);
+        rc = sqlite3_reset(pRtree->pReadRowid);
+        if( SQLITE_ROW==steprc ){
+          if( sqlite3_vtab_on_conflict(pRtree->db)==SQLITE_REPLACE ){
+            rc = rtreeDeleteRowid(pRtree, cell.iRowid);
+          }else{
+            rc = rtreeConstraintError(pRtree, 0);
+            goto constraint;
+          }
+        }
       }
-      rc = sqlite3_reset(pRtree->pReadRowid);
+      bHaveRowid = 1;
     }
+  }
+
+  /* If azData[0] is not an SQL NULL value, it is the rowid of a
+  ** record to delete from the r-tree table. The following block does
+  ** just that.
+  */
+  if( sqlite3_value_type(azData[0])!=SQLITE_NULL ){
+    rc = rtreeDeleteRowid(pRtree, sqlite3_value_int64(azData[0]));
+  }
+
+  /* If the azData[] array contains more than one element, elements
+  ** (azData[2]..azData[argc-1]) contain a new record to insert into
+  ** the r-tree structure.
+  */
+  if( rc==SQLITE_OK && nData>1 ){
+    /* Insert the new record into the r-tree */
+    RtreeNode *pLeaf = 0;
+
+    /* Figure out the rowid of the new row. */
+    if( bHaveRowid==0 ){
+      rc = newRowid(pRtree, &cell.iRowid);
+    }
+    *pRowid = cell.iRowid;
 
     if( rc==SQLITE_OK ){
       rc = ChooseLeaf(pRtree, &cell, 0, &pLeaf);
     }
     if( rc==SQLITE_OK ){
       int rc2;
