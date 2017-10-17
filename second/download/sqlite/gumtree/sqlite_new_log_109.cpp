sqlite3MPrintf(pParse->db, "%s.%s may not be NULL",
                              pTab->zName, pTab->aCol[i].zName);