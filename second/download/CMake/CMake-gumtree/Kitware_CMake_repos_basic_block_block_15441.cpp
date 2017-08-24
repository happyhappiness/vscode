(i = 0; i < num_coder; i++) {
			unsigned codec_id = coders[i].codec;

			/* Write Codec flag. */
			archive_be64enc(codec_buff, codec_id);
			for (codec_size = 8; codec_size > 0; codec_size--) {
				if (codec_buff[8 - codec_size])
					break;
			}
			if (codec_size == 0)
				codec_size = 1;
			if (coders[i].prop_size)
				r = enc_uint64(a, codec_size | 0x20);
			else
				r = enc_uint64(a, codec_size);
			if (r < 0)
				return (r);

			/* Write Codec ID. */
			codec_size &= 0x0f;
			r = (int)compress_out(a, &codec_buff[8-codec_size],
				codec_size, ARCHIVE_Z_RUN);
			if (r < 0)
				return (r);

			if (coders[i].prop_size) {
				/* Write Codec property size. */
				r = enc_uint64(a, coders[i].prop_size);
				if (r < 0)
					return (r);

				/* Write Codec properties. */
				r = (int)compress_out(a, coders[i].props,
					coders[i].prop_size, ARCHIVE_Z_RUN);
				if (r < 0)
					return (r);
			}
		}