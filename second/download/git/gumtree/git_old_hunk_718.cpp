	       diffopt->file);
}

static const char **column_colors;
static unsigned short column_colors_max;

void graph_set_column_colors(const char **colors, unsigned short colors_max)
{
	column_colors = colors;
	column_colors_max = colors_max;
}

