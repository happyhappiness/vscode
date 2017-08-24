{
		br->cache_buffer =
		   (br->cache_buffer << 16) |
		   ((uint16_t)(*strm->next_in)) << 8 | br->odd;
		strm->next_in++;
		strm->avail_in--;
		br->cache_avail += 16;
		br->have_odd = 0;
	}