               case VAR_FTP_ENTRY_PATH:
                 if((CURLE_OK ==
                     curl_easy_getinfo(curl, CURLINFO_FTP_ENTRY_PATH, &stringp))
                    && stringp)
                   fputs(stringp, stream);
                 break;
+              case VAR_REDIRECT_URL:
+                if((CURLE_OK ==
+                    curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &stringp))
+                   && stringp)
+                  fputs(stringp, stream);
+                break;
               default:
                 break;
               }
               break;
             }
           }
