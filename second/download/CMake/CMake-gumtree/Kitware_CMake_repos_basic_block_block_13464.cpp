(bitmap & 8) {
				/* 2 byte comment length + comment */
				uint32_t comment_length;
				if (datasize < 2)
					break;
				comment_length
				    = archive_le16dec(p + offset);
				offset += 2;
				datasize -= 2;

				if (datasize < comment_length)
					break;
				/* Comment is not supported by libarchive */
				offset += comment_length;
				datasize -= comment_length;
			}