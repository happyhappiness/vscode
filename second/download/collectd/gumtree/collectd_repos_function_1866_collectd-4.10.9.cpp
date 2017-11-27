static const char *standard_target_map(int verdict)
{
	switch (verdict) {
		case RETURN:
			return LABEL_RETURN;
			break;
		case -NF_ACCEPT-1:
			return LABEL_ACCEPT;
			break;
		case -NF_DROP-1:
			return LABEL_DROP;
			break;
		case -NF_QUEUE-1:
			return LABEL_QUEUE;
			break;
		default:
			fprintf(stderr, "ERROR: %d not a valid target)\n",
				verdict);
			abort();
			break;
	}
	/* not reached */
	return NULL;
}