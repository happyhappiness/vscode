		istate->resolve_undo = resolve_undo_read(data, sz);
		break;
	case CACHE_EXT_LINK:
		if (read_link_extension(istate, data, sz))
			return -1;
		break;
	default:
		if (*ext < 'A' || 'Z' < *ext)
			return error("index uses %.4s extension, which we do not understand",
				     ext);
		fprintf(stderr, "ignoring %.4s extension\n", ext);
		break;
