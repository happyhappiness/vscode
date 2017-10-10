				show_with_type(type, full);
				break;
			default: /* ambiguous */
				error("refname '%s' is ambiguous", name);
				break;
			}
			free(full);
		} else {
			show_with_type(type, name);
		}
	}
	else if (abbrev)
		show_with_type(type, find_unique_abbrev(sha1, abbrev));
