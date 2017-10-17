       || (SQLITE_TEMP_STORE==2 && db->temp_store==1)
      ){
        invalidateTempStorage(pParse);
      }
      sqlite3_free(sqlite3_temp_directory);
      if( zRight[0] ){
        sqlite3_temp_directory = sqlite3DbStrDup(0, zRight);
      }else{
        sqlite3_temp_directory = 0;
      }
#endif /* SQLITE_OMIT_WSD */
    }
  }else

#if !defined(SQLITE_ENABLE_LOCKING_STYLE)
#  if defined(__APPLE__)
#    define SQLITE_ENABLE_LOCKING_STYLE 1
#  else
#    define SQLITE_ENABLE_LOCKING_STYLE 0
#  endif
#endif
#if SQLITE_ENABLE_LOCKING_STYLE
  /*
   **   PRAGMA [database.]lock_proxy_file
   **   PRAGMA [database.]lock_proxy_file = ":auto:"|"lock_file_path"
   **
   ** Return or set the value of the lock_proxy_file flag.  Changing
   ** the value sets a specific file to be used for database access locks.
   **
   */
  if( sqlite3StrICmp(zLeft, "lock_proxy_file")==0 ){
    if( !zRight ){
      Pager *pPager = sqlite3BtreePager(pDb->pBt);
      char *proxy_file_path = NULL;
      sqlite3_file *pFile = sqlite3PagerFile(pPager);
      sqlite3OsFileControl(pFile, SQLITE_GET_LOCKPROXYFILE, 
                           &proxy_file_path);
      
      if( proxy_file_path ){
        sqlite3VdbeSetNumCols(v, 1);
        sqlite3VdbeSetColName(v, 0, COLNAME_NAME, 
                              "lock_proxy_file", SQLITE_STATIC);
        sqlite3VdbeAddOp4(v, OP_String8, 0, 1, 0, proxy_file_path, 0);
        sqlite3VdbeAddOp2(v, OP_ResultRow, 1, 1);
      }
    }else{
      Pager *pPager = sqlite3BtreePager(pDb->pBt);
      sqlite3_file *pFile = sqlite3PagerFile(pPager);
      int res;
      if( zRight[0] ){
        res=sqlite3OsFileControl(pFile, SQLITE_SET_LOCKPROXYFILE, 
