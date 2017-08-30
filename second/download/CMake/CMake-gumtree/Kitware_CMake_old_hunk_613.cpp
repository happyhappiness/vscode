		return (NULL);

	}



	/* Create a new file entry and copy data from the ISO dir record. */

	file = (struct file_info *)calloc(1, sizeof(*file));

	if (file == NULL) {

