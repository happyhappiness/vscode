                 m->in.type = SHORT;
                 break;
             case 'b':
                 m->in.type = BYTE;
                 break;
             default:
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv, APLOGNO(01522)
                         MODNAME ": indirect offset type %c invalid", *l);
                 break;
             }
             l++;
         }
         s = l;
