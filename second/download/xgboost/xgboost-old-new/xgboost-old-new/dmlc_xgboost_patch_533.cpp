@@ -341,7 +341,7 @@ namespace xgboost{
                     utils::Assert( fi.Read( &data[0] , data.size() * sizeof(REntry) ) , "Load FMatrixS" );
                 }
             }
-        private:
+        protected:
             /*! \brief row pointer of CSR sparse storage */
             std::vector<size_t>  row_ptr_;
             /*! \brief data in the row */