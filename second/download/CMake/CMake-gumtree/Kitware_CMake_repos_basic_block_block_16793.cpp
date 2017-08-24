{
	case 'a':
		if (strcmp(key, "all") == 0)
			keybit = ~0;
		break;
	case 'c':
		if (strcmp(key, "cksum") == 0)
			keybit = F_CKSUM;
		break;
	case 'd':
		if (strcmp(key, "device") == 0)
			keybit = F_DEV;
		else if (strcmp(key, "dironly") == 0) {
			mtree->dironly = (value != NULL)? 1: 0;
			return (ARCHIVE_OK);
		}
		break;
	case 'f':
		if (strcmp(key, "flags") == 0)
			keybit = F_FLAGS;
		break;
	case 'g':
		if (strcmp(key, "gid") == 0)
			keybit = F_GID;
		else if (strcmp(key, "gname") == 0)
			keybit = F_GNAME;
		break;
	case 'i':
		if (strcmp(key, "indent") == 0) {
			mtree->indent = (value != NULL)? 1: 0;
			return (ARCHIVE_OK);
		} else if (strcmp(key, "inode") == 0) {
			keybit = F_INO;
		}
		break;
	case 'l':
		if (strcmp(key, "link") == 0)
			keybit = F_SLINK;
		break;
	case 'm':
		if (strcmp(key, "md5") == 0 ||
		    strcmp(key, "md5digest") == 0)
			keybit = F_MD5;
		if (strcmp(key, "mode") == 0)
			keybit = F_MODE;
		break;
	case 'n':
		if (strcmp(key, "nlink") == 0)
			keybit = F_NLINK;
		break;
	case 'r':
		if (strcmp(key, "resdevice") == 0) {
			keybit = F_RESDEV;
		} else if (strcmp(key, "ripemd160digest") == 0 ||
		    strcmp(key, "rmd160") == 0 ||
		    strcmp(key, "rmd160digest") == 0)
			keybit = F_RMD160;
		break;
	case 's':
		if (strcmp(key, "sha1") == 0 ||
		    strcmp(key, "sha1digest") == 0)
			keybit = F_SHA1;
		if (strcmp(key, "sha256") == 0 ||
		    strcmp(key, "sha256digest") == 0)
			keybit = F_SHA256;
		if (strcmp(key, "sha384") == 0 ||
		    strcmp(key, "sha384digest") == 0)
			keybit = F_SHA384;
		if (strcmp(key, "sha512") == 0 ||
		    strcmp(key, "sha512digest") == 0)
			keybit = F_SHA512;
		if (strcmp(key, "size") == 0)
			keybit = F_SIZE;
		break;
	case 't':
		if (strcmp(key, "time") == 0)
			keybit = F_TIME;
		else if (strcmp(key, "type") == 0)
			keybit = F_TYPE;
		break;
	case 'u':
		if (strcmp(key, "uid") == 0)
			keybit = F_UID;
		else if (strcmp(key, "uname") == 0)
			keybit = F_UNAME;
		else if (strcmp(key, "use-set") == 0) {
			mtree->output_global_set = (value != NULL)? 1: 0;
			return (ARCHIVE_OK);
		}
		break;
	}