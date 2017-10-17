sqlite3MPrintf(db, "%s%.*s\"%w\"", 
            (zOutput?zOutput:""), (int)(z-zInput), zInput, (const char *)zNew
        );