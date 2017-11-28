
        while (x && *x == '\t') {
            ++column_span;
            ++x;
        }

        out.Printf("<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                   ttag, column_span,
                   is_header ? "center" : is_number(cell) ? "right" : "left",
                   html_quote(cell), ttag);
    }

    xfree(buf_copy);
    /* record ends */
    out.append("</tr>\n", 6);
    next_is_header = is_header && strstr(buf, "\t\t");
    ++table_line_num;
}

static const char *
munge_action_line(const char *_buf, cachemgr_request * req)
{
    static char html[2 * 1024];
