{
		bytes_read = (filter->read)(filter, &filter->client_buff);
		if (bytes_read < 0) {
			filter->client_buff = NULL;
			filter->fatal = 1;
			return (bytes_read);
		}

		if (bytes_read == 0) {
			if (filter->archive->client.cursor !=
			      filter->archive->client.nodes - 1) {
				if (client_switch_proxy(filter,
				    filter->archive->client.cursor + 1)
				    == ARCHIVE_OK)
					continue;
			}
			filter->client_buff = NULL;
			filter->end_of_file = 1;
			return (total_bytes_skipped);
		}

		if (bytes_read >= request) {
			filter->client_next =
			    ((const char *)filter->client_buff) + request;
			filter->client_avail = (size_t)(bytes_read - request);
			filter->client_total = bytes_read;
			total_bytes_skipped += request;
			filter->position += request;
			return (total_bytes_skipped);
		}

		filter->position += bytes_read;
		total_bytes_skipped += bytes_read;
		request -= bytes_read;
	}