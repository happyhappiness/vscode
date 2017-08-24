{
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