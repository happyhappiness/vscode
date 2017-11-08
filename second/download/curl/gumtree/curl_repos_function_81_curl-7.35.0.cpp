void handle_error(const char *file, int lineno, const char *msg){
     fprintf(stderr, "** %s:%d %s\n", file, lineno, msg);
     ERR_print_errors_fp(stderr);
     /* exit(-1); */
 }