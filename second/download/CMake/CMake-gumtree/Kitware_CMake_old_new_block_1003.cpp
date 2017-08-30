(zip->pack_stream_inbytes_remaining > 0) {
			r = extract_pack_stream(a);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size));
		} else if (zip->folder_outbytes_remaining > 0) {
			/* Extract a remaining pack stream. */
			r = extract_pack_stream(a);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size));
		}