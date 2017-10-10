		return status;
	}

	if (status) {
		patch->conflicted_threeway = 1;
		if (patch->is_new)
			oidclr(&patch->threeway_stage[0]);
		else
			hashcpy(patch->threeway_stage[0].hash, pre_sha1);
		hashcpy(patch->threeway_stage[1].hash, our_sha1);
		hashcpy(patch->threeway_stage[2].hash, post_sha1);
		fprintf(stderr, "Applied patch to '%s' with conflicts.\n", patch->new_name);
	} else {
		fprintf(stderr, "Applied patch to '%s' cleanly.\n", patch->new_name);
	}
	return 0;
}
