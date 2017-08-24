{
		parent = (hole - 1)/2;
		parent_id = heap->files[parent]->id;
		if (file_id >= parent_id) {
			heap->files[hole] = file;
			return (ARCHIVE_OK);
		}
		/* Move parent into hole <==> move hole up tree. */
		heap->files[hole] = heap->files[parent];
		hole = parent;
	}