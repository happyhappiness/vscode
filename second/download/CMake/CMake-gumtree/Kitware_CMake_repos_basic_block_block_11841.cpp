(file_key >= parent_key) {
			heap->files[hole] = file;
			return (ARCHIVE_OK);
		}