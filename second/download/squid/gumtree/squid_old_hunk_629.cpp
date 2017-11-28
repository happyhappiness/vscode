
#define DEBUG_STATEMENT(e) e
#define DEBUG_PRINT1(x) if (debug) printf (x)
#define DEBUG_PRINT2(x1, x2) if (debug) printf (x1, x2)
#define DEBUG_PRINT3(x1, x2, x3) if (debug) printf (x1, x2, x3)
#define DEBUG_PRINT4(x1, x2, x3, x4) if (debug) printf (x1, x2, x3, x4)
#define DEBUG_PRINT_COMPILED_PATTERN(p, s, e) 				\
  if (debug) print_partial_compiled_pattern (s, e)
#define DEBUG_PRINT_DOUBLE_STRING(w, s1, sz1, s2, sz2)			\
  if (debug) print_double_string (w, s1, sz1, s2, sz2)

extern void printchar();

/* Print the fastmap in human-readable form.  */

