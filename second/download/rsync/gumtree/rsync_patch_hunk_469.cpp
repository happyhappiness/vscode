    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
 
 #include "rsync.h"
-#include "lib/zlib.h"
+#include "zlib/zlib.h"
 
 extern int do_compression;
 
 
 /* non-compressing recv token */
 static int simple_recv_token(int f,char **data)
 {
-  static int residue;
-  static char *buf;
-  int n;
-
-  if (!buf) {
-    buf = (char *)malloc(CHUNK_SIZE);
-    if (!buf) out_of_memory("simple_recv_token");
-  }
-
-
-  if (residue == 0) {
-    int i = read_int(f);
-    if (i <= 0) return i;
-    residue = i;
-  }
-
-  *data = buf;
-  n = MIN(CHUNK_SIZE,residue);
-  residue -= n;
-  read_buf(f,buf,n);
-  return n;
-}
+	static int residue;
+	static char *buf;
+	int n;
+
+	if (!buf) {
+		buf = (char *)malloc(CHUNK_SIZE);
+		if (!buf) out_of_memory("simple_recv_token");
+	}
 
+	if (residue == 0) {
+		int i = read_int(f);
+		if (i <= 0) return i;
+		residue = i;
+	}
 
-/* non-compressing send token */
-static void simple_send_token(int f,int token,
-			      struct map_struct *buf,int offset,int n)
-{
-  if (n > 0) {
-    int l = 0;
-    while (l < n) {
-      int n1 = MIN(CHUNK_SIZE,n-l);
-      write_int(f,n1);
-      write_buf(f,map_ptr(buf,offset+l,n1),n1);
-      l += n1;
-    }
-  }
-  write_int(f,-(token+1));
+	*data = buf;
+	n = MIN(CHUNK_SIZE,residue);
+	residue -= n;
+	read_buf(f,buf,n);
+	return n;
 }
 
 
-/* Memory allocation/freeing routines, called by zlib stuff. */
-static void *
-z_alloc(void *opaque, uInt items, uInt size)
+/* non-compressing send token */
+static void simple_send_token(int f,int token,
+			      struct map_struct *buf,OFF_T offset,int n)
 {
-    return malloc(items * size);
+	if (n > 0) {
+		int l = 0;
+		while (l < n) {
+			int n1 = MIN(CHUNK_SIZE,n-l);
+			write_int(f,n1);
+			write_buf(f,map_ptr(buf,offset+l,n1),n1);
+			l += n1;
+		}
+	}
+	/* a -2 token means to send data only and no token */
+	if (token != -2) {
+		write_int(f,-(token+1));
+	}
 }
 
-static void
-z_free(void *opaque, void *adrs, uInt nbytes)
-{
-    free(adrs);
-}
 
 /* Flag bytes in compressed stream are encoded as follows: */
 #define END_FLAG	0	/* that's all folks */
 #define TOKEN_LONG	0x20	/* followed by 32-bit token number */
 #define TOKENRUN_LONG	0x21	/* ditto with 16-bit run count */
 #define DEFLATED_DATA	0x40	/* + 6-bit high len, then low len byte */
