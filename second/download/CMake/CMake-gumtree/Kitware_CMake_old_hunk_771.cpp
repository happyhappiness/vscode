			}
			coder2 = &(fc[3]);
			zip->main_stream_bytes_remaining =
				folder->unPackSize[2];
		} else if (coder2 != NULL && coder2->codec == _7Z_X86_BCJ2 &&
		    zip->pack_stream_remaining == 4 &&
		    folder->numInStreams == 5 && folder->numOutStreams == 2) {
			/* Source type 0 made by 7z */
			zip->main_stream_bytes_remaining =
				folder->unPackSize[0];
		} else {
			/* We got an unexpected form. */
			archive_set_error(&(a->archive),
