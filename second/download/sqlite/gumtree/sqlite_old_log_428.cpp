sqlite3MPrintf(db, 
        "SELECT name, rootpage, sql FROM '%q'.%s",
        db->aDb[iDb].zName, zMasterName);