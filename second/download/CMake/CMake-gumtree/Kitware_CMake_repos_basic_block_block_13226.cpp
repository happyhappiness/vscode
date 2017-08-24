{
		xar->unknowntags = tag->next;
		archive_string_free(&(tag->name));
		free(tag);
		if (xar->unknowntags == NULL) {
#if DEBUG
			fprintf(stderr, "UNKNOWNTAG_END:%s\n", name);
#endif
			xar->xmlsts = xar->xmlsts_unknown;
		}
	}