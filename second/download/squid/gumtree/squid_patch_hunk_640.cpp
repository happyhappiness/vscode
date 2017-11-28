  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
+#ifndef __SQUID_HELPERS_DEFINES_H
+#define __SQUID_HELPERS_DEFINES_H
+
 /*
  * This file contains several macro definitions which are
  * useful and shared between helpers.
  */
 
-#define HELPER_INPUT_BUFFER	8196
+#define HELPER_INPUT_BUFFER 8196
 
 /* send OK result to Squid with a string parameter. */
-#define SEND_OK(x)	fprintf(stdout, "OK %s\n",x)
+#define SEND_OK(x)  fprintf(stdout, "OK %s\n",x)
 
 /* send ERR result to Squid with a string parameter. */
-#define SEND_ERR(x)	fprintf(stdout, "ERR %s\n",x)
+#define SEND_ERR(x) fprintf(stdout, "ERR %s\n",x)
 
-/* send ERR result to Squid with a string parameter. */
-#define SEND_BH(x)	fprintf(stdout, "BH %s\n",x)
+/* send BH result to Squid with a string parameter. */
+#define SEND_BH(x)  fprintf(stdout, "BH %s\n",x)
+
+/* constructs a message to Squid. */
+#define HLP_MSG(text)  "message=\"" text "\""
 
 /* send TT result to Squid with a string parameter. */
-#define SEND_TT(x)	fprintf(stdout, "TT %s\n",x)
+#define SEND_TT(x)  fprintf(stdout, "TT %s\n",x)
 
 #endif /* __SQUID_HELPERS_DEFINES_H */
+
