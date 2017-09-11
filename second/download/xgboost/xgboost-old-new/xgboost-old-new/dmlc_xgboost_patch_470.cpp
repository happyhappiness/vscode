@@ -228,8 +228,8 @@ namespace xgboost{
              * \return the row id added line
              */
             inline size_t AddRow(const std::vector<bst_uint> &findex,
-                const std::vector<bst_float> &fvalue,
-                unsigned fstart = 0, unsigned fend = UINT_MAX){
+                                 const std::vector<bst_float> &fvalue,
+                                 unsigned fstart = 0, unsigned fend = UINT_MAX){
                 utils::Assert(findex.size() == fvalue.size());
                 unsigned cnt = 0;
                 for (size_t i = 0; i < findex.size(); i++){
@@ -378,7 +378,7 @@ namespace xgboost{
                     utils::Assert(fi.Read(&data[0], data.size() * sizeof(REntry)), "Load FMatrixS");
                 }
             }
-        protected:
+        public:
             /*! \brief row pointer of CSR sparse storage */
             std::vector<size_t>  row_ptr_;
             /*! \brief data in the row */