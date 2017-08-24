{
		r = isoent_make_path_table_2(a, &(iso9660->primary),
		    depth, &dir_number);
		if (r < 0)
			return (r);
	}