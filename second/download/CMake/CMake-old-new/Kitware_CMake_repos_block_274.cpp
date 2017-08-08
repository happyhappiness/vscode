{
#if DEBUG
		fprintf(stderr, "UNKNOWNTAG_START:%s\n", name);
#endif
		xar->xmlsts_unknown = xar->xmlsts;
		xar->xmlsts = UNKNOWN;
	}