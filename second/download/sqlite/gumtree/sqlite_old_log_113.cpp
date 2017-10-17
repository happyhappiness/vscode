sqlite3ErrorWithMsg(db, SQLITE_BUSY, 
        "unable to delete/modify user-function due to active statements");