     sqlite3ChangeCookie(pParse, iDb);
 
 #ifndef SQLITE_OMIT_AUTOINCREMENT
     /* Check to see if we need to create an sqlite_sequence table for
     ** keeping track of autoincrement keys.
     */
-    if( (p->tabFlags & TF_Autoincrement)!=0 ){
+    if( p->tabFlags & TF_Autoincrement ){
       Db *pDb = &db->aDb[iDb];
-      assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
       if( pDb->pSchema->pSeqTab==0 ){
         sqlite3NestedParse(pParse,
           "CREATE TABLE %Q.sqlite_sequence(name,seq)",
-          pDb->zDbSName
+          pDb->zName
         );
       }
     }
 #endif
 
     /* Reparse everything to update our internal data structures */
-    sqlite3VdbeAddParseSchemaOp(v, iDb,
-           sqlite3MPrintf(db, "tbl_name='%q' AND type!='trigger'", p->zName));
+    sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0,
+        sqlite3MPrintf(db, "tbl_name='%q'",p->zName), P4_DYNAMIC);
   }
 
 
   /* Add the table to the in-memory representation of the database.
   */
   if( db->init.busy ){
     Table *pOld;
     Schema *pSchema = p->pSchema;
-    assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
-    pOld = sqlite3HashInsert(&pSchema->tblHash, p->zName, p);
+    pOld = sqlite3HashInsert(&pSchema->tblHash, p->zName,
+                             sqlite3Strlen30(p->zName),p);
     if( pOld ){
       assert( p==pOld );  /* Malloc must have failed inside HashInsert() */
-      sqlite3OomFault(db);
+      db->mallocFailed = 1;
       return;
     }
     pParse->pNewTable = 0;
-    db->mDbFlags |= DBFLAG_SchemaChange;
+    db->nTable++;
+    db->flags |= SQLITE_InternChanges;
 
 #ifndef SQLITE_OMIT_ALTERTABLE
     if( !p->pSelect ){
       const char *zName = (const char *)pParse->sNameToken.z;
       int nName;
       assert( !pSelect && pCons && pEnd );
