(j = 0; src[i].id != features[j].id; ++j) {
				if (features[j].id == LZMA_VLI_UNKNOWN) {
					ret = LZMA_OPTIONS_ERROR;
					goto error;
				}
			}