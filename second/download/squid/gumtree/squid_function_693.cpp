static void
auth_html(const char *host, int port, const char *user_name)
{
    FILE *fp;
    int need_host = 1;

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
            strtok(config_line, "\r\n");

            if (config_line[0] == '#')
                continue;

            if (config_line[0] == '\0')
                continue;

            if ((server = strtok(config_line, " \t")) == NULL)
                continue;

            if (strchr(server, '*') || strchr(server, '[') || strchr(server, '?')) {
                need_host = -1;
                continue;
            }

            comment = strtok(NULL, "");

            if (comment)
                while (*comment == ' ' || *comment == '\t')
                    ++comment;

            if (!comment || !*comment)
                comment = server;

            if (!servers)
                printf("<TR><TH ALIGN=\"left\">Cache Server:</TH><TD><SELECT id=\"server\" NAME=\"server\">\n");

            printf("<OPTION VALUE=\"%s\"%s>%s</OPTION>\n", server, (servers || *host) ? "" : " SELECTED", comment);
            ++servers;
        }

        if (servers) {
            if (need_host == 1 && !*host)
                need_host = 0;

            if (need_host)
                printf("<OPTION VALUE=\"\"%s>Other</OPTION>\n", (*host) ? " SELECTED" : "");

            printf("</SELECT></TR>\n");
        }

        fclose(fp);
    }

    if (need_host) {
        if (need_host == 1 && !*host)
            host = "localhost";

        printf("<TR><TH ALIGN=\"left\">Cache Host:</TH><TD><INPUT NAME=\"host\" ");

        printf("size=\"30\" VALUE=\"%s\"></TD></TR>\n", host);

        printf("<TR><TH ALIGN=\"left\">Cache Port:</TH><TD><INPUT NAME=\"port\" ");

        printf("size=\"30\" VALUE=\"%d\"></TD></TR>\n", port);
    }

    printf("<TR><TH ALIGN=\"left\">Manager name:</TH><TD><INPUT NAME=\"user_name\" ");

    printf("size=\"30\" VALUE=\"%s\"></TD></TR>\n", user_name);

    printf("<TR><TH ALIGN=\"left\">Password:</TH><TD><INPUT TYPE=\"password\" NAME=\"passwd\" ");

    printf("size=\"30\" VALUE=\"\"></TD></TR>\n");

    printf("</TABLE><BR CLEAR=\"all\">\n");

    printf("<INPUT TYPE=\"submit\" VALUE=\"Continue...\">\n");

    printf("</FORM></div>\n");

    printf("<script type=\"text/javascript\">\n");
    printf("var s = document.getElementById(\"server\");\n");
    printf("for (var i = 0; i < s.childElementCount; i++) {\n");
    printf(" TS(s.children[i].value, '');\n");
    printf(" TS(s.children[i].value, 's');\n");
    printf("}</script>\n");

    print_trailer();
}