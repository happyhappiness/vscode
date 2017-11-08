static int write_tar_archive(const struct archiver *ar,
			     struct archiver_args *args)
{
	int err = 0;

	if (args->commit_sha1)
		err = write_global_extended_header(args);
	if (!err)
		err = write_archive_entries(args, write_tar_entry);
	if (!err)
		write_trailer();
	return err;
}