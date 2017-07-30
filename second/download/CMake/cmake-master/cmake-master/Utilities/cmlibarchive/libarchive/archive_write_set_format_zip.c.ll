; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_zip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_cryptor = type { i32 (i8*, i64, i8*, i64, i32, i8*, i64)*, i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*)*, i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*)* }
%struct.archive_hmac = type { i32 (i32*, i8*, i64)*, void (i32*, i8*, i64)*, void (i32*, i8*, i64*)*, void (i32*)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.zip = type { i64, i64, i64, i64, i64, i64, %struct.archive_entry*, i32, i32, i32, i32, i32, i32, %struct.trad_enc_ctx, i8, i8, i32, i32, i8, i32, i8, i8*, i64, i64 (i64, i8*, i64)*, %struct.cd_segment*, %struct.cd_segment*, i64, i64, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32, i32, i32, i32, i32, %struct.z_stream_s, i64, i8* }
%struct.trad_enc_ctx = type { [3 x i32] }
%struct.cd_segment = type { %struct.cd_segment*, i64, i8*, i8* }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@.str = private unnamed_addr constant [42 x i8] c"archive_write_zip_set_compression_deflate\00", align 1
@.str.1 = private unnamed_addr constant [71 x i8] c"Can only use archive_write_zip_set_compression_deflate with zip format\00", align 1
@.str.2 = private unnamed_addr constant [69 x i8] c"Can only use archive_write_zip_set_compression_store with zip format\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"archive_write_set_format_zip\00", align 1
@.str.4 = private unnamed_addr constant [24 x i8] c"Can't allocate zip data\00", align 1
@.str.5 = private unnamed_addr constant [34 x i8] c"Can't allocate compression buffer\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c"zip\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"ZIP\00", align 1
@.str.8 = private unnamed_addr constant [12 x i8] c"compression\00", align 1
@.str.9 = private unnamed_addr constant [48 x i8] c"%s: compression option needs a compression name\00", align 1
@.str.10 = private unnamed_addr constant [8 x i8] c"deflate\00", align 1
@.str.11 = private unnamed_addr constant [6 x i8] c"store\00", align 1
@.str.12 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.13 = private unnamed_addr constant [11 x i8] c"encryption\00", align 1
@.str.14 = private unnamed_addr constant [12 x i8] c"traditional\00", align 1
@.str.15 = private unnamed_addr constant [9 x i8] c"zipcrypt\00", align 1
@.str.16 = private unnamed_addr constant [9 x i8] c"ZipCrypt\00", align 1
@.str.17 = private unnamed_addr constant [25 x i8] c"encryption not supported\00", align 1
@.str.18 = private unnamed_addr constant [7 x i8] c"aes128\00", align 1
@.str.19 = private unnamed_addr constant [7 x i8] c"aes256\00", align 1
@.str.20 = private unnamed_addr constant [28 x i8] c"%s: unknown encryption '%s'\00", align 1
@.str.21 = private unnamed_addr constant [13 x i8] c"experimental\00", align 1
@.str.22 = private unnamed_addr constant [10 x i8] c"fakecrc32\00", align 1
@.str.23 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.24 = private unnamed_addr constant [49 x i8] c"%s: hdrcharset option needs a character-set name\00", align 1
@.str.25 = private unnamed_addr constant [6 x i8] c"zip64\00", align 1
@__archive_cryptor = external constant %struct.archive_cryptor, align 8
@.str.26 = private unnamed_addr constant [2 x i8] c"p\00", align 1
@__archive_hmac = external constant %struct.archive_hmac, align 8
@.str.27 = private unnamed_addr constant [23 x i8] c"Filetype not supported\00", align 1
@.str.28 = private unnamed_addr constant [37 x i8] c"Files > 4GB require Zip64 extensions\00", align 1
@.str.29 = private unnamed_addr constant [40 x i8] c"Archives > 4GB require Zip64 extensions\00", align 1
@.str.30 = private unnamed_addr constant [31 x i8] c"Can't allocate zip header data\00", align 1
@.str.31 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.32 = private unnamed_addr constant [36 x i8] c"Can't translate Pathname '%s' to %s\00", align 1
@.str.33 = private unnamed_addr constant [35 x i8] c"Can't allocate memory  for Symlink\00", align 1
@.str.34 = private unnamed_addr constant [6 x i8] c"UTF-8\00", align 1
@.str.35 = private unnamed_addr constant [5 x i8] c"PK\03\04\00", align 1
@.str.36 = private unnamed_addr constant [5 x i8] c"PK\01\02\00", align 1
@.str.37 = private unnamed_addr constant [3 x i8] c"UT\00", align 1
@.str.38 = private unnamed_addr constant [6 x i8] c"ux\0B\00\01\00", align 1
@.str.39 = private unnamed_addr constant [9 x i8] c"\01\99\07\00\01\00AE\00", align 1
@.str.40 = private unnamed_addr constant [5 x i8] c"\01\00\10\00\00", align 1
@.str.41 = private unnamed_addr constant [5 x i8] c"xl\00\00\00", align 1
@.str.42 = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1
@.str.43 = private unnamed_addr constant [30 x i8] c"Can't init deflate compressor\00", align 1
@.str.44 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.45 = private unnamed_addr constant [23 x i8] c"Failed to encrypt file\00", align 1
@.str.46 = private unnamed_addr constant [29 x i8] c"Invalid ZIP compression type\00", align 1
@.str.47 = private unnamed_addr constant [28 x i8] c"Encryption needs passphrase\00", align 1
@.str.48 = private unnamed_addr constant [44 x i8] c"Can't generate random number for encryption\00", align 1
@.str.49 = private unnamed_addr constant [56 x i8] c"Decryption is unsupported due to lack of crypto library\00", align 1
@.str.50 = private unnamed_addr constant [31 x i8] c"Failed to initialize HMAC-SHA1\00", align 1
@.str.51 = private unnamed_addr constant [5 x i8] c"PK\07\08\00", align 1
@.str.52 = private unnamed_addr constant [5 x i8] c"\01\00\00\00\00", align 1
@.str.53 = private unnamed_addr constant [5 x i8] c"PK\06\06\00", align 1
@.str.54 = private unnamed_addr constant [5 x i8] c"PK\06\07\00", align 1
@.str.55 = private unnamed_addr constant [5 x i8] c"PK\05\06\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_zip_set_compression_deflate(%struct.archive* %_a) #0 !dbg !652 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  %zip = alloca %struct.zip*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !727, metadata !728), !dbg !729
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !730, metadata !728), !dbg !731
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !732
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !733
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !731
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !734, metadata !728), !dbg !735
  store i32 -25, i32* %ret, align 4, !dbg !735
  br label %do.body, !dbg !736

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !737, metadata !728), !dbg !739
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !740
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 7, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str, i32 0, i32 0)), !dbg !740
  store i32 %call, i32* %magic_test, align 4, !dbg !740
  %3 = load i32, i32* %magic_test, align 4, !dbg !740
  %cmp = icmp eq i32 %3, -30, !dbg !740
  br i1 %cmp, label %if.then, label %if.end, !dbg !740

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !742
  br label %return, !dbg !742

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !745

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !747
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !749
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !750
  %5 = load i32, i32* %archive_format, align 8, !dbg !750
  %cmp1 = icmp ne i32 %5, 327680, !dbg !751
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !752

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !753
  %archive3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !755
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 -1, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0)), !dbg !756
  store i32 -30, i32* %ret, align 4, !dbg !757
  br label %if.end4, !dbg !758

if.else:                                          ; preds = %do.end
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !759, metadata !728), !dbg !761
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !762
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 14, !dbg !763
  %8 = load i8*, i8** %format_data, align 8, !dbg !763
  %9 = bitcast i8* %8 to %struct.zip*, !dbg !762
  store %struct.zip* %9, %struct.zip** %zip, align 8, !dbg !761
  %10 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !764
  %requested_compression = getelementptr inbounds %struct.zip, %struct.zip* %10, i32 0, i32 31, !dbg !765
  store i32 8, i32* %requested_compression, align 8, !dbg !766
  store i32 0, i32* %ret, align 4, !dbg !767
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then2
  %11 = load i32, i32* %ret, align 4, !dbg !768
  store i32 %11, i32* %retval, align 4, !dbg !769
  br label %return, !dbg !769

return:                                           ; preds = %if.end4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !770
  ret i32 %12, !dbg !770
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_zip_set_compression_store(%struct.archive* %_a) #0 !dbg !654 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !771, metadata !728), !dbg !772
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !773, metadata !728), !dbg !774
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !775
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !776
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !774
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !777, metadata !728), !dbg !778
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !779
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 14, !dbg !780
  %3 = load i8*, i8** %format_data, align 8, !dbg !780
  %4 = bitcast i8* %3 to %struct.zip*, !dbg !779
  store %struct.zip* %4, %struct.zip** %zip, align 8, !dbg !778
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !781, metadata !728), !dbg !782
  store i32 -25, i32* %ret, align 4, !dbg !782
  br label %do.body, !dbg !783

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !784, metadata !728), !dbg !786
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !787
  %call = call i32 @__archive_check_magic(%struct.archive* %5, i32 -1329217314, i32 7, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str, i32 0, i32 0)), !dbg !787
  store i32 %call, i32* %magic_test, align 4, !dbg !787
  %6 = load i32, i32* %magic_test, align 4, !dbg !787
  %cmp = icmp eq i32 %6, -30, !dbg !787
  br i1 %cmp, label %if.then, label %if.end, !dbg !787

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !789
  br label %return, !dbg !789

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !792

do.end:                                           ; preds = %if.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !794
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !796
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !797
  %8 = load i32, i32* %archive_format, align 8, !dbg !797
  %cmp1 = icmp ne i32 %8, 327680, !dbg !798
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !799

if.then2:                                         ; preds = %do.end
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !800
  %archive3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !802
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 -1, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.2, i32 0, i32 0)), !dbg !803
  store i32 -30, i32* %ret, align 4, !dbg !804
  br label %if.end4, !dbg !805

if.else:                                          ; preds = %do.end
  %10 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !806
  %requested_compression = getelementptr inbounds %struct.zip, %struct.zip* %10, i32 0, i32 31, !dbg !808
  store i32 0, i32* %requested_compression, align 8, !dbg !809
  store i32 0, i32* %ret, align 4, !dbg !810
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then2
  %11 = load i32, i32* %ret, align 4, !dbg !811
  store i32 %11, i32* %retval, align 4, !dbg !812
  br label %return, !dbg !812

return:                                           ; preds = %if.end4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !813
  ret i32 %12, !dbg !813
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_zip(%struct.archive* %_a) #0 !dbg !655 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !814, metadata !728), !dbg !815
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !816, metadata !728), !dbg !817
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !818
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !819
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !817
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !820, metadata !728), !dbg !821
  br label %do.body, !dbg !822

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !823, metadata !728), !dbg !825
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !826
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0)), !dbg !826
  store i32 %call, i32* %magic_test, align 4, !dbg !826
  %3 = load i32, i32* %magic_test, align 4, !dbg !826
  %cmp = icmp eq i32 %3, -30, !dbg !826
  br i1 %cmp, label %if.then, label %if.end, !dbg !826

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !828
  br label %return, !dbg !828

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !831

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !833
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !835
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !835
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !836
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !837

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !838
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !839
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !839
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !840
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !841
  br label %if.end5, !dbg !841

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 352) #8, !dbg !842
  %9 = bitcast i8* %call6 to %struct.zip*, !dbg !843
  store %struct.zip* %9, %struct.zip** %zip, align 8, !dbg !844
  %10 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !845
  %cmp7 = icmp eq %struct.zip* %10, null, !dbg !847
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !848

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !849
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !851
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i32 0, i32 0)), !dbg !852
  store i32 -30, i32* %retval, align 4, !dbg !853
  br label %return, !dbg !853

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !854
  %requested_compression = getelementptr inbounds %struct.zip, %struct.zip* %12, i32 0, i32 31, !dbg !855
  store i32 -1, i32* %requested_compression, align 8, !dbg !856
  %13 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !857
  %deflate_compression_level = getelementptr inbounds %struct.zip, %struct.zip* %13, i32 0, i32 32, !dbg !858
  store i32 -1, i32* %deflate_compression_level, align 4, !dbg !859
  %14 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !860
  %crc32func = getelementptr inbounds %struct.zip, %struct.zip* %14, i32 0, i32 23, !dbg !861
  store i64 (i64, i8*, i64)* @real_crc32, i64 (i64, i8*, i64)** %crc32func, align 8, !dbg !862
  %15 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !863
  %len_buf = getelementptr inbounds %struct.zip, %struct.zip* %15, i32 0, i32 37, !dbg !864
  store i64 65536, i64* %len_buf, align 8, !dbg !865
  %16 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !866
  %len_buf10 = getelementptr inbounds %struct.zip, %struct.zip* %16, i32 0, i32 37, !dbg !867
  %17 = load i64, i64* %len_buf10, align 8, !dbg !867
  %call11 = call noalias i8* @malloc(i64 %17) #8, !dbg !868
  %18 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !869
  %buf = getelementptr inbounds %struct.zip, %struct.zip* %18, i32 0, i32 38, !dbg !870
  store i8* %call11, i8** %buf, align 8, !dbg !871
  %19 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !872
  %buf12 = getelementptr inbounds %struct.zip, %struct.zip* %19, i32 0, i32 38, !dbg !874
  %20 = load i8*, i8** %buf12, align 8, !dbg !874
  %cmp13 = icmp eq i8* %20, null, !dbg !875
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !876

if.then14:                                        ; preds = %if.end9
  %21 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !877
  %22 = bitcast %struct.zip* %21 to i8*, !dbg !877
  call void @free(i8* %22) #8, !dbg !879
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !880
  %archive15 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !881
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive15, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.5, i32 0, i32 0)), !dbg !882
  store i32 -30, i32* %retval, align 4, !dbg !883
  br label %return, !dbg !883

if.end16:                                         ; preds = %if.end9
  %24 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !884
  %25 = bitcast %struct.zip* %24 to i8*, !dbg !884
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !885
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 14, !dbg !886
  store i8* %25, i8** %format_data, align 8, !dbg !887
  %27 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !888
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 15, !dbg !889
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i8** %format_name, align 8, !dbg !890
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !891
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 17, !dbg !892
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_zip_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !893
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !894
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 19, !dbg !895
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_zip_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !896
  %30 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !897
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 20, !dbg !898
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_zip_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !899
  %31 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !900
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 18, !dbg !901
  store i32 (%struct.archive_write*)* @archive_write_zip_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !902
  %32 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !903
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %32, i32 0, i32 21, !dbg !904
  store i32 (%struct.archive_write*)* @archive_write_zip_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !905
  %33 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !906
  %format_free17 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %33, i32 0, i32 22, !dbg !907
  store i32 (%struct.archive_write*)* @archive_write_zip_free, i32 (%struct.archive_write*)** %format_free17, align 8, !dbg !908
  %34 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !909
  %archive18 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %34, i32 0, i32 0, !dbg !910
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive18, i32 0, i32 3, !dbg !911
  store i32 327680, i32* %archive_format, align 8, !dbg !912
  %35 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !913
  %archive19 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %35, i32 0, i32 0, !dbg !914
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive19, i32 0, i32 4, !dbg !915
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !916
  store i32 0, i32* %retval, align 4, !dbg !917
  br label %return, !dbg !917

return:                                           ; preds = %if.end16, %if.then14, %if.then8, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !918
  ret i32 %36, !dbg !918
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind uwtable
define internal i64 @real_crc32(i64 %crc, i8* %buff, i64 %len) #0 !dbg !656 {
entry:
  %crc.addr = alloca i64, align 8
  %buff.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  store i64 %crc, i64* %crc.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %crc.addr, metadata !919, metadata !728), !dbg !920
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !921, metadata !728), !dbg !922
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !923, metadata !728), !dbg !924
  %0 = load i64, i64* %crc.addr, align 8, !dbg !925
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !926
  %2 = load i64, i64* %len.addr, align 8, !dbg !927
  %conv = trunc i64 %2 to i32, !dbg !928
  %call = call i64 @cm_zlib_crc32(i64 %0, i8* %1, i32 %conv), !dbg !929
  ret i64 %call, !dbg !930
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_zip_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !657 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %zip = alloca %struct.zip*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !931, metadata !728), !dbg !932
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !933, metadata !728), !dbg !934
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !935, metadata !728), !dbg !936
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !937, metadata !728), !dbg !938
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !939
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !940
  %1 = load i8*, i8** %format_data, align 8, !dbg !940
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !939
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !938
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !941, metadata !728), !dbg !942
  store i32 -25, i32* %ret, align 4, !dbg !942
  %3 = load i8*, i8** %key.addr, align 8, !dbg !943
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.8, i32 0, i32 0)) #9, !dbg !945
  %cmp = icmp eq i32 %call, 0, !dbg !946
  br i1 %cmp, label %if.then, label %if.else17, !dbg !947

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !948
  %cmp1 = icmp eq i8* %4, null, !dbg !951
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !952

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !953
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !953
  %6 = load i8, i8* %arrayidx, align 1, !dbg !953
  %conv = sext i8 %6 to i32, !dbg !953
  %cmp2 = icmp eq i32 %conv, 0, !dbg !955
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !956

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !957
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !959
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !960
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 15, !dbg !961
  %9 = load i8*, i8** %format_name, align 8, !dbg !961
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.9, i32 0, i32 0), i8* %9), !dbg !962
  br label %if.end16, !dbg !963

if.else:                                          ; preds = %lor.lhs.false
  %10 = load i8*, i8** %val.addr, align 8, !dbg !964
  %call5 = call i32 @strcmp(i8* %10, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.10, i32 0, i32 0)) #9, !dbg !967
  %cmp6 = icmp eq i32 %call5, 0, !dbg !968
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !967

if.then8:                                         ; preds = %if.else
  %11 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !969
  %requested_compression = getelementptr inbounds %struct.zip, %struct.zip* %11, i32 0, i32 31, !dbg !971
  store i32 8, i32* %requested_compression, align 8, !dbg !972
  store i32 0, i32* %ret, align 4, !dbg !973
  br label %if.end15, !dbg !974

if.else9:                                         ; preds = %if.else
  %12 = load i8*, i8** %val.addr, align 8, !dbg !975
  %call10 = call i32 @strcmp(i8* %12, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.11, i32 0, i32 0)) #9, !dbg !978
  %cmp11 = icmp eq i32 %call10, 0, !dbg !979
  br i1 %cmp11, label %if.then13, label %if.end, !dbg !978

if.then13:                                        ; preds = %if.else9
  %13 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !980
  %requested_compression14 = getelementptr inbounds %struct.zip, %struct.zip* %13, i32 0, i32 31, !dbg !982
  store i32 0, i32* %requested_compression14, align 8, !dbg !983
  store i32 0, i32* %ret, align 4, !dbg !984
  br label %if.end, !dbg !985

if.end:                                           ; preds = %if.then13, %if.else9
  br label %if.end15

if.end15:                                         ; preds = %if.end, %if.then8
  br label %if.end16

if.end16:                                         ; preds = %if.end15, %if.then4
  %14 = load i32, i32* %ret, align 4, !dbg !986
  store i32 %14, i32* %retval, align 4, !dbg !987
  br label %return, !dbg !987

if.else17:                                        ; preds = %entry
  %15 = load i8*, i8** %key.addr, align 8, !dbg !988
  %call18 = call i32 @strcmp(i8* %15, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.12, i32 0, i32 0)) #9, !dbg !990
  %cmp19 = icmp eq i32 %call18, 0, !dbg !991
  br i1 %cmp19, label %if.then21, label %if.else50, !dbg !992

if.then21:                                        ; preds = %if.else17
  %16 = load i8*, i8** %val.addr, align 8, !dbg !993
  %cmp22 = icmp eq i8* %16, null, !dbg !996
  br i1 %cmp22, label %if.then38, label %lor.lhs.false24, !dbg !997

lor.lhs.false24:                                  ; preds = %if.then21
  %17 = load i8*, i8** %val.addr, align 8, !dbg !998
  %arrayidx25 = getelementptr inbounds i8, i8* %17, i64 0, !dbg !998
  %18 = load i8, i8* %arrayidx25, align 1, !dbg !998
  %conv26 = sext i8 %18 to i32, !dbg !998
  %cmp27 = icmp sge i32 %conv26, 48, !dbg !1000
  br i1 %cmp27, label %land.lhs.true, label %if.then38, !dbg !1001

land.lhs.true:                                    ; preds = %lor.lhs.false24
  %19 = load i8*, i8** %val.addr, align 8, !dbg !1002
  %arrayidx29 = getelementptr inbounds i8, i8* %19, i64 0, !dbg !1002
  %20 = load i8, i8* %arrayidx29, align 1, !dbg !1002
  %conv30 = sext i8 %20 to i32, !dbg !1002
  %cmp31 = icmp sle i32 %conv30, 57, !dbg !1004
  br i1 %cmp31, label %lor.lhs.false33, label %if.then38, !dbg !1005

lor.lhs.false33:                                  ; preds = %land.lhs.true
  %21 = load i8*, i8** %val.addr, align 8, !dbg !1006
  %arrayidx34 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1006
  %22 = load i8, i8* %arrayidx34, align 1, !dbg !1006
  %conv35 = sext i8 %22 to i32, !dbg !1006
  %cmp36 = icmp ne i32 %conv35, 0, !dbg !1008
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !1009

if.then38:                                        ; preds = %lor.lhs.false33, %land.lhs.true, %lor.lhs.false24, %if.then21
  store i32 -20, i32* %retval, align 4, !dbg !1010
  br label %return, !dbg !1010

if.end39:                                         ; preds = %lor.lhs.false33
  %23 = load i8*, i8** %val.addr, align 8, !dbg !1012
  %arrayidx40 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !1012
  %24 = load i8, i8* %arrayidx40, align 1, !dbg !1012
  %conv41 = sext i8 %24 to i32, !dbg !1012
  %cmp42 = icmp eq i32 %conv41, 48, !dbg !1014
  br i1 %cmp42, label %if.then44, label %if.else46, !dbg !1015

if.then44:                                        ; preds = %if.end39
  %25 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1016
  %requested_compression45 = getelementptr inbounds %struct.zip, %struct.zip* %25, i32 0, i32 31, !dbg !1018
  store i32 0, i32* %requested_compression45, align 8, !dbg !1019
  store i32 0, i32* %retval, align 4, !dbg !1020
  br label %return, !dbg !1020

if.else46:                                        ; preds = %if.end39
  %26 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1021
  %requested_compression47 = getelementptr inbounds %struct.zip, %struct.zip* %26, i32 0, i32 31, !dbg !1023
  store i32 8, i32* %requested_compression47, align 8, !dbg !1024
  %27 = load i8*, i8** %val.addr, align 8, !dbg !1025
  %arrayidx48 = getelementptr inbounds i8, i8* %27, i64 0, !dbg !1025
  %28 = load i8, i8* %arrayidx48, align 1, !dbg !1025
  %conv49 = sext i8 %28 to i32, !dbg !1025
  %sub = sub nsw i32 %conv49, 48, !dbg !1026
  %29 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1027
  %deflate_compression_level = getelementptr inbounds %struct.zip, %struct.zip* %29, i32 0, i32 32, !dbg !1028
  store i32 %sub, i32* %deflate_compression_level, align 4, !dbg !1029
  store i32 0, i32* %retval, align 4, !dbg !1030
  br label %return, !dbg !1030

if.else50:                                        ; preds = %if.else17
  %30 = load i8*, i8** %key.addr, align 8, !dbg !1031
  %call51 = call i32 @strcmp(i8* %30, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.13, i32 0, i32 0)) #9, !dbg !1033
  %cmp52 = icmp eq i32 %call51, 0, !dbg !1034
  br i1 %cmp52, label %if.then54, label %if.else113, !dbg !1035

if.then54:                                        ; preds = %if.else50
  %31 = load i8*, i8** %val.addr, align 8, !dbg !1036
  %cmp55 = icmp eq i8* %31, null, !dbg !1039
  br i1 %cmp55, label %if.then57, label %if.else58, !dbg !1040

if.then57:                                        ; preds = %if.then54
  %32 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1041
  %encryption_type = getelementptr inbounds %struct.zip, %struct.zip* %32, i32 0, i32 34, !dbg !1043
  store i32 0, i32* %encryption_type, align 4, !dbg !1044
  store i32 0, i32* %ret, align 4, !dbg !1045
  br label %if.end112, !dbg !1046

if.else58:                                        ; preds = %if.then54
  %33 = load i8*, i8** %val.addr, align 8, !dbg !1047
  %arrayidx59 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !1047
  %34 = load i8, i8* %arrayidx59, align 1, !dbg !1047
  %conv60 = sext i8 %34 to i32, !dbg !1047
  %cmp61 = icmp eq i32 %conv60, 49, !dbg !1050
  br i1 %cmp61, label %if.then75, label %lor.lhs.false63, !dbg !1051

lor.lhs.false63:                                  ; preds = %if.else58
  %35 = load i8*, i8** %val.addr, align 8, !dbg !1052
  %call64 = call i32 @strcmp(i8* %35, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.14, i32 0, i32 0)) #9, !dbg !1054
  %cmp65 = icmp eq i32 %call64, 0, !dbg !1055
  br i1 %cmp65, label %if.then75, label %lor.lhs.false67, !dbg !1056

lor.lhs.false67:                                  ; preds = %lor.lhs.false63
  %36 = load i8*, i8** %val.addr, align 8, !dbg !1057
  %call68 = call i32 @strcmp(i8* %36, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.15, i32 0, i32 0)) #9, !dbg !1058
  %cmp69 = icmp eq i32 %call68, 0, !dbg !1059
  br i1 %cmp69, label %if.then75, label %lor.lhs.false71, !dbg !1060

lor.lhs.false71:                                  ; preds = %lor.lhs.false67
  %37 = load i8*, i8** %val.addr, align 8, !dbg !1061
  %call72 = call i32 @strcmp(i8* %37, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.16, i32 0, i32 0)) #9, !dbg !1062
  %cmp73 = icmp eq i32 %call72, 0, !dbg !1063
  br i1 %cmp73, label %if.then75, label %if.else82, !dbg !1064

if.then75:                                        ; preds = %lor.lhs.false71, %lor.lhs.false67, %lor.lhs.false63, %if.else58
  %call76 = call i32 @is_traditional_pkware_encryption_supported(), !dbg !1066
  %tobool = icmp ne i32 %call76, 0, !dbg !1066
  br i1 %tobool, label %if.then77, label %if.else79, !dbg !1069

if.then77:                                        ; preds = %if.then75
  %38 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1070
  %encryption_type78 = getelementptr inbounds %struct.zip, %struct.zip* %38, i32 0, i32 34, !dbg !1072
  store i32 1, i32* %encryption_type78, align 4, !dbg !1073
  store i32 0, i32* %ret, align 4, !dbg !1074
  br label %if.end81, !dbg !1075

if.else79:                                        ; preds = %if.then75
  %39 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1076
  %archive80 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %39, i32 0, i32 0, !dbg !1078
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive80, i32 -1, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.17, i32 0, i32 0)), !dbg !1079
  br label %if.end81

if.end81:                                         ; preds = %if.else79, %if.then77
  br label %if.end111, !dbg !1080

if.else82:                                        ; preds = %lor.lhs.false71
  %40 = load i8*, i8** %val.addr, align 8, !dbg !1081
  %call83 = call i32 @strcmp(i8* %40, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.18, i32 0, i32 0)) #9, !dbg !1084
  %cmp84 = icmp eq i32 %call83, 0, !dbg !1085
  br i1 %cmp84, label %if.then86, label %if.else94, !dbg !1084

if.then86:                                        ; preds = %if.else82
  %call87 = call i32 @is_winzip_aes_encryption_supported(i32 2), !dbg !1086
  %tobool88 = icmp ne i32 %call87, 0, !dbg !1086
  br i1 %tobool88, label %if.then89, label %if.else91, !dbg !1089

if.then89:                                        ; preds = %if.then86
  %41 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1090
  %encryption_type90 = getelementptr inbounds %struct.zip, %struct.zip* %41, i32 0, i32 34, !dbg !1092
  store i32 2, i32* %encryption_type90, align 4, !dbg !1093
  store i32 0, i32* %ret, align 4, !dbg !1094
  br label %if.end93, !dbg !1095

if.else91:                                        ; preds = %if.then86
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1096
  %archive92 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %42, i32 0, i32 0, !dbg !1098
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive92, i32 -1, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.17, i32 0, i32 0)), !dbg !1099
  br label %if.end93

if.end93:                                         ; preds = %if.else91, %if.then89
  br label %if.end110, !dbg !1100

if.else94:                                        ; preds = %if.else82
  %43 = load i8*, i8** %val.addr, align 8, !dbg !1101
  %call95 = call i32 @strcmp(i8* %43, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.19, i32 0, i32 0)) #9, !dbg !1104
  %cmp96 = icmp eq i32 %call95, 0, !dbg !1105
  br i1 %cmp96, label %if.then98, label %if.else106, !dbg !1104

if.then98:                                        ; preds = %if.else94
  %call99 = call i32 @is_winzip_aes_encryption_supported(i32 3), !dbg !1106
  %tobool100 = icmp ne i32 %call99, 0, !dbg !1106
  br i1 %tobool100, label %if.then101, label %if.else103, !dbg !1109

if.then101:                                       ; preds = %if.then98
  %44 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1110
  %encryption_type102 = getelementptr inbounds %struct.zip, %struct.zip* %44, i32 0, i32 34, !dbg !1112
  store i32 3, i32* %encryption_type102, align 4, !dbg !1113
  store i32 0, i32* %ret, align 4, !dbg !1114
  br label %if.end105, !dbg !1115

if.else103:                                       ; preds = %if.then98
  %45 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1116
  %archive104 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %45, i32 0, i32 0, !dbg !1118
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive104, i32 -1, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.17, i32 0, i32 0)), !dbg !1119
  br label %if.end105

if.end105:                                        ; preds = %if.else103, %if.then101
  br label %if.end109, !dbg !1120

if.else106:                                       ; preds = %if.else94
  %46 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1121
  %archive107 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %46, i32 0, i32 0, !dbg !1123
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1124
  %format_name108 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %47, i32 0, i32 15, !dbg !1125
  %48 = load i8*, i8** %format_name108, align 8, !dbg !1125
  %49 = load i8*, i8** %val.addr, align 8, !dbg !1126
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive107, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.20, i32 0, i32 0), i8* %48, i8* %49), !dbg !1127
  br label %if.end109

if.end109:                                        ; preds = %if.else106, %if.end105
  br label %if.end110

if.end110:                                        ; preds = %if.end109, %if.end93
  br label %if.end111

if.end111:                                        ; preds = %if.end110, %if.end81
  br label %if.end112

if.end112:                                        ; preds = %if.end111, %if.then57
  %50 = load i32, i32* %ret, align 4, !dbg !1128
  store i32 %50, i32* %retval, align 4, !dbg !1129
  br label %return, !dbg !1129

if.else113:                                       ; preds = %if.else50
  %51 = load i8*, i8** %key.addr, align 8, !dbg !1130
  %call114 = call i32 @strcmp(i8* %51, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.21, i32 0, i32 0)) #9, !dbg !1132
  %cmp115 = icmp eq i32 %call114, 0, !dbg !1133
  br i1 %cmp115, label %if.then117, label %if.else129, !dbg !1134

if.then117:                                       ; preds = %if.else113
  %52 = load i8*, i8** %val.addr, align 8, !dbg !1135
  %cmp118 = icmp eq i8* %52, null, !dbg !1138
  br i1 %cmp118, label %if.then125, label %lor.lhs.false120, !dbg !1139

lor.lhs.false120:                                 ; preds = %if.then117
  %53 = load i8*, i8** %val.addr, align 8, !dbg !1140
  %arrayidx121 = getelementptr inbounds i8, i8* %53, i64 0, !dbg !1140
  %54 = load i8, i8* %arrayidx121, align 1, !dbg !1140
  %conv122 = sext i8 %54 to i32, !dbg !1140
  %cmp123 = icmp eq i32 %conv122, 0, !dbg !1142
  br i1 %cmp123, label %if.then125, label %if.else126, !dbg !1143

if.then125:                                       ; preds = %lor.lhs.false120, %if.then117
  %55 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1144
  %flags = getelementptr inbounds %struct.zip, %struct.zip* %55, i32 0, i32 35, !dbg !1146
  %56 = load i32, i32* %flags, align 8, !dbg !1147
  %and = and i32 %56, -5, !dbg !1147
  store i32 %and, i32* %flags, align 8, !dbg !1147
  br label %if.end128, !dbg !1148

if.else126:                                       ; preds = %lor.lhs.false120
  %57 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1149
  %flags127 = getelementptr inbounds %struct.zip, %struct.zip* %57, i32 0, i32 35, !dbg !1151
  %58 = load i32, i32* %flags127, align 8, !dbg !1152
  %or = or i32 %58, 4, !dbg !1152
  store i32 %or, i32* %flags127, align 8, !dbg !1152
  br label %if.end128

if.end128:                                        ; preds = %if.else126, %if.then125
  store i32 0, i32* %retval, align 4, !dbg !1153
  br label %return, !dbg !1153

if.else129:                                       ; preds = %if.else113
  %59 = load i8*, i8** %key.addr, align 8, !dbg !1154
  %call130 = call i32 @strcmp(i8* %59, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.22, i32 0, i32 0)) #9, !dbg !1156
  %cmp131 = icmp eq i32 %call130, 0, !dbg !1157
  br i1 %cmp131, label %if.then133, label %if.else145, !dbg !1158

if.then133:                                       ; preds = %if.else129
  %60 = load i8*, i8** %val.addr, align 8, !dbg !1159
  %cmp134 = icmp eq i8* %60, null, !dbg !1162
  br i1 %cmp134, label %if.then141, label %lor.lhs.false136, !dbg !1163

lor.lhs.false136:                                 ; preds = %if.then133
  %61 = load i8*, i8** %val.addr, align 8, !dbg !1164
  %arrayidx137 = getelementptr inbounds i8, i8* %61, i64 0, !dbg !1164
  %62 = load i8, i8* %arrayidx137, align 1, !dbg !1164
  %conv138 = sext i8 %62 to i32, !dbg !1164
  %cmp139 = icmp eq i32 %conv138, 0, !dbg !1166
  br i1 %cmp139, label %if.then141, label %if.else142, !dbg !1167

if.then141:                                       ; preds = %lor.lhs.false136, %if.then133
  %63 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1168
  %crc32func = getelementptr inbounds %struct.zip, %struct.zip* %63, i32 0, i32 23, !dbg !1170
  store i64 (i64, i8*, i64)* @real_crc32, i64 (i64, i8*, i64)** %crc32func, align 8, !dbg !1171
  br label %if.end144, !dbg !1172

if.else142:                                       ; preds = %lor.lhs.false136
  %64 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1173
  %crc32func143 = getelementptr inbounds %struct.zip, %struct.zip* %64, i32 0, i32 23, !dbg !1175
  store i64 (i64, i8*, i64)* @fake_crc32, i64 (i64, i8*, i64)** %crc32func143, align 8, !dbg !1176
  br label %if.end144

if.end144:                                        ; preds = %if.else142, %if.then141
  store i32 0, i32* %retval, align 4, !dbg !1177
  br label %return, !dbg !1177

if.else145:                                       ; preds = %if.else129
  %65 = load i8*, i8** %key.addr, align 8, !dbg !1178
  %call146 = call i32 @strcmp(i8* %65, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i32 0, i32 0)) #9, !dbg !1180
  %cmp147 = icmp eq i32 %call146, 0, !dbg !1181
  br i1 %cmp147, label %if.then149, label %if.else170, !dbg !1182

if.then149:                                       ; preds = %if.else145
  %66 = load i8*, i8** %val.addr, align 8, !dbg !1183
  %cmp150 = icmp eq i8* %66, null, !dbg !1186
  br i1 %cmp150, label %if.then157, label %lor.lhs.false152, !dbg !1187

lor.lhs.false152:                                 ; preds = %if.then149
  %67 = load i8*, i8** %val.addr, align 8, !dbg !1188
  %arrayidx153 = getelementptr inbounds i8, i8* %67, i64 0, !dbg !1188
  %68 = load i8, i8* %arrayidx153, align 1, !dbg !1188
  %conv154 = sext i8 %68 to i32, !dbg !1188
  %cmp155 = icmp eq i32 %conv154, 0, !dbg !1190
  br i1 %cmp155, label %if.then157, label %if.else160, !dbg !1191

if.then157:                                       ; preds = %lor.lhs.false152, %if.then149
  %69 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1192
  %archive158 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %69, i32 0, i32 0, !dbg !1194
  %70 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1195
  %format_name159 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %70, i32 0, i32 15, !dbg !1196
  %71 = load i8*, i8** %format_name159, align 8, !dbg !1196
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive158, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.24, i32 0, i32 0), i8* %71), !dbg !1197
  br label %if.end169, !dbg !1198

if.else160:                                       ; preds = %lor.lhs.false152
  %72 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1199
  %archive161 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %72, i32 0, i32 0, !dbg !1201
  %73 = load i8*, i8** %val.addr, align 8, !dbg !1202
  %call162 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive161, i8* %73, i32 0), !dbg !1203
  %74 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1204
  %opt_sconv = getelementptr inbounds %struct.zip, %struct.zip* %74, i32 0, i32 29, !dbg !1205
  store %struct.archive_string_conv* %call162, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !1206
  %75 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1207
  %opt_sconv163 = getelementptr inbounds %struct.zip, %struct.zip* %75, i32 0, i32 29, !dbg !1209
  %76 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv163, align 8, !dbg !1209
  %cmp164 = icmp ne %struct.archive_string_conv* %76, null, !dbg !1210
  br i1 %cmp164, label %if.then166, label %if.else167, !dbg !1211

if.then166:                                       ; preds = %if.else160
  store i32 0, i32* %ret, align 4, !dbg !1212
  br label %if.end168, !dbg !1213

if.else167:                                       ; preds = %if.else160
  store i32 -30, i32* %ret, align 4, !dbg !1214
  br label %if.end168

if.end168:                                        ; preds = %if.else167, %if.then166
  br label %if.end169

if.end169:                                        ; preds = %if.end168, %if.then157
  %77 = load i32, i32* %ret, align 4, !dbg !1215
  store i32 %77, i32* %retval, align 4, !dbg !1216
  br label %return, !dbg !1216

if.else170:                                       ; preds = %if.else145
  %78 = load i8*, i8** %key.addr, align 8, !dbg !1217
  %call171 = call i32 @strcmp(i8* %78, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.25, i32 0, i32 0)) #9, !dbg !1219
  %cmp172 = icmp eq i32 %call171, 0, !dbg !1220
  br i1 %cmp172, label %if.then174, label %if.end192, !dbg !1221

if.then174:                                       ; preds = %if.else170
  %79 = load i8*, i8** %val.addr, align 8, !dbg !1222
  %cmp175 = icmp ne i8* %79, null, !dbg !1225
  br i1 %cmp175, label %land.lhs.true177, label %if.else186, !dbg !1226

land.lhs.true177:                                 ; preds = %if.then174
  %80 = load i8*, i8** %val.addr, align 8, !dbg !1227
  %81 = load i8, i8* %80, align 1, !dbg !1229
  %conv178 = sext i8 %81 to i32, !dbg !1229
  %cmp179 = icmp ne i32 %conv178, 0, !dbg !1230
  br i1 %cmp179, label %if.then181, label %if.else186, !dbg !1231

if.then181:                                       ; preds = %land.lhs.true177
  %82 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1232
  %flags182 = getelementptr inbounds %struct.zip, %struct.zip* %82, i32 0, i32 35, !dbg !1234
  %83 = load i32, i32* %flags182, align 8, !dbg !1235
  %or183 = or i32 %83, 2, !dbg !1235
  store i32 %or183, i32* %flags182, align 8, !dbg !1235
  %84 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1236
  %flags184 = getelementptr inbounds %struct.zip, %struct.zip* %84, i32 0, i32 35, !dbg !1237
  %85 = load i32, i32* %flags184, align 8, !dbg !1238
  %and185 = and i32 %85, -2, !dbg !1238
  store i32 %and185, i32* %flags184, align 8, !dbg !1238
  br label %if.end191, !dbg !1239

if.else186:                                       ; preds = %land.lhs.true177, %if.then174
  %86 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1240
  %flags187 = getelementptr inbounds %struct.zip, %struct.zip* %86, i32 0, i32 35, !dbg !1242
  %87 = load i32, i32* %flags187, align 8, !dbg !1243
  %and188 = and i32 %87, -3, !dbg !1243
  store i32 %and188, i32* %flags187, align 8, !dbg !1243
  %88 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1244
  %flags189 = getelementptr inbounds %struct.zip, %struct.zip* %88, i32 0, i32 35, !dbg !1245
  %89 = load i32, i32* %flags189, align 8, !dbg !1246
  %or190 = or i32 %89, 1, !dbg !1246
  store i32 %or190, i32* %flags189, align 8, !dbg !1246
  br label %if.end191

if.end191:                                        ; preds = %if.else186, %if.then181
  store i32 0, i32* %retval, align 4, !dbg !1247
  br label %return, !dbg !1247

if.end192:                                        ; preds = %if.else170
  br label %if.end193

if.end193:                                        ; preds = %if.end192
  br label %if.end194

if.end194:                                        ; preds = %if.end193
  br label %if.end195

if.end195:                                        ; preds = %if.end194
  br label %if.end196

if.end196:                                        ; preds = %if.end195
  br label %if.end197

if.end197:                                        ; preds = %if.end196
  br label %if.end198

if.end198:                                        ; preds = %if.end197
  store i32 -20, i32* %retval, align 4, !dbg !1248
  br label %return, !dbg !1248

return:                                           ; preds = %if.end198, %if.end191, %if.end169, %if.end144, %if.end128, %if.end112, %if.else46, %if.then44, %if.then38, %if.end16
  %90 = load i32, i32* %retval, align 4, !dbg !1249
  ret i32 %90, !dbg !1249
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_zip_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !665 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %local_header = alloca [32 x i8], align 16
  %local_extra = alloca [144 x i8], align 16
  %zip = alloca %struct.zip*, align 8
  %e = alloca i8*, align 8
  %cd_extra = alloca i8*, align 8
  %filename_length = alloca i64, align 8
  %slink = alloca i8*, align 8
  %slink_size = alloca i64, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %ret = alloca i32, align 4
  %ret2 = alloca i32, align 4
  %type = alloca i32, align 4
  %version_needed = alloca i32, align 4
  %p = alloca i8*, align 8
  %len = alloca i64, align 8
  %size = alloca i64, align 8
  %additional_size = alloca i64, align 8
  %zip64_start = alloca i8*, align 8
  %external_info = alloca i8*, align 8
  %included = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1250, metadata !728), !dbg !1251
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1252, metadata !728), !dbg !1253
  call void @llvm.dbg.declare(metadata [32 x i8]* %local_header, metadata !1254, metadata !728), !dbg !1258
  call void @llvm.dbg.declare(metadata [144 x i8]* %local_extra, metadata !1259, metadata !728), !dbg !1263
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !1264, metadata !728), !dbg !1265
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1266
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !1267
  %1 = load i8*, i8** %format_data, align 8, !dbg !1267
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !1266
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !1265
  call void @llvm.dbg.declare(metadata i8** %e, metadata !1268, metadata !728), !dbg !1269
  call void @llvm.dbg.declare(metadata i8** %cd_extra, metadata !1270, metadata !728), !dbg !1271
  call void @llvm.dbg.declare(metadata i64* %filename_length, metadata !1272, metadata !728), !dbg !1273
  call void @llvm.dbg.declare(metadata i8** %slink, metadata !1274, metadata !728), !dbg !1275
  store i8* null, i8** %slink, align 8, !dbg !1275
  call void @llvm.dbg.declare(metadata i64* %slink_size, metadata !1276, metadata !728), !dbg !1277
  store i64 0, i64* %slink_size, align 8, !dbg !1277
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !1278, metadata !728), !dbg !1279
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1280
  %4 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1281
  %call = call %struct.archive_string_conv* @get_sconv(%struct.archive_write* %3, %struct.zip* %4), !dbg !1282
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv, align 8, !dbg !1279
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1283, metadata !728), !dbg !1284
  call void @llvm.dbg.declare(metadata i32* %ret2, metadata !1285, metadata !728), !dbg !1286
  store i32 0, i32* %ret2, align 4, !dbg !1286
  call void @llvm.dbg.declare(metadata i32* %type, metadata !1287, metadata !728), !dbg !1288
  call void @llvm.dbg.declare(metadata i32* %version_needed, metadata !1289, metadata !728), !dbg !1290
  store i32 10, i32* %version_needed, align 4, !dbg !1290
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1291
  %call2 = call i32 @archive_entry_filetype(%struct.archive_entry* %5), !dbg !1292
  store i32 %call2, i32* %type, align 4, !dbg !1293
  %6 = load i32, i32* %type, align 4, !dbg !1294
  %cmp = icmp ne i32 %6, 32768, !dbg !1296
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !1297

land.lhs.true:                                    ; preds = %entry
  %7 = load i32, i32* %type, align 4, !dbg !1298
  %cmp3 = icmp ne i32 %7, 16384, !dbg !1300
  br i1 %cmp3, label %land.lhs.true4, label %if.end, !dbg !1301

land.lhs.true4:                                   ; preds = %land.lhs.true
  %8 = load i32, i32* %type, align 4, !dbg !1302
  %cmp5 = icmp ne i32 %8, 40960, !dbg !1304
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1305

if.then:                                          ; preds = %land.lhs.true4
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1306
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !1308
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.27, i32 0, i32 0)), !dbg !1309
  store i32 -25, i32* %retval, align 4, !dbg !1310
  br label %return, !dbg !1310

if.end:                                           ; preds = %land.lhs.true4, %land.lhs.true, %entry
  %10 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1311
  %flags = getelementptr inbounds %struct.zip, %struct.zip* %10, i32 0, i32 35, !dbg !1313
  %11 = load i32, i32* %flags, align 8, !dbg !1313
  %and = and i32 %11, 1, !dbg !1314
  %tobool = icmp ne i32 %and, 0, !dbg !1314
  br i1 %tobool, label %if.then6, label %if.end19, !dbg !1315

if.then6:                                         ; preds = %if.end
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1316
  %call7 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %12), !dbg !1319
  %tobool8 = icmp ne i32 %call7, 0, !dbg !1319
  br i1 %tobool8, label %land.lhs.true9, label %if.end14, !dbg !1320

land.lhs.true9:                                   ; preds = %if.then6
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1321
  %call10 = call i64 @archive_entry_size(%struct.archive_entry* %13), !dbg !1323
  %cmp11 = icmp sgt i64 %call10, 4294967295, !dbg !1324
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !1325

if.then12:                                        ; preds = %land.lhs.true9
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1327
  %archive13 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 0, !dbg !1329
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive13, i32 -1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.28, i32 0, i32 0)), !dbg !1330
  store i32 -25, i32* %retval, align 4, !dbg !1331
  br label %return, !dbg !1331

if.end14:                                         ; preds = %land.lhs.true9, %if.then6
  %15 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1332
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %15, i32 0, i32 28, !dbg !1334
  %16 = load i64, i64* %written_bytes, align 8, !dbg !1334
  %cmp15 = icmp sgt i64 %16, 4294967295, !dbg !1335
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !1336

if.then16:                                        ; preds = %if.end14
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1337
  %archive17 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 0, !dbg !1339
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 -1, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.29, i32 0, i32 0)), !dbg !1340
  store i32 -25, i32* %retval, align 4, !dbg !1341
  br label %return, !dbg !1341

if.end18:                                         ; preds = %if.end14
  br label %if.end19, !dbg !1342

if.end19:                                         ; preds = %if.end18, %if.end
  %18 = load i32, i32* %type, align 4, !dbg !1343
  %cmp20 = icmp ne i32 %18, 32768, !dbg !1345
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !1346

if.then21:                                        ; preds = %if.end19
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1347
  call void @archive_entry_set_size(%struct.archive_entry* %19, i64 0), !dbg !1348
  br label %if.end22, !dbg !1348

if.end22:                                         ; preds = %if.then21, %if.end19
  %20 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1349
  %written_bytes23 = getelementptr inbounds %struct.zip, %struct.zip* %20, i32 0, i32 28, !dbg !1350
  %21 = load i64, i64* %written_bytes23, align 8, !dbg !1350
  %22 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1351
  %entry_offset = getelementptr inbounds %struct.zip, %struct.zip* %22, i32 0, i32 0, !dbg !1352
  store i64 %21, i64* %entry_offset, align 8, !dbg !1353
  %23 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1354
  %entry_uncompressed_limit = getelementptr inbounds %struct.zip, %struct.zip* %23, i32 0, i32 5, !dbg !1355
  store i64 9223372036854775807, i64* %entry_uncompressed_limit, align 8, !dbg !1356
  %24 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1357
  %entry_compressed_size = getelementptr inbounds %struct.zip, %struct.zip* %24, i32 0, i32 1, !dbg !1358
  store i64 0, i64* %entry_compressed_size, align 8, !dbg !1359
  %25 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1360
  %entry_uncompressed_size = getelementptr inbounds %struct.zip, %struct.zip* %25, i32 0, i32 2, !dbg !1361
  store i64 0, i64* %entry_uncompressed_size, align 8, !dbg !1362
  %26 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1363
  %entry_compressed_written = getelementptr inbounds %struct.zip, %struct.zip* %26, i32 0, i32 3, !dbg !1364
  store i64 0, i64* %entry_compressed_written, align 8, !dbg !1365
  %27 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1366
  %entry_uncompressed_written = getelementptr inbounds %struct.zip, %struct.zip* %27, i32 0, i32 4, !dbg !1367
  store i64 0, i64* %entry_uncompressed_written, align 8, !dbg !1368
  %28 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1369
  %entry_flags = getelementptr inbounds %struct.zip, %struct.zip* %28, i32 0, i32 10, !dbg !1370
  store i32 0, i32* %entry_flags, align 4, !dbg !1371
  %29 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1372
  %entry_uses_zip64 = getelementptr inbounds %struct.zip, %struct.zip* %29, i32 0, i32 11, !dbg !1373
  store i32 0, i32* %entry_uses_zip64, align 8, !dbg !1374
  %30 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1375
  %crc32func = getelementptr inbounds %struct.zip, %struct.zip* %30, i32 0, i32 23, !dbg !1376
  %31 = load i64 (i64, i8*, i64)*, i64 (i64, i8*, i64)** %crc32func, align 8, !dbg !1376
  %call24 = call i64 %31(i64 0, i8* null, i64 0), !dbg !1375
  %conv = trunc i64 %call24 to i32, !dbg !1375
  %32 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1377
  %entry_crc32 = getelementptr inbounds %struct.zip, %struct.zip* %32, i32 0, i32 7, !dbg !1378
  store i32 %conv, i32* %entry_crc32, align 8, !dbg !1379
  %33 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1380
  %entry_encryption = getelementptr inbounds %struct.zip, %struct.zip* %33, i32 0, i32 9, !dbg !1381
  store i32 0, i32* %entry_encryption, align 8, !dbg !1382
  %34 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1383
  %entry25 = getelementptr inbounds %struct.zip, %struct.zip* %34, i32 0, i32 6, !dbg !1385
  %35 = load %struct.archive_entry*, %struct.archive_entry** %entry25, align 8, !dbg !1385
  %cmp26 = icmp ne %struct.archive_entry* %35, null, !dbg !1386
  br i1 %cmp26, label %if.then28, label %if.end31, !dbg !1387

if.then28:                                        ; preds = %if.end22
  %36 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1388
  %entry29 = getelementptr inbounds %struct.zip, %struct.zip* %36, i32 0, i32 6, !dbg !1390
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry29, align 8, !dbg !1390
  call void @archive_entry_free(%struct.archive_entry* %37), !dbg !1391
  %38 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1392
  %entry30 = getelementptr inbounds %struct.zip, %struct.zip* %38, i32 0, i32 6, !dbg !1393
  store %struct.archive_entry* null, %struct.archive_entry** %entry30, align 8, !dbg !1394
  br label %if.end31, !dbg !1395

if.end31:                                         ; preds = %if.then28, %if.end22
  %39 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1396
  %cctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %39, i32 0, i32 18, !dbg !1398
  %40 = load i8, i8* %cctx_valid, align 8, !dbg !1398
  %tobool32 = icmp ne i8 %40, 0, !dbg !1396
  br i1 %tobool32, label %if.then33, label %if.end35, !dbg !1399

if.then33:                                        ; preds = %if.end31
  %41 = load i32 (i32*)*, i32 (i32*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 6), align 8, !dbg !1400
  %42 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1400
  %cctx = getelementptr inbounds %struct.zip, %struct.zip* %42, i32 0, i32 17, !dbg !1400
  %call34 = call i32 %41(i32* %cctx), !dbg !1400
  br label %if.end35, !dbg !1400

if.end35:                                         ; preds = %if.then33, %if.end31
  %43 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1401
  %hctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %43, i32 0, i32 20, !dbg !1403
  %44 = load i8, i8* %hctx_valid, align 8, !dbg !1403
  %tobool36 = icmp ne i8 %44, 0, !dbg !1401
  br i1 %tobool36, label %if.then37, label %if.end38, !dbg !1404

if.then37:                                        ; preds = %if.end35
  %45 = load void (i32*)*, void (i32*)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 3), align 8, !dbg !1405
  %46 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1405
  %hctx = getelementptr inbounds %struct.zip, %struct.zip* %46, i32 0, i32 19, !dbg !1405
  call void %45(i32* %hctx), !dbg !1405
  br label %if.end38, !dbg !1405

if.end38:                                         ; preds = %if.then37, %if.end35
  %47 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1406
  %hctx_valid39 = getelementptr inbounds %struct.zip, %struct.zip* %47, i32 0, i32 20, !dbg !1407
  store i8 0, i8* %hctx_valid39, align 8, !dbg !1408
  %48 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1409
  %cctx_valid40 = getelementptr inbounds %struct.zip, %struct.zip* %48, i32 0, i32 18, !dbg !1410
  store i8 0, i8* %cctx_valid40, align 8, !dbg !1411
  %49 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1412
  %tctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %49, i32 0, i32 14, !dbg !1413
  store i8 0, i8* %tctx_valid, align 4, !dbg !1414
  %50 = load i32, i32* %type, align 4, !dbg !1415
  %cmp41 = icmp eq i32 %50, 32768, !dbg !1417
  br i1 %cmp41, label %land.lhs.true43, label %if.end53, !dbg !1418

land.lhs.true43:                                  ; preds = %if.end38
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1419
  %call44 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %51), !dbg !1421
  %tobool45 = icmp ne i32 %call44, 0, !dbg !1421
  br i1 %tobool45, label %lor.lhs.false, label %if.then49, !dbg !1422

lor.lhs.false:                                    ; preds = %land.lhs.true43
  %52 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1423
  %call46 = call i64 @archive_entry_size(%struct.archive_entry* %52), !dbg !1424
  %cmp47 = icmp sgt i64 %call46, 0, !dbg !1425
  br i1 %cmp47, label %if.then49, label %if.end53, !dbg !1426

if.then49:                                        ; preds = %lor.lhs.false, %land.lhs.true43
  %53 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1428
  %encryption_type = getelementptr inbounds %struct.zip, %struct.zip* %53, i32 0, i32 34, !dbg !1430
  %54 = load i32, i32* %encryption_type, align 4, !dbg !1430
  switch i32 %54, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb
    i32 3, label %sw.bb
  ], !dbg !1431

sw.bb:                                            ; preds = %if.then49, %if.then49, %if.then49
  %55 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1432
  %entry_flags50 = getelementptr inbounds %struct.zip, %struct.zip* %55, i32 0, i32 10, !dbg !1434
  %56 = load i32, i32* %entry_flags50, align 4, !dbg !1435
  %or = or i32 %56, 1, !dbg !1435
  store i32 %or, i32* %entry_flags50, align 4, !dbg !1435
  %57 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1436
  %encryption_type51 = getelementptr inbounds %struct.zip, %struct.zip* %57, i32 0, i32 34, !dbg !1437
  %58 = load i32, i32* %encryption_type51, align 4, !dbg !1437
  %59 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1438
  %entry_encryption52 = getelementptr inbounds %struct.zip, %struct.zip* %59, i32 0, i32 9, !dbg !1439
  store i32 %58, i32* %entry_encryption52, align 8, !dbg !1440
  br label %sw.epilog, !dbg !1441

sw.default:                                       ; preds = %if.then49
  br label %sw.epilog, !dbg !1442

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  br label %if.end53, !dbg !1443

if.end53:                                         ; preds = %sw.epilog, %lor.lhs.false, %if.end38
  %60 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1444
  %call54 = call %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %60), !dbg !1445
  %61 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1446
  %entry55 = getelementptr inbounds %struct.zip, %struct.zip* %61, i32 0, i32 6, !dbg !1447
  store %struct.archive_entry* %call54, %struct.archive_entry** %entry55, align 8, !dbg !1448
  %62 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1449
  %entry56 = getelementptr inbounds %struct.zip, %struct.zip* %62, i32 0, i32 6, !dbg !1451
  %63 = load %struct.archive_entry*, %struct.archive_entry** %entry56, align 8, !dbg !1451
  %cmp57 = icmp eq %struct.archive_entry* %63, null, !dbg !1452
  br i1 %cmp57, label %if.then59, label %if.end61, !dbg !1453

if.then59:                                        ; preds = %if.end53
  %64 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1454
  %archive60 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %64, i32 0, i32 0, !dbg !1456
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive60, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.30, i32 0, i32 0)), !dbg !1457
  store i32 -30, i32* %retval, align 4, !dbg !1458
  br label %return, !dbg !1458

if.end61:                                         ; preds = %if.end53
  %65 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1459
  %cmp62 = icmp ne %struct.archive_string_conv* %65, null, !dbg !1461
  br i1 %cmp62, label %if.then64, label %if.end103, !dbg !1462

if.then64:                                        ; preds = %if.end61
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1463, metadata !728), !dbg !1465
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1466, metadata !728), !dbg !1467
  %66 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1468
  %67 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1470
  %call65 = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %66, i8** %p, i64* %len, %struct.archive_string_conv* %67), !dbg !1471
  %cmp66 = icmp ne i32 %call65, 0, !dbg !1472
  br i1 %cmp66, label %if.then68, label %if.end78, !dbg !1473

if.then68:                                        ; preds = %if.then64
  %call69 = call i32* @__errno_location() #1, !dbg !1474
  %68 = load i32, i32* %call69, align 4, !dbg !1474
  %cmp70 = icmp eq i32 %68, 12, !dbg !1477
  br i1 %cmp70, label %if.then72, label %if.end74, !dbg !1478

if.then72:                                        ; preds = %if.then68
  %69 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1479
  %archive73 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %69, i32 0, i32 0, !dbg !1481
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive73, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.31, i32 0, i32 0)), !dbg !1482
  store i32 -30, i32* %retval, align 4, !dbg !1483
  br label %return, !dbg !1483

if.end74:                                         ; preds = %if.then68
  %70 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1484
  %archive75 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %70, i32 0, i32 0, !dbg !1485
  %71 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1486
  %call76 = call i8* @archive_entry_pathname(%struct.archive_entry* %71), !dbg !1487
  %72 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1488
  %call77 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %72), !dbg !1489
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive75, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.32, i32 0, i32 0), i8* %call76, i8* %call77), !dbg !1490
  store i32 -20, i32* %ret2, align 4, !dbg !1491
  br label %if.end78, !dbg !1492

if.end78:                                         ; preds = %if.end74, %if.then64
  %73 = load i64, i64* %len, align 8, !dbg !1493
  %cmp79 = icmp ugt i64 %73, 0, !dbg !1495
  br i1 %cmp79, label %if.then81, label %if.end83, !dbg !1496

if.then81:                                        ; preds = %if.end78
  %74 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1497
  %entry82 = getelementptr inbounds %struct.zip, %struct.zip* %74, i32 0, i32 6, !dbg !1498
  %75 = load %struct.archive_entry*, %struct.archive_entry** %entry82, align 8, !dbg !1498
  %76 = load i8*, i8** %p, align 8, !dbg !1499
  call void @archive_entry_set_pathname(%struct.archive_entry* %75, i8* %76), !dbg !1500
  br label %if.end83, !dbg !1500

if.end83:                                         ; preds = %if.then81, %if.end78
  %77 = load i32, i32* %type, align 4, !dbg !1501
  %cmp84 = icmp eq i32 %77, 40960, !dbg !1503
  br i1 %cmp84, label %if.then86, label %if.end102, !dbg !1504

if.then86:                                        ; preds = %if.end83
  %78 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1505
  %79 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1508
  %call87 = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %78, i8** %p, i64* %len, %struct.archive_string_conv* %79), !dbg !1509
  %tobool88 = icmp ne i32 %call87, 0, !dbg !1509
  br i1 %tobool88, label %if.then89, label %if.else, !dbg !1510

if.then89:                                        ; preds = %if.then86
  %call90 = call i32* @__errno_location() #1, !dbg !1511
  %80 = load i32, i32* %call90, align 4, !dbg !1511
  %cmp91 = icmp eq i32 %80, 12, !dbg !1514
  br i1 %cmp91, label %if.then93, label %if.end95, !dbg !1515

if.then93:                                        ; preds = %if.then89
  %81 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1516
  %archive94 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %81, i32 0, i32 0, !dbg !1518
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive94, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.33, i32 0, i32 0)), !dbg !1519
  store i32 -30, i32* %retval, align 4, !dbg !1520
  br label %return, !dbg !1520

if.end95:                                         ; preds = %if.then89
  br label %if.end101, !dbg !1521

if.else:                                          ; preds = %if.then86
  %82 = load i64, i64* %len, align 8, !dbg !1522
  %cmp96 = icmp ugt i64 %82, 0, !dbg !1525
  br i1 %cmp96, label %if.then98, label %if.end100, !dbg !1522

if.then98:                                        ; preds = %if.else
  %83 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1526
  %entry99 = getelementptr inbounds %struct.zip, %struct.zip* %83, i32 0, i32 6, !dbg !1527
  %84 = load %struct.archive_entry*, %struct.archive_entry** %entry99, align 8, !dbg !1527
  %85 = load i8*, i8** %p, align 8, !dbg !1528
  call void @archive_entry_set_symlink(%struct.archive_entry* %84, i8* %85), !dbg !1529
  br label %if.end100, !dbg !1529

if.end100:                                        ; preds = %if.then98, %if.else
  br label %if.end101

if.end101:                                        ; preds = %if.end100, %if.end95
  br label %if.end102, !dbg !1530

if.end102:                                        ; preds = %if.end101, %if.end83
  br label %if.end103, !dbg !1531

if.end103:                                        ; preds = %if.end102, %if.end61
  %86 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1532
  %entry104 = getelementptr inbounds %struct.zip, %struct.zip* %86, i32 0, i32 6, !dbg !1534
  %87 = load %struct.archive_entry*, %struct.archive_entry** %entry104, align 8, !dbg !1534
  %call105 = call i8* @archive_entry_pathname(%struct.archive_entry* %87), !dbg !1535
  %call106 = call i32 @is_all_ascii(i8* %call105), !dbg !1536
  %tobool107 = icmp ne i32 %call106, 0, !dbg !1538
  br i1 %tobool107, label %if.end131, label %if.then108, !dbg !1539

if.then108:                                       ; preds = %if.end103
  %88 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1540
  %opt_sconv = getelementptr inbounds %struct.zip, %struct.zip* %88, i32 0, i32 29, !dbg !1543
  %89 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !1543
  %cmp109 = icmp ne %struct.archive_string_conv* %89, null, !dbg !1544
  br i1 %cmp109, label %if.then111, label %if.else121, !dbg !1545

if.then111:                                       ; preds = %if.then108
  %90 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1546
  %opt_sconv112 = getelementptr inbounds %struct.zip, %struct.zip* %90, i32 0, i32 29, !dbg !1549
  %91 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv112, align 8, !dbg !1549
  %call113 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %91), !dbg !1550
  %call114 = call i32 @strcmp(i8* %call113, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.34, i32 0, i32 0)) #9, !dbg !1551
  %cmp115 = icmp eq i32 %call114, 0, !dbg !1553
  br i1 %cmp115, label %if.then117, label %if.end120, !dbg !1554

if.then117:                                       ; preds = %if.then111
  %92 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1555
  %entry_flags118 = getelementptr inbounds %struct.zip, %struct.zip* %92, i32 0, i32 10, !dbg !1556
  %93 = load i32, i32* %entry_flags118, align 4, !dbg !1557
  %or119 = or i32 %93, 2048, !dbg !1557
  store i32 %or119, i32* %entry_flags118, align 4, !dbg !1557
  br label %if.end120, !dbg !1555

if.end120:                                        ; preds = %if.then117, %if.then111
  br label %if.end130, !dbg !1558

if.else121:                                       ; preds = %if.then108
  %call122 = call i8* @nl_langinfo(i32 14) #8, !dbg !1559
  %call123 = call i32 @strcmp(i8* %call122, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.34, i32 0, i32 0)) #9, !dbg !1562
  %cmp124 = icmp eq i32 %call123, 0, !dbg !1564
  br i1 %cmp124, label %if.then126, label %if.end129, !dbg !1565

if.then126:                                       ; preds = %if.else121
  %94 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1566
  %entry_flags127 = getelementptr inbounds %struct.zip, %struct.zip* %94, i32 0, i32 10, !dbg !1568
  %95 = load i32, i32* %entry_flags127, align 4, !dbg !1569
  %or128 = or i32 %95, 2048, !dbg !1569
  store i32 %or128, i32* %entry_flags127, align 4, !dbg !1569
  br label %if.end129, !dbg !1570

if.end129:                                        ; preds = %if.then126, %if.else121
  br label %if.end130

if.end130:                                        ; preds = %if.end129, %if.end120
  br label %if.end131, !dbg !1571

if.end131:                                        ; preds = %if.end130, %if.end103
  %96 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1572
  %entry132 = getelementptr inbounds %struct.zip, %struct.zip* %96, i32 0, i32 6, !dbg !1573
  %97 = load %struct.archive_entry*, %struct.archive_entry** %entry132, align 8, !dbg !1573
  %call133 = call i64 @path_length(%struct.archive_entry* %97), !dbg !1574
  store i64 %call133, i64* %filename_length, align 8, !dbg !1575
  %98 = load i32, i32* %type, align 4, !dbg !1576
  %cmp134 = icmp eq i32 %98, 40960, !dbg !1578
  br i1 %cmp134, label %if.then136, label %if.else154, !dbg !1579

if.then136:                                       ; preds = %if.end131
  %99 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1580
  %entry137 = getelementptr inbounds %struct.zip, %struct.zip* %99, i32 0, i32 6, !dbg !1582
  %100 = load %struct.archive_entry*, %struct.archive_entry** %entry137, align 8, !dbg !1582
  %call138 = call i8* @archive_entry_symlink(%struct.archive_entry* %100), !dbg !1583
  store i8* %call138, i8** %slink, align 8, !dbg !1584
  %101 = load i8*, i8** %slink, align 8, !dbg !1585
  %cmp139 = icmp ne i8* %101, null, !dbg !1587
  br i1 %cmp139, label %if.then141, label %if.else143, !dbg !1588

if.then141:                                       ; preds = %if.then136
  %102 = load i8*, i8** %slink, align 8, !dbg !1589
  %call142 = call i64 @strlen(i8* %102) #9, !dbg !1590
  store i64 %call142, i64* %slink_size, align 8, !dbg !1591
  br label %if.end144, !dbg !1592

if.else143:                                       ; preds = %if.then136
  store i64 0, i64* %slink_size, align 8, !dbg !1593
  br label %if.end144

if.end144:                                        ; preds = %if.else143, %if.then141
  %103 = load i64, i64* %slink_size, align 8, !dbg !1594
  %104 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1595
  %entry_uncompressed_limit145 = getelementptr inbounds %struct.zip, %struct.zip* %104, i32 0, i32 5, !dbg !1596
  store i64 %103, i64* %entry_uncompressed_limit145, align 8, !dbg !1597
  %105 = load i64, i64* %slink_size, align 8, !dbg !1598
  %106 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1599
  %entry_compressed_size146 = getelementptr inbounds %struct.zip, %struct.zip* %106, i32 0, i32 1, !dbg !1600
  store i64 %105, i64* %entry_compressed_size146, align 8, !dbg !1601
  %107 = load i64, i64* %slink_size, align 8, !dbg !1602
  %108 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1603
  %entry_uncompressed_size147 = getelementptr inbounds %struct.zip, %struct.zip* %108, i32 0, i32 2, !dbg !1604
  store i64 %107, i64* %entry_uncompressed_size147, align 8, !dbg !1605
  %109 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1606
  %crc32func148 = getelementptr inbounds %struct.zip, %struct.zip* %109, i32 0, i32 23, !dbg !1607
  %110 = load i64 (i64, i8*, i64)*, i64 (i64, i8*, i64)** %crc32func148, align 8, !dbg !1607
  %111 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1608
  %entry_crc32149 = getelementptr inbounds %struct.zip, %struct.zip* %111, i32 0, i32 7, !dbg !1609
  %112 = load i32, i32* %entry_crc32149, align 8, !dbg !1609
  %conv150 = zext i32 %112 to i64, !dbg !1608
  %113 = load i8*, i8** %slink, align 8, !dbg !1610
  %114 = load i64, i64* %slink_size, align 8, !dbg !1611
  %call151 = call i64 %110(i64 %conv150, i8* %113, i64 %114), !dbg !1606
  %conv152 = trunc i64 %call151 to i32, !dbg !1606
  %115 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1612
  %entry_crc32153 = getelementptr inbounds %struct.zip, %struct.zip* %115, i32 0, i32 7, !dbg !1613
  store i32 %conv152, i32* %entry_crc32153, align 8, !dbg !1614
  %116 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1615
  %entry_compression = getelementptr inbounds %struct.zip, %struct.zip* %116, i32 0, i32 8, !dbg !1616
  store i32 0, i32* %entry_compression, align 4, !dbg !1617
  store i32 20, i32* %version_needed, align 4, !dbg !1618
  br label %if.end255, !dbg !1619

if.else154:                                       ; preds = %if.end131
  %117 = load i32, i32* %type, align 4, !dbg !1620
  %cmp155 = icmp ne i32 %117, 32768, !dbg !1623
  br i1 %cmp155, label %if.then157, label %if.else160, !dbg !1620

if.then157:                                       ; preds = %if.else154
  %118 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1624
  %entry_compression158 = getelementptr inbounds %struct.zip, %struct.zip* %118, i32 0, i32 8, !dbg !1626
  store i32 0, i32* %entry_compression158, align 4, !dbg !1627
  %119 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1628
  %entry_uncompressed_limit159 = getelementptr inbounds %struct.zip, %struct.zip* %119, i32 0, i32 5, !dbg !1629
  store i64 0, i64* %entry_uncompressed_limit159, align 8, !dbg !1630
  store i32 20, i32* %version_needed, align 4, !dbg !1631
  br label %if.end254, !dbg !1632

if.else160:                                       ; preds = %if.else154
  %120 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1633
  %entry161 = getelementptr inbounds %struct.zip, %struct.zip* %120, i32 0, i32 6, !dbg !1636
  %121 = load %struct.archive_entry*, %struct.archive_entry** %entry161, align 8, !dbg !1636
  %call162 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %121), !dbg !1637
  %tobool163 = icmp ne i32 %call162, 0, !dbg !1637
  br i1 %tobool163, label %if.then164, label %if.else222, !dbg !1637

if.then164:                                       ; preds = %if.else160
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1638, metadata !728), !dbg !1640
  %122 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1641
  %entry165 = getelementptr inbounds %struct.zip, %struct.zip* %122, i32 0, i32 6, !dbg !1642
  %123 = load %struct.archive_entry*, %struct.archive_entry** %entry165, align 8, !dbg !1642
  %call166 = call i64 @archive_entry_size(%struct.archive_entry* %123), !dbg !1643
  store i64 %call166, i64* %size, align 8, !dbg !1640
  call void @llvm.dbg.declare(metadata i64* %additional_size, metadata !1644, metadata !728), !dbg !1645
  store i64 0, i64* %additional_size, align 8, !dbg !1645
  %124 = load i64, i64* %size, align 8, !dbg !1646
  %125 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1647
  %entry_uncompressed_limit167 = getelementptr inbounds %struct.zip, %struct.zip* %125, i32 0, i32 5, !dbg !1648
  store i64 %124, i64* %entry_uncompressed_limit167, align 8, !dbg !1649
  %126 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1650
  %requested_compression = getelementptr inbounds %struct.zip, %struct.zip* %126, i32 0, i32 31, !dbg !1651
  %127 = load i32, i32* %requested_compression, align 8, !dbg !1651
  %128 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1652
  %entry_compression168 = getelementptr inbounds %struct.zip, %struct.zip* %128, i32 0, i32 8, !dbg !1653
  store i32 %127, i32* %entry_compression168, align 4, !dbg !1654
  %129 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1655
  %entry_compression169 = getelementptr inbounds %struct.zip, %struct.zip* %129, i32 0, i32 8, !dbg !1657
  %130 = load i32, i32* %entry_compression169, align 4, !dbg !1657
  %cmp170 = icmp eq i32 %130, -1, !dbg !1658
  br i1 %cmp170, label %if.then172, label %if.end174, !dbg !1659

if.then172:                                       ; preds = %if.then164
  %131 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1660
  %entry_compression173 = getelementptr inbounds %struct.zip, %struct.zip* %131, i32 0, i32 8, !dbg !1662
  store i32 8, i32* %entry_compression173, align 4, !dbg !1663
  br label %if.end174, !dbg !1664

if.end174:                                        ; preds = %if.then172, %if.then164
  %132 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1665
  %entry_compression175 = getelementptr inbounds %struct.zip, %struct.zip* %132, i32 0, i32 8, !dbg !1667
  %133 = load i32, i32* %entry_compression175, align 4, !dbg !1667
  %cmp176 = icmp eq i32 %133, 0, !dbg !1668
  br i1 %cmp176, label %if.then178, label %if.else181, !dbg !1669

if.then178:                                       ; preds = %if.end174
  %134 = load i64, i64* %size, align 8, !dbg !1670
  %135 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1672
  %entry_compressed_size179 = getelementptr inbounds %struct.zip, %struct.zip* %135, i32 0, i32 1, !dbg !1673
  store i64 %134, i64* %entry_compressed_size179, align 8, !dbg !1674
  %136 = load i64, i64* %size, align 8, !dbg !1675
  %137 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1676
  %entry_uncompressed_size180 = getelementptr inbounds %struct.zip, %struct.zip* %137, i32 0, i32 2, !dbg !1677
  store i64 %136, i64* %entry_uncompressed_size180, align 8, !dbg !1678
  store i32 10, i32* %version_needed, align 4, !dbg !1679
  br label %if.end183, !dbg !1680

if.else181:                                       ; preds = %if.end174
  %138 = load i64, i64* %size, align 8, !dbg !1681
  %139 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1683
  %entry_uncompressed_size182 = getelementptr inbounds %struct.zip, %struct.zip* %139, i32 0, i32 2, !dbg !1684
  store i64 %138, i64* %entry_uncompressed_size182, align 8, !dbg !1685
  store i32 20, i32* %version_needed, align 4, !dbg !1686
  br label %if.end183

if.end183:                                        ; preds = %if.else181, %if.then178
  %140 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1687
  %entry_flags184 = getelementptr inbounds %struct.zip, %struct.zip* %140, i32 0, i32 10, !dbg !1689
  %141 = load i32, i32* %entry_flags184, align 4, !dbg !1689
  %and185 = and i32 %141, 1, !dbg !1690
  %tobool186 = icmp ne i32 %and185, 0, !dbg !1690
  br i1 %tobool186, label %if.then187, label %if.end200, !dbg !1691

if.then187:                                       ; preds = %if.end183
  %142 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1692
  %entry_encryption188 = getelementptr inbounds %struct.zip, %struct.zip* %142, i32 0, i32 9, !dbg !1694
  %143 = load i32, i32* %entry_encryption188, align 8, !dbg !1694
  switch i32 %143, label %sw.default192 [
    i32 1, label %sw.bb189
    i32 2, label %sw.bb190
    i32 3, label %sw.bb191
  ], !dbg !1695

sw.bb189:                                         ; preds = %if.then187
  store i64 12, i64* %additional_size, align 8, !dbg !1696
  store i32 20, i32* %version_needed, align 4, !dbg !1698
  br label %sw.epilog193, !dbg !1699

sw.bb190:                                         ; preds = %if.then187
  store i64 20, i64* %additional_size, align 8, !dbg !1700
  store i32 20, i32* %version_needed, align 4, !dbg !1701
  br label %sw.epilog193, !dbg !1702

sw.bb191:                                         ; preds = %if.then187
  store i64 28, i64* %additional_size, align 8, !dbg !1703
  store i32 20, i32* %version_needed, align 4, !dbg !1704
  br label %sw.epilog193, !dbg !1705

sw.default192:                                    ; preds = %if.then187
  br label %sw.epilog193, !dbg !1706

sw.epilog193:                                     ; preds = %sw.default192, %sw.bb191, %sw.bb190, %sw.bb189
  %144 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1707
  %entry_compression194 = getelementptr inbounds %struct.zip, %struct.zip* %144, i32 0, i32 8, !dbg !1709
  %145 = load i32, i32* %entry_compression194, align 4, !dbg !1709
  %cmp195 = icmp eq i32 %145, 0, !dbg !1710
  br i1 %cmp195, label %if.then197, label %if.end199, !dbg !1711

if.then197:                                       ; preds = %sw.epilog193
  %146 = load i64, i64* %additional_size, align 8, !dbg !1712
  %147 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1713
  %entry_compressed_size198 = getelementptr inbounds %struct.zip, %struct.zip* %147, i32 0, i32 1, !dbg !1714
  %148 = load i64, i64* %entry_compressed_size198, align 8, !dbg !1715
  %add = add nsw i64 %148, %146, !dbg !1715
  store i64 %add, i64* %entry_compressed_size198, align 8, !dbg !1715
  br label %if.end199, !dbg !1713

if.end199:                                        ; preds = %if.then197, %sw.epilog193
  br label %if.end200, !dbg !1716

if.end200:                                        ; preds = %if.end199, %if.end183
  %149 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1717
  %flags201 = getelementptr inbounds %struct.zip, %struct.zip* %149, i32 0, i32 35, !dbg !1719
  %150 = load i32, i32* %flags201, align 8, !dbg !1719
  %and202 = and i32 %150, 2, !dbg !1720
  %tobool203 = icmp ne i32 %and202, 0, !dbg !1720
  br i1 %tobool203, label %if.then217, label %lor.lhs.false204, !dbg !1721

lor.lhs.false204:                                 ; preds = %if.end200
  %151 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1722
  %entry_uncompressed_size205 = getelementptr inbounds %struct.zip, %struct.zip* %151, i32 0, i32 2, !dbg !1724
  %152 = load i64, i64* %entry_uncompressed_size205, align 8, !dbg !1724
  %153 = load i64, i64* %additional_size, align 8, !dbg !1725
  %add206 = add nsw i64 %152, %153, !dbg !1726
  %cmp207 = icmp sgt i64 %add206, 4294967295, !dbg !1727
  br i1 %cmp207, label %if.then217, label %lor.lhs.false209, !dbg !1728

lor.lhs.false209:                                 ; preds = %lor.lhs.false204
  %154 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1729
  %entry_uncompressed_size210 = getelementptr inbounds %struct.zip, %struct.zip* %154, i32 0, i32 2, !dbg !1730
  %155 = load i64, i64* %entry_uncompressed_size210, align 8, !dbg !1730
  %cmp211 = icmp sgt i64 %155, 4278190080, !dbg !1731
  br i1 %cmp211, label %land.lhs.true213, label %if.end219, !dbg !1732

land.lhs.true213:                                 ; preds = %lor.lhs.false209
  %156 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1733
  %entry_compression214 = getelementptr inbounds %struct.zip, %struct.zip* %156, i32 0, i32 8, !dbg !1734
  %157 = load i32, i32* %entry_compression214, align 4, !dbg !1734
  %cmp215 = icmp ne i32 %157, 0, !dbg !1735
  br i1 %cmp215, label %if.then217, label %if.end219, !dbg !1736

if.then217:                                       ; preds = %land.lhs.true213, %lor.lhs.false204, %if.end200
  %158 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1738
  %entry_uses_zip64218 = getelementptr inbounds %struct.zip, %struct.zip* %158, i32 0, i32 11, !dbg !1740
  store i32 1, i32* %entry_uses_zip64218, align 8, !dbg !1741
  store i32 45, i32* %version_needed, align 4, !dbg !1742
  br label %if.end219, !dbg !1743

if.end219:                                        ; preds = %if.then217, %land.lhs.true213, %lor.lhs.false209
  %159 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1744
  %entry_flags220 = getelementptr inbounds %struct.zip, %struct.zip* %159, i32 0, i32 10, !dbg !1745
  %160 = load i32, i32* %entry_flags220, align 4, !dbg !1746
  %or221 = or i32 %160, 8, !dbg !1746
  store i32 %or221, i32* %entry_flags220, align 4, !dbg !1746
  br label %if.end253, !dbg !1747

if.else222:                                       ; preds = %if.else160
  %161 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1748
  %entry_compression223 = getelementptr inbounds %struct.zip, %struct.zip* %161, i32 0, i32 8, !dbg !1750
  store i32 8, i32* %entry_compression223, align 4, !dbg !1751
  %162 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1752
  %entry_flags224 = getelementptr inbounds %struct.zip, %struct.zip* %162, i32 0, i32 10, !dbg !1753
  %163 = load i32, i32* %entry_flags224, align 4, !dbg !1754
  %or225 = or i32 %163, 8, !dbg !1754
  store i32 %or225, i32* %entry_flags224, align 4, !dbg !1754
  %164 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1755
  %flags226 = getelementptr inbounds %struct.zip, %struct.zip* %164, i32 0, i32 35, !dbg !1757
  %165 = load i32, i32* %flags226, align 8, !dbg !1757
  %and227 = and i32 %165, 1, !dbg !1758
  %cmp228 = icmp eq i32 %and227, 0, !dbg !1759
  br i1 %cmp228, label %if.then230, label %if.else232, !dbg !1760

if.then230:                                       ; preds = %if.else222
  %166 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1761
  %entry_uses_zip64231 = getelementptr inbounds %struct.zip, %struct.zip* %166, i32 0, i32 11, !dbg !1763
  store i32 1, i32* %entry_uses_zip64231, align 8, !dbg !1764
  store i32 45, i32* %version_needed, align 4, !dbg !1765
  br label %if.end239, !dbg !1766

if.else232:                                       ; preds = %if.else222
  %167 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1767
  %entry_compression233 = getelementptr inbounds %struct.zip, %struct.zip* %167, i32 0, i32 8, !dbg !1770
  %168 = load i32, i32* %entry_compression233, align 4, !dbg !1770
  %cmp234 = icmp eq i32 %168, 0, !dbg !1771
  br i1 %cmp234, label %if.then236, label %if.else237, !dbg !1767

if.then236:                                       ; preds = %if.else232
  store i32 10, i32* %version_needed, align 4, !dbg !1772
  br label %if.end238, !dbg !1774

if.else237:                                       ; preds = %if.else232
  store i32 20, i32* %version_needed, align 4, !dbg !1775
  br label %if.end238

if.end238:                                        ; preds = %if.else237, %if.then236
  br label %if.end239

if.end239:                                        ; preds = %if.end238, %if.then230
  %169 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1777
  %entry_flags240 = getelementptr inbounds %struct.zip, %struct.zip* %169, i32 0, i32 10, !dbg !1779
  %170 = load i32, i32* %entry_flags240, align 4, !dbg !1779
  %and241 = and i32 %170, 1, !dbg !1780
  %tobool242 = icmp ne i32 %and241, 0, !dbg !1780
  br i1 %tobool242, label %if.then243, label %if.end252, !dbg !1781

if.then243:                                       ; preds = %if.end239
  %171 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1782
  %entry_encryption244 = getelementptr inbounds %struct.zip, %struct.zip* %171, i32 0, i32 9, !dbg !1784
  %172 = load i32, i32* %entry_encryption244, align 8, !dbg !1784
  switch i32 %172, label %sw.default250 [
    i32 1, label %sw.bb245
    i32 2, label %sw.bb245
    i32 3, label %sw.bb245
  ], !dbg !1785

sw.bb245:                                         ; preds = %if.then243, %if.then243, %if.then243
  %173 = load i32, i32* %version_needed, align 4, !dbg !1786
  %cmp246 = icmp slt i32 %173, 20, !dbg !1789
  br i1 %cmp246, label %if.then248, label %if.end249, !dbg !1790

if.then248:                                       ; preds = %sw.bb245
  store i32 20, i32* %version_needed, align 4, !dbg !1791
  br label %if.end249, !dbg !1792

if.end249:                                        ; preds = %if.then248, %sw.bb245
  br label %sw.epilog251, !dbg !1793

sw.default250:                                    ; preds = %if.then243
  br label %sw.epilog251, !dbg !1794

sw.epilog251:                                     ; preds = %sw.default250, %if.end249
  br label %if.end252, !dbg !1795

if.end252:                                        ; preds = %sw.epilog251, %if.end239
  br label %if.end253

if.end253:                                        ; preds = %if.end252, %if.end219
  br label %if.end254

if.end254:                                        ; preds = %if.end253, %if.then157
  br label %if.end255

if.end255:                                        ; preds = %if.end254, %if.end144
  %arraydecay = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1796
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 32, i32 16, i1 false), !dbg !1796
  %arraydecay256 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1797
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay256, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.35, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !1797
  %arraydecay257 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1798
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay257, i64 4, !dbg !1799
  %174 = load i32, i32* %version_needed, align 4, !dbg !1800
  %conv258 = trunc i32 %174 to i16, !dbg !1800
  call void @archive_le16enc(i8* %add.ptr, i16 zeroext %conv258), !dbg !1801
  %arraydecay259 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1802
  %add.ptr260 = getelementptr inbounds i8, i8* %arraydecay259, i64 6, !dbg !1803
  %175 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1804
  %entry_flags261 = getelementptr inbounds %struct.zip, %struct.zip* %175, i32 0, i32 10, !dbg !1805
  %176 = load i32, i32* %entry_flags261, align 4, !dbg !1805
  %conv262 = trunc i32 %176 to i16, !dbg !1804
  call void @archive_le16enc(i8* %add.ptr260, i16 zeroext %conv262), !dbg !1806
  %177 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1807
  %entry_encryption263 = getelementptr inbounds %struct.zip, %struct.zip* %177, i32 0, i32 9, !dbg !1809
  %178 = load i32, i32* %entry_encryption263, align 8, !dbg !1809
  %cmp264 = icmp eq i32 %178, 2, !dbg !1810
  br i1 %cmp264, label %if.then270, label %lor.lhs.false266, !dbg !1811

lor.lhs.false266:                                 ; preds = %if.end255
  %179 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1812
  %entry_encryption267 = getelementptr inbounds %struct.zip, %struct.zip* %179, i32 0, i32 9, !dbg !1814
  %180 = load i32, i32* %entry_encryption267, align 8, !dbg !1814
  %cmp268 = icmp eq i32 %180, 3, !dbg !1815
  br i1 %cmp268, label %if.then270, label %if.else273, !dbg !1816

if.then270:                                       ; preds = %lor.lhs.false266, %if.end255
  %arraydecay271 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1817
  %add.ptr272 = getelementptr inbounds i8, i8* %arraydecay271, i64 8, !dbg !1818
  call void @archive_le16enc(i8* %add.ptr272, i16 zeroext 99), !dbg !1819
  br label %if.end278, !dbg !1819

if.else273:                                       ; preds = %lor.lhs.false266
  %arraydecay274 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1820
  %add.ptr275 = getelementptr inbounds i8, i8* %arraydecay274, i64 8, !dbg !1821
  %181 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1822
  %entry_compression276 = getelementptr inbounds %struct.zip, %struct.zip* %181, i32 0, i32 8, !dbg !1823
  %182 = load i32, i32* %entry_compression276, align 4, !dbg !1823
  %conv277 = trunc i32 %182 to i16, !dbg !1822
  call void @archive_le16enc(i8* %add.ptr275, i16 zeroext %conv277), !dbg !1824
  br label %if.end278

if.end278:                                        ; preds = %if.else273, %if.then270
  %arraydecay279 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1825
  %add.ptr280 = getelementptr inbounds i8, i8* %arraydecay279, i64 10, !dbg !1826
  %183 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1827
  %entry281 = getelementptr inbounds %struct.zip, %struct.zip* %183, i32 0, i32 6, !dbg !1828
  %184 = load %struct.archive_entry*, %struct.archive_entry** %entry281, align 8, !dbg !1828
  %call282 = call i64 @archive_entry_mtime(%struct.archive_entry* %184), !dbg !1829
  %call283 = call i32 @dos_time(i64 %call282), !dbg !1830
  call void @archive_le32enc(i8* %add.ptr280, i32 %call283), !dbg !1831
  %arraydecay284 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1832
  %add.ptr285 = getelementptr inbounds i8, i8* %arraydecay284, i64 14, !dbg !1833
  %185 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1834
  %entry_crc32286 = getelementptr inbounds %struct.zip, %struct.zip* %185, i32 0, i32 7, !dbg !1835
  %186 = load i32, i32* %entry_crc32286, align 8, !dbg !1835
  call void @archive_le32enc(i8* %add.ptr285, i32 %186), !dbg !1836
  %187 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1837
  %entry_uses_zip64287 = getelementptr inbounds %struct.zip, %struct.zip* %187, i32 0, i32 11, !dbg !1839
  %188 = load i32, i32* %entry_uses_zip64287, align 8, !dbg !1839
  %tobool288 = icmp ne i32 %188, 0, !dbg !1837
  br i1 %tobool288, label %if.then289, label %if.else294, !dbg !1840

if.then289:                                       ; preds = %if.end278
  %arraydecay290 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1841
  %add.ptr291 = getelementptr inbounds i8, i8* %arraydecay290, i64 18, !dbg !1843
  call void @archive_le32enc(i8* %add.ptr291, i32 -1), !dbg !1844
  %arraydecay292 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1845
  %add.ptr293 = getelementptr inbounds i8, i8* %arraydecay292, i64 22, !dbg !1846
  call void @archive_le32enc(i8* %add.ptr293, i32 -1), !dbg !1847
  br label %if.end303, !dbg !1848

if.else294:                                       ; preds = %if.end278
  %arraydecay295 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1849
  %add.ptr296 = getelementptr inbounds i8, i8* %arraydecay295, i64 18, !dbg !1851
  %189 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1852
  %entry_compressed_size297 = getelementptr inbounds %struct.zip, %struct.zip* %189, i32 0, i32 1, !dbg !1853
  %190 = load i64, i64* %entry_compressed_size297, align 8, !dbg !1853
  %conv298 = trunc i64 %190 to i32, !dbg !1854
  call void @archive_le32enc(i8* %add.ptr296, i32 %conv298), !dbg !1855
  %arraydecay299 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1856
  %add.ptr300 = getelementptr inbounds i8, i8* %arraydecay299, i64 22, !dbg !1857
  %191 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1858
  %entry_uncompressed_size301 = getelementptr inbounds %struct.zip, %struct.zip* %191, i32 0, i32 2, !dbg !1859
  %192 = load i64, i64* %entry_uncompressed_size301, align 8, !dbg !1859
  %conv302 = trunc i64 %192 to i32, !dbg !1860
  call void @archive_le32enc(i8* %add.ptr300, i32 %conv302), !dbg !1861
  br label %if.end303

if.end303:                                        ; preds = %if.else294, %if.then289
  %arraydecay304 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !1862
  %add.ptr305 = getelementptr inbounds i8, i8* %arraydecay304, i64 26, !dbg !1863
  %193 = load i64, i64* %filename_length, align 8, !dbg !1864
  %conv306 = trunc i64 %193 to i16, !dbg !1865
  call void @archive_le16enc(i8* %add.ptr305, i16 zeroext %conv306), !dbg !1866
  %194 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1867
  %entry_encryption307 = getelementptr inbounds %struct.zip, %struct.zip* %194, i32 0, i32 9, !dbg !1869
  %195 = load i32, i32* %entry_encryption307, align 8, !dbg !1869
  %cmp308 = icmp eq i32 %195, 1, !dbg !1870
  br i1 %cmp308, label %if.then310, label %if.end319, !dbg !1871

if.then310:                                       ; preds = %if.end303
  %196 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1872
  %entry_flags311 = getelementptr inbounds %struct.zip, %struct.zip* %196, i32 0, i32 10, !dbg !1875
  %197 = load i32, i32* %entry_flags311, align 4, !dbg !1875
  %and312 = and i32 %197, 8, !dbg !1876
  %tobool313 = icmp ne i32 %and312, 0, !dbg !1876
  br i1 %tobool313, label %if.then314, label %if.else315, !dbg !1877

if.then314:                                       ; preds = %if.then310
  %arrayidx = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i64 0, i64 11, !dbg !1878
  %198 = load i8, i8* %arrayidx, align 1, !dbg !1878
  %199 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1879
  %trad_chkdat = getelementptr inbounds %struct.zip, %struct.zip* %199, i32 0, i32 15, !dbg !1880
  store i8 %198, i8* %trad_chkdat, align 1, !dbg !1881
  br label %if.end318, !dbg !1879

if.else315:                                       ; preds = %if.then310
  %arrayidx316 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i64 0, i64 17, !dbg !1882
  %200 = load i8, i8* %arrayidx316, align 1, !dbg !1882
  %201 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1883
  %trad_chkdat317 = getelementptr inbounds %struct.zip, %struct.zip* %201, i32 0, i32 15, !dbg !1884
  store i8 %200, i8* %trad_chkdat317, align 1, !dbg !1885
  br label %if.end318

if.end318:                                        ; preds = %if.else315, %if.then314
  br label %if.end319, !dbg !1886

if.end319:                                        ; preds = %if.end318, %if.end303
  %202 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1887
  %call320 = call i8* @cd_alloc(%struct.zip* %202, i64 46), !dbg !1888
  %203 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1889
  %file_header = getelementptr inbounds %struct.zip, %struct.zip* %203, i32 0, i32 21, !dbg !1890
  store i8* %call320, i8** %file_header, align 8, !dbg !1891
  %204 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1892
  %central_directory_entries = getelementptr inbounds %struct.zip, %struct.zip* %204, i32 0, i32 27, !dbg !1893
  %205 = load i64, i64* %central_directory_entries, align 8, !dbg !1894
  %inc = add i64 %205, 1, !dbg !1894
  store i64 %inc, i64* %central_directory_entries, align 8, !dbg !1894
  %206 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1895
  %file_header321 = getelementptr inbounds %struct.zip, %struct.zip* %206, i32 0, i32 21, !dbg !1896
  %207 = load i8*, i8** %file_header321, align 8, !dbg !1896
  call void @llvm.memset.p0i8.i64(i8* %207, i8 0, i64 46, i32 1, i1 false), !dbg !1897
  %208 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1898
  %file_header322 = getelementptr inbounds %struct.zip, %struct.zip* %208, i32 0, i32 21, !dbg !1899
  %209 = load i8*, i8** %file_header322, align 8, !dbg !1899
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %209, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !1900
  %210 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1901
  %file_header323 = getelementptr inbounds %struct.zip, %struct.zip* %210, i32 0, i32 21, !dbg !1902
  %211 = load i8*, i8** %file_header323, align 8, !dbg !1902
  %add.ptr324 = getelementptr inbounds i8, i8* %211, i64 4, !dbg !1903
  %212 = load i32, i32* %version_needed, align 4, !dbg !1904
  %add325 = add nsw i32 768, %212, !dbg !1905
  %conv326 = trunc i32 %add325 to i16, !dbg !1906
  call void @archive_le16enc(i8* %add.ptr324, i16 zeroext %conv326), !dbg !1907
  %213 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1908
  %file_header327 = getelementptr inbounds %struct.zip, %struct.zip* %213, i32 0, i32 21, !dbg !1909
  %214 = load i8*, i8** %file_header327, align 8, !dbg !1909
  %add.ptr328 = getelementptr inbounds i8, i8* %214, i64 6, !dbg !1910
  %215 = load i32, i32* %version_needed, align 4, !dbg !1911
  %conv329 = trunc i32 %215 to i16, !dbg !1911
  call void @archive_le16enc(i8* %add.ptr328, i16 zeroext %conv329), !dbg !1912
  %216 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1913
  %file_header330 = getelementptr inbounds %struct.zip, %struct.zip* %216, i32 0, i32 21, !dbg !1914
  %217 = load i8*, i8** %file_header330, align 8, !dbg !1914
  %add.ptr331 = getelementptr inbounds i8, i8* %217, i64 8, !dbg !1915
  %218 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1916
  %entry_flags332 = getelementptr inbounds %struct.zip, %struct.zip* %218, i32 0, i32 10, !dbg !1917
  %219 = load i32, i32* %entry_flags332, align 4, !dbg !1917
  %conv333 = trunc i32 %219 to i16, !dbg !1916
  call void @archive_le16enc(i8* %add.ptr331, i16 zeroext %conv333), !dbg !1918
  %220 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1919
  %entry_encryption334 = getelementptr inbounds %struct.zip, %struct.zip* %220, i32 0, i32 9, !dbg !1921
  %221 = load i32, i32* %entry_encryption334, align 8, !dbg !1921
  %cmp335 = icmp eq i32 %221, 2, !dbg !1922
  br i1 %cmp335, label %if.then341, label %lor.lhs.false337, !dbg !1923

lor.lhs.false337:                                 ; preds = %if.end319
  %222 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1924
  %entry_encryption338 = getelementptr inbounds %struct.zip, %struct.zip* %222, i32 0, i32 9, !dbg !1926
  %223 = load i32, i32* %entry_encryption338, align 8, !dbg !1926
  %cmp339 = icmp eq i32 %223, 3, !dbg !1927
  br i1 %cmp339, label %if.then341, label %if.else344, !dbg !1928

if.then341:                                       ; preds = %lor.lhs.false337, %if.end319
  %224 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1929
  %file_header342 = getelementptr inbounds %struct.zip, %struct.zip* %224, i32 0, i32 21, !dbg !1930
  %225 = load i8*, i8** %file_header342, align 8, !dbg !1930
  %add.ptr343 = getelementptr inbounds i8, i8* %225, i64 10, !dbg !1931
  call void @archive_le16enc(i8* %add.ptr343, i16 zeroext 99), !dbg !1932
  br label %if.end349, !dbg !1932

if.else344:                                       ; preds = %lor.lhs.false337
  %226 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1933
  %file_header345 = getelementptr inbounds %struct.zip, %struct.zip* %226, i32 0, i32 21, !dbg !1934
  %227 = load i8*, i8** %file_header345, align 8, !dbg !1934
  %add.ptr346 = getelementptr inbounds i8, i8* %227, i64 10, !dbg !1935
  %228 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1936
  %entry_compression347 = getelementptr inbounds %struct.zip, %struct.zip* %228, i32 0, i32 8, !dbg !1937
  %229 = load i32, i32* %entry_compression347, align 4, !dbg !1937
  %conv348 = trunc i32 %229 to i16, !dbg !1936
  call void @archive_le16enc(i8* %add.ptr346, i16 zeroext %conv348), !dbg !1938
  br label %if.end349

if.end349:                                        ; preds = %if.else344, %if.then341
  %230 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1939
  %file_header350 = getelementptr inbounds %struct.zip, %struct.zip* %230, i32 0, i32 21, !dbg !1940
  %231 = load i8*, i8** %file_header350, align 8, !dbg !1940
  %add.ptr351 = getelementptr inbounds i8, i8* %231, i64 12, !dbg !1941
  %232 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1942
  %entry352 = getelementptr inbounds %struct.zip, %struct.zip* %232, i32 0, i32 6, !dbg !1943
  %233 = load %struct.archive_entry*, %struct.archive_entry** %entry352, align 8, !dbg !1943
  %call353 = call i64 @archive_entry_mtime(%struct.archive_entry* %233), !dbg !1944
  %call354 = call i32 @dos_time(i64 %call353), !dbg !1945
  call void @archive_le32enc(i8* %add.ptr351, i32 %call354), !dbg !1946
  %234 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1947
  %file_header355 = getelementptr inbounds %struct.zip, %struct.zip* %234, i32 0, i32 21, !dbg !1948
  %235 = load i8*, i8** %file_header355, align 8, !dbg !1948
  %add.ptr356 = getelementptr inbounds i8, i8* %235, i64 28, !dbg !1949
  %236 = load i64, i64* %filename_length, align 8, !dbg !1950
  %conv357 = trunc i64 %236 to i16, !dbg !1951
  call void @archive_le16enc(i8* %add.ptr356, i16 zeroext %conv357), !dbg !1952
  %237 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1953
  %file_header358 = getelementptr inbounds %struct.zip, %struct.zip* %237, i32 0, i32 21, !dbg !1954
  %238 = load i8*, i8** %file_header358, align 8, !dbg !1954
  %add.ptr359 = getelementptr inbounds i8, i8* %238, i64 38, !dbg !1955
  %239 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1956
  %entry360 = getelementptr inbounds %struct.zip, %struct.zip* %239, i32 0, i32 6, !dbg !1957
  %240 = load %struct.archive_entry*, %struct.archive_entry** %entry360, align 8, !dbg !1957
  %call361 = call i32 @archive_entry_mode(%struct.archive_entry* %240), !dbg !1958
  %shl = shl i32 %call361, 16, !dbg !1959
  call void @archive_le32enc(i8* %add.ptr359, i32 %shl), !dbg !1960
  %241 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1961
  %242 = load i64, i64* %filename_length, align 8, !dbg !1962
  %call362 = call i8* @cd_alloc(%struct.zip* %241, i64 %242), !dbg !1963
  store i8* %call362, i8** %e, align 8, !dbg !1964
  %243 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !1965
  %entry363 = getelementptr inbounds %struct.zip, %struct.zip* %243, i32 0, i32 6, !dbg !1966
  %244 = load %struct.archive_entry*, %struct.archive_entry** %entry363, align 8, !dbg !1966
  %245 = load i8*, i8** %e, align 8, !dbg !1967
  call void @copy_path(%struct.archive_entry* %244, i8* %245), !dbg !1968
  %arraydecay364 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !1969
  call void @llvm.memset.p0i8.i64(i8* %arraydecay364, i8 0, i64 144, i32 16, i1 false), !dbg !1969
  %arraydecay365 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !1970
  store i8* %arraydecay365, i8** %e, align 8, !dbg !1971
  %246 = load i8*, i8** %e, align 8, !dbg !1972
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %246, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.37, i32 0, i32 0), i64 2, i32 1, i1 false), !dbg !1973
  %247 = load i8*, i8** %e, align 8, !dbg !1974
  %add.ptr366 = getelementptr inbounds i8, i8* %247, i64 2, !dbg !1975
  %248 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1976
  %call367 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %248), !dbg !1977
  %tobool368 = icmp ne i32 %call367, 0, !dbg !1977
  %cond = select i1 %tobool368, i32 4, i32 0, !dbg !1977
  %add369 = add nsw i32 1, %cond, !dbg !1978
  %249 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1979
  %call370 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %249), !dbg !1980
  %tobool371 = icmp ne i32 %call370, 0, !dbg !1980
  %cond372 = select i1 %tobool371, i32 4, i32 0, !dbg !1980
  %add373 = add nsw i32 %add369, %cond372, !dbg !1981
  %250 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1982
  %call374 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %250), !dbg !1983
  %tobool375 = icmp ne i32 %call374, 0, !dbg !1983
  %cond376 = select i1 %tobool375, i32 4, i32 0, !dbg !1983
  %add377 = add nsw i32 %add373, %cond376, !dbg !1984
  %conv378 = trunc i32 %add377 to i16, !dbg !1985
  call void @archive_le16enc(i8* %add.ptr366, i16 zeroext %conv378), !dbg !1986
  %251 = load i8*, i8** %e, align 8, !dbg !1987
  %add.ptr379 = getelementptr inbounds i8, i8* %251, i64 4, !dbg !1987
  store i8* %add.ptr379, i8** %e, align 8, !dbg !1987
  %252 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1988
  %call380 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %252), !dbg !1989
  %tobool381 = icmp ne i32 %call380, 0, !dbg !1989
  %cond382 = select i1 %tobool381, i32 1, i32 0, !dbg !1989
  %253 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1990
  %call383 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %253), !dbg !1991
  %tobool384 = icmp ne i32 %call383, 0, !dbg !1991
  %cond385 = select i1 %tobool384, i32 2, i32 0, !dbg !1991
  %or386 = or i32 %cond382, %cond385, !dbg !1992
  %254 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1993
  %call387 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %254), !dbg !1994
  %tobool388 = icmp ne i32 %call387, 0, !dbg !1994
  %cond389 = select i1 %tobool388, i32 4, i32 0, !dbg !1994
  %or390 = or i32 %or386, %cond389, !dbg !1995
  %conv391 = trunc i32 %or390 to i8, !dbg !1996
  %255 = load i8*, i8** %e, align 8, !dbg !1997
  %incdec.ptr = getelementptr inbounds i8, i8* %255, i32 1, !dbg !1997
  store i8* %incdec.ptr, i8** %e, align 8, !dbg !1997
  store i8 %conv391, i8* %255, align 1, !dbg !1998
  %256 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1999
  %call392 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %256), !dbg !2001
  %tobool393 = icmp ne i32 %call392, 0, !dbg !2001
  br i1 %tobool393, label %if.then394, label %if.end398, !dbg !2002

if.then394:                                       ; preds = %if.end349
  %257 = load i8*, i8** %e, align 8, !dbg !2003
  %258 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2005
  %call395 = call i64 @archive_entry_mtime(%struct.archive_entry* %258), !dbg !2006
  %conv396 = trunc i64 %call395 to i32, !dbg !2007
  call void @archive_le32enc(i8* %257, i32 %conv396), !dbg !2008
  %259 = load i8*, i8** %e, align 8, !dbg !2010
  %add.ptr397 = getelementptr inbounds i8, i8* %259, i64 4, !dbg !2010
  store i8* %add.ptr397, i8** %e, align 8, !dbg !2010
  br label %if.end398, !dbg !2011

if.end398:                                        ; preds = %if.then394, %if.end349
  %260 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2012
  %call399 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %260), !dbg !2014
  %tobool400 = icmp ne i32 %call399, 0, !dbg !2014
  br i1 %tobool400, label %if.then401, label %if.end405, !dbg !2015

if.then401:                                       ; preds = %if.end398
  %261 = load i8*, i8** %e, align 8, !dbg !2016
  %262 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2018
  %call402 = call i64 @archive_entry_atime(%struct.archive_entry* %262), !dbg !2019
  %conv403 = trunc i64 %call402 to i32, !dbg !2020
  call void @archive_le32enc(i8* %261, i32 %conv403), !dbg !2021
  %263 = load i8*, i8** %e, align 8, !dbg !2023
  %add.ptr404 = getelementptr inbounds i8, i8* %263, i64 4, !dbg !2023
  store i8* %add.ptr404, i8** %e, align 8, !dbg !2023
  br label %if.end405, !dbg !2024

if.end405:                                        ; preds = %if.then401, %if.end398
  %264 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2025
  %call406 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %264), !dbg !2027
  %tobool407 = icmp ne i32 %call406, 0, !dbg !2027
  br i1 %tobool407, label %if.then408, label %if.end412, !dbg !2028

if.then408:                                       ; preds = %if.end405
  %265 = load i8*, i8** %e, align 8, !dbg !2029
  %266 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2031
  %call409 = call i64 @archive_entry_ctime(%struct.archive_entry* %266), !dbg !2032
  %conv410 = trunc i64 %call409 to i32, !dbg !2033
  call void @archive_le32enc(i8* %265, i32 %conv410), !dbg !2034
  %267 = load i8*, i8** %e, align 8, !dbg !2036
  %add.ptr411 = getelementptr inbounds i8, i8* %267, i64 4, !dbg !2036
  store i8* %add.ptr411, i8** %e, align 8, !dbg !2036
  br label %if.end412, !dbg !2037

if.end412:                                        ; preds = %if.then408, %if.end405
  %268 = load i8*, i8** %e, align 8, !dbg !2038
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %268, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.38, i32 0, i32 0), i64 5, i32 1, i1 false), !dbg !2039
  %269 = load i8*, i8** %e, align 8, !dbg !2040
  %add.ptr413 = getelementptr inbounds i8, i8* %269, i64 5, !dbg !2040
  store i8* %add.ptr413, i8** %e, align 8, !dbg !2040
  %270 = load i8*, i8** %e, align 8, !dbg !2041
  %incdec.ptr414 = getelementptr inbounds i8, i8* %270, i32 1, !dbg !2041
  store i8* %incdec.ptr414, i8** %e, align 8, !dbg !2041
  store i8 4, i8* %270, align 1, !dbg !2042
  %271 = load i8*, i8** %e, align 8, !dbg !2043
  %272 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2044
  %call415 = call i64 @archive_entry_uid(%struct.archive_entry* %272), !dbg !2045
  %conv416 = trunc i64 %call415 to i32, !dbg !2046
  call void @archive_le32enc(i8* %271, i32 %conv416), !dbg !2047
  %273 = load i8*, i8** %e, align 8, !dbg !2048
  %add.ptr417 = getelementptr inbounds i8, i8* %273, i64 4, !dbg !2048
  store i8* %add.ptr417, i8** %e, align 8, !dbg !2048
  %274 = load i8*, i8** %e, align 8, !dbg !2049
  %incdec.ptr418 = getelementptr inbounds i8, i8* %274, i32 1, !dbg !2049
  store i8* %incdec.ptr418, i8** %e, align 8, !dbg !2049
  store i8 4, i8* %274, align 1, !dbg !2050
  %275 = load i8*, i8** %e, align 8, !dbg !2051
  %276 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2052
  %call419 = call i64 @archive_entry_gid(%struct.archive_entry* %276), !dbg !2053
  %conv420 = trunc i64 %call419 to i32, !dbg !2054
  call void @archive_le32enc(i8* %275, i32 %conv420), !dbg !2055
  %277 = load i8*, i8** %e, align 8, !dbg !2056
  %add.ptr421 = getelementptr inbounds i8, i8* %277, i64 4, !dbg !2056
  store i8* %add.ptr421, i8** %e, align 8, !dbg !2056
  %278 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2057
  %entry_flags422 = getelementptr inbounds %struct.zip, %struct.zip* %278, i32 0, i32 10, !dbg !2059
  %279 = load i32, i32* %entry_flags422, align 4, !dbg !2059
  %and423 = and i32 %279, 1, !dbg !2060
  %tobool424 = icmp ne i32 %and423, 0, !dbg !2060
  br i1 %tobool424, label %land.lhs.true425, label %if.end457, !dbg !2061

land.lhs.true425:                                 ; preds = %if.end412
  %280 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2062
  %entry_encryption426 = getelementptr inbounds %struct.zip, %struct.zip* %280, i32 0, i32 9, !dbg !2064
  %281 = load i32, i32* %entry_encryption426, align 8, !dbg !2064
  %cmp427 = icmp eq i32 %281, 2, !dbg !2065
  br i1 %cmp427, label %if.then433, label %lor.lhs.false429, !dbg !2066

lor.lhs.false429:                                 ; preds = %land.lhs.true425
  %282 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2067
  %entry_encryption430 = getelementptr inbounds %struct.zip, %struct.zip* %282, i32 0, i32 9, !dbg !2068
  %283 = load i32, i32* %entry_encryption430, align 8, !dbg !2068
  %cmp431 = icmp eq i32 %283, 3, !dbg !2069
  br i1 %cmp431, label %if.then433, label %if.end457, !dbg !2070

if.then433:                                       ; preds = %lor.lhs.false429, %land.lhs.true425
  %284 = load i8*, i8** %e, align 8, !dbg !2071
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %284, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.39, i32 0, i32 0), i64 8, i32 1, i1 false), !dbg !2073
  %285 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2074
  %entry434 = getelementptr inbounds %struct.zip, %struct.zip* %285, i32 0, i32 6, !dbg !2076
  %286 = load %struct.archive_entry*, %struct.archive_entry** %entry434, align 8, !dbg !2076
  %call435 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %286), !dbg !2077
  %tobool436 = icmp ne i32 %call435, 0, !dbg !2077
  br i1 %tobool436, label %land.lhs.true437, label %if.else444, !dbg !2078

land.lhs.true437:                                 ; preds = %if.then433
  %287 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2079
  %entry438 = getelementptr inbounds %struct.zip, %struct.zip* %287, i32 0, i32 6, !dbg !2081
  %288 = load %struct.archive_entry*, %struct.archive_entry** %entry438, align 8, !dbg !2081
  %call439 = call i64 @archive_entry_size(%struct.archive_entry* %288), !dbg !2082
  %cmp440 = icmp slt i64 %call439, 20, !dbg !2083
  br i1 %cmp440, label %if.then442, label %if.else444, !dbg !2084

if.then442:                                       ; preds = %land.lhs.true437
  %289 = load i8*, i8** %e, align 8, !dbg !2086
  %add.ptr443 = getelementptr inbounds i8, i8* %289, i64 4, !dbg !2088
  call void @archive_le16enc(i8* %add.ptr443, i16 zeroext 2), !dbg !2089
  %290 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2090
  %aes_vendor = getelementptr inbounds %struct.zip, %struct.zip* %290, i32 0, i32 16, !dbg !2091
  store i32 2, i32* %aes_vendor, align 8, !dbg !2092
  br label %if.end446, !dbg !2093

if.else444:                                       ; preds = %land.lhs.true437, %if.then433
  %291 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2094
  %aes_vendor445 = getelementptr inbounds %struct.zip, %struct.zip* %291, i32 0, i32 16, !dbg !2095
  store i32 1, i32* %aes_vendor445, align 8, !dbg !2096
  br label %if.end446

if.end446:                                        ; preds = %if.else444, %if.then442
  %292 = load i8*, i8** %e, align 8, !dbg !2097
  %add.ptr447 = getelementptr inbounds i8, i8* %292, i64 8, !dbg !2097
  store i8* %add.ptr447, i8** %e, align 8, !dbg !2097
  %293 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2098
  %entry_encryption448 = getelementptr inbounds %struct.zip, %struct.zip* %293, i32 0, i32 9, !dbg !2099
  %294 = load i32, i32* %entry_encryption448, align 8, !dbg !2099
  %cmp449 = icmp eq i32 %294, 2, !dbg !2100
  %cond451 = select i1 %cmp449, i32 1, i32 3, !dbg !2101
  %conv452 = trunc i32 %cond451 to i8, !dbg !2101
  %295 = load i8*, i8** %e, align 8, !dbg !2102
  %incdec.ptr453 = getelementptr inbounds i8, i8* %295, i32 1, !dbg !2102
  store i8* %incdec.ptr453, i8** %e, align 8, !dbg !2102
  store i8 %conv452, i8* %295, align 1, !dbg !2103
  %296 = load i8*, i8** %e, align 8, !dbg !2104
  %297 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2105
  %entry_compression454 = getelementptr inbounds %struct.zip, %struct.zip* %297, i32 0, i32 8, !dbg !2106
  %298 = load i32, i32* %entry_compression454, align 4, !dbg !2106
  %conv455 = trunc i32 %298 to i16, !dbg !2105
  call void @archive_le16enc(i8* %296, i16 zeroext %conv455), !dbg !2107
  %299 = load i8*, i8** %e, align 8, !dbg !2108
  %add.ptr456 = getelementptr inbounds i8, i8* %299, i64 2, !dbg !2108
  store i8* %add.ptr456, i8** %e, align 8, !dbg !2108
  br label %if.end457, !dbg !2109

if.end457:                                        ; preds = %if.end446, %lor.lhs.false429, %if.end412
  %300 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2110
  %central_directory_bytes = getelementptr inbounds %struct.zip, %struct.zip* %300, i32 0, i32 26, !dbg !2111
  %301 = load i64, i64* %central_directory_bytes, align 8, !dbg !2111
  %302 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2112
  %file_header_extra_offset = getelementptr inbounds %struct.zip, %struct.zip* %302, i32 0, i32 22, !dbg !2113
  store i64 %301, i64* %file_header_extra_offset, align 8, !dbg !2114
  %303 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2115
  %304 = load i8*, i8** %e, align 8, !dbg !2116
  %arraydecay458 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2117
  %sub.ptr.lhs.cast = ptrtoint i8* %304 to i64, !dbg !2118
  %sub.ptr.rhs.cast = ptrtoint i8* %arraydecay458 to i64, !dbg !2118
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2118
  %call459 = call i8* @cd_alloc(%struct.zip* %303, i64 %sub.ptr.sub), !dbg !2119
  store i8* %call459, i8** %cd_extra, align 8, !dbg !2120
  %305 = load i8*, i8** %cd_extra, align 8, !dbg !2121
  %arraydecay460 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2122
  %306 = load i8*, i8** %e, align 8, !dbg !2123
  %arraydecay461 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2124
  %sub.ptr.lhs.cast462 = ptrtoint i8* %306 to i64, !dbg !2125
  %sub.ptr.rhs.cast463 = ptrtoint i8* %arraydecay461 to i64, !dbg !2125
  %sub.ptr.sub464 = sub i64 %sub.ptr.lhs.cast462, %sub.ptr.rhs.cast463, !dbg !2125
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %305, i8* %arraydecay460, i64 %sub.ptr.sub464, i32 1, i1 false), !dbg !2122
  %307 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2126
  %entry_uses_zip64465 = getelementptr inbounds %struct.zip, %struct.zip* %307, i32 0, i32 11, !dbg !2128
  %308 = load i32, i32* %entry_uses_zip64465, align 8, !dbg !2128
  %tobool466 = icmp ne i32 %308, 0, !dbg !2126
  br i1 %tobool466, label %if.then467, label %if.end479, !dbg !2129

if.then467:                                       ; preds = %if.end457
  call void @llvm.dbg.declare(metadata i8** %zip64_start, metadata !2130, metadata !728), !dbg !2132
  %309 = load i8*, i8** %e, align 8, !dbg !2133
  store i8* %309, i8** %zip64_start, align 8, !dbg !2132
  %310 = load i8*, i8** %e, align 8, !dbg !2134
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %310, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.40, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !2135
  %311 = load i8*, i8** %e, align 8, !dbg !2136
  %add.ptr468 = getelementptr inbounds i8, i8* %311, i64 4, !dbg !2136
  store i8* %add.ptr468, i8** %e, align 8, !dbg !2136
  %312 = load i8*, i8** %e, align 8, !dbg !2137
  %313 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2138
  %entry_uncompressed_size469 = getelementptr inbounds %struct.zip, %struct.zip* %313, i32 0, i32 2, !dbg !2139
  %314 = load i64, i64* %entry_uncompressed_size469, align 8, !dbg !2139
  call void @archive_le64enc(i8* %312, i64 %314), !dbg !2140
  %315 = load i8*, i8** %e, align 8, !dbg !2141
  %add.ptr470 = getelementptr inbounds i8, i8* %315, i64 8, !dbg !2141
  store i8* %add.ptr470, i8** %e, align 8, !dbg !2141
  %316 = load i8*, i8** %e, align 8, !dbg !2142
  %317 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2143
  %entry_compressed_size471 = getelementptr inbounds %struct.zip, %struct.zip* %317, i32 0, i32 1, !dbg !2144
  %318 = load i64, i64* %entry_compressed_size471, align 8, !dbg !2144
  call void @archive_le64enc(i8* %316, i64 %318), !dbg !2145
  %319 = load i8*, i8** %e, align 8, !dbg !2146
  %add.ptr472 = getelementptr inbounds i8, i8* %319, i64 8, !dbg !2146
  store i8* %add.ptr472, i8** %e, align 8, !dbg !2146
  %320 = load i8*, i8** %zip64_start, align 8, !dbg !2147
  %add.ptr473 = getelementptr inbounds i8, i8* %320, i64 2, !dbg !2148
  %321 = load i8*, i8** %e, align 8, !dbg !2149
  %322 = load i8*, i8** %zip64_start, align 8, !dbg !2150
  %add.ptr474 = getelementptr inbounds i8, i8* %322, i64 4, !dbg !2151
  %sub.ptr.lhs.cast475 = ptrtoint i8* %321 to i64, !dbg !2152
  %sub.ptr.rhs.cast476 = ptrtoint i8* %add.ptr474 to i64, !dbg !2152
  %sub.ptr.sub477 = sub i64 %sub.ptr.lhs.cast475, %sub.ptr.rhs.cast476, !dbg !2152
  %conv478 = trunc i64 %sub.ptr.sub477 to i16, !dbg !2153
  call void @archive_le16enc(i8* %add.ptr473, i16 zeroext %conv478), !dbg !2154
  br label %if.end479, !dbg !2155

if.end479:                                        ; preds = %if.then467, %if.end457
  %323 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2156
  %flags480 = getelementptr inbounds %struct.zip, %struct.zip* %323, i32 0, i32 35, !dbg !2158
  %324 = load i32, i32* %flags480, align 8, !dbg !2158
  %and481 = and i32 %324, 4, !dbg !2159
  %tobool482 = icmp ne i32 %and481, 0, !dbg !2159
  br i1 %tobool482, label %if.then483, label %if.end518, !dbg !2160

if.then483:                                       ; preds = %if.end479
  call void @llvm.dbg.declare(metadata i8** %external_info, metadata !2161, metadata !728), !dbg !2163
  %325 = load i8*, i8** %e, align 8, !dbg !2164
  store i8* %325, i8** %external_info, align 8, !dbg !2163
  call void @llvm.dbg.declare(metadata i32* %included, metadata !2165, metadata !728), !dbg !2166
  store i32 7, i32* %included, align 4, !dbg !2166
  %326 = load i8*, i8** %e, align 8, !dbg !2167
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %326, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.41, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !2168
  %327 = load i8*, i8** %e, align 8, !dbg !2169
  %add.ptr484 = getelementptr inbounds i8, i8* %327, i64 4, !dbg !2169
  store i8* %add.ptr484, i8** %e, align 8, !dbg !2169
  %328 = load i32, i32* %included, align 4, !dbg !2170
  %conv485 = trunc i32 %328 to i8, !dbg !2170
  %329 = load i8*, i8** %e, align 8, !dbg !2171
  %arrayidx486 = getelementptr inbounds i8, i8* %329, i64 0, !dbg !2171
  store i8 %conv485, i8* %arrayidx486, align 1, !dbg !2172
  %330 = load i8*, i8** %e, align 8, !dbg !2173
  %add.ptr487 = getelementptr inbounds i8, i8* %330, i64 1, !dbg !2173
  store i8* %add.ptr487, i8** %e, align 8, !dbg !2173
  %331 = load i32, i32* %included, align 4, !dbg !2174
  %and488 = and i32 %331, 1, !dbg !2176
  %tobool489 = icmp ne i32 %and488, 0, !dbg !2176
  br i1 %tobool489, label %if.then490, label %if.end494, !dbg !2177

if.then490:                                       ; preds = %if.then483
  %332 = load i8*, i8** %e, align 8, !dbg !2178
  %333 = load i32, i32* %version_needed, align 4, !dbg !2180
  %add491 = add nsw i32 768, %333, !dbg !2181
  %conv492 = trunc i32 %add491 to i16, !dbg !2182
  call void @archive_le16enc(i8* %332, i16 zeroext %conv492), !dbg !2183
  %334 = load i8*, i8** %e, align 8, !dbg !2184
  %add.ptr493 = getelementptr inbounds i8, i8* %334, i64 2, !dbg !2184
  store i8* %add.ptr493, i8** %e, align 8, !dbg !2184
  br label %if.end494, !dbg !2185

if.end494:                                        ; preds = %if.then490, %if.then483
  %335 = load i32, i32* %included, align 4, !dbg !2186
  %and495 = and i32 %335, 2, !dbg !2188
  %tobool496 = icmp ne i32 %and495, 0, !dbg !2188
  br i1 %tobool496, label %if.then497, label %if.end499, !dbg !2189

if.then497:                                       ; preds = %if.end494
  %336 = load i8*, i8** %e, align 8, !dbg !2190
  call void @archive_le16enc(i8* %336, i16 zeroext 0), !dbg !2192
  %337 = load i8*, i8** %e, align 8, !dbg !2193
  %add.ptr498 = getelementptr inbounds i8, i8* %337, i64 2, !dbg !2193
  store i8* %add.ptr498, i8** %e, align 8, !dbg !2193
  br label %if.end499, !dbg !2194

if.end499:                                        ; preds = %if.then497, %if.end494
  %338 = load i32, i32* %included, align 4, !dbg !2195
  %and500 = and i32 %338, 4, !dbg !2197
  %tobool501 = icmp ne i32 %and500, 0, !dbg !2197
  br i1 %tobool501, label %if.then502, label %if.end507, !dbg !2198

if.then502:                                       ; preds = %if.end499
  %339 = load i8*, i8** %e, align 8, !dbg !2199
  %340 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2201
  %entry503 = getelementptr inbounds %struct.zip, %struct.zip* %340, i32 0, i32 6, !dbg !2202
  %341 = load %struct.archive_entry*, %struct.archive_entry** %entry503, align 8, !dbg !2202
  %call504 = call i32 @archive_entry_mode(%struct.archive_entry* %341), !dbg !2203
  %shl505 = shl i32 %call504, 16, !dbg !2204
  call void @archive_le32enc(i8* %339, i32 %shl505), !dbg !2205
  %342 = load i8*, i8** %e, align 8, !dbg !2206
  %add.ptr506 = getelementptr inbounds i8, i8* %342, i64 4, !dbg !2206
  store i8* %add.ptr506, i8** %e, align 8, !dbg !2206
  br label %if.end507, !dbg !2207

if.end507:                                        ; preds = %if.then502, %if.end499
  %343 = load i32, i32* %included, align 4, !dbg !2208
  %and508 = and i32 %343, 8, !dbg !2210
  %tobool509 = icmp ne i32 %and508, 0, !dbg !2210
  br i1 %tobool509, label %if.then510, label %if.end511, !dbg !2211

if.then510:                                       ; preds = %if.end507
  br label %if.end511, !dbg !2212

if.end511:                                        ; preds = %if.then510, %if.end507
  %344 = load i8*, i8** %external_info, align 8, !dbg !2214
  %add.ptr512 = getelementptr inbounds i8, i8* %344, i64 2, !dbg !2215
  %345 = load i8*, i8** %e, align 8, !dbg !2216
  %346 = load i8*, i8** %external_info, align 8, !dbg !2217
  %add.ptr513 = getelementptr inbounds i8, i8* %346, i64 4, !dbg !2218
  %sub.ptr.lhs.cast514 = ptrtoint i8* %345 to i64, !dbg !2219
  %sub.ptr.rhs.cast515 = ptrtoint i8* %add.ptr513 to i64, !dbg !2219
  %sub.ptr.sub516 = sub i64 %sub.ptr.lhs.cast514, %sub.ptr.rhs.cast515, !dbg !2219
  %conv517 = trunc i64 %sub.ptr.sub516 to i16, !dbg !2220
  call void @archive_le16enc(i8* %add.ptr512, i16 zeroext %conv517), !dbg !2221
  br label %if.end518, !dbg !2222

if.end518:                                        ; preds = %if.end511, %if.end479
  %arraydecay519 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !2223
  %add.ptr520 = getelementptr inbounds i8, i8* %arraydecay519, i64 28, !dbg !2224
  %347 = load i8*, i8** %e, align 8, !dbg !2225
  %arraydecay521 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2226
  %sub.ptr.lhs.cast522 = ptrtoint i8* %347 to i64, !dbg !2227
  %sub.ptr.rhs.cast523 = ptrtoint i8* %arraydecay521 to i64, !dbg !2227
  %sub.ptr.sub524 = sub i64 %sub.ptr.lhs.cast522, %sub.ptr.rhs.cast523, !dbg !2227
  %conv525 = trunc i64 %sub.ptr.sub524 to i16, !dbg !2228
  call void @archive_le16enc(i8* %add.ptr520, i16 zeroext %conv525), !dbg !2229
  %348 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2230
  %arraydecay526 = getelementptr inbounds [32 x i8], [32 x i8]* %local_header, i32 0, i32 0, !dbg !2231
  %call527 = call i32 @__archive_write_output(%struct.archive_write* %348, i8* %arraydecay526, i64 30), !dbg !2232
  store i32 %call527, i32* %ret, align 4, !dbg !2233
  %349 = load i32, i32* %ret, align 4, !dbg !2234
  %cmp528 = icmp ne i32 %349, 0, !dbg !2236
  br i1 %cmp528, label %if.then530, label %if.end531, !dbg !2237

if.then530:                                       ; preds = %if.end518
  store i32 -30, i32* %retval, align 4, !dbg !2238
  br label %return, !dbg !2238

if.end531:                                        ; preds = %if.end518
  %350 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2239
  %written_bytes532 = getelementptr inbounds %struct.zip, %struct.zip* %350, i32 0, i32 28, !dbg !2240
  %351 = load i64, i64* %written_bytes532, align 8, !dbg !2241
  %add533 = add nsw i64 %351, 30, !dbg !2241
  store i64 %add533, i64* %written_bytes532, align 8, !dbg !2241
  %352 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2242
  %entry534 = getelementptr inbounds %struct.zip, %struct.zip* %352, i32 0, i32 6, !dbg !2243
  %353 = load %struct.archive_entry*, %struct.archive_entry** %entry534, align 8, !dbg !2243
  %354 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2244
  %call535 = call i32 @write_path(%struct.archive_entry* %353, %struct.archive_write* %354), !dbg !2245
  store i32 %call535, i32* %ret, align 4, !dbg !2246
  %355 = load i32, i32* %ret, align 4, !dbg !2247
  %cmp536 = icmp sle i32 %355, 0, !dbg !2249
  br i1 %cmp536, label %if.then538, label %if.end539, !dbg !2250

if.then538:                                       ; preds = %if.end531
  store i32 -30, i32* %retval, align 4, !dbg !2251
  br label %return, !dbg !2251

if.end539:                                        ; preds = %if.end531
  %356 = load i32, i32* %ret, align 4, !dbg !2252
  %conv540 = sext i32 %356 to i64, !dbg !2252
  %357 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2253
  %written_bytes541 = getelementptr inbounds %struct.zip, %struct.zip* %357, i32 0, i32 28, !dbg !2254
  %358 = load i64, i64* %written_bytes541, align 8, !dbg !2255
  %add542 = add nsw i64 %358, %conv540, !dbg !2255
  store i64 %add542, i64* %written_bytes541, align 8, !dbg !2255
  %359 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2256
  %arraydecay543 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2257
  %360 = load i8*, i8** %e, align 8, !dbg !2258
  %arraydecay544 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2259
  %sub.ptr.lhs.cast545 = ptrtoint i8* %360 to i64, !dbg !2260
  %sub.ptr.rhs.cast546 = ptrtoint i8* %arraydecay544 to i64, !dbg !2260
  %sub.ptr.sub547 = sub i64 %sub.ptr.lhs.cast545, %sub.ptr.rhs.cast546, !dbg !2260
  %call548 = call i32 @__archive_write_output(%struct.archive_write* %359, i8* %arraydecay543, i64 %sub.ptr.sub547), !dbg !2261
  store i32 %call548, i32* %ret, align 4, !dbg !2262
  %361 = load i32, i32* %ret, align 4, !dbg !2263
  %cmp549 = icmp ne i32 %361, 0, !dbg !2265
  br i1 %cmp549, label %if.then551, label %if.end552, !dbg !2266

if.then551:                                       ; preds = %if.end539
  store i32 -30, i32* %retval, align 4, !dbg !2267
  br label %return, !dbg !2267

if.end552:                                        ; preds = %if.end539
  %362 = load i8*, i8** %e, align 8, !dbg !2268
  %arraydecay553 = getelementptr inbounds [144 x i8], [144 x i8]* %local_extra, i32 0, i32 0, !dbg !2269
  %sub.ptr.lhs.cast554 = ptrtoint i8* %362 to i64, !dbg !2270
  %sub.ptr.rhs.cast555 = ptrtoint i8* %arraydecay553 to i64, !dbg !2270
  %sub.ptr.sub556 = sub i64 %sub.ptr.lhs.cast554, %sub.ptr.rhs.cast555, !dbg !2270
  %363 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2271
  %written_bytes557 = getelementptr inbounds %struct.zip, %struct.zip* %363, i32 0, i32 28, !dbg !2272
  %364 = load i64, i64* %written_bytes557, align 8, !dbg !2273
  %add558 = add nsw i64 %364, %sub.ptr.sub556, !dbg !2273
  store i64 %add558, i64* %written_bytes557, align 8, !dbg !2273
  %365 = load i8*, i8** %slink, align 8, !dbg !2274
  %cmp559 = icmp ne i8* %365, null, !dbg !2276
  br i1 %cmp559, label %if.then561, label %if.end573, !dbg !2277

if.then561:                                       ; preds = %if.end552
  %366 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2278
  %367 = load i8*, i8** %slink, align 8, !dbg !2280
  %368 = load i64, i64* %slink_size, align 8, !dbg !2281
  %call562 = call i32 @__archive_write_output(%struct.archive_write* %366, i8* %367, i64 %368), !dbg !2282
  store i32 %call562, i32* %ret, align 4, !dbg !2283
  %369 = load i32, i32* %ret, align 4, !dbg !2284
  %cmp563 = icmp ne i32 %369, 0, !dbg !2286
  br i1 %cmp563, label %if.then565, label %if.end566, !dbg !2287

if.then565:                                       ; preds = %if.then561
  store i32 -30, i32* %retval, align 4, !dbg !2288
  br label %return, !dbg !2288

if.end566:                                        ; preds = %if.then561
  %370 = load i64, i64* %slink_size, align 8, !dbg !2289
  %371 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2290
  %entry_compressed_written567 = getelementptr inbounds %struct.zip, %struct.zip* %371, i32 0, i32 3, !dbg !2291
  %372 = load i64, i64* %entry_compressed_written567, align 8, !dbg !2292
  %add568 = add i64 %372, %370, !dbg !2292
  store i64 %add568, i64* %entry_compressed_written567, align 8, !dbg !2292
  %373 = load i64, i64* %slink_size, align 8, !dbg !2293
  %374 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2294
  %entry_uncompressed_written569 = getelementptr inbounds %struct.zip, %struct.zip* %374, i32 0, i32 4, !dbg !2295
  %375 = load i64, i64* %entry_uncompressed_written569, align 8, !dbg !2296
  %add570 = add i64 %375, %373, !dbg !2296
  store i64 %add570, i64* %entry_uncompressed_written569, align 8, !dbg !2296
  %376 = load i64, i64* %slink_size, align 8, !dbg !2297
  %377 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2298
  %written_bytes571 = getelementptr inbounds %struct.zip, %struct.zip* %377, i32 0, i32 28, !dbg !2299
  %378 = load i64, i64* %written_bytes571, align 8, !dbg !2300
  %add572 = add i64 %378, %376, !dbg !2300
  store i64 %add572, i64* %written_bytes571, align 8, !dbg !2300
  br label %if.end573, !dbg !2301

if.end573:                                        ; preds = %if.end566, %if.end552
  %379 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2302
  %entry_compression574 = getelementptr inbounds %struct.zip, %struct.zip* %379, i32 0, i32 8, !dbg !2304
  %380 = load i32, i32* %entry_compression574, align 4, !dbg !2304
  %cmp575 = icmp eq i32 %380, 8, !dbg !2305
  br i1 %cmp575, label %if.then577, label %if.end590, !dbg !2306

if.then577:                                       ; preds = %if.end573
  %381 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2307
  %stream = getelementptr inbounds %struct.zip, %struct.zip* %381, i32 0, i32 36, !dbg !2309
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 8, !dbg !2310
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !2311
  %382 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2312
  %stream578 = getelementptr inbounds %struct.zip, %struct.zip* %382, i32 0, i32 36, !dbg !2313
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream578, i32 0, i32 9, !dbg !2314
  store void (i8*, i8*)* null, void (i8*, i8*)** %zfree, align 8, !dbg !2315
  %383 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2316
  %stream579 = getelementptr inbounds %struct.zip, %struct.zip* %383, i32 0, i32 36, !dbg !2317
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream579, i32 0, i32 10, !dbg !2318
  store i8* null, i8** %opaque, align 8, !dbg !2319
  %384 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2320
  %buf = getelementptr inbounds %struct.zip, %struct.zip* %384, i32 0, i32 38, !dbg !2321
  %385 = load i8*, i8** %buf, align 8, !dbg !2321
  %386 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2322
  %stream580 = getelementptr inbounds %struct.zip, %struct.zip* %386, i32 0, i32 36, !dbg !2323
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream580, i32 0, i32 3, !dbg !2324
  store i8* %385, i8** %next_out, align 8, !dbg !2325
  %387 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2326
  %len_buf = getelementptr inbounds %struct.zip, %struct.zip* %387, i32 0, i32 37, !dbg !2327
  %388 = load i64, i64* %len_buf, align 8, !dbg !2327
  %conv581 = trunc i64 %388 to i32, !dbg !2328
  %389 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2329
  %stream582 = getelementptr inbounds %struct.zip, %struct.zip* %389, i32 0, i32 36, !dbg !2330
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream582, i32 0, i32 4, !dbg !2331
  store i32 %conv581, i32* %avail_out, align 8, !dbg !2332
  %390 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2333
  %stream583 = getelementptr inbounds %struct.zip, %struct.zip* %390, i32 0, i32 36, !dbg !2333
  %391 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2333
  %deflate_compression_level = getelementptr inbounds %struct.zip, %struct.zip* %391, i32 0, i32 32, !dbg !2333
  %392 = load i32, i32* %deflate_compression_level, align 4, !dbg !2333
  %call584 = call i32 @cm_zlib_deflateInit2_(%struct.z_stream_s* %stream583, i32 %392, i32 8, i32 -15, i32 8, i32 0, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.42, i32 0, i32 0), i32 112), !dbg !2333
  %cmp585 = icmp ne i32 %call584, 0, !dbg !2335
  br i1 %cmp585, label %if.then587, label %if.end589, !dbg !2336

if.then587:                                       ; preds = %if.then577
  %393 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2337
  %archive588 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %393, i32 0, i32 0, !dbg !2339
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive588, i32 12, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.43, i32 0, i32 0)), !dbg !2340
  store i32 -30, i32* %retval, align 4, !dbg !2341
  br label %return, !dbg !2341

if.end589:                                        ; preds = %if.then577
  br label %if.end590, !dbg !2342

if.end590:                                        ; preds = %if.end589, %if.end573
  %394 = load i32, i32* %ret2, align 4, !dbg !2343
  store i32 %394, i32* %retval, align 4, !dbg !2344
  br label %return, !dbg !2344

return:                                           ; preds = %if.end590, %if.then587, %if.then565, %if.then551, %if.then538, %if.then530, %if.then93, %if.then72, %if.then59, %if.then16, %if.then12, %if.then
  %395 = load i32, i32* %retval, align 4, !dbg !2345
  ret i32 %395, !dbg !2345
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_zip_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !701 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %ret = alloca i32, align 4
  %zip = alloca %struct.zip*, align 8
  %rb = alloca i8*, align 8
  %re = alloca i8*, align 8
  %l = alloca i64, align 8
  %outl = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2346, metadata !728), !dbg !2347
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !2348, metadata !728), !dbg !2349
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !2350, metadata !728), !dbg !2351
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2352, metadata !728), !dbg !2353
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !2354, metadata !728), !dbg !2355
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2356
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2357
  %1 = load i8*, i8** %format_data, align 8, !dbg !2357
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !2356
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !2355
  %3 = load i64, i64* %s.addr, align 8, !dbg !2358
  %4 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2360
  %entry_uncompressed_limit = getelementptr inbounds %struct.zip, %struct.zip* %4, i32 0, i32 5, !dbg !2361
  %5 = load i64, i64* %entry_uncompressed_limit, align 8, !dbg !2361
  %cmp = icmp sgt i64 %3, %5, !dbg !2362
  br i1 %cmp, label %if.then, label %if.end, !dbg !2363

if.then:                                          ; preds = %entry
  %6 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2364
  %entry_uncompressed_limit1 = getelementptr inbounds %struct.zip, %struct.zip* %6, i32 0, i32 5, !dbg !2365
  %7 = load i64, i64* %entry_uncompressed_limit1, align 8, !dbg !2365
  store i64 %7, i64* %s.addr, align 8, !dbg !2366
  br label %if.end, !dbg !2367

if.end:                                           ; preds = %if.then, %entry
  %8 = load i64, i64* %s.addr, align 8, !dbg !2368
  %9 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2369
  %entry_uncompressed_written = getelementptr inbounds %struct.zip, %struct.zip* %9, i32 0, i32 4, !dbg !2370
  %10 = load i64, i64* %entry_uncompressed_written, align 8, !dbg !2371
  %add = add i64 %10, %8, !dbg !2371
  store i64 %add, i64* %entry_uncompressed_written, align 8, !dbg !2371
  %11 = load i64, i64* %s.addr, align 8, !dbg !2372
  %cmp2 = icmp eq i64 %11, 0, !dbg !2374
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2375

if.then3:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !2376
  br label %return, !dbg !2376

if.end4:                                          ; preds = %if.end
  %12 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2378
  %entry_flags = getelementptr inbounds %struct.zip, %struct.zip* %12, i32 0, i32 10, !dbg !2380
  %13 = load i32, i32* %entry_flags, align 4, !dbg !2380
  %and = and i32 %13, 1, !dbg !2381
  %tobool = icmp ne i32 %and, 0, !dbg !2381
  br i1 %tobool, label %if.then5, label %if.end24, !dbg !2382

if.then5:                                         ; preds = %if.end4
  %14 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2383
  %entry_encryption = getelementptr inbounds %struct.zip, %struct.zip* %14, i32 0, i32 9, !dbg !2385
  %15 = load i32, i32* %entry_encryption, align 8, !dbg !2385
  switch i32 %15, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb13
    i32 3, label %sw.bb13
  ], !dbg !2386

sw.bb:                                            ; preds = %if.then5
  %16 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2387
  %tctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %16, i32 0, i32 14, !dbg !2390
  %17 = load i8, i8* %tctx_valid, align 4, !dbg !2390
  %tobool6 = icmp ne i8 %17, 0, !dbg !2387
  br i1 %tobool6, label %if.end12, label %if.then7, !dbg !2391

if.then7:                                         ; preds = %sw.bb
  %18 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2392
  %call = call i32 @init_traditional_pkware_encryption(%struct.archive_write* %18), !dbg !2394
  store i32 %call, i32* %ret, align 4, !dbg !2395
  %19 = load i32, i32* %ret, align 4, !dbg !2396
  %cmp8 = icmp ne i32 %19, 0, !dbg !2398
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !2399

if.then9:                                         ; preds = %if.then7
  %20 = load i32, i32* %ret, align 4, !dbg !2400
  %conv = sext i32 %20 to i64, !dbg !2401
  store i64 %conv, i64* %retval, align 8, !dbg !2402
  br label %return, !dbg !2402

if.end10:                                         ; preds = %if.then7
  %21 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2403
  %tctx_valid11 = getelementptr inbounds %struct.zip, %struct.zip* %21, i32 0, i32 14, !dbg !2404
  store i8 1, i8* %tctx_valid11, align 4, !dbg !2405
  br label %if.end12, !dbg !2406

if.end12:                                         ; preds = %if.end10, %sw.bb
  br label %sw.epilog, !dbg !2407

sw.bb13:                                          ; preds = %if.then5, %if.then5
  %22 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2408
  %cctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %22, i32 0, i32 18, !dbg !2410
  %23 = load i8, i8* %cctx_valid, align 8, !dbg !2410
  %tobool14 = icmp ne i8 %23, 0, !dbg !2408
  br i1 %tobool14, label %if.end23, label %if.then15, !dbg !2411

if.then15:                                        ; preds = %sw.bb13
  %24 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2412
  %call16 = call i32 @init_winzip_aes_encryption(%struct.archive_write* %24), !dbg !2414
  store i32 %call16, i32* %ret, align 4, !dbg !2415
  %25 = load i32, i32* %ret, align 4, !dbg !2416
  %cmp17 = icmp ne i32 %25, 0, !dbg !2418
  br i1 %cmp17, label %if.then19, label %if.end21, !dbg !2419

if.then19:                                        ; preds = %if.then15
  %26 = load i32, i32* %ret, align 4, !dbg !2420
  %conv20 = sext i32 %26 to i64, !dbg !2421
  store i64 %conv20, i64* %retval, align 8, !dbg !2422
  br label %return, !dbg !2422

if.end21:                                         ; preds = %if.then15
  %27 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2423
  %hctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %27, i32 0, i32 20, !dbg !2424
  store i8 1, i8* %hctx_valid, align 8, !dbg !2425
  %28 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2426
  %cctx_valid22 = getelementptr inbounds %struct.zip, %struct.zip* %28, i32 0, i32 18, !dbg !2427
  store i8 1, i8* %cctx_valid22, align 8, !dbg !2428
  br label %if.end23, !dbg !2429

if.end23:                                         ; preds = %if.end21, %sw.bb13
  br label %sw.epilog, !dbg !2430

sw.default:                                       ; preds = %if.then5
  br label %sw.epilog, !dbg !2431

sw.epilog:                                        ; preds = %sw.default, %if.end23, %if.end12
  br label %if.end24, !dbg !2432

if.end24:                                         ; preds = %sw.epilog, %if.end4
  %29 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2433
  %entry_compression = getelementptr inbounds %struct.zip, %struct.zip* %29, i32 0, i32 8, !dbg !2434
  %30 = load i32, i32* %entry_compression, align 4, !dbg !2434
  switch i32 %30, label %sw.default141 [
    i32 0, label %sw.bb25
    i32 8, label %sw.bb74
  ], !dbg !2435

sw.bb25:                                          ; preds = %if.end24
  %31 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2436
  %tctx_valid26 = getelementptr inbounds %struct.zip, %struct.zip* %31, i32 0, i32 14, !dbg !2439
  %32 = load i8, i8* %tctx_valid26, align 4, !dbg !2439
  %conv27 = sext i8 %32 to i32, !dbg !2436
  %tobool28 = icmp ne i32 %conv27, 0, !dbg !2436
  br i1 %tobool28, label %if.then32, label %lor.lhs.false, !dbg !2440

lor.lhs.false:                                    ; preds = %sw.bb25
  %33 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2441
  %cctx_valid29 = getelementptr inbounds %struct.zip, %struct.zip* %33, i32 0, i32 18, !dbg !2443
  %34 = load i8, i8* %cctx_valid29, align 8, !dbg !2443
  %conv30 = sext i8 %34 to i32, !dbg !2441
  %tobool31 = icmp ne i32 %conv30, 0, !dbg !2441
  br i1 %tobool31, label %if.then32, label %if.else62, !dbg !2444

if.then32:                                        ; preds = %lor.lhs.false, %sw.bb25
  call void @llvm.dbg.declare(metadata i8** %rb, metadata !2445, metadata !728), !dbg !2447
  %35 = load i8*, i8** %buff.addr, align 8, !dbg !2448
  store i8* %35, i8** %rb, align 8, !dbg !2447
  call void @llvm.dbg.declare(metadata i8** %re, metadata !2449, metadata !728), !dbg !2451
  %36 = load i8*, i8** %rb, align 8, !dbg !2452
  %37 = load i64, i64* %s.addr, align 8, !dbg !2453
  %add.ptr = getelementptr inbounds i8, i8* %36, i64 %37, !dbg !2454
  store i8* %add.ptr, i8** %re, align 8, !dbg !2451
  br label %while.cond, !dbg !2455

while.cond:                                       ; preds = %if.end58, %if.then32
  %38 = load i8*, i8** %rb, align 8, !dbg !2456
  %39 = load i8*, i8** %re, align 8, !dbg !2458
  %cmp33 = icmp ult i8* %38, %39, !dbg !2459
  br i1 %cmp33, label %while.body, label %while.end, !dbg !2460

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %l, metadata !2461, metadata !728), !dbg !2463
  %40 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2464
  %tctx_valid35 = getelementptr inbounds %struct.zip, %struct.zip* %40, i32 0, i32 14, !dbg !2466
  %41 = load i8, i8* %tctx_valid35, align 4, !dbg !2466
  %tobool36 = icmp ne i8 %41, 0, !dbg !2464
  br i1 %tobool36, label %if.then37, label %if.else, !dbg !2467

if.then37:                                        ; preds = %while.body
  %42 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2468
  %tctx = getelementptr inbounds %struct.zip, %struct.zip* %42, i32 0, i32 13, !dbg !2470
  %43 = load i8*, i8** %rb, align 8, !dbg !2471
  %44 = load i8*, i8** %re, align 8, !dbg !2472
  %45 = load i8*, i8** %rb, align 8, !dbg !2473
  %sub.ptr.lhs.cast = ptrtoint i8* %44 to i64, !dbg !2474
  %sub.ptr.rhs.cast = ptrtoint i8* %45 to i64, !dbg !2474
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2474
  %46 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2475
  %buf = getelementptr inbounds %struct.zip, %struct.zip* %46, i32 0, i32 38, !dbg !2476
  %47 = load i8*, i8** %buf, align 8, !dbg !2476
  %48 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2477
  %len_buf = getelementptr inbounds %struct.zip, %struct.zip* %48, i32 0, i32 37, !dbg !2478
  %49 = load i64, i64* %len_buf, align 8, !dbg !2478
  %call38 = call i32 @trad_enc_encrypt_update(%struct.trad_enc_ctx* %tctx, i8* %43, i64 %sub.ptr.sub, i8* %47, i64 %49), !dbg !2479
  %conv39 = zext i32 %call38 to i64, !dbg !2479
  store i64 %conv39, i64* %l, align 8, !dbg !2480
  br label %if.end51, !dbg !2481

if.else:                                          ; preds = %while.body
  %50 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2482
  %len_buf40 = getelementptr inbounds %struct.zip, %struct.zip* %50, i32 0, i32 37, !dbg !2484
  %51 = load i64, i64* %len_buf40, align 8, !dbg !2484
  store i64 %51, i64* %l, align 8, !dbg !2485
  %52 = load i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*, i8*, i64, i8*, i64*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 5), align 8, !dbg !2486
  %53 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2486
  %cctx = getelementptr inbounds %struct.zip, %struct.zip* %53, i32 0, i32 17, !dbg !2486
  %54 = load i8*, i8** %rb, align 8, !dbg !2486
  %55 = load i8*, i8** %re, align 8, !dbg !2486
  %56 = load i8*, i8** %rb, align 8, !dbg !2486
  %sub.ptr.lhs.cast41 = ptrtoint i8* %55 to i64, !dbg !2486
  %sub.ptr.rhs.cast42 = ptrtoint i8* %56 to i64, !dbg !2486
  %sub.ptr.sub43 = sub i64 %sub.ptr.lhs.cast41, %sub.ptr.rhs.cast42, !dbg !2486
  %57 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2486
  %buf44 = getelementptr inbounds %struct.zip, %struct.zip* %57, i32 0, i32 38, !dbg !2486
  %58 = load i8*, i8** %buf44, align 8, !dbg !2486
  %call45 = call i32 %52(i32* %cctx, i8* %54, i64 %sub.ptr.sub43, i8* %58, i64* %l), !dbg !2486
  store i32 %call45, i32* %ret, align 4, !dbg !2487
  %59 = load i32, i32* %ret, align 4, !dbg !2488
  %cmp46 = icmp slt i32 %59, 0, !dbg !2490
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !2491

if.then48:                                        ; preds = %if.else
  %60 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2492
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %60, i32 0, i32 0, !dbg !2494
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.45, i32 0, i32 0)), !dbg !2495
  store i64 -25, i64* %retval, align 8, !dbg !2496
  br label %return, !dbg !2496

if.end49:                                         ; preds = %if.else
  %61 = load void (i32*, i8*, i64)*, void (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 1), align 8, !dbg !2497
  %62 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2497
  %hctx = getelementptr inbounds %struct.zip, %struct.zip* %62, i32 0, i32 19, !dbg !2497
  %63 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2497
  %buf50 = getelementptr inbounds %struct.zip, %struct.zip* %63, i32 0, i32 38, !dbg !2497
  %64 = load i8*, i8** %buf50, align 8, !dbg !2497
  %65 = load i64, i64* %l, align 8, !dbg !2497
  call void %61(i32* %hctx, i8* %64, i64 %65), !dbg !2497
  br label %if.end51

if.end51:                                         ; preds = %if.end49, %if.then37
  %66 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2498
  %67 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2499
  %buf52 = getelementptr inbounds %struct.zip, %struct.zip* %67, i32 0, i32 38, !dbg !2500
  %68 = load i8*, i8** %buf52, align 8, !dbg !2500
  %69 = load i64, i64* %l, align 8, !dbg !2501
  %call53 = call i32 @__archive_write_output(%struct.archive_write* %66, i8* %68, i64 %69), !dbg !2502
  store i32 %call53, i32* %ret, align 4, !dbg !2503
  %70 = load i32, i32* %ret, align 4, !dbg !2504
  %cmp54 = icmp ne i32 %70, 0, !dbg !2506
  br i1 %cmp54, label %if.then56, label %if.end58, !dbg !2507

if.then56:                                        ; preds = %if.end51
  %71 = load i32, i32* %ret, align 4, !dbg !2508
  %conv57 = sext i32 %71 to i64, !dbg !2509
  store i64 %conv57, i64* %retval, align 8, !dbg !2510
  br label %return, !dbg !2510

if.end58:                                         ; preds = %if.end51
  %72 = load i64, i64* %l, align 8, !dbg !2511
  %73 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2512
  %entry_compressed_written = getelementptr inbounds %struct.zip, %struct.zip* %73, i32 0, i32 3, !dbg !2513
  %74 = load i64, i64* %entry_compressed_written, align 8, !dbg !2514
  %add59 = add i64 %74, %72, !dbg !2514
  store i64 %add59, i64* %entry_compressed_written, align 8, !dbg !2514
  %75 = load i64, i64* %l, align 8, !dbg !2515
  %76 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2516
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %76, i32 0, i32 28, !dbg !2517
  %77 = load i64, i64* %written_bytes, align 8, !dbg !2518
  %add60 = add i64 %77, %75, !dbg !2518
  store i64 %add60, i64* %written_bytes, align 8, !dbg !2518
  %78 = load i64, i64* %l, align 8, !dbg !2519
  %79 = load i8*, i8** %rb, align 8, !dbg !2520
  %add.ptr61 = getelementptr inbounds i8, i8* %79, i64 %78, !dbg !2520
  store i8* %add.ptr61, i8** %rb, align 8, !dbg !2520
  br label %while.cond, !dbg !2521

while.end:                                        ; preds = %while.cond
  br label %if.end73, !dbg !2523

if.else62:                                        ; preds = %lor.lhs.false
  %80 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2524
  %81 = load i8*, i8** %buff.addr, align 8, !dbg !2526
  %82 = load i64, i64* %s.addr, align 8, !dbg !2527
  %call63 = call i32 @__archive_write_output(%struct.archive_write* %80, i8* %81, i64 %82), !dbg !2528
  store i32 %call63, i32* %ret, align 4, !dbg !2529
  %83 = load i32, i32* %ret, align 4, !dbg !2530
  %cmp64 = icmp ne i32 %83, 0, !dbg !2532
  br i1 %cmp64, label %if.then66, label %if.end68, !dbg !2533

if.then66:                                        ; preds = %if.else62
  %84 = load i32, i32* %ret, align 4, !dbg !2534
  %conv67 = sext i32 %84 to i64, !dbg !2535
  store i64 %conv67, i64* %retval, align 8, !dbg !2536
  br label %return, !dbg !2536

if.end68:                                         ; preds = %if.else62
  %85 = load i64, i64* %s.addr, align 8, !dbg !2537
  %86 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2538
  %written_bytes69 = getelementptr inbounds %struct.zip, %struct.zip* %86, i32 0, i32 28, !dbg !2539
  %87 = load i64, i64* %written_bytes69, align 8, !dbg !2540
  %add70 = add i64 %87, %85, !dbg !2540
  store i64 %add70, i64* %written_bytes69, align 8, !dbg !2540
  %88 = load i64, i64* %s.addr, align 8, !dbg !2541
  %89 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2542
  %entry_compressed_written71 = getelementptr inbounds %struct.zip, %struct.zip* %89, i32 0, i32 3, !dbg !2543
  %90 = load i64, i64* %entry_compressed_written71, align 8, !dbg !2544
  %add72 = add i64 %90, %88, !dbg !2544
  store i64 %add72, i64* %entry_compressed_written71, align 8, !dbg !2544
  br label %if.end73

if.end73:                                         ; preds = %if.end68, %while.end
  br label %sw.epilog143, !dbg !2545

sw.bb74:                                          ; preds = %if.end24
  %91 = load i8*, i8** %buff.addr, align 8, !dbg !2546
  %92 = ptrtoint i8* %91 to i64, !dbg !2547
  %93 = inttoptr i64 %92 to i8*, !dbg !2548
  %94 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2549
  %stream = getelementptr inbounds %struct.zip, %struct.zip* %94, i32 0, i32 36, !dbg !2550
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 0, !dbg !2551
  store i8* %93, i8** %next_in, align 8, !dbg !2552
  %95 = load i64, i64* %s.addr, align 8, !dbg !2553
  %conv75 = trunc i64 %95 to i32, !dbg !2554
  %96 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2555
  %stream76 = getelementptr inbounds %struct.zip, %struct.zip* %96, i32 0, i32 36, !dbg !2556
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream76, i32 0, i32 1, !dbg !2557
  store i32 %conv75, i32* %avail_in, align 8, !dbg !2558
  br label %do.body, !dbg !2559

do.body:                                          ; preds = %do.cond, %sw.bb74
  %97 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2560
  %stream77 = getelementptr inbounds %struct.zip, %struct.zip* %97, i32 0, i32 36, !dbg !2562
  %call78 = call i32 @cm_zlib_deflate(%struct.z_stream_s* %stream77, i32 0), !dbg !2563
  store i32 %call78, i32* %ret, align 4, !dbg !2564
  %98 = load i32, i32* %ret, align 4, !dbg !2565
  %cmp79 = icmp eq i32 %98, -2, !dbg !2567
  br i1 %cmp79, label %if.then81, label %if.end82, !dbg !2568

if.then81:                                        ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !2569
  br label %return, !dbg !2569

if.end82:                                         ; preds = %do.body
  %99 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2570
  %stream83 = getelementptr inbounds %struct.zip, %struct.zip* %99, i32 0, i32 36, !dbg !2572
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream83, i32 0, i32 4, !dbg !2573
  %100 = load i32, i32* %avail_out, align 8, !dbg !2573
  %cmp84 = icmp eq i32 %100, 0, !dbg !2574
  br i1 %cmp84, label %if.then86, label %if.end136, !dbg !2575

if.then86:                                        ; preds = %if.end82
  %101 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2576
  %tctx_valid87 = getelementptr inbounds %struct.zip, %struct.zip* %101, i32 0, i32 14, !dbg !2579
  %102 = load i8, i8* %tctx_valid87, align 4, !dbg !2579
  %tobool88 = icmp ne i8 %102, 0, !dbg !2576
  br i1 %tobool88, label %if.then89, label %if.else96, !dbg !2580

if.then89:                                        ; preds = %if.then86
  %103 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2581
  %tctx90 = getelementptr inbounds %struct.zip, %struct.zip* %103, i32 0, i32 13, !dbg !2583
  %104 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2584
  %buf91 = getelementptr inbounds %struct.zip, %struct.zip* %104, i32 0, i32 38, !dbg !2585
  %105 = load i8*, i8** %buf91, align 8, !dbg !2585
  %106 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2586
  %len_buf92 = getelementptr inbounds %struct.zip, %struct.zip* %106, i32 0, i32 37, !dbg !2587
  %107 = load i64, i64* %len_buf92, align 8, !dbg !2587
  %108 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2588
  %buf93 = getelementptr inbounds %struct.zip, %struct.zip* %108, i32 0, i32 38, !dbg !2589
  %109 = load i8*, i8** %buf93, align 8, !dbg !2589
  %110 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2590
  %len_buf94 = getelementptr inbounds %struct.zip, %struct.zip* %110, i32 0, i32 37, !dbg !2591
  %111 = load i64, i64* %len_buf94, align 8, !dbg !2591
  %call95 = call i32 @trad_enc_encrypt_update(%struct.trad_enc_ctx* %tctx90, i8* %105, i64 %107, i8* %109, i64 %111), !dbg !2592
  br label %if.end115, !dbg !2593

if.else96:                                        ; preds = %if.then86
  %112 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2594
  %cctx_valid97 = getelementptr inbounds %struct.zip, %struct.zip* %112, i32 0, i32 18, !dbg !2597
  %113 = load i8, i8* %cctx_valid97, align 8, !dbg !2597
  %tobool98 = icmp ne i8 %113, 0, !dbg !2594
  br i1 %tobool98, label %if.then99, label %if.end114, !dbg !2594

if.then99:                                        ; preds = %if.else96
  call void @llvm.dbg.declare(metadata i64* %outl, metadata !2598, metadata !728), !dbg !2600
  %114 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2601
  %len_buf100 = getelementptr inbounds %struct.zip, %struct.zip* %114, i32 0, i32 37, !dbg !2602
  %115 = load i64, i64* %len_buf100, align 8, !dbg !2602
  store i64 %115, i64* %outl, align 8, !dbg !2600
  %116 = load i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*, i8*, i64, i8*, i64*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 5), align 8, !dbg !2603
  %117 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2603
  %cctx101 = getelementptr inbounds %struct.zip, %struct.zip* %117, i32 0, i32 17, !dbg !2603
  %118 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2603
  %buf102 = getelementptr inbounds %struct.zip, %struct.zip* %118, i32 0, i32 38, !dbg !2603
  %119 = load i8*, i8** %buf102, align 8, !dbg !2603
  %120 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2603
  %len_buf103 = getelementptr inbounds %struct.zip, %struct.zip* %120, i32 0, i32 37, !dbg !2603
  %121 = load i64, i64* %len_buf103, align 8, !dbg !2603
  %122 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2603
  %buf104 = getelementptr inbounds %struct.zip, %struct.zip* %122, i32 0, i32 38, !dbg !2603
  %123 = load i8*, i8** %buf104, align 8, !dbg !2603
  %call105 = call i32 %116(i32* %cctx101, i8* %119, i64 %121, i8* %123, i64* %outl), !dbg !2603
  store i32 %call105, i32* %ret, align 4, !dbg !2604
  %124 = load i32, i32* %ret, align 4, !dbg !2605
  %cmp106 = icmp slt i32 %124, 0, !dbg !2607
  br i1 %cmp106, label %if.then108, label %if.end110, !dbg !2608

if.then108:                                       ; preds = %if.then99
  %125 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2609
  %archive109 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %125, i32 0, i32 0, !dbg !2611
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive109, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.45, i32 0, i32 0)), !dbg !2612
  store i64 -25, i64* %retval, align 8, !dbg !2613
  br label %return, !dbg !2613

if.end110:                                        ; preds = %if.then99
  %126 = load void (i32*, i8*, i64)*, void (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 1), align 8, !dbg !2614
  %127 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2614
  %hctx111 = getelementptr inbounds %struct.zip, %struct.zip* %127, i32 0, i32 19, !dbg !2614
  %128 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2614
  %buf112 = getelementptr inbounds %struct.zip, %struct.zip* %128, i32 0, i32 38, !dbg !2614
  %129 = load i8*, i8** %buf112, align 8, !dbg !2614
  %130 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2614
  %len_buf113 = getelementptr inbounds %struct.zip, %struct.zip* %130, i32 0, i32 37, !dbg !2614
  %131 = load i64, i64* %len_buf113, align 8, !dbg !2614
  call void %126(i32* %hctx111, i8* %129, i64 %131), !dbg !2614
  br label %if.end114, !dbg !2615

if.end114:                                        ; preds = %if.end110, %if.else96
  br label %if.end115

if.end115:                                        ; preds = %if.end114, %if.then89
  %132 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2616
  %133 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2617
  %buf116 = getelementptr inbounds %struct.zip, %struct.zip* %133, i32 0, i32 38, !dbg !2618
  %134 = load i8*, i8** %buf116, align 8, !dbg !2618
  %135 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2619
  %len_buf117 = getelementptr inbounds %struct.zip, %struct.zip* %135, i32 0, i32 37, !dbg !2620
  %136 = load i64, i64* %len_buf117, align 8, !dbg !2620
  %call118 = call i32 @__archive_write_output(%struct.archive_write* %132, i8* %134, i64 %136), !dbg !2621
  store i32 %call118, i32* %ret, align 4, !dbg !2622
  %137 = load i32, i32* %ret, align 4, !dbg !2623
  %cmp119 = icmp ne i32 %137, 0, !dbg !2625
  br i1 %cmp119, label %if.then121, label %if.end123, !dbg !2626

if.then121:                                       ; preds = %if.end115
  %138 = load i32, i32* %ret, align 4, !dbg !2627
  %conv122 = sext i32 %138 to i64, !dbg !2628
  store i64 %conv122, i64* %retval, align 8, !dbg !2629
  br label %return, !dbg !2629

if.end123:                                        ; preds = %if.end115
  %139 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2630
  %len_buf124 = getelementptr inbounds %struct.zip, %struct.zip* %139, i32 0, i32 37, !dbg !2631
  %140 = load i64, i64* %len_buf124, align 8, !dbg !2631
  %141 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2632
  %entry_compressed_written125 = getelementptr inbounds %struct.zip, %struct.zip* %141, i32 0, i32 3, !dbg !2633
  %142 = load i64, i64* %entry_compressed_written125, align 8, !dbg !2634
  %add126 = add i64 %142, %140, !dbg !2634
  store i64 %add126, i64* %entry_compressed_written125, align 8, !dbg !2634
  %143 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2635
  %len_buf127 = getelementptr inbounds %struct.zip, %struct.zip* %143, i32 0, i32 37, !dbg !2636
  %144 = load i64, i64* %len_buf127, align 8, !dbg !2636
  %145 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2637
  %written_bytes128 = getelementptr inbounds %struct.zip, %struct.zip* %145, i32 0, i32 28, !dbg !2638
  %146 = load i64, i64* %written_bytes128, align 8, !dbg !2639
  %add129 = add i64 %146, %144, !dbg !2639
  store i64 %add129, i64* %written_bytes128, align 8, !dbg !2639
  %147 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2640
  %buf130 = getelementptr inbounds %struct.zip, %struct.zip* %147, i32 0, i32 38, !dbg !2641
  %148 = load i8*, i8** %buf130, align 8, !dbg !2641
  %149 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2642
  %stream131 = getelementptr inbounds %struct.zip, %struct.zip* %149, i32 0, i32 36, !dbg !2643
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream131, i32 0, i32 3, !dbg !2644
  store i8* %148, i8** %next_out, align 8, !dbg !2645
  %150 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2646
  %len_buf132 = getelementptr inbounds %struct.zip, %struct.zip* %150, i32 0, i32 37, !dbg !2647
  %151 = load i64, i64* %len_buf132, align 8, !dbg !2647
  %conv133 = trunc i64 %151 to i32, !dbg !2648
  %152 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2649
  %stream134 = getelementptr inbounds %struct.zip, %struct.zip* %152, i32 0, i32 36, !dbg !2650
  %avail_out135 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream134, i32 0, i32 4, !dbg !2651
  store i32 %conv133, i32* %avail_out135, align 8, !dbg !2652
  br label %if.end136, !dbg !2653

if.end136:                                        ; preds = %if.end123, %if.end82
  br label %do.cond, !dbg !2654

do.cond:                                          ; preds = %if.end136
  %153 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2655
  %stream137 = getelementptr inbounds %struct.zip, %struct.zip* %153, i32 0, i32 36, !dbg !2657
  %avail_in138 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream137, i32 0, i32 1, !dbg !2658
  %154 = load i32, i32* %avail_in138, align 8, !dbg !2658
  %cmp139 = icmp ne i32 %154, 0, !dbg !2659
  br i1 %cmp139, label %do.body, label %do.end, !dbg !2660

do.end:                                           ; preds = %do.cond
  br label %sw.epilog143, !dbg !2661

sw.default141:                                    ; preds = %if.end24
  %155 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2662
  %archive142 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %155, i32 0, i32 0, !dbg !2663
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive142, i32 -1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.46, i32 0, i32 0)), !dbg !2664
  store i64 -30, i64* %retval, align 8, !dbg !2665
  br label %return, !dbg !2665

sw.epilog143:                                     ; preds = %do.end, %if.end73
  %156 = load i64, i64* %s.addr, align 8, !dbg !2666
  %157 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2667
  %entry_uncompressed_limit144 = getelementptr inbounds %struct.zip, %struct.zip* %157, i32 0, i32 5, !dbg !2668
  %158 = load i64, i64* %entry_uncompressed_limit144, align 8, !dbg !2669
  %sub = sub i64 %158, %156, !dbg !2669
  store i64 %sub, i64* %entry_uncompressed_limit144, align 8, !dbg !2669
  %159 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2670
  %cctx_valid145 = getelementptr inbounds %struct.zip, %struct.zip* %159, i32 0, i32 18, !dbg !2672
  %160 = load i8, i8* %cctx_valid145, align 8, !dbg !2672
  %tobool146 = icmp ne i8 %160, 0, !dbg !2670
  br i1 %tobool146, label %lor.lhs.false147, label %if.then150, !dbg !2673

lor.lhs.false147:                                 ; preds = %sw.epilog143
  %161 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2674
  %aes_vendor = getelementptr inbounds %struct.zip, %struct.zip* %161, i32 0, i32 16, !dbg !2676
  %162 = load i32, i32* %aes_vendor, align 8, !dbg !2676
  %cmp148 = icmp ne i32 %162, 2, !dbg !2677
  br i1 %cmp148, label %if.then150, label %if.end157, !dbg !2678

if.then150:                                       ; preds = %lor.lhs.false147, %sw.epilog143
  %163 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2679
  %crc32func = getelementptr inbounds %struct.zip, %struct.zip* %163, i32 0, i32 23, !dbg !2680
  %164 = load i64 (i64, i8*, i64)*, i64 (i64, i8*, i64)** %crc32func, align 8, !dbg !2680
  %165 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2681
  %entry_crc32 = getelementptr inbounds %struct.zip, %struct.zip* %165, i32 0, i32 7, !dbg !2682
  %166 = load i32, i32* %entry_crc32, align 8, !dbg !2682
  %conv151 = zext i32 %166 to i64, !dbg !2681
  %167 = load i8*, i8** %buff.addr, align 8, !dbg !2683
  %168 = load i64, i64* %s.addr, align 8, !dbg !2684
  %conv152 = trunc i64 %168 to i32, !dbg !2685
  %conv153 = zext i32 %conv152 to i64, !dbg !2685
  %call154 = call i64 %164(i64 %conv151, i8* %167, i64 %conv153), !dbg !2679
  %conv155 = trunc i64 %call154 to i32, !dbg !2679
  %169 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2686
  %entry_crc32156 = getelementptr inbounds %struct.zip, %struct.zip* %169, i32 0, i32 7, !dbg !2687
  store i32 %conv155, i32* %entry_crc32156, align 8, !dbg !2688
  br label %if.end157, !dbg !2686

if.end157:                                        ; preds = %if.then150, %lor.lhs.false147
  %170 = load i64, i64* %s.addr, align 8, !dbg !2689
  store i64 %170, i64* %retval, align 8, !dbg !2690
  br label %return, !dbg !2690

return:                                           ; preds = %if.end157, %sw.default141, %if.then121, %if.then108, %if.then81, %if.then66, %if.then56, %if.then48, %if.then19, %if.then9, %if.then3
  %171 = load i64, i64* %retval, align 8, !dbg !2691
  ret i64 %171, !dbg !2691
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_zip_finish_entry(%struct.archive_write* %a) #0 !dbg !718 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %ret = alloca i32, align 4
  %remainder = alloca i64, align 8
  %outl = alloca i64, align 8
  %hmac = alloca [20 x i8], align 16
  %hmac_len = alloca i64, align 8
  %d = alloca [24 x i8], align 16
  %zip64 = alloca [32 x i8], align 16
  %z = alloca i8*, align 8
  %zd = alloca i8*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2692, metadata !728), !dbg !2693
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !2694, metadata !728), !dbg !2695
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2696
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2697
  %1 = load i8*, i8** %format_data, align 8, !dbg !2697
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !2696
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !2695
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2698, metadata !728), !dbg !2699
  %3 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2700
  %entry_compression = getelementptr inbounds %struct.zip, %struct.zip* %3, i32 0, i32 8, !dbg !2702
  %4 = load i32, i32* %entry_compression, align 4, !dbg !2702
  %cmp = icmp eq i32 %4, 8, !dbg !2703
  br i1 %cmp, label %if.then, label %if.end40, !dbg !2704

if.then:                                          ; preds = %entry
  br label %for.cond, !dbg !2705

for.cond:                                         ; preds = %if.end33, %if.then
  call void @llvm.dbg.declare(metadata i64* %remainder, metadata !2707, metadata !728), !dbg !2711
  %5 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2712
  %stream = getelementptr inbounds %struct.zip, %struct.zip* %5, i32 0, i32 36, !dbg !2713
  %call = call i32 @cm_zlib_deflate(%struct.z_stream_s* %stream, i32 4), !dbg !2714
  store i32 %call, i32* %ret, align 4, !dbg !2715
  %6 = load i32, i32* %ret, align 4, !dbg !2716
  %cmp1 = icmp eq i32 %6, -2, !dbg !2718
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !2719

if.then2:                                         ; preds = %for.cond
  store i32 -30, i32* %retval, align 4, !dbg !2720
  br label %return, !dbg !2720

if.end:                                           ; preds = %for.cond
  %7 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2721
  %len_buf = getelementptr inbounds %struct.zip, %struct.zip* %7, i32 0, i32 37, !dbg !2722
  %8 = load i64, i64* %len_buf, align 8, !dbg !2722
  %9 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2723
  %stream3 = getelementptr inbounds %struct.zip, %struct.zip* %9, i32 0, i32 36, !dbg !2724
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream3, i32 0, i32 4, !dbg !2725
  %10 = load i32, i32* %avail_out, align 8, !dbg !2725
  %conv = zext i32 %10 to i64, !dbg !2723
  %sub = sub i64 %8, %conv, !dbg !2726
  store i64 %sub, i64* %remainder, align 8, !dbg !2727
  %11 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2728
  %tctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %11, i32 0, i32 14, !dbg !2730
  %12 = load i8, i8* %tctx_valid, align 4, !dbg !2730
  %tobool = icmp ne i8 %12, 0, !dbg !2728
  br i1 %tobool, label %if.then4, label %if.else, !dbg !2731

if.then4:                                         ; preds = %if.end
  %13 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2732
  %tctx = getelementptr inbounds %struct.zip, %struct.zip* %13, i32 0, i32 13, !dbg !2734
  %14 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2735
  %buf = getelementptr inbounds %struct.zip, %struct.zip* %14, i32 0, i32 38, !dbg !2736
  %15 = load i8*, i8** %buf, align 8, !dbg !2736
  %16 = load i64, i64* %remainder, align 8, !dbg !2737
  %17 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2738
  %buf5 = getelementptr inbounds %struct.zip, %struct.zip* %17, i32 0, i32 38, !dbg !2739
  %18 = load i8*, i8** %buf5, align 8, !dbg !2739
  %19 = load i64, i64* %remainder, align 8, !dbg !2740
  %call6 = call i32 @trad_enc_encrypt_update(%struct.trad_enc_ctx* %tctx, i8* %15, i64 %16, i8* %18, i64 %19), !dbg !2741
  br label %if.end18, !dbg !2742

if.else:                                          ; preds = %if.end
  %20 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2743
  %cctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %20, i32 0, i32 18, !dbg !2746
  %21 = load i8, i8* %cctx_valid, align 8, !dbg !2746
  %tobool7 = icmp ne i8 %21, 0, !dbg !2743
  br i1 %tobool7, label %if.then8, label %if.end17, !dbg !2743

if.then8:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i64* %outl, metadata !2747, metadata !728), !dbg !2749
  %22 = load i64, i64* %remainder, align 8, !dbg !2750
  store i64 %22, i64* %outl, align 8, !dbg !2749
  %23 = load i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*, i8*, i64, i8*, i64*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 5), align 8, !dbg !2751
  %24 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2751
  %cctx = getelementptr inbounds %struct.zip, %struct.zip* %24, i32 0, i32 17, !dbg !2751
  %25 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2751
  %buf9 = getelementptr inbounds %struct.zip, %struct.zip* %25, i32 0, i32 38, !dbg !2751
  %26 = load i8*, i8** %buf9, align 8, !dbg !2751
  %27 = load i64, i64* %remainder, align 8, !dbg !2751
  %28 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2751
  %buf10 = getelementptr inbounds %struct.zip, %struct.zip* %28, i32 0, i32 38, !dbg !2751
  %29 = load i8*, i8** %buf10, align 8, !dbg !2751
  %call11 = call i32 %23(i32* %cctx, i8* %26, i64 %27, i8* %29, i64* %outl), !dbg !2751
  store i32 %call11, i32* %ret, align 4, !dbg !2752
  %30 = load i32, i32* %ret, align 4, !dbg !2753
  %cmp12 = icmp slt i32 %30, 0, !dbg !2755
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !2756

if.then14:                                        ; preds = %if.then8
  %31 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2757
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %31, i32 0, i32 0, !dbg !2759
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.45, i32 0, i32 0)), !dbg !2760
  store i32 -25, i32* %retval, align 4, !dbg !2761
  br label %return, !dbg !2761

if.end15:                                         ; preds = %if.then8
  %32 = load void (i32*, i8*, i64)*, void (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 1), align 8, !dbg !2762
  %33 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2762
  %hctx = getelementptr inbounds %struct.zip, %struct.zip* %33, i32 0, i32 19, !dbg !2762
  %34 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2762
  %buf16 = getelementptr inbounds %struct.zip, %struct.zip* %34, i32 0, i32 38, !dbg !2762
  %35 = load i8*, i8** %buf16, align 8, !dbg !2762
  %36 = load i64, i64* %remainder, align 8, !dbg !2762
  call void %32(i32* %hctx, i8* %35, i64 %36), !dbg !2762
  br label %if.end17, !dbg !2763

if.end17:                                         ; preds = %if.end15, %if.else
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then4
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2764
  %38 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2765
  %buf19 = getelementptr inbounds %struct.zip, %struct.zip* %38, i32 0, i32 38, !dbg !2766
  %39 = load i8*, i8** %buf19, align 8, !dbg !2766
  %40 = load i64, i64* %remainder, align 8, !dbg !2767
  %call20 = call i32 @__archive_write_output(%struct.archive_write* %37, i8* %39, i64 %40), !dbg !2768
  store i32 %call20, i32* %ret, align 4, !dbg !2769
  %41 = load i32, i32* %ret, align 4, !dbg !2770
  %cmp21 = icmp ne i32 %41, 0, !dbg !2772
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !2773

if.then23:                                        ; preds = %if.end18
  %42 = load i32, i32* %ret, align 4, !dbg !2774
  store i32 %42, i32* %retval, align 4, !dbg !2775
  br label %return, !dbg !2775

if.end24:                                         ; preds = %if.end18
  %43 = load i64, i64* %remainder, align 8, !dbg !2776
  %44 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2777
  %entry_compressed_written = getelementptr inbounds %struct.zip, %struct.zip* %44, i32 0, i32 3, !dbg !2778
  %45 = load i64, i64* %entry_compressed_written, align 8, !dbg !2779
  %add = add i64 %45, %43, !dbg !2779
  store i64 %add, i64* %entry_compressed_written, align 8, !dbg !2779
  %46 = load i64, i64* %remainder, align 8, !dbg !2780
  %47 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2781
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %47, i32 0, i32 28, !dbg !2782
  %48 = load i64, i64* %written_bytes, align 8, !dbg !2783
  %add25 = add i64 %48, %46, !dbg !2783
  store i64 %add25, i64* %written_bytes, align 8, !dbg !2783
  %49 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2784
  %buf26 = getelementptr inbounds %struct.zip, %struct.zip* %49, i32 0, i32 38, !dbg !2785
  %50 = load i8*, i8** %buf26, align 8, !dbg !2785
  %51 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2786
  %stream27 = getelementptr inbounds %struct.zip, %struct.zip* %51, i32 0, i32 36, !dbg !2787
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream27, i32 0, i32 3, !dbg !2788
  store i8* %50, i8** %next_out, align 8, !dbg !2789
  %52 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2790
  %stream28 = getelementptr inbounds %struct.zip, %struct.zip* %52, i32 0, i32 36, !dbg !2792
  %avail_out29 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream28, i32 0, i32 4, !dbg !2793
  %53 = load i32, i32* %avail_out29, align 8, !dbg !2793
  %cmp30 = icmp ne i32 %53, 0, !dbg !2794
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !2795

if.then32:                                        ; preds = %if.end24
  br label %for.end, !dbg !2796

if.end33:                                         ; preds = %if.end24
  %54 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2797
  %len_buf34 = getelementptr inbounds %struct.zip, %struct.zip* %54, i32 0, i32 37, !dbg !2798
  %55 = load i64, i64* %len_buf34, align 8, !dbg !2798
  %conv35 = trunc i64 %55 to i32, !dbg !2799
  %56 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2800
  %stream36 = getelementptr inbounds %struct.zip, %struct.zip* %56, i32 0, i32 36, !dbg !2801
  %avail_out37 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream36, i32 0, i32 4, !dbg !2802
  store i32 %conv35, i32* %avail_out37, align 8, !dbg !2803
  br label %for.cond, !dbg !2804

for.end:                                          ; preds = %if.then32
  %57 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2806
  %stream38 = getelementptr inbounds %struct.zip, %struct.zip* %57, i32 0, i32 36, !dbg !2807
  %call39 = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %stream38), !dbg !2808
  br label %if.end40, !dbg !2809

if.end40:                                         ; preds = %for.end, %entry
  %58 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2810
  %hctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %58, i32 0, i32 20, !dbg !2812
  %59 = load i8, i8* %hctx_valid, align 8, !dbg !2812
  %tobool41 = icmp ne i8 %59, 0, !dbg !2810
  br i1 %tobool41, label %if.then42, label %if.end54, !dbg !2813

if.then42:                                        ; preds = %if.end40
  call void @llvm.dbg.declare(metadata [20 x i8]* %hmac, metadata !2814, metadata !728), !dbg !2819
  call void @llvm.dbg.declare(metadata i64* %hmac_len, metadata !2820, metadata !728), !dbg !2821
  store i64 20, i64* %hmac_len, align 8, !dbg !2821
  %60 = load void (i32*, i8*, i64*)*, void (i32*, i8*, i64*)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 2), align 8, !dbg !2822
  %61 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2822
  %hctx43 = getelementptr inbounds %struct.zip, %struct.zip* %61, i32 0, i32 19, !dbg !2822
  %arraydecay = getelementptr inbounds [20 x i8], [20 x i8]* %hmac, i32 0, i32 0, !dbg !2822
  call void %60(i32* %hctx43, i8* %arraydecay, i64* %hmac_len), !dbg !2822
  %62 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2823
  %arraydecay44 = getelementptr inbounds [20 x i8], [20 x i8]* %hmac, i32 0, i32 0, !dbg !2824
  %call45 = call i32 @__archive_write_output(%struct.archive_write* %62, i8* %arraydecay44, i64 10), !dbg !2825
  store i32 %call45, i32* %ret, align 4, !dbg !2826
  %63 = load i32, i32* %ret, align 4, !dbg !2827
  %cmp46 = icmp ne i32 %63, 0, !dbg !2829
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !2830

if.then48:                                        ; preds = %if.then42
  %64 = load i32, i32* %ret, align 4, !dbg !2831
  store i32 %64, i32* %retval, align 4, !dbg !2832
  br label %return, !dbg !2832

if.end49:                                         ; preds = %if.then42
  %65 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2833
  %entry_compressed_written50 = getelementptr inbounds %struct.zip, %struct.zip* %65, i32 0, i32 3, !dbg !2834
  %66 = load i64, i64* %entry_compressed_written50, align 8, !dbg !2835
  %add51 = add nsw i64 %66, 10, !dbg !2835
  store i64 %add51, i64* %entry_compressed_written50, align 8, !dbg !2835
  %67 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2836
  %written_bytes52 = getelementptr inbounds %struct.zip, %struct.zip* %67, i32 0, i32 28, !dbg !2837
  %68 = load i64, i64* %written_bytes52, align 8, !dbg !2838
  %add53 = add nsw i64 %68, 10, !dbg !2838
  store i64 %add53, i64* %written_bytes52, align 8, !dbg !2838
  br label %if.end54, !dbg !2839

if.end54:                                         ; preds = %if.end49, %if.end40
  %69 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2840
  %entry_flags = getelementptr inbounds %struct.zip, %struct.zip* %69, i32 0, i32 10, !dbg !2842
  %70 = load i32, i32* %entry_flags, align 4, !dbg !2842
  %and = and i32 %70, 8, !dbg !2843
  %cmp55 = icmp ne i32 %and, 0, !dbg !2844
  br i1 %cmp55, label %if.then57, label %if.end99, !dbg !2845

if.then57:                                        ; preds = %if.end54
  call void @llvm.dbg.declare(metadata [24 x i8]* %d, metadata !2846, metadata !728), !dbg !2851
  %arraydecay58 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2852
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay58, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.51, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !2852
  %71 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2853
  %cctx_valid59 = getelementptr inbounds %struct.zip, %struct.zip* %71, i32 0, i32 18, !dbg !2855
  %72 = load i8, i8* %cctx_valid59, align 8, !dbg !2855
  %conv60 = sext i8 %72 to i32, !dbg !2853
  %tobool61 = icmp ne i32 %conv60, 0, !dbg !2853
  br i1 %tobool61, label %land.lhs.true, label %if.else66, !dbg !2856

land.lhs.true:                                    ; preds = %if.then57
  %73 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2857
  %aes_vendor = getelementptr inbounds %struct.zip, %struct.zip* %73, i32 0, i32 16, !dbg !2859
  %74 = load i32, i32* %aes_vendor, align 8, !dbg !2859
  %cmp62 = icmp eq i32 %74, 2, !dbg !2860
  br i1 %cmp62, label %if.then64, label %if.else66, !dbg !2861

if.then64:                                        ; preds = %land.lhs.true
  %arraydecay65 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2862
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay65, i64 4, !dbg !2863
  call void @archive_le32enc(i8* %add.ptr, i32 0), !dbg !2864
  br label %if.end69, !dbg !2864

if.else66:                                        ; preds = %land.lhs.true, %if.then57
  %arraydecay67 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2865
  %add.ptr68 = getelementptr inbounds i8, i8* %arraydecay67, i64 4, !dbg !2866
  %75 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2867
  %entry_crc32 = getelementptr inbounds %struct.zip, %struct.zip* %75, i32 0, i32 7, !dbg !2868
  %76 = load i32, i32* %entry_crc32, align 8, !dbg !2868
  call void @archive_le32enc(i8* %add.ptr68, i32 %76), !dbg !2869
  br label %if.end69

if.end69:                                         ; preds = %if.else66, %if.then64
  %77 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2870
  %entry_uses_zip64 = getelementptr inbounds %struct.zip, %struct.zip* %77, i32 0, i32 11, !dbg !2872
  %78 = load i32, i32* %entry_uses_zip64, align 8, !dbg !2872
  %tobool70 = icmp ne i32 %78, 0, !dbg !2870
  br i1 %tobool70, label %if.then71, label %if.else81, !dbg !2873

if.then71:                                        ; preds = %if.end69
  %arraydecay72 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2874
  %add.ptr73 = getelementptr inbounds i8, i8* %arraydecay72, i64 8, !dbg !2876
  %79 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2877
  %entry_compressed_written74 = getelementptr inbounds %struct.zip, %struct.zip* %79, i32 0, i32 3, !dbg !2878
  %80 = load i64, i64* %entry_compressed_written74, align 8, !dbg !2878
  call void @archive_le64enc(i8* %add.ptr73, i64 %80), !dbg !2879
  %arraydecay75 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2880
  %add.ptr76 = getelementptr inbounds i8, i8* %arraydecay75, i64 16, !dbg !2881
  %81 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2882
  %entry_uncompressed_written = getelementptr inbounds %struct.zip, %struct.zip* %81, i32 0, i32 4, !dbg !2883
  %82 = load i64, i64* %entry_uncompressed_written, align 8, !dbg !2883
  call void @archive_le64enc(i8* %add.ptr76, i64 %82), !dbg !2884
  %83 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2885
  %arraydecay77 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2886
  %call78 = call i32 @__archive_write_output(%struct.archive_write* %83, i8* %arraydecay77, i64 24), !dbg !2887
  store i32 %call78, i32* %ret, align 4, !dbg !2888
  %84 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2889
  %written_bytes79 = getelementptr inbounds %struct.zip, %struct.zip* %84, i32 0, i32 28, !dbg !2890
  %85 = load i64, i64* %written_bytes79, align 8, !dbg !2891
  %add80 = add nsw i64 %85, 24, !dbg !2891
  store i64 %add80, i64* %written_bytes79, align 8, !dbg !2891
  br label %if.end94, !dbg !2892

if.else81:                                        ; preds = %if.end69
  %arraydecay82 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2893
  %add.ptr83 = getelementptr inbounds i8, i8* %arraydecay82, i64 8, !dbg !2895
  %86 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2896
  %entry_compressed_written84 = getelementptr inbounds %struct.zip, %struct.zip* %86, i32 0, i32 3, !dbg !2897
  %87 = load i64, i64* %entry_compressed_written84, align 8, !dbg !2897
  %conv85 = trunc i64 %87 to i32, !dbg !2898
  call void @archive_le32enc(i8* %add.ptr83, i32 %conv85), !dbg !2899
  %arraydecay86 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2900
  %add.ptr87 = getelementptr inbounds i8, i8* %arraydecay86, i64 12, !dbg !2901
  %88 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2902
  %entry_uncompressed_written88 = getelementptr inbounds %struct.zip, %struct.zip* %88, i32 0, i32 4, !dbg !2903
  %89 = load i64, i64* %entry_uncompressed_written88, align 8, !dbg !2903
  %conv89 = trunc i64 %89 to i32, !dbg !2904
  call void @archive_le32enc(i8* %add.ptr87, i32 %conv89), !dbg !2905
  %90 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2906
  %arraydecay90 = getelementptr inbounds [24 x i8], [24 x i8]* %d, i32 0, i32 0, !dbg !2907
  %call91 = call i32 @__archive_write_output(%struct.archive_write* %90, i8* %arraydecay90, i64 16), !dbg !2908
  store i32 %call91, i32* %ret, align 4, !dbg !2909
  %91 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2910
  %written_bytes92 = getelementptr inbounds %struct.zip, %struct.zip* %91, i32 0, i32 28, !dbg !2911
  %92 = load i64, i64* %written_bytes92, align 8, !dbg !2912
  %add93 = add nsw i64 %92, 16, !dbg !2912
  store i64 %add93, i64* %written_bytes92, align 8, !dbg !2912
  br label %if.end94

if.end94:                                         ; preds = %if.else81, %if.then71
  %93 = load i32, i32* %ret, align 4, !dbg !2913
  %cmp95 = icmp ne i32 %93, 0, !dbg !2915
  br i1 %cmp95, label %if.then97, label %if.end98, !dbg !2916

if.then97:                                        ; preds = %if.end94
  store i32 -30, i32* %retval, align 4, !dbg !2917
  br label %return, !dbg !2917

if.end98:                                         ; preds = %if.end94
  br label %if.end99, !dbg !2918

if.end99:                                         ; preds = %if.end98, %if.end54
  %94 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2919
  %entry_compressed_written100 = getelementptr inbounds %struct.zip, %struct.zip* %94, i32 0, i32 3, !dbg !2921
  %95 = load i64, i64* %entry_compressed_written100, align 8, !dbg !2921
  %cmp101 = icmp sgt i64 %95, 4294967295, !dbg !2922
  br i1 %cmp101, label %if.then109, label %lor.lhs.false, !dbg !2923

lor.lhs.false:                                    ; preds = %if.end99
  %96 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2924
  %entry_uncompressed_written103 = getelementptr inbounds %struct.zip, %struct.zip* %96, i32 0, i32 4, !dbg !2926
  %97 = load i64, i64* %entry_uncompressed_written103, align 8, !dbg !2926
  %cmp104 = icmp sgt i64 %97, 4294967295, !dbg !2927
  br i1 %cmp104, label %if.then109, label %lor.lhs.false106, !dbg !2928

lor.lhs.false106:                                 ; preds = %lor.lhs.false
  %98 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2929
  %entry_offset = getelementptr inbounds %struct.zip, %struct.zip* %98, i32 0, i32 0, !dbg !2930
  %99 = load i64, i64* %entry_offset, align 8, !dbg !2930
  %cmp107 = icmp sgt i64 %99, 4294967295, !dbg !2931
  br i1 %cmp107, label %if.then109, label %if.end162, !dbg !2932

if.then109:                                       ; preds = %lor.lhs.false106, %lor.lhs.false, %if.end99
  call void @llvm.dbg.declare(metadata [32 x i8]* %zip64, metadata !2934, metadata !728), !dbg !2936
  call void @llvm.dbg.declare(metadata i8** %z, metadata !2937, metadata !728), !dbg !2938
  %arraydecay110 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !2939
  store i8* %arraydecay110, i8** %z, align 8, !dbg !2938
  call void @llvm.dbg.declare(metadata i8** %zd, metadata !2940, metadata !728), !dbg !2941
  %100 = load i8*, i8** %z, align 8, !dbg !2942
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %100, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.52, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !2943
  %101 = load i8*, i8** %z, align 8, !dbg !2944
  %add.ptr111 = getelementptr inbounds i8, i8* %101, i64 4, !dbg !2944
  store i8* %add.ptr111, i8** %z, align 8, !dbg !2944
  %102 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2945
  %entry_uncompressed_written112 = getelementptr inbounds %struct.zip, %struct.zip* %102, i32 0, i32 4, !dbg !2947
  %103 = load i64, i64* %entry_uncompressed_written112, align 8, !dbg !2947
  %cmp113 = icmp sge i64 %103, 4294967295, !dbg !2948
  br i1 %cmp113, label %if.then115, label %if.end118, !dbg !2949

if.then115:                                       ; preds = %if.then109
  %104 = load i8*, i8** %z, align 8, !dbg !2950
  %105 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2952
  %entry_uncompressed_written116 = getelementptr inbounds %struct.zip, %struct.zip* %105, i32 0, i32 4, !dbg !2953
  %106 = load i64, i64* %entry_uncompressed_written116, align 8, !dbg !2953
  call void @archive_le64enc(i8* %104, i64 %106), !dbg !2954
  %107 = load i8*, i8** %z, align 8, !dbg !2955
  %add.ptr117 = getelementptr inbounds i8, i8* %107, i64 8, !dbg !2955
  store i8* %add.ptr117, i8** %z, align 8, !dbg !2955
  br label %if.end118, !dbg !2956

if.end118:                                        ; preds = %if.then115, %if.then109
  %108 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2957
  %entry_compressed_written119 = getelementptr inbounds %struct.zip, %struct.zip* %108, i32 0, i32 3, !dbg !2959
  %109 = load i64, i64* %entry_compressed_written119, align 8, !dbg !2959
  %cmp120 = icmp sge i64 %109, 4294967295, !dbg !2960
  br i1 %cmp120, label %if.then122, label %if.end125, !dbg !2961

if.then122:                                       ; preds = %if.end118
  %110 = load i8*, i8** %z, align 8, !dbg !2962
  %111 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2964
  %entry_compressed_written123 = getelementptr inbounds %struct.zip, %struct.zip* %111, i32 0, i32 3, !dbg !2965
  %112 = load i64, i64* %entry_compressed_written123, align 8, !dbg !2965
  call void @archive_le64enc(i8* %110, i64 %112), !dbg !2966
  %113 = load i8*, i8** %z, align 8, !dbg !2967
  %add.ptr124 = getelementptr inbounds i8, i8* %113, i64 8, !dbg !2967
  store i8* %add.ptr124, i8** %z, align 8, !dbg !2967
  br label %if.end125, !dbg !2968

if.end125:                                        ; preds = %if.then122, %if.end118
  %114 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2969
  %entry_offset126 = getelementptr inbounds %struct.zip, %struct.zip* %114, i32 0, i32 0, !dbg !2971
  %115 = load i64, i64* %entry_offset126, align 8, !dbg !2971
  %cmp127 = icmp sge i64 %115, 4294967295, !dbg !2972
  br i1 %cmp127, label %if.then129, label %if.end132, !dbg !2973

if.then129:                                       ; preds = %if.end125
  %116 = load i8*, i8** %z, align 8, !dbg !2974
  %117 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2976
  %entry_offset130 = getelementptr inbounds %struct.zip, %struct.zip* %117, i32 0, i32 0, !dbg !2977
  %118 = load i64, i64* %entry_offset130, align 8, !dbg !2977
  call void @archive_le64enc(i8* %116, i64 %118), !dbg !2978
  %119 = load i8*, i8** %z, align 8, !dbg !2979
  %add.ptr131 = getelementptr inbounds i8, i8* %119, i64 8, !dbg !2979
  store i8* %add.ptr131, i8** %z, align 8, !dbg !2979
  br label %if.end132, !dbg !2980

if.end132:                                        ; preds = %if.then129, %if.end125
  %arraydecay133 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !2981
  %add.ptr134 = getelementptr inbounds i8, i8* %arraydecay133, i64 2, !dbg !2982
  %120 = load i8*, i8** %z, align 8, !dbg !2983
  %arraydecay135 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !2984
  %add.ptr136 = getelementptr inbounds i8, i8* %arraydecay135, i64 4, !dbg !2985
  %sub.ptr.lhs.cast = ptrtoint i8* %120 to i64, !dbg !2986
  %sub.ptr.rhs.cast = ptrtoint i8* %add.ptr136 to i64, !dbg !2986
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2986
  %conv137 = trunc i64 %sub.ptr.sub to i16, !dbg !2987
  call void @archive_le16enc(i8* %add.ptr134, i16 zeroext %conv137), !dbg !2988
  %121 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !2989
  %122 = load i8*, i8** %z, align 8, !dbg !2990
  %arraydecay138 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !2991
  %sub.ptr.lhs.cast139 = ptrtoint i8* %122 to i64, !dbg !2992
  %sub.ptr.rhs.cast140 = ptrtoint i8* %arraydecay138 to i64, !dbg !2992
  %sub.ptr.sub141 = sub i64 %sub.ptr.lhs.cast139, %sub.ptr.rhs.cast140, !dbg !2992
  %call142 = call i8* @cd_alloc(%struct.zip* %121, i64 %sub.ptr.sub141), !dbg !2993
  store i8* %call142, i8** %zd, align 8, !dbg !2994
  %123 = load i8*, i8** %zd, align 8, !dbg !2995
  %cmp143 = icmp eq i8* %123, null, !dbg !2997
  br i1 %cmp143, label %if.then145, label %if.end147, !dbg !2998

if.then145:                                       ; preds = %if.end132
  %124 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2999
  %archive146 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %124, i32 0, i32 0, !dbg !3001
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive146, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.4, i32 0, i32 0)), !dbg !3002
  store i32 -30, i32* %retval, align 4, !dbg !3003
  br label %return, !dbg !3003

if.end147:                                        ; preds = %if.end132
  %125 = load i8*, i8** %zd, align 8, !dbg !3004
  %arraydecay148 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !3005
  %126 = load i8*, i8** %z, align 8, !dbg !3006
  %arraydecay149 = getelementptr inbounds [32 x i8], [32 x i8]* %zip64, i32 0, i32 0, !dbg !3007
  %sub.ptr.lhs.cast150 = ptrtoint i8* %126 to i64, !dbg !3008
  %sub.ptr.rhs.cast151 = ptrtoint i8* %arraydecay149 to i64, !dbg !3008
  %sub.ptr.sub152 = sub i64 %sub.ptr.lhs.cast150, %sub.ptr.rhs.cast151, !dbg !3008
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %125, i8* %arraydecay148, i64 %sub.ptr.sub152, i32 1, i1 false), !dbg !3005
  %127 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3009
  %file_header = getelementptr inbounds %struct.zip, %struct.zip* %127, i32 0, i32 21, !dbg !3011
  %128 = load i8*, i8** %file_header, align 8, !dbg !3011
  %add.ptr153 = getelementptr inbounds i8, i8* %128, i64 6, !dbg !3012
  %call154 = call zeroext i16 @archive_le16dec(i8* %add.ptr153), !dbg !3013
  %conv155 = zext i16 %call154 to i32, !dbg !3013
  %cmp156 = icmp slt i32 %conv155, 45, !dbg !3014
  br i1 %cmp156, label %if.then158, label %if.end161, !dbg !3015

if.then158:                                       ; preds = %if.end147
  %129 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3016
  %file_header159 = getelementptr inbounds %struct.zip, %struct.zip* %129, i32 0, i32 21, !dbg !3017
  %130 = load i8*, i8** %file_header159, align 8, !dbg !3017
  %add.ptr160 = getelementptr inbounds i8, i8* %130, i64 6, !dbg !3018
  call void @archive_le16enc(i8* %add.ptr160, i16 zeroext 45), !dbg !3019
  br label %if.end161, !dbg !3019

if.end161:                                        ; preds = %if.then158, %if.end147
  br label %if.end162, !dbg !3020

if.end162:                                        ; preds = %if.end161, %lor.lhs.false106
  %131 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3021
  %cctx_valid163 = getelementptr inbounds %struct.zip, %struct.zip* %131, i32 0, i32 18, !dbg !3023
  %132 = load i8, i8* %cctx_valid163, align 8, !dbg !3023
  %conv164 = sext i8 %132 to i32, !dbg !3021
  %tobool165 = icmp ne i32 %conv164, 0, !dbg !3021
  br i1 %tobool165, label %land.lhs.true166, label %if.else173, !dbg !3024

land.lhs.true166:                                 ; preds = %if.end162
  %133 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3025
  %aes_vendor167 = getelementptr inbounds %struct.zip, %struct.zip* %133, i32 0, i32 16, !dbg !3027
  %134 = load i32, i32* %aes_vendor167, align 8, !dbg !3027
  %cmp168 = icmp eq i32 %134, 2, !dbg !3028
  br i1 %cmp168, label %if.then170, label %if.else173, !dbg !3029

if.then170:                                       ; preds = %land.lhs.true166
  %135 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3030
  %file_header171 = getelementptr inbounds %struct.zip, %struct.zip* %135, i32 0, i32 21, !dbg !3031
  %136 = load i8*, i8** %file_header171, align 8, !dbg !3031
  %add.ptr172 = getelementptr inbounds i8, i8* %136, i64 16, !dbg !3032
  call void @archive_le32enc(i8* %add.ptr172, i32 0), !dbg !3033
  br label %if.end177, !dbg !3033

if.else173:                                       ; preds = %land.lhs.true166, %if.end162
  %137 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3034
  %file_header174 = getelementptr inbounds %struct.zip, %struct.zip* %137, i32 0, i32 21, !dbg !3035
  %138 = load i8*, i8** %file_header174, align 8, !dbg !3035
  %add.ptr175 = getelementptr inbounds i8, i8* %138, i64 16, !dbg !3036
  %139 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3037
  %entry_crc32176 = getelementptr inbounds %struct.zip, %struct.zip* %139, i32 0, i32 7, !dbg !3038
  %140 = load i32, i32* %entry_crc32176, align 8, !dbg !3038
  call void @archive_le32enc(i8* %add.ptr175, i32 %140), !dbg !3039
  br label %if.end177

if.end177:                                        ; preds = %if.else173, %if.then170
  %141 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3040
  %file_header178 = getelementptr inbounds %struct.zip, %struct.zip* %141, i32 0, i32 21, !dbg !3041
  %142 = load i8*, i8** %file_header178, align 8, !dbg !3041
  %add.ptr179 = getelementptr inbounds i8, i8* %142, i64 20, !dbg !3042
  %143 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3043
  %entry_compressed_written180 = getelementptr inbounds %struct.zip, %struct.zip* %143, i32 0, i32 3, !dbg !3043
  %144 = load i64, i64* %entry_compressed_written180, align 8, !dbg !3043
  %cmp181 = icmp sgt i64 %144, 4294967295, !dbg !3043
  br i1 %cmp181, label %cond.true, label %cond.false, !dbg !3043

cond.true:                                        ; preds = %if.end177
  br label %cond.end, !dbg !3044

cond.false:                                       ; preds = %if.end177
  %145 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3045
  %entry_compressed_written183 = getelementptr inbounds %struct.zip, %struct.zip* %145, i32 0, i32 3, !dbg !3045
  %146 = load i64, i64* %entry_compressed_written183, align 8, !dbg !3045
  br label %cond.end, !dbg !3045

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 4294967295, %cond.true ], [ %146, %cond.false ], !dbg !3047
  %conv184 = trunc i64 %cond to i32, !dbg !3049
  call void @archive_le32enc(i8* %add.ptr179, i32 %conv184), !dbg !3050
  %147 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3051
  %file_header185 = getelementptr inbounds %struct.zip, %struct.zip* %147, i32 0, i32 21, !dbg !3052
  %148 = load i8*, i8** %file_header185, align 8, !dbg !3052
  %add.ptr186 = getelementptr inbounds i8, i8* %148, i64 24, !dbg !3053
  %149 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3054
  %entry_uncompressed_written187 = getelementptr inbounds %struct.zip, %struct.zip* %149, i32 0, i32 4, !dbg !3054
  %150 = load i64, i64* %entry_uncompressed_written187, align 8, !dbg !3054
  %cmp188 = icmp sgt i64 %150, 4294967295, !dbg !3054
  br i1 %cmp188, label %cond.true190, label %cond.false191, !dbg !3054

cond.true190:                                     ; preds = %cond.end
  br label %cond.end193, !dbg !3055

cond.false191:                                    ; preds = %cond.end
  %151 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3056
  %entry_uncompressed_written192 = getelementptr inbounds %struct.zip, %struct.zip* %151, i32 0, i32 4, !dbg !3056
  %152 = load i64, i64* %entry_uncompressed_written192, align 8, !dbg !3056
  br label %cond.end193, !dbg !3056

cond.end193:                                      ; preds = %cond.false191, %cond.true190
  %cond194 = phi i64 [ 4294967295, %cond.true190 ], [ %152, %cond.false191 ], !dbg !3057
  %conv195 = trunc i64 %cond194 to i32, !dbg !3058
  call void @archive_le32enc(i8* %add.ptr186, i32 %conv195), !dbg !3059
  %153 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3060
  %file_header196 = getelementptr inbounds %struct.zip, %struct.zip* %153, i32 0, i32 21, !dbg !3061
  %154 = load i8*, i8** %file_header196, align 8, !dbg !3061
  %add.ptr197 = getelementptr inbounds i8, i8* %154, i64 30, !dbg !3062
  %155 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3063
  %central_directory_bytes = getelementptr inbounds %struct.zip, %struct.zip* %155, i32 0, i32 26, !dbg !3064
  %156 = load i64, i64* %central_directory_bytes, align 8, !dbg !3064
  %157 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3065
  %file_header_extra_offset = getelementptr inbounds %struct.zip, %struct.zip* %157, i32 0, i32 22, !dbg !3066
  %158 = load i64, i64* %file_header_extra_offset, align 8, !dbg !3066
  %sub198 = sub i64 %156, %158, !dbg !3067
  %conv199 = trunc i64 %sub198 to i16, !dbg !3068
  call void @archive_le16enc(i8* %add.ptr197, i16 zeroext %conv199), !dbg !3069
  %159 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3070
  %file_header200 = getelementptr inbounds %struct.zip, %struct.zip* %159, i32 0, i32 21, !dbg !3071
  %160 = load i8*, i8** %file_header200, align 8, !dbg !3071
  %add.ptr201 = getelementptr inbounds i8, i8* %160, i64 42, !dbg !3072
  %161 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3073
  %entry_offset202 = getelementptr inbounds %struct.zip, %struct.zip* %161, i32 0, i32 0, !dbg !3073
  %162 = load i64, i64* %entry_offset202, align 8, !dbg !3073
  %cmp203 = icmp sgt i64 %162, 4294967295, !dbg !3073
  br i1 %cmp203, label %cond.true205, label %cond.false206, !dbg !3073

cond.true205:                                     ; preds = %cond.end193
  br label %cond.end208, !dbg !3074

cond.false206:                                    ; preds = %cond.end193
  %163 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3075
  %entry_offset207 = getelementptr inbounds %struct.zip, %struct.zip* %163, i32 0, i32 0, !dbg !3075
  %164 = load i64, i64* %entry_offset207, align 8, !dbg !3075
  br label %cond.end208, !dbg !3075

cond.end208:                                      ; preds = %cond.false206, %cond.true205
  %cond209 = phi i64 [ 4294967295, %cond.true205 ], [ %164, %cond.false206 ], !dbg !3076
  %conv210 = trunc i64 %cond209 to i32, !dbg !3077
  call void @archive_le32enc(i8* %add.ptr201, i32 %conv210), !dbg !3078
  store i32 0, i32* %retval, align 4, !dbg !3079
  br label %return, !dbg !3079

return:                                           ; preds = %cond.end208, %if.then145, %if.then97, %if.then48, %if.then23, %if.then14, %if.then2
  %165 = load i32, i32* %retval, align 4, !dbg !3080
  ret i32 %165, !dbg !3080
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_zip_close(%struct.archive_write* %a) #0 !dbg !722 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %buff = alloca [64 x i8], align 16
  %offset_start = alloca i64, align 8
  %offset_end = alloca i64, align 8
  %zip = alloca %struct.zip*, align 8
  %segment = alloca %struct.cd_segment*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3081, metadata !728), !dbg !3082
  call void @llvm.dbg.declare(metadata [64 x i8]* %buff, metadata !3083, metadata !728), !dbg !3087
  call void @llvm.dbg.declare(metadata i64* %offset_start, metadata !3088, metadata !728), !dbg !3089
  call void @llvm.dbg.declare(metadata i64* %offset_end, metadata !3090, metadata !728), !dbg !3091
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !3092, metadata !728), !dbg !3093
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3094
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3095
  %1 = load i8*, i8** %format_data, align 8, !dbg !3095
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !3094
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !3093
  call void @llvm.dbg.declare(metadata %struct.cd_segment** %segment, metadata !3096, metadata !728), !dbg !3097
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3098, metadata !728), !dbg !3099
  %3 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3100
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %3, i32 0, i32 28, !dbg !3101
  %4 = load i64, i64* %written_bytes, align 8, !dbg !3101
  store i64 %4, i64* %offset_start, align 8, !dbg !3102
  %5 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3103
  %central_directory = getelementptr inbounds %struct.zip, %struct.zip* %5, i32 0, i32 24, !dbg !3104
  %6 = load %struct.cd_segment*, %struct.cd_segment** %central_directory, align 8, !dbg !3104
  store %struct.cd_segment* %6, %struct.cd_segment** %segment, align 8, !dbg !3105
  br label %while.cond, !dbg !3106

while.cond:                                       ; preds = %if.end, %entry
  %7 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3107
  %cmp = icmp ne %struct.cd_segment* %7, null, !dbg !3109
  br i1 %cmp, label %while.body, label %while.end, !dbg !3110

while.body:                                       ; preds = %while.cond
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3111
  %9 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3113
  %buff1 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %9, i32 0, i32 2, !dbg !3114
  %10 = load i8*, i8** %buff1, align 8, !dbg !3114
  %11 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3115
  %p = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %11, i32 0, i32 3, !dbg !3116
  %12 = load i8*, i8** %p, align 8, !dbg !3116
  %13 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3117
  %buff2 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %13, i32 0, i32 2, !dbg !3118
  %14 = load i8*, i8** %buff2, align 8, !dbg !3118
  %sub.ptr.lhs.cast = ptrtoint i8* %12 to i64, !dbg !3119
  %sub.ptr.rhs.cast = ptrtoint i8* %14 to i64, !dbg !3119
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3119
  %call = call i32 @__archive_write_output(%struct.archive_write* %8, i8* %10, i64 %sub.ptr.sub), !dbg !3120
  store i32 %call, i32* %ret, align 4, !dbg !3121
  %15 = load i32, i32* %ret, align 4, !dbg !3122
  %cmp3 = icmp ne i32 %15, 0, !dbg !3124
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3125

if.then:                                          ; preds = %while.body
  store i32 -30, i32* %retval, align 4, !dbg !3126
  br label %return, !dbg !3126

if.end:                                           ; preds = %while.body
  %16 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3127
  %p4 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %16, i32 0, i32 3, !dbg !3128
  %17 = load i8*, i8** %p4, align 8, !dbg !3128
  %18 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3129
  %buff5 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %18, i32 0, i32 2, !dbg !3130
  %19 = load i8*, i8** %buff5, align 8, !dbg !3130
  %sub.ptr.lhs.cast6 = ptrtoint i8* %17 to i64, !dbg !3131
  %sub.ptr.rhs.cast7 = ptrtoint i8* %19 to i64, !dbg !3131
  %sub.ptr.sub8 = sub i64 %sub.ptr.lhs.cast6, %sub.ptr.rhs.cast7, !dbg !3131
  %20 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3132
  %written_bytes9 = getelementptr inbounds %struct.zip, %struct.zip* %20, i32 0, i32 28, !dbg !3133
  %21 = load i64, i64* %written_bytes9, align 8, !dbg !3134
  %add = add nsw i64 %21, %sub.ptr.sub8, !dbg !3134
  store i64 %add, i64* %written_bytes9, align 8, !dbg !3134
  %22 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3135
  %next = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %22, i32 0, i32 0, !dbg !3136
  %23 = load %struct.cd_segment*, %struct.cd_segment** %next, align 8, !dbg !3136
  store %struct.cd_segment* %23, %struct.cd_segment** %segment, align 8, !dbg !3137
  br label %while.cond, !dbg !3138

while.end:                                        ; preds = %while.cond
  %24 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3140
  %written_bytes10 = getelementptr inbounds %struct.zip, %struct.zip* %24, i32 0, i32 28, !dbg !3141
  %25 = load i64, i64* %written_bytes10, align 8, !dbg !3141
  store i64 %25, i64* %offset_end, align 8, !dbg !3142
  %26 = load i64, i64* %offset_end, align 8, !dbg !3143
  %27 = load i64, i64* %offset_start, align 8, !dbg !3145
  %sub = sub nsw i64 %26, %27, !dbg !3146
  %cmp11 = icmp sgt i64 %sub, 4294967295, !dbg !3147
  br i1 %cmp11, label %if.then16, label %lor.lhs.false, !dbg !3148

lor.lhs.false:                                    ; preds = %while.end
  %28 = load i64, i64* %offset_start, align 8, !dbg !3149
  %cmp12 = icmp sgt i64 %28, 4294967295, !dbg !3151
  br i1 %cmp12, label %if.then16, label %lor.lhs.false13, !dbg !3152

lor.lhs.false13:                                  ; preds = %lor.lhs.false
  %29 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3153
  %central_directory_entries = getelementptr inbounds %struct.zip, %struct.zip* %29, i32 0, i32 27, !dbg !3154
  %30 = load i64, i64* %central_directory_entries, align 8, !dbg !3154
  %cmp14 = icmp ugt i64 %30, 65535, !dbg !3155
  br i1 %cmp14, label %if.then16, label %lor.lhs.false15, !dbg !3156

lor.lhs.false15:                                  ; preds = %lor.lhs.false13
  %31 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3157
  %flags = getelementptr inbounds %struct.zip, %struct.zip* %31, i32 0, i32 35, !dbg !3158
  %32 = load i32, i32* %flags, align 8, !dbg !3158
  %and = and i32 %32, 2, !dbg !3159
  %tobool = icmp ne i32 %and, 0, !dbg !3159
  br i1 %tobool, label %if.then16, label %if.end56, !dbg !3160

if.then16:                                        ; preds = %lor.lhs.false15, %lor.lhs.false13, %lor.lhs.false, %while.end
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3161
  call void @llvm.memset.p0i8.i64(i8* %arraydecay, i8 0, i64 56, i32 16, i1 false), !dbg !3161
  %arraydecay17 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3163
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay17, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.53, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !3163
  %arraydecay18 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3164
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay18, i64 4, !dbg !3165
  call void @archive_le64enc(i8* %add.ptr, i64 44), !dbg !3166
  %arraydecay19 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3167
  %add.ptr20 = getelementptr inbounds i8, i8* %arraydecay19, i64 12, !dbg !3168
  call void @archive_le16enc(i8* %add.ptr20, i16 zeroext 45), !dbg !3169
  %arraydecay21 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3170
  %add.ptr22 = getelementptr inbounds i8, i8* %arraydecay21, i64 14, !dbg !3171
  call void @archive_le16enc(i8* %add.ptr22, i16 zeroext 45), !dbg !3172
  %arraydecay23 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3173
  %add.ptr24 = getelementptr inbounds i8, i8* %arraydecay23, i64 24, !dbg !3174
  %33 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3175
  %central_directory_entries25 = getelementptr inbounds %struct.zip, %struct.zip* %33, i32 0, i32 27, !dbg !3176
  %34 = load i64, i64* %central_directory_entries25, align 8, !dbg !3176
  call void @archive_le64enc(i8* %add.ptr24, i64 %34), !dbg !3177
  %arraydecay26 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3178
  %add.ptr27 = getelementptr inbounds i8, i8* %arraydecay26, i64 32, !dbg !3179
  %35 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3180
  %central_directory_entries28 = getelementptr inbounds %struct.zip, %struct.zip* %35, i32 0, i32 27, !dbg !3181
  %36 = load i64, i64* %central_directory_entries28, align 8, !dbg !3181
  call void @archive_le64enc(i8* %add.ptr27, i64 %36), !dbg !3182
  %arraydecay29 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3183
  %add.ptr30 = getelementptr inbounds i8, i8* %arraydecay29, i64 40, !dbg !3184
  %37 = load i64, i64* %offset_end, align 8, !dbg !3185
  %38 = load i64, i64* %offset_start, align 8, !dbg !3186
  %sub31 = sub nsw i64 %37, %38, !dbg !3187
  call void @archive_le64enc(i8* %add.ptr30, i64 %sub31), !dbg !3188
  %arraydecay32 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3189
  %add.ptr33 = getelementptr inbounds i8, i8* %arraydecay32, i64 48, !dbg !3190
  %39 = load i64, i64* %offset_start, align 8, !dbg !3191
  call void @archive_le64enc(i8* %add.ptr33, i64 %39), !dbg !3192
  %40 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3193
  %arraydecay34 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3194
  %call35 = call i32 @__archive_write_output(%struct.archive_write* %40, i8* %arraydecay34, i64 56), !dbg !3195
  store i32 %call35, i32* %ret, align 4, !dbg !3196
  %41 = load i32, i32* %ret, align 4, !dbg !3197
  %cmp36 = icmp ne i32 %41, 0, !dbg !3199
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !3200

if.then37:                                        ; preds = %if.then16
  store i32 -30, i32* %retval, align 4, !dbg !3201
  br label %return, !dbg !3201

if.end38:                                         ; preds = %if.then16
  %42 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3202
  %written_bytes39 = getelementptr inbounds %struct.zip, %struct.zip* %42, i32 0, i32 28, !dbg !3203
  %43 = load i64, i64* %written_bytes39, align 8, !dbg !3204
  %add40 = add nsw i64 %43, 56, !dbg !3204
  store i64 %add40, i64* %written_bytes39, align 8, !dbg !3204
  %arraydecay41 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3205
  call void @llvm.memset.p0i8.i64(i8* %arraydecay41, i8 0, i64 20, i32 16, i1 false), !dbg !3205
  %arraydecay42 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3206
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay42, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.54, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !3206
  %arraydecay43 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3207
  %add.ptr44 = getelementptr inbounds i8, i8* %arraydecay43, i64 4, !dbg !3208
  call void @archive_le32enc(i8* %add.ptr44, i32 0), !dbg !3209
  %arraydecay45 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3210
  %add.ptr46 = getelementptr inbounds i8, i8* %arraydecay45, i64 8, !dbg !3211
  %44 = load i64, i64* %offset_end, align 8, !dbg !3212
  call void @archive_le64enc(i8* %add.ptr46, i64 %44), !dbg !3213
  %arraydecay47 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3214
  %add.ptr48 = getelementptr inbounds i8, i8* %arraydecay47, i64 16, !dbg !3215
  call void @archive_le32enc(i8* %add.ptr48, i32 1), !dbg !3216
  %45 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3217
  %arraydecay49 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3218
  %call50 = call i32 @__archive_write_output(%struct.archive_write* %45, i8* %arraydecay49, i64 20), !dbg !3219
  store i32 %call50, i32* %ret, align 4, !dbg !3220
  %46 = load i32, i32* %ret, align 4, !dbg !3221
  %cmp51 = icmp ne i32 %46, 0, !dbg !3223
  br i1 %cmp51, label %if.then52, label %if.end53, !dbg !3224

if.then52:                                        ; preds = %if.end38
  store i32 -30, i32* %retval, align 4, !dbg !3225
  br label %return, !dbg !3225

if.end53:                                         ; preds = %if.end38
  %47 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3226
  %written_bytes54 = getelementptr inbounds %struct.zip, %struct.zip* %47, i32 0, i32 28, !dbg !3227
  %48 = load i64, i64* %written_bytes54, align 8, !dbg !3228
  %add55 = add nsw i64 %48, 20, !dbg !3228
  store i64 %add55, i64* %written_bytes54, align 8, !dbg !3228
  br label %if.end56, !dbg !3229

if.end56:                                         ; preds = %if.end53, %lor.lhs.false15
  %arraydecay57 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3230
  call void @llvm.memset.p0i8.i64(i8* %arraydecay57, i8 0, i64 64, i32 16, i1 false), !dbg !3230
  %arraydecay58 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3231
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay58, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.55, i32 0, i32 0), i64 4, i32 1, i1 false), !dbg !3231
  %arraydecay59 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3232
  %add.ptr60 = getelementptr inbounds i8, i8* %arraydecay59, i64 8, !dbg !3233
  %49 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3234
  %central_directory_entries61 = getelementptr inbounds %struct.zip, %struct.zip* %49, i32 0, i32 27, !dbg !3234
  %50 = load i64, i64* %central_directory_entries61, align 8, !dbg !3234
  %cmp62 = icmp ugt i64 65535, %50, !dbg !3234
  br i1 %cmp62, label %cond.true, label %cond.false, !dbg !3234

cond.true:                                        ; preds = %if.end56
  %51 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3235
  %central_directory_entries63 = getelementptr inbounds %struct.zip, %struct.zip* %51, i32 0, i32 27, !dbg !3235
  %52 = load i64, i64* %central_directory_entries63, align 8, !dbg !3235
  br label %cond.end, !dbg !3235

cond.false:                                       ; preds = %if.end56
  br label %cond.end, !dbg !3236

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %52, %cond.true ], [ 65535, %cond.false ], !dbg !3237
  %conv = trunc i64 %cond to i16, !dbg !3239
  call void @archive_le16enc(i8* %add.ptr60, i16 zeroext %conv), !dbg !3240
  %arraydecay64 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3241
  %add.ptr65 = getelementptr inbounds i8, i8* %arraydecay64, i64 10, !dbg !3242
  %53 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3243
  %central_directory_entries66 = getelementptr inbounds %struct.zip, %struct.zip* %53, i32 0, i32 27, !dbg !3243
  %54 = load i64, i64* %central_directory_entries66, align 8, !dbg !3243
  %cmp67 = icmp ugt i64 65535, %54, !dbg !3243
  br i1 %cmp67, label %cond.true69, label %cond.false71, !dbg !3243

cond.true69:                                      ; preds = %cond.end
  %55 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3244
  %central_directory_entries70 = getelementptr inbounds %struct.zip, %struct.zip* %55, i32 0, i32 27, !dbg !3244
  %56 = load i64, i64* %central_directory_entries70, align 8, !dbg !3244
  br label %cond.end72, !dbg !3244

cond.false71:                                     ; preds = %cond.end
  br label %cond.end72, !dbg !3245

cond.end72:                                       ; preds = %cond.false71, %cond.true69
  %cond73 = phi i64 [ %56, %cond.true69 ], [ 65535, %cond.false71 ], !dbg !3246
  %conv74 = trunc i64 %cond73 to i16, !dbg !3247
  call void @archive_le16enc(i8* %add.ptr65, i16 zeroext %conv74), !dbg !3248
  %arraydecay75 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3249
  %add.ptr76 = getelementptr inbounds i8, i8* %arraydecay75, i64 12, !dbg !3250
  %57 = load i64, i64* %offset_end, align 8, !dbg !3251
  %58 = load i64, i64* %offset_start, align 8, !dbg !3251
  %sub77 = sub nsw i64 %57, %58, !dbg !3251
  %cmp78 = icmp sgt i64 4294967295, %sub77, !dbg !3251
  br i1 %cmp78, label %cond.true80, label %cond.false82, !dbg !3251

cond.true80:                                      ; preds = %cond.end72
  %59 = load i64, i64* %offset_end, align 8, !dbg !3252
  %60 = load i64, i64* %offset_start, align 8, !dbg !3252
  %sub81 = sub nsw i64 %59, %60, !dbg !3252
  br label %cond.end83, !dbg !3252

cond.false82:                                     ; preds = %cond.end72
  br label %cond.end83, !dbg !3253

cond.end83:                                       ; preds = %cond.false82, %cond.true80
  %cond84 = phi i64 [ %sub81, %cond.true80 ], [ 4294967295, %cond.false82 ], !dbg !3254
  %conv85 = trunc i64 %cond84 to i32, !dbg !3255
  call void @archive_le32enc(i8* %add.ptr76, i32 %conv85), !dbg !3256
  %arraydecay86 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3257
  %add.ptr87 = getelementptr inbounds i8, i8* %arraydecay86, i64 16, !dbg !3258
  %61 = load i64, i64* %offset_start, align 8, !dbg !3259
  %cmp88 = icmp sgt i64 4294967295, %61, !dbg !3259
  br i1 %cmp88, label %cond.true90, label %cond.false91, !dbg !3259

cond.true90:                                      ; preds = %cond.end83
  %62 = load i64, i64* %offset_start, align 8, !dbg !3260
  br label %cond.end92, !dbg !3260

cond.false91:                                     ; preds = %cond.end83
  br label %cond.end92, !dbg !3261

cond.end92:                                       ; preds = %cond.false91, %cond.true90
  %cond93 = phi i64 [ %62, %cond.true90 ], [ 4294967295, %cond.false91 ], !dbg !3262
  %conv94 = trunc i64 %cond93 to i32, !dbg !3263
  call void @archive_le32enc(i8* %add.ptr87, i32 %conv94), !dbg !3264
  %63 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3265
  %arraydecay95 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3266
  %call96 = call i32 @__archive_write_output(%struct.archive_write* %63, i8* %arraydecay95, i64 22), !dbg !3267
  store i32 %call96, i32* %ret, align 4, !dbg !3268
  %64 = load i32, i32* %ret, align 4, !dbg !3269
  %cmp97 = icmp ne i32 %64, 0, !dbg !3271
  br i1 %cmp97, label %if.then99, label %if.end100, !dbg !3272

if.then99:                                        ; preds = %cond.end92
  store i32 -30, i32* %retval, align 4, !dbg !3273
  br label %return, !dbg !3273

if.end100:                                        ; preds = %cond.end92
  %65 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3274
  %written_bytes101 = getelementptr inbounds %struct.zip, %struct.zip* %65, i32 0, i32 28, !dbg !3275
  %66 = load i64, i64* %written_bytes101, align 8, !dbg !3276
  %add102 = add nsw i64 %66, 22, !dbg !3276
  store i64 %add102, i64* %written_bytes101, align 8, !dbg !3276
  store i32 0, i32* %retval, align 4, !dbg !3277
  br label %return, !dbg !3277

return:                                           ; preds = %if.end100, %if.then99, %if.then52, %if.then37, %if.then
  %67 = load i32, i32* %retval, align 4, !dbg !3278
  ret i32 %67, !dbg !3278
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_zip_free(%struct.archive_write* %a) #0 !dbg !723 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %segment = alloca %struct.cd_segment*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3279, metadata !728), !dbg !3280
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !3281, metadata !728), !dbg !3282
  call void @llvm.dbg.declare(metadata %struct.cd_segment** %segment, metadata !3283, metadata !728), !dbg !3284
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3285
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3286
  %1 = load i8*, i8** %format_data, align 8, !dbg !3286
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !3285
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !3287
  br label %while.cond, !dbg !3288

while.cond:                                       ; preds = %while.body, %entry
  %3 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3289
  %central_directory = getelementptr inbounds %struct.zip, %struct.zip* %3, i32 0, i32 24, !dbg !3291
  %4 = load %struct.cd_segment*, %struct.cd_segment** %central_directory, align 8, !dbg !3291
  %cmp = icmp ne %struct.cd_segment* %4, null, !dbg !3292
  br i1 %cmp, label %while.body, label %while.end, !dbg !3293

while.body:                                       ; preds = %while.cond
  %5 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3294
  %central_directory1 = getelementptr inbounds %struct.zip, %struct.zip* %5, i32 0, i32 24, !dbg !3296
  %6 = load %struct.cd_segment*, %struct.cd_segment** %central_directory1, align 8, !dbg !3296
  store %struct.cd_segment* %6, %struct.cd_segment** %segment, align 8, !dbg !3297
  %7 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3298
  %next = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %7, i32 0, i32 0, !dbg !3299
  %8 = load %struct.cd_segment*, %struct.cd_segment** %next, align 8, !dbg !3299
  %9 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3300
  %central_directory2 = getelementptr inbounds %struct.zip, %struct.zip* %9, i32 0, i32 24, !dbg !3301
  store %struct.cd_segment* %8, %struct.cd_segment** %central_directory2, align 8, !dbg !3302
  %10 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3303
  %buff = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %10, i32 0, i32 2, !dbg !3304
  %11 = load i8*, i8** %buff, align 8, !dbg !3304
  call void @free(i8* %11) #8, !dbg !3305
  %12 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3306
  %13 = bitcast %struct.cd_segment* %12 to i8*, !dbg !3306
  call void @free(i8* %13) #8, !dbg !3307
  br label %while.cond, !dbg !3308

while.end:                                        ; preds = %while.cond
  %14 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3310
  %buf = getelementptr inbounds %struct.zip, %struct.zip* %14, i32 0, i32 38, !dbg !3311
  %15 = load i8*, i8** %buf, align 8, !dbg !3311
  call void @free(i8* %15) #8, !dbg !3312
  %16 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3313
  %entry3 = getelementptr inbounds %struct.zip, %struct.zip* %16, i32 0, i32 6, !dbg !3314
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry3, align 8, !dbg !3314
  call void @archive_entry_free(%struct.archive_entry* %17), !dbg !3315
  %18 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3316
  %cctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %18, i32 0, i32 18, !dbg !3318
  %19 = load i8, i8* %cctx_valid, align 8, !dbg !3318
  %tobool = icmp ne i8 %19, 0, !dbg !3316
  br i1 %tobool, label %if.then, label %if.end, !dbg !3319

if.then:                                          ; preds = %while.end
  %20 = load i32 (i32*)*, i32 (i32*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 6), align 8, !dbg !3320
  %21 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3320
  %cctx = getelementptr inbounds %struct.zip, %struct.zip* %21, i32 0, i32 17, !dbg !3320
  %call = call i32 %20(i32* %cctx), !dbg !3320
  br label %if.end, !dbg !3320

if.end:                                           ; preds = %if.then, %while.end
  %22 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3321
  %hctx_valid = getelementptr inbounds %struct.zip, %struct.zip* %22, i32 0, i32 20, !dbg !3323
  %23 = load i8, i8* %hctx_valid, align 8, !dbg !3323
  %tobool4 = icmp ne i8 %23, 0, !dbg !3321
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !3324

if.then5:                                         ; preds = %if.end
  %24 = load void (i32*)*, void (i32*)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 3), align 8, !dbg !3325
  %25 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3325
  %hctx = getelementptr inbounds %struct.zip, %struct.zip* %25, i32 0, i32 19, !dbg !3325
  call void %24(i32* %hctx), !dbg !3325
  br label %if.end6, !dbg !3325

if.end6:                                          ; preds = %if.then5, %if.end
  %26 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3326
  %27 = bitcast %struct.zip* %26 to i8*, !dbg !3326
  call void @free(i8* %27) #8, !dbg !3327
  %28 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3328
  %format_data7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 14, !dbg !3329
  store i8* null, i8** %format_data7, align 8, !dbg !3330
  ret i32 0, !dbg !3331
}

declare i64 @cm_zlib_crc32(i64, i8*, i32) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @is_traditional_pkware_encryption_supported() #0 !dbg !658 {
entry:
  %retval = alloca i32, align 4
  %key = alloca [12 x i8], align 1
  call void @llvm.dbg.declare(metadata [12 x i8]* %key, metadata !3332, metadata !728), !dbg !3336
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %key, i32 0, i32 0, !dbg !3337
  %call = call i32 @archive_random(i8* %arraydecay, i64 11), !dbg !3339
  %cmp = icmp ne i32 %call, 0, !dbg !3340
  br i1 %cmp, label %if.then, label %if.end, !dbg !3341

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3342
  br label %return, !dbg !3342

if.end:                                           ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3343
  br label %return, !dbg !3343

return:                                           ; preds = %if.end, %if.then
  %0 = load i32, i32* %retval, align 4, !dbg !3344
  ret i32 %0, !dbg !3344
}

; Function Attrs: nounwind uwtable
define internal i32 @is_winzip_aes_encryption_supported(i32 %encryption) #0 !dbg !661 {
entry:
  %retval = alloca i32, align 4
  %encryption.addr = alloca i32, align 4
  %key_len = alloca i64, align 8
  %salt_len = alloca i64, align 8
  %salt = alloca [18 x i8], align 16
  %derived_key = alloca [66 x i8], align 16
  %cctx = alloca i32, align 4
  %hctx = alloca i32, align 4
  %ret = alloca i32, align 4
  store i32 %encryption, i32* %encryption.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %encryption.addr, metadata !3345, metadata !728), !dbg !3346
  call void @llvm.dbg.declare(metadata i64* %key_len, metadata !3347, metadata !728), !dbg !3348
  call void @llvm.dbg.declare(metadata i64* %salt_len, metadata !3349, metadata !728), !dbg !3350
  call void @llvm.dbg.declare(metadata [18 x i8]* %salt, metadata !3351, metadata !728), !dbg !3355
  call void @llvm.dbg.declare(metadata [66 x i8]* %derived_key, metadata !3356, metadata !728), !dbg !3360
  call void @llvm.dbg.declare(metadata i32* %cctx, metadata !3361, metadata !728), !dbg !3362
  call void @llvm.dbg.declare(metadata i32* %hctx, metadata !3363, metadata !728), !dbg !3364
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3365, metadata !728), !dbg !3366
  %0 = load i32, i32* %encryption.addr, align 4, !dbg !3367
  %cmp = icmp eq i32 %0, 2, !dbg !3369
  br i1 %cmp, label %if.then, label %if.else, !dbg !3370

if.then:                                          ; preds = %entry
  store i64 8, i64* %salt_len, align 8, !dbg !3371
  store i64 16, i64* %key_len, align 8, !dbg !3373
  br label %if.end, !dbg !3374

if.else:                                          ; preds = %entry
  store i64 16, i64* %salt_len, align 8, !dbg !3375
  store i64 32, i64* %key_len, align 8, !dbg !3377
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %arraydecay = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i32 0, i32 0, !dbg !3378
  %1 = load i64, i64* %salt_len, align 8, !dbg !3380
  %call = call i32 @archive_random(i8* %arraydecay, i64 %1), !dbg !3381
  %cmp1 = icmp ne i32 %call, 0, !dbg !3382
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3383

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3384
  br label %return, !dbg !3384

if.end3:                                          ; preds = %if.end
  %2 = load i32 (i8*, i64, i8*, i64, i32, i8*, i64)*, i32 (i8*, i64, i8*, i64, i32, i8*, i64)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 0), align 8, !dbg !3385
  %arraydecay4 = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i32 0, i32 0, !dbg !3385
  %3 = load i64, i64* %salt_len, align 8, !dbg !3385
  %arraydecay5 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3385
  %4 = load i64, i64* %key_len, align 8, !dbg !3385
  %mul = mul i64 %4, 2, !dbg !3385
  %add = add i64 %mul, 2, !dbg !3385
  %call6 = call i32 %2(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0), i64 1, i8* %arraydecay4, i64 %3, i32 1000, i8* %arraydecay5, i64 %add), !dbg !3385
  store i32 %call6, i32* %ret, align 4, !dbg !3386
  %5 = load i32, i32* %ret, align 4, !dbg !3387
  %cmp7 = icmp ne i32 %5, 0, !dbg !3389
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !3390

if.then8:                                         ; preds = %if.end3
  store i32 0, i32* %retval, align 4, !dbg !3391
  br label %return, !dbg !3391

if.end9:                                          ; preds = %if.end3
  %6 = load i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 4), align 8, !dbg !3392
  %arraydecay10 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3392
  %7 = load i64, i64* %key_len, align 8, !dbg !3392
  %call11 = call i32 %6(i32* %cctx, i8* %arraydecay10, i64 %7), !dbg !3392
  store i32 %call11, i32* %ret, align 4, !dbg !3393
  %8 = load i32, i32* %ret, align 4, !dbg !3394
  %cmp12 = icmp ne i32 %8, 0, !dbg !3396
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !3397

if.then13:                                        ; preds = %if.end9
  store i32 0, i32* %retval, align 4, !dbg !3398
  br label %return, !dbg !3398

if.end14:                                         ; preds = %if.end9
  %9 = load i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 0), align 8, !dbg !3399
  %arraydecay15 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3399
  %10 = load i64, i64* %key_len, align 8, !dbg !3399
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay15, i64 %10, !dbg !3399
  %11 = load i64, i64* %key_len, align 8, !dbg !3399
  %call16 = call i32 %9(i32* %hctx, i8* %add.ptr, i64 %11), !dbg !3399
  store i32 %call16, i32* %ret, align 4, !dbg !3400
  %12 = load i32 (i32*)*, i32 (i32*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 6), align 8, !dbg !3401
  %call17 = call i32 %12(i32* %cctx), !dbg !3401
  %13 = load i32, i32* %ret, align 4, !dbg !3402
  %cmp18 = icmp ne i32 %13, 0, !dbg !3404
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !3405

if.then19:                                        ; preds = %if.end14
  store i32 0, i32* %retval, align 4, !dbg !3406
  br label %return, !dbg !3406

if.end20:                                         ; preds = %if.end14
  %14 = load void (i32*)*, void (i32*)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 3), align 8, !dbg !3407
  call void %14(i32* %hctx), !dbg !3407
  store i32 1, i32* %retval, align 4, !dbg !3408
  br label %return, !dbg !3408

return:                                           ; preds = %if.end20, %if.then19, %if.then13, %if.then8, %if.then2
  %15 = load i32, i32* %retval, align 4, !dbg !3409
  ret i32 %15, !dbg !3409
}

; Function Attrs: nounwind uwtable
define internal i64 @fake_crc32(i64 %crc, i8* %buff, i64 %len) #0 !dbg !664 {
entry:
  %crc.addr = alloca i64, align 8
  %buff.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  store i64 %crc, i64* %crc.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %crc.addr, metadata !3410, metadata !728), !dbg !3411
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !3412, metadata !728), !dbg !3413
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3414, metadata !728), !dbg !3415
  %0 = load i64, i64* %crc.addr, align 8, !dbg !3416
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !3417
  %2 = load i64, i64* %len.addr, align 8, !dbg !3418
  ret i64 0, !dbg !3419
}

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare i32 @archive_random(i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal %struct.archive_string_conv* @get_sconv(%struct.archive_write* %a, %struct.zip* %zip) #0 !dbg !666 {
entry:
  %retval = alloca %struct.archive_string_conv*, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %zip.addr = alloca %struct.zip*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3420, metadata !728), !dbg !3421
  store %struct.zip* %zip, %struct.zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.zip** %zip.addr, metadata !3422, metadata !728), !dbg !3423
  %0 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3424
  %opt_sconv = getelementptr inbounds %struct.zip, %struct.zip* %0, i32 0, i32 29, !dbg !3426
  %1 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !3426
  %cmp = icmp ne %struct.archive_string_conv* %1, null, !dbg !3427
  br i1 %cmp, label %if.then, label %if.end, !dbg !3428

if.then:                                          ; preds = %entry
  %2 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3429
  %opt_sconv1 = getelementptr inbounds %struct.zip, %struct.zip* %2, i32 0, i32 29, !dbg !3430
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv1, align 8, !dbg !3430
  store %struct.archive_string_conv* %3, %struct.archive_string_conv** %retval, align 8, !dbg !3431
  br label %return, !dbg !3431

if.end:                                           ; preds = %entry
  %4 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3432
  %init_default_conversion = getelementptr inbounds %struct.zip, %struct.zip* %4, i32 0, i32 33, !dbg !3434
  %5 = load i32, i32* %init_default_conversion, align 8, !dbg !3434
  %tobool = icmp ne i32 %5, 0, !dbg !3432
  br i1 %tobool, label %if.end4, label %if.then2, !dbg !3435

if.then2:                                         ; preds = %if.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3436
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !3438
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive* %archive), !dbg !3439
  %7 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3440
  %sconv_default = getelementptr inbounds %struct.zip, %struct.zip* %7, i32 0, i32 30, !dbg !3441
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !3442
  %8 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3443
  %init_default_conversion3 = getelementptr inbounds %struct.zip, %struct.zip* %8, i32 0, i32 33, !dbg !3444
  store i32 1, i32* %init_default_conversion3, align 8, !dbg !3445
  br label %if.end4, !dbg !3446

if.end4:                                          ; preds = %if.then2, %if.end
  %9 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3447
  %sconv_default5 = getelementptr inbounds %struct.zip, %struct.zip* %9, i32 0, i32 30, !dbg !3448
  %10 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default5, align 8, !dbg !3448
  store %struct.archive_string_conv* %10, %struct.archive_string_conv** %retval, align 8, !dbg !3449
  br label %return, !dbg !3449

return:                                           ; preds = %if.end4, %if.then
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %retval, align 8, !dbg !3450
  ret %struct.archive_string_conv* %11, !dbg !3450
}

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @archive_entry_size_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

declare %struct.archive_entry* @archive_entry_clone(%struct.archive_entry*) #2

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

declare void @archive_entry_set_pathname(%struct.archive_entry*, i8*) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare void @archive_entry_set_symlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i32 @is_all_ascii(i8* %p) #0 !dbg !669 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %pp = alloca i8*, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3451, metadata !728), !dbg !3452
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !3453, metadata !728), !dbg !3454
  %0 = load i8*, i8** %p.addr, align 8, !dbg !3455
  store i8* %0, i8** %pp, align 8, !dbg !3454
  br label %while.cond, !dbg !3456

while.cond:                                       ; preds = %if.end, %entry
  %1 = load i8*, i8** %pp, align 8, !dbg !3457
  %2 = load i8, i8* %1, align 1, !dbg !3459
  %tobool = icmp ne i8 %2, 0, !dbg !3460
  br i1 %tobool, label %while.body, label %while.end, !dbg !3460

while.body:                                       ; preds = %while.cond
  %3 = load i8*, i8** %pp, align 8, !dbg !3461
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !3461
  store i8* %incdec.ptr, i8** %pp, align 8, !dbg !3461
  %4 = load i8, i8* %3, align 1, !dbg !3464
  %conv = zext i8 %4 to i32, !dbg !3464
  %cmp = icmp sgt i32 %conv, 127, !dbg !3465
  br i1 %cmp, label %if.then, label %if.end, !dbg !3466

if.then:                                          ; preds = %while.body
  store i32 0, i32* %retval, align 4, !dbg !3467
  br label %return, !dbg !3467

if.end:                                           ; preds = %while.body
  br label %while.cond, !dbg !3468

while.end:                                        ; preds = %while.cond
  store i32 1, i32* %retval, align 4, !dbg !3470
  br label %return, !dbg !3470

return:                                           ; preds = %while.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !3471
  ret i32 %5, !dbg !3471
}

; Function Attrs: nounwind
declare i8* @nl_langinfo(i32) #3

; Function Attrs: nounwind uwtable
define internal i64 @path_length(%struct.archive_entry* %entry1) #0 !dbg !672 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %type = alloca i32, align 4
  %path = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3472, metadata !728), !dbg !3473
  call void @llvm.dbg.declare(metadata i32* %type, metadata !3474, metadata !728), !dbg !3475
  call void @llvm.dbg.declare(metadata i8** %path, metadata !3476, metadata !728), !dbg !3477
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3478
  %call = call i32 @archive_entry_filetype(%struct.archive_entry* %0), !dbg !3479
  store i32 %call, i32* %type, align 4, !dbg !3480
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3481
  %call2 = call i8* @archive_entry_pathname(%struct.archive_entry* %1), !dbg !3482
  store i8* %call2, i8** %path, align 8, !dbg !3483
  %2 = load i8*, i8** %path, align 8, !dbg !3484
  %cmp = icmp eq i8* %2, null, !dbg !3486
  br i1 %cmp, label %if.then, label %if.end, !dbg !3487

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !3488
  br label %return, !dbg !3488

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %type, align 4, !dbg !3489
  %cmp3 = icmp eq i32 %3, 16384, !dbg !3491
  br i1 %cmp3, label %land.lhs.true, label %if.else, !dbg !3492

land.lhs.true:                                    ; preds = %if.end
  %4 = load i8*, i8** %path, align 8, !dbg !3493
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !3493
  %5 = load i8, i8* %arrayidx, align 1, !dbg !3493
  %conv = sext i8 %5 to i32, !dbg !3493
  %cmp4 = icmp eq i32 %conv, 0, !dbg !3494
  br i1 %cmp4, label %if.then11, label %lor.lhs.false, !dbg !3495

lor.lhs.false:                                    ; preds = %land.lhs.true
  %6 = load i8*, i8** %path, align 8, !dbg !3496
  %call6 = call i64 @strlen(i8* %6) #9, !dbg !3498
  %sub = sub i64 %call6, 1, !dbg !3499
  %7 = load i8*, i8** %path, align 8, !dbg !3500
  %arrayidx7 = getelementptr inbounds i8, i8* %7, i64 %sub, !dbg !3500
  %8 = load i8, i8* %arrayidx7, align 1, !dbg !3500
  %conv8 = sext i8 %8 to i32, !dbg !3500
  %cmp9 = icmp ne i32 %conv8, 47, !dbg !3501
  br i1 %cmp9, label %if.then11, label %if.else, !dbg !3502

if.then11:                                        ; preds = %lor.lhs.false, %land.lhs.true
  %9 = load i8*, i8** %path, align 8, !dbg !3504
  %call12 = call i64 @strlen(i8* %9) #9, !dbg !3506
  %add = add i64 %call12, 1, !dbg !3507
  store i64 %add, i64* %retval, align 8, !dbg !3508
  br label %return, !dbg !3508

if.else:                                          ; preds = %lor.lhs.false, %if.end
  %10 = load i8*, i8** %path, align 8, !dbg !3509
  %call13 = call i64 @strlen(i8* %10) #9, !dbg !3511
  store i64 %call13, i64* %retval, align 8, !dbg !3512
  br label %return, !dbg !3512

return:                                           ; preds = %if.else, %if.then11, %if.then
  %11 = load i64, i64* %retval, align 8, !dbg !3513
  ret i64 %11, !dbg !3513
}

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le16enc(i8* %pp, i16 zeroext %u) #7 !dbg !675 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i16, align 2
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3514, metadata !728), !dbg !3515
  store i16 %u, i16* %u.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %u.addr, metadata !3516, metadata !728), !dbg !3517
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3518, metadata !728), !dbg !3519
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3520
  store i8* %0, i8** %p, align 8, !dbg !3519
  %1 = load i16, i16* %u.addr, align 2, !dbg !3521
  %conv = zext i16 %1 to i32, !dbg !3521
  %and = and i32 %conv, 255, !dbg !3522
  %conv1 = trunc i32 %and to i8, !dbg !3521
  %2 = load i8*, i8** %p, align 8, !dbg !3523
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !3523
  store i8 %conv1, i8* %arrayidx, align 1, !dbg !3524
  %3 = load i16, i16* %u.addr, align 2, !dbg !3525
  %conv2 = zext i16 %3 to i32, !dbg !3525
  %shr = ashr i32 %conv2, 8, !dbg !3526
  %and3 = and i32 %shr, 255, !dbg !3527
  %conv4 = trunc i32 %and3 to i8, !dbg !3528
  %4 = load i8*, i8** %p, align 8, !dbg !3529
  %arrayidx5 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !3529
  store i8 %conv4, i8* %arrayidx5, align 1, !dbg !3530
  ret void, !dbg !3531
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le32enc(i8* %pp, i32 %u) #7 !dbg !679 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3532, metadata !728), !dbg !3533
  store i32 %u, i32* %u.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %u.addr, metadata !3534, metadata !728), !dbg !3535
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3536, metadata !728), !dbg !3537
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3538
  store i8* %0, i8** %p, align 8, !dbg !3537
  %1 = load i32, i32* %u.addr, align 4, !dbg !3539
  %and = and i32 %1, 255, !dbg !3540
  %conv = trunc i32 %and to i8, !dbg !3539
  %2 = load i8*, i8** %p, align 8, !dbg !3541
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !3541
  store i8 %conv, i8* %arrayidx, align 1, !dbg !3542
  %3 = load i32, i32* %u.addr, align 4, !dbg !3543
  %shr = lshr i32 %3, 8, !dbg !3544
  %and1 = and i32 %shr, 255, !dbg !3545
  %conv2 = trunc i32 %and1 to i8, !dbg !3546
  %4 = load i8*, i8** %p, align 8, !dbg !3547
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !3547
  store i8 %conv2, i8* %arrayidx3, align 1, !dbg !3548
  %5 = load i32, i32* %u.addr, align 4, !dbg !3549
  %shr4 = lshr i32 %5, 16, !dbg !3550
  %and5 = and i32 %shr4, 255, !dbg !3551
  %conv6 = trunc i32 %and5 to i8, !dbg !3552
  %6 = load i8*, i8** %p, align 8, !dbg !3553
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 2, !dbg !3553
  store i8 %conv6, i8* %arrayidx7, align 1, !dbg !3554
  %7 = load i32, i32* %u.addr, align 4, !dbg !3555
  %shr8 = lshr i32 %7, 24, !dbg !3556
  %and9 = and i32 %shr8, 255, !dbg !3557
  %conv10 = trunc i32 %and9 to i8, !dbg !3558
  %8 = load i8*, i8** %p, align 8, !dbg !3559
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 3, !dbg !3559
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !3560
  ret void, !dbg !3561
}

; Function Attrs: nounwind uwtable
define internal i32 @dos_time(i64 %unix_time) #0 !dbg !682 {
entry:
  %unix_time.addr = alloca i64, align 8
  %t = alloca %struct.tm*, align 8
  %dt = alloca i32, align 4
  store i64 %unix_time, i64* %unix_time.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unix_time.addr, metadata !3562, metadata !728), !dbg !3563
  call void @llvm.dbg.declare(metadata %struct.tm** %t, metadata !3564, metadata !728), !dbg !3579
  call void @llvm.dbg.declare(metadata i32* %dt, metadata !3580, metadata !728), !dbg !3581
  %call = call %struct.tm* @localtime(i64* %unix_time.addr) #8, !dbg !3582
  store %struct.tm* %call, %struct.tm** %t, align 8, !dbg !3583
  %0 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3584
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %0, i32 0, i32 5, !dbg !3586
  %1 = load i32, i32* %tm_year, align 4, !dbg !3586
  %cmp = icmp slt i32 %1, 80, !dbg !3587
  br i1 %cmp, label %if.then, label %if.else, !dbg !3588

if.then:                                          ; preds = %entry
  store i32 2162688, i32* %dt, align 4, !dbg !3589
  br label %if.end21, !dbg !3590

if.else:                                          ; preds = %entry
  %2 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3591
  %tm_year1 = getelementptr inbounds %struct.tm, %struct.tm* %2, i32 0, i32 5, !dbg !3593
  %3 = load i32, i32* %tm_year1, align 4, !dbg !3593
  %cmp2 = icmp sgt i32 %3, 207, !dbg !3594
  br i1 %cmp2, label %if.then3, label %if.else4, !dbg !3595

if.then3:                                         ; preds = %if.else
  store i32 -6307971, i32* %dt, align 4, !dbg !3596
  br label %if.end, !dbg !3597

if.else4:                                         ; preds = %if.else
  store i32 0, i32* %dt, align 4, !dbg !3598
  %4 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3600
  %tm_year5 = getelementptr inbounds %struct.tm, %struct.tm* %4, i32 0, i32 5, !dbg !3601
  %5 = load i32, i32* %tm_year5, align 4, !dbg !3601
  %sub = sub nsw i32 %5, 80, !dbg !3602
  %and = and i32 %sub, 127, !dbg !3603
  %shl = shl i32 %and, 9, !dbg !3604
  %6 = load i32, i32* %dt, align 4, !dbg !3605
  %add = add i32 %6, %shl, !dbg !3605
  store i32 %add, i32* %dt, align 4, !dbg !3605
  %7 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3606
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %7, i32 0, i32 4, !dbg !3607
  %8 = load i32, i32* %tm_mon, align 8, !dbg !3607
  %add6 = add nsw i32 %8, 1, !dbg !3608
  %and7 = and i32 %add6, 15, !dbg !3609
  %shl8 = shl i32 %and7, 5, !dbg !3610
  %9 = load i32, i32* %dt, align 4, !dbg !3611
  %add9 = add i32 %9, %shl8, !dbg !3611
  store i32 %add9, i32* %dt, align 4, !dbg !3611
  %10 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3612
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %10, i32 0, i32 3, !dbg !3613
  %11 = load i32, i32* %tm_mday, align 4, !dbg !3613
  %and10 = and i32 %11, 31, !dbg !3614
  %12 = load i32, i32* %dt, align 4, !dbg !3615
  %add11 = add i32 %12, %and10, !dbg !3615
  store i32 %add11, i32* %dt, align 4, !dbg !3615
  %13 = load i32, i32* %dt, align 4, !dbg !3616
  %shl12 = shl i32 %13, 16, !dbg !3616
  store i32 %shl12, i32* %dt, align 4, !dbg !3616
  %14 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3617
  %tm_hour = getelementptr inbounds %struct.tm, %struct.tm* %14, i32 0, i32 2, !dbg !3618
  %15 = load i32, i32* %tm_hour, align 8, !dbg !3618
  %and13 = and i32 %15, 31, !dbg !3619
  %shl14 = shl i32 %and13, 11, !dbg !3620
  %16 = load i32, i32* %dt, align 4, !dbg !3621
  %add15 = add i32 %16, %shl14, !dbg !3621
  store i32 %add15, i32* %dt, align 4, !dbg !3621
  %17 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3622
  %tm_min = getelementptr inbounds %struct.tm, %struct.tm* %17, i32 0, i32 1, !dbg !3623
  %18 = load i32, i32* %tm_min, align 4, !dbg !3623
  %and16 = and i32 %18, 63, !dbg !3624
  %shl17 = shl i32 %and16, 5, !dbg !3625
  %19 = load i32, i32* %dt, align 4, !dbg !3626
  %add18 = add i32 %19, %shl17, !dbg !3626
  store i32 %add18, i32* %dt, align 4, !dbg !3626
  %20 = load %struct.tm*, %struct.tm** %t, align 8, !dbg !3627
  %tm_sec = getelementptr inbounds %struct.tm, %struct.tm* %20, i32 0, i32 0, !dbg !3628
  %21 = load i32, i32* %tm_sec, align 8, !dbg !3628
  %and19 = and i32 %21, 62, !dbg !3629
  %shr = ashr i32 %and19, 1, !dbg !3630
  %22 = load i32, i32* %dt, align 4, !dbg !3631
  %add20 = add i32 %22, %shr, !dbg !3631
  store i32 %add20, i32* %dt, align 4, !dbg !3631
  br label %if.end

if.end:                                           ; preds = %if.else4, %if.then3
  br label %if.end21

if.end21:                                         ; preds = %if.end, %if.then
  %23 = load i32, i32* %dt, align 4, !dbg !3632
  ret i32 %23, !dbg !3633
}

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i8* @cd_alloc(%struct.zip* %zip, i64 %length) #0 !dbg !689 {
entry:
  %retval = alloca i8*, align 8
  %zip.addr = alloca %struct.zip*, align 8
  %length.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  %segment = alloca %struct.cd_segment*, align 8
  store %struct.zip* %zip, %struct.zip** %zip.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.zip** %zip.addr, metadata !3634, metadata !728), !dbg !3635
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !3636, metadata !728), !dbg !3637
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3638, metadata !728), !dbg !3639
  %0 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3640
  %central_directory = getelementptr inbounds %struct.zip, %struct.zip* %0, i32 0, i32 24, !dbg !3642
  %1 = load %struct.cd_segment*, %struct.cd_segment** %central_directory, align 8, !dbg !3642
  %cmp = icmp eq %struct.cd_segment* %1, null, !dbg !3643
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3644

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3645
  %central_directory_last = getelementptr inbounds %struct.zip, %struct.zip* %2, i32 0, i32 25, !dbg !3647
  %3 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last, align 8, !dbg !3647
  %p1 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %3, i32 0, i32 3, !dbg !3648
  %4 = load i8*, i8** %p1, align 8, !dbg !3648
  %5 = load i64, i64* %length.addr, align 8, !dbg !3649
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 %5, !dbg !3650
  %6 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3651
  %central_directory_last2 = getelementptr inbounds %struct.zip, %struct.zip* %6, i32 0, i32 25, !dbg !3652
  %7 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last2, align 8, !dbg !3652
  %buff = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %7, i32 0, i32 2, !dbg !3653
  %8 = load i8*, i8** %buff, align 8, !dbg !3653
  %9 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3654
  %central_directory_last3 = getelementptr inbounds %struct.zip, %struct.zip* %9, i32 0, i32 25, !dbg !3655
  %10 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last3, align 8, !dbg !3655
  %buff_size = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %10, i32 0, i32 1, !dbg !3656
  %11 = load i64, i64* %buff_size, align 8, !dbg !3656
  %add.ptr4 = getelementptr inbounds i8, i8* %8, i64 %11, !dbg !3657
  %cmp5 = icmp ugt i8* %add.ptr, %add.ptr4, !dbg !3658
  br i1 %cmp5, label %if.then, label %if.end26, !dbg !3659

if.then:                                          ; preds = %lor.lhs.false, %entry
  call void @llvm.dbg.declare(metadata %struct.cd_segment** %segment, metadata !3661, metadata !728), !dbg !3663
  %call = call noalias i8* @calloc(i64 1, i64 32) #8, !dbg !3664
  %12 = bitcast i8* %call to %struct.cd_segment*, !dbg !3664
  store %struct.cd_segment* %12, %struct.cd_segment** %segment, align 8, !dbg !3663
  %13 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3665
  %cmp6 = icmp eq %struct.cd_segment* %13, null, !dbg !3667
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !3668

if.then7:                                         ; preds = %if.then
  store i8* null, i8** %retval, align 8, !dbg !3669
  br label %return, !dbg !3669

if.end:                                           ; preds = %if.then
  %14 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3670
  %buff_size8 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %14, i32 0, i32 1, !dbg !3671
  store i64 65536, i64* %buff_size8, align 8, !dbg !3672
  %15 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3673
  %buff_size9 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %15, i32 0, i32 1, !dbg !3674
  %16 = load i64, i64* %buff_size9, align 8, !dbg !3674
  %call10 = call noalias i8* @malloc(i64 %16) #8, !dbg !3675
  %17 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3676
  %buff11 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %17, i32 0, i32 2, !dbg !3677
  store i8* %call10, i8** %buff11, align 8, !dbg !3678
  %18 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3679
  %buff12 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %18, i32 0, i32 2, !dbg !3681
  %19 = load i8*, i8** %buff12, align 8, !dbg !3681
  %cmp13 = icmp eq i8* %19, null, !dbg !3682
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !3683

if.then14:                                        ; preds = %if.end
  %20 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3684
  %21 = bitcast %struct.cd_segment* %20 to i8*, !dbg !3684
  call void @free(i8* %21) #8, !dbg !3686
  store i8* null, i8** %retval, align 8, !dbg !3687
  br label %return, !dbg !3687

if.end15:                                         ; preds = %if.end
  %22 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3688
  %buff16 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %22, i32 0, i32 2, !dbg !3689
  %23 = load i8*, i8** %buff16, align 8, !dbg !3689
  %24 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3690
  %p17 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %24, i32 0, i32 3, !dbg !3691
  store i8* %23, i8** %p17, align 8, !dbg !3692
  %25 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3693
  %central_directory18 = getelementptr inbounds %struct.zip, %struct.zip* %25, i32 0, i32 24, !dbg !3695
  %26 = load %struct.cd_segment*, %struct.cd_segment** %central_directory18, align 8, !dbg !3695
  %cmp19 = icmp eq %struct.cd_segment* %26, null, !dbg !3696
  br i1 %cmp19, label %if.then20, label %if.else, !dbg !3697

if.then20:                                        ; preds = %if.end15
  %27 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3698
  %28 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3700
  %central_directory_last21 = getelementptr inbounds %struct.zip, %struct.zip* %28, i32 0, i32 25, !dbg !3701
  store %struct.cd_segment* %27, %struct.cd_segment** %central_directory_last21, align 8, !dbg !3702
  %29 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3703
  %central_directory22 = getelementptr inbounds %struct.zip, %struct.zip* %29, i32 0, i32 24, !dbg !3704
  store %struct.cd_segment* %27, %struct.cd_segment** %central_directory22, align 8, !dbg !3705
  br label %if.end25, !dbg !3706

if.else:                                          ; preds = %if.end15
  %30 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3707
  %31 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3709
  %central_directory_last23 = getelementptr inbounds %struct.zip, %struct.zip* %31, i32 0, i32 25, !dbg !3710
  %32 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last23, align 8, !dbg !3710
  %next = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %32, i32 0, i32 0, !dbg !3711
  store %struct.cd_segment* %30, %struct.cd_segment** %next, align 8, !dbg !3712
  %33 = load %struct.cd_segment*, %struct.cd_segment** %segment, align 8, !dbg !3713
  %34 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3714
  %central_directory_last24 = getelementptr inbounds %struct.zip, %struct.zip* %34, i32 0, i32 25, !dbg !3715
  store %struct.cd_segment* %33, %struct.cd_segment** %central_directory_last24, align 8, !dbg !3716
  br label %if.end25

if.end25:                                         ; preds = %if.else, %if.then20
  br label %if.end26, !dbg !3717

if.end26:                                         ; preds = %if.end25, %lor.lhs.false
  %35 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3718
  %central_directory_last27 = getelementptr inbounds %struct.zip, %struct.zip* %35, i32 0, i32 25, !dbg !3719
  %36 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last27, align 8, !dbg !3719
  %p28 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %36, i32 0, i32 3, !dbg !3720
  %37 = load i8*, i8** %p28, align 8, !dbg !3720
  store i8* %37, i8** %p, align 8, !dbg !3721
  %38 = load i64, i64* %length.addr, align 8, !dbg !3722
  %39 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3723
  %central_directory_last29 = getelementptr inbounds %struct.zip, %struct.zip* %39, i32 0, i32 25, !dbg !3724
  %40 = load %struct.cd_segment*, %struct.cd_segment** %central_directory_last29, align 8, !dbg !3724
  %p30 = getelementptr inbounds %struct.cd_segment, %struct.cd_segment* %40, i32 0, i32 3, !dbg !3725
  %41 = load i8*, i8** %p30, align 8, !dbg !3726
  %add.ptr31 = getelementptr inbounds i8, i8* %41, i64 %38, !dbg !3726
  store i8* %add.ptr31, i8** %p30, align 8, !dbg !3726
  %42 = load i64, i64* %length.addr, align 8, !dbg !3727
  %43 = load %struct.zip*, %struct.zip** %zip.addr, align 8, !dbg !3728
  %central_directory_bytes = getelementptr inbounds %struct.zip, %struct.zip* %43, i32 0, i32 26, !dbg !3729
  %44 = load i64, i64* %central_directory_bytes, align 8, !dbg !3730
  %add = add i64 %44, %42, !dbg !3730
  store i64 %add, i64* %central_directory_bytes, align 8, !dbg !3730
  %45 = load i8*, i8** %p, align 8, !dbg !3731
  store i8* %45, i8** %retval, align 8, !dbg !3732
  br label %return, !dbg !3732

return:                                           ; preds = %if.end26, %if.then14, %if.then7
  %46 = load i8*, i8** %retval, align 8, !dbg !3733
  ret i8* %46, !dbg !3733
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal void @copy_path(%struct.archive_entry* %entry1, i8* %p) #0 !dbg !692 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8*, align 8
  %path = alloca i8*, align 8
  %pathlen = alloca i64, align 8
  %type = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3734, metadata !728), !dbg !3735
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3736, metadata !728), !dbg !3737
  call void @llvm.dbg.declare(metadata i8** %path, metadata !3738, metadata !728), !dbg !3739
  call void @llvm.dbg.declare(metadata i64* %pathlen, metadata !3740, metadata !728), !dbg !3741
  call void @llvm.dbg.declare(metadata i32* %type, metadata !3742, metadata !728), !dbg !3743
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3744
  %call = call i8* @archive_entry_pathname(%struct.archive_entry* %0), !dbg !3745
  store i8* %call, i8** %path, align 8, !dbg !3746
  %1 = load i8*, i8** %path, align 8, !dbg !3747
  %call2 = call i64 @strlen(i8* %1) #9, !dbg !3748
  store i64 %call2, i64* %pathlen, align 8, !dbg !3749
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3750
  %call3 = call i32 @archive_entry_filetype(%struct.archive_entry* %2), !dbg !3751
  store i32 %call3, i32* %type, align 4, !dbg !3752
  %3 = load i8*, i8** %p.addr, align 8, !dbg !3753
  %4 = load i8*, i8** %path, align 8, !dbg !3754
  %5 = load i64, i64* %pathlen, align 8, !dbg !3755
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 %5, i32 1, i1 false), !dbg !3756
  %6 = load i32, i32* %type, align 4, !dbg !3757
  %cmp = icmp eq i32 %6, 16384, !dbg !3759
  %conv = zext i1 %cmp to i32, !dbg !3759
  %7 = load i64, i64* %pathlen, align 8, !dbg !3760
  %sub = sub i64 %7, 1, !dbg !3761
  %8 = load i8*, i8** %path, align 8, !dbg !3762
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 %sub, !dbg !3762
  %9 = load i8, i8* %arrayidx, align 1, !dbg !3762
  %conv4 = sext i8 %9 to i32, !dbg !3762
  %cmp5 = icmp ne i32 %conv4, 47, !dbg !3763
  %conv6 = zext i1 %cmp5 to i32, !dbg !3763
  %and = and i32 %conv, %conv6, !dbg !3764
  %tobool = icmp ne i32 %and, 0, !dbg !3764
  br i1 %tobool, label %if.then, label %if.end, !dbg !3765

if.then:                                          ; preds = %entry
  %10 = load i64, i64* %pathlen, align 8, !dbg !3766
  %11 = load i8*, i8** %p.addr, align 8, !dbg !3768
  %arrayidx7 = getelementptr inbounds i8, i8* %11, i64 %10, !dbg !3768
  store i8 47, i8* %arrayidx7, align 1, !dbg !3769
  %12 = load i64, i64* %pathlen, align 8, !dbg !3770
  %add = add i64 %12, 1, !dbg !3771
  %13 = load i8*, i8** %p.addr, align 8, !dbg !3772
  %arrayidx8 = getelementptr inbounds i8, i8* %13, i64 %add, !dbg !3772
  store i8 0, i8* %arrayidx8, align 1, !dbg !3773
  br label %if.end, !dbg !3774

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !3775
}

declare i32 @archive_entry_mtime_is_set(%struct.archive_entry*) #2

declare i32 @archive_entry_atime_is_set(%struct.archive_entry*) #2

declare i32 @archive_entry_ctime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_atime(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le64enc(i8* %pp, i64 %u) #7 !dbg !695 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3776, metadata !728), !dbg !3777
  store i64 %u, i64* %u.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %u.addr, metadata !3778, metadata !728), !dbg !3779
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3780, metadata !728), !dbg !3781
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3782
  store i8* %0, i8** %p, align 8, !dbg !3781
  %1 = load i8*, i8** %p, align 8, !dbg !3783
  %2 = load i64, i64* %u.addr, align 8, !dbg !3784
  %and = and i64 %2, 4294967295, !dbg !3785
  %conv = trunc i64 %and to i32, !dbg !3786
  call void @archive_le32enc(i8* %1, i32 %conv), !dbg !3787
  %3 = load i8*, i8** %p, align 8, !dbg !3788
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !3789
  %4 = load i64, i64* %u.addr, align 8, !dbg !3790
  %shr = lshr i64 %4, 32, !dbg !3791
  %conv1 = trunc i64 %shr to i32, !dbg !3792
  call void @archive_le32enc(i8* %add.ptr, i32 %conv1), !dbg !3793
  ret void, !dbg !3794
}

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @write_path(%struct.archive_entry* %entry1, %struct.archive_write* %archive) #0 !dbg !698 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %archive.addr = alloca %struct.archive_write*, align 8
  %ret = alloca i32, align 4
  %path = alloca i8*, align 8
  %type = alloca i32, align 4
  %written_bytes = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3795, metadata !728), !dbg !3796
  store %struct.archive_write* %archive, %struct.archive_write** %archive.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %archive.addr, metadata !3797, metadata !728), !dbg !3798
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3799, metadata !728), !dbg !3800
  call void @llvm.dbg.declare(metadata i8** %path, metadata !3801, metadata !728), !dbg !3802
  call void @llvm.dbg.declare(metadata i32* %type, metadata !3803, metadata !728), !dbg !3804
  call void @llvm.dbg.declare(metadata i64* %written_bytes, metadata !3805, metadata !728), !dbg !3806
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3807
  %call = call i8* @archive_entry_pathname(%struct.archive_entry* %0), !dbg !3808
  store i8* %call, i8** %path, align 8, !dbg !3809
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3810
  %call2 = call i32 @archive_entry_filetype(%struct.archive_entry* %1), !dbg !3811
  store i32 %call2, i32* %type, align 4, !dbg !3812
  store i64 0, i64* %written_bytes, align 8, !dbg !3813
  %2 = load %struct.archive_write*, %struct.archive_write** %archive.addr, align 8, !dbg !3814
  %3 = load i8*, i8** %path, align 8, !dbg !3815
  %4 = load i8*, i8** %path, align 8, !dbg !3816
  %call3 = call i64 @strlen(i8* %4) #9, !dbg !3817
  %call4 = call i32 @__archive_write_output(%struct.archive_write* %2, i8* %3, i64 %call3), !dbg !3818
  store i32 %call4, i32* %ret, align 4, !dbg !3820
  %5 = load i32, i32* %ret, align 4, !dbg !3821
  %cmp = icmp ne i32 %5, 0, !dbg !3823
  br i1 %cmp, label %if.then, label %if.end, !dbg !3824

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !3825
  br label %return, !dbg !3825

if.end:                                           ; preds = %entry
  %6 = load i8*, i8** %path, align 8, !dbg !3826
  %call5 = call i64 @strlen(i8* %6) #9, !dbg !3827
  %7 = load i64, i64* %written_bytes, align 8, !dbg !3828
  %add = add i64 %7, %call5, !dbg !3828
  store i64 %add, i64* %written_bytes, align 8, !dbg !3828
  %8 = load i32, i32* %type, align 4, !dbg !3829
  %cmp6 = icmp eq i32 %8, 16384, !dbg !3831
  %conv = zext i1 %cmp6 to i32, !dbg !3831
  %9 = load i8*, i8** %path, align 8, !dbg !3832
  %call7 = call i64 @strlen(i8* %9) #9, !dbg !3833
  %sub = sub i64 %call7, 1, !dbg !3834
  %10 = load i8*, i8** %path, align 8, !dbg !3835
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 %sub, !dbg !3835
  %11 = load i8, i8* %arrayidx, align 1, !dbg !3835
  %conv8 = sext i8 %11 to i32, !dbg !3835
  %cmp9 = icmp ne i32 %conv8, 47, !dbg !3836
  %conv10 = zext i1 %cmp9 to i32, !dbg !3836
  %and = and i32 %conv, %conv10, !dbg !3837
  %tobool = icmp ne i32 %and, 0, !dbg !3837
  br i1 %tobool, label %if.then11, label %if.end18, !dbg !3838

if.then11:                                        ; preds = %if.end
  %12 = load %struct.archive_write*, %struct.archive_write** %archive.addr, align 8, !dbg !3839
  %call12 = call i32 @__archive_write_output(%struct.archive_write* %12, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.44, i32 0, i32 0), i64 1), !dbg !3841
  store i32 %call12, i32* %ret, align 4, !dbg !3842
  %13 = load i32, i32* %ret, align 4, !dbg !3843
  %cmp13 = icmp ne i32 %13, 0, !dbg !3845
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !3846

if.then15:                                        ; preds = %if.then11
  store i32 -30, i32* %retval, align 4, !dbg !3847
  br label %return, !dbg !3847

if.end16:                                         ; preds = %if.then11
  %14 = load i64, i64* %written_bytes, align 8, !dbg !3848
  %add17 = add i64 %14, 1, !dbg !3848
  store i64 %add17, i64* %written_bytes, align 8, !dbg !3848
  br label %if.end18, !dbg !3849

if.end18:                                         ; preds = %if.end16, %if.end
  %15 = load i64, i64* %written_bytes, align 8, !dbg !3850
  %conv19 = trunc i64 %15 to i32, !dbg !3851
  store i32 %conv19, i32* %retval, align 4, !dbg !3852
  br label %return, !dbg !3852

return:                                           ; preds = %if.end18, %if.then15, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !3853
  ret i32 %16, !dbg !3853
}

declare i32 @cm_zlib_deflateInit2_(%struct.z_stream_s*, i32, i32, i32, i32, i32, i8*, i32) #2

declare %struct.archive_string_conv* @archive_string_default_conversion_for_write(%struct.archive*) #2

; Function Attrs: nounwind
declare %struct.tm* @localtime(i64*) #3

; Function Attrs: nounwind uwtable
define internal i32 @init_traditional_pkware_encryption(%struct.archive_write* %a) #0 !dbg !702 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %passphrase = alloca i8*, align 8
  %key = alloca [12 x i8], align 1
  %key_encrypted = alloca [12 x i8], align 1
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3854, metadata !728), !dbg !3855
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !3856, metadata !728), !dbg !3857
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3858
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3859
  %1 = load i8*, i8** %format_data, align 8, !dbg !3859
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !3858
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !3857
  call void @llvm.dbg.declare(metadata i8** %passphrase, metadata !3860, metadata !728), !dbg !3861
  call void @llvm.dbg.declare(metadata [12 x i8]* %key, metadata !3862, metadata !728), !dbg !3863
  call void @llvm.dbg.declare(metadata [12 x i8]* %key_encrypted, metadata !3864, metadata !728), !dbg !3865
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3866, metadata !728), !dbg !3867
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3868
  %call = call i8* @__archive_write_get_passphrase(%struct.archive_write* %3), !dbg !3869
  store i8* %call, i8** %passphrase, align 8, !dbg !3870
  %4 = load i8*, i8** %passphrase, align 8, !dbg !3871
  %cmp = icmp eq i8* %4, null, !dbg !3873
  br i1 %cmp, label %if.then, label %if.end, !dbg !3874

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3875
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !3877
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.47, i32 0, i32 0)), !dbg !3878
  store i32 -25, i32* %retval, align 4, !dbg !3879
  br label %return, !dbg !3879

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %key, i32 0, i32 0, !dbg !3880
  %call1 = call i32 @archive_random(i8* %arraydecay, i64 11), !dbg !3882
  %cmp2 = icmp ne i32 %call1, 0, !dbg !3883
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !3884

if.then3:                                         ; preds = %if.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3885
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !3887
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive4, i32 -1, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.48, i32 0, i32 0)), !dbg !3888
  store i32 -30, i32* %retval, align 4, !dbg !3889
  br label %return, !dbg !3889

if.end5:                                          ; preds = %if.end
  %7 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3890
  %tctx = getelementptr inbounds %struct.zip, %struct.zip* %7, i32 0, i32 13, !dbg !3891
  %8 = load i8*, i8** %passphrase, align 8, !dbg !3892
  %9 = load i8*, i8** %passphrase, align 8, !dbg !3893
  %call6 = call i64 @strlen(i8* %9) #9, !dbg !3894
  %call7 = call i32 @trad_enc_init(%struct.trad_enc_ctx* %tctx, i8* %8, i64 %call6), !dbg !3895
  %10 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3897
  %trad_chkdat = getelementptr inbounds %struct.zip, %struct.zip* %10, i32 0, i32 15, !dbg !3898
  %11 = load i8, i8* %trad_chkdat, align 1, !dbg !3898
  %arrayidx = getelementptr inbounds [12 x i8], [12 x i8]* %key, i64 0, i64 11, !dbg !3899
  store i8 %11, i8* %arrayidx, align 1, !dbg !3900
  %12 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3901
  %tctx8 = getelementptr inbounds %struct.zip, %struct.zip* %12, i32 0, i32 13, !dbg !3902
  %arraydecay9 = getelementptr inbounds [12 x i8], [12 x i8]* %key, i32 0, i32 0, !dbg !3903
  %arraydecay10 = getelementptr inbounds [12 x i8], [12 x i8]* %key_encrypted, i32 0, i32 0, !dbg !3904
  %call11 = call i32 @trad_enc_encrypt_update(%struct.trad_enc_ctx* %tctx8, i8* %arraydecay9, i64 12, i8* %arraydecay10, i64 12), !dbg !3905
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3906
  %arraydecay12 = getelementptr inbounds [12 x i8], [12 x i8]* %key_encrypted, i32 0, i32 0, !dbg !3907
  %call13 = call i32 @__archive_write_output(%struct.archive_write* %13, i8* %arraydecay12, i64 12), !dbg !3908
  store i32 %call13, i32* %ret, align 4, !dbg !3909
  %14 = load i32, i32* %ret, align 4, !dbg !3910
  %cmp14 = icmp ne i32 %14, 0, !dbg !3912
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !3913

if.then15:                                        ; preds = %if.end5
  %15 = load i32, i32* %ret, align 4, !dbg !3914
  store i32 %15, i32* %retval, align 4, !dbg !3915
  br label %return, !dbg !3915

if.end16:                                         ; preds = %if.end5
  %16 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3916
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %16, i32 0, i32 28, !dbg !3917
  %17 = load i64, i64* %written_bytes, align 8, !dbg !3918
  %add = add nsw i64 %17, 12, !dbg !3918
  store i64 %add, i64* %written_bytes, align 8, !dbg !3918
  %18 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3919
  %entry_compressed_written = getelementptr inbounds %struct.zip, %struct.zip* %18, i32 0, i32 3, !dbg !3920
  %19 = load i64, i64* %entry_compressed_written, align 8, !dbg !3921
  %add17 = add nsw i64 %19, 12, !dbg !3921
  store i64 %add17, i64* %entry_compressed_written, align 8, !dbg !3921
  %20 = load i32, i32* %ret, align 4, !dbg !3922
  store i32 %20, i32* %retval, align 4, !dbg !3923
  br label %return, !dbg !3923

return:                                           ; preds = %if.end16, %if.then15, %if.then3, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !3924
  ret i32 %21, !dbg !3924
}

; Function Attrs: nounwind uwtable
define internal i32 @init_winzip_aes_encryption(%struct.archive_write* %a) #0 !dbg !710 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %zip = alloca %struct.zip*, align 8
  %passphrase = alloca i8*, align 8
  %key_len = alloca i64, align 8
  %salt_len = alloca i64, align 8
  %salt = alloca [18 x i8], align 16
  %derived_key = alloca [66 x i8], align 16
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3925, metadata !728), !dbg !3926
  call void @llvm.dbg.declare(metadata %struct.zip** %zip, metadata !3927, metadata !728), !dbg !3928
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3929
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !3930
  %1 = load i8*, i8** %format_data, align 8, !dbg !3930
  %2 = bitcast i8* %1 to %struct.zip*, !dbg !3929
  store %struct.zip* %2, %struct.zip** %zip, align 8, !dbg !3928
  call void @llvm.dbg.declare(metadata i8** %passphrase, metadata !3931, metadata !728), !dbg !3932
  call void @llvm.dbg.declare(metadata i64* %key_len, metadata !3933, metadata !728), !dbg !3934
  call void @llvm.dbg.declare(metadata i64* %salt_len, metadata !3935, metadata !728), !dbg !3936
  call void @llvm.dbg.declare(metadata [18 x i8]* %salt, metadata !3937, metadata !728), !dbg !3938
  call void @llvm.dbg.declare(metadata [66 x i8]* %derived_key, metadata !3939, metadata !728), !dbg !3940
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3941, metadata !728), !dbg !3942
  %3 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3943
  %call = call i8* @__archive_write_get_passphrase(%struct.archive_write* %3), !dbg !3944
  store i8* %call, i8** %passphrase, align 8, !dbg !3945
  %4 = load i8*, i8** %passphrase, align 8, !dbg !3946
  %cmp = icmp eq i8* %4, null, !dbg !3948
  br i1 %cmp, label %if.then, label %if.end, !dbg !3949

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3950
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !3952
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.47, i32 0, i32 0)), !dbg !3953
  store i32 -25, i32* %retval, align 4, !dbg !3954
  br label %return, !dbg !3954

if.end:                                           ; preds = %entry
  %6 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3955
  %entry_encryption = getelementptr inbounds %struct.zip, %struct.zip* %6, i32 0, i32 9, !dbg !3957
  %7 = load i32, i32* %entry_encryption, align 8, !dbg !3957
  %cmp1 = icmp eq i32 %7, 2, !dbg !3958
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !3959

if.then2:                                         ; preds = %if.end
  store i64 8, i64* %salt_len, align 8, !dbg !3960
  store i64 16, i64* %key_len, align 8, !dbg !3962
  br label %if.end3, !dbg !3963

if.else:                                          ; preds = %if.end
  store i64 16, i64* %salt_len, align 8, !dbg !3964
  store i64 32, i64* %key_len, align 8, !dbg !3966
  br label %if.end3

if.end3:                                          ; preds = %if.else, %if.then2
  %arraydecay = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i32 0, i32 0, !dbg !3967
  %8 = load i64, i64* %salt_len, align 8, !dbg !3969
  %call4 = call i32 @archive_random(i8* %arraydecay, i64 %8), !dbg !3970
  %cmp5 = icmp ne i32 %call4, 0, !dbg !3971
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !3972

if.then6:                                         ; preds = %if.end3
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3973
  %archive7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !3975
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive7, i32 -1, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.48, i32 0, i32 0)), !dbg !3976
  store i32 -30, i32* %retval, align 4, !dbg !3977
  br label %return, !dbg !3977

if.end8:                                          ; preds = %if.end3
  %10 = load i32 (i8*, i64, i8*, i64, i32, i8*, i64)*, i32 (i8*, i64, i8*, i64, i32, i8*, i64)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 0), align 8, !dbg !3978
  %11 = load i8*, i8** %passphrase, align 8, !dbg !3978
  %12 = load i8*, i8** %passphrase, align 8, !dbg !3978
  %call9 = call i64 @strlen(i8* %12) #9, !dbg !3978
  %arraydecay10 = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i32 0, i32 0, !dbg !3978
  %13 = load i64, i64* %salt_len, align 8, !dbg !3978
  %arraydecay11 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3978
  %14 = load i64, i64* %key_len, align 8, !dbg !3978
  %mul = mul i64 %14, 2, !dbg !3978
  %add = add i64 %mul, 2, !dbg !3978
  %call12 = call i32 %10(i8* %11, i64 %call9, i8* %arraydecay10, i64 %13, i32 1000, i8* %arraydecay11, i64 %add), !dbg !3979
  %15 = load i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 4), align 8, !dbg !3981
  %16 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3981
  %cctx = getelementptr inbounds %struct.zip, %struct.zip* %16, i32 0, i32 17, !dbg !3981
  %arraydecay13 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3981
  %17 = load i64, i64* %key_len, align 8, !dbg !3981
  %call14 = call i32 %15(i32* %cctx, i8* %arraydecay13, i64 %17), !dbg !3981
  store i32 %call14, i32* %ret, align 4, !dbg !3982
  %18 = load i32, i32* %ret, align 4, !dbg !3983
  %cmp15 = icmp ne i32 %18, 0, !dbg !3985
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !3986

if.then16:                                        ; preds = %if.end8
  %19 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3987
  %archive17 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 0, !dbg !3989
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 -1, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.49, i32 0, i32 0)), !dbg !3990
  store i32 -25, i32* %retval, align 4, !dbg !3991
  br label %return, !dbg !3991

if.end18:                                         ; preds = %if.end8
  %20 = load i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64)** getelementptr inbounds (%struct.archive_hmac, %struct.archive_hmac* @__archive_hmac, i32 0, i32 0), align 8, !dbg !3992
  %21 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3992
  %hctx = getelementptr inbounds %struct.zip, %struct.zip* %21, i32 0, i32 19, !dbg !3992
  %arraydecay19 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i32 0, i32 0, !dbg !3992
  %22 = load i64, i64* %key_len, align 8, !dbg !3992
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay19, i64 %22, !dbg !3992
  %23 = load i64, i64* %key_len, align 8, !dbg !3992
  %call20 = call i32 %20(i32* %hctx, i8* %add.ptr, i64 %23), !dbg !3992
  store i32 %call20, i32* %ret, align 4, !dbg !3993
  %24 = load i32, i32* %ret, align 4, !dbg !3994
  %cmp21 = icmp ne i32 %24, 0, !dbg !3996
  br i1 %cmp21, label %if.then22, label %if.end26, !dbg !3997

if.then22:                                        ; preds = %if.end18
  %25 = load i32 (i32*)*, i32 (i32*)** getelementptr inbounds (%struct.archive_cryptor, %struct.archive_cryptor* @__archive_cryptor, i32 0, i32 6), align 8, !dbg !3998
  %26 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !3998
  %cctx23 = getelementptr inbounds %struct.zip, %struct.zip* %26, i32 0, i32 17, !dbg !3998
  %call24 = call i32 %25(i32* %cctx23), !dbg !3998
  %27 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4000
  %archive25 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 0, !dbg !4001
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 -1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.50, i32 0, i32 0)), !dbg !4002
  store i32 -25, i32* %retval, align 4, !dbg !4003
  br label %return, !dbg !4003

if.end26:                                         ; preds = %if.end18
  %28 = load i64, i64* %key_len, align 8, !dbg !4004
  %mul27 = mul i64 %28, 2, !dbg !4005
  %arrayidx = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i64 0, i64 %mul27, !dbg !4006
  %29 = load i8, i8* %arrayidx, align 1, !dbg !4006
  %30 = load i64, i64* %salt_len, align 8, !dbg !4007
  %arrayidx28 = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i64 0, i64 %30, !dbg !4008
  store i8 %29, i8* %arrayidx28, align 1, !dbg !4009
  %31 = load i64, i64* %key_len, align 8, !dbg !4010
  %mul29 = mul i64 %31, 2, !dbg !4011
  %add30 = add i64 %mul29, 1, !dbg !4012
  %arrayidx31 = getelementptr inbounds [66 x i8], [66 x i8]* %derived_key, i64 0, i64 %add30, !dbg !4013
  %32 = load i8, i8* %arrayidx31, align 1, !dbg !4013
  %33 = load i64, i64* %salt_len, align 8, !dbg !4014
  %add32 = add i64 %33, 1, !dbg !4015
  %arrayidx33 = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i64 0, i64 %add32, !dbg !4016
  store i8 %32, i8* %arrayidx33, align 1, !dbg !4017
  %34 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !4018
  %arraydecay34 = getelementptr inbounds [18 x i8], [18 x i8]* %salt, i32 0, i32 0, !dbg !4019
  %35 = load i64, i64* %salt_len, align 8, !dbg !4020
  %add35 = add i64 %35, 2, !dbg !4021
  %call36 = call i32 @__archive_write_output(%struct.archive_write* %34, i8* %arraydecay34, i64 %add35), !dbg !4022
  store i32 %call36, i32* %ret, align 4, !dbg !4023
  %36 = load i32, i32* %ret, align 4, !dbg !4024
  %cmp37 = icmp ne i32 %36, 0, !dbg !4026
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !4027

if.then38:                                        ; preds = %if.end26
  %37 = load i32, i32* %ret, align 4, !dbg !4028
  store i32 %37, i32* %retval, align 4, !dbg !4029
  br label %return, !dbg !4029

if.end39:                                         ; preds = %if.end26
  %38 = load i64, i64* %salt_len, align 8, !dbg !4030
  %add40 = add i64 %38, 2, !dbg !4031
  %39 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !4032
  %written_bytes = getelementptr inbounds %struct.zip, %struct.zip* %39, i32 0, i32 28, !dbg !4033
  %40 = load i64, i64* %written_bytes, align 8, !dbg !4034
  %add41 = add i64 %40, %add40, !dbg !4034
  store i64 %add41, i64* %written_bytes, align 8, !dbg !4034
  %41 = load i64, i64* %salt_len, align 8, !dbg !4035
  %add42 = add i64 %41, 2, !dbg !4036
  %42 = load %struct.zip*, %struct.zip** %zip, align 8, !dbg !4037
  %entry_compressed_written = getelementptr inbounds %struct.zip, %struct.zip* %42, i32 0, i32 3, !dbg !4038
  %43 = load i64, i64* %entry_compressed_written, align 8, !dbg !4039
  %add43 = add i64 %43, %add42, !dbg !4039
  store i64 %add43, i64* %entry_compressed_written, align 8, !dbg !4039
  store i32 0, i32* %retval, align 4, !dbg !4040
  br label %return, !dbg !4040

return:                                           ; preds = %if.end39, %if.then38, %if.then22, %if.then16, %if.then6, %if.then
  %44 = load i32, i32* %retval, align 4, !dbg !4041
  ret i32 %44, !dbg !4041
}

; Function Attrs: nounwind uwtable
define internal i32 @trad_enc_encrypt_update(%struct.trad_enc_ctx* %ctx, i8* %in, i64 %in_len, i8* %out, i64 %out_len) #0 !dbg !711 {
entry:
  %ctx.addr = alloca %struct.trad_enc_ctx*, align 8
  %in.addr = alloca i8*, align 8
  %in_len.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_len.addr = alloca i64, align 8
  %i = alloca i32, align 4
  %max = alloca i32, align 4
  %t = alloca i8, align 1
  store %struct.trad_enc_ctx* %ctx, %struct.trad_enc_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.trad_enc_ctx** %ctx.addr, metadata !4042, metadata !728), !dbg !4043
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !4044, metadata !728), !dbg !4045
  store i64 %in_len, i64* %in_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_len.addr, metadata !4046, metadata !728), !dbg !4047
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !4048, metadata !728), !dbg !4049
  store i64 %out_len, i64* %out_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_len.addr, metadata !4050, metadata !728), !dbg !4051
  call void @llvm.dbg.declare(metadata i32* %i, metadata !4052, metadata !728), !dbg !4053
  call void @llvm.dbg.declare(metadata i32* %max, metadata !4054, metadata !728), !dbg !4055
  %0 = load i64, i64* %in_len.addr, align 8, !dbg !4056
  %1 = load i64, i64* %out_len.addr, align 8, !dbg !4057
  %cmp = icmp ult i64 %0, %1, !dbg !4058
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !4059

cond.true:                                        ; preds = %entry
  %2 = load i64, i64* %in_len.addr, align 8, !dbg !4060
  br label %cond.end, !dbg !4062

cond.false:                                       ; preds = %entry
  %3 = load i64, i64* %out_len.addr, align 8, !dbg !4063
  br label %cond.end, !dbg !4065

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %2, %cond.true ], [ %3, %cond.false ], !dbg !4066
  %conv = trunc i64 %cond to i32, !dbg !4068
  store i32 %conv, i32* %max, align 4, !dbg !4069
  store i32 0, i32* %i, align 4, !dbg !4070
  br label %for.cond, !dbg !4072

for.cond:                                         ; preds = %for.inc, %cond.end
  %4 = load i32, i32* %i, align 4, !dbg !4073
  %5 = load i32, i32* %max, align 4, !dbg !4076
  %cmp1 = icmp ult i32 %4, %5, !dbg !4077
  br i1 %cmp1, label %for.body, label %for.end, !dbg !4078

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8* %t, metadata !4079, metadata !728), !dbg !4081
  %6 = load i32, i32* %i, align 4, !dbg !4082
  %idxprom = zext i32 %6 to i64, !dbg !4083
  %7 = load i8*, i8** %in.addr, align 8, !dbg !4083
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 %idxprom, !dbg !4083
  %8 = load i8, i8* %arrayidx, align 1, !dbg !4083
  store i8 %8, i8* %t, align 1, !dbg !4081
  %9 = load i8, i8* %t, align 1, !dbg !4084
  %conv3 = zext i8 %9 to i32, !dbg !4084
  %10 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4085
  %call = call zeroext i8 @trad_enc_decrypt_byte(%struct.trad_enc_ctx* %10), !dbg !4086
  %conv4 = zext i8 %call to i32, !dbg !4086
  %xor = xor i32 %conv3, %conv4, !dbg !4087
  %conv5 = trunc i32 %xor to i8, !dbg !4084
  %11 = load i32, i32* %i, align 4, !dbg !4088
  %idxprom6 = zext i32 %11 to i64, !dbg !4089
  %12 = load i8*, i8** %out.addr, align 8, !dbg !4089
  %arrayidx7 = getelementptr inbounds i8, i8* %12, i64 %idxprom6, !dbg !4089
  store i8 %conv5, i8* %arrayidx7, align 1, !dbg !4090
  %13 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4091
  %14 = load i8, i8* %t, align 1, !dbg !4092
  call void @trad_enc_update_keys(%struct.trad_enc_ctx* %13, i8 zeroext %14), !dbg !4093
  br label %for.inc, !dbg !4094

for.inc:                                          ; preds = %for.body
  %15 = load i32, i32* %i, align 4, !dbg !4095
  %inc = add i32 %15, 1, !dbg !4095
  store i32 %inc, i32* %i, align 4, !dbg !4095
  br label %for.cond, !dbg !4097

for.end:                                          ; preds = %for.cond
  %16 = load i32, i32* %i, align 4, !dbg !4098
  ret i32 %16, !dbg !4099
}

declare i32 @cm_zlib_deflate(%struct.z_stream_s*, i32) #2

declare i8* @__archive_write_get_passphrase(%struct.archive_write*) #2

; Function Attrs: nounwind uwtable
define internal i32 @trad_enc_init(%struct.trad_enc_ctx* %ctx, i8* %pw, i64 %pw_len) #0 !dbg !703 {
entry:
  %ctx.addr = alloca %struct.trad_enc_ctx*, align 8
  %pw.addr = alloca i8*, align 8
  %pw_len.addr = alloca i64, align 8
  store %struct.trad_enc_ctx* %ctx, %struct.trad_enc_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.trad_enc_ctx** %ctx.addr, metadata !4100, metadata !728), !dbg !4101
  store i8* %pw, i8** %pw.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pw.addr, metadata !4102, metadata !728), !dbg !4103
  store i64 %pw_len, i64* %pw_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %pw_len.addr, metadata !4104, metadata !728), !dbg !4105
  %0 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4106
  %keys = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %0, i32 0, i32 0, !dbg !4107
  %arrayidx = getelementptr inbounds [3 x i32], [3 x i32]* %keys, i64 0, i64 0, !dbg !4106
  store i32 305419896, i32* %arrayidx, align 4, !dbg !4108
  %1 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4109
  %keys1 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %1, i32 0, i32 0, !dbg !4110
  %arrayidx2 = getelementptr inbounds [3 x i32], [3 x i32]* %keys1, i64 0, i64 1, !dbg !4109
  store i32 591751049, i32* %arrayidx2, align 4, !dbg !4111
  %2 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4112
  %keys3 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %2, i32 0, i32 0, !dbg !4113
  %arrayidx4 = getelementptr inbounds [3 x i32], [3 x i32]* %keys3, i64 0, i64 2, !dbg !4112
  store i32 878082192, i32* %arrayidx4, align 4, !dbg !4114
  br label %for.cond, !dbg !4115

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i64, i64* %pw_len.addr, align 8, !dbg !4116
  %tobool = icmp ne i64 %3, 0, !dbg !4120
  br i1 %tobool, label %for.body, label %for.end, !dbg !4120

for.body:                                         ; preds = %for.cond
  %4 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4121
  %5 = load i8*, i8** %pw.addr, align 8, !dbg !4122
  %incdec.ptr = getelementptr inbounds i8, i8* %5, i32 1, !dbg !4122
  store i8* %incdec.ptr, i8** %pw.addr, align 8, !dbg !4122
  %6 = load i8, i8* %5, align 1, !dbg !4123
  call void @trad_enc_update_keys(%struct.trad_enc_ctx* %4, i8 zeroext %6), !dbg !4124
  br label %for.inc, !dbg !4124

for.inc:                                          ; preds = %for.body
  %7 = load i64, i64* %pw_len.addr, align 8, !dbg !4125
  %dec = add i64 %7, -1, !dbg !4125
  store i64 %dec, i64* %pw_len.addr, align 8, !dbg !4125
  br label %for.cond, !dbg !4127

for.end:                                          ; preds = %for.cond
  ret i32 0, !dbg !4128
}

; Function Attrs: nounwind uwtable
define internal void @trad_enc_update_keys(%struct.trad_enc_ctx* %ctx, i8 zeroext %c) #0 !dbg !707 {
entry:
  %ctx.addr = alloca %struct.trad_enc_ctx*, align 8
  %c.addr = alloca i8, align 1
  %t = alloca i8, align 1
  store %struct.trad_enc_ctx* %ctx, %struct.trad_enc_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.trad_enc_ctx** %ctx.addr, metadata !4129, metadata !728), !dbg !4130
  store i8 %c, i8* %c.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %c.addr, metadata !4131, metadata !728), !dbg !4132
  call void @llvm.dbg.declare(metadata i8* %t, metadata !4133, metadata !728), !dbg !4134
  %0 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4135
  %keys = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %0, i32 0, i32 0, !dbg !4135
  %arrayidx = getelementptr inbounds [3 x i32], [3 x i32]* %keys, i64 0, i64 0, !dbg !4135
  %1 = load i32, i32* %arrayidx, align 4, !dbg !4135
  %conv = zext i32 %1 to i64, !dbg !4135
  %xor = xor i64 %conv, 4294967295, !dbg !4135
  %call = call i64 @cm_zlib_crc32(i64 %xor, i8* %c.addr, i32 1), !dbg !4135
  %xor1 = xor i64 %call, 4294967295, !dbg !4135
  %conv2 = trunc i64 %xor1 to i32, !dbg !4135
  %2 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4136
  %keys3 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %2, i32 0, i32 0, !dbg !4137
  %arrayidx4 = getelementptr inbounds [3 x i32], [3 x i32]* %keys3, i64 0, i64 0, !dbg !4136
  store i32 %conv2, i32* %arrayidx4, align 4, !dbg !4138
  %3 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4139
  %keys5 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %3, i32 0, i32 0, !dbg !4140
  %arrayidx6 = getelementptr inbounds [3 x i32], [3 x i32]* %keys5, i64 0, i64 1, !dbg !4139
  %4 = load i32, i32* %arrayidx6, align 4, !dbg !4139
  %5 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4141
  %keys7 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %5, i32 0, i32 0, !dbg !4142
  %arrayidx8 = getelementptr inbounds [3 x i32], [3 x i32]* %keys7, i64 0, i64 0, !dbg !4141
  %6 = load i32, i32* %arrayidx8, align 4, !dbg !4141
  %and = and i32 %6, 255, !dbg !4143
  %add = add i32 %4, %and, !dbg !4144
  %conv9 = zext i32 %add to i64, !dbg !4145
  %mul = mul nsw i64 %conv9, 134775813, !dbg !4146
  %add10 = add nsw i64 %mul, 1, !dbg !4147
  %conv11 = trunc i64 %add10 to i32, !dbg !4145
  %7 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4148
  %keys12 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %7, i32 0, i32 0, !dbg !4149
  %arrayidx13 = getelementptr inbounds [3 x i32], [3 x i32]* %keys12, i64 0, i64 1, !dbg !4148
  store i32 %conv11, i32* %arrayidx13, align 4, !dbg !4150
  %8 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4151
  %keys14 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %8, i32 0, i32 0, !dbg !4152
  %arrayidx15 = getelementptr inbounds [3 x i32], [3 x i32]* %keys14, i64 0, i64 1, !dbg !4151
  %9 = load i32, i32* %arrayidx15, align 4, !dbg !4151
  %shr = lshr i32 %9, 24, !dbg !4153
  %and16 = and i32 %shr, 255, !dbg !4154
  %conv17 = trunc i32 %and16 to i8, !dbg !4155
  store i8 %conv17, i8* %t, align 1, !dbg !4156
  %10 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4157
  %keys18 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %10, i32 0, i32 0, !dbg !4157
  %arrayidx19 = getelementptr inbounds [3 x i32], [3 x i32]* %keys18, i64 0, i64 2, !dbg !4157
  %11 = load i32, i32* %arrayidx19, align 4, !dbg !4157
  %conv20 = zext i32 %11 to i64, !dbg !4157
  %xor21 = xor i64 %conv20, 4294967295, !dbg !4157
  %call22 = call i64 @cm_zlib_crc32(i64 %xor21, i8* %t, i32 1), !dbg !4157
  %xor23 = xor i64 %call22, 4294967295, !dbg !4157
  %conv24 = trunc i64 %xor23 to i32, !dbg !4157
  %12 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4158
  %keys25 = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %12, i32 0, i32 0, !dbg !4159
  %arrayidx26 = getelementptr inbounds [3 x i32], [3 x i32]* %keys25, i64 0, i64 2, !dbg !4158
  store i32 %conv24, i32* %arrayidx26, align 4, !dbg !4160
  ret void, !dbg !4161
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @trad_enc_decrypt_byte(%struct.trad_enc_ctx* %ctx) #0 !dbg !715 {
entry:
  %ctx.addr = alloca %struct.trad_enc_ctx*, align 8
  %temp = alloca i32, align 4
  store %struct.trad_enc_ctx* %ctx, %struct.trad_enc_ctx** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.trad_enc_ctx** %ctx.addr, metadata !4162, metadata !728), !dbg !4163
  call void @llvm.dbg.declare(metadata i32* %temp, metadata !4164, metadata !728), !dbg !4165
  %0 = load %struct.trad_enc_ctx*, %struct.trad_enc_ctx** %ctx.addr, align 8, !dbg !4166
  %keys = getelementptr inbounds %struct.trad_enc_ctx, %struct.trad_enc_ctx* %0, i32 0, i32 0, !dbg !4167
  %arrayidx = getelementptr inbounds [3 x i32], [3 x i32]* %keys, i64 0, i64 2, !dbg !4166
  %1 = load i32, i32* %arrayidx, align 4, !dbg !4166
  %or = or i32 %1, 2, !dbg !4168
  store i32 %or, i32* %temp, align 4, !dbg !4165
  %2 = load i32, i32* %temp, align 4, !dbg !4169
  %3 = load i32, i32* %temp, align 4, !dbg !4170
  %xor = xor i32 %3, 1, !dbg !4171
  %mul = mul i32 %2, %xor, !dbg !4172
  %shr = lshr i32 %mul, 8, !dbg !4173
  %conv = trunc i32 %shr to i8, !dbg !4174
  %conv1 = zext i8 %conv to i32, !dbg !4174
  %and = and i32 %conv1, 255, !dbg !4175
  %conv2 = trunc i32 %and to i8, !dbg !4174
  ret i8 %conv2, !dbg !4176
}

declare i32 @cm_zlib_deflateEnd(%struct.z_stream_s*) #2

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i16 @archive_le16dec(i8* %pp) #7 !dbg !719 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %p1 = alloca i32, align 4
  %p0 = alloca i32, align 4
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !4177, metadata !728), !dbg !4178
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4179, metadata !728), !dbg !4180
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !4181
  store i8* %0, i8** %p, align 8, !dbg !4180
  call void @llvm.dbg.declare(metadata i32* %p1, metadata !4182, metadata !728), !dbg !4183
  %1 = load i8*, i8** %p, align 8, !dbg !4184
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 1, !dbg !4184
  %2 = load i8, i8* %arrayidx, align 1, !dbg !4184
  %conv = zext i8 %2 to i32, !dbg !4184
  store i32 %conv, i32* %p1, align 4, !dbg !4183
  call void @llvm.dbg.declare(metadata i32* %p0, metadata !4185, metadata !728), !dbg !4186
  %3 = load i8*, i8** %p, align 8, !dbg !4187
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 0, !dbg !4187
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !4187
  %conv2 = zext i8 %4 to i32, !dbg !4187
  store i32 %conv2, i32* %p0, align 4, !dbg !4186
  %5 = load i32, i32* %p1, align 4, !dbg !4188
  %shl = shl i32 %5, 8, !dbg !4189
  %6 = load i32, i32* %p0, align 4, !dbg !4190
  %or = or i32 %shl, %6, !dbg !4191
  %conv3 = trunc i32 %or to i16, !dbg !4192
  ret i16 %conv3, !dbg !4193
}

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
!llvm.module.flags = !{!724, !725}
!llvm.ident = !{!726}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !352, subprograms: !651)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_zip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !8, !14}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "compression", file: !1, line: 72, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7}
!5 = !DIEnumerator(name: "COMPRESSION_UNSPECIFIED", value: -1)
!6 = !DIEnumerator(name: "COMPRESSION_STORE", value: 0)
!7 = !DIEnumerator(name: "COMPRESSION_DEFLATE", value: 8)
!8 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "encryption", file: !1, line: 84, size: 32, align: 32, elements: !9)
!9 = !{!10, !11, !12, !13}
!10 = !DIEnumerator(name: "ENCRYPTION_NONE", value: 0)
!11 = !DIEnumerator(name: "ENCRYPTION_TRADITIONAL", value: 1)
!12 = !DIEnumerator(name: "ENCRYPTION_WINZIP_AES128", value: 2)
!13 = !DIEnumerator(name: "ENCRYPTION_WINZIP_AES256", value: 3)
!14 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 41, size: 32, align: 32, elements: !16)
!15 = !DIFile(filename: "/usr/include/langinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !{!17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252, !253, !254, !255, !256, !257, !258, !259, !260, !261, !262, !263, !264, !265, !266, !267, !268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314, !315, !316, !317, !318, !319, !320, !321, !322, !323, !324, !325, !326, !327, !328, !329, !330, !331, !332, !333, !334, !335, !336, !337, !338, !339, !340, !341, !342, !343, !344, !345, !346, !347, !348, !349, !350, !351}
!17 = !DIEnumerator(name: "ABDAY_1", value: 131072)
!18 = !DIEnumerator(name: "ABDAY_2", value: 131073)
!19 = !DIEnumerator(name: "ABDAY_3", value: 131074)
!20 = !DIEnumerator(name: "ABDAY_4", value: 131075)
!21 = !DIEnumerator(name: "ABDAY_5", value: 131076)
!22 = !DIEnumerator(name: "ABDAY_6", value: 131077)
!23 = !DIEnumerator(name: "ABDAY_7", value: 131078)
!24 = !DIEnumerator(name: "DAY_1", value: 131079)
!25 = !DIEnumerator(name: "DAY_2", value: 131080)
!26 = !DIEnumerator(name: "DAY_3", value: 131081)
!27 = !DIEnumerator(name: "DAY_4", value: 131082)
!28 = !DIEnumerator(name: "DAY_5", value: 131083)
!29 = !DIEnumerator(name: "DAY_6", value: 131084)
!30 = !DIEnumerator(name: "DAY_7", value: 131085)
!31 = !DIEnumerator(name: "ABMON_1", value: 131086)
!32 = !DIEnumerator(name: "ABMON_2", value: 131087)
!33 = !DIEnumerator(name: "ABMON_3", value: 131088)
!34 = !DIEnumerator(name: "ABMON_4", value: 131089)
!35 = !DIEnumerator(name: "ABMON_5", value: 131090)
!36 = !DIEnumerator(name: "ABMON_6", value: 131091)
!37 = !DIEnumerator(name: "ABMON_7", value: 131092)
!38 = !DIEnumerator(name: "ABMON_8", value: 131093)
!39 = !DIEnumerator(name: "ABMON_9", value: 131094)
!40 = !DIEnumerator(name: "ABMON_10", value: 131095)
!41 = !DIEnumerator(name: "ABMON_11", value: 131096)
!42 = !DIEnumerator(name: "ABMON_12", value: 131097)
!43 = !DIEnumerator(name: "MON_1", value: 131098)
!44 = !DIEnumerator(name: "MON_2", value: 131099)
!45 = !DIEnumerator(name: "MON_3", value: 131100)
!46 = !DIEnumerator(name: "MON_4", value: 131101)
!47 = !DIEnumerator(name: "MON_5", value: 131102)
!48 = !DIEnumerator(name: "MON_6", value: 131103)
!49 = !DIEnumerator(name: "MON_7", value: 131104)
!50 = !DIEnumerator(name: "MON_8", value: 131105)
!51 = !DIEnumerator(name: "MON_9", value: 131106)
!52 = !DIEnumerator(name: "MON_10", value: 131107)
!53 = !DIEnumerator(name: "MON_11", value: 131108)
!54 = !DIEnumerator(name: "MON_12", value: 131109)
!55 = !DIEnumerator(name: "AM_STR", value: 131110)
!56 = !DIEnumerator(name: "PM_STR", value: 131111)
!57 = !DIEnumerator(name: "D_T_FMT", value: 131112)
!58 = !DIEnumerator(name: "D_FMT", value: 131113)
!59 = !DIEnumerator(name: "T_FMT", value: 131114)
!60 = !DIEnumerator(name: "T_FMT_AMPM", value: 131115)
!61 = !DIEnumerator(name: "ERA", value: 131116)
!62 = !DIEnumerator(name: "__ERA_YEAR", value: 131117)
!63 = !DIEnumerator(name: "ERA_D_FMT", value: 131118)
!64 = !DIEnumerator(name: "ALT_DIGITS", value: 131119)
!65 = !DIEnumerator(name: "ERA_D_T_FMT", value: 131120)
!66 = !DIEnumerator(name: "ERA_T_FMT", value: 131121)
!67 = !DIEnumerator(name: "_NL_TIME_ERA_NUM_ENTRIES", value: 131122)
!68 = !DIEnumerator(name: "_NL_TIME_ERA_ENTRIES", value: 131123)
!69 = !DIEnumerator(name: "_NL_WABDAY_1", value: 131124)
!70 = !DIEnumerator(name: "_NL_WABDAY_2", value: 131125)
!71 = !DIEnumerator(name: "_NL_WABDAY_3", value: 131126)
!72 = !DIEnumerator(name: "_NL_WABDAY_4", value: 131127)
!73 = !DIEnumerator(name: "_NL_WABDAY_5", value: 131128)
!74 = !DIEnumerator(name: "_NL_WABDAY_6", value: 131129)
!75 = !DIEnumerator(name: "_NL_WABDAY_7", value: 131130)
!76 = !DIEnumerator(name: "_NL_WDAY_1", value: 131131)
!77 = !DIEnumerator(name: "_NL_WDAY_2", value: 131132)
!78 = !DIEnumerator(name: "_NL_WDAY_3", value: 131133)
!79 = !DIEnumerator(name: "_NL_WDAY_4", value: 131134)
!80 = !DIEnumerator(name: "_NL_WDAY_5", value: 131135)
!81 = !DIEnumerator(name: "_NL_WDAY_6", value: 131136)
!82 = !DIEnumerator(name: "_NL_WDAY_7", value: 131137)
!83 = !DIEnumerator(name: "_NL_WABMON_1", value: 131138)
!84 = !DIEnumerator(name: "_NL_WABMON_2", value: 131139)
!85 = !DIEnumerator(name: "_NL_WABMON_3", value: 131140)
!86 = !DIEnumerator(name: "_NL_WABMON_4", value: 131141)
!87 = !DIEnumerator(name: "_NL_WABMON_5", value: 131142)
!88 = !DIEnumerator(name: "_NL_WABMON_6", value: 131143)
!89 = !DIEnumerator(name: "_NL_WABMON_7", value: 131144)
!90 = !DIEnumerator(name: "_NL_WABMON_8", value: 131145)
!91 = !DIEnumerator(name: "_NL_WABMON_9", value: 131146)
!92 = !DIEnumerator(name: "_NL_WABMON_10", value: 131147)
!93 = !DIEnumerator(name: "_NL_WABMON_11", value: 131148)
!94 = !DIEnumerator(name: "_NL_WABMON_12", value: 131149)
!95 = !DIEnumerator(name: "_NL_WMON_1", value: 131150)
!96 = !DIEnumerator(name: "_NL_WMON_2", value: 131151)
!97 = !DIEnumerator(name: "_NL_WMON_3", value: 131152)
!98 = !DIEnumerator(name: "_NL_WMON_4", value: 131153)
!99 = !DIEnumerator(name: "_NL_WMON_5", value: 131154)
!100 = !DIEnumerator(name: "_NL_WMON_6", value: 131155)
!101 = !DIEnumerator(name: "_NL_WMON_7", value: 131156)
!102 = !DIEnumerator(name: "_NL_WMON_8", value: 131157)
!103 = !DIEnumerator(name: "_NL_WMON_9", value: 131158)
!104 = !DIEnumerator(name: "_NL_WMON_10", value: 131159)
!105 = !DIEnumerator(name: "_NL_WMON_11", value: 131160)
!106 = !DIEnumerator(name: "_NL_WMON_12", value: 131161)
!107 = !DIEnumerator(name: "_NL_WAM_STR", value: 131162)
!108 = !DIEnumerator(name: "_NL_WPM_STR", value: 131163)
!109 = !DIEnumerator(name: "_NL_WD_T_FMT", value: 131164)
!110 = !DIEnumerator(name: "_NL_WD_FMT", value: 131165)
!111 = !DIEnumerator(name: "_NL_WT_FMT", value: 131166)
!112 = !DIEnumerator(name: "_NL_WT_FMT_AMPM", value: 131167)
!113 = !DIEnumerator(name: "_NL_WERA_YEAR", value: 131168)
!114 = !DIEnumerator(name: "_NL_WERA_D_FMT", value: 131169)
!115 = !DIEnumerator(name: "_NL_WALT_DIGITS", value: 131170)
!116 = !DIEnumerator(name: "_NL_WERA_D_T_FMT", value: 131171)
!117 = !DIEnumerator(name: "_NL_WERA_T_FMT", value: 131172)
!118 = !DIEnumerator(name: "_NL_TIME_WEEK_NDAYS", value: 131173)
!119 = !DIEnumerator(name: "_NL_TIME_WEEK_1STDAY", value: 131174)
!120 = !DIEnumerator(name: "_NL_TIME_WEEK_1STWEEK", value: 131175)
!121 = !DIEnumerator(name: "_NL_TIME_FIRST_WEEKDAY", value: 131176)
!122 = !DIEnumerator(name: "_NL_TIME_FIRST_WORKDAY", value: 131177)
!123 = !DIEnumerator(name: "_NL_TIME_CAL_DIRECTION", value: 131178)
!124 = !DIEnumerator(name: "_NL_TIME_TIMEZONE", value: 131179)
!125 = !DIEnumerator(name: "_DATE_FMT", value: 131180)
!126 = !DIEnumerator(name: "_NL_W_DATE_FMT", value: 131181)
!127 = !DIEnumerator(name: "_NL_TIME_CODESET", value: 131182)
!128 = !DIEnumerator(name: "_NL_NUM_LC_TIME", value: 131183)
!129 = !DIEnumerator(name: "_NL_COLLATE_NRULES", value: 196608)
!130 = !DIEnumerator(name: "_NL_COLLATE_RULESETS", value: 196609)
!131 = !DIEnumerator(name: "_NL_COLLATE_TABLEMB", value: 196610)
!132 = !DIEnumerator(name: "_NL_COLLATE_WEIGHTMB", value: 196611)
!133 = !DIEnumerator(name: "_NL_COLLATE_EXTRAMB", value: 196612)
!134 = !DIEnumerator(name: "_NL_COLLATE_INDIRECTMB", value: 196613)
!135 = !DIEnumerator(name: "_NL_COLLATE_GAP1", value: 196614)
!136 = !DIEnumerator(name: "_NL_COLLATE_GAP2", value: 196615)
!137 = !DIEnumerator(name: "_NL_COLLATE_GAP3", value: 196616)
!138 = !DIEnumerator(name: "_NL_COLLATE_TABLEWC", value: 196617)
!139 = !DIEnumerator(name: "_NL_COLLATE_WEIGHTWC", value: 196618)
!140 = !DIEnumerator(name: "_NL_COLLATE_EXTRAWC", value: 196619)
!141 = !DIEnumerator(name: "_NL_COLLATE_INDIRECTWC", value: 196620)
!142 = !DIEnumerator(name: "_NL_COLLATE_SYMB_HASH_SIZEMB", value: 196621)
!143 = !DIEnumerator(name: "_NL_COLLATE_SYMB_TABLEMB", value: 196622)
!144 = !DIEnumerator(name: "_NL_COLLATE_SYMB_EXTRAMB", value: 196623)
!145 = !DIEnumerator(name: "_NL_COLLATE_COLLSEQMB", value: 196624)
!146 = !DIEnumerator(name: "_NL_COLLATE_COLLSEQWC", value: 196625)
!147 = !DIEnumerator(name: "_NL_COLLATE_CODESET", value: 196626)
!148 = !DIEnumerator(name: "_NL_NUM_LC_COLLATE", value: 196627)
!149 = !DIEnumerator(name: "_NL_CTYPE_CLASS", value: 0)
!150 = !DIEnumerator(name: "_NL_CTYPE_TOUPPER", value: 1)
!151 = !DIEnumerator(name: "_NL_CTYPE_GAP1", value: 2)
!152 = !DIEnumerator(name: "_NL_CTYPE_TOLOWER", value: 3)
!153 = !DIEnumerator(name: "_NL_CTYPE_GAP2", value: 4)
!154 = !DIEnumerator(name: "_NL_CTYPE_CLASS32", value: 5)
!155 = !DIEnumerator(name: "_NL_CTYPE_GAP3", value: 6)
!156 = !DIEnumerator(name: "_NL_CTYPE_GAP4", value: 7)
!157 = !DIEnumerator(name: "_NL_CTYPE_GAP5", value: 8)
!158 = !DIEnumerator(name: "_NL_CTYPE_GAP6", value: 9)
!159 = !DIEnumerator(name: "_NL_CTYPE_CLASS_NAMES", value: 10)
!160 = !DIEnumerator(name: "_NL_CTYPE_MAP_NAMES", value: 11)
!161 = !DIEnumerator(name: "_NL_CTYPE_WIDTH", value: 12)
!162 = !DIEnumerator(name: "_NL_CTYPE_MB_CUR_MAX", value: 13)
!163 = !DIEnumerator(name: "_NL_CTYPE_CODESET_NAME", value: 14)
!164 = !DIEnumerator(name: "CODESET", value: 14)
!165 = !DIEnumerator(name: "_NL_CTYPE_TOUPPER32", value: 15)
!166 = !DIEnumerator(name: "_NL_CTYPE_TOLOWER32", value: 16)
!167 = !DIEnumerator(name: "_NL_CTYPE_CLASS_OFFSET", value: 17)
!168 = !DIEnumerator(name: "_NL_CTYPE_MAP_OFFSET", value: 18)
!169 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS_MB_LEN", value: 19)
!170 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS0_MB", value: 20)
!171 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS1_MB", value: 21)
!172 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS2_MB", value: 22)
!173 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS3_MB", value: 23)
!174 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS4_MB", value: 24)
!175 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS5_MB", value: 25)
!176 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS6_MB", value: 26)
!177 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS7_MB", value: 27)
!178 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS8_MB", value: 28)
!179 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS9_MB", value: 29)
!180 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS_WC_LEN", value: 30)
!181 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS0_WC", value: 31)
!182 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS1_WC", value: 32)
!183 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS2_WC", value: 33)
!184 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS3_WC", value: 34)
!185 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS4_WC", value: 35)
!186 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS5_WC", value: 36)
!187 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS6_WC", value: 37)
!188 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS7_WC", value: 38)
!189 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS8_WC", value: 39)
!190 = !DIEnumerator(name: "_NL_CTYPE_INDIGITS9_WC", value: 40)
!191 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT0_MB", value: 41)
!192 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT1_MB", value: 42)
!193 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT2_MB", value: 43)
!194 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT3_MB", value: 44)
!195 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT4_MB", value: 45)
!196 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT5_MB", value: 46)
!197 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT6_MB", value: 47)
!198 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT7_MB", value: 48)
!199 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT8_MB", value: 49)
!200 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT9_MB", value: 50)
!201 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT0_WC", value: 51)
!202 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT1_WC", value: 52)
!203 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT2_WC", value: 53)
!204 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT3_WC", value: 54)
!205 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT4_WC", value: 55)
!206 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT5_WC", value: 56)
!207 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT6_WC", value: 57)
!208 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT7_WC", value: 58)
!209 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT8_WC", value: 59)
!210 = !DIEnumerator(name: "_NL_CTYPE_OUTDIGIT9_WC", value: 60)
!211 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_TAB_SIZE", value: 61)
!212 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_FROM_IDX", value: 62)
!213 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_FROM_TBL", value: 63)
!214 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_TO_IDX", value: 64)
!215 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_TO_TBL", value: 65)
!216 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_DEFAULT_MISSING_LEN", value: 66)
!217 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_DEFAULT_MISSING", value: 67)
!218 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_IGNORE_LEN", value: 68)
!219 = !DIEnumerator(name: "_NL_CTYPE_TRANSLIT_IGNORE", value: 69)
!220 = !DIEnumerator(name: "_NL_CTYPE_MAP_TO_NONASCII", value: 70)
!221 = !DIEnumerator(name: "_NL_CTYPE_NONASCII_CASE", value: 71)
!222 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_1", value: 72)
!223 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_2", value: 73)
!224 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_3", value: 74)
!225 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_4", value: 75)
!226 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_5", value: 76)
!227 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_6", value: 77)
!228 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_7", value: 78)
!229 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_8", value: 79)
!230 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_9", value: 80)
!231 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_10", value: 81)
!232 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_11", value: 82)
!233 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_12", value: 83)
!234 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_13", value: 84)
!235 = !DIEnumerator(name: "_NL_CTYPE_EXTRA_MAP_14", value: 85)
!236 = !DIEnumerator(name: "_NL_NUM_LC_CTYPE", value: 86)
!237 = !DIEnumerator(name: "__INT_CURR_SYMBOL", value: 262144)
!238 = !DIEnumerator(name: "__CURRENCY_SYMBOL", value: 262145)
!239 = !DIEnumerator(name: "__MON_DECIMAL_POINT", value: 262146)
!240 = !DIEnumerator(name: "__MON_THOUSANDS_SEP", value: 262147)
!241 = !DIEnumerator(name: "__MON_GROUPING", value: 262148)
!242 = !DIEnumerator(name: "__POSITIVE_SIGN", value: 262149)
!243 = !DIEnumerator(name: "__NEGATIVE_SIGN", value: 262150)
!244 = !DIEnumerator(name: "__INT_FRAC_DIGITS", value: 262151)
!245 = !DIEnumerator(name: "__FRAC_DIGITS", value: 262152)
!246 = !DIEnumerator(name: "__P_CS_PRECEDES", value: 262153)
!247 = !DIEnumerator(name: "__P_SEP_BY_SPACE", value: 262154)
!248 = !DIEnumerator(name: "__N_CS_PRECEDES", value: 262155)
!249 = !DIEnumerator(name: "__N_SEP_BY_SPACE", value: 262156)
!250 = !DIEnumerator(name: "__P_SIGN_POSN", value: 262157)
!251 = !DIEnumerator(name: "__N_SIGN_POSN", value: 262158)
!252 = !DIEnumerator(name: "_NL_MONETARY_CRNCYSTR", value: 262159)
!253 = !DIEnumerator(name: "__INT_P_CS_PRECEDES", value: 262160)
!254 = !DIEnumerator(name: "__INT_P_SEP_BY_SPACE", value: 262161)
!255 = !DIEnumerator(name: "__INT_N_CS_PRECEDES", value: 262162)
!256 = !DIEnumerator(name: "__INT_N_SEP_BY_SPACE", value: 262163)
!257 = !DIEnumerator(name: "__INT_P_SIGN_POSN", value: 262164)
!258 = !DIEnumerator(name: "__INT_N_SIGN_POSN", value: 262165)
!259 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_CURR_SYMBOL", value: 262166)
!260 = !DIEnumerator(name: "_NL_MONETARY_DUO_CURRENCY_SYMBOL", value: 262167)
!261 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_FRAC_DIGITS", value: 262168)
!262 = !DIEnumerator(name: "_NL_MONETARY_DUO_FRAC_DIGITS", value: 262169)
!263 = !DIEnumerator(name: "_NL_MONETARY_DUO_P_CS_PRECEDES", value: 262170)
!264 = !DIEnumerator(name: "_NL_MONETARY_DUO_P_SEP_BY_SPACE", value: 262171)
!265 = !DIEnumerator(name: "_NL_MONETARY_DUO_N_CS_PRECEDES", value: 262172)
!266 = !DIEnumerator(name: "_NL_MONETARY_DUO_N_SEP_BY_SPACE", value: 262173)
!267 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_P_CS_PRECEDES", value: 262174)
!268 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_P_SEP_BY_SPACE", value: 262175)
!269 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_N_CS_PRECEDES", value: 262176)
!270 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_N_SEP_BY_SPACE", value: 262177)
!271 = !DIEnumerator(name: "_NL_MONETARY_DUO_P_SIGN_POSN", value: 262178)
!272 = !DIEnumerator(name: "_NL_MONETARY_DUO_N_SIGN_POSN", value: 262179)
!273 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_P_SIGN_POSN", value: 262180)
!274 = !DIEnumerator(name: "_NL_MONETARY_DUO_INT_N_SIGN_POSN", value: 262181)
!275 = !DIEnumerator(name: "_NL_MONETARY_UNO_VALID_FROM", value: 262182)
!276 = !DIEnumerator(name: "_NL_MONETARY_UNO_VALID_TO", value: 262183)
!277 = !DIEnumerator(name: "_NL_MONETARY_DUO_VALID_FROM", value: 262184)
!278 = !DIEnumerator(name: "_NL_MONETARY_DUO_VALID_TO", value: 262185)
!279 = !DIEnumerator(name: "_NL_MONETARY_CONVERSION_RATE", value: 262186)
!280 = !DIEnumerator(name: "_NL_MONETARY_DECIMAL_POINT_WC", value: 262187)
!281 = !DIEnumerator(name: "_NL_MONETARY_THOUSANDS_SEP_WC", value: 262188)
!282 = !DIEnumerator(name: "_NL_MONETARY_CODESET", value: 262189)
!283 = !DIEnumerator(name: "_NL_NUM_LC_MONETARY", value: 262190)
!284 = !DIEnumerator(name: "__DECIMAL_POINT", value: 65536)
!285 = !DIEnumerator(name: "RADIXCHAR", value: 65536)
!286 = !DIEnumerator(name: "__THOUSANDS_SEP", value: 65537)
!287 = !DIEnumerator(name: "THOUSEP", value: 65537)
!288 = !DIEnumerator(name: "__GROUPING", value: 65538)
!289 = !DIEnumerator(name: "_NL_NUMERIC_DECIMAL_POINT_WC", value: 65539)
!290 = !DIEnumerator(name: "_NL_NUMERIC_THOUSANDS_SEP_WC", value: 65540)
!291 = !DIEnumerator(name: "_NL_NUMERIC_CODESET", value: 65541)
!292 = !DIEnumerator(name: "_NL_NUM_LC_NUMERIC", value: 65542)
!293 = !DIEnumerator(name: "__YESEXPR", value: 327680)
!294 = !DIEnumerator(name: "__NOEXPR", value: 327681)
!295 = !DIEnumerator(name: "__YESSTR", value: 327682)
!296 = !DIEnumerator(name: "__NOSTR", value: 327683)
!297 = !DIEnumerator(name: "_NL_MESSAGES_CODESET", value: 327684)
!298 = !DIEnumerator(name: "_NL_NUM_LC_MESSAGES", value: 327685)
!299 = !DIEnumerator(name: "_NL_PAPER_HEIGHT", value: 458752)
!300 = !DIEnumerator(name: "_NL_PAPER_WIDTH", value: 458753)
!301 = !DIEnumerator(name: "_NL_PAPER_CODESET", value: 458754)
!302 = !DIEnumerator(name: "_NL_NUM_LC_PAPER", value: 458755)
!303 = !DIEnumerator(name: "_NL_NAME_NAME_FMT", value: 524288)
!304 = !DIEnumerator(name: "_NL_NAME_NAME_GEN", value: 524289)
!305 = !DIEnumerator(name: "_NL_NAME_NAME_MR", value: 524290)
!306 = !DIEnumerator(name: "_NL_NAME_NAME_MRS", value: 524291)
!307 = !DIEnumerator(name: "_NL_NAME_NAME_MISS", value: 524292)
!308 = !DIEnumerator(name: "_NL_NAME_NAME_MS", value: 524293)
!309 = !DIEnumerator(name: "_NL_NAME_CODESET", value: 524294)
!310 = !DIEnumerator(name: "_NL_NUM_LC_NAME", value: 524295)
!311 = !DIEnumerator(name: "_NL_ADDRESS_POSTAL_FMT", value: 589824)
!312 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_NAME", value: 589825)
!313 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_POST", value: 589826)
!314 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_AB2", value: 589827)
!315 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_AB3", value: 589828)
!316 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_CAR", value: 589829)
!317 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_NUM", value: 589830)
!318 = !DIEnumerator(name: "_NL_ADDRESS_COUNTRY_ISBN", value: 589831)
!319 = !DIEnumerator(name: "_NL_ADDRESS_LANG_NAME", value: 589832)
!320 = !DIEnumerator(name: "_NL_ADDRESS_LANG_AB", value: 589833)
!321 = !DIEnumerator(name: "_NL_ADDRESS_LANG_TERM", value: 589834)
!322 = !DIEnumerator(name: "_NL_ADDRESS_LANG_LIB", value: 589835)
!323 = !DIEnumerator(name: "_NL_ADDRESS_CODESET", value: 589836)
!324 = !DIEnumerator(name: "_NL_NUM_LC_ADDRESS", value: 589837)
!325 = !DIEnumerator(name: "_NL_TELEPHONE_TEL_INT_FMT", value: 655360)
!326 = !DIEnumerator(name: "_NL_TELEPHONE_TEL_DOM_FMT", value: 655361)
!327 = !DIEnumerator(name: "_NL_TELEPHONE_INT_SELECT", value: 655362)
!328 = !DIEnumerator(name: "_NL_TELEPHONE_INT_PREFIX", value: 655363)
!329 = !DIEnumerator(name: "_NL_TELEPHONE_CODESET", value: 655364)
!330 = !DIEnumerator(name: "_NL_NUM_LC_TELEPHONE", value: 655365)
!331 = !DIEnumerator(name: "_NL_MEASUREMENT_MEASUREMENT", value: 720896)
!332 = !DIEnumerator(name: "_NL_MEASUREMENT_CODESET", value: 720897)
!333 = !DIEnumerator(name: "_NL_NUM_LC_MEASUREMENT", value: 720898)
!334 = !DIEnumerator(name: "_NL_IDENTIFICATION_TITLE", value: 786432)
!335 = !DIEnumerator(name: "_NL_IDENTIFICATION_SOURCE", value: 786433)
!336 = !DIEnumerator(name: "_NL_IDENTIFICATION_ADDRESS", value: 786434)
!337 = !DIEnumerator(name: "_NL_IDENTIFICATION_CONTACT", value: 786435)
!338 = !DIEnumerator(name: "_NL_IDENTIFICATION_EMAIL", value: 786436)
!339 = !DIEnumerator(name: "_NL_IDENTIFICATION_TEL", value: 786437)
!340 = !DIEnumerator(name: "_NL_IDENTIFICATION_FAX", value: 786438)
!341 = !DIEnumerator(name: "_NL_IDENTIFICATION_LANGUAGE", value: 786439)
!342 = !DIEnumerator(name: "_NL_IDENTIFICATION_TERRITORY", value: 786440)
!343 = !DIEnumerator(name: "_NL_IDENTIFICATION_AUDIENCE", value: 786441)
!344 = !DIEnumerator(name: "_NL_IDENTIFICATION_APPLICATION", value: 786442)
!345 = !DIEnumerator(name: "_NL_IDENTIFICATION_ABBREVIATION", value: 786443)
!346 = !DIEnumerator(name: "_NL_IDENTIFICATION_REVISION", value: 786444)
!347 = !DIEnumerator(name: "_NL_IDENTIFICATION_DATE", value: 786445)
!348 = !DIEnumerator(name: "_NL_IDENTIFICATION_CATEGORY", value: 786446)
!349 = !DIEnumerator(name: "_NL_IDENTIFICATION_CODESET", value: 786447)
!350 = !DIEnumerator(name: "_NL_NUM_LC_IDENTIFICATION", value: 786448)
!351 = !DIEnumerator(name: "_NL_NUM", value: 786449)
!352 = !{!353, !473, !541, !362, !642, !464, !552, !644, !613, !577, !372, !401, !394, !646, !649, !648, !650}
!353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !354, size: 64, align: 64)
!354 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !355, line: 72, size: 2816, align: 64, elements: !356)
!355 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!356 = !{!357, !460, !461, !462, !463, !467, !468, !474, !480, !483, !484, !485, !486, !512, !513, !514, !515, !519, !523, !524, !528, !532, !533, !534, !535, !540}
!357 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !354, file: !355, line: 73, baseType: !358, size: 1280, align: 64)
!358 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !359, line: 89, size: 1280, align: 64, elements: !360)
!359 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!360 = !{!361, !363, !364, !432, !433, !434, !435, !436, !437, !438, !439, !447, !448, !449, !450, !454, !455, !456, !457, !458, !459}
!361 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !358, file: !359, line: 96, baseType: !362, size: 32, align: 32)
!362 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !358, file: !359, line: 97, baseType: !362, size: 32, align: 32, offset: 32)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !358, file: !359, line: 103, baseType: !365, size: 64, align: 64, offset: 64)
!365 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !366, size: 64, align: 64)
!366 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !359, line: 63, size: 832, align: 64, elements: !367)
!367 = !{!368, !374, !375, !382, !383, !397, !403, !408, !409, !416, !417, !421, !425}
!368 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !366, file: !359, line: 64, baseType: !369, size: 64, align: 64)
!369 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !370, size: 64, align: 64)
!370 = !DISubroutineType(types: !371)
!371 = !{!372, !373}
!372 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!373 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !358, size: 64, align: 64)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !366, file: !359, line: 65, baseType: !369, size: 64, align: 64, offset: 64)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !366, file: !359, line: 66, baseType: !376, size: 64, align: 64, offset: 128)
!376 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !377, size: 64, align: 64)
!377 = !DISubroutineType(types: !378)
!378 = !{!372, !373, !379}
!379 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !380, size: 64, align: 64)
!380 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !381, line: 180, flags: DIFlagFwdDecl)
!381 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!382 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !366, file: !359, line: 68, baseType: !369, size: 64, align: 64, offset: 192)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !366, file: !359, line: 69, baseType: !384, size: 64, align: 64, offset: 256)
!384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !385, size: 64, align: 64)
!385 = !DISubroutineType(types: !386)
!386 = !{!387, !373, !392, !394}
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !388, line: 109, baseType: !389)
!388 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!389 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !390, line: 172, baseType: !391)
!390 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!391 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!392 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !393, size: 64, align: 64)
!393 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!394 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !395, line: 62, baseType: !396)
!395 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!396 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!397 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !366, file: !359, line: 71, baseType: !398, size: 64, align: 64, offset: 320)
!398 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !399, size: 64, align: 64)
!399 = !DISubroutineType(types: !400)
!400 = !{!387, !373, !392, !394, !401}
!401 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !402, line: 40, baseType: !391)
!402 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!403 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !366, file: !359, line: 74, baseType: !404, size: 64, align: 64, offset: 384)
!404 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !405, size: 64, align: 64)
!405 = !DISubroutineType(types: !406)
!406 = !{!372, !373, !407}
!407 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !366, file: !359, line: 76, baseType: !376, size: 64, align: 64, offset: 448)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !366, file: !359, line: 78, baseType: !410, size: 64, align: 64, offset: 512)
!410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !411, size: 64, align: 64)
!411 = !DISubroutineType(types: !412)
!412 = !{!372, !373, !413, !414, !415}
!413 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !392, size: 64, align: 64)
!414 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !394, size: 64, align: 64)
!415 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !401, size: 64, align: 64)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !366, file: !359, line: 81, baseType: !369, size: 64, align: 64, offset: 576)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !366, file: !359, line: 82, baseType: !418, size: 64, align: 64, offset: 640)
!418 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !419, size: 64, align: 64)
!419 = !DISubroutineType(types: !420)
!420 = !{!401, !373, !372}
!421 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !366, file: !359, line: 83, baseType: !422, size: 64, align: 64, offset: 704)
!422 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!423 = !DISubroutineType(types: !424)
!424 = !{!372, !373, !372}
!425 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !366, file: !359, line: 84, baseType: !426, size: 64, align: 64, offset: 768)
!426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !427, size: 64, align: 64)
!427 = !DISubroutineType(types: !428)
!428 = !{!429, !373, !372}
!429 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !430, size: 64, align: 64)
!430 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !431)
!431 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !358, file: !359, line: 105, baseType: !372, size: 32, align: 32, offset: 128)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !358, file: !359, line: 106, baseType: !429, size: 64, align: 64, offset: 192)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !358, file: !359, line: 108, baseType: !372, size: 32, align: 32, offset: 256)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !358, file: !359, line: 109, baseType: !429, size: 64, align: 64, offset: 320)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !358, file: !359, line: 112, baseType: !372, size: 32, align: 32, offset: 384)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !358, file: !359, line: 114, baseType: !372, size: 32, align: 32, offset: 416)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !358, file: !359, line: 115, baseType: !429, size: 64, align: 64, offset: 448)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !358, file: !359, line: 116, baseType: !440, size: 192, align: 64, offset: 512)
!440 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !441, line: 58, size: 192, align: 64, elements: !442)
!441 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!442 = !{!443, !445, !446}
!443 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !440, file: !441, line: 59, baseType: !444, size: 64, align: 64)
!444 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !431, size: 64, align: 64)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !440, file: !441, line: 60, baseType: !394, size: 64, align: 64, offset: 64)
!446 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !440, file: !441, line: 61, baseType: !394, size: 64, align: 64, offset: 128)
!447 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !358, file: !359, line: 118, baseType: !444, size: 64, align: 64, offset: 704)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !358, file: !359, line: 119, baseType: !362, size: 32, align: 32, offset: 768)
!449 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !358, file: !359, line: 120, baseType: !362, size: 32, align: 32, offset: 800)
!450 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !358, file: !359, line: 121, baseType: !451, size: 64, align: 64, offset: 832)
!451 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !452, size: 64, align: 64)
!452 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !453, line: 36, flags: DIFlagFwdDecl)
!453 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!454 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !358, file: !359, line: 127, baseType: !429, size: 64, align: 64, offset: 896)
!455 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !358, file: !359, line: 128, baseType: !401, size: 64, align: 64, offset: 960)
!456 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !358, file: !359, line: 129, baseType: !401, size: 64, align: 64, offset: 1024)
!457 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !358, file: !359, line: 130, baseType: !394, size: 64, align: 64, offset: 1088)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !358, file: !359, line: 137, baseType: !431, size: 8, align: 8, offset: 1152)
!459 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !358, file: !359, line: 138, baseType: !394, size: 64, align: 64, offset: 1216)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !354, file: !355, line: 76, baseType: !372, size: 32, align: 32, offset: 1280)
!461 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !354, file: !355, line: 77, baseType: !401, size: 64, align: 64, offset: 1344)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !354, file: !355, line: 78, baseType: !401, size: 64, align: 64, offset: 1408)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !354, file: !355, line: 81, baseType: !464, size: 64, align: 64, offset: 1472)
!464 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !465, size: 64, align: 64)
!465 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !466)
!466 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !354, file: !355, line: 82, baseType: !394, size: 64, align: 64, offset: 1536)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !354, file: !355, line: 85, baseType: !469, size: 64, align: 64, offset: 1600)
!469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !470, size: 64, align: 64)
!470 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !381, line: 241, baseType: !471)
!471 = !DISubroutineType(types: !472)
!472 = !{!372, !373, !473}
!473 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!474 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !354, file: !355, line: 86, baseType: !475, size: 64, align: 64, offset: 1664)
!475 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !476, size: 64, align: 64)
!476 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !381, line: 237, baseType: !477)
!477 = !DISubroutineType(types: !478)
!478 = !{!479, !373, !473, !392, !394}
!479 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !381, line: 95, baseType: !387)
!480 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !354, file: !355, line: 87, baseType: !481, size: 64, align: 64, offset: 1728)
!481 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !482, size: 64, align: 64)
!482 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !381, line: 243, baseType: !471)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !354, file: !355, line: 88, baseType: !473, size: 64, align: 64, offset: 1792)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !354, file: !355, line: 96, baseType: !372, size: 32, align: 32, offset: 1856)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !354, file: !355, line: 97, baseType: !372, size: 32, align: 32, offset: 1888)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !354, file: !355, line: 102, baseType: !487, size: 64, align: 64, offset: 1920)
!487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !488, size: 64, align: 64)
!488 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !355, line: 43, size: 768, align: 64, elements: !489)
!489 = !{!490, !491, !492, !493, !497, !501, !505, !506, !507, !508, !509, !510, !511}
!490 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !488, file: !355, line: 44, baseType: !401, size: 64, align: 64)
!491 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !488, file: !355, line: 45, baseType: !373, size: 64, align: 64, offset: 64)
!492 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !488, file: !355, line: 46, baseType: !487, size: 64, align: 64, offset: 128)
!493 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !488, file: !355, line: 47, baseType: !494, size: 64, align: 64, offset: 192)
!494 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !495, size: 64, align: 64)
!495 = !DISubroutineType(types: !496)
!496 = !{!372, !487, !429, !429}
!497 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !488, file: !355, line: 49, baseType: !498, size: 64, align: 64, offset: 256)
!498 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !499, size: 64, align: 64)
!499 = !DISubroutineType(types: !500)
!500 = !{!372, !487}
!501 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !488, file: !355, line: 50, baseType: !502, size: 64, align: 64, offset: 320)
!502 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !503, size: 64, align: 64)
!503 = !DISubroutineType(types: !504)
!504 = !{!372, !487, !392, !394}
!505 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !488, file: !355, line: 51, baseType: !498, size: 64, align: 64, offset: 384)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !488, file: !355, line: 52, baseType: !498, size: 64, align: 64, offset: 448)
!507 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !488, file: !355, line: 53, baseType: !473, size: 64, align: 64, offset: 512)
!508 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !488, file: !355, line: 54, baseType: !429, size: 64, align: 64, offset: 576)
!509 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !488, file: !355, line: 55, baseType: !372, size: 32, align: 32, offset: 640)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !488, file: !355, line: 56, baseType: !372, size: 32, align: 32, offset: 672)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !488, file: !355, line: 57, baseType: !372, size: 32, align: 32, offset: 704)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !354, file: !355, line: 103, baseType: !487, size: 64, align: 64, offset: 1984)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !354, file: !355, line: 109, baseType: !473, size: 64, align: 64, offset: 2048)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !354, file: !355, line: 110, baseType: !429, size: 64, align: 64, offset: 2112)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !354, file: !355, line: 111, baseType: !516, size: 64, align: 64, offset: 2176)
!516 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !517, size: 64, align: 64)
!517 = !DISubroutineType(types: !518)
!518 = !{!372, !353}
!519 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !354, file: !355, line: 112, baseType: !520, size: 64, align: 64, offset: 2240)
!520 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !521, size: 64, align: 64)
!521 = !DISubroutineType(types: !522)
!522 = !{!372, !353, !429, !429}
!523 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !354, file: !355, line: 114, baseType: !516, size: 64, align: 64, offset: 2304)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !354, file: !355, line: 115, baseType: !525, size: 64, align: 64, offset: 2368)
!525 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !526, size: 64, align: 64)
!526 = !DISubroutineType(types: !527)
!527 = !{!372, !353, !379}
!528 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !354, file: !355, line: 117, baseType: !529, size: 64, align: 64, offset: 2432)
!529 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !530, size: 64, align: 64)
!530 = !DISubroutineType(types: !531)
!531 = !{!387, !353, !392, !394}
!532 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !354, file: !355, line: 119, baseType: !516, size: 64, align: 64, offset: 2496)
!533 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !354, file: !355, line: 120, baseType: !516, size: 64, align: 64, offset: 2560)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !354, file: !355, line: 126, baseType: !444, size: 64, align: 64, offset: 2624)
!535 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !354, file: !355, line: 127, baseType: !536, size: 64, align: 64, offset: 2688)
!536 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !537, size: 64, align: 64)
!537 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !381, line: 256, baseType: !538)
!538 = !DISubroutineType(types: !539)
!539 = !{!429, !373, !473}
!540 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !354, file: !355, line: 128, baseType: !473, size: 64, align: 64, offset: 2752)
!541 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !542, size: 64, align: 64)
!542 = !DICompositeType(tag: DW_TAG_structure_type, name: "zip", file: !1, line: 121, size: 2816, align: 64, elements: !543)
!543 = !{!544, !545, !546, !547, !548, !549, !550, !551, !553, !554, !555, !556, !557, !558, !565, !566, !567, !568, !571, !572, !575, !576, !578, !579, !583, !591, !592, !593, !594, !595, !596, !597, !598, !599, !600, !601, !602, !640, !641}
!544 = !DIDerivedType(tag: DW_TAG_member, name: "entry_offset", scope: !542, file: !1, line: 123, baseType: !401, size: 64, align: 64)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "entry_compressed_size", scope: !542, file: !1, line: 124, baseType: !401, size: 64, align: 64, offset: 64)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "entry_uncompressed_size", scope: !542, file: !1, line: 125, baseType: !401, size: 64, align: 64, offset: 128)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "entry_compressed_written", scope: !542, file: !1, line: 126, baseType: !401, size: 64, align: 64, offset: 192)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "entry_uncompressed_written", scope: !542, file: !1, line: 127, baseType: !401, size: 64, align: 64, offset: 256)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "entry_uncompressed_limit", scope: !542, file: !1, line: 128, baseType: !401, size: 64, align: 64, offset: 320)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !542, file: !1, line: 129, baseType: !379, size: 64, align: 64, offset: 384)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "entry_crc32", scope: !542, file: !1, line: 130, baseType: !552, size: 32, align: 32, offset: 448)
!552 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !402, line: 51, baseType: !362)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "entry_compression", scope: !542, file: !1, line: 131, baseType: !3, size: 32, align: 32, offset: 480)
!554 = !DIDerivedType(tag: DW_TAG_member, name: "entry_encryption", scope: !542, file: !1, line: 132, baseType: !8, size: 32, align: 32, offset: 512)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "entry_flags", scope: !542, file: !1, line: 133, baseType: !372, size: 32, align: 32, offset: 544)
!556 = !DIDerivedType(tag: DW_TAG_member, name: "entry_uses_zip64", scope: !542, file: !1, line: 134, baseType: !372, size: 32, align: 32, offset: 576)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "experiments", scope: !542, file: !1, line: 135, baseType: !372, size: 32, align: 32, offset: 608)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "tctx", scope: !542, file: !1, line: 136, baseType: !559, size: 96, align: 32, offset: 640)
!559 = !DICompositeType(tag: DW_TAG_structure_type, name: "trad_enc_ctx", file: !1, line: 117, size: 96, align: 32, elements: !560)
!560 = !{!561}
!561 = !DIDerivedType(tag: DW_TAG_member, name: "keys", scope: !559, file: !1, line: 118, baseType: !562, size: 96, align: 32)
!562 = !DICompositeType(tag: DW_TAG_array_type, baseType: !552, size: 96, align: 32, elements: !563)
!563 = !{!564}
!564 = !DISubrange(count: 3)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "tctx_valid", scope: !542, file: !1, line: 137, baseType: !431, size: 8, align: 8, offset: 736)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "trad_chkdat", scope: !542, file: !1, line: 138, baseType: !466, size: 8, align: 8, offset: 744)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "aes_vendor", scope: !542, file: !1, line: 139, baseType: !362, size: 32, align: 32, offset: 768)
!568 = !DIDerivedType(tag: DW_TAG_member, name: "cctx", scope: !542, file: !1, line: 140, baseType: !569, size: 32, align: 32, offset: 800)
!569 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_crypto_ctx", file: !570, line: 120, baseType: !372)
!570 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cryptor_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!571 = !DIDerivedType(tag: DW_TAG_member, name: "cctx_valid", scope: !542, file: !1, line: 141, baseType: !431, size: 8, align: 8, offset: 832)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "hctx", scope: !542, file: !1, line: 142, baseType: !573, size: 32, align: 32, offset: 864)
!573 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_hmac_sha1_ctx", file: !574, line: 79, baseType: !372)
!574 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_hmac_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!575 = !DIDerivedType(tag: DW_TAG_member, name: "hctx_valid", scope: !542, file: !1, line: 143, baseType: !431, size: 8, align: 8, offset: 896)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "file_header", scope: !542, file: !1, line: 145, baseType: !577, size: 64, align: 64, offset: 960)
!577 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !466, size: 64, align: 64)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "file_header_extra_offset", scope: !542, file: !1, line: 146, baseType: !394, size: 64, align: 64, offset: 1024)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "crc32func", scope: !542, file: !1, line: 147, baseType: !580, size: 64, align: 64, offset: 1088)
!580 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !581, size: 64, align: 64)
!581 = !DISubroutineType(types: !582)
!582 = !{!396, !396, !392, !394}
!583 = !DIDerivedType(tag: DW_TAG_member, name: "central_directory", scope: !542, file: !1, line: 149, baseType: !584, size: 64, align: 64, offset: 1152)
!584 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !585, size: 64, align: 64)
!585 = !DICompositeType(tag: DW_TAG_structure_type, name: "cd_segment", file: !1, line: 110, size: 256, align: 64, elements: !586)
!586 = !{!587, !588, !589, !590}
!587 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !585, file: !1, line: 111, baseType: !584, size: 64, align: 64)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "buff_size", scope: !585, file: !1, line: 112, baseType: !394, size: 64, align: 64, offset: 64)
!589 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !585, file: !1, line: 113, baseType: !577, size: 64, align: 64, offset: 128)
!590 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !585, file: !1, line: 114, baseType: !577, size: 64, align: 64, offset: 192)
!591 = !DIDerivedType(tag: DW_TAG_member, name: "central_directory_last", scope: !542, file: !1, line: 150, baseType: !584, size: 64, align: 64, offset: 1216)
!592 = !DIDerivedType(tag: DW_TAG_member, name: "central_directory_bytes", scope: !542, file: !1, line: 151, baseType: !394, size: 64, align: 64, offset: 1280)
!593 = !DIDerivedType(tag: DW_TAG_member, name: "central_directory_entries", scope: !542, file: !1, line: 152, baseType: !394, size: 64, align: 64, offset: 1344)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "written_bytes", scope: !542, file: !1, line: 154, baseType: !401, size: 64, align: 64, offset: 1408)
!595 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !542, file: !1, line: 156, baseType: !451, size: 64, align: 64, offset: 1472)
!596 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !542, file: !1, line: 157, baseType: !451, size: 64, align: 64, offset: 1536)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "requested_compression", scope: !542, file: !1, line: 158, baseType: !3, size: 32, align: 32, offset: 1600)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "deflate_compression_level", scope: !542, file: !1, line: 159, baseType: !372, size: 32, align: 32, offset: 1632)
!599 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !542, file: !1, line: 160, baseType: !372, size: 32, align: 32, offset: 1664)
!600 = !DIDerivedType(tag: DW_TAG_member, name: "encryption_type", scope: !542, file: !1, line: 161, baseType: !8, size: 32, align: 32, offset: 1696)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !542, file: !1, line: 166, baseType: !372, size: 32, align: 32, offset: 1728)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !542, file: !1, line: 169, baseType: !603, size: 896, align: 64, offset: 1792)
!603 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !604, line: 101, baseType: !605)
!604 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!605 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !604, line: 82, size: 896, align: 64, elements: !606)
!606 = !{!607, !612, !614, !616, !617, !618, !619, !620, !625, !631, !636, !637, !638, !639}
!607 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !605, file: !604, line: 83, baseType: !608, size: 64, align: 64)
!608 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !609, size: 64, align: 64)
!609 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !610, line: 276, baseType: !611)
!610 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!611 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !610, line: 267, baseType: !466)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !605, file: !604, line: 84, baseType: !613, size: 32, align: 32, offset: 64)
!613 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !610, line: 269, baseType: !362)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !605, file: !604, line: 85, baseType: !615, size: 64, align: 64, offset: 128)
!615 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !610, line: 270, baseType: !396)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !605, file: !604, line: 87, baseType: !608, size: 64, align: 64, offset: 192)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !605, file: !604, line: 88, baseType: !613, size: 32, align: 32, offset: 256)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !605, file: !604, line: 89, baseType: !615, size: 64, align: 64, offset: 320)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !605, file: !604, line: 91, baseType: !444, size: 64, align: 64, offset: 384)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !605, file: !604, line: 92, baseType: !621, size: 64, align: 64, offset: 448)
!621 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !622, size: 64, align: 64)
!622 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !604, line: 1346, size: 32, align: 32, elements: !623)
!623 = !{!624}
!624 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !622, file: !604, line: 1346, baseType: !372, size: 32, align: 32)
!625 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !605, file: !604, line: 94, baseType: !626, size: 64, align: 64, offset: 512)
!626 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !604, line: 77, baseType: !627)
!627 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !628, size: 64, align: 64)
!628 = !DISubroutineType(types: !629)
!629 = !{!630, !630, !613, !613}
!630 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !610, line: 285, baseType: !473)
!631 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !605, file: !604, line: 95, baseType: !632, size: 64, align: 64, offset: 576)
!632 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !604, line: 78, baseType: !633)
!633 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !634, size: 64, align: 64)
!634 = !DISubroutineType(types: !635)
!635 = !{null, !630, !630}
!636 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !605, file: !604, line: 96, baseType: !630, size: 64, align: 64, offset: 640)
!637 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !605, file: !604, line: 98, baseType: !372, size: 32, align: 32, offset: 704)
!638 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !605, file: !604, line: 99, baseType: !615, size: 64, align: 64, offset: 768)
!639 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !605, file: !604, line: 100, baseType: !615, size: 64, align: 64, offset: 832)
!640 = !DIDerivedType(tag: DW_TAG_member, name: "len_buf", scope: !542, file: !1, line: 171, baseType: !394, size: 64, align: 64, offset: 2688)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !542, file: !1, line: 172, baseType: !577, size: 64, align: 64, offset: 2752)
!642 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !388, line: 70, baseType: !643)
!643 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !390, line: 129, baseType: !362)
!644 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !402, line: 49, baseType: !645)
!645 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!646 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !647, size: 64, align: 64)
!647 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !648)
!648 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !402, line: 48, baseType: !466)
!649 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !402, line: 122, baseType: !396)
!650 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !402, line: 55, baseType: !396)
!651 = !{!652, !654, !655, !656, !657, !658, !661, !664, !665, !666, !669, !672, !675, !679, !682, !689, !692, !695, !698, !701, !702, !703, !707, !710, !711, !715, !718, !719, !722, !723}
!652 = distinct !DISubprogram(name: "archive_write_zip_set_compression_deflate", scope: !1, file: !1, line: 398, type: !370, isLocal: false, isDefinition: true, scopeLine: 399, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!653 = !{}
!654 = distinct !DISubprogram(name: "archive_write_zip_set_compression_store", scope: !1, file: !1, line: 426, type: !370, isLocal: false, isDefinition: true, scopeLine: 427, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!655 = distinct !DISubprogram(name: "archive_write_set_format_zip", scope: !1, file: !1, line: 448, type: !370, isLocal: false, isDefinition: true, scopeLine: 449, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!656 = distinct !DISubprogram(name: "real_crc32", scope: !1, file: !1, line: 237, type: !581, isLocal: true, isDefinition: true, scopeLine: 238, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!657 = distinct !DISubprogram(name: "archive_write_zip_options", scope: !1, file: !1, line: 252, type: !521, isLocal: true, isDefinition: true, scopeLine: 254, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!658 = distinct !DISubprogram(name: "is_traditional_pkware_encryption_supported", scope: !1, file: !1, line: 1538, type: !659, isLocal: true, isDefinition: true, scopeLine: 1539, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!659 = !DISubroutineType(types: !660)
!660 = !{!372}
!661 = distinct !DISubprogram(name: "is_winzip_aes_encryption_supported", scope: !1, file: !1, line: 1644, type: !662, isLocal: true, isDefinition: true, scopeLine: 1645, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!662 = !DISubroutineType(types: !663)
!663 = !{!372, !372}
!664 = distinct !DISubprogram(name: "fake_crc32", scope: !1, file: !1, line: 243, type: !581, isLocal: true, isDefinition: true, scopeLine: 244, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!665 = distinct !DISubprogram(name: "archive_write_zip_header", scope: !1, file: !1, line: 511, type: !526, isLocal: true, isDefinition: true, scopeLine: 512, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!666 = distinct !DISubprogram(name: "get_sconv", scope: !1, file: !1, line: 1471, type: !667, isLocal: true, isDefinition: true, scopeLine: 1472, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!667 = !DISubroutineType(types: !668)
!668 = !{!451, !353, !541}
!669 = distinct !DISubprogram(name: "is_all_ascii", scope: !1, file: !1, line: 499, type: !670, isLocal: true, isDefinition: true, scopeLine: 500, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!670 = !DISubroutineType(types: !671)
!671 = !{!372, !429}
!672 = distinct !DISubprogram(name: "path_length", scope: !1, file: !1, line: 1403, type: !673, isLocal: true, isDefinition: true, scopeLine: 1404, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!673 = !DISubroutineType(types: !674)
!674 = !{!394, !379}
!675 = distinct !DISubprogram(name: "archive_le16enc", scope: !676, file: !676, line: 168, type: !677, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!676 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!677 = !DISubroutineType(types: !678)
!678 = !{null, !473, !644}
!679 = distinct !DISubprogram(name: "archive_le32enc", scope: !676, file: !676, line: 177, type: !680, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!680 = !DISubroutineType(types: !681)
!681 = !{null, !473, !552}
!682 = distinct !DISubprogram(name: "dos_time", scope: !1, file: !1, line: 1373, type: !683, isLocal: true, isDefinition: true, scopeLine: 1374, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!683 = !DISubroutineType(types: !684)
!684 = !{!362, !685}
!685 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !686)
!686 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !687, line: 75, baseType: !688)
!687 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!688 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !390, line: 139, baseType: !391)
!689 = distinct !DISubprogram(name: "cd_alloc", scope: !1, file: !1, line: 202, type: !690, isLocal: true, isDefinition: true, scopeLine: 203, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!690 = !DISubroutineType(types: !691)
!691 = !{!577, !541, !394}
!692 = distinct !DISubprogram(name: "copy_path", scope: !1, file: !1, line: 1450, type: !693, isLocal: true, isDefinition: true, scopeLine: 1451, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!693 = !DISubroutineType(types: !694)
!694 = !{null, !379, !577}
!695 = distinct !DISubprogram(name: "archive_le64enc", scope: !676, file: !676, line: 188, type: !696, isLocal: true, isDefinition: true, scopeLine: 189, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!696 = !DISubroutineType(types: !697)
!697 = !{null, !473, !650}
!698 = distinct !DISubprogram(name: "write_path", scope: !1, file: !1, line: 1422, type: !699, isLocal: true, isDefinition: true, scopeLine: 1423, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!699 = !DISubroutineType(types: !700)
!700 = !{!372, !379, !353}
!701 = distinct !DISubprogram(name: "archive_write_zip_data", scope: !1, file: !1, line: 1002, type: !530, isLocal: true, isDefinition: true, scopeLine: 1003, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!702 = distinct !DISubprogram(name: "init_traditional_pkware_encryption", scope: !1, file: !1, line: 1548, type: !517, isLocal: true, isDefinition: true, scopeLine: 1549, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!703 = distinct !DISubprogram(name: "trad_enc_init", scope: !1, file: !1, line: 1525, type: !704, isLocal: true, isDefinition: true, scopeLine: 1526, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!704 = !DISubroutineType(types: !705)
!705 = !{!372, !706, !429, !394}
!706 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !559, size: 64, align: 64)
!707 = distinct !DISubprogram(name: "trad_enc_update_keys", scope: !1, file: !1, line: 1489, type: !708, isLocal: true, isDefinition: true, scopeLine: 1490, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!708 = !DISubroutineType(types: !709)
!709 = !{null, !706, !648}
!710 = distinct !DISubprogram(name: "init_winzip_aes_encryption", scope: !1, file: !1, line: 1583, type: !517, isLocal: true, isDefinition: true, scopeLine: 1584, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!711 = distinct !DISubprogram(name: "trad_enc_encrypt_update", scope: !1, file: !1, line: 1509, type: !712, isLocal: true, isDefinition: true, scopeLine: 1511, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!712 = !DISubroutineType(types: !713)
!713 = !{!362, !706, !646, !394, !714, !394}
!714 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !648, size: 64, align: 64)
!715 = distinct !DISubprogram(name: "trad_enc_decrypt_byte", scope: !1, file: !1, line: 1502, type: !716, isLocal: true, isDefinition: true, scopeLine: 1503, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!716 = !DISubroutineType(types: !717)
!717 = !{!648, !706}
!718 = distinct !DISubprogram(name: "archive_write_zip_finish_entry", scope: !1, file: !1, line: 1136, type: !517, isLocal: true, isDefinition: true, scopeLine: 1137, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!719 = distinct !DISubprogram(name: "archive_le16dec", scope: !676, file: !676, line: 101, type: !720, isLocal: true, isDefinition: true, scopeLine: 102, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!720 = !DISubroutineType(types: !721)
!721 = !{!644, !392}
!722 = distinct !DISubprogram(name: "archive_write_zip_close", scope: !1, file: !1, line: 1273, type: !517, isLocal: true, isDefinition: true, scopeLine: 1274, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!723 = distinct !DISubprogram(name: "archive_write_zip_free", scope: !1, file: !1, line: 1346, type: !517, isLocal: true, isDefinition: true, scopeLine: 1347, flags: DIFlagPrototyped, isOptimized: false, variables: !653)
!724 = !{i32 2, !"Dwarf Version", i32 4}
!725 = !{i32 2, !"Debug Info Version", i32 3}
!726 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!727 = !DILocalVariable(name: "_a", arg: 1, scope: !652, file: !1, line: 398, type: !373)
!728 = !DIExpression()
!729 = !DILocation(line: 398, column: 59, scope: !652)
!730 = !DILocalVariable(name: "a", scope: !652, file: !1, line: 400, type: !353)
!731 = !DILocation(line: 400, column: 24, scope: !652)
!732 = !DILocation(line: 400, column: 52, scope: !652)
!733 = !DILocation(line: 400, column: 28, scope: !652)
!734 = !DILocalVariable(name: "ret", scope: !652, file: !1, line: 401, type: !372)
!735 = !DILocation(line: 401, column: 6, scope: !652)
!736 = !DILocation(line: 403, column: 2, scope: !652)
!737 = !DILocalVariable(name: "magic_test", scope: !738, file: !1, line: 403, type: !372)
!738 = distinct !DILexicalBlock(scope: !652, file: !1, line: 403, column: 2)
!739 = !DILocation(line: 403, column: 2, scope: !738)
!740 = !DILocation(line: 403, column: 2, scope: !741)
!741 = !DILexicalBlockFile(scope: !738, file: !1, discriminator: 1)
!742 = !DILocation(line: 403, column: 2, scope: !743)
!743 = !DILexicalBlockFile(scope: !744, file: !1, discriminator: 2)
!744 = distinct !DILexicalBlock(scope: !738, file: !1, line: 403, column: 2)
!745 = !DILocation(line: 403, column: 2, scope: !746)
!746 = !DILexicalBlockFile(scope: !738, file: !1, discriminator: 3)
!747 = !DILocation(line: 406, column: 6, scope: !748)
!748 = distinct !DILexicalBlock(scope: !652, file: !1, line: 406, column: 6)
!749 = !DILocation(line: 406, column: 9, scope: !748)
!750 = !DILocation(line: 406, column: 17, scope: !748)
!751 = !DILocation(line: 406, column: 32, scope: !748)
!752 = !DILocation(line: 406, column: 6, scope: !652)
!753 = !DILocation(line: 407, column: 22, scope: !754)
!754 = distinct !DILexicalBlock(scope: !748, file: !1, line: 406, column: 55)
!755 = !DILocation(line: 407, column: 25, scope: !754)
!756 = !DILocation(line: 407, column: 3, scope: !754)
!757 = !DILocation(line: 410, column: 7, scope: !754)
!758 = !DILocation(line: 411, column: 2, scope: !754)
!759 = !DILocalVariable(name: "zip", scope: !760, file: !1, line: 413, type: !541)
!760 = distinct !DILexicalBlock(scope: !748, file: !1, line: 411, column: 9)
!761 = !DILocation(line: 413, column: 15, scope: !760)
!762 = !DILocation(line: 413, column: 21, scope: !760)
!763 = !DILocation(line: 413, column: 24, scope: !760)
!764 = !DILocation(line: 414, column: 3, scope: !760)
!765 = !DILocation(line: 414, column: 8, scope: !760)
!766 = !DILocation(line: 414, column: 30, scope: !760)
!767 = !DILocation(line: 415, column: 7, scope: !760)
!768 = !DILocation(line: 422, column: 10, scope: !652)
!769 = !DILocation(line: 422, column: 2, scope: !652)
!770 = !DILocation(line: 423, column: 1, scope: !652)
!771 = !DILocalVariable(name: "_a", arg: 1, scope: !654, file: !1, line: 426, type: !373)
!772 = !DILocation(line: 426, column: 57, scope: !654)
!773 = !DILocalVariable(name: "a", scope: !654, file: !1, line: 428, type: !353)
!774 = !DILocation(line: 428, column: 24, scope: !654)
!775 = !DILocation(line: 428, column: 52, scope: !654)
!776 = !DILocation(line: 428, column: 28, scope: !654)
!777 = !DILocalVariable(name: "zip", scope: !654, file: !1, line: 429, type: !541)
!778 = !DILocation(line: 429, column: 14, scope: !654)
!779 = !DILocation(line: 429, column: 20, scope: !654)
!780 = !DILocation(line: 429, column: 23, scope: !654)
!781 = !DILocalVariable(name: "ret", scope: !654, file: !1, line: 430, type: !372)
!782 = !DILocation(line: 430, column: 6, scope: !654)
!783 = !DILocation(line: 432, column: 2, scope: !654)
!784 = !DILocalVariable(name: "magic_test", scope: !785, file: !1, line: 432, type: !372)
!785 = distinct !DILexicalBlock(scope: !654, file: !1, line: 432, column: 2)
!786 = !DILocation(line: 432, column: 2, scope: !785)
!787 = !DILocation(line: 432, column: 2, scope: !788)
!788 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 1)
!789 = !DILocation(line: 432, column: 2, scope: !790)
!790 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 2)
!791 = distinct !DILexicalBlock(scope: !785, file: !1, line: 432, column: 2)
!792 = !DILocation(line: 432, column: 2, scope: !793)
!793 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 3)
!794 = !DILocation(line: 435, column: 6, scope: !795)
!795 = distinct !DILexicalBlock(scope: !654, file: !1, line: 435, column: 6)
!796 = !DILocation(line: 435, column: 9, scope: !795)
!797 = !DILocation(line: 435, column: 17, scope: !795)
!798 = !DILocation(line: 435, column: 32, scope: !795)
!799 = !DILocation(line: 435, column: 6, scope: !654)
!800 = !DILocation(line: 436, column: 22, scope: !801)
!801 = distinct !DILexicalBlock(scope: !795, file: !1, line: 435, column: 55)
!802 = !DILocation(line: 436, column: 25, scope: !801)
!803 = !DILocation(line: 436, column: 3, scope: !801)
!804 = !DILocation(line: 439, column: 7, scope: !801)
!805 = !DILocation(line: 440, column: 2, scope: !801)
!806 = !DILocation(line: 441, column: 3, scope: !807)
!807 = distinct !DILexicalBlock(scope: !795, file: !1, line: 440, column: 9)
!808 = !DILocation(line: 441, column: 8, scope: !807)
!809 = !DILocation(line: 441, column: 30, scope: !807)
!810 = !DILocation(line: 442, column: 7, scope: !807)
!811 = !DILocation(line: 444, column: 10, scope: !654)
!812 = !DILocation(line: 444, column: 2, scope: !654)
!813 = !DILocation(line: 445, column: 1, scope: !654)
!814 = !DILocalVariable(name: "_a", arg: 1, scope: !655, file: !1, line: 448, type: !373)
!815 = !DILocation(line: 448, column: 46, scope: !655)
!816 = !DILocalVariable(name: "a", scope: !655, file: !1, line: 450, type: !353)
!817 = !DILocation(line: 450, column: 24, scope: !655)
!818 = !DILocation(line: 450, column: 52, scope: !655)
!819 = !DILocation(line: 450, column: 28, scope: !655)
!820 = !DILocalVariable(name: "zip", scope: !655, file: !1, line: 451, type: !541)
!821 = !DILocation(line: 451, column: 14, scope: !655)
!822 = !DILocation(line: 453, column: 2, scope: !655)
!823 = !DILocalVariable(name: "magic_test", scope: !824, file: !1, line: 453, type: !372)
!824 = distinct !DILexicalBlock(scope: !655, file: !1, line: 453, column: 2)
!825 = !DILocation(line: 453, column: 2, scope: !824)
!826 = !DILocation(line: 453, column: 2, scope: !827)
!827 = !DILexicalBlockFile(scope: !824, file: !1, discriminator: 1)
!828 = !DILocation(line: 453, column: 2, scope: !829)
!829 = !DILexicalBlockFile(scope: !830, file: !1, discriminator: 2)
!830 = distinct !DILexicalBlock(scope: !824, file: !1, line: 453, column: 2)
!831 = !DILocation(line: 453, column: 2, scope: !832)
!832 = !DILexicalBlockFile(scope: !824, file: !1, discriminator: 3)
!833 = !DILocation(line: 457, column: 6, scope: !834)
!834 = distinct !DILexicalBlock(scope: !655, file: !1, line: 457, column: 6)
!835 = !DILocation(line: 457, column: 9, scope: !834)
!836 = !DILocation(line: 457, column: 21, scope: !834)
!837 = !DILocation(line: 457, column: 6, scope: !655)
!838 = !DILocation(line: 458, column: 4, scope: !834)
!839 = !DILocation(line: 458, column: 7, scope: !834)
!840 = !DILocation(line: 458, column: 20, scope: !834)
!841 = !DILocation(line: 458, column: 3, scope: !834)
!842 = !DILocation(line: 460, column: 23, scope: !655)
!843 = !DILocation(line: 460, column: 8, scope: !655)
!844 = !DILocation(line: 460, column: 6, scope: !655)
!845 = !DILocation(line: 461, column: 6, scope: !846)
!846 = distinct !DILexicalBlock(scope: !655, file: !1, line: 461, column: 6)
!847 = !DILocation(line: 461, column: 10, scope: !846)
!848 = !DILocation(line: 461, column: 6, scope: !655)
!849 = !DILocation(line: 462, column: 22, scope: !850)
!850 = distinct !DILexicalBlock(scope: !846, file: !1, line: 461, column: 19)
!851 = !DILocation(line: 462, column: 25, scope: !850)
!852 = !DILocation(line: 462, column: 3, scope: !850)
!853 = !DILocation(line: 464, column: 3, scope: !850)
!854 = !DILocation(line: 468, column: 2, scope: !655)
!855 = !DILocation(line: 468, column: 7, scope: !655)
!856 = !DILocation(line: 468, column: 29, scope: !655)
!857 = !DILocation(line: 470, column: 2, scope: !655)
!858 = !DILocation(line: 470, column: 7, scope: !655)
!859 = !DILocation(line: 470, column: 33, scope: !655)
!860 = !DILocation(line: 472, column: 2, scope: !655)
!861 = !DILocation(line: 472, column: 7, scope: !655)
!862 = !DILocation(line: 472, column: 17, scope: !655)
!863 = !DILocation(line: 475, column: 2, scope: !655)
!864 = !DILocation(line: 475, column: 7, scope: !655)
!865 = !DILocation(line: 475, column: 15, scope: !655)
!866 = !DILocation(line: 476, column: 20, scope: !655)
!867 = !DILocation(line: 476, column: 25, scope: !655)
!868 = !DILocation(line: 476, column: 13, scope: !655)
!869 = !DILocation(line: 476, column: 2, scope: !655)
!870 = !DILocation(line: 476, column: 7, scope: !655)
!871 = !DILocation(line: 476, column: 11, scope: !655)
!872 = !DILocation(line: 477, column: 6, scope: !873)
!873 = distinct !DILexicalBlock(scope: !655, file: !1, line: 477, column: 6)
!874 = !DILocation(line: 477, column: 11, scope: !873)
!875 = !DILocation(line: 477, column: 15, scope: !873)
!876 = !DILocation(line: 477, column: 6, scope: !655)
!877 = !DILocation(line: 478, column: 8, scope: !878)
!878 = distinct !DILexicalBlock(scope: !873, file: !1, line: 477, column: 24)
!879 = !DILocation(line: 478, column: 3, scope: !878)
!880 = !DILocation(line: 479, column: 22, scope: !878)
!881 = !DILocation(line: 479, column: 25, scope: !878)
!882 = !DILocation(line: 479, column: 3, scope: !878)
!883 = !DILocation(line: 481, column: 3, scope: !878)
!884 = !DILocation(line: 484, column: 19, scope: !655)
!885 = !DILocation(line: 484, column: 2, scope: !655)
!886 = !DILocation(line: 484, column: 5, scope: !655)
!887 = !DILocation(line: 484, column: 17, scope: !655)
!888 = !DILocation(line: 485, column: 2, scope: !655)
!889 = !DILocation(line: 485, column: 5, scope: !655)
!890 = !DILocation(line: 485, column: 17, scope: !655)
!891 = !DILocation(line: 486, column: 2, scope: !655)
!892 = !DILocation(line: 486, column: 5, scope: !655)
!893 = !DILocation(line: 486, column: 20, scope: !655)
!894 = !DILocation(line: 487, column: 2, scope: !655)
!895 = !DILocation(line: 487, column: 5, scope: !655)
!896 = !DILocation(line: 487, column: 25, scope: !655)
!897 = !DILocation(line: 488, column: 2, scope: !655)
!898 = !DILocation(line: 488, column: 5, scope: !655)
!899 = !DILocation(line: 488, column: 23, scope: !655)
!900 = !DILocation(line: 489, column: 2, scope: !655)
!901 = !DILocation(line: 489, column: 5, scope: !655)
!902 = !DILocation(line: 489, column: 25, scope: !655)
!903 = !DILocation(line: 490, column: 2, scope: !655)
!904 = !DILocation(line: 490, column: 5, scope: !655)
!905 = !DILocation(line: 490, column: 18, scope: !655)
!906 = !DILocation(line: 491, column: 2, scope: !655)
!907 = !DILocation(line: 491, column: 5, scope: !655)
!908 = !DILocation(line: 491, column: 17, scope: !655)
!909 = !DILocation(line: 492, column: 2, scope: !655)
!910 = !DILocation(line: 492, column: 5, scope: !655)
!911 = !DILocation(line: 492, column: 13, scope: !655)
!912 = !DILocation(line: 492, column: 28, scope: !655)
!913 = !DILocation(line: 493, column: 2, scope: !655)
!914 = !DILocation(line: 493, column: 5, scope: !655)
!915 = !DILocation(line: 493, column: 13, scope: !655)
!916 = !DILocation(line: 493, column: 33, scope: !655)
!917 = !DILocation(line: 495, column: 2, scope: !655)
!918 = !DILocation(line: 496, column: 1, scope: !655)
!919 = !DILocalVariable(name: "crc", arg: 1, scope: !656, file: !1, line: 237, type: !396)
!920 = !DILocation(line: 237, column: 26, scope: !656)
!921 = !DILocalVariable(name: "buff", arg: 2, scope: !656, file: !1, line: 237, type: !392)
!922 = !DILocation(line: 237, column: 43, scope: !656)
!923 = !DILocalVariable(name: "len", arg: 3, scope: !656, file: !1, line: 237, type: !394)
!924 = !DILocation(line: 237, column: 56, scope: !656)
!925 = !DILocation(line: 239, column: 15, scope: !656)
!926 = !DILocation(line: 239, column: 20, scope: !656)
!927 = !DILocation(line: 239, column: 40, scope: !656)
!928 = !DILocation(line: 239, column: 26, scope: !656)
!929 = !DILocation(line: 239, column: 9, scope: !656)
!930 = !DILocation(line: 239, column: 2, scope: !656)
!931 = !DILocalVariable(name: "a", arg: 1, scope: !657, file: !1, line: 252, type: !353)
!932 = !DILocation(line: 252, column: 49, scope: !657)
!933 = !DILocalVariable(name: "key", arg: 2, scope: !657, file: !1, line: 252, type: !429)
!934 = !DILocation(line: 252, column: 64, scope: !657)
!935 = !DILocalVariable(name: "val", arg: 3, scope: !657, file: !1, line: 253, type: !429)
!936 = !DILocation(line: 253, column: 17, scope: !657)
!937 = !DILocalVariable(name: "zip", scope: !657, file: !1, line: 255, type: !541)
!938 = !DILocation(line: 255, column: 14, scope: !657)
!939 = !DILocation(line: 255, column: 20, scope: !657)
!940 = !DILocation(line: 255, column: 23, scope: !657)
!941 = !DILocalVariable(name: "ret", scope: !657, file: !1, line: 256, type: !372)
!942 = !DILocation(line: 256, column: 6, scope: !657)
!943 = !DILocation(line: 258, column: 13, scope: !944)
!944 = distinct !DILexicalBlock(scope: !657, file: !1, line: 258, column: 6)
!945 = !DILocation(line: 258, column: 6, scope: !944)
!946 = !DILocation(line: 258, column: 33, scope: !944)
!947 = !DILocation(line: 258, column: 6, scope: !657)
!948 = !DILocation(line: 263, column: 7, scope: !949)
!949 = distinct !DILexicalBlock(scope: !950, file: !1, line: 263, column: 7)
!950 = distinct !DILexicalBlock(scope: !944, file: !1, line: 258, column: 39)
!951 = !DILocation(line: 263, column: 11, scope: !949)
!952 = !DILocation(line: 263, column: 19, scope: !949)
!953 = !DILocation(line: 263, column: 22, scope: !954)
!954 = !DILexicalBlockFile(scope: !949, file: !1, discriminator: 1)
!955 = !DILocation(line: 263, column: 29, scope: !954)
!956 = !DILocation(line: 263, column: 7, scope: !954)
!957 = !DILocation(line: 264, column: 23, scope: !958)
!958 = distinct !DILexicalBlock(scope: !949, file: !1, line: 263, column: 35)
!959 = !DILocation(line: 264, column: 26, scope: !958)
!960 = !DILocation(line: 266, column: 8, scope: !958)
!961 = !DILocation(line: 266, column: 11, scope: !958)
!962 = !DILocation(line: 264, column: 4, scope: !958)
!963 = !DILocation(line: 267, column: 3, scope: !958)
!964 = !DILocation(line: 267, column: 21, scope: !965)
!965 = !DILexicalBlockFile(scope: !966, file: !1, discriminator: 1)
!966 = distinct !DILexicalBlock(scope: !949, file: !1, line: 267, column: 14)
!967 = !DILocation(line: 267, column: 14, scope: !965)
!968 = !DILocation(line: 267, column: 37, scope: !965)
!969 = !DILocation(line: 269, column: 4, scope: !970)
!970 = distinct !DILexicalBlock(scope: !966, file: !1, line: 267, column: 43)
!971 = !DILocation(line: 269, column: 9, scope: !970)
!972 = !DILocation(line: 269, column: 31, scope: !970)
!973 = !DILocation(line: 270, column: 8, scope: !970)
!974 = !DILocation(line: 275, column: 3, scope: !970)
!975 = !DILocation(line: 275, column: 21, scope: !976)
!976 = !DILexicalBlockFile(scope: !977, file: !1, discriminator: 1)
!977 = distinct !DILexicalBlock(scope: !966, file: !1, line: 275, column: 14)
!978 = !DILocation(line: 275, column: 14, scope: !976)
!979 = !DILocation(line: 275, column: 35, scope: !976)
!980 = !DILocation(line: 276, column: 4, scope: !981)
!981 = distinct !DILexicalBlock(scope: !977, file: !1, line: 275, column: 41)
!982 = !DILocation(line: 276, column: 9, scope: !981)
!983 = !DILocation(line: 276, column: 31, scope: !981)
!984 = !DILocation(line: 277, column: 8, scope: !981)
!985 = !DILocation(line: 278, column: 3, scope: !981)
!986 = !DILocation(line: 279, column: 11, scope: !950)
!987 = !DILocation(line: 279, column: 3, scope: !950)
!988 = !DILocation(line: 280, column: 20, scope: !989)
!989 = distinct !DILexicalBlock(scope: !944, file: !1, line: 280, column: 13)
!990 = !DILocation(line: 280, column: 13, scope: !989)
!991 = !DILocation(line: 280, column: 46, scope: !989)
!992 = !DILocation(line: 280, column: 13, scope: !944)
!993 = !DILocation(line: 281, column: 7, scope: !994)
!994 = distinct !DILexicalBlock(scope: !995, file: !1, line: 281, column: 7)
!995 = distinct !DILexicalBlock(scope: !989, file: !1, line: 280, column: 52)
!996 = !DILocation(line: 281, column: 11, scope: !994)
!997 = !DILocation(line: 281, column: 19, scope: !994)
!998 = !DILocation(line: 281, column: 24, scope: !999)
!999 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 1)
!1000 = !DILocation(line: 281, column: 31, scope: !999)
!1001 = !DILocation(line: 281, column: 38, scope: !999)
!1002 = !DILocation(line: 281, column: 41, scope: !1003)
!1003 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 2)
!1004 = !DILocation(line: 281, column: 48, scope: !1003)
!1005 = !DILocation(line: 281, column: 56, scope: !1003)
!1006 = !DILocation(line: 281, column: 59, scope: !1007)
!1007 = !DILexicalBlockFile(scope: !994, file: !1, discriminator: 3)
!1008 = !DILocation(line: 281, column: 66, scope: !1007)
!1009 = !DILocation(line: 281, column: 7, scope: !1007)
!1010 = !DILocation(line: 282, column: 4, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !994, file: !1, line: 281, column: 75)
!1012 = !DILocation(line: 285, column: 7, scope: !1013)
!1013 = distinct !DILexicalBlock(scope: !995, file: !1, line: 285, column: 7)
!1014 = !DILocation(line: 285, column: 14, scope: !1013)
!1015 = !DILocation(line: 285, column: 7, scope: !995)
!1016 = !DILocation(line: 286, column: 4, scope: !1017)
!1017 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 285, column: 22)
!1018 = !DILocation(line: 286, column: 9, scope: !1017)
!1019 = !DILocation(line: 286, column: 31, scope: !1017)
!1020 = !DILocation(line: 287, column: 4, scope: !1017)
!1021 = !DILocation(line: 290, column: 4, scope: !1022)
!1022 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 288, column: 10)
!1023 = !DILocation(line: 290, column: 9, scope: !1022)
!1024 = !DILocation(line: 290, column: 31, scope: !1022)
!1025 = !DILocation(line: 291, column: 37, scope: !1022)
!1026 = !DILocation(line: 291, column: 44, scope: !1022)
!1027 = !DILocation(line: 291, column: 4, scope: !1022)
!1028 = !DILocation(line: 291, column: 9, scope: !1022)
!1029 = !DILocation(line: 291, column: 35, scope: !1022)
!1030 = !DILocation(line: 292, column: 4, scope: !1022)
!1031 = !DILocation(line: 298, column: 20, scope: !1032)
!1032 = distinct !DILexicalBlock(scope: !989, file: !1, line: 298, column: 13)
!1033 = !DILocation(line: 298, column: 13, scope: !1032)
!1034 = !DILocation(line: 298, column: 39, scope: !1032)
!1035 = !DILocation(line: 298, column: 13, scope: !989)
!1036 = !DILocation(line: 299, column: 7, scope: !1037)
!1037 = distinct !DILexicalBlock(scope: !1038, file: !1, line: 299, column: 7)
!1038 = distinct !DILexicalBlock(scope: !1032, file: !1, line: 298, column: 45)
!1039 = !DILocation(line: 299, column: 11, scope: !1037)
!1040 = !DILocation(line: 299, column: 7, scope: !1038)
!1041 = !DILocation(line: 300, column: 4, scope: !1042)
!1042 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 299, column: 20)
!1043 = !DILocation(line: 300, column: 9, scope: !1042)
!1044 = !DILocation(line: 300, column: 25, scope: !1042)
!1045 = !DILocation(line: 301, column: 8, scope: !1042)
!1046 = !DILocation(line: 302, column: 3, scope: !1042)
!1047 = !DILocation(line: 302, column: 14, scope: !1048)
!1048 = !DILexicalBlockFile(scope: !1049, file: !1, discriminator: 1)
!1049 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 302, column: 14)
!1050 = !DILocation(line: 302, column: 21, scope: !1048)
!1051 = !DILocation(line: 302, column: 28, scope: !1048)
!1052 = !DILocation(line: 302, column: 38, scope: !1053)
!1053 = !DILexicalBlockFile(scope: !1049, file: !1, discriminator: 2)
!1054 = !DILocation(line: 302, column: 31, scope: !1053)
!1055 = !DILocation(line: 302, column: 58, scope: !1053)
!1056 = !DILocation(line: 303, column: 7, scope: !1049)
!1057 = !DILocation(line: 303, column: 17, scope: !1048)
!1058 = !DILocation(line: 303, column: 10, scope: !1048)
!1059 = !DILocation(line: 303, column: 34, scope: !1048)
!1060 = !DILocation(line: 304, column: 7, scope: !1049)
!1061 = !DILocation(line: 304, column: 17, scope: !1048)
!1062 = !DILocation(line: 304, column: 10, scope: !1048)
!1063 = !DILocation(line: 304, column: 34, scope: !1048)
!1064 = !DILocation(line: 302, column: 14, scope: !1065)
!1065 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 3)
!1066 = !DILocation(line: 305, column: 8, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 305, column: 8)
!1068 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 304, column: 40)
!1069 = !DILocation(line: 305, column: 8, scope: !1068)
!1070 = !DILocation(line: 306, column: 5, scope: !1071)
!1071 = distinct !DILexicalBlock(scope: !1067, file: !1, line: 305, column: 54)
!1072 = !DILocation(line: 306, column: 10, scope: !1071)
!1073 = !DILocation(line: 306, column: 26, scope: !1071)
!1074 = !DILocation(line: 307, column: 9, scope: !1071)
!1075 = !DILocation(line: 308, column: 4, scope: !1071)
!1076 = !DILocation(line: 309, column: 24, scope: !1077)
!1077 = distinct !DILexicalBlock(scope: !1067, file: !1, line: 308, column: 11)
!1078 = !DILocation(line: 309, column: 27, scope: !1077)
!1079 = !DILocation(line: 309, column: 5, scope: !1077)
!1080 = !DILocation(line: 313, column: 3, scope: !1068)
!1081 = !DILocation(line: 313, column: 21, scope: !1082)
!1082 = !DILexicalBlockFile(scope: !1083, file: !1, discriminator: 1)
!1083 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 313, column: 14)
!1084 = !DILocation(line: 313, column: 14, scope: !1082)
!1085 = !DILocation(line: 313, column: 36, scope: !1082)
!1086 = !DILocation(line: 314, column: 8, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !1088, file: !1, line: 314, column: 8)
!1088 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 313, column: 42)
!1089 = !DILocation(line: 314, column: 8, scope: !1088)
!1090 = !DILocation(line: 316, column: 5, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 315, column: 35)
!1092 = !DILocation(line: 316, column: 10, scope: !1091)
!1093 = !DILocation(line: 316, column: 26, scope: !1091)
!1094 = !DILocation(line: 317, column: 9, scope: !1091)
!1095 = !DILocation(line: 318, column: 4, scope: !1091)
!1096 = !DILocation(line: 319, column: 24, scope: !1097)
!1097 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 318, column: 11)
!1098 = !DILocation(line: 319, column: 27, scope: !1097)
!1099 = !DILocation(line: 319, column: 5, scope: !1097)
!1100 = !DILocation(line: 323, column: 3, scope: !1088)
!1101 = !DILocation(line: 323, column: 21, scope: !1102)
!1102 = !DILexicalBlockFile(scope: !1103, file: !1, discriminator: 1)
!1103 = distinct !DILexicalBlock(scope: !1083, file: !1, line: 323, column: 14)
!1104 = !DILocation(line: 323, column: 14, scope: !1102)
!1105 = !DILocation(line: 323, column: 36, scope: !1102)
!1106 = !DILocation(line: 324, column: 8, scope: !1107)
!1107 = distinct !DILexicalBlock(scope: !1108, file: !1, line: 324, column: 8)
!1108 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 323, column: 42)
!1109 = !DILocation(line: 324, column: 8, scope: !1108)
!1110 = !DILocation(line: 326, column: 5, scope: !1111)
!1111 = distinct !DILexicalBlock(scope: !1107, file: !1, line: 325, column: 35)
!1112 = !DILocation(line: 326, column: 10, scope: !1111)
!1113 = !DILocation(line: 326, column: 26, scope: !1111)
!1114 = !DILocation(line: 327, column: 9, scope: !1111)
!1115 = !DILocation(line: 328, column: 4, scope: !1111)
!1116 = !DILocation(line: 329, column: 24, scope: !1117)
!1117 = distinct !DILexicalBlock(scope: !1107, file: !1, line: 328, column: 11)
!1118 = !DILocation(line: 329, column: 27, scope: !1117)
!1119 = !DILocation(line: 329, column: 5, scope: !1117)
!1120 = !DILocation(line: 333, column: 3, scope: !1108)
!1121 = !DILocation(line: 334, column: 23, scope: !1122)
!1122 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 333, column: 10)
!1123 = !DILocation(line: 334, column: 26, scope: !1122)
!1124 = !DILocation(line: 336, column: 8, scope: !1122)
!1125 = !DILocation(line: 336, column: 11, scope: !1122)
!1126 = !DILocation(line: 336, column: 24, scope: !1122)
!1127 = !DILocation(line: 334, column: 4, scope: !1122)
!1128 = !DILocation(line: 338, column: 11, scope: !1038)
!1129 = !DILocation(line: 338, column: 3, scope: !1038)
!1130 = !DILocation(line: 339, column: 20, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !1032, file: !1, line: 339, column: 13)
!1132 = !DILocation(line: 339, column: 13, scope: !1131)
!1133 = !DILocation(line: 339, column: 41, scope: !1131)
!1134 = !DILocation(line: 339, column: 13, scope: !1032)
!1135 = !DILocation(line: 340, column: 7, scope: !1136)
!1136 = distinct !DILexicalBlock(scope: !1137, file: !1, line: 340, column: 7)
!1137 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 339, column: 47)
!1138 = !DILocation(line: 340, column: 11, scope: !1136)
!1139 = !DILocation(line: 340, column: 19, scope: !1136)
!1140 = !DILocation(line: 340, column: 22, scope: !1141)
!1141 = !DILexicalBlockFile(scope: !1136, file: !1, discriminator: 1)
!1142 = !DILocation(line: 340, column: 29, scope: !1141)
!1143 = !DILocation(line: 340, column: 7, scope: !1141)
!1144 = !DILocation(line: 341, column: 4, scope: !1145)
!1145 = distinct !DILexicalBlock(scope: !1136, file: !1, line: 340, column: 35)
!1146 = !DILocation(line: 341, column: 9, scope: !1145)
!1147 = !DILocation(line: 341, column: 15, scope: !1145)
!1148 = !DILocation(line: 342, column: 3, scope: !1145)
!1149 = !DILocation(line: 343, column: 4, scope: !1150)
!1150 = distinct !DILexicalBlock(scope: !1136, file: !1, line: 342, column: 10)
!1151 = !DILocation(line: 343, column: 9, scope: !1150)
!1152 = !DILocation(line: 343, column: 15, scope: !1150)
!1153 = !DILocation(line: 345, column: 3, scope: !1137)
!1154 = !DILocation(line: 346, column: 20, scope: !1155)
!1155 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 346, column: 13)
!1156 = !DILocation(line: 346, column: 13, scope: !1155)
!1157 = !DILocation(line: 346, column: 38, scope: !1155)
!1158 = !DILocation(line: 346, column: 13, scope: !1131)
!1159 = !DILocation(line: 351, column: 7, scope: !1160)
!1160 = distinct !DILexicalBlock(scope: !1161, file: !1, line: 351, column: 7)
!1161 = distinct !DILexicalBlock(scope: !1155, file: !1, line: 346, column: 44)
!1162 = !DILocation(line: 351, column: 11, scope: !1160)
!1163 = !DILocation(line: 351, column: 19, scope: !1160)
!1164 = !DILocation(line: 351, column: 22, scope: !1165)
!1165 = !DILexicalBlockFile(scope: !1160, file: !1, discriminator: 1)
!1166 = !DILocation(line: 351, column: 29, scope: !1165)
!1167 = !DILocation(line: 351, column: 7, scope: !1165)
!1168 = !DILocation(line: 352, column: 4, scope: !1169)
!1169 = distinct !DILexicalBlock(scope: !1160, file: !1, line: 351, column: 35)
!1170 = !DILocation(line: 352, column: 9, scope: !1169)
!1171 = !DILocation(line: 352, column: 19, scope: !1169)
!1172 = !DILocation(line: 353, column: 3, scope: !1169)
!1173 = !DILocation(line: 354, column: 4, scope: !1174)
!1174 = distinct !DILexicalBlock(scope: !1160, file: !1, line: 353, column: 10)
!1175 = !DILocation(line: 354, column: 9, scope: !1174)
!1176 = !DILocation(line: 354, column: 19, scope: !1174)
!1177 = !DILocation(line: 356, column: 3, scope: !1161)
!1178 = !DILocation(line: 357, column: 20, scope: !1179)
!1179 = distinct !DILexicalBlock(scope: !1155, file: !1, line: 357, column: 13)
!1180 = !DILocation(line: 357, column: 13, scope: !1179)
!1181 = !DILocation(line: 357, column: 40, scope: !1179)
!1182 = !DILocation(line: 357, column: 13, scope: !1155)
!1183 = !DILocation(line: 361, column: 7, scope: !1184)
!1184 = distinct !DILexicalBlock(scope: !1185, file: !1, line: 361, column: 7)
!1185 = distinct !DILexicalBlock(scope: !1179, file: !1, line: 357, column: 46)
!1186 = !DILocation(line: 361, column: 11, scope: !1184)
!1187 = !DILocation(line: 361, column: 19, scope: !1184)
!1188 = !DILocation(line: 361, column: 22, scope: !1189)
!1189 = !DILexicalBlockFile(scope: !1184, file: !1, discriminator: 1)
!1190 = !DILocation(line: 361, column: 29, scope: !1189)
!1191 = !DILocation(line: 361, column: 7, scope: !1189)
!1192 = !DILocation(line: 362, column: 23, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !1184, file: !1, line: 361, column: 35)
!1194 = !DILocation(line: 362, column: 26, scope: !1193)
!1195 = !DILocation(line: 364, column: 8, scope: !1193)
!1196 = !DILocation(line: 364, column: 11, scope: !1193)
!1197 = !DILocation(line: 362, column: 4, scope: !1193)
!1198 = !DILocation(line: 365, column: 3, scope: !1193)
!1199 = !DILocation(line: 367, column: 9, scope: !1200)
!1200 = distinct !DILexicalBlock(scope: !1184, file: !1, line: 365, column: 10)
!1201 = !DILocation(line: 367, column: 12, scope: !1200)
!1202 = !DILocation(line: 367, column: 21, scope: !1200)
!1203 = !DILocation(line: 366, column: 21, scope: !1200)
!1204 = !DILocation(line: 366, column: 4, scope: !1200)
!1205 = !DILocation(line: 366, column: 9, scope: !1200)
!1206 = !DILocation(line: 366, column: 19, scope: !1200)
!1207 = !DILocation(line: 368, column: 8, scope: !1208)
!1208 = distinct !DILexicalBlock(scope: !1200, file: !1, line: 368, column: 8)
!1209 = !DILocation(line: 368, column: 13, scope: !1208)
!1210 = !DILocation(line: 368, column: 23, scope: !1208)
!1211 = !DILocation(line: 368, column: 8, scope: !1200)
!1212 = !DILocation(line: 369, column: 9, scope: !1208)
!1213 = !DILocation(line: 369, column: 5, scope: !1208)
!1214 = !DILocation(line: 371, column: 9, scope: !1208)
!1215 = !DILocation(line: 373, column: 11, scope: !1185)
!1216 = !DILocation(line: 373, column: 3, scope: !1185)
!1217 = !DILocation(line: 374, column: 20, scope: !1218)
!1218 = distinct !DILexicalBlock(scope: !1179, file: !1, line: 374, column: 13)
!1219 = !DILocation(line: 374, column: 13, scope: !1218)
!1220 = !DILocation(line: 374, column: 34, scope: !1218)
!1221 = !DILocation(line: 374, column: 13, scope: !1179)
!1222 = !DILocation(line: 381, column: 7, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !1224, file: !1, line: 381, column: 7)
!1224 = distinct !DILexicalBlock(scope: !1218, file: !1, line: 374, column: 40)
!1225 = !DILocation(line: 381, column: 11, scope: !1223)
!1226 = !DILocation(line: 381, column: 19, scope: !1223)
!1227 = !DILocation(line: 381, column: 23, scope: !1228)
!1228 = !DILexicalBlockFile(scope: !1223, file: !1, discriminator: 1)
!1229 = !DILocation(line: 381, column: 22, scope: !1228)
!1230 = !DILocation(line: 381, column: 27, scope: !1228)
!1231 = !DILocation(line: 381, column: 7, scope: !1228)
!1232 = !DILocation(line: 382, column: 4, scope: !1233)
!1233 = distinct !DILexicalBlock(scope: !1223, file: !1, line: 381, column: 36)
!1234 = !DILocation(line: 382, column: 9, scope: !1233)
!1235 = !DILocation(line: 382, column: 15, scope: !1233)
!1236 = !DILocation(line: 383, column: 4, scope: !1233)
!1237 = !DILocation(line: 383, column: 9, scope: !1233)
!1238 = !DILocation(line: 383, column: 15, scope: !1233)
!1239 = !DILocation(line: 384, column: 3, scope: !1233)
!1240 = !DILocation(line: 385, column: 4, scope: !1241)
!1241 = distinct !DILexicalBlock(scope: !1223, file: !1, line: 384, column: 10)
!1242 = !DILocation(line: 385, column: 9, scope: !1241)
!1243 = !DILocation(line: 385, column: 15, scope: !1241)
!1244 = !DILocation(line: 386, column: 4, scope: !1241)
!1245 = !DILocation(line: 386, column: 9, scope: !1241)
!1246 = !DILocation(line: 386, column: 15, scope: !1241)
!1247 = !DILocation(line: 388, column: 3, scope: !1224)
!1248 = !DILocation(line: 394, column: 2, scope: !657)
!1249 = !DILocation(line: 395, column: 1, scope: !657)
!1250 = !DILocalVariable(name: "a", arg: 1, scope: !665, file: !1, line: 511, type: !353)
!1251 = !DILocation(line: 511, column: 48, scope: !665)
!1252 = !DILocalVariable(name: "entry", arg: 2, scope: !665, file: !1, line: 511, type: !379)
!1253 = !DILocation(line: 511, column: 73, scope: !665)
!1254 = !DILocalVariable(name: "local_header", scope: !665, file: !1, line: 513, type: !1255)
!1255 = !DICompositeType(tag: DW_TAG_array_type, baseType: !466, size: 256, align: 8, elements: !1256)
!1256 = !{!1257}
!1257 = !DISubrange(count: 32)
!1258 = !DILocation(line: 513, column: 16, scope: !665)
!1259 = !DILocalVariable(name: "local_extra", scope: !665, file: !1, line: 514, type: !1260)
!1260 = !DICompositeType(tag: DW_TAG_array_type, baseType: !466, size: 1152, align: 8, elements: !1261)
!1261 = !{!1262}
!1262 = !DISubrange(count: 144)
!1263 = !DILocation(line: 514, column: 16, scope: !665)
!1264 = !DILocalVariable(name: "zip", scope: !665, file: !1, line: 515, type: !541)
!1265 = !DILocation(line: 515, column: 14, scope: !665)
!1266 = !DILocation(line: 515, column: 20, scope: !665)
!1267 = !DILocation(line: 515, column: 23, scope: !665)
!1268 = !DILocalVariable(name: "e", scope: !665, file: !1, line: 516, type: !577)
!1269 = !DILocation(line: 516, column: 17, scope: !665)
!1270 = !DILocalVariable(name: "cd_extra", scope: !665, file: !1, line: 517, type: !577)
!1271 = !DILocation(line: 517, column: 17, scope: !665)
!1272 = !DILocalVariable(name: "filename_length", scope: !665, file: !1, line: 518, type: !394)
!1273 = !DILocation(line: 518, column: 9, scope: !665)
!1274 = !DILocalVariable(name: "slink", scope: !665, file: !1, line: 519, type: !429)
!1275 = !DILocation(line: 519, column: 14, scope: !665)
!1276 = !DILocalVariable(name: "slink_size", scope: !665, file: !1, line: 520, type: !394)
!1277 = !DILocation(line: 520, column: 9, scope: !665)
!1278 = !DILocalVariable(name: "sconv", scope: !665, file: !1, line: 521, type: !451)
!1279 = !DILocation(line: 521, column: 30, scope: !665)
!1280 = !DILocation(line: 521, column: 48, scope: !665)
!1281 = !DILocation(line: 521, column: 51, scope: !665)
!1282 = !DILocation(line: 521, column: 38, scope: !665)
!1283 = !DILocalVariable(name: "ret", scope: !665, file: !1, line: 522, type: !372)
!1284 = !DILocation(line: 522, column: 6, scope: !665)
!1285 = !DILocalVariable(name: "ret2", scope: !665, file: !1, line: 522, type: !372)
!1286 = !DILocation(line: 522, column: 11, scope: !665)
!1287 = !DILocalVariable(name: "type", scope: !665, file: !1, line: 523, type: !642)
!1288 = !DILocation(line: 523, column: 9, scope: !665)
!1289 = !DILocalVariable(name: "version_needed", scope: !665, file: !1, line: 524, type: !372)
!1290 = !DILocation(line: 524, column: 6, scope: !665)
!1291 = !DILocation(line: 527, column: 32, scope: !665)
!1292 = !DILocation(line: 527, column: 9, scope: !665)
!1293 = !DILocation(line: 527, column: 7, scope: !665)
!1294 = !DILocation(line: 528, column: 6, scope: !1295)
!1295 = distinct !DILexicalBlock(scope: !665, file: !1, line: 528, column: 6)
!1296 = !DILocation(line: 528, column: 11, scope: !1295)
!1297 = !DILocation(line: 528, column: 23, scope: !1295)
!1298 = !DILocation(line: 528, column: 26, scope: !1299)
!1299 = !DILexicalBlockFile(scope: !1295, file: !1, discriminator: 1)
!1300 = !DILocation(line: 528, column: 31, scope: !1299)
!1301 = !DILocation(line: 528, column: 43, scope: !1299)
!1302 = !DILocation(line: 528, column: 46, scope: !1303)
!1303 = !DILexicalBlockFile(scope: !1295, file: !1, discriminator: 2)
!1304 = !DILocation(line: 528, column: 51, scope: !1303)
!1305 = !DILocation(line: 528, column: 6, scope: !1303)
!1306 = !DILocation(line: 529, column: 22, scope: !1307)
!1307 = distinct !DILexicalBlock(scope: !1295, file: !1, line: 528, column: 64)
!1308 = !DILocation(line: 529, column: 25, scope: !1307)
!1309 = !DILocation(line: 529, column: 3, scope: !1307)
!1310 = !DILocation(line: 531, column: 3, scope: !1307)
!1311 = !DILocation(line: 535, column: 6, scope: !1312)
!1312 = distinct !DILexicalBlock(scope: !665, file: !1, line: 535, column: 6)
!1313 = !DILocation(line: 535, column: 11, scope: !1312)
!1314 = !DILocation(line: 535, column: 17, scope: !1312)
!1315 = !DILocation(line: 535, column: 6, scope: !665)
!1316 = !DILocation(line: 537, column: 33, scope: !1317)
!1317 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 537, column: 7)
!1318 = distinct !DILexicalBlock(scope: !1312, file: !1, line: 535, column: 41)
!1319 = !DILocation(line: 537, column: 7, scope: !1317)
!1320 = !DILocation(line: 538, column: 7, scope: !1317)
!1321 = !DILocation(line: 538, column: 30, scope: !1322)
!1322 = !DILexicalBlockFile(scope: !1317, file: !1, discriminator: 1)
!1323 = !DILocation(line: 538, column: 11, scope: !1322)
!1324 = !DILocation(line: 538, column: 37, scope: !1322)
!1325 = !DILocation(line: 537, column: 7, scope: !1326)
!1326 = !DILexicalBlockFile(scope: !1318, file: !1, discriminator: 1)
!1327 = !DILocation(line: 539, column: 23, scope: !1328)
!1328 = distinct !DILexicalBlock(scope: !1317, file: !1, line: 538, column: 53)
!1329 = !DILocation(line: 539, column: 26, scope: !1328)
!1330 = !DILocation(line: 539, column: 4, scope: !1328)
!1331 = !DILocation(line: 541, column: 4, scope: !1328)
!1332 = !DILocation(line: 544, column: 7, scope: !1333)
!1333 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 544, column: 7)
!1334 = !DILocation(line: 544, column: 12, scope: !1333)
!1335 = !DILocation(line: 544, column: 26, scope: !1333)
!1336 = !DILocation(line: 544, column: 7, scope: !1318)
!1337 = !DILocation(line: 545, column: 23, scope: !1338)
!1338 = distinct !DILexicalBlock(scope: !1333, file: !1, line: 544, column: 41)
!1339 = !DILocation(line: 545, column: 26, scope: !1338)
!1340 = !DILocation(line: 545, column: 4, scope: !1338)
!1341 = !DILocation(line: 547, column: 4, scope: !1338)
!1342 = !DILocation(line: 549, column: 2, scope: !1318)
!1343 = !DILocation(line: 552, column: 6, scope: !1344)
!1344 = distinct !DILexicalBlock(scope: !665, file: !1, line: 552, column: 6)
!1345 = !DILocation(line: 552, column: 11, scope: !1344)
!1346 = !DILocation(line: 552, column: 6, scope: !665)
!1347 = !DILocation(line: 553, column: 26, scope: !1344)
!1348 = !DILocation(line: 553, column: 3, scope: !1344)
!1349 = !DILocation(line: 557, column: 22, scope: !665)
!1350 = !DILocation(line: 557, column: 27, scope: !665)
!1351 = !DILocation(line: 557, column: 2, scope: !665)
!1352 = !DILocation(line: 557, column: 7, scope: !665)
!1353 = !DILocation(line: 557, column: 20, scope: !665)
!1354 = !DILocation(line: 558, column: 2, scope: !665)
!1355 = !DILocation(line: 558, column: 7, scope: !665)
!1356 = !DILocation(line: 558, column: 32, scope: !665)
!1357 = !DILocation(line: 559, column: 2, scope: !665)
!1358 = !DILocation(line: 559, column: 7, scope: !665)
!1359 = !DILocation(line: 559, column: 29, scope: !665)
!1360 = !DILocation(line: 560, column: 2, scope: !665)
!1361 = !DILocation(line: 560, column: 7, scope: !665)
!1362 = !DILocation(line: 560, column: 31, scope: !665)
!1363 = !DILocation(line: 561, column: 2, scope: !665)
!1364 = !DILocation(line: 561, column: 7, scope: !665)
!1365 = !DILocation(line: 561, column: 32, scope: !665)
!1366 = !DILocation(line: 562, column: 2, scope: !665)
!1367 = !DILocation(line: 562, column: 7, scope: !665)
!1368 = !DILocation(line: 562, column: 34, scope: !665)
!1369 = !DILocation(line: 563, column: 2, scope: !665)
!1370 = !DILocation(line: 563, column: 7, scope: !665)
!1371 = !DILocation(line: 563, column: 19, scope: !665)
!1372 = !DILocation(line: 564, column: 2, scope: !665)
!1373 = !DILocation(line: 564, column: 7, scope: !665)
!1374 = !DILocation(line: 564, column: 24, scope: !665)
!1375 = !DILocation(line: 565, column: 21, scope: !665)
!1376 = !DILocation(line: 565, column: 26, scope: !665)
!1377 = !DILocation(line: 565, column: 2, scope: !665)
!1378 = !DILocation(line: 565, column: 7, scope: !665)
!1379 = !DILocation(line: 565, column: 19, scope: !665)
!1380 = !DILocation(line: 566, column: 2, scope: !665)
!1381 = !DILocation(line: 566, column: 7, scope: !665)
!1382 = !DILocation(line: 566, column: 24, scope: !665)
!1383 = !DILocation(line: 567, column: 6, scope: !1384)
!1384 = distinct !DILexicalBlock(scope: !665, file: !1, line: 567, column: 6)
!1385 = !DILocation(line: 567, column: 11, scope: !1384)
!1386 = !DILocation(line: 567, column: 17, scope: !1384)
!1387 = !DILocation(line: 567, column: 6, scope: !665)
!1388 = !DILocation(line: 568, column: 22, scope: !1389)
!1389 = distinct !DILexicalBlock(scope: !1384, file: !1, line: 567, column: 26)
!1390 = !DILocation(line: 568, column: 27, scope: !1389)
!1391 = !DILocation(line: 568, column: 3, scope: !1389)
!1392 = !DILocation(line: 569, column: 3, scope: !1389)
!1393 = !DILocation(line: 569, column: 8, scope: !1389)
!1394 = !DILocation(line: 569, column: 14, scope: !1389)
!1395 = !DILocation(line: 570, column: 2, scope: !1389)
!1396 = !DILocation(line: 572, column: 6, scope: !1397)
!1397 = distinct !DILexicalBlock(scope: !665, file: !1, line: 572, column: 6)
!1398 = !DILocation(line: 572, column: 11, scope: !1397)
!1399 = !DILocation(line: 572, column: 6, scope: !665)
!1400 = !DILocation(line: 573, column: 3, scope: !1397)
!1401 = !DILocation(line: 574, column: 6, scope: !1402)
!1402 = distinct !DILexicalBlock(scope: !665, file: !1, line: 574, column: 6)
!1403 = !DILocation(line: 574, column: 11, scope: !1402)
!1404 = !DILocation(line: 574, column: 6, scope: !665)
!1405 = !DILocation(line: 575, column: 3, scope: !1402)
!1406 = !DILocation(line: 576, column: 38, scope: !665)
!1407 = !DILocation(line: 576, column: 43, scope: !665)
!1408 = !DILocation(line: 576, column: 54, scope: !665)
!1409 = !DILocation(line: 576, column: 20, scope: !665)
!1410 = !DILocation(line: 576, column: 25, scope: !665)
!1411 = !DILocation(line: 576, column: 36, scope: !665)
!1412 = !DILocation(line: 576, column: 2, scope: !665)
!1413 = !DILocation(line: 576, column: 7, scope: !665)
!1414 = !DILocation(line: 576, column: 18, scope: !665)
!1415 = !DILocation(line: 578, column: 6, scope: !1416)
!1416 = distinct !DILexicalBlock(scope: !665, file: !1, line: 578, column: 6)
!1417 = !DILocation(line: 578, column: 11, scope: !1416)
!1418 = !DILocation(line: 579, column: 7, scope: !1416)
!1419 = !DILocation(line: 579, column: 37, scope: !1420)
!1420 = !DILexicalBlockFile(scope: !1416, file: !1, discriminator: 1)
!1421 = !DILocation(line: 579, column: 11, scope: !1420)
!1422 = !DILocation(line: 580, column: 4, scope: !1416)
!1423 = !DILocation(line: 580, column: 26, scope: !1420)
!1424 = !DILocation(line: 580, column: 7, scope: !1420)
!1425 = !DILocation(line: 580, column: 33, scope: !1420)
!1426 = !DILocation(line: 578, column: 6, scope: !1427)
!1427 = !DILexicalBlockFile(scope: !665, file: !1, discriminator: 1)
!1428 = !DILocation(line: 581, column: 11, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !1416, file: !1, line: 580, column: 39)
!1430 = !DILocation(line: 581, column: 16, scope: !1429)
!1431 = !DILocation(line: 581, column: 3, scope: !1429)
!1432 = !DILocation(line: 585, column: 4, scope: !1433)
!1433 = distinct !DILexicalBlock(scope: !1429, file: !1, line: 581, column: 33)
!1434 = !DILocation(line: 585, column: 9, scope: !1433)
!1435 = !DILocation(line: 585, column: 21, scope: !1433)
!1436 = !DILocation(line: 586, column: 28, scope: !1433)
!1437 = !DILocation(line: 586, column: 33, scope: !1433)
!1438 = !DILocation(line: 586, column: 4, scope: !1433)
!1439 = !DILocation(line: 586, column: 9, scope: !1433)
!1440 = !DILocation(line: 586, column: 26, scope: !1433)
!1441 = !DILocation(line: 587, column: 4, scope: !1433)
!1442 = !DILocation(line: 589, column: 4, scope: !1433)
!1443 = !DILocation(line: 591, column: 2, scope: !1429)
!1444 = !DILocation(line: 601, column: 35, scope: !665)
!1445 = !DILocation(line: 601, column: 15, scope: !665)
!1446 = !DILocation(line: 601, column: 2, scope: !665)
!1447 = !DILocation(line: 601, column: 7, scope: !665)
!1448 = !DILocation(line: 601, column: 13, scope: !665)
!1449 = !DILocation(line: 603, column: 6, scope: !1450)
!1450 = distinct !DILexicalBlock(scope: !665, file: !1, line: 603, column: 6)
!1451 = !DILocation(line: 603, column: 11, scope: !1450)
!1452 = !DILocation(line: 603, column: 17, scope: !1450)
!1453 = !DILocation(line: 603, column: 6, scope: !665)
!1454 = !DILocation(line: 604, column: 22, scope: !1455)
!1455 = distinct !DILexicalBlock(scope: !1450, file: !1, line: 603, column: 26)
!1456 = !DILocation(line: 604, column: 25, scope: !1455)
!1457 = !DILocation(line: 604, column: 3, scope: !1455)
!1458 = !DILocation(line: 606, column: 3, scope: !1455)
!1459 = !DILocation(line: 609, column: 6, scope: !1460)
!1460 = distinct !DILexicalBlock(scope: !665, file: !1, line: 609, column: 6)
!1461 = !DILocation(line: 609, column: 12, scope: !1460)
!1462 = !DILocation(line: 609, column: 6, scope: !665)
!1463 = !DILocalVariable(name: "p", scope: !1464, file: !1, line: 610, type: !429)
!1464 = distinct !DILexicalBlock(scope: !1460, file: !1, line: 609, column: 21)
!1465 = !DILocation(line: 610, column: 15, scope: !1464)
!1466 = !DILocalVariable(name: "len", scope: !1464, file: !1, line: 611, type: !394)
!1467 = !DILocation(line: 611, column: 10, scope: !1464)
!1468 = !DILocation(line: 613, column: 32, scope: !1469)
!1469 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 613, column: 7)
!1470 = !DILocation(line: 613, column: 49, scope: !1469)
!1471 = !DILocation(line: 613, column: 7, scope: !1469)
!1472 = !DILocation(line: 613, column: 56, scope: !1469)
!1473 = !DILocation(line: 613, column: 7, scope: !1464)
!1474 = !DILocation(line: 614, column: 8, scope: !1475)
!1475 = distinct !DILexicalBlock(scope: !1476, file: !1, line: 614, column: 8)
!1476 = distinct !DILexicalBlock(scope: !1469, file: !1, line: 613, column: 62)
!1477 = !DILocation(line: 614, column: 14, scope: !1475)
!1478 = !DILocation(line: 614, column: 8, scope: !1476)
!1479 = !DILocation(line: 615, column: 24, scope: !1480)
!1480 = distinct !DILexicalBlock(scope: !1475, file: !1, line: 614, column: 25)
!1481 = !DILocation(line: 615, column: 27, scope: !1480)
!1482 = !DILocation(line: 615, column: 5, scope: !1480)
!1483 = !DILocation(line: 617, column: 5, scope: !1480)
!1484 = !DILocation(line: 619, column: 23, scope: !1476)
!1485 = !DILocation(line: 619, column: 26, scope: !1476)
!1486 = !DILocation(line: 622, column: 31, scope: !1476)
!1487 = !DILocation(line: 622, column: 8, scope: !1476)
!1488 = !DILocation(line: 623, column: 47, scope: !1476)
!1489 = !DILocation(line: 623, column: 8, scope: !1476)
!1490 = !DILocation(line: 619, column: 4, scope: !1476)
!1491 = !DILocation(line: 624, column: 9, scope: !1476)
!1492 = !DILocation(line: 625, column: 3, scope: !1476)
!1493 = !DILocation(line: 626, column: 7, scope: !1494)
!1494 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 626, column: 7)
!1495 = !DILocation(line: 626, column: 11, scope: !1494)
!1496 = !DILocation(line: 626, column: 7, scope: !1464)
!1497 = !DILocation(line: 627, column: 31, scope: !1494)
!1498 = !DILocation(line: 627, column: 36, scope: !1494)
!1499 = !DILocation(line: 627, column: 43, scope: !1494)
!1500 = !DILocation(line: 627, column: 4, scope: !1494)
!1501 = !DILocation(line: 634, column: 7, scope: !1502)
!1502 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 634, column: 7)
!1503 = !DILocation(line: 634, column: 12, scope: !1502)
!1504 = !DILocation(line: 634, column: 7, scope: !1464)
!1505 = !DILocation(line: 635, column: 32, scope: !1506)
!1506 = distinct !DILexicalBlock(scope: !1507, file: !1, line: 635, column: 8)
!1507 = distinct !DILexicalBlock(scope: !1502, file: !1, line: 634, column: 25)
!1508 = !DILocation(line: 635, column: 49, scope: !1506)
!1509 = !DILocation(line: 635, column: 8, scope: !1506)
!1510 = !DILocation(line: 635, column: 8, scope: !1507)
!1511 = !DILocation(line: 636, column: 9, scope: !1512)
!1512 = distinct !DILexicalBlock(scope: !1513, file: !1, line: 636, column: 9)
!1513 = distinct !DILexicalBlock(scope: !1506, file: !1, line: 635, column: 57)
!1514 = !DILocation(line: 636, column: 15, scope: !1512)
!1515 = !DILocation(line: 636, column: 9, scope: !1513)
!1516 = !DILocation(line: 637, column: 25, scope: !1517)
!1517 = distinct !DILexicalBlock(scope: !1512, file: !1, line: 636, column: 26)
!1518 = !DILocation(line: 637, column: 28, scope: !1517)
!1519 = !DILocation(line: 637, column: 6, scope: !1517)
!1520 = !DILocation(line: 640, column: 6, scope: !1517)
!1521 = !DILocation(line: 643, column: 4, scope: !1513)
!1522 = !DILocation(line: 643, column: 15, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1524, file: !1, discriminator: 1)
!1524 = distinct !DILexicalBlock(scope: !1506, file: !1, line: 643, column: 15)
!1525 = !DILocation(line: 643, column: 19, scope: !1523)
!1526 = !DILocation(line: 644, column: 31, scope: !1524)
!1527 = !DILocation(line: 644, column: 36, scope: !1524)
!1528 = !DILocation(line: 644, column: 43, scope: !1524)
!1529 = !DILocation(line: 644, column: 5, scope: !1524)
!1530 = !DILocation(line: 645, column: 3, scope: !1507)
!1531 = !DILocation(line: 646, column: 2, scope: !1464)
!1532 = !DILocation(line: 649, column: 43, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !665, file: !1, line: 649, column: 6)
!1534 = !DILocation(line: 649, column: 48, scope: !1533)
!1535 = !DILocation(line: 649, column: 20, scope: !1533)
!1536 = !DILocation(line: 649, column: 7, scope: !1537)
!1537 = !DILexicalBlockFile(scope: !1533, file: !1, discriminator: 1)
!1538 = !DILocation(line: 649, column: 7, scope: !1533)
!1539 = !DILocation(line: 649, column: 6, scope: !665)
!1540 = !DILocation(line: 650, column: 7, scope: !1541)
!1541 = distinct !DILexicalBlock(scope: !1542, file: !1, line: 650, column: 7)
!1542 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 649, column: 57)
!1543 = !DILocation(line: 650, column: 12, scope: !1541)
!1544 = !DILocation(line: 650, column: 22, scope: !1541)
!1545 = !DILocation(line: 650, column: 7, scope: !1542)
!1546 = !DILocation(line: 652, column: 6, scope: !1547)
!1547 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 651, column: 8)
!1548 = distinct !DILexicalBlock(scope: !1541, file: !1, line: 650, column: 31)
!1549 = !DILocation(line: 652, column: 11, scope: !1547)
!1550 = !DILocation(line: 651, column: 15, scope: !1547)
!1551 = !DILocation(line: 651, column: 8, scope: !1552)
!1552 = !DILexicalBlockFile(scope: !1547, file: !1, discriminator: 1)
!1553 = !DILocation(line: 652, column: 32, scope: !1547)
!1554 = !DILocation(line: 651, column: 8, scope: !1548)
!1555 = !DILocation(line: 653, column: 5, scope: !1547)
!1556 = !DILocation(line: 653, column: 10, scope: !1547)
!1557 = !DILocation(line: 653, column: 22, scope: !1547)
!1558 = !DILocation(line: 655, column: 3, scope: !1548)
!1559 = !DILocation(line: 655, column: 21, scope: !1560)
!1560 = !DILexicalBlockFile(scope: !1561, file: !1, discriminator: 1)
!1561 = distinct !DILexicalBlock(scope: !1541, file: !1, line: 655, column: 14)
!1562 = !DILocation(line: 655, column: 14, scope: !1563)
!1563 = !DILexicalBlockFile(scope: !1560, file: !1, discriminator: 2)
!1564 = !DILocation(line: 655, column: 52, scope: !1560)
!1565 = !DILocation(line: 655, column: 14, scope: !1560)
!1566 = !DILocation(line: 656, column: 4, scope: !1567)
!1567 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 655, column: 58)
!1568 = !DILocation(line: 656, column: 9, scope: !1567)
!1569 = !DILocation(line: 656, column: 21, scope: !1567)
!1570 = !DILocation(line: 658, column: 3, scope: !1567)
!1571 = !DILocation(line: 659, column: 2, scope: !1542)
!1572 = !DILocation(line: 660, column: 32, scope: !665)
!1573 = !DILocation(line: 660, column: 37, scope: !665)
!1574 = !DILocation(line: 660, column: 20, scope: !665)
!1575 = !DILocation(line: 660, column: 18, scope: !665)
!1576 = !DILocation(line: 663, column: 6, scope: !1577)
!1577 = distinct !DILexicalBlock(scope: !665, file: !1, line: 663, column: 6)
!1578 = !DILocation(line: 663, column: 11, scope: !1577)
!1579 = !DILocation(line: 663, column: 6, scope: !665)
!1580 = !DILocation(line: 664, column: 33, scope: !1581)
!1581 = distinct !DILexicalBlock(scope: !1577, file: !1, line: 663, column: 24)
!1582 = !DILocation(line: 664, column: 38, scope: !1581)
!1583 = !DILocation(line: 664, column: 11, scope: !1581)
!1584 = !DILocation(line: 664, column: 9, scope: !1581)
!1585 = !DILocation(line: 665, column: 7, scope: !1586)
!1586 = distinct !DILexicalBlock(scope: !1581, file: !1, line: 665, column: 7)
!1587 = !DILocation(line: 665, column: 13, scope: !1586)
!1588 = !DILocation(line: 665, column: 7, scope: !1581)
!1589 = !DILocation(line: 666, column: 24, scope: !1586)
!1590 = !DILocation(line: 666, column: 17, scope: !1586)
!1591 = !DILocation(line: 666, column: 15, scope: !1586)
!1592 = !DILocation(line: 666, column: 4, scope: !1586)
!1593 = !DILocation(line: 668, column: 15, scope: !1586)
!1594 = !DILocation(line: 669, column: 35, scope: !1581)
!1595 = !DILocation(line: 669, column: 3, scope: !1581)
!1596 = !DILocation(line: 669, column: 8, scope: !1581)
!1597 = !DILocation(line: 669, column: 33, scope: !1581)
!1598 = !DILocation(line: 670, column: 32, scope: !1581)
!1599 = !DILocation(line: 670, column: 3, scope: !1581)
!1600 = !DILocation(line: 670, column: 8, scope: !1581)
!1601 = !DILocation(line: 670, column: 30, scope: !1581)
!1602 = !DILocation(line: 671, column: 34, scope: !1581)
!1603 = !DILocation(line: 671, column: 3, scope: !1581)
!1604 = !DILocation(line: 671, column: 8, scope: !1581)
!1605 = !DILocation(line: 671, column: 32, scope: !1581)
!1606 = !DILocation(line: 672, column: 22, scope: !1581)
!1607 = !DILocation(line: 672, column: 27, scope: !1581)
!1608 = !DILocation(line: 672, column: 37, scope: !1581)
!1609 = !DILocation(line: 672, column: 42, scope: !1581)
!1610 = !DILocation(line: 673, column: 30, scope: !1581)
!1611 = !DILocation(line: 673, column: 37, scope: !1581)
!1612 = !DILocation(line: 672, column: 3, scope: !1581)
!1613 = !DILocation(line: 672, column: 8, scope: !1581)
!1614 = !DILocation(line: 672, column: 20, scope: !1581)
!1615 = !DILocation(line: 674, column: 3, scope: !1581)
!1616 = !DILocation(line: 674, column: 8, scope: !1581)
!1617 = !DILocation(line: 674, column: 26, scope: !1581)
!1618 = !DILocation(line: 675, column: 18, scope: !1581)
!1619 = !DILocation(line: 676, column: 2, scope: !1581)
!1620 = !DILocation(line: 676, column: 13, scope: !1621)
!1621 = !DILexicalBlockFile(scope: !1622, file: !1, discriminator: 1)
!1622 = distinct !DILexicalBlock(scope: !1577, file: !1, line: 676, column: 13)
!1623 = !DILocation(line: 676, column: 18, scope: !1621)
!1624 = !DILocation(line: 677, column: 3, scope: !1625)
!1625 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 676, column: 31)
!1626 = !DILocation(line: 677, column: 8, scope: !1625)
!1627 = !DILocation(line: 677, column: 26, scope: !1625)
!1628 = !DILocation(line: 678, column: 3, scope: !1625)
!1629 = !DILocation(line: 678, column: 8, scope: !1625)
!1630 = !DILocation(line: 678, column: 33, scope: !1625)
!1631 = !DILocation(line: 679, column: 18, scope: !1625)
!1632 = !DILocation(line: 680, column: 2, scope: !1625)
!1633 = !DILocation(line: 680, column: 39, scope: !1634)
!1634 = !DILexicalBlockFile(scope: !1635, file: !1, discriminator: 1)
!1635 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 680, column: 13)
!1636 = !DILocation(line: 680, column: 44, scope: !1634)
!1637 = !DILocation(line: 680, column: 13, scope: !1634)
!1638 = !DILocalVariable(name: "size", scope: !1639, file: !1, line: 681, type: !401)
!1639 = distinct !DILexicalBlock(scope: !1635, file: !1, line: 680, column: 52)
!1640 = !DILocation(line: 681, column: 11, scope: !1639)
!1641 = !DILocation(line: 681, column: 37, scope: !1639)
!1642 = !DILocation(line: 681, column: 42, scope: !1639)
!1643 = !DILocation(line: 681, column: 18, scope: !1639)
!1644 = !DILocalVariable(name: "additional_size", scope: !1639, file: !1, line: 682, type: !401)
!1645 = !DILocation(line: 682, column: 11, scope: !1639)
!1646 = !DILocation(line: 684, column: 35, scope: !1639)
!1647 = !DILocation(line: 684, column: 3, scope: !1639)
!1648 = !DILocation(line: 684, column: 8, scope: !1639)
!1649 = !DILocation(line: 684, column: 33, scope: !1639)
!1650 = !DILocation(line: 685, column: 28, scope: !1639)
!1651 = !DILocation(line: 685, column: 33, scope: !1639)
!1652 = !DILocation(line: 685, column: 3, scope: !1639)
!1653 = !DILocation(line: 685, column: 8, scope: !1639)
!1654 = !DILocation(line: 685, column: 26, scope: !1639)
!1655 = !DILocation(line: 686, column: 7, scope: !1656)
!1656 = distinct !DILexicalBlock(scope: !1639, file: !1, line: 686, column: 7)
!1657 = !DILocation(line: 686, column: 12, scope: !1656)
!1658 = !DILocation(line: 686, column: 30, scope: !1656)
!1659 = !DILocation(line: 686, column: 7, scope: !1639)
!1660 = !DILocation(line: 687, column: 4, scope: !1661)
!1661 = distinct !DILexicalBlock(scope: !1656, file: !1, line: 686, column: 58)
!1662 = !DILocation(line: 687, column: 9, scope: !1661)
!1663 = !DILocation(line: 687, column: 27, scope: !1661)
!1664 = !DILocation(line: 688, column: 3, scope: !1661)
!1665 = !DILocation(line: 689, column: 7, scope: !1666)
!1666 = distinct !DILexicalBlock(scope: !1639, file: !1, line: 689, column: 7)
!1667 = !DILocation(line: 689, column: 12, scope: !1666)
!1668 = !DILocation(line: 689, column: 30, scope: !1666)
!1669 = !DILocation(line: 689, column: 7, scope: !1639)
!1670 = !DILocation(line: 690, column: 33, scope: !1671)
!1671 = distinct !DILexicalBlock(scope: !1666, file: !1, line: 689, column: 52)
!1672 = !DILocation(line: 690, column: 4, scope: !1671)
!1673 = !DILocation(line: 690, column: 9, scope: !1671)
!1674 = !DILocation(line: 690, column: 31, scope: !1671)
!1675 = !DILocation(line: 691, column: 35, scope: !1671)
!1676 = !DILocation(line: 691, column: 4, scope: !1671)
!1677 = !DILocation(line: 691, column: 9, scope: !1671)
!1678 = !DILocation(line: 691, column: 33, scope: !1671)
!1679 = !DILocation(line: 692, column: 19, scope: !1671)
!1680 = !DILocation(line: 693, column: 3, scope: !1671)
!1681 = !DILocation(line: 694, column: 35, scope: !1682)
!1682 = distinct !DILexicalBlock(scope: !1666, file: !1, line: 693, column: 10)
!1683 = !DILocation(line: 694, column: 4, scope: !1682)
!1684 = !DILocation(line: 694, column: 9, scope: !1682)
!1685 = !DILocation(line: 694, column: 33, scope: !1682)
!1686 = !DILocation(line: 695, column: 19, scope: !1682)
!1687 = !DILocation(line: 698, column: 7, scope: !1688)
!1688 = distinct !DILexicalBlock(scope: !1639, file: !1, line: 698, column: 7)
!1689 = !DILocation(line: 698, column: 12, scope: !1688)
!1690 = !DILocation(line: 698, column: 24, scope: !1688)
!1691 = !DILocation(line: 698, column: 7, scope: !1639)
!1692 = !DILocation(line: 699, column: 12, scope: !1693)
!1693 = distinct !DILexicalBlock(scope: !1688, file: !1, line: 698, column: 52)
!1694 = !DILocation(line: 699, column: 17, scope: !1693)
!1695 = !DILocation(line: 699, column: 4, scope: !1693)
!1696 = !DILocation(line: 701, column: 21, scope: !1697)
!1697 = distinct !DILexicalBlock(scope: !1693, file: !1, line: 699, column: 35)
!1698 = !DILocation(line: 702, column: 20, scope: !1697)
!1699 = !DILocation(line: 703, column: 5, scope: !1697)
!1700 = !DILocation(line: 705, column: 21, scope: !1697)
!1701 = !DILocation(line: 707, column: 20, scope: !1697)
!1702 = !DILocation(line: 708, column: 5, scope: !1697)
!1703 = !DILocation(line: 710, column: 21, scope: !1697)
!1704 = !DILocation(line: 712, column: 20, scope: !1697)
!1705 = !DILocation(line: 713, column: 5, scope: !1697)
!1706 = !DILocation(line: 715, column: 5, scope: !1697)
!1707 = !DILocation(line: 717, column: 8, scope: !1708)
!1708 = distinct !DILexicalBlock(scope: !1693, file: !1, line: 717, column: 8)
!1709 = !DILocation(line: 717, column: 13, scope: !1708)
!1710 = !DILocation(line: 717, column: 31, scope: !1708)
!1711 = !DILocation(line: 717, column: 8, scope: !1693)
!1712 = !DILocation(line: 718, column: 35, scope: !1708)
!1713 = !DILocation(line: 718, column: 5, scope: !1708)
!1714 = !DILocation(line: 718, column: 10, scope: !1708)
!1715 = !DILocation(line: 718, column: 32, scope: !1708)
!1716 = !DILocation(line: 719, column: 3, scope: !1693)
!1717 = !DILocation(line: 731, column: 8, scope: !1718)
!1718 = distinct !DILexicalBlock(scope: !1639, file: !1, line: 731, column: 7)
!1719 = !DILocation(line: 731, column: 13, scope: !1718)
!1720 = !DILocation(line: 731, column: 19, scope: !1718)
!1721 = !DILocation(line: 732, column: 7, scope: !1718)
!1722 = !DILocation(line: 732, column: 11, scope: !1723)
!1723 = !DILexicalBlockFile(scope: !1718, file: !1, discriminator: 1)
!1724 = !DILocation(line: 732, column: 16, scope: !1723)
!1725 = !DILocation(line: 732, column: 42, scope: !1723)
!1726 = !DILocation(line: 732, column: 40, scope: !1723)
!1727 = !DILocation(line: 732, column: 58, scope: !1723)
!1728 = !DILocation(line: 733, column: 7, scope: !1718)
!1729 = !DILocation(line: 733, column: 11, scope: !1723)
!1730 = !DILocation(line: 733, column: 16, scope: !1723)
!1731 = !DILocation(line: 733, column: 40, scope: !1723)
!1732 = !DILocation(line: 734, column: 4, scope: !1718)
!1733 = !DILocation(line: 734, column: 7, scope: !1723)
!1734 = !DILocation(line: 734, column: 12, scope: !1723)
!1735 = !DILocation(line: 734, column: 30, scope: !1723)
!1736 = !DILocation(line: 731, column: 7, scope: !1737)
!1737 = !DILexicalBlockFile(scope: !1639, file: !1, discriminator: 1)
!1738 = !DILocation(line: 735, column: 4, scope: !1739)
!1739 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 734, column: 53)
!1740 = !DILocation(line: 735, column: 9, scope: !1739)
!1741 = !DILocation(line: 735, column: 26, scope: !1739)
!1742 = !DILocation(line: 736, column: 19, scope: !1739)
!1743 = !DILocation(line: 737, column: 3, scope: !1739)
!1744 = !DILocation(line: 740, column: 3, scope: !1639)
!1745 = !DILocation(line: 740, column: 8, scope: !1639)
!1746 = !DILocation(line: 740, column: 20, scope: !1639)
!1747 = !DILocation(line: 741, column: 2, scope: !1639)
!1748 = !DILocation(line: 747, column: 3, scope: !1749)
!1749 = distinct !DILexicalBlock(scope: !1635, file: !1, line: 741, column: 9)
!1750 = !DILocation(line: 747, column: 8, scope: !1749)
!1751 = !DILocation(line: 747, column: 26, scope: !1749)
!1752 = !DILocation(line: 748, column: 3, scope: !1749)
!1753 = !DILocation(line: 748, column: 8, scope: !1749)
!1754 = !DILocation(line: 748, column: 20, scope: !1749)
!1755 = !DILocation(line: 749, column: 8, scope: !1756)
!1756 = distinct !DILexicalBlock(scope: !1749, file: !1, line: 749, column: 7)
!1757 = !DILocation(line: 749, column: 13, scope: !1756)
!1758 = !DILocation(line: 749, column: 19, scope: !1756)
!1759 = !DILocation(line: 749, column: 43, scope: !1756)
!1760 = !DILocation(line: 749, column: 7, scope: !1749)
!1761 = !DILocation(line: 750, column: 4, scope: !1762)
!1762 = distinct !DILexicalBlock(scope: !1756, file: !1, line: 749, column: 49)
!1763 = !DILocation(line: 750, column: 9, scope: !1762)
!1764 = !DILocation(line: 750, column: 26, scope: !1762)
!1765 = !DILocation(line: 751, column: 19, scope: !1762)
!1766 = !DILocation(line: 752, column: 3, scope: !1762)
!1767 = !DILocation(line: 752, column: 14, scope: !1768)
!1768 = !DILexicalBlockFile(scope: !1769, file: !1, discriminator: 1)
!1769 = distinct !DILexicalBlock(scope: !1756, file: !1, line: 752, column: 14)
!1770 = !DILocation(line: 752, column: 19, scope: !1768)
!1771 = !DILocation(line: 752, column: 37, scope: !1768)
!1772 = !DILocation(line: 753, column: 19, scope: !1773)
!1773 = distinct !DILexicalBlock(scope: !1769, file: !1, line: 752, column: 59)
!1774 = !DILocation(line: 754, column: 3, scope: !1773)
!1775 = !DILocation(line: 755, column: 19, scope: !1776)
!1776 = distinct !DILexicalBlock(scope: !1769, file: !1, line: 754, column: 10)
!1777 = !DILocation(line: 758, column: 7, scope: !1778)
!1778 = distinct !DILexicalBlock(scope: !1749, file: !1, line: 758, column: 7)
!1779 = !DILocation(line: 758, column: 12, scope: !1778)
!1780 = !DILocation(line: 758, column: 24, scope: !1778)
!1781 = !DILocation(line: 758, column: 7, scope: !1749)
!1782 = !DILocation(line: 759, column: 12, scope: !1783)
!1783 = distinct !DILexicalBlock(scope: !1778, file: !1, line: 758, column: 52)
!1784 = !DILocation(line: 759, column: 17, scope: !1783)
!1785 = !DILocation(line: 759, column: 4, scope: !1783)
!1786 = !DILocation(line: 763, column: 9, scope: !1787)
!1787 = distinct !DILexicalBlock(scope: !1788, file: !1, line: 763, column: 9)
!1788 = distinct !DILexicalBlock(scope: !1783, file: !1, line: 759, column: 35)
!1789 = !DILocation(line: 763, column: 24, scope: !1787)
!1790 = !DILocation(line: 763, column: 9, scope: !1788)
!1791 = !DILocation(line: 764, column: 21, scope: !1787)
!1792 = !DILocation(line: 764, column: 6, scope: !1787)
!1793 = !DILocation(line: 765, column: 5, scope: !1788)
!1794 = !DILocation(line: 767, column: 5, scope: !1788)
!1795 = !DILocation(line: 769, column: 3, scope: !1783)
!1796 = !DILocation(line: 773, column: 2, scope: !665)
!1797 = !DILocation(line: 774, column: 2, scope: !665)
!1798 = !DILocation(line: 775, column: 18, scope: !665)
!1799 = !DILocation(line: 775, column: 31, scope: !665)
!1800 = !DILocation(line: 775, column: 36, scope: !665)
!1801 = !DILocation(line: 775, column: 2, scope: !665)
!1802 = !DILocation(line: 776, column: 18, scope: !665)
!1803 = !DILocation(line: 776, column: 31, scope: !665)
!1804 = !DILocation(line: 776, column: 36, scope: !665)
!1805 = !DILocation(line: 776, column: 41, scope: !665)
!1806 = !DILocation(line: 776, column: 2, scope: !665)
!1807 = !DILocation(line: 777, column: 6, scope: !1808)
!1808 = distinct !DILexicalBlock(scope: !665, file: !1, line: 777, column: 6)
!1809 = !DILocation(line: 777, column: 11, scope: !1808)
!1810 = !DILocation(line: 777, column: 28, scope: !1808)
!1811 = !DILocation(line: 778, column: 6, scope: !1808)
!1812 = !DILocation(line: 778, column: 9, scope: !1813)
!1813 = !DILexicalBlockFile(scope: !1808, file: !1, discriminator: 1)
!1814 = !DILocation(line: 778, column: 14, scope: !1813)
!1815 = !DILocation(line: 778, column: 31, scope: !1813)
!1816 = !DILocation(line: 777, column: 6, scope: !1427)
!1817 = !DILocation(line: 779, column: 19, scope: !1808)
!1818 = !DILocation(line: 779, column: 32, scope: !1808)
!1819 = !DILocation(line: 779, column: 3, scope: !1808)
!1820 = !DILocation(line: 781, column: 19, scope: !1808)
!1821 = !DILocation(line: 781, column: 32, scope: !1808)
!1822 = !DILocation(line: 781, column: 37, scope: !1808)
!1823 = !DILocation(line: 781, column: 42, scope: !1808)
!1824 = !DILocation(line: 781, column: 3, scope: !1808)
!1825 = !DILocation(line: 782, column: 18, scope: !665)
!1826 = !DILocation(line: 782, column: 31, scope: !665)
!1827 = !DILocation(line: 783, column: 32, scope: !665)
!1828 = !DILocation(line: 783, column: 37, scope: !665)
!1829 = !DILocation(line: 783, column: 12, scope: !665)
!1830 = !DILocation(line: 783, column: 3, scope: !1427)
!1831 = !DILocation(line: 782, column: 2, scope: !665)
!1832 = !DILocation(line: 784, column: 18, scope: !665)
!1833 = !DILocation(line: 784, column: 31, scope: !665)
!1834 = !DILocation(line: 784, column: 37, scope: !665)
!1835 = !DILocation(line: 784, column: 42, scope: !665)
!1836 = !DILocation(line: 784, column: 2, scope: !665)
!1837 = !DILocation(line: 785, column: 6, scope: !1838)
!1838 = distinct !DILexicalBlock(scope: !665, file: !1, line: 785, column: 6)
!1839 = !DILocation(line: 785, column: 11, scope: !1838)
!1840 = !DILocation(line: 785, column: 6, scope: !665)
!1841 = !DILocation(line: 791, column: 19, scope: !1842)
!1842 = distinct !DILexicalBlock(scope: !1838, file: !1, line: 785, column: 29)
!1843 = !DILocation(line: 791, column: 32, scope: !1842)
!1844 = !DILocation(line: 791, column: 3, scope: !1842)
!1845 = !DILocation(line: 792, column: 19, scope: !1842)
!1846 = !DILocation(line: 792, column: 32, scope: !1842)
!1847 = !DILocation(line: 792, column: 3, scope: !1842)
!1848 = !DILocation(line: 793, column: 2, scope: !1842)
!1849 = !DILocation(line: 794, column: 19, scope: !1850)
!1850 = distinct !DILexicalBlock(scope: !1838, file: !1, line: 793, column: 9)
!1851 = !DILocation(line: 794, column: 32, scope: !1850)
!1852 = !DILocation(line: 794, column: 48, scope: !1850)
!1853 = !DILocation(line: 794, column: 53, scope: !1850)
!1854 = !DILocation(line: 794, column: 38, scope: !1850)
!1855 = !DILocation(line: 794, column: 3, scope: !1850)
!1856 = !DILocation(line: 795, column: 19, scope: !1850)
!1857 = !DILocation(line: 795, column: 32, scope: !1850)
!1858 = !DILocation(line: 795, column: 48, scope: !1850)
!1859 = !DILocation(line: 795, column: 53, scope: !1850)
!1860 = !DILocation(line: 795, column: 38, scope: !1850)
!1861 = !DILocation(line: 795, column: 3, scope: !1850)
!1862 = !DILocation(line: 797, column: 18, scope: !665)
!1863 = !DILocation(line: 797, column: 31, scope: !665)
!1864 = !DILocation(line: 797, column: 47, scope: !665)
!1865 = !DILocation(line: 797, column: 37, scope: !665)
!1866 = !DILocation(line: 797, column: 2, scope: !665)
!1867 = !DILocation(line: 799, column: 6, scope: !1868)
!1868 = distinct !DILexicalBlock(scope: !665, file: !1, line: 799, column: 6)
!1869 = !DILocation(line: 799, column: 11, scope: !1868)
!1870 = !DILocation(line: 799, column: 28, scope: !1868)
!1871 = !DILocation(line: 799, column: 6, scope: !665)
!1872 = !DILocation(line: 800, column: 7, scope: !1873)
!1873 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 800, column: 7)
!1874 = distinct !DILexicalBlock(scope: !1868, file: !1, line: 799, column: 55)
!1875 = !DILocation(line: 800, column: 12, scope: !1873)
!1876 = !DILocation(line: 800, column: 24, scope: !1873)
!1877 = !DILocation(line: 800, column: 7, scope: !1874)
!1878 = !DILocation(line: 801, column: 23, scope: !1873)
!1879 = !DILocation(line: 801, column: 4, scope: !1873)
!1880 = !DILocation(line: 801, column: 9, scope: !1873)
!1881 = !DILocation(line: 801, column: 21, scope: !1873)
!1882 = !DILocation(line: 803, column: 23, scope: !1873)
!1883 = !DILocation(line: 803, column: 4, scope: !1873)
!1884 = !DILocation(line: 803, column: 9, scope: !1873)
!1885 = !DILocation(line: 803, column: 21, scope: !1873)
!1886 = !DILocation(line: 804, column: 2, scope: !1874)
!1887 = !DILocation(line: 807, column: 30, scope: !665)
!1888 = !DILocation(line: 807, column: 21, scope: !665)
!1889 = !DILocation(line: 807, column: 2, scope: !665)
!1890 = !DILocation(line: 807, column: 7, scope: !665)
!1891 = !DILocation(line: 807, column: 19, scope: !665)
!1892 = !DILocation(line: 809, column: 4, scope: !665)
!1893 = !DILocation(line: 809, column: 9, scope: !665)
!1894 = !DILocation(line: 809, column: 2, scope: !665)
!1895 = !DILocation(line: 810, column: 9, scope: !665)
!1896 = !DILocation(line: 810, column: 14, scope: !665)
!1897 = !DILocation(line: 810, column: 2, scope: !665)
!1898 = !DILocation(line: 811, column: 9, scope: !665)
!1899 = !DILocation(line: 811, column: 14, scope: !665)
!1900 = !DILocation(line: 811, column: 2, scope: !665)
!1901 = !DILocation(line: 813, column: 18, scope: !665)
!1902 = !DILocation(line: 813, column: 23, scope: !665)
!1903 = !DILocation(line: 813, column: 35, scope: !665)
!1904 = !DILocation(line: 813, column: 50, scope: !665)
!1905 = !DILocation(line: 813, column: 48, scope: !665)
!1906 = !DILocation(line: 813, column: 40, scope: !665)
!1907 = !DILocation(line: 813, column: 2, scope: !665)
!1908 = !DILocation(line: 814, column: 18, scope: !665)
!1909 = !DILocation(line: 814, column: 23, scope: !665)
!1910 = !DILocation(line: 814, column: 35, scope: !665)
!1911 = !DILocation(line: 814, column: 40, scope: !665)
!1912 = !DILocation(line: 814, column: 2, scope: !665)
!1913 = !DILocation(line: 815, column: 18, scope: !665)
!1914 = !DILocation(line: 815, column: 23, scope: !665)
!1915 = !DILocation(line: 815, column: 35, scope: !665)
!1916 = !DILocation(line: 815, column: 40, scope: !665)
!1917 = !DILocation(line: 815, column: 45, scope: !665)
!1918 = !DILocation(line: 815, column: 2, scope: !665)
!1919 = !DILocation(line: 816, column: 6, scope: !1920)
!1920 = distinct !DILexicalBlock(scope: !665, file: !1, line: 816, column: 6)
!1921 = !DILocation(line: 816, column: 11, scope: !1920)
!1922 = !DILocation(line: 816, column: 28, scope: !1920)
!1923 = !DILocation(line: 817, column: 6, scope: !1920)
!1924 = !DILocation(line: 817, column: 9, scope: !1925)
!1925 = !DILexicalBlockFile(scope: !1920, file: !1, discriminator: 1)
!1926 = !DILocation(line: 817, column: 14, scope: !1925)
!1927 = !DILocation(line: 817, column: 31, scope: !1925)
!1928 = !DILocation(line: 816, column: 6, scope: !1427)
!1929 = !DILocation(line: 818, column: 19, scope: !1920)
!1930 = !DILocation(line: 818, column: 24, scope: !1920)
!1931 = !DILocation(line: 818, column: 36, scope: !1920)
!1932 = !DILocation(line: 818, column: 3, scope: !1920)
!1933 = !DILocation(line: 820, column: 19, scope: !1920)
!1934 = !DILocation(line: 820, column: 24, scope: !1920)
!1935 = !DILocation(line: 820, column: 36, scope: !1920)
!1936 = !DILocation(line: 820, column: 42, scope: !1920)
!1937 = !DILocation(line: 820, column: 47, scope: !1920)
!1938 = !DILocation(line: 820, column: 3, scope: !1920)
!1939 = !DILocation(line: 821, column: 18, scope: !665)
!1940 = !DILocation(line: 821, column: 23, scope: !665)
!1941 = !DILocation(line: 821, column: 35, scope: !665)
!1942 = !DILocation(line: 822, column: 32, scope: !665)
!1943 = !DILocation(line: 822, column: 37, scope: !665)
!1944 = !DILocation(line: 822, column: 12, scope: !665)
!1945 = !DILocation(line: 822, column: 3, scope: !1427)
!1946 = !DILocation(line: 821, column: 2, scope: !665)
!1947 = !DILocation(line: 823, column: 18, scope: !665)
!1948 = !DILocation(line: 823, column: 23, scope: !665)
!1949 = !DILocation(line: 823, column: 35, scope: !665)
!1950 = !DILocation(line: 823, column: 51, scope: !665)
!1951 = !DILocation(line: 823, column: 41, scope: !665)
!1952 = !DILocation(line: 823, column: 2, scope: !665)
!1953 = !DILocation(line: 825, column: 18, scope: !665)
!1954 = !DILocation(line: 825, column: 23, scope: !665)
!1955 = !DILocation(line: 825, column: 35, scope: !665)
!1956 = !DILocation(line: 826, column: 36, scope: !665)
!1957 = !DILocation(line: 826, column: 41, scope: !665)
!1958 = !DILocation(line: 826, column: 17, scope: !665)
!1959 = !DILocation(line: 826, column: 49, scope: !665)
!1960 = !DILocation(line: 825, column: 2, scope: !665)
!1961 = !DILocation(line: 827, column: 15, scope: !665)
!1962 = !DILocation(line: 827, column: 20, scope: !665)
!1963 = !DILocation(line: 827, column: 6, scope: !665)
!1964 = !DILocation(line: 827, column: 4, scope: !665)
!1965 = !DILocation(line: 829, column: 12, scope: !665)
!1966 = !DILocation(line: 829, column: 17, scope: !665)
!1967 = !DILocation(line: 829, column: 24, scope: !665)
!1968 = !DILocation(line: 829, column: 2, scope: !665)
!1969 = !DILocation(line: 832, column: 2, scope: !665)
!1970 = !DILocation(line: 833, column: 6, scope: !665)
!1971 = !DILocation(line: 833, column: 4, scope: !665)
!1972 = !DILocation(line: 840, column: 9, scope: !665)
!1973 = !DILocation(line: 840, column: 2, scope: !665)
!1974 = !DILocation(line: 841, column: 18, scope: !665)
!1975 = !DILocation(line: 841, column: 20, scope: !665)
!1976 = !DILocation(line: 843, column: 36, scope: !665)
!1977 = !DILocation(line: 843, column: 9, scope: !665)
!1978 = !DILocation(line: 843, column: 6, scope: !665)
!1979 = !DILocation(line: 844, column: 36, scope: !665)
!1980 = !DILocation(line: 844, column: 9, scope: !665)
!1981 = !DILocation(line: 844, column: 6, scope: !665)
!1982 = !DILocation(line: 845, column: 36, scope: !665)
!1983 = !DILocation(line: 845, column: 9, scope: !665)
!1984 = !DILocation(line: 845, column: 6, scope: !665)
!1985 = !DILocation(line: 842, column: 6, scope: !665)
!1986 = !DILocation(line: 841, column: 2, scope: !665)
!1987 = !DILocation(line: 846, column: 4, scope: !665)
!1988 = !DILocation(line: 848, column: 34, scope: !665)
!1989 = !DILocation(line: 848, column: 7, scope: !665)
!1990 = !DILocation(line: 849, column: 36, scope: !665)
!1991 = !DILocation(line: 849, column: 9, scope: !665)
!1992 = !DILocation(line: 849, column: 6, scope: !665)
!1993 = !DILocation(line: 850, column: 36, scope: !665)
!1994 = !DILocation(line: 850, column: 9, scope: !665)
!1995 = !DILocation(line: 850, column: 6, scope: !665)
!1996 = !DILocation(line: 848, column: 6, scope: !665)
!1997 = !DILocation(line: 847, column: 4, scope: !665)
!1998 = !DILocation(line: 847, column: 7, scope: !665)
!1999 = !DILocation(line: 851, column: 33, scope: !2000)
!2000 = distinct !DILexicalBlock(scope: !665, file: !1, line: 851, column: 6)
!2001 = !DILocation(line: 851, column: 6, scope: !2000)
!2002 = !DILocation(line: 851, column: 6, scope: !665)
!2003 = !DILocation(line: 852, column: 19, scope: !2004)
!2004 = distinct !DILexicalBlock(scope: !2000, file: !1, line: 851, column: 41)
!2005 = !DILocation(line: 852, column: 52, scope: !2004)
!2006 = !DILocation(line: 852, column: 32, scope: !2004)
!2007 = !DILocation(line: 852, column: 22, scope: !2004)
!2008 = !DILocation(line: 852, column: 3, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !2004, file: !1, discriminator: 1)
!2010 = !DILocation(line: 853, column: 5, scope: !2004)
!2011 = !DILocation(line: 854, column: 2, scope: !2004)
!2012 = !DILocation(line: 855, column: 33, scope: !2013)
!2013 = distinct !DILexicalBlock(scope: !665, file: !1, line: 855, column: 6)
!2014 = !DILocation(line: 855, column: 6, scope: !2013)
!2015 = !DILocation(line: 855, column: 6, scope: !665)
!2016 = !DILocation(line: 856, column: 19, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !2013, file: !1, line: 855, column: 41)
!2018 = !DILocation(line: 856, column: 52, scope: !2017)
!2019 = !DILocation(line: 856, column: 32, scope: !2017)
!2020 = !DILocation(line: 856, column: 22, scope: !2017)
!2021 = !DILocation(line: 856, column: 3, scope: !2022)
!2022 = !DILexicalBlockFile(scope: !2017, file: !1, discriminator: 1)
!2023 = !DILocation(line: 857, column: 5, scope: !2017)
!2024 = !DILocation(line: 858, column: 2, scope: !2017)
!2025 = !DILocation(line: 859, column: 33, scope: !2026)
!2026 = distinct !DILexicalBlock(scope: !665, file: !1, line: 859, column: 6)
!2027 = !DILocation(line: 859, column: 6, scope: !2026)
!2028 = !DILocation(line: 859, column: 6, scope: !665)
!2029 = !DILocation(line: 860, column: 19, scope: !2030)
!2030 = distinct !DILexicalBlock(scope: !2026, file: !1, line: 859, column: 41)
!2031 = !DILocation(line: 860, column: 52, scope: !2030)
!2032 = !DILocation(line: 860, column: 32, scope: !2030)
!2033 = !DILocation(line: 860, column: 22, scope: !2030)
!2034 = !DILocation(line: 860, column: 3, scope: !2035)
!2035 = !DILexicalBlockFile(scope: !2030, file: !1, discriminator: 1)
!2036 = !DILocation(line: 861, column: 5, scope: !2030)
!2037 = !DILocation(line: 862, column: 2, scope: !2030)
!2038 = !DILocation(line: 866, column: 9, scope: !665)
!2039 = !DILocation(line: 866, column: 2, scope: !665)
!2040 = !DILocation(line: 867, column: 4, scope: !665)
!2041 = !DILocation(line: 868, column: 4, scope: !665)
!2042 = !DILocation(line: 868, column: 7, scope: !665)
!2043 = !DILocation(line: 869, column: 18, scope: !665)
!2044 = !DILocation(line: 869, column: 49, scope: !665)
!2045 = !DILocation(line: 869, column: 31, scope: !665)
!2046 = !DILocation(line: 869, column: 21, scope: !665)
!2047 = !DILocation(line: 869, column: 2, scope: !1427)
!2048 = !DILocation(line: 870, column: 4, scope: !665)
!2049 = !DILocation(line: 871, column: 4, scope: !665)
!2050 = !DILocation(line: 871, column: 7, scope: !665)
!2051 = !DILocation(line: 872, column: 18, scope: !665)
!2052 = !DILocation(line: 872, column: 49, scope: !665)
!2053 = !DILocation(line: 872, column: 31, scope: !665)
!2054 = !DILocation(line: 872, column: 21, scope: !665)
!2055 = !DILocation(line: 872, column: 2, scope: !1427)
!2056 = !DILocation(line: 873, column: 4, scope: !665)
!2057 = !DILocation(line: 876, column: 7, scope: !2058)
!2058 = distinct !DILexicalBlock(scope: !665, file: !1, line: 876, column: 6)
!2059 = !DILocation(line: 876, column: 12, scope: !2058)
!2060 = !DILocation(line: 876, column: 24, scope: !2058)
!2061 = !DILocation(line: 877, column: 6, scope: !2058)
!2062 = !DILocation(line: 877, column: 10, scope: !2063)
!2063 = !DILexicalBlockFile(scope: !2058, file: !1, discriminator: 1)
!2064 = !DILocation(line: 877, column: 15, scope: !2063)
!2065 = !DILocation(line: 877, column: 32, scope: !2063)
!2066 = !DILocation(line: 878, column: 10, scope: !2058)
!2067 = !DILocation(line: 878, column: 13, scope: !2063)
!2068 = !DILocation(line: 878, column: 18, scope: !2063)
!2069 = !DILocation(line: 878, column: 35, scope: !2063)
!2070 = !DILocation(line: 876, column: 6, scope: !1427)
!2071 = !DILocation(line: 880, column: 10, scope: !2072)
!2072 = distinct !DILexicalBlock(scope: !2058, file: !1, line: 878, column: 65)
!2073 = !DILocation(line: 880, column: 3, scope: !2072)
!2074 = !DILocation(line: 887, column: 33, scope: !2075)
!2075 = distinct !DILexicalBlock(scope: !2072, file: !1, line: 887, column: 7)
!2076 = !DILocation(line: 887, column: 38, scope: !2075)
!2077 = !DILocation(line: 887, column: 7, scope: !2075)
!2078 = !DILocation(line: 888, column: 7, scope: !2075)
!2079 = !DILocation(line: 888, column: 29, scope: !2080)
!2080 = !DILexicalBlockFile(scope: !2075, file: !1, discriminator: 1)
!2081 = !DILocation(line: 888, column: 34, scope: !2080)
!2082 = !DILocation(line: 888, column: 10, scope: !2080)
!2083 = !DILocation(line: 888, column: 41, scope: !2080)
!2084 = !DILocation(line: 887, column: 7, scope: !2085)
!2085 = !DILexicalBlockFile(scope: !2072, file: !1, discriminator: 1)
!2086 = !DILocation(line: 889, column: 20, scope: !2087)
!2087 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 888, column: 47)
!2088 = !DILocation(line: 889, column: 21, scope: !2087)
!2089 = !DILocation(line: 889, column: 4, scope: !2087)
!2090 = !DILocation(line: 890, column: 4, scope: !2087)
!2091 = !DILocation(line: 890, column: 9, scope: !2087)
!2092 = !DILocation(line: 890, column: 20, scope: !2087)
!2093 = !DILocation(line: 891, column: 3, scope: !2087)
!2094 = !DILocation(line: 892, column: 4, scope: !2075)
!2095 = !DILocation(line: 892, column: 9, scope: !2075)
!2096 = !DILocation(line: 892, column: 20, scope: !2075)
!2097 = !DILocation(line: 893, column: 5, scope: !2072)
!2098 = !DILocation(line: 895, column: 11, scope: !2072)
!2099 = !DILocation(line: 895, column: 16, scope: !2072)
!2100 = !DILocation(line: 895, column: 33, scope: !2072)
!2101 = !DILocation(line: 895, column: 10, scope: !2072)
!2102 = !DILocation(line: 895, column: 5, scope: !2072)
!2103 = !DILocation(line: 895, column: 8, scope: !2072)
!2104 = !DILocation(line: 897, column: 19, scope: !2072)
!2105 = !DILocation(line: 897, column: 22, scope: !2072)
!2106 = !DILocation(line: 897, column: 27, scope: !2072)
!2107 = !DILocation(line: 897, column: 3, scope: !2072)
!2108 = !DILocation(line: 898, column: 5, scope: !2072)
!2109 = !DILocation(line: 899, column: 2, scope: !2072)
!2110 = !DILocation(line: 902, column: 34, scope: !665)
!2111 = !DILocation(line: 902, column: 39, scope: !665)
!2112 = !DILocation(line: 902, column: 2, scope: !665)
!2113 = !DILocation(line: 902, column: 7, scope: !665)
!2114 = !DILocation(line: 902, column: 32, scope: !665)
!2115 = !DILocation(line: 903, column: 22, scope: !665)
!2116 = !DILocation(line: 903, column: 27, scope: !665)
!2117 = !DILocation(line: 903, column: 31, scope: !665)
!2118 = !DILocation(line: 903, column: 29, scope: !665)
!2119 = !DILocation(line: 903, column: 13, scope: !665)
!2120 = !DILocation(line: 903, column: 11, scope: !665)
!2121 = !DILocation(line: 904, column: 9, scope: !665)
!2122 = !DILocation(line: 904, column: 2, scope: !665)
!2123 = !DILocation(line: 904, column: 32, scope: !665)
!2124 = !DILocation(line: 904, column: 36, scope: !665)
!2125 = !DILocation(line: 904, column: 34, scope: !665)
!2126 = !DILocation(line: 915, column: 6, scope: !2127)
!2127 = distinct !DILexicalBlock(scope: !665, file: !1, line: 915, column: 6)
!2128 = !DILocation(line: 915, column: 11, scope: !2127)
!2129 = !DILocation(line: 915, column: 6, scope: !665)
!2130 = !DILocalVariable(name: "zip64_start", scope: !2131, file: !1, line: 916, type: !577)
!2131 = distinct !DILexicalBlock(scope: !2127, file: !1, line: 915, column: 29)
!2132 = !DILocation(line: 916, column: 18, scope: !2131)
!2133 = !DILocation(line: 916, column: 32, scope: !2131)
!2134 = !DILocation(line: 917, column: 10, scope: !2131)
!2135 = !DILocation(line: 917, column: 3, scope: !2131)
!2136 = !DILocation(line: 918, column: 5, scope: !2131)
!2137 = !DILocation(line: 919, column: 19, scope: !2131)
!2138 = !DILocation(line: 919, column: 22, scope: !2131)
!2139 = !DILocation(line: 919, column: 27, scope: !2131)
!2140 = !DILocation(line: 919, column: 3, scope: !2131)
!2141 = !DILocation(line: 920, column: 5, scope: !2131)
!2142 = !DILocation(line: 921, column: 19, scope: !2131)
!2143 = !DILocation(line: 921, column: 22, scope: !2131)
!2144 = !DILocation(line: 921, column: 27, scope: !2131)
!2145 = !DILocation(line: 921, column: 3, scope: !2131)
!2146 = !DILocation(line: 922, column: 5, scope: !2131)
!2147 = !DILocation(line: 923, column: 19, scope: !2131)
!2148 = !DILocation(line: 923, column: 31, scope: !2131)
!2149 = !DILocation(line: 923, column: 47, scope: !2131)
!2150 = !DILocation(line: 923, column: 52, scope: !2131)
!2151 = !DILocation(line: 923, column: 64, scope: !2131)
!2152 = !DILocation(line: 923, column: 49, scope: !2131)
!2153 = !DILocation(line: 923, column: 36, scope: !2131)
!2154 = !DILocation(line: 923, column: 3, scope: !2131)
!2155 = !DILocation(line: 924, column: 2, scope: !2131)
!2156 = !DILocation(line: 926, column: 6, scope: !2157)
!2157 = distinct !DILexicalBlock(scope: !665, file: !1, line: 926, column: 6)
!2158 = !DILocation(line: 926, column: 11, scope: !2157)
!2159 = !DILocation(line: 926, column: 17, scope: !2157)
!2160 = !DILocation(line: 926, column: 6, scope: !665)
!2161 = !DILocalVariable(name: "external_info", scope: !2162, file: !1, line: 928, type: !577)
!2162 = distinct !DILexicalBlock(scope: !2157, file: !1, line: 926, column: 43)
!2163 = !DILocation(line: 928, column: 18, scope: !2162)
!2164 = !DILocation(line: 928, column: 34, scope: !2162)
!2165 = !DILocalVariable(name: "included", scope: !2162, file: !1, line: 929, type: !372)
!2166 = !DILocation(line: 929, column: 7, scope: !2162)
!2167 = !DILocation(line: 930, column: 10, scope: !2162)
!2168 = !DILocation(line: 930, column: 3, scope: !2162)
!2169 = !DILocation(line: 931, column: 5, scope: !2162)
!2170 = !DILocation(line: 932, column: 10, scope: !2162)
!2171 = !DILocation(line: 932, column: 3, scope: !2162)
!2172 = !DILocation(line: 932, column: 8, scope: !2162)
!2173 = !DILocation(line: 933, column: 5, scope: !2162)
!2174 = !DILocation(line: 934, column: 7, scope: !2175)
!2175 = distinct !DILexicalBlock(scope: !2162, file: !1, line: 934, column: 7)
!2176 = !DILocation(line: 934, column: 16, scope: !2175)
!2177 = !DILocation(line: 934, column: 7, scope: !2162)
!2178 = !DILocation(line: 935, column: 20, scope: !2179)
!2179 = distinct !DILexicalBlock(scope: !2175, file: !1, line: 934, column: 21)
!2180 = !DILocation(line: 936, column: 18, scope: !2179)
!2181 = !DILocation(line: 936, column: 16, scope: !2179)
!2182 = !DILocation(line: 936, column: 8, scope: !2179)
!2183 = !DILocation(line: 935, column: 4, scope: !2179)
!2184 = !DILocation(line: 937, column: 6, scope: !2179)
!2185 = !DILocation(line: 938, column: 3, scope: !2179)
!2186 = !DILocation(line: 939, column: 7, scope: !2187)
!2187 = distinct !DILexicalBlock(scope: !2162, file: !1, line: 939, column: 7)
!2188 = !DILocation(line: 939, column: 16, scope: !2187)
!2189 = !DILocation(line: 939, column: 7, scope: !2162)
!2190 = !DILocation(line: 940, column: 20, scope: !2191)
!2191 = distinct !DILexicalBlock(scope: !2187, file: !1, line: 939, column: 21)
!2192 = !DILocation(line: 940, column: 4, scope: !2191)
!2193 = !DILocation(line: 941, column: 6, scope: !2191)
!2194 = !DILocation(line: 942, column: 3, scope: !2191)
!2195 = !DILocation(line: 943, column: 7, scope: !2196)
!2196 = distinct !DILexicalBlock(scope: !2162, file: !1, line: 943, column: 7)
!2197 = !DILocation(line: 943, column: 16, scope: !2196)
!2198 = !DILocation(line: 943, column: 7, scope: !2162)
!2199 = !DILocation(line: 944, column: 20, scope: !2200)
!2200 = distinct !DILexicalBlock(scope: !2196, file: !1, line: 943, column: 21)
!2201 = !DILocation(line: 945, column: 38, scope: !2200)
!2202 = !DILocation(line: 945, column: 43, scope: !2200)
!2203 = !DILocation(line: 945, column: 19, scope: !2200)
!2204 = !DILocation(line: 945, column: 51, scope: !2200)
!2205 = !DILocation(line: 944, column: 4, scope: !2200)
!2206 = !DILocation(line: 946, column: 6, scope: !2200)
!2207 = !DILocation(line: 947, column: 3, scope: !2200)
!2208 = !DILocation(line: 948, column: 7, scope: !2209)
!2209 = distinct !DILexicalBlock(scope: !2162, file: !1, line: 948, column: 7)
!2210 = !DILocation(line: 948, column: 16, scope: !2209)
!2211 = !DILocation(line: 948, column: 7, scope: !2162)
!2212 = !DILocation(line: 950, column: 3, scope: !2213)
!2213 = distinct !DILexicalBlock(scope: !2209, file: !1, line: 948, column: 21)
!2214 = !DILocation(line: 951, column: 19, scope: !2162)
!2215 = !DILocation(line: 951, column: 33, scope: !2162)
!2216 = !DILocation(line: 951, column: 49, scope: !2162)
!2217 = !DILocation(line: 951, column: 54, scope: !2162)
!2218 = !DILocation(line: 951, column: 68, scope: !2162)
!2219 = !DILocation(line: 951, column: 51, scope: !2162)
!2220 = !DILocation(line: 951, column: 38, scope: !2162)
!2221 = !DILocation(line: 951, column: 3, scope: !2162)
!2222 = !DILocation(line: 952, column: 2, scope: !2162)
!2223 = !DILocation(line: 955, column: 18, scope: !665)
!2224 = !DILocation(line: 955, column: 31, scope: !665)
!2225 = !DILocation(line: 955, column: 48, scope: !665)
!2226 = !DILocation(line: 955, column: 52, scope: !665)
!2227 = !DILocation(line: 955, column: 50, scope: !665)
!2228 = !DILocation(line: 955, column: 37, scope: !665)
!2229 = !DILocation(line: 955, column: 2, scope: !665)
!2230 = !DILocation(line: 957, column: 31, scope: !665)
!2231 = !DILocation(line: 957, column: 34, scope: !665)
!2232 = !DILocation(line: 957, column: 8, scope: !665)
!2233 = !DILocation(line: 957, column: 6, scope: !665)
!2234 = !DILocation(line: 958, column: 6, scope: !2235)
!2235 = distinct !DILexicalBlock(scope: !665, file: !1, line: 958, column: 6)
!2236 = !DILocation(line: 958, column: 10, scope: !2235)
!2237 = !DILocation(line: 958, column: 6, scope: !665)
!2238 = !DILocation(line: 959, column: 3, scope: !2235)
!2239 = !DILocation(line: 960, column: 2, scope: !665)
!2240 = !DILocation(line: 960, column: 7, scope: !665)
!2241 = !DILocation(line: 960, column: 21, scope: !665)
!2242 = !DILocation(line: 962, column: 19, scope: !665)
!2243 = !DILocation(line: 962, column: 24, scope: !665)
!2244 = !DILocation(line: 962, column: 31, scope: !665)
!2245 = !DILocation(line: 962, column: 8, scope: !665)
!2246 = !DILocation(line: 962, column: 6, scope: !665)
!2247 = !DILocation(line: 963, column: 6, scope: !2248)
!2248 = distinct !DILexicalBlock(scope: !665, file: !1, line: 963, column: 6)
!2249 = !DILocation(line: 963, column: 10, scope: !2248)
!2250 = !DILocation(line: 963, column: 6, scope: !665)
!2251 = !DILocation(line: 964, column: 3, scope: !2248)
!2252 = !DILocation(line: 965, column: 24, scope: !665)
!2253 = !DILocation(line: 965, column: 2, scope: !665)
!2254 = !DILocation(line: 965, column: 7, scope: !665)
!2255 = !DILocation(line: 965, column: 21, scope: !665)
!2256 = !DILocation(line: 967, column: 31, scope: !665)
!2257 = !DILocation(line: 967, column: 34, scope: !665)
!2258 = !DILocation(line: 967, column: 47, scope: !665)
!2259 = !DILocation(line: 967, column: 51, scope: !665)
!2260 = !DILocation(line: 967, column: 49, scope: !665)
!2261 = !DILocation(line: 967, column: 8, scope: !665)
!2262 = !DILocation(line: 967, column: 6, scope: !665)
!2263 = !DILocation(line: 968, column: 6, scope: !2264)
!2264 = distinct !DILexicalBlock(scope: !665, file: !1, line: 968, column: 6)
!2265 = !DILocation(line: 968, column: 10, scope: !2264)
!2266 = !DILocation(line: 968, column: 6, scope: !665)
!2267 = !DILocation(line: 969, column: 3, scope: !2264)
!2268 = !DILocation(line: 970, column: 24, scope: !665)
!2269 = !DILocation(line: 970, column: 28, scope: !665)
!2270 = !DILocation(line: 970, column: 26, scope: !665)
!2271 = !DILocation(line: 970, column: 2, scope: !665)
!2272 = !DILocation(line: 970, column: 7, scope: !665)
!2273 = !DILocation(line: 970, column: 21, scope: !665)
!2274 = !DILocation(line: 973, column: 6, scope: !2275)
!2275 = distinct !DILexicalBlock(scope: !665, file: !1, line: 973, column: 6)
!2276 = !DILocation(line: 973, column: 12, scope: !2275)
!2277 = !DILocation(line: 973, column: 6, scope: !665)
!2278 = !DILocation(line: 974, column: 32, scope: !2279)
!2279 = distinct !DILexicalBlock(scope: !2275, file: !1, line: 973, column: 21)
!2280 = !DILocation(line: 974, column: 35, scope: !2279)
!2281 = !DILocation(line: 974, column: 42, scope: !2279)
!2282 = !DILocation(line: 974, column: 9, scope: !2279)
!2283 = !DILocation(line: 974, column: 7, scope: !2279)
!2284 = !DILocation(line: 975, column: 7, scope: !2285)
!2285 = distinct !DILexicalBlock(scope: !2279, file: !1, line: 975, column: 7)
!2286 = !DILocation(line: 975, column: 11, scope: !2285)
!2287 = !DILocation(line: 975, column: 7, scope: !2279)
!2288 = !DILocation(line: 976, column: 4, scope: !2285)
!2289 = !DILocation(line: 977, column: 36, scope: !2279)
!2290 = !DILocation(line: 977, column: 3, scope: !2279)
!2291 = !DILocation(line: 977, column: 8, scope: !2279)
!2292 = !DILocation(line: 977, column: 33, scope: !2279)
!2293 = !DILocation(line: 978, column: 38, scope: !2279)
!2294 = !DILocation(line: 978, column: 3, scope: !2279)
!2295 = !DILocation(line: 978, column: 8, scope: !2279)
!2296 = !DILocation(line: 978, column: 35, scope: !2279)
!2297 = !DILocation(line: 979, column: 25, scope: !2279)
!2298 = !DILocation(line: 979, column: 3, scope: !2279)
!2299 = !DILocation(line: 979, column: 8, scope: !2279)
!2300 = !DILocation(line: 979, column: 22, scope: !2279)
!2301 = !DILocation(line: 980, column: 2, scope: !2279)
!2302 = !DILocation(line: 983, column: 6, scope: !2303)
!2303 = distinct !DILexicalBlock(scope: !665, file: !1, line: 983, column: 6)
!2304 = !DILocation(line: 983, column: 11, scope: !2303)
!2305 = !DILocation(line: 983, column: 29, scope: !2303)
!2306 = !DILocation(line: 983, column: 6, scope: !665)
!2307 = !DILocation(line: 984, column: 3, scope: !2308)
!2308 = distinct !DILexicalBlock(scope: !2303, file: !1, line: 983, column: 53)
!2309 = !DILocation(line: 984, column: 8, scope: !2308)
!2310 = !DILocation(line: 984, column: 15, scope: !2308)
!2311 = !DILocation(line: 984, column: 22, scope: !2308)
!2312 = !DILocation(line: 985, column: 3, scope: !2308)
!2313 = !DILocation(line: 985, column: 8, scope: !2308)
!2314 = !DILocation(line: 985, column: 15, scope: !2308)
!2315 = !DILocation(line: 985, column: 21, scope: !2308)
!2316 = !DILocation(line: 986, column: 3, scope: !2308)
!2317 = !DILocation(line: 986, column: 8, scope: !2308)
!2318 = !DILocation(line: 986, column: 15, scope: !2308)
!2319 = !DILocation(line: 986, column: 22, scope: !2308)
!2320 = !DILocation(line: 987, column: 26, scope: !2308)
!2321 = !DILocation(line: 987, column: 31, scope: !2308)
!2322 = !DILocation(line: 987, column: 3, scope: !2308)
!2323 = !DILocation(line: 987, column: 8, scope: !2308)
!2324 = !DILocation(line: 987, column: 15, scope: !2308)
!2325 = !DILocation(line: 987, column: 24, scope: !2308)
!2326 = !DILocation(line: 988, column: 33, scope: !2308)
!2327 = !DILocation(line: 988, column: 38, scope: !2308)
!2328 = !DILocation(line: 988, column: 27, scope: !2308)
!2329 = !DILocation(line: 988, column: 3, scope: !2308)
!2330 = !DILocation(line: 988, column: 8, scope: !2308)
!2331 = !DILocation(line: 988, column: 15, scope: !2308)
!2332 = !DILocation(line: 988, column: 25, scope: !2308)
!2333 = !DILocation(line: 989, column: 7, scope: !2334)
!2334 = distinct !DILexicalBlock(scope: !2308, file: !1, line: 989, column: 7)
!2335 = !DILocation(line: 990, column: 47, scope: !2334)
!2336 = !DILocation(line: 989, column: 7, scope: !2308)
!2337 = !DILocation(line: 991, column: 23, scope: !2338)
!2338 = distinct !DILexicalBlock(scope: !2334, file: !1, line: 990, column: 56)
!2339 = !DILocation(line: 991, column: 26, scope: !2338)
!2340 = !DILocation(line: 991, column: 4, scope: !2338)
!2341 = !DILocation(line: 993, column: 4, scope: !2338)
!2342 = !DILocation(line: 995, column: 2, scope: !2308)
!2343 = !DILocation(line: 998, column: 10, scope: !665)
!2344 = !DILocation(line: 998, column: 2, scope: !665)
!2345 = !DILocation(line: 999, column: 1, scope: !665)
!2346 = !DILocalVariable(name: "a", arg: 1, scope: !701, file: !1, line: 1002, type: !353)
!2347 = !DILocation(line: 1002, column: 46, scope: !701)
!2348 = !DILocalVariable(name: "buff", arg: 2, scope: !701, file: !1, line: 1002, type: !392)
!2349 = !DILocation(line: 1002, column: 61, scope: !701)
!2350 = !DILocalVariable(name: "s", arg: 3, scope: !701, file: !1, line: 1002, type: !394)
!2351 = !DILocation(line: 1002, column: 74, scope: !701)
!2352 = !DILocalVariable(name: "ret", scope: !701, file: !1, line: 1004, type: !372)
!2353 = !DILocation(line: 1004, column: 6, scope: !701)
!2354 = !DILocalVariable(name: "zip", scope: !701, file: !1, line: 1005, type: !541)
!2355 = !DILocation(line: 1005, column: 14, scope: !701)
!2356 = !DILocation(line: 1005, column: 20, scope: !701)
!2357 = !DILocation(line: 1005, column: 23, scope: !701)
!2358 = !DILocation(line: 1007, column: 15, scope: !2359)
!2359 = distinct !DILexicalBlock(scope: !701, file: !1, line: 1007, column: 6)
!2360 = !DILocation(line: 1007, column: 19, scope: !2359)
!2361 = !DILocation(line: 1007, column: 24, scope: !2359)
!2362 = !DILocation(line: 1007, column: 17, scope: !2359)
!2363 = !DILocation(line: 1007, column: 6, scope: !701)
!2364 = !DILocation(line: 1008, column: 15, scope: !2359)
!2365 = !DILocation(line: 1008, column: 20, scope: !2359)
!2366 = !DILocation(line: 1008, column: 5, scope: !2359)
!2367 = !DILocation(line: 1008, column: 3, scope: !2359)
!2368 = !DILocation(line: 1009, column: 37, scope: !701)
!2369 = !DILocation(line: 1009, column: 2, scope: !701)
!2370 = !DILocation(line: 1009, column: 7, scope: !701)
!2371 = !DILocation(line: 1009, column: 34, scope: !701)
!2372 = !DILocation(line: 1011, column: 6, scope: !2373)
!2373 = distinct !DILexicalBlock(scope: !701, file: !1, line: 1011, column: 6)
!2374 = !DILocation(line: 1011, column: 8, scope: !2373)
!2375 = !DILocation(line: 1011, column: 6, scope: !701)
!2376 = !DILocation(line: 1011, column: 14, scope: !2377)
!2377 = !DILexicalBlockFile(scope: !2373, file: !1, discriminator: 1)
!2378 = !DILocation(line: 1013, column: 6, scope: !2379)
!2379 = distinct !DILexicalBlock(scope: !701, file: !1, line: 1013, column: 6)
!2380 = !DILocation(line: 1013, column: 11, scope: !2379)
!2381 = !DILocation(line: 1013, column: 23, scope: !2379)
!2382 = !DILocation(line: 1013, column: 6, scope: !701)
!2383 = !DILocation(line: 1014, column: 11, scope: !2384)
!2384 = distinct !DILexicalBlock(scope: !2379, file: !1, line: 1013, column: 51)
!2385 = !DILocation(line: 1014, column: 16, scope: !2384)
!2386 = !DILocation(line: 1014, column: 3, scope: !2384)
!2387 = !DILocation(line: 1017, column: 9, scope: !2388)
!2388 = distinct !DILexicalBlock(scope: !2389, file: !1, line: 1017, column: 8)
!2389 = distinct !DILexicalBlock(scope: !2384, file: !1, line: 1014, column: 34)
!2390 = !DILocation(line: 1017, column: 14, scope: !2388)
!2391 = !DILocation(line: 1017, column: 8, scope: !2389)
!2392 = !DILocation(line: 1018, column: 46, scope: !2393)
!2393 = distinct !DILexicalBlock(scope: !2388, file: !1, line: 1017, column: 26)
!2394 = !DILocation(line: 1018, column: 11, scope: !2393)
!2395 = !DILocation(line: 1018, column: 9, scope: !2393)
!2396 = !DILocation(line: 1019, column: 9, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !2393, file: !1, line: 1019, column: 9)
!2398 = !DILocation(line: 1019, column: 13, scope: !2397)
!2399 = !DILocation(line: 1019, column: 9, scope: !2393)
!2400 = !DILocation(line: 1020, column: 14, scope: !2397)
!2401 = !DILocation(line: 1020, column: 13, scope: !2397)
!2402 = !DILocation(line: 1020, column: 6, scope: !2397)
!2403 = !DILocation(line: 1021, column: 5, scope: !2393)
!2404 = !DILocation(line: 1021, column: 10, scope: !2393)
!2405 = !DILocation(line: 1021, column: 21, scope: !2393)
!2406 = !DILocation(line: 1022, column: 4, scope: !2393)
!2407 = !DILocation(line: 1023, column: 4, scope: !2389)
!2408 = !DILocation(line: 1026, column: 9, scope: !2409)
!2409 = distinct !DILexicalBlock(scope: !2389, file: !1, line: 1026, column: 8)
!2410 = !DILocation(line: 1026, column: 14, scope: !2409)
!2411 = !DILocation(line: 1026, column: 8, scope: !2389)
!2412 = !DILocation(line: 1027, column: 38, scope: !2413)
!2413 = distinct !DILexicalBlock(scope: !2409, file: !1, line: 1026, column: 26)
!2414 = !DILocation(line: 1027, column: 11, scope: !2413)
!2415 = !DILocation(line: 1027, column: 9, scope: !2413)
!2416 = !DILocation(line: 1028, column: 9, scope: !2417)
!2417 = distinct !DILexicalBlock(scope: !2413, file: !1, line: 1028, column: 9)
!2418 = !DILocation(line: 1028, column: 13, scope: !2417)
!2419 = !DILocation(line: 1028, column: 9, scope: !2413)
!2420 = !DILocation(line: 1029, column: 14, scope: !2417)
!2421 = !DILocation(line: 1029, column: 13, scope: !2417)
!2422 = !DILocation(line: 1029, column: 6, scope: !2417)
!2423 = !DILocation(line: 1030, column: 23, scope: !2413)
!2424 = !DILocation(line: 1030, column: 28, scope: !2413)
!2425 = !DILocation(line: 1030, column: 39, scope: !2413)
!2426 = !DILocation(line: 1030, column: 5, scope: !2413)
!2427 = !DILocation(line: 1030, column: 10, scope: !2413)
!2428 = !DILocation(line: 1030, column: 21, scope: !2413)
!2429 = !DILocation(line: 1031, column: 4, scope: !2413)
!2430 = !DILocation(line: 1032, column: 4, scope: !2389)
!2431 = !DILocation(line: 1034, column: 4, scope: !2389)
!2432 = !DILocation(line: 1036, column: 2, scope: !2384)
!2433 = !DILocation(line: 1038, column: 10, scope: !701)
!2434 = !DILocation(line: 1038, column: 15, scope: !701)
!2435 = !DILocation(line: 1038, column: 2, scope: !701)
!2436 = !DILocation(line: 1040, column: 7, scope: !2437)
!2437 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 1040, column: 7)
!2438 = distinct !DILexicalBlock(scope: !701, file: !1, line: 1038, column: 34)
!2439 = !DILocation(line: 1040, column: 12, scope: !2437)
!2440 = !DILocation(line: 1040, column: 23, scope: !2437)
!2441 = !DILocation(line: 1040, column: 26, scope: !2442)
!2442 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 1)
!2443 = !DILocation(line: 1040, column: 31, scope: !2442)
!2444 = !DILocation(line: 1040, column: 7, scope: !2442)
!2445 = !DILocalVariable(name: "rb", scope: !2446, file: !1, line: 1041, type: !646)
!2446 = distinct !DILexicalBlock(scope: !2437, file: !1, line: 1040, column: 43)
!2447 = !DILocation(line: 1041, column: 19, scope: !2446)
!2448 = !DILocation(line: 1041, column: 41, scope: !2446)
!2449 = !DILocalVariable(name: "re", scope: !2446, file: !1, line: 1042, type: !2450)
!2450 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !646)
!2451 = !DILocation(line: 1042, column: 26, scope: !2446)
!2452 = !DILocation(line: 1042, column: 31, scope: !2446)
!2453 = !DILocation(line: 1042, column: 36, scope: !2446)
!2454 = !DILocation(line: 1042, column: 34, scope: !2446)
!2455 = !DILocation(line: 1044, column: 4, scope: !2446)
!2456 = !DILocation(line: 1044, column: 11, scope: !2457)
!2457 = !DILexicalBlockFile(scope: !2446, file: !1, discriminator: 1)
!2458 = !DILocation(line: 1044, column: 16, scope: !2457)
!2459 = !DILocation(line: 1044, column: 14, scope: !2457)
!2460 = !DILocation(line: 1044, column: 4, scope: !2457)
!2461 = !DILocalVariable(name: "l", scope: !2462, file: !1, line: 1045, type: !394)
!2462 = distinct !DILexicalBlock(scope: !2446, file: !1, line: 1044, column: 20)
!2463 = !DILocation(line: 1045, column: 12, scope: !2462)
!2464 = !DILocation(line: 1047, column: 9, scope: !2465)
!2465 = distinct !DILexicalBlock(scope: !2462, file: !1, line: 1047, column: 9)
!2466 = !DILocation(line: 1047, column: 14, scope: !2465)
!2467 = !DILocation(line: 1047, column: 9, scope: !2462)
!2468 = !DILocation(line: 1048, column: 35, scope: !2469)
!2469 = distinct !DILexicalBlock(scope: !2465, file: !1, line: 1047, column: 26)
!2470 = !DILocation(line: 1048, column: 40, scope: !2469)
!2471 = !DILocation(line: 1049, column: 10, scope: !2469)
!2472 = !DILocation(line: 1049, column: 14, scope: !2469)
!2473 = !DILocation(line: 1049, column: 19, scope: !2469)
!2474 = !DILocation(line: 1049, column: 17, scope: !2469)
!2475 = !DILocation(line: 1050, column: 10, scope: !2469)
!2476 = !DILocation(line: 1050, column: 15, scope: !2469)
!2477 = !DILocation(line: 1050, column: 20, scope: !2469)
!2478 = !DILocation(line: 1050, column: 25, scope: !2469)
!2479 = !DILocation(line: 1048, column: 10, scope: !2469)
!2480 = !DILocation(line: 1048, column: 8, scope: !2469)
!2481 = !DILocation(line: 1051, column: 5, scope: !2469)
!2482 = !DILocation(line: 1052, column: 10, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2465, file: !1, line: 1051, column: 12)
!2484 = !DILocation(line: 1052, column: 15, scope: !2483)
!2485 = !DILocation(line: 1052, column: 8, scope: !2483)
!2486 = !DILocation(line: 1053, column: 12, scope: !2483)
!2487 = !DILocation(line: 1053, column: 10, scope: !2483)
!2488 = !DILocation(line: 1056, column: 10, scope: !2489)
!2489 = distinct !DILexicalBlock(scope: !2483, file: !1, line: 1056, column: 10)
!2490 = !DILocation(line: 1056, column: 14, scope: !2489)
!2491 = !DILocation(line: 1056, column: 10, scope: !2483)
!2492 = !DILocation(line: 1057, column: 26, scope: !2493)
!2493 = distinct !DILexicalBlock(scope: !2489, file: !1, line: 1056, column: 19)
!2494 = !DILocation(line: 1057, column: 29, scope: !2493)
!2495 = !DILocation(line: 1057, column: 7, scope: !2493)
!2496 = !DILocation(line: 1060, column: 7, scope: !2493)
!2497 = !DILocation(line: 1062, column: 6, scope: !2483)
!2498 = !DILocation(line: 1065, column: 34, scope: !2462)
!2499 = !DILocation(line: 1065, column: 37, scope: !2462)
!2500 = !DILocation(line: 1065, column: 42, scope: !2462)
!2501 = !DILocation(line: 1065, column: 47, scope: !2462)
!2502 = !DILocation(line: 1065, column: 11, scope: !2462)
!2503 = !DILocation(line: 1065, column: 9, scope: !2462)
!2504 = !DILocation(line: 1066, column: 9, scope: !2505)
!2505 = distinct !DILexicalBlock(scope: !2462, file: !1, line: 1066, column: 9)
!2506 = !DILocation(line: 1066, column: 13, scope: !2505)
!2507 = !DILocation(line: 1066, column: 9, scope: !2462)
!2508 = !DILocation(line: 1067, column: 14, scope: !2505)
!2509 = !DILocation(line: 1067, column: 13, scope: !2505)
!2510 = !DILocation(line: 1067, column: 6, scope: !2505)
!2511 = !DILocation(line: 1068, column: 38, scope: !2462)
!2512 = !DILocation(line: 1068, column: 5, scope: !2462)
!2513 = !DILocation(line: 1068, column: 10, scope: !2462)
!2514 = !DILocation(line: 1068, column: 35, scope: !2462)
!2515 = !DILocation(line: 1069, column: 27, scope: !2462)
!2516 = !DILocation(line: 1069, column: 5, scope: !2462)
!2517 = !DILocation(line: 1069, column: 10, scope: !2462)
!2518 = !DILocation(line: 1069, column: 24, scope: !2462)
!2519 = !DILocation(line: 1070, column: 11, scope: !2462)
!2520 = !DILocation(line: 1070, column: 8, scope: !2462)
!2521 = !DILocation(line: 1044, column: 4, scope: !2522)
!2522 = !DILexicalBlockFile(scope: !2446, file: !1, discriminator: 2)
!2523 = !DILocation(line: 1072, column: 3, scope: !2446)
!2524 = !DILocation(line: 1073, column: 33, scope: !2525)
!2525 = distinct !DILexicalBlock(scope: !2437, file: !1, line: 1072, column: 10)
!2526 = !DILocation(line: 1073, column: 36, scope: !2525)
!2527 = !DILocation(line: 1073, column: 42, scope: !2525)
!2528 = !DILocation(line: 1073, column: 10, scope: !2525)
!2529 = !DILocation(line: 1073, column: 8, scope: !2525)
!2530 = !DILocation(line: 1074, column: 8, scope: !2531)
!2531 = distinct !DILexicalBlock(scope: !2525, file: !1, line: 1074, column: 8)
!2532 = !DILocation(line: 1074, column: 12, scope: !2531)
!2533 = !DILocation(line: 1074, column: 8, scope: !2525)
!2534 = !DILocation(line: 1075, column: 13, scope: !2531)
!2535 = !DILocation(line: 1075, column: 12, scope: !2531)
!2536 = !DILocation(line: 1075, column: 5, scope: !2531)
!2537 = !DILocation(line: 1076, column: 26, scope: !2525)
!2538 = !DILocation(line: 1076, column: 4, scope: !2525)
!2539 = !DILocation(line: 1076, column: 9, scope: !2525)
!2540 = !DILocation(line: 1076, column: 23, scope: !2525)
!2541 = !DILocation(line: 1077, column: 37, scope: !2525)
!2542 = !DILocation(line: 1077, column: 4, scope: !2525)
!2543 = !DILocation(line: 1077, column: 9, scope: !2525)
!2544 = !DILocation(line: 1077, column: 34, scope: !2525)
!2545 = !DILocation(line: 1079, column: 3, scope: !2438)
!2546 = !DILocation(line: 1082, column: 52, scope: !2438)
!2547 = !DILocation(line: 1082, column: 41, scope: !2438)
!2548 = !DILocation(line: 1082, column: 25, scope: !2438)
!2549 = !DILocation(line: 1082, column: 3, scope: !2438)
!2550 = !DILocation(line: 1082, column: 8, scope: !2438)
!2551 = !DILocation(line: 1082, column: 15, scope: !2438)
!2552 = !DILocation(line: 1082, column: 23, scope: !2438)
!2553 = !DILocation(line: 1083, column: 32, scope: !2438)
!2554 = !DILocation(line: 1083, column: 26, scope: !2438)
!2555 = !DILocation(line: 1083, column: 3, scope: !2438)
!2556 = !DILocation(line: 1083, column: 8, scope: !2438)
!2557 = !DILocation(line: 1083, column: 15, scope: !2438)
!2558 = !DILocation(line: 1083, column: 24, scope: !2438)
!2559 = !DILocation(line: 1084, column: 3, scope: !2438)
!2560 = !DILocation(line: 1085, column: 19, scope: !2561)
!2561 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 1084, column: 6)
!2562 = !DILocation(line: 1085, column: 24, scope: !2561)
!2563 = !DILocation(line: 1085, column: 10, scope: !2561)
!2564 = !DILocation(line: 1085, column: 8, scope: !2561)
!2565 = !DILocation(line: 1086, column: 8, scope: !2566)
!2566 = distinct !DILexicalBlock(scope: !2561, file: !1, line: 1086, column: 8)
!2567 = !DILocation(line: 1086, column: 12, scope: !2566)
!2568 = !DILocation(line: 1086, column: 8, scope: !2561)
!2569 = !DILocation(line: 1087, column: 5, scope: !2566)
!2570 = !DILocation(line: 1088, column: 8, scope: !2571)
!2571 = distinct !DILexicalBlock(scope: !2561, file: !1, line: 1088, column: 8)
!2572 = !DILocation(line: 1088, column: 13, scope: !2571)
!2573 = !DILocation(line: 1088, column: 20, scope: !2571)
!2574 = !DILocation(line: 1088, column: 30, scope: !2571)
!2575 = !DILocation(line: 1088, column: 8, scope: !2561)
!2576 = !DILocation(line: 1089, column: 9, scope: !2577)
!2577 = distinct !DILexicalBlock(scope: !2578, file: !1, line: 1089, column: 9)
!2578 = distinct !DILexicalBlock(scope: !2571, file: !1, line: 1088, column: 36)
!2579 = !DILocation(line: 1089, column: 14, scope: !2577)
!2580 = !DILocation(line: 1089, column: 9, scope: !2578)
!2581 = !DILocation(line: 1090, column: 31, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2577, file: !1, line: 1089, column: 26)
!2583 = !DILocation(line: 1090, column: 36, scope: !2582)
!2584 = !DILocation(line: 1091, column: 10, scope: !2582)
!2585 = !DILocation(line: 1091, column: 15, scope: !2582)
!2586 = !DILocation(line: 1091, column: 20, scope: !2582)
!2587 = !DILocation(line: 1091, column: 25, scope: !2582)
!2588 = !DILocation(line: 1092, column: 10, scope: !2582)
!2589 = !DILocation(line: 1092, column: 15, scope: !2582)
!2590 = !DILocation(line: 1092, column: 20, scope: !2582)
!2591 = !DILocation(line: 1092, column: 25, scope: !2582)
!2592 = !DILocation(line: 1090, column: 6, scope: !2582)
!2593 = !DILocation(line: 1093, column: 5, scope: !2582)
!2594 = !DILocation(line: 1093, column: 16, scope: !2595)
!2595 = !DILexicalBlockFile(scope: !2596, file: !1, discriminator: 1)
!2596 = distinct !DILexicalBlock(scope: !2577, file: !1, line: 1093, column: 16)
!2597 = !DILocation(line: 1093, column: 21, scope: !2595)
!2598 = !DILocalVariable(name: "outl", scope: !2599, file: !1, line: 1094, type: !394)
!2599 = distinct !DILexicalBlock(scope: !2596, file: !1, line: 1093, column: 33)
!2600 = !DILocation(line: 1094, column: 13, scope: !2599)
!2601 = !DILocation(line: 1094, column: 20, scope: !2599)
!2602 = !DILocation(line: 1094, column: 25, scope: !2599)
!2603 = !DILocation(line: 1095, column: 12, scope: !2599)
!2604 = !DILocation(line: 1095, column: 10, scope: !2599)
!2605 = !DILocation(line: 1099, column: 10, scope: !2606)
!2606 = distinct !DILexicalBlock(scope: !2599, file: !1, line: 1099, column: 10)
!2607 = !DILocation(line: 1099, column: 14, scope: !2606)
!2608 = !DILocation(line: 1099, column: 10, scope: !2599)
!2609 = !DILocation(line: 1100, column: 26, scope: !2610)
!2610 = distinct !DILexicalBlock(scope: !2606, file: !1, line: 1099, column: 19)
!2611 = !DILocation(line: 1100, column: 29, scope: !2610)
!2612 = !DILocation(line: 1100, column: 7, scope: !2610)
!2613 = !DILocation(line: 1103, column: 7, scope: !2610)
!2614 = !DILocation(line: 1105, column: 6, scope: !2599)
!2615 = !DILocation(line: 1107, column: 5, scope: !2599)
!2616 = !DILocation(line: 1108, column: 34, scope: !2578)
!2617 = !DILocation(line: 1108, column: 37, scope: !2578)
!2618 = !DILocation(line: 1108, column: 42, scope: !2578)
!2619 = !DILocation(line: 1109, column: 6, scope: !2578)
!2620 = !DILocation(line: 1109, column: 11, scope: !2578)
!2621 = !DILocation(line: 1108, column: 11, scope: !2578)
!2622 = !DILocation(line: 1108, column: 9, scope: !2578)
!2623 = !DILocation(line: 1110, column: 9, scope: !2624)
!2624 = distinct !DILexicalBlock(scope: !2578, file: !1, line: 1110, column: 9)
!2625 = !DILocation(line: 1110, column: 13, scope: !2624)
!2626 = !DILocation(line: 1110, column: 9, scope: !2578)
!2627 = !DILocation(line: 1111, column: 14, scope: !2624)
!2628 = !DILocation(line: 1111, column: 13, scope: !2624)
!2629 = !DILocation(line: 1111, column: 6, scope: !2624)
!2630 = !DILocation(line: 1112, column: 38, scope: !2578)
!2631 = !DILocation(line: 1112, column: 43, scope: !2578)
!2632 = !DILocation(line: 1112, column: 5, scope: !2578)
!2633 = !DILocation(line: 1112, column: 10, scope: !2578)
!2634 = !DILocation(line: 1112, column: 35, scope: !2578)
!2635 = !DILocation(line: 1113, column: 27, scope: !2578)
!2636 = !DILocation(line: 1113, column: 32, scope: !2578)
!2637 = !DILocation(line: 1113, column: 5, scope: !2578)
!2638 = !DILocation(line: 1113, column: 10, scope: !2578)
!2639 = !DILocation(line: 1113, column: 24, scope: !2578)
!2640 = !DILocation(line: 1114, column: 28, scope: !2578)
!2641 = !DILocation(line: 1114, column: 33, scope: !2578)
!2642 = !DILocation(line: 1114, column: 5, scope: !2578)
!2643 = !DILocation(line: 1114, column: 10, scope: !2578)
!2644 = !DILocation(line: 1114, column: 17, scope: !2578)
!2645 = !DILocation(line: 1114, column: 26, scope: !2578)
!2646 = !DILocation(line: 1115, column: 35, scope: !2578)
!2647 = !DILocation(line: 1115, column: 40, scope: !2578)
!2648 = !DILocation(line: 1115, column: 29, scope: !2578)
!2649 = !DILocation(line: 1115, column: 5, scope: !2578)
!2650 = !DILocation(line: 1115, column: 10, scope: !2578)
!2651 = !DILocation(line: 1115, column: 17, scope: !2578)
!2652 = !DILocation(line: 1115, column: 27, scope: !2578)
!2653 = !DILocation(line: 1116, column: 4, scope: !2578)
!2654 = !DILocation(line: 1117, column: 3, scope: !2561)
!2655 = !DILocation(line: 1117, column: 12, scope: !2656)
!2656 = !DILexicalBlockFile(scope: !2438, file: !1, discriminator: 1)
!2657 = !DILocation(line: 1117, column: 17, scope: !2656)
!2658 = !DILocation(line: 1117, column: 24, scope: !2656)
!2659 = !DILocation(line: 1117, column: 33, scope: !2656)
!2660 = !DILocation(line: 1117, column: 3, scope: !2656)
!2661 = !DILocation(line: 1118, column: 3, scope: !2438)
!2662 = !DILocation(line: 1122, column: 22, scope: !2438)
!2663 = !DILocation(line: 1122, column: 25, scope: !2438)
!2664 = !DILocation(line: 1122, column: 3, scope: !2438)
!2665 = !DILocation(line: 1124, column: 3, scope: !2438)
!2666 = !DILocation(line: 1127, column: 35, scope: !701)
!2667 = !DILocation(line: 1127, column: 2, scope: !701)
!2668 = !DILocation(line: 1127, column: 7, scope: !701)
!2669 = !DILocation(line: 1127, column: 32, scope: !701)
!2670 = !DILocation(line: 1128, column: 7, scope: !2671)
!2671 = distinct !DILexicalBlock(scope: !701, file: !1, line: 1128, column: 6)
!2672 = !DILocation(line: 1128, column: 12, scope: !2671)
!2673 = !DILocation(line: 1128, column: 23, scope: !2671)
!2674 = !DILocation(line: 1128, column: 26, scope: !2675)
!2675 = !DILexicalBlockFile(scope: !2671, file: !1, discriminator: 1)
!2676 = !DILocation(line: 1128, column: 31, scope: !2675)
!2677 = !DILocation(line: 1128, column: 42, scope: !2675)
!2678 = !DILocation(line: 1128, column: 6, scope: !2675)
!2679 = !DILocation(line: 1130, column: 7, scope: !2671)
!2680 = !DILocation(line: 1130, column: 12, scope: !2671)
!2681 = !DILocation(line: 1130, column: 22, scope: !2671)
!2682 = !DILocation(line: 1130, column: 27, scope: !2671)
!2683 = !DILocation(line: 1130, column: 40, scope: !2671)
!2684 = !DILocation(line: 1130, column: 56, scope: !2671)
!2685 = !DILocation(line: 1130, column: 46, scope: !2671)
!2686 = !DILocation(line: 1129, column: 3, scope: !2671)
!2687 = !DILocation(line: 1129, column: 8, scope: !2671)
!2688 = !DILocation(line: 1129, column: 20, scope: !2671)
!2689 = !DILocation(line: 1131, column: 10, scope: !701)
!2690 = !DILocation(line: 1131, column: 2, scope: !701)
!2691 = !DILocation(line: 1133, column: 1, scope: !701)
!2692 = !DILocalVariable(name: "a", arg: 1, scope: !718, file: !1, line: 1136, type: !353)
!2693 = !DILocation(line: 1136, column: 54, scope: !718)
!2694 = !DILocalVariable(name: "zip", scope: !718, file: !1, line: 1138, type: !541)
!2695 = !DILocation(line: 1138, column: 14, scope: !718)
!2696 = !DILocation(line: 1138, column: 20, scope: !718)
!2697 = !DILocation(line: 1138, column: 23, scope: !718)
!2698 = !DILocalVariable(name: "ret", scope: !718, file: !1, line: 1139, type: !372)
!2699 = !DILocation(line: 1139, column: 6, scope: !718)
!2700 = !DILocation(line: 1142, column: 6, scope: !2701)
!2701 = distinct !DILexicalBlock(scope: !718, file: !1, line: 1142, column: 6)
!2702 = !DILocation(line: 1142, column: 11, scope: !2701)
!2703 = !DILocation(line: 1142, column: 29, scope: !2701)
!2704 = !DILocation(line: 1142, column: 6, scope: !718)
!2705 = !DILocation(line: 1143, column: 3, scope: !2706)
!2706 = distinct !DILexicalBlock(scope: !2701, file: !1, line: 1142, column: 53)
!2707 = !DILocalVariable(name: "remainder", scope: !2708, file: !1, line: 1144, type: !394)
!2708 = distinct !DILexicalBlock(scope: !2709, file: !1, line: 1143, column: 12)
!2709 = distinct !DILexicalBlock(scope: !2710, file: !1, line: 1143, column: 3)
!2710 = distinct !DILexicalBlock(scope: !2706, file: !1, line: 1143, column: 3)
!2711 = !DILocation(line: 1144, column: 11, scope: !2708)
!2712 = !DILocation(line: 1146, column: 19, scope: !2708)
!2713 = !DILocation(line: 1146, column: 24, scope: !2708)
!2714 = !DILocation(line: 1146, column: 10, scope: !2708)
!2715 = !DILocation(line: 1146, column: 8, scope: !2708)
!2716 = !DILocation(line: 1147, column: 8, scope: !2717)
!2717 = distinct !DILexicalBlock(scope: !2708, file: !1, line: 1147, column: 8)
!2718 = !DILocation(line: 1147, column: 12, scope: !2717)
!2719 = !DILocation(line: 1147, column: 8, scope: !2708)
!2720 = !DILocation(line: 1148, column: 5, scope: !2717)
!2721 = !DILocation(line: 1149, column: 16, scope: !2708)
!2722 = !DILocation(line: 1149, column: 21, scope: !2708)
!2723 = !DILocation(line: 1149, column: 31, scope: !2708)
!2724 = !DILocation(line: 1149, column: 36, scope: !2708)
!2725 = !DILocation(line: 1149, column: 43, scope: !2708)
!2726 = !DILocation(line: 1149, column: 29, scope: !2708)
!2727 = !DILocation(line: 1149, column: 14, scope: !2708)
!2728 = !DILocation(line: 1150, column: 8, scope: !2729)
!2729 = distinct !DILexicalBlock(scope: !2708, file: !1, line: 1150, column: 8)
!2730 = !DILocation(line: 1150, column: 13, scope: !2729)
!2731 = !DILocation(line: 1150, column: 8, scope: !2708)
!2732 = !DILocation(line: 1151, column: 30, scope: !2733)
!2733 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 1150, column: 25)
!2734 = !DILocation(line: 1151, column: 35, scope: !2733)
!2735 = !DILocation(line: 1152, column: 9, scope: !2733)
!2736 = !DILocation(line: 1152, column: 14, scope: !2733)
!2737 = !DILocation(line: 1152, column: 19, scope: !2733)
!2738 = !DILocation(line: 1152, column: 30, scope: !2733)
!2739 = !DILocation(line: 1152, column: 35, scope: !2733)
!2740 = !DILocation(line: 1152, column: 40, scope: !2733)
!2741 = !DILocation(line: 1151, column: 5, scope: !2733)
!2742 = !DILocation(line: 1153, column: 4, scope: !2733)
!2743 = !DILocation(line: 1153, column: 15, scope: !2744)
!2744 = !DILexicalBlockFile(scope: !2745, file: !1, discriminator: 1)
!2745 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 1153, column: 15)
!2746 = !DILocation(line: 1153, column: 20, scope: !2744)
!2747 = !DILocalVariable(name: "outl", scope: !2748, file: !1, line: 1154, type: !394)
!2748 = distinct !DILexicalBlock(scope: !2745, file: !1, line: 1153, column: 32)
!2749 = !DILocation(line: 1154, column: 12, scope: !2748)
!2750 = !DILocation(line: 1154, column: 19, scope: !2748)
!2751 = !DILocation(line: 1155, column: 11, scope: !2748)
!2752 = !DILocation(line: 1155, column: 9, scope: !2748)
!2753 = !DILocation(line: 1158, column: 9, scope: !2754)
!2754 = distinct !DILexicalBlock(scope: !2748, file: !1, line: 1158, column: 9)
!2755 = !DILocation(line: 1158, column: 13, scope: !2754)
!2756 = !DILocation(line: 1158, column: 9, scope: !2748)
!2757 = !DILocation(line: 1159, column: 25, scope: !2758)
!2758 = distinct !DILexicalBlock(scope: !2754, file: !1, line: 1158, column: 18)
!2759 = !DILocation(line: 1159, column: 28, scope: !2758)
!2760 = !DILocation(line: 1159, column: 6, scope: !2758)
!2761 = !DILocation(line: 1162, column: 6, scope: !2758)
!2762 = !DILocation(line: 1164, column: 5, scope: !2748)
!2763 = !DILocation(line: 1166, column: 4, scope: !2748)
!2764 = !DILocation(line: 1167, column: 33, scope: !2708)
!2765 = !DILocation(line: 1167, column: 36, scope: !2708)
!2766 = !DILocation(line: 1167, column: 41, scope: !2708)
!2767 = !DILocation(line: 1167, column: 46, scope: !2708)
!2768 = !DILocation(line: 1167, column: 10, scope: !2708)
!2769 = !DILocation(line: 1167, column: 8, scope: !2708)
!2770 = !DILocation(line: 1168, column: 8, scope: !2771)
!2771 = distinct !DILexicalBlock(scope: !2708, file: !1, line: 1168, column: 8)
!2772 = !DILocation(line: 1168, column: 12, scope: !2771)
!2773 = !DILocation(line: 1168, column: 8, scope: !2708)
!2774 = !DILocation(line: 1169, column: 13, scope: !2771)
!2775 = !DILocation(line: 1169, column: 5, scope: !2771)
!2776 = !DILocation(line: 1170, column: 37, scope: !2708)
!2777 = !DILocation(line: 1170, column: 4, scope: !2708)
!2778 = !DILocation(line: 1170, column: 9, scope: !2708)
!2779 = !DILocation(line: 1170, column: 34, scope: !2708)
!2780 = !DILocation(line: 1171, column: 26, scope: !2708)
!2781 = !DILocation(line: 1171, column: 4, scope: !2708)
!2782 = !DILocation(line: 1171, column: 9, scope: !2708)
!2783 = !DILocation(line: 1171, column: 23, scope: !2708)
!2784 = !DILocation(line: 1172, column: 27, scope: !2708)
!2785 = !DILocation(line: 1172, column: 32, scope: !2708)
!2786 = !DILocation(line: 1172, column: 4, scope: !2708)
!2787 = !DILocation(line: 1172, column: 9, scope: !2708)
!2788 = !DILocation(line: 1172, column: 16, scope: !2708)
!2789 = !DILocation(line: 1172, column: 25, scope: !2708)
!2790 = !DILocation(line: 1173, column: 8, scope: !2791)
!2791 = distinct !DILexicalBlock(scope: !2708, file: !1, line: 1173, column: 8)
!2792 = !DILocation(line: 1173, column: 13, scope: !2791)
!2793 = !DILocation(line: 1173, column: 20, scope: !2791)
!2794 = !DILocation(line: 1173, column: 30, scope: !2791)
!2795 = !DILocation(line: 1173, column: 8, scope: !2708)
!2796 = !DILocation(line: 1174, column: 5, scope: !2791)
!2797 = !DILocation(line: 1175, column: 34, scope: !2708)
!2798 = !DILocation(line: 1175, column: 39, scope: !2708)
!2799 = !DILocation(line: 1175, column: 28, scope: !2708)
!2800 = !DILocation(line: 1175, column: 4, scope: !2708)
!2801 = !DILocation(line: 1175, column: 9, scope: !2708)
!2802 = !DILocation(line: 1175, column: 16, scope: !2708)
!2803 = !DILocation(line: 1175, column: 26, scope: !2708)
!2804 = !DILocation(line: 1143, column: 3, scope: !2805)
!2805 = !DILexicalBlockFile(scope: !2709, file: !1, discriminator: 1)
!2806 = !DILocation(line: 1177, column: 15, scope: !2706)
!2807 = !DILocation(line: 1177, column: 20, scope: !2706)
!2808 = !DILocation(line: 1177, column: 3, scope: !2706)
!2809 = !DILocation(line: 1178, column: 2, scope: !2706)
!2810 = !DILocation(line: 1180, column: 6, scope: !2811)
!2811 = distinct !DILexicalBlock(scope: !718, file: !1, line: 1180, column: 6)
!2812 = !DILocation(line: 1180, column: 11, scope: !2811)
!2813 = !DILocation(line: 1180, column: 6, scope: !718)
!2814 = !DILocalVariable(name: "hmac", scope: !2815, file: !1, line: 1181, type: !2816)
!2815 = distinct !DILexicalBlock(scope: !2811, file: !1, line: 1180, column: 23)
!2816 = !DICompositeType(tag: DW_TAG_array_type, baseType: !648, size: 160, align: 8, elements: !2817)
!2817 = !{!2818}
!2818 = !DISubrange(count: 20)
!2819 = !DILocation(line: 1181, column: 11, scope: !2815)
!2820 = !DILocalVariable(name: "hmac_len", scope: !2815, file: !1, line: 1182, type: !394)
!2821 = !DILocation(line: 1182, column: 10, scope: !2815)
!2822 = !DILocation(line: 1184, column: 3, scope: !2815)
!2823 = !DILocation(line: 1185, column: 32, scope: !2815)
!2824 = !DILocation(line: 1185, column: 35, scope: !2815)
!2825 = !DILocation(line: 1185, column: 9, scope: !2815)
!2826 = !DILocation(line: 1185, column: 7, scope: !2815)
!2827 = !DILocation(line: 1186, column: 7, scope: !2828)
!2828 = distinct !DILexicalBlock(scope: !2815, file: !1, line: 1186, column: 7)
!2829 = !DILocation(line: 1186, column: 11, scope: !2828)
!2830 = !DILocation(line: 1186, column: 7, scope: !2815)
!2831 = !DILocation(line: 1187, column: 12, scope: !2828)
!2832 = !DILocation(line: 1187, column: 4, scope: !2828)
!2833 = !DILocation(line: 1188, column: 3, scope: !2815)
!2834 = !DILocation(line: 1188, column: 8, scope: !2815)
!2835 = !DILocation(line: 1188, column: 33, scope: !2815)
!2836 = !DILocation(line: 1189, column: 3, scope: !2815)
!2837 = !DILocation(line: 1189, column: 8, scope: !2815)
!2838 = !DILocation(line: 1189, column: 22, scope: !2815)
!2839 = !DILocation(line: 1190, column: 2, scope: !2815)
!2840 = !DILocation(line: 1193, column: 7, scope: !2841)
!2841 = distinct !DILexicalBlock(scope: !718, file: !1, line: 1193, column: 6)
!2842 = !DILocation(line: 1193, column: 12, scope: !2841)
!2843 = !DILocation(line: 1193, column: 24, scope: !2841)
!2844 = !DILocation(line: 1193, column: 56, scope: !2841)
!2845 = !DILocation(line: 1193, column: 6, scope: !718)
!2846 = !DILocalVariable(name: "d", scope: !2847, file: !1, line: 1194, type: !2848)
!2847 = distinct !DILexicalBlock(scope: !2841, file: !1, line: 1193, column: 62)
!2848 = !DICompositeType(tag: DW_TAG_array_type, baseType: !431, size: 192, align: 8, elements: !2849)
!2849 = !{!2850}
!2850 = !DISubrange(count: 24)
!2851 = !DILocation(line: 1194, column: 8, scope: !2847)
!2852 = !DILocation(line: 1195, column: 3, scope: !2847)
!2853 = !DILocation(line: 1196, column: 7, scope: !2854)
!2854 = distinct !DILexicalBlock(scope: !2847, file: !1, line: 1196, column: 7)
!2855 = !DILocation(line: 1196, column: 12, scope: !2854)
!2856 = !DILocation(line: 1196, column: 23, scope: !2854)
!2857 = !DILocation(line: 1196, column: 26, scope: !2858)
!2858 = !DILexicalBlockFile(scope: !2854, file: !1, discriminator: 1)
!2859 = !DILocation(line: 1196, column: 31, scope: !2858)
!2860 = !DILocation(line: 1196, column: 42, scope: !2858)
!2861 = !DILocation(line: 1196, column: 7, scope: !2858)
!2862 = !DILocation(line: 1197, column: 20, scope: !2854)
!2863 = !DILocation(line: 1197, column: 22, scope: !2854)
!2864 = !DILocation(line: 1197, column: 4, scope: !2854)
!2865 = !DILocation(line: 1199, column: 20, scope: !2854)
!2866 = !DILocation(line: 1199, column: 22, scope: !2854)
!2867 = !DILocation(line: 1199, column: 27, scope: !2854)
!2868 = !DILocation(line: 1199, column: 32, scope: !2854)
!2869 = !DILocation(line: 1199, column: 4, scope: !2854)
!2870 = !DILocation(line: 1200, column: 7, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2847, file: !1, line: 1200, column: 7)
!2872 = !DILocation(line: 1200, column: 12, scope: !2871)
!2873 = !DILocation(line: 1200, column: 7, scope: !2847)
!2874 = !DILocation(line: 1201, column: 20, scope: !2875)
!2875 = distinct !DILexicalBlock(scope: !2871, file: !1, line: 1200, column: 30)
!2876 = !DILocation(line: 1201, column: 22, scope: !2875)
!2877 = !DILocation(line: 1202, column: 15, scope: !2875)
!2878 = !DILocation(line: 1202, column: 20, scope: !2875)
!2879 = !DILocation(line: 1201, column: 4, scope: !2875)
!2880 = !DILocation(line: 1203, column: 20, scope: !2875)
!2881 = !DILocation(line: 1203, column: 22, scope: !2875)
!2882 = !DILocation(line: 1204, column: 15, scope: !2875)
!2883 = !DILocation(line: 1204, column: 20, scope: !2875)
!2884 = !DILocation(line: 1203, column: 4, scope: !2875)
!2885 = !DILocation(line: 1205, column: 33, scope: !2875)
!2886 = !DILocation(line: 1205, column: 36, scope: !2875)
!2887 = !DILocation(line: 1205, column: 10, scope: !2875)
!2888 = !DILocation(line: 1205, column: 8, scope: !2875)
!2889 = !DILocation(line: 1206, column: 4, scope: !2875)
!2890 = !DILocation(line: 1206, column: 9, scope: !2875)
!2891 = !DILocation(line: 1206, column: 23, scope: !2875)
!2892 = !DILocation(line: 1207, column: 3, scope: !2875)
!2893 = !DILocation(line: 1208, column: 20, scope: !2894)
!2894 = distinct !DILexicalBlock(scope: !2871, file: !1, line: 1207, column: 10)
!2895 = !DILocation(line: 1208, column: 22, scope: !2894)
!2896 = !DILocation(line: 1209, column: 15, scope: !2894)
!2897 = !DILocation(line: 1209, column: 20, scope: !2894)
!2898 = !DILocation(line: 1209, column: 5, scope: !2894)
!2899 = !DILocation(line: 1208, column: 4, scope: !2894)
!2900 = !DILocation(line: 1210, column: 20, scope: !2894)
!2901 = !DILocation(line: 1210, column: 22, scope: !2894)
!2902 = !DILocation(line: 1211, column: 15, scope: !2894)
!2903 = !DILocation(line: 1211, column: 20, scope: !2894)
!2904 = !DILocation(line: 1211, column: 5, scope: !2894)
!2905 = !DILocation(line: 1210, column: 4, scope: !2894)
!2906 = !DILocation(line: 1212, column: 33, scope: !2894)
!2907 = !DILocation(line: 1212, column: 36, scope: !2894)
!2908 = !DILocation(line: 1212, column: 10, scope: !2894)
!2909 = !DILocation(line: 1212, column: 8, scope: !2894)
!2910 = !DILocation(line: 1213, column: 4, scope: !2894)
!2911 = !DILocation(line: 1213, column: 9, scope: !2894)
!2912 = !DILocation(line: 1213, column: 23, scope: !2894)
!2913 = !DILocation(line: 1215, column: 7, scope: !2914)
!2914 = distinct !DILexicalBlock(scope: !2847, file: !1, line: 1215, column: 7)
!2915 = !DILocation(line: 1215, column: 11, scope: !2914)
!2916 = !DILocation(line: 1215, column: 7, scope: !2847)
!2917 = !DILocation(line: 1216, column: 4, scope: !2914)
!2918 = !DILocation(line: 1217, column: 2, scope: !2847)
!2919 = !DILocation(line: 1220, column: 6, scope: !2920)
!2920 = distinct !DILexicalBlock(scope: !718, file: !1, line: 1220, column: 6)
!2921 = !DILocation(line: 1220, column: 11, scope: !2920)
!2922 = !DILocation(line: 1220, column: 36, scope: !2920)
!2923 = !DILocation(line: 1221, column: 6, scope: !2920)
!2924 = !DILocation(line: 1221, column: 9, scope: !2925)
!2925 = !DILexicalBlockFile(scope: !2920, file: !1, discriminator: 1)
!2926 = !DILocation(line: 1221, column: 14, scope: !2925)
!2927 = !DILocation(line: 1221, column: 41, scope: !2925)
!2928 = !DILocation(line: 1222, column: 6, scope: !2920)
!2929 = !DILocation(line: 1222, column: 9, scope: !2925)
!2930 = !DILocation(line: 1222, column: 14, scope: !2925)
!2931 = !DILocation(line: 1222, column: 27, scope: !2925)
!2932 = !DILocation(line: 1220, column: 6, scope: !2933)
!2933 = !DILexicalBlockFile(scope: !718, file: !1, discriminator: 1)
!2934 = !DILocalVariable(name: "zip64", scope: !2935, file: !1, line: 1223, type: !1255)
!2935 = distinct !DILexicalBlock(scope: !2920, file: !1, line: 1222, column: 42)
!2936 = !DILocation(line: 1223, column: 17, scope: !2935)
!2937 = !DILocalVariable(name: "z", scope: !2935, file: !1, line: 1224, type: !577)
!2938 = !DILocation(line: 1224, column: 18, scope: !2935)
!2939 = !DILocation(line: 1224, column: 22, scope: !2935)
!2940 = !DILocalVariable(name: "zd", scope: !2935, file: !1, line: 1224, type: !577)
!2941 = !DILocation(line: 1224, column: 30, scope: !2935)
!2942 = !DILocation(line: 1225, column: 10, scope: !2935)
!2943 = !DILocation(line: 1225, column: 3, scope: !2935)
!2944 = !DILocation(line: 1226, column: 5, scope: !2935)
!2945 = !DILocation(line: 1227, column: 7, scope: !2946)
!2946 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 1227, column: 7)
!2947 = !DILocation(line: 1227, column: 12, scope: !2946)
!2948 = !DILocation(line: 1227, column: 39, scope: !2946)
!2949 = !DILocation(line: 1227, column: 7, scope: !2935)
!2950 = !DILocation(line: 1228, column: 20, scope: !2951)
!2951 = distinct !DILexicalBlock(scope: !2946, file: !1, line: 1227, column: 55)
!2952 = !DILocation(line: 1228, column: 23, scope: !2951)
!2953 = !DILocation(line: 1228, column: 28, scope: !2951)
!2954 = !DILocation(line: 1228, column: 4, scope: !2951)
!2955 = !DILocation(line: 1229, column: 6, scope: !2951)
!2956 = !DILocation(line: 1230, column: 3, scope: !2951)
!2957 = !DILocation(line: 1231, column: 7, scope: !2958)
!2958 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 1231, column: 7)
!2959 = !DILocation(line: 1231, column: 12, scope: !2958)
!2960 = !DILocation(line: 1231, column: 37, scope: !2958)
!2961 = !DILocation(line: 1231, column: 7, scope: !2935)
!2962 = !DILocation(line: 1232, column: 20, scope: !2963)
!2963 = distinct !DILexicalBlock(scope: !2958, file: !1, line: 1231, column: 53)
!2964 = !DILocation(line: 1232, column: 23, scope: !2963)
!2965 = !DILocation(line: 1232, column: 28, scope: !2963)
!2966 = !DILocation(line: 1232, column: 4, scope: !2963)
!2967 = !DILocation(line: 1233, column: 6, scope: !2963)
!2968 = !DILocation(line: 1234, column: 3, scope: !2963)
!2969 = !DILocation(line: 1235, column: 7, scope: !2970)
!2970 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 1235, column: 7)
!2971 = !DILocation(line: 1235, column: 12, scope: !2970)
!2972 = !DILocation(line: 1235, column: 25, scope: !2970)
!2973 = !DILocation(line: 1235, column: 7, scope: !2935)
!2974 = !DILocation(line: 1236, column: 20, scope: !2975)
!2975 = distinct !DILexicalBlock(scope: !2970, file: !1, line: 1235, column: 41)
!2976 = !DILocation(line: 1236, column: 23, scope: !2975)
!2977 = !DILocation(line: 1236, column: 28, scope: !2975)
!2978 = !DILocation(line: 1236, column: 4, scope: !2975)
!2979 = !DILocation(line: 1237, column: 6, scope: !2975)
!2980 = !DILocation(line: 1238, column: 3, scope: !2975)
!2981 = !DILocation(line: 1239, column: 19, scope: !2935)
!2982 = !DILocation(line: 1239, column: 25, scope: !2935)
!2983 = !DILocation(line: 1239, column: 41, scope: !2935)
!2984 = !DILocation(line: 1239, column: 46, scope: !2935)
!2985 = !DILocation(line: 1239, column: 52, scope: !2935)
!2986 = !DILocation(line: 1239, column: 43, scope: !2935)
!2987 = !DILocation(line: 1239, column: 30, scope: !2935)
!2988 = !DILocation(line: 1239, column: 3, scope: !2935)
!2989 = !DILocation(line: 1240, column: 17, scope: !2935)
!2990 = !DILocation(line: 1240, column: 22, scope: !2935)
!2991 = !DILocation(line: 1240, column: 26, scope: !2935)
!2992 = !DILocation(line: 1240, column: 24, scope: !2935)
!2993 = !DILocation(line: 1240, column: 8, scope: !2935)
!2994 = !DILocation(line: 1240, column: 6, scope: !2935)
!2995 = !DILocation(line: 1241, column: 7, scope: !2996)
!2996 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 1241, column: 7)
!2997 = !DILocation(line: 1241, column: 10, scope: !2996)
!2998 = !DILocation(line: 1241, column: 7, scope: !2935)
!2999 = !DILocation(line: 1242, column: 23, scope: !3000)
!3000 = distinct !DILexicalBlock(scope: !2996, file: !1, line: 1241, column: 19)
!3001 = !DILocation(line: 1242, column: 26, scope: !3000)
!3002 = !DILocation(line: 1242, column: 4, scope: !3000)
!3003 = !DILocation(line: 1244, column: 4, scope: !3000)
!3004 = !DILocation(line: 1246, column: 10, scope: !2935)
!3005 = !DILocation(line: 1246, column: 3, scope: !2935)
!3006 = !DILocation(line: 1246, column: 21, scope: !2935)
!3007 = !DILocation(line: 1246, column: 25, scope: !2935)
!3008 = !DILocation(line: 1246, column: 23, scope: !2935)
!3009 = !DILocation(line: 1248, column: 23, scope: !3010)
!3010 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 1248, column: 7)
!3011 = !DILocation(line: 1248, column: 28, scope: !3010)
!3012 = !DILocation(line: 1248, column: 40, scope: !3010)
!3013 = !DILocation(line: 1248, column: 7, scope: !3010)
!3014 = !DILocation(line: 1248, column: 45, scope: !3010)
!3015 = !DILocation(line: 1248, column: 7, scope: !2935)
!3016 = !DILocation(line: 1249, column: 20, scope: !3010)
!3017 = !DILocation(line: 1249, column: 25, scope: !3010)
!3018 = !DILocation(line: 1249, column: 37, scope: !3010)
!3019 = !DILocation(line: 1249, column: 4, scope: !3010)
!3020 = !DILocation(line: 1250, column: 2, scope: !2935)
!3021 = !DILocation(line: 1253, column: 6, scope: !3022)
!3022 = distinct !DILexicalBlock(scope: !718, file: !1, line: 1253, column: 6)
!3023 = !DILocation(line: 1253, column: 11, scope: !3022)
!3024 = !DILocation(line: 1253, column: 22, scope: !3022)
!3025 = !DILocation(line: 1253, column: 25, scope: !3026)
!3026 = !DILexicalBlockFile(scope: !3022, file: !1, discriminator: 1)
!3027 = !DILocation(line: 1253, column: 30, scope: !3026)
!3028 = !DILocation(line: 1253, column: 41, scope: !3026)
!3029 = !DILocation(line: 1253, column: 6, scope: !3026)
!3030 = !DILocation(line: 1254, column: 19, scope: !3022)
!3031 = !DILocation(line: 1254, column: 24, scope: !3022)
!3032 = !DILocation(line: 1254, column: 36, scope: !3022)
!3033 = !DILocation(line: 1254, column: 3, scope: !3022)
!3034 = !DILocation(line: 1256, column: 19, scope: !3022)
!3035 = !DILocation(line: 1256, column: 24, scope: !3022)
!3036 = !DILocation(line: 1256, column: 36, scope: !3022)
!3037 = !DILocation(line: 1256, column: 42, scope: !3022)
!3038 = !DILocation(line: 1256, column: 47, scope: !3022)
!3039 = !DILocation(line: 1256, column: 3, scope: !3022)
!3040 = !DILocation(line: 1257, column: 18, scope: !718)
!3041 = !DILocation(line: 1257, column: 23, scope: !718)
!3042 = !DILocation(line: 1257, column: 35, scope: !718)
!3043 = !DILocation(line: 1258, column: 13, scope: !718)
!3044 = !DILocation(line: 1258, column: 13, scope: !2933)
!3045 = !DILocation(line: 1258, column: 13, scope: !3046)
!3046 = !DILexicalBlockFile(scope: !718, file: !1, discriminator: 2)
!3047 = !DILocation(line: 1258, column: 13, scope: !3048)
!3048 = !DILexicalBlockFile(scope: !718, file: !1, discriminator: 3)
!3049 = !DILocation(line: 1258, column: 3, scope: !3048)
!3050 = !DILocation(line: 1257, column: 2, scope: !2933)
!3051 = !DILocation(line: 1260, column: 18, scope: !718)
!3052 = !DILocation(line: 1260, column: 23, scope: !718)
!3053 = !DILocation(line: 1260, column: 35, scope: !718)
!3054 = !DILocation(line: 1261, column: 13, scope: !718)
!3055 = !DILocation(line: 1261, column: 13, scope: !2933)
!3056 = !DILocation(line: 1261, column: 13, scope: !3046)
!3057 = !DILocation(line: 1261, column: 13, scope: !3048)
!3058 = !DILocation(line: 1261, column: 3, scope: !3048)
!3059 = !DILocation(line: 1260, column: 2, scope: !2933)
!3060 = !DILocation(line: 1263, column: 18, scope: !718)
!3061 = !DILocation(line: 1263, column: 23, scope: !718)
!3062 = !DILocation(line: 1263, column: 35, scope: !718)
!3063 = !DILocation(line: 1264, column: 17, scope: !718)
!3064 = !DILocation(line: 1264, column: 22, scope: !718)
!3065 = !DILocation(line: 1264, column: 48, scope: !718)
!3066 = !DILocation(line: 1264, column: 53, scope: !718)
!3067 = !DILocation(line: 1264, column: 46, scope: !718)
!3068 = !DILocation(line: 1264, column: 6, scope: !718)
!3069 = !DILocation(line: 1263, column: 2, scope: !718)
!3070 = !DILocation(line: 1265, column: 18, scope: !718)
!3071 = !DILocation(line: 1265, column: 23, scope: !718)
!3072 = !DILocation(line: 1265, column: 35, scope: !718)
!3073 = !DILocation(line: 1266, column: 13, scope: !718)
!3074 = !DILocation(line: 1266, column: 13, scope: !2933)
!3075 = !DILocation(line: 1266, column: 13, scope: !3046)
!3076 = !DILocation(line: 1266, column: 13, scope: !3048)
!3077 = !DILocation(line: 1266, column: 3, scope: !3048)
!3078 = !DILocation(line: 1265, column: 2, scope: !2933)
!3079 = !DILocation(line: 1269, column: 2, scope: !718)
!3080 = !DILocation(line: 1270, column: 1, scope: !718)
!3081 = !DILocalVariable(name: "a", arg: 1, scope: !722, file: !1, line: 1273, type: !353)
!3082 = !DILocation(line: 1273, column: 47, scope: !722)
!3083 = !DILocalVariable(name: "buff", scope: !722, file: !1, line: 1275, type: !3084)
!3084 = !DICompositeType(tag: DW_TAG_array_type, baseType: !648, size: 512, align: 8, elements: !3085)
!3085 = !{!3086}
!3086 = !DISubrange(count: 64)
!3087 = !DILocation(line: 1275, column: 10, scope: !722)
!3088 = !DILocalVariable(name: "offset_start", scope: !722, file: !1, line: 1276, type: !401)
!3089 = !DILocation(line: 1276, column: 10, scope: !722)
!3090 = !DILocalVariable(name: "offset_end", scope: !722, file: !1, line: 1276, type: !401)
!3091 = !DILocation(line: 1276, column: 24, scope: !722)
!3092 = !DILocalVariable(name: "zip", scope: !722, file: !1, line: 1277, type: !541)
!3093 = !DILocation(line: 1277, column: 14, scope: !722)
!3094 = !DILocation(line: 1277, column: 20, scope: !722)
!3095 = !DILocation(line: 1277, column: 23, scope: !722)
!3096 = !DILocalVariable(name: "segment", scope: !722, file: !1, line: 1278, type: !584)
!3097 = !DILocation(line: 1278, column: 21, scope: !722)
!3098 = !DILocalVariable(name: "ret", scope: !722, file: !1, line: 1279, type: !372)
!3099 = !DILocation(line: 1279, column: 6, scope: !722)
!3100 = !DILocation(line: 1281, column: 17, scope: !722)
!3101 = !DILocation(line: 1281, column: 22, scope: !722)
!3102 = !DILocation(line: 1281, column: 15, scope: !722)
!3103 = !DILocation(line: 1282, column: 12, scope: !722)
!3104 = !DILocation(line: 1282, column: 17, scope: !722)
!3105 = !DILocation(line: 1282, column: 10, scope: !722)
!3106 = !DILocation(line: 1283, column: 2, scope: !722)
!3107 = !DILocation(line: 1283, column: 9, scope: !3108)
!3108 = !DILexicalBlockFile(scope: !722, file: !1, discriminator: 1)
!3109 = !DILocation(line: 1283, column: 17, scope: !3108)
!3110 = !DILocation(line: 1283, column: 2, scope: !3108)
!3111 = !DILocation(line: 1284, column: 32, scope: !3112)
!3112 = distinct !DILexicalBlock(scope: !722, file: !1, line: 1283, column: 26)
!3113 = !DILocation(line: 1285, column: 7, scope: !3112)
!3114 = !DILocation(line: 1285, column: 16, scope: !3112)
!3115 = !DILocation(line: 1285, column: 22, scope: !3112)
!3116 = !DILocation(line: 1285, column: 31, scope: !3112)
!3117 = !DILocation(line: 1285, column: 35, scope: !3112)
!3118 = !DILocation(line: 1285, column: 44, scope: !3112)
!3119 = !DILocation(line: 1285, column: 33, scope: !3112)
!3120 = !DILocation(line: 1284, column: 9, scope: !3112)
!3121 = !DILocation(line: 1284, column: 7, scope: !3112)
!3122 = !DILocation(line: 1286, column: 7, scope: !3123)
!3123 = distinct !DILexicalBlock(scope: !3112, file: !1, line: 1286, column: 7)
!3124 = !DILocation(line: 1286, column: 11, scope: !3123)
!3125 = !DILocation(line: 1286, column: 7, scope: !3112)
!3126 = !DILocation(line: 1287, column: 4, scope: !3123)
!3127 = !DILocation(line: 1288, column: 25, scope: !3112)
!3128 = !DILocation(line: 1288, column: 34, scope: !3112)
!3129 = !DILocation(line: 1288, column: 38, scope: !3112)
!3130 = !DILocation(line: 1288, column: 47, scope: !3112)
!3131 = !DILocation(line: 1288, column: 36, scope: !3112)
!3132 = !DILocation(line: 1288, column: 3, scope: !3112)
!3133 = !DILocation(line: 1288, column: 8, scope: !3112)
!3134 = !DILocation(line: 1288, column: 22, scope: !3112)
!3135 = !DILocation(line: 1289, column: 13, scope: !3112)
!3136 = !DILocation(line: 1289, column: 22, scope: !3112)
!3137 = !DILocation(line: 1289, column: 11, scope: !3112)
!3138 = !DILocation(line: 1283, column: 2, scope: !3139)
!3139 = !DILexicalBlockFile(scope: !722, file: !1, discriminator: 2)
!3140 = !DILocation(line: 1291, column: 15, scope: !722)
!3141 = !DILocation(line: 1291, column: 20, scope: !722)
!3142 = !DILocation(line: 1291, column: 13, scope: !722)
!3143 = !DILocation(line: 1294, column: 6, scope: !3144)
!3144 = distinct !DILexicalBlock(scope: !722, file: !1, line: 1294, column: 6)
!3145 = !DILocation(line: 1294, column: 19, scope: !3144)
!3146 = !DILocation(line: 1294, column: 17, scope: !3144)
!3147 = !DILocation(line: 1294, column: 32, scope: !3144)
!3148 = !DILocation(line: 1295, column: 6, scope: !3144)
!3149 = !DILocation(line: 1295, column: 9, scope: !3150)
!3150 = !DILexicalBlockFile(scope: !3144, file: !1, discriminator: 1)
!3151 = !DILocation(line: 1295, column: 22, scope: !3150)
!3152 = !DILocation(line: 1296, column: 6, scope: !3144)
!3153 = !DILocation(line: 1296, column: 9, scope: !3150)
!3154 = !DILocation(line: 1296, column: 14, scope: !3150)
!3155 = !DILocation(line: 1296, column: 40, scope: !3150)
!3156 = !DILocation(line: 1297, column: 6, scope: !3144)
!3157 = !DILocation(line: 1297, column: 10, scope: !3150)
!3158 = !DILocation(line: 1297, column: 15, scope: !3150)
!3159 = !DILocation(line: 1297, column: 21, scope: !3150)
!3160 = !DILocation(line: 1294, column: 6, scope: !3108)
!3161 = !DILocation(line: 1299, column: 4, scope: !3162)
!3162 = distinct !DILexicalBlock(scope: !3144, file: !1, line: 1297, column: 46)
!3163 = !DILocation(line: 1300, column: 4, scope: !3162)
!3164 = !DILocation(line: 1301, column: 20, scope: !3162)
!3165 = !DILocation(line: 1301, column: 25, scope: !3162)
!3166 = !DILocation(line: 1301, column: 4, scope: !3162)
!3167 = !DILocation(line: 1302, column: 20, scope: !3162)
!3168 = !DILocation(line: 1302, column: 25, scope: !3162)
!3169 = !DILocation(line: 1302, column: 4, scope: !3162)
!3170 = !DILocation(line: 1303, column: 20, scope: !3162)
!3171 = !DILocation(line: 1303, column: 25, scope: !3162)
!3172 = !DILocation(line: 1303, column: 4, scope: !3162)
!3173 = !DILocation(line: 1305, column: 20, scope: !3162)
!3174 = !DILocation(line: 1305, column: 25, scope: !3162)
!3175 = !DILocation(line: 1305, column: 31, scope: !3162)
!3176 = !DILocation(line: 1305, column: 36, scope: !3162)
!3177 = !DILocation(line: 1305, column: 4, scope: !3162)
!3178 = !DILocation(line: 1306, column: 20, scope: !3162)
!3179 = !DILocation(line: 1306, column: 25, scope: !3162)
!3180 = !DILocation(line: 1306, column: 31, scope: !3162)
!3181 = !DILocation(line: 1306, column: 36, scope: !3162)
!3182 = !DILocation(line: 1306, column: 4, scope: !3162)
!3183 = !DILocation(line: 1307, column: 20, scope: !3162)
!3184 = !DILocation(line: 1307, column: 25, scope: !3162)
!3185 = !DILocation(line: 1307, column: 31, scope: !3162)
!3186 = !DILocation(line: 1307, column: 44, scope: !3162)
!3187 = !DILocation(line: 1307, column: 42, scope: !3162)
!3188 = !DILocation(line: 1307, column: 4, scope: !3162)
!3189 = !DILocation(line: 1308, column: 20, scope: !3162)
!3190 = !DILocation(line: 1308, column: 25, scope: !3162)
!3191 = !DILocation(line: 1308, column: 31, scope: !3162)
!3192 = !DILocation(line: 1308, column: 4, scope: !3162)
!3193 = !DILocation(line: 1309, column: 33, scope: !3162)
!3194 = !DILocation(line: 1309, column: 36, scope: !3162)
!3195 = !DILocation(line: 1309, column: 10, scope: !3162)
!3196 = !DILocation(line: 1309, column: 8, scope: !3162)
!3197 = !DILocation(line: 1310, column: 8, scope: !3198)
!3198 = distinct !DILexicalBlock(scope: !3162, file: !1, line: 1310, column: 8)
!3199 = !DILocation(line: 1310, column: 12, scope: !3198)
!3200 = !DILocation(line: 1310, column: 8, scope: !3162)
!3201 = !DILocation(line: 1311, column: 5, scope: !3198)
!3202 = !DILocation(line: 1312, column: 4, scope: !3162)
!3203 = !DILocation(line: 1312, column: 9, scope: !3162)
!3204 = !DILocation(line: 1312, column: 23, scope: !3162)
!3205 = !DILocation(line: 1315, column: 4, scope: !3162)
!3206 = !DILocation(line: 1316, column: 4, scope: !3162)
!3207 = !DILocation(line: 1317, column: 20, scope: !3162)
!3208 = !DILocation(line: 1317, column: 25, scope: !3162)
!3209 = !DILocation(line: 1317, column: 4, scope: !3162)
!3210 = !DILocation(line: 1318, column: 20, scope: !3162)
!3211 = !DILocation(line: 1318, column: 25, scope: !3162)
!3212 = !DILocation(line: 1318, column: 30, scope: !3162)
!3213 = !DILocation(line: 1318, column: 4, scope: !3162)
!3214 = !DILocation(line: 1319, column: 20, scope: !3162)
!3215 = !DILocation(line: 1319, column: 25, scope: !3162)
!3216 = !DILocation(line: 1319, column: 4, scope: !3162)
!3217 = !DILocation(line: 1320, column: 33, scope: !3162)
!3218 = !DILocation(line: 1320, column: 36, scope: !3162)
!3219 = !DILocation(line: 1320, column: 10, scope: !3162)
!3220 = !DILocation(line: 1320, column: 8, scope: !3162)
!3221 = !DILocation(line: 1321, column: 8, scope: !3222)
!3222 = distinct !DILexicalBlock(scope: !3162, file: !1, line: 1321, column: 8)
!3223 = !DILocation(line: 1321, column: 12, scope: !3222)
!3224 = !DILocation(line: 1321, column: 8, scope: !3162)
!3225 = !DILocation(line: 1322, column: 5, scope: !3222)
!3226 = !DILocation(line: 1323, column: 4, scope: !3162)
!3227 = !DILocation(line: 1323, column: 9, scope: !3162)
!3228 = !DILocation(line: 1323, column: 23, scope: !3162)
!3229 = !DILocation(line: 1325, column: 2, scope: !3162)
!3230 = !DILocation(line: 1328, column: 2, scope: !722)
!3231 = !DILocation(line: 1329, column: 2, scope: !722)
!3232 = !DILocation(line: 1330, column: 18, scope: !722)
!3233 = !DILocation(line: 1330, column: 23, scope: !722)
!3234 = !DILocation(line: 1330, column: 38, scope: !722)
!3235 = !DILocation(line: 1330, column: 38, scope: !3108)
!3236 = !DILocation(line: 1330, column: 38, scope: !3139)
!3237 = !DILocation(line: 1330, column: 38, scope: !3238)
!3238 = !DILexicalBlockFile(scope: !722, file: !1, discriminator: 3)
!3239 = !DILocation(line: 1330, column: 28, scope: !3238)
!3240 = !DILocation(line: 1330, column: 2, scope: !3238)
!3241 = !DILocation(line: 1332, column: 18, scope: !722)
!3242 = !DILocation(line: 1332, column: 23, scope: !722)
!3243 = !DILocation(line: 1332, column: 39, scope: !722)
!3244 = !DILocation(line: 1332, column: 39, scope: !3108)
!3245 = !DILocation(line: 1332, column: 39, scope: !3139)
!3246 = !DILocation(line: 1332, column: 39, scope: !3238)
!3247 = !DILocation(line: 1332, column: 29, scope: !3238)
!3248 = !DILocation(line: 1332, column: 2, scope: !3238)
!3249 = !DILocation(line: 1334, column: 18, scope: !722)
!3250 = !DILocation(line: 1334, column: 23, scope: !722)
!3251 = !DILocation(line: 1335, column: 13, scope: !722)
!3252 = !DILocation(line: 1335, column: 13, scope: !3108)
!3253 = !DILocation(line: 1335, column: 13, scope: !3139)
!3254 = !DILocation(line: 1335, column: 13, scope: !3238)
!3255 = !DILocation(line: 1335, column: 3, scope: !3238)
!3256 = !DILocation(line: 1334, column: 2, scope: !3108)
!3257 = !DILocation(line: 1336, column: 18, scope: !722)
!3258 = !DILocation(line: 1336, column: 23, scope: !722)
!3259 = !DILocation(line: 1337, column: 13, scope: !722)
!3260 = !DILocation(line: 1337, column: 13, scope: !3108)
!3261 = !DILocation(line: 1337, column: 13, scope: !3139)
!3262 = !DILocation(line: 1337, column: 13, scope: !3238)
!3263 = !DILocation(line: 1337, column: 3, scope: !3238)
!3264 = !DILocation(line: 1336, column: 2, scope: !3108)
!3265 = !DILocation(line: 1338, column: 31, scope: !722)
!3266 = !DILocation(line: 1338, column: 34, scope: !722)
!3267 = !DILocation(line: 1338, column: 8, scope: !722)
!3268 = !DILocation(line: 1338, column: 6, scope: !722)
!3269 = !DILocation(line: 1339, column: 6, scope: !3270)
!3270 = distinct !DILexicalBlock(scope: !722, file: !1, line: 1339, column: 6)
!3271 = !DILocation(line: 1339, column: 10, scope: !3270)
!3272 = !DILocation(line: 1339, column: 6, scope: !722)
!3273 = !DILocation(line: 1340, column: 3, scope: !3270)
!3274 = !DILocation(line: 1341, column: 2, scope: !722)
!3275 = !DILocation(line: 1341, column: 7, scope: !722)
!3276 = !DILocation(line: 1341, column: 21, scope: !722)
!3277 = !DILocation(line: 1342, column: 2, scope: !722)
!3278 = !DILocation(line: 1343, column: 1, scope: !722)
!3279 = !DILocalVariable(name: "a", arg: 1, scope: !723, file: !1, line: 1346, type: !353)
!3280 = !DILocation(line: 1346, column: 46, scope: !723)
!3281 = !DILocalVariable(name: "zip", scope: !723, file: !1, line: 1348, type: !541)
!3282 = !DILocation(line: 1348, column: 14, scope: !723)
!3283 = !DILocalVariable(name: "segment", scope: !723, file: !1, line: 1349, type: !584)
!3284 = !DILocation(line: 1349, column: 21, scope: !723)
!3285 = !DILocation(line: 1351, column: 8, scope: !723)
!3286 = !DILocation(line: 1351, column: 11, scope: !723)
!3287 = !DILocation(line: 1351, column: 6, scope: !723)
!3288 = !DILocation(line: 1352, column: 2, scope: !723)
!3289 = !DILocation(line: 1352, column: 9, scope: !3290)
!3290 = !DILexicalBlockFile(scope: !723, file: !1, discriminator: 1)
!3291 = !DILocation(line: 1352, column: 14, scope: !3290)
!3292 = !DILocation(line: 1352, column: 32, scope: !3290)
!3293 = !DILocation(line: 1352, column: 2, scope: !3290)
!3294 = !DILocation(line: 1353, column: 13, scope: !3295)
!3295 = distinct !DILexicalBlock(scope: !723, file: !1, line: 1352, column: 41)
!3296 = !DILocation(line: 1353, column: 18, scope: !3295)
!3297 = !DILocation(line: 1353, column: 11, scope: !3295)
!3298 = !DILocation(line: 1354, column: 28, scope: !3295)
!3299 = !DILocation(line: 1354, column: 37, scope: !3295)
!3300 = !DILocation(line: 1354, column: 3, scope: !3295)
!3301 = !DILocation(line: 1354, column: 8, scope: !3295)
!3302 = !DILocation(line: 1354, column: 26, scope: !3295)
!3303 = !DILocation(line: 1355, column: 8, scope: !3295)
!3304 = !DILocation(line: 1355, column: 17, scope: !3295)
!3305 = !DILocation(line: 1355, column: 3, scope: !3295)
!3306 = !DILocation(line: 1356, column: 8, scope: !3295)
!3307 = !DILocation(line: 1356, column: 3, scope: !3295)
!3308 = !DILocation(line: 1352, column: 2, scope: !3309)
!3309 = !DILexicalBlockFile(scope: !723, file: !1, discriminator: 2)
!3310 = !DILocation(line: 1358, column: 7, scope: !723)
!3311 = !DILocation(line: 1358, column: 12, scope: !723)
!3312 = !DILocation(line: 1358, column: 2, scope: !723)
!3313 = !DILocation(line: 1359, column: 21, scope: !723)
!3314 = !DILocation(line: 1359, column: 26, scope: !723)
!3315 = !DILocation(line: 1359, column: 2, scope: !723)
!3316 = !DILocation(line: 1360, column: 6, scope: !3317)
!3317 = distinct !DILexicalBlock(scope: !723, file: !1, line: 1360, column: 6)
!3318 = !DILocation(line: 1360, column: 11, scope: !3317)
!3319 = !DILocation(line: 1360, column: 6, scope: !723)
!3320 = !DILocation(line: 1361, column: 3, scope: !3317)
!3321 = !DILocation(line: 1362, column: 6, scope: !3322)
!3322 = distinct !DILexicalBlock(scope: !723, file: !1, line: 1362, column: 6)
!3323 = !DILocation(line: 1362, column: 11, scope: !3322)
!3324 = !DILocation(line: 1362, column: 6, scope: !723)
!3325 = !DILocation(line: 1363, column: 3, scope: !3322)
!3326 = !DILocation(line: 1366, column: 7, scope: !723)
!3327 = !DILocation(line: 1366, column: 2, scope: !723)
!3328 = !DILocation(line: 1367, column: 2, scope: !723)
!3329 = !DILocation(line: 1367, column: 5, scope: !723)
!3330 = !DILocation(line: 1367, column: 17, scope: !723)
!3331 = !DILocation(line: 1368, column: 2, scope: !723)
!3332 = !DILocalVariable(name: "key", scope: !658, file: !1, line: 1540, type: !3333)
!3333 = !DICompositeType(tag: DW_TAG_array_type, baseType: !648, size: 96, align: 8, elements: !3334)
!3334 = !{!3335}
!3335 = !DISubrange(count: 12)
!3336 = !DILocation(line: 1540, column: 10, scope: !658)
!3337 = !DILocation(line: 1542, column: 21, scope: !3338)
!3338 = distinct !DILexicalBlock(scope: !658, file: !1, line: 1542, column: 6)
!3339 = !DILocation(line: 1542, column: 6, scope: !3338)
!3340 = !DILocation(line: 1542, column: 41, scope: !3338)
!3341 = !DILocation(line: 1542, column: 6, scope: !658)
!3342 = !DILocation(line: 1543, column: 3, scope: !3338)
!3343 = !DILocation(line: 1544, column: 2, scope: !658)
!3344 = !DILocation(line: 1545, column: 1, scope: !658)
!3345 = !DILocalVariable(name: "encryption", arg: 1, scope: !661, file: !1, line: 1644, type: !372)
!3346 = !DILocation(line: 1644, column: 40, scope: !661)
!3347 = !DILocalVariable(name: "key_len", scope: !661, file: !1, line: 1646, type: !394)
!3348 = !DILocation(line: 1646, column: 9, scope: !661)
!3349 = !DILocalVariable(name: "salt_len", scope: !661, file: !1, line: 1646, type: !394)
!3350 = !DILocation(line: 1646, column: 18, scope: !661)
!3351 = !DILocalVariable(name: "salt", scope: !661, file: !1, line: 1647, type: !3352)
!3352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !648, size: 144, align: 8, elements: !3353)
!3353 = !{!3354}
!3354 = !DISubrange(count: 18)
!3355 = !DILocation(line: 1647, column: 10, scope: !661)
!3356 = !DILocalVariable(name: "derived_key", scope: !661, file: !1, line: 1648, type: !3357)
!3357 = !DICompositeType(tag: DW_TAG_array_type, baseType: !648, size: 528, align: 8, elements: !3358)
!3358 = !{!3359}
!3359 = !DISubrange(count: 66)
!3360 = !DILocation(line: 1648, column: 10, scope: !661)
!3361 = !DILocalVariable(name: "cctx", scope: !661, file: !1, line: 1649, type: !569)
!3362 = !DILocation(line: 1649, column: 21, scope: !661)
!3363 = !DILocalVariable(name: "hctx", scope: !661, file: !1, line: 1650, type: !573)
!3364 = !DILocation(line: 1650, column: 24, scope: !661)
!3365 = !DILocalVariable(name: "ret", scope: !661, file: !1, line: 1651, type: !372)
!3366 = !DILocation(line: 1651, column: 6, scope: !661)
!3367 = !DILocation(line: 1653, column: 6, scope: !3368)
!3368 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1653, column: 6)
!3369 = !DILocation(line: 1653, column: 17, scope: !3368)
!3370 = !DILocation(line: 1653, column: 6, scope: !661)
!3371 = !DILocation(line: 1654, column: 12, scope: !3372)
!3372 = distinct !DILexicalBlock(scope: !3368, file: !1, line: 1653, column: 46)
!3373 = !DILocation(line: 1655, column: 11, scope: !3372)
!3374 = !DILocation(line: 1656, column: 2, scope: !3372)
!3375 = !DILocation(line: 1658, column: 12, scope: !3376)
!3376 = distinct !DILexicalBlock(scope: !3368, file: !1, line: 1656, column: 9)
!3377 = !DILocation(line: 1659, column: 11, scope: !3376)
!3378 = !DILocation(line: 1661, column: 21, scope: !3379)
!3379 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1661, column: 6)
!3380 = !DILocation(line: 1661, column: 27, scope: !3379)
!3381 = !DILocation(line: 1661, column: 6, scope: !3379)
!3382 = !DILocation(line: 1661, column: 37, scope: !3379)
!3383 = !DILocation(line: 1661, column: 6, scope: !661)
!3384 = !DILocation(line: 1662, column: 3, scope: !3379)
!3385 = !DILocation(line: 1663, column: 8, scope: !661)
!3386 = !DILocation(line: 1663, column: 6, scope: !661)
!3387 = !DILocation(line: 1665, column: 6, scope: !3388)
!3388 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1665, column: 6)
!3389 = !DILocation(line: 1665, column: 10, scope: !3388)
!3390 = !DILocation(line: 1665, column: 6, scope: !661)
!3391 = !DILocation(line: 1666, column: 3, scope: !3388)
!3392 = !DILocation(line: 1668, column: 8, scope: !661)
!3393 = !DILocation(line: 1668, column: 6, scope: !661)
!3394 = !DILocation(line: 1669, column: 6, scope: !3395)
!3395 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1669, column: 6)
!3396 = !DILocation(line: 1669, column: 10, scope: !3395)
!3397 = !DILocation(line: 1669, column: 6, scope: !661)
!3398 = !DILocation(line: 1670, column: 3, scope: !3395)
!3399 = !DILocation(line: 1671, column: 8, scope: !661)
!3400 = !DILocation(line: 1671, column: 6, scope: !661)
!3401 = !DILocation(line: 1673, column: 2, scope: !661)
!3402 = !DILocation(line: 1674, column: 6, scope: !3403)
!3403 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1674, column: 6)
!3404 = !DILocation(line: 1674, column: 10, scope: !3403)
!3405 = !DILocation(line: 1674, column: 6, scope: !661)
!3406 = !DILocation(line: 1675, column: 3, scope: !3403)
!3407 = !DILocation(line: 1676, column: 2, scope: !661)
!3408 = !DILocation(line: 1677, column: 2, scope: !661)
!3409 = !DILocation(line: 1678, column: 1, scope: !661)
!3410 = !DILocalVariable(name: "crc", arg: 1, scope: !664, file: !1, line: 243, type: !396)
!3411 = !DILocation(line: 243, column: 26, scope: !664)
!3412 = !DILocalVariable(name: "buff", arg: 2, scope: !664, file: !1, line: 243, type: !392)
!3413 = !DILocation(line: 243, column: 43, scope: !664)
!3414 = !DILocalVariable(name: "len", arg: 3, scope: !664, file: !1, line: 243, type: !394)
!3415 = !DILocation(line: 243, column: 56, scope: !664)
!3416 = !DILocation(line: 245, column: 8, scope: !664)
!3417 = !DILocation(line: 246, column: 8, scope: !664)
!3418 = !DILocation(line: 247, column: 8, scope: !664)
!3419 = !DILocation(line: 248, column: 2, scope: !664)
!3420 = !DILocalVariable(name: "a", arg: 1, scope: !666, file: !1, line: 1471, type: !353)
!3421 = !DILocation(line: 1471, column: 33, scope: !666)
!3422 = !DILocalVariable(name: "zip", arg: 2, scope: !666, file: !1, line: 1471, type: !541)
!3423 = !DILocation(line: 1471, column: 48, scope: !666)
!3424 = !DILocation(line: 1473, column: 6, scope: !3425)
!3425 = distinct !DILexicalBlock(scope: !666, file: !1, line: 1473, column: 6)
!3426 = !DILocation(line: 1473, column: 11, scope: !3425)
!3427 = !DILocation(line: 1473, column: 21, scope: !3425)
!3428 = !DILocation(line: 1473, column: 6, scope: !666)
!3429 = !DILocation(line: 1474, column: 11, scope: !3425)
!3430 = !DILocation(line: 1474, column: 16, scope: !3425)
!3431 = !DILocation(line: 1474, column: 3, scope: !3425)
!3432 = !DILocation(line: 1476, column: 7, scope: !3433)
!3433 = distinct !DILexicalBlock(scope: !666, file: !1, line: 1476, column: 6)
!3434 = !DILocation(line: 1476, column: 12, scope: !3433)
!3435 = !DILocation(line: 1476, column: 6, scope: !666)
!3436 = !DILocation(line: 1478, column: 53, scope: !3437)
!3437 = distinct !DILexicalBlock(scope: !3433, file: !1, line: 1476, column: 37)
!3438 = !DILocation(line: 1478, column: 56, scope: !3437)
!3439 = !DILocation(line: 1478, column: 7, scope: !3437)
!3440 = !DILocation(line: 1477, column: 3, scope: !3437)
!3441 = !DILocation(line: 1477, column: 8, scope: !3437)
!3442 = !DILocation(line: 1477, column: 22, scope: !3437)
!3443 = !DILocation(line: 1479, column: 3, scope: !3437)
!3444 = !DILocation(line: 1479, column: 8, scope: !3437)
!3445 = !DILocation(line: 1479, column: 32, scope: !3437)
!3446 = !DILocation(line: 1480, column: 2, scope: !3437)
!3447 = !DILocation(line: 1481, column: 10, scope: !666)
!3448 = !DILocation(line: 1481, column: 15, scope: !666)
!3449 = !DILocation(line: 1481, column: 2, scope: !666)
!3450 = !DILocation(line: 1482, column: 1, scope: !666)
!3451 = !DILocalVariable(name: "p", arg: 1, scope: !669, file: !1, line: 499, type: !429)
!3452 = !DILocation(line: 499, column: 26, scope: !669)
!3453 = !DILocalVariable(name: "pp", scope: !669, file: !1, line: 501, type: !464)
!3454 = !DILocation(line: 501, column: 23, scope: !669)
!3455 = !DILocation(line: 501, column: 51, scope: !669)
!3456 = !DILocation(line: 503, column: 2, scope: !669)
!3457 = !DILocation(line: 503, column: 10, scope: !3458)
!3458 = !DILexicalBlockFile(scope: !669, file: !1, discriminator: 1)
!3459 = !DILocation(line: 503, column: 9, scope: !3458)
!3460 = !DILocation(line: 503, column: 2, scope: !3458)
!3461 = !DILocation(line: 504, column: 10, scope: !3462)
!3462 = distinct !DILexicalBlock(scope: !3463, file: !1, line: 504, column: 7)
!3463 = distinct !DILexicalBlock(scope: !669, file: !1, line: 503, column: 14)
!3464 = !DILocation(line: 504, column: 7, scope: !3462)
!3465 = !DILocation(line: 504, column: 13, scope: !3462)
!3466 = !DILocation(line: 504, column: 7, scope: !3463)
!3467 = !DILocation(line: 505, column: 4, scope: !3462)
!3468 = !DILocation(line: 503, column: 2, scope: !3469)
!3469 = !DILexicalBlockFile(scope: !669, file: !1, discriminator: 2)
!3470 = !DILocation(line: 507, column: 2, scope: !669)
!3471 = !DILocation(line: 508, column: 1, scope: !669)
!3472 = !DILocalVariable(name: "entry", arg: 1, scope: !672, file: !1, line: 1403, type: !379)
!3473 = !DILocation(line: 1403, column: 35, scope: !672)
!3474 = !DILocalVariable(name: "type", scope: !672, file: !1, line: 1405, type: !642)
!3475 = !DILocation(line: 1405, column: 9, scope: !672)
!3476 = !DILocalVariable(name: "path", scope: !672, file: !1, line: 1406, type: !429)
!3477 = !DILocation(line: 1406, column: 14, scope: !672)
!3478 = !DILocation(line: 1408, column: 32, scope: !672)
!3479 = !DILocation(line: 1408, column: 9, scope: !672)
!3480 = !DILocation(line: 1408, column: 7, scope: !672)
!3481 = !DILocation(line: 1409, column: 32, scope: !672)
!3482 = !DILocation(line: 1409, column: 9, scope: !672)
!3483 = !DILocation(line: 1409, column: 7, scope: !672)
!3484 = !DILocation(line: 1411, column: 6, scope: !3485)
!3485 = distinct !DILexicalBlock(scope: !672, file: !1, line: 1411, column: 6)
!3486 = !DILocation(line: 1411, column: 11, scope: !3485)
!3487 = !DILocation(line: 1411, column: 6, scope: !672)
!3488 = !DILocation(line: 1412, column: 3, scope: !3485)
!3489 = !DILocation(line: 1413, column: 6, scope: !3490)
!3490 = distinct !DILexicalBlock(scope: !672, file: !1, line: 1413, column: 6)
!3491 = !DILocation(line: 1413, column: 11, scope: !3490)
!3492 = !DILocation(line: 1413, column: 23, scope: !3490)
!3493 = !DILocation(line: 1414, column: 7, scope: !3490)
!3494 = !DILocation(line: 1414, column: 15, scope: !3490)
!3495 = !DILocation(line: 1414, column: 23, scope: !3490)
!3496 = !DILocation(line: 1414, column: 38, scope: !3497)
!3497 = !DILexicalBlockFile(scope: !3490, file: !1, discriminator: 1)
!3498 = !DILocation(line: 1414, column: 31, scope: !3497)
!3499 = !DILocation(line: 1414, column: 44, scope: !3497)
!3500 = !DILocation(line: 1414, column: 26, scope: !3497)
!3501 = !DILocation(line: 1414, column: 49, scope: !3497)
!3502 = !DILocation(line: 1413, column: 6, scope: !3503)
!3503 = !DILexicalBlockFile(scope: !672, file: !1, discriminator: 1)
!3504 = !DILocation(line: 1415, column: 17, scope: !3505)
!3505 = distinct !DILexicalBlock(scope: !3490, file: !1, line: 1414, column: 58)
!3506 = !DILocation(line: 1415, column: 10, scope: !3505)
!3507 = !DILocation(line: 1415, column: 23, scope: !3505)
!3508 = !DILocation(line: 1415, column: 3, scope: !3505)
!3509 = !DILocation(line: 1417, column: 17, scope: !3510)
!3510 = distinct !DILexicalBlock(scope: !3490, file: !1, line: 1416, column: 9)
!3511 = !DILocation(line: 1417, column: 10, scope: !3510)
!3512 = !DILocation(line: 1417, column: 3, scope: !3510)
!3513 = !DILocation(line: 1419, column: 1, scope: !672)
!3514 = !DILocalVariable(name: "pp", arg: 1, scope: !675, file: !676, line: 168, type: !473)
!3515 = !DILocation(line: 168, column: 23, scope: !675)
!3516 = !DILocalVariable(name: "u", arg: 2, scope: !675, file: !676, line: 168, type: !644)
!3517 = !DILocation(line: 168, column: 36, scope: !675)
!3518 = !DILocalVariable(name: "p", scope: !675, file: !676, line: 170, type: !577)
!3519 = !DILocation(line: 170, column: 17, scope: !675)
!3520 = !DILocation(line: 170, column: 38, scope: !675)
!3521 = !DILocation(line: 172, column: 9, scope: !675)
!3522 = !DILocation(line: 172, column: 11, scope: !675)
!3523 = !DILocation(line: 172, column: 2, scope: !675)
!3524 = !DILocation(line: 172, column: 7, scope: !675)
!3525 = !DILocation(line: 173, column: 10, scope: !675)
!3526 = !DILocation(line: 173, column: 12, scope: !675)
!3527 = !DILocation(line: 173, column: 18, scope: !675)
!3528 = !DILocation(line: 173, column: 9, scope: !675)
!3529 = !DILocation(line: 173, column: 2, scope: !675)
!3530 = !DILocation(line: 173, column: 7, scope: !675)
!3531 = !DILocation(line: 174, column: 1, scope: !675)
!3532 = !DILocalVariable(name: "pp", arg: 1, scope: !679, file: !676, line: 177, type: !473)
!3533 = !DILocation(line: 177, column: 23, scope: !679)
!3534 = !DILocalVariable(name: "u", arg: 2, scope: !679, file: !676, line: 177, type: !552)
!3535 = !DILocation(line: 177, column: 36, scope: !679)
!3536 = !DILocalVariable(name: "p", scope: !679, file: !676, line: 179, type: !577)
!3537 = !DILocation(line: 179, column: 17, scope: !679)
!3538 = !DILocation(line: 179, column: 38, scope: !679)
!3539 = !DILocation(line: 181, column: 9, scope: !679)
!3540 = !DILocation(line: 181, column: 11, scope: !679)
!3541 = !DILocation(line: 181, column: 2, scope: !679)
!3542 = !DILocation(line: 181, column: 7, scope: !679)
!3543 = !DILocation(line: 182, column: 10, scope: !679)
!3544 = !DILocation(line: 182, column: 12, scope: !679)
!3545 = !DILocation(line: 182, column: 18, scope: !679)
!3546 = !DILocation(line: 182, column: 9, scope: !679)
!3547 = !DILocation(line: 182, column: 2, scope: !679)
!3548 = !DILocation(line: 182, column: 7, scope: !679)
!3549 = !DILocation(line: 183, column: 10, scope: !679)
!3550 = !DILocation(line: 183, column: 12, scope: !679)
!3551 = !DILocation(line: 183, column: 19, scope: !679)
!3552 = !DILocation(line: 183, column: 9, scope: !679)
!3553 = !DILocation(line: 183, column: 2, scope: !679)
!3554 = !DILocation(line: 183, column: 7, scope: !679)
!3555 = !DILocation(line: 184, column: 10, scope: !679)
!3556 = !DILocation(line: 184, column: 12, scope: !679)
!3557 = !DILocation(line: 184, column: 19, scope: !679)
!3558 = !DILocation(line: 184, column: 9, scope: !679)
!3559 = !DILocation(line: 184, column: 2, scope: !679)
!3560 = !DILocation(line: 184, column: 7, scope: !679)
!3561 = !DILocation(line: 185, column: 1, scope: !679)
!3562 = !DILocalVariable(name: "unix_time", arg: 1, scope: !682, file: !1, line: 1373, type: !685)
!3563 = !DILocation(line: 1373, column: 23, scope: !682)
!3564 = !DILocalVariable(name: "t", scope: !682, file: !1, line: 1375, type: !3565)
!3565 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !3566, size: 64, align: 64)
!3566 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !687, line: 133, size: 448, align: 64, elements: !3567)
!3567 = !{!3568, !3569, !3570, !3571, !3572, !3573, !3574, !3575, !3576, !3577, !3578}
!3568 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !3566, file: !687, line: 135, baseType: !372, size: 32, align: 32)
!3569 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !3566, file: !687, line: 136, baseType: !372, size: 32, align: 32, offset: 32)
!3570 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !3566, file: !687, line: 137, baseType: !372, size: 32, align: 32, offset: 64)
!3571 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !3566, file: !687, line: 138, baseType: !372, size: 32, align: 32, offset: 96)
!3572 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !3566, file: !687, line: 139, baseType: !372, size: 32, align: 32, offset: 128)
!3573 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !3566, file: !687, line: 140, baseType: !372, size: 32, align: 32, offset: 160)
!3574 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !3566, file: !687, line: 141, baseType: !372, size: 32, align: 32, offset: 192)
!3575 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !3566, file: !687, line: 142, baseType: !372, size: 32, align: 32, offset: 224)
!3576 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !3566, file: !687, line: 143, baseType: !372, size: 32, align: 32, offset: 256)
!3577 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !3566, file: !687, line: 146, baseType: !391, size: 64, align: 64, offset: 320)
!3578 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !3566, file: !687, line: 147, baseType: !429, size: 64, align: 64, offset: 384)
!3579 = !DILocation(line: 1375, column: 13, scope: !682)
!3580 = !DILocalVariable(name: "dt", scope: !682, file: !1, line: 1376, type: !362)
!3581 = !DILocation(line: 1376, column: 15, scope: !682)
!3582 = !DILocation(line: 1380, column: 6, scope: !682)
!3583 = !DILocation(line: 1380, column: 4, scope: !682)
!3584 = !DILocation(line: 1383, column: 6, scope: !3585)
!3585 = distinct !DILexicalBlock(scope: !682, file: !1, line: 1383, column: 6)
!3586 = !DILocation(line: 1383, column: 9, scope: !3585)
!3587 = !DILocation(line: 1383, column: 17, scope: !3585)
!3588 = !DILocation(line: 1383, column: 6, scope: !682)
!3589 = !DILocation(line: 1385, column: 6, scope: !3585)
!3590 = !DILocation(line: 1385, column: 3, scope: !3585)
!3591 = !DILocation(line: 1386, column: 11, scope: !3592)
!3592 = distinct !DILexicalBlock(scope: !3585, file: !1, line: 1386, column: 11)
!3593 = !DILocation(line: 1386, column: 14, scope: !3592)
!3594 = !DILocation(line: 1386, column: 22, scope: !3592)
!3595 = !DILocation(line: 1386, column: 11, scope: !3585)
!3596 = !DILocation(line: 1388, column: 6, scope: !3592)
!3597 = !DILocation(line: 1388, column: 3, scope: !3592)
!3598 = !DILocation(line: 1390, column: 6, scope: !3599)
!3599 = distinct !DILexicalBlock(scope: !3592, file: !1, line: 1389, column: 7)
!3600 = !DILocation(line: 1391, column: 11, scope: !3599)
!3601 = !DILocation(line: 1391, column: 14, scope: !3599)
!3602 = !DILocation(line: 1391, column: 22, scope: !3599)
!3603 = !DILocation(line: 1391, column: 28, scope: !3599)
!3604 = !DILocation(line: 1391, column: 36, scope: !3599)
!3605 = !DILocation(line: 1391, column: 6, scope: !3599)
!3606 = !DILocation(line: 1392, column: 11, scope: !3599)
!3607 = !DILocation(line: 1392, column: 14, scope: !3599)
!3608 = !DILocation(line: 1392, column: 21, scope: !3599)
!3609 = !DILocation(line: 1392, column: 26, scope: !3599)
!3610 = !DILocation(line: 1392, column: 34, scope: !3599)
!3611 = !DILocation(line: 1392, column: 6, scope: !3599)
!3612 = !DILocation(line: 1393, column: 10, scope: !3599)
!3613 = !DILocation(line: 1393, column: 13, scope: !3599)
!3614 = !DILocation(line: 1393, column: 21, scope: !3599)
!3615 = !DILocation(line: 1393, column: 6, scope: !3599)
!3616 = !DILocation(line: 1394, column: 6, scope: !3599)
!3617 = !DILocation(line: 1395, column: 10, scope: !3599)
!3618 = !DILocation(line: 1395, column: 13, scope: !3599)
!3619 = !DILocation(line: 1395, column: 21, scope: !3599)
!3620 = !DILocation(line: 1395, column: 29, scope: !3599)
!3621 = !DILocation(line: 1395, column: 6, scope: !3599)
!3622 = !DILocation(line: 1396, column: 10, scope: !3599)
!3623 = !DILocation(line: 1396, column: 13, scope: !3599)
!3624 = !DILocation(line: 1396, column: 20, scope: !3599)
!3625 = !DILocation(line: 1396, column: 28, scope: !3599)
!3626 = !DILocation(line: 1396, column: 6, scope: !3599)
!3627 = !DILocation(line: 1397, column: 10, scope: !3599)
!3628 = !DILocation(line: 1397, column: 13, scope: !3599)
!3629 = !DILocation(line: 1397, column: 20, scope: !3599)
!3630 = !DILocation(line: 1397, column: 28, scope: !3599)
!3631 = !DILocation(line: 1397, column: 6, scope: !3599)
!3632 = !DILocation(line: 1399, column: 9, scope: !682)
!3633 = !DILocation(line: 1399, column: 2, scope: !682)
!3634 = !DILocalVariable(name: "zip", arg: 1, scope: !689, file: !1, line: 202, type: !541)
!3635 = !DILocation(line: 202, column: 22, scope: !689)
!3636 = !DILocalVariable(name: "length", arg: 2, scope: !689, file: !1, line: 202, type: !394)
!3637 = !DILocation(line: 202, column: 34, scope: !689)
!3638 = !DILocalVariable(name: "p", scope: !689, file: !1, line: 204, type: !577)
!3639 = !DILocation(line: 204, column: 17, scope: !689)
!3640 = !DILocation(line: 206, column: 6, scope: !3641)
!3641 = distinct !DILexicalBlock(scope: !689, file: !1, line: 206, column: 6)
!3642 = !DILocation(line: 206, column: 11, scope: !3641)
!3643 = !DILocation(line: 206, column: 29, scope: !3641)
!3644 = !DILocation(line: 207, column: 6, scope: !3641)
!3645 = !DILocation(line: 207, column: 10, scope: !3646)
!3646 = !DILexicalBlockFile(scope: !3641, file: !1, discriminator: 1)
!3647 = !DILocation(line: 207, column: 15, scope: !3646)
!3648 = !DILocation(line: 207, column: 39, scope: !3646)
!3649 = !DILocation(line: 207, column: 43, scope: !3646)
!3650 = !DILocation(line: 207, column: 41, scope: !3646)
!3651 = !DILocation(line: 208, column: 5, scope: !3641)
!3652 = !DILocation(line: 208, column: 10, scope: !3641)
!3653 = !DILocation(line: 208, column: 34, scope: !3641)
!3654 = !DILocation(line: 208, column: 41, scope: !3641)
!3655 = !DILocation(line: 208, column: 46, scope: !3641)
!3656 = !DILocation(line: 208, column: 70, scope: !3641)
!3657 = !DILocation(line: 208, column: 39, scope: !3641)
!3658 = !DILocation(line: 208, column: 3, scope: !3641)
!3659 = !DILocation(line: 206, column: 6, scope: !3660)
!3660 = !DILexicalBlockFile(scope: !689, file: !1, discriminator: 1)
!3661 = !DILocalVariable(name: "segment", scope: !3662, file: !1, line: 209, type: !584)
!3662 = distinct !DILexicalBlock(scope: !3641, file: !1, line: 208, column: 82)
!3663 = !DILocation(line: 209, column: 22, scope: !3662)
!3664 = !DILocation(line: 209, column: 32, scope: !3662)
!3665 = !DILocation(line: 210, column: 7, scope: !3666)
!3666 = distinct !DILexicalBlock(scope: !3662, file: !1, line: 210, column: 7)
!3667 = !DILocation(line: 210, column: 15, scope: !3666)
!3668 = !DILocation(line: 210, column: 7, scope: !3662)
!3669 = !DILocation(line: 211, column: 4, scope: !3666)
!3670 = !DILocation(line: 212, column: 3, scope: !3662)
!3671 = !DILocation(line: 212, column: 12, scope: !3662)
!3672 = !DILocation(line: 212, column: 22, scope: !3662)
!3673 = !DILocation(line: 213, column: 26, scope: !3662)
!3674 = !DILocation(line: 213, column: 35, scope: !3662)
!3675 = !DILocation(line: 213, column: 19, scope: !3662)
!3676 = !DILocation(line: 213, column: 3, scope: !3662)
!3677 = !DILocation(line: 213, column: 12, scope: !3662)
!3678 = !DILocation(line: 213, column: 17, scope: !3662)
!3679 = !DILocation(line: 214, column: 7, scope: !3680)
!3680 = distinct !DILexicalBlock(scope: !3662, file: !1, line: 214, column: 7)
!3681 = !DILocation(line: 214, column: 16, scope: !3680)
!3682 = !DILocation(line: 214, column: 21, scope: !3680)
!3683 = !DILocation(line: 214, column: 7, scope: !3662)
!3684 = !DILocation(line: 215, column: 9, scope: !3685)
!3685 = distinct !DILexicalBlock(scope: !3680, file: !1, line: 214, column: 30)
!3686 = !DILocation(line: 215, column: 4, scope: !3685)
!3687 = !DILocation(line: 216, column: 4, scope: !3685)
!3688 = !DILocation(line: 218, column: 16, scope: !3662)
!3689 = !DILocation(line: 218, column: 25, scope: !3662)
!3690 = !DILocation(line: 218, column: 3, scope: !3662)
!3691 = !DILocation(line: 218, column: 12, scope: !3662)
!3692 = !DILocation(line: 218, column: 14, scope: !3662)
!3693 = !DILocation(line: 220, column: 7, scope: !3694)
!3694 = distinct !DILexicalBlock(scope: !3662, file: !1, line: 220, column: 7)
!3695 = !DILocation(line: 220, column: 12, scope: !3694)
!3696 = !DILocation(line: 220, column: 30, scope: !3694)
!3697 = !DILocation(line: 220, column: 7, scope: !3662)
!3698 = !DILocation(line: 223, column: 10, scope: !3699)
!3699 = distinct !DILexicalBlock(scope: !3694, file: !1, line: 220, column: 39)
!3700 = !DILocation(line: 222, column: 10, scope: !3699)
!3701 = !DILocation(line: 222, column: 15, scope: !3699)
!3702 = !DILocation(line: 223, column: 8, scope: !3699)
!3703 = !DILocation(line: 221, column: 4, scope: !3699)
!3704 = !DILocation(line: 221, column: 9, scope: !3699)
!3705 = !DILocation(line: 222, column: 8, scope: !3699)
!3706 = !DILocation(line: 224, column: 3, scope: !3699)
!3707 = !DILocation(line: 225, column: 40, scope: !3708)
!3708 = distinct !DILexicalBlock(scope: !3694, file: !1, line: 224, column: 10)
!3709 = !DILocation(line: 225, column: 4, scope: !3708)
!3710 = !DILocation(line: 225, column: 9, scope: !3708)
!3711 = !DILocation(line: 225, column: 33, scope: !3708)
!3712 = !DILocation(line: 225, column: 38, scope: !3708)
!3713 = !DILocation(line: 226, column: 34, scope: !3708)
!3714 = !DILocation(line: 226, column: 4, scope: !3708)
!3715 = !DILocation(line: 226, column: 9, scope: !3708)
!3716 = !DILocation(line: 226, column: 32, scope: !3708)
!3717 = !DILocation(line: 228, column: 2, scope: !3662)
!3718 = !DILocation(line: 230, column: 6, scope: !689)
!3719 = !DILocation(line: 230, column: 11, scope: !689)
!3720 = !DILocation(line: 230, column: 35, scope: !689)
!3721 = !DILocation(line: 230, column: 4, scope: !689)
!3722 = !DILocation(line: 231, column: 36, scope: !689)
!3723 = !DILocation(line: 231, column: 2, scope: !689)
!3724 = !DILocation(line: 231, column: 7, scope: !689)
!3725 = !DILocation(line: 231, column: 31, scope: !689)
!3726 = !DILocation(line: 231, column: 33, scope: !689)
!3727 = !DILocation(line: 232, column: 34, scope: !689)
!3728 = !DILocation(line: 232, column: 2, scope: !689)
!3729 = !DILocation(line: 232, column: 7, scope: !689)
!3730 = !DILocation(line: 232, column: 31, scope: !689)
!3731 = !DILocation(line: 233, column: 10, scope: !689)
!3732 = !DILocation(line: 233, column: 2, scope: !689)
!3733 = !DILocation(line: 234, column: 1, scope: !689)
!3734 = !DILocalVariable(name: "entry", arg: 1, scope: !692, file: !1, line: 1450, type: !379)
!3735 = !DILocation(line: 1450, column: 33, scope: !692)
!3736 = !DILocalVariable(name: "p", arg: 2, scope: !692, file: !1, line: 1450, type: !577)
!3737 = !DILocation(line: 1450, column: 55, scope: !692)
!3738 = !DILocalVariable(name: "path", scope: !692, file: !1, line: 1452, type: !429)
!3739 = !DILocation(line: 1452, column: 14, scope: !692)
!3740 = !DILocalVariable(name: "pathlen", scope: !692, file: !1, line: 1453, type: !394)
!3741 = !DILocation(line: 1453, column: 9, scope: !692)
!3742 = !DILocalVariable(name: "type", scope: !692, file: !1, line: 1454, type: !642)
!3743 = !DILocation(line: 1454, column: 9, scope: !692)
!3744 = !DILocation(line: 1456, column: 32, scope: !692)
!3745 = !DILocation(line: 1456, column: 9, scope: !692)
!3746 = !DILocation(line: 1456, column: 7, scope: !692)
!3747 = !DILocation(line: 1457, column: 19, scope: !692)
!3748 = !DILocation(line: 1457, column: 12, scope: !692)
!3749 = !DILocation(line: 1457, column: 10, scope: !692)
!3750 = !DILocation(line: 1458, column: 32, scope: !692)
!3751 = !DILocation(line: 1458, column: 9, scope: !692)
!3752 = !DILocation(line: 1458, column: 7, scope: !692)
!3753 = !DILocation(line: 1460, column: 9, scope: !692)
!3754 = !DILocation(line: 1460, column: 12, scope: !692)
!3755 = !DILocation(line: 1460, column: 18, scope: !692)
!3756 = !DILocation(line: 1460, column: 2, scope: !692)
!3757 = !DILocation(line: 1463, column: 7, scope: !3758)
!3758 = distinct !DILexicalBlock(scope: !692, file: !1, line: 1463, column: 6)
!3759 = !DILocation(line: 1463, column: 12, scope: !3758)
!3760 = !DILocation(line: 1463, column: 33, scope: !3758)
!3761 = !DILocation(line: 1463, column: 41, scope: !3758)
!3762 = !DILocation(line: 1463, column: 28, scope: !3758)
!3763 = !DILocation(line: 1463, column: 46, scope: !3758)
!3764 = !DILocation(line: 1463, column: 25, scope: !3758)
!3765 = !DILocation(line: 1463, column: 6, scope: !692)
!3766 = !DILocation(line: 1464, column: 5, scope: !3767)
!3767 = distinct !DILexicalBlock(scope: !3758, file: !1, line: 1463, column: 55)
!3768 = !DILocation(line: 1464, column: 3, scope: !3767)
!3769 = !DILocation(line: 1464, column: 14, scope: !3767)
!3770 = !DILocation(line: 1465, column: 5, scope: !3767)
!3771 = !DILocation(line: 1465, column: 13, scope: !3767)
!3772 = !DILocation(line: 1465, column: 3, scope: !3767)
!3773 = !DILocation(line: 1465, column: 18, scope: !3767)
!3774 = !DILocation(line: 1466, column: 2, scope: !3767)
!3775 = !DILocation(line: 1467, column: 1, scope: !692)
!3776 = !DILocalVariable(name: "pp", arg: 1, scope: !695, file: !676, line: 188, type: !473)
!3777 = !DILocation(line: 188, column: 23, scope: !695)
!3778 = !DILocalVariable(name: "u", arg: 2, scope: !695, file: !676, line: 188, type: !650)
!3779 = !DILocation(line: 188, column: 36, scope: !695)
!3780 = !DILocalVariable(name: "p", scope: !695, file: !676, line: 190, type: !577)
!3781 = !DILocation(line: 190, column: 17, scope: !695)
!3782 = !DILocation(line: 190, column: 38, scope: !695)
!3783 = !DILocation(line: 192, column: 18, scope: !695)
!3784 = !DILocation(line: 192, column: 32, scope: !695)
!3785 = !DILocation(line: 192, column: 34, scope: !695)
!3786 = !DILocation(line: 192, column: 21, scope: !695)
!3787 = !DILocation(line: 192, column: 2, scope: !695)
!3788 = !DILocation(line: 193, column: 18, scope: !695)
!3789 = !DILocation(line: 193, column: 20, scope: !695)
!3790 = !DILocation(line: 193, column: 36, scope: !695)
!3791 = !DILocation(line: 193, column: 38, scope: !695)
!3792 = !DILocation(line: 193, column: 25, scope: !695)
!3793 = !DILocation(line: 193, column: 2, scope: !695)
!3794 = !DILocation(line: 194, column: 1, scope: !695)
!3795 = !DILocalVariable(name: "entry", arg: 1, scope: !698, file: !1, line: 1422, type: !379)
!3796 = !DILocation(line: 1422, column: 34, scope: !698)
!3797 = !DILocalVariable(name: "archive", arg: 2, scope: !698, file: !1, line: 1422, type: !353)
!3798 = !DILocation(line: 1422, column: 63, scope: !698)
!3799 = !DILocalVariable(name: "ret", scope: !698, file: !1, line: 1424, type: !372)
!3800 = !DILocation(line: 1424, column: 6, scope: !698)
!3801 = !DILocalVariable(name: "path", scope: !698, file: !1, line: 1425, type: !429)
!3802 = !DILocation(line: 1425, column: 14, scope: !698)
!3803 = !DILocalVariable(name: "type", scope: !698, file: !1, line: 1426, type: !642)
!3804 = !DILocation(line: 1426, column: 9, scope: !698)
!3805 = !DILocalVariable(name: "written_bytes", scope: !698, file: !1, line: 1427, type: !394)
!3806 = !DILocation(line: 1427, column: 9, scope: !698)
!3807 = !DILocation(line: 1429, column: 32, scope: !698)
!3808 = !DILocation(line: 1429, column: 9, scope: !698)
!3809 = !DILocation(line: 1429, column: 7, scope: !698)
!3810 = !DILocation(line: 1430, column: 32, scope: !698)
!3811 = !DILocation(line: 1430, column: 9, scope: !698)
!3812 = !DILocation(line: 1430, column: 7, scope: !698)
!3813 = !DILocation(line: 1431, column: 16, scope: !698)
!3814 = !DILocation(line: 1433, column: 31, scope: !698)
!3815 = !DILocation(line: 1433, column: 40, scope: !698)
!3816 = !DILocation(line: 1433, column: 53, scope: !698)
!3817 = !DILocation(line: 1433, column: 46, scope: !698)
!3818 = !DILocation(line: 1433, column: 8, scope: !3819)
!3819 = !DILexicalBlockFile(scope: !698, file: !1, discriminator: 1)
!3820 = !DILocation(line: 1433, column: 6, scope: !698)
!3821 = !DILocation(line: 1434, column: 6, scope: !3822)
!3822 = distinct !DILexicalBlock(scope: !698, file: !1, line: 1434, column: 6)
!3823 = !DILocation(line: 1434, column: 10, scope: !3822)
!3824 = !DILocation(line: 1434, column: 6, scope: !698)
!3825 = !DILocation(line: 1435, column: 3, scope: !3822)
!3826 = !DILocation(line: 1436, column: 26, scope: !698)
!3827 = !DILocation(line: 1436, column: 19, scope: !698)
!3828 = !DILocation(line: 1436, column: 16, scope: !698)
!3829 = !DILocation(line: 1439, column: 7, scope: !3830)
!3830 = distinct !DILexicalBlock(scope: !698, file: !1, line: 1439, column: 6)
!3831 = !DILocation(line: 1439, column: 12, scope: !3830)
!3832 = !DILocation(line: 1439, column: 40, scope: !3830)
!3833 = !DILocation(line: 1439, column: 33, scope: !3830)
!3834 = !DILocation(line: 1439, column: 46, scope: !3830)
!3835 = !DILocation(line: 1439, column: 28, scope: !3830)
!3836 = !DILocation(line: 1439, column: 51, scope: !3830)
!3837 = !DILocation(line: 1439, column: 25, scope: !3830)
!3838 = !DILocation(line: 1439, column: 6, scope: !698)
!3839 = !DILocation(line: 1440, column: 32, scope: !3840)
!3840 = distinct !DILexicalBlock(scope: !3830, file: !1, line: 1439, column: 60)
!3841 = !DILocation(line: 1440, column: 9, scope: !3840)
!3842 = !DILocation(line: 1440, column: 7, scope: !3840)
!3843 = !DILocation(line: 1441, column: 7, scope: !3844)
!3844 = distinct !DILexicalBlock(scope: !3840, file: !1, line: 1441, column: 7)
!3845 = !DILocation(line: 1441, column: 11, scope: !3844)
!3846 = !DILocation(line: 1441, column: 7, scope: !3840)
!3847 = !DILocation(line: 1442, column: 4, scope: !3844)
!3848 = !DILocation(line: 1443, column: 17, scope: !3840)
!3849 = !DILocation(line: 1444, column: 2, scope: !3840)
!3850 = !DILocation(line: 1446, column: 15, scope: !698)
!3851 = !DILocation(line: 1446, column: 10, scope: !698)
!3852 = !DILocation(line: 1446, column: 2, scope: !698)
!3853 = !DILocation(line: 1447, column: 1, scope: !698)
!3854 = !DILocalVariable(name: "a", arg: 1, scope: !702, file: !1, line: 1548, type: !353)
!3855 = !DILocation(line: 1548, column: 58, scope: !702)
!3856 = !DILocalVariable(name: "zip", scope: !702, file: !1, line: 1550, type: !541)
!3857 = !DILocation(line: 1550, column: 14, scope: !702)
!3858 = !DILocation(line: 1550, column: 20, scope: !702)
!3859 = !DILocation(line: 1550, column: 23, scope: !702)
!3860 = !DILocalVariable(name: "passphrase", scope: !702, file: !1, line: 1551, type: !429)
!3861 = !DILocation(line: 1551, column: 14, scope: !702)
!3862 = !DILocalVariable(name: "key", scope: !702, file: !1, line: 1552, type: !3333)
!3863 = !DILocation(line: 1552, column: 10, scope: !702)
!3864 = !DILocalVariable(name: "key_encrypted", scope: !702, file: !1, line: 1553, type: !3333)
!3865 = !DILocation(line: 1553, column: 10, scope: !702)
!3866 = !DILocalVariable(name: "ret", scope: !702, file: !1, line: 1554, type: !372)
!3867 = !DILocation(line: 1554, column: 6, scope: !702)
!3868 = !DILocation(line: 1556, column: 46, scope: !702)
!3869 = !DILocation(line: 1556, column: 15, scope: !702)
!3870 = !DILocation(line: 1556, column: 13, scope: !702)
!3871 = !DILocation(line: 1557, column: 6, scope: !3872)
!3872 = distinct !DILexicalBlock(scope: !702, file: !1, line: 1557, column: 6)
!3873 = !DILocation(line: 1557, column: 17, scope: !3872)
!3874 = !DILocation(line: 1557, column: 6, scope: !702)
!3875 = !DILocation(line: 1558, column: 22, scope: !3876)
!3876 = distinct !DILexicalBlock(scope: !3872, file: !1, line: 1557, column: 26)
!3877 = !DILocation(line: 1558, column: 25, scope: !3876)
!3878 = !DILocation(line: 1558, column: 3, scope: !3876)
!3879 = !DILocation(line: 1560, column: 3, scope: !3876)
!3880 = !DILocation(line: 1562, column: 21, scope: !3881)
!3881 = distinct !DILexicalBlock(scope: !702, file: !1, line: 1562, column: 6)
!3882 = !DILocation(line: 1562, column: 6, scope: !3881)
!3883 = !DILocation(line: 1562, column: 41, scope: !3881)
!3884 = !DILocation(line: 1562, column: 6, scope: !702)
!3885 = !DILocation(line: 1563, column: 22, scope: !3886)
!3886 = distinct !DILexicalBlock(scope: !3881, file: !1, line: 1562, column: 56)
!3887 = !DILocation(line: 1563, column: 25, scope: !3886)
!3888 = !DILocation(line: 1563, column: 3, scope: !3886)
!3889 = !DILocation(line: 1565, column: 3, scope: !3886)
!3890 = !DILocation(line: 1567, column: 17, scope: !702)
!3891 = !DILocation(line: 1567, column: 22, scope: !702)
!3892 = !DILocation(line: 1567, column: 28, scope: !702)
!3893 = !DILocation(line: 1567, column: 47, scope: !702)
!3894 = !DILocation(line: 1567, column: 40, scope: !702)
!3895 = !DILocation(line: 1567, column: 2, scope: !3896)
!3896 = !DILexicalBlockFile(scope: !702, file: !1, discriminator: 1)
!3897 = !DILocation(line: 1570, column: 28, scope: !702)
!3898 = !DILocation(line: 1570, column: 33, scope: !702)
!3899 = !DILocation(line: 1570, column: 2, scope: !702)
!3900 = !DILocation(line: 1570, column: 26, scope: !702)
!3901 = !DILocation(line: 1571, column: 27, scope: !702)
!3902 = !DILocation(line: 1571, column: 32, scope: !702)
!3903 = !DILocation(line: 1571, column: 38, scope: !702)
!3904 = !DILocation(line: 1572, column: 6, scope: !702)
!3905 = !DILocation(line: 1571, column: 2, scope: !702)
!3906 = !DILocation(line: 1574, column: 31, scope: !702)
!3907 = !DILocation(line: 1574, column: 34, scope: !702)
!3908 = !DILocation(line: 1574, column: 8, scope: !702)
!3909 = !DILocation(line: 1574, column: 6, scope: !702)
!3910 = !DILocation(line: 1575, column: 6, scope: !3911)
!3911 = distinct !DILexicalBlock(scope: !702, file: !1, line: 1575, column: 6)
!3912 = !DILocation(line: 1575, column: 10, scope: !3911)
!3913 = !DILocation(line: 1575, column: 6, scope: !702)
!3914 = !DILocation(line: 1576, column: 11, scope: !3911)
!3915 = !DILocation(line: 1576, column: 3, scope: !3911)
!3916 = !DILocation(line: 1577, column: 2, scope: !702)
!3917 = !DILocation(line: 1577, column: 7, scope: !702)
!3918 = !DILocation(line: 1577, column: 21, scope: !702)
!3919 = !DILocation(line: 1578, column: 2, scope: !702)
!3920 = !DILocation(line: 1578, column: 7, scope: !702)
!3921 = !DILocation(line: 1578, column: 32, scope: !702)
!3922 = !DILocation(line: 1579, column: 10, scope: !702)
!3923 = !DILocation(line: 1579, column: 2, scope: !702)
!3924 = !DILocation(line: 1580, column: 1, scope: !702)
!3925 = !DILocalVariable(name: "a", arg: 1, scope: !710, file: !1, line: 1583, type: !353)
!3926 = !DILocation(line: 1583, column: 50, scope: !710)
!3927 = !DILocalVariable(name: "zip", scope: !710, file: !1, line: 1585, type: !541)
!3928 = !DILocation(line: 1585, column: 14, scope: !710)
!3929 = !DILocation(line: 1585, column: 20, scope: !710)
!3930 = !DILocation(line: 1585, column: 23, scope: !710)
!3931 = !DILocalVariable(name: "passphrase", scope: !710, file: !1, line: 1586, type: !429)
!3932 = !DILocation(line: 1586, column: 14, scope: !710)
!3933 = !DILocalVariable(name: "key_len", scope: !710, file: !1, line: 1587, type: !394)
!3934 = !DILocation(line: 1587, column: 9, scope: !710)
!3935 = !DILocalVariable(name: "salt_len", scope: !710, file: !1, line: 1587, type: !394)
!3936 = !DILocation(line: 1587, column: 18, scope: !710)
!3937 = !DILocalVariable(name: "salt", scope: !710, file: !1, line: 1588, type: !3352)
!3938 = !DILocation(line: 1588, column: 10, scope: !710)
!3939 = !DILocalVariable(name: "derived_key", scope: !710, file: !1, line: 1589, type: !3357)
!3940 = !DILocation(line: 1589, column: 10, scope: !710)
!3941 = !DILocalVariable(name: "ret", scope: !710, file: !1, line: 1590, type: !372)
!3942 = !DILocation(line: 1590, column: 6, scope: !710)
!3943 = !DILocation(line: 1592, column: 46, scope: !710)
!3944 = !DILocation(line: 1592, column: 15, scope: !710)
!3945 = !DILocation(line: 1592, column: 13, scope: !710)
!3946 = !DILocation(line: 1593, column: 6, scope: !3947)
!3947 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1593, column: 6)
!3948 = !DILocation(line: 1593, column: 17, scope: !3947)
!3949 = !DILocation(line: 1593, column: 6, scope: !710)
!3950 = !DILocation(line: 1594, column: 22, scope: !3951)
!3951 = distinct !DILexicalBlock(scope: !3947, file: !1, line: 1593, column: 26)
!3952 = !DILocation(line: 1594, column: 25, scope: !3951)
!3953 = !DILocation(line: 1594, column: 3, scope: !3951)
!3954 = !DILocation(line: 1596, column: 3, scope: !3951)
!3955 = !DILocation(line: 1598, column: 6, scope: !3956)
!3956 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1598, column: 6)
!3957 = !DILocation(line: 1598, column: 11, scope: !3956)
!3958 = !DILocation(line: 1598, column: 28, scope: !3956)
!3959 = !DILocation(line: 1598, column: 6, scope: !710)
!3960 = !DILocation(line: 1599, column: 12, scope: !3961)
!3961 = distinct !DILexicalBlock(scope: !3956, file: !1, line: 1598, column: 57)
!3962 = !DILocation(line: 1600, column: 11, scope: !3961)
!3963 = !DILocation(line: 1601, column: 2, scope: !3961)
!3964 = !DILocation(line: 1603, column: 12, scope: !3965)
!3965 = distinct !DILexicalBlock(scope: !3956, file: !1, line: 1601, column: 9)
!3966 = !DILocation(line: 1604, column: 11, scope: !3965)
!3967 = !DILocation(line: 1606, column: 21, scope: !3968)
!3968 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1606, column: 6)
!3969 = !DILocation(line: 1606, column: 27, scope: !3968)
!3970 = !DILocation(line: 1606, column: 6, scope: !3968)
!3971 = !DILocation(line: 1606, column: 37, scope: !3968)
!3972 = !DILocation(line: 1606, column: 6, scope: !710)
!3973 = !DILocation(line: 1607, column: 22, scope: !3974)
!3974 = distinct !DILexicalBlock(scope: !3968, file: !1, line: 1606, column: 52)
!3975 = !DILocation(line: 1607, column: 25, scope: !3974)
!3976 = !DILocation(line: 1607, column: 3, scope: !3974)
!3977 = !DILocation(line: 1609, column: 3, scope: !3974)
!3978 = !DILocation(line: 1611, column: 2, scope: !710)
!3979 = !DILocation(line: 1611, column: 2, scope: !3980)
!3980 = !DILexicalBlockFile(scope: !710, file: !1, discriminator: 1)
!3981 = !DILocation(line: 1614, column: 8, scope: !710)
!3982 = !DILocation(line: 1614, column: 6, scope: !710)
!3983 = !DILocation(line: 1615, column: 6, scope: !3984)
!3984 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1615, column: 6)
!3985 = !DILocation(line: 1615, column: 10, scope: !3984)
!3986 = !DILocation(line: 1615, column: 6, scope: !710)
!3987 = !DILocation(line: 1616, column: 22, scope: !3988)
!3988 = distinct !DILexicalBlock(scope: !3984, file: !1, line: 1615, column: 16)
!3989 = !DILocation(line: 1616, column: 25, scope: !3988)
!3990 = !DILocation(line: 1616, column: 3, scope: !3988)
!3991 = !DILocation(line: 1618, column: 3, scope: !3988)
!3992 = !DILocation(line: 1620, column: 8, scope: !710)
!3993 = !DILocation(line: 1620, column: 6, scope: !710)
!3994 = !DILocation(line: 1622, column: 6, scope: !3995)
!3995 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1622, column: 6)
!3996 = !DILocation(line: 1622, column: 10, scope: !3995)
!3997 = !DILocation(line: 1622, column: 6, scope: !710)
!3998 = !DILocation(line: 1623, column: 3, scope: !3999)
!3999 = distinct !DILexicalBlock(scope: !3995, file: !1, line: 1622, column: 16)
!4000 = !DILocation(line: 1624, column: 22, scope: !3999)
!4001 = !DILocation(line: 1624, column: 25, scope: !3999)
!4002 = !DILocation(line: 1624, column: 3, scope: !3999)
!4003 = !DILocation(line: 1626, column: 3, scope: !3999)
!4004 = !DILocation(line: 1630, column: 31, scope: !710)
!4005 = !DILocation(line: 1630, column: 39, scope: !710)
!4006 = !DILocation(line: 1630, column: 19, scope: !710)
!4007 = !DILocation(line: 1630, column: 7, scope: !710)
!4008 = !DILocation(line: 1630, column: 2, scope: !710)
!4009 = !DILocation(line: 1630, column: 17, scope: !710)
!4010 = !DILocation(line: 1631, column: 35, scope: !710)
!4011 = !DILocation(line: 1631, column: 43, scope: !710)
!4012 = !DILocation(line: 1631, column: 47, scope: !710)
!4013 = !DILocation(line: 1631, column: 23, scope: !710)
!4014 = !DILocation(line: 1631, column: 7, scope: !710)
!4015 = !DILocation(line: 1631, column: 16, scope: !710)
!4016 = !DILocation(line: 1631, column: 2, scope: !710)
!4017 = !DILocation(line: 1631, column: 21, scope: !710)
!4018 = !DILocation(line: 1634, column: 31, scope: !710)
!4019 = !DILocation(line: 1634, column: 34, scope: !710)
!4020 = !DILocation(line: 1634, column: 40, scope: !710)
!4021 = !DILocation(line: 1634, column: 49, scope: !710)
!4022 = !DILocation(line: 1634, column: 8, scope: !710)
!4023 = !DILocation(line: 1634, column: 6, scope: !710)
!4024 = !DILocation(line: 1635, column: 6, scope: !4025)
!4025 = distinct !DILexicalBlock(scope: !710, file: !1, line: 1635, column: 6)
!4026 = !DILocation(line: 1635, column: 10, scope: !4025)
!4027 = !DILocation(line: 1635, column: 6, scope: !710)
!4028 = !DILocation(line: 1636, column: 11, scope: !4025)
!4029 = !DILocation(line: 1636, column: 3, scope: !4025)
!4030 = !DILocation(line: 1637, column: 24, scope: !710)
!4031 = !DILocation(line: 1637, column: 33, scope: !710)
!4032 = !DILocation(line: 1637, column: 2, scope: !710)
!4033 = !DILocation(line: 1637, column: 7, scope: !710)
!4034 = !DILocation(line: 1637, column: 21, scope: !710)
!4035 = !DILocation(line: 1638, column: 35, scope: !710)
!4036 = !DILocation(line: 1638, column: 44, scope: !710)
!4037 = !DILocation(line: 1638, column: 2, scope: !710)
!4038 = !DILocation(line: 1638, column: 7, scope: !710)
!4039 = !DILocation(line: 1638, column: 32, scope: !710)
!4040 = !DILocation(line: 1640, column: 2, scope: !710)
!4041 = !DILocation(line: 1641, column: 1, scope: !710)
!4042 = !DILocalVariable(name: "ctx", arg: 1, scope: !711, file: !1, line: 1509, type: !706)
!4043 = !DILocation(line: 1509, column: 46, scope: !711)
!4044 = !DILocalVariable(name: "in", arg: 2, scope: !711, file: !1, line: 1509, type: !646)
!4045 = !DILocation(line: 1509, column: 66, scope: !711)
!4046 = !DILocalVariable(name: "in_len", arg: 3, scope: !711, file: !1, line: 1510, type: !394)
!4047 = !DILocation(line: 1510, column: 12, scope: !711)
!4048 = !DILocalVariable(name: "out", arg: 4, scope: !711, file: !1, line: 1510, type: !714)
!4049 = !DILocation(line: 1510, column: 29, scope: !711)
!4050 = !DILocalVariable(name: "out_len", arg: 5, scope: !711, file: !1, line: 1510, type: !394)
!4051 = !DILocation(line: 1510, column: 41, scope: !711)
!4052 = !DILocalVariable(name: "i", scope: !711, file: !1, line: 1512, type: !362)
!4053 = !DILocation(line: 1512, column: 11, scope: !711)
!4054 = !DILocalVariable(name: "max", scope: !711, file: !1, line: 1512, type: !362)
!4055 = !DILocation(line: 1512, column: 14, scope: !711)
!4056 = !DILocation(line: 1514, column: 20, scope: !711)
!4057 = !DILocation(line: 1514, column: 29, scope: !711)
!4058 = !DILocation(line: 1514, column: 27, scope: !711)
!4059 = !DILocation(line: 1514, column: 19, scope: !711)
!4060 = !DILocation(line: 1514, column: 39, scope: !4061)
!4061 = !DILexicalBlockFile(scope: !711, file: !1, discriminator: 1)
!4062 = !DILocation(line: 1514, column: 19, scope: !4061)
!4063 = !DILocation(line: 1514, column: 47, scope: !4064)
!4064 = !DILexicalBlockFile(scope: !711, file: !1, discriminator: 2)
!4065 = !DILocation(line: 1514, column: 19, scope: !4064)
!4066 = !DILocation(line: 1514, column: 19, scope: !4067)
!4067 = !DILexicalBlockFile(scope: !711, file: !1, discriminator: 3)
!4068 = !DILocation(line: 1514, column: 8, scope: !4067)
!4069 = !DILocation(line: 1514, column: 6, scope: !4067)
!4070 = !DILocation(line: 1516, column: 9, scope: !4071)
!4071 = distinct !DILexicalBlock(scope: !711, file: !1, line: 1516, column: 2)
!4072 = !DILocation(line: 1516, column: 7, scope: !4071)
!4073 = !DILocation(line: 1516, column: 14, scope: !4074)
!4074 = !DILexicalBlockFile(scope: !4075, file: !1, discriminator: 1)
!4075 = distinct !DILexicalBlock(scope: !4071, file: !1, line: 1516, column: 2)
!4076 = !DILocation(line: 1516, column: 18, scope: !4074)
!4077 = !DILocation(line: 1516, column: 16, scope: !4074)
!4078 = !DILocation(line: 1516, column: 2, scope: !4074)
!4079 = !DILocalVariable(name: "t", scope: !4080, file: !1, line: 1517, type: !648)
!4080 = distinct !DILexicalBlock(scope: !4075, file: !1, line: 1516, column: 28)
!4081 = !DILocation(line: 1517, column: 11, scope: !4080)
!4082 = !DILocation(line: 1517, column: 18, scope: !4080)
!4083 = !DILocation(line: 1517, column: 15, scope: !4080)
!4084 = !DILocation(line: 1518, column: 12, scope: !4080)
!4085 = !DILocation(line: 1518, column: 38, scope: !4080)
!4086 = !DILocation(line: 1518, column: 16, scope: !4080)
!4087 = !DILocation(line: 1518, column: 14, scope: !4080)
!4088 = !DILocation(line: 1518, column: 7, scope: !4080)
!4089 = !DILocation(line: 1518, column: 3, scope: !4080)
!4090 = !DILocation(line: 1518, column: 10, scope: !4080)
!4091 = !DILocation(line: 1519, column: 24, scope: !4080)
!4092 = !DILocation(line: 1519, column: 29, scope: !4080)
!4093 = !DILocation(line: 1519, column: 3, scope: !4080)
!4094 = !DILocation(line: 1520, column: 2, scope: !4080)
!4095 = !DILocation(line: 1516, column: 24, scope: !4096)
!4096 = !DILexicalBlockFile(scope: !4075, file: !1, discriminator: 2)
!4097 = !DILocation(line: 1516, column: 2, scope: !4096)
!4098 = !DILocation(line: 1521, column: 9, scope: !711)
!4099 = !DILocation(line: 1521, column: 2, scope: !711)
!4100 = !DILocalVariable(name: "ctx", arg: 1, scope: !703, file: !1, line: 1525, type: !706)
!4101 = !DILocation(line: 1525, column: 36, scope: !703)
!4102 = !DILocalVariable(name: "pw", arg: 2, scope: !703, file: !1, line: 1525, type: !429)
!4103 = !DILocation(line: 1525, column: 53, scope: !703)
!4104 = !DILocalVariable(name: "pw_len", arg: 3, scope: !703, file: !1, line: 1525, type: !394)
!4105 = !DILocation(line: 1525, column: 64, scope: !703)
!4106 = !DILocation(line: 1528, column: 2, scope: !703)
!4107 = !DILocation(line: 1528, column: 7, scope: !703)
!4108 = !DILocation(line: 1528, column: 15, scope: !703)
!4109 = !DILocation(line: 1529, column: 2, scope: !703)
!4110 = !DILocation(line: 1529, column: 7, scope: !703)
!4111 = !DILocation(line: 1529, column: 15, scope: !703)
!4112 = !DILocation(line: 1530, column: 2, scope: !703)
!4113 = !DILocation(line: 1530, column: 7, scope: !703)
!4114 = !DILocation(line: 1530, column: 15, scope: !703)
!4115 = !DILocation(line: 1532, column: 2, scope: !703)
!4116 = !DILocation(line: 1532, column: 8, scope: !4117)
!4117 = !DILexicalBlockFile(scope: !4118, file: !1, discriminator: 1)
!4118 = distinct !DILexicalBlock(scope: !4119, file: !1, line: 1532, column: 2)
!4119 = distinct !DILexicalBlock(scope: !703, file: !1, line: 1532, column: 2)
!4120 = !DILocation(line: 1532, column: 2, scope: !4117)
!4121 = !DILocation(line: 1533, column: 24, scope: !4118)
!4122 = !DILocation(line: 1533, column: 32, scope: !4118)
!4123 = !DILocation(line: 1533, column: 29, scope: !4118)
!4124 = !DILocation(line: 1533, column: 3, scope: !4118)
!4125 = !DILocation(line: 1532, column: 16, scope: !4126)
!4126 = !DILexicalBlockFile(scope: !4118, file: !1, discriminator: 2)
!4127 = !DILocation(line: 1532, column: 2, scope: !4126)
!4128 = !DILocation(line: 1534, column: 2, scope: !703)
!4129 = !DILocalVariable(name: "ctx", arg: 1, scope: !707, file: !1, line: 1489, type: !706)
!4130 = !DILocation(line: 1489, column: 43, scope: !707)
!4131 = !DILocalVariable(name: "c", arg: 2, scope: !707, file: !1, line: 1489, type: !648)
!4132 = !DILocation(line: 1489, column: 56, scope: !707)
!4133 = !DILocalVariable(name: "t", scope: !707, file: !1, line: 1491, type: !648)
!4134 = !DILocation(line: 1491, column: 10, scope: !707)
!4135 = !DILocation(line: 1494, column: 17, scope: !707)
!4136 = !DILocation(line: 1494, column: 2, scope: !707)
!4137 = !DILocation(line: 1494, column: 7, scope: !707)
!4138 = !DILocation(line: 1494, column: 15, scope: !707)
!4139 = !DILocation(line: 1495, column: 18, scope: !707)
!4140 = !DILocation(line: 1495, column: 23, scope: !707)
!4141 = !DILocation(line: 1495, column: 34, scope: !707)
!4142 = !DILocation(line: 1495, column: 39, scope: !707)
!4143 = !DILocation(line: 1495, column: 47, scope: !707)
!4144 = !DILocation(line: 1495, column: 31, scope: !707)
!4145 = !DILocation(line: 1495, column: 17, scope: !707)
!4146 = !DILocation(line: 1495, column: 56, scope: !707)
!4147 = !DILocation(line: 1495, column: 69, scope: !707)
!4148 = !DILocation(line: 1495, column: 2, scope: !707)
!4149 = !DILocation(line: 1495, column: 7, scope: !707)
!4150 = !DILocation(line: 1495, column: 15, scope: !707)
!4151 = !DILocation(line: 1496, column: 7, scope: !707)
!4152 = !DILocation(line: 1496, column: 12, scope: !707)
!4153 = !DILocation(line: 1496, column: 20, scope: !707)
!4154 = !DILocation(line: 1496, column: 27, scope: !707)
!4155 = !DILocation(line: 1496, column: 6, scope: !707)
!4156 = !DILocation(line: 1496, column: 4, scope: !707)
!4157 = !DILocation(line: 1497, column: 17, scope: !707)
!4158 = !DILocation(line: 1497, column: 2, scope: !707)
!4159 = !DILocation(line: 1497, column: 7, scope: !707)
!4160 = !DILocation(line: 1497, column: 15, scope: !707)
!4161 = !DILocation(line: 1499, column: 1, scope: !707)
!4162 = !DILocalVariable(name: "ctx", arg: 1, scope: !715, file: !1, line: 1502, type: !706)
!4163 = !DILocation(line: 1502, column: 44, scope: !715)
!4164 = !DILocalVariable(name: "temp", scope: !715, file: !1, line: 1504, type: !362)
!4165 = !DILocation(line: 1504, column: 11, scope: !715)
!4166 = !DILocation(line: 1504, column: 18, scope: !715)
!4167 = !DILocation(line: 1504, column: 23, scope: !715)
!4168 = !DILocation(line: 1504, column: 31, scope: !715)
!4169 = !DILocation(line: 1505, column: 20, scope: !715)
!4170 = !DILocation(line: 1505, column: 28, scope: !715)
!4171 = !DILocation(line: 1505, column: 33, scope: !715)
!4172 = !DILocation(line: 1505, column: 25, scope: !715)
!4173 = !DILocation(line: 1505, column: 39, scope: !715)
!4174 = !DILocation(line: 1505, column: 9, scope: !715)
!4175 = !DILocation(line: 1505, column: 45, scope: !715)
!4176 = !DILocation(line: 1505, column: 2, scope: !715)
!4177 = !DILocalVariable(name: "pp", arg: 1, scope: !719, file: !676, line: 101, type: !392)
!4178 = !DILocation(line: 101, column: 29, scope: !719)
!4179 = !DILocalVariable(name: "p", scope: !719, file: !676, line: 103, type: !464)
!4180 = !DILocation(line: 103, column: 23, scope: !719)
!4181 = !DILocation(line: 103, column: 50, scope: !719)
!4182 = !DILocalVariable(name: "p1", scope: !719, file: !676, line: 108, type: !362)
!4183 = !DILocation(line: 108, column: 15, scope: !719)
!4184 = !DILocation(line: 108, column: 20, scope: !719)
!4185 = !DILocalVariable(name: "p0", scope: !719, file: !676, line: 109, type: !362)
!4186 = !DILocation(line: 109, column: 15, scope: !719)
!4187 = !DILocation(line: 109, column: 20, scope: !719)
!4188 = !DILocation(line: 111, column: 11, scope: !719)
!4189 = !DILocation(line: 111, column: 14, scope: !719)
!4190 = !DILocation(line: 111, column: 22, scope: !719)
!4191 = !DILocation(line: 111, column: 20, scope: !719)
!4192 = !DILocation(line: 111, column: 9, scope: !719)
!4193 = !DILocation(line: 111, column: 2, scope: !719)
