m_canvas->print(84, pos, "%i - %i %c%c",
		    e.chunk_begin(),
		    e.chunk_begin() != e.chunk_end() ? (e.chunk_end() - 1) : e.chunk_end(),
		    e.is_created() ? 'E' : 'M',
		    e.is_correct_size() ? 'C' : 'W');