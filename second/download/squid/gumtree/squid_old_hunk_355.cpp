 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 */

#include "squid-old.h"
#include "acl/TimeData.h"
#include "acl/Checklist.h"
#include "wordlist.h"

ACLTimeData::ACLTimeData () : weekbits (0), start (0), stop (0), next (NULL) {}

ACLTimeData::ACLTimeData(ACLTimeData const &old) : weekbits(old.weekbits), start (old.start), stop (old.stop), next (NULL)
{
