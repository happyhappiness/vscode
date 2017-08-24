{
			/* Source type 1 made by 7zr or 7z with -m options. */
			if (folder->bindPairs[0].inIndex == 5) {
				/* The form made by 7zr */
				idx[0] = 1; idx[1] = 2; idx[2] = 0;
				scoder[1] = &(fc[1]);
				scoder[2] = &(fc[0]);
				sunpack[1] = folder->unPackSize[1];
				sunpack[2] = folder->unPackSize[0];
				coder1 = &(fc[2]);
			} else {
				/*
				 * NOTE: Some patterns do not work.
				 * work:
				 *  7z a -m0=BCJ2 -m1=COPY -m2=COPY
				 *       -m3=(any)
				 *  7z a -m0=BCJ2 -m1=COPY -m2=(any)
				 *       -m3=COPY
				 *  7z a -m0=BCJ2 -m1=(any) -m2=COPY
				 *       -m3=COPY
				 * not work:
				 *  other patterns.
				 *
				 * We have to handle this like `pipe' or
				 * our libarchive7s filter frame work,
				 * decoding the BCJ2 main stream sequentially,
				 * m3 -> m2 -> m1 -> BCJ2.
				 *
				 */
				if (fc[0].codec == _7Z_COPY &&
				    fc[1].codec == _7Z_COPY)
					coder1 = &(folder->coders[2]);
				else if (fc[0].codec == _7Z_COPY &&
				    fc[2].codec == _7Z_COPY)
					coder1 = &(folder->coders[1]);
				else if (fc[1].codec == _7Z_COPY &&
				    fc[2].codec == _7Z_COPY)
					coder1 = &(folder->coders[0]);
				else {
					archive_set_error(&(a->archive),
					    ARCHIVE_ERRNO_MISC,
					    "Unsupported form of "
					    "BCJ2 streams");
					return (ARCHIVE_FATAL);
				}
			}
			coder2 = &(fc[3]);
			zip->main_stream_bytes_remaining =
				(size_t)folder->unPackSize[2];
		}