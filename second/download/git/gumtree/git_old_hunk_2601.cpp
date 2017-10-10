	write_or_die(keep_fd, keep_msg, strlen(keep_msg));
	if (close(keep_fd))
		die_errno("failed to write keep file");

	snprintf(name, sizeof(name), "%s/pack/pack-%s.pack",
		 get_object_directory(), sha1_to_hex(pack_data->sha1));
	if (move_temp_to_file(pack_data->pack_name, name))
		die("cannot store pack file");

	snprintf(name, sizeof(name), "%s/pack/pack-%s.idx",
		 get_object_directory(), sha1_to_hex(pack_data->sha1));
	if (move_temp_to_file(curr_index_name, name))
		die("cannot store index file");
	free((void *)curr_index_name);
	return name;
}

static void unkeep_all_packs(void)
