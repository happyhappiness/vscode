static dav_error * dav_core_patch_validate(const dav_resource *resource,
                                           const apr_xml_elem *elem,
                                           int operation, void **context,
                                           int *defer_to_dead)
{
    /* all of our writable props go in the dead prop database */
    *defer_to_dead = 1;

    return NULL;
}