#define ACL_THURSDAY	0x10
#define ACL_FRIDAY	0x20
#define ACL_SATURDAY	0x40
#define ACL_ALLWEEK	0x7F
#define ACL_WEEKDAYS	0x3E

/* Select types. */
#define COMM_SELECT_READ   (0x1)
#define COMM_SELECT_WRITE  (0x2)

#define DISK_OK                   (0)
#define DISK_ERROR               (-1)
#define DISK_EOF                 (-2)
#define DISK_NO_SPACE_LEFT       (-6)

#define DNS_INBUF_SZ 4096
