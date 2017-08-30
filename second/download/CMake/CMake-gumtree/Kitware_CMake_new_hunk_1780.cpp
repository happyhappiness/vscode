        {

        char buffer[200];

        sprintf(buffer, "Long, Long Label; this label should be "

                "bigger than button %d",cc);

        value = new wxStaticText(panel, -1, buffer);

        sizer->Add(value, 1, wxGROW | wxALL );

        sprintf(buffer, "Button %d", cc);

