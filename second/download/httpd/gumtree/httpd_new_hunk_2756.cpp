        ap_rprintf(r, "<dt><strong>%s:</strong>\n <br /><tt>\n",
                   request_hooks[i].name);
        dump_a_hook(r, request_hooks[i].get);
        ap_rputs("\n  </tt>\n</dt>\n", r);
    }

    ap_rputs
        ("</dl>\n<hr />\n<h2><a name=\"other_hooks\">Other Hooks</a></h2>\n<dl>",
         r);

    for (i = 0; other_hooks[i].name; i++) {
        ap_rprintf(r, "<dt><strong>%s:</strong>\n <br /><tt>\n",
                   other_hooks[i].name);
        dump_a_hook(r, other_hooks[i].get);
        ap_rputs("\n  </tt>\n</dt>\n", r);
    }

    ap_rputs("</dl>\n<hr />\n", r);

    return 0;
}

static int cmp_module_name(const void *a_, const void *b_)
{
    const module * const *a = a_;
    const module * const *b = b_;
    return strcmp((*a)->name, (*b)->name);
}

static apr_array_header_t *get_sorted_modules(apr_pool_t *p)
{
    apr_array_header_t *arr = apr_array_make(p, 64, sizeof(module *));
    module *modp, **entry;
    for (modp = ap_top_module; modp; modp = modp->next) {
        entry = &APR_ARRAY_PUSH(arr, module *);
        *entry = modp;
    }
    qsort(arr->elts, arr->nelts, sizeof(module *), cmp_module_name);
    return arr;
}

static int display_info(request_rec * r)
{
    module *modp = NULL;
    const char *more_info;
    const command_rec *cmd;
    apr_array_header_t *modules = NULL;
    int i;

    if (strcmp(r->handler, "server-info")) {
        return DECLINED;
    }

    r->allowed |= (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET) {
        return DECLINED;
    }

    ap_set_content_type(r, "text/html; charset=ISO-8859-1");

    ap_rputs(DOCTYPE_XHTML_1_0T
             "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
             "<head>\n"
