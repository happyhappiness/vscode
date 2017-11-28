inline
int WSADuplicateSocket(int s, DWORD n, LPWSAPROTOCOL_INFO l)
{
#ifdef UNICODE
    if (::WSADuplicateSocketW(_get_osfhandle(s), n, l) == SOCKET_ERROR) {
#else
    if (::WSADuplicateSocketA(_get_osfhandle(s), n, l) == SOCKET_ERROR) {
#endif
        errno = WSAGetLastError();
        return -1;
    } else
        return 0;
}
#define WSADuplicateSocket(s,n,l) Squid::WSADuplicateSocket(s,n,l)

#undef WSASocket
inline
int WSASocket(int a, int t, int p, LPWSAPROTOCOL_INFO i, GROUP g, DWORD f)
{
    SOCKET result;
#ifdef UNICODE
    if ((result = ::WSASocketW(a, t, p, i, g, f)) == INVALID_SOCKET) {
#else
    if ((result = ::WSASocketA(a, t, p, i, g, f)) == INVALID_SOCKET) {
#endif
        if (WSAEMFILE == (errno = WSAGetLastError()))
            errno = EMFILE;
        return -1;
    } else
        return _open_osfhandle(result, 0);
}
#define WSASocket(a,t,p,i,g,f) Squid::WSASocket(a,t,p,i,g,f)

} /* namespace Squid */

#else /* #ifdef __cplusplus */
#define connect(s,n,l) \
	(SOCKET_ERROR == connect(_get_osfhandle(s),n,l) ? \
	(WSAEMFILE == (errno = WSAGetLastError()) ? errno = EMFILE : -1, -1) : 0)
#define gethostbyname(n) \
	(NULL == ((HOSTENT FAR*)(ws32_result = (int)gethostbyname(n))) ? \
	(errno = WSAGetLastError()), (HOSTENT FAR*)NULL : (HOSTENT FAR*)ws32_result)
#define gethostname(n,l) \
	(SOCKET_ERROR == gethostname(n,l) ? \
	(errno = WSAGetLastError()), -1 : 0)
#define recv(s,b,l,f) \
	(SOCKET_ERROR == (ws32_result = recv(_get_osfhandle(s),b,l,f)) ? \
	(errno = WSAGetLastError()), -1 : ws32_result)
#define sendto(s,b,l,f,t,tl) \
	(SOCKET_ERROR == (ws32_result = sendto(_get_osfhandle(s),b,l,f,t,tl)) ? \
	(errno = WSAGetLastError()), -1 : ws32_result)
#define select(n,r,w,e,t) \
	(SOCKET_ERROR == (ws32_result = select(n,r,w,e,t)) ? \
	(errno = WSAGetLastError()), -1 : ws32_result)
#define socket(f,t,p) \
	(INVALID_SOCKET == ((SOCKET)(ws32_result = (int)socket(f,t,p))) ? \
	((WSAEMFILE == (errno = WSAGetLastError()) ? errno = EMFILE : -1), -1) : \
	(SOCKET)_open_osfhandle(ws32_result,0))
#define write      _write /* Needed in util.c */
#define open       _open /* Needed in win32lib.c */
#endif /* #ifdef __cplusplus */

#if HAVE_SYS_RESOURCE_H
#include <sys/resource.h>
#else
#define	RUSAGE_SELF	0		/* calling process */
#define	RUSAGE_CHILDREN	-1		/* terminated child processes */

struct rusage {
    struct timeval ru_utime;	/* user time used */
    struct timeval ru_stime;	/* system time used */
    long ru_maxrss;			/* integral max resident set size */
    long ru_ixrss;			/* integral shared text memory size */
    long ru_idrss;			/* integral unshared data size */
    long ru_isrss;			/* integral unshared stack size */
    long ru_minflt;			/* page reclaims */
    long ru_majflt;			/* page faults */
    long ru_nswap;			/* swaps */
    long ru_inblock;		/* block input operations */
    long ru_oublock;		/* block output operations */
    long ru_msgsnd;			/* messages sent */
    long ru_msgrcv;			/* messages received */
    long ru_nsignals;		/* signals received */
    long ru_nvcsw;			/* voluntary context switches */
    long ru_nivcsw;			/* involuntary context switches */
};
#endif /* HAVE_SYS_RESOURCE_H */

#undef ACL

#if !defined(getpagesize)
/* Windows may lack getpagesize() prototype */
SQUIDCEXTERN size_t getpagesize(void);