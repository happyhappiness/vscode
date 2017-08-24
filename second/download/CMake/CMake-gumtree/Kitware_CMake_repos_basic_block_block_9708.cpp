(a->metadata_filter_func) {
		if (!a->metadata_filter_func(&(a->archive),
		    a->metadata_filter_data, entry))
			return (ARCHIVE_RETRY);
	}