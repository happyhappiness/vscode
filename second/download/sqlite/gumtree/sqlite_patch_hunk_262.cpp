     */
     iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
     sqlite3NestedParse(pParse,
       "UPDATE %Q.%s "
          "SET type='table', name=%Q, tbl_name=%Q, rootpage=0, sql=%Q "
        "WHERE rowid=#%d",
-      db->aDb[iDb].zName, SCHEMA_TABLE(iDb),
+      db->aDb[iDb].zDbSName, MASTER_NAME,
       pTab->zName,
       pTab->zName,
       zStmt,
       pParse->regRowid
     );
     sqlite3DbFree(db, zStmt);
     v = sqlite3GetVdbe(pParse);
     sqlite3ChangeCookie(pParse, iDb);
 
-    sqlite3VdbeAddOp2(v, OP_Expire, 0, 0);
-    zWhere = sqlite3MPrintf(db, "name='%q'", pTab->zName);
-    sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 1, 0, zWhere, P4_DYNAMIC);
-    sqlite3VdbeAddOp4(v, OP_VCreate, iDb, 0, 0, 
-                         pTab->zName, sqlite3Strlen30(pTab->zName) + 1);
+    sqlite3VdbeAddOp0(v, OP_Expire);
+    zWhere = sqlite3MPrintf(db, "name='%q' AND type='table'", pTab->zName);
+    sqlite3VdbeAddParseSchemaOp(v, iDb, zWhere);
+
+    iReg = ++pParse->nMem;
+    sqlite3VdbeLoadString(v, iReg, pTab->zName);
+    sqlite3VdbeAddOp2(v, OP_VCreate, iDb, iReg);
   }
 
   /* If we are rereading the sqlite_master table create the in-memory
-  ** record of the table. If the module has already been registered,
-  ** also call the xConnect method here.
-  */
+  ** record of the table. The xConnect() method is not called until
+  ** the first time the virtual table is used in an SQL statement. This
+  ** allows a schema that contains virtual tables to be loaded before
+  ** the required virtual table implementations are registered.  */
   else {
     Table *pOld;
     Schema *pSchema = pTab->pSchema;
     const char *zName = pTab->zName;
-    int nName = sqlite3Strlen30(zName);
-    pOld = sqlite3HashInsert(&pSchema->tblHash, zName, nName, pTab);
+    assert( sqlite3SchemaMutexHeld(db, 0, pSchema) );
+    pOld = sqlite3HashInsert(&pSchema->tblHash, zName, pTab);
     if( pOld ){
-      db->mallocFailed = 1;
+      sqlite3OomFault(db);
       assert( pTab==pOld );  /* Malloc must have failed inside HashInsert() */
       return;
     }
-    pSchema->db = pParse->db;
     pParse->pNewTable = 0;
   }
 }
 
 /*
 ** The parser calls this routine when it sees the first token
