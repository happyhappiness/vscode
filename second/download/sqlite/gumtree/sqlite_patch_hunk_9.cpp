       pIdxInfo->aConstraintUsage[ii].argvIndex = 1;
       pIdxInfo->aConstraintUsage[jj].omit = 1;
 
       /* This strategy involves a two rowid lookups on an B-Tree structures
       ** and then a linear search of an R-Tree node. This should be 
       ** considered almost as quick as a direct rowid lookup (for which 
-      ** sqlite uses an internal cost of 0.0). It is expected to return
-      ** a single row.
+      ** sqlite uses an internal cost of 0.0).
       */ 
-      pIdxInfo->estimatedCost = 30.0;
-      pIdxInfo->estimatedRows = 1;
+      pIdxInfo->estimatedCost = 10.0;
       return SQLITE_OK;
     }
 
-    if( p->usable && (p->iColumn>0 || p->op==SQLITE_INDEX_CONSTRAINT_MATCH) ){
-      u8 op;
+    if( p->usable && p->iColumn>0 ){
+      u8 op = 0;
       switch( p->op ){
         case SQLITE_INDEX_CONSTRAINT_EQ: op = RTREE_EQ; break;
         case SQLITE_INDEX_CONSTRAINT_GT: op = RTREE_GT; break;
         case SQLITE_INDEX_CONSTRAINT_LE: op = RTREE_LE; break;
         case SQLITE_INDEX_CONSTRAINT_LT: op = RTREE_LT; break;
         case SQLITE_INDEX_CONSTRAINT_GE: op = RTREE_GE; break;
-        default:
-          assert( p->op==SQLITE_INDEX_CONSTRAINT_MATCH );
-          op = RTREE_MATCH; 
-          break;
       }
-      zIdxStr[iIdx++] = op;
-      zIdxStr[iIdx++] = (char)(p->iColumn - 1 + '0');
-      pIdxInfo->aConstraintUsage[ii].argvIndex = (iIdx/2);
-      pIdxInfo->aConstraintUsage[ii].omit = 1;
+      if( op ){
+        /* Make sure this particular constraint has not been used before.
+        ** If it has been used before, ignore it.
+        **
+        ** A <= or < can be used if there is a prior >= or >.
+        ** A >= or > can be used if there is a prior < or <=.
+        ** A <= or < is disqualified if there is a prior <=, <, or ==.
+        ** A >= or > is disqualified if there is a prior >=, >, or ==.
+        ** A == is disqualifed if there is any prior constraint.
+        */
+        int j, opmsk;
+        static const unsigned char compatible[] = { 0, 0, 1, 1, 2, 2 };
+        assert( compatible[RTREE_EQ & 7]==0 );
+        assert( compatible[RTREE_LT & 7]==1 );
+        assert( compatible[RTREE_LE & 7]==1 );
+        assert( compatible[RTREE_GT & 7]==2 );
+        assert( compatible[RTREE_GE & 7]==2 );
+        cCol = p->iColumn - 1 + 'a';
+        opmsk = compatible[op & 7];
+        for(j=0; j<iIdx; j+=2){
+          if( zIdxStr[j+1]==cCol && (compatible[zIdxStr[j] & 7] & opmsk)!=0 ){
+            op = 0;
+            break;
+          }
+        }
+      }
+      if( op ){
+        assert( iIdx<sizeof(zIdxStr)-1 );
+        zIdxStr[iIdx++] = op;
+        zIdxStr[iIdx++] = cCol;
+        pIdxInfo->aConstraintUsage[ii].argvIndex = (iIdx/2);
+        pIdxInfo->aConstraintUsage[ii].omit = 1;
+      }
     }
   }
 
   pIdxInfo->idxNum = 2;
   pIdxInfo->needToFreeIdxStr = 1;
   if( iIdx>0 && 0==(pIdxInfo->idxStr = sqlite3_mprintf("%s", zIdxStr)) ){
     return SQLITE_NOMEM;
   }
-
-  nRow = pRtree->nRowEst >> (iIdx/2);
-  pIdxInfo->estimatedCost = (double)6.0 * (double)nRow;
-  pIdxInfo->estimatedRows = nRow;
-
+  assert( iIdx>=0 );
+  pIdxInfo->estimatedCost = (2000000.0 / (double)(iIdx + 1));
   return rc;
 }
 
 /*
 ** Return the N-dimensional volumn of the cell stored in *p.
 */
-static RtreeDValue cellArea(Rtree *pRtree, RtreeCell *p){
-  RtreeDValue area = (RtreeDValue)1;
-  assert( pRtree->nDim>=1 && pRtree->nDim<=5 );
-#ifndef SQLITE_RTREE_INT_ONLY
-  if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
-    switch( pRtree->nDim ){
-      case 5:  area  = p->aCoord[9].f - p->aCoord[8].f;
-      case 4:  area *= p->aCoord[7].f - p->aCoord[6].f;
-      case 3:  area *= p->aCoord[5].f - p->aCoord[4].f;
-      case 2:  area *= p->aCoord[3].f - p->aCoord[2].f;
-      default: area *= p->aCoord[1].f - p->aCoord[0].f;
-    }
-  }else
-#endif
-  {
-    switch( pRtree->nDim ){
-      case 5:  area  = p->aCoord[9].i - p->aCoord[8].i;
-      case 4:  area *= p->aCoord[7].i - p->aCoord[6].i;
-      case 3:  area *= p->aCoord[5].i - p->aCoord[4].i;
-      case 2:  area *= p->aCoord[3].i - p->aCoord[2].i;
-      default: area *= p->aCoord[1].i - p->aCoord[0].i;
-    }
+static float cellArea(Rtree *pRtree, RtreeCell *p){
+  float area = 1.0;
+  int ii;
+  for(ii=0; ii<(pRtree->nDim*2); ii+=2){
+    area = area * (DCOORD(p->aCoord[ii+1]) - DCOORD(p->aCoord[ii]));
   }
   return area;
 }
 
 /*
 ** Return the margin length of cell p. The margin length is the sum
 ** of the objects size in each dimension.
 */
-static RtreeDValue cellMargin(Rtree *pRtree, RtreeCell *p){
-  RtreeDValue margin = 0;
-  int ii = pRtree->nDim2 - 2;
-  do{
+static float cellMargin(Rtree *pRtree, RtreeCell *p){
+  float margin = 0.0;
+  int ii;
+  for(ii=0; ii<(pRtree->nDim*2); ii+=2){
     margin += (DCOORD(p->aCoord[ii+1]) - DCOORD(p->aCoord[ii]));
-    ii -= 2;
-  }while( ii>=0 );
+  }
   return margin;
 }
 
 /*
 ** Store the union of cells p1 and p2 in p1.
 */
 static void cellUnion(Rtree *pRtree, RtreeCell *p1, RtreeCell *p2){
-  int ii = 0;
+  int ii;
   if( pRtree->eCoordType==RTREE_COORD_REAL32 ){
-    do{
+    for(ii=0; ii<(pRtree->nDim*2); ii+=2){
       p1->aCoord[ii].f = MIN(p1->aCoord[ii].f, p2->aCoord[ii].f);
       p1->aCoord[ii+1].f = MAX(p1->aCoord[ii+1].f, p2->aCoord[ii+1].f);
-      ii += 2;
-    }while( ii<pRtree->nDim2 );
+    }
   }else{
-    do{
+    for(ii=0; ii<(pRtree->nDim*2); ii+=2){
       p1->aCoord[ii].i = MIN(p1->aCoord[ii].i, p2->aCoord[ii].i);
       p1->aCoord[ii+1].i = MAX(p1->aCoord[ii+1].i, p2->aCoord[ii+1].i);
-      ii += 2;
-    }while( ii<pRtree->nDim2 );
+    }
   }
 }
 
 /*
 ** Return true if the area covered by p2 is a subset of the area covered
 ** by p1. False otherwise.
 */
 static int cellContains(Rtree *pRtree, RtreeCell *p1, RtreeCell *p2){
   int ii;
   int isInt = (pRtree->eCoordType==RTREE_COORD_INT32);
-  for(ii=0; ii<pRtree->nDim2; ii+=2){
+  for(ii=0; ii<(pRtree->nDim*2); ii+=2){
     RtreeCoord *a1 = &p1->aCoord[ii];
     RtreeCoord *a2 = &p2->aCoord[ii];
     if( (!isInt && (a2[0].f<a1[0].f || a2[1].f>a1[1].f)) 
      || ( isInt && (a2[0].i<a1[0].i || a2[1].i>a1[1].i)) 
     ){
       return 0;
