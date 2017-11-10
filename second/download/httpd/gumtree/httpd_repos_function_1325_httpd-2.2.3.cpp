static int dump_a_hook(request_rec * r, hook_get_t hook_get)
{
    int i;
    char qs;
    hook_struct_t *elts;
    apr_array_header_t *hooks = hook_get();

    if (!hooks) {
        return 0;
    }

    if (r->args && strcasecmp(r->args, "hooks") == 0) {
        qs = '?';
    }
    else {
        qs = '#';
    }

    elts = (hook_struct_t *) hooks->elts;

    for (i = 0; i < hooks->nelts; i++) {
        ap_rprintf(r,
                   "&nbsp;&nbsp; %02d <a href=\"%c%s\">%s</a> <br/>",
                   elts[i].nOrder, qs, elts[i].szName, elts[i].szName);
    }
    return 0;
}