void register_tempfile(struct tempfile *tempfile, const char *path)
{
	prepare_tempfile_object(tempfile);
	strbuf_add_absolute_path(&tempfile->filename, path);
	tempfile->owner = getpid();
	tempfile->active = 1;
}