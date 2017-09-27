    }

    apr_dbm_close(dbmfp);

    return value;
}

static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
                                apr_file_t *fpout, char *key)
{
    char *buf;
    char c;
