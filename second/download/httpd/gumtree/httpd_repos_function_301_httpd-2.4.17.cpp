static void dav_set_name(dav_db *db, dav_prop_name *pname)
{
    const char *s = db->iter.dptr;

    if (s == NULL) {
        pname->ns = pname->name = NULL;
    }
    else if (*s == ':') {
        pname->ns = "";
        pname->name = s + 1;
    }
    else {
        int id = atoi(s);

        pname->ns = dav_get_ns_table_uri(db, id);
        if (s[1] == ':') {
            pname->name = s + 2;
        }
        else {
            pname->name = ap_strchr_c(s + 2, ':') + 1;
        }
    }
}