          break;
        }
      }
      if( n==0 ) *tokenType = TK_ILLEGAL;
      return i;
    }
#ifndef SQLITE_OMIT_BLOB_LITERAL
    case 'x': case 'X': {
      testcase( z[0]=='x' ); testcase( z[0]=='X' );
      if( z[1]=='\'' ){
        *tokenType = TK_BLOB;
        for(i=2; (c=z[i])!=0 && c!='\''; i++){
          if( !sqlite3Isxdigit(c) ){
            *tokenType = TK_ILLEGAL;
          }
        }
        if( i%2 || !c ) *tokenType = TK_ILLEGAL;
        if( c ) i++;
        return i;
      }
      /* Otherwise fall through to the next case */
    }
#endif
    default: {
      if( !IdChar(*z) ){
        break;
      }
      for(i=1; IdChar(z[i]); i++){}
      *tokenType = keywordCode((char*)z, i);
      return i;
    }
  }
  *tokenType = TK_ILLEGAL;
  return 1;
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
  int i;                          /* Loop counter */
  void *pEngine;                  /* The LEMON-generated LALR(1) parser */
  int tokenType;                  /* type of the next token */
  int lastTokenParsed = -1;       /* type of the previous token */
  u8 enableLookaside;             /* Saved value of db->lookaside.bEnabled */
  sqlite3 *db = pParse->db;       /* The database connection */
  int mxSqlLen;                   /* Max length of an SQL string */


  mxSqlLen = db->aLimit[SQLITE_LIMIT_SQL_LENGTH];
  if( db->activeVdbeCnt==0 ){
    db->u1.isInterrupted = 0;
  }
  pParse->rc = SQLITE_OK;
  pParse->zTail = pParse->zSql = zSql;
  i = 0;
  assert( pzErrMsg!=0 );
  pEngine = sqlite3ParserAlloc((void*(*)(size_t))sqlite3Malloc);
  if( pEngine==0 ){
    db->mallocFailed = 1;
    return SQLITE_NOMEM;
  }
  assert( pParse->pNewTable==0 );
  assert( pParse->pNewTrigger==0 );
  assert( pParse->nVar==0 );
  assert( pParse->nVarExpr==0 );
  assert( pParse->nVarExprAlloc==0 );
  assert( pParse->apVarExpr==0 );
  enableLookaside = db->lookaside.bEnabled;
  if( db->lookaside.pStart ) db->lookaside.bEnabled = 1;
  while( !db->mallocFailed && zSql[i]!=0 ){
    assert( i>=0 );
    pParse->sLastToken.z = &zSql[i];
    pParse->sLastToken.n = sqlite3GetToken((unsigned char*)&zSql[i],&tokenType);
    i += pParse->sLastToken.n;
    if( i>mxSqlLen ){
      pParse->rc = SQLITE_TOOBIG;
      break;
    }
    switch( tokenType ){
      case TK_SPACE: {
        if( db->u1.isInterrupted ){
          sqlite3ErrorMsg(pParse, "interrupt");
          pParse->rc = SQLITE_INTERRUPT;
          goto abort_parse;
        }
        break;
      }
      case TK_ILLEGAL: {
        sqlite3DbFree(db, *pzErrMsg);
        *pzErrMsg = sqlite3MPrintf(db, "unrecognized token: \"%T\"",
                        &pParse->sLastToken);
        nErr++;
        goto abort_parse;
      }
      case TK_SEMI: {
        pParse->zTail = &zSql[i];
        /* Fall thru into the default case */
      }
      default: {
        sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
        lastTokenParsed = tokenType;
        if( pParse->rc!=SQLITE_OK ){
          goto abort_parse;
        }
        break;
      }
    }
  }
abort_parse:
  if( zSql[i]==0 && nErr==0 && pParse->rc==SQLITE_OK ){
    if( lastTokenParsed!=TK_SEMI ){
      sqlite3Parser(pEngine, TK_SEMI, pParse->sLastToken, pParse);
      pParse->zTail = &zSql[i];
    }
    sqlite3Parser(pEngine, 0, pParse->sLastToken, pParse);
  }
#ifdef YYTRACKMAXSTACKDEPTH
  sqlite3StatusSet(SQLITE_STATUS_PARSER_STACK,
      sqlite3ParserStackPeak(pEngine)
  );
#endif /* YYDEBUG */
  sqlite3ParserFree(pEngine, sqlite3_free);
  db->lookaside.bEnabled = enableLookaside;
  if( db->mallocFailed ){
    pParse->rc = SQLITE_NOMEM;
  }
  if( pParse->rc!=SQLITE_OK && pParse->rc!=SQLITE_DONE && pParse->zErrMsg==0 ){
    sqlite3SetString(&pParse->zErrMsg, db, "%s", sqlite3ErrStr(pParse->rc));
  }
  assert( pzErrMsg!=0 );
  if( pParse->zErrMsg ){
    *pzErrMsg = pParse->zErrMsg;
    pParse->zErrMsg = 0;
    nErr++;
  }
  if( pParse->pVdbe && pParse->nErr>0 && pParse->nested==0 ){
    sqlite3VdbeDelete(pParse->pVdbe);
    pParse->pVdbe = 0;
