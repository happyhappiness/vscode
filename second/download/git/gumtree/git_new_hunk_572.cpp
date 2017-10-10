			strbuf_setlen(&extra, extra.len - 2);
			strbuf_addch(&extra, ')');
		}
		status = d->worktree_status;
		break;
	default:
		die("BUG: unhandled change_type %d in wt_longstatus_print_change_data",
		    change_type);
	}

	one = quote_path(one_name, s->prefix, &onebuf);
	two = quote_path(two_name, s->prefix, &twobuf);

