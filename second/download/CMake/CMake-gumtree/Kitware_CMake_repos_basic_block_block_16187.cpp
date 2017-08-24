(file = iso9660->data_file_list.first;
	    file != NULL; file = file->datanext) {

		if (!file->write_content)
			continue;

		if ((offset + (blocks << LOGICAL_BLOCK_BITS)) <
		     file->content.offset_of_temp) {
			if (blocks > 0) {
				r = write_file_contents(a, offset,
				    blocks << LOGICAL_BLOCK_BITS);
				if (r < 0)
					return (r);
			}
			blocks = 0;
			offset = file->content.offset_of_temp;
		}

		file->cur_content = &(file->content);
		do {
			blocks += file->cur_content->blocks;
			/* Next fragment */
			file->cur_content = file->cur_content->next;
		} while (file->cur_content != NULL);
	}