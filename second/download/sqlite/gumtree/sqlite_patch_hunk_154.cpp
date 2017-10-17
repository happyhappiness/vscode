 
 #ifndef SQLITE_OMIT_TRIGGER
   /* Drop any table triggers from the internal schema. */
   for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
     int iTrigDb = sqlite3SchemaToIndex(pParse->db, pTrig->pSchema);
     assert( iTrigDb==iDb || iTrigDb==1 );
-    sqlite3VdbeAddOp4(v, OP_DropTrigger, iTrigDb, 0, 0, pTrig->name, 0);
+    sqlite3VdbeAddOp4(v, OP_DropTrigger, iTrigDb, 0, 0, pTrig->zName, 0);
   }
 #endif
 
-  /* Drop the table and index from the internal schema */
+  /* Drop the table and index from the internal schema.  */
   sqlite3VdbeAddOp4(v, OP_DropTable, iDb, 0, 0, pTab->zName, 0);
 
   /* Reload the table, index and permanent trigger schemas. */
   zWhere = sqlite3MPrintf(pParse->db, "tbl_name=%Q", zName);
   if( !zWhere ) return;
-  sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0, zWhere, P4_DYNAMIC);
+  sqlite3VdbeAddParseSchemaOp(v, iDb, zWhere);
 
 #ifndef SQLITE_OMIT_TRIGGER
   /* Now, if the table is not stored in the temp database, reload any temp 
   ** triggers. Don't use IN(...) in case SQLITE_OMIT_SUBQUERY is defined. 
   */
   if( (zWhere=whereTempTriggers(pParse, pTab))!=0 ){
-    sqlite3VdbeAddOp4(v, OP_ParseSchema, 1, 0, 0, zWhere, P4_DYNAMIC);
+    sqlite3VdbeAddParseSchemaOp(v, 1, zWhere);
   }
 #endif
 }
 
 /*
+** Parameter zName is the name of a table that is about to be altered
+** (either with ALTER TABLE ... RENAME TO or ALTER TABLE ... ADD COLUMN).
+** If the table is a system table, this function leaves an error message
+** in pParse->zErr (system tables may not be altered) and returns non-zero.
+**
+** Or, if zName is not a system table, zero is returned.
+*/
+static int isSystemTable(Parse *pParse, const char *zName){
+  if( 0==sqlite3StrNICmp(zName, "sqlite_", 7) ){
+    sqlite3ErrorMsg(pParse, "table %s may not be altered", zName);
+    return 1;
+  }
+  return 0;
+}
+
+/*
 ** Generate code to implement the "ALTER TABLE xxx RENAME TO yyy" 
 ** command. 
 */
 void sqlite3AlterRenameTable(
   Parse *pParse,            /* Parser context. */
   SrcList *pSrc,            /* The table to rename. */
