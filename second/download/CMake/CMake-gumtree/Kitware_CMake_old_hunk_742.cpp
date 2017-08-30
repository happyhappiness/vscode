*----------------------------------------------------------------------

*/



static char sccsid[] = "@(#) winDumpExts.c 1.2 95/10/03 15:27:34";



#include <windows.h>

#include <stdio.h>

#include <string>

#include <fstream>



/*

*----------------------------------------------------------------------

* GetArgcArgv --

*

*      Break up a line into argc argv

*----------------------------------------------------------------------

*/

int

GetArgcArgv(std::string &s, char **argv)

{

   int quote = 0;

   int argc = 0;

   std::string::iterator bp = s.begin();



   while (1) {

      while (isspace(*bp)) {

         bp++;

      }

      if (*bp == '\n' || *bp == '\0') {

         *bp = '\0';

         return argc;

      }

      if (*bp == '\"') {

         quote = 1;

         bp++;

      }

      argv[argc++] = &(*bp);



      while (*bp != '\0') {

         if (quote) {

            if (*bp == '\"') {

               quote = 0;

               *bp = '\0';

               bp++;

               break;

            }

            bp++;

            continue;

         }

         if (isspace(*bp)) {

            *bp = '\0';

            bp++;

            break;

         }

         bp++;

      }

   }

}



/*

*  The names of the first group of possible symbol table storage classes

*/

char * SzStorageClass1[] = {

   "NULL","AUTOMATIC","EXTERNAL","STATIC","REGISTER","EXTERNAL_DEF","LABEL",

   "UNDEFINED_LABEL","MEMBER_OF_STRUCT","ARGUMENT","STRUCT_TAG",

   "MEMBER_OF_UNION","UNION_TAG","TYPE_DEFINITION","UNDEFINED_STATIC",

   "ENUM_TAG","MEMBER_OF_ENUM","REGISTER_PARAM","BIT_FIELD"

};



/*

* The names of the second group of possible symbol table storage classes

*/

char * SzStorageClass2[] = {

   "BLOCK","FUNCTION","END_OF_STRUCT","FILE","SECTION","WEAK_EXTERNAL"

};



/*

*----------------------------------------------------------------------

* GetSZStorageClass --

*

*      Given a symbol storage class value, return a descriptive

*      ASCII string

*----------------------------------------------------------------------

*/

PSTR

GetSZStorageClass(BYTE storageClass)

{

   if ( storageClass <= IMAGE_SYM_CLASS_BIT_FIELD )

      return SzStorageClass1[storageClass];

   else if ( (storageClass >= IMAGE_SYM_CLASS_BLOCK)

      && (storageClass <= IMAGE_SYM_CLASS_WEAK_EXTERNAL) )

      return SzStorageClass2[storageClass-IMAGE_SYM_CLASS_BLOCK];

   else

      return "???";

}



void AddHex(std::string& buf, long val, bool caps=false)

{

   buf += "0x";

   size_t len=buf.length();

   while (val) {

      char hex = (char)(val & 16);

      val = val >> 4;

      if (hex<10) hex+='0';

      else if (caps) hex+='A'-10;

      else hex+='a'-10;

      buf.insert(len, hex, 1);

   }

}



/*

*----------------------------------------------------------------------

* GetSectionName --

*

*      Used by DumpSymbolTable, it gives meaningful names to

*      the non-normal section number.

*

* Results:

*      A name is returned in buffer

*----------------------------------------------------------------------

*/

void

GetSectionName(PIMAGE_SYMBOL pSymbolTable, std::string& buffer)

{

   DWORD section;



   section = pSymbolTable->SectionNumber;



   switch ( (SHORT)section )

   {

   case IMAGE_SYM_UNDEFINED: if (pSymbolTable->Value) buffer += "COMM"; else buffer += "UNDEF"; break;

   case IMAGE_SYM_ABSOLUTE:  buffer += "ABS  "; break;

   case IMAGE_SYM_DEBUG:     buffer += "DEBUG"; break;

   default: AddHex(buffer, section, true);

   }

}



/*

*----------------------------------------------------------------------

* GetSectionCharacteristics --

*

*      Converts the Characteristics field of IMAGE_SECTION_HEADER

*      to print.

*

*  Results:

*       A definiton of the section symbol type

*----------------------------------------------------------------------

*/

void

GetSectionCharacteristics(PIMAGE_SECTION_HEADER pSectionHeaders, int nSectNum, std::string &buffer)

{

   DWORD SectChar;

   std::string TempBuf;

   buffer.clear();

   if (nSectNum > 0) {

      SectChar = pSectionHeaders[nSectNum-1].Characteristics;



      buffer = " ";

      AddHex(buffer, SectChar);

      if       (SectChar & IMAGE_SCN_CNT_CODE)                buffer += " Code";

      else if  (SectChar & IMAGE_SCN_CNT_INITIALIZED_DATA)    buffer += " Init. data";

      else if  (SectChar & IMAGE_SCN_CNT_UNINITIALIZED_DATA ) buffer += " UnInit data";

      else                                                    buffer += " Unknow type";



      if   (SectChar & IMAGE_SCN_MEM_READ)  {

         buffer += " Read";

         if (SectChar & IMAGE_SCN_MEM_WRITE)

            buffer += " and Write";

         else buffer += " only";

      }

      else if (SectChar & IMAGE_SCN_MEM_WRITE)

         buffer +=" Write only";



   }

}



/*

*----------------------------------------------------------------------

* DumpSymbolTable --

*

*      Dumps a COFF symbol table from an EXE or OBJ.  We only use

*      it to dump tables from OBJs.

*----------------------------------------------------------------------

*/

void

DumpSymbolTable(PIMAGE_SYMBOL pSymbolTable, PIMAGE_SECTION_HEADER pSectionHeaders, FILE *fout, unsigned cSymbols)

{

   unsigned i;

   PSTR stringTable;

   std::string sectionName;

   std::string sectionCharacter;

   int iSectNum;



   fprintf(fout, "Symbol Table - %X entries  (* = auxillary symbol)\n",

      cSymbols);



   fprintf(fout,

      "Indx Name                 Value    Section    cAux  Type    Storage  Character\n"

      "---- -------------------- -------- ---------- ----- ------- -------- ---------\n");



   /*

   * The string table apparently starts right after the symbol table

   */

   stringTable = (PSTR)&pSymbolTable[cSymbols];



   for ( i=0; i < cSymbols; i++ ) {

      fprintf(fout, "%04X ", i);

      if ( pSymbolTable->N.Name.Short != 0 )

         fprintf(fout, "%-20.8s", pSymbolTable->N.ShortName);

      else

         fprintf(fout, "%-20s", stringTable + pSymbolTable->N.Name.Long);



      fprintf(fout, " %08X", pSymbolTable->Value);



      iSectNum = pSymbolTable->SectionNumber;

      GetSectionName(pSymbolTable, sectionName);

      fprintf(fout, " sect:%s aux:%X type:%02X st:%s",

         sectionName.c_str(),

         pSymbolTable->NumberOfAuxSymbols,

         pSymbolTable->Type,

         GetSZStorageClass(pSymbolTable->StorageClass) );



      GetSectionCharacteristics(pSectionHeaders,iSectNum,sectionCharacter);

      fprintf(fout," hc: %s \n",sectionCharacter.c_str());

#if 0

      if ( pSymbolTable->NumberOfAuxSymbols )

         DumpAuxSymbols(pSymbolTable);

#endif



      /*

      * Take into account any aux symbols

      */

      i += pSymbolTable->NumberOfAuxSymbols;

      pSymbolTable += pSymbolTable->NumberOfAuxSymbols;

      pSymbolTable++;

   }

}



/*

*----------------------------------------------------------------------

* DumpExternals --

*

*      Dumps a COFF symbol table from an EXE or OBJ.  We only use

*      it to dump tables from OBJs.

*----------------------------------------------------------------------

*/

void

DumpExternals(PIMAGE_SYMBOL pSymbolTable, FILE *fout, unsigned cSymbols)

{

   unsigned i;

   PSTR stringTable;

   std::string symbol;



   /*

   * The string table apparently starts right after the symbol table

   */

   stringTable = (PSTR)&pSymbolTable[cSymbols];



   for ( i=0; i < cSymbols; i++ ) {

      if (pSymbolTable->SectionNumber > 0 && pSymbolTable->Type == 0x20) {

         if (pSymbolTable->StorageClass == IMAGE_SYM_CLASS_EXTERNAL) {

            if (pSymbolTable->N.Name.Short != 0) {

               symbol = "";

               symbol.insert(0, (const char *)(pSymbolTable->N.ShortName), 8);

            } else {

               symbol = stringTable + pSymbolTable->N.Name.Long;

            }

            std::string::size_type posAt = symbol.find('@');

            if (posAt != std::string::npos) symbol.erase(posAt);

#ifndef _MSC_VER

            fprintf(fout, "\t%s\n", symbol.c_str());

#else

            fprintf(fout, "\t%s\n", symbol.c_str()+1);

#endif

         }

      }



      /*

      * Take into account any aux symbols

      */

      i += pSymbolTable->NumberOfAuxSymbols;

      pSymbolTable += pSymbolTable->NumberOfAuxSymbols;

      pSymbolTable++;

   }

}



/*

+ * Utility func, strstr with size

+ */

const char* StrNStr(const char* start, const char* find, size_t &size) {

