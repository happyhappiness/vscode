(i = 0; i < count; ++i) {
			const lzma_filter_coder *const fc
					= coder_find(options[i].id);
			if (fc == NULL || fc->init == NULL)
				return LZMA_OPTIONS_ERROR;

			filters[i].id = options[i].id;
			filters[i].init = fc->init;
			filters[i].options = options[i].options;
		}