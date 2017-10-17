#ifndef SQLITE_OMIT_INTEGRITY_CHECK
/*
** Append a message to the error message string.
*/
static void checkAppendMsg(
  IntegrityCk *pCheck,
  char *zMsg1,
  const char *zFormat,
  ...
){
  va_list ap;
  if( !pCheck->mxErr ) return;
  pCheck->mxErr--;
  pCheck->nErr++;
  va_start(ap, zFormat);
  if( pCheck->errMsg.nChar ){
    sqlite3StrAccumAppend(&pCheck->errMsg, "\n", 1);
  }
  if( zMsg1 ){
    sqlite3StrAccumAppend(&pCheck->errMsg, zMsg1, -1);
  }
  sqlite3VXPrintf(&pCheck->errMsg, 1, zFormat, ap);
  va_end(ap);
  if( pCheck->errMsg.mallocFailed ){
    pCheck->mallocFailed = 1;
  }
}
#endif /* SQLITE_OMIT_INTEGRITY_CHECK */

#ifndef SQLITE_OMIT_INTEGRITY_CHECK
/*
** Add 1 to the reference count for page iPage.  If this is the second
** reference to the page, add an error message to pCheck->zErrMsg.
** Return 1 if there are 2 ore more references to the page and 0 if
** if this is the first reference to the page.
**
** Also check that the page number is in bounds.
*/
static int checkRef(IntegrityCk *pCheck, Pgno iPage, char *zContext){
  if( iPage==0 ) return 1;
  if( iPage>pCheck->nPage ){
    checkAppendMsg(pCheck, zContext, "invalid page number %d", iPage);
    return 1;
  }
  if( pCheck->anRef[iPage]==1 ){
    checkAppendMsg(pCheck, zContext, "2nd reference to page %d", iPage);
    return 1;
  }
  return  (pCheck->anRef[iPage]++)>1;
}

#ifndef SQLITE_OMIT_AUTOVACUUM
/*
** Check that the entry in the pointer-map for page iChild maps to 
** page iParent, pointer type ptrType. If not, append an error message
** to pCheck.
*/
static void checkPtrmap(
  IntegrityCk *pCheck,   /* Integrity check context */
  Pgno iChild,           /* Child page number */
  u8 eType,              /* Expected pointer map type */
  Pgno iParent,          /* Expected pointer map parent page number */
  char *zContext         /* Context description (used for error msg) */
){
  int rc;
  u8 ePtrmapType;
  Pgno iPtrmapParent;

  rc = ptrmapGet(pCheck->pBt, iChild, &ePtrmapType, &iPtrmapParent);
  if( rc!=SQLITE_OK ){
    if( rc==SQLITE_NOMEM || rc==SQLITE_IOERR_NOMEM ) pCheck->mallocFailed = 1;
    checkAppendMsg(pCheck, zContext, "Failed to read ptrmap key=%d", iChild);
    return;
  }

  if( ePtrmapType!=eType || iPtrmapParent!=iParent ){
    checkAppendMsg(pCheck, zContext, 
      "Bad ptr map entry key=%d expected=(%d,%d) got=(%d,%d)", 
      iChild, eType, iParent, ePtrmapType, iPtrmapParent);
  }
}
#endif

