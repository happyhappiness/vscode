        ap_rvputs(r, "  <link rel=\"stylesheet\" href=\"", d->style_sheet,
                "\" type=\"text/css\"", xhtml ? " />\n" : ">\n", NULL);
    }
    if (d->head_insert != NULL) {
        ap_rputs(d->head_insert, r);
    }
    ap_rputs(" </head>\n <body>\n", r);
}

static void push_item(apr_array_header_t *arr, char *type, const char *to,
                      const char *path, const char *data)
{
    struct item *p = (struct item *) apr_array_push(arr);
