sqlite3MPrintf(db, "%.*s\"%w\"%s", ((u8*)tname.z) - zSql, zSql, 
       zTableName, tname.z+tname.n);