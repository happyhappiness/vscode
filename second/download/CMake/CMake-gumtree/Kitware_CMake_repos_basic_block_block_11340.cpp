{
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
			}