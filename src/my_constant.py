#-*-coding: utf-8 -*-
"""
@ involve : constant definition
"""

"""
repository
"""
REPOS = 'curl'
"""
stroed file name prefix
"""
# parent
BASE_DIR = '/usr/info/code/cpp/LogMonitor/LogMonitor'
CURR_REPOS_DIR = BASE_DIR + '/second/download/' + REPOS + '/'
# patch dir
PATCH_DIR = CURR_REPOS_DIR + 'patch/'
# repos
REPOS_DIR = CURR_REPOS_DIR + 'repos/'
# gumtree dir(hunk, block, function)
GUMTREE_DIR = CURR_REPOS_DIR + 'gumtree/'
# hunk
DOWNLOAD_PATCH_HUNK = GUMTREE_DIR + REPOS + '_patch_hunk_'
DOWNLOAD_OLD_HUNK = GUMTREE_DIR + REPOS + '_old_hunk_'
DOWNLOAD_NEW_HUNK = GUMTREE_DIR + REPOS + '_new_hunk_'
# log
SAVE_OLD_LOG = GUMTREE_DIR + REPOS + '_old_log_'
SAVE_NEW_LOG = GUMTREE_DIR + REPOS + '_new_log_'
# function
SAVE_FUNCTION = GUMTREE_DIR + REPOS + '_function_'
SAVE_REPOS_FUNCTION = GUMTREE_DIR + REPOS + '_repos_function_'

"""
file name
"""
LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + REPOS + '_func_similarity.csv'
FETCH_HUNK_FILE_NAME = 'data/fetch/' + REPOS + '_hunk_fetch.csv'
FETCH_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_log_fetch.csv'
ANALYZE_OLD_NEW_GUMTREE_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_gumtree_analyze.csv'
ANALYZE_OLD_NEW_LLVM_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_llvm_analyze.csv'
CLUSTER_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_feature.csv'
CLUSTER_EDITION_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_edition.csv'
CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_edition_and_feature.csv'
CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_class_edition_and_feature.csv'
# clone
ANALYZE_CLONE_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_log_seek_clone.csv'
ANALYZE_CLONE_FUNCTION_FILE_NAME = 'data/fetch/' + REPOS + '_repos_function_seek_clone.csv'

# repos
CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + REPOS + '_repos_cluster.csv'
ANALYZE_REPOS_FUNCTION_FILE_NAME = 'data/fetch/' + REPOS + '_repos_call.csv'
ANALYZE_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_log.csv'
CLUSTER_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_cluster_log.csv'
CLASS_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_class_log.csv'

"""
fetch hunk file title and index
"""
FETCH_HUNK_TITLE = ['patch_file', 'old_file', 'new_file', 'patch_hunk_file','old_hunk_file', 'new_hunk_file', \
    'old_hunk_loc', 'new_hunk_loc', 'old_log_loc', 'new_log_loc']
FETCH_HUNK_OLD_HUNK_LOC = FETCH_HUNK_TITLE.index('old_hunk_loc')
FETCH_HUNK_NEW_HUNK_LOC = FETCH_HUNK_TITLE.index('new_hunk_loc')
FETCH_HUNK_OLD_LOG_LOC = FETCH_HUNK_TITLE.index('old_log_loc')
FETCH_HUNK_NEW_LOG_LOC = FETCH_HUNK_TITLE.index('new_log_loc')
FETCH_HUNK_OLD_HUNK_FILE = FETCH_HUNK_TITLE.index('old_hunk_file')
FETCH_HUNK_NEW_HUNK_FILE = FETCH_HUNK_TITLE.index('new_hunk_file')

"""
fetch log file title and index
"""
FETCH_LOG_TITLE = ['patch_file', 'old_file', 'new_file', 'patch_hunk_file', 'old_hunk_file', 'new_hunk_file', \
  'old_hunk_loc', 'new_hunk_loc', 'old_loc', 'new_loc', 'old_log', 'new_log', 'action_type']
FETCH_LOG_OLD_LOC = FETCH_LOG_TITLE.index('old_loc')
FETCH_LOG_NEW_LOC = FETCH_LOG_TITLE.index('new_loc')
FETCH_LOG_OLD_LOG = FETCH_LOG_TITLE.index('old_log')
FETCH_LOG_NEW_LOG = FETCH_LOG_TITLE.index('new_log')
FETCH_LOG_OLD_FILE = FETCH_LOG_TITLE.index('old_file')
FETCH_LOG_NEW_FILE = FETCH_LOG_TITLE.index('new_file')
FETCH_LOG_ACTION_TYPE = FETCH_LOG_TITLE.index('action_type')

"""
analyze old new title and index
"""
# 'old_block', 'old_block_file', 'old_block_feature',
ANALYZE_OLD_NEW_GUMTREE_TITLE = FETCH_LOG_TITLE + ['old_log_file', 'new_log_file', 'function', 'function_loc', 'edit_types', 'edit_words', 'edit_feature']
ANALYZE_EDIT_TYPE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('edit_types')
ANALYZE_EDIT_WORD = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('edit_words')
ANALYZE_EDIT_FEATURE = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('edit_feature')
ANALYZE_FUNCTION = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('function')
ANALYZE_FUNCTION_LOC = ANALYZE_OLD_NEW_GUMTREE_TITLE.index('function_loc')

ANALYZE_OLD_NEW_LLVM_TITLE = ANALYZE_OLD_NEW_GUMTREE_TITLE + ['check', 'variable', 'ddg_codes', 'ddg_locs']
ANALYZE_CHECK = ANALYZE_OLD_NEW_LLVM_TITLE.index('check')
ANALYZE_VARIABLE = ANALYZE_OLD_NEW_LLVM_TITLE.index('variable')
# cluster and class
CLUSTER_OLD_NEW_TITLE = ANALYZE_OLD_NEW_LLVM_TITLE + ['cluster']
ANALYZE_CLUSTER = CLUSTER_OLD_NEW_TITLE.index('cluster')
CLASS_OLD_NEW_TITLE = ['class', 'old_loc', 'old_log', 'new_log', 'check', 'variable', 'edit']
CLASS_OLD_NEW_OLD_LOC = CLASS_OLD_NEW_TITLE.index('old_loc')
CLASS_OLD_NEW_CHECK = CLASS_OLD_NEW_TITLE.index('check')
CLASS_OLD_NEW_VARIABLE = CLASS_OLD_NEW_TITLE.index('variable')
CLASS_OLD_NEW_EDIT = CLASS_OLD_NEW_TITLE.index('edit')

"""
analyze repos log title and index
"""
#'block', 'block_file', 'block_feature',
ANALYZE_REPOS_LOG_TITLE = ['file', 'function', \
                             'loc','log', 'check', 'variable']
ANALYZE_REPOS_LOG_FUNCTION = ANALYZE_REPOS_LOG_TITLE.index('function')
ANALYZE_REPOS_LOG_LOC = ANALYZE_REPOS_LOG_TITLE.index('loc')
ANALYZE_REPOS_LOG_CHECK = ANALYZE_REPOS_LOG_TITLE.index('check')
ANALYZE_REPOS_LOG_VARIABLE = ANALYZE_REPOS_LOG_TITLE.index('variable')

"""
analyze repos function title and index
"""
ANALYZE_REPOS_FUNCTION_TITLE =['file', 'function','calls', 'types']
ANALYZE_REPOS_FUNCTION_CALLS = ANALYZE_REPOS_FUNCTION_TITLE.index('calls')
ANALYZE_REPOS_FUNCTION_TYPES = ANALYZE_REPOS_FUNCTION_TITLE.index('types')
# cluster and class
CLUSTER_REPOS_LOG_TITLE = ANALYZE_REPOS_LOG_TITLE + ['cluster']
ANALYZE_REPOS_LOG_CLUSTER = CLUSTER_REPOS_LOG_TITLE.index('cluster')
CLASS_REPOS_LOG_TITLE = ['class', 'check', 'variable']
CLASS_REPOS_LOG_CHECK = CLASS_REPOS_LOG_TITLE.index('check')
CLASS_REPOS_LOG_VARIABLE = CLASS_REPOS_LOG_TITLE.index('variable')


"""
analyze clone title
"""
ANALYZE_CLONE_LOG_TITLE = CLASS_OLD_NEW_TITLE + CLUSTER_REPOS_LOG_TITLE
ANALYZE_CLONE_FUNCTION_TITLE = CLASS_OLD_NEW_TITLE + ANALYZE_REPOS_FUNCTION_TITLE

"""
flag type && log type
"""
LOG_FEATURE_MODIFY = 4
LOG_OTHER_LOG_FEATURE_MODIFY = 6
LOG_OTHER_LOG_MODIFY = 2
LOG_NO_MODIFY = 0
LOG_LOG_MODIFY = 3
LOG_LOG_FEATURE_MODIFY = 7

"""
log edit type info
"""
LOD_EDIT_TYPES = ["addLog", "removeLog", "updateLog", "addVariable", "removeVariable",\
          "updateVariable", "moveVariable", "addContent", "removeContent",\
          "updateContent", "moveContent"]

"""
data dependence type
"""
# level 1
VAR_FUNC_RETURN = 0
FlAG_FUNC_RETURN = '_ret'
# level 2
VAR_FUNC_ARG_RETURN = 1
FlAG_FUNC_ARG_RETURN = '_arg_ret'
# level 3
VAR_FUNC_ARG = 3
FlAG_FUNC_ARG = '_arg'
# level 4
VAR_TYPE = 4
FlAG_TYPE = ''

"""
split string for statement to get tokens
"""
SPLIT_STR = r'[\W\s_]'
SPLIT_ALGORITHM = r'[+-\*/%=]'

CPP_FILE_FORMAT = r'\.(c|cpp|cc|cxx|h)$'
UNSRCML_FILE_FORMAT = r'\.(h|c|cc|cxx)$'

"""
class path for java
"""
# GUMTREE_HOME = '/opt/gumtree/dist/build/distributions/gumtree-20170722-2.1.0-SNAPSHOT'
GUMTREE_HOME = '/opt/gumtree/gumtree/dist/build/distributions/gumtree-20170703-2.1.0-SNAPSHOT'
JAVA_CLASS_PATH = '.:/usr/info/code/cpp/LogMonitor/LogMonitor/java:' + GUMTREE_HOME + '/lib/annotations-2.0.1.jar:' + GUMTREE_HOME + '/lib/antlr-3.5.2.jar:' + GUMTREE_HOME + '/lib/antlr-runtime-3.5.2.jar:' + GUMTREE_HOME + '/lib/aopalliance-1.0.jar:' + GUMTREE_HOME + '/lib/app-1.3.200-v20130910-1609.jar:' + GUMTREE_HOME + '/lib/asm-3.1.jar:' + GUMTREE_HOME + '/lib/cglib-2.2.1-v20090111.jar:' + GUMTREE_HOME + '/lib/client.diff-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/client-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/common-3.6.200-v20130402-1505.jar:' + GUMTREE_HOME + '/lib/commons-codec-1.10.jar:' + GUMTREE_HOME + '/lib/commons-io-2.0.1.jar:' + GUMTREE_HOME + '/lib/commons-lang3-3.1.jar:' + GUMTREE_HOME + '/lib/commons-logging-1.2.jar:' + GUMTREE_HOME + '/lib/contenttype-3.4.200-v20140207-1251.jar:' + GUMTREE_HOME + '/lib/core-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-antlr-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-json-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-php-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-r-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.antlr3-xml-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.c-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.css-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.jdt-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.js-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.ruby-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gen.srcml-2.1.0-SNAPSHOT.jar:' + GUMTREE_HOME + '/lib/gson-2.4.jar:' + GUMTREE_HOME + '/lib/guava-18.0.jar:' + GUMTREE_HOME + '/lib/guice-3.0.jar:' + GUMTREE_HOME + '/lib/javassist-3.18.2-GA.jar:' + GUMTREE_HOME + '/lib/javax.inject-1.jar:' + GUMTREE_HOME + '/lib/javax.servlet-api-3.1.0.jar:' + GUMTREE_HOME + '/lib/jetty-http-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-io-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-security-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-server-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-servlet-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-util-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-webapp-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jetty-xml-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/jobs-3.6.0-v20140424-0053.jar:' + GUMTREE_HOME + '/lib/jrubyparser-0.5.3.jar:' + GUMTREE_HOME + '/lib/jsr305-3.0.1.jar:' + GUMTREE_HOME + '/lib/jtidy-r938.jar:' + GUMTREE_HOME + '/lib/junit-4.8.2.jar:' + GUMTREE_HOME + '/lib/org.eclipse.core.resources-3.10.0.v20150423-0755.jar:' + GUMTREE_HOME + '/lib/org.eclipse.jdt.core-3.11.0.v20150602-1242.jar:' + GUMTREE_HOME + '/lib/osgi-3.10.0-v20140606-1445.jar:' + GUMTREE_HOME + '/lib/ph-commons-8.3.0.jar:' + GUMTREE_HOME + '/lib/ph-css-5.0.1.jar:' + GUMTREE_HOME + '/lib/preferences-3.5.200-v20140224-1527.jar:' + GUMTREE_HOME + '/lib/reflections-0.9.10.jar:' + GUMTREE_HOME + '/lib/registry-3.5.400-v20140428-1507.jar:' + GUMTREE_HOME + '/lib/rendersnake-1.9.0.jar:' + GUMTREE_HOME + '/lib/rhino-1.7.7.jar:' + GUMTREE_HOME + '/lib/runtime-3.10.0-v20140318-2214.jar:' + GUMTREE_HOME + '/lib/simmetrics-core-3.2.3.jar:' + GUMTREE_HOME + '/lib/slf4j-api-1.7.21.jar:' + GUMTREE_HOME + '/lib/spark-core-2.5.2.jar:' + GUMTREE_HOME + '/lib/spring-aop-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-beans-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-context-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-core-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-expression-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-web-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/spring-webmvc-4.1.6.RELEASE.jar:' + GUMTREE_HOME + '/lib/ST4-4.0.8.jar:' + GUMTREE_HOME + '/lib/trove4j-3.0.3.jar:' + GUMTREE_HOME + '/lib/websocket-api-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-client-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-common-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-server-9.3.6.v20151106.jar:' + GUMTREE_HOME + '/lib/websocket-servlet-9.3.6.v20151106.jar'

def reset_repos(new_repos):
    """
    @ param new repository\n
    @ return nothing \n
    @ involve reset my_constant repos variable and related variable\n
    """
    global REPOS
    REPOS = new_repos
    """
    stroed file name prefix
    """
    # parent
    global BASE_DIR
    BASE_DIR = '/usr/info/code/cpp/LogMonitor/LogMonitor'
    global CURR_REPOS_DIR
    CURR_REPOS_DIR = BASE_DIR + '/second/download/' + REPOS + '/'
    # patch dir
    global PATCH_DIR
    PATCH_DIR = CURR_REPOS_DIR + 'patch/'
    # repos
    global REPOS_DIR
    REPOS_DIR = CURR_REPOS_DIR + 'repos/'
    # gumtree dir(hunk, block, function)
    global GUMTREE_DIR
    GUMTREE_DIR = CURR_REPOS_DIR + 'gumtree/'
    # hunk
    global DOWNLOAD_PATCH_HUNK
    DOWNLOAD_PATCH_HUNK = GUMTREE_DIR + REPOS + '_patch_hunk_'
    global DOWNLOAD_OLD_HUNK
    DOWNLOAD_OLD_HUNK = GUMTREE_DIR + REPOS + '_old_hunk_'
    global DOWNLOAD_NEW_HUNK
    DOWNLOAD_NEW_HUNK = GUMTREE_DIR + REPOS + '_new_hunk_'
    # log
    global SAVE_OLD_LOG
    SAVE_OLD_LOG = GUMTREE_DIR + REPOS + '_old_log_'
    global SAVE_NEW_LOG
    SAVE_NEW_LOG = GUMTREE_DIR + REPOS + '_new_log_'
    # function
    global SAVE_FUNCTION
    SAVE_FUNCTION = GUMTREE_DIR + REPOS + '_function_'
    global SAVE_REPOS_FUNCTION
    SAVE_REPOS_FUNCTION = GUMTREE_DIR + REPOS + '_repos_function_'

    """
    file name
    """
    global LOG_CALL_FILE_NAME
    LOG_CALL_FILE_NAME = 'data/fetch/' + REPOS + '_logging_statement.csv'
    global FUNC_SIMILAIRTY_FILE_NAME
    FUNC_SIMILAIRTY_FILE_NAME = 'data/fetch/' + REPOS + '_func_similarity.csv'
    global FETCH_HUNK_FILE_NAME
    FETCH_HUNK_FILE_NAME = 'data/fetch/' + REPOS + '_hunk_fetch.csv'
    global FETCH_LOG_FILE_NAME
    FETCH_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_log_fetch.csv'
    global ANALYZE_OLD_NEW_GUMTREE_FILE_NAME
    ANALYZE_OLD_NEW_GUMTREE_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_gumtree_analyze.csv'
    global ANALYZE_OLD_NEW_LLVM_FILE_NAME
    ANALYZE_OLD_NEW_LLVM_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_llvm_analyze.csv'
    global CLUSTER_FEATURE_OLD_NEW_FILE_NAME
    CLUSTER_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_feature.csv'
    global CLUSTER_EDITION_OLD_NEW_FILE_NAME
    CLUSTER_EDITION_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_edition.csv'
    global CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    CLUSTER_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_cluster_edition_and_feature.csv'
    global CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME
    CLASS_EDITION_AND_FEATURE_OLD_NEW_FILE_NAME = 'data/fetch/' + REPOS + '_old_new_class_edition_and_feature.csv'
    # clone
    global ANALYZE_CLONE_LOG_FILE_NAME
    ANALYZE_CLONE_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_log_seek_clone.csv'
    global ANALYZE_CLONE_FUNCTION_FILE_NAME
    ANALYZE_CLONE_FUNCTION_FILE_NAME = 'data/fetch/' + REPOS + '_repos_function_seek_clone.csv'

    # repos
    global CLUSTER_REPOS_FILE_NAME
    CLUSTER_REPOS_FILE_NAME = 'data/fetch/' + REPOS + '_repos_cluster.csv'
    global ANALYZE_REPOS_FUNCTION_FILE_NAME
    ANALYZE_REPOS_FUNCTION_FILE_NAME = 'data/fetch/' + REPOS + '_repos_call.csv'
    global ANALYZE_REPOS_LOG_FILE_NAME
    ANALYZE_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_log.csv'
    global CLUSTER_REPOS_LOG_FILE_NAME
    CLUSTER_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_cluster_log.csv'
    global CLASS_REPOS_LOG_FILE_NAME
    CLASS_REPOS_LOG_FILE_NAME = 'data/fetch/' + REPOS + '_repos_class_log.csv'
