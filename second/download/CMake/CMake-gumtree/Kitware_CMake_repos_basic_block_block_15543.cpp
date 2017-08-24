{
		memcpy(lastrm->next_out, lastrm->next_in, bytes);
		lastrm->next_in += bytes;
		lastrm->avail_in -= bytes;
		lastrm->total_in += bytes;
		lastrm->next_out += bytes;
		lastrm->avail_out -= bytes;
		lastrm->total_out += bytes;
	}