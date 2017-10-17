sqlite3VdbeAddOp4(v, OP_ParseSchema, iDb, 0, 0, sqlite3MPrintf(
        db, "type='trigger' AND name='%q'", zName), P4_DYNAMIC
    );