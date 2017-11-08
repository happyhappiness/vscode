static module *find_module(server_rec *s, const char *name)
{
    module *found = ap_find_linked_module(name);

    /* search prelinked stuff */
    if (!found) {
        ap_module_symbol_t *current = ap_prelinked_module_symbols;

        for (; current->name; ++current) {
            if (!strcmp(current->name, name)) {
                found = current->modp;
                break;
            }
        }
    }

    /* search dynamic stuff */
    if (!found) {
        APR_OPTIONAL_FN_TYPE(ap_find_loaded_module_symbol) *check_symbol =
            APR_RETRIEVE_OPTIONAL_FN(ap_find_loaded_module_symbol);

        if (check_symbol) {
            found = check_symbol(s, name);
        }
    }

    return found;
}