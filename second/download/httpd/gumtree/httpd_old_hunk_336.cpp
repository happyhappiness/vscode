

/* Debugging tools: */

#ifdef APR_RING_DEBUG
#include <stdio.h>
#define APR_RING_CHECK_ONE(msg, ptr)					\
	fprintf(stderr, "*** %s %p\n", msg, ptr)
#define APR_RING_CHECK(hp, elem, link, msg)				\
	APR_RING_CHECK_ELEM(APR_RING_SENTINEL(hp, elem, link), elem, link, msg)
#define APR_RING_CHECK_ELEM(ep, elem, link, msg) do {			\
	struct elem *start = (ep);					\
	struct elem *this = start;					\
	fprintf(stderr, "*** ring check start -- %s\n", msg);		\
	do {								\
	    fprintf(stderr, "\telem %p\n", this);			\
	    fprintf(stderr, "\telem->next %p\n",			\
		    APR_RING_NEXT(this, link));				\
	    fprintf(stderr, "\telem->prev %p\n",			\
		    APR_RING_PREV(this, link));				\
	    fprintf(stderr, "\telem->next->prev %p\n",			\
		    APR_RING_PREV(APR_RING_NEXT(this, link), link));	\
	    fprintf(stderr, "\telem->prev->next %p\n",			\
		    APR_RING_NEXT(APR_RING_PREV(this, link), link));	\
	    if (APR_RING_PREV(APR_RING_NEXT(this, link), link) != this) { \
		fprintf(stderr, "\t*** this->next->prev != this\n");	\
		break;							\
	    }								\
	    if (APR_RING_NEXT(APR_RING_PREV(this, link), link) != this) { \
		fprintf(stderr, "\t*** this->prev->next != this\n");	\
		break;							\
	    }								\
	    this = APR_RING_NEXT(this, link);				\
	} while (this != start);					\
	fprintf(stderr, "*** ring check end\n");			\
    } while (0)
#else
/**
 * Print a single pointer value to STDERR
 *   (This is a no-op unless APR_RING_DEBUG is defined.)
 * @param msg Descriptive message
 * @param ptr Pointer value to print
