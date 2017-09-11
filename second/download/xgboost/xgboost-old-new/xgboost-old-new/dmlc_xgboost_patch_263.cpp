@@ -11,6 +11,7 @@
 #include <ctime>
 #include <cmath>
 #include "../src/io/simple_dmatrix-inl.hpp"
+#include "../src/io/io.cpp"
 #include "../src/utils/utils.h"
 
 using namespace xgboost;
@@ -94,14 +95,14 @@ class DataLoader: public DMatrixSimple {
     for( size_t i = 0; i < vec.size(); i ++ ){
       if( !vec[i].is_dense ) { 
         for( int j = 0; j < vec[i].tmp_num; j ++ ){
-          utils::Assert( fscanf ( vec[i].fi, "%u:%f", &e.findex, &e.fvalue ) == 2, "Error when load feat" );  
-          vec[i].CheckBase( e.findex );
-          e.findex += vec[i].base;
+          utils::Assert( fscanf ( vec[i].fi, "%u:%f", &e.index, &e.fvalue ) == 2, "Error when load feat" );  
+          vec[i].CheckBase( e.index );
+          e.index += vec[i].base;
           feats.push_back(e);
         }
       }else{
         utils::Assert( fscanf ( vec[i].fi, "%f", &e.fvalue ) == 1, "load feat" );  
-        e.findex = vec[i].base;
+        e.index = vec[i].base;
         feats.push_back(e);
       }
     }
@@ -163,7 +164,7 @@ class DataLoader: public DMatrixSimple {
       }             
       if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
         info.group_ptr.push_back( info.group_ptr.back() + ngacc );
-        utils::Assert( info.group_ptr.back() == info.num_row, "group size must match num rows" );
+        utils::Assert( info.group_ptr.back() == info.num_row(), "group size must match num rows" );
         ngacc = 0;
       }
       // linelimit
@@ -173,7 +174,7 @@ class DataLoader: public DMatrixSimple {
     }
     if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
       info.group_ptr.push_back( info.group_ptr.back() + ngacc );
-      utils::Assert( info.group_ptr.back() == info.num_row, "group size must match num rows" );
+      utils::Assert( info.group_ptr.back() == info.num_row(), "group size must match num rows" );
     }
   }
   
@@ -236,7 +237,7 @@ int main( int argc, char *argv[] ){
   printf("num_features=%d\n", norm( loader.fheader ) ); 
   printf("start creating buffer...\n");
   loader.Load();
-  loader.SaveBinary( argv[2] );
+  io::SaveDataMatrix(loader, argv[2]);
   // close files
   fclose( loader.fp );
   if( loader.fwlist != NULL ) fclose( loader.fwlist );    