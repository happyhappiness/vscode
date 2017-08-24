{
#ifdef WORDS_BIGENDIAN
			const uint32_t tmp = (crc >> 32)
					^ *(const uint32_t *)(buf);
#else
			const uint32_t tmp = crc ^ *(const uint32_t *)(buf);
#endif
			buf += 4;

			crc = lzma_crc64_table[3][A(tmp)]
			    ^ lzma_crc64_table[2][B(tmp)]
			    ^ S32(crc)
			    ^ lzma_crc64_table[1][C(tmp)]
			    ^ lzma_crc64_table[0][D(tmp)];
		}