@@ -2028,6 +2028,12 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
       cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
       }
     cres.m_Name = testname;
+    if(m_TestsToRun.size() && 
+       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())
+      {
+      continue;
+      }
+
     if ( m_ShowOnly )
       {
       fprintf(stderr,"%3d/%3d Testing %-30s\n", cnt, (int)tmsize, testname.c_str());
@@ -4080,6 +4086,11 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
 
+    if(arg.find("-I",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      this->SetTestsToRunInformation(args[i].c_str());
+      }
     if(arg.find("-R",0) == 0 && i < args.size() - 1)
       {
       this->m_UseIncludeRegExp = true;
@@ -4775,3 +4786,110 @@ int cmCTest::ExecuteCommands(tm_VectorOfStrings& vec)
   return 1;
 }
 
+
+// get the next number in a string with numbers separated by ,
+// pos is the start of the search and pos2 is the end of the search
+// pos becomes pos2 after a call to GetNextNumber.   
+// -1 is returned at the end of the list.
+inline int GetNextNumber(std::string const& in, 
+                         int& val,
+                         std::string::size_type& pos,
+                         std::string::size_type& pos2)
+{
+  pos2 = in.find(',', pos);
+  if(pos2 != in.npos)
+    {
+    if(pos2-pos == 0)
+      {
+      val = -1;
+      }
+    else
+      {
+      val = atoi(in.substr(pos, pos2-pos).c_str());
+      }
+    pos = pos2+1;
+    return 1;
+    }
+  else
+    {
+    if(in.size()-pos == 0)
+      {
+       val = -1;
+      }
+    else
+      {
+      val = atoi(in.substr(pos, in.size()-pos).c_str());
+      }
+    return 0;
+    }
+}
+
+                         
+void cmCTest::SetTestsToRunInformation(const char* in)
+{
+  std::string testArgs = in;
+  // if the argument is a file, then read it and use the contents as the string
+  if(cmSystemTools::FileExists(in))
+    {
+    std::ifstream fin(in);
+    unsigned long filelen = cmSystemTools::FileLength(in);
+    char* buff = new char[filelen+1];
+    fin.getline(buff, filelen);
+    buff[fin.gcount()] = 0;
+    testArgs = buff;
+    }
+  int start = -1;
+  int end = -1;
+  int stride = -1;
+  std::string::size_type pos = 0;
+  std::string::size_type pos2 = 0;
+  // read start
+  if(GetNextNumber(testArgs, start, pos, pos2))
+    {
+    // read end
+    if(GetNextNumber(testArgs, end, pos, pos2))
+      {
+      // read stride
+      if(GetNextNumber(testArgs, stride, pos, pos2))
+        {
+        int val =0;
+        // now read specific numbers
+        while(GetNextNumber(testArgs, val, pos, pos2))
+          {
+          m_TestsToRun.push_back(val);
+          }
+        m_TestsToRun.push_back(val);
+        }
+      }
+    }
+  if(stride == -1)
+    {
+    stride = 1;
+    }
+  if(end != -1 && start != -1 && stride != 0 && stride != -1)
+    {
+    for(int i =start; i <= end; i+= stride)
+      {
+      m_TestsToRun.push_back(i);
+      }
+    }
+  else
+    {
+    if(start != -1)
+      {
+      m_TestsToRun.push_back(start);
+      }
+    }
+    // sort the array
+  std::sort(m_TestsToRun.begin(), m_TestsToRun.end(), std::less<int>());
+  // remove duplicates
+  std::vector<int>::iterator new_end = 
+    std::unique(m_TestsToRun.begin(), m_TestsToRun.end());
+  m_TestsToRun.erase(new_end, m_TestsToRun.end());
+  std::cout << "Running tests: ";
+  for(int i =0; i < m_TestsToRun.size(); ++i)
+    {
+    std::cout << m_TestsToRun[i] << " ";
+    }
+  std::cout << "\n";
+}