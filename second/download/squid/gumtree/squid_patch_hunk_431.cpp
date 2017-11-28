 #if ICAP_CLIENT
             case Log::Format::CLF_ICAP_SQUID:
                 Log::Format::SquidIcap(al, log->logfile);
                 break;
 #endif
 
+            case Log::Format::CLF_NONE:
+                return; // abort!
+
             default:
                 fatalf("Unknown log format %d\n", log->type);
                 break;
             }
 
             logfileLineEnd(log->logfile);
