			die(_("Not a valid object name: '%s'"), mergetag_data->argv[i]);
		if (!oidcmp(&tag->tagged->oid, &oid))
			return; /* found */
	}

	die(_("original commit '%s' contains mergetag '%s' that is discarded; "
	      "use --edit instead of --graft"), ref, sha1_to_hex(tag_sha1));
}

static void check_mergetags(struct commit *commit, int argc, const char **argv)
{
	struct check_mergetag_data mergetag_data;

