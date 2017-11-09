static void ssl_util_thr_id(CRYPTO_THREADID *id)
{
    /* OpenSSL needs this to return an unsigned long.  On OS/390, the pthread
     * id is a structure twice that big.  Use the TCB pointer instead as a
     * unique unsigned long.
     */
#ifdef __MVS__
    struct PSA {
        char unmapped[540]; /* PSATOLD is at offset 540 in the PSA */
        unsigned long PSATOLD;
    } *psaptr = 0; /* PSA is at address 0 */

    CRYPTO_THREADID_set_numeric(id, psaptr->PSATOLD);
#else
    CRYPTO_THREADID_set_numeric(id, (unsigned long) apr_os_thread_current());
#endif
}