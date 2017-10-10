	fetch_pack_setup();
	if (nr_sought)
		nr_sought = remove_duplicates_in_refs(sought, nr_sought);

	if (!ref) {
		packet_flush(fd[1]);
		die(_("no matching remote head"));
	}
	prepare_shallow_info(&si, shallow);
	ref_cpy = do_fetch_pack(args, fd, ref, sought, nr_sought,
				&si, pack_lockfile);
	reprepare_packed_git();
	update_shallow(args, sought, nr_sought, &si);
