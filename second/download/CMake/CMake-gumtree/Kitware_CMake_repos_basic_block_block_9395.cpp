(client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    client->dataset[cursor].begin_position +
			      client->dataset[cursor].total_size - 1 > offset ||
			    cursor + 1 >= client->nodes)
				break;