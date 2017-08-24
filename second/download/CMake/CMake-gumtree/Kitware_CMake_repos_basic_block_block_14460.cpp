{
			state->compress_ratio = 0;
			memset(state->hashtab, 0xff, sizeof(state->hashtab));
			state->first_free = FIRST;
			ret = output_code(f, CLEAR);
			if (ret != ARCHIVE_OK)
				return ret;
		}