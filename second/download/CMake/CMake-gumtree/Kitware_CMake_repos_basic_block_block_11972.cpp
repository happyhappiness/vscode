(crc != NULL) {
					static const char zeros[2] = {0, 0};
					*crc = lha_crc16(*crc, h,
					    extdsize - datasize);
					/* CRC value itself as zero */
					*crc = lha_crc16(*crc, zeros, 2);
					*crc = lha_crc16(*crc,
					    extdheader+2, datasize - 2);
				}