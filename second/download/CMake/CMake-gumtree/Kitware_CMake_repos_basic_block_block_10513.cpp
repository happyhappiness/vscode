(state->eof) {
				ret = lzip_tail(self);
				if (ret != ARCHIVE_OK)
					return (ret);
			}