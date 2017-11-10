void grep_source_load_driver(struct grep_source *gs)
{
	if (gs->driver)
		return;

	grep_attr_lock();
	if (gs->path)
		gs->driver = userdiff_find_by_path(gs->path);
	if (!gs->driver)
		gs->driver = userdiff_find_by_name("default");
	grep_attr_unlock();
}