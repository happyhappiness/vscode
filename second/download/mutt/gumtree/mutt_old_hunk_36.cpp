 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 */ 

#include "mutt.h"
#include "history.h"

/* global vars used for the string-history routines */

struct history
{
  char **hist;
  short cur;
  short last;
}; 

static struct history History[HC_LAST];
static int OldSize = 0;

static void init_history (struct history *h)
{
  int i;

  if(OldSize)
  {
    if (h->hist)
    {
      for (i = 0 ; i < OldSize ; i ++)
	safe_free ((void **) &h->hist[i]);
      safe_free ((void **) &h->hist);
    }
  }
  
  if (HistSize)
    h->hist = safe_calloc (HistSize, sizeof (char *));
  
  h->cur = 0;
  h->last = 0;
}

void mutt_init_history(void)
{
  history_class_t hclass;
  
  if (HistSize == OldSize)
    return;
