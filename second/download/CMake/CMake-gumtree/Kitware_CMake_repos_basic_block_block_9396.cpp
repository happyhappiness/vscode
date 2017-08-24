{
	case SEEK_CUR:
		/* Adjust the offset and use SEEK_SET instead */
		offset += filter->position;			
	case SEEK_SET:
		cursor = 0;
		while (1)
		{
			if (client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    client->dataset[cursor].begin_position +
			      client->dataset[cursor].total_size - 1 > offset ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
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
		offset -= client->dataset[cursor].begin_position;
		if (offset < 0
		    || offset > client->dataset[cursor].total_size)
			return ARCHIVE_FATAL;
		if ((r = client_seek_proxy(filter, offset, SEEK_SET)) < 0)
			return r;
		break;

	case SEEK_END:
		cursor = 0;
		while (1) {
			if (client->dataset[cursor].begin_position < 0 ||
			    client->dataset[cursor].total_size < 0 ||
			    cursor + 1 >= client->nodes)
				break;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
			r = client_switch_proxy(filter, cursor);
			if (r != ARCHIVE_OK)
				return r;
			if ((r = client_seek_proxy(filter, 0, SEEK_END)) < 0)
				return r;
			client->dataset[cursor].total_size = r;
			r = client->dataset[cursor].begin_position +
				client->dataset[cursor].total_size;
			if (cursor + 1 >= client->nodes)
				break;
			client->dataset[++cursor].begin_position = r;
		}
		while (1) {
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
		offset = (r + offset) - client->dataset[cursor].begin_position;
		if ((r = client_switch_proxy(filter, cursor)) != ARCHIVE_OK)
			return r;
		r = client_seek_proxy(filter, offset, SEEK_SET);
		if (r < ARCHIVE_OK)
			return r;
		break;

	default:
		return (ARCHIVE_FATAL);
	}