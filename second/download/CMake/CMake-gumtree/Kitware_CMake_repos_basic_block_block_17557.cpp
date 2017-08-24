{
	case CKSUM_NONE:
		sumval->len = 0;
		break;
	case CKSUM_SHA1:
		archive_sha1_final(&(sumwrk->sha1ctx), sumval->val);
		sumval->len = SHA1_SIZE;
		break;
	case CKSUM_MD5:
		archive_md5_final(&(sumwrk->md5ctx), sumval->val);
		sumval->len = MD5_SIZE;
		break;
	}