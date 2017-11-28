MemBuf *
Ftp::Gateway::htmlifyListEntry(const char *line)
{
    char icon[2048];
    char href[2048 + 40];
    char text[ 2048];
    char size[ 2048];
    char chdir[ 2048 + 40];
    char view[ 2048 + 40];
    char download[ 2048 + 40];
    char link[ 2048 + 40];
    MemBuf *html;
    char prefix[2048];
    ftpListParts *parts;
    *icon = *href = *text = *size = *chdir = *view = *download = *link = '\0';

    debugs(9, 7, HERE << " line ={" << line << "}");

    if (strlen(line) > 1024) {
        html = new MemBuf();
        html->init();
        html->Printf("<tr><td colspan=\"5\">%s</td></tr>\n", line);
        return html;
    }

    if (flags.dir_slash && dirpath && typecode != 'D')
        snprintf(prefix, 2048, "%s/", rfc1738_escape_part(dirpath));
    else
        prefix[0] = '\0';

    if ((parts = ftpListParseParts(line, flags)) == NULL) {
        const char *p;

        html = new MemBuf();
        html->init();
        html->Printf("<tr class=\"entry\"><td colspan=\"5\">%s</td></tr>\n", line);

        for (p = line; *p && xisspace(*p); ++p);
        if (*p && !xisspace(*p))
            flags.listformat_unknown = 1;

        return html;
    }

    if (!strcmp(parts->name, ".") || !strcmp(parts->name, "..")) {
        ftpListPartsFree(&parts);
        return NULL;
    }

    parts->size += 1023;
    parts->size >>= 10;
    parts->showname = xstrdup(parts->name);

    /* {icon} {text} . . . {date}{size}{chdir}{view}{download}{link}\n  */
    xstrncpy(href, rfc1738_escape_part(parts->name), 2048);

    xstrncpy(text, parts->showname, 2048);

    switch (parts->type) {

    case 'd':
        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                 mimeGetIconURL("internal-dir"),
                 "[DIR]");
        strcat(href, "/");  /* margin is allocated above */
        break;

    case 'l':
        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                 mimeGetIconURL("internal-link"),
                 "[LINK]");
        /* sometimes there is an 'l' flag, but no "->" link */

        if (parts->link) {
            char *link2 = xstrdup(html_quote(rfc1738_escape(parts->link)));
            snprintf(link, 2048, " -&gt; <a href=\"%s%s\">%s</a>",
                     *link2 != '/' ? prefix : "", link2,
                     html_quote(parts->link));
            safe_free(link2);
        }

        break;

    case '\0':
        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                 mimeGetIconURL(parts->name),
                 "[UNKNOWN]");
        snprintf(chdir, 2048, "<a href=\"%s/;type=d\"><img border=\"0\" src=\"%s\" "
                 "alt=\"[DIR]\"></a>",
                 rfc1738_escape_part(parts->name),
                 mimeGetIconURL("internal-dir"));
        break;

    case '-':

    default:
        snprintf(icon, 2048, "<img border=\"0\" src=\"%s\" alt=\"%-6s\">",
                 mimeGetIconURL(parts->name),
                 "[FILE]");
        snprintf(size, 2048, " %6" PRId64 "k", parts->size);
        break;
    }

    if (parts->type != 'd') {
        if (mimeGetViewOption(parts->name)) {
            snprintf(view, 2048, "<a href=\"%s%s;type=a\"><img border=\"0\" src=\"%s\" "
                     "alt=\"[VIEW]\"></a>",
                     prefix, href, mimeGetIconURL("internal-view"));
        }

        if (mimeGetDownloadOption(parts->name)) {
            snprintf(download, 2048, "<a href=\"%s%s;type=i\"><img border=\"0\" src=\"%s\" "
                     "alt=\"[DOWNLOAD]\"></a>",
                     prefix, href, mimeGetIconURL("internal-download"));
        }
    }

    /* construct the table row from parts. */
    html = new MemBuf();
    html->init();
    html->Printf("<tr class=\"entry\">"
                 "<td class=\"icon\"><a href=\"%s%s\">%s</a></td>"
                 "<td class=\"filename\"><a href=\"%s%s\">%s</a></td>"
                 "<td class=\"date\">%s</td>"
                 "<td class=\"size\">%s</td>"
                 "<td class=\"actions\">%s%s%s%s</td>"
                 "</tr>\n",
                 prefix, href, icon,
                 prefix, href, html_quote(text),
                 parts->date,
                 size,
                 chdir, view, download, link);

    ftpListPartsFree(&parts);
    return html;
}