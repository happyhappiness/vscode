int sqlite3NomemError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return reportError(SQLITE_NOMEM, lineno, "OOM");
}