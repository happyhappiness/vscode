 StatHist::enumInit(unsigned int last_enum)
 {
     init(last_enum + 3, Math::Null, Math::Null, -1.0, (2.0 + last_enum));
 }
 
 void
-statHistEnumDumper(StoreEntry * sentry, int idx, double val, double size, int count)
+statHistEnumDumper(StoreEntry * sentry, int idx, double val, double, int count)
 {
     if (count)
         storeAppendPrintf(sentry, "%2d\t %5d\t %5d\n",
                           idx, (int) val, count);
 }
 
 void
-statHistIntDumper(StoreEntry * sentry, int idx, double val, double size, int count)
+statHistIntDumper(StoreEntry * sentry, int, double val, double, int count)
 {
     if (count)
         storeAppendPrintf(sentry, "%9d\t%9d\n", (int) val, count);
 }
 
