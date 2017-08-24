{

	if (strm->ds == NULL)
		return;
	free(strm->ds->w_buff);
	free(strm->ds->pos_tbl);
	lzx_huffman_free(&(strm->ds->at));
	lzx_huffman_free(&(strm->ds->pt));
	lzx_huffman_free(&(strm->ds->mt));
	lzx_huffman_free(&(strm->ds->lt));
	free(strm->ds);
	strm->ds = NULL;
}