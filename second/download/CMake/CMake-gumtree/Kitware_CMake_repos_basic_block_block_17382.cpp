{
	case GZIP:
		encname = "application/x-gzip"; break;
	case BZIP2:
		encname = "application/x-bzip2"; break;
	case LZMA:
		encname = "application/x-lzma"; break;
	case XZ:
		encname = "application/x-xz"; break;
	default:
		encname = "application/octet-stream"; break;
	}