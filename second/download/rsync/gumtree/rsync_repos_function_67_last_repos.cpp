static inline mode_t
from_wire_mode(int mode)
{
#if _S_IFLNK != 0120000
	if ((mode & (_S_IFMT)) == 0120000)
		return (mode & ~(_S_IFMT)) | _S_IFLNK;
#endif
	return mode;
}