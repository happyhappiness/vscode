(bytes_read < 0) {		/* Read error. */
				filter->client_total = filter->client_avail = 0;
				filter->client_next =
				    filter->client_buff = NULL;
				filter->fatal = 1;
				if (avail != NULL)
					*avail = ARCHIVE_FATAL;
				return (NULL);
			}