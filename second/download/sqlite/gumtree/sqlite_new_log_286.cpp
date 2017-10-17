sqlite3_mprintf("%z %.*s%s", zBuf, 
            pPhrase->aToken[i].n, pPhrase->aToken[i].z,
            (pPhrase->aToken[i].isPrefix?"+":"")
        );