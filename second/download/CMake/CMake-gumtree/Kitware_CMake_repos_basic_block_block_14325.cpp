{
	case 0: /* Not replaced. */
		break;
	case 1: /* Replaced. */
		archive_entry_copy_pathname_w(entry, ws.s);
		break;
	default:
		ret = ARCHIVE_FAILED;
	}