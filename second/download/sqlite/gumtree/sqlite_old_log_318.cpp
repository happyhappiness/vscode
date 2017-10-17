sqlite3MPrintf(db, "SELECT idx, stat FROM %Q.sqlite_stat1",
                        sInfo.zDatabase);