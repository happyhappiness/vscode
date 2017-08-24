 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#include "curl_setup.h"

#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h> /* <netinet/tcp.h> may need it */
#endif
#ifdef HAVE_SYS_UN_H
#include <sys/un.h> /* for sockaddr_un */
#endif
#ifdef HAVE_NETINET_TCP_H
#include <netinet/tcp.h> /* for TCP_NODELAY */
#endif
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#if (defined(HAVE_IOCTL_FIONBIO) && defined(NETWARE))
#include <sys/filio.h>
#endif
#ifdef NETWARE
#undef in_addr_t
#define in_addr_t unsigned long
#endif
#ifdef __VMS
#include <in.h>
#include <inet.h>
#endif

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#include "urldata.h"
#include "sendf.h"
#include "if2ip.h"
#include "strerror.h"
#include "connect.h"
#include "curl_memory.h"
#include "select.h"
#include "url.h" /* for Curl_safefree() */
#include "multiif.h"
#include "sockaddr.h" /* required for Curl_sockaddr_storage */
#include "inet_ntop.h"
#include "inet_pton.h"
#include "vtls/vtls.h" /* for Curl_ssl_check_cxn() */
#include "progress.h"
#include "warnless.h"
#include "conncache.h"
#include "multihandle.h"

/* The last #include file should be: */
#include "memdebug.h"

#ifdef __SYMBIAN32__
/* This isn't actually supported under Symbian OS */
#undef SO_NOSIGPIPE
#endif

static bool verifyconnect(curl_socket_t sockfd, int *error);

#if defined(__DragonFly__) || defined(HAVE_WINSOCK_H)
/* DragonFlyBSD and Windows use millisecond units */
#define KEEPALIVE_FACTOR(x) (x *= 1000)
#else
#define KEEPALIVE_FACTOR(x)
#endif

#if defined(HAVE_WINSOCK2_H) && !defined(SIO_KEEPALIVE_VALS)
#define SIO_KEEPALIVE_VALS    _WSAIOW(IOC_VENDOR,4)

struct tcp_keepalive {
  u_long onoff;
  u_long keepalivetime;
  u_long keepaliveinterval;
};
#endif

static void
tcpkeepalive(struct SessionHandle *data,
             curl_socket_t sockfd)
{
  int optval = data->set.tcp_keepalive?1:0;

  /* only set IDLE and INTVL if setting KEEPALIVE is successful */
  if(setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE,
        (void *)&optval, sizeof(optval)) < 0) {
    infof(data, "Failed to set SO_KEEPALIVE on fd %d\n", sockfd);
  }
  else {
#if defined(SIO_KEEPALIVE_VALS)
    struct tcp_keepalive vals;
    DWORD dummy;
    vals.onoff = 1;
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    vals.keepalivetime = optval;
    optval = curlx_sltosi(data->set.tcp_keepintvl);
    KEEPALIVE_FACTOR(optval);
    vals.keepaliveinterval = optval;
    if(WSAIoctl(sockfd, SIO_KEEPALIVE_VALS, (LPVOID) &vals, sizeof(vals),
                NULL, 0, &dummy, NULL, NULL) != 0) {
      infof(data, "Failed to set SIO_KEEPALIVE_VALS on fd %d: %d\n",
            (int)sockfd, WSAGetLastError());
    }
#else
#ifdef TCP_KEEPIDLE
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPIDLE on fd %d\n", sockfd);
    }
#endif
#ifdef TCP_KEEPINTVL
    optval = curlx_sltosi(data->set.tcp_keepintvl);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPINTVL on fd %d\n", sockfd);
    }
#endif
#ifdef TCP_KEEPALIVE
    /* Mac OS X style */
    optval = curlx_sltosi(data->set.tcp_keepidle);
    KEEPALIVE_FACTOR(optval);
    if(setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPALIVE,
          (void *)&optval, sizeof(optval)) < 0) {
      infof(data, "Failed to set TCP_KEEPALIVE on fd %d\n", sockfd);
    }
#endif
#endif
  }
}

static CURLcode
singleipconnect(struct connectdata *conn,
                const Curl_addrinfo *ai, /* start connecting to this */
                curl_socket_t *sock);

/*
 * Curl_timeleft() returns the amount of milliseconds left allowed for the
 * transfer/connection. If the value is negative, the timeout time has already
 * elapsed.
 *
 * The start time is stored in progress.t_startsingle - as set with
 * Curl_pgrsTime(..., TIMER_STARTSINGLE);
 *
 * If 'nowp' is non-NULL, it points to the current time.
 * 'duringconnect' is FALSE if not during a connect, as then of course the
 * connect timeout is not taken into account!
 *
 * @unittest: 1303
 */
long Curl_timeleft(struct SessionHandle *data,
                   struct timeval *nowp,
                   bool duringconnect)
{
  int timeout_set = 0;
  long timeout_ms = duringconnect?DEFAULT_CONNECT_TIMEOUT:0;
  struct timeval now;

  /* if a timeout is set, use the most restrictive one */

  if(data->set.timeout > 0)
    timeout_set |= 1;
  if(duringconnect && (data->set.connecttimeout > 0))
    timeout_set |= 2;

  switch (timeout_set) {
  case 1:
    timeout_ms = data->set.timeout;
    break;
  case 2:
    timeout_ms = data->set.connecttimeout;
    break;
  case 3:
    if(data->set.timeout < data->set.connecttimeout)
      timeout_ms = data->set.timeout;
    else
      timeout_ms = data->set.connecttimeout;
    break;
  default:
    /* use the default */
    if(!duringconnect)
      /* if we're not during connect, there's no default timeout so if we're
         at zero we better just return zero and not make it a negative number
         by the math below */
      return 0;
    break;
  }

  if(!nowp) {
    now = Curl_tvnow();
    nowp = &now;
  }

  /* subtract elapsed time */
  if(duringconnect)
    /* since this most recent connect started */
    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startsingle);
  else
    /* since the entire operation started */
    timeout_ms -= Curl_tvdiff(*nowp, data->progress.t_startop);
  if(!timeout_ms)
    /* avoid returning 0 as that means no timeout! */
    return -1;

  return timeout_ms;
}

static CURLcode bindlocal(struct connectdata *conn,
                          curl_socket_t sockfd, int af)
{
  struct SessionHandle *data = conn->data;

  struct Curl_sockaddr_storage sa;
  struct sockaddr *sock = (struct sockaddr *)&sa;  /* bind to this address */
  curl_socklen_t sizeof_sa = 0; /* size of the data sock points to */
  struct sockaddr_in *si4 = (struct sockaddr_in *)&sa;
#ifdef ENABLE_IPV6
  struct sockaddr_in6 *si6 = (struct sockaddr_in6 *)&sa;
#endif

  struct Curl_dns_entry *h=NULL;
  unsigned short port = data->set.localport; /* use this port number, 0 for
                                                "random" */
  /* how many port numbers to try to bind to, increasing one at a time */
  int portnum = data->set.localportrange;
  const char *dev = data->set.str[STRING_DEVICE];
  int error;
  char myhost[256] = "";
  int done = 0; /* -1 for error, 1 for address found */
  bool is_interface = FALSE;
  bool is_host = FALSE;
  static const char *if_prefix = "if!";
  static const char *host_prefix = "host!";

  /*************************************************************
   * Select device to bind socket to
   *************************************************************/
  if(!dev && !port)
    /* no local kind of binding was requested */
    return CURLE_OK;

  memset(&sa, 0, sizeof(struct Curl_sockaddr_storage));

  if(dev && (strlen(dev)<255) ) {
    if(strncmp(if_prefix, dev, strlen(if_prefix)) == 0) {
      dev += strlen(if_prefix);
      is_interface = TRUE;
    }
    else if(strncmp(host_prefix, dev, strlen(host_prefix)) == 0) {
      dev += strlen(host_prefix);
      is_host = TRUE;
    }

    /* interface */
    if(!is_host) {
      switch(Curl_if2ip(af, conn->scope, dev, myhost, sizeof(myhost))) {
        case IF2IP_NOT_FOUND:
          if(is_interface) {
            /* Do not fall back to treating it as a host name */
            failf(data, "Couldn't bind to interface '%s'", dev);
            return CURLE_INTERFACE_FAILED;
          }
          break;
        case IF2IP_AF_NOT_SUPPORTED:
          /* Signal the caller to try another address family if available */
          return CURLE_UNSUPPORTED_PROTOCOL;
        case IF2IP_FOUND:
          is_interface = TRUE;
          /*
           * We now have the numerical IP address in the 'myhost' buffer
           */
          infof(data, "Local Interface %s is ip %s using address family %i\n",
                dev, myhost, af);
          done = 1;

#ifdef SO_BINDTODEVICE
          /* I am not sure any other OSs than Linux that provide this feature,
           * and at the least I cannot test. --Ben
           *
           * This feature allows one to tightly bind the local socket to a
           * particular interface.  This will force even requests to other
           * local interfaces to go out the external interface.
           *
           *
           * Only bind to the interface when specified as interface, not just
           * as a hostname or ip address.
           */
          if(setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,
                        dev, (curl_socklen_t)strlen(dev)+1) != 0) {
            error = SOCKERRNO;
            infof(data, "SO_BINDTODEVICE %s failed with errno %d: %s;"
                  " will do regular bind\n",
                  dev, error, Curl_strerror(conn, error));
            /* This is typically "errno 1, error: Operation not permitted" if
               you're not running as root or another suitable privileged
               user */
          }
#endif
          break;
      }
    }
    if(!is_interface) {
      /*
       * This was not an interface, resolve the name as a host name
       * or IP number
       *
       * Temporarily force name resolution to use only the address type
       * of the connection. The resolve functions should really be changed
       * to take a type parameter instead.
       */
      long ipver = conn->ip_version;
      int rc;

      if(af == AF_INET)
        conn->ip_version = CURL_IPRESOLVE_V4;
#ifdef ENABLE_IPV6
      else if(af == AF_INET6)
        conn->ip_version = CURL_IPRESOLVE_V6;
#endif

      rc = Curl_resolv(conn, dev, 0, &h);
      if(rc == CURLRESOLV_PENDING)
        (void)Curl_resolver_wait_resolv(conn, &h);
      conn->ip_version = ipver;

      if(h) {
        /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */
        Curl_printable_address(h->addr, myhost, sizeof(myhost));
        infof(data, "Name '%s' family %i resolved to '%s' family %i\n",
              dev, af, myhost, h->addr->ai_family);
        Curl_resolv_unlock(data, h);
        done = 1;
      }
      else {
        /*
         * provided dev was no interface (or interfaces are not supported
         * e.g. solaris) no ip address and no domain we fail here
         */
        done = -1;
      }
    }

    if(done > 0) {
#ifdef ENABLE_IPV6
      /* ipv6 address */
      if(af == AF_INET6) {
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
        char *scope_ptr = strchr(myhost, '%');
        if(scope_ptr)
          *(scope_ptr++) = 0;
#endif
        if(Curl_inet_pton(AF_INET6, myhost, &si6->sin6_addr) > 0) {
          si6->sin6_family = AF_INET6;
          si6->sin6_port = htons(port);
#ifdef HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID
          if(scope_ptr)
            /* The "myhost" string either comes from Curl_if2ip or from
               Curl_printable_address. The latter returns only numeric scope
               IDs and the former returns none at all.  So the scope ID, if
               present, is known to be numeric */
            si6->sin6_scope_id = atoi(scope_ptr);
#endif
        }
        sizeof_sa = sizeof(struct sockaddr_in6);
      }
      else
#endif
      /* ipv4 address */
      if((af == AF_INET) &&
         (Curl_inet_pton(AF_INET, myhost, &si4->sin_addr) > 0)) {
        si4->sin_family = AF_INET;
        si4->sin_port = htons(port);
        sizeof_sa = sizeof(struct sockaddr_in);
      }
    }

    if(done < 1) {
      failf(data, "Couldn't bind to '%s'", dev);
      return CURLE_INTERFACE_FAILED;
    }
  }
  else {
    /* no device was given, prepare sa to match af's needs */
#ifdef ENABLE_IPV6
    if(af == AF_INET6) {
      si6->sin6_family = AF_INET6;
      si6->sin6_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in6);
    }
    else
#endif
    if(af == AF_INET) {
      si4->sin_family = AF_INET;
      si4->sin_port = htons(port);
      sizeof_sa = sizeof(struct sockaddr_in);
    }
  }

  for(;;) {
    if(bind(sockfd, sock, sizeof_sa) >= 0) {
      /* we succeeded to bind */
      struct Curl_sockaddr_storage add;
      curl_socklen_t size = sizeof(add);
      memset(&add, 0, sizeof(struct Curl_sockaddr_storage));
      if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {
        data->state.os_errno = error = SOCKERRNO;
        failf(data, "getsockname() failed with errno %d: %s",
              error, Curl_strerror(conn, error));
        return CURLE_INTERFACE_FAILED;
      }
      infof(data, "Local port: %hu\n", port);
      conn->bits.bound = TRUE;
      return CURLE_OK;
    }

    if(--portnum > 0) {
      infof(data, "Bind to local port %hu failed, trying next\n", port);
      port++; /* try next port */
      /* We re-use/clobber the port variable here below */
      if(sock->sa_family == AF_INET)
        si4->sin_port = ntohs(port);
#ifdef ENABLE_IPV6
      else
        si6->sin6_port = ntohs(port);
#endif
    }
    else
      break;
  }

  data->state.os_errno = error = SOCKERRNO;
  failf(data, "bind failed with errno %d: %s",
        error, Curl_strerror(conn, error));

  return CURLE_INTERFACE_FAILED;
}

/*
