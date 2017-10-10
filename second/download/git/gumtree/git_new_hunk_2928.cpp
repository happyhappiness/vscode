
extern void release_pack_memory(size_t);

typedef void (*try_to_free_t)(size_t);
extern try_to_free_t set_try_to_free_routine(try_to_free_t);

#ifdef HAVE_ALLOCA_H
# include <alloca.h>
# define xalloca(size)      (alloca(size))
# define xalloca_free(p)    do {} while (0)
#else
# define xalloca(size)      (xmalloc(size))
