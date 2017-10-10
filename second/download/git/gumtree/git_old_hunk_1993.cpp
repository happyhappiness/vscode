 */

#include "cache.h"
#include "credential.h"
#include "exec_cmd.h"
#include "run-command.h"
#ifdef NO_OPENSSL
typedef void *SSL;
#endif

static const char imap_send_usage[] = "git imap-send < <mbox>";

#undef DRV_OK
#define DRV_OK          0
#define DRV_MSG_BAD     -1
#define DRV_BOX_BAD     -2
#define DRV_STORE_BAD   -3

static int Verbose, Quiet;

__attribute__((format (printf, 1, 2)))
static void imap_info(const char *, ...);
__attribute__((format (printf, 1, 2)))
static void imap_warn(const char *, ...);

static char *next_arg(char **);
