{
		ret = __archive_write_output(a, pax->sparse_map.s,
		    archive_strlen(&(pax->sparse_map)));
		if (ret != ARCHIVE_OK)
			return (ret);
		ret = __archive_write_nulls(a, pax->sparse_map_padding);
		if (ret != ARCHIVE_OK)
			return (ret);
		archive_string_empty(&(pax->sparse_map));
	}