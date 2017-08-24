(strcmp(key, "use-set") == 0) {
			mtree->output_global_set = (value != NULL)? 1: 0;
			return (ARCHIVE_OK);
		}