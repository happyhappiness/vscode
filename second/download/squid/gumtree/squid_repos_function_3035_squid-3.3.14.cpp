void
storeReplAdd(const char *type, REMOVALPOLICYCREATE * create)
{
    int i;

    /* find the number of currently known repl types */
    for (i = 0; storerepl_list && storerepl_list[i].typestr; ++i) {
        if (strcmp(storerepl_list[i].typestr, type) == 0) {
            debugs(20, DBG_IMPORTANT, "WARNING: Trying to load store replacement policy " << type << " twice.");
            return;
        }
    }

    /* add the new type */
    storerepl_list = static_cast<storerepl_entry_t *>(xrealloc(storerepl_list, (i + 2) * sizeof(storerepl_entry_t)));

    memset(&storerepl_list[i + 1], 0, sizeof(storerepl_entry_t));

    storerepl_list[i].typestr = type;

    storerepl_list[i].create = create;
}