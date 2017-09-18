        qvalue[7] = 'p';
        qvalue[8] = ';';
        qvalue[9] = 'O';
        qvalue[10] = '=';
        qvalue[11] = reverse ? D_DESCENDING : D_ASCENDING;
        qvalue[12] = '\0';
        ap_rvputs(r, "<a href=\"", qvalue, colargs ? colargs : "", 
                     "\">", anchor, "</a>", NULL);
    }
    else {
        ap_rputs(anchor, r);
    }
}

static void output_directories(struct ent **ar, int n,
                               autoindex_config_rec *d, request_rec *r,
                               apr_int32_t autoindex_opts, char keyid, 
                               char direction, const char *colargs)
{
    int x;
    apr_size_t rv;
    char *name = r->uri;
    char *tp;
