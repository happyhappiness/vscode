{
		struct archive_write *a = (struct archive_write *)_a;
		struct mtree_writer *mtree;

		mtree = (struct mtree_writer *)a->format_data;

		/* Set to output a mtree archive in classic format. */
		mtree->classic = 1;
		/* Basically, mtree classic format uses '/set' global
		 * value. */
		mtree->output_global_set = 1;
	}