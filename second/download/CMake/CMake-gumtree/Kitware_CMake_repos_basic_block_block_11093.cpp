{
		case iFoldCONTINUED_TO_NEXT:
			/* This must be last file in a folder. */
			if (i != hd->file_count -1)
				goto invalid;
			cur_folder = hd->folder_count -1;
			break;
		case iFoldCONTINUED_PREV_AND_NEXT:
			/* This must be only one file in a folder. */
			if (hd->file_count != 1)
				goto invalid;
			/* FALL THROUGH */
		case iFoldCONTINUED_FROM_PREV:
			/* This must be first file in a folder. */
			if (i != 0)
				goto invalid;
			prev_folder = cur_folder = 0;
			offset32 = file->offset;
			break;
		default:
			if (file->folder >= hd->folder_count)
				goto invalid;
			cur_folder = file->folder;
			break;
		}