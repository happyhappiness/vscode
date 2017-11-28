                     mb2.clean();
                 }
 
                 first = 0;
             }
             break;
-        case _external_acl_format::EXT_ACL_PERCENT:
+        case Format::LFT_PERCENT:
             str = "%";
             break;
-        case _external_acl_format::EXT_ACL_UNKNOWN:
 
-        case _external_acl_format::EXT_ACL_END:
-            fatal("unknown external_acl format error");
+        default:
+            // TODO: replace this function with Format::assemble()
+            // For now die on unsupported logformat codes.
+            fatalf("ERROR: unknown external_acl_type format %u", (uint8_t)format->type);
             break;
         }
 
         if (str)
             if (!*str)
                 str = NULL;
