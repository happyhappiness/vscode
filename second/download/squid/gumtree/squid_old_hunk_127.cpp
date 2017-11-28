#define ACL_THURSDAY	0x10
#define ACL_FRIDAY	0x20
#define ACL_SATURDAY	0x40
#define ACL_ALLWEEK	0x7F
#define ACL_WEEKDAYS	0x3E

#define MAXHTTPPORTS			128

/* Select types. */
#define COMM_SELECT_READ   (0x1)
#define COMM_SELECT_WRITE  (0x2)

#define COMM_NONBLOCKING	0x01
#define COMM_NOCLOEXEC		0x02
#define COMM_REUSEADDR		0x04
#define COMM_TRANSPARENT	0x08
#define COMM_DOBIND		0x10

#include "Debug.h"
#define do_debug(SECTION, LEVEL) ((Debug::level = (LEVEL)) > Debug::Levels[SECTION])
#define debug(SECTION, LEVEL) \
        do_debug(SECTION, LEVEL) ? (void) 0 : _db_print

#define safe_free(x)	if (x) { xxfree(x); x = NULL; }

#define DISK_OK                   (0)
#define DISK_ERROR               (-1)
#define DISK_EOF                 (-2)
#define DISK_NO_SPACE_LEFT       (-6)

#define DNS_INBUF_SZ 4096
