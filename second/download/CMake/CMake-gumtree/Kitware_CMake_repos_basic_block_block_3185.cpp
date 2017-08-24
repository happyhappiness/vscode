{
   if (!hasSuffix(name,oldSuffix)) return False;
   name[strlen(name)-strlen(oldSuffix)] = 0;
   strcat ( name, newSuffix );
   return True;
}