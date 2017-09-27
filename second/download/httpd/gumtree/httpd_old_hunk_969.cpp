 * @param fptr The apr file we are testing.
 * @remark Returns APR_EOF if we are at the end of file, APR_SUCCESS otherwise.
 */
APR_DECLARE(apr_status_t) apr_file_eof(apr_file_t *fptr);

/**
 * open standard error as an apr file pointer.
 * @param thefile The apr file to use as stderr.
 * @param cont The pool to allocate the file out of.
 * 
 * @remark The only reason that the apr_file_open_std* functions exist
 * is that you may not always have a stderr/out/in on Windows.  This
 * is generally a problem with newer versions of Windows and services.
 * 
 * The other problem is that the C library functions generally work
 * differently on Windows and Unix.  So, by using apr_file_open_std*
 * functions, you can get a handle to an APR struct that works with
 * the APR functions which are supposed to work identically on all
 * platforms.
 */
APR_DECLARE(apr_status_t) apr_file_open_stderr(apr_file_t **thefile,
                                          apr_pool_t *cont);

/**
 * open standard output as an apr file pointer.
 * @param thefile The apr file to use as stdout.
 * @param cont The pool to allocate the file out of.
 * 
 * @remark The only reason that the apr_file_open_std* functions exist
 * is that you may not always have a stderr/out/in on Windows.  This
 * is generally a problem with newer versions of Windows and services.
 * 
 * The other problem is that the C library functions generally work
 * differently on Windows and Unix.  So, by using apr_file_open_std*
 * functions, you can get a handle to an APR struct that works with
 * the APR functions which are supposed to work identically on all
 * platforms.
 */
APR_DECLARE(apr_status_t) apr_file_open_stdout(apr_file_t **thefile,
                                          apr_pool_t *cont);

/**
 * open standard input as an apr file pointer.
 * @param thefile The apr file to use as stdin.
 * @param cont The pool to allocate the file out of.
 * 
 * @remark The only reason that the apr_file_open_std* functions exist
 * is that you may not always have a stderr/out/in on Windows.  This
 * is generally a problem with newer versions of Windows and services.
 * 
 * The other problem is that the C library functions generally work
 * differently on Windows and Unix.  So, by using apr_file_open_std*
 * functions, you can get a handle to an APR struct that works with
 * the APR functions which are supposed to work identically on all
 * platforms.
 */
APR_DECLARE(apr_status_t) apr_file_open_stdin(apr_file_t **thefile,
                                              apr_pool_t *cont);

/**
 * Read data from the specified file.
 * @param thefile The file descriptor to read from.
 * @param buf The buffer to store the data to.
 * @param nbytes On entry, the number of bytes to read; on exit, the number of bytes read.
 * @remark apr_file_read will read up to the specified number of bytes, but 
 *         never more.  If there isn't enough data to fill that number of 
 *         bytes, all of the available data is read.  The third argument is 
 *         modified to reflect the number of bytes read.  If a char was put 
 *         back into the stream via ungetc, it will be the first character 
 *         returned. 
 *
 *         It is not possible for both bytes to be read and an APR_EOF or other 
 *         error to be returned.
 *
 *         APR_EINTR is never returned.
 */
APR_DECLARE(apr_status_t) apr_file_read(apr_file_t *thefile, void *buf,
                                   apr_size_t *nbytes);

/**
 * Write data to the specified file.
 * @param thefile The file descriptor to write to.
 * @param buf The buffer which contains the data.
 * @param nbytes On entry, the number of bytes to write; on exit, the number 
 *               of bytes written.
 * @remark apr_file_write will write up to the specified number of bytes, but never 
 *      more.  If the OS cannot write that many bytes, it will write as many 
 *      as it can.  The third argument is modified to reflect the * number 
 *      of bytes written. 
 *
 *      It is possible for both bytes to be written and an error to be returned.
 *
 *      APR_EINTR is never returned.
 */
APR_DECLARE(apr_status_t) apr_file_write(apr_file_t *thefile, const void *buf,
                                    apr_size_t *nbytes);

/**
 * Write data from iovec array to the specified file.
 * @param thefile The file descriptor to write to.
 * @param vec The array from which to get the data to write to the file.
 * @param nvec The number of elements in the struct iovec array. This must 
 *             be smaller than APR_MAX_IOVEC_SIZE.  If it isn't, the function 
 *             will fail with APR_EINVAL.
 * @param nbytes The number of bytes written.
 * @remark It is possible for both bytes to be written and an error to be returned.
 *      APR_EINTR is never returned.
 *
 *      apr_file_writev is available even if the underlying operating system 
 *
 *      doesn't provide writev().
 */
APR_DECLARE(apr_status_t) apr_file_writev(apr_file_t *thefile,
                                     const struct iovec *vec,
                                     apr_size_t nvec, apr_size_t *nbytes);

/**
 * Read data from the specified file, ensuring that the buffer is filled
 * before returning.
 * @param thefile The file descriptor to read from.
 * @param buf The buffer to store the data to.
 * @param nbytes The number of bytes to read.
 * @param bytes_read If non-NULL, this will contain the number of bytes read.
 * @remark apr_file_read will read up to the specified number of bytes, but never 
 *      more.  If there isn't enough data to fill that number of bytes, 
 *      then the process/thread will block until it is available or EOF 
 *      is reached.  If a char was put back into the stream via ungetc, 
 *      it will be the first character returned. 
 *
 *      It is possible for both bytes to be read and an error to be 
 *      returned.  And if *bytes_read is less than nbytes, an
 *      accompanying error is _always_ returned.
 *
 *      APR_EINTR is never returned.
 */
APR_DECLARE(apr_status_t) apr_file_read_full(apr_file_t *thefile, void *buf,
                                        apr_size_t nbytes,
                                        apr_size_t *bytes_read);

/**
 * Write data to the specified file, ensuring that all of the data is
 * written before returning.
 * @param thefile The file descriptor to write to.
 * @param buf The buffer which contains the data.
 * @param nbytes The number of bytes to write.
 * @param bytes_written If non-NULL, this will contain the number of bytes written.
 * @remark apr_file_write will write up to the specified number of bytes, but never 
 *      more.  If the OS cannot write that many bytes, the process/thread 
 *      will block until they can be written. Exceptional error such as 
 *      "out of space" or "pipe closed" will terminate with an error.
 *
 *      It is possible for both bytes to be written and an error to be 
 *      returned.  And if *bytes_written is less than nbytes, an
 *      accompanying error is _always_ returned.
 *
 *      APR_EINTR is never returned.
 */
APR_DECLARE(apr_status_t) apr_file_write_full(apr_file_t *thefile, const void *buf,
                                         apr_size_t nbytes, 
                                         apr_size_t *bytes_written);

/**
 * put a character into the specified file.
 * @param ch The character to write.
 * @param thefile The file descriptor to write to
 */
APR_DECLARE(apr_status_t) apr_file_putc(char ch, apr_file_t *thefile);

/**
 * get a character from the specified file.
 * @param ch The character to read into
 * @param thefile The file descriptor to read from
 */
APR_DECLARE(apr_status_t) apr_file_getc(char *ch, apr_file_t *thefile);

/**
 * put a character back onto a specified stream.
 * @param ch The character to write.
 * @param thefile The file descriptor to write to
 */
APR_DECLARE(apr_status_t) apr_file_ungetc(char ch, apr_file_t *thefile);

/**
 * Get a string from a specified file.
 * @param str The buffer to store the string in. 
 * @param len The length of the string
 * @param thefile The file descriptor to read from
 * @remark The buffer will be '\0'-terminated if any characters are stored.
 */
APR_DECLARE(apr_status_t) apr_file_gets(char *str, int len, apr_file_t *thefile);

/**
 * Put the string into a specified file.
 * @param str The string to write. 
 * @param thefile The file descriptor to write to
 */
APR_DECLARE(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile);

/**
 * Flush the file's buffer.
 * @param thefile The file descriptor to flush
 */
APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile);

/**
 * duplicate the specified file descriptor.
 * @param new_file The structure to duplicate into. 
 * @param old_file The file to duplicate.
 * @param p The pool to use for the new file.
 * @remark *new_file must point to a valid apr_file_t, or point to NULL
 */         
APR_DECLARE(apr_status_t) apr_file_dup(apr_file_t **new_file,
                                      apr_file_t *old_file,
                                      apr_pool_t *p);

/**
 * duplicate the specified file descriptor and close the original
 * @param new_file The old file that is to be closed and reused
 * @param old_file The file to duplicate
 * @param p        The pool to use for the new file
 *
 * @remark new_file MUST point at a valid apr_file_t. It cannot be NULL
 */
APR_DECLARE(apr_status_t) apr_file_dup2(apr_file_t *new_file,
                                        apr_file_t *old_file,
                                        apr_pool_t *p);

/**
 * move the specified file descriptor to a new pool
 * @param new_file Pointer in which to return the new apr_file_t
 * @param old_file The file to move
 * @param p        The pool to which the descriptor is to be moved
 * @remark Unlike apr_file_dup2(), this function doesn't do an
 *         OS dup() operation on the underlying descriptor; it just
 *         moves the descriptor's apr_file_t wrapper to a new pool.
