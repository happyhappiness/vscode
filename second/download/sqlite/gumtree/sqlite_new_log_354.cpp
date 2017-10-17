sqlite3MPrintf(pParse->db, "%s.%s", pTab->zName,
                          pTab->aCol[pTab->iPKey].zName);