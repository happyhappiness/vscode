@@ -3513,7 +3513,18 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         len = 1;
         buf[0] = (val < 0) ? 255 : 254;
     } else {
-        if (val > LLONG_MAX && val < LLONG_MIN && val == ((long long)val))
+        /* Check if the float is in a safe range to be casted into a
+         * long long. We are assuming that long long is 64 bit here.
+         * Also we are assuming that there are no implementations around where
+         * double has precision < 52 bit.
+         *
+         * Under this assumptions we test if a double is inside an interval
+         * where casting to long long is safe. Then using two castings we
+         * make sure the decimal part is zero. If all this is true we use
+         * integer printing function that is much faster. */
+        double min = -4503599627370495;
+        double max = 4503599627370496;
+        if (val > min && val < max && val == ((double)((long long)val)))
             ll2string((char*)buf+1,sizeof(buf),(long long)val);
         else
             snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);