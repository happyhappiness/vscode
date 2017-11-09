void walker_targets_free(int targets, char **target, const char **write_ref)
{
	while (targets--) {
		free(target[targets]);
		if (write_ref)
			free((char *) write_ref[targets]);
	}
}