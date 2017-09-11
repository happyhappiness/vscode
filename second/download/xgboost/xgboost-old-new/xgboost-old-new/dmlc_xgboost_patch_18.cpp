@@ -37,6 +37,13 @@ typedef void *BoosterHandle;
 XGB_DLL const char *XGBGetLastError();
 
 /*!
+ * \brief Entry point of CLI program.
+ * \param argc The number of arguments.
+ * \param argv The command line arguments.
+ */
+XGB_DLL int XGBoostCLIMain(int argc, char* argv[])
+
+/*!
  * \brief load a data matrix
  * \param fname the name of the file
  * \param silent whether print messages during loading