{
	case _7Z_DEFLATE:
		r = compression_init_encoder_deflate(
		    &(a->archive), &(zip->stream),
		    compression_level, 0);
		break;
	case _7Z_BZIP2:
		r = compression_init_encoder_bzip2(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_LZMA1:
		r = compression_init_encoder_lzma1(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_LZMA2:
		r = compression_init_encoder_lzma2(
		    &(a->archive), &(zip->stream),
		    compression_level);
		break;
	case _7Z_PPMD:
		r = compression_init_encoder_ppmd(
		    &(a->archive), &(zip->stream),
		    PPMD7_DEFAULT_ORDER, PPMD7_DEFAULT_MEM_SIZE);
		break;
	case _7Z_COPY:
	default:
		r = compression_init_encoder_copy(
		    &(a->archive), &(zip->stream));
		break;
	}