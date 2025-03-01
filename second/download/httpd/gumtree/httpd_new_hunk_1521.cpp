 * limitations under the License.
 */

#include "apr_strings.h"

#include "ap_config.h"
#include "ap_provider.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"

#include "mod_auth.h"

typedef struct {
        int dummy;  /* just here to stop compiler warnings for now. */
} authz_user_config_rec;

static void *create_authz_user_dir_config(apr_pool_t *p, char *d)
{
    authz_user_config_rec *conf = apr_palloc(p, sizeof(*conf));

    return conf;
}

static const command_rec authz_user_cmds[] =
{
    {NULL}
};

module AP_MODULE_DECLARE_DATA authz_user_module;

static authz_status user_check_authorization(request_rec *r,
                                             const char *require_args)
{
    const char *t, *w;

    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    t = require_args;
    while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
        if (!strcmp(r->user, w)) {
            return AUTHZ_GRANTED;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "access to %s failed, reason: user '%s' does not meet "
                  "'require'ments for user to be allowed access",
                  r->uri, r->user);

    return AUTHZ_DENIED;
}

static authz_status validuser_check_authorization(request_rec *r, const char *require_line)
{
    if (!r->user) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "access to %s failed, reason: no authenticated user", r->uri);
        return AUTHZ_DENIED;
    }

    return AUTHZ_GRANTED;
}

static const authz_provider authz_user_provider =
{
    &user_check_authorization,
};
static const authz_provider authz_validuser_provider =
{
    &validuser_check_authorization,
};

static void register_hooks(apr_pool_t *p)
{
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "user",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_user_provider, AP_AUTH_INTERNAL_PER_CONF);
    ap_register_auth_provider(p, AUTHZ_PROVIDER_GROUP, "valid-user",
                              AUTHZ_PROVIDER_VERSION,
                              &authz_validuser_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
}

AP_DECLARE_MODULE(authz_user) =
{
    STANDARD20_MODULE_STUFF,
    create_authz_user_dir_config, /* dir config creater */
    NULL,                         /* dir merger --- default is to override */
    NULL,                         /* server config */
    NULL,                         /* merge server config */
