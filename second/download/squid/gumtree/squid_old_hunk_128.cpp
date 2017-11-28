 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 */

#include "config.h"

#if DELAY_POOLS
#include "squid.h"
#include "DelayBucket.h"
#include "DelaySpec.h"
#include "Store.h"

#if DEAD_CODE // ?
#include "DelayPools.h"
#include "StoreClient.h"
#include "MemObject.h"
#include "client_side_request.h"
#include "acl/Checklist.h"
#include "acl/Acl.h"
#include "ConfigParser.h"
#include "DelayId.h"
#include "Array.h"
#include "String.h"
#include "CommonPool.h"
#include "CompositePoolNode.h"
#include "DelayPool.h"
#include "DelayVector.h"
#include "NullDelayId.h"
#endif

void
DelayBucket::stats(StoreEntry *entry)const
{
    storeAppendPrintf(entry, "%d", level());
}

