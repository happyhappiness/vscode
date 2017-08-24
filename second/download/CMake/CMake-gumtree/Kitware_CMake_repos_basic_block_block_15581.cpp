{
			*lastrm->next_out++ = *p++;
			lastrm->avail_out--;
			lastrm->total_out++;
			strm->buff_bytes--;
		}