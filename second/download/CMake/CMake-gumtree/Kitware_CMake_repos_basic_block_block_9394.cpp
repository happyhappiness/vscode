{
			r = client_switch_proxy(filter, cursor);
			if (r != ARCHIVE_OK)
				return r;
			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
				return r;
			client->dataset[cursor].total_size = r;
			if (client->dataset[cursor].begin_position +
			    client->dataset[cursor].total_size - 1 > offset ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}