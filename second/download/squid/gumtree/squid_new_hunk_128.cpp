 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 *
 * Copyright (c) 2003, Robert Collins <robertc@squid-cache.org>
 */

#include "squid.h"

#if USE_DELAY_POOLS
#include "squid-old.h"
#include "DelayBucket.h"
#include "DelaySpec.h"
#include "Store.h"

void
DelayBucket::stats(StoreEntry *entry)const
{
    storeAppendPrintf(entry, "%d", level());
}

