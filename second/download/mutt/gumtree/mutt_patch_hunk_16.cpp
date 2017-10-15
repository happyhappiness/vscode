  *     but WITHOUT ANY WARRANTY; without even the implied warranty of
  *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *     GNU General Public License for more details.
  * 
  *     You should have received a copy of the GNU General Public License
  *     along with this program; if not, write to the Free Software
- *     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
+ *     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
  */ 
 
+#if HAVE_CONFIG_H
+# include "config.h"
+#endif
+
 #include "mutt.h"
 #include "mailbox.h"
 #include "mx.h"
 #include "copy.h"
 #include "rfc2047.h"
 #include "mime.h"
-
-#ifdef HAVE_PGP
-#include "pgp.h"
-#endif
+#include "mutt_crypt.h"
+#include "mutt_idna.h"
+#include "mutt_curses.h"
 
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include <unistd.h> /* needed for SEEK_SET under SunOS 4.1.4 */
 
+static int address_header_decode (char **str);
 static int copy_delete_attach (BODY *b, FILE *fpin, FILE *fpout, char *date);
 
 /* Ok, the only reason for not merging this with mutt_copy_header()
  * below is to avoid creating a HEADER structure in message_handler().
+ * Also, this one will wrap headers much more aggressively than the other one.
  */
 int
-mutt_copy_hdr (FILE *in, FILE *out, long off_start, long off_end, int flags,
+mutt_copy_hdr (FILE *in, FILE *out, LOFF_T off_start, LOFF_T off_end, int flags,
 	       const char *prefix)
 {
   int from = 0;
   int this_is_from;
   int ignore = 0;
-  char buf[STRING]; /* should be long enough to get most fields in one pass */
+  char buf[LONG_STRING]; /* should be long enough to get most fields in one pass */
   char *nl;
   LIST *t;
   char **headers;
   int hdr_count;
   int x;
+  char *this_one = NULL;
+  size_t this_one_len = 0;
   int error;
 
-  if (ftell (in) != off_start)
-    fseek (in, off_start, 0);
+  if (ftello (in) != off_start)
+    fseeko (in, off_start, 0);
 
   buf[0] = '\n';
   buf[1] = 0;
 
   if ((flags & (CH_REORDER | CH_WEED | CH_MIME | CH_DECODE | CH_PREFIX | CH_WEED_DELIVERED)) == 0)
   {
     /* Without these flags to complicate things
      * we can do a more efficient line to line copying
      */
-    while (ftell (in) < off_end)
+    while (ftello (in) < off_end)
     {
       nl = strchr (buf, '\n');
 
       if ((fgets (buf, sizeof (buf), in)) == NULL)
 	break;
 
-      /* Is it the begining of a header? */
+      /* Is it the beginning of a header? */
       if (nl && buf[0] != ' ' && buf[0] != '\t')
       {
 	ignore = 1;
 	if (!from && mutt_strncmp ("From ", buf, 5) == 0)
 	{
 	  if ((flags & CH_FROM) == 0)
 	    continue;
 	  from = 1;
 	}
+	else if (flags & (CH_NOQFROM) &&
+			ascii_strncasecmp (">From ", buf, 6) == 0)
+		continue;
+
 	else if (buf[0] == '\n' || (buf[0] == '\r' && buf[1] == '\n'))
 	  break; /* end of header */
 
 	if ((flags & (CH_UPDATE | CH_XMIT | CH_NOSTATUS)) &&
 	    (ascii_strncasecmp ("Status:", buf, 7) == 0 ||
 	     ascii_strncasecmp ("X-Status:", buf, 9) == 0))
 	  continue;
 	if ((flags & (CH_UPDATE_LEN | CH_XMIT | CH_NOLEN)) &&
 	    (ascii_strncasecmp ("Content-Length:", buf, 15) == 0 ||
 	     ascii_strncasecmp ("Lines:", buf, 6) == 0))
 	  continue;
+	if ((flags & CH_UPDATE_REFS) &&
+	    ascii_strncasecmp ("References:", buf, 11) == 0)
+	  continue;
+	if ((flags & CH_UPDATE_IRT) &&
+	    ascii_strncasecmp ("In-Reply-To:", buf, 12) == 0)
+	  continue;
 	ignore = 0;
       }
 
       if (!ignore && fputs (buf, out) == EOF)
 	return (-1);
     }
