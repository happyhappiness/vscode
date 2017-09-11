@@ -113,6 +113,7 @@ namespace xgboost{
                     if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                         info.group_ptr.resize( ngptr );
                         utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                        utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
                     }
                 }
                 fs.Close();
@@ -123,7 +124,7 @@ namespace xgboost{
                     printf("%ux%u matrix with %lu entries is loaded from %s\n",
                            (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                     if( info.group_ptr.size() != 0 ){
-                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                     }
                 }
                 this->TryLoadWeight(fname, silent);
@@ -143,7 +144,7 @@ namespace xgboost{
                 utils::Assert( info.labels.size() == data.NumRow(), "label size is not consistent with feature matrix size" );
                 fs.Write(&info.labels[0], sizeof(float) * data.NumRow());
                 {// write out group ptr
-                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );                    
+                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );
                     fs.Write(&ngptr, sizeof(unsigned) );
                     fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
                 }
@@ -152,7 +153,7 @@ namespace xgboost{
                     printf("%ux%u matrix with %lu entries is saved to %s\n",
                        (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                     if( info.group_ptr.size() != 0 ){
-                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                     }
                 }
             }