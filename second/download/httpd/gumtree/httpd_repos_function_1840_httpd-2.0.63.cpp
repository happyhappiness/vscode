ap_directive_t *ap_add_node(ap_directive_t **parent, ap_directive_t *current, 
                            ap_directive_t *toadd, int child)
{
    if (current == NULL) {
        /* we just started a new parent */
        if (*parent != NULL) {
            (*parent)->first_child = toadd;
            toadd->parent = *parent;
        }
        if (child) {
            /* First item in config file or container is a container */
            *parent = toadd;
            return NULL;
        }
        return toadd;
    }
    current->next = toadd;
    toadd->parent = *parent;
    if (child) {
        /* switch parents, navigate into child */
        *parent = toadd;
        return NULL;
    }
    return toadd;
}