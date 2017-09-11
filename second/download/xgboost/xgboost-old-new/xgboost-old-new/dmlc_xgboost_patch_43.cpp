@@ -1,3 +1,4 @@
+// Copyright by Contributors
 // implementations in ctypes
 #define _CRT_SECURE_NO_WARNINGS
 #define _CRT_SECURE_NO_DEPRECATE
@@ -28,7 +29,7 @@ struct FHelper<op::BitOR, DType> {
             void (*prepare_fun)(void *arg),
             void *prepare_arg) {
     utils::Error("DataType does not support bitwise or operation");
-  }  
+  }
 };
 template<typename OP>
 inline void Allreduce_(void *sendrecvbuf_,
@@ -60,12 +61,12 @@ inline void Allreduce_(void *sendrecvbuf_,
       return;
     case kLong:
       rabit::Allreduce<OP>
-          (static_cast<long*>(sendrecvbuf_),
+          (static_cast<long*>(sendrecvbuf_),  // NOLINT(*)
            count, prepare_fun, prepare_arg);
       return;
     case kULong:
       rabit::Allreduce<OP>
-          (static_cast<unsigned long*>(sendrecvbuf_),
+          (static_cast<unsigned long*>(sendrecvbuf_),  // NOLINT(*)
            count, prepare_fun, prepare_arg);
       return;
     case kFloat:
@@ -135,7 +136,7 @@ struct ReadWrapper : public Serializable {
   }
   virtual void Save(Stream *fo) const {
     utils::Error("not implemented");
-  }  
+  }
 };
 struct WriteWrapper : public Serializable {
   const char *data;
@@ -179,7 +180,7 @@ extern "C" {
     if (s.length() > max_len) {
       s.resize(max_len - 1);
     }
-    strcpy(out_name, s.c_str());
+    strcpy(out_name, s.c_str()); // NOLINT(*)
     *out_len = static_cast<rbt_ulong>(s.length());
   }
   void RabitBroadcast(void *sendrecv_data,
@@ -218,7 +219,7 @@ extern "C" {
       *out_local_model = BeginPtr(local_buffer);
       *out_local_len = static_cast<rbt_ulong>(local_buffer.length());
     }
-    return version;    
+    return version;
   }
   void RabitCheckPoint(const char *global_model,
                        rbt_ulong global_len,