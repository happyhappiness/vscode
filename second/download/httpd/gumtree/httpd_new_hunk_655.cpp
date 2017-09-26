        return res;
    }

    return OK;
}

/*
 * Authorization-Info header code
 */

#ifdef SEND_DIGEST
static const char *hdr(const apr_table_t *tbl, const char *name)
