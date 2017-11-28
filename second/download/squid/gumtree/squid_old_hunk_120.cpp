#ifndef __COMM_H__
#define __COMM_H__

#include "squid.h"
#include "AsyncEngine.h"
#include "base/AsyncCall.h"
#include "StoreIOBuffer.h"
#include "Array.h"
#include "ip/IpAddress.h"

#define COMMIO_FD_READCB(fd)    (&commfd_table[(fd)].readcb)
#define COMMIO_FD_WRITECB(fd)   (&commfd_table[(fd)].writecb)

typedef enum {
    COMM_OK = 0,
    COMM_ERROR = -1,
    COMM_NOMESSAGE = -3,
    COMM_TIMEOUT = -4,
    COMM_SHUTDOWN = -5,
    COMM_IDLE = -6, /* there are no active fds and no pending callbacks. */
    COMM_INPROGRESS = -7,
    COMM_ERR_CONNECT = -8,
    COMM_ERR_DNS = -9,
    COMM_ERR_CLOSING = -10,
    COMM_ERR_PROTOCOL = -11, /* IPv4 or IPv6 cannot be used on the fd socket */
    COMM_ERR__END__ = -999999 /* Dummy entry to make syntax valid (comma on line above), do not use. New entries added above */
} comm_err_t;

class DnsLookupDetails;
typedef void CNCB(int fd, const DnsLookupDetails &dns, comm_err_t status, int xerrno, void *data);

typedef void IOCB(int fd, char *, size_t size, comm_err_t flag, int xerrno, void *data);


/* comm.c */
extern bool comm_iocallbackpending(void); /* inline candidate */

extern int comm_listen(int fd);
SQUIDCEXTERN int commSetNonBlocking(int fd);
SQUIDCEXTERN int commUnsetNonBlocking(int fd);
SQUIDCEXTERN void commSetCloseOnExec(int fd);
SQUIDCEXTERN void commSetTcpKeepalive(int fd, int idle, int interval, int timeout);
extern void _comm_close(int fd, char const *file, int line);
#define comm_close(fd) (_comm_close((fd), __FILE__, __LINE__))
SQUIDCEXTERN void comm_reset_close(int fd);
#if LINGERING_CLOSE
SQUIDCEXTERN void comm_lingering_close(int fd);
#endif
SQUIDCEXTERN void commConnectStart(int fd, const char *, unsigned short, CNCB *, void *);
void commConnectStart(int fd, const char *, unsigned short, AsyncCall::Pointer &cb);

SQUIDCEXTERN int comm_connect_addr(int sock, const IpAddress &addr);
SQUIDCEXTERN void comm_init(void);
SQUIDCEXTERN void comm_exit(void);

SQUIDCEXTERN int comm_open(int, int, IpAddress &, int, const char *note);

/**
 * Open a port specially bound for listening or sending through a specific port.
 * This is a wrapper providing IPv4/IPv6 failover around comm_openex().
 * Please use for all listening sockets and bind() outbound sockets.
 *
