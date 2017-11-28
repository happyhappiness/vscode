static const char *
munge_menu_line(const char *buf, cachemgr_request * req)
{
    char *x;
    const char *a;
    const char *d;
    const char *p;
    char *a_url;
    char *buf_copy;
    static char html[2 * 1024];

    if (strlen(buf) < 1)
        return buf;

    if (*buf != ' ')
        return buf;

    buf_copy = x = xstrdup(buf);

    a = xstrtok(&x, '\t');

    d = xstrtok(&x, '\t');

    p = xstrtok(&x, '\t');

    a_url = xstrdup(menu_url(req, a));

    /* no reason to give a url for a disabled action */
    if (!strcmp(p, "disabled"))
        snprintf(html, sizeof(html), "<LI type=\"circle\">%s (disabled)<A HREF=\"%s\">.</A>\n", d, a_url);
    else
        /* disable a hidden action (requires a password, but password is not in squid.conf) */
        if (!strcmp(p, "hidden"))
            snprintf(html, sizeof(html), "<LI type=\"circle\">%s (hidden)<A HREF=\"%s\">.</A>\n", d, a_url);
        else
            /* disable link if authentication is required and we have no password */
            if (!strcmp(p, "protected") && !req->passwd)
                snprintf(html, sizeof(html), "<LI type=\"circle\">%s (requires <a href=\"%s\">authentication</a>)<A HREF=\"%s\">.</A>\n",
                         d, menu_url(req, "authenticate"), a_url);
            else
                /* highlight protected but probably available entries */
                if (!strcmp(p, "protected"))
                    snprintf(html, sizeof(html), "<LI type=\"square\"><A HREF=\"%s\"><font color=\"#FF0000\">%s</font></A>\n",
                             a_url, d);

    /* public entry or unknown type of protection */
                else
                    snprintf(html, sizeof(html), "<LI type=\"disk\"><A HREF=\"%s\">%s</A>\n", a_url, d);

    xfree(a_url);

    xfree(buf_copy);

    return html;
}