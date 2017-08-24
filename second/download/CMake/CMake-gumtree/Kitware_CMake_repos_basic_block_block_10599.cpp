{
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