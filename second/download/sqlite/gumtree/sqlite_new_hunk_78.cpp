
/*
** sqlite3_snprintf() works like snprintf() except that it ignores the
** current locale settings.  This is important for SQLite because we
** are not able to use a "," as the decimal point in place of "." as
** specified by some locales.
*/
char *sqlite3_snprintf(int n, char *zBuf, const char *zFormat, ...){
  char *z;
  va_list ap;
  StrAccum acc;

  if( n<=0 ){
    return zBuf;
  }
  sqlite3StrAccumInit(&acc, zBuf, n, 0);
  acc.useMalloc = 0;
  va_start(ap,zFormat);
  sqlite3VXPrintf(&acc, 0, zFormat, ap);
  va_end(ap);
  z = sqlite3StrAccumFinish(&acc);
  return z;
}

#if defined(SQLITE_DEBUG)
/*
** A version of printf() that understands %lld.  Used for debugging.
** The printf() built into some versions of windows does not understand %lld
** and segfaults if you give it a long long int.
*/
void sqlite3DebugPrintf(const char *zFormat, ...){
  va_list ap;
  StrAccum acc;
  char zBuf[500];
  sqlite3StrAccumInit(&acc, zBuf, sizeof(zBuf), 0);
  acc.useMalloc = 0;
  va_start(ap,zFormat);
  sqlite3VXPrintf(&acc, 0, zFormat, ap);
  va_end(ap);
  sqlite3StrAccumFinish(&acc);
  fprintf(stdout,"%s", zBuf);
  fflush(stdout);
}
#endif
