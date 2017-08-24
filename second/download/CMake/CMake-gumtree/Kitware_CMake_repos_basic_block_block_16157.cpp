{
		r = _write_path_table(a, type_m, depth, vdd);
		if (r < 0)
			return (r);
		path_table_size += r;
	}