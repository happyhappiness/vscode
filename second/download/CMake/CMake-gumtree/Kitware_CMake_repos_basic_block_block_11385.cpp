{
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