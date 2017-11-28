    if (!user_name)
        user_name = "";

    if (!host || !strlen(host))
        host = "";

    fp = fopen("cachemgr.conf", "r");

    if (fp == NULL)
        fp = fopen(DEFAULT_CACHEMGR_CONFIG, "r");

    if (fp == NULL)
        printf("X-Error: message=\"Unable to open config %s\"", DEFAULT_CACHEMGR_CONFIG);

    printf("Content-Type: text/html\r\n\r\n");

    printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");

    printf("<HTML><HEAD><TITLE>Cache Manager Interface</TITLE>\n");

    printf("<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}--></STYLE>\n");

    printf("<script type=\"text/javascript\">\n");
    printf("function TS(t, s) {\n");
    printf(" var x = new XMLHttpRequest();\n");
    printf(" x.open('GET', 'http' + s + '://' + t + '/squid-internal-mgr/', true);\n");
    printf(" x.onreadystatechange=function() {\n");
    printf("  if (x.readyState==4) {\n");
    printf("   if ((x.status>=200 && x.status <= 299) || x.status==401) {\n");
    printf("    var v = x.getResponseHeader('Server');\n");
    printf("    if (v.substring(0,8) == 'squid/3.' && (v[8]=='H' || parseInt(v.substring(8)) >= 2)) {\n");
    printf("     var d = document.getElementById('H' + s + 'mgr');\n");
    printf("     if (d.innerHTML == '') d.innerHTML = '<h2>HTTP' + (s=='s'?'S':'') + ' Managed Proxies</h2>';\n");
    printf("     d.innerHTML = d.innerHTML + '<p>Host: <a href=\"http' + s + '://' + t + '/squid-internal-mgr/\">' + t + '</a></p>';\n");
    printf(" }}}}\n");
    printf(" x.send(null);\n");
    printf("}\n");
    printf("</script>\n");

    printf("</HEAD>\n");

    printf("<BODY><H1>Cache Manager Interface</H1>\n");

    printf("<P>This is a WWW interface to the instrumentation interface\n");

    printf("for the Squid object cache.</P>\n");

    printf("<HR noshade size=\"1px\">\n");

    printf("<div id=\"Hsmgr\"></div>\n");
    printf("<div id=\"Hmgr\"></div>\n");
    printf("<div id=\"Cmgr\">\n");
    printf("<h2>CGI Managed Proxies</h2>\n");
    printf("<FORM METHOD=\"POST\" ACTION=\"%s\">\n", script_name);

    printf("<TABLE BORDER=\"0\" CELLPADDING=\"10\" CELLSPACING=\"1\">\n");


    if (fp != NULL) {
        int servers = 0;
        char config_line[BUFSIZ];

        while (fgets(config_line, BUFSIZ, fp)) {
            char *server, *comment;
