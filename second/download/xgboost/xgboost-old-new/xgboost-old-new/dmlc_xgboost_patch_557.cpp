@@ -89,16 +89,23 @@ namespace xgboost{
             * \param fi input stream
             */          
             inline void LoadModel( utils::IStream &fi ){
-                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
                 base_model.LoadModel( fi );
+                utils::Assert( fi.Read( &mparam, sizeof(ModelParam) ) != 0 );
+            }
+            /*! 
+             * \brief DumpModel
+             * \param fo text file 
+             */            
+            inline void DumpModel( FILE *fo ){
+                base_model.DumpModel( fo );
             }
             /*! 
             * \brief save model to stream
             * \param fo output stream
             */
             inline void SaveModel( utils::IStream &fo ) const{
-                fo.Write( &mparam, sizeof(ModelParam) );
                 base_model.SaveModel( fo );	
+                fo.Write( &mparam, sizeof(ModelParam) );
             } 
             /*! 
              * \brief update the model for one iteration