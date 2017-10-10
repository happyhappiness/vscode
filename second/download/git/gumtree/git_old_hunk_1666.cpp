
	if (args->verbose)
		fprintf(stderr, "%.*s\n", (int)path.len, path.buf);
	return write_entry(args, sha1, path.buf, path.len, mode);
}

int write_archive_entries(struct archiver_args *args,
		write_archive_entry_fn_t write_entry)
{
	struct archiver_context context;
	struct unpack_trees_options opts;
	struct tree_desc t;
