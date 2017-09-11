@@ -49,7 +49,7 @@ class BoostLearnTask {
       fprintf(stderr, "start %s:%d\n", pname.c_str(), rabit::GetRank());
     }
     if (rabit::IsDistributed()) {
-      this->SetParam("data_split", "col");
+      this->SetParam("dsplit", "row");
     }
     if (rabit::GetRank() != 0) {
       this->SetParam("silent", "2");