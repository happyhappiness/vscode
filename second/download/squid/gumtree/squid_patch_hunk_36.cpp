     FinalizeEach(AllServices(), "message adaptation services");
     FinalizeEach(AllGroups(), "message adaptation service groups");
     FinalizeEach(AllRules(), "message adaptation access rules");
 }
 
 void
+Adaptation::Config::ParseMetaHeader(ConfigParser &parser)
+{
+    String name, value;
+    const char *warnFor[] = {
+        "Methods",
+        "Service",
+        "ISTag",
+        "Encapsulated",
+        "Opt-body-type",
+        "Max-Connections",
+        "Options-TTL",
+        "Date",
+        "Service-ID",
+        "Allow",
+        "Preview",
+        "Transfer-Preview",
+        "Transfer-Ignore",
+        "Transfer-Complete",
+        NULL
+    };
+    ConfigParser::ParseString(&name);
+    ConfigParser::ParseQuotedString(&value);
+
+    // TODO: Find a way to move this check to ICAP
+    for (int i = 0; warnFor[i] != NULL; i++) {
+        if (name.caseCmp(warnFor[i]) == 0) {
+            fatalf("%s:%d: meta name \"%s\" is a reserved ICAP header name",
+                   cfg_filename, config_lineno, name.termedBuf());
+        }
+    }
+
+    MetaHeader::Pointer meta = addMetaHeader(name);
+    MetaHeader::Value::Pointer headValue = meta->addValue(value);
+    aclParseAclList(parser, &headValue->aclList);
+}
+
+void
+Adaptation::Config::DumpMetaHeader(StoreEntry *entry, const char *name)
+{
+    typedef MetaHeaders::iterator AMLI;
+    for (AMLI m = metaHeaders.begin(); m != metaHeaders.end(); ++m) {
+        typedef MetaHeader::Values::iterator VLI;
+        for (VLI v =(*m)->values.begin(); v != (*m)->values.end(); ++v ) {
+            storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s",
+                              name, SQUIDSTRINGPRINT((*m)->name), ConfigParser::QuoteString((*v)->value));
+            dump_acl_list(entry, (*v)->aclList);
+            storeAppendPrintf(entry, "\n");
+        }
+    }
+}
+
+void
+Adaptation::Config::FreeMetaHeader()
+{
+    metaHeaders.clean();
+}
+
+void
 Adaptation::Config::ParseServiceSet()
 {
     Adaptation::Config::ParseServiceGroup(new ServiceSet);
 }
 
 void
