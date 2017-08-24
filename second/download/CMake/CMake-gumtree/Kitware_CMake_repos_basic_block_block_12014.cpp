(method[2]) {
	case '5':
		w_bits = 13;/* 8KiB for window */
		break;
	case '6':
		w_bits = 15;/* 32KiB for window */
		break;
	case '7':
		w_bits = 16;/* 64KiB for window */
		break;
	default:
		return (ARCHIVE_FAILED);/* Not supported. */
	}