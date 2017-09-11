@@ -58,7 +58,7 @@ class FeatMap {
   }
   /*! \brief return type of specific feature */
   const Type& type(size_t idx) const {
-    utils::Assert(idx < names_.size(), "utils::FMap::name feature index exceed bound");
+    utils::Assert(idx < names_.size(), "utils::FMap::type feature index exceed bound");
     return types_[idx];
   }
 