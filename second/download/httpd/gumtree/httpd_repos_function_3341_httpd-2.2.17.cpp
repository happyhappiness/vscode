static apr_status_t apr_xlate_cleanup(void *convset)
{
    apr_xlate_t *old = convset;

#if APU_HAVE_APR_ICONV
    if (old->ich != (apr_iconv_t)-1) {
        return apr_iconv_close(old->ich, old->pool);
    }

#elif APU_HAVE_ICONV
    if (old->ich != (iconv_t)-1) {
        if (iconv_close(old->ich)) {
            int rv = errno;

            /* Sometimes, iconv is not good about setting errno. */
            return rv ? rv : APR_EINVAL;
        }
    }
#endif

    return APR_SUCCESS;
}