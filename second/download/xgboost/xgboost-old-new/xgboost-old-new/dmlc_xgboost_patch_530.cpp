@@ -48,6 +48,7 @@ namespace xgboost{
                  * \brief move to next position 
                  * \return whether there is element in next position
                  */
+
                 inline bool Next( void );
                 /*! \return feature index in current position */
                 inline bst_uint  findex( void ) const;
@@ -315,16 +316,15 @@ namespace xgboost{
                 while( fscanf( fi, "%d", &ninst ) == 1 ){
                     std::vector<booster::bst_uint>  findex;
                     std::vector<booster::bst_float> fvalue;
-                    while( -- ninst ){
+                    while(  ninst -- ){
                         unsigned index; float value;
-                        utils::Assert( fscanf( fi, "%u:%f", &index, &value ) == 2 );
+                        utils::Assert( fscanf( fi, "%u:%f", &index, &value ) == 2, "load Text" );
                         findex.push_back( index ); fvalue.push_back( value );
                     }
                     this->AddRow( findex, fvalue );                    
                 }
                 // initialize column support as well
                 this->InitData();
-                fclose(fi);
             }
         private:
             /*!