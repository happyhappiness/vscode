static int to_wire_mode(mode_t mode)
{
	if (S_ISLNK(mode) && (_S_IFLNK != 0120000)) {
		return (mode & ~(_S_IFMT)) | 0120000;
	}
	return (int) mode;
}