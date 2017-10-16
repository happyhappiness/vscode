         unsigned int i;
         printf("Features: ");
         for(i = 0; i < sizeof(feats)/sizeof(feats[0]); i++) {
           if(curlinfo->features & feats[i].bitmask)
             printf("%s ", feats[i].name);
         }
+#ifdef USE_METALINK
+        printf("Metalink ");
+#endif
         puts(""); /* newline */
       }
     }
     return PARAM_HELP_REQUESTED;
     case 'w':
       /* get the output string */
