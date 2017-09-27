        new->active = base->active;
    }
    else {
        new->active = add->active;
    }

    if (add->expiresdefault != NULL) {
        new->expiresdefault = add->expiresdefault;
    }
    else {
	new->expiresdefault = base->expiresdefault;
    }
    new->wildcards = add->wildcards;
    new->expiresbytype = apr_table_overlay(p, add->expiresbytype,
                                        base->expiresbytype);
    return new;
}

/*
 * Handle the setting of the expiration response header fields according
 * to our criteria.
 */

static int set_expiration_fields(request_rec *r, const char *code,
                                 apr_table_t *t)
{
    apr_time_t base;
    apr_time_t additional;
    apr_time_t expires;
    int additional_sec;
    char *timestr;

    switch (code[0]) {
    case 'M':
	if (r->finfo.filetype == 0) { 
	    /* file doesn't exist on disk, so we can't do anything based on
	     * modification time.  Note that this does _not_ log an error.
	     */
