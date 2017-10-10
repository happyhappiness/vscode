					 curr_pack, nr_objects,
					 read_sha1, consumed_bytes-20);
		if (hashcmp(read_sha1, tail_sha1) != 0)
			die(_("Unexpected tail checksum for %s "
			      "(disk corruption?)"), curr_pack);
	}
	if (nr_deltas != nr_resolved_deltas)
		die(Q_("pack has %d unresolved delta",
		       "pack has %d unresolved deltas",
		       nr_deltas - nr_resolved_deltas),
		    nr_deltas - nr_resolved_deltas);
}

static int write_compressed(struct sha1file *f, void *in, unsigned int size)
{
	git_zstream stream;
	int status;
