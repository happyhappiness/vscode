     ** A shared-cache write-lock is not required to write to the new table,
     ** as a schema-lock must have already been obtained to create it. Since
     ** a schema-lock excludes all other database users, the write-lock would
     ** be redundant.
     */
     if( pSelect ){
-      SelectDest dest;
-      Table *pSelTab;
-
+      SelectDest dest;    /* Where the SELECT should store results */
+      int regYield;       /* Register holding co-routine entry-point */
+      int addrTop;        /* Top of the co-routine */
+      int regRec;         /* A record to be insert into the new table */
+      int regRowid;       /* Rowid of the next row to insert */
+      int addrInsLoop;    /* Top of the loop for inserting rows */
+      Table *pSelTab;     /* A table that describes the SELECT results */
+
+      regYield = ++pParse->nMem;
+      regRec = ++pParse->nMem;
+      regRowid = ++pParse->nMem;
       assert(pParse->nTab==1);
+      sqlite3MayAbort(pParse);
       sqlite3VdbeAddOp3(v, OP_OpenWrite, 1, pParse->regRoot, iDb);
-      sqlite3VdbeChangeP5(v, 1);
+      sqlite3VdbeChangeP5(v, OPFLAG_P2ISREG);
       pParse->nTab = 2;
-      sqlite3SelectDestInit(&dest, SRT_Table, 1);
+      addrTop = sqlite3VdbeCurrentAddr(v) + 1;
+      sqlite3VdbeAddOp3(v, OP_InitCoroutine, regYield, 0, addrTop);
+      sqlite3SelectDestInit(&dest, SRT_Coroutine, regYield);
       sqlite3Select(pParse, pSelect, &dest);
+      sqlite3VdbeEndCoroutine(v, regYield);
+      sqlite3VdbeJumpHere(v, addrTop - 1);
+      if( pParse->nErr ) return;
+      pSelTab = sqlite3ResultSetOfSelect(pParse, pSelect);
+      if( pSelTab==0 ) return;
+      assert( p->aCol==0 );
+      p->nCol = pSelTab->nCol;
+      p->aCol = pSelTab->aCol;
+      pSelTab->nCol = 0;
+      pSelTab->aCol = 0;
+      sqlite3DeleteTable(db, pSelTab);
+      addrInsLoop = sqlite3VdbeAddOp1(v, OP_Yield, dest.iSDParm);
+      VdbeCoverage(v);
+      sqlite3VdbeAddOp3(v, OP_MakeRecord, dest.iSdst, dest.nSdst, regRec);
+      sqlite3TableAffinity(v, p, 0);
+      sqlite3VdbeAddOp2(v, OP_NewRowid, 1, regRowid);
+      sqlite3VdbeAddOp3(v, OP_Insert, 1, regRec, regRowid);
+      sqlite3VdbeGoto(v, addrInsLoop);
+      sqlite3VdbeJumpHere(v, addrInsLoop);
       sqlite3VdbeAddOp1(v, OP_Close, 1);
-      if( pParse->nErr==0 ){
-        pSelTab = sqlite3ResultSetOfSelect(pParse, pSelect);
-        if( pSelTab==0 ) return;
-        assert( p->aCol==0 );
-        p->nCol = pSelTab->nCol;
-        p->aCol = pSelTab->aCol;
-        pSelTab->nCol = 0;
-        pSelTab->aCol = 0;
-        sqlite3DeleteTable(pSelTab);
-      }
     }
 
     /* Compute the complete text of the CREATE statement */
     if( pSelect ){
       zStmt = createTableStmt(db, p);
     }else{
-      n = (int)(pEnd->z - pParse->sNameToken.z) + 1;
+      Token *pEnd2 = tabOpts ? &pParse->sLastToken : pEnd;
+      n = (int)(pEnd2->z - pParse->sNameToken.z);
+      if( pEnd2->z[0]!=';' ) n += pEnd2->n;
       zStmt = sqlite3MPrintf(db, 
           "CREATE %s %.*s", zType2, n, pParse->sNameToken.z
       );
     }
 
     /* A slot for the record has already been allocated in the 
