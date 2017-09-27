 * slots for extension methods.
 *
 * @param   p       Pointer to a pool in which the structure should be
 *                  allocated.
 * @param   nelts   Number of preallocated extension slots
 * @return  Pointer to the newly created structure.
 * @deffunc ap_method_list_t ap_make_method_list(apr_pool_t *p, int nelts)
 */
AP_DECLARE(ap_method_list_t *) ap_make_method_list(apr_pool_t *p, int nelts);
AP_DECLARE(void) ap_copy_method_list(ap_method_list_t *dest,
				     ap_method_list_t *src);
AP_DECLARE_NONSTD(void) ap_method_list_do(int (*comp) (void *urec, const char *mname,
						       int mnum),
				          void *rec,
				          const ap_method_list_t *ml, ...);
AP_DECLARE(void) ap_method_list_vdo(int (*comp) (void *urec, const char *mname,
						 int mnum),
				    void *rec, const ap_method_list_t *ml,
				    va_list vp);
/**
 * Search for an HTTP method name in an ap_method_list_t structure, and
 * return true if found.
 *
 * @param   method  String containing the name of the method to check.
 * @param   l       Pointer to a method list, such as cmd->methods_limited.
 * @return  1 if method is in the list, otherwise 0
 * @deffunc int ap_method_in_list(const char *method, ap_method_list_t *l)
 */
AP_DECLARE(int) ap_method_in_list(ap_method_list_t *l, const char *method);

/**
 * Add an HTTP method name to an ap_method_list_t structure if it isn't
 * already listed.
 *
 * @param   method  String containing the name of the method to check.
 * @param   l       Pointer to a method list, such as cmd->methods_limited.
 * @return  None.
 * @deffunc void ap_method_in_list(ap_method_list_t *l, const char *method)
 */
AP_DECLARE(void) ap_method_list_add(ap_method_list_t *l, const char *method);
    
/**
 * Remove an HTTP method name from an ap_method_list_t structure.
 *
 * @param   l       Pointer to a method list, such as cmd->methods_limited.
 * @param   method  String containing the name of the method to remove.
 * @return  None.
 * @deffunc void ap_method_list_remove(ap_method_list_t *l, const char *method)
 */
AP_DECLARE(void) ap_method_list_remove(ap_method_list_t *l,
				       const char *method);

/**
 * Reset a method list to be completely empty.
 *
 * @param   l       Pointer to a method list, such as cmd->methods_limited.
 * @return  None.
 * @deffunc void ap_clear_method_list(ap_method_list_t *l)
 */
AP_DECLARE(void) ap_clear_method_list(ap_method_list_t *l);
    
/**
 * Set the content type for this request (r->content_type). 
 * @param r The current request
 * @param ct The new content type
 * @deffunc void ap_set_content_type(request_rec *r, const char* ct)
 * @warning This function must be called to set r->content_type in order 
 * for the AddOutputFilterByType directive to work correctly.
 */
AP_DECLARE(void) ap_set_content_type(request_rec *r, const char *ct);

/**
 * Set the Accept-Ranges header for this response
 * @param r The current request
 */
AP_DECLARE(void) ap_set_accept_ranges(request_rec *r);


/* Hmmm... could macrofy these for now, and maybe forever, though the
 * definitions of the macros would get a whole lot hairier.
 */

/**
 * Output one character for this request
 * @param c the character to output
 * @param r the current request
 * @return The number of bytes sent
 * @deffunc int ap_rputc(int c, request_rec *r)
 */
AP_DECLARE(int) ap_rputc(int c, request_rec *r);

/**
 * Output a string for the current request
 * @param str The string to output
 * @param r The current request
 * @return The number of bytes sent
 * @deffunc int ap_rputs(const char *str, request_rec *r)
 */
AP_DECLARE(int) ap_rputs(const char *str, request_rec *r);

/**
 * Write a buffer for the current request
 * @param buf The buffer to write
 * @param nbyte The number of bytes to send from the buffer
 * @param r The current request
 * @return The number of bytes sent
 * @deffunc int ap_rwrite(const void *buf, int nbyte, request_rec *r)
 */
AP_DECLARE(int) ap_rwrite(const void *buf, int nbyte, request_rec *r);

/**
 * Write an unspecified number of strings to the request
 * @param r The current request
 * @param ... The strings to write
 * @return The number of bytes sent
 * @deffunc int ap_rvputs(request_rec *r, ...)
 */
AP_DECLARE_NONSTD(int) ap_rvputs(request_rec *r,...);

/**
 * Output data to the client in a printf format
 * @param r The current request
 * @param fmt The format string
 * @param vlist The arguments to use to fill out the format string
 * @return The number of bytes sent
 * @deffunc int ap_vrprintf(request_rec *r, const char *fmt, va_list vlist)
 */
AP_DECLARE(int) ap_vrprintf(request_rec *r, const char *fmt, va_list vlist);

/**
 * Output data to the client in a printf format
 * @param r The current request
 * @param fmt The format string
 * @param ... The arguments to use to fill out the format string
 * @return The number of bytes sent
 * @deffunc int ap_rprintf(request_rec *r, const char *fmt, ...)
 */
AP_DECLARE_NONSTD(int) ap_rprintf(request_rec *r, const char *fmt,...)
				__attribute__((format(printf,2,3)));
/**
 * Flush all of the data for the current request to the client
 * @param r The current request
 * @return 0 on success, -1 if an error occurred
 * @deffunc int ap_rflush(request_rec *r)
 */
AP_DECLARE(int) ap_rflush(request_rec *r);

/**
 * Index used in custom_responses array for a specific error code
 * (only use outside protocol.c is in getting them configured).
 * @param status HTTP status code
 * @return The index of the response
 * @deffunc int ap_index_of_response(int status)
 */
AP_DECLARE(int) ap_index_of_response(int status);

/** 
 * Return the Status-Line for a given status code (excluding the
 * HTTP-Version field). If an invalid or unknown status code is
 * passed, "500 Internal Server Error" will be returned. 
 * @param status The HTTP status code
 * @return The Status-Line
 * @deffunc const char *ap_get_status_line(int status)
 */
AP_DECLARE(const char *) ap_get_status_line(int status);

/* Reading a block of data from the client connection (e.g., POST arg) */

/**
