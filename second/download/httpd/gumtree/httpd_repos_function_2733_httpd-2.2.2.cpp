int XML_GetCurrentColumnNumber(XML_Parser parser)
{
  if (eventPtr) {
    XmlUpdatePosition(encoding, positionPtr, eventPtr, &position);
    positionPtr = eventPtr;
  }
  return position.columnNumber;
}