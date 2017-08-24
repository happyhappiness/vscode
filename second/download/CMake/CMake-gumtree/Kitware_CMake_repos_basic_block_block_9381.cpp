{
			if (r + offset >=
			    client->dataset[cursor].begin_position)
				break;
			offset += client->dataset[cursor].total_size;
			if (cursor == 0)
				break;
			cursor--;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
		}