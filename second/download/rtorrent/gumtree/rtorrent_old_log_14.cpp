m_canvas->print(0, y++, "Chunks: %u / %u * %u",
		  m_download->get_download().get_chunks_done(),
		  m_download->get_download().get_chunks_total(),
		  m_download->get_download().get_chunks_size());