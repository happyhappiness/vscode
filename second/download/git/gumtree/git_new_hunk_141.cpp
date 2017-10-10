#define raise mingw_raise

/*
 * ANSI emulation wrappers
 */

void winansi_init(void);
HANDLE winansi_get_osfhandle(int fd);

/*
 * git specific compatibility
 */

#define has_dos_drive_prefix(path) (isalpha(*(path)) && (path)[1] == ':')
