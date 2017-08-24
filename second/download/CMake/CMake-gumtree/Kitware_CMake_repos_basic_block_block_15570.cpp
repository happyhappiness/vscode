{
		*lastrm->next_out++ = b;
		lastrm->avail_out--;
		lastrm->total_out++;
		return;
	}