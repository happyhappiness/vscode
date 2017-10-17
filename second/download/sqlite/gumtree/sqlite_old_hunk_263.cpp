  sqlite3 *db, 
  Table *pTab,
  Module *pMod,
  int (*xConstruct)(sqlite3*,void*,int,const char*const*,sqlite3_vtab**,char**),
  char **pzErr
){
  int rc;
  int rc2;
  sqlite3_vtab *pVtab = 0;
  const char *const*azArg = (const char *const*)pTab->azModuleArg;
  int nArg = pTab->nModuleArg;
  char *zErr = 0;
  char *zModuleName = sqlite3MPrintf(db, "%s", pTab->zName);

  if( !zModuleName ){
    return SQLITE_NOMEM;
  }

  assert( !db->pVTab );
  assert( xConstruct );

  db->pVTab = pTab;
  rc = sqlite3SafetyOff(db);
  assert( rc==SQLITE_OK );
  rc = xConstruct(db, pMod->pAux, nArg, azArg, &pVtab, &zErr);
  rc2 = sqlite3SafetyOn(db);
  if( rc==SQLITE_NOMEM ) db->mallocFailed = 1;
  /* Justification of ALWAYS():  A correct vtab constructor must allocate
  ** the sqlite3_vtab object if successful. */
  if( rc==SQLITE_OK && ALWAYS(pVtab) ){
    pVtab->pModule = pMod->pModule;
    pVtab->nRef = 1;
    pTab->pVtab = pVtab;
  }

  if( SQLITE_OK!=rc ){
    if( zErr==0 ){
      *pzErr = sqlite3MPrintf(db, "vtable constructor failed: %s", zModuleName);
    }else {
      *pzErr = sqlite3MPrintf(db, "%s", zErr);
      sqlite3DbFree(db, zErr);
    }
  }else if( db->pVTab ){
    const char *zFormat = "vtable constructor did not declare schema: %s";
    *pzErr = sqlite3MPrintf(db, zFormat, pTab->zName);
    rc = SQLITE_ERROR;
  } 
  if( rc==SQLITE_OK ){
    rc = rc2;
  }
  db->pVTab = 0;
  sqlite3DbFree(db, zModuleName);

  /* If everything went according to plan, loop through the columns
  ** of the table to see if any of them contain the token "hidden".
  ** If so, set the Column.isHidden flag and remove the token from
  ** the type string.
  */
  if( rc==SQLITE_OK ){
    int iCol;
    for(iCol=0; iCol<pTab->nCol; iCol++){
      char *zType = pTab->aCol[iCol].zType;
      int nType;
      int i = 0;
      if( !zType ) continue;
      nType = sqlite3Strlen30(zType);
      if( sqlite3StrNICmp("hidden", zType, 6) || (zType[6] && zType[6]!=' ') ){
        for(i=0; i<nType; i++){
          if( (0==sqlite3StrNICmp(" hidden", &zType[i], 7))
           && (zType[i+7]=='\0' || zType[i+7]==' ')
          ){
            i++;
            break;
          }
        }
      }
      if( i<nType ){
        int j;
        int nDel = 6 + (zType[i+6] ? 1 : 0);
        for(j=i; (j+nDel)<=nType; j++){
          zType[j] = zType[j+nDel];
        }
        if( zType[i]=='\0' && i>0 ){
          assert(zType[i-1]==' ');
          zType[i-1] = '\0';
        }
        pTab->aCol[iCol].isHidden = 1;
      }
    }
  }
  return rc;
}

/*
** This function is invoked by the parser to call the xConnect() method
** of the virtual table pTab. If an error occurs, an error code is returned 
** and an error left in pParse.
**
** This call is a no-op if table pTab is not a virtual table.
*/
int sqlite3VtabCallConnect(Parse *pParse, Table *pTab){
  Module *pMod;
  int rc = SQLITE_OK;

  assert( pTab );
  if( (pTab->tabFlags & TF_Virtual)==0 || pTab->pVtab ){
    return SQLITE_OK;
  }

  pMod = pTab->pMod;
  if( !pMod ){
    const char *zModule = pTab->azModuleArg[0];
    sqlite3ErrorMsg(pParse, "no such module: %s", zModule);
    rc = SQLITE_ERROR;
  } else {
    char *zErr = 0;
    sqlite3 *db = pParse->db;
    rc = vtabCallConstructor(db, pTab, pMod, pMod->pModule->xConnect, &zErr);
    if( rc!=SQLITE_OK ){
      sqlite3ErrorMsg(pParse, "%s", zErr);
    }
    sqlite3DbFree(db, zErr);
  }

  return rc;
}
