{
		struct cd_segment *segment = calloc(1, sizeof(*segment));
		if (segment == NULL)
			return NULL;
		segment->buff_size = 64 * 1024;
		segment->buff = malloc(segment->buff_size);
		if (segment->buff == NULL) {
			free(segment);
			return NULL;
		}
		segment->p = segment->buff;

		if (zip->central_directory == NULL) {
			zip->central_directory
			    = zip->central_directory_last
			    = segment;
		} else {
			zip->central_directory_last->next = segment;
			zip->central_directory_last = segment;
		}
	}