 ** A new lower limit does not shrink existing constructs.
 ** It merely prevents new constructs that exceed the limit
 ** from forming.
 */
 int sqlite3_limit(sqlite3 *db, int limitId, int newLimit){
   int oldLimit;
+
+#ifdef SQLITE_ENABLE_API_ARMOR
+  if( !sqlite3SafetyCheckOk(db) ){
+    (void)SQLITE_MISUSE_BKPT;
+    return -1;
+  }
+#endif
+
+  /* EVIDENCE-OF: R-30189-54097 For each limit category SQLITE_LIMIT_NAME
+  ** there is a hard upper bound set at compile-time by a C preprocessor
+  ** macro called SQLITE_MAX_NAME. (The "_LIMIT_" in the name is changed to
+  ** "_MAX_".)
+  */
+  assert( aHardLimit[SQLITE_LIMIT_LENGTH]==SQLITE_MAX_LENGTH );
+  assert( aHardLimit[SQLITE_LIMIT_SQL_LENGTH]==SQLITE_MAX_SQL_LENGTH );
+  assert( aHardLimit[SQLITE_LIMIT_COLUMN]==SQLITE_MAX_COLUMN );
+  assert( aHardLimit[SQLITE_LIMIT_EXPR_DEPTH]==SQLITE_MAX_EXPR_DEPTH );
+  assert( aHardLimit[SQLITE_LIMIT_COMPOUND_SELECT]==SQLITE_MAX_COMPOUND_SELECT);
+  assert( aHardLimit[SQLITE_LIMIT_VDBE_OP]==SQLITE_MAX_VDBE_OP );
+  assert( aHardLimit[SQLITE_LIMIT_FUNCTION_ARG]==SQLITE_MAX_FUNCTION_ARG );
+  assert( aHardLimit[SQLITE_LIMIT_ATTACHED]==SQLITE_MAX_ATTACHED );
+  assert( aHardLimit[SQLITE_LIMIT_LIKE_PATTERN_LENGTH]==
+                                               SQLITE_MAX_LIKE_PATTERN_LENGTH );
+  assert( aHardLimit[SQLITE_LIMIT_VARIABLE_NUMBER]==SQLITE_MAX_VARIABLE_NUMBER);
+  assert( aHardLimit[SQLITE_LIMIT_TRIGGER_DEPTH]==SQLITE_MAX_TRIGGER_DEPTH );
+  assert( aHardLimit[SQLITE_LIMIT_WORKER_THREADS]==SQLITE_MAX_WORKER_THREADS );
+  assert( SQLITE_LIMIT_WORKER_THREADS==(SQLITE_N_LIMIT-1) );
+
+
   if( limitId<0 || limitId>=SQLITE_N_LIMIT ){
     return -1;
   }
   oldLimit = db->aLimit[limitId];
-  if( newLimit>=0 ){
+  if( newLimit>=0 ){                   /* IMP: R-52476-28732 */
     if( newLimit>aHardLimit[limitId] ){
-      newLimit = aHardLimit[limitId];
+      newLimit = aHardLimit[limitId];  /* IMP: R-51463-25634 */
     }
     db->aLimit[limitId] = newLimit;
   }
-  return oldLimit;
+  return oldLimit;                     /* IMP: R-53341-35419 */
+}
+
+/*
+** This function is used to parse both URIs and non-URI filenames passed by the
+** user to API functions sqlite3_open() or sqlite3_open_v2(), and for database
+** URIs specified as part of ATTACH statements.
+**
+** The first argument to this function is the name of the VFS to use (or
+** a NULL to signify the default VFS) if the URI does not contain a "vfs=xxx"
+** query parameter. The second argument contains the URI (or non-URI filename)
+** itself. When this function is called the *pFlags variable should contain
+** the default flags to open the database handle with. The value stored in
+** *pFlags may be updated before returning if the URI filename contains 
+** "cache=xxx" or "mode=xxx" query parameters.
+**
+** If successful, SQLITE_OK is returned. In this case *ppVfs is set to point to
+** the VFS that should be used to open the database file. *pzFile is set to
+** point to a buffer containing the name of the file to open. It is the 
+** responsibility of the caller to eventually call sqlite3_free() to release
+** this buffer.
+**
+** If an error occurs, then an SQLite error code is returned and *pzErrMsg
+** may be set to point to a buffer containing an English language error 
+** message. It is the responsibility of the caller to eventually release
+** this buffer by calling sqlite3_free().
+*/
+int sqlite3ParseUri(
+  const char *zDefaultVfs,        /* VFS to use if no "vfs=xxx" query option */
+  const char *zUri,               /* Nul-terminated URI to parse */
+  unsigned int *pFlags,           /* IN/OUT: SQLITE_OPEN_XXX flags */
+  sqlite3_vfs **ppVfs,            /* OUT: VFS to use */ 
+  char **pzFile,                  /* OUT: Filename component of URI */
+  char **pzErrMsg                 /* OUT: Error message (if rc!=SQLITE_OK) */
+){
+  int rc = SQLITE_OK;
+  unsigned int flags = *pFlags;
+  const char *zVfs = zDefaultVfs;
+  char *zFile;
+  char c;
+  int nUri = sqlite3Strlen30(zUri);
+
+  assert( *pzErrMsg==0 );
+
+  if( ((flags & SQLITE_OPEN_URI)             /* IMP: R-48725-32206 */
+            || sqlite3GlobalConfig.bOpenUri) /* IMP: R-51689-46548 */
+   && nUri>=5 && memcmp(zUri, "file:", 5)==0 /* IMP: R-57884-37496 */
+  ){
+    char *zOpt;
+    int eState;                   /* Parser state when parsing URI */
+    int iIn;                      /* Input character index */
+    int iOut = 0;                 /* Output character index */
+    u64 nByte = nUri+2;           /* Bytes of space to allocate */
+
+    /* Make sure the SQLITE_OPEN_URI flag is set to indicate to the VFS xOpen 
+    ** method that there may be extra parameters following the file-name.  */
+    flags |= SQLITE_OPEN_URI;
+
+    for(iIn=0; iIn<nUri; iIn++) nByte += (zUri[iIn]=='&');
+    zFile = sqlite3_malloc64(nByte);
+    if( !zFile ) return SQLITE_NOMEM_BKPT;
+
+    iIn = 5;
+#ifdef SQLITE_ALLOW_URI_AUTHORITY
+    if( strncmp(zUri+5, "///", 3)==0 ){
+      iIn = 7;
+      /* The following condition causes URIs with five leading / characters
+      ** like file://///host/path to be converted into UNCs like //host/path.
+      ** The correct URI for that UNC has only two or four leading / characters
+      ** file://host/path or file:////host/path.  But 5 leading slashes is a 
+      ** common error, we are told, so we handle it as a special case. */
+      if( strncmp(zUri+7, "///", 3)==0 ){ iIn++; }
+    }else if( strncmp(zUri+5, "//localhost/", 12)==0 ){
+      iIn = 16;
+    }
+#else
+    /* Discard the scheme and authority segments of the URI. */
+    if( zUri[5]=='/' && zUri[6]=='/' ){
+      iIn = 7;
+      while( zUri[iIn] && zUri[iIn]!='/' ) iIn++;
+      if( iIn!=7 && (iIn!=16 || memcmp("localhost", &zUri[7], 9)) ){
+        *pzErrMsg = sqlite3_mprintf("invalid uri authority: %.*s", 
+            iIn-7, &zUri[7]);
+        rc = SQLITE_ERROR;
+        goto parse_uri_out;
+      }
+    }
+#endif
+
+    /* Copy the filename and any query parameters into the zFile buffer. 
+    ** Decode %HH escape codes along the way. 
+    **
+    ** Within this loop, variable eState may be set to 0, 1 or 2, depending
+    ** on the parsing context. As follows:
+    **
+    **   0: Parsing file-name.
+    **   1: Parsing name section of a name=value query parameter.
+    **   2: Parsing value section of a name=value query parameter.
+    */
+    eState = 0;
+    while( (c = zUri[iIn])!=0 && c!='#' ){
+      iIn++;
+      if( c=='%' 
+       && sqlite3Isxdigit(zUri[iIn]) 
+       && sqlite3Isxdigit(zUri[iIn+1]) 
+      ){
+        int octet = (sqlite3HexToInt(zUri[iIn++]) << 4);
+        octet += sqlite3HexToInt(zUri[iIn++]);
+
+        assert( octet>=0 && octet<256 );
+        if( octet==0 ){
+#ifndef SQLITE_ENABLE_URI_00_ERROR
+          /* This branch is taken when "%00" appears within the URI. In this
+          ** case we ignore all text in the remainder of the path, name or
+          ** value currently being parsed. So ignore the current character
+          ** and skip to the next "?", "=" or "&", as appropriate. */
+          while( (c = zUri[iIn])!=0 && c!='#' 
+              && (eState!=0 || c!='?')
+              && (eState!=1 || (c!='=' && c!='&'))
+              && (eState!=2 || c!='&')
+          ){
+            iIn++;
+          }
+          continue;
+#else
+          /* If ENABLE_URI_00_ERROR is defined, "%00" in a URI is an error. */
+          *pzErrMsg = sqlite3_mprintf("unexpected %%00 in uri");
+          rc = SQLITE_ERROR;
+          goto parse_uri_out;
+#endif
+        }
+        c = octet;
+      }else if( eState==1 && (c=='&' || c=='=') ){
+        if( zFile[iOut-1]==0 ){
+          /* An empty option name. Ignore this option altogether. */
+          while( zUri[iIn] && zUri[iIn]!='#' && zUri[iIn-1]!='&' ) iIn++;
+          continue;
+        }
+        if( c=='&' ){
+          zFile[iOut++] = '\0';
+        }else{
+          eState = 2;
+        }
+        c = 0;
+      }else if( (eState==0 && c=='?') || (eState==2 && c=='&') ){
+        c = 0;
+        eState = 1;
+      }
+      zFile[iOut++] = c;
+    }
+    if( eState==1 ) zFile[iOut++] = '\0';
+    zFile[iOut++] = '\0';
+    zFile[iOut++] = '\0';
+
+    /* Check if there were any options specified that should be interpreted 
+    ** here. Options that are interpreted here include "vfs" and those that
+    ** correspond to flags that may be passed to the sqlite3_open_v2()
+    ** method. */
+    zOpt = &zFile[sqlite3Strlen30(zFile)+1];
+    while( zOpt[0] ){
+      int nOpt = sqlite3Strlen30(zOpt);
+      char *zVal = &zOpt[nOpt+1];
+      int nVal = sqlite3Strlen30(zVal);
+
+      if( nOpt==3 && memcmp("vfs", zOpt, 3)==0 ){
+        zVfs = zVal;
+      }else{
+        struct OpenMode {
+          const char *z;
+          int mode;
+        } *aMode = 0;
+        char *zModeType = 0;
+        int mask = 0;
+        int limit = 0;
+
+        if( nOpt==5 && memcmp("cache", zOpt, 5)==0 ){
+          static struct OpenMode aCacheMode[] = {
+            { "shared",  SQLITE_OPEN_SHAREDCACHE },
+            { "private", SQLITE_OPEN_PRIVATECACHE },
+            { 0, 0 }
+          };
+
+          mask = SQLITE_OPEN_SHAREDCACHE|SQLITE_OPEN_PRIVATECACHE;
+          aMode = aCacheMode;
+          limit = mask;
+          zModeType = "cache";
+        }
+        if( nOpt==4 && memcmp("mode", zOpt, 4)==0 ){
+          static struct OpenMode aOpenMode[] = {
+            { "ro",  SQLITE_OPEN_READONLY },
+            { "rw",  SQLITE_OPEN_READWRITE }, 
+            { "rwc", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE },
+            { "memory", SQLITE_OPEN_MEMORY },
+            { 0, 0 }
+          };
+
+          mask = SQLITE_OPEN_READONLY | SQLITE_OPEN_READWRITE
+                   | SQLITE_OPEN_CREATE | SQLITE_OPEN_MEMORY;
+          aMode = aOpenMode;
+          limit = mask & flags;
+          zModeType = "access";
+        }
+
+        if( aMode ){
+          int i;
+          int mode = 0;
+          for(i=0; aMode[i].z; i++){
+            const char *z = aMode[i].z;
+            if( nVal==sqlite3Strlen30(z) && 0==memcmp(zVal, z, nVal) ){
+              mode = aMode[i].mode;
+              break;
+            }
+          }
+          if( mode==0 ){
+            *pzErrMsg = sqlite3_mprintf("no such %s mode: %s", zModeType, zVal);
+            rc = SQLITE_ERROR;
+            goto parse_uri_out;
+          }
+          if( (mode & ~SQLITE_OPEN_MEMORY)>limit ){
+            *pzErrMsg = sqlite3_mprintf("%s mode not allowed: %s",
+                                        zModeType, zVal);
+            rc = SQLITE_PERM;
+            goto parse_uri_out;
+          }
+          flags = (flags & ~mask) | mode;
+        }
+      }
+
+      zOpt = &zVal[nVal+1];
+    }
+
+  }else{
+    zFile = sqlite3_malloc64(nUri+2);
+    if( !zFile ) return SQLITE_NOMEM_BKPT;
+    if( nUri ){
+      memcpy(zFile, zUri, nUri);
+    }
+    zFile[nUri] = '\0';
+    zFile[nUri+1] = '\0';
+    flags &= ~SQLITE_OPEN_URI;
+  }
+
+  *ppVfs = sqlite3_vfs_find(zVfs);
+  if( *ppVfs==0 ){
+    *pzErrMsg = sqlite3_mprintf("no such vfs: %s", zVfs);
+    rc = SQLITE_ERROR;
+  }
+ parse_uri_out:
+  if( rc!=SQLITE_OK ){
+    sqlite3_free(zFile);
+    zFile = 0;
+  }
+  *pFlags = flags;
+  *pzFile = zFile;
+  return rc;
 }
 
+
 /*
 ** This routine does the work of opening a database on behalf of
 ** sqlite3_open() and sqlite3_open16(). The database filename "zFilename"  
 ** is UTF-8 encoded.
 */
 static int openDatabase(
