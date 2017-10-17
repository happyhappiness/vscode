   ** cid:        Column id (numbered from left to right, starting at 0)
   ** name:       Column name
   ** type:       Column declaration type.
   ** notnull:    True if 'NOT NULL' is part of column declaration
   ** dflt_value: The default value for the column, if any.
   */
-  if( sqlite3StrICmp(zLeft, "table_info")==0 && zRight ){
+  case PragTyp_TABLE_INFO: if( zRight ){
     Table *pTab;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
-    pTab = sqlite3FindTable(db, zRight, zDb);
+    pTab = sqlite3LocateTable(pParse, LOCATE_NOERR, zRight, zDb);
     if( pTab ){
-      int i;
+      int i, k;
       int nHidden = 0;
       Column *pCol;
-      sqlite3VdbeSetNumCols(v, 6);
+      Index *pPk = sqlite3PrimaryKeyIndex(pTab);
       pParse->nMem = 6;
-      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "cid", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "type", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 3, COLNAME_NAME, "notnull", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 4, COLNAME_NAME, "dflt_value", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 5, COLNAME_NAME, "pk", SQLITE_STATIC);
+      sqlite3CodeVerifySchema(pParse, iDb);
       sqlite3ViewGetColumnNames(pParse, pTab);
       for(i=0, pCol=pTab->aCol; i<pTab->nCol; i++, pCol++){
         if( IsHiddenColumn(pCol) ){
           nHidden++;
           continue;
         }
-        sqlite3VdbeAddOp2(v, OP_Integer, i-nHidden, 1);
-        sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pCol->zName, 0);
-        sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
-           pCol->zType ? pCol->zType : "", 0);
-        sqlite3VdbeAddOp2(v, OP_Integer, (pCol->notNull ? 1 : 0), 4);
-        if( pCol->zDflt ){
-          sqlite3VdbeAddOp4(v, OP_String8, 0, 5, 0, (char*)pCol->zDflt, 0);
+        if( (pCol->colFlags & COLFLAG_PRIMKEY)==0 ){
+          k = 0;
+        }else if( pPk==0 ){
+          k = 1;
         }else{
-          sqlite3VdbeAddOp2(v, OP_Null, 0, 5);
+          for(k=1; k<=pTab->nCol && pPk->aiColumn[k-1]!=i; k++){}
         }
-        sqlite3VdbeAddOp2(v, OP_Integer, pCol->isPrimKey, 6);
-        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 6);
+        assert( pCol->pDflt==0 || pCol->pDflt->op==TK_SPAN );
+        sqlite3VdbeMultiLoad(v, 1, "issisi",
+               i-nHidden,
+               pCol->zName,
+               sqlite3ColumnType(pCol,""),
+               pCol->notNull ? 1 : 0,
+               pCol->pDflt ? pCol->pDflt->u.zToken : 0,
+               k);
       }
     }
-  }else
+  }
+  break;
 
-  if( sqlite3StrICmp(zLeft, "index_info")==0 && zRight ){
+#ifdef SQLITE_DEBUG
+  case PragTyp_STATS: {
+    Index *pIdx;
+    HashElem *i;
+    pParse->nMem = 5;
+    sqlite3CodeVerifySchema(pParse, iDb);
+    for(i=sqliteHashFirst(&pDb->pSchema->tblHash); i; i=sqliteHashNext(i)){
+      Table *pTab = sqliteHashData(i);
+      sqlite3VdbeMultiLoad(v, 1, "ssiii",
+           pTab->zName,
+           0,
+           pTab->szTabRow,
+           pTab->nRowLogEst,
+           pTab->tabFlags);
+      for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
+        sqlite3VdbeMultiLoad(v, 2, "siiiX",
+           pIdx->zName,
+           pIdx->szIdxRow,
+           pIdx->aiRowLogEst[0],
+           pIdx->hasStat1);
+        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 5);
+      }
+    }
+  }
+  break;
+#endif
+
+  case PragTyp_INDEX_INFO: if( zRight ){
     Index *pIdx;
     Table *pTab;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
     pIdx = sqlite3FindIndex(db, zRight, zDb);
     if( pIdx ){
       int i;
+      int mx;
+      if( pPragma->iArg ){
+        /* PRAGMA index_xinfo (newer version with more rows and columns) */
+        mx = pIdx->nColumn;
+        pParse->nMem = 6;
+      }else{
+        /* PRAGMA index_info (legacy version) */
+        mx = pIdx->nKeyCol;
+        pParse->nMem = 3;
+      }
       pTab = pIdx->pTable;
-      sqlite3VdbeSetNumCols(v, 3);
-      pParse->nMem = 3;
-      sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seqno", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "cid", SQLITE_STATIC);
-      sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "name", SQLITE_STATIC);
-      for(i=0; i<pIdx->nColumn; i++){
-        int cnum = pIdx->aiColumn[i];
-        sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
-        sqlite3VdbeAddOp2(v, OP_Integer, cnum, 2);
-        assert( pTab->nCol>cnum );
-        sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, pTab->aCol[cnum].zName, 0);
-        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
+      sqlite3CodeVerifySchema(pParse, iDb);
+      assert( pParse->nMem<=pPragma->nPragCName );
+      for(i=0; i<mx; i++){
+        i16 cnum = pIdx->aiColumn[i];
+        sqlite3VdbeMultiLoad(v, 1, "iisX", i, cnum,
+                             cnum<0 ? 0 : pTab->aCol[cnum].zName);
+        if( pPragma->iArg ){
+          sqlite3VdbeMultiLoad(v, 4, "isiX",
+            pIdx->aSortOrder[i],
+            pIdx->azColl[i],
+            i<pIdx->nKeyCol);
+        }
+        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, pParse->nMem);
       }
     }
-  }else
+  }
+  break;
 
-  if( sqlite3StrICmp(zLeft, "index_list")==0 && zRight ){
+  case PragTyp_INDEX_LIST: if( zRight ){
     Index *pIdx;
     Table *pTab;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
+    int i;
     pTab = sqlite3FindTable(db, zRight, zDb);
     if( pTab ){
-      v = sqlite3GetVdbe(pParse);
-      pIdx = pTab->pIndex;
-      if( pIdx ){
-        int i = 0; 
-        sqlite3VdbeSetNumCols(v, 3);
-        pParse->nMem = 3;
-        sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "unique", SQLITE_STATIC);
-        while(pIdx){
-          sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
-          sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pIdx->zName, 0);
-          sqlite3VdbeAddOp2(v, OP_Integer, pIdx->onError!=OE_None, 3);
-          sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
-          ++i;
-          pIdx = pIdx->pNext;
-        }
+      pParse->nMem = 5;
+      sqlite3CodeVerifySchema(pParse, iDb);
+      for(pIdx=pTab->pIndex, i=0; pIdx; pIdx=pIdx->pNext, i++){
+        const char *azOrigin[] = { "c", "u", "pk" };
+        sqlite3VdbeMultiLoad(v, 1, "isisi",
+           i,
+           pIdx->zName,
+           IsUniqueIndex(pIdx),
+           azOrigin[pIdx->idxType],
+           pIdx->pPartIdxWhere!=0);
       }
     }
-  }else
+  }
+  break;
 
-  if( sqlite3StrICmp(zLeft, "database_list")==0 ){
+  case PragTyp_DATABASE_LIST: {
     int i;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
-    sqlite3VdbeSetNumCols(v, 3);
     pParse->nMem = 3;
-    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
-    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
-    sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "file", SQLITE_STATIC);
     for(i=0; i<db->nDb; i++){
       if( db->aDb[i].pBt==0 ) continue;
-      assert( db->aDb[i].zName!=0 );
-      sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
-      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, db->aDb[i].zName, 0);
-      sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
-           sqlite3BtreeGetFilename(db->aDb[i].pBt), 0);
-      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 3);
+      assert( db->aDb[i].zDbSName!=0 );
+      sqlite3VdbeMultiLoad(v, 1, "iss",
+         i,
+         db->aDb[i].zDbSName,
+         sqlite3BtreeGetFilename(db->aDb[i].pBt));
     }
-  }else
+  }
+  break;
 
-  if( sqlite3StrICmp(zLeft, "collation_list")==0 ){
+  case PragTyp_COLLATION_LIST: {
     int i = 0;
     HashElem *p;
-    sqlite3VdbeSetNumCols(v, 2);
     pParse->nMem = 2;
-    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "seq", SQLITE_STATIC);
-    sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "name", SQLITE_STATIC);
     for(p=sqliteHashFirst(&db->aCollSeq); p; p=sqliteHashNext(p)){
       CollSeq *pColl = (CollSeq *)sqliteHashData(p);
-      sqlite3VdbeAddOp2(v, OP_Integer, i++, 1);
-      sqlite3VdbeAddOp4(v, OP_String8, 0, 2, 0, pColl->zName, 0);
-      sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 2);
+      sqlite3VdbeMultiLoad(v, 1, "is", i++, pColl->zName);
+    }
+  }
+  break;
+
+#ifdef SQLITE_INTROSPECTION_PRAGMAS
+  case PragTyp_FUNCTION_LIST: {
+    int i;
+    HashElem *j;
+    FuncDef *p;
+    pParse->nMem = 2;
+    for(i=0; i<SQLITE_FUNC_HASH_SZ; i++){
+      for(p=sqlite3BuiltinFunctions.a[i]; p; p=p->u.pHash ){
+        sqlite3VdbeMultiLoad(v, 1, "si", p->zName, 1);
+      }
+    }
+    for(j=sqliteHashFirst(&db->aFunc); j; j=sqliteHashNext(j)){
+      p = (FuncDef*)sqliteHashData(j);
+      sqlite3VdbeMultiLoad(v, 1, "si", p->zName, 0);
+    }
+  }
+  break;
+
+#ifndef SQLITE_OMIT_VIRTUALTABLE
+  case PragTyp_MODULE_LIST: {
+    HashElem *j;
+    pParse->nMem = 1;
+    for(j=sqliteHashFirst(&db->aModule); j; j=sqliteHashNext(j)){
+      Module *pMod = (Module*)sqliteHashData(j);
+      sqlite3VdbeMultiLoad(v, 1, "s", pMod->zName);
+    }
+  }
+  break;
+#endif /* SQLITE_OMIT_VIRTUALTABLE */
+
+  case PragTyp_PRAGMA_LIST: {
+    int i;
+    for(i=0; i<ArraySize(aPragmaName); i++){
+      sqlite3VdbeMultiLoad(v, 1, "s", aPragmaName[i].zName);
     }
-  }else
+  }
+  break;
+#endif /* SQLITE_INTROSPECTION_PRAGMAS */
+
 #endif /* SQLITE_OMIT_SCHEMA_PRAGMAS */
 
 #ifndef SQLITE_OMIT_FOREIGN_KEY
-  if( sqlite3StrICmp(zLeft, "foreign_key_list")==0 && zRight ){
+  case PragTyp_FOREIGN_KEY_LIST: if( zRight ){
     FKey *pFK;
     Table *pTab;
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
     pTab = sqlite3FindTable(db, zRight, zDb);
     if( pTab ){
-      v = sqlite3GetVdbe(pParse);
       pFK = pTab->pFKey;
       if( pFK ){
         int i = 0; 
-        sqlite3VdbeSetNumCols(v, 8);
         pParse->nMem = 8;
-        sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "id", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 1, COLNAME_NAME, "seq", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 2, COLNAME_NAME, "table", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 3, COLNAME_NAME, "from", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 4, COLNAME_NAME, "to", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 5, COLNAME_NAME, "on_update", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 6, COLNAME_NAME, "on_delete", SQLITE_STATIC);
-        sqlite3VdbeSetColName(v, 7, COLNAME_NAME, "match", SQLITE_STATIC);
+        sqlite3CodeVerifySchema(pParse, iDb);
         while(pFK){
           int j;
           for(j=0; j<pFK->nCol; j++){
-            char *zCol = pFK->aCol[j].zCol;
-            char *zOnUpdate = (char *)actionName(pFK->updateConf);
-            char *zOnDelete = (char *)actionName(pFK->deleteConf);
-            sqlite3VdbeAddOp2(v, OP_Integer, i, 1);
-            sqlite3VdbeAddOp2(v, OP_Integer, j, 2);
-            sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, pFK->zTo, 0);
-            sqlite3VdbeAddOp4(v, OP_String8, 0, 4, 0,
-                              pTab->aCol[pFK->aCol[j].iFrom].zName, 0);
-            sqlite3VdbeAddOp4(v, zCol ? OP_String8 : OP_Null, 0, 5, 0, zCol, 0);
-            sqlite3VdbeAddOp4(v, OP_String8, 0, 6, 0, zOnUpdate, 0);
-            sqlite3VdbeAddOp4(v, OP_String8, 0, 7, 0, zOnDelete, 0);
-            sqlite3VdbeAddOp4(v, OP_String8, 0, 8, 0, "NONE", 0);
-            sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 8);
+            sqlite3VdbeMultiLoad(v, 1, "iissssss",
+                   i,
+                   j,
+                   pFK->zTo,
+                   pTab->aCol[pFK->aCol[j].iFrom].zName,
+                   pFK->aCol[j].zCol,
+                   actionName(pFK->aAction[1]),  /* ON UPDATE */
+                   actionName(pFK->aAction[0]),  /* ON DELETE */
+                   "NONE");
           }
           ++i;
           pFK = pFK->pNextFrom;
         }
       }
     }
-  }else
+  }
+  break;
+#endif /* !defined(SQLITE_OMIT_FOREIGN_KEY) */
+
+#ifndef SQLITE_OMIT_FOREIGN_KEY
+#ifndef SQLITE_OMIT_TRIGGER
+  case PragTyp_FOREIGN_KEY_CHECK: {
+    FKey *pFK;             /* A foreign key constraint */
+    Table *pTab;           /* Child table contain "REFERENCES" keyword */
+    Table *pParent;        /* Parent table that child points to */
+    Index *pIdx;           /* Index in the parent table */
+    int i;                 /* Loop counter:  Foreign key number for pTab */
+    int j;                 /* Loop counter:  Field of the foreign key */
+    HashElem *k;           /* Loop counter:  Next table in schema */
+    int x;                 /* result variable */
+    int regResult;         /* 3 registers to hold a result row */
+    int regKey;            /* Register to hold key for checking the FK */
+    int regRow;            /* Registers to hold a row from pTab */
+    int addrTop;           /* Top of a loop checking foreign keys */
+    int addrOk;            /* Jump here if the key is OK */
+    int *aiCols;           /* child to parent column mapping */
+
+    regResult = pParse->nMem+1;
+    pParse->nMem += 4;
+    regKey = ++pParse->nMem;
+    regRow = ++pParse->nMem;
+    sqlite3CodeVerifySchema(pParse, iDb);
+    k = sqliteHashFirst(&db->aDb[iDb].pSchema->tblHash);
+    while( k ){
+      if( zRight ){
+        pTab = sqlite3LocateTable(pParse, 0, zRight, zDb);
+        k = 0;
+      }else{
+        pTab = (Table*)sqliteHashData(k);
+        k = sqliteHashNext(k);
+      }
+      if( pTab==0 || pTab->pFKey==0 ) continue;
+      sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);
+      if( pTab->nCol+regRow>pParse->nMem ) pParse->nMem = pTab->nCol + regRow;
+      sqlite3OpenTable(pParse, 0, iDb, pTab, OP_OpenRead);
+      sqlite3VdbeLoadString(v, regResult, pTab->zName);
+      for(i=1, pFK=pTab->pFKey; pFK; i++, pFK=pFK->pNextFrom){
+        pParent = sqlite3FindTable(db, pFK->zTo, zDb);
+        if( pParent==0 ) continue;
+        pIdx = 0;
+        sqlite3TableLock(pParse, iDb, pParent->tnum, 0, pParent->zName);
+        x = sqlite3FkLocateIndex(pParse, pParent, pFK, &pIdx, 0);
+        if( x==0 ){
+          if( pIdx==0 ){
+            sqlite3OpenTable(pParse, i, iDb, pParent, OP_OpenRead);
+          }else{
+            sqlite3VdbeAddOp3(v, OP_OpenRead, i, pIdx->tnum, iDb);
+            sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
+          }
+        }else{
+          k = 0;
+          break;
+        }
+      }
+      assert( pParse->nErr>0 || pFK==0 );
+      if( pFK ) break;
+      if( pParse->nTab<i ) pParse->nTab = i;
+      addrTop = sqlite3VdbeAddOp1(v, OP_Rewind, 0); VdbeCoverage(v);
+      for(i=1, pFK=pTab->pFKey; pFK; i++, pFK=pFK->pNextFrom){
+        pParent = sqlite3FindTable(db, pFK->zTo, zDb);
+        pIdx = 0;
+        aiCols = 0;
+        if( pParent ){
+          x = sqlite3FkLocateIndex(pParse, pParent, pFK, &pIdx, &aiCols);
+          assert( x==0 );
+        }
+        addrOk = sqlite3VdbeMakeLabel(v);
+
+        /* Generate code to read the child key values into registers
+        ** regRow..regRow+n. If any of the child key values are NULL, this 
+        ** row cannot cause an FK violation. Jump directly to addrOk in 
+        ** this case. */
+        for(j=0; j<pFK->nCol; j++){
+          int iCol = aiCols ? aiCols[j] : pFK->aCol[j].iFrom;
+          sqlite3ExprCodeGetColumnOfTable(v, pTab, 0, iCol, regRow+j);
+          sqlite3VdbeAddOp2(v, OP_IsNull, regRow+j, addrOk); VdbeCoverage(v);
+        }
+
+        /* Generate code to query the parent index for a matching parent
+        ** key. If a match is found, jump to addrOk. */
+        if( pIdx ){
+          sqlite3VdbeAddOp4(v, OP_MakeRecord, regRow, pFK->nCol, regKey,
+              sqlite3IndexAffinityStr(db,pIdx), pFK->nCol);
+          sqlite3VdbeAddOp4Int(v, OP_Found, i, addrOk, regKey, 0);
+          VdbeCoverage(v);
+        }else if( pParent ){
+          int jmp = sqlite3VdbeCurrentAddr(v)+2;
+          sqlite3VdbeAddOp3(v, OP_SeekRowid, i, jmp, regRow); VdbeCoverage(v);
+          sqlite3VdbeGoto(v, addrOk);
+          assert( pFK->nCol==1 );
+        }
+
+        /* Generate code to report an FK violation to the caller. */
+        if( HasRowid(pTab) ){
+          sqlite3VdbeAddOp2(v, OP_Rowid, 0, regResult+1);
+        }else{
+          sqlite3VdbeAddOp2(v, OP_Null, 0, regResult+1);
+        }
+        sqlite3VdbeMultiLoad(v, regResult+2, "siX", pFK->zTo, i-1);
+        sqlite3VdbeAddOp2(v, OP_ResultRow, regResult, 4);
+        sqlite3VdbeResolveLabel(v, addrOk);
+        sqlite3DbFree(db, aiCols);
+      }
+      sqlite3VdbeAddOp2(v, OP_Next, 0, addrTop+1); VdbeCoverage(v);
+      sqlite3VdbeJumpHere(v, addrTop);
+    }
+  }
+  break;
+#endif /* !defined(SQLITE_OMIT_TRIGGER) */
 #endif /* !defined(SQLITE_OMIT_FOREIGN_KEY) */
 
 #ifndef NDEBUG
-  if( sqlite3StrICmp(zLeft, "parser_trace")==0 ){
+  case PragTyp_PARSER_TRACE: {
     if( zRight ){
-      if( getBoolean(zRight) ){
-        sqlite3ParserTrace(stderr, "parser: ");
+      if( sqlite3GetBoolean(zRight, 0) ){
+        sqlite3ParserTrace(stdout, "parser: ");
       }else{
         sqlite3ParserTrace(0, 0);
       }
     }
-  }else
+  }
+  break;
 #endif
 
   /* Reinstall the LIKE and GLOB functions.  The variant of LIKE
   ** used will be case sensitive or not depending on the RHS.
   */
-  if( sqlite3StrICmp(zLeft, "case_sensitive_like")==0 ){
+  case PragTyp_CASE_SENSITIVE_LIKE: {
     if( zRight ){
-      sqlite3RegisterLikeFunctions(db, getBoolean(zRight));
+      sqlite3RegisterLikeFunctions(db, sqlite3GetBoolean(zRight, 0));
     }
-  }else
+  }
+  break;
 
 #ifndef SQLITE_INTEGRITY_CHECK_ERROR_MAX
 # define SQLITE_INTEGRITY_CHECK_ERROR_MAX 100
 #endif
 
 #ifndef SQLITE_OMIT_INTEGRITY_CHECK
-  /* Pragma "quick_check" is an experimental reduced version of 
+  /*    PRAGMA integrity_check
+  **    PRAGMA integrity_check(N)
+  **    PRAGMA quick_check
+  **    PRAGMA quick_check(N)
+  **
+  ** Verify the integrity of the database.
+  **
+  ** The "quick_check" is reduced version of 
   ** integrity_check designed to detect most database corruption
-  ** without most of the overhead of a full integrity-check.
+  ** without the overhead of cross-checking indexes.  Quick_check
+  ** is linear time wherease integrity_check is O(NlogN).
   */
-  if( sqlite3StrICmp(zLeft, "integrity_check")==0
-   || sqlite3StrICmp(zLeft, "quick_check")==0 
-  ){
+  case PragTyp_INTEGRITY_CHECK: {
     int i, j, addr, mxErr;
 
-    /* Code that appears at the end of the integrity check.  If no error
-    ** messages have been generated, output OK.  Otherwise output the
-    ** error message
-    */
-    static const VdbeOpList endCode[] = {
-      { OP_AddImm,      1, 0,        0},    /* 0 */
-      { OP_IfNeg,       1, 0,        0},    /* 1 */
-      { OP_String8,     0, 3,        0},    /* 2 */
-      { OP_ResultRow,   3, 1,        0},
-    };
+    int isQuick = (sqlite3Tolower(zLeft[0])=='q');
 
-    int isQuick = (zLeft[0]=='q');
+    /* If the PRAGMA command was of the form "PRAGMA <db>.integrity_check",
+    ** then iDb is set to the index of the database identified by <db>.
+    ** In this case, the integrity of database iDb only is verified by
+    ** the VDBE created below.
+    **
+    ** Otherwise, if the command was simply "PRAGMA integrity_check" (or
+    ** "PRAGMA quick_check"), then iDb is set to 0. In this case, set iDb
+    ** to -1 here, to indicate that the VDBE should verify the integrity
+    ** of all attached databases.  */
+    assert( iDb>=0 );
+    assert( iDb==0 || pId2->z );
+    if( pId2->z==0 ) iDb = -1;
 
     /* Initialize the VDBE program */
-    if( sqlite3ReadSchema(pParse) ) goto pragma_out;
     pParse->nMem = 6;
-    sqlite3VdbeSetNumCols(v, 1);
-    sqlite3VdbeSetColName(v, 0, COLNAME_NAME, "integrity_check", SQLITE_STATIC);
 
     /* Set the maximum error count */
     mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
     if( zRight ){
-      mxErr = atoi(zRight);
+      sqlite3GetInt32(zRight, &mxErr);
       if( mxErr<=0 ){
         mxErr = SQLITE_INTEGRITY_CHECK_ERROR_MAX;
       }
     }
-    sqlite3VdbeAddOp2(v, OP_Integer, mxErr, 1);  /* reg[1] holds errors left */
+    sqlite3VdbeAddOp2(v, OP_Integer, mxErr-1, 1); /* reg[1] holds errors left */
 
     /* Do an integrity check on each database file */
     for(i=0; i<db->nDb; i++){
-      HashElem *x;
-      Hash *pTbls;
-      int cnt = 0;
+      HashElem *x;     /* For looping over tables in the schema */
+      Hash *pTbls;     /* Set of all tables in the schema */
+      int *aRoot;      /* Array of root page numbers of all btrees */
+      int cnt = 0;     /* Number of entries in aRoot[] */
+      int mxIdx = 0;   /* Maximum number of indexes for any table */
 
       if( OMIT_TEMPDB && i==1 ) continue;
+      if( iDb>=0 && i!=iDb ) continue;
 
       sqlite3CodeVerifySchema(pParse, i);
-      addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1); /* Halt if out of errors */
-      sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
-      sqlite3VdbeJumpHere(v, addr);
 
       /* Do an integrity check of the B-Tree
       **
-      ** Begin by filling registers 2, 3, ... with the root pages numbers
+      ** Begin by finding the root pages numbers
       ** for all tables and indices in the database.
       */
+      assert( sqlite3SchemaMutexHeld(db, i, 0) );
       pTbls = &db->aDb[i].pSchema->tblHash;
-      for(x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
+      for(cnt=0, x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
+        Table *pTab = sqliteHashData(x);  /* Current table */
+        Index *pIdx;                      /* An index on pTab */
+        int nIdx;                         /* Number of indexes on pTab */
+        if( HasRowid(pTab) ) cnt++;
+        for(nIdx=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, nIdx++){ cnt++; }
+        if( nIdx>mxIdx ) mxIdx = nIdx;
+      }
+      aRoot = sqlite3DbMallocRawNN(db, sizeof(int)*(cnt+1));
+      if( aRoot==0 ) break;
+      for(cnt=0, x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
         Table *pTab = sqliteHashData(x);
         Index *pIdx;
-        sqlite3VdbeAddOp2(v, OP_Integer, pTab->tnum, 2+cnt);
-        cnt++;
+        if( HasRowid(pTab) ) aRoot[++cnt] = pTab->tnum;
         for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
-          sqlite3VdbeAddOp2(v, OP_Integer, pIdx->tnum, 2+cnt);
-          cnt++;
+          aRoot[++cnt] = pIdx->tnum;
         }
       }
+      aRoot[0] = cnt;
 
       /* Make sure sufficient number of registers have been allocated */
-      if( pParse->nMem < cnt+4 ){
-        pParse->nMem = cnt+4;
-      }
+      pParse->nMem = MAX( pParse->nMem, 8+mxIdx );
+      sqlite3ClearTempRegCache(pParse);
 
       /* Do the b-tree integrity checks */
-      sqlite3VdbeAddOp3(v, OP_IntegrityCk, 2, cnt, 1);
+      sqlite3VdbeAddOp4(v, OP_IntegrityCk, 2, cnt, 1, (char*)aRoot,P4_INTARRAY);
       sqlite3VdbeChangeP5(v, (u8)i);
-      addr = sqlite3VdbeAddOp1(v, OP_IsNull, 2);
+      addr = sqlite3VdbeAddOp1(v, OP_IsNull, 2); VdbeCoverage(v);
       sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0,
-         sqlite3MPrintf(db, "*** in database %s ***\n", db->aDb[i].zName),
+         sqlite3MPrintf(db, "*** in database %s ***\n", db->aDb[i].zDbSName),
          P4_DYNAMIC);
-      sqlite3VdbeAddOp3(v, OP_Move, 2, 4, 1);
-      sqlite3VdbeAddOp3(v, OP_Concat, 4, 3, 2);
-      sqlite3VdbeAddOp2(v, OP_ResultRow, 2, 1);
+      sqlite3VdbeAddOp3(v, OP_Concat, 2, 3, 3);
+      integrityCheckResultRow(v);
       sqlite3VdbeJumpHere(v, addr);
 
       /* Make sure all the indices are constructed correctly.
       */
-      for(x=sqliteHashFirst(pTbls); x && !isQuick; x=sqliteHashNext(x)){
+      for(x=sqliteHashFirst(pTbls); x; x=sqliteHashNext(x)){
         Table *pTab = sqliteHashData(x);
-        Index *pIdx;
+        Index *pIdx, *pPk;
+        Index *pPrior = 0;
         int loopTop;
+        int iDataCur, iIdxCur;
+        int r1 = -1;
 
-        if( pTab->pIndex==0 ) continue;
-        addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);  /* Stop if out of errors */
-        sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
-        sqlite3VdbeJumpHere(v, addr);
-        sqlite3OpenTableAndIndices(pParse, pTab, 1, OP_OpenRead);
-        sqlite3VdbeAddOp2(v, OP_Integer, 0, 2);  /* reg(2) will count entries */
-        loopTop = sqlite3VdbeAddOp2(v, OP_Rewind, 1, 0);
-        sqlite3VdbeAddOp2(v, OP_AddImm, 2, 1);   /* increment entry count */
+        if( pTab->tnum<1 ) continue;  /* Skip VIEWs or VIRTUAL TABLEs */
+        pPk = HasRowid(pTab) ? 0 : sqlite3PrimaryKeyIndex(pTab);
+        sqlite3ExprCacheClear(pParse);
+        sqlite3OpenTableAndIndices(pParse, pTab, OP_OpenRead, 0,
+                                   1, 0, &iDataCur, &iIdxCur);
+        /* reg[7] counts the number of entries in the table.
+        ** reg[8+i] counts the number of entries in the i-th index 
+        */
+        sqlite3VdbeAddOp2(v, OP_Integer, 0, 7);
         for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
+          sqlite3VdbeAddOp2(v, OP_Integer, 0, 8+j); /* index entries counter */
+        }
+        assert( pParse->nMem>=8+j );
+        assert( sqlite3NoTempsInRange(pParse,1,7+j) );
+        sqlite3VdbeAddOp2(v, OP_Rewind, iDataCur, 0); VdbeCoverage(v);
+        loopTop = sqlite3VdbeAddOp2(v, OP_AddImm, 7, 1);
+        /* Verify that all NOT NULL columns really are NOT NULL */
+        for(j=0; j<pTab->nCol; j++){
+          char *zErr;
           int jmp2;
-          static const VdbeOpList idxErr[] = {
-            { OP_AddImm,      1, -1,  0},
-            { OP_String8,     0,  3,  0},    /* 1 */
-            { OP_Rowid,       1,  4,  0},
-            { OP_String8,     0,  5,  0},    /* 3 */
-            { OP_String8,     0,  6,  0},    /* 4 */
-            { OP_Concat,      4,  3,  3},
-            { OP_Concat,      5,  3,  3},
-            { OP_Concat,      6,  3,  3},
-            { OP_ResultRow,   3,  1,  0},
-            { OP_IfPos,       1,  0,  0},    /* 9 */
-            { OP_Halt,        0,  0,  0},
-          };
-          sqlite3GenerateIndexKey(pParse, pIdx, 1, 3, 1);
-          jmp2 = sqlite3VdbeAddOp3(v, OP_Found, j+2, 0, 3);
-          addr = sqlite3VdbeAddOpList(v, ArraySize(idxErr), idxErr);
-          sqlite3VdbeChangeP4(v, addr+1, "rowid ", P4_STATIC);
-          sqlite3VdbeChangeP4(v, addr+3, " missing from index ", P4_STATIC);
-          sqlite3VdbeChangeP4(v, addr+4, pIdx->zName, P4_STATIC);
-          sqlite3VdbeJumpHere(v, addr+9);
+          if( j==pTab->iPKey ) continue;
+          if( pTab->aCol[j].notNull==0 ) continue;
+          sqlite3ExprCodeGetColumnOfTable(v, pTab, iDataCur, j, 3);
+          sqlite3VdbeChangeP5(v, OPFLAG_TYPEOFARG);
+          jmp2 = sqlite3VdbeAddOp1(v, OP_NotNull, 3); VdbeCoverage(v);
+          zErr = sqlite3MPrintf(db, "NULL value in %s.%s", pTab->zName,
+                              pTab->aCol[j].zName);
+          sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, zErr, P4_DYNAMIC);
+          integrityCheckResultRow(v);
           sqlite3VdbeJumpHere(v, jmp2);
         }
-        sqlite3VdbeAddOp2(v, OP_Next, 1, loopTop+1);
-        sqlite3VdbeJumpHere(v, loopTop);
-        for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
-          static const VdbeOpList cntIdx[] = {
-             { OP_Integer,      0,  3,  0},
-             { OP_Rewind,       0,  0,  0},  /* 1 */
-             { OP_AddImm,       3,  1,  0},
-             { OP_Next,         0,  0,  0},  /* 3 */
-             { OP_Eq,           2,  0,  3},  /* 4 */
-             { OP_AddImm,       1, -1,  0},
-             { OP_String8,      0,  2,  0},  /* 6 */
-             { OP_String8,      0,  3,  0},  /* 7 */
-             { OP_Concat,       3,  2,  2},
-             { OP_ResultRow,    2,  1,  0},
-          };
-          addr = sqlite3VdbeAddOp1(v, OP_IfPos, 1);
-          sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
-          sqlite3VdbeJumpHere(v, addr);
-          addr = sqlite3VdbeAddOpList(v, ArraySize(cntIdx), cntIdx);
-          sqlite3VdbeChangeP1(v, addr+1, j+2);
-          sqlite3VdbeChangeP2(v, addr+1, addr+4);
-          sqlite3VdbeChangeP1(v, addr+3, j+2);
-          sqlite3VdbeChangeP2(v, addr+3, addr+2);
-          sqlite3VdbeJumpHere(v, addr+4);
-          sqlite3VdbeChangeP4(v, addr+6, 
-                     "wrong # of entries in index ", P4_STATIC);
-          sqlite3VdbeChangeP4(v, addr+7, pIdx->zName, P4_STATIC);
+        /* Verify CHECK constraints */
+        if( pTab->pCheck && (db->flags & SQLITE_IgnoreChecks)==0 ){
+          ExprList *pCheck = sqlite3ExprListDup(db, pTab->pCheck, 0);
+          if( db->mallocFailed==0 ){
+            int addrCkFault = sqlite3VdbeMakeLabel(v);
+            int addrCkOk = sqlite3VdbeMakeLabel(v);
+            char *zErr;
+            int k;
+            pParse->iSelfTab = iDataCur + 1;
+            sqlite3ExprCachePush(pParse);
+            for(k=pCheck->nExpr-1; k>0; k--){
+              sqlite3ExprIfFalse(pParse, pCheck->a[k].pExpr, addrCkFault, 0);
+            }
+            sqlite3ExprIfTrue(pParse, pCheck->a[0].pExpr, addrCkOk, 
+                SQLITE_JUMPIFNULL);
+            sqlite3VdbeResolveLabel(v, addrCkFault);
+            pParse->iSelfTab = 0;
+            zErr = sqlite3MPrintf(db, "CHECK constraint failed in %s",
+                pTab->zName);
+            sqlite3VdbeAddOp4(v, OP_String8, 0, 3, 0, zErr, P4_DYNAMIC);
+            integrityCheckResultRow(v);
+            sqlite3VdbeResolveLabel(v, addrCkOk);
+            sqlite3ExprCachePop(pParse);
+          }
+          sqlite3ExprListDelete(db, pCheck);
         }
+        if( !isQuick ){ /* Omit the remaining tests for quick_check */
+          /* Sanity check on record header decoding */
+          sqlite3VdbeAddOp3(v, OP_Column, iDataCur, pTab->nCol-1, 3);
+          sqlite3VdbeChangeP5(v, OPFLAG_TYPEOFARG);
+          /* Validate index entries for the current row */
+          for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
+            int jmp2, jmp3, jmp4, jmp5;
+            int ckUniq = sqlite3VdbeMakeLabel(v);
+            if( pPk==pIdx ) continue;
+            r1 = sqlite3GenerateIndexKey(pParse, pIdx, iDataCur, 0, 0, &jmp3,
+                                         pPrior, r1);
+            pPrior = pIdx;
+            sqlite3VdbeAddOp2(v, OP_AddImm, 8+j, 1);/* increment entry count */
+            /* Verify that an index entry exists for the current table row */
+            jmp2 = sqlite3VdbeAddOp4Int(v, OP_Found, iIdxCur+j, ckUniq, r1,
+                                        pIdx->nColumn); VdbeCoverage(v);
+            sqlite3VdbeLoadString(v, 3, "row ");
+            sqlite3VdbeAddOp3(v, OP_Concat, 7, 3, 3);
+            sqlite3VdbeLoadString(v, 4, " missing from index ");
+            sqlite3VdbeAddOp3(v, OP_Concat, 4, 3, 3);
+            jmp5 = sqlite3VdbeLoadString(v, 4, pIdx->zName);
+            sqlite3VdbeAddOp3(v, OP_Concat, 4, 3, 3);
+            jmp4 = integrityCheckResultRow(v);
+            sqlite3VdbeJumpHere(v, jmp2);
+            /* For UNIQUE indexes, verify that only one entry exists with the
+            ** current key.  The entry is unique if (1) any column is NULL
+            ** or (2) the next entry has a different key */
+            if( IsUniqueIndex(pIdx) ){
+              int uniqOk = sqlite3VdbeMakeLabel(v);
+              int jmp6;
+              int kk;
+              for(kk=0; kk<pIdx->nKeyCol; kk++){
+                int iCol = pIdx->aiColumn[kk];
+                assert( iCol!=XN_ROWID && iCol<pTab->nCol );
+                if( iCol>=0 && pTab->aCol[iCol].notNull ) continue;
+                sqlite3VdbeAddOp2(v, OP_IsNull, r1+kk, uniqOk);
+                VdbeCoverage(v);
+              }
+              jmp6 = sqlite3VdbeAddOp1(v, OP_Next, iIdxCur+j); VdbeCoverage(v);
+              sqlite3VdbeGoto(v, uniqOk);
+              sqlite3VdbeJumpHere(v, jmp6);
+              sqlite3VdbeAddOp4Int(v, OP_IdxGT, iIdxCur+j, uniqOk, r1,
+                                   pIdx->nKeyCol); VdbeCoverage(v);
+              sqlite3VdbeLoadString(v, 3, "non-unique entry in index ");
+              sqlite3VdbeGoto(v, jmp5);
+              sqlite3VdbeResolveLabel(v, uniqOk);
+            }
+            sqlite3VdbeJumpHere(v, jmp4);
+            sqlite3ResolvePartIdxLabel(pParse, jmp3);
+          }
+        }
+        sqlite3VdbeAddOp2(v, OP_Next, iDataCur, loopTop); VdbeCoverage(v);
+        sqlite3VdbeJumpHere(v, loopTop-1);
+#ifndef SQLITE_OMIT_BTREECOUNT
+        if( !isQuick ){
+          sqlite3VdbeLoadString(v, 2, "wrong # of entries in index ");
+          for(j=0, pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext, j++){
+            if( pPk==pIdx ) continue;
+            sqlite3VdbeAddOp2(v, OP_Count, iIdxCur+j, 3);
+            addr = sqlite3VdbeAddOp3(v, OP_Eq, 8+j, 0, 3); VdbeCoverage(v);
+            sqlite3VdbeChangeP5(v, SQLITE_NOTNULL);
+            sqlite3VdbeLoadString(v, 4, pIdx->zName);
+            sqlite3VdbeAddOp3(v, OP_Concat, 4, 2, 3);
+            integrityCheckResultRow(v);
+            sqlite3VdbeJumpHere(v, addr);
+          }
+        }
+#endif /* SQLITE_OMIT_BTREECOUNT */
       } 
     }
-    addr = sqlite3VdbeAddOpList(v, ArraySize(endCode), endCode);
-    sqlite3VdbeChangeP2(v, addr, -mxErr);
-    sqlite3VdbeJumpHere(v, addr+1);
-    sqlite3VdbeChangeP4(v, addr+2, "ok", P4_STATIC);
-  }else
+    {
+      static const int iLn = VDBE_OFFSET_LINENO(2);
+      static const VdbeOpList endCode[] = {
+        { OP_AddImm,      1, 0,        0},    /* 0 */
+        { OP_IfNotZero,   1, 4,        0},    /* 1 */
+        { OP_String8,     0, 3,        0},    /* 2 */
+        { OP_ResultRow,   3, 1,        0},    /* 3 */
+        { OP_Halt,        0, 0,        0},    /* 4 */
+        { OP_String8,     0, 3,        0},    /* 5 */
+        { OP_Goto,        0, 3,        0},    /* 6 */
+      };
+      VdbeOp *aOp;
+
+      aOp = sqlite3VdbeAddOpList(v, ArraySize(endCode), endCode, iLn);
+      if( aOp ){
+        aOp[0].p2 = 1-mxErr;
+        aOp[2].p4type = P4_STATIC;
+        aOp[2].p4.z = "ok";
+        aOp[5].p4type = P4_STATIC;
+        aOp[5].p4.z = (char*)sqlite3ErrStr(SQLITE_CORRUPT);
+      }
+      sqlite3VdbeChangeP3(v, 0, sqlite3VdbeCurrentAddr(v)-2);
+    }
+  }
+  break;
 #endif /* SQLITE_OMIT_INTEGRITY_CHECK */
 
 #ifndef SQLITE_OMIT_UTF16
   /*
   **   PRAGMA encoding
   **   PRAGMA encoding = "utf-8"|"utf-16"|"utf-16le"|"utf-16be"
