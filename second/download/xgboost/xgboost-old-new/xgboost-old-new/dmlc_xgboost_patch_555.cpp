@@ -92,6 +92,13 @@ namespace xgboost{
              * \param fo output stream 
              */        
             virtual void PrintInfo( FILE *fo ){}
+            /*! 
+             * \brief dump model into text file
+             * \param fo output stream 
+             */        
+            virtual void DumpModel( FILE *fo ){
+                utils::Error( "not implemented" );                
+            }
         public:
             /*! \brief virtual destructor */
             virtual ~IBooster( void ){}