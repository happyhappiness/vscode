void
String::append (char chr)
{
    char myString[2];
    myString[0]=chr;
    myString[1]='\0';
    append (myString, 1);
}