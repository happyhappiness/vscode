		ce->ce_mode |= 0111; break;
	case '-':
		ce->ce_mode &= ~0111; break;
	default:
		goto fail;
	}
	cache_tree_invalidate_path(active_cache_tree, path);
	active_cache_changed = 1;
	report("chmod %cx '%s'", flip, path);
	return;
 fail:
	die("git update-index: cannot chmod %cx '%s'", flip, path);
}

