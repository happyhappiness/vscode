; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_mtree.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_rb_tree_ops = type { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, i8*)* }
%struct.archive_rb_node = type { [2 x %struct.archive_rb_node*], i64 }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.mtree_writer = type { %struct.mtree_entry*, %struct.mtree_entry*, %struct.mtree_entry*, %struct.archive_string, %struct.mtree_chain, %struct.archive_string, %struct.archive_string, i32, i64, %struct.anon, %struct.att_counter_set, i32, i32, i32, i32, i64, i32, i32, i32, i32 }
%struct.mtree_entry = type { %struct.archive_rb_node, %struct.mtree_entry*, %struct.mtree_entry*, %struct.dir_info*, %struct.reg_info*, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, i32, i32, i32, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64 }
%struct.dir_info = type { %struct.archive_rb_tree, %struct.mtree_chain, %struct.mtree_entry*, i32 }
%struct.archive_rb_tree = type { %struct.archive_rb_node*, %struct.archive_rb_tree_ops* }
%struct.reg_info = type { i32, i32 }
%struct.mtree_chain = type { %struct.mtree_entry*, %struct.mtree_entry** }
%struct.anon = type { i32, i32, i32, i64, i64, i32, i64, i64 }
%struct.att_counter_set = type { %struct.attr_counter*, %struct.attr_counter*, %struct.attr_counter*, %struct.attr_counter* }
%struct.attr_counter = type { %struct.attr_counter*, %struct.attr_counter*, %struct.mtree_entry*, i32 }

@.str = private unnamed_addr constant [31 x i8] c"archive_write_set_format_mtree\00", align 1
@.str.1 = private unnamed_addr constant [39 x i8] c"archive_write_set_format_mtree_classic\00", align 1
@.str.2 = private unnamed_addr constant [26 x i8] c"Can't allocate mtree data\00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"mtree\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"all\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"cksum\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"device\00", align 1
@.str.7 = private unnamed_addr constant [8 x i8] c"dironly\00", align 1
@.str.8 = private unnamed_addr constant [6 x i8] c"flags\00", align 1
@.str.9 = private unnamed_addr constant [4 x i8] c"gid\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"gname\00", align 1
@.str.11 = private unnamed_addr constant [7 x i8] c"indent\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"inode\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"link\00", align 1
@.str.14 = private unnamed_addr constant [4 x i8] c"md5\00", align 1
@.str.15 = private unnamed_addr constant [10 x i8] c"md5digest\00", align 1
@.str.16 = private unnamed_addr constant [5 x i8] c"mode\00", align 1
@.str.17 = private unnamed_addr constant [6 x i8] c"nlink\00", align 1
@.str.18 = private unnamed_addr constant [10 x i8] c"resdevice\00", align 1
@.str.19 = private unnamed_addr constant [16 x i8] c"ripemd160digest\00", align 1
@.str.20 = private unnamed_addr constant [7 x i8] c"rmd160\00", align 1
@.str.21 = private unnamed_addr constant [13 x i8] c"rmd160digest\00", align 1
@.str.22 = private unnamed_addr constant [5 x i8] c"sha1\00", align 1
@.str.23 = private unnamed_addr constant [11 x i8] c"sha1digest\00", align 1
@.str.24 = private unnamed_addr constant [7 x i8] c"sha256\00", align 1
@.str.25 = private unnamed_addr constant [13 x i8] c"sha256digest\00", align 1
@.str.26 = private unnamed_addr constant [7 x i8] c"sha384\00", align 1
@.str.27 = private unnamed_addr constant [13 x i8] c"sha384digest\00", align 1
@.str.28 = private unnamed_addr constant [7 x i8] c"sha512\00", align 1
@.str.29 = private unnamed_addr constant [13 x i8] c"sha512digest\00", align 1
@.str.30 = private unnamed_addr constant [5 x i8] c"size\00", align 1
@.str.31 = private unnamed_addr constant [5 x i8] c"time\00", align 1
@.str.32 = private unnamed_addr constant [5 x i8] c"type\00", align 1
@.str.33 = private unnamed_addr constant [4 x i8] c"uid\00", align 1
@.str.34 = private unnamed_addr constant [6 x i8] c"uname\00", align 1
@.str.35 = private unnamed_addr constant [8 x i8] c"use-set\00", align 1
@.str.36 = private unnamed_addr constant [8 x i8] c"#mtree\0A\00", align 1
@mtree_entry_new.rb_ops = internal constant %struct.archive_rb_tree_ops { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)* @mtree_entry_cmp_node, i32 (%struct.archive_rb_node*, i8*)* @mtree_entry_cmp_key }, align 8
@.str.37 = private unnamed_addr constant [40 x i8] c"Can't allocate memory for a mtree entry\00", align 1
@.str.38 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.39 = private unnamed_addr constant [3 x i8] c"./\00", align 1
@.str.40 = private unnamed_addr constant [62 x i8] c"Internal programing error in generating canonical name for %s\00", align 1
@.str.41 = private unnamed_addr constant [27 x i8] c"A name buffer is too small\00", align 1
@.str.42 = private unnamed_addr constant [46 x i8] c"`%s' is not directory, we cannot insert `%s' \00", align 1
@.str.43 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.44 = private unnamed_addr constant [60 x i8] c"Found duplicate entries `%s' and its file type is different\00", align 1
@.str.45 = private unnamed_addr constant [9 x i8] c"# %s/%s\0A\00", align 1
@.str.46 = private unnamed_addr constant [6 x i8] c"# %s\0A\00", align 1
@.str.47 = private unnamed_addr constant [10 x i8] c" nlink=%u\00", align 1
@.str.48 = private unnamed_addr constant [8 x i8] c" gname=\00", align 1
@.str.49 = private unnamed_addr constant [8 x i8] c" uname=\00", align 1
@.str.50 = private unnamed_addr constant [8 x i8] c" flags=\00", align 1
@.str.51 = private unnamed_addr constant [12 x i8] c" flags=none\00", align 1
@.str.52 = private unnamed_addr constant [14 x i8] c" time=%jd.%jd\00", align 1
@.str.53 = private unnamed_addr constant [9 x i8] c" mode=%o\00", align 1
@.str.54 = private unnamed_addr constant [9 x i8] c" gid=%jd\00", align 1
@.str.55 = private unnamed_addr constant [9 x i8] c" uid=%jd\00", align 1
@.str.56 = private unnamed_addr constant [11 x i8] c" inode=%jd\00", align 1
@.str.57 = private unnamed_addr constant [26 x i8] c" resdevice=native,%ju,%ju\00", align 1
@.str.58 = private unnamed_addr constant [11 x i8] c" type=link\00", align 1
@.str.59 = private unnamed_addr constant [7 x i8] c" link=\00", align 1
@.str.60 = private unnamed_addr constant [13 x i8] c" type=socket\00", align 1
@.str.61 = private unnamed_addr constant [11 x i8] c" type=char\00", align 1
@.str.62 = private unnamed_addr constant [23 x i8] c" device=native,%ju,%ju\00", align 1
@.str.63 = private unnamed_addr constant [12 x i8] c" type=block\00", align 1
@.str.64 = private unnamed_addr constant [10 x i8] c" type=dir\00", align 1
@.str.65 = private unnamed_addr constant [11 x i8] c" type=fifo\00", align 1
@.str.66 = private unnamed_addr constant [11 x i8] c" type=file\00", align 1
@.str.67 = private unnamed_addr constant [10 x i8] c" size=%jd\00", align 1
@safe_char = internal constant [256 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\01\01\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.68 = private unnamed_addr constant [11 x i8] c" cksum=%ju\00", align 1
@.str.69 = private unnamed_addr constant [4 x i8] c" \5C\0A\00", align 1
@.str.70 = private unnamed_addr constant [7 x i8] c" uname\00", align 1
@.str.71 = private unnamed_addr constant [7 x i8] c" gname\00", align 1
@.str.72 = private unnamed_addr constant [7 x i8] c" flags\00", align 1
@.str.73 = private unnamed_addr constant [10 x i8] c"/unset%s\0A\00", align 1
@.str.74 = private unnamed_addr constant [8 x i8] c"/set%s\0A\00", align 1
@.str.75 = private unnamed_addr constant [5 x i8] c"..\0A\0A\00", align 1
@crctab = internal constant [256 x i32] [i32 0, i32 79764919, i32 159529838, i32 222504665, i32 319059676, i32 398814059, i32 445009330, i32 507990021, i32 638119352, i32 583659535, i32 797628118, i32 726387553, i32 890018660, i32 835552979, i32 1015980042, i32 944750013, i32 1276238704, i32 1221641927, i32 1167319070, i32 1095957929, i32 1595256236, i32 1540665371, i32 1452775106, i32 1381403509, i32 1780037320, i32 1859660671, i32 1671105958, i32 1733955601, i32 2031960084, i32 2111593891, i32 1889500026, i32 1952343757, i32 -1742489888, i32 -1662866601, i32 -1851683442, i32 -1788833735, i32 -1960329156, i32 -1880695413, i32 -2103051438, i32 -2040207643, i32 -1104454824, i32 -1159051537, i32 -1213636554, i32 -1284997759, i32 -1389417084, i32 -1444007885, i32 -1532160278, i32 -1603531939, i32 -734892656, i32 -789352409, i32 -575645954, i32 -646886583, i32 -952755380, i32 -1007220997, i32 -827056094, i32 -898286187, i32 -231047128, i32 -151282273, i32 -71779514, i32 -8804623, i32 -515967244, i32 -436212925, i32 -390279782, i32 -327299027, i32 881225847, i32 809987520, i32 1023691545, i32 969234094, i32 662832811, i32 591600412, i32 771767749, i32 717299826, i32 311336399, i32 374308984, i32 453813921, i32 533576470, i32 25881363, i32 88864420, i32 134795389, i32 214552010, i32 2023205639, i32 2086057648, i32 1897238633, i32 1976864222, i32 1804852699, i32 1867694188, i32 1645340341, i32 1724971778, i32 1587496639, i32 1516133128, i32 1461550545, i32 1406951526, i32 1302016099, i32 1230646740, i32 1142491917, i32 1087903418, i32 -1398421865, i32 -1469785312, i32 -1524105735, i32 -1578704818, i32 -1079922613, i32 -1151291908, i32 -1239184603, i32 -1293773166, i32 -1968362705, i32 -1905510760, i32 -2094067647, i32 -2014441994, i32 -1716953613, i32 -1654112188, i32 -1876203875, i32 -1796572374, i32 -525066777, i32 -462094256, i32 -382327159, i32 -302564546, i32 -206542021, i32 -143559028, i32 -97365931, i32 -17609246, i32 -960696225, i32 -1031934488, i32 -817968335, i32 -872425850, i32 -709327229, i32 -780559564, i32 -600130067, i32 -654598054, i32 1762451694, i32 1842216281, i32 1619975040, i32 1682949687, i32 2047383090, i32 2127137669, i32 1938468188, i32 2001449195, i32 1325665622, i32 1271206113, i32 1183200824, i32 1111960463, i32 1543535498, i32 1489069629, i32 1434599652, i32 1363369299, i32 622672798, i32 568075817, i32 748617968, i32 677256519, i32 907627842, i32 853037301, i32 1067152940, i32 995781531, i32 51762726, i32 131386257, i32 177728840, i32 240578815, i32 269590778, i32 349224269, i32 429104020, i32 491947555, i32 -248556018, i32 -168932423, i32 -122852000, i32 -60002089, i32 -500490030, i32 -420856475, i32 -341238852, i32 -278395381, i32 -685261898, i32 -739858943, i32 -559578920, i32 -630940305, i32 -1004286614, i32 -1058877219, i32 -845023740, i32 -916395085, i32 -1119974018, i32 -1174433591, i32 -1262701040, i32 -1333941337, i32 -1371866206, i32 -1426332139, i32 -1481064244, i32 -1552294533, i32 -1690935098, i32 -1611170447, i32 -1833673816, i32 -1770699233, i32 -2009983462, i32 -1930228819, i32 -2119160460, i32 -2056179517, i32 1569362073, i32 1498123566, i32 1409854455, i32 1355396672, i32 1317987909, i32 1246755826, i32 1192025387, i32 1137557660, i32 2072149281, i32 2135122070, i32 1912620623, i32 1992383480, i32 1753615357, i32 1816598090, i32 1627664531, i32 1707420964, i32 295390185, i32 358241886, i32 404320391, i32 483945776, i32 43990325, i32 106832002, i32 186451547, i32 266083308, i32 932423249, i32 861060070, i32 1041341759, i32 986742920, i32 613929101, i32 542559546, i32 756411363, i32 701822548, i32 -978770311, i32 -1050133554, i32 -869589737, i32 -924188512, i32 -693284699, i32 -764654318, i32 -550540341, i32 -605129092, i32 -475935807, i32 -413084042, i32 -366743377, i32 -287118056, i32 -257573603, i32 -194731862, i32 -114850189, i32 -35218492, i32 -1984365303, i32 -1921392450, i32 -2143631769, i32 -2063868976, i32 -1698919467, i32 -1635936670, i32 -1824608069, i32 -1744851700, i32 -1347415887, i32 -1418654458, i32 -1506661409, i32 -1561119128, i32 -1129027987, i32 -1200260134, i32 -1254728445, i32 -1309196108], align 16

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_mtree(%struct.archive* %_a) #0 !dbg !330 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !425, metadata !426), !dbg !427
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !428
  %call = call i32 @archive_write_set_format_mtree_default(%struct.archive* %0, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !429
  ret i32 %call, !dbg !430
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_set_format_mtree_default(%struct.archive* %_a, i8* %fn) #0 !dbg !332 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %fn.addr = alloca i8*, align 8
  %a = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !431, metadata !426), !dbg !432
  store i8* %fn, i8** %fn.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fn.addr, metadata !433, metadata !426), !dbg !434
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !435, metadata !426), !dbg !436
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !437
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !438
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !436
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !439, metadata !426), !dbg !440
  br label %do.body, !dbg !441

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !442, metadata !426), !dbg !444
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !445
  %3 = load i8*, i8** %fn.addr, align 8, !dbg !445
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* %3), !dbg !445
  store i32 %call, i32* %magic_test, align 4, !dbg !445
  %4 = load i32, i32* %magic_test, align 4, !dbg !445
  %cmp = icmp eq i32 %4, -30, !dbg !445
  br i1 %cmp, label %if.then, label %if.end, !dbg !445

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !447
  br label %return, !dbg !447

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !450

do.end:                                           ; preds = %if.end
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !452
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 22, !dbg !454
  %6 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !454
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %6, null, !dbg !455
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !456

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !457
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 22, !dbg !458
  %8 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !458
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !459
  %call4 = call i32 %8(%struct.archive_write* %9), !dbg !460
  br label %if.end5, !dbg !460

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 256) #6, !dbg !461
  %10 = bitcast i8* %call6 to %struct.mtree_writer*, !dbg !461
  store %struct.mtree_writer* %10, %struct.mtree_writer** %mtree, align 8, !dbg !463
  %cmp7 = icmp eq %struct.mtree_writer* %10, null, !dbg !464
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !465

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !466
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !468
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i32 0, i32 0)), !dbg !469
  store i32 -30, i32* %retval, align 4, !dbg !470
  br label %return, !dbg !470

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !471
  %mtree_entry = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %12, i32 0, i32 0, !dbg !472
  store %struct.mtree_entry* null, %struct.mtree_entry** %mtree_entry, align 8, !dbg !473
  %13 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !474
  %first = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %13, i32 0, i32 7, !dbg !475
  store i32 1, i32* %first, align 8, !dbg !476
  %14 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !477
  %set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %14, i32 0, i32 9, !dbg !478
  %15 = bitcast %struct.anon* %set to i8*, !dbg !479
  call void @llvm.memset.p0i8.i64(i8* %15, i8 0, i64 56, i32 8, i1 false), !dbg !479
  %16 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !480
  %keys = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %16, i32 0, i32 16, !dbg !481
  store i32 4032058, i32* %keys, align 8, !dbg !482
  %17 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !483
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %17, i32 0, i32 17, !dbg !484
  store i32 0, i32* %dironly, align 4, !dbg !485
  %18 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !486
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %18, i32 0, i32 18, !dbg !487
  store i32 0, i32* %indent, align 8, !dbg !488
  br label %do.body10, !dbg !489

do.body10:                                        ; preds = %if.end9
  %19 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !490
  %ebuf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %19, i32 0, i32 5, !dbg !490
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf, i32 0, i32 0, !dbg !490
  store i8* null, i8** %s, align 8, !dbg !490
  %20 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !490
  %ebuf11 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %20, i32 0, i32 5, !dbg !490
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf11, i32 0, i32 1, !dbg !490
  store i64 0, i64* %length, align 8, !dbg !490
  %21 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !490
  %ebuf12 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %21, i32 0, i32 5, !dbg !490
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf12, i32 0, i32 2, !dbg !490
  store i64 0, i64* %buffer_length, align 8, !dbg !490
  br label %do.end13, !dbg !490

do.end13:                                         ; preds = %do.body10
  br label %do.body14, !dbg !493

do.body14:                                        ; preds = %do.end13
  %22 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !494
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %22, i32 0, i32 6, !dbg !494
  %s15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf, i32 0, i32 0, !dbg !494
  store i8* null, i8** %s15, align 8, !dbg !494
  %23 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !494
  %buf16 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %23, i32 0, i32 6, !dbg !494
  %length17 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf16, i32 0, i32 1, !dbg !494
  store i64 0, i64* %length17, align 8, !dbg !494
  %24 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !494
  %buf18 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %24, i32 0, i32 6, !dbg !494
  %buffer_length19 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf18, i32 0, i32 2, !dbg !494
  store i64 0, i64* %buffer_length19, align 8, !dbg !494
  br label %do.end20, !dbg !494

do.end20:                                         ; preds = %do.body14
  %25 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !497
  call void @mtree_entry_register_init(%struct.mtree_writer* %25), !dbg !498
  %26 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !499
  %27 = bitcast %struct.mtree_writer* %26 to i8*, !dbg !499
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !500
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 14, !dbg !501
  store i8* %27, i8** %format_data, align 8, !dbg !502
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !503
  %format_free21 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 22, !dbg !504
  store i32 (%struct.archive_write*)* @archive_write_mtree_free, i32 (%struct.archive_write*)** %format_free21, align 8, !dbg !505
  %30 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !506
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 15, !dbg !507
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i32 0, i32 0), i8** %format_name, align 8, !dbg !508
  %31 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !509
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 17, !dbg !510
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_mtree_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !511
  %32 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !512
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %32, i32 0, i32 19, !dbg !513
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_mtree_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !514
  %33 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !515
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %33, i32 0, i32 21, !dbg !516
  store i32 (%struct.archive_write*)* @archive_write_mtree_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !517
  %34 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !518
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %34, i32 0, i32 20, !dbg !519
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_mtree_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !520
  %35 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !521
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %35, i32 0, i32 18, !dbg !522
  store i32 (%struct.archive_write*)* @archive_write_mtree_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !523
  %36 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !524
  %archive22 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %36, i32 0, i32 0, !dbg !525
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive22, i32 0, i32 3, !dbg !526
  store i32 524288, i32* %archive_format, align 8, !dbg !527
  %37 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !528
  %archive23 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %37, i32 0, i32 0, !dbg !529
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive23, i32 0, i32 4, !dbg !530
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !531
  store i32 0, i32* %retval, align 4, !dbg !532
  br label %return, !dbg !532

return:                                           ; preds = %do.end20, %if.then8, %if.then
  %38 = load i32, i32* %retval, align 4, !dbg !533
  ret i32 %38, !dbg !533
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_mtree_classic(%struct.archive* %_a) #0 !dbg !331 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %r = alloca i32, align 4
  %a = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !534, metadata !426), !dbg !535
  call void @llvm.dbg.declare(metadata i32* %r, metadata !536, metadata !426), !dbg !537
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !538
  %call = call i32 @archive_write_set_format_mtree_default(%struct.archive* %0, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i32 0, i32 0)), !dbg !539
  store i32 %call, i32* %r, align 4, !dbg !540
  %1 = load i32, i32* %r, align 4, !dbg !541
  %cmp = icmp eq i32 %1, 0, !dbg !543
  br i1 %cmp, label %if.then, label %if.end, !dbg !544

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !545, metadata !426), !dbg !547
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !548
  %3 = bitcast %struct.archive* %2 to %struct.archive_write*, !dbg !549
  store %struct.archive_write* %3, %struct.archive_write** %a, align 8, !dbg !547
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !550, metadata !426), !dbg !551
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !552
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 14, !dbg !553
  %5 = load i8*, i8** %format_data, align 8, !dbg !553
  %6 = bitcast i8* %5 to %struct.mtree_writer*, !dbg !554
  store %struct.mtree_writer* %6, %struct.mtree_writer** %mtree, align 8, !dbg !555
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !556
  %classic = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 11, !dbg !557
  store i32 1, i32* %classic, align 8, !dbg !558
  %8 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !559
  %output_global_set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %8, i32 0, i32 19, !dbg !560
  store i32 1, i32* %output_global_set, align 4, !dbg !561
  br label %if.end, !dbg !562

if.end:                                           ; preds = %if.then, %entry
  %9 = load i32, i32* %r, align 4, !dbg !563
  ret i32 %9, !dbg !564
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define internal void @mtree_entry_register_init(%struct.mtree_writer* %mtree) #0 !dbg !335 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !565, metadata !426), !dbg !566
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !567
  %file_list = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 4, !dbg !568
  %first = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list, i32 0, i32 0, !dbg !569
  store %struct.mtree_entry* null, %struct.mtree_entry** %first, align 8, !dbg !570
  %1 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !571
  %file_list1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %1, i32 0, i32 4, !dbg !572
  %first2 = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list1, i32 0, i32 0, !dbg !573
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !574
  %file_list3 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 4, !dbg !575
  %last = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list3, i32 0, i32 1, !dbg !576
  store %struct.mtree_entry** %first2, %struct.mtree_entry*** %last, align 8, !dbg !577
  ret void, !dbg !578
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_mtree_free(%struct.archive_write* %a) #0 !dbg !338 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !579, metadata !426), !dbg !580
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !581, metadata !426), !dbg !582
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !583
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !584
  %1 = load i8*, i8** %format_data, align 8, !dbg !584
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !583
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !582
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !585
  %cmp = icmp eq %struct.mtree_writer* %3, null, !dbg !587
  br i1 %cmp, label %if.then, label %if.end, !dbg !588

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !589
  br label %return, !dbg !589

if.end:                                           ; preds = %entry
  %4 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !590
  call void @mtree_entry_register_free(%struct.mtree_writer* %4), !dbg !591
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !592
  %cur_dirstr = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 3, !dbg !593
  call void @archive_string_free(%struct.archive_string* %cur_dirstr), !dbg !594
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !595
  %ebuf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 5, !dbg !596
  call void @archive_string_free(%struct.archive_string* %ebuf), !dbg !597
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !598
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 6, !dbg !599
  call void @archive_string_free(%struct.archive_string* %buf), !dbg !600
  %8 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !601
  call void @attr_counter_set_free(%struct.mtree_writer* %8), !dbg !602
  %9 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !603
  %10 = bitcast %struct.mtree_writer* %9 to i8*, !dbg !603
  call void @free(i8* %10) #6, !dbg !604
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !605
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 14, !dbg !606
  store i8* null, i8** %format_data1, align 8, !dbg !607
  store i32 0, i32* %retval, align 4, !dbg !608
  br label %return, !dbg !608

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !609
  ret i32 %12, !dbg !609
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_mtree_options(%struct.archive_write* %a, i8* %key, i8* %value) #0 !dbg !348 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %keybit = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !610, metadata !426), !dbg !611
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !612, metadata !426), !dbg !613
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !614, metadata !426), !dbg !615
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !616, metadata !426), !dbg !617
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !618
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !619
  %1 = load i8*, i8** %format_data, align 8, !dbg !619
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !618
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !617
  call void @llvm.dbg.declare(metadata i32* %keybit, metadata !620, metadata !426), !dbg !621
  store i32 0, i32* %keybit, align 4, !dbg !621
  %3 = load i8*, i8** %key.addr, align 8, !dbg !622
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !622
  %4 = load i8, i8* %arrayidx, align 1, !dbg !622
  %conv = sext i8 %4 to i32, !dbg !622
  switch i32 %conv, label %sw.epilog [
    i32 97, label %sw.bb
    i32 99, label %sw.bb2
    i32 100, label %sw.bb8
    i32 102, label %sw.bb21
    i32 103, label %sw.bb27
    i32 105, label %sw.bb39
    i32 108, label %sw.bb54
    i32 109, label %sw.bb60
    i32 110, label %sw.bb74
    i32 114, label %sw.bb80
    i32 115, label %sw.bb100
    i32 116, label %sw.bb142
    i32 117, label %sw.bb154
  ], !dbg !623

sw.bb:                                            ; preds = %entry
  %5 = load i8*, i8** %key.addr, align 8, !dbg !624
  %call = call i32 @strcmp(i8* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0)) #7, !dbg !627
  %cmp = icmp eq i32 %call, 0, !dbg !628
  br i1 %cmp, label %if.then, label %if.end, !dbg !629

if.then:                                          ; preds = %sw.bb
  store i32 -1, i32* %keybit, align 4, !dbg !630
  br label %if.end, !dbg !631

if.end:                                           ; preds = %if.then, %sw.bb
  br label %sw.epilog, !dbg !632

sw.bb2:                                           ; preds = %entry
  %6 = load i8*, i8** %key.addr, align 8, !dbg !633
  %call3 = call i32 @strcmp(i8* %6, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i32 0, i32 0)) #7, !dbg !635
  %cmp4 = icmp eq i32 %call3, 0, !dbg !636
  br i1 %cmp4, label %if.then6, label %if.end7, !dbg !637

if.then6:                                         ; preds = %sw.bb2
  store i32 1, i32* %keybit, align 4, !dbg !638
  br label %if.end7, !dbg !639

if.end7:                                          ; preds = %if.then6, %sw.bb2
  br label %sw.epilog, !dbg !640

sw.bb8:                                           ; preds = %entry
  %7 = load i8*, i8** %key.addr, align 8, !dbg !641
  %call9 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0)) #7, !dbg !643
  %cmp10 = icmp eq i32 %call9, 0, !dbg !644
  br i1 %cmp10, label %if.then12, label %if.else, !dbg !645

if.then12:                                        ; preds = %sw.bb8
  store i32 2, i32* %keybit, align 4, !dbg !646
  br label %if.end20, !dbg !647

if.else:                                          ; preds = %sw.bb8
  %8 = load i8*, i8** %key.addr, align 8, !dbg !648
  %call13 = call i32 @strcmp(i8* %8, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.7, i32 0, i32 0)) #7, !dbg !650
  %cmp14 = icmp eq i32 %call13, 0, !dbg !651
  br i1 %cmp14, label %if.then16, label %if.end19, !dbg !652

if.then16:                                        ; preds = %if.else
  %9 = load i8*, i8** %value.addr, align 8, !dbg !653
  %cmp17 = icmp ne i8* %9, null, !dbg !655
  %cond = select i1 %cmp17, i32 1, i32 0, !dbg !656
  %10 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !657
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %10, i32 0, i32 17, !dbg !658
  store i32 %cond, i32* %dironly, align 4, !dbg !659
  store i32 0, i32* %retval, align 4, !dbg !660
  br label %return, !dbg !660

if.end19:                                         ; preds = %if.else
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.then12
  br label %sw.epilog, !dbg !661

sw.bb21:                                          ; preds = %entry
  %11 = load i8*, i8** %key.addr, align 8, !dbg !662
  %call22 = call i32 @strcmp(i8* %11, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.8, i32 0, i32 0)) #7, !dbg !664
  %cmp23 = icmp eq i32 %call22, 0, !dbg !665
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !666

if.then25:                                        ; preds = %sw.bb21
  store i32 8, i32* %keybit, align 4, !dbg !667
  br label %if.end26, !dbg !668

if.end26:                                         ; preds = %if.then25, %sw.bb21
  br label %sw.epilog, !dbg !669

sw.bb27:                                          ; preds = %entry
  %12 = load i8*, i8** %key.addr, align 8, !dbg !670
  %call28 = call i32 @strcmp(i8* %12, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i32 0, i32 0)) #7, !dbg !672
  %cmp29 = icmp eq i32 %call28, 0, !dbg !673
  br i1 %cmp29, label %if.then31, label %if.else32, !dbg !674

if.then31:                                        ; preds = %sw.bb27
  store i32 16, i32* %keybit, align 4, !dbg !675
  br label %if.end38, !dbg !676

if.else32:                                        ; preds = %sw.bb27
  %13 = load i8*, i8** %key.addr, align 8, !dbg !677
  %call33 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)) #7, !dbg !679
  %cmp34 = icmp eq i32 %call33, 0, !dbg !680
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !681

if.then36:                                        ; preds = %if.else32
  store i32 32, i32* %keybit, align 4, !dbg !682
  br label %if.end37, !dbg !683

if.end37:                                         ; preds = %if.then36, %if.else32
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.then31
  br label %sw.epilog, !dbg !684

sw.bb39:                                          ; preds = %entry
  %14 = load i8*, i8** %key.addr, align 8, !dbg !685
  %call40 = call i32 @strcmp(i8* %14, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0)) #7, !dbg !687
  %cmp41 = icmp eq i32 %call40, 0, !dbg !688
  br i1 %cmp41, label %if.then43, label %if.else47, !dbg !689

if.then43:                                        ; preds = %sw.bb39
  %15 = load i8*, i8** %value.addr, align 8, !dbg !690
  %cmp44 = icmp ne i8* %15, null, !dbg !692
  %cond46 = select i1 %cmp44, i32 1, i32 0, !dbg !693
  %16 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !694
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %16, i32 0, i32 18, !dbg !695
  store i32 %cond46, i32* %indent, align 8, !dbg !696
  store i32 0, i32* %retval, align 4, !dbg !697
  br label %return, !dbg !697

if.else47:                                        ; preds = %sw.bb39
  %17 = load i8*, i8** %key.addr, align 8, !dbg !698
  %call48 = call i32 @strcmp(i8* %17, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0)) #7, !dbg !700
  %cmp49 = icmp eq i32 %call48, 0, !dbg !701
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !702

if.then51:                                        ; preds = %if.else47
  store i32 67108864, i32* %keybit, align 4, !dbg !703
  br label %if.end52, !dbg !705

if.end52:                                         ; preds = %if.then51, %if.else47
  br label %if.end53

if.end53:                                         ; preds = %if.end52
  br label %sw.epilog, !dbg !706

sw.bb54:                                          ; preds = %entry
  %18 = load i8*, i8** %key.addr, align 8, !dbg !707
  %call55 = call i32 @strcmp(i8* %18, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0)) #7, !dbg !709
  %cmp56 = icmp eq i32 %call55, 0, !dbg !710
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !711

if.then58:                                        ; preds = %sw.bb54
  store i32 65536, i32* %keybit, align 4, !dbg !712
  br label %if.end59, !dbg !713

if.end59:                                         ; preds = %if.then58, %sw.bb54
  br label %sw.epilog, !dbg !714

sw.bb60:                                          ; preds = %entry
  %19 = load i8*, i8** %key.addr, align 8, !dbg !715
  %call61 = call i32 @strcmp(i8* %19, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.14, i32 0, i32 0)) #7, !dbg !717
  %cmp62 = icmp eq i32 %call61, 0, !dbg !718
  br i1 %cmp62, label %if.then67, label %lor.lhs.false, !dbg !719

lor.lhs.false:                                    ; preds = %sw.bb60
  %20 = load i8*, i8** %key.addr, align 8, !dbg !720
  %call64 = call i32 @strcmp(i8* %20, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.15, i32 0, i32 0)) #7, !dbg !721
  %cmp65 = icmp eq i32 %call64, 0, !dbg !722
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !723

if.then67:                                        ; preds = %lor.lhs.false, %sw.bb60
  store i32 256, i32* %keybit, align 4, !dbg !725
  br label %if.end68, !dbg !726

if.end68:                                         ; preds = %if.then67, %lor.lhs.false
  %21 = load i8*, i8** %key.addr, align 8, !dbg !727
  %call69 = call i32 @strcmp(i8* %21, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.16, i32 0, i32 0)) #7, !dbg !729
  %cmp70 = icmp eq i32 %call69, 0, !dbg !730
  br i1 %cmp70, label %if.then72, label %if.end73, !dbg !731

if.then72:                                        ; preds = %if.end68
  store i32 512, i32* %keybit, align 4, !dbg !732
  br label %if.end73, !dbg !733

if.end73:                                         ; preds = %if.then72, %if.end68
  br label %sw.epilog, !dbg !734

sw.bb74:                                          ; preds = %entry
  %22 = load i8*, i8** %key.addr, align 8, !dbg !735
  %call75 = call i32 @strcmp(i8* %22, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.17, i32 0, i32 0)) #7, !dbg !737
  %cmp76 = icmp eq i32 %call75, 0, !dbg !738
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !739

if.then78:                                        ; preds = %sw.bb74
  store i32 1024, i32* %keybit, align 4, !dbg !740
  br label %if.end79, !dbg !741

if.end79:                                         ; preds = %if.then78, %sw.bb74
  br label %sw.epilog, !dbg !742

sw.bb80:                                          ; preds = %entry
  %23 = load i8*, i8** %key.addr, align 8, !dbg !743
  %call81 = call i32 @strcmp(i8* %23, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0)) #7, !dbg !745
  %cmp82 = icmp eq i32 %call81, 0, !dbg !746
  br i1 %cmp82, label %if.then84, label %if.else85, !dbg !747

if.then84:                                        ; preds = %sw.bb80
  store i32 134217728, i32* %keybit, align 4, !dbg !748
  br label %if.end99, !dbg !750

if.else85:                                        ; preds = %sw.bb80
  %24 = load i8*, i8** %key.addr, align 8, !dbg !751
  %call86 = call i32 @strcmp(i8* %24, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.19, i32 0, i32 0)) #7, !dbg !754
  %cmp87 = icmp eq i32 %call86, 0, !dbg !755
  br i1 %cmp87, label %if.then97, label %lor.lhs.false89, !dbg !756

lor.lhs.false89:                                  ; preds = %if.else85
  %25 = load i8*, i8** %key.addr, align 8, !dbg !757
  %call90 = call i32 @strcmp(i8* %25, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.20, i32 0, i32 0)) #7, !dbg !758
  %cmp91 = icmp eq i32 %call90, 0, !dbg !759
  br i1 %cmp91, label %if.then97, label %lor.lhs.false93, !dbg !760

lor.lhs.false93:                                  ; preds = %lor.lhs.false89
  %26 = load i8*, i8** %key.addr, align 8, !dbg !761
  %call94 = call i32 @strcmp(i8* %26, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.21, i32 0, i32 0)) #7, !dbg !762
  %cmp95 = icmp eq i32 %call94, 0, !dbg !763
  br i1 %cmp95, label %if.then97, label %if.end98, !dbg !764

if.then97:                                        ; preds = %lor.lhs.false93, %lor.lhs.false89, %if.else85
  store i32 8192, i32* %keybit, align 4, !dbg !766
  br label %if.end98, !dbg !767

if.end98:                                         ; preds = %if.then97, %lor.lhs.false93
  br label %if.end99

if.end99:                                         ; preds = %if.end98, %if.then84
  br label %sw.epilog, !dbg !768

sw.bb100:                                         ; preds = %entry
  %27 = load i8*, i8** %key.addr, align 8, !dbg !769
  %call101 = call i32 @strcmp(i8* %27, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i32 0, i32 0)) #7, !dbg !771
  %cmp102 = icmp eq i32 %call101, 0, !dbg !772
  br i1 %cmp102, label %if.then108, label %lor.lhs.false104, !dbg !773

lor.lhs.false104:                                 ; preds = %sw.bb100
  %28 = load i8*, i8** %key.addr, align 8, !dbg !774
  %call105 = call i32 @strcmp(i8* %28, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i32 0, i32 0)) #7, !dbg !775
  %cmp106 = icmp eq i32 %call105, 0, !dbg !776
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !777

if.then108:                                       ; preds = %lor.lhs.false104, %sw.bb100
  store i32 16384, i32* %keybit, align 4, !dbg !778
  br label %if.end109, !dbg !779

if.end109:                                        ; preds = %if.then108, %lor.lhs.false104
  %29 = load i8*, i8** %key.addr, align 8, !dbg !780
  %call110 = call i32 @strcmp(i8* %29, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.24, i32 0, i32 0)) #7, !dbg !782
  %cmp111 = icmp eq i32 %call110, 0, !dbg !783
  br i1 %cmp111, label %if.then117, label %lor.lhs.false113, !dbg !784

lor.lhs.false113:                                 ; preds = %if.end109
  %30 = load i8*, i8** %key.addr, align 8, !dbg !785
  %call114 = call i32 @strcmp(i8* %30, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.25, i32 0, i32 0)) #7, !dbg !786
  %cmp115 = icmp eq i32 %call114, 0, !dbg !787
  br i1 %cmp115, label %if.then117, label %if.end118, !dbg !788

if.then117:                                       ; preds = %lor.lhs.false113, %if.end109
  store i32 8388608, i32* %keybit, align 4, !dbg !789
  br label %if.end118, !dbg !790

if.end118:                                        ; preds = %if.then117, %lor.lhs.false113
  %31 = load i8*, i8** %key.addr, align 8, !dbg !791
  %call119 = call i32 @strcmp(i8* %31, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.26, i32 0, i32 0)) #7, !dbg !793
  %cmp120 = icmp eq i32 %call119, 0, !dbg !794
  br i1 %cmp120, label %if.then126, label %lor.lhs.false122, !dbg !795

lor.lhs.false122:                                 ; preds = %if.end118
  %32 = load i8*, i8** %key.addr, align 8, !dbg !796
  %call123 = call i32 @strcmp(i8* %32, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.27, i32 0, i32 0)) #7, !dbg !797
  %cmp124 = icmp eq i32 %call123, 0, !dbg !798
  br i1 %cmp124, label %if.then126, label %if.end127, !dbg !799

if.then126:                                       ; preds = %lor.lhs.false122, %if.end118
  store i32 16777216, i32* %keybit, align 4, !dbg !800
  br label %if.end127, !dbg !801

if.end127:                                        ; preds = %if.then126, %lor.lhs.false122
  %33 = load i8*, i8** %key.addr, align 8, !dbg !802
  %call128 = call i32 @strcmp(i8* %33, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.28, i32 0, i32 0)) #7, !dbg !804
  %cmp129 = icmp eq i32 %call128, 0, !dbg !805
  br i1 %cmp129, label %if.then135, label %lor.lhs.false131, !dbg !806

lor.lhs.false131:                                 ; preds = %if.end127
  %34 = load i8*, i8** %key.addr, align 8, !dbg !807
  %call132 = call i32 @strcmp(i8* %34, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.29, i32 0, i32 0)) #7, !dbg !808
  %cmp133 = icmp eq i32 %call132, 0, !dbg !809
  br i1 %cmp133, label %if.then135, label %if.end136, !dbg !810

if.then135:                                       ; preds = %lor.lhs.false131, %if.end127
  store i32 33554432, i32* %keybit, align 4, !dbg !811
  br label %if.end136, !dbg !812

if.end136:                                        ; preds = %if.then135, %lor.lhs.false131
  %35 = load i8*, i8** %key.addr, align 8, !dbg !813
  %call137 = call i32 @strcmp(i8* %35, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.30, i32 0, i32 0)) #7, !dbg !815
  %cmp138 = icmp eq i32 %call137, 0, !dbg !816
  br i1 %cmp138, label %if.then140, label %if.end141, !dbg !817

if.then140:                                       ; preds = %if.end136
  store i32 32768, i32* %keybit, align 4, !dbg !818
  br label %if.end141, !dbg !819

if.end141:                                        ; preds = %if.then140, %if.end136
  br label %sw.epilog, !dbg !820

sw.bb142:                                         ; preds = %entry
  %36 = load i8*, i8** %key.addr, align 8, !dbg !821
  %call143 = call i32 @strcmp(i8* %36, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.31, i32 0, i32 0)) #7, !dbg !823
  %cmp144 = icmp eq i32 %call143, 0, !dbg !824
  br i1 %cmp144, label %if.then146, label %if.else147, !dbg !825

if.then146:                                       ; preds = %sw.bb142
  store i32 262144, i32* %keybit, align 4, !dbg !826
  br label %if.end153, !dbg !827

if.else147:                                       ; preds = %sw.bb142
  %37 = load i8*, i8** %key.addr, align 8, !dbg !828
  %call148 = call i32 @strcmp(i8* %37, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.32, i32 0, i32 0)) #7, !dbg !830
  %cmp149 = icmp eq i32 %call148, 0, !dbg !831
  br i1 %cmp149, label %if.then151, label %if.end152, !dbg !832

if.then151:                                       ; preds = %if.else147
  store i32 524288, i32* %keybit, align 4, !dbg !833
  br label %if.end152, !dbg !834

if.end152:                                        ; preds = %if.then151, %if.else147
  br label %if.end153

if.end153:                                        ; preds = %if.end152, %if.then146
  br label %sw.epilog, !dbg !835

sw.bb154:                                         ; preds = %entry
  %38 = load i8*, i8** %key.addr, align 8, !dbg !836
  %call155 = call i32 @strcmp(i8* %38, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.33, i32 0, i32 0)) #7, !dbg !838
  %cmp156 = icmp eq i32 %call155, 0, !dbg !839
  br i1 %cmp156, label %if.then158, label %if.else159, !dbg !840

if.then158:                                       ; preds = %sw.bb154
  store i32 1048576, i32* %keybit, align 4, !dbg !841
  br label %if.end174, !dbg !842

if.else159:                                       ; preds = %sw.bb154
  %39 = load i8*, i8** %key.addr, align 8, !dbg !843
  %call160 = call i32 @strcmp(i8* %39, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.34, i32 0, i32 0)) #7, !dbg !845
  %cmp161 = icmp eq i32 %call160, 0, !dbg !846
  br i1 %cmp161, label %if.then163, label %if.else164, !dbg !847

if.then163:                                       ; preds = %if.else159
  store i32 2097152, i32* %keybit, align 4, !dbg !848
  br label %if.end173, !dbg !849

if.else164:                                       ; preds = %if.else159
  %40 = load i8*, i8** %key.addr, align 8, !dbg !850
  %call165 = call i32 @strcmp(i8* %40, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.35, i32 0, i32 0)) #7, !dbg !852
  %cmp166 = icmp eq i32 %call165, 0, !dbg !853
  br i1 %cmp166, label %if.then168, label %if.end172, !dbg !854

if.then168:                                       ; preds = %if.else164
  %41 = load i8*, i8** %value.addr, align 8, !dbg !855
  %cmp169 = icmp ne i8* %41, null, !dbg !857
  %cond171 = select i1 %cmp169, i32 1, i32 0, !dbg !858
  %42 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !859
  %output_global_set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %42, i32 0, i32 19, !dbg !860
  store i32 %cond171, i32* %output_global_set, align 4, !dbg !861
  store i32 0, i32* %retval, align 4, !dbg !862
  br label %return, !dbg !862

if.end172:                                        ; preds = %if.else164
  br label %if.end173

if.end173:                                        ; preds = %if.end172, %if.then163
  br label %if.end174

if.end174:                                        ; preds = %if.end173, %if.then158
  br label %sw.epilog, !dbg !863

sw.epilog:                                        ; preds = %entry, %if.end174, %if.end153, %if.end141, %if.end99, %if.end79, %if.end73, %if.end59, %if.end53, %if.end38, %if.end26, %if.end20, %if.end7, %if.end
  %43 = load i32, i32* %keybit, align 4, !dbg !864
  %cmp175 = icmp ne i32 %43, 0, !dbg !866
  br i1 %cmp175, label %if.then177, label %if.end184, !dbg !867

if.then177:                                       ; preds = %sw.epilog
  %44 = load i8*, i8** %value.addr, align 8, !dbg !868
  %cmp178 = icmp ne i8* %44, null, !dbg !871
  br i1 %cmp178, label %if.then180, label %if.else181, !dbg !872

if.then180:                                       ; preds = %if.then177
  %45 = load i32, i32* %keybit, align 4, !dbg !873
  %46 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !874
  %keys = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %46, i32 0, i32 16, !dbg !875
  %47 = load i32, i32* %keys, align 8, !dbg !876
  %or = or i32 %47, %45, !dbg !876
  store i32 %or, i32* %keys, align 8, !dbg !876
  br label %if.end183, !dbg !874

if.else181:                                       ; preds = %if.then177
  %48 = load i32, i32* %keybit, align 4, !dbg !877
  %neg = xor i32 %48, -1, !dbg !878
  %49 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !879
  %keys182 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %49, i32 0, i32 16, !dbg !880
  %50 = load i32, i32* %keys182, align 8, !dbg !881
  %and = and i32 %50, %neg, !dbg !881
  store i32 %and, i32* %keys182, align 8, !dbg !881
  br label %if.end183

if.end183:                                        ; preds = %if.else181, %if.then180
  store i32 0, i32* %retval, align 4, !dbg !882
  br label %return, !dbg !882

if.end184:                                        ; preds = %sw.epilog
  store i32 -20, i32* %retval, align 4, !dbg !883
  br label %return, !dbg !883

return:                                           ; preds = %if.end184, %if.end183, %if.then168, %if.then43, %if.then16
  %51 = load i32, i32* %retval, align 4, !dbg !884
  ret i32 %51, !dbg !884
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_mtree_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %mtree_entry = alloca %struct.mtree_entry*, align 8
  %r = alloca i32, align 4
  %r2 = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !885, metadata !426), !dbg !886
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !887, metadata !426), !dbg !888
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !889, metadata !426), !dbg !890
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !891
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !892
  %1 = load i8*, i8** %format_data, align 8, !dbg !892
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !891
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !890
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %mtree_entry, metadata !893, metadata !426), !dbg !894
  call void @llvm.dbg.declare(metadata i32* %r, metadata !895, metadata !426), !dbg !896
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !897, metadata !426), !dbg !898
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !899
  %first = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %3, i32 0, i32 7, !dbg !901
  %4 = load i32, i32* %first, align 8, !dbg !901
  %tobool = icmp ne i32 %4, 0, !dbg !899
  br i1 %tobool, label %if.then, label %if.end4, !dbg !902

if.then:                                          ; preds = %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !903
  %first2 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 7, !dbg !905
  store i32 0, i32* %first2, align 8, !dbg !906
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !907
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 6, !dbg !908
  %call = call %struct.archive_string* @archive_strcat(%struct.archive_string* %buf, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.36, i32 0, i32 0)), !dbg !909
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !910
  %keys = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 16, !dbg !912
  %8 = load i32, i32* %keys, align 8, !dbg !912
  %and = and i32 %8, 3670584, !dbg !913
  %cmp = icmp eq i32 %and, 0, !dbg !914
  br i1 %cmp, label %if.then3, label %if.end, !dbg !915

if.then3:                                         ; preds = %if.then
  %9 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !916
  %output_global_set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %9, i32 0, i32 19, !dbg !917
  store i32 0, i32* %output_global_set, align 4, !dbg !918
  br label %if.end, !dbg !916

if.end:                                           ; preds = %if.then3, %if.then
  br label %if.end4, !dbg !919

if.end4:                                          ; preds = %if.end, %entry
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !920
  %call5 = call i64 @archive_entry_size(%struct.archive_entry* %10), !dbg !921
  %11 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !922
  %entry_bytes_remaining = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %11, i32 0, i32 8, !dbg !923
  store i64 %call5, i64* %entry_bytes_remaining, align 8, !dbg !924
  %12 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !925
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %12, i32 0, i32 17, !dbg !927
  %13 = load i32, i32* %dironly, align 4, !dbg !927
  %tobool6 = icmp ne i32 %13, 0, !dbg !925
  br i1 %tobool6, label %land.lhs.true, label %if.end10, !dbg !928

land.lhs.true:                                    ; preds = %if.end4
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !929
  %call7 = call i32 @archive_entry_filetype(%struct.archive_entry* %14), !dbg !931
  %cmp8 = icmp ne i32 %call7, 16384, !dbg !932
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !933

if.then9:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !934
  br label %return, !dbg !934

if.end10:                                         ; preds = %land.lhs.true, %if.end4
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !935
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !936
  %call11 = call i32 @mtree_entry_new(%struct.archive_write* %15, %struct.archive_entry* %16, %struct.mtree_entry** %mtree_entry), !dbg !937
  store i32 %call11, i32* %r2, align 4, !dbg !938
  %17 = load i32, i32* %r2, align 4, !dbg !939
  %cmp12 = icmp slt i32 %17, -20, !dbg !941
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !942

if.then13:                                        ; preds = %if.end10
  %18 = load i32, i32* %r2, align 4, !dbg !943
  store i32 %18, i32* %retval, align 4, !dbg !944
  br label %return, !dbg !944

if.end14:                                         ; preds = %if.end10
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !945
  %call15 = call i32 @mtree_entry_tree_add(%struct.archive_write* %19, %struct.mtree_entry** %mtree_entry), !dbg !946
  store i32 %call15, i32* %r, align 4, !dbg !947
  %20 = load i32, i32* %r, align 4, !dbg !948
  %cmp16 = icmp slt i32 %20, -20, !dbg !950
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !951

if.then17:                                        ; preds = %if.end14
  %21 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry, align 8, !dbg !952
  call void @mtree_entry_free(%struct.mtree_entry* %21), !dbg !954
  %22 = load i32, i32* %r, align 4, !dbg !955
  store i32 %22, i32* %retval, align 4, !dbg !956
  br label %return, !dbg !956

if.end18:                                         ; preds = %if.end14
  %23 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry, align 8, !dbg !957
  %24 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !958
  %mtree_entry19 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %24, i32 0, i32 0, !dbg !959
  store %struct.mtree_entry* %23, %struct.mtree_entry** %mtree_entry19, align 8, !dbg !960
  %25 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry, align 8, !dbg !961
  %reg_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %25, i32 0, i32 4, !dbg !963
  %26 = load %struct.reg_info*, %struct.reg_info** %reg_info, align 8, !dbg !963
  %tobool20 = icmp ne %struct.reg_info* %26, null, !dbg !961
  br i1 %tobool20, label %if.then21, label %if.end22, !dbg !964

if.then21:                                        ; preds = %if.end18
  %27 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !965
  call void @sum_init(%struct.mtree_writer* %27), !dbg !966
  br label %if.end22, !dbg !966

if.end22:                                         ; preds = %if.then21, %if.end18
  %28 = load i32, i32* %r2, align 4, !dbg !967
  store i32 %28, i32* %retval, align 4, !dbg !968
  br label %return, !dbg !968

return:                                           ; preds = %if.end22, %if.then17, %if.then13, %if.then9
  %29 = load i32, i32* %retval, align 4, !dbg !969
  ret i32 %29, !dbg !969
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_mtree_close(%struct.archive_write* %a) #0 !dbg !377 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !970, metadata !426), !dbg !971
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !972, metadata !426), !dbg !973
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !974
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !975
  %1 = load i8*, i8** %format_data, align 8, !dbg !975
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !974
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !973
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !976, metadata !426), !dbg !977
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !978
  %root = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %3, i32 0, i32 1, !dbg !980
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %root, align 8, !dbg !980
  %cmp = icmp ne %struct.mtree_entry* %4, null, !dbg !981
  br i1 %cmp, label %if.then, label %if.end3, !dbg !982

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !983
  %call = call i32 @write_mtree_entry_tree(%struct.archive_write* %5), !dbg !985
  store i32 %call, i32* %ret, align 4, !dbg !986
  %6 = load i32, i32* %ret, align 4, !dbg !987
  %cmp1 = icmp ne i32 %6, 0, !dbg !989
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !990

if.then2:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !991
  br label %return, !dbg !991

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !992

if.end3:                                          ; preds = %if.end, %entry
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !993
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !994
  %call4 = call i32 @archive_write_set_bytes_in_last_block(%struct.archive* %archive, i32 1), !dbg !995
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !996
  %9 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !997
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %9, i32 0, i32 6, !dbg !998
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf, i32 0, i32 0, !dbg !999
  %10 = load i8*, i8** %s, align 8, !dbg !999
  %11 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1000
  %buf5 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %11, i32 0, i32 6, !dbg !1001
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf5, i32 0, i32 1, !dbg !1002
  %12 = load i64, i64* %length, align 8, !dbg !1002
  %call6 = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %10, i64 %12), !dbg !1003
  store i32 %call6, i32* %retval, align 4, !dbg !1004
  br label %return, !dbg !1004

return:                                           ; preds = %if.end3, %if.then2
  %13 = load i32, i32* %retval, align 4, !dbg !1005
  ret i32 %13, !dbg !1005
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_mtree_data(%struct.archive_write* %a, i8* %buff, i64 %n) #0 !dbg !405 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1006, metadata !426), !dbg !1007
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1008, metadata !426), !dbg !1009
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !1010, metadata !426), !dbg !1011
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !1012, metadata !426), !dbg !1013
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1014
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1015
  %1 = load i8*, i8** %format_data, align 8, !dbg !1015
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !1014
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !1013
  %3 = load i64, i64* %n.addr, align 8, !dbg !1016
  %4 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1018
  %entry_bytes_remaining = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %4, i32 0, i32 8, !dbg !1019
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1019
  %cmp = icmp ugt i64 %3, %5, !dbg !1020
  br i1 %cmp, label %if.then, label %if.end, !dbg !1021

if.then:                                          ; preds = %entry
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1022
  %entry_bytes_remaining1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 8, !dbg !1023
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !1023
  store i64 %7, i64* %n.addr, align 8, !dbg !1024
  br label %if.end, !dbg !1025

if.end:                                           ; preds = %if.then, %entry
  %8 = load i64, i64* %n.addr, align 8, !dbg !1026
  %9 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1027
  %entry_bytes_remaining2 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %9, i32 0, i32 8, !dbg !1028
  %10 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !1029
  %sub = sub i64 %10, %8, !dbg !1029
  store i64 %sub, i64* %entry_bytes_remaining2, align 8, !dbg !1029
  %11 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1030
  %mtree_entry = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %11, i32 0, i32 0, !dbg !1032
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry, align 8, !dbg !1032
  %cmp3 = icmp eq %struct.mtree_entry* %12, null, !dbg !1033
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1034

if.then4:                                         ; preds = %if.end
  %13 = load i64, i64* %n.addr, align 8, !dbg !1035
  store i64 %13, i64* %retval, align 8, !dbg !1036
  br label %return, !dbg !1036

if.end5:                                          ; preds = %if.end
  %14 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1037
  %mtree_entry6 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %14, i32 0, i32 0, !dbg !1039
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry6, align 8, !dbg !1039
  %filetype = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %15, i32 0, i32 13, !dbg !1040
  %16 = load i32, i32* %filetype, align 4, !dbg !1040
  %cmp7 = icmp eq i32 %16, 32768, !dbg !1041
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1042

if.then8:                                         ; preds = %if.end5
  %17 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1043
  %18 = load i8*, i8** %buff.addr, align 8, !dbg !1044
  %19 = load i64, i64* %n.addr, align 8, !dbg !1045
  call void @sum_update(%struct.mtree_writer* %17, i8* %18, i64 %19), !dbg !1046
  br label %if.end9, !dbg !1046

if.end9:                                          ; preds = %if.then8, %if.end5
  %20 = load i64, i64* %n.addr, align 8, !dbg !1047
  store i64 %20, i64* %retval, align 8, !dbg !1048
  br label %return, !dbg !1048

return:                                           ; preds = %if.end9, %if.then4
  %21 = load i64, i64* %retval, align 8, !dbg !1049
  ret i64 %21, !dbg !1049
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_mtree_finish_entry(%struct.archive_write* %a) #0 !dbg !409 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %me = alloca %struct.mtree_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1050, metadata !426), !dbg !1051
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !1052, metadata !426), !dbg !1053
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1054
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1055
  %1 = load i8*, i8** %format_data, align 8, !dbg !1055
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !1054
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !1053
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me, metadata !1056, metadata !426), !dbg !1057
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1058
  %mtree_entry = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %3, i32 0, i32 0, !dbg !1060
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %mtree_entry, align 8, !dbg !1060
  store %struct.mtree_entry* %4, %struct.mtree_entry** %me, align 8, !dbg !1061
  %cmp = icmp eq %struct.mtree_entry* %4, null, !dbg !1062
  br i1 %cmp, label %if.then, label %if.end, !dbg !1063

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1064
  br label %return, !dbg !1064

if.end:                                           ; preds = %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1065
  %mtree_entry1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 0, !dbg !1066
  store %struct.mtree_entry* null, %struct.mtree_entry** %mtree_entry1, align 8, !dbg !1067
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1068
  %reg_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 4, !dbg !1070
  %7 = load %struct.reg_info*, %struct.reg_info** %reg_info, align 8, !dbg !1070
  %tobool = icmp ne %struct.reg_info* %7, null, !dbg !1068
  br i1 %tobool, label %if.then2, label %if.end4, !dbg !1071

if.then2:                                         ; preds = %if.end
  %8 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1072
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1073
  %reg_info3 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 4, !dbg !1074
  %10 = load %struct.reg_info*, %struct.reg_info** %reg_info3, align 8, !dbg !1074
  call void @sum_final(%struct.mtree_writer* %8, %struct.reg_info* %10), !dbg !1075
  br label %if.end4, !dbg !1075

if.end4:                                          ; preds = %if.then2, %if.end
  store i32 0, i32* %retval, align 4, !dbg !1076
  br label %return, !dbg !1076

return:                                           ; preds = %if.end4, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1077
  ret i32 %11, !dbg !1077
}

; Function Attrs: nounwind uwtable
define internal void @mtree_entry_register_free(%struct.mtree_writer* %mtree) #0 !dbg !339 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %file = alloca %struct.mtree_entry*, align 8
  %file_next = alloca %struct.mtree_entry*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !1078, metadata !426), !dbg !1079
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file, metadata !1080, metadata !426), !dbg !1081
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file_next, metadata !1082, metadata !426), !dbg !1083
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1084
  %file_list = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 4, !dbg !1085
  %first = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list, i32 0, i32 0, !dbg !1086
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %first, align 8, !dbg !1086
  store %struct.mtree_entry* %1, %struct.mtree_entry** %file, align 8, !dbg !1087
  br label %while.cond, !dbg !1088

while.cond:                                       ; preds = %while.body, %entry
  %2 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1089
  %cmp = icmp ne %struct.mtree_entry* %2, null, !dbg !1091
  br i1 %cmp, label %while.body, label %while.end, !dbg !1092

while.body:                                       ; preds = %while.cond
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1093
  %next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 1, !dbg !1095
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %next, align 8, !dbg !1095
  store %struct.mtree_entry* %4, %struct.mtree_entry** %file_next, align 8, !dbg !1096
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1097
  call void @mtree_entry_free(%struct.mtree_entry* %5), !dbg !1098
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %file_next, align 8, !dbg !1099
  store %struct.mtree_entry* %6, %struct.mtree_entry** %file, align 8, !dbg !1100
  br label %while.cond, !dbg !1101

while.end:                                        ; preds = %while.cond
  ret void, !dbg !1103
}

declare void @archive_string_free(%struct.archive_string*) #2

; Function Attrs: nounwind uwtable
define internal void @attr_counter_set_free(%struct.mtree_writer* %mtree) #0 !dbg !343 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %acs = alloca %struct.att_counter_set*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !1104, metadata !426), !dbg !1105
  call void @llvm.dbg.declare(metadata %struct.att_counter_set** %acs, metadata !1106, metadata !426), !dbg !1108
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1109
  %acs1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 10, !dbg !1110
  store %struct.att_counter_set* %acs1, %struct.att_counter_set** %acs, align 8, !dbg !1108
  %1 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !1111
  %uid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %1, i32 0, i32 0, !dbg !1112
  call void @attr_counter_free(%struct.attr_counter** %uid_list), !dbg !1113
  %2 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !1114
  %gid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %2, i32 0, i32 1, !dbg !1115
  call void @attr_counter_free(%struct.attr_counter** %gid_list), !dbg !1116
  %3 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !1117
  %mode_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %3, i32 0, i32 2, !dbg !1118
  call void @attr_counter_free(%struct.attr_counter** %mode_list), !dbg !1119
  %4 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !1120
  %flags_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %4, i32 0, i32 3, !dbg !1121
  call void @attr_counter_free(%struct.attr_counter** %flags_list), !dbg !1122
  ret void, !dbg !1123
}

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal void @mtree_entry_free(%struct.mtree_entry* %me) #0 !dbg !340 {
entry:
  %me.addr = alloca %struct.mtree_entry*, align 8
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !1124, metadata !426), !dbg !1125
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1126
  %parentdir = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 5, !dbg !1127
  call void @archive_string_free(%struct.archive_string* %parentdir), !dbg !1128
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1129
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %1, i32 0, i32 6, !dbg !1130
  call void @archive_string_free(%struct.archive_string* %basename), !dbg !1131
  %2 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1132
  %pathname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %2, i32 0, i32 7, !dbg !1133
  call void @archive_string_free(%struct.archive_string* %pathname), !dbg !1134
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1135
  %symlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 8, !dbg !1136
  call void @archive_string_free(%struct.archive_string* %symlink), !dbg !1137
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1138
  %uname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %4, i32 0, i32 9, !dbg !1139
  call void @archive_string_free(%struct.archive_string* %uname), !dbg !1140
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1141
  %gname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %5, i32 0, i32 10, !dbg !1142
  call void @archive_string_free(%struct.archive_string* %gname), !dbg !1143
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1144
  %fflags_text = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 11, !dbg !1145
  call void @archive_string_free(%struct.archive_string* %fflags_text), !dbg !1146
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1147
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %7, i32 0, i32 3, !dbg !1148
  %8 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !1148
  %9 = bitcast %struct.dir_info* %8 to i8*, !dbg !1147
  call void @free(i8* %9) #6, !dbg !1149
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1150
  %reg_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %10, i32 0, i32 4, !dbg !1151
  %11 = load %struct.reg_info*, %struct.reg_info** %reg_info, align 8, !dbg !1151
  %12 = bitcast %struct.reg_info* %11 to i8*, !dbg !1150
  call void @free(i8* %12) #6, !dbg !1152
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !1153
  %14 = bitcast %struct.mtree_entry* %13 to i8*, !dbg !1153
  call void @free(i8* %14) #6, !dbg !1154
  ret void, !dbg !1155
}

; Function Attrs: nounwind uwtable
define internal void @attr_counter_free(%struct.attr_counter** %top) #0 !dbg !344 {
entry:
  %top.addr = alloca %struct.attr_counter**, align 8
  %ac = alloca %struct.attr_counter*, align 8
  %tac = alloca %struct.attr_counter*, align 8
  store %struct.attr_counter** %top, %struct.attr_counter*** %top.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.attr_counter*** %top.addr, metadata !1156, metadata !426), !dbg !1157
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %ac, metadata !1158, metadata !426), !dbg !1159
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %tac, metadata !1160, metadata !426), !dbg !1161
  %0 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !1162
  %1 = load %struct.attr_counter*, %struct.attr_counter** %0, align 8, !dbg !1164
  %cmp = icmp eq %struct.attr_counter* %1, null, !dbg !1165
  br i1 %cmp, label %if.then, label %if.end, !dbg !1166

if.then:                                          ; preds = %entry
  br label %return, !dbg !1167

if.end:                                           ; preds = %entry
  %2 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !1168
  %3 = load %struct.attr_counter*, %struct.attr_counter** %2, align 8, !dbg !1169
  store %struct.attr_counter* %3, %struct.attr_counter** %ac, align 8, !dbg !1170
  br label %while.cond, !dbg !1171

while.cond:                                       ; preds = %while.body, %if.end
  %4 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !1172
  %cmp1 = icmp ne %struct.attr_counter* %4, null, !dbg !1174
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1175

while.body:                                       ; preds = %while.cond
  %5 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !1176
  %next = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %5, i32 0, i32 1, !dbg !1178
  %6 = load %struct.attr_counter*, %struct.attr_counter** %next, align 8, !dbg !1178
  store %struct.attr_counter* %6, %struct.attr_counter** %tac, align 8, !dbg !1179
  %7 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !1180
  %8 = bitcast %struct.attr_counter* %7 to i8*, !dbg !1180
  call void @free(i8* %8) #6, !dbg !1181
  %9 = load %struct.attr_counter*, %struct.attr_counter** %tac, align 8, !dbg !1182
  store %struct.attr_counter* %9, %struct.attr_counter** %ac, align 8, !dbg !1183
  br label %while.cond, !dbg !1184

while.end:                                        ; preds = %while.cond
  %10 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !1186
  store %struct.attr_counter* null, %struct.attr_counter** %10, align 8, !dbg !1187
  br label %return, !dbg !1188

return:                                           ; preds = %while.end, %if.then
  ret void, !dbg !1189
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #5

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_new(%struct.archive_write* %a, %struct.archive_entry* %entry1, %struct.mtree_entry** %m_entry) #0 !dbg !350 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m_entry.addr = alloca %struct.mtree_entry**, align 8
  %me = alloca %struct.mtree_entry*, align 8
  %s = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1190, metadata !426), !dbg !1191
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1192, metadata !426), !dbg !1193
  store %struct.mtree_entry** %m_entry, %struct.mtree_entry*** %m_entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry*** %m_entry.addr, metadata !1194, metadata !426), !dbg !1195
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me, metadata !1196, metadata !426), !dbg !1197
  call void @llvm.dbg.declare(metadata i8** %s, metadata !1198, metadata !426), !dbg !1199
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1200, metadata !426), !dbg !1201
  %call = call noalias i8* @calloc(i64 1, i64 336) #6, !dbg !1202
  %0 = bitcast i8* %call to %struct.mtree_entry*, !dbg !1202
  store %struct.mtree_entry* %0, %struct.mtree_entry** %me, align 8, !dbg !1203
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1204
  %cmp = icmp eq %struct.mtree_entry* %1, null, !dbg !1206
  br i1 %cmp, label %if.then, label %if.end, !dbg !1207

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1208
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !1210
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.37, i32 0, i32 0)), !dbg !1211
  %3 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !1212
  store %struct.mtree_entry* null, %struct.mtree_entry** %3, align 8, !dbg !1213
  store i32 -30, i32* %retval, align 4, !dbg !1214
  br label %return, !dbg !1214

if.end:                                           ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1215
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1216
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1217
  %call2 = call i32 @mtree_entry_setup_filenames(%struct.archive_write* %4, %struct.mtree_entry* %5, %struct.archive_entry* %6), !dbg !1218
  store i32 %call2, i32* %r, align 4, !dbg !1219
  %7 = load i32, i32* %r, align 4, !dbg !1220
  %cmp3 = icmp slt i32 %7, -20, !dbg !1222
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1223

if.then4:                                         ; preds = %if.end
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1224
  call void @mtree_entry_free(%struct.mtree_entry* %8), !dbg !1226
  %9 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !1227
  store %struct.mtree_entry* null, %struct.mtree_entry** %9, align 8, !dbg !1228
  %10 = load i32, i32* %r, align 4, !dbg !1229
  store i32 %10, i32* %retval, align 4, !dbg !1230
  br label %return, !dbg !1230

if.end5:                                          ; preds = %if.end
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1231
  %call6 = call i8* @archive_entry_symlink(%struct.archive_entry* %11), !dbg !1233
  store i8* %call6, i8** %s, align 8, !dbg !1234
  %cmp7 = icmp ne i8* %call6, null, !dbg !1235
  br i1 %cmp7, label %if.then8, label %if.end13, !dbg !1236

if.then8:                                         ; preds = %if.end5
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1237
  %symlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %12, i32 0, i32 8, !dbg !1237
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %symlink, i32 0, i32 1, !dbg !1237
  store i64 0, i64* %length, align 8, !dbg !1237
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1237
  %symlink9 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 8, !dbg !1237
  %14 = load i8*, i8** %s, align 8, !dbg !1237
  %15 = load i8*, i8** %s, align 8, !dbg !1237
  %cmp10 = icmp eq i8* %15, null, !dbg !1237
  br i1 %cmp10, label %cond.true, label %cond.false, !dbg !1237

cond.true:                                        ; preds = %if.then8
  br label %cond.end, !dbg !1238

cond.false:                                       ; preds = %if.then8
  %16 = load i8*, i8** %s, align 8, !dbg !1240
  %call11 = call i64 @strlen(i8* %16) #7, !dbg !1240
  br label %cond.end, !dbg !1240

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call11, %cond.false ], !dbg !1242
  %call12 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %symlink9, i8* %14, i64 %cond), !dbg !1242
  br label %if.end13, !dbg !1242

if.end13:                                         ; preds = %cond.end, %if.end5
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1244
  %call14 = call i32 @archive_entry_nlink(%struct.archive_entry* %17), !dbg !1245
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1246
  %nlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %18, i32 0, i32 12, !dbg !1247
  store i32 %call14, i32* %nlink, align 8, !dbg !1248
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1249
  %call15 = call i32 @archive_entry_filetype(%struct.archive_entry* %19), !dbg !1250
  %20 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1251
  %filetype = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %20, i32 0, i32 13, !dbg !1252
  store i32 %call15, i32* %filetype, align 4, !dbg !1253
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1254
  %call16 = call i32 @archive_entry_mode(%struct.archive_entry* %21), !dbg !1255
  %and = and i32 %call16, 4095, !dbg !1256
  %22 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1257
  %mode = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %22, i32 0, i32 14, !dbg !1258
  store i32 %and, i32* %mode, align 8, !dbg !1259
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1260
  %call17 = call i64 @archive_entry_uid(%struct.archive_entry* %23), !dbg !1261
  %24 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1262
  %uid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %24, i32 0, i32 16, !dbg !1263
  store i64 %call17, i64* %uid, align 8, !dbg !1264
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1265
  %call18 = call i64 @archive_entry_gid(%struct.archive_entry* %25), !dbg !1266
  %26 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1267
  %gid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %26, i32 0, i32 17, !dbg !1268
  store i64 %call18, i64* %gid, align 8, !dbg !1269
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1270
  %call19 = call i8* @archive_entry_uname(%struct.archive_entry* %27), !dbg !1272
  store i8* %call19, i8** %s, align 8, !dbg !1273
  %cmp20 = icmp ne i8* %call19, null, !dbg !1274
  br i1 %cmp20, label %if.then21, label %if.end31, !dbg !1275

if.then21:                                        ; preds = %if.end13
  %28 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1276
  %uname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %28, i32 0, i32 9, !dbg !1276
  %length22 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !1276
  store i64 0, i64* %length22, align 8, !dbg !1276
  %29 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1276
  %uname23 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %29, i32 0, i32 9, !dbg !1276
  %30 = load i8*, i8** %s, align 8, !dbg !1276
  %31 = load i8*, i8** %s, align 8, !dbg !1276
  %cmp24 = icmp eq i8* %31, null, !dbg !1276
  br i1 %cmp24, label %cond.true25, label %cond.false26, !dbg !1276

cond.true25:                                      ; preds = %if.then21
  br label %cond.end28, !dbg !1277

cond.false26:                                     ; preds = %if.then21
  %32 = load i8*, i8** %s, align 8, !dbg !1279
  %call27 = call i64 @strlen(i8* %32) #7, !dbg !1279
  br label %cond.end28, !dbg !1279

cond.end28:                                       ; preds = %cond.false26, %cond.true25
  %cond29 = phi i64 [ 0, %cond.true25 ], [ %call27, %cond.false26 ], !dbg !1281
  %call30 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %uname23, i8* %30, i64 %cond29), !dbg !1281
  br label %if.end31, !dbg !1281

if.end31:                                         ; preds = %cond.end28, %if.end13
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1283
  %call32 = call i8* @archive_entry_gname(%struct.archive_entry* %33), !dbg !1285
  store i8* %call32, i8** %s, align 8, !dbg !1286
  %cmp33 = icmp ne i8* %call32, null, !dbg !1287
  br i1 %cmp33, label %if.then34, label %if.end44, !dbg !1288

if.then34:                                        ; preds = %if.end31
  %34 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1289
  %gname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %34, i32 0, i32 10, !dbg !1289
  %length35 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !1289
  store i64 0, i64* %length35, align 8, !dbg !1289
  %35 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1289
  %gname36 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %35, i32 0, i32 10, !dbg !1289
  %36 = load i8*, i8** %s, align 8, !dbg !1289
  %37 = load i8*, i8** %s, align 8, !dbg !1289
  %cmp37 = icmp eq i8* %37, null, !dbg !1289
  br i1 %cmp37, label %cond.true38, label %cond.false39, !dbg !1289

cond.true38:                                      ; preds = %if.then34
  br label %cond.end41, !dbg !1290

cond.false39:                                     ; preds = %if.then34
  %38 = load i8*, i8** %s, align 8, !dbg !1292
  %call40 = call i64 @strlen(i8* %38) #7, !dbg !1292
  br label %cond.end41, !dbg !1292

cond.end41:                                       ; preds = %cond.false39, %cond.true38
  %cond42 = phi i64 [ 0, %cond.true38 ], [ %call40, %cond.false39 ], !dbg !1294
  %call43 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %gname36, i8* %36, i64 %cond42), !dbg !1294
  br label %if.end44, !dbg !1294

if.end44:                                         ; preds = %cond.end41, %if.end31
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1296
  %call45 = call i8* @archive_entry_fflags_text(%struct.archive_entry* %39), !dbg !1298
  store i8* %call45, i8** %s, align 8, !dbg !1299
  %cmp46 = icmp ne i8* %call45, null, !dbg !1300
  br i1 %cmp46, label %if.then47, label %if.end57, !dbg !1301

if.then47:                                        ; preds = %if.end44
  %40 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1302
  %fflags_text = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %40, i32 0, i32 11, !dbg !1302
  %length48 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text, i32 0, i32 1, !dbg !1302
  store i64 0, i64* %length48, align 8, !dbg !1302
  %41 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1302
  %fflags_text49 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %41, i32 0, i32 11, !dbg !1302
  %42 = load i8*, i8** %s, align 8, !dbg !1302
  %43 = load i8*, i8** %s, align 8, !dbg !1302
  %cmp50 = icmp eq i8* %43, null, !dbg !1302
  br i1 %cmp50, label %cond.true51, label %cond.false52, !dbg !1302

cond.true51:                                      ; preds = %if.then47
  br label %cond.end54, !dbg !1303

cond.false52:                                     ; preds = %if.then47
  %44 = load i8*, i8** %s, align 8, !dbg !1305
  %call53 = call i64 @strlen(i8* %44) #7, !dbg !1305
  br label %cond.end54, !dbg !1305

cond.end54:                                       ; preds = %cond.false52, %cond.true51
  %cond55 = phi i64 [ 0, %cond.true51 ], [ %call53, %cond.false52 ], !dbg !1307
  %call56 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %fflags_text49, i8* %42, i64 %cond55), !dbg !1307
  br label %if.end57, !dbg !1307

if.end57:                                         ; preds = %cond.end54, %if.end44
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1309
  %46 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1310
  %fflags_set = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %46, i32 0, i32 20, !dbg !1311
  %47 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1312
  %fflags_clear = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %47, i32 0, i32 21, !dbg !1313
  call void @archive_entry_fflags(%struct.archive_entry* %45, i64* %fflags_set, i64* %fflags_clear), !dbg !1314
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1315
  %call58 = call i64 @archive_entry_mtime(%struct.archive_entry* %48), !dbg !1316
  %49 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1317
  %mtime = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %49, i32 0, i32 18, !dbg !1318
  store i64 %call58, i64* %mtime, align 8, !dbg !1319
  %50 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1320
  %call59 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %50), !dbg !1321
  %51 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1322
  %mtime_nsec = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %51, i32 0, i32 19, !dbg !1323
  store i64 %call59, i64* %mtime_nsec, align 8, !dbg !1324
  %52 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1325
  %call60 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %52), !dbg !1326
  %53 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1327
  %rdevmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %53, i32 0, i32 22, !dbg !1328
  store i64 %call60, i64* %rdevmajor, align 8, !dbg !1329
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1330
  %call61 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %54), !dbg !1331
  %55 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1332
  %rdevminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %55, i32 0, i32 23, !dbg !1333
  store i64 %call61, i64* %rdevminor, align 8, !dbg !1334
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1335
  %call62 = call i64 @archive_entry_devmajor(%struct.archive_entry* %56), !dbg !1336
  %57 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1337
  %devmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %57, i32 0, i32 24, !dbg !1338
  store i64 %call62, i64* %devmajor, align 8, !dbg !1339
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1340
  %call63 = call i64 @archive_entry_devminor(%struct.archive_entry* %58), !dbg !1341
  %59 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1342
  %devminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %59, i32 0, i32 25, !dbg !1343
  store i64 %call63, i64* %devminor, align 8, !dbg !1344
  %60 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1345
  %call64 = call i64 @archive_entry_ino(%struct.archive_entry* %60), !dbg !1346
  %61 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1347
  %ino = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %61, i32 0, i32 26, !dbg !1348
  store i64 %call64, i64* %ino, align 8, !dbg !1349
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1350
  %call65 = call i64 @archive_entry_size(%struct.archive_entry* %62), !dbg !1351
  %63 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1352
  %size = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %63, i32 0, i32 15, !dbg !1353
  store i64 %call65, i64* %size, align 8, !dbg !1354
  %64 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1355
  %filetype66 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %64, i32 0, i32 13, !dbg !1357
  %65 = load i32, i32* %filetype66, align 4, !dbg !1357
  %cmp67 = icmp eq i32 %65, 16384, !dbg !1358
  br i1 %cmp67, label %if.then68, label %if.else, !dbg !1359

if.then68:                                        ; preds = %if.end57
  %call69 = call noalias i8* @calloc(i64 1, i64 48) #6, !dbg !1360
  %66 = bitcast i8* %call69 to %struct.dir_info*, !dbg !1360
  %67 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1362
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %67, i32 0, i32 3, !dbg !1363
  store %struct.dir_info* %66, %struct.dir_info** %dir_info, align 8, !dbg !1364
  %68 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1365
  %dir_info70 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %68, i32 0, i32 3, !dbg !1367
  %69 = load %struct.dir_info*, %struct.dir_info** %dir_info70, align 8, !dbg !1367
  %cmp71 = icmp eq %struct.dir_info* %69, null, !dbg !1368
  br i1 %cmp71, label %if.then72, label %if.end74, !dbg !1369

if.then72:                                        ; preds = %if.then68
  %70 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1370
  call void @mtree_entry_free(%struct.mtree_entry* %70), !dbg !1372
  %71 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1373
  %archive73 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %71, i32 0, i32 0, !dbg !1374
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive73, i32 12, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.37, i32 0, i32 0)), !dbg !1375
  %72 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !1376
  store %struct.mtree_entry* null, %struct.mtree_entry** %72, align 8, !dbg !1377
  store i32 -30, i32* %retval, align 4, !dbg !1378
  br label %return, !dbg !1378

if.end74:                                         ; preds = %if.then68
  %73 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1379
  %dir_info75 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %73, i32 0, i32 3, !dbg !1380
  %74 = load %struct.dir_info*, %struct.dir_info** %dir_info75, align 8, !dbg !1380
  %rbtree = getelementptr inbounds %struct.dir_info, %struct.dir_info* %74, i32 0, i32 0, !dbg !1381
  call void @__archive_rb_tree_init(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_tree_ops* @mtree_entry_new.rb_ops), !dbg !1382
  %75 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1383
  %dir_info76 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %75, i32 0, i32 3, !dbg !1384
  %76 = load %struct.dir_info*, %struct.dir_info** %dir_info76, align 8, !dbg !1384
  %children = getelementptr inbounds %struct.dir_info, %struct.dir_info* %76, i32 0, i32 1, !dbg !1385
  %first = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children, i32 0, i32 0, !dbg !1386
  store %struct.mtree_entry* null, %struct.mtree_entry** %first, align 8, !dbg !1387
  %77 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1388
  %dir_info77 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %77, i32 0, i32 3, !dbg !1389
  %78 = load %struct.dir_info*, %struct.dir_info** %dir_info77, align 8, !dbg !1389
  %children78 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %78, i32 0, i32 1, !dbg !1390
  %first79 = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children78, i32 0, i32 0, !dbg !1391
  %79 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1392
  %dir_info80 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %79, i32 0, i32 3, !dbg !1393
  %80 = load %struct.dir_info*, %struct.dir_info** %dir_info80, align 8, !dbg !1393
  %children81 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %80, i32 0, i32 1, !dbg !1394
  %last = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children81, i32 0, i32 1, !dbg !1395
  store %struct.mtree_entry** %first79, %struct.mtree_entry*** %last, align 8, !dbg !1396
  %81 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1397
  %dir_info82 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %81, i32 0, i32 3, !dbg !1398
  %82 = load %struct.dir_info*, %struct.dir_info** %dir_info82, align 8, !dbg !1398
  %chnext = getelementptr inbounds %struct.dir_info, %struct.dir_info* %82, i32 0, i32 2, !dbg !1399
  store %struct.mtree_entry* null, %struct.mtree_entry** %chnext, align 8, !dbg !1400
  br label %if.end94, !dbg !1401

if.else:                                          ; preds = %if.end57
  %83 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1402
  %filetype83 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %83, i32 0, i32 13, !dbg !1405
  %84 = load i32, i32* %filetype83, align 4, !dbg !1405
  %cmp84 = icmp eq i32 %84, 32768, !dbg !1406
  br i1 %cmp84, label %if.then85, label %if.end93, !dbg !1402

if.then85:                                        ; preds = %if.else
  %call86 = call noalias i8* @calloc(i64 1, i64 8) #6, !dbg !1407
  %85 = bitcast i8* %call86 to %struct.reg_info*, !dbg !1407
  %86 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1409
  %reg_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %86, i32 0, i32 4, !dbg !1410
  store %struct.reg_info* %85, %struct.reg_info** %reg_info, align 8, !dbg !1411
  %87 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1412
  %reg_info87 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %87, i32 0, i32 4, !dbg !1414
  %88 = load %struct.reg_info*, %struct.reg_info** %reg_info87, align 8, !dbg !1414
  %cmp88 = icmp eq %struct.reg_info* %88, null, !dbg !1415
  br i1 %cmp88, label %if.then89, label %if.end91, !dbg !1416

if.then89:                                        ; preds = %if.then85
  %89 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1417
  call void @mtree_entry_free(%struct.mtree_entry* %89), !dbg !1419
  %90 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1420
  %archive90 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %90, i32 0, i32 0, !dbg !1421
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive90, i32 12, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.37, i32 0, i32 0)), !dbg !1422
  %91 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !1423
  store %struct.mtree_entry* null, %struct.mtree_entry** %91, align 8, !dbg !1424
  store i32 -30, i32* %retval, align 4, !dbg !1425
  br label %return, !dbg !1425

if.end91:                                         ; preds = %if.then85
  %92 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1426
  %reg_info92 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %92, i32 0, i32 4, !dbg !1427
  %93 = load %struct.reg_info*, %struct.reg_info** %reg_info92, align 8, !dbg !1427
  %compute_sum = getelementptr inbounds %struct.reg_info, %struct.reg_info* %93, i32 0, i32 0, !dbg !1428
  store i32 0, i32* %compute_sum, align 4, !dbg !1429
  br label %if.end93, !dbg !1430

if.end93:                                         ; preds = %if.end91, %if.else
  br label %if.end94

if.end94:                                         ; preds = %if.end93, %if.end74
  %94 = load %struct.mtree_entry*, %struct.mtree_entry** %me, align 8, !dbg !1431
  %95 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !1432
  store %struct.mtree_entry* %94, %struct.mtree_entry** %95, align 8, !dbg !1433
  store i32 0, i32* %retval, align 4, !dbg !1434
  br label %return, !dbg !1434

return:                                           ; preds = %if.end94, %if.then89, %if.then72, %if.then4, %if.then
  %96 = load i32, i32* %retval, align 4, !dbg !1435
  ret i32 %96, !dbg !1435
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_tree_add(%struct.archive_write* %a, %struct.mtree_entry** %filep) #0 !dbg !358 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %filep.addr = alloca %struct.mtree_entry**, align 8
  %name = alloca [256 x i8], align 16
  %mtree = alloca %struct.mtree_writer*, align 8
  %dent = alloca %struct.mtree_entry*, align 8
  %file = alloca %struct.mtree_entry*, align 8
  %np = alloca %struct.mtree_entry*, align 8
  %fn = alloca i8*, align 8
  %p = alloca i8*, align 8
  %l = alloca i32, align 4
  %r = alloca i32, align 4
  %vp = alloca %struct.mtree_entry*, align 8
  %as = alloca %struct.archive_string, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1436, metadata !426), !dbg !1437
  store %struct.mtree_entry** %filep, %struct.mtree_entry*** %filep.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry*** %filep.addr, metadata !1438, metadata !426), !dbg !1439
  call void @llvm.dbg.declare(metadata [256 x i8]* %name, metadata !1440, metadata !426), !dbg !1442
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !1443, metadata !426), !dbg !1444
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1445
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1446
  %1 = load i8*, i8** %format_data, align 8, !dbg !1446
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !1447
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !1444
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %dent, metadata !1448, metadata !426), !dbg !1449
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file, metadata !1450, metadata !426), !dbg !1451
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %np, metadata !1452, metadata !426), !dbg !1453
  call void @llvm.dbg.declare(metadata i8** %fn, metadata !1454, metadata !426), !dbg !1455
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1456, metadata !426), !dbg !1457
  call void @llvm.dbg.declare(metadata i32* %l, metadata !1458, metadata !426), !dbg !1459
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1460, metadata !426), !dbg !1461
  %3 = load %struct.mtree_entry**, %struct.mtree_entry*** %filep.addr, align 8, !dbg !1462
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %3, align 8, !dbg !1463
  store %struct.mtree_entry* %4, %struct.mtree_entry** %file, align 8, !dbg !1464
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1465
  %parentdir = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %5, i32 0, i32 5, !dbg !1467
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir, i32 0, i32 1, !dbg !1468
  %6 = load i64, i64* %length, align 8, !dbg !1468
  %cmp = icmp eq i64 %6, 0, !dbg !1469
  br i1 %cmp, label %land.lhs.true, label %if.end12, !dbg !1470

land.lhs.true:                                    ; preds = %entry
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1471
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %7, i32 0, i32 6, !dbg !1473
  %length1 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 1, !dbg !1474
  %8 = load i64, i64* %length1, align 8, !dbg !1474
  %cmp2 = icmp eq i64 %8, 1, !dbg !1475
  br i1 %cmp2, label %land.lhs.true3, label %if.end12, !dbg !1476

land.lhs.true3:                                   ; preds = %land.lhs.true
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1477
  %basename4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 6, !dbg !1478
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename4, i32 0, i32 0, !dbg !1479
  %10 = load i8*, i8** %s, align 8, !dbg !1479
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 0, !dbg !1477
  %11 = load i8, i8* %arrayidx, align 1, !dbg !1477
  %conv = sext i8 %11 to i32, !dbg !1477
  %cmp5 = icmp eq i32 %conv, 46, !dbg !1480
  br i1 %cmp5, label %if.then, label %if.end12, !dbg !1481

if.then:                                          ; preds = %land.lhs.true3
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1483
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1485
  %parent = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 2, !dbg !1486
  store %struct.mtree_entry* %12, %struct.mtree_entry** %parent, align 8, !dbg !1487
  %14 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1488
  %root = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %14, i32 0, i32 1, !dbg !1490
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %root, align 8, !dbg !1490
  %cmp7 = icmp ne %struct.mtree_entry* %15, null, !dbg !1491
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !1492

if.then9:                                         ; preds = %if.then
  %16 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1493
  %root10 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %16, i32 0, i32 1, !dbg !1495
  %17 = load %struct.mtree_entry*, %struct.mtree_entry** %root10, align 8, !dbg !1495
  store %struct.mtree_entry* %17, %struct.mtree_entry** %np, align 8, !dbg !1496
  br label %same_entry, !dbg !1497

if.end:                                           ; preds = %if.then
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1498
  %19 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1499
  %root11 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %19, i32 0, i32 1, !dbg !1500
  store %struct.mtree_entry* %18, %struct.mtree_entry** %root11, align 8, !dbg !1501
  %20 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1502
  %21 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1503
  call void @mtree_entry_register_add(%struct.mtree_writer* %20, %struct.mtree_entry* %21), !dbg !1504
  store i32 0, i32* %retval, align 4, !dbg !1505
  br label %return, !dbg !1505

if.end12:                                         ; preds = %land.lhs.true3, %land.lhs.true, %entry
  %22 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1506
  %parentdir13 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %22, i32 0, i32 5, !dbg !1508
  %length14 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir13, i32 0, i32 1, !dbg !1509
  %23 = load i64, i64* %length14, align 8, !dbg !1509
  %cmp15 = icmp eq i64 %23, 0, !dbg !1510
  br i1 %cmp15, label %if.then17, label %if.end19, !dbg !1511

if.then17:                                        ; preds = %if.end12
  %24 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1512
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 0, !dbg !1514
  %25 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1515
  %pathname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %25, i32 0, i32 7, !dbg !1516
  %s18 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 0, !dbg !1517
  %26 = load i8*, i8** %s18, align 8, !dbg !1517
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.40, i32 0, i32 0), i8* %26), !dbg !1518
  store i32 -25, i32* %retval, align 4, !dbg !1519
  br label %return, !dbg !1519

if.end19:                                         ; preds = %if.end12
  %27 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1520
  %parentdir20 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %27, i32 0, i32 5, !dbg !1521
  %s21 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir20, i32 0, i32 0, !dbg !1522
  %28 = load i8*, i8** %s21, align 8, !dbg !1522
  store i8* %28, i8** %p, align 8, !dbg !1523
  store i8* %28, i8** %fn, align 8, !dbg !1524
  %29 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1525
  %cur_dirstr = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %29, i32 0, i32 3, !dbg !1525
  %length22 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cur_dirstr, i32 0, i32 1, !dbg !1525
  %30 = load i64, i64* %length22, align 8, !dbg !1525
  %31 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1527
  %parentdir23 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %31, i32 0, i32 5, !dbg !1527
  %length24 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir23, i32 0, i32 1, !dbg !1527
  %32 = load i64, i64* %length24, align 8, !dbg !1527
  %cmp25 = icmp eq i64 %30, %32, !dbg !1528
  br i1 %cmp25, label %land.lhs.true27, label %if.end44, !dbg !1529

land.lhs.true27:                                  ; preds = %if.end19
  %33 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1530
  %cur_dirstr28 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %33, i32 0, i32 3, !dbg !1531
  %s29 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cur_dirstr28, i32 0, i32 0, !dbg !1532
  %34 = load i8*, i8** %s29, align 8, !dbg !1532
  %35 = load i8*, i8** %fn, align 8, !dbg !1533
  %call = call i32 @strcmp(i8* %34, i8* %35) #7, !dbg !1534
  %cmp30 = icmp eq i32 %call, 0, !dbg !1535
  br i1 %cmp30, label %if.then32, label %if.end44, !dbg !1536

if.then32:                                        ; preds = %land.lhs.true27
  %36 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1538
  %cur_dirent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %36, i32 0, i32 2, !dbg !1541
  %37 = load %struct.mtree_entry*, %struct.mtree_entry** %cur_dirent, align 8, !dbg !1541
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %37, i32 0, i32 3, !dbg !1542
  %38 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !1542
  %rbtree = getelementptr inbounds %struct.dir_info, %struct.dir_info* %38, i32 0, i32 0, !dbg !1543
  %39 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1544
  %40 = bitcast %struct.mtree_entry* %39 to %struct.archive_rb_node*, !dbg !1545
  %call33 = call i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_node* %40), !dbg !1546
  %tobool = icmp ne i32 %call33, 0, !dbg !1546
  br i1 %tobool, label %if.end41, label %if.then34, !dbg !1547

if.then34:                                        ; preds = %if.then32
  %41 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1548
  %cur_dirent35 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %41, i32 0, i32 2, !dbg !1550
  %42 = load %struct.mtree_entry*, %struct.mtree_entry** %cur_dirent35, align 8, !dbg !1550
  %dir_info36 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %42, i32 0, i32 3, !dbg !1551
  %43 = load %struct.dir_info*, %struct.dir_info** %dir_info36, align 8, !dbg !1551
  %rbtree37 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %43, i32 0, i32 0, !dbg !1552
  %44 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1553
  %basename38 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %44, i32 0, i32 6, !dbg !1554
  %s39 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename38, i32 0, i32 0, !dbg !1555
  %45 = load i8*, i8** %s39, align 8, !dbg !1555
  %call40 = call %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %rbtree37, i8* %45), !dbg !1556
  %46 = bitcast %struct.archive_rb_node* %call40 to %struct.mtree_entry*, !dbg !1557
  store %struct.mtree_entry* %46, %struct.mtree_entry** %np, align 8, !dbg !1558
  br label %same_entry, !dbg !1559

if.end41:                                         ; preds = %if.then32
  %47 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1560
  %cur_dirent42 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %47, i32 0, i32 2, !dbg !1561
  %48 = load %struct.mtree_entry*, %struct.mtree_entry** %cur_dirent42, align 8, !dbg !1561
  %49 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1562
  %parent43 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %49, i32 0, i32 2, !dbg !1563
  store %struct.mtree_entry* %48, %struct.mtree_entry** %parent43, align 8, !dbg !1564
  %50 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1565
  %51 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1566
  call void @mtree_entry_register_add(%struct.mtree_writer* %50, %struct.mtree_entry* %51), !dbg !1567
  store i32 0, i32* %retval, align 4, !dbg !1568
  br label %return, !dbg !1568

if.end44:                                         ; preds = %land.lhs.true27, %if.end19
  %52 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1569
  %root45 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %52, i32 0, i32 1, !dbg !1570
  %53 = load %struct.mtree_entry*, %struct.mtree_entry** %root45, align 8, !dbg !1570
  store %struct.mtree_entry* %53, %struct.mtree_entry** %dent, align 8, !dbg !1571
  br label %for.cond, !dbg !1572

for.cond:                                         ; preds = %if.end105, %if.end76, %if.end44
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %name, i32 0, i32 0, !dbg !1573
  %54 = load i8*, i8** %fn, align 8, !dbg !1577
  %call46 = call i32 @get_path_component(i8* %arraydecay, i64 256, i8* %54), !dbg !1578
  store i32 %call46, i32* %l, align 4, !dbg !1579
  %55 = load i32, i32* %l, align 4, !dbg !1580
  %cmp47 = icmp eq i32 %55, 0, !dbg !1582
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !1583

if.then49:                                        ; preds = %for.cond
  store %struct.mtree_entry* null, %struct.mtree_entry** %np, align 8, !dbg !1584
  br label %for.end, !dbg !1586

if.end50:                                         ; preds = %for.cond
  %56 = load i32, i32* %l, align 4, !dbg !1587
  %cmp51 = icmp slt i32 %56, 0, !dbg !1589
  br i1 %cmp51, label %if.then53, label %if.end55, !dbg !1590

if.then53:                                        ; preds = %if.end50
  %57 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1591
  %archive54 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %57, i32 0, i32 0, !dbg !1593
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive54, i32 -1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.41, i32 0, i32 0)), !dbg !1594
  store i32 -30, i32* %retval, align 4, !dbg !1595
  br label %return, !dbg !1595

if.end55:                                         ; preds = %if.end50
  %58 = load i32, i32* %l, align 4, !dbg !1596
  %cmp56 = icmp eq i32 %58, 1, !dbg !1598
  br i1 %cmp56, label %land.lhs.true58, label %if.end77, !dbg !1599

land.lhs.true58:                                  ; preds = %if.end55
  %arrayidx59 = getelementptr inbounds [256 x i8], [256 x i8]* %name, i64 0, i64 0, !dbg !1600
  %59 = load i8, i8* %arrayidx59, align 16, !dbg !1600
  %conv60 = sext i8 %59 to i32, !dbg !1600
  %cmp61 = icmp eq i32 %conv60, 46, !dbg !1602
  br i1 %cmp61, label %land.lhs.true63, label %if.end77, !dbg !1603

land.lhs.true63:                                  ; preds = %land.lhs.true58
  %60 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1604
  %cmp64 = icmp ne %struct.mtree_entry* %60, null, !dbg !1606
  br i1 %cmp64, label %land.lhs.true66, label %if.end77, !dbg !1607

land.lhs.true66:                                  ; preds = %land.lhs.true63
  %61 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1608
  %62 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1609
  %root67 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %62, i32 0, i32 1, !dbg !1610
  %63 = load %struct.mtree_entry*, %struct.mtree_entry** %root67, align 8, !dbg !1610
  %cmp68 = icmp eq %struct.mtree_entry* %61, %63, !dbg !1611
  br i1 %cmp68, label %if.then70, label %if.end77, !dbg !1612

if.then70:                                        ; preds = %land.lhs.true66
  %64 = load i32, i32* %l, align 4, !dbg !1614
  %65 = load i8*, i8** %fn, align 8, !dbg !1616
  %idx.ext = sext i32 %64 to i64, !dbg !1616
  %add.ptr = getelementptr inbounds i8, i8* %65, i64 %idx.ext, !dbg !1616
  store i8* %add.ptr, i8** %fn, align 8, !dbg !1616
  %66 = load i8*, i8** %fn, align 8, !dbg !1617
  %arrayidx71 = getelementptr inbounds i8, i8* %66, i64 0, !dbg !1617
  %67 = load i8, i8* %arrayidx71, align 1, !dbg !1617
  %conv72 = sext i8 %67 to i32, !dbg !1617
  %cmp73 = icmp eq i32 %conv72, 47, !dbg !1619
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !1620

if.then75:                                        ; preds = %if.then70
  %68 = load i8*, i8** %fn, align 8, !dbg !1621
  %incdec.ptr = getelementptr inbounds i8, i8* %68, i32 1, !dbg !1621
  store i8* %incdec.ptr, i8** %fn, align 8, !dbg !1621
  br label %if.end76, !dbg !1622

if.end76:                                         ; preds = %if.then75, %if.then70
  br label %for.cond, !dbg !1623

if.end77:                                         ; preds = %land.lhs.true66, %land.lhs.true63, %land.lhs.true58, %if.end55
  %69 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1624
  %arraydecay78 = getelementptr inbounds [256 x i8], [256 x i8]* %name, i32 0, i32 0, !dbg !1625
  %call79 = call %struct.mtree_entry* @mtree_entry_find_child(%struct.mtree_entry* %69, i8* %arraydecay78), !dbg !1626
  store %struct.mtree_entry* %call79, %struct.mtree_entry** %np, align 8, !dbg !1627
  %70 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1628
  %cmp80 = icmp eq %struct.mtree_entry* %70, null, !dbg !1630
  br i1 %cmp80, label %if.then86, label %lor.lhs.false, !dbg !1631

lor.lhs.false:                                    ; preds = %if.end77
  %71 = load i8*, i8** %fn, align 8, !dbg !1632
  %arrayidx82 = getelementptr inbounds i8, i8* %71, i64 0, !dbg !1632
  %72 = load i8, i8* %arrayidx82, align 1, !dbg !1632
  %conv83 = sext i8 %72 to i32, !dbg !1632
  %cmp84 = icmp eq i32 %conv83, 0, !dbg !1634
  br i1 %cmp84, label %if.then86, label %if.end87, !dbg !1635

if.then86:                                        ; preds = %lor.lhs.false, %if.end77
  br label %for.end, !dbg !1636

if.end87:                                         ; preds = %lor.lhs.false
  %73 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1637
  %dir_info88 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %73, i32 0, i32 3, !dbg !1639
  %74 = load %struct.dir_info*, %struct.dir_info** %dir_info88, align 8, !dbg !1639
  %tobool89 = icmp ne %struct.dir_info* %74, null, !dbg !1637
  br i1 %tobool89, label %if.end96, label %if.then90, !dbg !1640

if.then90:                                        ; preds = %if.end87
  %75 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1641
  %archive91 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %75, i32 0, i32 0, !dbg !1643
  %76 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1644
  %pathname92 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %76, i32 0, i32 7, !dbg !1645
  %s93 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname92, i32 0, i32 0, !dbg !1646
  %77 = load i8*, i8** %s93, align 8, !dbg !1646
  %78 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1647
  %pathname94 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %78, i32 0, i32 7, !dbg !1648
  %s95 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname94, i32 0, i32 0, !dbg !1649
  %79 = load i8*, i8** %s95, align 8, !dbg !1649
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive91, i32 -1, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.42, i32 0, i32 0), i8* %77, i8* %79), !dbg !1650
  store i32 -25, i32* %retval, align 4, !dbg !1651
  br label %return, !dbg !1651

if.end96:                                         ; preds = %if.end87
  %80 = load i32, i32* %l, align 4, !dbg !1652
  %81 = load i8*, i8** %fn, align 8, !dbg !1653
  %idx.ext97 = sext i32 %80 to i64, !dbg !1653
  %add.ptr98 = getelementptr inbounds i8, i8* %81, i64 %idx.ext97, !dbg !1653
  store i8* %add.ptr98, i8** %fn, align 8, !dbg !1653
  %82 = load i8*, i8** %fn, align 8, !dbg !1654
  %arrayidx99 = getelementptr inbounds i8, i8* %82, i64 0, !dbg !1654
  %83 = load i8, i8* %arrayidx99, align 1, !dbg !1654
  %conv100 = sext i8 %83 to i32, !dbg !1654
  %cmp101 = icmp eq i32 %conv100, 47, !dbg !1656
  br i1 %cmp101, label %if.then103, label %if.end105, !dbg !1657

if.then103:                                       ; preds = %if.end96
  %84 = load i8*, i8** %fn, align 8, !dbg !1658
  %incdec.ptr104 = getelementptr inbounds i8, i8* %84, i32 1, !dbg !1658
  store i8* %incdec.ptr104, i8** %fn, align 8, !dbg !1658
  br label %if.end105, !dbg !1659

if.end105:                                        ; preds = %if.then103, %if.end96
  %85 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1660
  store %struct.mtree_entry* %85, %struct.mtree_entry** %dent, align 8, !dbg !1661
  br label %for.cond, !dbg !1662

for.end:                                          ; preds = %if.then86, %if.then49
  %86 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1664
  %cmp106 = icmp eq %struct.mtree_entry* %86, null, !dbg !1666
  br i1 %cmp106, label %if.then108, label %if.end215, !dbg !1667

if.then108:                                       ; preds = %for.end
  br label %while.cond, !dbg !1668

while.cond:                                       ; preds = %if.end164, %if.then108
  %87 = load i8*, i8** %fn, align 8, !dbg !1670
  %arrayidx109 = getelementptr inbounds i8, i8* %87, i64 0, !dbg !1670
  %88 = load i8, i8* %arrayidx109, align 1, !dbg !1670
  %conv110 = sext i8 %88 to i32, !dbg !1670
  %cmp111 = icmp ne i32 %conv110, 0, !dbg !1672
  br i1 %cmp111, label %while.body, label %while.end, !dbg !1673

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %vp, metadata !1674, metadata !426), !dbg !1676
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !1677, metadata !426), !dbg !1678
  br label %do.body, !dbg !1679

do.body:                                          ; preds = %while.body
  %s113 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1680
  store i8* null, i8** %s113, align 8, !dbg !1680
  %length114 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1680
  store i64 0, i64* %length114, align 8, !dbg !1680
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !1680
  store i64 0, i64* %buffer_length, align 8, !dbg !1680
  br label %do.end, !dbg !1680

do.end:                                           ; preds = %do.body
  %89 = load i8*, i8** %p, align 8, !dbg !1683
  %90 = load i8*, i8** %fn, align 8, !dbg !1684
  %91 = load i8*, i8** %p, align 8, !dbg !1685
  %sub.ptr.lhs.cast = ptrtoint i8* %90 to i64, !dbg !1686
  %sub.ptr.rhs.cast = ptrtoint i8* %91 to i64, !dbg !1686
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1686
  %92 = load i32, i32* %l, align 4, !dbg !1687
  %conv115 = sext i32 %92 to i64, !dbg !1687
  %add = add nsw i64 %sub.ptr.sub, %conv115, !dbg !1688
  %call116 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %89, i64 %add), !dbg !1689
  %length117 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1690
  %93 = load i64, i64* %length117, align 8, !dbg !1690
  %sub = sub i64 %93, 1, !dbg !1692
  %s118 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1693
  %94 = load i8*, i8** %s118, align 8, !dbg !1693
  %arrayidx119 = getelementptr inbounds i8, i8* %94, i64 %sub, !dbg !1694
  %95 = load i8, i8* %arrayidx119, align 1, !dbg !1694
  %conv120 = sext i8 %95 to i32, !dbg !1694
  %cmp121 = icmp eq i32 %conv120, 47, !dbg !1695
  br i1 %cmp121, label %if.then123, label %if.end129, !dbg !1696

if.then123:                                       ; preds = %do.end
  %length124 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1697
  %96 = load i64, i64* %length124, align 8, !dbg !1697
  %sub125 = sub i64 %96, 1, !dbg !1699
  %s126 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1700
  %97 = load i8*, i8** %s126, align 8, !dbg !1700
  %arrayidx127 = getelementptr inbounds i8, i8* %97, i64 %sub125, !dbg !1701
  store i8 0, i8* %arrayidx127, align 1, !dbg !1702
  %length128 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1703
  %98 = load i64, i64* %length128, align 8, !dbg !1704
  %dec = add i64 %98, -1, !dbg !1704
  store i64 %dec, i64* %length128, align 8, !dbg !1704
  br label %if.end129, !dbg !1705

if.end129:                                        ; preds = %if.then123, %do.end
  %99 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1706
  %s130 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1707
  %100 = load i8*, i8** %s130, align 8, !dbg !1707
  %call131 = call i32 @mtree_entry_create_virtual_dir(%struct.archive_write* %99, i8* %100, %struct.mtree_entry** %vp), !dbg !1708
  store i32 %call131, i32* %r, align 4, !dbg !1709
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1710
  %101 = load i32, i32* %r, align 4, !dbg !1711
  %cmp132 = icmp slt i32 %101, -20, !dbg !1713
  br i1 %cmp132, label %if.then134, label %if.end135, !dbg !1714

if.then134:                                       ; preds = %if.end129
  %102 = load i32, i32* %r, align 4, !dbg !1715
  store i32 %102, i32* %retval, align 4, !dbg !1716
  br label %return, !dbg !1716

if.end135:                                        ; preds = %if.end129
  %103 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1717
  %pathname136 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %103, i32 0, i32 7, !dbg !1719
  %s137 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname136, i32 0, i32 0, !dbg !1720
  %104 = load i8*, i8** %s137, align 8, !dbg !1720
  %call138 = call i32 @strcmp(i8* %104, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.38, i32 0, i32 0)) #7, !dbg !1721
  %cmp139 = icmp eq i32 %call138, 0, !dbg !1722
  br i1 %cmp139, label %if.then141, label %if.else, !dbg !1723

if.then141:                                       ; preds = %if.end135
  %105 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1724
  %106 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1726
  %parent142 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %106, i32 0, i32 2, !dbg !1727
  store %struct.mtree_entry* %105, %struct.mtree_entry** %parent142, align 8, !dbg !1728
  %107 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1729
  %108 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1730
  %root143 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %108, i32 0, i32 1, !dbg !1731
  store %struct.mtree_entry* %107, %struct.mtree_entry** %root143, align 8, !dbg !1732
  br label %if.end148, !dbg !1733

if.else:                                          ; preds = %if.end135
  %109 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1734
  %dir_info144 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %109, i32 0, i32 3, !dbg !1736
  %110 = load %struct.dir_info*, %struct.dir_info** %dir_info144, align 8, !dbg !1736
  %rbtree145 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %110, i32 0, i32 0, !dbg !1737
  %111 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1738
  %112 = bitcast %struct.mtree_entry* %111 to %struct.archive_rb_node*, !dbg !1739
  %call146 = call i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %rbtree145, %struct.archive_rb_node* %112), !dbg !1740
  %113 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1741
  %114 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1742
  %parent147 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %114, i32 0, i32 2, !dbg !1743
  store %struct.mtree_entry* %113, %struct.mtree_entry** %parent147, align 8, !dbg !1744
  br label %if.end148

if.end148:                                        ; preds = %if.else, %if.then141
  %115 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1745
  %116 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1746
  call void @mtree_entry_register_add(%struct.mtree_writer* %115, %struct.mtree_entry* %116), !dbg !1747
  %117 = load %struct.mtree_entry*, %struct.mtree_entry** %vp, align 8, !dbg !1748
  store %struct.mtree_entry* %117, %struct.mtree_entry** %np, align 8, !dbg !1749
  %118 = load i32, i32* %l, align 4, !dbg !1750
  %119 = load i8*, i8** %fn, align 8, !dbg !1751
  %idx.ext149 = sext i32 %118 to i64, !dbg !1751
  %add.ptr150 = getelementptr inbounds i8, i8* %119, i64 %idx.ext149, !dbg !1751
  store i8* %add.ptr150, i8** %fn, align 8, !dbg !1751
  %120 = load i8*, i8** %fn, align 8, !dbg !1752
  %arrayidx151 = getelementptr inbounds i8, i8* %120, i64 0, !dbg !1752
  %121 = load i8, i8* %arrayidx151, align 1, !dbg !1752
  %conv152 = sext i8 %121 to i32, !dbg !1752
  %cmp153 = icmp eq i32 %conv152, 47, !dbg !1754
  br i1 %cmp153, label %if.then155, label %if.end157, !dbg !1755

if.then155:                                       ; preds = %if.end148
  %122 = load i8*, i8** %fn, align 8, !dbg !1756
  %incdec.ptr156 = getelementptr inbounds i8, i8* %122, i32 1, !dbg !1756
  store i8* %incdec.ptr156, i8** %fn, align 8, !dbg !1756
  br label %if.end157, !dbg !1757

if.end157:                                        ; preds = %if.then155, %if.end148
  %arraydecay158 = getelementptr inbounds [256 x i8], [256 x i8]* %name, i32 0, i32 0, !dbg !1758
  %123 = load i8*, i8** %fn, align 8, !dbg !1759
  %call159 = call i32 @get_path_component(i8* %arraydecay158, i64 256, i8* %123), !dbg !1760
  store i32 %call159, i32* %l, align 4, !dbg !1761
  %124 = load i32, i32* %l, align 4, !dbg !1762
  %cmp160 = icmp slt i32 %124, 0, !dbg !1764
  br i1 %cmp160, label %if.then162, label %if.end164, !dbg !1765

if.then162:                                       ; preds = %if.end157
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1766
  %125 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1768
  %archive163 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %125, i32 0, i32 0, !dbg !1769
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive163, i32 -1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.41, i32 0, i32 0)), !dbg !1770
  store i32 -30, i32* %retval, align 4, !dbg !1771
  br label %return, !dbg !1771

if.end164:                                        ; preds = %if.end157
  %126 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1772
  store %struct.mtree_entry* %126, %struct.mtree_entry** %dent, align 8, !dbg !1773
  br label %while.cond, !dbg !1774

while.end:                                        ; preds = %while.cond
  %127 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1776
  %128 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1777
  %cur_dirent165 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %128, i32 0, i32 2, !dbg !1778
  store %struct.mtree_entry* %127, %struct.mtree_entry** %cur_dirent165, align 8, !dbg !1779
  %129 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1780
  %cur_dirstr166 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %129, i32 0, i32 3, !dbg !1780
  %length167 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cur_dirstr166, i32 0, i32 1, !dbg !1780
  store i64 0, i64* %length167, align 8, !dbg !1780
  %130 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1781
  %cur_dirstr168 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %130, i32 0, i32 3, !dbg !1782
  %131 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1783
  %parentdir169 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %131, i32 0, i32 5, !dbg !1783
  %length170 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir169, i32 0, i32 1, !dbg !1783
  %132 = load i64, i64* %length170, align 8, !dbg !1783
  %133 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1784
  %basename171 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %133, i32 0, i32 6, !dbg !1784
  %length172 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename171, i32 0, i32 1, !dbg !1784
  %134 = load i64, i64* %length172, align 8, !dbg !1784
  %add173 = add i64 %132, %134, !dbg !1785
  %add174 = add i64 %add173, 2, !dbg !1786
  %call175 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %cur_dirstr168, i64 %add174), !dbg !1787
  %135 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1788
  %parentdir176 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %135, i32 0, i32 5, !dbg !1788
  %length177 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir176, i32 0, i32 1, !dbg !1788
  %136 = load i64, i64* %length177, align 8, !dbg !1788
  %137 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1790
  %basename178 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %137, i32 0, i32 6, !dbg !1790
  %length179 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename178, i32 0, i32 1, !dbg !1790
  %138 = load i64, i64* %length179, align 8, !dbg !1790
  %add180 = add i64 %136, %138, !dbg !1791
  %cmp181 = icmp eq i64 %add180, 0, !dbg !1792
  br i1 %cmp181, label %if.then183, label %if.else187, !dbg !1793

if.then183:                                       ; preds = %while.end
  %139 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1794
  %cur_dirstr184 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %139, i32 0, i32 3, !dbg !1795
  %s185 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cur_dirstr184, i32 0, i32 0, !dbg !1796
  %140 = load i8*, i8** %s185, align 8, !dbg !1796
  %arrayidx186 = getelementptr inbounds i8, i8* %140, i64 0, !dbg !1794
  store i8 0, i8* %arrayidx186, align 1, !dbg !1797
  br label %if.end202, !dbg !1794

if.else187:                                       ; preds = %while.end
  %141 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1798
  %parentdir188 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %141, i32 0, i32 5, !dbg !1798
  %length189 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir188, i32 0, i32 1, !dbg !1798
  %142 = load i64, i64* %length189, align 8, !dbg !1798
  %cmp190 = icmp ugt i64 %142, 0, !dbg !1801
  br i1 %cmp190, label %if.then192, label %if.end199, !dbg !1802

if.then192:                                       ; preds = %if.else187
  %143 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1803
  %cur_dirstr193 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %143, i32 0, i32 3, !dbg !1803
  %length194 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cur_dirstr193, i32 0, i32 1, !dbg !1803
  store i64 0, i64* %length194, align 8, !dbg !1803
  %144 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1803
  %cur_dirstr195 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %144, i32 0, i32 3, !dbg !1803
  %145 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1803
  %parentdir196 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %145, i32 0, i32 5, !dbg !1803
  call void @archive_string_concat(%struct.archive_string* %cur_dirstr195, %struct.archive_string* %parentdir196), !dbg !1803
  %146 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1805
  %cur_dirstr197 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %146, i32 0, i32 3, !dbg !1806
  %call198 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %cur_dirstr197, i8 signext 47), !dbg !1807
  br label %if.end199, !dbg !1808

if.end199:                                        ; preds = %if.then192, %if.else187
  %147 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1809
  %cur_dirstr200 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %147, i32 0, i32 3, !dbg !1810
  %148 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1811
  %basename201 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %148, i32 0, i32 6, !dbg !1812
  call void @archive_string_concat(%struct.archive_string* %cur_dirstr200, %struct.archive_string* %basename201), !dbg !1813
  br label %if.end202

if.end202:                                        ; preds = %if.end199, %if.then183
  %149 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1814
  %dir_info203 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %149, i32 0, i32 3, !dbg !1816
  %150 = load %struct.dir_info*, %struct.dir_info** %dir_info203, align 8, !dbg !1816
  %rbtree204 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %150, i32 0, i32 0, !dbg !1817
  %151 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1818
  %152 = bitcast %struct.mtree_entry* %151 to %struct.archive_rb_node*, !dbg !1819
  %call205 = call i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %rbtree204, %struct.archive_rb_node* %152), !dbg !1820
  %tobool206 = icmp ne i32 %call205, 0, !dbg !1820
  br i1 %tobool206, label %if.end213, label %if.then207, !dbg !1821

if.then207:                                       ; preds = %if.end202
  %153 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1822
  %dir_info208 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %153, i32 0, i32 3, !dbg !1824
  %154 = load %struct.dir_info*, %struct.dir_info** %dir_info208, align 8, !dbg !1824
  %rbtree209 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %154, i32 0, i32 0, !dbg !1825
  %155 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1826
  %basename210 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %155, i32 0, i32 6, !dbg !1827
  %s211 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename210, i32 0, i32 0, !dbg !1828
  %156 = load i8*, i8** %s211, align 8, !dbg !1828
  %call212 = call %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %rbtree209, i8* %156), !dbg !1829
  %157 = bitcast %struct.archive_rb_node* %call212 to %struct.mtree_entry*, !dbg !1830
  store %struct.mtree_entry* %157, %struct.mtree_entry** %np, align 8, !dbg !1831
  br label %same_entry, !dbg !1832

if.end213:                                        ; preds = %if.end202
  %158 = load %struct.mtree_entry*, %struct.mtree_entry** %dent, align 8, !dbg !1833
  %159 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1834
  %parent214 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %159, i32 0, i32 2, !dbg !1835
  store %struct.mtree_entry* %158, %struct.mtree_entry** %parent214, align 8, !dbg !1836
  %160 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !1837
  %161 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1838
  call void @mtree_entry_register_add(%struct.mtree_writer* %160, %struct.mtree_entry* %161), !dbg !1839
  store i32 0, i32* %retval, align 4, !dbg !1840
  br label %return, !dbg !1840

if.end215:                                        ; preds = %for.end
  br label %same_entry, !dbg !1841

same_entry:                                       ; preds = %if.end215, %if.then207, %if.then34, %if.then9
  %162 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1843
  %163 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1844
  %164 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1845
  %call216 = call i32 @mtree_entry_exchange_same_entry(%struct.archive_write* %162, %struct.mtree_entry* %163, %struct.mtree_entry* %164), !dbg !1846
  store i32 %call216, i32* %r, align 4, !dbg !1847
  %165 = load i32, i32* %r, align 4, !dbg !1848
  %cmp217 = icmp slt i32 %165, -20, !dbg !1850
  br i1 %cmp217, label %if.then219, label %if.end220, !dbg !1851

if.then219:                                       ; preds = %same_entry
  %166 = load i32, i32* %r, align 4, !dbg !1852
  store i32 %166, i32* %retval, align 4, !dbg !1853
  br label %return, !dbg !1853

if.end220:                                        ; preds = %same_entry
  %167 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1854
  %dir_info221 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %167, i32 0, i32 3, !dbg !1856
  %168 = load %struct.dir_info*, %struct.dir_info** %dir_info221, align 8, !dbg !1856
  %tobool222 = icmp ne %struct.dir_info* %168, null, !dbg !1854
  br i1 %tobool222, label %if.then223, label %if.end225, !dbg !1857

if.then223:                                       ; preds = %if.end220
  %169 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1858
  %dir_info224 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %169, i32 0, i32 3, !dbg !1859
  %170 = load %struct.dir_info*, %struct.dir_info** %dir_info224, align 8, !dbg !1859
  %virtual = getelementptr inbounds %struct.dir_info, %struct.dir_info* %170, i32 0, i32 3, !dbg !1860
  store i32 0, i32* %virtual, align 8, !dbg !1861
  br label %if.end225, !dbg !1858

if.end225:                                        ; preds = %if.then223, %if.end220
  %171 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !1862
  %172 = load %struct.mtree_entry**, %struct.mtree_entry*** %filep.addr, align 8, !dbg !1863
  store %struct.mtree_entry* %171, %struct.mtree_entry** %172, align 8, !dbg !1864
  %173 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !1865
  call void @mtree_entry_free(%struct.mtree_entry* %173), !dbg !1866
  store i32 -20, i32* %retval, align 4, !dbg !1867
  br label %return, !dbg !1867

return:                                           ; preds = %if.end225, %if.then219, %if.end213, %if.then162, %if.then134, %if.then90, %if.then53, %if.end41, %if.then17, %if.end
  %174 = load i32, i32* %retval, align 4, !dbg !1868
  ret i32 %174, !dbg !1868
}

; Function Attrs: nounwind uwtable
define internal void @sum_init(%struct.mtree_writer* %mtree) #0 !dbg !376 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !1869, metadata !426), !dbg !1870
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1871
  %compute_sum = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 13, !dbg !1872
  store i32 0, i32* %compute_sum, align 8, !dbg !1873
  %1 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1874
  %keys = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %1, i32 0, i32 16, !dbg !1876
  %2 = load i32, i32* %keys, align 8, !dbg !1876
  %and = and i32 %2, 1, !dbg !1877
  %tobool = icmp ne i32 %and, 0, !dbg !1877
  br i1 %tobool, label %if.then, label %if.end, !dbg !1878

if.then:                                          ; preds = %entry
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1879
  %compute_sum1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %3, i32 0, i32 13, !dbg !1881
  %4 = load i32, i32* %compute_sum1, align 8, !dbg !1882
  %or = or i32 %4, 1, !dbg !1882
  store i32 %or, i32* %compute_sum1, align 8, !dbg !1882
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1883
  %crc = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 14, !dbg !1884
  store i32 0, i32* %crc, align 4, !dbg !1885
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !1886
  %crc_len = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 15, !dbg !1887
  store i64 0, i64* %crc_len, align 8, !dbg !1888
  br label %if.end, !dbg !1889

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !1890
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_cmp_node(%struct.archive_rb_node* %n1, %struct.archive_rb_node* %n2) #0 !dbg !353 {
entry:
  %n1.addr = alloca %struct.archive_rb_node*, align 8
  %n2.addr = alloca %struct.archive_rb_node*, align 8
  %e1 = alloca %struct.mtree_entry*, align 8
  %e2 = alloca %struct.mtree_entry*, align 8
  store %struct.archive_rb_node* %n1, %struct.archive_rb_node** %n1.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n1.addr, metadata !1891, metadata !426), !dbg !1892
  store %struct.archive_rb_node* %n2, %struct.archive_rb_node** %n2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n2.addr, metadata !1893, metadata !426), !dbg !1894
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %e1, metadata !1895, metadata !426), !dbg !1896
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n1.addr, align 8, !dbg !1897
  %1 = bitcast %struct.archive_rb_node* %0 to %struct.mtree_entry*, !dbg !1898
  store %struct.mtree_entry* %1, %struct.mtree_entry** %e1, align 8, !dbg !1896
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %e2, metadata !1899, metadata !426), !dbg !1900
  %2 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n2.addr, align 8, !dbg !1901
  %3 = bitcast %struct.archive_rb_node* %2 to %struct.mtree_entry*, !dbg !1902
  store %struct.mtree_entry* %3, %struct.mtree_entry** %e2, align 8, !dbg !1900
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %e2, align 8, !dbg !1903
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %4, i32 0, i32 6, !dbg !1904
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 0, !dbg !1905
  %5 = load i8*, i8** %s, align 8, !dbg !1905
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %e1, align 8, !dbg !1906
  %basename1 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 6, !dbg !1907
  %s2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename1, i32 0, i32 0, !dbg !1908
  %7 = load i8*, i8** %s2, align 8, !dbg !1908
  %call = call i32 @strcmp(i8* %5, i8* %7) #7, !dbg !1909
  ret i32 %call, !dbg !1910
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_cmp_key(%struct.archive_rb_node* %n, i8* %key) #0 !dbg !354 {
entry:
  %n.addr = alloca %struct.archive_rb_node*, align 8
  %key.addr = alloca i8*, align 8
  %e = alloca %struct.mtree_entry*, align 8
  store %struct.archive_rb_node* %n, %struct.archive_rb_node** %n.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n.addr, metadata !1911, metadata !426), !dbg !1912
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !1913, metadata !426), !dbg !1914
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %e, metadata !1915, metadata !426), !dbg !1916
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n.addr, align 8, !dbg !1917
  %1 = bitcast %struct.archive_rb_node* %0 to %struct.mtree_entry*, !dbg !1918
  store %struct.mtree_entry* %1, %struct.mtree_entry** %e, align 8, !dbg !1916
  %2 = load i8*, i8** %key.addr, align 8, !dbg !1919
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %e, align 8, !dbg !1920
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 6, !dbg !1921
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 0, !dbg !1922
  %4 = load i8*, i8** %s, align 8, !dbg !1922
  %call = call i32 @strcmp(i8* %2, i8* %4) #7, !dbg !1923
  ret i32 %call, !dbg !1924
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_setup_filenames(%struct.archive_write* %a, %struct.mtree_entry* %file, %struct.archive_entry* %entry1) #0 !dbg !355 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %file.addr = alloca %struct.mtree_entry*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %pathname = alloca i8*, align 8
  %p = alloca i8*, align 8
  %dirname = alloca i8*, align 8
  %slash = alloca i8*, align 8
  %len = alloca i64, align 8
  %ret = alloca i32, align 4
  %ll = alloca i64, align 8
  %rp = alloca i8*, align 8
  %as = alloca %struct.archive_string, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1925, metadata !426), !dbg !1926
  store %struct.mtree_entry* %file, %struct.mtree_entry** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file.addr, metadata !1927, metadata !426), !dbg !1928
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1929, metadata !426), !dbg !1930
  call void @llvm.dbg.declare(metadata i8** %pathname, metadata !1931, metadata !426), !dbg !1932
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1933, metadata !426), !dbg !1934
  call void @llvm.dbg.declare(metadata i8** %dirname, metadata !1935, metadata !426), !dbg !1936
  call void @llvm.dbg.declare(metadata i8** %slash, metadata !1937, metadata !426), !dbg !1938
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1939, metadata !426), !dbg !1940
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1941, metadata !426), !dbg !1942
  store i32 0, i32* %ret, align 4, !dbg !1942
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1943
  %pathname2 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 7, !dbg !1943
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname2, i32 0, i32 1, !dbg !1943
  store i64 0, i64* %length, align 8, !dbg !1943
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1943
  %pathname3 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %1, i32 0, i32 7, !dbg !1943
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1943
  %call = call i8* @archive_entry_pathname(%struct.archive_entry* %2), !dbg !1943
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1943
  %call4 = call i8* @archive_entry_pathname(%struct.archive_entry* %3), !dbg !1944
  %cmp = icmp eq i8* %call4, null, !dbg !1943
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1943

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1946

cond.false:                                       ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1948
  %call5 = call i8* @archive_entry_pathname(%struct.archive_entry* %4), !dbg !1948
  %call6 = call i64 @strlen(i8* %call5) #7, !dbg !1950
  br label %cond.end, !dbg !1948

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call6, %cond.false ], !dbg !1952
  %call7 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %pathname3, i8* %call, i64 %cond), !dbg !1952
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1954
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1955
  %pathname8 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 7, !dbg !1956
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname8, i32 0, i32 0, !dbg !1957
  %7 = load i8*, i8** %s, align 8, !dbg !1957
  store i8* %7, i8** %pathname, align 8, !dbg !1958
  %8 = load i8*, i8** %pathname, align 8, !dbg !1959
  %call9 = call i32 @strcmp(i8* %8, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.38, i32 0, i32 0)) #7, !dbg !1961
  %cmp10 = icmp eq i32 %call9, 0, !dbg !1962
  br i1 %cmp10, label %if.then, label %if.end, !dbg !1963

if.then:                                          ; preds = %cond.end
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1964
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 6, !dbg !1964
  %length11 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 1, !dbg !1964
  store i64 0, i64* %length11, align 8, !dbg !1964
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1964
  %basename12 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %10, i32 0, i32 6, !dbg !1964
  %call13 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %basename12, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.38, i32 0, i32 0), i64 1), !dbg !1964
  store i32 0, i32* %retval, align 4, !dbg !1966
  br label %return, !dbg !1966

if.end:                                           ; preds = %cond.end
  %11 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1967
  %parentdir = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %11, i32 0, i32 5, !dbg !1967
  %length14 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir, i32 0, i32 1, !dbg !1967
  store i64 0, i64* %length14, align 8, !dbg !1967
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1967
  %parentdir15 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %12, i32 0, i32 5, !dbg !1967
  %13 = load i8*, i8** %pathname, align 8, !dbg !1967
  %14 = load i8*, i8** %pathname, align 8, !dbg !1967
  %cmp16 = icmp eq i8* %14, null, !dbg !1967
  br i1 %cmp16, label %cond.true17, label %cond.false18, !dbg !1967

cond.true17:                                      ; preds = %if.end
  br label %cond.end20, !dbg !1968

cond.false18:                                     ; preds = %if.end
  %15 = load i8*, i8** %pathname, align 8, !dbg !1969
  %call19 = call i64 @strlen(i8* %15) #7, !dbg !1969
  br label %cond.end20, !dbg !1969

cond.end20:                                       ; preds = %cond.false18, %cond.true17
  %cond21 = phi i64 [ 0, %cond.true17 ], [ %call19, %cond.false18 ], !dbg !1970
  %call22 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %parentdir15, i8* %13, i64 %cond21), !dbg !1970
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1971
  %parentdir23 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 5, !dbg !1972
  %length24 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir23, i32 0, i32 1, !dbg !1973
  %17 = load i64, i64* %length24, align 8, !dbg !1973
  store i64 %17, i64* %len, align 8, !dbg !1974
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !1975
  %parentdir25 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %18, i32 0, i32 5, !dbg !1976
  %s26 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir25, i32 0, i32 0, !dbg !1977
  %19 = load i8*, i8** %s26, align 8, !dbg !1977
  store i8* %19, i8** %dirname, align 8, !dbg !1978
  store i8* %19, i8** %p, align 8, !dbg !1979
  br label %while.cond, !dbg !1980

while.cond:                                       ; preds = %if.end48, %cond.end20
  %20 = load i8*, i8** %p, align 8, !dbg !1981
  %21 = load i8, i8* %20, align 1, !dbg !1982
  %tobool = icmp ne i8 %21, 0, !dbg !1983
  br i1 %tobool, label %while.body, label %while.end, !dbg !1983

while.body:                                       ; preds = %while.cond
  %22 = load i8*, i8** %p, align 8, !dbg !1984
  %arrayidx = getelementptr inbounds i8, i8* %22, i64 0, !dbg !1984
  %23 = load i8, i8* %arrayidx, align 1, !dbg !1984
  %conv = sext i8 %23 to i32, !dbg !1984
  %cmp27 = icmp eq i32 %conv, 47, !dbg !1987
  br i1 %cmp27, label %if.then29, label %if.else, !dbg !1988

if.then29:                                        ; preds = %while.body
  %24 = load i8*, i8** %p, align 8, !dbg !1989
  %incdec.ptr = getelementptr inbounds i8, i8* %24, i32 1, !dbg !1989
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1989
  %25 = load i64, i64* %len, align 8, !dbg !1991
  %dec = add i64 %25, -1, !dbg !1991
  store i64 %dec, i64* %len, align 8, !dbg !1991
  br label %if.end48, !dbg !1992

if.else:                                          ; preds = %while.body
  %26 = load i8*, i8** %p, align 8, !dbg !1993
  %arrayidx30 = getelementptr inbounds i8, i8* %26, i64 0, !dbg !1993
  %27 = load i8, i8* %arrayidx30, align 1, !dbg !1993
  %conv31 = sext i8 %27 to i32, !dbg !1993
  %cmp32 = icmp ne i32 %conv31, 46, !dbg !1996
  br i1 %cmp32, label %if.then34, label %if.else35, !dbg !1993

if.then34:                                        ; preds = %if.else
  br label %while.end, !dbg !1997

if.else35:                                        ; preds = %if.else
  %28 = load i8*, i8** %p, align 8, !dbg !1998
  %arrayidx36 = getelementptr inbounds i8, i8* %28, i64 1, !dbg !1998
  %29 = load i8, i8* %arrayidx36, align 1, !dbg !1998
  %conv37 = sext i8 %29 to i32, !dbg !1998
  %cmp38 = icmp eq i32 %conv37, 46, !dbg !2000
  br i1 %cmp38, label %land.lhs.true, label %if.else45, !dbg !2001

land.lhs.true:                                    ; preds = %if.else35
  %30 = load i8*, i8** %p, align 8, !dbg !2002
  %arrayidx40 = getelementptr inbounds i8, i8* %30, i64 2, !dbg !2002
  %31 = load i8, i8* %arrayidx40, align 1, !dbg !2002
  %conv41 = sext i8 %31 to i32, !dbg !2002
  %cmp42 = icmp eq i32 %conv41, 47, !dbg !2004
  br i1 %cmp42, label %if.then44, label %if.else45, !dbg !2005

if.then44:                                        ; preds = %land.lhs.true
  %32 = load i8*, i8** %p, align 8, !dbg !2006
  %add.ptr = getelementptr inbounds i8, i8* %32, i64 3, !dbg !2006
  store i8* %add.ptr, i8** %p, align 8, !dbg !2006
  %33 = load i64, i64* %len, align 8, !dbg !2008
  %sub = sub i64 %33, 3, !dbg !2008
  store i64 %sub, i64* %len, align 8, !dbg !2008
  br label %if.end46, !dbg !2009

if.else45:                                        ; preds = %land.lhs.true, %if.else35
  br label %while.end, !dbg !2010

if.end46:                                         ; preds = %if.then44
  br label %if.end47

if.end47:                                         ; preds = %if.end46
  br label %if.end48

if.end48:                                         ; preds = %if.end47, %if.then29
  br label %while.cond, !dbg !2011

while.end:                                        ; preds = %if.else45, %if.then34, %while.cond
  %34 = load i8*, i8** %p, align 8, !dbg !2012
  %35 = load i8*, i8** %dirname, align 8, !dbg !2014
  %cmp49 = icmp ne i8* %34, %35, !dbg !2015
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !2016

if.then51:                                        ; preds = %while.end
  %36 = load i8*, i8** %dirname, align 8, !dbg !2017
  %37 = load i8*, i8** %p, align 8, !dbg !2019
  %38 = load i64, i64* %len, align 8, !dbg !2020
  %add = add i64 %38, 1, !dbg !2021
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %36, i8* %37, i64 %add, i32 1, i1 false), !dbg !2022
  %39 = load i8*, i8** %dirname, align 8, !dbg !2023
  store i8* %39, i8** %p, align 8, !dbg !2024
  br label %if.end52, !dbg !2025

if.end52:                                         ; preds = %if.then51, %while.end
  br label %while.cond53, !dbg !2026

while.cond53:                                     ; preds = %if.end117, %if.end52
  %40 = load i64, i64* %len, align 8, !dbg !2027
  %cmp54 = icmp ugt i64 %40, 0, !dbg !2028
  br i1 %cmp54, label %while.body56, label %while.end118, !dbg !2029

while.body56:                                     ; preds = %while.cond53
  call void @llvm.dbg.declare(metadata i64* %ll, metadata !2030, metadata !426), !dbg !2032
  %41 = load i64, i64* %len, align 8, !dbg !2033
  store i64 %41, i64* %ll, align 8, !dbg !2032
  %42 = load i64, i64* %len, align 8, !dbg !2034
  %cmp57 = icmp ugt i64 %42, 0, !dbg !2036
  br i1 %cmp57, label %land.lhs.true59, label %if.end69, !dbg !2037

land.lhs.true59:                                  ; preds = %while.body56
  %43 = load i64, i64* %len, align 8, !dbg !2038
  %sub60 = sub i64 %43, 1, !dbg !2040
  %44 = load i8*, i8** %p, align 8, !dbg !2041
  %arrayidx61 = getelementptr inbounds i8, i8* %44, i64 %sub60, !dbg !2041
  %45 = load i8, i8* %arrayidx61, align 1, !dbg !2041
  %conv62 = sext i8 %45 to i32, !dbg !2041
  %cmp63 = icmp eq i32 %conv62, 47, !dbg !2042
  br i1 %cmp63, label %if.then65, label %if.end69, !dbg !2043

if.then65:                                        ; preds = %land.lhs.true59
  %46 = load i64, i64* %len, align 8, !dbg !2044
  %sub66 = sub i64 %46, 1, !dbg !2046
  %47 = load i8*, i8** %p, align 8, !dbg !2047
  %arrayidx67 = getelementptr inbounds i8, i8* %47, i64 %sub66, !dbg !2047
  store i8 0, i8* %arrayidx67, align 1, !dbg !2048
  %48 = load i64, i64* %len, align 8, !dbg !2049
  %dec68 = add i64 %48, -1, !dbg !2049
  store i64 %dec68, i64* %len, align 8, !dbg !2049
  br label %if.end69, !dbg !2050

if.end69:                                         ; preds = %if.then65, %land.lhs.true59, %while.body56
  %49 = load i64, i64* %len, align 8, !dbg !2051
  %cmp70 = icmp ugt i64 %49, 1, !dbg !2053
  br i1 %cmp70, label %land.lhs.true72, label %if.end88, !dbg !2054

land.lhs.true72:                                  ; preds = %if.end69
  %50 = load i64, i64* %len, align 8, !dbg !2055
  %sub73 = sub i64 %50, 2, !dbg !2057
  %51 = load i8*, i8** %p, align 8, !dbg !2058
  %arrayidx74 = getelementptr inbounds i8, i8* %51, i64 %sub73, !dbg !2058
  %52 = load i8, i8* %arrayidx74, align 1, !dbg !2058
  %conv75 = sext i8 %52 to i32, !dbg !2058
  %cmp76 = icmp eq i32 %conv75, 47, !dbg !2059
  br i1 %cmp76, label %land.lhs.true78, label %if.end88, !dbg !2060

land.lhs.true78:                                  ; preds = %land.lhs.true72
  %53 = load i64, i64* %len, align 8, !dbg !2061
  %sub79 = sub i64 %53, 1, !dbg !2063
  %54 = load i8*, i8** %p, align 8, !dbg !2064
  %arrayidx80 = getelementptr inbounds i8, i8* %54, i64 %sub79, !dbg !2064
  %55 = load i8, i8* %arrayidx80, align 1, !dbg !2064
  %conv81 = sext i8 %55 to i32, !dbg !2064
  %cmp82 = icmp eq i32 %conv81, 46, !dbg !2065
  br i1 %cmp82, label %if.then84, label %if.end88, !dbg !2066

if.then84:                                        ; preds = %land.lhs.true78
  %56 = load i64, i64* %len, align 8, !dbg !2067
  %sub85 = sub i64 %56, 2, !dbg !2069
  %57 = load i8*, i8** %p, align 8, !dbg !2070
  %arrayidx86 = getelementptr inbounds i8, i8* %57, i64 %sub85, !dbg !2070
  store i8 0, i8* %arrayidx86, align 1, !dbg !2071
  %58 = load i64, i64* %len, align 8, !dbg !2072
  %sub87 = sub i64 %58, 2, !dbg !2072
  store i64 %sub87, i64* %len, align 8, !dbg !2072
  br label %if.end88, !dbg !2073

if.end88:                                         ; preds = %if.then84, %land.lhs.true78, %land.lhs.true72, %if.end69
  %59 = load i64, i64* %len, align 8, !dbg !2074
  %cmp89 = icmp ugt i64 %59, 2, !dbg !2076
  br i1 %cmp89, label %land.lhs.true91, label %if.end113, !dbg !2077

land.lhs.true91:                                  ; preds = %if.end88
  %60 = load i64, i64* %len, align 8, !dbg !2078
  %sub92 = sub i64 %60, 3, !dbg !2080
  %61 = load i8*, i8** %p, align 8, !dbg !2081
  %arrayidx93 = getelementptr inbounds i8, i8* %61, i64 %sub92, !dbg !2081
  %62 = load i8, i8* %arrayidx93, align 1, !dbg !2081
  %conv94 = sext i8 %62 to i32, !dbg !2081
  %cmp95 = icmp eq i32 %conv94, 47, !dbg !2082
  br i1 %cmp95, label %land.lhs.true97, label %if.end113, !dbg !2083

land.lhs.true97:                                  ; preds = %land.lhs.true91
  %63 = load i64, i64* %len, align 8, !dbg !2084
  %sub98 = sub i64 %63, 2, !dbg !2086
  %64 = load i8*, i8** %p, align 8, !dbg !2087
  %arrayidx99 = getelementptr inbounds i8, i8* %64, i64 %sub98, !dbg !2087
  %65 = load i8, i8* %arrayidx99, align 1, !dbg !2087
  %conv100 = sext i8 %65 to i32, !dbg !2087
  %cmp101 = icmp eq i32 %conv100, 46, !dbg !2088
  br i1 %cmp101, label %land.lhs.true103, label %if.end113, !dbg !2089

land.lhs.true103:                                 ; preds = %land.lhs.true97
  %66 = load i64, i64* %len, align 8, !dbg !2090
  %sub104 = sub i64 %66, 1, !dbg !2091
  %67 = load i8*, i8** %p, align 8, !dbg !2092
  %arrayidx105 = getelementptr inbounds i8, i8* %67, i64 %sub104, !dbg !2092
  %68 = load i8, i8* %arrayidx105, align 1, !dbg !2092
  %conv106 = sext i8 %68 to i32, !dbg !2092
  %cmp107 = icmp eq i32 %conv106, 46, !dbg !2093
  br i1 %cmp107, label %if.then109, label %if.end113, !dbg !2094

if.then109:                                       ; preds = %land.lhs.true103
  %69 = load i64, i64* %len, align 8, !dbg !2096
  %sub110 = sub i64 %69, 3, !dbg !2098
  %70 = load i8*, i8** %p, align 8, !dbg !2099
  %arrayidx111 = getelementptr inbounds i8, i8* %70, i64 %sub110, !dbg !2099
  store i8 0, i8* %arrayidx111, align 1, !dbg !2100
  %71 = load i64, i64* %len, align 8, !dbg !2101
  %sub112 = sub i64 %71, 3, !dbg !2101
  store i64 %sub112, i64* %len, align 8, !dbg !2101
  br label %if.end113, !dbg !2102

if.end113:                                        ; preds = %if.then109, %land.lhs.true103, %land.lhs.true97, %land.lhs.true91, %if.end88
  %72 = load i64, i64* %ll, align 8, !dbg !2103
  %73 = load i64, i64* %len, align 8, !dbg !2105
  %cmp114 = icmp eq i64 %72, %73, !dbg !2106
  br i1 %cmp114, label %if.then116, label %if.end117, !dbg !2107

if.then116:                                       ; preds = %if.end113
  br label %while.end118, !dbg !2108

if.end117:                                        ; preds = %if.end113
  br label %while.cond53, !dbg !2109

while.end118:                                     ; preds = %if.then116, %while.cond53
  br label %while.cond119, !dbg !2110

while.cond119:                                    ; preds = %if.end191, %while.end118
  %74 = load i8*, i8** %p, align 8, !dbg !2111
  %75 = load i8, i8* %74, align 1, !dbg !2112
  %tobool120 = icmp ne i8 %75, 0, !dbg !2113
  br i1 %tobool120, label %while.body121, label %while.end192, !dbg !2113

while.body121:                                    ; preds = %while.cond119
  %76 = load i8*, i8** %p, align 8, !dbg !2114
  %arrayidx122 = getelementptr inbounds i8, i8* %76, i64 0, !dbg !2114
  %77 = load i8, i8* %arrayidx122, align 1, !dbg !2114
  %conv123 = sext i8 %77 to i32, !dbg !2114
  %cmp124 = icmp eq i32 %conv123, 47, !dbg !2117
  br i1 %cmp124, label %if.then126, label %if.else189, !dbg !2118

if.then126:                                       ; preds = %while.body121
  %78 = load i8*, i8** %p, align 8, !dbg !2119
  %arrayidx127 = getelementptr inbounds i8, i8* %78, i64 1, !dbg !2119
  %79 = load i8, i8* %arrayidx127, align 1, !dbg !2119
  %conv128 = sext i8 %79 to i32, !dbg !2119
  %cmp129 = icmp eq i32 %conv128, 47, !dbg !2122
  br i1 %cmp129, label %if.then131, label %if.else134, !dbg !2123

if.then131:                                       ; preds = %if.then126
  %80 = load i8*, i8** %p, align 8, !dbg !2124
  %81 = load i8*, i8** %p, align 8, !dbg !2125
  %add.ptr132 = getelementptr inbounds i8, i8* %81, i64 1, !dbg !2126
  %call133 = call i8* @strcpy(i8* %80, i8* %add.ptr132) #6, !dbg !2127
  br label %if.end188, !dbg !2127

if.else134:                                       ; preds = %if.then126
  %82 = load i8*, i8** %p, align 8, !dbg !2128
  %arrayidx135 = getelementptr inbounds i8, i8* %82, i64 1, !dbg !2128
  %83 = load i8, i8* %arrayidx135, align 1, !dbg !2128
  %conv136 = sext i8 %83 to i32, !dbg !2128
  %cmp137 = icmp eq i32 %conv136, 46, !dbg !2130
  br i1 %cmp137, label %land.lhs.true139, label %if.else147, !dbg !2131

land.lhs.true139:                                 ; preds = %if.else134
  %84 = load i8*, i8** %p, align 8, !dbg !2132
  %arrayidx140 = getelementptr inbounds i8, i8* %84, i64 2, !dbg !2132
  %85 = load i8, i8* %arrayidx140, align 1, !dbg !2132
  %conv141 = sext i8 %85 to i32, !dbg !2132
  %cmp142 = icmp eq i32 %conv141, 47, !dbg !2134
  br i1 %cmp142, label %if.then144, label %if.else147, !dbg !2135

if.then144:                                       ; preds = %land.lhs.true139
  %86 = load i8*, i8** %p, align 8, !dbg !2136
  %87 = load i8*, i8** %p, align 8, !dbg !2137
  %add.ptr145 = getelementptr inbounds i8, i8* %87, i64 2, !dbg !2138
  %call146 = call i8* @strcpy(i8* %86, i8* %add.ptr145) #6, !dbg !2139
  br label %if.end187, !dbg !2139

if.else147:                                       ; preds = %land.lhs.true139, %if.else134
  %88 = load i8*, i8** %p, align 8, !dbg !2140
  %arrayidx148 = getelementptr inbounds i8, i8* %88, i64 1, !dbg !2140
  %89 = load i8, i8* %arrayidx148, align 1, !dbg !2140
  %conv149 = sext i8 %89 to i32, !dbg !2140
  %cmp150 = icmp eq i32 %conv149, 46, !dbg !2142
  br i1 %cmp150, label %land.lhs.true152, label %if.else184, !dbg !2143

land.lhs.true152:                                 ; preds = %if.else147
  %90 = load i8*, i8** %p, align 8, !dbg !2144
  %arrayidx153 = getelementptr inbounds i8, i8* %90, i64 2, !dbg !2144
  %91 = load i8, i8* %arrayidx153, align 1, !dbg !2144
  %conv154 = sext i8 %91 to i32, !dbg !2144
  %cmp155 = icmp eq i32 %conv154, 46, !dbg !2146
  br i1 %cmp155, label %land.lhs.true157, label %if.else184, !dbg !2147

land.lhs.true157:                                 ; preds = %land.lhs.true152
  %92 = load i8*, i8** %p, align 8, !dbg !2148
  %arrayidx158 = getelementptr inbounds i8, i8* %92, i64 3, !dbg !2148
  %93 = load i8, i8* %arrayidx158, align 1, !dbg !2148
  %conv159 = sext i8 %93 to i32, !dbg !2148
  %cmp160 = icmp eq i32 %conv159, 47, !dbg !2150
  br i1 %cmp160, label %if.then162, label %if.else184, !dbg !2151

if.then162:                                       ; preds = %land.lhs.true157
  call void @llvm.dbg.declare(metadata i8** %rp, metadata !2152, metadata !426), !dbg !2154
  %94 = load i8*, i8** %p, align 8, !dbg !2155
  %add.ptr163 = getelementptr inbounds i8, i8* %94, i64 -1, !dbg !2156
  store i8* %add.ptr163, i8** %rp, align 8, !dbg !2154
  br label %while.cond164, !dbg !2157

while.cond164:                                    ; preds = %if.end172, %if.then162
  %95 = load i8*, i8** %rp, align 8, !dbg !2158
  %96 = load i8*, i8** %dirname, align 8, !dbg !2160
  %cmp165 = icmp uge i8* %95, %96, !dbg !2161
  br i1 %cmp165, label %while.body167, label %while.end174, !dbg !2162

while.body167:                                    ; preds = %while.cond164
  %97 = load i8*, i8** %rp, align 8, !dbg !2163
  %98 = load i8, i8* %97, align 1, !dbg !2166
  %conv168 = sext i8 %98 to i32, !dbg !2166
  %cmp169 = icmp eq i32 %conv168, 47, !dbg !2167
  br i1 %cmp169, label %if.then171, label %if.end172, !dbg !2168

if.then171:                                       ; preds = %while.body167
  br label %while.end174, !dbg !2169

if.end172:                                        ; preds = %while.body167
  %99 = load i8*, i8** %rp, align 8, !dbg !2170
  %incdec.ptr173 = getelementptr inbounds i8, i8* %99, i32 -1, !dbg !2170
  store i8* %incdec.ptr173, i8** %rp, align 8, !dbg !2170
  br label %while.cond164, !dbg !2171

while.end174:                                     ; preds = %if.then171, %while.cond164
  %100 = load i8*, i8** %rp, align 8, !dbg !2173
  %101 = load i8*, i8** %dirname, align 8, !dbg !2175
  %cmp175 = icmp ugt i8* %100, %101, !dbg !2176
  br i1 %cmp175, label %if.then177, label %if.else180, !dbg !2177

if.then177:                                       ; preds = %while.end174
  %102 = load i8*, i8** %rp, align 8, !dbg !2178
  %103 = load i8*, i8** %p, align 8, !dbg !2180
  %add.ptr178 = getelementptr inbounds i8, i8* %103, i64 3, !dbg !2181
  %call179 = call i8* @strcpy(i8* %102, i8* %add.ptr178) #6, !dbg !2182
  %104 = load i8*, i8** %rp, align 8, !dbg !2183
  store i8* %104, i8** %p, align 8, !dbg !2184
  br label %if.end183, !dbg !2185

if.else180:                                       ; preds = %while.end174
  %105 = load i8*, i8** %dirname, align 8, !dbg !2186
  %106 = load i8*, i8** %p, align 8, !dbg !2188
  %add.ptr181 = getelementptr inbounds i8, i8* %106, i64 4, !dbg !2189
  %call182 = call i8* @strcpy(i8* %105, i8* %add.ptr181) #6, !dbg !2190
  %107 = load i8*, i8** %dirname, align 8, !dbg !2191
  store i8* %107, i8** %p, align 8, !dbg !2192
  br label %if.end183

if.end183:                                        ; preds = %if.else180, %if.then177
  br label %if.end186, !dbg !2193

if.else184:                                       ; preds = %land.lhs.true157, %land.lhs.true152, %if.else147
  %108 = load i8*, i8** %p, align 8, !dbg !2194
  %incdec.ptr185 = getelementptr inbounds i8, i8* %108, i32 1, !dbg !2194
  store i8* %incdec.ptr185, i8** %p, align 8, !dbg !2194
  br label %if.end186

if.end186:                                        ; preds = %if.else184, %if.end183
  br label %if.end187

if.end187:                                        ; preds = %if.end186, %if.then144
  br label %if.end188

if.end188:                                        ; preds = %if.end187, %if.then131
  br label %if.end191, !dbg !2195

if.else189:                                       ; preds = %while.body121
  %109 = load i8*, i8** %p, align 8, !dbg !2196
  %incdec.ptr190 = getelementptr inbounds i8, i8* %109, i32 1, !dbg !2196
  store i8* %incdec.ptr190, i8** %p, align 8, !dbg !2196
  br label %if.end191

if.end191:                                        ; preds = %if.else189, %if.end188
  br label %while.cond119, !dbg !2197

while.end192:                                     ; preds = %while.cond119
  %110 = load i8*, i8** %dirname, align 8, !dbg !2198
  store i8* %110, i8** %p, align 8, !dbg !2199
  %111 = load i8*, i8** %p, align 8, !dbg !2200
  %call193 = call i64 @strlen(i8* %111) #7, !dbg !2201
  store i64 %call193, i64* %len, align 8, !dbg !2202
  %112 = load i8*, i8** %p, align 8, !dbg !2203
  %call194 = call i32 @strcmp(i8* %112, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.38, i32 0, i32 0)) #7, !dbg !2205
  %cmp195 = icmp ne i32 %call194, 0, !dbg !2206
  br i1 %cmp195, label %land.lhs.true197, label %if.end214, !dbg !2207

land.lhs.true197:                                 ; preds = %while.end192
  %113 = load i8*, i8** %p, align 8, !dbg !2208
  %call198 = call i32 @strncmp(i8* %113, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i32 0, i32 0), i64 2) #7, !dbg !2210
  %cmp199 = icmp ne i32 %call198, 0, !dbg !2211
  br i1 %cmp199, label %if.then201, label %if.end214, !dbg !2212

if.then201:                                       ; preds = %land.lhs.true197
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !2213, metadata !426), !dbg !2215
  br label %do.body, !dbg !2216

do.body:                                          ; preds = %if.then201
  %s202 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !2217
  store i8* null, i8** %s202, align 8, !dbg !2217
  %length203 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !2217
  store i64 0, i64* %length203, align 8, !dbg !2217
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !2217
  store i64 0, i64* %buffer_length, align 8, !dbg !2217
  br label %do.end, !dbg !2217

do.end:                                           ; preds = %do.body
  %length204 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !2220
  store i64 0, i64* %length204, align 8, !dbg !2220
  %call205 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.39, i32 0, i32 0), i64 2), !dbg !2220
  %114 = load i8*, i8** %p, align 8, !dbg !2221
  %115 = load i64, i64* %len, align 8, !dbg !2222
  %call206 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %114, i64 %115), !dbg !2223
  %116 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2224
  %parentdir207 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %116, i32 0, i32 5, !dbg !2224
  %length208 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir207, i32 0, i32 1, !dbg !2224
  store i64 0, i64* %length208, align 8, !dbg !2224
  %117 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2225
  %parentdir209 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %117, i32 0, i32 5, !dbg !2226
  call void @archive_string_concat(%struct.archive_string* %parentdir209, %struct.archive_string* %as), !dbg !2227
  call void @archive_string_free(%struct.archive_string* %as), !dbg !2228
  %118 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2229
  %parentdir210 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %118, i32 0, i32 5, !dbg !2230
  %s211 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir210, i32 0, i32 0, !dbg !2231
  %119 = load i8*, i8** %s211, align 8, !dbg !2231
  store i8* %119, i8** %p, align 8, !dbg !2232
  %120 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2233
  %parentdir212 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %120, i32 0, i32 5, !dbg !2233
  %length213 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir212, i32 0, i32 1, !dbg !2233
  %121 = load i64, i64* %length213, align 8, !dbg !2233
  store i64 %121, i64* %len, align 8, !dbg !2234
  br label %if.end214, !dbg !2235

if.end214:                                        ; preds = %do.end, %land.lhs.true197, %while.end192
  store i8* null, i8** %slash, align 8, !dbg !2236
  br label %for.cond, !dbg !2237

for.cond:                                         ; preds = %for.inc, %if.end214
  %122 = load i8*, i8** %p, align 8, !dbg !2238
  %123 = load i8, i8* %122, align 1, !dbg !2242
  %conv215 = sext i8 %123 to i32, !dbg !2242
  %cmp216 = icmp ne i32 %conv215, 0, !dbg !2243
  br i1 %cmp216, label %for.body, label %for.end, !dbg !2244

for.body:                                         ; preds = %for.cond
  %124 = load i8*, i8** %p, align 8, !dbg !2245
  %125 = load i8, i8* %124, align 1, !dbg !2248
  %conv218 = sext i8 %125 to i32, !dbg !2248
  %cmp219 = icmp eq i32 %conv218, 47, !dbg !2249
  br i1 %cmp219, label %if.then221, label %if.end222, !dbg !2250

if.then221:                                       ; preds = %for.body
  %126 = load i8*, i8** %p, align 8, !dbg !2251
  store i8* %126, i8** %slash, align 8, !dbg !2252
  br label %if.end222, !dbg !2253

if.end222:                                        ; preds = %if.then221, %for.body
  br label %for.inc, !dbg !2254

for.inc:                                          ; preds = %if.end222
  %127 = load i8*, i8** %p, align 8, !dbg !2255
  %incdec.ptr223 = getelementptr inbounds i8, i8* %127, i32 1, !dbg !2255
  store i8* %incdec.ptr223, i8** %p, align 8, !dbg !2255
  br label %for.cond, !dbg !2257

for.end:                                          ; preds = %for.cond
  %128 = load i8*, i8** %slash, align 8, !dbg !2258
  %cmp224 = icmp eq i8* %128, null, !dbg !2260
  br i1 %cmp224, label %if.then226, label %if.end237, !dbg !2261

if.then226:                                       ; preds = %for.end
  %129 = load i64, i64* %len, align 8, !dbg !2262
  %130 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2264
  %parentdir227 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %130, i32 0, i32 5, !dbg !2265
  %length228 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir227, i32 0, i32 1, !dbg !2266
  store i64 %129, i64* %length228, align 8, !dbg !2267
  %131 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2268
  %basename229 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %131, i32 0, i32 6, !dbg !2268
  %length230 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename229, i32 0, i32 1, !dbg !2268
  store i64 0, i64* %length230, align 8, !dbg !2268
  %132 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2268
  %basename231 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %132, i32 0, i32 6, !dbg !2268
  %133 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2268
  %parentdir232 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %133, i32 0, i32 5, !dbg !2268
  call void @archive_string_concat(%struct.archive_string* %basename231, %struct.archive_string* %parentdir232), !dbg !2268
  %134 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2269
  %parentdir233 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %134, i32 0, i32 5, !dbg !2269
  %length234 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir233, i32 0, i32 1, !dbg !2269
  store i64 0, i64* %length234, align 8, !dbg !2269
  %135 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2270
  %parentdir235 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %135, i32 0, i32 5, !dbg !2271
  %s236 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir235, i32 0, i32 0, !dbg !2272
  %136 = load i8*, i8** %s236, align 8, !dbg !2272
  store i8 0, i8* %136, align 1, !dbg !2273
  %137 = load i32, i32* %ret, align 4, !dbg !2274
  store i32 %137, i32* %retval, align 4, !dbg !2275
  br label %return, !dbg !2275

if.end237:                                        ; preds = %for.end
  %138 = load i8*, i8** %slash, align 8, !dbg !2276
  store i8 0, i8* %138, align 1, !dbg !2277
  %139 = load i8*, i8** %slash, align 8, !dbg !2278
  %140 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2279
  %parentdir238 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %140, i32 0, i32 5, !dbg !2280
  %s239 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir238, i32 0, i32 0, !dbg !2281
  %141 = load i8*, i8** %s239, align 8, !dbg !2281
  %sub.ptr.lhs.cast = ptrtoint i8* %139 to i64, !dbg !2282
  %sub.ptr.rhs.cast = ptrtoint i8* %141 to i64, !dbg !2282
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2282
  %142 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2283
  %parentdir240 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %142, i32 0, i32 5, !dbg !2284
  %length241 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir240, i32 0, i32 1, !dbg !2285
  store i64 %sub.ptr.sub, i64* %length241, align 8, !dbg !2286
  %143 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2287
  %basename242 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %143, i32 0, i32 6, !dbg !2287
  %length243 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename242, i32 0, i32 1, !dbg !2287
  store i64 0, i64* %length243, align 8, !dbg !2287
  %144 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2287
  %basename244 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %144, i32 0, i32 6, !dbg !2287
  %145 = load i8*, i8** %slash, align 8, !dbg !2287
  %add.ptr245 = getelementptr inbounds i8, i8* %145, i64 1, !dbg !2287
  %146 = load i8*, i8** %slash, align 8, !dbg !2287
  %add.ptr246 = getelementptr inbounds i8, i8* %146, i64 1, !dbg !2287
  %cmp247 = icmp eq i8* %add.ptr246, null, !dbg !2287
  br i1 %cmp247, label %cond.true249, label %cond.false250, !dbg !2287

cond.true249:                                     ; preds = %if.end237
  br label %cond.end253, !dbg !2288

cond.false250:                                    ; preds = %if.end237
  %147 = load i8*, i8** %slash, align 8, !dbg !2289
  %add.ptr251 = getelementptr inbounds i8, i8* %147, i64 1, !dbg !2289
  %call252 = call i64 @strlen(i8* %add.ptr251) #7, !dbg !2289
  br label %cond.end253, !dbg !2289

cond.end253:                                      ; preds = %cond.false250, %cond.true249
  %cond254 = phi i64 [ 0, %cond.true249 ], [ %call252, %cond.false250 ], !dbg !2290
  %call255 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %basename244, i8* %add.ptr245, i64 %cond254), !dbg !2290
  %148 = load i32, i32* %ret, align 4, !dbg !2291
  store i32 %148, i32* %retval, align 4, !dbg !2292
  br label %return, !dbg !2292

return:                                           ; preds = %cond.end253, %if.then226, %if.then
  %149 = load i32, i32* %retval, align 4, !dbg !2293
  ret i32 %149, !dbg !2293
}

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #5

declare i32 @archive_entry_nlink(%struct.archive_entry*) #2

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare i8* @archive_entry_uname(%struct.archive_entry*) #2

declare i8* @archive_entry_gname(%struct.archive_entry*) #2

declare i8* @archive_entry_fflags_text(%struct.archive_entry*) #2

declare void @archive_entry_fflags(%struct.archive_entry*, i64*, i64*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #2

declare i64 @archive_entry_devmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_devminor(%struct.archive_entry*) #2

declare i64 @archive_entry_ino(%struct.archive_entry*) #2

declare void @__archive_rb_tree_init(%struct.archive_rb_tree*, %struct.archive_rb_tree_ops*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #5

declare void @archive_string_concat(%struct.archive_string*, %struct.archive_string*) #2

; Function Attrs: nounwind uwtable
define internal void @mtree_entry_register_add(%struct.mtree_writer* %mtree, %struct.mtree_entry* %file) #0 !dbg !361 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %file.addr = alloca %struct.mtree_entry*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !2294, metadata !426), !dbg !2295
  store %struct.mtree_entry* %file, %struct.mtree_entry** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file.addr, metadata !2296, metadata !426), !dbg !2297
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2298
  %next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 1, !dbg !2299
  store %struct.mtree_entry* null, %struct.mtree_entry** %next, align 8, !dbg !2300
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2301
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !2302
  %file_list = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 4, !dbg !2303
  %last = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list, i32 0, i32 1, !dbg !2304
  %3 = load %struct.mtree_entry**, %struct.mtree_entry*** %last, align 8, !dbg !2304
  store %struct.mtree_entry* %1, %struct.mtree_entry** %3, align 8, !dbg !2305
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2306
  %next1 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %4, i32 0, i32 1, !dbg !2307
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !2308
  %file_list2 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 4, !dbg !2309
  %last3 = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %file_list2, i32 0, i32 1, !dbg !2310
  store %struct.mtree_entry** %next1, %struct.mtree_entry*** %last3, align 8, !dbg !2311
  ret void, !dbg !2312
}

declare i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree*, %struct.archive_rb_node*) #2

declare %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @get_path_component(i8* %name, i64 %n, i8* %fn) #0 !dbg !364 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %fn.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %l = alloca i64, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2313, metadata !426), !dbg !2314
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !2315, metadata !426), !dbg !2316
  store i8* %fn, i8** %fn.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fn.addr, metadata !2317, metadata !426), !dbg !2318
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2319, metadata !426), !dbg !2320
  call void @llvm.dbg.declare(metadata i64* %l, metadata !2321, metadata !426), !dbg !2322
  %0 = load i8*, i8** %fn.addr, align 8, !dbg !2323
  %call = call i8* @strchr(i8* %0, i32 47) #7, !dbg !2324
  store i8* %call, i8** %p, align 8, !dbg !2325
  %1 = load i8*, i8** %p, align 8, !dbg !2326
  %cmp = icmp eq i8* %1, null, !dbg !2328
  br i1 %cmp, label %if.then, label %if.else, !dbg !2329

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %fn.addr, align 8, !dbg !2330
  %call1 = call i64 @strlen(i8* %2) #7, !dbg !2333
  store i64 %call1, i64* %l, align 8, !dbg !2334
  %cmp2 = icmp eq i64 %call1, 0, !dbg !2335
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !2336

if.then3:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !2337
  br label %return, !dbg !2337

if.end:                                           ; preds = %if.then
  br label %if.end4, !dbg !2338

if.else:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !2339
  %4 = load i8*, i8** %fn.addr, align 8, !dbg !2340
  %sub.ptr.lhs.cast = ptrtoint i8* %3 to i64, !dbg !2341
  %sub.ptr.rhs.cast = ptrtoint i8* %4 to i64, !dbg !2341
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2341
  store i64 %sub.ptr.sub, i64* %l, align 8, !dbg !2342
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.end
  %5 = load i64, i64* %l, align 8, !dbg !2343
  %6 = load i64, i64* %n.addr, align 8, !dbg !2345
  %sub = sub i64 %6, 1, !dbg !2346
  %cmp5 = icmp ugt i64 %5, %sub, !dbg !2347
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2348

if.then6:                                         ; preds = %if.end4
  store i32 -1, i32* %retval, align 4, !dbg !2349
  br label %return, !dbg !2349

if.end7:                                          ; preds = %if.end4
  %7 = load i8*, i8** %name.addr, align 8, !dbg !2350
  %8 = load i8*, i8** %fn.addr, align 8, !dbg !2351
  %9 = load i64, i64* %l, align 8, !dbg !2352
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 %9, i32 1, i1 false), !dbg !2353
  %10 = load i64, i64* %l, align 8, !dbg !2354
  %11 = load i8*, i8** %name.addr, align 8, !dbg !2355
  %arrayidx = getelementptr inbounds i8, i8* %11, i64 %10, !dbg !2355
  store i8 0, i8* %arrayidx, align 1, !dbg !2356
  %12 = load i64, i64* %l, align 8, !dbg !2357
  %conv = trunc i64 %12 to i32, !dbg !2358
  store i32 %conv, i32* %retval, align 4, !dbg !2359
  br label %return, !dbg !2359

return:                                           ; preds = %if.end7, %if.then6, %if.then3
  %13 = load i32, i32* %retval, align 4, !dbg !2360
  ret i32 %13, !dbg !2360
}

; Function Attrs: nounwind uwtable
define internal %struct.mtree_entry* @mtree_entry_find_child(%struct.mtree_entry* %parent, i8* %child_name) #0 !dbg !367 {
entry:
  %retval = alloca %struct.mtree_entry*, align 8
  %parent.addr = alloca %struct.mtree_entry*, align 8
  %child_name.addr = alloca i8*, align 8
  %np = alloca %struct.mtree_entry*, align 8
  store %struct.mtree_entry* %parent, %struct.mtree_entry** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %parent.addr, metadata !2361, metadata !426), !dbg !2362
  store i8* %child_name, i8** %child_name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %child_name.addr, metadata !2363, metadata !426), !dbg !2364
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %np, metadata !2365, metadata !426), !dbg !2366
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %parent.addr, align 8, !dbg !2367
  %cmp = icmp eq %struct.mtree_entry* %0, null, !dbg !2369
  br i1 %cmp, label %if.then, label %if.end, !dbg !2370

if.then:                                          ; preds = %entry
  store %struct.mtree_entry* null, %struct.mtree_entry** %retval, align 8, !dbg !2371
  br label %return, !dbg !2371

if.end:                                           ; preds = %entry
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %parent.addr, align 8, !dbg !2372
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %1, i32 0, i32 3, !dbg !2373
  %2 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !2373
  %rbtree = getelementptr inbounds %struct.dir_info, %struct.dir_info* %2, i32 0, i32 0, !dbg !2374
  %3 = load i8*, i8** %child_name.addr, align 8, !dbg !2375
  %call = call %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %rbtree, i8* %3), !dbg !2376
  %4 = bitcast %struct.archive_rb_node* %call to %struct.mtree_entry*, !dbg !2377
  store %struct.mtree_entry* %4, %struct.mtree_entry** %np, align 8, !dbg !2378
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2379
  store %struct.mtree_entry* %5, %struct.mtree_entry** %retval, align 8, !dbg !2380
  br label %return, !dbg !2380

return:                                           ; preds = %if.end, %if.then
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %retval, align 8, !dbg !2381
  ret %struct.mtree_entry* %6, !dbg !2381
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_create_virtual_dir(%struct.archive_write* %a, i8* %pathname, %struct.mtree_entry** %m_entry) #0 !dbg !370 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %pathname.addr = alloca i8*, align 8
  %m_entry.addr = alloca %struct.mtree_entry**, align 8
  %entry1 = alloca %struct.archive_entry*, align 8
  %file = alloca %struct.mtree_entry*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2382, metadata !426), !dbg !2383
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !2384, metadata !426), !dbg !2385
  store %struct.mtree_entry** %m_entry, %struct.mtree_entry*** %m_entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry*** %m_entry.addr, metadata !2386, metadata !426), !dbg !2387
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry1, metadata !2388, metadata !426), !dbg !2389
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file, metadata !2390, metadata !426), !dbg !2391
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2392, metadata !426), !dbg !2393
  %call = call %struct.archive_entry* @archive_entry_new(), !dbg !2394
  store %struct.archive_entry* %call, %struct.archive_entry** %entry1, align 8, !dbg !2395
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2396
  %cmp = icmp eq %struct.archive_entry* %0, null, !dbg !2398
  br i1 %cmp, label %if.then, label %if.end, !dbg !2399

if.then:                                          ; preds = %entry
  %1 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !2400
  store %struct.mtree_entry* null, %struct.mtree_entry** %1, align 8, !dbg !2402
  %2 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2403
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 0, !dbg !2404
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.43, i32 0, i32 0)), !dbg !2405
  store i32 -30, i32* %retval, align 4, !dbg !2406
  br label %return, !dbg !2406

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2407
  %4 = load i8*, i8** %pathname.addr, align 8, !dbg !2408
  call void @archive_entry_copy_pathname(%struct.archive_entry* %3, i8* %4), !dbg !2409
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2410
  call void @archive_entry_set_mode(%struct.archive_entry* %5, i32 16877), !dbg !2411
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2412
  %call2 = call i64 @time(i64* null) #6, !dbg !2413
  call void @archive_entry_set_mtime(%struct.archive_entry* %6, i64 %call2, i64 0), !dbg !2414
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2416
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2417
  %call3 = call i32 @mtree_entry_new(%struct.archive_write* %7, %struct.archive_entry* %8, %struct.mtree_entry** %file), !dbg !2418
  store i32 %call3, i32* %r, align 4, !dbg !2419
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2420
  call void @archive_entry_free(%struct.archive_entry* %9), !dbg !2421
  %10 = load i32, i32* %r, align 4, !dbg !2422
  %cmp4 = icmp slt i32 %10, -20, !dbg !2424
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !2425

if.then5:                                         ; preds = %if.end
  %11 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !2426
  store %struct.mtree_entry* null, %struct.mtree_entry** %11, align 8, !dbg !2428
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2429
  %archive6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 0, !dbg !2430
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.43, i32 0, i32 0)), !dbg !2431
  store i32 -30, i32* %retval, align 4, !dbg !2432
  br label %return, !dbg !2432

if.end7:                                          ; preds = %if.end
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !2433
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 3, !dbg !2434
  %14 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !2434
  %virtual = getelementptr inbounds %struct.dir_info, %struct.dir_info* %14, i32 0, i32 3, !dbg !2435
  store i32 1, i32* %virtual, align 8, !dbg !2436
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %file, align 8, !dbg !2437
  %16 = load %struct.mtree_entry**, %struct.mtree_entry*** %m_entry.addr, align 8, !dbg !2438
  store %struct.mtree_entry* %15, %struct.mtree_entry** %16, align 8, !dbg !2439
  store i32 0, i32* %retval, align 4, !dbg !2440
  br label %return, !dbg !2440

return:                                           ; preds = %if.end7, %if.then5, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !2441
  ret i32 %17, !dbg !2441
}

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_exchange_same_entry(%struct.archive_write* %a, %struct.mtree_entry* %np, %struct.mtree_entry* %file) #0 !dbg !373 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %np.addr = alloca %struct.mtree_entry*, align 8
  %file.addr = alloca %struct.mtree_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2442, metadata !426), !dbg !2443
  store %struct.mtree_entry* %np, %struct.mtree_entry** %np.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %np.addr, metadata !2444, metadata !426), !dbg !2445
  store %struct.mtree_entry* %file, %struct.mtree_entry** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %file.addr, metadata !2446, metadata !426), !dbg !2447
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2448
  %mode = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 14, !dbg !2450
  %1 = load i32, i32* %mode, align 8, !dbg !2450
  %and = and i32 %1, 61440, !dbg !2451
  %2 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2452
  %mode1 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %2, i32 0, i32 14, !dbg !2453
  %3 = load i32, i32* %mode1, align 8, !dbg !2453
  %and2 = and i32 %3, 61440, !dbg !2454
  %cmp = icmp ne i32 %and, %and2, !dbg !2455
  br i1 %cmp, label %if.then, label %if.end, !dbg !2456

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2457
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !2459
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2460
  %pathname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %5, i32 0, i32 7, !dbg !2461
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 0, !dbg !2462
  %6 = load i8*, i8** %s, align 8, !dbg !2462
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @.str.44, i32 0, i32 0), i8* %6), !dbg !2463
  store i32 -25, i32* %retval, align 4, !dbg !2464
  br label %return, !dbg !2464

if.end:                                           ; preds = %entry
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2465
  %symlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %7, i32 0, i32 8, !dbg !2465
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %symlink, i32 0, i32 1, !dbg !2465
  store i64 0, i64* %length, align 8, !dbg !2465
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2466
  %symlink3 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %8, i32 0, i32 8, !dbg !2467
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2468
  %symlink4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 8, !dbg !2469
  call void @archive_string_concat(%struct.archive_string* %symlink3, %struct.archive_string* %symlink4), !dbg !2470
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2471
  %uname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %10, i32 0, i32 9, !dbg !2471
  %length5 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !2471
  store i64 0, i64* %length5, align 8, !dbg !2471
  %11 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2472
  %uname6 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %11, i32 0, i32 9, !dbg !2473
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2474
  %uname7 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %12, i32 0, i32 9, !dbg !2475
  call void @archive_string_concat(%struct.archive_string* %uname6, %struct.archive_string* %uname7), !dbg !2476
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2477
  %gname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 10, !dbg !2477
  %length8 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !2477
  store i64 0, i64* %length8, align 8, !dbg !2477
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2478
  %gname9 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %14, i32 0, i32 10, !dbg !2479
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2480
  %gname10 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %15, i32 0, i32 10, !dbg !2481
  call void @archive_string_concat(%struct.archive_string* %gname9, %struct.archive_string* %gname10), !dbg !2482
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2483
  %fflags_text = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 11, !dbg !2483
  %length11 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text, i32 0, i32 1, !dbg !2483
  store i64 0, i64* %length11, align 8, !dbg !2483
  %17 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2484
  %fflags_text12 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %17, i32 0, i32 11, !dbg !2485
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2486
  %fflags_text13 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %18, i32 0, i32 11, !dbg !2487
  call void @archive_string_concat(%struct.archive_string* %fflags_text12, %struct.archive_string* %fflags_text13), !dbg !2488
  %19 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2489
  %nlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %19, i32 0, i32 12, !dbg !2490
  %20 = load i32, i32* %nlink, align 8, !dbg !2490
  %21 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2491
  %nlink14 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %21, i32 0, i32 12, !dbg !2492
  store i32 %20, i32* %nlink14, align 8, !dbg !2493
  %22 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2494
  %filetype = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %22, i32 0, i32 13, !dbg !2495
  %23 = load i32, i32* %filetype, align 4, !dbg !2495
  %24 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2496
  %filetype15 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %24, i32 0, i32 13, !dbg !2497
  store i32 %23, i32* %filetype15, align 4, !dbg !2498
  %25 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2499
  %mode16 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %25, i32 0, i32 14, !dbg !2500
  %26 = load i32, i32* %mode16, align 8, !dbg !2500
  %27 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2501
  %mode17 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %27, i32 0, i32 14, !dbg !2502
  store i32 %26, i32* %mode17, align 8, !dbg !2503
  %28 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2504
  %size = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %28, i32 0, i32 15, !dbg !2505
  %29 = load i64, i64* %size, align 8, !dbg !2505
  %30 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2506
  %size18 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %30, i32 0, i32 15, !dbg !2507
  store i64 %29, i64* %size18, align 8, !dbg !2508
  %31 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2509
  %uid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %31, i32 0, i32 16, !dbg !2510
  %32 = load i64, i64* %uid, align 8, !dbg !2510
  %33 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2511
  %uid19 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %33, i32 0, i32 16, !dbg !2512
  store i64 %32, i64* %uid19, align 8, !dbg !2513
  %34 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2514
  %gid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %34, i32 0, i32 17, !dbg !2515
  %35 = load i64, i64* %gid, align 8, !dbg !2515
  %36 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2516
  %gid20 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %36, i32 0, i32 17, !dbg !2517
  store i64 %35, i64* %gid20, align 8, !dbg !2518
  %37 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2519
  %fflags_set = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %37, i32 0, i32 20, !dbg !2520
  %38 = load i64, i64* %fflags_set, align 8, !dbg !2520
  %39 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2521
  %fflags_set21 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %39, i32 0, i32 20, !dbg !2522
  store i64 %38, i64* %fflags_set21, align 8, !dbg !2523
  %40 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2524
  %fflags_clear = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %40, i32 0, i32 21, !dbg !2525
  %41 = load i64, i64* %fflags_clear, align 8, !dbg !2525
  %42 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2526
  %fflags_clear22 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %42, i32 0, i32 21, !dbg !2527
  store i64 %41, i64* %fflags_clear22, align 8, !dbg !2528
  %43 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2529
  %mtime = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %43, i32 0, i32 18, !dbg !2530
  %44 = load i64, i64* %mtime, align 8, !dbg !2530
  %45 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2531
  %mtime23 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %45, i32 0, i32 18, !dbg !2532
  store i64 %44, i64* %mtime23, align 8, !dbg !2533
  %46 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2534
  %mtime_nsec = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %46, i32 0, i32 19, !dbg !2535
  %47 = load i64, i64* %mtime_nsec, align 8, !dbg !2535
  %48 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2536
  %mtime_nsec24 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %48, i32 0, i32 19, !dbg !2537
  store i64 %47, i64* %mtime_nsec24, align 8, !dbg !2538
  %49 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2539
  %rdevmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %49, i32 0, i32 22, !dbg !2540
  %50 = load i64, i64* %rdevmajor, align 8, !dbg !2540
  %51 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2541
  %rdevmajor25 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %51, i32 0, i32 22, !dbg !2542
  store i64 %50, i64* %rdevmajor25, align 8, !dbg !2543
  %52 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2544
  %rdevminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %52, i32 0, i32 23, !dbg !2545
  %53 = load i64, i64* %rdevminor, align 8, !dbg !2545
  %54 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2546
  %rdevminor26 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %54, i32 0, i32 23, !dbg !2547
  store i64 %53, i64* %rdevminor26, align 8, !dbg !2548
  %55 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2549
  %devmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %55, i32 0, i32 24, !dbg !2550
  %56 = load i64, i64* %devmajor, align 8, !dbg !2550
  %57 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2551
  %devmajor27 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %57, i32 0, i32 24, !dbg !2552
  store i64 %56, i64* %devmajor27, align 8, !dbg !2553
  %58 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2554
  %devminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %58, i32 0, i32 25, !dbg !2555
  %59 = load i64, i64* %devminor, align 8, !dbg !2555
  %60 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2556
  %devminor28 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %60, i32 0, i32 25, !dbg !2557
  store i64 %59, i64* %devminor28, align 8, !dbg !2558
  %61 = load %struct.mtree_entry*, %struct.mtree_entry** %file.addr, align 8, !dbg !2559
  %ino = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %61, i32 0, i32 26, !dbg !2560
  %62 = load i64, i64* %ino, align 8, !dbg !2560
  %63 = load %struct.mtree_entry*, %struct.mtree_entry** %np.addr, align 8, !dbg !2561
  %ino29 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %63, i32 0, i32 26, !dbg !2562
  store i64 %62, i64* %ino29, align 8, !dbg !2563
  store i32 -20, i32* %retval, align 4, !dbg !2564
  br label %return, !dbg !2564

return:                                           ; preds = %if.end, %if.then
  %64 = load i32, i32* %retval, align 4, !dbg !2565
  ret i32 %64, !dbg !2565
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare %struct.archive_entry* @archive_entry_new() #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind
declare i64 @time(i64*) #3

declare void @archive_entry_free(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @write_mtree_entry_tree(%struct.archive_write* %a) #0 !dbg !378 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %np = alloca %struct.mtree_entry*, align 8
  %n = alloca %struct.archive_rb_node*, align 8
  %ret = alloca i32, align 4
  %e = alloca %struct.mtree_entry*, align 8
  %e27 = alloca %struct.mtree_entry*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2566, metadata !426), !dbg !2567
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !2568, metadata !426), !dbg !2569
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2570
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2571
  %1 = load i8*, i8** %format_data, align 8, !dbg !2571
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !2570
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !2569
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %np, metadata !2572, metadata !426), !dbg !2573
  %3 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2574
  %root = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %3, i32 0, i32 1, !dbg !2575
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %root, align 8, !dbg !2575
  store %struct.mtree_entry* %4, %struct.mtree_entry** %np, align 8, !dbg !2573
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n, metadata !2576, metadata !426), !dbg !2577
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2578, metadata !426), !dbg !2579
  br label %do.body, !dbg !2580

do.body:                                          ; preds = %do.cond, %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2581
  %output_global_set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 19, !dbg !2584
  %6 = load i32, i32* %output_global_set, align 4, !dbg !2584
  %tobool = icmp ne i32 %6, 0, !dbg !2581
  br i1 %tobool, label %if.then, label %if.end7, !dbg !2585

if.then:                                          ; preds = %do.body
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2586
  call void @attr_counter_set_free(%struct.mtree_writer* %7), !dbg !2588
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2589
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %8, i32 0, i32 3, !dbg !2589
  %9 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !2589
  %rbtree = getelementptr inbounds %struct.dir_info, %struct.dir_info* %9, i32 0, i32 0, !dbg !2589
  %call = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_node* null, i32 0), !dbg !2589
  store %struct.archive_rb_node* %call, %struct.archive_rb_node** %n, align 8, !dbg !2589
  br label %for.cond, !dbg !2589

for.cond:                                         ; preds = %for.inc, %if.then
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2591
  %tobool1 = icmp ne %struct.archive_rb_node* %10, null, !dbg !2591
  br i1 %tobool1, label %for.body, label %for.end, !dbg !2591

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %e, metadata !2594, metadata !426), !dbg !2596
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2597
  %12 = bitcast %struct.archive_rb_node* %11 to %struct.mtree_entry*, !dbg !2598
  store %struct.mtree_entry* %12, %struct.mtree_entry** %e, align 8, !dbg !2596
  %13 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2599
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %e, align 8, !dbg !2601
  %call2 = call i32 @attr_counter_set_collect(%struct.mtree_writer* %13, %struct.mtree_entry* %14), !dbg !2602
  %cmp = icmp slt i32 %call2, 0, !dbg !2603
  br i1 %cmp, label %if.then3, label %if.end, !dbg !2604

if.then3:                                         ; preds = %for.body
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2605
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 0, !dbg !2607
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.43, i32 0, i32 0)), !dbg !2608
  store i32 -30, i32* %retval, align 4, !dbg !2609
  br label %return, !dbg !2609

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !2610

for.inc:                                          ; preds = %if.end
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2611
  %dir_info4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 3, !dbg !2611
  %17 = load %struct.dir_info*, %struct.dir_info** %dir_info4, align 8, !dbg !2611
  %rbtree5 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %17, i32 0, i32 0, !dbg !2611
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2611
  %call6 = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree5, %struct.archive_rb_node* %18, i32 1), !dbg !2611
  store %struct.archive_rb_node* %call6, %struct.archive_rb_node** %n, align 8, !dbg !2611
  br label %for.cond, !dbg !2611

for.end:                                          ; preds = %for.cond
  br label %if.end7, !dbg !2613

if.end7:                                          ; preds = %for.end, %do.body
  %19 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2614
  %dir_info8 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %19, i32 0, i32 3, !dbg !2616
  %20 = load %struct.dir_info*, %struct.dir_info** %dir_info8, align 8, !dbg !2616
  %virtual = getelementptr inbounds %struct.dir_info, %struct.dir_info* %20, i32 0, i32 3, !dbg !2617
  %21 = load i32, i32* %virtual, align 8, !dbg !2617
  %tobool9 = icmp ne i32 %21, 0, !dbg !2614
  br i1 %tobool9, label %lor.lhs.false, label %if.then11, !dbg !2618

lor.lhs.false:                                    ; preds = %if.end7
  %22 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2619
  %classic = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %22, i32 0, i32 11, !dbg !2621
  %23 = load i32, i32* %classic, align 8, !dbg !2621
  %tobool10 = icmp ne i32 %23, 0, !dbg !2619
  br i1 %tobool10, label %if.then11, label %if.else, !dbg !2622

if.then11:                                        ; preds = %lor.lhs.false, %if.end7
  %24 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2623
  %25 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2625
  %call12 = call i32 @write_mtree_entry(%struct.archive_write* %24, %struct.mtree_entry* %25), !dbg !2626
  store i32 %call12, i32* %ret, align 4, !dbg !2627
  %26 = load i32, i32* %ret, align 4, !dbg !2628
  %cmp13 = icmp ne i32 %26, 0, !dbg !2630
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !2631

if.then14:                                        ; preds = %if.then11
  store i32 -30, i32* %retval, align 4, !dbg !2632
  br label %return, !dbg !2632

if.end15:                                         ; preds = %if.then11
  br label %if.end20, !dbg !2633

if.else:                                          ; preds = %lor.lhs.false
  %27 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2634
  %output_global_set16 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %27, i32 0, i32 19, !dbg !2637
  %28 = load i32, i32* %output_global_set16, align 4, !dbg !2637
  %tobool17 = icmp ne i32 %28, 0, !dbg !2634
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !2638

if.then18:                                        ; preds = %if.else
  %29 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2639
  call void @write_global(%struct.mtree_writer* %29), !dbg !2640
  br label %if.end19, !dbg !2640

if.end19:                                         ; preds = %if.then18, %if.else
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.end15
  %30 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2641
  %depth = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %30, i32 0, i32 12, !dbg !2642
  %31 = load i32, i32* %depth, align 4, !dbg !2643
  %inc = add nsw i32 %31, 1, !dbg !2643
  store i32 %inc, i32* %depth, align 4, !dbg !2643
  %32 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2644
  %dir_info21 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %32, i32 0, i32 3, !dbg !2644
  %33 = load %struct.dir_info*, %struct.dir_info** %dir_info21, align 8, !dbg !2644
  %rbtree22 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %33, i32 0, i32 0, !dbg !2644
  %call23 = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree22, %struct.archive_rb_node* null, i32 0), !dbg !2644
  store %struct.archive_rb_node* %call23, %struct.archive_rb_node** %n, align 8, !dbg !2644
  br label %for.cond24, !dbg !2644

for.cond24:                                       ; preds = %for.inc38, %if.end20
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2646
  %tobool25 = icmp ne %struct.archive_rb_node* %34, null, !dbg !2646
  br i1 %tobool25, label %for.body26, label %for.end42, !dbg !2646

for.body26:                                       ; preds = %for.cond24
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %e27, metadata !2649, metadata !426), !dbg !2651
  %35 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2652
  %36 = bitcast %struct.archive_rb_node* %35 to %struct.mtree_entry*, !dbg !2653
  store %struct.mtree_entry* %36, %struct.mtree_entry** %e27, align 8, !dbg !2651
  %37 = load %struct.mtree_entry*, %struct.mtree_entry** %e27, align 8, !dbg !2654
  %dir_info28 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %37, i32 0, i32 3, !dbg !2656
  %38 = load %struct.dir_info*, %struct.dir_info** %dir_info28, align 8, !dbg !2656
  %tobool29 = icmp ne %struct.dir_info* %38, null, !dbg !2654
  br i1 %tobool29, label %if.then30, label %if.else32, !dbg !2657

if.then30:                                        ; preds = %for.body26
  %39 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2658
  %40 = load %struct.mtree_entry*, %struct.mtree_entry** %e27, align 8, !dbg !2659
  %call31 = call i32 @mtree_entry_add_child_tail(%struct.mtree_entry* %39, %struct.mtree_entry* %40), !dbg !2660
  br label %if.end37, !dbg !2660

if.else32:                                        ; preds = %for.body26
  %41 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2661
  %42 = load %struct.mtree_entry*, %struct.mtree_entry** %e27, align 8, !dbg !2663
  %call33 = call i32 @write_mtree_entry(%struct.archive_write* %41, %struct.mtree_entry* %42), !dbg !2664
  store i32 %call33, i32* %ret, align 4, !dbg !2665
  %43 = load i32, i32* %ret, align 4, !dbg !2666
  %cmp34 = icmp ne i32 %43, 0, !dbg !2668
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !2669

if.then35:                                        ; preds = %if.else32
  store i32 -30, i32* %retval, align 4, !dbg !2670
  br label %return, !dbg !2670

if.end36:                                         ; preds = %if.else32
  br label %if.end37

if.end37:                                         ; preds = %if.end36, %if.then30
  br label %for.inc38, !dbg !2671

for.inc38:                                        ; preds = %if.end37
  %44 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2672
  %dir_info39 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %44, i32 0, i32 3, !dbg !2672
  %45 = load %struct.dir_info*, %struct.dir_info** %dir_info39, align 8, !dbg !2672
  %rbtree40 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %45, i32 0, i32 0, !dbg !2672
  %46 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !2672
  %call41 = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree40, %struct.archive_rb_node* %46, i32 1), !dbg !2672
  store %struct.archive_rb_node* %call41, %struct.archive_rb_node** %n, align 8, !dbg !2672
  br label %for.cond24, !dbg !2672

for.end42:                                        ; preds = %for.cond24
  %47 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2674
  %depth43 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %47, i32 0, i32 12, !dbg !2675
  %48 = load i32, i32* %depth43, align 4, !dbg !2676
  %dec = add nsw i32 %48, -1, !dbg !2676
  store i32 %dec, i32* %depth43, align 4, !dbg !2676
  %49 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2677
  %dir_info44 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %49, i32 0, i32 3, !dbg !2679
  %50 = load %struct.dir_info*, %struct.dir_info** %dir_info44, align 8, !dbg !2679
  %children = getelementptr inbounds %struct.dir_info, %struct.dir_info* %50, i32 0, i32 1, !dbg !2680
  %first = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children, i32 0, i32 0, !dbg !2681
  %51 = load %struct.mtree_entry*, %struct.mtree_entry** %first, align 8, !dbg !2681
  %cmp45 = icmp ne %struct.mtree_entry* %51, null, !dbg !2682
  br i1 %cmp45, label %if.then46, label %if.else55, !dbg !2683

if.then46:                                        ; preds = %for.end42
  %52 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2684
  %dir_info47 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %52, i32 0, i32 3, !dbg !2686
  %53 = load %struct.dir_info*, %struct.dir_info** %dir_info47, align 8, !dbg !2686
  %children48 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %53, i32 0, i32 1, !dbg !2687
  %first49 = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children48, i32 0, i32 0, !dbg !2688
  %54 = load %struct.mtree_entry*, %struct.mtree_entry** %first49, align 8, !dbg !2688
  store %struct.mtree_entry* %54, %struct.mtree_entry** %np, align 8, !dbg !2689
  %55 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2690
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %55, i32 0, i32 18, !dbg !2692
  %56 = load i32, i32* %indent, align 8, !dbg !2692
  %tobool50 = icmp ne i32 %56, 0, !dbg !2690
  br i1 %tobool50, label %if.then51, label %if.end54, !dbg !2693

if.then51:                                        ; preds = %if.then46
  %57 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2694
  %depth52 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %57, i32 0, i32 12, !dbg !2695
  %58 = load i32, i32* %depth52, align 4, !dbg !2696
  %inc53 = add nsw i32 %58, 1, !dbg !2696
  store i32 %inc53, i32* %depth52, align 4, !dbg !2696
  br label %if.end54, !dbg !2694

if.end54:                                         ; preds = %if.then51, %if.then46
  br label %do.cond, !dbg !2697

if.else55:                                        ; preds = %for.end42
  %59 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2698
  %classic56 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %59, i32 0, i32 11, !dbg !2700
  %60 = load i32, i32* %classic56, align 8, !dbg !2700
  %tobool57 = icmp ne i32 %60, 0, !dbg !2698
  br i1 %tobool57, label %if.then58, label %if.end63, !dbg !2701

if.then58:                                        ; preds = %if.else55
  %61 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2702
  %62 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2704
  %call59 = call i32 @write_dot_dot_entry(%struct.archive_write* %61, %struct.mtree_entry* %62), !dbg !2705
  store i32 %call59, i32* %ret, align 4, !dbg !2706
  %63 = load i32, i32* %ret, align 4, !dbg !2707
  %cmp60 = icmp ne i32 %63, 0, !dbg !2709
  br i1 %cmp60, label %if.then61, label %if.end62, !dbg !2710

if.then61:                                        ; preds = %if.then58
  store i32 -30, i32* %retval, align 4, !dbg !2711
  br label %return, !dbg !2711

if.end62:                                         ; preds = %if.then58
  br label %if.end63, !dbg !2712

if.end63:                                         ; preds = %if.end62, %if.else55
  br label %if.end64

if.end64:                                         ; preds = %if.end63
  br label %while.cond, !dbg !2713

while.cond:                                       ; preds = %if.end88, %if.end64
  %64 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2714
  %65 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2716
  %parent = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %65, i32 0, i32 2, !dbg !2717
  %66 = load %struct.mtree_entry*, %struct.mtree_entry** %parent, align 8, !dbg !2717
  %cmp65 = icmp ne %struct.mtree_entry* %64, %66, !dbg !2718
  br i1 %cmp65, label %while.body, label %while.end, !dbg !2719

while.body:                                       ; preds = %while.cond
  %67 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2720
  %dir_info66 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %67, i32 0, i32 3, !dbg !2723
  %68 = load %struct.dir_info*, %struct.dir_info** %dir_info66, align 8, !dbg !2723
  %chnext = getelementptr inbounds %struct.dir_info, %struct.dir_info* %68, i32 0, i32 2, !dbg !2724
  %69 = load %struct.mtree_entry*, %struct.mtree_entry** %chnext, align 8, !dbg !2724
  %cmp67 = icmp eq %struct.mtree_entry* %69, null, !dbg !2725
  br i1 %cmp67, label %if.then68, label %if.else85, !dbg !2726

if.then68:                                        ; preds = %while.body
  %70 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2727
  %indent69 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %70, i32 0, i32 18, !dbg !2730
  %71 = load i32, i32* %indent69, align 8, !dbg !2730
  %tobool70 = icmp ne i32 %71, 0, !dbg !2727
  br i1 %tobool70, label %if.then71, label %if.end74, !dbg !2731

if.then71:                                        ; preds = %if.then68
  %72 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2732
  %depth72 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %72, i32 0, i32 12, !dbg !2733
  %73 = load i32, i32* %depth72, align 4, !dbg !2734
  %dec73 = add nsw i32 %73, -1, !dbg !2734
  store i32 %dec73, i32* %depth72, align 4, !dbg !2734
  br label %if.end74, !dbg !2732

if.end74:                                         ; preds = %if.then71, %if.then68
  %74 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !2735
  %classic75 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %74, i32 0, i32 11, !dbg !2737
  %75 = load i32, i32* %classic75, align 8, !dbg !2737
  %tobool76 = icmp ne i32 %75, 0, !dbg !2735
  br i1 %tobool76, label %if.then77, label %if.end83, !dbg !2738

if.then77:                                        ; preds = %if.end74
  %76 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2739
  %77 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2741
  %parent78 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %77, i32 0, i32 2, !dbg !2742
  %78 = load %struct.mtree_entry*, %struct.mtree_entry** %parent78, align 8, !dbg !2742
  %call79 = call i32 @write_dot_dot_entry(%struct.archive_write* %76, %struct.mtree_entry* %78), !dbg !2743
  store i32 %call79, i32* %ret, align 4, !dbg !2744
  %79 = load i32, i32* %ret, align 4, !dbg !2745
  %cmp80 = icmp ne i32 %79, 0, !dbg !2747
  br i1 %cmp80, label %if.then81, label %if.end82, !dbg !2748

if.then81:                                        ; preds = %if.then77
  store i32 -30, i32* %retval, align 4, !dbg !2749
  br label %return, !dbg !2749

if.end82:                                         ; preds = %if.then77
  br label %if.end83, !dbg !2750

if.end83:                                         ; preds = %if.end82, %if.end74
  %80 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2751
  %parent84 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %80, i32 0, i32 2, !dbg !2752
  %81 = load %struct.mtree_entry*, %struct.mtree_entry** %parent84, align 8, !dbg !2752
  store %struct.mtree_entry* %81, %struct.mtree_entry** %np, align 8, !dbg !2753
  br label %if.end88, !dbg !2754

if.else85:                                        ; preds = %while.body
  %82 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2755
  %dir_info86 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %82, i32 0, i32 3, !dbg !2757
  %83 = load %struct.dir_info*, %struct.dir_info** %dir_info86, align 8, !dbg !2757
  %chnext87 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %83, i32 0, i32 2, !dbg !2758
  %84 = load %struct.mtree_entry*, %struct.mtree_entry** %chnext87, align 8, !dbg !2758
  store %struct.mtree_entry* %84, %struct.mtree_entry** %np, align 8, !dbg !2759
  br label %while.end, !dbg !2760

if.end88:                                         ; preds = %if.end83
  br label %while.cond, !dbg !2761

while.end:                                        ; preds = %if.else85, %while.cond
  br label %do.cond, !dbg !2763

do.cond:                                          ; preds = %while.end, %if.end54
  %85 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2764
  %86 = load %struct.mtree_entry*, %struct.mtree_entry** %np, align 8, !dbg !2766
  %parent89 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %86, i32 0, i32 2, !dbg !2767
  %87 = load %struct.mtree_entry*, %struct.mtree_entry** %parent89, align 8, !dbg !2767
  %cmp90 = icmp ne %struct.mtree_entry* %85, %87, !dbg !2768
  br i1 %cmp90, label %do.body, label %do.end, !dbg !2769

do.end:                                           ; preds = %do.cond
  store i32 0, i32* %retval, align 4, !dbg !2770
  br label %return, !dbg !2770

return:                                           ; preds = %do.end, %if.then81, %if.then61, %if.then35, %if.then14, %if.then3
  %88 = load i32, i32* %retval, align 4, !dbg !2771
  ret i32 %88, !dbg !2771
}

declare i32 @archive_write_set_bytes_in_last_block(%struct.archive*, i32) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree*, %struct.archive_rb_node*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @attr_counter_set_collect(%struct.mtree_writer* %mtree, %struct.mtree_entry* %me) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %me.addr = alloca %struct.mtree_entry*, align 8
  %ac = alloca %struct.attr_counter*, align 8
  %last = alloca %struct.attr_counter*, align 8
  %acs = alloca %struct.att_counter_set*, align 8
  %keys = alloca i32, align 4
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !2772, metadata !426), !dbg !2773
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !2774, metadata !426), !dbg !2775
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %ac, metadata !2776, metadata !426), !dbg !2777
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %last, metadata !2778, metadata !426), !dbg !2779
  call void @llvm.dbg.declare(metadata %struct.att_counter_set** %acs, metadata !2780, metadata !426), !dbg !2781
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !2782
  %acs1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 10, !dbg !2783
  store %struct.att_counter_set* %acs1, %struct.att_counter_set** %acs, align 8, !dbg !2781
  call void @llvm.dbg.declare(metadata i32* %keys, metadata !2784, metadata !426), !dbg !2785
  %1 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !2786
  %keys2 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %1, i32 0, i32 16, !dbg !2787
  %2 = load i32, i32* %keys2, align 8, !dbg !2787
  store i32 %2, i32* %keys, align 4, !dbg !2785
  %3 = load i32, i32* %keys, align 4, !dbg !2788
  %and = and i32 %3, 3145728, !dbg !2790
  %tobool = icmp ne i32 %and, 0, !dbg !2790
  br i1 %tobool, label %if.then, label %if.end20, !dbg !2791

if.then:                                          ; preds = %entry
  %4 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2792
  %uid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %4, i32 0, i32 0, !dbg !2795
  %5 = load %struct.attr_counter*, %struct.attr_counter** %uid_list, align 8, !dbg !2795
  %cmp = icmp eq %struct.attr_counter* %5, null, !dbg !2796
  br i1 %cmp, label %if.then3, label %if.else, !dbg !2797

if.then3:                                         ; preds = %if.then
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2798
  %call = call %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %6, %struct.attr_counter* null), !dbg !2800
  %7 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2801
  %uid_list4 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %7, i32 0, i32 0, !dbg !2802
  store %struct.attr_counter* %call, %struct.attr_counter** %uid_list4, align 8, !dbg !2803
  %8 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2804
  %uid_list5 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %8, i32 0, i32 0, !dbg !2806
  %9 = load %struct.attr_counter*, %struct.attr_counter** %uid_list5, align 8, !dbg !2806
  %cmp6 = icmp eq %struct.attr_counter* %9, null, !dbg !2807
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !2808

if.then7:                                         ; preds = %if.then3
  store i32 -1, i32* %retval, align 4, !dbg !2809
  br label %return, !dbg !2809

if.end:                                           ; preds = %if.then3
  br label %if.end19, !dbg !2810

if.else:                                          ; preds = %if.then
  store %struct.attr_counter* null, %struct.attr_counter** %last, align 8, !dbg !2811
  %10 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2813
  %uid_list8 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %10, i32 0, i32 0, !dbg !2815
  %11 = load %struct.attr_counter*, %struct.attr_counter** %uid_list8, align 8, !dbg !2815
  store %struct.attr_counter* %11, %struct.attr_counter** %ac, align 8, !dbg !2816
  br label %for.cond, !dbg !2817

for.cond:                                         ; preds = %for.inc, %if.else
  %12 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2818
  %tobool9 = icmp ne %struct.attr_counter* %12, null, !dbg !2821
  br i1 %tobool9, label %for.body, label %for.end, !dbg !2821

for.body:                                         ; preds = %for.cond
  %13 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2822
  %m_entry = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %13, i32 0, i32 2, !dbg !2825
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry, align 8, !dbg !2825
  %uid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %14, i32 0, i32 16, !dbg !2826
  %15 = load i64, i64* %uid, align 8, !dbg !2826
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2827
  %uid10 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 16, !dbg !2828
  %17 = load i64, i64* %uid10, align 8, !dbg !2828
  %cmp11 = icmp eq i64 %15, %17, !dbg !2829
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !2830

if.then12:                                        ; preds = %for.body
  br label %for.end, !dbg !2831

if.end13:                                         ; preds = %for.body
  %18 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2832
  store %struct.attr_counter* %18, %struct.attr_counter** %last, align 8, !dbg !2833
  br label %for.inc, !dbg !2834

for.inc:                                          ; preds = %if.end13
  %19 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2835
  %next = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %19, i32 0, i32 1, !dbg !2837
  %20 = load %struct.attr_counter*, %struct.attr_counter** %next, align 8, !dbg !2837
  store %struct.attr_counter* %20, %struct.attr_counter** %ac, align 8, !dbg !2838
  br label %for.cond, !dbg !2839

for.end:                                          ; preds = %if.then12, %for.cond
  %21 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2840
  %uid_list14 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %21, i32 0, i32 0, !dbg !2842
  %22 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2843
  %23 = load %struct.attr_counter*, %struct.attr_counter** %last, align 8, !dbg !2844
  %24 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2845
  %call15 = call i32 @attr_counter_inc(%struct.attr_counter** %uid_list14, %struct.attr_counter* %22, %struct.attr_counter* %23, %struct.mtree_entry* %24), !dbg !2846
  %cmp16 = icmp slt i32 %call15, 0, !dbg !2847
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !2848

if.then17:                                        ; preds = %for.end
  store i32 -1, i32* %retval, align 4, !dbg !2849
  br label %return, !dbg !2849

if.end18:                                         ; preds = %for.end
  br label %if.end19

if.end19:                                         ; preds = %if.end18, %if.end
  br label %if.end20, !dbg !2850

if.end20:                                         ; preds = %if.end19, %entry
  %25 = load i32, i32* %keys, align 4, !dbg !2851
  %and21 = and i32 %25, 48, !dbg !2853
  %tobool22 = icmp ne i32 %and21, 0, !dbg !2853
  br i1 %tobool22, label %if.then23, label %if.end51, !dbg !2854

if.then23:                                        ; preds = %if.end20
  %26 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2855
  %gid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %26, i32 0, i32 1, !dbg !2858
  %27 = load %struct.attr_counter*, %struct.attr_counter** %gid_list, align 8, !dbg !2858
  %cmp24 = icmp eq %struct.attr_counter* %27, null, !dbg !2859
  br i1 %cmp24, label %if.then25, label %if.else32, !dbg !2860

if.then25:                                        ; preds = %if.then23
  %28 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2861
  %call26 = call %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %28, %struct.attr_counter* null), !dbg !2863
  %29 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2864
  %gid_list27 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %29, i32 0, i32 1, !dbg !2865
  store %struct.attr_counter* %call26, %struct.attr_counter** %gid_list27, align 8, !dbg !2866
  %30 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2867
  %gid_list28 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %30, i32 0, i32 1, !dbg !2869
  %31 = load %struct.attr_counter*, %struct.attr_counter** %gid_list28, align 8, !dbg !2869
  %cmp29 = icmp eq %struct.attr_counter* %31, null, !dbg !2870
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !2871

if.then30:                                        ; preds = %if.then25
  store i32 -1, i32* %retval, align 4, !dbg !2872
  br label %return, !dbg !2872

if.end31:                                         ; preds = %if.then25
  br label %if.end50, !dbg !2873

if.else32:                                        ; preds = %if.then23
  store %struct.attr_counter* null, %struct.attr_counter** %last, align 8, !dbg !2874
  %32 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2876
  %gid_list33 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %32, i32 0, i32 1, !dbg !2878
  %33 = load %struct.attr_counter*, %struct.attr_counter** %gid_list33, align 8, !dbg !2878
  store %struct.attr_counter* %33, %struct.attr_counter** %ac, align 8, !dbg !2879
  br label %for.cond34, !dbg !2880

for.cond34:                                       ; preds = %for.inc42, %if.else32
  %34 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2881
  %tobool35 = icmp ne %struct.attr_counter* %34, null, !dbg !2884
  br i1 %tobool35, label %for.body36, label %for.end44, !dbg !2884

for.body36:                                       ; preds = %for.cond34
  %35 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2885
  %m_entry37 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %35, i32 0, i32 2, !dbg !2888
  %36 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry37, align 8, !dbg !2888
  %gid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %36, i32 0, i32 17, !dbg !2889
  %37 = load i64, i64* %gid, align 8, !dbg !2889
  %38 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2890
  %gid38 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %38, i32 0, i32 17, !dbg !2891
  %39 = load i64, i64* %gid38, align 8, !dbg !2891
  %cmp39 = icmp eq i64 %37, %39, !dbg !2892
  br i1 %cmp39, label %if.then40, label %if.end41, !dbg !2893

if.then40:                                        ; preds = %for.body36
  br label %for.end44, !dbg !2894

if.end41:                                         ; preds = %for.body36
  %40 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2895
  store %struct.attr_counter* %40, %struct.attr_counter** %last, align 8, !dbg !2896
  br label %for.inc42, !dbg !2897

for.inc42:                                        ; preds = %if.end41
  %41 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2898
  %next43 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %41, i32 0, i32 1, !dbg !2900
  %42 = load %struct.attr_counter*, %struct.attr_counter** %next43, align 8, !dbg !2900
  store %struct.attr_counter* %42, %struct.attr_counter** %ac, align 8, !dbg !2901
  br label %for.cond34, !dbg !2902

for.end44:                                        ; preds = %if.then40, %for.cond34
  %43 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2903
  %gid_list45 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %43, i32 0, i32 1, !dbg !2905
  %44 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2906
  %45 = load %struct.attr_counter*, %struct.attr_counter** %last, align 8, !dbg !2907
  %46 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2908
  %call46 = call i32 @attr_counter_inc(%struct.attr_counter** %gid_list45, %struct.attr_counter* %44, %struct.attr_counter* %45, %struct.mtree_entry* %46), !dbg !2909
  %cmp47 = icmp slt i32 %call46, 0, !dbg !2910
  br i1 %cmp47, label %if.then48, label %if.end49, !dbg !2911

if.then48:                                        ; preds = %for.end44
  store i32 -1, i32* %retval, align 4, !dbg !2912
  br label %return, !dbg !2912

if.end49:                                         ; preds = %for.end44
  br label %if.end50

if.end50:                                         ; preds = %if.end49, %if.end31
  br label %if.end51, !dbg !2913

if.end51:                                         ; preds = %if.end50, %if.end20
  %47 = load i32, i32* %keys, align 4, !dbg !2914
  %and52 = and i32 %47, 512, !dbg !2916
  %tobool53 = icmp ne i32 %and52, 0, !dbg !2916
  br i1 %tobool53, label %if.then54, label %if.end82, !dbg !2917

if.then54:                                        ; preds = %if.end51
  %48 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2918
  %mode_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %48, i32 0, i32 2, !dbg !2921
  %49 = load %struct.attr_counter*, %struct.attr_counter** %mode_list, align 8, !dbg !2921
  %cmp55 = icmp eq %struct.attr_counter* %49, null, !dbg !2922
  br i1 %cmp55, label %if.then56, label %if.else63, !dbg !2923

if.then56:                                        ; preds = %if.then54
  %50 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2924
  %call57 = call %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %50, %struct.attr_counter* null), !dbg !2926
  %51 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2927
  %mode_list58 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %51, i32 0, i32 2, !dbg !2928
  store %struct.attr_counter* %call57, %struct.attr_counter** %mode_list58, align 8, !dbg !2929
  %52 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2930
  %mode_list59 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %52, i32 0, i32 2, !dbg !2932
  %53 = load %struct.attr_counter*, %struct.attr_counter** %mode_list59, align 8, !dbg !2932
  %cmp60 = icmp eq %struct.attr_counter* %53, null, !dbg !2933
  br i1 %cmp60, label %if.then61, label %if.end62, !dbg !2934

if.then61:                                        ; preds = %if.then56
  store i32 -1, i32* %retval, align 4, !dbg !2935
  br label %return, !dbg !2935

if.end62:                                         ; preds = %if.then56
  br label %if.end81, !dbg !2936

if.else63:                                        ; preds = %if.then54
  store %struct.attr_counter* null, %struct.attr_counter** %last, align 8, !dbg !2937
  %54 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2939
  %mode_list64 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %54, i32 0, i32 2, !dbg !2941
  %55 = load %struct.attr_counter*, %struct.attr_counter** %mode_list64, align 8, !dbg !2941
  store %struct.attr_counter* %55, %struct.attr_counter** %ac, align 8, !dbg !2942
  br label %for.cond65, !dbg !2943

for.cond65:                                       ; preds = %for.inc73, %if.else63
  %56 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2944
  %tobool66 = icmp ne %struct.attr_counter* %56, null, !dbg !2947
  br i1 %tobool66, label %for.body67, label %for.end75, !dbg !2947

for.body67:                                       ; preds = %for.cond65
  %57 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2948
  %m_entry68 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %57, i32 0, i32 2, !dbg !2951
  %58 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry68, align 8, !dbg !2951
  %mode = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %58, i32 0, i32 14, !dbg !2952
  %59 = load i32, i32* %mode, align 8, !dbg !2952
  %60 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2953
  %mode69 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %60, i32 0, i32 14, !dbg !2954
  %61 = load i32, i32* %mode69, align 8, !dbg !2954
  %cmp70 = icmp eq i32 %59, %61, !dbg !2955
  br i1 %cmp70, label %if.then71, label %if.end72, !dbg !2956

if.then71:                                        ; preds = %for.body67
  br label %for.end75, !dbg !2957

if.end72:                                         ; preds = %for.body67
  %62 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2958
  store %struct.attr_counter* %62, %struct.attr_counter** %last, align 8, !dbg !2959
  br label %for.inc73, !dbg !2960

for.inc73:                                        ; preds = %if.end72
  %63 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2961
  %next74 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %63, i32 0, i32 1, !dbg !2963
  %64 = load %struct.attr_counter*, %struct.attr_counter** %next74, align 8, !dbg !2963
  store %struct.attr_counter* %64, %struct.attr_counter** %ac, align 8, !dbg !2964
  br label %for.cond65, !dbg !2965

for.end75:                                        ; preds = %if.then71, %for.cond65
  %65 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2966
  %mode_list76 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %65, i32 0, i32 2, !dbg !2968
  %66 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !2969
  %67 = load %struct.attr_counter*, %struct.attr_counter** %last, align 8, !dbg !2970
  %68 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2971
  %call77 = call i32 @attr_counter_inc(%struct.attr_counter** %mode_list76, %struct.attr_counter* %66, %struct.attr_counter* %67, %struct.mtree_entry* %68), !dbg !2972
  %cmp78 = icmp slt i32 %call77, 0, !dbg !2973
  br i1 %cmp78, label %if.then79, label %if.end80, !dbg !2974

if.then79:                                        ; preds = %for.end75
  store i32 -1, i32* %retval, align 4, !dbg !2975
  br label %return, !dbg !2975

if.end80:                                         ; preds = %for.end75
  br label %if.end81

if.end81:                                         ; preds = %if.end80, %if.end62
  br label %if.end82, !dbg !2976

if.end82:                                         ; preds = %if.end81, %if.end51
  %69 = load i32, i32* %keys, align 4, !dbg !2977
  %and83 = and i32 %69, 8, !dbg !2979
  %tobool84 = icmp ne i32 %and83, 0, !dbg !2979
  br i1 %tobool84, label %if.then85, label %if.end116, !dbg !2980

if.then85:                                        ; preds = %if.end82
  %70 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2981
  %flags_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %70, i32 0, i32 3, !dbg !2984
  %71 = load %struct.attr_counter*, %struct.attr_counter** %flags_list, align 8, !dbg !2984
  %cmp86 = icmp eq %struct.attr_counter* %71, null, !dbg !2985
  br i1 %cmp86, label %if.then87, label %if.else94, !dbg !2986

if.then87:                                        ; preds = %if.then85
  %72 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !2987
  %call88 = call %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %72, %struct.attr_counter* null), !dbg !2989
  %73 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2990
  %flags_list89 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %73, i32 0, i32 3, !dbg !2991
  store %struct.attr_counter* %call88, %struct.attr_counter** %flags_list89, align 8, !dbg !2992
  %74 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !2993
  %flags_list90 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %74, i32 0, i32 3, !dbg !2995
  %75 = load %struct.attr_counter*, %struct.attr_counter** %flags_list90, align 8, !dbg !2995
  %cmp91 = icmp eq %struct.attr_counter* %75, null, !dbg !2996
  br i1 %cmp91, label %if.then92, label %if.end93, !dbg !2997

if.then92:                                        ; preds = %if.then87
  store i32 -1, i32* %retval, align 4, !dbg !2998
  br label %return, !dbg !2998

if.end93:                                         ; preds = %if.then87
  br label %if.end115, !dbg !2999

if.else94:                                        ; preds = %if.then85
  store %struct.attr_counter* null, %struct.attr_counter** %last, align 8, !dbg !3000
  %76 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3002
  %flags_list95 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %76, i32 0, i32 3, !dbg !3004
  %77 = load %struct.attr_counter*, %struct.attr_counter** %flags_list95, align 8, !dbg !3004
  store %struct.attr_counter* %77, %struct.attr_counter** %ac, align 8, !dbg !3005
  br label %for.cond96, !dbg !3006

for.cond96:                                       ; preds = %for.inc107, %if.else94
  %78 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3007
  %tobool97 = icmp ne %struct.attr_counter* %78, null, !dbg !3010
  br i1 %tobool97, label %for.body98, label %for.end109, !dbg !3010

for.body98:                                       ; preds = %for.cond96
  %79 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3011
  %m_entry99 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %79, i32 0, i32 2, !dbg !3014
  %80 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry99, align 8, !dbg !3014
  %fflags_set = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %80, i32 0, i32 20, !dbg !3015
  %81 = load i64, i64* %fflags_set, align 8, !dbg !3015
  %82 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3016
  %fflags_set100 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %82, i32 0, i32 20, !dbg !3017
  %83 = load i64, i64* %fflags_set100, align 8, !dbg !3017
  %cmp101 = icmp eq i64 %81, %83, !dbg !3018
  br i1 %cmp101, label %land.lhs.true, label %if.end106, !dbg !3019

land.lhs.true:                                    ; preds = %for.body98
  %84 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3020
  %m_entry102 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %84, i32 0, i32 2, !dbg !3021
  %85 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry102, align 8, !dbg !3021
  %fflags_clear = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %85, i32 0, i32 21, !dbg !3022
  %86 = load i64, i64* %fflags_clear, align 8, !dbg !3022
  %87 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3023
  %fflags_clear103 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %87, i32 0, i32 21, !dbg !3024
  %88 = load i64, i64* %fflags_clear103, align 8, !dbg !3024
  %cmp104 = icmp eq i64 %86, %88, !dbg !3025
  br i1 %cmp104, label %if.then105, label %if.end106, !dbg !3026

if.then105:                                       ; preds = %land.lhs.true
  br label %for.end109, !dbg !3028

if.end106:                                        ; preds = %land.lhs.true, %for.body98
  %89 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3029
  store %struct.attr_counter* %89, %struct.attr_counter** %last, align 8, !dbg !3030
  br label %for.inc107, !dbg !3031

for.inc107:                                       ; preds = %if.end106
  %90 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3032
  %next108 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %90, i32 0, i32 1, !dbg !3034
  %91 = load %struct.attr_counter*, %struct.attr_counter** %next108, align 8, !dbg !3034
  store %struct.attr_counter* %91, %struct.attr_counter** %ac, align 8, !dbg !3035
  br label %for.cond96, !dbg !3036

for.end109:                                       ; preds = %if.then105, %for.cond96
  %92 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3037
  %flags_list110 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %92, i32 0, i32 3, !dbg !3039
  %93 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !3040
  %94 = load %struct.attr_counter*, %struct.attr_counter** %last, align 8, !dbg !3041
  %95 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3042
  %call111 = call i32 @attr_counter_inc(%struct.attr_counter** %flags_list110, %struct.attr_counter* %93, %struct.attr_counter* %94, %struct.mtree_entry* %95), !dbg !3043
  %cmp112 = icmp slt i32 %call111, 0, !dbg !3044
  br i1 %cmp112, label %if.then113, label %if.end114, !dbg !3045

if.then113:                                       ; preds = %for.end109
  store i32 -1, i32* %retval, align 4, !dbg !3046
  br label %return, !dbg !3046

if.end114:                                        ; preds = %for.end109
  br label %if.end115

if.end115:                                        ; preds = %if.end114, %if.end93
  br label %if.end116, !dbg !3047

if.end116:                                        ; preds = %if.end115, %if.end82
  store i32 0, i32* %retval, align 4, !dbg !3048
  br label %return, !dbg !3048

return:                                           ; preds = %if.end116, %if.then113, %if.then92, %if.then79, %if.then61, %if.then48, %if.then30, %if.then17, %if.then7
  %96 = load i32, i32* %retval, align 4, !dbg !3049
  ret i32 %96, !dbg !3049
}

; Function Attrs: nounwind uwtable
define internal i32 @write_mtree_entry(%struct.archive_write* %a, %struct.mtree_entry* %me) #0 !dbg !388 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %me.addr = alloca %struct.mtree_entry*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %str = alloca %struct.archive_string*, align 8
  %keys = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3050, metadata !426), !dbg !3051
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !3052, metadata !426), !dbg !3053
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !3054, metadata !426), !dbg !3055
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3056
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3057
  %1 = load i8*, i8** %format_data, align 8, !dbg !3057
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !3056
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !3055
  call void @llvm.dbg.declare(metadata %struct.archive_string** %str, metadata !3058, metadata !426), !dbg !3059
  call void @llvm.dbg.declare(metadata i32* %keys, metadata !3060, metadata !426), !dbg !3061
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3062, metadata !426), !dbg !3063
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3064
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 3, !dbg !3066
  %4 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !3066
  %tobool = icmp ne %struct.dir_info* %4, null, !dbg !3064
  br i1 %tobool, label %if.then, label %if.end19, !dbg !3067

if.then:                                          ; preds = %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3068
  %classic = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 11, !dbg !3071
  %6 = load i32, i32* %classic, align 8, !dbg !3071
  %tobool1 = icmp ne i32 %6, 0, !dbg !3068
  br i1 %tobool1, label %if.then2, label %if.end15, !dbg !3072

if.then2:                                         ; preds = %if.then
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3073
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 17, !dbg !3076
  %8 = load i32, i32* %dironly, align 4, !dbg !3076
  %tobool3 = icmp ne i32 %8, 0, !dbg !3073
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !3077

if.then4:                                         ; preds = %if.then2
  %9 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3078
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %9, i32 0, i32 6, !dbg !3079
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf, i8 signext 10), !dbg !3080
  br label %if.end, !dbg !3080

if.end:                                           ; preds = %if.then4, %if.then2
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3081
  %parentdir = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %10, i32 0, i32 5, !dbg !3083
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir, i32 0, i32 0, !dbg !3084
  %11 = load i8*, i8** %s, align 8, !dbg !3084
  %tobool5 = icmp ne i8* %11, null, !dbg !3081
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !3085

if.then6:                                         ; preds = %if.end
  %12 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3086
  %buf7 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %12, i32 0, i32 6, !dbg !3087
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3088
  %parentdir8 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 5, !dbg !3089
  %s9 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir8, i32 0, i32 0, !dbg !3090
  %14 = load i8*, i8** %s9, align 8, !dbg !3090
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3091
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %15, i32 0, i32 6, !dbg !3092
  %s10 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 0, !dbg !3093
  %16 = load i8*, i8** %s10, align 8, !dbg !3093
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %buf7, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.45, i32 0, i32 0), i8* %14, i8* %16), !dbg !3094
  br label %if.end14, !dbg !3094

if.else:                                          ; preds = %if.end
  %17 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3095
  %buf11 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %17, i32 0, i32 6, !dbg !3096
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3097
  %basename12 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %18, i32 0, i32 6, !dbg !3098
  %s13 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename12, i32 0, i32 0, !dbg !3099
  %19 = load i8*, i8** %s13, align 8, !dbg !3099
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %buf11, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.46, i32 0, i32 0), i8* %19), !dbg !3100
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then6
  br label %if.end15, !dbg !3101

if.end15:                                         ; preds = %if.end14, %if.then
  %20 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3102
  %output_global_set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %20, i32 0, i32 19, !dbg !3104
  %21 = load i32, i32* %output_global_set, align 4, !dbg !3104
  %tobool16 = icmp ne i32 %21, 0, !dbg !3102
  br i1 %tobool16, label %if.then17, label %if.end18, !dbg !3105

if.then17:                                        ; preds = %if.end15
  %22 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3106
  call void @write_global(%struct.mtree_writer* %22), !dbg !3107
  br label %if.end18, !dbg !3107

if.end18:                                         ; preds = %if.then17, %if.end15
  br label %if.end19, !dbg !3108

if.end19:                                         ; preds = %if.end18, %entry
  %23 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3109
  %ebuf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %23, i32 0, i32 5, !dbg !3109
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf, i32 0, i32 1, !dbg !3109
  store i64 0, i64* %length, align 8, !dbg !3109
  %24 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3110
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %24, i32 0, i32 18, !dbg !3111
  %25 = load i32, i32* %indent, align 8, !dbg !3111
  %tobool20 = icmp ne i32 %25, 0, !dbg !3110
  br i1 %tobool20, label %cond.true, label %lor.lhs.false, !dbg !3112

lor.lhs.false:                                    ; preds = %if.end19
  %26 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3113
  %classic21 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %26, i32 0, i32 11, !dbg !3115
  %27 = load i32, i32* %classic21, align 8, !dbg !3115
  %tobool22 = icmp ne i32 %27, 0, !dbg !3113
  br i1 %tobool22, label %cond.true, label %cond.false, !dbg !3116

cond.true:                                        ; preds = %lor.lhs.false, %if.end19
  %28 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3117
  %ebuf23 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %28, i32 0, i32 5, !dbg !3119
  br label %cond.end, !dbg !3120

cond.false:                                       ; preds = %lor.lhs.false
  %29 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3121
  %buf24 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %29, i32 0, i32 6, !dbg !3123
  br label %cond.end, !dbg !3124

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct.archive_string* [ %ebuf23, %cond.true ], [ %buf24, %cond.false ], !dbg !3125
  store %struct.archive_string* %cond, %struct.archive_string** %str, align 8, !dbg !3127
  %30 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3128
  %classic25 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %30, i32 0, i32 11, !dbg !3130
  %31 = load i32, i32* %classic25, align 8, !dbg !3130
  %tobool26 = icmp ne i32 %31, 0, !dbg !3128
  br i1 %tobool26, label %if.end34, label %land.lhs.true, !dbg !3131

land.lhs.true:                                    ; preds = %cond.end
  %32 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3132
  %parentdir27 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %32, i32 0, i32 5, !dbg !3134
  %s28 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir27, i32 0, i32 0, !dbg !3135
  %33 = load i8*, i8** %s28, align 8, !dbg !3135
  %tobool29 = icmp ne i8* %33, null, !dbg !3132
  br i1 %tobool29, label %if.then30, label %if.end34, !dbg !3136

if.then30:                                        ; preds = %land.lhs.true
  %34 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3137
  %35 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3139
  %parentdir31 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %35, i32 0, i32 5, !dbg !3140
  %s32 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir31, i32 0, i32 0, !dbg !3141
  %36 = load i8*, i8** %s32, align 8, !dbg !3141
  call void @mtree_quote(%struct.archive_string* %34, i8* %36), !dbg !3142
  %37 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3143
  %call33 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %37, i8 signext 47), !dbg !3144
  br label %if.end34, !dbg !3145

if.end34:                                         ; preds = %if.then30, %land.lhs.true, %cond.end
  %38 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3146
  %39 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3147
  %basename35 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %39, i32 0, i32 6, !dbg !3148
  %s36 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename35, i32 0, i32 0, !dbg !3149
  %40 = load i8*, i8** %s36, align 8, !dbg !3149
  call void @mtree_quote(%struct.archive_string* %38, i8* %40), !dbg !3150
  %41 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3151
  %42 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3152
  %call37 = call i32 @get_global_set_keys(%struct.mtree_writer* %41, %struct.mtree_entry* %42), !dbg !3153
  store i32 %call37, i32* %keys, align 4, !dbg !3154
  %43 = load i32, i32* %keys, align 4, !dbg !3155
  %and = and i32 %43, 1024, !dbg !3157
  %cmp = icmp ne i32 %and, 0, !dbg !3158
  br i1 %cmp, label %land.lhs.true38, label %if.end44, !dbg !3159

land.lhs.true38:                                  ; preds = %if.end34
  %44 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3160
  %nlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %44, i32 0, i32 12, !dbg !3161
  %45 = load i32, i32* %nlink, align 8, !dbg !3161
  %cmp39 = icmp ne i32 %45, 1, !dbg !3162
  br i1 %cmp39, label %land.lhs.true40, label %if.end44, !dbg !3163

land.lhs.true40:                                  ; preds = %land.lhs.true38
  %46 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3164
  %filetype = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %46, i32 0, i32 13, !dbg !3166
  %47 = load i32, i32* %filetype, align 4, !dbg !3166
  %cmp41 = icmp ne i32 %47, 16384, !dbg !3167
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !3168

if.then42:                                        ; preds = %land.lhs.true40
  %48 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3169
  %49 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3170
  %nlink43 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %49, i32 0, i32 12, !dbg !3171
  %50 = load i32, i32* %nlink43, align 8, !dbg !3171
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %48, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.47, i32 0, i32 0), i32 %50), !dbg !3172
  br label %if.end44, !dbg !3172

if.end44:                                         ; preds = %if.then42, %land.lhs.true40, %land.lhs.true38, %if.end34
  %51 = load i32, i32* %keys, align 4, !dbg !3173
  %and45 = and i32 %51, 32, !dbg !3175
  %cmp46 = icmp ne i32 %and45, 0, !dbg !3176
  br i1 %cmp46, label %land.lhs.true47, label %if.end54, !dbg !3177

land.lhs.true47:                                  ; preds = %if.end44
  %52 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3178
  %gname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %52, i32 0, i32 10, !dbg !3178
  %length48 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !3178
  %53 = load i64, i64* %length48, align 8, !dbg !3178
  %cmp49 = icmp ugt i64 %53, 0, !dbg !3180
  br i1 %cmp49, label %if.then50, label %if.end54, !dbg !3181

if.then50:                                        ; preds = %land.lhs.true47
  %54 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3182
  %call51 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %54, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.48, i32 0, i32 0)), !dbg !3184
  %55 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3185
  %56 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3186
  %gname52 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %56, i32 0, i32 10, !dbg !3187
  %s53 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname52, i32 0, i32 0, !dbg !3188
  %57 = load i8*, i8** %s53, align 8, !dbg !3188
  call void @mtree_quote(%struct.archive_string* %55, i8* %57), !dbg !3189
  br label %if.end54, !dbg !3190

if.end54:                                         ; preds = %if.then50, %land.lhs.true47, %if.end44
  %58 = load i32, i32* %keys, align 4, !dbg !3191
  %and55 = and i32 %58, 2097152, !dbg !3193
  %cmp56 = icmp ne i32 %and55, 0, !dbg !3194
  br i1 %cmp56, label %land.lhs.true57, label %if.end64, !dbg !3195

land.lhs.true57:                                  ; preds = %if.end54
  %59 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3196
  %uname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %59, i32 0, i32 9, !dbg !3196
  %length58 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !3196
  %60 = load i64, i64* %length58, align 8, !dbg !3196
  %cmp59 = icmp ugt i64 %60, 0, !dbg !3198
  br i1 %cmp59, label %if.then60, label %if.end64, !dbg !3199

if.then60:                                        ; preds = %land.lhs.true57
  %61 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3200
  %call61 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %61, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.49, i32 0, i32 0)), !dbg !3202
  %62 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3203
  %63 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3204
  %uname62 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %63, i32 0, i32 9, !dbg !3205
  %s63 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname62, i32 0, i32 0, !dbg !3206
  %64 = load i8*, i8** %s63, align 8, !dbg !3206
  call void @mtree_quote(%struct.archive_string* %62, i8* %64), !dbg !3207
  br label %if.end64, !dbg !3208

if.end64:                                         ; preds = %if.then60, %land.lhs.true57, %if.end54
  %65 = load i32, i32* %keys, align 4, !dbg !3209
  %and65 = and i32 %65, 8, !dbg !3211
  %cmp66 = icmp ne i32 %and65, 0, !dbg !3212
  br i1 %cmp66, label %if.then67, label %if.end85, !dbg !3213

if.then67:                                        ; preds = %if.end64
  %66 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3214
  %fflags_text = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %66, i32 0, i32 11, !dbg !3214
  %length68 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text, i32 0, i32 1, !dbg !3214
  %67 = load i64, i64* %length68, align 8, !dbg !3214
  %cmp69 = icmp ugt i64 %67, 0, !dbg !3217
  br i1 %cmp69, label %if.then70, label %if.else74, !dbg !3218

if.then70:                                        ; preds = %if.then67
  %68 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3219
  %call71 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %68, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.50, i32 0, i32 0)), !dbg !3221
  %69 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3222
  %70 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3223
  %fflags_text72 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %70, i32 0, i32 11, !dbg !3224
  %s73 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text72, i32 0, i32 0, !dbg !3225
  %71 = load i8*, i8** %s73, align 8, !dbg !3225
  call void @mtree_quote(%struct.archive_string* %69, i8* %71), !dbg !3226
  br label %if.end84, !dbg !3227

if.else74:                                        ; preds = %if.then67
  %72 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3228
  %set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %72, i32 0, i32 9, !dbg !3231
  %processing = getelementptr inbounds %struct.anon, %struct.anon* %set, i32 0, i32 0, !dbg !3232
  %73 = load i32, i32* %processing, align 8, !dbg !3232
  %tobool75 = icmp ne i32 %73, 0, !dbg !3228
  br i1 %tobool75, label %land.lhs.true76, label %if.end83, !dbg !3233

land.lhs.true76:                                  ; preds = %if.else74
  %74 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3234
  %set77 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %74, i32 0, i32 9, !dbg !3235
  %keys78 = getelementptr inbounds %struct.anon, %struct.anon* %set77, i32 0, i32 2, !dbg !3236
  %75 = load i32, i32* %keys78, align 8, !dbg !3236
  %and79 = and i32 %75, 8, !dbg !3237
  %cmp80 = icmp ne i32 %and79, 0, !dbg !3238
  br i1 %cmp80, label %if.then81, label %if.end83, !dbg !3239

if.then81:                                        ; preds = %land.lhs.true76
  %76 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3241
  %call82 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %76, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.51, i32 0, i32 0)), !dbg !3242
  br label %if.end83, !dbg !3242

if.end83:                                         ; preds = %if.then81, %land.lhs.true76, %if.else74
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.then70
  br label %if.end85, !dbg !3243

if.end85:                                         ; preds = %if.end84, %if.end64
  %77 = load i32, i32* %keys, align 4, !dbg !3244
  %and86 = and i32 %77, 262144, !dbg !3246
  %cmp87 = icmp ne i32 %and86, 0, !dbg !3247
  br i1 %cmp87, label %if.then88, label %if.end89, !dbg !3248

if.then88:                                        ; preds = %if.end85
  %78 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3249
  %79 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3250
  %mtime = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %79, i32 0, i32 18, !dbg !3251
  %80 = load i64, i64* %mtime, align 8, !dbg !3251
  %81 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3252
  %mtime_nsec = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %81, i32 0, i32 19, !dbg !3253
  %82 = load i64, i64* %mtime_nsec, align 8, !dbg !3253
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %78, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.52, i32 0, i32 0), i64 %80, i64 %82), !dbg !3254
  br label %if.end89, !dbg !3254

if.end89:                                         ; preds = %if.then88, %if.end85
  %83 = load i32, i32* %keys, align 4, !dbg !3255
  %and90 = and i32 %83, 512, !dbg !3257
  %cmp91 = icmp ne i32 %and90, 0, !dbg !3258
  br i1 %cmp91, label %if.then92, label %if.end93, !dbg !3259

if.then92:                                        ; preds = %if.end89
  %84 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3260
  %85 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3261
  %mode = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %85, i32 0, i32 14, !dbg !3262
  %86 = load i32, i32* %mode, align 8, !dbg !3262
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %84, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.53, i32 0, i32 0), i32 %86), !dbg !3263
  br label %if.end93, !dbg !3263

if.end93:                                         ; preds = %if.then92, %if.end89
  %87 = load i32, i32* %keys, align 4, !dbg !3264
  %and94 = and i32 %87, 16, !dbg !3266
  %cmp95 = icmp ne i32 %and94, 0, !dbg !3267
  br i1 %cmp95, label %if.then96, label %if.end97, !dbg !3268

if.then96:                                        ; preds = %if.end93
  %88 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3269
  %89 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3270
  %gid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %89, i32 0, i32 17, !dbg !3271
  %90 = load i64, i64* %gid, align 8, !dbg !3271
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %88, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.54, i32 0, i32 0), i64 %90), !dbg !3272
  br label %if.end97, !dbg !3272

if.end97:                                         ; preds = %if.then96, %if.end93
  %91 = load i32, i32* %keys, align 4, !dbg !3273
  %and98 = and i32 %91, 1048576, !dbg !3275
  %cmp99 = icmp ne i32 %and98, 0, !dbg !3276
  br i1 %cmp99, label %if.then100, label %if.end101, !dbg !3277

if.then100:                                       ; preds = %if.end97
  %92 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3278
  %93 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3279
  %uid = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %93, i32 0, i32 16, !dbg !3280
  %94 = load i64, i64* %uid, align 8, !dbg !3280
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %92, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i32 0, i32 0), i64 %94), !dbg !3281
  br label %if.end101, !dbg !3281

if.end101:                                        ; preds = %if.then100, %if.end97
  %95 = load i32, i32* %keys, align 4, !dbg !3282
  %and102 = and i32 %95, 67108864, !dbg !3284
  %cmp103 = icmp ne i32 %and102, 0, !dbg !3285
  br i1 %cmp103, label %if.then104, label %if.end105, !dbg !3286

if.then104:                                       ; preds = %if.end101
  %96 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3287
  %97 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3288
  %ino = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %97, i32 0, i32 26, !dbg !3289
  %98 = load i64, i64* %ino, align 8, !dbg !3289
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %96, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.56, i32 0, i32 0), i64 %98), !dbg !3290
  br label %if.end105, !dbg !3290

if.end105:                                        ; preds = %if.then104, %if.end101
  %99 = load i32, i32* %keys, align 4, !dbg !3291
  %and106 = and i32 %99, 134217728, !dbg !3293
  %cmp107 = icmp ne i32 %and106, 0, !dbg !3294
  br i1 %cmp107, label %if.then108, label %if.end109, !dbg !3295

if.then108:                                       ; preds = %if.end105
  %100 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3296
  %101 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3298
  %devmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %101, i32 0, i32 24, !dbg !3299
  %102 = load i64, i64* %devmajor, align 8, !dbg !3299
  %103 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3300
  %devminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %103, i32 0, i32 25, !dbg !3301
  %104 = load i64, i64* %devminor, align 8, !dbg !3301
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %100, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.57, i32 0, i32 0), i64 %102, i64 %104), !dbg !3302
  br label %if.end109, !dbg !3303

if.end109:                                        ; preds = %if.then108, %if.end105
  %105 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3304
  %filetype110 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %105, i32 0, i32 13, !dbg !3305
  %106 = load i32, i32* %filetype110, align 4, !dbg !3305
  switch i32 %106, label %sw.default [
    i32 40960, label %sw.bb
    i32 49152, label %sw.bb122
    i32 8192, label %sw.bb128
    i32 24576, label %sw.bb138
    i32 16384, label %sw.bb150
    i32 4096, label %sw.bb156
    i32 32768, label %sw.bb162
  ], !dbg !3306

sw.bb:                                            ; preds = %if.end109
  %107 = load i32, i32* %keys, align 4, !dbg !3307
  %and111 = and i32 %107, 524288, !dbg !3310
  %cmp112 = icmp ne i32 %and111, 0, !dbg !3311
  br i1 %cmp112, label %if.then113, label %if.end115, !dbg !3312

if.then113:                                       ; preds = %sw.bb
  %108 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3313
  %call114 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %108, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.58, i32 0, i32 0)), !dbg !3314
  br label %if.end115, !dbg !3314

if.end115:                                        ; preds = %if.then113, %sw.bb
  %109 = load i32, i32* %keys, align 4, !dbg !3315
  %and116 = and i32 %109, 65536, !dbg !3317
  %cmp117 = icmp ne i32 %and116, 0, !dbg !3318
  br i1 %cmp117, label %if.then118, label %if.end121, !dbg !3319

if.then118:                                       ; preds = %if.end115
  %110 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3320
  %call119 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %110, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.59, i32 0, i32 0)), !dbg !3322
  %111 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3323
  %112 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3324
  %symlink = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %112, i32 0, i32 8, !dbg !3325
  %s120 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %symlink, i32 0, i32 0, !dbg !3326
  %113 = load i8*, i8** %s120, align 8, !dbg !3326
  call void @mtree_quote(%struct.archive_string* %111, i8* %113), !dbg !3327
  br label %if.end121, !dbg !3328

if.end121:                                        ; preds = %if.then118, %if.end115
  br label %sw.epilog, !dbg !3329

sw.bb122:                                         ; preds = %if.end109
  %114 = load i32, i32* %keys, align 4, !dbg !3330
  %and123 = and i32 %114, 524288, !dbg !3332
  %cmp124 = icmp ne i32 %and123, 0, !dbg !3333
  br i1 %cmp124, label %if.then125, label %if.end127, !dbg !3334

if.then125:                                       ; preds = %sw.bb122
  %115 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3335
  %call126 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %115, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.60, i32 0, i32 0)), !dbg !3336
  br label %if.end127, !dbg !3336

if.end127:                                        ; preds = %if.then125, %sw.bb122
  br label %sw.epilog, !dbg !3337

sw.bb128:                                         ; preds = %if.end109
  %116 = load i32, i32* %keys, align 4, !dbg !3338
  %and129 = and i32 %116, 524288, !dbg !3340
  %cmp130 = icmp ne i32 %and129, 0, !dbg !3341
  br i1 %cmp130, label %if.then131, label %if.end133, !dbg !3342

if.then131:                                       ; preds = %sw.bb128
  %117 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3343
  %call132 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %117, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.61, i32 0, i32 0)), !dbg !3344
  br label %if.end133, !dbg !3344

if.end133:                                        ; preds = %if.then131, %sw.bb128
  %118 = load i32, i32* %keys, align 4, !dbg !3345
  %and134 = and i32 %118, 2, !dbg !3347
  %cmp135 = icmp ne i32 %and134, 0, !dbg !3348
  br i1 %cmp135, label %if.then136, label %if.end137, !dbg !3349

if.then136:                                       ; preds = %if.end133
  %119 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3350
  %120 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3352
  %rdevmajor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %120, i32 0, i32 22, !dbg !3353
  %121 = load i64, i64* %rdevmajor, align 8, !dbg !3353
  %122 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3354
  %rdevminor = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %122, i32 0, i32 23, !dbg !3355
  %123 = load i64, i64* %rdevminor, align 8, !dbg !3355
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %119, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.62, i32 0, i32 0), i64 %121, i64 %123), !dbg !3356
  br label %if.end137, !dbg !3357

if.end137:                                        ; preds = %if.then136, %if.end133
  br label %sw.epilog, !dbg !3358

sw.bb138:                                         ; preds = %if.end109
  %124 = load i32, i32* %keys, align 4, !dbg !3359
  %and139 = and i32 %124, 524288, !dbg !3361
  %cmp140 = icmp ne i32 %and139, 0, !dbg !3362
  br i1 %cmp140, label %if.then141, label %if.end143, !dbg !3363

if.then141:                                       ; preds = %sw.bb138
  %125 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3364
  %call142 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %125, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.63, i32 0, i32 0)), !dbg !3365
  br label %if.end143, !dbg !3365

if.end143:                                        ; preds = %if.then141, %sw.bb138
  %126 = load i32, i32* %keys, align 4, !dbg !3366
  %and144 = and i32 %126, 2, !dbg !3368
  %cmp145 = icmp ne i32 %and144, 0, !dbg !3369
  br i1 %cmp145, label %if.then146, label %if.end149, !dbg !3370

if.then146:                                       ; preds = %if.end143
  %127 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3371
  %128 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3373
  %rdevmajor147 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %128, i32 0, i32 22, !dbg !3374
  %129 = load i64, i64* %rdevmajor147, align 8, !dbg !3374
  %130 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3375
  %rdevminor148 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %130, i32 0, i32 23, !dbg !3376
  %131 = load i64, i64* %rdevminor148, align 8, !dbg !3376
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %127, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.62, i32 0, i32 0), i64 %129, i64 %131), !dbg !3377
  br label %if.end149, !dbg !3378

if.end149:                                        ; preds = %if.then146, %if.end143
  br label %sw.epilog, !dbg !3379

sw.bb150:                                         ; preds = %if.end109
  %132 = load i32, i32* %keys, align 4, !dbg !3380
  %and151 = and i32 %132, 524288, !dbg !3382
  %cmp152 = icmp ne i32 %and151, 0, !dbg !3383
  br i1 %cmp152, label %if.then153, label %if.end155, !dbg !3384

if.then153:                                       ; preds = %sw.bb150
  %133 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3385
  %call154 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %133, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.64, i32 0, i32 0)), !dbg !3386
  br label %if.end155, !dbg !3386

if.end155:                                        ; preds = %if.then153, %sw.bb150
  br label %sw.epilog, !dbg !3387

sw.bb156:                                         ; preds = %if.end109
  %134 = load i32, i32* %keys, align 4, !dbg !3388
  %and157 = and i32 %134, 524288, !dbg !3390
  %cmp158 = icmp ne i32 %and157, 0, !dbg !3391
  br i1 %cmp158, label %if.then159, label %if.end161, !dbg !3392

if.then159:                                       ; preds = %sw.bb156
  %135 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3393
  %call160 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %135, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.65, i32 0, i32 0)), !dbg !3394
  br label %if.end161, !dbg !3394

if.end161:                                        ; preds = %if.then159, %sw.bb156
  br label %sw.epilog, !dbg !3395

sw.bb162:                                         ; preds = %if.end109
  br label %sw.default, !dbg !3396

sw.default:                                       ; preds = %if.end109, %sw.bb162
  %136 = load i32, i32* %keys, align 4, !dbg !3398
  %and163 = and i32 %136, 524288, !dbg !3400
  %cmp164 = icmp ne i32 %and163, 0, !dbg !3401
  br i1 %cmp164, label %if.then165, label %if.end167, !dbg !3402

if.then165:                                       ; preds = %sw.default
  %137 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3403
  %call166 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %137, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.66, i32 0, i32 0)), !dbg !3404
  br label %if.end167, !dbg !3404

if.end167:                                        ; preds = %if.then165, %sw.default
  %138 = load i32, i32* %keys, align 4, !dbg !3405
  %and168 = and i32 %138, 32768, !dbg !3407
  %cmp169 = icmp ne i32 %and168, 0, !dbg !3408
  br i1 %cmp169, label %if.then170, label %if.end171, !dbg !3409

if.then170:                                       ; preds = %if.end167
  %139 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3410
  %140 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3411
  %size = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %140, i32 0, i32 15, !dbg !3412
  %141 = load i64, i64* %size, align 8, !dbg !3412
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %139, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.67, i32 0, i32 0), i64 %141), !dbg !3413
  br label %if.end171, !dbg !3413

if.end171:                                        ; preds = %if.then170, %if.end167
  br label %sw.epilog, !dbg !3414

sw.epilog:                                        ; preds = %if.end171, %if.end161, %if.end155, %if.end149, %if.end137, %if.end127, %if.end121
  %142 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3415
  %reg_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %142, i32 0, i32 4, !dbg !3417
  %143 = load %struct.reg_info*, %struct.reg_info** %reg_info, align 8, !dbg !3417
  %tobool172 = icmp ne %struct.reg_info* %143, null, !dbg !3415
  br i1 %tobool172, label %if.then173, label %if.end175, !dbg !3418

if.then173:                                       ; preds = %sw.epilog
  %144 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3419
  %145 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !3420
  %reg_info174 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %145, i32 0, i32 4, !dbg !3421
  %146 = load %struct.reg_info*, %struct.reg_info** %reg_info174, align 8, !dbg !3421
  call void @sum_write(%struct.archive_string* %144, %struct.reg_info* %146), !dbg !3422
  br label %if.end175, !dbg !3422

if.end175:                                        ; preds = %if.then173, %sw.epilog
  %147 = load %struct.archive_string*, %struct.archive_string** %str, align 8, !dbg !3423
  %call176 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %147, i8 signext 10), !dbg !3424
  %148 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3425
  %indent177 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %148, i32 0, i32 18, !dbg !3427
  %149 = load i32, i32* %indent177, align 8, !dbg !3427
  %tobool178 = icmp ne i32 %149, 0, !dbg !3425
  br i1 %tobool178, label %if.then182, label %lor.lhs.false179, !dbg !3428

lor.lhs.false179:                                 ; preds = %if.end175
  %150 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3429
  %classic180 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %150, i32 0, i32 11, !dbg !3431
  %151 = load i32, i32* %classic180, align 8, !dbg !3431
  %tobool181 = icmp ne i32 %151, 0, !dbg !3429
  br i1 %tobool181, label %if.then182, label %if.end183, !dbg !3432

if.then182:                                       ; preds = %lor.lhs.false179, %if.end175
  %152 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3433
  call void @mtree_indent(%struct.mtree_writer* %152), !dbg !3434
  br label %if.end183, !dbg !3434

if.end183:                                        ; preds = %if.then182, %lor.lhs.false179
  %153 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3435
  %buf184 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %153, i32 0, i32 6, !dbg !3437
  %length185 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf184, i32 0, i32 1, !dbg !3438
  %154 = load i64, i64* %length185, align 8, !dbg !3438
  %cmp186 = icmp ugt i64 %154, 32768, !dbg !3439
  br i1 %cmp186, label %if.then187, label %if.else195, !dbg !3440

if.then187:                                       ; preds = %if.end183
  %155 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3441
  %156 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3443
  %buf188 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %156, i32 0, i32 6, !dbg !3444
  %s189 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf188, i32 0, i32 0, !dbg !3445
  %157 = load i8*, i8** %s189, align 8, !dbg !3445
  %158 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3446
  %buf190 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %158, i32 0, i32 6, !dbg !3447
  %length191 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf190, i32 0, i32 1, !dbg !3448
  %159 = load i64, i64* %length191, align 8, !dbg !3448
  %call192 = call i32 @__archive_write_output(%struct.archive_write* %155, i8* %157, i64 %159), !dbg !3449
  store i32 %call192, i32* %ret, align 4, !dbg !3450
  %160 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3451
  %buf193 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %160, i32 0, i32 6, !dbg !3451
  %length194 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf193, i32 0, i32 1, !dbg !3451
  store i64 0, i64* %length194, align 8, !dbg !3451
  br label %if.end196, !dbg !3452

if.else195:                                       ; preds = %if.end183
  store i32 0, i32* %ret, align 4, !dbg !3453
  br label %if.end196

if.end196:                                        ; preds = %if.else195, %if.then187
  %161 = load i32, i32* %ret, align 4, !dbg !3454
  ret i32 %161, !dbg !3455
}

; Function Attrs: nounwind uwtable
define internal void @write_global(%struct.mtree_writer* %mtree) #0 !dbg !400 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %setstr = alloca %struct.archive_string, align 8
  %unsetstr = alloca %struct.archive_string, align 8
  %acs = alloca %struct.att_counter_set*, align 8
  %keys = alloca i32, align 4
  %oldkeys = alloca i32, align 4
  %effkeys = alloca i32, align 4
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !3456, metadata !426), !dbg !3457
  call void @llvm.dbg.declare(metadata %struct.archive_string* %setstr, metadata !3458, metadata !426), !dbg !3459
  call void @llvm.dbg.declare(metadata %struct.archive_string* %unsetstr, metadata !3460, metadata !426), !dbg !3461
  call void @llvm.dbg.declare(metadata %struct.att_counter_set** %acs, metadata !3462, metadata !426), !dbg !3463
  call void @llvm.dbg.declare(metadata i32* %keys, metadata !3464, metadata !426), !dbg !3465
  call void @llvm.dbg.declare(metadata i32* %oldkeys, metadata !3466, metadata !426), !dbg !3467
  call void @llvm.dbg.declare(metadata i32* %effkeys, metadata !3468, metadata !426), !dbg !3469
  br label %do.body, !dbg !3470

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %setstr, i32 0, i32 0, !dbg !3471
  store i8* null, i8** %s, align 8, !dbg !3471
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %setstr, i32 0, i32 1, !dbg !3471
  store i64 0, i64* %length, align 8, !dbg !3471
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %setstr, i32 0, i32 2, !dbg !3471
  store i64 0, i64* %buffer_length, align 8, !dbg !3471
  br label %do.end, !dbg !3471

do.end:                                           ; preds = %do.body
  br label %do.body1, !dbg !3474

do.body1:                                         ; preds = %do.end
  %s2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %unsetstr, i32 0, i32 0, !dbg !3475
  store i8* null, i8** %s2, align 8, !dbg !3475
  %length3 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %unsetstr, i32 0, i32 1, !dbg !3475
  store i64 0, i64* %length3, align 8, !dbg !3475
  %buffer_length4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %unsetstr, i32 0, i32 2, !dbg !3475
  store i64 0, i64* %buffer_length4, align 8, !dbg !3475
  br label %do.end5, !dbg !3475

do.end5:                                          ; preds = %do.body1
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3478
  %keys6 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 16, !dbg !3479
  %1 = load i32, i32* %keys6, align 8, !dbg !3479
  %and = and i32 %1, 3670584, !dbg !3480
  store i32 %and, i32* %keys, align 4, !dbg !3481
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3482
  %set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 9, !dbg !3483
  %keys7 = getelementptr inbounds %struct.anon, %struct.anon* %set, i32 0, i32 2, !dbg !3484
  %3 = load i32, i32* %keys7, align 8, !dbg !3484
  store i32 %3, i32* %oldkeys, align 4, !dbg !3485
  %4 = load i32, i32* %keys, align 4, !dbg !3486
  store i32 %4, i32* %effkeys, align 4, !dbg !3487
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3488
  %acs8 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 10, !dbg !3489
  store %struct.att_counter_set* %acs8, %struct.att_counter_set** %acs, align 8, !dbg !3490
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3491
  %set9 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 9, !dbg !3493
  %processing = getelementptr inbounds %struct.anon, %struct.anon* %set9, i32 0, i32 0, !dbg !3494
  %7 = load i32, i32* %processing, align 8, !dbg !3494
  %tobool = icmp ne i32 %7, 0, !dbg !3491
  br i1 %tobool, label %if.then, label %if.else94, !dbg !3495

if.then:                                          ; preds = %do.end5
  %8 = load i32, i32* %effkeys, align 4, !dbg !3496
  %and10 = and i32 %8, -524289, !dbg !3496
  store i32 %and10, i32* %effkeys, align 4, !dbg !3496
  %9 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3498
  %uid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %9, i32 0, i32 0, !dbg !3500
  %10 = load %struct.attr_counter*, %struct.attr_counter** %uid_list, align 8, !dbg !3500
  %cmp = icmp eq %struct.attr_counter* %10, null, !dbg !3501
  br i1 %cmp, label %if.then11, label %if.else, !dbg !3502

if.then11:                                        ; preds = %if.then
  %11 = load i32, i32* %effkeys, align 4, !dbg !3503
  %and12 = and i32 %11, -3145729, !dbg !3503
  store i32 %and12, i32* %effkeys, align 4, !dbg !3503
  br label %if.end25, !dbg !3504

if.else:                                          ; preds = %if.then
  %12 = load i32, i32* %oldkeys, align 4, !dbg !3505
  %and13 = and i32 %12, 3145728, !dbg !3507
  %tobool14 = icmp ne i32 %and13, 0, !dbg !3507
  br i1 %tobool14, label %if.then15, label %if.end24, !dbg !3508

if.then15:                                        ; preds = %if.else
  %13 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3509
  %uid_list16 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %13, i32 0, i32 0, !dbg !3512
  %14 = load %struct.attr_counter*, %struct.attr_counter** %uid_list16, align 8, !dbg !3512
  %count = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %14, i32 0, i32 3, !dbg !3513
  %15 = load i32, i32* %count, align 8, !dbg !3513
  %cmp17 = icmp slt i32 %15, 2, !dbg !3514
  br i1 %cmp17, label %if.then22, label %lor.lhs.false, !dbg !3515

lor.lhs.false:                                    ; preds = %if.then15
  %16 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3516
  %set18 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %16, i32 0, i32 9, !dbg !3517
  %uid = getelementptr inbounds %struct.anon, %struct.anon* %set18, i32 0, i32 3, !dbg !3518
  %17 = load i64, i64* %uid, align 8, !dbg !3518
  %18 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3519
  %uid_list19 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %18, i32 0, i32 0, !dbg !3520
  %19 = load %struct.attr_counter*, %struct.attr_counter** %uid_list19, align 8, !dbg !3520
  %m_entry = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %19, i32 0, i32 2, !dbg !3521
  %20 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry, align 8, !dbg !3521
  %uid20 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %20, i32 0, i32 16, !dbg !3522
  %21 = load i64, i64* %uid20, align 8, !dbg !3522
  %cmp21 = icmp eq i64 %17, %21, !dbg !3523
  br i1 %cmp21, label %if.then22, label %if.end, !dbg !3524

if.then22:                                        ; preds = %lor.lhs.false, %if.then15
  %22 = load i32, i32* %effkeys, align 4, !dbg !3526
  %and23 = and i32 %22, -3145729, !dbg !3526
  store i32 %and23, i32* %effkeys, align 4, !dbg !3526
  br label %if.end, !dbg !3527

if.end:                                           ; preds = %if.then22, %lor.lhs.false
  br label %if.end24, !dbg !3528

if.end24:                                         ; preds = %if.end, %if.else
  br label %if.end25

if.end25:                                         ; preds = %if.end24, %if.then11
  %23 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3529
  %gid_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %23, i32 0, i32 1, !dbg !3531
  %24 = load %struct.attr_counter*, %struct.attr_counter** %gid_list, align 8, !dbg !3531
  %cmp26 = icmp eq %struct.attr_counter* %24, null, !dbg !3532
  br i1 %cmp26, label %if.then27, label %if.else29, !dbg !3533

if.then27:                                        ; preds = %if.end25
  %25 = load i32, i32* %effkeys, align 4, !dbg !3534
  %and28 = and i32 %25, -49, !dbg !3534
  store i32 %and28, i32* %effkeys, align 4, !dbg !3534
  br label %if.end46, !dbg !3535

if.else29:                                        ; preds = %if.end25
  %26 = load i32, i32* %oldkeys, align 4, !dbg !3536
  %and30 = and i32 %26, 48, !dbg !3538
  %tobool31 = icmp ne i32 %and30, 0, !dbg !3538
  br i1 %tobool31, label %if.then32, label %if.end45, !dbg !3539

if.then32:                                        ; preds = %if.else29
  %27 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3540
  %gid_list33 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %27, i32 0, i32 1, !dbg !3543
  %28 = load %struct.attr_counter*, %struct.attr_counter** %gid_list33, align 8, !dbg !3543
  %count34 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %28, i32 0, i32 3, !dbg !3544
  %29 = load i32, i32* %count34, align 8, !dbg !3544
  %cmp35 = icmp slt i32 %29, 2, !dbg !3545
  br i1 %cmp35, label %if.then42, label %lor.lhs.false36, !dbg !3546

lor.lhs.false36:                                  ; preds = %if.then32
  %30 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3547
  %set37 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %30, i32 0, i32 9, !dbg !3548
  %gid = getelementptr inbounds %struct.anon, %struct.anon* %set37, i32 0, i32 4, !dbg !3549
  %31 = load i64, i64* %gid, align 8, !dbg !3549
  %32 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3550
  %gid_list38 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %32, i32 0, i32 1, !dbg !3551
  %33 = load %struct.attr_counter*, %struct.attr_counter** %gid_list38, align 8, !dbg !3551
  %m_entry39 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %33, i32 0, i32 2, !dbg !3552
  %34 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry39, align 8, !dbg !3552
  %gid40 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %34, i32 0, i32 17, !dbg !3553
  %35 = load i64, i64* %gid40, align 8, !dbg !3553
  %cmp41 = icmp eq i64 %31, %35, !dbg !3554
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !3555

if.then42:                                        ; preds = %lor.lhs.false36, %if.then32
  %36 = load i32, i32* %effkeys, align 4, !dbg !3557
  %and43 = and i32 %36, -49, !dbg !3557
  store i32 %and43, i32* %effkeys, align 4, !dbg !3557
  br label %if.end44, !dbg !3558

if.end44:                                         ; preds = %if.then42, %lor.lhs.false36
  br label %if.end45, !dbg !3559

if.end45:                                         ; preds = %if.end44, %if.else29
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.then27
  %37 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3560
  %mode_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %37, i32 0, i32 2, !dbg !3562
  %38 = load %struct.attr_counter*, %struct.attr_counter** %mode_list, align 8, !dbg !3562
  %cmp47 = icmp eq %struct.attr_counter* %38, null, !dbg !3563
  br i1 %cmp47, label %if.then48, label %if.else50, !dbg !3564

if.then48:                                        ; preds = %if.end46
  %39 = load i32, i32* %effkeys, align 4, !dbg !3565
  %and49 = and i32 %39, -513, !dbg !3565
  store i32 %and49, i32* %effkeys, align 4, !dbg !3565
  br label %if.end67, !dbg !3566

if.else50:                                        ; preds = %if.end46
  %40 = load i32, i32* %oldkeys, align 4, !dbg !3567
  %and51 = and i32 %40, 512, !dbg !3569
  %tobool52 = icmp ne i32 %and51, 0, !dbg !3569
  br i1 %tobool52, label %if.then53, label %if.end66, !dbg !3570

if.then53:                                        ; preds = %if.else50
  %41 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3571
  %mode_list54 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %41, i32 0, i32 2, !dbg !3574
  %42 = load %struct.attr_counter*, %struct.attr_counter** %mode_list54, align 8, !dbg !3574
  %count55 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %42, i32 0, i32 3, !dbg !3575
  %43 = load i32, i32* %count55, align 8, !dbg !3575
  %cmp56 = icmp slt i32 %43, 2, !dbg !3576
  br i1 %cmp56, label %if.then63, label %lor.lhs.false57, !dbg !3577

lor.lhs.false57:                                  ; preds = %if.then53
  %44 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3578
  %set58 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %44, i32 0, i32 9, !dbg !3579
  %mode = getelementptr inbounds %struct.anon, %struct.anon* %set58, i32 0, i32 5, !dbg !3580
  %45 = load i32, i32* %mode, align 8, !dbg !3580
  %46 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3581
  %mode_list59 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %46, i32 0, i32 2, !dbg !3582
  %47 = load %struct.attr_counter*, %struct.attr_counter** %mode_list59, align 8, !dbg !3582
  %m_entry60 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %47, i32 0, i32 2, !dbg !3583
  %48 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry60, align 8, !dbg !3583
  %mode61 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %48, i32 0, i32 14, !dbg !3584
  %49 = load i32, i32* %mode61, align 8, !dbg !3584
  %cmp62 = icmp eq i32 %45, %49, !dbg !3585
  br i1 %cmp62, label %if.then63, label %if.end65, !dbg !3586

if.then63:                                        ; preds = %lor.lhs.false57, %if.then53
  %50 = load i32, i32* %effkeys, align 4, !dbg !3588
  %and64 = and i32 %50, -513, !dbg !3588
  store i32 %and64, i32* %effkeys, align 4, !dbg !3588
  br label %if.end65, !dbg !3589

if.end65:                                         ; preds = %if.then63, %lor.lhs.false57
  br label %if.end66, !dbg !3590

if.end66:                                         ; preds = %if.end65, %if.else50
  br label %if.end67

if.end67:                                         ; preds = %if.end66, %if.then48
  %51 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3591
  %flags_list = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %51, i32 0, i32 3, !dbg !3593
  %52 = load %struct.attr_counter*, %struct.attr_counter** %flags_list, align 8, !dbg !3593
  %cmp68 = icmp eq %struct.attr_counter* %52, null, !dbg !3594
  br i1 %cmp68, label %if.then69, label %if.else71, !dbg !3595

if.then69:                                        ; preds = %if.end67
  %53 = load i32, i32* %effkeys, align 4, !dbg !3596
  %and70 = and i32 %53, -9, !dbg !3596
  store i32 %and70, i32* %effkeys, align 4, !dbg !3596
  br label %if.end93, !dbg !3597

if.else71:                                        ; preds = %if.end67
  %54 = load i32, i32* %oldkeys, align 4, !dbg !3598
  %and72 = and i32 %54, 8, !dbg !3600
  %cmp73 = icmp ne i32 %and72, 0, !dbg !3601
  br i1 %cmp73, label %if.then74, label %if.end92, !dbg !3602

if.then74:                                        ; preds = %if.else71
  %55 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3603
  %flags_list75 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %55, i32 0, i32 3, !dbg !3606
  %56 = load %struct.attr_counter*, %struct.attr_counter** %flags_list75, align 8, !dbg !3606
  %count76 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %56, i32 0, i32 3, !dbg !3607
  %57 = load i32, i32* %count76, align 8, !dbg !3607
  %cmp77 = icmp slt i32 %57, 2, !dbg !3608
  br i1 %cmp77, label %if.then89, label %lor.lhs.false78, !dbg !3609

lor.lhs.false78:                                  ; preds = %if.then74
  %58 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3610
  %flags_list79 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %58, i32 0, i32 3, !dbg !3611
  %59 = load %struct.attr_counter*, %struct.attr_counter** %flags_list79, align 8, !dbg !3611
  %m_entry80 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %59, i32 0, i32 2, !dbg !3612
  %60 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry80, align 8, !dbg !3612
  %fflags_set = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %60, i32 0, i32 20, !dbg !3613
  %61 = load i64, i64* %fflags_set, align 8, !dbg !3613
  %62 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3614
  %set81 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %62, i32 0, i32 9, !dbg !3615
  %fflags_set82 = getelementptr inbounds %struct.anon, %struct.anon* %set81, i32 0, i32 6, !dbg !3616
  %63 = load i64, i64* %fflags_set82, align 8, !dbg !3616
  %cmp83 = icmp eq i64 %61, %63, !dbg !3617
  br i1 %cmp83, label %land.lhs.true, label %if.end91, !dbg !3618

land.lhs.true:                                    ; preds = %lor.lhs.false78
  %64 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3619
  %flags_list84 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %64, i32 0, i32 3, !dbg !3620
  %65 = load %struct.attr_counter*, %struct.attr_counter** %flags_list84, align 8, !dbg !3620
  %m_entry85 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %65, i32 0, i32 2, !dbg !3621
  %66 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry85, align 8, !dbg !3621
  %fflags_clear = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %66, i32 0, i32 21, !dbg !3622
  %67 = load i64, i64* %fflags_clear, align 8, !dbg !3622
  %68 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3623
  %set86 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %68, i32 0, i32 9, !dbg !3624
  %fflags_clear87 = getelementptr inbounds %struct.anon, %struct.anon* %set86, i32 0, i32 7, !dbg !3625
  %69 = load i64, i64* %fflags_clear87, align 8, !dbg !3625
  %cmp88 = icmp eq i64 %67, %69, !dbg !3626
  br i1 %cmp88, label %if.then89, label %if.end91, !dbg !3627

if.then89:                                        ; preds = %land.lhs.true, %if.then74
  %70 = load i32, i32* %effkeys, align 4, !dbg !3629
  %and90 = and i32 %70, -9, !dbg !3629
  store i32 %and90, i32* %effkeys, align 4, !dbg !3629
  br label %if.end91, !dbg !3630

if.end91:                                         ; preds = %if.then89, %land.lhs.true, %lor.lhs.false78
  br label %if.end92, !dbg !3631

if.end92:                                         ; preds = %if.end91, %if.else71
  br label %if.end93

if.end93:                                         ; preds = %if.end92, %if.then69
  br label %if.end115, !dbg !3632

if.else94:                                        ; preds = %do.end5
  %71 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3633
  %uid_list95 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %71, i32 0, i32 0, !dbg !3636
  %72 = load %struct.attr_counter*, %struct.attr_counter** %uid_list95, align 8, !dbg !3636
  %cmp96 = icmp eq %struct.attr_counter* %72, null, !dbg !3637
  br i1 %cmp96, label %if.then97, label %if.end99, !dbg !3638

if.then97:                                        ; preds = %if.else94
  %73 = load i32, i32* %keys, align 4, !dbg !3639
  %and98 = and i32 %73, -3145729, !dbg !3639
  store i32 %and98, i32* %keys, align 4, !dbg !3639
  br label %if.end99, !dbg !3640

if.end99:                                         ; preds = %if.then97, %if.else94
  %74 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3641
  %gid_list100 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %74, i32 0, i32 1, !dbg !3643
  %75 = load %struct.attr_counter*, %struct.attr_counter** %gid_list100, align 8, !dbg !3643
  %cmp101 = icmp eq %struct.attr_counter* %75, null, !dbg !3644
  br i1 %cmp101, label %if.then102, label %if.end104, !dbg !3645

if.then102:                                       ; preds = %if.end99
  %76 = load i32, i32* %keys, align 4, !dbg !3646
  %and103 = and i32 %76, -49, !dbg !3646
  store i32 %and103, i32* %keys, align 4, !dbg !3646
  br label %if.end104, !dbg !3647

if.end104:                                        ; preds = %if.then102, %if.end99
  %77 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3648
  %mode_list105 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %77, i32 0, i32 2, !dbg !3650
  %78 = load %struct.attr_counter*, %struct.attr_counter** %mode_list105, align 8, !dbg !3650
  %cmp106 = icmp eq %struct.attr_counter* %78, null, !dbg !3651
  br i1 %cmp106, label %if.then107, label %if.end109, !dbg !3652

if.then107:                                       ; preds = %if.end104
  %79 = load i32, i32* %keys, align 4, !dbg !3653
  %and108 = and i32 %79, -513, !dbg !3653
  store i32 %and108, i32* %keys, align 4, !dbg !3653
  br label %if.end109, !dbg !3654

if.end109:                                        ; preds = %if.then107, %if.end104
  %80 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3655
  %flags_list110 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %80, i32 0, i32 3, !dbg !3657
  %81 = load %struct.attr_counter*, %struct.attr_counter** %flags_list110, align 8, !dbg !3657
  %cmp111 = icmp eq %struct.attr_counter* %81, null, !dbg !3658
  br i1 %cmp111, label %if.then112, label %if.end114, !dbg !3659

if.then112:                                       ; preds = %if.end109
  %82 = load i32, i32* %keys, align 4, !dbg !3660
  %and113 = and i32 %82, -9, !dbg !3660
  store i32 %and113, i32* %keys, align 4, !dbg !3660
  br label %if.end114, !dbg !3661

if.end114:                                        ; preds = %if.then112, %if.end109
  br label %if.end115

if.end115:                                        ; preds = %if.end114, %if.end93
  %83 = load i32, i32* %keys, align 4, !dbg !3662
  %84 = load i32, i32* %effkeys, align 4, !dbg !3664
  %and116 = and i32 %83, %84, !dbg !3665
  %and117 = and i32 %and116, 524288, !dbg !3666
  %cmp118 = icmp ne i32 %and117, 0, !dbg !3667
  br i1 %cmp118, label %if.then119, label %if.end128, !dbg !3668

if.then119:                                       ; preds = %if.end115
  %85 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3669
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %85, i32 0, i32 17, !dbg !3672
  %86 = load i32, i32* %dironly, align 4, !dbg !3672
  %tobool120 = icmp ne i32 %86, 0, !dbg !3669
  br i1 %tobool120, label %if.then121, label %if.else123, !dbg !3673

if.then121:                                       ; preds = %if.then119
  %call = call %struct.archive_string* @archive_strcat(%struct.archive_string* %setstr, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.64, i32 0, i32 0)), !dbg !3674
  %87 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3676
  %set122 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %87, i32 0, i32 9, !dbg !3677
  %type = getelementptr inbounds %struct.anon, %struct.anon* %set122, i32 0, i32 1, !dbg !3678
  store i32 16384, i32* %type, align 4, !dbg !3679
  br label %if.end127, !dbg !3680

if.else123:                                       ; preds = %if.then119
  %call124 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %setstr, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.66, i32 0, i32 0)), !dbg !3681
  %88 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3683
  %set125 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %88, i32 0, i32 9, !dbg !3684
  %type126 = getelementptr inbounds %struct.anon, %struct.anon* %set125, i32 0, i32 1, !dbg !3685
  store i32 32768, i32* %type126, align 4, !dbg !3686
  br label %if.end127

if.end127:                                        ; preds = %if.else123, %if.then121
  br label %if.end128, !dbg !3687

if.end128:                                        ; preds = %if.end127, %if.end115
  %89 = load i32, i32* %keys, align 4, !dbg !3688
  %90 = load i32, i32* %effkeys, align 4, !dbg !3690
  %and129 = and i32 %89, %90, !dbg !3691
  %and130 = and i32 %and129, 2097152, !dbg !3692
  %cmp131 = icmp ne i32 %and130, 0, !dbg !3693
  br i1 %cmp131, label %if.then132, label %if.end151, !dbg !3694

if.then132:                                       ; preds = %if.end128
  %91 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3695
  %uid_list133 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %91, i32 0, i32 0, !dbg !3695
  %92 = load %struct.attr_counter*, %struct.attr_counter** %uid_list133, align 8, !dbg !3695
  %m_entry134 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %92, i32 0, i32 2, !dbg !3695
  %93 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry134, align 8, !dbg !3695
  %uname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %93, i32 0, i32 9, !dbg !3695
  %length135 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !3695
  %94 = load i64, i64* %length135, align 8, !dbg !3695
  %cmp136 = icmp ugt i64 %94, 0, !dbg !3698
  br i1 %cmp136, label %if.then137, label %if.else143, !dbg !3699

if.then137:                                       ; preds = %if.then132
  %call138 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %setstr, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.49, i32 0, i32 0)), !dbg !3700
  %95 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3702
  %uid_list139 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %95, i32 0, i32 0, !dbg !3703
  %96 = load %struct.attr_counter*, %struct.attr_counter** %uid_list139, align 8, !dbg !3703
  %m_entry140 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %96, i32 0, i32 2, !dbg !3704
  %97 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry140, align 8, !dbg !3704
  %uname141 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %97, i32 0, i32 9, !dbg !3705
  %s142 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname141, i32 0, i32 0, !dbg !3706
  %98 = load i8*, i8** %s142, align 8, !dbg !3706
  call void @mtree_quote(%struct.archive_string* %setstr, i8* %98), !dbg !3707
  br label %if.end150, !dbg !3708

if.else143:                                       ; preds = %if.then132
  %99 = load i32, i32* %keys, align 4, !dbg !3709
  %and144 = and i32 %99, -2097153, !dbg !3709
  store i32 %and144, i32* %keys, align 4, !dbg !3709
  %100 = load i32, i32* %oldkeys, align 4, !dbg !3711
  %and145 = and i32 %100, 2097152, !dbg !3713
  %cmp146 = icmp ne i32 %and145, 0, !dbg !3714
  br i1 %cmp146, label %if.then147, label %if.end149, !dbg !3715

if.then147:                                       ; preds = %if.else143
  %call148 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %unsetstr, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.70, i32 0, i32 0)), !dbg !3716
  br label %if.end149, !dbg !3716

if.end149:                                        ; preds = %if.then147, %if.else143
  br label %if.end150

if.end150:                                        ; preds = %if.end149, %if.then137
  br label %if.end151, !dbg !3717

if.end151:                                        ; preds = %if.end150, %if.end128
  %101 = load i32, i32* %keys, align 4, !dbg !3718
  %102 = load i32, i32* %effkeys, align 4, !dbg !3720
  %and152 = and i32 %101, %102, !dbg !3721
  %and153 = and i32 %and152, 1048576, !dbg !3722
  %cmp154 = icmp ne i32 %and153, 0, !dbg !3723
  br i1 %cmp154, label %if.then155, label %if.end163, !dbg !3724

if.then155:                                       ; preds = %if.end151
  %103 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3725
  %uid_list156 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %103, i32 0, i32 0, !dbg !3727
  %104 = load %struct.attr_counter*, %struct.attr_counter** %uid_list156, align 8, !dbg !3727
  %m_entry157 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %104, i32 0, i32 2, !dbg !3728
  %105 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry157, align 8, !dbg !3728
  %uid158 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %105, i32 0, i32 16, !dbg !3729
  %106 = load i64, i64* %uid158, align 8, !dbg !3729
  %107 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3730
  %set159 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %107, i32 0, i32 9, !dbg !3731
  %uid160 = getelementptr inbounds %struct.anon, %struct.anon* %set159, i32 0, i32 3, !dbg !3732
  store i64 %106, i64* %uid160, align 8, !dbg !3733
  %108 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3734
  %set161 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %108, i32 0, i32 9, !dbg !3735
  %uid162 = getelementptr inbounds %struct.anon, %struct.anon* %set161, i32 0, i32 3, !dbg !3736
  %109 = load i64, i64* %uid162, align 8, !dbg !3736
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %setstr, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i32 0, i32 0), i64 %109), !dbg !3737
  br label %if.end163, !dbg !3738

if.end163:                                        ; preds = %if.then155, %if.end151
  %110 = load i32, i32* %keys, align 4, !dbg !3739
  %111 = load i32, i32* %effkeys, align 4, !dbg !3741
  %and164 = and i32 %110, %111, !dbg !3742
  %and165 = and i32 %and164, 32, !dbg !3743
  %cmp166 = icmp ne i32 %and165, 0, !dbg !3744
  br i1 %cmp166, label %if.then167, label %if.end186, !dbg !3745

if.then167:                                       ; preds = %if.end163
  %112 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3746
  %gid_list168 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %112, i32 0, i32 1, !dbg !3746
  %113 = load %struct.attr_counter*, %struct.attr_counter** %gid_list168, align 8, !dbg !3746
  %m_entry169 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %113, i32 0, i32 2, !dbg !3746
  %114 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry169, align 8, !dbg !3746
  %gname = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %114, i32 0, i32 10, !dbg !3746
  %length170 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !3746
  %115 = load i64, i64* %length170, align 8, !dbg !3746
  %cmp171 = icmp ugt i64 %115, 0, !dbg !3749
  br i1 %cmp171, label %if.then172, label %if.else178, !dbg !3750

if.then172:                                       ; preds = %if.then167
  %call173 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %setstr, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.48, i32 0, i32 0)), !dbg !3751
  %116 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3753
  %gid_list174 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %116, i32 0, i32 1, !dbg !3754
  %117 = load %struct.attr_counter*, %struct.attr_counter** %gid_list174, align 8, !dbg !3754
  %m_entry175 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %117, i32 0, i32 2, !dbg !3755
  %118 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry175, align 8, !dbg !3755
  %gname176 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %118, i32 0, i32 10, !dbg !3756
  %s177 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname176, i32 0, i32 0, !dbg !3757
  %119 = load i8*, i8** %s177, align 8, !dbg !3757
  call void @mtree_quote(%struct.archive_string* %setstr, i8* %119), !dbg !3758
  br label %if.end185, !dbg !3759

if.else178:                                       ; preds = %if.then167
  %120 = load i32, i32* %keys, align 4, !dbg !3760
  %and179 = and i32 %120, -33, !dbg !3760
  store i32 %and179, i32* %keys, align 4, !dbg !3760
  %121 = load i32, i32* %oldkeys, align 4, !dbg !3762
  %and180 = and i32 %121, 32, !dbg !3764
  %cmp181 = icmp ne i32 %and180, 0, !dbg !3765
  br i1 %cmp181, label %if.then182, label %if.end184, !dbg !3766

if.then182:                                       ; preds = %if.else178
  %call183 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %unsetstr, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.71, i32 0, i32 0)), !dbg !3767
  br label %if.end184, !dbg !3767

if.end184:                                        ; preds = %if.then182, %if.else178
  br label %if.end185

if.end185:                                        ; preds = %if.end184, %if.then172
  br label %if.end186, !dbg !3768

if.end186:                                        ; preds = %if.end185, %if.end163
  %122 = load i32, i32* %keys, align 4, !dbg !3769
  %123 = load i32, i32* %effkeys, align 4, !dbg !3771
  %and187 = and i32 %122, %123, !dbg !3772
  %and188 = and i32 %and187, 16, !dbg !3773
  %cmp189 = icmp ne i32 %and188, 0, !dbg !3774
  br i1 %cmp189, label %if.then190, label %if.end198, !dbg !3775

if.then190:                                       ; preds = %if.end186
  %124 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3776
  %gid_list191 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %124, i32 0, i32 1, !dbg !3778
  %125 = load %struct.attr_counter*, %struct.attr_counter** %gid_list191, align 8, !dbg !3778
  %m_entry192 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %125, i32 0, i32 2, !dbg !3779
  %126 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry192, align 8, !dbg !3779
  %gid193 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %126, i32 0, i32 17, !dbg !3780
  %127 = load i64, i64* %gid193, align 8, !dbg !3780
  %128 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3781
  %set194 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %128, i32 0, i32 9, !dbg !3782
  %gid195 = getelementptr inbounds %struct.anon, %struct.anon* %set194, i32 0, i32 4, !dbg !3783
  store i64 %127, i64* %gid195, align 8, !dbg !3784
  %129 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3785
  %set196 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %129, i32 0, i32 9, !dbg !3786
  %gid197 = getelementptr inbounds %struct.anon, %struct.anon* %set196, i32 0, i32 4, !dbg !3787
  %130 = load i64, i64* %gid197, align 8, !dbg !3787
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %setstr, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.54, i32 0, i32 0), i64 %130), !dbg !3788
  br label %if.end198, !dbg !3789

if.end198:                                        ; preds = %if.then190, %if.end186
  %131 = load i32, i32* %keys, align 4, !dbg !3790
  %132 = load i32, i32* %effkeys, align 4, !dbg !3792
  %and199 = and i32 %131, %132, !dbg !3793
  %and200 = and i32 %and199, 512, !dbg !3794
  %cmp201 = icmp ne i32 %and200, 0, !dbg !3795
  br i1 %cmp201, label %if.then202, label %if.end210, !dbg !3796

if.then202:                                       ; preds = %if.end198
  %133 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3797
  %mode_list203 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %133, i32 0, i32 2, !dbg !3799
  %134 = load %struct.attr_counter*, %struct.attr_counter** %mode_list203, align 8, !dbg !3799
  %m_entry204 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %134, i32 0, i32 2, !dbg !3800
  %135 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry204, align 8, !dbg !3800
  %mode205 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %135, i32 0, i32 14, !dbg !3801
  %136 = load i32, i32* %mode205, align 8, !dbg !3801
  %137 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3802
  %set206 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %137, i32 0, i32 9, !dbg !3803
  %mode207 = getelementptr inbounds %struct.anon, %struct.anon* %set206, i32 0, i32 5, !dbg !3804
  store i32 %136, i32* %mode207, align 8, !dbg !3805
  %138 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3806
  %set208 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %138, i32 0, i32 9, !dbg !3807
  %mode209 = getelementptr inbounds %struct.anon, %struct.anon* %set208, i32 0, i32 5, !dbg !3808
  %139 = load i32, i32* %mode209, align 8, !dbg !3808
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %setstr, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.53, i32 0, i32 0), i32 %139), !dbg !3809
  br label %if.end210, !dbg !3810

if.end210:                                        ; preds = %if.then202, %if.end198
  %140 = load i32, i32* %keys, align 4, !dbg !3811
  %141 = load i32, i32* %effkeys, align 4, !dbg !3813
  %and211 = and i32 %140, %141, !dbg !3814
  %and212 = and i32 %and211, 8, !dbg !3815
  %cmp213 = icmp ne i32 %and212, 0, !dbg !3816
  br i1 %cmp213, label %if.then214, label %if.end243, !dbg !3817

if.then214:                                       ; preds = %if.end210
  %142 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3818
  %flags_list215 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %142, i32 0, i32 3, !dbg !3818
  %143 = load %struct.attr_counter*, %struct.attr_counter** %flags_list215, align 8, !dbg !3818
  %m_entry216 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %143, i32 0, i32 2, !dbg !3818
  %144 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry216, align 8, !dbg !3818
  %fflags_text = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %144, i32 0, i32 11, !dbg !3818
  %length217 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text, i32 0, i32 1, !dbg !3818
  %145 = load i64, i64* %length217, align 8, !dbg !3818
  %cmp218 = icmp ugt i64 %145, 0, !dbg !3821
  br i1 %cmp218, label %if.then219, label %if.else235, !dbg !3822

if.then219:                                       ; preds = %if.then214
  %call220 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %setstr, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.50, i32 0, i32 0)), !dbg !3823
  %146 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3825
  %flags_list221 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %146, i32 0, i32 3, !dbg !3826
  %147 = load %struct.attr_counter*, %struct.attr_counter** %flags_list221, align 8, !dbg !3826
  %m_entry222 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %147, i32 0, i32 2, !dbg !3827
  %148 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry222, align 8, !dbg !3827
  %fflags_text223 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %148, i32 0, i32 11, !dbg !3828
  %s224 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %fflags_text223, i32 0, i32 0, !dbg !3829
  %149 = load i8*, i8** %s224, align 8, !dbg !3829
  call void @mtree_quote(%struct.archive_string* %setstr, i8* %149), !dbg !3830
  %150 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3831
  %flags_list225 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %150, i32 0, i32 3, !dbg !3832
  %151 = load %struct.attr_counter*, %struct.attr_counter** %flags_list225, align 8, !dbg !3832
  %m_entry226 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %151, i32 0, i32 2, !dbg !3833
  %152 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry226, align 8, !dbg !3833
  %fflags_set227 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %152, i32 0, i32 20, !dbg !3834
  %153 = load i64, i64* %fflags_set227, align 8, !dbg !3834
  %154 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3835
  %set228 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %154, i32 0, i32 9, !dbg !3836
  %fflags_set229 = getelementptr inbounds %struct.anon, %struct.anon* %set228, i32 0, i32 6, !dbg !3837
  store i64 %153, i64* %fflags_set229, align 8, !dbg !3838
  %155 = load %struct.att_counter_set*, %struct.att_counter_set** %acs, align 8, !dbg !3839
  %flags_list230 = getelementptr inbounds %struct.att_counter_set, %struct.att_counter_set* %155, i32 0, i32 3, !dbg !3840
  %156 = load %struct.attr_counter*, %struct.attr_counter** %flags_list230, align 8, !dbg !3840
  %m_entry231 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %156, i32 0, i32 2, !dbg !3841
  %157 = load %struct.mtree_entry*, %struct.mtree_entry** %m_entry231, align 8, !dbg !3841
  %fflags_clear232 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %157, i32 0, i32 21, !dbg !3842
  %158 = load i64, i64* %fflags_clear232, align 8, !dbg !3842
  %159 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3843
  %set233 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %159, i32 0, i32 9, !dbg !3844
  %fflags_clear234 = getelementptr inbounds %struct.anon, %struct.anon* %set233, i32 0, i32 7, !dbg !3845
  store i64 %158, i64* %fflags_clear234, align 8, !dbg !3846
  br label %if.end242, !dbg !3847

if.else235:                                       ; preds = %if.then214
  %160 = load i32, i32* %keys, align 4, !dbg !3848
  %and236 = and i32 %160, -9, !dbg !3848
  store i32 %and236, i32* %keys, align 4, !dbg !3848
  %161 = load i32, i32* %oldkeys, align 4, !dbg !3850
  %and237 = and i32 %161, 8, !dbg !3852
  %cmp238 = icmp ne i32 %and237, 0, !dbg !3853
  br i1 %cmp238, label %if.then239, label %if.end241, !dbg !3854

if.then239:                                       ; preds = %if.else235
  %call240 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %unsetstr, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.72, i32 0, i32 0)), !dbg !3855
  br label %if.end241, !dbg !3855

if.end241:                                        ; preds = %if.then239, %if.else235
  br label %if.end242

if.end242:                                        ; preds = %if.end241, %if.then219
  br label %if.end243, !dbg !3856

if.end243:                                        ; preds = %if.end242, %if.end210
  %length244 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %unsetstr, i32 0, i32 1, !dbg !3857
  %162 = load i64, i64* %length244, align 8, !dbg !3857
  %cmp245 = icmp ugt i64 %162, 0, !dbg !3859
  br i1 %cmp245, label %if.then246, label %if.end248, !dbg !3860

if.then246:                                       ; preds = %if.end243
  %163 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3861
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %163, i32 0, i32 6, !dbg !3862
  %s247 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %unsetstr, i32 0, i32 0, !dbg !3863
  %164 = load i8*, i8** %s247, align 8, !dbg !3863
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %buf, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.73, i32 0, i32 0), i8* %164), !dbg !3864
  br label %if.end248, !dbg !3864

if.end248:                                        ; preds = %if.then246, %if.end243
  call void @archive_string_free(%struct.archive_string* %unsetstr), !dbg !3865
  %length249 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %setstr, i32 0, i32 1, !dbg !3866
  %165 = load i64, i64* %length249, align 8, !dbg !3866
  %cmp250 = icmp ugt i64 %165, 0, !dbg !3868
  br i1 %cmp250, label %if.then251, label %if.end254, !dbg !3869

if.then251:                                       ; preds = %if.end248
  %166 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3870
  %buf252 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %166, i32 0, i32 6, !dbg !3871
  %s253 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %setstr, i32 0, i32 0, !dbg !3872
  %167 = load i8*, i8** %s253, align 8, !dbg !3872
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %buf252, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.74, i32 0, i32 0), i8* %167), !dbg !3873
  br label %if.end254, !dbg !3873

if.end254:                                        ; preds = %if.then251, %if.end248
  call void @archive_string_free(%struct.archive_string* %setstr), !dbg !3874
  %168 = load i32, i32* %keys, align 4, !dbg !3875
  %169 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3876
  %set255 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %169, i32 0, i32 9, !dbg !3877
  %keys256 = getelementptr inbounds %struct.anon, %struct.anon* %set255, i32 0, i32 2, !dbg !3878
  store i32 %168, i32* %keys256, align 8, !dbg !3879
  %170 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !3880
  %set257 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %170, i32 0, i32 9, !dbg !3881
  %processing258 = getelementptr inbounds %struct.anon, %struct.anon* %set257, i32 0, i32 0, !dbg !3882
  store i32 1, i32* %processing258, align 8, !dbg !3883
  ret void, !dbg !3884
}

; Function Attrs: nounwind uwtable
define internal i32 @mtree_entry_add_child_tail(%struct.mtree_entry* %parent, %struct.mtree_entry* %child) #0 !dbg !401 {
entry:
  %parent.addr = alloca %struct.mtree_entry*, align 8
  %child.addr = alloca %struct.mtree_entry*, align 8
  store %struct.mtree_entry* %parent, %struct.mtree_entry** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %parent.addr, metadata !3885, metadata !426), !dbg !3886
  store %struct.mtree_entry* %child, %struct.mtree_entry** %child.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %child.addr, metadata !3887, metadata !426), !dbg !3888
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %child.addr, align 8, !dbg !3889
  %dir_info = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 3, !dbg !3890
  %1 = load %struct.dir_info*, %struct.dir_info** %dir_info, align 8, !dbg !3890
  %chnext = getelementptr inbounds %struct.dir_info, %struct.dir_info* %1, i32 0, i32 2, !dbg !3891
  store %struct.mtree_entry* null, %struct.mtree_entry** %chnext, align 8, !dbg !3892
  %2 = load %struct.mtree_entry*, %struct.mtree_entry** %child.addr, align 8, !dbg !3893
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %parent.addr, align 8, !dbg !3894
  %dir_info1 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 3, !dbg !3895
  %4 = load %struct.dir_info*, %struct.dir_info** %dir_info1, align 8, !dbg !3895
  %children = getelementptr inbounds %struct.dir_info, %struct.dir_info* %4, i32 0, i32 1, !dbg !3896
  %last = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children, i32 0, i32 1, !dbg !3897
  %5 = load %struct.mtree_entry**, %struct.mtree_entry*** %last, align 8, !dbg !3897
  store %struct.mtree_entry* %2, %struct.mtree_entry** %5, align 8, !dbg !3898
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %child.addr, align 8, !dbg !3899
  %dir_info2 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 3, !dbg !3900
  %7 = load %struct.dir_info*, %struct.dir_info** %dir_info2, align 8, !dbg !3900
  %chnext3 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %7, i32 0, i32 2, !dbg !3901
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %parent.addr, align 8, !dbg !3902
  %dir_info4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %8, i32 0, i32 3, !dbg !3903
  %9 = load %struct.dir_info*, %struct.dir_info** %dir_info4, align 8, !dbg !3903
  %children5 = getelementptr inbounds %struct.dir_info, %struct.dir_info* %9, i32 0, i32 1, !dbg !3904
  %last6 = getelementptr inbounds %struct.mtree_chain, %struct.mtree_chain* %children5, i32 0, i32 1, !dbg !3905
  store %struct.mtree_entry** %chnext3, %struct.mtree_entry*** %last6, align 8, !dbg !3906
  ret i32 1, !dbg !3907
}

; Function Attrs: nounwind uwtable
define internal i32 @write_dot_dot_entry(%struct.archive_write* %a, %struct.mtree_entry* %n) #0 !dbg !404 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %n.addr = alloca %struct.mtree_entry*, align 8
  %mtree = alloca %struct.mtree_writer*, align 8
  %ret = alloca i32, align 4
  %i = alloca i32, align 4
  %pd = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3908, metadata !426), !dbg !3909
  store %struct.mtree_entry* %n, %struct.mtree_entry** %n.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %n.addr, metadata !3910, metadata !426), !dbg !3911
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree, metadata !3912, metadata !426), !dbg !3913
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3914
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3915
  %1 = load i8*, i8** %format_data, align 8, !dbg !3915
  %2 = bitcast i8* %1 to %struct.mtree_writer*, !dbg !3914
  store %struct.mtree_writer* %2, %struct.mtree_writer** %mtree, align 8, !dbg !3913
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3916, metadata !426), !dbg !3917
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %n.addr, align 8, !dbg !3918
  %parentdir = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 5, !dbg !3920
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir, i32 0, i32 0, !dbg !3921
  %4 = load i8*, i8** %s, align 8, !dbg !3921
  %tobool = icmp ne i8* %4, null, !dbg !3918
  br i1 %tobool, label %if.then, label %if.end7, !dbg !3922

if.then:                                          ; preds = %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3923
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 18, !dbg !3926
  %6 = load i32, i32* %indent, align 8, !dbg !3926
  %tobool1 = icmp ne i32 %6, 0, !dbg !3923
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !3927

if.then2:                                         ; preds = %if.then
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3928, metadata !426), !dbg !3930
  call void @llvm.dbg.declare(metadata i32* %pd, metadata !3931, metadata !426), !dbg !3932
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3933
  %depth = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 12, !dbg !3934
  %8 = load i32, i32* %depth, align 4, !dbg !3934
  %mul = mul nsw i32 %8, 4, !dbg !3935
  store i32 %mul, i32* %pd, align 4, !dbg !3932
  store i32 0, i32* %i, align 4, !dbg !3936
  br label %for.cond, !dbg !3938

for.cond:                                         ; preds = %for.inc, %if.then2
  %9 = load i32, i32* %i, align 4, !dbg !3939
  %10 = load i32, i32* %pd, align 4, !dbg !3942
  %cmp = icmp slt i32 %9, %10, !dbg !3943
  br i1 %cmp, label %for.body, label %for.end, !dbg !3944

for.body:                                         ; preds = %for.cond
  %11 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3945
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %11, i32 0, i32 6, !dbg !3946
  %call = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf, i8 signext 32), !dbg !3947
  br label %for.inc, !dbg !3947

for.inc:                                          ; preds = %for.body
  %12 = load i32, i32* %i, align 4, !dbg !3948
  %inc = add nsw i32 %12, 1, !dbg !3948
  store i32 %inc, i32* %i, align 4, !dbg !3948
  br label %for.cond, !dbg !3950

for.end:                                          ; preds = %for.cond
  br label %if.end, !dbg !3951

if.end:                                           ; preds = %for.end, %if.then
  %13 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3952
  %buf3 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %13, i32 0, i32 6, !dbg !3953
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %n.addr, align 8, !dbg !3954
  %parentdir4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %14, i32 0, i32 5, !dbg !3955
  %s5 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %parentdir4, i32 0, i32 0, !dbg !3956
  %15 = load i8*, i8** %s5, align 8, !dbg !3956
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %n.addr, align 8, !dbg !3957
  %basename = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 6, !dbg !3958
  %s6 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %basename, i32 0, i32 0, !dbg !3959
  %17 = load i8*, i8** %s6, align 8, !dbg !3959
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %buf3, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.45, i32 0, i32 0), i8* %15, i8* %17), !dbg !3960
  br label %if.end7, !dbg !3961

if.end7:                                          ; preds = %if.end, %entry
  %18 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3962
  %indent8 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %18, i32 0, i32 18, !dbg !3964
  %19 = load i32, i32* %indent8, align 8, !dbg !3964
  %tobool9 = icmp ne i32 %19, 0, !dbg !3962
  br i1 %tobool9, label %if.then10, label %if.else, !dbg !3965

if.then10:                                        ; preds = %if.end7
  %20 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3966
  %ebuf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %20, i32 0, i32 5, !dbg !3966
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf, i32 0, i32 1, !dbg !3966
  store i64 0, i64* %length, align 8, !dbg !3966
  %21 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3968
  %ebuf11 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %21, i32 0, i32 5, !dbg !3969
  %22 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3970
  %dironly = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %22, i32 0, i32 17, !dbg !3971
  %23 = load i32, i32* %dironly, align 4, !dbg !3971
  %tobool12 = icmp ne i32 %23, 0, !dbg !3972
  %cond = select i1 %tobool12, i32 3, i32 4, !dbg !3972
  %conv = sext i32 %cond to i64, !dbg !3972
  %call13 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %ebuf11, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.75, i32 0, i32 0), i64 %conv), !dbg !3973
  %24 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3974
  call void @mtree_indent(%struct.mtree_writer* %24), !dbg !3975
  br label %if.end20, !dbg !3976

if.else:                                          ; preds = %if.end7
  %25 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3977
  %buf14 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %25, i32 0, i32 6, !dbg !3978
  %26 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3979
  %dironly15 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %26, i32 0, i32 17, !dbg !3980
  %27 = load i32, i32* %dironly15, align 4, !dbg !3980
  %tobool16 = icmp ne i32 %27, 0, !dbg !3981
  %cond17 = select i1 %tobool16, i32 3, i32 4, !dbg !3981
  %conv18 = sext i32 %cond17 to i64, !dbg !3981
  %call19 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf14, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.75, i32 0, i32 0), i64 %conv18), !dbg !3982
  br label %if.end20

if.end20:                                         ; preds = %if.else, %if.then10
  %28 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3983
  %buf21 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %28, i32 0, i32 6, !dbg !3985
  %length22 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf21, i32 0, i32 1, !dbg !3986
  %29 = load i64, i64* %length22, align 8, !dbg !3986
  %cmp23 = icmp ugt i64 %29, 32768, !dbg !3987
  br i1 %cmp23, label %if.then25, label %if.else33, !dbg !3988

if.then25:                                        ; preds = %if.end20
  %30 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3989
  %31 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3991
  %buf26 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %31, i32 0, i32 6, !dbg !3992
  %s27 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf26, i32 0, i32 0, !dbg !3993
  %32 = load i8*, i8** %s27, align 8, !dbg !3993
  %33 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3994
  %buf28 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %33, i32 0, i32 6, !dbg !3995
  %length29 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf28, i32 0, i32 1, !dbg !3996
  %34 = load i64, i64* %length29, align 8, !dbg !3996
  %call30 = call i32 @__archive_write_output(%struct.archive_write* %30, i8* %32, i64 %34), !dbg !3997
  store i32 %call30, i32* %ret, align 4, !dbg !3998
  %35 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree, align 8, !dbg !3999
  %buf31 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %35, i32 0, i32 6, !dbg !3999
  %length32 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %buf31, i32 0, i32 1, !dbg !3999
  store i64 0, i64* %length32, align 8, !dbg !3999
  br label %if.end34, !dbg !4000

if.else33:                                        ; preds = %if.end20
  store i32 0, i32* %ret, align 4, !dbg !4001
  br label %if.end34

if.end34:                                         ; preds = %if.else33, %if.then25
  %36 = load i32, i32* %ret, align 4, !dbg !4002
  ret i32 %36, !dbg !4003
}

; Function Attrs: nounwind uwtable
define internal %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %me, %struct.attr_counter* %prev) #0 !dbg !382 {
entry:
  %me.addr = alloca %struct.mtree_entry*, align 8
  %prev.addr = alloca %struct.attr_counter*, align 8
  %ac = alloca %struct.attr_counter*, align 8
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !4004, metadata !426), !dbg !4005
  store %struct.attr_counter* %prev, %struct.attr_counter** %prev.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %prev.addr, metadata !4006, metadata !426), !dbg !4007
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %ac, metadata !4008, metadata !426), !dbg !4009
  %call = call noalias i8* @malloc(i64 32) #6, !dbg !4010
  %0 = bitcast i8* %call to %struct.attr_counter*, !dbg !4010
  store %struct.attr_counter* %0, %struct.attr_counter** %ac, align 8, !dbg !4011
  %1 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4012
  %cmp = icmp ne %struct.attr_counter* %1, null, !dbg !4014
  br i1 %cmp, label %if.then, label %if.end, !dbg !4015

if.then:                                          ; preds = %entry
  %2 = load %struct.attr_counter*, %struct.attr_counter** %prev.addr, align 8, !dbg !4016
  %3 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4018
  %prev1 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %3, i32 0, i32 0, !dbg !4019
  store %struct.attr_counter* %2, %struct.attr_counter** %prev1, align 8, !dbg !4020
  %4 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4021
  %next = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %4, i32 0, i32 1, !dbg !4022
  store %struct.attr_counter* null, %struct.attr_counter** %next, align 8, !dbg !4023
  %5 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4024
  %count = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %5, i32 0, i32 3, !dbg !4025
  store i32 1, i32* %count, align 8, !dbg !4026
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4027
  %7 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4028
  %m_entry = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %7, i32 0, i32 2, !dbg !4029
  store %struct.mtree_entry* %6, %struct.mtree_entry** %m_entry, align 8, !dbg !4030
  br label %if.end, !dbg !4031

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.attr_counter*, %struct.attr_counter** %ac, align 8, !dbg !4032
  ret %struct.attr_counter* %8, !dbg !4033
}

; Function Attrs: nounwind uwtable
define internal i32 @attr_counter_inc(%struct.attr_counter** %top, %struct.attr_counter* %ac, %struct.attr_counter* %last, %struct.mtree_entry* %me) #0 !dbg !385 {
entry:
  %retval = alloca i32, align 4
  %top.addr = alloca %struct.attr_counter**, align 8
  %ac.addr = alloca %struct.attr_counter*, align 8
  %last.addr = alloca %struct.attr_counter*, align 8
  %me.addr = alloca %struct.mtree_entry*, align 8
  %pac = alloca %struct.attr_counter*, align 8
  store %struct.attr_counter** %top, %struct.attr_counter*** %top.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.attr_counter*** %top.addr, metadata !4034, metadata !426), !dbg !4035
  store %struct.attr_counter* %ac, %struct.attr_counter** %ac.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %ac.addr, metadata !4036, metadata !426), !dbg !4037
  store %struct.attr_counter* %last, %struct.attr_counter** %last.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %last.addr, metadata !4038, metadata !426), !dbg !4039
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !4040, metadata !426), !dbg !4041
  call void @llvm.dbg.declare(metadata %struct.attr_counter** %pac, metadata !4042, metadata !426), !dbg !4043
  %0 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4044
  %cmp = icmp ne %struct.attr_counter* %0, null, !dbg !4046
  br i1 %cmp, label %if.then, label %if.else39, !dbg !4047

if.then:                                          ; preds = %entry
  %1 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4048
  %count = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %1, i32 0, i32 3, !dbg !4050
  %2 = load i32, i32* %count, align 8, !dbg !4051
  %inc = add nsw i32 %2, 1, !dbg !4051
  store i32 %inc, i32* %count, align 8, !dbg !4051
  %3 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !4052
  %4 = load %struct.attr_counter*, %struct.attr_counter** %3, align 8, !dbg !4054
  %5 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4055
  %cmp1 = icmp eq %struct.attr_counter* %4, %5, !dbg !4056
  br i1 %cmp1, label %if.then5, label %lor.lhs.false, !dbg !4057

lor.lhs.false:                                    ; preds = %if.then
  %6 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4058
  %prev = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %6, i32 0, i32 0, !dbg !4060
  %7 = load %struct.attr_counter*, %struct.attr_counter** %prev, align 8, !dbg !4060
  %count2 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %7, i32 0, i32 3, !dbg !4061
  %8 = load i32, i32* %count2, align 8, !dbg !4061
  %9 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4062
  %count3 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %9, i32 0, i32 3, !dbg !4063
  %10 = load i32, i32* %count3, align 8, !dbg !4063
  %cmp4 = icmp sge i32 %8, %10, !dbg !4064
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !4065

if.then5:                                         ; preds = %lor.lhs.false, %if.then
  store i32 0, i32* %retval, align 4, !dbg !4066
  br label %return, !dbg !4066

if.end:                                           ; preds = %lor.lhs.false
  %11 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4067
  %prev6 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %11, i32 0, i32 0, !dbg !4069
  %12 = load %struct.attr_counter*, %struct.attr_counter** %prev6, align 8, !dbg !4069
  store %struct.attr_counter* %12, %struct.attr_counter** %pac, align 8, !dbg !4070
  br label %for.cond, !dbg !4071

for.cond:                                         ; preds = %for.inc, %if.end
  %13 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4072
  %tobool = icmp ne %struct.attr_counter* %13, null, !dbg !4075
  br i1 %tobool, label %for.body, label %for.end, !dbg !4075

for.body:                                         ; preds = %for.cond
  %14 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4076
  %count7 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %14, i32 0, i32 3, !dbg !4079
  %15 = load i32, i32* %count7, align 8, !dbg !4079
  %16 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4080
  %count8 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %16, i32 0, i32 3, !dbg !4081
  %17 = load i32, i32* %count8, align 8, !dbg !4081
  %cmp9 = icmp sge i32 %15, %17, !dbg !4082
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !4083

if.then10:                                        ; preds = %for.body
  br label %for.end, !dbg !4084

if.end11:                                         ; preds = %for.body
  br label %for.inc, !dbg !4085

for.inc:                                          ; preds = %if.end11
  %18 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4086
  %prev12 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %18, i32 0, i32 0, !dbg !4088
  %19 = load %struct.attr_counter*, %struct.attr_counter** %prev12, align 8, !dbg !4088
  store %struct.attr_counter* %19, %struct.attr_counter** %pac, align 8, !dbg !4089
  br label %for.cond, !dbg !4090

for.end:                                          ; preds = %if.then10, %for.cond
  %20 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4091
  %next = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %20, i32 0, i32 1, !dbg !4092
  %21 = load %struct.attr_counter*, %struct.attr_counter** %next, align 8, !dbg !4092
  %22 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4093
  %prev13 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %22, i32 0, i32 0, !dbg !4094
  %23 = load %struct.attr_counter*, %struct.attr_counter** %prev13, align 8, !dbg !4094
  %next14 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %23, i32 0, i32 1, !dbg !4095
  store %struct.attr_counter* %21, %struct.attr_counter** %next14, align 8, !dbg !4096
  %24 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4097
  %next15 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %24, i32 0, i32 1, !dbg !4099
  %25 = load %struct.attr_counter*, %struct.attr_counter** %next15, align 8, !dbg !4099
  %cmp16 = icmp ne %struct.attr_counter* %25, null, !dbg !4100
  br i1 %cmp16, label %if.then17, label %if.end21, !dbg !4101

if.then17:                                        ; preds = %for.end
  %26 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4102
  %prev18 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %26, i32 0, i32 0, !dbg !4103
  %27 = load %struct.attr_counter*, %struct.attr_counter** %prev18, align 8, !dbg !4103
  %28 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4104
  %next19 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %28, i32 0, i32 1, !dbg !4105
  %29 = load %struct.attr_counter*, %struct.attr_counter** %next19, align 8, !dbg !4105
  %prev20 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %29, i32 0, i32 0, !dbg !4106
  store %struct.attr_counter* %27, %struct.attr_counter** %prev20, align 8, !dbg !4107
  br label %if.end21, !dbg !4104

if.end21:                                         ; preds = %if.then17, %for.end
  %30 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4108
  %cmp22 = icmp ne %struct.attr_counter* %30, null, !dbg !4110
  br i1 %cmp22, label %if.then23, label %if.else, !dbg !4111

if.then23:                                        ; preds = %if.end21
  %31 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4112
  %32 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4114
  %prev24 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %32, i32 0, i32 0, !dbg !4115
  store %struct.attr_counter* %31, %struct.attr_counter** %prev24, align 8, !dbg !4116
  %33 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4117
  %next25 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %33, i32 0, i32 1, !dbg !4118
  %34 = load %struct.attr_counter*, %struct.attr_counter** %next25, align 8, !dbg !4118
  %35 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4119
  %next26 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %35, i32 0, i32 1, !dbg !4120
  store %struct.attr_counter* %34, %struct.attr_counter** %next26, align 8, !dbg !4121
  %36 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4122
  %37 = load %struct.attr_counter*, %struct.attr_counter** %pac, align 8, !dbg !4123
  %next27 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %37, i32 0, i32 1, !dbg !4124
  store %struct.attr_counter* %36, %struct.attr_counter** %next27, align 8, !dbg !4125
  %38 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4126
  %next28 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %38, i32 0, i32 1, !dbg !4128
  %39 = load %struct.attr_counter*, %struct.attr_counter** %next28, align 8, !dbg !4128
  %cmp29 = icmp ne %struct.attr_counter* %39, null, !dbg !4129
  br i1 %cmp29, label %if.then30, label %if.end33, !dbg !4130

if.then30:                                        ; preds = %if.then23
  %40 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4131
  %41 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4132
  %next31 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %41, i32 0, i32 1, !dbg !4133
  %42 = load %struct.attr_counter*, %struct.attr_counter** %next31, align 8, !dbg !4133
  %prev32 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %42, i32 0, i32 0, !dbg !4134
  store %struct.attr_counter* %40, %struct.attr_counter** %prev32, align 8, !dbg !4135
  br label %if.end33, !dbg !4132

if.end33:                                         ; preds = %if.then30, %if.then23
  br label %if.end38, !dbg !4136

if.else:                                          ; preds = %if.end21
  %43 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4137
  %prev34 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %43, i32 0, i32 0, !dbg !4139
  store %struct.attr_counter* null, %struct.attr_counter** %prev34, align 8, !dbg !4140
  %44 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !4141
  %45 = load %struct.attr_counter*, %struct.attr_counter** %44, align 8, !dbg !4142
  %46 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4143
  %next35 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %46, i32 0, i32 1, !dbg !4144
  store %struct.attr_counter* %45, %struct.attr_counter** %next35, align 8, !dbg !4145
  %47 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4146
  %48 = load %struct.attr_counter**, %struct.attr_counter*** %top.addr, align 8, !dbg !4147
  store %struct.attr_counter* %47, %struct.attr_counter** %48, align 8, !dbg !4148
  %49 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4149
  %50 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4150
  %next36 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %50, i32 0, i32 1, !dbg !4151
  %51 = load %struct.attr_counter*, %struct.attr_counter** %next36, align 8, !dbg !4151
  %prev37 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %51, i32 0, i32 0, !dbg !4152
  store %struct.attr_counter* %49, %struct.attr_counter** %prev37, align 8, !dbg !4153
  br label %if.end38

if.end38:                                         ; preds = %if.else, %if.end33
  br label %if.end47, !dbg !4154

if.else39:                                        ; preds = %entry
  %52 = load %struct.attr_counter*, %struct.attr_counter** %last.addr, align 8, !dbg !4155
  %cmp40 = icmp ne %struct.attr_counter* %52, null, !dbg !4158
  br i1 %cmp40, label %if.then41, label %if.end46, !dbg !4155

if.then41:                                        ; preds = %if.else39
  %53 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4159
  %54 = load %struct.attr_counter*, %struct.attr_counter** %last.addr, align 8, !dbg !4161
  %call = call %struct.attr_counter* @attr_counter_new(%struct.mtree_entry* %53, %struct.attr_counter* %54), !dbg !4162
  store %struct.attr_counter* %call, %struct.attr_counter** %ac.addr, align 8, !dbg !4163
  %55 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4164
  %cmp42 = icmp eq %struct.attr_counter* %55, null, !dbg !4166
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !4167

if.then43:                                        ; preds = %if.then41
  store i32 -1, i32* %retval, align 4, !dbg !4168
  br label %return, !dbg !4168

if.end44:                                         ; preds = %if.then41
  %56 = load %struct.attr_counter*, %struct.attr_counter** %ac.addr, align 8, !dbg !4169
  %57 = load %struct.attr_counter*, %struct.attr_counter** %last.addr, align 8, !dbg !4170
  %next45 = getelementptr inbounds %struct.attr_counter, %struct.attr_counter* %57, i32 0, i32 1, !dbg !4171
  store %struct.attr_counter* %56, %struct.attr_counter** %next45, align 8, !dbg !4172
  br label %if.end46, !dbg !4173

if.end46:                                         ; preds = %if.end44, %if.else39
  br label %if.end47

if.end47:                                         ; preds = %if.end46, %if.end38
  store i32 0, i32* %retval, align 4, !dbg !4174
  br label %return, !dbg !4174

return:                                           ; preds = %if.end47, %if.then43, %if.then5
  %58 = load i32, i32* %retval, align 4, !dbg !4175
  ret i32 %58, !dbg !4175
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal void @mtree_quote(%struct.archive_string* %s, i8* %str) #0 !dbg !391 {
entry:
  %s.addr = alloca %struct.archive_string*, align 8
  %str.addr = alloca i8*, align 8
  %start = alloca i8*, align 8
  %buf = alloca [4 x i8], align 1
  %c = alloca i8, align 1
  store %struct.archive_string* %s, %struct.archive_string** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %s.addr, metadata !4176, metadata !426), !dbg !4177
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !4178, metadata !426), !dbg !4179
  call void @llvm.dbg.declare(metadata i8** %start, metadata !4180, metadata !426), !dbg !4181
  call void @llvm.dbg.declare(metadata [4 x i8]* %buf, metadata !4182, metadata !426), !dbg !4186
  call void @llvm.dbg.declare(metadata i8* %c, metadata !4187, metadata !426), !dbg !4188
  %0 = load i8*, i8** %str.addr, align 8, !dbg !4189
  store i8* %0, i8** %start, align 8, !dbg !4191
  br label %for.cond, !dbg !4192

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i8*, i8** %str.addr, align 8, !dbg !4193
  %2 = load i8, i8* %1, align 1, !dbg !4196
  %conv = sext i8 %2 to i32, !dbg !4196
  %cmp = icmp ne i32 %conv, 0, !dbg !4197
  br i1 %cmp, label %for.body, label %for.end, !dbg !4198

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %str.addr, align 8, !dbg !4199
  %4 = load i8, i8* %3, align 1, !dbg !4202
  %idxprom = zext i8 %4 to i64, !dbg !4203
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* @safe_char, i64 0, i64 %idxprom, !dbg !4203
  %5 = load i8, i8* %arrayidx, align 1, !dbg !4203
  %tobool = icmp ne i8 %5, 0, !dbg !4203
  br i1 %tobool, label %if.then, label %if.end, !dbg !4204

if.then:                                          ; preds = %for.body
  br label %for.inc, !dbg !4205

if.end:                                           ; preds = %for.body
  %6 = load i8*, i8** %start, align 8, !dbg !4206
  %7 = load i8*, i8** %str.addr, align 8, !dbg !4208
  %cmp2 = icmp ne i8* %6, %7, !dbg !4209
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !4210

if.then4:                                         ; preds = %if.end
  %8 = load %struct.archive_string*, %struct.archive_string** %s.addr, align 8, !dbg !4211
  %9 = load i8*, i8** %start, align 8, !dbg !4212
  %10 = load i8*, i8** %str.addr, align 8, !dbg !4213
  %11 = load i8*, i8** %start, align 8, !dbg !4214
  %sub.ptr.lhs.cast = ptrtoint i8* %10 to i64, !dbg !4215
  %sub.ptr.rhs.cast = ptrtoint i8* %11 to i64, !dbg !4215
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !4215
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %8, i8* %9, i64 %sub.ptr.sub), !dbg !4216
  br label %if.end5, !dbg !4216

if.end5:                                          ; preds = %if.then4, %if.end
  %12 = load i8*, i8** %str.addr, align 8, !dbg !4217
  %13 = load i8, i8* %12, align 1, !dbg !4218
  store i8 %13, i8* %c, align 1, !dbg !4219
  %arrayidx6 = getelementptr inbounds [4 x i8], [4 x i8]* %buf, i64 0, i64 0, !dbg !4220
  store i8 92, i8* %arrayidx6, align 1, !dbg !4221
  %14 = load i8, i8* %c, align 1, !dbg !4222
  %conv7 = zext i8 %14 to i32, !dbg !4222
  %div = sdiv i32 %conv7, 64, !dbg !4223
  %add = add nsw i32 %div, 48, !dbg !4224
  %conv8 = trunc i32 %add to i8, !dbg !4225
  %arrayidx9 = getelementptr inbounds [4 x i8], [4 x i8]* %buf, i64 0, i64 1, !dbg !4226
  store i8 %conv8, i8* %arrayidx9, align 1, !dbg !4227
  %15 = load i8, i8* %c, align 1, !dbg !4228
  %conv10 = zext i8 %15 to i32, !dbg !4228
  %div11 = sdiv i32 %conv10, 8, !dbg !4229
  %rem = srem i32 %div11, 8, !dbg !4230
  %add12 = add nsw i32 %rem, 48, !dbg !4231
  %conv13 = trunc i32 %add12 to i8, !dbg !4232
  %arrayidx14 = getelementptr inbounds [4 x i8], [4 x i8]* %buf, i64 0, i64 2, !dbg !4233
  store i8 %conv13, i8* %arrayidx14, align 1, !dbg !4234
  %16 = load i8, i8* %c, align 1, !dbg !4235
  %conv15 = zext i8 %16 to i32, !dbg !4235
  %rem16 = srem i32 %conv15, 8, !dbg !4236
  %add17 = add nsw i32 %rem16, 48, !dbg !4237
  %conv18 = trunc i32 %add17 to i8, !dbg !4238
  %arrayidx19 = getelementptr inbounds [4 x i8], [4 x i8]* %buf, i64 0, i64 3, !dbg !4239
  store i8 %conv18, i8* %arrayidx19, align 1, !dbg !4240
  %17 = load %struct.archive_string*, %struct.archive_string** %s.addr, align 8, !dbg !4241
  %arraydecay = getelementptr inbounds [4 x i8], [4 x i8]* %buf, i32 0, i32 0, !dbg !4242
  %call20 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %17, i8* %arraydecay, i64 4), !dbg !4243
  %18 = load i8*, i8** %str.addr, align 8, !dbg !4244
  %add.ptr = getelementptr inbounds i8, i8* %18, i64 1, !dbg !4245
  store i8* %add.ptr, i8** %start, align 8, !dbg !4246
  br label %for.inc, !dbg !4247

for.inc:                                          ; preds = %if.end5, %if.then
  %19 = load i8*, i8** %str.addr, align 8, !dbg !4248
  %incdec.ptr = getelementptr inbounds i8, i8* %19, i32 1, !dbg !4248
  store i8* %incdec.ptr, i8** %str.addr, align 8, !dbg !4248
  br label %for.cond, !dbg !4250

for.end:                                          ; preds = %for.cond
  %20 = load i8*, i8** %start, align 8, !dbg !4251
  %21 = load i8*, i8** %str.addr, align 8, !dbg !4253
  %cmp21 = icmp ne i8* %20, %21, !dbg !4254
  br i1 %cmp21, label %if.then23, label %if.end28, !dbg !4255

if.then23:                                        ; preds = %for.end
  %22 = load %struct.archive_string*, %struct.archive_string** %s.addr, align 8, !dbg !4256
  %23 = load i8*, i8** %start, align 8, !dbg !4257
  %24 = load i8*, i8** %str.addr, align 8, !dbg !4258
  %25 = load i8*, i8** %start, align 8, !dbg !4259
  %sub.ptr.lhs.cast24 = ptrtoint i8* %24 to i64, !dbg !4260
  %sub.ptr.rhs.cast25 = ptrtoint i8* %25 to i64, !dbg !4260
  %sub.ptr.sub26 = sub i64 %sub.ptr.lhs.cast24, %sub.ptr.rhs.cast25, !dbg !4260
  %call27 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %22, i8* %23, i64 %sub.ptr.sub26), !dbg !4261
  br label %if.end28, !dbg !4261

if.end28:                                         ; preds = %if.then23, %for.end
  ret void, !dbg !4262
}

; Function Attrs: nounwind uwtable
define internal i32 @get_global_set_keys(%struct.mtree_writer* %mtree, %struct.mtree_entry* %me) #0 !dbg !395 {
entry:
  %retval = alloca i32, align 4
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %me.addr = alloca %struct.mtree_entry*, align 8
  %keys = alloca i32, align 4
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !4263, metadata !426), !dbg !4264
  store %struct.mtree_entry* %me, %struct.mtree_entry** %me.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %me.addr, metadata !4265, metadata !426), !dbg !4266
  call void @llvm.dbg.declare(metadata i32* %keys, metadata !4267, metadata !426), !dbg !4268
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4269
  %keys1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 16, !dbg !4270
  %1 = load i32, i32* %keys1, align 8, !dbg !4270
  store i32 %1, i32* %keys, align 4, !dbg !4271
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4272
  %set = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 9, !dbg !4274
  %keys2 = getelementptr inbounds %struct.anon, %struct.anon* %set, i32 0, i32 2, !dbg !4275
  %3 = load i32, i32* %keys2, align 8, !dbg !4275
  %cmp = icmp eq i32 %3, 0, !dbg !4276
  br i1 %cmp, label %if.then, label %if.end, !dbg !4277

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %keys, align 4, !dbg !4278
  store i32 %4, i32* %retval, align 4, !dbg !4279
  br label %return, !dbg !4279

if.end:                                           ; preds = %entry
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4280
  %set3 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 9, !dbg !4282
  %keys4 = getelementptr inbounds %struct.anon, %struct.anon* %set3, i32 0, i32 2, !dbg !4283
  %6 = load i32, i32* %keys4, align 8, !dbg !4283
  %and = and i32 %6, 48, !dbg !4284
  %cmp5 = icmp ne i32 %and, 0, !dbg !4285
  br i1 %cmp5, label %land.lhs.true, label %if.end11, !dbg !4286

land.lhs.true:                                    ; preds = %if.end
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4287
  %set6 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 9, !dbg !4288
  %gid = getelementptr inbounds %struct.anon, %struct.anon* %set6, i32 0, i32 4, !dbg !4289
  %8 = load i64, i64* %gid, align 8, !dbg !4289
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4290
  %gid7 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 17, !dbg !4291
  %10 = load i64, i64* %gid7, align 8, !dbg !4291
  %cmp8 = icmp eq i64 %8, %10, !dbg !4292
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !4293

if.then9:                                         ; preds = %land.lhs.true
  %11 = load i32, i32* %keys, align 4, !dbg !4295
  %and10 = and i32 %11, -49, !dbg !4295
  store i32 %and10, i32* %keys, align 4, !dbg !4295
  br label %if.end11, !dbg !4296

if.end11:                                         ; preds = %if.then9, %land.lhs.true, %if.end
  %12 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4297
  %set12 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %12, i32 0, i32 9, !dbg !4299
  %keys13 = getelementptr inbounds %struct.anon, %struct.anon* %set12, i32 0, i32 2, !dbg !4300
  %13 = load i32, i32* %keys13, align 8, !dbg !4300
  %and14 = and i32 %13, 3145728, !dbg !4301
  %cmp15 = icmp ne i32 %and14, 0, !dbg !4302
  br i1 %cmp15, label %land.lhs.true16, label %if.end22, !dbg !4303

land.lhs.true16:                                  ; preds = %if.end11
  %14 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4304
  %set17 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %14, i32 0, i32 9, !dbg !4305
  %uid = getelementptr inbounds %struct.anon, %struct.anon* %set17, i32 0, i32 3, !dbg !4306
  %15 = load i64, i64* %uid, align 8, !dbg !4306
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4307
  %uid18 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 16, !dbg !4308
  %17 = load i64, i64* %uid18, align 8, !dbg !4308
  %cmp19 = icmp eq i64 %15, %17, !dbg !4309
  br i1 %cmp19, label %if.then20, label %if.end22, !dbg !4310

if.then20:                                        ; preds = %land.lhs.true16
  %18 = load i32, i32* %keys, align 4, !dbg !4311
  %and21 = and i32 %18, -3145729, !dbg !4311
  store i32 %and21, i32* %keys, align 4, !dbg !4311
  br label %if.end22, !dbg !4312

if.end22:                                         ; preds = %if.then20, %land.lhs.true16, %if.end11
  %19 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4313
  %set23 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %19, i32 0, i32 9, !dbg !4315
  %keys24 = getelementptr inbounds %struct.anon, %struct.anon* %set23, i32 0, i32 2, !dbg !4316
  %20 = load i32, i32* %keys24, align 8, !dbg !4316
  %and25 = and i32 %20, 8, !dbg !4317
  %tobool = icmp ne i32 %and25, 0, !dbg !4317
  br i1 %tobool, label %if.then26, label %if.end37, !dbg !4318

if.then26:                                        ; preds = %if.end22
  %21 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4319
  %set27 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %21, i32 0, i32 9, !dbg !4322
  %fflags_set = getelementptr inbounds %struct.anon, %struct.anon* %set27, i32 0, i32 6, !dbg !4323
  %22 = load i64, i64* %fflags_set, align 8, !dbg !4323
  %23 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4324
  %fflags_set28 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %23, i32 0, i32 20, !dbg !4325
  %24 = load i64, i64* %fflags_set28, align 8, !dbg !4325
  %cmp29 = icmp eq i64 %22, %24, !dbg !4326
  br i1 %cmp29, label %land.lhs.true30, label %if.end36, !dbg !4327

land.lhs.true30:                                  ; preds = %if.then26
  %25 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4328
  %set31 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %25, i32 0, i32 9, !dbg !4329
  %fflags_clear = getelementptr inbounds %struct.anon, %struct.anon* %set31, i32 0, i32 7, !dbg !4330
  %26 = load i64, i64* %fflags_clear, align 8, !dbg !4330
  %27 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4331
  %fflags_clear32 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %27, i32 0, i32 21, !dbg !4332
  %28 = load i64, i64* %fflags_clear32, align 8, !dbg !4332
  %cmp33 = icmp eq i64 %26, %28, !dbg !4333
  br i1 %cmp33, label %if.then34, label %if.end36, !dbg !4334

if.then34:                                        ; preds = %land.lhs.true30
  %29 = load i32, i32* %keys, align 4, !dbg !4336
  %and35 = and i32 %29, -9, !dbg !4336
  store i32 %and35, i32* %keys, align 4, !dbg !4336
  br label %if.end36, !dbg !4337

if.end36:                                         ; preds = %if.then34, %land.lhs.true30, %if.then26
  br label %if.end37, !dbg !4338

if.end37:                                         ; preds = %if.end36, %if.end22
  %30 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4339
  %set38 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %30, i32 0, i32 9, !dbg !4341
  %keys39 = getelementptr inbounds %struct.anon, %struct.anon* %set38, i32 0, i32 2, !dbg !4342
  %31 = load i32, i32* %keys39, align 8, !dbg !4342
  %and40 = and i32 %31, 512, !dbg !4343
  %cmp41 = icmp ne i32 %and40, 0, !dbg !4344
  br i1 %cmp41, label %land.lhs.true42, label %if.end48, !dbg !4345

land.lhs.true42:                                  ; preds = %if.end37
  %32 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4346
  %set43 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %32, i32 0, i32 9, !dbg !4348
  %mode = getelementptr inbounds %struct.anon, %struct.anon* %set43, i32 0, i32 5, !dbg !4349
  %33 = load i32, i32* %mode, align 8, !dbg !4349
  %34 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4350
  %mode44 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %34, i32 0, i32 14, !dbg !4351
  %35 = load i32, i32* %mode44, align 8, !dbg !4351
  %cmp45 = icmp eq i32 %33, %35, !dbg !4352
  br i1 %cmp45, label %if.then46, label %if.end48, !dbg !4353

if.then46:                                        ; preds = %land.lhs.true42
  %36 = load i32, i32* %keys, align 4, !dbg !4354
  %and47 = and i32 %36, -513, !dbg !4354
  store i32 %and47, i32* %keys, align 4, !dbg !4354
  br label %if.end48, !dbg !4355

if.end48:                                         ; preds = %if.then46, %land.lhs.true42, %if.end37
  %37 = load %struct.mtree_entry*, %struct.mtree_entry** %me.addr, align 8, !dbg !4356
  %filetype = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %37, i32 0, i32 13, !dbg !4357
  %38 = load i32, i32* %filetype, align 4, !dbg !4357
  switch i32 %38, label %sw.default [
    i32 40960, label %sw.bb
    i32 49152, label %sw.bb
    i32 8192, label %sw.bb
    i32 24576, label %sw.bb
    i32 4096, label %sw.bb
    i32 16384, label %sw.bb49
    i32 32768, label %sw.bb60
  ], !dbg !4358

sw.bb:                                            ; preds = %if.end48, %if.end48, %if.end48, %if.end48, %if.end48
  br label %sw.epilog, !dbg !4359

sw.bb49:                                          ; preds = %if.end48
  %39 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4361
  %set50 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %39, i32 0, i32 9, !dbg !4363
  %keys51 = getelementptr inbounds %struct.anon, %struct.anon* %set50, i32 0, i32 2, !dbg !4364
  %40 = load i32, i32* %keys51, align 8, !dbg !4364
  %and52 = and i32 %40, 524288, !dbg !4365
  %cmp53 = icmp ne i32 %and52, 0, !dbg !4366
  br i1 %cmp53, label %land.lhs.true54, label %if.end59, !dbg !4367

land.lhs.true54:                                  ; preds = %sw.bb49
  %41 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4368
  %set55 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %41, i32 0, i32 9, !dbg !4369
  %type = getelementptr inbounds %struct.anon, %struct.anon* %set55, i32 0, i32 1, !dbg !4370
  %42 = load i32, i32* %type, align 4, !dbg !4370
  %cmp56 = icmp eq i32 %42, 16384, !dbg !4371
  br i1 %cmp56, label %if.then57, label %if.end59, !dbg !4372

if.then57:                                        ; preds = %land.lhs.true54
  %43 = load i32, i32* %keys, align 4, !dbg !4374
  %and58 = and i32 %43, -524289, !dbg !4374
  store i32 %and58, i32* %keys, align 4, !dbg !4374
  br label %if.end59, !dbg !4375

if.end59:                                         ; preds = %if.then57, %land.lhs.true54, %sw.bb49
  br label %sw.epilog, !dbg !4376

sw.bb60:                                          ; preds = %if.end48
  br label %sw.default, !dbg !4377

sw.default:                                       ; preds = %if.end48, %sw.bb60
  %44 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4378
  %set61 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %44, i32 0, i32 9, !dbg !4380
  %keys62 = getelementptr inbounds %struct.anon, %struct.anon* %set61, i32 0, i32 2, !dbg !4381
  %45 = load i32, i32* %keys62, align 8, !dbg !4381
  %and63 = and i32 %45, 524288, !dbg !4382
  %cmp64 = icmp ne i32 %and63, 0, !dbg !4383
  br i1 %cmp64, label %land.lhs.true65, label %if.end71, !dbg !4384

land.lhs.true65:                                  ; preds = %sw.default
  %46 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4385
  %set66 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %46, i32 0, i32 9, !dbg !4386
  %type67 = getelementptr inbounds %struct.anon, %struct.anon* %set66, i32 0, i32 1, !dbg !4387
  %47 = load i32, i32* %type67, align 4, !dbg !4387
  %cmp68 = icmp eq i32 %47, 32768, !dbg !4388
  br i1 %cmp68, label %if.then69, label %if.end71, !dbg !4389

if.then69:                                        ; preds = %land.lhs.true65
  %48 = load i32, i32* %keys, align 4, !dbg !4390
  %and70 = and i32 %48, -524289, !dbg !4390
  store i32 %and70, i32* %keys, align 4, !dbg !4390
  br label %if.end71, !dbg !4391

if.end71:                                         ; preds = %if.then69, %land.lhs.true65, %sw.default
  br label %sw.epilog, !dbg !4392

sw.epilog:                                        ; preds = %if.end71, %if.end59, %sw.bb
  %49 = load i32, i32* %keys, align 4, !dbg !4393
  store i32 %49, i32* %retval, align 4, !dbg !4394
  br label %return, !dbg !4394

return:                                           ; preds = %sw.epilog, %if.then
  %50 = load i32, i32* %retval, align 4, !dbg !4395
  ret i32 %50, !dbg !4395
}

; Function Attrs: nounwind uwtable
define internal void @sum_write(%struct.archive_string* %str, %struct.reg_info* %reg) #0 !dbg !396 {
entry:
  %str.addr = alloca %struct.archive_string*, align 8
  %reg.addr = alloca %struct.reg_info*, align 8
  store %struct.archive_string* %str, %struct.archive_string** %str.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %str.addr, metadata !4396, metadata !426), !dbg !4397
  store %struct.reg_info* %reg, %struct.reg_info** %reg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.reg_info** %reg.addr, metadata !4398, metadata !426), !dbg !4399
  %0 = load %struct.reg_info*, %struct.reg_info** %reg.addr, align 8, !dbg !4400
  %compute_sum = getelementptr inbounds %struct.reg_info, %struct.reg_info* %0, i32 0, i32 0, !dbg !4402
  %1 = load i32, i32* %compute_sum, align 4, !dbg !4402
  %and = and i32 %1, 1, !dbg !4403
  %tobool = icmp ne i32 %and, 0, !dbg !4403
  br i1 %tobool, label %if.then, label %if.end, !dbg !4404

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_string*, %struct.archive_string** %str.addr, align 8, !dbg !4405
  %3 = load %struct.reg_info*, %struct.reg_info** %reg.addr, align 8, !dbg !4407
  %crc = getelementptr inbounds %struct.reg_info, %struct.reg_info* %3, i32 0, i32 1, !dbg !4408
  %4 = load i32, i32* %crc, align 4, !dbg !4408
  %conv = zext i32 %4 to i64, !dbg !4409
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.68, i32 0, i32 0), i64 %conv), !dbg !4410
  br label %if.end, !dbg !4411

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !4412
}

; Function Attrs: nounwind uwtable
define internal void @mtree_indent(%struct.mtree_writer* %mtree) #0 !dbg !399 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %i = alloca i32, align 4
  %fn = alloca i32, align 4
  %nd = alloca i32, align 4
  %pd = alloca i32, align 4
  %r = alloca i8*, align 8
  %s = alloca i8*, align 8
  %x = alloca i8*, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !4413, metadata !426), !dbg !4414
  call void @llvm.dbg.declare(metadata i32* %i, metadata !4415, metadata !426), !dbg !4416
  call void @llvm.dbg.declare(metadata i32* %fn, metadata !4417, metadata !426), !dbg !4418
  call void @llvm.dbg.declare(metadata i32* %nd, metadata !4419, metadata !426), !dbg !4420
  call void @llvm.dbg.declare(metadata i32* %pd, metadata !4421, metadata !426), !dbg !4422
  call void @llvm.dbg.declare(metadata i8** %r, metadata !4423, metadata !426), !dbg !4424
  call void @llvm.dbg.declare(metadata i8** %s, metadata !4425, metadata !426), !dbg !4426
  call void @llvm.dbg.declare(metadata i8** %x, metadata !4427, metadata !426), !dbg !4428
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4429
  %classic = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 11, !dbg !4431
  %1 = load i32, i32* %classic, align 8, !dbg !4431
  %tobool = icmp ne i32 %1, 0, !dbg !4429
  br i1 %tobool, label %if.then, label %if.else5, !dbg !4432

if.then:                                          ; preds = %entry
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4433
  %indent = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 18, !dbg !4436
  %3 = load i32, i32* %indent, align 8, !dbg !4436
  %tobool1 = icmp ne i32 %3, 0, !dbg !4433
  br i1 %tobool1, label %if.then2, label %if.else, !dbg !4437

if.then2:                                         ; preds = %if.then
  store i32 0, i32* %nd, align 4, !dbg !4438
  %4 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4440
  %depth = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %4, i32 0, i32 12, !dbg !4441
  %5 = load i32, i32* %depth, align 4, !dbg !4441
  %mul = mul nsw i32 %5, 4, !dbg !4442
  store i32 %mul, i32* %pd, align 4, !dbg !4443
  br label %if.end, !dbg !4444

if.else:                                          ; preds = %if.then
  %6 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4445
  %depth3 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %6, i32 0, i32 12, !dbg !4447
  %7 = load i32, i32* %depth3, align 4, !dbg !4447
  %tobool4 = icmp ne i32 %7, 0, !dbg !4445
  %cond = select i1 %tobool4, i32 4, i32 0, !dbg !4445
  store i32 %cond, i32* %nd, align 4, !dbg !4448
  store i32 0, i32* %pd, align 4, !dbg !4449
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then2
  br label %if.end6, !dbg !4450

if.else5:                                         ; preds = %entry
  store i32 0, i32* %pd, align 4, !dbg !4451
  store i32 0, i32* %nd, align 4, !dbg !4452
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.end
  store i32 1, i32* %fn, align 4, !dbg !4453
  %8 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4454
  %ebuf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %8, i32 0, i32 5, !dbg !4455
  %s7 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf, i32 0, i32 0, !dbg !4456
  %9 = load i8*, i8** %s7, align 8, !dbg !4456
  store i8* %9, i8** %r, align 8, !dbg !4457
  store i8* %9, i8** %s, align 8, !dbg !4458
  store i8* null, i8** %x, align 8, !dbg !4459
  br label %while.cond, !dbg !4460

while.cond:                                       ; preds = %while.body, %if.end6
  %10 = load i8*, i8** %r, align 8, !dbg !4461
  %11 = load i8, i8* %10, align 1, !dbg !4463
  %conv = sext i8 %11 to i32, !dbg !4463
  %cmp = icmp eq i32 %conv, 32, !dbg !4464
  br i1 %cmp, label %while.body, label %while.end, !dbg !4465

while.body:                                       ; preds = %while.cond
  %12 = load i8*, i8** %r, align 8, !dbg !4466
  %incdec.ptr = getelementptr inbounds i8, i8* %12, i32 1, !dbg !4466
  store i8* %incdec.ptr, i8** %r, align 8, !dbg !4466
  br label %while.cond, !dbg !4467

while.end:                                        ; preds = %while.cond
  br label %while.cond9, !dbg !4469

while.cond9:                                      ; preds = %if.end91, %if.end56, %while.end
  %13 = load i8*, i8** %r, align 8, !dbg !4470
  %call = call i8* @strchr(i8* %13, i32 32) #7, !dbg !4471
  store i8* %call, i8** %r, align 8, !dbg !4472
  %cmp10 = icmp ne i8* %call, null, !dbg !4473
  br i1 %cmp10, label %while.body12, label %while.end92, !dbg !4474

while.body12:                                     ; preds = %while.cond9
  %14 = load i32, i32* %fn, align 4, !dbg !4475
  %tobool13 = icmp ne i32 %14, 0, !dbg !4475
  br i1 %tobool13, label %if.then14, label %if.end58, !dbg !4478

if.then14:                                        ; preds = %while.body12
  store i32 0, i32* %fn, align 4, !dbg !4479
  store i32 0, i32* %i, align 4, !dbg !4481
  br label %for.cond, !dbg !4483

for.cond:                                         ; preds = %for.inc, %if.then14
  %15 = load i32, i32* %i, align 4, !dbg !4484
  %16 = load i32, i32* %nd, align 4, !dbg !4487
  %17 = load i32, i32* %pd, align 4, !dbg !4488
  %add = add nsw i32 %16, %17, !dbg !4489
  %cmp15 = icmp slt i32 %15, %add, !dbg !4490
  br i1 %cmp15, label %for.body, label %for.end, !dbg !4491

for.body:                                         ; preds = %for.cond
  %18 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4492
  %buf = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %18, i32 0, i32 6, !dbg !4493
  %call17 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf, i8 signext 32), !dbg !4494
  br label %for.inc, !dbg !4494

for.inc:                                          ; preds = %for.body
  %19 = load i32, i32* %i, align 4, !dbg !4495
  %inc = add nsw i32 %19, 1, !dbg !4495
  store i32 %inc, i32* %i, align 4, !dbg !4495
  br label %for.cond, !dbg !4497

for.end:                                          ; preds = %for.cond
  %20 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4498
  %buf18 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %20, i32 0, i32 6, !dbg !4499
  %21 = load i8*, i8** %s, align 8, !dbg !4500
  %22 = load i8*, i8** %r, align 8, !dbg !4501
  %23 = load i8*, i8** %s, align 8, !dbg !4502
  %sub.ptr.lhs.cast = ptrtoint i8* %22 to i64, !dbg !4503
  %sub.ptr.rhs.cast = ptrtoint i8* %23 to i64, !dbg !4503
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !4503
  %call19 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf18, i8* %21, i64 %sub.ptr.sub), !dbg !4504
  %24 = load i32, i32* %nd, align 4, !dbg !4505
  %conv20 = sext i32 %24 to i64, !dbg !4505
  %25 = load i8*, i8** %r, align 8, !dbg !4507
  %26 = load i8*, i8** %s, align 8, !dbg !4508
  %sub.ptr.lhs.cast21 = ptrtoint i8* %25 to i64, !dbg !4509
  %sub.ptr.rhs.cast22 = ptrtoint i8* %26 to i64, !dbg !4509
  %sub.ptr.sub23 = sub i64 %sub.ptr.lhs.cast21, %sub.ptr.rhs.cast22, !dbg !4509
  %add24 = add nsw i64 %conv20, %sub.ptr.sub23, !dbg !4510
  %cmp25 = icmp sgt i64 %add24, 15, !dbg !4511
  br i1 %cmp25, label %if.then27, label %if.else40, !dbg !4512

if.then27:                                        ; preds = %for.end
  %27 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4513
  %buf28 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %27, i32 0, i32 6, !dbg !4515
  %call29 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf28, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.69, i32 0, i32 0), i64 3), !dbg !4516
  store i32 0, i32* %i, align 4, !dbg !4517
  br label %for.cond30, !dbg !4519

for.cond30:                                       ; preds = %for.inc37, %if.then27
  %28 = load i32, i32* %i, align 4, !dbg !4520
  %29 = load i32, i32* %pd, align 4, !dbg !4523
  %add31 = add nsw i32 16, %29, !dbg !4524
  %cmp32 = icmp slt i32 %28, %add31, !dbg !4525
  br i1 %cmp32, label %for.body34, label %for.end39, !dbg !4526

for.body34:                                       ; preds = %for.cond30
  %30 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4527
  %buf35 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %30, i32 0, i32 6, !dbg !4528
  %call36 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf35, i8 signext 32), !dbg !4529
  br label %for.inc37, !dbg !4529

for.inc37:                                        ; preds = %for.body34
  %31 = load i32, i32* %i, align 4, !dbg !4530
  %inc38 = add nsw i32 %31, 1, !dbg !4530
  store i32 %inc38, i32* %i, align 4, !dbg !4530
  br label %for.cond30, !dbg !4532

for.end39:                                        ; preds = %for.cond30
  br label %if.end56, !dbg !4533

if.else40:                                        ; preds = %for.end
  %32 = load i8*, i8** %r, align 8, !dbg !4534
  %33 = load i8*, i8** %s, align 8, !dbg !4537
  %sub.ptr.lhs.cast41 = ptrtoint i8* %32 to i64, !dbg !4538
  %sub.ptr.rhs.cast42 = ptrtoint i8* %33 to i64, !dbg !4538
  %sub.ptr.sub43 = sub i64 %sub.ptr.lhs.cast41, %sub.ptr.rhs.cast42, !dbg !4538
  %34 = load i32, i32* %nd, align 4, !dbg !4539
  %conv44 = sext i32 %34 to i64, !dbg !4539
  %add45 = add nsw i64 %sub.ptr.sub43, %conv44, !dbg !4540
  %conv46 = trunc i64 %add45 to i32, !dbg !4541
  store i32 %conv46, i32* %i, align 4, !dbg !4542
  br label %for.cond47, !dbg !4543

for.cond47:                                       ; preds = %for.inc53, %if.else40
  %35 = load i32, i32* %i, align 4, !dbg !4544
  %cmp48 = icmp slt i32 %35, 16, !dbg !4546
  br i1 %cmp48, label %for.body50, label %for.end55, !dbg !4547

for.body50:                                       ; preds = %for.cond47
  %36 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4549
  %buf51 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %36, i32 0, i32 6, !dbg !4550
  %call52 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf51, i8 signext 32), !dbg !4551
  br label %for.inc53, !dbg !4551

for.inc53:                                        ; preds = %for.body50
  %37 = load i32, i32* %i, align 4, !dbg !4552
  %inc54 = add nsw i32 %37, 1, !dbg !4552
  store i32 %inc54, i32* %i, align 4, !dbg !4552
  br label %for.cond47, !dbg !4554

for.end55:                                        ; preds = %for.cond47
  br label %if.end56

if.end56:                                         ; preds = %for.end55, %for.end39
  %38 = load i8*, i8** %r, align 8, !dbg !4556
  %incdec.ptr57 = getelementptr inbounds i8, i8* %38, i32 1, !dbg !4556
  store i8* %incdec.ptr57, i8** %r, align 8, !dbg !4556
  store i8* %incdec.ptr57, i8** %s, align 8, !dbg !4557
  store i8* null, i8** %x, align 8, !dbg !4558
  br label %while.cond9, !dbg !4559

if.end58:                                         ; preds = %while.body12
  %39 = load i32, i32* %pd, align 4, !dbg !4560
  %conv59 = sext i32 %39 to i64, !dbg !4560
  %40 = load i8*, i8** %r, align 8, !dbg !4562
  %41 = load i8*, i8** %s, align 8, !dbg !4563
  %sub.ptr.lhs.cast60 = ptrtoint i8* %40 to i64, !dbg !4564
  %sub.ptr.rhs.cast61 = ptrtoint i8* %41 to i64, !dbg !4564
  %sub.ptr.sub62 = sub i64 %sub.ptr.lhs.cast60, %sub.ptr.rhs.cast61, !dbg !4564
  %add63 = add nsw i64 %conv59, %sub.ptr.sub62, !dbg !4565
  %cmp64 = icmp sle i64 %add63, 62, !dbg !4566
  br i1 %cmp64, label %if.then66, label %if.else68, !dbg !4567

if.then66:                                        ; preds = %if.end58
  %42 = load i8*, i8** %r, align 8, !dbg !4568
  %incdec.ptr67 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !4568
  store i8* %incdec.ptr67, i8** %r, align 8, !dbg !4568
  store i8* %42, i8** %x, align 8, !dbg !4569
  br label %if.end91, !dbg !4570

if.else68:                                        ; preds = %if.end58
  %43 = load i8*, i8** %x, align 8, !dbg !4571
  %cmp69 = icmp eq i8* %43, null, !dbg !4574
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !4575

if.then71:                                        ; preds = %if.else68
  %44 = load i8*, i8** %r, align 8, !dbg !4576
  store i8* %44, i8** %x, align 8, !dbg !4577
  br label %if.end72, !dbg !4578

if.end72:                                         ; preds = %if.then71, %if.else68
  %45 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4579
  %buf73 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %45, i32 0, i32 6, !dbg !4580
  %46 = load i8*, i8** %s, align 8, !dbg !4581
  %47 = load i8*, i8** %x, align 8, !dbg !4582
  %48 = load i8*, i8** %s, align 8, !dbg !4583
  %sub.ptr.lhs.cast74 = ptrtoint i8* %47 to i64, !dbg !4584
  %sub.ptr.rhs.cast75 = ptrtoint i8* %48 to i64, !dbg !4584
  %sub.ptr.sub76 = sub i64 %sub.ptr.lhs.cast74, %sub.ptr.rhs.cast75, !dbg !4584
  %call77 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf73, i8* %46, i64 %sub.ptr.sub76), !dbg !4585
  %49 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4586
  %buf78 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %49, i32 0, i32 6, !dbg !4587
  %call79 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf78, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.69, i32 0, i32 0), i64 3), !dbg !4588
  store i32 0, i32* %i, align 4, !dbg !4589
  br label %for.cond80, !dbg !4591

for.cond80:                                       ; preds = %for.inc87, %if.end72
  %50 = load i32, i32* %i, align 4, !dbg !4592
  %51 = load i32, i32* %pd, align 4, !dbg !4595
  %add81 = add nsw i32 16, %51, !dbg !4596
  %cmp82 = icmp slt i32 %50, %add81, !dbg !4597
  br i1 %cmp82, label %for.body84, label %for.end89, !dbg !4598

for.body84:                                       ; preds = %for.cond80
  %52 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4599
  %buf85 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %52, i32 0, i32 6, !dbg !4600
  %call86 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf85, i8 signext 32), !dbg !4601
  br label %for.inc87, !dbg !4601

for.inc87:                                        ; preds = %for.body84
  %53 = load i32, i32* %i, align 4, !dbg !4602
  %inc88 = add nsw i32 %53, 1, !dbg !4602
  store i32 %inc88, i32* %i, align 4, !dbg !4602
  br label %for.cond80, !dbg !4604

for.end89:                                        ; preds = %for.cond80
  %54 = load i8*, i8** %x, align 8, !dbg !4605
  %incdec.ptr90 = getelementptr inbounds i8, i8* %54, i32 1, !dbg !4605
  store i8* %incdec.ptr90, i8** %x, align 8, !dbg !4605
  store i8* %incdec.ptr90, i8** %r, align 8, !dbg !4606
  store i8* %incdec.ptr90, i8** %s, align 8, !dbg !4607
  store i8* null, i8** %x, align 8, !dbg !4608
  br label %if.end91

if.end91:                                         ; preds = %for.end89, %if.then66
  br label %while.cond9, !dbg !4609

while.end92:                                      ; preds = %while.cond9
  %55 = load i32, i32* %fn, align 4, !dbg !4610
  %tobool93 = icmp ne i32 %55, 0, !dbg !4610
  br i1 %tobool93, label %if.then94, label %if.end108, !dbg !4612

if.then94:                                        ; preds = %while.end92
  store i32 0, i32* %i, align 4, !dbg !4613
  br label %for.cond95, !dbg !4616

for.cond95:                                       ; preds = %for.inc102, %if.then94
  %56 = load i32, i32* %i, align 4, !dbg !4617
  %57 = load i32, i32* %nd, align 4, !dbg !4620
  %58 = load i32, i32* %pd, align 4, !dbg !4621
  %add96 = add nsw i32 %57, %58, !dbg !4622
  %cmp97 = icmp slt i32 %56, %add96, !dbg !4623
  br i1 %cmp97, label %for.body99, label %for.end104, !dbg !4624

for.body99:                                       ; preds = %for.cond95
  %59 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4625
  %buf100 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %59, i32 0, i32 6, !dbg !4626
  %call101 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf100, i8 signext 32), !dbg !4627
  br label %for.inc102, !dbg !4627

for.inc102:                                       ; preds = %for.body99
  %60 = load i32, i32* %i, align 4, !dbg !4628
  %inc103 = add nsw i32 %60, 1, !dbg !4628
  store i32 %inc103, i32* %i, align 4, !dbg !4628
  br label %for.cond95, !dbg !4630

for.end104:                                       ; preds = %for.cond95
  %61 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4631
  %buf105 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %61, i32 0, i32 6, !dbg !4632
  %62 = load i8*, i8** %s, align 8, !dbg !4633
  %call106 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %buf105, i8* %62), !dbg !4634
  %63 = load i8*, i8** %s, align 8, !dbg !4635
  %call107 = call i64 @strlen(i8* %63) #7, !dbg !4636
  %64 = load i8*, i8** %s, align 8, !dbg !4637
  %add.ptr = getelementptr inbounds i8, i8* %64, i64 %call107, !dbg !4637
  store i8* %add.ptr, i8** %s, align 8, !dbg !4637
  br label %if.end108, !dbg !4638

if.end108:                                        ; preds = %for.end104, %while.end92
  %65 = load i8*, i8** %x, align 8, !dbg !4639
  %cmp109 = icmp ne i8* %65, null, !dbg !4641
  br i1 %cmp109, label %land.lhs.true, label %if.end135, !dbg !4642

land.lhs.true:                                    ; preds = %if.end108
  %66 = load i32, i32* %pd, align 4, !dbg !4643
  %conv111 = sext i32 %66 to i64, !dbg !4643
  %67 = load i8*, i8** %s, align 8, !dbg !4645
  %call112 = call i64 @strlen(i8* %67) #7, !dbg !4646
  %add113 = add i64 %conv111, %call112, !dbg !4647
  %cmp114 = icmp ugt i64 %add113, 62, !dbg !4648
  br i1 %cmp114, label %if.then116, label %if.end135, !dbg !4649

if.then116:                                       ; preds = %land.lhs.true
  %68 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4650
  %buf117 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %68, i32 0, i32 6, !dbg !4652
  %69 = load i8*, i8** %s, align 8, !dbg !4653
  %70 = load i8*, i8** %x, align 8, !dbg !4654
  %71 = load i8*, i8** %s, align 8, !dbg !4655
  %sub.ptr.lhs.cast118 = ptrtoint i8* %70 to i64, !dbg !4656
  %sub.ptr.rhs.cast119 = ptrtoint i8* %71 to i64, !dbg !4656
  %sub.ptr.sub120 = sub i64 %sub.ptr.lhs.cast118, %sub.ptr.rhs.cast119, !dbg !4656
  %call121 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf117, i8* %69, i64 %sub.ptr.sub120), !dbg !4657
  %72 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4658
  %buf122 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %72, i32 0, i32 6, !dbg !4659
  %call123 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %buf122, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.69, i32 0, i32 0), i64 3), !dbg !4660
  store i32 0, i32* %i, align 4, !dbg !4661
  br label %for.cond124, !dbg !4663

for.cond124:                                      ; preds = %for.inc131, %if.then116
  %73 = load i32, i32* %i, align 4, !dbg !4664
  %74 = load i32, i32* %pd, align 4, !dbg !4667
  %add125 = add nsw i32 16, %74, !dbg !4668
  %cmp126 = icmp slt i32 %73, %add125, !dbg !4669
  br i1 %cmp126, label %for.body128, label %for.end133, !dbg !4670

for.body128:                                      ; preds = %for.cond124
  %75 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4671
  %buf129 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %75, i32 0, i32 6, !dbg !4672
  %call130 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %buf129, i8 signext 32), !dbg !4673
  br label %for.inc131, !dbg !4673

for.inc131:                                       ; preds = %for.body128
  %76 = load i32, i32* %i, align 4, !dbg !4674
  %inc132 = add nsw i32 %76, 1, !dbg !4674
  store i32 %inc132, i32* %i, align 4, !dbg !4674
  br label %for.cond124, !dbg !4676

for.end133:                                       ; preds = %for.cond124
  %77 = load i8*, i8** %x, align 8, !dbg !4677
  %incdec.ptr134 = getelementptr inbounds i8, i8* %77, i32 1, !dbg !4677
  store i8* %incdec.ptr134, i8** %x, align 8, !dbg !4677
  store i8* %incdec.ptr134, i8** %s, align 8, !dbg !4678
  br label %if.end135, !dbg !4679

if.end135:                                        ; preds = %for.end133, %land.lhs.true, %if.end108
  %78 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4680
  %buf136 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %78, i32 0, i32 6, !dbg !4681
  %79 = load i8*, i8** %s, align 8, !dbg !4682
  %call137 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %buf136, i8* %79), !dbg !4683
  %80 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4684
  %ebuf138 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %80, i32 0, i32 5, !dbg !4684
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %ebuf138, i32 0, i32 1, !dbg !4684
  store i64 0, i64* %length, align 8, !dbg !4684
  ret void, !dbg !4685
}

; Function Attrs: nounwind uwtable
define internal void @sum_update(%struct.mtree_writer* %mtree, i8* %buff, i64 %n) #0 !dbg !406 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %buff.addr = alloca i8*, align 8
  %n.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  %nn = alloca i64, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !4686, metadata !426), !dbg !4687
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !4688, metadata !426), !dbg !4689
  store i64 %n, i64* %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %n.addr, metadata !4690, metadata !426), !dbg !4691
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4692
  %compute_sum = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 13, !dbg !4694
  %1 = load i32, i32* %compute_sum, align 8, !dbg !4694
  %and = and i32 %1, 1, !dbg !4695
  %tobool = icmp ne i32 %and, 0, !dbg !4695
  br i1 %tobool, label %if.then, label %if.end, !dbg !4696

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4697, metadata !426), !dbg !4699
  call void @llvm.dbg.declare(metadata i64* %nn, metadata !4700, metadata !426), !dbg !4701
  %2 = load i64, i64* %n.addr, align 8, !dbg !4702
  store i64 %2, i64* %nn, align 8, !dbg !4704
  %3 = load i8*, i8** %buff.addr, align 8, !dbg !4705
  store i8* %3, i8** %p, align 8, !dbg !4706
  br label %for.cond, !dbg !4707

for.cond:                                         ; preds = %for.inc, %if.then
  %4 = load i64, i64* %nn, align 8, !dbg !4708
  %dec = add i64 %4, -1, !dbg !4708
  store i64 %dec, i64* %nn, align 8, !dbg !4708
  %tobool1 = icmp ne i64 %4, 0, !dbg !4711
  br i1 %tobool1, label %for.body, label %for.end, !dbg !4711

for.body:                                         ; preds = %for.cond
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4712
  %crc = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 14, !dbg !4712
  %6 = load i32, i32* %crc, align 4, !dbg !4712
  %shl = shl i32 %6, 8, !dbg !4712
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4712
  %crc2 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 14, !dbg !4712
  %8 = load i32, i32* %crc2, align 4, !dbg !4712
  %shr = lshr i32 %8, 24, !dbg !4712
  %9 = load i8*, i8** %p, align 8, !dbg !4712
  %10 = load i8, i8* %9, align 1, !dbg !4712
  %conv = zext i8 %10 to i32, !dbg !4712
  %xor = xor i32 %shr, %conv, !dbg !4712
  %idxprom = zext i32 %xor to i64, !dbg !4712
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @crctab, i64 0, i64 %idxprom, !dbg !4712
  %11 = load i32, i32* %arrayidx, align 4, !dbg !4712
  %xor3 = xor i32 %shl, %11, !dbg !4712
  %12 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4712
  %crc4 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %12, i32 0, i32 14, !dbg !4712
  store i32 %xor3, i32* %crc4, align 4, !dbg !4712
  br label %for.inc, !dbg !4712

for.inc:                                          ; preds = %for.body
  %13 = load i8*, i8** %p, align 8, !dbg !4713
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !4713
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !4713
  br label %for.cond, !dbg !4715

for.end:                                          ; preds = %for.cond
  %14 = load i64, i64* %n.addr, align 8, !dbg !4716
  %15 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4717
  %crc_len = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %15, i32 0, i32 15, !dbg !4718
  %16 = load i64, i64* %crc_len, align 8, !dbg !4719
  %add = add i64 %16, %14, !dbg !4719
  store i64 %add, i64* %crc_len, align 8, !dbg !4719
  br label %if.end, !dbg !4720

if.end:                                           ; preds = %for.end, %entry
  ret void, !dbg !4721
}

; Function Attrs: nounwind uwtable
define internal void @sum_final(%struct.mtree_writer* %mtree, %struct.reg_info* %reg) #0 !dbg !410 {
entry:
  %mtree.addr = alloca %struct.mtree_writer*, align 8
  %reg.addr = alloca %struct.reg_info*, align 8
  %len = alloca i64, align 8
  store %struct.mtree_writer* %mtree, %struct.mtree_writer** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_writer** %mtree.addr, metadata !4722, metadata !426), !dbg !4723
  store %struct.reg_info* %reg, %struct.reg_info** %reg.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.reg_info** %reg.addr, metadata !4724, metadata !426), !dbg !4725
  %0 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4726
  %compute_sum = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %0, i32 0, i32 13, !dbg !4728
  %1 = load i32, i32* %compute_sum, align 8, !dbg !4728
  %and = and i32 %1, 1, !dbg !4729
  %tobool = icmp ne i32 %and, 0, !dbg !4729
  br i1 %tobool, label %if.then, label %if.end, !dbg !4730

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %len, metadata !4731, metadata !426), !dbg !4733
  %2 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4734
  %crc_len = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %2, i32 0, i32 15, !dbg !4736
  %3 = load i64, i64* %crc_len, align 8, !dbg !4736
  store i64 %3, i64* %len, align 8, !dbg !4737
  br label %for.cond, !dbg !4738

for.cond:                                         ; preds = %for.inc, %if.then
  %4 = load i64, i64* %len, align 8, !dbg !4739
  %cmp = icmp ne i64 %4, 0, !dbg !4742
  br i1 %cmp, label %for.body, label %for.end, !dbg !4743

for.body:                                         ; preds = %for.cond
  %5 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4744
  %crc = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %5, i32 0, i32 14, !dbg !4744
  %6 = load i32, i32* %crc, align 4, !dbg !4744
  %shl = shl i32 %6, 8, !dbg !4744
  %7 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4744
  %crc1 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %7, i32 0, i32 14, !dbg !4744
  %8 = load i32, i32* %crc1, align 4, !dbg !4744
  %shr = lshr i32 %8, 24, !dbg !4744
  %conv = zext i32 %shr to i64, !dbg !4744
  %9 = load i64, i64* %len, align 8, !dbg !4744
  %and2 = and i64 %9, 255, !dbg !4744
  %xor = xor i64 %conv, %and2, !dbg !4744
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @crctab, i64 0, i64 %xor, !dbg !4744
  %10 = load i32, i32* %arrayidx, align 4, !dbg !4744
  %xor3 = xor i32 %shl, %10, !dbg !4744
  %11 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4744
  %crc4 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %11, i32 0, i32 14, !dbg !4744
  store i32 %xor3, i32* %crc4, align 4, !dbg !4744
  br label %for.inc, !dbg !4744

for.inc:                                          ; preds = %for.body
  %12 = load i64, i64* %len, align 8, !dbg !4745
  %shr5 = lshr i64 %12, 8, !dbg !4745
  store i64 %shr5, i64* %len, align 8, !dbg !4745
  br label %for.cond, !dbg !4747

for.end:                                          ; preds = %for.cond
  %13 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4748
  %crc6 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %13, i32 0, i32 14, !dbg !4749
  %14 = load i32, i32* %crc6, align 4, !dbg !4749
  %neg = xor i32 %14, -1, !dbg !4750
  %15 = load %struct.reg_info*, %struct.reg_info** %reg.addr, align 8, !dbg !4751
  %crc7 = getelementptr inbounds %struct.reg_info, %struct.reg_info* %15, i32 0, i32 1, !dbg !4752
  store i32 %neg, i32* %crc7, align 4, !dbg !4753
  br label %if.end, !dbg !4754

if.end:                                           ; preds = %for.end, %entry
  %16 = load %struct.mtree_writer*, %struct.mtree_writer** %mtree.addr, align 8, !dbg !4755
  %compute_sum8 = getelementptr inbounds %struct.mtree_writer, %struct.mtree_writer* %16, i32 0, i32 13, !dbg !4756
  %17 = load i32, i32* %compute_sum8, align 8, !dbg !4756
  %18 = load %struct.reg_info*, %struct.reg_info** %reg.addr, align 8, !dbg !4757
  %compute_sum9 = getelementptr inbounds %struct.reg_info, %struct.reg_info* %18, i32 0, i32 0, !dbg !4758
  store i32 %17, i32* %compute_sum9, align 4, !dbg !4759
  ret void, !dbg !4760
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!422, !423}
!llvm.ident = !{!424}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !329, globals: !413)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_mtree.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !191, !123, !262, !325, !80, !204, !195, !23, !327, !13, !328, !114, !116, !45}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !124, !130, !133, !134, !135, !136, !162, !163, !164, !165, !169, !173, !174, !178, !182, !183, !184, !185, !190}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !125, size: 64, align: 64, offset: 1664)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !43, !45}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !131, size: 64, align: 64, offset: 1728)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !123, size: 64, align: 64, offset: 1792)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !137, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !147, !151, !155, !156, !157, !158, !159, !160, !161}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !138, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !138, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !138, file: !6, line: 46, baseType: !137, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !6, line: 47, baseType: !144, size: 64, align: 64, offset: 192)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!23, !137, !80, !80}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !138, file: !6, line: 49, baseType: !148, size: 64, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DISubroutineType(types: !150)
!150 = !{!23, !137}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !138, file: !6, line: 50, baseType: !152, size: 64, align: 64, offset: 320)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!23, !137, !43, !45}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !138, file: !6, line: 51, baseType: !148, size: 64, align: 64, offset: 384)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !138, file: !6, line: 52, baseType: !148, size: 64, align: 64, offset: 448)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !6, line: 53, baseType: !123, size: 64, align: 64, offset: 512)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !138, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !138, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !138, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !138, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !137, size: 64, align: 64, offset: 1984)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !123, size: 64, align: 64, offset: 2048)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !166, size: 64, align: 64, offset: 2176)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !4}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !170, size: 64, align: 64, offset: 2240)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!23, !4, !80, !80}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !166, size: 64, align: 64, offset: 2304)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !175, size: 64, align: 64, offset: 2368)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!23, !4, !30}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !179, size: 64, align: 64, offset: 2432)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!38, !4, !43, !45}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !166, size: 64, align: 64, offset: 2496)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !166, size: 64, align: 64, offset: 2560)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !186, size: 64, align: 64, offset: 2688)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !188)
!188 = !DISubroutineType(types: !189)
!189 = !{!80, !24, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !123, size: 64, align: 64, offset: 2752)
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree_writer", file: !1, line: 136, size: 2048, align: 64, elements: !193)
!193 = !{!194, !282, !283, !284, !285, !286, !287, !288, !289, !291, !302, !316, !317, !318, !319, !320, !321, !322, !323, !324}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "mtree_entry", scope: !192, file: !1, line: 137, baseType: !195, size: 64, align: 64)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree_entry", file: !1, line: 105, size: 2688, align: 64, elements: !197)
!197 = !{!198, !209, !210, !211, !246, !253, !254, !255, !256, !257, !258, !259, !260, !261, !264, !265, !266, !267, !268, !272, !273, !274, !275, !278, !279, !280, !281}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "rbnode", scope: !196, file: !1, line: 106, baseType: !199, size: 192, align: 64)
!199 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_node", file: !200, line: 34, size: 192, align: 64, elements: !201)
!200 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!201 = !{!202, !207}
!202 = !DIDerivedType(tag: DW_TAG_member, name: "rb_nodes", scope: !199, file: !200, line: 35, baseType: !203, size: 128, align: 64)
!203 = !DICompositeType(tag: DW_TAG_array_type, baseType: !204, size: 128, align: 64, elements: !205)
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!205 = !{!206}
!206 = !DISubrange(count: 2)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "rb_info", scope: !199, file: !200, line: 41, baseType: !208, size: 64, align: 64, offset: 128)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !196, file: !1, line: 107, baseType: !195, size: 64, align: 64, offset: 192)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "parent", scope: !196, file: !1, line: 108, baseType: !195, size: 64, align: 64, offset: 256)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "dir_info", scope: !196, file: !1, line: 109, baseType: !212, size: 64, align: 64, offset: 320)
!212 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !213, size: 64, align: 64)
!213 = !DICompositeType(tag: DW_TAG_structure_type, name: "dir_info", file: !1, line: 72, size: 384, align: 64, elements: !214)
!214 = !{!215, !238, !244, !245}
!215 = !DIDerivedType(tag: DW_TAG_member, name: "rbtree", scope: !213, file: !1, line: 73, baseType: !216, size: 128, align: 64)
!216 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree", file: !200, line: 80, size: 128, align: 64, elements: !217)
!217 = !{!218, !219}
!218 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_root", scope: !216, file: !200, line: 81, baseType: !204, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_ops", scope: !216, file: !200, line: 82, baseType: !220, size: 64, align: 64, offset: 64)
!220 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !221, size: 64, align: 64)
!221 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !222)
!222 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree_ops", file: !200, line: 75, size: 128, align: 64, elements: !223)
!223 = !{!224, !232}
!224 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_nodes", scope: !222, file: !200, line: 76, baseType: !225, size: 64, align: 64)
!225 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_nodes_fn", file: !200, line: 70, baseType: !226)
!226 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !227)
!227 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !228, size: 64, align: 64)
!228 = !DISubroutineType(types: !229)
!229 = !{!23, !230, !230}
!230 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !231, size: 64, align: 64)
!231 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !199)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_key", scope: !222, file: !200, line: 77, baseType: !233, size: 64, align: 64, offset: 64)
!233 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_key_fn", file: !200, line: 72, baseType: !234)
!234 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !235)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DISubroutineType(types: !237)
!237 = !{!23, !230, !43}
!238 = !DIDerivedType(tag: DW_TAG_member, name: "children", scope: !213, file: !1, line: 74, baseType: !239, size: 128, align: 64, offset: 128)
!239 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree_chain", file: !1, line: 64, size: 128, align: 64, elements: !240)
!240 = !{!241, !242}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !239, file: !1, line: 65, baseType: !195, size: 64, align: 64)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !239, file: !1, line: 66, baseType: !243, size: 64, align: 64, offset: 64)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "chnext", scope: !213, file: !1, line: 75, baseType: !195, size: 64, align: 64, offset: 256)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "virtual", scope: !213, file: !1, line: 76, baseType: !23, size: 32, align: 32, offset: 320)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "reg_info", scope: !196, file: !1, line: 110, baseType: !247, size: 64, align: 64, offset: 384)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DICompositeType(tag: DW_TAG_structure_type, name: "reg_info", file: !1, line: 82, size: 64, align: 32, elements: !249)
!249 = !{!250, !251}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "compute_sum", scope: !248, file: !1, line: 83, baseType: !23, size: 32, align: 32)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !248, file: !1, line: 84, baseType: !252, size: 32, align: 32, offset: 32)
!252 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !53, line: 51, baseType: !13)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "parentdir", scope: !196, file: !1, line: 112, baseType: !91, size: 192, align: 64, offset: 448)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "basename", scope: !196, file: !1, line: 113, baseType: !91, size: 192, align: 64, offset: 640)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "pathname", scope: !196, file: !1, line: 114, baseType: !91, size: 192, align: 64, offset: 832)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "symlink", scope: !196, file: !1, line: 115, baseType: !91, size: 192, align: 64, offset: 1024)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "uname", scope: !196, file: !1, line: 116, baseType: !91, size: 192, align: 64, offset: 1216)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "gname", scope: !196, file: !1, line: 117, baseType: !91, size: 192, align: 64, offset: 1408)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_text", scope: !196, file: !1, line: 118, baseType: !91, size: 192, align: 64, offset: 1600)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "nlink", scope: !196, file: !1, line: 119, baseType: !13, size: 32, align: 32, offset: 1792)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "filetype", scope: !196, file: !1, line: 120, baseType: !262, size: 32, align: 32, offset: 1824)
!262 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !263)
!263 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !196, file: !1, line: 121, baseType: !262, size: 32, align: 32, offset: 1856)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !196, file: !1, line: 122, baseType: !52, size: 64, align: 64, offset: 1920)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !196, file: !1, line: 123, baseType: !52, size: 64, align: 64, offset: 1984)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !196, file: !1, line: 124, baseType: !52, size: 64, align: 64, offset: 2048)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !196, file: !1, line: 125, baseType: !269, size: 64, align: 64, offset: 2112)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !270, line: 75, baseType: !271)
!270 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!271 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_nsec", scope: !196, file: !1, line: 126, baseType: !42, size: 64, align: 64, offset: 2176)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_set", scope: !196, file: !1, line: 127, baseType: !47, size: 64, align: 64, offset: 2240)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_clear", scope: !196, file: !1, line: 128, baseType: !47, size: 64, align: 64, offset: 2304)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "rdevmajor", scope: !196, file: !1, line: 129, baseType: !276, size: 64, align: 64, offset: 2368)
!276 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !39, line: 60, baseType: !277)
!277 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "rdevminor", scope: !196, file: !1, line: 130, baseType: !276, size: 64, align: 64, offset: 2432)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "devmajor", scope: !196, file: !1, line: 131, baseType: !276, size: 64, align: 64, offset: 2496)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "devminor", scope: !196, file: !1, line: 132, baseType: !276, size: 64, align: 64, offset: 2560)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "ino", scope: !196, file: !1, line: 133, baseType: !52, size: 64, align: 64, offset: 2624)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "root", scope: !192, file: !1, line: 138, baseType: !195, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "cur_dirent", scope: !192, file: !1, line: 139, baseType: !195, size: 64, align: 64, offset: 128)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "cur_dirstr", scope: !192, file: !1, line: 140, baseType: !91, size: 192, align: 64, offset: 192)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "file_list", scope: !192, file: !1, line: 141, baseType: !239, size: 128, align: 64, offset: 384)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "ebuf", scope: !192, file: !1, line: 143, baseType: !91, size: 192, align: 64, offset: 512)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !192, file: !1, line: 144, baseType: !91, size: 192, align: 64, offset: 704)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !192, file: !1, line: 145, baseType: !23, size: 32, align: 32, offset: 896)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !192, file: !1, line: 146, baseType: !290, size: 64, align: 64, offset: 960)
!290 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !192, file: !1, line: 160, baseType: !292, size: 448, align: 64, offset: 1024)
!292 = !DICompositeType(tag: DW_TAG_structure_type, scope: !192, file: !1, line: 151, size: 448, align: 64, elements: !293)
!293 = !{!294, !295, !296, !297, !298, !299, !300, !301}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "processing", scope: !292, file: !1, line: 152, baseType: !23, size: 32, align: 32)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !292, file: !1, line: 153, baseType: !262, size: 32, align: 32, offset: 32)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "keys", scope: !292, file: !1, line: 154, baseType: !23, size: 32, align: 32, offset: 64)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !292, file: !1, line: 155, baseType: !52, size: 64, align: 64, offset: 128)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !292, file: !1, line: 156, baseType: !52, size: 64, align: 64, offset: 192)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !292, file: !1, line: 157, baseType: !262, size: 32, align: 32, offset: 256)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_set", scope: !292, file: !1, line: 158, baseType: !47, size: 64, align: 64, offset: 320)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_clear", scope: !292, file: !1, line: 159, baseType: !47, size: 64, align: 64, offset: 384)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "acs", scope: !192, file: !1, line: 161, baseType: !303, size: 256, align: 64, offset: 1472)
!303 = !DICompositeType(tag: DW_TAG_structure_type, name: "att_counter_set", file: !1, line: 57, size: 256, align: 64, elements: !304)
!304 = !{!305, !313, !314, !315}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "uid_list", scope: !303, file: !1, line: 58, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !307, size: 64, align: 64)
!307 = !DICompositeType(tag: DW_TAG_structure_type, name: "attr_counter", file: !1, line: 50, size: 256, align: 64, elements: !308)
!308 = !{!309, !310, !311, !312}
!309 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !307, file: !1, line: 51, baseType: !306, size: 64, align: 64)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !307, file: !1, line: 52, baseType: !306, size: 64, align: 64, offset: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "m_entry", scope: !307, file: !1, line: 53, baseType: !195, size: 64, align: 64, offset: 128)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !307, file: !1, line: 54, baseType: !23, size: 32, align: 32, offset: 192)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "gid_list", scope: !303, file: !1, line: 59, baseType: !306, size: 64, align: 64, offset: 64)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "mode_list", scope: !303, file: !1, line: 60, baseType: !306, size: 64, align: 64, offset: 128)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "flags_list", scope: !303, file: !1, line: 61, baseType: !306, size: 64, align: 64, offset: 192)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "classic", scope: !192, file: !1, line: 162, baseType: !23, size: 32, align: 32, offset: 1728)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !192, file: !1, line: 163, baseType: !23, size: 32, align: 32, offset: 1760)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "compute_sum", scope: !192, file: !1, line: 166, baseType: !23, size: 32, align: 32, offset: 1792)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !192, file: !1, line: 167, baseType: !252, size: 32, align: 32, offset: 1824)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "crc_len", scope: !192, file: !1, line: 168, baseType: !290, size: 64, align: 64, offset: 1856)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "keys", scope: !192, file: !1, line: 188, baseType: !23, size: 32, align: 32, offset: 1920)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "dironly", scope: !192, file: !1, line: 221, baseType: !23, size: 32, align: 32, offset: 1952)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "indent", scope: !192, file: !1, line: 223, baseType: !23, size: 32, align: 32, offset: 1984)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "output_global_set", scope: !192, file: !1, line: 224, baseType: !23, size: 32, align: 32, offset: 2016)
!325 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !326, size: 64, align: 64)
!326 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !196)
!327 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !53, line: 134, baseType: !42)
!328 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !53, line: 135, baseType: !47)
!329 = !{!330, !331, !332, !335, !338, !339, !340, !343, !344, !348, !349, !350, !353, !354, !355, !358, !361, !364, !367, !370, !373, !376, !377, !378, !379, !382, !385, !388, !391, !395, !396, !399, !400, !401, !404, !405, !406, !409, !410}
!330 = distinct !DISubprogram(name: "archive_write_set_format_mtree", scope: !1, file: !1, line: 1432, type: !21, isLocal: false, isDefinition: true, scopeLine: 1433, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!331 = distinct !DISubprogram(name: "archive_write_set_format_mtree_classic", scope: !1, file: !1, line: 1439, type: !21, isLocal: false, isDefinition: true, scopeLine: 1440, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = distinct !DISubprogram(name: "archive_write_set_format_mtree_default", scope: !1, file: !1, line: 1392, type: !333, isLocal: true, isDefinition: true, scopeLine: 1393, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!333 = !DISubroutineType(types: !334)
!334 = !{!23, !24, !80}
!335 = distinct !DISubprogram(name: "mtree_entry_register_init", scope: !1, file: !1, line: 1930, type: !336, isLocal: true, isDefinition: true, scopeLine: 1931, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!336 = !DISubroutineType(types: !337)
!337 = !{null, !191}
!338 = distinct !DISubprogram(name: "archive_write_mtree_free", scope: !1, file: !1, line: 1261, type: !167, isLocal: true, isDefinition: true, scopeLine: 1262, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!339 = distinct !DISubprogram(name: "mtree_entry_register_free", scope: !1, file: !1, line: 1937, type: !336, isLocal: true, isDefinition: true, scopeLine: 1938, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = distinct !DISubprogram(name: "mtree_entry_free", scope: !1, file: !1, line: 868, type: !341, isLocal: true, isDefinition: true, scopeLine: 869, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!341 = !DISubroutineType(types: !342)
!342 = !{null, !195}
!343 = distinct !DISubprogram(name: "attr_counter_set_free", scope: !1, file: !1, line: 732, type: !336, isLocal: true, isDefinition: true, scopeLine: 733, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = distinct !DISubprogram(name: "attr_counter_free", scope: !1, file: !1, line: 598, type: !345, isLocal: true, isDefinition: true, scopeLine: 599, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!345 = !DISubroutineType(types: !346)
!346 = !{null, !347}
!347 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!348 = distinct !DISubprogram(name: "archive_write_mtree_options", scope: !1, file: !1, line: 1280, type: !171, isLocal: true, isDefinition: true, scopeLine: 1282, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!349 = distinct !DISubprogram(name: "archive_write_mtree_header", scope: !1, file: !1, line: 883, type: !176, isLocal: true, isDefinition: true, scopeLine: 885, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = distinct !DISubprogram(name: "mtree_entry_new", scope: !1, file: !1, line: 791, type: !351, isLocal: true, isDefinition: true, scopeLine: 793, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!351 = !DISubroutineType(types: !352)
!352 = !{!23, !4, !30, !243}
!353 = distinct !DISubprogram(name: "mtree_entry_cmp_node", scope: !1, file: !1, line: 1663, type: !228, isLocal: true, isDefinition: true, scopeLine: 1665, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!354 = distinct !DISubprogram(name: "mtree_entry_cmp_key", scope: !1, file: !1, line: 1673, type: !236, isLocal: true, isDefinition: true, scopeLine: 1674, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!355 = distinct !DISubprogram(name: "mtree_entry_setup_filenames", scope: !1, file: !1, line: 1721, type: !356, isLocal: true, isDefinition: true, scopeLine: 1723, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!356 = !DISubroutineType(types: !357)
!357 = !{!23, !4, !195, !30}
!358 = distinct !DISubprogram(name: "mtree_entry_tree_add", scope: !1, file: !1, line: 1998, type: !359, isLocal: true, isDefinition: true, scopeLine: 1999, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!359 = !DISubroutineType(types: !360)
!360 = !{!23, !4, !243}
!361 = distinct !DISubprogram(name: "mtree_entry_register_add", scope: !1, file: !1, line: 1922, type: !362, isLocal: true, isDefinition: true, scopeLine: 1923, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!362 = !DISubroutineType(types: !363)
!363 = !{null, !191, !195}
!364 = distinct !DISubprogram(name: "get_path_component", scope: !1, file: !1, line: 1975, type: !365, isLocal: true, isDefinition: true, scopeLine: 1976, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!365 = !DISubroutineType(types: !366)
!366 = !{!23, !95, !45, !80}
!367 = distinct !DISubprogram(name: "mtree_entry_find_child", scope: !1, file: !1, line: 1963, type: !368, isLocal: true, isDefinition: true, scopeLine: 1964, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!368 = !DISubroutineType(types: !369)
!369 = !{!195, !195, !80}
!370 = distinct !DISubprogram(name: "mtree_entry_create_virtual_dir", scope: !1, file: !1, line: 1888, type: !371, isLocal: true, isDefinition: true, scopeLine: 1890, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!371 = !DISubroutineType(types: !372)
!372 = !{!23, !4, !80, !243}
!373 = distinct !DISubprogram(name: "mtree_entry_exchange_same_entry", scope: !1, file: !1, line: 2190, type: !374, isLocal: true, isDefinition: true, scopeLine: 2192, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!374 = !DISubroutineType(types: !375)
!375 = !{!23, !4, !195, !195}
!376 = distinct !DISubprogram(name: "sum_init", scope: !1, file: !1, line: 1461, type: !336, isLocal: true, isDefinition: true, scopeLine: 1462, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!377 = distinct !DISubprogram(name: "archive_write_mtree_close", scope: !1, file: !1, line: 1225, type: !167, isLocal: true, isDefinition: true, scopeLine: 1226, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!378 = distinct !DISubprogram(name: "write_mtree_entry_tree", scope: !1, file: !1, line: 1108, type: !167, isLocal: true, isDefinition: true, scopeLine: 1109, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!379 = distinct !DISubprogram(name: "attr_counter_set_collect", scope: !1, file: !1, line: 655, type: !380, isLocal: true, isDefinition: true, scopeLine: 656, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!380 = !DISubroutineType(types: !381)
!381 = !{!23, !191, !195}
!382 = distinct !DISubprogram(name: "attr_counter_new", scope: !1, file: !1, line: 583, type: !383, isLocal: true, isDefinition: true, scopeLine: 584, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = !DISubroutineType(types: !384)
!384 = !{!306, !195, !306}
!385 = distinct !DISubprogram(name: "attr_counter_inc", scope: !1, file: !1, line: 614, type: !386, isLocal: true, isDefinition: true, scopeLine: 616, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!386 = !DISubroutineType(types: !387)
!387 = !{!23, !347, !306, !306, !195}
!388 = distinct !DISubprogram(name: "write_mtree_entry", scope: !1, file: !1, line: 923, type: !389, isLocal: true, isDefinition: true, scopeLine: 924, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!389 = !DISubroutineType(types: !390)
!390 = !{!23, !4, !195}
!391 = distinct !DISubprogram(name: "mtree_quote", scope: !1, file: !1, line: 349, type: !392, isLocal: true, isDefinition: true, scopeLine: 350, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!392 = !DISubroutineType(types: !393)
!393 = !{null, !394, !80}
!394 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!395 = distinct !DISubprogram(name: "get_global_set_keys", scope: !1, file: !1, line: 743, type: !380, isLocal: true, isDefinition: true, scopeLine: 744, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!396 = distinct !DISubprogram(name: "sum_write", scope: !1, file: !1, line: 1617, type: !397, isLocal: true, isDefinition: true, scopeLine: 1618, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!397 = !DISubroutineType(types: !398)
!398 = !{null, !394, !247}
!399 = distinct !DISubprogram(name: "mtree_indent", scope: !1, file: !1, line: 377, type: !336, isLocal: true, isDefinition: true, scopeLine: 378, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!400 = distinct !DISubprogram(name: "write_global", scope: !1, file: !1, line: 453, type: !336, isLocal: true, isDefinition: true, scopeLine: 454, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!401 = distinct !DISubprogram(name: "mtree_entry_add_child_tail", scope: !1, file: !1, line: 1950, type: !402, isLocal: true, isDefinition: true, scopeLine: 1952, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!402 = !DISubroutineType(types: !403)
!403 = !{!23, !195, !195}
!404 = distinct !DISubprogram(name: "write_dot_dot_entry", scope: !1, file: !1, line: 1073, type: !389, isLocal: true, isDefinition: true, scopeLine: 1074, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!405 = distinct !DISubprogram(name: "archive_write_mtree_data", scope: !1, file: !1, line: 1242, type: !180, isLocal: true, isDefinition: true, scopeLine: 1243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!406 = distinct !DISubprogram(name: "sum_update", scope: !1, file: !1, line: 1522, type: !407, isLocal: true, isDefinition: true, scopeLine: 1523, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!407 = !DISubroutineType(types: !408)
!408 = !{null, !191, !43, !45}
!409 = distinct !DISubprogram(name: "archive_write_mtree_finish_entry", scope: !1, file: !1, line: 1209, type: !167, isLocal: true, isDefinition: true, scopeLine: 1210, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!410 = distinct !DISubprogram(name: "sum_final", scope: !1, file: !1, line: 1562, type: !411, isLocal: true, isDefinition: true, scopeLine: 1563, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!411 = !DISubroutineType(types: !412)
!412 = !{null, !191, !247}
!413 = !{!414, !415, !419}
!414 = !DIGlobalVariable(name: "rb_ops", scope: !350, file: !1, line: 797, type: !221, isLocal: true, isDefinition: true, variable: %struct.archive_rb_tree_ops* @mtree_entry_new.rb_ops)
!415 = !DIGlobalVariable(name: "safe_char", scope: !0, file: !1, line: 323, type: !416, isLocal: true, isDefinition: true, variable: [256 x i8]* @safe_char)
!416 = !DICompositeType(tag: DW_TAG_array_type, baseType: !115, size: 2048, align: 8, elements: !417)
!417 = !{!418}
!418 = !DISubrange(count: 256)
!419 = !DIGlobalVariable(name: "crctab", scope: !0, file: !1, line: 268, type: !420, isLocal: true, isDefinition: true, variable: [256 x i32]* @crctab)
!420 = !DICompositeType(tag: DW_TAG_array_type, baseType: !421, size: 8192, align: 32, elements: !417)
!421 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !252)
!422 = !{i32 2, !"Dwarf Version", i32 4}
!423 = !{i32 2, !"Debug Info Version", i32 3}
!424 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!425 = !DILocalVariable(name: "_a", arg: 1, scope: !330, file: !1, line: 1432, type: !24)
!426 = !DIExpression()
!427 = !DILocation(line: 1432, column: 48, scope: !330)
!428 = !DILocation(line: 1434, column: 48, scope: !330)
!429 = !DILocation(line: 1434, column: 9, scope: !330)
!430 = !DILocation(line: 1434, column: 2, scope: !330)
!431 = !DILocalVariable(name: "_a", arg: 1, scope: !332, file: !1, line: 1392, type: !24)
!432 = !DILocation(line: 1392, column: 56, scope: !332)
!433 = !DILocalVariable(name: "fn", arg: 2, scope: !332, file: !1, line: 1392, type: !80)
!434 = !DILocation(line: 1392, column: 72, scope: !332)
!435 = !DILocalVariable(name: "a", scope: !332, file: !1, line: 1394, type: !4)
!436 = !DILocation(line: 1394, column: 24, scope: !332)
!437 = !DILocation(line: 1394, column: 52, scope: !332)
!438 = !DILocation(line: 1394, column: 28, scope: !332)
!439 = !DILocalVariable(name: "mtree", scope: !332, file: !1, line: 1395, type: !191)
!440 = !DILocation(line: 1395, column: 23, scope: !332)
!441 = !DILocation(line: 1397, column: 2, scope: !332)
!442 = !DILocalVariable(name: "magic_test", scope: !443, file: !1, line: 1397, type: !23)
!443 = distinct !DILexicalBlock(scope: !332, file: !1, line: 1397, column: 2)
!444 = !DILocation(line: 1397, column: 2, scope: !443)
!445 = !DILocation(line: 1397, column: 2, scope: !446)
!446 = !DILexicalBlockFile(scope: !443, file: !1, discriminator: 1)
!447 = !DILocation(line: 1397, column: 2, scope: !448)
!448 = !DILexicalBlockFile(scope: !449, file: !1, discriminator: 2)
!449 = distinct !DILexicalBlock(scope: !443, file: !1, line: 1397, column: 2)
!450 = !DILocation(line: 1397, column: 2, scope: !451)
!451 = !DILexicalBlockFile(scope: !443, file: !1, discriminator: 3)
!452 = !DILocation(line: 1399, column: 6, scope: !453)
!453 = distinct !DILexicalBlock(scope: !332, file: !1, line: 1399, column: 6)
!454 = !DILocation(line: 1399, column: 9, scope: !453)
!455 = !DILocation(line: 1399, column: 21, scope: !453)
!456 = !DILocation(line: 1399, column: 6, scope: !332)
!457 = !DILocation(line: 1400, column: 4, scope: !453)
!458 = !DILocation(line: 1400, column: 7, scope: !453)
!459 = !DILocation(line: 1400, column: 20, scope: !453)
!460 = !DILocation(line: 1400, column: 3, scope: !453)
!461 = !DILocation(line: 1402, column: 15, scope: !462)
!462 = distinct !DILexicalBlock(scope: !332, file: !1, line: 1402, column: 6)
!463 = !DILocation(line: 1402, column: 13, scope: !462)
!464 = !DILocation(line: 1402, column: 42, scope: !462)
!465 = !DILocation(line: 1402, column: 6, scope: !332)
!466 = !DILocation(line: 1403, column: 22, scope: !467)
!467 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1402, column: 51)
!468 = !DILocation(line: 1403, column: 25, scope: !467)
!469 = !DILocation(line: 1403, column: 3, scope: !467)
!470 = !DILocation(line: 1405, column: 3, scope: !467)
!471 = !DILocation(line: 1408, column: 2, scope: !332)
!472 = !DILocation(line: 1408, column: 9, scope: !332)
!473 = !DILocation(line: 1408, column: 21, scope: !332)
!474 = !DILocation(line: 1409, column: 2, scope: !332)
!475 = !DILocation(line: 1409, column: 9, scope: !332)
!476 = !DILocation(line: 1409, column: 15, scope: !332)
!477 = !DILocation(line: 1410, column: 11, scope: !332)
!478 = !DILocation(line: 1410, column: 18, scope: !332)
!479 = !DILocation(line: 1410, column: 2, scope: !332)
!480 = !DILocation(line: 1411, column: 2, scope: !332)
!481 = !DILocation(line: 1411, column: 9, scope: !332)
!482 = !DILocation(line: 1411, column: 14, scope: !332)
!483 = !DILocation(line: 1412, column: 2, scope: !332)
!484 = !DILocation(line: 1412, column: 9, scope: !332)
!485 = !DILocation(line: 1412, column: 17, scope: !332)
!486 = !DILocation(line: 1413, column: 2, scope: !332)
!487 = !DILocation(line: 1413, column: 9, scope: !332)
!488 = !DILocation(line: 1413, column: 16, scope: !332)
!489 = !DILocation(line: 1414, column: 2, scope: !332)
!490 = !DILocation(line: 1414, column: 2, scope: !491)
!491 = !DILexicalBlockFile(scope: !492, file: !1, discriminator: 1)
!492 = distinct !DILexicalBlock(scope: !332, file: !1, line: 1414, column: 2)
!493 = !DILocation(line: 1415, column: 2, scope: !332)
!494 = !DILocation(line: 1415, column: 2, scope: !495)
!495 = !DILexicalBlockFile(scope: !496, file: !1, discriminator: 1)
!496 = distinct !DILexicalBlock(scope: !332, file: !1, line: 1415, column: 2)
!497 = !DILocation(line: 1416, column: 28, scope: !332)
!498 = !DILocation(line: 1416, column: 2, scope: !332)
!499 = !DILocation(line: 1417, column: 19, scope: !332)
!500 = !DILocation(line: 1417, column: 2, scope: !332)
!501 = !DILocation(line: 1417, column: 5, scope: !332)
!502 = !DILocation(line: 1417, column: 17, scope: !332)
!503 = !DILocation(line: 1418, column: 2, scope: !332)
!504 = !DILocation(line: 1418, column: 5, scope: !332)
!505 = !DILocation(line: 1418, column: 17, scope: !332)
!506 = !DILocation(line: 1419, column: 2, scope: !332)
!507 = !DILocation(line: 1419, column: 5, scope: !332)
!508 = !DILocation(line: 1419, column: 17, scope: !332)
!509 = !DILocation(line: 1420, column: 2, scope: !332)
!510 = !DILocation(line: 1420, column: 5, scope: !332)
!511 = !DILocation(line: 1420, column: 20, scope: !332)
!512 = !DILocation(line: 1421, column: 2, scope: !332)
!513 = !DILocation(line: 1421, column: 5, scope: !332)
!514 = !DILocation(line: 1421, column: 25, scope: !332)
!515 = !DILocation(line: 1422, column: 2, scope: !332)
!516 = !DILocation(line: 1422, column: 5, scope: !332)
!517 = !DILocation(line: 1422, column: 18, scope: !332)
!518 = !DILocation(line: 1423, column: 2, scope: !332)
!519 = !DILocation(line: 1423, column: 5, scope: !332)
!520 = !DILocation(line: 1423, column: 23, scope: !332)
!521 = !DILocation(line: 1424, column: 2, scope: !332)
!522 = !DILocation(line: 1424, column: 5, scope: !332)
!523 = !DILocation(line: 1424, column: 25, scope: !332)
!524 = !DILocation(line: 1425, column: 2, scope: !332)
!525 = !DILocation(line: 1425, column: 5, scope: !332)
!526 = !DILocation(line: 1425, column: 13, scope: !332)
!527 = !DILocation(line: 1425, column: 28, scope: !332)
!528 = !DILocation(line: 1426, column: 2, scope: !332)
!529 = !DILocation(line: 1426, column: 5, scope: !332)
!530 = !DILocation(line: 1426, column: 13, scope: !332)
!531 = !DILocation(line: 1426, column: 33, scope: !332)
!532 = !DILocation(line: 1428, column: 2, scope: !332)
!533 = !DILocation(line: 1429, column: 1, scope: !332)
!534 = !DILocalVariable(name: "_a", arg: 1, scope: !331, file: !1, line: 1439, type: !24)
!535 = !DILocation(line: 1439, column: 56, scope: !331)
!536 = !DILocalVariable(name: "r", scope: !331, file: !1, line: 1441, type: !23)
!537 = !DILocation(line: 1441, column: 6, scope: !331)
!538 = !DILocation(line: 1443, column: 45, scope: !331)
!539 = !DILocation(line: 1443, column: 6, scope: !331)
!540 = !DILocation(line: 1443, column: 4, scope: !331)
!541 = !DILocation(line: 1445, column: 6, scope: !542)
!542 = distinct !DILexicalBlock(scope: !331, file: !1, line: 1445, column: 6)
!543 = !DILocation(line: 1445, column: 8, scope: !542)
!544 = !DILocation(line: 1445, column: 6, scope: !331)
!545 = !DILocalVariable(name: "a", scope: !546, file: !1, line: 1446, type: !4)
!546 = distinct !DILexicalBlock(scope: !542, file: !1, line: 1445, column: 23)
!547 = !DILocation(line: 1446, column: 25, scope: !546)
!548 = !DILocation(line: 1446, column: 53, scope: !546)
!549 = !DILocation(line: 1446, column: 29, scope: !546)
!550 = !DILocalVariable(name: "mtree", scope: !546, file: !1, line: 1447, type: !191)
!551 = !DILocation(line: 1447, column: 24, scope: !546)
!552 = !DILocation(line: 1449, column: 34, scope: !546)
!553 = !DILocation(line: 1449, column: 37, scope: !546)
!554 = !DILocation(line: 1449, column: 11, scope: !546)
!555 = !DILocation(line: 1449, column: 9, scope: !546)
!556 = !DILocation(line: 1452, column: 3, scope: !546)
!557 = !DILocation(line: 1452, column: 10, scope: !546)
!558 = !DILocation(line: 1452, column: 18, scope: !546)
!559 = !DILocation(line: 1455, column: 3, scope: !546)
!560 = !DILocation(line: 1455, column: 10, scope: !546)
!561 = !DILocation(line: 1455, column: 28, scope: !546)
!562 = !DILocation(line: 1456, column: 2, scope: !546)
!563 = !DILocation(line: 1457, column: 10, scope: !331)
!564 = !DILocation(line: 1457, column: 2, scope: !331)
!565 = !DILocalVariable(name: "mtree", arg: 1, scope: !335, file: !1, line: 1930, type: !191)
!566 = !DILocation(line: 1930, column: 48, scope: !335)
!567 = !DILocation(line: 1932, column: 2, scope: !335)
!568 = !DILocation(line: 1932, column: 9, scope: !335)
!569 = !DILocation(line: 1932, column: 19, scope: !335)
!570 = !DILocation(line: 1932, column: 25, scope: !335)
!571 = !DILocation(line: 1933, column: 28, scope: !335)
!572 = !DILocation(line: 1933, column: 35, scope: !335)
!573 = !DILocation(line: 1933, column: 45, scope: !335)
!574 = !DILocation(line: 1933, column: 2, scope: !335)
!575 = !DILocation(line: 1933, column: 9, scope: !335)
!576 = !DILocation(line: 1933, column: 19, scope: !335)
!577 = !DILocation(line: 1933, column: 24, scope: !335)
!578 = !DILocation(line: 1934, column: 1, scope: !335)
!579 = !DILocalVariable(name: "a", arg: 1, scope: !338, file: !1, line: 1261, type: !4)
!580 = !DILocation(line: 1261, column: 48, scope: !338)
!581 = !DILocalVariable(name: "mtree", scope: !338, file: !1, line: 1263, type: !191)
!582 = !DILocation(line: 1263, column: 23, scope: !338)
!583 = !DILocation(line: 1263, column: 30, scope: !338)
!584 = !DILocation(line: 1263, column: 33, scope: !338)
!585 = !DILocation(line: 1265, column: 6, scope: !586)
!586 = distinct !DILexicalBlock(scope: !338, file: !1, line: 1265, column: 6)
!587 = !DILocation(line: 1265, column: 12, scope: !586)
!588 = !DILocation(line: 1265, column: 6, scope: !338)
!589 = !DILocation(line: 1266, column: 3, scope: !586)
!590 = !DILocation(line: 1269, column: 28, scope: !338)
!591 = !DILocation(line: 1269, column: 2, scope: !338)
!592 = !DILocation(line: 1270, column: 23, scope: !338)
!593 = !DILocation(line: 1270, column: 30, scope: !338)
!594 = !DILocation(line: 1270, column: 2, scope: !338)
!595 = !DILocation(line: 1271, column: 23, scope: !338)
!596 = !DILocation(line: 1271, column: 30, scope: !338)
!597 = !DILocation(line: 1271, column: 2, scope: !338)
!598 = !DILocation(line: 1272, column: 23, scope: !338)
!599 = !DILocation(line: 1272, column: 30, scope: !338)
!600 = !DILocation(line: 1272, column: 2, scope: !338)
!601 = !DILocation(line: 1273, column: 24, scope: !338)
!602 = !DILocation(line: 1273, column: 2, scope: !338)
!603 = !DILocation(line: 1274, column: 7, scope: !338)
!604 = !DILocation(line: 1274, column: 2, scope: !338)
!605 = !DILocation(line: 1275, column: 2, scope: !338)
!606 = !DILocation(line: 1275, column: 5, scope: !338)
!607 = !DILocation(line: 1275, column: 17, scope: !338)
!608 = !DILocation(line: 1276, column: 2, scope: !338)
!609 = !DILocation(line: 1277, column: 1, scope: !338)
!610 = !DILocalVariable(name: "a", arg: 1, scope: !348, file: !1, line: 1280, type: !4)
!611 = !DILocation(line: 1280, column: 51, scope: !348)
!612 = !DILocalVariable(name: "key", arg: 2, scope: !348, file: !1, line: 1280, type: !80)
!613 = !DILocation(line: 1280, column: 66, scope: !348)
!614 = !DILocalVariable(name: "value", arg: 3, scope: !348, file: !1, line: 1281, type: !80)
!615 = !DILocation(line: 1281, column: 17, scope: !348)
!616 = !DILocalVariable(name: "mtree", scope: !348, file: !1, line: 1283, type: !191)
!617 = !DILocation(line: 1283, column: 23, scope: !348)
!618 = !DILocation(line: 1283, column: 30, scope: !348)
!619 = !DILocation(line: 1283, column: 33, scope: !348)
!620 = !DILocalVariable(name: "keybit", scope: !348, file: !1, line: 1284, type: !23)
!621 = !DILocation(line: 1284, column: 6, scope: !348)
!622 = !DILocation(line: 1286, column: 10, scope: !348)
!623 = !DILocation(line: 1286, column: 2, scope: !348)
!624 = !DILocation(line: 1288, column: 14, scope: !625)
!625 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1288, column: 7)
!626 = distinct !DILexicalBlock(scope: !348, file: !1, line: 1286, column: 18)
!627 = !DILocation(line: 1288, column: 7, scope: !625)
!628 = !DILocation(line: 1288, column: 26, scope: !625)
!629 = !DILocation(line: 1288, column: 7, scope: !626)
!630 = !DILocation(line: 1289, column: 11, scope: !625)
!631 = !DILocation(line: 1289, column: 4, scope: !625)
!632 = !DILocation(line: 1290, column: 3, scope: !626)
!633 = !DILocation(line: 1292, column: 14, scope: !634)
!634 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1292, column: 7)
!635 = !DILocation(line: 1292, column: 7, scope: !634)
!636 = !DILocation(line: 1292, column: 28, scope: !634)
!637 = !DILocation(line: 1292, column: 7, scope: !626)
!638 = !DILocation(line: 1293, column: 11, scope: !634)
!639 = !DILocation(line: 1293, column: 4, scope: !634)
!640 = !DILocation(line: 1294, column: 3, scope: !626)
!641 = !DILocation(line: 1296, column: 14, scope: !642)
!642 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1296, column: 7)
!643 = !DILocation(line: 1296, column: 7, scope: !642)
!644 = !DILocation(line: 1296, column: 29, scope: !642)
!645 = !DILocation(line: 1296, column: 7, scope: !626)
!646 = !DILocation(line: 1297, column: 11, scope: !642)
!647 = !DILocation(line: 1297, column: 4, scope: !642)
!648 = !DILocation(line: 1298, column: 19, scope: !649)
!649 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1298, column: 12)
!650 = !DILocation(line: 1298, column: 12, scope: !649)
!651 = !DILocation(line: 1298, column: 35, scope: !649)
!652 = !DILocation(line: 1298, column: 12, scope: !642)
!653 = !DILocation(line: 1299, column: 22, scope: !654)
!654 = distinct !DILexicalBlock(scope: !649, file: !1, line: 1298, column: 41)
!655 = !DILocation(line: 1299, column: 28, scope: !654)
!656 = !DILocation(line: 1299, column: 21, scope: !654)
!657 = !DILocation(line: 1299, column: 4, scope: !654)
!658 = !DILocation(line: 1299, column: 11, scope: !654)
!659 = !DILocation(line: 1299, column: 19, scope: !654)
!660 = !DILocation(line: 1300, column: 4, scope: !654)
!661 = !DILocation(line: 1302, column: 3, scope: !626)
!662 = !DILocation(line: 1304, column: 14, scope: !663)
!663 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1304, column: 7)
!664 = !DILocation(line: 1304, column: 7, scope: !663)
!665 = !DILocation(line: 1304, column: 28, scope: !663)
!666 = !DILocation(line: 1304, column: 7, scope: !626)
!667 = !DILocation(line: 1305, column: 11, scope: !663)
!668 = !DILocation(line: 1305, column: 4, scope: !663)
!669 = !DILocation(line: 1306, column: 3, scope: !626)
!670 = !DILocation(line: 1308, column: 14, scope: !671)
!671 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1308, column: 7)
!672 = !DILocation(line: 1308, column: 7, scope: !671)
!673 = !DILocation(line: 1308, column: 26, scope: !671)
!674 = !DILocation(line: 1308, column: 7, scope: !626)
!675 = !DILocation(line: 1309, column: 11, scope: !671)
!676 = !DILocation(line: 1309, column: 4, scope: !671)
!677 = !DILocation(line: 1310, column: 19, scope: !678)
!678 = distinct !DILexicalBlock(scope: !671, file: !1, line: 1310, column: 12)
!679 = !DILocation(line: 1310, column: 12, scope: !678)
!680 = !DILocation(line: 1310, column: 33, scope: !678)
!681 = !DILocation(line: 1310, column: 12, scope: !671)
!682 = !DILocation(line: 1311, column: 11, scope: !678)
!683 = !DILocation(line: 1311, column: 4, scope: !678)
!684 = !DILocation(line: 1312, column: 3, scope: !626)
!685 = !DILocation(line: 1314, column: 14, scope: !686)
!686 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1314, column: 7)
!687 = !DILocation(line: 1314, column: 7, scope: !686)
!688 = !DILocation(line: 1314, column: 29, scope: !686)
!689 = !DILocation(line: 1314, column: 7, scope: !626)
!690 = !DILocation(line: 1315, column: 21, scope: !691)
!691 = distinct !DILexicalBlock(scope: !686, file: !1, line: 1314, column: 35)
!692 = !DILocation(line: 1315, column: 27, scope: !691)
!693 = !DILocation(line: 1315, column: 20, scope: !691)
!694 = !DILocation(line: 1315, column: 4, scope: !691)
!695 = !DILocation(line: 1315, column: 11, scope: !691)
!696 = !DILocation(line: 1315, column: 18, scope: !691)
!697 = !DILocation(line: 1316, column: 4, scope: !691)
!698 = !DILocation(line: 1317, column: 21, scope: !699)
!699 = distinct !DILexicalBlock(scope: !686, file: !1, line: 1317, column: 14)
!700 = !DILocation(line: 1317, column: 14, scope: !699)
!701 = !DILocation(line: 1317, column: 35, scope: !699)
!702 = !DILocation(line: 1317, column: 14, scope: !686)
!703 = !DILocation(line: 1318, column: 11, scope: !704)
!704 = distinct !DILexicalBlock(scope: !699, file: !1, line: 1317, column: 41)
!705 = !DILocation(line: 1319, column: 3, scope: !704)
!706 = !DILocation(line: 1320, column: 3, scope: !626)
!707 = !DILocation(line: 1322, column: 14, scope: !708)
!708 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1322, column: 7)
!709 = !DILocation(line: 1322, column: 7, scope: !708)
!710 = !DILocation(line: 1322, column: 27, scope: !708)
!711 = !DILocation(line: 1322, column: 7, scope: !626)
!712 = !DILocation(line: 1323, column: 11, scope: !708)
!713 = !DILocation(line: 1323, column: 4, scope: !708)
!714 = !DILocation(line: 1324, column: 3, scope: !626)
!715 = !DILocation(line: 1326, column: 14, scope: !716)
!716 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1326, column: 7)
!717 = !DILocation(line: 1326, column: 7, scope: !716)
!718 = !DILocation(line: 1326, column: 26, scope: !716)
!719 = !DILocation(line: 1326, column: 31, scope: !716)
!720 = !DILocation(line: 1327, column: 14, scope: !716)
!721 = !DILocation(line: 1327, column: 7, scope: !716)
!722 = !DILocation(line: 1327, column: 32, scope: !716)
!723 = !DILocation(line: 1326, column: 7, scope: !724)
!724 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 1)
!725 = !DILocation(line: 1328, column: 11, scope: !716)
!726 = !DILocation(line: 1328, column: 4, scope: !716)
!727 = !DILocation(line: 1329, column: 14, scope: !728)
!728 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1329, column: 7)
!729 = !DILocation(line: 1329, column: 7, scope: !728)
!730 = !DILocation(line: 1329, column: 27, scope: !728)
!731 = !DILocation(line: 1329, column: 7, scope: !626)
!732 = !DILocation(line: 1330, column: 11, scope: !728)
!733 = !DILocation(line: 1330, column: 4, scope: !728)
!734 = !DILocation(line: 1331, column: 3, scope: !626)
!735 = !DILocation(line: 1333, column: 14, scope: !736)
!736 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1333, column: 7)
!737 = !DILocation(line: 1333, column: 7, scope: !736)
!738 = !DILocation(line: 1333, column: 28, scope: !736)
!739 = !DILocation(line: 1333, column: 7, scope: !626)
!740 = !DILocation(line: 1334, column: 11, scope: !736)
!741 = !DILocation(line: 1334, column: 4, scope: !736)
!742 = !DILocation(line: 1335, column: 3, scope: !626)
!743 = !DILocation(line: 1337, column: 14, scope: !744)
!744 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1337, column: 7)
!745 = !DILocation(line: 1337, column: 7, scope: !744)
!746 = !DILocation(line: 1337, column: 32, scope: !744)
!747 = !DILocation(line: 1337, column: 7, scope: !626)
!748 = !DILocation(line: 1338, column: 11, scope: !749)
!749 = distinct !DILexicalBlock(scope: !744, file: !1, line: 1337, column: 38)
!750 = !DILocation(line: 1339, column: 3, scope: !749)
!751 = !DILocation(line: 1339, column: 21, scope: !752)
!752 = !DILexicalBlockFile(scope: !753, file: !1, discriminator: 1)
!753 = distinct !DILexicalBlock(scope: !744, file: !1, line: 1339, column: 14)
!754 = !DILocation(line: 1339, column: 14, scope: !752)
!755 = !DILocation(line: 1339, column: 45, scope: !752)
!756 = !DILocation(line: 1339, column: 50, scope: !752)
!757 = !DILocation(line: 1340, column: 14, scope: !753)
!758 = !DILocation(line: 1340, column: 7, scope: !753)
!759 = !DILocation(line: 1340, column: 29, scope: !753)
!760 = !DILocation(line: 1340, column: 34, scope: !753)
!761 = !DILocation(line: 1341, column: 14, scope: !753)
!762 = !DILocation(line: 1341, column: 7, scope: !753)
!763 = !DILocation(line: 1341, column: 35, scope: !753)
!764 = !DILocation(line: 1339, column: 14, scope: !765)
!765 = !DILexicalBlockFile(scope: !744, file: !1, discriminator: 2)
!766 = !DILocation(line: 1342, column: 11, scope: !753)
!767 = !DILocation(line: 1342, column: 4, scope: !753)
!768 = !DILocation(line: 1343, column: 3, scope: !626)
!769 = !DILocation(line: 1345, column: 14, scope: !770)
!770 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1345, column: 7)
!771 = !DILocation(line: 1345, column: 7, scope: !770)
!772 = !DILocation(line: 1345, column: 27, scope: !770)
!773 = !DILocation(line: 1345, column: 32, scope: !770)
!774 = !DILocation(line: 1346, column: 14, scope: !770)
!775 = !DILocation(line: 1346, column: 7, scope: !770)
!776 = !DILocation(line: 1346, column: 33, scope: !770)
!777 = !DILocation(line: 1345, column: 7, scope: !724)
!778 = !DILocation(line: 1347, column: 11, scope: !770)
!779 = !DILocation(line: 1347, column: 4, scope: !770)
!780 = !DILocation(line: 1348, column: 14, scope: !781)
!781 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1348, column: 7)
!782 = !DILocation(line: 1348, column: 7, scope: !781)
!783 = !DILocation(line: 1348, column: 29, scope: !781)
!784 = !DILocation(line: 1348, column: 34, scope: !781)
!785 = !DILocation(line: 1349, column: 14, scope: !781)
!786 = !DILocation(line: 1349, column: 7, scope: !781)
!787 = !DILocation(line: 1349, column: 35, scope: !781)
!788 = !DILocation(line: 1348, column: 7, scope: !724)
!789 = !DILocation(line: 1350, column: 11, scope: !781)
!790 = !DILocation(line: 1350, column: 4, scope: !781)
!791 = !DILocation(line: 1351, column: 14, scope: !792)
!792 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1351, column: 7)
!793 = !DILocation(line: 1351, column: 7, scope: !792)
!794 = !DILocation(line: 1351, column: 29, scope: !792)
!795 = !DILocation(line: 1351, column: 34, scope: !792)
!796 = !DILocation(line: 1352, column: 14, scope: !792)
!797 = !DILocation(line: 1352, column: 7, scope: !792)
!798 = !DILocation(line: 1352, column: 35, scope: !792)
!799 = !DILocation(line: 1351, column: 7, scope: !724)
!800 = !DILocation(line: 1353, column: 11, scope: !792)
!801 = !DILocation(line: 1353, column: 4, scope: !792)
!802 = !DILocation(line: 1354, column: 14, scope: !803)
!803 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1354, column: 7)
!804 = !DILocation(line: 1354, column: 7, scope: !803)
!805 = !DILocation(line: 1354, column: 29, scope: !803)
!806 = !DILocation(line: 1354, column: 34, scope: !803)
!807 = !DILocation(line: 1355, column: 14, scope: !803)
!808 = !DILocation(line: 1355, column: 7, scope: !803)
!809 = !DILocation(line: 1355, column: 35, scope: !803)
!810 = !DILocation(line: 1354, column: 7, scope: !724)
!811 = !DILocation(line: 1356, column: 11, scope: !803)
!812 = !DILocation(line: 1356, column: 4, scope: !803)
!813 = !DILocation(line: 1357, column: 14, scope: !814)
!814 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1357, column: 7)
!815 = !DILocation(line: 1357, column: 7, scope: !814)
!816 = !DILocation(line: 1357, column: 27, scope: !814)
!817 = !DILocation(line: 1357, column: 7, scope: !626)
!818 = !DILocation(line: 1358, column: 11, scope: !814)
!819 = !DILocation(line: 1358, column: 4, scope: !814)
!820 = !DILocation(line: 1359, column: 3, scope: !626)
!821 = !DILocation(line: 1361, column: 14, scope: !822)
!822 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1361, column: 7)
!823 = !DILocation(line: 1361, column: 7, scope: !822)
!824 = !DILocation(line: 1361, column: 27, scope: !822)
!825 = !DILocation(line: 1361, column: 7, scope: !626)
!826 = !DILocation(line: 1362, column: 11, scope: !822)
!827 = !DILocation(line: 1362, column: 4, scope: !822)
!828 = !DILocation(line: 1363, column: 19, scope: !829)
!829 = distinct !DILexicalBlock(scope: !822, file: !1, line: 1363, column: 12)
!830 = !DILocation(line: 1363, column: 12, scope: !829)
!831 = !DILocation(line: 1363, column: 32, scope: !829)
!832 = !DILocation(line: 1363, column: 12, scope: !822)
!833 = !DILocation(line: 1364, column: 11, scope: !829)
!834 = !DILocation(line: 1364, column: 4, scope: !829)
!835 = !DILocation(line: 1365, column: 3, scope: !626)
!836 = !DILocation(line: 1367, column: 14, scope: !837)
!837 = distinct !DILexicalBlock(scope: !626, file: !1, line: 1367, column: 7)
!838 = !DILocation(line: 1367, column: 7, scope: !837)
!839 = !DILocation(line: 1367, column: 26, scope: !837)
!840 = !DILocation(line: 1367, column: 7, scope: !626)
!841 = !DILocation(line: 1368, column: 11, scope: !837)
!842 = !DILocation(line: 1368, column: 4, scope: !837)
!843 = !DILocation(line: 1369, column: 19, scope: !844)
!844 = distinct !DILexicalBlock(scope: !837, file: !1, line: 1369, column: 12)
!845 = !DILocation(line: 1369, column: 12, scope: !844)
!846 = !DILocation(line: 1369, column: 33, scope: !844)
!847 = !DILocation(line: 1369, column: 12, scope: !837)
!848 = !DILocation(line: 1370, column: 11, scope: !844)
!849 = !DILocation(line: 1370, column: 4, scope: !844)
!850 = !DILocation(line: 1371, column: 19, scope: !851)
!851 = distinct !DILexicalBlock(scope: !844, file: !1, line: 1371, column: 12)
!852 = !DILocation(line: 1371, column: 12, scope: !851)
!853 = !DILocation(line: 1371, column: 35, scope: !851)
!854 = !DILocation(line: 1371, column: 12, scope: !844)
!855 = !DILocation(line: 1372, column: 32, scope: !856)
!856 = distinct !DILexicalBlock(scope: !851, file: !1, line: 1371, column: 41)
!857 = !DILocation(line: 1372, column: 38, scope: !856)
!858 = !DILocation(line: 1372, column: 31, scope: !856)
!859 = !DILocation(line: 1372, column: 4, scope: !856)
!860 = !DILocation(line: 1372, column: 11, scope: !856)
!861 = !DILocation(line: 1372, column: 29, scope: !856)
!862 = !DILocation(line: 1373, column: 4, scope: !856)
!863 = !DILocation(line: 1375, column: 3, scope: !626)
!864 = !DILocation(line: 1377, column: 6, scope: !865)
!865 = distinct !DILexicalBlock(scope: !348, file: !1, line: 1377, column: 6)
!866 = !DILocation(line: 1377, column: 13, scope: !865)
!867 = !DILocation(line: 1377, column: 6, scope: !348)
!868 = !DILocation(line: 1378, column: 7, scope: !869)
!869 = distinct !DILexicalBlock(scope: !870, file: !1, line: 1378, column: 7)
!870 = distinct !DILexicalBlock(scope: !865, file: !1, line: 1377, column: 19)
!871 = !DILocation(line: 1378, column: 13, scope: !869)
!872 = !DILocation(line: 1378, column: 7, scope: !870)
!873 = !DILocation(line: 1379, column: 19, scope: !869)
!874 = !DILocation(line: 1379, column: 4, scope: !869)
!875 = !DILocation(line: 1379, column: 11, scope: !869)
!876 = !DILocation(line: 1379, column: 16, scope: !869)
!877 = !DILocation(line: 1381, column: 20, scope: !869)
!878 = !DILocation(line: 1381, column: 19, scope: !869)
!879 = !DILocation(line: 1381, column: 4, scope: !869)
!880 = !DILocation(line: 1381, column: 11, scope: !869)
!881 = !DILocation(line: 1381, column: 16, scope: !869)
!882 = !DILocation(line: 1382, column: 3, scope: !870)
!883 = !DILocation(line: 1388, column: 2, scope: !348)
!884 = !DILocation(line: 1389, column: 1, scope: !348)
!885 = !DILocalVariable(name: "a", arg: 1, scope: !349, file: !1, line: 883, type: !4)
!886 = !DILocation(line: 883, column: 50, scope: !349)
!887 = !DILocalVariable(name: "entry", arg: 2, scope: !349, file: !1, line: 884, type: !30)
!888 = !DILocation(line: 884, column: 27, scope: !349)
!889 = !DILocalVariable(name: "mtree", scope: !349, file: !1, line: 886, type: !191)
!890 = !DILocation(line: 886, column: 23, scope: !349)
!891 = !DILocation(line: 886, column: 30, scope: !349)
!892 = !DILocation(line: 886, column: 33, scope: !349)
!893 = !DILocalVariable(name: "mtree_entry", scope: !349, file: !1, line: 887, type: !195)
!894 = !DILocation(line: 887, column: 22, scope: !349)
!895 = !DILocalVariable(name: "r", scope: !349, file: !1, line: 888, type: !23)
!896 = !DILocation(line: 888, column: 6, scope: !349)
!897 = !DILocalVariable(name: "r2", scope: !349, file: !1, line: 888, type: !23)
!898 = !DILocation(line: 888, column: 9, scope: !349)
!899 = !DILocation(line: 890, column: 6, scope: !900)
!900 = distinct !DILexicalBlock(scope: !349, file: !1, line: 890, column: 6)
!901 = !DILocation(line: 890, column: 13, scope: !900)
!902 = !DILocation(line: 890, column: 6, scope: !349)
!903 = !DILocation(line: 891, column: 3, scope: !904)
!904 = distinct !DILexicalBlock(scope: !900, file: !1, line: 890, column: 20)
!905 = !DILocation(line: 891, column: 10, scope: !904)
!906 = !DILocation(line: 891, column: 16, scope: !904)
!907 = !DILocation(line: 892, column: 19, scope: !904)
!908 = !DILocation(line: 892, column: 26, scope: !904)
!909 = !DILocation(line: 892, column: 3, scope: !904)
!910 = !DILocation(line: 893, column: 8, scope: !911)
!911 = distinct !DILexicalBlock(scope: !904, file: !1, line: 893, column: 7)
!912 = !DILocation(line: 893, column: 15, scope: !911)
!913 = !DILocation(line: 893, column: 20, scope: !911)
!914 = !DILocation(line: 893, column: 32, scope: !911)
!915 = !DILocation(line: 893, column: 7, scope: !904)
!916 = !DILocation(line: 894, column: 4, scope: !911)
!917 = !DILocation(line: 894, column: 11, scope: !911)
!918 = !DILocation(line: 894, column: 29, scope: !911)
!919 = !DILocation(line: 895, column: 2, scope: !904)
!920 = !DILocation(line: 897, column: 52, scope: !349)
!921 = !DILocation(line: 897, column: 33, scope: !349)
!922 = !DILocation(line: 897, column: 2, scope: !349)
!923 = !DILocation(line: 897, column: 9, scope: !349)
!924 = !DILocation(line: 897, column: 31, scope: !349)
!925 = !DILocation(line: 900, column: 6, scope: !926)
!926 = distinct !DILexicalBlock(scope: !349, file: !1, line: 900, column: 6)
!927 = !DILocation(line: 900, column: 13, scope: !926)
!928 = !DILocation(line: 900, column: 21, scope: !926)
!929 = !DILocation(line: 900, column: 47, scope: !930)
!930 = !DILexicalBlockFile(scope: !926, file: !1, discriminator: 1)
!931 = !DILocation(line: 900, column: 24, scope: !930)
!932 = !DILocation(line: 900, column: 54, scope: !930)
!933 = !DILocation(line: 900, column: 6, scope: !930)
!934 = !DILocation(line: 901, column: 3, scope: !926)
!935 = !DILocation(line: 903, column: 23, scope: !349)
!936 = !DILocation(line: 903, column: 26, scope: !349)
!937 = !DILocation(line: 903, column: 7, scope: !349)
!938 = !DILocation(line: 903, column: 5, scope: !349)
!939 = !DILocation(line: 904, column: 6, scope: !940)
!940 = distinct !DILexicalBlock(scope: !349, file: !1, line: 904, column: 6)
!941 = !DILocation(line: 904, column: 9, scope: !940)
!942 = !DILocation(line: 904, column: 6, scope: !349)
!943 = !DILocation(line: 905, column: 11, scope: !940)
!944 = !DILocation(line: 905, column: 3, scope: !940)
!945 = !DILocation(line: 906, column: 27, scope: !349)
!946 = !DILocation(line: 906, column: 6, scope: !349)
!947 = !DILocation(line: 906, column: 4, scope: !349)
!948 = !DILocation(line: 907, column: 6, scope: !949)
!949 = distinct !DILexicalBlock(scope: !349, file: !1, line: 907, column: 6)
!950 = !DILocation(line: 907, column: 8, scope: !949)
!951 = !DILocation(line: 907, column: 6, scope: !349)
!952 = !DILocation(line: 908, column: 20, scope: !953)
!953 = distinct !DILexicalBlock(scope: !949, file: !1, line: 907, column: 24)
!954 = !DILocation(line: 908, column: 3, scope: !953)
!955 = !DILocation(line: 909, column: 11, scope: !953)
!956 = !DILocation(line: 909, column: 3, scope: !953)
!957 = !DILocation(line: 911, column: 23, scope: !349)
!958 = !DILocation(line: 911, column: 2, scope: !349)
!959 = !DILocation(line: 911, column: 9, scope: !349)
!960 = !DILocation(line: 911, column: 21, scope: !349)
!961 = !DILocation(line: 916, column: 6, scope: !962)
!962 = distinct !DILexicalBlock(scope: !349, file: !1, line: 916, column: 6)
!963 = !DILocation(line: 916, column: 19, scope: !962)
!964 = !DILocation(line: 916, column: 6, scope: !349)
!965 = !DILocation(line: 917, column: 12, scope: !962)
!966 = !DILocation(line: 917, column: 3, scope: !962)
!967 = !DILocation(line: 919, column: 10, scope: !349)
!968 = !DILocation(line: 919, column: 2, scope: !349)
!969 = !DILocation(line: 920, column: 1, scope: !349)
!970 = !DILocalVariable(name: "a", arg: 1, scope: !377, file: !1, line: 1225, type: !4)
!971 = !DILocation(line: 1225, column: 49, scope: !377)
!972 = !DILocalVariable(name: "mtree", scope: !377, file: !1, line: 1227, type: !191)
!973 = !DILocation(line: 1227, column: 23, scope: !377)
!974 = !DILocation(line: 1227, column: 30, scope: !377)
!975 = !DILocation(line: 1227, column: 33, scope: !377)
!976 = !DILocalVariable(name: "ret", scope: !377, file: !1, line: 1228, type: !23)
!977 = !DILocation(line: 1228, column: 6, scope: !377)
!978 = !DILocation(line: 1230, column: 6, scope: !979)
!979 = distinct !DILexicalBlock(scope: !377, file: !1, line: 1230, column: 6)
!980 = !DILocation(line: 1230, column: 13, scope: !979)
!981 = !DILocation(line: 1230, column: 18, scope: !979)
!982 = !DILocation(line: 1230, column: 6, scope: !377)
!983 = !DILocation(line: 1231, column: 32, scope: !984)
!984 = distinct !DILexicalBlock(scope: !979, file: !1, line: 1230, column: 27)
!985 = !DILocation(line: 1231, column: 9, scope: !984)
!986 = !DILocation(line: 1231, column: 7, scope: !984)
!987 = !DILocation(line: 1232, column: 7, scope: !988)
!988 = distinct !DILexicalBlock(scope: !984, file: !1, line: 1232, column: 7)
!989 = !DILocation(line: 1232, column: 11, scope: !988)
!990 = !DILocation(line: 1232, column: 7, scope: !984)
!991 = !DILocation(line: 1233, column: 4, scope: !988)
!992 = !DILocation(line: 1234, column: 2, scope: !984)
!993 = !DILocation(line: 1236, column: 41, scope: !377)
!994 = !DILocation(line: 1236, column: 44, scope: !377)
!995 = !DILocation(line: 1236, column: 2, scope: !377)
!996 = !DILocation(line: 1238, column: 32, scope: !377)
!997 = !DILocation(line: 1238, column: 35, scope: !377)
!998 = !DILocation(line: 1238, column: 42, scope: !377)
!999 = !DILocation(line: 1238, column: 46, scope: !377)
!1000 = !DILocation(line: 1238, column: 49, scope: !377)
!1001 = !DILocation(line: 1238, column: 56, scope: !377)
!1002 = !DILocation(line: 1238, column: 60, scope: !377)
!1003 = !DILocation(line: 1238, column: 9, scope: !377)
!1004 = !DILocation(line: 1238, column: 2, scope: !377)
!1005 = !DILocation(line: 1239, column: 1, scope: !377)
!1006 = !DILocalVariable(name: "a", arg: 1, scope: !405, file: !1, line: 1242, type: !4)
!1007 = !DILocation(line: 1242, column: 48, scope: !405)
!1008 = !DILocalVariable(name: "buff", arg: 2, scope: !405, file: !1, line: 1242, type: !43)
!1009 = !DILocation(line: 1242, column: 63, scope: !405)
!1010 = !DILocalVariable(name: "n", arg: 3, scope: !405, file: !1, line: 1242, type: !45)
!1011 = !DILocation(line: 1242, column: 76, scope: !405)
!1012 = !DILocalVariable(name: "mtree", scope: !405, file: !1, line: 1244, type: !191)
!1013 = !DILocation(line: 1244, column: 23, scope: !405)
!1014 = !DILocation(line: 1244, column: 30, scope: !405)
!1015 = !DILocation(line: 1244, column: 33, scope: !405)
!1016 = !DILocation(line: 1246, column: 6, scope: !1017)
!1017 = distinct !DILexicalBlock(scope: !405, file: !1, line: 1246, column: 6)
!1018 = !DILocation(line: 1246, column: 10, scope: !1017)
!1019 = !DILocation(line: 1246, column: 17, scope: !1017)
!1020 = !DILocation(line: 1246, column: 8, scope: !1017)
!1021 = !DILocation(line: 1246, column: 6, scope: !405)
!1022 = !DILocation(line: 1247, column: 15, scope: !1017)
!1023 = !DILocation(line: 1247, column: 22, scope: !1017)
!1024 = !DILocation(line: 1247, column: 5, scope: !1017)
!1025 = !DILocation(line: 1247, column: 3, scope: !1017)
!1026 = !DILocation(line: 1248, column: 34, scope: !405)
!1027 = !DILocation(line: 1248, column: 2, scope: !405)
!1028 = !DILocation(line: 1248, column: 9, scope: !405)
!1029 = !DILocation(line: 1248, column: 31, scope: !405)
!1030 = !DILocation(line: 1251, column: 6, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !405, file: !1, line: 1251, column: 6)
!1032 = !DILocation(line: 1251, column: 13, scope: !1031)
!1033 = !DILocation(line: 1251, column: 25, scope: !1031)
!1034 = !DILocation(line: 1251, column: 6, scope: !405)
!1035 = !DILocation(line: 1252, column: 11, scope: !1031)
!1036 = !DILocation(line: 1252, column: 3, scope: !1031)
!1037 = !DILocation(line: 1254, column: 6, scope: !1038)
!1038 = distinct !DILexicalBlock(scope: !405, file: !1, line: 1254, column: 6)
!1039 = !DILocation(line: 1254, column: 13, scope: !1038)
!1040 = !DILocation(line: 1254, column: 26, scope: !1038)
!1041 = !DILocation(line: 1254, column: 35, scope: !1038)
!1042 = !DILocation(line: 1254, column: 6, scope: !405)
!1043 = !DILocation(line: 1255, column: 14, scope: !1038)
!1044 = !DILocation(line: 1255, column: 21, scope: !1038)
!1045 = !DILocation(line: 1255, column: 27, scope: !1038)
!1046 = !DILocation(line: 1255, column: 3, scope: !1038)
!1047 = !DILocation(line: 1257, column: 10, scope: !405)
!1048 = !DILocation(line: 1257, column: 2, scope: !405)
!1049 = !DILocation(line: 1258, column: 1, scope: !405)
!1050 = !DILocalVariable(name: "a", arg: 1, scope: !409, file: !1, line: 1209, type: !4)
!1051 = !DILocation(line: 1209, column: 56, scope: !409)
!1052 = !DILocalVariable(name: "mtree", scope: !409, file: !1, line: 1211, type: !191)
!1053 = !DILocation(line: 1211, column: 23, scope: !409)
!1054 = !DILocation(line: 1211, column: 31, scope: !409)
!1055 = !DILocation(line: 1211, column: 34, scope: !409)
!1056 = !DILocalVariable(name: "me", scope: !409, file: !1, line: 1212, type: !195)
!1057 = !DILocation(line: 1212, column: 22, scope: !409)
!1058 = !DILocation(line: 1214, column: 12, scope: !1059)
!1059 = distinct !DILexicalBlock(scope: !409, file: !1, line: 1214, column: 6)
!1060 = !DILocation(line: 1214, column: 19, scope: !1059)
!1061 = !DILocation(line: 1214, column: 10, scope: !1059)
!1062 = !DILocation(line: 1214, column: 32, scope: !1059)
!1063 = !DILocation(line: 1214, column: 6, scope: !409)
!1064 = !DILocation(line: 1215, column: 3, scope: !1059)
!1065 = !DILocation(line: 1216, column: 2, scope: !409)
!1066 = !DILocation(line: 1216, column: 9, scope: !409)
!1067 = !DILocation(line: 1216, column: 21, scope: !409)
!1068 = !DILocation(line: 1218, column: 6, scope: !1069)
!1069 = distinct !DILexicalBlock(scope: !409, file: !1, line: 1218, column: 6)
!1070 = !DILocation(line: 1218, column: 10, scope: !1069)
!1071 = !DILocation(line: 1218, column: 6, scope: !409)
!1072 = !DILocation(line: 1219, column: 13, scope: !1069)
!1073 = !DILocation(line: 1219, column: 20, scope: !1069)
!1074 = !DILocation(line: 1219, column: 24, scope: !1069)
!1075 = !DILocation(line: 1219, column: 3, scope: !1069)
!1076 = !DILocation(line: 1221, column: 2, scope: !409)
!1077 = !DILocation(line: 1222, column: 1, scope: !409)
!1078 = !DILocalVariable(name: "mtree", arg: 1, scope: !339, file: !1, line: 1937, type: !191)
!1079 = !DILocation(line: 1937, column: 48, scope: !339)
!1080 = !DILocalVariable(name: "file", scope: !339, file: !1, line: 1939, type: !195)
!1081 = !DILocation(line: 1939, column: 22, scope: !339)
!1082 = !DILocalVariable(name: "file_next", scope: !339, file: !1, line: 1939, type: !195)
!1083 = !DILocation(line: 1939, column: 29, scope: !339)
!1084 = !DILocation(line: 1941, column: 9, scope: !339)
!1085 = !DILocation(line: 1941, column: 16, scope: !339)
!1086 = !DILocation(line: 1941, column: 26, scope: !339)
!1087 = !DILocation(line: 1941, column: 7, scope: !339)
!1088 = !DILocation(line: 1942, column: 2, scope: !339)
!1089 = !DILocation(line: 1942, column: 9, scope: !1090)
!1090 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!1091 = !DILocation(line: 1942, column: 14, scope: !1090)
!1092 = !DILocation(line: 1942, column: 2, scope: !1090)
!1093 = !DILocation(line: 1943, column: 15, scope: !1094)
!1094 = distinct !DILexicalBlock(scope: !339, file: !1, line: 1942, column: 23)
!1095 = !DILocation(line: 1943, column: 21, scope: !1094)
!1096 = !DILocation(line: 1943, column: 13, scope: !1094)
!1097 = !DILocation(line: 1944, column: 20, scope: !1094)
!1098 = !DILocation(line: 1944, column: 3, scope: !1094)
!1099 = !DILocation(line: 1945, column: 10, scope: !1094)
!1100 = !DILocation(line: 1945, column: 8, scope: !1094)
!1101 = !DILocation(line: 1942, column: 2, scope: !1102)
!1102 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 2)
!1103 = !DILocation(line: 1947, column: 1, scope: !339)
!1104 = !DILocalVariable(name: "mtree", arg: 1, scope: !343, file: !1, line: 732, type: !191)
!1105 = !DILocation(line: 732, column: 44, scope: !343)
!1106 = !DILocalVariable(name: "acs", scope: !343, file: !1, line: 734, type: !1107)
!1107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!1108 = !DILocation(line: 734, column: 26, scope: !343)
!1109 = !DILocation(line: 734, column: 33, scope: !343)
!1110 = !DILocation(line: 734, column: 40, scope: !343)
!1111 = !DILocation(line: 736, column: 21, scope: !343)
!1112 = !DILocation(line: 736, column: 26, scope: !343)
!1113 = !DILocation(line: 736, column: 2, scope: !343)
!1114 = !DILocation(line: 737, column: 21, scope: !343)
!1115 = !DILocation(line: 737, column: 26, scope: !343)
!1116 = !DILocation(line: 737, column: 2, scope: !343)
!1117 = !DILocation(line: 738, column: 21, scope: !343)
!1118 = !DILocation(line: 738, column: 26, scope: !343)
!1119 = !DILocation(line: 738, column: 2, scope: !343)
!1120 = !DILocation(line: 739, column: 21, scope: !343)
!1121 = !DILocation(line: 739, column: 26, scope: !343)
!1122 = !DILocation(line: 739, column: 2, scope: !343)
!1123 = !DILocation(line: 740, column: 1, scope: !343)
!1124 = !DILocalVariable(name: "me", arg: 1, scope: !340, file: !1, line: 868, type: !195)
!1125 = !DILocation(line: 868, column: 38, scope: !340)
!1126 = !DILocation(line: 870, column: 23, scope: !340)
!1127 = !DILocation(line: 870, column: 27, scope: !340)
!1128 = !DILocation(line: 870, column: 2, scope: !340)
!1129 = !DILocation(line: 871, column: 23, scope: !340)
!1130 = !DILocation(line: 871, column: 27, scope: !340)
!1131 = !DILocation(line: 871, column: 2, scope: !340)
!1132 = !DILocation(line: 872, column: 23, scope: !340)
!1133 = !DILocation(line: 872, column: 27, scope: !340)
!1134 = !DILocation(line: 872, column: 2, scope: !340)
!1135 = !DILocation(line: 873, column: 23, scope: !340)
!1136 = !DILocation(line: 873, column: 27, scope: !340)
!1137 = !DILocation(line: 873, column: 2, scope: !340)
!1138 = !DILocation(line: 874, column: 23, scope: !340)
!1139 = !DILocation(line: 874, column: 27, scope: !340)
!1140 = !DILocation(line: 874, column: 2, scope: !340)
!1141 = !DILocation(line: 875, column: 23, scope: !340)
!1142 = !DILocation(line: 875, column: 27, scope: !340)
!1143 = !DILocation(line: 875, column: 2, scope: !340)
!1144 = !DILocation(line: 876, column: 23, scope: !340)
!1145 = !DILocation(line: 876, column: 27, scope: !340)
!1146 = !DILocation(line: 876, column: 2, scope: !340)
!1147 = !DILocation(line: 877, column: 7, scope: !340)
!1148 = !DILocation(line: 877, column: 11, scope: !340)
!1149 = !DILocation(line: 877, column: 2, scope: !340)
!1150 = !DILocation(line: 878, column: 7, scope: !340)
!1151 = !DILocation(line: 878, column: 11, scope: !340)
!1152 = !DILocation(line: 878, column: 2, scope: !340)
!1153 = !DILocation(line: 879, column: 7, scope: !340)
!1154 = !DILocation(line: 879, column: 2, scope: !340)
!1155 = !DILocation(line: 880, column: 1, scope: !340)
!1156 = !DILocalVariable(name: "top", arg: 1, scope: !344, file: !1, line: 598, type: !347)
!1157 = !DILocation(line: 598, column: 41, scope: !344)
!1158 = !DILocalVariable(name: "ac", scope: !344, file: !1, line: 600, type: !306)
!1159 = !DILocation(line: 600, column: 23, scope: !344)
!1160 = !DILocalVariable(name: "tac", scope: !344, file: !1, line: 600, type: !306)
!1161 = !DILocation(line: 600, column: 28, scope: !344)
!1162 = !DILocation(line: 602, column: 7, scope: !1163)
!1163 = distinct !DILexicalBlock(scope: !344, file: !1, line: 602, column: 6)
!1164 = !DILocation(line: 602, column: 6, scope: !1163)
!1165 = !DILocation(line: 602, column: 11, scope: !1163)
!1166 = !DILocation(line: 602, column: 6, scope: !344)
!1167 = !DILocation(line: 603, column: 3, scope: !1163)
!1168 = !DILocation(line: 604, column: 8, scope: !344)
!1169 = !DILocation(line: 604, column: 7, scope: !344)
!1170 = !DILocation(line: 604, column: 5, scope: !344)
!1171 = !DILocation(line: 605, column: 9, scope: !344)
!1172 = !DILocation(line: 605, column: 16, scope: !1173)
!1173 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!1174 = !DILocation(line: 605, column: 19, scope: !1173)
!1175 = !DILocation(line: 605, column: 9, scope: !1173)
!1176 = !DILocation(line: 606, column: 9, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !344, file: !1, line: 605, column: 28)
!1178 = !DILocation(line: 606, column: 13, scope: !1177)
!1179 = !DILocation(line: 606, column: 7, scope: !1177)
!1180 = !DILocation(line: 607, column: 8, scope: !1177)
!1181 = !DILocation(line: 607, column: 3, scope: !1177)
!1182 = !DILocation(line: 608, column: 8, scope: !1177)
!1183 = !DILocation(line: 608, column: 6, scope: !1177)
!1184 = !DILocation(line: 605, column: 9, scope: !1185)
!1185 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 2)
!1186 = !DILocation(line: 610, column: 3, scope: !344)
!1187 = !DILocation(line: 610, column: 7, scope: !344)
!1188 = !DILocation(line: 611, column: 1, scope: !344)
!1189 = !DILocation(line: 611, column: 1, scope: !1173)
!1190 = !DILocalVariable(name: "a", arg: 1, scope: !350, file: !1, line: 791, type: !4)
!1191 = !DILocation(line: 791, column: 39, scope: !350)
!1192 = !DILocalVariable(name: "entry", arg: 2, scope: !350, file: !1, line: 791, type: !30)
!1193 = !DILocation(line: 791, column: 64, scope: !350)
!1194 = !DILocalVariable(name: "m_entry", arg: 3, scope: !350, file: !1, line: 792, type: !243)
!1195 = !DILocation(line: 792, column: 26, scope: !350)
!1196 = !DILocalVariable(name: "me", scope: !350, file: !1, line: 794, type: !195)
!1197 = !DILocation(line: 794, column: 22, scope: !350)
!1198 = !DILocalVariable(name: "s", scope: !350, file: !1, line: 795, type: !80)
!1199 = !DILocation(line: 795, column: 14, scope: !350)
!1200 = !DILocalVariable(name: "r", scope: !350, file: !1, line: 796, type: !23)
!1201 = !DILocation(line: 796, column: 6, scope: !350)
!1202 = !DILocation(line: 801, column: 7, scope: !350)
!1203 = !DILocation(line: 801, column: 5, scope: !350)
!1204 = !DILocation(line: 802, column: 6, scope: !1205)
!1205 = distinct !DILexicalBlock(scope: !350, file: !1, line: 802, column: 6)
!1206 = !DILocation(line: 802, column: 9, scope: !1205)
!1207 = !DILocation(line: 802, column: 6, scope: !350)
!1208 = !DILocation(line: 803, column: 22, scope: !1209)
!1209 = distinct !DILexicalBlock(scope: !1205, file: !1, line: 802, column: 18)
!1210 = !DILocation(line: 803, column: 25, scope: !1209)
!1211 = !DILocation(line: 803, column: 3, scope: !1209)
!1212 = !DILocation(line: 805, column: 4, scope: !1209)
!1213 = !DILocation(line: 805, column: 12, scope: !1209)
!1214 = !DILocation(line: 806, column: 3, scope: !1209)
!1215 = !DILocation(line: 809, column: 34, scope: !350)
!1216 = !DILocation(line: 809, column: 37, scope: !350)
!1217 = !DILocation(line: 809, column: 41, scope: !350)
!1218 = !DILocation(line: 809, column: 6, scope: !350)
!1219 = !DILocation(line: 809, column: 4, scope: !350)
!1220 = !DILocation(line: 810, column: 6, scope: !1221)
!1221 = distinct !DILexicalBlock(scope: !350, file: !1, line: 810, column: 6)
!1222 = !DILocation(line: 810, column: 8, scope: !1221)
!1223 = !DILocation(line: 810, column: 6, scope: !350)
!1224 = !DILocation(line: 811, column: 20, scope: !1225)
!1225 = distinct !DILexicalBlock(scope: !1221, file: !1, line: 810, column: 24)
!1226 = !DILocation(line: 811, column: 3, scope: !1225)
!1227 = !DILocation(line: 812, column: 4, scope: !1225)
!1228 = !DILocation(line: 812, column: 12, scope: !1225)
!1229 = !DILocation(line: 813, column: 11, scope: !1225)
!1230 = !DILocation(line: 813, column: 3, scope: !1225)
!1231 = !DILocation(line: 816, column: 33, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !350, file: !1, line: 816, column: 6)
!1233 = !DILocation(line: 816, column: 11, scope: !1232)
!1234 = !DILocation(line: 816, column: 9, scope: !1232)
!1235 = !DILocation(line: 816, column: 41, scope: !1232)
!1236 = !DILocation(line: 816, column: 6, scope: !350)
!1237 = !DILocation(line: 817, column: 3, scope: !1232)
!1238 = !DILocation(line: 817, column: 3, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 1)
!1240 = !DILocation(line: 817, column: 3, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 2)
!1242 = !DILocation(line: 817, column: 3, scope: !1243)
!1243 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 3)
!1244 = !DILocation(line: 818, column: 34, scope: !350)
!1245 = !DILocation(line: 818, column: 14, scope: !350)
!1246 = !DILocation(line: 818, column: 2, scope: !350)
!1247 = !DILocation(line: 818, column: 6, scope: !350)
!1248 = !DILocation(line: 818, column: 12, scope: !350)
!1249 = !DILocation(line: 819, column: 40, scope: !350)
!1250 = !DILocation(line: 819, column: 17, scope: !350)
!1251 = !DILocation(line: 819, column: 2, scope: !350)
!1252 = !DILocation(line: 819, column: 6, scope: !350)
!1253 = !DILocation(line: 819, column: 15, scope: !350)
!1254 = !DILocation(line: 820, column: 32, scope: !350)
!1255 = !DILocation(line: 820, column: 13, scope: !350)
!1256 = !DILocation(line: 820, column: 39, scope: !350)
!1257 = !DILocation(line: 820, column: 2, scope: !350)
!1258 = !DILocation(line: 820, column: 6, scope: !350)
!1259 = !DILocation(line: 820, column: 11, scope: !350)
!1260 = !DILocation(line: 821, column: 30, scope: !350)
!1261 = !DILocation(line: 821, column: 12, scope: !350)
!1262 = !DILocation(line: 821, column: 2, scope: !350)
!1263 = !DILocation(line: 821, column: 6, scope: !350)
!1264 = !DILocation(line: 821, column: 10, scope: !350)
!1265 = !DILocation(line: 822, column: 30, scope: !350)
!1266 = !DILocation(line: 822, column: 12, scope: !350)
!1267 = !DILocation(line: 822, column: 2, scope: !350)
!1268 = !DILocation(line: 822, column: 6, scope: !350)
!1269 = !DILocation(line: 822, column: 10, scope: !350)
!1270 = !DILocation(line: 823, column: 31, scope: !1271)
!1271 = distinct !DILexicalBlock(scope: !350, file: !1, line: 823, column: 6)
!1272 = !DILocation(line: 823, column: 11, scope: !1271)
!1273 = !DILocation(line: 823, column: 9, scope: !1271)
!1274 = !DILocation(line: 823, column: 39, scope: !1271)
!1275 = !DILocation(line: 823, column: 6, scope: !350)
!1276 = !DILocation(line: 824, column: 3, scope: !1271)
!1277 = !DILocation(line: 824, column: 3, scope: !1278)
!1278 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 1)
!1279 = !DILocation(line: 824, column: 3, scope: !1280)
!1280 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 2)
!1281 = !DILocation(line: 824, column: 3, scope: !1282)
!1282 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 3)
!1283 = !DILocation(line: 825, column: 31, scope: !1284)
!1284 = distinct !DILexicalBlock(scope: !350, file: !1, line: 825, column: 6)
!1285 = !DILocation(line: 825, column: 11, scope: !1284)
!1286 = !DILocation(line: 825, column: 9, scope: !1284)
!1287 = !DILocation(line: 825, column: 39, scope: !1284)
!1288 = !DILocation(line: 825, column: 6, scope: !350)
!1289 = !DILocation(line: 826, column: 3, scope: !1284)
!1290 = !DILocation(line: 826, column: 3, scope: !1291)
!1291 = !DILexicalBlockFile(scope: !1284, file: !1, discriminator: 1)
!1292 = !DILocation(line: 826, column: 3, scope: !1293)
!1293 = !DILexicalBlockFile(scope: !1284, file: !1, discriminator: 2)
!1294 = !DILocation(line: 826, column: 3, scope: !1295)
!1295 = !DILexicalBlockFile(scope: !1284, file: !1, discriminator: 3)
!1296 = !DILocation(line: 827, column: 37, scope: !1297)
!1297 = distinct !DILexicalBlock(scope: !350, file: !1, line: 827, column: 6)
!1298 = !DILocation(line: 827, column: 11, scope: !1297)
!1299 = !DILocation(line: 827, column: 9, scope: !1297)
!1300 = !DILocation(line: 827, column: 45, scope: !1297)
!1301 = !DILocation(line: 827, column: 6, scope: !350)
!1302 = !DILocation(line: 828, column: 3, scope: !1297)
!1303 = !DILocation(line: 828, column: 3, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1297, file: !1, discriminator: 1)
!1305 = !DILocation(line: 828, column: 3, scope: !1306)
!1306 = !DILexicalBlockFile(scope: !1297, file: !1, discriminator: 2)
!1307 = !DILocation(line: 828, column: 3, scope: !1308)
!1308 = !DILexicalBlockFile(scope: !1297, file: !1, discriminator: 3)
!1309 = !DILocation(line: 829, column: 23, scope: !350)
!1310 = !DILocation(line: 829, column: 31, scope: !350)
!1311 = !DILocation(line: 829, column: 35, scope: !350)
!1312 = !DILocation(line: 829, column: 48, scope: !350)
!1313 = !DILocation(line: 829, column: 52, scope: !350)
!1314 = !DILocation(line: 829, column: 2, scope: !350)
!1315 = !DILocation(line: 830, column: 34, scope: !350)
!1316 = !DILocation(line: 830, column: 14, scope: !350)
!1317 = !DILocation(line: 830, column: 2, scope: !350)
!1318 = !DILocation(line: 830, column: 6, scope: !350)
!1319 = !DILocation(line: 830, column: 12, scope: !350)
!1320 = !DILocation(line: 831, column: 44, scope: !350)
!1321 = !DILocation(line: 831, column: 19, scope: !350)
!1322 = !DILocation(line: 831, column: 2, scope: !350)
!1323 = !DILocation(line: 831, column: 6, scope: !350)
!1324 = !DILocation(line: 831, column: 17, scope: !350)
!1325 = !DILocation(line: 832, column: 42, scope: !350)
!1326 = !DILocation(line: 832, column: 18, scope: !350)
!1327 = !DILocation(line: 832, column: 2, scope: !350)
!1328 = !DILocation(line: 832, column: 6, scope: !350)
!1329 = !DILocation(line: 832, column: 16, scope: !350)
!1330 = !DILocation(line: 833, column: 42, scope: !350)
!1331 = !DILocation(line: 833, column: 18, scope: !350)
!1332 = !DILocation(line: 833, column: 2, scope: !350)
!1333 = !DILocation(line: 833, column: 6, scope: !350)
!1334 = !DILocation(line: 833, column: 16, scope: !350)
!1335 = !DILocation(line: 834, column: 40, scope: !350)
!1336 = !DILocation(line: 834, column: 17, scope: !350)
!1337 = !DILocation(line: 834, column: 2, scope: !350)
!1338 = !DILocation(line: 834, column: 6, scope: !350)
!1339 = !DILocation(line: 834, column: 15, scope: !350)
!1340 = !DILocation(line: 835, column: 40, scope: !350)
!1341 = !DILocation(line: 835, column: 17, scope: !350)
!1342 = !DILocation(line: 835, column: 2, scope: !350)
!1343 = !DILocation(line: 835, column: 6, scope: !350)
!1344 = !DILocation(line: 835, column: 15, scope: !350)
!1345 = !DILocation(line: 836, column: 30, scope: !350)
!1346 = !DILocation(line: 836, column: 12, scope: !350)
!1347 = !DILocation(line: 836, column: 2, scope: !350)
!1348 = !DILocation(line: 836, column: 6, scope: !350)
!1349 = !DILocation(line: 836, column: 10, scope: !350)
!1350 = !DILocation(line: 837, column: 32, scope: !350)
!1351 = !DILocation(line: 837, column: 13, scope: !350)
!1352 = !DILocation(line: 837, column: 2, scope: !350)
!1353 = !DILocation(line: 837, column: 6, scope: !350)
!1354 = !DILocation(line: 837, column: 11, scope: !350)
!1355 = !DILocation(line: 838, column: 6, scope: !1356)
!1356 = distinct !DILexicalBlock(scope: !350, file: !1, line: 838, column: 6)
!1357 = !DILocation(line: 838, column: 10, scope: !1356)
!1358 = !DILocation(line: 838, column: 19, scope: !1356)
!1359 = !DILocation(line: 838, column: 6, scope: !350)
!1360 = !DILocation(line: 839, column: 18, scope: !1361)
!1361 = distinct !DILexicalBlock(scope: !1356, file: !1, line: 838, column: 32)
!1362 = !DILocation(line: 839, column: 3, scope: !1361)
!1363 = !DILocation(line: 839, column: 7, scope: !1361)
!1364 = !DILocation(line: 839, column: 16, scope: !1361)
!1365 = !DILocation(line: 840, column: 7, scope: !1366)
!1366 = distinct !DILexicalBlock(scope: !1361, file: !1, line: 840, column: 7)
!1367 = !DILocation(line: 840, column: 11, scope: !1366)
!1368 = !DILocation(line: 840, column: 20, scope: !1366)
!1369 = !DILocation(line: 840, column: 7, scope: !1361)
!1370 = !DILocation(line: 841, column: 21, scope: !1371)
!1371 = distinct !DILexicalBlock(scope: !1366, file: !1, line: 840, column: 29)
!1372 = !DILocation(line: 841, column: 4, scope: !1371)
!1373 = !DILocation(line: 842, column: 23, scope: !1371)
!1374 = !DILocation(line: 842, column: 26, scope: !1371)
!1375 = !DILocation(line: 842, column: 4, scope: !1371)
!1376 = !DILocation(line: 844, column: 5, scope: !1371)
!1377 = !DILocation(line: 844, column: 13, scope: !1371)
!1378 = !DILocation(line: 845, column: 4, scope: !1371)
!1379 = !DILocation(line: 847, column: 27, scope: !1361)
!1380 = !DILocation(line: 847, column: 31, scope: !1361)
!1381 = !DILocation(line: 847, column: 41, scope: !1361)
!1382 = !DILocation(line: 847, column: 3, scope: !1361)
!1383 = !DILocation(line: 848, column: 3, scope: !1361)
!1384 = !DILocation(line: 848, column: 7, scope: !1361)
!1385 = !DILocation(line: 848, column: 17, scope: !1361)
!1386 = !DILocation(line: 848, column: 26, scope: !1361)
!1387 = !DILocation(line: 848, column: 32, scope: !1361)
!1388 = !DILocation(line: 849, column: 35, scope: !1361)
!1389 = !DILocation(line: 849, column: 39, scope: !1361)
!1390 = !DILocation(line: 849, column: 49, scope: !1361)
!1391 = !DILocation(line: 849, column: 58, scope: !1361)
!1392 = !DILocation(line: 849, column: 3, scope: !1361)
!1393 = !DILocation(line: 849, column: 7, scope: !1361)
!1394 = !DILocation(line: 849, column: 17, scope: !1361)
!1395 = !DILocation(line: 849, column: 26, scope: !1361)
!1396 = !DILocation(line: 849, column: 31, scope: !1361)
!1397 = !DILocation(line: 850, column: 3, scope: !1361)
!1398 = !DILocation(line: 850, column: 7, scope: !1361)
!1399 = !DILocation(line: 850, column: 17, scope: !1361)
!1400 = !DILocation(line: 850, column: 24, scope: !1361)
!1401 = !DILocation(line: 851, column: 2, scope: !1361)
!1402 = !DILocation(line: 851, column: 13, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1404, file: !1, discriminator: 1)
!1404 = distinct !DILexicalBlock(scope: !1356, file: !1, line: 851, column: 13)
!1405 = !DILocation(line: 851, column: 17, scope: !1403)
!1406 = !DILocation(line: 851, column: 26, scope: !1403)
!1407 = !DILocation(line: 852, column: 18, scope: !1408)
!1408 = distinct !DILexicalBlock(scope: !1404, file: !1, line: 851, column: 39)
!1409 = !DILocation(line: 852, column: 3, scope: !1408)
!1410 = !DILocation(line: 852, column: 7, scope: !1408)
!1411 = !DILocation(line: 852, column: 16, scope: !1408)
!1412 = !DILocation(line: 853, column: 7, scope: !1413)
!1413 = distinct !DILexicalBlock(scope: !1408, file: !1, line: 853, column: 7)
!1414 = !DILocation(line: 853, column: 11, scope: !1413)
!1415 = !DILocation(line: 853, column: 20, scope: !1413)
!1416 = !DILocation(line: 853, column: 7, scope: !1408)
!1417 = !DILocation(line: 854, column: 21, scope: !1418)
!1418 = distinct !DILexicalBlock(scope: !1413, file: !1, line: 853, column: 29)
!1419 = !DILocation(line: 854, column: 4, scope: !1418)
!1420 = !DILocation(line: 855, column: 23, scope: !1418)
!1421 = !DILocation(line: 855, column: 26, scope: !1418)
!1422 = !DILocation(line: 855, column: 4, scope: !1418)
!1423 = !DILocation(line: 857, column: 5, scope: !1418)
!1424 = !DILocation(line: 857, column: 13, scope: !1418)
!1425 = !DILocation(line: 858, column: 4, scope: !1418)
!1426 = !DILocation(line: 860, column: 3, scope: !1408)
!1427 = !DILocation(line: 860, column: 7, scope: !1408)
!1428 = !DILocation(line: 860, column: 17, scope: !1408)
!1429 = !DILocation(line: 860, column: 29, scope: !1408)
!1430 = !DILocation(line: 861, column: 2, scope: !1408)
!1431 = !DILocation(line: 863, column: 13, scope: !350)
!1432 = !DILocation(line: 863, column: 3, scope: !350)
!1433 = !DILocation(line: 863, column: 11, scope: !350)
!1434 = !DILocation(line: 864, column: 2, scope: !350)
!1435 = !DILocation(line: 865, column: 1, scope: !350)
!1436 = !DILocalVariable(name: "a", arg: 1, scope: !358, file: !1, line: 1998, type: !4)
!1437 = !DILocation(line: 1998, column: 44, scope: !358)
!1438 = !DILocalVariable(name: "filep", arg: 2, scope: !358, file: !1, line: 1998, type: !243)
!1439 = !DILocation(line: 1998, column: 68, scope: !358)
!1440 = !DILocalVariable(name: "name", scope: !358, file: !1, line: 2005, type: !1441)
!1441 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 2048, align: 8, elements: !417)
!1442 = !DILocation(line: 2005, column: 7, scope: !358)
!1443 = !DILocalVariable(name: "mtree", scope: !358, file: !1, line: 2007, type: !191)
!1444 = !DILocation(line: 2007, column: 23, scope: !358)
!1445 = !DILocation(line: 2007, column: 54, scope: !358)
!1446 = !DILocation(line: 2007, column: 57, scope: !358)
!1447 = !DILocation(line: 2007, column: 31, scope: !358)
!1448 = !DILocalVariable(name: "dent", scope: !358, file: !1, line: 2008, type: !195)
!1449 = !DILocation(line: 2008, column: 22, scope: !358)
!1450 = !DILocalVariable(name: "file", scope: !358, file: !1, line: 2008, type: !195)
!1451 = !DILocation(line: 2008, column: 29, scope: !358)
!1452 = !DILocalVariable(name: "np", scope: !358, file: !1, line: 2008, type: !195)
!1453 = !DILocation(line: 2008, column: 36, scope: !358)
!1454 = !DILocalVariable(name: "fn", scope: !358, file: !1, line: 2009, type: !80)
!1455 = !DILocation(line: 2009, column: 14, scope: !358)
!1456 = !DILocalVariable(name: "p", scope: !358, file: !1, line: 2009, type: !80)
!1457 = !DILocation(line: 2009, column: 19, scope: !358)
!1458 = !DILocalVariable(name: "l", scope: !358, file: !1, line: 2010, type: !23)
!1459 = !DILocation(line: 2010, column: 6, scope: !358)
!1460 = !DILocalVariable(name: "r", scope: !358, file: !1, line: 2010, type: !23)
!1461 = !DILocation(line: 2010, column: 9, scope: !358)
!1462 = !DILocation(line: 2012, column: 10, scope: !358)
!1463 = !DILocation(line: 2012, column: 9, scope: !358)
!1464 = !DILocation(line: 2012, column: 7, scope: !358)
!1465 = !DILocation(line: 2013, column: 6, scope: !1466)
!1466 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2013, column: 6)
!1467 = !DILocation(line: 2013, column: 12, scope: !1466)
!1468 = !DILocation(line: 2013, column: 22, scope: !1466)
!1469 = !DILocation(line: 2013, column: 29, scope: !1466)
!1470 = !DILocation(line: 2013, column: 34, scope: !1466)
!1471 = !DILocation(line: 2013, column: 37, scope: !1472)
!1472 = !DILexicalBlockFile(scope: !1466, file: !1, discriminator: 1)
!1473 = !DILocation(line: 2013, column: 43, scope: !1472)
!1474 = !DILocation(line: 2013, column: 52, scope: !1472)
!1475 = !DILocation(line: 2013, column: 59, scope: !1472)
!1476 = !DILocation(line: 2013, column: 64, scope: !1472)
!1477 = !DILocation(line: 2014, column: 6, scope: !1466)
!1478 = !DILocation(line: 2014, column: 12, scope: !1466)
!1479 = !DILocation(line: 2014, column: 21, scope: !1466)
!1480 = !DILocation(line: 2014, column: 26, scope: !1466)
!1481 = !DILocation(line: 2013, column: 6, scope: !1482)
!1482 = !DILexicalBlockFile(scope: !358, file: !1, discriminator: 2)
!1483 = !DILocation(line: 2015, column: 18, scope: !1484)
!1484 = distinct !DILexicalBlock(scope: !1466, file: !1, line: 2014, column: 34)
!1485 = !DILocation(line: 2015, column: 3, scope: !1484)
!1486 = !DILocation(line: 2015, column: 9, scope: !1484)
!1487 = !DILocation(line: 2015, column: 16, scope: !1484)
!1488 = !DILocation(line: 2016, column: 7, scope: !1489)
!1489 = distinct !DILexicalBlock(scope: !1484, file: !1, line: 2016, column: 7)
!1490 = !DILocation(line: 2016, column: 14, scope: !1489)
!1491 = !DILocation(line: 2016, column: 19, scope: !1489)
!1492 = !DILocation(line: 2016, column: 7, scope: !1484)
!1493 = !DILocation(line: 2017, column: 9, scope: !1494)
!1494 = distinct !DILexicalBlock(scope: !1489, file: !1, line: 2016, column: 28)
!1495 = !DILocation(line: 2017, column: 16, scope: !1494)
!1496 = !DILocation(line: 2017, column: 7, scope: !1494)
!1497 = !DILocation(line: 2018, column: 4, scope: !1494)
!1498 = !DILocation(line: 2020, column: 17, scope: !1484)
!1499 = !DILocation(line: 2020, column: 3, scope: !1484)
!1500 = !DILocation(line: 2020, column: 10, scope: !1484)
!1501 = !DILocation(line: 2020, column: 15, scope: !1484)
!1502 = !DILocation(line: 2021, column: 28, scope: !1484)
!1503 = !DILocation(line: 2021, column: 35, scope: !1484)
!1504 = !DILocation(line: 2021, column: 3, scope: !1484)
!1505 = !DILocation(line: 2022, column: 3, scope: !1484)
!1506 = !DILocation(line: 2025, column: 6, scope: !1507)
!1507 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2025, column: 6)
!1508 = !DILocation(line: 2025, column: 12, scope: !1507)
!1509 = !DILocation(line: 2025, column: 22, scope: !1507)
!1510 = !DILocation(line: 2025, column: 29, scope: !1507)
!1511 = !DILocation(line: 2025, column: 6, scope: !358)
!1512 = !DILocation(line: 2026, column: 22, scope: !1513)
!1513 = distinct !DILexicalBlock(scope: !1507, file: !1, line: 2025, column: 35)
!1514 = !DILocation(line: 2026, column: 25, scope: !1513)
!1515 = !DILocation(line: 2029, column: 7, scope: !1513)
!1516 = !DILocation(line: 2029, column: 13, scope: !1513)
!1517 = !DILocation(line: 2029, column: 22, scope: !1513)
!1518 = !DILocation(line: 2026, column: 3, scope: !1513)
!1519 = !DILocation(line: 2030, column: 3, scope: !1513)
!1520 = !DILocation(line: 2033, column: 11, scope: !358)
!1521 = !DILocation(line: 2033, column: 17, scope: !358)
!1522 = !DILocation(line: 2033, column: 27, scope: !358)
!1523 = !DILocation(line: 2033, column: 9, scope: !358)
!1524 = !DILocation(line: 2033, column: 5, scope: !358)
!1525 = !DILocation(line: 2040, column: 6, scope: !1526)
!1526 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2040, column: 6)
!1527 = !DILocation(line: 2041, column: 11, scope: !1526)
!1528 = !DILocation(line: 2041, column: 8, scope: !1526)
!1529 = !DILocation(line: 2041, column: 46, scope: !1526)
!1530 = !DILocation(line: 2042, column: 13, scope: !1526)
!1531 = !DILocation(line: 2042, column: 20, scope: !1526)
!1532 = !DILocation(line: 2042, column: 31, scope: !1526)
!1533 = !DILocation(line: 2042, column: 34, scope: !1526)
!1534 = !DILocation(line: 2042, column: 6, scope: !1526)
!1535 = !DILocation(line: 2042, column: 38, scope: !1526)
!1536 = !DILocation(line: 2040, column: 6, scope: !1537)
!1537 = !DILexicalBlockFile(scope: !358, file: !1, discriminator: 1)
!1538 = !DILocation(line: 2044, column: 9, scope: !1539)
!1539 = distinct !DILexicalBlock(scope: !1540, file: !1, line: 2043, column: 7)
!1540 = distinct !DILexicalBlock(scope: !1526, file: !1, line: 2042, column: 44)
!1541 = !DILocation(line: 2044, column: 16, scope: !1539)
!1542 = !DILocation(line: 2044, column: 28, scope: !1539)
!1543 = !DILocation(line: 2044, column: 38, scope: !1539)
!1544 = !DILocation(line: 2045, column: 33, scope: !1539)
!1545 = !DILocation(line: 2045, column: 7, scope: !1539)
!1546 = !DILocation(line: 2043, column: 8, scope: !1539)
!1547 = !DILocation(line: 2043, column: 7, scope: !1540)
!1548 = !DILocation(line: 2048, column: 10, scope: !1549)
!1549 = distinct !DILexicalBlock(scope: !1539, file: !1, line: 2045, column: 40)
!1550 = !DILocation(line: 2048, column: 17, scope: !1549)
!1551 = !DILocation(line: 2048, column: 29, scope: !1549)
!1552 = !DILocation(line: 2048, column: 39, scope: !1549)
!1553 = !DILocation(line: 2049, column: 8, scope: !1549)
!1554 = !DILocation(line: 2049, column: 14, scope: !1549)
!1555 = !DILocation(line: 2049, column: 23, scope: !1549)
!1556 = !DILocation(line: 2047, column: 31, scope: !1549)
!1557 = !DILocation(line: 2047, column: 9, scope: !1549)
!1558 = !DILocation(line: 2047, column: 7, scope: !1549)
!1559 = !DILocation(line: 2050, column: 4, scope: !1549)
!1560 = !DILocation(line: 2052, column: 18, scope: !1540)
!1561 = !DILocation(line: 2052, column: 25, scope: !1540)
!1562 = !DILocation(line: 2052, column: 3, scope: !1540)
!1563 = !DILocation(line: 2052, column: 9, scope: !1540)
!1564 = !DILocation(line: 2052, column: 16, scope: !1540)
!1565 = !DILocation(line: 2053, column: 28, scope: !1540)
!1566 = !DILocation(line: 2053, column: 35, scope: !1540)
!1567 = !DILocation(line: 2053, column: 3, scope: !1540)
!1568 = !DILocation(line: 2054, column: 3, scope: !1540)
!1569 = !DILocation(line: 2057, column: 9, scope: !358)
!1570 = !DILocation(line: 2057, column: 16, scope: !358)
!1571 = !DILocation(line: 2057, column: 7, scope: !358)
!1572 = !DILocation(line: 2058, column: 2, scope: !358)
!1573 = !DILocation(line: 2059, column: 26, scope: !1574)
!1574 = distinct !DILexicalBlock(scope: !1575, file: !1, line: 2058, column: 11)
!1575 = distinct !DILexicalBlock(scope: !1576, file: !1, line: 2058, column: 2)
!1576 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2058, column: 2)
!1577 = !DILocation(line: 2059, column: 46, scope: !1574)
!1578 = !DILocation(line: 2059, column: 7, scope: !1574)
!1579 = !DILocation(line: 2059, column: 5, scope: !1574)
!1580 = !DILocation(line: 2060, column: 7, scope: !1581)
!1581 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2060, column: 7)
!1582 = !DILocation(line: 2060, column: 9, scope: !1581)
!1583 = !DILocation(line: 2060, column: 7, scope: !1574)
!1584 = !DILocation(line: 2061, column: 7, scope: !1585)
!1585 = distinct !DILexicalBlock(scope: !1581, file: !1, line: 2060, column: 15)
!1586 = !DILocation(line: 2062, column: 4, scope: !1585)
!1587 = !DILocation(line: 2064, column: 7, scope: !1588)
!1588 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2064, column: 7)
!1589 = !DILocation(line: 2064, column: 9, scope: !1588)
!1590 = !DILocation(line: 2064, column: 7, scope: !1574)
!1591 = !DILocation(line: 2065, column: 23, scope: !1592)
!1592 = distinct !DILexicalBlock(scope: !1588, file: !1, line: 2064, column: 14)
!1593 = !DILocation(line: 2065, column: 26, scope: !1592)
!1594 = !DILocation(line: 2065, column: 4, scope: !1592)
!1595 = !DILocation(line: 2068, column: 4, scope: !1592)
!1596 = !DILocation(line: 2070, column: 7, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2070, column: 7)
!1598 = !DILocation(line: 2070, column: 9, scope: !1597)
!1599 = !DILocation(line: 2070, column: 14, scope: !1597)
!1600 = !DILocation(line: 2070, column: 17, scope: !1601)
!1601 = !DILexicalBlockFile(scope: !1597, file: !1, discriminator: 1)
!1602 = !DILocation(line: 2070, column: 25, scope: !1601)
!1603 = !DILocation(line: 2070, column: 32, scope: !1601)
!1604 = !DILocation(line: 2070, column: 35, scope: !1605)
!1605 = !DILexicalBlockFile(scope: !1597, file: !1, discriminator: 2)
!1606 = !DILocation(line: 2070, column: 40, scope: !1605)
!1607 = !DILocation(line: 2070, column: 48, scope: !1605)
!1608 = !DILocation(line: 2071, column: 7, scope: !1597)
!1609 = !DILocation(line: 2071, column: 15, scope: !1597)
!1610 = !DILocation(line: 2071, column: 22, scope: !1597)
!1611 = !DILocation(line: 2071, column: 12, scope: !1597)
!1612 = !DILocation(line: 2070, column: 7, scope: !1613)
!1613 = !DILexicalBlockFile(scope: !1574, file: !1, discriminator: 3)
!1614 = !DILocation(line: 2072, column: 10, scope: !1615)
!1615 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 2071, column: 28)
!1616 = !DILocation(line: 2072, column: 7, scope: !1615)
!1617 = !DILocation(line: 2073, column: 8, scope: !1618)
!1618 = distinct !DILexicalBlock(scope: !1615, file: !1, line: 2073, column: 8)
!1619 = !DILocation(line: 2073, column: 14, scope: !1618)
!1620 = !DILocation(line: 2073, column: 8, scope: !1615)
!1621 = !DILocation(line: 2074, column: 7, scope: !1618)
!1622 = !DILocation(line: 2074, column: 5, scope: !1618)
!1623 = !DILocation(line: 2075, column: 4, scope: !1615)
!1624 = !DILocation(line: 2078, column: 31, scope: !1574)
!1625 = !DILocation(line: 2078, column: 37, scope: !1574)
!1626 = !DILocation(line: 2078, column: 8, scope: !1574)
!1627 = !DILocation(line: 2078, column: 6, scope: !1574)
!1628 = !DILocation(line: 2079, column: 7, scope: !1629)
!1629 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2079, column: 7)
!1630 = !DILocation(line: 2079, column: 10, scope: !1629)
!1631 = !DILocation(line: 2079, column: 18, scope: !1629)
!1632 = !DILocation(line: 2079, column: 21, scope: !1633)
!1633 = !DILexicalBlockFile(scope: !1629, file: !1, discriminator: 1)
!1634 = !DILocation(line: 2079, column: 27, scope: !1633)
!1635 = !DILocation(line: 2079, column: 7, scope: !1633)
!1636 = !DILocation(line: 2080, column: 4, scope: !1629)
!1637 = !DILocation(line: 2083, column: 8, scope: !1638)
!1638 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2083, column: 7)
!1639 = !DILocation(line: 2083, column: 12, scope: !1638)
!1640 = !DILocation(line: 2083, column: 7, scope: !1574)
!1641 = !DILocation(line: 2085, column: 23, scope: !1642)
!1642 = distinct !DILexicalBlock(scope: !1638, file: !1, line: 2083, column: 22)
!1643 = !DILocation(line: 2085, column: 26, scope: !1642)
!1644 = !DILocation(line: 2088, column: 8, scope: !1642)
!1645 = !DILocation(line: 2088, column: 12, scope: !1642)
!1646 = !DILocation(line: 2088, column: 21, scope: !1642)
!1647 = !DILocation(line: 2088, column: 24, scope: !1642)
!1648 = !DILocation(line: 2088, column: 30, scope: !1642)
!1649 = !DILocation(line: 2088, column: 39, scope: !1642)
!1650 = !DILocation(line: 2085, column: 4, scope: !1642)
!1651 = !DILocation(line: 2089, column: 4, scope: !1642)
!1652 = !DILocation(line: 2091, column: 9, scope: !1574)
!1653 = !DILocation(line: 2091, column: 6, scope: !1574)
!1654 = !DILocation(line: 2092, column: 7, scope: !1655)
!1655 = distinct !DILexicalBlock(scope: !1574, file: !1, line: 2092, column: 7)
!1656 = !DILocation(line: 2092, column: 13, scope: !1655)
!1657 = !DILocation(line: 2092, column: 7, scope: !1574)
!1658 = !DILocation(line: 2093, column: 6, scope: !1655)
!1659 = !DILocation(line: 2093, column: 4, scope: !1655)
!1660 = !DILocation(line: 2094, column: 10, scope: !1574)
!1661 = !DILocation(line: 2094, column: 8, scope: !1574)
!1662 = !DILocation(line: 2058, column: 2, scope: !1663)
!1663 = !DILexicalBlockFile(scope: !1575, file: !1, discriminator: 1)
!1664 = !DILocation(line: 2096, column: 6, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2096, column: 6)
!1666 = !DILocation(line: 2096, column: 9, scope: !1665)
!1667 = !DILocation(line: 2096, column: 6, scope: !358)
!1668 = !DILocation(line: 2100, column: 3, scope: !1669)
!1669 = distinct !DILexicalBlock(scope: !1665, file: !1, line: 2096, column: 18)
!1670 = !DILocation(line: 2100, column: 10, scope: !1671)
!1671 = !DILexicalBlockFile(scope: !1669, file: !1, discriminator: 1)
!1672 = !DILocation(line: 2100, column: 16, scope: !1671)
!1673 = !DILocation(line: 2100, column: 3, scope: !1671)
!1674 = !DILocalVariable(name: "vp", scope: !1675, file: !1, line: 2101, type: !195)
!1675 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 2100, column: 25)
!1676 = !DILocation(line: 2101, column: 24, scope: !1675)
!1677 = !DILocalVariable(name: "as", scope: !1675, file: !1, line: 2102, type: !91)
!1678 = !DILocation(line: 2102, column: 26, scope: !1675)
!1679 = !DILocation(line: 2104, column: 4, scope: !1675)
!1680 = !DILocation(line: 2104, column: 4, scope: !1681)
!1681 = !DILexicalBlockFile(scope: !1682, file: !1, discriminator: 1)
!1682 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2104, column: 4)
!1683 = !DILocation(line: 2105, column: 25, scope: !1675)
!1684 = !DILocation(line: 2105, column: 28, scope: !1675)
!1685 = !DILocation(line: 2105, column: 33, scope: !1675)
!1686 = !DILocation(line: 2105, column: 31, scope: !1675)
!1687 = !DILocation(line: 2105, column: 37, scope: !1675)
!1688 = !DILocation(line: 2105, column: 35, scope: !1675)
!1689 = !DILocation(line: 2105, column: 4, scope: !1675)
!1690 = !DILocation(line: 2106, column: 16, scope: !1691)
!1691 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2106, column: 8)
!1692 = !DILocation(line: 2106, column: 22, scope: !1691)
!1693 = !DILocation(line: 2106, column: 11, scope: !1691)
!1694 = !DILocation(line: 2106, column: 8, scope: !1691)
!1695 = !DILocation(line: 2106, column: 26, scope: !1691)
!1696 = !DILocation(line: 2106, column: 8, scope: !1675)
!1697 = !DILocation(line: 2107, column: 13, scope: !1698)
!1698 = distinct !DILexicalBlock(scope: !1691, file: !1, line: 2106, column: 34)
!1699 = !DILocation(line: 2107, column: 19, scope: !1698)
!1700 = !DILocation(line: 2107, column: 8, scope: !1698)
!1701 = !DILocation(line: 2107, column: 5, scope: !1698)
!1702 = !DILocation(line: 2107, column: 23, scope: !1698)
!1703 = !DILocation(line: 2108, column: 8, scope: !1698)
!1704 = !DILocation(line: 2108, column: 14, scope: !1698)
!1705 = !DILocation(line: 2109, column: 4, scope: !1698)
!1706 = !DILocation(line: 2110, column: 39, scope: !1675)
!1707 = !DILocation(line: 2110, column: 45, scope: !1675)
!1708 = !DILocation(line: 2110, column: 8, scope: !1675)
!1709 = !DILocation(line: 2110, column: 6, scope: !1675)
!1710 = !DILocation(line: 2111, column: 4, scope: !1675)
!1711 = !DILocation(line: 2112, column: 8, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2112, column: 8)
!1713 = !DILocation(line: 2112, column: 10, scope: !1712)
!1714 = !DILocation(line: 2112, column: 8, scope: !1675)
!1715 = !DILocation(line: 2113, column: 13, scope: !1712)
!1716 = !DILocation(line: 2113, column: 5, scope: !1712)
!1717 = !DILocation(line: 2115, column: 15, scope: !1718)
!1718 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2115, column: 8)
!1719 = !DILocation(line: 2115, column: 19, scope: !1718)
!1720 = !DILocation(line: 2115, column: 28, scope: !1718)
!1721 = !DILocation(line: 2115, column: 8, scope: !1718)
!1722 = !DILocation(line: 2115, column: 36, scope: !1718)
!1723 = !DILocation(line: 2115, column: 8, scope: !1675)
!1724 = !DILocation(line: 2116, column: 18, scope: !1725)
!1725 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 2115, column: 42)
!1726 = !DILocation(line: 2116, column: 5, scope: !1725)
!1727 = !DILocation(line: 2116, column: 9, scope: !1725)
!1728 = !DILocation(line: 2116, column: 16, scope: !1725)
!1729 = !DILocation(line: 2117, column: 19, scope: !1725)
!1730 = !DILocation(line: 2117, column: 5, scope: !1725)
!1731 = !DILocation(line: 2117, column: 12, scope: !1725)
!1732 = !DILocation(line: 2117, column: 17, scope: !1725)
!1733 = !DILocation(line: 2118, column: 4, scope: !1725)
!1734 = !DILocation(line: 2120, column: 11, scope: !1735)
!1735 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 2118, column: 11)
!1736 = !DILocation(line: 2120, column: 17, scope: !1735)
!1737 = !DILocation(line: 2120, column: 27, scope: !1735)
!1738 = !DILocation(line: 2121, column: 35, scope: !1735)
!1739 = !DILocation(line: 2121, column: 9, scope: !1735)
!1740 = !DILocation(line: 2119, column: 5, scope: !1735)
!1741 = !DILocation(line: 2122, column: 18, scope: !1735)
!1742 = !DILocation(line: 2122, column: 5, scope: !1735)
!1743 = !DILocation(line: 2122, column: 9, scope: !1735)
!1744 = !DILocation(line: 2122, column: 16, scope: !1735)
!1745 = !DILocation(line: 2124, column: 29, scope: !1675)
!1746 = !DILocation(line: 2124, column: 36, scope: !1675)
!1747 = !DILocation(line: 2124, column: 4, scope: !1675)
!1748 = !DILocation(line: 2125, column: 9, scope: !1675)
!1749 = !DILocation(line: 2125, column: 7, scope: !1675)
!1750 = !DILocation(line: 2127, column: 10, scope: !1675)
!1751 = !DILocation(line: 2127, column: 7, scope: !1675)
!1752 = !DILocation(line: 2128, column: 8, scope: !1753)
!1753 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2128, column: 8)
!1754 = !DILocation(line: 2128, column: 14, scope: !1753)
!1755 = !DILocation(line: 2128, column: 8, scope: !1675)
!1756 = !DILocation(line: 2129, column: 7, scope: !1753)
!1757 = !DILocation(line: 2129, column: 5, scope: !1753)
!1758 = !DILocation(line: 2130, column: 27, scope: !1675)
!1759 = !DILocation(line: 2130, column: 47, scope: !1675)
!1760 = !DILocation(line: 2130, column: 8, scope: !1675)
!1761 = !DILocation(line: 2130, column: 6, scope: !1675)
!1762 = !DILocation(line: 2131, column: 8, scope: !1763)
!1763 = distinct !DILexicalBlock(scope: !1675, file: !1, line: 2131, column: 8)
!1764 = !DILocation(line: 2131, column: 10, scope: !1763)
!1765 = !DILocation(line: 2131, column: 8, scope: !1675)
!1766 = !DILocation(line: 2132, column: 5, scope: !1767)
!1767 = distinct !DILexicalBlock(scope: !1763, file: !1, line: 2131, column: 15)
!1768 = !DILocation(line: 2133, column: 24, scope: !1767)
!1769 = !DILocation(line: 2133, column: 27, scope: !1767)
!1770 = !DILocation(line: 2133, column: 5, scope: !1767)
!1771 = !DILocation(line: 2136, column: 5, scope: !1767)
!1772 = !DILocation(line: 2138, column: 11, scope: !1675)
!1773 = !DILocation(line: 2138, column: 9, scope: !1675)
!1774 = !DILocation(line: 2100, column: 3, scope: !1775)
!1775 = !DILexicalBlockFile(scope: !1669, file: !1, discriminator: 2)
!1776 = !DILocation(line: 2143, column: 23, scope: !1669)
!1777 = !DILocation(line: 2143, column: 3, scope: !1669)
!1778 = !DILocation(line: 2143, column: 10, scope: !1669)
!1779 = !DILocation(line: 2143, column: 21, scope: !1669)
!1780 = !DILocation(line: 2144, column: 3, scope: !1669)
!1781 = !DILocation(line: 2145, column: 27, scope: !1669)
!1782 = !DILocation(line: 2145, column: 34, scope: !1669)
!1783 = !DILocation(line: 2146, column: 7, scope: !1669)
!1784 = !DILocation(line: 2147, column: 7, scope: !1669)
!1785 = !DILocation(line: 2146, column: 42, scope: !1669)
!1786 = !DILocation(line: 2147, column: 41, scope: !1669)
!1787 = !DILocation(line: 2145, column: 3, scope: !1669)
!1788 = !DILocation(line: 2148, column: 7, scope: !1789)
!1789 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 2148, column: 7)
!1790 = !DILocation(line: 2149, column: 7, scope: !1789)
!1791 = !DILocation(line: 2148, column: 42, scope: !1789)
!1792 = !DILocation(line: 2149, column: 41, scope: !1789)
!1793 = !DILocation(line: 2148, column: 7, scope: !1669)
!1794 = !DILocation(line: 2150, column: 4, scope: !1789)
!1795 = !DILocation(line: 2150, column: 11, scope: !1789)
!1796 = !DILocation(line: 2150, column: 22, scope: !1789)
!1797 = !DILocation(line: 2150, column: 27, scope: !1789)
!1798 = !DILocation(line: 2152, column: 8, scope: !1799)
!1799 = distinct !DILexicalBlock(scope: !1800, file: !1, line: 2152, column: 8)
!1800 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 2151, column: 8)
!1801 = !DILocation(line: 2152, column: 43, scope: !1799)
!1802 = !DILocation(line: 2152, column: 8, scope: !1800)
!1803 = !DILocation(line: 2153, column: 5, scope: !1804)
!1804 = distinct !DILexicalBlock(scope: !1799, file: !1, line: 2152, column: 48)
!1805 = !DILocation(line: 2156, column: 11, scope: !1804)
!1806 = !DILocation(line: 2156, column: 18, scope: !1804)
!1807 = !DILocation(line: 2155, column: 5, scope: !1804)
!1808 = !DILocation(line: 2157, column: 4, scope: !1804)
!1809 = !DILocation(line: 2158, column: 28, scope: !1800)
!1810 = !DILocation(line: 2158, column: 35, scope: !1800)
!1811 = !DILocation(line: 2159, column: 10, scope: !1800)
!1812 = !DILocation(line: 2159, column: 16, scope: !1800)
!1813 = !DILocation(line: 2158, column: 4, scope: !1800)
!1814 = !DILocation(line: 2163, column: 9, scope: !1815)
!1815 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 2162, column: 7)
!1816 = !DILocation(line: 2163, column: 15, scope: !1815)
!1817 = !DILocation(line: 2163, column: 25, scope: !1815)
!1818 = !DILocation(line: 2164, column: 33, scope: !1815)
!1819 = !DILocation(line: 2164, column: 7, scope: !1815)
!1820 = !DILocation(line: 2162, column: 8, scope: !1815)
!1821 = !DILocation(line: 2162, column: 7, scope: !1669)
!1822 = !DILocation(line: 2166, column: 10, scope: !1823)
!1823 = distinct !DILexicalBlock(scope: !1815, file: !1, line: 2164, column: 40)
!1824 = !DILocation(line: 2166, column: 16, scope: !1823)
!1825 = !DILocation(line: 2166, column: 26, scope: !1823)
!1826 = !DILocation(line: 2166, column: 35, scope: !1823)
!1827 = !DILocation(line: 2166, column: 41, scope: !1823)
!1828 = !DILocation(line: 2166, column: 50, scope: !1823)
!1829 = !DILocation(line: 2165, column: 31, scope: !1823)
!1830 = !DILocation(line: 2165, column: 9, scope: !1823)
!1831 = !DILocation(line: 2165, column: 7, scope: !1823)
!1832 = !DILocation(line: 2167, column: 4, scope: !1823)
!1833 = !DILocation(line: 2169, column: 18, scope: !1669)
!1834 = !DILocation(line: 2169, column: 3, scope: !1669)
!1835 = !DILocation(line: 2169, column: 9, scope: !1669)
!1836 = !DILocation(line: 2169, column: 16, scope: !1669)
!1837 = !DILocation(line: 2170, column: 28, scope: !1669)
!1838 = !DILocation(line: 2170, column: 35, scope: !1669)
!1839 = !DILocation(line: 2170, column: 3, scope: !1669)
!1840 = !DILocation(line: 2171, column: 3, scope: !1669)
!1841 = !DILocation(line: 2096, column: 12, scope: !1842)
!1842 = !DILexicalBlockFile(scope: !1665, file: !1, discriminator: 1)
!1843 = !DILocation(line: 2179, column: 38, scope: !358)
!1844 = !DILocation(line: 2179, column: 41, scope: !358)
!1845 = !DILocation(line: 2179, column: 45, scope: !358)
!1846 = !DILocation(line: 2179, column: 6, scope: !358)
!1847 = !DILocation(line: 2179, column: 4, scope: !358)
!1848 = !DILocation(line: 2180, column: 6, scope: !1849)
!1849 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2180, column: 6)
!1850 = !DILocation(line: 2180, column: 8, scope: !1849)
!1851 = !DILocation(line: 2180, column: 6, scope: !358)
!1852 = !DILocation(line: 2181, column: 11, scope: !1849)
!1853 = !DILocation(line: 2181, column: 3, scope: !1849)
!1854 = !DILocation(line: 2182, column: 6, scope: !1855)
!1855 = distinct !DILexicalBlock(scope: !358, file: !1, line: 2182, column: 6)
!1856 = !DILocation(line: 2182, column: 10, scope: !1855)
!1857 = !DILocation(line: 2182, column: 6, scope: !358)
!1858 = !DILocation(line: 2183, column: 3, scope: !1855)
!1859 = !DILocation(line: 2183, column: 7, scope: !1855)
!1860 = !DILocation(line: 2183, column: 17, scope: !1855)
!1861 = !DILocation(line: 2183, column: 25, scope: !1855)
!1862 = !DILocation(line: 2184, column: 11, scope: !358)
!1863 = !DILocation(line: 2184, column: 3, scope: !358)
!1864 = !DILocation(line: 2184, column: 9, scope: !358)
!1865 = !DILocation(line: 2185, column: 19, scope: !358)
!1866 = !DILocation(line: 2185, column: 2, scope: !358)
!1867 = !DILocation(line: 2186, column: 2, scope: !358)
!1868 = !DILocation(line: 2187, column: 1, scope: !358)
!1869 = !DILocalVariable(name: "mtree", arg: 1, scope: !376, file: !1, line: 1461, type: !191)
!1870 = !DILocation(line: 1461, column: 31, scope: !376)
!1871 = !DILocation(line: 1464, column: 2, scope: !376)
!1872 = !DILocation(line: 1464, column: 9, scope: !376)
!1873 = !DILocation(line: 1464, column: 21, scope: !376)
!1874 = !DILocation(line: 1466, column: 6, scope: !1875)
!1875 = distinct !DILexicalBlock(scope: !376, file: !1, line: 1466, column: 6)
!1876 = !DILocation(line: 1466, column: 13, scope: !1875)
!1877 = !DILocation(line: 1466, column: 18, scope: !1875)
!1878 = !DILocation(line: 1466, column: 6, scope: !376)
!1879 = !DILocation(line: 1467, column: 3, scope: !1880)
!1880 = distinct !DILexicalBlock(scope: !1875, file: !1, line: 1466, column: 29)
!1881 = !DILocation(line: 1467, column: 10, scope: !1880)
!1882 = !DILocation(line: 1467, column: 22, scope: !1880)
!1883 = !DILocation(line: 1468, column: 3, scope: !1880)
!1884 = !DILocation(line: 1468, column: 10, scope: !1880)
!1885 = !DILocation(line: 1468, column: 14, scope: !1880)
!1886 = !DILocation(line: 1469, column: 3, scope: !1880)
!1887 = !DILocation(line: 1469, column: 10, scope: !1880)
!1888 = !DILocation(line: 1469, column: 18, scope: !1880)
!1889 = !DILocation(line: 1470, column: 2, scope: !1880)
!1890 = !DILocation(line: 1519, column: 1, scope: !376)
!1891 = !DILocalVariable(name: "n1", arg: 1, scope: !353, file: !1, line: 1663, type: !230)
!1892 = !DILocation(line: 1663, column: 52, scope: !353)
!1893 = !DILocalVariable(name: "n2", arg: 2, scope: !353, file: !1, line: 1664, type: !230)
!1894 = !DILocation(line: 1664, column: 35, scope: !353)
!1895 = !DILocalVariable(name: "e1", scope: !353, file: !1, line: 1666, type: !325)
!1896 = !DILocation(line: 1666, column: 28, scope: !353)
!1897 = !DILocation(line: 1666, column: 61, scope: !353)
!1898 = !DILocation(line: 1666, column: 33, scope: !353)
!1899 = !DILocalVariable(name: "e2", scope: !353, file: !1, line: 1667, type: !325)
!1900 = !DILocation(line: 1667, column: 28, scope: !353)
!1901 = !DILocation(line: 1667, column: 61, scope: !353)
!1902 = !DILocation(line: 1667, column: 33, scope: !353)
!1903 = !DILocation(line: 1669, column: 17, scope: !353)
!1904 = !DILocation(line: 1669, column: 21, scope: !353)
!1905 = !DILocation(line: 1669, column: 30, scope: !353)
!1906 = !DILocation(line: 1669, column: 33, scope: !353)
!1907 = !DILocation(line: 1669, column: 37, scope: !353)
!1908 = !DILocation(line: 1669, column: 46, scope: !353)
!1909 = !DILocation(line: 1669, column: 10, scope: !353)
!1910 = !DILocation(line: 1669, column: 2, scope: !353)
!1911 = !DILocalVariable(name: "n", arg: 1, scope: !354, file: !1, line: 1673, type: !230)
!1912 = !DILocation(line: 1673, column: 51, scope: !354)
!1913 = !DILocalVariable(name: "key", arg: 2, scope: !354, file: !1, line: 1673, type: !43)
!1914 = !DILocation(line: 1673, column: 66, scope: !354)
!1915 = !DILocalVariable(name: "e", scope: !354, file: !1, line: 1675, type: !325)
!1916 = !DILocation(line: 1675, column: 28, scope: !354)
!1917 = !DILocation(line: 1675, column: 60, scope: !354)
!1918 = !DILocation(line: 1675, column: 32, scope: !354)
!1919 = !DILocation(line: 1677, column: 31, scope: !354)
!1920 = !DILocation(line: 1677, column: 36, scope: !354)
!1921 = !DILocation(line: 1677, column: 39, scope: !354)
!1922 = !DILocation(line: 1677, column: 48, scope: !354)
!1923 = !DILocation(line: 1677, column: 10, scope: !354)
!1924 = !DILocation(line: 1677, column: 2, scope: !354)
!1925 = !DILocalVariable(name: "a", arg: 1, scope: !355, file: !1, line: 1721, type: !4)
!1926 = !DILocation(line: 1721, column: 51, scope: !355)
!1927 = !DILocalVariable(name: "file", arg: 2, scope: !355, file: !1, line: 1721, type: !195)
!1928 = !DILocation(line: 1721, column: 74, scope: !355)
!1929 = !DILocalVariable(name: "entry", arg: 3, scope: !355, file: !1, line: 1722, type: !30)
!1930 = !DILocation(line: 1722, column: 27, scope: !355)
!1931 = !DILocalVariable(name: "pathname", scope: !355, file: !1, line: 1724, type: !80)
!1932 = !DILocation(line: 1724, column: 14, scope: !355)
!1933 = !DILocalVariable(name: "p", scope: !355, file: !1, line: 1725, type: !95)
!1934 = !DILocation(line: 1725, column: 8, scope: !355)
!1935 = !DILocalVariable(name: "dirname", scope: !355, file: !1, line: 1725, type: !95)
!1936 = !DILocation(line: 1725, column: 12, scope: !355)
!1937 = !DILocalVariable(name: "slash", scope: !355, file: !1, line: 1725, type: !95)
!1938 = !DILocation(line: 1725, column: 22, scope: !355)
!1939 = !DILocalVariable(name: "len", scope: !355, file: !1, line: 1726, type: !45)
!1940 = !DILocation(line: 1726, column: 9, scope: !355)
!1941 = !DILocalVariable(name: "ret", scope: !355, file: !1, line: 1727, type: !23)
!1942 = !DILocation(line: 1727, column: 6, scope: !355)
!1943 = !DILocation(line: 1729, column: 2, scope: !355)
!1944 = !DILocation(line: 1729, column: 2, scope: !1945)
!1945 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 4)
!1946 = !DILocation(line: 1729, column: 2, scope: !1947)
!1947 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 1)
!1948 = !DILocation(line: 1729, column: 2, scope: !1949)
!1949 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 2)
!1950 = !DILocation(line: 1729, column: 2, scope: !1951)
!1951 = !DILexicalBlockFile(scope: !1949, file: !1, discriminator: 5)
!1952 = !DILocation(line: 1729, column: 2, scope: !1953)
!1953 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 3)
!1954 = !DILocation(line: 1755, column: 8, scope: !355)
!1955 = !DILocation(line: 1757, column: 14, scope: !355)
!1956 = !DILocation(line: 1757, column: 20, scope: !355)
!1957 = !DILocation(line: 1757, column: 29, scope: !355)
!1958 = !DILocation(line: 1757, column: 11, scope: !355)
!1959 = !DILocation(line: 1758, column: 13, scope: !1960)
!1960 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1758, column: 6)
!1961 = !DILocation(line: 1758, column: 6, scope: !1960)
!1962 = !DILocation(line: 1758, column: 28, scope: !1960)
!1963 = !DILocation(line: 1758, column: 6, scope: !355)
!1964 = !DILocation(line: 1759, column: 3, scope: !1965)
!1965 = distinct !DILexicalBlock(scope: !1960, file: !1, line: 1758, column: 34)
!1966 = !DILocation(line: 1760, column: 3, scope: !1965)
!1967 = !DILocation(line: 1763, column: 2, scope: !355)
!1968 = !DILocation(line: 1763, column: 2, scope: !1947)
!1969 = !DILocation(line: 1763, column: 2, scope: !1949)
!1970 = !DILocation(line: 1763, column: 2, scope: !1953)
!1971 = !DILocation(line: 1765, column: 8, scope: !355)
!1972 = !DILocation(line: 1765, column: 14, scope: !355)
!1973 = !DILocation(line: 1765, column: 24, scope: !355)
!1974 = !DILocation(line: 1765, column: 6, scope: !355)
!1975 = !DILocation(line: 1766, column: 16, scope: !355)
!1976 = !DILocation(line: 1766, column: 22, scope: !355)
!1977 = !DILocation(line: 1766, column: 32, scope: !355)
!1978 = !DILocation(line: 1766, column: 14, scope: !355)
!1979 = !DILocation(line: 1766, column: 4, scope: !355)
!1980 = !DILocation(line: 1771, column: 2, scope: !355)
!1981 = !DILocation(line: 1771, column: 10, scope: !1947)
!1982 = !DILocation(line: 1771, column: 9, scope: !1947)
!1983 = !DILocation(line: 1771, column: 2, scope: !1947)
!1984 = !DILocation(line: 1772, column: 7, scope: !1985)
!1985 = distinct !DILexicalBlock(scope: !1986, file: !1, line: 1772, column: 7)
!1986 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1771, column: 13)
!1987 = !DILocation(line: 1772, column: 12, scope: !1985)
!1988 = !DILocation(line: 1772, column: 7, scope: !1986)
!1989 = !DILocation(line: 1773, column: 5, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1985, file: !1, line: 1772, column: 20)
!1991 = !DILocation(line: 1774, column: 7, scope: !1990)
!1992 = !DILocation(line: 1775, column: 3, scope: !1990)
!1993 = !DILocation(line: 1775, column: 14, scope: !1994)
!1994 = !DILexicalBlockFile(scope: !1995, file: !1, discriminator: 1)
!1995 = distinct !DILexicalBlock(scope: !1985, file: !1, line: 1775, column: 14)
!1996 = !DILocation(line: 1775, column: 19, scope: !1994)
!1997 = !DILocation(line: 1776, column: 4, scope: !1995)
!1998 = !DILocation(line: 1777, column: 12, scope: !1999)
!1999 = distinct !DILexicalBlock(scope: !1995, file: !1, line: 1777, column: 12)
!2000 = !DILocation(line: 1777, column: 17, scope: !1999)
!2001 = !DILocation(line: 1777, column: 24, scope: !1999)
!2002 = !DILocation(line: 1777, column: 27, scope: !2003)
!2003 = !DILexicalBlockFile(scope: !1999, file: !1, discriminator: 1)
!2004 = !DILocation(line: 1777, column: 32, scope: !2003)
!2005 = !DILocation(line: 1777, column: 12, scope: !2003)
!2006 = !DILocation(line: 1778, column: 6, scope: !2007)
!2007 = distinct !DILexicalBlock(scope: !1999, file: !1, line: 1777, column: 40)
!2008 = !DILocation(line: 1779, column: 8, scope: !2007)
!2009 = !DILocation(line: 1780, column: 3, scope: !2007)
!2010 = !DILocation(line: 1781, column: 4, scope: !1999)
!2011 = !DILocation(line: 1771, column: 2, scope: !1949)
!2012 = !DILocation(line: 1783, column: 6, scope: !2013)
!2013 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1783, column: 6)
!2014 = !DILocation(line: 1783, column: 11, scope: !2013)
!2015 = !DILocation(line: 1783, column: 8, scope: !2013)
!2016 = !DILocation(line: 1783, column: 6, scope: !355)
!2017 = !DILocation(line: 1784, column: 11, scope: !2018)
!2018 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 1783, column: 20)
!2019 = !DILocation(line: 1784, column: 20, scope: !2018)
!2020 = !DILocation(line: 1784, column: 23, scope: !2018)
!2021 = !DILocation(line: 1784, column: 26, scope: !2018)
!2022 = !DILocation(line: 1784, column: 3, scope: !2018)
!2023 = !DILocation(line: 1785, column: 7, scope: !2018)
!2024 = !DILocation(line: 1785, column: 5, scope: !2018)
!2025 = !DILocation(line: 1786, column: 2, scope: !2018)
!2026 = !DILocation(line: 1790, column: 2, scope: !355)
!2027 = !DILocation(line: 1790, column: 9, scope: !1947)
!2028 = !DILocation(line: 1790, column: 13, scope: !1947)
!2029 = !DILocation(line: 1790, column: 2, scope: !1947)
!2030 = !DILocalVariable(name: "ll", scope: !2031, file: !1, line: 1791, type: !45)
!2031 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1790, column: 18)
!2032 = !DILocation(line: 1791, column: 10, scope: !2031)
!2033 = !DILocation(line: 1791, column: 15, scope: !2031)
!2034 = !DILocation(line: 1793, column: 7, scope: !2035)
!2035 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1793, column: 7)
!2036 = !DILocation(line: 1793, column: 11, scope: !2035)
!2037 = !DILocation(line: 1793, column: 15, scope: !2035)
!2038 = !DILocation(line: 1793, column: 20, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !2035, file: !1, discriminator: 1)
!2040 = !DILocation(line: 1793, column: 23, scope: !2039)
!2041 = !DILocation(line: 1793, column: 18, scope: !2039)
!2042 = !DILocation(line: 1793, column: 27, scope: !2039)
!2043 = !DILocation(line: 1793, column: 7, scope: !2039)
!2044 = !DILocation(line: 1794, column: 6, scope: !2045)
!2045 = distinct !DILexicalBlock(scope: !2035, file: !1, line: 1793, column: 35)
!2046 = !DILocation(line: 1794, column: 9, scope: !2045)
!2047 = !DILocation(line: 1794, column: 4, scope: !2045)
!2048 = !DILocation(line: 1794, column: 13, scope: !2045)
!2049 = !DILocation(line: 1795, column: 7, scope: !2045)
!2050 = !DILocation(line: 1796, column: 3, scope: !2045)
!2051 = !DILocation(line: 1797, column: 7, scope: !2052)
!2052 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1797, column: 7)
!2053 = !DILocation(line: 1797, column: 11, scope: !2052)
!2054 = !DILocation(line: 1797, column: 15, scope: !2052)
!2055 = !DILocation(line: 1797, column: 20, scope: !2056)
!2056 = !DILexicalBlockFile(scope: !2052, file: !1, discriminator: 1)
!2057 = !DILocation(line: 1797, column: 23, scope: !2056)
!2058 = !DILocation(line: 1797, column: 18, scope: !2056)
!2059 = !DILocation(line: 1797, column: 27, scope: !2056)
!2060 = !DILocation(line: 1797, column: 34, scope: !2056)
!2061 = !DILocation(line: 1797, column: 39, scope: !2062)
!2062 = !DILexicalBlockFile(scope: !2052, file: !1, discriminator: 2)
!2063 = !DILocation(line: 1797, column: 42, scope: !2062)
!2064 = !DILocation(line: 1797, column: 37, scope: !2062)
!2065 = !DILocation(line: 1797, column: 46, scope: !2062)
!2066 = !DILocation(line: 1797, column: 7, scope: !2062)
!2067 = !DILocation(line: 1798, column: 6, scope: !2068)
!2068 = distinct !DILexicalBlock(scope: !2052, file: !1, line: 1797, column: 54)
!2069 = !DILocation(line: 1798, column: 9, scope: !2068)
!2070 = !DILocation(line: 1798, column: 4, scope: !2068)
!2071 = !DILocation(line: 1798, column: 13, scope: !2068)
!2072 = !DILocation(line: 1799, column: 8, scope: !2068)
!2073 = !DILocation(line: 1800, column: 3, scope: !2068)
!2074 = !DILocation(line: 1801, column: 7, scope: !2075)
!2075 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1801, column: 7)
!2076 = !DILocation(line: 1801, column: 11, scope: !2075)
!2077 = !DILocation(line: 1801, column: 15, scope: !2075)
!2078 = !DILocation(line: 1801, column: 20, scope: !2079)
!2079 = !DILexicalBlockFile(scope: !2075, file: !1, discriminator: 1)
!2080 = !DILocation(line: 1801, column: 23, scope: !2079)
!2081 = !DILocation(line: 1801, column: 18, scope: !2079)
!2082 = !DILocation(line: 1801, column: 27, scope: !2079)
!2083 = !DILocation(line: 1801, column: 34, scope: !2079)
!2084 = !DILocation(line: 1801, column: 39, scope: !2085)
!2085 = !DILexicalBlockFile(scope: !2075, file: !1, discriminator: 2)
!2086 = !DILocation(line: 1801, column: 42, scope: !2085)
!2087 = !DILocation(line: 1801, column: 37, scope: !2085)
!2088 = !DILocation(line: 1801, column: 46, scope: !2085)
!2089 = !DILocation(line: 1801, column: 53, scope: !2085)
!2090 = !DILocation(line: 1802, column: 9, scope: !2075)
!2091 = !DILocation(line: 1802, column: 12, scope: !2075)
!2092 = !DILocation(line: 1802, column: 7, scope: !2075)
!2093 = !DILocation(line: 1802, column: 16, scope: !2075)
!2094 = !DILocation(line: 1801, column: 7, scope: !2095)
!2095 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 3)
!2096 = !DILocation(line: 1803, column: 6, scope: !2097)
!2097 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 1802, column: 24)
!2098 = !DILocation(line: 1803, column: 9, scope: !2097)
!2099 = !DILocation(line: 1803, column: 4, scope: !2097)
!2100 = !DILocation(line: 1803, column: 13, scope: !2097)
!2101 = !DILocation(line: 1804, column: 8, scope: !2097)
!2102 = !DILocation(line: 1805, column: 3, scope: !2097)
!2103 = !DILocation(line: 1806, column: 7, scope: !2104)
!2104 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1806, column: 7)
!2105 = !DILocation(line: 1806, column: 13, scope: !2104)
!2106 = !DILocation(line: 1806, column: 10, scope: !2104)
!2107 = !DILocation(line: 1806, column: 7, scope: !2031)
!2108 = !DILocation(line: 1807, column: 4, scope: !2104)
!2109 = !DILocation(line: 1790, column: 2, scope: !1949)
!2110 = !DILocation(line: 1809, column: 2, scope: !355)
!2111 = !DILocation(line: 1809, column: 10, scope: !1947)
!2112 = !DILocation(line: 1809, column: 9, scope: !1947)
!2113 = !DILocation(line: 1809, column: 2, scope: !1947)
!2114 = !DILocation(line: 1810, column: 7, scope: !2115)
!2115 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 1810, column: 7)
!2116 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1809, column: 13)
!2117 = !DILocation(line: 1810, column: 12, scope: !2115)
!2118 = !DILocation(line: 1810, column: 7, scope: !2116)
!2119 = !DILocation(line: 1811, column: 8, scope: !2120)
!2120 = distinct !DILexicalBlock(scope: !2121, file: !1, line: 1811, column: 8)
!2121 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 1810, column: 20)
!2122 = !DILocation(line: 1811, column: 13, scope: !2120)
!2123 = !DILocation(line: 1811, column: 8, scope: !2121)
!2124 = !DILocation(line: 1813, column: 12, scope: !2120)
!2125 = !DILocation(line: 1813, column: 15, scope: !2120)
!2126 = !DILocation(line: 1813, column: 16, scope: !2120)
!2127 = !DILocation(line: 1813, column: 5, scope: !2120)
!2128 = !DILocation(line: 1814, column: 13, scope: !2129)
!2129 = distinct !DILexicalBlock(scope: !2120, file: !1, line: 1814, column: 13)
!2130 = !DILocation(line: 1814, column: 18, scope: !2129)
!2131 = !DILocation(line: 1814, column: 25, scope: !2129)
!2132 = !DILocation(line: 1814, column: 28, scope: !2133)
!2133 = !DILexicalBlockFile(scope: !2129, file: !1, discriminator: 1)
!2134 = !DILocation(line: 1814, column: 33, scope: !2133)
!2135 = !DILocation(line: 1814, column: 13, scope: !2133)
!2136 = !DILocation(line: 1816, column: 12, scope: !2129)
!2137 = !DILocation(line: 1816, column: 15, scope: !2129)
!2138 = !DILocation(line: 1816, column: 16, scope: !2129)
!2139 = !DILocation(line: 1816, column: 5, scope: !2129)
!2140 = !DILocation(line: 1817, column: 13, scope: !2141)
!2141 = distinct !DILexicalBlock(scope: !2129, file: !1, line: 1817, column: 13)
!2142 = !DILocation(line: 1817, column: 18, scope: !2141)
!2143 = !DILocation(line: 1817, column: 25, scope: !2141)
!2144 = !DILocation(line: 1817, column: 28, scope: !2145)
!2145 = !DILexicalBlockFile(scope: !2141, file: !1, discriminator: 1)
!2146 = !DILocation(line: 1817, column: 33, scope: !2145)
!2147 = !DILocation(line: 1817, column: 40, scope: !2145)
!2148 = !DILocation(line: 1817, column: 43, scope: !2149)
!2149 = !DILexicalBlockFile(scope: !2141, file: !1, discriminator: 2)
!2150 = !DILocation(line: 1817, column: 48, scope: !2149)
!2151 = !DILocation(line: 1817, column: 13, scope: !2149)
!2152 = !DILocalVariable(name: "rp", scope: !2153, file: !1, line: 1821, type: !95)
!2153 = distinct !DILexicalBlock(scope: !2141, file: !1, line: 1817, column: 56)
!2154 = !DILocation(line: 1821, column: 11, scope: !2153)
!2155 = !DILocation(line: 1821, column: 16, scope: !2153)
!2156 = !DILocation(line: 1821, column: 18, scope: !2153)
!2157 = !DILocation(line: 1822, column: 5, scope: !2153)
!2158 = !DILocation(line: 1822, column: 12, scope: !2159)
!2159 = !DILexicalBlockFile(scope: !2153, file: !1, discriminator: 1)
!2160 = !DILocation(line: 1822, column: 18, scope: !2159)
!2161 = !DILocation(line: 1822, column: 15, scope: !2159)
!2162 = !DILocation(line: 1822, column: 5, scope: !2159)
!2163 = !DILocation(line: 1823, column: 11, scope: !2164)
!2164 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 1823, column: 10)
!2165 = distinct !DILexicalBlock(scope: !2153, file: !1, line: 1822, column: 27)
!2166 = !DILocation(line: 1823, column: 10, scope: !2164)
!2167 = !DILocation(line: 1823, column: 14, scope: !2164)
!2168 = !DILocation(line: 1823, column: 10, scope: !2165)
!2169 = !DILocation(line: 1824, column: 7, scope: !2164)
!2170 = !DILocation(line: 1825, column: 6, scope: !2165)
!2171 = !DILocation(line: 1822, column: 5, scope: !2172)
!2172 = !DILexicalBlockFile(scope: !2153, file: !1, discriminator: 2)
!2173 = !DILocation(line: 1827, column: 9, scope: !2174)
!2174 = distinct !DILexicalBlock(scope: !2153, file: !1, line: 1827, column: 9)
!2175 = !DILocation(line: 1827, column: 14, scope: !2174)
!2176 = !DILocation(line: 1827, column: 12, scope: !2174)
!2177 = !DILocation(line: 1827, column: 9, scope: !2153)
!2178 = !DILocation(line: 1828, column: 13, scope: !2179)
!2179 = distinct !DILexicalBlock(scope: !2174, file: !1, line: 1827, column: 23)
!2180 = !DILocation(line: 1828, column: 17, scope: !2179)
!2181 = !DILocation(line: 1828, column: 18, scope: !2179)
!2182 = !DILocation(line: 1828, column: 6, scope: !2179)
!2183 = !DILocation(line: 1829, column: 10, scope: !2179)
!2184 = !DILocation(line: 1829, column: 8, scope: !2179)
!2185 = !DILocation(line: 1830, column: 5, scope: !2179)
!2186 = !DILocation(line: 1831, column: 13, scope: !2187)
!2187 = distinct !DILexicalBlock(scope: !2174, file: !1, line: 1830, column: 12)
!2188 = !DILocation(line: 1831, column: 22, scope: !2187)
!2189 = !DILocation(line: 1831, column: 23, scope: !2187)
!2190 = !DILocation(line: 1831, column: 6, scope: !2187)
!2191 = !DILocation(line: 1832, column: 10, scope: !2187)
!2192 = !DILocation(line: 1832, column: 8, scope: !2187)
!2193 = !DILocation(line: 1834, column: 4, scope: !2153)
!2194 = !DILocation(line: 1835, column: 6, scope: !2141)
!2195 = !DILocation(line: 1836, column: 3, scope: !2121)
!2196 = !DILocation(line: 1837, column: 5, scope: !2115)
!2197 = !DILocation(line: 1809, column: 2, scope: !1949)
!2198 = !DILocation(line: 1839, column: 6, scope: !355)
!2199 = !DILocation(line: 1839, column: 4, scope: !355)
!2200 = !DILocation(line: 1840, column: 15, scope: !355)
!2201 = !DILocation(line: 1840, column: 8, scope: !355)
!2202 = !DILocation(line: 1840, column: 6, scope: !355)
!2203 = !DILocation(line: 1850, column: 13, scope: !2204)
!2204 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1850, column: 6)
!2205 = !DILocation(line: 1850, column: 6, scope: !2204)
!2206 = !DILocation(line: 1850, column: 21, scope: !2204)
!2207 = !DILocation(line: 1850, column: 26, scope: !2204)
!2208 = !DILocation(line: 1850, column: 37, scope: !2209)
!2209 = !DILexicalBlockFile(scope: !2204, file: !1, discriminator: 1)
!2210 = !DILocation(line: 1850, column: 29, scope: !2209)
!2211 = !DILocation(line: 1850, column: 49, scope: !2209)
!2212 = !DILocation(line: 1850, column: 6, scope: !2209)
!2213 = !DILocalVariable(name: "as", scope: !2214, file: !1, line: 1851, type: !91)
!2214 = distinct !DILexicalBlock(scope: !2204, file: !1, line: 1850, column: 55)
!2215 = !DILocation(line: 1851, column: 25, scope: !2214)
!2216 = !DILocation(line: 1852, column: 3, scope: !2214)
!2217 = !DILocation(line: 1852, column: 3, scope: !2218)
!2218 = !DILexicalBlockFile(scope: !2219, file: !1, discriminator: 1)
!2219 = distinct !DILexicalBlock(scope: !2214, file: !1, line: 1852, column: 3)
!2220 = !DILocation(line: 1853, column: 3, scope: !2214)
!2221 = !DILocation(line: 1854, column: 24, scope: !2214)
!2222 = !DILocation(line: 1854, column: 27, scope: !2214)
!2223 = !DILocation(line: 1854, column: 3, scope: !2214)
!2224 = !DILocation(line: 1855, column: 3, scope: !2214)
!2225 = !DILocation(line: 1856, column: 26, scope: !2214)
!2226 = !DILocation(line: 1856, column: 32, scope: !2214)
!2227 = !DILocation(line: 1856, column: 3, scope: !2214)
!2228 = !DILocation(line: 1857, column: 3, scope: !2214)
!2229 = !DILocation(line: 1858, column: 7, scope: !2214)
!2230 = !DILocation(line: 1858, column: 13, scope: !2214)
!2231 = !DILocation(line: 1858, column: 23, scope: !2214)
!2232 = !DILocation(line: 1858, column: 5, scope: !2214)
!2233 = !DILocation(line: 1859, column: 9, scope: !2214)
!2234 = !DILocation(line: 1859, column: 7, scope: !2214)
!2235 = !DILocation(line: 1860, column: 2, scope: !2214)
!2236 = !DILocation(line: 1866, column: 8, scope: !355)
!2237 = !DILocation(line: 1867, column: 2, scope: !355)
!2238 = !DILocation(line: 1867, column: 10, scope: !2239)
!2239 = !DILexicalBlockFile(scope: !2240, file: !1, discriminator: 1)
!2240 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 1867, column: 2)
!2241 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1867, column: 2)
!2242 = !DILocation(line: 1867, column: 9, scope: !2239)
!2243 = !DILocation(line: 1867, column: 12, scope: !2239)
!2244 = !DILocation(line: 1867, column: 2, scope: !2239)
!2245 = !DILocation(line: 1868, column: 8, scope: !2246)
!2246 = distinct !DILexicalBlock(scope: !2247, file: !1, line: 1868, column: 7)
!2247 = distinct !DILexicalBlock(scope: !2240, file: !1, line: 1867, column: 26)
!2248 = !DILocation(line: 1868, column: 7, scope: !2246)
!2249 = !DILocation(line: 1868, column: 10, scope: !2246)
!2250 = !DILocation(line: 1868, column: 7, scope: !2247)
!2251 = !DILocation(line: 1869, column: 12, scope: !2246)
!2252 = !DILocation(line: 1869, column: 10, scope: !2246)
!2253 = !DILocation(line: 1869, column: 4, scope: !2246)
!2254 = !DILocation(line: 1870, column: 2, scope: !2247)
!2255 = !DILocation(line: 1867, column: 22, scope: !2256)
!2256 = !DILexicalBlockFile(scope: !2240, file: !1, discriminator: 2)
!2257 = !DILocation(line: 1867, column: 2, scope: !2256)
!2258 = !DILocation(line: 1871, column: 6, scope: !2259)
!2259 = distinct !DILexicalBlock(scope: !355, file: !1, line: 1871, column: 6)
!2260 = !DILocation(line: 1871, column: 12, scope: !2259)
!2261 = !DILocation(line: 1871, column: 6, scope: !355)
!2262 = !DILocation(line: 1873, column: 28, scope: !2263)
!2263 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 1871, column: 21)
!2264 = !DILocation(line: 1873, column: 3, scope: !2263)
!2265 = !DILocation(line: 1873, column: 9, scope: !2263)
!2266 = !DILocation(line: 1873, column: 19, scope: !2263)
!2267 = !DILocation(line: 1873, column: 26, scope: !2263)
!2268 = !DILocation(line: 1874, column: 3, scope: !2263)
!2269 = !DILocation(line: 1875, column: 3, scope: !2263)
!2270 = !DILocation(line: 1876, column: 4, scope: !2263)
!2271 = !DILocation(line: 1876, column: 10, scope: !2263)
!2272 = !DILocation(line: 1876, column: 20, scope: !2263)
!2273 = !DILocation(line: 1876, column: 22, scope: !2263)
!2274 = !DILocation(line: 1877, column: 11, scope: !2263)
!2275 = !DILocation(line: 1877, column: 3, scope: !2263)
!2276 = !DILocation(line: 1881, column: 3, scope: !355)
!2277 = !DILocation(line: 1881, column: 10, scope: !355)
!2278 = !DILocation(line: 1882, column: 27, scope: !355)
!2279 = !DILocation(line: 1882, column: 35, scope: !355)
!2280 = !DILocation(line: 1882, column: 41, scope: !355)
!2281 = !DILocation(line: 1882, column: 51, scope: !355)
!2282 = !DILocation(line: 1882, column: 33, scope: !355)
!2283 = !DILocation(line: 1882, column: 2, scope: !355)
!2284 = !DILocation(line: 1882, column: 8, scope: !355)
!2285 = !DILocation(line: 1882, column: 18, scope: !355)
!2286 = !DILocation(line: 1882, column: 25, scope: !355)
!2287 = !DILocation(line: 1883, column: 2, scope: !355)
!2288 = !DILocation(line: 1883, column: 2, scope: !1947)
!2289 = !DILocation(line: 1883, column: 2, scope: !1949)
!2290 = !DILocation(line: 1883, column: 2, scope: !1953)
!2291 = !DILocation(line: 1884, column: 10, scope: !355)
!2292 = !DILocation(line: 1884, column: 2, scope: !355)
!2293 = !DILocation(line: 1885, column: 1, scope: !355)
!2294 = !DILocalVariable(name: "mtree", arg: 1, scope: !361, file: !1, line: 1922, type: !191)
!2295 = !DILocation(line: 1922, column: 47, scope: !361)
!2296 = !DILocalVariable(name: "file", arg: 2, scope: !361, file: !1, line: 1922, type: !195)
!2297 = !DILocation(line: 1922, column: 74, scope: !361)
!2298 = !DILocation(line: 1924, column: 9, scope: !361)
!2299 = !DILocation(line: 1924, column: 15, scope: !361)
!2300 = !DILocation(line: 1924, column: 20, scope: !361)
!2301 = !DILocation(line: 1925, column: 34, scope: !361)
!2302 = !DILocation(line: 1925, column: 10, scope: !361)
!2303 = !DILocation(line: 1925, column: 17, scope: !361)
!2304 = !DILocation(line: 1925, column: 27, scope: !361)
!2305 = !DILocation(line: 1925, column: 32, scope: !361)
!2306 = !DILocation(line: 1926, column: 35, scope: !361)
!2307 = !DILocation(line: 1926, column: 41, scope: !361)
!2308 = !DILocation(line: 1926, column: 9, scope: !361)
!2309 = !DILocation(line: 1926, column: 16, scope: !361)
!2310 = !DILocation(line: 1926, column: 26, scope: !361)
!2311 = !DILocation(line: 1926, column: 31, scope: !361)
!2312 = !DILocation(line: 1927, column: 1, scope: !361)
!2313 = !DILocalVariable(name: "name", arg: 1, scope: !364, file: !1, line: 1975, type: !95)
!2314 = !DILocation(line: 1975, column: 26, scope: !364)
!2315 = !DILocalVariable(name: "n", arg: 2, scope: !364, file: !1, line: 1975, type: !45)
!2316 = !DILocation(line: 1975, column: 39, scope: !364)
!2317 = !DILocalVariable(name: "fn", arg: 3, scope: !364, file: !1, line: 1975, type: !80)
!2318 = !DILocation(line: 1975, column: 54, scope: !364)
!2319 = !DILocalVariable(name: "p", scope: !364, file: !1, line: 1977, type: !95)
!2320 = !DILocation(line: 1977, column: 8, scope: !364)
!2321 = !DILocalVariable(name: "l", scope: !364, file: !1, line: 1978, type: !45)
!2322 = !DILocation(line: 1978, column: 9, scope: !364)
!2323 = !DILocation(line: 1980, column: 13, scope: !364)
!2324 = !DILocation(line: 1980, column: 6, scope: !364)
!2325 = !DILocation(line: 1980, column: 4, scope: !364)
!2326 = !DILocation(line: 1981, column: 6, scope: !2327)
!2327 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1981, column: 6)
!2328 = !DILocation(line: 1981, column: 8, scope: !2327)
!2329 = !DILocation(line: 1981, column: 6, scope: !364)
!2330 = !DILocation(line: 1982, column: 19, scope: !2331)
!2331 = distinct !DILexicalBlock(scope: !2332, file: !1, line: 1982, column: 7)
!2332 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 1981, column: 17)
!2333 = !DILocation(line: 1982, column: 12, scope: !2331)
!2334 = !DILocation(line: 1982, column: 10, scope: !2331)
!2335 = !DILocation(line: 1982, column: 24, scope: !2331)
!2336 = !DILocation(line: 1982, column: 7, scope: !2332)
!2337 = !DILocation(line: 1983, column: 4, scope: !2331)
!2338 = !DILocation(line: 1984, column: 2, scope: !2332)
!2339 = !DILocation(line: 1985, column: 7, scope: !2327)
!2340 = !DILocation(line: 1985, column: 11, scope: !2327)
!2341 = !DILocation(line: 1985, column: 9, scope: !2327)
!2342 = !DILocation(line: 1985, column: 5, scope: !2327)
!2343 = !DILocation(line: 1986, column: 6, scope: !2344)
!2344 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1986, column: 6)
!2345 = !DILocation(line: 1986, column: 10, scope: !2344)
!2346 = !DILocation(line: 1986, column: 12, scope: !2344)
!2347 = !DILocation(line: 1986, column: 8, scope: !2344)
!2348 = !DILocation(line: 1986, column: 6, scope: !364)
!2349 = !DILocation(line: 1987, column: 3, scope: !2344)
!2350 = !DILocation(line: 1988, column: 9, scope: !364)
!2351 = !DILocation(line: 1988, column: 15, scope: !364)
!2352 = !DILocation(line: 1988, column: 19, scope: !364)
!2353 = !DILocation(line: 1988, column: 2, scope: !364)
!2354 = !DILocation(line: 1989, column: 7, scope: !364)
!2355 = !DILocation(line: 1989, column: 2, scope: !364)
!2356 = !DILocation(line: 1989, column: 10, scope: !364)
!2357 = !DILocation(line: 1991, column: 15, scope: !364)
!2358 = !DILocation(line: 1991, column: 10, scope: !364)
!2359 = !DILocation(line: 1991, column: 2, scope: !364)
!2360 = !DILocation(line: 1992, column: 1, scope: !364)
!2361 = !DILocalVariable(name: "parent", arg: 1, scope: !367, file: !1, line: 1963, type: !195)
!2362 = !DILocation(line: 1963, column: 44, scope: !367)
!2363 = !DILocalVariable(name: "child_name", arg: 2, scope: !367, file: !1, line: 1963, type: !80)
!2364 = !DILocation(line: 1963, column: 64, scope: !367)
!2365 = !DILocalVariable(name: "np", scope: !367, file: !1, line: 1965, type: !195)
!2366 = !DILocation(line: 1965, column: 22, scope: !367)
!2367 = !DILocation(line: 1967, column: 6, scope: !2368)
!2368 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1967, column: 6)
!2369 = !DILocation(line: 1967, column: 13, scope: !2368)
!2370 = !DILocation(line: 1967, column: 6, scope: !367)
!2371 = !DILocation(line: 1968, column: 3, scope: !2368)
!2372 = !DILocation(line: 1970, column: 8, scope: !367)
!2373 = !DILocation(line: 1970, column: 16, scope: !367)
!2374 = !DILocation(line: 1970, column: 26, scope: !367)
!2375 = !DILocation(line: 1970, column: 35, scope: !367)
!2376 = !DILocation(line: 1969, column: 29, scope: !367)
!2377 = !DILocation(line: 1969, column: 7, scope: !367)
!2378 = !DILocation(line: 1969, column: 5, scope: !367)
!2379 = !DILocation(line: 1971, column: 10, scope: !367)
!2380 = !DILocation(line: 1971, column: 2, scope: !367)
!2381 = !DILocation(line: 1972, column: 1, scope: !367)
!2382 = !DILocalVariable(name: "a", arg: 1, scope: !370, file: !1, line: 1888, type: !4)
!2383 = !DILocation(line: 1888, column: 54, scope: !370)
!2384 = !DILocalVariable(name: "pathname", arg: 2, scope: !370, file: !1, line: 1888, type: !80)
!2385 = !DILocation(line: 1888, column: 69, scope: !370)
!2386 = !DILocalVariable(name: "m_entry", arg: 3, scope: !370, file: !1, line: 1889, type: !243)
!2387 = !DILocation(line: 1889, column: 26, scope: !370)
!2388 = !DILocalVariable(name: "entry", scope: !370, file: !1, line: 1891, type: !30)
!2389 = !DILocation(line: 1891, column: 24, scope: !370)
!2390 = !DILocalVariable(name: "file", scope: !370, file: !1, line: 1892, type: !195)
!2391 = !DILocation(line: 1892, column: 22, scope: !370)
!2392 = !DILocalVariable(name: "r", scope: !370, file: !1, line: 1893, type: !23)
!2393 = !DILocation(line: 1893, column: 6, scope: !370)
!2394 = !DILocation(line: 1895, column: 10, scope: !370)
!2395 = !DILocation(line: 1895, column: 8, scope: !370)
!2396 = !DILocation(line: 1896, column: 6, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !370, file: !1, line: 1896, column: 6)
!2398 = !DILocation(line: 1896, column: 12, scope: !2397)
!2399 = !DILocation(line: 1896, column: 6, scope: !370)
!2400 = !DILocation(line: 1897, column: 4, scope: !2401)
!2401 = distinct !DILexicalBlock(scope: !2397, file: !1, line: 1896, column: 21)
!2402 = !DILocation(line: 1897, column: 12, scope: !2401)
!2403 = !DILocation(line: 1898, column: 22, scope: !2401)
!2404 = !DILocation(line: 1898, column: 25, scope: !2401)
!2405 = !DILocation(line: 1898, column: 3, scope: !2401)
!2406 = !DILocation(line: 1900, column: 3, scope: !2401)
!2407 = !DILocation(line: 1902, column: 30, scope: !370)
!2408 = !DILocation(line: 1902, column: 37, scope: !370)
!2409 = !DILocation(line: 1902, column: 2, scope: !370)
!2410 = !DILocation(line: 1903, column: 25, scope: !370)
!2411 = !DILocation(line: 1903, column: 2, scope: !370)
!2412 = !DILocation(line: 1904, column: 26, scope: !370)
!2413 = !DILocation(line: 1904, column: 33, scope: !370)
!2414 = !DILocation(line: 1904, column: 2, scope: !2415)
!2415 = !DILexicalBlockFile(scope: !370, file: !1, discriminator: 1)
!2416 = !DILocation(line: 1906, column: 22, scope: !370)
!2417 = !DILocation(line: 1906, column: 25, scope: !370)
!2418 = !DILocation(line: 1906, column: 6, scope: !370)
!2419 = !DILocation(line: 1906, column: 4, scope: !370)
!2420 = !DILocation(line: 1907, column: 21, scope: !370)
!2421 = !DILocation(line: 1907, column: 2, scope: !370)
!2422 = !DILocation(line: 1908, column: 6, scope: !2423)
!2423 = distinct !DILexicalBlock(scope: !370, file: !1, line: 1908, column: 6)
!2424 = !DILocation(line: 1908, column: 8, scope: !2423)
!2425 = !DILocation(line: 1908, column: 6, scope: !370)
!2426 = !DILocation(line: 1909, column: 4, scope: !2427)
!2427 = distinct !DILexicalBlock(scope: !2423, file: !1, line: 1908, column: 24)
!2428 = !DILocation(line: 1909, column: 12, scope: !2427)
!2429 = !DILocation(line: 1910, column: 22, scope: !2427)
!2430 = !DILocation(line: 1910, column: 25, scope: !2427)
!2431 = !DILocation(line: 1910, column: 3, scope: !2427)
!2432 = !DILocation(line: 1912, column: 3, scope: !2427)
!2433 = !DILocation(line: 1915, column: 2, scope: !370)
!2434 = !DILocation(line: 1915, column: 8, scope: !370)
!2435 = !DILocation(line: 1915, column: 18, scope: !370)
!2436 = !DILocation(line: 1915, column: 26, scope: !370)
!2437 = !DILocation(line: 1917, column: 13, scope: !370)
!2438 = !DILocation(line: 1917, column: 3, scope: !370)
!2439 = !DILocation(line: 1917, column: 11, scope: !370)
!2440 = !DILocation(line: 1918, column: 2, scope: !370)
!2441 = !DILocation(line: 1919, column: 1, scope: !370)
!2442 = !DILocalVariable(name: "a", arg: 1, scope: !373, file: !1, line: 2190, type: !4)
!2443 = !DILocation(line: 2190, column: 55, scope: !373)
!2444 = !DILocalVariable(name: "np", arg: 2, scope: !373, file: !1, line: 2190, type: !195)
!2445 = !DILocation(line: 2190, column: 78, scope: !373)
!2446 = !DILocalVariable(name: "file", arg: 3, scope: !373, file: !1, line: 2191, type: !195)
!2447 = !DILocation(line: 2191, column: 25, scope: !373)
!2448 = !DILocation(line: 2194, column: 7, scope: !2449)
!2449 = distinct !DILexicalBlock(scope: !373, file: !1, line: 2194, column: 6)
!2450 = !DILocation(line: 2194, column: 11, scope: !2449)
!2451 = !DILocation(line: 2194, column: 16, scope: !2449)
!2452 = !DILocation(line: 2194, column: 31, scope: !2449)
!2453 = !DILocation(line: 2194, column: 37, scope: !2449)
!2454 = !DILocation(line: 2194, column: 42, scope: !2449)
!2455 = !DILocation(line: 2194, column: 27, scope: !2449)
!2456 = !DILocation(line: 2194, column: 6, scope: !373)
!2457 = !DILocation(line: 2195, column: 22, scope: !2458)
!2458 = distinct !DILexicalBlock(scope: !2449, file: !1, line: 2194, column: 54)
!2459 = !DILocation(line: 2195, column: 25, scope: !2458)
!2460 = !DILocation(line: 2198, column: 7, scope: !2458)
!2461 = !DILocation(line: 2198, column: 11, scope: !2458)
!2462 = !DILocation(line: 2198, column: 20, scope: !2458)
!2463 = !DILocation(line: 2195, column: 3, scope: !2458)
!2464 = !DILocation(line: 2199, column: 3, scope: !2458)
!2465 = !DILocation(line: 2203, column: 2, scope: !373)
!2466 = !DILocation(line: 2204, column: 25, scope: !373)
!2467 = !DILocation(line: 2204, column: 29, scope: !373)
!2468 = !DILocation(line: 2204, column: 39, scope: !373)
!2469 = !DILocation(line: 2204, column: 45, scope: !373)
!2470 = !DILocation(line: 2204, column: 2, scope: !373)
!2471 = !DILocation(line: 2205, column: 2, scope: !373)
!2472 = !DILocation(line: 2206, column: 25, scope: !373)
!2473 = !DILocation(line: 2206, column: 29, scope: !373)
!2474 = !DILocation(line: 2206, column: 37, scope: !373)
!2475 = !DILocation(line: 2206, column: 43, scope: !373)
!2476 = !DILocation(line: 2206, column: 2, scope: !373)
!2477 = !DILocation(line: 2207, column: 2, scope: !373)
!2478 = !DILocation(line: 2208, column: 25, scope: !373)
!2479 = !DILocation(line: 2208, column: 29, scope: !373)
!2480 = !DILocation(line: 2208, column: 37, scope: !373)
!2481 = !DILocation(line: 2208, column: 43, scope: !373)
!2482 = !DILocation(line: 2208, column: 2, scope: !373)
!2483 = !DILocation(line: 2209, column: 2, scope: !373)
!2484 = !DILocation(line: 2210, column: 25, scope: !373)
!2485 = !DILocation(line: 2210, column: 29, scope: !373)
!2486 = !DILocation(line: 2210, column: 43, scope: !373)
!2487 = !DILocation(line: 2210, column: 49, scope: !373)
!2488 = !DILocation(line: 2210, column: 2, scope: !373)
!2489 = !DILocation(line: 2211, column: 14, scope: !373)
!2490 = !DILocation(line: 2211, column: 20, scope: !373)
!2491 = !DILocation(line: 2211, column: 2, scope: !373)
!2492 = !DILocation(line: 2211, column: 6, scope: !373)
!2493 = !DILocation(line: 2211, column: 12, scope: !373)
!2494 = !DILocation(line: 2212, column: 17, scope: !373)
!2495 = !DILocation(line: 2212, column: 23, scope: !373)
!2496 = !DILocation(line: 2212, column: 2, scope: !373)
!2497 = !DILocation(line: 2212, column: 6, scope: !373)
!2498 = !DILocation(line: 2212, column: 15, scope: !373)
!2499 = !DILocation(line: 2213, column: 13, scope: !373)
!2500 = !DILocation(line: 2213, column: 19, scope: !373)
!2501 = !DILocation(line: 2213, column: 2, scope: !373)
!2502 = !DILocation(line: 2213, column: 6, scope: !373)
!2503 = !DILocation(line: 2213, column: 11, scope: !373)
!2504 = !DILocation(line: 2214, column: 13, scope: !373)
!2505 = !DILocation(line: 2214, column: 19, scope: !373)
!2506 = !DILocation(line: 2214, column: 2, scope: !373)
!2507 = !DILocation(line: 2214, column: 6, scope: !373)
!2508 = !DILocation(line: 2214, column: 11, scope: !373)
!2509 = !DILocation(line: 2215, column: 12, scope: !373)
!2510 = !DILocation(line: 2215, column: 18, scope: !373)
!2511 = !DILocation(line: 2215, column: 2, scope: !373)
!2512 = !DILocation(line: 2215, column: 6, scope: !373)
!2513 = !DILocation(line: 2215, column: 10, scope: !373)
!2514 = !DILocation(line: 2216, column: 12, scope: !373)
!2515 = !DILocation(line: 2216, column: 18, scope: !373)
!2516 = !DILocation(line: 2216, column: 2, scope: !373)
!2517 = !DILocation(line: 2216, column: 6, scope: !373)
!2518 = !DILocation(line: 2216, column: 10, scope: !373)
!2519 = !DILocation(line: 2217, column: 19, scope: !373)
!2520 = !DILocation(line: 2217, column: 25, scope: !373)
!2521 = !DILocation(line: 2217, column: 2, scope: !373)
!2522 = !DILocation(line: 2217, column: 6, scope: !373)
!2523 = !DILocation(line: 2217, column: 17, scope: !373)
!2524 = !DILocation(line: 2218, column: 21, scope: !373)
!2525 = !DILocation(line: 2218, column: 27, scope: !373)
!2526 = !DILocation(line: 2218, column: 2, scope: !373)
!2527 = !DILocation(line: 2218, column: 6, scope: !373)
!2528 = !DILocation(line: 2218, column: 19, scope: !373)
!2529 = !DILocation(line: 2219, column: 14, scope: !373)
!2530 = !DILocation(line: 2219, column: 20, scope: !373)
!2531 = !DILocation(line: 2219, column: 2, scope: !373)
!2532 = !DILocation(line: 2219, column: 6, scope: !373)
!2533 = !DILocation(line: 2219, column: 12, scope: !373)
!2534 = !DILocation(line: 2220, column: 19, scope: !373)
!2535 = !DILocation(line: 2220, column: 25, scope: !373)
!2536 = !DILocation(line: 2220, column: 2, scope: !373)
!2537 = !DILocation(line: 2220, column: 6, scope: !373)
!2538 = !DILocation(line: 2220, column: 17, scope: !373)
!2539 = !DILocation(line: 2221, column: 18, scope: !373)
!2540 = !DILocation(line: 2221, column: 24, scope: !373)
!2541 = !DILocation(line: 2221, column: 2, scope: !373)
!2542 = !DILocation(line: 2221, column: 6, scope: !373)
!2543 = !DILocation(line: 2221, column: 16, scope: !373)
!2544 = !DILocation(line: 2222, column: 18, scope: !373)
!2545 = !DILocation(line: 2222, column: 24, scope: !373)
!2546 = !DILocation(line: 2222, column: 2, scope: !373)
!2547 = !DILocation(line: 2222, column: 6, scope: !373)
!2548 = !DILocation(line: 2222, column: 16, scope: !373)
!2549 = !DILocation(line: 2223, column: 17, scope: !373)
!2550 = !DILocation(line: 2223, column: 23, scope: !373)
!2551 = !DILocation(line: 2223, column: 2, scope: !373)
!2552 = !DILocation(line: 2223, column: 6, scope: !373)
!2553 = !DILocation(line: 2223, column: 15, scope: !373)
!2554 = !DILocation(line: 2224, column: 17, scope: !373)
!2555 = !DILocation(line: 2224, column: 23, scope: !373)
!2556 = !DILocation(line: 2224, column: 2, scope: !373)
!2557 = !DILocation(line: 2224, column: 6, scope: !373)
!2558 = !DILocation(line: 2224, column: 15, scope: !373)
!2559 = !DILocation(line: 2225, column: 12, scope: !373)
!2560 = !DILocation(line: 2225, column: 18, scope: !373)
!2561 = !DILocation(line: 2225, column: 2, scope: !373)
!2562 = !DILocation(line: 2225, column: 6, scope: !373)
!2563 = !DILocation(line: 2225, column: 10, scope: !373)
!2564 = !DILocation(line: 2227, column: 2, scope: !373)
!2565 = !DILocation(line: 2228, column: 1, scope: !373)
!2566 = !DILocalVariable(name: "a", arg: 1, scope: !378, file: !1, line: 1108, type: !4)
!2567 = !DILocation(line: 1108, column: 46, scope: !378)
!2568 = !DILocalVariable(name: "mtree", scope: !378, file: !1, line: 1110, type: !191)
!2569 = !DILocation(line: 1110, column: 23, scope: !378)
!2570 = !DILocation(line: 1110, column: 31, scope: !378)
!2571 = !DILocation(line: 1110, column: 34, scope: !378)
!2572 = !DILocalVariable(name: "np", scope: !378, file: !1, line: 1111, type: !195)
!2573 = !DILocation(line: 1111, column: 22, scope: !378)
!2574 = !DILocation(line: 1111, column: 27, scope: !378)
!2575 = !DILocation(line: 1111, column: 34, scope: !378)
!2576 = !DILocalVariable(name: "n", scope: !378, file: !1, line: 1112, type: !204)
!2577 = !DILocation(line: 1112, column: 26, scope: !378)
!2578 = !DILocalVariable(name: "ret", scope: !378, file: !1, line: 1113, type: !23)
!2579 = !DILocation(line: 1113, column: 6, scope: !378)
!2580 = !DILocation(line: 1115, column: 2, scope: !378)
!2581 = !DILocation(line: 1116, column: 7, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1116, column: 7)
!2583 = distinct !DILexicalBlock(scope: !378, file: !1, line: 1115, column: 5)
!2584 = !DILocation(line: 1116, column: 14, scope: !2582)
!2585 = !DILocation(line: 1116, column: 7, scope: !2583)
!2586 = !DILocation(line: 1121, column: 27, scope: !2587)
!2587 = distinct !DILexicalBlock(scope: !2582, file: !1, line: 1116, column: 33)
!2588 = !DILocation(line: 1121, column: 4, scope: !2587)
!2589 = !DILocation(line: 1122, column: 4, scope: !2590)
!2590 = distinct !DILexicalBlock(scope: !2587, file: !1, line: 1122, column: 4)
!2591 = !DILocation(line: 1122, column: 4, scope: !2592)
!2592 = !DILexicalBlockFile(scope: !2593, file: !1, discriminator: 1)
!2593 = distinct !DILexicalBlock(scope: !2590, file: !1, line: 1122, column: 4)
!2594 = !DILocalVariable(name: "e", scope: !2595, file: !1, line: 1123, type: !195)
!2595 = distinct !DILexicalBlock(scope: !2593, file: !1, line: 1122, column: 56)
!2596 = !DILocation(line: 1123, column: 25, scope: !2595)
!2597 = !DILocation(line: 1123, column: 51, scope: !2595)
!2598 = !DILocation(line: 1123, column: 29, scope: !2595)
!2599 = !DILocation(line: 1124, column: 34, scope: !2600)
!2600 = distinct !DILexicalBlock(scope: !2595, file: !1, line: 1124, column: 9)
!2601 = !DILocation(line: 1124, column: 41, scope: !2600)
!2602 = !DILocation(line: 1124, column: 9, scope: !2600)
!2603 = !DILocation(line: 1124, column: 44, scope: !2600)
!2604 = !DILocation(line: 1124, column: 9, scope: !2595)
!2605 = !DILocation(line: 1125, column: 25, scope: !2606)
!2606 = distinct !DILexicalBlock(scope: !2600, file: !1, line: 1124, column: 49)
!2607 = !DILocation(line: 1125, column: 28, scope: !2606)
!2608 = !DILocation(line: 1125, column: 6, scope: !2606)
!2609 = !DILocation(line: 1127, column: 6, scope: !2606)
!2610 = !DILocation(line: 1129, column: 4, scope: !2595)
!2611 = !DILocation(line: 1122, column: 4, scope: !2612)
!2612 = !DILexicalBlockFile(scope: !2593, file: !1, discriminator: 2)
!2613 = !DILocation(line: 1130, column: 3, scope: !2587)
!2614 = !DILocation(line: 1131, column: 8, scope: !2615)
!2615 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1131, column: 7)
!2616 = !DILocation(line: 1131, column: 12, scope: !2615)
!2617 = !DILocation(line: 1131, column: 22, scope: !2615)
!2618 = !DILocation(line: 1131, column: 30, scope: !2615)
!2619 = !DILocation(line: 1131, column: 33, scope: !2620)
!2620 = !DILexicalBlockFile(scope: !2615, file: !1, discriminator: 1)
!2621 = !DILocation(line: 1131, column: 40, scope: !2620)
!2622 = !DILocation(line: 1131, column: 7, scope: !2620)
!2623 = !DILocation(line: 1132, column: 28, scope: !2624)
!2624 = distinct !DILexicalBlock(scope: !2615, file: !1, line: 1131, column: 49)
!2625 = !DILocation(line: 1132, column: 31, scope: !2624)
!2626 = !DILocation(line: 1132, column: 10, scope: !2624)
!2627 = !DILocation(line: 1132, column: 8, scope: !2624)
!2628 = !DILocation(line: 1133, column: 8, scope: !2629)
!2629 = distinct !DILexicalBlock(scope: !2624, file: !1, line: 1133, column: 8)
!2630 = !DILocation(line: 1133, column: 12, scope: !2629)
!2631 = !DILocation(line: 1133, column: 8, scope: !2624)
!2632 = !DILocation(line: 1134, column: 5, scope: !2629)
!2633 = !DILocation(line: 1135, column: 3, scope: !2624)
!2634 = !DILocation(line: 1141, column: 8, scope: !2635)
!2635 = distinct !DILexicalBlock(scope: !2636, file: !1, line: 1141, column: 8)
!2636 = distinct !DILexicalBlock(scope: !2615, file: !1, line: 1135, column: 10)
!2637 = !DILocation(line: 1141, column: 15, scope: !2635)
!2638 = !DILocation(line: 1141, column: 8, scope: !2636)
!2639 = !DILocation(line: 1142, column: 18, scope: !2635)
!2640 = !DILocation(line: 1142, column: 5, scope: !2635)
!2641 = !DILocation(line: 1147, column: 3, scope: !2583)
!2642 = !DILocation(line: 1147, column: 10, scope: !2583)
!2643 = !DILocation(line: 1147, column: 15, scope: !2583)
!2644 = !DILocation(line: 1148, column: 3, scope: !2645)
!2645 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1148, column: 3)
!2646 = !DILocation(line: 1148, column: 3, scope: !2647)
!2647 = !DILexicalBlockFile(scope: !2648, file: !1, discriminator: 1)
!2648 = distinct !DILexicalBlock(scope: !2645, file: !1, line: 1148, column: 3)
!2649 = !DILocalVariable(name: "e", scope: !2650, file: !1, line: 1149, type: !195)
!2650 = distinct !DILexicalBlock(scope: !2648, file: !1, line: 1148, column: 55)
!2651 = !DILocation(line: 1149, column: 24, scope: !2650)
!2652 = !DILocation(line: 1149, column: 50, scope: !2650)
!2653 = !DILocation(line: 1149, column: 28, scope: !2650)
!2654 = !DILocation(line: 1151, column: 8, scope: !2655)
!2655 = distinct !DILexicalBlock(scope: !2650, file: !1, line: 1151, column: 8)
!2656 = !DILocation(line: 1151, column: 11, scope: !2655)
!2657 = !DILocation(line: 1151, column: 8, scope: !2650)
!2658 = !DILocation(line: 1152, column: 32, scope: !2655)
!2659 = !DILocation(line: 1152, column: 36, scope: !2655)
!2660 = !DILocation(line: 1152, column: 5, scope: !2655)
!2661 = !DILocation(line: 1154, column: 29, scope: !2662)
!2662 = distinct !DILexicalBlock(scope: !2655, file: !1, line: 1153, column: 9)
!2663 = !DILocation(line: 1154, column: 32, scope: !2662)
!2664 = !DILocation(line: 1154, column: 11, scope: !2662)
!2665 = !DILocation(line: 1154, column: 9, scope: !2662)
!2666 = !DILocation(line: 1155, column: 9, scope: !2667)
!2667 = distinct !DILexicalBlock(scope: !2662, file: !1, line: 1155, column: 9)
!2668 = !DILocation(line: 1155, column: 13, scope: !2667)
!2669 = !DILocation(line: 1155, column: 9, scope: !2662)
!2670 = !DILocation(line: 1156, column: 6, scope: !2667)
!2671 = !DILocation(line: 1158, column: 3, scope: !2650)
!2672 = !DILocation(line: 1148, column: 3, scope: !2673)
!2673 = !DILexicalBlockFile(scope: !2648, file: !1, discriminator: 2)
!2674 = !DILocation(line: 1159, column: 3, scope: !2583)
!2675 = !DILocation(line: 1159, column: 10, scope: !2583)
!2676 = !DILocation(line: 1159, column: 15, scope: !2583)
!2677 = !DILocation(line: 1161, column: 7, scope: !2678)
!2678 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1161, column: 7)
!2679 = !DILocation(line: 1161, column: 11, scope: !2678)
!2680 = !DILocation(line: 1161, column: 21, scope: !2678)
!2681 = !DILocation(line: 1161, column: 30, scope: !2678)
!2682 = !DILocation(line: 1161, column: 36, scope: !2678)
!2683 = !DILocation(line: 1161, column: 7, scope: !2583)
!2684 = !DILocation(line: 1165, column: 9, scope: !2685)
!2685 = distinct !DILexicalBlock(scope: !2678, file: !1, line: 1161, column: 45)
!2686 = !DILocation(line: 1165, column: 13, scope: !2685)
!2687 = !DILocation(line: 1165, column: 23, scope: !2685)
!2688 = !DILocation(line: 1165, column: 32, scope: !2685)
!2689 = !DILocation(line: 1165, column: 7, scope: !2685)
!2690 = !DILocation(line: 1166, column: 8, scope: !2691)
!2691 = distinct !DILexicalBlock(scope: !2685, file: !1, line: 1166, column: 8)
!2692 = !DILocation(line: 1166, column: 15, scope: !2691)
!2693 = !DILocation(line: 1166, column: 8, scope: !2685)
!2694 = !DILocation(line: 1167, column: 5, scope: !2691)
!2695 = !DILocation(line: 1167, column: 12, scope: !2691)
!2696 = !DILocation(line: 1167, column: 17, scope: !2691)
!2697 = !DILocation(line: 1168, column: 4, scope: !2685)
!2698 = !DILocation(line: 1169, column: 14, scope: !2699)
!2699 = distinct !DILexicalBlock(scope: !2678, file: !1, line: 1169, column: 14)
!2700 = !DILocation(line: 1169, column: 21, scope: !2699)
!2701 = !DILocation(line: 1169, column: 14, scope: !2678)
!2702 = !DILocation(line: 1176, column: 30, scope: !2703)
!2703 = distinct !DILexicalBlock(scope: !2699, file: !1, line: 1169, column: 30)
!2704 = !DILocation(line: 1176, column: 33, scope: !2703)
!2705 = !DILocation(line: 1176, column: 10, scope: !2703)
!2706 = !DILocation(line: 1176, column: 8, scope: !2703)
!2707 = !DILocation(line: 1177, column: 8, scope: !2708)
!2708 = distinct !DILexicalBlock(scope: !2703, file: !1, line: 1177, column: 8)
!2709 = !DILocation(line: 1177, column: 12, scope: !2708)
!2710 = !DILocation(line: 1177, column: 8, scope: !2703)
!2711 = !DILocation(line: 1178, column: 5, scope: !2708)
!2712 = !DILocation(line: 1179, column: 3, scope: !2703)
!2713 = !DILocation(line: 1181, column: 3, scope: !2583)
!2714 = !DILocation(line: 1181, column: 10, scope: !2715)
!2715 = !DILexicalBlockFile(scope: !2583, file: !1, discriminator: 1)
!2716 = !DILocation(line: 1181, column: 16, scope: !2715)
!2717 = !DILocation(line: 1181, column: 20, scope: !2715)
!2718 = !DILocation(line: 1181, column: 13, scope: !2715)
!2719 = !DILocation(line: 1181, column: 3, scope: !2715)
!2720 = !DILocation(line: 1182, column: 8, scope: !2721)
!2721 = distinct !DILexicalBlock(scope: !2722, file: !1, line: 1182, column: 8)
!2722 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1181, column: 28)
!2723 = !DILocation(line: 1182, column: 12, scope: !2721)
!2724 = !DILocation(line: 1182, column: 22, scope: !2721)
!2725 = !DILocation(line: 1182, column: 29, scope: !2721)
!2726 = !DILocation(line: 1182, column: 8, scope: !2722)
!2727 = !DILocation(line: 1186, column: 9, scope: !2728)
!2728 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 1186, column: 9)
!2729 = distinct !DILexicalBlock(scope: !2721, file: !1, line: 1182, column: 38)
!2730 = !DILocation(line: 1186, column: 16, scope: !2728)
!2731 = !DILocation(line: 1186, column: 9, scope: !2729)
!2732 = !DILocation(line: 1187, column: 6, scope: !2728)
!2733 = !DILocation(line: 1187, column: 13, scope: !2728)
!2734 = !DILocation(line: 1187, column: 18, scope: !2728)
!2735 = !DILocation(line: 1188, column: 9, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 1188, column: 9)
!2737 = !DILocation(line: 1188, column: 16, scope: !2736)
!2738 = !DILocation(line: 1188, column: 9, scope: !2729)
!2739 = !DILocation(line: 1189, column: 32, scope: !2740)
!2740 = distinct !DILexicalBlock(scope: !2736, file: !1, line: 1188, column: 25)
!2741 = !DILocation(line: 1190, column: 7, scope: !2740)
!2742 = !DILocation(line: 1190, column: 11, scope: !2740)
!2743 = !DILocation(line: 1189, column: 12, scope: !2740)
!2744 = !DILocation(line: 1189, column: 10, scope: !2740)
!2745 = !DILocation(line: 1191, column: 10, scope: !2746)
!2746 = distinct !DILexicalBlock(scope: !2740, file: !1, line: 1191, column: 10)
!2747 = !DILocation(line: 1191, column: 14, scope: !2746)
!2748 = !DILocation(line: 1191, column: 10, scope: !2740)
!2749 = !DILocation(line: 1192, column: 7, scope: !2746)
!2750 = !DILocation(line: 1193, column: 5, scope: !2740)
!2751 = !DILocation(line: 1194, column: 10, scope: !2729)
!2752 = !DILocation(line: 1194, column: 14, scope: !2729)
!2753 = !DILocation(line: 1194, column: 8, scope: !2729)
!2754 = !DILocation(line: 1195, column: 4, scope: !2729)
!2755 = !DILocation(line: 1199, column: 10, scope: !2756)
!2756 = distinct !DILexicalBlock(scope: !2721, file: !1, line: 1195, column: 11)
!2757 = !DILocation(line: 1199, column: 14, scope: !2756)
!2758 = !DILocation(line: 1199, column: 24, scope: !2756)
!2759 = !DILocation(line: 1199, column: 8, scope: !2756)
!2760 = !DILocation(line: 1200, column: 5, scope: !2756)
!2761 = !DILocation(line: 1181, column: 3, scope: !2762)
!2762 = !DILexicalBlockFile(scope: !2583, file: !1, discriminator: 2)
!2763 = !DILocation(line: 1203, column: 2, scope: !2583)
!2764 = !DILocation(line: 1203, column: 11, scope: !2765)
!2765 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!2766 = !DILocation(line: 1203, column: 17, scope: !2765)
!2767 = !DILocation(line: 1203, column: 21, scope: !2765)
!2768 = !DILocation(line: 1203, column: 14, scope: !2765)
!2769 = !DILocation(line: 1203, column: 2, scope: !2765)
!2770 = !DILocation(line: 1205, column: 2, scope: !378)
!2771 = !DILocation(line: 1206, column: 1, scope: !378)
!2772 = !DILocalVariable(name: "mtree", arg: 1, scope: !379, file: !1, line: 655, type: !191)
!2773 = !DILocation(line: 655, column: 47, scope: !379)
!2774 = !DILocalVariable(name: "me", arg: 2, scope: !379, file: !1, line: 655, type: !195)
!2775 = !DILocation(line: 655, column: 74, scope: !379)
!2776 = !DILocalVariable(name: "ac", scope: !379, file: !1, line: 657, type: !306)
!2777 = !DILocation(line: 657, column: 23, scope: !379)
!2778 = !DILocalVariable(name: "last", scope: !379, file: !1, line: 657, type: !306)
!2779 = !DILocation(line: 657, column: 28, scope: !379)
!2780 = !DILocalVariable(name: "acs", scope: !379, file: !1, line: 658, type: !1107)
!2781 = !DILocation(line: 658, column: 26, scope: !379)
!2782 = !DILocation(line: 658, column: 33, scope: !379)
!2783 = !DILocation(line: 658, column: 40, scope: !379)
!2784 = !DILocalVariable(name: "keys", scope: !379, file: !1, line: 659, type: !23)
!2785 = !DILocation(line: 659, column: 6, scope: !379)
!2786 = !DILocation(line: 659, column: 13, scope: !379)
!2787 = !DILocation(line: 659, column: 20, scope: !379)
!2788 = !DILocation(line: 661, column: 6, scope: !2789)
!2789 = distinct !DILexicalBlock(scope: !379, file: !1, line: 661, column: 6)
!2790 = !DILocation(line: 661, column: 11, scope: !2789)
!2791 = !DILocation(line: 661, column: 6, scope: !379)
!2792 = !DILocation(line: 662, column: 7, scope: !2793)
!2793 = distinct !DILexicalBlock(scope: !2794, file: !1, line: 662, column: 7)
!2794 = distinct !DILexicalBlock(scope: !2789, file: !1, line: 661, column: 32)
!2795 = !DILocation(line: 662, column: 12, scope: !2793)
!2796 = !DILocation(line: 662, column: 21, scope: !2793)
!2797 = !DILocation(line: 662, column: 7, scope: !2794)
!2798 = !DILocation(line: 663, column: 37, scope: !2799)
!2799 = distinct !DILexicalBlock(scope: !2793, file: !1, line: 662, column: 30)
!2800 = !DILocation(line: 663, column: 20, scope: !2799)
!2801 = !DILocation(line: 663, column: 4, scope: !2799)
!2802 = !DILocation(line: 663, column: 9, scope: !2799)
!2803 = !DILocation(line: 663, column: 18, scope: !2799)
!2804 = !DILocation(line: 664, column: 8, scope: !2805)
!2805 = distinct !DILexicalBlock(scope: !2799, file: !1, line: 664, column: 8)
!2806 = !DILocation(line: 664, column: 13, scope: !2805)
!2807 = !DILocation(line: 664, column: 22, scope: !2805)
!2808 = !DILocation(line: 664, column: 8, scope: !2799)
!2809 = !DILocation(line: 665, column: 5, scope: !2805)
!2810 = !DILocation(line: 666, column: 3, scope: !2799)
!2811 = !DILocation(line: 667, column: 9, scope: !2812)
!2812 = distinct !DILexicalBlock(scope: !2793, file: !1, line: 666, column: 10)
!2813 = !DILocation(line: 668, column: 14, scope: !2814)
!2814 = distinct !DILexicalBlock(scope: !2812, file: !1, line: 668, column: 4)
!2815 = !DILocation(line: 668, column: 19, scope: !2814)
!2816 = !DILocation(line: 668, column: 12, scope: !2814)
!2817 = !DILocation(line: 668, column: 9, scope: !2814)
!2818 = !DILocation(line: 668, column: 29, scope: !2819)
!2819 = !DILexicalBlockFile(scope: !2820, file: !1, discriminator: 1)
!2820 = distinct !DILexicalBlock(scope: !2814, file: !1, line: 668, column: 4)
!2821 = !DILocation(line: 668, column: 4, scope: !2819)
!2822 = !DILocation(line: 669, column: 9, scope: !2823)
!2823 = distinct !DILexicalBlock(scope: !2824, file: !1, line: 669, column: 9)
!2824 = distinct !DILexicalBlock(scope: !2820, file: !1, line: 668, column: 48)
!2825 = !DILocation(line: 669, column: 13, scope: !2823)
!2826 = !DILocation(line: 669, column: 22, scope: !2823)
!2827 = !DILocation(line: 669, column: 29, scope: !2823)
!2828 = !DILocation(line: 669, column: 33, scope: !2823)
!2829 = !DILocation(line: 669, column: 26, scope: !2823)
!2830 = !DILocation(line: 669, column: 9, scope: !2824)
!2831 = !DILocation(line: 670, column: 6, scope: !2823)
!2832 = !DILocation(line: 671, column: 12, scope: !2824)
!2833 = !DILocation(line: 671, column: 10, scope: !2824)
!2834 = !DILocation(line: 672, column: 4, scope: !2824)
!2835 = !DILocation(line: 668, column: 38, scope: !2836)
!2836 = !DILexicalBlockFile(scope: !2820, file: !1, discriminator: 2)
!2837 = !DILocation(line: 668, column: 42, scope: !2836)
!2838 = !DILocation(line: 668, column: 36, scope: !2836)
!2839 = !DILocation(line: 668, column: 4, scope: !2836)
!2840 = !DILocation(line: 673, column: 26, scope: !2841)
!2841 = distinct !DILexicalBlock(scope: !2812, file: !1, line: 673, column: 8)
!2842 = !DILocation(line: 673, column: 31, scope: !2841)
!2843 = !DILocation(line: 673, column: 41, scope: !2841)
!2844 = !DILocation(line: 673, column: 45, scope: !2841)
!2845 = !DILocation(line: 673, column: 51, scope: !2841)
!2846 = !DILocation(line: 673, column: 8, scope: !2841)
!2847 = !DILocation(line: 673, column: 55, scope: !2841)
!2848 = !DILocation(line: 673, column: 8, scope: !2812)
!2849 = !DILocation(line: 674, column: 5, scope: !2841)
!2850 = !DILocation(line: 676, column: 2, scope: !2794)
!2851 = !DILocation(line: 677, column: 6, scope: !2852)
!2852 = distinct !DILexicalBlock(scope: !379, file: !1, line: 677, column: 6)
!2853 = !DILocation(line: 677, column: 11, scope: !2852)
!2854 = !DILocation(line: 677, column: 6, scope: !379)
!2855 = !DILocation(line: 678, column: 7, scope: !2856)
!2856 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 678, column: 7)
!2857 = distinct !DILexicalBlock(scope: !2852, file: !1, line: 677, column: 32)
!2858 = !DILocation(line: 678, column: 12, scope: !2856)
!2859 = !DILocation(line: 678, column: 21, scope: !2856)
!2860 = !DILocation(line: 678, column: 7, scope: !2857)
!2861 = !DILocation(line: 679, column: 37, scope: !2862)
!2862 = distinct !DILexicalBlock(scope: !2856, file: !1, line: 678, column: 30)
!2863 = !DILocation(line: 679, column: 20, scope: !2862)
!2864 = !DILocation(line: 679, column: 4, scope: !2862)
!2865 = !DILocation(line: 679, column: 9, scope: !2862)
!2866 = !DILocation(line: 679, column: 18, scope: !2862)
!2867 = !DILocation(line: 680, column: 8, scope: !2868)
!2868 = distinct !DILexicalBlock(scope: !2862, file: !1, line: 680, column: 8)
!2869 = !DILocation(line: 680, column: 13, scope: !2868)
!2870 = !DILocation(line: 680, column: 22, scope: !2868)
!2871 = !DILocation(line: 680, column: 8, scope: !2862)
!2872 = !DILocation(line: 681, column: 5, scope: !2868)
!2873 = !DILocation(line: 682, column: 3, scope: !2862)
!2874 = !DILocation(line: 683, column: 9, scope: !2875)
!2875 = distinct !DILexicalBlock(scope: !2856, file: !1, line: 682, column: 10)
!2876 = !DILocation(line: 684, column: 14, scope: !2877)
!2877 = distinct !DILexicalBlock(scope: !2875, file: !1, line: 684, column: 4)
!2878 = !DILocation(line: 684, column: 19, scope: !2877)
!2879 = !DILocation(line: 684, column: 12, scope: !2877)
!2880 = !DILocation(line: 684, column: 9, scope: !2877)
!2881 = !DILocation(line: 684, column: 29, scope: !2882)
!2882 = !DILexicalBlockFile(scope: !2883, file: !1, discriminator: 1)
!2883 = distinct !DILexicalBlock(scope: !2877, file: !1, line: 684, column: 4)
!2884 = !DILocation(line: 684, column: 4, scope: !2882)
!2885 = !DILocation(line: 685, column: 9, scope: !2886)
!2886 = distinct !DILexicalBlock(scope: !2887, file: !1, line: 685, column: 9)
!2887 = distinct !DILexicalBlock(scope: !2883, file: !1, line: 684, column: 48)
!2888 = !DILocation(line: 685, column: 13, scope: !2886)
!2889 = !DILocation(line: 685, column: 22, scope: !2886)
!2890 = !DILocation(line: 685, column: 29, scope: !2886)
!2891 = !DILocation(line: 685, column: 33, scope: !2886)
!2892 = !DILocation(line: 685, column: 26, scope: !2886)
!2893 = !DILocation(line: 685, column: 9, scope: !2887)
!2894 = !DILocation(line: 686, column: 6, scope: !2886)
!2895 = !DILocation(line: 687, column: 12, scope: !2887)
!2896 = !DILocation(line: 687, column: 10, scope: !2887)
!2897 = !DILocation(line: 688, column: 4, scope: !2887)
!2898 = !DILocation(line: 684, column: 38, scope: !2899)
!2899 = !DILexicalBlockFile(scope: !2883, file: !1, discriminator: 2)
!2900 = !DILocation(line: 684, column: 42, scope: !2899)
!2901 = !DILocation(line: 684, column: 36, scope: !2899)
!2902 = !DILocation(line: 684, column: 4, scope: !2899)
!2903 = !DILocation(line: 689, column: 26, scope: !2904)
!2904 = distinct !DILexicalBlock(scope: !2875, file: !1, line: 689, column: 8)
!2905 = !DILocation(line: 689, column: 31, scope: !2904)
!2906 = !DILocation(line: 689, column: 41, scope: !2904)
!2907 = !DILocation(line: 689, column: 45, scope: !2904)
!2908 = !DILocation(line: 689, column: 51, scope: !2904)
!2909 = !DILocation(line: 689, column: 8, scope: !2904)
!2910 = !DILocation(line: 689, column: 55, scope: !2904)
!2911 = !DILocation(line: 689, column: 8, scope: !2875)
!2912 = !DILocation(line: 690, column: 5, scope: !2904)
!2913 = !DILocation(line: 692, column: 2, scope: !2857)
!2914 = !DILocation(line: 693, column: 6, scope: !2915)
!2915 = distinct !DILexicalBlock(scope: !379, file: !1, line: 693, column: 6)
!2916 = !DILocation(line: 693, column: 11, scope: !2915)
!2917 = !DILocation(line: 693, column: 6, scope: !379)
!2918 = !DILocation(line: 694, column: 7, scope: !2919)
!2919 = distinct !DILexicalBlock(scope: !2920, file: !1, line: 694, column: 7)
!2920 = distinct !DILexicalBlock(scope: !2915, file: !1, line: 693, column: 21)
!2921 = !DILocation(line: 694, column: 12, scope: !2919)
!2922 = !DILocation(line: 694, column: 22, scope: !2919)
!2923 = !DILocation(line: 694, column: 7, scope: !2920)
!2924 = !DILocation(line: 695, column: 38, scope: !2925)
!2925 = distinct !DILexicalBlock(scope: !2919, file: !1, line: 694, column: 31)
!2926 = !DILocation(line: 695, column: 21, scope: !2925)
!2927 = !DILocation(line: 695, column: 4, scope: !2925)
!2928 = !DILocation(line: 695, column: 9, scope: !2925)
!2929 = !DILocation(line: 695, column: 19, scope: !2925)
!2930 = !DILocation(line: 696, column: 8, scope: !2931)
!2931 = distinct !DILexicalBlock(scope: !2925, file: !1, line: 696, column: 8)
!2932 = !DILocation(line: 696, column: 13, scope: !2931)
!2933 = !DILocation(line: 696, column: 23, scope: !2931)
!2934 = !DILocation(line: 696, column: 8, scope: !2925)
!2935 = !DILocation(line: 697, column: 5, scope: !2931)
!2936 = !DILocation(line: 698, column: 3, scope: !2925)
!2937 = !DILocation(line: 699, column: 9, scope: !2938)
!2938 = distinct !DILexicalBlock(scope: !2919, file: !1, line: 698, column: 10)
!2939 = !DILocation(line: 700, column: 14, scope: !2940)
!2940 = distinct !DILexicalBlock(scope: !2938, file: !1, line: 700, column: 4)
!2941 = !DILocation(line: 700, column: 19, scope: !2940)
!2942 = !DILocation(line: 700, column: 12, scope: !2940)
!2943 = !DILocation(line: 700, column: 9, scope: !2940)
!2944 = !DILocation(line: 700, column: 30, scope: !2945)
!2945 = !DILexicalBlockFile(scope: !2946, file: !1, discriminator: 1)
!2946 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 700, column: 4)
!2947 = !DILocation(line: 700, column: 4, scope: !2945)
!2948 = !DILocation(line: 701, column: 9, scope: !2949)
!2949 = distinct !DILexicalBlock(scope: !2950, file: !1, line: 701, column: 9)
!2950 = distinct !DILexicalBlock(scope: !2946, file: !1, line: 700, column: 49)
!2951 = !DILocation(line: 701, column: 13, scope: !2949)
!2952 = !DILocation(line: 701, column: 22, scope: !2949)
!2953 = !DILocation(line: 701, column: 30, scope: !2949)
!2954 = !DILocation(line: 701, column: 34, scope: !2949)
!2955 = !DILocation(line: 701, column: 27, scope: !2949)
!2956 = !DILocation(line: 701, column: 9, scope: !2950)
!2957 = !DILocation(line: 702, column: 6, scope: !2949)
!2958 = !DILocation(line: 703, column: 12, scope: !2950)
!2959 = !DILocation(line: 703, column: 10, scope: !2950)
!2960 = !DILocation(line: 704, column: 4, scope: !2950)
!2961 = !DILocation(line: 700, column: 39, scope: !2962)
!2962 = !DILexicalBlockFile(scope: !2946, file: !1, discriminator: 2)
!2963 = !DILocation(line: 700, column: 43, scope: !2962)
!2964 = !DILocation(line: 700, column: 37, scope: !2962)
!2965 = !DILocation(line: 700, column: 4, scope: !2962)
!2966 = !DILocation(line: 705, column: 26, scope: !2967)
!2967 = distinct !DILexicalBlock(scope: !2938, file: !1, line: 705, column: 8)
!2968 = !DILocation(line: 705, column: 31, scope: !2967)
!2969 = !DILocation(line: 705, column: 42, scope: !2967)
!2970 = !DILocation(line: 705, column: 46, scope: !2967)
!2971 = !DILocation(line: 705, column: 52, scope: !2967)
!2972 = !DILocation(line: 705, column: 8, scope: !2967)
!2973 = !DILocation(line: 705, column: 56, scope: !2967)
!2974 = !DILocation(line: 705, column: 8, scope: !2938)
!2975 = !DILocation(line: 706, column: 5, scope: !2967)
!2976 = !DILocation(line: 708, column: 2, scope: !2920)
!2977 = !DILocation(line: 709, column: 6, scope: !2978)
!2978 = distinct !DILexicalBlock(scope: !379, file: !1, line: 709, column: 6)
!2979 = !DILocation(line: 709, column: 11, scope: !2978)
!2980 = !DILocation(line: 709, column: 6, scope: !379)
!2981 = !DILocation(line: 710, column: 7, scope: !2982)
!2982 = distinct !DILexicalBlock(scope: !2983, file: !1, line: 710, column: 7)
!2983 = distinct !DILexicalBlock(scope: !2978, file: !1, line: 709, column: 22)
!2984 = !DILocation(line: 710, column: 12, scope: !2982)
!2985 = !DILocation(line: 710, column: 23, scope: !2982)
!2986 = !DILocation(line: 710, column: 7, scope: !2983)
!2987 = !DILocation(line: 711, column: 39, scope: !2988)
!2988 = distinct !DILexicalBlock(scope: !2982, file: !1, line: 710, column: 32)
!2989 = !DILocation(line: 711, column: 22, scope: !2988)
!2990 = !DILocation(line: 711, column: 4, scope: !2988)
!2991 = !DILocation(line: 711, column: 9, scope: !2988)
!2992 = !DILocation(line: 711, column: 20, scope: !2988)
!2993 = !DILocation(line: 712, column: 8, scope: !2994)
!2994 = distinct !DILexicalBlock(scope: !2988, file: !1, line: 712, column: 8)
!2995 = !DILocation(line: 712, column: 13, scope: !2994)
!2996 = !DILocation(line: 712, column: 24, scope: !2994)
!2997 = !DILocation(line: 712, column: 8, scope: !2988)
!2998 = !DILocation(line: 713, column: 5, scope: !2994)
!2999 = !DILocation(line: 714, column: 3, scope: !2988)
!3000 = !DILocation(line: 715, column: 9, scope: !3001)
!3001 = distinct !DILexicalBlock(scope: !2982, file: !1, line: 714, column: 10)
!3002 = !DILocation(line: 716, column: 14, scope: !3003)
!3003 = distinct !DILexicalBlock(scope: !3001, file: !1, line: 716, column: 4)
!3004 = !DILocation(line: 716, column: 19, scope: !3003)
!3005 = !DILocation(line: 716, column: 12, scope: !3003)
!3006 = !DILocation(line: 716, column: 9, scope: !3003)
!3007 = !DILocation(line: 716, column: 31, scope: !3008)
!3008 = !DILexicalBlockFile(scope: !3009, file: !1, discriminator: 1)
!3009 = distinct !DILexicalBlock(scope: !3003, file: !1, line: 716, column: 4)
!3010 = !DILocation(line: 716, column: 4, scope: !3008)
!3011 = !DILocation(line: 717, column: 9, scope: !3012)
!3012 = distinct !DILexicalBlock(scope: !3013, file: !1, line: 717, column: 9)
!3013 = distinct !DILexicalBlock(scope: !3009, file: !1, line: 716, column: 50)
!3014 = !DILocation(line: 717, column: 13, scope: !3012)
!3015 = !DILocation(line: 717, column: 22, scope: !3012)
!3016 = !DILocation(line: 717, column: 36, scope: !3012)
!3017 = !DILocation(line: 717, column: 40, scope: !3012)
!3018 = !DILocation(line: 717, column: 33, scope: !3012)
!3019 = !DILocation(line: 717, column: 51, scope: !3012)
!3020 = !DILocation(line: 718, column: 9, scope: !3012)
!3021 = !DILocation(line: 718, column: 13, scope: !3012)
!3022 = !DILocation(line: 718, column: 22, scope: !3012)
!3023 = !DILocation(line: 719, column: 8, scope: !3012)
!3024 = !DILocation(line: 719, column: 12, scope: !3012)
!3025 = !DILocation(line: 718, column: 35, scope: !3012)
!3026 = !DILocation(line: 717, column: 9, scope: !3027)
!3027 = !DILexicalBlockFile(scope: !3013, file: !1, discriminator: 1)
!3028 = !DILocation(line: 720, column: 6, scope: !3012)
!3029 = !DILocation(line: 721, column: 12, scope: !3013)
!3030 = !DILocation(line: 721, column: 10, scope: !3013)
!3031 = !DILocation(line: 722, column: 4, scope: !3013)
!3032 = !DILocation(line: 716, column: 40, scope: !3033)
!3033 = !DILexicalBlockFile(scope: !3009, file: !1, discriminator: 2)
!3034 = !DILocation(line: 716, column: 44, scope: !3033)
!3035 = !DILocation(line: 716, column: 38, scope: !3033)
!3036 = !DILocation(line: 716, column: 4, scope: !3033)
!3037 = !DILocation(line: 723, column: 26, scope: !3038)
!3038 = distinct !DILexicalBlock(scope: !3001, file: !1, line: 723, column: 8)
!3039 = !DILocation(line: 723, column: 31, scope: !3038)
!3040 = !DILocation(line: 723, column: 43, scope: !3038)
!3041 = !DILocation(line: 723, column: 47, scope: !3038)
!3042 = !DILocation(line: 723, column: 53, scope: !3038)
!3043 = !DILocation(line: 723, column: 8, scope: !3038)
!3044 = !DILocation(line: 723, column: 57, scope: !3038)
!3045 = !DILocation(line: 723, column: 8, scope: !3001)
!3046 = !DILocation(line: 724, column: 5, scope: !3038)
!3047 = !DILocation(line: 726, column: 2, scope: !2983)
!3048 = !DILocation(line: 728, column: 2, scope: !379)
!3049 = !DILocation(line: 729, column: 1, scope: !379)
!3050 = !DILocalVariable(name: "a", arg: 1, scope: !388, file: !1, line: 923, type: !4)
!3051 = !DILocation(line: 923, column: 41, scope: !388)
!3052 = !DILocalVariable(name: "me", arg: 2, scope: !388, file: !1, line: 923, type: !195)
!3053 = !DILocation(line: 923, column: 64, scope: !388)
!3054 = !DILocalVariable(name: "mtree", scope: !388, file: !1, line: 925, type: !191)
!3055 = !DILocation(line: 925, column: 23, scope: !388)
!3056 = !DILocation(line: 925, column: 31, scope: !388)
!3057 = !DILocation(line: 925, column: 34, scope: !388)
!3058 = !DILocalVariable(name: "str", scope: !388, file: !1, line: 926, type: !394)
!3059 = !DILocation(line: 926, column: 25, scope: !388)
!3060 = !DILocalVariable(name: "keys", scope: !388, file: !1, line: 927, type: !23)
!3061 = !DILocation(line: 927, column: 6, scope: !388)
!3062 = !DILocalVariable(name: "ret", scope: !388, file: !1, line: 927, type: !23)
!3063 = !DILocation(line: 927, column: 12, scope: !388)
!3064 = !DILocation(line: 929, column: 6, scope: !3065)
!3065 = distinct !DILexicalBlock(scope: !388, file: !1, line: 929, column: 6)
!3066 = !DILocation(line: 929, column: 10, scope: !3065)
!3067 = !DILocation(line: 929, column: 6, scope: !388)
!3068 = !DILocation(line: 930, column: 7, scope: !3069)
!3069 = distinct !DILexicalBlock(scope: !3070, file: !1, line: 930, column: 7)
!3070 = distinct !DILexicalBlock(scope: !3065, file: !1, line: 929, column: 20)
!3071 = !DILocation(line: 930, column: 14, scope: !3069)
!3072 = !DILocation(line: 930, column: 7, scope: !3070)
!3073 = !DILocation(line: 936, column: 9, scope: !3074)
!3074 = distinct !DILexicalBlock(scope: !3075, file: !1, line: 936, column: 8)
!3075 = distinct !DILexicalBlock(scope: !3069, file: !1, line: 930, column: 23)
!3076 = !DILocation(line: 936, column: 16, scope: !3074)
!3077 = !DILocation(line: 936, column: 8, scope: !3075)
!3078 = !DILocation(line: 937, column: 29, scope: !3074)
!3079 = !DILocation(line: 937, column: 36, scope: !3074)
!3080 = !DILocation(line: 937, column: 5, scope: !3074)
!3081 = !DILocation(line: 938, column: 8, scope: !3082)
!3082 = distinct !DILexicalBlock(scope: !3075, file: !1, line: 938, column: 8)
!3083 = !DILocation(line: 938, column: 12, scope: !3082)
!3084 = !DILocation(line: 938, column: 22, scope: !3082)
!3085 = !DILocation(line: 938, column: 8, scope: !3075)
!3086 = !DILocation(line: 939, column: 29, scope: !3082)
!3087 = !DILocation(line: 939, column: 36, scope: !3082)
!3088 = !DILocation(line: 941, column: 9, scope: !3082)
!3089 = !DILocation(line: 941, column: 13, scope: !3082)
!3090 = !DILocation(line: 941, column: 23, scope: !3082)
!3091 = !DILocation(line: 941, column: 26, scope: !3082)
!3092 = !DILocation(line: 941, column: 30, scope: !3082)
!3093 = !DILocation(line: 941, column: 39, scope: !3082)
!3094 = !DILocation(line: 939, column: 5, scope: !3082)
!3095 = !DILocation(line: 943, column: 29, scope: !3082)
!3096 = !DILocation(line: 943, column: 36, scope: !3082)
!3097 = !DILocation(line: 945, column: 9, scope: !3082)
!3098 = !DILocation(line: 945, column: 13, scope: !3082)
!3099 = !DILocation(line: 945, column: 22, scope: !3082)
!3100 = !DILocation(line: 943, column: 5, scope: !3082)
!3101 = !DILocation(line: 946, column: 3, scope: !3075)
!3102 = !DILocation(line: 947, column: 7, scope: !3103)
!3103 = distinct !DILexicalBlock(scope: !3070, file: !1, line: 947, column: 7)
!3104 = !DILocation(line: 947, column: 14, scope: !3103)
!3105 = !DILocation(line: 947, column: 7, scope: !3070)
!3106 = !DILocation(line: 948, column: 17, scope: !3103)
!3107 = !DILocation(line: 948, column: 4, scope: !3103)
!3108 = !DILocation(line: 949, column: 2, scope: !3070)
!3109 = !DILocation(line: 950, column: 2, scope: !388)
!3110 = !DILocation(line: 951, column: 9, scope: !388)
!3111 = !DILocation(line: 951, column: 16, scope: !388)
!3112 = !DILocation(line: 951, column: 23, scope: !388)
!3113 = !DILocation(line: 951, column: 26, scope: !3114)
!3114 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 1)
!3115 = !DILocation(line: 951, column: 33, scope: !3114)
!3116 = !DILocation(line: 951, column: 8, scope: !3114)
!3117 = !DILocation(line: 951, column: 44, scope: !3118)
!3118 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 2)
!3119 = !DILocation(line: 951, column: 51, scope: !3118)
!3120 = !DILocation(line: 951, column: 8, scope: !3118)
!3121 = !DILocation(line: 951, column: 59, scope: !3122)
!3122 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 3)
!3123 = !DILocation(line: 951, column: 66, scope: !3122)
!3124 = !DILocation(line: 951, column: 8, scope: !3122)
!3125 = !DILocation(line: 951, column: 8, scope: !3126)
!3126 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 4)
!3127 = !DILocation(line: 951, column: 6, scope: !3126)
!3128 = !DILocation(line: 953, column: 7, scope: !3129)
!3129 = distinct !DILexicalBlock(scope: !388, file: !1, line: 953, column: 6)
!3130 = !DILocation(line: 953, column: 14, scope: !3129)
!3131 = !DILocation(line: 953, column: 22, scope: !3129)
!3132 = !DILocation(line: 953, column: 25, scope: !3133)
!3133 = !DILexicalBlockFile(scope: !3129, file: !1, discriminator: 1)
!3134 = !DILocation(line: 953, column: 29, scope: !3133)
!3135 = !DILocation(line: 953, column: 39, scope: !3133)
!3136 = !DILocation(line: 953, column: 6, scope: !3133)
!3137 = !DILocation(line: 958, column: 15, scope: !3138)
!3138 = distinct !DILexicalBlock(scope: !3129, file: !1, line: 953, column: 42)
!3139 = !DILocation(line: 958, column: 20, scope: !3138)
!3140 = !DILocation(line: 958, column: 24, scope: !3138)
!3141 = !DILocation(line: 958, column: 34, scope: !3138)
!3142 = !DILocation(line: 958, column: 3, scope: !3138)
!3143 = !DILocation(line: 959, column: 26, scope: !3138)
!3144 = !DILocation(line: 959, column: 3, scope: !3138)
!3145 = !DILocation(line: 960, column: 2, scope: !3138)
!3146 = !DILocation(line: 961, column: 14, scope: !388)
!3147 = !DILocation(line: 961, column: 19, scope: !388)
!3148 = !DILocation(line: 961, column: 23, scope: !388)
!3149 = !DILocation(line: 961, column: 32, scope: !388)
!3150 = !DILocation(line: 961, column: 2, scope: !388)
!3151 = !DILocation(line: 963, column: 29, scope: !388)
!3152 = !DILocation(line: 963, column: 36, scope: !388)
!3153 = !DILocation(line: 963, column: 9, scope: !388)
!3154 = !DILocation(line: 963, column: 7, scope: !388)
!3155 = !DILocation(line: 964, column: 7, scope: !3156)
!3156 = distinct !DILexicalBlock(scope: !388, file: !1, line: 964, column: 6)
!3157 = !DILocation(line: 964, column: 12, scope: !3156)
!3158 = !DILocation(line: 964, column: 23, scope: !3156)
!3159 = !DILocation(line: 964, column: 28, scope: !3156)
!3160 = !DILocation(line: 965, column: 6, scope: !3156)
!3161 = !DILocation(line: 965, column: 10, scope: !3156)
!3162 = !DILocation(line: 965, column: 16, scope: !3156)
!3163 = !DILocation(line: 965, column: 21, scope: !3156)
!3164 = !DILocation(line: 965, column: 24, scope: !3165)
!3165 = !DILexicalBlockFile(scope: !3156, file: !1, discriminator: 1)
!3166 = !DILocation(line: 965, column: 28, scope: !3165)
!3167 = !DILocation(line: 965, column: 37, scope: !3165)
!3168 = !DILocation(line: 964, column: 6, scope: !3114)
!3169 = !DILocation(line: 966, column: 26, scope: !3156)
!3170 = !DILocation(line: 966, column: 44, scope: !3156)
!3171 = !DILocation(line: 966, column: 48, scope: !3156)
!3172 = !DILocation(line: 966, column: 3, scope: !3156)
!3173 = !DILocation(line: 968, column: 7, scope: !3174)
!3174 = distinct !DILexicalBlock(scope: !388, file: !1, line: 968, column: 6)
!3175 = !DILocation(line: 968, column: 12, scope: !3174)
!3176 = !DILocation(line: 968, column: 23, scope: !3174)
!3177 = !DILocation(line: 968, column: 28, scope: !3174)
!3178 = !DILocation(line: 968, column: 31, scope: !3179)
!3179 = !DILexicalBlockFile(scope: !3174, file: !1, discriminator: 1)
!3180 = !DILocation(line: 968, column: 58, scope: !3179)
!3181 = !DILocation(line: 968, column: 6, scope: !3179)
!3182 = !DILocation(line: 969, column: 18, scope: !3183)
!3183 = distinct !DILexicalBlock(scope: !3174, file: !1, line: 968, column: 63)
!3184 = !DILocation(line: 969, column: 3, scope: !3183)
!3185 = !DILocation(line: 970, column: 15, scope: !3183)
!3186 = !DILocation(line: 970, column: 20, scope: !3183)
!3187 = !DILocation(line: 970, column: 24, scope: !3183)
!3188 = !DILocation(line: 970, column: 30, scope: !3183)
!3189 = !DILocation(line: 970, column: 3, scope: !3183)
!3190 = !DILocation(line: 971, column: 2, scope: !3183)
!3191 = !DILocation(line: 972, column: 7, scope: !3192)
!3192 = distinct !DILexicalBlock(scope: !388, file: !1, line: 972, column: 6)
!3193 = !DILocation(line: 972, column: 12, scope: !3192)
!3194 = !DILocation(line: 972, column: 23, scope: !3192)
!3195 = !DILocation(line: 972, column: 28, scope: !3192)
!3196 = !DILocation(line: 972, column: 31, scope: !3197)
!3197 = !DILexicalBlockFile(scope: !3192, file: !1, discriminator: 1)
!3198 = !DILocation(line: 972, column: 58, scope: !3197)
!3199 = !DILocation(line: 972, column: 6, scope: !3197)
!3200 = !DILocation(line: 973, column: 18, scope: !3201)
!3201 = distinct !DILexicalBlock(scope: !3192, file: !1, line: 972, column: 63)
!3202 = !DILocation(line: 973, column: 3, scope: !3201)
!3203 = !DILocation(line: 974, column: 15, scope: !3201)
!3204 = !DILocation(line: 974, column: 20, scope: !3201)
!3205 = !DILocation(line: 974, column: 24, scope: !3201)
!3206 = !DILocation(line: 974, column: 30, scope: !3201)
!3207 = !DILocation(line: 974, column: 3, scope: !3201)
!3208 = !DILocation(line: 975, column: 2, scope: !3201)
!3209 = !DILocation(line: 976, column: 7, scope: !3210)
!3210 = distinct !DILexicalBlock(scope: !388, file: !1, line: 976, column: 6)
!3211 = !DILocation(line: 976, column: 12, scope: !3210)
!3212 = !DILocation(line: 976, column: 23, scope: !3210)
!3213 = !DILocation(line: 976, column: 6, scope: !388)
!3214 = !DILocation(line: 977, column: 7, scope: !3215)
!3215 = distinct !DILexicalBlock(scope: !3216, file: !1, line: 977, column: 7)
!3216 = distinct !DILexicalBlock(scope: !3210, file: !1, line: 976, column: 29)
!3217 = !DILocation(line: 977, column: 40, scope: !3215)
!3218 = !DILocation(line: 977, column: 7, scope: !3216)
!3219 = !DILocation(line: 978, column: 19, scope: !3220)
!3220 = distinct !DILexicalBlock(scope: !3215, file: !1, line: 977, column: 45)
!3221 = !DILocation(line: 978, column: 4, scope: !3220)
!3222 = !DILocation(line: 979, column: 16, scope: !3220)
!3223 = !DILocation(line: 979, column: 21, scope: !3220)
!3224 = !DILocation(line: 979, column: 25, scope: !3220)
!3225 = !DILocation(line: 979, column: 37, scope: !3220)
!3226 = !DILocation(line: 979, column: 4, scope: !3220)
!3227 = !DILocation(line: 980, column: 3, scope: !3220)
!3228 = !DILocation(line: 980, column: 14, scope: !3229)
!3229 = !DILexicalBlockFile(scope: !3230, file: !1, discriminator: 1)
!3230 = distinct !DILexicalBlock(scope: !3215, file: !1, line: 980, column: 14)
!3231 = !DILocation(line: 980, column: 21, scope: !3229)
!3232 = !DILocation(line: 980, column: 25, scope: !3229)
!3233 = !DILocation(line: 980, column: 36, scope: !3229)
!3234 = !DILocation(line: 981, column: 8, scope: !3230)
!3235 = !DILocation(line: 981, column: 15, scope: !3230)
!3236 = !DILocation(line: 981, column: 19, scope: !3230)
!3237 = !DILocation(line: 981, column: 24, scope: !3230)
!3238 = !DILocation(line: 981, column: 35, scope: !3230)
!3239 = !DILocation(line: 980, column: 14, scope: !3240)
!3240 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 2)
!3241 = !DILocation(line: 983, column: 19, scope: !3230)
!3242 = !DILocation(line: 983, column: 4, scope: !3230)
!3243 = !DILocation(line: 984, column: 2, scope: !3216)
!3244 = !DILocation(line: 985, column: 7, scope: !3245)
!3245 = distinct !DILexicalBlock(scope: !388, file: !1, line: 985, column: 6)
!3246 = !DILocation(line: 985, column: 12, scope: !3245)
!3247 = !DILocation(line: 985, column: 22, scope: !3245)
!3248 = !DILocation(line: 985, column: 6, scope: !388)
!3249 = !DILocation(line: 986, column: 26, scope: !3245)
!3250 = !DILocation(line: 987, column: 17, scope: !3245)
!3251 = !DILocation(line: 987, column: 21, scope: !3245)
!3252 = !DILocation(line: 987, column: 38, scope: !3245)
!3253 = !DILocation(line: 987, column: 42, scope: !3245)
!3254 = !DILocation(line: 986, column: 3, scope: !3245)
!3255 = !DILocation(line: 988, column: 7, scope: !3256)
!3256 = distinct !DILexicalBlock(scope: !388, file: !1, line: 988, column: 6)
!3257 = !DILocation(line: 988, column: 12, scope: !3256)
!3258 = !DILocation(line: 988, column: 22, scope: !3256)
!3259 = !DILocation(line: 988, column: 6, scope: !388)
!3260 = !DILocation(line: 989, column: 26, scope: !3256)
!3261 = !DILocation(line: 989, column: 57, scope: !3256)
!3262 = !DILocation(line: 989, column: 61, scope: !3256)
!3263 = !DILocation(line: 989, column: 3, scope: !3256)
!3264 = !DILocation(line: 990, column: 7, scope: !3265)
!3265 = distinct !DILexicalBlock(scope: !388, file: !1, line: 990, column: 6)
!3266 = !DILocation(line: 990, column: 12, scope: !3265)
!3267 = !DILocation(line: 990, column: 21, scope: !3265)
!3268 = !DILocation(line: 990, column: 6, scope: !388)
!3269 = !DILocation(line: 991, column: 26, scope: !3265)
!3270 = !DILocation(line: 991, column: 53, scope: !3265)
!3271 = !DILocation(line: 991, column: 57, scope: !3265)
!3272 = !DILocation(line: 991, column: 3, scope: !3265)
!3273 = !DILocation(line: 992, column: 7, scope: !3274)
!3274 = distinct !DILexicalBlock(scope: !388, file: !1, line: 992, column: 6)
!3275 = !DILocation(line: 992, column: 12, scope: !3274)
!3276 = !DILocation(line: 992, column: 21, scope: !3274)
!3277 = !DILocation(line: 992, column: 6, scope: !388)
!3278 = !DILocation(line: 993, column: 26, scope: !3274)
!3279 = !DILocation(line: 993, column: 53, scope: !3274)
!3280 = !DILocation(line: 993, column: 57, scope: !3274)
!3281 = !DILocation(line: 993, column: 3, scope: !3274)
!3282 = !DILocation(line: 995, column: 7, scope: !3283)
!3283 = distinct !DILexicalBlock(scope: !388, file: !1, line: 995, column: 6)
!3284 = !DILocation(line: 995, column: 12, scope: !3283)
!3285 = !DILocation(line: 995, column: 21, scope: !3283)
!3286 = !DILocation(line: 995, column: 6, scope: !388)
!3287 = !DILocation(line: 996, column: 26, scope: !3283)
!3288 = !DILocation(line: 996, column: 55, scope: !3283)
!3289 = !DILocation(line: 996, column: 59, scope: !3283)
!3290 = !DILocation(line: 996, column: 3, scope: !3283)
!3291 = !DILocation(line: 997, column: 7, scope: !3292)
!3292 = distinct !DILexicalBlock(scope: !388, file: !1, line: 997, column: 6)
!3293 = !DILocation(line: 997, column: 12, scope: !3292)
!3294 = !DILocation(line: 997, column: 24, scope: !3292)
!3295 = !DILocation(line: 997, column: 6, scope: !388)
!3296 = !DILocation(line: 998, column: 26, scope: !3297)
!3297 = distinct !DILexicalBlock(scope: !3292, file: !1, line: 997, column: 30)
!3298 = !DILocation(line: 1000, column: 18, scope: !3297)
!3299 = !DILocation(line: 1000, column: 22, scope: !3297)
!3300 = !DILocation(line: 1001, column: 18, scope: !3297)
!3301 = !DILocation(line: 1001, column: 22, scope: !3297)
!3302 = !DILocation(line: 998, column: 3, scope: !3297)
!3303 = !DILocation(line: 1002, column: 2, scope: !3297)
!3304 = !DILocation(line: 1004, column: 10, scope: !388)
!3305 = !DILocation(line: 1004, column: 14, scope: !388)
!3306 = !DILocation(line: 1004, column: 2, scope: !388)
!3307 = !DILocation(line: 1006, column: 8, scope: !3308)
!3308 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1006, column: 7)
!3309 = distinct !DILexicalBlock(scope: !388, file: !1, line: 1004, column: 24)
!3310 = !DILocation(line: 1006, column: 13, scope: !3308)
!3311 = !DILocation(line: 1006, column: 23, scope: !3308)
!3312 = !DILocation(line: 1006, column: 7, scope: !3309)
!3313 = !DILocation(line: 1007, column: 19, scope: !3308)
!3314 = !DILocation(line: 1007, column: 4, scope: !3308)
!3315 = !DILocation(line: 1008, column: 8, scope: !3316)
!3316 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1008, column: 7)
!3317 = !DILocation(line: 1008, column: 13, scope: !3316)
!3318 = !DILocation(line: 1008, column: 24, scope: !3316)
!3319 = !DILocation(line: 1008, column: 7, scope: !3309)
!3320 = !DILocation(line: 1009, column: 19, scope: !3321)
!3321 = distinct !DILexicalBlock(scope: !3316, file: !1, line: 1008, column: 30)
!3322 = !DILocation(line: 1009, column: 4, scope: !3321)
!3323 = !DILocation(line: 1010, column: 16, scope: !3321)
!3324 = !DILocation(line: 1010, column: 21, scope: !3321)
!3325 = !DILocation(line: 1010, column: 25, scope: !3321)
!3326 = !DILocation(line: 1010, column: 33, scope: !3321)
!3327 = !DILocation(line: 1010, column: 4, scope: !3321)
!3328 = !DILocation(line: 1011, column: 3, scope: !3321)
!3329 = !DILocation(line: 1012, column: 3, scope: !3309)
!3330 = !DILocation(line: 1014, column: 8, scope: !3331)
!3331 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1014, column: 7)
!3332 = !DILocation(line: 1014, column: 13, scope: !3331)
!3333 = !DILocation(line: 1014, column: 23, scope: !3331)
!3334 = !DILocation(line: 1014, column: 7, scope: !3309)
!3335 = !DILocation(line: 1015, column: 19, scope: !3331)
!3336 = !DILocation(line: 1015, column: 4, scope: !3331)
!3337 = !DILocation(line: 1016, column: 3, scope: !3309)
!3338 = !DILocation(line: 1018, column: 8, scope: !3339)
!3339 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1018, column: 7)
!3340 = !DILocation(line: 1018, column: 13, scope: !3339)
!3341 = !DILocation(line: 1018, column: 23, scope: !3339)
!3342 = !DILocation(line: 1018, column: 7, scope: !3309)
!3343 = !DILocation(line: 1019, column: 19, scope: !3339)
!3344 = !DILocation(line: 1019, column: 4, scope: !3339)
!3345 = !DILocation(line: 1020, column: 8, scope: !3346)
!3346 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1020, column: 7)
!3347 = !DILocation(line: 1020, column: 13, scope: !3346)
!3348 = !DILocation(line: 1020, column: 22, scope: !3346)
!3349 = !DILocation(line: 1020, column: 7, scope: !3309)
!3350 = !DILocation(line: 1021, column: 27, scope: !3351)
!3351 = distinct !DILexicalBlock(scope: !3346, file: !1, line: 1020, column: 28)
!3352 = !DILocation(line: 1023, column: 19, scope: !3351)
!3353 = !DILocation(line: 1023, column: 23, scope: !3351)
!3354 = !DILocation(line: 1024, column: 19, scope: !3351)
!3355 = !DILocation(line: 1024, column: 23, scope: !3351)
!3356 = !DILocation(line: 1021, column: 4, scope: !3351)
!3357 = !DILocation(line: 1025, column: 3, scope: !3351)
!3358 = !DILocation(line: 1026, column: 3, scope: !3309)
!3359 = !DILocation(line: 1028, column: 8, scope: !3360)
!3360 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1028, column: 7)
!3361 = !DILocation(line: 1028, column: 13, scope: !3360)
!3362 = !DILocation(line: 1028, column: 23, scope: !3360)
!3363 = !DILocation(line: 1028, column: 7, scope: !3309)
!3364 = !DILocation(line: 1029, column: 19, scope: !3360)
!3365 = !DILocation(line: 1029, column: 4, scope: !3360)
!3366 = !DILocation(line: 1030, column: 8, scope: !3367)
!3367 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1030, column: 7)
!3368 = !DILocation(line: 1030, column: 13, scope: !3367)
!3369 = !DILocation(line: 1030, column: 22, scope: !3367)
!3370 = !DILocation(line: 1030, column: 7, scope: !3309)
!3371 = !DILocation(line: 1031, column: 27, scope: !3372)
!3372 = distinct !DILexicalBlock(scope: !3367, file: !1, line: 1030, column: 28)
!3373 = !DILocation(line: 1033, column: 19, scope: !3372)
!3374 = !DILocation(line: 1033, column: 23, scope: !3372)
!3375 = !DILocation(line: 1034, column: 19, scope: !3372)
!3376 = !DILocation(line: 1034, column: 23, scope: !3372)
!3377 = !DILocation(line: 1031, column: 4, scope: !3372)
!3378 = !DILocation(line: 1035, column: 3, scope: !3372)
!3379 = !DILocation(line: 1036, column: 3, scope: !3309)
!3380 = !DILocation(line: 1038, column: 8, scope: !3381)
!3381 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1038, column: 7)
!3382 = !DILocation(line: 1038, column: 13, scope: !3381)
!3383 = !DILocation(line: 1038, column: 23, scope: !3381)
!3384 = !DILocation(line: 1038, column: 7, scope: !3309)
!3385 = !DILocation(line: 1039, column: 19, scope: !3381)
!3386 = !DILocation(line: 1039, column: 4, scope: !3381)
!3387 = !DILocation(line: 1040, column: 3, scope: !3309)
!3388 = !DILocation(line: 1042, column: 8, scope: !3389)
!3389 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1042, column: 7)
!3390 = !DILocation(line: 1042, column: 13, scope: !3389)
!3391 = !DILocation(line: 1042, column: 23, scope: !3389)
!3392 = !DILocation(line: 1042, column: 7, scope: !3309)
!3393 = !DILocation(line: 1043, column: 19, scope: !3389)
!3394 = !DILocation(line: 1043, column: 4, scope: !3389)
!3395 = !DILocation(line: 1044, column: 3, scope: !3309)
!3396 = !DILocation(line: 1044, column: 3, scope: !3397)
!3397 = !DILexicalBlockFile(scope: !3309, file: !1, discriminator: 1)
!3398 = !DILocation(line: 1047, column: 8, scope: !3399)
!3399 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1047, column: 7)
!3400 = !DILocation(line: 1047, column: 13, scope: !3399)
!3401 = !DILocation(line: 1047, column: 23, scope: !3399)
!3402 = !DILocation(line: 1047, column: 7, scope: !3309)
!3403 = !DILocation(line: 1048, column: 19, scope: !3399)
!3404 = !DILocation(line: 1048, column: 4, scope: !3399)
!3405 = !DILocation(line: 1049, column: 8, scope: !3406)
!3406 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 1049, column: 7)
!3407 = !DILocation(line: 1049, column: 13, scope: !3406)
!3408 = !DILocation(line: 1049, column: 23, scope: !3406)
!3409 = !DILocation(line: 1049, column: 7, scope: !3309)
!3410 = !DILocation(line: 1050, column: 27, scope: !3406)
!3411 = !DILocation(line: 1051, column: 18, scope: !3406)
!3412 = !DILocation(line: 1051, column: 22, scope: !3406)
!3413 = !DILocation(line: 1050, column: 4, scope: !3406)
!3414 = !DILocation(line: 1052, column: 3, scope: !3309)
!3415 = !DILocation(line: 1056, column: 6, scope: !3416)
!3416 = distinct !DILexicalBlock(scope: !388, file: !1, line: 1056, column: 6)
!3417 = !DILocation(line: 1056, column: 10, scope: !3416)
!3418 = !DILocation(line: 1056, column: 6, scope: !388)
!3419 = !DILocation(line: 1057, column: 13, scope: !3416)
!3420 = !DILocation(line: 1057, column: 18, scope: !3416)
!3421 = !DILocation(line: 1057, column: 22, scope: !3416)
!3422 = !DILocation(line: 1057, column: 3, scope: !3416)
!3423 = !DILocation(line: 1059, column: 25, scope: !388)
!3424 = !DILocation(line: 1059, column: 2, scope: !388)
!3425 = !DILocation(line: 1060, column: 6, scope: !3426)
!3426 = distinct !DILexicalBlock(scope: !388, file: !1, line: 1060, column: 6)
!3427 = !DILocation(line: 1060, column: 13, scope: !3426)
!3428 = !DILocation(line: 1060, column: 20, scope: !3426)
!3429 = !DILocation(line: 1060, column: 23, scope: !3430)
!3430 = !DILexicalBlockFile(scope: !3426, file: !1, discriminator: 1)
!3431 = !DILocation(line: 1060, column: 30, scope: !3430)
!3432 = !DILocation(line: 1060, column: 6, scope: !3430)
!3433 = !DILocation(line: 1061, column: 16, scope: !3426)
!3434 = !DILocation(line: 1061, column: 3, scope: !3426)
!3435 = !DILocation(line: 1063, column: 6, scope: !3436)
!3436 = distinct !DILexicalBlock(scope: !388, file: !1, line: 1063, column: 6)
!3437 = !DILocation(line: 1063, column: 13, scope: !3436)
!3438 = !DILocation(line: 1063, column: 17, scope: !3436)
!3439 = !DILocation(line: 1063, column: 24, scope: !3436)
!3440 = !DILocation(line: 1063, column: 6, scope: !388)
!3441 = !DILocation(line: 1065, column: 4, scope: !3442)
!3442 = distinct !DILexicalBlock(scope: !3436, file: !1, line: 1063, column: 33)
!3443 = !DILocation(line: 1065, column: 7, scope: !3442)
!3444 = !DILocation(line: 1065, column: 14, scope: !3442)
!3445 = !DILocation(line: 1065, column: 18, scope: !3442)
!3446 = !DILocation(line: 1065, column: 21, scope: !3442)
!3447 = !DILocation(line: 1065, column: 28, scope: !3442)
!3448 = !DILocation(line: 1065, column: 32, scope: !3442)
!3449 = !DILocation(line: 1064, column: 9, scope: !3442)
!3450 = !DILocation(line: 1064, column: 7, scope: !3442)
!3451 = !DILocation(line: 1066, column: 3, scope: !3442)
!3452 = !DILocation(line: 1067, column: 2, scope: !3442)
!3453 = !DILocation(line: 1068, column: 7, scope: !3436)
!3454 = !DILocation(line: 1069, column: 10, scope: !388)
!3455 = !DILocation(line: 1069, column: 2, scope: !388)
!3456 = !DILocalVariable(name: "mtree", arg: 1, scope: !400, file: !1, line: 453, type: !191)
!3457 = !DILocation(line: 453, column: 35, scope: !400)
!3458 = !DILocalVariable(name: "setstr", scope: !400, file: !1, line: 455, type: !91)
!3459 = !DILocation(line: 455, column: 24, scope: !400)
!3460 = !DILocalVariable(name: "unsetstr", scope: !400, file: !1, line: 456, type: !91)
!3461 = !DILocation(line: 456, column: 24, scope: !400)
!3462 = !DILocalVariable(name: "acs", scope: !400, file: !1, line: 457, type: !1107)
!3463 = !DILocation(line: 457, column: 26, scope: !400)
!3464 = !DILocalVariable(name: "keys", scope: !400, file: !1, line: 458, type: !23)
!3465 = !DILocation(line: 458, column: 6, scope: !400)
!3466 = !DILocalVariable(name: "oldkeys", scope: !400, file: !1, line: 458, type: !23)
!3467 = !DILocation(line: 458, column: 12, scope: !400)
!3468 = !DILocalVariable(name: "effkeys", scope: !400, file: !1, line: 458, type: !23)
!3469 = !DILocation(line: 458, column: 21, scope: !400)
!3470 = !DILocation(line: 460, column: 2, scope: !400)
!3471 = !DILocation(line: 460, column: 2, scope: !3472)
!3472 = !DILexicalBlockFile(scope: !3473, file: !1, discriminator: 1)
!3473 = distinct !DILexicalBlock(scope: !400, file: !1, line: 460, column: 2)
!3474 = !DILocation(line: 461, column: 2, scope: !400)
!3475 = !DILocation(line: 461, column: 2, scope: !3476)
!3476 = !DILexicalBlockFile(scope: !3477, file: !1, discriminator: 1)
!3477 = distinct !DILexicalBlock(scope: !400, file: !1, line: 461, column: 2)
!3478 = !DILocation(line: 462, column: 9, scope: !400)
!3479 = !DILocation(line: 462, column: 16, scope: !400)
!3480 = !DILocation(line: 462, column: 21, scope: !400)
!3481 = !DILocation(line: 462, column: 7, scope: !400)
!3482 = !DILocation(line: 463, column: 12, scope: !400)
!3483 = !DILocation(line: 463, column: 19, scope: !400)
!3484 = !DILocation(line: 463, column: 23, scope: !400)
!3485 = !DILocation(line: 463, column: 10, scope: !400)
!3486 = !DILocation(line: 464, column: 12, scope: !400)
!3487 = !DILocation(line: 464, column: 10, scope: !400)
!3488 = !DILocation(line: 465, column: 9, scope: !400)
!3489 = !DILocation(line: 465, column: 16, scope: !400)
!3490 = !DILocation(line: 465, column: 6, scope: !400)
!3491 = !DILocation(line: 466, column: 6, scope: !3492)
!3492 = distinct !DILexicalBlock(scope: !400, file: !1, line: 466, column: 6)
!3493 = !DILocation(line: 466, column: 13, scope: !3492)
!3494 = !DILocation(line: 466, column: 17, scope: !3492)
!3495 = !DILocation(line: 466, column: 6, scope: !400)
!3496 = !DILocation(line: 470, column: 11, scope: !3497)
!3497 = distinct !DILexicalBlock(scope: !3492, file: !1, line: 466, column: 29)
!3498 = !DILocation(line: 471, column: 7, scope: !3499)
!3499 = distinct !DILexicalBlock(scope: !3497, file: !1, line: 471, column: 7)
!3500 = !DILocation(line: 471, column: 12, scope: !3499)
!3501 = !DILocation(line: 471, column: 21, scope: !3499)
!3502 = !DILocation(line: 471, column: 7, scope: !3497)
!3503 = !DILocation(line: 472, column: 12, scope: !3499)
!3504 = !DILocation(line: 472, column: 4, scope: !3499)
!3505 = !DILocation(line: 473, column: 12, scope: !3506)
!3506 = distinct !DILexicalBlock(scope: !3499, file: !1, line: 473, column: 12)
!3507 = !DILocation(line: 473, column: 20, scope: !3506)
!3508 = !DILocation(line: 473, column: 12, scope: !3499)
!3509 = !DILocation(line: 474, column: 8, scope: !3510)
!3510 = distinct !DILexicalBlock(scope: !3511, file: !1, line: 474, column: 8)
!3511 = distinct !DILexicalBlock(scope: !3506, file: !1, line: 473, column: 41)
!3512 = !DILocation(line: 474, column: 13, scope: !3510)
!3513 = !DILocation(line: 474, column: 23, scope: !3510)
!3514 = !DILocation(line: 474, column: 29, scope: !3510)
!3515 = !DILocation(line: 474, column: 33, scope: !3510)
!3516 = !DILocation(line: 475, column: 8, scope: !3510)
!3517 = !DILocation(line: 475, column: 15, scope: !3510)
!3518 = !DILocation(line: 475, column: 19, scope: !3510)
!3519 = !DILocation(line: 475, column: 26, scope: !3510)
!3520 = !DILocation(line: 475, column: 31, scope: !3510)
!3521 = !DILocation(line: 475, column: 41, scope: !3510)
!3522 = !DILocation(line: 475, column: 50, scope: !3510)
!3523 = !DILocation(line: 475, column: 23, scope: !3510)
!3524 = !DILocation(line: 474, column: 8, scope: !3525)
!3525 = !DILexicalBlockFile(scope: !3511, file: !1, discriminator: 1)
!3526 = !DILocation(line: 476, column: 13, scope: !3510)
!3527 = !DILocation(line: 476, column: 5, scope: !3510)
!3528 = !DILocation(line: 477, column: 3, scope: !3511)
!3529 = !DILocation(line: 478, column: 7, scope: !3530)
!3530 = distinct !DILexicalBlock(scope: !3497, file: !1, line: 478, column: 7)
!3531 = !DILocation(line: 478, column: 12, scope: !3530)
!3532 = !DILocation(line: 478, column: 21, scope: !3530)
!3533 = !DILocation(line: 478, column: 7, scope: !3497)
!3534 = !DILocation(line: 479, column: 12, scope: !3530)
!3535 = !DILocation(line: 479, column: 4, scope: !3530)
!3536 = !DILocation(line: 480, column: 12, scope: !3537)
!3537 = distinct !DILexicalBlock(scope: !3530, file: !1, line: 480, column: 12)
!3538 = !DILocation(line: 480, column: 20, scope: !3537)
!3539 = !DILocation(line: 480, column: 12, scope: !3530)
!3540 = !DILocation(line: 481, column: 8, scope: !3541)
!3541 = distinct !DILexicalBlock(scope: !3542, file: !1, line: 481, column: 8)
!3542 = distinct !DILexicalBlock(scope: !3537, file: !1, line: 480, column: 41)
!3543 = !DILocation(line: 481, column: 13, scope: !3541)
!3544 = !DILocation(line: 481, column: 23, scope: !3541)
!3545 = !DILocation(line: 481, column: 29, scope: !3541)
!3546 = !DILocation(line: 481, column: 33, scope: !3541)
!3547 = !DILocation(line: 482, column: 8, scope: !3541)
!3548 = !DILocation(line: 482, column: 15, scope: !3541)
!3549 = !DILocation(line: 482, column: 19, scope: !3541)
!3550 = !DILocation(line: 482, column: 26, scope: !3541)
!3551 = !DILocation(line: 482, column: 31, scope: !3541)
!3552 = !DILocation(line: 482, column: 41, scope: !3541)
!3553 = !DILocation(line: 482, column: 50, scope: !3541)
!3554 = !DILocation(line: 482, column: 23, scope: !3541)
!3555 = !DILocation(line: 481, column: 8, scope: !3556)
!3556 = !DILexicalBlockFile(scope: !3542, file: !1, discriminator: 1)
!3557 = !DILocation(line: 483, column: 13, scope: !3541)
!3558 = !DILocation(line: 483, column: 5, scope: !3541)
!3559 = !DILocation(line: 484, column: 3, scope: !3542)
!3560 = !DILocation(line: 485, column: 7, scope: !3561)
!3561 = distinct !DILexicalBlock(scope: !3497, file: !1, line: 485, column: 7)
!3562 = !DILocation(line: 485, column: 12, scope: !3561)
!3563 = !DILocation(line: 485, column: 22, scope: !3561)
!3564 = !DILocation(line: 485, column: 7, scope: !3497)
!3565 = !DILocation(line: 486, column: 12, scope: !3561)
!3566 = !DILocation(line: 486, column: 4, scope: !3561)
!3567 = !DILocation(line: 487, column: 12, scope: !3568)
!3568 = distinct !DILexicalBlock(scope: !3561, file: !1, line: 487, column: 12)
!3569 = !DILocation(line: 487, column: 20, scope: !3568)
!3570 = !DILocation(line: 487, column: 12, scope: !3561)
!3571 = !DILocation(line: 488, column: 8, scope: !3572)
!3572 = distinct !DILexicalBlock(scope: !3573, file: !1, line: 488, column: 8)
!3573 = distinct !DILexicalBlock(scope: !3568, file: !1, line: 487, column: 30)
!3574 = !DILocation(line: 488, column: 13, scope: !3572)
!3575 = !DILocation(line: 488, column: 24, scope: !3572)
!3576 = !DILocation(line: 488, column: 30, scope: !3572)
!3577 = !DILocation(line: 488, column: 34, scope: !3572)
!3578 = !DILocation(line: 489, column: 8, scope: !3572)
!3579 = !DILocation(line: 489, column: 15, scope: !3572)
!3580 = !DILocation(line: 489, column: 19, scope: !3572)
!3581 = !DILocation(line: 489, column: 27, scope: !3572)
!3582 = !DILocation(line: 489, column: 32, scope: !3572)
!3583 = !DILocation(line: 489, column: 43, scope: !3572)
!3584 = !DILocation(line: 489, column: 52, scope: !3572)
!3585 = !DILocation(line: 489, column: 24, scope: !3572)
!3586 = !DILocation(line: 488, column: 8, scope: !3587)
!3587 = !DILexicalBlockFile(scope: !3573, file: !1, discriminator: 1)
!3588 = !DILocation(line: 490, column: 13, scope: !3572)
!3589 = !DILocation(line: 490, column: 5, scope: !3572)
!3590 = !DILocation(line: 491, column: 3, scope: !3573)
!3591 = !DILocation(line: 492, column: 7, scope: !3592)
!3592 = distinct !DILexicalBlock(scope: !3497, file: !1, line: 492, column: 7)
!3593 = !DILocation(line: 492, column: 12, scope: !3592)
!3594 = !DILocation(line: 492, column: 23, scope: !3592)
!3595 = !DILocation(line: 492, column: 7, scope: !3497)
!3596 = !DILocation(line: 493, column: 12, scope: !3592)
!3597 = !DILocation(line: 493, column: 4, scope: !3592)
!3598 = !DILocation(line: 494, column: 13, scope: !3599)
!3599 = distinct !DILexicalBlock(scope: !3592, file: !1, line: 494, column: 12)
!3600 = !DILocation(line: 494, column: 21, scope: !3599)
!3601 = !DILocation(line: 494, column: 32, scope: !3599)
!3602 = !DILocation(line: 494, column: 12, scope: !3592)
!3603 = !DILocation(line: 495, column: 8, scope: !3604)
!3604 = distinct !DILexicalBlock(scope: !3605, file: !1, line: 495, column: 8)
!3605 = distinct !DILexicalBlock(scope: !3599, file: !1, line: 494, column: 38)
!3606 = !DILocation(line: 495, column: 13, scope: !3604)
!3607 = !DILocation(line: 495, column: 25, scope: !3604)
!3608 = !DILocation(line: 495, column: 31, scope: !3604)
!3609 = !DILocation(line: 495, column: 35, scope: !3604)
!3610 = !DILocation(line: 496, column: 9, scope: !3604)
!3611 = !DILocation(line: 496, column: 14, scope: !3604)
!3612 = !DILocation(line: 496, column: 26, scope: !3604)
!3613 = !DILocation(line: 496, column: 35, scope: !3604)
!3614 = !DILocation(line: 497, column: 5, scope: !3604)
!3615 = !DILocation(line: 497, column: 12, scope: !3604)
!3616 = !DILocation(line: 497, column: 16, scope: !3604)
!3617 = !DILocation(line: 496, column: 46, scope: !3604)
!3618 = !DILocation(line: 497, column: 27, scope: !3604)
!3619 = !DILocation(line: 498, column: 9, scope: !3604)
!3620 = !DILocation(line: 498, column: 14, scope: !3604)
!3621 = !DILocation(line: 498, column: 26, scope: !3604)
!3622 = !DILocation(line: 498, column: 35, scope: !3604)
!3623 = !DILocation(line: 499, column: 5, scope: !3604)
!3624 = !DILocation(line: 499, column: 12, scope: !3604)
!3625 = !DILocation(line: 499, column: 16, scope: !3604)
!3626 = !DILocation(line: 498, column: 48, scope: !3604)
!3627 = !DILocation(line: 495, column: 8, scope: !3628)
!3628 = !DILexicalBlockFile(scope: !3605, file: !1, discriminator: 1)
!3629 = !DILocation(line: 500, column: 13, scope: !3604)
!3630 = !DILocation(line: 500, column: 5, scope: !3604)
!3631 = !DILocation(line: 501, column: 3, scope: !3605)
!3632 = !DILocation(line: 502, column: 2, scope: !3497)
!3633 = !DILocation(line: 503, column: 7, scope: !3634)
!3634 = distinct !DILexicalBlock(scope: !3635, file: !1, line: 503, column: 7)
!3635 = distinct !DILexicalBlock(scope: !3492, file: !1, line: 502, column: 9)
!3636 = !DILocation(line: 503, column: 12, scope: !3634)
!3637 = !DILocation(line: 503, column: 21, scope: !3634)
!3638 = !DILocation(line: 503, column: 7, scope: !3635)
!3639 = !DILocation(line: 504, column: 9, scope: !3634)
!3640 = !DILocation(line: 504, column: 4, scope: !3634)
!3641 = !DILocation(line: 505, column: 7, scope: !3642)
!3642 = distinct !DILexicalBlock(scope: !3635, file: !1, line: 505, column: 7)
!3643 = !DILocation(line: 505, column: 12, scope: !3642)
!3644 = !DILocation(line: 505, column: 21, scope: !3642)
!3645 = !DILocation(line: 505, column: 7, scope: !3635)
!3646 = !DILocation(line: 506, column: 9, scope: !3642)
!3647 = !DILocation(line: 506, column: 4, scope: !3642)
!3648 = !DILocation(line: 507, column: 7, scope: !3649)
!3649 = distinct !DILexicalBlock(scope: !3635, file: !1, line: 507, column: 7)
!3650 = !DILocation(line: 507, column: 12, scope: !3649)
!3651 = !DILocation(line: 507, column: 22, scope: !3649)
!3652 = !DILocation(line: 507, column: 7, scope: !3635)
!3653 = !DILocation(line: 508, column: 9, scope: !3649)
!3654 = !DILocation(line: 508, column: 4, scope: !3649)
!3655 = !DILocation(line: 509, column: 7, scope: !3656)
!3656 = distinct !DILexicalBlock(scope: !3635, file: !1, line: 509, column: 7)
!3657 = !DILocation(line: 509, column: 12, scope: !3656)
!3658 = !DILocation(line: 509, column: 23, scope: !3656)
!3659 = !DILocation(line: 509, column: 7, scope: !3635)
!3660 = !DILocation(line: 510, column: 9, scope: !3656)
!3661 = !DILocation(line: 510, column: 4, scope: !3656)
!3662 = !DILocation(line: 512, column: 7, scope: !3663)
!3663 = distinct !DILexicalBlock(scope: !400, file: !1, line: 512, column: 6)
!3664 = !DILocation(line: 512, column: 14, scope: !3663)
!3665 = !DILocation(line: 512, column: 12, scope: !3663)
!3666 = !DILocation(line: 512, column: 22, scope: !3663)
!3667 = !DILocation(line: 512, column: 32, scope: !3663)
!3668 = !DILocation(line: 512, column: 6, scope: !400)
!3669 = !DILocation(line: 513, column: 7, scope: !3670)
!3670 = distinct !DILexicalBlock(scope: !3671, file: !1, line: 513, column: 7)
!3671 = distinct !DILexicalBlock(scope: !3663, file: !1, line: 512, column: 38)
!3672 = !DILocation(line: 513, column: 14, scope: !3670)
!3673 = !DILocation(line: 513, column: 7, scope: !3671)
!3674 = !DILocation(line: 514, column: 4, scope: !3675)
!3675 = distinct !DILexicalBlock(scope: !3670, file: !1, line: 513, column: 23)
!3676 = !DILocation(line: 515, column: 4, scope: !3675)
!3677 = !DILocation(line: 515, column: 11, scope: !3675)
!3678 = !DILocation(line: 515, column: 15, scope: !3675)
!3679 = !DILocation(line: 515, column: 20, scope: !3675)
!3680 = !DILocation(line: 516, column: 3, scope: !3675)
!3681 = !DILocation(line: 517, column: 4, scope: !3682)
!3682 = distinct !DILexicalBlock(scope: !3670, file: !1, line: 516, column: 10)
!3683 = !DILocation(line: 518, column: 4, scope: !3682)
!3684 = !DILocation(line: 518, column: 11, scope: !3682)
!3685 = !DILocation(line: 518, column: 15, scope: !3682)
!3686 = !DILocation(line: 518, column: 20, scope: !3682)
!3687 = !DILocation(line: 520, column: 2, scope: !3671)
!3688 = !DILocation(line: 521, column: 7, scope: !3689)
!3689 = distinct !DILexicalBlock(scope: !400, file: !1, line: 521, column: 6)
!3690 = !DILocation(line: 521, column: 14, scope: !3689)
!3691 = !DILocation(line: 521, column: 12, scope: !3689)
!3692 = !DILocation(line: 521, column: 22, scope: !3689)
!3693 = !DILocation(line: 521, column: 33, scope: !3689)
!3694 = !DILocation(line: 521, column: 6, scope: !400)
!3695 = !DILocation(line: 522, column: 7, scope: !3696)
!3696 = distinct !DILexicalBlock(scope: !3697, file: !1, line: 522, column: 7)
!3697 = distinct !DILexicalBlock(scope: !3689, file: !1, line: 521, column: 39)
!3698 = !DILocation(line: 522, column: 56, scope: !3696)
!3699 = !DILocation(line: 522, column: 7, scope: !3697)
!3700 = !DILocation(line: 523, column: 4, scope: !3701)
!3701 = distinct !DILexicalBlock(scope: !3696, file: !1, line: 522, column: 61)
!3702 = !DILocation(line: 524, column: 25, scope: !3701)
!3703 = !DILocation(line: 524, column: 30, scope: !3701)
!3704 = !DILocation(line: 524, column: 40, scope: !3701)
!3705 = !DILocation(line: 524, column: 49, scope: !3701)
!3706 = !DILocation(line: 524, column: 55, scope: !3701)
!3707 = !DILocation(line: 524, column: 4, scope: !3701)
!3708 = !DILocation(line: 525, column: 3, scope: !3701)
!3709 = !DILocation(line: 526, column: 9, scope: !3710)
!3710 = distinct !DILexicalBlock(scope: !3696, file: !1, line: 525, column: 10)
!3711 = !DILocation(line: 527, column: 9, scope: !3712)
!3712 = distinct !DILexicalBlock(scope: !3710, file: !1, line: 527, column: 8)
!3713 = !DILocation(line: 527, column: 17, scope: !3712)
!3714 = !DILocation(line: 527, column: 28, scope: !3712)
!3715 = !DILocation(line: 527, column: 8, scope: !3710)
!3716 = !DILocation(line: 528, column: 5, scope: !3712)
!3717 = !DILocation(line: 530, column: 2, scope: !3697)
!3718 = !DILocation(line: 531, column: 7, scope: !3719)
!3719 = distinct !DILexicalBlock(scope: !400, file: !1, line: 531, column: 6)
!3720 = !DILocation(line: 531, column: 14, scope: !3719)
!3721 = !DILocation(line: 531, column: 12, scope: !3719)
!3722 = !DILocation(line: 531, column: 22, scope: !3719)
!3723 = !DILocation(line: 531, column: 31, scope: !3719)
!3724 = !DILocation(line: 531, column: 6, scope: !400)
!3725 = !DILocation(line: 532, column: 20, scope: !3726)
!3726 = distinct !DILexicalBlock(scope: !3719, file: !1, line: 531, column: 37)
!3727 = !DILocation(line: 532, column: 25, scope: !3726)
!3728 = !DILocation(line: 532, column: 35, scope: !3726)
!3729 = !DILocation(line: 532, column: 44, scope: !3726)
!3730 = !DILocation(line: 532, column: 3, scope: !3726)
!3731 = !DILocation(line: 532, column: 10, scope: !3726)
!3732 = !DILocation(line: 532, column: 14, scope: !3726)
!3733 = !DILocation(line: 532, column: 18, scope: !3726)
!3734 = !DILocation(line: 534, column: 17, scope: !3726)
!3735 = !DILocation(line: 534, column: 24, scope: !3726)
!3736 = !DILocation(line: 534, column: 28, scope: !3726)
!3737 = !DILocation(line: 533, column: 3, scope: !3726)
!3738 = !DILocation(line: 535, column: 2, scope: !3726)
!3739 = !DILocation(line: 536, column: 7, scope: !3740)
!3740 = distinct !DILexicalBlock(scope: !400, file: !1, line: 536, column: 6)
!3741 = !DILocation(line: 536, column: 14, scope: !3740)
!3742 = !DILocation(line: 536, column: 12, scope: !3740)
!3743 = !DILocation(line: 536, column: 22, scope: !3740)
!3744 = !DILocation(line: 536, column: 33, scope: !3740)
!3745 = !DILocation(line: 536, column: 6, scope: !400)
!3746 = !DILocation(line: 537, column: 7, scope: !3747)
!3747 = distinct !DILexicalBlock(scope: !3748, file: !1, line: 537, column: 7)
!3748 = distinct !DILexicalBlock(scope: !3740, file: !1, line: 536, column: 39)
!3749 = !DILocation(line: 537, column: 56, scope: !3747)
!3750 = !DILocation(line: 537, column: 7, scope: !3748)
!3751 = !DILocation(line: 538, column: 4, scope: !3752)
!3752 = distinct !DILexicalBlock(scope: !3747, file: !1, line: 537, column: 61)
!3753 = !DILocation(line: 539, column: 25, scope: !3752)
!3754 = !DILocation(line: 539, column: 30, scope: !3752)
!3755 = !DILocation(line: 539, column: 40, scope: !3752)
!3756 = !DILocation(line: 539, column: 49, scope: !3752)
!3757 = !DILocation(line: 539, column: 55, scope: !3752)
!3758 = !DILocation(line: 539, column: 4, scope: !3752)
!3759 = !DILocation(line: 540, column: 3, scope: !3752)
!3760 = !DILocation(line: 541, column: 9, scope: !3761)
!3761 = distinct !DILexicalBlock(scope: !3747, file: !1, line: 540, column: 10)
!3762 = !DILocation(line: 542, column: 9, scope: !3763)
!3763 = distinct !DILexicalBlock(scope: !3761, file: !1, line: 542, column: 8)
!3764 = !DILocation(line: 542, column: 17, scope: !3763)
!3765 = !DILocation(line: 542, column: 28, scope: !3763)
!3766 = !DILocation(line: 542, column: 8, scope: !3761)
!3767 = !DILocation(line: 543, column: 5, scope: !3763)
!3768 = !DILocation(line: 545, column: 2, scope: !3748)
!3769 = !DILocation(line: 546, column: 7, scope: !3770)
!3770 = distinct !DILexicalBlock(scope: !400, file: !1, line: 546, column: 6)
!3771 = !DILocation(line: 546, column: 14, scope: !3770)
!3772 = !DILocation(line: 546, column: 12, scope: !3770)
!3773 = !DILocation(line: 546, column: 22, scope: !3770)
!3774 = !DILocation(line: 546, column: 31, scope: !3770)
!3775 = !DILocation(line: 546, column: 6, scope: !400)
!3776 = !DILocation(line: 547, column: 20, scope: !3777)
!3777 = distinct !DILexicalBlock(scope: !3770, file: !1, line: 546, column: 37)
!3778 = !DILocation(line: 547, column: 25, scope: !3777)
!3779 = !DILocation(line: 547, column: 35, scope: !3777)
!3780 = !DILocation(line: 547, column: 44, scope: !3777)
!3781 = !DILocation(line: 547, column: 3, scope: !3777)
!3782 = !DILocation(line: 547, column: 10, scope: !3777)
!3783 = !DILocation(line: 547, column: 14, scope: !3777)
!3784 = !DILocation(line: 547, column: 18, scope: !3777)
!3785 = !DILocation(line: 549, column: 17, scope: !3777)
!3786 = !DILocation(line: 549, column: 24, scope: !3777)
!3787 = !DILocation(line: 549, column: 28, scope: !3777)
!3788 = !DILocation(line: 548, column: 3, scope: !3777)
!3789 = !DILocation(line: 550, column: 2, scope: !3777)
!3790 = !DILocation(line: 551, column: 7, scope: !3791)
!3791 = distinct !DILexicalBlock(scope: !400, file: !1, line: 551, column: 6)
!3792 = !DILocation(line: 551, column: 14, scope: !3791)
!3793 = !DILocation(line: 551, column: 12, scope: !3791)
!3794 = !DILocation(line: 551, column: 22, scope: !3791)
!3795 = !DILocation(line: 551, column: 32, scope: !3791)
!3796 = !DILocation(line: 551, column: 6, scope: !400)
!3797 = !DILocation(line: 552, column: 21, scope: !3798)
!3798 = distinct !DILexicalBlock(scope: !3791, file: !1, line: 551, column: 38)
!3799 = !DILocation(line: 552, column: 26, scope: !3798)
!3800 = !DILocation(line: 552, column: 37, scope: !3798)
!3801 = !DILocation(line: 552, column: 46, scope: !3798)
!3802 = !DILocation(line: 552, column: 3, scope: !3798)
!3803 = !DILocation(line: 552, column: 10, scope: !3798)
!3804 = !DILocation(line: 552, column: 14, scope: !3798)
!3805 = !DILocation(line: 552, column: 19, scope: !3798)
!3806 = !DILocation(line: 554, column: 21, scope: !3798)
!3807 = !DILocation(line: 554, column: 28, scope: !3798)
!3808 = !DILocation(line: 554, column: 32, scope: !3798)
!3809 = !DILocation(line: 553, column: 3, scope: !3798)
!3810 = !DILocation(line: 555, column: 2, scope: !3798)
!3811 = !DILocation(line: 556, column: 7, scope: !3812)
!3812 = distinct !DILexicalBlock(scope: !400, file: !1, line: 556, column: 6)
!3813 = !DILocation(line: 556, column: 14, scope: !3812)
!3814 = !DILocation(line: 556, column: 12, scope: !3812)
!3815 = !DILocation(line: 556, column: 22, scope: !3812)
!3816 = !DILocation(line: 556, column: 33, scope: !3812)
!3817 = !DILocation(line: 556, column: 6, scope: !400)
!3818 = !DILocation(line: 557, column: 7, scope: !3819)
!3819 = distinct !DILexicalBlock(scope: !3820, file: !1, line: 557, column: 7)
!3820 = distinct !DILexicalBlock(scope: !3812, file: !1, line: 556, column: 39)
!3821 = !DILocation(line: 558, column: 49, scope: !3819)
!3822 = !DILocation(line: 557, column: 7, scope: !3820)
!3823 = !DILocation(line: 559, column: 4, scope: !3824)
!3824 = distinct !DILexicalBlock(scope: !3819, file: !1, line: 558, column: 54)
!3825 = !DILocation(line: 561, column: 8, scope: !3824)
!3826 = !DILocation(line: 561, column: 13, scope: !3824)
!3827 = !DILocation(line: 561, column: 25, scope: !3824)
!3828 = !DILocation(line: 561, column: 34, scope: !3824)
!3829 = !DILocation(line: 561, column: 46, scope: !3824)
!3830 = !DILocation(line: 560, column: 4, scope: !3824)
!3831 = !DILocation(line: 563, column: 8, scope: !3824)
!3832 = !DILocation(line: 563, column: 13, scope: !3824)
!3833 = !DILocation(line: 563, column: 25, scope: !3824)
!3834 = !DILocation(line: 563, column: 34, scope: !3824)
!3835 = !DILocation(line: 562, column: 4, scope: !3824)
!3836 = !DILocation(line: 562, column: 11, scope: !3824)
!3837 = !DILocation(line: 562, column: 15, scope: !3824)
!3838 = !DILocation(line: 562, column: 26, scope: !3824)
!3839 = !DILocation(line: 565, column: 8, scope: !3824)
!3840 = !DILocation(line: 565, column: 13, scope: !3824)
!3841 = !DILocation(line: 565, column: 25, scope: !3824)
!3842 = !DILocation(line: 565, column: 34, scope: !3824)
!3843 = !DILocation(line: 564, column: 4, scope: !3824)
!3844 = !DILocation(line: 564, column: 11, scope: !3824)
!3845 = !DILocation(line: 564, column: 15, scope: !3824)
!3846 = !DILocation(line: 564, column: 28, scope: !3824)
!3847 = !DILocation(line: 566, column: 3, scope: !3824)
!3848 = !DILocation(line: 567, column: 9, scope: !3849)
!3849 = distinct !DILexicalBlock(scope: !3819, file: !1, line: 566, column: 10)
!3850 = !DILocation(line: 568, column: 9, scope: !3851)
!3851 = distinct !DILexicalBlock(scope: !3849, file: !1, line: 568, column: 8)
!3852 = !DILocation(line: 568, column: 17, scope: !3851)
!3853 = !DILocation(line: 568, column: 28, scope: !3851)
!3854 = !DILocation(line: 568, column: 8, scope: !3849)
!3855 = !DILocation(line: 569, column: 5, scope: !3851)
!3856 = !DILocation(line: 571, column: 2, scope: !3820)
!3857 = !DILocation(line: 572, column: 15, scope: !3858)
!3858 = distinct !DILexicalBlock(scope: !400, file: !1, line: 572, column: 6)
!3859 = !DILocation(line: 572, column: 22, scope: !3858)
!3860 = !DILocation(line: 572, column: 6, scope: !400)
!3861 = !DILocation(line: 573, column: 27, scope: !3858)
!3862 = !DILocation(line: 573, column: 34, scope: !3858)
!3863 = !DILocation(line: 573, column: 62, scope: !3858)
!3864 = !DILocation(line: 573, column: 3, scope: !3858)
!3865 = !DILocation(line: 574, column: 2, scope: !400)
!3866 = !DILocation(line: 575, column: 13, scope: !3867)
!3867 = distinct !DILexicalBlock(scope: !400, file: !1, line: 575, column: 6)
!3868 = !DILocation(line: 575, column: 20, scope: !3867)
!3869 = !DILocation(line: 575, column: 6, scope: !400)
!3870 = !DILocation(line: 576, column: 27, scope: !3867)
!3871 = !DILocation(line: 576, column: 34, scope: !3867)
!3872 = !DILocation(line: 576, column: 58, scope: !3867)
!3873 = !DILocation(line: 576, column: 3, scope: !3867)
!3874 = !DILocation(line: 577, column: 2, scope: !400)
!3875 = !DILocation(line: 578, column: 20, scope: !400)
!3876 = !DILocation(line: 578, column: 2, scope: !400)
!3877 = !DILocation(line: 578, column: 9, scope: !400)
!3878 = !DILocation(line: 578, column: 13, scope: !400)
!3879 = !DILocation(line: 578, column: 18, scope: !400)
!3880 = !DILocation(line: 579, column: 2, scope: !400)
!3881 = !DILocation(line: 579, column: 9, scope: !400)
!3882 = !DILocation(line: 579, column: 13, scope: !400)
!3883 = !DILocation(line: 579, column: 24, scope: !400)
!3884 = !DILocation(line: 580, column: 1, scope: !400)
!3885 = !DILocalVariable(name: "parent", arg: 1, scope: !401, file: !1, line: 1950, type: !195)
!3886 = !DILocation(line: 1950, column: 48, scope: !401)
!3887 = !DILocalVariable(name: "child", arg: 2, scope: !401, file: !1, line: 1951, type: !195)
!3888 = !DILocation(line: 1951, column: 25, scope: !401)
!3889 = !DILocation(line: 1953, column: 2, scope: !401)
!3890 = !DILocation(line: 1953, column: 9, scope: !401)
!3891 = !DILocation(line: 1953, column: 19, scope: !401)
!3892 = !DILocation(line: 1953, column: 26, scope: !401)
!3893 = !DILocation(line: 1954, column: 37, scope: !401)
!3894 = !DILocation(line: 1954, column: 3, scope: !401)
!3895 = !DILocation(line: 1954, column: 11, scope: !401)
!3896 = !DILocation(line: 1954, column: 21, scope: !401)
!3897 = !DILocation(line: 1954, column: 30, scope: !401)
!3898 = !DILocation(line: 1954, column: 35, scope: !401)
!3899 = !DILocation(line: 1955, column: 38, scope: !401)
!3900 = !DILocation(line: 1955, column: 45, scope: !401)
!3901 = !DILocation(line: 1955, column: 55, scope: !401)
!3902 = !DILocation(line: 1955, column: 2, scope: !401)
!3903 = !DILocation(line: 1955, column: 10, scope: !401)
!3904 = !DILocation(line: 1955, column: 20, scope: !401)
!3905 = !DILocation(line: 1955, column: 29, scope: !401)
!3906 = !DILocation(line: 1955, column: 34, scope: !401)
!3907 = !DILocation(line: 1956, column: 2, scope: !401)
!3908 = !DILocalVariable(name: "a", arg: 1, scope: !404, file: !1, line: 1073, type: !4)
!3909 = !DILocation(line: 1073, column: 43, scope: !404)
!3910 = !DILocalVariable(name: "n", arg: 2, scope: !404, file: !1, line: 1073, type: !195)
!3911 = !DILocation(line: 1073, column: 66, scope: !404)
!3912 = !DILocalVariable(name: "mtree", scope: !404, file: !1, line: 1075, type: !191)
!3913 = !DILocation(line: 1075, column: 23, scope: !404)
!3914 = !DILocation(line: 1075, column: 31, scope: !404)
!3915 = !DILocation(line: 1075, column: 34, scope: !404)
!3916 = !DILocalVariable(name: "ret", scope: !404, file: !1, line: 1076, type: !23)
!3917 = !DILocation(line: 1076, column: 6, scope: !404)
!3918 = !DILocation(line: 1078, column: 6, scope: !3919)
!3919 = distinct !DILexicalBlock(scope: !404, file: !1, line: 1078, column: 6)
!3920 = !DILocation(line: 1078, column: 9, scope: !3919)
!3921 = !DILocation(line: 1078, column: 19, scope: !3919)
!3922 = !DILocation(line: 1078, column: 6, scope: !404)
!3923 = !DILocation(line: 1079, column: 7, scope: !3924)
!3924 = distinct !DILexicalBlock(scope: !3925, file: !1, line: 1079, column: 7)
!3925 = distinct !DILexicalBlock(scope: !3919, file: !1, line: 1078, column: 22)
!3926 = !DILocation(line: 1079, column: 14, scope: !3924)
!3927 = !DILocation(line: 1079, column: 7, scope: !3925)
!3928 = !DILocalVariable(name: "i", scope: !3929, file: !1, line: 1080, type: !23)
!3929 = distinct !DILexicalBlock(scope: !3924, file: !1, line: 1079, column: 22)
!3930 = !DILocation(line: 1080, column: 8, scope: !3929)
!3931 = !DILocalVariable(name: "pd", scope: !3929, file: !1, line: 1080, type: !23)
!3932 = !DILocation(line: 1080, column: 11, scope: !3929)
!3933 = !DILocation(line: 1080, column: 16, scope: !3929)
!3934 = !DILocation(line: 1080, column: 23, scope: !3929)
!3935 = !DILocation(line: 1080, column: 29, scope: !3929)
!3936 = !DILocation(line: 1081, column: 11, scope: !3937)
!3937 = distinct !DILexicalBlock(scope: !3929, file: !1, line: 1081, column: 4)
!3938 = !DILocation(line: 1081, column: 9, scope: !3937)
!3939 = !DILocation(line: 1081, column: 16, scope: !3940)
!3940 = !DILexicalBlockFile(scope: !3941, file: !1, discriminator: 1)
!3941 = distinct !DILexicalBlock(scope: !3937, file: !1, line: 1081, column: 4)
!3942 = !DILocation(line: 1081, column: 20, scope: !3940)
!3943 = !DILocation(line: 1081, column: 18, scope: !3940)
!3944 = !DILocation(line: 1081, column: 4, scope: !3940)
!3945 = !DILocation(line: 1082, column: 29, scope: !3941)
!3946 = !DILocation(line: 1082, column: 36, scope: !3941)
!3947 = !DILocation(line: 1082, column: 5, scope: !3941)
!3948 = !DILocation(line: 1081, column: 25, scope: !3949)
!3949 = !DILexicalBlockFile(scope: !3941, file: !1, discriminator: 2)
!3950 = !DILocation(line: 1081, column: 4, scope: !3949)
!3951 = !DILocation(line: 1083, column: 3, scope: !3929)
!3952 = !DILocation(line: 1084, column: 27, scope: !3925)
!3953 = !DILocation(line: 1084, column: 34, scope: !3925)
!3954 = !DILocation(line: 1085, column: 4, scope: !3925)
!3955 = !DILocation(line: 1085, column: 7, scope: !3925)
!3956 = !DILocation(line: 1085, column: 17, scope: !3925)
!3957 = !DILocation(line: 1085, column: 20, scope: !3925)
!3958 = !DILocation(line: 1085, column: 23, scope: !3925)
!3959 = !DILocation(line: 1085, column: 32, scope: !3925)
!3960 = !DILocation(line: 1084, column: 3, scope: !3925)
!3961 = !DILocation(line: 1086, column: 2, scope: !3925)
!3962 = !DILocation(line: 1088, column: 6, scope: !3963)
!3963 = distinct !DILexicalBlock(scope: !404, file: !1, line: 1088, column: 6)
!3964 = !DILocation(line: 1088, column: 13, scope: !3963)
!3965 = !DILocation(line: 1088, column: 6, scope: !404)
!3966 = !DILocation(line: 1089, column: 3, scope: !3967)
!3967 = distinct !DILexicalBlock(scope: !3963, file: !1, line: 1088, column: 21)
!3968 = !DILocation(line: 1090, column: 20, scope: !3967)
!3969 = !DILocation(line: 1090, column: 27, scope: !3967)
!3970 = !DILocation(line: 1090, column: 44, scope: !3967)
!3971 = !DILocation(line: 1090, column: 51, scope: !3967)
!3972 = !DILocation(line: 1090, column: 43, scope: !3967)
!3973 = !DILocation(line: 1090, column: 3, scope: !3967)
!3974 = !DILocation(line: 1091, column: 16, scope: !3967)
!3975 = !DILocation(line: 1091, column: 3, scope: !3967)
!3976 = !DILocation(line: 1092, column: 2, scope: !3967)
!3977 = !DILocation(line: 1093, column: 20, scope: !3963)
!3978 = !DILocation(line: 1093, column: 27, scope: !3963)
!3979 = !DILocation(line: 1093, column: 43, scope: !3963)
!3980 = !DILocation(line: 1093, column: 50, scope: !3963)
!3981 = !DILocation(line: 1093, column: 42, scope: !3963)
!3982 = !DILocation(line: 1093, column: 3, scope: !3963)
!3983 = !DILocation(line: 1095, column: 6, scope: !3984)
!3984 = distinct !DILexicalBlock(scope: !404, file: !1, line: 1095, column: 6)
!3985 = !DILocation(line: 1095, column: 13, scope: !3984)
!3986 = !DILocation(line: 1095, column: 17, scope: !3984)
!3987 = !DILocation(line: 1095, column: 24, scope: !3984)
!3988 = !DILocation(line: 1095, column: 6, scope: !404)
!3989 = !DILocation(line: 1097, column: 4, scope: !3990)
!3990 = distinct !DILexicalBlock(scope: !3984, file: !1, line: 1095, column: 33)
!3991 = !DILocation(line: 1097, column: 7, scope: !3990)
!3992 = !DILocation(line: 1097, column: 14, scope: !3990)
!3993 = !DILocation(line: 1097, column: 18, scope: !3990)
!3994 = !DILocation(line: 1097, column: 21, scope: !3990)
!3995 = !DILocation(line: 1097, column: 28, scope: !3990)
!3996 = !DILocation(line: 1097, column: 32, scope: !3990)
!3997 = !DILocation(line: 1096, column: 9, scope: !3990)
!3998 = !DILocation(line: 1096, column: 7, scope: !3990)
!3999 = !DILocation(line: 1098, column: 3, scope: !3990)
!4000 = !DILocation(line: 1099, column: 2, scope: !3990)
!4001 = !DILocation(line: 1100, column: 7, scope: !3984)
!4002 = !DILocation(line: 1101, column: 10, scope: !404)
!4003 = !DILocation(line: 1101, column: 2, scope: !404)
!4004 = !DILocalVariable(name: "me", arg: 1, scope: !382, file: !1, line: 583, type: !195)
!4005 = !DILocation(line: 583, column: 38, scope: !382)
!4006 = !DILocalVariable(name: "prev", arg: 2, scope: !382, file: !1, line: 583, type: !306)
!4007 = !DILocation(line: 583, column: 63, scope: !382)
!4008 = !DILocalVariable(name: "ac", scope: !382, file: !1, line: 585, type: !306)
!4009 = !DILocation(line: 585, column: 23, scope: !382)
!4010 = !DILocation(line: 587, column: 7, scope: !382)
!4011 = !DILocation(line: 587, column: 5, scope: !382)
!4012 = !DILocation(line: 588, column: 6, scope: !4013)
!4013 = distinct !DILexicalBlock(scope: !382, file: !1, line: 588, column: 6)
!4014 = !DILocation(line: 588, column: 9, scope: !4013)
!4015 = !DILocation(line: 588, column: 6, scope: !382)
!4016 = !DILocation(line: 589, column: 14, scope: !4017)
!4017 = distinct !DILexicalBlock(scope: !4013, file: !1, line: 588, column: 18)
!4018 = !DILocation(line: 589, column: 3, scope: !4017)
!4019 = !DILocation(line: 589, column: 7, scope: !4017)
!4020 = !DILocation(line: 589, column: 12, scope: !4017)
!4021 = !DILocation(line: 590, column: 3, scope: !4017)
!4022 = !DILocation(line: 590, column: 7, scope: !4017)
!4023 = !DILocation(line: 590, column: 12, scope: !4017)
!4024 = !DILocation(line: 591, column: 3, scope: !4017)
!4025 = !DILocation(line: 591, column: 7, scope: !4017)
!4026 = !DILocation(line: 591, column: 13, scope: !4017)
!4027 = !DILocation(line: 592, column: 17, scope: !4017)
!4028 = !DILocation(line: 592, column: 3, scope: !4017)
!4029 = !DILocation(line: 592, column: 7, scope: !4017)
!4030 = !DILocation(line: 592, column: 15, scope: !4017)
!4031 = !DILocation(line: 593, column: 2, scope: !4017)
!4032 = !DILocation(line: 594, column: 10, scope: !382)
!4033 = !DILocation(line: 594, column: 2, scope: !382)
!4034 = !DILocalVariable(name: "top", arg: 1, scope: !385, file: !1, line: 614, type: !347)
!4035 = !DILocation(line: 614, column: 40, scope: !385)
!4036 = !DILocalVariable(name: "ac", arg: 2, scope: !385, file: !1, line: 614, type: !306)
!4037 = !DILocation(line: 614, column: 66, scope: !385)
!4038 = !DILocalVariable(name: "last", arg: 3, scope: !385, file: !1, line: 615, type: !306)
!4039 = !DILocation(line: 615, column: 26, scope: !385)
!4040 = !DILocalVariable(name: "me", arg: 4, scope: !385, file: !1, line: 615, type: !195)
!4041 = !DILocation(line: 615, column: 52, scope: !385)
!4042 = !DILocalVariable(name: "pac", scope: !385, file: !1, line: 617, type: !306)
!4043 = !DILocation(line: 617, column: 23, scope: !385)
!4044 = !DILocation(line: 619, column: 6, scope: !4045)
!4045 = distinct !DILexicalBlock(scope: !385, file: !1, line: 619, column: 6)
!4046 = !DILocation(line: 619, column: 9, scope: !4045)
!4047 = !DILocation(line: 619, column: 6, scope: !385)
!4048 = !DILocation(line: 620, column: 3, scope: !4049)
!4049 = distinct !DILexicalBlock(scope: !4045, file: !1, line: 619, column: 18)
!4050 = !DILocation(line: 620, column: 7, scope: !4049)
!4051 = !DILocation(line: 620, column: 12, scope: !4049)
!4052 = !DILocation(line: 621, column: 8, scope: !4053)
!4053 = distinct !DILexicalBlock(scope: !4049, file: !1, line: 621, column: 7)
!4054 = !DILocation(line: 621, column: 7, scope: !4053)
!4055 = !DILocation(line: 621, column: 15, scope: !4053)
!4056 = !DILocation(line: 621, column: 12, scope: !4053)
!4057 = !DILocation(line: 621, column: 18, scope: !4053)
!4058 = !DILocation(line: 621, column: 21, scope: !4059)
!4059 = !DILexicalBlockFile(scope: !4053, file: !1, discriminator: 1)
!4060 = !DILocation(line: 621, column: 25, scope: !4059)
!4061 = !DILocation(line: 621, column: 31, scope: !4059)
!4062 = !DILocation(line: 621, column: 40, scope: !4059)
!4063 = !DILocation(line: 621, column: 44, scope: !4059)
!4064 = !DILocation(line: 621, column: 37, scope: !4059)
!4065 = !DILocation(line: 621, column: 7, scope: !4059)
!4066 = !DILocation(line: 622, column: 4, scope: !4053)
!4067 = !DILocation(line: 623, column: 14, scope: !4068)
!4068 = distinct !DILexicalBlock(scope: !4049, file: !1, line: 623, column: 3)
!4069 = !DILocation(line: 623, column: 18, scope: !4068)
!4070 = !DILocation(line: 623, column: 12, scope: !4068)
!4071 = !DILocation(line: 623, column: 8, scope: !4068)
!4072 = !DILocation(line: 623, column: 24, scope: !4073)
!4073 = !DILexicalBlockFile(scope: !4074, file: !1, discriminator: 1)
!4074 = distinct !DILexicalBlock(scope: !4068, file: !1, line: 623, column: 3)
!4075 = !DILocation(line: 623, column: 3, scope: !4073)
!4076 = !DILocation(line: 624, column: 8, scope: !4077)
!4077 = distinct !DILexicalBlock(scope: !4078, file: !1, line: 624, column: 8)
!4078 = distinct !DILexicalBlock(scope: !4074, file: !1, line: 623, column: 46)
!4079 = !DILocation(line: 624, column: 13, scope: !4077)
!4080 = !DILocation(line: 624, column: 22, scope: !4077)
!4081 = !DILocation(line: 624, column: 26, scope: !4077)
!4082 = !DILocation(line: 624, column: 19, scope: !4077)
!4083 = !DILocation(line: 624, column: 8, scope: !4078)
!4084 = !DILocation(line: 625, column: 5, scope: !4077)
!4085 = !DILocation(line: 626, column: 3, scope: !4078)
!4086 = !DILocation(line: 623, column: 35, scope: !4087)
!4087 = !DILexicalBlockFile(scope: !4074, file: !1, discriminator: 2)
!4088 = !DILocation(line: 623, column: 40, scope: !4087)
!4089 = !DILocation(line: 623, column: 33, scope: !4087)
!4090 = !DILocation(line: 623, column: 3, scope: !4087)
!4091 = !DILocation(line: 627, column: 20, scope: !4049)
!4092 = !DILocation(line: 627, column: 24, scope: !4049)
!4093 = !DILocation(line: 627, column: 3, scope: !4049)
!4094 = !DILocation(line: 627, column: 7, scope: !4049)
!4095 = !DILocation(line: 627, column: 13, scope: !4049)
!4096 = !DILocation(line: 627, column: 18, scope: !4049)
!4097 = !DILocation(line: 628, column: 7, scope: !4098)
!4098 = distinct !DILexicalBlock(scope: !4049, file: !1, line: 628, column: 7)
!4099 = !DILocation(line: 628, column: 11, scope: !4098)
!4100 = !DILocation(line: 628, column: 16, scope: !4098)
!4101 = !DILocation(line: 628, column: 7, scope: !4049)
!4102 = !DILocation(line: 629, column: 21, scope: !4098)
!4103 = !DILocation(line: 629, column: 25, scope: !4098)
!4104 = !DILocation(line: 629, column: 4, scope: !4098)
!4105 = !DILocation(line: 629, column: 8, scope: !4098)
!4106 = !DILocation(line: 629, column: 14, scope: !4098)
!4107 = !DILocation(line: 629, column: 19, scope: !4098)
!4108 = !DILocation(line: 630, column: 7, scope: !4109)
!4109 = distinct !DILexicalBlock(scope: !4049, file: !1, line: 630, column: 7)
!4110 = !DILocation(line: 630, column: 11, scope: !4109)
!4111 = !DILocation(line: 630, column: 7, scope: !4049)
!4112 = !DILocation(line: 631, column: 15, scope: !4113)
!4113 = distinct !DILexicalBlock(scope: !4109, file: !1, line: 630, column: 20)
!4114 = !DILocation(line: 631, column: 4, scope: !4113)
!4115 = !DILocation(line: 631, column: 8, scope: !4113)
!4116 = !DILocation(line: 631, column: 13, scope: !4113)
!4117 = !DILocation(line: 632, column: 15, scope: !4113)
!4118 = !DILocation(line: 632, column: 20, scope: !4113)
!4119 = !DILocation(line: 632, column: 4, scope: !4113)
!4120 = !DILocation(line: 632, column: 8, scope: !4113)
!4121 = !DILocation(line: 632, column: 13, scope: !4113)
!4122 = !DILocation(line: 633, column: 16, scope: !4113)
!4123 = !DILocation(line: 633, column: 4, scope: !4113)
!4124 = !DILocation(line: 633, column: 9, scope: !4113)
!4125 = !DILocation(line: 633, column: 14, scope: !4113)
!4126 = !DILocation(line: 634, column: 8, scope: !4127)
!4127 = distinct !DILexicalBlock(scope: !4113, file: !1, line: 634, column: 8)
!4128 = !DILocation(line: 634, column: 12, scope: !4127)
!4129 = !DILocation(line: 634, column: 17, scope: !4127)
!4130 = !DILocation(line: 634, column: 8, scope: !4113)
!4131 = !DILocation(line: 635, column: 22, scope: !4127)
!4132 = !DILocation(line: 635, column: 5, scope: !4127)
!4133 = !DILocation(line: 635, column: 9, scope: !4127)
!4134 = !DILocation(line: 635, column: 15, scope: !4127)
!4135 = !DILocation(line: 635, column: 20, scope: !4127)
!4136 = !DILocation(line: 636, column: 3, scope: !4113)
!4137 = !DILocation(line: 637, column: 4, scope: !4138)
!4138 = distinct !DILexicalBlock(scope: !4109, file: !1, line: 636, column: 10)
!4139 = !DILocation(line: 637, column: 8, scope: !4138)
!4140 = !DILocation(line: 637, column: 13, scope: !4138)
!4141 = !DILocation(line: 638, column: 16, scope: !4138)
!4142 = !DILocation(line: 638, column: 15, scope: !4138)
!4143 = !DILocation(line: 638, column: 4, scope: !4138)
!4144 = !DILocation(line: 638, column: 8, scope: !4138)
!4145 = !DILocation(line: 638, column: 13, scope: !4138)
!4146 = !DILocation(line: 639, column: 11, scope: !4138)
!4147 = !DILocation(line: 639, column: 5, scope: !4138)
!4148 = !DILocation(line: 639, column: 9, scope: !4138)
!4149 = !DILocation(line: 640, column: 21, scope: !4138)
!4150 = !DILocation(line: 640, column: 4, scope: !4138)
!4151 = !DILocation(line: 640, column: 8, scope: !4138)
!4152 = !DILocation(line: 640, column: 14, scope: !4138)
!4153 = !DILocation(line: 640, column: 19, scope: !4138)
!4154 = !DILocation(line: 642, column: 2, scope: !4049)
!4155 = !DILocation(line: 642, column: 13, scope: !4156)
!4156 = !DILexicalBlockFile(scope: !4157, file: !1, discriminator: 1)
!4157 = distinct !DILexicalBlock(scope: !4045, file: !1, line: 642, column: 13)
!4158 = !DILocation(line: 642, column: 18, scope: !4156)
!4159 = !DILocation(line: 643, column: 25, scope: !4160)
!4160 = distinct !DILexicalBlock(scope: !4157, file: !1, line: 642, column: 27)
!4161 = !DILocation(line: 643, column: 29, scope: !4160)
!4162 = !DILocation(line: 643, column: 8, scope: !4160)
!4163 = !DILocation(line: 643, column: 6, scope: !4160)
!4164 = !DILocation(line: 644, column: 7, scope: !4165)
!4165 = distinct !DILexicalBlock(scope: !4160, file: !1, line: 644, column: 7)
!4166 = !DILocation(line: 644, column: 10, scope: !4165)
!4167 = !DILocation(line: 644, column: 7, scope: !4160)
!4168 = !DILocation(line: 645, column: 4, scope: !4165)
!4169 = !DILocation(line: 646, column: 16, scope: !4160)
!4170 = !DILocation(line: 646, column: 3, scope: !4160)
!4171 = !DILocation(line: 646, column: 9, scope: !4160)
!4172 = !DILocation(line: 646, column: 14, scope: !4160)
!4173 = !DILocation(line: 647, column: 2, scope: !4160)
!4174 = !DILocation(line: 648, column: 2, scope: !385)
!4175 = !DILocation(line: 649, column: 1, scope: !385)
!4176 = !DILocalVariable(name: "s", arg: 1, scope: !391, file: !1, line: 349, type: !394)
!4177 = !DILocation(line: 349, column: 36, scope: !391)
!4178 = !DILocalVariable(name: "str", arg: 2, scope: !391, file: !1, line: 349, type: !80)
!4179 = !DILocation(line: 349, column: 51, scope: !391)
!4180 = !DILocalVariable(name: "start", scope: !391, file: !1, line: 351, type: !80)
!4181 = !DILocation(line: 351, column: 14, scope: !391)
!4182 = !DILocalVariable(name: "buf", scope: !391, file: !1, line: 352, type: !4183)
!4183 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 32, align: 8, elements: !4184)
!4184 = !{!4185}
!4185 = !DISubrange(count: 4)
!4186 = !DILocation(line: 352, column: 7, scope: !391)
!4187 = !DILocalVariable(name: "c", scope: !391, file: !1, line: 353, type: !116)
!4188 = !DILocation(line: 353, column: 16, scope: !391)
!4189 = !DILocation(line: 355, column: 15, scope: !4190)
!4190 = distinct !DILexicalBlock(scope: !391, file: !1, line: 355, column: 2)
!4191 = !DILocation(line: 355, column: 13, scope: !4190)
!4192 = !DILocation(line: 355, column: 7, scope: !4190)
!4193 = !DILocation(line: 355, column: 21, scope: !4194)
!4194 = !DILexicalBlockFile(scope: !4195, file: !1, discriminator: 1)
!4195 = distinct !DILexicalBlock(scope: !4190, file: !1, line: 355, column: 2)
!4196 = !DILocation(line: 355, column: 20, scope: !4194)
!4197 = !DILocation(line: 355, column: 25, scope: !4194)
!4198 = !DILocation(line: 355, column: 2, scope: !4194)
!4199 = !DILocation(line: 356, column: 41, scope: !4200)
!4200 = distinct !DILexicalBlock(scope: !4201, file: !1, line: 356, column: 7)
!4201 = distinct !DILexicalBlock(scope: !4195, file: !1, line: 355, column: 41)
!4202 = !DILocation(line: 356, column: 17, scope: !4200)
!4203 = !DILocation(line: 356, column: 7, scope: !4200)
!4204 = !DILocation(line: 356, column: 7, scope: !4201)
!4205 = !DILocation(line: 357, column: 4, scope: !4200)
!4206 = !DILocation(line: 358, column: 7, scope: !4207)
!4207 = distinct !DILexicalBlock(scope: !4201, file: !1, line: 358, column: 7)
!4208 = !DILocation(line: 358, column: 16, scope: !4207)
!4209 = !DILocation(line: 358, column: 13, scope: !4207)
!4210 = !DILocation(line: 358, column: 7, scope: !4201)
!4211 = !DILocation(line: 359, column: 20, scope: !4207)
!4212 = !DILocation(line: 359, column: 23, scope: !4207)
!4213 = !DILocation(line: 359, column: 30, scope: !4207)
!4214 = !DILocation(line: 359, column: 36, scope: !4207)
!4215 = !DILocation(line: 359, column: 34, scope: !4207)
!4216 = !DILocation(line: 359, column: 4, scope: !4207)
!4217 = !DILocation(line: 360, column: 23, scope: !4201)
!4218 = !DILocation(line: 360, column: 22, scope: !4201)
!4219 = !DILocation(line: 360, column: 5, scope: !4201)
!4220 = !DILocation(line: 361, column: 3, scope: !4201)
!4221 = !DILocation(line: 361, column: 10, scope: !4201)
!4222 = !DILocation(line: 362, column: 13, scope: !4201)
!4223 = !DILocation(line: 362, column: 15, scope: !4201)
!4224 = !DILocation(line: 362, column: 21, scope: !4201)
!4225 = !DILocation(line: 362, column: 12, scope: !4201)
!4226 = !DILocation(line: 362, column: 3, scope: !4201)
!4227 = !DILocation(line: 362, column: 10, scope: !4201)
!4228 = !DILocation(line: 363, column: 13, scope: !4201)
!4229 = !DILocation(line: 363, column: 15, scope: !4201)
!4230 = !DILocation(line: 363, column: 19, scope: !4201)
!4231 = !DILocation(line: 363, column: 24, scope: !4201)
!4232 = !DILocation(line: 363, column: 12, scope: !4201)
!4233 = !DILocation(line: 363, column: 3, scope: !4201)
!4234 = !DILocation(line: 363, column: 10, scope: !4201)
!4235 = !DILocation(line: 364, column: 13, scope: !4201)
!4236 = !DILocation(line: 364, column: 15, scope: !4201)
!4237 = !DILocation(line: 364, column: 20, scope: !4201)
!4238 = !DILocation(line: 364, column: 12, scope: !4201)
!4239 = !DILocation(line: 364, column: 3, scope: !4201)
!4240 = !DILocation(line: 364, column: 10, scope: !4201)
!4241 = !DILocation(line: 365, column: 19, scope: !4201)
!4242 = !DILocation(line: 365, column: 22, scope: !4201)
!4243 = !DILocation(line: 365, column: 3, scope: !4201)
!4244 = !DILocation(line: 366, column: 11, scope: !4201)
!4245 = !DILocation(line: 366, column: 15, scope: !4201)
!4246 = !DILocation(line: 366, column: 9, scope: !4201)
!4247 = !DILocation(line: 367, column: 2, scope: !4201)
!4248 = !DILocation(line: 355, column: 34, scope: !4249)
!4249 = !DILexicalBlockFile(scope: !4195, file: !1, discriminator: 2)
!4250 = !DILocation(line: 355, column: 2, scope: !4249)
!4251 = !DILocation(line: 369, column: 6, scope: !4252)
!4252 = distinct !DILexicalBlock(scope: !391, file: !1, line: 369, column: 6)
!4253 = !DILocation(line: 369, column: 15, scope: !4252)
!4254 = !DILocation(line: 369, column: 12, scope: !4252)
!4255 = !DILocation(line: 369, column: 6, scope: !391)
!4256 = !DILocation(line: 370, column: 19, scope: !4252)
!4257 = !DILocation(line: 370, column: 22, scope: !4252)
!4258 = !DILocation(line: 370, column: 29, scope: !4252)
!4259 = !DILocation(line: 370, column: 35, scope: !4252)
!4260 = !DILocation(line: 370, column: 33, scope: !4252)
!4261 = !DILocation(line: 370, column: 3, scope: !4252)
!4262 = !DILocation(line: 371, column: 1, scope: !391)
!4263 = !DILocalVariable(name: "mtree", arg: 1, scope: !395, file: !1, line: 743, type: !191)
!4264 = !DILocation(line: 743, column: 42, scope: !395)
!4265 = !DILocalVariable(name: "me", arg: 2, scope: !395, file: !1, line: 743, type: !195)
!4266 = !DILocation(line: 743, column: 69, scope: !395)
!4267 = !DILocalVariable(name: "keys", scope: !395, file: !1, line: 745, type: !23)
!4268 = !DILocation(line: 745, column: 6, scope: !395)
!4269 = !DILocation(line: 747, column: 9, scope: !395)
!4270 = !DILocation(line: 747, column: 16, scope: !395)
!4271 = !DILocation(line: 747, column: 7, scope: !395)
!4272 = !DILocation(line: 753, column: 6, scope: !4273)
!4273 = distinct !DILexicalBlock(scope: !395, file: !1, line: 753, column: 6)
!4274 = !DILocation(line: 753, column: 13, scope: !4273)
!4275 = !DILocation(line: 753, column: 17, scope: !4273)
!4276 = !DILocation(line: 753, column: 22, scope: !4273)
!4277 = !DILocation(line: 753, column: 6, scope: !395)
!4278 = !DILocation(line: 754, column: 11, scope: !4273)
!4279 = !DILocation(line: 754, column: 3, scope: !4273)
!4280 = !DILocation(line: 756, column: 7, scope: !4281)
!4281 = distinct !DILexicalBlock(scope: !395, file: !1, line: 756, column: 6)
!4282 = !DILocation(line: 756, column: 14, scope: !4281)
!4283 = !DILocation(line: 756, column: 18, scope: !4281)
!4284 = !DILocation(line: 756, column: 23, scope: !4281)
!4285 = !DILocation(line: 756, column: 44, scope: !4281)
!4286 = !DILocation(line: 756, column: 49, scope: !4281)
!4287 = !DILocation(line: 757, column: 7, scope: !4281)
!4288 = !DILocation(line: 757, column: 14, scope: !4281)
!4289 = !DILocation(line: 757, column: 18, scope: !4281)
!4290 = !DILocation(line: 757, column: 25, scope: !4281)
!4291 = !DILocation(line: 757, column: 29, scope: !4281)
!4292 = !DILocation(line: 757, column: 22, scope: !4281)
!4293 = !DILocation(line: 756, column: 6, scope: !4294)
!4294 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 1)
!4295 = !DILocation(line: 758, column: 8, scope: !4281)
!4296 = !DILocation(line: 758, column: 3, scope: !4281)
!4297 = !DILocation(line: 759, column: 7, scope: !4298)
!4298 = distinct !DILexicalBlock(scope: !395, file: !1, line: 759, column: 6)
!4299 = !DILocation(line: 759, column: 14, scope: !4298)
!4300 = !DILocation(line: 759, column: 18, scope: !4298)
!4301 = !DILocation(line: 759, column: 23, scope: !4298)
!4302 = !DILocation(line: 759, column: 44, scope: !4298)
!4303 = !DILocation(line: 759, column: 49, scope: !4298)
!4304 = !DILocation(line: 760, column: 7, scope: !4298)
!4305 = !DILocation(line: 760, column: 14, scope: !4298)
!4306 = !DILocation(line: 760, column: 18, scope: !4298)
!4307 = !DILocation(line: 760, column: 25, scope: !4298)
!4308 = !DILocation(line: 760, column: 29, scope: !4298)
!4309 = !DILocation(line: 760, column: 22, scope: !4298)
!4310 = !DILocation(line: 759, column: 6, scope: !4294)
!4311 = !DILocation(line: 761, column: 8, scope: !4298)
!4312 = !DILocation(line: 761, column: 3, scope: !4298)
!4313 = !DILocation(line: 762, column: 6, scope: !4314)
!4314 = distinct !DILexicalBlock(scope: !395, file: !1, line: 762, column: 6)
!4315 = !DILocation(line: 762, column: 13, scope: !4314)
!4316 = !DILocation(line: 762, column: 17, scope: !4314)
!4317 = !DILocation(line: 762, column: 22, scope: !4314)
!4318 = !DILocation(line: 762, column: 6, scope: !395)
!4319 = !DILocation(line: 763, column: 7, scope: !4320)
!4320 = distinct !DILexicalBlock(scope: !4321, file: !1, line: 763, column: 7)
!4321 = distinct !DILexicalBlock(scope: !4314, file: !1, line: 762, column: 33)
!4322 = !DILocation(line: 763, column: 14, scope: !4320)
!4323 = !DILocation(line: 763, column: 18, scope: !4320)
!4324 = !DILocation(line: 763, column: 32, scope: !4320)
!4325 = !DILocation(line: 763, column: 36, scope: !4320)
!4326 = !DILocation(line: 763, column: 29, scope: !4320)
!4327 = !DILocation(line: 763, column: 47, scope: !4320)
!4328 = !DILocation(line: 764, column: 7, scope: !4320)
!4329 = !DILocation(line: 764, column: 14, scope: !4320)
!4330 = !DILocation(line: 764, column: 18, scope: !4320)
!4331 = !DILocation(line: 764, column: 34, scope: !4320)
!4332 = !DILocation(line: 764, column: 38, scope: !4320)
!4333 = !DILocation(line: 764, column: 31, scope: !4320)
!4334 = !DILocation(line: 763, column: 7, scope: !4335)
!4335 = !DILexicalBlockFile(scope: !4321, file: !1, discriminator: 1)
!4336 = !DILocation(line: 765, column: 9, scope: !4320)
!4337 = !DILocation(line: 765, column: 4, scope: !4320)
!4338 = !DILocation(line: 766, column: 2, scope: !4321)
!4339 = !DILocation(line: 767, column: 7, scope: !4340)
!4340 = distinct !DILexicalBlock(scope: !395, file: !1, line: 767, column: 6)
!4341 = !DILocation(line: 767, column: 14, scope: !4340)
!4342 = !DILocation(line: 767, column: 18, scope: !4340)
!4343 = !DILocation(line: 767, column: 23, scope: !4340)
!4344 = !DILocation(line: 767, column: 33, scope: !4340)
!4345 = !DILocation(line: 767, column: 38, scope: !4340)
!4346 = !DILocation(line: 767, column: 41, scope: !4347)
!4347 = !DILexicalBlockFile(scope: !4340, file: !1, discriminator: 1)
!4348 = !DILocation(line: 767, column: 48, scope: !4347)
!4349 = !DILocation(line: 767, column: 52, scope: !4347)
!4350 = !DILocation(line: 767, column: 60, scope: !4347)
!4351 = !DILocation(line: 767, column: 64, scope: !4347)
!4352 = !DILocation(line: 767, column: 57, scope: !4347)
!4353 = !DILocation(line: 767, column: 6, scope: !4347)
!4354 = !DILocation(line: 768, column: 8, scope: !4340)
!4355 = !DILocation(line: 768, column: 3, scope: !4340)
!4356 = !DILocation(line: 770, column: 10, scope: !395)
!4357 = !DILocation(line: 770, column: 14, scope: !395)
!4358 = !DILocation(line: 770, column: 2, scope: !395)
!4359 = !DILocation(line: 773, column: 3, scope: !4360)
!4360 = distinct !DILexicalBlock(scope: !395, file: !1, line: 770, column: 24)
!4361 = !DILocation(line: 775, column: 8, scope: !4362)
!4362 = distinct !DILexicalBlock(scope: !4360, file: !1, line: 775, column: 7)
!4363 = !DILocation(line: 775, column: 15, scope: !4362)
!4364 = !DILocation(line: 775, column: 19, scope: !4362)
!4365 = !DILocation(line: 775, column: 24, scope: !4362)
!4366 = !DILocation(line: 775, column: 34, scope: !4362)
!4367 = !DILocation(line: 775, column: 39, scope: !4362)
!4368 = !DILocation(line: 776, column: 7, scope: !4362)
!4369 = !DILocation(line: 776, column: 14, scope: !4362)
!4370 = !DILocation(line: 776, column: 18, scope: !4362)
!4371 = !DILocation(line: 776, column: 23, scope: !4362)
!4372 = !DILocation(line: 775, column: 7, scope: !4373)
!4373 = !DILexicalBlockFile(scope: !4360, file: !1, discriminator: 1)
!4374 = !DILocation(line: 777, column: 9, scope: !4362)
!4375 = !DILocation(line: 777, column: 4, scope: !4362)
!4376 = !DILocation(line: 778, column: 3, scope: !4360)
!4377 = !DILocation(line: 778, column: 3, scope: !4373)
!4378 = !DILocation(line: 781, column: 8, scope: !4379)
!4379 = distinct !DILexicalBlock(scope: !4360, file: !1, line: 781, column: 7)
!4380 = !DILocation(line: 781, column: 15, scope: !4379)
!4381 = !DILocation(line: 781, column: 19, scope: !4379)
!4382 = !DILocation(line: 781, column: 24, scope: !4379)
!4383 = !DILocation(line: 781, column: 34, scope: !4379)
!4384 = !DILocation(line: 781, column: 39, scope: !4379)
!4385 = !DILocation(line: 782, column: 7, scope: !4379)
!4386 = !DILocation(line: 782, column: 14, scope: !4379)
!4387 = !DILocation(line: 782, column: 18, scope: !4379)
!4388 = !DILocation(line: 782, column: 23, scope: !4379)
!4389 = !DILocation(line: 781, column: 7, scope: !4373)
!4390 = !DILocation(line: 783, column: 9, scope: !4379)
!4391 = !DILocation(line: 783, column: 4, scope: !4379)
!4392 = !DILocation(line: 784, column: 3, scope: !4360)
!4393 = !DILocation(line: 787, column: 10, scope: !395)
!4394 = !DILocation(line: 787, column: 2, scope: !395)
!4395 = !DILocation(line: 788, column: 1, scope: !395)
!4396 = !DILocalVariable(name: "str", arg: 1, scope: !396, file: !1, line: 1617, type: !394)
!4397 = !DILocation(line: 1617, column: 34, scope: !396)
!4398 = !DILocalVariable(name: "reg", arg: 2, scope: !396, file: !1, line: 1617, type: !247)
!4399 = !DILocation(line: 1617, column: 56, scope: !396)
!4400 = !DILocation(line: 1620, column: 6, scope: !4401)
!4401 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1620, column: 6)
!4402 = !DILocation(line: 1620, column: 11, scope: !4401)
!4403 = !DILocation(line: 1620, column: 23, scope: !4401)
!4404 = !DILocation(line: 1620, column: 6, scope: !396)
!4405 = !DILocation(line: 1621, column: 26, scope: !4406)
!4406 = distinct !DILexicalBlock(scope: !4401, file: !1, line: 1620, column: 34)
!4407 = !DILocation(line: 1622, column: 18, scope: !4406)
!4408 = !DILocation(line: 1622, column: 23, scope: !4406)
!4409 = !DILocation(line: 1622, column: 7, scope: !4406)
!4410 = !DILocation(line: 1621, column: 3, scope: !4406)
!4411 = !DILocation(line: 1623, column: 2, scope: !4406)
!4412 = !DILocation(line: 1660, column: 1, scope: !396)
!4413 = !DILocalVariable(name: "mtree", arg: 1, scope: !399, file: !1, line: 377, type: !191)
!4414 = !DILocation(line: 377, column: 35, scope: !399)
!4415 = !DILocalVariable(name: "i", scope: !399, file: !1, line: 379, type: !23)
!4416 = !DILocation(line: 379, column: 6, scope: !399)
!4417 = !DILocalVariable(name: "fn", scope: !399, file: !1, line: 379, type: !23)
!4418 = !DILocation(line: 379, column: 9, scope: !399)
!4419 = !DILocalVariable(name: "nd", scope: !399, file: !1, line: 379, type: !23)
!4420 = !DILocation(line: 379, column: 13, scope: !399)
!4421 = !DILocalVariable(name: "pd", scope: !399, file: !1, line: 379, type: !23)
!4422 = !DILocation(line: 379, column: 17, scope: !399)
!4423 = !DILocalVariable(name: "r", scope: !399, file: !1, line: 380, type: !80)
!4424 = !DILocation(line: 380, column: 14, scope: !399)
!4425 = !DILocalVariable(name: "s", scope: !399, file: !1, line: 380, type: !80)
!4426 = !DILocation(line: 380, column: 18, scope: !399)
!4427 = !DILocalVariable(name: "x", scope: !399, file: !1, line: 380, type: !80)
!4428 = !DILocation(line: 380, column: 22, scope: !399)
!4429 = !DILocation(line: 382, column: 6, scope: !4430)
!4430 = distinct !DILexicalBlock(scope: !399, file: !1, line: 382, column: 6)
!4431 = !DILocation(line: 382, column: 13, scope: !4430)
!4432 = !DILocation(line: 382, column: 6, scope: !399)
!4433 = !DILocation(line: 383, column: 7, scope: !4434)
!4434 = distinct !DILexicalBlock(scope: !4435, file: !1, line: 383, column: 7)
!4435 = distinct !DILexicalBlock(scope: !4430, file: !1, line: 382, column: 22)
!4436 = !DILocation(line: 383, column: 14, scope: !4434)
!4437 = !DILocation(line: 383, column: 7, scope: !4435)
!4438 = !DILocation(line: 384, column: 7, scope: !4439)
!4439 = distinct !DILexicalBlock(scope: !4434, file: !1, line: 383, column: 22)
!4440 = !DILocation(line: 385, column: 9, scope: !4439)
!4441 = !DILocation(line: 385, column: 16, scope: !4439)
!4442 = !DILocation(line: 385, column: 22, scope: !4439)
!4443 = !DILocation(line: 385, column: 7, scope: !4439)
!4444 = !DILocation(line: 386, column: 3, scope: !4439)
!4445 = !DILocation(line: 387, column: 9, scope: !4446)
!4446 = distinct !DILexicalBlock(scope: !4434, file: !1, line: 386, column: 10)
!4447 = !DILocation(line: 387, column: 16, scope: !4446)
!4448 = !DILocation(line: 387, column: 7, scope: !4446)
!4449 = !DILocation(line: 388, column: 7, scope: !4446)
!4450 = !DILocation(line: 390, column: 2, scope: !4435)
!4451 = !DILocation(line: 391, column: 11, scope: !4430)
!4452 = !DILocation(line: 391, column: 6, scope: !4430)
!4453 = !DILocation(line: 392, column: 5, scope: !399)
!4454 = !DILocation(line: 393, column: 10, scope: !399)
!4455 = !DILocation(line: 393, column: 17, scope: !399)
!4456 = !DILocation(line: 393, column: 22, scope: !399)
!4457 = !DILocation(line: 393, column: 8, scope: !399)
!4458 = !DILocation(line: 393, column: 4, scope: !399)
!4459 = !DILocation(line: 394, column: 4, scope: !399)
!4460 = !DILocation(line: 395, column: 2, scope: !399)
!4461 = !DILocation(line: 395, column: 10, scope: !4462)
!4462 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!4463 = !DILocation(line: 395, column: 9, scope: !4462)
!4464 = !DILocation(line: 395, column: 12, scope: !4462)
!4465 = !DILocation(line: 395, column: 2, scope: !4462)
!4466 = !DILocation(line: 396, column: 4, scope: !399)
!4467 = !DILocation(line: 395, column: 2, scope: !4468)
!4468 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 2)
!4469 = !DILocation(line: 397, column: 2, scope: !399)
!4470 = !DILocation(line: 397, column: 21, scope: !4462)
!4471 = !DILocation(line: 397, column: 14, scope: !4462)
!4472 = !DILocation(line: 397, column: 12, scope: !4462)
!4473 = !DILocation(line: 397, column: 30, scope: !4462)
!4474 = !DILocation(line: 397, column: 2, scope: !4462)
!4475 = !DILocation(line: 398, column: 7, scope: !4476)
!4476 = distinct !DILexicalBlock(scope: !4477, file: !1, line: 398, column: 7)
!4477 = distinct !DILexicalBlock(scope: !399, file: !1, line: 397, column: 39)
!4478 = !DILocation(line: 398, column: 7, scope: !4477)
!4479 = !DILocation(line: 399, column: 7, scope: !4480)
!4480 = distinct !DILexicalBlock(scope: !4476, file: !1, line: 398, column: 11)
!4481 = !DILocation(line: 400, column: 11, scope: !4482)
!4482 = distinct !DILexicalBlock(scope: !4480, file: !1, line: 400, column: 4)
!4483 = !DILocation(line: 400, column: 9, scope: !4482)
!4484 = !DILocation(line: 400, column: 16, scope: !4485)
!4485 = !DILexicalBlockFile(scope: !4486, file: !1, discriminator: 1)
!4486 = distinct !DILexicalBlock(scope: !4482, file: !1, line: 400, column: 4)
!4487 = !DILocation(line: 400, column: 20, scope: !4485)
!4488 = !DILocation(line: 400, column: 25, scope: !4485)
!4489 = !DILocation(line: 400, column: 23, scope: !4485)
!4490 = !DILocation(line: 400, column: 18, scope: !4485)
!4491 = !DILocation(line: 400, column: 4, scope: !4485)
!4492 = !DILocation(line: 401, column: 29, scope: !4486)
!4493 = !DILocation(line: 401, column: 36, scope: !4486)
!4494 = !DILocation(line: 401, column: 5, scope: !4486)
!4495 = !DILocation(line: 400, column: 30, scope: !4496)
!4496 = !DILexicalBlockFile(scope: !4486, file: !1, discriminator: 2)
!4497 = !DILocation(line: 400, column: 4, scope: !4496)
!4498 = !DILocation(line: 402, column: 21, scope: !4480)
!4499 = !DILocation(line: 402, column: 28, scope: !4480)
!4500 = !DILocation(line: 402, column: 33, scope: !4480)
!4501 = !DILocation(line: 402, column: 36, scope: !4480)
!4502 = !DILocation(line: 402, column: 40, scope: !4480)
!4503 = !DILocation(line: 402, column: 38, scope: !4480)
!4504 = !DILocation(line: 402, column: 4, scope: !4480)
!4505 = !DILocation(line: 403, column: 8, scope: !4506)
!4506 = distinct !DILexicalBlock(scope: !4480, file: !1, line: 403, column: 8)
!4507 = !DILocation(line: 403, column: 14, scope: !4506)
!4508 = !DILocation(line: 403, column: 17, scope: !4506)
!4509 = !DILocation(line: 403, column: 16, scope: !4506)
!4510 = !DILocation(line: 403, column: 11, scope: !4506)
!4511 = !DILocation(line: 403, column: 20, scope: !4506)
!4512 = !DILocation(line: 403, column: 8, scope: !4480)
!4513 = !DILocation(line: 404, column: 22, scope: !4514)
!4514 = distinct !DILexicalBlock(scope: !4506, file: !1, line: 403, column: 37)
!4515 = !DILocation(line: 404, column: 29, scope: !4514)
!4516 = !DILocation(line: 404, column: 5, scope: !4514)
!4517 = !DILocation(line: 405, column: 12, scope: !4518)
!4518 = distinct !DILexicalBlock(scope: !4514, file: !1, line: 405, column: 5)
!4519 = !DILocation(line: 405, column: 10, scope: !4518)
!4520 = !DILocation(line: 405, column: 17, scope: !4521)
!4521 = !DILexicalBlockFile(scope: !4522, file: !1, discriminator: 1)
!4522 = distinct !DILexicalBlock(scope: !4518, file: !1, line: 405, column: 5)
!4523 = !DILocation(line: 405, column: 42, scope: !4521)
!4524 = !DILocation(line: 405, column: 40, scope: !4521)
!4525 = !DILocation(line: 405, column: 19, scope: !4521)
!4526 = !DILocation(line: 405, column: 5, scope: !4521)
!4527 = !DILocation(line: 406, column: 30, scope: !4522)
!4528 = !DILocation(line: 406, column: 37, scope: !4522)
!4529 = !DILocation(line: 406, column: 6, scope: !4522)
!4530 = !DILocation(line: 405, column: 48, scope: !4531)
!4531 = !DILexicalBlockFile(scope: !4522, file: !1, discriminator: 2)
!4532 = !DILocation(line: 405, column: 5, scope: !4531)
!4533 = !DILocation(line: 407, column: 4, scope: !4514)
!4534 = !DILocation(line: 408, column: 20, scope: !4535)
!4535 = distinct !DILexicalBlock(scope: !4536, file: !1, line: 408, column: 5)
!4536 = distinct !DILexicalBlock(scope: !4506, file: !1, line: 407, column: 11)
!4537 = !DILocation(line: 408, column: 23, scope: !4535)
!4538 = !DILocation(line: 408, column: 22, scope: !4535)
!4539 = !DILocation(line: 408, column: 27, scope: !4535)
!4540 = !DILocation(line: 408, column: 25, scope: !4535)
!4541 = !DILocation(line: 408, column: 14, scope: !4535)
!4542 = !DILocation(line: 408, column: 12, scope: !4535)
!4543 = !DILocation(line: 408, column: 10, scope: !4535)
!4544 = !DILocation(line: 409, column: 9, scope: !4545)
!4545 = distinct !DILexicalBlock(scope: !4535, file: !1, line: 408, column: 5)
!4546 = !DILocation(line: 409, column: 11, scope: !4545)
!4547 = !DILocation(line: 408, column: 5, scope: !4548)
!4548 = !DILexicalBlockFile(scope: !4535, file: !1, discriminator: 1)
!4549 = !DILocation(line: 410, column: 30, scope: !4545)
!4550 = !DILocation(line: 410, column: 37, scope: !4545)
!4551 = !DILocation(line: 410, column: 6, scope: !4545)
!4552 = !DILocation(line: 409, column: 35, scope: !4553)
!4553 = !DILexicalBlockFile(scope: !4545, file: !1, discriminator: 1)
!4554 = !DILocation(line: 408, column: 5, scope: !4555)
!4555 = !DILexicalBlockFile(scope: !4545, file: !1, discriminator: 2)
!4556 = !DILocation(line: 412, column: 8, scope: !4480)
!4557 = !DILocation(line: 412, column: 6, scope: !4480)
!4558 = !DILocation(line: 413, column: 6, scope: !4480)
!4559 = !DILocation(line: 414, column: 4, scope: !4480)
!4560 = !DILocation(line: 416, column: 7, scope: !4561)
!4561 = distinct !DILexicalBlock(scope: !4477, file: !1, line: 416, column: 7)
!4562 = !DILocation(line: 416, column: 13, scope: !4561)
!4563 = !DILocation(line: 416, column: 17, scope: !4561)
!4564 = !DILocation(line: 416, column: 15, scope: !4561)
!4565 = !DILocation(line: 416, column: 10, scope: !4561)
!4566 = !DILocation(line: 416, column: 20, scope: !4561)
!4567 = !DILocation(line: 416, column: 7, scope: !4477)
!4568 = !DILocation(line: 417, column: 9, scope: !4561)
!4569 = !DILocation(line: 417, column: 6, scope: !4561)
!4570 = !DILocation(line: 417, column: 4, scope: !4561)
!4571 = !DILocation(line: 419, column: 8, scope: !4572)
!4572 = distinct !DILexicalBlock(scope: !4573, file: !1, line: 419, column: 8)
!4573 = distinct !DILexicalBlock(scope: !4561, file: !1, line: 418, column: 8)
!4574 = !DILocation(line: 419, column: 10, scope: !4572)
!4575 = !DILocation(line: 419, column: 8, scope: !4573)
!4576 = !DILocation(line: 420, column: 9, scope: !4572)
!4577 = !DILocation(line: 420, column: 7, scope: !4572)
!4578 = !DILocation(line: 420, column: 5, scope: !4572)
!4579 = !DILocation(line: 421, column: 21, scope: !4573)
!4580 = !DILocation(line: 421, column: 28, scope: !4573)
!4581 = !DILocation(line: 421, column: 33, scope: !4573)
!4582 = !DILocation(line: 421, column: 36, scope: !4573)
!4583 = !DILocation(line: 421, column: 40, scope: !4573)
!4584 = !DILocation(line: 421, column: 38, scope: !4573)
!4585 = !DILocation(line: 421, column: 4, scope: !4573)
!4586 = !DILocation(line: 422, column: 21, scope: !4573)
!4587 = !DILocation(line: 422, column: 28, scope: !4573)
!4588 = !DILocation(line: 422, column: 4, scope: !4573)
!4589 = !DILocation(line: 423, column: 11, scope: !4590)
!4590 = distinct !DILexicalBlock(scope: !4573, file: !1, line: 423, column: 4)
!4591 = !DILocation(line: 423, column: 9, scope: !4590)
!4592 = !DILocation(line: 423, column: 16, scope: !4593)
!4593 = !DILexicalBlockFile(scope: !4594, file: !1, discriminator: 1)
!4594 = distinct !DILexicalBlock(scope: !4590, file: !1, line: 423, column: 4)
!4595 = !DILocation(line: 423, column: 41, scope: !4593)
!4596 = !DILocation(line: 423, column: 39, scope: !4593)
!4597 = !DILocation(line: 423, column: 18, scope: !4593)
!4598 = !DILocation(line: 423, column: 4, scope: !4593)
!4599 = !DILocation(line: 424, column: 29, scope: !4594)
!4600 = !DILocation(line: 424, column: 36, scope: !4594)
!4601 = !DILocation(line: 424, column: 5, scope: !4594)
!4602 = !DILocation(line: 423, column: 47, scope: !4603)
!4603 = !DILexicalBlockFile(scope: !4594, file: !1, discriminator: 2)
!4604 = !DILocation(line: 423, column: 4, scope: !4603)
!4605 = !DILocation(line: 425, column: 12, scope: !4573)
!4606 = !DILocation(line: 425, column: 10, scope: !4573)
!4607 = !DILocation(line: 425, column: 6, scope: !4573)
!4608 = !DILocation(line: 426, column: 6, scope: !4573)
!4609 = !DILocation(line: 397, column: 2, scope: !4468)
!4610 = !DILocation(line: 429, column: 6, scope: !4611)
!4611 = distinct !DILexicalBlock(scope: !399, file: !1, line: 429, column: 6)
!4612 = !DILocation(line: 429, column: 6, scope: !399)
!4613 = !DILocation(line: 430, column: 10, scope: !4614)
!4614 = distinct !DILexicalBlock(scope: !4615, file: !1, line: 430, column: 3)
!4615 = distinct !DILexicalBlock(scope: !4611, file: !1, line: 429, column: 10)
!4616 = !DILocation(line: 430, column: 8, scope: !4614)
!4617 = !DILocation(line: 430, column: 15, scope: !4618)
!4618 = !DILexicalBlockFile(scope: !4619, file: !1, discriminator: 1)
!4619 = distinct !DILexicalBlock(scope: !4614, file: !1, line: 430, column: 3)
!4620 = !DILocation(line: 430, column: 19, scope: !4618)
!4621 = !DILocation(line: 430, column: 24, scope: !4618)
!4622 = !DILocation(line: 430, column: 22, scope: !4618)
!4623 = !DILocation(line: 430, column: 17, scope: !4618)
!4624 = !DILocation(line: 430, column: 3, scope: !4618)
!4625 = !DILocation(line: 431, column: 28, scope: !4619)
!4626 = !DILocation(line: 431, column: 35, scope: !4619)
!4627 = !DILocation(line: 431, column: 4, scope: !4619)
!4628 = !DILocation(line: 430, column: 29, scope: !4629)
!4629 = !DILexicalBlockFile(scope: !4619, file: !1, discriminator: 2)
!4630 = !DILocation(line: 430, column: 3, scope: !4629)
!4631 = !DILocation(line: 432, column: 19, scope: !4615)
!4632 = !DILocation(line: 432, column: 26, scope: !4615)
!4633 = !DILocation(line: 432, column: 31, scope: !4615)
!4634 = !DILocation(line: 432, column: 3, scope: !4615)
!4635 = !DILocation(line: 433, column: 15, scope: !4615)
!4636 = !DILocation(line: 433, column: 8, scope: !4615)
!4637 = !DILocation(line: 433, column: 5, scope: !4615)
!4638 = !DILocation(line: 434, column: 2, scope: !4615)
!4639 = !DILocation(line: 435, column: 6, scope: !4640)
!4640 = distinct !DILexicalBlock(scope: !399, file: !1, line: 435, column: 6)
!4641 = !DILocation(line: 435, column: 8, scope: !4640)
!4642 = !DILocation(line: 435, column: 16, scope: !4640)
!4643 = !DILocation(line: 435, column: 19, scope: !4644)
!4644 = !DILexicalBlockFile(scope: !4640, file: !1, discriminator: 1)
!4645 = !DILocation(line: 435, column: 31, scope: !4644)
!4646 = !DILocation(line: 435, column: 24, scope: !4644)
!4647 = !DILocation(line: 435, column: 22, scope: !4644)
!4648 = !DILocation(line: 435, column: 34, scope: !4644)
!4649 = !DILocation(line: 435, column: 6, scope: !4644)
!4650 = !DILocation(line: 437, column: 20, scope: !4651)
!4651 = distinct !DILexicalBlock(scope: !4640, file: !1, line: 435, column: 68)
!4652 = !DILocation(line: 437, column: 27, scope: !4651)
!4653 = !DILocation(line: 437, column: 32, scope: !4651)
!4654 = !DILocation(line: 437, column: 35, scope: !4651)
!4655 = !DILocation(line: 437, column: 39, scope: !4651)
!4656 = !DILocation(line: 437, column: 37, scope: !4651)
!4657 = !DILocation(line: 437, column: 3, scope: !4651)
!4658 = !DILocation(line: 438, column: 20, scope: !4651)
!4659 = !DILocation(line: 438, column: 27, scope: !4651)
!4660 = !DILocation(line: 438, column: 3, scope: !4651)
!4661 = !DILocation(line: 439, column: 10, scope: !4662)
!4662 = distinct !DILexicalBlock(scope: !4651, file: !1, line: 439, column: 3)
!4663 = !DILocation(line: 439, column: 8, scope: !4662)
!4664 = !DILocation(line: 439, column: 15, scope: !4665)
!4665 = !DILexicalBlockFile(scope: !4666, file: !1, discriminator: 1)
!4666 = distinct !DILexicalBlock(scope: !4662, file: !1, line: 439, column: 3)
!4667 = !DILocation(line: 439, column: 40, scope: !4665)
!4668 = !DILocation(line: 439, column: 38, scope: !4665)
!4669 = !DILocation(line: 439, column: 17, scope: !4665)
!4670 = !DILocation(line: 439, column: 3, scope: !4665)
!4671 = !DILocation(line: 440, column: 28, scope: !4666)
!4672 = !DILocation(line: 440, column: 35, scope: !4666)
!4673 = !DILocation(line: 440, column: 4, scope: !4666)
!4674 = !DILocation(line: 439, column: 46, scope: !4675)
!4675 = !DILexicalBlockFile(scope: !4666, file: !1, discriminator: 2)
!4676 = !DILocation(line: 439, column: 3, scope: !4675)
!4677 = !DILocation(line: 441, column: 7, scope: !4651)
!4678 = !DILocation(line: 441, column: 5, scope: !4651)
!4679 = !DILocation(line: 442, column: 2, scope: !4651)
!4680 = !DILocation(line: 443, column: 18, scope: !399)
!4681 = !DILocation(line: 443, column: 25, scope: !399)
!4682 = !DILocation(line: 443, column: 30, scope: !399)
!4683 = !DILocation(line: 443, column: 2, scope: !399)
!4684 = !DILocation(line: 444, column: 2, scope: !399)
!4685 = !DILocation(line: 445, column: 1, scope: !399)
!4686 = !DILocalVariable(name: "mtree", arg: 1, scope: !406, file: !1, line: 1522, type: !191)
!4687 = !DILocation(line: 1522, column: 33, scope: !406)
!4688 = !DILocalVariable(name: "buff", arg: 2, scope: !406, file: !1, line: 1522, type: !43)
!4689 = !DILocation(line: 1522, column: 52, scope: !406)
!4690 = !DILocalVariable(name: "n", arg: 3, scope: !406, file: !1, line: 1522, type: !45)
!4691 = !DILocation(line: 1522, column: 65, scope: !406)
!4692 = !DILocation(line: 1524, column: 6, scope: !4693)
!4693 = distinct !DILexicalBlock(scope: !406, file: !1, line: 1524, column: 6)
!4694 = !DILocation(line: 1524, column: 13, scope: !4693)
!4695 = !DILocation(line: 1524, column: 25, scope: !4693)
!4696 = !DILocation(line: 1524, column: 6, scope: !406)
!4697 = !DILocalVariable(name: "p", scope: !4698, file: !1, line: 1528, type: !114)
!4698 = distinct !DILexicalBlock(scope: !4693, file: !1, line: 1524, column: 36)
!4699 = !DILocation(line: 1528, column: 24, scope: !4698)
!4700 = !DILocalVariable(name: "nn", scope: !4698, file: !1, line: 1529, type: !45)
!4701 = !DILocation(line: 1529, column: 10, scope: !4698)
!4702 = !DILocation(line: 1531, column: 13, scope: !4703)
!4703 = distinct !DILexicalBlock(scope: !4698, file: !1, line: 1531, column: 3)
!4704 = !DILocation(line: 1531, column: 11, scope: !4703)
!4705 = !DILocation(line: 1531, column: 20, scope: !4703)
!4706 = !DILocation(line: 1531, column: 18, scope: !4703)
!4707 = !DILocation(line: 1531, column: 8, scope: !4703)
!4708 = !DILocation(line: 1531, column: 28, scope: !4709)
!4709 = !DILexicalBlockFile(scope: !4710, file: !1, discriminator: 1)
!4710 = distinct !DILexicalBlock(scope: !4703, file: !1, line: 1531, column: 3)
!4711 = !DILocation(line: 1531, column: 3, scope: !4709)
!4712 = !DILocation(line: 1532, column: 4, scope: !4710)
!4713 = !DILocation(line: 1531, column: 32, scope: !4714)
!4714 = !DILexicalBlockFile(scope: !4710, file: !1, discriminator: 2)
!4715 = !DILocation(line: 1531, column: 3, scope: !4714)
!4716 = !DILocation(line: 1533, column: 21, scope: !4698)
!4717 = !DILocation(line: 1533, column: 3, scope: !4698)
!4718 = !DILocation(line: 1533, column: 10, scope: !4698)
!4719 = !DILocation(line: 1533, column: 18, scope: !4698)
!4720 = !DILocation(line: 1534, column: 2, scope: !4698)
!4721 = !DILocation(line: 1559, column: 1, scope: !406)
!4722 = !DILocalVariable(name: "mtree", arg: 1, scope: !410, file: !1, line: 1562, type: !191)
!4723 = !DILocation(line: 1562, column: 32, scope: !410)
!4724 = !DILocalVariable(name: "reg", arg: 2, scope: !410, file: !1, line: 1562, type: !247)
!4725 = !DILocation(line: 1562, column: 56, scope: !410)
!4726 = !DILocation(line: 1565, column: 6, scope: !4727)
!4727 = distinct !DILexicalBlock(scope: !410, file: !1, line: 1565, column: 6)
!4728 = !DILocation(line: 1565, column: 13, scope: !4727)
!4729 = !DILocation(line: 1565, column: 25, scope: !4727)
!4730 = !DILocation(line: 1565, column: 6, scope: !410)
!4731 = !DILocalVariable(name: "len", scope: !4732, file: !1, line: 1566, type: !290)
!4732 = distinct !DILexicalBlock(scope: !4727, file: !1, line: 1565, column: 36)
!4733 = !DILocation(line: 1566, column: 12, scope: !4732)
!4734 = !DILocation(line: 1568, column: 14, scope: !4735)
!4735 = distinct !DILexicalBlock(scope: !4732, file: !1, line: 1568, column: 3)
!4736 = !DILocation(line: 1568, column: 21, scope: !4735)
!4737 = !DILocation(line: 1568, column: 12, scope: !4735)
!4738 = !DILocation(line: 1568, column: 8, scope: !4735)
!4739 = !DILocation(line: 1568, column: 30, scope: !4740)
!4740 = !DILexicalBlockFile(scope: !4741, file: !1, discriminator: 1)
!4741 = distinct !DILexicalBlock(scope: !4735, file: !1, line: 1568, column: 3)
!4742 = !DILocation(line: 1568, column: 34, scope: !4740)
!4743 = !DILocation(line: 1568, column: 3, scope: !4740)
!4744 = !DILocation(line: 1569, column: 4, scope: !4741)
!4745 = !DILocation(line: 1568, column: 44, scope: !4746)
!4746 = !DILexicalBlockFile(scope: !4741, file: !1, discriminator: 2)
!4747 = !DILocation(line: 1568, column: 3, scope: !4746)
!4748 = !DILocation(line: 1570, column: 15, scope: !4732)
!4749 = !DILocation(line: 1570, column: 22, scope: !4732)
!4750 = !DILocation(line: 1570, column: 14, scope: !4732)
!4751 = !DILocation(line: 1570, column: 3, scope: !4732)
!4752 = !DILocation(line: 1570, column: 8, scope: !4732)
!4753 = !DILocation(line: 1570, column: 12, scope: !4732)
!4754 = !DILocation(line: 1571, column: 2, scope: !4732)
!4755 = !DILocation(line: 1597, column: 21, scope: !410)
!4756 = !DILocation(line: 1597, column: 28, scope: !410)
!4757 = !DILocation(line: 1597, column: 2, scope: !410)
!4758 = !DILocation(line: 1597, column: 7, scope: !410)
!4759 = !DILocation(line: 1597, column: 19, scope: !410)
!4760 = !DILocation(line: 1598, column: 1, scope: !410)
