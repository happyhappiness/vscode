sqlite3_mprintf(
          "SELECT %s WHERE rowid BETWEEN %lld AND %lld ORDER BY rowid %s",
          p->zReadExprlist, pCsr->iMinDocid, pCsr->iMaxDocid,
          (pCsr->bDesc ? "DESC" : "ASC")
      );