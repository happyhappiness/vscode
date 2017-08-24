/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmTryCompileCommand.h"
#include "cmake.h"
#include "cmCacheManager.h"
#include "cmGlobalGenerator.h"
#include "cmListFileCache.h"
#include <cmsys/Directory.hxx>

int cmTryCompileCommand::CoreTryCompileCode(
  cmMakefile *mf, std::vector<std::string> const& argv, bool clean)
{
  // which signature were we called with ?
  bool srcFileSignature = false;
  unsigned int i;
  
  // where will the binaries be stored
  const char* binaryDirectory = argv[1].c_str();
  const char* sourceDirectory = argv[2].c_str();
  const char* projectName = 0;
  const char* targetName = 0;
  std::string tmpString;
  int extraArgs = 0;
  
  // look for CMAKE_FLAGS and store them
  std::vector<std::string> cmakeFlags;
  for (i = 3; i < argv.size(); ++i)
    {
    if (argv[i] == "CMAKE_FLAGS")
      {
     // CMAKE_FLAGS is the first argument because we need an argv[0] that
     // is not used, so it matches regular command line parsing which has
     // the program name as arg 0
      for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS" && 
             argv[i] != "OUTPUT_VARIABLE"; 
           ++i)
        {
        extraArgs++;
        cmakeFlags.push_back(argv[i]);
        }
      break;
      }
    }

  // look for OUTPUT_VARIABLE and store them
  std::string outputVariable;
  for (i = 3; i < argv.size(); ++i)
    {
    if (argv[i] == "OUTPUT_VARIABLE")
      {
      if ( argv.size() <= (i+1) )
        {
        cmSystemTools::Error(
          "OUTPUT_VARIABLE specified but there is no variable");
        return -1;
        }
      extraArgs += 2;
      outputVariable = argv[i+1];
      break;
      }
    }

  // look for COMPILE_DEFINITIONS and store them
  std::vector<std::string> compileFlags;
  for (i = 3; i < argv.size(); ++i)
    {
    if (argv[i] == "COMPILE_DEFINITIONS")
      {
      extraArgs++;
      for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS" && 
             argv[i] != "OUTPUT_VARIABLE"; 
           ++i)
        {
        extraArgs++;
        compileFlags.push_back(argv[i]);
        }
      break;
      }
    }

  // do we have a srcfile signature
  if (argv.size() - extraArgs == 3)
    {
    srcFileSignature = true;
    }

  // only valid for srcfile signatures
  if (!srcFileSignature && compileFlags.size())
    {
    cmSystemTools::Error(
      "COMPILE_FLAGS specified on a srcdir type TRY_COMPILE");
    return -1;
    }

  // compute the binary dir when TRY_COMPILE is called with a src file
  // signature
  if (srcFileSignature)
    {
    tmpString = argv[1] + "/CMakeFiles/CMakeTmp";
    binaryDirectory = tmpString.c_str();
    }
  // make sure the binary directory exists
  cmSystemTools::MakeDirectory(binaryDirectory);
  
  // do not allow recursive try Compiles
  if (!strcmp(binaryDirectory,mf->GetHomeOutputDirectory()))
    {
    cmSystemTools::Error(
      "Attempt at a recursive or nested TRY_COMPILE in directory ",
      binaryDirectory);
    return -1;
    }
  
  std::string outFileName = tmpString + "/CMakeLists.txt";
  // which signature are we using? If we are using var srcfile bindir
  if (srcFileSignature)
    {
    // remove any CMakeCache.txt files so we will have a clean test
    std::string ccFile = tmpString + "/CMakeCache.txt";
    cmSystemTools::RemoveFile(ccFile.c_str());
    
    // we need to create a directory and CMakeList file etc...
    // first create the directories
    sourceDirectory = binaryDirectory;

    // now create a CMakeList.txt file in that directory
    FILE *fout = fopen(outFileName.c_str(),"w");
    if (!fout)
      {
      cmSystemTools::Error("Failed to create CMakeList file for ", 
                           outFileName.c_str());
      cmSystemTools::ReportLastSystemError("");
      return -1;
      }

    std::string source = argv[2];
    std::string ext = cmSystemTools::GetFilenameExtension(source);
    const char* lang = (mf->GetCMakeInstance()->GetGlobalGenerator()
                        ->GetLanguageFromExtension(ext.c_str()));
    const char* def = mf->GetDefinition("CMAKE_MODULE_PATH");
    if(def)
      {
      fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
      }
    if(lang)
      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE %s)\n", lang);
      }
    else
      {
      cmOStringStream err;
      err << "Unknown extension \"" << ext << "\" for file \""
          << source << "\".  TRY_COMPILE only works for enabled languages.\n"
          << "Currently enabled languages are:";
      std::vector<std::string> langs;
      mf->GetCMakeInstance()->GetGlobalGenerator()->GetEnabledLanguages(langs);
      for(std::vector<std::string>::iterator l = langs.begin();
          l != langs.end(); ++l)
        {
        err << " " << *l;
        }
      err << "\nSee PROJECT command for help enabling other languages.";
      cmSystemTools::Error(err.str().c_str());
      return -1;
      }
    std::string langFlags = "CMAKE_";
    langFlags +=  lang;
    langFlags += "_FLAGS";
    fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
    fprintf(fout, "SET(CMAKE_%s_FLAGS \"", lang);
    const char* flags = mf->GetDefinition(langFlags.c_str()); 
    if(flags)
      {
      fprintf(fout, " %s ", flags);
      }
    fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
    // handle any compile flags we need to pass on
    if (compileFlags.size())
      {
      fprintf(fout, "ADD_DEFINITIONS( ");
      for (i = 0; i < compileFlags.size(); ++i)
        {
        fprintf(fout,"%s ",compileFlags[i].c_str());
        }
      fprintf(fout, ")\n");
      }
    
    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());
    fprintf(fout, 
            "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    targetName = "cmTryCompileExec";
    // if the source is not in CMakeTmp 
    if(source.find("CMakeTmp") == source.npos)
      {
      mf->AddCMakeDependFile(source.c_str());
      }
    
    }
  // else the srcdir bindir project target signature
  else
    {
    projectName = argv[3].c_str();
    
    if (argv.size() - extraArgs == 5)
      {
      targetName = argv[4].c_str();
      }
    }
  
  bool erroroc = cmSystemTools::GetErrorOccuredFlag();
  cmSystemTools::ResetErrorOccuredFlag();
  std::string output;
  // actually do the try compile now that everything is setup
  int res = mf->TryCompile(sourceDirectory, binaryDirectory,
                           projectName, targetName, &cmakeFlags, &output);
  
  if ( erroroc )
    {
    cmSystemTools::SetErrorOccured();
    }
  
  // set the result var to the return value to indicate success or failure
  mf->AddCacheDefinition(argv[0].c_str(), (res == 0 ? "TRUE" : "FALSE"),
                         "Result of TRY_COMPILE",
                         cmCacheManager::INTERNAL);

  if ( outputVariable.size() > 0 )
    {
    mf->AddDefinition(outputVariable.c_str(), output.c_str());
    }
  
  // if They specified clean then we clean up what we can
  if (srcFileSignature && clean)
    {    
    if(!mf->GetCMakeInstance()->GetDebugTryCompile())
      {
      cmTryCompileCommand::CleanupFiles(binaryDirectory);
      }
    }
  return res;
}

// cmExecutableCommand
bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
{
  if(argv.size() < 3)
    {
    return false;
    }

  cmTryCompileCommand::CoreTryCompileCode(m_Makefile,argv,true);
  
  return true;
}

void cmTryCompileCommand::CleanupFiles(const char* binDir)
{
  if ( !binDir )
    {
    return;
    }
  
  std::string bdir = binDir;
  if(bdir.find("CMakeTmp") == std::string::npos)
    {
    cmSystemTools::Error(
      "TRY_COMPILE attempt to remove -rf directory that does not contain "
      "CMakeTmp:", binDir);
    return;
    }
  
  cmsys::Directory dir;
  dir.Load(binDir);
  size_t fileNum;
  std::set<cmStdString> deletedFiles;
  for (fileNum = 0; fileNum <  dir.GetNumberOfFiles(); ++fileNum)
    {
    if (strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)),".") &&
        strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)),".."))
      {
      
      if(deletedFiles.find( dir.GetFile(static_cast<unsigned long>(fileNum))) 
         == deletedFiles.end())
        {
        deletedFiles.insert(dir.GetFile(static_cast<unsigned long>(fileNum)));
        std::string fullPath = binDir;
        fullPath += "/";
        fullPath += dir.GetFile(static_cast<unsigned long>(fileNum));
        if(cmSystemTools::FileIsDirectory(fullPath.c_str()))
          {
          cmTryCompileCommand::CleanupFiles(fullPath.c_str());
          }
        else
          {
          if(!cmSystemTools::RemoveFile(fullPath.c_str()))
            {
            std::string m = "Remove failed on file: ";
            m += fullPath;
            cmSystemTools::ReportLastSystemError(m.c_str());
            }
          }
        }
      }
    }
}
