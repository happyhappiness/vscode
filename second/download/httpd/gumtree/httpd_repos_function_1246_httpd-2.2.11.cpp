static char *find_default_item(char *bogus_name, apr_array_header_t *list)
{
    request_rec r;
    /* Bleah.  I tried to clean up find_item, and it lead to this bit
     * of ugliness.   Note that the fields initialized are precisely
     * those that find_item looks at...
     */
    r.filename = bogus_name;
    r.content_type = r.content_encoding = NULL;
    return find_item(&r, list, 1);
}