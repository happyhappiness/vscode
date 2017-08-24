{
		iso9660->joliet.location_type_L_path_table = blocks;
		blocks += iso9660->joliet.path_table_block;
		iso9660->joliet.location_type_M_path_table = blocks;
		blocks += iso9660->joliet.path_table_block;
	}