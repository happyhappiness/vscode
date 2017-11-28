  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
  *
  */
 
-#include "squid.h"
+#include "squid-old.h"
 #include "Store.h"
 #include "fde.h"
 #include "ufscommon.h"
 #include "StoreSwapLogData.h"
 #include "ConfigOption.h"
 #include "DiskIO/DiskIOStrategy.h"
 #include "DiskIO/DiskIOModule.h"
+#include "FileMap.h"
 #include "Parsing.h"
 #include "SquidMath.h"
 #include "SquidTime.h"
+#include "StatCounters.h"
 #include "SwapDir.h"
+#include "swap_log_op.h"
 
 int UFSSwapDir::NumberOfUFSDirs = 0;
 int *UFSSwapDir::UFSDirToGlobalDirMapping = NULL;
 
 /*
  * storeUfsDirCheckObj
  *
  * This routine is called by storeDirSelectSwapDir to see if the given
  * object is able to be stored on this filesystem. UFS filesystems will
  * happily store anything as long as the LRU time isn't too small.
  */
-int
-UFSSwapDir::canStore(StoreEntry const &e)const
+bool
+UFSSwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
 {
+    if (!SwapDir::canStore(e, diskSpaceNeeded, load))
+        return false;
+
     if (IO->shedLoad())
-        return -1;
+        return false;
 
-    return IO->load();
+    load = IO->load();
+    return true;
 }
 
 
 /* ========== LOCAL FUNCTIONS ABOVE, GLOBAL FUNCTIONS BELOW ========== */
 
 void
 UFSSwapDir::parseSizeL1L2()
 {
     int i = GetInteger();
     if (i <= 0)
         fatal("UFSSwapDir::parseSizeL1L2: invalid size value");
 
-    size_t size = i << 10;		/* Mbytes to kbytes */
+    const uint64_t size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes
 
     /* just reconfigure it */
     if (reconfiguring) {
-        if (size == max_size)
-            debugs(3, 2, "Cache dir '" << path << "' size remains unchanged at " << size << " KB");
+        if (size == maxSize())
+            debugs(3, 2, "Cache dir '" << path << "' size remains unchanged at " << i << " MB");
         else
-            debugs(3, 1, "Cache dir '" << path << "' size changed to " << size << " KB");
+            debugs(3, 1, "Cache dir '" << path << "' size changed to " << i << " MB");
     }
 
     max_size = size;
 
     l1 = GetInteger();
 
