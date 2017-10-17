       addToBlockedList(db);
     }
   }
 
   leaveMutex();
   assert( !db->mallocFailed );
-  sqlite3ErrorWithMsg(db, rc, (rc?"database is deadlocked":0));
+  sqlite3Error(db, rc, (rc?"database is deadlocked":0));
   sqlite3_mutex_leave(db->mutex);
   return rc;
 }
 
 /*
 ** This function is called while stepping or preparing a statement 
