sqlite3MPrintf(db, "CREATE%s INDEX %.*s",
        onError==OE_None ? "" : " UNIQUE",
        pEnd->z - pName->z + 1,
        pName->z);