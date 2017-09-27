#include "apr.h"
#include "apr_strings.h"
#include "apr_getopt.h"
#include "apr_general.h"
#include "apr_lib.h"
#include "apr_md5.h"
#include "apr_time.h"
#include "apr_version.h"
#include "apu_version.h"

#define APR_WANT_STDIO
#define APR_WANT_STRFUNC
#include "apr_want.h"

#define CORE_PRIVATE
#include "ap_config.h"
#include "httpd.h"
#include "http_main.h"
#include "http_log.h"
#include "http_config.h"
#include "http_vhost.h"
#include "apr_uri.h"
#include "util_ebcdic.h"
#include "ap_mpm.h"
#include "mpm_common.h"

/* WARNING: Win32 binds http_main.c dynamically to the server. Please place
 *          extern functions and global data in another appropriate module.
 *
 * Most significant main() global data can be found in http_config.c
 */

/* XXX - We should be able to grab the per-MPM settings here too */
static void show_compile_settings(void)
{
    printf("Server version: %s\n", ap_get_server_version());
    printf("Server built:   %s\n", ap_get_server_built());
    printf("Server's Module Magic Number: %u:%u\n",
           MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
    printf("Server loaded:  APR %s, APR-UTIL %s\n",
           apr_version_string(), apu_version_string());
    printf("Compiled using: APR %s, APR-UTIL %s\n",
           APR_VERSION_STRING, APU_VERSION_STRING);
    /* sizeof(foo) is long on some platforms so we might as well
     * make it long everywhere to keep the printf format
     * consistent
     */
    printf("Architecture:   %ld-bit\n", 8 * (long)sizeof(void *));
    printf("Server compiled with....\n");
#ifdef BIG_SECURITY_HOLE
    printf(" -D BIG_SECURITY_HOLE\n");
#endif

#ifdef SECURITY_HOLE_PASS_AUTHORIZATION
    printf(" -D SECURITY_HOLE_PASS_AUTHORIZATION\n");
#endif

#ifdef APACHE_MPM_DIR
    printf(" -D APACHE_MPM_DIR=\"%s\"\n", APACHE_MPM_DIR);
#endif

#ifdef HAVE_SHMGET
    printf(" -D HAVE_SHMGET\n");
#endif

