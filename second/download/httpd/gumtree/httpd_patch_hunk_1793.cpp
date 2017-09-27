 /**
  * Initialize the arguments for parsing by apr_getopt().
  * @param os   The options structure created for apr_getopt()
  * @param cont The pool to operate on
  * @param argc The number of arguments to parse
  * @param argv The array of arguments to parse
- * @remark Arguments 2 and 3 are most commonly argc and argv from main(argc, argv)
- * The errfn is initialized to fprintf(stderr... but may be overridden.
+ * @remark Arguments 3 and 4 are most commonly argc and argv from main(argc, argv)
+ * The (*os)->errfn is initialized to fprintf(stderr... but may be overridden.
  */
 APR_DECLARE(apr_status_t) apr_getopt_init(apr_getopt_t **os, apr_pool_t *cont,
                                       int argc, const char * const *argv);
 
 /**
  * Parse the options initialized by apr_getopt_init().
