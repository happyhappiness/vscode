sqlite3MPrintf(pParse->db, "EXECUTE %s%s SUBQUERY %d",
        jmpIfDynamic>=0?"":"CORRELATED ",
        pExpr->op==TK_IN?"LIST":"SCALAR",
        pParse->iNextSelectId
    );