 *
 * -----------------------------------------------------------------------------
 */

#include "squid.h"
#include "rfc1738.h"
#include "compat/getaddrinfo.h"
#include "compat/getnameinfo.h"

#include "negotiate_kerberos.h"

#if HAVE_PAC_SUPPORT

static int bpos;
static krb5_data *ad_data;
static unsigned char *p;

int
check_k5_err(krb5_context context, const char *function, krb5_error_code code)
{
    const char *errmsg;

    if (code) {
        errmsg = krb5_get_error_message(context, code);
        debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, errmsg);
        fprintf(stderr, "%s| %s: ERROR: %s: %s\n", LogTime(), PROGRAM, function, errmsg);
        krb5_free_error_message(context, errmsg);
    }
    return code;
}

void
align(int n)
{
    if ( bpos % n != 0 ) {
        int al;
