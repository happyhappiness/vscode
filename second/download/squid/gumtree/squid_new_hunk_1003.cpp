        }
    }

    /* construct the table row from parts. */
    html = new MemBuf();
    html->init();
    html->appendf("<tr class=\"entry\">"
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

void
