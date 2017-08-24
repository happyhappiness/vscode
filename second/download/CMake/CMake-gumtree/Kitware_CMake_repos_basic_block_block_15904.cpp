{
		isoent_setup_directory_location(iso9660, blocks,
		    &(iso9660->joliet));
		blocks += iso9660->joliet.total_dir_block;
	}