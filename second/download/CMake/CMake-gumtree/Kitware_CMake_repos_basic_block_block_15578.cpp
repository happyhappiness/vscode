{
		__archive_ppmd7_functions.Ppmd7_EncodeSymbol(
			&(strm->ppmd7_context), &(strm->range_enc),
			*lastrm->next_in++);
		lastrm->avail_in--;
		lastrm->total_in++;
	}