static void *yy_flex_realloc( void *ptr, yy_size_t size )
#else
static void *yy_flex_realloc( ptr, size )
void *ptr;
yy_size_t size;
#endif
        {
        /* The cast to (char *) in the following accommodates both
         * implementations that use char* generic pointers, and those
         * that use void* generic pointers.  It works with the latter
         * because both ANSI C and C++ allow castless assignment from
         * any pointer type to void*, and deal with argument conversions
         * as though doing an assignment.
         */
        return (void *) realloc( (char *) ptr, size );
        }