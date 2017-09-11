@@ -112,7 +112,9 @@ namespace xgboost{
                     unsigned ngptr;
                     if( fs.Read(&ngptr, sizeof(unsigned) ) != 0 ){
                         info.group_ptr.resize( ngptr );
-                        utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                        if( ngptr != 0 ){
+                            utils::Assert( fs.Read(&info.group_ptr[0], sizeof(unsigned) * ngptr) != 0, "Load group file");
+                        }
                     }
                 }
                 fs.Close();
@@ -143,7 +145,9 @@ namespace xgboost{
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