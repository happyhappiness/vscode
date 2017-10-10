	case CACHE_EXT_TREE:
		istate->cache_tree = cache_tree_read(data, sz);
		break;
	case CACHE_EXT_RESOLVE_UNDO:
		istate->resolve_undo = resolve_undo_read(data, sz);
		break;
	default:
		if (*ext < 'A' || 'Z' < *ext)
			return error("index uses %.4s extension, which we do not understand",
				     ext);
		fprintf(stderr, "ignoring %.4s extension\n", ext);
		break;
