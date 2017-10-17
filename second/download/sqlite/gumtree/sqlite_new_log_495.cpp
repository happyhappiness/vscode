sqlite3_log(rc, "statement aborts at %d: [%s] %s", 
                   (int)(pOp - aOp), p->zSql, p->zErrMsg);