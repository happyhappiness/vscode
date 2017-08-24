{
		lzma_options_delta delta_opt;
		lzma_filter filters[LZMA_FILTERS_MAX], *ff;
		int fi = 0;

		if (zip->lzstream_valid) {
			lzma_end(&(zip->lzstream));
			zip->lzstream_valid = 0;
		}

		/*
		 * NOTE: liblzma incompletely handle the BCJ+LZMA compressed
		 * data made by 7-Zip because 7-Zip does not add End-Of-
		 * Payload Marker(EOPM) at the end of LZMA compressed data,
		 * and so liblzma cannot know the end of the compressed data
		 * without EOPM. So consequently liblzma will not return last
		 * three or four bytes of uncompressed data because
		 * LZMA_FILTER_X86 filter does not handle input data if its
		 * data size is less than five bytes. If liblzma detect EOPM
		 * or know the uncompressed data size, liblzma will flush out
		 * the remaining that three or four bytes of uncompressed
		 * data. That is why we have to use our converting program
		 * for BCJ+LZMA. If we were able to tell the uncompressed
		 * size to liblzma when using lzma_raw_decoder() liblzma
		 * could correctly deal with BCJ+LZMA. But unfortunately
		 * there is no way to do that.
		 * Discussion about this can be found at XZ Utils forum.
		 */
		if (coder2 != NULL) {
			zip->codec2 = coder2->codec;

			filters[fi].options = NULL;
			switch (zip->codec2) {
			case _7Z_X86:
				if (zip->codec == _7Z_LZMA2) {
					filters[fi].id = LZMA_FILTER_X86;
					fi++;
				} else
					/* Use our filter. */
					x86_Init(zip);
				break;
			case _7Z_X86_BCJ2:
				/* Use our filter. */
				zip->bcj_state = 0;
				break;
			case _7Z_DELTA:
				filters[fi].id = LZMA_FILTER_DELTA;
				memset(&delta_opt, 0, sizeof(delta_opt));
				delta_opt.type = LZMA_DELTA_TYPE_BYTE;
				delta_opt.dist = 1;
				filters[fi].options = &delta_opt;
				fi++;
				break;
			/* Following filters have not been tested yet. */
			case _7Z_POWERPC:
				filters[fi].id = LZMA_FILTER_POWERPC;
				fi++;
				break;
			case _7Z_IA64:
				filters[fi].id = LZMA_FILTER_IA64;
				fi++;
				break;
			case _7Z_ARM:
				filters[fi].id = LZMA_FILTER_ARM;
				fi++;
				break;
			case _7Z_ARMTHUMB:
				filters[fi].id = LZMA_FILTER_ARMTHUMB;
				fi++;
				break;
			case _7Z_SPARC:
				filters[fi].id = LZMA_FILTER_SPARC;
				fi++;
				break;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Unexpected codec ID: %lX", zip->codec2);
				return (ARCHIVE_FAILED);
			}
		}

		if (zip->codec == _7Z_LZMA2)
			filters[fi].id = LZMA_FILTER_LZMA2;
		else
			filters[fi].id = LZMA_FILTER_LZMA1;
		filters[fi].options = NULL;
		ff = &filters[fi];
		r = lzma_properties_decode(&filters[fi], NULL,
		    coder1->properties, (size_t)coder1->propertiesSize);
		if (r != LZMA_OK) {
			set_error(a, r);
			return (ARCHIVE_FAILED);
		}
		fi++;

		filters[fi].id = LZMA_VLI_UNKNOWN;
		filters[fi].options = NULL;
		r = lzma_raw_decoder(&(zip->lzstream), filters);
		free(ff->options);
		if (r != LZMA_OK) {
			set_error(a, r);
			return (ARCHIVE_FAILED);
		}
		zip->lzstream_valid = 1;
		zip->lzstream.total_in = 0;
		zip->lzstream.total_out = 0;
		break;
	}