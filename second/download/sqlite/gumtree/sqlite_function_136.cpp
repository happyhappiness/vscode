int sqlite3_unlock_notify(
  sqlite3 *db,
  void (*xNotify)(void **, int),
  void *pArg
){
  int rc = SQLITE_OK;

  sqlite3_mutex_enter(db->mutex);
  enterMutex();

  if( xNotify==0 ){
    removeFromBlockedList(db);
    db->pBlockingConnection = 0;
    db->pUnlockConnection = 0;
    db->xUnlockNotify = 0;
    db->pUnlockArg = 0;
  }else if( 0==db->pBlockingConnection ){
    /* The blocking transaction has been concluded. Or there never was a 
    ** blocking transaction. In either case, invoke the notify callback
    ** immediately. 
    */
    xNotify(&pArg, 1);
  }else{
    sqlite3 *p;

    for(p=db->pBlockingConnection; p && p!=db; p=p->pUnlockConnection){}
    if( p ){
      rc = SQLITE_LOCKED;              /* Deadlock detected. */
    }else{
      db->pUnlockConnection = db->pBlockingConnection;
      db->xUnlockNotify = xNotify;
      db->pUnlockArg = pArg;
      removeFromBlockedList(db);
      addToBlockedList(db);
    }
  }

  leaveMutex();
  assert( !db->mallocFailed );
  sqlite3ErrorWithMsg(db, rc, (rc?"database is deadlocked":0));
  sqlite3_mutex_leave(db->mutex);
  return rc;
}