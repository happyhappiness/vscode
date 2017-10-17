sqlite3SetString(&p->zErrMsg, db, 
        "cannot %s savepoint - SQL statements in progress",
        (p1==SAVEPOINT_ROLLBACK ? "rollback": "release")
      );