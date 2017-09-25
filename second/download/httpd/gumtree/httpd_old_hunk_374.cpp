        if (rv != APR_SUCCESS) {
            break;
        }
    }
}

static int cgi_handler(request_rec *r)
{
    int nph;
    apr_size_t dbpos = 0;
    const char *argv0;
    const char *command;
