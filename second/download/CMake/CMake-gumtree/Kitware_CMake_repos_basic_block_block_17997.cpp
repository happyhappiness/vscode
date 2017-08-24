(j = 0; filters[i].id != features[j].id; ++j)
			if (features[j].id == LZMA_VLI_UNKNOWN)
				return LZMA_OPTIONS_ERROR;