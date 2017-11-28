
        while (x && *x == '\t') {
            ++column_span;
            ++x;
        }

        l += snprintf(html + l, sizeof(html) - l, "<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                      ttag, column_span,
                      is_header ? "center" : is_number(cell) ? "right" : "left",
                      html_quote(cell), ttag);
    }

    xfree(buf_copy);
    /* record ends */
    snprintf(html + l, sizeof(html) - l, "</tr>\n");
    next_is_header = is_header && strstr(buf, "\t\t");
    ++table_line_num;
    return html;
}

static const char *
munge_action_line(const char *_buf, cachemgr_request * req)
{
    static char html[2 * 1024];
