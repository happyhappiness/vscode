             /* default templates are in English */
             /* language is known unless error_directory override used */
             if (!Config.errorDirectory)
                 rep->header.putStr(HDR_CONTENT_LANGUAGE, "en");
         }
 
-        httpBodySet(&rep->body, content);
+        rep->body.setMb(content);
         /* do not memBufClean() or delete the content, it was absorbed by httpBody */
     }
 
     return rep;
 }
 
