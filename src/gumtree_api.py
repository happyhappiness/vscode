#-*-coding: utf-8 -*-
from jpype import *
import my_constant
import myUtil
import re

class Gumtree:  
    gumtree = None

    def __init__(self, class_name='gumtree.GumTreeApi'):
        if Gumtree.gumtree is None:
            # class path
            jvm_arg = "-Djava.class.path=" + my_constant.JAVA_CLASS_PATH
            startJVM(getDefaultJVMPath(), '-d64', jvm_arg)
            # initial class and object
            GumtreeApi = JClass(class_name)
            Gumtree.gumtree = GumtreeApi()

    """
    @ param old and new file\n
    @ return\n
    @ involve set old and new file\n
    """
    def set_old_new_file(self, old_file, new_file):
        Gumtree.gumtree.setOldAndNewFile(old_file, new_file)

    """
    @ param line\n
    @ return flag about whether find old log\n
    @ involve set line for gumtree object\n
    """
    def set_old_loc(self, line):
        return Gumtree.gumtree.setOldLoc(line)

    """
    @ param \n
    @ return line\n
    @ involve get mapping line of old log\n
    """
    def get_new_loc(self):
        return Gumtree.gumtree.getNewLoc()

    """
    @ param \n
    @ return new log\n
    @ involve get mapping log of old log\n
    """
    def get_new_log(self):
        new_log = Gumtree.gumtree.getNewLog()
        if new_log is not None:
            return new_log + ';'
        else:
            return new_log
    """
    @ param \n
    @ return old log\n
    @ involve get old log\n
    """
    def get_old_log(self):
        return Gumtree.gumtree.getOldLog() + ';'
      
    """
    @ param \n
    @ return\n
    @ involve judge if log in old location has been edited\n
    """
    def is_old_log_edited(self):
        return Gumtree.gumtree.isOldLogEdited()

    """
    @ param line\n
    @ return flag about whether find new log\n
    @ involve set line for inserted node\n
    """
    def set_new_loc(self, line):
        return Gumtree.gumtree.setNewLoc(line)

    """
    @ param \n
    @ return line\n
    @ involve get old loc for the inserted node\n
    """
    def get_old_loc(self):
        return Gumtree.gumtree.getOldLoc()

    """
    @ param old log locations\n
    @ return\n
    @ involve add log node into log nodes\n
    """
    def add_old_log_nodes(self, lines):
        for line in lines:
            Gumtree.gumtree.addOldLogNode(line)

    """
    @ param new log locations\n
    @ return\n
    @ involve add log node into log nodes\n
    """
    def add_new_log_nodes(self, lines):
        for line in lines:
            Gumtree.gumtree.addNewLogNode(line)

    """
    @ param \n
    @ return\n
    @ involve get action type for hunk\n
    """
    def get_hunk_edited_type(self):
        return Gumtree.gumtree.getActionType()

    """
    @ param ddg locations(index from 0)\n
    @ return\n
    @ involve get action type for function\n
    """
    def get_function_edited_type(self, ddg_locs):
        for ddg_loc in ddg_locs:
            Gumtree.gumtree.addDDGNode(ddg_loc)
        return Gumtree.gumtree.isDDGModified()

    """
    @ param none(set old file and new file before)\n
    @ return\n
    @ involve get edtion type of log\n
    """
    def get_log_edited_type(self):
        return list(Gumtree.gumtree.getLogEditType())

    """
    @ param filename\n
    @ return\n
    @ involve set file\n
    """
    def set_file(self, filename):
        Gumtree.gumtree.setFile(filename)

    """
    @ param line(int)\n
    @ return flag about whether success\n
    @ involve set loccation of log\n
    """
    def set_loc(self, line):
        return Gumtree.gumtree.setLoc(line)

    """
    @ param\n
    @ return\n
    @ involve get log statement\n
    """
    def get_log(self):
        return Gumtree.gumtree.getLog() + ';'

    """
    @ param\n
    @ return\n
    @ involve get block which contains log\n
    """
    def get_block(self):
        return Gumtree.gumtree.getBlock()

    """
    @ param\n
    @ return\n
    @ involve get block which contains log\n
    """
    def get_function(self):
        return Gumtree.gumtree.getFunction()

    """
    @ param\n
    @ return\n
    @ involve get block which contains log\n
    """
    def get_function_loc(self):
        return Gumtree.gumtree.getFunctionLoc()

    """
    @ param\n
    @ return\n
    @ involve get feature vector for block[type vs frequence]\n
    """
    def get_block_feature(self):
        vector_str = Gumtree.gumtree.getBlockFeature()
        vector = vector_str[1:-1].split(",")
        vector = [int(i) for i in vector]
        return vector

    """
    @ param\n
    @ return\n
    @ involve get type vector of block\n
    """
    def get_block_type(self):
        return Gumtree.gumtree.getBlockType()
    """
    @ param old and new log file\n
    @ return flag about match or not\n
    @ involve just update action\n
    """
    def is_match(self, old_log_file, new_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        return Gumtree.gumtree.isMatch()

    """
    @ param old and new log file, and repos log file\n
    @ return flag about match or not\n
    @ involve no action allowed in edited node\n
    """
    def is_match_with_edit(self, old_log_file, new_log_file, repos_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        Gumtree.gumtree.getEditedNodes()
        return Gumtree.gumtree.isMatchWithEdit(repos_log_file)

    """
    @ param old and new log file\n
    @ return list of edited word pair\n
    @ involve ast node edition -> word edition(literal split with space)\n
    """
    def get_word_edit(self, old_log_file, new_log_file):
        Gumtree.gumtree.setOldAndNewFile(old_log_file, new_log_file)
        edit_elements = list(Gumtree.gumtree.getWordEdit())
        edit_words = []
        edit_feature = []
        for edit_element in edit_elements:
            old_element = edit_element[0]
            new_element = edit_element[1]
            edit_words.append([old_element, new_element])
            edit_feature.append(abs(hash(new_element.lower()) - hash(old_element.lower())))

        return edit_words, edit_feature

    """
    @ param old and new log\n
    @ return list of edited word pair\n
    @ involve ast node edition -> word edition(literal split with space)\n
    """
    def get_word_edit_from_log(self, old_log, new_log):

        # split to get list of words
        log_spliter = r'[^\w%&/\[\]\*\\]'
        old_log = myUtil.remove_given_element('', re.split(log_spliter, old_log))
        new_log = myUtil.remove_given_element('', re.split(log_spliter, new_log))
        # print old_log
        # print new_log
        # get edition(match and compute delta)
        edit_words = []
        edit_feature = []
        is_continue = True
        # stop if can not find new exact match
        while is_continue:
            is_continue = False
            for old_element in old_log:
                # exact match and remove both
                if old_element in new_log:
                    new_log.remove(old_element)
                    old_log.remove(old_element)
                    is_continue = True
                    break
        edit_words.append(old_log)
        edit_words.append(new_log)
        old_feature = 0
        for old_element in old_log:
            old_feature += hash(old_element.lower())
        new_feature = 0
        for new_element in new_log:
            new_feature += hash(new_element.lower())
        edit_feature.append(new_feature - old_feature)
        return edit_words, edit_feature

"""
@ param \n
@ return\n
@ involve close jvm\n
"""
def close_jvm():
    shutdownJVM()


"""
main function
"""
if __name__ == "__main__":
    old_file = 'second/gumtree/c/old.cpp'
    new_file = 'second/gumtree/c/new.cpp'
    gumtree = Gumtree()
    gumtree.set_old_new_file(old_file, new_file)
    print gumtree.get_log_edited_type()
    # gumtree.set_old_loc(7)
    # gumtree.get_new_log()
    # gumtree.get_word_edit_from_log('archive_string_sprintf(a_estr, errstr, path);', 'archive_string_sprintf(a_estr, "%s%s", errstr, path);')



  