sqlite3ValueSetStr(db->pErr, -1, sqlite3ErrStr(db->errCode),
           SQLITE_UTF8, SQLITE_STATIC);