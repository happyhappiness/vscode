sqlite3_log(SQLITE_MISUSE, 
        "bind on a busy prepared statement: [%s]", p->zSql);