
    ap_rputs("</dl>\n<hr />\n", r);

    return 0;
}

static int cmp_module_name(const void *a_, const void *b_)
{
    const module * const *a = a_;
    const module * const *b = b_;
    return strcmp((*a)->name, (*b)->name);
}
