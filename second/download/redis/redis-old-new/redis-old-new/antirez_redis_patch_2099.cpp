@@ -3513,6 +3513,7 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         len = 1;
         buf[0] = (val < 0) ? 255 : 254;
     } else {
+#if (DBL_MANT_DIG >= 52) && (LLONG_MAX == 0x7fffffffffffffffLL)
         /* Check if the float is in a safe range to be casted into a
          * long long. We are assuming that long long is 64 bit here.
          * Also we are assuming that there are no implementations around where
@@ -3527,6 +3528,7 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         if (val > min && val < max && val == ((double)((long long)val)))
             ll2string((char*)buf+1,sizeof(buf),(long long)val);
         else
+#endif
             snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
         buf[0] = strlen((char*)buf+1);
         len = buf[0]+1;