{
				/* Check for another client object first */
				if (filter->archive->client.cursor !=
				      filter->archive->client.nodes - 1) {
					if (client_switch_proxy(filter,
					    filter->archive->client.cursor + 1)
					    == ARCHIVE_OK)
						continue;
				}
				/* Premature end-of-file. */
				filter->client_total = filter->client_avail = 0;
				filter->client_next =
				    filter->client_buff = NULL;
				filter->end_of_file = 1;
				/* Return whatever we do have. */
				if (avail != NULL)
					*avail = filter->avail;
				return (NULL);
			}