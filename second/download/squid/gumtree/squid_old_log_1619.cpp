out.Printf("<%s colspan=\"%d\" align=\"%s\">%s</%s>",
                   ttag, column_span,
                   is_header ? "center" : is_number(cell) ? "right" : "left",
                   html_quote(cell), ttag);