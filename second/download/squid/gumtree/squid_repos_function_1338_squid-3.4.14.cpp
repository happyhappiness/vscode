void
String::append(char const chr)
{
    char myString[2];
    myString[0]=chr;
    myString[1]='\0';
    append(myString, 1);
}