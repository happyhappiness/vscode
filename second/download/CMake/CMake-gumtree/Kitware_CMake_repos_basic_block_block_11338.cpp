{
	struct lzx_dec *ds = strm->ds;
	struct lzx_br *br = &(ds->br);
	int i, r;

	for (;;) {
		switch (ds->state) {
		case ST_RD_TRANSLATION:
			if (!lzx_br_read_ahead(strm, br, 1)) {
				ds->state = ST_RD_TRANSLATION;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			ds->translation = lzx_br_bits(br, 1);
			lzx_br_consume(br, 1);
			/* FALL THROUGH */
		case ST_RD_TRANSLATION_SIZE:
			if (ds->translation) {
				if (!lzx_br_read_ahead(strm, br, 32)) {
					ds->state = ST_RD_TRANSLATION_SIZE;
					if (last)
						goto failed;
					return (ARCHIVE_OK);
				}
				ds->translation_size = lzx_br_bits(br, 16);
				lzx_br_consume(br, 16);
				ds->translation_size <<= 16;
				ds->translation_size |= lzx_br_bits(br, 16);
				lzx_br_consume(br, 16);
			}
			/* FALL THROUGH */
		case ST_RD_BLOCK_TYPE:
			if (!lzx_br_read_ahead(strm, br, 3)) {
				ds->state = ST_RD_BLOCK_TYPE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			ds->block_type = lzx_br_bits(br, 3);
			lzx_br_consume(br, 3);
			/* Check a block type. */
			switch (ds->block_type) {
			case VERBATIM_BLOCK:
			case ALIGNED_OFFSET_BLOCK:
			case UNCOMPRESSED_BLOCK:
				break;
			default:
				goto failed;/* Invalid */
			}
			/* FALL THROUGH */
		case ST_RD_BLOCK_SIZE:
			if (!lzx_br_read_ahead(strm, br, 24)) {
				ds->state = ST_RD_BLOCK_SIZE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			ds->block_size = lzx_br_bits(br, 8);
			lzx_br_consume(br, 8);
			ds->block_size <<= 16;
			ds->block_size |= lzx_br_bits(br, 16);
			lzx_br_consume(br, 16);
			if (ds->block_size == 0)
				goto failed;
			ds->block_bytes_avail = ds->block_size;
			if (ds->block_type != UNCOMPRESSED_BLOCK) {
				if (ds->block_type == VERBATIM_BLOCK)
					ds->state = ST_RD_VERBATIM;
				else
					ds->state = ST_RD_ALIGNED_OFFSET;
				break;
			}
			/* FALL THROUGH */
		case ST_RD_ALIGNMENT:
			/*
			 * Handle an Uncompressed Block.
			 */
			/* Skip padding to align following field on
			 * 16-bit boundary. */
			if (lzx_br_is_unaligned(br))
				lzx_br_consume_unaligned_bits(br);
			else {
				if (lzx_br_read_ahead(strm, br, 16))
					lzx_br_consume(br, 16);
				else {
					ds->state = ST_RD_ALIGNMENT;
					if (last)
						goto failed;
					return (ARCHIVE_OK);
				}
			}
			/* Preparation to read repeated offsets R0,R1 and R2. */
			ds->rbytes_avail = 0;
			ds->state = ST_RD_R0;
			/* FALL THROUGH */
		case ST_RD_R0:
		case ST_RD_R1:
		case ST_RD_R2:
			do {
				uint16_t u16;
				/* Drain bits in the cache buffer of
				 * bit-stream. */
				if (lzx_br_has(br, 32)) {
					u16 = lzx_br_bits(br, 16);
					lzx_br_consume(br, 16);
					archive_le16enc(ds->rbytes, u16);
					u16 = lzx_br_bits(br, 16);
					lzx_br_consume(br, 16);
					archive_le16enc(ds->rbytes+2, u16);
					ds->rbytes_avail = 4;
				} else if (lzx_br_has(br, 16)) {
					u16 = lzx_br_bits(br, 16);
					lzx_br_consume(br, 16);
					archive_le16enc(ds->rbytes, u16);
					ds->rbytes_avail = 2;
				}
				if (ds->rbytes_avail < 4 && ds->br.have_odd) {
					ds->rbytes[ds->rbytes_avail++] =
					    ds->br.odd;
					ds->br.have_odd = 0;
				}
				while (ds->rbytes_avail < 4) {
					if (strm->avail_in <= 0) {
						if (last)
							goto failed;
						return (ARCHIVE_OK);
					}
					ds->rbytes[ds->rbytes_avail++] =
					    *strm->next_in++;
					strm->avail_in--;
				}
				ds->rbytes_avail = 0;
				if (ds->state == ST_RD_R0) {
					ds->r0 = archive_le32dec(ds->rbytes);
					if (ds->r0 < 0)
						goto failed;
					ds->state = ST_RD_R1;
				} else if (ds->state == ST_RD_R1) {
					ds->r1 = archive_le32dec(ds->rbytes);
					if (ds->r1 < 0)
						goto failed;
					ds->state = ST_RD_R2;
				} else if (ds->state == ST_RD_R2) {
					ds->r2 = archive_le32dec(ds->rbytes);
					if (ds->r2 < 0)
						goto failed;
					/* We've gotten all repeated offsets. */
					ds->state = ST_COPY_UNCOMP1;
				}
			} while (ds->state != ST_COPY_UNCOMP1);
			/* FALL THROUGH */
		case ST_COPY_UNCOMP1:
			/*
			 * Copy bytes form next_in to next_out directly.
			 */
			while (ds->block_bytes_avail) {
				int l;

				if (strm->avail_out <= 0)
					/* Output buffer is empty. */
					return (ARCHIVE_OK);
				if (strm->avail_in <= 0) {
					/* Input buffer is empty. */
					if (last)
						goto failed;
					return (ARCHIVE_OK);
				}
				l = (int)ds->block_bytes_avail;
				if (l > ds->w_size - ds->w_pos)
					l = ds->w_size - ds->w_pos;
				if (l > strm->avail_out)
					l = (int)strm->avail_out;
				if (l > strm->avail_in)
					l = (int)strm->avail_in;
				memcpy(strm->next_out, strm->next_in, l);
				memcpy(&(ds->w_buff[ds->w_pos]),
				    strm->next_in, l);
				strm->next_in += l;
				strm->avail_in -= l;
				strm->next_out += l;
				strm->avail_out -= l;
				strm->total_out += l;
				ds->w_pos = (ds->w_pos + l) & ds->w_mask;
				ds->block_bytes_avail -= l;
			}
			/* FALL THROUGH */
		case ST_COPY_UNCOMP2:
			/* Re-align; skip padding byte. */
			if (ds->block_size & 1) {
				if (strm->avail_in <= 0) {
					/* Input buffer is empty. */
					ds->state = ST_COPY_UNCOMP2;
					if (last)
						goto failed;
					return (ARCHIVE_OK);
				}
				strm->next_in++;
				strm->avail_in --;
			}
			/* This block ended. */
			ds->state = ST_RD_BLOCK_TYPE;
			return (ARCHIVE_EOF);
			/********************/
		case ST_RD_ALIGNED_OFFSET:
			/*
			 * Read Aligned offset tree.
			 */
			if (!lzx_br_read_ahead(strm, br, 3 * ds->at.len_size)) {
				ds->state = ST_RD_ALIGNED_OFFSET;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			memset(ds->at.freq, 0, sizeof(ds->at.freq));
			for (i = 0; i < ds->at.len_size; i++) {
				ds->at.bitlen[i] = lzx_br_bits(br, 3);
				ds->at.freq[ds->at.bitlen[i]]++;
				lzx_br_consume(br, 3);
			}
			if (!lzx_make_huffman_table(&ds->at))
				goto failed;
			/* FALL THROUGH */
		case ST_RD_VERBATIM:
			ds->loop = 0;
			/* FALL THROUGH */
		case ST_RD_PRE_MAIN_TREE_256:
			/*
			 * Read Pre-tree for first 256 elements of main tree.
			 */
			if (!lzx_read_pre_tree(strm)) {
				ds->state = ST_RD_PRE_MAIN_TREE_256;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			if (!lzx_make_huffman_table(&ds->pt))
				goto failed;
			ds->loop = 0;
			/* FALL THROUGH */
		case ST_MAIN_TREE_256:
			/*
			 * Get path lengths of first 256 elements of main tree.
			 */
			r = lzx_read_bitlen(strm, &ds->mt, 256);
			if (r < 0)
				goto failed;
			else if (!r) {
				ds->state = ST_MAIN_TREE_256;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			ds->loop = 0;
			/* FALL THROUGH */
		case ST_RD_PRE_MAIN_TREE_REM:
			/*
			 * Read Pre-tree for remaining elements of main tree.
			 */
			if (!lzx_read_pre_tree(strm)) {
				ds->state = ST_RD_PRE_MAIN_TREE_REM;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			if (!lzx_make_huffman_table(&ds->pt))
				goto failed;
			ds->loop = 256;
			/* FALL THROUGH */
		case ST_MAIN_TREE_REM:
			/*
			 * Get path lengths of remaining elements of main tree.
			 */
			r = lzx_read_bitlen(strm, &ds->mt, -1);
			if (r < 0)
				goto failed;
			else if (!r) {
				ds->state = ST_MAIN_TREE_REM;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			if (!lzx_make_huffman_table(&ds->mt))
				goto failed;
			ds->loop = 0;
			/* FALL THROUGH */
		case ST_RD_PRE_LENGTH_TREE:
			/*
			 * Read Pre-tree for remaining elements of main tree.
			 */
			if (!lzx_read_pre_tree(strm)) {
				ds->state = ST_RD_PRE_LENGTH_TREE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			if (!lzx_make_huffman_table(&ds->pt))
				goto failed;
			ds->loop = 0;
			/* FALL THROUGH */
		case ST_LENGTH_TREE:
			/*
			 * Get path lengths of remaining elements of main tree.
			 */
			r = lzx_read_bitlen(strm, &ds->lt, -1);
			if (r < 0)
				goto failed;
			else if (!r) {
				ds->state = ST_LENGTH_TREE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}
			if (!lzx_make_huffman_table(&ds->lt))
				goto failed;
			ds->state = ST_MAIN;
			return (100);
		}
	}
failed:
	return (ds->error = ARCHIVE_FAILED);
}