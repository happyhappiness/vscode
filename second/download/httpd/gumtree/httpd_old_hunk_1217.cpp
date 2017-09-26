        }
        ptr = value+vlen;
    }

    process = dbopen(login, server);

    fprintf(stderr, "databaseName [%s]\n", databaseName);

    if (databaseName != NULL)
    {
        dbuse(process, databaseName);
    }
 
    dbloginfree(login);
    if (process == NULL) {
