static int module_find_hook(module * modp, hook_get_t hook_get)
{
    int i;
    apr_array_header_t *hooks = hook_get();
    hook_struct_t *elts;

    if (!hooks) {
        return 0;
    }

    elts = (hook_struct_t *) hooks->elts;

    for (i = 0; i < hooks->nelts; i++) {
        if (strcmp(elts[i].szName, modp->name) == 0) {
            return 1;
        }
    }

    return 0;
}