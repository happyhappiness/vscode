sqlite3MPrintf(db, "CREATE%s INDEX %.*s",
        onError==OE_None ? "" : " UNIQUE", n, pName->z);