(client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    cursor + 1 >= client->nodes)
				break;