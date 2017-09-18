        apr_cpystrn(record, "resultant record too long", (rlen - 1));
        return ERR_OVERFLOW;
    }
    strcpy(record, user);
    strcat(record, ":");
    strcat(record, cpw);
    return 0;
}

static void usage(void)
{
    apr_file_printf(errfile, "Usage:\n");
