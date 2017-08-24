{
		case ST_MAIN:
			for (;;) {
				if (block_bytes_avail == 0) {
					/* This block ended. */
					ds->state = ST_RD_BLOCK_TYPE;
					ds->br = bre;
					ds->block_bytes_avail =
					    block_bytes_avail;
					ds->copy_len = copy_len;
					ds->copy_pos = copy_pos;
					ds->length_header = length_header;
					ds->position_slot = position_slot;
					ds->r0 = r0; ds->r1 = r1; ds->r2 = r2;
					ds->w_pos = w_pos;
					strm->avail_out = endp - noutp;
					return (ARCHIVE_EOF);
				}
				if (noutp >= endp)
					/* Output buffer is empty. */
					goto next_data;

				if (!lzx_br_read_ahead(strm, &bre,
				    mt_max_bits)) {
					if (!last)
						goto next_data;
					/* Remaining bits are less than
					 * maximum bits(mt.max_bits) but maybe
					 * it still remains as much as we need,
					 * so we should try to use it with
					 * dummy bits. */
					c = lzx_decode_huffman(mt,
					      lzx_br_bits_forced(
				 	        &bre, mt_max_bits));
					lzx_br_consume(&bre, mt_bitlen[c]);
					if (!lzx_br_has(&bre, 0))
						goto failed;/* Over read. */
				} else {
					c = lzx_decode_huffman(mt,
					      lzx_br_bits(&bre, mt_max_bits));
					lzx_br_consume(&bre, mt_bitlen[c]);
				}
				if (c > UCHAR_MAX)
					break;
				/*
				 * 'c' is exactly literal code.
				 */
				/* Save a decoded code to reference it
				 * afterward. */
				w_buff[w_pos] = c;
				w_pos = (w_pos + 1) & w_mask;
				/* Store the decoded code to output buffer. */
				*noutp++ = c;
				block_bytes_avail--;
			}
			/*
			 * Get a match code, its length and offset.
			 */
			c -= UCHAR_MAX + 1;
			length_header = c & 7;
			position_slot = c >> 3;
			/* FALL THROUGH */
		case ST_LENGTH:
			/*
			 * Get a length.
			 */
			if (length_header == 7) {
				if (!lzx_br_read_ahead(strm, &bre,
				    lt_max_bits)) {
					if (!last) {
						state = ST_LENGTH;
						goto next_data;
					}
					c = lzx_decode_huffman(lt,
					      lzx_br_bits_forced(
					        &bre, lt_max_bits));
					lzx_br_consume(&bre, lt_bitlen[c]);
					if (!lzx_br_has(&bre, 0))
						goto failed;/* Over read. */
				} else {
					c = lzx_decode_huffman(lt,
					    lzx_br_bits(&bre, lt_max_bits));
					lzx_br_consume(&bre, lt_bitlen[c]);
				}
				copy_len = c + 7 + 2;
			} else
				copy_len = length_header + 2;
			if ((size_t)copy_len > block_bytes_avail)
				goto failed;
			/*
			 * Get an offset.
			 */
			switch (position_slot) {
			case 0: /* Use repeated offset 0. */
				copy_pos = r0;
				state = ST_REAL_POS;
				continue;
			case 1: /* Use repeated offset 1. */
				copy_pos = r1;
				/* Swap repeated offset. */
				r1 = r0;
				r0 = copy_pos;
				state = ST_REAL_POS;
				continue;
			case 2: /* Use repeated offset 2. */
				copy_pos = r2;
				/* Swap repeated offset. */
				r2 = r0;
				r0 = copy_pos;
				state = ST_REAL_POS;
				continue;
			default:
				offset_bits =
				    pos_tbl[position_slot].footer_bits;
				break;
			}
			/* FALL THROUGH */
		case ST_OFFSET:
			/*
			 * Get the offset, which is a distance from
			 * current window position.
			 */
			if (block_type == ALIGNED_OFFSET_BLOCK &&
			    offset_bits >= 3) {
				int offbits = offset_bits - 3;

				if (!lzx_br_read_ahead(strm, &bre, offbits)) {
					state = ST_OFFSET;
					if (last)
						goto failed;
					goto next_data;
				}
				copy_pos = lzx_br_bits(&bre, offbits) << 3;

				/* Get an aligned number. */
				if (!lzx_br_read_ahead(strm, &bre,
				    offbits + at_max_bits)) {
					if (!last) {
						state = ST_OFFSET;
						goto next_data;
					}
					lzx_br_consume(&bre, offbits);
					c = lzx_decode_huffman(at,
					      lzx_br_bits_forced(&bre,
					        at_max_bits));
					lzx_br_consume(&bre, at_bitlen[c]);
					if (!lzx_br_has(&bre, 0))
						goto failed;/* Over read. */
				} else {
					lzx_br_consume(&bre, offbits);
					c = lzx_decode_huffman(at,
					      lzx_br_bits(&bre, at_max_bits));
					lzx_br_consume(&bre, at_bitlen[c]);
				}
				/* Add an aligned number. */
				copy_pos += c;
			} else {
				if (!lzx_br_read_ahead(strm, &bre,
				    offset_bits)) {
					state = ST_OFFSET;
					if (last)
						goto failed;
					goto next_data;
				}
				copy_pos = lzx_br_bits(&bre, offset_bits);
				lzx_br_consume(&bre, offset_bits);
			}
			copy_pos += pos_tbl[position_slot].base -2;

			/* Update repeated offset LRU queue. */
			r2 = r1;
			r1 = r0;
			r0 = copy_pos;
			/* FALL THROUGH */
		case ST_REAL_POS:
			/*
			 * Compute a real position in window.
			 */
			copy_pos = (w_pos - copy_pos) & w_mask;
			/* FALL THROUGH */
		case ST_COPY:
			/*
			 * Copy several bytes as extracted data from the window
			 * into the output buffer.
			 */
			for (;;) {
				const unsigned char *s;
				int l;

				l = copy_len;
				if (copy_pos > w_pos) {
					if (l > w_size - copy_pos)
						l = w_size - copy_pos;
				} else {
					if (l > w_size - w_pos)
						l = w_size - w_pos;
				}
				if (noutp + l >= endp)
					l = (int)(endp - noutp);
				s = w_buff + copy_pos;
				if (l >= 8 && ((copy_pos + l < w_pos)
				  || (w_pos + l < copy_pos))) {
					memcpy(w_buff + w_pos, s, l);
					memcpy(noutp, s, l);
				} else {
					unsigned char *d;
					int li;

					d = w_buff + w_pos;
					for (li = 0; li < l; li++)
						noutp[li] = d[li] = s[li];
				}
				noutp += l;
				copy_pos = (copy_pos + l) & w_mask;
				w_pos = (w_pos + l) & w_mask;
				block_bytes_avail -= l;
				if (copy_len <= l)
					/* A copy of current pattern ended. */
					break;
				copy_len -= l;
				if (noutp >= endp) {
					/* Output buffer is empty. */
					state = ST_COPY;
					goto next_data;
				}
			}
			state = ST_MAIN;
			break;
		}