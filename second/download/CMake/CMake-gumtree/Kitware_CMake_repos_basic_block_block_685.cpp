{
    // Construct and print requested documentation.
    cmake hcm(cmake::RoleInternal);
    hcm.SetHomeDirectory("");
    hcm.SetHomeOutputDirectory("");
    hcm.AddCMakePaths();

    std::vector<cmDocumentationEntry> generators;
    hcm.GetGeneratorDocumentation(generators);
    doc.SetName("cmake");
    doc.SetSection("Name", cmDocumentationName);
    doc.SetSection("Usage", cmDocumentationUsage);
    doc.AppendSection("Generators", generators);
    doc.PrependSection("Options", cmDocumentationOptions);

    return (doc.PrintRequestedDocumentation(std::cout) ? 0 : 1);
  }