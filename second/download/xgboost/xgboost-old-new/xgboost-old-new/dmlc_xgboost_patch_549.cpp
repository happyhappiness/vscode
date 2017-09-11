@@ -65,11 +65,12 @@ namespace xgboost{
 
                 labels.push_back( label );
                 data.AddRow( findex, fvalue );
+                // initialize column support as well
+                data.InitData();
 
-                this->UpdateInfo();
                 if( !silent ){
                     printf("%ux%u matrix with %lu entries is loaded from %s\n", 
-                        (unsigned)labels.size(), num_feature, (unsigned long)data.NumEntry(), fname );
+                           (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname );
                 }
                 fclose(file);
             }
@@ -87,10 +88,12 @@ namespace xgboost{
                 labels.resize( data.NumRow() );
                 utils::Assert( fs.Read( &labels[0], sizeof(float) * data.NumRow() ) != 0, "DMatrix LoadBinary" );
                 fs.Close();
-                this->UpdateInfo();
+                // initialize column support as well
+                data.InitData();
+
                 if( !silent ){
                     printf("%ux%u matrix with %lu entries is loaded from %s\n", 
-                        (unsigned)labels.size(), num_feature, (unsigned long)data.NumEntry(), fname );
+                           (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname );
                 }
                 return true;
             }
@@ -100,13 +103,16 @@ namespace xgboost{
             * \param silent whether print information or not
             */
             inline void SaveBinary( const char* fname, bool silent = false ){
+                // initialize column support as well
+                data.InitData();
+
                 utils::FileStream fs( utils::FopenCheck( fname, "wb" ) );
                 data.SaveBinary( fs );
                 fs.Write( &labels[0], sizeof(float) * data.NumRow() );
                 fs.Close();
                 if( !silent ){
                     printf("%ux%u matrix with %lu entries is saved to %s\n", 
-                        (unsigned)labels.size(), num_feature, (unsigned long)data.NumEntry(), fname );
+                           (unsigned)data.NumRow(), (unsigned)data.NumCol(), (unsigned long)data.NumEntry(), fname );
                 }
             }
             /*! 