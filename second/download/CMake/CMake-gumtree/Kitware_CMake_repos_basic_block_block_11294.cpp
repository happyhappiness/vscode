{
				br->cache_buffer =
		 		   (br->cache_buffer << 48) |
				    ((uint64_t)strm->next_in[1]) << 40 |
				    ((uint64_t)strm->next_in[0]) << 32 |
				    ((uint32_t)strm->next_in[3]) << 24 |
				    ((uint32_t)strm->next_in[2]) << 16 |
				    ((uint32_t)strm->next_in[5]) << 8 |
				     (uint32_t)strm->next_in[4];
				strm->next_in += 6;
				strm->avail_in -= 6;
				br->cache_avail += 6 * 8;
				return (1);
			}