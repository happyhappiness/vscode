   const char *zFile,    /* Name of the shared library containing extension */
   const char *zProc,    /* Entry point.  Use "sqlite3_extension_init" if 0 */
   char **pzErrMsg       /* Put error message here if not 0 */
 ){
   sqlite3_vfs *pVfs = db->pVfs;
   void *handle;
-  int (*xInit)(sqlite3*,char**,const sqlite3_api_routines*);
+  sqlite3_loadext_entry xInit;
   char *zErrmsg = 0;
+  const char *zEntry;
+  char *zAltEntry = 0;
   void **aHandle;
-  const int nMsg = 300;
+  u64 nMsg = 300 + sqlite3Strlen30(zFile);
+  int ii;
+  int rc;
+
+  /* Shared library endings to try if zFile cannot be loaded as written */
+  static const char *azEndings[] = {
+#if SQLITE_OS_WIN
+     "dll"   
+#elif defined(__APPLE__)
+     "dylib"
+#else
+     "so"
+#endif
+  };
+
 
   if( pzErrMsg ) *pzErrMsg = 0;
 
   /* Ticket #1863.  To avoid a creating security problems for older
   ** applications that relink against newer versions of SQLite, the
   ** ability to run load_extension is turned off by default.  One
-  ** must call sqlite3_enable_load_extension() to turn on extension
-  ** loading.  Otherwise you get the following error.
+  ** must call either sqlite3_enable_load_extension(db) or
+  ** sqlite3_db_config(db, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, 0)
+  ** to turn on extension loading.
   */
   if( (db->flags & SQLITE_LoadExtension)==0 ){
     if( pzErrMsg ){
       *pzErrMsg = sqlite3_mprintf("not authorized");
     }
     return SQLITE_ERROR;
   }
 
-  if( zProc==0 ){
-    zProc = "sqlite3_extension_init";
-  }
+  zEntry = zProc ? zProc : "sqlite3_extension_init";
 
   handle = sqlite3OsDlOpen(pVfs, zFile);
+#if SQLITE_OS_UNIX || SQLITE_OS_WIN
+  for(ii=0; ii<ArraySize(azEndings) && handle==0; ii++){
+    char *zAltFile = sqlite3_mprintf("%s.%s", zFile, azEndings[ii]);
+    if( zAltFile==0 ) return SQLITE_NOMEM_BKPT;
+    handle = sqlite3OsDlOpen(pVfs, zAltFile);
+    sqlite3_free(zAltFile);
+  }
+#endif
   if( handle==0 ){
     if( pzErrMsg ){
-      zErrmsg = sqlite3StackAllocZero(db, nMsg);
+      *pzErrMsg = zErrmsg = sqlite3_malloc64(nMsg);
       if( zErrmsg ){
         sqlite3_snprintf(nMsg, zErrmsg, 
             "unable to open shared library [%s]", zFile);
         sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
-        *pzErrMsg = sqlite3DbStrDup(0, zErrmsg);
-        sqlite3StackFree(db, zErrmsg);
       }
     }
     return SQLITE_ERROR;
   }
-  xInit = (int(*)(sqlite3*,char**,const sqlite3_api_routines*))
-                   sqlite3OsDlSym(pVfs, handle, zProc);
+  xInit = (sqlite3_loadext_entry)sqlite3OsDlSym(pVfs, handle, zEntry);
+
+  /* If no entry point was specified and the default legacy
+  ** entry point name "sqlite3_extension_init" was not found, then
+  ** construct an entry point name "sqlite3_X_init" where the X is
+  ** replaced by the lowercase value of every ASCII alphabetic 
+  ** character in the filename after the last "/" upto the first ".",
+  ** and eliding the first three characters if they are "lib".  
+  ** Examples:
+  **
+  **    /usr/local/lib/libExample5.4.3.so ==>  sqlite3_example_init
+  **    C:/lib/mathfuncs.dll              ==>  sqlite3_mathfuncs_init
+  */
+  if( xInit==0 && zProc==0 ){
+    int iFile, iEntry, c;
+    int ncFile = sqlite3Strlen30(zFile);
+    zAltEntry = sqlite3_malloc64(ncFile+30);
+    if( zAltEntry==0 ){
+      sqlite3OsDlClose(pVfs, handle);
+      return SQLITE_NOMEM_BKPT;
+    }
+    memcpy(zAltEntry, "sqlite3_", 8);
+    for(iFile=ncFile-1; iFile>=0 && zFile[iFile]!='/'; iFile--){}
+    iFile++;
+    if( sqlite3_strnicmp(zFile+iFile, "lib", 3)==0 ) iFile += 3;
+    for(iEntry=8; (c = zFile[iFile])!=0 && c!='.'; iFile++){
+      if( sqlite3Isalpha(c) ){
+        zAltEntry[iEntry++] = (char)sqlite3UpperToLower[(unsigned)c];
+      }
+    }
+    memcpy(zAltEntry+iEntry, "_init", 6);
+    zEntry = zAltEntry;
+    xInit = (sqlite3_loadext_entry)sqlite3OsDlSym(pVfs, handle, zEntry);
+  }
   if( xInit==0 ){
     if( pzErrMsg ){
-      zErrmsg = sqlite3StackAllocZero(db, nMsg);
+      nMsg += sqlite3Strlen30(zEntry);
+      *pzErrMsg = zErrmsg = sqlite3_malloc64(nMsg);
       if( zErrmsg ){
         sqlite3_snprintf(nMsg, zErrmsg,
-            "no entry point [%s] in shared library [%s]", zProc,zFile);
+            "no entry point [%s] in shared library [%s]", zEntry, zFile);
         sqlite3OsDlError(pVfs, nMsg-1, zErrmsg);
-        *pzErrMsg = sqlite3DbStrDup(0, zErrmsg);
-        sqlite3StackFree(db, zErrmsg);
       }
-      sqlite3OsDlClose(pVfs, handle);
     }
+    sqlite3OsDlClose(pVfs, handle);
+    sqlite3_free(zAltEntry);
     return SQLITE_ERROR;
-  }else if( xInit(db, &zErrmsg, &sqlite3Apis) ){
+  }
+  sqlite3_free(zAltEntry);
+  rc = xInit(db, &zErrmsg, &sqlite3Apis);
+  if( rc ){
+    if( rc==SQLITE_OK_LOAD_PERMANENTLY ) return SQLITE_OK;
     if( pzErrMsg ){
       *pzErrMsg = sqlite3_mprintf("error during initialization: %s", zErrmsg);
     }
     sqlite3_free(zErrmsg);
     sqlite3OsDlClose(pVfs, handle);
     return SQLITE_ERROR;
   }
 
   /* Append the new shared library handle to the db->aExtension array. */
   aHandle = sqlite3DbMallocZero(db, sizeof(handle)*(db->nExtension+1));
   if( aHandle==0 ){
-    return SQLITE_NOMEM;
+    return SQLITE_NOMEM_BKPT;
   }
   if( db->nExtension>0 ){
     memcpy(aHandle, db->aExtension, sizeof(handle)*db->nExtension);
   }
   sqlite3DbFree(db, db->aExtension);
   db->aExtension = aHandle;
