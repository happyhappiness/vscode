static void
debug(char *format,...)
{
#ifdef DEBUG
#ifdef _SQUID_MSWIN_
#if FAIL_DEBUG
    if (debug_enabled || fail_debug_enabled) {
#else
if (debug_enabled) {
#endif
        va_list args;

        va_start(args,format);
        fprintf(stderr, "negotiate-auth[%d]: ",getpid());
        vfprintf(stderr, format, args);
        va_end(args);
#if FAIL_DEBUG
        fail_debug_enabled = 0;
#endif
    }
#endif /* _SQUID_MSWIN_ */
#endif /* DEBUG */
}
#endif /* __GNUC__ */


/* A couple of harmless helper macros */
#define SEND(X) debug("sending '%s' to squid\n",X); printf(X "\n");
#ifdef __GNUC__
#define SEND2(X,Y...) debug("sending '" X "' to squid\n",Y); printf(X "\n",Y);
#define SEND3(X,Y...) debug("sending '" X "' to squid\n",Y); printf(X "\n",Y);
#else
/* no gcc, no debugging. varargs macros are a gcc extension */
#define SEND2(X,Y) debug("sending '" X "' to squid\n",Y); printf(X "\n",Y);
#define SEND3(X,Y,Z) debug("sending '" X "' to squid\n",Y,Z); printf(X "\n",Y,Z);
#endif

extern void uc(char *);

extern char *negotiate_check_auth(SSP_blobP auth, int auth_length);
extern void hex_dump(void *, int);