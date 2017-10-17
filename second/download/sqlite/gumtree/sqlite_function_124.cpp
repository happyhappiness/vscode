int sqlite3CorruptError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return reportError(SQLITE_CORRUPT, lineno, "database corruption");
}