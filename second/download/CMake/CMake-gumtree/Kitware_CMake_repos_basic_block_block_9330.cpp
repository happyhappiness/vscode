{
			a->formats[i].bid = bid;
			a->formats[i].options = options;
			a->formats[i].read_header = read_header;
			a->formats[i].read_data = read_data;
			a->formats[i].read_data_skip = read_data_skip;
			a->formats[i].seek_data = seek_data;
			a->formats[i].cleanup = cleanup;
			a->formats[i].data = format_data;
			a->formats[i].name = name;
			a->formats[i].format_capabilties = format_capabilities;
			a->formats[i].has_encrypted_entries = has_encrypted_entries;
			return (ARCHIVE_OK);
		}