@@ -86,6 +86,20 @@ namespace xgboost{
              * \return row iterator
              */
             inline RowIter GetRow( size_t ridx ) const;
+            /*! 
+             * \brief get number of column groups, this ise used together with GetRow( ridx, gid )
+             * \return number of column group
+             */
+            inline unsigned NumColGroup( void ) const{
+                return 1;
+            }
+            /*!
+             * \brief get row iterator, return iterator of specific column group
+             * \param ridx row index
+             * \param gid colmun group id
+             * \return row iterator, only iterates over features of specified column group
+             */
+            inline RowIter GetRow( size_t ridx, unsigned gid ) const;
 
             /*! \return whether column access is enabled */
             inline bool HaveColAccess( void ) const;
@@ -140,6 +154,8 @@ namespace xgboost{
             /*! \brief row iterator */
             struct RowIter{
                 const REntry *dptr_, *end_;
+                RowIter( const REntry* dptr, const REntry* end )
+                    :dptr_(dptr),end_(end){}
                 inline bool Next( void ){
                     if( dptr_ == end_ ) return false;
                     else{
@@ -155,12 +171,16 @@ namespace xgboost{
             };
             /*! \brief column iterator */
             struct ColIter: public RowIter{
+                ColIter( const REntry* dptr, const REntry* end )
+                    :RowIter( dptr, end ){}
                 inline bst_uint  rindex( void ) const{
                     return this->findex();
                 }
             };
             /*! \brief reverse column iterator */
             struct ColBackIter: public ColIter{
+                ColBackIter( const REntry* dptr, const REntry* end )
+                    :ColIter( dptr, end ){}
                 // shadows RowIter::Next
                 inline bool Next( void ){
                     if( dptr_ == end_ ) return false;
@@ -223,10 +243,12 @@ namespace xgboost{
             /*!  \brief get row iterator*/
             inline RowIter GetRow( size_t ridx ) const{
                 utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
-                RowIter it; 
-                it.dptr_ = &row_data_[ row_ptr_[ridx] ] - 1;
-                it.end_  = &row_data_[ row_ptr_[ridx+1] ] - 1;
-                return it;
+                return RowIter( &row_data_[ row_ptr_[ridx] ] - 1, &row_data_[ row_ptr_[ridx+1] ] - 1 );
+            }
+            /*!  \brief get row iterator*/
+            inline RowIter GetRow( size_t ridx, unsigned gid ) const{
+                utils::Assert( gid == 0, "FMatrixS only have 1 column group" );
+                return FMatrixS::GetRow( ridx );
             }
         public:
             /*! \return whether column access is enabled */
@@ -241,18 +263,12 @@ namespace xgboost{
             /*!  \brief get col iterator*/
             inline ColIter GetSortedCol( size_t cidx ) const{
                 utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
-                ColIter it; 
-                it.dptr_ = &col_data_[ col_ptr_[cidx] ] - 1;
-                it.end_  = &col_data_[ col_ptr_[cidx+1] ] - 1;
-                return it;
+                return ColIter( &col_data_[ col_ptr_[cidx] ] - 1, &col_data_[ col_ptr_[cidx+1] ] - 1 );
             }
             /*!  \brief get col iterator */
             inline ColBackIter GetReverseSortedCol( size_t cidx ) const{
                 utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
-                ColBackIter it; 
-                it.dptr_ = &col_data_[ col_ptr_[cidx+1] ];
-                it.end_  = &col_data_[ col_ptr_[cidx] ];
-                return it;
+                return ColBackIter( &col_data_[ col_ptr_[cidx+1] ], &col_data_[ col_ptr_[cidx] ] );
             }
             /*!
              * \brief intialize the data so that we have both column and row major