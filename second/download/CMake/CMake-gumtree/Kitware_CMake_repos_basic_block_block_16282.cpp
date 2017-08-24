{
			file->cur_content->location = location;
			location += file->cur_content->blocks;
			total_block += file->cur_content->blocks;
			/* Next fragment */
			file->cur_content = file->cur_content->next;
		}