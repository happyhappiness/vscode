#define	__LA_PRINTF(fmtarg, firstvararg)	/* nothing */
#endif

#if defined(__GNUC__) && __GNUC__ >= 3 && __GNUC_MINOR__ >= 1
# define __LA_DEPRECATED __attribute__((deprecated))
#else
# define __LA_DEPRECATED
#endif

#ifdef __cplusplus
extern "C" {
#endif
