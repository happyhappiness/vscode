(extdsize == 0) {
			/* End of extended header */
			if (crc != NULL)
				*crc = lha_crc16(*crc, h, sizefield_length);
			__archive_read_consume(a, sizefield_length);
			return (ARCHIVE_OK);
		}