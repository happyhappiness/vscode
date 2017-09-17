}

#ifdef USE_PERL_SSI
static int handle_perl(FILE *in, request_rec *r, const char *error)
{
    char tag[MAX_STRING_LEN];
    char *tag_val;
    SV *sub = Nullsv;
    AV *av = newAV();

    if (!(ap_allow_options(r) & OPT_INCLUDES)) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
