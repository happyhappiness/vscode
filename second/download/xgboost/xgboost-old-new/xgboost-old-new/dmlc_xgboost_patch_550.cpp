@@ -43,13 +43,13 @@ namespace xgboost{
             }
         public:
             /*! 
-             * \brief step 1: initialize the number of rows in the data
-             * \nrows number of rows in the matrix 
+             * \brief step 1: initialize the number of rows in the data, not necessary exact
+             * \nrows number of rows in the matrix, can be smaller than expected
              */
-            inline void InitBudget( size_t nrows ){
+            inline void InitBudget( size_t nrows = 0 ){
                 if( !UseAcList ){
-                    rptr.resize( nrows + 1 );
-                    std::fill( rptr.begin(), rptr.end(), 0 );
+                    rptr.clear();
+                    rptr.resize( nrows + 1, 0 );
                 }else{
                     Assert( nrows + 1 == rptr.size(), "rptr must be initialized already" );
                     this->Cleanup();
@@ -61,6 +61,9 @@ namespace xgboost{
              * \param nelem  number of element budget add to this row
              */
             inline void AddBudget( size_t row_id, size_t nelem = 1 ){
+                if( rptr.size() < row_id + 2 ){
+                    rptr.resize( row_id + 2, 0 );
+                }
                 if( UseAcList ){
                     if( rptr[ row_id + 1 ] == 0 ) aclist.push_back( row_id );
                 }