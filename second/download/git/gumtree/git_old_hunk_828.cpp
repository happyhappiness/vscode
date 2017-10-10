				&si, pack_lockfile);
	reprepare_packed_git();
	update_shallow(args, sought, nr_sought, &si);
	clear_shallow_info(&si);
	return ref_cpy;
}
