 
 #include <curl/mprintf.h>
 /* this is still a public header file that provides the curl_mprintf()
    functions while they still are offered publicly. They will be made library-
    private one day */
 
-#include "strequal.h"
-/* "strequal.h" provides the strequal protos */
+#include "strcase.h"
+/* "strcase.h" provides the strcasecompare protos */
 
 #include "strtoofft.h"
 /* "strtoofft.h" provides this function: curlx_strtoofft(), returns a
    curl_off_t number from a given string.
 */
 
