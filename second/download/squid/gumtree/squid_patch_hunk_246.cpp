 SQUIDCEXTERN void parse_onoff(int *var);
 SQUIDCEXTERN void parse_eol(char *volatile *var);
 SQUIDCEXTERN void parse_wordlist(wordlist ** list);
 SQUIDCEXTERN void requirePathnameExists(const char *name, const char *path);
 SQUIDCEXTERN void parse_time_t(time_t * var);
 
-SQUIDCEXTERN void parse_IpAddress_list_token(IpAddress_list **, char *);
-
 
 /* client_side.c - FD related client side routines */
 
 SQUIDCEXTERN void clientdbInit(void);
 
-SQUIDCEXTERN void clientdbUpdate(const IpAddress &, log_type, protocol_t, size_t);
+#include "anyp/ProtocolType.h"
+SQUIDCEXTERN void clientdbUpdate(const Ip::Address &, log_type, AnyP::ProtocolType, size_t);
 
-SQUIDCEXTERN int clientdbCutoffDenied(const IpAddress &);
+SQUIDCEXTERN int clientdbCutoffDenied(const Ip::Address &);
 void clientdbDump(StoreEntry *);
 SQUIDCEXTERN void clientdbFreeMemory(void);
 
-SQUIDCEXTERN int clientdbEstablished(const IpAddress &, int);
+SQUIDCEXTERN int clientdbEstablished(const Ip::Address &, int);
+#if USE_DELAY_POOLS
+SQUIDCEXTERN void clientdbSetWriteLimiter(ClientInfo * info, const int writeSpeedLimit,const double initialBurst,const double highWatermark);
+SQUIDCEXTERN ClientInfo * clientdbGetInfo(const Ip::Address &addr);
+#endif
 SQUIDCEXTERN void clientOpenListenSockets(void);
 SQUIDCEXTERN void clientHttpConnectionsClose(void);
 SQUIDCEXTERN void httpRequestFree(void *);
 
 extern void clientAccessCheck(void *);
 
-/* see debug.c for info on context-based debugging */
-SQUIDCEXTERN Ctx ctx_enter(const char *descr);
-SQUIDCEXTERN void ctx_exit(Ctx ctx);
-
-SQUIDCEXTERN void _db_set_syslog(const char *facility);
-SQUIDCEXTERN void _db_init(const char *logfile, const char *options);
-SQUIDCEXTERN void _db_rotate_log(void);
+#include "Debug.h"
 
-SQUIDCEXTERN void _db_print(const char *,...) PRINTF_FORMAT_ARG1;
-
-/* packs, then prints an object using debug() */
+/* packs, then prints an object using debugs() */
 SQUIDCEXTERN void debugObj(int section, int level, const char *label, void *obj, ObjPackMethod pm);
 
 /* disk.c */
 SQUIDCEXTERN int file_open(const char *path, int mode);
 SQUIDCEXTERN void file_close(int fd);
 /* Adapter file_write for object callbacks */
