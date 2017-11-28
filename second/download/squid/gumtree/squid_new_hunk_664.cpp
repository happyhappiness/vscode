 *   with MIT, Heimdal or other GSS/Kerberos libraries, and distribute
 *   the resulting executable, without including the source code for
 *   the Libraries in the source distribution.
 *
 * -----------------------------------------------------------------------------
 */

#include "squid.h"
#include "rfc1738.h"

#if HAVE_GSSAPI

#include "negotiate_kerberos.h"

#if HAVE_SYS_STAT_H
#include "sys/stat.h"
#endif
#if HAVE_UNISTD_H
#include "unistd.h"
#endif

#if HAVE_KRB5_MEMORY_KEYTAB
typedef struct _krb5_kt_list {
    struct _krb5_kt_list *next;
    krb5_keytab_entry *entry;
} *krb5_kt_list;
krb5_kt_list ktlist = NULL;

krb5_error_code krb5_free_kt_list(krb5_context context, krb5_kt_list kt_list);
krb5_error_code krb5_write_keytab(krb5_context context,
                                  krb5_kt_list kt_list,
                                  char *name);
krb5_error_code krb5_read_keytab(krb5_context context,
                                 char *name,
                                 krb5_kt_list *kt_list);
#endif /* HAVE_KRB5_MEMORY_KEYTAB */

int
check_k5_err(krb5_context context, const char *function, krb5_error_code code)
{

    if (code && code != KRB5_KT_END) {
        const char *errmsg;
        errmsg = krb5_get_error_message(context, code);
        debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, errmsg);
        fprintf(stderr, "%s| %s: ERROR: %s: %s\n", LogTime(), PROGRAM, function, errmsg);
#if HAVE_KRB5_FREE_ERROR_MESSAGE
        krb5_free_error_message(context, errmsg);
#elif HAVE_KRB5_FREE_ERROR_STRING
        krb5_free_error_string(context, (char *)errmsg);
#else
        xfree(errmsg);
#endif
    }
    return code;
}

char *
gethost_name(void)
{
    /*
     * char hostname[sysconf(_SC_HOST_NAME_MAX)];
     */
    char hostname[1024];
    struct addrinfo *hres = NULL, *hres_list;
    int rc, count;

    rc = gethostname(hostname, sizeof(hostname)-1);
    if (rc) {
        debug((char *) "%s| %s: ERROR: resolving hostname '%s' failed\n", LogTime(), PROGRAM, hostname);
        fprintf(stderr, "%s| %s: ERROR: resolving hostname '%s' failed\n",
                LogTime(), PROGRAM, hostname);
        return NULL;
    }
    rc = getaddrinfo(hostname, NULL, NULL, &hres);
    if (rc != 0 || hres == NULL ) {
        debug((char *) "%s| %s: ERROR: resolving hostname with getaddrinfo: %s failed\n",
              LogTime(), PROGRAM, gai_strerror(rc));
        fprintf(stderr,
                "%s| %s: ERROR: resolving hostname with getaddrinfo: %s failed\n",
                LogTime(), PROGRAM, gai_strerror(rc));
        return NULL;
    }
    hres_list = hres;
