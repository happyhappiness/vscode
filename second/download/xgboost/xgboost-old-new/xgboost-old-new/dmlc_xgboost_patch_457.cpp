@@ -136,25 +136,24 @@ class DataLoader: public DMatrix{
             }
             ngleft -= 1; ngacc += 1;
 
+            int pass = 1;
             if( fwlist != NULL ){
-                int pass;
                 utils::Assert( fscanf( fwlist, "%u", &pass ) ==1 );
-                if( pass == 0 ){
-                    vskip( fheader ); ngacc -= 1;
-                }
             }
-
-            const int nfeat = readnum( fheader );
-            std::vector<unsigned> findex;
-            std::vector<float> fvalue;
-            // pairs 
-            this->Load( findex, fvalue, fheader );
-            utils::Assert( findex.size() == (unsigned)nfeat );
-            if( rescale != 0 ) this->DoRescale( fvalue );
-            // push back data :)
-            this->info.labels.push_back( label );
-            this->data.AddRow( findex, fvalue );
-
+            if( pass == 0 ){
+                vskip( fheader ); ngacc -= 1;
+            }else{            
+                const int nfeat = readnum( fheader );
+                std::vector<unsigned> findex;
+                std::vector<float> fvalue;
+                // pairs 
+                this->Load( findex, fvalue, fheader );
+                utils::Assert( findex.size() == (unsigned)nfeat );
+                if( rescale != 0 ) this->DoRescale( fvalue );
+                // push back data :)
+                this->info.labels.push_back( label );
+                this->data.AddRow( findex, fvalue );
+            }             
             if( ngleft == 0 && fgroup != NULL && ngacc != 0 ){
                 info.group_ptr.push_back( info.group_ptr.back() + ngacc );
                 utils::Assert( info.group_ptr.back() == data.NumRow(), "group size must match num rows" );