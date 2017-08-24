{
			/* jackpot! */
			/* now also use HDR buffer for the actual warcinfo */
			archive_strncat(&hdr, warcinfo, sizeof(warcinfo) -1);

			/* append end-of-record indicator */
			archive_strncat(&hdr, "\r\n\r\n", 4);

			/* write to output stream */
			__archive_write_output(a, hdr.s, archive_strlen(&hdr));
		}