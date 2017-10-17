 static void corruptSchema(
   InitData *pData,     /* Initialization context */
   const char *zObj,    /* Object being parsed at the point of error */
   const char *zExtra   /* Error information */
 ){
   sqlite3 *db = pData->db;
-  if( !db->mallocFailed && (db->flags & SQLITE_RecoveryMode)==0 ){
+  if( !db->mallocFailed && (db->flags & SQLITE_WriteSchema)==0 ){
+    char *z;
     if( zObj==0 ) zObj = "?";
-    sqlite3SetString(pData->pzErrMsg, pData->db,
-       "malformed database schema (%s)", zObj);
-    if( zExtra && zExtra[0] ){
-      *pData->pzErrMsg = sqlite3MAppendf(pData->db, *pData->pzErrMsg, "%s - %s",
-                                  *pData->pzErrMsg, zExtra);
-    }
+    z = sqlite3MPrintf(db, "malformed database schema (%s)", zObj);
+    if( zExtra ) z = sqlite3MPrintf(db, "%z - %s", z, zExtra);
+    sqlite3DbFree(db, *pData->pzErrMsg);
+    *pData->pzErrMsg = z;
   }
-  pData->rc = SQLITE_CORRUPT;
+  pData->rc = db->mallocFailed ? SQLITE_NOMEM_BKPT : SQLITE_CORRUPT_BKPT;
 }
 
 /*
 ** This is the callback routine for the code that initializes the
 ** database.  See sqlite3Init() below for additional information.
 ** This routine is also called from the OP_ParseSchema opcode of the VDBE.
