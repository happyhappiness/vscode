sqlite3_mprintf("SELECT %s ORDER BY rowid %s", 
          p->zReadExprlist, (pCsr->bDesc ? "DESC" : "ASC")
      );