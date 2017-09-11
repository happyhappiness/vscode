@@ -17,7 +17,9 @@ namespace xgboost{
         public:
             enum Type{
                 kIndicator  = 0,
-                kQuantitive = 1
+                kQuantitive = 1,
+                kInteger = 2,
+                kFloat = 3
             };
         public:
             /*! \brief load feature map from text format */
@@ -54,6 +56,8 @@ namespace xgboost{
             inline static Type GetType( const char *tname ){
                 if( !strcmp( "i", tname ) ) return kIndicator;        
                 if( !strcmp( "q", tname ) ) return kQuantitive;
+                if( !strcmp( "int", tname ) ) return kInteger;        
+                if( !strcmp( "float", tname ) ) return kFloat;        
                 utils::Error("unknown feature type, use i for indicator and q for quantity");
                 return kIndicator;
             }