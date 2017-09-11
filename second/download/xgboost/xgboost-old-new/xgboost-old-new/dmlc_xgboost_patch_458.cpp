@@ -15,6 +15,8 @@
  */
 #include <cstdio>
 #include <vector>
+#include <string>
+#include <cstring>
 #include "../booster/xgboost_data.h"
 #include "../utils/xgboost_utils.h"
 #include "../utils/xgboost_stream.h"
@@ -106,15 +108,24 @@ namespace xgboost{
                 data.LoadBinary(fs);
                 info.labels.resize(data.NumRow());
                 utils::Assert(fs.Read(&info.labels[0], sizeof(float)* data.NumRow()) != 0, "DMatrix LoadBinary");
+                {// load in group ptr
+                    unsigned ngptr;
+                    if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
+                        info.group_ptr.resize( ngptr );
+                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                    }
+                }
                 fs.Close();
                 // initialize column support as well
                 data.InitData();
                 
                 if (!silent){
                     printf("%ux%u matrix with %lu entries is loaded from %s\n",
                            (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
+                    if( info.group_ptr.size() != 0 ){
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                    }
                 }
-                this->TryLoadGroup(fname, silent);
                 this->TryLoadWeight(fname, silent);
                 return true;
             }
@@ -129,11 +140,20 @@ namespace xgboost{
                 
                 utils::FileStream fs(utils::FopenCheck(fname, "wb"));
                 data.SaveBinary(fs);
-                fs.Write(&info.labels[0], sizeof(float)* data.NumRow());
+                utils::Assert( info.labels.size() == data.NumRow(), "label size is not consistent with feature matrix size" );
+                fs.Write(&info.labels[0], sizeof(float) * data.NumRow());
+                {// write out group ptr
+                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );                    
+                    fs.Write(&ngptr, sizeof(unsigned) );
+                    fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                }
                 fs.Close();
                 if (!silent){
                     printf("%ux%u matrix with %lu entries is saved to %s\n",
                        (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
+                    if( info.group_ptr.size() != 0 ){
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                    }
                 }
             }
             /*!