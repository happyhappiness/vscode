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
#include "cmGlobalGenerator.h"
#include "cmLocalGenerator.h"
#include "cmake.h"
#include "cmMakefile.h"

#include <stdlib.h> // required for atof

#if defined(_WIN32) && !defined(__CYGWIN__) 
#include <windows.h>
#endif

#include <assert.h>

int cmGlobalGenerator::s_TryCompileTimeout = 0;

cmGlobalGenerator::cmGlobalGenerator()
{
  // by default use the native paths
  m_ForceUnixPaths = false;
}

cmGlobalGenerator::~cmGlobalGenerator()
{ 
  // Delete any existing cmLocalGenerators
  unsigned int i;
  for (i = 0; i < m_LocalGenerators.size(); ++i)
    {
    delete m_LocalGenerators[i];
    }
  m_LocalGenerators.clear();
}

// Find the make program for the generator, required for try compiles
void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
{
  if(m_FindMakeProgramFile.size() == 0)
    {
    cmSystemTools::Error(
      "Generator implementation error, "
      "all generators must specify m_FindMakeProgramFile");
    }
  if(!mf->GetDefinition("CMAKE_MAKE_PROGRAM")
     || cmSystemTools::IsOff(mf->GetDefinition("CMAKE_MAKE_PROGRAM")))
    {
    std::string setMakeProgram = mf->GetModulesFile(m_FindMakeProgramFile.c_str());
    if(setMakeProgram.size())
      {
      mf->ReadListFile(0, setMakeProgram.c_str());
      }
    } 
  if(!mf->GetDefinition("CMAKE_MAKE_PROGRAM")
     || cmSystemTools::IsOff(mf->GetDefinition("CMAKE_MAKE_PROGRAM")))
    {
    cmOStringStream err;
    err << "CMake was unable to find a build program corresponding to \""
        << this->GetName() << "\".  CMAKE_MAKE_PROGRAM is not set.  You "
        << "probably need to select a different build tool.";
    cmSystemTools::Error(err.str().c_str());
    cmSystemTools::SetFatalErrorOccured();
    return;
    }
  std::string makeProgram = mf->GetRequiredDefinition("CMAKE_MAKE_PROGRAM");
  // if there are spaces in the make program use short path
  // but do not short path the actual program name, as
  // this can cause trouble with VSExpress
  if(makeProgram.find(' ') != makeProgram.npos)
    {
    std::string dir;
    std::string file;
    cmSystemTools::SplitProgramPath(makeProgram.c_str(),
                                    dir, file);
    std::string saveFile = file;
    cmSystemTools::GetShortPath(makeProgram.c_str(), makeProgram);
    cmSystemTools::SplitProgramPath(makeProgram.c_str(),
                                    dir, file);
    makeProgram = dir;
    makeProgram += "/";
    makeProgram += saveFile;
    this->GetCMakeInstance()->AddCacheEntry("CMAKE_MAKE_PROGRAM", makeProgram.c_str(),
                                            "make program",
                                            cmCacheManager::FILEPATH);
    }
  
}

// enable the given language
void cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
                                       cmMakefile *mf)
{  
  if(languages.size() == 0)
    {
    cmSystemTools::Error("EnableLanguage must have a lang specified!");
    cmSystemTools::SetFatalErrorOccured();
    return;
    }

  mf->AddDefinition("RUN_CONFIGURE", true);
  bool needTestLanguage = false;
  std::string rootBin = mf->GetHomeOutputDirectory();
  // If the configuration files path has been set,
  // then we are in a try compile and need to copy the enable language
  // files into the try compile directory
  if(m_ConfiguredFilesPath.size())
    {
    std::string src = m_ConfiguredFilesPath;
    src += "/CMakeSystem.cmake";
    std::string dst = rootBin;
    dst += "/CMakeSystem.cmake";
    cmSystemTools::CopyFileIfDifferent(src.c_str(), dst.c_str());
    for(std::vector<std::string>::const_iterator l = languages.begin();
        l != languages.end(); ++l)
      {
      if(*l == "NONE")
        {
        this->SetLanguageEnabled("NONE", mf);
        continue;
        }
      const char* lang = l->c_str();
      std::string src2 = m_ConfiguredFilesPath;
      src2 += "/CMake";
      src2 += lang;
      src2 += "Compiler.cmake";
      std::string dst2 = rootBin;
      dst2 += "/CMake";
      dst2 += lang;
      dst2 += "Compiler.cmake";
      cmSystemTools::CopyFileIfDifferent(src2.c_str(), dst2.c_str()); 
      src2 = m_ConfiguredFilesPath;
      src2 += "/CMake";
      src2 += lang;
      src2 += "Platform.cmake";
      dst2 = rootBin;
      dst2 += "/CMake";
      dst2 += lang;
      dst2 += "Platform.cmake";
      cmSystemTools::CopyFileIfDifferent(src2.c_str(), dst2.c_str());
      }
    rootBin = m_ConfiguredFilesPath;
    }

  // **** Step 1, find and make sure CMAKE_MAKE_PROGRAM is defined
  this->FindMakeProgram(mf);

  // try and load the CMakeSystem.cmake if it is there
  std::string fpath = rootBin;
  if(!mf->GetDefinition("CMAKE_SYSTEM_LOADED"))
    {
    fpath += "/CMakeSystem.cmake";
    if(cmSystemTools::FileExists(fpath.c_str()))
      {
      mf->ReadListFile(0,fpath.c_str());
      }
    }
  // **** Step 2, Load the CMakeDetermineSystem.cmake file and find out
  // what platform we are running on
  if (!mf->GetDefinition("CMAKE_SYSTEM_NAME"))
    {
#if defined(_WIN32) && !defined(__CYGWIN__) 
    /* Windows version number data.  */
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(osvi));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx (&osvi);
    cmOStringStream windowsVersionString;
    windowsVersionString << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;
    windowsVersionString.str();
    mf->AddDefinition("CMAKE_SYSTEM_VERSION", windowsVersionString.str().c_str());
#endif
    // Read the DetermineSystem file
    std::string systemFile = mf->GetModulesFile("CMakeDetermineSystem.cmake");
    mf->ReadListFile(0, systemFile.c_str());
    }
  // **** Step 3, load the CMakeSystem.cmake from the binary directory
  // this file is configured by the CMakeDetermineSystem.cmake file
  fpath = rootBin;
  if(!mf->GetDefinition("CMAKE_SYSTEM_LOADED"))
    {
    fpath += "/CMakeSystem.cmake";
    mf->ReadListFile(0,fpath.c_str());
    }
  // **** Step 4, foreach language 
  // load the CMakeDetermine(LANG)Compiler.cmake file to find
  // the compiler 
  for(std::vector<std::string>::const_iterator l = languages.begin();
      l != languages.end(); ++l)
    {
    const char* lang = l->c_str();
    if(*l == "NONE")
      {
      this->SetLanguageEnabled("NONE", mf);
      continue;
      }

    if(!this->GetLanguageEnabled(lang) )
      {  
      if (m_CMakeInstance->GetIsInTryCompile())
        {
        cmSystemTools::Error("This should not have happen. "
                             "If you see this message, you are probably using a "
                             "broken CMakeLists.txt file or a problematic release of "
                             "CMake");
        }

      // If the existing build tree was already configured with this
      // version of CMake then try to load the configured file first
      // to avoid duplicate compiler tests.
      unsigned int cacheMajor = mf->GetCacheMajorVersion();
      unsigned int cacheMinor = mf->GetCacheMinorVersion();
      unsigned int selfMajor = cmMakefile::GetMajorVersion();
      unsigned int selfMinor = cmMakefile::GetMinorVersion();
      if(selfMajor == cacheMajor && selfMinor == cacheMinor)
        {
        std::string loadedLang = "CMAKE_";
        loadedLang +=  lang;
        loadedLang += "_COMPILER_LOADED";
        if(!mf->GetDefinition(loadedLang.c_str()))
          {
          fpath = rootBin;
          fpath += "/CMake";
          fpath += lang;
          fpath += "Compiler.cmake";
          if(cmSystemTools::FileExists(fpath.c_str()))
            {
            if(!mf->ReadListFile(0,fpath.c_str()))
              {
              cmSystemTools::Error("Could not find cmake module file:", fpath.c_str());
              }
            this->SetLanguageEnabled(lang, mf);
            }
          }
        }
      
      needTestLanguage = true; // must test a language after finding it
      // read determine LANG compiler
      std::string determineCompiler = "CMakeDetermine";
      determineCompiler += lang;
      determineCompiler += "Compiler.cmake";
      std::string determineFile = mf->GetModulesFile(determineCompiler.c_str());
      if(!mf->ReadListFile(0,determineFile.c_str()))
        {
        cmSystemTools::Error("Could not find cmake module file:", determineFile.c_str());
        }
      // Some generators like visual studio should not use the env variables
      // So the global generator can specify that in this variable
      if(!mf->GetDefinition("CMAKE_GENERATOR_NO_COMPILER_ENV"))
        {
        // put ${CMake_(LANG)_COMPILER_ENV_VAR}=${CMAKE_(LANG)_COMPILER into the
        // environment, in case user scripts want to run configure, or sub cmakes
        std::string compilerName = "CMAKE_";
        compilerName += lang;
        compilerName += "_COMPILER";
        std::string compilerEnv = "CMAKE_";
        compilerEnv += lang;
        compilerEnv += "_COMPILER_ENV_VAR";
        std::string envVar = mf->GetRequiredDefinition(compilerEnv.c_str());
        std::string envVarValue = mf->GetRequiredDefinition(compilerName.c_str());
        std::string env = envVar;
        env += "=";
        env += envVarValue;
        cmSystemTools::PutEnv(env.c_str());
        }
      }
    
    // **** Step 5, Load the configured language compiler file, if not loaded.
    // look to see if CMAKE_(LANG)_COMPILER_LOADED is set, 
    // if not then load the CMake(LANG)Compiler.cmake file from the
    // binary tree, this is a configured file provided by
    // CMakeDetermine(LANG)Compiler.cmake
    std::string loadedLang = "CMAKE_";
    loadedLang +=  lang;
    loadedLang += "_COMPILER_LOADED";
    if(!mf->GetDefinition(loadedLang.c_str()))
      {
      fpath = rootBin;
      fpath += "/CMake";
      fpath += lang;
      fpath += "Compiler.cmake";
      if(!mf->ReadListFile(0,fpath.c_str()))
        {
        cmSystemTools::Error("Could not find cmake module file:", fpath.c_str());
        }
      this->SetLanguageEnabled(lang, mf);
      }
    }
  
  // **** Step 6, Load the system specific information if not yet loaded
  if (!mf->GetDefinition("CMAKE_SYSTEM_SPECIFIC_INFORMATION_LOADED"))
    {
    fpath = mf->GetModulesFile("CMakeSystemSpecificInformation.cmake");
    if(!mf->ReadListFile(0,fpath.c_str()))
      {
      cmSystemTools::Error("Could not find cmake module file:", fpath.c_str());
      }
    }
  for(std::vector<std::string>::const_iterator l = languages.begin();
      l != languages.end(); ++l)
    {
    const char* lang = l->c_str();
    if(*l == "NONE")
      {
      this->SetLanguageEnabled("NONE", mf);
      continue;
      }
    std::string langLoadedVar = "CMAKE_";
    langLoadedVar += lang;
    langLoadedVar += "_INFORMATION_LOADED";
    if (!mf->GetDefinition(langLoadedVar.c_str()))
      { 
      fpath = "CMake";
      fpath +=  lang;
      fpath += "Information.cmake";
      fpath = mf->GetModulesFile(fpath.c_str());
      if(!mf->ReadListFile(0,fpath.c_str()))
        {
        cmSystemTools::Error("Could not find cmake module file:", fpath.c_str());
        }
      }
    // **** Step 7, Test the compiler for the language just setup
    // At this point we should have enough info for a try compile
    // which is used in the backward stuff
    if(needTestLanguage)
      {
      if (!m_CMakeInstance->GetIsInTryCompile())
        {
        std::string testLang = "CMakeTest";
        testLang += lang;
        testLang += "Compiler.cmake";
        std::string ifpath = mf->GetModulesFile(testLang.c_str());
        if(!mf->ReadListFile(0,ifpath.c_str()))
          {
          cmSystemTools::Error("Could not find cmake module file:", ifpath.c_str());
          }
        // **** Step 8, load backwards compatibility stuff for C and CXX
        // for old versions of CMake ListFiles C and CXX had some
        // backwards compatibility files they have to load
        const char* versionValue
          = mf->GetDefinition("CMAKE_BACKWARDS_COMPATIBILITY");
        if (atof(versionValue) <= 1.4)
          {
          if(strcmp(lang, "C") == 0)
            {
            ifpath =  mf->GetModulesFile("CMakeBackwardCompatibilityC.cmake");
            mf->ReadListFile(0,ifpath.c_str()); 
            }
          if(strcmp(lang, "CXX") == 0)
            {
            ifpath =  mf->GetModulesFile("CMakeBackwardCompatibilityCXX.cmake");
            mf->ReadListFile(0,ifpath.c_str()); 
            }
          
          }
        }
      }
    }
}

const char* cmGlobalGenerator::GetLanguageOutputExtensionForLanguage(const char* lang)
{
  if(!lang) 
    {
    return "";
    }
  if(m_LanguageToOutputExtension.count(lang) > 0)
    {
    return m_LanguageToOutputExtension[lang].c_str();
    }
  return "";
}

const char* cmGlobalGenerator::GetLanguageOutputExtensionFromExtension(const char* ext)
{
  if(!ext)
    {
    return "";
    }
  const char* lang = this->GetLanguageFromExtension(ext);
  if(!lang || *lang == 0)
    {
    // if no language is found then check to see if it is already an
    // ouput extension for some language.  In that case it should be ignored
    // and in this map, so it will not be compiled but will just be used.
    if(m_OutputExtensions.count(ext))
      {
      return ext;
      }
    }
  return this->GetLanguageOutputExtensionForLanguage(lang);
}


const char* cmGlobalGenerator::GetLanguageFromExtension(const char* ext)
{
  // if there is an extension and it starts with . then
  // move past the . because the extensions are not stored with a .
  // in the map
  if(ext && *ext == '.')
    {
    ++ext;
    }
  if(m_ExtensionToLanguage.count(ext) > 0)
    {
    return m_ExtensionToLanguage[ext].c_str();
    }
  return 0;
}

void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
{
  if(m_LanguageEnabled.count(l) > 0)
    {
    return;
    }
  std::string outputExtensionVar = std::string("CMAKE_") + 
    std::string(l) + std::string("_OUTPUT_EXTENSION");
  const char* outputExtension = mf->GetDefinition(outputExtensionVar.c_str());
  if(outputExtension)
    {
    m_LanguageToOutputExtension[l] = outputExtension;
    m_OutputExtensions[outputExtension] = outputExtension;
    if(outputExtension[0] == '.')
      {
      m_OutputExtensions[outputExtension+1] = outputExtension+1;
      }
    }
  
  std::string linkerPrefVar = std::string("CMAKE_") + 
    std::string(l) + std::string("_LINKER_PREFERENCE");
  const char* linkerPref = mf->GetDefinition(linkerPrefVar.c_str());
  if(!linkerPref)
    {
    linkerPref = "None";
    }
  m_LanguageToLinkerPreference[l] = linkerPref;
  
  std::string extensionsVar = std::string("CMAKE_") + 
    std::string(l) + std::string("_SOURCE_FILE_EXTENSIONS");
  std::string ignoreExtensionsVar = std::string("CMAKE_") + 
    std::string(l) + std::string("_IGNORE_EXTENSIONS");
  std::string ignoreExts = mf->GetSafeDefinition(ignoreExtensionsVar.c_str());
  std::string exts = mf->GetSafeDefinition(extensionsVar.c_str());
  std::vector<std::string> extensionList;
  cmSystemTools::ExpandListArgument(exts, extensionList);
  for(std::vector<std::string>::iterator i = extensionList.begin();
      i != extensionList.end(); ++i)
    {
    m_ExtensionToLanguage[*i] = l;
    }
  cmSystemTools::ExpandListArgument(ignoreExts, extensionList);
  for(std::vector<std::string>::iterator i = extensionList.begin();
      i != extensionList.end(); ++i)
    {
    m_IgnoreExtensions[*i] = true;
    }
  m_LanguageEnabled[l] = true;

}
bool cmGlobalGenerator::IgnoreFile(const char* l)
{
  if(this->GetLanguageFromExtension(l))
    {
    return false;
    }
  return (m_IgnoreExtensions.count(l) > 0);
}

bool cmGlobalGenerator::GetLanguageEnabled(const char* l)
{
  return (m_LanguageEnabled.count(l) > 0);
}

void cmGlobalGenerator::ClearEnabledLanguages()
{
  m_LanguageEnabled.clear();
}

void cmGlobalGenerator::Configure()
{
  // Delete any existing cmLocalGenerators
  unsigned int i;
  for (i = 0; i < m_LocalGenerators.size(); ++i)
    {
    delete m_LocalGenerators[i];
    }
  m_LocalGenerators.clear();

  // Setup relative path generation.
  this->ConfigureRelativePaths();

  // start with this directory
  cmLocalGenerator *lg = this->CreateLocalGenerator();
  m_LocalGenerators.push_back(lg);

  // set the Start directories
  lg->GetMakefile()->SetStartDirectory
    (m_CMakeInstance->GetStartDirectory());
  lg->GetMakefile()->SetStartOutputDirectory
    (m_CMakeInstance->GetStartOutputDirectory());
  lg->GetMakefile()->MakeStartDirectoriesCurrent();
  
  // now do it
  lg->Configure();
  
  // update the cache entry for the number of local generators, this is used
  // for progress
  char num[100];
  sprintf(num,"%d",static_cast<int>(m_LocalGenerators.size()));
  this->GetCMakeInstance()->AddCacheEntry
    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
     "number of local generators",
                                          cmCacheManager::INTERNAL);
