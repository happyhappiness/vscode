(p[0]) {
	case kEncodedHeader:
		p++;
		len--;

		/*
		 * The archive has an encoded header and we have to decode it
		 * in order to parse the header correctly.
		 */
		image_bytes =
		    decode_header_image(a, zip, &(zip->si), p, len, &image);
		free_StreamsInfo(&(zip->si));
		memset(&(zip->si), 0, sizeof(zip->si));
		if (image_bytes < 0)
			return (ARCHIVE_FATAL);
		p = image;
		len = image_bytes;
		/* FALL THROUGH */
	case kHeader:
		/*
		 * Parse the header.
		 */
		errno = 0;
		r = read_Header(zip, header, p, len);
		if (r < 0) {
			if (errno == ENOMEM)
				archive_set_error(&a->archive, -1,
				    "Couldn't allocate memory");
			else
				archive_set_error(&a->archive, -1,
				    "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}
		if (len - r == 0 || p[r] != kEnd) {
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