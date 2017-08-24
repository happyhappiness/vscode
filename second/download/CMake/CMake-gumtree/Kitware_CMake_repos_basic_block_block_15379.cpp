{
			if (write_to_temp(a, zip->wbuff, sizeof(zip->wbuff))
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			zip->stream.next_out = zip->wbuff;
			zip->stream.avail_out = sizeof(zip->wbuff);
			if (zip->crc32flg & ENCODED_CRC32)
				zip->encoded_crc32 = crc32(zip->encoded_crc32,
				    zip->wbuff, sizeof(zip->wbuff));
			if (run == ARCHIVE_Z_FINISH && r != ARCHIVE_EOF)
				continue;
		}