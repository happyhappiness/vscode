{
			ret = consume_header(self);
			if (ret < ARCHIVE_OK)
				return (ret);
			if (ret == ARCHIVE_EOF) {
				state->eof = 1;
				return (0);
			}
		}