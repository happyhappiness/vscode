inline int
WSADuplicateSocket(int s, DWORD n, LPWSAPROTOCOL_INFO l)
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
inline int
WSASocket(int a, int t, int p, LPWSAPROTOCOL_INFO i, GROUP g, DWORD f)
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

/* provide missing definitions from resoruce.h */
/* NP: sys/resource.h and sys/time.h are apparently order-dependant. */
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
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

SQUIDCEXTERN int chroot(const char *dirname);
SQUIDCEXTERN int kill(pid_t, int);
#if !_SQUID_MINGW_
SQUIDCEXTERN int statfs(const char *, struct statfs *);
#endif
SQUIDCEXTERN struct passwd * getpwnam(char *unused);
SQUIDCEXTERN struct group * getgrnam(char *unused);

static inline uid_t
geteuid(void)
{
    return 100;
}
static inline int
seteuid (uid_t euid)
{
    return 0;
}
static inline uid_t
getuid(void)
{
    return 100;
}
static inline int
setuid (uid_t uid)
{
    return 0;
}
static inline gid_t
getegid(void)
{
    return 100;
}
static inline int
setegid (gid_t egid)
{
    return 0;
}
static inline int
getgid(void)
{
    return 100;
}
static inline int
setgid (gid_t gid)
{
    return 0;
}

/* for some reason autoconf misdetects getpagesize.. */
#if HAVE_GETPAGESIZE && _SQUID_MINGW_
#undef HAVE_GETPAGESIZE
#endif

#if !HAVE_GETPAGESIZE
/* And now we define a compatibility layer */
size_t getpagesize();
#define HAVE_GETPAGESIZE 2
#endif

SQUIDCEXTERN void WIN32_ExceptionHandlerInit(void);
SQUIDCEXTERN int Win32__WSAFDIsSet(int fd, fd_set* set);
SQUIDCEXTERN DWORD WIN32_IpAddrChangeMonitorInit();

/* gcc doesn't recognize the Windows native 64 bit formatting tags causing
 * the compile fail, so we must disable the check on native Windows.
 */
#if __GNUC__
#define PRINTF_FORMAT_ARG1
#define PRINTF_FORMAT_ARG2
#define PRINTF_FORMAT_ARG3
#endif

/* XXX: the logic around this is a bit warped:
 *   we #define ACL unconditionally at the top of this file,
 *   then #undef ACL unconditionally hafway down,
 *   then here re-define ACL to the same value as at the top,
 *   then include windows.h and #undef ACL again.
 */
#ifndef ACL
#define ACL WindowsACL
#define _MSWIN_ACL_WAS_NOT_DEFINED 1
#endif
#include <windows.h>
#if _MSWIN_ACL_WAS_NOT_DEFINED
#undef ACL
#undef _MSWIN_ACL_WAS_NOT_DEFINED
#endif

#if !HAVE_SYSLOG
/* syslog compatibility layer derives from git */
#define LOG_PID     0x01
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7
#define LOG_DAEMON  (3<<3)

void openlog(const char *ident, int logopt, int facility);
void syslog(int priority, const char *fmt, ...);
#endif

#if _SQUID_MINGW_
/* MinGW missing bits from sys/wait.h */
/* A status looks like:
 *  <2 bytes info> <2 bytes code>
 *
 *  <code> == 0, child has exited, info is the exit value
 *  <code> == 1..7e, child has exited, info is the signal number.
 *  <code> == 7f, child has stopped, info was the signal number.
 *  <code> == 80, there was a core dump.
 */
#define WIFEXITED(w)    (((w) & 0xff) == 0)
#define WIFSIGNALED(w)  (((w) & 0x7f) > 0 && (((w) & 0x7f) < 0x7f))
#define WIFSTOPPED(w)   (((w) & 0xff) == 0x7f)
#define WEXITSTATUS(w)  (((w) >> 8) & 0xff)
#define WTERMSIG(w) ((w) & 0x7f)
#define WSTOPSIG    WEXITSTATUS
#endif

/* prototypes */
void WIN32_maperror(unsigned long WIN32_oserrno);