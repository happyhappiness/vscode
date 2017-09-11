@@ -24,119 +24,187 @@ namespace xgboost{
         const bool bst_debug = false;    
     };
 };
+
+namespace xgboost{
+    namespace booster{
+        /**
+         * \brief This is a interface, defining the way to access features, 
+         *        by column or by row. This interface is used to make implementation
+         *        of booster does not depend on how feature is stored.
+         *
+         *        Why template instead of virtual class: for efficiency
+         *          feature matrix is going to be used by most inner loop of the algorithm
+         *
+         * \tparam Derived type of actual implementation 
+         * \sa FMatrixS: most of time FMatrixS is sufficient, refer to it if you find it confusing
+         */
+        template<typename Derived>
+        struct FMatrix{
+        public:
+            /*! \brief exmaple iterator over one row */            
+            struct RowIter{
+                /*! 
+                 * \brief move to next position 
+                 * \return whether there is element in next position
+                 */
+                inline bool Next( void );
+                /*! \return feature index in current position */
+                inline bst_uint  findex( void ) const;
+                /*! \return feature value in current position */
+                inline bst_float fvalue( void ) const;
+            };
+            /*! \brief example iterator over one column */
+            struct ColIter{
+                /*! 
+                 * \brief move to next position 
+                 * \return whether there is element in next position
+                 */
+                inline bool Next( void );
+                /*! \return row index of current position  */
+                inline bst_uint  rindex( void ) const;
+                /*! \return feature value in current position */
+                inline bst_float fvalue( void ) const;
+            };
+        public:
+            /*! 
+             * \brief prepare sorted columns so that GetSortedCol can be called
+             */
+            inline void MakeSortedCol( void );
+            /*! 
+             * \brief get number of rows 
+             * \return number of rows
+             */
+            inline size_t NumRow( void ) const;
+            /*! 
+             * \brief get number of columns
+             * \return number of columns
+             */
+            inline size_t NumCol( void ) const;
+            /*!
+             * \brief get row iterator
+             * \param ridx row index
+             * \return row iterator
+             */
+            inline RowIter GetRow( size_t ridx ) const;
+            /*!
+             * \brief get column iterator, the columns must be sorted by feature value
+             * \param ridx column index
+             * \return column iterator
+             */
+            inline ColIter GetSortedCol( size_t ridx ) const;
+
+            /*! \return the view of derived class */
+            inline const Derived& self( void ) const{
+                return *static_cast<const Derived*>(this);
+            }
+        };
+    };
+};
+
 namespace xgboost{
     namespace booster{
         /*! 
          * \brief feature matrix to store training instance, in sparse CSR format
-         */
-        class FMatrixS{
+         */        
+        class FMatrixS: public FMatrix<FMatrixS>{
         public:
+            /*! \brief one entry in a row */
+            struct REntry{
+                /*! \brief feature index */
+                bst_uint  findex;
+                /*! \brief feature value */
+                bst_float fvalue;
+            };
+            /*! \brief one entry in a row */
+            struct CEntry{
+                /*! \brief row index */
+                bst_uint  rindex;
+                /*! \brief feature value */
+                bst_float fvalue;
+            };
             /*! \brief one row of sparse feature matrix */
             struct Line{
                 /*! \brief array of feature index */
-                const bst_uint  *findex;
-                /*! \brief array of feature value */
-                const bst_float *fvalue;
+                const REntry *data_;
                 /*! \brief size of the data */
                 bst_uint len;
+                inline const REntry& operator[]( unsigned i ) const{
+                    return data_[i];
+                }  
             };
-            /*! 
-             * \brief remapped image of sparse matrix, 
-             *  allows use a subset of sparse matrix, by specifying a rowmap
-             */
-            struct Image{
-            public:
-                Image( const FMatrixS &smat ):smat(smat), row_map( tmp_rowmap ){                
-                }
-                Image( const FMatrixS &smat, const std::vector<unsigned> &row_map )
-                    :smat(smat), row_map(row_map){
+        public:
+            struct RowIter{
+                const REntry *dptr, *end;                
+                inline bool Next( void ){
+                    if( dptr == end ) return false;
+                    else{
+                       ++ dptr; return true;
+                    }
                 }
-                /*! \brief get sparse part of current row */
-                inline Line operator[]( size_t sidx ) const{
-                    if( row_map.size() == 0 ) return smat[ sidx ];
-                    else return smat[ row_map[ sidx ] ];
+                inline bst_uint  findex( void ) const{
+                    return dptr->findex;
                 }
-            private:
-                // used to set the simple case
-                std::vector<unsigned> tmp_rowmap;
-                const FMatrixS &smat;
-                const std::vector<unsigned> &row_map;
+                inline bst_float fvalue( void ) const{
+                    return dptr->fvalue;
+                }                
             };
         public:
-            // -----Note: unless needed for hacking, these fields should not be accessed directly -----
-            /*! \brief row pointer of CSR sparse storage */
-            std::vector<size_t>  row_ptr;
-            /*! \brief index of CSR format */
-            std::vector<bst_uint>   findex;
-            /*! \brief value of CSR format */
-            std::vector<bst_float>  fvalue;
-        public:
             /*! \brief constructor */
             FMatrixS( void ){ this->Clear(); }
-            /*! 
-             * \brief get number of rows 
-             * \return number of rows
-             */
+            /*!  \brief get number of rows */
             inline size_t NumRow( void ) const{
-                return row_ptr.size() - 1;
+                return row_ptr_.size() - 1;
             }
             /*! 
              * \brief get number of nonzero entries
              * \return number of nonzero entries
              */
             inline size_t NumEntry( void ) const{
-                return findex.size();
+                return row_data_.size();
             }
             /*! \brief clear the storage */
             inline void Clear( void ){
-                row_ptr.resize( 0 );
-                findex.resize( 0 );
-                fvalue.resize( 0 );
-                row_ptr.push_back( 0 );
+                row_ptr_.clear();
+                row_ptr_.push_back( 0 );
+                row_data_.clear();
             }
-            /*! 
-             * \brief add a row to the matrix, but only accept features from fstart to fend
-             *  \param feat sparse feature
-             *  \param fstart start bound of feature
-             *  \param fend   end bound range of feature
-             *  \return the row id of added line
-             */
-            inline size_t AddRow( const Line &feat, unsigned fstart = 0, unsigned fend = UINT_MAX ){
-                utils::Assert( feat.len >= 0, "sparse feature length can not be negative" );
-                unsigned cnt = 0;
-                for( unsigned i = 0; i < feat.len; i ++ ){
-                    if( feat.findex[i] < fstart || feat.findex[i] >= fend ) continue;
-                    findex.push_back( feat.findex[i] );
-                    fvalue.push_back( feat.fvalue[i] );
-                    cnt ++;
-                }
-                row_ptr.push_back( row_ptr.back() + cnt );
-                return row_ptr.size() - 2;
+            /*! \brief get sparse part of current row */
+            inline Line operator[]( size_t sidx ) const{
+                Line sp;
+                utils::Assert( !bst_debug || sidx < this->NumRow(), "row id exceed bound" );
+                sp.len = static_cast<bst_uint>( row_ptr_[ sidx + 1 ] - row_ptr_[ sidx ] );
+                sp.data_ = &row_data_[ row_ptr_[ sidx ] ];
+                return sp;
+            }            
+            /*!  \brief get row iterator*/
+            inline RowIter GetRow( size_t ridx ) const{
+                utils::Assert( !bst_debug || ridx < this->NumRow(), "row id exceed bound" );
+                RowIter it; 
+                it.dptr = &row_data_[ row_ptr_[ridx] ] - 1;
+                it.dptr = &row_data_[ row_ptr_[ridx+1] ] - 1;
+                return it;
             }
-
             /*! 
              * \brief add a row to the matrix, with data stored in STL container
              * \param findex feature index
              * \param fvalue feature value
+             *  \param fstart start bound of feature
+             *  \param fend   end bound range of feature
              * \return the row id added line
              */
             inline size_t AddRow( const std::vector<bst_uint> &findex, 
-                                  const std::vector<bst_float> &fvalue ){
-                FMatrixS::Line l;
+                                  const std::vector<bst_float> &fvalue,
+                                  unsigned fstart = 0, unsigned fend = UINT_MAX ){
                 utils::Assert( findex.size() == fvalue.size() );
-                l.findex = &findex[0];
-                l.fvalue = &fvalue[0];
-                l.len = static_cast<bst_uint>( findex.size() );
-                return this->AddRow( l );
-            }
-            /*! \brief get sparse part of current row */
-            inline Line operator[]( size_t sidx ) const{
-                Line sp;
-                utils::Assert( !bst_debug || sidx < this->NumRow(), "row id exceed bound" );
-                sp.len = static_cast<bst_uint>( row_ptr[ sidx + 1 ] - row_ptr[ sidx ] );
-                sp.findex = &findex[ row_ptr[ sidx ] ];
-                sp.fvalue = &fvalue[ row_ptr[ sidx ] ];
-                return sp;
+                unsigned cnt = 0;
+                for( size_t i = 0; i < findex.size(); i ++ ){
+                    if( findex[i] < fstart || findex[i] >= fend ) continue;
+                    REntry e; e.findex = findex[i]; e.fvalue = fvalue[i];
+                    row_data_.push_back( e );
+                    cnt ++;
+                }
+                row_ptr_.push_back( row_ptr_.back() + cnt );
+                return row_ptr_.size() - 2;
             }
         public:
             /*!
@@ -148,10 +216,9 @@ namespace xgboost{
 			inline void SaveBinary(utils::IStream &fo ) const{
                 size_t nrow = this->NumRow();
                 fo.Write( &nrow, sizeof(size_t) );
-                fo.Write( &row_ptr[0], row_ptr.size() * sizeof(size_t) );
-                if( findex.size() != 0 ){
-                    fo.Write( &findex[0] , findex.size() * sizeof(bst_uint) );
-                    fo.Write( &fvalue[0] , fvalue.size() * sizeof(bst_float) );
+                fo.Write( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) );
+                if( row_data_.size() != 0 ){
+                    fo.Write( &row_data_[0] , row_data_.size() * sizeof(REntry) );
                 }
             }
             /*!
@@ -163,17 +230,20 @@ namespace xgboost{
             inline void LoadBinary( utils::IStream &fi ){
                 size_t nrow;
                 utils::Assert( fi.Read( &nrow, sizeof(size_t) ) != 0, "Load FMatrixS" );
-                row_ptr.resize( nrow + 1 );
-                utils::Assert( fi.Read( &row_ptr[0], row_ptr.size() * sizeof(size_t) ), "Load FMatrixS" );
+                row_ptr_.resize( nrow + 1 );
+                utils::Assert( fi.Read( &row_ptr_[0], row_ptr_.size() * sizeof(size_t) ), "Load FMatrixS" );
 
-                findex.resize( row_ptr.back() ); fvalue.resize( row_ptr.back() );                
-                if( findex.size() != 0 ){
-                    utils::Assert( fi.Read( &findex[0] , findex.size() * sizeof(bst_uint) ) , "Load FMatrixS" );
-                    utils::Assert( fi.Read( &fvalue[0] , fvalue.size() * sizeof(bst_float) ), "Load FMatrixS" );
+                row_data_.resize( row_ptr_.back() ); 
+                if( row_data_.size() != 0 ){
+                    utils::Assert( fi.Read( &row_data_[0] , row_data_.size() * sizeof(REntry) ) , "Load FMatrixS" );
                 }
             }
-        };
-    };    
+        private:
+            /*! \brief row pointer of CSR sparse storage */
+            std::vector<size_t>  row_ptr_;
+            /*! \brief data in the row */
+            std::vector<REntry>  row_data_;
+        };        
+    };
 };
-
 #endif