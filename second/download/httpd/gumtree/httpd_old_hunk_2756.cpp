        ap_rprintf(r, "<dt><strong>%s:</strong>\n <br /><tt>\n",
                   request_hooks[i].name);
        dump_a_hook(r, request_hooks[i].get);
        ap_rputs("\n  </tt>\n</dt>\n", r);
    }

    ap_rputs("</dl>\n<hr />\n", r);

    return 0;
}

static int display_info(request_rec * r)
{
    module *modp = NULL;
    server_rec *serv = r->server;
    const char *more_info;
    const command_rec *cmd = NULL;
    int comma = 0;

    if (strcmp(r->handler, "server-info"))
        return DECLINED;

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
        return DECLINED;

    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

    ap_rputs(DOCTYPE_XHTML_1_0T
             "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
             "<head>\n"
