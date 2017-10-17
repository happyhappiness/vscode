     ** the constraint occur in different orders, then the constraints are
     ** considered distinct and both result in separate indices.
     */
     Index *pIdx;
     for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
       int k;
-      assert( IsUniqueIndex(pIdx) );
-      assert( pIdx->idxType!=SQLITE_IDXTYPE_APPDEF );
-      assert( IsUniqueIndex(pIndex) );
+      assert( pIdx->onError!=OE_None );
+      assert( pIdx->autoIndex );
+      assert( pIndex->onError!=OE_None );
 
-      if( pIdx->nKeyCol!=pIndex->nKeyCol ) continue;
-      for(k=0; k<pIdx->nKeyCol; k++){
+      if( pIdx->nColumn!=pIndex->nColumn ) continue;
+      for(k=0; k<pIdx->nColumn; k++){
         const char *z1;
         const char *z2;
-        assert( pIdx->aiColumn[k]>=0 );
         if( pIdx->aiColumn[k]!=pIndex->aiColumn[k] ) break;
         z1 = pIdx->azColl[k];
         z2 = pIndex->azColl[k];
-        if( sqlite3StrICmp(z1, z2) ) break;
+        if( z1!=z2 && sqlite3StrICmp(z1, z2) ) break;
       }
-      if( k==pIdx->nKeyCol ){
+      if( k==pIdx->nColumn ){
         if( pIdx->onError!=pIndex->onError ){
           /* This constraint creates the same index as a previous
           ** constraint specified somewhere in the CREATE TABLE statement.
           ** However the ON CONFLICT clauses are different. If both this 
           ** constraint and the previous equivalent constraint have explicit
           ** ON CONFLICT clauses this is an error. Otherwise, use the
-          ** explicitly specified behavior for the index.
+          ** explicitly specified behaviour for the index.
           */
           if( !(pIdx->onError==OE_Default || pIndex->onError==OE_Default) ){
             sqlite3ErrorMsg(pParse, 
                 "conflicting ON CONFLICT clauses specified", 0);
           }
           if( pIdx->onError==OE_Default ){
             pIdx->onError = pIndex->onError;
           }
         }
-        if( idxType==SQLITE_IDXTYPE_PRIMARYKEY ) pIdx->idxType = idxType;
         goto exit_create_index;
       }
     }
   }
 
   /* Link the new Index structure to its table and to the other
   ** in-memory database structures. 
   */
-  assert( pParse->nErr==0 );
   if( db->init.busy ){
     Index *p;
-    assert( !IN_DECLARE_VTAB );
-    assert( sqlite3SchemaMutexHeld(db, 0, pIndex->pSchema) );
     p = sqlite3HashInsert(&pIndex->pSchema->idxHash, 
-                          pIndex->zName, pIndex);
+                          pIndex->zName, sqlite3Strlen30(pIndex->zName),
+                          pIndex);
     if( p ){
       assert( p==pIndex );  /* Malloc must have failed */
-      sqlite3OomFault(db);
+      db->mallocFailed = 1;
       goto exit_create_index;
     }
-    db->mDbFlags |= DBFLAG_SchemaChange;
+    db->flags |= SQLITE_InternChanges;
     if( pTblName!=0 ){
       pIndex->tnum = db->init.newTnum;
     }
   }
 
-  /* If this is the initial CREATE INDEX statement (or CREATE TABLE if the
-  ** index is an implied index for a UNIQUE or PRIMARY KEY constraint) then
-  ** emit code to allocate the index rootpage on disk and make an entry for
-  ** the index in the sqlite_master table and populate the index with
-  ** content.  But, do not do this if we are simply reading the sqlite_master
-  ** table to parse the schema, or if this index is the PRIMARY KEY index
-  ** of a WITHOUT ROWID table.
+  /* If the db->init.busy is 0 then create the index on disk.  This
+  ** involves writing the index into the master table and filling in the
+  ** index with the current table contents.
   **
-  ** If pTblName==0 it means this index is generated as an implied PRIMARY KEY
-  ** or UNIQUE index in a CREATE TABLE statement.  Since the table
+  ** The db->init.busy is 0 when the user first enters a CREATE INDEX 
+  ** command.  db->init.busy is 1 when a database is opened and 
+  ** CREATE INDEX statements are read out of the master table.  In
+  ** the latter case the index already exists on disk, which is why
+  ** we don't want to recreate it.
+  **
+  ** If pTblName==0 it means this index is generated as a primary key
+  ** or UNIQUE constraint of a CREATE TABLE statement.  Since the table
   ** has just been created, it contains no data and the index initialization
   ** step can be skipped.
   */
-  else if( HasRowid(pTab) || pTblName!=0 ){
+  else{ /* if( db->init.busy==0 ) */
     Vdbe *v;
     char *zStmt;
     int iMem = ++pParse->nMem;
 
     v = sqlite3GetVdbe(pParse);
     if( v==0 ) goto exit_create_index;
 
-    sqlite3BeginWriteOperation(pParse, 1, iDb);
 
-    /* Create the rootpage for the index using CreateIndex. But before
-    ** doing so, code a Noop instruction and store its address in 
-    ** Index.tnum. This is required in case this index is actually a 
-    ** PRIMARY KEY and the table is actually a WITHOUT ROWID table. In 
-    ** that case the convertToWithoutRowidTable() routine will replace
-    ** the Noop with a Goto to jump over the VDBE code generated below. */
-    pIndex->tnum = sqlite3VdbeAddOp0(v, OP_Noop);
-    sqlite3VdbeAddOp3(v, OP_CreateBtree, iDb, iMem, BTREE_BLOBKEY);
+    /* Create the rootpage for the index
+    */
+    sqlite3BeginWriteOperation(pParse, 1, iDb);
+    sqlite3VdbeAddOp2(v, OP_CreateIndex, iDb, iMem);
 
     /* Gather the complete text of the CREATE INDEX statement into
     ** the zStmt variable
     */
     if( pStart ){
-      int n = (int)(pParse->sLastToken.z - pName->z) + pParse->sLastToken.n;
-      if( pName->z[n-1]==';' ) n--;
+      assert( pEnd!=0 );
       /* A named index with an explicit CREATE INDEX statement */
       zStmt = sqlite3MPrintf(db, "CREATE%s INDEX %.*s",
-        onError==OE_None ? "" : " UNIQUE", n, pName->z);
+        onError==OE_None ? "" : " UNIQUE",
+        pEnd->z - pName->z + 1,
+        pName->z);
     }else{
       /* An automatic index created by a PRIMARY KEY or UNIQUE constraint */
       /* zStmt = sqlite3MPrintf(""); */
       zStmt = 0;
     }
 
     /* Add an entry in sqlite_master for this index
     */
     sqlite3NestedParse(pParse, 
         "INSERT INTO %Q.%s VALUES('index',%Q,%Q,#%d,%Q);",
-        db->aDb[iDb].zDbSName, MASTER_NAME,
+        db->aDb[iDb].zName, SCHEMA_TABLE(iDb),
         pIndex->zName,
         pTab->zName,
         iMem,
         zStmt
     );
     sqlite3DbFree(db, zStmt);
