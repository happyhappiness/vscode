       }
     } while( dist!=2 || (token!=TK_WHEN && token!=TK_FOR && token!=TK_BEGIN) );
 
     /* Variable tname now contains the token that is the old table-name
     ** in the CREATE TRIGGER statement.
     */
-    zRet = sqlite3MPrintf(db, "%.*s\"%w\"%s", (int)(((u8*)tname.z) - zSql),
-       zSql, zTableName, tname.z+tname.n);
+    zRet = sqlite3MPrintf(db, "%.*s\"%w\"%s", ((u8*)tname.z) - zSql, zSql, 
+       zTableName, tname.z+tname.n);
     sqlite3_result_text(context, zRet, -1, SQLITE_DYNAMIC);
   }
 }
 #endif   /* !SQLITE_OMIT_TRIGGER */
 
 /*
 ** Register built-in functions used to help implement ALTER TABLE
 */
-void sqlite3AlterFunctions(void){
-  static FuncDef aAlterTableFuncs[] = {
-    FUNCTION(sqlite_rename_table,   2, 0, 0, renameTableFunc),
+void sqlite3AlterFunctions(sqlite3 *db){
+  sqlite3CreateFunc(db, "sqlite_rename_table", 2, SQLITE_UTF8, 0,
+                         renameTableFunc, 0, 0);
 #ifndef SQLITE_OMIT_TRIGGER
-    FUNCTION(sqlite_rename_trigger, 2, 0, 0, renameTriggerFunc),
-#endif
-#ifndef SQLITE_OMIT_FOREIGN_KEY
-    FUNCTION(sqlite_rename_parent,  3, 0, 0, renameParentFunc),
+  sqlite3CreateFunc(db, "sqlite_rename_trigger", 2, SQLITE_UTF8, 0,
+                         renameTriggerFunc, 0, 0);
 #endif
-  };
-  sqlite3InsertBuiltinFuncs(aAlterTableFuncs, ArraySize(aAlterTableFuncs));
 }
 
 /*
-** This function is used to create the text of expressions of the form:
-**
-**   name=<constant1> OR name=<constant2> OR ...
-**
-** If argument zWhere is NULL, then a pointer string containing the text 
-** "name=<constant>" is returned, where <constant> is the quoted version
-** of the string passed as argument zConstant. The returned buffer is
-** allocated using sqlite3DbMalloc(). It is the responsibility of the
-** caller to ensure that it is eventually freed.
-**
-** If argument zWhere is not NULL, then the string returned is 
-** "<where> OR name=<constant>", where <where> is the contents of zWhere.
-** In this case zWhere is passed to sqlite3DbFree() before returning.
-** 
-*/
-static char *whereOrName(sqlite3 *db, char *zWhere, char *zConstant){
-  char *zNew;
-  if( !zWhere ){
-    zNew = sqlite3MPrintf(db, "name=%Q", zConstant);
-  }else{
-    zNew = sqlite3MPrintf(db, "%s OR name=%Q", zWhere, zConstant);
-    sqlite3DbFree(db, zWhere);
-  }
-  return zNew;
-}
-
-#if !defined(SQLITE_OMIT_FOREIGN_KEY) && !defined(SQLITE_OMIT_TRIGGER)
-/*
-** Generate the text of a WHERE expression which can be used to select all
-** tables that have foreign key constraints that refer to table pTab (i.e.
-** constraints for which pTab is the parent table) from the sqlite_master
-** table.
-*/
-static char *whereForeignKeys(Parse *pParse, Table *pTab){
-  FKey *p;
-  char *zWhere = 0;
-  for(p=sqlite3FkReferences(pTab); p; p=p->pNextTo){
-    zWhere = whereOrName(pParse->db, zWhere, p->pFrom->zName);
-  }
-  return zWhere;
-}
-#endif
-
-/*
 ** Generate the text of a WHERE expression which can be used to select all
 ** temporary triggers on table pTab from the sqlite_temp_master table. If
 ** table pTab has no temporary triggers, or is itself stored in the 
 ** temporary database, NULL is returned.
 */
 static char *whereTempTriggers(Parse *pParse, Table *pTab){
   Trigger *pTrig;
   char *zWhere = 0;
+  char *tmp = 0;
   const Schema *pTempSchema = pParse->db->aDb[1].pSchema; /* Temp db schema */
 
   /* If the table is not located in the temp-db (in which case NULL is 
   ** returned, loop through the tables list of triggers. For each trigger
   ** that is not part of the temp-db schema, add a clause to the WHERE 
   ** expression being built up in zWhere.
   */
   if( pTab->pSchema!=pTempSchema ){
     sqlite3 *db = pParse->db;
     for(pTrig=sqlite3TriggerList(pParse, pTab); pTrig; pTrig=pTrig->pNext){
       if( pTrig->pSchema==pTempSchema ){
-        zWhere = whereOrName(db, zWhere, pTrig->zName);
+        if( !zWhere ){
+          zWhere = sqlite3MPrintf(db, "name=%Q", pTrig->name);
+        }else{
+          tmp = zWhere;
+          zWhere = sqlite3MPrintf(db, "%s OR name=%Q", zWhere, pTrig->name);
+          sqlite3DbFree(db, tmp);
+        }
       }
     }
   }
-  if( zWhere ){
-    char *zNew = sqlite3MPrintf(pParse->db, "type='trigger' AND (%s)", zWhere);
-    sqlite3DbFree(pParse->db, zWhere);
-    zWhere = zNew;
-  }
   return zWhere;
 }
 
 /*
 ** Generate code to drop and reload the internal representation of table
 ** pTab from the database, including triggers and temporary triggers.
