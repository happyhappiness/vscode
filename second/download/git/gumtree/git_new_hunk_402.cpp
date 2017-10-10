					die("unable to force loose object");
		}
	}
}

/*
 * This tracks any options which pack-reuse code expects to be on, or which a
 * reader of the pack might not understand, and which would therefore prevent
 * blind reuse of what we have on disk.
 */
static int pack_options_allow_reuse(void)
{
	return pack_to_stdout && allow_ofs_delta;
}

static int get_object_list_from_bitmap(struct rev_info *revs)
{
	if (prepare_bitmap_walk(revs) < 0)
		return -1;
