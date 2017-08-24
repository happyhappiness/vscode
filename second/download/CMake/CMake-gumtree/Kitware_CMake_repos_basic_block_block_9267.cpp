{
		/* Need to add "NONE" type filter at the end of the filter chain */
		tmp = a->filter;
		while (tmp->upstream)
			tmp = tmp->upstream;
		tmp->upstream = filter;
	}