@@ -19,21 +19,36 @@ namespace utils {
  * \tparam RType type of rank
  */
 template<typename DType, typename RType=unsigned>
-class QuantileSketch {
+class WQuantileSketch {
  public:
   /*! \brief an entry in the sketch summary */
   struct Entry {
     /*! \brief minimum rank */
     RType rmin;
     /*! \brief maximum rank */
     RType rmax;
+    /*! \brief maximum weight */
+    RType wmin;
     /*! \brief the value of data */
     DType value;
     // constructor
     Entry(void) {}
     // constructor
-    Entry(RType rmin, RType rmax, DType value)
-        : rmin(rmin), rmax(rmax), value(value) {}
+    Entry(RType rmin, RType rmax, RType wmin, DType value)
+        : rmin(rmin), rmax(rmax), wmin(wmin), value(value) {}
+    /*! \brief debug function,  */
+    inline void CheckValid(void) const {
+      utils::Assert(rmin >= 0 && rmax >= 0 && wmin >= 0, "nonneg constraint");
+      utils::Assert(rmax >= rmin + wmin, "relation constraint");
+    }
+    /*! \return rmin estimation for v strictly bigger than value */
+    inline RType rmin_next(void) const {
+      return rmin + wmin;
+    }
+    /*! \return rmax estimation for v strictly smaller than value */
+    inline RType rmax_prev(void) const {
+      return rmax - wmin;
+    }
   };
   /*! 
    * \brief this is data structure presenting one summary
@@ -42,15 +57,34 @@ class QuantileSketch {
     /*! \brief data field */
     Entry *data;
     /*! \brief number of elements in the summary */
-    RType size;
-    /*! \brief the maximum error of the summary */
+    size_t size;
+    // constructor
+    Summary(void) : size(0) {
+    }
+    /*! 
+     * \brief the maximum error of the Summary
+     */
     inline RType MaxError(void) const {
-      RType res = 0;
+      RType res = data[0].rmax - data[0].rmin - data[0].wmin;
       for (RType i = 1; i < size; ++i) {
-        res = std::max(data[i].rmax - data[i-1].rmin, res);
+        res = std::max(data[i].rmax_prev() - data[i - 1].rmax_next(), res);
+        res = std::max(data[i].rmax - data[i].rmin - data[i].wmin, res);
       }
       return res;
     }
+    /*! 
+     * \brief debug function, validate whether the summary 
+     *  run consistency check to check if it is a valid summary
+     */
+    inline void CheckValid(void) const {
+      for (RType i = 0; i < size; ++i) {
+        data[i].CheckValid();
+        if (i != 0) {
+          utils::Assert(data[i].rmin >= data[i - 1].rmin + data[i - 1].wmin, "rmin range constraint");
+          utils::Assert(data[i].rmax >= data[i - 1].rmax + data[i].wmin, "rmax range constraint");
+        }
+      }
+    }
     /*! \return maximum rank in the summary */
     inline RType MaxRank(void) const {
       return data[size - 1].rmax;
@@ -59,84 +93,108 @@ class QuantileSketch {
     inline void Clear(void) {
       size = 0;
     }
-    /*! 
+    /*!
      * \brief copy content from src
      * \param src source sketch
      */
     inline void CopyFrom(const Summary &src) {
       size = src.size;
       std::memcpy(data, src.data, sizeof(Entry) * size);
     }
-    /*! 
+    /*!
      * \brief set current summary to be pruned summary of src
      *        assume data field is already allocated to be at least maxsize
      * \param src source summary
      * \param maxsize size we can afford in the pruned sketch
      */
     inline void SetPrune(const Summary &src, RType maxsize) {
+      if (src.size <= maxsize) {
+        this->CopyFrom(src); return;
+      }
       const RType max_rank = src.MaxRank();
-      this->size = maxsize;
+      const size_t n = maxsize - 1;
       data[0] = src.data[0];
-      RType n = maxsize - 1;
-      RType top = 1;
-      for (RType i = 1; i < n; ++i) {
-        RType k = (i * max_rank) / n;
-        while (k > src.data[top + 1].rmax) ++top;
-        // assert src.data[top].rmin <= k
-        // because k > src.data[top].rmax >= src.data[top].rmin
-        if ((k - src.data[top].rmin) < (src.data[top+1].rmax - k)) {
-          data[i] = src.data[top];
+      this->size = 1;
+      // lastidx is used to avoid duplicated records
+      size_t i = 0, lastidx = 0;
+      for (RType k = 1; k < n; ++k) {
+        RType d2 = (k * max_rank) / n * 2;
+        // find first i such that  d < (rmax[i+1] + rmin[i+1]) / 2 
+        while (i < src.size - 1 &&
+               d2 < src.data[i + 1].rmax + src.data[i + 1].rmin) ++i;
+        if (i == src.size - 1) break;
+        if (d2 < src.data[i].rmin_next() + src.data[i + 1].rmax_prev()) {
+          if (i != lastidx) {
+            data[size++] = src.data[i]; lastidx = i;
+          }
         } else {
-          data[i] = src.data[top + 1];
+          if (i + 1 != lastidx) {
+            data[size++] = src.data[i + 1]; lastidx = i + 1;
+          }
         }
       }
-      data[n] = src.data[src.size - 1];
+      if (lastidx != src.size - 1) {
+        data[size++] = src.data[src.size - 1];
+      }
     }
     inline void SetCombine(const Summary &sa,
                            const Summary &sb) {
       utils::Assert(sa.size > 0 && sb.size > 0, "invalid input for merge"); 
       const Entry *a = sa.data, *a_end = sa.data + sa.size;
       const Entry *b = sb.data, *b_end = sb.data + sb.size;
-      this->size = sa.size + sb.size;
+      // extended rmin value
       RType aprev_rmin = 0, bprev_rmin = 0;
       Entry *dst = this->data;
       while (a != a_end && b != b_end) {
-        if (a->value < b->value) {
+        // duplicated value entry
+        if (a->value == b->value) {
+          *dst = Entry(a->rmin + b->rmin,
+                       a->rmax + b->rmax,
+                       a->wmin + b->wmin, a->value);
+          aprev_rmin = a->rmin_next();
+          bprev_rmin = b->rmin_next();
+          ++dst; ++a; ++b;
+        } else if (a->value < b->value) {
           *dst = Entry(bprev_rmin + a->rmin,
-                       a->rmax + b->rmax - 1, a->value);
-          aprev_rmin = a->rmin;
+                       a->rmax + b->rmax_prev(),
+                       a->wmin, a->value);
+          aprev_rmin = a->rmin_next();
           ++dst; ++a;
         } else {
-          *dst = Entry(aprev_rmin + b->rmin, 
-                       b->rmax + a->rmax - 1, b->value);
-          bprev_rmin = b->rmin;
+          *dst = Entry(aprev_rmin + b->rmin,
+                       b->rmax + a->rmax_prev(),
+                       b->wmin, b->value);
+          bprev_rmin = b->rmin_next();
           ++dst; ++b;
         }
       }
       if (a != a_end) {
-        RType bprev_rmax = (b_end - 1)->rmax;
+        RType brmax = (b_end - 1)->rmax;
         do {
-          *dst = Entry(bprev_rmin + a->rmin, bprev_rmax + a->rmax, a->value);
+          *dst = Entry(bprev_rmin + a->rmin, brmax + a->rmax, a->wmin, a->value);
           ++dst; ++a;
         } while (a != a_end);
       }
       if (b != b_end) {
-        RType aprev_rmax = (a_end - 1)->rmax;
+        RType armax = (a_end - 1)->rmax;
         do {
-          *dst = Entry(aprev_rmin + b->rmin, aprev_rmax + b->rmax, b->value);
+          *dst = Entry(aprev_rmin + b->rmin, armax + b->rmax, b->wmin, b->value);
           ++dst; ++b;
         } while (b != b_end);
       }
-      utils::Assert(dst == data + size, "bug in combine");
+      this->size = dst - data;
+      utils::Assert(size <= sa.size + sb.size, "bug in combine");
     }
   };
   // same as summary, but use STL to backup the space
   struct SummaryContainer : public Summary {
     std::vector<Entry> space;
     /*! \brief reserve space for summary */
     inline void Reserve(size_t size) {
-      space.resize(size);
-      this->data = BeginPtr(space);
+      if (size > space.size()) {
+        space.resize(size);
+        this->data = BeginPtr(space);
+      }
     }
     /*! 
      * \brief set the space to be merge of all Summary arrays
@@ -169,107 +227,144 @@ class QuantileSketch {
    * \param eps accuracy level of summary
    */
   inline void Init(RType maxn, double eps) {
-    eps  = eps * 0.5;
-    size_t L = 0;
+    nlevel = 0;
     size_t b = std::max(floor(log2(eps * maxn) / eps), 8.0);
-    // check for lower 
+    // check for small n case
     while (b < maxn) {
-      L = ceil(log2(maxn / b)) + 1;
-      if (L < eps * b) break;
+      nlevel = ceil(log2(maxn / b)) + 1;
+      if (nlevel < eps * b) break;
       ++b;
     }
-    L += 1;
-    inqueue.resize(b);
+    nlevel += 1;
     level_batch = (b + 1) / 2 + 1;
-    temp.Reserve(level_batch * 2);
-    data.resize(level_batch * L);
-    for (size_t l = 0; l < L; ++l) {
-      Summary s; s.size = 0;
-      s.data = BeginPtr(data) + l * level_batch;
-      level.push_back(s);
-    }
+    // lazy reserve the space, if there is only one value, no need to allocate space
+    inqueue.resize(1);
+    data.resize(0);
+    level.resize(0);
     qtail = 0;
   }
   /*! 
    * \brief add an element to a sketch 
    * \param x the elemented added to the sketch
    */
-  inline void Add(DType x) {
-    inqueue[qtail++] = x;
+  inline void Add(DType x, RType w = 1) {
     if (qtail == inqueue.size()) {
-      // start update sketch
-      std::sort(inqueue.begin(), inqueue.end());
-      for (size_t i = 0; i < qtail; ++i) {
-        temp.data[i] = Entry(i + 1, i + 1, inqueue[i]);
+      // jump from lazy one value to level_batch * 2
+      if (inqueue.size() == 1) {
+        inqueue.resize(level_batch * 2);
+      } else {
+        temp.Reserve(2 * level_batch);
+        this->Queue2Summary(&temp);
+        for (size_t l = 1; true; ++l) {
+          this->InitLevel(std::max(l + 1, nlevel));
+          // check if level l is empty
+          if (level[l].size == 0) {
+            level[l].SetPrune(temp, level_batch); break;            
+          } else {
+            // level 0 is actually temp space
+            level[0].SetPrune(temp, level_batch);
+            temp.SetCombine(level[0], level[l]);
+            if (temp.size > level_batch) {
+              // try next level
+              level[l].size = 0;
+            } else {
+              // if merged record is still smaller, no need to send to next level
+              level[l].CopyFrom(temp); break;
+            }
+          }
+        }
       }
-      temp.size = static_cast<RType>(qtail);
-      // clean up queue
-      qtail = 0;
+    }
+    if (qtail == 0 || inqueue[qtail - 1].value != x) {
+      inqueue[qtail++] = QEntry(x, w); 
+    } else {
+      inqueue[qtail - 1].weight += w;
+    }
+  } 
+  /*! \brief get the summary after finalize */
+  inline void GetSummary(SummaryContainer *out) {
+    if (level.size() != 0) {
+      out->Reserve(level_batch * 2);
+    }
+    this->Queue2Summary(out);
+    if (level.size() != 0) {
+      level[0].SetPrune(*out, level_batch);
       for (size_t l = 1; l < level.size(); ++l) {
-        // check if level l is empty
-        if (level[l].size == 0) {
-          level[l].SetPrune(temp, level_batch);
-          return;
+        if (level[l].size == 0) continue;
+        if (level[0].size == 0) {
+          level[0].CopyFrom(level[l]);
         } else {
-          // level 0 is actually temp space
-          level[0].SetPrune(temp, level_batch);
-          temp.SetCombine(level[0], level[l]);
-          level[l].size = 0;
+          out->SetCombine(level[0], level[l]);
+          level[0].SetPrune(*out, level_batch);
         }
       }
-      utils::Error("adding more element than allowed");
+      out->CopyFrom(level[0]);
     }
   }
-  /*! 
-   * \brief finalize the result after all data has been passed 
-   *        copy the final result to level 0
-   *        this can only be called once
-   */
-  inline void Finalize(void) {
+  
+ private:
+  // initialize level space to at least nlevel
+  inline void InitLevel(size_t nlevel) {
+    if (level.size() >= nlevel) return;
+    data.resize(level_batch * nlevel);
+    level.resize(nlevel, Summary());
+    for (size_t l = 0; l < level.size(); ++l) {
+      level[l].data = BeginPtr(data) + l * level_batch;
+    }
+  }
+  inline void Queue2Summary(SummaryContainer *temp) {
+    // reserve temp space
+    temp->Reserve(inqueue.size());
+    temp->size = 0;
     // start update sketch
     std::sort(inqueue.begin(), inqueue.begin() + qtail);
-    for (size_t i = 0; i < qtail; ++i) {
-      temp.data[i] = Entry(i + 1, i + 1, inqueue[i]);
-    }
-    temp.size = static_cast<RType>(qtail);
-    if (temp.size < level_batch) {
-      level[0].CopyFrom(temp);
-    } else {
-      level[0].SetPrune(temp, level_batch);
-    }
-    // start adding other things in
-    for (size_t l = 1; l < level.size(); ++l) {
-      if (level[l].size == 0) continue;
-      if (level[0].size == 0) {
-        level[0].CopyFrom(level[l]);
-      } else {
-        temp.SetCombine(level[0], level[l]);
-        level[0].SetPrune(temp, level_batch);        
+    RType wsum = 0;
+    // construct data with unique weights
+    for (size_t i = 0; i < qtail;) {
+      size_t j = 1;
+      RType w = inqueue[i].weight;
+      while (j < qtail && inqueue[j].value == inqueue[i].value) {
+        w += inqueue[j].weight; ++j;
       }
-      level[l].size = 0;
+      temp->data[temp->size++] = Entry(wsum, wsum + w, w, inqueue[i].value);
+      wsum += w; i = j;
     }
+    // clean up queue
+    qtail = 0;
   }
-  /*! \brief get the summary after finalize */
-  inline Summary GetSummary(void) const {
-    return level[0];
-  }  
-  
- private:  
+  // entry in the queue
+  struct QEntry {
+    // value of the instance
+    DType value;
+    // weight of instance
+    RType weight;
+    // default constructor
+    QEntry(void) {}
+    // constructor
+    QEntry(DType value, RType weight) 
+        : value(value), weight(weight) {}
+    // comparator on value
+    inline bool operator<(const QEntry &b) const {
+      return value < b.value;
+    }
+  };
   // the input queue
-  std::vector<DType> inqueue;
+  std::vector<QEntry> inqueue;
   // end of the queue
   size_t qtail;
+  // number of levels
+  size_t nlevel;
   // size of summary in each level
   size_t level_batch;
+  // the level of each summaries
+  std::vector<Summary> level;
   // content of the summary
   std::vector<Entry> data;
-  // different level of summary
-  std::vector<Summary> level;  
   // temporal summary, used for temp-merge
   SummaryContainer temp;  
 };
 
-/*! 
+/*!
  * \brief a helper class to compute streaming quantile
  * \tparam DType type of data content
  * \tparam RType type of rank