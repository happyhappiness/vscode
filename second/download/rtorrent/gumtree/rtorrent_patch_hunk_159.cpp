 
 #include "window_download_chunks_seen.h"
 
 namespace display {
 
 WindowDownloadChunksSeen::WindowDownloadChunksSeen(core::Download* d, unsigned int *focus) :
-  Window(new Canvas, true),
+  Window(new Canvas, 0, 0, 0, extent_full, extent_full),
   m_download(d),
   m_focus(focus) {
 }
 
 void
 WindowDownloadChunksSeen::redraw() {
   // TODO: Make this depend on tracker signal.
   m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
   m_canvas->erase();
 
-  if (m_canvas->get_height() < 3 || m_canvas->get_width() < 18)
+  if (m_canvas->height() < 3 || m_canvas->width() < 18)
     return;
 
   m_canvas->print(2, 0, "Chunks seen: [C/A/D %i/%i/%.2f]",
                   (int)m_download->download()->peers_complete(),
                   (int)m_download->download()->peers_accounted(),
                   std::floor(m_download->distributed_copies() * 100.0f) / 100.0f);
