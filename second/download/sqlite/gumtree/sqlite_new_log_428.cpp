sqlite3MPrintf(db, 
        "SELECT name, rootpage, sql FROM \"%w\".%s ORDER BY rowid",
        db->aDb[iDb].zDbSName, zMasterName);