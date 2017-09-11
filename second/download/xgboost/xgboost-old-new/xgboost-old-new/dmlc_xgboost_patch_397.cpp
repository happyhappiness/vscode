@@ -129,7 +129,9 @@ namespace xgboost{
                     if( fs.Read(&nwt, sizeof(unsigned) ) != 0 ){
                         utils::Assert( nwt == 0 || nwt == data.NumRow(), "invalid weight" );
                         info.weights.resize( nwt );
-                        utils::Assert( fs.Read(&info.weights[0], sizeof(unsigned) * nwt) != 0, "Load weight file");
+                        if( nwt != 0 ){
+                            utils::Assert( fs.Read(&info.weights[0], sizeof(unsigned) * nwt) != 0, "Load weight file");
+                        }
                     }
                 }
                 fs.Close();