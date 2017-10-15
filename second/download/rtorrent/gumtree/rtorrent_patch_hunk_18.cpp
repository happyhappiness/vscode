 #include "config.h"
 
 #include <stdexcept>
 
+#include "core/download.h"
+#include "utils/algorithm.h"
+
 #include "canvas.h"
 #include "window_peer_list.h"
 
 namespace display {
 
-WindowPeerList::WindowPeerList(PList* l, PList::iterator* f) :
+WindowPeerList::WindowPeerList(core::Download* d, PList* l, PList::iterator* f) :
   Window(new Canvas, true),
+  m_download(d),
   m_list(l),
   m_focus(f) {
 }
 
 void
 WindowPeerList::redraw() {
-  if (utils::Timer::cache() - m_lastDraw < 1000000)
-    return;
-
-  m_lastDraw = utils::Timer::cache();
+  m_nextDraw = utils::Timer::cache().round_seconds() + 1000000;
   m_canvas->erase();
 
   int x = 2;
   int y = 0;
 
   m_canvas->print(x, y, "DNS");   x += 16;
