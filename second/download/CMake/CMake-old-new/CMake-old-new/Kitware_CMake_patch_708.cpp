@@ -245,7 +245,6 @@ bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix,
             sprintf(hex, "%%%02X", (int)c);
             ofile.append(hex);
             break;
-            break;
           default: 
             ofile.append(hex);
           }
@@ -353,7 +352,6 @@ bool cmCTestSubmit::TriggerUsingHTTP(const std::vector<std::string>& files,
             sprintf(hex, "%%%02X", (int)c);
             ofile.append(hex);
             break;
-            break;
           default: 
             ofile.append(hex);
           }