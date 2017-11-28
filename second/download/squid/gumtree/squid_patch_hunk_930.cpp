     // AsyncJob API
     virtual void start();
     virtual bool doneAll() const { return false; } /// not done until mustStop
 
     bool usedDynamicRules();
     void check();
-
-private:
-    CBDATA_CLASS2(AccessCheck);
 };
 
 } // namespace Adaptation
 
 #endif /* SQUID_ADAPTATION__ACCESS_CHECK_H */
 
