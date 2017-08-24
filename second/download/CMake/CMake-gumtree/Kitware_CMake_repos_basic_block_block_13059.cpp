{
	case CKSUM_NONE:
	case CKSUM_SHA1:
	case CKSUM_MD5:
		bid += 32;
		break;
	default:
		return (0);
	}