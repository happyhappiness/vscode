{
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