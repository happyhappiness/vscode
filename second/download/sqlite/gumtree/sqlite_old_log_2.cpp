sqlite3_mprintf(
        "CREATE TABLE x(%s %Q HIDDEN, docid HIDDEN, %Q HIDDEN)", 
        zCols, p->zName, zLanguageid
    );