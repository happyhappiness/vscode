; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_xz.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.option_value = type { i32, i32, i32 }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_internal_s = type opaque
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.private_data = type { i32, i32, %struct.lzma_stream, [2 x %struct.lzma_filter], %struct.lzma_options_lzma, i64, i8*, i64, i64, i32 }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }

@.str = private unnamed_addr constant [28 x i8] c"archive_write_add_filter_xz\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"xz\00", align 1
@.str.2 = private unnamed_addr constant [30 x i8] c"archive_write_add_filter_lzma\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"lzma\00", align 1
@.str.4 = private unnamed_addr constant [30 x i8] c"archive_write_add_filter_lzip\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"lzip\00", align 1
@.str.6 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.7 = private unnamed_addr constant [43 x i8] c"Can't allocate data for compression buffer\00", align 1
@option_values = internal constant [10 x %struct.option_value] [%struct.option_value { i32 65536, i32 32, i32 3 }, %struct.option_value { i32 1048576, i32 32, i32 3 }, %struct.option_value { i32 1572864, i32 32, i32 4 }, %struct.option_value { i32 2097152, i32 32, i32 20 }, %struct.option_value { i32 3145728, i32 32, i32 20 }, %struct.option_value { i32 4194304, i32 32, i32 20 }, %struct.option_value { i32 8388608, i32 64, i32 20 }, %struct.option_value { i32 16777216, i32 64, i32 20 }, %struct.option_value { i32 25165824, i32 64, i32 20 }, %struct.option_value { i32 33554432, i32 64, i32 20 }], align 16
@.str.8 = private unnamed_addr constant [48 x i8] c"Internal error initializing compression library\00", align 1
@.str.9 = private unnamed_addr constant [28 x i8] c"lzma compression data error\00", align 1
@.str.10 = private unnamed_addr constant [55 x i8] c"lzma compression error: %ju MiB would have been needed\00", align 1
@.str.11 = private unnamed_addr constant [61 x i8] c"lzma compression failed: lzma_code() call returned status %d\00", align 1
@archive_compressor_xz_init_stream.lzma_stream_init_data = internal constant %struct.lzma_stream zeroinitializer, align 8
@.str.12 = private unnamed_addr constant [42 x i8] c"Unacceptable dictionary size for lzip: %d\00", align 1
@.str.13 = private unnamed_addr constant [72 x i8] c"Internal error initializing compression library: Cannot allocate memory\00", align 1
@.str.14 = private unnamed_addr constant [71 x i8] c"Internal error initializing compression library: It's a bug in liblzma\00", align 1
@.str.15 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1
@.str.16 = private unnamed_addr constant [8 x i8] c"threads\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_lzip(%struct.archive* %a) #0 !dbg !334 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !376, metadata !377), !dbg !378
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !379
  call void @__archive_write_filters_free(%struct.archive* %0), !dbg !380
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !381
  %call = call i32 @archive_write_add_filter_lzip(%struct.archive* %1), !dbg !382
  ret i32 %call, !dbg !383
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @__archive_write_filters_free(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_lzip(%struct.archive* %_a) #0 !dbg !340 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !384, metadata !377), !dbg !385
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !386, metadata !377), !dbg !387
  call void @llvm.dbg.declare(metadata i32* %r, metadata !388, metadata !377), !dbg !389
  br label %do.body, !dbg !390

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !391, metadata !377), !dbg !393
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !394
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.4, i32 0, i32 0)), !dbg !394
  store i32 %call, i32* %magic_test, align 4, !dbg !394
  %1 = load i32, i32* %magic_test, align 4, !dbg !394
  %cmp = icmp eq i32 %1, -30, !dbg !394
  br i1 %cmp, label %if.then, label %if.end, !dbg !394

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !396
  br label %return, !dbg !396

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !399

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !401
  %call1 = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !402
  store %struct.archive_write_filter* %call1, %struct.archive_write_filter** %f, align 8, !dbg !403
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !404
  %call2 = call i32 @common_setup(%struct.archive_write_filter* %3), !dbg !405
  store i32 %call2, i32* %r, align 4, !dbg !406
  %4 = load i32, i32* %r, align 4, !dbg !407
  %cmp3 = icmp eq i32 %4, 0, !dbg !409
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !410

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !411
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 10, !dbg !413
  store i32 9, i32* %code, align 8, !dbg !414
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !415
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 9, !dbg !416
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8** %name, align 8, !dbg !417
  br label %if.end5, !dbg !418

if.end5:                                          ; preds = %if.then4, %do.end
  %7 = load i32, i32* %r, align 4, !dbg !419
  store i32 %7, i32* %retval, align 4, !dbg !420
  br label %return, !dbg !420

return:                                           ; preds = %if.end5, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !421
  ret i32 %8, !dbg !421
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_lzma(%struct.archive* %a) #0 !dbg !336 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !422, metadata !377), !dbg !423
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !424
  call void @__archive_write_filters_free(%struct.archive* %0), !dbg !425
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !426
  %call = call i32 @archive_write_add_filter_lzma(%struct.archive* %1), !dbg !427
  ret i32 %call, !dbg !428
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_lzma(%struct.archive* %_a) #0 !dbg !339 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !429, metadata !377), !dbg !430
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !431, metadata !377), !dbg !432
  call void @llvm.dbg.declare(metadata i32* %r, metadata !433, metadata !377), !dbg !434
  br label %do.body, !dbg !435

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !436, metadata !377), !dbg !438
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !439
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.2, i32 0, i32 0)), !dbg !439
  store i32 %call, i32* %magic_test, align 4, !dbg !439
  %1 = load i32, i32* %magic_test, align 4, !dbg !439
  %cmp = icmp eq i32 %1, -30, !dbg !439
  br i1 %cmp, label %if.then, label %if.end, !dbg !439

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !441
  br label %return, !dbg !441

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !444

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !446
  %call1 = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !447
  store %struct.archive_write_filter* %call1, %struct.archive_write_filter** %f, align 8, !dbg !448
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !449
  %call2 = call i32 @common_setup(%struct.archive_write_filter* %3), !dbg !450
  store i32 %call2, i32* %r, align 4, !dbg !451
  %4 = load i32, i32* %r, align 4, !dbg !452
  %cmp3 = icmp eq i32 %4, 0, !dbg !454
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !455

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !456
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 10, !dbg !458
  store i32 5, i32* %code, align 8, !dbg !459
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !460
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 9, !dbg !461
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i8** %name, align 8, !dbg !462
  br label %if.end5, !dbg !463

if.end5:                                          ; preds = %if.then4, %do.end
  %7 = load i32, i32* %r, align 4, !dbg !464
  store i32 %7, i32* %retval, align 4, !dbg !465
  br label %return, !dbg !465

return:                                           ; preds = %if.end5, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !466
  ret i32 %8, !dbg !466
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_compression_xz(%struct.archive* %a) #0 !dbg !337 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !467, metadata !377), !dbg !468
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !469
  call void @__archive_write_filters_free(%struct.archive* %0), !dbg !470
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !471
  %call = call i32 @archive_write_add_filter_xz(%struct.archive* %1), !dbg !472
  ret i32 %call, !dbg !473
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_xz(%struct.archive* %_a) #0 !dbg !338 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !474, metadata !377), !dbg !475
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !476, metadata !377), !dbg !477
  call void @llvm.dbg.declare(metadata i32* %r, metadata !478, metadata !377), !dbg !479
  br label %do.body, !dbg !480

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !481, metadata !377), !dbg !483
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !484
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 -1329217314, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0)), !dbg !484
  store i32 %call, i32* %magic_test, align 4, !dbg !484
  %1 = load i32, i32* %magic_test, align 4, !dbg !484
  %cmp = icmp eq i32 %1, -30, !dbg !484
  br i1 %cmp, label %if.then, label %if.end, !dbg !484

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !486
  br label %return, !dbg !486

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !489

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !491
  %call1 = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %2), !dbg !492
  store %struct.archive_write_filter* %call1, %struct.archive_write_filter** %f, align 8, !dbg !493
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !494
  %call2 = call i32 @common_setup(%struct.archive_write_filter* %3), !dbg !495
  store i32 %call2, i32* %r, align 4, !dbg !496
  %4 = load i32, i32* %r, align 4, !dbg !497
  %cmp3 = icmp eq i32 %4, 0, !dbg !499
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !500

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !501
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 10, !dbg !503
  store i32 6, i32* %code, align 8, !dbg !504
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !505
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 9, !dbg !506
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !507
  br label %if.end5, !dbg !508

if.end5:                                          ; preds = %if.then4, %do.end
  %7 = load i32, i32* %r, align 4, !dbg !509
  store i32 %7, i32* %retval, align 4, !dbg !510
  br label %return, !dbg !510

return:                                           ; preds = %if.end5, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !511
  ret i32 %8, !dbg !511
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @common_setup(%struct.archive_write_filter* %f) #0 !dbg !341 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %a = alloca %struct.archive_write*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !512, metadata !377), !dbg !513
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !514, metadata !377), !dbg !515
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !516, metadata !377), !dbg !517
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !518
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 1, !dbg !519
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !519
  %2 = bitcast %struct.archive* %1 to %struct.archive_write*, !dbg !520
  store %struct.archive_write* %2, %struct.archive_write** %a, align 8, !dbg !517
  %call = call noalias i8* @calloc(i64 1, i64 328) #8, !dbg !521
  %3 = bitcast i8* %call to %struct.private_data*, !dbg !521
  store %struct.private_data* %3, %struct.private_data** %data, align 8, !dbg !522
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !523
  %cmp = icmp eq %struct.private_data* %4, null, !dbg !525
  br i1 %cmp, label %if.then, label %if.end, !dbg !526

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !527
  %archive1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !529
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.6, i32 0, i32 0)), !dbg !530
  store i32 -30, i32* %retval, align 4, !dbg !531
  br label %return, !dbg !531

if.end:                                           ; preds = %entry
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !532
  %7 = bitcast %struct.private_data* %6 to i8*, !dbg !532
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !533
  %data2 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %8, i32 0, i32 8, !dbg !534
  store i8* %7, i8** %data2, align 8, !dbg !535
  %9 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !536
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 0, !dbg !537
  store i32 6, i32* %compression_level, align 8, !dbg !538
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !539
  %threads = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 1, !dbg !540
  store i32 1, i32* %threads, align 4, !dbg !541
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !542
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 4, !dbg !543
  store i32 (%struct.archive_write_filter*)* @archive_compressor_xz_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !544
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !545
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 6, !dbg !546
  store i32 (%struct.archive_write_filter*)* @archive_compressor_xz_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !547
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !548
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 7, !dbg !549
  store i32 (%struct.archive_write_filter*)* @archive_compressor_xz_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !550
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !551
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %14, i32 0, i32 3, !dbg !552
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_compressor_xz_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !553
  store i32 0, i32* %retval, align 4, !dbg !554
  br label %return, !dbg !554

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !555
  ret i32 %15, !dbg !555
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_open(%struct.archive_write_filter* %f) #0 !dbg !342 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  %bs = alloca i64, align 8
  %bpb = alloca i64, align 8
  %val = alloca %struct.option_value*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !556, metadata !377), !dbg !557
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !558, metadata !377), !dbg !559
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !560
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !561
  %1 = load i8*, i8** %data1, align 8, !dbg !561
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !560
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !559
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !562, metadata !377), !dbg !563
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !564
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %3, i32 0, i32 2, !dbg !565
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !565
  %call = call i32 @__archive_write_open_filter(%struct.archive_write_filter* %4), !dbg !566
  store i32 %call, i32* %ret, align 4, !dbg !567
  %5 = load i32, i32* %ret, align 4, !dbg !568
  %cmp = icmp ne i32 %5, 0, !dbg !570
  br i1 %cmp, label %if.then, label %if.end, !dbg !571

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %ret, align 4, !dbg !572
  store i32 %6, i32* %retval, align 4, !dbg !573
  br label %return, !dbg !573

if.end:                                           ; preds = %entry
  %7 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !574
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %7, i32 0, i32 6, !dbg !576
  %8 = load i8*, i8** %compressed, align 8, !dbg !576
  %cmp2 = icmp eq i8* %8, null, !dbg !577
  br i1 %cmp2, label %if.then3, label %if.end26, !dbg !578

if.then3:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %bs, metadata !579, metadata !377), !dbg !581
  store i64 65536, i64* %bs, align 8, !dbg !581
  call void @llvm.dbg.declare(metadata i64* %bpb, metadata !582, metadata !377), !dbg !583
  %9 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !584
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %9, i32 0, i32 1, !dbg !586
  %10 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !586
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %10, i32 0, i32 0, !dbg !587
  %11 = load i32, i32* %magic, align 8, !dbg !587
  %cmp4 = icmp eq i32 %11, -1329217314, !dbg !588
  br i1 %cmp4, label %if.then5, label %if.end16, !dbg !589

if.then5:                                         ; preds = %if.then3
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !590
  %archive6 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 1, !dbg !592
  %13 = load %struct.archive*, %struct.archive** %archive6, align 8, !dbg !592
  %call7 = call i32 @archive_write_get_bytes_per_block(%struct.archive* %13), !dbg !593
  %conv = sext i32 %call7 to i64, !dbg !593
  store i64 %conv, i64* %bpb, align 8, !dbg !594
  %14 = load i64, i64* %bpb, align 8, !dbg !595
  %15 = load i64, i64* %bs, align 8, !dbg !597
  %cmp8 = icmp ugt i64 %14, %15, !dbg !598
  br i1 %cmp8, label %if.then10, label %if.else, !dbg !599

if.then10:                                        ; preds = %if.then5
  %16 = load i64, i64* %bpb, align 8, !dbg !600
  store i64 %16, i64* %bs, align 8, !dbg !601
  br label %if.end15, !dbg !602

if.else:                                          ; preds = %if.then5
  %17 = load i64, i64* %bpb, align 8, !dbg !603
  %cmp11 = icmp ne i64 %17, 0, !dbg !605
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !606

if.then13:                                        ; preds = %if.else
  %18 = load i64, i64* %bs, align 8, !dbg !607
  %19 = load i64, i64* %bpb, align 8, !dbg !608
  %rem = urem i64 %18, %19, !dbg !609
  %20 = load i64, i64* %bs, align 8, !dbg !610
  %sub = sub i64 %20, %rem, !dbg !610
  store i64 %sub, i64* %bs, align 8, !dbg !610
  br label %if.end14, !dbg !611

if.end14:                                         ; preds = %if.then13, %if.else
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.then10
  br label %if.end16, !dbg !612

if.end16:                                         ; preds = %if.end15, %if.then3
  %21 = load i64, i64* %bs, align 8, !dbg !613
  %22 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !614
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 7, !dbg !615
  store i64 %21, i64* %compressed_buffer_size, align 8, !dbg !616
  %23 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !617
  %compressed_buffer_size17 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 7, !dbg !618
  %24 = load i64, i64* %compressed_buffer_size17, align 8, !dbg !618
  %call18 = call noalias i8* @malloc(i64 %24) #8, !dbg !619
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !620
  %compressed19 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 6, !dbg !621
  store i8* %call18, i8** %compressed19, align 8, !dbg !622
  %26 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !623
  %compressed20 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 6, !dbg !625
  %27 = load i8*, i8** %compressed20, align 8, !dbg !625
  %cmp21 = icmp eq i8* %27, null, !dbg !626
  br i1 %cmp21, label %if.then23, label %if.end25, !dbg !627

if.then23:                                        ; preds = %if.end16
  %28 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !628
  %archive24 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %28, i32 0, i32 1, !dbg !630
  %29 = load %struct.archive*, %struct.archive** %archive24, align 8, !dbg !630
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %29, i32 12, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.7, i32 0, i32 0)), !dbg !631
  store i32 -30, i32* %retval, align 4, !dbg !632
  br label %return, !dbg !632

if.end25:                                         ; preds = %if.end16
  br label %if.end26, !dbg !633

if.end26:                                         ; preds = %if.end25, %if.end
  %30 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !634
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %30, i32 0, i32 5, !dbg !635
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_compressor_xz_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !636
  %31 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !637
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %31, i32 0, i32 10, !dbg !639
  %32 = load i32, i32* %code, align 8, !dbg !639
  %cmp27 = icmp eq i32 %32, 9, !dbg !640
  br i1 %cmp27, label %if.then29, label %if.else52, !dbg !641

if.then29:                                        ; preds = %if.end26
  call void @llvm.dbg.declare(metadata %struct.option_value** %val, metadata !642, metadata !377), !dbg !645
  %33 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !646
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 0, !dbg !647
  %34 = load i32, i32* %compression_level, align 8, !dbg !647
  %idxprom = sext i32 %34 to i64, !dbg !648
  %arrayidx = getelementptr inbounds [10 x %struct.option_value], [10 x %struct.option_value]* @option_values, i64 0, i64 %idxprom, !dbg !648
  store %struct.option_value* %arrayidx, %struct.option_value** %val, align 8, !dbg !645
  %35 = load %struct.option_value*, %struct.option_value** %val, align 8, !dbg !649
  %dict_size = getelementptr inbounds %struct.option_value, %struct.option_value* %35, i32 0, i32 0, !dbg !650
  %36 = load i32, i32* %dict_size, align 4, !dbg !650
  %37 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !651
  %lzma_opt = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 4, !dbg !652
  %dict_size30 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt, i32 0, i32 0, !dbg !653
  store i32 %36, i32* %dict_size30, align 8, !dbg !654
  %38 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !655
  %lzma_opt31 = getelementptr inbounds %struct.private_data, %struct.private_data* %38, i32 0, i32 4, !dbg !656
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt31, i32 0, i32 1, !dbg !657
  store i8* null, i8** %preset_dict, align 8, !dbg !658
  %39 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !659
  %lzma_opt32 = getelementptr inbounds %struct.private_data, %struct.private_data* %39, i32 0, i32 4, !dbg !660
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt32, i32 0, i32 2, !dbg !661
  store i32 0, i32* %preset_dict_size, align 8, !dbg !662
  %40 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !663
  %lzma_opt33 = getelementptr inbounds %struct.private_data, %struct.private_data* %40, i32 0, i32 4, !dbg !664
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt33, i32 0, i32 3, !dbg !665
  store i32 3, i32* %lc, align 4, !dbg !666
  %41 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !667
  %lzma_opt34 = getelementptr inbounds %struct.private_data, %struct.private_data* %41, i32 0, i32 4, !dbg !668
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt34, i32 0, i32 4, !dbg !669
  store i32 0, i32* %lp, align 8, !dbg !670
  %42 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !671
  %lzma_opt35 = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 4, !dbg !672
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt35, i32 0, i32 5, !dbg !673
  store i32 2, i32* %pb, align 4, !dbg !674
  %43 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !675
  %compression_level36 = getelementptr inbounds %struct.private_data, %struct.private_data* %43, i32 0, i32 0, !dbg !676
  %44 = load i32, i32* %compression_level36, align 8, !dbg !676
  %cmp37 = icmp sle i32 %44, 2, !dbg !677
  %cond = select i1 %cmp37, i32 1, i32 2, !dbg !675
  %45 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !678
  %lzma_opt39 = getelementptr inbounds %struct.private_data, %struct.private_data* %45, i32 0, i32 4, !dbg !679
  %mode = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt39, i32 0, i32 6, !dbg !680
  store i32 %cond, i32* %mode, align 8, !dbg !681
  %46 = load %struct.option_value*, %struct.option_value** %val, align 8, !dbg !682
  %nice_len = getelementptr inbounds %struct.option_value, %struct.option_value* %46, i32 0, i32 1, !dbg !683
  %47 = load i32, i32* %nice_len, align 4, !dbg !683
  %48 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !684
  %lzma_opt40 = getelementptr inbounds %struct.private_data, %struct.private_data* %48, i32 0, i32 4, !dbg !685
  %nice_len41 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt40, i32 0, i32 7, !dbg !686
  store i32 %47, i32* %nice_len41, align 4, !dbg !687
  %49 = load %struct.option_value*, %struct.option_value** %val, align 8, !dbg !688
  %mf = getelementptr inbounds %struct.option_value, %struct.option_value* %49, i32 0, i32 2, !dbg !689
  %50 = load i32, i32* %mf, align 4, !dbg !689
  %51 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !690
  %lzma_opt42 = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 4, !dbg !691
  %mf43 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt42, i32 0, i32 8, !dbg !692
  store i32 %50, i32* %mf43, align 8, !dbg !693
  %52 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !694
  %lzma_opt44 = getelementptr inbounds %struct.private_data, %struct.private_data* %52, i32 0, i32 4, !dbg !695
  %depth = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt44, i32 0, i32 9, !dbg !696
  store i32 0, i32* %depth, align 4, !dbg !697
  %53 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !698
  %lzmafilters = getelementptr inbounds %struct.private_data, %struct.private_data* %53, i32 0, i32 3, !dbg !699
  %arrayidx45 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters, i64 0, i64 0, !dbg !698
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx45, i32 0, i32 0, !dbg !700
  store i64 4611686018427387905, i64* %id, align 8, !dbg !701
  %54 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !702
  %lzma_opt46 = getelementptr inbounds %struct.private_data, %struct.private_data* %54, i32 0, i32 4, !dbg !703
  %55 = bitcast %struct.lzma_options_lzma* %lzma_opt46 to i8*, !dbg !704
  %56 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !705
  %lzmafilters47 = getelementptr inbounds %struct.private_data, %struct.private_data* %56, i32 0, i32 3, !dbg !706
  %arrayidx48 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters47, i64 0, i64 0, !dbg !705
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx48, i32 0, i32 1, !dbg !707
  store i8* %55, i8** %options, align 8, !dbg !708
  %57 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !709
  %lzmafilters49 = getelementptr inbounds %struct.private_data, %struct.private_data* %57, i32 0, i32 3, !dbg !710
  %arrayidx50 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters49, i64 0, i64 1, !dbg !709
  %id51 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx50, i32 0, i32 0, !dbg !711
  store i64 -1, i64* %id51, align 8, !dbg !712
  br label %if.end69, !dbg !713

if.else52:                                        ; preds = %if.end26
  %58 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !714
  %lzma_opt53 = getelementptr inbounds %struct.private_data, %struct.private_data* %58, i32 0, i32 4, !dbg !717
  %59 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !718
  %compression_level54 = getelementptr inbounds %struct.private_data, %struct.private_data* %59, i32 0, i32 0, !dbg !719
  %60 = load i32, i32* %compression_level54, align 8, !dbg !719
  %call55 = call zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma* %lzma_opt53, i32 %60) #8, !dbg !720
  %tobool = icmp ne i8 %call55, 0, !dbg !720
  br i1 %tobool, label %if.then56, label %if.end58, !dbg !721

if.then56:                                        ; preds = %if.else52
  %61 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !722
  %archive57 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %61, i32 0, i32 1, !dbg !724
  %62 = load %struct.archive*, %struct.archive** %archive57, align 8, !dbg !724
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %62, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.8, i32 0, i32 0)), !dbg !725
  br label %if.end58, !dbg !726

if.end58:                                         ; preds = %if.then56, %if.else52
  %63 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !727
  %lzmafilters59 = getelementptr inbounds %struct.private_data, %struct.private_data* %63, i32 0, i32 3, !dbg !728
  %arrayidx60 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters59, i64 0, i64 0, !dbg !727
  %id61 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx60, i32 0, i32 0, !dbg !729
  store i64 33, i64* %id61, align 8, !dbg !730
  %64 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !731
  %lzma_opt62 = getelementptr inbounds %struct.private_data, %struct.private_data* %64, i32 0, i32 4, !dbg !732
  %65 = bitcast %struct.lzma_options_lzma* %lzma_opt62 to i8*, !dbg !733
  %66 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !734
  %lzmafilters63 = getelementptr inbounds %struct.private_data, %struct.private_data* %66, i32 0, i32 3, !dbg !735
  %arrayidx64 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters63, i64 0, i64 0, !dbg !734
  %options65 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx64, i32 0, i32 1, !dbg !736
  store i8* %65, i8** %options65, align 8, !dbg !737
  %67 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !738
  %lzmafilters66 = getelementptr inbounds %struct.private_data, %struct.private_data* %67, i32 0, i32 3, !dbg !739
  %arrayidx67 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters66, i64 0, i64 1, !dbg !738
  %id68 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx67, i32 0, i32 0, !dbg !740
  store i64 -1, i64* %id68, align 8, !dbg !741
  br label %if.end69

if.end69:                                         ; preds = %if.end58, %if.then29
  %68 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !742
  %69 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !743
  %call70 = call i32 @archive_compressor_xz_init_stream(%struct.archive_write_filter* %68, %struct.private_data* %69), !dbg !744
  store i32 %call70, i32* %ret, align 4, !dbg !745
  %70 = load i32, i32* %ret, align 4, !dbg !746
  %cmp71 = icmp eq i32 %70, 0, !dbg !748
  br i1 %cmp71, label %if.then73, label %if.end75, !dbg !749

if.then73:                                        ; preds = %if.end69
  %71 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !750
  %72 = bitcast %struct.private_data* %71 to i8*, !dbg !750
  %73 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !752
  %data74 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %73, i32 0, i32 8, !dbg !753
  store i8* %72, i8** %data74, align 8, !dbg !754
  store i32 0, i32* %retval, align 4, !dbg !755
  br label %return, !dbg !755

if.end75:                                         ; preds = %if.end69
  store i32 -30, i32* %retval, align 4, !dbg !756
  br label %return, !dbg !756

return:                                           ; preds = %if.end75, %if.then73, %if.then23, %if.then
  %74 = load i32, i32* %retval, align 4, !dbg !757
  ret i32 %74, !dbg !757
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_close(%struct.archive_write_filter* %f) #0 !dbg !350 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  %r1 = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !758, metadata !377), !dbg !759
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !760, metadata !377), !dbg !761
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !762
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !763
  %1 = load i8*, i8** %data1, align 8, !dbg !763
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !764
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !761
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !765, metadata !377), !dbg !766
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !767, metadata !377), !dbg !768
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !769
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !770
  %call = call i32 @drive_compressor(%struct.archive_write_filter* %3, %struct.private_data* %4, i32 1), !dbg !771
  store i32 %call, i32* %ret, align 4, !dbg !772
  %5 = load i32, i32* %ret, align 4, !dbg !773
  %cmp = icmp eq i32 %5, 0, !dbg !775
  br i1 %cmp, label %if.then, label %if.end19, !dbg !776

if.then:                                          ; preds = %entry
  %6 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !777
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 7, !dbg !779
  %7 = load i64, i64* %compressed_buffer_size, align 8, !dbg !779
  %8 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !780
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 2, !dbg !781
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream, i32 0, i32 4, !dbg !782
  %9 = load i64, i64* %avail_out, align 8, !dbg !782
  %sub = sub i64 %7, %9, !dbg !783
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !784
  %total_out = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 8, !dbg !785
  %11 = load i64, i64* %total_out, align 8, !dbg !786
  %add = add i64 %11, %sub, !dbg !786
  store i64 %add, i64* %total_out, align 8, !dbg !786
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !787
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 2, !dbg !788
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !788
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !789
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 6, !dbg !790
  %15 = load i8*, i8** %compressed, align 8, !dbg !790
  %16 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !791
  %compressed_buffer_size2 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 7, !dbg !792
  %17 = load i64, i64* %compressed_buffer_size2, align 8, !dbg !792
  %18 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !793
  %stream3 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 2, !dbg !794
  %avail_out4 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream3, i32 0, i32 4, !dbg !795
  %19 = load i64, i64* %avail_out4, align 8, !dbg !795
  %sub5 = sub i64 %17, %19, !dbg !796
  %call6 = call i32 @__archive_write_filter(%struct.archive_write_filter* %13, i8* %15, i64 %sub5), !dbg !797
  store i32 %call6, i32* %ret, align 4, !dbg !798
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !799
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 10, !dbg !801
  %21 = load i32, i32* %code, align 8, !dbg !801
  %cmp7 = icmp eq i32 %21, 9, !dbg !802
  br i1 %cmp7, label %land.lhs.true, label %if.end, !dbg !803

land.lhs.true:                                    ; preds = %if.then
  %22 = load i32, i32* %ret, align 4, !dbg !804
  %cmp8 = icmp eq i32 %22, 0, !dbg !806
  br i1 %cmp8, label %if.then9, label %if.end, !dbg !807

if.then9:                                         ; preds = %land.lhs.true
  %23 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !808
  %compressed10 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 6, !dbg !810
  %24 = load i8*, i8** %compressed10, align 8, !dbg !810
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !811
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 9, !dbg !812
  %26 = load i32, i32* %crc32, align 8, !dbg !812
  call void @archive_le32enc(i8* %24, i32 %26), !dbg !813
  %27 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !814
  %compressed11 = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 6, !dbg !815
  %28 = load i8*, i8** %compressed11, align 8, !dbg !815
  %add.ptr = getelementptr inbounds i8, i8* %28, i64 4, !dbg !816
  %29 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !817
  %total_in = getelementptr inbounds %struct.private_data, %struct.private_data* %29, i32 0, i32 5, !dbg !818
  %30 = load i64, i64* %total_in, align 8, !dbg !818
  call void @archive_le64enc(i8* %add.ptr, i64 %30), !dbg !819
  %31 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !820
  %compressed12 = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 6, !dbg !821
  %32 = load i8*, i8** %compressed12, align 8, !dbg !821
  %add.ptr13 = getelementptr inbounds i8, i8* %32, i64 12, !dbg !822
  %33 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !823
  %total_out14 = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 8, !dbg !824
  %34 = load i64, i64* %total_out14, align 8, !dbg !824
  %add15 = add nsw i64 %34, 20, !dbg !825
  call void @archive_le64enc(i8* %add.ptr13, i64 %add15), !dbg !826
  %35 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !827
  %next_filter16 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %35, i32 0, i32 2, !dbg !828
  %36 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter16, align 8, !dbg !828
  %37 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !829
  %compressed17 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 6, !dbg !830
  %38 = load i8*, i8** %compressed17, align 8, !dbg !830
  %call18 = call i32 @__archive_write_filter(%struct.archive_write_filter* %36, i8* %38, i64 20), !dbg !831
  store i32 %call18, i32* %ret, align 4, !dbg !832
  br label %if.end, !dbg !833

if.end:                                           ; preds = %if.then9, %land.lhs.true, %if.then
  br label %if.end19, !dbg !834

if.end19:                                         ; preds = %if.end, %entry
  %39 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !835
  %stream20 = getelementptr inbounds %struct.private_data, %struct.private_data* %39, i32 0, i32 2, !dbg !836
  call void @lzma_end(%struct.lzma_stream* %stream20) #8, !dbg !837
  %40 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !838
  %next_filter21 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %40, i32 0, i32 2, !dbg !839
  %41 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter21, align 8, !dbg !839
  %call22 = call i32 @__archive_write_close_filter(%struct.archive_write_filter* %41), !dbg !840
  store i32 %call22, i32* %r1, align 4, !dbg !841
  %42 = load i32, i32* %r1, align 4, !dbg !842
  %43 = load i32, i32* %ret, align 4, !dbg !843
  %cmp23 = icmp slt i32 %42, %43, !dbg !844
  br i1 %cmp23, label %cond.true, label %cond.false, !dbg !842

cond.true:                                        ; preds = %if.end19
  %44 = load i32, i32* %r1, align 4, !dbg !845
  br label %cond.end, !dbg !847

cond.false:                                       ; preds = %if.end19
  %45 = load i32, i32* %ret, align 4, !dbg !848
  br label %cond.end, !dbg !850

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %44, %cond.true ], [ %45, %cond.false ], !dbg !851
  ret i32 %cond, !dbg !853
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_free(%struct.archive_write_filter* %f) #0 !dbg !358 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !854, metadata !377), !dbg !855
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !856, metadata !377), !dbg !857
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !858
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !859
  %1 = load i8*, i8** %data1, align 8, !dbg !859
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !860
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !857
  %3 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !861
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 6, !dbg !862
  %4 = load i8*, i8** %compressed, align 8, !dbg !862
  call void @free(i8* %4) #8, !dbg !863
  %5 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !864
  %6 = bitcast %struct.private_data* %5 to i8*, !dbg !864
  call void @free(i8* %6) #8, !dbg !865
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !866
  %data2 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 8, !dbg !867
  store i8* null, i8** %data2, align 8, !dbg !868
  ret i32 0, !dbg !869
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !359 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %data = alloca %struct.private_data*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !870, metadata !377), !dbg !871
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !872, metadata !377), !dbg !873
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !874, metadata !377), !dbg !875
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !876, metadata !377), !dbg !877
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !878
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !879
  %1 = load i8*, i8** %data1, align 8, !dbg !879
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !880
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !877
  %3 = load i8*, i8** %key.addr, align 8, !dbg !881
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.15, i32 0, i32 0)) #9, !dbg !883
  %cmp = icmp eq i32 %call, 0, !dbg !884
  br i1 %cmp, label %if.then, label %if.else, !dbg !885

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %value.addr, align 8, !dbg !886
  %cmp2 = icmp eq i8* %4, null, !dbg !889
  br i1 %cmp2, label %if.then14, label %lor.lhs.false, !dbg !890

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !891
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !891
  %6 = load i8, i8* %arrayidx, align 1, !dbg !891
  %conv = sext i8 %6 to i32, !dbg !891
  %cmp3 = icmp sge i32 %conv, 48, !dbg !893
  br i1 %cmp3, label %land.lhs.true, label %if.then14, !dbg !894

land.lhs.true:                                    ; preds = %lor.lhs.false
  %7 = load i8*, i8** %value.addr, align 8, !dbg !895
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !895
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !895
  %conv6 = sext i8 %8 to i32, !dbg !895
  %cmp7 = icmp sle i32 %conv6, 57, !dbg !897
  br i1 %cmp7, label %lor.lhs.false9, label %if.then14, !dbg !898

lor.lhs.false9:                                   ; preds = %land.lhs.true
  %9 = load i8*, i8** %value.addr, align 8, !dbg !899
  %arrayidx10 = getelementptr inbounds i8, i8* %9, i64 1, !dbg !899
  %10 = load i8, i8* %arrayidx10, align 1, !dbg !899
  %conv11 = sext i8 %10 to i32, !dbg !899
  %cmp12 = icmp ne i32 %conv11, 0, !dbg !900
  br i1 %cmp12, label %if.then14, label %if.end, !dbg !901

if.then14:                                        ; preds = %lor.lhs.false9, %land.lhs.true, %lor.lhs.false, %if.then
  store i32 -20, i32* %retval, align 4, !dbg !903
  br label %return, !dbg !903

if.end:                                           ; preds = %lor.lhs.false9
  %11 = load i8*, i8** %value.addr, align 8, !dbg !904
  %arrayidx15 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !904
  %12 = load i8, i8* %arrayidx15, align 1, !dbg !904
  %conv16 = sext i8 %12 to i32, !dbg !904
  %sub = sub nsw i32 %conv16, 48, !dbg !905
  %13 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !906
  %compression_level = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 0, !dbg !907
  store i32 %sub, i32* %compression_level, align 8, !dbg !908
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !909
  %compression_level17 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 0, !dbg !911
  %15 = load i32, i32* %compression_level17, align 8, !dbg !911
  %cmp18 = icmp sgt i32 %15, 6, !dbg !912
  br i1 %cmp18, label %if.then20, label %if.end22, !dbg !913

if.then20:                                        ; preds = %if.end
  %16 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !914
  %compression_level21 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 0, !dbg !915
  store i32 6, i32* %compression_level21, align 8, !dbg !916
  br label %if.end22, !dbg !914

if.end22:                                         ; preds = %if.then20, %if.end
  store i32 0, i32* %retval, align 4, !dbg !917
  br label %return, !dbg !917

if.else:                                          ; preds = %entry
  %17 = load i8*, i8** %key.addr, align 8, !dbg !918
  %call23 = call i32 @strcmp(i8* %17, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.16, i32 0, i32 0)) #9, !dbg !920
  %cmp24 = icmp eq i32 %call23, 0, !dbg !921
  br i1 %cmp24, label %if.then26, label %if.end49, !dbg !922

if.then26:                                        ; preds = %if.else
  %18 = load i8*, i8** %value.addr, align 8, !dbg !923
  %cmp27 = icmp eq i8* %18, null, !dbg !926
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !927

if.then29:                                        ; preds = %if.then26
  store i32 -20, i32* %retval, align 4, !dbg !928
  br label %return, !dbg !928

if.end30:                                         ; preds = %if.then26
  %19 = load i8*, i8** %value.addr, align 8, !dbg !929
  %call31 = call i64 @strtoul(i8* %19, i8** null, i32 10) #8, !dbg !930
  %conv32 = trunc i64 %call31 to i32, !dbg !931
  %20 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !932
  %threads = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 1, !dbg !933
  store i32 %conv32, i32* %threads, align 4, !dbg !934
  %21 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !935
  %threads33 = getelementptr inbounds %struct.private_data, %struct.private_data* %21, i32 0, i32 1, !dbg !937
  %22 = load i32, i32* %threads33, align 4, !dbg !937
  %cmp34 = icmp eq i32 %22, 0, !dbg !938
  br i1 %cmp34, label %land.lhs.true36, label %if.end42, !dbg !939

land.lhs.true36:                                  ; preds = %if.end30
  %call37 = call i32* @__errno_location() #1, !dbg !940
  %23 = load i32, i32* %call37, align 4, !dbg !940
  %cmp38 = icmp ne i32 %23, 0, !dbg !942
  br i1 %cmp38, label %if.then40, label %if.end42, !dbg !943

if.then40:                                        ; preds = %land.lhs.true36
  %24 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !944
  %threads41 = getelementptr inbounds %struct.private_data, %struct.private_data* %24, i32 0, i32 1, !dbg !946
  store i32 1, i32* %threads41, align 4, !dbg !947
  store i32 -20, i32* %retval, align 4, !dbg !948
  br label %return, !dbg !948

if.end42:                                         ; preds = %land.lhs.true36, %if.end30
  %25 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !949
  %threads43 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 1, !dbg !951
  %26 = load i32, i32* %threads43, align 4, !dbg !951
  %cmp44 = icmp eq i32 %26, 0, !dbg !952
  br i1 %cmp44, label %if.then46, label %if.end48, !dbg !953

if.then46:                                        ; preds = %if.end42
  %27 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !954
  %threads47 = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 1, !dbg !956
  store i32 1, i32* %threads47, align 4, !dbg !957
  br label %if.end48, !dbg !958

if.end48:                                         ; preds = %if.then46, %if.end42
  store i32 0, i32* %retval, align 4, !dbg !959
  br label %return, !dbg !959

if.end49:                                         ; preds = %if.else
  br label %if.end50

if.end50:                                         ; preds = %if.end49
  store i32 -20, i32* %retval, align 4, !dbg !960
  br label %return, !dbg !960

return:                                           ; preds = %if.end50, %if.end48, %if.then40, %if.then29, %if.end22, %if.then14
  %28 = load i32, i32* %retval, align 4, !dbg !961
  ret i32 %28, !dbg !961
}

declare i32 @__archive_write_open_filter(%struct.archive_write_filter*) #2

declare i32 @archive_write_get_bytes_per_block(%struct.archive*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !343 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !962, metadata !377), !dbg !963
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !964, metadata !377), !dbg !965
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !966, metadata !377), !dbg !967
  call void @llvm.dbg.declare(metadata %struct.private_data** %data, metadata !968, metadata !377), !dbg !969
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !970
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !971
  %1 = load i8*, i8** %data1, align 8, !dbg !971
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !972
  store %struct.private_data* %2, %struct.private_data** %data, align 8, !dbg !969
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !973, metadata !377), !dbg !974
  %3 = load i64, i64* %length.addr, align 8, !dbg !975
  %4 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !976
  %total_in = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 5, !dbg !977
  %5 = load i64, i64* %total_in, align 8, !dbg !978
  %add = add i64 %5, %3, !dbg !978
  store i64 %add, i64* %total_in, align 8, !dbg !978
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !979
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 10, !dbg !981
  %7 = load i32, i32* %code, align 8, !dbg !981
  %cmp = icmp eq i32 %7, 9, !dbg !982
  br i1 %cmp, label %if.then, label %if.end, !dbg !983

if.then:                                          ; preds = %entry
  %8 = load i8*, i8** %buff.addr, align 8, !dbg !984
  %9 = load i64, i64* %length.addr, align 8, !dbg !985
  %10 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !986
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 9, !dbg !987
  %11 = load i32, i32* %crc32, align 8, !dbg !987
  %call = call i32 @lzma_crc32(i8* %8, i64 %9, i32 %11) #9, !dbg !988
  %12 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !989
  %crc322 = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 9, !dbg !990
  store i32 %call, i32* %crc322, align 8, !dbg !991
  br label %if.end, !dbg !989

if.end:                                           ; preds = %if.then, %entry
  %13 = load i8*, i8** %buff.addr, align 8, !dbg !992
  %14 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !993
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 2, !dbg !994
  %next_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream, i32 0, i32 0, !dbg !995
  store i8* %13, i8** %next_in, align 8, !dbg !996
  %15 = load i64, i64* %length.addr, align 8, !dbg !997
  %16 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !998
  %stream3 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 2, !dbg !999
  %avail_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream3, i32 0, i32 1, !dbg !1000
  store i64 %15, i64* %avail_in, align 8, !dbg !1001
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1002
  %18 = load %struct.private_data*, %struct.private_data** %data, align 8, !dbg !1004
  %call4 = call i32 @drive_compressor(%struct.archive_write_filter* %17, %struct.private_data* %18, i32 0), !dbg !1005
  store i32 %call4, i32* %ret, align 4, !dbg !1006
  %cmp5 = icmp ne i32 %call4, 0, !dbg !1007
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1008

if.then6:                                         ; preds = %if.end
  %19 = load i32, i32* %ret, align 4, !dbg !1009
  store i32 %19, i32* %retval, align 4, !dbg !1010
  br label %return, !dbg !1010

if.end7:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1011
  br label %return, !dbg !1011

return:                                           ; preds = %if.end7, %if.then6
  %20 = load i32, i32* %retval, align 4, !dbg !1012
  ret i32 %20, !dbg !1012
}

; Function Attrs: nounwind
declare zeroext i8 @lzma_lzma_preset(%struct.lzma_options_lzma*, i32) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_compressor_xz_init_stream(%struct.archive_write_filter* %f, %struct.private_data* %data) #0 !dbg !347 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  %dict_size = alloca i32, align 4
  %ds = alloca i32, align 4
  %log2dic = alloca i32, align 4
  %wedges = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !1013, metadata !377), !dbg !1014
  store %struct.private_data* %data, %struct.private_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.private_data** %data.addr, metadata !1015, metadata !377), !dbg !1016
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1017, metadata !377), !dbg !1018
  %0 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1019
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %0, i32 0, i32 2, !dbg !1020
  %1 = bitcast %struct.lzma_stream* %stream to i8*, !dbg !1021
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %1, i8* bitcast (%struct.lzma_stream* @archive_compressor_xz_init_stream.lzma_stream_init_data to i8*), i64 136, i32 8, i1 false), !dbg !1021
  %2 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1022
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %2, i32 0, i32 6, !dbg !1023
  %3 = load i8*, i8** %compressed, align 8, !dbg !1023
  %4 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1024
  %stream1 = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 2, !dbg !1025
  %next_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream1, i32 0, i32 3, !dbg !1026
  store i8* %3, i8** %next_out, align 8, !dbg !1027
  %5 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1028
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 7, !dbg !1029
  %6 = load i64, i64* %compressed_buffer_size, align 8, !dbg !1029
  %7 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1030
  %stream2 = getelementptr inbounds %struct.private_data, %struct.private_data* %7, i32 0, i32 2, !dbg !1031
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream2, i32 0, i32 4, !dbg !1032
  store i64 %6, i64* %avail_out, align 8, !dbg !1033
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1034
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %8, i32 0, i32 10, !dbg !1036
  %9 = load i32, i32* %code, align 8, !dbg !1036
  %cmp = icmp eq i32 %9, 6, !dbg !1037
  br i1 %cmp, label %if.then, label %if.else, !dbg !1038

if.then:                                          ; preds = %entry
  %10 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1039
  %stream3 = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 2, !dbg !1041
  %11 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1042
  %lzmafilters = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 3, !dbg !1043
  %arraydecay = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters, i32 0, i32 0, !dbg !1042
  %call = call i32 @lzma_stream_encoder(%struct.lzma_stream* %stream3, %struct.lzma_filter* %arraydecay, i32 4) #8, !dbg !1044
  store i32 %call, i32* %ret, align 4, !dbg !1045
  br label %if.end50, !dbg !1046

if.else:                                          ; preds = %entry
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1047
  %code4 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 10, !dbg !1050
  %13 = load i32, i32* %code4, align 8, !dbg !1050
  %cmp5 = icmp eq i32 %13, 5, !dbg !1051
  br i1 %cmp5, label %if.then6, label %if.else9, !dbg !1047

if.then6:                                         ; preds = %if.else
  %14 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1052
  %stream7 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 2, !dbg !1054
  %15 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1055
  %lzma_opt = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 4, !dbg !1056
  %call8 = call i32 @lzma_alone_encoder(%struct.lzma_stream* %stream7, %struct.lzma_options_lzma* %lzma_opt) #8, !dbg !1057
  store i32 %call8, i32* %ret, align 4, !dbg !1058
  br label %if.end49, !dbg !1059

if.else9:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i32* %dict_size, metadata !1060, metadata !377), !dbg !1062
  %16 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1063
  %lzma_opt10 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 4, !dbg !1064
  %dict_size11 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %lzma_opt10, i32 0, i32 0, !dbg !1065
  %17 = load i32, i32* %dict_size11, align 8, !dbg !1065
  store i32 %17, i32* %dict_size, align 4, !dbg !1062
  call void @llvm.dbg.declare(metadata i32* %ds, metadata !1066, metadata !377), !dbg !1067
  call void @llvm.dbg.declare(metadata i32* %log2dic, metadata !1068, metadata !377), !dbg !1069
  call void @llvm.dbg.declare(metadata i32* %wedges, metadata !1070, metadata !377), !dbg !1071
  %18 = load i32, i32* %dict_size, align 4, !dbg !1072
  %cmp12 = icmp slt i32 %18, 4096, !dbg !1074
  br i1 %cmp12, label %if.then14, label %lor.lhs.false, !dbg !1075

lor.lhs.false:                                    ; preds = %if.else9
  %19 = load i32, i32* %dict_size, align 4, !dbg !1076
  %cmp13 = icmp sgt i32 %19, 134217728, !dbg !1078
  br i1 %cmp13, label %if.then14, label %if.end, !dbg !1079

if.then14:                                        ; preds = %lor.lhs.false, %if.else9
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1080
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 1, !dbg !1082
  %21 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1082
  %22 = load i32, i32* %dict_size, align 4, !dbg !1083
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %21, i32 -1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.12, i32 0, i32 0), i32 %22), !dbg !1084
  store i32 -30, i32* %retval, align 4, !dbg !1085
  br label %return, !dbg !1085

if.end:                                           ; preds = %lor.lhs.false
  store i32 27, i32* %log2dic, align 4, !dbg !1086
  br label %for.cond, !dbg !1088

for.cond:                                         ; preds = %for.inc, %if.end
  %23 = load i32, i32* %log2dic, align 4, !dbg !1089
  %cmp15 = icmp sge i32 %23, 12, !dbg !1092
  br i1 %cmp15, label %for.body, label %for.end, !dbg !1093

for.body:                                         ; preds = %for.cond
  %24 = load i32, i32* %dict_size, align 4, !dbg !1094
  %25 = load i32, i32* %log2dic, align 4, !dbg !1097
  %shl = shl i32 1, %25, !dbg !1098
  %and = and i32 %24, %shl, !dbg !1099
  %tobool = icmp ne i32 %and, 0, !dbg !1099
  br i1 %tobool, label %if.then16, label %if.end17, !dbg !1100

if.then16:                                        ; preds = %for.body
  br label %for.end, !dbg !1101

if.end17:                                         ; preds = %for.body
  br label %for.inc, !dbg !1102

for.inc:                                          ; preds = %if.end17
  %26 = load i32, i32* %log2dic, align 4, !dbg !1103
  %dec = add nsw i32 %26, -1, !dbg !1103
  store i32 %dec, i32* %log2dic, align 4, !dbg !1103
  br label %for.cond, !dbg !1105

for.end:                                          ; preds = %if.then16, %for.cond
  %27 = load i32, i32* %dict_size, align 4, !dbg !1106
  %28 = load i32, i32* %log2dic, align 4, !dbg !1108
  %shl18 = shl i32 1, %28, !dbg !1109
  %cmp19 = icmp sgt i32 %27, %shl18, !dbg !1110
  br i1 %cmp19, label %if.then20, label %if.else24, !dbg !1111

if.then20:                                        ; preds = %for.end
  %29 = load i32, i32* %log2dic, align 4, !dbg !1112
  %inc = add nsw i32 %29, 1, !dbg !1112
  store i32 %inc, i32* %log2dic, align 4, !dbg !1112
  %30 = load i32, i32* %log2dic, align 4, !dbg !1114
  %shl21 = shl i32 1, %30, !dbg !1115
  %31 = load i32, i32* %dict_size, align 4, !dbg !1116
  %sub = sub nsw i32 %shl21, %31, !dbg !1117
  %32 = load i32, i32* %log2dic, align 4, !dbg !1118
  %sub22 = sub nsw i32 %32, 4, !dbg !1119
  %shl23 = shl i32 1, %sub22, !dbg !1120
  %div = sdiv i32 %sub, %shl23, !dbg !1121
  store i32 %div, i32* %wedges, align 4, !dbg !1122
  br label %if.end25, !dbg !1123

if.else24:                                        ; preds = %for.end
  store i32 0, i32* %wedges, align 4, !dbg !1124
  br label %if.end25

if.end25:                                         ; preds = %if.else24, %if.then20
  %33 = load i32, i32* %wedges, align 4, !dbg !1125
  %shl26 = shl i32 %33, 5, !dbg !1126
  %and27 = and i32 %shl26, 224, !dbg !1127
  %34 = load i32, i32* %log2dic, align 4, !dbg !1128
  %and28 = and i32 %34, 31, !dbg !1129
  %or = or i32 %and27, %and28, !dbg !1130
  store i32 %or, i32* %ds, align 4, !dbg !1131
  %35 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1132
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %35, i32 0, i32 9, !dbg !1133
  store i32 0, i32* %crc32, align 8, !dbg !1134
  %36 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1135
  %compressed29 = getelementptr inbounds %struct.private_data, %struct.private_data* %36, i32 0, i32 6, !dbg !1136
  %37 = load i8*, i8** %compressed29, align 8, !dbg !1136
  %arrayidx = getelementptr inbounds i8, i8* %37, i64 0, !dbg !1135
  store i8 76, i8* %arrayidx, align 1, !dbg !1137
  %38 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1138
  %compressed30 = getelementptr inbounds %struct.private_data, %struct.private_data* %38, i32 0, i32 6, !dbg !1139
  %39 = load i8*, i8** %compressed30, align 8, !dbg !1139
  %arrayidx31 = getelementptr inbounds i8, i8* %39, i64 1, !dbg !1138
  store i8 90, i8* %arrayidx31, align 1, !dbg !1140
  %40 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1141
  %compressed32 = getelementptr inbounds %struct.private_data, %struct.private_data* %40, i32 0, i32 6, !dbg !1142
  %41 = load i8*, i8** %compressed32, align 8, !dbg !1142
  %arrayidx33 = getelementptr inbounds i8, i8* %41, i64 2, !dbg !1141
  store i8 73, i8* %arrayidx33, align 1, !dbg !1143
  %42 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1144
  %compressed34 = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 6, !dbg !1145
  %43 = load i8*, i8** %compressed34, align 8, !dbg !1145
  %arrayidx35 = getelementptr inbounds i8, i8* %43, i64 3, !dbg !1144
  store i8 80, i8* %arrayidx35, align 1, !dbg !1146
  %44 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1147
  %compressed36 = getelementptr inbounds %struct.private_data, %struct.private_data* %44, i32 0, i32 6, !dbg !1148
  %45 = load i8*, i8** %compressed36, align 8, !dbg !1148
  %arrayidx37 = getelementptr inbounds i8, i8* %45, i64 4, !dbg !1147
  store i8 1, i8* %arrayidx37, align 1, !dbg !1149
  %46 = load i32, i32* %ds, align 4, !dbg !1150
  %conv = trunc i32 %46 to i8, !dbg !1151
  %47 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1152
  %compressed38 = getelementptr inbounds %struct.private_data, %struct.private_data* %47, i32 0, i32 6, !dbg !1153
  %48 = load i8*, i8** %compressed38, align 8, !dbg !1153
  %arrayidx39 = getelementptr inbounds i8, i8* %48, i64 5, !dbg !1152
  store i8 %conv, i8* %arrayidx39, align 1, !dbg !1154
  %49 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1155
  %stream40 = getelementptr inbounds %struct.private_data, %struct.private_data* %49, i32 0, i32 2, !dbg !1156
  %next_out41 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream40, i32 0, i32 3, !dbg !1157
  %50 = load i8*, i8** %next_out41, align 8, !dbg !1158
  %add.ptr = getelementptr inbounds i8, i8* %50, i64 6, !dbg !1158
  store i8* %add.ptr, i8** %next_out41, align 8, !dbg !1158
  %51 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1159
  %stream42 = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 2, !dbg !1160
  %avail_out43 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream42, i32 0, i32 4, !dbg !1161
  %52 = load i64, i64* %avail_out43, align 8, !dbg !1162
  %sub44 = sub i64 %52, 6, !dbg !1162
  store i64 %sub44, i64* %avail_out43, align 8, !dbg !1162
  %53 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1163
  %stream45 = getelementptr inbounds %struct.private_data, %struct.private_data* %53, i32 0, i32 2, !dbg !1164
  %54 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1165
  %lzmafilters46 = getelementptr inbounds %struct.private_data, %struct.private_data* %54, i32 0, i32 3, !dbg !1166
  %arraydecay47 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %lzmafilters46, i32 0, i32 0, !dbg !1165
  %call48 = call i32 @lzma_raw_encoder(%struct.lzma_stream* %stream45, %struct.lzma_filter* %arraydecay47) #8, !dbg !1167
  store i32 %call48, i32* %ret, align 4, !dbg !1168
  br label %if.end49

if.end49:                                         ; preds = %if.end25, %if.then6
  br label %if.end50

if.end50:                                         ; preds = %if.end49, %if.then
  %55 = load i32, i32* %ret, align 4, !dbg !1169
  %cmp51 = icmp eq i32 %55, 0, !dbg !1171
  br i1 %cmp51, label %if.then53, label %if.end54, !dbg !1172

if.then53:                                        ; preds = %if.end50
  store i32 0, i32* %retval, align 4, !dbg !1173
  br label %return, !dbg !1173

if.end54:                                         ; preds = %if.end50
  %56 = load i32, i32* %ret, align 4, !dbg !1174
  switch i32 %56, label %sw.default [
    i32 5, label %sw.bb
  ], !dbg !1175

sw.bb:                                            ; preds = %if.end54
  %57 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1176
  %archive55 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %57, i32 0, i32 1, !dbg !1178
  %58 = load %struct.archive*, %struct.archive** %archive55, align 8, !dbg !1178
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %58, i32 12, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.13, i32 0, i32 0)), !dbg !1179
  br label %sw.epilog, !dbg !1180

sw.default:                                       ; preds = %if.end54
  %59 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1181
  %archive56 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %59, i32 0, i32 1, !dbg !1182
  %60 = load %struct.archive*, %struct.archive** %archive56, align 8, !dbg !1182
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %60, i32 -1, i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.14, i32 0, i32 0)), !dbg !1183
  br label %sw.epilog, !dbg !1184

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  store i32 -30, i32* %retval, align 4, !dbg !1185
  br label %return, !dbg !1185

return:                                           ; preds = %sw.epilog, %if.then53, %if.then14
  %61 = load i32, i32* %retval, align 4, !dbg !1186
  ret i32 %61, !dbg !1186
}

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #4

; Function Attrs: nounwind uwtable
define internal i32 @drive_compressor(%struct.archive_write_filter* %f, %struct.private_data* %data, i32 %finishing) #0 !dbg !344 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data.addr = alloca %struct.private_data*, align 8
  %finishing.addr = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !1187, metadata !377), !dbg !1188
  store %struct.private_data* %data, %struct.private_data** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.private_data** %data.addr, metadata !1189, metadata !377), !dbg !1190
  store i32 %finishing, i32* %finishing.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %finishing.addr, metadata !1191, metadata !377), !dbg !1192
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1193, metadata !377), !dbg !1194
  br label %for.cond, !dbg !1195

for.cond:                                         ; preds = %sw.epilog, %entry
  %0 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1196
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %0, i32 0, i32 2, !dbg !1201
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream, i32 0, i32 4, !dbg !1202
  %1 = load i64, i64* %avail_out, align 8, !dbg !1202
  %cmp = icmp eq i64 %1, 0, !dbg !1203
  br i1 %cmp, label %if.then, label %if.end9, !dbg !1204

if.then:                                          ; preds = %for.cond
  %2 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1205
  %compressed_buffer_size = getelementptr inbounds %struct.private_data, %struct.private_data* %2, i32 0, i32 7, !dbg !1207
  %3 = load i64, i64* %compressed_buffer_size, align 8, !dbg !1207
  %4 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1208
  %total_out = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 8, !dbg !1209
  %5 = load i64, i64* %total_out, align 8, !dbg !1210
  %add = add i64 %5, %3, !dbg !1210
  store i64 %add, i64* %total_out, align 8, !dbg !1210
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1211
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 2, !dbg !1212
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !1212
  %8 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1213
  %compressed = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 6, !dbg !1214
  %9 = load i8*, i8** %compressed, align 8, !dbg !1214
  %10 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1215
  %compressed_buffer_size1 = getelementptr inbounds %struct.private_data, %struct.private_data* %10, i32 0, i32 7, !dbg !1216
  %11 = load i64, i64* %compressed_buffer_size1, align 8, !dbg !1216
  %call = call i32 @__archive_write_filter(%struct.archive_write_filter* %7, i8* %9, i64 %11), !dbg !1217
  store i32 %call, i32* %ret, align 4, !dbg !1218
  %12 = load i32, i32* %ret, align 4, !dbg !1219
  %cmp2 = icmp ne i32 %12, 0, !dbg !1221
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !1222

if.then3:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !1223
  br label %return, !dbg !1223

if.end:                                           ; preds = %if.then
  %13 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1224
  %compressed4 = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 6, !dbg !1225
  %14 = load i8*, i8** %compressed4, align 8, !dbg !1225
  %15 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1226
  %stream5 = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 2, !dbg !1227
  %next_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream5, i32 0, i32 3, !dbg !1228
  store i8* %14, i8** %next_out, align 8, !dbg !1229
  %16 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1230
  %compressed_buffer_size6 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 7, !dbg !1231
  %17 = load i64, i64* %compressed_buffer_size6, align 8, !dbg !1231
  %18 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1232
  %stream7 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 2, !dbg !1233
  %avail_out8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream7, i32 0, i32 4, !dbg !1234
  store i64 %17, i64* %avail_out8, align 8, !dbg !1235
  br label %if.end9, !dbg !1236

if.end9:                                          ; preds = %if.end, %for.cond
  %19 = load i32, i32* %finishing.addr, align 4, !dbg !1237
  %tobool = icmp ne i32 %19, 0, !dbg !1237
  br i1 %tobool, label %if.end13, label %land.lhs.true, !dbg !1239

land.lhs.true:                                    ; preds = %if.end9
  %20 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1240
  %stream10 = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 2, !dbg !1242
  %avail_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream10, i32 0, i32 1, !dbg !1243
  %21 = load i64, i64* %avail_in, align 8, !dbg !1243
  %cmp11 = icmp eq i64 %21, 0, !dbg !1244
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1245

if.then12:                                        ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !1246
  br label %return, !dbg !1246

if.end13:                                         ; preds = %land.lhs.true, %if.end9
  %22 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1247
  %stream14 = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 2, !dbg !1248
  %23 = load i32, i32* %finishing.addr, align 4, !dbg !1249
  %tobool15 = icmp ne i32 %23, 0, !dbg !1249
  %cond = select i1 %tobool15, i32 3, i32 0, !dbg !1249
  %call16 = call i32 @lzma_code(%struct.lzma_stream* %stream14, i32 %cond) #8, !dbg !1250
  store i32 %call16, i32* %ret, align 4, !dbg !1251
  %24 = load i32, i32* %ret, align 4, !dbg !1252
  switch i32 %24, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb24
    i32 6, label %sw.bb28
  ], !dbg !1253

sw.bb:                                            ; preds = %if.end13
  %25 = load i32, i32* %finishing.addr, align 4, !dbg !1254
  %tobool17 = icmp ne i32 %25, 0, !dbg !1254
  br i1 %tobool17, label %if.end23, label %land.lhs.true18, !dbg !1257

land.lhs.true18:                                  ; preds = %sw.bb
  %26 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1258
  %stream19 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 2, !dbg !1260
  %avail_in20 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream19, i32 0, i32 1, !dbg !1261
  %27 = load i64, i64* %avail_in20, align 8, !dbg !1261
  %cmp21 = icmp eq i64 %27, 0, !dbg !1262
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1263

if.then22:                                        ; preds = %land.lhs.true18
  store i32 0, i32* %retval, align 4, !dbg !1264
  br label %return, !dbg !1264

if.end23:                                         ; preds = %land.lhs.true18, %sw.bb
  br label %sw.epilog, !dbg !1265

sw.bb24:                                          ; preds = %if.end13
  %28 = load i32, i32* %finishing.addr, align 4, !dbg !1266
  %tobool25 = icmp ne i32 %28, 0, !dbg !1266
  br i1 %tobool25, label %if.then26, label %if.end27, !dbg !1268

if.then26:                                        ; preds = %sw.bb24
  store i32 0, i32* %retval, align 4, !dbg !1269
  br label %return, !dbg !1269

if.end27:                                         ; preds = %sw.bb24
  %29 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1270
  %archive = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %29, i32 0, i32 1, !dbg !1271
  %30 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1271
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %30, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.9, i32 0, i32 0)), !dbg !1272
  store i32 -30, i32* %retval, align 4, !dbg !1273
  br label %return, !dbg !1273

sw.bb28:                                          ; preds = %if.end13
  %31 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1274
  %archive29 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %31, i32 0, i32 1, !dbg !1275
  %32 = load %struct.archive*, %struct.archive** %archive29, align 8, !dbg !1275
  %33 = load %struct.private_data*, %struct.private_data** %data.addr, align 8, !dbg !1276
  %stream30 = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 2, !dbg !1277
  %call31 = call i64 @lzma_memusage(%struct.lzma_stream* %stream30) #9, !dbg !1278
  %add32 = add i64 %call31, 1048576, !dbg !1279
  %sub = sub i64 %add32, 1, !dbg !1280
  %div = udiv i64 %sub, 1048576, !dbg !1281
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %32, i32 12, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.10, i32 0, i32 0), i64 %div), !dbg !1282
  store i32 -30, i32* %retval, align 4, !dbg !1283
  br label %return, !dbg !1283

sw.default:                                       ; preds = %if.end13
  %34 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !1284
  %archive33 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %34, i32 0, i32 1, !dbg !1285
  %35 = load %struct.archive*, %struct.archive** %archive33, align 8, !dbg !1285
  %36 = load i32, i32* %ret, align 4, !dbg !1286
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %35, i32 -1, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.11, i32 0, i32 0), i32 %36), !dbg !1287
  store i32 -30, i32* %retval, align 4, !dbg !1288
  br label %return, !dbg !1288

sw.epilog:                                        ; preds = %if.end23
  br label %for.cond, !dbg !1289

return:                                           ; preds = %sw.default, %sw.bb28, %if.end27, %if.then26, %if.then22, %if.then12, %if.then3
  %37 = load i32, i32* %retval, align 4, !dbg !1291
  ret i32 %37, !dbg !1291
}

declare i32 @__archive_write_filter(%struct.archive_write_filter*, i8*, i64) #2

; Function Attrs: nounwind
declare i32 @lzma_code(%struct.lzma_stream*, i32) #3

; Function Attrs: nounwind readonly
declare i64 @lzma_memusage(%struct.lzma_stream*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @lzma_stream_encoder(%struct.lzma_stream*, %struct.lzma_filter*, i32) #3

; Function Attrs: nounwind
declare i32 @lzma_alone_encoder(%struct.lzma_stream*, %struct.lzma_options_lzma*) #3

; Function Attrs: nounwind
declare i32 @lzma_raw_encoder(%struct.lzma_stream*, %struct.lzma_filter*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le32enc(i8* %pp, i32 %u) #6 !dbg !351 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !1292, metadata !377), !dbg !1293
  store i32 %u, i32* %u.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %u.addr, metadata !1294, metadata !377), !dbg !1295
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1296, metadata !377), !dbg !1297
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !1298
  store i8* %0, i8** %p, align 8, !dbg !1297
  %1 = load i32, i32* %u.addr, align 4, !dbg !1299
  %and = and i32 %1, 255, !dbg !1300
  %conv = trunc i32 %and to i8, !dbg !1299
  %2 = load i8*, i8** %p, align 8, !dbg !1301
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !1301
  store i8 %conv, i8* %arrayidx, align 1, !dbg !1302
  %3 = load i32, i32* %u.addr, align 4, !dbg !1303
  %shr = lshr i32 %3, 8, !dbg !1304
  %and1 = and i32 %shr, 255, !dbg !1305
  %conv2 = trunc i32 %and1 to i8, !dbg !1306
  %4 = load i8*, i8** %p, align 8, !dbg !1307
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !1307
  store i8 %conv2, i8* %arrayidx3, align 1, !dbg !1308
  %5 = load i32, i32* %u.addr, align 4, !dbg !1309
  %shr4 = lshr i32 %5, 16, !dbg !1310
  %and5 = and i32 %shr4, 255, !dbg !1311
  %conv6 = trunc i32 %and5 to i8, !dbg !1312
  %6 = load i8*, i8** %p, align 8, !dbg !1313
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 2, !dbg !1313
  store i8 %conv6, i8* %arrayidx7, align 1, !dbg !1314
  %7 = load i32, i32* %u.addr, align 4, !dbg !1315
  %shr8 = lshr i32 %7, 24, !dbg !1316
  %and9 = and i32 %shr8, 255, !dbg !1317
  %conv10 = trunc i32 %and9 to i8, !dbg !1318
  %8 = load i8*, i8** %p, align 8, !dbg !1319
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 3, !dbg !1319
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !1320
  ret void, !dbg !1321
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le64enc(i8* %pp, i64 %u) #6 !dbg !355 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !1322, metadata !377), !dbg !1323
  store i64 %u, i64* %u.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %u.addr, metadata !1324, metadata !377), !dbg !1325
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1326, metadata !377), !dbg !1327
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !1328
  store i8* %0, i8** %p, align 8, !dbg !1327
  %1 = load i8*, i8** %p, align 8, !dbg !1329
  %2 = load i64, i64* %u.addr, align 8, !dbg !1330
  %and = and i64 %2, 4294967295, !dbg !1331
  %conv = trunc i64 %and to i32, !dbg !1332
  call void @archive_le32enc(i8* %1, i32 %conv), !dbg !1333
  %3 = load i8*, i8** %p, align 8, !dbg !1334
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !1335
  %4 = load i64, i64* %u.addr, align 8, !dbg !1336
  %shr = lshr i64 %4, 32, !dbg !1337
  %conv1 = trunc i64 %shr to i32, !dbg !1338
  call void @archive_le32enc(i8* %add.ptr, i32 %conv1), !dbg !1339
  ret void, !dbg !1340
}

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

declare i32 @__archive_write_close_filter(%struct.archive_write_filter*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind
declare i64 @strtoul(i8*, i8**, i32) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #7

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!373, !374}
!llvm.ident = !{!375}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !46, subprograms: !333, globals: !360)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_xz.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !7, !12, !19, !33, !39}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!5 = !{!6}
!6 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!7 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !8, line: 138, size: 32, align: 32, elements: !9)
!8 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !{!10, !11}
!10 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!11 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!12 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !8, line: 58, size: 32, align: 32, elements: !13)
!13 = !{!14, !15, !16, !17, !18}
!14 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!15 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!16 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!17 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!18 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!19 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !20)
!20 = !{!21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32}
!21 = !DIEnumerator(name: "LZMA_OK", value: 0)
!22 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!23 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!24 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!25 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!26 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!27 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!28 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!29 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!30 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!31 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!32 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!33 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !34)
!34 = !{!35, !36, !37, !38}
!35 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!36 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!37 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!38 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!39 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !40, line: 27, size: 32, align: 32, elements: !41)
!40 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!41 = !{!42, !43, !44, !45}
!42 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!43 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!44 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!45 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!46 = !{!47, !166, !234, !235, !332, !159, !240, !66}
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !49, line: 72, size: 2816, align: 64, elements: !50)
!49 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!50 = !{!51, !153, !154, !155, !156, !160, !161, !167, !173, !176, !177, !178, !179, !205, !206, !207, !208, !212, !216, !217, !221, !225, !226, !227, !228, !233}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !48, file: !49, line: 73, baseType: !52, size: 1280, align: 64)
!52 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !53, line: 89, size: 1280, align: 64, elements: !54)
!53 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !{!55, !57, !58, !126, !127, !128, !129, !130, !131, !132, !133, !141, !142, !143, !144, !147, !148, !149, !150, !151, !152}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !52, file: !53, line: 96, baseType: !56, size: 32, align: 32)
!56 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !52, file: !53, line: 97, baseType: !56, size: 32, align: 32, offset: 32)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !52, file: !53, line: 103, baseType: !59, size: 64, align: 64, offset: 64)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !53, line: 63, size: 832, align: 64, elements: !61)
!61 = !{!62, !68, !69, !76, !77, !91, !97, !102, !103, !110, !111, !115, !119}
!62 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !60, file: !53, line: 64, baseType: !63, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!64 = !DISubroutineType(types: !65)
!65 = !{!66, !67}
!66 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !60, file: !53, line: 65, baseType: !63, size: 64, align: 64, offset: 64)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !60, file: !53, line: 66, baseType: !70, size: 64, align: 64, offset: 128)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DISubroutineType(types: !72)
!72 = !{!66, !67, !73}
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !75, line: 180, flags: DIFlagFwdDecl)
!75 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !60, file: !53, line: 68, baseType: !63, size: 64, align: 64, offset: 192)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !60, file: !53, line: 69, baseType: !78, size: 64, align: 64, offset: 256)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DISubroutineType(types: !80)
!80 = !{!81, !67, !86, !88}
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !82, line: 109, baseType: !83)
!82 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !84, line: 172, baseType: !85)
!84 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!85 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !89, line: 62, baseType: !90)
!89 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!90 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !60, file: !53, line: 71, baseType: !92, size: 64, align: 64, offset: 320)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{!81, !67, !86, !88, !95}
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !96, line: 40, baseType: !85)
!96 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!97 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !60, file: !53, line: 74, baseType: !98, size: 64, align: 64, offset: 384)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{!66, !67, !101}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !60, file: !53, line: 76, baseType: !70, size: 64, align: 64, offset: 448)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !60, file: !53, line: 78, baseType: !104, size: 64, align: 64, offset: 512)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!66, !67, !107, !108, !109}
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !60, file: !53, line: 81, baseType: !63, size: 64, align: 64, offset: 576)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !60, file: !53, line: 82, baseType: !112, size: 64, align: 64, offset: 640)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{!95, !67, !66}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !60, file: !53, line: 83, baseType: !116, size: 64, align: 64, offset: 704)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!66, !67, !66}
!119 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !60, file: !53, line: 84, baseType: !120, size: 64, align: 64, offset: 768)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DISubroutineType(types: !122)
!122 = !{!123, !67, !66}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !125)
!125 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !52, file: !53, line: 105, baseType: !66, size: 32, align: 32, offset: 128)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !52, file: !53, line: 106, baseType: !123, size: 64, align: 64, offset: 192)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !52, file: !53, line: 108, baseType: !66, size: 32, align: 32, offset: 256)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !52, file: !53, line: 109, baseType: !123, size: 64, align: 64, offset: 320)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !52, file: !53, line: 112, baseType: !66, size: 32, align: 32, offset: 384)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !52, file: !53, line: 114, baseType: !66, size: 32, align: 32, offset: 416)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !52, file: !53, line: 115, baseType: !123, size: 64, align: 64, offset: 448)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !52, file: !53, line: 116, baseType: !134, size: 192, align: 64, offset: 512)
!134 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !135, line: 58, size: 192, align: 64, elements: !136)
!135 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!136 = !{!137, !139, !140}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !134, file: !135, line: 59, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !134, file: !135, line: 60, baseType: !88, size: 64, align: 64, offset: 64)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !134, file: !135, line: 61, baseType: !88, size: 64, align: 64, offset: 128)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !52, file: !53, line: 118, baseType: !138, size: 64, align: 64, offset: 704)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !52, file: !53, line: 119, baseType: !56, size: 32, align: 32, offset: 768)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !52, file: !53, line: 120, baseType: !56, size: 32, align: 32, offset: 800)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !52, file: !53, line: 121, baseType: !145, size: 64, align: 64, offset: 832)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !135, line: 70, flags: DIFlagFwdDecl)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !52, file: !53, line: 127, baseType: !123, size: 64, align: 64, offset: 896)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !52, file: !53, line: 128, baseType: !95, size: 64, align: 64, offset: 960)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !52, file: !53, line: 129, baseType: !95, size: 64, align: 64, offset: 1024)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !52, file: !53, line: 130, baseType: !88, size: 64, align: 64, offset: 1088)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !52, file: !53, line: 137, baseType: !125, size: 8, align: 8, offset: 1152)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !52, file: !53, line: 138, baseType: !88, size: 64, align: 64, offset: 1216)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !48, file: !49, line: 76, baseType: !66, size: 32, align: 32, offset: 1280)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !48, file: !49, line: 77, baseType: !95, size: 64, align: 64, offset: 1344)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !48, file: !49, line: 78, baseType: !95, size: 64, align: 64, offset: 1408)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !48, file: !49, line: 81, baseType: !157, size: 64, align: 64, offset: 1472)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !159)
!159 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !48, file: !49, line: 82, baseType: !88, size: 64, align: 64, offset: 1536)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !48, file: !49, line: 85, baseType: !162, size: 64, align: 64, offset: 1600)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !75, line: 241, baseType: !164)
!164 = !DISubroutineType(types: !165)
!165 = !{!66, !67, !166}
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !48, file: !49, line: 86, baseType: !168, size: 64, align: 64, offset: 1664)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !75, line: 237, baseType: !170)
!170 = !DISubroutineType(types: !171)
!171 = !{!172, !67, !166, !86, !88}
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !75, line: 95, baseType: !81)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !48, file: !49, line: 87, baseType: !174, size: 64, align: 64, offset: 1728)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !75, line: 243, baseType: !164)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !48, file: !49, line: 88, baseType: !166, size: 64, align: 64, offset: 1792)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !48, file: !49, line: 96, baseType: !66, size: 32, align: 32, offset: 1856)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !48, file: !49, line: 97, baseType: !66, size: 32, align: 32, offset: 1888)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !48, file: !49, line: 102, baseType: !180, size: 64, align: 64, offset: 1920)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !49, line: 43, size: 768, align: 64, elements: !182)
!182 = !{!183, !184, !185, !186, !190, !194, !198, !199, !200, !201, !202, !203, !204}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !181, file: !49, line: 44, baseType: !95, size: 64, align: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !181, file: !49, line: 45, baseType: !67, size: 64, align: 64, offset: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !181, file: !49, line: 46, baseType: !180, size: 64, align: 64, offset: 128)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !181, file: !49, line: 47, baseType: !187, size: 64, align: 64, offset: 192)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DISubroutineType(types: !189)
!189 = !{!66, !180, !123, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !181, file: !49, line: 49, baseType: !191, size: 64, align: 64, offset: 256)
!191 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !192, size: 64, align: 64)
!192 = !DISubroutineType(types: !193)
!193 = !{!66, !180}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !181, file: !49, line: 50, baseType: !195, size: 64, align: 64, offset: 320)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DISubroutineType(types: !197)
!197 = !{!66, !180, !86, !88}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !181, file: !49, line: 51, baseType: !191, size: 64, align: 64, offset: 384)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !181, file: !49, line: 52, baseType: !191, size: 64, align: 64, offset: 448)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !181, file: !49, line: 53, baseType: !166, size: 64, align: 64, offset: 512)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !181, file: !49, line: 54, baseType: !123, size: 64, align: 64, offset: 576)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !181, file: !49, line: 55, baseType: !66, size: 32, align: 32, offset: 640)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !181, file: !49, line: 56, baseType: !66, size: 32, align: 32, offset: 672)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !181, file: !49, line: 57, baseType: !66, size: 32, align: 32, offset: 704)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !48, file: !49, line: 103, baseType: !180, size: 64, align: 64, offset: 1984)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !48, file: !49, line: 109, baseType: !166, size: 64, align: 64, offset: 2048)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !48, file: !49, line: 110, baseType: !123, size: 64, align: 64, offset: 2112)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !48, file: !49, line: 111, baseType: !209, size: 64, align: 64, offset: 2176)
!209 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !210, size: 64, align: 64)
!210 = !DISubroutineType(types: !211)
!211 = !{!66, !47}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !48, file: !49, line: 112, baseType: !213, size: 64, align: 64, offset: 2240)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!66, !47, !123, !123}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !48, file: !49, line: 114, baseType: !209, size: 64, align: 64, offset: 2304)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !48, file: !49, line: 115, baseType: !218, size: 64, align: 64, offset: 2368)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{!66, !47, !73}
!221 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !48, file: !49, line: 117, baseType: !222, size: 64, align: 64, offset: 2432)
!222 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !223, size: 64, align: 64)
!223 = !DISubroutineType(types: !224)
!224 = !{!81, !47, !86, !88}
!225 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !48, file: !49, line: 119, baseType: !209, size: 64, align: 64, offset: 2496)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !48, file: !49, line: 120, baseType: !209, size: 64, align: 64, offset: 2560)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !48, file: !49, line: 126, baseType: !138, size: 64, align: 64, offset: 2624)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !48, file: !49, line: 127, baseType: !229, size: 64, align: 64, offset: 2688)
!229 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !75, line: 256, baseType: !231)
!231 = !DISubroutineType(types: !232)
!232 = !{!123, !67, !166}
!233 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !48, file: !49, line: 128, baseType: !166, size: 64, align: 64, offset: 2752)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 101, size: 2624, align: 64, elements: !237)
!237 = !{!238, !239, !241, !285, !297, !327, !328, !329, !330, !331}
!238 = !DIDerivedType(tag: DW_TAG_member, name: "compression_level", scope: !236, file: !1, line: 102, baseType: !66, size: 32, align: 32)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "threads", scope: !236, file: !1, line: 103, baseType: !240, size: 32, align: 32, offset: 32)
!240 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !96, line: 51, baseType: !56)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !236, file: !1, line: 104, baseType: !242, size: 1088, align: 64, offset: 64)
!242 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !243)
!243 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !244)
!244 = !{!245, !249, !250, !252, !254, !255, !256, !270, !274, !275, !276, !277, !278, !279, !280, !281, !282, !284}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !243, file: !4, line: 454, baseType: !246, size: 64, align: 64)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !248)
!248 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !96, line: 48, baseType: !159)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !243, file: !4, line: 455, baseType: !88, size: 64, align: 64, offset: 64)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !243, file: !4, line: 456, baseType: !251, size: 64, align: 64, offset: 128)
!251 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !96, line: 55, baseType: !90)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !243, file: !4, line: 458, baseType: !253, size: 64, align: 64, offset: 192)
!253 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !243, file: !4, line: 459, baseType: !88, size: 64, align: 64, offset: 256)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !243, file: !4, line: 460, baseType: !251, size: 64, align: 64, offset: 320)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !243, file: !4, line: 468, baseType: !257, size: 64, align: 64, offset: 384)
!257 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !258, size: 64, align: 64)
!258 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !259)
!259 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !260)
!260 = !{!261, !265, !269}
!261 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !259, file: !4, line: 376, baseType: !262, size: 64, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !263, size: 64, align: 64)
!263 = !DISubroutineType(types: !264)
!264 = !{!166, !166, !88, !88}
!265 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !259, file: !4, line: 390, baseType: !266, size: 64, align: 64, offset: 64)
!266 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !267, size: 64, align: 64)
!267 = !DISubroutineType(types: !268)
!268 = !{null, !166, !166}
!269 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !259, file: !4, line: 401, baseType: !166, size: 64, align: 64, offset: 128)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !243, file: !4, line: 471, baseType: !271, size: 64, align: 64, offset: 448)
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !272, size: 64, align: 64)
!272 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !273)
!273 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !4, line: 411, flags: DIFlagFwdDecl)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !243, file: !4, line: 479, baseType: !166, size: 64, align: 64, offset: 512)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !243, file: !4, line: 480, baseType: !166, size: 64, align: 64, offset: 576)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !243, file: !4, line: 481, baseType: !166, size: 64, align: 64, offset: 640)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !243, file: !4, line: 482, baseType: !166, size: 64, align: 64, offset: 704)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !243, file: !4, line: 483, baseType: !251, size: 64, align: 64, offset: 768)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !243, file: !4, line: 484, baseType: !251, size: 64, align: 64, offset: 832)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !243, file: !4, line: 485, baseType: !88, size: 64, align: 64, offset: 896)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !243, file: !4, line: 486, baseType: !88, size: 64, align: 64, offset: 960)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !243, file: !4, line: 487, baseType: !283, size: 32, align: 32, offset: 1024)
!283 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !3)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !243, file: !4, line: 488, baseType: !283, size: 32, align: 32, offset: 1056)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "lzmafilters", scope: !236, file: !1, line: 105, baseType: !286, size: 256, align: 64, offset: 1152)
!286 = !DICompositeType(tag: DW_TAG_array_type, baseType: !287, size: 256, align: 64, elements: !295)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !288, line: 65, baseType: !289)
!288 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!289 = !DICompositeType(tag: DW_TAG_structure_type, file: !288, line: 43, size: 128, align: 64, elements: !290)
!290 = !{!291, !294}
!291 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !289, file: !288, line: 54, baseType: !292, size: 64, align: 64)
!292 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !293, line: 63, baseType: !251)
!293 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!294 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !289, file: !288, line: 63, baseType: !166, size: 64, align: 64, offset: 64)
!295 = !{!296}
!296 = !DISubrange(count: 2)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "lzma_opt", scope: !236, file: !1, line: 106, baseType: !298, size: 896, align: 64, offset: 1408)
!298 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !8, line: 399, baseType: !299)
!299 = !DICompositeType(tag: DW_TAG_structure_type, file: !8, line: 185, size: 896, align: 64, elements: !300)
!300 = !{!301, !302, !303, !304, !305, !306, !307, !309, !310, !312, !313, !314, !315, !316, !317, !318, !319, !320, !321, !322, !323, !324, !325, !326}
!301 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !299, file: !8, line: 217, baseType: !240, size: 32, align: 32)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !299, file: !8, line: 240, baseType: !246, size: 64, align: 64, offset: 64)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !299, file: !8, line: 254, baseType: !240, size: 32, align: 32, offset: 128)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !299, file: !8, line: 281, baseType: !240, size: 32, align: 32, offset: 160)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !299, file: !8, line: 293, baseType: !240, size: 32, align: 32, offset: 192)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !299, file: !8, line: 316, baseType: !240, size: 32, align: 32, offset: 224)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !299, file: !8, line: 322, baseType: !308, size: 32, align: 32, offset: 256)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !8, line: 155, baseType: !7)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !299, file: !8, line: 342, baseType: !240, size: 32, align: 32, offset: 288)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !299, file: !8, line: 345, baseType: !311, size: 32, align: 32, offset: 320)
!311 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !8, line: 111, baseType: !12)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !299, file: !8, line: 375, baseType: !240, size: 32, align: 32, offset: 352)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !299, file: !8, line: 384, baseType: !240, size: 32, align: 32, offset: 384)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !299, file: !8, line: 385, baseType: !240, size: 32, align: 32, offset: 416)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !299, file: !8, line: 386, baseType: !240, size: 32, align: 32, offset: 448)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !299, file: !8, line: 387, baseType: !240, size: 32, align: 32, offset: 480)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !299, file: !8, line: 388, baseType: !240, size: 32, align: 32, offset: 512)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !299, file: !8, line: 389, baseType: !240, size: 32, align: 32, offset: 544)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !299, file: !8, line: 390, baseType: !240, size: 32, align: 32, offset: 576)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !299, file: !8, line: 391, baseType: !240, size: 32, align: 32, offset: 608)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !299, file: !8, line: 392, baseType: !283, size: 32, align: 32, offset: 640)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !299, file: !8, line: 393, baseType: !283, size: 32, align: 32, offset: 672)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !299, file: !8, line: 394, baseType: !283, size: 32, align: 32, offset: 704)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !299, file: !8, line: 395, baseType: !283, size: 32, align: 32, offset: 736)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !299, file: !8, line: 396, baseType: !166, size: 64, align: 64, offset: 768)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !299, file: !8, line: 397, baseType: !166, size: 64, align: 64, offset: 832)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !236, file: !1, line: 107, baseType: !95, size: 64, align: 64, offset: 2304)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "compressed", scope: !236, file: !1, line: 108, baseType: !234, size: 64, align: 64, offset: 2368)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_buffer_size", scope: !236, file: !1, line: 109, baseType: !88, size: 64, align: 64, offset: 2432)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !236, file: !1, line: 110, baseType: !95, size: 64, align: 64, offset: 2496)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !236, file: !1, line: 112, baseType: !240, size: 32, align: 32, offset: 2560)
!332 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !96, line: 135, baseType: !90)
!333 = !{!334, !336, !337, !338, !339, !340, !341, !342, !343, !344, !347, !350, !351, !355, !358, !359}
!334 = distinct !DISubprogram(name: "archive_write_set_compression_lzip", scope: !1, file: !1, line: 52, type: !64, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!335 = !{}
!336 = distinct !DISubprogram(name: "archive_write_set_compression_lzma", scope: !1, file: !1, line: 59, type: !64, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!337 = distinct !DISubprogram(name: "archive_write_set_compression_xz", scope: !1, file: !1, line: 66, type: !64, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!338 = distinct !DISubprogram(name: "archive_write_add_filter_xz", scope: !1, file: !1, line: 167, type: !64, isLocal: false, isDefinition: true, scopeLine: 168, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!339 = distinct !DISubprogram(name: "archive_write_add_filter_lzma", scope: !1, file: !1, line: 187, type: !64, isLocal: false, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!340 = distinct !DISubprogram(name: "archive_write_add_filter_lzip", scope: !1, file: !1, line: 204, type: !64, isLocal: false, isDefinition: true, scopeLine: 205, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!341 = distinct !DISubprogram(name: "common_setup", scope: !1, file: !1, line: 144, type: !192, isLocal: true, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!342 = distinct !DISubprogram(name: "archive_compressor_xz_open", scope: !1, file: !1, line: 307, type: !192, isLocal: true, isDefinition: true, scopeLine: 308, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!343 = distinct !DISubprogram(name: "archive_compressor_xz_write", scope: !1, file: !1, line: 420, type: !196, isLocal: true, isDefinition: true, scopeLine: 422, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!344 = distinct !DISubprogram(name: "drive_compressor", scope: !1, file: !1, line: 488, type: !345, isLocal: true, isDefinition: true, scopeLine: 490, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!345 = !DISubroutineType(types: !346)
!346 = !{!66, !180, !235, !66}
!347 = distinct !DISubprogram(name: "archive_compressor_xz_init_stream", scope: !1, file: !1, line: 221, type: !348, isLocal: true, isDefinition: true, scopeLine: 223, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!348 = !DISubroutineType(types: !349)
!349 = !{!66, !180, !235}
!350 = distinct !DISubprogram(name: "archive_compressor_xz_close", scope: !1, file: !1, line: 445, type: !192, isLocal: true, isDefinition: true, scopeLine: 446, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!351 = distinct !DISubprogram(name: "archive_le32enc", scope: !352, file: !352, line: 177, type: !353, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!352 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!353 = !DISubroutineType(types: !354)
!354 = !{null, !166, !240}
!355 = distinct !DISubprogram(name: "archive_le64enc", scope: !352, file: !352, line: 188, type: !356, isLocal: true, isDefinition: true, scopeLine: 189, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!356 = !DISubroutineType(types: !357)
!357 = !{null, !166, !251}
!358 = distinct !DISubprogram(name: "archive_compressor_xz_free", scope: !1, file: !1, line: 471, type: !192, isLocal: true, isDefinition: true, scopeLine: 472, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!359 = distinct !DISubprogram(name: "archive_compressor_xz_options", scope: !1, file: !1, line: 379, type: !188, isLocal: true, isDefinition: true, scopeLine: 381, flags: DIFlagPrototyped, isOptimized: false, variables: !335)
!360 = !{!361, !371}
!361 = !DIGlobalVariable(name: "option_values", scope: !0, file: !1, line: 130, type: !362, isLocal: true, isDefinition: true, variable: [10 x %struct.option_value]* @option_values)
!362 = !DICompositeType(tag: DW_TAG_array_type, baseType: !363, size: 960, align: 32, elements: !369)
!363 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !364)
!364 = !DICompositeType(tag: DW_TAG_structure_type, name: "option_value", file: !1, line: 125, size: 96, align: 32, elements: !365)
!365 = !{!366, !367, !368}
!366 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !364, file: !1, line: 126, baseType: !240, size: 32, align: 32)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !364, file: !1, line: 127, baseType: !240, size: 32, align: 32, offset: 32)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !364, file: !1, line: 128, baseType: !311, size: 32, align: 32, offset: 64)
!369 = !{!370}
!370 = !DISubrange(count: 10)
!371 = !DIGlobalVariable(name: "lzma_stream_init_data", scope: !347, file: !1, line: 224, type: !372, isLocal: true, isDefinition: true, variable: %struct.lzma_stream* @archive_compressor_xz_init_stream.lzma_stream_init_data)
!372 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !242)
!373 = !{i32 2, !"Dwarf Version", i32 4}
!374 = !{i32 2, !"Debug Info Version", i32 3}
!375 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!376 = !DILocalVariable(name: "a", arg: 1, scope: !334, file: !1, line: 52, type: !67)
!377 = !DIExpression()
!378 = !DILocation(line: 52, column: 52, scope: !334)
!379 = !DILocation(line: 54, column: 31, scope: !334)
!380 = !DILocation(line: 54, column: 2, scope: !334)
!381 = !DILocation(line: 55, column: 40, scope: !334)
!382 = !DILocation(line: 55, column: 10, scope: !334)
!383 = !DILocation(line: 55, column: 2, scope: !334)
!384 = !DILocalVariable(name: "_a", arg: 1, scope: !340, file: !1, line: 204, type: !67)
!385 = !DILocation(line: 204, column: 47, scope: !340)
!386 = !DILocalVariable(name: "f", scope: !340, file: !1, line: 206, type: !180)
!387 = !DILocation(line: 206, column: 31, scope: !340)
!388 = !DILocalVariable(name: "r", scope: !340, file: !1, line: 207, type: !66)
!389 = !DILocation(line: 207, column: 6, scope: !340)
!390 = !DILocation(line: 209, column: 2, scope: !340)
!391 = !DILocalVariable(name: "magic_test", scope: !392, file: !1, line: 209, type: !66)
!392 = distinct !DILexicalBlock(scope: !340, file: !1, line: 209, column: 2)
!393 = !DILocation(line: 209, column: 2, scope: !392)
!394 = !DILocation(line: 209, column: 2, scope: !395)
!395 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!396 = !DILocation(line: 209, column: 2, scope: !397)
!397 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 2)
!398 = distinct !DILexicalBlock(scope: !392, file: !1, line: 209, column: 2)
!399 = !DILocation(line: 209, column: 2, scope: !400)
!400 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 3)
!401 = !DILocation(line: 211, column: 38, scope: !340)
!402 = !DILocation(line: 211, column: 6, scope: !340)
!403 = !DILocation(line: 211, column: 4, scope: !340)
!404 = !DILocation(line: 212, column: 19, scope: !340)
!405 = !DILocation(line: 212, column: 6, scope: !340)
!406 = !DILocation(line: 212, column: 4, scope: !340)
!407 = !DILocation(line: 213, column: 6, scope: !408)
!408 = distinct !DILexicalBlock(scope: !340, file: !1, line: 213, column: 6)
!409 = !DILocation(line: 213, column: 8, scope: !408)
!410 = !DILocation(line: 213, column: 6, scope: !340)
!411 = !DILocation(line: 214, column: 3, scope: !412)
!412 = distinct !DILexicalBlock(scope: !408, file: !1, line: 213, column: 23)
!413 = !DILocation(line: 214, column: 6, scope: !412)
!414 = !DILocation(line: 214, column: 11, scope: !412)
!415 = !DILocation(line: 215, column: 3, scope: !412)
!416 = !DILocation(line: 215, column: 6, scope: !412)
!417 = !DILocation(line: 215, column: 11, scope: !412)
!418 = !DILocation(line: 216, column: 2, scope: !412)
!419 = !DILocation(line: 217, column: 10, scope: !340)
!420 = !DILocation(line: 217, column: 2, scope: !340)
!421 = !DILocation(line: 218, column: 1, scope: !340)
!422 = !DILocalVariable(name: "a", arg: 1, scope: !336, file: !1, line: 59, type: !67)
!423 = !DILocation(line: 59, column: 52, scope: !336)
!424 = !DILocation(line: 61, column: 31, scope: !336)
!425 = !DILocation(line: 61, column: 2, scope: !336)
!426 = !DILocation(line: 62, column: 40, scope: !336)
!427 = !DILocation(line: 62, column: 10, scope: !336)
!428 = !DILocation(line: 62, column: 2, scope: !336)
!429 = !DILocalVariable(name: "_a", arg: 1, scope: !339, file: !1, line: 187, type: !67)
!430 = !DILocation(line: 187, column: 47, scope: !339)
!431 = !DILocalVariable(name: "f", scope: !339, file: !1, line: 189, type: !180)
!432 = !DILocation(line: 189, column: 31, scope: !339)
!433 = !DILocalVariable(name: "r", scope: !339, file: !1, line: 190, type: !66)
!434 = !DILocation(line: 190, column: 6, scope: !339)
!435 = !DILocation(line: 192, column: 2, scope: !339)
!436 = !DILocalVariable(name: "magic_test", scope: !437, file: !1, line: 192, type: !66)
!437 = distinct !DILexicalBlock(scope: !339, file: !1, line: 192, column: 2)
!438 = !DILocation(line: 192, column: 2, scope: !437)
!439 = !DILocation(line: 192, column: 2, scope: !440)
!440 = !DILexicalBlockFile(scope: !437, file: !1, discriminator: 1)
!441 = !DILocation(line: 192, column: 2, scope: !442)
!442 = !DILexicalBlockFile(scope: !443, file: !1, discriminator: 2)
!443 = distinct !DILexicalBlock(scope: !437, file: !1, line: 192, column: 2)
!444 = !DILocation(line: 192, column: 2, scope: !445)
!445 = !DILexicalBlockFile(scope: !437, file: !1, discriminator: 3)
!446 = !DILocation(line: 194, column: 38, scope: !339)
!447 = !DILocation(line: 194, column: 6, scope: !339)
!448 = !DILocation(line: 194, column: 4, scope: !339)
!449 = !DILocation(line: 195, column: 19, scope: !339)
!450 = !DILocation(line: 195, column: 6, scope: !339)
!451 = !DILocation(line: 195, column: 4, scope: !339)
!452 = !DILocation(line: 196, column: 6, scope: !453)
!453 = distinct !DILexicalBlock(scope: !339, file: !1, line: 196, column: 6)
!454 = !DILocation(line: 196, column: 8, scope: !453)
!455 = !DILocation(line: 196, column: 6, scope: !339)
!456 = !DILocation(line: 197, column: 3, scope: !457)
!457 = distinct !DILexicalBlock(scope: !453, file: !1, line: 196, column: 23)
!458 = !DILocation(line: 197, column: 6, scope: !457)
!459 = !DILocation(line: 197, column: 11, scope: !457)
!460 = !DILocation(line: 198, column: 3, scope: !457)
!461 = !DILocation(line: 198, column: 6, scope: !457)
!462 = !DILocation(line: 198, column: 11, scope: !457)
!463 = !DILocation(line: 199, column: 2, scope: !457)
!464 = !DILocation(line: 200, column: 10, scope: !339)
!465 = !DILocation(line: 200, column: 2, scope: !339)
!466 = !DILocation(line: 201, column: 1, scope: !339)
!467 = !DILocalVariable(name: "a", arg: 1, scope: !337, file: !1, line: 66, type: !67)
!468 = !DILocation(line: 66, column: 50, scope: !337)
!469 = !DILocation(line: 68, column: 31, scope: !337)
!470 = !DILocation(line: 68, column: 2, scope: !337)
!471 = !DILocation(line: 69, column: 38, scope: !337)
!472 = !DILocation(line: 69, column: 10, scope: !337)
!473 = !DILocation(line: 69, column: 2, scope: !337)
!474 = !DILocalVariable(name: "_a", arg: 1, scope: !338, file: !1, line: 167, type: !67)
!475 = !DILocation(line: 167, column: 45, scope: !338)
!476 = !DILocalVariable(name: "f", scope: !338, file: !1, line: 169, type: !180)
!477 = !DILocation(line: 169, column: 31, scope: !338)
!478 = !DILocalVariable(name: "r", scope: !338, file: !1, line: 170, type: !66)
!479 = !DILocation(line: 170, column: 6, scope: !338)
!480 = !DILocation(line: 172, column: 2, scope: !338)
!481 = !DILocalVariable(name: "magic_test", scope: !482, file: !1, line: 172, type: !66)
!482 = distinct !DILexicalBlock(scope: !338, file: !1, line: 172, column: 2)
!483 = !DILocation(line: 172, column: 2, scope: !482)
!484 = !DILocation(line: 172, column: 2, scope: !485)
!485 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 1)
!486 = !DILocation(line: 172, column: 2, scope: !487)
!487 = !DILexicalBlockFile(scope: !488, file: !1, discriminator: 2)
!488 = distinct !DILexicalBlock(scope: !482, file: !1, line: 172, column: 2)
!489 = !DILocation(line: 172, column: 2, scope: !490)
!490 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 3)
!491 = !DILocation(line: 174, column: 38, scope: !338)
!492 = !DILocation(line: 174, column: 6, scope: !338)
!493 = !DILocation(line: 174, column: 4, scope: !338)
!494 = !DILocation(line: 175, column: 19, scope: !338)
!495 = !DILocation(line: 175, column: 6, scope: !338)
!496 = !DILocation(line: 175, column: 4, scope: !338)
!497 = !DILocation(line: 176, column: 6, scope: !498)
!498 = distinct !DILexicalBlock(scope: !338, file: !1, line: 176, column: 6)
!499 = !DILocation(line: 176, column: 8, scope: !498)
!500 = !DILocation(line: 176, column: 6, scope: !338)
!501 = !DILocation(line: 177, column: 3, scope: !502)
!502 = distinct !DILexicalBlock(scope: !498, file: !1, line: 176, column: 23)
!503 = !DILocation(line: 177, column: 6, scope: !502)
!504 = !DILocation(line: 177, column: 11, scope: !502)
!505 = !DILocation(line: 178, column: 3, scope: !502)
!506 = !DILocation(line: 178, column: 6, scope: !502)
!507 = !DILocation(line: 178, column: 11, scope: !502)
!508 = !DILocation(line: 179, column: 2, scope: !502)
!509 = !DILocation(line: 180, column: 10, scope: !338)
!510 = !DILocation(line: 180, column: 2, scope: !338)
!511 = !DILocation(line: 181, column: 1, scope: !338)
!512 = !DILocalVariable(name: "f", arg: 1, scope: !341, file: !1, line: 144, type: !180)
!513 = !DILocation(line: 144, column: 43, scope: !341)
!514 = !DILocalVariable(name: "data", scope: !341, file: !1, line: 146, type: !235)
!515 = !DILocation(line: 146, column: 23, scope: !341)
!516 = !DILocalVariable(name: "a", scope: !341, file: !1, line: 147, type: !47)
!517 = !DILocation(line: 147, column: 24, scope: !341)
!518 = !DILocation(line: 147, column: 52, scope: !341)
!519 = !DILocation(line: 147, column: 55, scope: !341)
!520 = !DILocation(line: 147, column: 28, scope: !341)
!521 = !DILocation(line: 148, column: 9, scope: !341)
!522 = !DILocation(line: 148, column: 7, scope: !341)
!523 = !DILocation(line: 149, column: 6, scope: !524)
!524 = distinct !DILexicalBlock(scope: !341, file: !1, line: 149, column: 6)
!525 = !DILocation(line: 149, column: 11, scope: !524)
!526 = !DILocation(line: 149, column: 6, scope: !341)
!527 = !DILocation(line: 150, column: 22, scope: !528)
!528 = distinct !DILexicalBlock(scope: !524, file: !1, line: 149, column: 20)
!529 = !DILocation(line: 150, column: 25, scope: !528)
!530 = !DILocation(line: 150, column: 3, scope: !528)
!531 = !DILocation(line: 151, column: 3, scope: !528)
!532 = !DILocation(line: 153, column: 12, scope: !341)
!533 = !DILocation(line: 153, column: 2, scope: !341)
!534 = !DILocation(line: 153, column: 5, scope: !341)
!535 = !DILocation(line: 153, column: 10, scope: !341)
!536 = !DILocation(line: 154, column: 2, scope: !341)
!537 = !DILocation(line: 154, column: 8, scope: !341)
!538 = !DILocation(line: 154, column: 26, scope: !341)
!539 = !DILocation(line: 155, column: 2, scope: !341)
!540 = !DILocation(line: 155, column: 8, scope: !341)
!541 = !DILocation(line: 155, column: 16, scope: !341)
!542 = !DILocation(line: 156, column: 2, scope: !341)
!543 = !DILocation(line: 156, column: 5, scope: !341)
!544 = !DILocation(line: 156, column: 10, scope: !341)
!545 = !DILocation(line: 157, column: 2, scope: !341)
!546 = !DILocation(line: 157, column: 5, scope: !341)
!547 = !DILocation(line: 157, column: 11, scope: !341)
!548 = !DILocation(line: 158, column: 2, scope: !341)
!549 = !DILocation(line: 158, column: 5, scope: !341)
!550 = !DILocation(line: 158, column: 10, scope: !341)
!551 = !DILocation(line: 159, column: 2, scope: !341)
!552 = !DILocation(line: 159, column: 5, scope: !341)
!553 = !DILocation(line: 159, column: 13, scope: !341)
!554 = !DILocation(line: 160, column: 2, scope: !341)
!555 = !DILocation(line: 161, column: 1, scope: !341)
!556 = !DILocalVariable(name: "f", arg: 1, scope: !342, file: !1, line: 307, type: !180)
!557 = !DILocation(line: 307, column: 57, scope: !342)
!558 = !DILocalVariable(name: "data", scope: !342, file: !1, line: 309, type: !235)
!559 = !DILocation(line: 309, column: 23, scope: !342)
!560 = !DILocation(line: 309, column: 30, scope: !342)
!561 = !DILocation(line: 309, column: 33, scope: !342)
!562 = !DILocalVariable(name: "ret", scope: !342, file: !1, line: 310, type: !66)
!563 = !DILocation(line: 310, column: 6, scope: !342)
!564 = !DILocation(line: 312, column: 36, scope: !342)
!565 = !DILocation(line: 312, column: 39, scope: !342)
!566 = !DILocation(line: 312, column: 8, scope: !342)
!567 = !DILocation(line: 312, column: 6, scope: !342)
!568 = !DILocation(line: 313, column: 6, scope: !569)
!569 = distinct !DILexicalBlock(scope: !342, file: !1, line: 313, column: 6)
!570 = !DILocation(line: 313, column: 10, scope: !569)
!571 = !DILocation(line: 313, column: 6, scope: !342)
!572 = !DILocation(line: 314, column: 11, scope: !569)
!573 = !DILocation(line: 314, column: 3, scope: !569)
!574 = !DILocation(line: 316, column: 6, scope: !575)
!575 = distinct !DILexicalBlock(scope: !342, file: !1, line: 316, column: 6)
!576 = !DILocation(line: 316, column: 12, scope: !575)
!577 = !DILocation(line: 316, column: 23, scope: !575)
!578 = !DILocation(line: 316, column: 6, scope: !342)
!579 = !DILocalVariable(name: "bs", scope: !580, file: !1, line: 317, type: !88)
!580 = distinct !DILexicalBlock(scope: !575, file: !1, line: 316, column: 32)
!581 = !DILocation(line: 317, column: 10, scope: !580)
!582 = !DILocalVariable(name: "bpb", scope: !580, file: !1, line: 317, type: !88)
!583 = !DILocation(line: 317, column: 22, scope: !580)
!584 = !DILocation(line: 318, column: 7, scope: !585)
!585 = distinct !DILexicalBlock(scope: !580, file: !1, line: 318, column: 7)
!586 = !DILocation(line: 318, column: 10, scope: !585)
!587 = !DILocation(line: 318, column: 19, scope: !585)
!588 = !DILocation(line: 318, column: 25, scope: !585)
!589 = !DILocation(line: 318, column: 7, scope: !580)
!590 = !DILocation(line: 321, column: 44, scope: !591)
!591 = distinct !DILexicalBlock(scope: !585, file: !1, line: 318, column: 49)
!592 = !DILocation(line: 321, column: 47, scope: !591)
!593 = !DILocation(line: 321, column: 10, scope: !591)
!594 = !DILocation(line: 321, column: 8, scope: !591)
!595 = !DILocation(line: 322, column: 8, scope: !596)
!596 = distinct !DILexicalBlock(scope: !591, file: !1, line: 322, column: 8)
!597 = !DILocation(line: 322, column: 14, scope: !596)
!598 = !DILocation(line: 322, column: 12, scope: !596)
!599 = !DILocation(line: 322, column: 8, scope: !591)
!600 = !DILocation(line: 323, column: 10, scope: !596)
!601 = !DILocation(line: 323, column: 8, scope: !596)
!602 = !DILocation(line: 323, column: 5, scope: !596)
!603 = !DILocation(line: 324, column: 13, scope: !604)
!604 = distinct !DILexicalBlock(scope: !596, file: !1, line: 324, column: 13)
!605 = !DILocation(line: 324, column: 17, scope: !604)
!606 = !DILocation(line: 324, column: 13, scope: !596)
!607 = !DILocation(line: 325, column: 11, scope: !604)
!608 = !DILocation(line: 325, column: 16, scope: !604)
!609 = !DILocation(line: 325, column: 14, scope: !604)
!610 = !DILocation(line: 325, column: 8, scope: !604)
!611 = !DILocation(line: 325, column: 5, scope: !604)
!612 = !DILocation(line: 326, column: 3, scope: !591)
!613 = !DILocation(line: 327, column: 34, scope: !580)
!614 = !DILocation(line: 327, column: 3, scope: !580)
!615 = !DILocation(line: 327, column: 9, scope: !580)
!616 = !DILocation(line: 327, column: 32, scope: !580)
!617 = !DILocation(line: 329, column: 33, scope: !580)
!618 = !DILocation(line: 329, column: 39, scope: !580)
!619 = !DILocation(line: 329, column: 26, scope: !580)
!620 = !DILocation(line: 328, column: 3, scope: !580)
!621 = !DILocation(line: 328, column: 9, scope: !580)
!622 = !DILocation(line: 329, column: 7, scope: !580)
!623 = !DILocation(line: 330, column: 7, scope: !624)
!624 = distinct !DILexicalBlock(scope: !580, file: !1, line: 330, column: 7)
!625 = !DILocation(line: 330, column: 13, scope: !624)
!626 = !DILocation(line: 330, column: 24, scope: !624)
!627 = !DILocation(line: 330, column: 7, scope: !580)
!628 = !DILocation(line: 331, column: 22, scope: !629)
!629 = distinct !DILexicalBlock(scope: !624, file: !1, line: 330, column: 33)
!630 = !DILocation(line: 331, column: 25, scope: !629)
!631 = !DILocation(line: 331, column: 4, scope: !629)
!632 = !DILocation(line: 333, column: 4, scope: !629)
!633 = !DILocation(line: 335, column: 2, scope: !580)
!634 = !DILocation(line: 337, column: 2, scope: !342)
!635 = !DILocation(line: 337, column: 5, scope: !342)
!636 = !DILocation(line: 337, column: 11, scope: !342)
!637 = !DILocation(line: 340, column: 6, scope: !638)
!638 = distinct !DILexicalBlock(scope: !342, file: !1, line: 340, column: 6)
!639 = !DILocation(line: 340, column: 9, scope: !638)
!640 = !DILocation(line: 340, column: 14, scope: !638)
!641 = !DILocation(line: 340, column: 6, scope: !342)
!642 = !DILocalVariable(name: "val", scope: !643, file: !1, line: 341, type: !644)
!643 = distinct !DILexicalBlock(scope: !638, file: !1, line: 340, column: 38)
!644 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !363, size: 64, align: 64)
!645 = !DILocation(line: 341, column: 30, scope: !643)
!646 = !DILocation(line: 342, column: 22, scope: !643)
!647 = !DILocation(line: 342, column: 28, scope: !643)
!648 = !DILocation(line: 342, column: 8, scope: !643)
!649 = !DILocation(line: 344, column: 30, scope: !643)
!650 = !DILocation(line: 344, column: 35, scope: !643)
!651 = !DILocation(line: 344, column: 3, scope: !643)
!652 = !DILocation(line: 344, column: 9, scope: !643)
!653 = !DILocation(line: 344, column: 18, scope: !643)
!654 = !DILocation(line: 344, column: 28, scope: !643)
!655 = !DILocation(line: 345, column: 3, scope: !643)
!656 = !DILocation(line: 345, column: 9, scope: !643)
!657 = !DILocation(line: 345, column: 18, scope: !643)
!658 = !DILocation(line: 345, column: 30, scope: !643)
!659 = !DILocation(line: 346, column: 3, scope: !643)
!660 = !DILocation(line: 346, column: 9, scope: !643)
!661 = !DILocation(line: 346, column: 18, scope: !643)
!662 = !DILocation(line: 346, column: 35, scope: !643)
!663 = !DILocation(line: 347, column: 3, scope: !643)
!664 = !DILocation(line: 347, column: 9, scope: !643)
!665 = !DILocation(line: 347, column: 18, scope: !643)
!666 = !DILocation(line: 347, column: 21, scope: !643)
!667 = !DILocation(line: 348, column: 3, scope: !643)
!668 = !DILocation(line: 348, column: 9, scope: !643)
!669 = !DILocation(line: 348, column: 18, scope: !643)
!670 = !DILocation(line: 348, column: 21, scope: !643)
!671 = !DILocation(line: 349, column: 3, scope: !643)
!672 = !DILocation(line: 349, column: 9, scope: !643)
!673 = !DILocation(line: 349, column: 18, scope: !643)
!674 = !DILocation(line: 349, column: 21, scope: !643)
!675 = !DILocation(line: 351, column: 7, scope: !643)
!676 = !DILocation(line: 351, column: 13, scope: !643)
!677 = !DILocation(line: 351, column: 30, scope: !643)
!678 = !DILocation(line: 350, column: 3, scope: !643)
!679 = !DILocation(line: 350, column: 9, scope: !643)
!680 = !DILocation(line: 350, column: 18, scope: !643)
!681 = !DILocation(line: 350, column: 23, scope: !643)
!682 = !DILocation(line: 352, column: 29, scope: !643)
!683 = !DILocation(line: 352, column: 34, scope: !643)
!684 = !DILocation(line: 352, column: 3, scope: !643)
!685 = !DILocation(line: 352, column: 9, scope: !643)
!686 = !DILocation(line: 352, column: 18, scope: !643)
!687 = !DILocation(line: 352, column: 27, scope: !643)
!688 = !DILocation(line: 353, column: 23, scope: !643)
!689 = !DILocation(line: 353, column: 28, scope: !643)
!690 = !DILocation(line: 353, column: 3, scope: !643)
!691 = !DILocation(line: 353, column: 9, scope: !643)
!692 = !DILocation(line: 353, column: 18, scope: !643)
!693 = !DILocation(line: 353, column: 21, scope: !643)
!694 = !DILocation(line: 354, column: 3, scope: !643)
!695 = !DILocation(line: 354, column: 9, scope: !643)
!696 = !DILocation(line: 354, column: 18, scope: !643)
!697 = !DILocation(line: 354, column: 24, scope: !643)
!698 = !DILocation(line: 355, column: 3, scope: !643)
!699 = !DILocation(line: 355, column: 9, scope: !643)
!700 = !DILocation(line: 355, column: 24, scope: !643)
!701 = !DILocation(line: 355, column: 27, scope: !643)
!702 = !DILocation(line: 356, column: 35, scope: !643)
!703 = !DILocation(line: 356, column: 41, scope: !643)
!704 = !DILocation(line: 356, column: 34, scope: !643)
!705 = !DILocation(line: 356, column: 3, scope: !643)
!706 = !DILocation(line: 356, column: 9, scope: !643)
!707 = !DILocation(line: 356, column: 24, scope: !643)
!708 = !DILocation(line: 356, column: 32, scope: !643)
!709 = !DILocation(line: 357, column: 3, scope: !643)
!710 = !DILocation(line: 357, column: 9, scope: !643)
!711 = !DILocation(line: 357, column: 24, scope: !643)
!712 = !DILocation(line: 357, column: 27, scope: !643)
!713 = !DILocation(line: 358, column: 2, scope: !643)
!714 = !DILocation(line: 359, column: 25, scope: !715)
!715 = distinct !DILexicalBlock(scope: !716, file: !1, line: 359, column: 7)
!716 = distinct !DILexicalBlock(scope: !638, file: !1, line: 358, column: 9)
!717 = !DILocation(line: 359, column: 31, scope: !715)
!718 = !DILocation(line: 359, column: 41, scope: !715)
!719 = !DILocation(line: 359, column: 47, scope: !715)
!720 = !DILocation(line: 359, column: 7, scope: !715)
!721 = !DILocation(line: 359, column: 7, scope: !716)
!722 = !DILocation(line: 360, column: 22, scope: !723)
!723 = distinct !DILexicalBlock(scope: !715, file: !1, line: 359, column: 67)
!724 = !DILocation(line: 360, column: 25, scope: !723)
!725 = !DILocation(line: 360, column: 4, scope: !723)
!726 = !DILocation(line: 362, column: 3, scope: !723)
!727 = !DILocation(line: 363, column: 3, scope: !716)
!728 = !DILocation(line: 363, column: 9, scope: !716)
!729 = !DILocation(line: 363, column: 24, scope: !716)
!730 = !DILocation(line: 363, column: 27, scope: !716)
!731 = !DILocation(line: 364, column: 35, scope: !716)
!732 = !DILocation(line: 364, column: 41, scope: !716)
!733 = !DILocation(line: 364, column: 34, scope: !716)
!734 = !DILocation(line: 364, column: 3, scope: !716)
!735 = !DILocation(line: 364, column: 9, scope: !716)
!736 = !DILocation(line: 364, column: 24, scope: !716)
!737 = !DILocation(line: 364, column: 32, scope: !716)
!738 = !DILocation(line: 365, column: 3, scope: !716)
!739 = !DILocation(line: 365, column: 9, scope: !716)
!740 = !DILocation(line: 365, column: 24, scope: !716)
!741 = !DILocation(line: 365, column: 27, scope: !716)
!742 = !DILocation(line: 367, column: 42, scope: !342)
!743 = !DILocation(line: 367, column: 45, scope: !342)
!744 = !DILocation(line: 367, column: 8, scope: !342)
!745 = !DILocation(line: 367, column: 6, scope: !342)
!746 = !DILocation(line: 368, column: 6, scope: !747)
!747 = distinct !DILexicalBlock(scope: !342, file: !1, line: 368, column: 6)
!748 = !DILocation(line: 368, column: 10, scope: !747)
!749 = !DILocation(line: 368, column: 6, scope: !342)
!750 = !DILocation(line: 369, column: 13, scope: !751)
!751 = distinct !DILexicalBlock(scope: !747, file: !1, line: 368, column: 22)
!752 = !DILocation(line: 369, column: 3, scope: !751)
!753 = !DILocation(line: 369, column: 6, scope: !751)
!754 = !DILocation(line: 369, column: 11, scope: !751)
!755 = !DILocation(line: 370, column: 3, scope: !751)
!756 = !DILocation(line: 372, column: 2, scope: !342)
!757 = !DILocation(line: 373, column: 1, scope: !342)
!758 = !DILocalVariable(name: "f", arg: 1, scope: !350, file: !1, line: 445, type: !180)
!759 = !DILocation(line: 445, column: 58, scope: !350)
!760 = !DILocalVariable(name: "data", scope: !350, file: !1, line: 447, type: !235)
!761 = !DILocation(line: 447, column: 23, scope: !350)
!762 = !DILocation(line: 447, column: 53, scope: !350)
!763 = !DILocation(line: 447, column: 56, scope: !350)
!764 = !DILocation(line: 447, column: 30, scope: !350)
!765 = !DILocalVariable(name: "ret", scope: !350, file: !1, line: 448, type: !66)
!766 = !DILocation(line: 448, column: 6, scope: !350)
!767 = !DILocalVariable(name: "r1", scope: !350, file: !1, line: 448, type: !66)
!768 = !DILocation(line: 448, column: 11, scope: !350)
!769 = !DILocation(line: 450, column: 25, scope: !350)
!770 = !DILocation(line: 450, column: 28, scope: !350)
!771 = !DILocation(line: 450, column: 8, scope: !350)
!772 = !DILocation(line: 450, column: 6, scope: !350)
!773 = !DILocation(line: 451, column: 6, scope: !774)
!774 = distinct !DILexicalBlock(scope: !350, file: !1, line: 451, column: 6)
!775 = !DILocation(line: 451, column: 10, scope: !774)
!776 = !DILocation(line: 451, column: 6, scope: !350)
!777 = !DILocation(line: 453, column: 7, scope: !778)
!778 = distinct !DILexicalBlock(scope: !774, file: !1, line: 451, column: 25)
!779 = !DILocation(line: 453, column: 13, scope: !778)
!780 = !DILocation(line: 453, column: 38, scope: !778)
!781 = !DILocation(line: 453, column: 44, scope: !778)
!782 = !DILocation(line: 453, column: 51, scope: !778)
!783 = !DILocation(line: 453, column: 36, scope: !778)
!784 = !DILocation(line: 452, column: 3, scope: !778)
!785 = !DILocation(line: 452, column: 9, scope: !778)
!786 = !DILocation(line: 452, column: 19, scope: !778)
!787 = !DILocation(line: 454, column: 32, scope: !778)
!788 = !DILocation(line: 454, column: 35, scope: !778)
!789 = !DILocation(line: 455, column: 7, scope: !778)
!790 = !DILocation(line: 455, column: 13, scope: !778)
!791 = !DILocation(line: 456, column: 7, scope: !778)
!792 = !DILocation(line: 456, column: 13, scope: !778)
!793 = !DILocation(line: 456, column: 38, scope: !778)
!794 = !DILocation(line: 456, column: 44, scope: !778)
!795 = !DILocation(line: 456, column: 51, scope: !778)
!796 = !DILocation(line: 456, column: 36, scope: !778)
!797 = !DILocation(line: 454, column: 9, scope: !778)
!798 = !DILocation(line: 454, column: 7, scope: !778)
!799 = !DILocation(line: 457, column: 7, scope: !800)
!800 = distinct !DILexicalBlock(scope: !778, file: !1, line: 457, column: 7)
!801 = !DILocation(line: 457, column: 10, scope: !800)
!802 = !DILocation(line: 457, column: 15, scope: !800)
!803 = !DILocation(line: 457, column: 38, scope: !800)
!804 = !DILocation(line: 457, column: 41, scope: !805)
!805 = !DILexicalBlockFile(scope: !800, file: !1, discriminator: 1)
!806 = !DILocation(line: 457, column: 45, scope: !805)
!807 = !DILocation(line: 457, column: 7, scope: !805)
!808 = !DILocation(line: 458, column: 20, scope: !809)
!809 = distinct !DILexicalBlock(scope: !800, file: !1, line: 457, column: 60)
!810 = !DILocation(line: 458, column: 26, scope: !809)
!811 = !DILocation(line: 458, column: 38, scope: !809)
!812 = !DILocation(line: 458, column: 44, scope: !809)
!813 = !DILocation(line: 458, column: 4, scope: !809)
!814 = !DILocation(line: 459, column: 20, scope: !809)
!815 = !DILocation(line: 459, column: 26, scope: !809)
!816 = !DILocation(line: 459, column: 36, scope: !809)
!817 = !DILocation(line: 459, column: 40, scope: !809)
!818 = !DILocation(line: 459, column: 46, scope: !809)
!819 = !DILocation(line: 459, column: 4, scope: !809)
!820 = !DILocation(line: 460, column: 20, scope: !809)
!821 = !DILocation(line: 460, column: 26, scope: !809)
!822 = !DILocation(line: 460, column: 36, scope: !809)
!823 = !DILocation(line: 460, column: 41, scope: !809)
!824 = !DILocation(line: 460, column: 47, scope: !809)
!825 = !DILocation(line: 460, column: 57, scope: !809)
!826 = !DILocation(line: 460, column: 4, scope: !809)
!827 = !DILocation(line: 461, column: 33, scope: !809)
!828 = !DILocation(line: 461, column: 36, scope: !809)
!829 = !DILocation(line: 462, column: 8, scope: !809)
!830 = !DILocation(line: 462, column: 14, scope: !809)
!831 = !DILocation(line: 461, column: 10, scope: !809)
!832 = !DILocation(line: 461, column: 8, scope: !809)
!833 = !DILocation(line: 463, column: 3, scope: !809)
!834 = !DILocation(line: 464, column: 2, scope: !778)
!835 = !DILocation(line: 465, column: 13, scope: !350)
!836 = !DILocation(line: 465, column: 19, scope: !350)
!837 = !DILocation(line: 465, column: 2, scope: !350)
!838 = !DILocation(line: 466, column: 36, scope: !350)
!839 = !DILocation(line: 466, column: 39, scope: !350)
!840 = !DILocation(line: 466, column: 7, scope: !350)
!841 = !DILocation(line: 466, column: 5, scope: !350)
!842 = !DILocation(line: 467, column: 10, scope: !350)
!843 = !DILocation(line: 467, column: 15, scope: !350)
!844 = !DILocation(line: 467, column: 13, scope: !350)
!845 = !DILocation(line: 467, column: 21, scope: !846)
!846 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 1)
!847 = !DILocation(line: 467, column: 10, scope: !846)
!848 = !DILocation(line: 467, column: 26, scope: !849)
!849 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 2)
!850 = !DILocation(line: 467, column: 10, scope: !849)
!851 = !DILocation(line: 467, column: 10, scope: !852)
!852 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 3)
!853 = !DILocation(line: 467, column: 2, scope: !852)
!854 = !DILocalVariable(name: "f", arg: 1, scope: !358, file: !1, line: 471, type: !180)
!855 = !DILocation(line: 471, column: 57, scope: !358)
!856 = !DILocalVariable(name: "data", scope: !358, file: !1, line: 473, type: !235)
!857 = !DILocation(line: 473, column: 23, scope: !358)
!858 = !DILocation(line: 473, column: 53, scope: !358)
!859 = !DILocation(line: 473, column: 56, scope: !358)
!860 = !DILocation(line: 473, column: 30, scope: !358)
!861 = !DILocation(line: 474, column: 7, scope: !358)
!862 = !DILocation(line: 474, column: 13, scope: !358)
!863 = !DILocation(line: 474, column: 2, scope: !358)
!864 = !DILocation(line: 475, column: 7, scope: !358)
!865 = !DILocation(line: 475, column: 2, scope: !358)
!866 = !DILocation(line: 476, column: 2, scope: !358)
!867 = !DILocation(line: 476, column: 5, scope: !358)
!868 = !DILocation(line: 476, column: 10, scope: !358)
!869 = !DILocation(line: 477, column: 2, scope: !358)
!870 = !DILocalVariable(name: "f", arg: 1, scope: !359, file: !1, line: 379, type: !180)
!871 = !DILocation(line: 379, column: 60, scope: !359)
!872 = !DILocalVariable(name: "key", arg: 2, scope: !359, file: !1, line: 380, type: !123)
!873 = !DILocation(line: 380, column: 17, scope: !359)
!874 = !DILocalVariable(name: "value", arg: 3, scope: !359, file: !1, line: 380, type: !123)
!875 = !DILocation(line: 380, column: 34, scope: !359)
!876 = !DILocalVariable(name: "data", scope: !359, file: !1, line: 382, type: !235)
!877 = !DILocation(line: 382, column: 23, scope: !359)
!878 = !DILocation(line: 382, column: 53, scope: !359)
!879 = !DILocation(line: 382, column: 56, scope: !359)
!880 = !DILocation(line: 382, column: 30, scope: !359)
!881 = !DILocation(line: 384, column: 13, scope: !882)
!882 = distinct !DILexicalBlock(scope: !359, file: !1, line: 384, column: 6)
!883 = !DILocation(line: 384, column: 6, scope: !882)
!884 = !DILocation(line: 384, column: 39, scope: !882)
!885 = !DILocation(line: 384, column: 6, scope: !359)
!886 = !DILocation(line: 385, column: 7, scope: !887)
!887 = distinct !DILexicalBlock(scope: !888, file: !1, line: 385, column: 7)
!888 = distinct !DILexicalBlock(scope: !882, file: !1, line: 384, column: 45)
!889 = !DILocation(line: 385, column: 13, scope: !887)
!890 = !DILocation(line: 385, column: 21, scope: !887)
!891 = !DILocation(line: 385, column: 26, scope: !892)
!892 = !DILexicalBlockFile(scope: !887, file: !1, discriminator: 1)
!893 = !DILocation(line: 385, column: 35, scope: !892)
!894 = !DILocation(line: 385, column: 42, scope: !892)
!895 = !DILocation(line: 385, column: 45, scope: !896)
!896 = !DILexicalBlockFile(scope: !887, file: !1, discriminator: 2)
!897 = !DILocation(line: 385, column: 54, scope: !896)
!898 = !DILocation(line: 385, column: 62, scope: !896)
!899 = !DILocation(line: 386, column: 7, scope: !887)
!900 = !DILocation(line: 386, column: 16, scope: !887)
!901 = !DILocation(line: 385, column: 7, scope: !902)
!902 = !DILexicalBlockFile(scope: !888, file: !1, discriminator: 3)
!903 = !DILocation(line: 387, column: 4, scope: !887)
!904 = !DILocation(line: 388, column: 29, scope: !888)
!905 = !DILocation(line: 388, column: 38, scope: !888)
!906 = !DILocation(line: 388, column: 3, scope: !888)
!907 = !DILocation(line: 388, column: 9, scope: !888)
!908 = !DILocation(line: 388, column: 27, scope: !888)
!909 = !DILocation(line: 389, column: 7, scope: !910)
!910 = distinct !DILexicalBlock(scope: !888, file: !1, line: 389, column: 7)
!911 = !DILocation(line: 389, column: 13, scope: !910)
!912 = !DILocation(line: 389, column: 31, scope: !910)
!913 = !DILocation(line: 389, column: 7, scope: !888)
!914 = !DILocation(line: 390, column: 4, scope: !910)
!915 = !DILocation(line: 390, column: 10, scope: !910)
!916 = !DILocation(line: 390, column: 28, scope: !910)
!917 = !DILocation(line: 391, column: 3, scope: !888)
!918 = !DILocation(line: 392, column: 20, scope: !919)
!919 = distinct !DILexicalBlock(scope: !882, file: !1, line: 392, column: 13)
!920 = !DILocation(line: 392, column: 13, scope: !919)
!921 = !DILocation(line: 392, column: 36, scope: !919)
!922 = !DILocation(line: 392, column: 13, scope: !882)
!923 = !DILocation(line: 393, column: 7, scope: !924)
!924 = distinct !DILexicalBlock(scope: !925, file: !1, line: 393, column: 7)
!925 = distinct !DILexicalBlock(scope: !919, file: !1, line: 392, column: 42)
!926 = !DILocation(line: 393, column: 13, scope: !924)
!927 = !DILocation(line: 393, column: 7, scope: !925)
!928 = !DILocation(line: 394, column: 4, scope: !924)
!929 = !DILocation(line: 395, column: 32, scope: !925)
!930 = !DILocation(line: 395, column: 24, scope: !925)
!931 = !DILocation(line: 395, column: 19, scope: !925)
!932 = !DILocation(line: 395, column: 3, scope: !925)
!933 = !DILocation(line: 395, column: 9, scope: !925)
!934 = !DILocation(line: 395, column: 17, scope: !925)
!935 = !DILocation(line: 396, column: 7, scope: !936)
!936 = distinct !DILexicalBlock(scope: !925, file: !1, line: 396, column: 7)
!937 = !DILocation(line: 396, column: 13, scope: !936)
!938 = !DILocation(line: 396, column: 21, scope: !936)
!939 = !DILocation(line: 396, column: 26, scope: !936)
!940 = !DILocation(line: 396, column: 29, scope: !941)
!941 = !DILexicalBlockFile(scope: !936, file: !1, discriminator: 1)
!942 = !DILocation(line: 396, column: 35, scope: !941)
!943 = !DILocation(line: 396, column: 7, scope: !941)
!944 = !DILocation(line: 397, column: 4, scope: !945)
!945 = distinct !DILexicalBlock(scope: !936, file: !1, line: 396, column: 41)
!946 = !DILocation(line: 397, column: 10, scope: !945)
!947 = !DILocation(line: 397, column: 18, scope: !945)
!948 = !DILocation(line: 398, column: 4, scope: !945)
!949 = !DILocation(line: 400, column: 7, scope: !950)
!950 = distinct !DILexicalBlock(scope: !925, file: !1, line: 400, column: 7)
!951 = !DILocation(line: 400, column: 13, scope: !950)
!952 = !DILocation(line: 400, column: 21, scope: !950)
!953 = !DILocation(line: 400, column: 7, scope: !925)
!954 = !DILocation(line: 404, column: 4, scope: !955)
!955 = distinct !DILexicalBlock(scope: !950, file: !1, line: 400, column: 27)
!956 = !DILocation(line: 404, column: 10, scope: !955)
!957 = !DILocation(line: 404, column: 18, scope: !955)
!958 = !DILocation(line: 406, column: 3, scope: !955)
!959 = !DILocation(line: 407, column: 3, scope: !925)
!960 = !DILocation(line: 413, column: 2, scope: !359)
!961 = !DILocation(line: 414, column: 1, scope: !359)
!962 = !DILocalVariable(name: "f", arg: 1, scope: !343, file: !1, line: 420, type: !180)
!963 = !DILocation(line: 420, column: 58, scope: !343)
!964 = !DILocalVariable(name: "buff", arg: 2, scope: !343, file: !1, line: 421, type: !86)
!965 = !DILocation(line: 421, column: 17, scope: !343)
!966 = !DILocalVariable(name: "length", arg: 3, scope: !343, file: !1, line: 421, type: !88)
!967 = !DILocation(line: 421, column: 30, scope: !343)
!968 = !DILocalVariable(name: "data", scope: !343, file: !1, line: 423, type: !235)
!969 = !DILocation(line: 423, column: 23, scope: !343)
!970 = !DILocation(line: 423, column: 53, scope: !343)
!971 = !DILocation(line: 423, column: 56, scope: !343)
!972 = !DILocation(line: 423, column: 30, scope: !343)
!973 = !DILocalVariable(name: "ret", scope: !343, file: !1, line: 424, type: !66)
!974 = !DILocation(line: 424, column: 6, scope: !343)
!975 = !DILocation(line: 427, column: 20, scope: !343)
!976 = !DILocation(line: 427, column: 2, scope: !343)
!977 = !DILocation(line: 427, column: 8, scope: !343)
!978 = !DILocation(line: 427, column: 17, scope: !343)
!979 = !DILocation(line: 428, column: 6, scope: !980)
!980 = distinct !DILexicalBlock(scope: !343, file: !1, line: 428, column: 6)
!981 = !DILocation(line: 428, column: 9, scope: !980)
!982 = !DILocation(line: 428, column: 14, scope: !980)
!983 = !DILocation(line: 428, column: 6, scope: !343)
!984 = !DILocation(line: 429, column: 28, scope: !980)
!985 = !DILocation(line: 429, column: 34, scope: !980)
!986 = !DILocation(line: 429, column: 42, scope: !980)
!987 = !DILocation(line: 429, column: 48, scope: !980)
!988 = !DILocation(line: 429, column: 17, scope: !980)
!989 = !DILocation(line: 429, column: 3, scope: !980)
!990 = !DILocation(line: 429, column: 9, scope: !980)
!991 = !DILocation(line: 429, column: 15, scope: !980)
!992 = !DILocation(line: 432, column: 25, scope: !343)
!993 = !DILocation(line: 432, column: 2, scope: !343)
!994 = !DILocation(line: 432, column: 8, scope: !343)
!995 = !DILocation(line: 432, column: 15, scope: !343)
!996 = !DILocation(line: 432, column: 23, scope: !343)
!997 = !DILocation(line: 433, column: 26, scope: !343)
!998 = !DILocation(line: 433, column: 2, scope: !343)
!999 = !DILocation(line: 433, column: 8, scope: !343)
!1000 = !DILocation(line: 433, column: 15, scope: !343)
!1001 = !DILocation(line: 433, column: 24, scope: !343)
!1002 = !DILocation(line: 434, column: 30, scope: !1003)
!1003 = distinct !DILexicalBlock(scope: !343, file: !1, line: 434, column: 6)
!1004 = !DILocation(line: 434, column: 33, scope: !1003)
!1005 = !DILocation(line: 434, column: 13, scope: !1003)
!1006 = !DILocation(line: 434, column: 11, scope: !1003)
!1007 = !DILocation(line: 434, column: 43, scope: !1003)
!1008 = !DILocation(line: 434, column: 6, scope: !343)
!1009 = !DILocation(line: 435, column: 11, scope: !1003)
!1010 = !DILocation(line: 435, column: 3, scope: !1003)
!1011 = !DILocation(line: 437, column: 2, scope: !343)
!1012 = !DILocation(line: 438, column: 1, scope: !343)
!1013 = !DILocalVariable(name: "f", arg: 1, scope: !347, file: !1, line: 221, type: !180)
!1014 = !DILocation(line: 221, column: 64, scope: !347)
!1015 = !DILocalVariable(name: "data", arg: 2, scope: !347, file: !1, line: 222, type: !235)
!1016 = !DILocation(line: 222, column: 26, scope: !347)
!1017 = !DILocalVariable(name: "ret", scope: !347, file: !1, line: 225, type: !66)
!1018 = !DILocation(line: 225, column: 6, scope: !347)
!1019 = !DILocation(line: 230, column: 2, scope: !347)
!1020 = !DILocation(line: 230, column: 8, scope: !347)
!1021 = !DILocation(line: 230, column: 17, scope: !347)
!1022 = !DILocation(line: 231, column: 26, scope: !347)
!1023 = !DILocation(line: 231, column: 32, scope: !347)
!1024 = !DILocation(line: 231, column: 2, scope: !347)
!1025 = !DILocation(line: 231, column: 8, scope: !347)
!1026 = !DILocation(line: 231, column: 15, scope: !347)
!1027 = !DILocation(line: 231, column: 24, scope: !347)
!1028 = !DILocation(line: 232, column: 27, scope: !347)
!1029 = !DILocation(line: 232, column: 33, scope: !347)
!1030 = !DILocation(line: 232, column: 2, scope: !347)
!1031 = !DILocation(line: 232, column: 8, scope: !347)
!1032 = !DILocation(line: 232, column: 15, scope: !347)
!1033 = !DILocation(line: 232, column: 25, scope: !347)
!1034 = !DILocation(line: 233, column: 6, scope: !1035)
!1035 = distinct !DILexicalBlock(scope: !347, file: !1, line: 233, column: 6)
!1036 = !DILocation(line: 233, column: 9, scope: !1035)
!1037 = !DILocation(line: 233, column: 14, scope: !1035)
!1038 = !DILocation(line: 233, column: 6, scope: !347)
!1039 = !DILocation(line: 245, column: 32, scope: !1040)
!1040 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 233, column: 36)
!1041 = !DILocation(line: 245, column: 38, scope: !1040)
!1042 = !DILocation(line: 246, column: 8, scope: !1040)
!1043 = !DILocation(line: 246, column: 14, scope: !1040)
!1044 = !DILocation(line: 245, column: 10, scope: !1040)
!1045 = !DILocation(line: 245, column: 8, scope: !1040)
!1046 = !DILocation(line: 247, column: 2, scope: !1040)
!1047 = !DILocation(line: 247, column: 13, scope: !1048)
!1048 = !DILexicalBlockFile(scope: !1049, file: !1, discriminator: 1)
!1049 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 247, column: 13)
!1050 = !DILocation(line: 247, column: 16, scope: !1048)
!1051 = !DILocation(line: 247, column: 21, scope: !1048)
!1052 = !DILocation(line: 248, column: 30, scope: !1053)
!1053 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 247, column: 45)
!1054 = !DILocation(line: 248, column: 36, scope: !1053)
!1055 = !DILocation(line: 248, column: 46, scope: !1053)
!1056 = !DILocation(line: 248, column: 52, scope: !1053)
!1057 = !DILocation(line: 248, column: 9, scope: !1053)
!1058 = !DILocation(line: 248, column: 7, scope: !1053)
!1059 = !DILocation(line: 249, column: 2, scope: !1053)
!1060 = !DILocalVariable(name: "dict_size", scope: !1061, file: !1, line: 250, type: !66)
!1061 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 249, column: 9)
!1062 = !DILocation(line: 250, column: 7, scope: !1061)
!1063 = !DILocation(line: 250, column: 19, scope: !1061)
!1064 = !DILocation(line: 250, column: 25, scope: !1061)
!1065 = !DILocation(line: 250, column: 34, scope: !1061)
!1066 = !DILocalVariable(name: "ds", scope: !1061, file: !1, line: 251, type: !66)
!1067 = !DILocation(line: 251, column: 7, scope: !1061)
!1068 = !DILocalVariable(name: "log2dic", scope: !1061, file: !1, line: 251, type: !66)
!1069 = !DILocation(line: 251, column: 11, scope: !1061)
!1070 = !DILocalVariable(name: "wedges", scope: !1061, file: !1, line: 251, type: !66)
!1071 = !DILocation(line: 251, column: 20, scope: !1061)
!1072 = !DILocation(line: 254, column: 7, scope: !1073)
!1073 = distinct !DILexicalBlock(scope: !1061, file: !1, line: 254, column: 7)
!1074 = !DILocation(line: 254, column: 17, scope: !1073)
!1075 = !DILocation(line: 254, column: 29, scope: !1073)
!1076 = !DILocation(line: 254, column: 32, scope: !1077)
!1077 = !DILexicalBlockFile(scope: !1073, file: !1, discriminator: 1)
!1078 = !DILocation(line: 254, column: 42, scope: !1077)
!1079 = !DILocation(line: 254, column: 7, scope: !1077)
!1080 = !DILocation(line: 255, column: 22, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1073, file: !1, line: 254, column: 55)
!1082 = !DILocation(line: 255, column: 25, scope: !1081)
!1083 = !DILocation(line: 257, column: 8, scope: !1081)
!1084 = !DILocation(line: 255, column: 4, scope: !1081)
!1085 = !DILocation(line: 258, column: 4, scope: !1081)
!1086 = !DILocation(line: 260, column: 16, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !1061, file: !1, line: 260, column: 3)
!1088 = !DILocation(line: 260, column: 8, scope: !1087)
!1089 = !DILocation(line: 260, column: 22, scope: !1090)
!1090 = !DILexicalBlockFile(scope: !1091, file: !1, discriminator: 1)
!1091 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 260, column: 3)
!1092 = !DILocation(line: 260, column: 30, scope: !1090)
!1093 = !DILocation(line: 260, column: 3, scope: !1090)
!1094 = !DILocation(line: 261, column: 8, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 261, column: 8)
!1096 = distinct !DILexicalBlock(scope: !1091, file: !1, line: 260, column: 48)
!1097 = !DILocation(line: 261, column: 26, scope: !1095)
!1098 = !DILocation(line: 261, column: 23, scope: !1095)
!1099 = !DILocation(line: 261, column: 18, scope: !1095)
!1100 = !DILocation(line: 261, column: 8, scope: !1096)
!1101 = !DILocation(line: 262, column: 5, scope: !1095)
!1102 = !DILocation(line: 263, column: 3, scope: !1096)
!1103 = !DILocation(line: 260, column: 44, scope: !1104)
!1104 = !DILexicalBlockFile(scope: !1091, file: !1, discriminator: 2)
!1105 = !DILocation(line: 260, column: 3, scope: !1104)
!1106 = !DILocation(line: 264, column: 7, scope: !1107)
!1107 = distinct !DILexicalBlock(scope: !1061, file: !1, line: 264, column: 7)
!1108 = !DILocation(line: 264, column: 25, scope: !1107)
!1109 = !DILocation(line: 264, column: 22, scope: !1107)
!1110 = !DILocation(line: 264, column: 17, scope: !1107)
!1111 = !DILocation(line: 264, column: 7, scope: !1061)
!1112 = !DILocation(line: 265, column: 11, scope: !1113)
!1113 = distinct !DILexicalBlock(scope: !1107, file: !1, line: 264, column: 35)
!1114 = !DILocation(line: 267, column: 15, scope: !1113)
!1115 = !DILocation(line: 267, column: 12, scope: !1113)
!1116 = !DILocation(line: 267, column: 26, scope: !1113)
!1117 = !DILocation(line: 267, column: 24, scope: !1113)
!1118 = !DILocation(line: 267, column: 46, scope: !1113)
!1119 = !DILocation(line: 267, column: 54, scope: !1113)
!1120 = !DILocation(line: 267, column: 42, scope: !1113)
!1121 = !DILocation(line: 267, column: 37, scope: !1113)
!1122 = !DILocation(line: 266, column: 11, scope: !1113)
!1123 = !DILocation(line: 268, column: 3, scope: !1113)
!1124 = !DILocation(line: 269, column: 11, scope: !1107)
!1125 = !DILocation(line: 270, column: 10, scope: !1061)
!1126 = !DILocation(line: 270, column: 17, scope: !1061)
!1127 = !DILocation(line: 270, column: 23, scope: !1061)
!1128 = !DILocation(line: 270, column: 34, scope: !1061)
!1129 = !DILocation(line: 270, column: 42, scope: !1061)
!1130 = !DILocation(line: 270, column: 31, scope: !1061)
!1131 = !DILocation(line: 270, column: 6, scope: !1061)
!1132 = !DILocation(line: 272, column: 3, scope: !1061)
!1133 = !DILocation(line: 272, column: 9, scope: !1061)
!1134 = !DILocation(line: 272, column: 15, scope: !1061)
!1135 = !DILocation(line: 274, column: 3, scope: !1061)
!1136 = !DILocation(line: 274, column: 9, scope: !1061)
!1137 = !DILocation(line: 274, column: 23, scope: !1061)
!1138 = !DILocation(line: 275, column: 3, scope: !1061)
!1139 = !DILocation(line: 275, column: 9, scope: !1061)
!1140 = !DILocation(line: 275, column: 23, scope: !1061)
!1141 = !DILocation(line: 276, column: 3, scope: !1061)
!1142 = !DILocation(line: 276, column: 9, scope: !1061)
!1143 = !DILocation(line: 276, column: 23, scope: !1061)
!1144 = !DILocation(line: 277, column: 3, scope: !1061)
!1145 = !DILocation(line: 277, column: 9, scope: !1061)
!1146 = !DILocation(line: 277, column: 23, scope: !1061)
!1147 = !DILocation(line: 278, column: 3, scope: !1061)
!1148 = !DILocation(line: 278, column: 9, scope: !1061)
!1149 = !DILocation(line: 278, column: 23, scope: !1061)
!1150 = !DILocation(line: 279, column: 40, scope: !1061)
!1151 = !DILocation(line: 279, column: 25, scope: !1061)
!1152 = !DILocation(line: 279, column: 3, scope: !1061)
!1153 = !DILocation(line: 279, column: 9, scope: !1061)
!1154 = !DILocation(line: 279, column: 23, scope: !1061)
!1155 = !DILocation(line: 280, column: 3, scope: !1061)
!1156 = !DILocation(line: 280, column: 9, scope: !1061)
!1157 = !DILocation(line: 280, column: 16, scope: !1061)
!1158 = !DILocation(line: 280, column: 25, scope: !1061)
!1159 = !DILocation(line: 281, column: 3, scope: !1061)
!1160 = !DILocation(line: 281, column: 9, scope: !1061)
!1161 = !DILocation(line: 281, column: 16, scope: !1061)
!1162 = !DILocation(line: 281, column: 26, scope: !1061)
!1163 = !DILocation(line: 283, column: 28, scope: !1061)
!1164 = !DILocation(line: 283, column: 34, scope: !1061)
!1165 = !DILocation(line: 283, column: 43, scope: !1061)
!1166 = !DILocation(line: 283, column: 49, scope: !1061)
!1167 = !DILocation(line: 283, column: 9, scope: !1061)
!1168 = !DILocation(line: 283, column: 7, scope: !1061)
!1169 = !DILocation(line: 285, column: 6, scope: !1170)
!1170 = distinct !DILexicalBlock(scope: !347, file: !1, line: 285, column: 6)
!1171 = !DILocation(line: 285, column: 10, scope: !1170)
!1172 = !DILocation(line: 285, column: 6, scope: !347)
!1173 = !DILocation(line: 286, column: 3, scope: !1170)
!1174 = !DILocation(line: 288, column: 10, scope: !347)
!1175 = !DILocation(line: 288, column: 2, scope: !347)
!1176 = !DILocation(line: 290, column: 21, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !347, file: !1, line: 288, column: 15)
!1178 = !DILocation(line: 290, column: 24, scope: !1177)
!1179 = !DILocation(line: 290, column: 3, scope: !1177)
!1180 = !DILocation(line: 293, column: 3, scope: !1177)
!1181 = !DILocation(line: 295, column: 21, scope: !1177)
!1182 = !DILocation(line: 295, column: 24, scope: !1177)
!1183 = !DILocation(line: 295, column: 3, scope: !1177)
!1184 = !DILocation(line: 298, column: 3, scope: !1177)
!1185 = !DILocation(line: 300, column: 2, scope: !347)
!1186 = !DILocation(line: 301, column: 1, scope: !347)
!1187 = !DILocalVariable(name: "f", arg: 1, scope: !344, file: !1, line: 488, type: !180)
!1188 = !DILocation(line: 488, column: 47, scope: !344)
!1189 = !DILocalVariable(name: "data", arg: 2, scope: !344, file: !1, line: 489, type: !235)
!1190 = !DILocation(line: 489, column: 26, scope: !344)
!1191 = !DILocalVariable(name: "finishing", arg: 3, scope: !344, file: !1, line: 489, type: !66)
!1192 = !DILocation(line: 489, column: 36, scope: !344)
!1193 = !DILocalVariable(name: "ret", scope: !344, file: !1, line: 491, type: !66)
!1194 = !DILocation(line: 491, column: 6, scope: !344)
!1195 = !DILocation(line: 493, column: 2, scope: !344)
!1196 = !DILocation(line: 494, column: 7, scope: !1197)
!1197 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 494, column: 7)
!1198 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 493, column: 11)
!1199 = distinct !DILexicalBlock(scope: !1200, file: !1, line: 493, column: 2)
!1200 = distinct !DILexicalBlock(scope: !344, file: !1, line: 493, column: 2)
!1201 = !DILocation(line: 494, column: 13, scope: !1197)
!1202 = !DILocation(line: 494, column: 20, scope: !1197)
!1203 = !DILocation(line: 494, column: 30, scope: !1197)
!1204 = !DILocation(line: 494, column: 7, scope: !1198)
!1205 = !DILocation(line: 495, column: 23, scope: !1206)
!1206 = distinct !DILexicalBlock(scope: !1197, file: !1, line: 494, column: 36)
!1207 = !DILocation(line: 495, column: 29, scope: !1206)
!1208 = !DILocation(line: 495, column: 4, scope: !1206)
!1209 = !DILocation(line: 495, column: 10, scope: !1206)
!1210 = !DILocation(line: 495, column: 20, scope: !1206)
!1211 = !DILocation(line: 496, column: 33, scope: !1206)
!1212 = !DILocation(line: 496, column: 36, scope: !1206)
!1213 = !DILocation(line: 497, column: 8, scope: !1206)
!1214 = !DILocation(line: 497, column: 14, scope: !1206)
!1215 = !DILocation(line: 498, column: 8, scope: !1206)
!1216 = !DILocation(line: 498, column: 14, scope: !1206)
!1217 = !DILocation(line: 496, column: 10, scope: !1206)
!1218 = !DILocation(line: 496, column: 8, scope: !1206)
!1219 = !DILocation(line: 499, column: 8, scope: !1220)
!1220 = distinct !DILexicalBlock(scope: !1206, file: !1, line: 499, column: 8)
!1221 = !DILocation(line: 499, column: 12, scope: !1220)
!1222 = !DILocation(line: 499, column: 8, scope: !1206)
!1223 = !DILocation(line: 500, column: 5, scope: !1220)
!1224 = !DILocation(line: 501, column: 28, scope: !1206)
!1225 = !DILocation(line: 501, column: 34, scope: !1206)
!1226 = !DILocation(line: 501, column: 4, scope: !1206)
!1227 = !DILocation(line: 501, column: 10, scope: !1206)
!1228 = !DILocation(line: 501, column: 17, scope: !1206)
!1229 = !DILocation(line: 501, column: 26, scope: !1206)
!1230 = !DILocation(line: 502, column: 29, scope: !1206)
!1231 = !DILocation(line: 502, column: 35, scope: !1206)
!1232 = !DILocation(line: 502, column: 4, scope: !1206)
!1233 = !DILocation(line: 502, column: 10, scope: !1206)
!1234 = !DILocation(line: 502, column: 17, scope: !1206)
!1235 = !DILocation(line: 502, column: 27, scope: !1206)
!1236 = !DILocation(line: 503, column: 3, scope: !1206)
!1237 = !DILocation(line: 506, column: 8, scope: !1238)
!1238 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 506, column: 7)
!1239 = !DILocation(line: 506, column: 18, scope: !1238)
!1240 = !DILocation(line: 506, column: 21, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1238, file: !1, discriminator: 1)
!1242 = !DILocation(line: 506, column: 27, scope: !1241)
!1243 = !DILocation(line: 506, column: 34, scope: !1241)
!1244 = !DILocation(line: 506, column: 43, scope: !1241)
!1245 = !DILocation(line: 506, column: 7, scope: !1241)
!1246 = !DILocation(line: 507, column: 4, scope: !1238)
!1247 = !DILocation(line: 509, column: 21, scope: !1198)
!1248 = !DILocation(line: 509, column: 27, scope: !1198)
!1249 = !DILocation(line: 510, column: 7, scope: !1198)
!1250 = !DILocation(line: 509, column: 9, scope: !1198)
!1251 = !DILocation(line: 509, column: 7, scope: !1198)
!1252 = !DILocation(line: 512, column: 11, scope: !1198)
!1253 = !DILocation(line: 512, column: 3, scope: !1198)
!1254 = !DILocation(line: 516, column: 9, scope: !1255)
!1255 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 516, column: 8)
!1256 = distinct !DILexicalBlock(scope: !1198, file: !1, line: 512, column: 16)
!1257 = !DILocation(line: 516, column: 19, scope: !1255)
!1258 = !DILocation(line: 516, column: 22, scope: !1259)
!1259 = !DILexicalBlockFile(scope: !1255, file: !1, discriminator: 1)
!1260 = !DILocation(line: 516, column: 28, scope: !1259)
!1261 = !DILocation(line: 516, column: 35, scope: !1259)
!1262 = !DILocation(line: 516, column: 44, scope: !1259)
!1263 = !DILocation(line: 516, column: 8, scope: !1259)
!1264 = !DILocation(line: 517, column: 5, scope: !1255)
!1265 = !DILocation(line: 520, column: 4, scope: !1256)
!1266 = !DILocation(line: 523, column: 8, scope: !1267)
!1267 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 523, column: 8)
!1268 = !DILocation(line: 523, column: 8, scope: !1256)
!1269 = !DILocation(line: 524, column: 5, scope: !1267)
!1270 = !DILocation(line: 525, column: 22, scope: !1256)
!1271 = !DILocation(line: 525, column: 25, scope: !1256)
!1272 = !DILocation(line: 525, column: 4, scope: !1256)
!1273 = !DILocation(line: 527, column: 4, scope: !1256)
!1274 = !DILocation(line: 529, column: 22, scope: !1256)
!1275 = !DILocation(line: 529, column: 25, scope: !1256)
!1276 = !DILocation(line: 532, column: 37, scope: !1256)
!1277 = !DILocation(line: 532, column: 43, scope: !1256)
!1278 = !DILocation(line: 532, column: 21, scope: !1256)
!1279 = !DILocation(line: 533, column: 9, scope: !1256)
!1280 = !DILocation(line: 533, column: 23, scope: !1256)
!1281 = !DILocation(line: 534, column: 5, scope: !1256)
!1282 = !DILocation(line: 529, column: 4, scope: !1256)
!1283 = !DILocation(line: 535, column: 4, scope: !1256)
!1284 = !DILocation(line: 538, column: 22, scope: !1256)
!1285 = !DILocation(line: 538, column: 25, scope: !1256)
!1286 = !DILocation(line: 541, column: 8, scope: !1256)
!1287 = !DILocation(line: 538, column: 4, scope: !1256)
!1288 = !DILocation(line: 542, column: 4, scope: !1256)
!1289 = !DILocation(line: 493, column: 2, scope: !1290)
!1290 = !DILexicalBlockFile(scope: !1199, file: !1, discriminator: 1)
!1291 = !DILocation(line: 545, column: 1, scope: !344)
!1292 = !DILocalVariable(name: "pp", arg: 1, scope: !351, file: !352, line: 177, type: !166)
!1293 = !DILocation(line: 177, column: 23, scope: !351)
!1294 = !DILocalVariable(name: "u", arg: 2, scope: !351, file: !352, line: 177, type: !240)
!1295 = !DILocation(line: 177, column: 36, scope: !351)
!1296 = !DILocalVariable(name: "p", scope: !351, file: !352, line: 179, type: !234)
!1297 = !DILocation(line: 179, column: 17, scope: !351)
!1298 = !DILocation(line: 179, column: 38, scope: !351)
!1299 = !DILocation(line: 181, column: 9, scope: !351)
!1300 = !DILocation(line: 181, column: 11, scope: !351)
!1301 = !DILocation(line: 181, column: 2, scope: !351)
!1302 = !DILocation(line: 181, column: 7, scope: !351)
!1303 = !DILocation(line: 182, column: 10, scope: !351)
!1304 = !DILocation(line: 182, column: 12, scope: !351)
!1305 = !DILocation(line: 182, column: 18, scope: !351)
!1306 = !DILocation(line: 182, column: 9, scope: !351)
!1307 = !DILocation(line: 182, column: 2, scope: !351)
!1308 = !DILocation(line: 182, column: 7, scope: !351)
!1309 = !DILocation(line: 183, column: 10, scope: !351)
!1310 = !DILocation(line: 183, column: 12, scope: !351)
!1311 = !DILocation(line: 183, column: 19, scope: !351)
!1312 = !DILocation(line: 183, column: 9, scope: !351)
!1313 = !DILocation(line: 183, column: 2, scope: !351)
!1314 = !DILocation(line: 183, column: 7, scope: !351)
!1315 = !DILocation(line: 184, column: 10, scope: !351)
!1316 = !DILocation(line: 184, column: 12, scope: !351)
!1317 = !DILocation(line: 184, column: 19, scope: !351)
!1318 = !DILocation(line: 184, column: 9, scope: !351)
!1319 = !DILocation(line: 184, column: 2, scope: !351)
!1320 = !DILocation(line: 184, column: 7, scope: !351)
!1321 = !DILocation(line: 185, column: 1, scope: !351)
!1322 = !DILocalVariable(name: "pp", arg: 1, scope: !355, file: !352, line: 188, type: !166)
!1323 = !DILocation(line: 188, column: 23, scope: !355)
!1324 = !DILocalVariable(name: "u", arg: 2, scope: !355, file: !352, line: 188, type: !251)
!1325 = !DILocation(line: 188, column: 36, scope: !355)
!1326 = !DILocalVariable(name: "p", scope: !355, file: !352, line: 190, type: !234)
!1327 = !DILocation(line: 190, column: 17, scope: !355)
!1328 = !DILocation(line: 190, column: 38, scope: !355)
!1329 = !DILocation(line: 192, column: 18, scope: !355)
!1330 = !DILocation(line: 192, column: 32, scope: !355)
!1331 = !DILocation(line: 192, column: 34, scope: !355)
!1332 = !DILocation(line: 192, column: 21, scope: !355)
!1333 = !DILocation(line: 192, column: 2, scope: !355)
!1334 = !DILocation(line: 193, column: 18, scope: !355)
!1335 = !DILocation(line: 193, column: 20, scope: !355)
!1336 = !DILocation(line: 193, column: 36, scope: !355)
!1337 = !DILocation(line: 193, column: 38, scope: !355)
!1338 = !DILocation(line: 193, column: 25, scope: !355)
!1339 = !DILocation(line: 193, column: 2, scope: !355)
!1340 = !DILocation(line: 194, column: 1, scope: !355)
