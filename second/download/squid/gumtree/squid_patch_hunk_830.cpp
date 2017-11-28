 };
 
 /// Globally available instance of Qos::Config
 extern Config TheConfig;
 
 /* legacy parser access wrappers */
-#define parse_QosConfig(X)	(X)->parseConfigLine()
+#define parse_QosConfig(X)  (X)->parseConfigLine()
 #define free_QosConfig(X)
 #define dump_QosConfig(e,n,X) do { \
-		char temp[256]; /* random number. change as needed. max config line length. */ \
-		(X).dumpConfigLine(temp,n); \
-	        storeAppendPrintf(e, "%s", temp); \
-	} while(0);
+        char temp[256]; /* random number. change as needed. max config line length. */ \
+        (X).dumpConfigLine(temp,n); \
+            storeAppendPrintf(e, "%s", temp); \
+    } while(0);
 
 } // namespace Qos
 
 } // namespace Ip
 
 #if _USE_INLINE_
