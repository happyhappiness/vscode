{
	default:
	case CKSUM_NONE:
		return (NULL);
	case CKSUM_SHA1:
		return (SHA1_NAME);
	case CKSUM_MD5:
		return (MD5_NAME);
	}