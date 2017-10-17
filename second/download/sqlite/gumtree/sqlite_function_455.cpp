static void logBadConnection(const char *zType){
  sqlite3_log(SQLITE_MISUSE, 
     "API call with %s database connection pointer",
     zType
  );
}