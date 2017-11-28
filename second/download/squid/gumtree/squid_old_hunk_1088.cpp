        entry->flush();
        gopherState->HTML_header_added = 1;

        return;
    }

    if (gopherState->conversion == gopher_ds::HTML_CSO_PAGE) {
        char *html_url = html_quote(entry->url());
        gopherHTMLHeader(entry, "CSO Search of %s", html_url);
        storeAppendPrintf(entry,
                          "<P>A CSO database usually contains a phonebook or\n"
                          "directory.  Use the search function of your browser to enter\n"
                          "search terms.</P><ISINDEX>\n");
