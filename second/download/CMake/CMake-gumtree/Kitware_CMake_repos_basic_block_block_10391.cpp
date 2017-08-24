{
				n = (size_t)(RPM_LEAD_SIZE - rpm->total_in);
				used += n;
				b += n;
				rpm->state = ST_HEADER;
				rpm->hpos = 0;
				rpm->hlen = 0;
				rpm->first_header = 1;
			}