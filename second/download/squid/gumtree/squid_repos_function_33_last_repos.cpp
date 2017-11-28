static int
read_reply(int s, cachemgr_request * req)
{
    char buf[4 * 1024];
#if _SQUID_WINDOWS_

    int reply;
    char *tmpfile = tempnam(NULL, "tmp0000");
    FILE *fp = fopen(tmpfile, "w+");
#else

    FILE *fp = fdopen(s, "r");
#endif
    /* interpretation states */
    enum {
        isStatusLine, isHeaders, isActions, isBodyStart, isBody, isForward, isEof, isForwardEof, isSuccess, isError
    } istate = isStatusLine;
    int parse_menu = 0;
    const char *action = req->action;
    const char *statusStr = NULL;
    int status = -1;

    if (0 == strlen(req->action))
        parse_menu = 1;
    else if (0 == strcasecmp(req->action, "menu"))
        parse_menu = 1;

    if (fp == NULL) {
#if _SQUID_WINDOWS_
        perror(tmpfile);
        xfree(tmpfile);
#else

        perror("fdopen");
#endif

        close(s);
        return 1;
    }

#if _SQUID_WINDOWS_

    while ((reply=recv(s, buf , sizeof(buf), 0)) > 0)
        fwrite(buf, 1, reply, fp);

    rewind(fp);

#endif

    if (parse_menu)
        action = "menu";

    /* read reply interpreting one line at a time depending on state */
    while (istate < isEof) {
        if (!fgets(buf, sizeof(buf), fp))
            istate = istate == isForward ? isForwardEof : isEof;

        switch (istate) {

        case isStatusLine:
            /* get HTTP status */
            /* uncomment the following if you want to debug headers */
            /* fputs("\r\n\r\n", stdout); */
            status = parse_status_line(buf, &statusStr);
            istate = status == 200 ? isHeaders : isForward;
            /* if cache asks for authentication, we have to reset our info */

            if (status == 401 || status == 407) {
                reset_auth(req);
                status = 403;   /* Forbiden, see comments in case isForward: */
            }

            /* this is a way to pass HTTP status to the Web server */
            if (statusStr)
                printf("Status: %d %s", status, statusStr); /* statusStr has '\n' */

            break;

        case isHeaders:
            /* forward header field */
            if (!strcmp(buf, "\r\n")) {     /* end of headers */
                fputs("Content-Type: text/html\r\n", stdout);   /* add our type */
                istate = isBodyStart;
            }

            if (strncasecmp(buf, "Content-Type:", 13))  /* filter out their type */
                fputs(buf, stdout);

            break;

        case isBodyStart:
            printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");

            printf("<HTML><HEAD><TITLE>CacheMgr@%s: %s</TITLE>\n",
                   req->hostname, action);

            printf("<STYLE type=\"text/css\"><!--BODY{background-color:#ffffff;font-family:verdana,sans-serif}TABLE{background-color:#333333;border:0pt;padding:0pt}TH,TD{background-color:#ffffff;white-space:nowrap}--></STYLE>\n");

            printf("</HEAD><BODY>\n");

            if (parse_menu) {
                printf("<H2><a href=\"%s\">Cache Manager</a> menu for %s:</H2>",
                       menu_url(req, "authenticate"), req->hostname);
                printf("<UL>\n");
            } else {
                printf("<P><A HREF=\"%s\">%s</A>\n<HR noshade size=\"1px\">\n",
                       menu_url(req, "menu"), "Cache Manager menu");
                printf("<PRE>\n");
            }

            istate = isActions;
        /* yes, fall through, we do not want to loose the first line */

        case isActions:
            if (strncmp(buf, "action:", 7) == 0) {
                fputs(" ", stdout);
                fputs(munge_action_line(buf + 7, req), stdout);
                break;
            }
            if (parse_menu) {
                printf("<UL>\n");
            } else {
                printf("<HR noshade size=\"1px\">\n");
                printf("<PRE>\n");
            }

            istate = isBody;
        /* yes, fall through, we do not want to loose the first line */

        case isBody:
        {
            /* interpret [and reformat] cache response */
            MemBuf out;
            out.init();
            if (parse_menu)
                munge_menu_line(out, buf, req);
            else
                munge_other_line(out, buf, req);

            fputs(out.buf, stdout);
        }
        break;

        case isForward:
            /* forward: no modifications allowed */
            /*
             * Note: we currently do not know any way to get browser.reply to
             * 401 to .cgi because web server filters out all auth info. Thus we
             * disable authentication headers for now.
             */
            if (!strncasecmp(buf, "WWW-Authenticate:", 17) || !strncasecmp(buf, "Proxy-Authenticate:", 19));    /* skip */
            else
                fputs(buf, stdout);

            break;

        case isEof:
            /* print trailers */
            if (parse_menu)
                printf("</UL>\n");
            else
                printf("</table></PRE>\n");

            print_trailer();

            istate = isSuccess;

            break;

        case isForwardEof:
            /* indicate that we finished processing an "error" sequence */
            istate = isError;

            break;

        default:
            printf("%s: internal bug: invalid state reached: %d", script_name, istate);

            istate = isError;
        }
    }

    fclose(fp);
#if _SQUID_WINDOWS_

    remove(tmpfile);
    xfree(tmpfile);
    close(s);

#endif

    return 0;
}