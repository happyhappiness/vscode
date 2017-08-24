{
	case CKSUM_NONE:
		break;
	case CKSUM_SHA1:
		archive_sha1_init(&(sumwrk->sha1ctx));
		break;
	case CKSUM_MD5:
		archive_md5_init(&(sumwrk->md5ctx));
		break;
	}