                                   really an href */
    }
    if (!strcasecmp(menu, "formatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "semiformatted")) {
        ap_rvputs(r, "<pre>          <a href=\"", href, "\">", text,
               "</a></pre>\n", NULL);
    }
    else if (!strcasecmp(menu, "unformatted")) {
        ap_rvputs(r, "<a href=\"", href, "\">", text, "</a>", NULL);
    }
    return;
}

static void menu_footer(request_rec *r)
