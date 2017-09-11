@@ -66,6 +66,8 @@ namespace xgboost{
                 /*! \return feature value in current position */
                 inline bst_float fvalue( void ) const;
             };
+            /*! \brief backward iterator over column */
+            struct ColBackIter : public ColIter {};
         public:
             /*! 
              * \brief get number of rows 
@@ -83,17 +85,21 @@ namespace xgboost{
              * \return row iterator
              */
             inline RowIter GetRow( size_t ridx ) const;
+
+            /*! \return whether column access is enabled */
+            inline bool HaveColAccess( void ) const;
             /*!
              * \brief get column iterator, the columns must be sorted by feature value
              * \param ridx column index
              * \return column iterator
              */
             inline ColIter GetSortedCol( size_t ridx ) const;
-
-            /*! \return the view of derived class */
-            inline const Derived& self( void ) const{
-                return *static_cast<const Derived*>(this);
-            }
+            /*!
+             * \brief get column backward iterator, starts from biggest fvalue, and iterator back
+             * \param ridx column index
+             * \return reverse column iterator
+             */
+            inline ColBackIter GetReverseSortedCol( size_t ridx ) const;
         };
     };
 };
@@ -152,6 +158,16 @@ namespace xgboost{
                     return this->findex();
                 }
             };
+            /*! \brief reverse column iterator */
+            struct ColBackIter: public ColIter{
+                // shadows RowIter::Next
+                inline bool Next( void ){
+                    if( dptr_ == end_ ) return false;
+                    else{
+                       -- dptr_; return true;
+                    }
+                }
+            };
         public:
             /*! \brief constructor */
             FMatrixS( void ){ this->Clear(); }
@@ -229,6 +245,14 @@ namespace xgboost{
                 it.end_  = &col_data_[ col_ptr_[cidx+1] ] - 1;
                 return it;
             }
+            /*!  \brief get col iterator */
+            inline ColIter GetReverseSortedCol( size_t cidx ) const{
+                utils::Assert( !bst_debug || cidx < this->NumCol(), "col id exceed bound" );
+                ColIter it; 
+                it.dptr_ = &col_data_[ col_ptr_[cidx+1] ];
+                it.end_  = &col_data_[ col_ptr_[cidx] ];
+                return it;
+            }
             /*!
              * \brief intialize the data so that we have both column and row major
              *        access, call this whenever we need column access