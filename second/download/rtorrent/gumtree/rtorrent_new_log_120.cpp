m_canvas->print(84, pos, "%i - %i",
		    e.chunk_begin(),
		    e.chunk_begin() != e.chunk_end() ? (e.chunk_end() - 1) : e.chunk_end());