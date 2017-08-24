(hole > 0) {
		parent = (hole - 1)/2;
		parent_offset = heap->reqs[parent].offset;
		if (offset >= parent_offset) {
			heap->reqs[hole].offset = offset;
			heap->reqs[hole].file = file;
			return (ARCHIVE_OK);
		}
		/* Move parent into hole <==> move hole up tree. */
		heap->reqs[hole] = heap->reqs[parent];
		hole = parent;
	}