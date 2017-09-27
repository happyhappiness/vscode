        }
        ptr = value+vlen;
    }

    process = dbopen(login, server);

    if (process != NULL && databaseName != NULL)
    {
        dbuse(process, databaseName);
    }
 
    dbloginfree(login);
    if (process == NULL) {
