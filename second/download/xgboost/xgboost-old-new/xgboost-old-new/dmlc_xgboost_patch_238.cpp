@@ -224,6 +224,12 @@ struct WQSummary {
    */
   inline void SetCombine(const WQSummary &sa,
                          const WQSummary &sb) {
+    if (sa.size == 0) {
+      this->CopyFrom(sb); return;
+    }
+    if (sb.size == 0) {
+      this->CopyFrom(sa); return;
+    }
     utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
@@ -453,6 +459,12 @@ struct GKSummary {
   }
   inline void SetCombine(const GKSummary &sa,
                          const GKSummary &sb) {
+    if (sa.size == 0) {
+      this->CopyFrom(sb); return;
+    }
+    if (sb.size == 0) {
+      this->CopyFrom(sa); return;
+    }    
     utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
     const Entry *a = sa.data, *a_end = sa.data + sa.size;
     const Entry *b = sb.data, *b_end = sb.data + sb.size;
@@ -537,96 +549,41 @@ class QuantileSketchTemplate {
         this->SetMerge(begin[0], begin[1]);
       } else {
         // recursive merge
-        SummaryContainer lhs, rhs;        
+        SummaryContainer lhs, rhs;
         lhs.SetCombine(begin, begin + len / 2);
         rhs.SetCombine(begin + len / 2, end);
         this->Reserve(lhs.size + rhs.size);
         this->SetCombine(lhs, rhs);
       }
     }
-  };
-  /*!
-   * \brief represent an array of summary
-   *  each contains fixed maximum size summary
-   */
-  class SummaryArray {
-   public:
-    /*!
-     * \brief intialize the SummaryArray 
-     * \param num_summary number of summary in the array
-     * \param max_size maximum number of elements in each summary
-     */
-    inline void Init(unsigned num_summary, unsigned max_size) {
-      this->num_summary = num_summary;
-      this->max_size = max_size;
-      sizes.resize(num_summary);
-      data.resize(num_summary * max_size);
-    }
-    /*!
-     * \brief set i-th element of array to be the src summary,
-     *   the summary can be pruned if it does not fit into max_size
-     * \param the index in the array
-     * \param src the source summary
-     * \tparam the type if source summary
-     */
-    template<typename TSrc>
-    inline void Set(size_t i, const TSrc &src) {
-      Summary dst = (*this)[i];
-      dst.SetPrune(src, max_size);
-      this->sizes[i] = dst.size;
-    }
-    /*! 
-     * \brief get i-th summary of the array, only use this for read purpose
-     */
-    inline const Summary operator[](size_t i) const {
-      return Summary((Entry*)BeginPtr(data) + i * max_size, sizes[i]);
-    }
     /*!
      * \brief do elementwise combination of summary array
      *        this[i] = combine(this[i], src[i]) for each i
      * \param src the source summary
+     * \param max_nbyte, maximum number of byte allowed in here
      */
-    inline void Reduce(const SummaryArray &src) {
-      utils::Check(num_summary == src.num_summary &&
-                   max_size == src.max_size, "array shape mismatch in reduce");
+    inline void Reduce(const Summary &src, size_t max_nbyte) {
+      this->Reserve((max_nbyte - sizeof(this->size)) / sizeof(Entry));
       SummaryContainer temp;
-      temp.Reserve(max_size * 2);
-      for (unsigned i = 0; i < num_summary; ++i) {
-        temp.SetCombine((*this)[i], src[i]);
-        this->Set(i, temp);
-      }
+      temp.Reserve(this->size + src.size);
+      temp.SetCombine(*this, src);
+      this->SetPrune(temp, space.size());
     }
     /*! \brief return the number of bytes this data structure cost in serialization */
-    inline size_t MemSize(void) const {
-      return sizeof(num_summary) + sizeof(max_size) 
-          + data.size() * sizeof(Entry) + sizes.size() * sizeof(unsigned);
+    inline static size_t CalcMemCost(size_t nentry) {
+      return sizeof(size_t) + sizeof(Entry) * nentry;
     }
     /*! \brief save the data structure into stream */
     inline void Save(IStream &fo) const {
-      fo.Write(&num_summary, sizeof(num_summary));
-      fo.Write(&max_size, sizeof(max_size));
-      fo.Write(BeginPtr(sizes), sizes.size() * sizeof(unsigned));
-      fo.Write(BeginPtr(data), data.size() * sizeof(Entry));
+      fo.Write(&(this->size), sizeof(this->size));
+      fo.Write(data, this->size * sizeof(Entry));
     }
     /*! \brief load data structure from input stream */
     inline void Load(IStream &fi) {
-      utils::Check(fi.Read(&num_summary, sizeof(num_summary)) != 0, "invalid SummaryArray");
-      utils::Check(fi.Read(&max_size, sizeof(max_size)) != 0, "invalid SummaryArray");
-      sizes.resize(num_summary);
-      data.resize(num_summary * max_size);
-      utils::Check(fi.Read(BeginPtr(sizes), sizes.size() * sizeof(unsigned)) != 0, "invalid SummaryArray");
-      utils::Check(fi.Read(BeginPtr(data), data.size() * sizeof(Entry)) != 0, "invalid SummaryArray");
+      utils::Check(fi.Read(&this->size, sizeof(this->size)) != 0, "invalid SummaryArray 1");
+      this->Reserve(this->size);      
+      utils::Check(fi.Read(data, this->size * sizeof(Entry)) != 0, "invalid SummaryArray 2");
     }
-
-   private:
-    /*! \brief number of summaries in the group */
-    unsigned num_summary;
-    /*! \brief maximum size of each summary */
-    unsigned max_size;
-    /*! \brief the current size of each summary */
-    std::vector<unsigned> sizes;
-    /*! \brief the data content */
-    std::vector<Entry> data;
   };
   /*! 
    * \brief intialize the quantile sketch, given the performance specification