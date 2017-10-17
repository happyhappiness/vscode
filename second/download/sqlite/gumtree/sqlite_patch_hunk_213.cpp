     **     SELECT a+b AS x FROM table WHERE x<10;
     **
     ** In cases like this, replace pExpr with a copy of the expression that
     ** forms the result set entry ("a+b" in the example) and return immediately.
     ** Note that the expression in the result set should have already been
     ** resolved by the time the WHERE clause is resolved.
+    **
+    ** The ability to use an output result-set column in the WHERE, GROUP BY,
+    ** or HAVING clauses, or as part of a larger expression in the ORDER BY
+    ** clause is not standard SQL.  This is a (goofy) SQLite extension, that
+    ** is supported for backwards compatibility only. Hence, we issue a warning
+    ** on sqlite3_log() whenever the capability is used.
     */
-    if( cnt==0 && (pEList = pNC->pEList)!=0 && zTab==0 ){
+    if( (pEList = pNC->pEList)!=0
+     && zTab==0
+     && cnt==0
+    ){
       for(j=0; j<pEList->nExpr; j++){
         char *zAs = pEList->a[j].zName;
         if( zAs!=0 && sqlite3StrICmp(zAs, zCol)==0 ){
           Expr *pOrig;
           assert( pExpr->pLeft==0 && pExpr->pRight==0 );
           assert( pExpr->x.pList==0 );
           assert( pExpr->x.pSelect==0 );
           pOrig = pEList->a[j].pExpr;
-          if( !pNC->allowAgg && ExprHasProperty(pOrig, EP_Agg) ){
+          if( (pNC->ncFlags&NC_AllowAgg)==0 && ExprHasProperty(pOrig, EP_Agg) ){
             sqlite3ErrorMsg(pParse, "misuse of aliased aggregate %s", zAs);
-            return 2;
+            return WRC_Abort;
+          }
+          if( sqlite3ExprVectorSize(pOrig)!=1 ){
+            sqlite3ErrorMsg(pParse, "row value misused");
+            return WRC_Abort;
           }
-          resolveAlias(pParse, pEList, j, pExpr, "");
+          resolveAlias(pParse, pEList, j, pExpr, "", nSubquery);
           cnt = 1;
           pMatch = 0;
           assert( zTab==0 && zDb==0 );
           goto lookupname_end;
         }
       } 
     }
 
     /* Advance to the next name context.  The loop will exit when either
     ** we have a match (cnt>0) or when we run out of name contexts.
     */
-    if( cnt==0 ){
-      pNC = pNC->pNext;
-    }
-  }
+    if( cnt ) break;
+    pNC = pNC->pNext;
+    nSubquery++;
+  }while( pNC );
+
 
   /*
   ** If X and Y are NULL (in other words if only the column name Z is
   ** supplied) and the value of Z is enclosed in double-quotes, then
   ** Z is a string literal if it doesn't match any column names.  In that
   ** case, we need to return right away and not make any changes to
