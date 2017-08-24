{
		parent = (hole - 1)/2;
		parent_key = heap->files[parent]->key;
		if (file_key >= parent_key) {
			heap->files[hole] = file;
			return (ARCHIVE_OK);
		}
		/* Move parent into hole <==> move hole up tree. */
		heap->files[hole] = heap->files[parent];
		hole = parent;
	}