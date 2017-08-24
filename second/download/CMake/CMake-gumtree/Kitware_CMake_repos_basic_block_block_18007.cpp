(fc->memusage == NULL) {
			// This filter doesn't have a function to calculate
			// the memory usage and validate the options. Such
			// filters need only little memory, so we use 1 KiB
			// as a good estimate. They also accept all possible
			// options, so there's no need to worry about lack
			// of validation.
			total += 1024;
		} else {
			// Call the filter-specific memory usage calculation
			// function.
			const uint64_t usage
					= fc->memusage(filters[i].options);
			if (usage == UINT64_MAX)
				return UINT64_MAX; // Invalid options

			total += usage;
		}