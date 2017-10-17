int sqlite3VtabCallCreate(sqlite3 *db, int iDb, const char *zTab, char **pzErr){
  int rc = SQLITE_OK;
  Table *pTab;
  Module *pMod;
  const char *zModule;

  pTab = sqlite3FindTable(db, zTab, db->aDb[iDb].zName);
  assert(pTab && (pTab->tabFlags & TF_Virtual)!=0 && !pTab->pVtab);
  pMod = pTab->pMod;
  zModule = pTab->azModuleArg[0];

  /* If the module has been registered and includes a Create method, 
  ** invoke it now. If the module has not been registered, return an 
  ** error. Otherwise, do nothing.
  */
  if( !pMod ){
    *pzErr = sqlite3MPrintf(db, "no such module: %s", zModule);
    rc = SQLITE_ERROR;
  }else{
    rc = vtabCallConstructor(db, pTab, pMod, pMod->pModule->xCreate, pzErr);
  }

  /* Justification of ALWAYS():  The xConstructor method is required to
  ** create a valid sqlite3_vtab if it returns SQLITE_OK. */
  if( rc==SQLITE_OK && ALWAYS(pTab->pVtab) ){
      rc = addToVTrans(db, pTab->pVtab);
  }

  return rc;
}