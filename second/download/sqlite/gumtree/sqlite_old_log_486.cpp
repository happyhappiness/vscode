sqlite3MPrintf(db,
       "SELECT name, rootpage, sql FROM '%q'.%s WHERE %s",
       db->aDb[iDb].zName, zMaster, pOp->p4.z);