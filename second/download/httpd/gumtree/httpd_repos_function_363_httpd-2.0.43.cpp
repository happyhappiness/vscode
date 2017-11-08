void dav_close_propdb(dav_propdb *propdb)
{
    if (propdb->db == NULL)
	return;

    (*propdb->db_hooks->close)(propdb->db);
}