    if (!user_name)
        user_name = "";

    if (!host || !strlen(host))
        host = "";

    printf("Content-Type: text/html\r\n\r\n");

    printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");

    printf("<HTML><HEAD><TITLE>Cache Manager Interface</TITLE>\n");

    printf("<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE></HEAD>\n");

    printf("<BODY><H1>Cache Manager Interface</H1>\n");

    printf("<P>This is a WWW interface to the instrumentation interface\n");

    printf("for the Squid object cache.</P>\n");

    printf("<HR noshade size=\"1px\">\n");

    printf("<FORM METHOD=\"POST\" ACTION=\"%s\">\n", script_name);

    printf("<TABLE BORDER=\"0\" CELLPADDING=\"10\" CELLSPACING=\"1\">\n");


    fp = fopen("cachemgr.conf", "r");

    if (fp == NULL)
        fp = fopen(DEFAULT_CACHEMGR_CONFIG, "r");

    if (fp != NULL) {
        int servers = 0;
        char config_line[BUFSIZ];

        while (fgets(config_line, BUFSIZ, fp)) {
            char *server, *comment;
