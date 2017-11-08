static apr_status_t strtoff(apr_off_t *offset, const char *nptr,
                           char **endptr, int base)
{
   errno = 0;
   if (sizeof(apr_off_t) == 4) {
       *offset = strtol(nptr, endptr, base);
   }
   else {
       *offset = apr_strtoi64(nptr, endptr, base);
   }
   return APR_FROM_OS_ERROR(errno);
}