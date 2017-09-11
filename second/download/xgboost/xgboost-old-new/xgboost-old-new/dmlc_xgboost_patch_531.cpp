@@ -305,6 +305,27 @@ namespace xgboost{
                     FMatrixS::LoadBinary( fi, col_ptr_, col_data_ );
                 }
             }
+            /*!
+            * \brief load from text file 
+            * \param fi input file pointer
+            */            
+            inline void LoadText( FILE *fi ){
+                this->Clear();
+                int ninst;
+                while( fscanf( fi, "%d", &ninst ) == 1 ){
+                    std::vector<booster::bst_uint>  findex;
+                    std::vector<booster::bst_float> fvalue;
+                    while( -- ninst ){
+                        unsigned index; float value;
+                        utils::Assert( fscanf( fi, "%u:%f", &index, &value ) == 2 );
+                        findex.push_back( index ); fvalue.push_back( value );
+                    }
+                    this->AddRow( findex, fvalue );                    
+                }
+                // initialize column support as well
+                this->InitData();
+                fclose(fi);
+            }
         private:
             /*!
              * \brief save data to binary stream 