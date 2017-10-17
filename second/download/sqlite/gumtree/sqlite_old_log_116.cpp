sqlite3ErrorWithMsg(db, SQLITE_BUSY, 
        "unable to delete/modify collation sequence due to active statements");