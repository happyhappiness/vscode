{
		size_t mapsize = archive_strlen(&(pax->sparse_map));
		pax->sparse_map_padding = 0x1ff & (-(ssize_t)mapsize);
		archive_entry_set_size(entry_main,
		    mapsize + pax->sparse_map_padding + sparse_total);
	}