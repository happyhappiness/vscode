 *
 * -----------------------------------------------------------------------------
 */

#include "squid.h"
#include "rfc1738.h"

#include "negotiate_kerberos.h"

#if HAVE_GSSAPI && HAVE_PAC_SUPPORT

static int bpos;
static krb5_data *ad_data;
static unsigned char *p;

extern int
check_k5_err(krb5_context context, const char *function, krb5_error_code code);

void
align(int n)
{
    if ( bpos % n != 0 ) {
        int al;
