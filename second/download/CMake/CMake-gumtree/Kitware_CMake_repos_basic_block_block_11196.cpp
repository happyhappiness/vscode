(cab_minimum_consume_cfdata(
				    a, cfdata->unconsumed) < 0) {
					*avail = ARCHIVE_FATAL;
					return (NULL);
				}