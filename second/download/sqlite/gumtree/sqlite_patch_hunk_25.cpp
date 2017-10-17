   UNUSED_PARAMETER(NotUsed);
 
   if( zName==0 ) zName = "";
   for(i=0; i<db->nDb; i++){
     pDb = &db->aDb[i];
     if( pDb->pBt==0 ) continue;
-    if( sqlite3StrICmp(pDb->zDbSName, zName)==0 ) break;
+    if( sqlite3StrICmp(pDb->zName, zName)==0 ) break;
   }
 
   if( i>=db->nDb ){
     sqlite3_snprintf(sizeof(zErr),zErr, "no such database: %s", zName);
     goto detach_error;
   }
   if( i<2 ){
     sqlite3_snprintf(sizeof(zErr),zErr, "cannot detach database %s", zName);
     goto detach_error;
   }
+  if( !db->autoCommit ){
+    sqlite3_snprintf(sizeof(zErr), zErr,
+                     "cannot DETACH database within transaction");
+    goto detach_error;
+  }
   if( sqlite3BtreeIsInReadTrans(pDb->pBt) || sqlite3BtreeIsInBackup(pDb->pBt) ){
     sqlite3_snprintf(sizeof(zErr),zErr, "database %s is locked", zName);
     goto detach_error;
   }
 
   sqlite3BtreeClose(pDb->pBt);
   pDb->pBt = 0;
   pDb->pSchema = 0;
-  sqlite3CollapseDatabaseArray(db);
+  sqlite3ResetInternalSchema(db, 0);
   return;
 
 detach_error:
   sqlite3_result_error(context, zErr, -1);
 }
 
