
        for (x = n->hosts; x; x = x->next)
            logfilePrintf(lf, " %s", hashKeyStr(&x->hash));

        logfilePrintf(lf, "\n");

        count++;

#undef RBUF_SZ

    }

    logfileClose(lf);
