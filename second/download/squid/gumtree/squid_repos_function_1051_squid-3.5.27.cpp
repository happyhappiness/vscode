void
parse_obsolete(const char *name)
{
    // Directives which have been radically changed rather than removed
    if (!strcmp(name, "url_rewrite_concurrency")) {
        int cval;
        parse_int(&cval);
        debugs(3, DBG_CRITICAL, "WARNING: url_rewrite_concurrency upgrade overriding url_rewrite_children settings.");
        Config.redirectChildren.concurrency = cval;
    }

    if (!strcmp(name, "log_access"))
        self_destruct();

    if (!strcmp(name, "log_icap"))
        self_destruct();

    if (!strcmp(name, "ignore_ims_on_miss")) {
        // the replacement directive cache_revalidate_on_miss has opposite meanings for ON/OFF value
        // than the 2.7 directive. We need to parse and invert the configured value.
        int temp = 0;
        parse_onoff(&temp);
        Config.onoff.cache_miss_revalidate = !temp;
    }
}