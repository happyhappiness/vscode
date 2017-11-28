     virtual int bytesWanted (int min, int max) const =0;
     virtual void bytesIn(int qty) = 0;
     /* only aggregate and vector need this today */
     virtual void delayRead(DeferredRead const &) {fatal("Not implemented");}
 };
 
-#endif
+#endif /* USE_DELAY_POOLS */
 #endif /* DELAYIDCOMPOSITE_H */
