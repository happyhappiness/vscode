{
			ret = next_code(self);
			if (ret == -1)
				state->end_of_stream = ret;
			else if (ret != ARCHIVE_OK)
				return (ret);
		}