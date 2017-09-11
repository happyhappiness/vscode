@@ -677,7 +677,7 @@ AllreduceRobust::TryRecoverData(RecoverType role,
           if (req_in[i]) min_write = std::min(links[i].size_write, min_write);
         }
         utils::Assert(min_write <= links[pid].size_read, "boundary check");
-        ReturnType ret = links[pid].ReadToRingBuffer(min_write);
+        ReturnType ret = links[pid].ReadToRingBuffer(min_write, size);
         if (ret != kSuccess) {
           return ReportError(&links[pid], ret);
         }