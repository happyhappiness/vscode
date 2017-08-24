(lzx_br_has(br, 16)) {
					u16 = lzx_br_bits(br, 16);
					lzx_br_consume(br, 16);
					archive_le16enc(ds->rbytes, u16);
					ds->rbytes_avail = 2;
				}