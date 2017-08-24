(*p) {
	case 0:
		ci->folders =
			calloc((size_t)ci->numFolders, sizeof(*ci->folders));
		if (ci->folders == NULL)
			return (-1);
		for (i = 0; i < ci->numFolders; i++) {
			if (read_Folder(a, &(ci->folders[i])) < 0)
				goto failed;
		}
		break;
	case 1:
		if (parse_7zip_uint64(a, &(ci->dataStreamIndex)) < 0)
			return (-1);
		if (UMAX_ENTRY < ci->dataStreamIndex)
			return (-1);
		if (ci->numFolders > 0) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			goto failed;
		}
		break;
	default:
		archive_set_error(&a->archive, -1,
		    "Malformed 7-Zip archive");
		goto failed;
	}