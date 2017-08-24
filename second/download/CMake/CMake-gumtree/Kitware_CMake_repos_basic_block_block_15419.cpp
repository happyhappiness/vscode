(;file != NULL; file = file->next) {
			if (file->next == NULL ||
			    file->next->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}