struct ref *fetch_pack(struct fetch_pack_args *args,
		       int fd[], struct child_process *conn,
		       const struct ref *ref,
		       const char *dest,
		       struct ref **sought, int nr_sought,
		       struct sha1_array *shallow,
		       char **pack_lockfile)
{
	struct ref *ref_cpy;
	struct shallow_info si;

	fetch_pack_setup();
	if (nr_sought)
		nr_sought = remove_duplicates_in_refs(sought, nr_sought);

	if (!ref) {
		packet_flush(fd[1]);
		die("no matching remote head");
	}
	prepare_shallow_info(&si, shallow);
	ref_cpy = do_fetch_pack(args, fd, ref, sought, nr_sought,
				&si, pack_lockfile);
	reprepare_packed_git();
	update_shallow(args, sought, nr_sought, &si);
	clear_shallow_info(&si);
	return ref_cpy;
}