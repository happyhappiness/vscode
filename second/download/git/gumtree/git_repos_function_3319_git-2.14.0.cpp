static int write_zip_archive(const struct archiver *ar,
			     struct archiver_args *args)
{
	int err;

	git_config(archive_zip_config, NULL);

	dos_time(&args->time, &zip_date, &zip_time);

	strbuf_init(&zip_dir, 0);

	err = write_archive_entries(args, write_zip_entry);
	if (!err)
		write_zip_trailer(args->commit_sha1);

	strbuf_release(&zip_dir);

	return err;
}