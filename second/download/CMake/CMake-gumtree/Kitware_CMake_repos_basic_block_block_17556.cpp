{
	case CKSUM_NONE:
		break;
	case CKSUM_SHA1:
		archive_sha1_update(&(sumwrk->sha1ctx), buff, size);
		break;
	case CKSUM_MD5:
		archive_md5_update(&(sumwrk->md5ctx), buff, size);
		break;
	}