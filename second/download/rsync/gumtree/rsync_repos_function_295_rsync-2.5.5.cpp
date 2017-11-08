static mode_t from_wire_mode(int mode)
{
	if ((mode & (_S_IFMT)) == 0120000 && (_S_IFLNK != 0120000)) {
		return (mode & ~(_S_IFMT)) | _S_IFLNK;
	}
	return (mode_t) mode;
}