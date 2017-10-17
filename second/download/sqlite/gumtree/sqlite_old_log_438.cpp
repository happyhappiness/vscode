sqlite3MPrintf(db, "%s",
                 iCol>=0 ? pTab->aCol[iCol].zName : "rowid");