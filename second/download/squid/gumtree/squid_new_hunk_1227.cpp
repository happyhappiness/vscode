/* DEBUG: section 28    Access Control */

#include "squid.h"
#include "acl/Acl.h"
#include "acl/Checklist.h"
#include "acl/Gadgets.h"
#include "acl/Options.h"
#include "anyp/PortCfg.h"
#include "cache_cf.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "fatal.h"
#include "globals.h"
#include "profiler/Profiler.h"
#include "sbuf/List.h"
#include "sbuf/Stream.h"
#include "SquidConfig.h"

#include <algorithm>
#include <map>

const char *AclMatchedName = NULL;

namespace Acl {

/// ACL type name comparison functor
class TypeNameCmp {
public:
    bool operator()(TypeName a, TypeName b) const { return strcmp(a, b) < 0; }
};

/// ACL makers indexed by ACL type name
typedef std::map<TypeName, Maker, TypeNameCmp> Makers;

/// registered ACL Makers
static Makers &
TheMakers()
{
    static Makers Registry;
    return Registry;
}

/// creates an ACL object of the named (and already registered) ACL child type
static
ACL *
Make(TypeName typeName)
{
    const auto pos = TheMakers().find(typeName);
    if (pos == TheMakers().end()) {
        debugs(28, DBG_CRITICAL, "FATAL: Invalid ACL type '" << typeName << "'");
        self_destruct();
        assert(false); // not reached
    }

    ACL *result = (pos->second)(pos->first);
    debugs(28, 4, typeName << '=' << result);
    assert(result);
    return result;
}

} // namespace Acl

void
Acl::RegisterMaker(TypeName typeName, Maker maker)
{
    assert(typeName);
    assert(*typeName);
    TheMakers().emplace(typeName, maker);
}

void *
ACL::operator new (size_t)
{
    fatal ("unusable ACL::new");
