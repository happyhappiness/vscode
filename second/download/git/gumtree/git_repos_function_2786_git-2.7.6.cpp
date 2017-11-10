static void get_loose_object(char *name)
{
	select_getanyfile();
	hdr_cache_forever();
	send_local_file("application/x-git-loose-object", name);
}