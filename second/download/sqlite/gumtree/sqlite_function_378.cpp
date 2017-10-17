int sqlite3CantopenError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return reportError(SQLITE_CANTOPEN, lineno, "cannot open file");
}