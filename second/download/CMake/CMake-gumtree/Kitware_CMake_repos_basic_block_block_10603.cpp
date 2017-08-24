{
	case _7Z_COPY:
	case _7Z_BZ2:
	case _7Z_DEFLATE:
	case _7Z_PPMD:
		if (coder2 != NULL) {
			if (coder2->codec != _7Z_X86 &&
			    coder2->codec != _7Z_X86_BCJ2) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Unsupported filter %lx for %lx",
				    coder2->codec, coder1->codec);
				return (ARCHIVE_FAILED);
			}
			zip->codec2 = coder2->codec;
			zip->bcj_state = 0;
			if (coder2->codec == _7Z_X86)
				x86_Init(zip);
		}
		break;
	default:
		break;
	}