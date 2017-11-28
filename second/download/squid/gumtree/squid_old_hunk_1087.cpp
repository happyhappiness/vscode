
    memset(tmpbuf, '\0', TEMP_BUF_SIZE);
    memset(line, '\0', TEMP_BUF_SIZE);

    entry = gopherState->entry;

    if (gopherState->conversion == gopher_ds::HTML_INDEX_PAGE) {
        char *html_url = html_quote(entry->url());
        gopherHTMLHeader(entry, "Gopher Index %s", html_url);
        storeAppendPrintf(entry,
                          "<p>This is a searchable Gopher index. Use the search\n"
                          "function of your browser to enter search terms.\n"
                          "<ISINDEX>\n");
