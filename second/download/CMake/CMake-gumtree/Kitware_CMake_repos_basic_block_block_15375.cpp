((zip->crc32flg & ENCODED_CRC32) && bytes)
			zip->encoded_crc32 = crc32(zip->encoded_crc32,
			    zip->wbuff, (unsigned)bytes)