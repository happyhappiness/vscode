(strm->avail_in >= 8) {
				br->cache_buffer =
				    ((uint64_t)strm->next_in[1]) << 56 |
				    ((uint64_t)strm->next_in[0]) << 48 |
				    ((uint64_t)strm->next_in[3]) << 40 |
				    ((uint64_t)strm->next_in[2]) << 32 |
				    ((uint32_t)strm->next_in[5]) << 24 |
				    ((uint32_t)strm->next_in[4]) << 16 |
				    ((uint32_t)strm->next_in[7]) << 8 |
				     (uint32_t)strm->next_in[6];
				strm->next_in += 8;
				strm->avail_in -= 8;
				br->cache_avail += 8 * 8;
				return (1);
			}