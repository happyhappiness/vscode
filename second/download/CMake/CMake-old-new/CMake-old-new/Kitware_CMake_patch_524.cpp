@@ -17,6 +17,7 @@
 #include KWSYS_HEADER(SystemInformation.hxx)
 #include KWSYS_HEADER(Process.h)
 #include KWSYS_HEADER(ios/iostream)
+#include KWSYS_HEADER(ios/sstream)
 #ifndef WIN32
   #include <sys/utsname.h> // int uname(struct utsname *buf);
 #endif
@@ -171,35 +172,35 @@ const char * SystemInformation::GetVendorID()
 }
 
 /** Return the type ID of the CPU */
-const char * SystemInformation::GetTypeID()
+kwsys_stl::string SystemInformation::GetTypeID()
 {
-  char * temp = new char[32];
-  sprintf(temp,"%d",this->ChipID.Type);
-  return temp;
+  kwsys_ios::ostringstream str;
+  str << this->ChipID.Type;
+  return str.str();
 }
 
 /** Return the family of the CPU present */
-const char * SystemInformation::GetFamilyID()
+kwsys_stl::string SystemInformation::GetFamilyID()
 {
-  char * temp = new char[32];
-  sprintf(temp,"%d",this->ChipID.Family);
-  return temp;
+  kwsys_ios::ostringstream str;
+  str << this->ChipID.Family;
+  return str.str();
 }
 
 // Return the model of CPU present */
-const char * SystemInformation::GetModelID()
+kwsys_stl::string SystemInformation::GetModelID()
 {
-  char * temp = new char[32];
-  sprintf(temp,"%d",this->ChipID.Model);
-  return temp;
+  kwsys_ios::ostringstream str;
+  str << this->ChipID.Model;
+  return str.str();
 }
 
 /** Return the stepping code of the CPU present. */
-const char * SystemInformation::GetSteppingCode()
-{
-  char * temp = new char[32];
-  sprintf(temp,"%d",this->ChipID.Revision);
-  return temp;
+kwsys_stl::string SystemInformation::GetSteppingCode()
+{ 
+  kwsys_ios::ostringstream str;
+  str << this->ChipID.Revision;
+  return str.str();
 }
 
 /** Return the stepping code of the CPU present. */
@@ -2649,7 +2650,8 @@ bool SystemInformation::QueryOSInformation()
       this->OSRelease = "Unknown";
       break;
   }
-
+  delete [] operatingSystem;
+  operatingSystem = 0;
 
   // Get the hostname
   WORD wVersionRequested;