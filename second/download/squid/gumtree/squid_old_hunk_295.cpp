    mb->init();
    mb->Printf( "<TITLE>Select URL for %s</TITLE>\n"
                "<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE>\n"
                "<H2>Select URL for %s</H2>\n"
                "<TABLE BORDER=\"0\" WIDTH=\"100%%\">\n", e->url(), e->url());

    for (i = 0; i < urlcnt; i++) {
        u = &urls[i];
        debugs(52, 3, "URL {" << u->url << "}");
        mb->Printf(
            "<TR><TD><A HREF=\"%s\">%s</A></TD>", u->url, u->url);

        if (urls[i].rtt > 0)
