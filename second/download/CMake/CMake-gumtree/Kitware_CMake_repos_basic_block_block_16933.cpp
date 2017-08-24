{
		/* This is not a sparse file but we handle its data as
		 * a sparse block. */
		sparse_list_add(pax, 0, real_size);
		sparse_total = real_size;
	}