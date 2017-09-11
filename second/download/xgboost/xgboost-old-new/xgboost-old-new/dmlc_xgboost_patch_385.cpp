@@ -129,7 +129,7 @@ namespace xgboost{
             inline void LoadModel(const char *fname){
                 utils::FileStream fi(utils::FopenCheck(fname, "rb"));
                 this->LoadModel(fi);
-                fi.Close();                
+                fi.Close();          
             }
             /*!
              * \brief load model from stream
@@ -138,6 +138,14 @@ namespace xgboost{
             inline void LoadModel(utils::IStream &fi){
                 base_gbm.LoadModel(fi);
                 utils::Assert(fi.Read(&mparam, sizeof(ModelParam)) != 0);
+                // save name obj
+                size_t len;                
+                if( fi.Read(&len, sizeof(len)) != 0 ){
+                    name_obj_.resize( len );
+                    if( len != 0 ){
+                        utils::Assert( fi.Read(&name_obj_[0], len*sizeof(char)) != 0 );
+                    }
+                }
             }
             /*!
              * \brief DumpModel
@@ -163,6 +171,10 @@ namespace xgboost{
             inline void SaveModel(utils::IStream &fo) const{
                 base_gbm.SaveModel(fo);
                 fo.Write(&mparam, sizeof(ModelParam));
+                // save name obj
+                size_t len = name_obj_.length();
+                fo.Write(&len, sizeof(len));
+                fo.Write(&name_obj_[0], len*sizeof(char));
             }
             /*!
              * \brief save model into file