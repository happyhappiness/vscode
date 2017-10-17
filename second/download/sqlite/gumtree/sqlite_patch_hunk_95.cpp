           break;
         }
       }
       if( n==0 ) *tokenType = TK_ILLEGAL;
       return i;
     }
-    case CC_KYWD: {
-      for(i=1; aiClass[z[i]]<=CC_KYWD; i++){}
-      if( IdChar(z[i]) ){
-        /* This token started out using characters that can appear in keywords,
-        ** but z[i] is a character not allowed within keywords, so this must
-        ** be an identifier instead */
-        i++;
-        break;
-      }
-      *tokenType = TK_ID;
-      return keywordCode((char*)z, i, tokenType);
-    }
-    case CC_X: {
 #ifndef SQLITE_OMIT_BLOB_LITERAL
+    case 'x': case 'X': {
       testcase( z[0]=='x' ); testcase( z[0]=='X' );
       if( z[1]=='\'' ){
         *tokenType = TK_BLOB;
-        for(i=2; sqlite3Isxdigit(z[i]); i++){}
-        if( z[i]!='\'' || i%2 ){
-          *tokenType = TK_ILLEGAL;
-          while( z[i] && z[i]!='\'' ){ i++; }
+        for(i=2; (c=z[i])!=0 && c!='\''; i++){
+          if( !sqlite3Isxdigit(c) ){
+            *tokenType = TK_ILLEGAL;
+          }
         }
-        if( z[i] ) i++;
+        if( i%2 || !c ) *tokenType = TK_ILLEGAL;
+        if( c ) i++;
         return i;
       }
-#endif
-      /* If it is not a BLOB literal, then it must be an ID, since no
-      ** SQL keywords start with the letter 'x'.  Fall through */
-    }
-    case CC_ID: {
-      i = 1;
-      break;
+      /* Otherwise fall through to the next case */
     }
+#endif
     default: {
-      *tokenType = TK_ILLEGAL;
-      return 1;
+      if( !IdChar(*z) ){
+        break;
+      }
+      for(i=1; IdChar(z[i]); i++){}
+      *tokenType = keywordCode((char*)z, i);
+      return i;
     }
   }
-  while( IdChar(z[i]) ){ i++; }
-  *tokenType = TK_ID;
-  return i;
+  *tokenType = TK_ILLEGAL;
+  return 1;
 }
 
 /*
 ** Run the parser on the given SQL string.  The parser structure is
 ** passed in.  An SQLITE_ status code is returned.  If an error occurs
 ** then an and attempt is made to write an error message into 
 ** memory obtained from sqlite3_malloc() and to make *pzErrMsg point to that
 ** error message.
 */
 int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg){
   int nErr = 0;                   /* Number of errors encountered */
+  int i;                          /* Loop counter */
   void *pEngine;                  /* The LEMON-generated LALR(1) parser */
-  int n = 0;                      /* Length of the next token token */
   int tokenType;                  /* type of the next token */
   int lastTokenParsed = -1;       /* type of the previous token */
+  u8 enableLookaside;             /* Saved value of db->lookaside.bEnabled */
   sqlite3 *db = pParse->db;       /* The database connection */
   int mxSqlLen;                   /* Max length of an SQL string */
-#ifdef sqlite3Parser_ENGINEALWAYSONSTACK
-  yyParser sEngine;    /* Space to hold the Lemon-generated Parser object */
-#endif
 
-  assert( zSql!=0 );
+
   mxSqlLen = db->aLimit[SQLITE_LIMIT_SQL_LENGTH];
-  if( db->nVdbeActive==0 ){
+  if( db->activeVdbeCnt==0 ){
     db->u1.isInterrupted = 0;
   }
   pParse->rc = SQLITE_OK;
-  pParse->zTail = zSql;
+  pParse->zTail = pParse->zSql = zSql;
+  i = 0;
   assert( pzErrMsg!=0 );
-  /* sqlite3ParserTrace(stdout, "parser: "); */
-#ifdef sqlite3Parser_ENGINEALWAYSONSTACK
-  pEngine = &sEngine;
-  sqlite3ParserInit(pEngine);
-#else
-  pEngine = sqlite3ParserAlloc(sqlite3Malloc);
+  pEngine = sqlite3ParserAlloc((void*(*)(size_t))sqlite3Malloc);
   if( pEngine==0 ){
-    sqlite3OomFault(db);
-    return SQLITE_NOMEM_BKPT;
+    db->mallocFailed = 1;
+    return SQLITE_NOMEM;
   }
-#endif
   assert( pParse->pNewTable==0 );
   assert( pParse->pNewTrigger==0 );
   assert( pParse->nVar==0 );
-  assert( pParse->pVList==0 );
-  while( 1 ){
-    if( zSql[0]!=0 ){
-      n = sqlite3GetToken((u8*)zSql, &tokenType);
-      mxSqlLen -= n;
-      if( mxSqlLen<0 ){
-        pParse->rc = SQLITE_TOOBIG;
-        break;
-      }
-    }else{
-      /* Upon reaching the end of input, call the parser two more times
-      ** with tokens TK_SEMI and 0, in that order. */
-      if( lastTokenParsed==TK_SEMI ){
-        tokenType = 0;
-      }else if( lastTokenParsed==0 ){
-        break;
-      }else{
-        tokenType = TK_SEMI;
-      }
-      zSql -= n;
+  assert( pParse->nVarExpr==0 );
+  assert( pParse->nVarExprAlloc==0 );
+  assert( pParse->apVarExpr==0 );
+  enableLookaside = db->lookaside.bEnabled;
+  if( db->lookaside.pStart ) db->lookaside.bEnabled = 1;
+  while( !db->mallocFailed && zSql[i]!=0 ){
+    assert( i>=0 );
+    pParse->sLastToken.z = &zSql[i];
+    pParse->sLastToken.n = sqlite3GetToken((unsigned char*)&zSql[i],&tokenType);
+    i += pParse->sLastToken.n;
+    if( i>mxSqlLen ){
+      pParse->rc = SQLITE_TOOBIG;
+      break;
     }
-    if( tokenType>=TK_SPACE ){
-      assert( tokenType==TK_SPACE || tokenType==TK_ILLEGAL );
-      if( db->u1.isInterrupted ){
-        pParse->rc = SQLITE_INTERRUPT;
+    switch( tokenType ){
+      case TK_SPACE: {
+        if( db->u1.isInterrupted ){
+          sqlite3ErrorMsg(pParse, "interrupt");
+          pParse->rc = SQLITE_INTERRUPT;
+          goto abort_parse;
+        }
         break;
       }
-      if( tokenType==TK_ILLEGAL ){
-        sqlite3ErrorMsg(pParse, "unrecognized token: \"%.*s\"", n, zSql);
+      case TK_ILLEGAL: {
+        sqlite3DbFree(db, *pzErrMsg);
+        *pzErrMsg = sqlite3MPrintf(db, "unrecognized token: \"%T\"",
+                        &pParse->sLastToken);
+        nErr++;
+        goto abort_parse;
+      }
+      case TK_SEMI: {
+        pParse->zTail = &zSql[i];
+        /* Fall thru into the default case */
+      }
+      default: {
+        sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
+        lastTokenParsed = tokenType;
+        if( pParse->rc!=SQLITE_OK ){
+          goto abort_parse;
+        }
         break;
       }
-      zSql += n;
-    }else{
-      pParse->sLastToken.z = zSql;
-      pParse->sLastToken.n = n;
-      sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
-      lastTokenParsed = tokenType;
-      zSql += n;
-      if( pParse->rc!=SQLITE_OK || db->mallocFailed ) break;
     }
   }
-  assert( nErr==0 );
-  pParse->zTail = zSql;
+abort_parse:
+  if( zSql[i]==0 && nErr==0 && pParse->rc==SQLITE_OK ){
+    if( lastTokenParsed!=TK_SEMI ){
+      sqlite3Parser(pEngine, TK_SEMI, pParse->sLastToken, pParse);
+      pParse->zTail = &zSql[i];
+    }
+    sqlite3Parser(pEngine, 0, pParse->sLastToken, pParse);
+  }
 #ifdef YYTRACKMAXSTACKDEPTH
-  sqlite3_mutex_enter(sqlite3MallocMutex());
-  sqlite3StatusHighwater(SQLITE_STATUS_PARSER_STACK,
+  sqlite3StatusSet(SQLITE_STATUS_PARSER_STACK,
       sqlite3ParserStackPeak(pEngine)
   );
-  sqlite3_mutex_leave(sqlite3MallocMutex());
 #endif /* YYDEBUG */
-#ifdef sqlite3Parser_ENGINEALWAYSONSTACK
-  sqlite3ParserFinalize(pEngine);
-#else
   sqlite3ParserFree(pEngine, sqlite3_free);
-#endif
+  db->lookaside.bEnabled = enableLookaside;
   if( db->mallocFailed ){
-    pParse->rc = SQLITE_NOMEM_BKPT;
+    pParse->rc = SQLITE_NOMEM;
   }
   if( pParse->rc!=SQLITE_OK && pParse->rc!=SQLITE_DONE && pParse->zErrMsg==0 ){
-    pParse->zErrMsg = sqlite3MPrintf(db, "%s", sqlite3ErrStr(pParse->rc));
+    sqlite3SetString(&pParse->zErrMsg, db, "%s", sqlite3ErrStr(pParse->rc));
   }
   assert( pzErrMsg!=0 );
   if( pParse->zErrMsg ){
     *pzErrMsg = pParse->zErrMsg;
-    sqlite3_log(pParse->rc, "%s", *pzErrMsg);
     pParse->zErrMsg = 0;
     nErr++;
   }
   if( pParse->pVdbe && pParse->nErr>0 && pParse->nested==0 ){
     sqlite3VdbeDelete(pParse->pVdbe);
     pParse->pVdbe = 0;
