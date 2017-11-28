 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#include "squid.h"
#include "Store.h"
#include "fde.h"
#include "ufscommon.h"
#include "StoreSwapLogData.h"
#include "ConfigOption.h"
#include "DiskIO/DiskIOStrategy.h"
#include "DiskIO/DiskIOModule.h"
#include "Parsing.h"
#include "SquidMath.h"
#include "SquidTime.h"
#include "SwapDir.h"

int UFSSwapDir::NumberOfUFSDirs = 0;
int *UFSSwapDir::UFSDirToGlobalDirMapping = NULL;

/*
 * storeUfsDirCheckObj
 *
 * This routine is called by storeDirSelectSwapDir to see if the given
 * object is able to be stored on this filesystem. UFS filesystems will
 * happily store anything as long as the LRU time isn't too small.
 */
int
UFSSwapDir::canStore(StoreEntry const &e)const
{
    if (IO->shedLoad())
        return -1;

    return IO->load();
}


/* ========== LOCAL FUNCTIONS ABOVE, GLOBAL FUNCTIONS BELOW ========== */

void
UFSSwapDir::parseSizeL1L2()
{
    int i = GetInteger();
    if (i <= 0)
        fatal("UFSSwapDir::parseSizeL1L2: invalid size value");

    size_t size = i << 10;		/* Mbytes to kbytes */

    /* just reconfigure it */
    if (reconfiguring) {
        if (size == max_size)
            debugs(3, 2, "Cache dir '" << path << "' size remains unchanged at " << size << " KB");
        else
            debugs(3, 1, "Cache dir '" << path << "' size changed to " << size << " KB");
    }

    max_size = size;

    l1 = GetInteger();

