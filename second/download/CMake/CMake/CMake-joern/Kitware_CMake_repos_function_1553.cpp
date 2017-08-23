int
archive_read_disk_set_standard_lookup(struct archive *a)
{
	struct name_cache *ucache = malloc(sizeof(struct name_cache));
	struct name_cache *gcache = malloc(sizeof(struct name_cache));

	if (ucache == NULL || gcache == NULL) {
		archive_set_error(a, ENOMEM,
		    "Can't allocate uname/gname lookup cache");
		free(ucache);
		free(gcache);
		return (ARCHIVE_FATAL);
	}

	memset(ucache, 0, sizeof(*ucache));
	ucache->archive = a;
	ucache->size = name_cache_size;
	memset(gcache, 0, sizeof(*gcache));
	gcache->archive = a;
	gcache->size = name_cache_size;

	archive_read_disk_set_gname_lookup(a, gcache, lookup_gname, cleanup);
	archive_read_disk_set_uname_lookup(a, ucache, lookup_uname, cleanup);

	return (ARCHIVE_OK);
}