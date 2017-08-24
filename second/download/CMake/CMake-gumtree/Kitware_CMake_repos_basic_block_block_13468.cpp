(bitmap & 2) {
				/* 2 byte "internal file attributes" */
				uint32_t internal_attributes;
				if (datasize < 2)
					break;
				internal_attributes
				    = archive_le16dec(p + offset);
				/* Not used by libarchive at present. */
				(void)internal_attributes; /* UNUSED */
				offset += 2;
				datasize -= 2;
			}