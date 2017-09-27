#include <sys/sem.h>
#endif
#ifdef HAVE_SYS_PRCTL_H
#include <sys/prctl.h>
#endif

unixd_config_rec ap_unixd_config;

APLOG_USE_MODULE(core);

AP_DECLARE(void) ap_unixd_set_rlimit(cmd_parms *cmd, struct rlimit **plimit,
                                     const char *arg,
                                     const char * arg2, int type)
{
#if (defined(RLIMIT_CPU) || defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_NPROC) || defined(RLIMIT_AS)) && APR_HAVE_STRUCT_RLIMIT && APR_HAVE_GETRLIMIT
    char *str;
    struct rlimit *limit;
    /* If your platform doesn't define rlim_t then typedef it in ap_config.h */
    rlim_t cur = 0;
