void
HttpHeader::removeConnectionHeaderEntries()
{
    if (has(HDR_CONNECTION)) {
        /* anything that matches Connection list member will be deleted */
        String strConnection;

        (void) getList(HDR_CONNECTION, &strConnection);
        const HttpHeaderEntry *e;
        HttpHeaderPos pos = HttpHeaderInitPos;
        /*
         * think: on-average-best nesting of the two loops (hdrEntry
         * and strListItem) @?@
         */
        /*
         * maybe we should delete standard stuff ("keep-alive","close")
         * from strConnection first?
         */

        int headers_deleted = 0;
        while ((e = getEntry(&pos))) {
            if (strListIsMember(&strConnection, e->name.termedBuf(), ','))
                delAt(pos, headers_deleted);
        }
        if (headers_deleted)
            refreshMask();
    }
}