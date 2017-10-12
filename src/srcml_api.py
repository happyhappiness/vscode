from lxml import etree
import commands
import my_constant
import myUtil

class SrcmlApi:
    
    def __init__(self, source_file):
        self.set_file(source_file)
        self.log_functions = myUtil.retrieveLogFunction(my_constant.LOG_CALL_FILE_NAME)

    """
    @ param log location(int from 0; better not be -1)
    @ return flag about whether find log or not
    @ involve find call in given loc and set log node
    """
    def set_file(self, source_file):
        # intiate xml info
        xml_file = source_file + '.xml'
        commands.getoutput('srcml --position ' + source_file + ' -o ' + xml_file)
        self.tree = etree.parse(xml_file)
        self.root = self.tree.getroot()
        self.namespace_map = self.root.nsmap
        self.namespace_map['default'] = self.namespace_map[None]
        self.namespace_map.pop(None)
        # initiate log and control info
        self.log_node = None
        self.log = []
        self.control_node = None
        self.control = []
    """
    @ param log location(int from 0; better not be -1)
    @ return flag about whether find log or not
    @ involve find call in given loc and set log node
    """
    def set_log_loc(self, log_location):
        log_location = str(log_location + 1) # from 1
        # iterates all call
        call_nodes = self.tree.findall('//default:call', namespaces=self.namespace_map)
        for call in call_nodes:
            name = call[0]
            location = name.attrib.values()[0]
            # filter by location
            if location == log_location:
                self.log_node = call
                # get info for log node(call --name --argumentlist)
                self.log = self._get_info_for_node(self.log_node[1])
                # self.log.sort()
                return True
        return False

    """
    @ param [call after: self.set_log_loc()]
    @ return self.log
    @ involve get log info for log
    """
    def get_log_info(self):
        return self.log

    """
    @ param [call after: self.set_control_dependence()]
    @ return self.control
    @ involve get control info for log
    """
    def get_control_info(self):
        return self.control

    """
    @ param [call after: self.set_log_loc()]
    @ return true if find control dependence
    @ involve get control node for node(if/switch)
    """
    def set_control_dependence(self):
        if self.log_node is None:
            return False
        # iterator parent to find if/switch
        self.control_node = []
        parent_iter = self.log_node.iterancestors()
        for parent in parent_iter:
            tag = self._remove_prefix(parent)
            # filter by tag[if or switch]
            if tag == 'if' or tag == 'switch':
                # filter by if/switch --confition
                self.control_node.append(parent[0])
                # print self.get_text(parent[0])
                # add case for switch
                if tag == 'switch':
                    # filter by switch --condition --block ----case
                    for child in parent[1]:
                        tag = self._remove_prefix(child)
                        # filter by sibling descendants
                        if tag == 'case' and \
                    self._is_ancestor(child.getnext(), self.log_node):
                            self.control_node.append(child)
                            # print self.get_text(child)
                            break
                # get info(function, decl) for control dependence
                self.control = []
                for temp_node in self.control_node:
                    self.control += self._get_info_for_node(temp_node)
                # self.control.sort()
                # print self.control
                # single layer control analysis
                return True

        return False

    """
    @ param node()
    @ return depended info for given node(function name or variable type)
    @ involve get and analyz dependent info for given node
    """
    def _get_info_for_node(self, node):
        # filter out the one with log statement changes
        name_nodes, node_info = self._get_pure_name_nodes(node)
        for name_node in name_nodes:
            name_line = int(name_node.attrib.values()[0])
            depended_nodes = self._get_depended_nodes(name_node)
            type_info = None
            arg_info = None
            return_info = None
            # iterate from name node
            depended_lines = depended_nodes.keys()
            depended_lines.sort(key=lambda d:abs(int(d)-name_line))
            for depended_line in depended_lines:
                depended_info = depended_nodes[depended_line]
                depended_node = depended_info[0]
                depended_type = depended_info[1]
                # call --name or type --name
                info = self._remove_blank(depended_node[0])
                if info in self.log_functions:
                    continue
                # level 1
                if depended_type == my_constant.VAR_FUNC_RETURN:
                    return_info = info + my_constant.FlAG_FUNC_RETURN
                    break
                elif depended_type == my_constant.VAR_FUNC_ARG_RETURN:
                    return_info = info + my_constant.FlAG_FUNC_ARG_RETURN
                    break
                # record nearest arg and decl
                elif depended_type == my_constant.VAR_TYPE and type_info is None:
                    type_info = info + my_constant.FlAG_TYPE
                elif depended_type == my_constant.VAR_FUNC_ARG and arg_info is None:
                    arg_info = info + my_constant.FlAG_FUNC_ARG
            # return > arg > var type
            if return_info is not None:
                info = return_info
            elif arg_info is not None:
                info = arg_info
            else:
                info = type_info
            node_info.append(info)

        return node_info

    """
    @ param node(must be name)
    @ return data depended node {line, [node, depended_type]}
    @ involve get data depended nodes for given node(call, decl)
    """
    def _get_depended_nodes(self, node):
        depended_nodes = {}
        node_line = node.attrib.values()[0]
        # find all name node
        candi_nodes = self.tree.findall("//default:name", namespaces=self.namespace_map)
        is_ptr = False # mark for pointer argument
        for candi_node in candi_nodes:
            if candi_node == node or candi_node.text != node.text:
                continue
            candi_line = candi_node.attrib.values()[0]
            # find use as return or reference argument for functions
            if candi_line < node_line:
                # filter by name = call
                operator_node = candi_node.getnext()
                if operator_node is not None and self._remove_blank(operator_node) == '=':
                    func_node = operator_node.getnext()
                    if func_node is not None and self._remove_prefix(func_node) == 'call':
                        depended_nodes[candi_line] = [func_node, my_constant.VAR_FUNC_RETURN]
                        continue
                # filter by call ----argument --------& --------name
                argument_node = candi_node.getparent().getparent()
                if argument_node is not None and self._remove_prefix(argument_node) == 'argument':
                    func_node = argument_node.getparent().getparent()
                    modifier_node = candi_node.getprevious()
                    if modifier_node is not None and self._remove_blank(modifier_node) == '&':
                        depended_nodes[candi_line] = [func_node, my_constant.VAR_FUNC_ARG_RETURN]
                    # filter by call ----argument --------name(ptr)
                    elif is_ptr:
                        depended_nodes[candi_line] = [func_node, my_constant.VAR_FUNC_ARG_RETURN]
                    continue
                # filter by decl --type --name --init ----expr --call
                init_node = candi_node.getnext()
                if init_node is not None and self._remove_prefix(init_node) == 'init':
                    # mark is pointer or not
                    type_node = candi_node.getprevious()
                    is_ptr = self._is_pointer(type_node)
                    func_nodes = init_node.iterdescendants(tag='{'+self.namespace_map['default']+'}call')
                    if func_nodes is not None:
                        for func_node in func_nodes:
                            depended_nodes[candi_line] = [func_node, my_constant.VAR_FUNC_RETURN]
                            break
                        continue
                # filter by decl --type ----name ----modifier --name
                decl_node = candi_node.getparent()
                if decl_node is not None and self._remove_prefix(decl_node) == 'decl':
                    # mark is pointer or not
                    type_node = candi_node.getprevious()
                    is_ptr = self._is_pointer(type_node)
                    depended_nodes[candi_line] = [decl_node[0], my_constant.VAR_TYPE]
                    continue
            # find use as argument for functions
            else:
                # filter by call ----argument --------name
                argument_node = candi_node.getparent().getparent()
                if argument_node is not None and self._remove_prefix(argument_node) == 'argument':
                    func_node = argument_node.getparent().getparent()
                    depended_nodes[candi_line] = [func_node, my_constant.VAR_FUNC_ARG]
                    continue

        return depended_nodes


    """
    @ param node
    @ return pure name node (no median call)
    @ involve get name nodes without expanding call
    """
    def _get_pure_name_nodes(self, node):
        name_nodes = []
        name_tag = "{" + self.namespace_map['default'] + "}name"
        call_tag = "{" + self.namespace_map['default'] + "}call"
        name_descendants = node.iterdescendants(tag=name_tag)
        # validate each name descendant
        for name_node in name_descendants:
            is_valid = True
            # filter by descendant of call descendants
            for call_node in node.iterdescendants(tag=call_tag):
                if self._is_ancestor(call_node, name_node):
                    is_valid = False
                    break
            # append valid name node
            if is_valid:
                name_nodes.append(name_node)

        # add call info for call descendants
        call_info = []
        for call_node in node.iterdescendants(tag=call_tag):
            # call --name --argument list ----argument
            call_info.append(self._remove_blank(call_node[0]) + my_constant.FlAG_FUNC_RETURN)
        return name_nodes, call_info
    """
    @ param ancestor and node
    @ return true if is
    @ involve judge whether ancestor relation true
    """
    def _is_ancestor(self, ancestor, node):
        # get descendants by tag
        descendant_iter = ancestor.iterdescendants(tag=node.tag)
        for descendant in descendant_iter:
            # filter by equality
            if descendant == node:
                return True
        return False

    """
    @ param node(type)
    @ return true if is
    @ involve judge whether type has a modifier and that modifier is *
    """
    def _is_pointer(self, node):
        if node is not None and self._remove_prefix(node) == 'type':
            # type must has at least two children
            children_nodes = node.getchildren()
            if len(children_nodes) > 1:
                # filter by type --name --modifier
                modifier_node = children_nodes[1]
                if self._remove_blank(modifier_node) == '*':
                    return True
        return False


    """
    @ param node and history text
    @ return
    @ involve text for this node(children whose line is not none)
    """
    def _get_text(self, node=None):
        content = ""
        if node is None or node.prefix == 'pos':
            return content
        # if has text, add to content
        if node.text:
            content += " " + node.attrib.values()[0]+ "@"\
                         + self._remove_prefix(node) + "@" + node.text

        # add text of children
        for child in node:
            content += self._get_text(child)

        return content

    """
    @ param node
    @ return tag without prefix
    @ involve remove prefix
    """
    def _remove_prefix(self, node):
        # prefix = node.prefix
        # if prefix is None:
        #     prefix = 'default'
        # return node.tag.replace(self.namespace_map[prefix], '')
        return node.tag[node.tag.find('}') + 1:]

    """
    @ param node
    @ return text without blank
    @ involve remove blank
    """
    def _remove_blank(self, node):
        return node.text.replace(' ', '')



if __name__ == "__main__":
    # input function cpp file
    srcml_api = SrcmlApi('clang/hello.cpp')
    if srcml_api.set_log_loc(33):
        if srcml_api.set_control_dependence():
            print srcml_api.get_control_info()
            print srcml_api.get_log_info()