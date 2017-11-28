                         break;
                     }
                     if (wcstrcmparray(pTmpBuf->grui0_name, Groups) == 0) {
                         result = 1;
                         break;
                     }
-                    pTmpBuf++;
-                    dwTotalCount++;
+                    ++pTmpBuf;
+                    ++dwTotalCount;
                 }
             }
         } else {
             result = 0;
             fprintf(stderr, "%s: ERROR: NetUserGetGroups() failed.'\n", program_name);
         }
