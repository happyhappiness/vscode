 
   std::vector<torrent::BlockList*>::const_iterator itrTransfer = transferChunks.begin();
 
   while (itrTransfer != transferChunks.end() && (uint32_t)(chunk - seen) > (*itrTransfer)->index())
     itrTransfer++;
 
-  for (int y = 1; y < m_canvas->get_height() && chunk < last; ++y) {
+  for (unsigned int y = 1; y < m_canvas->height() && chunk < last; ++y) {
     m_canvas->print(0, y, "%5u ", (int)(chunk - seen));
 
     while (chunk < last) {
       chtype attr;
 
       if (bitfield->get(chunk - seen)) {
