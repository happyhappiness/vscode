int sqlite3IoerrnomemError(int lineno){
  testcase( sqlite3GlobalConfig.xLog!=0 );
  return reportError(SQLITE_IOERR_NOMEM, lineno, "I/O OOM error");
}