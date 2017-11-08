static const char *dav_get_ns_table_uri(dav_db *db, int ns_id)
{
    const char *p = db->ns_table.buf + sizeof(dav_propdb_metadata);

    while (ns_id--)
        p += strlen(p) + 1;

    return p;
}