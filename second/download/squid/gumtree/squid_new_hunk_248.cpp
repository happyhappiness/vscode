SQUIDCEXTERN void leakInit(void);
SQUIDCEXTERN void *leakAddFL(void *, const char *, int);
SQUIDCEXTERN void *leakTouchFL(void *, const char *, int);
SQUIDCEXTERN void *leakFreeFL(void *, const char *, int);
#endif

/*
 * prototypes for system functions missing from system includes
 */

#if _SQUID_SOLARIS_

SQUIDCEXTERN int getrusage(int, struct rusage *);
SQUIDCEXTERN int getpagesize(void);
#if !defined(_XPG4_2) && !(defined(__EXTENSIONS__) || \
(!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)))
SQUIDCEXTERN int gethostname(char *, int);
#endif
#endif

/*
 * hack to allow snmp access to the statistics counters
 */
class StatCounters;
        SQUIDCEXTERN StatCounters *snmpStatGet(int);

        /* Vary support functions */
        SQUIDCEXTERN int varyEvaluateMatch(StoreEntry * entry, HttpRequest * req);

        /* CygWin & Windows NT Port */
        /* win32.c */
#if _SQUID_WINDOWS_
        SQUIDCEXTERN int WIN32_Subsystem_Init(int *, char ***);
        SQUIDCEXTERN void WIN32_sendSignal(int);
        SQUIDCEXTERN void WIN32_Abort(int);
        SQUIDCEXTERN void WIN32_Exit(void);
        SQUIDCEXTERN void WIN32_SetServiceCommandLine(void);
        SQUIDCEXTERN void WIN32_InstallService(void);
        SQUIDCEXTERN void WIN32_RemoveService(void);
        SQUIDCEXTERN int SquidMain(int, char **);
#endif /* _SQUID_WINDOWS_ */
#if _SQUID_MSWIN_

        SQUIDCEXTERN int WIN32_pipe(int[2]);

            SQUIDCEXTERN int WIN32_getrusage(int, struct rusage *);
    SQUIDCEXTERN void WIN32_ExceptionHandlerInit(void);

    SQUIDCEXTERN int Win32__WSAFDIsSet(int fd, fd_set* set);
    SQUIDCEXTERN DWORD WIN32_IpAddrChangeMonitorInit();

#endif

    /* external_acl.c */
    class external_acl;
            SQUIDCEXTERN void parse_externalAclHelper(external_acl **);

            SQUIDCEXTERN void dump_externalAclHelper(StoreEntry * sentry, const char *name, const external_acl *);

            SQUIDCEXTERN void free_externalAclHelper(external_acl **);

            typedef void EAH(void *data, void *result);
            class ACLChecklist;
                SQUIDCEXTERN void externalAclLookup(ACLChecklist * ch, void *acl_data, EAH * handler, void *data);

                SQUIDCEXTERN void externalAclInit(void);

                SQUIDCEXTERN void externalAclShutdown(void);

                SQUIDCEXTERN char *strtokFile(void);

#if USE_WCCPv2

                SQUIDCEXTERN void parse_wccp2_method(int *v);
                SQUIDCEXTERN void free_wccp2_method(int *v);
                SQUIDCEXTERN void dump_wccp2_method(StoreEntry * e, const char *label, int v);
                SQUIDCEXTERN void parse_wccp2_amethod(int *v);
                SQUIDCEXTERN void free_wccp2_amethod(int *v);
                SQUIDCEXTERN void dump_wccp2_amethod(StoreEntry * e, const char *label, int v);

                SQUIDCEXTERN void parse_wccp2_service(void *v);
                SQUIDCEXTERN void free_wccp2_service(void *v);
                SQUIDCEXTERN void dump_wccp2_service(StoreEntry * e, const char *label, void *v);

                SQUIDCEXTERN int check_null_wccp2_service(void *v);

                SQUIDCEXTERN void parse_wccp2_service_info(void *v);

                SQUIDCEXTERN void free_wccp2_service_info(void *v);

                SQUIDCEXTERN void dump_wccp2_service_info(StoreEntry * e, const char *label, void *v);

#endif

#if USE_AUTH

#if HAVE_AUTH_MODULE_NEGOTIATE && HAVE_KRB5 && HAVE_GSSAPI
                /* upstream proxy authentication */
                SQUIDCEXTERN char *peer_proxy_negotiate_auth(char *principal_name, char *proxy);
#endif

                    namespace Auth {
            /* call to ensure the auth component schemes exist. */
            extern void Init(void);
            } // namespace Auth

#endif /* USE_AUTH */

#endif /* SQUID_PROTOS_H */
