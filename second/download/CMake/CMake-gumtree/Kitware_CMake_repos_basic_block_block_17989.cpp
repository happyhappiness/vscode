(src[i].options == NULL) {
			dest[i].options = NULL;
		} else {
			// See if the filter is supported only when the
			// options is not NULL. This might be convenient
			// sometimes if the app is actually copying only
			// a partial filter chain with a place holder ID.
			//
			// When options is not NULL, the Filter ID must be
			// supported by us, because otherwise we don't know
			// how big the options are.
			size_t j;
			for (j = 0; src[i].id != features[j].id; ++j) {
				if (features[j].id == LZMA_VLI_UNKNOWN) {
					ret = LZMA_OPTIONS_ERROR;
					goto error;
				}
			}

			// Allocate and copy the options.
			dest[i].options = lzma_alloc(features[j].options_size,
					allocator);
			if (dest[i].options == NULL) {
				ret = LZMA_MEM_ERROR;
				goto error;
			}

			memcpy(dest[i].options, src[i].options,
					features[j].options_size);
		}