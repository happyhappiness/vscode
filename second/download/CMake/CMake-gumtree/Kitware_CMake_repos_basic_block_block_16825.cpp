(len = mtree->crc_len; len != 0; len >>= 8)
			COMPUTE_CRC(mtree->crc, len & 0xff)