/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2004, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * $Id$
 ***************************************************************************/

#include "setup.h"

#include <string.h>
#include <errno.h>

#define _REENTRANT

#if defined(WIN32) && !defined(__GNUC__) || defined(__MINGW32__)
#include <malloc.h>
#else
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>     /* required for free() prototypes */
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>     /* for the close() proto */
#endif
#ifdef  VMS
#include <in.h>
#include <inet.h>
#include <stdlib.h>
#endif
#endif

#ifdef HAVE_SETJMP_H
#include <setjmp.h>
#endif

#ifdef WIN32
#include <process.h>
#endif

#if (defined(NETWARE) && defined(__NOVELL_LIBC__))
#undef in_addr_t
#define in_addr_t unsigned long
#endif

#include "urldata.h"
#include "sendf.h"
#include "hostip.h"
#include "hash.h"
#include "share.h"
#include "strerror.h"
#include "url.h"
#include "inet_ntop.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

#if defined(HAVE_INET_NTOA_R) && !defined(HAVE_INET_NTOA_R_DECL)
#include "inet_ntoa_r.h"
#endif

#include "curl_memory.h"
/* The last #include file should be: */
#include "memdebug.h"

/*
 * hostip.c explained
 * ==================
 *
 * The main COMPILE-TIME DEFINES to keep in mind when reading the host*.c
 * source file are these:
 *
 * CURLRES_IPV6 - this host has getaddrinfo() and family, and thus we use
 * that. The host may not be able to resolve IPv6, but we don't really have to
 * take that into account. Hosts that aren't IPv6-enabled have CURLRES_IPV4
 * defined.
 *
 * CURLRES_ARES - is defined if libcurl is built to use c-ares for
 * asynchronous name resolves. It cannot have ENABLE_IPV6 defined at the same
 * time, as c-ares has no ipv6 support. This can be Windows or *nix.
 *
 * CURLRES_THREADED - is defined if libcurl is built to run under (native)
 * Windows, and then the name resolve will be done in a new thread, and the
 * supported API will be the same as for ares-builds.
 *
 * If any of the two previous are defined, CURLRES_ASYNCH is defined too. If
 * libcurl is not built to use an asynchronous resolver, CURLRES_SYNCH is
 * defined.
 *
 * The host*.c sources files are split up like this:
 *
 * hostip.c   - method-independent resolver functions and utility functions
 * hostasyn.c - functions for asynchronous name resolves
 * hostsyn.c  - functions for synchronous name resolves
 * hostares.c - functions for ares-using name resolves
 * hostthre.c - functions for threaded name resolves
 * hostip4.c  - ipv4-specific functions
 * hostip6.c  - ipv6-specific functions
 *
 * The hostip.h is the united header file for all this. It defines the
 * CURLRES_* defines based on the config*.h and setup.h defines.
 */

/* These two symbols are for the global DNS cache */
static curl_hash hostname_cache;
static int host_cache_initialized;

static void freednsentry(void *freethis);

/*
 * Curl_global_host_cache_init() initializes and sets up a global DNS cache.
 * Global DNS cache is general badness. Do not use. This will be removed in
 * a future version. Use the share interface instead!
 */
void Curl_global_host_cache_init(void)
{
  if (!host_cache_initialized) {
    Curl_hash_init(&hostname_cache, 7, freednsentry);
    host_cache_initialized = 1;
  }
}

/*
 * Return a pointer to the global cache
 */
curl_hash *Curl_global_host_cache_get(void)
{
  return &hostname_cache;
}

/*
 * Destroy and cleanup the global DNS cache
 */
void Curl_global_host_cache_dtor(void)
{
  if (host_cache_initialized) {
    Curl_hash_clean(&hostname_cache);
    host_cache_initialized = 0;
  }
}

/*
 * Return # of adresses in a Curl_addrinfo struct
 */
int Curl_num_addresses(const Curl_addrinfo *addr)
{
  int i;
  for (i = 0; addr; addr = addr->ai_next, i++);
  return i;
}

#define GET_SIN_ADDR_FROM_CURL_ADDRINFO(ai_addr, si, sin, sinaddr, ip) \
  { \
  union { \
    struct si* vsi; \
    struct sin* vsin;\
  } vi; \
  vi.vsi = ai_addr; \
  ip = &(vi.vsin->sinaddr); \
  }

/*
 * Curl_printable_address() returns a printable version of the 1st address
 * given in the 'ip' argument. The result will be stored in the buf that is
 * bufsize bytes big.
 *
 * If the conversion fails, it returns NULL.
 */
const char *Curl_printable_address(const Curl_addrinfo *ip,
                                   char *buf, size_t bufsize)
{
  int af = ip->ai_family;
  const void *ip4;
#ifdef CURLRES_IPV6
  const void *ip6;
  GET_SIN_ADDR_FROM_CURL_ADDRINFO(ip->ai_addr, sockaddr, sockaddr_in6,
    sin6_addr, ip6);
#else
  const void *ip6 = NULL;
#endif
  GET_SIN_ADDR_FROM_CURL_ADDRINFO(ip->ai_addr, sockaddr, sockaddr_in,
    sin_addr, ip4);

  return Curl_inet_ntop(af, af == AF_INET ? ip4 : ip6, buf, bufsize);
}

/*
 * Return a hostcache id string for the providing host + port, to be used by
 * the DNS caching.
 */
static char *
create_hostcache_id(char *server, int port)
{
  /* create and return the new allocated entry */
  return aprintf("%s:%d", server, port);
}

struct hostcache_prune_data {
  int cache_timeout;
  time_t now;
};

/*
 * This function is set as a callback to be called for every entry in the DNS
 * cache when we want to prune old unused entries.
 *
 * Returning non-zero means remove the entry, return 0 to keep it in the
 * cache.
 */
static int
hostcache_timestamp_remove(void *datap, void *hc)
{
  struct hostcache_prune_data *data =
    (struct hostcache_prune_data *) datap;
  struct Curl_dns_entry *c = (struct Curl_dns_entry *) hc;

  if ((data->now - c->timestamp < data->cache_timeout) ||
      c->inuse) {
    /* please don't remove */
    return 0;
  }

  /* fine, remove */
  return 1;
}

/*
 * Prune the DNS cache. This assumes that a lock has already been taken.
 */
static void
hostcache_prune(curl_hash *hostcache, int cache_timeout, time_t now)
{
  struct hostcache_prune_data user;

  user.cache_timeout = cache_timeout;
  user.now = now;

  Curl_hash_clean_with_criterium(hostcache,
                                 (void *) &user,
                                 hostcache_timestamp_remove);
}

/*
 * Library-wide function for pruning the DNS cache. This function takes and
 * returns the appropriate locks.
 */
void Curl_hostcache_prune(struct SessionHandle *data)
{
  time_t now;

  if(data->set.dns_cache_timeout == -1)
    /* cache forever means never prune! */
    return;

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  time(&now);

  /* Remove outdated and unused entries from the hostcache */
  hostcache_prune(data->hostcache,
                  data->set.dns_cache_timeout,
                  now);

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}

#ifdef HAVE_SIGSETJMP
/* Beware this is a global and unique instance. This is used to store the
   return address that we can jump back to from inside a signal handler. This
   is not thread-safe stuff. */
sigjmp_buf curl_jmpenv;
#endif


/*
 * Curl_cache_addr() stores a 'Curl_addrinfo' struct in the DNS cache.
 *
 * When calling Curl_resolv() has resulted in a response with a returned
 * address, we call this function to store the information in the dns
 * cache etc
 *
 * Returns the Curl_dns_entry entry pointer or NULL if the storage failed.
 */
struct Curl_dns_entry *
Curl_cache_addr(struct SessionHandle *data,
                Curl_addrinfo *addr,
                char *hostname,
                int port)
{
  char *entry_id;
  size_t entry_len;
  struct Curl_dns_entry *dns;
  struct Curl_dns_entry *dns2;
  time_t now;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if (!entry_id)
    return NULL;
  entry_len = strlen(entry_id);

  /* Create a new cache entry */
  dns = (struct Curl_dns_entry *) malloc(sizeof(struct Curl_dns_entry));
  if (!dns) {
    free(entry_id);
    return NULL;
  }

  dns->inuse = 0;   /* init to not used */
  dns->addr = addr; /* this is the address(es) */

  /* Store the resolved data in our DNS cache. This function may return a
     pointer to an existing struct already present in the hash, and it may
     return the same argument we pass in. Make no assumptions. */
  dns2 = Curl_hash_add(data->hostcache, entry_id, entry_len+1, (void *)dns);
  if(!dns2) {
    /* Major badness, run away. */
    free(dns);
    free(entry_id);
    return NULL;
  }
  time(&now);
  dns = dns2;

  dns->timestamp = now; /* used now */
  dns->inuse++;         /* mark entry as in-use */

  /* free the allocated entry_id again */
  free(entry_id);

  return dns;
}

/*
 * Curl_resolv() is the main name resolve function within libcurl. It resolves
 * a name and returns a pointer to the entry in the 'entry' argument (if one
 * is provided). This function might return immediately if we're using asynch
 * resolves. See the return codes.
 *
 * The cache entry we return will get its 'inuse' counter increased when this
 * function is used. You MUST call Curl_resolv_unlock() later (when you're
 * done using this struct) to decrease the counter again.
 *
 * Return codes:
 *
 * CURLRESOLV_ERROR   (-1) = error, no pointer
 * CURLRESOLV_RESOLVED (0) = OK, pointer provided
 * CURLRESOLV_PENDING  (1) = waiting for response, no pointer
 */

int Curl_resolv(struct connectdata *conn,
                char *hostname,
                int port,
                struct Curl_dns_entry **entry)
{
  char *entry_id;
  struct Curl_dns_entry *dns = NULL;
  size_t entry_len;
  int wait;
  struct SessionHandle *data = conn->data;
  CURLcode result;

  /* default to failure */
  int rc;
  *entry = NULL;

#ifdef HAVE_SIGSETJMP
  /* this allows us to time-out from the name resolver, as the timeout
     will generate a signal and we will siglongjmp() from that here */
  if(!data->set.no_signal && sigsetjmp(curl_jmpenv, 1)) {
    /* this is coming from a siglongjmp() */
    failf(data, "name lookup timed out");
    return CURLRESOLV_ERROR;
  }
#endif
  rc = CURLRESOLV_ERROR;

  /* Create an entry id, based upon the hostname and port */
  entry_id = create_hostcache_id(hostname, port);
  /* If we can't create the entry id, fail */
  if (!entry_id)
    return CURLRESOLV_ERROR;

  entry_len = strlen(entry_id);

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  /* See if its already in our dns cache */
  dns = Curl_hash_pick(data->hostcache, entry_id, entry_len+1);

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

  /* free the allocated entry_id again */
  free(entry_id);

  if (!dns) {
    /* The entry was not in the cache. Resolve it to IP address */

    Curl_addrinfo *addr;

    /* Check what IP specifics the app has requested and if we can provide it.
     * If not, bail out. */
    if(!Curl_ipvalid(data))
      return CURLRESOLV_ERROR;

    /* If Curl_getaddrinfo() returns NULL, 'wait' might be set to a non-zero
       value indicating that we need to wait for the response to the resolve
       call */
    addr = Curl_getaddrinfo(conn, hostname, port, &wait);

    if (!addr) {
      if(wait) {
        /* the response to our resolve call will come asynchronously at
           a later time, good or bad */
        /* First, check that we haven't received the info by now */
        result = Curl_is_resolved(conn, &dns);
        if(result) /* error detected */
          return CURLRESOLV_ERROR;
        if(dns)
          rc = CURLRESOLV_RESOLVED; /* pointer provided */
        else
          rc = CURLRESOLV_PENDING; /* no info yet */
      }
    }
    else {
      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      /* we got a response, store it in the cache */
      dns = Curl_cache_addr(data, addr, hostname, port);

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

      if(!dns)
        /* returned failure, bail out nicely */
        Curl_freeaddrinfo(addr);
      else
        rc = CURLRESOLV_RESOLVED;
    }
  }
  else {
    dns->inuse++; /* we use it! */
    rc = CURLRESOLV_RESOLVED;
  }

  *entry = dns;

  return rc;
}

/*
 * Curl_resolv_unlock() unlocks the given cached DNS entry. When this has been
 * made, the struct may be destroyed due to pruning. It is important that only
 * one unlock is made for each Curl_resolv() call.
 */
void Curl_resolv_unlock(struct SessionHandle *data, struct Curl_dns_entry *dns)
{
  curlassert(dns && (dns->inuse>0));

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  dns->inuse--;

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}

/*
 * File-internal: free a cache dns entry.
 */
static void freednsentry(void *freethis)
{
  struct Curl_dns_entry *p = (struct Curl_dns_entry *) freethis;

  Curl_freeaddrinfo(p->addr);

  free(p);
}

/*
 * Curl_mk_dnscache() creates a new DNS cache and returns the handle for it.
 */
curl_hash *Curl_mk_dnscache(void)
