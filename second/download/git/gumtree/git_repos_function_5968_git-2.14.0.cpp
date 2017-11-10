void prune_packed_objects(int opts)
{
	if (opts & PRUNE_PACKED_VERBOSE)
		progress = start_progress_delay(_("Removing duplicate objects"),
			256, 95, 2);

	for_each_loose_file_in_objdir(get_object_directory(),
				      prune_object, NULL, prune_subdir, &opts);

	/* Ensure we show 100% before finishing progress */
	display_progress(progress, 256);
	stop_progress(&progress);
}