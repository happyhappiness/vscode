(*p == kEnd) {
		/* PackStreamDigests[num] are not present. */
		pi->digest.defineds =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.defineds));
		pi->digest.digests =
		    calloc((size_t)pi->numPackStreams, sizeof(*pi->digest.digests));
		if (pi->digest.defineds == NULL || pi->digest.digests == NULL)
			return (-1);
		return (0);
	}