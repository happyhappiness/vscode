@@ -82,13 +82,13 @@ class DataLoader: public DMatrix{
     int rescale;
     int linelimit;
 public:
-    FILE *fp, *fwlist, *fgroup;
+    FILE *fp, *fwlist, *fgroup, *fweight;
     std::vector<Header> fheader;
     std::vector<FMatrixS::REntry> entry;
     DataLoader( void ){
         rescale = 0; 
         linelimit = -1;
-        fp = NULL; fwlist = NULL; fgroup = NULL;
+        fp = NULL; fwlist = NULL; fgroup = NULL; fweight = NULL;
     }
 private:
     inline void Load( std::vector<unsigned> &findex, std::vector<float> &fvalue, std::vector<Header> &vec ){
@@ -122,7 +122,7 @@ class DataLoader: public DMatrix{
     // basically we are loading all the data inside
     inline void Load( void ){
         this->data.Clear();
-        float label;
+        float label, weight = 0.0f;
 
         unsigned ngleft = 0, ngacc = 0;
         if( fgroup != NULL ){
@@ -132,8 +132,12 @@ class DataLoader: public DMatrix{
 
         while( fscanf( fp, "%f", &label ) == 1 ){            
             if( ngleft == 0 && fgroup != NULL ){
-                utils::Assert( fscanf( fgroup, "%u", &ngleft ) == 1 );                
+                utils::Assert( fscanf( fgroup, "%u", &ngleft ) == 1 );
             }
+            if( fweight != NULL ){
+                utils::Assert( fscanf( fweight, "%f", &weight ) == 1 );
+            }
+            
             ngleft -= 1; ngacc += 1;
 
             int pass = 1;
@@ -152,6 +156,10 @@ class DataLoader: public DMatrix{
                 if( rescale != 0 ) this->DoRescale( fvalue );
                 // push back data :)
                 this->info.labels.push_back( label );
+                // push back weight if any
+                if( fweight != NULL ){
+                    this->info.labels.push_back( weight );                    
+                }
                 this->data.AddRow( findex, fvalue );
             }             
             if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
@@ -201,6 +209,9 @@ int main( int argc, char *argv[] ){
         if( !strcmp( argv[i], "-fgroup") ){
             loader.fgroup = utils::FopenCheck( argv[ ++i ], "r" ); continue;
         }
+        if( !strcmp( argv[i], "-fweight") ){
+            loader.fweight = utils::FopenCheck( argv[ ++i ], "r" ); continue;
+        }
         if( !strcmp( argv[i], "-linelimit") ){
             loader.linelimit = atoi( argv[ ++i ] ); continue;
         }