{
			// The order of the filters is reversed in the
			// encoder. It allows more efficient handling
			// of the uncompressed data.
			const size_t j = count - i - 1;

			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[j].id = options[i].id;
			filters[j].init = fc->init;
			filters[j].options = options[i].options;
		}