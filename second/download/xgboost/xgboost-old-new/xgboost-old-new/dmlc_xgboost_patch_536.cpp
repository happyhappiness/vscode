@@ -8,6 +8,7 @@
  */
 #include <vector>
 #include "../utils/xgboost_utils.h"
+#include "../utils/xgboost_fmap.h"
 #include "../utils/xgboost_stream.h"
 #include "../utils/xgboost_config.h"
 #include "xgboost_data.h"
@@ -107,8 +108,10 @@ namespace xgboost{
             /*! 
              * \brief dump model into text file
              * \param fo output stream 
-             */        
-            virtual void DumpModel( FILE *fo ){
+             * \param fmap feature map that may help give interpretations of feature
+             * \param with_stats whether print statistics
+             */
+            virtual void DumpModel( FILE *fo, const utils::FeatMap& fmap, bool with_stats = false ){
                 utils::Error( "not implemented" );                
             }
         public: