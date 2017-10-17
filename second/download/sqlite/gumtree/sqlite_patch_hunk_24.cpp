         break;
         
       case SQLITE_TEXT:
       case SQLITE_BLOB:
         nKey = sqlite3_value_bytes(argv[2]);
         zKey = (char *)sqlite3_value_blob(argv[2]);
-        rc = sqlite3CodecAttach(db, db->nDb-1, zKey, nKey);
+        sqlite3CodecAttach(db, db->nDb-1, zKey, nKey);
         break;
 
       case SQLITE_NULL:
         /* No key specified.  Use the key from the main database */
         sqlite3CodecGetKey(db, 0, (void**)&zKey, &nKey);
-        if( nKey || sqlite3BtreeGetOptimalReserve(db->aDb[0].pBt)>0 ){
-          rc = sqlite3CodecAttach(db, db->nDb-1, zKey, nKey);
-        }
+        sqlite3CodecAttach(db, db->nDb-1, zKey, nKey);
         break;
     }
   }
 #endif
 
   /* If the file was opened successfully, read the schema for the new database.
   ** If this fails, or if opening the file failed, then close the file and 
   ** remove the entry from the db->aDb[] array. i.e. put everything back the way
   ** we found it.
   */
   if( rc==SQLITE_OK ){
+    (void)sqlite3SafetyOn(db);
     sqlite3BtreeEnterAll(db);
     rc = sqlite3Init(db, &zErrDyn);
     sqlite3BtreeLeaveAll(db);
+    (void)sqlite3SafetyOff(db);
   }
-#ifdef SQLITE_USER_AUTHENTICATION
-  if( rc==SQLITE_OK ){
-    u8 newAuth = 0;
-    rc = sqlite3UserAuthCheckLogin(db, zName, &newAuth);
-    if( newAuth<db->auth.authLevel ){
-      rc = SQLITE_AUTH_USER;
-    }
-  }
-#endif
   if( rc ){
     int iDb = db->nDb - 1;
     assert( iDb>=2 );
     if( db->aDb[iDb].pBt ){
       sqlite3BtreeClose(db->aDb[iDb].pBt);
       db->aDb[iDb].pBt = 0;
       db->aDb[iDb].pSchema = 0;
     }
-    sqlite3ResetAllSchemasOfConnection(db);
+    sqlite3ResetInternalSchema(db, 0);
     db->nDb = iDb;
     if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ){
-      sqlite3OomFault(db);
+      db->mallocFailed = 1;
       sqlite3DbFree(db, zErrDyn);
       zErrDyn = sqlite3MPrintf(db, "out of memory");
     }else if( zErrDyn==0 ){
       zErrDyn = sqlite3MPrintf(db, "unable to open database: %s", zFile);
     }
     goto attach_error;
