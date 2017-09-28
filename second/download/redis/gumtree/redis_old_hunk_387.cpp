/******************************************************************************/
#ifdef JEMALLOC_H_TYPES

/* Size of stack-allocated buffer passed to buferror(). */
#define	BUFERROR_BUF		64

/*
 * Size of stack-allocated buffer used by malloc_{,v,vc}printf().  This must be
 * large enough for all possible uses within jemalloc.
