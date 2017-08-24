(filter->archive->client.cursor !=
				      filter->archive->client.nodes - 1) {
					if (client_switch_proxy(filter,
					    filter->archive->client.cursor + 1)
					    == ARCHIVE_OK)
						continue;
				}