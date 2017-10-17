    return rc;
  }

  sqlite3_bind_text(pStmt, 1, zName, -1, SQLITE_STATIC);
  if( SQLITE_ROW==sqlite3_step(pStmt) ){
    if( sqlite3_column_type(pStmt, 0)==SQLITE_BLOB ){
      memcpy(pp, sqlite3_column_blob(pStmt, 0), sizeof(*pp));
    }
  }

  return sqlite3_finalize(pStmt);
}

/*
** This function is part of the test interface for the query parser. It
** writes a text representation of the query expression pExpr into the
** buffer pointed to by argument zBuf. It is assumed that zBuf is large 
** enough to store the required text representation.
*/
static void exprToString(Fts3Expr *pExpr, char *zBuf){
  switch( pExpr->eType ){
    case FTSQUERY_PHRASE: {
      Fts3Phrase *pPhrase = pExpr->pPhrase;
      int i;
      zBuf += sprintf(zBuf, "PHRASE %d %d", pPhrase->iColumn, pPhrase->isNot);
      for(i=0; i<pPhrase->nToken; i++){
        zBuf += sprintf(zBuf," %.*s",pPhrase->aToken[i].n,pPhrase->aToken[i].z);
        zBuf += sprintf(zBuf,"%s", (pPhrase->aToken[i].isPrefix?"+":""));
      }
      return;
    }

    case FTSQUERY_NEAR:
      zBuf += sprintf(zBuf, "NEAR/%d ", pExpr->nNear);
      break;
    case FTSQUERY_NOT:
      zBuf += sprintf(zBuf, "NOT ");
      break;
    case FTSQUERY_AND:
      zBuf += sprintf(zBuf, "AND ");
      break;
    case FTSQUERY_OR:
      zBuf += sprintf(zBuf, "OR ");
      break;
  }

  zBuf += sprintf(zBuf, "{");
  exprToString(pExpr->pLeft, zBuf);
  zBuf += strlen(zBuf);
  zBuf += sprintf(zBuf, "} ");

  zBuf += sprintf(zBuf, "{");
  exprToString(pExpr->pRight, zBuf);
  zBuf += strlen(zBuf);
  zBuf += sprintf(zBuf, "}");
}

/*
** This is the implementation of a scalar SQL function used to test the 
** expression parser. It should be called as follows:
**
