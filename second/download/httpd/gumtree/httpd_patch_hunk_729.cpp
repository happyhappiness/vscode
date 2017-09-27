                         ap_rputs("</td><td>I", r);
                         break;
                     default:
                         ap_rputs("</td><td>?", r);
                         break;
                     }
-                    
+
                     ap_rprintf(r,
                                "\n</td>"
 #ifdef HAVE_TIMES
                                "<td>%.2f</td>"
 #endif
                                "<td>%ld</td><td>%ld",
