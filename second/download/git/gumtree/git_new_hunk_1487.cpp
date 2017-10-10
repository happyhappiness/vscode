		case OBJ_TAG:
			ewah_set(writer.tags, i);
			break;

		default:
			die("Missing type information for %s (%d/%d)",
			    oid_to_hex(&entry->idx.oid), real_type,
			    entry->type);
		}
	}
}

/**
 * Compute the actual bitmaps
