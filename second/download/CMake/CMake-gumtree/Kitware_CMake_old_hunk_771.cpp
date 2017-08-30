 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY

 * KIND, either express or implied.

 *

 * $Id$

 ***************************************************************************/



#include "setup.h"



#ifndef WIN32

/* headers for non-win32 */

#ifdef HAVE_SYS_TIME_H

#include <sys/time.h>

#endif

#ifdef HAVE_SYS_TYPES_H

#include <sys/types.h>

#endif

#ifdef HAVE_SYS_SOCKET_H

#include <sys/socket.h>

#endif

#ifdef HAVE_NETINET_IN_H

#include <netinet/in.h> /* <netinet/tcp.h> may need it */

#endif

#ifdef HAVE_NETINET_TCP_H

#include <netinet/tcp.h> /* for TCP_NODELAY */

#endif

#ifdef HAVE_SYS_IOCTL_H

#include <sys/ioctl.h>

#endif

#ifdef HAVE_UNISTD_H

#include <unistd.h>

#endif

#ifdef HAVE_NETDB_H

#include <netdb.h>

#endif

#ifdef HAVE_FCNTL_H

#include <fcntl.h>

#endif

#ifdef HAVE_NETINET_IN_H

#include <netinet/in.h>

#endif

#ifdef HAVE_ARPA_INET_H

#include <arpa/inet.h>

#endif

#ifdef HAVE_STDLIB_H

#include <stdlib.h> /* required for free() prototype, without it, this crashes

                       on macos 68K */

#endif

#if (defined(HAVE_FIONBIO) && defined(__NOVELL_LIBC__))

#include <sys/filio.h>

#endif

#if (defined(NETWARE) && defined(__NOVELL_LIBC__))

#undef in_addr_t

#define in_addr_t unsigned long

#endif

#ifdef VMS

#include <in.h>

#include <inet.h>

#endif



#endif

#include <stdio.h>

#include <errno.h>

#include <string.h>



#ifndef TRUE

#define TRUE 1

#define FALSE 0

#endif



#ifdef USE_WINSOCK

#define EINPROGRESS WSAEINPROGRESS

#define EWOULDBLOCK WSAEWOULDBLOCK

#define EISCONN     WSAEISCONN

#define ENOTSOCK    WSAENOTSOCK

#define ECONNREFUSED WSAECONNREFUSED

#endif



#include "urldata.h"

#include "sendf.h"

#include "if2ip.h"

#include "strerror.h"

#include "connect.h"

#include "memory.h"

#include "select.h"

#include "url.h" /* for Curl_safefree() */

#include "multiif.h"

#include "sockaddr.h" /* required for Curl_sockaddr_storage */

#include "inet_ntop.h"



/* The last #include file should be: */

#include "memdebug.h"



static bool verifyconnect(curl_socket_t sockfd, int *error);



static curl_socket_t

singleipconnect(struct connectdata *conn,

                const Curl_addrinfo *ai, /* start connecting to this */

                long timeout_ms,

                bool *connected);



/*

 * Curl_sockerrno() returns the *socket-related* errno (or equivalent) on this

 * platform to hide platform specific for the function that calls this.

 */

int Curl_sockerrno(void)

{

#ifdef USE_WINSOCK

  return (int)WSAGetLastError();

#else

  return errno;

#endif

}



/*

 * Curl_nonblock() set the given socket to either blocking or non-blocking

 * mode based on the 'nonblock' boolean argument. This function is highly

 * portable.

 */

int Curl_nonblock(curl_socket_t sockfd,    /* operate on this */

                  int nonblock   /* TRUE or FALSE */)

{

#undef SETBLOCK

#define SETBLOCK 0

#ifdef HAVE_O_NONBLOCK

  /* most recent unix versions */

  int flags;



  flags = fcntl(sockfd, F_GETFL, 0);

  if (TRUE == nonblock)

    return fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

  else

    return fcntl(sockfd, F_SETFL, flags & (~O_NONBLOCK));

#undef SETBLOCK

#define SETBLOCK 1

#endif



#if defined(HAVE_FIONBIO) && (SETBLOCK == 0)

  /* older unix versions */

  int flags;



  flags = nonblock;

  return ioctl(sockfd, FIONBIO, &flags);

#undef SETBLOCK

#define SETBLOCK 2

#endif



#if defined(HAVE_IOCTLSOCKET) && (SETBLOCK == 0)

  /* Windows? */

  unsigned long flags;

  flags = nonblock;



  return ioctlsocket(sockfd, FIONBIO, &flags);

#undef SETBLOCK

#define SETBLOCK 3

#endif



#if defined(HAVE_IOCTLSOCKET_CASE) && (SETBLOCK == 0)

  /* presumably for Amiga */

  return IoctlSocket(sockfd, FIONBIO, (long)nonblock);

#undef SETBLOCK

#define SETBLOCK 4

#endif



#if defined(HAVE_SO_NONBLOCK) && (SETBLOCK == 0)

  /* BeOS */

  long b = nonblock ? 1 : 0;

  return setsockopt(sockfd, SOL_SOCKET, SO_NONBLOCK, &b, sizeof(b));

#undef SETBLOCK

#define SETBLOCK 5

#endif



#ifdef HAVE_DISABLED_NONBLOCKING

  return 0; /* returns success */

#undef SETBLOCK

#define SETBLOCK 6

#endif



#if (SETBLOCK == 0)

#error "no non-blocking method was found/used/set"

#endif

}



/*

 * waitconnect() waits for a TCP connect on the given socket for the specified

 * number if milliseconds. It returns:

 * 0    fine connect

 * -1   select() error

 * 1    select() timeout

 * 2    select() returned with an error condition fd_set

 */



#define WAITCONN_CONNECTED     0

#define WAITCONN_SELECT_ERROR -1

#define WAITCONN_TIMEOUT       1

#define WAITCONN_FDSET_ERROR   2



static

int waitconnect(curl_socket_t sockfd, /* socket */

                long timeout_msec)

{

  int rc;

#ifdef mpeix

  /* Call this function once now, and ignore the results. We do this to

     "clear" the error state on the socket so that we can later read it

     reliably. This is reported necessary on the MPE/iX operating system. */

  (void)verifyconnect(sockfd, NULL);

#endif



  /* now select() until we get connect or timeout */

  rc = Curl_select(CURL_SOCKET_BAD, sockfd, (int)timeout_msec);

  if(-1 == rc)

    /* error, no connect here, try next */

    return WAITCONN_SELECT_ERROR;



  else if(0 == rc)

    /* timeout, no connect today */

    return WAITCONN_TIMEOUT;



  if(rc & CSELECT_ERR)

    /* error condition caught */

    return WAITCONN_FDSET_ERROR;



  /* we have a connect! */

  return WAITCONN_CONNECTED;

}



static CURLcode bindlocal(struct connectdata *conn,

                          curl_socket_t sockfd)

{

  struct SessionHandle *data = conn->data;

  struct sockaddr_in me;

  struct sockaddr *sock = NULL;  /* bind to this address */

  socklen_t socksize; /* size of the data sock points to */

  unsigned short port = data->set.localport; /* use this port number, 0 for

                                                "random" */

  /* how many port numbers to try to bind to, increasing one at a time */

  int portnum = data->set.localportrange;



  /*************************************************************

   * Select device to bind socket to

   *************************************************************/

  if (data->set.device && (strlen(data->set.device)<255) ) {

    struct Curl_dns_entry *h=NULL;

    char myhost[256] = "";

    in_addr_t in;

    int rc;

    bool was_iface = FALSE;



    /* First check if the given name is an IP address */

    in=inet_addr(data->set.device);



    if((in == CURL_INADDR_NONE) &&

       Curl_if2ip(data->set.device, myhost, sizeof(myhost))) {

      /*

       * We now have the numerical IPv4-style x.y.z.w in the 'myhost' buffer

       */

      rc = Curl_resolv(conn, myhost, 0, &h);

      if(rc == CURLRESOLV_PENDING)

        (void)Curl_wait_for_resolv(conn, &h);



      if(h) {

        was_iface = TRUE;

        Curl_resolv_unlock(data, h);

      }

    }



    if(!was_iface) {

      /*

       * This was not an interface, resolve the name as a host name

       * or IP number

       */

      rc = Curl_resolv(conn, data->set.device, 0, &h);

      if(rc == CURLRESOLV_PENDING)

        (void)Curl_wait_for_resolv(conn, &h);



      if(h) {

        if(in == CURL_INADDR_NONE)

          /* convert the resolved address, sizeof myhost >= INET_ADDRSTRLEN */

          Curl_inet_ntop(h->addr->ai_addr->sa_family,

                         &((struct sockaddr_in*)h->addr->ai_addr)->sin_addr,

                         myhost, sizeof myhost);

        else

          /* we know data->set.device is shorter than the myhost array */

          strcpy(myhost, data->set.device);

        Curl_resolv_unlock(data, h);

      }

    }



    if(! *myhost) {

      /* need to fix this

         h=Curl_gethost(data,

         getmyhost(*myhost,sizeof(myhost)),

         hostent_buf,

         sizeof(hostent_buf));

      */

      failf(data, "Couldn't bind to '%s'", data->set.device);

      return CURLE_HTTP_PORT_FAILED;

    }



    infof(data, "Bind local address to %s\n", myhost);



#ifdef SO_BINDTODEVICE

    /* I am not sure any other OSs than Linux that provide this feature, and

     * at the least I cannot test. --Ben

     *

     * This feature allows one to tightly bind the local socket to a

     * particular interface.  This will force even requests to other local

     * interfaces to go out the external interface.

     *

     */

    if (was_iface) {

      /* Only bind to the interface when specified as interface, not just as a

       * hostname or ip address.

       */

      if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE,

                     data->set.device, strlen(data->set.device)+1) != 0) {

        /* printf("Failed to BINDTODEVICE, socket: %d  device: %s error: %s\n",

           sockfd, data->set.device, Curl_strerror(Curl_sockerrno())); */

        infof(data, "SO_BINDTODEVICE %s failed\n",

              data->set.device);

        /* This is typically "errno 1, error: Operation not permitted" if

           you're not running as root or another suitable privileged user */

      }

    }

#endif



    in=inet_addr(myhost);

    if (CURL_INADDR_NONE == in) {

      failf(data,"couldn't find my own IP address (%s)", myhost);

      return CURLE_HTTP_PORT_FAILED;

    } /* end of inet_addr */



    if ( h ) {

      Curl_addrinfo *addr = h->addr;

      sock = addr->ai_addr;

      socksize = addr->ai_addrlen;

    }

    else

      return CURLE_HTTP_PORT_FAILED;



  }

  else if(port) {

    /* if a local port number is requested but no local IP, extract the

       address from the socket */

    memset(&me, 0, sizeof(struct sockaddr));

    me.sin_family = AF_INET;

    me.sin_addr.s_addr = INADDR_ANY;



    sock = (struct sockaddr *)&me;

    socksize = sizeof(struct sockaddr);



  }

  else

    /* no local kind of binding was requested */

    return CURLE_OK;



  do {



    /* Set port number to bind to, 0 makes the system pick one */

    if(sock->sa_family == AF_INET)

      ((struct sockaddr_in *)sock)->sin_port = htons(port);

#ifdef ENABLE_IPV6

    else

      ((struct sockaddr_in6 *)sock)->sin6_port = htons(port);

#endif



    if( bind(sockfd, sock, socksize) >= 0) {

      /* we succeeded to bind */

      struct Curl_sockaddr_storage add;

      socklen_t size;



      size = sizeof(add);

      if(getsockname(sockfd, (struct sockaddr *) &add, &size) < 0) {

        failf(data, "getsockname() failed");

        return CURLE_HTTP_PORT_FAILED;

      }

      /* We re-use/clobber the port variable here below */

      if(((struct sockaddr *)&add)->sa_family == AF_INET)

        port = ntohs(((struct sockaddr_in *)&add)->sin_port);

#ifdef ENABLE_IPV6

      else

        port = ntohs(((struct sockaddr_in6 *)&add)->sin6_port);

#endif

      infof(data, "Local port: %d\n", port);

      return CURLE_OK;

    }

    if(--portnum > 0) {

      infof(data, "Bind to local port %d failed, trying next\n", port);

      port++; /* try next port */

    }

    else

      break;

  } while(1);



  data->state.os_errno = Curl_sockerrno();

  failf(data, "bind failure: %s",

        Curl_strerror(conn, data->state.os_errno));

  return CURLE_HTTP_PORT_FAILED;



}



/*

