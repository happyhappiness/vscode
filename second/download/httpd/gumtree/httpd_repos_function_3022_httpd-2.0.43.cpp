static int include_hdrs_in_length(void)
{
#ifdef HAVE_SYS_SYSCTL_H
/* this assumes: 
 *   if the header exits, so does the sysctlbyname() syscall, and 
 *   if the header doesn't exist, the kernel is really old
 */

/* see 
 * http://www.freebsd.org/cgi/cvsweb.cgi/src/sys/sys/param.h#rev1.61.2.29 
 * for kernel version number
 * 
 * http://www.freebsd.org/cgi/cvsweb.cgi/src/sys/kern/uipc_syscalls.c#rev1.65.2.10
 * for the sendfile patch
 */
#define KERNEL_WITH_SENDFILE_LENGTH_FIX 460001

    typedef enum { UNKNOWN = 0, 
                   NEW, 
                   OLD 
                 } api_e;

    static api_e api; 
    int kernel_version;  
    apr_size_t kernel_version_size;

    if (api != UNKNOWN) {
        return (api == OLD);
    }
    kernel_version = 0;    /* silence compiler warning */
    kernel_version_size = sizeof(kernel_version);
    if (sysctlbyname("kern.osreldate", &kernel_version, 
                     &kernel_version_size, NULL, NULL) == 0 &&
            kernel_version < KERNEL_WITH_SENDFILE_LENGTH_FIX) {
        api = OLD;
        return 1;
    }
    /* size of kern.osreldate's output might change in the future 
     * causing the sysctlbyname to fail,
     * but if it's the future, we should use the newer API 
     */
    api = NEW;
    return 0;
#else
    /* the build system's kernel is older than 3.4.  Use the old API */
    return 1;
#endif
}