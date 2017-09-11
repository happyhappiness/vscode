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
@@ -113,12 +119,13 @@ namespace xgboost{
                     if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                         info.group_ptr.resize( ngptr );
                         utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
-                        utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
+                        if( ngptr != 0 ){
+                            utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                            utils::Assert( info.group_ptr.back() == data.NumRow(), "number of group must match number of record" );
+                        }
                     }
                 }
                 fs.Close();
-                // initialize column support as well
-                data.InitData();
                 
                 if (!silent){
                     printf("%ux%u matrix with %lu entries is loaded from %s\n",
@@ -146,7 +153,9 @@ namespace xgboost{
                 {// write out group ptr
                     unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );
                     fs.Write(&ngptr, sizeof(unsigned) );
-                    fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                    if( ngptr != 0 ){
+                        fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                    }
                 }
                 fs.Close();
                 if (!silent){
@@ -169,7 +178,11 @@ namespace xgboost{
             inline void CacheLoad(const char *fname, bool silent = false, bool savebuffer = true){
                 int len = strlen(fname);
                 if (len > 8 && !strcmp(fname + len - 7, ".buffer")){
-                    this->LoadBinary(fname, silent); return;
+                    if( !this->LoadBinary(fname, silent) ){
+                        fprintf(stderr,"can not open file \"%s\"", fname);
+                        utils::Error("DMatrix::CacheLoad failed");
+                    }
+                    return;
                 }
                 char bname[1024];
                 sprintf(bname, "%s.buffer", fname);