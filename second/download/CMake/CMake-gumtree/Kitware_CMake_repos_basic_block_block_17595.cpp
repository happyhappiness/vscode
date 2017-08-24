{
	default:
	case CKSUM_NONE:
		return (0);
	case CKSUM_SHA1:
		return (SHA1_SIZE);
	case CKSUM_MD5:
		return (MD5_SIZE);
	}