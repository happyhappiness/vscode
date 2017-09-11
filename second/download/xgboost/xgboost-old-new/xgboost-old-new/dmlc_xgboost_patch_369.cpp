@@ -199,6 +199,10 @@ class FMatrixS : public FMatrixInterface<FMatrixS>{
     utils::Check(this->HaveColAccess(), "NumCol:need column access");
     return col_ptr_.size() - 1;
   }
+  /*! \brief get number of buffered rows */  
+  inline size_t NumBufferedRow(void) const {
+    return num_buffered_row_;
+  }
   /*! \brief get col sorted iterator */
   inline ColIter GetSortedCol(size_t cidx) const {
     utils::Assert(cidx < this->NumCol(), "col id exceed bound");