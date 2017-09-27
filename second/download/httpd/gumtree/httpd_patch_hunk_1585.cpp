                 ap_rputs("Ok", r);
             else
                 ap_rputs("-", r);
             ap_rvputs(r, "</td><td>", worker->s->route, NULL);
             ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
             ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
-            ap_rprintf(r, "<td>%d</td><td>", (int)(worker->s->elected));
+            ap_rprintf(r, "<td>%d</td>", worker->s->lbset);
+            ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", worker->s->elected);
             ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
             ap_rputs("</td><td>", r);
             ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
             ap_rputs("</td>\n", r);
 
             /* TODO: Add the rest of dynamic worker data */
