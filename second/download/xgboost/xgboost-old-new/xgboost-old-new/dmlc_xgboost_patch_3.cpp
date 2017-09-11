@@ -23,9 +23,10 @@ XGB_EXTERN_C {
 #define XGB_DLL XGB_EXTERN_C
 #endif
 
-// manually define unsign long
+// manually define unsigned long
 typedef uint64_t bst_ulong;  // NOLINT(*)
 
+
 /*! \brief handle to DMatrix */
 typedef void *DMatrixHandle;
 /*! \brief handle to Booster */
@@ -86,11 +87,11 @@ XGB_EXTERN_C typedef int XGBCallbackDataIterNext(
  * \brief get string message of the last error
  *
  *  all function in this file will return 0 when success
- *  and -1 when an error occured,
+ *  and -1 when an error occurred,
  *  XGBGetLastError can be called to retrieve the error
  *
- *  this function is threadsafe and can be called by different thread
- * \return const char* error inforomation
+ *  this function is thread safe and can be called by different thread
+ * \return const char* error information
  */
 XGB_DLL const char *XGBGetLastError();
 
@@ -124,7 +125,7 @@ XGB_DLL int XGDMatrixCreateFromDataIter(
  * \param indptr pointer to row headers
  * \param indices findex
  * \param data fvalue
- * \param nindptr number of rows in the matix + 1
+ * \param nindptr number of rows in the matrix + 1
  * \param nelem number of nonzero elements in the matrix
  * \param num_col number of columns; when it's set to 0, then guess from data
  * \param out created dmatrix
@@ -143,7 +144,7 @@ XGB_DLL int XGDMatrixCreateFromCSREx(const size_t* indptr,
  * \param indptr pointer to row headers
  * \param indices findex
  * \param data fvalue
- * \param nindptr number of rows in the matix + 1
+ * \param nindptr number of rows in the matrix + 1
  * \param nelem number of nonzero elements in the matrix
  * \param out created dmatrix
  * \return 0 when success, -1 when failure happens
@@ -159,7 +160,7 @@ XGB_DLL int XGDMatrixCreateFromCSR(const bst_ulong *indptr,
  * \param col_ptr pointer to col headers
  * \param indices findex
  * \param data fvalue
- * \param nindptr number of rows in the matix + 1
+ * \param nindptr number of rows in the matrix + 1
  * \param nelem number of nonzero elements in the matrix
  * \param num_row number of rows; when it's set to 0, then guess from data
  * \param out created dmatrix
@@ -178,7 +179,7 @@ XGB_DLL int XGDMatrixCreateFromCSCEx(const size_t* col_ptr,
  * \param col_ptr pointer to col headers
  * \param indices findex
  * \param data fvalue
- * \param nindptr number of rows in the matix + 1
+ * \param nindptr number of rows in the matrix + 1
  * \param nelem number of nonzero elements in the matrix
  * \param out created dmatrix
  * \return 0 when success, -1 when failure happens
@@ -201,7 +202,7 @@ XGB_DLL int XGDMatrixCreateFromCSC(const bst_ulong *col_ptr,
 XGB_DLL int XGDMatrixCreateFromMat(const float *data,
                                    bst_ulong nrow,
                                    bst_ulong ncol,
-                                   float  missing,
+                                   float missing,
                                    DMatrixHandle *out);
 /*!
  * \brief create a new dmatrix from sliced content of existing matrix