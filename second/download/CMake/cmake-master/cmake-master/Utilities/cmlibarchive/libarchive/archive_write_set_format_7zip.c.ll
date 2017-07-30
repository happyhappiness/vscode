; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_7zip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_rb_tree_ops = type { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, i8*)* }
%struct.archive_rb_node = type { [2 x %struct.archive_rb_node*], i64 }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_internal_s = type opaque
%struct.IPpmd7 = type { void (%struct.CPpmd7*)*, i32 (%struct.CPpmd7*, i32, %struct.ISzAlloc*)*, void (%struct.CPpmd7*, %struct.ISzAlloc*)*, void (%struct.CPpmd7*, i32)*, void (%struct.CPpmd7z_RangeDec*)*, void (%struct.CPpmd7z_RangeDec*)*, i32 (%struct.CPpmd7z_RangeDec*)*, i32 (%struct.CPpmd7z_RangeDec*)*, i32 (%struct.CPpmd7*, %struct.IPpmd7_RangeDec*)*, void (%struct.CPpmd7z_RangeEnc*)*, void (%struct.CPpmd7z_RangeEnc*)*, void (%struct.CPpmd7*, %struct.CPpmd7z_RangeEnc*, i32)* }
%struct.CPpmd7 = type { %struct.CPpmd7_Context_*, %struct.CPpmd7_Context_*, %struct.CPpmd_State*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8*, i8*, i8*, i8*, i32, [38 x i8], [128 x i8], [38 x i32], [256 x i8], [256 x i8], [256 x i8], %struct.CPpmd_See, [25 x [16 x %struct.CPpmd_See]], [128 x [64 x i16]] }
%struct.CPpmd7_Context_ = type { i16, i16, i32, i32 }
%struct.CPpmd_State = type { i8, i8, i16, i16 }
%struct.CPpmd_See = type { i16, i8, i8 }
%struct.ISzAlloc = type { i8* (i8*, i64)*, void (i8*, i8*)* }
%struct.CPpmd7z_RangeDec = type { %struct.IPpmd7_RangeDec, i32, i32, i32, i32, %struct.IByteIn* }
%struct.IPpmd7_RangeDec = type { i32 (i8*, i32)*, void (i8*, i32, i32)*, i32 (i8*, i32)* }
%struct.IByteIn = type { %struct.archive_read*, i8 (i8*)* }
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon.1 }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon.1 = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }
%struct.CPpmd7z_RangeEnc = type { i64, i32, i8, i64, %struct.IByteOut* }
%struct.IByteOut = type { %struct.archive_write*, void (i8*, i8)* }
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct._7zip = type { i32, i64, %struct.file*, i64, i64, i64, i64, i64, [3 x i64], i64, i64, i64, i32, i32, i32, i32, i32, i32, %struct.la_zstream, %struct.coder, %struct.archive_string_conv*, [61440 x i8], i64, %struct.anon.0, %struct.anon.0, %struct.archive_rb_tree }
%struct.file = type { %struct.archive_rb_node, %struct.file*, i32, i8*, i64, i32, [3 x %struct.anon], i32, i32, i8 }
%struct.anon = type { i64, i64 }
%struct.la_zstream = type { i8*, i64, i64, i8*, i64, i64, i32, i8*, i32, i8*, i32 (%struct.archive*, %struct.la_zstream*, i32)*, i32 (%struct.archive*, %struct.la_zstream*)* }
%struct.coder = type { i32, i64, i8* }
%struct.anon.0 = type { %struct.file*, %struct.file** }
%struct.archive_rb_tree = type { %struct.archive_rb_node*, %struct.archive_rb_tree_ops* }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }
%struct.bz_stream = type { i8*, i32, i32, i32, i8*, i32, i32, i32, i8*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8* }
%struct.ppmd_stream = type { i32, %struct.CPpmd7, %struct.CPpmd7z_RangeEnc, %struct.IByteOut, i8*, i8*, i8*, i64 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

@archive_write_set_format_7zip.rb_ops = internal constant %struct.archive_rb_tree_ops { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)* @file_cmp_node, i32 (%struct.archive_rb_node*, i8*)* @file_cmp_key }, align 8
@.str = private unnamed_addr constant [30 x i8] c"archive_write_set_format_7zip\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"Can't allocate 7-Zip data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"7zip\00", align 1
@.str.3 = private unnamed_addr constant [12 x i8] c"compression\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"copy\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"COPY\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"store\00", align 1
@.str.7 = private unnamed_addr constant [6 x i8] c"STORE\00", align 1
@.str.8 = private unnamed_addr constant [8 x i8] c"deflate\00", align 1
@.str.9 = private unnamed_addr constant [8 x i8] c"DEFLATE\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.11 = private unnamed_addr constant [6 x i8] c"BZIP2\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"lzma1\00", align 1
@.str.13 = private unnamed_addr constant [6 x i8] c"LZMA1\00", align 1
@.str.14 = private unnamed_addr constant [6 x i8] c"lzma2\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"LZMA2\00", align 1
@.str.16 = private unnamed_addr constant [5 x i8] c"ppmd\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"PPMD\00", align 1
@.str.18 = private unnamed_addr constant [5 x i8] c"PPMd\00", align 1
@.str.19 = private unnamed_addr constant [31 x i8] c"Unknown compression name: `%s'\00", align 1
@.str.20 = private unnamed_addr constant [48 x i8] c"`%s' compression not supported on this platform\00", align 1
@.str.21 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.22 = private unnamed_addr constant [19 x i8] c"Illegal value `%s'\00", align 1
@.str.23 = private unnamed_addr constant [9 x i8] c"UTF-16LE\00", align 1
@.str.24 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.25 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for UTF-16LE\00", align 1
@.str.26 = private unnamed_addr constant [86 x i8] c"A filename cannot be converted to UTF-16LE;You should disable making Joliet extension\00", align 1
@.str.27 = private unnamed_addr constant [31 x i8] c"Can't allocate memory for Name\00", align 1
@.str.28 = private unnamed_addr constant [38 x i8] c"Can't allocate memory for gzip stream\00", align 1
@.str.29 = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1
@.str.30 = private unnamed_addr constant [48 x i8] c"Internal error initializing compression library\00", align 1
@.str.31 = private unnamed_addr constant [59 x i8] c"GZip compression failed: deflate() call returned status %d\00", align 1
@.str.32 = private unnamed_addr constant [30 x i8] c"Failed to clean up compressor\00", align 1
@.str.33 = private unnamed_addr constant [39 x i8] c"Can't allocate memory for bzip2 stream\00", align 1
@.str.34 = private unnamed_addr constant [67 x i8] c"Bzip2 compression failed: BZ2_bzCompress() call returned status %d\00", align 1
@compression_init_encoder_lzma.lzma_init_data = internal constant %struct.lzma_stream zeroinitializer, align 8
@.str.35 = private unnamed_addr constant [38 x i8] c"Can't allocate memory for lzma stream\00", align 1
@.str.36 = private unnamed_addr constant [28 x i8] c"lzma_properties_size failed\00", align 1
@.str.37 = private unnamed_addr constant [23 x i8] c"Cannot allocate memory\00", align 1
@.str.38 = private unnamed_addr constant [30 x i8] c"lzma_properties_encode failed\00", align 1
@.str.39 = private unnamed_addr constant [72 x i8] c"Internal error initializing compression library: Cannot allocate memory\00", align 1
@.str.40 = private unnamed_addr constant [71 x i8] c"Internal error initializing compression library: It's a bug in liblzma\00", align 1
@.str.41 = private unnamed_addr constant [55 x i8] c"lzma compression error: %ju MiB would have been needed\00", align 1
@.str.42 = private unnamed_addr constant [61 x i8] c"lzma compression failed: lzma_code() call returned status %d\00", align 1
@.str.43 = private unnamed_addr constant [31 x i8] c"Can't allocate memory for PPMd\00", align 1
@.str.44 = private unnamed_addr constant [34 x i8] c"Coludn't allocate memory for PPMd\00", align 1
@__archive_ppmd7_functions = external constant %struct.IPpmd7, align 8
@g_szalloc = internal global %struct.ISzAlloc { i8* (i8*, i64)* @ppmd_alloc, void (i8*, i8*)* @ppmd_free }, align 8
@.str.45 = private unnamed_addr constant [31 x i8] c"Couldn't create temporary file\00", align 1
@.str.46 = private unnamed_addr constant [23 x i8] c"fwrite function failed\00", align 1
@.str.47 = private unnamed_addr constant [7 x i8] c"7z\BC\AF'\1C\00", align 1
@.str.48 = private unnamed_addr constant [13 x i8] c"lseek failed\00", align 1
@.str.49 = private unnamed_addr constant [31 x i8] c"Can't read temporary file(%jd)\00", align 1
@.str.50 = private unnamed_addr constant [24 x i8] c"Truncated 7-Zip archive\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_7zip(%struct.archive* %_a) #0 !dbg !580 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !692, metadata !693), !dbg !694
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !695, metadata !693), !dbg !696
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !697
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !698
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !696
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !699, metadata !693), !dbg !700
  br label %do.body, !dbg !701

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !702, metadata !693), !dbg !704
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !705
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !705
  store i32 %call, i32* %magic_test, align 4, !dbg !705
  %3 = load i32, i32* %magic_test, align 4, !dbg !705
  %cmp = icmp eq i32 %3, -30, !dbg !705
  br i1 %cmp, label %if.then, label %if.end, !dbg !705

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !707
  br label %return, !dbg !707

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !710

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !712
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !714
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !714
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !715
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !716

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !717
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !718
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !718
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !719
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !720
  br label %if.end5, !dbg !720

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 61760) #8, !dbg !721
  %9 = bitcast i8* %call6 to %struct._7zip*, !dbg !721
  store %struct._7zip* %9, %struct._7zip** %zip, align 8, !dbg !722
  %10 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !723
  %cmp7 = icmp eq %struct._7zip* %10, null, !dbg !725
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !726

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !727
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !729
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !730
  store i32 -30, i32* %retval, align 4, !dbg !731
  br label %return, !dbg !731

if.end9:                                          ; preds = %if.end5
  %12 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !732
  %temp_fd = getelementptr inbounds %struct._7zip, %struct._7zip* %12, i32 0, i32 0, !dbg !733
  store i32 -1, i32* %temp_fd, align 8, !dbg !734
  %13 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !735
  %rbtree = getelementptr inbounds %struct._7zip, %struct._7zip* %13, i32 0, i32 25, !dbg !736
  call void @__archive_rb_tree_init(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_tree_ops* @archive_write_set_format_7zip.rb_ops), !dbg !737
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !738
  call void @file_init_register(%struct._7zip* %14), !dbg !739
  %15 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !740
  call void @file_init_register_empty(%struct._7zip* %15), !dbg !741
  %16 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !742
  %opt_compression = getelementptr inbounds %struct._7zip, %struct._7zip* %16, i32 0, i32 16, !dbg !743
  store i32 196865, i32* %opt_compression, align 8, !dbg !744
  %17 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !745
  %opt_compression_level = getelementptr inbounds %struct._7zip, %struct._7zip* %17, i32 0, i32 17, !dbg !746
  store i32 6, i32* %opt_compression_level, align 4, !dbg !747
  %18 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !748
  %19 = bitcast %struct._7zip* %18 to i8*, !dbg !748
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !749
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 14, !dbg !750
  store i8* %19, i8** %format_data, align 8, !dbg !751
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !752
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 15, !dbg !753
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !754
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !755
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 17, !dbg !756
  store i32 (%struct.archive_write*, i8*, i8*)* @_7z_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !757
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !758
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 19, !dbg !759
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @_7z_write_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !760
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !761
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 20, !dbg !762
  store i64 (%struct.archive_write*, i8*, i64)* @_7z_write_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !763
  %25 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !764
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 18, !dbg !765
  store i32 (%struct.archive_write*)* @_7z_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !766
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !767
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 21, !dbg !768
  store i32 (%struct.archive_write*)* @_7z_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !769
  %27 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !770
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 22, !dbg !771
  store i32 (%struct.archive_write*)* @_7z_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !772
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !773
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 0, !dbg !774
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !775
  store i32 917504, i32* %archive_format, align 8, !dbg !776
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !777
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 0, !dbg !778
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !779
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !780
  store i32 0, i32* %retval, align 4, !dbg !781
  br label %return, !dbg !781

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !782
  ret i32 %30, !dbg !782
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @file_cmp_node(%struct.archive_rb_node* %n1, %struct.archive_rb_node* %n2) #0 !dbg !674 {
entry:
  %retval = alloca i32, align 4
  %n1.addr = alloca %struct.archive_rb_node*, align 8
  %n2.addr = alloca %struct.archive_rb_node*, align 8
  %f1 = alloca %struct.file*, align 8
  %f2 = alloca %struct.file*, align 8
  store %struct.archive_rb_node* %n1, %struct.archive_rb_node** %n1.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n1.addr, metadata !783, metadata !693), !dbg !784
  store %struct.archive_rb_node* %n2, %struct.archive_rb_node** %n2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n2.addr, metadata !785, metadata !693), !dbg !786
  call void @llvm.dbg.declare(metadata %struct.file** %f1, metadata !787, metadata !693), !dbg !788
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n1.addr, align 8, !dbg !789
  %1 = bitcast %struct.archive_rb_node* %0 to %struct.file*, !dbg !790
  store %struct.file* %1, %struct.file** %f1, align 8, !dbg !788
  call void @llvm.dbg.declare(metadata %struct.file** %f2, metadata !791, metadata !693), !dbg !792
  %2 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n2.addr, align 8, !dbg !793
  %3 = bitcast %struct.archive_rb_node* %2 to %struct.file*, !dbg !794
  store %struct.file* %3, %struct.file** %f2, align 8, !dbg !792
  %4 = load %struct.file*, %struct.file** %f1, align 8, !dbg !795
  %name_len = getelementptr inbounds %struct.file, %struct.file* %4, i32 0, i32 2, !dbg !797
  %5 = load i32, i32* %name_len, align 8, !dbg !797
  %6 = load %struct.file*, %struct.file** %f2, align 8, !dbg !798
  %name_len1 = getelementptr inbounds %struct.file, %struct.file* %6, i32 0, i32 2, !dbg !799
  %7 = load i32, i32* %name_len1, align 8, !dbg !799
  %cmp = icmp eq i32 %5, %7, !dbg !800
  br i1 %cmp, label %if.then, label %if.end, !dbg !801

if.then:                                          ; preds = %entry
  %8 = load %struct.file*, %struct.file** %f1, align 8, !dbg !802
  %utf16name = getelementptr inbounds %struct.file, %struct.file* %8, i32 0, i32 3, !dbg !803
  %9 = load i8*, i8** %utf16name, align 8, !dbg !803
  %10 = load %struct.file*, %struct.file** %f2, align 8, !dbg !804
  %utf16name2 = getelementptr inbounds %struct.file, %struct.file* %10, i32 0, i32 3, !dbg !805
  %11 = load i8*, i8** %utf16name2, align 8, !dbg !805
  %12 = load %struct.file*, %struct.file** %f1, align 8, !dbg !806
  %name_len3 = getelementptr inbounds %struct.file, %struct.file* %12, i32 0, i32 2, !dbg !807
  %13 = load i32, i32* %name_len3, align 8, !dbg !807
  %conv = zext i32 %13 to i64, !dbg !806
  %call = call i32 @memcmp(i8* %9, i8* %11, i64 %conv) #9, !dbg !808
  store i32 %call, i32* %retval, align 4, !dbg !809
  br label %return, !dbg !809

if.end:                                           ; preds = %entry
  %14 = load %struct.file*, %struct.file** %f1, align 8, !dbg !810
  %name_len4 = getelementptr inbounds %struct.file, %struct.file* %14, i32 0, i32 2, !dbg !811
  %15 = load i32, i32* %name_len4, align 8, !dbg !811
  %16 = load %struct.file*, %struct.file** %f2, align 8, !dbg !812
  %name_len5 = getelementptr inbounds %struct.file, %struct.file* %16, i32 0, i32 2, !dbg !813
  %17 = load i32, i32* %name_len5, align 8, !dbg !813
  %cmp6 = icmp ugt i32 %15, %17, !dbg !814
  %cond = select i1 %cmp6, i32 1, i32 -1, !dbg !815
  store i32 %cond, i32* %retval, align 4, !dbg !816
  br label %return, !dbg !816

return:                                           ; preds = %if.end, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !817
  ret i32 %18, !dbg !817
}

; Function Attrs: nounwind uwtable
define internal i32 @file_cmp_key(%struct.archive_rb_node* %n, i8* %key) #0 !dbg !675 {
entry:
  %n.addr = alloca %struct.archive_rb_node*, align 8
  %key.addr = alloca i8*, align 8
  %f = alloca %struct.file*, align 8
  store %struct.archive_rb_node* %n, %struct.archive_rb_node** %n.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n.addr, metadata !818, metadata !693), !dbg !819
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !820, metadata !693), !dbg !821
  call void @llvm.dbg.declare(metadata %struct.file** %f, metadata !822, metadata !693), !dbg !823
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n.addr, align 8, !dbg !824
  %1 = bitcast %struct.archive_rb_node* %0 to %struct.file*, !dbg !825
  store %struct.file* %1, %struct.file** %f, align 8, !dbg !823
  %2 = load %struct.file*, %struct.file** %f, align 8, !dbg !826
  %name_len = getelementptr inbounds %struct.file, %struct.file* %2, i32 0, i32 2, !dbg !827
  %3 = load i32, i32* %name_len, align 8, !dbg !827
  %4 = load i8*, i8** %key.addr, align 8, !dbg !828
  %5 = load i8, i8* %4, align 1, !dbg !829
  %conv = sext i8 %5 to i32, !dbg !829
  %sub = sub i32 %3, %conv, !dbg !830
  ret i32 %sub, !dbg !831
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare void @__archive_rb_tree_init(%struct.archive_rb_tree*, %struct.archive_rb_tree_ops*) #2

; Function Attrs: nounwind uwtable
define internal void @file_init_register(%struct._7zip* %zip) #0 !dbg !676 {
entry:
  %zip.addr = alloca %struct._7zip*, align 8
  store %struct._7zip* %zip, %struct._7zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip.addr, metadata !832, metadata !693), !dbg !833
  %0 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !834
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %0, i32 0, i32 23, !dbg !835
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !836
  store %struct.file* null, %struct.file** %first, align 8, !dbg !837
  %1 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !838
  %file_list1 = getelementptr inbounds %struct._7zip, %struct._7zip* %1, i32 0, i32 23, !dbg !839
  %first2 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list1, i32 0, i32 0, !dbg !840
  %2 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !841
  %file_list3 = getelementptr inbounds %struct._7zip, %struct._7zip* %2, i32 0, i32 23, !dbg !842
  %last = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list3, i32 0, i32 1, !dbg !843
  store %struct.file** %first2, %struct.file*** %last, align 8, !dbg !844
  ret void, !dbg !845
}

; Function Attrs: nounwind uwtable
define internal void @file_init_register_empty(%struct._7zip* %zip) #0 !dbg !677 {
entry:
  %zip.addr = alloca %struct._7zip*, align 8
  store %struct._7zip* %zip, %struct._7zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip.addr, metadata !846, metadata !693), !dbg !847
  %0 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !848
  %empty_list = getelementptr inbounds %struct._7zip, %struct._7zip* %0, i32 0, i32 24, !dbg !849
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list, i32 0, i32 0, !dbg !850
  store %struct.file* null, %struct.file** %first, align 8, !dbg !851
  %1 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !852
  %empty_list1 = getelementptr inbounds %struct._7zip, %struct._7zip* %1, i32 0, i32 24, !dbg !853
  %first2 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list1, i32 0, i32 0, !dbg !854
  %2 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !855
  %empty_list3 = getelementptr inbounds %struct._7zip, %struct._7zip* %2, i32 0, i32 24, !dbg !856
  %last = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list3, i32 0, i32 1, !dbg !857
  store %struct.file** %first2, %struct.file*** %last, align 8, !dbg !858
  ret void, !dbg !859
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_options(%struct.archive_write* %a, i8* %key, i8* %value) #0 !dbg !582 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %zip = alloca %struct._7zip*, align 8
  %name = alloca i8*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !860, metadata !693), !dbg !861
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !862, metadata !693), !dbg !863
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !864, metadata !693), !dbg !865
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !866, metadata !693), !dbg !867
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !868
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !869
  %1 = load i8*, i8** %format_data, align 8, !dbg !869
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !870
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !871
  %3 = load i8*, i8** %key.addr, align 8, !dbg !872
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i32 0, i32 0)) #9, !dbg !874
  %cmp = icmp eq i32 %call, 0, !dbg !875
  br i1 %cmp, label %if.then, label %if.end66, !dbg !876

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %name, metadata !877, metadata !693), !dbg !879
  store i8* null, i8** %name, align 8, !dbg !879
  %4 = load i8*, i8** %value.addr, align 8, !dbg !880
  %cmp1 = icmp eq i8* %4, null, !dbg !882
  br i1 %cmp1, label %if.then13, label %lor.lhs.false, !dbg !883

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !884
  %call2 = call i32 @strcmp(i8* %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)) #9, !dbg !886
  %cmp3 = icmp eq i32 %call2, 0, !dbg !887
  br i1 %cmp3, label %if.then13, label %lor.lhs.false4, !dbg !888

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %6 = load i8*, i8** %value.addr, align 8, !dbg !889
  %call5 = call i32 @strcmp(i8* %6, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0)) #9, !dbg !890
  %cmp6 = icmp eq i32 %call5, 0, !dbg !891
  br i1 %cmp6, label %if.then13, label %lor.lhs.false7, !dbg !892

lor.lhs.false7:                                   ; preds = %lor.lhs.false4
  %7 = load i8*, i8** %value.addr, align 8, !dbg !893
  %call8 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0)) #9, !dbg !894
  %cmp9 = icmp eq i32 %call8, 0, !dbg !895
  br i1 %cmp9, label %if.then13, label %lor.lhs.false10, !dbg !896

lor.lhs.false10:                                  ; preds = %lor.lhs.false7
  %8 = load i8*, i8** %value.addr, align 8, !dbg !897
  %call11 = call i32 @strcmp(i8* %8, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.7, i32 0, i32 0)) #9, !dbg !898
  %cmp12 = icmp eq i32 %call11, 0, !dbg !899
  br i1 %cmp12, label %if.then13, label %if.else, !dbg !900

if.then13:                                        ; preds = %lor.lhs.false10, %lor.lhs.false7, %lor.lhs.false4, %lor.lhs.false, %if.then
  %9 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !902
  %opt_compression = getelementptr inbounds %struct._7zip, %struct._7zip* %9, i32 0, i32 16, !dbg !903
  store i32 0, i32* %opt_compression, align 8, !dbg !904
  br label %if.end61, !dbg !902

if.else:                                          ; preds = %lor.lhs.false10
  %10 = load i8*, i8** %value.addr, align 8, !dbg !905
  %call14 = call i32 @strcmp(i8* %10, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !907
  %cmp15 = icmp eq i32 %call14, 0, !dbg !908
  br i1 %cmp15, label %if.then19, label %lor.lhs.false16, !dbg !909

lor.lhs.false16:                                  ; preds = %if.else
  %11 = load i8*, i8** %value.addr, align 8, !dbg !910
  %call17 = call i32 @strcmp(i8* %11, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.9, i32 0, i32 0)) #9, !dbg !911
  %cmp18 = icmp eq i32 %call17, 0, !dbg !912
  br i1 %cmp18, label %if.then19, label %if.else21, !dbg !913

if.then19:                                        ; preds = %lor.lhs.false16, %if.else
  %12 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !914
  %opt_compression20 = getelementptr inbounds %struct._7zip, %struct._7zip* %12, i32 0, i32 16, !dbg !915
  store i32 262408, i32* %opt_compression20, align 8, !dbg !916
  br label %if.end60, !dbg !914

if.else21:                                        ; preds = %lor.lhs.false16
  %13 = load i8*, i8** %value.addr, align 8, !dbg !917
  %call22 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)) #9, !dbg !919
  %cmp23 = icmp eq i32 %call22, 0, !dbg !920
  br i1 %cmp23, label %if.then27, label %lor.lhs.false24, !dbg !921

lor.lhs.false24:                                  ; preds = %if.else21
  %14 = load i8*, i8** %value.addr, align 8, !dbg !922
  %call25 = call i32 @strcmp(i8* %14, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.11, i32 0, i32 0)) #9, !dbg !923
  %cmp26 = icmp eq i32 %call25, 0, !dbg !924
  br i1 %cmp26, label %if.then27, label %if.else29, !dbg !925

if.then27:                                        ; preds = %lor.lhs.false24, %if.else21
  %15 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !927
  %opt_compression28 = getelementptr inbounds %struct._7zip, %struct._7zip* %15, i32 0, i32 16, !dbg !928
  store i32 262658, i32* %opt_compression28, align 8, !dbg !929
  br label %if.end59, !dbg !927

if.else29:                                        ; preds = %lor.lhs.false24
  %16 = load i8*, i8** %value.addr, align 8, !dbg !930
  %call30 = call i32 @strcmp(i8* %16, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0)) #9, !dbg !932
  %cmp31 = icmp eq i32 %call30, 0, !dbg !933
  br i1 %cmp31, label %if.then35, label %lor.lhs.false32, !dbg !934

lor.lhs.false32:                                  ; preds = %if.else29
  %17 = load i8*, i8** %value.addr, align 8, !dbg !935
  %call33 = call i32 @strcmp(i8* %17, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.13, i32 0, i32 0)) #9, !dbg !936
  %cmp34 = icmp eq i32 %call33, 0, !dbg !937
  br i1 %cmp34, label %if.then35, label %if.else37, !dbg !938

if.then35:                                        ; preds = %lor.lhs.false32, %if.else29
  %18 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !940
  %opt_compression36 = getelementptr inbounds %struct._7zip, %struct._7zip* %18, i32 0, i32 16, !dbg !941
  store i32 196865, i32* %opt_compression36, align 8, !dbg !942
  br label %if.end58, !dbg !940

if.else37:                                        ; preds = %lor.lhs.false32
  %19 = load i8*, i8** %value.addr, align 8, !dbg !943
  %call38 = call i32 @strcmp(i8* %19, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !945
  %cmp39 = icmp eq i32 %call38, 0, !dbg !946
  br i1 %cmp39, label %if.then43, label %lor.lhs.false40, !dbg !947

lor.lhs.false40:                                  ; preds = %if.else37
  %20 = load i8*, i8** %value.addr, align 8, !dbg !948
  %call41 = call i32 @strcmp(i8* %20, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i32 0, i32 0)) #9, !dbg !949
  %cmp42 = icmp eq i32 %call41, 0, !dbg !950
  br i1 %cmp42, label %if.then43, label %if.else45, !dbg !951

if.then43:                                        ; preds = %lor.lhs.false40, %if.else37
  %21 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !953
  %opt_compression44 = getelementptr inbounds %struct._7zip, %struct._7zip* %21, i32 0, i32 16, !dbg !954
  store i32 33, i32* %opt_compression44, align 8, !dbg !955
  br label %if.end57, !dbg !953

if.else45:                                        ; preds = %lor.lhs.false40
  %22 = load i8*, i8** %value.addr, align 8, !dbg !956
  %call46 = call i32 @strcmp(i8* %22, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.16, i32 0, i32 0)) #9, !dbg !958
  %cmp47 = icmp eq i32 %call46, 0, !dbg !959
  br i1 %cmp47, label %if.then54, label %lor.lhs.false48, !dbg !960

lor.lhs.false48:                                  ; preds = %if.else45
  %23 = load i8*, i8** %value.addr, align 8, !dbg !961
  %call49 = call i32 @strcmp(i8* %23, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)) #9, !dbg !962
  %cmp50 = icmp eq i32 %call49, 0, !dbg !963
  br i1 %cmp50, label %if.then54, label %lor.lhs.false51, !dbg !964

lor.lhs.false51:                                  ; preds = %lor.lhs.false48
  %24 = load i8*, i8** %value.addr, align 8, !dbg !965
  %call52 = call i32 @strcmp(i8* %24, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.18, i32 0, i32 0)) #9, !dbg !966
  %cmp53 = icmp eq i32 %call52, 0, !dbg !967
  br i1 %cmp53, label %if.then54, label %if.else56, !dbg !968

if.then54:                                        ; preds = %lor.lhs.false51, %lor.lhs.false48, %if.else45
  %25 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !970
  %opt_compression55 = getelementptr inbounds %struct._7zip, %struct._7zip* %25, i32 0, i32 16, !dbg !971
  store i32 197633, i32* %opt_compression55, align 8, !dbg !972
  br label %if.end, !dbg !970

if.else56:                                        ; preds = %lor.lhs.false51
  %26 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !973
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 0, !dbg !975
  %27 = load i8*, i8** %value.addr, align 8, !dbg !976
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.19, i32 0, i32 0), i8* %27), !dbg !977
  store i32 -25, i32* %retval, align 4, !dbg !978
  br label %return, !dbg !978

if.end:                                           ; preds = %if.then54
  br label %if.end57

if.end57:                                         ; preds = %if.end, %if.then43
  br label %if.end58

if.end58:                                         ; preds = %if.end57, %if.then35
  br label %if.end59

if.end59:                                         ; preds = %if.end58, %if.then27
  br label %if.end60

if.end60:                                         ; preds = %if.end59, %if.then19
  br label %if.end61

if.end61:                                         ; preds = %if.end60, %if.then13
  %28 = load i8*, i8** %name, align 8, !dbg !979
  %cmp62 = icmp ne i8* %28, null, !dbg !981
  br i1 %cmp62, label %if.then63, label %if.end65, !dbg !982

if.then63:                                        ; preds = %if.end61
  %29 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !983
  %archive64 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 0, !dbg !985
  %30 = load i8*, i8** %name, align 8, !dbg !986
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive64, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.20, i32 0, i32 0), i8* %30), !dbg !987
  store i32 -25, i32* %retval, align 4, !dbg !988
  br label %return, !dbg !988

if.end65:                                         ; preds = %if.end61
  store i32 0, i32* %retval, align 4, !dbg !989
  br label %return, !dbg !989

if.end66:                                         ; preds = %entry
  %31 = load i8*, i8** %key.addr, align 8, !dbg !990
  %call67 = call i32 @strcmp(i8* %31, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.21, i32 0, i32 0)) #9, !dbg !992
  %cmp68 = icmp eq i32 %call67, 0, !dbg !993
  br i1 %cmp68, label %if.then69, label %if.end88, !dbg !994

if.then69:                                        ; preds = %if.end66
  %32 = load i8*, i8** %value.addr, align 8, !dbg !995
  %cmp70 = icmp eq i8* %32, null, !dbg !998
  br i1 %cmp70, label %if.then83, label %lor.lhs.false71, !dbg !999

lor.lhs.false71:                                  ; preds = %if.then69
  %33 = load i8*, i8** %value.addr, align 8, !dbg !1000
  %arrayidx = getelementptr inbounds i8, i8* %33, i64 0, !dbg !1000
  %34 = load i8, i8* %arrayidx, align 1, !dbg !1000
  %conv = sext i8 %34 to i32, !dbg !1000
  %cmp72 = icmp sge i32 %conv, 48, !dbg !1001
  br i1 %cmp72, label %land.lhs.true, label %if.then83, !dbg !1002

land.lhs.true:                                    ; preds = %lor.lhs.false71
  %35 = load i8*, i8** %value.addr, align 8, !dbg !1003
  %arrayidx74 = getelementptr inbounds i8, i8* %35, i64 0, !dbg !1003
  %36 = load i8, i8* %arrayidx74, align 1, !dbg !1003
  %conv75 = sext i8 %36 to i32, !dbg !1003
  %cmp76 = icmp sle i32 %conv75, 57, !dbg !1005
  br i1 %cmp76, label %lor.lhs.false78, label %if.then83, !dbg !1006

lor.lhs.false78:                                  ; preds = %land.lhs.true
  %37 = load i8*, i8** %value.addr, align 8, !dbg !1007
  %arrayidx79 = getelementptr inbounds i8, i8* %37, i64 1, !dbg !1007
  %38 = load i8, i8* %arrayidx79, align 1, !dbg !1007
  %conv80 = sext i8 %38 to i32, !dbg !1007
  %cmp81 = icmp ne i32 %conv80, 0, !dbg !1008
  br i1 %cmp81, label %if.then83, label %if.end85, !dbg !1009

if.then83:                                        ; preds = %lor.lhs.false78, %land.lhs.true, %lor.lhs.false71, %if.then69
  %39 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1011
  %archive84 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 0, !dbg !1013
  %40 = load i8*, i8** %value.addr, align 8, !dbg !1014
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive84, i32 -1, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.22, i32 0, i32 0), i8* %40), !dbg !1015
  store i32 -25, i32* %retval, align 4, !dbg !1016
  br label %return, !dbg !1016

if.end85:                                         ; preds = %lor.lhs.false78
  %41 = load i8*, i8** %value.addr, align 8, !dbg !1017
  %arrayidx86 = getelementptr inbounds i8, i8* %41, i64 0, !dbg !1017
  %42 = load i8, i8* %arrayidx86, align 1, !dbg !1017
  %conv87 = sext i8 %42 to i32, !dbg !1017
  %sub = sub nsw i32 %conv87, 48, !dbg !1018
  %43 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1019
  %opt_compression_level = getelementptr inbounds %struct._7zip, %struct._7zip* %43, i32 0, i32 17, !dbg !1020
  store i32 %sub, i32* %opt_compression_level, align 4, !dbg !1021
  store i32 0, i32* %retval, align 4, !dbg !1022
  br label %return, !dbg !1022

if.end88:                                         ; preds = %if.end66
  store i32 -20, i32* %retval, align 4, !dbg !1023
  br label %return, !dbg !1023

return:                                           ; preds = %if.end88, %if.end85, %if.then83, %if.end65, %if.then63, %if.else56
  %44 = load i32, i32* %retval, align 4, !dbg !1024
  ret i32 %44, !dbg !1024
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_write_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !583 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %zip = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %r = alloca i32, align 4
  %bytes = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1025, metadata !693), !dbg !1026
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1027, metadata !693), !dbg !1028
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1029, metadata !693), !dbg !1030
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !1031, metadata !693), !dbg !1032
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1033, metadata !693), !dbg !1034
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1035
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1036
  %1 = load i8*, i8** %format_data, align 8, !dbg !1036
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1037
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1038
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1039
  %cur_file = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 2, !dbg !1040
  store %struct.file* null, %struct.file** %cur_file, align 8, !dbg !1041
  %4 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1042
  %entry_bytes_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %4, i32 0, i32 11, !dbg !1043
  store i64 0, i64* %entry_bytes_remaining, align 8, !dbg !1044
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1045
  %sconv = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 20, !dbg !1047
  %6 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1047
  %cmp = icmp eq %struct.archive_string_conv* %6, null, !dbg !1048
  br i1 %cmp, label %if.then, label %if.end6, !dbg !1049

if.then:                                          ; preds = %entry
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1050
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !1052
  %call = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.23, i32 0, i32 0), i32 1), !dbg !1053
  %8 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1054
  %sconv2 = getelementptr inbounds %struct._7zip, %struct._7zip* %8, i32 0, i32 20, !dbg !1055
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv2, align 8, !dbg !1056
  %9 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1057
  %sconv3 = getelementptr inbounds %struct._7zip, %struct._7zip* %9, i32 0, i32 20, !dbg !1059
  %10 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv3, align 8, !dbg !1059
  %cmp4 = icmp eq %struct.archive_string_conv* %10, null, !dbg !1060
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !1061

if.then5:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !1062
  br label %return, !dbg !1062

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !1063

if.end6:                                          ; preds = %if.end, %entry
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1064
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1065
  %call7 = call i32 @file_new(%struct.archive_write* %11, %struct.archive_entry* %12, %struct.file** %file), !dbg !1066
  store i32 %call7, i32* %r, align 4, !dbg !1067
  %13 = load i32, i32* %r, align 4, !dbg !1068
  %cmp8 = icmp slt i32 %13, -20, !dbg !1070
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !1071

if.then9:                                         ; preds = %if.end6
  %14 = load %struct.file*, %struct.file** %file, align 8, !dbg !1072
  call void @file_free(%struct.file* %14), !dbg !1074
  %15 = load i32, i32* %r, align 4, !dbg !1075
  store i32 %15, i32* %retval, align 4, !dbg !1076
  br label %return, !dbg !1076

if.end10:                                         ; preds = %if.end6
  %16 = load %struct.file*, %struct.file** %file, align 8, !dbg !1077
  %size = getelementptr inbounds %struct.file, %struct.file* %16, i32 0, i32 4, !dbg !1079
  %17 = load i64, i64* %size, align 8, !dbg !1079
  %cmp11 = icmp eq i64 %17, 0, !dbg !1080
  br i1 %cmp11, label %land.lhs.true, label %if.end17, !dbg !1081

land.lhs.true:                                    ; preds = %if.end10
  %18 = load %struct.file*, %struct.file** %file, align 8, !dbg !1082
  %dir = getelementptr inbounds %struct.file, %struct.file* %18, i32 0, i32 9, !dbg !1084
  %bf.load = load i8, i8* %dir, align 8, !dbg !1084
  %bf.shl = shl i8 %bf.load, 7, !dbg !1084
  %bf.ashr = ashr i8 %bf.shl, 7, !dbg !1084
  %bf.cast = sext i8 %bf.ashr to i32, !dbg !1084
  %tobool = icmp ne i32 %bf.cast, 0, !dbg !1082
  br i1 %tobool, label %if.then12, label %if.end17, !dbg !1085

if.then12:                                        ; preds = %land.lhs.true
  %19 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1086
  %rbtree = getelementptr inbounds %struct._7zip, %struct._7zip* %19, i32 0, i32 25, !dbg !1089
  %20 = load %struct.file*, %struct.file** %file, align 8, !dbg !1090
  %21 = bitcast %struct.file* %20 to %struct.archive_rb_node*, !dbg !1091
  %call13 = call i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_node* %21), !dbg !1092
  %tobool14 = icmp ne i32 %call13, 0, !dbg !1092
  br i1 %tobool14, label %if.end16, label %if.then15, !dbg !1093

if.then15:                                        ; preds = %if.then12
  %22 = load %struct.file*, %struct.file** %file, align 8, !dbg !1094
  call void @file_free(%struct.file* %22), !dbg !1096
  store i32 0, i32* %retval, align 4, !dbg !1097
  br label %return, !dbg !1097

if.end16:                                         ; preds = %if.then12
  br label %if.end17, !dbg !1098

if.end17:                                         ; preds = %if.end16, %land.lhs.true, %if.end10
  %23 = load %struct.file*, %struct.file** %file, align 8, !dbg !1099
  %flg = getelementptr inbounds %struct.file, %struct.file* %23, i32 0, i32 5, !dbg !1101
  %24 = load i32, i32* %flg, align 8, !dbg !1101
  %and = and i32 %24, 1, !dbg !1102
  %tobool18 = icmp ne i32 %and, 0, !dbg !1102
  br i1 %tobool18, label %if.then19, label %if.end20, !dbg !1103

if.then19:                                        ; preds = %if.end17
  %25 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1104
  %total_number_time_defined = getelementptr inbounds %struct._7zip, %struct._7zip* %25, i32 0, i32 8, !dbg !1105
  %arrayidx = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined, i64 0, i64 0, !dbg !1104
  %26 = load i64, i64* %arrayidx, align 8, !dbg !1106
  %inc = add i64 %26, 1, !dbg !1106
  store i64 %inc, i64* %arrayidx, align 8, !dbg !1106
  br label %if.end20, !dbg !1104

if.end20:                                         ; preds = %if.then19, %if.end17
  %27 = load %struct.file*, %struct.file** %file, align 8, !dbg !1107
  %flg21 = getelementptr inbounds %struct.file, %struct.file* %27, i32 0, i32 5, !dbg !1109
  %28 = load i32, i32* %flg21, align 8, !dbg !1109
  %and22 = and i32 %28, 4, !dbg !1110
  %tobool23 = icmp ne i32 %and22, 0, !dbg !1110
  br i1 %tobool23, label %if.then24, label %if.end28, !dbg !1111

if.then24:                                        ; preds = %if.end20
  %29 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1112
  %total_number_time_defined25 = getelementptr inbounds %struct._7zip, %struct._7zip* %29, i32 0, i32 8, !dbg !1113
  %arrayidx26 = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined25, i64 0, i64 2, !dbg !1112
  %30 = load i64, i64* %arrayidx26, align 8, !dbg !1114
  %inc27 = add i64 %30, 1, !dbg !1114
  store i64 %inc27, i64* %arrayidx26, align 8, !dbg !1114
  br label %if.end28, !dbg !1112

if.end28:                                         ; preds = %if.then24, %if.end20
  %31 = load %struct.file*, %struct.file** %file, align 8, !dbg !1115
  %flg29 = getelementptr inbounds %struct.file, %struct.file* %31, i32 0, i32 5, !dbg !1117
  %32 = load i32, i32* %flg29, align 8, !dbg !1117
  %and30 = and i32 %32, 2, !dbg !1118
  %tobool31 = icmp ne i32 %and30, 0, !dbg !1118
  br i1 %tobool31, label %if.then32, label %if.end36, !dbg !1119

if.then32:                                        ; preds = %if.end28
  %33 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1120
  %total_number_time_defined33 = getelementptr inbounds %struct._7zip, %struct._7zip* %33, i32 0, i32 8, !dbg !1121
  %arrayidx34 = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined33, i64 0, i64 1, !dbg !1120
  %34 = load i64, i64* %arrayidx34, align 8, !dbg !1122
  %inc35 = add i64 %34, 1, !dbg !1122
  store i64 %inc35, i64* %arrayidx34, align 8, !dbg !1122
  br label %if.end36, !dbg !1120

if.end36:                                         ; preds = %if.then32, %if.end28
  %35 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1123
  %total_number_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %35, i32 0, i32 3, !dbg !1124
  %36 = load i64, i64* %total_number_entry, align 8, !dbg !1125
  %inc37 = add i64 %36, 1, !dbg !1125
  store i64 %inc37, i64* %total_number_entry, align 8, !dbg !1125
  %37 = load %struct.file*, %struct.file** %file, align 8, !dbg !1126
  %name_len = getelementptr inbounds %struct.file, %struct.file* %37, i32 0, i32 2, !dbg !1127
  %38 = load i32, i32* %name_len, align 8, !dbg !1127
  %add = add i32 %38, 2, !dbg !1128
  %conv = zext i32 %add to i64, !dbg !1126
  %39 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1129
  %total_bytes_entry_name = getelementptr inbounds %struct._7zip, %struct._7zip* %39, i32 0, i32 7, !dbg !1130
  %40 = load i64, i64* %total_bytes_entry_name, align 8, !dbg !1131
  %add38 = add i64 %40, %conv, !dbg !1131
  store i64 %add38, i64* %total_bytes_entry_name, align 8, !dbg !1131
  %41 = load %struct.file*, %struct.file** %file, align 8, !dbg !1132
  %size39 = getelementptr inbounds %struct.file, %struct.file* %41, i32 0, i32 4, !dbg !1134
  %42 = load i64, i64* %size39, align 8, !dbg !1134
  %cmp40 = icmp eq i64 %42, 0, !dbg !1135
  br i1 %cmp40, label %if.then42, label %if.end53, !dbg !1136

if.then42:                                        ; preds = %if.end36
  %43 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1137
  %total_number_empty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %43, i32 0, i32 5, !dbg !1139
  %44 = load i64, i64* %total_number_empty_entry, align 8, !dbg !1140
  %inc43 = add i64 %44, 1, !dbg !1140
  store i64 %inc43, i64* %total_number_empty_entry, align 8, !dbg !1140
  %45 = load %struct.file*, %struct.file** %file, align 8, !dbg !1141
  %dir44 = getelementptr inbounds %struct.file, %struct.file* %45, i32 0, i32 9, !dbg !1143
  %bf.load45 = load i8, i8* %dir44, align 8, !dbg !1143
  %bf.shl46 = shl i8 %bf.load45, 7, !dbg !1143
  %bf.ashr47 = ashr i8 %bf.shl46, 7, !dbg !1143
  %bf.cast48 = sext i8 %bf.ashr47 to i32, !dbg !1143
  %tobool49 = icmp ne i32 %bf.cast48, 0, !dbg !1141
  br i1 %tobool49, label %if.then50, label %if.else, !dbg !1144

if.then50:                                        ; preds = %if.then42
  %46 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1145
  %total_number_dir_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %46, i32 0, i32 6, !dbg !1146
  %47 = load i64, i64* %total_number_dir_entry, align 8, !dbg !1147
  %inc51 = add i64 %47, 1, !dbg !1147
  store i64 %inc51, i64* %total_number_dir_entry, align 8, !dbg !1147
  br label %if.end52, !dbg !1145

if.else:                                          ; preds = %if.then42
  %48 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1148
  %49 = load %struct.file*, %struct.file** %file, align 8, !dbg !1149
  call void @file_register_empty(%struct._7zip* %48, %struct.file* %49), !dbg !1150
  br label %if.end52

if.end52:                                         ; preds = %if.else, %if.then50
  %50 = load i32, i32* %r, align 4, !dbg !1151
  store i32 %50, i32* %retval, align 4, !dbg !1152
  br label %return, !dbg !1152

if.end53:                                         ; preds = %if.end36
  %51 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1153
  %total_number_entry54 = getelementptr inbounds %struct._7zip, %struct._7zip* %51, i32 0, i32 3, !dbg !1155
  %52 = load i64, i64* %total_number_entry54, align 8, !dbg !1155
  %53 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1156
  %total_number_empty_entry55 = getelementptr inbounds %struct._7zip, %struct._7zip* %53, i32 0, i32 5, !dbg !1157
  %54 = load i64, i64* %total_number_empty_entry55, align 8, !dbg !1157
  %sub = sub i64 %52, %54, !dbg !1158
  %cmp56 = icmp eq i64 %sub, 1, !dbg !1159
  br i1 %cmp56, label %if.then58, label %if.end64, !dbg !1160

if.then58:                                        ; preds = %if.end53
  %55 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1161
  %56 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1163
  %opt_compression = getelementptr inbounds %struct._7zip, %struct._7zip* %56, i32 0, i32 16, !dbg !1164
  %57 = load i32, i32* %opt_compression, align 8, !dbg !1164
  %58 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1165
  %opt_compression_level = getelementptr inbounds %struct._7zip, %struct._7zip* %58, i32 0, i32 17, !dbg !1166
  %59 = load i32, i32* %opt_compression_level, align 4, !dbg !1166
  %call59 = call i32 @_7z_compression_init_encoder(%struct.archive_write* %55, i32 %57, i32 %59), !dbg !1167
  store i32 %call59, i32* %r, align 4, !dbg !1168
  %60 = load i32, i32* %r, align 4, !dbg !1169
  %cmp60 = icmp slt i32 %60, 0, !dbg !1171
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !1172

if.then62:                                        ; preds = %if.then58
  %61 = load %struct.file*, %struct.file** %file, align 8, !dbg !1173
  call void @file_free(%struct.file* %61), !dbg !1175
  store i32 -30, i32* %retval, align 4, !dbg !1176
  br label %return, !dbg !1176

if.end63:                                         ; preds = %if.then58
  br label %if.end64, !dbg !1177

if.end64:                                         ; preds = %if.end63, %if.end53
  %62 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1178
  %63 = load %struct.file*, %struct.file** %file, align 8, !dbg !1179
  call void @file_register(%struct._7zip* %62, %struct.file* %63), !dbg !1180
  %64 = load %struct.file*, %struct.file** %file, align 8, !dbg !1181
  %65 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1182
  %cur_file65 = getelementptr inbounds %struct._7zip, %struct._7zip* %65, i32 0, i32 2, !dbg !1183
  store %struct.file* %64, %struct.file** %cur_file65, align 8, !dbg !1184
  %66 = load %struct.file*, %struct.file** %file, align 8, !dbg !1185
  %size66 = getelementptr inbounds %struct.file, %struct.file* %66, i32 0, i32 4, !dbg !1186
  %67 = load i64, i64* %size66, align 8, !dbg !1186
  %68 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1187
  %entry_bytes_remaining67 = getelementptr inbounds %struct._7zip, %struct._7zip* %68, i32 0, i32 11, !dbg !1188
  store i64 %67, i64* %entry_bytes_remaining67, align 8, !dbg !1189
  %69 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1190
  %entry_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %69, i32 0, i32 12, !dbg !1191
  store i32 0, i32* %entry_crc32, align 8, !dbg !1192
  %70 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1193
  %call68 = call i32 @archive_entry_filetype(%struct.archive_entry* %70), !dbg !1195
  %cmp69 = icmp eq i32 %call68, 40960, !dbg !1196
  br i1 %cmp69, label %if.then71, label %if.end88, !dbg !1197

if.then71:                                        ; preds = %if.end64
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1198, metadata !693), !dbg !1200
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1201, metadata !693), !dbg !1202
  %71 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1203
  %call72 = call i8* @archive_entry_symlink(%struct.archive_entry* %71), !dbg !1204
  store i8* %call72, i8** %p, align 8, !dbg !1202
  %72 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1205
  %73 = load i8*, i8** %p, align 8, !dbg !1206
  %74 = load %struct.file*, %struct.file** %file, align 8, !dbg !1207
  %size73 = getelementptr inbounds %struct.file, %struct.file* %74, i32 0, i32 4, !dbg !1208
  %75 = load i64, i64* %size73, align 8, !dbg !1208
  %call74 = call i64 @compress_out(%struct.archive_write* %72, i8* %73, i64 %75, i32 1), !dbg !1209
  store i64 %call74, i64* %bytes, align 8, !dbg !1210
  %76 = load i64, i64* %bytes, align 8, !dbg !1211
  %cmp75 = icmp slt i64 %76, 0, !dbg !1213
  br i1 %cmp75, label %if.then77, label %if.end79, !dbg !1214

if.then77:                                        ; preds = %if.then71
  %77 = load i64, i64* %bytes, align 8, !dbg !1215
  %conv78 = trunc i64 %77 to i32, !dbg !1216
  store i32 %conv78, i32* %retval, align 4, !dbg !1217
  br label %return, !dbg !1217

if.end79:                                         ; preds = %if.then71
  %78 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1218
  %entry_crc3280 = getelementptr inbounds %struct._7zip, %struct._7zip* %78, i32 0, i32 12, !dbg !1219
  %79 = load i32, i32* %entry_crc3280, align 8, !dbg !1219
  %conv81 = zext i32 %79 to i64, !dbg !1218
  %80 = load i8*, i8** %p, align 8, !dbg !1220
  %81 = load i64, i64* %bytes, align 8, !dbg !1221
  %conv82 = trunc i64 %81 to i32, !dbg !1222
  %call83 = call i64 @cm_zlib_crc32(i64 %conv81, i8* %80, i32 %conv82), !dbg !1223
  %conv84 = trunc i64 %call83 to i32, !dbg !1223
  %82 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1224
  %entry_crc3285 = getelementptr inbounds %struct._7zip, %struct._7zip* %82, i32 0, i32 12, !dbg !1225
  store i32 %conv84, i32* %entry_crc3285, align 8, !dbg !1226
  %83 = load i64, i64* %bytes, align 8, !dbg !1227
  %84 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1228
  %entry_bytes_remaining86 = getelementptr inbounds %struct._7zip, %struct._7zip* %84, i32 0, i32 11, !dbg !1229
  %85 = load i64, i64* %entry_bytes_remaining86, align 8, !dbg !1230
  %sub87 = sub i64 %85, %83, !dbg !1230
  store i64 %sub87, i64* %entry_bytes_remaining86, align 8, !dbg !1230
  br label %if.end88, !dbg !1231

if.end88:                                         ; preds = %if.end79, %if.end64
  %86 = load i32, i32* %r, align 4, !dbg !1232
  store i32 %86, i32* %retval, align 4, !dbg !1233
  br label %return, !dbg !1233

return:                                           ; preds = %if.end88, %if.then77, %if.then62, %if.end52, %if.then15, %if.then9, %if.then5
  %87 = load i32, i32* %retval, align 4, !dbg !1234
  ret i32 %87, !dbg !1234
}

; Function Attrs: nounwind uwtable
define internal i64 @_7z_write_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !639 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %zip = alloca %struct._7zip*, align 8
  %bytes = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1235, metadata !693), !dbg !1236
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1237, metadata !693), !dbg !1238
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !1239, metadata !693), !dbg !1240
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1241, metadata !693), !dbg !1242
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1243, metadata !693), !dbg !1244
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1245
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1246
  %1 = load i8*, i8** %format_data, align 8, !dbg !1246
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1247
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1248
  %3 = load i64, i64* %s.addr, align 8, !dbg !1249
  %4 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1251
  %entry_bytes_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %4, i32 0, i32 11, !dbg !1252
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1252
  %cmp = icmp ugt i64 %3, %5, !dbg !1253
  br i1 %cmp, label %if.then, label %if.end, !dbg !1254

if.then:                                          ; preds = %entry
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1255
  %entry_bytes_remaining1 = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 11, !dbg !1256
  %7 = load i64, i64* %entry_bytes_remaining1, align 8, !dbg !1256
  store i64 %7, i64* %s.addr, align 8, !dbg !1257
  br label %if.end, !dbg !1258

if.end:                                           ; preds = %if.then, %entry
  %8 = load i64, i64* %s.addr, align 8, !dbg !1259
  %cmp2 = icmp eq i64 %8, 0, !dbg !1261
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1262

lor.lhs.false:                                    ; preds = %if.end
  %9 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1263
  %cur_file = getelementptr inbounds %struct._7zip, %struct._7zip* %9, i32 0, i32 2, !dbg !1265
  %10 = load %struct.file*, %struct.file** %cur_file, align 8, !dbg !1265
  %cmp3 = icmp eq %struct.file* %10, null, !dbg !1266
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1267

if.then4:                                         ; preds = %lor.lhs.false, %if.end
  store i64 0, i64* %retval, align 8, !dbg !1268
  br label %return, !dbg !1268

if.end5:                                          ; preds = %lor.lhs.false
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1269
  %12 = load i8*, i8** %buff.addr, align 8, !dbg !1270
  %13 = load i64, i64* %s.addr, align 8, !dbg !1271
  %call = call i64 @compress_out(%struct.archive_write* %11, i8* %12, i64 %13, i32 1), !dbg !1272
  store i64 %call, i64* %bytes, align 8, !dbg !1273
  %14 = load i64, i64* %bytes, align 8, !dbg !1274
  %cmp6 = icmp slt i64 %14, 0, !dbg !1276
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1277

if.then7:                                         ; preds = %if.end5
  %15 = load i64, i64* %bytes, align 8, !dbg !1278
  store i64 %15, i64* %retval, align 8, !dbg !1279
  br label %return, !dbg !1279

if.end8:                                          ; preds = %if.end5
  %16 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1280
  %entry_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %16, i32 0, i32 12, !dbg !1281
  %17 = load i32, i32* %entry_crc32, align 8, !dbg !1281
  %conv = zext i32 %17 to i64, !dbg !1280
  %18 = load i8*, i8** %buff.addr, align 8, !dbg !1282
  %19 = load i64, i64* %bytes, align 8, !dbg !1283
  %conv9 = trunc i64 %19 to i32, !dbg !1284
  %call10 = call i64 @cm_zlib_crc32(i64 %conv, i8* %18, i32 %conv9), !dbg !1285
  %conv11 = trunc i64 %call10 to i32, !dbg !1285
  %20 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1286
  %entry_crc3212 = getelementptr inbounds %struct._7zip, %struct._7zip* %20, i32 0, i32 12, !dbg !1287
  store i32 %conv11, i32* %entry_crc3212, align 8, !dbg !1288
  %21 = load i64, i64* %bytes, align 8, !dbg !1289
  %22 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1290
  %entry_bytes_remaining13 = getelementptr inbounds %struct._7zip, %struct._7zip* %22, i32 0, i32 11, !dbg !1291
  %23 = load i64, i64* %entry_bytes_remaining13, align 8, !dbg !1292
  %sub = sub i64 %23, %21, !dbg !1292
  store i64 %sub, i64* %entry_bytes_remaining13, align 8, !dbg !1292
  %24 = load i64, i64* %bytes, align 8, !dbg !1293
  store i64 %24, i64* %retval, align 8, !dbg !1294
  br label %return, !dbg !1294

return:                                           ; preds = %if.end8, %if.then7, %if.then4
  %25 = load i64, i64* %retval, align 8, !dbg !1295
  ret i64 %25, !dbg !1295
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_finish_entry(%struct.archive_write* %a) #0 !dbg !640 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  %s = alloca i64, align 8
  %r = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1296, metadata !693), !dbg !1297
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1298, metadata !693), !dbg !1299
  call void @llvm.dbg.declare(metadata i64* %s, metadata !1300, metadata !693), !dbg !1301
  call void @llvm.dbg.declare(metadata i64* %r, metadata !1302, metadata !693), !dbg !1303
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1304
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1305
  %1 = load i8*, i8** %format_data, align 8, !dbg !1305
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1306
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1307
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1308
  %cur_file = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 2, !dbg !1310
  %4 = load %struct.file*, %struct.file** %cur_file, align 8, !dbg !1310
  %cmp = icmp eq %struct.file* %4, null, !dbg !1311
  br i1 %cmp, label %if.then, label %if.end, !dbg !1312

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1313
  br label %return, !dbg !1313

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !1314

while.cond:                                       ; preds = %if.end9, %if.end
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1315
  %entry_bytes_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 11, !dbg !1317
  %6 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1317
  %cmp1 = icmp ugt i64 %6, 0, !dbg !1318
  br i1 %cmp1, label %while.body, label %while.end, !dbg !1319

while.body:                                       ; preds = %while.cond
  %7 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1320
  %entry_bytes_remaining2 = getelementptr inbounds %struct._7zip, %struct._7zip* %7, i32 0, i32 11, !dbg !1322
  %8 = load i64, i64* %entry_bytes_remaining2, align 8, !dbg !1322
  store i64 %8, i64* %s, align 8, !dbg !1323
  %9 = load i64, i64* %s, align 8, !dbg !1324
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1326
  %null_length = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 5, !dbg !1327
  %11 = load i64, i64* %null_length, align 8, !dbg !1327
  %cmp3 = icmp ugt i64 %9, %11, !dbg !1328
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !1329

if.then4:                                         ; preds = %while.body
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1330
  %null_length5 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 5, !dbg !1331
  %13 = load i64, i64* %null_length5, align 8, !dbg !1331
  store i64 %13, i64* %s, align 8, !dbg !1332
  br label %if.end6, !dbg !1333

if.end6:                                          ; preds = %if.then4, %while.body
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1334
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1335
  %nulls = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 4, !dbg !1336
  %16 = load i8*, i8** %nulls, align 8, !dbg !1336
  %17 = load i64, i64* %s, align 8, !dbg !1337
  %call = call i64 @_7z_write_data(%struct.archive_write* %14, i8* %16, i64 %17), !dbg !1338
  store i64 %call, i64* %r, align 8, !dbg !1339
  %18 = load i64, i64* %r, align 8, !dbg !1340
  %cmp7 = icmp slt i64 %18, 0, !dbg !1342
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1343

if.then8:                                         ; preds = %if.end6
  %19 = load i64, i64* %r, align 8, !dbg !1344
  %conv = trunc i64 %19 to i32, !dbg !1345
  store i32 %conv, i32* %retval, align 4, !dbg !1346
  br label %return, !dbg !1346

if.end9:                                          ; preds = %if.end6
  br label %while.cond, !dbg !1347

while.end:                                        ; preds = %while.cond
  %20 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1349
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %20, i32 0, i32 18, !dbg !1350
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream, i32 0, i32 2, !dbg !1351
  %21 = load i64, i64* %total_in, align 8, !dbg !1351
  %22 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1352
  %total_bytes_compressed = getelementptr inbounds %struct._7zip, %struct._7zip* %22, i32 0, i32 9, !dbg !1353
  %23 = load i64, i64* %total_bytes_compressed, align 8, !dbg !1354
  %add = add i64 %23, %21, !dbg !1354
  store i64 %add, i64* %total_bytes_compressed, align 8, !dbg !1354
  %24 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1355
  %stream10 = getelementptr inbounds %struct._7zip, %struct._7zip* %24, i32 0, i32 18, !dbg !1356
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream10, i32 0, i32 5, !dbg !1357
  %25 = load i64, i64* %total_out, align 8, !dbg !1357
  %26 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1358
  %total_bytes_uncompressed = getelementptr inbounds %struct._7zip, %struct._7zip* %26, i32 0, i32 10, !dbg !1359
  %27 = load i64, i64* %total_bytes_uncompressed, align 8, !dbg !1360
  %add11 = add i64 %27, %25, !dbg !1360
  store i64 %add11, i64* %total_bytes_uncompressed, align 8, !dbg !1360
  %28 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1361
  %entry_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %28, i32 0, i32 12, !dbg !1362
  %29 = load i32, i32* %entry_crc32, align 8, !dbg !1362
  %30 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1363
  %cur_file12 = getelementptr inbounds %struct._7zip, %struct._7zip* %30, i32 0, i32 2, !dbg !1364
  %31 = load %struct.file*, %struct.file** %cur_file12, align 8, !dbg !1364
  %cm_zlib_crc32 = getelementptr inbounds %struct.file, %struct.file* %31, i32 0, i32 8, !dbg !1365
  store i32 %29, i32* %cm_zlib_crc32, align 4, !dbg !1366
  %32 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1367
  %cur_file13 = getelementptr inbounds %struct._7zip, %struct._7zip* %32, i32 0, i32 2, !dbg !1368
  store %struct.file* null, %struct.file** %cur_file13, align 8, !dbg !1369
  store i32 0, i32* %retval, align 4, !dbg !1370
  br label %return, !dbg !1370

return:                                           ; preds = %while.end, %if.then8, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !1371
  ret i32 %33, !dbg !1371
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_close(%struct.archive_write* %a) #0 !dbg !641 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  %wb = alloca i8*, align 8
  %header_offset = alloca i64, align 8
  %header_size = alloca i64, align 8
  %header_unpacksize = alloca i64, align 8
  %length = alloca i64, align 8
  %header_crc32 = alloca i32, align 4
  %r = alloca i32, align 4
  %n = alloca %struct.archive_rb_node*, align 8
  %data_offset = alloca i64, align 8
  %data_size = alloca i64, align 8
  %data_unpacksize = alloca i64, align 8
  %header_compression = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1372, metadata !693), !dbg !1373
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1374, metadata !693), !dbg !1375
  call void @llvm.dbg.declare(metadata i8** %wb, metadata !1376, metadata !693), !dbg !1377
  call void @llvm.dbg.declare(metadata i64* %header_offset, metadata !1378, metadata !693), !dbg !1379
  call void @llvm.dbg.declare(metadata i64* %header_size, metadata !1380, metadata !693), !dbg !1381
  call void @llvm.dbg.declare(metadata i64* %header_unpacksize, metadata !1382, metadata !693), !dbg !1383
  call void @llvm.dbg.declare(metadata i64* %length, metadata !1384, metadata !693), !dbg !1385
  call void @llvm.dbg.declare(metadata i32* %header_crc32, metadata !1386, metadata !693), !dbg !1387
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1388, metadata !693), !dbg !1389
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1390
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1391
  %1 = load i8*, i8** %format_data, align 8, !dbg !1391
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1392
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1393
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1394
  %total_number_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 3, !dbg !1396
  %4 = load i64, i64* %total_number_entry, align 8, !dbg !1396
  %cmp = icmp ugt i64 %4, 0, !dbg !1397
  br i1 %cmp, label %if.then, label %if.else, !dbg !1398

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n, metadata !1399, metadata !693), !dbg !1401
  call void @llvm.dbg.declare(metadata i64* %data_offset, metadata !1402, metadata !693), !dbg !1403
  call void @llvm.dbg.declare(metadata i64* %data_size, metadata !1404, metadata !693), !dbg !1405
  call void @llvm.dbg.declare(metadata i64* %data_unpacksize, metadata !1406, metadata !693), !dbg !1407
  call void @llvm.dbg.declare(metadata i32* %header_compression, metadata !1408, metadata !693), !dbg !1409
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1410
  %call = call i64 @compress_out(%struct.archive_write* %5, i8* null, i64 0, i32 0), !dbg !1411
  %conv = trunc i64 %call to i32, !dbg !1412
  store i32 %conv, i32* %r, align 4, !dbg !1413
  %6 = load i32, i32* %r, align 4, !dbg !1414
  %cmp1 = icmp slt i32 %6, 0, !dbg !1416
  br i1 %cmp1, label %if.then3, label %if.end, !dbg !1417

if.then3:                                         ; preds = %if.then
  %7 = load i32, i32* %r, align 4, !dbg !1418
  store i32 %7, i32* %retval, align 4, !dbg !1419
  br label %return, !dbg !1419

if.end:                                           ; preds = %if.then
  store i64 0, i64* %data_offset, align 8, !dbg !1420
  %8 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1421
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %8, i32 0, i32 18, !dbg !1422
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream, i32 0, i32 5, !dbg !1423
  %9 = load i64, i64* %total_out, align 8, !dbg !1423
  store i64 %9, i64* %data_size, align 8, !dbg !1424
  %10 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1425
  %stream4 = getelementptr inbounds %struct._7zip, %struct._7zip* %10, i32 0, i32 18, !dbg !1426
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream4, i32 0, i32 2, !dbg !1427
  %11 = load i64, i64* %total_in, align 8, !dbg !1427
  store i64 %11, i64* %data_unpacksize, align 8, !dbg !1428
  %12 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1429
  %opt_compression = getelementptr inbounds %struct._7zip, %struct._7zip* %12, i32 0, i32 16, !dbg !1430
  %13 = load i32, i32* %opt_compression, align 8, !dbg !1430
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1431
  %coder = getelementptr inbounds %struct._7zip, %struct._7zip* %14, i32 0, i32 19, !dbg !1432
  %codec = getelementptr inbounds %struct.coder, %struct.coder* %coder, i32 0, i32 0, !dbg !1433
  store i32 %13, i32* %codec, align 8, !dbg !1434
  %15 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1435
  %stream5 = getelementptr inbounds %struct._7zip, %struct._7zip* %15, i32 0, i32 18, !dbg !1436
  %prop_size = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream5, i32 0, i32 6, !dbg !1437
  %16 = load i32, i32* %prop_size, align 8, !dbg !1437
  %conv6 = zext i32 %16 to i64, !dbg !1435
  %17 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1438
  %coder7 = getelementptr inbounds %struct._7zip, %struct._7zip* %17, i32 0, i32 19, !dbg !1439
  %prop_size8 = getelementptr inbounds %struct.coder, %struct.coder* %coder7, i32 0, i32 1, !dbg !1440
  store i64 %conv6, i64* %prop_size8, align 8, !dbg !1441
  %18 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1442
  %stream9 = getelementptr inbounds %struct._7zip, %struct._7zip* %18, i32 0, i32 18, !dbg !1443
  %props = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream9, i32 0, i32 7, !dbg !1444
  %19 = load i8*, i8** %props, align 8, !dbg !1444
  %20 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1445
  %coder10 = getelementptr inbounds %struct._7zip, %struct._7zip* %20, i32 0, i32 19, !dbg !1446
  %props11 = getelementptr inbounds %struct.coder, %struct.coder* %coder10, i32 0, i32 2, !dbg !1447
  store i8* %19, i8** %props11, align 8, !dbg !1448
  %21 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1449
  %stream12 = getelementptr inbounds %struct._7zip, %struct._7zip* %21, i32 0, i32 18, !dbg !1450
  %prop_size13 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream12, i32 0, i32 6, !dbg !1451
  store i32 0, i32* %prop_size13, align 8, !dbg !1452
  %22 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1453
  %stream14 = getelementptr inbounds %struct._7zip, %struct._7zip* %22, i32 0, i32 18, !dbg !1454
  %props15 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream14, i32 0, i32 7, !dbg !1455
  store i8* null, i8** %props15, align 8, !dbg !1456
  %23 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1457
  %total_number_entry16 = getelementptr inbounds %struct._7zip, %struct._7zip* %23, i32 0, i32 3, !dbg !1458
  %24 = load i64, i64* %total_number_entry16, align 8, !dbg !1458
  %25 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1459
  %total_number_empty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %25, i32 0, i32 5, !dbg !1460
  %26 = load i64, i64* %total_number_empty_entry, align 8, !dbg !1460
  %sub = sub i64 %24, %26, !dbg !1461
  %27 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1462
  %total_number_nonempty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %27, i32 0, i32 4, !dbg !1463
  store i64 %sub, i64* %total_number_nonempty_entry, align 8, !dbg !1464
  %28 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1465
  %empty_list = getelementptr inbounds %struct._7zip, %struct._7zip* %28, i32 0, i32 24, !dbg !1467
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list, i32 0, i32 0, !dbg !1468
  %29 = load %struct.file*, %struct.file** %first, align 8, !dbg !1468
  %cmp17 = icmp ne %struct.file* %29, null, !dbg !1469
  br i1 %cmp17, label %if.then19, label %if.end26, !dbg !1470

if.then19:                                        ; preds = %if.end
  %30 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1471
  %empty_list20 = getelementptr inbounds %struct._7zip, %struct._7zip* %30, i32 0, i32 24, !dbg !1473
  %first21 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list20, i32 0, i32 0, !dbg !1474
  %31 = load %struct.file*, %struct.file** %first21, align 8, !dbg !1474
  %32 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1475
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %32, i32 0, i32 23, !dbg !1476
  %last = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 1, !dbg !1477
  %33 = load %struct.file**, %struct.file*** %last, align 8, !dbg !1477
  store %struct.file* %31, %struct.file** %33, align 8, !dbg !1478
  %34 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1479
  %empty_list22 = getelementptr inbounds %struct._7zip, %struct._7zip* %34, i32 0, i32 24, !dbg !1480
  %last23 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list22, i32 0, i32 1, !dbg !1481
  %35 = load %struct.file**, %struct.file*** %last23, align 8, !dbg !1481
  %36 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1482
  %file_list24 = getelementptr inbounds %struct._7zip, %struct._7zip* %36, i32 0, i32 23, !dbg !1483
  %last25 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list24, i32 0, i32 1, !dbg !1484
  store %struct.file** %35, %struct.file*** %last25, align 8, !dbg !1485
  br label %if.end26, !dbg !1486

if.end26:                                         ; preds = %if.then19, %if.end
  %37 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1487
  %rbtree = getelementptr inbounds %struct._7zip, %struct._7zip* %37, i32 0, i32 25, !dbg !1487
  %call27 = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree, %struct.archive_rb_node* null, i32 0), !dbg !1487
  store %struct.archive_rb_node* %call27, %struct.archive_rb_node** %n, align 8, !dbg !1487
  br label %for.cond, !dbg !1487

for.cond:                                         ; preds = %for.inc, %if.end26
  %38 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !1489
  %tobool = icmp ne %struct.archive_rb_node* %38, null, !dbg !1489
  br i1 %tobool, label %for.body, label %for.end, !dbg !1489

for.body:                                         ; preds = %for.cond
  %39 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1492
  %40 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !1494
  %41 = bitcast %struct.archive_rb_node* %40 to %struct.file*, !dbg !1495
  call void @file_register(%struct._7zip* %39, %struct.file* %41), !dbg !1496
  br label %for.inc, !dbg !1497

for.inc:                                          ; preds = %for.body
  %42 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1498
  %rbtree28 = getelementptr inbounds %struct._7zip, %struct._7zip* %42, i32 0, i32 25, !dbg !1498
  %43 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n, align 8, !dbg !1498
  %call29 = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbtree28, %struct.archive_rb_node* %43, i32 1), !dbg !1498
  store %struct.archive_rb_node* %call29, %struct.archive_rb_node** %n, align 8, !dbg !1498
  br label %for.cond, !dbg !1498

for.end:                                          ; preds = %for.cond
  store i32 196865, i32* %header_compression, align 4, !dbg !1500
  %44 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1501
  %total_number_entry30 = getelementptr inbounds %struct._7zip, %struct._7zip* %44, i32 0, i32 3, !dbg !1503
  %45 = load i64, i64* %total_number_entry30, align 8, !dbg !1503
  %cmp31 = icmp eq i64 %45, 1, !dbg !1504
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !1505

if.then33:                                        ; preds = %for.end
  store i32 0, i32* %header_compression, align 4, !dbg !1506
  br label %if.end34, !dbg !1507

if.end34:                                         ; preds = %if.then33, %for.end
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1508
  %47 = load i32, i32* %header_compression, align 4, !dbg !1509
  %call35 = call i32 @_7z_compression_init_encoder(%struct.archive_write* %46, i32 %47, i32 6), !dbg !1510
  store i32 %call35, i32* %r, align 4, !dbg !1511
  %48 = load i32, i32* %r, align 4, !dbg !1512
  %cmp36 = icmp slt i32 %48, 0, !dbg !1514
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !1515

if.then38:                                        ; preds = %if.end34
  %49 = load i32, i32* %r, align 4, !dbg !1516
  store i32 %49, i32* %retval, align 4, !dbg !1517
  br label %return, !dbg !1517

if.end39:                                         ; preds = %if.end34
  %50 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1518
  %crc32flg = getelementptr inbounds %struct._7zip, %struct._7zip* %50, i32 0, i32 15, !dbg !1519
  store i32 1, i32* %crc32flg, align 4, !dbg !1520
  %51 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1521
  %precode_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %51, i32 0, i32 13, !dbg !1522
  store i32 0, i32* %precode_crc32, align 4, !dbg !1523
  %52 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1524
  %53 = load i64, i64* %data_offset, align 8, !dbg !1525
  %54 = load i64, i64* %data_size, align 8, !dbg !1526
  %55 = load i64, i64* %data_unpacksize, align 8, !dbg !1527
  %56 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1528
  %coder40 = getelementptr inbounds %struct._7zip, %struct._7zip* %56, i32 0, i32 19, !dbg !1529
  %call41 = call i32 @make_header(%struct.archive_write* %52, i64 %53, i64 %54, i64 %55, i32 1, %struct.coder* %coder40), !dbg !1530
  store i32 %call41, i32* %r, align 4, !dbg !1531
  %57 = load i32, i32* %r, align 4, !dbg !1532
  %cmp42 = icmp slt i32 %57, 0, !dbg !1534
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !1535

if.then44:                                        ; preds = %if.end39
  %58 = load i32, i32* %r, align 4, !dbg !1536
  store i32 %58, i32* %retval, align 4, !dbg !1537
  br label %return, !dbg !1537

if.end45:                                         ; preds = %if.end39
  %59 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1538
  %call46 = call i64 @compress_out(%struct.archive_write* %59, i8* null, i64 0, i32 0), !dbg !1539
  %conv47 = trunc i64 %call46 to i32, !dbg !1540
  store i32 %conv47, i32* %r, align 4, !dbg !1541
  %60 = load i32, i32* %r, align 4, !dbg !1542
  %cmp48 = icmp slt i32 %60, 0, !dbg !1544
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !1545

if.then50:                                        ; preds = %if.end45
  %61 = load i32, i32* %r, align 4, !dbg !1546
  store i32 %61, i32* %retval, align 4, !dbg !1547
  br label %return, !dbg !1547

if.end51:                                         ; preds = %if.end45
  %62 = load i64, i64* %data_offset, align 8, !dbg !1548
  %63 = load i64, i64* %data_size, align 8, !dbg !1549
  %add = add i64 %62, %63, !dbg !1550
  store i64 %add, i64* %header_offset, align 8, !dbg !1551
  %64 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1552
  %stream52 = getelementptr inbounds %struct._7zip, %struct._7zip* %64, i32 0, i32 18, !dbg !1553
  %total_out53 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream52, i32 0, i32 5, !dbg !1554
  %65 = load i64, i64* %total_out53, align 8, !dbg !1554
  store i64 %65, i64* %header_size, align 8, !dbg !1555
  %66 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1556
  %precode_crc3254 = getelementptr inbounds %struct._7zip, %struct._7zip* %66, i32 0, i32 13, !dbg !1557
  %67 = load i32, i32* %precode_crc3254, align 4, !dbg !1557
  store i32 %67, i32* %header_crc32, align 4, !dbg !1558
  %68 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1559
  %stream55 = getelementptr inbounds %struct._7zip, %struct._7zip* %68, i32 0, i32 18, !dbg !1560
  %total_in56 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream55, i32 0, i32 2, !dbg !1561
  %69 = load i64, i64* %total_in56, align 8, !dbg !1561
  store i64 %69, i64* %header_unpacksize, align 8, !dbg !1562
  %70 = load i32, i32* %header_compression, align 4, !dbg !1563
  %cmp57 = icmp ne i32 %70, 0, !dbg !1565
  br i1 %cmp57, label %if.then59, label %if.end104, !dbg !1566

if.then59:                                        ; preds = %if.end51
  %71 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1567
  %coder60 = getelementptr inbounds %struct._7zip, %struct._7zip* %71, i32 0, i32 19, !dbg !1569
  %props61 = getelementptr inbounds %struct.coder, %struct.coder* %coder60, i32 0, i32 2, !dbg !1570
  %72 = load i8*, i8** %props61, align 8, !dbg !1570
  call void @free(i8* %72) #8, !dbg !1571
  %73 = load i32, i32* %header_compression, align 4, !dbg !1572
  %74 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1573
  %coder62 = getelementptr inbounds %struct._7zip, %struct._7zip* %74, i32 0, i32 19, !dbg !1574
  %codec63 = getelementptr inbounds %struct.coder, %struct.coder* %coder62, i32 0, i32 0, !dbg !1575
  store i32 %73, i32* %codec63, align 8, !dbg !1576
  %75 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1577
  %stream64 = getelementptr inbounds %struct._7zip, %struct._7zip* %75, i32 0, i32 18, !dbg !1578
  %prop_size65 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream64, i32 0, i32 6, !dbg !1579
  %76 = load i32, i32* %prop_size65, align 8, !dbg !1579
  %conv66 = zext i32 %76 to i64, !dbg !1577
  %77 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1580
  %coder67 = getelementptr inbounds %struct._7zip, %struct._7zip* %77, i32 0, i32 19, !dbg !1581
  %prop_size68 = getelementptr inbounds %struct.coder, %struct.coder* %coder67, i32 0, i32 1, !dbg !1582
  store i64 %conv66, i64* %prop_size68, align 8, !dbg !1583
  %78 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1584
  %stream69 = getelementptr inbounds %struct._7zip, %struct._7zip* %78, i32 0, i32 18, !dbg !1585
  %props70 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream69, i32 0, i32 7, !dbg !1586
  %79 = load i8*, i8** %props70, align 8, !dbg !1586
  %80 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1587
  %coder71 = getelementptr inbounds %struct._7zip, %struct._7zip* %80, i32 0, i32 19, !dbg !1588
  %props72 = getelementptr inbounds %struct.coder, %struct.coder* %coder71, i32 0, i32 2, !dbg !1589
  store i8* %79, i8** %props72, align 8, !dbg !1590
  %81 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1591
  %stream73 = getelementptr inbounds %struct._7zip, %struct._7zip* %81, i32 0, i32 18, !dbg !1592
  %prop_size74 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream73, i32 0, i32 6, !dbg !1593
  store i32 0, i32* %prop_size74, align 8, !dbg !1594
  %82 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1595
  %stream75 = getelementptr inbounds %struct._7zip, %struct._7zip* %82, i32 0, i32 18, !dbg !1596
  %props76 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream75, i32 0, i32 7, !dbg !1597
  store i8* null, i8** %props76, align 8, !dbg !1598
  %83 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1599
  %call77 = call i32 @_7z_compression_init_encoder(%struct.archive_write* %83, i32 0, i32 0), !dbg !1600
  store i32 %call77, i32* %r, align 4, !dbg !1601
  %84 = load i32, i32* %r, align 4, !dbg !1602
  %cmp78 = icmp slt i32 %84, 0, !dbg !1604
  br i1 %cmp78, label %if.then80, label %if.end81, !dbg !1605

if.then80:                                        ; preds = %if.then59
  %85 = load i32, i32* %r, align 4, !dbg !1606
  store i32 %85, i32* %retval, align 4, !dbg !1607
  br label %return, !dbg !1607

if.end81:                                         ; preds = %if.then59
  %86 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1608
  %crc32flg82 = getelementptr inbounds %struct._7zip, %struct._7zip* %86, i32 0, i32 15, !dbg !1609
  store i32 2, i32* %crc32flg82, align 4, !dbg !1610
  %87 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1611
  %encoded_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %87, i32 0, i32 14, !dbg !1612
  store i32 0, i32* %encoded_crc32, align 8, !dbg !1613
  %88 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1614
  %call83 = call i32 @enc_uint64(%struct.archive_write* %88, i64 23), !dbg !1615
  store i32 %call83, i32* %r, align 4, !dbg !1616
  %89 = load i32, i32* %r, align 4, !dbg !1617
  %cmp84 = icmp slt i32 %89, 0, !dbg !1619
  br i1 %cmp84, label %if.then86, label %if.end87, !dbg !1620

if.then86:                                        ; preds = %if.end81
  %90 = load i32, i32* %r, align 4, !dbg !1621
  store i32 %90, i32* %retval, align 4, !dbg !1622
  br label %return, !dbg !1622

if.end87:                                         ; preds = %if.end81
  %91 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1623
  %92 = load i64, i64* %header_offset, align 8, !dbg !1624
  %93 = load i64, i64* %header_size, align 8, !dbg !1625
  %94 = load i64, i64* %header_unpacksize, align 8, !dbg !1626
  %95 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1627
  %coder88 = getelementptr inbounds %struct._7zip, %struct._7zip* %95, i32 0, i32 19, !dbg !1628
  %96 = load i32, i32* %header_crc32, align 4, !dbg !1629
  %call89 = call i32 @make_streamsInfo(%struct.archive_write* %91, i64 %92, i64 %93, i64 %94, i32 1, %struct.coder* %coder88, i32 0, i32 %96), !dbg !1630
  store i32 %call89, i32* %r, align 4, !dbg !1631
  %97 = load i32, i32* %r, align 4, !dbg !1632
  %cmp90 = icmp slt i32 %97, 0, !dbg !1634
  br i1 %cmp90, label %if.then92, label %if.end93, !dbg !1635

if.then92:                                        ; preds = %if.end87
  %98 = load i32, i32* %r, align 4, !dbg !1636
  store i32 %98, i32* %retval, align 4, !dbg !1637
  br label %return, !dbg !1637

if.end93:                                         ; preds = %if.end87
  %99 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1638
  %call94 = call i64 @compress_out(%struct.archive_write* %99, i8* null, i64 0, i32 0), !dbg !1639
  %conv95 = trunc i64 %call94 to i32, !dbg !1640
  store i32 %conv95, i32* %r, align 4, !dbg !1641
  %100 = load i32, i32* %r, align 4, !dbg !1642
  %cmp96 = icmp slt i32 %100, 0, !dbg !1644
  br i1 %cmp96, label %if.then98, label %if.end99, !dbg !1645

if.then98:                                        ; preds = %if.end93
  %101 = load i32, i32* %r, align 4, !dbg !1646
  store i32 %101, i32* %retval, align 4, !dbg !1647
  br label %return, !dbg !1647

if.end99:                                         ; preds = %if.end93
  %102 = load i64, i64* %header_offset, align 8, !dbg !1648
  %103 = load i64, i64* %header_size, align 8, !dbg !1649
  %add100 = add i64 %102, %103, !dbg !1650
  store i64 %add100, i64* %header_offset, align 8, !dbg !1651
  %104 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1652
  %stream101 = getelementptr inbounds %struct._7zip, %struct._7zip* %104, i32 0, i32 18, !dbg !1653
  %total_out102 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream101, i32 0, i32 5, !dbg !1654
  %105 = load i64, i64* %total_out102, align 8, !dbg !1654
  store i64 %105, i64* %header_size, align 8, !dbg !1655
  %106 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1656
  %encoded_crc32103 = getelementptr inbounds %struct._7zip, %struct._7zip* %106, i32 0, i32 14, !dbg !1657
  %107 = load i32, i32* %encoded_crc32103, align 8, !dbg !1657
  store i32 %107, i32* %header_crc32, align 4, !dbg !1658
  br label %if.end104, !dbg !1659

if.end104:                                        ; preds = %if.end99, %if.end51
  %108 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1660
  %crc32flg105 = getelementptr inbounds %struct._7zip, %struct._7zip* %108, i32 0, i32 15, !dbg !1661
  store i32 0, i32* %crc32flg105, align 4, !dbg !1662
  br label %if.end106, !dbg !1663

if.else:                                          ; preds = %entry
  store i64 0, i64* %header_size, align 8, !dbg !1664
  store i64 0, i64* %header_offset, align 8, !dbg !1666
  store i32 0, i32* %header_crc32, align 4, !dbg !1667
  br label %if.end106

if.end106:                                        ; preds = %if.else, %if.end104
  %109 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1668
  %temp_offset = getelementptr inbounds %struct._7zip, %struct._7zip* %109, i32 0, i32 1, !dbg !1669
  %110 = load i64, i64* %temp_offset, align 8, !dbg !1669
  store i64 %110, i64* %length, align 8, !dbg !1670
  %111 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1671
  %wbuff = getelementptr inbounds %struct._7zip, %struct._7zip* %111, i32 0, i32 21, !dbg !1672
  %arraydecay = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff, i32 0, i32 0, !dbg !1671
  store i8* %arraydecay, i8** %wb, align 8, !dbg !1673
  %112 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1674
  %wbuff_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %112, i32 0, i32 22, !dbg !1675
  store i64 61440, i64* %wbuff_remaining, align 8, !dbg !1676
  %113 = load i8*, i8** %wb, align 8, !dbg !1677
  %arrayidx = getelementptr inbounds i8, i8* %113, i64 0, !dbg !1677
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arrayidx, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.47, i32 0, i32 0), i64 6, i32 1, i1 false), !dbg !1678
  %114 = load i8*, i8** %wb, align 8, !dbg !1679
  %arrayidx107 = getelementptr inbounds i8, i8* %114, i64 6, !dbg !1679
  store i8 0, i8* %arrayidx107, align 1, !dbg !1680
  %115 = load i8*, i8** %wb, align 8, !dbg !1681
  %arrayidx108 = getelementptr inbounds i8, i8* %115, i64 7, !dbg !1681
  store i8 3, i8* %arrayidx108, align 1, !dbg !1682
  %116 = load i8*, i8** %wb, align 8, !dbg !1683
  %arrayidx109 = getelementptr inbounds i8, i8* %116, i64 12, !dbg !1683
  %117 = load i64, i64* %header_offset, align 8, !dbg !1684
  call void @archive_le64enc(i8* %arrayidx109, i64 %117), !dbg !1685
  %118 = load i8*, i8** %wb, align 8, !dbg !1686
  %arrayidx110 = getelementptr inbounds i8, i8* %118, i64 20, !dbg !1686
  %119 = load i64, i64* %header_size, align 8, !dbg !1687
  call void @archive_le64enc(i8* %arrayidx110, i64 %119), !dbg !1688
  %120 = load i8*, i8** %wb, align 8, !dbg !1689
  %arrayidx111 = getelementptr inbounds i8, i8* %120, i64 28, !dbg !1689
  %121 = load i32, i32* %header_crc32, align 4, !dbg !1690
  call void @archive_le32enc(i8* %arrayidx111, i32 %121), !dbg !1691
  %122 = load i8*, i8** %wb, align 8, !dbg !1692
  %arrayidx112 = getelementptr inbounds i8, i8* %122, i64 8, !dbg !1692
  %123 = load i8*, i8** %wb, align 8, !dbg !1693
  %arrayidx113 = getelementptr inbounds i8, i8* %123, i64 12, !dbg !1693
  %call114 = call i64 @cm_zlib_crc32(i64 0, i8* %arrayidx113, i32 20), !dbg !1694
  %conv115 = trunc i64 %call114 to i32, !dbg !1694
  call void @archive_le32enc(i8* %arrayidx112, i32 %conv115), !dbg !1695
  %124 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1697
  %wbuff_remaining116 = getelementptr inbounds %struct._7zip, %struct._7zip* %124, i32 0, i32 22, !dbg !1698
  %125 = load i64, i64* %wbuff_remaining116, align 8, !dbg !1699
  %sub117 = sub i64 %125, 32, !dbg !1699
  store i64 %sub117, i64* %wbuff_remaining116, align 8, !dbg !1699
  %126 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1700
  %127 = load i64, i64* %length, align 8, !dbg !1701
  %call118 = call i32 @copy_out(%struct.archive_write* %126, i64 0, i64 %127), !dbg !1702
  store i32 %call118, i32* %r, align 4, !dbg !1703
  %128 = load i32, i32* %r, align 4, !dbg !1704
  %cmp119 = icmp ne i32 %128, 0, !dbg !1706
  br i1 %cmp119, label %if.then121, label %if.end122, !dbg !1707

if.then121:                                       ; preds = %if.end106
  %129 = load i32, i32* %r, align 4, !dbg !1708
  store i32 %129, i32* %retval, align 4, !dbg !1709
  br label %return, !dbg !1709

if.end122:                                        ; preds = %if.end106
  %130 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1710
  %call123 = call i32 @flush_wbuff(%struct.archive_write* %130), !dbg !1711
  store i32 %call123, i32* %r, align 4, !dbg !1712
  %131 = load i32, i32* %r, align 4, !dbg !1713
  store i32 %131, i32* %retval, align 4, !dbg !1714
  br label %return, !dbg !1714

return:                                           ; preds = %if.end122, %if.then121, %if.then98, %if.then92, %if.then86, %if.then80, %if.then50, %if.then44, %if.then38, %if.then3
  %132 = load i32, i32* %retval, align 4, !dbg !1715
  ret i32 %132, !dbg !1715
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_free(%struct.archive_write* %a) #0 !dbg !670 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1716, metadata !693), !dbg !1717
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1718, metadata !693), !dbg !1719
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1720
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1721
  %1 = load i8*, i8** %format_data, align 8, !dbg !1721
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1722
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1719
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1723
  %temp_fd = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 0, !dbg !1725
  %4 = load i32, i32* %temp_fd, align 8, !dbg !1725
  %cmp = icmp sge i32 %4, 0, !dbg !1726
  br i1 %cmp, label %if.then, label %if.end, !dbg !1727

if.then:                                          ; preds = %entry
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1728
  %temp_fd1 = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 0, !dbg !1729
  %6 = load i32, i32* %temp_fd1, align 8, !dbg !1729
  %call = call i32 @close(i32 %6), !dbg !1730
  br label %if.end, !dbg !1730

if.end:                                           ; preds = %if.then, %entry
  %7 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1731
  call void @file_free_register(%struct._7zip* %7), !dbg !1732
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1733
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !1734
  %9 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1735
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %9, i32 0, i32 18, !dbg !1736
  %call2 = call i32 @compression_end(%struct.archive* %archive, %struct.la_zstream* %stream), !dbg !1737
  %10 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1738
  %coder = getelementptr inbounds %struct._7zip, %struct._7zip* %10, i32 0, i32 19, !dbg !1739
  %props = getelementptr inbounds %struct.coder, %struct.coder* %coder, i32 0, i32 2, !dbg !1740
  %11 = load i8*, i8** %props, align 8, !dbg !1740
  call void @free(i8* %11) #8, !dbg !1741
  %12 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1742
  %13 = bitcast %struct._7zip* %12 to i8*, !dbg !1742
  call void @free(i8* %13) #8, !dbg !1743
  ret i32 0, !dbg !1744
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_new(%struct.archive_write* %a, %struct.archive_entry* %entry1, %struct.file** %newfile) #0 !dbg !584 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %newfile.addr = alloca %struct.file**, align 8
  %zip = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %u16 = alloca i8*, align 8
  %u16len = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1745, metadata !693), !dbg !1746
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1747, metadata !693), !dbg !1748
  store %struct.file** %newfile, %struct.file*** %newfile.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.file*** %newfile.addr, metadata !1749, metadata !693), !dbg !1750
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1751, metadata !693), !dbg !1752
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !1753, metadata !693), !dbg !1754
  call void @llvm.dbg.declare(metadata i8** %u16, metadata !1755, metadata !693), !dbg !1756
  call void @llvm.dbg.declare(metadata i64* %u16len, metadata !1757, metadata !693), !dbg !1758
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1759, metadata !693), !dbg !1760
  store i32 0, i32* %ret, align 4, !dbg !1760
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1761
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1762
  %1 = load i8*, i8** %format_data, align 8, !dbg !1762
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1763
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1764
  %3 = load %struct.file**, %struct.file*** %newfile.addr, align 8, !dbg !1765
  store %struct.file* null, %struct.file** %3, align 8, !dbg !1766
  %call = call noalias i8* @calloc(i64 1, i64 128) #8, !dbg !1767
  %4 = bitcast i8* %call to %struct.file*, !dbg !1767
  store %struct.file* %4, %struct.file** %file, align 8, !dbg !1768
  %5 = load %struct.file*, %struct.file** %file, align 8, !dbg !1769
  %cmp = icmp eq %struct.file* %5, null, !dbg !1771
  br i1 %cmp, label %if.then, label %if.end, !dbg !1772

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1773
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !1775
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.24, i32 0, i32 0)), !dbg !1776
  store i32 -30, i32* %retval, align 4, !dbg !1777
  br label %return, !dbg !1777

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1778
  %8 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1780
  %sconv = getelementptr inbounds %struct._7zip, %struct._7zip* %8, i32 0, i32 20, !dbg !1781
  %9 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1781
  %call2 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %7, i8** %u16, i64* %u16len, %struct.archive_string_conv* %9), !dbg !1782
  %cmp3 = icmp sgt i32 0, %call2, !dbg !1783
  br i1 %cmp3, label %if.then4, label %if.end11, !dbg !1784

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1785
  %10 = load i32, i32* %call5, align 4, !dbg !1785
  %cmp6 = icmp eq i32 %10, 12, !dbg !1788
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !1789

if.then7:                                         ; preds = %if.then4
  %11 = load %struct.file*, %struct.file** %file, align 8, !dbg !1790
  %12 = bitcast %struct.file* %11 to i8*, !dbg !1790
  call void @free(i8* %12) #8, !dbg !1792
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1793
  %archive8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 0, !dbg !1794
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive8, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.25, i32 0, i32 0)), !dbg !1795
  store i32 -30, i32* %retval, align 4, !dbg !1796
  br label %return, !dbg !1796

if.end9:                                          ; preds = %if.then4
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1797
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 0, !dbg !1798
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @.str.26, i32 0, i32 0)), !dbg !1799
  store i32 -20, i32* %ret, align 4, !dbg !1800
  br label %if.end11, !dbg !1801

if.end11:                                         ; preds = %if.end9, %if.end
  %15 = load i64, i64* %u16len, align 8, !dbg !1802
  %add = add i64 %15, 2, !dbg !1803
  %call12 = call noalias i8* @malloc(i64 %add) #8, !dbg !1804
  %16 = load %struct.file*, %struct.file** %file, align 8, !dbg !1805
  %utf16name = getelementptr inbounds %struct.file, %struct.file* %16, i32 0, i32 3, !dbg !1806
  store i8* %call12, i8** %utf16name, align 8, !dbg !1807
  %17 = load %struct.file*, %struct.file** %file, align 8, !dbg !1808
  %utf16name13 = getelementptr inbounds %struct.file, %struct.file* %17, i32 0, i32 3, !dbg !1810
  %18 = load i8*, i8** %utf16name13, align 8, !dbg !1810
  %cmp14 = icmp eq i8* %18, null, !dbg !1811
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !1812

if.then15:                                        ; preds = %if.end11
  %19 = load %struct.file*, %struct.file** %file, align 8, !dbg !1813
  %20 = bitcast %struct.file* %19 to i8*, !dbg !1813
  call void @free(i8* %20) #8, !dbg !1815
  %21 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1816
  %archive16 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 0, !dbg !1817
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.27, i32 0, i32 0)), !dbg !1818
  store i32 -30, i32* %retval, align 4, !dbg !1819
  br label %return, !dbg !1819

if.end17:                                         ; preds = %if.end11
  %22 = load %struct.file*, %struct.file** %file, align 8, !dbg !1820
  %utf16name18 = getelementptr inbounds %struct.file, %struct.file* %22, i32 0, i32 3, !dbg !1821
  %23 = load i8*, i8** %utf16name18, align 8, !dbg !1821
  %24 = load i8*, i8** %u16, align 8, !dbg !1822
  %25 = load i64, i64* %u16len, align 8, !dbg !1823
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %23, i8* %24, i64 %25, i32 1, i1 false), !dbg !1824
  %26 = load i64, i64* %u16len, align 8, !dbg !1825
  %add19 = add i64 %26, 0, !dbg !1826
  %27 = load %struct.file*, %struct.file** %file, align 8, !dbg !1827
  %utf16name20 = getelementptr inbounds %struct.file, %struct.file* %27, i32 0, i32 3, !dbg !1828
  %28 = load i8*, i8** %utf16name20, align 8, !dbg !1828
  %arrayidx = getelementptr inbounds i8, i8* %28, i64 %add19, !dbg !1827
  store i8 0, i8* %arrayidx, align 1, !dbg !1829
  %29 = load i64, i64* %u16len, align 8, !dbg !1830
  %add21 = add i64 %29, 1, !dbg !1831
  %30 = load %struct.file*, %struct.file** %file, align 8, !dbg !1832
  %utf16name22 = getelementptr inbounds %struct.file, %struct.file* %30, i32 0, i32 3, !dbg !1833
  %31 = load i8*, i8** %utf16name22, align 8, !dbg !1833
  %arrayidx23 = getelementptr inbounds i8, i8* %31, i64 %add21, !dbg !1832
  store i8 0, i8* %arrayidx23, align 1, !dbg !1834
  %32 = load i64, i64* %u16len, align 8, !dbg !1835
  %conv = trunc i64 %32 to i32, !dbg !1836
  %33 = load %struct.file*, %struct.file** %file, align 8, !dbg !1837
  %name_len = getelementptr inbounds %struct.file, %struct.file* %33, i32 0, i32 2, !dbg !1838
  store i32 %conv, i32* %name_len, align 8, !dbg !1839
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1840
  %call24 = call i32 @archive_entry_mode(%struct.archive_entry* %34), !dbg !1841
  %35 = load %struct.file*, %struct.file** %file, align 8, !dbg !1842
  %mode = getelementptr inbounds %struct.file, %struct.file* %35, i32 0, i32 7, !dbg !1843
  store i32 %call24, i32* %mode, align 8, !dbg !1844
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1845
  %call25 = call i32 @archive_entry_filetype(%struct.archive_entry* %36), !dbg !1847
  %cmp26 = icmp eq i32 %call25, 32768, !dbg !1848
  br i1 %cmp26, label %if.then28, label %if.else, !dbg !1849

if.then28:                                        ; preds = %if.end17
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1850
  %call29 = call i64 @archive_entry_size(%struct.archive_entry* %37), !dbg !1851
  %38 = load %struct.file*, %struct.file** %file, align 8, !dbg !1852
  %size = getelementptr inbounds %struct.file, %struct.file* %38, i32 0, i32 4, !dbg !1853
  store i64 %call29, i64* %size, align 8, !dbg !1854
  br label %if.end30, !dbg !1852

if.else:                                          ; preds = %if.end17
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1855
  call void @archive_entry_set_size(%struct.archive_entry* %39, i64 0), !dbg !1856
  br label %if.end30

if.end30:                                         ; preds = %if.else, %if.then28
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1857
  %call31 = call i32 @archive_entry_filetype(%struct.archive_entry* %40), !dbg !1859
  %cmp32 = icmp eq i32 %call31, 16384, !dbg !1860
  br i1 %cmp32, label %if.then34, label %if.else35, !dbg !1861

if.then34:                                        ; preds = %if.end30
  %41 = load %struct.file*, %struct.file** %file, align 8, !dbg !1862
  %dir = getelementptr inbounds %struct.file, %struct.file* %41, i32 0, i32 9, !dbg !1863
  %bf.load = load i8, i8* %dir, align 8, !dbg !1864
  %bf.clear = and i8 %bf.load, -2, !dbg !1864
  %bf.set = or i8 %bf.clear, 1, !dbg !1864
  store i8 %bf.set, i8* %dir, align 8, !dbg !1864
  br label %if.end44, !dbg !1862

if.else35:                                        ; preds = %if.end30
  %42 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1865
  %call36 = call i32 @archive_entry_filetype(%struct.archive_entry* %42), !dbg !1867
  %cmp37 = icmp eq i32 %call36, 40960, !dbg !1868
  br i1 %cmp37, label %if.then39, label %if.end43, !dbg !1869

if.then39:                                        ; preds = %if.else35
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1870
  %call40 = call i8* @archive_entry_symlink(%struct.archive_entry* %43), !dbg !1871
  %call41 = call i64 @strlen(i8* %call40) #9, !dbg !1872
  %44 = load %struct.file*, %struct.file** %file, align 8, !dbg !1874
  %size42 = getelementptr inbounds %struct.file, %struct.file* %44, i32 0, i32 4, !dbg !1875
  store i64 %call41, i64* %size42, align 8, !dbg !1876
  br label %if.end43, !dbg !1874

if.end43:                                         ; preds = %if.then39, %if.else35
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then34
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1877
  %call45 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %45), !dbg !1879
  %tobool = icmp ne i32 %call45, 0, !dbg !1879
  br i1 %tobool, label %if.then46, label %if.end52, !dbg !1880

if.then46:                                        ; preds = %if.end44
  %46 = load %struct.file*, %struct.file** %file, align 8, !dbg !1881
  %flg = getelementptr inbounds %struct.file, %struct.file* %46, i32 0, i32 5, !dbg !1883
  %47 = load i32, i32* %flg, align 8, !dbg !1884
  %or = or i32 %47, 1, !dbg !1884
  store i32 %or, i32* %flg, align 8, !dbg !1884
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1885
  %call47 = call i64 @archive_entry_mtime(%struct.archive_entry* %48), !dbg !1886
  %49 = load %struct.file*, %struct.file** %file, align 8, !dbg !1887
  %times = getelementptr inbounds %struct.file, %struct.file* %49, i32 0, i32 6, !dbg !1888
  %arrayidx48 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times, i64 0, i64 0, !dbg !1887
  %time = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx48, i32 0, i32 0, !dbg !1889
  store i64 %call47, i64* %time, align 8, !dbg !1890
  %50 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1891
  %call49 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %50), !dbg !1892
  %51 = load %struct.file*, %struct.file** %file, align 8, !dbg !1893
  %times50 = getelementptr inbounds %struct.file, %struct.file* %51, i32 0, i32 6, !dbg !1894
  %arrayidx51 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times50, i64 0, i64 0, !dbg !1893
  %time_ns = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx51, i32 0, i32 1, !dbg !1895
  store i64 %call49, i64* %time_ns, align 8, !dbg !1896
  br label %if.end52, !dbg !1897

if.end52:                                         ; preds = %if.then46, %if.end44
  %52 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1898
  %call53 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %52), !dbg !1900
  %tobool54 = icmp ne i32 %call53, 0, !dbg !1900
  br i1 %tobool54, label %if.then55, label %if.end66, !dbg !1901

if.then55:                                        ; preds = %if.end52
  %53 = load %struct.file*, %struct.file** %file, align 8, !dbg !1902
  %flg56 = getelementptr inbounds %struct.file, %struct.file* %53, i32 0, i32 5, !dbg !1904
  %54 = load i32, i32* %flg56, align 8, !dbg !1905
  %or57 = or i32 %54, 2, !dbg !1905
  store i32 %or57, i32* %flg56, align 8, !dbg !1905
  %55 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1906
  %call58 = call i64 @archive_entry_atime(%struct.archive_entry* %55), !dbg !1907
  %56 = load %struct.file*, %struct.file** %file, align 8, !dbg !1908
  %times59 = getelementptr inbounds %struct.file, %struct.file* %56, i32 0, i32 6, !dbg !1909
  %arrayidx60 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times59, i64 0, i64 1, !dbg !1908
  %time61 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx60, i32 0, i32 0, !dbg !1910
  store i64 %call58, i64* %time61, align 8, !dbg !1911
  %57 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1912
  %call62 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %57), !dbg !1913
  %58 = load %struct.file*, %struct.file** %file, align 8, !dbg !1914
  %times63 = getelementptr inbounds %struct.file, %struct.file* %58, i32 0, i32 6, !dbg !1915
  %arrayidx64 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times63, i64 0, i64 1, !dbg !1914
  %time_ns65 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx64, i32 0, i32 1, !dbg !1916
  store i64 %call62, i64* %time_ns65, align 8, !dbg !1917
  br label %if.end66, !dbg !1918

if.end66:                                         ; preds = %if.then55, %if.end52
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1919
  %call67 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %59), !dbg !1921
  %tobool68 = icmp ne i32 %call67, 0, !dbg !1921
  br i1 %tobool68, label %if.then69, label %if.end80, !dbg !1922

if.then69:                                        ; preds = %if.end66
  %60 = load %struct.file*, %struct.file** %file, align 8, !dbg !1923
  %flg70 = getelementptr inbounds %struct.file, %struct.file* %60, i32 0, i32 5, !dbg !1925
  %61 = load i32, i32* %flg70, align 8, !dbg !1926
  %or71 = or i32 %61, 4, !dbg !1926
  store i32 %or71, i32* %flg70, align 8, !dbg !1926
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1927
  %call72 = call i64 @archive_entry_ctime(%struct.archive_entry* %62), !dbg !1928
  %63 = load %struct.file*, %struct.file** %file, align 8, !dbg !1929
  %times73 = getelementptr inbounds %struct.file, %struct.file* %63, i32 0, i32 6, !dbg !1930
  %arrayidx74 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times73, i64 0, i64 2, !dbg !1929
  %time75 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx74, i32 0, i32 0, !dbg !1931
  store i64 %call72, i64* %time75, align 8, !dbg !1932
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1933
  %call76 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %64), !dbg !1934
  %65 = load %struct.file*, %struct.file** %file, align 8, !dbg !1935
  %times77 = getelementptr inbounds %struct.file, %struct.file* %65, i32 0, i32 6, !dbg !1936
  %arrayidx78 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times77, i64 0, i64 2, !dbg !1935
  %time_ns79 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx78, i32 0, i32 1, !dbg !1937
  store i64 %call76, i64* %time_ns79, align 8, !dbg !1938
  br label %if.end80, !dbg !1939

if.end80:                                         ; preds = %if.then69, %if.end66
  %66 = load %struct.file*, %struct.file** %file, align 8, !dbg !1940
  %67 = load %struct.file**, %struct.file*** %newfile.addr, align 8, !dbg !1941
  store %struct.file* %66, %struct.file** %67, align 8, !dbg !1942
  %68 = load i32, i32* %ret, align 4, !dbg !1943
  store i32 %68, i32* %retval, align 4, !dbg !1944
  br label %return, !dbg !1944

return:                                           ; preds = %if.end80, %if.then15, %if.then7, %if.then
  %69 = load i32, i32* %retval, align 4, !dbg !1945
  ret i32 %69, !dbg !1945
}

; Function Attrs: nounwind uwtable
define internal void @file_free(%struct.file* %file) #0 !dbg !587 {
entry:
  %file.addr = alloca %struct.file*, align 8
  store %struct.file* %file, %struct.file** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.file** %file.addr, metadata !1946, metadata !693), !dbg !1947
  %0 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !1948
  %utf16name = getelementptr inbounds %struct.file, %struct.file* %0, i32 0, i32 3, !dbg !1949
  %1 = load i8*, i8** %utf16name, align 8, !dbg !1949
  call void @free(i8* %1) #8, !dbg !1950
  %2 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !1951
  %3 = bitcast %struct.file* %2 to i8*, !dbg !1951
  call void @free(i8* %3) #8, !dbg !1952
  ret void, !dbg !1953
}

declare i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree*, %struct.archive_rb_node*) #2

; Function Attrs: nounwind uwtable
define internal void @file_register_empty(%struct._7zip* %zip, %struct.file* %file) #0 !dbg !590 {
entry:
  %zip.addr = alloca %struct._7zip*, align 8
  %file.addr = alloca %struct.file*, align 8
  store %struct._7zip* %zip, %struct._7zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip.addr, metadata !1954, metadata !693), !dbg !1955
  store %struct.file* %file, %struct.file** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.file** %file.addr, metadata !1956, metadata !693), !dbg !1957
  %0 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !1958
  %next = getelementptr inbounds %struct.file, %struct.file* %0, i32 0, i32 1, !dbg !1959
  store %struct.file* null, %struct.file** %next, align 8, !dbg !1960
  %1 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !1961
  %2 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !1962
  %empty_list = getelementptr inbounds %struct._7zip, %struct._7zip* %2, i32 0, i32 24, !dbg !1963
  %last = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list, i32 0, i32 1, !dbg !1964
  %3 = load %struct.file**, %struct.file*** %last, align 8, !dbg !1964
  store %struct.file* %1, %struct.file** %3, align 8, !dbg !1965
  %4 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !1966
  %next1 = getelementptr inbounds %struct.file, %struct.file* %4, i32 0, i32 1, !dbg !1967
  %5 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !1968
  %empty_list2 = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 24, !dbg !1969
  %last3 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %empty_list2, i32 0, i32 1, !dbg !1970
  store %struct.file** %next1, %struct.file*** %last3, align 8, !dbg !1971
  ret void, !dbg !1972
}

; Function Attrs: nounwind uwtable
define internal i32 @_7z_compression_init_encoder(%struct.archive_write* %a, i32 %compression, i32 %compression_level) #0 !dbg !593 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %compression.addr = alloca i32, align 4
  %compression_level.addr = alloca i32, align 4
  %zip = alloca %struct._7zip*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1973, metadata !693), !dbg !1974
  store i32 %compression, i32* %compression.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %compression.addr, metadata !1975, metadata !693), !dbg !1976
  store i32 %compression_level, i32* %compression_level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %compression_level.addr, metadata !1977, metadata !693), !dbg !1978
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !1979, metadata !693), !dbg !1980
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1981, metadata !693), !dbg !1982
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1983
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1984
  %1 = load i8*, i8** %format_data, align 8, !dbg !1984
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !1985
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !1986
  %3 = load i32, i32* %compression.addr, align 4, !dbg !1987
  switch i32 %3, label %sw.default [
    i32 262408, label %sw.bb
    i32 262658, label %sw.bb1
    i32 196865, label %sw.bb5
    i32 33, label %sw.bb9
    i32 197633, label %sw.bb13
    i32 0, label %sw.bb17
  ], !dbg !1988

sw.bb:                                            ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1989
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !1991
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !1992
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 18, !dbg !1993
  %6 = load i32, i32* %compression_level.addr, align 4, !dbg !1994
  %call = call i32 @compression_init_encoder_deflate(%struct.archive* %archive, %struct.la_zstream* %stream, i32 %6, i32 0), !dbg !1995
  store i32 %call, i32* %r, align 4, !dbg !1996
  br label %sw.epilog, !dbg !1997

sw.bb1:                                           ; preds = %entry
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1998
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !1999
  %8 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2000
  %stream3 = getelementptr inbounds %struct._7zip, %struct._7zip* %8, i32 0, i32 18, !dbg !2001
  %9 = load i32, i32* %compression_level.addr, align 4, !dbg !2002
  %call4 = call i32 @compression_init_encoder_bzip2(%struct.archive* %archive2, %struct.la_zstream* %stream3, i32 %9), !dbg !2003
  store i32 %call4, i32* %r, align 4, !dbg !2004
  br label %sw.epilog, !dbg !2005

sw.bb5:                                           ; preds = %entry
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2006
  %archive6 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !2007
  %11 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2008
  %stream7 = getelementptr inbounds %struct._7zip, %struct._7zip* %11, i32 0, i32 18, !dbg !2009
  %12 = load i32, i32* %compression_level.addr, align 4, !dbg !2010
  %call8 = call i32 @compression_init_encoder_lzma1(%struct.archive* %archive6, %struct.la_zstream* %stream7, i32 %12), !dbg !2011
  store i32 %call8, i32* %r, align 4, !dbg !2012
  br label %sw.epilog, !dbg !2013

sw.bb9:                                           ; preds = %entry
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2014
  %archive10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 0, !dbg !2015
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2016
  %stream11 = getelementptr inbounds %struct._7zip, %struct._7zip* %14, i32 0, i32 18, !dbg !2017
  %15 = load i32, i32* %compression_level.addr, align 4, !dbg !2018
  %call12 = call i32 @compression_init_encoder_lzma2(%struct.archive* %archive10, %struct.la_zstream* %stream11, i32 %15), !dbg !2019
  store i32 %call12, i32* %r, align 4, !dbg !2020
  br label %sw.epilog, !dbg !2021

sw.bb13:                                          ; preds = %entry
  %16 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2022
  %archive14 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 0, !dbg !2023
  %17 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2024
  %stream15 = getelementptr inbounds %struct._7zip, %struct._7zip* %17, i32 0, i32 18, !dbg !2025
  %call16 = call i32 @compression_init_encoder_ppmd(%struct.archive* %archive14, %struct.la_zstream* %stream15, i32 6, i32 16777216), !dbg !2026
  store i32 %call16, i32* %r, align 4, !dbg !2027
  br label %sw.epilog, !dbg !2028

sw.bb17:                                          ; preds = %entry
  br label %sw.default, !dbg !2029

sw.default:                                       ; preds = %entry, %sw.bb17
  %18 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2031
  %archive18 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 0, !dbg !2032
  %19 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2033
  %stream19 = getelementptr inbounds %struct._7zip, %struct._7zip* %19, i32 0, i32 18, !dbg !2034
  %call20 = call i32 @compression_init_encoder_copy(%struct.archive* %archive18, %struct.la_zstream* %stream19), !dbg !2035
  store i32 %call20, i32* %r, align 4, !dbg !2036
  br label %sw.epilog, !dbg !2037

sw.epilog:                                        ; preds = %sw.default, %sw.bb13, %sw.bb9, %sw.bb5, %sw.bb1, %sw.bb
  %20 = load i32, i32* %r, align 4, !dbg !2038
  %cmp = icmp eq i32 %20, 0, !dbg !2040
  br i1 %cmp, label %if.then, label %if.end, !dbg !2041

if.then:                                          ; preds = %sw.epilog
  %21 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2042
  %stream21 = getelementptr inbounds %struct._7zip, %struct._7zip* %21, i32 0, i32 18, !dbg !2044
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream21, i32 0, i32 2, !dbg !2045
  store i64 0, i64* %total_in, align 8, !dbg !2046
  %22 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2047
  %wbuff = getelementptr inbounds %struct._7zip, %struct._7zip* %22, i32 0, i32 21, !dbg !2048
  %arraydecay = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff, i32 0, i32 0, !dbg !2047
  %23 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2049
  %stream22 = getelementptr inbounds %struct._7zip, %struct._7zip* %23, i32 0, i32 18, !dbg !2050
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream22, i32 0, i32 3, !dbg !2051
  store i8* %arraydecay, i8** %next_out, align 8, !dbg !2052
  %24 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2053
  %stream23 = getelementptr inbounds %struct._7zip, %struct._7zip* %24, i32 0, i32 18, !dbg !2054
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream23, i32 0, i32 4, !dbg !2055
  store i64 61440, i64* %avail_out, align 8, !dbg !2056
  %25 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2057
  %stream24 = getelementptr inbounds %struct._7zip, %struct._7zip* %25, i32 0, i32 18, !dbg !2058
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream24, i32 0, i32 5, !dbg !2059
  store i64 0, i64* %total_out, align 8, !dbg !2060
  br label %if.end, !dbg !2061

if.end:                                           ; preds = %if.then, %sw.epilog
  %26 = load i32, i32* %r, align 4, !dbg !2062
  ret i32 %26, !dbg !2063
}

; Function Attrs: nounwind uwtable
define internal void @file_register(%struct._7zip* %zip, %struct.file* %file) #0 !dbg !631 {
entry:
  %zip.addr = alloca %struct._7zip*, align 8
  %file.addr = alloca %struct.file*, align 8
  store %struct._7zip* %zip, %struct._7zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip.addr, metadata !2064, metadata !693), !dbg !2065
  store %struct.file* %file, %struct.file** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.file** %file.addr, metadata !2066, metadata !693), !dbg !2067
  %0 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !2068
  %next = getelementptr inbounds %struct.file, %struct.file* %0, i32 0, i32 1, !dbg !2069
  store %struct.file* null, %struct.file** %next, align 8, !dbg !2070
  %1 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !2071
  %2 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !2072
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %2, i32 0, i32 23, !dbg !2073
  %last = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 1, !dbg !2074
  %3 = load %struct.file**, %struct.file*** %last, align 8, !dbg !2074
  store %struct.file* %1, %struct.file** %3, align 8, !dbg !2075
  %4 = load %struct.file*, %struct.file** %file.addr, align 8, !dbg !2076
  %next1 = getelementptr inbounds %struct.file, %struct.file* %4, i32 0, i32 1, !dbg !2077
  %5 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !2078
  %file_list2 = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 23, !dbg !2079
  %last3 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list2, i32 0, i32 1, !dbg !2080
  store %struct.file** %next1, %struct.file*** %last3, align 8, !dbg !2081
  ret void, !dbg !2082
}

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i64 @compress_out(%struct.archive_write* %a, i8* %buff, i64 %s, i32 %run) #0 !dbg !632 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %run.addr = alloca i32, align 4
  %zip = alloca %struct._7zip*, align 8
  %r = alloca i32, align 4
  %bytes = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2083, metadata !693), !dbg !2084
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !2085, metadata !693), !dbg !2086
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !2087, metadata !693), !dbg !2088
  store i32 %run, i32* %run.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %run.addr, metadata !2089, metadata !693), !dbg !2090
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !2091, metadata !693), !dbg !2092
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2093
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2094
  %1 = load i8*, i8** %format_data, align 8, !dbg !2094
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !2095
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !2092
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2096, metadata !693), !dbg !2097
  %3 = load i32, i32* %run.addr, align 4, !dbg !2098
  %cmp = icmp eq i32 %3, 0, !dbg !2100
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2101

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2102
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %4, i32 0, i32 18, !dbg !2104
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream, i32 0, i32 2, !dbg !2105
  %5 = load i64, i64* %total_in, align 8, !dbg !2105
  %cmp1 = icmp eq i64 %5, 0, !dbg !2106
  br i1 %cmp1, label %land.lhs.true2, label %if.end, !dbg !2107

land.lhs.true2:                                   ; preds = %land.lhs.true
  %6 = load i64, i64* %s.addr, align 8, !dbg !2108
  %cmp3 = icmp eq i64 %6, 0, !dbg !2110
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2111

if.then:                                          ; preds = %land.lhs.true2
  store i64 0, i64* %retval, align 8, !dbg !2112
  br label %return, !dbg !2112

if.end:                                           ; preds = %land.lhs.true2, %land.lhs.true, %entry
  %7 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2113
  %crc32flg = getelementptr inbounds %struct._7zip, %struct._7zip* %7, i32 0, i32 15, !dbg !2115
  %8 = load i32, i32* %crc32flg, align 4, !dbg !2115
  %and = and i32 %8, 1, !dbg !2116
  %tobool = icmp ne i32 %and, 0, !dbg !2116
  br i1 %tobool, label %land.lhs.true4, label %if.end10, !dbg !2117

land.lhs.true4:                                   ; preds = %if.end
  %9 = load i64, i64* %s.addr, align 8, !dbg !2118
  %tobool5 = icmp ne i64 %9, 0, !dbg !2118
  br i1 %tobool5, label %if.then6, label %if.end10, !dbg !2120

if.then6:                                         ; preds = %land.lhs.true4
  %10 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2121
  %precode_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %10, i32 0, i32 13, !dbg !2122
  %11 = load i32, i32* %precode_crc32, align 4, !dbg !2122
  %conv = zext i32 %11 to i64, !dbg !2121
  %12 = load i8*, i8** %buff.addr, align 8, !dbg !2123
  %13 = load i64, i64* %s.addr, align 8, !dbg !2124
  %conv7 = trunc i64 %13 to i32, !dbg !2125
  %call = call i64 @cm_zlib_crc32(i64 %conv, i8* %12, i32 %conv7), !dbg !2126
  %conv8 = trunc i64 %call to i32, !dbg !2126
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2127
  %precode_crc329 = getelementptr inbounds %struct._7zip, %struct._7zip* %14, i32 0, i32 13, !dbg !2128
  store i32 %conv8, i32* %precode_crc329, align 4, !dbg !2129
  br label %if.end10, !dbg !2127

if.end10:                                         ; preds = %if.then6, %land.lhs.true4, %if.end
  %15 = load i8*, i8** %buff.addr, align 8, !dbg !2130
  %16 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2131
  %stream11 = getelementptr inbounds %struct._7zip, %struct._7zip* %16, i32 0, i32 18, !dbg !2132
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream11, i32 0, i32 0, !dbg !2133
  store i8* %15, i8** %next_in, align 8, !dbg !2134
  %17 = load i64, i64* %s.addr, align 8, !dbg !2135
  %18 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2136
  %stream12 = getelementptr inbounds %struct._7zip, %struct._7zip* %18, i32 0, i32 18, !dbg !2137
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream12, i32 0, i32 1, !dbg !2138
  store i64 %17, i64* %avail_in, align 8, !dbg !2139
  br label %for.cond, !dbg !2140

for.cond:                                         ; preds = %if.end60, %if.then52, %if.end10
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2141
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !2145
  %20 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2146
  %stream13 = getelementptr inbounds %struct._7zip, %struct._7zip* %20, i32 0, i32 18, !dbg !2147
  %21 = load i32, i32* %run.addr, align 4, !dbg !2148
  %call14 = call i32 @compression_code(%struct.archive* %archive, %struct.la_zstream* %stream13, i32 %21), !dbg !2149
  store i32 %call14, i32* %r, align 4, !dbg !2150
  %22 = load i32, i32* %r, align 4, !dbg !2151
  %cmp15 = icmp ne i32 %22, 0, !dbg !2153
  br i1 %cmp15, label %land.lhs.true17, label %if.end21, !dbg !2154

land.lhs.true17:                                  ; preds = %for.cond
  %23 = load i32, i32* %r, align 4, !dbg !2155
  %cmp18 = icmp ne i32 %23, 1, !dbg !2157
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !2158

if.then20:                                        ; preds = %land.lhs.true17
  store i64 -30, i64* %retval, align 8, !dbg !2159
  br label %return, !dbg !2159

if.end21:                                         ; preds = %land.lhs.true17, %for.cond
  %24 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2160
  %stream22 = getelementptr inbounds %struct._7zip, %struct._7zip* %24, i32 0, i32 18, !dbg !2162
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream22, i32 0, i32 4, !dbg !2163
  %25 = load i64, i64* %avail_out, align 8, !dbg !2163
  %cmp23 = icmp eq i64 %25, 0, !dbg !2164
  br i1 %cmp23, label %if.then25, label %if.end54, !dbg !2165

if.then25:                                        ; preds = %if.end21
  %26 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2166
  %27 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2169
  %wbuff = getelementptr inbounds %struct._7zip, %struct._7zip* %27, i32 0, i32 21, !dbg !2170
  %arraydecay = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff, i32 0, i32 0, !dbg !2169
  %call26 = call i32 @write_to_temp(%struct.archive_write* %26, i8* %arraydecay, i64 61440), !dbg !2171
  %cmp27 = icmp ne i32 %call26, 0, !dbg !2172
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !2173

if.then29:                                        ; preds = %if.then25
  store i64 -30, i64* %retval, align 8, !dbg !2174
  br label %return, !dbg !2174

if.end30:                                         ; preds = %if.then25
  %28 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2175
  %wbuff31 = getelementptr inbounds %struct._7zip, %struct._7zip* %28, i32 0, i32 21, !dbg !2176
  %arraydecay32 = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff31, i32 0, i32 0, !dbg !2175
  %29 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2177
  %stream33 = getelementptr inbounds %struct._7zip, %struct._7zip* %29, i32 0, i32 18, !dbg !2178
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream33, i32 0, i32 3, !dbg !2179
  store i8* %arraydecay32, i8** %next_out, align 8, !dbg !2180
  %30 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2181
  %stream34 = getelementptr inbounds %struct._7zip, %struct._7zip* %30, i32 0, i32 18, !dbg !2182
  %avail_out35 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream34, i32 0, i32 4, !dbg !2183
  store i64 61440, i64* %avail_out35, align 8, !dbg !2184
  %31 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2185
  %crc32flg36 = getelementptr inbounds %struct._7zip, %struct._7zip* %31, i32 0, i32 15, !dbg !2187
  %32 = load i32, i32* %crc32flg36, align 4, !dbg !2187
  %and37 = and i32 %32, 2, !dbg !2188
  %tobool38 = icmp ne i32 %and37, 0, !dbg !2188
  br i1 %tobool38, label %if.then39, label %if.end46, !dbg !2189

if.then39:                                        ; preds = %if.end30
  %33 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2190
  %encoded_crc32 = getelementptr inbounds %struct._7zip, %struct._7zip* %33, i32 0, i32 14, !dbg !2191
  %34 = load i32, i32* %encoded_crc32, align 8, !dbg !2191
  %conv40 = zext i32 %34 to i64, !dbg !2190
  %35 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2192
  %wbuff41 = getelementptr inbounds %struct._7zip, %struct._7zip* %35, i32 0, i32 21, !dbg !2193
  %arraydecay42 = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff41, i32 0, i32 0, !dbg !2192
  %call43 = call i64 @cm_zlib_crc32(i64 %conv40, i8* %arraydecay42, i32 61440), !dbg !2194
  %conv44 = trunc i64 %call43 to i32, !dbg !2194
  %36 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2195
  %encoded_crc3245 = getelementptr inbounds %struct._7zip, %struct._7zip* %36, i32 0, i32 14, !dbg !2196
  store i32 %conv44, i32* %encoded_crc3245, align 8, !dbg !2197
  br label %if.end46, !dbg !2195

if.end46:                                         ; preds = %if.then39, %if.end30
  %37 = load i32, i32* %run.addr, align 4, !dbg !2198
  %cmp47 = icmp eq i32 %37, 0, !dbg !2200
  br i1 %cmp47, label %land.lhs.true49, label %if.end53, !dbg !2201

land.lhs.true49:                                  ; preds = %if.end46
  %38 = load i32, i32* %r, align 4, !dbg !2202
  %cmp50 = icmp ne i32 %38, 1, !dbg !2204
  br i1 %cmp50, label %if.then52, label %if.end53, !dbg !2205

if.then52:                                        ; preds = %land.lhs.true49
  br label %for.cond, !dbg !2206

if.end53:                                         ; preds = %land.lhs.true49, %if.end46
  br label %if.end54, !dbg !2207

if.end54:                                         ; preds = %if.end53, %if.end21
  %39 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2208
  %stream55 = getelementptr inbounds %struct._7zip, %struct._7zip* %39, i32 0, i32 18, !dbg !2210
  %avail_in56 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream55, i32 0, i32 1, !dbg !2211
  %40 = load i64, i64* %avail_in56, align 8, !dbg !2211
  %cmp57 = icmp eq i64 %40, 0, !dbg !2212
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !2213

if.then59:                                        ; preds = %if.end54
  br label %for.end, !dbg !2214

if.end60:                                         ; preds = %if.end54
  br label %for.cond, !dbg !2215

for.end:                                          ; preds = %if.then59
  %41 = load i32, i32* %run.addr, align 4, !dbg !2217
  %cmp61 = icmp eq i32 %41, 0, !dbg !2219
  br i1 %cmp61, label %if.then63, label %if.end88, !dbg !2220

if.then63:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !2221, metadata !693), !dbg !2223
  %42 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2224
  %stream64 = getelementptr inbounds %struct._7zip, %struct._7zip* %42, i32 0, i32 18, !dbg !2225
  %avail_out65 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %stream64, i32 0, i32 4, !dbg !2226
  %43 = load i64, i64* %avail_out65, align 8, !dbg !2226
  %sub = sub i64 61440, %43, !dbg !2227
  store i64 %sub, i64* %bytes, align 8, !dbg !2223
  %44 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2228
  %45 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2230
  %wbuff66 = getelementptr inbounds %struct._7zip, %struct._7zip* %45, i32 0, i32 21, !dbg !2231
  %arraydecay67 = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff66, i32 0, i32 0, !dbg !2230
  %46 = load i64, i64* %bytes, align 8, !dbg !2232
  %call68 = call i32 @write_to_temp(%struct.archive_write* %44, i8* %arraydecay67, i64 %46), !dbg !2233
  %cmp69 = icmp ne i32 %call68, 0, !dbg !2234
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !2235

if.then71:                                        ; preds = %if.then63
  store i64 -30, i64* %retval, align 8, !dbg !2236
  br label %return, !dbg !2236

if.end72:                                         ; preds = %if.then63
  %47 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2237
  %crc32flg73 = getelementptr inbounds %struct._7zip, %struct._7zip* %47, i32 0, i32 15, !dbg !2239
  %48 = load i32, i32* %crc32flg73, align 4, !dbg !2239
  %and74 = and i32 %48, 2, !dbg !2240
  %tobool75 = icmp ne i32 %and74, 0, !dbg !2240
  br i1 %tobool75, label %land.lhs.true76, label %if.end87, !dbg !2241

land.lhs.true76:                                  ; preds = %if.end72
  %49 = load i64, i64* %bytes, align 8, !dbg !2242
  %tobool77 = icmp ne i64 %49, 0, !dbg !2242
  br i1 %tobool77, label %if.then78, label %if.end87, !dbg !2244

if.then78:                                        ; preds = %land.lhs.true76
  %50 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2245
  %encoded_crc3279 = getelementptr inbounds %struct._7zip, %struct._7zip* %50, i32 0, i32 14, !dbg !2246
  %51 = load i32, i32* %encoded_crc3279, align 8, !dbg !2246
  %conv80 = zext i32 %51 to i64, !dbg !2245
  %52 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2247
  %wbuff81 = getelementptr inbounds %struct._7zip, %struct._7zip* %52, i32 0, i32 21, !dbg !2248
  %arraydecay82 = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff81, i32 0, i32 0, !dbg !2247
  %53 = load i64, i64* %bytes, align 8, !dbg !2249
  %conv83 = trunc i64 %53 to i32, !dbg !2250
  %call84 = call i64 @cm_zlib_crc32(i64 %conv80, i8* %arraydecay82, i32 %conv83), !dbg !2251
  %conv85 = trunc i64 %call84 to i32, !dbg !2251
  %54 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !2252
  %encoded_crc3286 = getelementptr inbounds %struct._7zip, %struct._7zip* %54, i32 0, i32 14, !dbg !2253
  store i32 %conv85, i32* %encoded_crc3286, align 8, !dbg !2254
  br label %if.end87, !dbg !2252

if.end87:                                         ; preds = %if.then78, %land.lhs.true76, %if.end72
  br label %if.end88, !dbg !2255

if.end88:                                         ; preds = %if.end87, %for.end
  %55 = load i64, i64* %s.addr, align 8, !dbg !2256
  store i64 %55, i64* %retval, align 8, !dbg !2257
  br label %return, !dbg !2257

return:                                           ; preds = %if.end88, %if.then71, %if.then29, %if.then20, %if.then
  %56 = load i64, i64* %retval, align 8, !dbg !2258
  ret i64 %56, !dbg !2258
}

declare i64 @cm_zlib_crc32(i64, i8*, i32) #2

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @archive_entry_mtime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #2

declare i32 @archive_entry_atime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_atime(%struct.archive_entry*) #2

declare i64 @archive_entry_atime_nsec(%struct.archive_entry*) #2

declare i32 @archive_entry_ctime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime_nsec(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_deflate(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %level, i32 %withheader) #0 !dbg !596 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %level.addr = alloca i32, align 4
  %withheader.addr = alloca i32, align 4
  %strm = alloca %struct.z_stream_s*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2259, metadata !693), !dbg !2260
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2261, metadata !693), !dbg !2262
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !2263, metadata !693), !dbg !2264
  store i32 %withheader, i32* %withheader.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %withheader.addr, metadata !2265, metadata !693), !dbg !2266
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm, metadata !2267, metadata !693), !dbg !2268
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2269
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !2271
  %1 = load i32, i32* %valid, align 8, !dbg !2271
  %tobool = icmp ne i32 %1, 0, !dbg !2269
  br i1 %tobool, label %if.then, label %if.end, !dbg !2272

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2273
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2274
  %call = call i32 @compression_end(%struct.archive* %2, %struct.la_zstream* %3), !dbg !2275
  br label %if.end, !dbg !2275

if.end:                                           ; preds = %if.then, %entry
  %call1 = call noalias i8* @calloc(i64 1, i64 112) #8, !dbg !2276
  %4 = bitcast i8* %call1 to %struct.z_stream_s*, !dbg !2276
  store %struct.z_stream_s* %4, %struct.z_stream_s** %strm, align 8, !dbg !2277
  %5 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2278
  %cmp = icmp eq %struct.z_stream_s* %5, null, !dbg !2280
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !2281

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2282
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 12, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.28, i32 0, i32 0)), !dbg !2284
  store i32 -30, i32* %retval, align 4, !dbg !2285
  br label %return, !dbg !2285

if.end3:                                          ; preds = %if.end
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2286
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 0, !dbg !2287
  %8 = load i8*, i8** %next_in, align 8, !dbg !2287
  %9 = ptrtoint i8* %8 to i64, !dbg !2288
  %10 = inttoptr i64 %9 to i8*, !dbg !2289
  %11 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2290
  %next_in4 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %11, i32 0, i32 0, !dbg !2291
  store i8* %10, i8** %next_in4, align 8, !dbg !2292
  %12 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2293
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %12, i32 0, i32 1, !dbg !2294
  %13 = load i64, i64* %avail_in, align 8, !dbg !2294
  %conv = trunc i64 %13 to i32, !dbg !2295
  %14 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2296
  %avail_in5 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %14, i32 0, i32 1, !dbg !2297
  store i32 %conv, i32* %avail_in5, align 8, !dbg !2298
  %15 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2299
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %15, i32 0, i32 2, !dbg !2300
  %16 = load i64, i64* %total_in, align 8, !dbg !2300
  %17 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2301
  %total_in6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %17, i32 0, i32 2, !dbg !2302
  store i64 %16, i64* %total_in6, align 8, !dbg !2303
  %18 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2304
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %18, i32 0, i32 3, !dbg !2305
  %19 = load i8*, i8** %next_out, align 8, !dbg !2305
  %20 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2306
  %next_out7 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %20, i32 0, i32 3, !dbg !2307
  store i8* %19, i8** %next_out7, align 8, !dbg !2308
  %21 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2309
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %21, i32 0, i32 4, !dbg !2310
  %22 = load i64, i64* %avail_out, align 8, !dbg !2310
  %conv8 = trunc i64 %22 to i32, !dbg !2311
  %23 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2312
  %avail_out9 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %23, i32 0, i32 4, !dbg !2313
  store i32 %conv8, i32* %avail_out9, align 8, !dbg !2314
  %24 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2315
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %24, i32 0, i32 5, !dbg !2316
  %25 = load i64, i64* %total_out, align 8, !dbg !2316
  %26 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2317
  %total_out10 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %26, i32 0, i32 5, !dbg !2318
  store i64 %25, i64* %total_out10, align 8, !dbg !2319
  %27 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2320
  %28 = load i32, i32* %level.addr, align 4, !dbg !2320
  %29 = load i32, i32* %withheader.addr, align 4, !dbg !2320
  %tobool11 = icmp ne i32 %29, 0, !dbg !2320
  %cond = select i1 %tobool11, i32 15, i32 -15, !dbg !2320
  %call12 = call i32 @cm_zlib_deflateInit2_(%struct.z_stream_s* %27, i32 %28, i32 8, i32 %cond, i32 8, i32 0, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i32 0, i32 0), i32 112), !dbg !2320
  %cmp13 = icmp ne i32 %call12, 0, !dbg !2322
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !2323

if.then15:                                        ; preds = %if.end3
  %30 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2324
  %31 = bitcast %struct.z_stream_s* %30 to i8*, !dbg !2324
  call void @free(i8* %31) #8, !dbg !2326
  %32 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2327
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %32, i32 0, i32 9, !dbg !2328
  store i8* null, i8** %real_stream, align 8, !dbg !2329
  %33 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2330
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %33, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.30, i32 0, i32 0)), !dbg !2331
  store i32 -30, i32* %retval, align 4, !dbg !2332
  br label %return, !dbg !2332

if.end16:                                         ; preds = %if.end3
  %34 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2333
  %35 = bitcast %struct.z_stream_s* %34 to i8*, !dbg !2333
  %36 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2334
  %real_stream17 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %36, i32 0, i32 9, !dbg !2335
  store i8* %35, i8** %real_stream17, align 8, !dbg !2336
  %37 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2337
  %valid18 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %37, i32 0, i32 8, !dbg !2338
  store i32 1, i32* %valid18, align 8, !dbg !2339
  %38 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2340
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %38, i32 0, i32 10, !dbg !2341
  store i32 (%struct.archive*, %struct.la_zstream*, i32)* @compression_code_deflate, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !2342
  %39 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2343
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %39, i32 0, i32 11, !dbg !2344
  store i32 (%struct.archive*, %struct.la_zstream*)* @compression_end_deflate, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !2345
  store i32 0, i32* %retval, align 4, !dbg !2346
  br label %return, !dbg !2346

return:                                           ; preds = %if.end16, %if.then15, %if.then2
  %40 = load i32, i32* %retval, align 4, !dbg !2347
  ret i32 %40, !dbg !2347
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_bzip2(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %level) #0 !dbg !602 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %level.addr = alloca i32, align 4
  %strm = alloca %struct.bz_stream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2348, metadata !693), !dbg !2349
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2350, metadata !693), !dbg !2351
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !2352, metadata !693), !dbg !2353
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm, metadata !2354, metadata !693), !dbg !2355
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2356
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !2358
  %1 = load i32, i32* %valid, align 8, !dbg !2358
  %tobool = icmp ne i32 %1, 0, !dbg !2356
  br i1 %tobool, label %if.then, label %if.end, !dbg !2359

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2360
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2361
  %call = call i32 @compression_end(%struct.archive* %2, %struct.la_zstream* %3), !dbg !2362
  br label %if.end, !dbg !2362

if.end:                                           ; preds = %if.then, %entry
  %call1 = call noalias i8* @calloc(i64 1, i64 80) #8, !dbg !2363
  %4 = bitcast i8* %call1 to %struct.bz_stream*, !dbg !2363
  store %struct.bz_stream* %4, %struct.bz_stream** %strm, align 8, !dbg !2364
  %5 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2365
  %cmp = icmp eq %struct.bz_stream* %5, null, !dbg !2367
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !2368

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2369
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 12, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.33, i32 0, i32 0)), !dbg !2371
  store i32 -30, i32* %retval, align 4, !dbg !2372
  br label %return, !dbg !2372

if.end3:                                          ; preds = %if.end
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2373
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 0, !dbg !2374
  %8 = load i8*, i8** %next_in, align 8, !dbg !2374
  %9 = ptrtoint i8* %8 to i64, !dbg !2375
  %10 = inttoptr i64 %9 to i8*, !dbg !2376
  %11 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2377
  %next_in4 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %11, i32 0, i32 0, !dbg !2378
  store i8* %10, i8** %next_in4, align 8, !dbg !2379
  %12 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2380
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %12, i32 0, i32 1, !dbg !2381
  %13 = load i64, i64* %avail_in, align 8, !dbg !2381
  %conv = trunc i64 %13 to i32, !dbg !2380
  %14 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2382
  %avail_in5 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %14, i32 0, i32 1, !dbg !2383
  store i32 %conv, i32* %avail_in5, align 8, !dbg !2384
  %15 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2385
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %15, i32 0, i32 2, !dbg !2386
  %16 = load i64, i64* %total_in, align 8, !dbg !2386
  %and = and i64 %16, 4294967295, !dbg !2387
  %conv6 = trunc i64 %and to i32, !dbg !2388
  %17 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2389
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %17, i32 0, i32 2, !dbg !2390
  store i32 %conv6, i32* %total_in_lo32, align 4, !dbg !2391
  %18 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2392
  %total_in7 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %18, i32 0, i32 2, !dbg !2393
  %19 = load i64, i64* %total_in7, align 8, !dbg !2393
  %shr = lshr i64 %19, 32, !dbg !2394
  %conv8 = trunc i64 %shr to i32, !dbg !2395
  %20 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2396
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %20, i32 0, i32 3, !dbg !2397
  store i32 %conv8, i32* %total_in_hi32, align 8, !dbg !2398
  %21 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2399
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %21, i32 0, i32 3, !dbg !2400
  %22 = load i8*, i8** %next_out, align 8, !dbg !2400
  %23 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2401
  %next_out9 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %23, i32 0, i32 4, !dbg !2402
  store i8* %22, i8** %next_out9, align 8, !dbg !2403
  %24 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2404
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %24, i32 0, i32 4, !dbg !2405
  %25 = load i64, i64* %avail_out, align 8, !dbg !2405
  %conv10 = trunc i64 %25 to i32, !dbg !2404
  %26 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2406
  %avail_out11 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %26, i32 0, i32 5, !dbg !2407
  store i32 %conv10, i32* %avail_out11, align 8, !dbg !2408
  %27 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2409
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %27, i32 0, i32 5, !dbg !2410
  %28 = load i64, i64* %total_out, align 8, !dbg !2410
  %and12 = and i64 %28, 4294967295, !dbg !2411
  %conv13 = trunc i64 %and12 to i32, !dbg !2412
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2413
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %29, i32 0, i32 6, !dbg !2414
  store i32 %conv13, i32* %total_out_lo32, align 4, !dbg !2415
  %30 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2416
  %total_out14 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %30, i32 0, i32 5, !dbg !2417
  %31 = load i64, i64* %total_out14, align 8, !dbg !2417
  %shr15 = lshr i64 %31, 32, !dbg !2418
  %conv16 = trunc i64 %shr15 to i32, !dbg !2419
  %32 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2420
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %32, i32 0, i32 7, !dbg !2421
  store i32 %conv16, i32* %total_out_hi32, align 8, !dbg !2422
  %33 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2423
  %34 = load i32, i32* %level.addr, align 4, !dbg !2425
  %call17 = call i32 @BZ2_bzCompressInit(%struct.bz_stream* %33, i32 %34, i32 0, i32 30), !dbg !2426
  %cmp18 = icmp ne i32 %call17, 0, !dbg !2427
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !2428

if.then20:                                        ; preds = %if.end3
  %35 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2429
  %36 = bitcast %struct.bz_stream* %35 to i8*, !dbg !2429
  call void @free(i8* %36) #8, !dbg !2431
  %37 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2432
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %37, i32 0, i32 9, !dbg !2433
  store i8* null, i8** %real_stream, align 8, !dbg !2434
  %38 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2435
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %38, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.30, i32 0, i32 0)), !dbg !2436
  store i32 -30, i32* %retval, align 4, !dbg !2437
  br label %return, !dbg !2437

if.end21:                                         ; preds = %if.end3
  %39 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2438
  %40 = bitcast %struct.bz_stream* %39 to i8*, !dbg !2438
  %41 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2439
  %real_stream22 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %41, i32 0, i32 9, !dbg !2440
  store i8* %40, i8** %real_stream22, align 8, !dbg !2441
  %42 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2442
  %valid23 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %42, i32 0, i32 8, !dbg !2443
  store i32 1, i32* %valid23, align 8, !dbg !2444
  %43 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2445
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %43, i32 0, i32 10, !dbg !2446
  store i32 (%struct.archive*, %struct.la_zstream*, i32)* @compression_code_bzip2, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !2447
  %44 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2448
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %44, i32 0, i32 11, !dbg !2449
  store i32 (%struct.archive*, %struct.la_zstream*)* @compression_end_bzip2, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !2450
  store i32 0, i32* %retval, align 4, !dbg !2451
  br label %return, !dbg !2451

return:                                           ; preds = %if.end21, %if.then20, %if.then2
  %45 = load i32, i32* %retval, align 4, !dbg !2452
  ret i32 %45, !dbg !2452
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_lzma1(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %level) #0 !dbg !607 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %level.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2453, metadata !693), !dbg !2454
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2455, metadata !693), !dbg !2456
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !2457, metadata !693), !dbg !2458
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2459
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2460
  %2 = load i32, i32* %level.addr, align 4, !dbg !2461
  %call = call i32 @compression_init_encoder_lzma(%struct.archive* %0, %struct.la_zstream* %1, i32 %2, i64 4611686018427387905), !dbg !2462
  ret i32 %call, !dbg !2463
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_lzma2(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %level) #0 !dbg !613 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %level.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2464, metadata !693), !dbg !2465
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2466, metadata !693), !dbg !2467
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !2468, metadata !693), !dbg !2469
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2470
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2471
  %2 = load i32, i32* %level.addr, align 4, !dbg !2472
  %call = call i32 @compression_init_encoder_lzma(%struct.archive* %0, %struct.la_zstream* %1, i32 %2, i64 33), !dbg !2473
  ret i32 %call, !dbg !2474
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_ppmd(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %maxOrder, i32 %msize) #0 !dbg !614 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %maxOrder.addr = alloca i32, align 4
  %msize.addr = alloca i32, align 4
  %strm = alloca %struct.ppmd_stream*, align 8
  %props = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2475, metadata !693), !dbg !2476
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2477, metadata !693), !dbg !2478
  store i32 %maxOrder, i32* %maxOrder.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %maxOrder.addr, metadata !2479, metadata !693), !dbg !2480
  store i32 %msize, i32* %msize.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %msize.addr, metadata !2481, metadata !693), !dbg !2482
  call void @llvm.dbg.declare(metadata %struct.ppmd_stream** %strm, metadata !2483, metadata !693), !dbg !2484
  call void @llvm.dbg.declare(metadata i8** %props, metadata !2485, metadata !693), !dbg !2486
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2487, metadata !693), !dbg !2488
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2489
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !2491
  %1 = load i32, i32* %valid, align 8, !dbg !2491
  %tobool = icmp ne i32 %1, 0, !dbg !2489
  br i1 %tobool, label %if.then, label %if.end, !dbg !2492

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2493
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2494
  %call = call i32 @compression_end(%struct.archive* %2, %struct.la_zstream* %3), !dbg !2495
  br label %if.end, !dbg !2495

if.end:                                           ; preds = %if.then, %entry
  %call1 = call noalias i8* @calloc(i64 1, i64 19272) #8, !dbg !2496
  %4 = bitcast i8* %call1 to %struct.ppmd_stream*, !dbg !2496
  store %struct.ppmd_stream* %4, %struct.ppmd_stream** %strm, align 8, !dbg !2497
  %5 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2498
  %cmp = icmp eq %struct.ppmd_stream* %5, null, !dbg !2500
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !2501

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2502
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.43, i32 0, i32 0)), !dbg !2504
  store i32 -30, i32* %retval, align 4, !dbg !2505
  br label %return, !dbg !2505

if.end3:                                          ; preds = %if.end
  %call4 = call noalias i8* @malloc(i64 32) #8, !dbg !2506
  %7 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2507
  %buff = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %7, i32 0, i32 4, !dbg !2508
  store i8* %call4, i8** %buff, align 8, !dbg !2509
  %8 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2510
  %buff5 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %8, i32 0, i32 4, !dbg !2512
  %9 = load i8*, i8** %buff5, align 8, !dbg !2512
  %cmp6 = icmp eq i8* %9, null, !dbg !2513
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2514

if.then7:                                         ; preds = %if.end3
  %10 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2515
  %11 = bitcast %struct.ppmd_stream* %10 to i8*, !dbg !2515
  call void @free(i8* %11) #8, !dbg !2517
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2518
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %12, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.43, i32 0, i32 0)), !dbg !2519
  store i32 -30, i32* %retval, align 4, !dbg !2520
  br label %return, !dbg !2520

if.end8:                                          ; preds = %if.end3
  %13 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2521
  %buff9 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %13, i32 0, i32 4, !dbg !2522
  %14 = load i8*, i8** %buff9, align 8, !dbg !2522
  %15 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2523
  %buff_ptr = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %15, i32 0, i32 5, !dbg !2524
  store i8* %14, i8** %buff_ptr, align 8, !dbg !2525
  %16 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2526
  %buff10 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %16, i32 0, i32 4, !dbg !2527
  %17 = load i8*, i8** %buff10, align 8, !dbg !2527
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 32, !dbg !2528
  %18 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2529
  %buff_end = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %18, i32 0, i32 6, !dbg !2530
  store i8* %add.ptr, i8** %buff_end, align 8, !dbg !2531
  %call11 = call noalias i8* @malloc(i64 5) #8, !dbg !2532
  store i8* %call11, i8** %props, align 8, !dbg !2533
  %19 = load i8*, i8** %props, align 8, !dbg !2534
  %cmp12 = icmp eq i8* %19, null, !dbg !2536
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !2537

if.then13:                                        ; preds = %if.end8
  %20 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2538
  %buff14 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %20, i32 0, i32 4, !dbg !2540
  %21 = load i8*, i8** %buff14, align 8, !dbg !2540
  call void @free(i8* %21) #8, !dbg !2541
  %22 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2542
  %23 = bitcast %struct.ppmd_stream* %22 to i8*, !dbg !2542
  call void @free(i8* %23) #8, !dbg !2543
  %24 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2544
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %24, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.44, i32 0, i32 0)), !dbg !2545
  store i32 -30, i32* %retval, align 4, !dbg !2546
  br label %return, !dbg !2546

if.end15:                                         ; preds = %if.end8
  %25 = load i32, i32* %maxOrder.addr, align 4, !dbg !2547
  %conv = trunc i32 %25 to i8, !dbg !2547
  %26 = load i8*, i8** %props, align 8, !dbg !2548
  %arrayidx = getelementptr inbounds i8, i8* %26, i64 0, !dbg !2548
  store i8 %conv, i8* %arrayidx, align 1, !dbg !2549
  %27 = load i8*, i8** %props, align 8, !dbg !2550
  %add.ptr16 = getelementptr inbounds i8, i8* %27, i64 1, !dbg !2551
  %28 = load i32, i32* %msize.addr, align 4, !dbg !2552
  call void @archive_le32enc(i8* %add.ptr16, i32 %28), !dbg !2553
  %29 = load void (%struct.CPpmd7*)*, void (%struct.CPpmd7*)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 0), align 8, !dbg !2554
  %30 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2555
  %ppmd7_context = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %30, i32 0, i32 1, !dbg !2556
  call void %29(%struct.CPpmd7* %ppmd7_context), !dbg !2557
  %31 = load i32 (%struct.CPpmd7*, i32, %struct.ISzAlloc*)*, i32 (%struct.CPpmd7*, i32, %struct.ISzAlloc*)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 1), align 8, !dbg !2558
  %32 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2559
  %ppmd7_context17 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %32, i32 0, i32 1, !dbg !2560
  %33 = load i32, i32* %msize.addr, align 4, !dbg !2561
  %call18 = call i32 %31(%struct.CPpmd7* %ppmd7_context17, i32 %33, %struct.ISzAlloc* @g_szalloc), !dbg !2562
  store i32 %call18, i32* %r, align 4, !dbg !2563
  %34 = load i32, i32* %r, align 4, !dbg !2564
  %cmp19 = icmp eq i32 %34, 0, !dbg !2566
  br i1 %cmp19, label %if.then21, label %if.end23, !dbg !2567

if.then21:                                        ; preds = %if.end15
  %35 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2568
  %buff22 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %35, i32 0, i32 4, !dbg !2570
  %36 = load i8*, i8** %buff22, align 8, !dbg !2570
  call void @free(i8* %36) #8, !dbg !2571
  %37 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2572
  %38 = bitcast %struct.ppmd_stream* %37 to i8*, !dbg !2572
  call void @free(i8* %38) #8, !dbg !2573
  %39 = load i8*, i8** %props, align 8, !dbg !2574
  call void @free(i8* %39) #8, !dbg !2575
  %40 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2576
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %40, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.44, i32 0, i32 0)), !dbg !2577
  store i32 -30, i32* %retval, align 4, !dbg !2578
  br label %return, !dbg !2578

if.end23:                                         ; preds = %if.end15
  %41 = load void (%struct.CPpmd7*, i32)*, void (%struct.CPpmd7*, i32)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 3), align 8, !dbg !2579
  %42 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2580
  %ppmd7_context24 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %42, i32 0, i32 1, !dbg !2581
  %43 = load i32, i32* %maxOrder.addr, align 4, !dbg !2582
  call void %41(%struct.CPpmd7* %ppmd7_context24, i32 %43), !dbg !2583
  %44 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2584
  %45 = bitcast %struct.archive* %44 to %struct.archive_write*, !dbg !2585
  %46 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2586
  %byteout = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %46, i32 0, i32 3, !dbg !2587
  %a25 = getelementptr inbounds %struct.IByteOut, %struct.IByteOut* %byteout, i32 0, i32 0, !dbg !2588
  store %struct.archive_write* %45, %struct.archive_write** %a25, align 8, !dbg !2589
  %47 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2590
  %byteout26 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %47, i32 0, i32 3, !dbg !2591
  %Write = getelementptr inbounds %struct.IByteOut, %struct.IByteOut* %byteout26, i32 0, i32 1, !dbg !2592
  store void (i8*, i8)* @ppmd_write, void (i8*, i8)** %Write, align 8, !dbg !2593
  %48 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2594
  %byteout27 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %48, i32 0, i32 3, !dbg !2595
  %49 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2596
  %range_enc = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %49, i32 0, i32 2, !dbg !2597
  %Stream = getelementptr inbounds %struct.CPpmd7z_RangeEnc, %struct.CPpmd7z_RangeEnc* %range_enc, i32 0, i32 4, !dbg !2598
  store %struct.IByteOut* %byteout27, %struct.IByteOut** %Stream, align 8, !dbg !2599
  %50 = load void (%struct.CPpmd7z_RangeEnc*)*, void (%struct.CPpmd7z_RangeEnc*)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 9), align 8, !dbg !2600
  %51 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2601
  %range_enc28 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %51, i32 0, i32 2, !dbg !2602
  call void %50(%struct.CPpmd7z_RangeEnc* %range_enc28), !dbg !2603
  %52 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2604
  %stat = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %52, i32 0, i32 0, !dbg !2605
  store i32 0, i32* %stat, align 8, !dbg !2606
  %53 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !2607
  %54 = bitcast %struct.ppmd_stream* %53 to i8*, !dbg !2607
  %55 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2608
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %55, i32 0, i32 9, !dbg !2609
  store i8* %54, i8** %real_stream, align 8, !dbg !2610
  %56 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2611
  %valid29 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %56, i32 0, i32 8, !dbg !2612
  store i32 1, i32* %valid29, align 8, !dbg !2613
  %57 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2614
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %57, i32 0, i32 10, !dbg !2615
  store i32 (%struct.archive*, %struct.la_zstream*, i32)* @compression_code_ppmd, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !2616
  %58 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2617
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %58, i32 0, i32 11, !dbg !2618
  store i32 (%struct.archive*, %struct.la_zstream*)* @compression_end_ppmd, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !2619
  %59 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2620
  %prop_size = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %59, i32 0, i32 6, !dbg !2621
  store i32 5, i32* %prop_size, align 8, !dbg !2622
  %60 = load i8*, i8** %props, align 8, !dbg !2623
  %61 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2624
  %props30 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %61, i32 0, i32 7, !dbg !2625
  store i8* %60, i8** %props30, align 8, !dbg !2626
  store i32 0, i32* %retval, align 4, !dbg !2627
  br label %return, !dbg !2627

return:                                           ; preds = %if.end23, %if.then21, %if.then13, %if.then7, %if.then2
  %62 = load i32, i32* %retval, align 4, !dbg !2628
  ret i32 %62, !dbg !2628
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_copy(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !628 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2629, metadata !693), !dbg !2630
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2631, metadata !693), !dbg !2632
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2633
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !2635
  %1 = load i32, i32* %valid, align 8, !dbg !2635
  %tobool = icmp ne i32 %1, 0, !dbg !2633
  br i1 %tobool, label %if.then, label %if.end, !dbg !2636

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2637
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2638
  %call = call i32 @compression_end(%struct.archive* %2, %struct.la_zstream* %3), !dbg !2639
  br label %if.end, !dbg !2639

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2640
  %valid1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %4, i32 0, i32 8, !dbg !2641
  store i32 1, i32* %valid1, align 8, !dbg !2642
  %5 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2643
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %5, i32 0, i32 10, !dbg !2644
  store i32 (%struct.archive*, %struct.la_zstream*, i32)* @compression_code_copy, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !2645
  %6 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2646
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %6, i32 0, i32 11, !dbg !2647
  store i32 (%struct.archive*, %struct.la_zstream*)* @compression_end_copy, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !2648
  ret i32 0, !dbg !2649
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !599 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2650, metadata !693), !dbg !2651
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2652, metadata !693), !dbg !2653
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2654
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !2656
  %1 = load i32, i32* %valid, align 8, !dbg !2656
  %tobool = icmp ne i32 %1, 0, !dbg !2654
  br i1 %tobool, label %if.then, label %if.end, !dbg !2657

if.then:                                          ; preds = %entry
  %2 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2658
  %prop_size = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %2, i32 0, i32 6, !dbg !2660
  store i32 0, i32* %prop_size, align 8, !dbg !2661
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2662
  %props = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %3, i32 0, i32 7, !dbg !2663
  %4 = load i8*, i8** %props, align 8, !dbg !2663
  call void @free(i8* %4) #8, !dbg !2664
  %5 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2665
  %props1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %5, i32 0, i32 7, !dbg !2666
  store i8* null, i8** %props1, align 8, !dbg !2667
  %6 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2668
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %6, i32 0, i32 11, !dbg !2669
  %7 = load i32 (%struct.archive*, %struct.la_zstream*)*, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !2669
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2670
  %9 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2671
  %call = call i32 %7(%struct.archive* %8, %struct.la_zstream* %9), !dbg !2668
  store i32 %call, i32* %retval, align 4, !dbg !2672
  br label %return, !dbg !2672

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2673
  br label %return, !dbg !2673

return:                                           ; preds = %if.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2674
  ret i32 %10, !dbg !2674
}

declare i32 @cm_zlib_deflateInit2_(%struct.z_stream_s*, i32, i32, i32, i32, i32, i8*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @compression_code_deflate(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !600 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  %strm = alloca %struct.z_stream_s*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2675, metadata !693), !dbg !2676
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2677, metadata !693), !dbg !2678
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !2679, metadata !693), !dbg !2680
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm, metadata !2681, metadata !693), !dbg !2682
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2683, metadata !693), !dbg !2684
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2685
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 9, !dbg !2686
  %1 = load i8*, i8** %real_stream, align 8, !dbg !2686
  %2 = bitcast i8* %1 to %struct.z_stream_s*, !dbg !2687
  store %struct.z_stream_s* %2, %struct.z_stream_s** %strm, align 8, !dbg !2688
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2689
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %3, i32 0, i32 0, !dbg !2690
  %4 = load i8*, i8** %next_in, align 8, !dbg !2690
  %5 = ptrtoint i8* %4 to i64, !dbg !2691
  %6 = inttoptr i64 %5 to i8*, !dbg !2692
  %7 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2693
  %next_in1 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %7, i32 0, i32 0, !dbg !2694
  store i8* %6, i8** %next_in1, align 8, !dbg !2695
  %8 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2696
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %8, i32 0, i32 1, !dbg !2697
  %9 = load i64, i64* %avail_in, align 8, !dbg !2697
  %conv = trunc i64 %9 to i32, !dbg !2698
  %10 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2699
  %avail_in2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %10, i32 0, i32 1, !dbg !2700
  store i32 %conv, i32* %avail_in2, align 8, !dbg !2701
  %11 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2702
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %11, i32 0, i32 2, !dbg !2703
  %12 = load i64, i64* %total_in, align 8, !dbg !2703
  %13 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2704
  %total_in3 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %13, i32 0, i32 2, !dbg !2705
  store i64 %12, i64* %total_in3, align 8, !dbg !2706
  %14 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2707
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %14, i32 0, i32 3, !dbg !2708
  %15 = load i8*, i8** %next_out, align 8, !dbg !2708
  %16 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2709
  %next_out4 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %16, i32 0, i32 3, !dbg !2710
  store i8* %15, i8** %next_out4, align 8, !dbg !2711
  %17 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2712
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %17, i32 0, i32 4, !dbg !2713
  %18 = load i64, i64* %avail_out, align 8, !dbg !2713
  %conv5 = trunc i64 %18 to i32, !dbg !2714
  %19 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2715
  %avail_out6 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %19, i32 0, i32 4, !dbg !2716
  store i32 %conv5, i32* %avail_out6, align 8, !dbg !2717
  %20 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2718
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %20, i32 0, i32 5, !dbg !2719
  %21 = load i64, i64* %total_out, align 8, !dbg !2719
  %22 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2720
  %total_out7 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %22, i32 0, i32 5, !dbg !2721
  store i64 %21, i64* %total_out7, align 8, !dbg !2722
  %23 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2723
  %24 = load i32, i32* %action.addr, align 4, !dbg !2724
  %cmp = icmp eq i32 %24, 0, !dbg !2725
  %cond = select i1 %cmp, i32 4, i32 0, !dbg !2726
  %call = call i32 @cm_zlib_deflate(%struct.z_stream_s* %23, i32 %cond), !dbg !2727
  store i32 %call, i32* %r, align 4, !dbg !2728
  %25 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2729
  %next_in9 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %25, i32 0, i32 0, !dbg !2730
  %26 = load i8*, i8** %next_in9, align 8, !dbg !2730
  %27 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2731
  %next_in10 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %27, i32 0, i32 0, !dbg !2732
  store i8* %26, i8** %next_in10, align 8, !dbg !2733
  %28 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2734
  %avail_in11 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %28, i32 0, i32 1, !dbg !2735
  %29 = load i32, i32* %avail_in11, align 8, !dbg !2735
  %conv12 = zext i32 %29 to i64, !dbg !2734
  %30 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2736
  %avail_in13 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %30, i32 0, i32 1, !dbg !2737
  store i64 %conv12, i64* %avail_in13, align 8, !dbg !2738
  %31 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2739
  %total_in14 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %31, i32 0, i32 2, !dbg !2740
  %32 = load i64, i64* %total_in14, align 8, !dbg !2740
  %33 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2741
  %total_in15 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %33, i32 0, i32 2, !dbg !2742
  store i64 %32, i64* %total_in15, align 8, !dbg !2743
  %34 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2744
  %next_out16 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %34, i32 0, i32 3, !dbg !2745
  %35 = load i8*, i8** %next_out16, align 8, !dbg !2745
  %36 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2746
  %next_out17 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %36, i32 0, i32 3, !dbg !2747
  store i8* %35, i8** %next_out17, align 8, !dbg !2748
  %37 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2749
  %avail_out18 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %37, i32 0, i32 4, !dbg !2750
  %38 = load i32, i32* %avail_out18, align 8, !dbg !2750
  %conv19 = zext i32 %38 to i64, !dbg !2749
  %39 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2751
  %avail_out20 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %39, i32 0, i32 4, !dbg !2752
  store i64 %conv19, i64* %avail_out20, align 8, !dbg !2753
  %40 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2754
  %total_out21 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %40, i32 0, i32 5, !dbg !2755
  %41 = load i64, i64* %total_out21, align 8, !dbg !2755
  %42 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2756
  %total_out22 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %42, i32 0, i32 5, !dbg !2757
  store i64 %41, i64* %total_out22, align 8, !dbg !2758
  %43 = load i32, i32* %r, align 4, !dbg !2759
  switch i32 %43, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb23
  ], !dbg !2760

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2761
  br label %return, !dbg !2761

sw.bb23:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !2763
  br label %return, !dbg !2763

sw.default:                                       ; preds = %entry
  %44 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2764
  %45 = load i32, i32* %r, align 4, !dbg !2765
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %44, i32 -1, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.31, i32 0, i32 0), i32 %45), !dbg !2766
  store i32 -30, i32* %retval, align 4, !dbg !2767
  br label %return, !dbg !2767

return:                                           ; preds = %sw.default, %sw.bb23, %sw.bb
  %46 = load i32, i32* %retval, align 4, !dbg !2768
  ret i32 %46, !dbg !2768
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end_deflate(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !601 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %strm = alloca %struct.z_stream_s*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2769, metadata !693), !dbg !2770
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2771, metadata !693), !dbg !2772
  call void @llvm.dbg.declare(metadata %struct.z_stream_s** %strm, metadata !2773, metadata !693), !dbg !2774
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2775, metadata !693), !dbg !2776
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2777
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 9, !dbg !2778
  %1 = load i8*, i8** %real_stream, align 8, !dbg !2778
  %2 = bitcast i8* %1 to %struct.z_stream_s*, !dbg !2779
  store %struct.z_stream_s* %2, %struct.z_stream_s** %strm, align 8, !dbg !2780
  %3 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2781
  %call = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %3), !dbg !2782
  store i32 %call, i32* %r, align 4, !dbg !2783
  %4 = load %struct.z_stream_s*, %struct.z_stream_s** %strm, align 8, !dbg !2784
  %5 = bitcast %struct.z_stream_s* %4 to i8*, !dbg !2784
  call void @free(i8* %5) #8, !dbg !2785
  %6 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2786
  %real_stream1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %6, i32 0, i32 9, !dbg !2787
  store i8* null, i8** %real_stream1, align 8, !dbg !2788
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2789
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 8, !dbg !2790
  store i32 0, i32* %valid, align 8, !dbg !2791
  %8 = load i32, i32* %r, align 4, !dbg !2792
  %cmp = icmp ne i32 %8, 0, !dbg !2794
  br i1 %cmp, label %if.then, label %if.end, !dbg !2795

if.then:                                          ; preds = %entry
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2796
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 -1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.32, i32 0, i32 0)), !dbg !2798
  store i32 -30, i32* %retval, align 4, !dbg !2799
  br label %return, !dbg !2799

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2800
  br label %return, !dbg !2800

return:                                           ; preds = %if.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2801
  ret i32 %10, !dbg !2801
}

declare i32 @cm_zlib_deflate(%struct.z_stream_s*, i32) #2

declare i32 @cm_zlib_deflateEnd(%struct.z_stream_s*) #2

declare i32 @BZ2_bzCompressInit(%struct.bz_stream*, i32, i32, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @compression_code_bzip2(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !605 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  %strm = alloca %struct.bz_stream*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2802, metadata !693), !dbg !2803
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2804, metadata !693), !dbg !2805
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !2806, metadata !693), !dbg !2807
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm, metadata !2808, metadata !693), !dbg !2809
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2810, metadata !693), !dbg !2811
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2812
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 9, !dbg !2813
  %1 = load i8*, i8** %real_stream, align 8, !dbg !2813
  %2 = bitcast i8* %1 to %struct.bz_stream*, !dbg !2814
  store %struct.bz_stream* %2, %struct.bz_stream** %strm, align 8, !dbg !2815
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2816
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %3, i32 0, i32 0, !dbg !2817
  %4 = load i8*, i8** %next_in, align 8, !dbg !2817
  %5 = ptrtoint i8* %4 to i64, !dbg !2818
  %6 = inttoptr i64 %5 to i8*, !dbg !2819
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2820
  %next_in1 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %7, i32 0, i32 0, !dbg !2821
  store i8* %6, i8** %next_in1, align 8, !dbg !2822
  %8 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2823
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %8, i32 0, i32 1, !dbg !2824
  %9 = load i64, i64* %avail_in, align 8, !dbg !2824
  %conv = trunc i64 %9 to i32, !dbg !2823
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2825
  %avail_in2 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 1, !dbg !2826
  store i32 %conv, i32* %avail_in2, align 8, !dbg !2827
  %11 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2828
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %11, i32 0, i32 2, !dbg !2829
  %12 = load i64, i64* %total_in, align 8, !dbg !2829
  %and = and i64 %12, 4294967295, !dbg !2830
  %conv3 = trunc i64 %and to i32, !dbg !2831
  %13 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2832
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %13, i32 0, i32 2, !dbg !2833
  store i32 %conv3, i32* %total_in_lo32, align 4, !dbg !2834
  %14 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2835
  %total_in4 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %14, i32 0, i32 2, !dbg !2836
  %15 = load i64, i64* %total_in4, align 8, !dbg !2836
  %shr = lshr i64 %15, 32, !dbg !2837
  %conv5 = trunc i64 %shr to i32, !dbg !2838
  %16 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2839
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %16, i32 0, i32 3, !dbg !2840
  store i32 %conv5, i32* %total_in_hi32, align 8, !dbg !2841
  %17 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2842
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %17, i32 0, i32 3, !dbg !2843
  %18 = load i8*, i8** %next_out, align 8, !dbg !2843
  %19 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2844
  %next_out6 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %19, i32 0, i32 4, !dbg !2845
  store i8* %18, i8** %next_out6, align 8, !dbg !2846
  %20 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2847
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %20, i32 0, i32 4, !dbg !2848
  %21 = load i64, i64* %avail_out, align 8, !dbg !2848
  %conv7 = trunc i64 %21 to i32, !dbg !2847
  %22 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2849
  %avail_out8 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %22, i32 0, i32 5, !dbg !2850
  store i32 %conv7, i32* %avail_out8, align 8, !dbg !2851
  %23 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2852
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %23, i32 0, i32 5, !dbg !2853
  %24 = load i64, i64* %total_out, align 8, !dbg !2853
  %and9 = and i64 %24, 4294967295, !dbg !2854
  %conv10 = trunc i64 %and9 to i32, !dbg !2855
  %25 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2856
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %25, i32 0, i32 6, !dbg !2857
  store i32 %conv10, i32* %total_out_lo32, align 4, !dbg !2858
  %26 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2859
  %total_out11 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %26, i32 0, i32 5, !dbg !2860
  %27 = load i64, i64* %total_out11, align 8, !dbg !2860
  %shr12 = lshr i64 %27, 32, !dbg !2861
  %conv13 = trunc i64 %shr12 to i32, !dbg !2862
  %28 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2863
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %28, i32 0, i32 7, !dbg !2864
  store i32 %conv13, i32* %total_out_hi32, align 8, !dbg !2865
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2866
  %30 = load i32, i32* %action.addr, align 4, !dbg !2867
  %cmp = icmp eq i32 %30, 0, !dbg !2868
  %cond = select i1 %cmp, i32 2, i32 0, !dbg !2869
  %call = call i32 @BZ2_bzCompress(%struct.bz_stream* %29, i32 %cond), !dbg !2870
  store i32 %call, i32* %r, align 4, !dbg !2871
  %31 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2872
  %next_in15 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %31, i32 0, i32 0, !dbg !2873
  %32 = load i8*, i8** %next_in15, align 8, !dbg !2873
  %33 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2874
  %next_in16 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %33, i32 0, i32 0, !dbg !2875
  store i8* %32, i8** %next_in16, align 8, !dbg !2876
  %34 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2877
  %avail_in17 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %34, i32 0, i32 1, !dbg !2878
  %35 = load i32, i32* %avail_in17, align 8, !dbg !2878
  %conv18 = zext i32 %35 to i64, !dbg !2877
  %36 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2879
  %avail_in19 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %36, i32 0, i32 1, !dbg !2880
  store i64 %conv18, i64* %avail_in19, align 8, !dbg !2881
  %37 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2882
  %total_in_hi3220 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %37, i32 0, i32 3, !dbg !2883
  %38 = load i32, i32* %total_in_hi3220, align 8, !dbg !2883
  %conv21 = zext i32 %38 to i64, !dbg !2884
  %shl = shl i64 %conv21, 32, !dbg !2885
  %39 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2886
  %total_in_lo3222 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %39, i32 0, i32 2, !dbg !2887
  %40 = load i32, i32* %total_in_lo3222, align 4, !dbg !2887
  %conv23 = zext i32 %40 to i64, !dbg !2888
  %add = add i64 %shl, %conv23, !dbg !2889
  %41 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2890
  %total_in24 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %41, i32 0, i32 2, !dbg !2891
  store i64 %add, i64* %total_in24, align 8, !dbg !2892
  %42 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2893
  %next_out25 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %42, i32 0, i32 4, !dbg !2894
  %43 = load i8*, i8** %next_out25, align 8, !dbg !2894
  %44 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2895
  %next_out26 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %44, i32 0, i32 3, !dbg !2896
  store i8* %43, i8** %next_out26, align 8, !dbg !2897
  %45 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2898
  %avail_out27 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %45, i32 0, i32 5, !dbg !2899
  %46 = load i32, i32* %avail_out27, align 8, !dbg !2899
  %conv28 = zext i32 %46 to i64, !dbg !2898
  %47 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2900
  %avail_out29 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %47, i32 0, i32 4, !dbg !2901
  store i64 %conv28, i64* %avail_out29, align 8, !dbg !2902
  %48 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2903
  %total_out_hi3230 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %48, i32 0, i32 7, !dbg !2904
  %49 = load i32, i32* %total_out_hi3230, align 8, !dbg !2904
  %conv31 = zext i32 %49 to i64, !dbg !2905
  %shl32 = shl i64 %conv31, 32, !dbg !2906
  %50 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2907
  %total_out_lo3233 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %50, i32 0, i32 6, !dbg !2908
  %51 = load i32, i32* %total_out_lo3233, align 4, !dbg !2908
  %conv34 = zext i32 %51 to i64, !dbg !2909
  %add35 = add i64 %shl32, %conv34, !dbg !2910
  %52 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2911
  %total_out36 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %52, i32 0, i32 5, !dbg !2912
  store i64 %add35, i64* %total_out36, align 8, !dbg !2913
  %53 = load i32, i32* %r, align 4, !dbg !2914
  switch i32 %53, label %sw.default [
    i32 1, label %sw.bb
    i32 3, label %sw.bb
    i32 4, label %sw.bb37
  ], !dbg !2915

sw.bb:                                            ; preds = %entry, %entry
  store i32 0, i32* %retval, align 4, !dbg !2916
  br label %return, !dbg !2916

sw.bb37:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !2918
  br label %return, !dbg !2918

sw.default:                                       ; preds = %entry
  %54 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2919
  %55 = load i32, i32* %r, align 4, !dbg !2920
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %54, i32 -1, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.34, i32 0, i32 0), i32 %55), !dbg !2921
  store i32 -30, i32* %retval, align 4, !dbg !2922
  br label %return, !dbg !2922

return:                                           ; preds = %sw.default, %sw.bb37, %sw.bb
  %56 = load i32, i32* %retval, align 4, !dbg !2923
  ret i32 %56, !dbg !2923
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end_bzip2(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !606 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %strm = alloca %struct.bz_stream*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2924, metadata !693), !dbg !2925
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2926, metadata !693), !dbg !2927
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm, metadata !2928, metadata !693), !dbg !2929
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2930, metadata !693), !dbg !2931
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2932
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 9, !dbg !2933
  %1 = load i8*, i8** %real_stream, align 8, !dbg !2933
  %2 = bitcast i8* %1 to %struct.bz_stream*, !dbg !2934
  store %struct.bz_stream* %2, %struct.bz_stream** %strm, align 8, !dbg !2935
  %3 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2936
  %call = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %3), !dbg !2937
  store i32 %call, i32* %r, align 4, !dbg !2938
  %4 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !2939
  %5 = bitcast %struct.bz_stream* %4 to i8*, !dbg !2939
  call void @free(i8* %5) #8, !dbg !2940
  %6 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2941
  %real_stream1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %6, i32 0, i32 9, !dbg !2942
  store i8* null, i8** %real_stream1, align 8, !dbg !2943
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !2944
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 8, !dbg !2945
  store i32 0, i32* %valid, align 8, !dbg !2946
  %8 = load i32, i32* %r, align 4, !dbg !2947
  %cmp = icmp ne i32 %8, 0, !dbg !2949
  br i1 %cmp, label %if.then, label %if.end, !dbg !2950

if.then:                                          ; preds = %entry
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2951
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 -1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.32, i32 0, i32 0)), !dbg !2953
  store i32 -30, i32* %retval, align 4, !dbg !2954
  br label %return, !dbg !2954

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2955
  br label %return, !dbg !2955

return:                                           ; preds = %if.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2956
  ret i32 %10, !dbg !2956
}

declare i32 @BZ2_bzCompress(%struct.bz_stream*, i32) #2

declare i32 @BZ2_bzCompressEnd(%struct.bz_stream*) #2

; Function Attrs: nounwind uwtable
define internal i32 @compression_init_encoder_lzma(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %level, i64 %filter_id) #0 !dbg !608 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %level.addr = alloca i32, align 4
  %filter_id.addr = alloca i64, align 8
  %strm = alloca %struct.lzma_stream*, align 8
  %lzmafilters = alloca %struct.lzma_filter*, align 8
  %lzma_opt = alloca %struct.lzma_options_lzma, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2957, metadata !693), !dbg !2958
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !2959, metadata !693), !dbg !2960
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !2961, metadata !693), !dbg !2962
  store i64 %filter_id, i64* %filter_id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %filter_id.addr, metadata !2963, metadata !693), !dbg !2964
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm, metadata !2965, metadata !693), !dbg !2966
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %lzmafilters, metadata !2967, metadata !693), !dbg !2968
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma* %lzma_opt, metadata !2969, metadata !693), !dbg !2999
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3000, metadata !693), !dbg !3001
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3002
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !3004
  %1 = load i32, i32* %valid, align 8, !dbg !3004
  %tobool = icmp ne i32 %1, 0, !dbg !3002
  br i1 %tobool, label %if.then, label %if.end, !dbg !3005

if.then:                                          ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3006
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3007
  %call = call i32 @compression_end(%struct.archive* %2, %struct.la_zstream* %3), !dbg !3008
  br label %if.end, !dbg !3008

if.end:                                           ; preds = %if.then, %entry
  %call1 = call noalias i8* @calloc(i64 1, i64 168) #8, !dbg !3009
  %4 = bitcast i8* %call1 to %struct.lzma_stream*, !dbg !3009
  store %struct.lzma_stream* %4, %struct.lzma_stream** %strm, align 8, !dbg !3010
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3011
  %cmp = icmp eq %struct.lzma_stream* %5, null, !dbg !3013
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !3014

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3015
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 12, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.35, i32 0, i32 0)), !dbg !3017
  store i32 -30, i32* %retval, align 4, !dbg !3018
  br label %return, !dbg !3018

if.end3:                                          ; preds = %if.end
  %7 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3019
  %add.ptr = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %7, i64 1, !dbg !3020
  %8 = bitcast %struct.lzma_stream* %add.ptr to %struct.lzma_filter*, !dbg !3021
  store %struct.lzma_filter* %8, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3022
  %9 = load i32, i32* %level.addr, align 4, !dbg !3023
  %cmp4 = icmp sgt i32 %9, 6, !dbg !3025
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !3026

if.then5:                                         ; preds = %if.end3
  store i32 6, i32* %level.addr, align 4, !dbg !3027
  br label %if.end6, !dbg !3028

if.end6:                                          ; preds = %if.then5, %if.end3
  %10 = load i32, i32* %level.addr, align 4, !dbg !3029
  %call7 = call zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma* %lzma_opt, i32 %10) #8, !dbg !3031
  %tobool8 = icmp ne i8 %call7, 0, !dbg !3031
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !3032

if.then9:                                         ; preds = %if.end6
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3033
  %12 = bitcast %struct.lzma_stream* %11 to i8*, !dbg !3033
  call void @free(i8* %12) #8, !dbg !3035
  %13 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3036
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %13, i32 0, i32 9, !dbg !3037
  store i8* null, i8** %real_stream, align 8, !dbg !3038
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3039
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 12, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.30, i32 0, i32 0)), !dbg !3040
  store i32 -30, i32* %retval, align 4, !dbg !3041
  br label %return, !dbg !3041

if.end10:                                         ; preds = %if.end6
  %15 = load i64, i64* %filter_id.addr, align 8, !dbg !3042
  %16 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3043
  %arrayidx = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %16, i64 0, !dbg !3043
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx, i32 0, i32 0, !dbg !3044
  store i64 %15, i64* %id, align 8, !dbg !3045
  %17 = bitcast %struct.lzma_options_lzma* %lzma_opt to i8*, !dbg !3046
  %18 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3047
  %arrayidx11 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %18, i64 0, !dbg !3047
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx11, i32 0, i32 1, !dbg !3048
  store i8* %17, i8** %options, align 8, !dbg !3049
  %19 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3050
  %arrayidx12 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %19, i64 1, !dbg !3050
  %id13 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx12, i32 0, i32 0, !dbg !3051
  store i64 -1, i64* %id13, align 8, !dbg !3052
  %20 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3053
  %prop_size = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %20, i32 0, i32 6, !dbg !3054
  %21 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3055
  %call14 = call i32 @lzma_properties_size(i32* %prop_size, %struct.lzma_filter* %21) #8, !dbg !3056
  store i32 %call14, i32* %r, align 4, !dbg !3057
  %22 = load i32, i32* %r, align 4, !dbg !3058
  %cmp15 = icmp ne i32 %22, 0, !dbg !3060
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !3061

if.then16:                                        ; preds = %if.end10
  %23 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3062
  %24 = bitcast %struct.lzma_stream* %23 to i8*, !dbg !3062
  call void @free(i8* %24) #8, !dbg !3064
  %25 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3065
  %real_stream17 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %25, i32 0, i32 9, !dbg !3066
  store i8* null, i8** %real_stream17, align 8, !dbg !3067
  %26 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3068
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %26, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.36, i32 0, i32 0)), !dbg !3069
  store i32 -30, i32* %retval, align 4, !dbg !3070
  br label %return, !dbg !3070

if.end18:                                         ; preds = %if.end10
  %27 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3071
  %prop_size19 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %27, i32 0, i32 6, !dbg !3073
  %28 = load i32, i32* %prop_size19, align 8, !dbg !3073
  %tobool20 = icmp ne i32 %28, 0, !dbg !3071
  br i1 %tobool20, label %if.then21, label %if.end37, !dbg !3074

if.then21:                                        ; preds = %if.end18
  %29 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3075
  %prop_size22 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %29, i32 0, i32 6, !dbg !3077
  %30 = load i32, i32* %prop_size22, align 8, !dbg !3077
  %conv = zext i32 %30 to i64, !dbg !3075
  %call23 = call noalias i8* @malloc(i64 %conv) #8, !dbg !3078
  %31 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3079
  %props = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %31, i32 0, i32 7, !dbg !3080
  store i8* %call23, i8** %props, align 8, !dbg !3081
  %32 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3082
  %props24 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %32, i32 0, i32 7, !dbg !3084
  %33 = load i8*, i8** %props24, align 8, !dbg !3084
  %cmp25 = icmp eq i8* %33, null, !dbg !3085
  br i1 %cmp25, label %if.then27, label %if.end29, !dbg !3086

if.then27:                                        ; preds = %if.then21
  %34 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3087
  %35 = bitcast %struct.lzma_stream* %34 to i8*, !dbg !3087
  call void @free(i8* %35) #8, !dbg !3089
  %36 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3090
  %real_stream28 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %36, i32 0, i32 9, !dbg !3091
  store i8* null, i8** %real_stream28, align 8, !dbg !3092
  %37 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3093
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %37, i32 12, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.37, i32 0, i32 0)), !dbg !3094
  store i32 -30, i32* %retval, align 4, !dbg !3095
  br label %return, !dbg !3095

if.end29:                                         ; preds = %if.then21
  %38 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3096
  %39 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3097
  %props30 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %39, i32 0, i32 7, !dbg !3098
  %40 = load i8*, i8** %props30, align 8, !dbg !3098
  %call31 = call i32 @lzma_properties_encode(%struct.lzma_filter* %38, i8* %40) #8, !dbg !3099
  store i32 %call31, i32* %r, align 4, !dbg !3100
  %41 = load i32, i32* %r, align 4, !dbg !3101
  %cmp32 = icmp ne i32 %41, 0, !dbg !3103
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !3104

if.then34:                                        ; preds = %if.end29
  %42 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3105
  %43 = bitcast %struct.lzma_stream* %42 to i8*, !dbg !3105
  call void @free(i8* %43) #8, !dbg !3107
  %44 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3108
  %real_stream35 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %44, i32 0, i32 9, !dbg !3109
  store i8* null, i8** %real_stream35, align 8, !dbg !3110
  %45 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3111
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %45, i32 -1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.38, i32 0, i32 0)), !dbg !3112
  store i32 -30, i32* %retval, align 4, !dbg !3113
  br label %return, !dbg !3113

if.end36:                                         ; preds = %if.end29
  br label %if.end37, !dbg !3114

if.end37:                                         ; preds = %if.end36, %if.end18
  %46 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3115
  %47 = bitcast %struct.lzma_stream* %46 to i8*, !dbg !3116
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %47, i8* bitcast (%struct.lzma_stream* @compression_init_encoder_lzma.lzma_init_data to i8*), i64 136, i32 8, i1 false), !dbg !3116
  %48 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3117
  %49 = load %struct.lzma_filter*, %struct.lzma_filter** %lzmafilters, align 8, !dbg !3118
  %call38 = call i32 @lzma_raw_encoder(%struct.lzma_stream* %48, %struct.lzma_filter* %49) #8, !dbg !3119
  store i32 %call38, i32* %r, align 4, !dbg !3120
  %50 = load i32, i32* %r, align 4, !dbg !3121
  switch i32 %50, label %sw.default [
    i32 0, label %sw.bb
    i32 5, label %sw.bb41
  ], !dbg !3122

sw.bb:                                            ; preds = %if.end37
  %51 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3123
  %52 = bitcast %struct.lzma_stream* %51 to i8*, !dbg !3123
  %53 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3125
  %real_stream39 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %53, i32 0, i32 9, !dbg !3126
  store i8* %52, i8** %real_stream39, align 8, !dbg !3127
  %54 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3128
  %valid40 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %54, i32 0, i32 8, !dbg !3129
  store i32 1, i32* %valid40, align 8, !dbg !3130
  %55 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3131
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %55, i32 0, i32 10, !dbg !3132
  store i32 (%struct.archive*, %struct.la_zstream*, i32)* @compression_code_lzma, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !3133
  %56 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3134
  %end = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %56, i32 0, i32 11, !dbg !3135
  store i32 (%struct.archive*, %struct.la_zstream*)* @compression_end_lzma, i32 (%struct.archive*, %struct.la_zstream*)** %end, align 8, !dbg !3136
  store i32 0, i32* %r, align 4, !dbg !3137
  br label %sw.epilog, !dbg !3138

sw.bb41:                                          ; preds = %if.end37
  %57 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3139
  %58 = bitcast %struct.lzma_stream* %57 to i8*, !dbg !3139
  call void @free(i8* %58) #8, !dbg !3140
  %59 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3141
  %real_stream42 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %59, i32 0, i32 9, !dbg !3142
  store i8* null, i8** %real_stream42, align 8, !dbg !3143
  %60 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3144
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %60, i32 12, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.39, i32 0, i32 0)), !dbg !3145
  store i32 -30, i32* %r, align 4, !dbg !3146
  br label %sw.epilog, !dbg !3147

sw.default:                                       ; preds = %if.end37
  %61 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3148
  %62 = bitcast %struct.lzma_stream* %61 to i8*, !dbg !3148
  call void @free(i8* %62) #8, !dbg !3149
  %63 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3150
  %real_stream43 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %63, i32 0, i32 9, !dbg !3151
  store i8* null, i8** %real_stream43, align 8, !dbg !3152
  %64 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3153
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %64, i32 -1, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.40, i32 0, i32 0)), !dbg !3154
  store i32 -30, i32* %r, align 4, !dbg !3155
  br label %sw.epilog, !dbg !3156

sw.epilog:                                        ; preds = %sw.default, %sw.bb41, %sw.bb
  %65 = load i32, i32* %r, align 4, !dbg !3157
  store i32 %65, i32* %retval, align 4, !dbg !3158
  br label %return, !dbg !3158

return:                                           ; preds = %sw.epilog, %if.then34, %if.then27, %if.then16, %if.then9, %if.then2
  %66 = load i32, i32* %retval, align 4, !dbg !3159
  ret i32 %66, !dbg !3159
}

; Function Attrs: nounwind
declare zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma*, i32) #3

; Function Attrs: nounwind
declare i32 @lzma_properties_size(i32*, %struct.lzma_filter*) #3

; Function Attrs: nounwind
declare i32 @lzma_properties_encode(%struct.lzma_filter*, i8*) #3

; Function Attrs: nounwind
declare i32 @lzma_raw_encoder(%struct.lzma_stream*, %struct.lzma_filter*) #3

; Function Attrs: nounwind uwtable
define internal i32 @compression_code_lzma(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !611 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  %strm = alloca %struct.lzma_stream*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3160, metadata !693), !dbg !3161
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3162, metadata !693), !dbg !3163
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !3164, metadata !693), !dbg !3165
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm, metadata !3166, metadata !693), !dbg !3167
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3168, metadata !693), !dbg !3169
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3170
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 9, !dbg !3171
  %1 = load i8*, i8** %real_stream, align 8, !dbg !3171
  %2 = bitcast i8* %1 to %struct.lzma_stream*, !dbg !3172
  store %struct.lzma_stream* %2, %struct.lzma_stream** %strm, align 8, !dbg !3173
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3174
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %3, i32 0, i32 0, !dbg !3175
  %4 = load i8*, i8** %next_in, align 8, !dbg !3175
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3176
  %next_in1 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 0, !dbg !3177
  store i8* %4, i8** %next_in1, align 8, !dbg !3178
  %6 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3179
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %6, i32 0, i32 1, !dbg !3180
  %7 = load i64, i64* %avail_in, align 8, !dbg !3180
  %8 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3181
  %avail_in2 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %8, i32 0, i32 1, !dbg !3182
  store i64 %7, i64* %avail_in2, align 8, !dbg !3183
  %9 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3184
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %9, i32 0, i32 2, !dbg !3185
  %10 = load i64, i64* %total_in, align 8, !dbg !3185
  %11 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3186
  %total_in3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %11, i32 0, i32 2, !dbg !3187
  store i64 %10, i64* %total_in3, align 8, !dbg !3188
  %12 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3189
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %12, i32 0, i32 3, !dbg !3190
  %13 = load i8*, i8** %next_out, align 8, !dbg !3190
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3191
  %next_out4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 3, !dbg !3192
  store i8* %13, i8** %next_out4, align 8, !dbg !3193
  %15 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3194
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %15, i32 0, i32 4, !dbg !3195
  %16 = load i64, i64* %avail_out, align 8, !dbg !3195
  %17 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3196
  %avail_out5 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %17, i32 0, i32 4, !dbg !3197
  store i64 %16, i64* %avail_out5, align 8, !dbg !3198
  %18 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3199
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %18, i32 0, i32 5, !dbg !3200
  %19 = load i64, i64* %total_out, align 8, !dbg !3200
  %20 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3201
  %total_out6 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %20, i32 0, i32 5, !dbg !3202
  store i64 %19, i64* %total_out6, align 8, !dbg !3203
  %21 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3204
  %22 = load i32, i32* %action.addr, align 4, !dbg !3205
  %cmp = icmp eq i32 %22, 0, !dbg !3206
  %cond = select i1 %cmp, i32 3, i32 0, !dbg !3207
  %call = call i32 @lzma_code(%struct.lzma_stream* %21, i32 %cond) #8, !dbg !3208
  store i32 %call, i32* %r, align 4, !dbg !3209
  %23 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3210
  %next_in7 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %23, i32 0, i32 0, !dbg !3211
  %24 = load i8*, i8** %next_in7, align 8, !dbg !3211
  %25 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3212
  %next_in8 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %25, i32 0, i32 0, !dbg !3213
  store i8* %24, i8** %next_in8, align 8, !dbg !3214
  %26 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3215
  %avail_in9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %26, i32 0, i32 1, !dbg !3216
  %27 = load i64, i64* %avail_in9, align 8, !dbg !3216
  %28 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3217
  %avail_in10 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %28, i32 0, i32 1, !dbg !3218
  store i64 %27, i64* %avail_in10, align 8, !dbg !3219
  %29 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3220
  %total_in11 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %29, i32 0, i32 2, !dbg !3221
  %30 = load i64, i64* %total_in11, align 8, !dbg !3221
  %31 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3222
  %total_in12 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %31, i32 0, i32 2, !dbg !3223
  store i64 %30, i64* %total_in12, align 8, !dbg !3224
  %32 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3225
  %next_out13 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %32, i32 0, i32 3, !dbg !3226
  %33 = load i8*, i8** %next_out13, align 8, !dbg !3226
  %34 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3227
  %next_out14 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %34, i32 0, i32 3, !dbg !3228
  store i8* %33, i8** %next_out14, align 8, !dbg !3229
  %35 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3230
  %avail_out15 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %35, i32 0, i32 4, !dbg !3231
  %36 = load i64, i64* %avail_out15, align 8, !dbg !3231
  %37 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3232
  %avail_out16 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %37, i32 0, i32 4, !dbg !3233
  store i64 %36, i64* %avail_out16, align 8, !dbg !3234
  %38 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3235
  %total_out17 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %38, i32 0, i32 5, !dbg !3236
  %39 = load i64, i64* %total_out17, align 8, !dbg !3236
  %40 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3237
  %total_out18 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %40, i32 0, i32 5, !dbg !3238
  store i64 %39, i64* %total_out18, align 8, !dbg !3239
  %41 = load i32, i32* %r, align 4, !dbg !3240
  switch i32 %41, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb19
    i32 6, label %sw.bb20
  ], !dbg !3241

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3242
  br label %return, !dbg !3242

sw.bb19:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3244
  br label %return, !dbg !3244

sw.bb20:                                          ; preds = %entry
  %42 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3245
  %43 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3246
  %call21 = call i64 @lzma_memusage(%struct.lzma_stream* %43) #9, !dbg !3247
  %add = add i64 %call21, 1048576, !dbg !3248
  %sub = sub i64 %add, 1, !dbg !3249
  %div = udiv i64 %sub, 1048576, !dbg !3250
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %42, i32 12, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.41, i32 0, i32 0), i64 %div), !dbg !3251
  store i32 -30, i32* %retval, align 4, !dbg !3252
  br label %return, !dbg !3252

sw.default:                                       ; preds = %entry
  %44 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3253
  %45 = load i32, i32* %r, align 4, !dbg !3254
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %44, i32 -1, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.42, i32 0, i32 0), i32 %45), !dbg !3255
  store i32 -30, i32* %retval, align 4, !dbg !3256
  br label %return, !dbg !3256

return:                                           ; preds = %sw.default, %sw.bb20, %sw.bb19, %sw.bb
  %46 = load i32, i32* %retval, align 4, !dbg !3257
  ret i32 %46, !dbg !3257
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end_lzma(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !612 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %strm = alloca %struct.lzma_stream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3258, metadata !693), !dbg !3259
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3260, metadata !693), !dbg !3261
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm, metadata !3262, metadata !693), !dbg !3263
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3264
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3265
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %1, i32 0, i32 9, !dbg !3266
  %2 = load i8*, i8** %real_stream, align 8, !dbg !3266
  %3 = bitcast i8* %2 to %struct.lzma_stream*, !dbg !3267
  store %struct.lzma_stream* %3, %struct.lzma_stream** %strm, align 8, !dbg !3268
  %4 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3269
  call void @lzma_end(%struct.lzma_stream* %4) #8, !dbg !3270
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm, align 8, !dbg !3271
  %6 = bitcast %struct.lzma_stream* %5 to i8*, !dbg !3271
  call void @free(i8* %6) #8, !dbg !3272
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3273
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 8, !dbg !3274
  store i32 0, i32* %valid, align 8, !dbg !3275
  %8 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3276
  %real_stream1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %8, i32 0, i32 9, !dbg !3277
  store i8* null, i8** %real_stream1, align 8, !dbg !3278
  ret i32 0, !dbg !3279
}

; Function Attrs: nounwind
declare i32 @lzma_code(%struct.lzma_stream*, i32) #3

; Function Attrs: nounwind readonly
declare i64 @lzma_memusage(%struct.lzma_stream*) #4

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le32enc(i8* %pp, i32 %u) #7 !dbg !617 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3280, metadata !693), !dbg !3281
  store i32 %u, i32* %u.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %u.addr, metadata !3282, metadata !693), !dbg !3283
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3284, metadata !693), !dbg !3285
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3286
  store i8* %0, i8** %p, align 8, !dbg !3285
  %1 = load i32, i32* %u.addr, align 4, !dbg !3287
  %and = and i32 %1, 255, !dbg !3288
  %conv = trunc i32 %and to i8, !dbg !3287
  %2 = load i8*, i8** %p, align 8, !dbg !3289
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !3289
  store i8 %conv, i8* %arrayidx, align 1, !dbg !3290
  %3 = load i32, i32* %u.addr, align 4, !dbg !3291
  %shr = lshr i32 %3, 8, !dbg !3292
  %and1 = and i32 %shr, 255, !dbg !3293
  %conv2 = trunc i32 %and1 to i8, !dbg !3294
  %4 = load i8*, i8** %p, align 8, !dbg !3295
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !3295
  store i8 %conv2, i8* %arrayidx3, align 1, !dbg !3296
  %5 = load i32, i32* %u.addr, align 4, !dbg !3297
  %shr4 = lshr i32 %5, 16, !dbg !3298
  %and5 = and i32 %shr4, 255, !dbg !3299
  %conv6 = trunc i32 %and5 to i8, !dbg !3300
  %6 = load i8*, i8** %p, align 8, !dbg !3301
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 2, !dbg !3301
  store i8 %conv6, i8* %arrayidx7, align 1, !dbg !3302
  %7 = load i32, i32* %u.addr, align 4, !dbg !3303
  %shr8 = lshr i32 %7, 24, !dbg !3304
  %and9 = and i32 %shr8, 255, !dbg !3305
  %conv10 = trunc i32 %and9 to i8, !dbg !3306
  %8 = load i8*, i8** %p, align 8, !dbg !3307
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 3, !dbg !3307
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !3308
  ret void, !dbg !3309
}

; Function Attrs: nounwind uwtable
define internal void @ppmd_write(i8* %p, i8 zeroext %b) #0 !dbg !625 {
entry:
  %p.addr = alloca i8*, align 8
  %b.addr = alloca i8, align 1
  %a = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  %lastrm = alloca %struct.la_zstream*, align 8
  %strm = alloca %struct.ppmd_stream*, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3310, metadata !693), !dbg !3311
  store i8 %b, i8* %b.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %b.addr, metadata !3312, metadata !693), !dbg !3313
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !3314, metadata !693), !dbg !3315
  %0 = load i8*, i8** %p.addr, align 8, !dbg !3316
  %1 = bitcast i8* %0 to %struct.IByteOut*, !dbg !3317
  %a1 = getelementptr inbounds %struct.IByteOut, %struct.IByteOut* %1, i32 0, i32 0, !dbg !3318
  %2 = load %struct.archive_write*, %struct.archive_write** %a1, align 8, !dbg !3318
  store %struct.archive_write* %2, %struct.archive_write** %a, align 8, !dbg !3315
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !3319, metadata !693), !dbg !3320
  %3 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !3321
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %3, i32 0, i32 14, !dbg !3322
  %4 = load i8*, i8** %format_data, align 8, !dbg !3322
  %5 = bitcast i8* %4 to %struct._7zip*, !dbg !3323
  store %struct._7zip* %5, %struct._7zip** %zip, align 8, !dbg !3320
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm, metadata !3324, metadata !693), !dbg !3325
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3326
  %stream = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 18, !dbg !3327
  store %struct.la_zstream* %stream, %struct.la_zstream** %lastrm, align 8, !dbg !3325
  call void @llvm.dbg.declare(metadata %struct.ppmd_stream** %strm, metadata !3328, metadata !693), !dbg !3329
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm, align 8, !dbg !3330
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 4, !dbg !3332
  %8 = load i64, i64* %avail_out, align 8, !dbg !3332
  %tobool = icmp ne i64 %8, 0, !dbg !3330
  br i1 %tobool, label %if.then, label %if.end, !dbg !3333

if.then:                                          ; preds = %entry
  %9 = load i8, i8* %b.addr, align 1, !dbg !3334
  %10 = load %struct.la_zstream*, %struct.la_zstream** %lastrm, align 8, !dbg !3336
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %10, i32 0, i32 3, !dbg !3337
  %11 = load i8*, i8** %next_out, align 8, !dbg !3338
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !3338
  store i8* %incdec.ptr, i8** %next_out, align 8, !dbg !3338
  store i8 %9, i8* %11, align 1, !dbg !3339
  %12 = load %struct.la_zstream*, %struct.la_zstream** %lastrm, align 8, !dbg !3340
  %avail_out2 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %12, i32 0, i32 4, !dbg !3341
  %13 = load i64, i64* %avail_out2, align 8, !dbg !3342
  %dec = add i64 %13, -1, !dbg !3342
  store i64 %dec, i64* %avail_out2, align 8, !dbg !3342
  %14 = load %struct.la_zstream*, %struct.la_zstream** %lastrm, align 8, !dbg !3343
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %14, i32 0, i32 5, !dbg !3344
  %15 = load i64, i64* %total_out, align 8, !dbg !3345
  %inc = add i64 %15, 1, !dbg !3345
  store i64 %inc, i64* %total_out, align 8, !dbg !3345
  br label %if.end7, !dbg !3346

if.end:                                           ; preds = %entry
  %16 = load %struct.la_zstream*, %struct.la_zstream** %lastrm, align 8, !dbg !3347
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %16, i32 0, i32 9, !dbg !3348
  %17 = load i8*, i8** %real_stream, align 8, !dbg !3348
  %18 = bitcast i8* %17 to %struct.ppmd_stream*, !dbg !3349
  store %struct.ppmd_stream* %18, %struct.ppmd_stream** %strm, align 8, !dbg !3350
  %19 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3351
  %buff_ptr = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %19, i32 0, i32 5, !dbg !3353
  %20 = load i8*, i8** %buff_ptr, align 8, !dbg !3353
  %21 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3354
  %buff_end = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %21, i32 0, i32 6, !dbg !3355
  %22 = load i8*, i8** %buff_end, align 8, !dbg !3355
  %cmp = icmp ult i8* %20, %22, !dbg !3356
  br i1 %cmp, label %if.then3, label %if.end7, !dbg !3357

if.then3:                                         ; preds = %if.end
  %23 = load i8, i8* %b.addr, align 1, !dbg !3358
  %24 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3360
  %buff_ptr4 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %24, i32 0, i32 5, !dbg !3361
  %25 = load i8*, i8** %buff_ptr4, align 8, !dbg !3362
  %incdec.ptr5 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !3362
  store i8* %incdec.ptr5, i8** %buff_ptr4, align 8, !dbg !3362
  store i8 %23, i8* %25, align 1, !dbg !3363
  %26 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3364
  %buff_bytes = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %26, i32 0, i32 7, !dbg !3365
  %27 = load i64, i64* %buff_bytes, align 8, !dbg !3366
  %inc6 = add i64 %27, 1, !dbg !3366
  store i64 %inc6, i64* %buff_bytes, align 8, !dbg !3366
  br label %if.end7, !dbg !3367

if.end7:                                          ; preds = %if.then, %if.then3, %if.end
  ret void, !dbg !3368
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_code_ppmd(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !626 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  %strm = alloca %struct.ppmd_stream*, align 8
  %p = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3369, metadata !693), !dbg !3370
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3371, metadata !693), !dbg !3372
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !3373, metadata !693), !dbg !3374
  call void @llvm.dbg.declare(metadata %struct.ppmd_stream** %strm, metadata !3375, metadata !693), !dbg !3376
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3377
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3378
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %1, i32 0, i32 9, !dbg !3379
  %2 = load i8*, i8** %real_stream, align 8, !dbg !3379
  %3 = bitcast i8* %2 to %struct.ppmd_stream*, !dbg !3380
  store %struct.ppmd_stream* %3, %struct.ppmd_stream** %strm, align 8, !dbg !3381
  %4 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3382
  %buff_bytes = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %4, i32 0, i32 7, !dbg !3384
  %5 = load i64, i64* %buff_bytes, align 8, !dbg !3384
  %tobool = icmp ne i64 %5, 0, !dbg !3382
  br i1 %tobool, label %if.then, label %if.end15, !dbg !3385

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3386, metadata !693), !dbg !3388
  %6 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3389
  %buff_ptr = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %6, i32 0, i32 5, !dbg !3390
  %7 = load i8*, i8** %buff_ptr, align 8, !dbg !3390
  %8 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3391
  %buff_bytes1 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %8, i32 0, i32 7, !dbg !3392
  %9 = load i64, i64* %buff_bytes1, align 8, !dbg !3392
  %idx.neg = sub i64 0, %9, !dbg !3393
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %idx.neg, !dbg !3393
  store i8* %add.ptr, i8** %p, align 8, !dbg !3388
  br label %while.cond, !dbg !3394

while.cond:                                       ; preds = %while.body, %if.then
  %10 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3395
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %10, i32 0, i32 4, !dbg !3397
  %11 = load i64, i64* %avail_out, align 8, !dbg !3397
  %tobool2 = icmp ne i64 %11, 0, !dbg !3395
  br i1 %tobool2, label %land.rhs, label %land.end, !dbg !3398

land.rhs:                                         ; preds = %while.cond
  %12 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3399
  %buff_bytes3 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %12, i32 0, i32 7, !dbg !3401
  %13 = load i64, i64* %buff_bytes3, align 8, !dbg !3401
  %tobool4 = icmp ne i64 %13, 0, !dbg !3402
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %14 = phi i1 [ false, %while.cond ], [ %tobool4, %land.rhs ]
  br i1 %14, label %while.body, label %while.end, !dbg !3403

while.body:                                       ; preds = %land.end
  %15 = load i8*, i8** %p, align 8, !dbg !3405
  %incdec.ptr = getelementptr inbounds i8, i8* %15, i32 1, !dbg !3405
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3405
  %16 = load i8, i8* %15, align 1, !dbg !3407
  %17 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3408
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %17, i32 0, i32 3, !dbg !3409
  %18 = load i8*, i8** %next_out, align 8, !dbg !3410
  %incdec.ptr5 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !3410
  store i8* %incdec.ptr5, i8** %next_out, align 8, !dbg !3410
  store i8 %16, i8* %18, align 1, !dbg !3411
  %19 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3412
  %avail_out6 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %19, i32 0, i32 4, !dbg !3413
  %20 = load i64, i64* %avail_out6, align 8, !dbg !3414
  %dec = add i64 %20, -1, !dbg !3414
  store i64 %dec, i64* %avail_out6, align 8, !dbg !3414
  %21 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3415
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %21, i32 0, i32 5, !dbg !3416
  %22 = load i64, i64* %total_out, align 8, !dbg !3417
  %inc = add i64 %22, 1, !dbg !3417
  store i64 %inc, i64* %total_out, align 8, !dbg !3417
  %23 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3418
  %buff_bytes7 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %23, i32 0, i32 7, !dbg !3419
  %24 = load i64, i64* %buff_bytes7, align 8, !dbg !3420
  %dec8 = add i64 %24, -1, !dbg !3420
  store i64 %dec8, i64* %buff_bytes7, align 8, !dbg !3420
  br label %while.cond, !dbg !3421

while.end:                                        ; preds = %land.end
  %25 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3423
  %buff_bytes9 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %25, i32 0, i32 7, !dbg !3425
  %26 = load i64, i64* %buff_bytes9, align 8, !dbg !3425
  %tobool10 = icmp ne i64 %26, 0, !dbg !3423
  br i1 %tobool10, label %if.then11, label %if.end, !dbg !3426

if.then11:                                        ; preds = %while.end
  store i32 0, i32* %retval, align 4, !dbg !3427
  br label %return, !dbg !3427

if.end:                                           ; preds = %while.end
  %27 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3428
  %stat = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %27, i32 0, i32 0, !dbg !3430
  %28 = load i32, i32* %stat, align 8, !dbg !3430
  %cmp = icmp eq i32 %28, 1, !dbg !3431
  br i1 %cmp, label %if.then12, label %if.end13, !dbg !3432

if.then12:                                        ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !3433
  br label %return, !dbg !3433

if.end13:                                         ; preds = %if.end
  %29 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3434
  %buff = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %29, i32 0, i32 4, !dbg !3435
  %30 = load i8*, i8** %buff, align 8, !dbg !3435
  %31 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3436
  %buff_ptr14 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %31, i32 0, i32 5, !dbg !3437
  store i8* %30, i8** %buff_ptr14, align 8, !dbg !3438
  br label %if.end15, !dbg !3439

if.end15:                                         ; preds = %if.end13, %entry
  br label %while.cond16, !dbg !3440

while.cond16:                                     ; preds = %while.body22, %if.end15
  %32 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3441
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %32, i32 0, i32 1, !dbg !3443
  %33 = load i64, i64* %avail_in, align 8, !dbg !3443
  %tobool17 = icmp ne i64 %33, 0, !dbg !3441
  br i1 %tobool17, label %land.rhs18, label %land.end21, !dbg !3444

land.rhs18:                                       ; preds = %while.cond16
  %34 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3445
  %avail_out19 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %34, i32 0, i32 4, !dbg !3447
  %35 = load i64, i64* %avail_out19, align 8, !dbg !3447
  %tobool20 = icmp ne i64 %35, 0, !dbg !3448
  br label %land.end21

land.end21:                                       ; preds = %land.rhs18, %while.cond16
  %36 = phi i1 [ false, %while.cond16 ], [ %tobool20, %land.rhs18 ]
  br i1 %36, label %while.body22, label %while.end27, !dbg !3449

while.body22:                                     ; preds = %land.end21
  %37 = load void (%struct.CPpmd7*, %struct.CPpmd7z_RangeEnc*, i32)*, void (%struct.CPpmd7*, %struct.CPpmd7z_RangeEnc*, i32)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 11), align 8, !dbg !3451
  %38 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3453
  %ppmd7_context = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %38, i32 0, i32 1, !dbg !3454
  %39 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3455
  %range_enc = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %39, i32 0, i32 2, !dbg !3456
  %40 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3457
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %40, i32 0, i32 0, !dbg !3458
  %41 = load i8*, i8** %next_in, align 8, !dbg !3459
  %incdec.ptr23 = getelementptr inbounds i8, i8* %41, i32 1, !dbg !3459
  store i8* %incdec.ptr23, i8** %next_in, align 8, !dbg !3459
  %42 = load i8, i8* %41, align 1, !dbg !3460
  %conv = zext i8 %42 to i32, !dbg !3460
  call void %37(%struct.CPpmd7* %ppmd7_context, %struct.CPpmd7z_RangeEnc* %range_enc, i32 %conv), !dbg !3461
  %43 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3462
  %avail_in24 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %43, i32 0, i32 1, !dbg !3463
  %44 = load i64, i64* %avail_in24, align 8, !dbg !3464
  %dec25 = add i64 %44, -1, !dbg !3464
  store i64 %dec25, i64* %avail_in24, align 8, !dbg !3464
  %45 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3465
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %45, i32 0, i32 2, !dbg !3466
  %46 = load i64, i64* %total_in, align 8, !dbg !3467
  %inc26 = add i64 %46, 1, !dbg !3467
  store i64 %inc26, i64* %total_in, align 8, !dbg !3467
  br label %while.cond16, !dbg !3468

while.end27:                                      ; preds = %land.end21
  %47 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3470
  %avail_in28 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %47, i32 0, i32 1, !dbg !3472
  %48 = load i64, i64* %avail_in28, align 8, !dbg !3472
  %cmp29 = icmp eq i64 %48, 0, !dbg !3473
  br i1 %cmp29, label %land.lhs.true, label %if.end41, !dbg !3474

land.lhs.true:                                    ; preds = %while.end27
  %49 = load i32, i32* %action.addr, align 4, !dbg !3475
  %cmp31 = icmp eq i32 %49, 0, !dbg !3477
  br i1 %cmp31, label %if.then33, label %if.end41, !dbg !3478

if.then33:                                        ; preds = %land.lhs.true
  %50 = load void (%struct.CPpmd7z_RangeEnc*)*, void (%struct.CPpmd7z_RangeEnc*)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 10), align 8, !dbg !3479
  %51 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3481
  %range_enc34 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %51, i32 0, i32 2, !dbg !3482
  call void %50(%struct.CPpmd7z_RangeEnc* %range_enc34), !dbg !3483
  %52 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3484
  %stat35 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %52, i32 0, i32 0, !dbg !3485
  store i32 1, i32* %stat35, align 8, !dbg !3486
  %53 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3487
  %buff_bytes36 = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %53, i32 0, i32 7, !dbg !3489
  %54 = load i64, i64* %buff_bytes36, align 8, !dbg !3489
  %cmp37 = icmp eq i64 %54, 0, !dbg !3490
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !3491

if.then39:                                        ; preds = %if.then33
  store i32 1, i32* %retval, align 4, !dbg !3492
  br label %return, !dbg !3492

if.end40:                                         ; preds = %if.then33
  br label %if.end41, !dbg !3493

if.end41:                                         ; preds = %if.end40, %land.lhs.true, %while.end27
  store i32 0, i32* %retval, align 4, !dbg !3494
  br label %return, !dbg !3494

return:                                           ; preds = %if.end41, %if.then39, %if.then12, %if.then11
  %55 = load i32, i32* %retval, align 4, !dbg !3495
  ret i32 %55, !dbg !3495
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end_ppmd(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !627 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %strm = alloca %struct.ppmd_stream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3496, metadata !693), !dbg !3497
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3498, metadata !693), !dbg !3499
  call void @llvm.dbg.declare(metadata %struct.ppmd_stream** %strm, metadata !3500, metadata !693), !dbg !3501
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3502
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3503
  %real_stream = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %1, i32 0, i32 9, !dbg !3504
  %2 = load i8*, i8** %real_stream, align 8, !dbg !3504
  %3 = bitcast i8* %2 to %struct.ppmd_stream*, !dbg !3505
  store %struct.ppmd_stream* %3, %struct.ppmd_stream** %strm, align 8, !dbg !3506
  %4 = load void (%struct.CPpmd7*, %struct.ISzAlloc*)*, void (%struct.CPpmd7*, %struct.ISzAlloc*)** getelementptr inbounds (%struct.IPpmd7, %struct.IPpmd7* @__archive_ppmd7_functions, i32 0, i32 2), align 8, !dbg !3507
  %5 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3508
  %ppmd7_context = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %5, i32 0, i32 1, !dbg !3509
  call void %4(%struct.CPpmd7* %ppmd7_context, %struct.ISzAlloc* @g_szalloc), !dbg !3510
  %6 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3511
  %buff = getelementptr inbounds %struct.ppmd_stream, %struct.ppmd_stream* %6, i32 0, i32 4, !dbg !3512
  %7 = load i8*, i8** %buff, align 8, !dbg !3512
  call void @free(i8* %7) #8, !dbg !3513
  %8 = load %struct.ppmd_stream*, %struct.ppmd_stream** %strm, align 8, !dbg !3514
  %9 = bitcast %struct.ppmd_stream* %8 to i8*, !dbg !3514
  call void @free(i8* %9) #8, !dbg !3515
  %10 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3516
  %real_stream1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %10, i32 0, i32 9, !dbg !3517
  store i8* null, i8** %real_stream1, align 8, !dbg !3518
  %11 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3519
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %11, i32 0, i32 8, !dbg !3520
  store i32 0, i32* %valid, align 8, !dbg !3521
  ret i32 0, !dbg !3522
}

; Function Attrs: nounwind uwtable
define internal i8* @ppmd_alloc(i8* %p, i64 %size) #0 !dbg !621 {
entry:
  %p.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3523, metadata !693), !dbg !3524
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !3525, metadata !693), !dbg !3526
  %0 = load i8*, i8** %p.addr, align 8, !dbg !3527
  %1 = load i64, i64* %size.addr, align 8, !dbg !3528
  %call = call noalias i8* @malloc(i64 %1) #8, !dbg !3529
  ret i8* %call, !dbg !3530
}

; Function Attrs: nounwind uwtable
define internal void @ppmd_free(i8* %p, i8* %address) #0 !dbg !624 {
entry:
  %p.addr = alloca i8*, align 8
  %address.addr = alloca i8*, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3531, metadata !693), !dbg !3532
  store i8* %address, i8** %address.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %address.addr, metadata !3533, metadata !693), !dbg !3534
  %0 = load i8*, i8** %p.addr, align 8, !dbg !3535
  %1 = load i8*, i8** %address.addr, align 8, !dbg !3536
  call void @free(i8* %1) #8, !dbg !3537
  ret void, !dbg !3538
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_code_copy(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !629 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  %bytes = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3539, metadata !693), !dbg !3540
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3541, metadata !693), !dbg !3542
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !3543, metadata !693), !dbg !3544
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !3545, metadata !693), !dbg !3546
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3547
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3548
  %avail_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %1, i32 0, i32 4, !dbg !3550
  %2 = load i64, i64* %avail_out, align 8, !dbg !3550
  %3 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3551
  %avail_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %3, i32 0, i32 1, !dbg !3552
  %4 = load i64, i64* %avail_in, align 8, !dbg !3552
  %cmp = icmp ugt i64 %2, %4, !dbg !3553
  br i1 %cmp, label %if.then, label %if.else, !dbg !3554

if.then:                                          ; preds = %entry
  %5 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3555
  %avail_in1 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %5, i32 0, i32 1, !dbg !3556
  %6 = load i64, i64* %avail_in1, align 8, !dbg !3556
  store i64 %6, i64* %bytes, align 8, !dbg !3557
  br label %if.end, !dbg !3558

if.else:                                          ; preds = %entry
  %7 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3559
  %avail_out2 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %7, i32 0, i32 4, !dbg !3560
  %8 = load i64, i64* %avail_out2, align 8, !dbg !3560
  store i64 %8, i64* %bytes, align 8, !dbg !3561
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %9 = load i64, i64* %bytes, align 8, !dbg !3562
  %tobool = icmp ne i64 %9, 0, !dbg !3562
  br i1 %tobool, label %if.then3, label %if.end11, !dbg !3564

if.then3:                                         ; preds = %if.end
  %10 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3565
  %next_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %10, i32 0, i32 3, !dbg !3567
  %11 = load i8*, i8** %next_out, align 8, !dbg !3567
  %12 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3568
  %next_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %12, i32 0, i32 0, !dbg !3569
  %13 = load i8*, i8** %next_in, align 8, !dbg !3569
  %14 = load i64, i64* %bytes, align 8, !dbg !3570
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* %13, i64 %14, i32 1, i1 false), !dbg !3571
  %15 = load i64, i64* %bytes, align 8, !dbg !3572
  %16 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3573
  %next_in4 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %16, i32 0, i32 0, !dbg !3574
  %17 = load i8*, i8** %next_in4, align 8, !dbg !3575
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %15, !dbg !3575
  store i8* %add.ptr, i8** %next_in4, align 8, !dbg !3575
  %18 = load i64, i64* %bytes, align 8, !dbg !3576
  %19 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3577
  %avail_in5 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %19, i32 0, i32 1, !dbg !3578
  %20 = load i64, i64* %avail_in5, align 8, !dbg !3579
  %sub = sub i64 %20, %18, !dbg !3579
  store i64 %sub, i64* %avail_in5, align 8, !dbg !3579
  %21 = load i64, i64* %bytes, align 8, !dbg !3580
  %22 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3581
  %total_in = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %22, i32 0, i32 2, !dbg !3582
  %23 = load i64, i64* %total_in, align 8, !dbg !3583
  %add = add i64 %23, %21, !dbg !3583
  store i64 %add, i64* %total_in, align 8, !dbg !3583
  %24 = load i64, i64* %bytes, align 8, !dbg !3584
  %25 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3585
  %next_out6 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %25, i32 0, i32 3, !dbg !3586
  %26 = load i8*, i8** %next_out6, align 8, !dbg !3587
  %add.ptr7 = getelementptr inbounds i8, i8* %26, i64 %24, !dbg !3587
  store i8* %add.ptr7, i8** %next_out6, align 8, !dbg !3587
  %27 = load i64, i64* %bytes, align 8, !dbg !3588
  %28 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3589
  %avail_out8 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %28, i32 0, i32 4, !dbg !3590
  %29 = load i64, i64* %avail_out8, align 8, !dbg !3591
  %sub9 = sub i64 %29, %27, !dbg !3591
  store i64 %sub9, i64* %avail_out8, align 8, !dbg !3591
  %30 = load i64, i64* %bytes, align 8, !dbg !3592
  %31 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3593
  %total_out = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %31, i32 0, i32 5, !dbg !3594
  %32 = load i64, i64* %total_out, align 8, !dbg !3595
  %add10 = add i64 %32, %30, !dbg !3595
  store i64 %add10, i64* %total_out, align 8, !dbg !3595
  br label %if.end11, !dbg !3596

if.end11:                                         ; preds = %if.then3, %if.end
  %33 = load i32, i32* %action.addr, align 4, !dbg !3597
  %cmp12 = icmp eq i32 %33, 0, !dbg !3599
  br i1 %cmp12, label %land.lhs.true, label %if.end16, !dbg !3600

land.lhs.true:                                    ; preds = %if.end11
  %34 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3601
  %avail_in13 = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %34, i32 0, i32 1, !dbg !3603
  %35 = load i64, i64* %avail_in13, align 8, !dbg !3603
  %cmp14 = icmp eq i64 %35, 0, !dbg !3604
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !3605

if.then15:                                        ; preds = %land.lhs.true
  store i32 1, i32* %retval, align 4, !dbg !3606
  br label %return, !dbg !3606

if.end16:                                         ; preds = %land.lhs.true, %if.end11
  store i32 0, i32* %retval, align 4, !dbg !3607
  br label %return, !dbg !3607

return:                                           ; preds = %if.end16, %if.then15
  %36 = load i32, i32* %retval, align 4, !dbg !3608
  ret i32 %36, !dbg !3608
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_end_copy(%struct.archive* %a, %struct.la_zstream* %lastrm) #0 !dbg !630 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3609, metadata !693), !dbg !3610
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3611, metadata !693), !dbg !3612
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3613
  %1 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3614
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %1, i32 0, i32 8, !dbg !3615
  store i32 0, i32* %valid, align 8, !dbg !3616
  ret i32 0, !dbg !3617
}

; Function Attrs: nounwind uwtable
define internal i32 @compression_code(%struct.archive* %a, %struct.la_zstream* %lastrm, i32 %action) #0 !dbg !635 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %lastrm.addr = alloca %struct.la_zstream*, align 8
  %action.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !3618, metadata !693), !dbg !3619
  store %struct.la_zstream* %lastrm, %struct.la_zstream** %lastrm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.la_zstream** %lastrm.addr, metadata !3620, metadata !693), !dbg !3621
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !3622, metadata !693), !dbg !3623
  %0 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3624
  %valid = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %0, i32 0, i32 8, !dbg !3626
  %1 = load i32, i32* %valid, align 8, !dbg !3626
  %tobool = icmp ne i32 %1, 0, !dbg !3624
  br i1 %tobool, label %if.then, label %if.end, !dbg !3627

if.then:                                          ; preds = %entry
  %2 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3628
  %code = getelementptr inbounds %struct.la_zstream, %struct.la_zstream* %2, i32 0, i32 10, !dbg !3629
  %3 = load i32 (%struct.archive*, %struct.la_zstream*, i32)*, i32 (%struct.archive*, %struct.la_zstream*, i32)** %code, align 8, !dbg !3629
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !3630
  %5 = load %struct.la_zstream*, %struct.la_zstream** %lastrm.addr, align 8, !dbg !3631
  %6 = load i32, i32* %action.addr, align 4, !dbg !3632
  %call = call i32 %3(%struct.archive* %4, %struct.la_zstream* %5, i32 %6), !dbg !3628
  store i32 %call, i32* %retval, align 4, !dbg !3633
  br label %return, !dbg !3633

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3634
  br label %return, !dbg !3634

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3635
  ret i32 %7, !dbg !3635
}

; Function Attrs: nounwind uwtable
define internal i32 @write_to_temp(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !636 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %zip = alloca %struct._7zip*, align 8
  %p = alloca i8*, align 8
  %ws = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3636, metadata !693), !dbg !3637
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !3638, metadata !693), !dbg !3639
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !3640, metadata !693), !dbg !3641
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !3642, metadata !693), !dbg !3643
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3644, metadata !693), !dbg !3645
  call void @llvm.dbg.declare(metadata i64* %ws, metadata !3646, metadata !693), !dbg !3647
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3648
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3649
  %1 = load i8*, i8** %format_data, align 8, !dbg !3649
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !3650
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !3651
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3652
  %temp_fd = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 0, !dbg !3654
  %4 = load i32, i32* %temp_fd, align 8, !dbg !3654
  %cmp = icmp eq i32 %4, -1, !dbg !3655
  br i1 %cmp, label %if.then, label %if.end6, !dbg !3656

if.then:                                          ; preds = %entry
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3657
  %temp_offset = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 1, !dbg !3659
  store i64 0, i64* %temp_offset, align 8, !dbg !3660
  %call = call i32 @__archive_mktemp(i8* null), !dbg !3661
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3662
  %temp_fd1 = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 0, !dbg !3663
  store i32 %call, i32* %temp_fd1, align 8, !dbg !3664
  %7 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3665
  %temp_fd2 = getelementptr inbounds %struct._7zip, %struct._7zip* %7, i32 0, i32 0, !dbg !3667
  %8 = load i32, i32* %temp_fd2, align 8, !dbg !3667
  %cmp3 = icmp slt i32 %8, 0, !dbg !3668
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !3669

if.then4:                                         ; preds = %if.then
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3670
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !3672
  %call5 = call i32* @__errno_location() #1, !dbg !3673
  %10 = load i32, i32* %call5, align 4, !dbg !3673
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %10, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.45, i32 0, i32 0)), !dbg !3674
  store i32 -30, i32* %retval, align 4, !dbg !3676
  br label %return, !dbg !3676

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !3677

if.end6:                                          ; preds = %if.end, %entry
  %11 = load i8*, i8** %buff.addr, align 8, !dbg !3678
  store i8* %11, i8** %p, align 8, !dbg !3679
  br label %while.cond, !dbg !3680

while.cond:                                       ; preds = %if.end13, %if.end6
  %12 = load i64, i64* %s.addr, align 8, !dbg !3681
  %tobool = icmp ne i64 %12, 0, !dbg !3683
  br i1 %tobool, label %while.body, label %while.end, !dbg !3683

while.body:                                       ; preds = %while.cond
  %13 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3684
  %temp_fd7 = getelementptr inbounds %struct._7zip, %struct._7zip* %13, i32 0, i32 0, !dbg !3686
  %14 = load i32, i32* %temp_fd7, align 8, !dbg !3686
  %15 = load i8*, i8** %p, align 8, !dbg !3687
  %16 = load i64, i64* %s.addr, align 8, !dbg !3688
  %call8 = call i64 @write(i32 %14, i8* %15, i64 %16), !dbg !3689
  store i64 %call8, i64* %ws, align 8, !dbg !3690
  %17 = load i64, i64* %ws, align 8, !dbg !3691
  %cmp9 = icmp slt i64 %17, 0, !dbg !3693
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !3694

if.then10:                                        ; preds = %while.body
  %18 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3695
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 0, !dbg !3697
  %call12 = call i32* @__errno_location() #1, !dbg !3698
  %19 = load i32, i32* %call12, align 4, !dbg !3698
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive11, i32 %19, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.46, i32 0, i32 0)), !dbg !3699
  store i32 -30, i32* %retval, align 4, !dbg !3701
  br label %return, !dbg !3701

if.end13:                                         ; preds = %while.body
  %20 = load i64, i64* %ws, align 8, !dbg !3702
  %21 = load i64, i64* %s.addr, align 8, !dbg !3703
  %sub = sub i64 %21, %20, !dbg !3703
  store i64 %sub, i64* %s.addr, align 8, !dbg !3703
  %22 = load i64, i64* %ws, align 8, !dbg !3704
  %23 = load i8*, i8** %p, align 8, !dbg !3705
  %add.ptr = getelementptr inbounds i8, i8* %23, i64 %22, !dbg !3705
  store i8* %add.ptr, i8** %p, align 8, !dbg !3705
  %24 = load i64, i64* %ws, align 8, !dbg !3706
  %25 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3707
  %temp_offset14 = getelementptr inbounds %struct._7zip, %struct._7zip* %25, i32 0, i32 1, !dbg !3708
  %26 = load i64, i64* %temp_offset14, align 8, !dbg !3709
  %add = add i64 %26, %24, !dbg !3709
  store i64 %add, i64* %temp_offset14, align 8, !dbg !3709
  br label %while.cond, !dbg !3710

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !3712
  br label %return, !dbg !3712

return:                                           ; preds = %while.end, %if.then10, %if.then4
  %27 = load i32, i32* %retval, align 4, !dbg !3713
  ret i32 %27, !dbg !3713
}

declare i32 @__archive_mktemp(i8*) #2

declare i64 @write(i32, i8*, i64) #2

declare %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree*, %struct.archive_rb_node*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @make_header(%struct.archive_write* %a, i64 %offset, i64 %pack_size, i64 %unpack_size, i32 %codernum, %struct.coder* %coders) #0 !dbg !642 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %offset.addr = alloca i64, align 8
  %pack_size.addr = alloca i64, align 8
  %unpack_size.addr = alloca i64, align 8
  %codernum.addr = alloca i32, align 4
  %coders.addr = alloca %struct.coder*, align 8
  %zip = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %r = alloca i32, align 4
  %b = alloca i8, align 1
  %mask = alloca i8, align 1
  %encattr = alloca i32, align 4
  %attr = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3714, metadata !693), !dbg !3715
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !3716, metadata !693), !dbg !3717
  store i64 %pack_size, i64* %pack_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %pack_size.addr, metadata !3718, metadata !693), !dbg !3719
  store i64 %unpack_size, i64* %unpack_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpack_size.addr, metadata !3720, metadata !693), !dbg !3721
  store i32 %codernum, i32* %codernum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %codernum.addr, metadata !3722, metadata !693), !dbg !3723
  store %struct.coder* %coders, %struct.coder** %coders.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.coder** %coders.addr, metadata !3724, metadata !693), !dbg !3725
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !3726, metadata !693), !dbg !3727
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3728
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3729
  %1 = load i8*, i8** %format_data, align 8, !dbg !3729
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !3730
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !3727
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !3731, metadata !693), !dbg !3732
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3733, metadata !693), !dbg !3734
  call void @llvm.dbg.declare(metadata i8* %b, metadata !3735, metadata !693), !dbg !3736
  call void @llvm.dbg.declare(metadata i8* %mask, metadata !3737, metadata !693), !dbg !3738
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3739
  %call = call i32 @enc_uint64(%struct.archive_write* %3, i64 1), !dbg !3740
  store i32 %call, i32* %r, align 4, !dbg !3741
  %4 = load i32, i32* %r, align 4, !dbg !3742
  %cmp = icmp slt i32 %4, 0, !dbg !3744
  br i1 %cmp, label %if.then, label %if.end, !dbg !3745

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %r, align 4, !dbg !3746
  store i32 %5, i32* %retval, align 4, !dbg !3747
  br label %return, !dbg !3747

if.end:                                           ; preds = %entry
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3748
  %total_number_nonempty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 4, !dbg !3750
  %7 = load i64, i64* %total_number_nonempty_entry, align 8, !dbg !3750
  %tobool = icmp ne i64 %7, 0, !dbg !3748
  br i1 %tobool, label %if.then1, label %if.end10, !dbg !3751

if.then1:                                         ; preds = %if.end
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3752
  %call2 = call i32 @enc_uint64(%struct.archive_write* %8, i64 4), !dbg !3754
  store i32 %call2, i32* %r, align 4, !dbg !3755
  %9 = load i32, i32* %r, align 4, !dbg !3756
  %cmp3 = icmp slt i32 %9, 0, !dbg !3758
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3759

if.then4:                                         ; preds = %if.then1
  %10 = load i32, i32* %r, align 4, !dbg !3760
  store i32 %10, i32* %retval, align 4, !dbg !3761
  br label %return, !dbg !3761

if.end5:                                          ; preds = %if.then1
  %11 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3762
  %12 = load i64, i64* %offset.addr, align 8, !dbg !3763
  %13 = load i64, i64* %pack_size.addr, align 8, !dbg !3764
  %14 = load i64, i64* %unpack_size.addr, align 8, !dbg !3765
  %15 = load i32, i32* %codernum.addr, align 4, !dbg !3766
  %16 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !3767
  %call6 = call i32 @make_streamsInfo(%struct.archive_write* %11, i64 %12, i64 %13, i64 %14, i32 %15, %struct.coder* %16, i32 1, i32 0), !dbg !3768
  store i32 %call6, i32* %r, align 4, !dbg !3769
  %17 = load i32, i32* %r, align 4, !dbg !3770
  %cmp7 = icmp slt i32 %17, 0, !dbg !3772
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !3773

if.then8:                                         ; preds = %if.end5
  %18 = load i32, i32* %r, align 4, !dbg !3774
  store i32 %18, i32* %retval, align 4, !dbg !3775
  br label %return, !dbg !3775

if.end9:                                          ; preds = %if.end5
  br label %if.end10, !dbg !3776

if.end10:                                         ; preds = %if.end9, %if.end
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3777
  %call11 = call i32 @enc_uint64(%struct.archive_write* %19, i64 5), !dbg !3778
  store i32 %call11, i32* %r, align 4, !dbg !3779
  %20 = load i32, i32* %r, align 4, !dbg !3780
  %cmp12 = icmp slt i32 %20, 0, !dbg !3782
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !3783

if.then13:                                        ; preds = %if.end10
  %21 = load i32, i32* %r, align 4, !dbg !3784
  store i32 %21, i32* %retval, align 4, !dbg !3785
  br label %return, !dbg !3785

if.end14:                                         ; preds = %if.end10
  %22 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3786
  %23 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3787
  %total_number_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %23, i32 0, i32 3, !dbg !3788
  %24 = load i64, i64* %total_number_entry, align 8, !dbg !3788
  %call15 = call i32 @enc_uint64(%struct.archive_write* %22, i64 %24), !dbg !3789
  store i32 %call15, i32* %r, align 4, !dbg !3790
  %25 = load i32, i32* %r, align 4, !dbg !3791
  %cmp16 = icmp slt i32 %25, 0, !dbg !3793
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !3794

if.then17:                                        ; preds = %if.end14
  %26 = load i32, i32* %r, align 4, !dbg !3795
  store i32 %26, i32* %retval, align 4, !dbg !3796
  br label %return, !dbg !3796

if.end18:                                         ; preds = %if.end14
  %27 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3797
  %total_number_empty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %27, i32 0, i32 5, !dbg !3799
  %28 = load i64, i64* %total_number_empty_entry, align 8, !dbg !3799
  %cmp19 = icmp ugt i64 %28, 0, !dbg !3800
  br i1 %cmp19, label %if.then20, label %if.end61, !dbg !3801

if.then20:                                        ; preds = %if.end18
  %29 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3802
  %call21 = call i32 @enc_uint64(%struct.archive_write* %29, i64 14), !dbg !3804
  store i32 %call21, i32* %r, align 4, !dbg !3805
  %30 = load i32, i32* %r, align 4, !dbg !3806
  %cmp22 = icmp slt i32 %30, 0, !dbg !3808
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !3809

if.then23:                                        ; preds = %if.then20
  %31 = load i32, i32* %r, align 4, !dbg !3810
  store i32 %31, i32* %retval, align 4, !dbg !3811
  br label %return, !dbg !3811

if.end24:                                         ; preds = %if.then20
  %32 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3812
  %33 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3813
  %total_number_entry25 = getelementptr inbounds %struct._7zip, %struct._7zip* %33, i32 0, i32 3, !dbg !3814
  %34 = load i64, i64* %total_number_entry25, align 8, !dbg !3814
  %add = add i64 %34, 7, !dbg !3815
  %shr = lshr i64 %add, 3, !dbg !3816
  %call26 = call i32 @enc_uint64(%struct.archive_write* %32, i64 %shr), !dbg !3817
  store i32 %call26, i32* %r, align 4, !dbg !3818
  %35 = load i32, i32* %r, align 4, !dbg !3819
  %cmp27 = icmp slt i32 %35, 0, !dbg !3821
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !3822

if.then28:                                        ; preds = %if.end24
  %36 = load i32, i32* %r, align 4, !dbg !3823
  store i32 %36, i32* %retval, align 4, !dbg !3824
  br label %return, !dbg !3824

if.end29:                                         ; preds = %if.end24
  store i8 0, i8* %b, align 1, !dbg !3825
  store i8 -128, i8* %mask, align 1, !dbg !3826
  %37 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3827
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %37, i32 0, i32 23, !dbg !3828
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !3829
  %38 = load %struct.file*, %struct.file** %first, align 8, !dbg !3829
  store %struct.file* %38, %struct.file** %file, align 8, !dbg !3830
  br label %for.cond, !dbg !3831

for.cond:                                         ; preds = %for.inc, %if.end29
  %39 = load %struct.file*, %struct.file** %file, align 8, !dbg !3832
  %cmp30 = icmp ne %struct.file* %39, null, !dbg !3836
  br i1 %cmp30, label %for.body, label %for.end, !dbg !3837

for.body:                                         ; preds = %for.cond
  %40 = load %struct.file*, %struct.file** %file, align 8, !dbg !3838
  %size = getelementptr inbounds %struct.file, %struct.file* %40, i32 0, i32 4, !dbg !3841
  %41 = load i64, i64* %size, align 8, !dbg !3841
  %cmp31 = icmp eq i64 %41, 0, !dbg !3842
  br i1 %cmp31, label %if.then32, label %if.end35, !dbg !3843

if.then32:                                        ; preds = %for.body
  %42 = load i8, i8* %mask, align 1, !dbg !3844
  %conv = zext i8 %42 to i32, !dbg !3844
  %43 = load i8, i8* %b, align 1, !dbg !3845
  %conv33 = zext i8 %43 to i32, !dbg !3845
  %or = or i32 %conv33, %conv, !dbg !3845
  %conv34 = trunc i32 %or to i8, !dbg !3845
  store i8 %conv34, i8* %b, align 1, !dbg !3845
  br label %if.end35, !dbg !3846

if.end35:                                         ; preds = %if.then32, %for.body
  %44 = load i8, i8* %mask, align 1, !dbg !3847
  %conv36 = zext i8 %44 to i32, !dbg !3847
  %shr37 = ashr i32 %conv36, 1, !dbg !3847
  %conv38 = trunc i32 %shr37 to i8, !dbg !3847
  store i8 %conv38, i8* %mask, align 1, !dbg !3847
  %45 = load i8, i8* %mask, align 1, !dbg !3848
  %conv39 = zext i8 %45 to i32, !dbg !3848
  %cmp40 = icmp eq i32 %conv39, 0, !dbg !3850
  br i1 %cmp40, label %if.then42, label %if.end49, !dbg !3851

if.then42:                                        ; preds = %if.end35
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3852
  %call43 = call i64 @compress_out(%struct.archive_write* %46, i8* %b, i64 1, i32 1), !dbg !3854
  %conv44 = trunc i64 %call43 to i32, !dbg !3855
  store i32 %conv44, i32* %r, align 4, !dbg !3856
  %47 = load i32, i32* %r, align 4, !dbg !3857
  %cmp45 = icmp slt i32 %47, 0, !dbg !3859
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !3860

if.then47:                                        ; preds = %if.then42
  %48 = load i32, i32* %r, align 4, !dbg !3861
  store i32 %48, i32* %retval, align 4, !dbg !3862
  br label %return, !dbg !3862

if.end48:                                         ; preds = %if.then42
  store i8 -128, i8* %mask, align 1, !dbg !3863
  store i8 0, i8* %b, align 1, !dbg !3864
  br label %if.end49, !dbg !3865

if.end49:                                         ; preds = %if.end48, %if.end35
  br label %for.inc, !dbg !3866

for.inc:                                          ; preds = %if.end49
  %49 = load %struct.file*, %struct.file** %file, align 8, !dbg !3867
  %next = getelementptr inbounds %struct.file, %struct.file* %49, i32 0, i32 1, !dbg !3869
  %50 = load %struct.file*, %struct.file** %next, align 8, !dbg !3869
  store %struct.file* %50, %struct.file** %file, align 8, !dbg !3870
  br label %for.cond, !dbg !3871

for.end:                                          ; preds = %for.cond
  %51 = load i8, i8* %mask, align 1, !dbg !3872
  %conv50 = zext i8 %51 to i32, !dbg !3872
  %cmp51 = icmp ne i32 %conv50, 128, !dbg !3874
  br i1 %cmp51, label %if.then53, label %if.end60, !dbg !3875

if.then53:                                        ; preds = %for.end
  %52 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3876
  %call54 = call i64 @compress_out(%struct.archive_write* %52, i8* %b, i64 1, i32 1), !dbg !3878
  %conv55 = trunc i64 %call54 to i32, !dbg !3879
  store i32 %conv55, i32* %r, align 4, !dbg !3880
  %53 = load i32, i32* %r, align 4, !dbg !3881
  %cmp56 = icmp slt i32 %53, 0, !dbg !3883
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !3884

if.then58:                                        ; preds = %if.then53
  %54 = load i32, i32* %r, align 4, !dbg !3885
  store i32 %54, i32* %retval, align 4, !dbg !3886
  br label %return, !dbg !3886

if.end59:                                         ; preds = %if.then53
  br label %if.end60, !dbg !3887

if.end60:                                         ; preds = %if.end59, %for.end
  br label %if.end61, !dbg !3888

if.end61:                                         ; preds = %if.end60, %if.end18
  %55 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3889
  %total_number_empty_entry62 = getelementptr inbounds %struct._7zip, %struct._7zip* %55, i32 0, i32 5, !dbg !3891
  %56 = load i64, i64* %total_number_empty_entry62, align 8, !dbg !3891
  %57 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3892
  %total_number_dir_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %57, i32 0, i32 6, !dbg !3893
  %58 = load i64, i64* %total_number_dir_entry, align 8, !dbg !3893
  %cmp63 = icmp ugt i64 %56, %58, !dbg !3894
  br i1 %cmp63, label %if.then65, label %if.end124, !dbg !3895

if.then65:                                        ; preds = %if.end61
  %59 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3896
  %call66 = call i32 @enc_uint64(%struct.archive_write* %59, i64 15), !dbg !3898
  store i32 %call66, i32* %r, align 4, !dbg !3899
  %60 = load i32, i32* %r, align 4, !dbg !3900
  %cmp67 = icmp slt i32 %60, 0, !dbg !3902
  br i1 %cmp67, label %if.then69, label %if.end70, !dbg !3903

if.then69:                                        ; preds = %if.then65
  %61 = load i32, i32* %r, align 4, !dbg !3904
  store i32 %61, i32* %retval, align 4, !dbg !3905
  br label %return, !dbg !3905

if.end70:                                         ; preds = %if.then65
  %62 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3906
  %63 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3907
  %total_number_empty_entry71 = getelementptr inbounds %struct._7zip, %struct._7zip* %63, i32 0, i32 5, !dbg !3908
  %64 = load i64, i64* %total_number_empty_entry71, align 8, !dbg !3908
  %add72 = add i64 %64, 7, !dbg !3909
  %shr73 = lshr i64 %add72, 3, !dbg !3910
  %call74 = call i32 @enc_uint64(%struct.archive_write* %62, i64 %shr73), !dbg !3911
  store i32 %call74, i32* %r, align 4, !dbg !3912
  %65 = load i32, i32* %r, align 4, !dbg !3913
  %cmp75 = icmp slt i32 %65, 0, !dbg !3915
  br i1 %cmp75, label %if.then77, label %if.end78, !dbg !3916

if.then77:                                        ; preds = %if.end70
  %66 = load i32, i32* %r, align 4, !dbg !3917
  store i32 %66, i32* %retval, align 4, !dbg !3918
  br label %return, !dbg !3918

if.end78:                                         ; preds = %if.end70
  store i8 0, i8* %b, align 1, !dbg !3919
  store i8 -128, i8* %mask, align 1, !dbg !3920
  %67 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3921
  %file_list79 = getelementptr inbounds %struct._7zip, %struct._7zip* %67, i32 0, i32 23, !dbg !3922
  %first80 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list79, i32 0, i32 0, !dbg !3923
  %68 = load %struct.file*, %struct.file** %first80, align 8, !dbg !3923
  store %struct.file* %68, %struct.file** %file, align 8, !dbg !3924
  br label %for.cond81, !dbg !3925

for.cond81:                                       ; preds = %for.inc110, %if.end78
  %69 = load %struct.file*, %struct.file** %file, align 8, !dbg !3926
  %cmp82 = icmp ne %struct.file* %69, null, !dbg !3930
  br i1 %cmp82, label %for.body84, label %for.end112, !dbg !3931

for.body84:                                       ; preds = %for.cond81
  %70 = load %struct.file*, %struct.file** %file, align 8, !dbg !3932
  %size85 = getelementptr inbounds %struct.file, %struct.file* %70, i32 0, i32 4, !dbg !3935
  %71 = load i64, i64* %size85, align 8, !dbg !3935
  %tobool86 = icmp ne i64 %71, 0, !dbg !3932
  br i1 %tobool86, label %if.then87, label %if.end88, !dbg !3936

if.then87:                                        ; preds = %for.body84
  br label %for.inc110, !dbg !3937

if.end88:                                         ; preds = %for.body84
  %72 = load %struct.file*, %struct.file** %file, align 8, !dbg !3938
  %dir = getelementptr inbounds %struct.file, %struct.file* %72, i32 0, i32 9, !dbg !3940
  %bf.load = load i8, i8* %dir, align 8, !dbg !3940
  %bf.shl = shl i8 %bf.load, 7, !dbg !3940
  %bf.ashr = ashr i8 %bf.shl, 7, !dbg !3940
  %bf.cast = sext i8 %bf.ashr to i32, !dbg !3940
  %tobool89 = icmp ne i32 %bf.cast, 0, !dbg !3938
  br i1 %tobool89, label %if.end95, label %if.then90, !dbg !3941

if.then90:                                        ; preds = %if.end88
  %73 = load i8, i8* %mask, align 1, !dbg !3942
  %conv91 = zext i8 %73 to i32, !dbg !3942
  %74 = load i8, i8* %b, align 1, !dbg !3943
  %conv92 = zext i8 %74 to i32, !dbg !3943
  %or93 = or i32 %conv92, %conv91, !dbg !3943
  %conv94 = trunc i32 %or93 to i8, !dbg !3943
  store i8 %conv94, i8* %b, align 1, !dbg !3943
  br label %if.end95, !dbg !3944

if.end95:                                         ; preds = %if.then90, %if.end88
  %75 = load i8, i8* %mask, align 1, !dbg !3945
  %conv96 = zext i8 %75 to i32, !dbg !3945
  %shr97 = ashr i32 %conv96, 1, !dbg !3945
  %conv98 = trunc i32 %shr97 to i8, !dbg !3945
  store i8 %conv98, i8* %mask, align 1, !dbg !3945
  %76 = load i8, i8* %mask, align 1, !dbg !3946
  %conv99 = zext i8 %76 to i32, !dbg !3946
  %cmp100 = icmp eq i32 %conv99, 0, !dbg !3948
  br i1 %cmp100, label %if.then102, label %if.end109, !dbg !3949

if.then102:                                       ; preds = %if.end95
  %77 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3950
  %call103 = call i64 @compress_out(%struct.archive_write* %77, i8* %b, i64 1, i32 1), !dbg !3952
  %conv104 = trunc i64 %call103 to i32, !dbg !3953
  store i32 %conv104, i32* %r, align 4, !dbg !3954
  %78 = load i32, i32* %r, align 4, !dbg !3955
  %cmp105 = icmp slt i32 %78, 0, !dbg !3957
  br i1 %cmp105, label %if.then107, label %if.end108, !dbg !3958

if.then107:                                       ; preds = %if.then102
  %79 = load i32, i32* %r, align 4, !dbg !3959
  store i32 %79, i32* %retval, align 4, !dbg !3960
  br label %return, !dbg !3960

if.end108:                                        ; preds = %if.then102
  store i8 -128, i8* %mask, align 1, !dbg !3961
  store i8 0, i8* %b, align 1, !dbg !3962
  br label %if.end109, !dbg !3963

if.end109:                                        ; preds = %if.end108, %if.end95
  br label %for.inc110, !dbg !3964

for.inc110:                                       ; preds = %if.end109, %if.then87
  %80 = load %struct.file*, %struct.file** %file, align 8, !dbg !3965
  %next111 = getelementptr inbounds %struct.file, %struct.file* %80, i32 0, i32 1, !dbg !3967
  %81 = load %struct.file*, %struct.file** %next111, align 8, !dbg !3967
  store %struct.file* %81, %struct.file** %file, align 8, !dbg !3968
  br label %for.cond81, !dbg !3969

for.end112:                                       ; preds = %for.cond81
  %82 = load i8, i8* %mask, align 1, !dbg !3970
  %conv113 = zext i8 %82 to i32, !dbg !3970
  %cmp114 = icmp ne i32 %conv113, 128, !dbg !3972
  br i1 %cmp114, label %if.then116, label %if.end123, !dbg !3973

if.then116:                                       ; preds = %for.end112
  %83 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3974
  %call117 = call i64 @compress_out(%struct.archive_write* %83, i8* %b, i64 1, i32 1), !dbg !3976
  %conv118 = trunc i64 %call117 to i32, !dbg !3977
  store i32 %conv118, i32* %r, align 4, !dbg !3978
  %84 = load i32, i32* %r, align 4, !dbg !3979
  %cmp119 = icmp slt i32 %84, 0, !dbg !3981
  br i1 %cmp119, label %if.then121, label %if.end122, !dbg !3982

if.then121:                                       ; preds = %if.then116
  %85 = load i32, i32* %r, align 4, !dbg !3983
  store i32 %85, i32* %retval, align 4, !dbg !3984
  br label %return, !dbg !3984

if.end122:                                        ; preds = %if.then116
  br label %if.end123, !dbg !3985

if.end123:                                        ; preds = %if.end122, %for.end112
  br label %if.end124, !dbg !3986

if.end124:                                        ; preds = %if.end123, %if.end61
  %86 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3987
  %call125 = call i32 @enc_uint64(%struct.archive_write* %86, i64 17), !dbg !3988
  store i32 %call125, i32* %r, align 4, !dbg !3989
  %87 = load i32, i32* %r, align 4, !dbg !3990
  %cmp126 = icmp slt i32 %87, 0, !dbg !3992
  br i1 %cmp126, label %if.then128, label %if.end129, !dbg !3993

if.then128:                                       ; preds = %if.end124
  %88 = load i32, i32* %r, align 4, !dbg !3994
  store i32 %88, i32* %retval, align 4, !dbg !3995
  br label %return, !dbg !3995

if.end129:                                        ; preds = %if.end124
  %89 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3996
  %90 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !3997
  %total_bytes_entry_name = getelementptr inbounds %struct._7zip, %struct._7zip* %90, i32 0, i32 7, !dbg !3998
  %91 = load i64, i64* %total_bytes_entry_name, align 8, !dbg !3998
  %add130 = add i64 %91, 1, !dbg !3999
  %call131 = call i32 @enc_uint64(%struct.archive_write* %89, i64 %add130), !dbg !4000
  store i32 %call131, i32* %r, align 4, !dbg !4001
  %92 = load i32, i32* %r, align 4, !dbg !4002
  %cmp132 = icmp slt i32 %92, 0, !dbg !4004
  br i1 %cmp132, label %if.then134, label %if.end135, !dbg !4005

if.then134:                                       ; preds = %if.end129
  %93 = load i32, i32* %r, align 4, !dbg !4006
  store i32 %93, i32* %retval, align 4, !dbg !4007
  br label %return, !dbg !4007

if.end135:                                        ; preds = %if.end129
  %94 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4008
  %call136 = call i32 @enc_uint64(%struct.archive_write* %94, i64 0), !dbg !4009
  store i32 %call136, i32* %r, align 4, !dbg !4010
  %95 = load i32, i32* %r, align 4, !dbg !4011
  %cmp137 = icmp slt i32 %95, 0, !dbg !4013
  br i1 %cmp137, label %if.then139, label %if.end140, !dbg !4014

if.then139:                                       ; preds = %if.end135
  %96 = load i32, i32* %r, align 4, !dbg !4015
  store i32 %96, i32* %retval, align 4, !dbg !4016
  br label %return, !dbg !4016

if.end140:                                        ; preds = %if.end135
  %97 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4017
  %file_list141 = getelementptr inbounds %struct._7zip, %struct._7zip* %97, i32 0, i32 23, !dbg !4018
  %first142 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list141, i32 0, i32 0, !dbg !4019
  %98 = load %struct.file*, %struct.file** %first142, align 8, !dbg !4019
  store %struct.file* %98, %struct.file** %file, align 8, !dbg !4020
  br label %for.cond143, !dbg !4021

for.cond143:                                      ; preds = %for.inc155, %if.end140
  %99 = load %struct.file*, %struct.file** %file, align 8, !dbg !4022
  %cmp144 = icmp ne %struct.file* %99, null, !dbg !4026
  br i1 %cmp144, label %for.body146, label %for.end157, !dbg !4027

for.body146:                                      ; preds = %for.cond143
  %100 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4028
  %101 = load %struct.file*, %struct.file** %file, align 8, !dbg !4030
  %utf16name = getelementptr inbounds %struct.file, %struct.file* %101, i32 0, i32 3, !dbg !4031
  %102 = load i8*, i8** %utf16name, align 8, !dbg !4031
  %103 = load %struct.file*, %struct.file** %file, align 8, !dbg !4032
  %name_len = getelementptr inbounds %struct.file, %struct.file* %103, i32 0, i32 2, !dbg !4033
  %104 = load i32, i32* %name_len, align 8, !dbg !4033
  %add147 = add i32 %104, 2, !dbg !4034
  %conv148 = zext i32 %add147 to i64, !dbg !4032
  %call149 = call i64 @compress_out(%struct.archive_write* %100, i8* %102, i64 %conv148, i32 1), !dbg !4035
  %conv150 = trunc i64 %call149 to i32, !dbg !4036
  store i32 %conv150, i32* %r, align 4, !dbg !4037
  %105 = load i32, i32* %r, align 4, !dbg !4038
  %cmp151 = icmp slt i32 %105, 0, !dbg !4040
  br i1 %cmp151, label %if.then153, label %if.end154, !dbg !4041

if.then153:                                       ; preds = %for.body146
  %106 = load i32, i32* %r, align 4, !dbg !4042
  store i32 %106, i32* %retval, align 4, !dbg !4043
  br label %return, !dbg !4043

if.end154:                                        ; preds = %for.body146
  br label %for.inc155, !dbg !4044

for.inc155:                                       ; preds = %if.end154
  %107 = load %struct.file*, %struct.file** %file, align 8, !dbg !4045
  %next156 = getelementptr inbounds %struct.file, %struct.file* %107, i32 0, i32 1, !dbg !4047
  %108 = load %struct.file*, %struct.file** %next156, align 8, !dbg !4047
  store %struct.file* %108, %struct.file** %file, align 8, !dbg !4048
  br label %for.cond143, !dbg !4049

for.end157:                                       ; preds = %for.cond143
  %109 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4050
  %call158 = call i32 @make_time(%struct.archive_write* %109, i8 zeroext 20, i32 1, i32 0), !dbg !4051
  store i32 %call158, i32* %r, align 4, !dbg !4052
  %110 = load i32, i32* %r, align 4, !dbg !4053
  %cmp159 = icmp slt i32 %110, 0, !dbg !4055
  br i1 %cmp159, label %if.then161, label %if.end162, !dbg !4056

if.then161:                                       ; preds = %for.end157
  %111 = load i32, i32* %r, align 4, !dbg !4057
  store i32 %111, i32* %retval, align 4, !dbg !4058
  br label %return, !dbg !4058

if.end162:                                        ; preds = %for.end157
  %112 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4059
  %call163 = call i32 @make_time(%struct.archive_write* %112, i8 zeroext 18, i32 4, i32 2), !dbg !4060
  store i32 %call163, i32* %r, align 4, !dbg !4061
  %113 = load i32, i32* %r, align 4, !dbg !4062
  %cmp164 = icmp slt i32 %113, 0, !dbg !4064
  br i1 %cmp164, label %if.then166, label %if.end167, !dbg !4065

if.then166:                                       ; preds = %if.end162
  %114 = load i32, i32* %r, align 4, !dbg !4066
  store i32 %114, i32* %retval, align 4, !dbg !4067
  br label %return, !dbg !4067

if.end167:                                        ; preds = %if.end162
  %115 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4068
  %call168 = call i32 @make_time(%struct.archive_write* %115, i8 zeroext 19, i32 2, i32 1), !dbg !4069
  store i32 %call168, i32* %r, align 4, !dbg !4070
  %116 = load i32, i32* %r, align 4, !dbg !4071
  %cmp169 = icmp slt i32 %116, 0, !dbg !4073
  br i1 %cmp169, label %if.then171, label %if.end172, !dbg !4074

if.then171:                                       ; preds = %if.end167
  %117 = load i32, i32* %r, align 4, !dbg !4075
  store i32 %117, i32* %retval, align 4, !dbg !4076
  br label %return, !dbg !4076

if.end172:                                        ; preds = %if.end167
  %118 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4077
  %call173 = call i32 @enc_uint64(%struct.archive_write* %118, i64 21), !dbg !4078
  store i32 %call173, i32* %r, align 4, !dbg !4079
  %119 = load i32, i32* %r, align 4, !dbg !4080
  %cmp174 = icmp slt i32 %119, 0, !dbg !4082
  br i1 %cmp174, label %if.then176, label %if.end177, !dbg !4083

if.then176:                                       ; preds = %if.end172
  %120 = load i32, i32* %r, align 4, !dbg !4084
  store i32 %120, i32* %retval, align 4, !dbg !4085
  br label %return, !dbg !4085

if.end177:                                        ; preds = %if.end172
  %121 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4086
  %122 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4087
  %total_number_entry178 = getelementptr inbounds %struct._7zip, %struct._7zip* %122, i32 0, i32 3, !dbg !4088
  %123 = load i64, i64* %total_number_entry178, align 8, !dbg !4088
  %mul = mul i64 %123, 4, !dbg !4089
  %add179 = add i64 2, %mul, !dbg !4090
  %call180 = call i32 @enc_uint64(%struct.archive_write* %121, i64 %add179), !dbg !4091
  store i32 %call180, i32* %r, align 4, !dbg !4092
  %124 = load i32, i32* %r, align 4, !dbg !4093
  %cmp181 = icmp slt i32 %124, 0, !dbg !4095
  br i1 %cmp181, label %if.then183, label %if.end184, !dbg !4096

if.then183:                                       ; preds = %if.end177
  %125 = load i32, i32* %r, align 4, !dbg !4097
  store i32 %125, i32* %retval, align 4, !dbg !4098
  br label %return, !dbg !4098

if.end184:                                        ; preds = %if.end177
  %126 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4099
  %call185 = call i32 @enc_uint64(%struct.archive_write* %126, i64 1), !dbg !4100
  store i32 %call185, i32* %r, align 4, !dbg !4101
  %127 = load i32, i32* %r, align 4, !dbg !4102
  %cmp186 = icmp slt i32 %127, 0, !dbg !4104
  br i1 %cmp186, label %if.then188, label %if.end189, !dbg !4105

if.then188:                                       ; preds = %if.end184
  %128 = load i32, i32* %r, align 4, !dbg !4106
  store i32 %128, i32* %retval, align 4, !dbg !4107
  br label %return, !dbg !4107

if.end189:                                        ; preds = %if.end184
  %129 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4108
  %call190 = call i32 @enc_uint64(%struct.archive_write* %129, i64 0), !dbg !4109
  store i32 %call190, i32* %r, align 4, !dbg !4110
  %130 = load i32, i32* %r, align 4, !dbg !4111
  %cmp191 = icmp slt i32 %130, 0, !dbg !4113
  br i1 %cmp191, label %if.then193, label %if.end194, !dbg !4114

if.then193:                                       ; preds = %if.end189
  %131 = load i32, i32* %r, align 4, !dbg !4115
  store i32 %131, i32* %retval, align 4, !dbg !4116
  br label %return, !dbg !4116

if.end194:                                        ; preds = %if.end189
  %132 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4117
  %file_list195 = getelementptr inbounds %struct._7zip, %struct._7zip* %132, i32 0, i32 23, !dbg !4118
  %first196 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list195, i32 0, i32 0, !dbg !4119
  %133 = load %struct.file*, %struct.file** %first196, align 8, !dbg !4119
  store %struct.file* %133, %struct.file** %file, align 8, !dbg !4120
  br label %for.cond197, !dbg !4121

for.cond197:                                      ; preds = %for.inc222, %if.end194
  %134 = load %struct.file*, %struct.file** %file, align 8, !dbg !4122
  %cmp198 = icmp ne %struct.file* %134, null, !dbg !4126
  br i1 %cmp198, label %for.body200, label %for.end224, !dbg !4127

for.body200:                                      ; preds = %for.cond197
  call void @llvm.dbg.declare(metadata i32* %encattr, metadata !4128, metadata !693), !dbg !4130
  call void @llvm.dbg.declare(metadata i32* %attr, metadata !4131, metadata !693), !dbg !4132
  %135 = load %struct.file*, %struct.file** %file, align 8, !dbg !4133
  %dir201 = getelementptr inbounds %struct.file, %struct.file* %135, i32 0, i32 9, !dbg !4135
  %bf.load202 = load i8, i8* %dir201, align 8, !dbg !4135
  %bf.shl203 = shl i8 %bf.load202, 7, !dbg !4135
  %bf.ashr204 = ashr i8 %bf.shl203, 7, !dbg !4135
  %bf.cast205 = sext i8 %bf.ashr204 to i32, !dbg !4135
  %tobool206 = icmp ne i32 %bf.cast205, 0, !dbg !4133
  br i1 %tobool206, label %if.then207, label %if.else, !dbg !4136

if.then207:                                       ; preds = %for.body200
  store i32 32784, i32* %attr, align 4, !dbg !4137
  br label %if.end208, !dbg !4138

if.else:                                          ; preds = %for.body200
  store i32 32800, i32* %attr, align 4, !dbg !4139
  br label %if.end208

if.end208:                                        ; preds = %if.else, %if.then207
  %136 = load %struct.file*, %struct.file** %file, align 8, !dbg !4140
  %mode = getelementptr inbounds %struct.file, %struct.file* %136, i32 0, i32 7, !dbg !4142
  %137 = load i32, i32* %mode, align 8, !dbg !4142
  %and = and i32 %137, 146, !dbg !4143
  %cmp209 = icmp eq i32 %and, 0, !dbg !4144
  br i1 %cmp209, label %if.then211, label %if.end213, !dbg !4145

if.then211:                                       ; preds = %if.end208
  %138 = load i32, i32* %attr, align 4, !dbg !4146
  %or212 = or i32 %138, 1, !dbg !4146
  store i32 %or212, i32* %attr, align 4, !dbg !4146
  br label %if.end213, !dbg !4147

if.end213:                                        ; preds = %if.then211, %if.end208
  %139 = load %struct.file*, %struct.file** %file, align 8, !dbg !4148
  %mode214 = getelementptr inbounds %struct.file, %struct.file* %139, i32 0, i32 7, !dbg !4149
  %140 = load i32, i32* %mode214, align 8, !dbg !4149
  %shl = shl i32 %140, 16, !dbg !4150
  %141 = load i32, i32* %attr, align 4, !dbg !4151
  %or215 = or i32 %141, %shl, !dbg !4151
  store i32 %or215, i32* %attr, align 4, !dbg !4151
  %142 = bitcast i32* %encattr to i8*, !dbg !4152
  %143 = load i32, i32* %attr, align 4, !dbg !4153
  call void @archive_le32enc(i8* %142, i32 %143), !dbg !4154
  %144 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4155
  %145 = bitcast i32* %encattr to i8*, !dbg !4156
  %call216 = call i64 @compress_out(%struct.archive_write* %144, i8* %145, i64 4, i32 1), !dbg !4157
  %conv217 = trunc i64 %call216 to i32, !dbg !4158
  store i32 %conv217, i32* %r, align 4, !dbg !4159
  %146 = load i32, i32* %r, align 4, !dbg !4160
  %cmp218 = icmp slt i32 %146, 0, !dbg !4162
  br i1 %cmp218, label %if.then220, label %if.end221, !dbg !4163

if.then220:                                       ; preds = %if.end213
  %147 = load i32, i32* %r, align 4, !dbg !4164
  store i32 %147, i32* %retval, align 4, !dbg !4165
  br label %return, !dbg !4165

if.end221:                                        ; preds = %if.end213
  br label %for.inc222, !dbg !4166

for.inc222:                                       ; preds = %if.end221
  %148 = load %struct.file*, %struct.file** %file, align 8, !dbg !4167
  %next223 = getelementptr inbounds %struct.file, %struct.file* %148, i32 0, i32 1, !dbg !4169
  %149 = load %struct.file*, %struct.file** %next223, align 8, !dbg !4169
  store %struct.file* %149, %struct.file** %file, align 8, !dbg !4170
  br label %for.cond197, !dbg !4171

for.end224:                                       ; preds = %for.cond197
  %150 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4172
  %call225 = call i32 @enc_uint64(%struct.archive_write* %150, i64 0), !dbg !4173
  store i32 %call225, i32* %r, align 4, !dbg !4174
  %151 = load i32, i32* %r, align 4, !dbg !4175
  %cmp226 = icmp slt i32 %151, 0, !dbg !4177
  br i1 %cmp226, label %if.then228, label %if.end229, !dbg !4178

if.then228:                                       ; preds = %for.end224
  %152 = load i32, i32* %r, align 4, !dbg !4179
  store i32 %152, i32* %retval, align 4, !dbg !4180
  br label %return, !dbg !4180

if.end229:                                        ; preds = %for.end224
  %153 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4181
  %call230 = call i32 @enc_uint64(%struct.archive_write* %153, i64 0), !dbg !4182
  store i32 %call230, i32* %r, align 4, !dbg !4183
  %154 = load i32, i32* %r, align 4, !dbg !4184
  %cmp231 = icmp slt i32 %154, 0, !dbg !4186
  br i1 %cmp231, label %if.then233, label %if.end234, !dbg !4187

if.then233:                                       ; preds = %if.end229
  %155 = load i32, i32* %r, align 4, !dbg !4188
  store i32 %155, i32* %retval, align 4, !dbg !4189
  br label %return, !dbg !4189

if.end234:                                        ; preds = %if.end229
  store i32 0, i32* %retval, align 4, !dbg !4190
  br label %return, !dbg !4190

return:                                           ; preds = %if.end234, %if.then233, %if.then228, %if.then220, %if.then193, %if.then188, %if.then183, %if.then176, %if.then171, %if.then166, %if.then161, %if.then153, %if.then139, %if.then134, %if.then128, %if.then121, %if.then107, %if.then77, %if.then69, %if.then58, %if.then47, %if.then28, %if.then23, %if.then17, %if.then13, %if.then8, %if.then4, %if.then
  %156 = load i32, i32* %retval, align 4, !dbg !4191
  ret i32 %156, !dbg !4191
}

; Function Attrs: nounwind uwtable
define internal i32 @enc_uint64(%struct.archive_write* %a, i64 %val) #0 !dbg !652 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %val.addr = alloca i64, align 8
  %mask = alloca i32, align 4
  %numdata = alloca [9 x i8], align 1
  %i = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !4192, metadata !693), !dbg !4193
  store i64 %val, i64* %val.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %val.addr, metadata !4194, metadata !693), !dbg !4195
  call void @llvm.dbg.declare(metadata i32* %mask, metadata !4196, metadata !693), !dbg !4197
  store i32 128, i32* %mask, align 4, !dbg !4197
  call void @llvm.dbg.declare(metadata [9 x i8]* %numdata, metadata !4198, metadata !693), !dbg !4202
  call void @llvm.dbg.declare(metadata i32* %i, metadata !4203, metadata !693), !dbg !4204
  %arrayidx = getelementptr inbounds [9 x i8], [9 x i8]* %numdata, i64 0, i64 0, !dbg !4205
  store i8 0, i8* %arrayidx, align 1, !dbg !4206
  store i32 1, i32* %i, align 4, !dbg !4207
  br label %for.cond, !dbg !4209

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !4210
  %cmp = icmp slt i32 %0, 9, !dbg !4213
  br i1 %cmp, label %for.body, label %for.end, !dbg !4214

for.body:                                         ; preds = %for.cond
  %1 = load i64, i64* %val.addr, align 8, !dbg !4215
  %2 = load i32, i32* %mask, align 4, !dbg !4218
  %conv = zext i32 %2 to i64, !dbg !4218
  %cmp1 = icmp ult i64 %1, %conv, !dbg !4219
  br i1 %cmp1, label %if.then, label %if.end, !dbg !4220

if.then:                                          ; preds = %for.body
  %3 = load i64, i64* %val.addr, align 8, !dbg !4221
  %conv3 = trunc i64 %3 to i8, !dbg !4223
  %conv4 = zext i8 %conv3 to i32, !dbg !4223
  %arrayidx5 = getelementptr inbounds [9 x i8], [9 x i8]* %numdata, i64 0, i64 0, !dbg !4224
  %4 = load i8, i8* %arrayidx5, align 1, !dbg !4225
  %conv6 = zext i8 %4 to i32, !dbg !4225
  %or = or i32 %conv6, %conv4, !dbg !4225
  %conv7 = trunc i32 %or to i8, !dbg !4225
  store i8 %conv7, i8* %arrayidx5, align 1, !dbg !4225
  br label %for.end, !dbg !4226

if.end:                                           ; preds = %for.body
  %5 = load i64, i64* %val.addr, align 8, !dbg !4227
  %conv8 = trunc i64 %5 to i8, !dbg !4228
  %6 = load i32, i32* %i, align 4, !dbg !4229
  %idxprom = sext i32 %6 to i64, !dbg !4230
  %arrayidx9 = getelementptr inbounds [9 x i8], [9 x i8]* %numdata, i64 0, i64 %idxprom, !dbg !4230
  store i8 %conv8, i8* %arrayidx9, align 1, !dbg !4231
  %7 = load i64, i64* %val.addr, align 8, !dbg !4232
  %shr = lshr i64 %7, 8, !dbg !4232
  store i64 %shr, i64* %val.addr, align 8, !dbg !4232
  %8 = load i32, i32* %mask, align 4, !dbg !4233
  %arrayidx10 = getelementptr inbounds [9 x i8], [9 x i8]* %numdata, i64 0, i64 0, !dbg !4234
  %9 = load i8, i8* %arrayidx10, align 1, !dbg !4235
  %conv11 = zext i8 %9 to i32, !dbg !4235
  %or12 = or i32 %conv11, %8, !dbg !4235
  %conv13 = trunc i32 %or12 to i8, !dbg !4235
  store i8 %conv13, i8* %arrayidx10, align 1, !dbg !4235
  %10 = load i32, i32* %mask, align 4, !dbg !4236
  %shr14 = lshr i32 %10, 1, !dbg !4236
  store i32 %shr14, i32* %mask, align 4, !dbg !4236
  br label %for.inc, !dbg !4237

for.inc:                                          ; preds = %if.end
  %11 = load i32, i32* %i, align 4, !dbg !4238
  %inc = add nsw i32 %11, 1, !dbg !4238
  store i32 %inc, i32* %i, align 4, !dbg !4238
  br label %for.cond, !dbg !4240

for.end:                                          ; preds = %if.then, %for.cond
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4241
  %arraydecay = getelementptr inbounds [9 x i8], [9 x i8]* %numdata, i32 0, i32 0, !dbg !4242
  %13 = load i32, i32* %i, align 4, !dbg !4243
  %conv15 = sext i32 %13 to i64, !dbg !4243
  %call = call i64 @compress_out(%struct.archive_write* %12, i8* %arraydecay, i64 %conv15, i32 1), !dbg !4244
  %conv16 = trunc i64 %call to i32, !dbg !4245
  ret i32 %conv16, !dbg !4246
}

; Function Attrs: nounwind uwtable
define internal i32 @make_streamsInfo(%struct.archive_write* %a, i64 %offset, i64 %pack_size, i64 %unpack_size, i32 %num_coder, %struct.coder* %coders, i32 %substrm, i32 %header_crc) #0 !dbg !655 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %offset.addr = alloca i64, align 8
  %pack_size.addr = alloca i64, align 8
  %unpack_size.addr = alloca i64, align 8
  %num_coder.addr = alloca i32, align 4
  %coders.addr = alloca %struct.coder*, align 8
  %substrm.addr = alloca i32, align 4
  %header_crc.addr = alloca i32, align 4
  %zip = alloca %struct._7zip*, align 8
  %codec_buff = alloca [8 x i8], align 1
  %numFolders = alloca i32, align 4
  %fi = alloca i32, align 4
  %codec_size = alloca i32, align 4
  %i = alloca i32, align 4
  %r = alloca i32, align 4
  %file = alloca %struct.file*, align 8
  %codec_id = alloca i32, align 4
  %file161 = alloca %struct.file*, align 8
  %crc = alloca [4 x i8], align 1
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !4247, metadata !693), !dbg !4248
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !4249, metadata !693), !dbg !4250
  store i64 %pack_size, i64* %pack_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %pack_size.addr, metadata !4251, metadata !693), !dbg !4252
  store i64 %unpack_size, i64* %unpack_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpack_size.addr, metadata !4253, metadata !693), !dbg !4254
  store i32 %num_coder, i32* %num_coder.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num_coder.addr, metadata !4255, metadata !693), !dbg !4256
  store %struct.coder* %coders, %struct.coder** %coders.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.coder** %coders.addr, metadata !4257, metadata !693), !dbg !4258
  store i32 %substrm, i32* %substrm.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %substrm.addr, metadata !4259, metadata !693), !dbg !4260
  store i32 %header_crc, i32* %header_crc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %header_crc.addr, metadata !4261, metadata !693), !dbg !4262
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !4263, metadata !693), !dbg !4264
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4265
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !4266
  %1 = load i8*, i8** %format_data, align 8, !dbg !4266
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !4267
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !4264
  call void @llvm.dbg.declare(metadata [8 x i8]* %codec_buff, metadata !4268, metadata !693), !dbg !4272
  call void @llvm.dbg.declare(metadata i32* %numFolders, metadata !4273, metadata !693), !dbg !4274
  call void @llvm.dbg.declare(metadata i32* %fi, metadata !4275, metadata !693), !dbg !4276
  call void @llvm.dbg.declare(metadata i32* %codec_size, metadata !4277, metadata !693), !dbg !4278
  call void @llvm.dbg.declare(metadata i32* %i, metadata !4279, metadata !693), !dbg !4280
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4281, metadata !693), !dbg !4282
  %3 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4283
  %codec = getelementptr inbounds %struct.coder, %struct.coder* %3, i32 0, i32 0, !dbg !4285
  %4 = load i32, i32* %codec, align 8, !dbg !4285
  %cmp = icmp eq i32 %4, 0, !dbg !4286
  br i1 %cmp, label %if.then, label %if.else, !dbg !4287

if.then:                                          ; preds = %entry
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4288
  %total_number_nonempty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 4, !dbg !4289
  %6 = load i64, i64* %total_number_nonempty_entry, align 8, !dbg !4289
  %conv = trunc i64 %6 to i32, !dbg !4290
  store i32 %conv, i32* %numFolders, align 4, !dbg !4291
  br label %if.end, !dbg !4292

if.else:                                          ; preds = %entry
  store i32 1, i32* %numFolders, align 4, !dbg !4293
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4294
  %call = call i32 @enc_uint64(%struct.archive_write* %7, i64 6), !dbg !4295
  store i32 %call, i32* %r, align 4, !dbg !4296
  %8 = load i32, i32* %r, align 4, !dbg !4297
  %cmp1 = icmp slt i32 %8, 0, !dbg !4299
  br i1 %cmp1, label %if.then3, label %if.end4, !dbg !4300

if.then3:                                         ; preds = %if.end
  %9 = load i32, i32* %r, align 4, !dbg !4301
  store i32 %9, i32* %retval, align 4, !dbg !4302
  br label %return, !dbg !4302

if.end4:                                          ; preds = %if.end
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4303
  %11 = load i64, i64* %offset.addr, align 8, !dbg !4304
  %call5 = call i32 @enc_uint64(%struct.archive_write* %10, i64 %11), !dbg !4305
  store i32 %call5, i32* %r, align 4, !dbg !4306
  %12 = load i32, i32* %r, align 4, !dbg !4307
  %cmp6 = icmp slt i32 %12, 0, !dbg !4309
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !4310

if.then8:                                         ; preds = %if.end4
  %13 = load i32, i32* %r, align 4, !dbg !4311
  store i32 %13, i32* %retval, align 4, !dbg !4312
  br label %return, !dbg !4312

if.end9:                                          ; preds = %if.end4
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4313
  %15 = load i32, i32* %numFolders, align 4, !dbg !4314
  %conv10 = sext i32 %15 to i64, !dbg !4314
  %call11 = call i32 @enc_uint64(%struct.archive_write* %14, i64 %conv10), !dbg !4315
  store i32 %call11, i32* %r, align 4, !dbg !4316
  %16 = load i32, i32* %r, align 4, !dbg !4317
  %cmp12 = icmp slt i32 %16, 0, !dbg !4319
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !4320

if.then14:                                        ; preds = %if.end9
  %17 = load i32, i32* %r, align 4, !dbg !4321
  store i32 %17, i32* %retval, align 4, !dbg !4322
  br label %return, !dbg !4322

if.end15:                                         ; preds = %if.end9
  %18 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4323
  %call16 = call i32 @enc_uint64(%struct.archive_write* %18, i64 9), !dbg !4324
  store i32 %call16, i32* %r, align 4, !dbg !4325
  %19 = load i32, i32* %r, align 4, !dbg !4326
  %cmp17 = icmp slt i32 %19, 0, !dbg !4328
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !4329

if.then19:                                        ; preds = %if.end15
  %20 = load i32, i32* %r, align 4, !dbg !4330
  store i32 %20, i32* %retval, align 4, !dbg !4331
  br label %return, !dbg !4331

if.end20:                                         ; preds = %if.end15
  %21 = load i32, i32* %numFolders, align 4, !dbg !4332
  %cmp21 = icmp sgt i32 %21, 1, !dbg !4334
  br i1 %cmp21, label %if.then23, label %if.else36, !dbg !4335

if.then23:                                        ; preds = %if.end20
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !4336, metadata !693), !dbg !4338
  %22 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4339
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %22, i32 0, i32 23, !dbg !4340
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !4341
  %23 = load %struct.file*, %struct.file** %first, align 8, !dbg !4341
  store %struct.file* %23, %struct.file** %file, align 8, !dbg !4338
  br label %for.cond, !dbg !4342

for.cond:                                         ; preds = %for.inc, %if.then23
  %24 = load %struct.file*, %struct.file** %file, align 8, !dbg !4343
  %cmp24 = icmp ne %struct.file* %24, null, !dbg !4347
  br i1 %cmp24, label %for.body, label %for.end, !dbg !4348

for.body:                                         ; preds = %for.cond
  %25 = load %struct.file*, %struct.file** %file, align 8, !dbg !4349
  %size = getelementptr inbounds %struct.file, %struct.file* %25, i32 0, i32 4, !dbg !4352
  %26 = load i64, i64* %size, align 8, !dbg !4352
  %cmp26 = icmp eq i64 %26, 0, !dbg !4353
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !4354

if.then28:                                        ; preds = %for.body
  br label %for.end, !dbg !4355

if.end29:                                         ; preds = %for.body
  %27 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4356
  %28 = load %struct.file*, %struct.file** %file, align 8, !dbg !4357
  %size30 = getelementptr inbounds %struct.file, %struct.file* %28, i32 0, i32 4, !dbg !4358
  %29 = load i64, i64* %size30, align 8, !dbg !4358
  %call31 = call i32 @enc_uint64(%struct.archive_write* %27, i64 %29), !dbg !4359
  store i32 %call31, i32* %r, align 4, !dbg !4360
  %30 = load i32, i32* %r, align 4, !dbg !4361
  %cmp32 = icmp slt i32 %30, 0, !dbg !4363
  br i1 %cmp32, label %if.then34, label %if.end35, !dbg !4364

if.then34:                                        ; preds = %if.end29
  %31 = load i32, i32* %r, align 4, !dbg !4365
  store i32 %31, i32* %retval, align 4, !dbg !4366
  br label %return, !dbg !4366

if.end35:                                         ; preds = %if.end29
  br label %for.inc, !dbg !4367

for.inc:                                          ; preds = %if.end35
  %32 = load %struct.file*, %struct.file** %file, align 8, !dbg !4368
  %next = getelementptr inbounds %struct.file, %struct.file* %32, i32 0, i32 1, !dbg !4370
  %33 = load %struct.file*, %struct.file** %next, align 8, !dbg !4370
  store %struct.file* %33, %struct.file** %file, align 8, !dbg !4371
  br label %for.cond, !dbg !4372

for.end:                                          ; preds = %if.then28, %for.cond
  br label %if.end42, !dbg !4373

if.else36:                                        ; preds = %if.end20
  %34 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4374
  %35 = load i64, i64* %pack_size.addr, align 8, !dbg !4376
  %call37 = call i32 @enc_uint64(%struct.archive_write* %34, i64 %35), !dbg !4377
  store i32 %call37, i32* %r, align 4, !dbg !4378
  %36 = load i32, i32* %r, align 4, !dbg !4379
  %cmp38 = icmp slt i32 %36, 0, !dbg !4381
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !4382

if.then40:                                        ; preds = %if.else36
  %37 = load i32, i32* %r, align 4, !dbg !4383
  store i32 %37, i32* %retval, align 4, !dbg !4384
  br label %return, !dbg !4384

if.end41:                                         ; preds = %if.else36
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %for.end
  %38 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4385
  %call43 = call i32 @enc_uint64(%struct.archive_write* %38, i64 0), !dbg !4386
  store i32 %call43, i32* %r, align 4, !dbg !4387
  %39 = load i32, i32* %r, align 4, !dbg !4388
  %cmp44 = icmp slt i32 %39, 0, !dbg !4390
  br i1 %cmp44, label %if.then46, label %if.end47, !dbg !4391

if.then46:                                        ; preds = %if.end42
  %40 = load i32, i32* %r, align 4, !dbg !4392
  store i32 %40, i32* %retval, align 4, !dbg !4393
  br label %return, !dbg !4393

if.end47:                                         ; preds = %if.end42
  %41 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4394
  %call48 = call i32 @enc_uint64(%struct.archive_write* %41, i64 7), !dbg !4395
  store i32 %call48, i32* %r, align 4, !dbg !4396
  %42 = load i32, i32* %r, align 4, !dbg !4397
  %cmp49 = icmp slt i32 %42, 0, !dbg !4399
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !4400

if.then51:                                        ; preds = %if.end47
  %43 = load i32, i32* %r, align 4, !dbg !4401
  store i32 %43, i32* %retval, align 4, !dbg !4402
  br label %return, !dbg !4402

if.end52:                                         ; preds = %if.end47
  %44 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4403
  %call53 = call i32 @enc_uint64(%struct.archive_write* %44, i64 11), !dbg !4404
  store i32 %call53, i32* %r, align 4, !dbg !4405
  %45 = load i32, i32* %r, align 4, !dbg !4406
  %cmp54 = icmp slt i32 %45, 0, !dbg !4408
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !4409

if.then56:                                        ; preds = %if.end52
  %46 = load i32, i32* %r, align 4, !dbg !4410
  store i32 %46, i32* %retval, align 4, !dbg !4411
  br label %return, !dbg !4411

if.end57:                                         ; preds = %if.end52
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4412
  %48 = load i32, i32* %numFolders, align 4, !dbg !4413
  %conv58 = sext i32 %48 to i64, !dbg !4413
  %call59 = call i32 @enc_uint64(%struct.archive_write* %47, i64 %conv58), !dbg !4414
  store i32 %call59, i32* %r, align 4, !dbg !4415
  %49 = load i32, i32* %r, align 4, !dbg !4416
  %cmp60 = icmp slt i32 %49, 0, !dbg !4418
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !4419

if.then62:                                        ; preds = %if.end57
  %50 = load i32, i32* %r, align 4, !dbg !4420
  store i32 %50, i32* %retval, align 4, !dbg !4421
  br label %return, !dbg !4421

if.end63:                                         ; preds = %if.end57
  %51 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4422
  %call64 = call i32 @enc_uint64(%struct.archive_write* %51, i64 0), !dbg !4423
  store i32 %call64, i32* %r, align 4, !dbg !4424
  %52 = load i32, i32* %r, align 4, !dbg !4425
  %cmp65 = icmp slt i32 %52, 0, !dbg !4427
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !4428

if.then67:                                        ; preds = %if.end63
  %53 = load i32, i32* %r, align 4, !dbg !4429
  store i32 %53, i32* %retval, align 4, !dbg !4430
  br label %return, !dbg !4430

if.end68:                                         ; preds = %if.end63
  store i32 0, i32* %fi, align 4, !dbg !4431
  br label %for.cond69, !dbg !4433

for.cond69:                                       ; preds = %for.inc150, %if.end68
  %54 = load i32, i32* %fi, align 4, !dbg !4434
  %55 = load i32, i32* %numFolders, align 4, !dbg !4437
  %cmp70 = icmp slt i32 %54, %55, !dbg !4438
  br i1 %cmp70, label %for.body72, label %for.end152, !dbg !4439

for.body72:                                       ; preds = %for.cond69
  %56 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4440
  %57 = load i32, i32* %num_coder.addr, align 4, !dbg !4442
  %conv73 = sext i32 %57 to i64, !dbg !4442
  %call74 = call i32 @enc_uint64(%struct.archive_write* %56, i64 %conv73), !dbg !4443
  store i32 %call74, i32* %r, align 4, !dbg !4444
  %58 = load i32, i32* %r, align 4, !dbg !4445
  %cmp75 = icmp slt i32 %58, 0, !dbg !4447
  br i1 %cmp75, label %if.then77, label %if.end78, !dbg !4448

if.then77:                                        ; preds = %for.body72
  %59 = load i32, i32* %r, align 4, !dbg !4449
  store i32 %59, i32* %retval, align 4, !dbg !4450
  br label %return, !dbg !4450

if.end78:                                         ; preds = %for.body72
  store i32 0, i32* %i, align 4, !dbg !4451
  br label %for.cond79, !dbg !4453

for.cond79:                                       ; preds = %for.inc148, %if.end78
  %60 = load i32, i32* %i, align 4, !dbg !4454
  %61 = load i32, i32* %num_coder.addr, align 4, !dbg !4457
  %cmp80 = icmp slt i32 %60, %61, !dbg !4458
  br i1 %cmp80, label %for.body82, label %for.end149, !dbg !4459

for.body82:                                       ; preds = %for.cond79
  call void @llvm.dbg.declare(metadata i32* %codec_id, metadata !4460, metadata !693), !dbg !4462
  %62 = load i32, i32* %i, align 4, !dbg !4463
  %idxprom = sext i32 %62 to i64, !dbg !4464
  %63 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4464
  %arrayidx = getelementptr inbounds %struct.coder, %struct.coder* %63, i64 %idxprom, !dbg !4464
  %codec83 = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx, i32 0, i32 0, !dbg !4465
  %64 = load i32, i32* %codec83, align 8, !dbg !4465
  store i32 %64, i32* %codec_id, align 4, !dbg !4462
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %codec_buff, i32 0, i32 0, !dbg !4466
  %65 = load i32, i32* %codec_id, align 4, !dbg !4467
  %conv84 = zext i32 %65 to i64, !dbg !4467
  call void @archive_be64enc(i8* %arraydecay, i64 %conv84), !dbg !4468
  store i32 8, i32* %codec_size, align 4, !dbg !4469
  br label %for.cond85, !dbg !4471

for.cond85:                                       ; preds = %for.inc93, %for.body82
  %66 = load i32, i32* %codec_size, align 4, !dbg !4472
  %cmp86 = icmp sgt i32 %66, 0, !dbg !4475
  br i1 %cmp86, label %for.body88, label %for.end94, !dbg !4476

for.body88:                                       ; preds = %for.cond85
  %67 = load i32, i32* %codec_size, align 4, !dbg !4477
  %sub = sub nsw i32 8, %67, !dbg !4480
  %idxprom89 = sext i32 %sub to i64, !dbg !4481
  %arrayidx90 = getelementptr inbounds [8 x i8], [8 x i8]* %codec_buff, i64 0, i64 %idxprom89, !dbg !4481
  %68 = load i8, i8* %arrayidx90, align 1, !dbg !4481
  %tobool = icmp ne i8 %68, 0, !dbg !4481
  br i1 %tobool, label %if.then91, label %if.end92, !dbg !4482

if.then91:                                        ; preds = %for.body88
  br label %for.end94, !dbg !4483

if.end92:                                         ; preds = %for.body88
  br label %for.inc93, !dbg !4484

for.inc93:                                        ; preds = %if.end92
  %69 = load i32, i32* %codec_size, align 4, !dbg !4485
  %dec = add nsw i32 %69, -1, !dbg !4485
  store i32 %dec, i32* %codec_size, align 4, !dbg !4485
  br label %for.cond85, !dbg !4487

for.end94:                                        ; preds = %if.then91, %for.cond85
  %70 = load i32, i32* %codec_size, align 4, !dbg !4488
  %cmp95 = icmp eq i32 %70, 0, !dbg !4490
  br i1 %cmp95, label %if.then97, label %if.end98, !dbg !4491

if.then97:                                        ; preds = %for.end94
  store i32 1, i32* %codec_size, align 4, !dbg !4492
  br label %if.end98, !dbg !4493

if.end98:                                         ; preds = %if.then97, %for.end94
  %71 = load i32, i32* %i, align 4, !dbg !4494
  %idxprom99 = sext i32 %71 to i64, !dbg !4496
  %72 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4496
  %arrayidx100 = getelementptr inbounds %struct.coder, %struct.coder* %72, i64 %idxprom99, !dbg !4496
  %prop_size = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx100, i32 0, i32 1, !dbg !4497
  %73 = load i64, i64* %prop_size, align 8, !dbg !4497
  %tobool101 = icmp ne i64 %73, 0, !dbg !4496
  br i1 %tobool101, label %if.then102, label %if.else105, !dbg !4498

if.then102:                                       ; preds = %if.end98
  %74 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4499
  %75 = load i32, i32* %codec_size, align 4, !dbg !4500
  %or = or i32 %75, 32, !dbg !4501
  %conv103 = sext i32 %or to i64, !dbg !4500
  %call104 = call i32 @enc_uint64(%struct.archive_write* %74, i64 %conv103), !dbg !4502
  store i32 %call104, i32* %r, align 4, !dbg !4503
  br label %if.end108, !dbg !4504

if.else105:                                       ; preds = %if.end98
  %76 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4505
  %77 = load i32, i32* %codec_size, align 4, !dbg !4506
  %conv106 = sext i32 %77 to i64, !dbg !4506
  %call107 = call i32 @enc_uint64(%struct.archive_write* %76, i64 %conv106), !dbg !4507
  store i32 %call107, i32* %r, align 4, !dbg !4508
  br label %if.end108

if.end108:                                        ; preds = %if.else105, %if.then102
  %78 = load i32, i32* %r, align 4, !dbg !4509
  %cmp109 = icmp slt i32 %78, 0, !dbg !4511
  br i1 %cmp109, label %if.then111, label %if.end112, !dbg !4512

if.then111:                                       ; preds = %if.end108
  %79 = load i32, i32* %r, align 4, !dbg !4513
  store i32 %79, i32* %retval, align 4, !dbg !4514
  br label %return, !dbg !4514

if.end112:                                        ; preds = %if.end108
  %80 = load i32, i32* %codec_size, align 4, !dbg !4515
  %and = and i32 %80, 15, !dbg !4515
  store i32 %and, i32* %codec_size, align 4, !dbg !4515
  %81 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4516
  %82 = load i32, i32* %codec_size, align 4, !dbg !4517
  %sub113 = sub nsw i32 8, %82, !dbg !4518
  %idxprom114 = sext i32 %sub113 to i64, !dbg !4519
  %arrayidx115 = getelementptr inbounds [8 x i8], [8 x i8]* %codec_buff, i64 0, i64 %idxprom114, !dbg !4519
  %83 = load i32, i32* %codec_size, align 4, !dbg !4520
  %conv116 = sext i32 %83 to i64, !dbg !4520
  %call117 = call i64 @compress_out(%struct.archive_write* %81, i8* %arrayidx115, i64 %conv116, i32 1), !dbg !4521
  %conv118 = trunc i64 %call117 to i32, !dbg !4522
  store i32 %conv118, i32* %r, align 4, !dbg !4523
  %84 = load i32, i32* %r, align 4, !dbg !4524
  %cmp119 = icmp slt i32 %84, 0, !dbg !4526
  br i1 %cmp119, label %if.then121, label %if.end122, !dbg !4527

if.then121:                                       ; preds = %if.end112
  %85 = load i32, i32* %r, align 4, !dbg !4528
  store i32 %85, i32* %retval, align 4, !dbg !4529
  br label %return, !dbg !4529

if.end122:                                        ; preds = %if.end112
  %86 = load i32, i32* %i, align 4, !dbg !4530
  %idxprom123 = sext i32 %86 to i64, !dbg !4532
  %87 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4532
  %arrayidx124 = getelementptr inbounds %struct.coder, %struct.coder* %87, i64 %idxprom123, !dbg !4532
  %prop_size125 = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx124, i32 0, i32 1, !dbg !4533
  %88 = load i64, i64* %prop_size125, align 8, !dbg !4533
  %tobool126 = icmp ne i64 %88, 0, !dbg !4532
  br i1 %tobool126, label %if.then127, label %if.end147, !dbg !4534

if.then127:                                       ; preds = %if.end122
  %89 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4535
  %90 = load i32, i32* %i, align 4, !dbg !4537
  %idxprom128 = sext i32 %90 to i64, !dbg !4538
  %91 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4538
  %arrayidx129 = getelementptr inbounds %struct.coder, %struct.coder* %91, i64 %idxprom128, !dbg !4538
  %prop_size130 = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx129, i32 0, i32 1, !dbg !4539
  %92 = load i64, i64* %prop_size130, align 8, !dbg !4539
  %call131 = call i32 @enc_uint64(%struct.archive_write* %89, i64 %92), !dbg !4540
  store i32 %call131, i32* %r, align 4, !dbg !4541
  %93 = load i32, i32* %r, align 4, !dbg !4542
  %cmp132 = icmp slt i32 %93, 0, !dbg !4544
  br i1 %cmp132, label %if.then134, label %if.end135, !dbg !4545

if.then134:                                       ; preds = %if.then127
  %94 = load i32, i32* %r, align 4, !dbg !4546
  store i32 %94, i32* %retval, align 4, !dbg !4547
  br label %return, !dbg !4547

if.end135:                                        ; preds = %if.then127
  %95 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4548
  %96 = load i32, i32* %i, align 4, !dbg !4549
  %idxprom136 = sext i32 %96 to i64, !dbg !4550
  %97 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4550
  %arrayidx137 = getelementptr inbounds %struct.coder, %struct.coder* %97, i64 %idxprom136, !dbg !4550
  %props = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx137, i32 0, i32 2, !dbg !4551
  %98 = load i8*, i8** %props, align 8, !dbg !4551
  %99 = load i32, i32* %i, align 4, !dbg !4552
  %idxprom138 = sext i32 %99 to i64, !dbg !4553
  %100 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4553
  %arrayidx139 = getelementptr inbounds %struct.coder, %struct.coder* %100, i64 %idxprom138, !dbg !4553
  %prop_size140 = getelementptr inbounds %struct.coder, %struct.coder* %arrayidx139, i32 0, i32 1, !dbg !4554
  %101 = load i64, i64* %prop_size140, align 8, !dbg !4554
  %call141 = call i64 @compress_out(%struct.archive_write* %95, i8* %98, i64 %101, i32 1), !dbg !4555
  %conv142 = trunc i64 %call141 to i32, !dbg !4556
  store i32 %conv142, i32* %r, align 4, !dbg !4557
  %102 = load i32, i32* %r, align 4, !dbg !4558
  %cmp143 = icmp slt i32 %102, 0, !dbg !4560
  br i1 %cmp143, label %if.then145, label %if.end146, !dbg !4561

if.then145:                                       ; preds = %if.end135
  %103 = load i32, i32* %r, align 4, !dbg !4562
  store i32 %103, i32* %retval, align 4, !dbg !4563
  br label %return, !dbg !4563

if.end146:                                        ; preds = %if.end135
  br label %if.end147, !dbg !4564

if.end147:                                        ; preds = %if.end146, %if.end122
  br label %for.inc148, !dbg !4565

for.inc148:                                       ; preds = %if.end147
  %104 = load i32, i32* %i, align 4, !dbg !4566
  %inc = add nsw i32 %104, 1, !dbg !4566
  store i32 %inc, i32* %i, align 4, !dbg !4566
  br label %for.cond79, !dbg !4568

for.end149:                                       ; preds = %for.cond79
  br label %for.inc150, !dbg !4569

for.inc150:                                       ; preds = %for.end149
  %105 = load i32, i32* %fi, align 4, !dbg !4570
  %inc151 = add nsw i32 %105, 1, !dbg !4570
  store i32 %inc151, i32* %fi, align 4, !dbg !4570
  br label %for.cond69, !dbg !4572

for.end152:                                       ; preds = %for.cond69
  %106 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4573
  %call153 = call i32 @enc_uint64(%struct.archive_write* %106, i64 12), !dbg !4574
  store i32 %call153, i32* %r, align 4, !dbg !4575
  %107 = load i32, i32* %r, align 4, !dbg !4576
  %cmp154 = icmp slt i32 %107, 0, !dbg !4578
  br i1 %cmp154, label %if.then156, label %if.end157, !dbg !4579

if.then156:                                       ; preds = %for.end152
  %108 = load i32, i32* %r, align 4, !dbg !4580
  store i32 %108, i32* %retval, align 4, !dbg !4581
  br label %return, !dbg !4581

if.end157:                                        ; preds = %for.end152
  %109 = load i32, i32* %numFolders, align 4, !dbg !4582
  %cmp158 = icmp sgt i32 %109, 1, !dbg !4584
  br i1 %cmp158, label %if.then160, label %if.else182, !dbg !4585

if.then160:                                       ; preds = %if.end157
  call void @llvm.dbg.declare(metadata %struct.file** %file161, metadata !4586, metadata !693), !dbg !4588
  %110 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4589
  %file_list162 = getelementptr inbounds %struct._7zip, %struct._7zip* %110, i32 0, i32 23, !dbg !4590
  %first163 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list162, i32 0, i32 0, !dbg !4591
  %111 = load %struct.file*, %struct.file** %first163, align 8, !dbg !4591
  store %struct.file* %111, %struct.file** %file161, align 8, !dbg !4588
  br label %for.cond164, !dbg !4592

for.cond164:                                      ; preds = %for.inc179, %if.then160
  %112 = load %struct.file*, %struct.file** %file161, align 8, !dbg !4593
  %cmp165 = icmp ne %struct.file* %112, null, !dbg !4597
  br i1 %cmp165, label %for.body167, label %for.end181, !dbg !4598

for.body167:                                      ; preds = %for.cond164
  %113 = load %struct.file*, %struct.file** %file161, align 8, !dbg !4599
  %size168 = getelementptr inbounds %struct.file, %struct.file* %113, i32 0, i32 4, !dbg !4602
  %114 = load i64, i64* %size168, align 8, !dbg !4602
  %cmp169 = icmp eq i64 %114, 0, !dbg !4603
  br i1 %cmp169, label %if.then171, label %if.end172, !dbg !4604

if.then171:                                       ; preds = %for.body167
  br label %for.end181, !dbg !4605

if.end172:                                        ; preds = %for.body167
  %115 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4606
  %116 = load %struct.file*, %struct.file** %file161, align 8, !dbg !4607
  %size173 = getelementptr inbounds %struct.file, %struct.file* %116, i32 0, i32 4, !dbg !4608
  %117 = load i64, i64* %size173, align 8, !dbg !4608
  %call174 = call i32 @enc_uint64(%struct.archive_write* %115, i64 %117), !dbg !4609
  store i32 %call174, i32* %r, align 4, !dbg !4610
  %118 = load i32, i32* %r, align 4, !dbg !4611
  %cmp175 = icmp slt i32 %118, 0, !dbg !4613
  br i1 %cmp175, label %if.then177, label %if.end178, !dbg !4614

if.then177:                                       ; preds = %if.end172
  %119 = load i32, i32* %r, align 4, !dbg !4615
  store i32 %119, i32* %retval, align 4, !dbg !4616
  br label %return, !dbg !4616

if.end178:                                        ; preds = %if.end172
  br label %for.inc179, !dbg !4617

for.inc179:                                       ; preds = %if.end178
  %120 = load %struct.file*, %struct.file** %file161, align 8, !dbg !4618
  %next180 = getelementptr inbounds %struct.file, %struct.file* %120, i32 0, i32 1, !dbg !4620
  %121 = load %struct.file*, %struct.file** %next180, align 8, !dbg !4620
  store %struct.file* %121, %struct.file** %file161, align 8, !dbg !4621
  br label %for.cond164, !dbg !4622

for.end181:                                       ; preds = %if.then171, %for.cond164
  br label %if.end188, !dbg !4623

if.else182:                                       ; preds = %if.end157
  %122 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4624
  %123 = load i64, i64* %unpack_size.addr, align 8, !dbg !4626
  %call183 = call i32 @enc_uint64(%struct.archive_write* %122, i64 %123), !dbg !4627
  store i32 %call183, i32* %r, align 4, !dbg !4628
  %124 = load i32, i32* %r, align 4, !dbg !4629
  %cmp184 = icmp slt i32 %124, 0, !dbg !4631
  br i1 %cmp184, label %if.then186, label %if.end187, !dbg !4632

if.then186:                                       ; preds = %if.else182
  %125 = load i32, i32* %r, align 4, !dbg !4633
  store i32 %125, i32* %retval, align 4, !dbg !4634
  br label %return, !dbg !4634

if.end187:                                        ; preds = %if.else182
  br label %if.end188

if.end188:                                        ; preds = %if.end187, %for.end181
  %126 = load i32, i32* %substrm.addr, align 4, !dbg !4635
  %tobool189 = icmp ne i32 %126, 0, !dbg !4635
  br i1 %tobool189, label %if.end209, label %if.then190, !dbg !4637

if.then190:                                       ; preds = %if.end188
  call void @llvm.dbg.declare(metadata [4 x i8]* %crc, metadata !4638, metadata !693), !dbg !4643
  %127 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4644
  %call191 = call i32 @enc_uint64(%struct.archive_write* %127, i64 10), !dbg !4645
  store i32 %call191, i32* %r, align 4, !dbg !4646
  %128 = load i32, i32* %r, align 4, !dbg !4647
  %cmp192 = icmp slt i32 %128, 0, !dbg !4649
  br i1 %cmp192, label %if.then194, label %if.end195, !dbg !4650

if.then194:                                       ; preds = %if.then190
  %129 = load i32, i32* %r, align 4, !dbg !4651
  store i32 %129, i32* %retval, align 4, !dbg !4652
  br label %return, !dbg !4652

if.end195:                                        ; preds = %if.then190
  %130 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4653
  %call196 = call i32 @enc_uint64(%struct.archive_write* %130, i64 1), !dbg !4654
  store i32 %call196, i32* %r, align 4, !dbg !4655
  %131 = load i32, i32* %r, align 4, !dbg !4656
  %cmp197 = icmp slt i32 %131, 0, !dbg !4658
  br i1 %cmp197, label %if.then199, label %if.end200, !dbg !4659

if.then199:                                       ; preds = %if.end195
  %132 = load i32, i32* %r, align 4, !dbg !4660
  store i32 %132, i32* %retval, align 4, !dbg !4661
  br label %return, !dbg !4661

if.end200:                                        ; preds = %if.end195
  %arraydecay201 = getelementptr inbounds [4 x i8], [4 x i8]* %crc, i32 0, i32 0, !dbg !4662
  %133 = load i32, i32* %header_crc.addr, align 4, !dbg !4663
  call void @archive_le32enc(i8* %arraydecay201, i32 %133), !dbg !4664
  %134 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4665
  %arraydecay202 = getelementptr inbounds [4 x i8], [4 x i8]* %crc, i32 0, i32 0, !dbg !4666
  %call203 = call i64 @compress_out(%struct.archive_write* %134, i8* %arraydecay202, i64 4, i32 1), !dbg !4667
  %conv204 = trunc i64 %call203 to i32, !dbg !4668
  store i32 %conv204, i32* %r, align 4, !dbg !4669
  %135 = load i32, i32* %r, align 4, !dbg !4670
  %cmp205 = icmp slt i32 %135, 0, !dbg !4672
  br i1 %cmp205, label %if.then207, label %if.end208, !dbg !4673

if.then207:                                       ; preds = %if.end200
  %136 = load i32, i32* %r, align 4, !dbg !4674
  store i32 %136, i32* %retval, align 4, !dbg !4675
  br label %return, !dbg !4675

if.end208:                                        ; preds = %if.end200
  br label %if.end209, !dbg !4676

if.end209:                                        ; preds = %if.end208, %if.end188
  %137 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4677
  %call210 = call i32 @enc_uint64(%struct.archive_write* %137, i64 0), !dbg !4678
  store i32 %call210, i32* %r, align 4, !dbg !4679
  %138 = load i32, i32* %r, align 4, !dbg !4680
  %cmp211 = icmp slt i32 %138, 0, !dbg !4682
  br i1 %cmp211, label %if.then213, label %if.end214, !dbg !4683

if.then213:                                       ; preds = %if.end209
  %139 = load i32, i32* %r, align 4, !dbg !4684
  store i32 %139, i32* %retval, align 4, !dbg !4685
  br label %return, !dbg !4685

if.end214:                                        ; preds = %if.end209
  %140 = load i32, i32* %substrm.addr, align 4, !dbg !4686
  %tobool215 = icmp ne i32 %140, 0, !dbg !4686
  br i1 %tobool215, label %if.then216, label %if.end222, !dbg !4688

if.then216:                                       ; preds = %if.end214
  %141 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4689
  %142 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !4691
  %call217 = call i32 @make_substreamsInfo(%struct.archive_write* %141, %struct.coder* %142), !dbg !4692
  store i32 %call217, i32* %r, align 4, !dbg !4693
  %143 = load i32, i32* %r, align 4, !dbg !4694
  %cmp218 = icmp slt i32 %143, 0, !dbg !4696
  br i1 %cmp218, label %if.then220, label %if.end221, !dbg !4697

if.then220:                                       ; preds = %if.then216
  %144 = load i32, i32* %r, align 4, !dbg !4698
  store i32 %144, i32* %retval, align 4, !dbg !4699
  br label %return, !dbg !4699

if.end221:                                        ; preds = %if.then216
  br label %if.end222, !dbg !4700

if.end222:                                        ; preds = %if.end221, %if.end214
  %145 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4701
  %call223 = call i32 @enc_uint64(%struct.archive_write* %145, i64 0), !dbg !4702
  store i32 %call223, i32* %r, align 4, !dbg !4703
  %146 = load i32, i32* %r, align 4, !dbg !4704
  %cmp224 = icmp slt i32 %146, 0, !dbg !4706
  br i1 %cmp224, label %if.then226, label %if.end227, !dbg !4707

if.then226:                                       ; preds = %if.end222
  %147 = load i32, i32* %r, align 4, !dbg !4708
  store i32 %147, i32* %retval, align 4, !dbg !4709
  br label %return, !dbg !4709

if.end227:                                        ; preds = %if.end222
  store i32 0, i32* %retval, align 4, !dbg !4710
  br label %return, !dbg !4710

return:                                           ; preds = %if.end227, %if.then226, %if.then220, %if.then213, %if.then207, %if.then199, %if.then194, %if.then186, %if.then177, %if.then156, %if.then145, %if.then134, %if.then121, %if.then111, %if.then77, %if.then67, %if.then62, %if.then56, %if.then51, %if.then46, %if.then40, %if.then34, %if.then19, %if.then14, %if.then8, %if.then3
  %148 = load i32, i32* %retval, align 4, !dbg !4711
  ret i32 %148, !dbg !4711
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le64enc(i8* %pp, i64 %u) #7 !dbg !665 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !4712, metadata !693), !dbg !4713
  store i64 %u, i64* %u.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %u.addr, metadata !4714, metadata !693), !dbg !4715
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4716, metadata !693), !dbg !4717
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !4718
  store i8* %0, i8** %p, align 8, !dbg !4717
  %1 = load i8*, i8** %p, align 8, !dbg !4719
  %2 = load i64, i64* %u.addr, align 8, !dbg !4720
  %and = and i64 %2, 4294967295, !dbg !4721
  %conv = trunc i64 %and to i32, !dbg !4722
  call void @archive_le32enc(i8* %1, i32 %conv), !dbg !4723
  %3 = load i8*, i8** %p, align 8, !dbg !4724
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !4725
  %4 = load i64, i64* %u.addr, align 8, !dbg !4726
  %shr = lshr i64 %4, 32, !dbg !4727
  %conv1 = trunc i64 %shr to i32, !dbg !4728
  call void @archive_le32enc(i8* %add.ptr, i32 %conv1), !dbg !4729
  ret void, !dbg !4730
}

; Function Attrs: nounwind uwtable
define internal i32 @copy_out(%struct.archive_write* %a, i64 %offset, i64 %length) #0 !dbg !666 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %offset.addr = alloca i64, align 8
  %length.addr = alloca i64, align 8
  %zip = alloca %struct._7zip*, align 8
  %r = alloca i32, align 4
  %rsize = alloca i64, align 8
  %rs = alloca i64, align 8
  %wb = alloca i8*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !4731, metadata !693), !dbg !4732
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !4733, metadata !693), !dbg !4734
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !4735, metadata !693), !dbg !4736
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !4737, metadata !693), !dbg !4738
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4739, metadata !693), !dbg !4740
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4741
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !4742
  %1 = load i8*, i8** %format_data, align 8, !dbg !4742
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !4743
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !4744
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4745
  %temp_offset = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 1, !dbg !4747
  %4 = load i64, i64* %temp_offset, align 8, !dbg !4747
  %cmp = icmp ugt i64 %4, 0, !dbg !4748
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !4749

land.lhs.true:                                    ; preds = %entry
  %5 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4750
  %temp_fd = getelementptr inbounds %struct._7zip, %struct._7zip* %5, i32 0, i32 0, !dbg !4751
  %6 = load i32, i32* %temp_fd, align 8, !dbg !4751
  %7 = load i64, i64* %offset.addr, align 8, !dbg !4752
  %call = call i64 @lseek(i32 %6, i64 %7, i32 0) #8, !dbg !4753
  %cmp1 = icmp slt i64 %call, 0, !dbg !4754
  br i1 %cmp1, label %if.then, label %if.end, !dbg !4755

if.then:                                          ; preds = %land.lhs.true
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4757
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !4759
  %call2 = call i32* @__errno_location() #1, !dbg !4760
  %9 = load i32, i32* %call2, align 4, !dbg !4760
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %9, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.48, i32 0, i32 0)), !dbg !4761
  store i32 -30, i32* %retval, align 4, !dbg !4763
  br label %return, !dbg !4763

if.end:                                           ; preds = %land.lhs.true, %entry
  br label %while.cond, !dbg !4764

while.cond:                                       ; preds = %if.end29, %if.end
  %10 = load i64, i64* %length.addr, align 8, !dbg !4765
  %tobool = icmp ne i64 %10, 0, !dbg !4766
  br i1 %tobool, label %while.body, label %while.end, !dbg !4766

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %rsize, metadata !4767, metadata !693), !dbg !4769
  call void @llvm.dbg.declare(metadata i64* %rs, metadata !4770, metadata !693), !dbg !4771
  call void @llvm.dbg.declare(metadata i8** %wb, metadata !4772, metadata !693), !dbg !4773
  %11 = load i64, i64* %length.addr, align 8, !dbg !4774
  %12 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4776
  %wbuff_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %12, i32 0, i32 22, !dbg !4777
  %13 = load i64, i64* %wbuff_remaining, align 8, !dbg !4777
  %cmp3 = icmp ugt i64 %11, %13, !dbg !4778
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !4779

if.then4:                                         ; preds = %while.body
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4780
  %wbuff_remaining5 = getelementptr inbounds %struct._7zip, %struct._7zip* %14, i32 0, i32 22, !dbg !4781
  %15 = load i64, i64* %wbuff_remaining5, align 8, !dbg !4781
  store i64 %15, i64* %rsize, align 8, !dbg !4782
  br label %if.end6, !dbg !4783

if.else:                                          ; preds = %while.body
  %16 = load i64, i64* %length.addr, align 8, !dbg !4784
  store i64 %16, i64* %rsize, align 8, !dbg !4785
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then4
  %17 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4786
  %wbuff = getelementptr inbounds %struct._7zip, %struct._7zip* %17, i32 0, i32 21, !dbg !4787
  %arraydecay = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff, i32 0, i32 0, !dbg !4786
  %18 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4788
  %wbuff_remaining7 = getelementptr inbounds %struct._7zip, %struct._7zip* %18, i32 0, i32 22, !dbg !4789
  %19 = load i64, i64* %wbuff_remaining7, align 8, !dbg !4789
  %sub = sub i64 61440, %19, !dbg !4790
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 %sub, !dbg !4791
  store i8* %add.ptr, i8** %wb, align 8, !dbg !4792
  %20 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4793
  %temp_fd8 = getelementptr inbounds %struct._7zip, %struct._7zip* %20, i32 0, i32 0, !dbg !4794
  %21 = load i32, i32* %temp_fd8, align 8, !dbg !4794
  %22 = load i8*, i8** %wb, align 8, !dbg !4795
  %23 = load i64, i64* %rsize, align 8, !dbg !4796
  %call9 = call i64 @read(i32 %21, i8* %22, i64 %23), !dbg !4797
  store i64 %call9, i64* %rs, align 8, !dbg !4798
  %24 = load i64, i64* %rs, align 8, !dbg !4799
  %cmp10 = icmp slt i64 %24, 0, !dbg !4801
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !4802

if.then11:                                        ; preds = %if.end6
  %25 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4803
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 0, !dbg !4805
  %call13 = call i32* @__errno_location() #1, !dbg !4806
  %26 = load i32, i32* %call13, align 4, !dbg !4806
  %27 = load i64, i64* %rs, align 8, !dbg !4807
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive12, i32 %26, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.49, i32 0, i32 0), i64 %27), !dbg !4808
  store i32 -30, i32* %retval, align 4, !dbg !4810
  br label %return, !dbg !4810

if.end14:                                         ; preds = %if.end6
  %28 = load i64, i64* %rs, align 8, !dbg !4811
  %cmp15 = icmp eq i64 %28, 0, !dbg !4813
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !4814

if.then16:                                        ; preds = %if.end14
  %29 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4815
  %archive17 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 0, !dbg !4817
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 0, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.50, i32 0, i32 0)), !dbg !4818
  store i32 -30, i32* %retval, align 4, !dbg !4819
  br label %return, !dbg !4819

if.end18:                                         ; preds = %if.end14
  %30 = load i64, i64* %rs, align 8, !dbg !4820
  %31 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4821
  %wbuff_remaining19 = getelementptr inbounds %struct._7zip, %struct._7zip* %31, i32 0, i32 22, !dbg !4822
  %32 = load i64, i64* %wbuff_remaining19, align 8, !dbg !4823
  %sub20 = sub i64 %32, %30, !dbg !4823
  store i64 %sub20, i64* %wbuff_remaining19, align 8, !dbg !4823
  %33 = load i64, i64* %rs, align 8, !dbg !4824
  %34 = load i64, i64* %length.addr, align 8, !dbg !4825
  %sub21 = sub i64 %34, %33, !dbg !4825
  store i64 %sub21, i64* %length.addr, align 8, !dbg !4825
  %35 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4826
  %wbuff_remaining22 = getelementptr inbounds %struct._7zip, %struct._7zip* %35, i32 0, i32 22, !dbg !4828
  %36 = load i64, i64* %wbuff_remaining22, align 8, !dbg !4828
  %cmp23 = icmp eq i64 %36, 0, !dbg !4829
  br i1 %cmp23, label %if.then24, label %if.end29, !dbg !4830

if.then24:                                        ; preds = %if.end18
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4831
  %call25 = call i32 @flush_wbuff(%struct.archive_write* %37), !dbg !4833
  store i32 %call25, i32* %r, align 4, !dbg !4834
  %38 = load i32, i32* %r, align 4, !dbg !4835
  %cmp26 = icmp ne i32 %38, 0, !dbg !4837
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !4838

if.then27:                                        ; preds = %if.then24
  %39 = load i32, i32* %r, align 4, !dbg !4839
  store i32 %39, i32* %retval, align 4, !dbg !4840
  br label %return, !dbg !4840

if.end28:                                         ; preds = %if.then24
  br label %if.end29, !dbg !4841

if.end29:                                         ; preds = %if.end28, %if.end18
  br label %while.cond, !dbg !4842

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !4844
  br label %return, !dbg !4844

return:                                           ; preds = %while.end, %if.then27, %if.then16, %if.then11, %if.then
  %40 = load i32, i32* %retval, align 4, !dbg !4845
  ret i32 %40, !dbg !4845
}

; Function Attrs: nounwind uwtable
define internal i32 @flush_wbuff(%struct.archive_write* %a) #0 !dbg !669 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct._7zip*, align 8
  %r = alloca i32, align 4
  %s = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !4846, metadata !693), !dbg !4847
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !4848, metadata !693), !dbg !4849
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4850, metadata !693), !dbg !4851
  call void @llvm.dbg.declare(metadata i64* %s, metadata !4852, metadata !693), !dbg !4853
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4854
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !4855
  %1 = load i8*, i8** %format_data, align 8, !dbg !4855
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !4856
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !4857
  %3 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4858
  %wbuff_remaining = getelementptr inbounds %struct._7zip, %struct._7zip* %3, i32 0, i32 22, !dbg !4859
  %4 = load i64, i64* %wbuff_remaining, align 8, !dbg !4859
  %sub = sub i64 61440, %4, !dbg !4860
  store i64 %sub, i64* %s, align 8, !dbg !4861
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4862
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4863
  %wbuff = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 21, !dbg !4864
  %arraydecay = getelementptr inbounds [61440 x i8], [61440 x i8]* %wbuff, i32 0, i32 0, !dbg !4863
  %7 = load i64, i64* %s, align 8, !dbg !4865
  %call = call i32 @__archive_write_output(%struct.archive_write* %5, i8* %arraydecay, i64 %7), !dbg !4866
  store i32 %call, i32* %r, align 4, !dbg !4867
  %8 = load i32, i32* %r, align 4, !dbg !4868
  %cmp = icmp ne i32 %8, 0, !dbg !4870
  br i1 %cmp, label %if.then, label %if.end, !dbg !4871

if.then:                                          ; preds = %entry
  %9 = load i32, i32* %r, align 4, !dbg !4872
  store i32 %9, i32* %retval, align 4, !dbg !4873
  br label %return, !dbg !4873

if.end:                                           ; preds = %entry
  %10 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4874
  %wbuff_remaining1 = getelementptr inbounds %struct._7zip, %struct._7zip* %10, i32 0, i32 22, !dbg !4875
  store i64 61440, i64* %wbuff_remaining1, align 8, !dbg !4876
  %11 = load i32, i32* %r, align 4, !dbg !4877
  store i32 %11, i32* %retval, align 4, !dbg !4878
  br label %return, !dbg !4878

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !4879
  ret i32 %12, !dbg !4879
}

; Function Attrs: nounwind uwtable
define internal i32 @make_time(%struct.archive_write* %a, i8 zeroext %type, i32 %flg, i32 %ti) #0 !dbg !646 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %type.addr = alloca i8, align 1
  %flg.addr = alloca i32, align 4
  %ti.addr = alloca i32, align 4
  %filetime = alloca [8 x i8], align 1
  %zip = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %r = alloca i32, align 4
  %b = alloca i8, align 1
  %mask = alloca i8, align 1
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !4880, metadata !693), !dbg !4881
  store i8 %type, i8* %type.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %type.addr, metadata !4882, metadata !693), !dbg !4883
  store i32 %flg, i32* %flg.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flg.addr, metadata !4884, metadata !693), !dbg !4885
  store i32 %ti, i32* %ti.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ti.addr, metadata !4886, metadata !693), !dbg !4887
  call void @llvm.dbg.declare(metadata [8 x i8]* %filetime, metadata !4888, metadata !693), !dbg !4889
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !4890, metadata !693), !dbg !4891
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4892
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !4893
  %1 = load i8*, i8** %format_data, align 8, !dbg !4893
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !4894
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !4891
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !4895, metadata !693), !dbg !4896
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4897, metadata !693), !dbg !4898
  call void @llvm.dbg.declare(metadata i8* %b, metadata !4899, metadata !693), !dbg !4900
  call void @llvm.dbg.declare(metadata i8* %mask, metadata !4901, metadata !693), !dbg !4902
  %3 = load i32, i32* %ti.addr, align 4, !dbg !4903
  %idxprom = sext i32 %3 to i64, !dbg !4905
  %4 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4905
  %total_number_time_defined = getelementptr inbounds %struct._7zip, %struct._7zip* %4, i32 0, i32 8, !dbg !4906
  %arrayidx = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined, i64 0, i64 %idxprom, !dbg !4905
  %5 = load i64, i64* %arrayidx, align 8, !dbg !4905
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4907
  %total_number_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 3, !dbg !4908
  %7 = load i64, i64* %total_number_entry, align 8, !dbg !4908
  %cmp = icmp eq i64 %5, %7, !dbg !4909
  br i1 %cmp, label %if.then, label %if.else, !dbg !4910

if.then:                                          ; preds = %entry
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4911
  %9 = load i8, i8* %type.addr, align 1, !dbg !4913
  %conv = zext i8 %9 to i64, !dbg !4913
  %call = call i32 @enc_uint64(%struct.archive_write* %8, i64 %conv), !dbg !4914
  store i32 %call, i32* %r, align 4, !dbg !4915
  %10 = load i32, i32* %r, align 4, !dbg !4916
  %cmp1 = icmp slt i32 %10, 0, !dbg !4918
  br i1 %cmp1, label %if.then3, label %if.end, !dbg !4919

if.then3:                                         ; preds = %if.then
  %11 = load i32, i32* %r, align 4, !dbg !4920
  store i32 %11, i32* %retval, align 4, !dbg !4921
  br label %return, !dbg !4921

if.end:                                           ; preds = %if.then
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4922
  %13 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4923
  %total_number_entry4 = getelementptr inbounds %struct._7zip, %struct._7zip* %13, i32 0, i32 3, !dbg !4924
  %14 = load i64, i64* %total_number_entry4, align 8, !dbg !4924
  %mul = mul i64 %14, 8, !dbg !4925
  %add = add i64 2, %mul, !dbg !4926
  %call5 = call i32 @enc_uint64(%struct.archive_write* %12, i64 %add), !dbg !4927
  store i32 %call5, i32* %r, align 4, !dbg !4928
  %15 = load i32, i32* %r, align 4, !dbg !4929
  %cmp6 = icmp slt i32 %15, 0, !dbg !4931
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !4932

if.then8:                                         ; preds = %if.end
  %16 = load i32, i32* %r, align 4, !dbg !4933
  store i32 %16, i32* %retval, align 4, !dbg !4934
  br label %return, !dbg !4934

if.end9:                                          ; preds = %if.end
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4935
  %call10 = call i32 @enc_uint64(%struct.archive_write* %17, i64 1), !dbg !4936
  store i32 %call10, i32* %r, align 4, !dbg !4937
  %18 = load i32, i32* %r, align 4, !dbg !4938
  %cmp11 = icmp slt i32 %18, 0, !dbg !4940
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !4941

if.then13:                                        ; preds = %if.end9
  %19 = load i32, i32* %r, align 4, !dbg !4942
  store i32 %19, i32* %retval, align 4, !dbg !4943
  br label %return, !dbg !4943

if.end14:                                         ; preds = %if.end9
  br label %if.end79, !dbg !4944

if.else:                                          ; preds = %entry
  %20 = load i32, i32* %ti.addr, align 4, !dbg !4945
  %idxprom15 = sext i32 %20 to i64, !dbg !4948
  %21 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4948
  %total_number_time_defined16 = getelementptr inbounds %struct._7zip, %struct._7zip* %21, i32 0, i32 8, !dbg !4949
  %arrayidx17 = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined16, i64 0, i64 %idxprom15, !dbg !4948
  %22 = load i64, i64* %arrayidx17, align 8, !dbg !4948
  %cmp18 = icmp eq i64 %22, 0, !dbg !4950
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !4951

if.then20:                                        ; preds = %if.else
  store i32 0, i32* %retval, align 4, !dbg !4952
  br label %return, !dbg !4952

if.end21:                                         ; preds = %if.else
  %23 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4953
  %24 = load i8, i8* %type.addr, align 1, !dbg !4954
  %conv22 = zext i8 %24 to i64, !dbg !4954
  %call23 = call i32 @enc_uint64(%struct.archive_write* %23, i64 %conv22), !dbg !4955
  store i32 %call23, i32* %r, align 4, !dbg !4956
  %25 = load i32, i32* %r, align 4, !dbg !4957
  %cmp24 = icmp slt i32 %25, 0, !dbg !4959
  br i1 %cmp24, label %if.then26, label %if.end27, !dbg !4960

if.then26:                                        ; preds = %if.end21
  %26 = load i32, i32* %r, align 4, !dbg !4961
  store i32 %26, i32* %retval, align 4, !dbg !4962
  br label %return, !dbg !4962

if.end27:                                         ; preds = %if.end21
  %27 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4963
  %28 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4964
  %total_number_entry28 = getelementptr inbounds %struct._7zip, %struct._7zip* %28, i32 0, i32 3, !dbg !4965
  %29 = load i64, i64* %total_number_entry28, align 8, !dbg !4965
  %add29 = add i64 %29, 7, !dbg !4966
  %shr = lshr i64 %add29, 3, !dbg !4967
  %add30 = add i64 2, %shr, !dbg !4968
  %30 = load i32, i32* %ti.addr, align 4, !dbg !4969
  %idxprom31 = sext i32 %30 to i64, !dbg !4970
  %31 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4970
  %total_number_time_defined32 = getelementptr inbounds %struct._7zip, %struct._7zip* %31, i32 0, i32 8, !dbg !4971
  %arrayidx33 = getelementptr inbounds [3 x i64], [3 x i64]* %total_number_time_defined32, i64 0, i64 %idxprom31, !dbg !4970
  %32 = load i64, i64* %arrayidx33, align 8, !dbg !4970
  %mul34 = mul i64 %32, 8, !dbg !4972
  %add35 = add i64 %add30, %mul34, !dbg !4973
  %call36 = call i32 @enc_uint64(%struct.archive_write* %27, i64 %add35), !dbg !4974
  store i32 %call36, i32* %r, align 4, !dbg !4975
  %33 = load i32, i32* %r, align 4, !dbg !4976
  %cmp37 = icmp slt i32 %33, 0, !dbg !4978
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !4979

if.then39:                                        ; preds = %if.end27
  %34 = load i32, i32* %r, align 4, !dbg !4980
  store i32 %34, i32* %retval, align 4, !dbg !4981
  br label %return, !dbg !4981

if.end40:                                         ; preds = %if.end27
  %35 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4982
  %call41 = call i32 @enc_uint64(%struct.archive_write* %35, i64 0), !dbg !4983
  store i32 %call41, i32* %r, align 4, !dbg !4984
  %36 = load i32, i32* %r, align 4, !dbg !4985
  %cmp42 = icmp slt i32 %36, 0, !dbg !4987
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !4988

if.then44:                                        ; preds = %if.end40
  %37 = load i32, i32* %r, align 4, !dbg !4989
  store i32 %37, i32* %retval, align 4, !dbg !4990
  br label %return, !dbg !4990

if.end45:                                         ; preds = %if.end40
  store i8 0, i8* %b, align 1, !dbg !4991
  store i8 -128, i8* %mask, align 1, !dbg !4992
  %38 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !4993
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %38, i32 0, i32 23, !dbg !4994
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !4995
  %39 = load %struct.file*, %struct.file** %first, align 8, !dbg !4995
  store %struct.file* %39, %struct.file** %file, align 8, !dbg !4996
  br label %for.cond, !dbg !4997

for.cond:                                         ; preds = %for.inc, %if.end45
  %40 = load %struct.file*, %struct.file** %file, align 8, !dbg !4998
  %cmp46 = icmp ne %struct.file* %40, null, !dbg !5002
  br i1 %cmp46, label %for.body, label %for.end, !dbg !5003

for.body:                                         ; preds = %for.cond
  %41 = load %struct.file*, %struct.file** %file, align 8, !dbg !5004
  %flg48 = getelementptr inbounds %struct.file, %struct.file* %41, i32 0, i32 5, !dbg !5007
  %42 = load i32, i32* %flg48, align 8, !dbg !5007
  %43 = load i32, i32* %flg.addr, align 4, !dbg !5008
  %and = and i32 %42, %43, !dbg !5009
  %tobool = icmp ne i32 %and, 0, !dbg !5009
  br i1 %tobool, label %if.then49, label %if.end53, !dbg !5010

if.then49:                                        ; preds = %for.body
  %44 = load i8, i8* %mask, align 1, !dbg !5011
  %conv50 = zext i8 %44 to i32, !dbg !5011
  %45 = load i8, i8* %b, align 1, !dbg !5012
  %conv51 = zext i8 %45 to i32, !dbg !5012
  %or = or i32 %conv51, %conv50, !dbg !5012
  %conv52 = trunc i32 %or to i8, !dbg !5012
  store i8 %conv52, i8* %b, align 1, !dbg !5012
  br label %if.end53, !dbg !5013

if.end53:                                         ; preds = %if.then49, %for.body
  %46 = load i8, i8* %mask, align 1, !dbg !5014
  %conv54 = zext i8 %46 to i32, !dbg !5014
  %shr55 = ashr i32 %conv54, 1, !dbg !5014
  %conv56 = trunc i32 %shr55 to i8, !dbg !5014
  store i8 %conv56, i8* %mask, align 1, !dbg !5014
  %47 = load i8, i8* %mask, align 1, !dbg !5015
  %conv57 = zext i8 %47 to i32, !dbg !5015
  %cmp58 = icmp eq i32 %conv57, 0, !dbg !5017
  br i1 %cmp58, label %if.then60, label %if.end67, !dbg !5018

if.then60:                                        ; preds = %if.end53
  %48 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5019
  %call61 = call i64 @compress_out(%struct.archive_write* %48, i8* %b, i64 1, i32 1), !dbg !5021
  %conv62 = trunc i64 %call61 to i32, !dbg !5022
  store i32 %conv62, i32* %r, align 4, !dbg !5023
  %49 = load i32, i32* %r, align 4, !dbg !5024
  %cmp63 = icmp slt i32 %49, 0, !dbg !5026
  br i1 %cmp63, label %if.then65, label %if.end66, !dbg !5027

if.then65:                                        ; preds = %if.then60
  %50 = load i32, i32* %r, align 4, !dbg !5028
  store i32 %50, i32* %retval, align 4, !dbg !5029
  br label %return, !dbg !5029

if.end66:                                         ; preds = %if.then60
  store i8 -128, i8* %mask, align 1, !dbg !5030
  store i8 0, i8* %b, align 1, !dbg !5031
  br label %if.end67, !dbg !5032

if.end67:                                         ; preds = %if.end66, %if.end53
  br label %for.inc, !dbg !5033

for.inc:                                          ; preds = %if.end67
  %51 = load %struct.file*, %struct.file** %file, align 8, !dbg !5034
  %next = getelementptr inbounds %struct.file, %struct.file* %51, i32 0, i32 1, !dbg !5036
  %52 = load %struct.file*, %struct.file** %next, align 8, !dbg !5036
  store %struct.file* %52, %struct.file** %file, align 8, !dbg !5037
  br label %for.cond, !dbg !5038

for.end:                                          ; preds = %for.cond
  %53 = load i8, i8* %mask, align 1, !dbg !5039
  %conv68 = zext i8 %53 to i32, !dbg !5039
  %cmp69 = icmp ne i32 %conv68, 128, !dbg !5041
  br i1 %cmp69, label %if.then71, label %if.end78, !dbg !5042

if.then71:                                        ; preds = %for.end
  %54 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5043
  %call72 = call i64 @compress_out(%struct.archive_write* %54, i8* %b, i64 1, i32 1), !dbg !5045
  %conv73 = trunc i64 %call72 to i32, !dbg !5046
  store i32 %conv73, i32* %r, align 4, !dbg !5047
  %55 = load i32, i32* %r, align 4, !dbg !5048
  %cmp74 = icmp slt i32 %55, 0, !dbg !5050
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !5051

if.then76:                                        ; preds = %if.then71
  %56 = load i32, i32* %r, align 4, !dbg !5052
  store i32 %56, i32* %retval, align 4, !dbg !5053
  br label %return, !dbg !5053

if.end77:                                         ; preds = %if.then71
  br label %if.end78, !dbg !5054

if.end78:                                         ; preds = %if.end77, %for.end
  br label %if.end79

if.end79:                                         ; preds = %if.end78, %if.end14
  %57 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5055
  %call80 = call i32 @enc_uint64(%struct.archive_write* %57, i64 0), !dbg !5056
  store i32 %call80, i32* %r, align 4, !dbg !5057
  %58 = load i32, i32* %r, align 4, !dbg !5058
  %cmp81 = icmp slt i32 %58, 0, !dbg !5060
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !5061

if.then83:                                        ; preds = %if.end79
  %59 = load i32, i32* %r, align 4, !dbg !5062
  store i32 %59, i32* %retval, align 4, !dbg !5063
  br label %return, !dbg !5063

if.end84:                                         ; preds = %if.end79
  %60 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !5064
  %file_list85 = getelementptr inbounds %struct._7zip, %struct._7zip* %60, i32 0, i32 23, !dbg !5065
  %first86 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list85, i32 0, i32 0, !dbg !5066
  %61 = load %struct.file*, %struct.file** %first86, align 8, !dbg !5066
  store %struct.file* %61, %struct.file** %file, align 8, !dbg !5067
  br label %for.cond87, !dbg !5068

for.cond87:                                       ; preds = %for.inc110, %if.end84
  %62 = load %struct.file*, %struct.file** %file, align 8, !dbg !5069
  %cmp88 = icmp ne %struct.file* %62, null, !dbg !5073
  br i1 %cmp88, label %for.body90, label %for.end112, !dbg !5074

for.body90:                                       ; preds = %for.cond87
  %63 = load %struct.file*, %struct.file** %file, align 8, !dbg !5075
  %flg91 = getelementptr inbounds %struct.file, %struct.file* %63, i32 0, i32 5, !dbg !5078
  %64 = load i32, i32* %flg91, align 8, !dbg !5078
  %65 = load i32, i32* %flg.addr, align 4, !dbg !5079
  %and92 = and i32 %64, %65, !dbg !5080
  %cmp93 = icmp eq i32 %and92, 0, !dbg !5081
  br i1 %cmp93, label %if.then95, label %if.end96, !dbg !5082

if.then95:                                        ; preds = %for.body90
  br label %for.inc110, !dbg !5083

if.end96:                                         ; preds = %for.body90
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %filetime, i32 0, i32 0, !dbg !5084
  %66 = load i32, i32* %ti.addr, align 4, !dbg !5085
  %idxprom97 = sext i32 %66 to i64, !dbg !5086
  %67 = load %struct.file*, %struct.file** %file, align 8, !dbg !5086
  %times = getelementptr inbounds %struct.file, %struct.file* %67, i32 0, i32 6, !dbg !5087
  %arrayidx98 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times, i64 0, i64 %idxprom97, !dbg !5086
  %time = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx98, i32 0, i32 0, !dbg !5088
  %68 = load i64, i64* %time, align 8, !dbg !5088
  %69 = load i32, i32* %ti.addr, align 4, !dbg !5089
  %idxprom99 = sext i32 %69 to i64, !dbg !5090
  %70 = load %struct.file*, %struct.file** %file, align 8, !dbg !5090
  %times100 = getelementptr inbounds %struct.file, %struct.file* %70, i32 0, i32 6, !dbg !5091
  %arrayidx101 = getelementptr inbounds [3 x %struct.anon], [3 x %struct.anon]* %times100, i64 0, i64 %idxprom99, !dbg !5090
  %time_ns = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx101, i32 0, i32 1, !dbg !5092
  %71 = load i64, i64* %time_ns, align 8, !dbg !5092
  %call102 = call i64 @utcToFiletime(i64 %68, i64 %71), !dbg !5093
  call void @archive_le64enc(i8* %arraydecay, i64 %call102), !dbg !5094
  %72 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5096
  %arraydecay103 = getelementptr inbounds [8 x i8], [8 x i8]* %filetime, i32 0, i32 0, !dbg !5097
  %call104 = call i64 @compress_out(%struct.archive_write* %72, i8* %arraydecay103, i64 8, i32 1), !dbg !5098
  %conv105 = trunc i64 %call104 to i32, !dbg !5099
  store i32 %conv105, i32* %r, align 4, !dbg !5100
  %73 = load i32, i32* %r, align 4, !dbg !5101
  %cmp106 = icmp slt i32 %73, 0, !dbg !5103
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !5104

if.then108:                                       ; preds = %if.end96
  %74 = load i32, i32* %r, align 4, !dbg !5105
  store i32 %74, i32* %retval, align 4, !dbg !5106
  br label %return, !dbg !5106

if.end109:                                        ; preds = %if.end96
  br label %for.inc110, !dbg !5107

for.inc110:                                       ; preds = %if.end109, %if.then95
  %75 = load %struct.file*, %struct.file** %file, align 8, !dbg !5108
  %next111 = getelementptr inbounds %struct.file, %struct.file* %75, i32 0, i32 1, !dbg !5110
  %76 = load %struct.file*, %struct.file** %next111, align 8, !dbg !5110
  store %struct.file* %76, %struct.file** %file, align 8, !dbg !5111
  br label %for.cond87, !dbg !5112

for.end112:                                       ; preds = %for.cond87
  store i32 0, i32* %retval, align 4, !dbg !5113
  br label %return, !dbg !5113

return:                                           ; preds = %for.end112, %if.then108, %if.then83, %if.then76, %if.then65, %if.then44, %if.then39, %if.then26, %if.then20, %if.then13, %if.then8, %if.then3
  %77 = load i32, i32* %retval, align 4, !dbg !5114
  ret i32 %77, !dbg !5114
}

; Function Attrs: nounwind uwtable
define internal i64 @utcToFiletime(i64 %t, i64 %ns) #0 !dbg !649 {
entry:
  %t.addr = alloca i64, align 8
  %ns.addr = alloca i64, align 8
  %fileTime = alloca i64, align 8
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !5115, metadata !693), !dbg !5116
  store i64 %ns, i64* %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ns.addr, metadata !5117, metadata !693), !dbg !5118
  call void @llvm.dbg.declare(metadata i64* %fileTime, metadata !5119, metadata !693), !dbg !5120
  %0 = load i64, i64* %t.addr, align 8, !dbg !5121
  store i64 %0, i64* %fileTime, align 8, !dbg !5122
  %1 = load i64, i64* %fileTime, align 8, !dbg !5123
  %mul = mul i64 %1, 10000000, !dbg !5123
  store i64 %mul, i64* %fileTime, align 8, !dbg !5123
  %2 = load i64, i64* %ns.addr, align 8, !dbg !5124
  %div = sdiv i64 %2, 100, !dbg !5125
  %3 = load i64, i64* %fileTime, align 8, !dbg !5126
  %add = add i64 %3, %div, !dbg !5126
  store i64 %add, i64* %fileTime, align 8, !dbg !5126
  %4 = load i64, i64* %fileTime, align 8, !dbg !5127
  %add1 = add i64 %4, 116444736000000000, !dbg !5127
  store i64 %add1, i64* %fileTime, align 8, !dbg !5127
  %5 = load i64, i64* %fileTime, align 8, !dbg !5128
  ret i64 %5, !dbg !5129
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_be64enc(i8* %pp, i64 %u) #7 !dbg !658 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !5130, metadata !693), !dbg !5131
  store i64 %u, i64* %u.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %u.addr, metadata !5132, metadata !693), !dbg !5133
  call void @llvm.dbg.declare(metadata i8** %p, metadata !5134, metadata !693), !dbg !5135
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !5136
  store i8* %0, i8** %p, align 8, !dbg !5135
  %1 = load i8*, i8** %p, align 8, !dbg !5137
  %2 = load i64, i64* %u.addr, align 8, !dbg !5138
  %shr = lshr i64 %2, 32, !dbg !5139
  %conv = trunc i64 %shr to i32, !dbg !5140
  call void @archive_be32enc(i8* %1, i32 %conv), !dbg !5141
  %3 = load i8*, i8** %p, align 8, !dbg !5142
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !5143
  %4 = load i64, i64* %u.addr, align 8, !dbg !5144
  %and = and i64 %4, 4294967295, !dbg !5145
  %conv1 = trunc i64 %and to i32, !dbg !5146
  call void @archive_be32enc(i8* %add.ptr, i32 %conv1), !dbg !5147
  ret void, !dbg !5148
}

; Function Attrs: nounwind uwtable
define internal i32 @make_substreamsInfo(%struct.archive_write* %a, %struct.coder* %coders) #0 !dbg !662 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %coders.addr = alloca %struct.coder*, align 8
  %zip = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %r = alloca i32, align 4
  %crc = alloca [4 x i8], align 1
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !5149, metadata !693), !dbg !5150
  store %struct.coder* %coders, %struct.coder** %coders.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.coder** %coders.addr, metadata !5151, metadata !693), !dbg !5152
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip, metadata !5153, metadata !693), !dbg !5154
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5155
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !5156
  %1 = load i8*, i8** %format_data, align 8, !dbg !5156
  %2 = bitcast i8* %1 to %struct._7zip*, !dbg !5157
  store %struct._7zip* %2, %struct._7zip** %zip, align 8, !dbg !5154
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !5158, metadata !693), !dbg !5159
  call void @llvm.dbg.declare(metadata i32* %r, metadata !5160, metadata !693), !dbg !5161
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5162
  %call = call i32 @enc_uint64(%struct.archive_write* %3, i64 8), !dbg !5163
  store i32 %call, i32* %r, align 4, !dbg !5164
  %4 = load i32, i32* %r, align 4, !dbg !5165
  %cmp = icmp slt i32 %4, 0, !dbg !5167
  br i1 %cmp, label %if.then, label %if.end, !dbg !5168

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %r, align 4, !dbg !5169
  store i32 %5, i32* %retval, align 4, !dbg !5170
  br label %return, !dbg !5170

if.end:                                           ; preds = %entry
  %6 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !5171
  %total_number_nonempty_entry = getelementptr inbounds %struct._7zip, %struct._7zip* %6, i32 0, i32 4, !dbg !5173
  %7 = load i64, i64* %total_number_nonempty_entry, align 8, !dbg !5173
  %cmp1 = icmp ugt i64 %7, 1, !dbg !5174
  br i1 %cmp1, label %land.lhs.true, label %if.end29, !dbg !5175

land.lhs.true:                                    ; preds = %if.end
  %8 = load %struct.coder*, %struct.coder** %coders.addr, align 8, !dbg !5176
  %codec = getelementptr inbounds %struct.coder, %struct.coder* %8, i32 0, i32 0, !dbg !5178
  %9 = load i32, i32* %codec, align 8, !dbg !5178
  %cmp2 = icmp ne i32 %9, 0, !dbg !5179
  br i1 %cmp2, label %if.then3, label %if.end29, !dbg !5180

if.then3:                                         ; preds = %land.lhs.true
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5181
  %call4 = call i32 @enc_uint64(%struct.archive_write* %10, i64 13), !dbg !5183
  store i32 %call4, i32* %r, align 4, !dbg !5184
  %11 = load i32, i32* %r, align 4, !dbg !5185
  %cmp5 = icmp slt i32 %11, 0, !dbg !5187
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !5188

if.then6:                                         ; preds = %if.then3
  %12 = load i32, i32* %r, align 4, !dbg !5189
  store i32 %12, i32* %retval, align 4, !dbg !5190
  br label %return, !dbg !5190

if.end7:                                          ; preds = %if.then3
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5191
  %14 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !5192
  %total_number_nonempty_entry8 = getelementptr inbounds %struct._7zip, %struct._7zip* %14, i32 0, i32 4, !dbg !5193
  %15 = load i64, i64* %total_number_nonempty_entry8, align 8, !dbg !5193
  %call9 = call i32 @enc_uint64(%struct.archive_write* %13, i64 %15), !dbg !5194
  store i32 %call9, i32* %r, align 4, !dbg !5195
  %16 = load i32, i32* %r, align 4, !dbg !5196
  %cmp10 = icmp slt i32 %16, 0, !dbg !5198
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !5199

if.then11:                                        ; preds = %if.end7
  %17 = load i32, i32* %r, align 4, !dbg !5200
  store i32 %17, i32* %retval, align 4, !dbg !5201
  br label %return, !dbg !5201

if.end12:                                         ; preds = %if.end7
  %18 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5202
  %call13 = call i32 @enc_uint64(%struct.archive_write* %18, i64 9), !dbg !5203
  store i32 %call13, i32* %r, align 4, !dbg !5204
  %19 = load i32, i32* %r, align 4, !dbg !5205
  %cmp14 = icmp slt i32 %19, 0, !dbg !5207
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !5208

if.then15:                                        ; preds = %if.end12
  %20 = load i32, i32* %r, align 4, !dbg !5209
  store i32 %20, i32* %retval, align 4, !dbg !5210
  br label %return, !dbg !5210

if.end16:                                         ; preds = %if.end12
  %21 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !5211
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %21, i32 0, i32 23, !dbg !5212
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !5213
  %22 = load %struct.file*, %struct.file** %first, align 8, !dbg !5213
  store %struct.file* %22, %struct.file** %file, align 8, !dbg !5214
  br label %for.cond, !dbg !5215

for.cond:                                         ; preds = %for.inc, %if.end16
  %23 = load %struct.file*, %struct.file** %file, align 8, !dbg !5216
  %cmp17 = icmp ne %struct.file* %23, null, !dbg !5220
  br i1 %cmp17, label %for.body, label %for.end, !dbg !5221

for.body:                                         ; preds = %for.cond
  %24 = load %struct.file*, %struct.file** %file, align 8, !dbg !5222
  %next = getelementptr inbounds %struct.file, %struct.file* %24, i32 0, i32 1, !dbg !5225
  %25 = load %struct.file*, %struct.file** %next, align 8, !dbg !5225
  %cmp18 = icmp eq %struct.file* %25, null, !dbg !5226
  br i1 %cmp18, label %if.then21, label %lor.lhs.false, !dbg !5227

lor.lhs.false:                                    ; preds = %for.body
  %26 = load %struct.file*, %struct.file** %file, align 8, !dbg !5228
  %next19 = getelementptr inbounds %struct.file, %struct.file* %26, i32 0, i32 1, !dbg !5229
  %27 = load %struct.file*, %struct.file** %next19, align 8, !dbg !5229
  %size = getelementptr inbounds %struct.file, %struct.file* %27, i32 0, i32 4, !dbg !5230
  %28 = load i64, i64* %size, align 8, !dbg !5230
  %cmp20 = icmp eq i64 %28, 0, !dbg !5231
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !5232

if.then21:                                        ; preds = %lor.lhs.false, %for.body
  br label %for.end, !dbg !5234

if.end22:                                         ; preds = %lor.lhs.false
  %29 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5235
  %30 = load %struct.file*, %struct.file** %file, align 8, !dbg !5236
  %size23 = getelementptr inbounds %struct.file, %struct.file* %30, i32 0, i32 4, !dbg !5237
  %31 = load i64, i64* %size23, align 8, !dbg !5237
  %call24 = call i32 @enc_uint64(%struct.archive_write* %29, i64 %31), !dbg !5238
  store i32 %call24, i32* %r, align 4, !dbg !5239
  %32 = load i32, i32* %r, align 4, !dbg !5240
  %cmp25 = icmp slt i32 %32, 0, !dbg !5242
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !5243

if.then26:                                        ; preds = %if.end22
  %33 = load i32, i32* %r, align 4, !dbg !5244
  store i32 %33, i32* %retval, align 4, !dbg !5245
  br label %return, !dbg !5245

if.end27:                                         ; preds = %if.end22
  br label %for.inc, !dbg !5246

for.inc:                                          ; preds = %if.end27
  %34 = load %struct.file*, %struct.file** %file, align 8, !dbg !5247
  %next28 = getelementptr inbounds %struct.file, %struct.file* %34, i32 0, i32 1, !dbg !5249
  %35 = load %struct.file*, %struct.file** %next28, align 8, !dbg !5249
  store %struct.file* %35, %struct.file** %file, align 8, !dbg !5250
  br label %for.cond, !dbg !5251

for.end:                                          ; preds = %if.then21, %for.cond
  br label %if.end29, !dbg !5252

if.end29:                                         ; preds = %for.end, %land.lhs.true, %if.end
  %36 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5253
  %call30 = call i32 @enc_uint64(%struct.archive_write* %36, i64 10), !dbg !5254
  store i32 %call30, i32* %r, align 4, !dbg !5255
  %37 = load i32, i32* %r, align 4, !dbg !5256
  %cmp31 = icmp slt i32 %37, 0, !dbg !5258
  br i1 %cmp31, label %if.then32, label %if.end33, !dbg !5259

if.then32:                                        ; preds = %if.end29
  %38 = load i32, i32* %r, align 4, !dbg !5260
  store i32 %38, i32* %retval, align 4, !dbg !5261
  br label %return, !dbg !5261

if.end33:                                         ; preds = %if.end29
  %39 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5262
  %call34 = call i32 @enc_uint64(%struct.archive_write* %39, i64 1), !dbg !5263
  store i32 %call34, i32* %r, align 4, !dbg !5264
  %40 = load i32, i32* %r, align 4, !dbg !5265
  %cmp35 = icmp slt i32 %40, 0, !dbg !5267
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !5268

if.then36:                                        ; preds = %if.end33
  %41 = load i32, i32* %r, align 4, !dbg !5269
  store i32 %41, i32* %retval, align 4, !dbg !5270
  br label %return, !dbg !5270

if.end37:                                         ; preds = %if.end33
  %42 = load %struct._7zip*, %struct._7zip** %zip, align 8, !dbg !5271
  %file_list38 = getelementptr inbounds %struct._7zip, %struct._7zip* %42, i32 0, i32 23, !dbg !5272
  %first39 = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list38, i32 0, i32 0, !dbg !5273
  %43 = load %struct.file*, %struct.file** %first39, align 8, !dbg !5273
  store %struct.file* %43, %struct.file** %file, align 8, !dbg !5274
  br label %for.cond40, !dbg !5275

for.cond40:                                       ; preds = %for.inc53, %if.end37
  %44 = load %struct.file*, %struct.file** %file, align 8, !dbg !5276
  %cmp41 = icmp ne %struct.file* %44, null, !dbg !5280
  br i1 %cmp41, label %for.body42, label %for.end55, !dbg !5281

for.body42:                                       ; preds = %for.cond40
  call void @llvm.dbg.declare(metadata [4 x i8]* %crc, metadata !5282, metadata !693), !dbg !5284
  %45 = load %struct.file*, %struct.file** %file, align 8, !dbg !5285
  %size43 = getelementptr inbounds %struct.file, %struct.file* %45, i32 0, i32 4, !dbg !5287
  %46 = load i64, i64* %size43, align 8, !dbg !5287
  %cmp44 = icmp eq i64 %46, 0, !dbg !5288
  br i1 %cmp44, label %if.then45, label %if.end46, !dbg !5289

if.then45:                                        ; preds = %for.body42
  br label %for.end55, !dbg !5290

if.end46:                                         ; preds = %for.body42
  %arraydecay = getelementptr inbounds [4 x i8], [4 x i8]* %crc, i32 0, i32 0, !dbg !5291
  %47 = load %struct.file*, %struct.file** %file, align 8, !dbg !5292
  %cm_zlib_crc32 = getelementptr inbounds %struct.file, %struct.file* %47, i32 0, i32 8, !dbg !5293
  %48 = load i32, i32* %cm_zlib_crc32, align 4, !dbg !5293
  call void @archive_le32enc(i8* %arraydecay, i32 %48), !dbg !5294
  %49 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5295
  %arraydecay47 = getelementptr inbounds [4 x i8], [4 x i8]* %crc, i32 0, i32 0, !dbg !5296
  %call48 = call i64 @compress_out(%struct.archive_write* %49, i8* %arraydecay47, i64 4, i32 1), !dbg !5297
  %conv = trunc i64 %call48 to i32, !dbg !5298
  store i32 %conv, i32* %r, align 4, !dbg !5299
  %50 = load i32, i32* %r, align 4, !dbg !5300
  %cmp49 = icmp slt i32 %50, 0, !dbg !5302
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !5303

if.then51:                                        ; preds = %if.end46
  %51 = load i32, i32* %r, align 4, !dbg !5304
  store i32 %51, i32* %retval, align 4, !dbg !5305
  br label %return, !dbg !5305

if.end52:                                         ; preds = %if.end46
  br label %for.inc53, !dbg !5306

for.inc53:                                        ; preds = %if.end52
  %52 = load %struct.file*, %struct.file** %file, align 8, !dbg !5307
  %next54 = getelementptr inbounds %struct.file, %struct.file* %52, i32 0, i32 1, !dbg !5309
  %53 = load %struct.file*, %struct.file** %next54, align 8, !dbg !5309
  store %struct.file* %53, %struct.file** %file, align 8, !dbg !5310
  br label %for.cond40, !dbg !5311

for.end55:                                        ; preds = %if.then45, %for.cond40
  %54 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !5312
  %call56 = call i32 @enc_uint64(%struct.archive_write* %54, i64 0), !dbg !5313
  store i32 %call56, i32* %r, align 4, !dbg !5314
  %55 = load i32, i32* %r, align 4, !dbg !5315
  %cmp57 = icmp slt i32 %55, 0, !dbg !5317
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !5318

if.then59:                                        ; preds = %for.end55
  %56 = load i32, i32* %r, align 4, !dbg !5319
  store i32 %56, i32* %retval, align 4, !dbg !5320
  br label %return, !dbg !5320

if.end60:                                         ; preds = %for.end55
  store i32 0, i32* %retval, align 4, !dbg !5321
  br label %return, !dbg !5321

return:                                           ; preds = %if.end60, %if.then59, %if.then51, %if.then36, %if.then32, %if.then26, %if.then15, %if.then11, %if.then6, %if.then
  %57 = load i32, i32* %retval, align 4, !dbg !5322
  ret i32 %57, !dbg !5322
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_be32enc(i8* %pp, i32 %u) #7 !dbg !661 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !5323, metadata !693), !dbg !5324
  store i32 %u, i32* %u.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %u.addr, metadata !5325, metadata !693), !dbg !5326
  call void @llvm.dbg.declare(metadata i8** %p, metadata !5327, metadata !693), !dbg !5328
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !5329
  store i8* %0, i8** %p, align 8, !dbg !5328
  %1 = load i32, i32* %u.addr, align 4, !dbg !5330
  %shr = lshr i32 %1, 24, !dbg !5331
  %and = and i32 %shr, 255, !dbg !5332
  %conv = trunc i32 %and to i8, !dbg !5333
  %2 = load i8*, i8** %p, align 8, !dbg !5334
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !5334
  store i8 %conv, i8* %arrayidx, align 1, !dbg !5335
  %3 = load i32, i32* %u.addr, align 4, !dbg !5336
  %shr1 = lshr i32 %3, 16, !dbg !5337
  %and2 = and i32 %shr1, 255, !dbg !5338
  %conv3 = trunc i32 %and2 to i8, !dbg !5339
  %4 = load i8*, i8** %p, align 8, !dbg !5340
  %arrayidx4 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !5340
  store i8 %conv3, i8* %arrayidx4, align 1, !dbg !5341
  %5 = load i32, i32* %u.addr, align 4, !dbg !5342
  %shr5 = lshr i32 %5, 8, !dbg !5343
  %and6 = and i32 %shr5, 255, !dbg !5344
  %conv7 = trunc i32 %and6 to i8, !dbg !5345
  %6 = load i8*, i8** %p, align 8, !dbg !5346
  %arrayidx8 = getelementptr inbounds i8, i8* %6, i64 2, !dbg !5346
  store i8 %conv7, i8* %arrayidx8, align 1, !dbg !5347
  %7 = load i32, i32* %u.addr, align 4, !dbg !5348
  %and9 = and i32 %7, 255, !dbg !5349
  %conv10 = trunc i32 %and9 to i8, !dbg !5348
  %8 = load i8*, i8** %p, align 8, !dbg !5350
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 3, !dbg !5350
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !5351
  ret void, !dbg !5352
}

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

declare i64 @read(i32, i8*, i64) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare i32 @close(i32) #2

; Function Attrs: nounwind uwtable
define internal void @file_free_register(%struct._7zip* %zip) #0 !dbg !671 {
entry:
  %zip.addr = alloca %struct._7zip*, align 8
  %file = alloca %struct.file*, align 8
  %file_next = alloca %struct.file*, align 8
  store %struct._7zip* %zip, %struct._7zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._7zip** %zip.addr, metadata !5353, metadata !693), !dbg !5354
  call void @llvm.dbg.declare(metadata %struct.file** %file, metadata !5355, metadata !693), !dbg !5356
  call void @llvm.dbg.declare(metadata %struct.file** %file_next, metadata !5357, metadata !693), !dbg !5358
  %0 = load %struct._7zip*, %struct._7zip** %zip.addr, align 8, !dbg !5359
  %file_list = getelementptr inbounds %struct._7zip, %struct._7zip* %0, i32 0, i32 23, !dbg !5360
  %first = getelementptr inbounds %struct.anon.0, %struct.anon.0* %file_list, i32 0, i32 0, !dbg !5361
  %1 = load %struct.file*, %struct.file** %first, align 8, !dbg !5361
  store %struct.file* %1, %struct.file** %file, align 8, !dbg !5362
  br label %while.cond, !dbg !5363

while.cond:                                       ; preds = %while.body, %entry
  %2 = load %struct.file*, %struct.file** %file, align 8, !dbg !5364
  %cmp = icmp ne %struct.file* %2, null, !dbg !5366
  br i1 %cmp, label %while.body, label %while.end, !dbg !5367

while.body:                                       ; preds = %while.cond
  %3 = load %struct.file*, %struct.file** %file, align 8, !dbg !5368
  %next = getelementptr inbounds %struct.file, %struct.file* %3, i32 0, i32 1, !dbg !5370
  %4 = load %struct.file*, %struct.file** %next, align 8, !dbg !5370
  store %struct.file* %4, %struct.file** %file_next, align 8, !dbg !5371
  %5 = load %struct.file*, %struct.file** %file, align 8, !dbg !5372
  call void @file_free(%struct.file* %5), !dbg !5373
  %6 = load %struct.file*, %struct.file** %file_next, align 8, !dbg !5374
  store %struct.file* %6, %struct.file** %file, align 8, !dbg !5375
  br label %while.cond, !dbg !5376

while.end:                                        ; preds = %while.cond
  ret void, !dbg !5378
}

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!689, !690}
!llvm.ident = !{!691}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !43, subprograms: !579, globals: !678)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_7zip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !7, !11, !16, !23, !37}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "la_zaction", file: !1, line: 93, size: 32, align: 32, elements: !4)
!4 = !{!5, !6}
!5 = !DIEnumerator(name: "ARCHIVE_Z_FINISH", value: 0)
!6 = !DIEnumerator(name: "ARCHIVE_Z_RUN", value: 1)
!7 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !8, line: 44, size: 32, align: 32, elements: !9)
!8 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !{!10}
!10 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!11 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !12, line: 138, size: 32, align: 32, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !15}
!14 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!15 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!16 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !12, line: 58, size: 32, align: 32, elements: !17)
!17 = !{!18, !19, !20, !21, !22}
!18 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!19 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!20 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!21 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!22 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!23 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !8, line: 57, size: 32, align: 32, elements: !24)
!24 = !{!25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36}
!25 = !DIEnumerator(name: "LZMA_OK", value: 0)
!26 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!27 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!28 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!29 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!30 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!31 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!32 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!33 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!34 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!35 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!36 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!37 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !8, line: 250, size: 32, align: 32, elements: !38)
!38 = !{!39, !40, !41, !42}
!39 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!40 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!41 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!42 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!43 = !{!44, !164, !232, !248, !272, !83, !85, !63, !53, !359, !252, !363, !364, !365, !135, !275, !397, !155, !237, !420, !421, !430, !466, !467, !477, !239, !257, !576, !577, !120}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !46, line: 72, size: 2816, align: 64, elements: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !{!48, !151, !152, !153, !154, !158, !159, !165, !171, !174, !175, !176, !177, !203, !204, !205, !206, !210, !214, !215, !219, !223, !224, !225, !226, !231}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !45, file: !46, line: 73, baseType: !49, size: 1280, align: 64)
!49 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !50, line: 89, size: 1280, align: 64, elements: !51)
!50 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!51 = !{!52, !54, !55, !123, !124, !125, !126, !127, !128, !129, !130, !138, !139, !140, !141, !145, !146, !147, !148, !149, !150}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !49, file: !50, line: 96, baseType: !53, size: 32, align: 32)
!53 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !49, file: !50, line: 97, baseType: !53, size: 32, align: 32, offset: 32)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !49, file: !50, line: 103, baseType: !56, size: 64, align: 64, offset: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !50, line: 63, size: 832, align: 64, elements: !58)
!58 = !{!59, !65, !66, !73, !74, !88, !94, !99, !100, !107, !108, !112, !116}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !57, file: !50, line: 64, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!63, !64}
!63 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !57, file: !50, line: 65, baseType: !60, size: 64, align: 64, offset: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !57, file: !50, line: 66, baseType: !67, size: 64, align: 64, offset: 128)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!63, !64, !70}
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !72, line: 180, flags: DIFlagFwdDecl)
!72 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !57, file: !50, line: 68, baseType: !60, size: 64, align: 64, offset: 192)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !57, file: !50, line: 69, baseType: !75, size: 64, align: 64, offset: 256)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DISubroutineType(types: !77)
!77 = !{!78, !64, !83, !85}
!78 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !79, line: 109, baseType: !80)
!79 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!80 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !81, line: 172, baseType: !82)
!81 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!82 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!83 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !86, line: 62, baseType: !87)
!86 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!87 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !57, file: !50, line: 71, baseType: !89, size: 64, align: 64, offset: 320)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!78, !64, !83, !85, !92}
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !93, line: 40, baseType: !82)
!93 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !57, file: !50, line: 74, baseType: !95, size: 64, align: 64, offset: 384)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DISubroutineType(types: !97)
!97 = !{!63, !64, !98}
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !57, file: !50, line: 76, baseType: !67, size: 64, align: 64, offset: 448)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !57, file: !50, line: 78, baseType: !101, size: 64, align: 64, offset: 512)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!63, !64, !104, !105, !106}
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !57, file: !50, line: 81, baseType: !60, size: 64, align: 64, offset: 576)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !57, file: !50, line: 82, baseType: !109, size: 64, align: 64, offset: 640)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DISubroutineType(types: !111)
!111 = !{!92, !64, !63}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !57, file: !50, line: 83, baseType: !113, size: 64, align: 64, offset: 704)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DISubroutineType(types: !115)
!115 = !{!63, !64, !63}
!116 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !57, file: !50, line: 84, baseType: !117, size: 64, align: 64, offset: 768)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!118 = !DISubroutineType(types: !119)
!119 = !{!120, !64, !63}
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !122)
!122 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !49, file: !50, line: 105, baseType: !63, size: 32, align: 32, offset: 128)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !49, file: !50, line: 106, baseType: !120, size: 64, align: 64, offset: 192)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !49, file: !50, line: 108, baseType: !63, size: 32, align: 32, offset: 256)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !49, file: !50, line: 109, baseType: !120, size: 64, align: 64, offset: 320)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !49, file: !50, line: 112, baseType: !63, size: 32, align: 32, offset: 384)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !49, file: !50, line: 114, baseType: !63, size: 32, align: 32, offset: 416)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !49, file: !50, line: 115, baseType: !120, size: 64, align: 64, offset: 448)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !49, file: !50, line: 116, baseType: !131, size: 192, align: 64, offset: 512)
!131 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !132, line: 58, size: 192, align: 64, elements: !133)
!132 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!133 = !{!134, !136, !137}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !131, file: !132, line: 59, baseType: !135, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !131, file: !132, line: 60, baseType: !85, size: 64, align: 64, offset: 64)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !131, file: !132, line: 61, baseType: !85, size: 64, align: 64, offset: 128)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !49, file: !50, line: 118, baseType: !135, size: 64, align: 64, offset: 704)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !49, file: !50, line: 119, baseType: !53, size: 32, align: 32, offset: 768)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !49, file: !50, line: 120, baseType: !53, size: 32, align: 32, offset: 800)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !49, file: !50, line: 121, baseType: !142, size: 64, align: 64, offset: 832)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !144, line: 36, flags: DIFlagFwdDecl)
!144 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!145 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !49, file: !50, line: 127, baseType: !120, size: 64, align: 64, offset: 896)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !49, file: !50, line: 128, baseType: !92, size: 64, align: 64, offset: 960)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !49, file: !50, line: 129, baseType: !92, size: 64, align: 64, offset: 1024)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !49, file: !50, line: 130, baseType: !85, size: 64, align: 64, offset: 1088)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !49, file: !50, line: 137, baseType: !122, size: 8, align: 8, offset: 1152)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !49, file: !50, line: 138, baseType: !85, size: 64, align: 64, offset: 1216)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !45, file: !46, line: 76, baseType: !63, size: 32, align: 32, offset: 1280)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !45, file: !46, line: 77, baseType: !92, size: 64, align: 64, offset: 1344)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !45, file: !46, line: 78, baseType: !92, size: 64, align: 64, offset: 1408)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !45, file: !46, line: 81, baseType: !155, size: 64, align: 64, offset: 1472)
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !157)
!157 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !45, file: !46, line: 82, baseType: !85, size: 64, align: 64, offset: 1536)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !45, file: !46, line: 85, baseType: !160, size: 64, align: 64, offset: 1600)
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !72, line: 241, baseType: !162)
!162 = !DISubroutineType(types: !163)
!163 = !{!63, !64, !164}
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !45, file: !46, line: 86, baseType: !166, size: 64, align: 64, offset: 1664)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !72, line: 237, baseType: !168)
!168 = !DISubroutineType(types: !169)
!169 = !{!170, !64, !164, !83, !85}
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !72, line: 95, baseType: !78)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !45, file: !46, line: 87, baseType: !172, size: 64, align: 64, offset: 1728)
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !72, line: 243, baseType: !162)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !45, file: !46, line: 88, baseType: !164, size: 64, align: 64, offset: 1792)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !45, file: !46, line: 96, baseType: !63, size: 32, align: 32, offset: 1856)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !45, file: !46, line: 97, baseType: !63, size: 32, align: 32, offset: 1888)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !45, file: !46, line: 102, baseType: !178, size: 64, align: 64, offset: 1920)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !46, line: 43, size: 768, align: 64, elements: !180)
!180 = !{!181, !182, !183, !184, !188, !192, !196, !197, !198, !199, !200, !201, !202}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !179, file: !46, line: 44, baseType: !92, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !179, file: !46, line: 45, baseType: !64, size: 64, align: 64, offset: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !179, file: !46, line: 46, baseType: !178, size: 64, align: 64, offset: 128)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !179, file: !46, line: 47, baseType: !185, size: 64, align: 64, offset: 192)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DISubroutineType(types: !187)
!187 = !{!63, !178, !120, !120}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !179, file: !46, line: 49, baseType: !189, size: 64, align: 64, offset: 256)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DISubroutineType(types: !191)
!191 = !{!63, !178}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !179, file: !46, line: 50, baseType: !193, size: 64, align: 64, offset: 320)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!194 = !DISubroutineType(types: !195)
!195 = !{!63, !178, !83, !85}
!196 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !179, file: !46, line: 51, baseType: !189, size: 64, align: 64, offset: 384)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !179, file: !46, line: 52, baseType: !189, size: 64, align: 64, offset: 448)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !179, file: !46, line: 53, baseType: !164, size: 64, align: 64, offset: 512)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !179, file: !46, line: 54, baseType: !120, size: 64, align: 64, offset: 576)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !179, file: !46, line: 55, baseType: !63, size: 32, align: 32, offset: 640)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !179, file: !46, line: 56, baseType: !63, size: 32, align: 32, offset: 672)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !179, file: !46, line: 57, baseType: !63, size: 32, align: 32, offset: 704)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !45, file: !46, line: 103, baseType: !178, size: 64, align: 64, offset: 1984)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !45, file: !46, line: 109, baseType: !164, size: 64, align: 64, offset: 2048)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !45, file: !46, line: 110, baseType: !120, size: 64, align: 64, offset: 2112)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !45, file: !46, line: 111, baseType: !207, size: 64, align: 64, offset: 2176)
!207 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !208, size: 64, align: 64)
!208 = !DISubroutineType(types: !209)
!209 = !{!63, !44}
!210 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !45, file: !46, line: 112, baseType: !211, size: 64, align: 64, offset: 2240)
!211 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !212, size: 64, align: 64)
!212 = !DISubroutineType(types: !213)
!213 = !{!63, !44, !120, !120}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !45, file: !46, line: 114, baseType: !207, size: 64, align: 64, offset: 2304)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !45, file: !46, line: 115, baseType: !216, size: 64, align: 64, offset: 2368)
!216 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !217, size: 64, align: 64)
!217 = !DISubroutineType(types: !218)
!218 = !{!63, !44, !70}
!219 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !45, file: !46, line: 117, baseType: !220, size: 64, align: 64, offset: 2432)
!220 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !221, size: 64, align: 64)
!221 = !DISubroutineType(types: !222)
!222 = !{!78, !44, !83, !85}
!223 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !45, file: !46, line: 119, baseType: !207, size: 64, align: 64, offset: 2496)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !45, file: !46, line: 120, baseType: !207, size: 64, align: 64, offset: 2560)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !45, file: !46, line: 126, baseType: !135, size: 64, align: 64, offset: 2624)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !45, file: !46, line: 127, baseType: !227, size: 64, align: 64, offset: 2688)
!227 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !228, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !72, line: 256, baseType: !229)
!229 = !DISubroutineType(types: !230)
!230 = !{!120, !64, !164}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !45, file: !46, line: 128, baseType: !164, size: 64, align: 64, offset: 2752)
!232 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !233, size: 64, align: 64)
!233 = !DICompositeType(tag: DW_TAG_structure_type, name: "_7zip", file: !1, line: 170, size: 494080, align: 64, elements: !234)
!234 = !{!235, !236, !238, !277, !278, !279, !280, !281, !282, !284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !317, !323, !324, !328, !329, !335, !336}
!235 = !DIDerivedType(tag: DW_TAG_member, name: "temp_fd", scope: !233, file: !1, line: 171, baseType: !63, size: 32, align: 32)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "temp_offset", scope: !233, file: !1, line: 172, baseType: !237, size: 64, align: 64, offset: 64)
!237 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !93, line: 55, baseType: !87)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "cur_file", scope: !233, file: !1, line: 174, baseType: !239, size: 64, align: 64, offset: 128)
!239 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !240, size: 64, align: 64)
!240 = !DICompositeType(tag: DW_TAG_structure_type, name: "file", file: !1, line: 142, size: 1024, align: 64, elements: !241)
!241 = !{!242, !253, !254, !255, !258, !259, !260, !271, !274, !276}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "rbnode", scope: !240, file: !1, line: 143, baseType: !243, size: 192, align: 64)
!243 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_node", file: !244, line: 34, size: 192, align: 64, elements: !245)
!244 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!245 = !{!246, !251}
!246 = !DIDerivedType(tag: DW_TAG_member, name: "rb_nodes", scope: !243, file: !244, line: 35, baseType: !247, size: 128, align: 64)
!247 = !DICompositeType(tag: DW_TAG_array_type, baseType: !248, size: 128, align: 64, elements: !249)
!248 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !243, size: 64, align: 64)
!249 = !{!250}
!250 = !DISubrange(count: 2)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "rb_info", scope: !243, file: !244, line: 41, baseType: !252, size: 64, align: 64, offset: 128)
!252 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !93, line: 122, baseType: !87)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !240, file: !1, line: 145, baseType: !239, size: 64, align: 64, offset: 192)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "name_len", scope: !240, file: !1, line: 146, baseType: !53, size: 32, align: 32, offset: 256)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "utf16name", scope: !240, file: !1, line: 147, baseType: !256, size: 64, align: 64, offset: 320)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !93, line: 48, baseType: !157)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !240, file: !1, line: 148, baseType: !237, size: 64, align: 64, offset: 384)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "flg", scope: !240, file: !1, line: 149, baseType: !53, size: 32, align: 32, offset: 448)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "times", scope: !240, file: !1, line: 159, baseType: !261, size: 384, align: 64, offset: 512)
!261 = !DICompositeType(tag: DW_TAG_array_type, baseType: !262, size: 384, align: 64, elements: !269)
!262 = !DICompositeType(tag: DW_TAG_structure_type, scope: !240, file: !1, line: 156, size: 128, align: 64, elements: !263)
!263 = !{!264, !268}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !262, file: !1, line: 157, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !266, line: 75, baseType: !267)
!266 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!267 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !81, line: 139, baseType: !82)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "time_ns", scope: !262, file: !1, line: 158, baseType: !82, size: 64, align: 64, offset: 64)
!269 = !{!270}
!270 = !DISubrange(count: 3)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !240, file: !1, line: 164, baseType: !272, size: 32, align: 32, offset: 896)
!272 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !79, line: 70, baseType: !273)
!273 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !81, line: 129, baseType: !53)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "cm_zlib_crc32", scope: !240, file: !1, line: 165, baseType: !275, size: 32, align: 32, offset: 928)
!275 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !93, line: 51, baseType: !53)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "dir", scope: !240, file: !1, line: 167, baseType: !63, size: 1, align: 32, offset: 960)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "total_number_entry", scope: !233, file: !1, line: 175, baseType: !85, size: 64, align: 64, offset: 192)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "total_number_nonempty_entry", scope: !233, file: !1, line: 176, baseType: !85, size: 64, align: 64, offset: 256)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "total_number_empty_entry", scope: !233, file: !1, line: 177, baseType: !85, size: 64, align: 64, offset: 320)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "total_number_dir_entry", scope: !233, file: !1, line: 178, baseType: !85, size: 64, align: 64, offset: 384)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "total_bytes_entry_name", scope: !233, file: !1, line: 179, baseType: !85, size: 64, align: 64, offset: 448)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "total_number_time_defined", scope: !233, file: !1, line: 180, baseType: !283, size: 192, align: 64, offset: 512)
!283 = !DICompositeType(tag: DW_TAG_array_type, baseType: !85, size: 192, align: 64, elements: !269)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "total_bytes_compressed", scope: !233, file: !1, line: 181, baseType: !237, size: 64, align: 64, offset: 704)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "total_bytes_uncompressed", scope: !233, file: !1, line: 182, baseType: !237, size: 64, align: 64, offset: 768)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !233, file: !1, line: 183, baseType: !237, size: 64, align: 64, offset: 832)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "entry_crc32", scope: !233, file: !1, line: 184, baseType: !275, size: 32, align: 32, offset: 896)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "precode_crc32", scope: !233, file: !1, line: 185, baseType: !275, size: 32, align: 32, offset: 928)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "encoded_crc32", scope: !233, file: !1, line: 186, baseType: !275, size: 32, align: 32, offset: 960)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "crc32flg", scope: !233, file: !1, line: 187, baseType: !63, size: 32, align: 32, offset: 992)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "opt_compression", scope: !233, file: !1, line: 191, baseType: !53, size: 32, align: 32, offset: 1024)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "opt_compression_level", scope: !233, file: !1, line: 192, baseType: !63, size: 32, align: 32, offset: 1056)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !233, file: !1, line: 194, baseType: !294, size: 768, align: 64, offset: 1088)
!294 = !DICompositeType(tag: DW_TAG_structure_type, name: "la_zstream", file: !1, line: 101, size: 768, align: 64, elements: !295)
!295 = !{!296, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !313}
!296 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !294, file: !1, line: 102, baseType: !297, size: 64, align: 64)
!297 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !298, size: 64, align: 64)
!298 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !257)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !294, file: !1, line: 103, baseType: !85, size: 64, align: 64, offset: 64)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !294, file: !1, line: 104, baseType: !237, size: 64, align: 64, offset: 128)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !294, file: !1, line: 106, baseType: !256, size: 64, align: 64, offset: 192)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !294, file: !1, line: 107, baseType: !85, size: 64, align: 64, offset: 256)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !294, file: !1, line: 108, baseType: !237, size: 64, align: 64, offset: 320)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "prop_size", scope: !294, file: !1, line: 110, baseType: !275, size: 32, align: 32, offset: 384)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "props", scope: !294, file: !1, line: 111, baseType: !256, size: 64, align: 64, offset: 448)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "valid", scope: !294, file: !1, line: 113, baseType: !63, size: 32, align: 32, offset: 512)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "real_stream", scope: !294, file: !1, line: 114, baseType: !164, size: 64, align: 64, offset: 576)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !294, file: !1, line: 115, baseType: !309, size: 64, align: 64, offset: 640)
!309 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!310 = !DISubroutineType(types: !311)
!311 = !{!63, !64, !312, !3}
!312 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !294, size: 64, align: 64)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !294, file: !1, line: 118, baseType: !314, size: 64, align: 64, offset: 704)
!314 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!315 = !DISubroutineType(types: !316)
!316 = !{!63, !64, !312}
!317 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !233, file: !1, line: 195, baseType: !318, size: 192, align: 64, offset: 1856)
!318 = !DICompositeType(tag: DW_TAG_structure_type, name: "coder", file: !1, line: 136, size: 192, align: 64, elements: !319)
!319 = !{!320, !321, !322}
!320 = !DIDerivedType(tag: DW_TAG_member, name: "codec", scope: !318, file: !1, line: 137, baseType: !53, size: 32, align: 32)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "prop_size", scope: !318, file: !1, line: 138, baseType: !85, size: 64, align: 64, offset: 64)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "props", scope: !318, file: !1, line: 139, baseType: !256, size: 64, align: 64, offset: 128)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !233, file: !1, line: 197, baseType: !142, size: 64, align: 64, offset: 2048)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "wbuff", scope: !233, file: !1, line: 202, baseType: !325, size: 491520, align: 8, offset: 2112)
!325 = !DICompositeType(tag: DW_TAG_array_type, baseType: !157, size: 491520, align: 8, elements: !326)
!326 = !{!327}
!327 = !DISubrange(count: 61440)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "wbuff_remaining", scope: !233, file: !1, line: 203, baseType: !85, size: 64, align: 64, offset: 493632)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "file_list", scope: !233, file: !1, line: 213, baseType: !330, size: 128, align: 64, offset: 493696)
!330 = !DICompositeType(tag: DW_TAG_structure_type, scope: !233, file: !1, line: 210, size: 128, align: 64, elements: !331)
!331 = !{!332, !333}
!332 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !330, file: !1, line: 211, baseType: !239, size: 64, align: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !330, file: !1, line: 212, baseType: !334, size: 64, align: 64, offset: 64)
!334 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "empty_list", scope: !233, file: !1, line: 213, baseType: !330, size: 128, align: 64, offset: 493824)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "rbtree", scope: !233, file: !1, line: 214, baseType: !337, size: 128, align: 64, offset: 493952)
!337 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree", file: !244, line: 80, size: 128, align: 64, elements: !338)
!338 = !{!339, !340}
!339 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_root", scope: !337, file: !244, line: 81, baseType: !248, size: 64, align: 64)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_ops", scope: !337, file: !244, line: 82, baseType: !341, size: 64, align: 64, offset: 64)
!341 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !342, size: 64, align: 64)
!342 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !343)
!343 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree_ops", file: !244, line: 75, size: 128, align: 64, elements: !344)
!344 = !{!345, !353}
!345 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_nodes", scope: !343, file: !244, line: 76, baseType: !346, size: 64, align: 64)
!346 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_nodes_fn", file: !244, line: 70, baseType: !347)
!347 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !348)
!348 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !349, size: 64, align: 64)
!349 = !DISubroutineType(types: !350)
!350 = !{!63, !351, !351}
!351 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !352, size: 64, align: 64)
!352 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !243)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_key", scope: !343, file: !244, line: 77, baseType: !354, size: 64, align: 64, offset: 64)
!354 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_key_fn", file: !244, line: 72, baseType: !355)
!355 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !356)
!356 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !357, size: 64, align: 64)
!357 = !DISubroutineType(types: !358)
!358 = !{!63, !351, !83}
!359 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !360, size: 64, align: 64)
!360 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !361, line: 276, baseType: !362)
!361 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!362 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !361, line: 267, baseType: !157)
!363 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !361, line: 269, baseType: !53)
!364 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !361, line: 270, baseType: !87)
!365 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !366, size: 64, align: 64)
!366 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !367, line: 101, baseType: !368)
!367 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!368 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !367, line: 82, size: 896, align: 64, elements: !369)
!369 = !{!370, !371, !372, !373, !374, !375, !376, !377, !382, !388, !393, !394, !395, !396}
!370 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !368, file: !367, line: 83, baseType: !359, size: 64, align: 64)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !368, file: !367, line: 84, baseType: !363, size: 32, align: 32, offset: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !368, file: !367, line: 85, baseType: !364, size: 64, align: 64, offset: 128)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !368, file: !367, line: 87, baseType: !359, size: 64, align: 64, offset: 192)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !368, file: !367, line: 88, baseType: !363, size: 32, align: 32, offset: 256)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !368, file: !367, line: 89, baseType: !364, size: 64, align: 64, offset: 320)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !368, file: !367, line: 91, baseType: !135, size: 64, align: 64, offset: 384)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !368, file: !367, line: 92, baseType: !378, size: 64, align: 64, offset: 448)
!378 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!379 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !367, line: 1346, size: 32, align: 32, elements: !380)
!380 = !{!381}
!381 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !379, file: !367, line: 1346, baseType: !63, size: 32, align: 32)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !368, file: !367, line: 94, baseType: !383, size: 64, align: 64, offset: 512)
!383 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !367, line: 77, baseType: !384)
!384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !385, size: 64, align: 64)
!385 = !DISubroutineType(types: !386)
!386 = !{!387, !387, !363, !363}
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !361, line: 285, baseType: !164)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !368, file: !367, line: 95, baseType: !389, size: 64, align: 64, offset: 576)
!389 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !367, line: 78, baseType: !390)
!390 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !391, size: 64, align: 64)
!391 = !DISubroutineType(types: !392)
!392 = !{null, !387, !387}
!393 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !368, file: !367, line: 96, baseType: !387, size: 64, align: 64, offset: 640)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !368, file: !367, line: 98, baseType: !63, size: 32, align: 32, offset: 704)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !368, file: !367, line: 99, baseType: !364, size: 64, align: 64, offset: 768)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !368, file: !367, line: 100, baseType: !364, size: 64, align: 64, offset: 832)
!397 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !398, size: 64, align: 64)
!398 = !DIDerivedType(tag: DW_TAG_typedef, name: "bz_stream", file: !399, line: 66, baseType: !400)
!399 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!400 = !DICompositeType(tag: DW_TAG_structure_type, file: !399, line: 49, size: 640, align: 64, elements: !401)
!401 = !{!402, !403, !404, !405, !406, !407, !408, !409, !410, !411, !415, !419}
!402 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !400, file: !399, line: 50, baseType: !135, size: 64, align: 64)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !400, file: !399, line: 51, baseType: !53, size: 32, align: 32, offset: 64)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_lo32", scope: !400, file: !399, line: 52, baseType: !53, size: 32, align: 32, offset: 96)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_hi32", scope: !400, file: !399, line: 53, baseType: !53, size: 32, align: 32, offset: 128)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !400, file: !399, line: 55, baseType: !135, size: 64, align: 64, offset: 192)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !400, file: !399, line: 56, baseType: !53, size: 32, align: 32, offset: 256)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_lo32", scope: !400, file: !399, line: 57, baseType: !53, size: 32, align: 32, offset: 288)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_hi32", scope: !400, file: !399, line: 58, baseType: !53, size: 32, align: 32, offset: 320)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !400, file: !399, line: 60, baseType: !164, size: 64, align: 64, offset: 384)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "bzalloc", scope: !400, file: !399, line: 62, baseType: !412, size: 64, align: 64, offset: 448)
!412 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !413, size: 64, align: 64)
!413 = !DISubroutineType(types: !414)
!414 = !{!164, !164, !63, !63}
!415 = !DIDerivedType(tag: DW_TAG_member, name: "bzfree", scope: !400, file: !399, line: 63, baseType: !416, size: 64, align: 64, offset: 512)
!416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !417, size: 64, align: 64)
!417 = !DISubroutineType(types: !418)
!418 = !{null, !164, !164}
!419 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !400, file: !399, line: 64, baseType: !164, size: 64, align: 64, offset: 576)
!420 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!421 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !422, size: 64, align: 64)
!422 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !423, line: 65, baseType: !424)
!423 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!424 = !DICompositeType(tag: DW_TAG_structure_type, file: !423, line: 43, size: 128, align: 64, elements: !425)
!425 = !{!426, !429}
!426 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !424, file: !423, line: 54, baseType: !427, size: 64, align: 64)
!427 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !428, line: 63, baseType: !237)
!428 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!429 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !424, file: !423, line: 63, baseType: !164, size: 64, align: 64, offset: 64)
!430 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !431, size: 64, align: 64)
!431 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !8, line: 490, baseType: !432)
!432 = !DICompositeType(tag: DW_TAG_structure_type, file: !8, line: 453, size: 1088, align: 64, elements: !433)
!433 = !{!434, !435, !436, !437, !438, !439, !440, !451, !455, !456, !457, !458, !459, !460, !461, !462, !463, !465}
!434 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !432, file: !8, line: 454, baseType: !297, size: 64, align: 64)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !432, file: !8, line: 455, baseType: !85, size: 64, align: 64, offset: 64)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !432, file: !8, line: 456, baseType: !237, size: 64, align: 64, offset: 128)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !432, file: !8, line: 458, baseType: !256, size: 64, align: 64, offset: 192)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !432, file: !8, line: 459, baseType: !85, size: 64, align: 64, offset: 256)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !432, file: !8, line: 460, baseType: !237, size: 64, align: 64, offset: 320)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !432, file: !8, line: 468, baseType: !441, size: 64, align: 64, offset: 384)
!441 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !442, size: 64, align: 64)
!442 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !8, line: 403, baseType: !443)
!443 = !DICompositeType(tag: DW_TAG_structure_type, file: !8, line: 341, size: 192, align: 64, elements: !444)
!444 = !{!445, !449, !450}
!445 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !443, file: !8, line: 376, baseType: !446, size: 64, align: 64)
!446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !447, size: 64, align: 64)
!447 = !DISubroutineType(types: !448)
!448 = !{!164, !164, !85, !85}
!449 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !443, file: !8, line: 390, baseType: !416, size: 64, align: 64, offset: 64)
!450 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !443, file: !8, line: 401, baseType: !164, size: 64, align: 64, offset: 128)
!451 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !432, file: !8, line: 471, baseType: !452, size: 64, align: 64, offset: 448)
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !453, size: 64, align: 64)
!453 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !8, line: 411, baseType: !454)
!454 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !8, line: 411, flags: DIFlagFwdDecl)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !432, file: !8, line: 479, baseType: !164, size: 64, align: 64, offset: 512)
!456 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !432, file: !8, line: 480, baseType: !164, size: 64, align: 64, offset: 576)
!457 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !432, file: !8, line: 481, baseType: !164, size: 64, align: 64, offset: 640)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !432, file: !8, line: 482, baseType: !164, size: 64, align: 64, offset: 704)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !432, file: !8, line: 483, baseType: !237, size: 64, align: 64, offset: 768)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !432, file: !8, line: 484, baseType: !237, size: 64, align: 64, offset: 832)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !432, file: !8, line: 485, baseType: !85, size: 64, align: 64, offset: 896)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !432, file: !8, line: 486, baseType: !85, size: 64, align: 64, offset: 960)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !432, file: !8, line: 487, baseType: !464, size: 32, align: 32, offset: 1024)
!464 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !8, line: 46, baseType: !7)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !432, file: !8, line: 488, baseType: !464, size: 32, align: 32, offset: 1056)
!466 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !93, line: 135, baseType: !87)
!467 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !468, size: 64, align: 64)
!468 = !DIDerivedType(tag: DW_TAG_typedef, name: "IByteOut", file: !469, line: 70, baseType: !470)
!469 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_ppmd_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!470 = !DICompositeType(tag: DW_TAG_structure_type, file: !469, line: 66, size: 128, align: 64, elements: !471)
!471 = !{!472, !473}
!472 = !DIDerivedType(tag: DW_TAG_member, name: "a", scope: !470, file: !469, line: 68, baseType: !44, size: 64, align: 64)
!473 = !DIDerivedType(tag: DW_TAG_member, name: "Write", scope: !470, file: !469, line: 69, baseType: !474, size: 64, align: 64, offset: 64)
!474 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !475, size: 64, align: 64)
!475 = !DISubroutineType(types: !476)
!476 = !{null, !164, !362}
!477 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !478, size: 64, align: 64)
!478 = !DICompositeType(tag: DW_TAG_structure_type, name: "ppmd_stream", file: !1, line: 125, size: 154176, align: 64, elements: !479)
!479 = !{!480, !481, !560, !571, !572, !573, !574, !575}
!480 = !DIDerivedType(tag: DW_TAG_member, name: "stat", scope: !478, file: !1, line: 126, baseType: !63, size: 32, align: 32)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "ppmd7_context", scope: !478, file: !1, line: 127, baseType: !482, size: 153472, align: 64, offset: 64)
!482 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd7", file: !483, line: 62, baseType: !484)
!483 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_ppmd7_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!484 = !DICompositeType(tag: DW_TAG_structure_type, file: !483, line: 44, size: 153472, align: 64, elements: !485)
!485 = !{!486, !500, !501, !510, !511, !512, !513, !514, !515, !517, !518, !519, !520, !522, !523, !524, !525, !526, !527, !531, !535, !538, !542, !543, !544, !551, !556}
!486 = !DIDerivedType(tag: DW_TAG_member, name: "MinContext", scope: !484, file: !483, line: 46, baseType: !487, size: 64, align: 64)
!487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !488, size: 64, align: 64)
!488 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd7_Context", file: !483, line: 40, baseType: !489)
!489 = !DICompositeType(tag: DW_TAG_structure_type, name: "CPpmd7_Context_", file: !483, line: 34, size: 96, align: 32, elements: !490)
!490 = !{!491, !494, !495, !498}
!491 = !DIDerivedType(tag: DW_TAG_member, name: "NumStats", scope: !489, file: !483, line: 36, baseType: !492, size: 16, align: 16)
!492 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt16", file: !469, line: 22, baseType: !493)
!493 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!494 = !DIDerivedType(tag: DW_TAG_member, name: "SummFreq", scope: !489, file: !483, line: 37, baseType: !492, size: 16, align: 16, offset: 16)
!495 = !DIDerivedType(tag: DW_TAG_member, name: "Stats", scope: !489, file: !483, line: 38, baseType: !496, size: 32, align: 32, offset: 32)
!496 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd_State_Ref", file: !469, line: 136, baseType: !497)
!497 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt32", file: !469, line: 29, baseType: !53)
!498 = !DIDerivedType(tag: DW_TAG_member, name: "Suffix", scope: !489, file: !483, line: 39, baseType: !499, size: 32, align: 32, offset: 64)
!499 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd7_Context_Ref", file: !483, line: 32, baseType: !497)
!500 = !DIDerivedType(tag: DW_TAG_member, name: "MaxContext", scope: !484, file: !483, line: 46, baseType: !487, size: 64, align: 64, offset: 64)
!501 = !DIDerivedType(tag: DW_TAG_member, name: "FoundState", scope: !484, file: !483, line: 47, baseType: !502, size: 64, align: 64, offset: 128)
!502 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !503, size: 64, align: 64)
!503 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd_State", file: !469, line: 128, baseType: !504)
!504 = !DICompositeType(tag: DW_TAG_structure_type, file: !469, line: 122, size: 48, align: 16, elements: !505)
!505 = !{!506, !507, !508, !509}
!506 = !DIDerivedType(tag: DW_TAG_member, name: "Symbol", scope: !504, file: !469, line: 124, baseType: !362, size: 8, align: 8)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "Freq", scope: !504, file: !469, line: 125, baseType: !362, size: 8, align: 8, offset: 8)
!508 = !DIDerivedType(tag: DW_TAG_member, name: "SuccessorLow", scope: !504, file: !469, line: 126, baseType: !492, size: 16, align: 16, offset: 16)
!509 = !DIDerivedType(tag: DW_TAG_member, name: "SuccessorHigh", scope: !504, file: !469, line: 127, baseType: !492, size: 16, align: 16, offset: 32)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "OrderFall", scope: !484, file: !483, line: 48, baseType: !53, size: 32, align: 32, offset: 192)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "InitEsc", scope: !484, file: !483, line: 48, baseType: !53, size: 32, align: 32, offset: 224)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "PrevSuccess", scope: !484, file: !483, line: 48, baseType: !53, size: 32, align: 32, offset: 256)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "MaxOrder", scope: !484, file: !483, line: 48, baseType: !53, size: 32, align: 32, offset: 288)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "HiBitsFlag", scope: !484, file: !483, line: 48, baseType: !53, size: 32, align: 32, offset: 320)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "RunLength", scope: !484, file: !483, line: 49, baseType: !516, size: 32, align: 32, offset: 352)
!516 = !DIDerivedType(tag: DW_TAG_typedef, name: "Int32", file: !469, line: 28, baseType: !63)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "InitRL", scope: !484, file: !483, line: 49, baseType: !516, size: 32, align: 32, offset: 384)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "Size", scope: !484, file: !483, line: 51, baseType: !497, size: 32, align: 32, offset: 416)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "GlueCount", scope: !484, file: !483, line: 52, baseType: !497, size: 32, align: 32, offset: 448)
!520 = !DIDerivedType(tag: DW_TAG_member, name: "Base", scope: !484, file: !483, line: 53, baseType: !521, size: 64, align: 64, offset: 512)
!521 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !362, size: 64, align: 64)
!522 = !DIDerivedType(tag: DW_TAG_member, name: "LoUnit", scope: !484, file: !483, line: 53, baseType: !521, size: 64, align: 64, offset: 576)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "HiUnit", scope: !484, file: !483, line: 53, baseType: !521, size: 64, align: 64, offset: 640)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "Text", scope: !484, file: !483, line: 53, baseType: !521, size: 64, align: 64, offset: 704)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "UnitsStart", scope: !484, file: !483, line: 53, baseType: !521, size: 64, align: 64, offset: 768)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "AlignOffset", scope: !484, file: !483, line: 54, baseType: !497, size: 32, align: 32, offset: 832)
!527 = !DIDerivedType(tag: DW_TAG_member, name: "Indx2Units", scope: !484, file: !483, line: 56, baseType: !528, size: 304, align: 8, offset: 864)
!528 = !DICompositeType(tag: DW_TAG_array_type, baseType: !362, size: 304, align: 8, elements: !529)
!529 = !{!530}
!530 = !DISubrange(count: 38)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "Units2Indx", scope: !484, file: !483, line: 57, baseType: !532, size: 1024, align: 8, offset: 1168)
!532 = !DICompositeType(tag: DW_TAG_array_type, baseType: !362, size: 1024, align: 8, elements: !533)
!533 = !{!534}
!534 = !DISubrange(count: 128)
!535 = !DIDerivedType(tag: DW_TAG_member, name: "FreeList", scope: !484, file: !483, line: 58, baseType: !536, size: 1216, align: 32, offset: 2208)
!536 = !DICompositeType(tag: DW_TAG_array_type, baseType: !537, size: 1216, align: 32, elements: !529)
!537 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd_Void_Ref", file: !469, line: 144, baseType: !497)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "NS2Indx", scope: !484, file: !483, line: 59, baseType: !539, size: 2048, align: 8, offset: 3424)
!539 = !DICompositeType(tag: DW_TAG_array_type, baseType: !362, size: 2048, align: 8, elements: !540)
!540 = !{!541}
!541 = !DISubrange(count: 256)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "NS2BSIndx", scope: !484, file: !483, line: 59, baseType: !539, size: 2048, align: 8, offset: 5472)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "HB2Flag", scope: !484, file: !483, line: 59, baseType: !539, size: 2048, align: 8, offset: 7520)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "DummySee", scope: !484, file: !483, line: 60, baseType: !545, size: 32, align: 16, offset: 9568)
!545 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd_See", file: !469, line: 117, baseType: !546)
!546 = !DICompositeType(tag: DW_TAG_structure_type, file: !469, line: 112, size: 32, align: 16, elements: !547)
!547 = !{!548, !549, !550}
!548 = !DIDerivedType(tag: DW_TAG_member, name: "Summ", scope: !546, file: !469, line: 114, baseType: !492, size: 16, align: 16)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "Shift", scope: !546, file: !469, line: 115, baseType: !362, size: 8, align: 8, offset: 16)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "Count", scope: !546, file: !469, line: 116, baseType: !362, size: 8, align: 8, offset: 24)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "See", scope: !484, file: !483, line: 60, baseType: !552, size: 12800, align: 16, offset: 9600)
!552 = !DICompositeType(tag: DW_TAG_array_type, baseType: !545, size: 12800, align: 16, elements: !553)
!553 = !{!554, !555}
!554 = !DISubrange(count: 25)
!555 = !DISubrange(count: 16)
!556 = !DIDerivedType(tag: DW_TAG_member, name: "BinSumm", scope: !484, file: !483, line: 61, baseType: !557, size: 131072, align: 16, offset: 22400)
!557 = !DICompositeType(tag: DW_TAG_array_type, baseType: !492, size: 131072, align: 16, elements: !558)
!558 = !{!534, !559}
!559 = !DISubrange(count: 64)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "range_enc", scope: !478, file: !1, line: 128, baseType: !561, size: 256, align: 64, offset: 153536)
!561 = !DIDerivedType(tag: DW_TAG_typedef, name: "CPpmd7z_RangeEnc", file: !483, line: 92, baseType: !562)
!562 = !DICompositeType(tag: DW_TAG_structure_type, file: !483, line: 85, size: 256, align: 64, elements: !563)
!563 = !{!564, !567, !568, !569, !570}
!564 = !DIDerivedType(tag: DW_TAG_member, name: "Low", scope: !562, file: !483, line: 87, baseType: !565, size: 64, align: 64)
!565 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt64", file: !469, line: 48, baseType: !566)
!566 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "Range", scope: !562, file: !483, line: 88, baseType: !497, size: 32, align: 32, offset: 64)
!568 = !DIDerivedType(tag: DW_TAG_member, name: "Cache", scope: !562, file: !483, line: 89, baseType: !362, size: 8, align: 8, offset: 96)
!569 = !DIDerivedType(tag: DW_TAG_member, name: "CacheSize", scope: !562, file: !483, line: 90, baseType: !565, size: 64, align: 64, offset: 128)
!570 = !DIDerivedType(tag: DW_TAG_member, name: "Stream", scope: !562, file: !483, line: 91, baseType: !467, size: 64, align: 64, offset: 192)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "byteout", scope: !478, file: !1, line: 129, baseType: !468, size: 128, align: 64, offset: 153792)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !478, file: !1, line: 130, baseType: !256, size: 64, align: 64, offset: 153920)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "buff_ptr", scope: !478, file: !1, line: 131, baseType: !256, size: 64, align: 64, offset: 153984)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "buff_end", scope: !478, file: !1, line: 132, baseType: !256, size: 64, align: 64, offset: 154048)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "buff_bytes", scope: !478, file: !1, line: 133, baseType: !85, size: 64, align: 64, offset: 154112)
!576 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !93, line: 134, baseType: !82)
!577 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !578, size: 64, align: 64)
!578 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !240)
!579 = !{!580, !582, !583, !584, !587, !590, !593, !596, !599, !600, !601, !602, !605, !606, !607, !608, !611, !612, !613, !614, !617, !621, !624, !625, !626, !627, !628, !629, !630, !631, !632, !635, !636, !639, !640, !641, !642, !646, !649, !652, !655, !658, !661, !662, !665, !666, !669, !670, !671, !674, !675, !676, !677}
!580 = distinct !DISubprogram(name: "archive_write_set_format_7zip", scope: !1, file: !1, line: 285, type: !61, isLocal: false, isDefinition: true, scopeLine: 286, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!581 = !{}
!582 = distinct !DISubprogram(name: "_7z_options", scope: !1, file: !1, line: 339, type: !212, isLocal: true, isDefinition: true, scopeLine: 340, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!583 = distinct !DISubprogram(name: "_7z_write_header", scope: !1, file: !1, line: 423, type: !217, isLocal: true, isDefinition: true, scopeLine: 424, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!584 = distinct !DISubprogram(name: "file_new", scope: !1, file: !1, line: 1486, type: !585, isLocal: true, isDefinition: true, scopeLine: 1488, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!585 = !DISubroutineType(types: !586)
!586 = !{!63, !44, !70, !334}
!587 = distinct !DISubprogram(name: "file_free", scope: !1, file: !1, line: 1558, type: !588, isLocal: true, isDefinition: true, scopeLine: 1559, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!588 = !DISubroutineType(types: !589)
!589 = !{null, !239}
!590 = distinct !DISubprogram(name: "file_register_empty", scope: !1, file: !1, line: 1593, type: !591, isLocal: true, isDefinition: true, scopeLine: 1594, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!591 = !DISubroutineType(types: !592)
!592 = !{null, !232, !239}
!593 = distinct !DISubprogram(name: "_7z_compression_init_encoder", scope: !1, file: !1, line: 2258, type: !594, isLocal: true, isDefinition: true, scopeLine: 2260, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!594 = !DISubroutineType(types: !595)
!595 = !{!63, !44, !53, !63}
!596 = distinct !DISubprogram(name: "compression_init_encoder_deflate", scope: !1, file: !1, line: 1675, type: !597, isLocal: true, isDefinition: true, scopeLine: 1677, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!597 = !DISubroutineType(types: !598)
!598 = !{!63, !64, !312, !63, !63}
!599 = distinct !DISubprogram(name: "compression_end", scope: !1, file: !1, line: 2317, type: !315, isLocal: true, isDefinition: true, scopeLine: 2318, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!600 = distinct !DISubprogram(name: "compression_code_deflate", scope: !1, file: !1, line: 1714, type: !310, isLocal: true, isDefinition: true, scopeLine: 1716, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!601 = distinct !DISubprogram(name: "compression_end_deflate", scope: !1, file: !1, line: 1752, type: !315, isLocal: true, isDefinition: true, scopeLine: 1753, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!602 = distinct !DISubprogram(name: "compression_init_encoder_bzip2", scope: !1, file: !1, line: 1788, type: !603, isLocal: true, isDefinition: true, scopeLine: 1790, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!603 = !DISubroutineType(types: !604)
!604 = !{!63, !64, !312, !63}
!605 = distinct !DISubprogram(name: "compression_code_bzip2", scope: !1, file: !1, line: 1827, type: !310, isLocal: true, isDefinition: true, scopeLine: 1829, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!606 = distinct !DISubprogram(name: "compression_end_bzip2", scope: !1, file: !1, line: 1874, type: !315, isLocal: true, isDefinition: true, scopeLine: 1875, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!607 = distinct !DISubprogram(name: "compression_init_encoder_lzma1", scope: !1, file: !1, line: 1999, type: !603, isLocal: true, isDefinition: true, scopeLine: 2001, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!608 = distinct !DISubprogram(name: "compression_init_encoder_lzma", scope: !1, file: !1, line: 1910, type: !609, isLocal: true, isDefinition: true, scopeLine: 1912, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!609 = !DISubroutineType(types: !610)
!610 = !{!63, !64, !312, !63, !237}
!611 = distinct !DISubprogram(name: "compression_code_lzma", scope: !1, file: !1, line: 2015, type: !310, isLocal: true, isDefinition: true, scopeLine: 2017, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!612 = distinct !DISubprogram(name: "compression_end_lzma", scope: !1, file: !1, line: 2060, type: !315, isLocal: true, isDefinition: true, scopeLine: 2061, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!613 = distinct !DISubprogram(name: "compression_init_encoder_lzma2", scope: !1, file: !1, line: 2007, type: !603, isLocal: true, isDefinition: true, scopeLine: 2009, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!614 = distinct !DISubprogram(name: "compression_init_encoder_ppmd", scope: !1, file: !1, line: 2133, type: !615, isLocal: true, isDefinition: true, scopeLine: 2135, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!615 = !DISubroutineType(types: !616)
!616 = !{!63, !64, !312, !53, !275}
!617 = distinct !DISubprogram(name: "archive_le32enc", scope: !618, file: !618, line: 177, type: !619, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!618 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!619 = !DISubroutineType(types: !620)
!620 = !{null, !164, !275}
!621 = distinct !DISubprogram(name: "ppmd_alloc", scope: !1, file: !1, line: 2099, type: !622, isLocal: true, isDefinition: true, scopeLine: 2100, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!622 = !DISubroutineType(types: !623)
!623 = !{!164, !164, !85}
!624 = distinct !DISubprogram(name: "ppmd_free", scope: !1, file: !1, line: 2105, type: !417, isLocal: true, isDefinition: true, scopeLine: 2106, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!625 = distinct !DISubprogram(name: "ppmd_write", scope: !1, file: !1, line: 2112, type: !475, isLocal: true, isDefinition: true, scopeLine: 2113, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!626 = distinct !DISubprogram(name: "compression_code_ppmd", scope: !1, file: !1, line: 2196, type: !310, isLocal: true, isDefinition: true, scopeLine: 2198, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!627 = distinct !DISubprogram(name: "compression_end_ppmd", scope: !1, file: !1, line: 2239, type: !315, isLocal: true, isDefinition: true, scopeLine: 2240, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!628 = distinct !DISubprogram(name: "compression_init_encoder_copy", scope: !1, file: !1, line: 1626, type: !315, isLocal: true, isDefinition: true, scopeLine: 1627, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!629 = distinct !DISubprogram(name: "compression_code_copy", scope: !1, file: !1, line: 1638, type: !310, isLocal: true, isDefinition: true, scopeLine: 1640, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!630 = distinct !DISubprogram(name: "compression_end_copy", scope: !1, file: !1, line: 1663, type: !315, isLocal: true, isDefinition: true, scopeLine: 1664, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!631 = distinct !DISubprogram(name: "file_register", scope: !1, file: !1, line: 1565, type: !591, isLocal: true, isDefinition: true, scopeLine: 1566, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!632 = distinct !DISubprogram(name: "compress_out", scope: !1, file: !1, line: 555, type: !633, isLocal: true, isDefinition: true, scopeLine: 557, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!633 = !DISubroutineType(types: !634)
!634 = !{!78, !44, !83, !85, !3}
!635 = distinct !DISubprogram(name: "compression_code", scope: !1, file: !1, line: 2308, type: !310, isLocal: true, isDefinition: true, scopeLine: 2310, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!636 = distinct !DISubprogram(name: "write_to_temp", scope: !1, file: !1, line: 518, type: !637, isLocal: true, isDefinition: true, scopeLine: 519, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!637 = !DISubroutineType(types: !638)
!638 = !{!63, !44, !83, !85}
!639 = distinct !DISubprogram(name: "_7z_write_data", scope: !1, file: !1, line: 602, type: !221, isLocal: true, isDefinition: true, scopeLine: 603, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!640 = distinct !DISubprogram(name: "_7z_finish_entry", scope: !1, file: !1, line: 622, type: !208, isLocal: true, isDefinition: true, scopeLine: 623, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!641 = distinct !DISubprogram(name: "_7z_close", scope: !1, file: !1, line: 710, type: !208, isLocal: true, isDefinition: true, scopeLine: 711, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!642 = distinct !DISubprogram(name: "make_header", scope: !1, file: !1, line: 1245, type: !643, isLocal: true, isDefinition: true, scopeLine: 1247, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!643 = !DISubroutineType(types: !644)
!644 = !{!63, !44, !237, !237, !237, !63, !645}
!645 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !318, size: 64, align: 64)
!646 = distinct !DISubprogram(name: "make_time", scope: !1, file: !1, line: 1156, type: !647, isLocal: true, isDefinition: true, scopeLine: 1157, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!647 = !DISubroutineType(types: !648)
!648 = !{!63, !44, !257, !53, !63}
!649 = distinct !DISubprogram(name: "utcToFiletime", scope: !1, file: !1, line: 1144, type: !650, isLocal: true, isDefinition: true, scopeLine: 1145, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!650 = !DISubroutineType(types: !651)
!651 = !{!237, !265, !82}
!652 = distinct !DISubprogram(name: "enc_uint64", scope: !1, file: !1, line: 853, type: !653, isLocal: true, isDefinition: true, scopeLine: 854, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!653 = !DISubroutineType(types: !654)
!654 = !{!63, !44, !237}
!655 = distinct !DISubprogram(name: "make_streamsInfo", scope: !1, file: !1, line: 948, type: !656, isLocal: true, isDefinition: true, scopeLine: 951, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!656 = !DISubroutineType(types: !657)
!657 = !{!63, !44, !237, !237, !237, !63, !645, !63, !275}
!658 = distinct !DISubprogram(name: "archive_be64enc", scope: !618, file: !618, line: 159, type: !659, isLocal: true, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!659 = !DISubroutineType(types: !660)
!660 = !{null, !164, !237}
!661 = distinct !DISubprogram(name: "archive_be32enc", scope: !618, file: !618, line: 148, type: !619, isLocal: true, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!662 = distinct !DISubprogram(name: "make_substreamsInfo", scope: !1, file: !1, line: 874, type: !663, isLocal: true, isDefinition: true, scopeLine: 875, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!663 = !DISubroutineType(types: !664)
!664 = !{!63, !44, !645}
!665 = distinct !DISubprogram(name: "archive_le64enc", scope: !618, file: !618, line: 188, type: !659, isLocal: true, isDefinition: true, scopeLine: 189, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!666 = distinct !DISubprogram(name: "copy_out", scope: !1, file: !1, line: 665, type: !667, isLocal: true, isDefinition: true, scopeLine: 666, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!667 = !DISubroutineType(types: !668)
!668 = !{!63, !44, !237, !237}
!669 = distinct !DISubprogram(name: "flush_wbuff", scope: !1, file: !1, line: 649, type: !208, isLocal: true, isDefinition: true, scopeLine: 650, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!670 = distinct !DISubprogram(name: "_7z_free", scope: !1, file: !1, line: 1449, type: !208, isLocal: true, isDefinition: true, scopeLine: 1450, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!671 = distinct !DISubprogram(name: "file_free_register", scope: !1, file: !1, line: 1580, type: !672, isLocal: true, isDefinition: true, scopeLine: 1581, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!672 = !DISubroutineType(types: !673)
!673 = !{null, !232}
!674 = distinct !DISubprogram(name: "file_cmp_node", scope: !1, file: !1, line: 1466, type: !349, isLocal: true, isDefinition: true, scopeLine: 1468, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!675 = distinct !DISubprogram(name: "file_cmp_key", scope: !1, file: !1, line: 1478, type: !357, isLocal: true, isDefinition: true, scopeLine: 1479, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!676 = distinct !DISubprogram(name: "file_init_register", scope: !1, file: !1, line: 1573, type: !672, isLocal: true, isDefinition: true, scopeLine: 1574, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!677 = distinct !DISubprogram(name: "file_init_register_empty", scope: !1, file: !1, line: 1601, type: !672, isLocal: true, isDefinition: true, scopeLine: 1602, flags: DIFlagPrototyped, isOptimized: false, variables: !581)
!678 = !{!679, !680, !682}
!679 = !DIGlobalVariable(name: "rb_ops", scope: !580, file: !1, line: 287, type: !342, isLocal: true, isDefinition: true, variable: %struct.archive_rb_tree_ops* @archive_write_set_format_7zip.rb_ops)
!680 = !DIGlobalVariable(name: "lzma_init_data", scope: !608, file: !1, line: 1913, type: !681, isLocal: true, isDefinition: true, variable: %struct.lzma_stream* @compression_init_encoder_lzma.lzma_init_data)
!681 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !431)
!682 = !DIGlobalVariable(name: "g_szalloc", scope: !0, file: !1, line: 2110, type: !683, isLocal: true, isDefinition: true, variable: %struct.ISzAlloc* @g_szalloc)
!683 = !DIDerivedType(tag: DW_TAG_typedef, name: "ISzAlloc", file: !469, line: 77, baseType: !684)
!684 = !DICompositeType(tag: DW_TAG_structure_type, file: !469, line: 73, size: 128, align: 64, elements: !685)
!685 = !{!686, !688}
!686 = !DIDerivedType(tag: DW_TAG_member, name: "Alloc", scope: !684, file: !469, line: 75, baseType: !687, size: 64, align: 64)
!687 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !622, size: 64, align: 64)
!688 = !DIDerivedType(tag: DW_TAG_member, name: "Free", scope: !684, file: !469, line: 76, baseType: !416, size: 64, align: 64, offset: 64)
!689 = !{i32 2, !"Dwarf Version", i32 4}
!690 = !{i32 2, !"Debug Info Version", i32 3}
!691 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!692 = !DILocalVariable(name: "_a", arg: 1, scope: !580, file: !1, line: 285, type: !64)
!693 = !DIExpression()
!694 = !DILocation(line: 285, column: 47, scope: !580)
!695 = !DILocalVariable(name: "a", scope: !580, file: !1, line: 290, type: !44)
!696 = !DILocation(line: 290, column: 24, scope: !580)
!697 = !DILocation(line: 290, column: 52, scope: !580)
!698 = !DILocation(line: 290, column: 28, scope: !580)
!699 = !DILocalVariable(name: "zip", scope: !580, file: !1, line: 291, type: !232)
!700 = !DILocation(line: 291, column: 16, scope: !580)
!701 = !DILocation(line: 293, column: 2, scope: !580)
!702 = !DILocalVariable(name: "magic_test", scope: !703, file: !1, line: 293, type: !63)
!703 = distinct !DILexicalBlock(scope: !580, file: !1, line: 293, column: 2)
!704 = !DILocation(line: 293, column: 2, scope: !703)
!705 = !DILocation(line: 293, column: 2, scope: !706)
!706 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 1)
!707 = !DILocation(line: 293, column: 2, scope: !708)
!708 = !DILexicalBlockFile(scope: !709, file: !1, discriminator: 2)
!709 = distinct !DILexicalBlock(scope: !703, file: !1, line: 293, column: 2)
!710 = !DILocation(line: 293, column: 2, scope: !711)
!711 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 3)
!712 = !DILocation(line: 297, column: 6, scope: !713)
!713 = distinct !DILexicalBlock(scope: !580, file: !1, line: 297, column: 6)
!714 = !DILocation(line: 297, column: 9, scope: !713)
!715 = !DILocation(line: 297, column: 21, scope: !713)
!716 = !DILocation(line: 297, column: 6, scope: !580)
!717 = !DILocation(line: 298, column: 4, scope: !713)
!718 = !DILocation(line: 298, column: 7, scope: !713)
!719 = !DILocation(line: 298, column: 20, scope: !713)
!720 = !DILocation(line: 298, column: 3, scope: !713)
!721 = !DILocation(line: 300, column: 8, scope: !580)
!722 = !DILocation(line: 300, column: 6, scope: !580)
!723 = !DILocation(line: 301, column: 6, scope: !724)
!724 = distinct !DILexicalBlock(scope: !580, file: !1, line: 301, column: 6)
!725 = !DILocation(line: 301, column: 10, scope: !724)
!726 = !DILocation(line: 301, column: 6, scope: !580)
!727 = !DILocation(line: 302, column: 22, scope: !728)
!728 = distinct !DILexicalBlock(scope: !724, file: !1, line: 301, column: 19)
!729 = !DILocation(line: 302, column: 25, scope: !728)
!730 = !DILocation(line: 302, column: 3, scope: !728)
!731 = !DILocation(line: 304, column: 3, scope: !728)
!732 = !DILocation(line: 306, column: 2, scope: !580)
!733 = !DILocation(line: 306, column: 7, scope: !580)
!734 = !DILocation(line: 306, column: 15, scope: !580)
!735 = !DILocation(line: 307, column: 27, scope: !580)
!736 = !DILocation(line: 307, column: 32, scope: !580)
!737 = !DILocation(line: 307, column: 2, scope: !580)
!738 = !DILocation(line: 308, column: 21, scope: !580)
!739 = !DILocation(line: 308, column: 2, scope: !580)
!740 = !DILocation(line: 309, column: 27, scope: !580)
!741 = !DILocation(line: 309, column: 2, scope: !580)
!742 = !DILocation(line: 313, column: 2, scope: !580)
!743 = !DILocation(line: 313, column: 7, scope: !580)
!744 = !DILocation(line: 313, column: 23, scope: !580)
!745 = !DILocation(line: 321, column: 2, scope: !580)
!746 = !DILocation(line: 321, column: 7, scope: !580)
!747 = !DILocation(line: 321, column: 29, scope: !580)
!748 = !DILocation(line: 323, column: 19, scope: !580)
!749 = !DILocation(line: 323, column: 2, scope: !580)
!750 = !DILocation(line: 323, column: 5, scope: !580)
!751 = !DILocation(line: 323, column: 17, scope: !580)
!752 = !DILocation(line: 325, column: 2, scope: !580)
!753 = !DILocation(line: 325, column: 5, scope: !580)
!754 = !DILocation(line: 325, column: 17, scope: !580)
!755 = !DILocation(line: 326, column: 2, scope: !580)
!756 = !DILocation(line: 326, column: 5, scope: !580)
!757 = !DILocation(line: 326, column: 20, scope: !580)
!758 = !DILocation(line: 327, column: 2, scope: !580)
!759 = !DILocation(line: 327, column: 5, scope: !580)
!760 = !DILocation(line: 327, column: 25, scope: !580)
!761 = !DILocation(line: 328, column: 2, scope: !580)
!762 = !DILocation(line: 328, column: 5, scope: !580)
!763 = !DILocation(line: 328, column: 23, scope: !580)
!764 = !DILocation(line: 329, column: 2, scope: !580)
!765 = !DILocation(line: 329, column: 5, scope: !580)
!766 = !DILocation(line: 329, column: 25, scope: !580)
!767 = !DILocation(line: 330, column: 2, scope: !580)
!768 = !DILocation(line: 330, column: 5, scope: !580)
!769 = !DILocation(line: 330, column: 18, scope: !580)
!770 = !DILocation(line: 331, column: 2, scope: !580)
!771 = !DILocation(line: 331, column: 5, scope: !580)
!772 = !DILocation(line: 331, column: 17, scope: !580)
!773 = !DILocation(line: 332, column: 2, scope: !580)
!774 = !DILocation(line: 332, column: 5, scope: !580)
!775 = !DILocation(line: 332, column: 13, scope: !580)
!776 = !DILocation(line: 332, column: 28, scope: !580)
!777 = !DILocation(line: 333, column: 2, scope: !580)
!778 = !DILocation(line: 333, column: 5, scope: !580)
!779 = !DILocation(line: 333, column: 13, scope: !580)
!780 = !DILocation(line: 333, column: 33, scope: !580)
!781 = !DILocation(line: 335, column: 2, scope: !580)
!782 = !DILocation(line: 336, column: 1, scope: !580)
!783 = !DILocalVariable(name: "n1", arg: 1, scope: !674, file: !1, line: 1466, type: !351)
!784 = !DILocation(line: 1466, column: 45, scope: !674)
!785 = !DILocalVariable(name: "n2", arg: 2, scope: !674, file: !1, line: 1467, type: !351)
!786 = !DILocation(line: 1467, column: 35, scope: !674)
!787 = !DILocalVariable(name: "f1", scope: !674, file: !1, line: 1469, type: !577)
!788 = !DILocation(line: 1469, column: 21, scope: !674)
!789 = !DILocation(line: 1469, column: 47, scope: !674)
!790 = !DILocation(line: 1469, column: 26, scope: !674)
!791 = !DILocalVariable(name: "f2", scope: !674, file: !1, line: 1470, type: !577)
!792 = !DILocation(line: 1470, column: 21, scope: !674)
!793 = !DILocation(line: 1470, column: 47, scope: !674)
!794 = !DILocation(line: 1470, column: 26, scope: !674)
!795 = !DILocation(line: 1472, column: 6, scope: !796)
!796 = distinct !DILexicalBlock(scope: !674, file: !1, line: 1472, column: 6)
!797 = !DILocation(line: 1472, column: 10, scope: !796)
!798 = !DILocation(line: 1472, column: 22, scope: !796)
!799 = !DILocation(line: 1472, column: 26, scope: !796)
!800 = !DILocation(line: 1472, column: 19, scope: !796)
!801 = !DILocation(line: 1472, column: 6, scope: !674)
!802 = !DILocation(line: 1473, column: 18, scope: !796)
!803 = !DILocation(line: 1473, column: 22, scope: !796)
!804 = !DILocation(line: 1473, column: 33, scope: !796)
!805 = !DILocation(line: 1473, column: 37, scope: !796)
!806 = !DILocation(line: 1473, column: 48, scope: !796)
!807 = !DILocation(line: 1473, column: 52, scope: !796)
!808 = !DILocation(line: 1473, column: 11, scope: !796)
!809 = !DILocation(line: 1473, column: 3, scope: !796)
!810 = !DILocation(line: 1474, column: 10, scope: !674)
!811 = !DILocation(line: 1474, column: 14, scope: !674)
!812 = !DILocation(line: 1474, column: 25, scope: !674)
!813 = !DILocation(line: 1474, column: 29, scope: !674)
!814 = !DILocation(line: 1474, column: 23, scope: !674)
!815 = !DILocation(line: 1474, column: 9, scope: !674)
!816 = !DILocation(line: 1474, column: 2, scope: !674)
!817 = !DILocation(line: 1475, column: 1, scope: !674)
!818 = !DILocalVariable(name: "n", arg: 1, scope: !675, file: !1, line: 1478, type: !351)
!819 = !DILocation(line: 1478, column: 44, scope: !675)
!820 = !DILocalVariable(name: "key", arg: 2, scope: !675, file: !1, line: 1478, type: !83)
!821 = !DILocation(line: 1478, column: 59, scope: !675)
!822 = !DILocalVariable(name: "f", scope: !675, file: !1, line: 1480, type: !577)
!823 = !DILocation(line: 1480, column: 21, scope: !675)
!824 = !DILocation(line: 1480, column: 46, scope: !675)
!825 = !DILocation(line: 1480, column: 25, scope: !675)
!826 = !DILocation(line: 1482, column: 10, scope: !675)
!827 = !DILocation(line: 1482, column: 13, scope: !675)
!828 = !DILocation(line: 1482, column: 39, scope: !675)
!829 = !DILocation(line: 1482, column: 24, scope: !675)
!830 = !DILocation(line: 1482, column: 22, scope: !675)
!831 = !DILocation(line: 1482, column: 2, scope: !675)
!832 = !DILocalVariable(name: "zip", arg: 1, scope: !676, file: !1, line: 1573, type: !232)
!833 = !DILocation(line: 1573, column: 34, scope: !676)
!834 = !DILocation(line: 1575, column: 2, scope: !676)
!835 = !DILocation(line: 1575, column: 7, scope: !676)
!836 = !DILocation(line: 1575, column: 17, scope: !676)
!837 = !DILocation(line: 1575, column: 23, scope: !676)
!838 = !DILocation(line: 1576, column: 26, scope: !676)
!839 = !DILocation(line: 1576, column: 31, scope: !676)
!840 = !DILocation(line: 1576, column: 41, scope: !676)
!841 = !DILocation(line: 1576, column: 2, scope: !676)
!842 = !DILocation(line: 1576, column: 7, scope: !676)
!843 = !DILocation(line: 1576, column: 17, scope: !676)
!844 = !DILocation(line: 1576, column: 22, scope: !676)
!845 = !DILocation(line: 1577, column: 1, scope: !676)
!846 = !DILocalVariable(name: "zip", arg: 1, scope: !677, file: !1, line: 1601, type: !232)
!847 = !DILocation(line: 1601, column: 40, scope: !677)
!848 = !DILocation(line: 1603, column: 2, scope: !677)
!849 = !DILocation(line: 1603, column: 7, scope: !677)
!850 = !DILocation(line: 1603, column: 18, scope: !677)
!851 = !DILocation(line: 1603, column: 24, scope: !677)
!852 = !DILocation(line: 1604, column: 27, scope: !677)
!853 = !DILocation(line: 1604, column: 32, scope: !677)
!854 = !DILocation(line: 1604, column: 43, scope: !677)
!855 = !DILocation(line: 1604, column: 2, scope: !677)
!856 = !DILocation(line: 1604, column: 7, scope: !677)
!857 = !DILocation(line: 1604, column: 18, scope: !677)
!858 = !DILocation(line: 1604, column: 23, scope: !677)
!859 = !DILocation(line: 1605, column: 1, scope: !677)
!860 = !DILocalVariable(name: "a", arg: 1, scope: !582, file: !1, line: 339, type: !44)
!861 = !DILocation(line: 339, column: 35, scope: !582)
!862 = !DILocalVariable(name: "key", arg: 2, scope: !582, file: !1, line: 339, type: !120)
!863 = !DILocation(line: 339, column: 50, scope: !582)
!864 = !DILocalVariable(name: "value", arg: 3, scope: !582, file: !1, line: 339, type: !120)
!865 = !DILocation(line: 339, column: 67, scope: !582)
!866 = !DILocalVariable(name: "zip", scope: !582, file: !1, line: 341, type: !232)
!867 = !DILocation(line: 341, column: 16, scope: !582)
!868 = !DILocation(line: 343, column: 24, scope: !582)
!869 = !DILocation(line: 343, column: 27, scope: !582)
!870 = !DILocation(line: 343, column: 8, scope: !582)
!871 = !DILocation(line: 343, column: 6, scope: !582)
!872 = !DILocation(line: 345, column: 13, scope: !873)
!873 = distinct !DILexicalBlock(scope: !582, file: !1, line: 345, column: 6)
!874 = !DILocation(line: 345, column: 6, scope: !873)
!875 = !DILocation(line: 345, column: 33, scope: !873)
!876 = !DILocation(line: 345, column: 6, scope: !582)
!877 = !DILocalVariable(name: "name", scope: !878, file: !1, line: 346, type: !120)
!878 = distinct !DILexicalBlock(scope: !873, file: !1, line: 345, column: 39)
!879 = !DILocation(line: 346, column: 15, scope: !878)
!880 = !DILocation(line: 348, column: 7, scope: !881)
!881 = distinct !DILexicalBlock(scope: !878, file: !1, line: 348, column: 7)
!882 = !DILocation(line: 348, column: 13, scope: !881)
!883 = !DILocation(line: 348, column: 21, scope: !881)
!884 = !DILocation(line: 348, column: 31, scope: !885)
!885 = !DILexicalBlockFile(scope: !881, file: !1, discriminator: 1)
!886 = !DILocation(line: 348, column: 24, scope: !885)
!887 = !DILocation(line: 348, column: 46, scope: !885)
!888 = !DILocation(line: 348, column: 51, scope: !885)
!889 = !DILocation(line: 349, column: 14, scope: !881)
!890 = !DILocation(line: 349, column: 7, scope: !881)
!891 = !DILocation(line: 349, column: 29, scope: !881)
!892 = !DILocation(line: 349, column: 34, scope: !881)
!893 = !DILocation(line: 350, column: 14, scope: !881)
!894 = !DILocation(line: 350, column: 7, scope: !881)
!895 = !DILocation(line: 350, column: 30, scope: !881)
!896 = !DILocation(line: 350, column: 35, scope: !881)
!897 = !DILocation(line: 351, column: 14, scope: !881)
!898 = !DILocation(line: 351, column: 7, scope: !881)
!899 = !DILocation(line: 351, column: 30, scope: !881)
!900 = !DILocation(line: 348, column: 7, scope: !901)
!901 = !DILexicalBlockFile(scope: !878, file: !1, discriminator: 2)
!902 = !DILocation(line: 352, column: 4, scope: !881)
!903 = !DILocation(line: 352, column: 9, scope: !881)
!904 = !DILocation(line: 352, column: 25, scope: !881)
!905 = !DILocation(line: 353, column: 19, scope: !906)
!906 = distinct !DILexicalBlock(scope: !881, file: !1, line: 353, column: 12)
!907 = !DILocation(line: 353, column: 12, scope: !906)
!908 = !DILocation(line: 353, column: 37, scope: !906)
!909 = !DILocation(line: 353, column: 42, scope: !906)
!910 = !DILocation(line: 354, column: 14, scope: !906)
!911 = !DILocation(line: 354, column: 7, scope: !906)
!912 = !DILocation(line: 354, column: 32, scope: !906)
!913 = !DILocation(line: 353, column: 12, scope: !885)
!914 = !DILocation(line: 356, column: 4, scope: !906)
!915 = !DILocation(line: 356, column: 9, scope: !906)
!916 = !DILocation(line: 356, column: 25, scope: !906)
!917 = !DILocation(line: 360, column: 19, scope: !918)
!918 = distinct !DILexicalBlock(scope: !906, file: !1, line: 360, column: 12)
!919 = !DILocation(line: 360, column: 12, scope: !918)
!920 = !DILocation(line: 360, column: 35, scope: !918)
!921 = !DILocation(line: 360, column: 40, scope: !918)
!922 = !DILocation(line: 361, column: 14, scope: !918)
!923 = !DILocation(line: 361, column: 7, scope: !918)
!924 = !DILocation(line: 361, column: 30, scope: !918)
!925 = !DILocation(line: 360, column: 12, scope: !926)
!926 = !DILexicalBlockFile(scope: !906, file: !1, discriminator: 1)
!927 = !DILocation(line: 363, column: 4, scope: !918)
!928 = !DILocation(line: 363, column: 9, scope: !918)
!929 = !DILocation(line: 363, column: 25, scope: !918)
!930 = !DILocation(line: 367, column: 19, scope: !931)
!931 = distinct !DILexicalBlock(scope: !918, file: !1, line: 367, column: 12)
!932 = !DILocation(line: 367, column: 12, scope: !931)
!933 = !DILocation(line: 367, column: 35, scope: !931)
!934 = !DILocation(line: 367, column: 40, scope: !931)
!935 = !DILocation(line: 368, column: 14, scope: !931)
!936 = !DILocation(line: 368, column: 7, scope: !931)
!937 = !DILocation(line: 368, column: 30, scope: !931)
!938 = !DILocation(line: 367, column: 12, scope: !939)
!939 = !DILexicalBlockFile(scope: !918, file: !1, discriminator: 1)
!940 = !DILocation(line: 370, column: 4, scope: !931)
!941 = !DILocation(line: 370, column: 9, scope: !931)
!942 = !DILocation(line: 370, column: 25, scope: !931)
!943 = !DILocation(line: 374, column: 19, scope: !944)
!944 = distinct !DILexicalBlock(scope: !931, file: !1, line: 374, column: 12)
!945 = !DILocation(line: 374, column: 12, scope: !944)
!946 = !DILocation(line: 374, column: 35, scope: !944)
!947 = !DILocation(line: 374, column: 40, scope: !944)
!948 = !DILocation(line: 375, column: 14, scope: !944)
!949 = !DILocation(line: 375, column: 7, scope: !944)
!950 = !DILocation(line: 375, column: 30, scope: !944)
!951 = !DILocation(line: 374, column: 12, scope: !952)
!952 = !DILexicalBlockFile(scope: !931, file: !1, discriminator: 1)
!953 = !DILocation(line: 377, column: 4, scope: !944)
!954 = !DILocation(line: 377, column: 9, scope: !944)
!955 = !DILocation(line: 377, column: 25, scope: !944)
!956 = !DILocation(line: 381, column: 19, scope: !957)
!957 = distinct !DILexicalBlock(scope: !944, file: !1, line: 381, column: 12)
!958 = !DILocation(line: 381, column: 12, scope: !957)
!959 = !DILocation(line: 381, column: 34, scope: !957)
!960 = !DILocation(line: 381, column: 39, scope: !957)
!961 = !DILocation(line: 382, column: 14, scope: !957)
!962 = !DILocation(line: 382, column: 7, scope: !957)
!963 = !DILocation(line: 382, column: 29, scope: !957)
!964 = !DILocation(line: 382, column: 34, scope: !957)
!965 = !DILocation(line: 383, column: 14, scope: !957)
!966 = !DILocation(line: 383, column: 7, scope: !957)
!967 = !DILocation(line: 383, column: 29, scope: !957)
!968 = !DILocation(line: 381, column: 12, scope: !969)
!969 = !DILexicalBlockFile(scope: !944, file: !1, discriminator: 1)
!970 = !DILocation(line: 384, column: 4, scope: !957)
!971 = !DILocation(line: 384, column: 9, scope: !957)
!972 = !DILocation(line: 384, column: 25, scope: !957)
!973 = !DILocation(line: 386, column: 24, scope: !974)
!974 = distinct !DILexicalBlock(scope: !957, file: !1, line: 385, column: 8)
!975 = !DILocation(line: 386, column: 27, scope: !974)
!976 = !DILocation(line: 389, column: 8, scope: !974)
!977 = !DILocation(line: 386, column: 4, scope: !974)
!978 = !DILocation(line: 390, column: 4, scope: !974)
!979 = !DILocation(line: 392, column: 7, scope: !980)
!980 = distinct !DILexicalBlock(scope: !878, file: !1, line: 392, column: 7)
!981 = !DILocation(line: 392, column: 12, scope: !980)
!982 = !DILocation(line: 392, column: 7, scope: !878)
!983 = !DILocation(line: 393, column: 24, scope: !984)
!984 = distinct !DILexicalBlock(scope: !980, file: !1, line: 392, column: 21)
!985 = !DILocation(line: 393, column: 27, scope: !984)
!986 = !DILocation(line: 397, column: 8, scope: !984)
!987 = !DILocation(line: 393, column: 4, scope: !984)
!988 = !DILocation(line: 398, column: 4, scope: !984)
!989 = !DILocation(line: 400, column: 3, scope: !878)
!990 = !DILocation(line: 402, column: 13, scope: !991)
!991 = distinct !DILexicalBlock(scope: !582, file: !1, line: 402, column: 6)
!992 = !DILocation(line: 402, column: 6, scope: !991)
!993 = !DILocation(line: 402, column: 39, scope: !991)
!994 = !DILocation(line: 402, column: 6, scope: !582)
!995 = !DILocation(line: 403, column: 7, scope: !996)
!996 = distinct !DILexicalBlock(scope: !997, file: !1, line: 403, column: 7)
!997 = distinct !DILexicalBlock(scope: !991, file: !1, line: 402, column: 45)
!998 = !DILocation(line: 403, column: 13, scope: !996)
!999 = !DILocation(line: 403, column: 21, scope: !996)
!1000 = !DILocation(line: 404, column: 9, scope: !996)
!1001 = !DILocation(line: 404, column: 18, scope: !996)
!1002 = !DILocation(line: 404, column: 25, scope: !996)
!1003 = !DILocation(line: 404, column: 28, scope: !1004)
!1004 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 1)
!1005 = !DILocation(line: 404, column: 37, scope: !1004)
!1006 = !DILocation(line: 404, column: 45, scope: !1004)
!1007 = !DILocation(line: 405, column: 7, scope: !996)
!1008 = !DILocation(line: 405, column: 16, scope: !996)
!1009 = !DILocation(line: 403, column: 7, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !997, file: !1, discriminator: 1)
!1011 = !DILocation(line: 406, column: 24, scope: !1012)
!1012 = distinct !DILexicalBlock(scope: !996, file: !1, line: 405, column: 25)
!1013 = !DILocation(line: 406, column: 27, scope: !1012)
!1014 = !DILocation(line: 409, column: 8, scope: !1012)
!1015 = !DILocation(line: 406, column: 4, scope: !1012)
!1016 = !DILocation(line: 410, column: 4, scope: !1012)
!1017 = !DILocation(line: 412, column: 32, scope: !997)
!1018 = !DILocation(line: 412, column: 41, scope: !997)
!1019 = !DILocation(line: 412, column: 3, scope: !997)
!1020 = !DILocation(line: 412, column: 8, scope: !997)
!1021 = !DILocation(line: 412, column: 30, scope: !997)
!1022 = !DILocation(line: 413, column: 3, scope: !997)
!1023 = !DILocation(line: 419, column: 2, scope: !582)
!1024 = !DILocation(line: 420, column: 1, scope: !582)
!1025 = !DILocalVariable(name: "a", arg: 1, scope: !583, file: !1, line: 423, type: !44)
!1026 = !DILocation(line: 423, column: 40, scope: !583)
!1027 = !DILocalVariable(name: "entry", arg: 2, scope: !583, file: !1, line: 423, type: !70)
!1028 = !DILocation(line: 423, column: 65, scope: !583)
!1029 = !DILocalVariable(name: "zip", scope: !583, file: !1, line: 425, type: !232)
!1030 = !DILocation(line: 425, column: 16, scope: !583)
!1031 = !DILocalVariable(name: "file", scope: !583, file: !1, line: 426, type: !239)
!1032 = !DILocation(line: 426, column: 15, scope: !583)
!1033 = !DILocalVariable(name: "r", scope: !583, file: !1, line: 427, type: !63)
!1034 = !DILocation(line: 427, column: 6, scope: !583)
!1035 = !DILocation(line: 429, column: 24, scope: !583)
!1036 = !DILocation(line: 429, column: 27, scope: !583)
!1037 = !DILocation(line: 429, column: 8, scope: !583)
!1038 = !DILocation(line: 429, column: 6, scope: !583)
!1039 = !DILocation(line: 430, column: 2, scope: !583)
!1040 = !DILocation(line: 430, column: 7, scope: !583)
!1041 = !DILocation(line: 430, column: 16, scope: !583)
!1042 = !DILocation(line: 431, column: 2, scope: !583)
!1043 = !DILocation(line: 431, column: 7, scope: !583)
!1044 = !DILocation(line: 431, column: 29, scope: !583)
!1045 = !DILocation(line: 433, column: 6, scope: !1046)
!1046 = distinct !DILexicalBlock(scope: !583, file: !1, line: 433, column: 6)
!1047 = !DILocation(line: 433, column: 11, scope: !1046)
!1048 = !DILocation(line: 433, column: 17, scope: !1046)
!1049 = !DILocation(line: 433, column: 6, scope: !583)
!1050 = !DILocation(line: 435, column: 8, scope: !1051)
!1051 = distinct !DILexicalBlock(scope: !1046, file: !1, line: 433, column: 26)
!1052 = !DILocation(line: 435, column: 11, scope: !1051)
!1053 = !DILocation(line: 434, column: 16, scope: !1051)
!1054 = !DILocation(line: 434, column: 3, scope: !1051)
!1055 = !DILocation(line: 434, column: 8, scope: !1051)
!1056 = !DILocation(line: 434, column: 14, scope: !1051)
!1057 = !DILocation(line: 436, column: 7, scope: !1058)
!1058 = distinct !DILexicalBlock(scope: !1051, file: !1, line: 436, column: 7)
!1059 = !DILocation(line: 436, column: 12, scope: !1058)
!1060 = !DILocation(line: 436, column: 18, scope: !1058)
!1061 = !DILocation(line: 436, column: 7, scope: !1051)
!1062 = !DILocation(line: 437, column: 4, scope: !1058)
!1063 = !DILocation(line: 438, column: 2, scope: !1051)
!1064 = !DILocation(line: 440, column: 15, scope: !583)
!1065 = !DILocation(line: 440, column: 18, scope: !583)
!1066 = !DILocation(line: 440, column: 6, scope: !583)
!1067 = !DILocation(line: 440, column: 4, scope: !583)
!1068 = !DILocation(line: 441, column: 6, scope: !1069)
!1069 = distinct !DILexicalBlock(scope: !583, file: !1, line: 441, column: 6)
!1070 = !DILocation(line: 441, column: 8, scope: !1069)
!1071 = !DILocation(line: 441, column: 6, scope: !583)
!1072 = !DILocation(line: 442, column: 13, scope: !1073)
!1073 = distinct !DILexicalBlock(scope: !1069, file: !1, line: 441, column: 24)
!1074 = !DILocation(line: 442, column: 3, scope: !1073)
!1075 = !DILocation(line: 443, column: 11, scope: !1073)
!1076 = !DILocation(line: 443, column: 3, scope: !1073)
!1077 = !DILocation(line: 445, column: 6, scope: !1078)
!1078 = distinct !DILexicalBlock(scope: !583, file: !1, line: 445, column: 6)
!1079 = !DILocation(line: 445, column: 12, scope: !1078)
!1080 = !DILocation(line: 445, column: 17, scope: !1078)
!1081 = !DILocation(line: 445, column: 22, scope: !1078)
!1082 = !DILocation(line: 445, column: 25, scope: !1083)
!1083 = !DILexicalBlockFile(scope: !1078, file: !1, discriminator: 1)
!1084 = !DILocation(line: 445, column: 31, scope: !1083)
!1085 = !DILocation(line: 445, column: 6, scope: !1083)
!1086 = !DILocation(line: 446, column: 40, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !1088, file: !1, line: 446, column: 7)
!1088 = distinct !DILexicalBlock(scope: !1078, file: !1, line: 445, column: 36)
!1089 = !DILocation(line: 446, column: 45, scope: !1087)
!1090 = !DILocation(line: 447, column: 33, scope: !1087)
!1091 = !DILocation(line: 447, column: 7, scope: !1087)
!1092 = !DILocation(line: 446, column: 8, scope: !1087)
!1093 = !DILocation(line: 446, column: 7, scope: !1088)
!1094 = !DILocation(line: 449, column: 14, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 447, column: 40)
!1096 = !DILocation(line: 449, column: 4, scope: !1095)
!1097 = !DILocation(line: 450, column: 4, scope: !1095)
!1098 = !DILocation(line: 452, column: 2, scope: !1088)
!1099 = !DILocation(line: 454, column: 6, scope: !1100)
!1100 = distinct !DILexicalBlock(scope: !583, file: !1, line: 454, column: 6)
!1101 = !DILocation(line: 454, column: 12, scope: !1100)
!1102 = !DILocation(line: 454, column: 16, scope: !1100)
!1103 = !DILocation(line: 454, column: 6, scope: !583)
!1104 = !DILocation(line: 455, column: 3, scope: !1100)
!1105 = !DILocation(line: 455, column: 8, scope: !1100)
!1106 = !DILocation(line: 455, column: 40, scope: !1100)
!1107 = !DILocation(line: 456, column: 6, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !583, file: !1, line: 456, column: 6)
!1109 = !DILocation(line: 456, column: 12, scope: !1108)
!1110 = !DILocation(line: 456, column: 16, scope: !1108)
!1111 = !DILocation(line: 456, column: 6, scope: !583)
!1112 = !DILocation(line: 457, column: 3, scope: !1108)
!1113 = !DILocation(line: 457, column: 8, scope: !1108)
!1114 = !DILocation(line: 457, column: 40, scope: !1108)
!1115 = !DILocation(line: 458, column: 6, scope: !1116)
!1116 = distinct !DILexicalBlock(scope: !583, file: !1, line: 458, column: 6)
!1117 = !DILocation(line: 458, column: 12, scope: !1116)
!1118 = !DILocation(line: 458, column: 16, scope: !1116)
!1119 = !DILocation(line: 458, column: 6, scope: !583)
!1120 = !DILocation(line: 459, column: 3, scope: !1116)
!1121 = !DILocation(line: 459, column: 8, scope: !1116)
!1122 = !DILocation(line: 459, column: 40, scope: !1116)
!1123 = !DILocation(line: 461, column: 2, scope: !583)
!1124 = !DILocation(line: 461, column: 7, scope: !583)
!1125 = !DILocation(line: 461, column: 25, scope: !583)
!1126 = !DILocation(line: 462, column: 33, scope: !583)
!1127 = !DILocation(line: 462, column: 39, scope: !583)
!1128 = !DILocation(line: 462, column: 48, scope: !583)
!1129 = !DILocation(line: 462, column: 2, scope: !583)
!1130 = !DILocation(line: 462, column: 7, scope: !583)
!1131 = !DILocation(line: 462, column: 30, scope: !583)
!1132 = !DILocation(line: 463, column: 6, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !583, file: !1, line: 463, column: 6)
!1134 = !DILocation(line: 463, column: 12, scope: !1133)
!1135 = !DILocation(line: 463, column: 17, scope: !1133)
!1136 = !DILocation(line: 463, column: 6, scope: !583)
!1137 = !DILocation(line: 465, column: 3, scope: !1138)
!1138 = distinct !DILexicalBlock(scope: !1133, file: !1, line: 463, column: 23)
!1139 = !DILocation(line: 465, column: 8, scope: !1138)
!1140 = !DILocation(line: 465, column: 32, scope: !1138)
!1141 = !DILocation(line: 466, column: 7, scope: !1142)
!1142 = distinct !DILexicalBlock(scope: !1138, file: !1, line: 466, column: 7)
!1143 = !DILocation(line: 466, column: 13, scope: !1142)
!1144 = !DILocation(line: 466, column: 7, scope: !1138)
!1145 = !DILocation(line: 467, column: 4, scope: !1142)
!1146 = !DILocation(line: 467, column: 9, scope: !1142)
!1147 = !DILocation(line: 467, column: 31, scope: !1142)
!1148 = !DILocation(line: 469, column: 24, scope: !1142)
!1149 = !DILocation(line: 469, column: 29, scope: !1142)
!1150 = !DILocation(line: 469, column: 4, scope: !1142)
!1151 = !DILocation(line: 470, column: 11, scope: !1138)
!1152 = !DILocation(line: 470, column: 3, scope: !1138)
!1153 = !DILocation(line: 476, column: 7, scope: !1154)
!1154 = distinct !DILexicalBlock(scope: !583, file: !1, line: 476, column: 6)
!1155 = !DILocation(line: 476, column: 12, scope: !1154)
!1156 = !DILocation(line: 476, column: 33, scope: !1154)
!1157 = !DILocation(line: 476, column: 38, scope: !1154)
!1158 = !DILocation(line: 476, column: 31, scope: !1154)
!1159 = !DILocation(line: 476, column: 64, scope: !1154)
!1160 = !DILocation(line: 476, column: 6, scope: !583)
!1161 = !DILocation(line: 477, column: 36, scope: !1162)
!1162 = distinct !DILexicalBlock(scope: !1154, file: !1, line: 476, column: 70)
!1163 = !DILocation(line: 477, column: 39, scope: !1162)
!1164 = !DILocation(line: 477, column: 44, scope: !1162)
!1165 = !DILocation(line: 478, column: 4, scope: !1162)
!1166 = !DILocation(line: 478, column: 9, scope: !1162)
!1167 = !DILocation(line: 477, column: 7, scope: !1162)
!1168 = !DILocation(line: 477, column: 5, scope: !1162)
!1169 = !DILocation(line: 479, column: 7, scope: !1170)
!1170 = distinct !DILexicalBlock(scope: !1162, file: !1, line: 479, column: 7)
!1171 = !DILocation(line: 479, column: 9, scope: !1170)
!1172 = !DILocation(line: 479, column: 7, scope: !1162)
!1173 = !DILocation(line: 480, column: 14, scope: !1174)
!1174 = distinct !DILexicalBlock(scope: !1170, file: !1, line: 479, column: 14)
!1175 = !DILocation(line: 480, column: 4, scope: !1174)
!1176 = !DILocation(line: 481, column: 4, scope: !1174)
!1177 = !DILocation(line: 483, column: 2, scope: !1162)
!1178 = !DILocation(line: 486, column: 16, scope: !583)
!1179 = !DILocation(line: 486, column: 21, scope: !583)
!1180 = !DILocation(line: 486, column: 2, scope: !583)
!1181 = !DILocation(line: 491, column: 18, scope: !583)
!1182 = !DILocation(line: 491, column: 2, scope: !583)
!1183 = !DILocation(line: 491, column: 7, scope: !583)
!1184 = !DILocation(line: 491, column: 16, scope: !583)
!1185 = !DILocation(line: 495, column: 31, scope: !583)
!1186 = !DILocation(line: 495, column: 37, scope: !583)
!1187 = !DILocation(line: 495, column: 2, scope: !583)
!1188 = !DILocation(line: 495, column: 7, scope: !583)
!1189 = !DILocation(line: 495, column: 29, scope: !583)
!1190 = !DILocation(line: 496, column: 2, scope: !583)
!1191 = !DILocation(line: 496, column: 7, scope: !583)
!1192 = !DILocation(line: 496, column: 19, scope: !583)
!1193 = !DILocation(line: 501, column: 29, scope: !1194)
!1194 = distinct !DILexicalBlock(scope: !583, file: !1, line: 501, column: 6)
!1195 = !DILocation(line: 501, column: 6, scope: !1194)
!1196 = !DILocation(line: 501, column: 36, scope: !1194)
!1197 = !DILocation(line: 501, column: 6, scope: !583)
!1198 = !DILocalVariable(name: "bytes", scope: !1199, file: !1, line: 502, type: !78)
!1199 = distinct !DILexicalBlock(scope: !1194, file: !1, line: 501, column: 49)
!1200 = !DILocation(line: 502, column: 11, scope: !1199)
!1201 = !DILocalVariable(name: "p", scope: !1199, file: !1, line: 503, type: !83)
!1202 = !DILocation(line: 503, column: 15, scope: !1199)
!1203 = !DILocation(line: 503, column: 55, scope: !1199)
!1204 = !DILocation(line: 503, column: 33, scope: !1199)
!1205 = !DILocation(line: 504, column: 24, scope: !1199)
!1206 = !DILocation(line: 504, column: 27, scope: !1199)
!1207 = !DILocation(line: 504, column: 38, scope: !1199)
!1208 = !DILocation(line: 504, column: 44, scope: !1199)
!1209 = !DILocation(line: 504, column: 11, scope: !1199)
!1210 = !DILocation(line: 504, column: 9, scope: !1199)
!1211 = !DILocation(line: 505, column: 7, scope: !1212)
!1212 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 505, column: 7)
!1213 = !DILocation(line: 505, column: 13, scope: !1212)
!1214 = !DILocation(line: 505, column: 7, scope: !1199)
!1215 = !DILocation(line: 506, column: 17, scope: !1212)
!1216 = !DILocation(line: 506, column: 12, scope: !1212)
!1217 = !DILocation(line: 506, column: 4, scope: !1212)
!1218 = !DILocation(line: 507, column: 28, scope: !1199)
!1219 = !DILocation(line: 507, column: 33, scope: !1199)
!1220 = !DILocation(line: 507, column: 46, scope: !1199)
!1221 = !DILocation(line: 507, column: 59, scope: !1199)
!1222 = !DILocation(line: 507, column: 49, scope: !1199)
!1223 = !DILocation(line: 507, column: 22, scope: !1199)
!1224 = !DILocation(line: 507, column: 3, scope: !1199)
!1225 = !DILocation(line: 507, column: 8, scope: !1199)
!1226 = !DILocation(line: 507, column: 20, scope: !1199)
!1227 = !DILocation(line: 508, column: 33, scope: !1199)
!1228 = !DILocation(line: 508, column: 3, scope: !1199)
!1229 = !DILocation(line: 508, column: 8, scope: !1199)
!1230 = !DILocation(line: 508, column: 30, scope: !1199)
!1231 = !DILocation(line: 509, column: 2, scope: !1199)
!1232 = !DILocation(line: 511, column: 10, scope: !583)
!1233 = !DILocation(line: 511, column: 2, scope: !583)
!1234 = !DILocation(line: 512, column: 1, scope: !583)
!1235 = !DILocalVariable(name: "a", arg: 1, scope: !639, file: !1, line: 602, type: !44)
!1236 = !DILocation(line: 602, column: 38, scope: !639)
!1237 = !DILocalVariable(name: "buff", arg: 2, scope: !639, file: !1, line: 602, type: !83)
!1238 = !DILocation(line: 602, column: 53, scope: !639)
!1239 = !DILocalVariable(name: "s", arg: 3, scope: !639, file: !1, line: 602, type: !85)
!1240 = !DILocation(line: 602, column: 66, scope: !639)
!1241 = !DILocalVariable(name: "zip", scope: !639, file: !1, line: 604, type: !232)
!1242 = !DILocation(line: 604, column: 16, scope: !639)
!1243 = !DILocalVariable(name: "bytes", scope: !639, file: !1, line: 605, type: !78)
!1244 = !DILocation(line: 605, column: 10, scope: !639)
!1245 = !DILocation(line: 607, column: 24, scope: !639)
!1246 = !DILocation(line: 607, column: 27, scope: !639)
!1247 = !DILocation(line: 607, column: 8, scope: !639)
!1248 = !DILocation(line: 607, column: 6, scope: !639)
!1249 = !DILocation(line: 609, column: 6, scope: !1250)
!1250 = distinct !DILexicalBlock(scope: !639, file: !1, line: 609, column: 6)
!1251 = !DILocation(line: 609, column: 10, scope: !1250)
!1252 = !DILocation(line: 609, column: 15, scope: !1250)
!1253 = !DILocation(line: 609, column: 8, scope: !1250)
!1254 = !DILocation(line: 609, column: 6, scope: !639)
!1255 = !DILocation(line: 610, column: 15, scope: !1250)
!1256 = !DILocation(line: 610, column: 20, scope: !1250)
!1257 = !DILocation(line: 610, column: 5, scope: !1250)
!1258 = !DILocation(line: 610, column: 3, scope: !1250)
!1259 = !DILocation(line: 611, column: 6, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !639, file: !1, line: 611, column: 6)
!1261 = !DILocation(line: 611, column: 8, scope: !1260)
!1262 = !DILocation(line: 611, column: 13, scope: !1260)
!1263 = !DILocation(line: 611, column: 16, scope: !1264)
!1264 = !DILexicalBlockFile(scope: !1260, file: !1, discriminator: 1)
!1265 = !DILocation(line: 611, column: 21, scope: !1264)
!1266 = !DILocation(line: 611, column: 30, scope: !1264)
!1267 = !DILocation(line: 611, column: 6, scope: !1264)
!1268 = !DILocation(line: 612, column: 3, scope: !1260)
!1269 = !DILocation(line: 613, column: 23, scope: !639)
!1270 = !DILocation(line: 613, column: 26, scope: !639)
!1271 = !DILocation(line: 613, column: 32, scope: !639)
!1272 = !DILocation(line: 613, column: 10, scope: !639)
!1273 = !DILocation(line: 613, column: 8, scope: !639)
!1274 = !DILocation(line: 614, column: 6, scope: !1275)
!1275 = distinct !DILexicalBlock(scope: !639, file: !1, line: 614, column: 6)
!1276 = !DILocation(line: 614, column: 12, scope: !1275)
!1277 = !DILocation(line: 614, column: 6, scope: !639)
!1278 = !DILocation(line: 615, column: 11, scope: !1275)
!1279 = !DILocation(line: 615, column: 3, scope: !1275)
!1280 = !DILocation(line: 616, column: 27, scope: !639)
!1281 = !DILocation(line: 616, column: 32, scope: !639)
!1282 = !DILocation(line: 616, column: 45, scope: !639)
!1283 = !DILocation(line: 616, column: 61, scope: !639)
!1284 = !DILocation(line: 616, column: 51, scope: !639)
!1285 = !DILocation(line: 616, column: 21, scope: !639)
!1286 = !DILocation(line: 616, column: 2, scope: !639)
!1287 = !DILocation(line: 616, column: 7, scope: !639)
!1288 = !DILocation(line: 616, column: 19, scope: !639)
!1289 = !DILocation(line: 617, column: 32, scope: !639)
!1290 = !DILocation(line: 617, column: 2, scope: !639)
!1291 = !DILocation(line: 617, column: 7, scope: !639)
!1292 = !DILocation(line: 617, column: 29, scope: !639)
!1293 = !DILocation(line: 618, column: 10, scope: !639)
!1294 = !DILocation(line: 618, column: 2, scope: !639)
!1295 = !DILocation(line: 619, column: 1, scope: !639)
!1296 = !DILocalVariable(name: "a", arg: 1, scope: !640, file: !1, line: 622, type: !44)
!1297 = !DILocation(line: 622, column: 40, scope: !640)
!1298 = !DILocalVariable(name: "zip", scope: !640, file: !1, line: 624, type: !232)
!1299 = !DILocation(line: 624, column: 16, scope: !640)
!1300 = !DILocalVariable(name: "s", scope: !640, file: !1, line: 625, type: !85)
!1301 = !DILocation(line: 625, column: 9, scope: !640)
!1302 = !DILocalVariable(name: "r", scope: !640, file: !1, line: 626, type: !78)
!1303 = !DILocation(line: 626, column: 10, scope: !640)
!1304 = !DILocation(line: 628, column: 24, scope: !640)
!1305 = !DILocation(line: 628, column: 27, scope: !640)
!1306 = !DILocation(line: 628, column: 8, scope: !640)
!1307 = !DILocation(line: 628, column: 6, scope: !640)
!1308 = !DILocation(line: 629, column: 6, scope: !1309)
!1309 = distinct !DILexicalBlock(scope: !640, file: !1, line: 629, column: 6)
!1310 = !DILocation(line: 629, column: 11, scope: !1309)
!1311 = !DILocation(line: 629, column: 20, scope: !1309)
!1312 = !DILocation(line: 629, column: 6, scope: !640)
!1313 = !DILocation(line: 630, column: 3, scope: !1309)
!1314 = !DILocation(line: 632, column: 2, scope: !640)
!1315 = !DILocation(line: 632, column: 9, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 1)
!1317 = !DILocation(line: 632, column: 14, scope: !1316)
!1318 = !DILocation(line: 632, column: 36, scope: !1316)
!1319 = !DILocation(line: 632, column: 2, scope: !1316)
!1320 = !DILocation(line: 633, column: 15, scope: !1321)
!1321 = distinct !DILexicalBlock(scope: !640, file: !1, line: 632, column: 41)
!1322 = !DILocation(line: 633, column: 20, scope: !1321)
!1323 = !DILocation(line: 633, column: 5, scope: !1321)
!1324 = !DILocation(line: 634, column: 7, scope: !1325)
!1325 = distinct !DILexicalBlock(scope: !1321, file: !1, line: 634, column: 7)
!1326 = !DILocation(line: 634, column: 11, scope: !1325)
!1327 = !DILocation(line: 634, column: 14, scope: !1325)
!1328 = !DILocation(line: 634, column: 9, scope: !1325)
!1329 = !DILocation(line: 634, column: 7, scope: !1321)
!1330 = !DILocation(line: 635, column: 8, scope: !1325)
!1331 = !DILocation(line: 635, column: 11, scope: !1325)
!1332 = !DILocation(line: 635, column: 6, scope: !1325)
!1333 = !DILocation(line: 635, column: 4, scope: !1325)
!1334 = !DILocation(line: 636, column: 22, scope: !1321)
!1335 = !DILocation(line: 636, column: 25, scope: !1321)
!1336 = !DILocation(line: 636, column: 28, scope: !1321)
!1337 = !DILocation(line: 636, column: 35, scope: !1321)
!1338 = !DILocation(line: 636, column: 7, scope: !1321)
!1339 = !DILocation(line: 636, column: 5, scope: !1321)
!1340 = !DILocation(line: 637, column: 7, scope: !1341)
!1341 = distinct !DILexicalBlock(scope: !1321, file: !1, line: 637, column: 7)
!1342 = !DILocation(line: 637, column: 9, scope: !1341)
!1343 = !DILocation(line: 637, column: 7, scope: !1321)
!1344 = !DILocation(line: 638, column: 17, scope: !1341)
!1345 = !DILocation(line: 638, column: 12, scope: !1341)
!1346 = !DILocation(line: 638, column: 4, scope: !1341)
!1347 = !DILocation(line: 632, column: 2, scope: !1348)
!1348 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 2)
!1349 = !DILocation(line: 640, column: 33, scope: !640)
!1350 = !DILocation(line: 640, column: 38, scope: !640)
!1351 = !DILocation(line: 640, column: 45, scope: !640)
!1352 = !DILocation(line: 640, column: 2, scope: !640)
!1353 = !DILocation(line: 640, column: 7, scope: !640)
!1354 = !DILocation(line: 640, column: 30, scope: !640)
!1355 = !DILocation(line: 641, column: 35, scope: !640)
!1356 = !DILocation(line: 641, column: 40, scope: !640)
!1357 = !DILocation(line: 641, column: 47, scope: !640)
!1358 = !DILocation(line: 641, column: 2, scope: !640)
!1359 = !DILocation(line: 641, column: 7, scope: !640)
!1360 = !DILocation(line: 641, column: 32, scope: !640)
!1361 = !DILocation(line: 642, column: 25, scope: !640)
!1362 = !DILocation(line: 642, column: 30, scope: !640)
!1363 = !DILocation(line: 642, column: 2, scope: !640)
!1364 = !DILocation(line: 642, column: 7, scope: !640)
!1365 = !DILocation(line: 642, column: 17, scope: !640)
!1366 = !DILocation(line: 642, column: 23, scope: !640)
!1367 = !DILocation(line: 643, column: 2, scope: !640)
!1368 = !DILocation(line: 643, column: 7, scope: !640)
!1369 = !DILocation(line: 643, column: 16, scope: !640)
!1370 = !DILocation(line: 645, column: 2, scope: !640)
!1371 = !DILocation(line: 646, column: 1, scope: !640)
!1372 = !DILocalVariable(name: "a", arg: 1, scope: !641, file: !1, line: 710, type: !44)
!1373 = !DILocation(line: 710, column: 33, scope: !641)
!1374 = !DILocalVariable(name: "zip", scope: !641, file: !1, line: 712, type: !232)
!1375 = !DILocation(line: 712, column: 16, scope: !641)
!1376 = !DILocalVariable(name: "wb", scope: !641, file: !1, line: 713, type: !420)
!1377 = !DILocation(line: 713, column: 17, scope: !641)
!1378 = !DILocalVariable(name: "header_offset", scope: !641, file: !1, line: 714, type: !237)
!1379 = !DILocation(line: 714, column: 11, scope: !641)
!1380 = !DILocalVariable(name: "header_size", scope: !641, file: !1, line: 714, type: !237)
!1381 = !DILocation(line: 714, column: 26, scope: !641)
!1382 = !DILocalVariable(name: "header_unpacksize", scope: !641, file: !1, line: 714, type: !237)
!1383 = !DILocation(line: 714, column: 39, scope: !641)
!1384 = !DILocalVariable(name: "length", scope: !641, file: !1, line: 715, type: !237)
!1385 = !DILocation(line: 715, column: 11, scope: !641)
!1386 = !DILocalVariable(name: "header_crc32", scope: !641, file: !1, line: 716, type: !275)
!1387 = !DILocation(line: 716, column: 11, scope: !641)
!1388 = !DILocalVariable(name: "r", scope: !641, file: !1, line: 717, type: !63)
!1389 = !DILocation(line: 717, column: 6, scope: !641)
!1390 = !DILocation(line: 719, column: 24, scope: !641)
!1391 = !DILocation(line: 719, column: 27, scope: !641)
!1392 = !DILocation(line: 719, column: 8, scope: !641)
!1393 = !DILocation(line: 719, column: 6, scope: !641)
!1394 = !DILocation(line: 721, column: 6, scope: !1395)
!1395 = distinct !DILexicalBlock(scope: !641, file: !1, line: 721, column: 6)
!1396 = !DILocation(line: 721, column: 11, scope: !1395)
!1397 = !DILocation(line: 721, column: 30, scope: !1395)
!1398 = !DILocation(line: 721, column: 6, scope: !641)
!1399 = !DILocalVariable(name: "n", scope: !1400, file: !1, line: 722, type: !248)
!1400 = distinct !DILexicalBlock(scope: !1395, file: !1, line: 721, column: 35)
!1401 = !DILocation(line: 722, column: 27, scope: !1400)
!1402 = !DILocalVariable(name: "data_offset", scope: !1400, file: !1, line: 723, type: !237)
!1403 = !DILocation(line: 723, column: 12, scope: !1400)
!1404 = !DILocalVariable(name: "data_size", scope: !1400, file: !1, line: 723, type: !237)
!1405 = !DILocation(line: 723, column: 25, scope: !1400)
!1406 = !DILocalVariable(name: "data_unpacksize", scope: !1400, file: !1, line: 723, type: !237)
!1407 = !DILocation(line: 723, column: 36, scope: !1400)
!1408 = !DILocalVariable(name: "header_compression", scope: !1400, file: !1, line: 724, type: !53)
!1409 = !DILocation(line: 724, column: 12, scope: !1400)
!1410 = !DILocation(line: 726, column: 25, scope: !1400)
!1411 = !DILocation(line: 726, column: 12, scope: !1400)
!1412 = !DILocation(line: 726, column: 7, scope: !1400)
!1413 = !DILocation(line: 726, column: 5, scope: !1400)
!1414 = !DILocation(line: 727, column: 7, scope: !1415)
!1415 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 727, column: 7)
!1416 = !DILocation(line: 727, column: 9, scope: !1415)
!1417 = !DILocation(line: 727, column: 7, scope: !1400)
!1418 = !DILocation(line: 728, column: 12, scope: !1415)
!1419 = !DILocation(line: 728, column: 4, scope: !1415)
!1420 = !DILocation(line: 729, column: 15, scope: !1400)
!1421 = !DILocation(line: 730, column: 15, scope: !1400)
!1422 = !DILocation(line: 730, column: 20, scope: !1400)
!1423 = !DILocation(line: 730, column: 27, scope: !1400)
!1424 = !DILocation(line: 730, column: 13, scope: !1400)
!1425 = !DILocation(line: 731, column: 21, scope: !1400)
!1426 = !DILocation(line: 731, column: 26, scope: !1400)
!1427 = !DILocation(line: 731, column: 33, scope: !1400)
!1428 = !DILocation(line: 731, column: 19, scope: !1400)
!1429 = !DILocation(line: 732, column: 22, scope: !1400)
!1430 = !DILocation(line: 732, column: 27, scope: !1400)
!1431 = !DILocation(line: 732, column: 3, scope: !1400)
!1432 = !DILocation(line: 732, column: 8, scope: !1400)
!1433 = !DILocation(line: 732, column: 14, scope: !1400)
!1434 = !DILocation(line: 732, column: 20, scope: !1400)
!1435 = !DILocation(line: 733, column: 26, scope: !1400)
!1436 = !DILocation(line: 733, column: 31, scope: !1400)
!1437 = !DILocation(line: 733, column: 38, scope: !1400)
!1438 = !DILocation(line: 733, column: 3, scope: !1400)
!1439 = !DILocation(line: 733, column: 8, scope: !1400)
!1440 = !DILocation(line: 733, column: 14, scope: !1400)
!1441 = !DILocation(line: 733, column: 24, scope: !1400)
!1442 = !DILocation(line: 734, column: 22, scope: !1400)
!1443 = !DILocation(line: 734, column: 27, scope: !1400)
!1444 = !DILocation(line: 734, column: 34, scope: !1400)
!1445 = !DILocation(line: 734, column: 3, scope: !1400)
!1446 = !DILocation(line: 734, column: 8, scope: !1400)
!1447 = !DILocation(line: 734, column: 14, scope: !1400)
!1448 = !DILocation(line: 734, column: 20, scope: !1400)
!1449 = !DILocation(line: 735, column: 3, scope: !1400)
!1450 = !DILocation(line: 735, column: 8, scope: !1400)
!1451 = !DILocation(line: 735, column: 15, scope: !1400)
!1452 = !DILocation(line: 735, column: 25, scope: !1400)
!1453 = !DILocation(line: 736, column: 3, scope: !1400)
!1454 = !DILocation(line: 736, column: 8, scope: !1400)
!1455 = !DILocation(line: 736, column: 15, scope: !1400)
!1456 = !DILocation(line: 736, column: 21, scope: !1400)
!1457 = !DILocation(line: 738, column: 7, scope: !1400)
!1458 = !DILocation(line: 738, column: 12, scope: !1400)
!1459 = !DILocation(line: 738, column: 33, scope: !1400)
!1460 = !DILocation(line: 738, column: 38, scope: !1400)
!1461 = !DILocation(line: 738, column: 31, scope: !1400)
!1462 = !DILocation(line: 737, column: 3, scope: !1400)
!1463 = !DILocation(line: 737, column: 8, scope: !1400)
!1464 = !DILocation(line: 737, column: 36, scope: !1400)
!1465 = !DILocation(line: 741, column: 7, scope: !1466)
!1466 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 741, column: 7)
!1467 = !DILocation(line: 741, column: 12, scope: !1466)
!1468 = !DILocation(line: 741, column: 23, scope: !1466)
!1469 = !DILocation(line: 741, column: 29, scope: !1466)
!1470 = !DILocation(line: 741, column: 7, scope: !1400)
!1471 = !DILocation(line: 742, column: 27, scope: !1472)
!1472 = distinct !DILexicalBlock(scope: !1466, file: !1, line: 741, column: 38)
!1473 = !DILocation(line: 742, column: 32, scope: !1472)
!1474 = !DILocation(line: 742, column: 43, scope: !1472)
!1475 = !DILocation(line: 742, column: 5, scope: !1472)
!1476 = !DILocation(line: 742, column: 10, scope: !1472)
!1477 = !DILocation(line: 742, column: 20, scope: !1472)
!1478 = !DILocation(line: 742, column: 25, scope: !1472)
!1479 = !DILocation(line: 743, column: 26, scope: !1472)
!1480 = !DILocation(line: 743, column: 31, scope: !1472)
!1481 = !DILocation(line: 743, column: 42, scope: !1472)
!1482 = !DILocation(line: 743, column: 4, scope: !1472)
!1483 = !DILocation(line: 743, column: 9, scope: !1472)
!1484 = !DILocation(line: 743, column: 19, scope: !1472)
!1485 = !DILocation(line: 743, column: 24, scope: !1472)
!1486 = !DILocation(line: 744, column: 3, scope: !1472)
!1487 = !DILocation(line: 746, column: 3, scope: !1488)
!1488 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 746, column: 3)
!1489 = !DILocation(line: 746, column: 3, scope: !1490)
!1490 = !DILexicalBlockFile(scope: !1491, file: !1, discriminator: 1)
!1491 = distinct !DILexicalBlock(scope: !1488, file: !1, line: 746, column: 3)
!1492 = !DILocation(line: 747, column: 18, scope: !1493)
!1493 = distinct !DILexicalBlock(scope: !1491, file: !1, line: 746, column: 46)
!1494 = !DILocation(line: 747, column: 38, scope: !1493)
!1495 = !DILocation(line: 747, column: 23, scope: !1493)
!1496 = !DILocation(line: 747, column: 4, scope: !1493)
!1497 = !DILocation(line: 748, column: 3, scope: !1493)
!1498 = !DILocation(line: 746, column: 3, scope: !1499)
!1499 = !DILexicalBlockFile(scope: !1491, file: !1, discriminator: 2)
!1500 = !DILocation(line: 755, column: 22, scope: !1400)
!1501 = !DILocation(line: 758, column: 7, scope: !1502)
!1502 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 758, column: 7)
!1503 = !DILocation(line: 758, column: 12, scope: !1502)
!1504 = !DILocation(line: 758, column: 31, scope: !1502)
!1505 = !DILocation(line: 758, column: 7, scope: !1400)
!1506 = !DILocation(line: 759, column: 23, scope: !1502)
!1507 = !DILocation(line: 759, column: 4, scope: !1502)
!1508 = !DILocation(line: 763, column: 36, scope: !1400)
!1509 = !DILocation(line: 763, column: 39, scope: !1400)
!1510 = !DILocation(line: 763, column: 7, scope: !1400)
!1511 = !DILocation(line: 763, column: 5, scope: !1400)
!1512 = !DILocation(line: 764, column: 7, scope: !1513)
!1513 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 764, column: 7)
!1514 = !DILocation(line: 764, column: 9, scope: !1513)
!1515 = !DILocation(line: 764, column: 7, scope: !1400)
!1516 = !DILocation(line: 765, column: 12, scope: !1513)
!1517 = !DILocation(line: 765, column: 4, scope: !1513)
!1518 = !DILocation(line: 766, column: 3, scope: !1400)
!1519 = !DILocation(line: 766, column: 8, scope: !1400)
!1520 = !DILocation(line: 766, column: 17, scope: !1400)
!1521 = !DILocation(line: 767, column: 3, scope: !1400)
!1522 = !DILocation(line: 767, column: 8, scope: !1400)
!1523 = !DILocation(line: 767, column: 22, scope: !1400)
!1524 = !DILocation(line: 768, column: 19, scope: !1400)
!1525 = !DILocation(line: 768, column: 22, scope: !1400)
!1526 = !DILocation(line: 768, column: 35, scope: !1400)
!1527 = !DILocation(line: 768, column: 46, scope: !1400)
!1528 = !DILocation(line: 769, column: 9, scope: !1400)
!1529 = !DILocation(line: 769, column: 14, scope: !1400)
!1530 = !DILocation(line: 768, column: 7, scope: !1400)
!1531 = !DILocation(line: 768, column: 5, scope: !1400)
!1532 = !DILocation(line: 770, column: 7, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 770, column: 7)
!1534 = !DILocation(line: 770, column: 9, scope: !1533)
!1535 = !DILocation(line: 770, column: 7, scope: !1400)
!1536 = !DILocation(line: 771, column: 12, scope: !1533)
!1537 = !DILocation(line: 771, column: 4, scope: !1533)
!1538 = !DILocation(line: 772, column: 25, scope: !1400)
!1539 = !DILocation(line: 772, column: 12, scope: !1400)
!1540 = !DILocation(line: 772, column: 7, scope: !1400)
!1541 = !DILocation(line: 772, column: 5, scope: !1400)
!1542 = !DILocation(line: 773, column: 7, scope: !1543)
!1543 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 773, column: 7)
!1544 = !DILocation(line: 773, column: 9, scope: !1543)
!1545 = !DILocation(line: 773, column: 7, scope: !1400)
!1546 = !DILocation(line: 774, column: 12, scope: !1543)
!1547 = !DILocation(line: 774, column: 4, scope: !1543)
!1548 = !DILocation(line: 775, column: 19, scope: !1400)
!1549 = !DILocation(line: 775, column: 33, scope: !1400)
!1550 = !DILocation(line: 775, column: 31, scope: !1400)
!1551 = !DILocation(line: 775, column: 17, scope: !1400)
!1552 = !DILocation(line: 776, column: 17, scope: !1400)
!1553 = !DILocation(line: 776, column: 22, scope: !1400)
!1554 = !DILocation(line: 776, column: 29, scope: !1400)
!1555 = !DILocation(line: 776, column: 15, scope: !1400)
!1556 = !DILocation(line: 777, column: 18, scope: !1400)
!1557 = !DILocation(line: 777, column: 23, scope: !1400)
!1558 = !DILocation(line: 777, column: 16, scope: !1400)
!1559 = !DILocation(line: 778, column: 23, scope: !1400)
!1560 = !DILocation(line: 778, column: 28, scope: !1400)
!1561 = !DILocation(line: 778, column: 35, scope: !1400)
!1562 = !DILocation(line: 778, column: 21, scope: !1400)
!1563 = !DILocation(line: 780, column: 7, scope: !1564)
!1564 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 780, column: 7)
!1565 = !DILocation(line: 780, column: 26, scope: !1564)
!1566 = !DILocation(line: 780, column: 7, scope: !1400)
!1567 = !DILocation(line: 785, column: 9, scope: !1568)
!1568 = distinct !DILexicalBlock(scope: !1564, file: !1, line: 780, column: 39)
!1569 = !DILocation(line: 785, column: 14, scope: !1568)
!1570 = !DILocation(line: 785, column: 20, scope: !1568)
!1571 = !DILocation(line: 785, column: 4, scope: !1568)
!1572 = !DILocation(line: 786, column: 23, scope: !1568)
!1573 = !DILocation(line: 786, column: 4, scope: !1568)
!1574 = !DILocation(line: 786, column: 9, scope: !1568)
!1575 = !DILocation(line: 786, column: 15, scope: !1568)
!1576 = !DILocation(line: 786, column: 21, scope: !1568)
!1577 = !DILocation(line: 787, column: 27, scope: !1568)
!1578 = !DILocation(line: 787, column: 32, scope: !1568)
!1579 = !DILocation(line: 787, column: 39, scope: !1568)
!1580 = !DILocation(line: 787, column: 4, scope: !1568)
!1581 = !DILocation(line: 787, column: 9, scope: !1568)
!1582 = !DILocation(line: 787, column: 15, scope: !1568)
!1583 = !DILocation(line: 787, column: 25, scope: !1568)
!1584 = !DILocation(line: 788, column: 23, scope: !1568)
!1585 = !DILocation(line: 788, column: 28, scope: !1568)
!1586 = !DILocation(line: 788, column: 35, scope: !1568)
!1587 = !DILocation(line: 788, column: 4, scope: !1568)
!1588 = !DILocation(line: 788, column: 9, scope: !1568)
!1589 = !DILocation(line: 788, column: 15, scope: !1568)
!1590 = !DILocation(line: 788, column: 21, scope: !1568)
!1591 = !DILocation(line: 789, column: 4, scope: !1568)
!1592 = !DILocation(line: 789, column: 9, scope: !1568)
!1593 = !DILocation(line: 789, column: 16, scope: !1568)
!1594 = !DILocation(line: 789, column: 26, scope: !1568)
!1595 = !DILocation(line: 790, column: 4, scope: !1568)
!1596 = !DILocation(line: 790, column: 9, scope: !1568)
!1597 = !DILocation(line: 790, column: 16, scope: !1568)
!1598 = !DILocation(line: 790, column: 22, scope: !1568)
!1599 = !DILocation(line: 792, column: 37, scope: !1568)
!1600 = !DILocation(line: 792, column: 8, scope: !1568)
!1601 = !DILocation(line: 792, column: 6, scope: !1568)
!1602 = !DILocation(line: 793, column: 8, scope: !1603)
!1603 = distinct !DILexicalBlock(scope: !1568, file: !1, line: 793, column: 8)
!1604 = !DILocation(line: 793, column: 10, scope: !1603)
!1605 = !DILocation(line: 793, column: 8, scope: !1568)
!1606 = !DILocation(line: 794, column: 13, scope: !1603)
!1607 = !DILocation(line: 794, column: 5, scope: !1603)
!1608 = !DILocation(line: 795, column: 4, scope: !1568)
!1609 = !DILocation(line: 795, column: 9, scope: !1568)
!1610 = !DILocation(line: 795, column: 18, scope: !1568)
!1611 = !DILocation(line: 796, column: 4, scope: !1568)
!1612 = !DILocation(line: 796, column: 9, scope: !1568)
!1613 = !DILocation(line: 796, column: 23, scope: !1568)
!1614 = !DILocation(line: 801, column: 19, scope: !1568)
!1615 = !DILocation(line: 801, column: 8, scope: !1568)
!1616 = !DILocation(line: 801, column: 6, scope: !1568)
!1617 = !DILocation(line: 802, column: 8, scope: !1618)
!1618 = distinct !DILexicalBlock(scope: !1568, file: !1, line: 802, column: 8)
!1619 = !DILocation(line: 802, column: 10, scope: !1618)
!1620 = !DILocation(line: 802, column: 8, scope: !1568)
!1621 = !DILocation(line: 803, column: 13, scope: !1618)
!1622 = !DILocation(line: 803, column: 5, scope: !1618)
!1623 = !DILocation(line: 804, column: 25, scope: !1568)
!1624 = !DILocation(line: 804, column: 28, scope: !1568)
!1625 = !DILocation(line: 804, column: 43, scope: !1568)
!1626 = !DILocation(line: 805, column: 10, scope: !1568)
!1627 = !DILocation(line: 805, column: 34, scope: !1568)
!1628 = !DILocation(line: 805, column: 39, scope: !1568)
!1629 = !DILocation(line: 806, column: 10, scope: !1568)
!1630 = !DILocation(line: 804, column: 8, scope: !1568)
!1631 = !DILocation(line: 804, column: 6, scope: !1568)
!1632 = !DILocation(line: 807, column: 8, scope: !1633)
!1633 = distinct !DILexicalBlock(scope: !1568, file: !1, line: 807, column: 8)
!1634 = !DILocation(line: 807, column: 10, scope: !1633)
!1635 = !DILocation(line: 807, column: 8, scope: !1568)
!1636 = !DILocation(line: 808, column: 13, scope: !1633)
!1637 = !DILocation(line: 808, column: 5, scope: !1633)
!1638 = !DILocation(line: 809, column: 26, scope: !1568)
!1639 = !DILocation(line: 809, column: 13, scope: !1568)
!1640 = !DILocation(line: 809, column: 8, scope: !1568)
!1641 = !DILocation(line: 809, column: 6, scope: !1568)
!1642 = !DILocation(line: 810, column: 8, scope: !1643)
!1643 = distinct !DILexicalBlock(scope: !1568, file: !1, line: 810, column: 8)
!1644 = !DILocation(line: 810, column: 10, scope: !1643)
!1645 = !DILocation(line: 810, column: 8, scope: !1568)
!1646 = !DILocation(line: 811, column: 13, scope: !1643)
!1647 = !DILocation(line: 811, column: 5, scope: !1643)
!1648 = !DILocation(line: 812, column: 20, scope: !1568)
!1649 = !DILocation(line: 812, column: 36, scope: !1568)
!1650 = !DILocation(line: 812, column: 34, scope: !1568)
!1651 = !DILocation(line: 812, column: 18, scope: !1568)
!1652 = !DILocation(line: 813, column: 18, scope: !1568)
!1653 = !DILocation(line: 813, column: 23, scope: !1568)
!1654 = !DILocation(line: 813, column: 30, scope: !1568)
!1655 = !DILocation(line: 813, column: 16, scope: !1568)
!1656 = !DILocation(line: 814, column: 19, scope: !1568)
!1657 = !DILocation(line: 814, column: 24, scope: !1568)
!1658 = !DILocation(line: 814, column: 17, scope: !1568)
!1659 = !DILocation(line: 815, column: 3, scope: !1568)
!1660 = !DILocation(line: 816, column: 3, scope: !1400)
!1661 = !DILocation(line: 816, column: 8, scope: !1400)
!1662 = !DILocation(line: 816, column: 17, scope: !1400)
!1663 = !DILocation(line: 817, column: 2, scope: !1400)
!1664 = !DILocation(line: 818, column: 31, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !1395, file: !1, line: 817, column: 9)
!1666 = !DILocation(line: 818, column: 17, scope: !1665)
!1667 = !DILocation(line: 819, column: 16, scope: !1665)
!1668 = !DILocation(line: 822, column: 11, scope: !641)
!1669 = !DILocation(line: 822, column: 16, scope: !641)
!1670 = !DILocation(line: 822, column: 9, scope: !641)
!1671 = !DILocation(line: 827, column: 7, scope: !641)
!1672 = !DILocation(line: 827, column: 12, scope: !641)
!1673 = !DILocation(line: 827, column: 5, scope: !641)
!1674 = !DILocation(line: 828, column: 2, scope: !641)
!1675 = !DILocation(line: 828, column: 7, scope: !641)
!1676 = !DILocation(line: 828, column: 23, scope: !641)
!1677 = !DILocation(line: 829, column: 10, scope: !641)
!1678 = !DILocation(line: 829, column: 2, scope: !641)
!1679 = !DILocation(line: 830, column: 2, scope: !641)
!1680 = !DILocation(line: 830, column: 8, scope: !641)
!1681 = !DILocation(line: 831, column: 2, scope: !641)
!1682 = !DILocation(line: 831, column: 8, scope: !641)
!1683 = !DILocation(line: 832, column: 19, scope: !641)
!1684 = !DILocation(line: 832, column: 27, scope: !641)
!1685 = !DILocation(line: 832, column: 2, scope: !641)
!1686 = !DILocation(line: 833, column: 19, scope: !641)
!1687 = !DILocation(line: 833, column: 27, scope: !641)
!1688 = !DILocation(line: 833, column: 2, scope: !641)
!1689 = !DILocation(line: 834, column: 19, scope: !641)
!1690 = !DILocation(line: 834, column: 27, scope: !641)
!1691 = !DILocation(line: 834, column: 2, scope: !641)
!1692 = !DILocation(line: 835, column: 19, scope: !641)
!1693 = !DILocation(line: 835, column: 36, scope: !641)
!1694 = !DILocation(line: 835, column: 26, scope: !641)
!1695 = !DILocation(line: 835, column: 2, scope: !1696)
!1696 = !DILexicalBlockFile(scope: !641, file: !1, discriminator: 1)
!1697 = !DILocation(line: 836, column: 2, scope: !641)
!1698 = !DILocation(line: 836, column: 7, scope: !641)
!1699 = !DILocation(line: 836, column: 23, scope: !641)
!1700 = !DILocation(line: 842, column: 15, scope: !641)
!1701 = !DILocation(line: 842, column: 21, scope: !641)
!1702 = !DILocation(line: 842, column: 6, scope: !641)
!1703 = !DILocation(line: 842, column: 4, scope: !641)
!1704 = !DILocation(line: 843, column: 6, scope: !1705)
!1705 = distinct !DILexicalBlock(scope: !641, file: !1, line: 843, column: 6)
!1706 = !DILocation(line: 843, column: 8, scope: !1705)
!1707 = !DILocation(line: 843, column: 6, scope: !641)
!1708 = !DILocation(line: 844, column: 11, scope: !1705)
!1709 = !DILocation(line: 844, column: 3, scope: !1705)
!1710 = !DILocation(line: 845, column: 18, scope: !641)
!1711 = !DILocation(line: 845, column: 6, scope: !641)
!1712 = !DILocation(line: 845, column: 4, scope: !641)
!1713 = !DILocation(line: 846, column: 10, scope: !641)
!1714 = !DILocation(line: 846, column: 2, scope: !641)
!1715 = !DILocation(line: 847, column: 1, scope: !641)
!1716 = !DILocalVariable(name: "a", arg: 1, scope: !670, file: !1, line: 1449, type: !44)
!1717 = !DILocation(line: 1449, column: 32, scope: !670)
!1718 = !DILocalVariable(name: "zip", scope: !670, file: !1, line: 1451, type: !232)
!1719 = !DILocation(line: 1451, column: 16, scope: !670)
!1720 = !DILocation(line: 1451, column: 38, scope: !670)
!1721 = !DILocation(line: 1451, column: 41, scope: !670)
!1722 = !DILocation(line: 1451, column: 22, scope: !670)
!1723 = !DILocation(line: 1454, column: 6, scope: !1724)
!1724 = distinct !DILexicalBlock(scope: !670, file: !1, line: 1454, column: 6)
!1725 = !DILocation(line: 1454, column: 11, scope: !1724)
!1726 = !DILocation(line: 1454, column: 19, scope: !1724)
!1727 = !DILocation(line: 1454, column: 6, scope: !670)
!1728 = !DILocation(line: 1455, column: 9, scope: !1724)
!1729 = !DILocation(line: 1455, column: 14, scope: !1724)
!1730 = !DILocation(line: 1455, column: 3, scope: !1724)
!1731 = !DILocation(line: 1457, column: 21, scope: !670)
!1732 = !DILocation(line: 1457, column: 2, scope: !670)
!1733 = !DILocation(line: 1458, column: 20, scope: !670)
!1734 = !DILocation(line: 1458, column: 23, scope: !670)
!1735 = !DILocation(line: 1458, column: 35, scope: !670)
!1736 = !DILocation(line: 1458, column: 40, scope: !670)
!1737 = !DILocation(line: 1458, column: 2, scope: !670)
!1738 = !DILocation(line: 1459, column: 7, scope: !670)
!1739 = !DILocation(line: 1459, column: 12, scope: !670)
!1740 = !DILocation(line: 1459, column: 18, scope: !670)
!1741 = !DILocation(line: 1459, column: 2, scope: !670)
!1742 = !DILocation(line: 1460, column: 7, scope: !670)
!1743 = !DILocation(line: 1460, column: 2, scope: !670)
!1744 = !DILocation(line: 1462, column: 2, scope: !670)
!1745 = !DILocalVariable(name: "a", arg: 1, scope: !584, file: !1, line: 1486, type: !44)
!1746 = !DILocation(line: 1486, column: 32, scope: !584)
!1747 = !DILocalVariable(name: "entry", arg: 2, scope: !584, file: !1, line: 1486, type: !70)
!1748 = !DILocation(line: 1486, column: 57, scope: !584)
!1749 = !DILocalVariable(name: "newfile", arg: 3, scope: !584, file: !1, line: 1487, type: !334)
!1750 = !DILocation(line: 1487, column: 19, scope: !584)
!1751 = !DILocalVariable(name: "zip", scope: !584, file: !1, line: 1489, type: !232)
!1752 = !DILocation(line: 1489, column: 16, scope: !584)
!1753 = !DILocalVariable(name: "file", scope: !584, file: !1, line: 1490, type: !239)
!1754 = !DILocation(line: 1490, column: 15, scope: !584)
!1755 = !DILocalVariable(name: "u16", scope: !584, file: !1, line: 1491, type: !120)
!1756 = !DILocation(line: 1491, column: 14, scope: !584)
!1757 = !DILocalVariable(name: "u16len", scope: !584, file: !1, line: 1492, type: !85)
!1758 = !DILocation(line: 1492, column: 9, scope: !584)
!1759 = !DILocalVariable(name: "ret", scope: !584, file: !1, line: 1493, type: !63)
!1760 = !DILocation(line: 1493, column: 6, scope: !584)
!1761 = !DILocation(line: 1495, column: 24, scope: !584)
!1762 = !DILocation(line: 1495, column: 27, scope: !584)
!1763 = !DILocation(line: 1495, column: 8, scope: !584)
!1764 = !DILocation(line: 1495, column: 6, scope: !584)
!1765 = !DILocation(line: 1496, column: 3, scope: !584)
!1766 = !DILocation(line: 1496, column: 11, scope: !584)
!1767 = !DILocation(line: 1498, column: 9, scope: !584)
!1768 = !DILocation(line: 1498, column: 7, scope: !584)
!1769 = !DILocation(line: 1499, column: 6, scope: !1770)
!1770 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1499, column: 6)
!1771 = !DILocation(line: 1499, column: 11, scope: !1770)
!1772 = !DILocation(line: 1499, column: 6, scope: !584)
!1773 = !DILocation(line: 1500, column: 22, scope: !1774)
!1774 = distinct !DILexicalBlock(scope: !1770, file: !1, line: 1499, column: 20)
!1775 = !DILocation(line: 1500, column: 25, scope: !1774)
!1776 = !DILocation(line: 1500, column: 3, scope: !1774)
!1777 = !DILocation(line: 1502, column: 3, scope: !1774)
!1778 = !DILocation(line: 1505, column: 35, scope: !1779)
!1779 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1505, column: 6)
!1780 = !DILocation(line: 1505, column: 57, scope: !1779)
!1781 = !DILocation(line: 1505, column: 62, scope: !1779)
!1782 = !DILocation(line: 1505, column: 10, scope: !1779)
!1783 = !DILocation(line: 1505, column: 8, scope: !1779)
!1784 = !DILocation(line: 1505, column: 6, scope: !584)
!1785 = !DILocation(line: 1506, column: 7, scope: !1786)
!1786 = distinct !DILexicalBlock(scope: !1787, file: !1, line: 1506, column: 7)
!1787 = distinct !DILexicalBlock(scope: !1779, file: !1, line: 1505, column: 70)
!1788 = !DILocation(line: 1506, column: 13, scope: !1786)
!1789 = !DILocation(line: 1506, column: 7, scope: !1787)
!1790 = !DILocation(line: 1507, column: 9, scope: !1791)
!1791 = distinct !DILexicalBlock(scope: !1786, file: !1, line: 1506, column: 24)
!1792 = !DILocation(line: 1507, column: 4, scope: !1791)
!1793 = !DILocation(line: 1508, column: 23, scope: !1791)
!1794 = !DILocation(line: 1508, column: 26, scope: !1791)
!1795 = !DILocation(line: 1508, column: 4, scope: !1791)
!1796 = !DILocation(line: 1510, column: 4, scope: !1791)
!1797 = !DILocation(line: 1512, column: 22, scope: !1787)
!1798 = !DILocation(line: 1512, column: 25, scope: !1787)
!1799 = !DILocation(line: 1512, column: 3, scope: !1787)
!1800 = !DILocation(line: 1515, column: 7, scope: !1787)
!1801 = !DILocation(line: 1516, column: 2, scope: !1787)
!1802 = !DILocation(line: 1517, column: 27, scope: !584)
!1803 = !DILocation(line: 1517, column: 34, scope: !584)
!1804 = !DILocation(line: 1517, column: 20, scope: !584)
!1805 = !DILocation(line: 1517, column: 2, scope: !584)
!1806 = !DILocation(line: 1517, column: 8, scope: !584)
!1807 = !DILocation(line: 1517, column: 18, scope: !584)
!1808 = !DILocation(line: 1518, column: 6, scope: !1809)
!1809 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1518, column: 6)
!1810 = !DILocation(line: 1518, column: 12, scope: !1809)
!1811 = !DILocation(line: 1518, column: 22, scope: !1809)
!1812 = !DILocation(line: 1518, column: 6, scope: !584)
!1813 = !DILocation(line: 1519, column: 8, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !1809, file: !1, line: 1518, column: 31)
!1815 = !DILocation(line: 1519, column: 3, scope: !1814)
!1816 = !DILocation(line: 1520, column: 22, scope: !1814)
!1817 = !DILocation(line: 1520, column: 25, scope: !1814)
!1818 = !DILocation(line: 1520, column: 3, scope: !1814)
!1819 = !DILocation(line: 1522, column: 3, scope: !1814)
!1820 = !DILocation(line: 1524, column: 9, scope: !584)
!1821 = !DILocation(line: 1524, column: 15, scope: !584)
!1822 = !DILocation(line: 1524, column: 26, scope: !584)
!1823 = !DILocation(line: 1524, column: 31, scope: !584)
!1824 = !DILocation(line: 1524, column: 2, scope: !584)
!1825 = !DILocation(line: 1525, column: 18, scope: !584)
!1826 = !DILocation(line: 1525, column: 24, scope: !584)
!1827 = !DILocation(line: 1525, column: 2, scope: !584)
!1828 = !DILocation(line: 1525, column: 8, scope: !584)
!1829 = !DILocation(line: 1525, column: 28, scope: !584)
!1830 = !DILocation(line: 1526, column: 18, scope: !584)
!1831 = !DILocation(line: 1526, column: 24, scope: !584)
!1832 = !DILocation(line: 1526, column: 2, scope: !584)
!1833 = !DILocation(line: 1526, column: 8, scope: !584)
!1834 = !DILocation(line: 1526, column: 28, scope: !584)
!1835 = !DILocation(line: 1527, column: 29, scope: !584)
!1836 = !DILocation(line: 1527, column: 19, scope: !584)
!1837 = !DILocation(line: 1527, column: 2, scope: !584)
!1838 = !DILocation(line: 1527, column: 8, scope: !584)
!1839 = !DILocation(line: 1527, column: 17, scope: !584)
!1840 = !DILocation(line: 1528, column: 34, scope: !584)
!1841 = !DILocation(line: 1528, column: 15, scope: !584)
!1842 = !DILocation(line: 1528, column: 2, scope: !584)
!1843 = !DILocation(line: 1528, column: 8, scope: !584)
!1844 = !DILocation(line: 1528, column: 13, scope: !584)
!1845 = !DILocation(line: 1529, column: 29, scope: !1846)
!1846 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1529, column: 6)
!1847 = !DILocation(line: 1529, column: 6, scope: !1846)
!1848 = !DILocation(line: 1529, column: 36, scope: !1846)
!1849 = !DILocation(line: 1529, column: 6, scope: !584)
!1850 = !DILocation(line: 1530, column: 35, scope: !1846)
!1851 = !DILocation(line: 1530, column: 16, scope: !1846)
!1852 = !DILocation(line: 1530, column: 3, scope: !1846)
!1853 = !DILocation(line: 1530, column: 9, scope: !1846)
!1854 = !DILocation(line: 1530, column: 14, scope: !1846)
!1855 = !DILocation(line: 1532, column: 26, scope: !1846)
!1856 = !DILocation(line: 1532, column: 3, scope: !1846)
!1857 = !DILocation(line: 1533, column: 29, scope: !1858)
!1858 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1533, column: 6)
!1859 = !DILocation(line: 1533, column: 6, scope: !1858)
!1860 = !DILocation(line: 1533, column: 36, scope: !1858)
!1861 = !DILocation(line: 1533, column: 6, scope: !584)
!1862 = !DILocation(line: 1534, column: 3, scope: !1858)
!1863 = !DILocation(line: 1534, column: 9, scope: !1858)
!1864 = !DILocation(line: 1534, column: 13, scope: !1858)
!1865 = !DILocation(line: 1535, column: 34, scope: !1866)
!1866 = distinct !DILexicalBlock(scope: !1858, file: !1, line: 1535, column: 11)
!1867 = !DILocation(line: 1535, column: 11, scope: !1866)
!1868 = !DILocation(line: 1535, column: 41, scope: !1866)
!1869 = !DILocation(line: 1535, column: 11, scope: !1858)
!1870 = !DILocation(line: 1536, column: 45, scope: !1866)
!1871 = !DILocation(line: 1536, column: 23, scope: !1866)
!1872 = !DILocation(line: 1536, column: 16, scope: !1873)
!1873 = !DILexicalBlockFile(scope: !1866, file: !1, discriminator: 1)
!1874 = !DILocation(line: 1536, column: 3, scope: !1866)
!1875 = !DILocation(line: 1536, column: 9, scope: !1866)
!1876 = !DILocation(line: 1536, column: 14, scope: !1866)
!1877 = !DILocation(line: 1537, column: 33, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1537, column: 6)
!1879 = !DILocation(line: 1537, column: 6, scope: !1878)
!1880 = !DILocation(line: 1537, column: 6, scope: !584)
!1881 = !DILocation(line: 1538, column: 3, scope: !1882)
!1882 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 1537, column: 41)
!1883 = !DILocation(line: 1538, column: 9, scope: !1882)
!1884 = !DILocation(line: 1538, column: 13, scope: !1882)
!1885 = !DILocation(line: 1539, column: 49, scope: !1882)
!1886 = !DILocation(line: 1539, column: 29, scope: !1882)
!1887 = !DILocation(line: 1539, column: 3, scope: !1882)
!1888 = !DILocation(line: 1539, column: 9, scope: !1882)
!1889 = !DILocation(line: 1539, column: 22, scope: !1882)
!1890 = !DILocation(line: 1539, column: 27, scope: !1882)
!1891 = !DILocation(line: 1540, column: 57, scope: !1882)
!1892 = !DILocation(line: 1540, column: 32, scope: !1882)
!1893 = !DILocation(line: 1540, column: 3, scope: !1882)
!1894 = !DILocation(line: 1540, column: 9, scope: !1882)
!1895 = !DILocation(line: 1540, column: 22, scope: !1882)
!1896 = !DILocation(line: 1540, column: 30, scope: !1882)
!1897 = !DILocation(line: 1541, column: 2, scope: !1882)
!1898 = !DILocation(line: 1542, column: 33, scope: !1899)
!1899 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1542, column: 6)
!1900 = !DILocation(line: 1542, column: 6, scope: !1899)
!1901 = !DILocation(line: 1542, column: 6, scope: !584)
!1902 = !DILocation(line: 1543, column: 3, scope: !1903)
!1903 = distinct !DILexicalBlock(scope: !1899, file: !1, line: 1542, column: 41)
!1904 = !DILocation(line: 1543, column: 9, scope: !1903)
!1905 = !DILocation(line: 1543, column: 13, scope: !1903)
!1906 = !DILocation(line: 1544, column: 49, scope: !1903)
!1907 = !DILocation(line: 1544, column: 29, scope: !1903)
!1908 = !DILocation(line: 1544, column: 3, scope: !1903)
!1909 = !DILocation(line: 1544, column: 9, scope: !1903)
!1910 = !DILocation(line: 1544, column: 22, scope: !1903)
!1911 = !DILocation(line: 1544, column: 27, scope: !1903)
!1912 = !DILocation(line: 1545, column: 57, scope: !1903)
!1913 = !DILocation(line: 1545, column: 32, scope: !1903)
!1914 = !DILocation(line: 1545, column: 3, scope: !1903)
!1915 = !DILocation(line: 1545, column: 9, scope: !1903)
!1916 = !DILocation(line: 1545, column: 22, scope: !1903)
!1917 = !DILocation(line: 1545, column: 30, scope: !1903)
!1918 = !DILocation(line: 1546, column: 2, scope: !1903)
!1919 = !DILocation(line: 1547, column: 33, scope: !1920)
!1920 = distinct !DILexicalBlock(scope: !584, file: !1, line: 1547, column: 6)
!1921 = !DILocation(line: 1547, column: 6, scope: !1920)
!1922 = !DILocation(line: 1547, column: 6, scope: !584)
!1923 = !DILocation(line: 1548, column: 3, scope: !1924)
!1924 = distinct !DILexicalBlock(scope: !1920, file: !1, line: 1547, column: 41)
!1925 = !DILocation(line: 1548, column: 9, scope: !1924)
!1926 = !DILocation(line: 1548, column: 13, scope: !1924)
!1927 = !DILocation(line: 1549, column: 49, scope: !1924)
!1928 = !DILocation(line: 1549, column: 29, scope: !1924)
!1929 = !DILocation(line: 1549, column: 3, scope: !1924)
!1930 = !DILocation(line: 1549, column: 9, scope: !1924)
!1931 = !DILocation(line: 1549, column: 22, scope: !1924)
!1932 = !DILocation(line: 1549, column: 27, scope: !1924)
!1933 = !DILocation(line: 1550, column: 57, scope: !1924)
!1934 = !DILocation(line: 1550, column: 32, scope: !1924)
!1935 = !DILocation(line: 1550, column: 3, scope: !1924)
!1936 = !DILocation(line: 1550, column: 9, scope: !1924)
!1937 = !DILocation(line: 1550, column: 22, scope: !1924)
!1938 = !DILocation(line: 1550, column: 30, scope: !1924)
!1939 = !DILocation(line: 1551, column: 2, scope: !1924)
!1940 = !DILocation(line: 1553, column: 13, scope: !584)
!1941 = !DILocation(line: 1553, column: 3, scope: !584)
!1942 = !DILocation(line: 1553, column: 11, scope: !584)
!1943 = !DILocation(line: 1554, column: 10, scope: !584)
!1944 = !DILocation(line: 1554, column: 2, scope: !584)
!1945 = !DILocation(line: 1555, column: 1, scope: !584)
!1946 = !DILocalVariable(name: "file", arg: 1, scope: !587, file: !1, line: 1558, type: !239)
!1947 = !DILocation(line: 1558, column: 24, scope: !587)
!1948 = !DILocation(line: 1560, column: 7, scope: !587)
!1949 = !DILocation(line: 1560, column: 13, scope: !587)
!1950 = !DILocation(line: 1560, column: 2, scope: !587)
!1951 = !DILocation(line: 1561, column: 7, scope: !587)
!1952 = !DILocation(line: 1561, column: 2, scope: !587)
!1953 = !DILocation(line: 1562, column: 1, scope: !587)
!1954 = !DILocalVariable(name: "zip", arg: 1, scope: !590, file: !1, line: 1593, type: !232)
!1955 = !DILocation(line: 1593, column: 35, scope: !590)
!1956 = !DILocalVariable(name: "file", arg: 2, scope: !590, file: !1, line: 1593, type: !239)
!1957 = !DILocation(line: 1593, column: 53, scope: !590)
!1958 = !DILocation(line: 1595, column: 2, scope: !590)
!1959 = !DILocation(line: 1595, column: 8, scope: !590)
!1960 = !DILocation(line: 1595, column: 13, scope: !590)
!1961 = !DILocation(line: 1596, column: 26, scope: !590)
!1962 = !DILocation(line: 1596, column: 3, scope: !590)
!1963 = !DILocation(line: 1596, column: 8, scope: !590)
!1964 = !DILocation(line: 1596, column: 19, scope: !590)
!1965 = !DILocation(line: 1596, column: 24, scope: !590)
!1966 = !DILocation(line: 1597, column: 27, scope: !590)
!1967 = !DILocation(line: 1597, column: 33, scope: !590)
!1968 = !DILocation(line: 1597, column: 2, scope: !590)
!1969 = !DILocation(line: 1597, column: 7, scope: !590)
!1970 = !DILocation(line: 1597, column: 18, scope: !590)
!1971 = !DILocation(line: 1597, column: 23, scope: !590)
!1972 = !DILocation(line: 1598, column: 1, scope: !590)
!1973 = !DILocalVariable(name: "a", arg: 1, scope: !593, file: !1, line: 2258, type: !44)
!1974 = !DILocation(line: 2258, column: 52, scope: !593)
!1975 = !DILocalVariable(name: "compression", arg: 2, scope: !593, file: !1, line: 2258, type: !53)
!1976 = !DILocation(line: 2258, column: 64, scope: !593)
!1977 = !DILocalVariable(name: "compression_level", arg: 3, scope: !593, file: !1, line: 2259, type: !63)
!1978 = !DILocation(line: 2259, column: 9, scope: !593)
!1979 = !DILocalVariable(name: "zip", scope: !593, file: !1, line: 2261, type: !232)
!1980 = !DILocation(line: 2261, column: 16, scope: !593)
!1981 = !DILocalVariable(name: "r", scope: !593, file: !1, line: 2262, type: !63)
!1982 = !DILocation(line: 2262, column: 6, scope: !593)
!1983 = !DILocation(line: 2264, column: 24, scope: !593)
!1984 = !DILocation(line: 2264, column: 27, scope: !593)
!1985 = !DILocation(line: 2264, column: 8, scope: !593)
!1986 = !DILocation(line: 2264, column: 6, scope: !593)
!1987 = !DILocation(line: 2265, column: 10, scope: !593)
!1988 = !DILocation(line: 2265, column: 2, scope: !593)
!1989 = !DILocation(line: 2268, column: 9, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !593, file: !1, line: 2265, column: 23)
!1991 = !DILocation(line: 2268, column: 12, scope: !1990)
!1992 = !DILocation(line: 2268, column: 24, scope: !1990)
!1993 = !DILocation(line: 2268, column: 29, scope: !1990)
!1994 = !DILocation(line: 2269, column: 7, scope: !1990)
!1995 = !DILocation(line: 2267, column: 7, scope: !1990)
!1996 = !DILocation(line: 2267, column: 5, scope: !1990)
!1997 = !DILocation(line: 2270, column: 3, scope: !1990)
!1998 = !DILocation(line: 2273, column: 9, scope: !1990)
!1999 = !DILocation(line: 2273, column: 12, scope: !1990)
!2000 = !DILocation(line: 2273, column: 24, scope: !1990)
!2001 = !DILocation(line: 2273, column: 29, scope: !1990)
!2002 = !DILocation(line: 2274, column: 7, scope: !1990)
!2003 = !DILocation(line: 2272, column: 7, scope: !1990)
!2004 = !DILocation(line: 2272, column: 5, scope: !1990)
!2005 = !DILocation(line: 2275, column: 3, scope: !1990)
!2006 = !DILocation(line: 2278, column: 9, scope: !1990)
!2007 = !DILocation(line: 2278, column: 12, scope: !1990)
!2008 = !DILocation(line: 2278, column: 24, scope: !1990)
!2009 = !DILocation(line: 2278, column: 29, scope: !1990)
!2010 = !DILocation(line: 2279, column: 7, scope: !1990)
!2011 = !DILocation(line: 2277, column: 7, scope: !1990)
!2012 = !DILocation(line: 2277, column: 5, scope: !1990)
!2013 = !DILocation(line: 2280, column: 3, scope: !1990)
!2014 = !DILocation(line: 2283, column: 9, scope: !1990)
!2015 = !DILocation(line: 2283, column: 12, scope: !1990)
!2016 = !DILocation(line: 2283, column: 24, scope: !1990)
!2017 = !DILocation(line: 2283, column: 29, scope: !1990)
!2018 = !DILocation(line: 2284, column: 7, scope: !1990)
!2019 = !DILocation(line: 2282, column: 7, scope: !1990)
!2020 = !DILocation(line: 2282, column: 5, scope: !1990)
!2021 = !DILocation(line: 2285, column: 3, scope: !1990)
!2022 = !DILocation(line: 2288, column: 9, scope: !1990)
!2023 = !DILocation(line: 2288, column: 12, scope: !1990)
!2024 = !DILocation(line: 2288, column: 24, scope: !1990)
!2025 = !DILocation(line: 2288, column: 29, scope: !1990)
!2026 = !DILocation(line: 2287, column: 7, scope: !1990)
!2027 = !DILocation(line: 2287, column: 5, scope: !1990)
!2028 = !DILocation(line: 2290, column: 3, scope: !1990)
!2029 = !DILocation(line: 2290, column: 3, scope: !2030)
!2030 = !DILexicalBlockFile(scope: !1990, file: !1, discriminator: 1)
!2031 = !DILocation(line: 2294, column: 9, scope: !1990)
!2032 = !DILocation(line: 2294, column: 12, scope: !1990)
!2033 = !DILocation(line: 2294, column: 24, scope: !1990)
!2034 = !DILocation(line: 2294, column: 29, scope: !1990)
!2035 = !DILocation(line: 2293, column: 7, scope: !1990)
!2036 = !DILocation(line: 2293, column: 5, scope: !1990)
!2037 = !DILocation(line: 2295, column: 3, scope: !1990)
!2038 = !DILocation(line: 2297, column: 6, scope: !2039)
!2039 = distinct !DILexicalBlock(scope: !593, file: !1, line: 2297, column: 6)
!2040 = !DILocation(line: 2297, column: 8, scope: !2039)
!2041 = !DILocation(line: 2297, column: 6, scope: !593)
!2042 = !DILocation(line: 2298, column: 3, scope: !2043)
!2043 = distinct !DILexicalBlock(scope: !2039, file: !1, line: 2297, column: 23)
!2044 = !DILocation(line: 2298, column: 8, scope: !2043)
!2045 = !DILocation(line: 2298, column: 15, scope: !2043)
!2046 = !DILocation(line: 2298, column: 24, scope: !2043)
!2047 = !DILocation(line: 2299, column: 26, scope: !2043)
!2048 = !DILocation(line: 2299, column: 31, scope: !2043)
!2049 = !DILocation(line: 2299, column: 3, scope: !2043)
!2050 = !DILocation(line: 2299, column: 8, scope: !2043)
!2051 = !DILocation(line: 2299, column: 15, scope: !2043)
!2052 = !DILocation(line: 2299, column: 24, scope: !2043)
!2053 = !DILocation(line: 2300, column: 3, scope: !2043)
!2054 = !DILocation(line: 2300, column: 8, scope: !2043)
!2055 = !DILocation(line: 2300, column: 15, scope: !2043)
!2056 = !DILocation(line: 2300, column: 25, scope: !2043)
!2057 = !DILocation(line: 2301, column: 3, scope: !2043)
!2058 = !DILocation(line: 2301, column: 8, scope: !2043)
!2059 = !DILocation(line: 2301, column: 15, scope: !2043)
!2060 = !DILocation(line: 2301, column: 25, scope: !2043)
!2061 = !DILocation(line: 2302, column: 2, scope: !2043)
!2062 = !DILocation(line: 2304, column: 10, scope: !593)
!2063 = !DILocation(line: 2304, column: 2, scope: !593)
!2064 = !DILocalVariable(name: "zip", arg: 1, scope: !631, file: !1, line: 1565, type: !232)
!2065 = !DILocation(line: 1565, column: 29, scope: !631)
!2066 = !DILocalVariable(name: "file", arg: 2, scope: !631, file: !1, line: 1565, type: !239)
!2067 = !DILocation(line: 1565, column: 47, scope: !631)
!2068 = !DILocation(line: 1567, column: 2, scope: !631)
!2069 = !DILocation(line: 1567, column: 8, scope: !631)
!2070 = !DILocation(line: 1567, column: 13, scope: !631)
!2071 = !DILocation(line: 1568, column: 25, scope: !631)
!2072 = !DILocation(line: 1568, column: 3, scope: !631)
!2073 = !DILocation(line: 1568, column: 8, scope: !631)
!2074 = !DILocation(line: 1568, column: 18, scope: !631)
!2075 = !DILocation(line: 1568, column: 23, scope: !631)
!2076 = !DILocation(line: 1569, column: 26, scope: !631)
!2077 = !DILocation(line: 1569, column: 32, scope: !631)
!2078 = !DILocation(line: 1569, column: 2, scope: !631)
!2079 = !DILocation(line: 1569, column: 7, scope: !631)
!2080 = !DILocation(line: 1569, column: 17, scope: !631)
!2081 = !DILocation(line: 1569, column: 22, scope: !631)
!2082 = !DILocation(line: 1570, column: 1, scope: !631)
!2083 = !DILocalVariable(name: "a", arg: 1, scope: !632, file: !1, line: 555, type: !44)
!2084 = !DILocation(line: 555, column: 36, scope: !632)
!2085 = !DILocalVariable(name: "buff", arg: 2, scope: !632, file: !1, line: 555, type: !83)
!2086 = !DILocation(line: 555, column: 51, scope: !632)
!2087 = !DILocalVariable(name: "s", arg: 3, scope: !632, file: !1, line: 555, type: !85)
!2088 = !DILocation(line: 555, column: 64, scope: !632)
!2089 = !DILocalVariable(name: "run", arg: 4, scope: !632, file: !1, line: 556, type: !3)
!2090 = !DILocation(line: 556, column: 21, scope: !632)
!2091 = !DILocalVariable(name: "zip", scope: !632, file: !1, line: 558, type: !232)
!2092 = !DILocation(line: 558, column: 16, scope: !632)
!2093 = !DILocation(line: 558, column: 38, scope: !632)
!2094 = !DILocation(line: 558, column: 41, scope: !632)
!2095 = !DILocation(line: 558, column: 22, scope: !632)
!2096 = !DILocalVariable(name: "r", scope: !632, file: !1, line: 559, type: !63)
!2097 = !DILocation(line: 559, column: 6, scope: !632)
!2098 = !DILocation(line: 561, column: 6, scope: !2099)
!2099 = distinct !DILexicalBlock(scope: !632, file: !1, line: 561, column: 6)
!2100 = !DILocation(line: 561, column: 10, scope: !2099)
!2101 = !DILocation(line: 561, column: 30, scope: !2099)
!2102 = !DILocation(line: 561, column: 33, scope: !2103)
!2103 = !DILexicalBlockFile(scope: !2099, file: !1, discriminator: 1)
!2104 = !DILocation(line: 561, column: 38, scope: !2103)
!2105 = !DILocation(line: 561, column: 45, scope: !2103)
!2106 = !DILocation(line: 561, column: 54, scope: !2103)
!2107 = !DILocation(line: 561, column: 59, scope: !2103)
!2108 = !DILocation(line: 561, column: 62, scope: !2109)
!2109 = !DILexicalBlockFile(scope: !2099, file: !1, discriminator: 2)
!2110 = !DILocation(line: 561, column: 64, scope: !2109)
!2111 = !DILocation(line: 561, column: 6, scope: !2109)
!2112 = !DILocation(line: 562, column: 3, scope: !2099)
!2113 = !DILocation(line: 564, column: 7, scope: !2114)
!2114 = distinct !DILexicalBlock(scope: !632, file: !1, line: 564, column: 6)
!2115 = !DILocation(line: 564, column: 12, scope: !2114)
!2116 = !DILocation(line: 564, column: 21, scope: !2114)
!2117 = !DILocation(line: 564, column: 38, scope: !2114)
!2118 = !DILocation(line: 564, column: 41, scope: !2119)
!2119 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 1)
!2120 = !DILocation(line: 564, column: 6, scope: !2119)
!2121 = !DILocation(line: 565, column: 30, scope: !2114)
!2122 = !DILocation(line: 565, column: 35, scope: !2114)
!2123 = !DILocation(line: 565, column: 50, scope: !2114)
!2124 = !DILocation(line: 566, column: 17, scope: !2114)
!2125 = !DILocation(line: 566, column: 7, scope: !2114)
!2126 = !DILocation(line: 565, column: 24, scope: !2114)
!2127 = !DILocation(line: 565, column: 3, scope: !2114)
!2128 = !DILocation(line: 565, column: 8, scope: !2114)
!2129 = !DILocation(line: 565, column: 22, scope: !2114)
!2130 = !DILocation(line: 567, column: 47, scope: !632)
!2131 = !DILocation(line: 567, column: 2, scope: !632)
!2132 = !DILocation(line: 567, column: 7, scope: !632)
!2133 = !DILocation(line: 567, column: 14, scope: !632)
!2134 = !DILocation(line: 567, column: 22, scope: !632)
!2135 = !DILocation(line: 568, column: 25, scope: !632)
!2136 = !DILocation(line: 568, column: 2, scope: !632)
!2137 = !DILocation(line: 568, column: 7, scope: !632)
!2138 = !DILocation(line: 568, column: 14, scope: !632)
!2139 = !DILocation(line: 568, column: 23, scope: !632)
!2140 = !DILocation(line: 569, column: 2, scope: !632)
!2141 = !DILocation(line: 571, column: 26, scope: !2142)
!2142 = distinct !DILexicalBlock(scope: !2143, file: !1, line: 569, column: 11)
!2143 = distinct !DILexicalBlock(scope: !2144, file: !1, line: 569, column: 2)
!2144 = distinct !DILexicalBlock(scope: !632, file: !1, line: 569, column: 2)
!2145 = !DILocation(line: 571, column: 29, scope: !2142)
!2146 = !DILocation(line: 571, column: 41, scope: !2142)
!2147 = !DILocation(line: 571, column: 46, scope: !2142)
!2148 = !DILocation(line: 571, column: 55, scope: !2142)
!2149 = !DILocation(line: 571, column: 7, scope: !2142)
!2150 = !DILocation(line: 571, column: 5, scope: !2142)
!2151 = !DILocation(line: 572, column: 7, scope: !2152)
!2152 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 572, column: 7)
!2153 = !DILocation(line: 572, column: 9, scope: !2152)
!2154 = !DILocation(line: 572, column: 23, scope: !2152)
!2155 = !DILocation(line: 572, column: 26, scope: !2156)
!2156 = !DILexicalBlockFile(scope: !2152, file: !1, discriminator: 1)
!2157 = !DILocation(line: 572, column: 28, scope: !2156)
!2158 = !DILocation(line: 572, column: 7, scope: !2156)
!2159 = !DILocation(line: 573, column: 4, scope: !2152)
!2160 = !DILocation(line: 574, column: 7, scope: !2161)
!2161 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 574, column: 7)
!2162 = !DILocation(line: 574, column: 12, scope: !2161)
!2163 = !DILocation(line: 574, column: 19, scope: !2161)
!2164 = !DILocation(line: 574, column: 29, scope: !2161)
!2165 = !DILocation(line: 574, column: 7, scope: !2142)
!2166 = !DILocation(line: 575, column: 22, scope: !2167)
!2167 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 575, column: 8)
!2168 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 574, column: 35)
!2169 = !DILocation(line: 575, column: 25, scope: !2167)
!2170 = !DILocation(line: 575, column: 30, scope: !2167)
!2171 = !DILocation(line: 575, column: 8, scope: !2167)
!2172 = !DILocation(line: 576, column: 8, scope: !2167)
!2173 = !DILocation(line: 575, column: 8, scope: !2168)
!2174 = !DILocation(line: 577, column: 5, scope: !2167)
!2175 = !DILocation(line: 578, column: 27, scope: !2168)
!2176 = !DILocation(line: 578, column: 32, scope: !2168)
!2177 = !DILocation(line: 578, column: 4, scope: !2168)
!2178 = !DILocation(line: 578, column: 9, scope: !2168)
!2179 = !DILocation(line: 578, column: 16, scope: !2168)
!2180 = !DILocation(line: 578, column: 25, scope: !2168)
!2181 = !DILocation(line: 579, column: 4, scope: !2168)
!2182 = !DILocation(line: 579, column: 9, scope: !2168)
!2183 = !DILocation(line: 579, column: 16, scope: !2168)
!2184 = !DILocation(line: 579, column: 26, scope: !2168)
!2185 = !DILocation(line: 580, column: 8, scope: !2186)
!2186 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 580, column: 8)
!2187 = !DILocation(line: 580, column: 13, scope: !2186)
!2188 = !DILocation(line: 580, column: 22, scope: !2186)
!2189 = !DILocation(line: 580, column: 8, scope: !2168)
!2190 = !DILocation(line: 581, column: 32, scope: !2186)
!2191 = !DILocation(line: 581, column: 37, scope: !2186)
!2192 = !DILocation(line: 582, column: 9, scope: !2186)
!2193 = !DILocation(line: 582, column: 14, scope: !2186)
!2194 = !DILocation(line: 581, column: 26, scope: !2186)
!2195 = !DILocation(line: 581, column: 5, scope: !2186)
!2196 = !DILocation(line: 581, column: 10, scope: !2186)
!2197 = !DILocation(line: 581, column: 24, scope: !2186)
!2198 = !DILocation(line: 583, column: 8, scope: !2199)
!2199 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 583, column: 8)
!2200 = !DILocation(line: 583, column: 12, scope: !2199)
!2201 = !DILocation(line: 583, column: 32, scope: !2199)
!2202 = !DILocation(line: 583, column: 35, scope: !2203)
!2203 = !DILexicalBlockFile(scope: !2199, file: !1, discriminator: 1)
!2204 = !DILocation(line: 583, column: 37, scope: !2203)
!2205 = !DILocation(line: 583, column: 8, scope: !2203)
!2206 = !DILocation(line: 584, column: 5, scope: !2199)
!2207 = !DILocation(line: 585, column: 3, scope: !2168)
!2208 = !DILocation(line: 586, column: 7, scope: !2209)
!2209 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 586, column: 7)
!2210 = !DILocation(line: 586, column: 12, scope: !2209)
!2211 = !DILocation(line: 586, column: 19, scope: !2209)
!2212 = !DILocation(line: 586, column: 28, scope: !2209)
!2213 = !DILocation(line: 586, column: 7, scope: !2142)
!2214 = !DILocation(line: 587, column: 4, scope: !2209)
!2215 = !DILocation(line: 569, column: 2, scope: !2216)
!2216 = !DILexicalBlockFile(scope: !2143, file: !1, discriminator: 1)
!2217 = !DILocation(line: 589, column: 6, scope: !2218)
!2218 = distinct !DILexicalBlock(scope: !632, file: !1, line: 589, column: 6)
!2219 = !DILocation(line: 589, column: 10, scope: !2218)
!2220 = !DILocation(line: 589, column: 6, scope: !632)
!2221 = !DILocalVariable(name: "bytes", scope: !2222, file: !1, line: 590, type: !237)
!2222 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 589, column: 31)
!2223 = !DILocation(line: 590, column: 12, scope: !2222)
!2224 = !DILocation(line: 590, column: 41, scope: !2222)
!2225 = !DILocation(line: 590, column: 46, scope: !2222)
!2226 = !DILocation(line: 590, column: 53, scope: !2222)
!2227 = !DILocation(line: 590, column: 39, scope: !2222)
!2228 = !DILocation(line: 591, column: 21, scope: !2229)
!2229 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 591, column: 7)
!2230 = !DILocation(line: 591, column: 24, scope: !2229)
!2231 = !DILocation(line: 591, column: 29, scope: !2229)
!2232 = !DILocation(line: 591, column: 44, scope: !2229)
!2233 = !DILocation(line: 591, column: 7, scope: !2229)
!2234 = !DILocation(line: 591, column: 51, scope: !2229)
!2235 = !DILocation(line: 591, column: 7, scope: !2222)
!2236 = !DILocation(line: 592, column: 4, scope: !2229)
!2237 = !DILocation(line: 593, column: 8, scope: !2238)
!2238 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 593, column: 7)
!2239 = !DILocation(line: 593, column: 13, scope: !2238)
!2240 = !DILocation(line: 593, column: 22, scope: !2238)
!2241 = !DILocation(line: 593, column: 39, scope: !2238)
!2242 = !DILocation(line: 593, column: 42, scope: !2243)
!2243 = !DILexicalBlockFile(scope: !2238, file: !1, discriminator: 1)
!2244 = !DILocation(line: 593, column: 7, scope: !2243)
!2245 = !DILocation(line: 594, column: 31, scope: !2238)
!2246 = !DILocation(line: 594, column: 36, scope: !2238)
!2247 = !DILocation(line: 595, column: 8, scope: !2238)
!2248 = !DILocation(line: 595, column: 13, scope: !2238)
!2249 = !DILocation(line: 595, column: 30, scope: !2238)
!2250 = !DILocation(line: 595, column: 20, scope: !2238)
!2251 = !DILocation(line: 594, column: 25, scope: !2238)
!2252 = !DILocation(line: 594, column: 4, scope: !2238)
!2253 = !DILocation(line: 594, column: 9, scope: !2238)
!2254 = !DILocation(line: 594, column: 23, scope: !2238)
!2255 = !DILocation(line: 596, column: 2, scope: !2222)
!2256 = !DILocation(line: 598, column: 10, scope: !632)
!2257 = !DILocation(line: 598, column: 2, scope: !632)
!2258 = !DILocation(line: 599, column: 1, scope: !632)
!2259 = !DILocalVariable(name: "a", arg: 1, scope: !596, file: !1, line: 1675, type: !64)
!2260 = !DILocation(line: 1675, column: 50, scope: !596)
!2261 = !DILocalVariable(name: "lastrm", arg: 2, scope: !596, file: !1, line: 1676, type: !312)
!2262 = !DILocation(line: 1676, column: 24, scope: !596)
!2263 = !DILocalVariable(name: "level", arg: 3, scope: !596, file: !1, line: 1676, type: !63)
!2264 = !DILocation(line: 1676, column: 36, scope: !596)
!2265 = !DILocalVariable(name: "withheader", arg: 4, scope: !596, file: !1, line: 1676, type: !63)
!2266 = !DILocation(line: 1676, column: 47, scope: !596)
!2267 = !DILocalVariable(name: "strm", scope: !596, file: !1, line: 1678, type: !365)
!2268 = !DILocation(line: 1678, column: 12, scope: !596)
!2269 = !DILocation(line: 1680, column: 6, scope: !2270)
!2270 = distinct !DILexicalBlock(scope: !596, file: !1, line: 1680, column: 6)
!2271 = !DILocation(line: 1680, column: 14, scope: !2270)
!2272 = !DILocation(line: 1680, column: 6, scope: !596)
!2273 = !DILocation(line: 1681, column: 19, scope: !2270)
!2274 = !DILocation(line: 1681, column: 22, scope: !2270)
!2275 = !DILocation(line: 1681, column: 3, scope: !2270)
!2276 = !DILocation(line: 1682, column: 9, scope: !596)
!2277 = !DILocation(line: 1682, column: 7, scope: !596)
!2278 = !DILocation(line: 1683, column: 6, scope: !2279)
!2279 = distinct !DILexicalBlock(scope: !596, file: !1, line: 1683, column: 6)
!2280 = !DILocation(line: 1683, column: 11, scope: !2279)
!2281 = !DILocation(line: 1683, column: 6, scope: !596)
!2282 = !DILocation(line: 1684, column: 21, scope: !2283)
!2283 = distinct !DILexicalBlock(scope: !2279, file: !1, line: 1683, column: 20)
!2284 = !DILocation(line: 1684, column: 3, scope: !2283)
!2285 = !DILocation(line: 1686, column: 3, scope: !2283)
!2286 = !DILocation(line: 1691, column: 52, scope: !596)
!2287 = !DILocation(line: 1691, column: 60, scope: !596)
!2288 = !DILocation(line: 1691, column: 27, scope: !596)
!2289 = !DILocation(line: 1691, column: 18, scope: !596)
!2290 = !DILocation(line: 1691, column: 2, scope: !596)
!2291 = !DILocation(line: 1691, column: 8, scope: !596)
!2292 = !DILocation(line: 1691, column: 16, scope: !596)
!2293 = !DILocation(line: 1692, column: 25, scope: !596)
!2294 = !DILocation(line: 1692, column: 33, scope: !596)
!2295 = !DILocation(line: 1692, column: 19, scope: !596)
!2296 = !DILocation(line: 1692, column: 2, scope: !596)
!2297 = !DILocation(line: 1692, column: 8, scope: !596)
!2298 = !DILocation(line: 1692, column: 17, scope: !596)
!2299 = !DILocation(line: 1693, column: 26, scope: !596)
!2300 = !DILocation(line: 1693, column: 34, scope: !596)
!2301 = !DILocation(line: 1693, column: 2, scope: !596)
!2302 = !DILocation(line: 1693, column: 8, scope: !596)
!2303 = !DILocation(line: 1693, column: 17, scope: !596)
!2304 = !DILocation(line: 1694, column: 19, scope: !596)
!2305 = !DILocation(line: 1694, column: 27, scope: !596)
!2306 = !DILocation(line: 1694, column: 2, scope: !596)
!2307 = !DILocation(line: 1694, column: 8, scope: !596)
!2308 = !DILocation(line: 1694, column: 17, scope: !596)
!2309 = !DILocation(line: 1695, column: 26, scope: !596)
!2310 = !DILocation(line: 1695, column: 34, scope: !596)
!2311 = !DILocation(line: 1695, column: 20, scope: !596)
!2312 = !DILocation(line: 1695, column: 2, scope: !596)
!2313 = !DILocation(line: 1695, column: 8, scope: !596)
!2314 = !DILocation(line: 1695, column: 18, scope: !596)
!2315 = !DILocation(line: 1696, column: 27, scope: !596)
!2316 = !DILocation(line: 1696, column: 35, scope: !596)
!2317 = !DILocation(line: 1696, column: 2, scope: !596)
!2318 = !DILocation(line: 1696, column: 8, scope: !596)
!2319 = !DILocation(line: 1696, column: 18, scope: !596)
!2320 = !DILocation(line: 1697, column: 6, scope: !2321)
!2321 = distinct !DILexicalBlock(scope: !596, file: !1, line: 1697, column: 6)
!2322 = !DILocation(line: 1699, column: 29, scope: !2321)
!2323 = !DILocation(line: 1697, column: 6, scope: !596)
!2324 = !DILocation(line: 1700, column: 8, scope: !2325)
!2325 = distinct !DILexicalBlock(scope: !2321, file: !1, line: 1699, column: 38)
!2326 = !DILocation(line: 1700, column: 3, scope: !2325)
!2327 = !DILocation(line: 1701, column: 3, scope: !2325)
!2328 = !DILocation(line: 1701, column: 11, scope: !2325)
!2329 = !DILocation(line: 1701, column: 23, scope: !2325)
!2330 = !DILocation(line: 1702, column: 21, scope: !2325)
!2331 = !DILocation(line: 1702, column: 3, scope: !2325)
!2332 = !DILocation(line: 1704, column: 3, scope: !2325)
!2333 = !DILocation(line: 1706, column: 24, scope: !596)
!2334 = !DILocation(line: 1706, column: 2, scope: !596)
!2335 = !DILocation(line: 1706, column: 10, scope: !596)
!2336 = !DILocation(line: 1706, column: 22, scope: !596)
!2337 = !DILocation(line: 1707, column: 2, scope: !596)
!2338 = !DILocation(line: 1707, column: 10, scope: !596)
!2339 = !DILocation(line: 1707, column: 16, scope: !596)
!2340 = !DILocation(line: 1708, column: 2, scope: !596)
!2341 = !DILocation(line: 1708, column: 10, scope: !596)
!2342 = !DILocation(line: 1708, column: 15, scope: !596)
!2343 = !DILocation(line: 1709, column: 2, scope: !596)
!2344 = !DILocation(line: 1709, column: 10, scope: !596)
!2345 = !DILocation(line: 1709, column: 14, scope: !596)
!2346 = !DILocation(line: 1710, column: 2, scope: !596)
!2347 = !DILocation(line: 1711, column: 1, scope: !596)
!2348 = !DILocalVariable(name: "a", arg: 1, scope: !602, file: !1, line: 1788, type: !64)
!2349 = !DILocation(line: 1788, column: 48, scope: !602)
!2350 = !DILocalVariable(name: "lastrm", arg: 2, scope: !602, file: !1, line: 1789, type: !312)
!2351 = !DILocation(line: 1789, column: 24, scope: !602)
!2352 = !DILocalVariable(name: "level", arg: 3, scope: !602, file: !1, line: 1789, type: !63)
!2353 = !DILocation(line: 1789, column: 36, scope: !602)
!2354 = !DILocalVariable(name: "strm", scope: !602, file: !1, line: 1791, type: !397)
!2355 = !DILocation(line: 1791, column: 13, scope: !602)
!2356 = !DILocation(line: 1793, column: 6, scope: !2357)
!2357 = distinct !DILexicalBlock(scope: !602, file: !1, line: 1793, column: 6)
!2358 = !DILocation(line: 1793, column: 14, scope: !2357)
!2359 = !DILocation(line: 1793, column: 6, scope: !602)
!2360 = !DILocation(line: 1794, column: 19, scope: !2357)
!2361 = !DILocation(line: 1794, column: 22, scope: !2357)
!2362 = !DILocation(line: 1794, column: 3, scope: !2357)
!2363 = !DILocation(line: 1795, column: 9, scope: !602)
!2364 = !DILocation(line: 1795, column: 7, scope: !602)
!2365 = !DILocation(line: 1796, column: 6, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !602, file: !1, line: 1796, column: 6)
!2367 = !DILocation(line: 1796, column: 11, scope: !2366)
!2368 = !DILocation(line: 1796, column: 6, scope: !602)
!2369 = !DILocation(line: 1797, column: 21, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !2366, file: !1, line: 1796, column: 20)
!2371 = !DILocation(line: 1797, column: 3, scope: !2370)
!2372 = !DILocation(line: 1799, column: 3, scope: !2370)
!2373 = !DILocation(line: 1804, column: 51, scope: !602)
!2374 = !DILocation(line: 1804, column: 59, scope: !602)
!2375 = !DILocation(line: 1804, column: 26, scope: !602)
!2376 = !DILocation(line: 1804, column: 18, scope: !602)
!2377 = !DILocation(line: 1804, column: 2, scope: !602)
!2378 = !DILocation(line: 1804, column: 8, scope: !602)
!2379 = !DILocation(line: 1804, column: 16, scope: !602)
!2380 = !DILocation(line: 1805, column: 19, scope: !602)
!2381 = !DILocation(line: 1805, column: 27, scope: !602)
!2382 = !DILocation(line: 1805, column: 2, scope: !602)
!2383 = !DILocation(line: 1805, column: 8, scope: !602)
!2384 = !DILocation(line: 1805, column: 17, scope: !602)
!2385 = !DILocation(line: 1806, column: 35, scope: !602)
!2386 = !DILocation(line: 1806, column: 43, scope: !602)
!2387 = !DILocation(line: 1806, column: 52, scope: !602)
!2388 = !DILocation(line: 1806, column: 24, scope: !602)
!2389 = !DILocation(line: 1806, column: 2, scope: !602)
!2390 = !DILocation(line: 1806, column: 8, scope: !602)
!2391 = !DILocation(line: 1806, column: 22, scope: !602)
!2392 = !DILocation(line: 1807, column: 35, scope: !602)
!2393 = !DILocation(line: 1807, column: 43, scope: !602)
!2394 = !DILocation(line: 1807, column: 52, scope: !602)
!2395 = !DILocation(line: 1807, column: 24, scope: !602)
!2396 = !DILocation(line: 1807, column: 2, scope: !602)
!2397 = !DILocation(line: 1807, column: 8, scope: !602)
!2398 = !DILocation(line: 1807, column: 22, scope: !602)
!2399 = !DILocation(line: 1808, column: 27, scope: !602)
!2400 = !DILocation(line: 1808, column: 35, scope: !602)
!2401 = !DILocation(line: 1808, column: 2, scope: !602)
!2402 = !DILocation(line: 1808, column: 8, scope: !602)
!2403 = !DILocation(line: 1808, column: 17, scope: !602)
!2404 = !DILocation(line: 1809, column: 20, scope: !602)
!2405 = !DILocation(line: 1809, column: 28, scope: !602)
!2406 = !DILocation(line: 1809, column: 2, scope: !602)
!2407 = !DILocation(line: 1809, column: 8, scope: !602)
!2408 = !DILocation(line: 1809, column: 18, scope: !602)
!2409 = !DILocation(line: 1810, column: 36, scope: !602)
!2410 = !DILocation(line: 1810, column: 44, scope: !602)
!2411 = !DILocation(line: 1810, column: 54, scope: !602)
!2412 = !DILocation(line: 1810, column: 25, scope: !602)
!2413 = !DILocation(line: 1810, column: 2, scope: !602)
!2414 = !DILocation(line: 1810, column: 8, scope: !602)
!2415 = !DILocation(line: 1810, column: 23, scope: !602)
!2416 = !DILocation(line: 1811, column: 36, scope: !602)
!2417 = !DILocation(line: 1811, column: 44, scope: !602)
!2418 = !DILocation(line: 1811, column: 54, scope: !602)
!2419 = !DILocation(line: 1811, column: 25, scope: !602)
!2420 = !DILocation(line: 1811, column: 2, scope: !602)
!2421 = !DILocation(line: 1811, column: 8, scope: !602)
!2422 = !DILocation(line: 1811, column: 23, scope: !602)
!2423 = !DILocation(line: 1812, column: 25, scope: !2424)
!2424 = distinct !DILexicalBlock(scope: !602, file: !1, line: 1812, column: 6)
!2425 = !DILocation(line: 1812, column: 31, scope: !2424)
!2426 = !DILocation(line: 1812, column: 6, scope: !2424)
!2427 = !DILocation(line: 1812, column: 45, scope: !2424)
!2428 = !DILocation(line: 1812, column: 6, scope: !602)
!2429 = !DILocation(line: 1813, column: 8, scope: !2430)
!2430 = distinct !DILexicalBlock(scope: !2424, file: !1, line: 1812, column: 55)
!2431 = !DILocation(line: 1813, column: 3, scope: !2430)
!2432 = !DILocation(line: 1814, column: 3, scope: !2430)
!2433 = !DILocation(line: 1814, column: 11, scope: !2430)
!2434 = !DILocation(line: 1814, column: 23, scope: !2430)
!2435 = !DILocation(line: 1815, column: 21, scope: !2430)
!2436 = !DILocation(line: 1815, column: 3, scope: !2430)
!2437 = !DILocation(line: 1817, column: 3, scope: !2430)
!2438 = !DILocation(line: 1819, column: 24, scope: !602)
!2439 = !DILocation(line: 1819, column: 2, scope: !602)
!2440 = !DILocation(line: 1819, column: 10, scope: !602)
!2441 = !DILocation(line: 1819, column: 22, scope: !602)
!2442 = !DILocation(line: 1820, column: 2, scope: !602)
!2443 = !DILocation(line: 1820, column: 10, scope: !602)
!2444 = !DILocation(line: 1820, column: 16, scope: !602)
!2445 = !DILocation(line: 1821, column: 2, scope: !602)
!2446 = !DILocation(line: 1821, column: 10, scope: !602)
!2447 = !DILocation(line: 1821, column: 15, scope: !602)
!2448 = !DILocation(line: 1822, column: 2, scope: !602)
!2449 = !DILocation(line: 1822, column: 10, scope: !602)
!2450 = !DILocation(line: 1822, column: 14, scope: !602)
!2451 = !DILocation(line: 1823, column: 2, scope: !602)
!2452 = !DILocation(line: 1824, column: 1, scope: !602)
!2453 = !DILocalVariable(name: "a", arg: 1, scope: !607, file: !1, line: 1999, type: !64)
!2454 = !DILocation(line: 1999, column: 48, scope: !607)
!2455 = !DILocalVariable(name: "lastrm", arg: 2, scope: !607, file: !1, line: 2000, type: !312)
!2456 = !DILocation(line: 2000, column: 24, scope: !607)
!2457 = !DILocalVariable(name: "level", arg: 3, scope: !607, file: !1, line: 2000, type: !63)
!2458 = !DILocation(line: 2000, column: 36, scope: !607)
!2459 = !DILocation(line: 2002, column: 39, scope: !607)
!2460 = !DILocation(line: 2002, column: 42, scope: !607)
!2461 = !DILocation(line: 2002, column: 50, scope: !607)
!2462 = !DILocation(line: 2002, column: 9, scope: !607)
!2463 = !DILocation(line: 2002, column: 2, scope: !607)
!2464 = !DILocalVariable(name: "a", arg: 1, scope: !613, file: !1, line: 2007, type: !64)
!2465 = !DILocation(line: 2007, column: 48, scope: !613)
!2466 = !DILocalVariable(name: "lastrm", arg: 2, scope: !613, file: !1, line: 2008, type: !312)
!2467 = !DILocation(line: 2008, column: 24, scope: !613)
!2468 = !DILocalVariable(name: "level", arg: 3, scope: !613, file: !1, line: 2008, type: !63)
!2469 = !DILocation(line: 2008, column: 36, scope: !613)
!2470 = !DILocation(line: 2010, column: 39, scope: !613)
!2471 = !DILocation(line: 2010, column: 42, scope: !613)
!2472 = !DILocation(line: 2010, column: 50, scope: !613)
!2473 = !DILocation(line: 2010, column: 9, scope: !613)
!2474 = !DILocation(line: 2010, column: 2, scope: !613)
!2475 = !DILocalVariable(name: "a", arg: 1, scope: !614, file: !1, line: 2133, type: !64)
!2476 = !DILocation(line: 2133, column: 47, scope: !614)
!2477 = !DILocalVariable(name: "lastrm", arg: 2, scope: !614, file: !1, line: 2134, type: !312)
!2478 = !DILocation(line: 2134, column: 24, scope: !614)
!2479 = !DILocalVariable(name: "maxOrder", arg: 3, scope: !614, file: !1, line: 2134, type: !53)
!2480 = !DILocation(line: 2134, column: 41, scope: !614)
!2481 = !DILocalVariable(name: "msize", arg: 4, scope: !614, file: !1, line: 2134, type: !275)
!2482 = !DILocation(line: 2134, column: 60, scope: !614)
!2483 = !DILocalVariable(name: "strm", scope: !614, file: !1, line: 2136, type: !477)
!2484 = !DILocation(line: 2136, column: 22, scope: !614)
!2485 = !DILocalVariable(name: "props", scope: !614, file: !1, line: 2137, type: !256)
!2486 = !DILocation(line: 2137, column: 11, scope: !614)
!2487 = !DILocalVariable(name: "r", scope: !614, file: !1, line: 2138, type: !63)
!2488 = !DILocation(line: 2138, column: 6, scope: !614)
!2489 = !DILocation(line: 2140, column: 6, scope: !2490)
!2490 = distinct !DILexicalBlock(scope: !614, file: !1, line: 2140, column: 6)
!2491 = !DILocation(line: 2140, column: 14, scope: !2490)
!2492 = !DILocation(line: 2140, column: 6, scope: !614)
!2493 = !DILocation(line: 2141, column: 19, scope: !2490)
!2494 = !DILocation(line: 2141, column: 22, scope: !2490)
!2495 = !DILocation(line: 2141, column: 3, scope: !2490)
!2496 = !DILocation(line: 2142, column: 9, scope: !614)
!2497 = !DILocation(line: 2142, column: 7, scope: !614)
!2498 = !DILocation(line: 2143, column: 6, scope: !2499)
!2499 = distinct !DILexicalBlock(scope: !614, file: !1, line: 2143, column: 6)
!2500 = !DILocation(line: 2143, column: 11, scope: !2499)
!2501 = !DILocation(line: 2143, column: 6, scope: !614)
!2502 = !DILocation(line: 2144, column: 21, scope: !2503)
!2503 = distinct !DILexicalBlock(scope: !2499, file: !1, line: 2143, column: 20)
!2504 = !DILocation(line: 2144, column: 3, scope: !2503)
!2505 = !DILocation(line: 2146, column: 3, scope: !2503)
!2506 = !DILocation(line: 2148, column: 15, scope: !614)
!2507 = !DILocation(line: 2148, column: 2, scope: !614)
!2508 = !DILocation(line: 2148, column: 8, scope: !614)
!2509 = !DILocation(line: 2148, column: 13, scope: !614)
!2510 = !DILocation(line: 2149, column: 6, scope: !2511)
!2511 = distinct !DILexicalBlock(scope: !614, file: !1, line: 2149, column: 6)
!2512 = !DILocation(line: 2149, column: 12, scope: !2511)
!2513 = !DILocation(line: 2149, column: 17, scope: !2511)
!2514 = !DILocation(line: 2149, column: 6, scope: !614)
!2515 = !DILocation(line: 2150, column: 8, scope: !2516)
!2516 = distinct !DILexicalBlock(scope: !2511, file: !1, line: 2149, column: 26)
!2517 = !DILocation(line: 2150, column: 3, scope: !2516)
!2518 = !DILocation(line: 2151, column: 21, scope: !2516)
!2519 = !DILocation(line: 2151, column: 3, scope: !2516)
!2520 = !DILocation(line: 2153, column: 3, scope: !2516)
!2521 = !DILocation(line: 2155, column: 19, scope: !614)
!2522 = !DILocation(line: 2155, column: 25, scope: !614)
!2523 = !DILocation(line: 2155, column: 2, scope: !614)
!2524 = !DILocation(line: 2155, column: 8, scope: !614)
!2525 = !DILocation(line: 2155, column: 17, scope: !614)
!2526 = !DILocation(line: 2156, column: 19, scope: !614)
!2527 = !DILocation(line: 2156, column: 25, scope: !614)
!2528 = !DILocation(line: 2156, column: 30, scope: !614)
!2529 = !DILocation(line: 2156, column: 2, scope: !614)
!2530 = !DILocation(line: 2156, column: 8, scope: !614)
!2531 = !DILocation(line: 2156, column: 17, scope: !614)
!2532 = !DILocation(line: 2158, column: 10, scope: !614)
!2533 = !DILocation(line: 2158, column: 8, scope: !614)
!2534 = !DILocation(line: 2159, column: 6, scope: !2535)
!2535 = distinct !DILexicalBlock(scope: !614, file: !1, line: 2159, column: 6)
!2536 = !DILocation(line: 2159, column: 12, scope: !2535)
!2537 = !DILocation(line: 2159, column: 6, scope: !614)
!2538 = !DILocation(line: 2160, column: 8, scope: !2539)
!2539 = distinct !DILexicalBlock(scope: !2535, file: !1, line: 2159, column: 21)
!2540 = !DILocation(line: 2160, column: 14, scope: !2539)
!2541 = !DILocation(line: 2160, column: 3, scope: !2539)
!2542 = !DILocation(line: 2161, column: 8, scope: !2539)
!2543 = !DILocation(line: 2161, column: 3, scope: !2539)
!2544 = !DILocation(line: 2162, column: 21, scope: !2539)
!2545 = !DILocation(line: 2162, column: 3, scope: !2539)
!2546 = !DILocation(line: 2164, column: 3, scope: !2539)
!2547 = !DILocation(line: 2166, column: 13, scope: !614)
!2548 = !DILocation(line: 2166, column: 2, scope: !614)
!2549 = !DILocation(line: 2166, column: 11, scope: !614)
!2550 = !DILocation(line: 2167, column: 18, scope: !614)
!2551 = !DILocation(line: 2167, column: 23, scope: !614)
!2552 = !DILocation(line: 2167, column: 27, scope: !614)
!2553 = !DILocation(line: 2167, column: 2, scope: !614)
!2554 = !DILocation(line: 2168, column: 28, scope: !614)
!2555 = !DILocation(line: 2168, column: 45, scope: !614)
!2556 = !DILocation(line: 2168, column: 51, scope: !614)
!2557 = !DILocation(line: 2168, column: 2, scope: !614)
!2558 = !DILocation(line: 2169, column: 32, scope: !614)
!2559 = !DILocation(line: 2170, column: 4, scope: !614)
!2560 = !DILocation(line: 2170, column: 10, scope: !614)
!2561 = !DILocation(line: 2170, column: 25, scope: !614)
!2562 = !DILocation(line: 2169, column: 6, scope: !614)
!2563 = !DILocation(line: 2169, column: 4, scope: !614)
!2564 = !DILocation(line: 2171, column: 6, scope: !2565)
!2565 = distinct !DILexicalBlock(scope: !614, file: !1, line: 2171, column: 6)
!2566 = !DILocation(line: 2171, column: 8, scope: !2565)
!2567 = !DILocation(line: 2171, column: 6, scope: !614)
!2568 = !DILocation(line: 2172, column: 8, scope: !2569)
!2569 = distinct !DILexicalBlock(scope: !2565, file: !1, line: 2171, column: 14)
!2570 = !DILocation(line: 2172, column: 14, scope: !2569)
!2571 = !DILocation(line: 2172, column: 3, scope: !2569)
!2572 = !DILocation(line: 2173, column: 8, scope: !2569)
!2573 = !DILocation(line: 2173, column: 3, scope: !2569)
!2574 = !DILocation(line: 2174, column: 8, scope: !2569)
!2575 = !DILocation(line: 2174, column: 3, scope: !2569)
!2576 = !DILocation(line: 2175, column: 21, scope: !2569)
!2577 = !DILocation(line: 2175, column: 3, scope: !2569)
!2578 = !DILocation(line: 2177, column: 3, scope: !2569)
!2579 = !DILocation(line: 2179, column: 28, scope: !614)
!2580 = !DILocation(line: 2179, column: 41, scope: !614)
!2581 = !DILocation(line: 2179, column: 47, scope: !614)
!2582 = !DILocation(line: 2179, column: 63, scope: !614)
!2583 = !DILocation(line: 2179, column: 2, scope: !614)
!2584 = !DILocation(line: 2180, column: 44, scope: !614)
!2585 = !DILocation(line: 2180, column: 20, scope: !614)
!2586 = !DILocation(line: 2180, column: 2, scope: !614)
!2587 = !DILocation(line: 2180, column: 8, scope: !614)
!2588 = !DILocation(line: 2180, column: 16, scope: !614)
!2589 = !DILocation(line: 2180, column: 18, scope: !614)
!2590 = !DILocation(line: 2181, column: 2, scope: !614)
!2591 = !DILocation(line: 2181, column: 8, scope: !614)
!2592 = !DILocation(line: 2181, column: 16, scope: !614)
!2593 = !DILocation(line: 2181, column: 22, scope: !614)
!2594 = !DILocation(line: 2182, column: 29, scope: !614)
!2595 = !DILocation(line: 2182, column: 35, scope: !614)
!2596 = !DILocation(line: 2182, column: 2, scope: !614)
!2597 = !DILocation(line: 2182, column: 8, scope: !614)
!2598 = !DILocation(line: 2182, column: 18, scope: !614)
!2599 = !DILocation(line: 2182, column: 25, scope: !614)
!2600 = !DILocation(line: 2183, column: 28, scope: !614)
!2601 = !DILocation(line: 2183, column: 51, scope: !614)
!2602 = !DILocation(line: 2183, column: 57, scope: !614)
!2603 = !DILocation(line: 2183, column: 2, scope: !614)
!2604 = !DILocation(line: 2184, column: 2, scope: !614)
!2605 = !DILocation(line: 2184, column: 8, scope: !614)
!2606 = !DILocation(line: 2184, column: 13, scope: !614)
!2607 = !DILocation(line: 2186, column: 24, scope: !614)
!2608 = !DILocation(line: 2186, column: 2, scope: !614)
!2609 = !DILocation(line: 2186, column: 10, scope: !614)
!2610 = !DILocation(line: 2186, column: 22, scope: !614)
!2611 = !DILocation(line: 2187, column: 2, scope: !614)
!2612 = !DILocation(line: 2187, column: 10, scope: !614)
!2613 = !DILocation(line: 2187, column: 16, scope: !614)
!2614 = !DILocation(line: 2188, column: 2, scope: !614)
!2615 = !DILocation(line: 2188, column: 10, scope: !614)
!2616 = !DILocation(line: 2188, column: 15, scope: !614)
!2617 = !DILocation(line: 2189, column: 2, scope: !614)
!2618 = !DILocation(line: 2189, column: 10, scope: !614)
!2619 = !DILocation(line: 2189, column: 14, scope: !614)
!2620 = !DILocation(line: 2190, column: 2, scope: !614)
!2621 = !DILocation(line: 2190, column: 10, scope: !614)
!2622 = !DILocation(line: 2190, column: 20, scope: !614)
!2623 = !DILocation(line: 2191, column: 18, scope: !614)
!2624 = !DILocation(line: 2191, column: 2, scope: !614)
!2625 = !DILocation(line: 2191, column: 10, scope: !614)
!2626 = !DILocation(line: 2191, column: 16, scope: !614)
!2627 = !DILocation(line: 2192, column: 2, scope: !614)
!2628 = !DILocation(line: 2193, column: 1, scope: !614)
!2629 = !DILocalVariable(name: "a", arg: 1, scope: !628, file: !1, line: 1626, type: !64)
!2630 = !DILocation(line: 1626, column: 47, scope: !628)
!2631 = !DILocalVariable(name: "lastrm", arg: 2, scope: !628, file: !1, line: 1626, type: !312)
!2632 = !DILocation(line: 1626, column: 69, scope: !628)
!2633 = !DILocation(line: 1629, column: 6, scope: !2634)
!2634 = distinct !DILexicalBlock(scope: !628, file: !1, line: 1629, column: 6)
!2635 = !DILocation(line: 1629, column: 14, scope: !2634)
!2636 = !DILocation(line: 1629, column: 6, scope: !628)
!2637 = !DILocation(line: 1630, column: 19, scope: !2634)
!2638 = !DILocation(line: 1630, column: 22, scope: !2634)
!2639 = !DILocation(line: 1630, column: 3, scope: !2634)
!2640 = !DILocation(line: 1631, column: 2, scope: !628)
!2641 = !DILocation(line: 1631, column: 10, scope: !628)
!2642 = !DILocation(line: 1631, column: 16, scope: !628)
!2643 = !DILocation(line: 1632, column: 2, scope: !628)
!2644 = !DILocation(line: 1632, column: 10, scope: !628)
!2645 = !DILocation(line: 1632, column: 15, scope: !628)
!2646 = !DILocation(line: 1633, column: 2, scope: !628)
!2647 = !DILocation(line: 1633, column: 10, scope: !628)
!2648 = !DILocation(line: 1633, column: 14, scope: !628)
!2649 = !DILocation(line: 1634, column: 2, scope: !628)
!2650 = !DILocalVariable(name: "a", arg: 1, scope: !599, file: !1, line: 2317, type: !64)
!2651 = !DILocation(line: 2317, column: 33, scope: !599)
!2652 = !DILocalVariable(name: "lastrm", arg: 2, scope: !599, file: !1, line: 2317, type: !312)
!2653 = !DILocation(line: 2317, column: 55, scope: !599)
!2654 = !DILocation(line: 2319, column: 6, scope: !2655)
!2655 = distinct !DILexicalBlock(scope: !599, file: !1, line: 2319, column: 6)
!2656 = !DILocation(line: 2319, column: 14, scope: !2655)
!2657 = !DILocation(line: 2319, column: 6, scope: !599)
!2658 = !DILocation(line: 2320, column: 3, scope: !2659)
!2659 = distinct !DILexicalBlock(scope: !2655, file: !1, line: 2319, column: 21)
!2660 = !DILocation(line: 2320, column: 11, scope: !2659)
!2661 = !DILocation(line: 2320, column: 21, scope: !2659)
!2662 = !DILocation(line: 2321, column: 8, scope: !2659)
!2663 = !DILocation(line: 2321, column: 16, scope: !2659)
!2664 = !DILocation(line: 2321, column: 3, scope: !2659)
!2665 = !DILocation(line: 2322, column: 3, scope: !2659)
!2666 = !DILocation(line: 2322, column: 11, scope: !2659)
!2667 = !DILocation(line: 2322, column: 17, scope: !2659)
!2668 = !DILocation(line: 2323, column: 11, scope: !2659)
!2669 = !DILocation(line: 2323, column: 19, scope: !2659)
!2670 = !DILocation(line: 2323, column: 23, scope: !2659)
!2671 = !DILocation(line: 2323, column: 26, scope: !2659)
!2672 = !DILocation(line: 2323, column: 3, scope: !2659)
!2673 = !DILocation(line: 2325, column: 2, scope: !599)
!2674 = !DILocation(line: 2326, column: 1, scope: !599)
!2675 = !DILocalVariable(name: "a", arg: 1, scope: !600, file: !1, line: 1714, type: !64)
!2676 = !DILocation(line: 1714, column: 42, scope: !600)
!2677 = !DILocalVariable(name: "lastrm", arg: 2, scope: !600, file: !1, line: 1715, type: !312)
!2678 = !DILocation(line: 1715, column: 24, scope: !600)
!2679 = !DILocalVariable(name: "action", arg: 3, scope: !600, file: !1, line: 1715, type: !3)
!2680 = !DILocation(line: 1715, column: 48, scope: !600)
!2681 = !DILocalVariable(name: "strm", scope: !600, file: !1, line: 1717, type: !365)
!2682 = !DILocation(line: 1717, column: 12, scope: !600)
!2683 = !DILocalVariable(name: "r", scope: !600, file: !1, line: 1718, type: !63)
!2684 = !DILocation(line: 1718, column: 6, scope: !600)
!2685 = !DILocation(line: 1720, column: 21, scope: !600)
!2686 = !DILocation(line: 1720, column: 29, scope: !600)
!2687 = !DILocation(line: 1720, column: 9, scope: !600)
!2688 = !DILocation(line: 1720, column: 7, scope: !600)
!2689 = !DILocation(line: 1724, column: 52, scope: !600)
!2690 = !DILocation(line: 1724, column: 60, scope: !600)
!2691 = !DILocation(line: 1724, column: 27, scope: !600)
!2692 = !DILocation(line: 1724, column: 18, scope: !600)
!2693 = !DILocation(line: 1724, column: 2, scope: !600)
!2694 = !DILocation(line: 1724, column: 8, scope: !600)
!2695 = !DILocation(line: 1724, column: 16, scope: !600)
!2696 = !DILocation(line: 1725, column: 25, scope: !600)
!2697 = !DILocation(line: 1725, column: 33, scope: !600)
!2698 = !DILocation(line: 1725, column: 19, scope: !600)
!2699 = !DILocation(line: 1725, column: 2, scope: !600)
!2700 = !DILocation(line: 1725, column: 8, scope: !600)
!2701 = !DILocation(line: 1725, column: 17, scope: !600)
!2702 = !DILocation(line: 1726, column: 26, scope: !600)
!2703 = !DILocation(line: 1726, column: 34, scope: !600)
!2704 = !DILocation(line: 1726, column: 2, scope: !600)
!2705 = !DILocation(line: 1726, column: 8, scope: !600)
!2706 = !DILocation(line: 1726, column: 17, scope: !600)
!2707 = !DILocation(line: 1727, column: 19, scope: !600)
!2708 = !DILocation(line: 1727, column: 27, scope: !600)
!2709 = !DILocation(line: 1727, column: 2, scope: !600)
!2710 = !DILocation(line: 1727, column: 8, scope: !600)
!2711 = !DILocation(line: 1727, column: 17, scope: !600)
!2712 = !DILocation(line: 1728, column: 26, scope: !600)
!2713 = !DILocation(line: 1728, column: 34, scope: !600)
!2714 = !DILocation(line: 1728, column: 20, scope: !600)
!2715 = !DILocation(line: 1728, column: 2, scope: !600)
!2716 = !DILocation(line: 1728, column: 8, scope: !600)
!2717 = !DILocation(line: 1728, column: 18, scope: !600)
!2718 = !DILocation(line: 1729, column: 27, scope: !600)
!2719 = !DILocation(line: 1729, column: 35, scope: !600)
!2720 = !DILocation(line: 1729, column: 2, scope: !600)
!2721 = !DILocation(line: 1729, column: 8, scope: !600)
!2722 = !DILocation(line: 1729, column: 18, scope: !600)
!2723 = !DILocation(line: 1730, column: 14, scope: !600)
!2724 = !DILocation(line: 1731, column: 7, scope: !600)
!2725 = !DILocation(line: 1731, column: 14, scope: !600)
!2726 = !DILocation(line: 1731, column: 6, scope: !600)
!2727 = !DILocation(line: 1730, column: 6, scope: !600)
!2728 = !DILocation(line: 1730, column: 4, scope: !600)
!2729 = !DILocation(line: 1732, column: 20, scope: !600)
!2730 = !DILocation(line: 1732, column: 26, scope: !600)
!2731 = !DILocation(line: 1732, column: 2, scope: !600)
!2732 = !DILocation(line: 1732, column: 10, scope: !600)
!2733 = !DILocation(line: 1732, column: 18, scope: !600)
!2734 = !DILocation(line: 1733, column: 21, scope: !600)
!2735 = !DILocation(line: 1733, column: 27, scope: !600)
!2736 = !DILocation(line: 1733, column: 2, scope: !600)
!2737 = !DILocation(line: 1733, column: 10, scope: !600)
!2738 = !DILocation(line: 1733, column: 19, scope: !600)
!2739 = !DILocation(line: 1734, column: 21, scope: !600)
!2740 = !DILocation(line: 1734, column: 27, scope: !600)
!2741 = !DILocation(line: 1734, column: 2, scope: !600)
!2742 = !DILocation(line: 1734, column: 10, scope: !600)
!2743 = !DILocation(line: 1734, column: 19, scope: !600)
!2744 = !DILocation(line: 1735, column: 21, scope: !600)
!2745 = !DILocation(line: 1735, column: 27, scope: !600)
!2746 = !DILocation(line: 1735, column: 2, scope: !600)
!2747 = !DILocation(line: 1735, column: 10, scope: !600)
!2748 = !DILocation(line: 1735, column: 19, scope: !600)
!2749 = !DILocation(line: 1736, column: 22, scope: !600)
!2750 = !DILocation(line: 1736, column: 28, scope: !600)
!2751 = !DILocation(line: 1736, column: 2, scope: !600)
!2752 = !DILocation(line: 1736, column: 10, scope: !600)
!2753 = !DILocation(line: 1736, column: 20, scope: !600)
!2754 = !DILocation(line: 1737, column: 22, scope: !600)
!2755 = !DILocation(line: 1737, column: 28, scope: !600)
!2756 = !DILocation(line: 1737, column: 2, scope: !600)
!2757 = !DILocation(line: 1737, column: 10, scope: !600)
!2758 = !DILocation(line: 1737, column: 20, scope: !600)
!2759 = !DILocation(line: 1738, column: 10, scope: !600)
!2760 = !DILocation(line: 1738, column: 2, scope: !600)
!2761 = !DILocation(line: 1740, column: 3, scope: !2762)
!2762 = distinct !DILexicalBlock(scope: !600, file: !1, line: 1738, column: 13)
!2763 = !DILocation(line: 1742, column: 3, scope: !2762)
!2764 = !DILocation(line: 1744, column: 21, scope: !2762)
!2765 = !DILocation(line: 1746, column: 45, scope: !2762)
!2766 = !DILocation(line: 1744, column: 3, scope: !2762)
!2767 = !DILocation(line: 1747, column: 3, scope: !2762)
!2768 = !DILocation(line: 1749, column: 1, scope: !600)
!2769 = !DILocalVariable(name: "a", arg: 1, scope: !601, file: !1, line: 1752, type: !64)
!2770 = !DILocation(line: 1752, column: 41, scope: !601)
!2771 = !DILocalVariable(name: "lastrm", arg: 2, scope: !601, file: !1, line: 1752, type: !312)
!2772 = !DILocation(line: 1752, column: 63, scope: !601)
!2773 = !DILocalVariable(name: "strm", scope: !601, file: !1, line: 1754, type: !365)
!2774 = !DILocation(line: 1754, column: 12, scope: !601)
!2775 = !DILocalVariable(name: "r", scope: !601, file: !1, line: 1755, type: !63)
!2776 = !DILocation(line: 1755, column: 6, scope: !601)
!2777 = !DILocation(line: 1757, column: 21, scope: !601)
!2778 = !DILocation(line: 1757, column: 29, scope: !601)
!2779 = !DILocation(line: 1757, column: 9, scope: !601)
!2780 = !DILocation(line: 1757, column: 7, scope: !601)
!2781 = !DILocation(line: 1758, column: 17, scope: !601)
!2782 = !DILocation(line: 1758, column: 6, scope: !601)
!2783 = !DILocation(line: 1758, column: 4, scope: !601)
!2784 = !DILocation(line: 1759, column: 7, scope: !601)
!2785 = !DILocation(line: 1759, column: 2, scope: !601)
!2786 = !DILocation(line: 1760, column: 2, scope: !601)
!2787 = !DILocation(line: 1760, column: 10, scope: !601)
!2788 = !DILocation(line: 1760, column: 22, scope: !601)
!2789 = !DILocation(line: 1761, column: 2, scope: !601)
!2790 = !DILocation(line: 1761, column: 10, scope: !601)
!2791 = !DILocation(line: 1761, column: 16, scope: !601)
!2792 = !DILocation(line: 1762, column: 6, scope: !2793)
!2793 = distinct !DILexicalBlock(scope: !601, file: !1, line: 1762, column: 6)
!2794 = !DILocation(line: 1762, column: 8, scope: !2793)
!2795 = !DILocation(line: 1762, column: 6, scope: !601)
!2796 = !DILocation(line: 1763, column: 21, scope: !2797)
!2797 = distinct !DILexicalBlock(scope: !2793, file: !1, line: 1762, column: 17)
!2798 = !DILocation(line: 1763, column: 3, scope: !2797)
!2799 = !DILocation(line: 1765, column: 3, scope: !2797)
!2800 = !DILocation(line: 1767, column: 2, scope: !601)
!2801 = !DILocation(line: 1768, column: 1, scope: !601)
!2802 = !DILocalVariable(name: "a", arg: 1, scope: !605, file: !1, line: 1827, type: !64)
!2803 = !DILocation(line: 1827, column: 40, scope: !605)
!2804 = !DILocalVariable(name: "lastrm", arg: 2, scope: !605, file: !1, line: 1828, type: !312)
!2805 = !DILocation(line: 1828, column: 24, scope: !605)
!2806 = !DILocalVariable(name: "action", arg: 3, scope: !605, file: !1, line: 1828, type: !3)
!2807 = !DILocation(line: 1828, column: 48, scope: !605)
!2808 = !DILocalVariable(name: "strm", scope: !605, file: !1, line: 1830, type: !397)
!2809 = !DILocation(line: 1830, column: 13, scope: !605)
!2810 = !DILocalVariable(name: "r", scope: !605, file: !1, line: 1831, type: !63)
!2811 = !DILocation(line: 1831, column: 6, scope: !605)
!2812 = !DILocation(line: 1833, column: 22, scope: !605)
!2813 = !DILocation(line: 1833, column: 30, scope: !605)
!2814 = !DILocation(line: 1833, column: 9, scope: !605)
!2815 = !DILocation(line: 1833, column: 7, scope: !605)
!2816 = !DILocation(line: 1837, column: 51, scope: !605)
!2817 = !DILocation(line: 1837, column: 59, scope: !605)
!2818 = !DILocation(line: 1837, column: 26, scope: !605)
!2819 = !DILocation(line: 1837, column: 18, scope: !605)
!2820 = !DILocation(line: 1837, column: 2, scope: !605)
!2821 = !DILocation(line: 1837, column: 8, scope: !605)
!2822 = !DILocation(line: 1837, column: 16, scope: !605)
!2823 = !DILocation(line: 1838, column: 19, scope: !605)
!2824 = !DILocation(line: 1838, column: 27, scope: !605)
!2825 = !DILocation(line: 1838, column: 2, scope: !605)
!2826 = !DILocation(line: 1838, column: 8, scope: !605)
!2827 = !DILocation(line: 1838, column: 17, scope: !605)
!2828 = !DILocation(line: 1839, column: 35, scope: !605)
!2829 = !DILocation(line: 1839, column: 43, scope: !605)
!2830 = !DILocation(line: 1839, column: 52, scope: !605)
!2831 = !DILocation(line: 1839, column: 24, scope: !605)
!2832 = !DILocation(line: 1839, column: 2, scope: !605)
!2833 = !DILocation(line: 1839, column: 8, scope: !605)
!2834 = !DILocation(line: 1839, column: 22, scope: !605)
!2835 = !DILocation(line: 1840, column: 35, scope: !605)
!2836 = !DILocation(line: 1840, column: 43, scope: !605)
!2837 = !DILocation(line: 1840, column: 52, scope: !605)
!2838 = !DILocation(line: 1840, column: 24, scope: !605)
!2839 = !DILocation(line: 1840, column: 2, scope: !605)
!2840 = !DILocation(line: 1840, column: 8, scope: !605)
!2841 = !DILocation(line: 1840, column: 22, scope: !605)
!2842 = !DILocation(line: 1841, column: 27, scope: !605)
!2843 = !DILocation(line: 1841, column: 35, scope: !605)
!2844 = !DILocation(line: 1841, column: 2, scope: !605)
!2845 = !DILocation(line: 1841, column: 8, scope: !605)
!2846 = !DILocation(line: 1841, column: 17, scope: !605)
!2847 = !DILocation(line: 1842, column: 20, scope: !605)
!2848 = !DILocation(line: 1842, column: 28, scope: !605)
!2849 = !DILocation(line: 1842, column: 2, scope: !605)
!2850 = !DILocation(line: 1842, column: 8, scope: !605)
!2851 = !DILocation(line: 1842, column: 18, scope: !605)
!2852 = !DILocation(line: 1843, column: 36, scope: !605)
!2853 = !DILocation(line: 1843, column: 44, scope: !605)
!2854 = !DILocation(line: 1843, column: 54, scope: !605)
!2855 = !DILocation(line: 1843, column: 25, scope: !605)
!2856 = !DILocation(line: 1843, column: 2, scope: !605)
!2857 = !DILocation(line: 1843, column: 8, scope: !605)
!2858 = !DILocation(line: 1843, column: 23, scope: !605)
!2859 = !DILocation(line: 1844, column: 36, scope: !605)
!2860 = !DILocation(line: 1844, column: 44, scope: !605)
!2861 = !DILocation(line: 1844, column: 54, scope: !605)
!2862 = !DILocation(line: 1844, column: 25, scope: !605)
!2863 = !DILocation(line: 1844, column: 2, scope: !605)
!2864 = !DILocation(line: 1844, column: 8, scope: !605)
!2865 = !DILocation(line: 1844, column: 23, scope: !605)
!2866 = !DILocation(line: 1845, column: 21, scope: !605)
!2867 = !DILocation(line: 1846, column: 7, scope: !605)
!2868 = !DILocation(line: 1846, column: 14, scope: !605)
!2869 = !DILocation(line: 1846, column: 6, scope: !605)
!2870 = !DILocation(line: 1845, column: 6, scope: !605)
!2871 = !DILocation(line: 1845, column: 4, scope: !605)
!2872 = !DILocation(line: 1847, column: 43, scope: !605)
!2873 = !DILocation(line: 1847, column: 49, scope: !605)
!2874 = !DILocation(line: 1847, column: 2, scope: !605)
!2875 = !DILocation(line: 1847, column: 10, scope: !605)
!2876 = !DILocation(line: 1847, column: 18, scope: !605)
!2877 = !DILocation(line: 1848, column: 21, scope: !605)
!2878 = !DILocation(line: 1848, column: 27, scope: !605)
!2879 = !DILocation(line: 1848, column: 2, scope: !605)
!2880 = !DILocation(line: 1848, column: 10, scope: !605)
!2881 = !DILocation(line: 1848, column: 19, scope: !605)
!2882 = !DILocation(line: 1850, column: 28, scope: !605)
!2883 = !DILocation(line: 1850, column: 34, scope: !605)
!2884 = !DILocation(line: 1850, column: 8, scope: !605)
!2885 = !DILocation(line: 1850, column: 49, scope: !605)
!2886 = !DILocation(line: 1851, column: 28, scope: !605)
!2887 = !DILocation(line: 1851, column: 34, scope: !605)
!2888 = !DILocation(line: 1851, column: 8, scope: !605)
!2889 = !DILocation(line: 1851, column: 6, scope: !605)
!2890 = !DILocation(line: 1849, column: 2, scope: !605)
!2891 = !DILocation(line: 1849, column: 10, scope: !605)
!2892 = !DILocation(line: 1849, column: 19, scope: !605)
!2893 = !DILocation(line: 1852, column: 38, scope: !605)
!2894 = !DILocation(line: 1852, column: 44, scope: !605)
!2895 = !DILocation(line: 1852, column: 2, scope: !605)
!2896 = !DILocation(line: 1852, column: 10, scope: !605)
!2897 = !DILocation(line: 1852, column: 19, scope: !605)
!2898 = !DILocation(line: 1853, column: 22, scope: !605)
!2899 = !DILocation(line: 1853, column: 28, scope: !605)
!2900 = !DILocation(line: 1853, column: 2, scope: !605)
!2901 = !DILocation(line: 1853, column: 10, scope: !605)
!2902 = !DILocation(line: 1853, column: 20, scope: !605)
!2903 = !DILocation(line: 1855, column: 28, scope: !605)
!2904 = !DILocation(line: 1855, column: 34, scope: !605)
!2905 = !DILocation(line: 1855, column: 8, scope: !605)
!2906 = !DILocation(line: 1855, column: 50, scope: !605)
!2907 = !DILocation(line: 1856, column: 28, scope: !605)
!2908 = !DILocation(line: 1856, column: 34, scope: !605)
!2909 = !DILocation(line: 1856, column: 8, scope: !605)
!2910 = !DILocation(line: 1856, column: 6, scope: !605)
!2911 = !DILocation(line: 1854, column: 2, scope: !605)
!2912 = !DILocation(line: 1854, column: 10, scope: !605)
!2913 = !DILocation(line: 1854, column: 20, scope: !605)
!2914 = !DILocation(line: 1857, column: 10, scope: !605)
!2915 = !DILocation(line: 1857, column: 2, scope: !605)
!2916 = !DILocation(line: 1860, column: 3, scope: !2917)
!2917 = distinct !DILexicalBlock(scope: !605, file: !1, line: 1857, column: 13)
!2918 = !DILocation(line: 1863, column: 3, scope: !2917)
!2919 = !DILocation(line: 1866, column: 21, scope: !2917)
!2920 = !DILocation(line: 1868, column: 52, scope: !2917)
!2921 = !DILocation(line: 1866, column: 3, scope: !2917)
!2922 = !DILocation(line: 1869, column: 3, scope: !2917)
!2923 = !DILocation(line: 1871, column: 1, scope: !605)
!2924 = !DILocalVariable(name: "a", arg: 1, scope: !606, file: !1, line: 1874, type: !64)
!2925 = !DILocation(line: 1874, column: 39, scope: !606)
!2926 = !DILocalVariable(name: "lastrm", arg: 2, scope: !606, file: !1, line: 1874, type: !312)
!2927 = !DILocation(line: 1874, column: 61, scope: !606)
!2928 = !DILocalVariable(name: "strm", scope: !606, file: !1, line: 1876, type: !397)
!2929 = !DILocation(line: 1876, column: 13, scope: !606)
!2930 = !DILocalVariable(name: "r", scope: !606, file: !1, line: 1877, type: !63)
!2931 = !DILocation(line: 1877, column: 6, scope: !606)
!2932 = !DILocation(line: 1879, column: 22, scope: !606)
!2933 = !DILocation(line: 1879, column: 30, scope: !606)
!2934 = !DILocation(line: 1879, column: 9, scope: !606)
!2935 = !DILocation(line: 1879, column: 7, scope: !606)
!2936 = !DILocation(line: 1880, column: 24, scope: !606)
!2937 = !DILocation(line: 1880, column: 6, scope: !606)
!2938 = !DILocation(line: 1880, column: 4, scope: !606)
!2939 = !DILocation(line: 1881, column: 7, scope: !606)
!2940 = !DILocation(line: 1881, column: 2, scope: !606)
!2941 = !DILocation(line: 1882, column: 2, scope: !606)
!2942 = !DILocation(line: 1882, column: 10, scope: !606)
!2943 = !DILocation(line: 1882, column: 22, scope: !606)
!2944 = !DILocation(line: 1883, column: 2, scope: !606)
!2945 = !DILocation(line: 1883, column: 10, scope: !606)
!2946 = !DILocation(line: 1883, column: 16, scope: !606)
!2947 = !DILocation(line: 1884, column: 6, scope: !2948)
!2948 = distinct !DILexicalBlock(scope: !606, file: !1, line: 1884, column: 6)
!2949 = !DILocation(line: 1884, column: 8, scope: !2948)
!2950 = !DILocation(line: 1884, column: 6, scope: !606)
!2951 = !DILocation(line: 1885, column: 21, scope: !2952)
!2952 = distinct !DILexicalBlock(scope: !2948, file: !1, line: 1884, column: 18)
!2953 = !DILocation(line: 1885, column: 3, scope: !2952)
!2954 = !DILocation(line: 1887, column: 3, scope: !2952)
!2955 = !DILocation(line: 1889, column: 2, scope: !606)
!2956 = !DILocation(line: 1890, column: 1, scope: !606)
!2957 = !DILocalVariable(name: "a", arg: 1, scope: !608, file: !1, line: 1910, type: !64)
!2958 = !DILocation(line: 1910, column: 47, scope: !608)
!2959 = !DILocalVariable(name: "lastrm", arg: 2, scope: !608, file: !1, line: 1911, type: !312)
!2960 = !DILocation(line: 1911, column: 24, scope: !608)
!2961 = !DILocalVariable(name: "level", arg: 3, scope: !608, file: !1, line: 1911, type: !63)
!2962 = !DILocation(line: 1911, column: 36, scope: !608)
!2963 = !DILocalVariable(name: "filter_id", arg: 4, scope: !608, file: !1, line: 1911, type: !237)
!2964 = !DILocation(line: 1911, column: 52, scope: !608)
!2965 = !DILocalVariable(name: "strm", scope: !608, file: !1, line: 1914, type: !430)
!2966 = !DILocation(line: 1914, column: 15, scope: !608)
!2967 = !DILocalVariable(name: "lzmafilters", scope: !608, file: !1, line: 1915, type: !421)
!2968 = !DILocation(line: 1915, column: 15, scope: !608)
!2969 = !DILocalVariable(name: "lzma_opt", scope: !608, file: !1, line: 1916, type: !2970)
!2970 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !12, line: 399, baseType: !2971)
!2971 = !DICompositeType(tag: DW_TAG_structure_type, file: !12, line: 185, size: 896, align: 64, elements: !2972)
!2972 = !{!2973, !2974, !2975, !2976, !2977, !2978, !2979, !2981, !2982, !2984, !2985, !2986, !2987, !2988, !2989, !2990, !2991, !2992, !2993, !2994, !2995, !2996, !2997, !2998}
!2973 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !2971, file: !12, line: 217, baseType: !275, size: 32, align: 32)
!2974 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !2971, file: !12, line: 240, baseType: !297, size: 64, align: 64, offset: 64)
!2975 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !2971, file: !12, line: 254, baseType: !275, size: 32, align: 32, offset: 128)
!2976 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !2971, file: !12, line: 281, baseType: !275, size: 32, align: 32, offset: 160)
!2977 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !2971, file: !12, line: 293, baseType: !275, size: 32, align: 32, offset: 192)
!2978 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !2971, file: !12, line: 316, baseType: !275, size: 32, align: 32, offset: 224)
!2979 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !2971, file: !12, line: 322, baseType: !2980, size: 32, align: 32, offset: 256)
!2980 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !12, line: 155, baseType: !11)
!2981 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !2971, file: !12, line: 342, baseType: !275, size: 32, align: 32, offset: 288)
!2982 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !2971, file: !12, line: 345, baseType: !2983, size: 32, align: 32, offset: 320)
!2983 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !12, line: 111, baseType: !16)
!2984 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !2971, file: !12, line: 375, baseType: !275, size: 32, align: 32, offset: 352)
!2985 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !2971, file: !12, line: 384, baseType: !275, size: 32, align: 32, offset: 384)
!2986 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !2971, file: !12, line: 385, baseType: !275, size: 32, align: 32, offset: 416)
!2987 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !2971, file: !12, line: 386, baseType: !275, size: 32, align: 32, offset: 448)
!2988 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !2971, file: !12, line: 387, baseType: !275, size: 32, align: 32, offset: 480)
!2989 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !2971, file: !12, line: 388, baseType: !275, size: 32, align: 32, offset: 512)
!2990 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !2971, file: !12, line: 389, baseType: !275, size: 32, align: 32, offset: 544)
!2991 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !2971, file: !12, line: 390, baseType: !275, size: 32, align: 32, offset: 576)
!2992 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !2971, file: !12, line: 391, baseType: !275, size: 32, align: 32, offset: 608)
!2993 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !2971, file: !12, line: 392, baseType: !464, size: 32, align: 32, offset: 640)
!2994 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !2971, file: !12, line: 393, baseType: !464, size: 32, align: 32, offset: 672)
!2995 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !2971, file: !12, line: 394, baseType: !464, size: 32, align: 32, offset: 704)
!2996 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !2971, file: !12, line: 395, baseType: !464, size: 32, align: 32, offset: 736)
!2997 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !2971, file: !12, line: 396, baseType: !164, size: 64, align: 64, offset: 768)
!2998 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !2971, file: !12, line: 397, baseType: !164, size: 64, align: 64, offset: 832)
!2999 = !DILocation(line: 1916, column: 20, scope: !608)
!3000 = !DILocalVariable(name: "r", scope: !608, file: !1, line: 1917, type: !63)
!3001 = !DILocation(line: 1917, column: 6, scope: !608)
!3002 = !DILocation(line: 1919, column: 6, scope: !3003)
!3003 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1919, column: 6)
!3004 = !DILocation(line: 1919, column: 14, scope: !3003)
!3005 = !DILocation(line: 1919, column: 6, scope: !608)
!3006 = !DILocation(line: 1920, column: 19, scope: !3003)
!3007 = !DILocation(line: 1920, column: 22, scope: !3003)
!3008 = !DILocation(line: 1920, column: 3, scope: !3003)
!3009 = !DILocation(line: 1921, column: 9, scope: !608)
!3010 = !DILocation(line: 1921, column: 7, scope: !608)
!3011 = !DILocation(line: 1922, column: 6, scope: !3012)
!3012 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1922, column: 6)
!3013 = !DILocation(line: 1922, column: 11, scope: !3012)
!3014 = !DILocation(line: 1922, column: 6, scope: !608)
!3015 = !DILocation(line: 1923, column: 21, scope: !3016)
!3016 = distinct !DILexicalBlock(scope: !3012, file: !1, line: 1922, column: 20)
!3017 = !DILocation(line: 1923, column: 3, scope: !3016)
!3018 = !DILocation(line: 1925, column: 3, scope: !3016)
!3019 = !DILocation(line: 1927, column: 32, scope: !608)
!3020 = !DILocation(line: 1927, column: 36, scope: !608)
!3021 = !DILocation(line: 1927, column: 16, scope: !608)
!3022 = !DILocation(line: 1927, column: 14, scope: !608)
!3023 = !DILocation(line: 1928, column: 6, scope: !3024)
!3024 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1928, column: 6)
!3025 = !DILocation(line: 1928, column: 12, scope: !3024)
!3026 = !DILocation(line: 1928, column: 6, scope: !608)
!3027 = !DILocation(line: 1929, column: 9, scope: !3024)
!3028 = !DILocation(line: 1929, column: 3, scope: !3024)
!3029 = !DILocation(line: 1930, column: 34, scope: !3030)
!3030 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1930, column: 6)
!3031 = !DILocation(line: 1930, column: 6, scope: !3030)
!3032 = !DILocation(line: 1930, column: 6, scope: !608)
!3033 = !DILocation(line: 1931, column: 8, scope: !3034)
!3034 = distinct !DILexicalBlock(scope: !3030, file: !1, line: 1930, column: 42)
!3035 = !DILocation(line: 1931, column: 3, scope: !3034)
!3036 = !DILocation(line: 1932, column: 3, scope: !3034)
!3037 = !DILocation(line: 1932, column: 11, scope: !3034)
!3038 = !DILocation(line: 1932, column: 23, scope: !3034)
!3039 = !DILocation(line: 1933, column: 21, scope: !3034)
!3040 = !DILocation(line: 1933, column: 3, scope: !3034)
!3041 = !DILocation(line: 1935, column: 3, scope: !3034)
!3042 = !DILocation(line: 1937, column: 22, scope: !608)
!3043 = !DILocation(line: 1937, column: 2, scope: !608)
!3044 = !DILocation(line: 1937, column: 17, scope: !608)
!3045 = !DILocation(line: 1937, column: 20, scope: !608)
!3046 = !DILocation(line: 1938, column: 27, scope: !608)
!3047 = !DILocation(line: 1938, column: 2, scope: !608)
!3048 = !DILocation(line: 1938, column: 17, scope: !608)
!3049 = !DILocation(line: 1938, column: 25, scope: !608)
!3050 = !DILocation(line: 1939, column: 2, scope: !608)
!3051 = !DILocation(line: 1939, column: 17, scope: !608)
!3052 = !DILocation(line: 1939, column: 20, scope: !608)
!3053 = !DILocation(line: 1941, column: 29, scope: !608)
!3054 = !DILocation(line: 1941, column: 37, scope: !608)
!3055 = !DILocation(line: 1941, column: 49, scope: !608)
!3056 = !DILocation(line: 1941, column: 6, scope: !608)
!3057 = !DILocation(line: 1941, column: 4, scope: !608)
!3058 = !DILocation(line: 1942, column: 6, scope: !3059)
!3059 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1942, column: 6)
!3060 = !DILocation(line: 1942, column: 8, scope: !3059)
!3061 = !DILocation(line: 1942, column: 6, scope: !608)
!3062 = !DILocation(line: 1943, column: 8, scope: !3063)
!3063 = distinct !DILexicalBlock(scope: !3059, file: !1, line: 1942, column: 20)
!3064 = !DILocation(line: 1943, column: 3, scope: !3063)
!3065 = !DILocation(line: 1944, column: 3, scope: !3063)
!3066 = !DILocation(line: 1944, column: 11, scope: !3063)
!3067 = !DILocation(line: 1944, column: 23, scope: !3063)
!3068 = !DILocation(line: 1945, column: 21, scope: !3063)
!3069 = !DILocation(line: 1945, column: 3, scope: !3063)
!3070 = !DILocation(line: 1947, column: 3, scope: !3063)
!3071 = !DILocation(line: 1949, column: 6, scope: !3072)
!3072 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1949, column: 6)
!3073 = !DILocation(line: 1949, column: 14, scope: !3072)
!3074 = !DILocation(line: 1949, column: 6, scope: !608)
!3075 = !DILocation(line: 1950, column: 26, scope: !3076)
!3076 = distinct !DILexicalBlock(scope: !3072, file: !1, line: 1949, column: 25)
!3077 = !DILocation(line: 1950, column: 34, scope: !3076)
!3078 = !DILocation(line: 1950, column: 19, scope: !3076)
!3079 = !DILocation(line: 1950, column: 3, scope: !3076)
!3080 = !DILocation(line: 1950, column: 11, scope: !3076)
!3081 = !DILocation(line: 1950, column: 17, scope: !3076)
!3082 = !DILocation(line: 1951, column: 7, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !3076, file: !1, line: 1951, column: 7)
!3084 = !DILocation(line: 1951, column: 15, scope: !3083)
!3085 = !DILocation(line: 1951, column: 21, scope: !3083)
!3086 = !DILocation(line: 1951, column: 7, scope: !3076)
!3087 = !DILocation(line: 1952, column: 9, scope: !3088)
!3088 = distinct !DILexicalBlock(scope: !3083, file: !1, line: 1951, column: 30)
!3089 = !DILocation(line: 1952, column: 4, scope: !3088)
!3090 = !DILocation(line: 1953, column: 4, scope: !3088)
!3091 = !DILocation(line: 1953, column: 12, scope: !3088)
!3092 = !DILocation(line: 1953, column: 24, scope: !3088)
!3093 = !DILocation(line: 1954, column: 22, scope: !3088)
!3094 = !DILocation(line: 1954, column: 4, scope: !3088)
!3095 = !DILocation(line: 1956, column: 4, scope: !3088)
!3096 = !DILocation(line: 1958, column: 30, scope: !3076)
!3097 = !DILocation(line: 1958, column: 44, scope: !3076)
!3098 = !DILocation(line: 1958, column: 52, scope: !3076)
!3099 = !DILocation(line: 1958, column: 7, scope: !3076)
!3100 = !DILocation(line: 1958, column: 5, scope: !3076)
!3101 = !DILocation(line: 1959, column: 7, scope: !3102)
!3102 = distinct !DILexicalBlock(scope: !3076, file: !1, line: 1959, column: 7)
!3103 = !DILocation(line: 1959, column: 9, scope: !3102)
!3104 = !DILocation(line: 1959, column: 7, scope: !3076)
!3105 = !DILocation(line: 1960, column: 9, scope: !3106)
!3106 = distinct !DILexicalBlock(scope: !3102, file: !1, line: 1959, column: 21)
!3107 = !DILocation(line: 1960, column: 4, scope: !3106)
!3108 = !DILocation(line: 1961, column: 4, scope: !3106)
!3109 = !DILocation(line: 1961, column: 12, scope: !3106)
!3110 = !DILocation(line: 1961, column: 24, scope: !3106)
!3111 = !DILocation(line: 1962, column: 22, scope: !3106)
!3112 = !DILocation(line: 1962, column: 4, scope: !3106)
!3113 = !DILocation(line: 1964, column: 4, scope: !3106)
!3114 = !DILocation(line: 1966, column: 2, scope: !3076)
!3115 = !DILocation(line: 1968, column: 3, scope: !608)
!3116 = !DILocation(line: 1968, column: 10, scope: !608)
!3117 = !DILocation(line: 1969, column: 23, scope: !608)
!3118 = !DILocation(line: 1969, column: 29, scope: !608)
!3119 = !DILocation(line: 1969, column: 6, scope: !608)
!3120 = !DILocation(line: 1969, column: 4, scope: !608)
!3121 = !DILocation(line: 1970, column: 10, scope: !608)
!3122 = !DILocation(line: 1970, column: 2, scope: !608)
!3123 = !DILocation(line: 1972, column: 25, scope: !3124)
!3124 = distinct !DILexicalBlock(scope: !608, file: !1, line: 1970, column: 13)
!3125 = !DILocation(line: 1972, column: 3, scope: !3124)
!3126 = !DILocation(line: 1972, column: 11, scope: !3124)
!3127 = !DILocation(line: 1972, column: 23, scope: !3124)
!3128 = !DILocation(line: 1973, column: 3, scope: !3124)
!3129 = !DILocation(line: 1973, column: 11, scope: !3124)
!3130 = !DILocation(line: 1973, column: 17, scope: !3124)
!3131 = !DILocation(line: 1974, column: 3, scope: !3124)
!3132 = !DILocation(line: 1974, column: 11, scope: !3124)
!3133 = !DILocation(line: 1974, column: 16, scope: !3124)
!3134 = !DILocation(line: 1975, column: 3, scope: !3124)
!3135 = !DILocation(line: 1975, column: 11, scope: !3124)
!3136 = !DILocation(line: 1975, column: 15, scope: !3124)
!3137 = !DILocation(line: 1976, column: 5, scope: !3124)
!3138 = !DILocation(line: 1977, column: 3, scope: !3124)
!3139 = !DILocation(line: 1979, column: 8, scope: !3124)
!3140 = !DILocation(line: 1979, column: 3, scope: !3124)
!3141 = !DILocation(line: 1980, column: 3, scope: !3124)
!3142 = !DILocation(line: 1980, column: 11, scope: !3124)
!3143 = !DILocation(line: 1980, column: 23, scope: !3124)
!3144 = !DILocation(line: 1981, column: 21, scope: !3124)
!3145 = !DILocation(line: 1981, column: 3, scope: !3124)
!3146 = !DILocation(line: 1984, column: 5, scope: !3124)
!3147 = !DILocation(line: 1985, column: 3, scope: !3124)
!3148 = !DILocation(line: 1987, column: 8, scope: !3124)
!3149 = !DILocation(line: 1987, column: 3, scope: !3124)
!3150 = !DILocation(line: 1988, column: 3, scope: !3124)
!3151 = !DILocation(line: 1988, column: 11, scope: !3124)
!3152 = !DILocation(line: 1988, column: 23, scope: !3124)
!3153 = !DILocation(line: 1989, column: 21, scope: !3124)
!3154 = !DILocation(line: 1989, column: 3, scope: !3124)
!3155 = !DILocation(line: 1992, column: 5, scope: !3124)
!3156 = !DILocation(line: 1993, column: 3, scope: !3124)
!3157 = !DILocation(line: 1995, column: 10, scope: !608)
!3158 = !DILocation(line: 1995, column: 2, scope: !608)
!3159 = !DILocation(line: 1996, column: 1, scope: !608)
!3160 = !DILocalVariable(name: "a", arg: 1, scope: !611, file: !1, line: 2015, type: !64)
!3161 = !DILocation(line: 2015, column: 39, scope: !611)
!3162 = !DILocalVariable(name: "lastrm", arg: 2, scope: !611, file: !1, line: 2016, type: !312)
!3163 = !DILocation(line: 2016, column: 24, scope: !611)
!3164 = !DILocalVariable(name: "action", arg: 3, scope: !611, file: !1, line: 2016, type: !3)
!3165 = !DILocation(line: 2016, column: 48, scope: !611)
!3166 = !DILocalVariable(name: "strm", scope: !611, file: !1, line: 2018, type: !430)
!3167 = !DILocation(line: 2018, column: 15, scope: !611)
!3168 = !DILocalVariable(name: "r", scope: !611, file: !1, line: 2019, type: !63)
!3169 = !DILocation(line: 2019, column: 6, scope: !611)
!3170 = !DILocation(line: 2021, column: 24, scope: !611)
!3171 = !DILocation(line: 2021, column: 32, scope: !611)
!3172 = !DILocation(line: 2021, column: 9, scope: !611)
!3173 = !DILocation(line: 2021, column: 7, scope: !611)
!3174 = !DILocation(line: 2022, column: 18, scope: !611)
!3175 = !DILocation(line: 2022, column: 26, scope: !611)
!3176 = !DILocation(line: 2022, column: 2, scope: !611)
!3177 = !DILocation(line: 2022, column: 8, scope: !611)
!3178 = !DILocation(line: 2022, column: 16, scope: !611)
!3179 = !DILocation(line: 2023, column: 19, scope: !611)
!3180 = !DILocation(line: 2023, column: 27, scope: !611)
!3181 = !DILocation(line: 2023, column: 2, scope: !611)
!3182 = !DILocation(line: 2023, column: 8, scope: !611)
!3183 = !DILocation(line: 2023, column: 17, scope: !611)
!3184 = !DILocation(line: 2024, column: 19, scope: !611)
!3185 = !DILocation(line: 2024, column: 27, scope: !611)
!3186 = !DILocation(line: 2024, column: 2, scope: !611)
!3187 = !DILocation(line: 2024, column: 8, scope: !611)
!3188 = !DILocation(line: 2024, column: 17, scope: !611)
!3189 = !DILocation(line: 2025, column: 19, scope: !611)
!3190 = !DILocation(line: 2025, column: 27, scope: !611)
!3191 = !DILocation(line: 2025, column: 2, scope: !611)
!3192 = !DILocation(line: 2025, column: 8, scope: !611)
!3193 = !DILocation(line: 2025, column: 17, scope: !611)
!3194 = !DILocation(line: 2026, column: 20, scope: !611)
!3195 = !DILocation(line: 2026, column: 28, scope: !611)
!3196 = !DILocation(line: 2026, column: 2, scope: !611)
!3197 = !DILocation(line: 2026, column: 8, scope: !611)
!3198 = !DILocation(line: 2026, column: 18, scope: !611)
!3199 = !DILocation(line: 2027, column: 20, scope: !611)
!3200 = !DILocation(line: 2027, column: 28, scope: !611)
!3201 = !DILocation(line: 2027, column: 2, scope: !611)
!3202 = !DILocation(line: 2027, column: 8, scope: !611)
!3203 = !DILocation(line: 2027, column: 18, scope: !611)
!3204 = !DILocation(line: 2028, column: 16, scope: !611)
!3205 = !DILocation(line: 2029, column: 7, scope: !611)
!3206 = !DILocation(line: 2029, column: 14, scope: !611)
!3207 = !DILocation(line: 2029, column: 6, scope: !611)
!3208 = !DILocation(line: 2028, column: 6, scope: !611)
!3209 = !DILocation(line: 2028, column: 4, scope: !611)
!3210 = !DILocation(line: 2030, column: 20, scope: !611)
!3211 = !DILocation(line: 2030, column: 26, scope: !611)
!3212 = !DILocation(line: 2030, column: 2, scope: !611)
!3213 = !DILocation(line: 2030, column: 10, scope: !611)
!3214 = !DILocation(line: 2030, column: 18, scope: !611)
!3215 = !DILocation(line: 2031, column: 21, scope: !611)
!3216 = !DILocation(line: 2031, column: 27, scope: !611)
!3217 = !DILocation(line: 2031, column: 2, scope: !611)
!3218 = !DILocation(line: 2031, column: 10, scope: !611)
!3219 = !DILocation(line: 2031, column: 19, scope: !611)
!3220 = !DILocation(line: 2032, column: 21, scope: !611)
!3221 = !DILocation(line: 2032, column: 27, scope: !611)
!3222 = !DILocation(line: 2032, column: 2, scope: !611)
!3223 = !DILocation(line: 2032, column: 10, scope: !611)
!3224 = !DILocation(line: 2032, column: 19, scope: !611)
!3225 = !DILocation(line: 2033, column: 21, scope: !611)
!3226 = !DILocation(line: 2033, column: 27, scope: !611)
!3227 = !DILocation(line: 2033, column: 2, scope: !611)
!3228 = !DILocation(line: 2033, column: 10, scope: !611)
!3229 = !DILocation(line: 2033, column: 19, scope: !611)
!3230 = !DILocation(line: 2034, column: 22, scope: !611)
!3231 = !DILocation(line: 2034, column: 28, scope: !611)
!3232 = !DILocation(line: 2034, column: 2, scope: !611)
!3233 = !DILocation(line: 2034, column: 10, scope: !611)
!3234 = !DILocation(line: 2034, column: 20, scope: !611)
!3235 = !DILocation(line: 2035, column: 22, scope: !611)
!3236 = !DILocation(line: 2035, column: 28, scope: !611)
!3237 = !DILocation(line: 2035, column: 2, scope: !611)
!3238 = !DILocation(line: 2035, column: 10, scope: !611)
!3239 = !DILocation(line: 2035, column: 20, scope: !611)
!3240 = !DILocation(line: 2036, column: 10, scope: !611)
!3241 = !DILocation(line: 2036, column: 2, scope: !611)
!3242 = !DILocation(line: 2039, column: 3, scope: !3243)
!3243 = distinct !DILexicalBlock(scope: !611, file: !1, line: 2036, column: 13)
!3244 = !DILocation(line: 2042, column: 3, scope: !3243)
!3245 = !DILocation(line: 2044, column: 21, scope: !3243)
!3246 = !DILocation(line: 2047, column: 34, scope: !3243)
!3247 = !DILocation(line: 2047, column: 20, scope: !3243)
!3248 = !DILocation(line: 2047, column: 40, scope: !3243)
!3249 = !DILocation(line: 2047, column: 54, scope: !3243)
!3250 = !DILocation(line: 2048, column: 4, scope: !3243)
!3251 = !DILocation(line: 2044, column: 3, scope: !3243)
!3252 = !DILocation(line: 2049, column: 3, scope: !3243)
!3253 = !DILocation(line: 2052, column: 21, scope: !3243)
!3254 = !DILocation(line: 2054, column: 47, scope: !3243)
!3255 = !DILocation(line: 2052, column: 3, scope: !3243)
!3256 = !DILocation(line: 2055, column: 3, scope: !3243)
!3257 = !DILocation(line: 2057, column: 1, scope: !611)
!3258 = !DILocalVariable(name: "a", arg: 1, scope: !612, file: !1, line: 2060, type: !64)
!3259 = !DILocation(line: 2060, column: 38, scope: !612)
!3260 = !DILocalVariable(name: "lastrm", arg: 2, scope: !612, file: !1, line: 2060, type: !312)
!3261 = !DILocation(line: 2060, column: 60, scope: !612)
!3262 = !DILocalVariable(name: "strm", scope: !612, file: !1, line: 2062, type: !430)
!3263 = !DILocation(line: 2062, column: 15, scope: !612)
!3264 = !DILocation(line: 2064, column: 8, scope: !612)
!3265 = !DILocation(line: 2065, column: 24, scope: !612)
!3266 = !DILocation(line: 2065, column: 32, scope: !612)
!3267 = !DILocation(line: 2065, column: 9, scope: !612)
!3268 = !DILocation(line: 2065, column: 7, scope: !612)
!3269 = !DILocation(line: 2066, column: 11, scope: !612)
!3270 = !DILocation(line: 2066, column: 2, scope: !612)
!3271 = !DILocation(line: 2067, column: 7, scope: !612)
!3272 = !DILocation(line: 2067, column: 2, scope: !612)
!3273 = !DILocation(line: 2068, column: 2, scope: !612)
!3274 = !DILocation(line: 2068, column: 10, scope: !612)
!3275 = !DILocation(line: 2068, column: 16, scope: !612)
!3276 = !DILocation(line: 2069, column: 2, scope: !612)
!3277 = !DILocation(line: 2069, column: 10, scope: !612)
!3278 = !DILocation(line: 2069, column: 22, scope: !612)
!3279 = !DILocation(line: 2070, column: 2, scope: !612)
!3280 = !DILocalVariable(name: "pp", arg: 1, scope: !617, file: !618, line: 177, type: !164)
!3281 = !DILocation(line: 177, column: 23, scope: !617)
!3282 = !DILocalVariable(name: "u", arg: 2, scope: !617, file: !618, line: 177, type: !275)
!3283 = !DILocation(line: 177, column: 36, scope: !617)
!3284 = !DILocalVariable(name: "p", scope: !617, file: !618, line: 179, type: !420)
!3285 = !DILocation(line: 179, column: 17, scope: !617)
!3286 = !DILocation(line: 179, column: 38, scope: !617)
!3287 = !DILocation(line: 181, column: 9, scope: !617)
!3288 = !DILocation(line: 181, column: 11, scope: !617)
!3289 = !DILocation(line: 181, column: 2, scope: !617)
!3290 = !DILocation(line: 181, column: 7, scope: !617)
!3291 = !DILocation(line: 182, column: 10, scope: !617)
!3292 = !DILocation(line: 182, column: 12, scope: !617)
!3293 = !DILocation(line: 182, column: 18, scope: !617)
!3294 = !DILocation(line: 182, column: 9, scope: !617)
!3295 = !DILocation(line: 182, column: 2, scope: !617)
!3296 = !DILocation(line: 182, column: 7, scope: !617)
!3297 = !DILocation(line: 183, column: 10, scope: !617)
!3298 = !DILocation(line: 183, column: 12, scope: !617)
!3299 = !DILocation(line: 183, column: 19, scope: !617)
!3300 = !DILocation(line: 183, column: 9, scope: !617)
!3301 = !DILocation(line: 183, column: 2, scope: !617)
!3302 = !DILocation(line: 183, column: 7, scope: !617)
!3303 = !DILocation(line: 184, column: 10, scope: !617)
!3304 = !DILocation(line: 184, column: 12, scope: !617)
!3305 = !DILocation(line: 184, column: 19, scope: !617)
!3306 = !DILocation(line: 184, column: 9, scope: !617)
!3307 = !DILocation(line: 184, column: 2, scope: !617)
!3308 = !DILocation(line: 184, column: 7, scope: !617)
!3309 = !DILocation(line: 185, column: 1, scope: !617)
!3310 = !DILocalVariable(name: "p", arg: 1, scope: !625, file: !1, line: 2112, type: !164)
!3311 = !DILocation(line: 2112, column: 18, scope: !625)
!3312 = !DILocalVariable(name: "b", arg: 2, scope: !625, file: !1, line: 2112, type: !362)
!3313 = !DILocation(line: 2112, column: 26, scope: !625)
!3314 = !DILocalVariable(name: "a", scope: !625, file: !1, line: 2114, type: !44)
!3315 = !DILocation(line: 2114, column: 24, scope: !625)
!3316 = !DILocation(line: 2114, column: 41, scope: !625)
!3317 = !DILocation(line: 2114, column: 29, scope: !625)
!3318 = !DILocation(line: 2114, column: 45, scope: !625)
!3319 = !DILocalVariable(name: "zip", scope: !625, file: !1, line: 2115, type: !232)
!3320 = !DILocation(line: 2115, column: 16, scope: !625)
!3321 = !DILocation(line: 2115, column: 39, scope: !625)
!3322 = !DILocation(line: 2115, column: 42, scope: !625)
!3323 = !DILocation(line: 2115, column: 22, scope: !625)
!3324 = !DILocalVariable(name: "lastrm", scope: !625, file: !1, line: 2116, type: !312)
!3325 = !DILocation(line: 2116, column: 21, scope: !625)
!3326 = !DILocation(line: 2116, column: 32, scope: !625)
!3327 = !DILocation(line: 2116, column: 37, scope: !625)
!3328 = !DILocalVariable(name: "strm", scope: !625, file: !1, line: 2117, type: !477)
!3329 = !DILocation(line: 2117, column: 22, scope: !625)
!3330 = !DILocation(line: 2119, column: 6, scope: !3331)
!3331 = distinct !DILexicalBlock(scope: !625, file: !1, line: 2119, column: 6)
!3332 = !DILocation(line: 2119, column: 14, scope: !3331)
!3333 = !DILocation(line: 2119, column: 6, scope: !625)
!3334 = !DILocation(line: 2120, column: 25, scope: !3335)
!3335 = distinct !DILexicalBlock(scope: !3331, file: !1, line: 2119, column: 25)
!3336 = !DILocation(line: 2120, column: 4, scope: !3335)
!3337 = !DILocation(line: 2120, column: 12, scope: !3335)
!3338 = !DILocation(line: 2120, column: 20, scope: !3335)
!3339 = !DILocation(line: 2120, column: 23, scope: !3335)
!3340 = !DILocation(line: 2121, column: 3, scope: !3335)
!3341 = !DILocation(line: 2121, column: 11, scope: !3335)
!3342 = !DILocation(line: 2121, column: 20, scope: !3335)
!3343 = !DILocation(line: 2122, column: 3, scope: !3335)
!3344 = !DILocation(line: 2122, column: 11, scope: !3335)
!3345 = !DILocation(line: 2122, column: 20, scope: !3335)
!3346 = !DILocation(line: 2123, column: 3, scope: !3335)
!3347 = !DILocation(line: 2125, column: 31, scope: !625)
!3348 = !DILocation(line: 2125, column: 39, scope: !625)
!3349 = !DILocation(line: 2125, column: 9, scope: !625)
!3350 = !DILocation(line: 2125, column: 7, scope: !625)
!3351 = !DILocation(line: 2126, column: 6, scope: !3352)
!3352 = distinct !DILexicalBlock(scope: !625, file: !1, line: 2126, column: 6)
!3353 = !DILocation(line: 2126, column: 12, scope: !3352)
!3354 = !DILocation(line: 2126, column: 23, scope: !3352)
!3355 = !DILocation(line: 2126, column: 29, scope: !3352)
!3356 = !DILocation(line: 2126, column: 21, scope: !3352)
!3357 = !DILocation(line: 2126, column: 6, scope: !625)
!3358 = !DILocation(line: 2127, column: 23, scope: !3359)
!3359 = distinct !DILexicalBlock(scope: !3352, file: !1, line: 2126, column: 39)
!3360 = !DILocation(line: 2127, column: 4, scope: !3359)
!3361 = !DILocation(line: 2127, column: 10, scope: !3359)
!3362 = !DILocation(line: 2127, column: 18, scope: !3359)
!3363 = !DILocation(line: 2127, column: 21, scope: !3359)
!3364 = !DILocation(line: 2128, column: 3, scope: !3359)
!3365 = !DILocation(line: 2128, column: 9, scope: !3359)
!3366 = !DILocation(line: 2128, column: 19, scope: !3359)
!3367 = !DILocation(line: 2129, column: 2, scope: !3359)
!3368 = !DILocation(line: 2130, column: 1, scope: !625)
!3369 = !DILocalVariable(name: "a", arg: 1, scope: !626, file: !1, line: 2196, type: !64)
!3370 = !DILocation(line: 2196, column: 39, scope: !626)
!3371 = !DILocalVariable(name: "lastrm", arg: 2, scope: !626, file: !1, line: 2197, type: !312)
!3372 = !DILocation(line: 2197, column: 24, scope: !626)
!3373 = !DILocalVariable(name: "action", arg: 3, scope: !626, file: !1, line: 2197, type: !3)
!3374 = !DILocation(line: 2197, column: 48, scope: !626)
!3375 = !DILocalVariable(name: "strm", scope: !626, file: !1, line: 2199, type: !477)
!3376 = !DILocation(line: 2199, column: 22, scope: !626)
!3377 = !DILocation(line: 2201, column: 8, scope: !626)
!3378 = !DILocation(line: 2203, column: 31, scope: !626)
!3379 = !DILocation(line: 2203, column: 39, scope: !626)
!3380 = !DILocation(line: 2203, column: 9, scope: !626)
!3381 = !DILocation(line: 2203, column: 7, scope: !626)
!3382 = !DILocation(line: 2206, column: 6, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !626, file: !1, line: 2206, column: 6)
!3384 = !DILocation(line: 2206, column: 12, scope: !3383)
!3385 = !DILocation(line: 2206, column: 6, scope: !626)
!3386 = !DILocalVariable(name: "p", scope: !3387, file: !1, line: 2207, type: !256)
!3387 = distinct !DILexicalBlock(scope: !3383, file: !1, line: 2206, column: 24)
!3388 = !DILocation(line: 2207, column: 12, scope: !3387)
!3389 = !DILocation(line: 2207, column: 16, scope: !3387)
!3390 = !DILocation(line: 2207, column: 22, scope: !3387)
!3391 = !DILocation(line: 2207, column: 33, scope: !3387)
!3392 = !DILocation(line: 2207, column: 39, scope: !3387)
!3393 = !DILocation(line: 2207, column: 31, scope: !3387)
!3394 = !DILocation(line: 2208, column: 3, scope: !3387)
!3395 = !DILocation(line: 2208, column: 10, scope: !3396)
!3396 = !DILexicalBlockFile(scope: !3387, file: !1, discriminator: 1)
!3397 = !DILocation(line: 2208, column: 18, scope: !3396)
!3398 = !DILocation(line: 2208, column: 28, scope: !3396)
!3399 = !DILocation(line: 2208, column: 31, scope: !3400)
!3400 = !DILexicalBlockFile(scope: !3387, file: !1, discriminator: 2)
!3401 = !DILocation(line: 2208, column: 37, scope: !3400)
!3402 = !DILocation(line: 2208, column: 28, scope: !3400)
!3403 = !DILocation(line: 2208, column: 3, scope: !3404)
!3404 = !DILexicalBlockFile(scope: !3387, file: !1, discriminator: 3)
!3405 = !DILocation(line: 2209, column: 28, scope: !3406)
!3406 = distinct !DILexicalBlock(scope: !3387, file: !1, line: 2208, column: 49)
!3407 = !DILocation(line: 2209, column: 26, scope: !3406)
!3408 = !DILocation(line: 2209, column: 5, scope: !3406)
!3409 = !DILocation(line: 2209, column: 13, scope: !3406)
!3410 = !DILocation(line: 2209, column: 21, scope: !3406)
!3411 = !DILocation(line: 2209, column: 24, scope: !3406)
!3412 = !DILocation(line: 2210, column: 4, scope: !3406)
!3413 = !DILocation(line: 2210, column: 12, scope: !3406)
!3414 = !DILocation(line: 2210, column: 21, scope: !3406)
!3415 = !DILocation(line: 2211, column: 4, scope: !3406)
!3416 = !DILocation(line: 2211, column: 12, scope: !3406)
!3417 = !DILocation(line: 2211, column: 21, scope: !3406)
!3418 = !DILocation(line: 2212, column: 4, scope: !3406)
!3419 = !DILocation(line: 2212, column: 10, scope: !3406)
!3420 = !DILocation(line: 2212, column: 20, scope: !3406)
!3421 = !DILocation(line: 2208, column: 3, scope: !3422)
!3422 = !DILexicalBlockFile(scope: !3387, file: !1, discriminator: 4)
!3423 = !DILocation(line: 2214, column: 7, scope: !3424)
!3424 = distinct !DILexicalBlock(scope: !3387, file: !1, line: 2214, column: 7)
!3425 = !DILocation(line: 2214, column: 13, scope: !3424)
!3426 = !DILocation(line: 2214, column: 7, scope: !3387)
!3427 = !DILocation(line: 2215, column: 4, scope: !3424)
!3428 = !DILocation(line: 2216, column: 7, scope: !3429)
!3429 = distinct !DILexicalBlock(scope: !3387, file: !1, line: 2216, column: 7)
!3430 = !DILocation(line: 2216, column: 13, scope: !3429)
!3431 = !DILocation(line: 2216, column: 18, scope: !3429)
!3432 = !DILocation(line: 2216, column: 7, scope: !3387)
!3433 = !DILocation(line: 2217, column: 4, scope: !3429)
!3434 = !DILocation(line: 2218, column: 20, scope: !3387)
!3435 = !DILocation(line: 2218, column: 26, scope: !3387)
!3436 = !DILocation(line: 2218, column: 3, scope: !3387)
!3437 = !DILocation(line: 2218, column: 9, scope: !3387)
!3438 = !DILocation(line: 2218, column: 18, scope: !3387)
!3439 = !DILocation(line: 2219, column: 2, scope: !3387)
!3440 = !DILocation(line: 2220, column: 2, scope: !626)
!3441 = !DILocation(line: 2220, column: 9, scope: !3442)
!3442 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 1)
!3443 = !DILocation(line: 2220, column: 17, scope: !3442)
!3444 = !DILocation(line: 2220, column: 26, scope: !3442)
!3445 = !DILocation(line: 2220, column: 29, scope: !3446)
!3446 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 2)
!3447 = !DILocation(line: 2220, column: 37, scope: !3446)
!3448 = !DILocation(line: 2220, column: 26, scope: !3446)
!3449 = !DILocation(line: 2220, column: 2, scope: !3450)
!3450 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 3)
!3451 = !DILocation(line: 2221, column: 29, scope: !3452)
!3452 = distinct !DILexicalBlock(scope: !626, file: !1, line: 2220, column: 48)
!3453 = !DILocation(line: 2222, column: 6, scope: !3452)
!3454 = !DILocation(line: 2222, column: 12, scope: !3452)
!3455 = !DILocation(line: 2222, column: 30, scope: !3452)
!3456 = !DILocation(line: 2222, column: 36, scope: !3452)
!3457 = !DILocation(line: 2223, column: 5, scope: !3452)
!3458 = !DILocation(line: 2223, column: 13, scope: !3452)
!3459 = !DILocation(line: 2223, column: 20, scope: !3452)
!3460 = !DILocation(line: 2223, column: 4, scope: !3452)
!3461 = !DILocation(line: 2221, column: 3, scope: !3452)
!3462 = !DILocation(line: 2224, column: 3, scope: !3452)
!3463 = !DILocation(line: 2224, column: 11, scope: !3452)
!3464 = !DILocation(line: 2224, column: 19, scope: !3452)
!3465 = !DILocation(line: 2225, column: 3, scope: !3452)
!3466 = !DILocation(line: 2225, column: 11, scope: !3452)
!3467 = !DILocation(line: 2225, column: 19, scope: !3452)
!3468 = !DILocation(line: 2220, column: 2, scope: !3469)
!3469 = !DILexicalBlockFile(scope: !626, file: !1, discriminator: 4)
!3470 = !DILocation(line: 2227, column: 6, scope: !3471)
!3471 = distinct !DILexicalBlock(scope: !626, file: !1, line: 2227, column: 6)
!3472 = !DILocation(line: 2227, column: 14, scope: !3471)
!3473 = !DILocation(line: 2227, column: 23, scope: !3471)
!3474 = !DILocation(line: 2227, column: 28, scope: !3471)
!3475 = !DILocation(line: 2227, column: 31, scope: !3476)
!3476 = !DILexicalBlockFile(scope: !3471, file: !1, discriminator: 1)
!3477 = !DILocation(line: 2227, column: 38, scope: !3476)
!3478 = !DILocation(line: 2227, column: 6, scope: !3476)
!3479 = !DILocation(line: 2228, column: 29, scope: !3480)
!3480 = distinct !DILexicalBlock(scope: !3471, file: !1, line: 2227, column: 59)
!3481 = !DILocation(line: 2229, column: 6, scope: !3480)
!3482 = !DILocation(line: 2229, column: 12, scope: !3480)
!3483 = !DILocation(line: 2228, column: 3, scope: !3480)
!3484 = !DILocation(line: 2230, column: 3, scope: !3480)
!3485 = !DILocation(line: 2230, column: 9, scope: !3480)
!3486 = !DILocation(line: 2230, column: 14, scope: !3480)
!3487 = !DILocation(line: 2232, column: 7, scope: !3488)
!3488 = distinct !DILexicalBlock(scope: !3480, file: !1, line: 2232, column: 7)
!3489 = !DILocation(line: 2232, column: 13, scope: !3488)
!3490 = !DILocation(line: 2232, column: 24, scope: !3488)
!3491 = !DILocation(line: 2232, column: 7, scope: !3480)
!3492 = !DILocation(line: 2233, column: 4, scope: !3488)
!3493 = !DILocation(line: 2234, column: 2, scope: !3480)
!3494 = !DILocation(line: 2235, column: 2, scope: !626)
!3495 = !DILocation(line: 2236, column: 1, scope: !626)
!3496 = !DILocalVariable(name: "a", arg: 1, scope: !627, file: !1, line: 2239, type: !64)
!3497 = !DILocation(line: 2239, column: 38, scope: !627)
!3498 = !DILocalVariable(name: "lastrm", arg: 2, scope: !627, file: !1, line: 2239, type: !312)
!3499 = !DILocation(line: 2239, column: 60, scope: !627)
!3500 = !DILocalVariable(name: "strm", scope: !627, file: !1, line: 2241, type: !477)
!3501 = !DILocation(line: 2241, column: 22, scope: !627)
!3502 = !DILocation(line: 2243, column: 8, scope: !627)
!3503 = !DILocation(line: 2245, column: 31, scope: !627)
!3504 = !DILocation(line: 2245, column: 39, scope: !627)
!3505 = !DILocation(line: 2245, column: 9, scope: !627)
!3506 = !DILocation(line: 2245, column: 7, scope: !627)
!3507 = !DILocation(line: 2246, column: 28, scope: !627)
!3508 = !DILocation(line: 2246, column: 40, scope: !627)
!3509 = !DILocation(line: 2246, column: 46, scope: !627)
!3510 = !DILocation(line: 2246, column: 2, scope: !627)
!3511 = !DILocation(line: 2247, column: 7, scope: !627)
!3512 = !DILocation(line: 2247, column: 13, scope: !627)
!3513 = !DILocation(line: 2247, column: 2, scope: !627)
!3514 = !DILocation(line: 2248, column: 7, scope: !627)
!3515 = !DILocation(line: 2248, column: 2, scope: !627)
!3516 = !DILocation(line: 2249, column: 2, scope: !627)
!3517 = !DILocation(line: 2249, column: 10, scope: !627)
!3518 = !DILocation(line: 2249, column: 22, scope: !627)
!3519 = !DILocation(line: 2250, column: 2, scope: !627)
!3520 = !DILocation(line: 2250, column: 10, scope: !627)
!3521 = !DILocation(line: 2250, column: 16, scope: !627)
!3522 = !DILocation(line: 2251, column: 2, scope: !627)
!3523 = !DILocalVariable(name: "p", arg: 1, scope: !621, file: !1, line: 2099, type: !164)
!3524 = !DILocation(line: 2099, column: 18, scope: !621)
!3525 = !DILocalVariable(name: "size", arg: 2, scope: !621, file: !1, line: 2099, type: !85)
!3526 = !DILocation(line: 2099, column: 28, scope: !621)
!3527 = !DILocation(line: 2101, column: 8, scope: !621)
!3528 = !DILocation(line: 2102, column: 16, scope: !621)
!3529 = !DILocation(line: 2102, column: 9, scope: !621)
!3530 = !DILocation(line: 2102, column: 2, scope: !621)
!3531 = !DILocalVariable(name: "p", arg: 1, scope: !624, file: !1, line: 2105, type: !164)
!3532 = !DILocation(line: 2105, column: 17, scope: !624)
!3533 = !DILocalVariable(name: "address", arg: 2, scope: !624, file: !1, line: 2105, type: !164)
!3534 = !DILocation(line: 2105, column: 26, scope: !624)
!3535 = !DILocation(line: 2107, column: 8, scope: !624)
!3536 = !DILocation(line: 2108, column: 7, scope: !624)
!3537 = !DILocation(line: 2108, column: 2, scope: !624)
!3538 = !DILocation(line: 2109, column: 1, scope: !624)
!3539 = !DILocalVariable(name: "a", arg: 1, scope: !629, file: !1, line: 1638, type: !64)
!3540 = !DILocation(line: 1638, column: 39, scope: !629)
!3541 = !DILocalVariable(name: "lastrm", arg: 2, scope: !629, file: !1, line: 1639, type: !312)
!3542 = !DILocation(line: 1639, column: 24, scope: !629)
!3543 = !DILocalVariable(name: "action", arg: 3, scope: !629, file: !1, line: 1639, type: !3)
!3544 = !DILocation(line: 1639, column: 48, scope: !629)
!3545 = !DILocalVariable(name: "bytes", scope: !629, file: !1, line: 1641, type: !85)
!3546 = !DILocation(line: 1641, column: 9, scope: !629)
!3547 = !DILocation(line: 1643, column: 8, scope: !629)
!3548 = !DILocation(line: 1644, column: 6, scope: !3549)
!3549 = distinct !DILexicalBlock(scope: !629, file: !1, line: 1644, column: 6)
!3550 = !DILocation(line: 1644, column: 14, scope: !3549)
!3551 = !DILocation(line: 1644, column: 26, scope: !3549)
!3552 = !DILocation(line: 1644, column: 34, scope: !3549)
!3553 = !DILocation(line: 1644, column: 24, scope: !3549)
!3554 = !DILocation(line: 1644, column: 6, scope: !629)
!3555 = !DILocation(line: 1645, column: 11, scope: !3549)
!3556 = !DILocation(line: 1645, column: 19, scope: !3549)
!3557 = !DILocation(line: 1645, column: 9, scope: !3549)
!3558 = !DILocation(line: 1645, column: 3, scope: !3549)
!3559 = !DILocation(line: 1647, column: 11, scope: !3549)
!3560 = !DILocation(line: 1647, column: 19, scope: !3549)
!3561 = !DILocation(line: 1647, column: 9, scope: !3549)
!3562 = !DILocation(line: 1648, column: 6, scope: !3563)
!3563 = distinct !DILexicalBlock(scope: !629, file: !1, line: 1648, column: 6)
!3564 = !DILocation(line: 1648, column: 6, scope: !629)
!3565 = !DILocation(line: 1649, column: 10, scope: !3566)
!3566 = distinct !DILexicalBlock(scope: !3563, file: !1, line: 1648, column: 13)
!3567 = !DILocation(line: 1649, column: 18, scope: !3566)
!3568 = !DILocation(line: 1649, column: 28, scope: !3566)
!3569 = !DILocation(line: 1649, column: 36, scope: !3566)
!3570 = !DILocation(line: 1649, column: 45, scope: !3566)
!3571 = !DILocation(line: 1649, column: 3, scope: !3566)
!3572 = !DILocation(line: 1650, column: 22, scope: !3566)
!3573 = !DILocation(line: 1650, column: 3, scope: !3566)
!3574 = !DILocation(line: 1650, column: 11, scope: !3566)
!3575 = !DILocation(line: 1650, column: 19, scope: !3566)
!3576 = !DILocation(line: 1651, column: 23, scope: !3566)
!3577 = !DILocation(line: 1651, column: 3, scope: !3566)
!3578 = !DILocation(line: 1651, column: 11, scope: !3566)
!3579 = !DILocation(line: 1651, column: 20, scope: !3566)
!3580 = !DILocation(line: 1652, column: 23, scope: !3566)
!3581 = !DILocation(line: 1652, column: 3, scope: !3566)
!3582 = !DILocation(line: 1652, column: 11, scope: !3566)
!3583 = !DILocation(line: 1652, column: 20, scope: !3566)
!3584 = !DILocation(line: 1653, column: 23, scope: !3566)
!3585 = !DILocation(line: 1653, column: 3, scope: !3566)
!3586 = !DILocation(line: 1653, column: 11, scope: !3566)
!3587 = !DILocation(line: 1653, column: 20, scope: !3566)
!3588 = !DILocation(line: 1654, column: 24, scope: !3566)
!3589 = !DILocation(line: 1654, column: 3, scope: !3566)
!3590 = !DILocation(line: 1654, column: 11, scope: !3566)
!3591 = !DILocation(line: 1654, column: 21, scope: !3566)
!3592 = !DILocation(line: 1655, column: 24, scope: !3566)
!3593 = !DILocation(line: 1655, column: 3, scope: !3566)
!3594 = !DILocation(line: 1655, column: 11, scope: !3566)
!3595 = !DILocation(line: 1655, column: 21, scope: !3566)
!3596 = !DILocation(line: 1656, column: 2, scope: !3566)
!3597 = !DILocation(line: 1657, column: 6, scope: !3598)
!3598 = distinct !DILexicalBlock(scope: !629, file: !1, line: 1657, column: 6)
!3599 = !DILocation(line: 1657, column: 13, scope: !3598)
!3600 = !DILocation(line: 1657, column: 33, scope: !3598)
!3601 = !DILocation(line: 1657, column: 36, scope: !3602)
!3602 = !DILexicalBlockFile(scope: !3598, file: !1, discriminator: 1)
!3603 = !DILocation(line: 1657, column: 44, scope: !3602)
!3604 = !DILocation(line: 1657, column: 53, scope: !3602)
!3605 = !DILocation(line: 1657, column: 6, scope: !3602)
!3606 = !DILocation(line: 1658, column: 3, scope: !3598)
!3607 = !DILocation(line: 1659, column: 2, scope: !629)
!3608 = !DILocation(line: 1660, column: 1, scope: !629)
!3609 = !DILocalVariable(name: "a", arg: 1, scope: !630, file: !1, line: 1663, type: !64)
!3610 = !DILocation(line: 1663, column: 38, scope: !630)
!3611 = !DILocalVariable(name: "lastrm", arg: 2, scope: !630, file: !1, line: 1663, type: !312)
!3612 = !DILocation(line: 1663, column: 60, scope: !630)
!3613 = !DILocation(line: 1665, column: 8, scope: !630)
!3614 = !DILocation(line: 1666, column: 2, scope: !630)
!3615 = !DILocation(line: 1666, column: 10, scope: !630)
!3616 = !DILocation(line: 1666, column: 16, scope: !630)
!3617 = !DILocation(line: 1667, column: 2, scope: !630)
!3618 = !DILocalVariable(name: "a", arg: 1, scope: !635, file: !1, line: 2308, type: !64)
!3619 = !DILocation(line: 2308, column: 34, scope: !635)
!3620 = !DILocalVariable(name: "lastrm", arg: 2, scope: !635, file: !1, line: 2308, type: !312)
!3621 = !DILocation(line: 2308, column: 56, scope: !635)
!3622 = !DILocalVariable(name: "action", arg: 3, scope: !635, file: !1, line: 2309, type: !3)
!3623 = !DILocation(line: 2309, column: 21, scope: !635)
!3624 = !DILocation(line: 2311, column: 6, scope: !3625)
!3625 = distinct !DILexicalBlock(scope: !635, file: !1, line: 2311, column: 6)
!3626 = !DILocation(line: 2311, column: 14, scope: !3625)
!3627 = !DILocation(line: 2311, column: 6, scope: !635)
!3628 = !DILocation(line: 2312, column: 11, scope: !3625)
!3629 = !DILocation(line: 2312, column: 19, scope: !3625)
!3630 = !DILocation(line: 2312, column: 24, scope: !3625)
!3631 = !DILocation(line: 2312, column: 27, scope: !3625)
!3632 = !DILocation(line: 2312, column: 35, scope: !3625)
!3633 = !DILocation(line: 2312, column: 3, scope: !3625)
!3634 = !DILocation(line: 2313, column: 2, scope: !635)
!3635 = !DILocation(line: 2314, column: 1, scope: !635)
!3636 = !DILocalVariable(name: "a", arg: 1, scope: !636, file: !1, line: 518, type: !44)
!3637 = !DILocation(line: 518, column: 37, scope: !636)
!3638 = !DILocalVariable(name: "buff", arg: 2, scope: !636, file: !1, line: 518, type: !83)
!3639 = !DILocation(line: 518, column: 52, scope: !636)
!3640 = !DILocalVariable(name: "s", arg: 3, scope: !636, file: !1, line: 518, type: !85)
!3641 = !DILocation(line: 518, column: 65, scope: !636)
!3642 = !DILocalVariable(name: "zip", scope: !636, file: !1, line: 520, type: !232)
!3643 = !DILocation(line: 520, column: 16, scope: !636)
!3644 = !DILocalVariable(name: "p", scope: !636, file: !1, line: 521, type: !155)
!3645 = !DILocation(line: 521, column: 23, scope: !636)
!3646 = !DILocalVariable(name: "ws", scope: !636, file: !1, line: 522, type: !78)
!3647 = !DILocation(line: 522, column: 10, scope: !636)
!3648 = !DILocation(line: 524, column: 24, scope: !636)
!3649 = !DILocation(line: 524, column: 27, scope: !636)
!3650 = !DILocation(line: 524, column: 8, scope: !636)
!3651 = !DILocation(line: 524, column: 6, scope: !636)
!3652 = !DILocation(line: 529, column: 6, scope: !3653)
!3653 = distinct !DILexicalBlock(scope: !636, file: !1, line: 529, column: 6)
!3654 = !DILocation(line: 529, column: 11, scope: !3653)
!3655 = !DILocation(line: 529, column: 19, scope: !3653)
!3656 = !DILocation(line: 529, column: 6, scope: !636)
!3657 = !DILocation(line: 530, column: 3, scope: !3658)
!3658 = distinct !DILexicalBlock(scope: !3653, file: !1, line: 529, column: 26)
!3659 = !DILocation(line: 530, column: 8, scope: !3658)
!3660 = !DILocation(line: 530, column: 20, scope: !3658)
!3661 = !DILocation(line: 531, column: 18, scope: !3658)
!3662 = !DILocation(line: 531, column: 3, scope: !3658)
!3663 = !DILocation(line: 531, column: 8, scope: !3658)
!3664 = !DILocation(line: 531, column: 16, scope: !3658)
!3665 = !DILocation(line: 532, column: 7, scope: !3666)
!3666 = distinct !DILexicalBlock(scope: !3658, file: !1, line: 532, column: 7)
!3667 = !DILocation(line: 532, column: 12, scope: !3666)
!3668 = !DILocation(line: 532, column: 20, scope: !3666)
!3669 = !DILocation(line: 532, column: 7, scope: !3658)
!3670 = !DILocation(line: 533, column: 23, scope: !3671)
!3671 = distinct !DILexicalBlock(scope: !3666, file: !1, line: 532, column: 25)
!3672 = !DILocation(line: 533, column: 26, scope: !3671)
!3673 = !DILocation(line: 533, column: 35, scope: !3671)
!3674 = !DILocation(line: 533, column: 4, scope: !3675)
!3675 = !DILexicalBlockFile(scope: !3671, file: !1, discriminator: 1)
!3676 = !DILocation(line: 535, column: 4, scope: !3671)
!3677 = !DILocation(line: 537, column: 2, scope: !3658)
!3678 = !DILocation(line: 539, column: 29, scope: !636)
!3679 = !DILocation(line: 539, column: 4, scope: !636)
!3680 = !DILocation(line: 540, column: 2, scope: !636)
!3681 = !DILocation(line: 540, column: 9, scope: !3682)
!3682 = !DILexicalBlockFile(scope: !636, file: !1, discriminator: 1)
!3683 = !DILocation(line: 540, column: 2, scope: !3682)
!3684 = !DILocation(line: 541, column: 14, scope: !3685)
!3685 = distinct !DILexicalBlock(scope: !636, file: !1, line: 540, column: 12)
!3686 = !DILocation(line: 541, column: 19, scope: !3685)
!3687 = !DILocation(line: 541, column: 28, scope: !3685)
!3688 = !DILocation(line: 541, column: 31, scope: !3685)
!3689 = !DILocation(line: 541, column: 8, scope: !3685)
!3690 = !DILocation(line: 541, column: 6, scope: !3685)
!3691 = !DILocation(line: 542, column: 7, scope: !3692)
!3692 = distinct !DILexicalBlock(scope: !3685, file: !1, line: 542, column: 7)
!3693 = !DILocation(line: 542, column: 10, scope: !3692)
!3694 = !DILocation(line: 542, column: 7, scope: !3685)
!3695 = !DILocation(line: 543, column: 24, scope: !3696)
!3696 = distinct !DILexicalBlock(scope: !3692, file: !1, line: 542, column: 15)
!3697 = !DILocation(line: 543, column: 27, scope: !3696)
!3698 = !DILocation(line: 543, column: 37, scope: !3696)
!3699 = !DILocation(line: 543, column: 4, scope: !3700)
!3700 = !DILexicalBlockFile(scope: !3696, file: !1, discriminator: 1)
!3701 = !DILocation(line: 545, column: 4, scope: !3696)
!3702 = !DILocation(line: 547, column: 8, scope: !3685)
!3703 = !DILocation(line: 547, column: 5, scope: !3685)
!3704 = !DILocation(line: 548, column: 8, scope: !3685)
!3705 = !DILocation(line: 548, column: 5, scope: !3685)
!3706 = !DILocation(line: 549, column: 23, scope: !3685)
!3707 = !DILocation(line: 549, column: 3, scope: !3685)
!3708 = !DILocation(line: 549, column: 8, scope: !3685)
!3709 = !DILocation(line: 549, column: 20, scope: !3685)
!3710 = !DILocation(line: 540, column: 2, scope: !3711)
!3711 = !DILexicalBlockFile(scope: !636, file: !1, discriminator: 2)
!3712 = !DILocation(line: 551, column: 2, scope: !636)
!3713 = !DILocation(line: 552, column: 1, scope: !636)
!3714 = !DILocalVariable(name: "a", arg: 1, scope: !642, file: !1, line: 1245, type: !44)
!3715 = !DILocation(line: 1245, column: 35, scope: !642)
!3716 = !DILocalVariable(name: "offset", arg: 2, scope: !642, file: !1, line: 1245, type: !237)
!3717 = !DILocation(line: 1245, column: 47, scope: !642)
!3718 = !DILocalVariable(name: "pack_size", arg: 3, scope: !642, file: !1, line: 1245, type: !237)
!3719 = !DILocation(line: 1245, column: 64, scope: !642)
!3720 = !DILocalVariable(name: "unpack_size", arg: 4, scope: !642, file: !1, line: 1246, type: !237)
!3721 = !DILocation(line: 1246, column: 14, scope: !642)
!3722 = !DILocalVariable(name: "codernum", arg: 5, scope: !642, file: !1, line: 1246, type: !63)
!3723 = !DILocation(line: 1246, column: 31, scope: !642)
!3724 = !DILocalVariable(name: "coders", arg: 6, scope: !642, file: !1, line: 1246, type: !645)
!3725 = !DILocation(line: 1246, column: 55, scope: !642)
!3726 = !DILocalVariable(name: "zip", scope: !642, file: !1, line: 1248, type: !232)
!3727 = !DILocation(line: 1248, column: 16, scope: !642)
!3728 = !DILocation(line: 1248, column: 38, scope: !642)
!3729 = !DILocation(line: 1248, column: 41, scope: !642)
!3730 = !DILocation(line: 1248, column: 22, scope: !642)
!3731 = !DILocalVariable(name: "file", scope: !642, file: !1, line: 1249, type: !239)
!3732 = !DILocation(line: 1249, column: 15, scope: !642)
!3733 = !DILocalVariable(name: "r", scope: !642, file: !1, line: 1250, type: !63)
!3734 = !DILocation(line: 1250, column: 6, scope: !642)
!3735 = !DILocalVariable(name: "b", scope: !642, file: !1, line: 1251, type: !257)
!3736 = !DILocation(line: 1251, column: 10, scope: !642)
!3737 = !DILocalVariable(name: "mask", scope: !642, file: !1, line: 1251, type: !257)
!3738 = !DILocation(line: 1251, column: 13, scope: !642)
!3739 = !DILocation(line: 1256, column: 17, scope: !642)
!3740 = !DILocation(line: 1256, column: 6, scope: !642)
!3741 = !DILocation(line: 1256, column: 4, scope: !642)
!3742 = !DILocation(line: 1257, column: 6, scope: !3743)
!3743 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1257, column: 6)
!3744 = !DILocation(line: 1257, column: 8, scope: !3743)
!3745 = !DILocation(line: 1257, column: 6, scope: !642)
!3746 = !DILocation(line: 1258, column: 11, scope: !3743)
!3747 = !DILocation(line: 1258, column: 3, scope: !3743)
!3748 = !DILocation(line: 1263, column: 6, scope: !3749)
!3749 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1263, column: 6)
!3750 = !DILocation(line: 1263, column: 11, scope: !3749)
!3751 = !DILocation(line: 1263, column: 6, scope: !642)
!3752 = !DILocation(line: 1267, column: 18, scope: !3753)
!3753 = distinct !DILexicalBlock(scope: !3749, file: !1, line: 1263, column: 40)
!3754 = !DILocation(line: 1267, column: 7, scope: !3753)
!3755 = !DILocation(line: 1267, column: 5, scope: !3753)
!3756 = !DILocation(line: 1268, column: 7, scope: !3757)
!3757 = distinct !DILexicalBlock(scope: !3753, file: !1, line: 1268, column: 7)
!3758 = !DILocation(line: 1268, column: 9, scope: !3757)
!3759 = !DILocation(line: 1268, column: 7, scope: !3753)
!3760 = !DILocation(line: 1269, column: 12, scope: !3757)
!3761 = !DILocation(line: 1269, column: 4, scope: !3757)
!3762 = !DILocation(line: 1270, column: 24, scope: !3753)
!3763 = !DILocation(line: 1270, column: 27, scope: !3753)
!3764 = !DILocation(line: 1270, column: 35, scope: !3753)
!3765 = !DILocation(line: 1270, column: 46, scope: !3753)
!3766 = !DILocation(line: 1271, column: 9, scope: !3753)
!3767 = !DILocation(line: 1271, column: 19, scope: !3753)
!3768 = !DILocation(line: 1270, column: 7, scope: !3753)
!3769 = !DILocation(line: 1270, column: 5, scope: !3753)
!3770 = !DILocation(line: 1272, column: 7, scope: !3771)
!3771 = distinct !DILexicalBlock(scope: !3753, file: !1, line: 1272, column: 7)
!3772 = !DILocation(line: 1272, column: 9, scope: !3771)
!3773 = !DILocation(line: 1272, column: 7, scope: !3753)
!3774 = !DILocation(line: 1273, column: 12, scope: !3771)
!3775 = !DILocation(line: 1273, column: 4, scope: !3771)
!3776 = !DILocation(line: 1274, column: 2, scope: !3753)
!3777 = !DILocation(line: 1279, column: 17, scope: !642)
!3778 = !DILocation(line: 1279, column: 6, scope: !642)
!3779 = !DILocation(line: 1279, column: 4, scope: !642)
!3780 = !DILocation(line: 1280, column: 6, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1280, column: 6)
!3782 = !DILocation(line: 1280, column: 8, scope: !3781)
!3783 = !DILocation(line: 1280, column: 6, scope: !642)
!3784 = !DILocation(line: 1281, column: 11, scope: !3781)
!3785 = !DILocation(line: 1281, column: 3, scope: !3781)
!3786 = !DILocation(line: 1284, column: 17, scope: !642)
!3787 = !DILocation(line: 1284, column: 20, scope: !642)
!3788 = !DILocation(line: 1284, column: 25, scope: !642)
!3789 = !DILocation(line: 1284, column: 6, scope: !642)
!3790 = !DILocation(line: 1284, column: 4, scope: !642)
!3791 = !DILocation(line: 1285, column: 6, scope: !3792)
!3792 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1285, column: 6)
!3793 = !DILocation(line: 1285, column: 8, scope: !3792)
!3794 = !DILocation(line: 1285, column: 6, scope: !642)
!3795 = !DILocation(line: 1286, column: 11, scope: !3792)
!3796 = !DILocation(line: 1286, column: 3, scope: !3792)
!3797 = !DILocation(line: 1288, column: 6, scope: !3798)
!3798 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1288, column: 6)
!3799 = !DILocation(line: 1288, column: 11, scope: !3798)
!3800 = !DILocation(line: 1288, column: 36, scope: !3798)
!3801 = !DILocation(line: 1288, column: 6, scope: !642)
!3802 = !DILocation(line: 1290, column: 18, scope: !3803)
!3803 = distinct !DILexicalBlock(scope: !3798, file: !1, line: 1288, column: 41)
!3804 = !DILocation(line: 1290, column: 7, scope: !3803)
!3805 = !DILocation(line: 1290, column: 5, scope: !3803)
!3806 = !DILocation(line: 1291, column: 7, scope: !3807)
!3807 = distinct !DILexicalBlock(scope: !3803, file: !1, line: 1291, column: 7)
!3808 = !DILocation(line: 1291, column: 9, scope: !3807)
!3809 = !DILocation(line: 1291, column: 7, scope: !3803)
!3810 = !DILocation(line: 1292, column: 12, scope: !3807)
!3811 = !DILocation(line: 1292, column: 4, scope: !3807)
!3812 = !DILocation(line: 1295, column: 18, scope: !3803)
!3813 = !DILocation(line: 1295, column: 22, scope: !3803)
!3814 = !DILocation(line: 1295, column: 27, scope: !3803)
!3815 = !DILocation(line: 1295, column: 45, scope: !3803)
!3816 = !DILocation(line: 1295, column: 48, scope: !3803)
!3817 = !DILocation(line: 1295, column: 7, scope: !3803)
!3818 = !DILocation(line: 1295, column: 5, scope: !3803)
!3819 = !DILocation(line: 1296, column: 7, scope: !3820)
!3820 = distinct !DILexicalBlock(scope: !3803, file: !1, line: 1296, column: 7)
!3821 = !DILocation(line: 1296, column: 9, scope: !3820)
!3822 = !DILocation(line: 1296, column: 7, scope: !3803)
!3823 = !DILocation(line: 1297, column: 12, scope: !3820)
!3824 = !DILocation(line: 1297, column: 4, scope: !3820)
!3825 = !DILocation(line: 1299, column: 5, scope: !3803)
!3826 = !DILocation(line: 1300, column: 8, scope: !3803)
!3827 = !DILocation(line: 1301, column: 10, scope: !3803)
!3828 = !DILocation(line: 1301, column: 15, scope: !3803)
!3829 = !DILocation(line: 1301, column: 25, scope: !3803)
!3830 = !DILocation(line: 1301, column: 8, scope: !3803)
!3831 = !DILocation(line: 1302, column: 3, scope: !3803)
!3832 = !DILocation(line: 1302, column: 9, scope: !3833)
!3833 = !DILexicalBlockFile(scope: !3834, file: !1, discriminator: 1)
!3834 = distinct !DILexicalBlock(scope: !3835, file: !1, line: 1302, column: 3)
!3835 = distinct !DILexicalBlock(scope: !3803, file: !1, line: 1302, column: 3)
!3836 = !DILocation(line: 1302, column: 14, scope: !3833)
!3837 = !DILocation(line: 1302, column: 3, scope: !3833)
!3838 = !DILocation(line: 1303, column: 8, scope: !3839)
!3839 = distinct !DILexicalBlock(scope: !3840, file: !1, line: 1303, column: 8)
!3840 = distinct !DILexicalBlock(scope: !3834, file: !1, line: 1302, column: 42)
!3841 = !DILocation(line: 1303, column: 14, scope: !3839)
!3842 = !DILocation(line: 1303, column: 19, scope: !3839)
!3843 = !DILocation(line: 1303, column: 8, scope: !3840)
!3844 = !DILocation(line: 1304, column: 10, scope: !3839)
!3845 = !DILocation(line: 1304, column: 7, scope: !3839)
!3846 = !DILocation(line: 1304, column: 5, scope: !3839)
!3847 = !DILocation(line: 1305, column: 9, scope: !3840)
!3848 = !DILocation(line: 1306, column: 8, scope: !3849)
!3849 = distinct !DILexicalBlock(scope: !3840, file: !1, line: 1306, column: 8)
!3850 = !DILocation(line: 1306, column: 13, scope: !3849)
!3851 = !DILocation(line: 1306, column: 8, scope: !3840)
!3852 = !DILocation(line: 1307, column: 27, scope: !3853)
!3853 = distinct !DILexicalBlock(scope: !3849, file: !1, line: 1306, column: 19)
!3854 = !DILocation(line: 1307, column: 14, scope: !3853)
!3855 = !DILocation(line: 1307, column: 9, scope: !3853)
!3856 = !DILocation(line: 1307, column: 7, scope: !3853)
!3857 = !DILocation(line: 1308, column: 9, scope: !3858)
!3858 = distinct !DILexicalBlock(scope: !3853, file: !1, line: 1308, column: 9)
!3859 = !DILocation(line: 1308, column: 11, scope: !3858)
!3860 = !DILocation(line: 1308, column: 9, scope: !3853)
!3861 = !DILocation(line: 1309, column: 14, scope: !3858)
!3862 = !DILocation(line: 1309, column: 6, scope: !3858)
!3863 = !DILocation(line: 1310, column: 10, scope: !3853)
!3864 = !DILocation(line: 1311, column: 7, scope: !3853)
!3865 = !DILocation(line: 1312, column: 4, scope: !3853)
!3866 = !DILocation(line: 1313, column: 3, scope: !3840)
!3867 = !DILocation(line: 1302, column: 30, scope: !3868)
!3868 = !DILexicalBlockFile(scope: !3834, file: !1, discriminator: 2)
!3869 = !DILocation(line: 1302, column: 36, scope: !3868)
!3870 = !DILocation(line: 1302, column: 28, scope: !3868)
!3871 = !DILocation(line: 1302, column: 3, scope: !3868)
!3872 = !DILocation(line: 1314, column: 7, scope: !3873)
!3873 = distinct !DILexicalBlock(scope: !3803, file: !1, line: 1314, column: 7)
!3874 = !DILocation(line: 1314, column: 12, scope: !3873)
!3875 = !DILocation(line: 1314, column: 7, scope: !3803)
!3876 = !DILocation(line: 1315, column: 26, scope: !3877)
!3877 = distinct !DILexicalBlock(scope: !3873, file: !1, line: 1314, column: 21)
!3878 = !DILocation(line: 1315, column: 13, scope: !3877)
!3879 = !DILocation(line: 1315, column: 8, scope: !3877)
!3880 = !DILocation(line: 1315, column: 6, scope: !3877)
!3881 = !DILocation(line: 1316, column: 8, scope: !3882)
!3882 = distinct !DILexicalBlock(scope: !3877, file: !1, line: 1316, column: 8)
!3883 = !DILocation(line: 1316, column: 10, scope: !3882)
!3884 = !DILocation(line: 1316, column: 8, scope: !3877)
!3885 = !DILocation(line: 1317, column: 13, scope: !3882)
!3886 = !DILocation(line: 1317, column: 5, scope: !3882)
!3887 = !DILocation(line: 1318, column: 3, scope: !3877)
!3888 = !DILocation(line: 1319, column: 2, scope: !3803)
!3889 = !DILocation(line: 1321, column: 6, scope: !3890)
!3890 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1321, column: 6)
!3891 = !DILocation(line: 1321, column: 11, scope: !3890)
!3892 = !DILocation(line: 1321, column: 38, scope: !3890)
!3893 = !DILocation(line: 1321, column: 43, scope: !3890)
!3894 = !DILocation(line: 1321, column: 36, scope: !3890)
!3895 = !DILocation(line: 1321, column: 6, scope: !642)
!3896 = !DILocation(line: 1323, column: 18, scope: !3897)
!3897 = distinct !DILexicalBlock(scope: !3890, file: !1, line: 1321, column: 67)
!3898 = !DILocation(line: 1323, column: 7, scope: !3897)
!3899 = !DILocation(line: 1323, column: 5, scope: !3897)
!3900 = !DILocation(line: 1324, column: 7, scope: !3901)
!3901 = distinct !DILexicalBlock(scope: !3897, file: !1, line: 1324, column: 7)
!3902 = !DILocation(line: 1324, column: 9, scope: !3901)
!3903 = !DILocation(line: 1324, column: 7, scope: !3897)
!3904 = !DILocation(line: 1325, column: 12, scope: !3901)
!3905 = !DILocation(line: 1325, column: 4, scope: !3901)
!3906 = !DILocation(line: 1328, column: 18, scope: !3897)
!3907 = !DILocation(line: 1328, column: 22, scope: !3897)
!3908 = !DILocation(line: 1328, column: 27, scope: !3897)
!3909 = !DILocation(line: 1328, column: 52, scope: !3897)
!3910 = !DILocation(line: 1328, column: 57, scope: !3897)
!3911 = !DILocation(line: 1328, column: 7, scope: !3897)
!3912 = !DILocation(line: 1328, column: 5, scope: !3897)
!3913 = !DILocation(line: 1329, column: 7, scope: !3914)
!3914 = distinct !DILexicalBlock(scope: !3897, file: !1, line: 1329, column: 7)
!3915 = !DILocation(line: 1329, column: 9, scope: !3914)
!3916 = !DILocation(line: 1329, column: 7, scope: !3897)
!3917 = !DILocation(line: 1330, column: 12, scope: !3914)
!3918 = !DILocation(line: 1330, column: 4, scope: !3914)
!3919 = !DILocation(line: 1332, column: 5, scope: !3897)
!3920 = !DILocation(line: 1333, column: 8, scope: !3897)
!3921 = !DILocation(line: 1334, column: 10, scope: !3897)
!3922 = !DILocation(line: 1334, column: 15, scope: !3897)
!3923 = !DILocation(line: 1334, column: 25, scope: !3897)
!3924 = !DILocation(line: 1334, column: 8, scope: !3897)
!3925 = !DILocation(line: 1335, column: 3, scope: !3897)
!3926 = !DILocation(line: 1335, column: 9, scope: !3927)
!3927 = !DILexicalBlockFile(scope: !3928, file: !1, discriminator: 1)
!3928 = distinct !DILexicalBlock(scope: !3929, file: !1, line: 1335, column: 3)
!3929 = distinct !DILexicalBlock(scope: !3897, file: !1, line: 1335, column: 3)
!3930 = !DILocation(line: 1335, column: 14, scope: !3927)
!3931 = !DILocation(line: 1335, column: 3, scope: !3927)
!3932 = !DILocation(line: 1336, column: 8, scope: !3933)
!3933 = distinct !DILexicalBlock(scope: !3934, file: !1, line: 1336, column: 8)
!3934 = distinct !DILexicalBlock(scope: !3928, file: !1, line: 1335, column: 42)
!3935 = !DILocation(line: 1336, column: 14, scope: !3933)
!3936 = !DILocation(line: 1336, column: 8, scope: !3934)
!3937 = !DILocation(line: 1337, column: 5, scope: !3933)
!3938 = !DILocation(line: 1338, column: 9, scope: !3939)
!3939 = distinct !DILexicalBlock(scope: !3934, file: !1, line: 1338, column: 8)
!3940 = !DILocation(line: 1338, column: 15, scope: !3939)
!3941 = !DILocation(line: 1338, column: 8, scope: !3934)
!3942 = !DILocation(line: 1339, column: 10, scope: !3939)
!3943 = !DILocation(line: 1339, column: 7, scope: !3939)
!3944 = !DILocation(line: 1339, column: 5, scope: !3939)
!3945 = !DILocation(line: 1340, column: 9, scope: !3934)
!3946 = !DILocation(line: 1341, column: 8, scope: !3947)
!3947 = distinct !DILexicalBlock(scope: !3934, file: !1, line: 1341, column: 8)
!3948 = !DILocation(line: 1341, column: 13, scope: !3947)
!3949 = !DILocation(line: 1341, column: 8, scope: !3934)
!3950 = !DILocation(line: 1342, column: 27, scope: !3951)
!3951 = distinct !DILexicalBlock(scope: !3947, file: !1, line: 1341, column: 19)
!3952 = !DILocation(line: 1342, column: 14, scope: !3951)
!3953 = !DILocation(line: 1342, column: 9, scope: !3951)
!3954 = !DILocation(line: 1342, column: 7, scope: !3951)
!3955 = !DILocation(line: 1343, column: 9, scope: !3956)
!3956 = distinct !DILexicalBlock(scope: !3951, file: !1, line: 1343, column: 9)
!3957 = !DILocation(line: 1343, column: 11, scope: !3956)
!3958 = !DILocation(line: 1343, column: 9, scope: !3951)
!3959 = !DILocation(line: 1344, column: 14, scope: !3956)
!3960 = !DILocation(line: 1344, column: 6, scope: !3956)
!3961 = !DILocation(line: 1345, column: 10, scope: !3951)
!3962 = !DILocation(line: 1346, column: 7, scope: !3951)
!3963 = !DILocation(line: 1347, column: 4, scope: !3951)
!3964 = !DILocation(line: 1348, column: 3, scope: !3934)
!3965 = !DILocation(line: 1335, column: 30, scope: !3966)
!3966 = !DILexicalBlockFile(scope: !3928, file: !1, discriminator: 2)
!3967 = !DILocation(line: 1335, column: 36, scope: !3966)
!3968 = !DILocation(line: 1335, column: 28, scope: !3966)
!3969 = !DILocation(line: 1335, column: 3, scope: !3966)
!3970 = !DILocation(line: 1349, column: 7, scope: !3971)
!3971 = distinct !DILexicalBlock(scope: !3897, file: !1, line: 1349, column: 7)
!3972 = !DILocation(line: 1349, column: 12, scope: !3971)
!3973 = !DILocation(line: 1349, column: 7, scope: !3897)
!3974 = !DILocation(line: 1350, column: 26, scope: !3975)
!3975 = distinct !DILexicalBlock(scope: !3971, file: !1, line: 1349, column: 21)
!3976 = !DILocation(line: 1350, column: 13, scope: !3975)
!3977 = !DILocation(line: 1350, column: 8, scope: !3975)
!3978 = !DILocation(line: 1350, column: 6, scope: !3975)
!3979 = !DILocation(line: 1351, column: 8, scope: !3980)
!3980 = distinct !DILexicalBlock(scope: !3975, file: !1, line: 1351, column: 8)
!3981 = !DILocation(line: 1351, column: 10, scope: !3980)
!3982 = !DILocation(line: 1351, column: 8, scope: !3975)
!3983 = !DILocation(line: 1352, column: 13, scope: !3980)
!3984 = !DILocation(line: 1352, column: 5, scope: !3980)
!3985 = !DILocation(line: 1353, column: 3, scope: !3975)
!3986 = !DILocation(line: 1354, column: 2, scope: !3897)
!3987 = !DILocation(line: 1357, column: 17, scope: !642)
!3988 = !DILocation(line: 1357, column: 6, scope: !642)
!3989 = !DILocation(line: 1357, column: 4, scope: !642)
!3990 = !DILocation(line: 1358, column: 6, scope: !3991)
!3991 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1358, column: 6)
!3992 = !DILocation(line: 1358, column: 8, scope: !3991)
!3993 = !DILocation(line: 1358, column: 6, scope: !642)
!3994 = !DILocation(line: 1359, column: 11, scope: !3991)
!3995 = !DILocation(line: 1359, column: 3, scope: !3991)
!3996 = !DILocation(line: 1362, column: 17, scope: !642)
!3997 = !DILocation(line: 1362, column: 20, scope: !642)
!3998 = !DILocation(line: 1362, column: 25, scope: !642)
!3999 = !DILocation(line: 1362, column: 47, scope: !642)
!4000 = !DILocation(line: 1362, column: 6, scope: !642)
!4001 = !DILocation(line: 1362, column: 4, scope: !642)
!4002 = !DILocation(line: 1363, column: 6, scope: !4003)
!4003 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1363, column: 6)
!4004 = !DILocation(line: 1363, column: 8, scope: !4003)
!4005 = !DILocation(line: 1363, column: 6, scope: !642)
!4006 = !DILocation(line: 1364, column: 11, scope: !4003)
!4007 = !DILocation(line: 1364, column: 3, scope: !4003)
!4008 = !DILocation(line: 1367, column: 17, scope: !642)
!4009 = !DILocation(line: 1367, column: 6, scope: !642)
!4010 = !DILocation(line: 1367, column: 4, scope: !642)
!4011 = !DILocation(line: 1368, column: 6, scope: !4012)
!4012 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1368, column: 6)
!4013 = !DILocation(line: 1368, column: 8, scope: !4012)
!4014 = !DILocation(line: 1368, column: 6, scope: !642)
!4015 = !DILocation(line: 1369, column: 11, scope: !4012)
!4016 = !DILocation(line: 1369, column: 3, scope: !4012)
!4017 = !DILocation(line: 1371, column: 9, scope: !642)
!4018 = !DILocation(line: 1371, column: 14, scope: !642)
!4019 = !DILocation(line: 1371, column: 24, scope: !642)
!4020 = !DILocation(line: 1371, column: 7, scope: !642)
!4021 = !DILocation(line: 1372, column: 2, scope: !642)
!4022 = !DILocation(line: 1372, column: 8, scope: !4023)
!4023 = !DILexicalBlockFile(scope: !4024, file: !1, discriminator: 1)
!4024 = distinct !DILexicalBlock(scope: !4025, file: !1, line: 1372, column: 2)
!4025 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1372, column: 2)
!4026 = !DILocation(line: 1372, column: 13, scope: !4023)
!4027 = !DILocation(line: 1372, column: 2, scope: !4023)
!4028 = !DILocation(line: 1373, column: 25, scope: !4029)
!4029 = distinct !DILexicalBlock(scope: !4024, file: !1, line: 1372, column: 41)
!4030 = !DILocation(line: 1373, column: 28, scope: !4029)
!4031 = !DILocation(line: 1373, column: 34, scope: !4029)
!4032 = !DILocation(line: 1373, column: 45, scope: !4029)
!4033 = !DILocation(line: 1373, column: 51, scope: !4029)
!4034 = !DILocation(line: 1373, column: 59, scope: !4029)
!4035 = !DILocation(line: 1373, column: 12, scope: !4029)
!4036 = !DILocation(line: 1373, column: 7, scope: !4029)
!4037 = !DILocation(line: 1373, column: 5, scope: !4029)
!4038 = !DILocation(line: 1375, column: 7, scope: !4039)
!4039 = distinct !DILexicalBlock(scope: !4029, file: !1, line: 1375, column: 7)
!4040 = !DILocation(line: 1375, column: 9, scope: !4039)
!4041 = !DILocation(line: 1375, column: 7, scope: !4029)
!4042 = !DILocation(line: 1376, column: 12, scope: !4039)
!4043 = !DILocation(line: 1376, column: 4, scope: !4039)
!4044 = !DILocation(line: 1377, column: 2, scope: !4029)
!4045 = !DILocation(line: 1372, column: 29, scope: !4046)
!4046 = !DILexicalBlockFile(scope: !4024, file: !1, discriminator: 2)
!4047 = !DILocation(line: 1372, column: 35, scope: !4046)
!4048 = !DILocation(line: 1372, column: 27, scope: !4046)
!4049 = !DILocation(line: 1372, column: 2, scope: !4046)
!4050 = !DILocation(line: 1380, column: 16, scope: !642)
!4051 = !DILocation(line: 1380, column: 6, scope: !642)
!4052 = !DILocation(line: 1380, column: 4, scope: !642)
!4053 = !DILocation(line: 1381, column: 6, scope: !4054)
!4054 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1381, column: 6)
!4055 = !DILocation(line: 1381, column: 8, scope: !4054)
!4056 = !DILocation(line: 1381, column: 6, scope: !642)
!4057 = !DILocation(line: 1382, column: 11, scope: !4054)
!4058 = !DILocation(line: 1382, column: 3, scope: !4054)
!4059 = !DILocation(line: 1385, column: 16, scope: !642)
!4060 = !DILocation(line: 1385, column: 6, scope: !642)
!4061 = !DILocation(line: 1385, column: 4, scope: !642)
!4062 = !DILocation(line: 1386, column: 6, scope: !4063)
!4063 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1386, column: 6)
!4064 = !DILocation(line: 1386, column: 8, scope: !4063)
!4065 = !DILocation(line: 1386, column: 6, scope: !642)
!4066 = !DILocation(line: 1387, column: 11, scope: !4063)
!4067 = !DILocation(line: 1387, column: 3, scope: !4063)
!4068 = !DILocation(line: 1390, column: 16, scope: !642)
!4069 = !DILocation(line: 1390, column: 6, scope: !642)
!4070 = !DILocation(line: 1390, column: 4, scope: !642)
!4071 = !DILocation(line: 1391, column: 6, scope: !4072)
!4072 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1391, column: 6)
!4073 = !DILocation(line: 1391, column: 8, scope: !4072)
!4074 = !DILocation(line: 1391, column: 6, scope: !642)
!4075 = !DILocation(line: 1392, column: 11, scope: !4072)
!4076 = !DILocation(line: 1392, column: 3, scope: !4072)
!4077 = !DILocation(line: 1395, column: 17, scope: !642)
!4078 = !DILocation(line: 1395, column: 6, scope: !642)
!4079 = !DILocation(line: 1395, column: 4, scope: !642)
!4080 = !DILocation(line: 1396, column: 6, scope: !4081)
!4081 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1396, column: 6)
!4082 = !DILocation(line: 1396, column: 8, scope: !4081)
!4083 = !DILocation(line: 1396, column: 6, scope: !642)
!4084 = !DILocation(line: 1397, column: 11, scope: !4081)
!4085 = !DILocation(line: 1397, column: 3, scope: !4081)
!4086 = !DILocation(line: 1400, column: 17, scope: !642)
!4087 = !DILocation(line: 1400, column: 24, scope: !642)
!4088 = !DILocation(line: 1400, column: 29, scope: !642)
!4089 = !DILocation(line: 1400, column: 48, scope: !642)
!4090 = !DILocation(line: 1400, column: 22, scope: !642)
!4091 = !DILocation(line: 1400, column: 6, scope: !642)
!4092 = !DILocation(line: 1400, column: 4, scope: !642)
!4093 = !DILocation(line: 1401, column: 6, scope: !4094)
!4094 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1401, column: 6)
!4095 = !DILocation(line: 1401, column: 8, scope: !4094)
!4096 = !DILocation(line: 1401, column: 6, scope: !642)
!4097 = !DILocation(line: 1402, column: 11, scope: !4094)
!4098 = !DILocation(line: 1402, column: 3, scope: !4094)
!4099 = !DILocation(line: 1405, column: 17, scope: !642)
!4100 = !DILocation(line: 1405, column: 6, scope: !642)
!4101 = !DILocation(line: 1405, column: 4, scope: !642)
!4102 = !DILocation(line: 1406, column: 6, scope: !4103)
!4103 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1406, column: 6)
!4104 = !DILocation(line: 1406, column: 8, scope: !4103)
!4105 = !DILocation(line: 1406, column: 6, scope: !642)
!4106 = !DILocation(line: 1407, column: 11, scope: !4103)
!4107 = !DILocation(line: 1407, column: 3, scope: !4103)
!4108 = !DILocation(line: 1410, column: 17, scope: !642)
!4109 = !DILocation(line: 1410, column: 6, scope: !642)
!4110 = !DILocation(line: 1410, column: 4, scope: !642)
!4111 = !DILocation(line: 1411, column: 6, scope: !4112)
!4112 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1411, column: 6)
!4113 = !DILocation(line: 1411, column: 8, scope: !4112)
!4114 = !DILocation(line: 1411, column: 6, scope: !642)
!4115 = !DILocation(line: 1412, column: 11, scope: !4112)
!4116 = !DILocation(line: 1412, column: 3, scope: !4112)
!4117 = !DILocation(line: 1414, column: 9, scope: !642)
!4118 = !DILocation(line: 1414, column: 14, scope: !642)
!4119 = !DILocation(line: 1414, column: 24, scope: !642)
!4120 = !DILocation(line: 1414, column: 7, scope: !642)
!4121 = !DILocation(line: 1415, column: 2, scope: !642)
!4122 = !DILocation(line: 1415, column: 8, scope: !4123)
!4123 = !DILexicalBlockFile(scope: !4124, file: !1, discriminator: 1)
!4124 = distinct !DILexicalBlock(scope: !4125, file: !1, line: 1415, column: 2)
!4125 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1415, column: 2)
!4126 = !DILocation(line: 1415, column: 13, scope: !4123)
!4127 = !DILocation(line: 1415, column: 2, scope: !4123)
!4128 = !DILocalVariable(name: "encattr", scope: !4129, file: !1, line: 1420, type: !275)
!4129 = distinct !DILexicalBlock(scope: !4124, file: !1, line: 1415, column: 41)
!4130 = !DILocation(line: 1420, column: 12, scope: !4129)
!4131 = !DILocalVariable(name: "attr", scope: !4129, file: !1, line: 1420, type: !275)
!4132 = !DILocation(line: 1420, column: 21, scope: !4129)
!4133 = !DILocation(line: 1421, column: 7, scope: !4134)
!4134 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1421, column: 7)
!4135 = !DILocation(line: 1421, column: 13, scope: !4134)
!4136 = !DILocation(line: 1421, column: 7, scope: !4129)
!4137 = !DILocation(line: 1422, column: 9, scope: !4134)
!4138 = !DILocation(line: 1422, column: 4, scope: !4134)
!4139 = !DILocation(line: 1424, column: 9, scope: !4134)
!4140 = !DILocation(line: 1425, column: 8, scope: !4141)
!4141 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1425, column: 7)
!4142 = !DILocation(line: 1425, column: 14, scope: !4141)
!4143 = !DILocation(line: 1425, column: 19, scope: !4141)
!4144 = !DILocation(line: 1425, column: 27, scope: !4141)
!4145 = !DILocation(line: 1425, column: 7, scope: !4129)
!4146 = !DILocation(line: 1426, column: 9, scope: !4141)
!4147 = !DILocation(line: 1426, column: 4, scope: !4141)
!4148 = !DILocation(line: 1427, column: 22, scope: !4129)
!4149 = !DILocation(line: 1427, column: 28, scope: !4129)
!4150 = !DILocation(line: 1427, column: 34, scope: !4129)
!4151 = !DILocation(line: 1427, column: 8, scope: !4129)
!4152 = !DILocation(line: 1428, column: 19, scope: !4129)
!4153 = !DILocation(line: 1428, column: 29, scope: !4129)
!4154 = !DILocation(line: 1428, column: 3, scope: !4129)
!4155 = !DILocation(line: 1429, column: 25, scope: !4129)
!4156 = !DILocation(line: 1429, column: 28, scope: !4129)
!4157 = !DILocation(line: 1429, column: 12, scope: !4129)
!4158 = !DILocation(line: 1429, column: 7, scope: !4129)
!4159 = !DILocation(line: 1429, column: 5, scope: !4129)
!4160 = !DILocation(line: 1430, column: 7, scope: !4161)
!4161 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1430, column: 7)
!4162 = !DILocation(line: 1430, column: 9, scope: !4161)
!4163 = !DILocation(line: 1430, column: 7, scope: !4129)
!4164 = !DILocation(line: 1431, column: 12, scope: !4161)
!4165 = !DILocation(line: 1431, column: 4, scope: !4161)
!4166 = !DILocation(line: 1432, column: 2, scope: !4129)
!4167 = !DILocation(line: 1415, column: 29, scope: !4168)
!4168 = !DILexicalBlockFile(scope: !4124, file: !1, discriminator: 2)
!4169 = !DILocation(line: 1415, column: 35, scope: !4168)
!4170 = !DILocation(line: 1415, column: 27, scope: !4168)
!4171 = !DILocation(line: 1415, column: 2, scope: !4168)
!4172 = !DILocation(line: 1435, column: 17, scope: !642)
!4173 = !DILocation(line: 1435, column: 6, scope: !642)
!4174 = !DILocation(line: 1435, column: 4, scope: !642)
!4175 = !DILocation(line: 1436, column: 6, scope: !4176)
!4176 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1436, column: 6)
!4177 = !DILocation(line: 1436, column: 8, scope: !4176)
!4178 = !DILocation(line: 1436, column: 6, scope: !642)
!4179 = !DILocation(line: 1437, column: 11, scope: !4176)
!4180 = !DILocation(line: 1437, column: 3, scope: !4176)
!4181 = !DILocation(line: 1440, column: 17, scope: !642)
!4182 = !DILocation(line: 1440, column: 6, scope: !642)
!4183 = !DILocation(line: 1440, column: 4, scope: !642)
!4184 = !DILocation(line: 1441, column: 6, scope: !4185)
!4185 = distinct !DILexicalBlock(scope: !642, file: !1, line: 1441, column: 6)
!4186 = !DILocation(line: 1441, column: 8, scope: !4185)
!4187 = !DILocation(line: 1441, column: 6, scope: !642)
!4188 = !DILocation(line: 1442, column: 11, scope: !4185)
!4189 = !DILocation(line: 1442, column: 3, scope: !4185)
!4190 = !DILocation(line: 1444, column: 2, scope: !642)
!4191 = !DILocation(line: 1445, column: 1, scope: !642)
!4192 = !DILocalVariable(name: "a", arg: 1, scope: !652, file: !1, line: 853, type: !44)
!4193 = !DILocation(line: 853, column: 34, scope: !652)
!4194 = !DILocalVariable(name: "val", arg: 2, scope: !652, file: !1, line: 853, type: !237)
!4195 = !DILocation(line: 853, column: 46, scope: !652)
!4196 = !DILocalVariable(name: "mask", scope: !652, file: !1, line: 855, type: !53)
!4197 = !DILocation(line: 855, column: 11, scope: !652)
!4198 = !DILocalVariable(name: "numdata", scope: !652, file: !1, line: 856, type: !4199)
!4199 = !DICompositeType(tag: DW_TAG_array_type, baseType: !257, size: 72, align: 8, elements: !4200)
!4200 = !{!4201}
!4201 = !DISubrange(count: 9)
!4202 = !DILocation(line: 856, column: 10, scope: !652)
!4203 = !DILocalVariable(name: "i", scope: !652, file: !1, line: 857, type: !63)
!4204 = !DILocation(line: 857, column: 6, scope: !652)
!4205 = !DILocation(line: 859, column: 2, scope: !652)
!4206 = !DILocation(line: 859, column: 13, scope: !652)
!4207 = !DILocation(line: 860, column: 9, scope: !4208)
!4208 = distinct !DILexicalBlock(scope: !652, file: !1, line: 860, column: 2)
!4209 = !DILocation(line: 860, column: 7, scope: !4208)
!4210 = !DILocation(line: 860, column: 14, scope: !4211)
!4211 = !DILexicalBlockFile(scope: !4212, file: !1, discriminator: 1)
!4212 = distinct !DILexicalBlock(scope: !4208, file: !1, line: 860, column: 2)
!4213 = !DILocation(line: 860, column: 16, scope: !4211)
!4214 = !DILocation(line: 860, column: 2, scope: !4211)
!4215 = !DILocation(line: 861, column: 7, scope: !4216)
!4216 = distinct !DILexicalBlock(scope: !4217, file: !1, line: 861, column: 7)
!4217 = distinct !DILexicalBlock(scope: !4212, file: !1, line: 860, column: 45)
!4218 = !DILocation(line: 861, column: 13, scope: !4216)
!4219 = !DILocation(line: 861, column: 11, scope: !4216)
!4220 = !DILocation(line: 861, column: 7, scope: !4217)
!4221 = !DILocation(line: 862, column: 27, scope: !4222)
!4222 = distinct !DILexicalBlock(scope: !4216, file: !1, line: 861, column: 19)
!4223 = !DILocation(line: 862, column: 18, scope: !4222)
!4224 = !DILocation(line: 862, column: 4, scope: !4222)
!4225 = !DILocation(line: 862, column: 15, scope: !4222)
!4226 = !DILocation(line: 863, column: 4, scope: !4222)
!4227 = !DILocation(line: 865, column: 25, scope: !4217)
!4228 = !DILocation(line: 865, column: 16, scope: !4217)
!4229 = !DILocation(line: 865, column: 11, scope: !4217)
!4230 = !DILocation(line: 865, column: 3, scope: !4217)
!4231 = !DILocation(line: 865, column: 14, scope: !4217)
!4232 = !DILocation(line: 866, column: 7, scope: !4217)
!4233 = !DILocation(line: 867, column: 17, scope: !4217)
!4234 = !DILocation(line: 867, column: 3, scope: !4217)
!4235 = !DILocation(line: 867, column: 14, scope: !4217)
!4236 = !DILocation(line: 868, column: 8, scope: !4217)
!4237 = !DILocation(line: 869, column: 2, scope: !4217)
!4238 = !DILocation(line: 860, column: 41, scope: !4239)
!4239 = !DILexicalBlockFile(scope: !4212, file: !1, discriminator: 2)
!4240 = !DILocation(line: 860, column: 2, scope: !4239)
!4241 = !DILocation(line: 870, column: 28, scope: !652)
!4242 = !DILocation(line: 870, column: 31, scope: !652)
!4243 = !DILocation(line: 870, column: 40, scope: !652)
!4244 = !DILocation(line: 870, column: 15, scope: !652)
!4245 = !DILocation(line: 870, column: 10, scope: !652)
!4246 = !DILocation(line: 870, column: 2, scope: !652)
!4247 = !DILocalVariable(name: "a", arg: 1, scope: !655, file: !1, line: 948, type: !44)
!4248 = !DILocation(line: 948, column: 40, scope: !655)
!4249 = !DILocalVariable(name: "offset", arg: 2, scope: !655, file: !1, line: 948, type: !237)
!4250 = !DILocation(line: 948, column: 52, scope: !655)
!4251 = !DILocalVariable(name: "pack_size", arg: 3, scope: !655, file: !1, line: 948, type: !237)
!4252 = !DILocation(line: 948, column: 69, scope: !655)
!4253 = !DILocalVariable(name: "unpack_size", arg: 4, scope: !655, file: !1, line: 949, type: !237)
!4254 = !DILocation(line: 949, column: 14, scope: !655)
!4255 = !DILocalVariable(name: "num_coder", arg: 5, scope: !655, file: !1, line: 949, type: !63)
!4256 = !DILocation(line: 949, column: 31, scope: !655)
!4257 = !DILocalVariable(name: "coders", arg: 6, scope: !655, file: !1, line: 949, type: !645)
!4258 = !DILocation(line: 949, column: 56, scope: !655)
!4259 = !DILocalVariable(name: "substrm", arg: 7, scope: !655, file: !1, line: 949, type: !63)
!4260 = !DILocation(line: 949, column: 68, scope: !655)
!4261 = !DILocalVariable(name: "header_crc", arg: 8, scope: !655, file: !1, line: 950, type: !275)
!4262 = !DILocation(line: 950, column: 14, scope: !655)
!4263 = !DILocalVariable(name: "zip", scope: !655, file: !1, line: 952, type: !232)
!4264 = !DILocation(line: 952, column: 16, scope: !655)
!4265 = !DILocation(line: 952, column: 38, scope: !655)
!4266 = !DILocation(line: 952, column: 41, scope: !655)
!4267 = !DILocation(line: 952, column: 22, scope: !655)
!4268 = !DILocalVariable(name: "codec_buff", scope: !655, file: !1, line: 953, type: !4269)
!4269 = !DICompositeType(tag: DW_TAG_array_type, baseType: !257, size: 64, align: 8, elements: !4270)
!4270 = !{!4271}
!4271 = !DISubrange(count: 8)
!4272 = !DILocation(line: 953, column: 10, scope: !655)
!4273 = !DILocalVariable(name: "numFolders", scope: !655, file: !1, line: 954, type: !63)
!4274 = !DILocation(line: 954, column: 6, scope: !655)
!4275 = !DILocalVariable(name: "fi", scope: !655, file: !1, line: 954, type: !63)
!4276 = !DILocation(line: 954, column: 18, scope: !655)
!4277 = !DILocalVariable(name: "codec_size", scope: !655, file: !1, line: 955, type: !63)
!4278 = !DILocation(line: 955, column: 6, scope: !655)
!4279 = !DILocalVariable(name: "i", scope: !655, file: !1, line: 956, type: !63)
!4280 = !DILocation(line: 956, column: 6, scope: !655)
!4281 = !DILocalVariable(name: "r", scope: !655, file: !1, line: 956, type: !63)
!4282 = !DILocation(line: 956, column: 9, scope: !655)
!4283 = !DILocation(line: 958, column: 6, scope: !4284)
!4284 = distinct !DILexicalBlock(scope: !655, file: !1, line: 958, column: 6)
!4285 = !DILocation(line: 958, column: 14, scope: !4284)
!4286 = !DILocation(line: 958, column: 20, scope: !4284)
!4287 = !DILocation(line: 958, column: 6, scope: !655)
!4288 = !DILocation(line: 959, column: 21, scope: !4284)
!4289 = !DILocation(line: 959, column: 26, scope: !4284)
!4290 = !DILocation(line: 959, column: 16, scope: !4284)
!4291 = !DILocation(line: 959, column: 14, scope: !4284)
!4292 = !DILocation(line: 959, column: 3, scope: !4284)
!4293 = !DILocation(line: 961, column: 14, scope: !4284)
!4294 = !DILocation(line: 966, column: 17, scope: !655)
!4295 = !DILocation(line: 966, column: 6, scope: !655)
!4296 = !DILocation(line: 966, column: 4, scope: !655)
!4297 = !DILocation(line: 967, column: 6, scope: !4298)
!4298 = distinct !DILexicalBlock(scope: !655, file: !1, line: 967, column: 6)
!4299 = !DILocation(line: 967, column: 8, scope: !4298)
!4300 = !DILocation(line: 967, column: 6, scope: !655)
!4301 = !DILocation(line: 968, column: 11, scope: !4298)
!4302 = !DILocation(line: 968, column: 3, scope: !4298)
!4303 = !DILocation(line: 971, column: 17, scope: !655)
!4304 = !DILocation(line: 971, column: 20, scope: !655)
!4305 = !DILocation(line: 971, column: 6, scope: !655)
!4306 = !DILocation(line: 971, column: 4, scope: !655)
!4307 = !DILocation(line: 972, column: 6, scope: !4308)
!4308 = distinct !DILexicalBlock(scope: !655, file: !1, line: 972, column: 6)
!4309 = !DILocation(line: 972, column: 8, scope: !4308)
!4310 = !DILocation(line: 972, column: 6, scope: !655)
!4311 = !DILocation(line: 973, column: 11, scope: !4308)
!4312 = !DILocation(line: 973, column: 3, scope: !4308)
!4313 = !DILocation(line: 976, column: 17, scope: !655)
!4314 = !DILocation(line: 976, column: 20, scope: !655)
!4315 = !DILocation(line: 976, column: 6, scope: !655)
!4316 = !DILocation(line: 976, column: 4, scope: !655)
!4317 = !DILocation(line: 977, column: 6, scope: !4318)
!4318 = distinct !DILexicalBlock(scope: !655, file: !1, line: 977, column: 6)
!4319 = !DILocation(line: 977, column: 8, scope: !4318)
!4320 = !DILocation(line: 977, column: 6, scope: !655)
!4321 = !DILocation(line: 978, column: 11, scope: !4318)
!4322 = !DILocation(line: 978, column: 3, scope: !4318)
!4323 = !DILocation(line: 981, column: 17, scope: !655)
!4324 = !DILocation(line: 981, column: 6, scope: !655)
!4325 = !DILocation(line: 981, column: 4, scope: !655)
!4326 = !DILocation(line: 982, column: 6, scope: !4327)
!4327 = distinct !DILexicalBlock(scope: !655, file: !1, line: 982, column: 6)
!4328 = !DILocation(line: 982, column: 8, scope: !4327)
!4329 = !DILocation(line: 982, column: 6, scope: !655)
!4330 = !DILocation(line: 983, column: 11, scope: !4327)
!4331 = !DILocation(line: 983, column: 3, scope: !4327)
!4332 = !DILocation(line: 985, column: 6, scope: !4333)
!4333 = distinct !DILexicalBlock(scope: !655, file: !1, line: 985, column: 6)
!4334 = !DILocation(line: 985, column: 17, scope: !4333)
!4335 = !DILocation(line: 985, column: 6, scope: !655)
!4336 = !DILocalVariable(name: "file", scope: !4337, file: !1, line: 986, type: !239)
!4337 = distinct !DILexicalBlock(scope: !4333, file: !1, line: 985, column: 22)
!4338 = !DILocation(line: 986, column: 16, scope: !4337)
!4339 = !DILocation(line: 986, column: 23, scope: !4337)
!4340 = !DILocation(line: 986, column: 28, scope: !4337)
!4341 = !DILocation(line: 986, column: 38, scope: !4337)
!4342 = !DILocation(line: 987, column: 3, scope: !4337)
!4343 = !DILocation(line: 987, column: 9, scope: !4344)
!4344 = !DILexicalBlockFile(scope: !4345, file: !1, discriminator: 1)
!4345 = distinct !DILexicalBlock(scope: !4346, file: !1, line: 987, column: 3)
!4346 = distinct !DILexicalBlock(scope: !4337, file: !1, line: 987, column: 3)
!4347 = !DILocation(line: 987, column: 14, scope: !4344)
!4348 = !DILocation(line: 987, column: 3, scope: !4344)
!4349 = !DILocation(line: 988, column: 8, scope: !4350)
!4350 = distinct !DILexicalBlock(scope: !4351, file: !1, line: 988, column: 8)
!4351 = distinct !DILexicalBlock(scope: !4345, file: !1, line: 987, column: 42)
!4352 = !DILocation(line: 988, column: 14, scope: !4350)
!4353 = !DILocation(line: 988, column: 19, scope: !4350)
!4354 = !DILocation(line: 988, column: 8, scope: !4351)
!4355 = !DILocation(line: 989, column: 5, scope: !4350)
!4356 = !DILocation(line: 990, column: 19, scope: !4351)
!4357 = !DILocation(line: 990, column: 22, scope: !4351)
!4358 = !DILocation(line: 990, column: 28, scope: !4351)
!4359 = !DILocation(line: 990, column: 8, scope: !4351)
!4360 = !DILocation(line: 990, column: 6, scope: !4351)
!4361 = !DILocation(line: 991, column: 8, scope: !4362)
!4362 = distinct !DILexicalBlock(scope: !4351, file: !1, line: 991, column: 8)
!4363 = !DILocation(line: 991, column: 10, scope: !4362)
!4364 = !DILocation(line: 991, column: 8, scope: !4351)
!4365 = !DILocation(line: 992, column: 13, scope: !4362)
!4366 = !DILocation(line: 992, column: 5, scope: !4362)
!4367 = !DILocation(line: 993, column: 3, scope: !4351)
!4368 = !DILocation(line: 987, column: 30, scope: !4369)
!4369 = !DILexicalBlockFile(scope: !4345, file: !1, discriminator: 2)
!4370 = !DILocation(line: 987, column: 36, scope: !4369)
!4371 = !DILocation(line: 987, column: 28, scope: !4369)
!4372 = !DILocation(line: 987, column: 3, scope: !4369)
!4373 = !DILocation(line: 994, column: 2, scope: !4337)
!4374 = !DILocation(line: 996, column: 18, scope: !4375)
!4375 = distinct !DILexicalBlock(scope: !4333, file: !1, line: 994, column: 9)
!4376 = !DILocation(line: 996, column: 21, scope: !4375)
!4377 = !DILocation(line: 996, column: 7, scope: !4375)
!4378 = !DILocation(line: 996, column: 5, scope: !4375)
!4379 = !DILocation(line: 997, column: 7, scope: !4380)
!4380 = distinct !DILexicalBlock(scope: !4375, file: !1, line: 997, column: 7)
!4381 = !DILocation(line: 997, column: 9, scope: !4380)
!4382 = !DILocation(line: 997, column: 7, scope: !4375)
!4383 = !DILocation(line: 998, column: 12, scope: !4380)
!4384 = !DILocation(line: 998, column: 4, scope: !4380)
!4385 = !DILocation(line: 1001, column: 17, scope: !655)
!4386 = !DILocation(line: 1001, column: 6, scope: !655)
!4387 = !DILocation(line: 1001, column: 4, scope: !655)
!4388 = !DILocation(line: 1002, column: 6, scope: !4389)
!4389 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1002, column: 6)
!4390 = !DILocation(line: 1002, column: 8, scope: !4389)
!4391 = !DILocation(line: 1002, column: 6, scope: !655)
!4392 = !DILocation(line: 1003, column: 11, scope: !4389)
!4393 = !DILocation(line: 1003, column: 3, scope: !4389)
!4394 = !DILocation(line: 1008, column: 17, scope: !655)
!4395 = !DILocation(line: 1008, column: 6, scope: !655)
!4396 = !DILocation(line: 1008, column: 4, scope: !655)
!4397 = !DILocation(line: 1009, column: 6, scope: !4398)
!4398 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1009, column: 6)
!4399 = !DILocation(line: 1009, column: 8, scope: !4398)
!4400 = !DILocation(line: 1009, column: 6, scope: !655)
!4401 = !DILocation(line: 1010, column: 11, scope: !4398)
!4402 = !DILocation(line: 1010, column: 3, scope: !4398)
!4403 = !DILocation(line: 1015, column: 17, scope: !655)
!4404 = !DILocation(line: 1015, column: 6, scope: !655)
!4405 = !DILocation(line: 1015, column: 4, scope: !655)
!4406 = !DILocation(line: 1016, column: 6, scope: !4407)
!4407 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1016, column: 6)
!4408 = !DILocation(line: 1016, column: 8, scope: !4407)
!4409 = !DILocation(line: 1016, column: 6, scope: !655)
!4410 = !DILocation(line: 1017, column: 11, scope: !4407)
!4411 = !DILocation(line: 1017, column: 3, scope: !4407)
!4412 = !DILocation(line: 1020, column: 17, scope: !655)
!4413 = !DILocation(line: 1020, column: 20, scope: !655)
!4414 = !DILocation(line: 1020, column: 6, scope: !655)
!4415 = !DILocation(line: 1020, column: 4, scope: !655)
!4416 = !DILocation(line: 1021, column: 6, scope: !4417)
!4417 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1021, column: 6)
!4418 = !DILocation(line: 1021, column: 8, scope: !4417)
!4419 = !DILocation(line: 1021, column: 6, scope: !655)
!4420 = !DILocation(line: 1022, column: 11, scope: !4417)
!4421 = !DILocation(line: 1022, column: 3, scope: !4417)
!4422 = !DILocation(line: 1025, column: 17, scope: !655)
!4423 = !DILocation(line: 1025, column: 6, scope: !655)
!4424 = !DILocation(line: 1025, column: 4, scope: !655)
!4425 = !DILocation(line: 1026, column: 6, scope: !4426)
!4426 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1026, column: 6)
!4427 = !DILocation(line: 1026, column: 8, scope: !4426)
!4428 = !DILocation(line: 1026, column: 6, scope: !655)
!4429 = !DILocation(line: 1027, column: 11, scope: !4426)
!4430 = !DILocation(line: 1027, column: 3, scope: !4426)
!4431 = !DILocation(line: 1029, column: 10, scope: !4432)
!4432 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1029, column: 2)
!4433 = !DILocation(line: 1029, column: 7, scope: !4432)
!4434 = !DILocation(line: 1029, column: 15, scope: !4435)
!4435 = !DILexicalBlockFile(scope: !4436, file: !1, discriminator: 1)
!4436 = distinct !DILexicalBlock(scope: !4432, file: !1, line: 1029, column: 2)
!4437 = !DILocation(line: 1029, column: 20, scope: !4435)
!4438 = !DILocation(line: 1029, column: 18, scope: !4435)
!4439 = !DILocation(line: 1029, column: 2, scope: !4435)
!4440 = !DILocation(line: 1031, column: 18, scope: !4441)
!4441 = distinct !DILexicalBlock(scope: !4436, file: !1, line: 1029, column: 38)
!4442 = !DILocation(line: 1031, column: 21, scope: !4441)
!4443 = !DILocation(line: 1031, column: 7, scope: !4441)
!4444 = !DILocation(line: 1031, column: 5, scope: !4441)
!4445 = !DILocation(line: 1032, column: 7, scope: !4446)
!4446 = distinct !DILexicalBlock(scope: !4441, file: !1, line: 1032, column: 7)
!4447 = !DILocation(line: 1032, column: 9, scope: !4446)
!4448 = !DILocation(line: 1032, column: 7, scope: !4441)
!4449 = !DILocation(line: 1033, column: 12, scope: !4446)
!4450 = !DILocation(line: 1033, column: 4, scope: !4446)
!4451 = !DILocation(line: 1035, column: 10, scope: !4452)
!4452 = distinct !DILexicalBlock(scope: !4441, file: !1, line: 1035, column: 3)
!4453 = !DILocation(line: 1035, column: 8, scope: !4452)
!4454 = !DILocation(line: 1035, column: 15, scope: !4455)
!4455 = !DILexicalBlockFile(scope: !4456, file: !1, discriminator: 1)
!4456 = distinct !DILexicalBlock(scope: !4452, file: !1, line: 1035, column: 3)
!4457 = !DILocation(line: 1035, column: 19, scope: !4455)
!4458 = !DILocation(line: 1035, column: 17, scope: !4455)
!4459 = !DILocation(line: 1035, column: 3, scope: !4455)
!4460 = !DILocalVariable(name: "codec_id", scope: !4461, file: !1, line: 1036, type: !53)
!4461 = distinct !DILexicalBlock(scope: !4456, file: !1, line: 1035, column: 35)
!4462 = !DILocation(line: 1036, column: 13, scope: !4461)
!4463 = !DILocation(line: 1036, column: 31, scope: !4461)
!4464 = !DILocation(line: 1036, column: 24, scope: !4461)
!4465 = !DILocation(line: 1036, column: 34, scope: !4461)
!4466 = !DILocation(line: 1039, column: 20, scope: !4461)
!4467 = !DILocation(line: 1039, column: 32, scope: !4461)
!4468 = !DILocation(line: 1039, column: 4, scope: !4461)
!4469 = !DILocation(line: 1040, column: 20, scope: !4470)
!4470 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1040, column: 4)
!4471 = !DILocation(line: 1040, column: 9, scope: !4470)
!4472 = !DILocation(line: 1040, column: 25, scope: !4473)
!4473 = !DILexicalBlockFile(scope: !4474, file: !1, discriminator: 1)
!4474 = distinct !DILexicalBlock(scope: !4470, file: !1, line: 1040, column: 4)
!4475 = !DILocation(line: 1040, column: 36, scope: !4473)
!4476 = !DILocation(line: 1040, column: 4, scope: !4473)
!4477 = !DILocation(line: 1041, column: 24, scope: !4478)
!4478 = distinct !DILexicalBlock(scope: !4479, file: !1, line: 1041, column: 9)
!4479 = distinct !DILexicalBlock(scope: !4474, file: !1, line: 1040, column: 55)
!4480 = !DILocation(line: 1041, column: 22, scope: !4478)
!4481 = !DILocation(line: 1041, column: 9, scope: !4478)
!4482 = !DILocation(line: 1041, column: 9, scope: !4479)
!4483 = !DILocation(line: 1042, column: 6, scope: !4478)
!4484 = !DILocation(line: 1043, column: 4, scope: !4479)
!4485 = !DILocation(line: 1040, column: 51, scope: !4486)
!4486 = !DILexicalBlockFile(scope: !4474, file: !1, discriminator: 2)
!4487 = !DILocation(line: 1040, column: 4, scope: !4486)
!4488 = !DILocation(line: 1044, column: 8, scope: !4489)
!4489 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1044, column: 8)
!4490 = !DILocation(line: 1044, column: 19, scope: !4489)
!4491 = !DILocation(line: 1044, column: 8, scope: !4461)
!4492 = !DILocation(line: 1045, column: 16, scope: !4489)
!4493 = !DILocation(line: 1045, column: 5, scope: !4489)
!4494 = !DILocation(line: 1046, column: 15, scope: !4495)
!4495 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1046, column: 8)
!4496 = !DILocation(line: 1046, column: 8, scope: !4495)
!4497 = !DILocation(line: 1046, column: 18, scope: !4495)
!4498 = !DILocation(line: 1046, column: 8, scope: !4461)
!4499 = !DILocation(line: 1047, column: 20, scope: !4495)
!4500 = !DILocation(line: 1047, column: 23, scope: !4495)
!4501 = !DILocation(line: 1047, column: 34, scope: !4495)
!4502 = !DILocation(line: 1047, column: 9, scope: !4495)
!4503 = !DILocation(line: 1047, column: 7, scope: !4495)
!4504 = !DILocation(line: 1047, column: 5, scope: !4495)
!4505 = !DILocation(line: 1049, column: 20, scope: !4495)
!4506 = !DILocation(line: 1049, column: 23, scope: !4495)
!4507 = !DILocation(line: 1049, column: 9, scope: !4495)
!4508 = !DILocation(line: 1049, column: 7, scope: !4495)
!4509 = !DILocation(line: 1050, column: 8, scope: !4510)
!4510 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1050, column: 8)
!4511 = !DILocation(line: 1050, column: 10, scope: !4510)
!4512 = !DILocation(line: 1050, column: 8, scope: !4461)
!4513 = !DILocation(line: 1051, column: 13, scope: !4510)
!4514 = !DILocation(line: 1051, column: 5, scope: !4510)
!4515 = !DILocation(line: 1054, column: 15, scope: !4461)
!4516 = !DILocation(line: 1055, column: 26, scope: !4461)
!4517 = !DILocation(line: 1055, column: 43, scope: !4461)
!4518 = !DILocation(line: 1055, column: 42, scope: !4461)
!4519 = !DILocation(line: 1055, column: 30, scope: !4461)
!4520 = !DILocation(line: 1056, column: 5, scope: !4461)
!4521 = !DILocation(line: 1055, column: 13, scope: !4461)
!4522 = !DILocation(line: 1055, column: 8, scope: !4461)
!4523 = !DILocation(line: 1055, column: 6, scope: !4461)
!4524 = !DILocation(line: 1057, column: 8, scope: !4525)
!4525 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1057, column: 8)
!4526 = !DILocation(line: 1057, column: 10, scope: !4525)
!4527 = !DILocation(line: 1057, column: 8, scope: !4461)
!4528 = !DILocation(line: 1058, column: 13, scope: !4525)
!4529 = !DILocation(line: 1058, column: 5, scope: !4525)
!4530 = !DILocation(line: 1060, column: 15, scope: !4531)
!4531 = distinct !DILexicalBlock(scope: !4461, file: !1, line: 1060, column: 8)
!4532 = !DILocation(line: 1060, column: 8, scope: !4531)
!4533 = !DILocation(line: 1060, column: 18, scope: !4531)
!4534 = !DILocation(line: 1060, column: 8, scope: !4461)
!4535 = !DILocation(line: 1062, column: 20, scope: !4536)
!4536 = distinct !DILexicalBlock(scope: !4531, file: !1, line: 1060, column: 29)
!4537 = !DILocation(line: 1062, column: 30, scope: !4536)
!4538 = !DILocation(line: 1062, column: 23, scope: !4536)
!4539 = !DILocation(line: 1062, column: 33, scope: !4536)
!4540 = !DILocation(line: 1062, column: 9, scope: !4536)
!4541 = !DILocation(line: 1062, column: 7, scope: !4536)
!4542 = !DILocation(line: 1063, column: 9, scope: !4543)
!4543 = distinct !DILexicalBlock(scope: !4536, file: !1, line: 1063, column: 9)
!4544 = !DILocation(line: 1063, column: 11, scope: !4543)
!4545 = !DILocation(line: 1063, column: 9, scope: !4536)
!4546 = !DILocation(line: 1064, column: 14, scope: !4543)
!4547 = !DILocation(line: 1064, column: 6, scope: !4543)
!4548 = !DILocation(line: 1067, column: 27, scope: !4536)
!4549 = !DILocation(line: 1067, column: 37, scope: !4536)
!4550 = !DILocation(line: 1067, column: 30, scope: !4536)
!4551 = !DILocation(line: 1067, column: 40, scope: !4536)
!4552 = !DILocation(line: 1068, column: 13, scope: !4536)
!4553 = !DILocation(line: 1068, column: 6, scope: !4536)
!4554 = !DILocation(line: 1068, column: 16, scope: !4536)
!4555 = !DILocation(line: 1067, column: 14, scope: !4536)
!4556 = !DILocation(line: 1067, column: 9, scope: !4536)
!4557 = !DILocation(line: 1067, column: 7, scope: !4536)
!4558 = !DILocation(line: 1069, column: 9, scope: !4559)
!4559 = distinct !DILexicalBlock(scope: !4536, file: !1, line: 1069, column: 9)
!4560 = !DILocation(line: 1069, column: 11, scope: !4559)
!4561 = !DILocation(line: 1069, column: 9, scope: !4536)
!4562 = !DILocation(line: 1070, column: 14, scope: !4559)
!4563 = !DILocation(line: 1070, column: 6, scope: !4559)
!4564 = !DILocation(line: 1071, column: 4, scope: !4536)
!4565 = !DILocation(line: 1072, column: 3, scope: !4461)
!4566 = !DILocation(line: 1035, column: 31, scope: !4567)
!4567 = !DILexicalBlockFile(scope: !4456, file: !1, discriminator: 2)
!4568 = !DILocation(line: 1035, column: 3, scope: !4567)
!4569 = !DILocation(line: 1073, column: 2, scope: !4441)
!4570 = !DILocation(line: 1029, column: 34, scope: !4571)
!4571 = !DILexicalBlockFile(scope: !4436, file: !1, discriminator: 2)
!4572 = !DILocation(line: 1029, column: 2, scope: !4571)
!4573 = !DILocation(line: 1078, column: 17, scope: !655)
!4574 = !DILocation(line: 1078, column: 6, scope: !655)
!4575 = !DILocation(line: 1078, column: 4, scope: !655)
!4576 = !DILocation(line: 1079, column: 6, scope: !4577)
!4577 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1079, column: 6)
!4578 = !DILocation(line: 1079, column: 8, scope: !4577)
!4579 = !DILocation(line: 1079, column: 6, scope: !655)
!4580 = !DILocation(line: 1080, column: 11, scope: !4577)
!4581 = !DILocation(line: 1080, column: 3, scope: !4577)
!4582 = !DILocation(line: 1082, column: 6, scope: !4583)
!4583 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1082, column: 6)
!4584 = !DILocation(line: 1082, column: 17, scope: !4583)
!4585 = !DILocation(line: 1082, column: 6, scope: !655)
!4586 = !DILocalVariable(name: "file", scope: !4587, file: !1, line: 1083, type: !239)
!4587 = distinct !DILexicalBlock(scope: !4583, file: !1, line: 1082, column: 22)
!4588 = !DILocation(line: 1083, column: 16, scope: !4587)
!4589 = !DILocation(line: 1083, column: 23, scope: !4587)
!4590 = !DILocation(line: 1083, column: 28, scope: !4587)
!4591 = !DILocation(line: 1083, column: 38, scope: !4587)
!4592 = !DILocation(line: 1084, column: 3, scope: !4587)
!4593 = !DILocation(line: 1084, column: 9, scope: !4594)
!4594 = !DILexicalBlockFile(scope: !4595, file: !1, discriminator: 1)
!4595 = distinct !DILexicalBlock(scope: !4596, file: !1, line: 1084, column: 3)
!4596 = distinct !DILexicalBlock(scope: !4587, file: !1, line: 1084, column: 3)
!4597 = !DILocation(line: 1084, column: 14, scope: !4594)
!4598 = !DILocation(line: 1084, column: 3, scope: !4594)
!4599 = !DILocation(line: 1085, column: 8, scope: !4600)
!4600 = distinct !DILexicalBlock(scope: !4601, file: !1, line: 1085, column: 8)
!4601 = distinct !DILexicalBlock(scope: !4595, file: !1, line: 1084, column: 42)
!4602 = !DILocation(line: 1085, column: 14, scope: !4600)
!4603 = !DILocation(line: 1085, column: 19, scope: !4600)
!4604 = !DILocation(line: 1085, column: 8, scope: !4601)
!4605 = !DILocation(line: 1086, column: 5, scope: !4600)
!4606 = !DILocation(line: 1087, column: 19, scope: !4601)
!4607 = !DILocation(line: 1087, column: 22, scope: !4601)
!4608 = !DILocation(line: 1087, column: 28, scope: !4601)
!4609 = !DILocation(line: 1087, column: 8, scope: !4601)
!4610 = !DILocation(line: 1087, column: 6, scope: !4601)
!4611 = !DILocation(line: 1088, column: 8, scope: !4612)
!4612 = distinct !DILexicalBlock(scope: !4601, file: !1, line: 1088, column: 8)
!4613 = !DILocation(line: 1088, column: 10, scope: !4612)
!4614 = !DILocation(line: 1088, column: 8, scope: !4601)
!4615 = !DILocation(line: 1089, column: 13, scope: !4612)
!4616 = !DILocation(line: 1089, column: 5, scope: !4612)
!4617 = !DILocation(line: 1090, column: 3, scope: !4601)
!4618 = !DILocation(line: 1084, column: 30, scope: !4619)
!4619 = !DILexicalBlockFile(scope: !4595, file: !1, discriminator: 2)
!4620 = !DILocation(line: 1084, column: 36, scope: !4619)
!4621 = !DILocation(line: 1084, column: 28, scope: !4619)
!4622 = !DILocation(line: 1084, column: 3, scope: !4619)
!4623 = !DILocation(line: 1092, column: 2, scope: !4587)
!4624 = !DILocation(line: 1094, column: 18, scope: !4625)
!4625 = distinct !DILexicalBlock(scope: !4583, file: !1, line: 1092, column: 9)
!4626 = !DILocation(line: 1094, column: 21, scope: !4625)
!4627 = !DILocation(line: 1094, column: 7, scope: !4625)
!4628 = !DILocation(line: 1094, column: 5, scope: !4625)
!4629 = !DILocation(line: 1095, column: 7, scope: !4630)
!4630 = distinct !DILexicalBlock(scope: !4625, file: !1, line: 1095, column: 7)
!4631 = !DILocation(line: 1095, column: 9, scope: !4630)
!4632 = !DILocation(line: 1095, column: 7, scope: !4625)
!4633 = !DILocation(line: 1096, column: 12, scope: !4630)
!4634 = !DILocation(line: 1096, column: 4, scope: !4630)
!4635 = !DILocation(line: 1099, column: 7, scope: !4636)
!4636 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1099, column: 6)
!4637 = !DILocation(line: 1099, column: 6, scope: !655)
!4638 = !DILocalVariable(name: "crc", scope: !4639, file: !1, line: 1100, type: !4640)
!4639 = distinct !DILexicalBlock(scope: !4636, file: !1, line: 1099, column: 16)
!4640 = !DICompositeType(tag: DW_TAG_array_type, baseType: !257, size: 32, align: 8, elements: !4641)
!4641 = !{!4642}
!4642 = !DISubrange(count: 4)
!4643 = !DILocation(line: 1100, column: 11, scope: !4639)
!4644 = !DILocation(line: 1104, column: 18, scope: !4639)
!4645 = !DILocation(line: 1104, column: 7, scope: !4639)
!4646 = !DILocation(line: 1104, column: 5, scope: !4639)
!4647 = !DILocation(line: 1105, column: 7, scope: !4648)
!4648 = distinct !DILexicalBlock(scope: !4639, file: !1, line: 1105, column: 7)
!4649 = !DILocation(line: 1105, column: 9, scope: !4648)
!4650 = !DILocation(line: 1105, column: 7, scope: !4639)
!4651 = !DILocation(line: 1106, column: 12, scope: !4648)
!4652 = !DILocation(line: 1106, column: 4, scope: !4648)
!4653 = !DILocation(line: 1109, column: 18, scope: !4639)
!4654 = !DILocation(line: 1109, column: 7, scope: !4639)
!4655 = !DILocation(line: 1109, column: 5, scope: !4639)
!4656 = !DILocation(line: 1110, column: 7, scope: !4657)
!4657 = distinct !DILexicalBlock(scope: !4639, file: !1, line: 1110, column: 7)
!4658 = !DILocation(line: 1110, column: 9, scope: !4657)
!4659 = !DILocation(line: 1110, column: 7, scope: !4639)
!4660 = !DILocation(line: 1111, column: 12, scope: !4657)
!4661 = !DILocation(line: 1111, column: 4, scope: !4657)
!4662 = !DILocation(line: 1112, column: 19, scope: !4639)
!4663 = !DILocation(line: 1112, column: 24, scope: !4639)
!4664 = !DILocation(line: 1112, column: 3, scope: !4639)
!4665 = !DILocation(line: 1113, column: 25, scope: !4639)
!4666 = !DILocation(line: 1113, column: 28, scope: !4639)
!4667 = !DILocation(line: 1113, column: 12, scope: !4639)
!4668 = !DILocation(line: 1113, column: 7, scope: !4639)
!4669 = !DILocation(line: 1113, column: 5, scope: !4639)
!4670 = !DILocation(line: 1114, column: 7, scope: !4671)
!4671 = distinct !DILexicalBlock(scope: !4639, file: !1, line: 1114, column: 7)
!4672 = !DILocation(line: 1114, column: 9, scope: !4671)
!4673 = !DILocation(line: 1114, column: 7, scope: !4639)
!4674 = !DILocation(line: 1115, column: 12, scope: !4671)
!4675 = !DILocation(line: 1115, column: 4, scope: !4671)
!4676 = !DILocation(line: 1116, column: 2, scope: !4639)
!4677 = !DILocation(line: 1119, column: 17, scope: !655)
!4678 = !DILocation(line: 1119, column: 6, scope: !655)
!4679 = !DILocation(line: 1119, column: 4, scope: !655)
!4680 = !DILocation(line: 1120, column: 6, scope: !4681)
!4681 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1120, column: 6)
!4682 = !DILocation(line: 1120, column: 8, scope: !4681)
!4683 = !DILocation(line: 1120, column: 6, scope: !655)
!4684 = !DILocation(line: 1121, column: 11, scope: !4681)
!4685 = !DILocation(line: 1121, column: 3, scope: !4681)
!4686 = !DILocation(line: 1123, column: 6, scope: !4687)
!4687 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1123, column: 6)
!4688 = !DILocation(line: 1123, column: 6, scope: !655)
!4689 = !DILocation(line: 1127, column: 27, scope: !4690)
!4690 = distinct !DILexicalBlock(scope: !4687, file: !1, line: 1123, column: 15)
!4691 = !DILocation(line: 1127, column: 30, scope: !4690)
!4692 = !DILocation(line: 1127, column: 7, scope: !4690)
!4693 = !DILocation(line: 1127, column: 5, scope: !4690)
!4694 = !DILocation(line: 1128, column: 7, scope: !4695)
!4695 = distinct !DILexicalBlock(scope: !4690, file: !1, line: 1128, column: 7)
!4696 = !DILocation(line: 1128, column: 9, scope: !4695)
!4697 = !DILocation(line: 1128, column: 7, scope: !4690)
!4698 = !DILocation(line: 1129, column: 12, scope: !4695)
!4699 = !DILocation(line: 1129, column: 4, scope: !4695)
!4700 = !DILocation(line: 1130, column: 2, scope: !4690)
!4701 = !DILocation(line: 1134, column: 17, scope: !655)
!4702 = !DILocation(line: 1134, column: 6, scope: !655)
!4703 = !DILocation(line: 1134, column: 4, scope: !655)
!4704 = !DILocation(line: 1135, column: 6, scope: !4705)
!4705 = distinct !DILexicalBlock(scope: !655, file: !1, line: 1135, column: 6)
!4706 = !DILocation(line: 1135, column: 8, scope: !4705)
!4707 = !DILocation(line: 1135, column: 6, scope: !655)
!4708 = !DILocation(line: 1136, column: 11, scope: !4705)
!4709 = !DILocation(line: 1136, column: 3, scope: !4705)
!4710 = !DILocation(line: 1138, column: 2, scope: !655)
!4711 = !DILocation(line: 1139, column: 1, scope: !655)
!4712 = !DILocalVariable(name: "pp", arg: 1, scope: !665, file: !618, line: 188, type: !164)
!4713 = !DILocation(line: 188, column: 23, scope: !665)
!4714 = !DILocalVariable(name: "u", arg: 2, scope: !665, file: !618, line: 188, type: !237)
!4715 = !DILocation(line: 188, column: 36, scope: !665)
!4716 = !DILocalVariable(name: "p", scope: !665, file: !618, line: 190, type: !420)
!4717 = !DILocation(line: 190, column: 17, scope: !665)
!4718 = !DILocation(line: 190, column: 38, scope: !665)
!4719 = !DILocation(line: 192, column: 18, scope: !665)
!4720 = !DILocation(line: 192, column: 32, scope: !665)
!4721 = !DILocation(line: 192, column: 34, scope: !665)
!4722 = !DILocation(line: 192, column: 21, scope: !665)
!4723 = !DILocation(line: 192, column: 2, scope: !665)
!4724 = !DILocation(line: 193, column: 18, scope: !665)
!4725 = !DILocation(line: 193, column: 20, scope: !665)
!4726 = !DILocation(line: 193, column: 36, scope: !665)
!4727 = !DILocation(line: 193, column: 38, scope: !665)
!4728 = !DILocation(line: 193, column: 25, scope: !665)
!4729 = !DILocation(line: 193, column: 2, scope: !665)
!4730 = !DILocation(line: 194, column: 1, scope: !665)
!4731 = !DILocalVariable(name: "a", arg: 1, scope: !666, file: !1, line: 665, type: !44)
!4732 = !DILocation(line: 665, column: 32, scope: !666)
!4733 = !DILocalVariable(name: "offset", arg: 2, scope: !666, file: !1, line: 665, type: !237)
!4734 = !DILocation(line: 665, column: 44, scope: !666)
!4735 = !DILocalVariable(name: "length", arg: 3, scope: !666, file: !1, line: 665, type: !237)
!4736 = !DILocation(line: 665, column: 61, scope: !666)
!4737 = !DILocalVariable(name: "zip", scope: !666, file: !1, line: 667, type: !232)
!4738 = !DILocation(line: 667, column: 16, scope: !666)
!4739 = !DILocalVariable(name: "r", scope: !666, file: !1, line: 668, type: !63)
!4740 = !DILocation(line: 668, column: 6, scope: !666)
!4741 = !DILocation(line: 670, column: 24, scope: !666)
!4742 = !DILocation(line: 670, column: 27, scope: !666)
!4743 = !DILocation(line: 670, column: 8, scope: !666)
!4744 = !DILocation(line: 670, column: 6, scope: !666)
!4745 = !DILocation(line: 671, column: 6, scope: !4746)
!4746 = distinct !DILexicalBlock(scope: !666, file: !1, line: 671, column: 6)
!4747 = !DILocation(line: 671, column: 11, scope: !4746)
!4748 = !DILocation(line: 671, column: 23, scope: !4746)
!4749 = !DILocation(line: 671, column: 27, scope: !4746)
!4750 = !DILocation(line: 672, column: 12, scope: !4746)
!4751 = !DILocation(line: 672, column: 17, scope: !4746)
!4752 = !DILocation(line: 672, column: 26, scope: !4746)
!4753 = !DILocation(line: 672, column: 6, scope: !4746)
!4754 = !DILocation(line: 672, column: 44, scope: !4746)
!4755 = !DILocation(line: 671, column: 6, scope: !4756)
!4756 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 1)
!4757 = !DILocation(line: 673, column: 23, scope: !4758)
!4758 = distinct !DILexicalBlock(scope: !4746, file: !1, line: 672, column: 49)
!4759 = !DILocation(line: 673, column: 26, scope: !4758)
!4760 = !DILocation(line: 673, column: 36, scope: !4758)
!4761 = !DILocation(line: 673, column: 3, scope: !4762)
!4762 = !DILexicalBlockFile(scope: !4758, file: !1, discriminator: 1)
!4763 = !DILocation(line: 674, column: 3, scope: !4758)
!4764 = !DILocation(line: 676, column: 2, scope: !666)
!4765 = !DILocation(line: 676, column: 9, scope: !4756)
!4766 = !DILocation(line: 676, column: 2, scope: !4756)
!4767 = !DILocalVariable(name: "rsize", scope: !4768, file: !1, line: 677, type: !85)
!4768 = distinct !DILexicalBlock(scope: !666, file: !1, line: 676, column: 17)
!4769 = !DILocation(line: 677, column: 10, scope: !4768)
!4770 = !DILocalVariable(name: "rs", scope: !4768, file: !1, line: 678, type: !78)
!4771 = !DILocation(line: 678, column: 11, scope: !4768)
!4772 = !DILocalVariable(name: "wb", scope: !4768, file: !1, line: 679, type: !420)
!4773 = !DILocation(line: 679, column: 18, scope: !4768)
!4774 = !DILocation(line: 681, column: 7, scope: !4775)
!4775 = distinct !DILexicalBlock(scope: !4768, file: !1, line: 681, column: 7)
!4776 = !DILocation(line: 681, column: 16, scope: !4775)
!4777 = !DILocation(line: 681, column: 21, scope: !4775)
!4778 = !DILocation(line: 681, column: 14, scope: !4775)
!4779 = !DILocation(line: 681, column: 7, scope: !4768)
!4780 = !DILocation(line: 682, column: 12, scope: !4775)
!4781 = !DILocation(line: 682, column: 17, scope: !4775)
!4782 = !DILocation(line: 682, column: 10, scope: !4775)
!4783 = !DILocation(line: 682, column: 4, scope: !4775)
!4784 = !DILocation(line: 684, column: 20, scope: !4775)
!4785 = !DILocation(line: 684, column: 10, scope: !4775)
!4786 = !DILocation(line: 685, column: 8, scope: !4768)
!4787 = !DILocation(line: 685, column: 13, scope: !4768)
!4788 = !DILocation(line: 685, column: 43, scope: !4768)
!4789 = !DILocation(line: 685, column: 48, scope: !4768)
!4790 = !DILocation(line: 685, column: 41, scope: !4768)
!4791 = !DILocation(line: 685, column: 19, scope: !4768)
!4792 = !DILocation(line: 685, column: 6, scope: !4768)
!4793 = !DILocation(line: 686, column: 13, scope: !4768)
!4794 = !DILocation(line: 686, column: 18, scope: !4768)
!4795 = !DILocation(line: 686, column: 27, scope: !4768)
!4796 = !DILocation(line: 686, column: 31, scope: !4768)
!4797 = !DILocation(line: 686, column: 8, scope: !4768)
!4798 = !DILocation(line: 686, column: 6, scope: !4768)
!4799 = !DILocation(line: 687, column: 7, scope: !4800)
!4800 = distinct !DILexicalBlock(scope: !4768, file: !1, line: 687, column: 7)
!4801 = !DILocation(line: 687, column: 10, scope: !4800)
!4802 = !DILocation(line: 687, column: 7, scope: !4768)
!4803 = !DILocation(line: 688, column: 24, scope: !4804)
!4804 = distinct !DILexicalBlock(scope: !4800, file: !1, line: 687, column: 15)
!4805 = !DILocation(line: 688, column: 27, scope: !4804)
!4806 = !DILocation(line: 688, column: 37, scope: !4804)
!4807 = !DILocation(line: 690, column: 18, scope: !4804)
!4808 = !DILocation(line: 688, column: 4, scope: !4809)
!4809 = !DILexicalBlockFile(scope: !4804, file: !1, discriminator: 1)
!4810 = !DILocation(line: 691, column: 4, scope: !4804)
!4811 = !DILocation(line: 693, column: 7, scope: !4812)
!4812 = distinct !DILexicalBlock(scope: !4768, file: !1, line: 693, column: 7)
!4813 = !DILocation(line: 693, column: 10, scope: !4812)
!4814 = !DILocation(line: 693, column: 7, scope: !4768)
!4815 = !DILocation(line: 694, column: 24, scope: !4816)
!4816 = distinct !DILexicalBlock(scope: !4812, file: !1, line: 693, column: 16)
!4817 = !DILocation(line: 694, column: 27, scope: !4816)
!4818 = !DILocation(line: 694, column: 4, scope: !4816)
!4819 = !DILocation(line: 696, column: 4, scope: !4816)
!4820 = !DILocation(line: 698, column: 27, scope: !4768)
!4821 = !DILocation(line: 698, column: 3, scope: !4768)
!4822 = !DILocation(line: 698, column: 8, scope: !4768)
!4823 = !DILocation(line: 698, column: 24, scope: !4768)
!4824 = !DILocation(line: 699, column: 13, scope: !4768)
!4825 = !DILocation(line: 699, column: 10, scope: !4768)
!4826 = !DILocation(line: 700, column: 7, scope: !4827)
!4827 = distinct !DILexicalBlock(scope: !4768, file: !1, line: 700, column: 7)
!4828 = !DILocation(line: 700, column: 12, scope: !4827)
!4829 = !DILocation(line: 700, column: 28, scope: !4827)
!4830 = !DILocation(line: 700, column: 7, scope: !4768)
!4831 = !DILocation(line: 701, column: 20, scope: !4832)
!4832 = distinct !DILexicalBlock(scope: !4827, file: !1, line: 700, column: 34)
!4833 = !DILocation(line: 701, column: 8, scope: !4832)
!4834 = !DILocation(line: 701, column: 6, scope: !4832)
!4835 = !DILocation(line: 702, column: 8, scope: !4836)
!4836 = distinct !DILexicalBlock(scope: !4832, file: !1, line: 702, column: 8)
!4837 = !DILocation(line: 702, column: 10, scope: !4836)
!4838 = !DILocation(line: 702, column: 8, scope: !4832)
!4839 = !DILocation(line: 703, column: 13, scope: !4836)
!4840 = !DILocation(line: 703, column: 5, scope: !4836)
!4841 = !DILocation(line: 704, column: 3, scope: !4832)
!4842 = !DILocation(line: 676, column: 2, scope: !4843)
!4843 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 2)
!4844 = !DILocation(line: 706, column: 2, scope: !666)
!4845 = !DILocation(line: 707, column: 1, scope: !666)
!4846 = !DILocalVariable(name: "a", arg: 1, scope: !669, file: !1, line: 649, type: !44)
!4847 = !DILocation(line: 649, column: 35, scope: !669)
!4848 = !DILocalVariable(name: "zip", scope: !669, file: !1, line: 651, type: !232)
!4849 = !DILocation(line: 651, column: 16, scope: !669)
!4850 = !DILocalVariable(name: "r", scope: !669, file: !1, line: 652, type: !63)
!4851 = !DILocation(line: 652, column: 6, scope: !669)
!4852 = !DILocalVariable(name: "s", scope: !669, file: !1, line: 653, type: !85)
!4853 = !DILocation(line: 653, column: 9, scope: !669)
!4854 = !DILocation(line: 655, column: 24, scope: !669)
!4855 = !DILocation(line: 655, column: 27, scope: !669)
!4856 = !DILocation(line: 655, column: 8, scope: !669)
!4857 = !DILocation(line: 655, column: 6, scope: !669)
!4858 = !DILocation(line: 656, column: 27, scope: !669)
!4859 = !DILocation(line: 656, column: 32, scope: !669)
!4860 = !DILocation(line: 656, column: 25, scope: !669)
!4861 = !DILocation(line: 656, column: 4, scope: !669)
!4862 = !DILocation(line: 657, column: 29, scope: !669)
!4863 = !DILocation(line: 657, column: 32, scope: !669)
!4864 = !DILocation(line: 657, column: 37, scope: !669)
!4865 = !DILocation(line: 657, column: 44, scope: !669)
!4866 = !DILocation(line: 657, column: 6, scope: !669)
!4867 = !DILocation(line: 657, column: 4, scope: !669)
!4868 = !DILocation(line: 658, column: 6, scope: !4869)
!4869 = distinct !DILexicalBlock(scope: !669, file: !1, line: 658, column: 6)
!4870 = !DILocation(line: 658, column: 8, scope: !4869)
!4871 = !DILocation(line: 658, column: 6, scope: !669)
!4872 = !DILocation(line: 659, column: 11, scope: !4869)
!4873 = !DILocation(line: 659, column: 3, scope: !4869)
!4874 = !DILocation(line: 660, column: 2, scope: !669)
!4875 = !DILocation(line: 660, column: 7, scope: !669)
!4876 = !DILocation(line: 660, column: 23, scope: !669)
!4877 = !DILocation(line: 661, column: 10, scope: !669)
!4878 = !DILocation(line: 661, column: 2, scope: !669)
!4879 = !DILocation(line: 662, column: 1, scope: !669)
!4880 = !DILocalVariable(name: "a", arg: 1, scope: !646, file: !1, line: 1156, type: !44)
!4881 = !DILocation(line: 1156, column: 33, scope: !646)
!4882 = !DILocalVariable(name: "type", arg: 2, scope: !646, file: !1, line: 1156, type: !257)
!4883 = !DILocation(line: 1156, column: 44, scope: !646)
!4884 = !DILocalVariable(name: "flg", arg: 3, scope: !646, file: !1, line: 1156, type: !53)
!4885 = !DILocation(line: 1156, column: 59, scope: !646)
!4886 = !DILocalVariable(name: "ti", arg: 4, scope: !646, file: !1, line: 1156, type: !63)
!4887 = !DILocation(line: 1156, column: 68, scope: !646)
!4888 = !DILocalVariable(name: "filetime", scope: !646, file: !1, line: 1158, type: !4269)
!4889 = !DILocation(line: 1158, column: 10, scope: !646)
!4890 = !DILocalVariable(name: "zip", scope: !646, file: !1, line: 1159, type: !232)
!4891 = !DILocation(line: 1159, column: 16, scope: !646)
!4892 = !DILocation(line: 1159, column: 38, scope: !646)
!4893 = !DILocation(line: 1159, column: 41, scope: !646)
!4894 = !DILocation(line: 1159, column: 22, scope: !646)
!4895 = !DILocalVariable(name: "file", scope: !646, file: !1, line: 1160, type: !239)
!4896 = !DILocation(line: 1160, column: 15, scope: !646)
!4897 = !DILocalVariable(name: "r", scope: !646, file: !1, line: 1161, type: !63)
!4898 = !DILocation(line: 1161, column: 6, scope: !646)
!4899 = !DILocalVariable(name: "b", scope: !646, file: !1, line: 1162, type: !257)
!4900 = !DILocation(line: 1162, column: 10, scope: !646)
!4901 = !DILocalVariable(name: "mask", scope: !646, file: !1, line: 1162, type: !257)
!4902 = !DILocation(line: 1162, column: 13, scope: !646)
!4903 = !DILocation(line: 1167, column: 37, scope: !4904)
!4904 = distinct !DILexicalBlock(scope: !646, file: !1, line: 1167, column: 6)
!4905 = !DILocation(line: 1167, column: 6, scope: !4904)
!4906 = !DILocation(line: 1167, column: 11, scope: !4904)
!4907 = !DILocation(line: 1167, column: 44, scope: !4904)
!4908 = !DILocation(line: 1167, column: 49, scope: !4904)
!4909 = !DILocation(line: 1167, column: 41, scope: !4904)
!4910 = !DILocation(line: 1167, column: 6, scope: !646)
!4911 = !DILocation(line: 1169, column: 18, scope: !4912)
!4912 = distinct !DILexicalBlock(scope: !4904, file: !1, line: 1167, column: 69)
!4913 = !DILocation(line: 1169, column: 21, scope: !4912)
!4914 = !DILocation(line: 1169, column: 7, scope: !4912)
!4915 = !DILocation(line: 1169, column: 5, scope: !4912)
!4916 = !DILocation(line: 1170, column: 7, scope: !4917)
!4917 = distinct !DILexicalBlock(scope: !4912, file: !1, line: 1170, column: 7)
!4918 = !DILocation(line: 1170, column: 9, scope: !4917)
!4919 = !DILocation(line: 1170, column: 7, scope: !4912)
!4920 = !DILocation(line: 1171, column: 12, scope: !4917)
!4921 = !DILocation(line: 1171, column: 4, scope: !4917)
!4922 = !DILocation(line: 1173, column: 18, scope: !4912)
!4923 = !DILocation(line: 1173, column: 25, scope: !4912)
!4924 = !DILocation(line: 1173, column: 30, scope: !4912)
!4925 = !DILocation(line: 1173, column: 49, scope: !4912)
!4926 = !DILocation(line: 1173, column: 23, scope: !4912)
!4927 = !DILocation(line: 1173, column: 7, scope: !4912)
!4928 = !DILocation(line: 1173, column: 5, scope: !4912)
!4929 = !DILocation(line: 1174, column: 7, scope: !4930)
!4930 = distinct !DILexicalBlock(scope: !4912, file: !1, line: 1174, column: 7)
!4931 = !DILocation(line: 1174, column: 9, scope: !4930)
!4932 = !DILocation(line: 1174, column: 7, scope: !4912)
!4933 = !DILocation(line: 1175, column: 12, scope: !4930)
!4934 = !DILocation(line: 1175, column: 4, scope: !4930)
!4935 = !DILocation(line: 1177, column: 18, scope: !4912)
!4936 = !DILocation(line: 1177, column: 7, scope: !4912)
!4937 = !DILocation(line: 1177, column: 5, scope: !4912)
!4938 = !DILocation(line: 1178, column: 7, scope: !4939)
!4939 = distinct !DILexicalBlock(scope: !4912, file: !1, line: 1178, column: 7)
!4940 = !DILocation(line: 1178, column: 9, scope: !4939)
!4941 = !DILocation(line: 1178, column: 7, scope: !4912)
!4942 = !DILocation(line: 1179, column: 12, scope: !4939)
!4943 = !DILocation(line: 1179, column: 4, scope: !4939)
!4944 = !DILocation(line: 1180, column: 2, scope: !4912)
!4945 = !DILocation(line: 1181, column: 38, scope: !4946)
!4946 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1181, column: 7)
!4947 = distinct !DILexicalBlock(scope: !4904, file: !1, line: 1180, column: 9)
!4948 = !DILocation(line: 1181, column: 7, scope: !4946)
!4949 = !DILocation(line: 1181, column: 12, scope: !4946)
!4950 = !DILocation(line: 1181, column: 42, scope: !4946)
!4951 = !DILocation(line: 1181, column: 7, scope: !4947)
!4952 = !DILocation(line: 1182, column: 4, scope: !4946)
!4953 = !DILocation(line: 1185, column: 18, scope: !4947)
!4954 = !DILocation(line: 1185, column: 21, scope: !4947)
!4955 = !DILocation(line: 1185, column: 7, scope: !4947)
!4956 = !DILocation(line: 1185, column: 5, scope: !4947)
!4957 = !DILocation(line: 1186, column: 7, scope: !4958)
!4958 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1186, column: 7)
!4959 = !DILocation(line: 1186, column: 9, scope: !4958)
!4960 = !DILocation(line: 1186, column: 7, scope: !4947)
!4961 = !DILocation(line: 1187, column: 12, scope: !4958)
!4962 = !DILocation(line: 1187, column: 4, scope: !4958)
!4963 = !DILocation(line: 1189, column: 18, scope: !4947)
!4964 = !DILocation(line: 1189, column: 27, scope: !4947)
!4965 = !DILocation(line: 1189, column: 32, scope: !4947)
!4966 = !DILocation(line: 1189, column: 51, scope: !4947)
!4967 = !DILocation(line: 1189, column: 56, scope: !4947)
!4968 = !DILocation(line: 1189, column: 23, scope: !4947)
!4969 = !DILocation(line: 1190, column: 37, scope: !4947)
!4970 = !DILocation(line: 1190, column: 6, scope: !4947)
!4971 = !DILocation(line: 1190, column: 11, scope: !4947)
!4972 = !DILocation(line: 1190, column: 41, scope: !4947)
!4973 = !DILocation(line: 1190, column: 4, scope: !4947)
!4974 = !DILocation(line: 1189, column: 7, scope: !4947)
!4975 = !DILocation(line: 1189, column: 5, scope: !4947)
!4976 = !DILocation(line: 1191, column: 7, scope: !4977)
!4977 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1191, column: 7)
!4978 = !DILocation(line: 1191, column: 9, scope: !4977)
!4979 = !DILocation(line: 1191, column: 7, scope: !4947)
!4980 = !DILocation(line: 1192, column: 12, scope: !4977)
!4981 = !DILocation(line: 1192, column: 4, scope: !4977)
!4982 = !DILocation(line: 1195, column: 18, scope: !4947)
!4983 = !DILocation(line: 1195, column: 7, scope: !4947)
!4984 = !DILocation(line: 1195, column: 5, scope: !4947)
!4985 = !DILocation(line: 1196, column: 7, scope: !4986)
!4986 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1196, column: 7)
!4987 = !DILocation(line: 1196, column: 9, scope: !4986)
!4988 = !DILocation(line: 1196, column: 7, scope: !4947)
!4989 = !DILocation(line: 1197, column: 12, scope: !4986)
!4990 = !DILocation(line: 1197, column: 4, scope: !4986)
!4991 = !DILocation(line: 1199, column: 5, scope: !4947)
!4992 = !DILocation(line: 1200, column: 8, scope: !4947)
!4993 = !DILocation(line: 1201, column: 10, scope: !4947)
!4994 = !DILocation(line: 1201, column: 15, scope: !4947)
!4995 = !DILocation(line: 1201, column: 25, scope: !4947)
!4996 = !DILocation(line: 1201, column: 8, scope: !4947)
!4997 = !DILocation(line: 1202, column: 3, scope: !4947)
!4998 = !DILocation(line: 1202, column: 9, scope: !4999)
!4999 = !DILexicalBlockFile(scope: !5000, file: !1, discriminator: 1)
!5000 = distinct !DILexicalBlock(scope: !5001, file: !1, line: 1202, column: 3)
!5001 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1202, column: 3)
!5002 = !DILocation(line: 1202, column: 14, scope: !4999)
!5003 = !DILocation(line: 1202, column: 3, scope: !4999)
!5004 = !DILocation(line: 1203, column: 8, scope: !5005)
!5005 = distinct !DILexicalBlock(scope: !5006, file: !1, line: 1203, column: 8)
!5006 = distinct !DILexicalBlock(scope: !5000, file: !1, line: 1202, column: 42)
!5007 = !DILocation(line: 1203, column: 14, scope: !5005)
!5008 = !DILocation(line: 1203, column: 20, scope: !5005)
!5009 = !DILocation(line: 1203, column: 18, scope: !5005)
!5010 = !DILocation(line: 1203, column: 8, scope: !5006)
!5011 = !DILocation(line: 1204, column: 10, scope: !5005)
!5012 = !DILocation(line: 1204, column: 7, scope: !5005)
!5013 = !DILocation(line: 1204, column: 5, scope: !5005)
!5014 = !DILocation(line: 1205, column: 9, scope: !5006)
!5015 = !DILocation(line: 1206, column: 8, scope: !5016)
!5016 = distinct !DILexicalBlock(scope: !5006, file: !1, line: 1206, column: 8)
!5017 = !DILocation(line: 1206, column: 13, scope: !5016)
!5018 = !DILocation(line: 1206, column: 8, scope: !5006)
!5019 = !DILocation(line: 1207, column: 27, scope: !5020)
!5020 = distinct !DILexicalBlock(scope: !5016, file: !1, line: 1206, column: 19)
!5021 = !DILocation(line: 1207, column: 14, scope: !5020)
!5022 = !DILocation(line: 1207, column: 9, scope: !5020)
!5023 = !DILocation(line: 1207, column: 7, scope: !5020)
!5024 = !DILocation(line: 1208, column: 9, scope: !5025)
!5025 = distinct !DILexicalBlock(scope: !5020, file: !1, line: 1208, column: 9)
!5026 = !DILocation(line: 1208, column: 11, scope: !5025)
!5027 = !DILocation(line: 1208, column: 9, scope: !5020)
!5028 = !DILocation(line: 1209, column: 14, scope: !5025)
!5029 = !DILocation(line: 1209, column: 6, scope: !5025)
!5030 = !DILocation(line: 1210, column: 10, scope: !5020)
!5031 = !DILocation(line: 1211, column: 7, scope: !5020)
!5032 = !DILocation(line: 1212, column: 4, scope: !5020)
!5033 = !DILocation(line: 1213, column: 3, scope: !5006)
!5034 = !DILocation(line: 1202, column: 30, scope: !5035)
!5035 = !DILexicalBlockFile(scope: !5000, file: !1, discriminator: 2)
!5036 = !DILocation(line: 1202, column: 36, scope: !5035)
!5037 = !DILocation(line: 1202, column: 28, scope: !5035)
!5038 = !DILocation(line: 1202, column: 3, scope: !5035)
!5039 = !DILocation(line: 1214, column: 7, scope: !5040)
!5040 = distinct !DILexicalBlock(scope: !4947, file: !1, line: 1214, column: 7)
!5041 = !DILocation(line: 1214, column: 12, scope: !5040)
!5042 = !DILocation(line: 1214, column: 7, scope: !4947)
!5043 = !DILocation(line: 1215, column: 26, scope: !5044)
!5044 = distinct !DILexicalBlock(scope: !5040, file: !1, line: 1214, column: 21)
!5045 = !DILocation(line: 1215, column: 13, scope: !5044)
!5046 = !DILocation(line: 1215, column: 8, scope: !5044)
!5047 = !DILocation(line: 1215, column: 6, scope: !5044)
!5048 = !DILocation(line: 1216, column: 8, scope: !5049)
!5049 = distinct !DILexicalBlock(scope: !5044, file: !1, line: 1216, column: 8)
!5050 = !DILocation(line: 1216, column: 10, scope: !5049)
!5051 = !DILocation(line: 1216, column: 8, scope: !5044)
!5052 = !DILocation(line: 1217, column: 13, scope: !5049)
!5053 = !DILocation(line: 1217, column: 5, scope: !5049)
!5054 = !DILocation(line: 1218, column: 3, scope: !5044)
!5055 = !DILocation(line: 1222, column: 17, scope: !646)
!5056 = !DILocation(line: 1222, column: 6, scope: !646)
!5057 = !DILocation(line: 1222, column: 4, scope: !646)
!5058 = !DILocation(line: 1223, column: 6, scope: !5059)
!5059 = distinct !DILexicalBlock(scope: !646, file: !1, line: 1223, column: 6)
!5060 = !DILocation(line: 1223, column: 8, scope: !5059)
!5061 = !DILocation(line: 1223, column: 6, scope: !646)
!5062 = !DILocation(line: 1224, column: 11, scope: !5059)
!5063 = !DILocation(line: 1224, column: 3, scope: !5059)
!5064 = !DILocation(line: 1230, column: 9, scope: !646)
!5065 = !DILocation(line: 1230, column: 14, scope: !646)
!5066 = !DILocation(line: 1230, column: 24, scope: !646)
!5067 = !DILocation(line: 1230, column: 7, scope: !646)
!5068 = !DILocation(line: 1231, column: 2, scope: !646)
!5069 = !DILocation(line: 1231, column: 8, scope: !5070)
!5070 = !DILexicalBlockFile(scope: !5071, file: !1, discriminator: 1)
!5071 = distinct !DILexicalBlock(scope: !5072, file: !1, line: 1231, column: 2)
!5072 = distinct !DILexicalBlock(scope: !646, file: !1, line: 1231, column: 2)
!5073 = !DILocation(line: 1231, column: 13, scope: !5070)
!5074 = !DILocation(line: 1231, column: 2, scope: !5070)
!5075 = !DILocation(line: 1232, column: 8, scope: !5076)
!5076 = distinct !DILexicalBlock(scope: !5077, file: !1, line: 1232, column: 7)
!5077 = distinct !DILexicalBlock(scope: !5071, file: !1, line: 1231, column: 41)
!5078 = !DILocation(line: 1232, column: 14, scope: !5076)
!5079 = !DILocation(line: 1232, column: 20, scope: !5076)
!5080 = !DILocation(line: 1232, column: 18, scope: !5076)
!5081 = !DILocation(line: 1232, column: 25, scope: !5076)
!5082 = !DILocation(line: 1232, column: 7, scope: !5077)
!5083 = !DILocation(line: 1233, column: 4, scope: !5076)
!5084 = !DILocation(line: 1234, column: 19, scope: !5077)
!5085 = !DILocation(line: 1234, column: 55, scope: !5077)
!5086 = !DILocation(line: 1234, column: 43, scope: !5077)
!5087 = !DILocation(line: 1234, column: 49, scope: !5077)
!5088 = !DILocation(line: 1234, column: 59, scope: !5077)
!5089 = !DILocation(line: 1235, column: 16, scope: !5077)
!5090 = !DILocation(line: 1235, column: 4, scope: !5077)
!5091 = !DILocation(line: 1235, column: 10, scope: !5077)
!5092 = !DILocation(line: 1235, column: 20, scope: !5077)
!5093 = !DILocation(line: 1234, column: 29, scope: !5077)
!5094 = !DILocation(line: 1234, column: 3, scope: !5095)
!5095 = !DILexicalBlockFile(scope: !5077, file: !1, discriminator: 1)
!5096 = !DILocation(line: 1236, column: 25, scope: !5077)
!5097 = !DILocation(line: 1236, column: 28, scope: !5077)
!5098 = !DILocation(line: 1236, column: 12, scope: !5077)
!5099 = !DILocation(line: 1236, column: 7, scope: !5077)
!5100 = !DILocation(line: 1236, column: 5, scope: !5077)
!5101 = !DILocation(line: 1237, column: 7, scope: !5102)
!5102 = distinct !DILexicalBlock(scope: !5077, file: !1, line: 1237, column: 7)
!5103 = !DILocation(line: 1237, column: 9, scope: !5102)
!5104 = !DILocation(line: 1237, column: 7, scope: !5077)
!5105 = !DILocation(line: 1238, column: 12, scope: !5102)
!5106 = !DILocation(line: 1238, column: 4, scope: !5102)
!5107 = !DILocation(line: 1239, column: 2, scope: !5077)
!5108 = !DILocation(line: 1231, column: 29, scope: !5109)
!5109 = !DILexicalBlockFile(scope: !5071, file: !1, discriminator: 2)
!5110 = !DILocation(line: 1231, column: 35, scope: !5109)
!5111 = !DILocation(line: 1231, column: 27, scope: !5109)
!5112 = !DILocation(line: 1231, column: 2, scope: !5109)
!5113 = !DILocation(line: 1241, column: 2, scope: !646)
!5114 = !DILocation(line: 1242, column: 1, scope: !646)
!5115 = !DILocalVariable(name: "t", arg: 1, scope: !649, file: !1, line: 1144, type: !265)
!5116 = !DILocation(line: 1144, column: 22, scope: !649)
!5117 = !DILocalVariable(name: "ns", arg: 2, scope: !649, file: !1, line: 1144, type: !82)
!5118 = !DILocation(line: 1144, column: 30, scope: !649)
!5119 = !DILocalVariable(name: "fileTime", scope: !649, file: !1, line: 1146, type: !237)
!5120 = !DILocation(line: 1146, column: 11, scope: !649)
!5121 = !DILocation(line: 1148, column: 13, scope: !649)
!5122 = !DILocation(line: 1148, column: 11, scope: !649)
!5123 = !DILocation(line: 1149, column: 11, scope: !649)
!5124 = !DILocation(line: 1150, column: 14, scope: !649)
!5125 = !DILocation(line: 1150, column: 17, scope: !649)
!5126 = !DILocation(line: 1150, column: 11, scope: !649)
!5127 = !DILocation(line: 1151, column: 11, scope: !649)
!5128 = !DILocation(line: 1152, column: 10, scope: !649)
!5129 = !DILocation(line: 1152, column: 2, scope: !649)
!5130 = !DILocalVariable(name: "pp", arg: 1, scope: !658, file: !618, line: 159, type: !164)
!5131 = !DILocation(line: 159, column: 23, scope: !658)
!5132 = !DILocalVariable(name: "u", arg: 2, scope: !658, file: !618, line: 159, type: !237)
!5133 = !DILocation(line: 159, column: 36, scope: !658)
!5134 = !DILocalVariable(name: "p", scope: !658, file: !618, line: 161, type: !420)
!5135 = !DILocation(line: 161, column: 17, scope: !658)
!5136 = !DILocation(line: 161, column: 38, scope: !658)
!5137 = !DILocation(line: 163, column: 18, scope: !658)
!5138 = !DILocation(line: 163, column: 32, scope: !658)
!5139 = !DILocation(line: 163, column: 34, scope: !658)
!5140 = !DILocation(line: 163, column: 21, scope: !658)
!5141 = !DILocation(line: 163, column: 2, scope: !658)
!5142 = !DILocation(line: 164, column: 18, scope: !658)
!5143 = !DILocation(line: 164, column: 20, scope: !658)
!5144 = !DILocation(line: 164, column: 36, scope: !658)
!5145 = !DILocation(line: 164, column: 38, scope: !658)
!5146 = !DILocation(line: 164, column: 25, scope: !658)
!5147 = !DILocation(line: 164, column: 2, scope: !658)
!5148 = !DILocation(line: 165, column: 1, scope: !658)
!5149 = !DILocalVariable(name: "a", arg: 1, scope: !662, file: !1, line: 874, type: !44)
!5150 = !DILocation(line: 874, column: 43, scope: !662)
!5151 = !DILocalVariable(name: "coders", arg: 2, scope: !662, file: !1, line: 874, type: !645)
!5152 = !DILocation(line: 874, column: 60, scope: !662)
!5153 = !DILocalVariable(name: "zip", scope: !662, file: !1, line: 876, type: !232)
!5154 = !DILocation(line: 876, column: 16, scope: !662)
!5155 = !DILocation(line: 876, column: 38, scope: !662)
!5156 = !DILocation(line: 876, column: 41, scope: !662)
!5157 = !DILocation(line: 876, column: 22, scope: !662)
!5158 = !DILocalVariable(name: "file", scope: !662, file: !1, line: 877, type: !239)
!5159 = !DILocation(line: 877, column: 15, scope: !662)
!5160 = !DILocalVariable(name: "r", scope: !662, file: !1, line: 878, type: !63)
!5161 = !DILocation(line: 878, column: 6, scope: !662)
!5162 = !DILocation(line: 883, column: 17, scope: !662)
!5163 = !DILocation(line: 883, column: 6, scope: !662)
!5164 = !DILocation(line: 883, column: 4, scope: !662)
!5165 = !DILocation(line: 884, column: 6, scope: !5166)
!5166 = distinct !DILexicalBlock(scope: !662, file: !1, line: 884, column: 6)
!5167 = !DILocation(line: 884, column: 8, scope: !5166)
!5168 = !DILocation(line: 884, column: 6, scope: !662)
!5169 = !DILocation(line: 885, column: 11, scope: !5166)
!5170 = !DILocation(line: 885, column: 3, scope: !5166)
!5171 = !DILocation(line: 887, column: 6, scope: !5172)
!5172 = distinct !DILexicalBlock(scope: !662, file: !1, line: 887, column: 6)
!5173 = !DILocation(line: 887, column: 11, scope: !5172)
!5174 = !DILocation(line: 887, column: 39, scope: !5172)
!5175 = !DILocation(line: 887, column: 43, scope: !5172)
!5176 = !DILocation(line: 887, column: 46, scope: !5177)
!5177 = !DILexicalBlockFile(scope: !5172, file: !1, discriminator: 1)
!5178 = !DILocation(line: 887, column: 54, scope: !5177)
!5179 = !DILocation(line: 887, column: 60, scope: !5177)
!5180 = !DILocation(line: 887, column: 6, scope: !5177)
!5181 = !DILocation(line: 891, column: 18, scope: !5182)
!5182 = distinct !DILexicalBlock(scope: !5172, file: !1, line: 887, column: 73)
!5183 = !DILocation(line: 891, column: 7, scope: !5182)
!5184 = !DILocation(line: 891, column: 5, scope: !5182)
!5185 = !DILocation(line: 892, column: 7, scope: !5186)
!5186 = distinct !DILexicalBlock(scope: !5182, file: !1, line: 892, column: 7)
!5187 = !DILocation(line: 892, column: 9, scope: !5186)
!5188 = !DILocation(line: 892, column: 7, scope: !5182)
!5189 = !DILocation(line: 893, column: 12, scope: !5186)
!5190 = !DILocation(line: 893, column: 4, scope: !5186)
!5191 = !DILocation(line: 896, column: 18, scope: !5182)
!5192 = !DILocation(line: 896, column: 21, scope: !5182)
!5193 = !DILocation(line: 896, column: 26, scope: !5182)
!5194 = !DILocation(line: 896, column: 7, scope: !5182)
!5195 = !DILocation(line: 896, column: 5, scope: !5182)
!5196 = !DILocation(line: 897, column: 7, scope: !5197)
!5197 = distinct !DILexicalBlock(scope: !5182, file: !1, line: 897, column: 7)
!5198 = !DILocation(line: 897, column: 9, scope: !5197)
!5199 = !DILocation(line: 897, column: 7, scope: !5182)
!5200 = !DILocation(line: 898, column: 12, scope: !5197)
!5201 = !DILocation(line: 898, column: 4, scope: !5197)
!5202 = !DILocation(line: 903, column: 18, scope: !5182)
!5203 = !DILocation(line: 903, column: 7, scope: !5182)
!5204 = !DILocation(line: 903, column: 5, scope: !5182)
!5205 = !DILocation(line: 904, column: 7, scope: !5206)
!5206 = distinct !DILexicalBlock(scope: !5182, file: !1, line: 904, column: 7)
!5207 = !DILocation(line: 904, column: 9, scope: !5206)
!5208 = !DILocation(line: 904, column: 7, scope: !5182)
!5209 = !DILocation(line: 905, column: 12, scope: !5206)
!5210 = !DILocation(line: 905, column: 4, scope: !5206)
!5211 = !DILocation(line: 906, column: 10, scope: !5182)
!5212 = !DILocation(line: 906, column: 15, scope: !5182)
!5213 = !DILocation(line: 906, column: 25, scope: !5182)
!5214 = !DILocation(line: 906, column: 8, scope: !5182)
!5215 = !DILocation(line: 907, column: 3, scope: !5182)
!5216 = !DILocation(line: 907, column: 9, scope: !5217)
!5217 = !DILexicalBlockFile(scope: !5218, file: !1, discriminator: 1)
!5218 = distinct !DILexicalBlock(scope: !5219, file: !1, line: 907, column: 3)
!5219 = distinct !DILexicalBlock(scope: !5182, file: !1, line: 907, column: 3)
!5220 = !DILocation(line: 907, column: 14, scope: !5217)
!5221 = !DILocation(line: 907, column: 3, scope: !5217)
!5222 = !DILocation(line: 908, column: 8, scope: !5223)
!5223 = distinct !DILexicalBlock(scope: !5224, file: !1, line: 908, column: 8)
!5224 = distinct !DILexicalBlock(scope: !5218, file: !1, line: 907, column: 42)
!5225 = !DILocation(line: 908, column: 14, scope: !5223)
!5226 = !DILocation(line: 908, column: 19, scope: !5223)
!5227 = !DILocation(line: 908, column: 27, scope: !5223)
!5228 = !DILocation(line: 909, column: 8, scope: !5223)
!5229 = !DILocation(line: 909, column: 14, scope: !5223)
!5230 = !DILocation(line: 909, column: 20, scope: !5223)
!5231 = !DILocation(line: 909, column: 25, scope: !5223)
!5232 = !DILocation(line: 908, column: 8, scope: !5233)
!5233 = !DILexicalBlockFile(scope: !5224, file: !1, discriminator: 1)
!5234 = !DILocation(line: 910, column: 5, scope: !5223)
!5235 = !DILocation(line: 911, column: 19, scope: !5224)
!5236 = !DILocation(line: 911, column: 22, scope: !5224)
!5237 = !DILocation(line: 911, column: 28, scope: !5224)
!5238 = !DILocation(line: 911, column: 8, scope: !5224)
!5239 = !DILocation(line: 911, column: 6, scope: !5224)
!5240 = !DILocation(line: 912, column: 8, scope: !5241)
!5241 = distinct !DILexicalBlock(scope: !5224, file: !1, line: 912, column: 8)
!5242 = !DILocation(line: 912, column: 10, scope: !5241)
!5243 = !DILocation(line: 912, column: 8, scope: !5224)
!5244 = !DILocation(line: 913, column: 13, scope: !5241)
!5245 = !DILocation(line: 913, column: 5, scope: !5241)
!5246 = !DILocation(line: 914, column: 3, scope: !5224)
!5247 = !DILocation(line: 907, column: 30, scope: !5248)
!5248 = !DILexicalBlockFile(scope: !5218, file: !1, discriminator: 2)
!5249 = !DILocation(line: 907, column: 36, scope: !5248)
!5250 = !DILocation(line: 907, column: 28, scope: !5248)
!5251 = !DILocation(line: 907, column: 3, scope: !5248)
!5252 = !DILocation(line: 915, column: 2, scope: !5182)
!5253 = !DILocation(line: 920, column: 17, scope: !662)
!5254 = !DILocation(line: 920, column: 6, scope: !662)
!5255 = !DILocation(line: 920, column: 4, scope: !662)
!5256 = !DILocation(line: 921, column: 6, scope: !5257)
!5257 = distinct !DILexicalBlock(scope: !662, file: !1, line: 921, column: 6)
!5258 = !DILocation(line: 921, column: 8, scope: !5257)
!5259 = !DILocation(line: 921, column: 6, scope: !662)
!5260 = !DILocation(line: 922, column: 11, scope: !5257)
!5261 = !DILocation(line: 922, column: 3, scope: !5257)
!5262 = !DILocation(line: 926, column: 17, scope: !662)
!5263 = !DILocation(line: 926, column: 6, scope: !662)
!5264 = !DILocation(line: 926, column: 4, scope: !662)
!5265 = !DILocation(line: 927, column: 6, scope: !5266)
!5266 = distinct !DILexicalBlock(scope: !662, file: !1, line: 927, column: 6)
!5267 = !DILocation(line: 927, column: 8, scope: !5266)
!5268 = !DILocation(line: 927, column: 6, scope: !662)
!5269 = !DILocation(line: 928, column: 11, scope: !5266)
!5270 = !DILocation(line: 928, column: 3, scope: !5266)
!5271 = !DILocation(line: 929, column: 9, scope: !662)
!5272 = !DILocation(line: 929, column: 14, scope: !662)
!5273 = !DILocation(line: 929, column: 24, scope: !662)
!5274 = !DILocation(line: 929, column: 7, scope: !662)
!5275 = !DILocation(line: 930, column: 2, scope: !662)
!5276 = !DILocation(line: 930, column: 8, scope: !5277)
!5277 = !DILexicalBlockFile(scope: !5278, file: !1, discriminator: 1)
!5278 = distinct !DILexicalBlock(scope: !5279, file: !1, line: 930, column: 2)
!5279 = distinct !DILexicalBlock(scope: !662, file: !1, line: 930, column: 2)
!5280 = !DILocation(line: 930, column: 13, scope: !5277)
!5281 = !DILocation(line: 930, column: 2, scope: !5277)
!5282 = !DILocalVariable(name: "crc", scope: !5283, file: !1, line: 931, type: !4640)
!5283 = distinct !DILexicalBlock(scope: !5278, file: !1, line: 930, column: 41)
!5284 = !DILocation(line: 931, column: 11, scope: !5283)
!5285 = !DILocation(line: 932, column: 7, scope: !5286)
!5286 = distinct !DILexicalBlock(scope: !5283, file: !1, line: 932, column: 7)
!5287 = !DILocation(line: 932, column: 13, scope: !5286)
!5288 = !DILocation(line: 932, column: 18, scope: !5286)
!5289 = !DILocation(line: 932, column: 7, scope: !5283)
!5290 = !DILocation(line: 933, column: 4, scope: !5286)
!5291 = !DILocation(line: 934, column: 19, scope: !5283)
!5292 = !DILocation(line: 934, column: 24, scope: !5283)
!5293 = !DILocation(line: 934, column: 30, scope: !5283)
!5294 = !DILocation(line: 934, column: 3, scope: !5283)
!5295 = !DILocation(line: 935, column: 25, scope: !5283)
!5296 = !DILocation(line: 935, column: 28, scope: !5283)
!5297 = !DILocation(line: 935, column: 12, scope: !5283)
!5298 = !DILocation(line: 935, column: 7, scope: !5283)
!5299 = !DILocation(line: 935, column: 5, scope: !5283)
!5300 = !DILocation(line: 936, column: 7, scope: !5301)
!5301 = distinct !DILexicalBlock(scope: !5283, file: !1, line: 936, column: 7)
!5302 = !DILocation(line: 936, column: 9, scope: !5301)
!5303 = !DILocation(line: 936, column: 7, scope: !5283)
!5304 = !DILocation(line: 937, column: 12, scope: !5301)
!5305 = !DILocation(line: 937, column: 4, scope: !5301)
!5306 = !DILocation(line: 938, column: 2, scope: !5283)
!5307 = !DILocation(line: 930, column: 29, scope: !5308)
!5308 = !DILexicalBlockFile(scope: !5278, file: !1, discriminator: 2)
!5309 = !DILocation(line: 930, column: 35, scope: !5308)
!5310 = !DILocation(line: 930, column: 27, scope: !5308)
!5311 = !DILocation(line: 930, column: 2, scope: !5308)
!5312 = !DILocation(line: 941, column: 17, scope: !662)
!5313 = !DILocation(line: 941, column: 6, scope: !662)
!5314 = !DILocation(line: 941, column: 4, scope: !662)
!5315 = !DILocation(line: 942, column: 6, scope: !5316)
!5316 = distinct !DILexicalBlock(scope: !662, file: !1, line: 942, column: 6)
!5317 = !DILocation(line: 942, column: 8, scope: !5316)
!5318 = !DILocation(line: 942, column: 6, scope: !662)
!5319 = !DILocation(line: 943, column: 11, scope: !5316)
!5320 = !DILocation(line: 943, column: 3, scope: !5316)
!5321 = !DILocation(line: 944, column: 2, scope: !662)
!5322 = !DILocation(line: 945, column: 1, scope: !662)
!5323 = !DILocalVariable(name: "pp", arg: 1, scope: !661, file: !618, line: 148, type: !164)
!5324 = !DILocation(line: 148, column: 23, scope: !661)
!5325 = !DILocalVariable(name: "u", arg: 2, scope: !661, file: !618, line: 148, type: !275)
!5326 = !DILocation(line: 148, column: 36, scope: !661)
!5327 = !DILocalVariable(name: "p", scope: !661, file: !618, line: 150, type: !420)
!5328 = !DILocation(line: 150, column: 17, scope: !661)
!5329 = !DILocation(line: 150, column: 38, scope: !661)
!5330 = !DILocation(line: 152, column: 10, scope: !661)
!5331 = !DILocation(line: 152, column: 12, scope: !661)
!5332 = !DILocation(line: 152, column: 19, scope: !661)
!5333 = !DILocation(line: 152, column: 9, scope: !661)
!5334 = !DILocation(line: 152, column: 2, scope: !661)
!5335 = !DILocation(line: 152, column: 7, scope: !661)
!5336 = !DILocation(line: 153, column: 10, scope: !661)
!5337 = !DILocation(line: 153, column: 12, scope: !661)
!5338 = !DILocation(line: 153, column: 19, scope: !661)
!5339 = !DILocation(line: 153, column: 9, scope: !661)
!5340 = !DILocation(line: 153, column: 2, scope: !661)
!5341 = !DILocation(line: 153, column: 7, scope: !661)
!5342 = !DILocation(line: 154, column: 10, scope: !661)
!5343 = !DILocation(line: 154, column: 12, scope: !661)
!5344 = !DILocation(line: 154, column: 18, scope: !661)
!5345 = !DILocation(line: 154, column: 9, scope: !661)
!5346 = !DILocation(line: 154, column: 2, scope: !661)
!5347 = !DILocation(line: 154, column: 7, scope: !661)
!5348 = !DILocation(line: 155, column: 9, scope: !661)
!5349 = !DILocation(line: 155, column: 11, scope: !661)
!5350 = !DILocation(line: 155, column: 2, scope: !661)
!5351 = !DILocation(line: 155, column: 7, scope: !661)
!5352 = !DILocation(line: 156, column: 1, scope: !661)
!5353 = !DILocalVariable(name: "zip", arg: 1, scope: !671, file: !1, line: 1580, type: !232)
!5354 = !DILocation(line: 1580, column: 34, scope: !671)
!5355 = !DILocalVariable(name: "file", scope: !671, file: !1, line: 1582, type: !239)
!5356 = !DILocation(line: 1582, column: 15, scope: !671)
!5357 = !DILocalVariable(name: "file_next", scope: !671, file: !1, line: 1582, type: !239)
!5358 = !DILocation(line: 1582, column: 22, scope: !671)
!5359 = !DILocation(line: 1584, column: 9, scope: !671)
!5360 = !DILocation(line: 1584, column: 14, scope: !671)
!5361 = !DILocation(line: 1584, column: 24, scope: !671)
!5362 = !DILocation(line: 1584, column: 7, scope: !671)
!5363 = !DILocation(line: 1585, column: 2, scope: !671)
!5364 = !DILocation(line: 1585, column: 9, scope: !5365)
!5365 = !DILexicalBlockFile(scope: !671, file: !1, discriminator: 1)
!5366 = !DILocation(line: 1585, column: 14, scope: !5365)
!5367 = !DILocation(line: 1585, column: 2, scope: !5365)
!5368 = !DILocation(line: 1586, column: 15, scope: !5369)
!5369 = distinct !DILexicalBlock(scope: !671, file: !1, line: 1585, column: 23)
!5370 = !DILocation(line: 1586, column: 21, scope: !5369)
!5371 = !DILocation(line: 1586, column: 13, scope: !5369)
!5372 = !DILocation(line: 1587, column: 13, scope: !5369)
!5373 = !DILocation(line: 1587, column: 3, scope: !5369)
!5374 = !DILocation(line: 1588, column: 10, scope: !5369)
!5375 = !DILocation(line: 1588, column: 8, scope: !5369)
!5376 = !DILocation(line: 1585, column: 2, scope: !5377)
!5377 = !DILexicalBlockFile(scope: !671, file: !1, discriminator: 2)
!5378 = !DILocation(line: 1590, column: 1, scope: !671)
