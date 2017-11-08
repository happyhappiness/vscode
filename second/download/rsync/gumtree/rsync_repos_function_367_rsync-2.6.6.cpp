static OFF_T parse_size_arg(const char *size_arg)
{
	const char *arg;
	OFF_T size;

	for (arg = size_arg; isdigit(*(uchar*)arg); arg++) {}
	if (*arg == '.')
		for (arg++; isdigit(*(uchar*)arg); arg++) {}
	switch (*arg) {
	case 'k': case 'K':
		size = atof(size_arg) * 1024;
		break;
	case 'm': case 'M':
		size = atof(size_arg) * 1024*1024;
		break;
	case 'g': case 'G':
		size = atof(size_arg) * 1024*1024*1024;
		break;
	case '\0':
		size = atof(size_arg);
		break;
	default:
		size = 0;
		break;
	}
	return size;
}