core::View*
DownloadList::current_view() {
  return dynamic_cast<ElementDownloadList*>(m_uiArray[DISPLAY_DOWNLOAD_LIST])->view();
}