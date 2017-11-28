 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */
#include "squid.h"
#include "acl/Acl.h"
#include "acl/Checklist.h"
#include "acl/Gadgets.h"
#include "anyp/PortCfg.h"
#include "cache_cf.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "dlink.h"
#include "globals.h"
#include "profiler/Profiler.h"
#include "SquidConfig.h"

const ACLFlag ACLFlags::NoFlags[1] = {ACL_F_END};

const char *AclMatchedName = NULL;

bool ACLFlags::supported(const ACLFlag f) const
{
    if (f == ACL_F_REGEX_CASE)
        return true;
    return (supported_.find(f) != std::string::npos);
}

void
ACLFlags::parseFlags()
{
    char *nextToken;
    while ((nextToken = ConfigParser::strtokFile()) != NULL && nextToken[0] == '-') {

        //if token is the "--" break flag
        if (strcmp(nextToken, "--") == 0)
            break;

        for (const char *flg = nextToken+1; *flg!='\0'; flg++ ) {
            if (supported(*flg)) {
                makeSet(*flg);
            } else {
                debugs(28, 0, HERE << "Flag '" << *flg << "' not supported");
                self_destruct();
            }
        }
    }

    /*Regex code needs to parse -i file*/
    if ( isSet(ACL_F_REGEX_CASE))
        ConfigParser::strtokFilePutBack("-i");

    if (nextToken != NULL && strcmp(nextToken, "--") != 0 )
        ConfigParser::strtokFileUndo();
}

const char *
ACLFlags::flagsStr() const
{
    static char buf[64];
    if (flags_ == 0)
        return "";

    char *s = buf;
    *s++ = '-';
    for (ACLFlag f = 'A'; f <= 'z'; f++) {
        // ACL_F_REGEX_CASE (-i) flag handled by ACLRegexData class, ignore
        if (isSet(f) && f != ACL_F_REGEX_CASE)
            *s++ = f;
    }
    *s = '\0';
    return buf;
}

void *
ACL::operator new (size_t byteCount)
{
    fatal ("unusable ACL::new");
    return (void *)1;
}
