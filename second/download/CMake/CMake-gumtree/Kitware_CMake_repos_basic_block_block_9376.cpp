{
		min = (size_t)minimum(request, (int64_t)filter->avail);
		filter->next += min;
		filter->avail -= min;
		request -= min;
		filter->position += min;
		total_bytes_skipped += min;
	}