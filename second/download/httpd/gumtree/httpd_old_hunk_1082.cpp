    }

    if (d->style_sheet != NULL) {
        ap_rvputs(r, "  <link rel=\"stylesheet\" href=\"", d->style_sheet,
                "\" type=\"text/css\"", xhtml ? " />\n" : ">\n", NULL);
    }
    ap_rvputs(r, " </head>\n <body>\n", NULL);
}

static void push_item(apr_array_header_t *arr, char *type, const char *to,
                      const char *path, const char *data)
{
