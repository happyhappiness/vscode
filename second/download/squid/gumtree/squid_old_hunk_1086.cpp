    storeAppendPrintf(e, "<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE>\n");
    storeAppendPrintf(e, "</HEAD>\n<BODY><H1>");
    storeAppendPrintf(e, title, substring);
    storeAppendPrintf(e, "</H1>\n");
}

/// \ingroup ServerProtocolGopherInternal
static void
gopherHTMLFooter(StoreEntry * e)
{
    storeAppendPrintf(e, "<HR noshade size=\"1px\">\n");
    storeAppendPrintf(e, "<ADDRESS>\n");
    storeAppendPrintf(e, "Generated %s by %s (%s)\n",
                      mkrfc1123(squid_curtime),
                      getMyHostname(),
                      visible_appname_string);
    storeAppendPrintf(e, "</ADDRESS></BODY></HTML>\n");
}

/// \ingroup ServerProtocolGopherInternal
static void
gopherEndHTML(GopherStateData * gopherState)
{
    StoreEntry *e = gopherState->entry;

    if (!gopherState->HTML_header_added) {
