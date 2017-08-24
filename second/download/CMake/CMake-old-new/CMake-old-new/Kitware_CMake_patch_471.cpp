@@ -151,10 +151,6 @@ class SystemInformationImplementation
   void RunMemoryCheck();
 
 public:
-#define VENDOR_STRING_LENGTH    (12 + 1)
-#define CHIPNAME_STRING_LENGTH    (48 + 1)
-#define SERIALNUMBER_STRING_LENGTH  (29 + 1)
-
   typedef struct tagID
     {
     int Type;
@@ -163,9 +159,9 @@ class SystemInformationImplementation
     int Revision;
     int ExtendedFamily;
     int ExtendedModel;
-    char ProcessorName[CHIPNAME_STRING_LENGTH];
-    char Vendor[VENDOR_STRING_LENGTH];
-    char SerialNumber[SERIALNUMBER_STRING_LENGTH];
+    kwsys_stl::string ProcessorName;
+    kwsys_stl::string Vendor;
+    kwsys_stl::string SerialNumber;
     } ID;
 
   typedef struct tagCPUPowerManagement
@@ -530,7 +526,12 @@ SystemInformationImplementation::SystemInformationImplementation()
   this->CurrentPositionInFile = 0;
   this->ChipManufacturer = UnknownManufacturer;
   memset(&this->Features, 0, sizeof(CPUFeatures));
-  memset(&this->ChipID, 0, sizeof(ID));
+  this->ChipID.Type = 0;
+  this->ChipID.Family = 0;
+  this->ChipID.Model = 0;
+  this->ChipID.Revision = 0;
+  this->ChipID.ExtendedFamily = 0;
+  this->ChipID.ExtendedModel = 0;
   this->CPUSpeedInMHz = 0;
   this->NumberOfLogicalCPU = 0;
   this->NumberOfPhysicalCPU = 0;
@@ -623,7 +624,7 @@ void SystemInformationImplementation::RunMemoryCheck()
 /** Get the vendor string */
 const char * SystemInformationImplementation::GetVendorString()
 {
-  return this->ChipID.Vendor;
+  return this->ChipID.Vendor.c_str();
 }
 
 /** Get the OS Name */
@@ -726,14 +727,14 @@ kwsys_stl::string SystemInformationImplementation::GetSteppingCode()
 /** Return the stepping code of the CPU present. */
 const char * SystemInformationImplementation::GetExtendedProcessorName()
 {
-  return this->ChipID.ProcessorName;
+  return this->ChipID.ProcessorName.c_str();
 }
   
 /** Return the serial number of the processor 
  *  in hexadecimal: xxxx-xxxx-xxxx-xxxx-xxxx-xxxx. */
 const char * SystemInformationImplementation::GetProcessorSerialNumber()
 {
-  return this->ChipID.SerialNumber;
+  return this->ChipID.SerialNumber.c_str();
 }
 
 /** Return the logical processors per physical */
@@ -1022,21 +1023,21 @@ bool SystemInformationImplementation::RetrieveCPUFeatures()
 /** Find the manufacturer given the vendor id */
 void SystemInformationImplementation::FindManufacturer()
 {
-  if (strcmp (this->ChipID.Vendor, "GenuineIntel") == 0)       this->ChipManufacturer = Intel;        // Intel Corp.
-  else if (strcmp (this->ChipID.Vendor, "UMC UMC UMC ") == 0)  this->ChipManufacturer = UMC;          // United Microelectronics Corp.
-  else if (strcmp (this->ChipID.Vendor, "AuthenticAMD") == 0)  this->ChipManufacturer = AMD;          // Advanced Micro Devices
-  else if (strcmp (this->ChipID.Vendor, "AMD ISBETTER") == 0)  this->ChipManufacturer = AMD;          // Advanced Micro Devices (1994)
-  else if (strcmp (this->ChipID.Vendor, "CyrixInstead") == 0)  this->ChipManufacturer = Cyrix;        // Cyrix Corp., VIA Inc.
-  else if (strcmp (this->ChipID.Vendor, "NexGenDriven") == 0)  this->ChipManufacturer = NexGen;        // NexGen Inc. (now AMD)
-  else if (strcmp (this->ChipID.Vendor, "CentaurHauls") == 0)  this->ChipManufacturer = IDT;          // IDT/Centaur (now VIA)
-  else if (strcmp (this->ChipID.Vendor, "RiseRiseRise") == 0)  this->ChipManufacturer = Rise;        // Rise
-  else if (strcmp (this->ChipID.Vendor, "GenuineTMx86") == 0)  this->ChipManufacturer = Transmeta;      // Transmeta
-  else if (strcmp (this->ChipID.Vendor, "TransmetaCPU") == 0)  this->ChipManufacturer = Transmeta;      // Transmeta
-  else if (strcmp (this->ChipID.Vendor, "Geode By NSC") == 0)  this->ChipManufacturer = NSC;          // National Semiconductor
-  else if (strcmp (this->ChipID.Vendor, "Sun") == 0)           this->ChipManufacturer = Sun;          // Sun Microelectronics
-  else if (strcmp (this->ChipID.Vendor, "IBM") == 0)           this->ChipManufacturer = IBM;          // IBM Microelectronics
-  else if (strcmp (this->ChipID.Vendor, "Motorola") == 0)      this->ChipManufacturer = Motorola;          // Motorola Microelectronics
-  else                                                         this->ChipManufacturer = UnknownManufacturer;  // Unknown manufacturer
+  if (this->ChipID.Vendor == "GenuineIntel")       this->ChipManufacturer = Intel;        // Intel Corp.
+  else if (this->ChipID.Vendor == "UMC UMC UMC ")  this->ChipManufacturer = UMC;          // United Microelectronics Corp.
+  else if (this->ChipID.Vendor == "AuthenticAMD")  this->ChipManufacturer = AMD;          // Advanced Micro Devices
+  else if (this->ChipID.Vendor == "AMD ISBETTER")  this->ChipManufacturer = AMD;          // Advanced Micro Devices (1994)
+  else if (this->ChipID.Vendor == "CyrixInstead")  this->ChipManufacturer = Cyrix;        // Cyrix Corp., VIA Inc.
+  else if (this->ChipID.Vendor == "NexGenDriven")  this->ChipManufacturer = NexGen;        // NexGen Inc. (now AMD)
+  else if (this->ChipID.Vendor == "CentaurHauls")  this->ChipManufacturer = IDT;          // IDT/Centaur (now VIA)
+  else if (this->ChipID.Vendor == "RiseRiseRise")  this->ChipManufacturer = Rise;        // Rise
+  else if (this->ChipID.Vendor == "GenuineTMx86")  this->ChipManufacturer = Transmeta;      // Transmeta
+  else if (this->ChipID.Vendor == "TransmetaCPU")  this->ChipManufacturer = Transmeta;      // Transmeta
+  else if (this->ChipID.Vendor == "Geode By NSC")  this->ChipManufacturer = NSC;          // National Semiconductor
+  else if (this->ChipID.Vendor == "Sun")           this->ChipManufacturer = Sun;          // Sun Microelectronics
+  else if (this->ChipID.Vendor == "IBM")           this->ChipManufacturer = IBM;          // IBM Microelectronics
+  else if (this->ChipID.Vendor == "Motorola")      this->ChipManufacturer = Motorola;          // Motorola Microelectronics
+  else                                             this->ChipManufacturer = UnknownManufacturer;  // Unknown manufacturer
 }
 
 
@@ -1094,10 +1095,12 @@ bool SystemInformationImplementation::RetrieveCPUIdentity()
     }
 
   // Process the returned information.
-  memcpy (this->ChipID.Vendor, &(localCPUVendor[0]), sizeof (int));
-  memcpy (&(this->ChipID.Vendor[4]), &(localCPUVendor[1]), sizeof (int));
-  memcpy (&(this->ChipID.Vendor[8]), &(localCPUVendor[2]), sizeof (int));
-  this->ChipID.Vendor[12] = '\0';
+  char vbuf[13];
+  memcpy (&(vbuf[0]), &(localCPUVendor[0]), sizeof (int));
+  memcpy (&(vbuf[4]), &(localCPUVendor[1]), sizeof (int));
+  memcpy (&(vbuf[8]), &(localCPUVendor[2]), sizeof (int));
+  vbuf[12] = '\0';
+  this->ChipID.Vendor = vbuf;
 
   this->FindManufacturer();
 
@@ -1792,7 +1795,8 @@ bool SystemInformationImplementation::RetrieveProcessorSerialNumber()
     }
 
   // Process the returned information.
-  sprintf (this->ChipID.SerialNumber, "%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x",
+  char sn[128];
+  sprintf (sn, "%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x",
        ((SerialNumber[0] & 0xff000000) >> 24),
        ((SerialNumber[0] & 0x00ff0000) >> 16),
        ((SerialNumber[0] & 0x0000ff00) >> 8),
@@ -1805,7 +1809,7 @@ bool SystemInformationImplementation::RetrieveProcessorSerialNumber()
        ((SerialNumber[2] & 0x00ff0000) >> 16),
        ((SerialNumber[2] & 0x0000ff00) >> 8),
        ((SerialNumber[2] & 0x000000ff) >> 0));
-
+  this->ChipID.SerialNumber = sn;
   return true;
 
 #else
@@ -1873,6 +1877,15 @@ bool SystemInformationImplementation::RetrieveCPUPowerManagement()
 #endif
 }
 
+void SystemInformationStripLeadingSpace(kwsys_stl::string& str)
+{
+  // Because some manufacturers have leading white space - we have to post-process the name.
+  kwsys_stl::string::size_type pos = str.find_first_not_of(" ");
+  if(pos != kwsys_stl::string::npos)
+    {
+    str = str.substr(pos);
+    }
+}
 
 /** */
 bool SystemInformationImplementation::RetrieveExtendedCPUIdentity()
@@ -1886,7 +1899,6 @@ bool SystemInformationImplementation::RetrieveExtendedCPUIdentity()
     return false;
 
 #if USE_ASM_INSTRUCTIONS
-  int ProcessorNameStartPos = 0;
   int CPUExtendedIdentity[12];
 
   // Use assembly to detect CPUID information...
@@ -1942,47 +1954,25 @@ bool SystemInformationImplementation::RetrieveExtendedCPUIdentity()
     }
 
   // Process the returned information.
-  memcpy (this->ChipID.ProcessorName, &(CPUExtendedIdentity[0]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[4]), &(CPUExtendedIdentity[1]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[8]), &(CPUExtendedIdentity[2]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[12]), &(CPUExtendedIdentity[3]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[16]), &(CPUExtendedIdentity[4]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[20]), &(CPUExtendedIdentity[5]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[24]), &(CPUExtendedIdentity[6]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[28]), &(CPUExtendedIdentity[7]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[32]), &(CPUExtendedIdentity[8]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[36]), &(CPUExtendedIdentity[9]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[40]), &(CPUExtendedIdentity[10]), sizeof (int));
-  memcpy (&(this->ChipID.ProcessorName[44]), &(CPUExtendedIdentity[11]), sizeof (int));
-  this->ChipID.ProcessorName[48] = '\0';
+  char nbuf[49];
+  memcpy (&(nbuf[0]), &(CPUExtendedIdentity[0]), sizeof (int));
+  memcpy (&(nbuf[4]), &(CPUExtendedIdentity[1]), sizeof (int));
+  memcpy (&(nbuf[8]), &(CPUExtendedIdentity[2]), sizeof (int));
+  memcpy (&(nbuf[12]), &(CPUExtendedIdentity[3]), sizeof (int));
+  memcpy (&(nbuf[16]), &(CPUExtendedIdentity[4]), sizeof (int));
+  memcpy (&(nbuf[20]), &(CPUExtendedIdentity[5]), sizeof (int));
+  memcpy (&(nbuf[24]), &(CPUExtendedIdentity[6]), sizeof (int));
+  memcpy (&(nbuf[28]), &(CPUExtendedIdentity[7]), sizeof (int));
+  memcpy (&(nbuf[32]), &(CPUExtendedIdentity[8]), sizeof (int));
+  memcpy (&(nbuf[36]), &(CPUExtendedIdentity[9]), sizeof (int));
+  memcpy (&(nbuf[40]), &(CPUExtendedIdentity[10]), sizeof (int));
+  memcpy (&(nbuf[44]), &(CPUExtendedIdentity[11]), sizeof (int));
+  nbuf[48] = '\0';
+  this->ChipID.ProcessorName = nbuf;
 
   // Because some manufacturers have leading white space - we have to post-process the name.
-  if (this->ChipManufacturer == Intel) 
-    {
-    for (int nCounter = 0; nCounter < CHIPNAME_STRING_LENGTH; nCounter ++) 
-      {
-      // There will either be NULL (\0) or spaces ( ) as the leading characters.
-      if ((this->ChipID.ProcessorName[nCounter] != '\0') && (this->ChipID.ProcessorName[nCounter] != ' ')) 
-        {
-        // We have found the starting position of the name.
-        ProcessorNameStartPos = nCounter;
-        // Terminate the loop.
-        break;
-        }
-      }
-
-    // Check to see if there is any white space at the start.
-    if (ProcessorNameStartPos == 0) 
-      {
-      return true;
-      }
-
-    // Now move the name forward so that there is no white space.
-    memmove(this->ChipID.ProcessorName, &(this->ChipID.ProcessorName[ProcessorNameStartPos]), (CHIPNAME_STRING_LENGTH - ProcessorNameStartPos));
-   }
-
+  SystemInformationStripLeadingSpace(this->ChipID.ProcessorName);
   return true;
-
 #else
   return false;
 #endif
@@ -1999,53 +1989,53 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
       // Check the family / model / revision to determine the CPU ID.
       switch (this->ChipID.Family) {
         case 3:
-          sprintf (this->ChipID.ProcessorName, "Newer i80386 family"); 
+          this->ChipID.ProcessorName =  "Newer i80386 family"; 
           break;
         case 4:
           switch (this->ChipID.Model) {
-            case 0: sprintf (this->ChipID.ProcessorName,"i80486DX-25/33"); break;
-            case 1: sprintf (this->ChipID.ProcessorName,"i80486DX-50"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"i80486SX"); break;
-            case 3: sprintf (this->ChipID.ProcessorName,"i80486DX2"); break;
-            case 4: sprintf (this->ChipID.ProcessorName,"i80486SL"); break;
-            case 5: sprintf (this->ChipID.ProcessorName,"i80486SX2"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"i80486DX2 WriteBack"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"i80486DX4"); break;
-            case 9: sprintf (this->ChipID.ProcessorName,"i80486DX4 WriteBack"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown 80486 family"); return false;
+            case 0: this->ChipID.ProcessorName = "i80486DX-25/33"; break;
+            case 1: this->ChipID.ProcessorName = "i80486DX-50"; break;
+            case 2: this->ChipID.ProcessorName = "i80486SX"; break;
+            case 3: this->ChipID.ProcessorName = "i80486DX2"; break;
+            case 4: this->ChipID.ProcessorName = "i80486SL"; break;
+            case 5: this->ChipID.ProcessorName = "i80486SX2"; break;
+            case 7: this->ChipID.ProcessorName = "i80486DX2 WriteBack"; break;
+            case 8: this->ChipID.ProcessorName = "i80486DX4"; break;
+            case 9: this->ChipID.ProcessorName = "i80486DX4 WriteBack"; break;
+            default: this->ChipID.ProcessorName = "Unknown 80486 family"; return false;
             }
           break;
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"P5 A-Step"); break;
-            case 1: sprintf (this->ChipID.ProcessorName,"P5"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"P54C"); break;
-            case 3: sprintf (this->ChipID.ProcessorName,"P24T OverDrive"); break;
-            case 4: sprintf (this->ChipID.ProcessorName,"P55C"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"P54C"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"P55C (0.25micron)"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown Pentium family"); return false;
+            case 0: this->ChipID.ProcessorName = "P5 A-Step"; break;
+            case 1: this->ChipID.ProcessorName = "P5"; break;
+            case 2: this->ChipID.ProcessorName = "P54C"; break;
+            case 3: this->ChipID.ProcessorName = "P24T OverDrive"; break;
+            case 4: this->ChipID.ProcessorName = "P55C"; break;
+            case 7: this->ChipID.ProcessorName = "P54C"; break;
+            case 8: this->ChipID.ProcessorName = "P55C (0.25micron)"; break;
+            default: this->ChipID.ProcessorName = "Unknown Pentium family"; return false;
             }
           break;
         case 6:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"P6 A-Step"); break;
-            case 1: sprintf (this->ChipID.ProcessorName,"P6"); break;
-            case 3: sprintf (this->ChipID.ProcessorName,"Pentium II (0.28 micron)"); break;
-            case 5: sprintf (this->ChipID.ProcessorName,"Pentium II (0.25 micron)"); break;
-            case 6: sprintf (this->ChipID.ProcessorName,"Pentium II With On-Die L2 Cache"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"Pentium III (0.25 micron)"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"Pentium III (0.18 micron) With 256 KB On-Die L2 Cache "); break;
-            case 0xa: sprintf (this->ChipID.ProcessorName,"Pentium III (0.18 micron) With 1 Or 2 MB On-Die L2 Cache "); break;
-            case 0xb: sprintf (this->ChipID.ProcessorName,"Pentium III (0.13 micron) With 256 Or 512 KB On-Die L2 Cache "); break;
-            case 23: sprintf (this->ChipID.ProcessorName, "Intel(R) Core(TM)2 Duo CPU     T9500  @ 2.60GHz"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown P6 family"); return false;
+            case 0: this->ChipID.ProcessorName = "P6 A-Step"; break;
+            case 1: this->ChipID.ProcessorName = "P6"; break;
+            case 3: this->ChipID.ProcessorName = "Pentium II (0.28 micron)"; break;
+            case 5: this->ChipID.ProcessorName = "Pentium II (0.25 micron)"; break;
+            case 6: this->ChipID.ProcessorName = "Pentium II With On-Die L2 Cache"; break;
+            case 7: this->ChipID.ProcessorName = "Pentium III (0.25 micron)"; break;
+            case 8: this->ChipID.ProcessorName = "Pentium III (0.18 micron) With 256 KB On-Die L2 Cache "; break;
+            case 0xa: this->ChipID.ProcessorName = "Pentium III (0.18 micron) With 1 Or 2 MB On-Die L2 Cache "; break;
+            case 0xb: this->ChipID.ProcessorName = "Pentium III (0.13 micron) With 256 Or 512 KB On-Die L2 Cache "; break;
+            case 23: this->ChipID.ProcessorName =  "Intel(R) Core(TM)2 Duo CPU     T9500  @ 2.60GHz"; break;
+            default: this->ChipID.ProcessorName = "Unknown P6 family"; return false;
             }
           break;
         case 7:
-          sprintf (this->ChipID.ProcessorName,"Intel Merced (IA-64)");
+          this->ChipID.ProcessorName = "Intel Merced (IA-64)";
           break;
         case 0xf:
           // Check the extended family bits...
@@ -2054,21 +2044,21 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
             case 0:
               switch (this->ChipID.Model) 
                 {
-                case 0: sprintf (this->ChipID.ProcessorName,"Pentium IV (0.18 micron)"); break;
-                case 1: sprintf (this->ChipID.ProcessorName,"Pentium IV (0.18 micron)"); break;
-                case 2: sprintf (this->ChipID.ProcessorName,"Pentium IV (0.13 micron)"); break;
-                default: sprintf (this->ChipID.ProcessorName,"Unknown Pentium 4 family"); return false;
+                case 0: this->ChipID.ProcessorName = "Pentium IV (0.18 micron)"; break;
+                case 1: this->ChipID.ProcessorName = "Pentium IV (0.18 micron)"; break;
+                case 2: this->ChipID.ProcessorName = "Pentium IV (0.13 micron)"; break;
+                default: this->ChipID.ProcessorName = "Unknown Pentium 4 family"; return false;
                 }
               break;
             case 1:
-              sprintf (this->ChipID.ProcessorName,"Intel McKinley (IA-64)");
+              this->ChipID.ProcessorName = "Intel McKinley (IA-64)";
               break;
             default:
-              sprintf (this->ChipID.ProcessorName,"Pentium");
+              this->ChipID.ProcessorName = "Pentium";
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown Intel family");
+          this->ChipID.ProcessorName = "Unknown Intel family";
           return false;
         }
       break;
@@ -2080,49 +2070,49 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 4:
           switch (this->ChipID.Model) 
             {
-            case 3: sprintf (this->ChipID.ProcessorName,"80486DX2"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"80486DX2 WriteBack"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"80486DX4"); break;
-            case 9: sprintf (this->ChipID.ProcessorName,"80486DX4 WriteBack"); break;
-            case 0xe: sprintf (this->ChipID.ProcessorName,"5x86"); break;
-            case 0xf: sprintf (this->ChipID.ProcessorName,"5x86WB"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown 80486 family"); return false;
+            case 3: this->ChipID.ProcessorName = "80486DX2"; break;
+            case 7: this->ChipID.ProcessorName = "80486DX2 WriteBack"; break;
+            case 8: this->ChipID.ProcessorName = "80486DX4"; break;
+            case 9: this->ChipID.ProcessorName = "80486DX4 WriteBack"; break;
+            case 0xe: this->ChipID.ProcessorName = "5x86"; break;
+            case 0xf: this->ChipID.ProcessorName = "5x86WB"; break;
+            default: this->ChipID.ProcessorName = "Unknown 80486 family"; return false;
             }
           break;
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"SSA5 (PR75, PR90, PR100)"); break;
-            case 1: sprintf (this->ChipID.ProcessorName,"5k86 (PR120, PR133)"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"5k86 (PR166)"); break;
-            case 3: sprintf (this->ChipID.ProcessorName,"5k86 (PR200)"); break;
-            case 6: sprintf (this->ChipID.ProcessorName,"K6 (0.30 micron)"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"K6 (0.25 micron)"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"K6-2"); break;
-            case 9: sprintf (this->ChipID.ProcessorName,"K6-III"); break;
-            case 0xd: sprintf (this->ChipID.ProcessorName,"K6-2+ or K6-III+ (0.18 micron)"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown 80586 family"); return false;
+            case 0: this->ChipID.ProcessorName = "SSA5 (PR75, PR90 =  PR100)"; break;
+            case 1: this->ChipID.ProcessorName = "5k86 (PR120 =  PR133)"; break;
+            case 2: this->ChipID.ProcessorName = "5k86 (PR166)"; break;
+            case 3: this->ChipID.ProcessorName = "5k86 (PR200)"; break;
+            case 6: this->ChipID.ProcessorName = "K6 (0.30 micron)"; break;
+            case 7: this->ChipID.ProcessorName = "K6 (0.25 micron)"; break;
+            case 8: this->ChipID.ProcessorName = "K6-2"; break;
+            case 9: this->ChipID.ProcessorName = "K6-III"; break;
+            case 0xd: this->ChipID.ProcessorName = "K6-2+ or K6-III+ (0.18 micron)"; break;
+            default: this->ChipID.ProcessorName = "Unknown 80586 family"; return false;
             }
           break;
         case 6:
           switch (this->ChipID.Model) 
             {
-            case 1: sprintf (this->ChipID.ProcessorName,"Athlon- (0.25 micron)"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"Athlon- (0.18 micron)"); break;
-            case 3: sprintf (this->ChipID.ProcessorName,"Duron- (SF core)"); break;
-            case 4: sprintf (this->ChipID.ProcessorName,"Athlon- (Thunderbird core)"); break;
-            case 6: sprintf (this->ChipID.ProcessorName,"Athlon- (Palomino core)"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"Duron- (Morgan core)"); break;
+            case 1: this->ChipID.ProcessorName = "Athlon- (0.25 micron)"; break;
+            case 2: this->ChipID.ProcessorName = "Athlon- (0.18 micron)"; break;
+            case 3: this->ChipID.ProcessorName = "Duron- (SF core)"; break;
+            case 4: this->ChipID.ProcessorName = "Athlon- (Thunderbird core)"; break;
+            case 6: this->ChipID.ProcessorName = "Athlon- (Palomino core)"; break;
+            case 7: this->ChipID.ProcessorName = "Duron- (Morgan core)"; break;
             case 8: 
               if (this->Features.ExtendedFeatures.SupportsMP)
-                sprintf (this->ChipID.ProcessorName,"Athlon - MP (Thoroughbred core)"); 
-              else sprintf (this->ChipID.ProcessorName,"Athlon - XP (Thoroughbred core)");
+                this->ChipID.ProcessorName = "Athlon - MP (Thoroughbred core)"; 
+              else this->ChipID.ProcessorName = "Athlon - XP (Thoroughbred core)";
               break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown K7 family"); return false;
+            default: this->ChipID.ProcessorName = "Unknown K7 family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown AMD family");
+          this->ChipID.ProcessorName = "Unknown AMD family";
           return false;
         }
       break;
@@ -2133,12 +2123,12 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 4: sprintf (this->ChipID.ProcessorName,"Crusoe TM3x00 and TM5x00"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown Crusoe family"); return false;
+            case 4: this->ChipID.ProcessorName = "Crusoe TM3x00 and TM5x00"; break;
+            default: this->ChipID.ProcessorName = "Unknown Crusoe family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown Transmeta family");
+          this->ChipID.ProcessorName = "Unknown Transmeta family";
           return false;
         }
       break;
@@ -2149,13 +2139,13 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"mP6 (0.25 micron)"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"mP6 (0.18 micron)"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown Rise family"); return false;
+            case 0: this->ChipID.ProcessorName = "mP6 (0.25 micron)"; break;
+            case 2: this->ChipID.ProcessorName = "mP6 (0.18 micron)"; break;
+            default: this->ChipID.ProcessorName = "Unknown Rise family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown Rise family");
+          this->ChipID.ProcessorName = "Unknown Rise family";
           return false;
         }
       break;
@@ -2166,13 +2156,13 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 4:
           switch (this->ChipID.Model) 
             {
-            case 1: sprintf (this->ChipID.ProcessorName,"U5D"); break;
-            case 2: sprintf (this->ChipID.ProcessorName,"U5S"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown UMC family"); return false;
+            case 1: this->ChipID.ProcessorName = "U5D"; break;
+            case 2: this->ChipID.ProcessorName = "U5S"; break;
+            default: this->ChipID.ProcessorName = "Unknown UMC family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown UMC family");
+          this->ChipID.ProcessorName = "Unknown UMC family";
           return false;
         }
       break;
@@ -2183,21 +2173,21 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 4: sprintf (this->ChipID.ProcessorName,"C6"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"C2"); break;
-            case 9: sprintf (this->ChipID.ProcessorName,"C3"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown IDT\\Centaur family"); return false;
+            case 4: this->ChipID.ProcessorName = "C6"; break;
+            case 8: this->ChipID.ProcessorName = "C2"; break;
+            case 9: this->ChipID.ProcessorName = "C3"; break;
+            default: this->ChipID.ProcessorName = "Unknown IDT\\Centaur family"; return false;
             }
           break;
         case 6:
           switch (this->ChipID.Model) 
             {
-            case 6: sprintf (this->ChipID.ProcessorName,"VIA Cyrix III - Samuel"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown IDT\\Centaur family"); return false;
+            case 6: this->ChipID.ProcessorName = "VIA Cyrix III - Samuel"; break;
+            default: this->ChipID.ProcessorName = "Unknown IDT\\Centaur family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown IDT\\Centaur family");
+          this->ChipID.ProcessorName = "Unknown IDT\\Centaur family";
           return false;
         }
       break;
@@ -2208,32 +2198,32 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 4:
           switch (this->ChipID.Model) 
             {
-            case 4: sprintf (this->ChipID.ProcessorName,"MediaGX GX, GXm"); break;
-            case 9: sprintf (this->ChipID.ProcessorName,"5x86"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown Cx5x86 family"); return false;
+            case 4: this->ChipID.ProcessorName = "MediaGX GX =  GXm"; break;
+            case 9: this->ChipID.ProcessorName = "5x86"; break;
+            default: this->ChipID.ProcessorName = "Unknown Cx5x86 family"; return false;
             }
           break;
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 2: sprintf (this->ChipID.ProcessorName,"Cx6x86"); break;
-            case 4: sprintf (this->ChipID.ProcessorName,"MediaGX GXm"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown Cx6x86 family"); return false;
+            case 2: this->ChipID.ProcessorName = "Cx6x86"; break;
+            case 4: this->ChipID.ProcessorName = "MediaGX GXm"; break;
+            default: this->ChipID.ProcessorName = "Unknown Cx6x86 family"; return false;
             }
           break;
         case 6:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"6x86MX"); break;
-            case 5: sprintf (this->ChipID.ProcessorName,"Cyrix M2 Core"); break;
-            case 6: sprintf (this->ChipID.ProcessorName,"WinChip C5A Core"); break;
-            case 7: sprintf (this->ChipID.ProcessorName,"WinChip C5B\\C5C Core"); break;
-            case 8: sprintf (this->ChipID.ProcessorName,"WinChip C5C-T Core"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown 6x86MX\\Cyrix III family"); return false;
+            case 0: this->ChipID.ProcessorName = "6x86MX"; break;
+            case 5: this->ChipID.ProcessorName = "Cyrix M2 Core"; break;
+            case 6: this->ChipID.ProcessorName = "WinChip C5A Core"; break;
+            case 7: this->ChipID.ProcessorName = "WinChip C5B\\C5C Core"; break;
+            case 8: this->ChipID.ProcessorName = "WinChip C5C-T Core"; break;
+            default: this->ChipID.ProcessorName = "Unknown 6x86MX\\Cyrix III family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown Cyrix family");
+          this->ChipID.ProcessorName = "Unknown Cyrix family";
           return false;
         }
       break;
@@ -2244,21 +2234,21 @@ bool SystemInformationImplementation::RetrieveClassicalCPUIdentity()
         case 5:
           switch (this->ChipID.Model) 
             {
-            case 0: sprintf (this->ChipID.ProcessorName,"Nx586 or Nx586FPU"); break;
-            default: sprintf (this->ChipID.ProcessorName,"Unknown NexGen family"); return false;
+            case 0: this->ChipID.ProcessorName = "Nx586 or Nx586FPU"; break;
+            default: this->ChipID.ProcessorName = "Unknown NexGen family"; return false;
             }
           break;
         default:
-          sprintf (this->ChipID.ProcessorName,"Unknown NexGen family");
+          this->ChipID.ProcessorName = "Unknown NexGen family";
           return false;
         }
       break;
 
     case NSC:
-      sprintf (this->ChipID.ProcessorName,"Cx486SLC \\ DLC \\ Cx486S A-Step");
+      this->ChipID.ProcessorName = "Cx486SLC \\ DLC \\ Cx486S A-Step";
       break;
     default:
-      sprintf (this->ChipID.ProcessorName,"Unknown family"); // We cannot identify the processor.
+      this->ChipID.ProcessorName = "Unknown family"; // We cannot identify the processor.
       return false;
     }
 
@@ -2365,7 +2355,7 @@ int SystemInformationImplementation::RetreiveInformationFromCpuInfoFile()
   this->ChipID.Family = atoi(this->ExtractValueFromCpuInfoFile(buffer,"cpu family").c_str());
  
   // Chip Vendor
-  strcpy(this->ChipID.Vendor,this->ExtractValueFromCpuInfoFile(buffer,"vendor_id").c_str());
+  this->ChipID.Vendor = this->ExtractValueFromCpuInfoFile(buffer,"vendor_id");
   this->FindManufacturer();
   
   // Chip Model
@@ -2964,7 +2954,7 @@ bool SystemInformationImplementation::ParseSysCtl()
     kwsys_stl::string machineBuf(retBuf);
     if (machineBuf.find_first_of("Power") != kwsys_stl::string::npos)
       {
-      strcpy(this->ChipID.Vendor, "IBM");
+      this->ChipID.Vendor = "IBM";
       len = 4;
       err = sysctlbyname("hw.cputype", &this->ChipID.Family, &len, NULL, 0);
       err = sysctlbyname("hw.cpusubtype", &this->ChipID.Model, &len, NULL, 0);
@@ -2982,13 +2972,14 @@ bool SystemInformationImplementation::ParseSysCtl()
     len = 128;
     err = sysctlbyname("machdep.cpu.vendor", retBuf, &len, NULL, 0);
     // Chip Vendor
-    strcpy(this->ChipID.Vendor,retBuf);
+    this->ChipID.Vendor = retBuf;
     this->FindManufacturer();
     
-    len=CHIPNAME_STRING_LENGTH;
+    ::memset(retBuf, 0, 128);
     err = 
       sysctlbyname("machdep.cpu.brand_string", 
-                   this->ChipID.ProcessorName, &len, NULL, 0);
+                   retBuf, &len, NULL, 0);
+    this->ChipID.ProcessorName = retBuf;
 
     // Chip Model
     len = sizeof(value);
@@ -3175,11 +3166,11 @@ bool SystemInformationImplementation::QuerySolarisInfo()
   this->ChipID.Family = 0; 
  
   // Chip Vendor
-  strcpy(this->ChipID.Vendor,"Sun");
+  this->ChipID.Vendor = "Sun";
   this->FindManufacturer();
   
   // Chip Model
-  sprintf(this->ChipID.ProcessorName,"%s",this->ParseValueFromKStat("-s cpu_type").c_str());
+  this->ChipID.ProcessorName = this->ParseValueFromKStat("-s cpu_type");
   this->ChipID.Model = 0;
 
   // Cache size
@@ -3233,7 +3224,7 @@ bool SystemInformationImplementation::QueryHaikuInfo()
   char vbuf[13];
   strncpy(vbuf, cpu_info.eax_0.vendor_id, 12);
   vbuf[12] = '\0';
-  strcpy(this->ChipID.Vendor,vbuf);
+  this->ChipID.Vendor = vbuf;
 
   this->FindManufacturer();
 