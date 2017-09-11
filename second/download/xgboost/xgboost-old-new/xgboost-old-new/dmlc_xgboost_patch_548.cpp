@@ -11,6 +11,7 @@
 #include <climits>
 #include "../utils/xgboost_utils.h"
 #include "../utils/xgboost_stream.h"
+#include "../utils/xgboost_matrix_csr.h"
 
 namespace xgboost{
     namespace booster{
@@ -67,10 +68,6 @@ namespace xgboost{
             };
         public:
             /*! 
-             * \brief prepare sorted columns so that GetSortedCol can be called
-             */
-            inline void MakeSortedCol( void );
-            /*! 
              * \brief get number of rows 
              * \return number of rows
              */
@@ -114,39 +111,46 @@ namespace xgboost{
                 bst_uint  findex;
                 /*! \brief feature value */
                 bst_float fvalue;
-            };
-            /*! \brief one entry in a row */
-            struct CEntry{
-                /*! \brief row index */
-                bst_uint  rindex;
-                /*! \brief feature value */
-                bst_float fvalue;
+                /*! \brief constructor */
+                REntry( void ){}
+                /*! \brief constructor */
+                REntry( bst_uint findex, bst_float fvalue ) : findex(findex), fvalue(fvalue){}
+                inline static bool cmp_fvalue( const REntry &a, const REntry &b ){
+                    return a.fvalue < b.fvalue;
+                }
             };
             /*! \brief one row of sparse feature matrix */
             struct Line{
                 /*! \brief array of feature index */
                 const REntry *data_;
                 /*! \brief size of the data */
                 bst_uint len;
+                /*! \brief get k-th element */
                 inline const REntry& operator[]( unsigned i ) const{
                     return data_[i];
                 }  
             };
-        public:
+            /*! \brief row iterator */
             struct RowIter{
-                const REntry *dptr, *end;                
+                const REntry *dptr_, *end_;
                 inline bool Next( void ){
-                    if( dptr == end ) return false;
+                    if( dptr_ == end_ ) return false;
                     else{
-                       ++ dptr; return true;
+                       ++ dptr_; return true;
                     }
                 }
                 inline bst_uint  findex( void ) const{
-                    return dptr->findex;
+                    return dptr_->findex;
                 }
                 inline bst_float fvalue( void ) const{
-                    return dptr->fvalue;
-                }                
+                    return dptr_->fvalue;
+                }
+            };
+            /*! \brief column iterator */
+            struct ColIter: public RowIter{
+                inline bst_uint  rindex( void ) const{
+                    return this->findex();
+                }
             };
         public:
             /*! \brief constructor */
@@ -167,6 +171,8 @@ namespace xgboost{
                 row_ptr_.clear();
                 row_ptr_.push_back( 0 );
                 row_data_.clear();
+                col_ptr_.clear();
+                col_data_.clear();
             }
             /*! \brief get sparse part of current row */
             inline Line operator[]( size_t sidx ) const{
@@ -175,14 +181,6 @@ namespace xgboost{
                 sp.len = static_cast<bst_uint>( row_ptr_[ sidx + 1 ] - row_ptr_[ sidx ] );
                 sp.data_ = &row_data_[ row_ptr_[ sidx ] ];
                 return sp;
-            }            
-            /*!  \brief get row iterator*/
-            inline RowIter GetRow( size_t ridx ) const{
-                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
-                RowIter it; 
-                it.dptr = &row_data_[ row_ptr_[ridx] ] - 1;
-                it.dptr = &row_data_[ row_ptr_[ridx+1] ] - 1;
-                return it;
             }
             /*! 
              * \brief add a row to the matrix, with data stored in STL container
@@ -199,50 +197,135 @@ namespace xgboost{
                 unsigned cnt = 0;
                 for( size_t i = 0; i < findex.size(); i ++ ){
                     if( findex[i] < fstart || findex[i] >= fend ) continue;
-                    REntry e; e.findex = findex[i]; e.fvalue = fvalue[i];
-                    row_data_.push_back( e );
+                    row_data_.push_back( REntry( findex[i], fvalue[i] ) );
                     cnt ++;
                 }
                 row_ptr_.push_back( row_ptr_.back() + cnt );
                 return row_ptr_.size() - 2;
             }
+            /*!  \brief get row iterator*/
+            inline RowIter GetRow( size_t ridx ) const{
+                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
+                RowIter it; 
+                it.dptr_ = &row_data_[ row_ptr_[ridx] ] - 1;
+                it.end_  = &row_data_[ row_ptr_[ridx+1] ] - 1;
+                return it;
+            }
         public:
+            /*! \return whether column access is enabled */
+            inline bool HaveColAccess( void ) const{
+                return col_ptr_.size() != 0 && col_data_.size() == row_data_.size();
+            }
+            /*!  \brief get number of colmuns */
+            inline size_t NumCol( void ) const{
+                utils::Assert( this->HaveColAccess() );
+                return col_ptr_.size() - 1;
+            }
+            /*!  \brief get col iterator*/
+            inline ColIter GetSortedCol( size_t cidx ) const{
+                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
+                ColIter it; 
+                it.dptr_ = &col_data_[ col_ptr_[cidx] ] - 1;
+                it.end_  = &col_data_[ col_ptr_[cidx+1] ] - 1;
+                return it;
+            }
+            /*!
+             * \brief intialize the data so that we have both column and row major
+             *        access, call this whenever we need column access
+             */
+            inline void InitData( void ){
+                utils::SparseCSRMBuilder<REntry> builder( col_ptr_, col_data_ );
+                builder.InitBudget( 0 );
+                for( size_t i = 0; i < this->NumRow(); i ++ ){
+                    for( RowIter it = this->GetRow(i); it.Next(); ){
+                        builder.AddBudget( it.findex() );
+                    }
+                }
+                builder.InitStorage();
+                for( size_t i = 0; i < this->NumRow(); i ++ ){
+                    for( RowIter it = this->GetRow(i); it.Next(); ){
+                        builder.PushElem( it.findex(), REntry( (bst_uint)i, it.fvalue() ) );
+                    }
+                }
+                // sort columns
+                unsigned ncol = static_cast<unsigned>( this->NumCol() );
+                for( unsigned i = 0; i < ncol; i ++ ){
+                    std::sort( &col_data_[ col_ptr_[ i ] ], &col_data_[ col_ptr_[ i+1 ] ], REntry::cmp_fvalue );
+                }
+            }
             /*!
              * \brief save data to binary stream 
-             *        note: since we have size_t in row_ptr, 
+             *        note: since we have size_t in ptr, 
              *              the function is not consistent between 64bit and 32bit machine
              * \param fo output stream
              */
-			inline void SaveBinary(utils::IStream &fo ) const{
-                size_t nrow = this->NumRow();
-                fo.Write( &nrow, sizeof(size_t) );
-                fo.Write( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) );
-                if( row_data_.size() != 0 ){
-                    fo.Write( &row_data_[0] , row_data_.size() * sizeof(REntry) );
+            inline void SaveBinary( utils::IStream &fo ) const{
+                FMatrixS::SaveBinary( fo, row_ptr_, row_data_ );
+                int col_access = this->HaveColAccess() ? 1 : 0;
+                fo.Write( &col_access, sizeof(int) );
+                if( col_access != 0 ){
+                    FMatrixS::SaveBinary( fo, col_ptr_, col_data_ );
                 }
             }
             /*!
              * \brief load data from binary stream 
-             *        note: since we have size_t in row_ptr, 
-             *              the function is not consistent between 64bit and 32bit machine
-             * \param fi output stream
+             *        note: since we have size_t in ptr, 
+             *              the function is not consistent between 64bit and 32bit machin
+             * \param fi input stream
              */
             inline void LoadBinary( utils::IStream &fi ){
+                FMatrixS::LoadBinary( fi, row_ptr_, row_data_ );
+                int col_access;                
+                fi.Read( &col_access, sizeof(int) );
+                if( col_access != 0 ){
+                    FMatrixS::LoadBinary( fi, col_ptr_, col_data_ );
+                }
+            }
+        private:
+            /*!
+             * \brief save data to binary stream 
+             * \param fo output stream
+             * \param ptr pointer data
+             * \param data data content
+             */
+            inline static void SaveBinary( utils::IStream &fo, 
+                                           const std::vector<size_t> &ptr, 
+                                           const std::vector<REntry> &data ){
+                size_t nrow = ptr.size() - 1;
+                fo.Write( &nrow, sizeof(size_t) );
+                fo.Write( &ptr[0], ptr.size() * sizeof(size_t) );
+                if( data.size() != 0 ){
+                    fo.Write( &data[0] , data.size() * sizeof(REntry) );
+                }
+            }
+            /*!
+             * \brief load data from binary stream 
+             * \param fi input stream
+             * \param ptr pointer data
+             * \param data data content
+             */
+            inline static void LoadBinary( utils::IStream &fi,
+                                           std::vector<size_t> &ptr, 
+                                           std::vector<REntry> &data ){
                 size_t nrow;
                 utils::Assert( fi.Read( &nrow, sizeof(size_t) ) != 0, "Load FMatrixS" );
-                row_ptr_.resize( nrow + 1 );
-                utils::Assert( fi.Read( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) ), "Load FMatrixS" );
+                ptr.resize( nrow + 1 );
+                utils::Assert( fi.Read( &ptr[0], ptr.size() * sizeof(size_t) ), "Load FMatrixS" );
 
-                row_data_.resize( row_ptr_.back() ); 
-                if( row_data_.size() != 0 ){
-                    utils::Assert( fi.Read( &row_data_[0] , row_data_.size() * sizeof(REntry) ) , "Load FMatrixS" );
+                data.resize( ptr.back() ); 
+                if( data.size() != 0 ){
+                    utils::Assert( fi.Read( &data[0] , data.size() * sizeof(REntry) ) , "Load FMatrixS" );
                 }
             }
         private:
             /*! \brief row pointer of CSR sparse storage */
             std::vector<size_t>  row_ptr_;
             /*! \brief data in the row */
             std::vector<REntry>  row_data_;
+            /*! \brief column pointer of CSC format */
+            std::vector<size_t>  col_ptr_;
+            /*! \brief column datas */
+            std::vector<REntry>  col_data_;
         };        
     };
 };