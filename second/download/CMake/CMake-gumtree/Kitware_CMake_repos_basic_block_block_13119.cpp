{
		struct unknown_tag *tag;

		tag = xar->unknowntags;
		xar->unknowntags = tag->next;
		archive_string_free(&(tag->name));
		free(tag);
	}