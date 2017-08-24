{
			// This filter doesn't have a function to calculate
			// the memory usage and validate the options. Such
			// filters need only little memory, so we use 1 KiB
			// as a good estimate. They also accept all possible
			// options, so there's no need to worry about lack
			// of validation.
			total += 1024;
		}