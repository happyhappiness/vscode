{
	case kEncodedHeader:
		/*
		 * The archive has an encoded header and we have to decode it
		 * in order to parse the header correctly.
		 */
		r = decode_encoded_header_info(a, &(zip->si));

		/* Check the EncodedHeader CRC.*/
		if (r == 0 && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Damaged 7-Zip archive");
			r = -1;
		}
		if (r == 0) {
			if (zip->si.ci.folders[0].digest_defined)
				next_header_crc = zip->si.ci.folders[0].digest;
			else
				check_header_crc = 0;
			if (zip->pack_stream_bytes_unconsumed)
				read_consume(a);
			r = setup_decode_folder(a, zip->si.ci.folders, 1);
			if (r == 0) {
				zip->header_bytes_remaining =
					zip->folder_outbytes_remaining;
				r = seek_pack(a);
			}
		}
		/* Clean up StreamsInfo. */
		free_StreamsInfo(&(zip->si));
		memset(&(zip->si), 0, sizeof(zip->si));
		if (r < 0)
			return (ARCHIVE_FATAL);
		zip->header_is_encoded = 1;
		zip->header_crc32 = 0;
		/* FALL THROUGH */
	case kHeader:
		/*
		 * Parse the header.
		 */
		errno = 0;
		r = read_Header(a, header, zip->header_is_encoded);
		if (r < 0) {
			if (errno == ENOMEM)
				archive_set_error(&a->archive, -1,
				    "Couldn't allocate memory");
			else
				archive_set_error(&a->archive, -1,
				    "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 *  Must be kEnd.
		 */
		if ((p = header_bytes(a, 1)) == NULL ||*p != kEnd) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/* Check the Header CRC.*/
		if (check_header_crc && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		break;
	default:
		archive_set_error(&a->archive, -1,
		    "Unexpected Property ID = %X", p[0]);
		return (ARCHIVE_FATAL);
	}