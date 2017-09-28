/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

#ifdef _WIN32
#  ifdef _WIN64
#    define FMT64_PREFIX "ll"
#    define FMTPTR_PREFIX "ll"
#  else
#    define FMT64_PREFIX "ll"
#    define FMTPTR_PREFIX ""
#  endif
#  define FMTd32 "d"
#  define FMTu32 "u"
#  define FMTx32 "x"
#  define FMTd64 FMT64_PREFIX "d"
#  define FMTu64 FMT64_PREFIX "u"
#  define FMTx64 FMT64_PREFIX "x"
#  define FMTdPTR FMTPTR_PREFIX "d"
#  define FMTuPTR FMTPTR_PREFIX "u"
#  define FMTxPTR FMTPTR_PREFIX "x"
#else
#  include <inttypes.h>
#  define FMTd32 PRId32
#  define FMTu32 PRIu32
#  define FMTx32 PRIx32
#  define FMTd64 PRId64
#  define FMTu64 PRIu64
#  define FMTx64 PRIx64
#  define FMTdPTR PRIdPTR
#  define FMTuPTR PRIuPTR
#  define FMTxPTR PRIxPTR
#endif

/* Size of stack-allocated buffer passed to buferror(). */
#define	BUFERROR_BUF		64

/*
 * Size of stack-allocated buffer used by malloc_{,v,vc}printf().  This must be
 * large enough for all possible uses within jemalloc.
