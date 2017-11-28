
        while (x && *x == '\t') {
            ++column_span;
            ++x;
        }

        out.appendf("<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                    ttag, column_span,
                    is_header ? "center" : is_number(cell) ? "right" : "left",
                    html_quote(cell), ttag);
    }

    xfree(buf_copy);
    /* record ends */
    out.append("</tr>\n", 6);
    next_is_header = is_header && strstr(buf, "\t\t");
