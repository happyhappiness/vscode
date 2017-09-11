@@ -124,6 +124,14 @@ namespace xgboost{
                         }
                     }
                 }
+                {// load in weight
+                    unsigned nwt;
+                    if( fs.Read(&nwt, sizeof(unsigned) ) != 0 ){
+                        utils::Assert( nwt == 0 || nwt == data.NumRow(), "invalid weight" );
+                        info.weights.resize( nwt );
+                        utils::Assert( fs.Read(&info.weights[0], sizeof(unsigned) * nwt) != 0, "Load weight file");
+                    }
+                }
                 fs.Close();
                 
                 if (!silent){
@@ -133,7 +141,6 @@ namespace xgboost{
                         printf("data contains %u groups\n", (unsigned)info.group_ptr.size()-1 );
                     }
                 }
-                this->TryLoadWeight(fname, silent);
                 return true;
             }
             /*!
@@ -153,7 +160,14 @@ namespace xgboost{
                     unsigned ngptr = static_cast<unsigned>( info.group_ptr.size() );
                     fs.Write(&ngptr, sizeof(unsigned) );
                     if( ngptr != 0 ){
-                        fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);                    
+                        fs.Write(&info.group_ptr[0], sizeof(unsigned) * ngptr);
+                    }
+                }                
+                {// write out weight
+                    unsigned nwt = static_cast<unsigned>( info.weights.size() );
+                    fs.Write( &nwt, sizeof(unsigned) );
+                    if( nwt != 0 ){
+                        fs.Write(&info.weights[0], sizeof(float) * nwt);
                     }
                 }
                 fs.Close();