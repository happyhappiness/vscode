void
storeLog(int tag, const StoreEntry * e)
{
    MemObject *mem = e->mem_obj;
    HttpReply const *reply;

    if (str_unknown.undefined())
        str_unknown="unknown"; //hack. Delay initialization as string doesn't support global variables..

    if (NULL == storelog)
        return;

    ++storeLogTagsCounts[tag];
    if (mem != NULL) {
        if (mem->log_url == NULL) {
            debugs(20, DBG_IMPORTANT, "storeLog: NULL log_url for " << mem->url);
            mem->dump();
            mem->log_url = xstrdup(mem->url);
        }

        reply = e->getReply();
        /*
         * XXX Ok, where should we print the dir number here?
         * Because if we print it before the swap file number, it'll break
         * the existing log format.
         */

        String ctype=(reply->content_type.size() ? reply->content_type.termedBuf() : str_unknown);

        logfileLineStart(storelog);
        logfilePrintf(storelog, "%9d.%03d %-7s %02d %08X %s %4d %9d %9d %9d " SQUIDSTRINGPH " %" PRId64 "/%" PRId64 " %s %s\n",
                      (int) current_time.tv_sec,
                      (int) current_time.tv_usec / 1000,
                      storeLogTags[tag],
                      e->swap_dirn,
                      e->swap_filen,
                      e->getMD5Text(),
