 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "squid-old.h"
#include "structs.h"

#include "ConfigParser.h"
#include "acl/Gadgets.h"
#include "Store.h"
#include "Array.h"    // really Vector
#include "acl/FilledChecklist.h"
#include "adaptation/Config.h"
#include "adaptation/Service.h"
#include "adaptation/AccessRule.h"
#include "adaptation/ServiceGroups.h"
#include "adaptation/History.h"
#include "HttpRequest.h"


bool Adaptation::Config::Enabled = false;
char *Adaptation::Config::masterx_shared_name = NULL;
int Adaptation::Config::service_iteration_limit = 16;
int Adaptation::Config::send_client_ip = false;
int Adaptation::Config::send_username = false;
int Adaptation::Config::use_indirect_client = true;
Adaptation::Config::MetaHeaders Adaptation::Config::metaHeaders;


Adaptation::Config::MetaHeader::Value::~Value()
{
    aclDestroyAclList(&aclList);
}

Adaptation::Config::MetaHeader::Value::Pointer
Adaptation::Config::MetaHeader::addValue(const String &value)
{
    Value::Pointer v = new Value(value);
    values.push_back(v);
    return v;
}

const char *
Adaptation::Config::MetaHeader::match(HttpRequest *request, HttpReply *reply)
{

    typedef Values::iterator VLI;
    ACLFilledChecklist ch(NULL, request, NULL);
    if (reply)
        ch.reply = HTTPMSGLOCK(reply);

    for (VLI i = values.begin(); i != values.end(); ++i ) {
        const int ret= ch.fastCheck((*i)->aclList);
        debugs(93, 5, HERE << "Check for header name: " << name << ": " << (*i)->value
               <<", HttpRequest: " << request << " HttpReply: " << reply << " matched: " << ret);
        if (ret == ACCESS_ALLOWED)
            return (*i)->value.termedBuf();
    }
    return NULL;
}

Adaptation::Config::MetaHeader::Pointer
Adaptation::Config::addMetaHeader(const String &headerName)
{
    typedef MetaHeaders::iterator AMLI;
    for (AMLI i = metaHeaders.begin(); i != metaHeaders.end(); ++i) {
        if ((*i)->name == headerName)
            return (*i);
    }

    MetaHeader::Pointer meta = new MetaHeader(headerName);
    metaHeaders.push_back(meta);
    return meta;
}


Adaptation::ServiceConfig*
Adaptation::Config::newServiceConfig() const
{
    return new ServiceConfig();
}

void
Adaptation::Config::removeService(const String& service)
{
    removeRule(service);
    const Groups& groups = AllGroups();
    for (unsigned int i = 0; i < groups.size(); ) {
        const ServiceGroupPointer group = groups[i];
        const ServiceGroup::Store& services = group->services;
        typedef ServiceGroup::Store::const_iterator SGSI;
        for (SGSI it = services.begin(); it != services.end(); ++it) {
            if (*it == service) {
                group->removedServices.push_back(service);
                group->services.prune(service);
                debugs(93, 5, HERE << "adaptation service " << service <<
                       " removed from group " << group->id);
                break;
            }
        }
        if (services.empty()) {
            removeRule(group->id);
            AllGroups().prune(group);
        } else {
            ++i;
        }
    }
}

void
Adaptation::Config::removeRule(const String& id)
{
    typedef AccessRules::const_iterator ARI;
    const AccessRules& rules = AllRules();
    for (ARI it = rules.begin(); it != rules.end(); ++it) {
        AccessRule* rule = *it;
        if (rule->groupId == id) {
            debugs(93, 5, HERE << "removing access rules for:" << id);
            AllRules().prune(rule);
            delete (rule);
            break;
        }
    }
}

void
Adaptation::Config::clear()
{
    debugs(93, 3, HERE << "rules: " << AllRules().size() << ", groups: " <<
           AllGroups().size() << ", services: " << serviceConfigs.size());
    typedef ServiceConfigs::const_iterator SCI;
    const ServiceConfigs& configs = serviceConfigs;
    for (SCI cfg = configs.begin(); cfg != configs.end(); ++cfg)
        removeService((*cfg)->key);
    serviceConfigs.clean();
    debugs(93, 3, HERE << "rules: " << AllRules().size() << ", groups: " <<
           AllGroups().size() << ", services: " << serviceConfigs.size());
}

void
Adaptation::Config::parseService()
{
    ServiceConfigPointer cfg = newServiceConfig();
    if (!cfg->parse()) {
        fatalf("%s:%d: malformed adaptation service configuration",
               cfg_filename, config_lineno);
    }
    serviceConfigs.push_back(cfg);
}
