 
 extern void release_pack_memory(size_t);
 
 typedef void (*try_to_free_t)(size_t);
 extern try_to_free_t set_try_to_free_routine(try_to_free_t);
 
-static inline size_t st_add(size_t a, size_t b)
-{
-	if (unsigned_add_overflows(a, b))
-		die("size_t overflow: %"PRIuMAX" + %"PRIuMAX,
-		    (uintmax_t)a, (uintmax_t)b);
-	return a + b;
-}
-#define st_add3(a,b,c)   st_add((a),st_add((b),(c)))
-#define st_add4(a,b,c,d) st_add((a),st_add3((b),(c),(d)))
-
-static inline size_t st_mult(size_t a, size_t b)
-{
-	if (unsigned_mult_overflows(a, b))
-		die("size_t overflow: %"PRIuMAX" * %"PRIuMAX,
-		    (uintmax_t)a, (uintmax_t)b);
-	return a * b;
-}
-
-static inline size_t st_sub(size_t a, size_t b)
-{
-	if (a < b)
-		die("size_t underflow: %"PRIuMAX" - %"PRIuMAX,
-		    (uintmax_t)a, (uintmax_t)b);
-	return a - b;
-}
-
 #ifdef HAVE_ALLOCA_H
 # include <alloca.h>
 # define xalloca(size)      (alloca(size))
 # define xalloca_free(p)    do {} while (0)
 #else
 # define xalloca(size)      (xmalloc(size))
