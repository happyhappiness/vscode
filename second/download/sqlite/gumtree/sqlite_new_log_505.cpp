sqlite3_mprintf("(%d,\"%s\",%x)",
                p->u.vtab.idxNum, p->u.vtab.idxStr, p->u.vtab.omitMask);