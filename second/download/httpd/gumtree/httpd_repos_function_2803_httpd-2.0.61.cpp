static char *apr_os_strerror(char* buf, apr_size_t bufsize, int err) 
{
#ifdef HAVE_HSTRERROR
    return stuffbuffer(buf, bufsize, hstrerror(err));
#else /* HAVE_HSTRERROR */
    const char *msg;

    switch(err) {
    case HOST_NOT_FOUND:
        msg = "Unknown host";
        break;
#if defined(NO_DATA)
    case NO_DATA:
#if defined(NO_ADDRESS) && (NO_DATA != NO_ADDRESS)
    case NO_ADDRESS:
#endif
        msg = "No address for host";
        break;
#elif defined(NO_ADDRESS)
    case NO_ADDRESS:
        msg = "No address for host";
        break;
#endif /* NO_DATA */
    default:
        msg = "Unrecognized resolver error";
    }
    return stuffbuffer(buf, bufsize, msg);
#endif /* HAVE_STRERROR */
}