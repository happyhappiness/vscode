     // accomodate callers unable to convert their ACL list context to string
     if (!label)
         label = "...";
 
     MemBuf ctxLine;
     ctxLine.init();
-    ctxLine.Printf("(%s %s line)", cfg_directive, label);
+    ctxLine.appendf("(%s %s line)", cfg_directive, label);
     ctxLine.terminate();
 
     Acl::AndNode *rule = new Acl::AndNode;
     rule->context(ctxLine.content(), config_input_line);
     rule->lineParse();
 
     MemBuf ctxTree;
     ctxTree.init();
-    ctxTree.Printf("%s %s", cfg_directive, label);
+    ctxTree.appendf("%s %s", cfg_directive, label);
     ctxTree.terminate();
 
     // We want a cbdata-protected Tree (despite giving it only one child node).
     Acl::Tree *tree = new Acl::Tree;
     tree->add(rule);
     tree->context(ctxTree.content(), config_input_line);
