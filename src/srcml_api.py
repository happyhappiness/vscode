import xml.etree.ElementTree as etree
import commands

class SrcmlApi:
    
    def __init__(self, source_file, xml_file):
        commands.getoutput('srcml --position' + source_file + ' -o ' + xml_file)
        self.tree = etree.parse('clang/hello.xml')
        self.root = self.tree.getroot()

    """
    @ param node
    @ return data dependence node
    @ involve get data dependence node for node(decl_stmt, call, parameter)
    """
    def get_data_dependence(node):
        
    """
    @ param node
    @ return control node
    @ involve get control node for node(if/switch)
    """
    def get_control_dependence(node):
        
    """
    @ param node and history text
    @ return
    @ involve text for this node(children whose line is not none)
    """
    def _get_text(node, text):
        # check attrib size for print or not
        attribute = node.attrib.values()
        content = remove_prefix(node.tag)
        # do not deal with position flag
        if content == 'position':
            return
        # if has text so print
        if node.text:
            content = attribute[0]+ " " + content + " " + node.text
            text.append(content)
        print content

        # get text for children
        for child in node:
            get_text(child, text)

"""
@ param node
@ return text list
@ involve remove {....//srcml....} prefix
"""
def remove_prefix(text):
    splitter = text.find('}')
    if splitter != -1:
        return text[splitter + 1:]


if __name__ == "__main__":
    srcml_api = SrcmlApi('clang/hello.cpp', 'clang/hello.xml')
    srcml_api.get_text()
