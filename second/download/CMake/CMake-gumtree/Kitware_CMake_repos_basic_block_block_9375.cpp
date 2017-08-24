{
		min = (size_t)minimum(request, (int64_t)filter->client_avail);
		filter->client_next += min;
		filter->client_avail -= min;
		request -= min;
		filter->position += min;
		total_bytes_skipped += min;
	}