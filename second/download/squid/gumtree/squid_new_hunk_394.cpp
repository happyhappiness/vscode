#ifndef __COMM_H__
#define __COMM_H__

#include "AsyncEngine.h"
#include "base/AsyncCall.h"
#include "CommCalls.h"
#include "comm_err_t.h"
#include "comm/IoCallback.h"
#include "StoreIOBuffer.h"

namespace Ip
{
class Address;
}

bool comm_iocallbackpending(void); /* inline candidate */

int commSetNonBlocking(int fd);
int commUnsetNonBlocking(int fd);
void commSetCloseOnExec(int fd);
void commSetTcpKeepalive(int fd, int idle, int interval, int timeout);
void _comm_close(int fd, char const *file, int line);
#define comm_close(x) (_comm_close((x), __FILE__, __LINE__))
void old_comm_reset_close(int fd);
void comm_reset_close(const Comm::ConnectionPointer &conn);
#if LINGERING_CLOSE
void comm_lingering_close(int fd);
#endif

int comm_connect_addr(int sock, const Ip::Address &addr);
void comm_init(void);
void comm_exit(void);

int comm_open(int, int, Ip::Address &, int, const char *note);
int comm_open_uds(int sock_type, int proto, struct sockaddr_un* addr, int flags);
/// update Comm state after getting a comm_open() FD from another process
void comm_import_opened(const Comm::ConnectionPointer &, const char *note, struct addrinfo *AI);

/**
 * Open a port specially bound for listening or sending through a specific port.
 * This is a wrapper providing IPv4/IPv6 failover around comm_openex().
 * Please use for all listening sockets and bind() outbound sockets.
 *
