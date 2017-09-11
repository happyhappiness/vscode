@@ -35,11 +35,17 @@ namespace xgboost{
                 std::vector<unsigned> group_ptr;
                 /*! \brief weights of each instance, optional */            
                 std::vector<float> weights;
+                /*! \brief specified root index of each instance, can be used for multi task setting*/
+                std::vector<unsigned> root_index;
                 /*! \brief get weight of each instances */
                 inline float GetWeight( size_t i ) const{
-                    if(  weights.size() != 0 ) return weights[i];
+                    if( weights.size() != 0 ) return weights[i];
                     else return 1.0f;
                 }
+                inline float GetRoot( size_t i ) const{
+                    if( root_index.size() != 0 ) return root_index[i];
+                    else return 0;
+                }
             };
         public:
             /*! \brief feature data content */
@@ -112,7 +118,10 @@ namespace xgboost{
                     unsigned ngptr;
                     if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                         info.group_ptr.resize( ngptr );
-                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                        if( ngptr != 0 ){
+                            utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                            utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
+                        }
                     }
                 }
                 fs.Close();
@@ -121,7 +130,7 @@ namespace xgboost{
                     printf("%ux%u matrix with %lu entries is loaded from %s\n",
                            (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                     if( info.group_ptr.size() != 0 ){
-                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                     }
                 }
                 this->TryLoadWeight(fname, silent);
@@ -141,16 +150,18 @@ namespace xgboost{
                 utils::Assert( info.labels.size() == data.NumRow(), "label size is not consistent with feature matrix size" );
                 fs.Write(&info.labels[0], sizeof(float) * data.NumRow());
                 {// write out group ptr
-                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );                    
+                    unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );
                     fs.Write(&ngptr, sizeof(unsigned) );
-                    fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                    if( ngptr != 0 ){
+                        fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                    }
                 }
                 fs.Close();
                 if (!silent){
                     printf("%ux%u matrix with %lu entries is saved to %s\n",
                        (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname);
                     if( info.group_ptr.size() != 0 ){
-                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size() );
+                        printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                     }
                 }
             }