@@ -882,7 +882,8 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
     }
 
   // Compute a regex to match link extensions.
-  std::string libext = this->CreateExtensionRegex(this->LinkExtensions);
+  std::string libext = this->CreateExtensionRegex(this->LinkExtensions,
+                                                  LinkUnknown);
 
   // Create regex to remove any library extension.
   std::string reg("(.*)");
@@ -916,7 +917,8 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
   if(!this->StaticLinkExtensions.empty())
     {
     std::string reg_static = reg;
-    reg_static += this->CreateExtensionRegex(this->StaticLinkExtensions);
+    reg_static += this->CreateExtensionRegex(this->StaticLinkExtensions,
+                                             LinkStatic);
 #ifdef CM_COMPUTE_LINK_INFO_DEBUG
   fprintf(stderr, "static regex [%s]\n", reg_static.c_str());
 #endif
@@ -928,7 +930,7 @@ void cmComputeLinkInformation::ComputeItemParserInfo()
     {
     std::string reg_shared = reg;
     this->SharedRegexString =
-      this->CreateExtensionRegex(this->SharedLinkExtensions);
+      this->CreateExtensionRegex(this->SharedLinkExtensions, LinkShared);
     reg_shared += this->SharedRegexString;
 #ifdef CM_COMPUTE_LINK_INFO_DEBUG
   fprintf(stderr, "shared regex [%s]\n", reg_shared.c_str());
@@ -966,7 +968,7 @@ void cmComputeLinkInformation::AddLinkExtension(const char* e, LinkType type)
 //----------------------------------------------------------------------------
 std::string
 cmComputeLinkInformation
-::CreateExtensionRegex(std::vector<std::string> const& exts)
+::CreateExtensionRegex(std::vector<std::string> const& exts, LinkType type)
 {
   // Build a list of extension choices.
   std::string libext = "(";
@@ -995,6 +997,10 @@ ::CreateExtensionRegex(std::vector<std::string> const& exts)
     {
     libext += "(\\.[0-9]+\\.[0-9]+)?";
     }
+  else if(type == LinkShared)
+    {
+    libext += "(\\.[0-9]+)?";
+    }
 
   libext += "$";
   return libext;