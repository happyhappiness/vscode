(bytes_skipped < 0) {	/* error */
			filter->fatal = 1;
			return (bytes_skipped);
		}