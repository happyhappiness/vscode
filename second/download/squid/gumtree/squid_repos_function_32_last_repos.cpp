static const char *
munge_action_line(const char *_buf, cachemgr_request * req)
{
    static char html[2 * 1024];
    char *buf = xstrdup(_buf);
    char *x = buf;
    const char *action, *description;
    char *p;

    if ((p = strchr(x, '\n')))
        *p = '\0';
    action = xstrtok(&x, '\t');
    if (!action) {
        xfree(buf);
        return "";
    }
    description = xstrtok(&x, '\t');
    if (!description)
        description = action;
    snprintf(html, sizeof(html), " <a href=\"%s\">%s</a>", menu_url(req, action), description);
    xfree(buf);
    return html;
}