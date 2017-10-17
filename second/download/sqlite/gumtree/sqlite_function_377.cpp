int sqlite3MisuseError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return reportError(SQLITE_MISUSE, lineno, "misuse");
}