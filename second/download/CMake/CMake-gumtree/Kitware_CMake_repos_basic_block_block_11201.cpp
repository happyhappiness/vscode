(r) {
		case Z_OK:
			break;
		case Z_STREAM_END:
			eod = 1;
			break;
		default:
			goto zlibfailed;
		}