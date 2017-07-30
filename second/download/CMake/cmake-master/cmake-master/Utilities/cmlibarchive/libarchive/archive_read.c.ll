; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }

@.str = private unnamed_addr constant [35 x i8] c"archive_read_extract_set_skip_file\00", align 1
@.str.1 = private unnamed_addr constant [31 x i8] c"archive_read_set_open_callback\00", align 1
@.str.2 = private unnamed_addr constant [31 x i8] c"archive_read_set_read_callback\00", align 1
@.str.3 = private unnamed_addr constant [31 x i8] c"archive_read_set_skip_callback\00", align 1
@.str.4 = private unnamed_addr constant [31 x i8] c"archive_read_set_seek_callback\00", align 1
@.str.5 = private unnamed_addr constant [32 x i8] c"archive_read_set_close_callback\00", align 1
@.str.6 = private unnamed_addr constant [33 x i8] c"archive_read_set_switch_callback\00", align 1
@.str.7 = private unnamed_addr constant [32 x i8] c"archive_read_set_callback_data2\00", align 1
@.str.8 = private unnamed_addr constant [11 x i8] c"No memory.\00", align 1
@.str.9 = private unnamed_addr constant [25 x i8] c"Invalid index specified.\00", align 1
@.str.10 = private unnamed_addr constant [31 x i8] c"archive_read_add_callback_data\00", align 1
@.str.11 = private unnamed_addr constant [18 x i8] c"archive_read_open\00", align 1
@.str.12 = private unnamed_addr constant [49 x i8] c"No reader function provided to archive_read_open\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"none\00", align 1
@.str.14 = private unnamed_addr constant [29 x i8] c"archive_read_header_position\00", align 1
@.str.15 = private unnamed_addr constant [39 x i8] c"Encountered out-of-order sparse blocks\00", align 1
@.str.16 = private unnamed_addr constant [23 x i8] c"archive_read_data_skip\00", align 1
@.str.17 = private unnamed_addr constant [24 x i8] c"archive_seek_data_block\00", align 1
@.str.18 = private unnamed_addr constant [62 x i8] c"Internal error: No format_seek_data_block function registered\00", align 1
@.str.19 = private unnamed_addr constant [31 x i8] c"__archive_read_register_format\00", align 1
@.str.20 = private unnamed_addr constant [41 x i8] c"Not enough slots for format registration\00", align 1
@.str.21 = private unnamed_addr constant [41 x i8] c"Not enough slots for filter registration\00", align 1
@.str.22 = private unnamed_addr constant [31 x i8] c"Unable to allocate copy buffer\00", align 1
@.str.23 = private unnamed_addr constant [60 x i8] c"Truncated input file (needed %jd bytes, only %jd available)\00", align 1
@archive_read_vtable.av = internal global %struct.archive_vtable zeroinitializer, align 8
@archive_read_vtable.inited = internal global i32 0, align 4
@.str.24 = private unnamed_addr constant [24 x i8] c"archive_read_data_block\00", align 1
@.str.25 = private unnamed_addr constant [57 x i8] c"Internal error: No format->read_data function registered\00", align 1
@.str.26 = private unnamed_addr constant [25 x i8] c"archive_read_next_header\00", align 1
@.str.27 = private unnamed_addr constant [23 x i8] c"Premature end-of-file.\00", align 1
@.str.28 = private unnamed_addr constant [18 x i8] c"archive_read_free\00", align 1
@.str.29 = private unnamed_addr constant [19 x i8] c"archive_read_close\00", align 1
@.str.30 = private unnamed_addr constant [25 x i8] c"Negative skip requested.\00", align 1
@.str.31 = private unnamed_addr constant [56 x i8] c"Current client reader does not support seeking a device\00", align 1
@.str.32 = private unnamed_addr constant [45 x i8] c"Input requires too many filters for decoding\00", align 1
@.str.33 = private unnamed_addr constant [22 x i8] c"No formats registered\00", align 1
@.str.34 = private unnamed_addr constant [28 x i8] c"Unrecognized archive format\00", align 1

; Function Attrs: nounwind uwtable
define %struct.archive* @archive_read_new() #0 !dbg !293 {
entry:
  %retval = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !400, metadata !401), !dbg !402
  %call = call noalias i8* @calloc(i64 1, i64 2536) #7, !dbg !403
  %0 = bitcast i8* %call to %struct.archive_read*, !dbg !404
  store %struct.archive_read* %0, %struct.archive_read** %a, align 8, !dbg !405
  %1 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !406
  %cmp = icmp eq %struct.archive_read* %1, null, !dbg !408
  br i1 %cmp, label %if.then, label %if.end, !dbg !409

if.then:                                          ; preds = %entry
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !410
  br label %return, !dbg !410

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !411
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !412
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 0, !dbg !413
  store i32 14594245, i32* %magic, align 8, !dbg !414
  %3 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !415
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 0, !dbg !416
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !417
  store i32 1, i32* %state, align 4, !dbg !418
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !419
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !420
  %call3 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive2), !dbg !421
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !422
  %entry4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 1, !dbg !423
  store %struct.archive_entry* %call3, %struct.archive_entry** %entry4, align 8, !dbg !424
  %call5 = call %struct.archive_vtable* @archive_read_vtable(), !dbg !425
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !426
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !427
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %archive6, i32 0, i32 2, !dbg !428
  store %struct.archive_vtable* %call5, %struct.archive_vtable** %vtable, align 8, !dbg !429
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !430
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 16, !dbg !431
  %first = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 0, !dbg !432
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !433
  %passphrases7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 16, !dbg !434
  %last = getelementptr inbounds %struct.anon, %struct.anon* %passphrases7, i32 0, i32 1, !dbg !435
  store %struct.archive_read_passphrase** %first, %struct.archive_read_passphrase*** %last, align 8, !dbg !436
  %9 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !437
  %archive8 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !438
  store %struct.archive* %archive8, %struct.archive** %retval, align 8, !dbg !439
  br label %return, !dbg !439

return:                                           ; preds = %if.end, %if.then
  %10 = load %struct.archive*, %struct.archive** %retval, align 8, !dbg !440
  ret %struct.archive* %10, !dbg !440
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare %struct.archive_entry* @archive_entry_new2(%struct.archive*) #3

; Function Attrs: nounwind uwtable
define internal %struct.archive_vtable* @archive_read_vtable() #0 !dbg !369 {
entry:
  %0 = load i32, i32* @archive_read_vtable.inited, align 4, !dbg !441
  %tobool = icmp ne i32 %0, 0, !dbg !441
  br i1 %tobool, label %if.end, label %if.then, !dbg !443

if.then:                                          ; preds = %entry
  store i64 (%struct.archive*, i32)* @_archive_filter_bytes, i64 (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 10), align 8, !dbg !444
  store i32 (%struct.archive*, i32)* @_archive_filter_code, i32 (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 11), align 8, !dbg !446
  store i8* (%struct.archive*, i32)* @_archive_filter_name, i8* (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 12), align 8, !dbg !447
  store i32 (%struct.archive*)* @_archive_filter_count, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 9), align 8, !dbg !448
  store i32 (%struct.archive*, i8**, i64*, i64*)* @_archive_read_data_block, i32 (%struct.archive*, i8**, i64*, i64*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 8), align 8, !dbg !449
  store i32 (%struct.archive*, %struct.archive_entry**)* @_archive_read_next_header, i32 (%struct.archive*, %struct.archive_entry**)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 6), align 8, !dbg !450
  store i32 (%struct.archive*, %struct.archive_entry*)* @_archive_read_next_header2, i32 (%struct.archive*, %struct.archive_entry*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 7), align 8, !dbg !451
  store i32 (%struct.archive*)* @_archive_read_free, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 1), align 8, !dbg !452
  store i32 (%struct.archive*)* @_archive_read_close, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_vtable.av, i32 0, i32 0), align 8, !dbg !453
  store i32 1, i32* @archive_read_vtable.inited, align 4, !dbg !454
  br label %if.end, !dbg !455

if.end:                                           ; preds = %if.then, %entry
  ret %struct.archive_vtable* @archive_read_vtable.av, !dbg !456
}

; Function Attrs: nounwind uwtable
define void @archive_read_extract_set_skip_file(%struct.archive* %_a, i64 %d, i64 %i) #0 !dbg !296 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %d.addr = alloca i64, align 8
  %i.addr = alloca i64, align 8
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !457, metadata !401), !dbg !458
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !459, metadata !401), !dbg !460
  store i64 %i, i64* %i.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %i.addr, metadata !461, metadata !401), !dbg !462
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !463, metadata !401), !dbg !464
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !465
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !466
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !464
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !467
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 32767, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str, i32 0, i32 0)), !dbg !469
  %cmp = icmp ne i32 0, %call, !dbg !470
  br i1 %cmp, label %if.then, label %if.end, !dbg !471

if.then:                                          ; preds = %entry
  br label %return, !dbg !472

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !473
  %skip_file_set = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 2, !dbg !474
  store i32 1, i32* %skip_file_set, align 8, !dbg !475
  %4 = load i64, i64* %d.addr, align 8, !dbg !476
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !477
  %skip_file_dev = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 3, !dbg !478
  store i64 %4, i64* %skip_file_dev, align 8, !dbg !479
  %6 = load i64, i64* %i.addr, align 8, !dbg !480
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !481
  %skip_file_ino = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 4, !dbg !482
  store i64 %6, i64* %skip_file_ino, align 8, !dbg !483
  br label %return, !dbg !484

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !485
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #3

; Function Attrs: nounwind uwtable
define i32 @archive_read_open(%struct.archive* %a, i8* %client_data, i32 (%struct.archive*, i8*)* %client_opener, i64 (%struct.archive*, i8*, i8**)* %client_reader, i32 (%struct.archive*, i8*)* %client_closer) #0 !dbg !299 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %client_opener.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %client_reader.addr = alloca i64 (%struct.archive*, i8*, i8**)*, align 8
  %client_closer.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !487, metadata !401), !dbg !488
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !489, metadata !401), !dbg !490
  store i32 (%struct.archive*, i8*)* %client_opener, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_opener.addr, metadata !491, metadata !401), !dbg !492
  store i64 (%struct.archive*, i8*, i8**)* %client_reader, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, metadata !493, metadata !401), !dbg !494
  store i32 (%struct.archive*, i8*)* %client_closer, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_closer.addr, metadata !495, metadata !401), !dbg !496
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !497
  %1 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8, !dbg !498
  %call = call i32 @archive_read_set_open_callback(%struct.archive* %0, i32 (%struct.archive*, i8*)* %1), !dbg !499
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !500
  %3 = load i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8, !dbg !501
  %call1 = call i32 @archive_read_set_read_callback(%struct.archive* %2, i64 (%struct.archive*, i8*, i8**)* %3), !dbg !502
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !503
  %5 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8, !dbg !504
  %call2 = call i32 @archive_read_set_close_callback(%struct.archive* %4, i32 (%struct.archive*, i8*)* %5), !dbg !505
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !506
  %7 = load i8*, i8** %client_data.addr, align 8, !dbg !507
  %call3 = call i32 @archive_read_set_callback_data(%struct.archive* %6, i8* %7), !dbg !508
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !509
  %call4 = call i32 @archive_read_open1(%struct.archive* %8), !dbg !510
  ret i32 %call4, !dbg !511
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_open_callback(%struct.archive* %_a, i32 (%struct.archive*, i8*)* %client_opener) #0 !dbg !305 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_opener.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !512, metadata !401), !dbg !513
  store i32 (%struct.archive*, i8*)* %client_opener, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_opener.addr, metadata !514, metadata !401), !dbg !515
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !516, metadata !401), !dbg !517
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !518
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !519
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !517
  br label %do.body, !dbg !520

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !521, metadata !401), !dbg !523
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !524
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.1, i32 0, i32 0)), !dbg !524
  store i32 %call, i32* %magic_test, align 4, !dbg !524
  %3 = load i32, i32* %magic_test, align 4, !dbg !524
  %cmp = icmp eq i32 %3, -30, !dbg !524
  br i1 %cmp, label %if.then, label %if.end, !dbg !524

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !526
  br label %return, !dbg !526

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !529

do.end:                                           ; preds = %if.end
  %4 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8, !dbg !531
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !532
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !533
  %opener = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 0, !dbg !534
  store i32 (%struct.archive*, i8*)* %4, i32 (%struct.archive*, i8*)** %opener, align 8, !dbg !535
  store i32 0, i32* %retval, align 4, !dbg !536
  br label %return, !dbg !536

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !537
  ret i32 %6, !dbg !537
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_read_callback(%struct.archive* %_a, i64 (%struct.archive*, i8*, i8**)* %client_reader) #0 !dbg !308 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_reader.addr = alloca i64 (%struct.archive*, i8*, i8**)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !538, metadata !401), !dbg !539
  store i64 (%struct.archive*, i8*, i8**)* %client_reader, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, metadata !540, metadata !401), !dbg !541
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !542, metadata !401), !dbg !543
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !544
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !545
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !543
  br label %do.body, !dbg !546

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !547, metadata !401), !dbg !549
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !550
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.2, i32 0, i32 0)), !dbg !550
  store i32 %call, i32* %magic_test, align 4, !dbg !550
  %3 = load i32, i32* %magic_test, align 4, !dbg !550
  %cmp = icmp eq i32 %3, -30, !dbg !550
  br i1 %cmp, label %if.then, label %if.end, !dbg !550

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !552
  br label %return, !dbg !552

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !555

do.end:                                           ; preds = %if.end
  %4 = load i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8, !dbg !557
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !558
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !559
  %reader = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 1, !dbg !560
  store i64 (%struct.archive*, i8*, i8**)* %4, i64 (%struct.archive*, i8*, i8**)** %reader, align 8, !dbg !561
  store i32 0, i32* %retval, align 4, !dbg !562
  br label %return, !dbg !562

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !563
  ret i32 %6, !dbg !563
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_close_callback(%struct.archive* %_a, i32 (%struct.archive*, i8*)* %client_closer) #0 !dbg !317 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_closer.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !564, metadata !401), !dbg !565
  store i32 (%struct.archive*, i8*)* %client_closer, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_closer.addr, metadata !566, metadata !401), !dbg !567
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !568, metadata !401), !dbg !569
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !570
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !571
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !569
  br label %do.body, !dbg !572

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !573, metadata !401), !dbg !575
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !576
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.5, i32 0, i32 0)), !dbg !576
  store i32 %call, i32* %magic_test, align 4, !dbg !576
  %3 = load i32, i32* %magic_test, align 4, !dbg !576
  %cmp = icmp eq i32 %3, -30, !dbg !576
  br i1 %cmp, label %if.then, label %if.end, !dbg !576

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !578
  br label %return, !dbg !578

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !581

do.end:                                           ; preds = %if.end
  %4 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8, !dbg !583
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !584
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !585
  %closer = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 4, !dbg !586
  store i32 (%struct.archive*, i8*)* %4, i32 (%struct.archive*, i8*)** %closer, align 8, !dbg !587
  store i32 0, i32* %retval, align 4, !dbg !588
  br label %return, !dbg !588

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !589
  ret i32 %6, !dbg !589
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_callback_data(%struct.archive* %_a, i8* %client_data) #0 !dbg !323 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !590, metadata !401), !dbg !591
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !592, metadata !401), !dbg !593
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !594
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !595
  %call = call i32 @archive_read_set_callback_data2(%struct.archive* %0, i8* %1, i32 0), !dbg !596
  ret i32 %call, !dbg !597
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_open1(%struct.archive* %_a) #0 !dbg !330 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %filter = alloca %struct.archive_read_filter*, align 8
  %tmp = alloca %struct.archive_read_filter*, align 8
  %slot = alloca i32, align 4
  %e = alloca i32, align 4
  %i = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !598, metadata !401), !dbg !599
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !600, metadata !401), !dbg !601
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !602
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !603
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !601
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter, metadata !604, metadata !401), !dbg !605
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %tmp, metadata !606, metadata !401), !dbg !607
  call void @llvm.dbg.declare(metadata i32* %slot, metadata !608, metadata !401), !dbg !609
  call void @llvm.dbg.declare(metadata i32* %e, metadata !610, metadata !401), !dbg !611
  store i32 0, i32* %e, align 4, !dbg !611
  call void @llvm.dbg.declare(metadata i32* %i, metadata !612, metadata !401), !dbg !613
  br label %do.body, !dbg !614

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !615, metadata !401), !dbg !617
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !618
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.11, i32 0, i32 0)), !dbg !618
  store i32 %call, i32* %magic_test, align 4, !dbg !618
  %3 = load i32, i32* %magic_test, align 4, !dbg !618
  %cmp = icmp eq i32 %3, -30, !dbg !618
  br i1 %cmp, label %if.then, label %if.end, !dbg !618

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !620
  br label %return, !dbg !620

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !623

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !625
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !626
  call void @archive_clear_error(%struct.archive* %archive), !dbg !627
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !628
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !630
  %reader = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 1, !dbg !631
  %6 = load i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i8**)** %reader, align 8, !dbg !631
  %cmp5 = icmp eq i64 (%struct.archive*, i8*, i8**)* %6, null, !dbg !632
  br i1 %cmp5, label %if.then6, label %if.end9, !dbg !633

if.then6:                                         ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !634
  %archive7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !636
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive7, i32 22, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.12, i32 0, i32 0)), !dbg !637
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !638
  %archive8 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !639
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive8, i32 0, i32 1, !dbg !640
  store i32 32768, i32* %state, align 4, !dbg !641
  store i32 -30, i32* %retval, align 4, !dbg !642
  br label %return, !dbg !642

if.end9:                                          ; preds = %do.end
  %9 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !643
  %client10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 5, !dbg !645
  %opener = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client10, i32 0, i32 0, !dbg !646
  %10 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener, align 8, !dbg !646
  %cmp11 = icmp ne i32 (%struct.archive*, i8*)* %10, null, !dbg !647
  br i1 %cmp11, label %if.then12, label %if.end34, !dbg !648

if.then12:                                        ; preds = %if.end9
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !649
  %client13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 5, !dbg !651
  %opener14 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client13, i32 0, i32 0, !dbg !652
  %12 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener14, align 8, !dbg !652
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !653
  %archive15 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !654
  %14 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !655
  %client16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 5, !dbg !656
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client16, i32 0, i32 9, !dbg !657
  %15 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !657
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %15, i64 0, !dbg !655
  %data = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 2, !dbg !658
  %16 = load i8*, i8** %data, align 8, !dbg !658
  %call17 = call i32 %12(%struct.archive* %archive15, i8* %16), !dbg !659
  store i32 %call17, i32* %e, align 4, !dbg !660
  %17 = load i32, i32* %e, align 4, !dbg !661
  %cmp18 = icmp ne i32 %17, 0, !dbg !663
  br i1 %cmp18, label %if.then19, label %if.end33, !dbg !664

if.then19:                                        ; preds = %if.then12
  %18 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !665
  %client20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 5, !dbg !668
  %closer = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client20, i32 0, i32 4, !dbg !669
  %19 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer, align 8, !dbg !669
  %tobool = icmp ne i32 (%struct.archive*, i8*)* %19, null, !dbg !665
  br i1 %tobool, label %if.then21, label %if.end32, !dbg !670

if.then21:                                        ; preds = %if.then19
  store i32 0, i32* %i, align 4, !dbg !671
  br label %for.cond, !dbg !674

for.cond:                                         ; preds = %for.inc, %if.then21
  %20 = load i32, i32* %i, align 4, !dbg !675
  %21 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !678
  %client22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 5, !dbg !679
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client22, i32 0, i32 6, !dbg !680
  %22 = load i32, i32* %nodes, align 8, !dbg !680
  %cmp23 = icmp ult i32 %20, %22, !dbg !681
  br i1 %cmp23, label %for.body, label %for.end, !dbg !682

for.body:                                         ; preds = %for.cond
  %23 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !683
  %client24 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 5, !dbg !684
  %closer25 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client24, i32 0, i32 4, !dbg !685
  %24 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer25, align 8, !dbg !685
  %25 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !686
  %archive26 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 0, !dbg !687
  %26 = load i32, i32* %i, align 4, !dbg !688
  %idxprom = zext i32 %26 to i64, !dbg !689
  %27 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !689
  %client27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 5, !dbg !690
  %dataset28 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client27, i32 0, i32 9, !dbg !691
  %28 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset28, align 8, !dbg !691
  %arrayidx29 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %28, i64 %idxprom, !dbg !689
  %data30 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx29, i32 0, i32 2, !dbg !692
  %29 = load i8*, i8** %data30, align 8, !dbg !692
  %call31 = call i32 %24(%struct.archive* %archive26, i8* %29), !dbg !693
  br label %for.inc, !dbg !693

for.inc:                                          ; preds = %for.body
  %30 = load i32, i32* %i, align 4, !dbg !694
  %inc = add i32 %30, 1, !dbg !694
  store i32 %inc, i32* %i, align 4, !dbg !694
  br label %for.cond, !dbg !696

for.end:                                          ; preds = %for.cond
  br label %if.end32, !dbg !697

if.end32:                                         ; preds = %for.end, %if.then19
  %31 = load i32, i32* %e, align 4, !dbg !698
  store i32 %31, i32* %retval, align 4, !dbg !699
  br label %return, !dbg !699

if.end33:                                         ; preds = %if.then12
  br label %if.end34, !dbg !700

if.end34:                                         ; preds = %if.end33, %if.end9
  %call35 = call noalias i8* @calloc(i64 1, i64 176) #7, !dbg !701
  %32 = bitcast i8* %call35 to %struct.archive_read_filter*, !dbg !701
  store %struct.archive_read_filter* %32, %struct.archive_read_filter** %filter, align 8, !dbg !702
  %33 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !703
  %cmp36 = icmp eq %struct.archive_read_filter* %33, null, !dbg !705
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !706

if.then37:                                        ; preds = %if.end34
  store i32 -30, i32* %retval, align 4, !dbg !707
  br label %return, !dbg !707

if.end38:                                         ; preds = %if.end34
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !708
  %bidder = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %34, i32 0, i32 1, !dbg !709
  store %struct.archive_read_filter_bidder* null, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !710
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !711
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %35, i32 0, i32 2, !dbg !712
  store %struct.archive_read_filter* null, %struct.archive_read_filter** %upstream, align 8, !dbg !713
  %36 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !714
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !715
  %archive39 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %37, i32 0, i32 3, !dbg !716
  store %struct.archive_read* %36, %struct.archive_read** %archive39, align 8, !dbg !717
  %38 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !718
  %client40 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %38, i32 0, i32 5, !dbg !719
  %dataset41 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client40, i32 0, i32 9, !dbg !720
  %39 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset41, align 8, !dbg !720
  %arrayidx42 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %39, i64 0, !dbg !718
  %data43 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx42, i32 0, i32 2, !dbg !721
  %40 = load i8*, i8** %data43, align 8, !dbg !721
  %41 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !722
  %data44 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %41, i32 0, i32 10, !dbg !723
  store i8* %40, i8** %data44, align 8, !dbg !724
  %42 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !725
  %open = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %42, i32 0, i32 4, !dbg !726
  store i32 (%struct.archive_read_filter*)* @client_open_proxy, i32 (%struct.archive_read_filter*)** %open, align 8, !dbg !727
  %43 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !728
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %43, i32 0, i32 5, !dbg !729
  store i64 (%struct.archive_read_filter*, i8**)* @client_read_proxy, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !730
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !731
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %44, i32 0, i32 6, !dbg !732
  store i64 (%struct.archive_read_filter*, i64)* @client_skip_proxy, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !733
  %45 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !734
  %seek = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %45, i32 0, i32 7, !dbg !735
  store i64 (%struct.archive_read_filter*, i64, i32)* @client_seek_proxy, i64 (%struct.archive_read_filter*, i64, i32)** %seek, align 8, !dbg !736
  %46 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !737
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %46, i32 0, i32 8, !dbg !738
  store i32 (%struct.archive_read_filter*)* @client_close_proxy, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !739
  %47 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !740
  %sswitch = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %47, i32 0, i32 9, !dbg !741
  store i32 (%struct.archive_read_filter*, i32)* @client_switch_proxy, i32 (%struct.archive_read_filter*, i32)** %sswitch, align 8, !dbg !742
  %48 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !743
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %48, i32 0, i32 11, !dbg !744
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i8** %name, align 8, !dbg !745
  %49 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !746
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %49, i32 0, i32 12, !dbg !747
  store i32 0, i32* %code, align 8, !dbg !748
  %50 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !749
  %client45 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %50, i32 0, i32 5, !dbg !750
  %dataset46 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client45, i32 0, i32 9, !dbg !751
  %51 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset46, align 8, !dbg !751
  %arrayidx47 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %51, i64 0, !dbg !749
  %begin_position = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx47, i32 0, i32 0, !dbg !752
  store i64 0, i64* %begin_position, align 8, !dbg !753
  %52 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !754
  %filter48 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %52, i32 0, i32 7, !dbg !756
  %53 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter48, align 8, !dbg !756
  %tobool49 = icmp ne %struct.archive_read_filter* %53, null, !dbg !754
  br i1 %tobool49, label %lor.lhs.false, label %if.then51, !dbg !757

lor.lhs.false:                                    ; preds = %if.end38
  %54 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !758
  %bypass_filter_bidding = getelementptr inbounds %struct.archive_read, %struct.archive_read* %54, i32 0, i32 8, !dbg !760
  %55 = load i32, i32* %bypass_filter_bidding, align 8, !dbg !760
  %tobool50 = icmp ne i32 %55, 0, !dbg !758
  br i1 %tobool50, label %if.else, label %if.then51, !dbg !761

if.then51:                                        ; preds = %lor.lhs.false, %if.end38
  %56 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !762
  %57 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !764
  %filter52 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %57, i32 0, i32 7, !dbg !765
  store %struct.archive_read_filter* %56, %struct.archive_read_filter** %filter52, align 8, !dbg !766
  %58 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !767
  %call53 = call i32 @choose_filters(%struct.archive_read* %58), !dbg !768
  store i32 %call53, i32* %e, align 4, !dbg !769
  %59 = load i32, i32* %e, align 4, !dbg !770
  %cmp54 = icmp slt i32 %59, -20, !dbg !772
  br i1 %cmp54, label %if.then55, label %if.end58, !dbg !773

if.then55:                                        ; preds = %if.then51
  %60 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !774
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %60, i32 0, i32 0, !dbg !776
  %state57 = getelementptr inbounds %struct.archive, %struct.archive* %archive56, i32 0, i32 1, !dbg !777
  store i32 32768, i32* %state57, align 4, !dbg !778
  store i32 -30, i32* %retval, align 4, !dbg !779
  br label %return, !dbg !779

if.end58:                                         ; preds = %if.then51
  br label %if.end64, !dbg !780

if.else:                                          ; preds = %lor.lhs.false
  %61 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !781
  %filter59 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %61, i32 0, i32 7, !dbg !783
  %62 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter59, align 8, !dbg !783
  store %struct.archive_read_filter* %62, %struct.archive_read_filter** %tmp, align 8, !dbg !784
  br label %while.cond, !dbg !785

while.cond:                                       ; preds = %while.body, %if.else
  %63 = load %struct.archive_read_filter*, %struct.archive_read_filter** %tmp, align 8, !dbg !786
  %upstream60 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %63, i32 0, i32 2, !dbg !788
  %64 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream60, align 8, !dbg !788
  %tobool61 = icmp ne %struct.archive_read_filter* %64, null, !dbg !789
  br i1 %tobool61, label %while.body, label %while.end, !dbg !789

while.body:                                       ; preds = %while.cond
  %65 = load %struct.archive_read_filter*, %struct.archive_read_filter** %tmp, align 8, !dbg !790
  %upstream62 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %65, i32 0, i32 2, !dbg !791
  %66 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream62, align 8, !dbg !791
  store %struct.archive_read_filter* %66, %struct.archive_read_filter** %tmp, align 8, !dbg !792
  br label %while.cond, !dbg !793

while.end:                                        ; preds = %while.cond
  %67 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !795
  %68 = load %struct.archive_read_filter*, %struct.archive_read_filter** %tmp, align 8, !dbg !796
  %upstream63 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %68, i32 0, i32 2, !dbg !797
  store %struct.archive_read_filter* %67, %struct.archive_read_filter** %upstream63, align 8, !dbg !798
  br label %if.end64

if.end64:                                         ; preds = %while.end, %if.end58
  %69 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !799
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %69, i32 0, i32 13, !dbg !801
  %70 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !801
  %tobool65 = icmp ne %struct.archive_format_descriptor* %70, null, !dbg !799
  br i1 %tobool65, label %if.end77, label %if.then66, !dbg !802

if.then66:                                        ; preds = %if.end64
  %71 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !803
  %call67 = call i32 @choose_format(%struct.archive_read* %71), !dbg !805
  store i32 %call67, i32* %slot, align 4, !dbg !806
  %72 = load i32, i32* %slot, align 4, !dbg !807
  %cmp68 = icmp slt i32 %72, 0, !dbg !809
  br i1 %cmp68, label %if.then69, label %if.end73, !dbg !810

if.then69:                                        ; preds = %if.then66
  %73 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !811
  %call70 = call i32 @close_filters(%struct.archive_read* %73), !dbg !813
  %74 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !814
  %archive71 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %74, i32 0, i32 0, !dbg !815
  %state72 = getelementptr inbounds %struct.archive, %struct.archive* %archive71, i32 0, i32 1, !dbg !816
  store i32 32768, i32* %state72, align 4, !dbg !817
  store i32 -30, i32* %retval, align 4, !dbg !818
  br label %return, !dbg !818

if.end73:                                         ; preds = %if.then66
  %75 = load i32, i32* %slot, align 4, !dbg !819
  %idxprom74 = sext i32 %75 to i64, !dbg !820
  %76 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !820
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %76, i32 0, i32 12, !dbg !821
  %arrayidx75 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 %idxprom74, !dbg !820
  %77 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !822
  %format76 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %77, i32 0, i32 13, !dbg !823
  store %struct.archive_format_descriptor* %arrayidx75, %struct.archive_format_descriptor** %format76, align 8, !dbg !824
  br label %if.end77, !dbg !825

if.end77:                                         ; preds = %if.end73, %if.end64
  %78 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !826
  %archive78 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %78, i32 0, i32 0, !dbg !827
  %state79 = getelementptr inbounds %struct.archive, %struct.archive* %archive78, i32 0, i32 1, !dbg !828
  store i32 2, i32* %state79, align 4, !dbg !829
  %79 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !830
  %filter80 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %79, i32 0, i32 7, !dbg !831
  %80 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter80, align 8, !dbg !831
  %call81 = call i32 @client_switch_proxy(%struct.archive_read_filter* %80, i32 0), !dbg !832
  %81 = load i32, i32* %e, align 4, !dbg !833
  store i32 %81, i32* %retval, align 4, !dbg !834
  br label %return, !dbg !834

return:                                           ; preds = %if.end77, %if.then69, %if.then55, %if.then37, %if.end32, %if.then6, %if.then
  %82 = load i32, i32* %retval, align 4, !dbg !835
  ret i32 %82, !dbg !835
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_open2(%struct.archive* %a, i8* %client_data, i32 (%struct.archive*, i8*)* %client_opener, i64 (%struct.archive*, i8*, i8**)* %client_reader, i64 (%struct.archive*, i8*, i64)* %client_skipper, i32 (%struct.archive*, i8*)* %client_closer) #0 !dbg !302 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %client_opener.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  %client_reader.addr = alloca i64 (%struct.archive*, i8*, i8**)*, align 8
  %client_skipper.addr = alloca i64 (%struct.archive*, i8*, i64)*, align 8
  %client_closer.addr = alloca i32 (%struct.archive*, i8*)*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !836, metadata !401), !dbg !837
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !838, metadata !401), !dbg !839
  store i32 (%struct.archive*, i8*)* %client_opener, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_opener.addr, metadata !840, metadata !401), !dbg !841
  store i64 (%struct.archive*, i8*, i8**)* %client_reader, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, metadata !842, metadata !401), !dbg !843
  store i64 (%struct.archive*, i8*, i64)* %client_skipper, i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, metadata !844, metadata !401), !dbg !845
  store i32 (%struct.archive*, i8*)* %client_closer, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*)** %client_closer.addr, metadata !846, metadata !401), !dbg !847
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !848
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !849
  %call = call i32 @archive_read_set_callback_data(%struct.archive* %0, i8* %1), !dbg !850
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !851
  %3 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_opener.addr, align 8, !dbg !852
  %call1 = call i32 @archive_read_set_open_callback(%struct.archive* %2, i32 (%struct.archive*, i8*)* %3), !dbg !853
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !854
  %5 = load i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i8**)** %client_reader.addr, align 8, !dbg !855
  %call2 = call i32 @archive_read_set_read_callback(%struct.archive* %4, i64 (%struct.archive*, i8*, i8**)* %5), !dbg !856
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !857
  %7 = load i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, align 8, !dbg !858
  %call3 = call i32 @archive_read_set_skip_callback(%struct.archive* %6, i64 (%struct.archive*, i8*, i64)* %7), !dbg !859
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !860
  %9 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %client_closer.addr, align 8, !dbg !861
  %call4 = call i32 @archive_read_set_close_callback(%struct.archive* %8, i32 (%struct.archive*, i8*)* %9), !dbg !862
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !863
  %call5 = call i32 @archive_read_open1(%struct.archive* %10), !dbg !864
  ret i32 %call5, !dbg !865
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_skip_callback(%struct.archive* %_a, i64 (%struct.archive*, i8*, i64)* %client_skipper) #0 !dbg !311 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_skipper.addr = alloca i64 (%struct.archive*, i8*, i64)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !866, metadata !401), !dbg !867
  store i64 (%struct.archive*, i8*, i64)* %client_skipper, i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, metadata !868, metadata !401), !dbg !869
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !870, metadata !401), !dbg !871
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !872
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !873
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !871
  br label %do.body, !dbg !874

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !875, metadata !401), !dbg !877
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !878
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.3, i32 0, i32 0)), !dbg !878
  store i32 %call, i32* %magic_test, align 4, !dbg !878
  %3 = load i32, i32* %magic_test, align 4, !dbg !878
  %cmp = icmp eq i32 %3, -30, !dbg !878
  br i1 %cmp, label %if.then, label %if.end, !dbg !878

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !880
  br label %return, !dbg !880

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !883

do.end:                                           ; preds = %if.end
  %4 = load i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64)** %client_skipper.addr, align 8, !dbg !885
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !886
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !887
  %skipper = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 2, !dbg !888
  store i64 (%struct.archive*, i8*, i64)* %4, i64 (%struct.archive*, i8*, i64)** %skipper, align 8, !dbg !889
  store i32 0, i32* %retval, align 4, !dbg !890
  br label %return, !dbg !890

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !891
  ret i32 %6, !dbg !891
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_seek_callback(%struct.archive* %_a, i64 (%struct.archive*, i8*, i64, i32)* %client_seeker) #0 !dbg !314 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_seeker.addr = alloca i64 (%struct.archive*, i8*, i64, i32)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !892, metadata !401), !dbg !893
  store i64 (%struct.archive*, i8*, i64, i32)* %client_seeker, i64 (%struct.archive*, i8*, i64, i32)** %client_seeker.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive*, i8*, i64, i32)** %client_seeker.addr, metadata !894, metadata !401), !dbg !895
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !896, metadata !401), !dbg !897
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !898
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !899
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !897
  br label %do.body, !dbg !900

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !901, metadata !401), !dbg !903
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !904
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.4, i32 0, i32 0)), !dbg !904
  store i32 %call, i32* %magic_test, align 4, !dbg !904
  %3 = load i32, i32* %magic_test, align 4, !dbg !904
  %cmp = icmp eq i32 %3, -30, !dbg !904
  br i1 %cmp, label %if.then, label %if.end, !dbg !904

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !906
  br label %return, !dbg !906

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !909

do.end:                                           ; preds = %if.end
  %4 = load i64 (%struct.archive*, i8*, i64, i32)*, i64 (%struct.archive*, i8*, i64, i32)** %client_seeker.addr, align 8, !dbg !911
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !912
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !913
  %seeker = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 3, !dbg !914
  store i64 (%struct.archive*, i8*, i64, i32)* %4, i64 (%struct.archive*, i8*, i64, i32)** %seeker, align 8, !dbg !915
  store i32 0, i32* %retval, align 4, !dbg !916
  br label %return, !dbg !916

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !917
  ret i32 %6, !dbg !917
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_switch_callback(%struct.archive* %_a, i32 (%struct.archive*, i8*, i8*)* %client_switcher) #0 !dbg !320 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_switcher.addr = alloca i32 (%struct.archive*, i8*, i8*)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !918, metadata !401), !dbg !919
  store i32 (%struct.archive*, i8*, i8*)* %client_switcher, i32 (%struct.archive*, i8*, i8*)** %client_switcher.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*, i8*)** %client_switcher.addr, metadata !920, metadata !401), !dbg !921
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !922, metadata !401), !dbg !923
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !924
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !925
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !923
  br label %do.body, !dbg !926

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !927, metadata !401), !dbg !929
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !930
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.6, i32 0, i32 0)), !dbg !930
  store i32 %call, i32* %magic_test, align 4, !dbg !930
  %3 = load i32, i32* %magic_test, align 4, !dbg !930
  %cmp = icmp eq i32 %3, -30, !dbg !930
  br i1 %cmp, label %if.then, label %if.end, !dbg !930

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !932
  br label %return, !dbg !932

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !935

do.end:                                           ; preds = %if.end
  %4 = load i32 (%struct.archive*, i8*, i8*)*, i32 (%struct.archive*, i8*, i8*)** %client_switcher.addr, align 8, !dbg !937
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !938
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !939
  %switcher = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 5, !dbg !940
  store i32 (%struct.archive*, i8*, i8*)* %4, i32 (%struct.archive*, i8*, i8*)** %switcher, align 8, !dbg !941
  store i32 0, i32* %retval, align 4, !dbg !942
  br label %return, !dbg !942

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !943
  ret i32 %6, !dbg !943
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_callback_data2(%struct.archive* %_a, i8* %client_data, i32 %iindex) #0 !dbg !324 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %iindex.addr = alloca i32, align 4
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !944, metadata !401), !dbg !945
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !946, metadata !401), !dbg !947
  store i32 %iindex, i32* %iindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %iindex.addr, metadata !948, metadata !401), !dbg !949
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !950, metadata !401), !dbg !951
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !952
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !953
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !951
  br label %do.body, !dbg !954

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !955, metadata !401), !dbg !957
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !958
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.7, i32 0, i32 0)), !dbg !958
  store i32 %call, i32* %magic_test, align 4, !dbg !958
  %3 = load i32, i32* %magic_test, align 4, !dbg !958
  %cmp = icmp eq i32 %3, -30, !dbg !958
  br i1 %cmp, label %if.then, label %if.end, !dbg !958

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !960
  br label %return, !dbg !960

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !963

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !965
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 5, !dbg !967
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 6, !dbg !968
  %5 = load i32, i32* %nodes, align 8, !dbg !968
  %cmp1 = icmp eq i32 %5, 0, !dbg !969
  br i1 %cmp1, label %if.then2, label %if.end12, !dbg !970

if.then2:                                         ; preds = %do.end
  %call3 = call noalias i8* @calloc(i64 1, i64 24) #7, !dbg !971
  %6 = bitcast i8* %call3 to %struct.archive_read_data_node*, !dbg !973
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !974
  %client4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 5, !dbg !975
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client4, i32 0, i32 9, !dbg !976
  store %struct.archive_read_data_node* %6, %struct.archive_read_data_node** %dataset, align 8, !dbg !977
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !978
  %client5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 5, !dbg !980
  %dataset6 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client5, i32 0, i32 9, !dbg !981
  %9 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset6, align 8, !dbg !981
  %cmp7 = icmp eq %struct.archive_read_data_node* %9, null, !dbg !982
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !983

if.then8:                                         ; preds = %if.then2
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !984
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !986
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.8, i32 0, i32 0)), !dbg !987
  store i32 -30, i32* %retval, align 4, !dbg !988
  br label %return, !dbg !988

if.end9:                                          ; preds = %if.then2
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !989
  %client10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 5, !dbg !990
  %nodes11 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client10, i32 0, i32 6, !dbg !991
  store i32 1, i32* %nodes11, align 8, !dbg !992
  br label %if.end12, !dbg !993

if.end12:                                         ; preds = %if.end9, %do.end
  %12 = load i32, i32* %iindex.addr, align 4, !dbg !994
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !996
  %client13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 5, !dbg !997
  %nodes14 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client13, i32 0, i32 6, !dbg !998
  %14 = load i32, i32* %nodes14, align 8, !dbg !998
  %sub = sub i32 %14, 1, !dbg !999
  %cmp15 = icmp ugt i32 %12, %sub, !dbg !1000
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !1001

if.then16:                                        ; preds = %if.end12
  %15 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1002
  %archive17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 0, !dbg !1004
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 22, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0)), !dbg !1005
  store i32 -30, i32* %retval, align 4, !dbg !1006
  br label %return, !dbg !1006

if.end18:                                         ; preds = %if.end12
  %16 = load i8*, i8** %client_data.addr, align 8, !dbg !1007
  %17 = load i32, i32* %iindex.addr, align 4, !dbg !1008
  %idxprom = zext i32 %17 to i64, !dbg !1009
  %18 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1009
  %client19 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 5, !dbg !1010
  %dataset20 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client19, i32 0, i32 9, !dbg !1011
  %19 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset20, align 8, !dbg !1011
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %19, i64 %idxprom, !dbg !1009
  %data = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 2, !dbg !1012
  store i8* %16, i8** %data, align 8, !dbg !1013
  %20 = load i32, i32* %iindex.addr, align 4, !dbg !1014
  %idxprom21 = zext i32 %20 to i64, !dbg !1015
  %21 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1015
  %client22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 5, !dbg !1016
  %dataset23 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client22, i32 0, i32 9, !dbg !1017
  %22 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset23, align 8, !dbg !1017
  %arrayidx24 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %22, i64 %idxprom21, !dbg !1015
  %begin_position = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx24, i32 0, i32 0, !dbg !1018
  store i64 -1, i64* %begin_position, align 8, !dbg !1019
  %23 = load i32, i32* %iindex.addr, align 4, !dbg !1020
  %idxprom25 = zext i32 %23 to i64, !dbg !1021
  %24 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1021
  %client26 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 5, !dbg !1022
  %dataset27 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client26, i32 0, i32 9, !dbg !1023
  %25 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset27, align 8, !dbg !1023
  %arrayidx28 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %25, i64 %idxprom25, !dbg !1021
  %total_size = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx28, i32 0, i32 1, !dbg !1024
  store i64 -1, i64* %total_size, align 8, !dbg !1025
  store i32 0, i32* %retval, align 4, !dbg !1026
  br label %return, !dbg !1026

return:                                           ; preds = %if.end18, %if.then16, %if.then8, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !1027
  ret i32 %26, !dbg !1027
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

; Function Attrs: nounwind uwtable
define i32 @archive_read_add_callback_data(%struct.archive* %_a, i8* %client_data, i32 %iindex) #0 !dbg !327 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %iindex.addr = alloca i32, align 4
  %a = alloca %struct.archive_read*, align 8
  %p = alloca i8*, align 8
  %i = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1028, metadata !401), !dbg !1029
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !1030, metadata !401), !dbg !1031
  store i32 %iindex, i32* %iindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %iindex.addr, metadata !1032, metadata !401), !dbg !1033
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !1034, metadata !401), !dbg !1035
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1036
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !1037
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !1035
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1038, metadata !401), !dbg !1039
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1040, metadata !401), !dbg !1041
  br label %do.body, !dbg !1042

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1043, metadata !401), !dbg !1045
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1046
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.10, i32 0, i32 0)), !dbg !1046
  store i32 %call, i32* %magic_test, align 4, !dbg !1046
  %3 = load i32, i32* %magic_test, align 4, !dbg !1046
  %cmp = icmp eq i32 %3, -30, !dbg !1046
  br i1 %cmp, label %if.then, label %if.end, !dbg !1046

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1048
  br label %return, !dbg !1048

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1051

do.end:                                           ; preds = %if.end
  %4 = load i32, i32* %iindex.addr, align 4, !dbg !1053
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1055
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 5, !dbg !1056
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 6, !dbg !1057
  %6 = load i32, i32* %nodes, align 8, !dbg !1057
  %cmp1 = icmp ugt i32 %4, %6, !dbg !1058
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1059

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1060
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !1062
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.9, i32 0, i32 0)), !dbg !1063
  store i32 -30, i32* %retval, align 4, !dbg !1064
  br label %return, !dbg !1064

if.end3:                                          ; preds = %do.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1065
  %client4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 5, !dbg !1066
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client4, i32 0, i32 9, !dbg !1067
  %9 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !1067
  %10 = bitcast %struct.archive_read_data_node* %9 to i8*, !dbg !1065
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1068
  %client5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 5, !dbg !1069
  %nodes6 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client5, i32 0, i32 6, !dbg !1070
  %12 = load i32, i32* %nodes6, align 8, !dbg !1071
  %inc = add i32 %12, 1, !dbg !1071
  store i32 %inc, i32* %nodes6, align 8, !dbg !1071
  %conv = zext i32 %inc to i64, !dbg !1072
  %mul = mul i64 24, %conv, !dbg !1073
  %call7 = call i8* @realloc(i8* %10, i64 %mul) #7, !dbg !1074
  store i8* %call7, i8** %p, align 8, !dbg !1075
  %13 = load i8*, i8** %p, align 8, !dbg !1076
  %cmp8 = icmp eq i8* %13, null, !dbg !1078
  br i1 %cmp8, label %if.then10, label %if.end12, !dbg !1079

if.then10:                                        ; preds = %if.end3
  %14 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1080
  %archive11 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !1082
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive11, i32 12, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.8, i32 0, i32 0)), !dbg !1083
  store i32 -30, i32* %retval, align 4, !dbg !1084
  br label %return, !dbg !1084

if.end12:                                         ; preds = %if.end3
  %15 = load i8*, i8** %p, align 8, !dbg !1085
  %16 = bitcast i8* %15 to %struct.archive_read_data_node*, !dbg !1086
  %17 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1087
  %client13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %17, i32 0, i32 5, !dbg !1088
  %dataset14 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client13, i32 0, i32 9, !dbg !1089
  store %struct.archive_read_data_node* %16, %struct.archive_read_data_node** %dataset14, align 8, !dbg !1090
  %18 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1091
  %client15 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 5, !dbg !1093
  %nodes16 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client15, i32 0, i32 6, !dbg !1094
  %19 = load i32, i32* %nodes16, align 8, !dbg !1094
  %sub = sub i32 %19, 1, !dbg !1095
  store i32 %sub, i32* %i, align 4, !dbg !1096
  br label %for.cond, !dbg !1097

for.cond:                                         ; preds = %for.inc, %if.end12
  %20 = load i32, i32* %i, align 4, !dbg !1098
  %21 = load i32, i32* %iindex.addr, align 4, !dbg !1101
  %cmp17 = icmp ugt i32 %20, %21, !dbg !1102
  br i1 %cmp17, label %land.rhs, label %land.end, !dbg !1103

land.rhs:                                         ; preds = %for.cond
  %22 = load i32, i32* %i, align 4, !dbg !1104
  %cmp19 = icmp ugt i32 %22, 0, !dbg !1106
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %23 = phi i1 [ false, %for.cond ], [ %cmp19, %land.rhs ]
  br i1 %23, label %for.body, label %for.end, !dbg !1107

for.body:                                         ; preds = %land.end
  %24 = load i32, i32* %i, align 4, !dbg !1109
  %sub21 = sub i32 %24, 1, !dbg !1111
  %idxprom = zext i32 %sub21 to i64, !dbg !1112
  %25 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1112
  %client22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 5, !dbg !1113
  %dataset23 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client22, i32 0, i32 9, !dbg !1114
  %26 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset23, align 8, !dbg !1114
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %26, i64 %idxprom, !dbg !1112
  %data = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 2, !dbg !1115
  %27 = load i8*, i8** %data, align 8, !dbg !1115
  %28 = load i32, i32* %i, align 4, !dbg !1116
  %idxprom24 = zext i32 %28 to i64, !dbg !1117
  %29 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1117
  %client25 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 5, !dbg !1118
  %dataset26 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client25, i32 0, i32 9, !dbg !1119
  %30 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset26, align 8, !dbg !1119
  %arrayidx27 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %30, i64 %idxprom24, !dbg !1117
  %data28 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx27, i32 0, i32 2, !dbg !1120
  store i8* %27, i8** %data28, align 8, !dbg !1121
  %31 = load i32, i32* %i, align 4, !dbg !1122
  %idxprom29 = zext i32 %31 to i64, !dbg !1123
  %32 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1123
  %client30 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 5, !dbg !1124
  %dataset31 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client30, i32 0, i32 9, !dbg !1125
  %33 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset31, align 8, !dbg !1125
  %arrayidx32 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %33, i64 %idxprom29, !dbg !1123
  %begin_position = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx32, i32 0, i32 0, !dbg !1126
  store i64 -1, i64* %begin_position, align 8, !dbg !1127
  %34 = load i32, i32* %i, align 4, !dbg !1128
  %idxprom33 = zext i32 %34 to i64, !dbg !1129
  %35 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1129
  %client34 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %35, i32 0, i32 5, !dbg !1130
  %dataset35 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client34, i32 0, i32 9, !dbg !1131
  %36 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset35, align 8, !dbg !1131
  %arrayidx36 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %36, i64 %idxprom33, !dbg !1129
  %total_size = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx36, i32 0, i32 1, !dbg !1132
  store i64 -1, i64* %total_size, align 8, !dbg !1133
  br label %for.inc, !dbg !1134

for.inc:                                          ; preds = %for.body
  %37 = load i32, i32* %i, align 4, !dbg !1135
  %dec = add i32 %37, -1, !dbg !1135
  store i32 %dec, i32* %i, align 4, !dbg !1135
  br label %for.cond, !dbg !1137

for.end:                                          ; preds = %land.end
  %38 = load i8*, i8** %client_data.addr, align 8, !dbg !1138
  %39 = load i32, i32* %iindex.addr, align 4, !dbg !1139
  %idxprom37 = zext i32 %39 to i64, !dbg !1140
  %40 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1140
  %client38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 5, !dbg !1141
  %dataset39 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client38, i32 0, i32 9, !dbg !1142
  %41 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset39, align 8, !dbg !1142
  %arrayidx40 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %41, i64 %idxprom37, !dbg !1140
  %data41 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx40, i32 0, i32 2, !dbg !1143
  store i8* %38, i8** %data41, align 8, !dbg !1144
  %42 = load i32, i32* %iindex.addr, align 4, !dbg !1145
  %idxprom42 = zext i32 %42 to i64, !dbg !1146
  %43 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1146
  %client43 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 5, !dbg !1147
  %dataset44 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client43, i32 0, i32 9, !dbg !1148
  %44 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset44, align 8, !dbg !1148
  %arrayidx45 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %44, i64 %idxprom42, !dbg !1146
  %begin_position46 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx45, i32 0, i32 0, !dbg !1149
  store i64 -1, i64* %begin_position46, align 8, !dbg !1150
  %45 = load i32, i32* %iindex.addr, align 4, !dbg !1151
  %idxprom47 = zext i32 %45 to i64, !dbg !1152
  %46 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1152
  %client48 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %46, i32 0, i32 5, !dbg !1153
  %dataset49 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client48, i32 0, i32 9, !dbg !1154
  %47 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset49, align 8, !dbg !1154
  %arrayidx50 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %47, i64 %idxprom47, !dbg !1152
  %total_size51 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx50, i32 0, i32 1, !dbg !1155
  store i64 -1, i64* %total_size51, align 8, !dbg !1156
  store i32 0, i32* %retval, align 4, !dbg !1157
  br label %return, !dbg !1157

return:                                           ; preds = %for.end, %if.then10, %if.then2, %if.then
  %48 = load i32, i32* %retval, align 4, !dbg !1158
  ret i32 %48, !dbg !1158
}

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #2

; Function Attrs: nounwind uwtable
define i32 @archive_read_append_callback_data(%struct.archive* %_a, i8* %client_data) #0 !dbg !328 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1159, metadata !401), !dbg !1160
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !1161, metadata !401), !dbg !1162
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !1163, metadata !401), !dbg !1164
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1165
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !1166
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !1164
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1167
  %3 = load i8*, i8** %client_data.addr, align 8, !dbg !1168
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1169
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 5, !dbg !1170
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 6, !dbg !1171
  %5 = load i32, i32* %nodes, align 8, !dbg !1171
  %call = call i32 @archive_read_add_callback_data(%struct.archive* %2, i8* %3, i32 %5), !dbg !1172
  ret i32 %call, !dbg !1173
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_prepend_callback_data(%struct.archive* %_a, i8* %client_data) #0 !dbg !329 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1174, metadata !401), !dbg !1175
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !1176, metadata !401), !dbg !1177
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1178
  %1 = load i8*, i8** %client_data.addr, align 8, !dbg !1179
  %call = call i32 @archive_read_add_callback_data(%struct.archive* %0, i8* %1, i32 0), !dbg !1180
  ret i32 %call, !dbg !1181
}

declare void @archive_clear_error(%struct.archive*) #3

; Function Attrs: nounwind uwtable
define internal i32 @client_open_proxy(%struct.archive_read_filter* %self) #0 !dbg !384 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %r = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1182, metadata !401), !dbg !1183
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1184, metadata !401), !dbg !1185
  store i32 0, i32* %r, align 4, !dbg !1185
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1186
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 3, !dbg !1188
  %1 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1188
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 5, !dbg !1189
  %opener = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 0, !dbg !1190
  %2 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener, align 8, !dbg !1190
  %cmp = icmp ne i32 (%struct.archive*, i8*)* %2, null, !dbg !1191
  br i1 %cmp, label %if.then, label %if.end, !dbg !1192

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1193
  %archive1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 3, !dbg !1194
  %4 = load %struct.archive_read*, %struct.archive_read** %archive1, align 8, !dbg !1194
  %client2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 5, !dbg !1195
  %opener3 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client2, i32 0, i32 0, !dbg !1196
  %5 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener3, align 8, !dbg !1196
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1197
  %archive4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 3, !dbg !1198
  %7 = load %struct.archive_read*, %struct.archive_read** %archive4, align 8, !dbg !1198
  %8 = bitcast %struct.archive_read* %7 to %struct.archive*, !dbg !1199
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1200
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %9, i32 0, i32 10, !dbg !1201
  %10 = load i8*, i8** %data, align 8, !dbg !1201
  %call = call i32 %5(%struct.archive* %8, i8* %10), !dbg !1202
  store i32 %call, i32* %r, align 4, !dbg !1203
  br label %if.end, !dbg !1204

if.end:                                           ; preds = %if.then, %entry
  %11 = load i32, i32* %r, align 4, !dbg !1205
  ret i32 %11, !dbg !1206
}

; Function Attrs: nounwind uwtable
define internal i64 @client_read_proxy(%struct.archive_read_filter* %self, i8** %buff) #0 !dbg !385 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %buff.addr = alloca i8**, align 8
  %r = alloca i64, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1207, metadata !401), !dbg !1208
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !1209, metadata !401), !dbg !1210
  call void @llvm.dbg.declare(metadata i64* %r, metadata !1211, metadata !401), !dbg !1212
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1213
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 3, !dbg !1214
  %1 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1214
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 5, !dbg !1215
  %reader = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 1, !dbg !1216
  %2 = load i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i8**)** %reader, align 8, !dbg !1216
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1217
  %archive1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 3, !dbg !1218
  %4 = load %struct.archive_read*, %struct.archive_read** %archive1, align 8, !dbg !1218
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !1219
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1220
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 10, !dbg !1221
  %6 = load i8*, i8** %data, align 8, !dbg !1221
  %7 = load i8**, i8*** %buff.addr, align 8, !dbg !1222
  %call = call i64 %2(%struct.archive* %archive2, i8* %6, i8** %7), !dbg !1223
  store i64 %call, i64* %r, align 8, !dbg !1224
  %8 = load i64, i64* %r, align 8, !dbg !1225
  ret i64 %8, !dbg !1226
}

; Function Attrs: nounwind uwtable
define internal i64 @client_skip_proxy(%struct.archive_read_filter* %self, i64 %request) #0 !dbg !386 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %request.addr = alloca i64, align 8
  %skip_limit = alloca i64, align 8
  %total = alloca i64, align 8
  %get = alloca i64, align 8
  %ask = alloca i64, align 8
  %before = alloca i64, align 8
  %after = alloca i64, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1227, metadata !401), !dbg !1228
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !1229, metadata !401), !dbg !1230
  %0 = load i64, i64* %request.addr, align 8, !dbg !1231
  %cmp = icmp slt i64 %0, 0, !dbg !1233
  br i1 %cmp, label %if.then, label %if.end, !dbg !1234

if.then:                                          ; preds = %entry
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.30, i32 0, i32 0)) #8, !dbg !1235
  unreachable, !dbg !1235

if.end:                                           ; preds = %entry
  %1 = load i64, i64* %request.addr, align 8, !dbg !1236
  %cmp1 = icmp eq i64 %1, 0, !dbg !1238
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1239

if.then2:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !1240
  br label %return, !dbg !1240

if.end3:                                          ; preds = %if.end
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1241
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %2, i32 0, i32 3, !dbg !1243
  %3 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1243
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 5, !dbg !1244
  %skipper = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 2, !dbg !1245
  %4 = load i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64)** %skipper, align 8, !dbg !1245
  %cmp4 = icmp ne i64 (%struct.archive*, i8*, i64)* %4, null, !dbg !1246
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !1247

if.then5:                                         ; preds = %if.end3
  call void @llvm.dbg.declare(metadata i64* %skip_limit, metadata !1248, metadata !401), !dbg !1250
  store i64 1073741824, i64* %skip_limit, align 8, !dbg !1250
  call void @llvm.dbg.declare(metadata i64* %total, metadata !1251, metadata !401), !dbg !1252
  store i64 0, i64* %total, align 8, !dbg !1252
  br label %for.cond, !dbg !1253

for.cond:                                         ; preds = %if.end20, %if.then5
  call void @llvm.dbg.declare(metadata i64* %get, metadata !1254, metadata !401), !dbg !1258
  call void @llvm.dbg.declare(metadata i64* %ask, metadata !1259, metadata !401), !dbg !1260
  %5 = load i64, i64* %request.addr, align 8, !dbg !1261
  store i64 %5, i64* %ask, align 8, !dbg !1260
  %6 = load i64, i64* %ask, align 8, !dbg !1262
  %7 = load i64, i64* %skip_limit, align 8, !dbg !1264
  %cmp6 = icmp sgt i64 %6, %7, !dbg !1265
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1266

if.then7:                                         ; preds = %for.cond
  %8 = load i64, i64* %skip_limit, align 8, !dbg !1267
  store i64 %8, i64* %ask, align 8, !dbg !1268
  br label %if.end8, !dbg !1269

if.end8:                                          ; preds = %if.then7, %for.cond
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1270
  %archive9 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %9, i32 0, i32 3, !dbg !1271
  %10 = load %struct.archive_read*, %struct.archive_read** %archive9, align 8, !dbg !1271
  %client10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 5, !dbg !1272
  %skipper11 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client10, i32 0, i32 2, !dbg !1273
  %11 = load i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64)** %skipper11, align 8, !dbg !1273
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1274
  %archive12 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %12, i32 0, i32 3, !dbg !1275
  %13 = load %struct.archive_read*, %struct.archive_read** %archive12, align 8, !dbg !1275
  %archive13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !1276
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1277
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 10, !dbg !1278
  %15 = load i8*, i8** %data, align 8, !dbg !1278
  %16 = load i64, i64* %ask, align 8, !dbg !1279
  %call = call i64 %11(%struct.archive* %archive13, i8* %15, i64 %16), !dbg !1280
  store i64 %call, i64* %get, align 8, !dbg !1281
  %17 = load i64, i64* %get, align 8, !dbg !1282
  %18 = load i64, i64* %total, align 8, !dbg !1283
  %add = add nsw i64 %18, %17, !dbg !1283
  store i64 %add, i64* %total, align 8, !dbg !1283
  %19 = load i64, i64* %get, align 8, !dbg !1284
  %cmp14 = icmp eq i64 %19, 0, !dbg !1286
  br i1 %cmp14, label %if.then16, label %lor.lhs.false, !dbg !1287

lor.lhs.false:                                    ; preds = %if.end8
  %20 = load i64, i64* %get, align 8, !dbg !1288
  %21 = load i64, i64* %request.addr, align 8, !dbg !1290
  %cmp15 = icmp eq i64 %20, %21, !dbg !1291
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !1292

if.then16:                                        ; preds = %lor.lhs.false, %if.end8
  %22 = load i64, i64* %total, align 8, !dbg !1293
  store i64 %22, i64* %retval, align 8, !dbg !1294
  br label %return, !dbg !1294

if.end17:                                         ; preds = %lor.lhs.false
  %23 = load i64, i64* %get, align 8, !dbg !1295
  %24 = load i64, i64* %request.addr, align 8, !dbg !1297
  %cmp18 = icmp sgt i64 %23, %24, !dbg !1298
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !1299

if.then19:                                        ; preds = %if.end17
  store i64 -30, i64* %retval, align 8, !dbg !1300
  br label %return, !dbg !1300

if.end20:                                         ; preds = %if.end17
  %25 = load i64, i64* %get, align 8, !dbg !1301
  %26 = load i64, i64* %request.addr, align 8, !dbg !1302
  %sub = sub nsw i64 %26, %25, !dbg !1302
  store i64 %sub, i64* %request.addr, align 8, !dbg !1302
  br label %for.cond, !dbg !1303

if.else:                                          ; preds = %if.end3
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1305
  %archive21 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %27, i32 0, i32 3, !dbg !1307
  %28 = load %struct.archive_read*, %struct.archive_read** %archive21, align 8, !dbg !1307
  %client22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 5, !dbg !1308
  %seeker = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client22, i32 0, i32 3, !dbg !1309
  %29 = load i64 (%struct.archive*, i8*, i64, i32)*, i64 (%struct.archive*, i8*, i64, i32)** %seeker, align 8, !dbg !1309
  %cmp23 = icmp ne i64 (%struct.archive*, i8*, i64, i32)* %29, null, !dbg !1310
  br i1 %cmp23, label %land.lhs.true, label %if.end38, !dbg !1311

land.lhs.true:                                    ; preds = %if.else
  %30 = load i64, i64* %request.addr, align 8, !dbg !1312
  %cmp24 = icmp sgt i64 %30, 65536, !dbg !1314
  br i1 %cmp24, label %if.then25, label %if.end38, !dbg !1315

if.then25:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i64* %before, metadata !1317, metadata !401), !dbg !1319
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1320
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %31, i32 0, i32 0, !dbg !1321
  %32 = load i64, i64* %position, align 8, !dbg !1321
  store i64 %32, i64* %before, align 8, !dbg !1319
  call void @llvm.dbg.declare(metadata i64* %after, metadata !1322, metadata !401), !dbg !1323
  %33 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1324
  %archive26 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %33, i32 0, i32 3, !dbg !1325
  %34 = load %struct.archive_read*, %struct.archive_read** %archive26, align 8, !dbg !1325
  %client27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %34, i32 0, i32 5, !dbg !1326
  %seeker28 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client27, i32 0, i32 3, !dbg !1327
  %35 = load i64 (%struct.archive*, i8*, i64, i32)*, i64 (%struct.archive*, i8*, i64, i32)** %seeker28, align 8, !dbg !1327
  %36 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1328
  %archive29 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %36, i32 0, i32 3, !dbg !1329
  %37 = load %struct.archive_read*, %struct.archive_read** %archive29, align 8, !dbg !1329
  %archive30 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %37, i32 0, i32 0, !dbg !1330
  %38 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1331
  %data31 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %38, i32 0, i32 10, !dbg !1332
  %39 = load i8*, i8** %data31, align 8, !dbg !1332
  %40 = load i64, i64* %request.addr, align 8, !dbg !1333
  %call32 = call i64 %35(%struct.archive* %archive30, i8* %39, i64 %40, i32 1), !dbg !1334
  store i64 %call32, i64* %after, align 8, !dbg !1323
  %41 = load i64, i64* %after, align 8, !dbg !1335
  %42 = load i64, i64* %before, align 8, !dbg !1337
  %43 = load i64, i64* %request.addr, align 8, !dbg !1338
  %add33 = add nsw i64 %42, %43, !dbg !1339
  %cmp34 = icmp ne i64 %41, %add33, !dbg !1340
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !1341

if.then35:                                        ; preds = %if.then25
  store i64 -30, i64* %retval, align 8, !dbg !1342
  br label %return, !dbg !1342

if.end36:                                         ; preds = %if.then25
  %44 = load i64, i64* %after, align 8, !dbg !1343
  %45 = load i64, i64* %before, align 8, !dbg !1344
  %sub37 = sub nsw i64 %44, %45, !dbg !1345
  store i64 %sub37, i64* %retval, align 8, !dbg !1346
  br label %return, !dbg !1346

if.end38:                                         ; preds = %land.lhs.true, %if.else
  br label %if.end39

if.end39:                                         ; preds = %if.end38
  store i64 0, i64* %retval, align 8, !dbg !1347
  br label %return, !dbg !1347

return:                                           ; preds = %if.end39, %if.end36, %if.then35, %if.then19, %if.then16, %if.then2
  %46 = load i64, i64* %retval, align 8, !dbg !1348
  ret i64 %46, !dbg !1348
}

; Function Attrs: nounwind uwtable
define internal i64 @client_seek_proxy(%struct.archive_read_filter* %self, i64 %offset, i32 %whence) #0 !dbg !387 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1349, metadata !401), !dbg !1350
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !1351, metadata !401), !dbg !1352
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !1353, metadata !401), !dbg !1354
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1355
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 3, !dbg !1357
  %1 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1357
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 5, !dbg !1358
  %seeker = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 3, !dbg !1359
  %2 = load i64 (%struct.archive*, i8*, i64, i32)*, i64 (%struct.archive*, i8*, i64, i32)** %seeker, align 8, !dbg !1359
  %cmp = icmp eq i64 (%struct.archive*, i8*, i64, i32)* %2, null, !dbg !1360
  br i1 %cmp, label %if.then, label %if.end, !dbg !1361

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1362
  %archive1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 3, !dbg !1364
  %4 = load %struct.archive_read*, %struct.archive_read** %archive1, align 8, !dbg !1364
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !1365
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive2, i32 -1, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.31, i32 0, i32 0)), !dbg !1366
  store i64 -25, i64* %retval, align 8, !dbg !1367
  br label %return, !dbg !1367

if.end:                                           ; preds = %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1368
  %archive3 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !1369
  %6 = load %struct.archive_read*, %struct.archive_read** %archive3, align 8, !dbg !1369
  %client4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 5, !dbg !1370
  %seeker5 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client4, i32 0, i32 3, !dbg !1371
  %7 = load i64 (%struct.archive*, i8*, i64, i32)*, i64 (%struct.archive*, i8*, i64, i32)** %seeker5, align 8, !dbg !1371
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1372
  %archive6 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 3, !dbg !1373
  %9 = load %struct.archive_read*, %struct.archive_read** %archive6, align 8, !dbg !1373
  %archive7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !1374
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1375
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 10, !dbg !1376
  %11 = load i8*, i8** %data, align 8, !dbg !1376
  %12 = load i64, i64* %offset.addr, align 8, !dbg !1377
  %13 = load i32, i32* %whence.addr, align 4, !dbg !1378
  %call = call i64 %7(%struct.archive* %archive7, i8* %11, i64 %12, i32 %13), !dbg !1379
  store i64 %call, i64* %retval, align 8, !dbg !1380
  br label %return, !dbg !1380

return:                                           ; preds = %if.end, %if.then
  %14 = load i64, i64* %retval, align 8, !dbg !1381
  ret i64 %14, !dbg !1381
}

; Function Attrs: nounwind uwtable
define internal i32 @client_close_proxy(%struct.archive_read_filter* %self) #0 !dbg !388 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %r = alloca i32, align 4
  %r2 = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1382, metadata !401), !dbg !1383
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1384, metadata !401), !dbg !1385
  store i32 0, i32* %r, align 4, !dbg !1385
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !1386, metadata !401), !dbg !1387
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1388, metadata !401), !dbg !1389
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1390
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 3, !dbg !1392
  %1 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1392
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 5, !dbg !1393
  %closer = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 4, !dbg !1394
  %2 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer, align 8, !dbg !1394
  %cmp = icmp eq i32 (%struct.archive*, i8*)* %2, null, !dbg !1395
  br i1 %cmp, label %if.then, label %if.end, !dbg !1396

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !1397
  store i32 %3, i32* %retval, align 4, !dbg !1398
  br label %return, !dbg !1398

if.end:                                           ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !1399
  br label %for.cond, !dbg !1401

for.cond:                                         ; preds = %for.inc, %if.end
  %4 = load i32, i32* %i, align 4, !dbg !1402
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1405
  %archive1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !1406
  %6 = load %struct.archive_read*, %struct.archive_read** %archive1, align 8, !dbg !1406
  %client2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 5, !dbg !1407
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client2, i32 0, i32 6, !dbg !1408
  %7 = load i32, i32* %nodes, align 8, !dbg !1408
  %cmp3 = icmp ult i32 %4, %7, !dbg !1409
  br i1 %cmp3, label %for.body, label %for.end, !dbg !1410

for.body:                                         ; preds = %for.cond
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1411
  %archive4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 3, !dbg !1413
  %9 = load %struct.archive_read*, %struct.archive_read** %archive4, align 8, !dbg !1413
  %client5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 5, !dbg !1414
  %closer6 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client5, i32 0, i32 4, !dbg !1415
  %10 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer6, align 8, !dbg !1415
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1416
  %archive7 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 3, !dbg !1417
  %12 = load %struct.archive_read*, %struct.archive_read** %archive7, align 8, !dbg !1417
  %13 = bitcast %struct.archive_read* %12 to %struct.archive*, !dbg !1418
  %14 = load i32, i32* %i, align 4, !dbg !1419
  %idxprom = zext i32 %14 to i64, !dbg !1420
  %15 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1420
  %archive8 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %15, i32 0, i32 3, !dbg !1421
  %16 = load %struct.archive_read*, %struct.archive_read** %archive8, align 8, !dbg !1421
  %client9 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 5, !dbg !1422
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client9, i32 0, i32 9, !dbg !1423
  %17 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !1423
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %17, i64 %idxprom, !dbg !1420
  %data = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 2, !dbg !1424
  %18 = load i8*, i8** %data, align 8, !dbg !1424
  %call = call i32 %10(%struct.archive* %13, i8* %18), !dbg !1425
  store i32 %call, i32* %r2, align 4, !dbg !1426
  %19 = load i32, i32* %r, align 4, !dbg !1427
  %20 = load i32, i32* %r2, align 4, !dbg !1429
  %cmp10 = icmp sgt i32 %19, %20, !dbg !1430
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !1431

if.then11:                                        ; preds = %for.body
  %21 = load i32, i32* %r2, align 4, !dbg !1432
  store i32 %21, i32* %r, align 4, !dbg !1433
  br label %if.end12, !dbg !1434

if.end12:                                         ; preds = %if.then11, %for.body
  br label %for.inc, !dbg !1435

for.inc:                                          ; preds = %if.end12
  %22 = load i32, i32* %i, align 4, !dbg !1436
  %inc = add i32 %22, 1, !dbg !1436
  store i32 %inc, i32* %i, align 4, !dbg !1436
  br label %for.cond, !dbg !1438

for.end:                                          ; preds = %for.cond
  %23 = load i32, i32* %r, align 4, !dbg !1439
  store i32 %23, i32* %retval, align 4, !dbg !1440
  br label %return, !dbg !1440

return:                                           ; preds = %for.end, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !1441
  ret i32 %24, !dbg !1441
}

; Function Attrs: nounwind uwtable
define internal i32 @client_switch_proxy(%struct.archive_read_filter* %self, i32 %iindex) #0 !dbg !389 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %iindex.addr = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %data2 = alloca i8*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1442, metadata !401), !dbg !1443
  store i32 %iindex, i32* %iindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %iindex.addr, metadata !1444, metadata !401), !dbg !1445
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !1446, metadata !401), !dbg !1447
  store i32 0, i32* %r1, align 4, !dbg !1447
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !1448, metadata !401), !dbg !1449
  store i32 0, i32* %r2, align 4, !dbg !1449
  call void @llvm.dbg.declare(metadata i8** %data2, metadata !1450, metadata !401), !dbg !1451
  store i8* null, i8** %data2, align 8, !dbg !1451
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1452
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 3, !dbg !1454
  %1 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1454
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 5, !dbg !1455
  %cursor = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 7, !dbg !1456
  %2 = load i32, i32* %cursor, align 4, !dbg !1456
  %3 = load i32, i32* %iindex.addr, align 4, !dbg !1457
  %cmp = icmp eq i32 %2, %3, !dbg !1458
  br i1 %cmp, label %if.then, label %if.end, !dbg !1459

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1460
  br label %return, !dbg !1460

if.end:                                           ; preds = %entry
  %4 = load i32, i32* %iindex.addr, align 4, !dbg !1461
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1462
  %archive1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !1463
  %6 = load %struct.archive_read*, %struct.archive_read** %archive1, align 8, !dbg !1463
  %client2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 5, !dbg !1464
  %cursor3 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client2, i32 0, i32 7, !dbg !1465
  store i32 %4, i32* %cursor3, align 4, !dbg !1466
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1467
  %archive4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 3, !dbg !1468
  %8 = load %struct.archive_read*, %struct.archive_read** %archive4, align 8, !dbg !1468
  %client5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 5, !dbg !1469
  %cursor6 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client5, i32 0, i32 7, !dbg !1470
  %9 = load i32, i32* %cursor6, align 4, !dbg !1470
  %idxprom = zext i32 %9 to i64, !dbg !1471
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1471
  %archive7 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 3, !dbg !1472
  %11 = load %struct.archive_read*, %struct.archive_read** %archive7, align 8, !dbg !1472
  %client8 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 5, !dbg !1473
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client8, i32 0, i32 9, !dbg !1474
  %12 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !1474
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %12, i64 %idxprom, !dbg !1471
  %data = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 2, !dbg !1475
  %13 = load i8*, i8** %data, align 8, !dbg !1475
  store i8* %13, i8** %data2, align 8, !dbg !1476
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1477
  %archive9 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 3, !dbg !1479
  %15 = load %struct.archive_read*, %struct.archive_read** %archive9, align 8, !dbg !1479
  %client10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 5, !dbg !1480
  %switcher = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client10, i32 0, i32 5, !dbg !1481
  %16 = load i32 (%struct.archive*, i8*, i8*)*, i32 (%struct.archive*, i8*, i8*)** %switcher, align 8, !dbg !1481
  %cmp11 = icmp ne i32 (%struct.archive*, i8*, i8*)* %16, null, !dbg !1482
  br i1 %cmp11, label %if.then12, label %if.else, !dbg !1483

if.then12:                                        ; preds = %if.end
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1484
  %archive13 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %17, i32 0, i32 3, !dbg !1486
  %18 = load %struct.archive_read*, %struct.archive_read** %archive13, align 8, !dbg !1486
  %client14 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 5, !dbg !1487
  %switcher15 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client14, i32 0, i32 5, !dbg !1488
  %19 = load i32 (%struct.archive*, i8*, i8*)*, i32 (%struct.archive*, i8*, i8*)** %switcher15, align 8, !dbg !1488
  %20 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1489
  %archive16 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %20, i32 0, i32 3, !dbg !1490
  %21 = load %struct.archive_read*, %struct.archive_read** %archive16, align 8, !dbg !1490
  %22 = bitcast %struct.archive_read* %21 to %struct.archive*, !dbg !1491
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1492
  %data17 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 10, !dbg !1493
  %24 = load i8*, i8** %data17, align 8, !dbg !1493
  %25 = load i8*, i8** %data2, align 8, !dbg !1494
  %call = call i32 %19(%struct.archive* %22, i8* %24, i8* %25), !dbg !1495
  store i32 %call, i32* %r2, align 4, !dbg !1496
  store i32 %call, i32* %r1, align 4, !dbg !1497
  %26 = load i8*, i8** %data2, align 8, !dbg !1498
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1499
  %data18 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %27, i32 0, i32 10, !dbg !1500
  store i8* %26, i8** %data18, align 8, !dbg !1501
  br label %if.end42, !dbg !1502

if.else:                                          ; preds = %if.end
  %28 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1503
  %archive19 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %28, i32 0, i32 3, !dbg !1506
  %29 = load %struct.archive_read*, %struct.archive_read** %archive19, align 8, !dbg !1506
  %client20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 5, !dbg !1507
  %closer = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client20, i32 0, i32 4, !dbg !1508
  %30 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer, align 8, !dbg !1508
  %cmp21 = icmp ne i32 (%struct.archive*, i8*)* %30, null, !dbg !1509
  br i1 %cmp21, label %if.then22, label %if.end29, !dbg !1510

if.then22:                                        ; preds = %if.else
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1511
  %archive23 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %31, i32 0, i32 3, !dbg !1512
  %32 = load %struct.archive_read*, %struct.archive_read** %archive23, align 8, !dbg !1512
  %client24 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 5, !dbg !1513
  %closer25 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client24, i32 0, i32 4, !dbg !1514
  %33 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %closer25, align 8, !dbg !1514
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1515
  %archive26 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %34, i32 0, i32 3, !dbg !1516
  %35 = load %struct.archive_read*, %struct.archive_read** %archive26, align 8, !dbg !1516
  %36 = bitcast %struct.archive_read* %35 to %struct.archive*, !dbg !1517
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1518
  %data27 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %37, i32 0, i32 10, !dbg !1519
  %38 = load i8*, i8** %data27, align 8, !dbg !1519
  %call28 = call i32 %33(%struct.archive* %36, i8* %38), !dbg !1520
  store i32 %call28, i32* %r1, align 4, !dbg !1521
  br label %if.end29, !dbg !1522

if.end29:                                         ; preds = %if.then22, %if.else
  %39 = load i8*, i8** %data2, align 8, !dbg !1523
  %40 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1524
  %data30 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %40, i32 0, i32 10, !dbg !1525
  store i8* %39, i8** %data30, align 8, !dbg !1526
  %41 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1527
  %archive31 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %41, i32 0, i32 3, !dbg !1529
  %42 = load %struct.archive_read*, %struct.archive_read** %archive31, align 8, !dbg !1529
  %client32 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %42, i32 0, i32 5, !dbg !1530
  %opener = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client32, i32 0, i32 0, !dbg !1531
  %43 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener, align 8, !dbg !1531
  %cmp33 = icmp ne i32 (%struct.archive*, i8*)* %43, null, !dbg !1532
  br i1 %cmp33, label %if.then34, label %if.end41, !dbg !1533

if.then34:                                        ; preds = %if.end29
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1534
  %archive35 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %44, i32 0, i32 3, !dbg !1535
  %45 = load %struct.archive_read*, %struct.archive_read** %archive35, align 8, !dbg !1535
  %client36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %45, i32 0, i32 5, !dbg !1536
  %opener37 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client36, i32 0, i32 0, !dbg !1537
  %46 = load i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*)** %opener37, align 8, !dbg !1537
  %47 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1538
  %archive38 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %47, i32 0, i32 3, !dbg !1539
  %48 = load %struct.archive_read*, %struct.archive_read** %archive38, align 8, !dbg !1539
  %49 = bitcast %struct.archive_read* %48 to %struct.archive*, !dbg !1540
  %50 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1541
  %data39 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %50, i32 0, i32 10, !dbg !1542
  %51 = load i8*, i8** %data39, align 8, !dbg !1542
  %call40 = call i32 %46(%struct.archive* %49, i8* %51), !dbg !1543
  store i32 %call40, i32* %r2, align 4, !dbg !1544
  br label %if.end41, !dbg !1545

if.end41:                                         ; preds = %if.then34, %if.end29
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %if.then12
  %52 = load i32, i32* %r1, align 4, !dbg !1546
  %53 = load i32, i32* %r2, align 4, !dbg !1547
  %cmp43 = icmp slt i32 %52, %53, !dbg !1548
  br i1 %cmp43, label %cond.true, label %cond.false, !dbg !1549

cond.true:                                        ; preds = %if.end42
  %54 = load i32, i32* %r1, align 4, !dbg !1550
  br label %cond.end, !dbg !1552

cond.false:                                       ; preds = %if.end42
  %55 = load i32, i32* %r2, align 4, !dbg !1553
  br label %cond.end, !dbg !1555

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %54, %cond.true ], [ %55, %cond.false ], !dbg !1556
  store i32 %cond, i32* %retval, align 4, !dbg !1558
  br label %return, !dbg !1558

return:                                           ; preds = %cond.end, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !1559
  ret i32 %56, !dbg !1559
}

; Function Attrs: nounwind uwtable
define internal i32 @choose_filters(%struct.archive_read* %a) #0 !dbg !390 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %number_bidders = alloca i32, align 4
  %i = alloca i32, align 4
  %bid = alloca i32, align 4
  %best_bid = alloca i32, align 4
  %number_filters = alloca i32, align 4
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %best_bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %filter = alloca %struct.archive_read_filter*, align 8
  %avail = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1560, metadata !401), !dbg !1561
  call void @llvm.dbg.declare(metadata i32* %number_bidders, metadata !1562, metadata !401), !dbg !1563
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1564, metadata !401), !dbg !1565
  call void @llvm.dbg.declare(metadata i32* %bid, metadata !1566, metadata !401), !dbg !1567
  call void @llvm.dbg.declare(metadata i32* %best_bid, metadata !1568, metadata !401), !dbg !1569
  call void @llvm.dbg.declare(metadata i32* %number_filters, metadata !1570, metadata !401), !dbg !1571
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !1572, metadata !401), !dbg !1573
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %best_bidder, metadata !1574, metadata !401), !dbg !1575
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter, metadata !1576, metadata !401), !dbg !1577
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !1578, metadata !401), !dbg !1579
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1580, metadata !401), !dbg !1581
  store i32 0, i32* %number_filters, align 4, !dbg !1582
  br label %for.cond, !dbg !1584

for.cond:                                         ; preds = %for.inc35, %entry
  %0 = load i32, i32* %number_filters, align 4, !dbg !1585
  %cmp = icmp slt i32 %0, 25, !dbg !1588
  br i1 %cmp, label %for.body, label %for.end37, !dbg !1589

for.body:                                         ; preds = %for.cond
  store i32 16, i32* %number_bidders, align 4, !dbg !1590
  store i32 0, i32* %best_bid, align 4, !dbg !1592
  store %struct.archive_read_filter_bidder* null, %struct.archive_read_filter_bidder** %best_bidder, align 8, !dbg !1593
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1594
  %bidders = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 6, !dbg !1595
  %arraydecay = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders, i32 0, i32 0, !dbg !1594
  store %struct.archive_read_filter_bidder* %arraydecay, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1596
  store i32 0, i32* %i, align 4, !dbg !1597
  br label %for.cond1, !dbg !1599

for.cond1:                                        ; preds = %for.inc, %for.body
  %2 = load i32, i32* %i, align 4, !dbg !1600
  %3 = load i32, i32* %number_bidders, align 4, !dbg !1603
  %cmp2 = icmp slt i32 %2, %3, !dbg !1604
  br i1 %cmp2, label %for.body3, label %for.end, !dbg !1605

for.body3:                                        ; preds = %for.cond1
  %4 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1606
  %bid4 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %4, i32 0, i32 2, !dbg !1609
  %5 = load i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid4, align 8, !dbg !1609
  %cmp5 = icmp ne i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* %5, null, !dbg !1610
  br i1 %cmp5, label %if.then, label %if.end10, !dbg !1611

if.then:                                          ; preds = %for.body3
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1612
  %bid6 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 2, !dbg !1614
  %7 = load i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid6, align 8, !dbg !1614
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1615
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1616
  %filter7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 7, !dbg !1617
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter7, align 8, !dbg !1617
  %call = call i32 %7(%struct.archive_read_filter_bidder* %8, %struct.archive_read_filter* %10), !dbg !1618
  store i32 %call, i32* %bid, align 4, !dbg !1619
  %11 = load i32, i32* %bid, align 4, !dbg !1620
  %12 = load i32, i32* %best_bid, align 4, !dbg !1622
  %cmp8 = icmp sgt i32 %11, %12, !dbg !1623
  br i1 %cmp8, label %if.then9, label %if.end, !dbg !1624

if.then9:                                         ; preds = %if.then
  %13 = load i32, i32* %bid, align 4, !dbg !1625
  store i32 %13, i32* %best_bid, align 4, !dbg !1627
  %14 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1628
  store %struct.archive_read_filter_bidder* %14, %struct.archive_read_filter_bidder** %best_bidder, align 8, !dbg !1629
  br label %if.end, !dbg !1630

if.end:                                           ; preds = %if.then9, %if.then
  br label %if.end10, !dbg !1631

if.end10:                                         ; preds = %if.end, %for.body3
  br label %for.inc, !dbg !1632

for.inc:                                          ; preds = %if.end10
  %15 = load i32, i32* %i, align 4, !dbg !1633
  %inc = add nsw i32 %15, 1, !dbg !1633
  store i32 %inc, i32* %i, align 4, !dbg !1633
  %16 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1635
  %incdec.ptr = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %16, i32 1, !dbg !1635
  store %struct.archive_read_filter_bidder* %incdec.ptr, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !1635
  br label %for.cond1, !dbg !1636

for.end:                                          ; preds = %for.cond1
  %17 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %best_bidder, align 8, !dbg !1637
  %cmp11 = icmp eq %struct.archive_read_filter_bidder* %17, null, !dbg !1639
  br i1 %cmp11, label %if.then12, label %if.end21, !dbg !1640

if.then12:                                        ; preds = %for.end
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1641
  %filter13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 7, !dbg !1643
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter13, align 8, !dbg !1643
  %call14 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %19, i64 1, i64* %avail), !dbg !1644
  %20 = load i64, i64* %avail, align 8, !dbg !1645
  %cmp15 = icmp slt i64 %20, 0, !dbg !1647
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !1648

if.then16:                                        ; preds = %if.then12
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1649
  call void @__archive_read_free_filters(%struct.archive_read* %21), !dbg !1651
  store i32 -30, i32* %retval, align 4, !dbg !1652
  br label %return, !dbg !1652

if.end17:                                         ; preds = %if.then12
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1653
  %filter18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 7, !dbg !1654
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter18, align 8, !dbg !1654
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 11, !dbg !1655
  %24 = load i8*, i8** %name, align 8, !dbg !1655
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1656
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 0, !dbg !1657
  %compression_name = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 6, !dbg !1658
  store i8* %24, i8** %compression_name, align 8, !dbg !1659
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1660
  %filter19 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 7, !dbg !1661
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter19, align 8, !dbg !1661
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %27, i32 0, i32 12, !dbg !1662
  %28 = load i32, i32* %code, align 8, !dbg !1662
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1663
  %archive20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !1664
  %compression_code = getelementptr inbounds %struct.archive, %struct.archive* %archive20, i32 0, i32 5, !dbg !1665
  store i32 %28, i32* %compression_code, align 8, !dbg !1666
  store i32 0, i32* %retval, align 4, !dbg !1667
  br label %return, !dbg !1667

if.end21:                                         ; preds = %for.end
  %call22 = call noalias i8* @calloc(i64 1, i64 176) #7, !dbg !1668
  %30 = bitcast i8* %call22 to %struct.archive_read_filter*, !dbg !1669
  store %struct.archive_read_filter* %30, %struct.archive_read_filter** %filter, align 8, !dbg !1670
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1671
  %cmp23 = icmp eq %struct.archive_read_filter* %31, null, !dbg !1673
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !1674

if.then24:                                        ; preds = %if.end21
  store i32 -30, i32* %retval, align 4, !dbg !1675
  br label %return, !dbg !1675

if.end25:                                         ; preds = %if.end21
  %32 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %best_bidder, align 8, !dbg !1676
  %33 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1677
  %bidder26 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %33, i32 0, i32 1, !dbg !1678
  store %struct.archive_read_filter_bidder* %32, %struct.archive_read_filter_bidder** %bidder26, align 8, !dbg !1679
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1680
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1681
  %archive27 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %35, i32 0, i32 3, !dbg !1682
  store %struct.archive_read* %34, %struct.archive_read** %archive27, align 8, !dbg !1683
  %36 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1684
  %filter28 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %36, i32 0, i32 7, !dbg !1685
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter28, align 8, !dbg !1685
  %38 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1686
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %38, i32 0, i32 2, !dbg !1687
  store %struct.archive_read_filter* %37, %struct.archive_read_filter** %upstream, align 8, !dbg !1688
  %39 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1689
  %40 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1690
  %filter29 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 7, !dbg !1691
  store %struct.archive_read_filter* %39, %struct.archive_read_filter** %filter29, align 8, !dbg !1692
  %41 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %best_bidder, align 8, !dbg !1693
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %41, i32 0, i32 3, !dbg !1694
  %42 = load i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !1694
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1695
  %filter30 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 7, !dbg !1696
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter30, align 8, !dbg !1696
  %call31 = call i32 %42(%struct.archive_read_filter* %44), !dbg !1697
  store i32 %call31, i32* %r, align 4, !dbg !1698
  %45 = load i32, i32* %r, align 4, !dbg !1699
  %cmp32 = icmp ne i32 %45, 0, !dbg !1701
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !1702

if.then33:                                        ; preds = %if.end25
  %46 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1703
  call void @__archive_read_free_filters(%struct.archive_read* %46), !dbg !1705
  store i32 -30, i32* %retval, align 4, !dbg !1706
  br label %return, !dbg !1706

if.end34:                                         ; preds = %if.end25
  br label %for.inc35, !dbg !1707

for.inc35:                                        ; preds = %if.end34
  %47 = load i32, i32* %number_filters, align 4, !dbg !1708
  %inc36 = add nsw i32 %47, 1, !dbg !1708
  store i32 %inc36, i32* %number_filters, align 4, !dbg !1708
  br label %for.cond, !dbg !1710

for.end37:                                        ; preds = %for.cond
  %48 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1711
  %archive38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %48, i32 0, i32 0, !dbg !1712
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive38, i32 84, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.32, i32 0, i32 0)), !dbg !1713
  store i32 -30, i32* %retval, align 4, !dbg !1714
  br label %return, !dbg !1714

return:                                           ; preds = %for.end37, %if.then33, %if.then24, %if.end17, %if.then16
  %49 = load i32, i32* %retval, align 4, !dbg !1715
  ret i32 %49, !dbg !1715
}

; Function Attrs: nounwind uwtable
define internal i32 @choose_format(%struct.archive_read* %a) #0 !dbg !391 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %slots = alloca i32, align 4
  %i = alloca i32, align 4
  %bid = alloca i32, align 4
  %best_bid = alloca i32, align 4
  %best_bid_slot = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1716, metadata !401), !dbg !1717
  call void @llvm.dbg.declare(metadata i32* %slots, metadata !1718, metadata !401), !dbg !1719
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1720, metadata !401), !dbg !1721
  call void @llvm.dbg.declare(metadata i32* %bid, metadata !1722, metadata !401), !dbg !1723
  call void @llvm.dbg.declare(metadata i32* %best_bid, metadata !1724, metadata !401), !dbg !1725
  call void @llvm.dbg.declare(metadata i32* %best_bid_slot, metadata !1726, metadata !401), !dbg !1727
  store i32 16, i32* %slots, align 4, !dbg !1728
  store i32 -1, i32* %best_bid, align 4, !dbg !1729
  store i32 -1, i32* %best_bid_slot, align 4, !dbg !1730
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1731
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 12, !dbg !1732
  %arrayidx = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 0, !dbg !1731
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1733
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 13, !dbg !1734
  store %struct.archive_format_descriptor* %arrayidx, %struct.archive_format_descriptor** %format, align 8, !dbg !1735
  store i32 0, i32* %i, align 4, !dbg !1736
  br label %for.cond, !dbg !1738

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i32, i32* %i, align 4, !dbg !1739
  %3 = load i32, i32* %slots, align 4, !dbg !1742
  %cmp = icmp slt i32 %2, %3, !dbg !1743
  br i1 %cmp, label %for.body, label %for.end, !dbg !1744

for.body:                                         ; preds = %for.cond
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1745
  %format1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 13, !dbg !1748
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format1, align 8, !dbg !1748
  %bid2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 2, !dbg !1749
  %6 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid2, align 8, !dbg !1749
  %tobool = icmp ne i32 (%struct.archive_read*, i32)* %6, null, !dbg !1745
  br i1 %tobool, label %if.then, label %if.end15, !dbg !1750

if.then:                                          ; preds = %for.body
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1751
  %format3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 13, !dbg !1753
  %8 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format3, align 8, !dbg !1753
  %bid4 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %8, i32 0, i32 2, !dbg !1754
  %9 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid4, align 8, !dbg !1754
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1755
  %11 = load i32, i32* %best_bid, align 4, !dbg !1756
  %call = call i32 %9(%struct.archive_read* %10, i32 %11), !dbg !1757
  store i32 %call, i32* %bid, align 4, !dbg !1758
  %12 = load i32, i32* %bid, align 4, !dbg !1759
  %cmp5 = icmp eq i32 %12, -30, !dbg !1761
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !1762

if.then6:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !1763
  br label %return, !dbg !1763

if.end:                                           ; preds = %if.then
  %13 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1764
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 7, !dbg !1766
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1766
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 0, !dbg !1767
  %15 = load i64, i64* %position, align 8, !dbg !1767
  %cmp7 = icmp ne i64 %15, 0, !dbg !1768
  br i1 %cmp7, label %if.then8, label %if.end10, !dbg !1769

if.then8:                                         ; preds = %if.end
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1770
  %call9 = call i64 @__archive_read_seek(%struct.archive_read* %16, i64 0, i32 0), !dbg !1771
  br label %if.end10, !dbg !1771

if.end10:                                         ; preds = %if.then8, %if.end
  %17 = load i32, i32* %bid, align 4, !dbg !1772
  %18 = load i32, i32* %best_bid, align 4, !dbg !1774
  %cmp11 = icmp sgt i32 %17, %18, !dbg !1775
  br i1 %cmp11, label %if.then13, label %lor.lhs.false, !dbg !1776

lor.lhs.false:                                    ; preds = %if.end10
  %19 = load i32, i32* %best_bid_slot, align 4, !dbg !1777
  %cmp12 = icmp slt i32 %19, 0, !dbg !1779
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1780

if.then13:                                        ; preds = %lor.lhs.false, %if.end10
  %20 = load i32, i32* %bid, align 4, !dbg !1781
  store i32 %20, i32* %best_bid, align 4, !dbg !1783
  %21 = load i32, i32* %i, align 4, !dbg !1784
  store i32 %21, i32* %best_bid_slot, align 4, !dbg !1785
  br label %if.end14, !dbg !1786

if.end14:                                         ; preds = %if.then13, %lor.lhs.false
  br label %if.end15, !dbg !1787

if.end15:                                         ; preds = %if.end14, %for.body
  br label %for.inc, !dbg !1788

for.inc:                                          ; preds = %if.end15
  %22 = load i32, i32* %i, align 4, !dbg !1789
  %inc = add nsw i32 %22, 1, !dbg !1789
  store i32 %inc, i32* %i, align 4, !dbg !1789
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1791
  %format16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 13, !dbg !1792
  %24 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format16, align 8, !dbg !1793
  %incdec.ptr = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %24, i32 1, !dbg !1793
  store %struct.archive_format_descriptor* %incdec.ptr, %struct.archive_format_descriptor** %format16, align 8, !dbg !1793
  br label %for.cond, !dbg !1794

for.end:                                          ; preds = %for.cond
  %25 = load i32, i32* %best_bid_slot, align 4, !dbg !1795
  %cmp17 = icmp slt i32 %25, 0, !dbg !1797
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !1798

if.then18:                                        ; preds = %for.end
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1799
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 0, !dbg !1801
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.33, i32 0, i32 0)), !dbg !1802
  store i32 -30, i32* %retval, align 4, !dbg !1803
  br label %return, !dbg !1803

if.end19:                                         ; preds = %for.end
  %27 = load i32, i32* %best_bid, align 4, !dbg !1804
  %cmp20 = icmp slt i32 %27, 1, !dbg !1806
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !1807

if.then21:                                        ; preds = %if.end19
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1808
  %archive22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 0, !dbg !1810
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive22, i32 84, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.34, i32 0, i32 0)), !dbg !1811
  store i32 -30, i32* %retval, align 4, !dbg !1812
  br label %return, !dbg !1812

if.end23:                                         ; preds = %if.end19
  %29 = load i32, i32* %best_bid_slot, align 4, !dbg !1813
  store i32 %29, i32* %retval, align 4, !dbg !1814
  br label %return, !dbg !1814

return:                                           ; preds = %if.end23, %if.then21, %if.then18, %if.then6
  %30 = load i32, i32* %retval, align 4, !dbg !1815
  ret i32 %30, !dbg !1815
}

; Function Attrs: nounwind uwtable
define internal i32 @close_filters(%struct.archive_read* %a) #0 !dbg !392 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %f = alloca %struct.archive_read_filter*, align 8
  %r = alloca i32, align 4
  %t = alloca %struct.archive_read_filter*, align 8
  %r1 = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1816, metadata !401), !dbg !1817
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %f, metadata !1818, metadata !401), !dbg !1819
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1820
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 7, !dbg !1821
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !1821
  store %struct.archive_read_filter* %1, %struct.archive_read_filter** %f, align 8, !dbg !1819
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1822, metadata !401), !dbg !1823
  store i32 0, i32* %r, align 4, !dbg !1823
  br label %while.cond, !dbg !1824

while.cond:                                       ; preds = %if.end6, %entry
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1825
  %cmp = icmp ne %struct.archive_read_filter* %2, null, !dbg !1827
  br i1 %cmp, label %while.body, label %while.end, !dbg !1828

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %t, metadata !1829, metadata !401), !dbg !1831
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1832
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 2, !dbg !1833
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !1833
  store %struct.archive_read_filter* %4, %struct.archive_read_filter** %t, align 8, !dbg !1831
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1834
  %closed = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 22, !dbg !1836
  %6 = load i8, i8* %closed, align 1, !dbg !1836
  %tobool = icmp ne i8 %6, 0, !dbg !1834
  br i1 %tobool, label %if.end6, label %land.lhs.true, !dbg !1837

land.lhs.true:                                    ; preds = %while.body
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1838
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 8, !dbg !1840
  %8 = load i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !1840
  %cmp1 = icmp ne i32 (%struct.archive_read_filter*)* %8, null, !dbg !1841
  br i1 %cmp1, label %if.then, label %if.end6, !dbg !1842

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !1843, metadata !401), !dbg !1845
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1846
  %close2 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %9, i32 0, i32 8, !dbg !1847
  %10 = load i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)** %close2, align 8, !dbg !1847
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1848
  %call = call i32 %10(%struct.archive_read_filter* %11), !dbg !1849
  store i32 %call, i32* %r1, align 4, !dbg !1845
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1850
  %closed3 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %12, i32 0, i32 22, !dbg !1851
  store i8 1, i8* %closed3, align 1, !dbg !1852
  %13 = load i32, i32* %r1, align 4, !dbg !1853
  %14 = load i32, i32* %r, align 4, !dbg !1855
  %cmp4 = icmp slt i32 %13, %14, !dbg !1856
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !1857

if.then5:                                         ; preds = %if.then
  %15 = load i32, i32* %r1, align 4, !dbg !1858
  store i32 %15, i32* %r, align 4, !dbg !1859
  br label %if.end, !dbg !1860

if.end:                                           ; preds = %if.then5, %if.then
  br label %if.end6, !dbg !1861

if.end6:                                          ; preds = %if.end, %land.lhs.true, %while.body
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1862
  %buffer = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %16, i32 0, i32 13, !dbg !1863
  %17 = load i8*, i8** %buffer, align 8, !dbg !1863
  call void @free(i8* %17) #7, !dbg !1864
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !1865
  %buffer7 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 13, !dbg !1866
  store i8* null, i8** %buffer7, align 8, !dbg !1867
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %t, align 8, !dbg !1868
  store %struct.archive_read_filter* %19, %struct.archive_read_filter** %f, align 8, !dbg !1869
  br label %while.cond, !dbg !1870

while.end:                                        ; preds = %while.cond
  %20 = load i32, i32* %r, align 4, !dbg !1872
  ret i32 %20, !dbg !1873
}

; Function Attrs: nounwind uwtable
define i64 @archive_read_header_position(%struct.archive* %_a) #0 !dbg !331 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1874, metadata !401), !dbg !1875
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !1876, metadata !401), !dbg !1877
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1878
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !1879
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !1877
  br label %do.body, !dbg !1880

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1881, metadata !401), !dbg !1883
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1884
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 32767, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.14, i32 0, i32 0)), !dbg !1884
  store i32 %call, i32* %magic_test, align 4, !dbg !1884
  %3 = load i32, i32* %magic_test, align 4, !dbg !1884
  %cmp = icmp eq i32 %3, -30, !dbg !1884
  br i1 %cmp, label %if.then, label %if.end, !dbg !1884

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !1886
  br label %return, !dbg !1886

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1889

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1891
  %header_position = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 9, !dbg !1892
  %5 = load i64, i64* %header_position, align 8, !dbg !1892
  store i64 %5, i64* %retval, align 8, !dbg !1893
  br label %return, !dbg !1893

return:                                           ; preds = %do.end, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !1894
  ret i64 %6, !dbg !1894
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_has_encrypted_entries(%struct.archive* %_a) #0 !dbg !334 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %format_supports_encryption = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1895, metadata !401), !dbg !1896
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !1897, metadata !401), !dbg !1898
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1899
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !1900
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !1898
  call void @llvm.dbg.declare(metadata i32* %format_supports_encryption, metadata !1901, metadata !401), !dbg !1902
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1903
  %call = call i32 @archive_read_format_capabilities(%struct.archive* %2), !dbg !1904
  %and = and i32 %call, 3, !dbg !1905
  store i32 %and, i32* %format_supports_encryption, align 4, !dbg !1902
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1906
  %tobool = icmp ne %struct.archive* %3, null, !dbg !1906
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !1908

lor.lhs.false:                                    ; preds = %entry
  %4 = load i32, i32* %format_supports_encryption, align 4, !dbg !1909
  %tobool1 = icmp ne i32 %4, 0, !dbg !1909
  br i1 %tobool1, label %if.end, label %if.then, !dbg !1911

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !1912
  br label %return, !dbg !1912

if.end:                                           ; preds = %lor.lhs.false
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1914
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 13, !dbg !1916
  %6 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1916
  %tobool2 = icmp ne %struct.archive_format_descriptor* %6, null, !dbg !1914
  br i1 %tobool2, label %land.lhs.true, label %if.end9, !dbg !1917

land.lhs.true:                                    ; preds = %if.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1918
  %format3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 13, !dbg !1920
  %8 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format3, align 8, !dbg !1920
  %has_encrypted_entries = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %8, i32 0, i32 10, !dbg !1921
  %9 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %has_encrypted_entries, align 8, !dbg !1921
  %tobool4 = icmp ne i32 (%struct.archive_read*)* %9, null, !dbg !1918
  br i1 %tobool4, label %if.then5, label %if.end9, !dbg !1922

if.then5:                                         ; preds = %land.lhs.true
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1923
  %format6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 13, !dbg !1925
  %11 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format6, align 8, !dbg !1925
  %has_encrypted_entries7 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %11, i32 0, i32 10, !dbg !1926
  %12 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %has_encrypted_entries7, align 8, !dbg !1926
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1927
  %call8 = call i32 %12(%struct.archive_read* %13), !dbg !1928
  store i32 %call8, i32* %retval, align 4, !dbg !1929
  br label %return, !dbg !1929

if.end9:                                          ; preds = %land.lhs.true, %if.end
  store i32 -1, i32* %retval, align 4, !dbg !1930
  br label %return, !dbg !1930

return:                                           ; preds = %if.end9, %if.then5, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !1931
  ret i32 %14, !dbg !1931
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_format_capabilities(%struct.archive* %_a) #0 !dbg !335 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1932, metadata !401), !dbg !1933
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !1934, metadata !401), !dbg !1935
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1936
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !1937
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !1935
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1938
  %tobool = icmp ne %struct.archive_read* %2, null, !dbg !1938
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !1940

land.lhs.true:                                    ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1941
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 13, !dbg !1943
  %4 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1943
  %tobool1 = icmp ne %struct.archive_format_descriptor* %4, null, !dbg !1941
  br i1 %tobool1, label %land.lhs.true2, label %if.end, !dbg !1944

land.lhs.true2:                                   ; preds = %land.lhs.true
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1945
  %format3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 13, !dbg !1947
  %6 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format3, align 8, !dbg !1947
  %format_capabilties = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %6, i32 0, i32 9, !dbg !1948
  %7 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %format_capabilties, align 8, !dbg !1948
  %tobool4 = icmp ne i32 (%struct.archive_read*)* %7, null, !dbg !1945
  br i1 %tobool4, label %if.then, label %if.end, !dbg !1949

if.then:                                          ; preds = %land.lhs.true2
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1950
  %format5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 13, !dbg !1952
  %9 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format5, align 8, !dbg !1952
  %format_capabilties6 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %9, i32 0, i32 9, !dbg !1953
  %10 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %format_capabilties6, align 8, !dbg !1953
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !1954
  %call = call i32 %10(%struct.archive_read* %11), !dbg !1955
  store i32 %call, i32* %retval, align 4, !dbg !1956
  br label %return, !dbg !1956

if.end:                                           ; preds = %land.lhs.true2, %land.lhs.true, %entry
  store i32 0, i32* %retval, align 4, !dbg !1957
  br label %return, !dbg !1957

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1958
  ret i32 %12, !dbg !1958
}

; Function Attrs: nounwind uwtable
define i64 @archive_read_data(%struct.archive* %_a, i8* %buff, i64 %s) #0 !dbg !336 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %a = alloca %struct.archive*, align 8
  %dest = alloca i8*, align 8
  %read_buf = alloca i8*, align 8
  %bytes_read = alloca i64, align 8
  %len = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1959, metadata !401), !dbg !1960
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1961, metadata !401), !dbg !1962
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !1963, metadata !401), !dbg !1964
  call void @llvm.dbg.declare(metadata %struct.archive** %a, metadata !1965, metadata !401), !dbg !1966
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1967
  store %struct.archive* %0, %struct.archive** %a, align 8, !dbg !1966
  call void @llvm.dbg.declare(metadata i8** %dest, metadata !1968, metadata !401), !dbg !1969
  call void @llvm.dbg.declare(metadata i8** %read_buf, metadata !1970, metadata !401), !dbg !1971
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !1972, metadata !401), !dbg !1973
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1974, metadata !401), !dbg !1975
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1976, metadata !401), !dbg !1977
  store i64 0, i64* %bytes_read, align 8, !dbg !1978
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !1979
  store i8* %1, i8** %dest, align 8, !dbg !1980
  br label %while.cond, !dbg !1981

while.cond:                                       ; preds = %if.end54, %entry
  %2 = load i64, i64* %s.addr, align 8, !dbg !1982
  %cmp = icmp ugt i64 %2, 0, !dbg !1984
  br i1 %cmp, label %while.body, label %while.end, !dbg !1985

while.body:                                       ; preds = %while.cond
  %3 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !1986
  %read_data_remaining = getelementptr inbounds %struct.archive, %struct.archive* %3, i32 0, i32 18, !dbg !1989
  %4 = load i64, i64* %read_data_remaining, align 8, !dbg !1989
  %cmp1 = icmp eq i64 %4, 0, !dbg !1990
  br i1 %cmp1, label %if.then, label %if.end9, !dbg !1991

if.then:                                          ; preds = %while.body
  %5 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !1992
  %read_data_block = getelementptr inbounds %struct.archive, %struct.archive* %5, i32 0, i32 15, !dbg !1994
  %6 = load i8*, i8** %read_data_block, align 8, !dbg !1994
  store i8* %6, i8** %read_buf, align 8, !dbg !1995
  %7 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !1996
  %read_data_is_posix_read = getelementptr inbounds %struct.archive, %struct.archive* %7, i32 0, i32 19, !dbg !1997
  store i8 1, i8* %read_data_is_posix_read, align 8, !dbg !1998
  %8 = load i64, i64* %s.addr, align 8, !dbg !1999
  %9 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2000
  %read_data_requested = getelementptr inbounds %struct.archive, %struct.archive* %9, i32 0, i32 20, !dbg !2001
  store i64 %8, i64* %read_data_requested, align 8, !dbg !2002
  %10 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2003
  %11 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2004
  %read_data_remaining2 = getelementptr inbounds %struct.archive, %struct.archive* %11, i32 0, i32 18, !dbg !2005
  %12 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2006
  %read_data_offset = getelementptr inbounds %struct.archive, %struct.archive* %12, i32 0, i32 16, !dbg !2007
  %call = call i32 @archive_read_data_block(%struct.archive* %10, i8** %read_buf, i64* %read_data_remaining2, i64* %read_data_offset), !dbg !2008
  store i32 %call, i32* %r, align 4, !dbg !2009
  %13 = load i8*, i8** %read_buf, align 8, !dbg !2010
  %14 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2011
  %read_data_block3 = getelementptr inbounds %struct.archive, %struct.archive* %14, i32 0, i32 15, !dbg !2012
  store i8* %13, i8** %read_data_block3, align 8, !dbg !2013
  %15 = load i32, i32* %r, align 4, !dbg !2014
  %cmp4 = icmp eq i32 %15, 1, !dbg !2016
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !2017

if.then5:                                         ; preds = %if.then
  %16 = load i64, i64* %bytes_read, align 8, !dbg !2018
  store i64 %16, i64* %retval, align 8, !dbg !2019
  br label %return, !dbg !2019

if.end:                                           ; preds = %if.then
  %17 = load i32, i32* %r, align 4, !dbg !2020
  %cmp6 = icmp slt i32 %17, 0, !dbg !2022
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2023

if.then7:                                         ; preds = %if.end
  %18 = load i32, i32* %r, align 4, !dbg !2024
  %conv = sext i32 %18 to i64, !dbg !2025
  store i64 %conv, i64* %retval, align 8, !dbg !2026
  br label %return, !dbg !2026

if.end8:                                          ; preds = %if.end
  br label %if.end9, !dbg !2027

if.end9:                                          ; preds = %if.end8, %while.body
  %19 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2028
  %read_data_offset10 = getelementptr inbounds %struct.archive, %struct.archive* %19, i32 0, i32 16, !dbg !2030
  %20 = load i64, i64* %read_data_offset10, align 8, !dbg !2030
  %21 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2031
  %read_data_output_offset = getelementptr inbounds %struct.archive, %struct.archive* %21, i32 0, i32 17, !dbg !2032
  %22 = load i64, i64* %read_data_output_offset, align 8, !dbg !2032
  %cmp11 = icmp slt i64 %20, %22, !dbg !2033
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !2034

if.then13:                                        ; preds = %if.end9
  %23 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2035
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %23, i32 84, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.15, i32 0, i32 0)), !dbg !2037
  store i64 -10, i64* %retval, align 8, !dbg !2038
  br label %return, !dbg !2038

if.end14:                                         ; preds = %if.end9
  %24 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2039
  %read_data_output_offset15 = getelementptr inbounds %struct.archive, %struct.archive* %24, i32 0, i32 17, !dbg !2041
  %25 = load i64, i64* %read_data_output_offset15, align 8, !dbg !2041
  %26 = load i64, i64* %s.addr, align 8, !dbg !2042
  %add = add nsw i64 %25, %26, !dbg !2043
  %27 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2044
  %read_data_offset16 = getelementptr inbounds %struct.archive, %struct.archive* %27, i32 0, i32 16, !dbg !2045
  %28 = load i64, i64* %read_data_offset16, align 8, !dbg !2045
  %cmp17 = icmp slt i64 %add, %28, !dbg !2046
  br i1 %cmp17, label %if.then19, label %if.else, !dbg !2047

if.then19:                                        ; preds = %if.end14
  %29 = load i64, i64* %s.addr, align 8, !dbg !2048
  store i64 %29, i64* %len, align 8, !dbg !2050
  br label %if.end29, !dbg !2051

if.else:                                          ; preds = %if.end14
  %30 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2052
  %read_data_output_offset20 = getelementptr inbounds %struct.archive, %struct.archive* %30, i32 0, i32 17, !dbg !2055
  %31 = load i64, i64* %read_data_output_offset20, align 8, !dbg !2055
  %32 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2056
  %read_data_offset21 = getelementptr inbounds %struct.archive, %struct.archive* %32, i32 0, i32 16, !dbg !2057
  %33 = load i64, i64* %read_data_offset21, align 8, !dbg !2057
  %cmp22 = icmp slt i64 %31, %33, !dbg !2058
  br i1 %cmp22, label %if.then24, label %if.else27, !dbg !2052

if.then24:                                        ; preds = %if.else
  %34 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2059
  %read_data_offset25 = getelementptr inbounds %struct.archive, %struct.archive* %34, i32 0, i32 16, !dbg !2061
  %35 = load i64, i64* %read_data_offset25, align 8, !dbg !2061
  %36 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2062
  %read_data_output_offset26 = getelementptr inbounds %struct.archive, %struct.archive* %36, i32 0, i32 17, !dbg !2063
  %37 = load i64, i64* %read_data_output_offset26, align 8, !dbg !2063
  %sub = sub nsw i64 %35, %37, !dbg !2064
  store i64 %sub, i64* %len, align 8, !dbg !2065
  br label %if.end28, !dbg !2066

if.else27:                                        ; preds = %if.else
  store i64 0, i64* %len, align 8, !dbg !2067
  br label %if.end28

if.end28:                                         ; preds = %if.else27, %if.then24
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.then19
  %38 = load i8*, i8** %dest, align 8, !dbg !2068
  %39 = load i64, i64* %len, align 8, !dbg !2069
  call void @llvm.memset.p0i8.i64(i8* %38, i8 0, i64 %39, i32 1, i1 false), !dbg !2070
  %40 = load i64, i64* %len, align 8, !dbg !2071
  %41 = load i64, i64* %s.addr, align 8, !dbg !2072
  %sub30 = sub i64 %41, %40, !dbg !2072
  store i64 %sub30, i64* %s.addr, align 8, !dbg !2072
  %42 = load i64, i64* %len, align 8, !dbg !2073
  %43 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2074
  %read_data_output_offset31 = getelementptr inbounds %struct.archive, %struct.archive* %43, i32 0, i32 17, !dbg !2075
  %44 = load i64, i64* %read_data_output_offset31, align 8, !dbg !2076
  %add32 = add i64 %44, %42, !dbg !2076
  store i64 %add32, i64* %read_data_output_offset31, align 8, !dbg !2076
  %45 = load i64, i64* %len, align 8, !dbg !2077
  %46 = load i8*, i8** %dest, align 8, !dbg !2078
  %add.ptr = getelementptr inbounds i8, i8* %46, i64 %45, !dbg !2078
  store i8* %add.ptr, i8** %dest, align 8, !dbg !2078
  %47 = load i64, i64* %len, align 8, !dbg !2079
  %48 = load i64, i64* %bytes_read, align 8, !dbg !2080
  %add33 = add i64 %48, %47, !dbg !2080
  store i64 %add33, i64* %bytes_read, align 8, !dbg !2080
  %49 = load i64, i64* %s.addr, align 8, !dbg !2081
  %cmp34 = icmp ugt i64 %49, 0, !dbg !2083
  br i1 %cmp34, label %if.then36, label %if.end54, !dbg !2084

if.then36:                                        ; preds = %if.end29
  %50 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2085
  %read_data_remaining37 = getelementptr inbounds %struct.archive, %struct.archive* %50, i32 0, i32 18, !dbg !2087
  %51 = load i64, i64* %read_data_remaining37, align 8, !dbg !2087
  store i64 %51, i64* %len, align 8, !dbg !2088
  %52 = load i64, i64* %len, align 8, !dbg !2089
  %53 = load i64, i64* %s.addr, align 8, !dbg !2091
  %cmp38 = icmp ugt i64 %52, %53, !dbg !2092
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !2093

if.then40:                                        ; preds = %if.then36
  %54 = load i64, i64* %s.addr, align 8, !dbg !2094
  store i64 %54, i64* %len, align 8, !dbg !2095
  br label %if.end41, !dbg !2096

if.end41:                                         ; preds = %if.then40, %if.then36
  %55 = load i8*, i8** %dest, align 8, !dbg !2097
  %56 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2098
  %read_data_block42 = getelementptr inbounds %struct.archive, %struct.archive* %56, i32 0, i32 15, !dbg !2099
  %57 = load i8*, i8** %read_data_block42, align 8, !dbg !2099
  %58 = load i64, i64* %len, align 8, !dbg !2100
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %55, i8* %57, i64 %58, i32 1, i1 false), !dbg !2101
  %59 = load i64, i64* %len, align 8, !dbg !2102
  %60 = load i64, i64* %s.addr, align 8, !dbg !2103
  %sub43 = sub i64 %60, %59, !dbg !2103
  store i64 %sub43, i64* %s.addr, align 8, !dbg !2103
  %61 = load i64, i64* %len, align 8, !dbg !2104
  %62 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2105
  %read_data_block44 = getelementptr inbounds %struct.archive, %struct.archive* %62, i32 0, i32 15, !dbg !2106
  %63 = load i8*, i8** %read_data_block44, align 8, !dbg !2107
  %add.ptr45 = getelementptr inbounds i8, i8* %63, i64 %61, !dbg !2107
  store i8* %add.ptr45, i8** %read_data_block44, align 8, !dbg !2107
  %64 = load i64, i64* %len, align 8, !dbg !2108
  %65 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2109
  %read_data_remaining46 = getelementptr inbounds %struct.archive, %struct.archive* %65, i32 0, i32 18, !dbg !2110
  %66 = load i64, i64* %read_data_remaining46, align 8, !dbg !2111
  %sub47 = sub i64 %66, %64, !dbg !2111
  store i64 %sub47, i64* %read_data_remaining46, align 8, !dbg !2111
  %67 = load i64, i64* %len, align 8, !dbg !2112
  %68 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2113
  %read_data_output_offset48 = getelementptr inbounds %struct.archive, %struct.archive* %68, i32 0, i32 17, !dbg !2114
  %69 = load i64, i64* %read_data_output_offset48, align 8, !dbg !2115
  %add49 = add i64 %69, %67, !dbg !2115
  store i64 %add49, i64* %read_data_output_offset48, align 8, !dbg !2115
  %70 = load i64, i64* %len, align 8, !dbg !2116
  %71 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2117
  %read_data_offset50 = getelementptr inbounds %struct.archive, %struct.archive* %71, i32 0, i32 16, !dbg !2118
  %72 = load i64, i64* %read_data_offset50, align 8, !dbg !2119
  %add51 = add i64 %72, %70, !dbg !2119
  store i64 %add51, i64* %read_data_offset50, align 8, !dbg !2119
  %73 = load i64, i64* %len, align 8, !dbg !2120
  %74 = load i8*, i8** %dest, align 8, !dbg !2121
  %add.ptr52 = getelementptr inbounds i8, i8* %74, i64 %73, !dbg !2121
  store i8* %add.ptr52, i8** %dest, align 8, !dbg !2121
  %75 = load i64, i64* %len, align 8, !dbg !2122
  %76 = load i64, i64* %bytes_read, align 8, !dbg !2123
  %add53 = add i64 %76, %75, !dbg !2123
  store i64 %add53, i64* %bytes_read, align 8, !dbg !2123
  br label %if.end54, !dbg !2124

if.end54:                                         ; preds = %if.end41, %if.end29
  br label %while.cond, !dbg !2125

while.end:                                        ; preds = %while.cond
  %77 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2127
  %read_data_is_posix_read55 = getelementptr inbounds %struct.archive, %struct.archive* %77, i32 0, i32 19, !dbg !2128
  store i8 0, i8* %read_data_is_posix_read55, align 8, !dbg !2129
  %78 = load %struct.archive*, %struct.archive** %a, align 8, !dbg !2130
  %read_data_requested56 = getelementptr inbounds %struct.archive, %struct.archive* %78, i32 0, i32 20, !dbg !2131
  store i64 0, i64* %read_data_requested56, align 8, !dbg !2132
  %79 = load i64, i64* %bytes_read, align 8, !dbg !2133
  store i64 %79, i64* %retval, align 8, !dbg !2134
  br label %return, !dbg !2134

return:                                           ; preds = %while.end, %if.then13, %if.then7, %if.then5
  %80 = load i64, i64* %retval, align 8, !dbg !2135
  ret i64 %80, !dbg !2135
}

declare i32 @archive_read_data_block(%struct.archive*, i8**, i64*, i64*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define void @__archive_reset_read_data(%struct.archive* %a) #0 !dbg !339 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !2136, metadata !401), !dbg !2137
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2138
  %read_data_output_offset = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 17, !dbg !2139
  store i64 0, i64* %read_data_output_offset, align 8, !dbg !2140
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2141
  %read_data_remaining = getelementptr inbounds %struct.archive, %struct.archive* %1, i32 0, i32 18, !dbg !2142
  store i64 0, i64* %read_data_remaining, align 8, !dbg !2143
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2144
  %read_data_is_posix_read = getelementptr inbounds %struct.archive, %struct.archive* %2, i32 0, i32 19, !dbg !2145
  store i8 0, i8* %read_data_is_posix_read, align 8, !dbg !2146
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2147
  %read_data_requested = getelementptr inbounds %struct.archive, %struct.archive* %3, i32 0, i32 20, !dbg !2148
  store i64 0, i64* %read_data_requested, align 8, !dbg !2149
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2150
  %read_data_block = getelementptr inbounds %struct.archive, %struct.archive* %4, i32 0, i32 15, !dbg !2151
  store i8* null, i8** %read_data_block, align 8, !dbg !2152
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !2153
  %read_data_offset = getelementptr inbounds %struct.archive, %struct.archive* %5, i32 0, i32 16, !dbg !2154
  store i64 0, i64* %read_data_offset, align 8, !dbg !2155
  ret void, !dbg !2156
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_data_skip(%struct.archive* %_a) #0 !dbg !342 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %r = alloca i32, align 4
  %buff = alloca i8*, align 8
  %size = alloca i64, align 8
  %offset = alloca i64, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2157, metadata !401), !dbg !2158
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !2159, metadata !401), !dbg !2160
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2161
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !2162
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !2160
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2163, metadata !401), !dbg !2164
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !2165, metadata !401), !dbg !2166
  call void @llvm.dbg.declare(metadata i64* %size, metadata !2167, metadata !401), !dbg !2168
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !2169, metadata !401), !dbg !2170
  br label %do.body, !dbg !2171

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2172, metadata !401), !dbg !2174
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2175
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 4, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.16, i32 0, i32 0)), !dbg !2175
  store i32 %call, i32* %magic_test, align 4, !dbg !2175
  %3 = load i32, i32* %magic_test, align 4, !dbg !2175
  %cmp = icmp eq i32 %3, -30, !dbg !2175
  br i1 %cmp, label %if.then, label %if.end, !dbg !2175

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2177
  br label %return, !dbg !2177

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2180

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2182
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 13, !dbg !2184
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !2184
  %read_data_skip = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 6, !dbg !2185
  %6 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %read_data_skip, align 8, !dbg !2185
  %cmp1 = icmp ne i32 (%struct.archive_read*)* %6, null, !dbg !2186
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !2187

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2188
  %format3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 13, !dbg !2189
  %8 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format3, align 8, !dbg !2189
  %read_data_skip4 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %8, i32 0, i32 6, !dbg !2190
  %9 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %read_data_skip4, align 8, !dbg !2190
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2191
  %call5 = call i32 %9(%struct.archive_read* %10), !dbg !2192
  store i32 %call5, i32* %r, align 4, !dbg !2193
  br label %if.end8, !dbg !2194

if.else:                                          ; preds = %do.end
  br label %while.cond, !dbg !2195

while.cond:                                       ; preds = %while.body, %if.else
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2197
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !2199
  %call6 = call i32 @archive_read_data_block(%struct.archive* %archive, i8** %buff, i64* %size, i64* %offset), !dbg !2200
  store i32 %call6, i32* %r, align 4, !dbg !2201
  %cmp7 = icmp eq i32 %call6, 0, !dbg !2202
  br i1 %cmp7, label %while.body, label %while.end, !dbg !2203

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !2204

while.end:                                        ; preds = %while.cond
  br label %if.end8

if.end8:                                          ; preds = %while.end, %if.then2
  %12 = load i32, i32* %r, align 4, !dbg !2206
  %cmp9 = icmp eq i32 %12, 1, !dbg !2208
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !2209

if.then10:                                        ; preds = %if.end8
  store i32 0, i32* %r, align 4, !dbg !2210
  br label %if.end11, !dbg !2211

if.end11:                                         ; preds = %if.then10, %if.end8
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2212
  %archive12 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !2213
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 1, !dbg !2214
  store i32 2, i32* %state, align 4, !dbg !2215
  %14 = load i32, i32* %r, align 4, !dbg !2216
  store i32 %14, i32* %retval, align 4, !dbg !2217
  br label %return, !dbg !2217

return:                                           ; preds = %if.end11, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !2218
  ret i32 %15, !dbg !2218
}

; Function Attrs: nounwind uwtable
define i64 @archive_seek_data(%struct.archive* %_a, i64 %offset, i32 %whence) #0 !dbg !343 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2219, metadata !401), !dbg !2220
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !2221, metadata !401), !dbg !2222
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !2223, metadata !401), !dbg !2224
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !2225, metadata !401), !dbg !2226
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2227
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !2228
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !2226
  br label %do.body, !dbg !2229

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2230, metadata !401), !dbg !2232
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2233
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 4, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.17, i32 0, i32 0)), !dbg !2233
  store i32 %call, i32* %magic_test, align 4, !dbg !2233
  %3 = load i32, i32* %magic_test, align 4, !dbg !2233
  %cmp = icmp eq i32 %3, -30, !dbg !2233
  br i1 %cmp, label %if.then, label %if.end, !dbg !2233

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !2235
  br label %return, !dbg !2235

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2238

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2240
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 13, !dbg !2242
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !2242
  %seek_data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 7, !dbg !2243
  %6 = load i64 (%struct.archive_read*, i64, i32)*, i64 (%struct.archive_read*, i64, i32)** %seek_data, align 8, !dbg !2243
  %cmp1 = icmp eq i64 (%struct.archive_read*, i64, i32)* %6, null, !dbg !2244
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2245

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2246
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !2248
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.18, i32 0, i32 0)), !dbg !2249
  store i64 -30, i64* %retval, align 8, !dbg !2250
  br label %return, !dbg !2250

if.end3:                                          ; preds = %do.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2251
  %format4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 13, !dbg !2252
  %9 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format4, align 8, !dbg !2252
  %seek_data5 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %9, i32 0, i32 7, !dbg !2253
  %10 = load i64 (%struct.archive_read*, i64, i32)*, i64 (%struct.archive_read*, i64, i32)** %seek_data5, align 8, !dbg !2253
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !2254
  %12 = load i64, i64* %offset.addr, align 8, !dbg !2255
  %13 = load i32, i32* %whence.addr, align 4, !dbg !2256
  %call6 = call i64 %10(%struct.archive_read* %11, i64 %12, i32 %13), !dbg !2257
  store i64 %call6, i64* %retval, align 8, !dbg !2258
  br label %return, !dbg !2258

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %14 = load i64, i64* %retval, align 8, !dbg !2259
  ret i64 %14, !dbg !2259
}

; Function Attrs: nounwind uwtable
define void @__archive_read_free_filters(%struct.archive_read* %a) #0 !dbg !346 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %t = alloca %struct.archive_read_filter*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2260, metadata !401), !dbg !2261
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2262
  %call = call i32 @close_filters(%struct.archive_read* %0), !dbg !2263
  br label %while.cond, !dbg !2264

while.cond:                                       ; preds = %while.body, %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2265
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 7, !dbg !2267
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !2267
  %cmp = icmp ne %struct.archive_read_filter* %2, null, !dbg !2268
  br i1 %cmp, label %while.body, label %while.end, !dbg !2269

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %t, metadata !2270, metadata !401), !dbg !2272
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2273
  %filter1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 7, !dbg !2274
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter1, align 8, !dbg !2274
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %4, i32 0, i32 2, !dbg !2275
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !2275
  store %struct.archive_read_filter* %5, %struct.archive_read_filter** %t, align 8, !dbg !2272
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2276
  %filter2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 7, !dbg !2277
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter2, align 8, !dbg !2277
  %8 = bitcast %struct.archive_read_filter* %7 to i8*, !dbg !2276
  call void @free(i8* %8) #7, !dbg !2278
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %t, align 8, !dbg !2279
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2280
  %filter3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 7, !dbg !2281
  store %struct.archive_read_filter* %9, %struct.archive_read_filter** %filter3, align 8, !dbg !2282
  br label %while.cond, !dbg !2283

while.end:                                        ; preds = %while.cond
  ret void, !dbg !2285
}

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @__archive_read_register_format(%struct.archive_read* %a, i8* %format_data, i8* %name, i32 (%struct.archive_read*, i32)* %bid, i32 (%struct.archive_read*, i8*, i8*)* %options, i32 (%struct.archive_read*, %struct.archive_entry*)* %read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* %read_data, i32 (%struct.archive_read*)* %read_data_skip, i64 (%struct.archive_read*, i64, i32)* %seek_data, i32 (%struct.archive_read*)* %cleanup, i32 (%struct.archive_read*)* %format_capabilities, i32 (%struct.archive_read*)* %has_encrypted_entries) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %format_data.addr = alloca i8*, align 8
  %name.addr = alloca i8*, align 8
  %bid.addr = alloca i32 (%struct.archive_read*, i32)*, align 8
  %options.addr = alloca i32 (%struct.archive_read*, i8*, i8*)*, align 8
  %read_header.addr = alloca i32 (%struct.archive_read*, %struct.archive_entry*)*, align 8
  %read_data.addr = alloca i32 (%struct.archive_read*, i8**, i64*, i64*)*, align 8
  %read_data_skip.addr = alloca i32 (%struct.archive_read*)*, align 8
  %seek_data.addr = alloca i64 (%struct.archive_read*, i64, i32)*, align 8
  %cleanup.addr = alloca i32 (%struct.archive_read*)*, align 8
  %format_capabilities.addr = alloca i32 (%struct.archive_read*)*, align 8
  %has_encrypted_entries.addr = alloca i32 (%struct.archive_read*)*, align 8
  %i = alloca i32, align 4
  %number_slots = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2286, metadata !401), !dbg !2287
  store i8* %format_data, i8** %format_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format_data.addr, metadata !2288, metadata !401), !dbg !2289
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2290, metadata !401), !dbg !2291
  store i32 (%struct.archive_read*, i32)* %bid, i32 (%struct.archive_read*, i32)** %bid.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*, i32)** %bid.addr, metadata !2292, metadata !401), !dbg !2293
  store i32 (%struct.archive_read*, i8*, i8*)* %options, i32 (%struct.archive_read*, i8*, i8*)** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*, i8*, i8*)** %options.addr, metadata !2294, metadata !401), !dbg !2295
  store i32 (%struct.archive_read*, %struct.archive_entry*)* %read_header, i32 (%struct.archive_read*, %struct.archive_entry*)** %read_header.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*, %struct.archive_entry*)** %read_header.addr, metadata !2296, metadata !401), !dbg !2297
  store i32 (%struct.archive_read*, i8**, i64*, i64*)* %read_data, i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data.addr, metadata !2298, metadata !401), !dbg !2299
  store i32 (%struct.archive_read*)* %read_data_skip, i32 (%struct.archive_read*)** %read_data_skip.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*)** %read_data_skip.addr, metadata !2300, metadata !401), !dbg !2301
  store i64 (%struct.archive_read*, i64, i32)* %seek_data, i64 (%struct.archive_read*, i64, i32)** %seek_data.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (%struct.archive_read*, i64, i32)** %seek_data.addr, metadata !2302, metadata !401), !dbg !2303
  store i32 (%struct.archive_read*)* %cleanup, i32 (%struct.archive_read*)** %cleanup.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*)** %cleanup.addr, metadata !2304, metadata !401), !dbg !2305
  store i32 (%struct.archive_read*)* %format_capabilities, i32 (%struct.archive_read*)** %format_capabilities.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*)** %format_capabilities.addr, metadata !2306, metadata !401), !dbg !2307
  store i32 (%struct.archive_read*)* %has_encrypted_entries, i32 (%struct.archive_read*)** %has_encrypted_entries.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_read*)** %has_encrypted_entries.addr, metadata !2308, metadata !401), !dbg !2309
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2310, metadata !401), !dbg !2311
  call void @llvm.dbg.declare(metadata i32* %number_slots, metadata !2312, metadata !401), !dbg !2313
  br label %do.body, !dbg !2314

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2315, metadata !401), !dbg !2317
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2318
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !2318
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.19, i32 0, i32 0)), !dbg !2318
  store i32 %call, i32* %magic_test, align 4, !dbg !2318
  %1 = load i32, i32* %magic_test, align 4, !dbg !2318
  %cmp = icmp eq i32 %1, -30, !dbg !2318
  br i1 %cmp, label %if.then, label %if.end, !dbg !2318

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2320
  br label %return, !dbg !2320

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2323

do.end:                                           ; preds = %if.end
  store i32 16, i32* %number_slots, align 4, !dbg !2325
  store i32 0, i32* %i, align 4, !dbg !2326
  br label %for.cond, !dbg !2328

for.cond:                                         ; preds = %for.inc, %do.end
  %2 = load i32, i32* %i, align 4, !dbg !2329
  %3 = load i32, i32* %number_slots, align 4, !dbg !2332
  %cmp1 = icmp slt i32 %2, %3, !dbg !2333
  br i1 %cmp1, label %for.body, label %for.end, !dbg !2334

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !2335
  %idxprom = sext i32 %4 to i64, !dbg !2338
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2338
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 12, !dbg !2339
  %arrayidx = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 %idxprom, !dbg !2338
  %bid2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx, i32 0, i32 2, !dbg !2340
  %6 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid2, align 8, !dbg !2340
  %7 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid.addr, align 8, !dbg !2341
  %cmp3 = icmp eq i32 (%struct.archive_read*, i32)* %6, %7, !dbg !2342
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2343

if.then4:                                         ; preds = %for.body
  store i32 -20, i32* %retval, align 4, !dbg !2344
  br label %return, !dbg !2344

if.end5:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !2345
  %idxprom6 = sext i32 %8 to i64, !dbg !2347
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2347
  %formats7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 12, !dbg !2348
  %arrayidx8 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats7, i64 0, i64 %idxprom6, !dbg !2347
  %bid9 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx8, i32 0, i32 2, !dbg !2349
  %10 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid9, align 8, !dbg !2349
  %cmp10 = icmp eq i32 (%struct.archive_read*, i32)* %10, null, !dbg !2350
  br i1 %cmp10, label %if.then11, label %if.end54, !dbg !2351

if.then11:                                        ; preds = %if.end5
  %11 = load i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i32)** %bid.addr, align 8, !dbg !2352
  %12 = load i32, i32* %i, align 4, !dbg !2354
  %idxprom12 = sext i32 %12 to i64, !dbg !2355
  %13 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2355
  %formats13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 12, !dbg !2356
  %arrayidx14 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats13, i64 0, i64 %idxprom12, !dbg !2355
  %bid15 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx14, i32 0, i32 2, !dbg !2357
  store i32 (%struct.archive_read*, i32)* %11, i32 (%struct.archive_read*, i32)** %bid15, align 8, !dbg !2358
  %14 = load i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, i8*, i8*)** %options.addr, align 8, !dbg !2359
  %15 = load i32, i32* %i, align 4, !dbg !2360
  %idxprom16 = sext i32 %15 to i64, !dbg !2361
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2361
  %formats17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 12, !dbg !2362
  %arrayidx18 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats17, i64 0, i64 %idxprom16, !dbg !2361
  %options19 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx18, i32 0, i32 3, !dbg !2363
  store i32 (%struct.archive_read*, i8*, i8*)* %14, i32 (%struct.archive_read*, i8*, i8*)** %options19, align 8, !dbg !2364
  %17 = load i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, %struct.archive_entry*)** %read_header.addr, align 8, !dbg !2365
  %18 = load i32, i32* %i, align 4, !dbg !2366
  %idxprom20 = sext i32 %18 to i64, !dbg !2367
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2367
  %formats21 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 12, !dbg !2368
  %arrayidx22 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats21, i64 0, i64 %idxprom20, !dbg !2367
  %read_header23 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx22, i32 0, i32 4, !dbg !2369
  store i32 (%struct.archive_read*, %struct.archive_entry*)* %17, i32 (%struct.archive_read*, %struct.archive_entry*)** %read_header23, align 8, !dbg !2370
  %20 = load i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data.addr, align 8, !dbg !2371
  %21 = load i32, i32* %i, align 4, !dbg !2372
  %idxprom24 = sext i32 %21 to i64, !dbg !2373
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2373
  %formats25 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 12, !dbg !2374
  %arrayidx26 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats25, i64 0, i64 %idxprom24, !dbg !2373
  %read_data27 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx26, i32 0, i32 5, !dbg !2375
  store i32 (%struct.archive_read*, i8**, i64*, i64*)* %20, i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data27, align 8, !dbg !2376
  %23 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %read_data_skip.addr, align 8, !dbg !2377
  %24 = load i32, i32* %i, align 4, !dbg !2378
  %idxprom28 = sext i32 %24 to i64, !dbg !2379
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2379
  %formats29 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 12, !dbg !2380
  %arrayidx30 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats29, i64 0, i64 %idxprom28, !dbg !2379
  %read_data_skip31 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx30, i32 0, i32 6, !dbg !2381
  store i32 (%struct.archive_read*)* %23, i32 (%struct.archive_read*)** %read_data_skip31, align 8, !dbg !2382
  %26 = load i64 (%struct.archive_read*, i64, i32)*, i64 (%struct.archive_read*, i64, i32)** %seek_data.addr, align 8, !dbg !2383
  %27 = load i32, i32* %i, align 4, !dbg !2384
  %idxprom32 = sext i32 %27 to i64, !dbg !2385
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2385
  %formats33 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 12, !dbg !2386
  %arrayidx34 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats33, i64 0, i64 %idxprom32, !dbg !2385
  %seek_data35 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx34, i32 0, i32 7, !dbg !2387
  store i64 (%struct.archive_read*, i64, i32)* %26, i64 (%struct.archive_read*, i64, i32)** %seek_data35, align 8, !dbg !2388
  %29 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %cleanup.addr, align 8, !dbg !2389
  %30 = load i32, i32* %i, align 4, !dbg !2390
  %idxprom36 = sext i32 %30 to i64, !dbg !2391
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2391
  %formats37 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 12, !dbg !2392
  %arrayidx38 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats37, i64 0, i64 %idxprom36, !dbg !2391
  %cleanup39 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx38, i32 0, i32 8, !dbg !2393
  store i32 (%struct.archive_read*)* %29, i32 (%struct.archive_read*)** %cleanup39, align 8, !dbg !2394
  %32 = load i8*, i8** %format_data.addr, align 8, !dbg !2395
  %33 = load i32, i32* %i, align 4, !dbg !2396
  %idxprom40 = sext i32 %33 to i64, !dbg !2397
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2397
  %formats41 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %34, i32 0, i32 12, !dbg !2398
  %arrayidx42 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats41, i64 0, i64 %idxprom40, !dbg !2397
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx42, i32 0, i32 0, !dbg !2399
  store i8* %32, i8** %data, align 8, !dbg !2400
  %35 = load i8*, i8** %name.addr, align 8, !dbg !2401
  %36 = load i32, i32* %i, align 4, !dbg !2402
  %idxprom43 = sext i32 %36 to i64, !dbg !2403
  %37 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2403
  %formats44 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %37, i32 0, i32 12, !dbg !2404
  %arrayidx45 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats44, i64 0, i64 %idxprom43, !dbg !2403
  %name46 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx45, i32 0, i32 1, !dbg !2405
  store i8* %35, i8** %name46, align 8, !dbg !2406
  %38 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %format_capabilities.addr, align 8, !dbg !2407
  %39 = load i32, i32* %i, align 4, !dbg !2408
  %idxprom47 = sext i32 %39 to i64, !dbg !2409
  %40 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2409
  %formats48 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 12, !dbg !2410
  %arrayidx49 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats48, i64 0, i64 %idxprom47, !dbg !2409
  %format_capabilties = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx49, i32 0, i32 9, !dbg !2411
  store i32 (%struct.archive_read*)* %38, i32 (%struct.archive_read*)** %format_capabilties, align 8, !dbg !2412
  %41 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %has_encrypted_entries.addr, align 8, !dbg !2413
  %42 = load i32, i32* %i, align 4, !dbg !2414
  %idxprom50 = sext i32 %42 to i64, !dbg !2415
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2415
  %formats51 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 12, !dbg !2416
  %arrayidx52 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats51, i64 0, i64 %idxprom50, !dbg !2415
  %has_encrypted_entries53 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx52, i32 0, i32 10, !dbg !2417
  store i32 (%struct.archive_read*)* %41, i32 (%struct.archive_read*)** %has_encrypted_entries53, align 8, !dbg !2418
  store i32 0, i32* %retval, align 4, !dbg !2419
  br label %return, !dbg !2419

if.end54:                                         ; preds = %if.end5
  br label %for.inc, !dbg !2420

for.inc:                                          ; preds = %if.end54
  %44 = load i32, i32* %i, align 4, !dbg !2421
  %inc = add nsw i32 %44, 1, !dbg !2421
  store i32 %inc, i32* %i, align 4, !dbg !2421
  br label %for.cond, !dbg !2423

for.end:                                          ; preds = %for.cond
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2424
  %archive55 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %45, i32 0, i32 0, !dbg !2425
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive55, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.20, i32 0, i32 0)), !dbg !2426
  store i32 -30, i32* %retval, align 4, !dbg !2427
  br label %return, !dbg !2427

return:                                           ; preds = %for.end, %if.then11, %if.then4, %if.then
  %46 = load i32, i32* %retval, align 4, !dbg !2428
  ret i32 %46, !dbg !2428
}

; Function Attrs: nounwind uwtable
define i32 @__archive_read_get_bidder(%struct.archive_read* %a, %struct.archive_read_filter_bidder** %bidder) #0 !dbg !352 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %bidder.addr = alloca %struct.archive_read_filter_bidder**, align 8
  %i = alloca i32, align 4
  %number_slots = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2429, metadata !401), !dbg !2430
  store %struct.archive_read_filter_bidder** %bidder, %struct.archive_read_filter_bidder*** %bidder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder*** %bidder.addr, metadata !2431, metadata !401), !dbg !2432
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2433, metadata !401), !dbg !2434
  call void @llvm.dbg.declare(metadata i32* %number_slots, metadata !2435, metadata !401), !dbg !2436
  store i32 16, i32* %number_slots, align 4, !dbg !2437
  store i32 0, i32* %i, align 4, !dbg !2438
  br label %for.cond, !dbg !2440

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2441
  %1 = load i32, i32* %number_slots, align 4, !dbg !2444
  %cmp = icmp slt i32 %0, %1, !dbg !2445
  br i1 %cmp, label %for.body, label %for.end, !dbg !2446

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %i, align 4, !dbg !2447
  %idxprom = sext i32 %2 to i64, !dbg !2450
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2450
  %bidders = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 6, !dbg !2451
  %arrayidx = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders, i64 0, i64 %idxprom, !dbg !2450
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %arrayidx, i32 0, i32 2, !dbg !2452
  %4 = load i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !2452
  %cmp1 = icmp eq i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* %4, null, !dbg !2453
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2454

if.then:                                          ; preds = %for.body
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2455
  %bidders2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 6, !dbg !2457
  %arraydecay = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders2, i32 0, i32 0, !dbg !2455
  %6 = load i32, i32* %i, align 4, !dbg !2458
  %idx.ext = sext i32 %6 to i64, !dbg !2459
  %add.ptr = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %arraydecay, i64 %idx.ext, !dbg !2459
  %7 = bitcast %struct.archive_read_filter_bidder* %add.ptr to i8*, !dbg !2460
  call void @llvm.memset.p0i8.i64(i8* %7, i8 0, i64 48, i32 8, i1 false), !dbg !2460
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2461
  %bidders3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 6, !dbg !2462
  %arraydecay4 = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders3, i32 0, i32 0, !dbg !2461
  %9 = load i32, i32* %i, align 4, !dbg !2463
  %idx.ext5 = sext i32 %9 to i64, !dbg !2464
  %add.ptr6 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %arraydecay4, i64 %idx.ext5, !dbg !2464
  %10 = load %struct.archive_read_filter_bidder**, %struct.archive_read_filter_bidder*** %bidder.addr, align 8, !dbg !2465
  store %struct.archive_read_filter_bidder* %add.ptr6, %struct.archive_read_filter_bidder** %10, align 8, !dbg !2466
  store i32 0, i32* %retval, align 4, !dbg !2467
  br label %return, !dbg !2467

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !2468

for.inc:                                          ; preds = %if.end
  %11 = load i32, i32* %i, align 4, !dbg !2469
  %inc = add nsw i32 %11, 1, !dbg !2469
  store i32 %inc, i32* %i, align 4, !dbg !2469
  br label %for.cond, !dbg !2471

for.end:                                          ; preds = %for.cond
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2472
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !2473
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.21, i32 0, i32 0)), !dbg !2474
  store i32 -30, i32* %retval, align 4, !dbg !2475
  br label %return, !dbg !2475

return:                                           ; preds = %for.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2476
  ret i32 %13, !dbg !2476
}

; Function Attrs: nounwind uwtable
define i8* @__archive_read_ahead(%struct.archive_read* %a, i64 %min, i64* %avail) #0 !dbg !356 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %min.addr = alloca i64, align 8
  %avail.addr = alloca i64*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2477, metadata !401), !dbg !2478
  store i64 %min, i64* %min.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %min.addr, metadata !2479, metadata !401), !dbg !2480
  store i64* %avail, i64** %avail.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %avail.addr, metadata !2481, metadata !401), !dbg !2482
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2483
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 7, !dbg !2484
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !2484
  %2 = load i64, i64* %min.addr, align 8, !dbg !2485
  %3 = load i64*, i64** %avail.addr, align 8, !dbg !2486
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 %2, i64* %3), !dbg !2487
  ret i8* %call, !dbg !2488
}

; Function Attrs: nounwind uwtable
define i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %filter, i64 %min, i64* %avail) #0 !dbg !360 {
entry:
  %retval = alloca i8*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %min.addr = alloca i64, align 8
  %avail.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %tocopy = alloca i64, align 8
  %s = alloca i64, align 8
  %t = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !2489, metadata !401), !dbg !2490
  store i64 %min, i64* %min.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %min.addr, metadata !2491, metadata !401), !dbg !2492
  store i64* %avail, i64** %avail.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %avail.addr, metadata !2493, metadata !401), !dbg !2494
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !2495, metadata !401), !dbg !2496
  call void @llvm.dbg.declare(metadata i64* %tocopy, metadata !2497, metadata !401), !dbg !2498
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2499
  %fatal = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 23, !dbg !2501
  %1 = load i8, i8* %fatal, align 2, !dbg !2501
  %tobool = icmp ne i8 %1, 0, !dbg !2499
  br i1 %tobool, label %if.then, label %if.end3, !dbg !2502

if.then:                                          ; preds = %entry
  %2 = load i64*, i64** %avail.addr, align 8, !dbg !2503
  %tobool1 = icmp ne i64* %2, null, !dbg !2503
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !2506

if.then2:                                         ; preds = %if.then
  %3 = load i64*, i64** %avail.addr, align 8, !dbg !2507
  store i64 -30, i64* %3, align 8, !dbg !2508
  br label %if.end, !dbg !2509

if.end:                                           ; preds = %if.then2, %if.then
  store i8* null, i8** %retval, align 8, !dbg !2510
  br label %return, !dbg !2510

if.end3:                                          ; preds = %entry
  br label %for.cond, !dbg !2511

for.cond:                                         ; preds = %if.end169, %if.then85, %if.end3
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2512
  %avail4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %4, i32 0, i32 16, !dbg !2517
  %5 = load i64, i64* %avail4, align 8, !dbg !2517
  %6 = load i64, i64* %min.addr, align 8, !dbg !2518
  %cmp = icmp uge i64 %5, %6, !dbg !2519
  br i1 %cmp, label %land.lhs.true, label %if.end12, !dbg !2520

land.lhs.true:                                    ; preds = %for.cond
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2521
  %avail5 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 16, !dbg !2523
  %8 = load i64, i64* %avail5, align 8, !dbg !2523
  %cmp6 = icmp ugt i64 %8, 0, !dbg !2524
  br i1 %cmp6, label %if.then7, label %if.end12, !dbg !2525

if.then7:                                         ; preds = %land.lhs.true
  %9 = load i64*, i64** %avail.addr, align 8, !dbg !2526
  %cmp8 = icmp ne i64* %9, null, !dbg !2529
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !2530

if.then9:                                         ; preds = %if.then7
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2531
  %avail10 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 16, !dbg !2532
  %11 = load i64, i64* %avail10, align 8, !dbg !2532
  %12 = load i64*, i64** %avail.addr, align 8, !dbg !2533
  store i64 %11, i64* %12, align 8, !dbg !2534
  br label %if.end11, !dbg !2535

if.end11:                                         ; preds = %if.then9, %if.then7
  %13 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2536
  %next = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %13, i32 0, i32 15, !dbg !2537
  %14 = load i8*, i8** %next, align 8, !dbg !2537
  store i8* %14, i8** %retval, align 8, !dbg !2538
  br label %return, !dbg !2538

if.end12:                                         ; preds = %land.lhs.true, %for.cond
  %15 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2539
  %client_total = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %15, i32 0, i32 18, !dbg !2541
  %16 = load i64, i64* %client_total, align 8, !dbg !2541
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2542
  %client_avail = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %17, i32 0, i32 20, !dbg !2543
  %18 = load i64, i64* %client_avail, align 8, !dbg !2543
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2544
  %avail13 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %19, i32 0, i32 16, !dbg !2545
  %20 = load i64, i64* %avail13, align 8, !dbg !2545
  %add = add i64 %18, %20, !dbg !2546
  %cmp14 = icmp uge i64 %16, %add, !dbg !2547
  br i1 %cmp14, label %land.lhs.true15, label %if.end32, !dbg !2548

land.lhs.true15:                                  ; preds = %if.end12
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2549
  %client_avail16 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %21, i32 0, i32 20, !dbg !2551
  %22 = load i64, i64* %client_avail16, align 8, !dbg !2551
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2552
  %avail17 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 16, !dbg !2553
  %24 = load i64, i64* %avail17, align 8, !dbg !2553
  %add18 = add i64 %22, %24, !dbg !2554
  %25 = load i64, i64* %min.addr, align 8, !dbg !2555
  %cmp19 = icmp uge i64 %add18, %25, !dbg !2556
  br i1 %cmp19, label %if.then20, label %if.end32, !dbg !2557

if.then20:                                        ; preds = %land.lhs.true15
  %26 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2559
  %avail21 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %26, i32 0, i32 16, !dbg !2561
  %27 = load i64, i64* %avail21, align 8, !dbg !2561
  %28 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2562
  %client_avail22 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %28, i32 0, i32 20, !dbg !2563
  %29 = load i64, i64* %client_avail22, align 8, !dbg !2564
  %add23 = add i64 %29, %27, !dbg !2564
  store i64 %add23, i64* %client_avail22, align 8, !dbg !2564
  %30 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2565
  %avail24 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %30, i32 0, i32 16, !dbg !2566
  %31 = load i64, i64* %avail24, align 8, !dbg !2566
  %32 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2567
  %client_next = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %32, i32 0, i32 19, !dbg !2568
  %33 = load i8*, i8** %client_next, align 8, !dbg !2569
  %idx.neg = sub i64 0, %31, !dbg !2569
  %add.ptr = getelementptr inbounds i8, i8* %33, i64 %idx.neg, !dbg !2569
  store i8* %add.ptr, i8** %client_next, align 8, !dbg !2569
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2570
  %avail25 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %34, i32 0, i32 16, !dbg !2571
  store i64 0, i64* %avail25, align 8, !dbg !2572
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2573
  %buffer = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %35, i32 0, i32 13, !dbg !2574
  %36 = load i8*, i8** %buffer, align 8, !dbg !2574
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2575
  %next26 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %37, i32 0, i32 15, !dbg !2576
  store i8* %36, i8** %next26, align 8, !dbg !2577
  %38 = load i64*, i64** %avail.addr, align 8, !dbg !2578
  %cmp27 = icmp ne i64* %38, null, !dbg !2580
  br i1 %cmp27, label %if.then28, label %if.end30, !dbg !2581

if.then28:                                        ; preds = %if.then20
  %39 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2582
  %client_avail29 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %39, i32 0, i32 20, !dbg !2583
  %40 = load i64, i64* %client_avail29, align 8, !dbg !2583
  %41 = load i64*, i64** %avail.addr, align 8, !dbg !2584
  store i64 %40, i64* %41, align 8, !dbg !2585
  br label %if.end30, !dbg !2586

if.end30:                                         ; preds = %if.then28, %if.then20
  %42 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2587
  %client_next31 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %42, i32 0, i32 19, !dbg !2588
  %43 = load i8*, i8** %client_next31, align 8, !dbg !2588
  store i8* %43, i8** %retval, align 8, !dbg !2589
  br label %return, !dbg !2589

if.end32:                                         ; preds = %land.lhs.true15, %if.end12
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2590
  %next33 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %44, i32 0, i32 15, !dbg !2592
  %45 = load i8*, i8** %next33, align 8, !dbg !2592
  %46 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2593
  %buffer34 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %46, i32 0, i32 13, !dbg !2594
  %47 = load i8*, i8** %buffer34, align 8, !dbg !2594
  %cmp35 = icmp ugt i8* %45, %47, !dbg !2595
  br i1 %cmp35, label %land.lhs.true36, label %if.end52, !dbg !2596

land.lhs.true36:                                  ; preds = %if.end32
  %48 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2597
  %next37 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %48, i32 0, i32 15, !dbg !2598
  %49 = load i8*, i8** %next37, align 8, !dbg !2598
  %50 = load i64, i64* %min.addr, align 8, !dbg !2599
  %add.ptr38 = getelementptr inbounds i8, i8* %49, i64 %50, !dbg !2600
  %51 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2601
  %buffer39 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %51, i32 0, i32 13, !dbg !2602
  %52 = load i8*, i8** %buffer39, align 8, !dbg !2602
  %53 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2603
  %buffer_size = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %53, i32 0, i32 14, !dbg !2604
  %54 = load i64, i64* %buffer_size, align 8, !dbg !2604
  %add.ptr40 = getelementptr inbounds i8, i8* %52, i64 %54, !dbg !2605
  %cmp41 = icmp ugt i8* %add.ptr38, %add.ptr40, !dbg !2606
  br i1 %cmp41, label %if.then42, label %if.end52, !dbg !2607

if.then42:                                        ; preds = %land.lhs.true36
  %55 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2608
  %avail43 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %55, i32 0, i32 16, !dbg !2611
  %56 = load i64, i64* %avail43, align 8, !dbg !2611
  %cmp44 = icmp ugt i64 %56, 0, !dbg !2612
  br i1 %cmp44, label %if.then45, label %if.end49, !dbg !2613

if.then45:                                        ; preds = %if.then42
  %57 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2614
  %buffer46 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %57, i32 0, i32 13, !dbg !2615
  %58 = load i8*, i8** %buffer46, align 8, !dbg !2615
  %59 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2616
  %next47 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %59, i32 0, i32 15, !dbg !2617
  %60 = load i8*, i8** %next47, align 8, !dbg !2617
  %61 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2618
  %avail48 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %61, i32 0, i32 16, !dbg !2619
  %62 = load i64, i64* %avail48, align 8, !dbg !2619
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %58, i8* %60, i64 %62, i32 1, i1 false), !dbg !2620
  br label %if.end49, !dbg !2620

if.end49:                                         ; preds = %if.then45, %if.then42
  %63 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2621
  %buffer50 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %63, i32 0, i32 13, !dbg !2622
  %64 = load i8*, i8** %buffer50, align 8, !dbg !2622
  %65 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2623
  %next51 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %65, i32 0, i32 15, !dbg !2624
  store i8* %64, i8** %next51, align 8, !dbg !2625
  br label %if.end52, !dbg !2626

if.end52:                                         ; preds = %if.end49, %land.lhs.true36, %if.end32
  %66 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2627
  %client_avail53 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %66, i32 0, i32 20, !dbg !2629
  %67 = load i64, i64* %client_avail53, align 8, !dbg !2629
  %cmp54 = icmp ule i64 %67, 0, !dbg !2630
  br i1 %cmp54, label %if.then55, label %if.else, !dbg !2631

if.then55:                                        ; preds = %if.end52
  %68 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2632
  %end_of_file = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %68, i32 0, i32 21, !dbg !2635
  %69 = load i8, i8* %end_of_file, align 8, !dbg !2635
  %tobool56 = icmp ne i8 %69, 0, !dbg !2632
  br i1 %tobool56, label %if.then57, label %if.end61, !dbg !2636

if.then57:                                        ; preds = %if.then55
  %70 = load i64*, i64** %avail.addr, align 8, !dbg !2637
  %cmp58 = icmp ne i64* %70, null, !dbg !2640
  br i1 %cmp58, label %if.then59, label %if.end60, !dbg !2641

if.then59:                                        ; preds = %if.then57
  %71 = load i64*, i64** %avail.addr, align 8, !dbg !2642
  store i64 0, i64* %71, align 8, !dbg !2643
  br label %if.end60, !dbg !2644

if.end60:                                         ; preds = %if.then59, %if.then57
  store i8* null, i8** %retval, align 8, !dbg !2645
  br label %return, !dbg !2645

if.end61:                                         ; preds = %if.then55
  %72 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2646
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %72, i32 0, i32 5, !dbg !2647
  %73 = load i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !2647
  %74 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2648
  %75 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2649
  %client_buff = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %75, i32 0, i32 17, !dbg !2650
  %call = call i64 %73(%struct.archive_read_filter* %74, i8** %client_buff), !dbg !2651
  store i64 %call, i64* %bytes_read, align 8, !dbg !2652
  %76 = load i64, i64* %bytes_read, align 8, !dbg !2653
  %cmp62 = icmp slt i64 %76, 0, !dbg !2655
  br i1 %cmp62, label %if.then63, label %if.end72, !dbg !2656

if.then63:                                        ; preds = %if.end61
  %77 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2657
  %client_avail64 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %77, i32 0, i32 20, !dbg !2659
  store i64 0, i64* %client_avail64, align 8, !dbg !2660
  %78 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2661
  %client_total65 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %78, i32 0, i32 18, !dbg !2662
  store i64 0, i64* %client_total65, align 8, !dbg !2663
  %79 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2664
  %client_buff66 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %79, i32 0, i32 17, !dbg !2665
  store i8* null, i8** %client_buff66, align 8, !dbg !2666
  %80 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2667
  %client_next67 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %80, i32 0, i32 19, !dbg !2668
  store i8* null, i8** %client_next67, align 8, !dbg !2669
  %81 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2670
  %fatal68 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %81, i32 0, i32 23, !dbg !2671
  store i8 1, i8* %fatal68, align 2, !dbg !2672
  %82 = load i64*, i64** %avail.addr, align 8, !dbg !2673
  %cmp69 = icmp ne i64* %82, null, !dbg !2675
  br i1 %cmp69, label %if.then70, label %if.end71, !dbg !2676

if.then70:                                        ; preds = %if.then63
  %83 = load i64*, i64** %avail.addr, align 8, !dbg !2677
  store i64 -30, i64* %83, align 8, !dbg !2678
  br label %if.end71, !dbg !2679

if.end71:                                         ; preds = %if.then70, %if.then63
  store i8* null, i8** %retval, align 8, !dbg !2680
  br label %return, !dbg !2680

if.end72:                                         ; preds = %if.end61
  %84 = load i64, i64* %bytes_read, align 8, !dbg !2681
  %cmp73 = icmp eq i64 %84, 0, !dbg !2683
  br i1 %cmp73, label %if.then74, label %if.end97, !dbg !2684

if.then74:                                        ; preds = %if.end72
  %85 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2685
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %85, i32 0, i32 3, !dbg !2688
  %86 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !2688
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %86, i32 0, i32 5, !dbg !2689
  %cursor = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 7, !dbg !2690
  %87 = load i32, i32* %cursor, align 4, !dbg !2690
  %88 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2691
  %archive75 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %88, i32 0, i32 3, !dbg !2692
  %89 = load %struct.archive_read*, %struct.archive_read** %archive75, align 8, !dbg !2692
  %client76 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %89, i32 0, i32 5, !dbg !2693
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client76, i32 0, i32 6, !dbg !2694
  %90 = load i32, i32* %nodes, align 8, !dbg !2694
  %sub = sub i32 %90, 1, !dbg !2695
  %cmp77 = icmp ne i32 %87, %sub, !dbg !2696
  br i1 %cmp77, label %if.then78, label %if.end87, !dbg !2697

if.then78:                                        ; preds = %if.then74
  %91 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2698
  %92 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2701
  %archive79 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %92, i32 0, i32 3, !dbg !2702
  %93 = load %struct.archive_read*, %struct.archive_read** %archive79, align 8, !dbg !2702
  %client80 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %93, i32 0, i32 5, !dbg !2703
  %cursor81 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client80, i32 0, i32 7, !dbg !2704
  %94 = load i32, i32* %cursor81, align 4, !dbg !2704
  %add82 = add i32 %94, 1, !dbg !2705
  %call83 = call i32 @client_switch_proxy(%struct.archive_read_filter* %91, i32 %add82), !dbg !2706
  %cmp84 = icmp eq i32 %call83, 0, !dbg !2707
  br i1 %cmp84, label %if.then85, label %if.end86, !dbg !2708

if.then85:                                        ; preds = %if.then78
  br label %for.cond, !dbg !2709

if.end86:                                         ; preds = %if.then78
  br label %if.end87, !dbg !2710

if.end87:                                         ; preds = %if.end86, %if.then74
  %95 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2711
  %client_avail88 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %95, i32 0, i32 20, !dbg !2712
  store i64 0, i64* %client_avail88, align 8, !dbg !2713
  %96 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2714
  %client_total89 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %96, i32 0, i32 18, !dbg !2715
  store i64 0, i64* %client_total89, align 8, !dbg !2716
  %97 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2717
  %client_buff90 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %97, i32 0, i32 17, !dbg !2718
  store i8* null, i8** %client_buff90, align 8, !dbg !2719
  %98 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2720
  %client_next91 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %98, i32 0, i32 19, !dbg !2721
  store i8* null, i8** %client_next91, align 8, !dbg !2722
  %99 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2723
  %end_of_file92 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %99, i32 0, i32 21, !dbg !2724
  store i8 1, i8* %end_of_file92, align 8, !dbg !2725
  %100 = load i64*, i64** %avail.addr, align 8, !dbg !2726
  %cmp93 = icmp ne i64* %100, null, !dbg !2728
  br i1 %cmp93, label %if.then94, label %if.end96, !dbg !2729

if.then94:                                        ; preds = %if.end87
  %101 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2730
  %avail95 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %101, i32 0, i32 16, !dbg !2731
  %102 = load i64, i64* %avail95, align 8, !dbg !2731
  %103 = load i64*, i64** %avail.addr, align 8, !dbg !2732
  store i64 %102, i64* %103, align 8, !dbg !2733
  br label %if.end96, !dbg !2734

if.end96:                                         ; preds = %if.then94, %if.end87
  store i8* null, i8** %retval, align 8, !dbg !2735
  br label %return, !dbg !2735

if.end97:                                         ; preds = %if.end72
  %104 = load i64, i64* %bytes_read, align 8, !dbg !2736
  %105 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2737
  %client_total98 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %105, i32 0, i32 18, !dbg !2738
  store i64 %104, i64* %client_total98, align 8, !dbg !2739
  %106 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2740
  %client_total99 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %106, i32 0, i32 18, !dbg !2741
  %107 = load i64, i64* %client_total99, align 8, !dbg !2741
  %108 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2742
  %client_avail100 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %108, i32 0, i32 20, !dbg !2743
  store i64 %107, i64* %client_avail100, align 8, !dbg !2744
  %109 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2745
  %client_buff101 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %109, i32 0, i32 17, !dbg !2746
  %110 = load i8*, i8** %client_buff101, align 8, !dbg !2746
  %111 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2747
  %client_next102 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %111, i32 0, i32 19, !dbg !2748
  store i8* %110, i8** %client_next102, align 8, !dbg !2749
  br label %if.end169, !dbg !2750

if.else:                                          ; preds = %if.end52
  %112 = load i64, i64* %min.addr, align 8, !dbg !2751
  %113 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2754
  %buffer_size103 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %113, i32 0, i32 14, !dbg !2755
  %114 = load i64, i64* %buffer_size103, align 8, !dbg !2755
  %cmp104 = icmp ugt i64 %112, %114, !dbg !2756
  br i1 %cmp104, label %if.then105, label %if.end140, !dbg !2757

if.then105:                                       ; preds = %if.else
  call void @llvm.dbg.declare(metadata i64* %s, metadata !2758, metadata !401), !dbg !2760
  call void @llvm.dbg.declare(metadata i64* %t, metadata !2761, metadata !401), !dbg !2762
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2763, metadata !401), !dbg !2764
  %115 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2765
  %buffer_size106 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %115, i32 0, i32 14, !dbg !2766
  %116 = load i64, i64* %buffer_size106, align 8, !dbg !2766
  store i64 %116, i64* %t, align 8, !dbg !2767
  store i64 %116, i64* %s, align 8, !dbg !2768
  %117 = load i64, i64* %s, align 8, !dbg !2769
  %cmp107 = icmp eq i64 %117, 0, !dbg !2771
  br i1 %cmp107, label %if.then108, label %if.end109, !dbg !2772

if.then108:                                       ; preds = %if.then105
  %118 = load i64, i64* %min.addr, align 8, !dbg !2773
  store i64 %118, i64* %s, align 8, !dbg !2774
  br label %if.end109, !dbg !2775

if.end109:                                        ; preds = %if.then108, %if.then105
  br label %while.cond, !dbg !2776

while.cond:                                       ; preds = %if.end119, %if.end109
  %119 = load i64, i64* %s, align 8, !dbg !2777
  %120 = load i64, i64* %min.addr, align 8, !dbg !2779
  %cmp110 = icmp ult i64 %119, %120, !dbg !2780
  br i1 %cmp110, label %while.body, label %while.end, !dbg !2781

while.body:                                       ; preds = %while.cond
  %121 = load i64, i64* %t, align 8, !dbg !2782
  %mul = mul i64 %121, 2, !dbg !2782
  store i64 %mul, i64* %t, align 8, !dbg !2782
  %122 = load i64, i64* %t, align 8, !dbg !2784
  %123 = load i64, i64* %s, align 8, !dbg !2786
  %cmp111 = icmp ule i64 %122, %123, !dbg !2787
  br i1 %cmp111, label %if.then112, label %if.end119, !dbg !2788

if.then112:                                       ; preds = %while.body
  %124 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2789
  %archive113 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %124, i32 0, i32 3, !dbg !2791
  %125 = load %struct.archive_read*, %struct.archive_read** %archive113, align 8, !dbg !2791
  %archive114 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %125, i32 0, i32 0, !dbg !2792
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive114, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.22, i32 0, i32 0)), !dbg !2793
  %126 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2794
  %fatal115 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %126, i32 0, i32 23, !dbg !2795
  store i8 1, i8* %fatal115, align 2, !dbg !2796
  %127 = load i64*, i64** %avail.addr, align 8, !dbg !2797
  %cmp116 = icmp ne i64* %127, null, !dbg !2799
  br i1 %cmp116, label %if.then117, label %if.end118, !dbg !2800

if.then117:                                       ; preds = %if.then112
  %128 = load i64*, i64** %avail.addr, align 8, !dbg !2801
  store i64 -30, i64* %128, align 8, !dbg !2802
  br label %if.end118, !dbg !2803

if.end118:                                        ; preds = %if.then117, %if.then112
  store i8* null, i8** %retval, align 8, !dbg !2804
  br label %return, !dbg !2804

if.end119:                                        ; preds = %while.body
  %129 = load i64, i64* %t, align 8, !dbg !2805
  store i64 %129, i64* %s, align 8, !dbg !2806
  br label %while.cond, !dbg !2807

while.end:                                        ; preds = %while.cond
  %130 = load i64, i64* %s, align 8, !dbg !2809
  %call120 = call noalias i8* @malloc(i64 %130) #7, !dbg !2810
  store i8* %call120, i8** %p, align 8, !dbg !2811
  %131 = load i8*, i8** %p, align 8, !dbg !2812
  %cmp121 = icmp eq i8* %131, null, !dbg !2814
  br i1 %cmp121, label %if.then122, label %if.end129, !dbg !2815

if.then122:                                       ; preds = %while.end
  %132 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2816
  %archive123 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %132, i32 0, i32 3, !dbg !2818
  %133 = load %struct.archive_read*, %struct.archive_read** %archive123, align 8, !dbg !2818
  %archive124 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %133, i32 0, i32 0, !dbg !2819
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive124, i32 12, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.22, i32 0, i32 0)), !dbg !2820
  %134 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2821
  %fatal125 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %134, i32 0, i32 23, !dbg !2822
  store i8 1, i8* %fatal125, align 2, !dbg !2823
  %135 = load i64*, i64** %avail.addr, align 8, !dbg !2824
  %cmp126 = icmp ne i64* %135, null, !dbg !2826
  br i1 %cmp126, label %if.then127, label %if.end128, !dbg !2827

if.then127:                                       ; preds = %if.then122
  %136 = load i64*, i64** %avail.addr, align 8, !dbg !2828
  store i64 -30, i64* %136, align 8, !dbg !2829
  br label %if.end128, !dbg !2830

if.end128:                                        ; preds = %if.then127, %if.then122
  store i8* null, i8** %retval, align 8, !dbg !2831
  br label %return, !dbg !2831

if.end129:                                        ; preds = %while.end
  %137 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2832
  %avail130 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %137, i32 0, i32 16, !dbg !2834
  %138 = load i64, i64* %avail130, align 8, !dbg !2834
  %cmp131 = icmp ugt i64 %138, 0, !dbg !2835
  br i1 %cmp131, label %if.then132, label %if.end135, !dbg !2836

if.then132:                                       ; preds = %if.end129
  %139 = load i8*, i8** %p, align 8, !dbg !2837
  %140 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2838
  %next133 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %140, i32 0, i32 15, !dbg !2839
  %141 = load i8*, i8** %next133, align 8, !dbg !2839
  %142 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2840
  %avail134 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %142, i32 0, i32 16, !dbg !2841
  %143 = load i64, i64* %avail134, align 8, !dbg !2841
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %139, i8* %141, i64 %143, i32 1, i1 false), !dbg !2842
  br label %if.end135, !dbg !2842

if.end135:                                        ; preds = %if.then132, %if.end129
  %144 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2843
  %buffer136 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %144, i32 0, i32 13, !dbg !2844
  %145 = load i8*, i8** %buffer136, align 8, !dbg !2844
  call void @free(i8* %145) #7, !dbg !2845
  %146 = load i8*, i8** %p, align 8, !dbg !2846
  %147 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2847
  %buffer137 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %147, i32 0, i32 13, !dbg !2848
  store i8* %146, i8** %buffer137, align 8, !dbg !2849
  %148 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2850
  %next138 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %148, i32 0, i32 15, !dbg !2851
  store i8* %146, i8** %next138, align 8, !dbg !2852
  %149 = load i64, i64* %s, align 8, !dbg !2853
  %150 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2854
  %buffer_size139 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %150, i32 0, i32 14, !dbg !2855
  store i64 %149, i64* %buffer_size139, align 8, !dbg !2856
  br label %if.end140, !dbg !2857

if.end140:                                        ; preds = %if.end135, %if.else
  %151 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2858
  %buffer141 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %151, i32 0, i32 13, !dbg !2859
  %152 = load i8*, i8** %buffer141, align 8, !dbg !2859
  %153 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2860
  %buffer_size142 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %153, i32 0, i32 14, !dbg !2861
  %154 = load i64, i64* %buffer_size142, align 8, !dbg !2861
  %add.ptr143 = getelementptr inbounds i8, i8* %152, i64 %154, !dbg !2862
  %155 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2863
  %next144 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %155, i32 0, i32 15, !dbg !2864
  %156 = load i8*, i8** %next144, align 8, !dbg !2864
  %157 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2865
  %avail145 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %157, i32 0, i32 16, !dbg !2866
  %158 = load i64, i64* %avail145, align 8, !dbg !2866
  %add.ptr146 = getelementptr inbounds i8, i8* %156, i64 %158, !dbg !2867
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr143 to i64, !dbg !2868
  %sub.ptr.rhs.cast = ptrtoint i8* %add.ptr146 to i64, !dbg !2868
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2868
  store i64 %sub.ptr.sub, i64* %tocopy, align 8, !dbg !2869
  %159 = load i64, i64* %tocopy, align 8, !dbg !2870
  %160 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2872
  %avail147 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %160, i32 0, i32 16, !dbg !2873
  %161 = load i64, i64* %avail147, align 8, !dbg !2873
  %add148 = add i64 %159, %161, !dbg !2874
  %162 = load i64, i64* %min.addr, align 8, !dbg !2875
  %cmp149 = icmp ugt i64 %add148, %162, !dbg !2876
  br i1 %cmp149, label %if.then150, label %if.end153, !dbg !2877

if.then150:                                       ; preds = %if.end140
  %163 = load i64, i64* %min.addr, align 8, !dbg !2878
  %164 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2879
  %avail151 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %164, i32 0, i32 16, !dbg !2880
  %165 = load i64, i64* %avail151, align 8, !dbg !2880
  %sub152 = sub i64 %163, %165, !dbg !2881
  store i64 %sub152, i64* %tocopy, align 8, !dbg !2882
  br label %if.end153, !dbg !2883

if.end153:                                        ; preds = %if.then150, %if.end140
  %166 = load i64, i64* %tocopy, align 8, !dbg !2884
  %167 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2886
  %client_avail154 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %167, i32 0, i32 20, !dbg !2887
  %168 = load i64, i64* %client_avail154, align 8, !dbg !2887
  %cmp155 = icmp ugt i64 %166, %168, !dbg !2888
  br i1 %cmp155, label %if.then156, label %if.end158, !dbg !2889

if.then156:                                       ; preds = %if.end153
  %169 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2890
  %client_avail157 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %169, i32 0, i32 20, !dbg !2891
  %170 = load i64, i64* %client_avail157, align 8, !dbg !2891
  store i64 %170, i64* %tocopy, align 8, !dbg !2892
  br label %if.end158, !dbg !2893

if.end158:                                        ; preds = %if.then156, %if.end153
  %171 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2894
  %next159 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %171, i32 0, i32 15, !dbg !2895
  %172 = load i8*, i8** %next159, align 8, !dbg !2895
  %173 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2896
  %avail160 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %173, i32 0, i32 16, !dbg !2897
  %174 = load i64, i64* %avail160, align 8, !dbg !2897
  %add.ptr161 = getelementptr inbounds i8, i8* %172, i64 %174, !dbg !2898
  %175 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2899
  %client_next162 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %175, i32 0, i32 19, !dbg !2900
  %176 = load i8*, i8** %client_next162, align 8, !dbg !2900
  %177 = load i64, i64* %tocopy, align 8, !dbg !2901
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr161, i8* %176, i64 %177, i32 1, i1 false), !dbg !2902
  %178 = load i64, i64* %tocopy, align 8, !dbg !2903
  %179 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2904
  %client_next163 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %179, i32 0, i32 19, !dbg !2905
  %180 = load i8*, i8** %client_next163, align 8, !dbg !2906
  %add.ptr164 = getelementptr inbounds i8, i8* %180, i64 %178, !dbg !2906
  store i8* %add.ptr164, i8** %client_next163, align 8, !dbg !2906
  %181 = load i64, i64* %tocopy, align 8, !dbg !2907
  %182 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2908
  %client_avail165 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %182, i32 0, i32 20, !dbg !2909
  %183 = load i64, i64* %client_avail165, align 8, !dbg !2910
  %sub166 = sub i64 %183, %181, !dbg !2910
  store i64 %sub166, i64* %client_avail165, align 8, !dbg !2910
  %184 = load i64, i64* %tocopy, align 8, !dbg !2911
  %185 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2912
  %avail167 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %185, i32 0, i32 16, !dbg !2913
  %186 = load i64, i64* %avail167, align 8, !dbg !2914
  %add168 = add i64 %186, %184, !dbg !2914
  store i64 %add168, i64* %avail167, align 8, !dbg !2914
  br label %if.end169

if.end169:                                        ; preds = %if.end158, %if.end97
  br label %for.cond, !dbg !2915

return:                                           ; preds = %if.end128, %if.end118, %if.end96, %if.end71, %if.end60, %if.end30, %if.end11, %if.end
  %187 = load i8*, i8** %retval, align 8, !dbg !2917
  ret i8* %187, !dbg !2917
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind uwtable
define i64 @__archive_read_consume(%struct.archive_read* %a, i64 %request) #0 !dbg !363 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %request.addr = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2918, metadata !401), !dbg !2919
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !2920, metadata !401), !dbg !2921
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2922
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 7, !dbg !2923
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !2923
  %2 = load i64, i64* %request.addr, align 8, !dbg !2924
  %call = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %1, i64 %2), !dbg !2925
  ret i64 %call, !dbg !2926
}

; Function Attrs: nounwind uwtable
define i64 @__archive_read_filter_consume(%struct.archive_read_filter* %filter, i64 %request) #0 !dbg !366 {
entry:
  %retval = alloca i64, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %request.addr = alloca i64, align 8
  %skipped = alloca i64, align 8
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !2927, metadata !401), !dbg !2928
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !2929, metadata !401), !dbg !2930
  call void @llvm.dbg.declare(metadata i64* %skipped, metadata !2931, metadata !401), !dbg !2932
  %0 = load i64, i64* %request.addr, align 8, !dbg !2933
  %cmp = icmp slt i64 %0, 0, !dbg !2935
  br i1 %cmp, label %if.then, label %if.end, !dbg !2936

if.then:                                          ; preds = %entry
  store i64 -30, i64* %retval, align 8, !dbg !2937
  br label %return, !dbg !2937

if.end:                                           ; preds = %entry
  %1 = load i64, i64* %request.addr, align 8, !dbg !2938
  %cmp1 = icmp eq i64 %1, 0, !dbg !2940
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2941

if.then2:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !2942
  br label %return, !dbg !2942

if.end3:                                          ; preds = %if.end
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2943
  %3 = load i64, i64* %request.addr, align 8, !dbg !2944
  %call = call i64 @advance_file_pointer(%struct.archive_read_filter* %2, i64 %3), !dbg !2945
  store i64 %call, i64* %skipped, align 8, !dbg !2946
  %4 = load i64, i64* %skipped, align 8, !dbg !2947
  %5 = load i64, i64* %request.addr, align 8, !dbg !2949
  %cmp4 = icmp eq i64 %4, %5, !dbg !2950
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2951

if.then5:                                         ; preds = %if.end3
  %6 = load i64, i64* %skipped, align 8, !dbg !2952
  store i64 %6, i64* %retval, align 8, !dbg !2953
  br label %return, !dbg !2953

if.end6:                                          ; preds = %if.end3
  %7 = load i64, i64* %skipped, align 8, !dbg !2954
  %cmp7 = icmp slt i64 %7, 0, !dbg !2956
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2957

if.then8:                                         ; preds = %if.end6
  store i64 0, i64* %skipped, align 8, !dbg !2958
  br label %if.end9, !dbg !2959

if.end9:                                          ; preds = %if.then8, %if.end6
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2960
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 3, !dbg !2961
  %9 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !2961
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !2962
  %10 = load i64, i64* %request.addr, align 8, !dbg !2963
  %11 = load i64, i64* %skipped, align 8, !dbg !2964
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @.str.23, i32 0, i32 0), i64 %10, i64 %11), !dbg !2965
  store i64 -30, i64* %retval, align 8, !dbg !2966
  br label %return, !dbg !2966

return:                                           ; preds = %if.end9, %if.then5, %if.then2, %if.then
  %12 = load i64, i64* %retval, align 8, !dbg !2967
  ret i64 %12, !dbg !2967
}

; Function Attrs: nounwind uwtable
define internal i64 @advance_file_pointer(%struct.archive_read_filter* %filter, i64 %request) #0 !dbg !393 {
entry:
  %retval = alloca i64, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %request.addr = alloca i64, align 8
  %bytes_skipped = alloca i64, align 8
  %total_bytes_skipped = alloca i64, align 8
  %bytes_read = alloca i64, align 8
  %min = alloca i64, align 8
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !2968, metadata !401), !dbg !2969
  store i64 %request, i64* %request.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %request.addr, metadata !2970, metadata !401), !dbg !2971
  call void @llvm.dbg.declare(metadata i64* %bytes_skipped, metadata !2972, metadata !401), !dbg !2973
  call void @llvm.dbg.declare(metadata i64* %total_bytes_skipped, metadata !2974, metadata !401), !dbg !2975
  store i64 0, i64* %total_bytes_skipped, align 8, !dbg !2975
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !2976, metadata !401), !dbg !2977
  call void @llvm.dbg.declare(metadata i64* %min, metadata !2978, metadata !401), !dbg !2979
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2980
  %fatal = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 23, !dbg !2982
  %1 = load i8, i8* %fatal, align 2, !dbg !2982
  %tobool = icmp ne i8 %1, 0, !dbg !2980
  br i1 %tobool, label %if.then, label %if.end, !dbg !2983

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !2984
  br label %return, !dbg !2984

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2985
  %avail = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %2, i32 0, i32 16, !dbg !2987
  %3 = load i64, i64* %avail, align 8, !dbg !2987
  %cmp = icmp ugt i64 %3, 0, !dbg !2988
  br i1 %cmp, label %if.then1, label %if.end8, !dbg !2989

if.then1:                                         ; preds = %if.end
  %4 = load i64, i64* %request.addr, align 8, !dbg !2990
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2990
  %avail2 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 16, !dbg !2990
  %6 = load i64, i64* %avail2, align 8, !dbg !2990
  %cmp3 = icmp slt i64 %4, %6, !dbg !2990
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !2990

cond.true:                                        ; preds = %if.then1
  %7 = load i64, i64* %request.addr, align 8, !dbg !2992
  br label %cond.end, !dbg !2992

cond.false:                                       ; preds = %if.then1
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !2994
  %avail4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 16, !dbg !2994
  %9 = load i64, i64* %avail4, align 8, !dbg !2994
  br label %cond.end, !dbg !2994

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %7, %cond.true ], [ %9, %cond.false ], !dbg !2996
  store i64 %cond, i64* %min, align 8, !dbg !2998
  %10 = load i64, i64* %min, align 8, !dbg !2999
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3000
  %next = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 15, !dbg !3001
  %12 = load i8*, i8** %next, align 8, !dbg !3002
  %add.ptr = getelementptr inbounds i8, i8* %12, i64 %10, !dbg !3002
  store i8* %add.ptr, i8** %next, align 8, !dbg !3002
  %13 = load i64, i64* %min, align 8, !dbg !3003
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3004
  %avail5 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 16, !dbg !3005
  %15 = load i64, i64* %avail5, align 8, !dbg !3006
  %sub = sub i64 %15, %13, !dbg !3006
  store i64 %sub, i64* %avail5, align 8, !dbg !3006
  %16 = load i64, i64* %min, align 8, !dbg !3007
  %17 = load i64, i64* %request.addr, align 8, !dbg !3008
  %sub6 = sub i64 %17, %16, !dbg !3008
  store i64 %sub6, i64* %request.addr, align 8, !dbg !3008
  %18 = load i64, i64* %min, align 8, !dbg !3009
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3010
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %19, i32 0, i32 0, !dbg !3011
  %20 = load i64, i64* %position, align 8, !dbg !3012
  %add = add i64 %20, %18, !dbg !3012
  store i64 %add, i64* %position, align 8, !dbg !3012
  %21 = load i64, i64* %min, align 8, !dbg !3013
  %22 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3014
  %add7 = add i64 %22, %21, !dbg !3014
  store i64 %add7, i64* %total_bytes_skipped, align 8, !dbg !3014
  br label %if.end8, !dbg !3015

if.end8:                                          ; preds = %cond.end, %if.end
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3016
  %client_avail = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 20, !dbg !3018
  %24 = load i64, i64* %client_avail, align 8, !dbg !3018
  %cmp9 = icmp ugt i64 %24, 0, !dbg !3019
  br i1 %cmp9, label %if.then10, label %if.end25, !dbg !3020

if.then10:                                        ; preds = %if.end8
  %25 = load i64, i64* %request.addr, align 8, !dbg !3021
  %26 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3021
  %client_avail11 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %26, i32 0, i32 20, !dbg !3021
  %27 = load i64, i64* %client_avail11, align 8, !dbg !3021
  %cmp12 = icmp slt i64 %25, %27, !dbg !3021
  br i1 %cmp12, label %cond.true13, label %cond.false14, !dbg !3021

cond.true13:                                      ; preds = %if.then10
  %28 = load i64, i64* %request.addr, align 8, !dbg !3023
  br label %cond.end16, !dbg !3023

cond.false14:                                     ; preds = %if.then10
  %29 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3025
  %client_avail15 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %29, i32 0, i32 20, !dbg !3025
  %30 = load i64, i64* %client_avail15, align 8, !dbg !3025
  br label %cond.end16, !dbg !3025

cond.end16:                                       ; preds = %cond.false14, %cond.true13
  %cond17 = phi i64 [ %28, %cond.true13 ], [ %30, %cond.false14 ], !dbg !3027
  store i64 %cond17, i64* %min, align 8, !dbg !3029
  %31 = load i64, i64* %min, align 8, !dbg !3030
  %32 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3031
  %client_next = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %32, i32 0, i32 19, !dbg !3032
  %33 = load i8*, i8** %client_next, align 8, !dbg !3033
  %add.ptr18 = getelementptr inbounds i8, i8* %33, i64 %31, !dbg !3033
  store i8* %add.ptr18, i8** %client_next, align 8, !dbg !3033
  %34 = load i64, i64* %min, align 8, !dbg !3034
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3035
  %client_avail19 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %35, i32 0, i32 20, !dbg !3036
  %36 = load i64, i64* %client_avail19, align 8, !dbg !3037
  %sub20 = sub i64 %36, %34, !dbg !3037
  store i64 %sub20, i64* %client_avail19, align 8, !dbg !3037
  %37 = load i64, i64* %min, align 8, !dbg !3038
  %38 = load i64, i64* %request.addr, align 8, !dbg !3039
  %sub21 = sub i64 %38, %37, !dbg !3039
  store i64 %sub21, i64* %request.addr, align 8, !dbg !3039
  %39 = load i64, i64* %min, align 8, !dbg !3040
  %40 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3041
  %position22 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %40, i32 0, i32 0, !dbg !3042
  %41 = load i64, i64* %position22, align 8, !dbg !3043
  %add23 = add i64 %41, %39, !dbg !3043
  store i64 %add23, i64* %position22, align 8, !dbg !3043
  %42 = load i64, i64* %min, align 8, !dbg !3044
  %43 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3045
  %add24 = add i64 %43, %42, !dbg !3045
  store i64 %add24, i64* %total_bytes_skipped, align 8, !dbg !3045
  br label %if.end25, !dbg !3046

if.end25:                                         ; preds = %cond.end16, %if.end8
  %44 = load i64, i64* %request.addr, align 8, !dbg !3047
  %cmp26 = icmp eq i64 %44, 0, !dbg !3049
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !3050

if.then27:                                        ; preds = %if.end25
  %45 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3051
  store i64 %45, i64* %retval, align 8, !dbg !3052
  br label %return, !dbg !3052

if.end28:                                         ; preds = %if.end25
  %46 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3053
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %46, i32 0, i32 6, !dbg !3055
  %47 = load i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !3055
  %cmp29 = icmp ne i64 (%struct.archive_read_filter*, i64)* %47, null, !dbg !3056
  br i1 %cmp29, label %if.then30, label %if.end43, !dbg !3057

if.then30:                                        ; preds = %if.end28
  %48 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3058
  %skip31 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %48, i32 0, i32 6, !dbg !3060
  %49 = load i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64)** %skip31, align 8, !dbg !3060
  %50 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3061
  %51 = load i64, i64* %request.addr, align 8, !dbg !3062
  %call = call i64 %49(%struct.archive_read_filter* %50, i64 %51), !dbg !3063
  store i64 %call, i64* %bytes_skipped, align 8, !dbg !3064
  %52 = load i64, i64* %bytes_skipped, align 8, !dbg !3065
  %cmp32 = icmp slt i64 %52, 0, !dbg !3067
  br i1 %cmp32, label %if.then33, label %if.end35, !dbg !3068

if.then33:                                        ; preds = %if.then30
  %53 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3069
  %fatal34 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %53, i32 0, i32 23, !dbg !3071
  store i8 1, i8* %fatal34, align 2, !dbg !3072
  %54 = load i64, i64* %bytes_skipped, align 8, !dbg !3073
  store i64 %54, i64* %retval, align 8, !dbg !3074
  br label %return, !dbg !3074

if.end35:                                         ; preds = %if.then30
  %55 = load i64, i64* %bytes_skipped, align 8, !dbg !3075
  %56 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3076
  %position36 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %56, i32 0, i32 0, !dbg !3077
  %57 = load i64, i64* %position36, align 8, !dbg !3078
  %add37 = add nsw i64 %57, %55, !dbg !3078
  store i64 %add37, i64* %position36, align 8, !dbg !3078
  %58 = load i64, i64* %bytes_skipped, align 8, !dbg !3079
  %59 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3080
  %add38 = add nsw i64 %59, %58, !dbg !3080
  store i64 %add38, i64* %total_bytes_skipped, align 8, !dbg !3080
  %60 = load i64, i64* %bytes_skipped, align 8, !dbg !3081
  %61 = load i64, i64* %request.addr, align 8, !dbg !3082
  %sub39 = sub nsw i64 %61, %60, !dbg !3082
  store i64 %sub39, i64* %request.addr, align 8, !dbg !3082
  %62 = load i64, i64* %request.addr, align 8, !dbg !3083
  %cmp40 = icmp eq i64 %62, 0, !dbg !3085
  br i1 %cmp40, label %if.then41, label %if.end42, !dbg !3086

if.then41:                                        ; preds = %if.end35
  %63 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3087
  store i64 %63, i64* %retval, align 8, !dbg !3088
  br label %return, !dbg !3088

if.end42:                                         ; preds = %if.end35
  br label %if.end43, !dbg !3089

if.end43:                                         ; preds = %if.end42, %if.end28
  br label %for.cond, !dbg !3090

for.cond:                                         ; preds = %if.end78, %if.then63, %if.end43
  %64 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3091
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %64, i32 0, i32 5, !dbg !3095
  %65 = load i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !3095
  %66 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3096
  %67 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3097
  %client_buff = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %67, i32 0, i32 17, !dbg !3098
  %call44 = call i64 %65(%struct.archive_read_filter* %66, i8** %client_buff), !dbg !3099
  store i64 %call44, i64* %bytes_read, align 8, !dbg !3100
  %68 = load i64, i64* %bytes_read, align 8, !dbg !3101
  %cmp45 = icmp slt i64 %68, 0, !dbg !3103
  br i1 %cmp45, label %if.then46, label %if.end49, !dbg !3104

if.then46:                                        ; preds = %for.cond
  %69 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3105
  %client_buff47 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %69, i32 0, i32 17, !dbg !3107
  store i8* null, i8** %client_buff47, align 8, !dbg !3108
  %70 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3109
  %fatal48 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %70, i32 0, i32 23, !dbg !3110
  store i8 1, i8* %fatal48, align 2, !dbg !3111
  %71 = load i64, i64* %bytes_read, align 8, !dbg !3112
  store i64 %71, i64* %retval, align 8, !dbg !3113
  br label %return, !dbg !3113

if.end49:                                         ; preds = %for.cond
  %72 = load i64, i64* %bytes_read, align 8, !dbg !3114
  %cmp50 = icmp eq i64 %72, 0, !dbg !3116
  br i1 %cmp50, label %if.then51, label %if.end67, !dbg !3117

if.then51:                                        ; preds = %if.end49
  %73 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3118
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %73, i32 0, i32 3, !dbg !3121
  %74 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !3121
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %74, i32 0, i32 5, !dbg !3122
  %cursor = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 7, !dbg !3123
  %75 = load i32, i32* %cursor, align 4, !dbg !3123
  %76 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3124
  %archive52 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %76, i32 0, i32 3, !dbg !3125
  %77 = load %struct.archive_read*, %struct.archive_read** %archive52, align 8, !dbg !3125
  %client53 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %77, i32 0, i32 5, !dbg !3126
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client53, i32 0, i32 6, !dbg !3127
  %78 = load i32, i32* %nodes, align 8, !dbg !3127
  %sub54 = sub i32 %78, 1, !dbg !3128
  %cmp55 = icmp ne i32 %75, %sub54, !dbg !3129
  br i1 %cmp55, label %if.then56, label %if.end65, !dbg !3130

if.then56:                                        ; preds = %if.then51
  %79 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3131
  %80 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3134
  %archive57 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %80, i32 0, i32 3, !dbg !3135
  %81 = load %struct.archive_read*, %struct.archive_read** %archive57, align 8, !dbg !3135
  %client58 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %81, i32 0, i32 5, !dbg !3136
  %cursor59 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client58, i32 0, i32 7, !dbg !3137
  %82 = load i32, i32* %cursor59, align 4, !dbg !3137
  %add60 = add i32 %82, 1, !dbg !3138
  %call61 = call i32 @client_switch_proxy(%struct.archive_read_filter* %79, i32 %add60), !dbg !3139
  %cmp62 = icmp eq i32 %call61, 0, !dbg !3140
  br i1 %cmp62, label %if.then63, label %if.end64, !dbg !3141

if.then63:                                        ; preds = %if.then56
  br label %for.cond, !dbg !3142

if.end64:                                         ; preds = %if.then56
  br label %if.end65, !dbg !3143

if.end65:                                         ; preds = %if.end64, %if.then51
  %83 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3144
  %client_buff66 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %83, i32 0, i32 17, !dbg !3145
  store i8* null, i8** %client_buff66, align 8, !dbg !3146
  %84 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3147
  %end_of_file = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %84, i32 0, i32 21, !dbg !3148
  store i8 1, i8* %end_of_file, align 8, !dbg !3149
  %85 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3150
  store i64 %85, i64* %retval, align 8, !dbg !3151
  br label %return, !dbg !3151

if.end67:                                         ; preds = %if.end49
  %86 = load i64, i64* %bytes_read, align 8, !dbg !3152
  %87 = load i64, i64* %request.addr, align 8, !dbg !3154
  %cmp68 = icmp sge i64 %86, %87, !dbg !3155
  br i1 %cmp68, label %if.then69, label %if.end78, !dbg !3156

if.then69:                                        ; preds = %if.end67
  %88 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3157
  %client_buff70 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %88, i32 0, i32 17, !dbg !3159
  %89 = load i8*, i8** %client_buff70, align 8, !dbg !3159
  %90 = load i64, i64* %request.addr, align 8, !dbg !3160
  %add.ptr71 = getelementptr inbounds i8, i8* %89, i64 %90, !dbg !3161
  %91 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3162
  %client_next72 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %91, i32 0, i32 19, !dbg !3163
  store i8* %add.ptr71, i8** %client_next72, align 8, !dbg !3164
  %92 = load i64, i64* %bytes_read, align 8, !dbg !3165
  %93 = load i64, i64* %request.addr, align 8, !dbg !3166
  %sub73 = sub nsw i64 %92, %93, !dbg !3167
  %94 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3168
  %client_avail74 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %94, i32 0, i32 20, !dbg !3169
  store i64 %sub73, i64* %client_avail74, align 8, !dbg !3170
  %95 = load i64, i64* %bytes_read, align 8, !dbg !3171
  %96 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3172
  %client_total = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %96, i32 0, i32 18, !dbg !3173
  store i64 %95, i64* %client_total, align 8, !dbg !3174
  %97 = load i64, i64* %request.addr, align 8, !dbg !3175
  %98 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3176
  %add75 = add nsw i64 %98, %97, !dbg !3176
  store i64 %add75, i64* %total_bytes_skipped, align 8, !dbg !3176
  %99 = load i64, i64* %request.addr, align 8, !dbg !3177
  %100 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3178
  %position76 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %100, i32 0, i32 0, !dbg !3179
  %101 = load i64, i64* %position76, align 8, !dbg !3180
  %add77 = add nsw i64 %101, %99, !dbg !3180
  store i64 %add77, i64* %position76, align 8, !dbg !3180
  %102 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3181
  store i64 %102, i64* %retval, align 8, !dbg !3182
  br label %return, !dbg !3182

if.end78:                                         ; preds = %if.end67
  %103 = load i64, i64* %bytes_read, align 8, !dbg !3183
  %104 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3184
  %position79 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %104, i32 0, i32 0, !dbg !3185
  %105 = load i64, i64* %position79, align 8, !dbg !3186
  %add80 = add nsw i64 %105, %103, !dbg !3186
  store i64 %add80, i64* %position79, align 8, !dbg !3186
  %106 = load i64, i64* %bytes_read, align 8, !dbg !3187
  %107 = load i64, i64* %total_bytes_skipped, align 8, !dbg !3188
  %add81 = add nsw i64 %107, %106, !dbg !3188
  store i64 %add81, i64* %total_bytes_skipped, align 8, !dbg !3188
  %108 = load i64, i64* %bytes_read, align 8, !dbg !3189
  %109 = load i64, i64* %request.addr, align 8, !dbg !3190
  %sub82 = sub nsw i64 %109, %108, !dbg !3190
  store i64 %sub82, i64* %request.addr, align 8, !dbg !3190
  br label %for.cond, !dbg !3191

return:                                           ; preds = %if.then69, %if.end65, %if.then46, %if.then41, %if.then33, %if.then27, %if.then
  %110 = load i64, i64* %retval, align 8, !dbg !3193
  ret i64 %110, !dbg !3193
}

; Function Attrs: nounwind uwtable
define i64 @__archive_read_seek(%struct.archive_read* %a, i64 %offset, i32 %whence) #0 !dbg !367 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3194, metadata !401), !dbg !3195
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !3196, metadata !401), !dbg !3197
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !3198, metadata !401), !dbg !3199
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3200
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 7, !dbg !3201
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !3201
  %2 = load i64, i64* %offset.addr, align 8, !dbg !3202
  %3 = load i32, i32* %whence.addr, align 4, !dbg !3203
  %call = call i64 @__archive_read_filter_seek(%struct.archive_read_filter* %1, i64 %2, i32 %3), !dbg !3204
  ret i64 %call, !dbg !3205
}

; Function Attrs: nounwind uwtable
define i64 @__archive_read_filter_seek(%struct.archive_read_filter* %filter, i64 %offset, i32 %whence) #0 !dbg !368 {
entry:
  %retval = alloca i64, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %offset.addr = alloca i64, align 8
  %whence.addr = alloca i32, align 4
  %client = alloca %struct.archive_read_client*, align 8
  %r = alloca i64, align 8
  %cursor = alloca i32, align 4
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !3206, metadata !401), !dbg !3207
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !3208, metadata !401), !dbg !3209
  store i32 %whence, i32* %whence.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %whence.addr, metadata !3210, metadata !401), !dbg !3211
  call void @llvm.dbg.declare(metadata %struct.archive_read_client** %client, metadata !3212, metadata !401), !dbg !3214
  call void @llvm.dbg.declare(metadata i64* %r, metadata !3215, metadata !401), !dbg !3216
  call void @llvm.dbg.declare(metadata i32* %cursor, metadata !3217, metadata !401), !dbg !3218
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3219
  %closed = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 22, !dbg !3221
  %1 = load i8, i8* %closed, align 1, !dbg !3221
  %conv = sext i8 %1 to i32, !dbg !3219
  %tobool = icmp ne i32 %conv, 0, !dbg !3219
  br i1 %tobool, label %if.then, label %lor.lhs.false, !dbg !3222

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3223
  %fatal = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %2, i32 0, i32 23, !dbg !3225
  %3 = load i8, i8* %fatal, align 2, !dbg !3225
  %conv1 = sext i8 %3 to i32, !dbg !3223
  %tobool2 = icmp ne i32 %conv1, 0, !dbg !3223
  br i1 %tobool2, label %if.then, label %if.end, !dbg !3226

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i64 -30, i64* %retval, align 8, !dbg !3227
  br label %return, !dbg !3227

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3228
  %seek = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %4, i32 0, i32 7, !dbg !3230
  %5 = load i64 (%struct.archive_read_filter*, i64, i32)*, i64 (%struct.archive_read_filter*, i64, i32)** %seek, align 8, !dbg !3230
  %cmp = icmp eq i64 (%struct.archive_read_filter*, i64, i32)* %5, null, !dbg !3231
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !3232

if.then4:                                         ; preds = %if.end
  store i64 -25, i64* %retval, align 8, !dbg !3233
  br label %return, !dbg !3233

if.end5:                                          ; preds = %if.end
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3234
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 3, !dbg !3235
  %7 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !3235
  %client6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 5, !dbg !3236
  store %struct.archive_read_client* %client6, %struct.archive_read_client** %client, align 8, !dbg !3237
  %8 = load i32, i32* %whence.addr, align 4, !dbg !3238
  switch i32 %8, label %sw.default [
    i32 1, label %sw.bb
    i32 0, label %sw.bb7
    i32 2, label %sw.bb117
  ], !dbg !3239

sw.bb:                                            ; preds = %if.end5
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3240
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %9, i32 0, i32 0, !dbg !3242
  %10 = load i64, i64* %position, align 8, !dbg !3242
  %11 = load i64, i64* %offset.addr, align 8, !dbg !3243
  %add = add nsw i64 %11, %10, !dbg !3243
  store i64 %add, i64* %offset.addr, align 8, !dbg !3243
  br label %sw.bb7, !dbg !3244

sw.bb7:                                           ; preds = %if.end5, %sw.bb
  store i32 0, i32* %cursor, align 4, !dbg !3245
  br label %while.body, !dbg !3246

while.body:                                       ; preds = %sw.bb7, %if.end33
  %12 = load i32, i32* %cursor, align 4, !dbg !3247
  %idxprom = zext i32 %12 to i64, !dbg !3250
  %13 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3250
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %13, i32 0, i32 9, !dbg !3251
  %14 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !3251
  %arrayidx = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %14, i64 %idxprom, !dbg !3250
  %begin_position = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx, i32 0, i32 0, !dbg !3252
  %15 = load i64, i64* %begin_position, align 8, !dbg !3252
  %cmp8 = icmp slt i64 %15, 0, !dbg !3253
  br i1 %cmp8, label %if.then32, label %lor.lhs.false10, !dbg !3254

lor.lhs.false10:                                  ; preds = %while.body
  %16 = load i32, i32* %cursor, align 4, !dbg !3255
  %idxprom11 = zext i32 %16 to i64, !dbg !3256
  %17 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3256
  %dataset12 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %17, i32 0, i32 9, !dbg !3257
  %18 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset12, align 8, !dbg !3257
  %arrayidx13 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %18, i64 %idxprom11, !dbg !3256
  %total_size = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx13, i32 0, i32 1, !dbg !3258
  %19 = load i64, i64* %total_size, align 8, !dbg !3258
  %cmp14 = icmp slt i64 %19, 0, !dbg !3259
  br i1 %cmp14, label %if.then32, label %lor.lhs.false16, !dbg !3260

lor.lhs.false16:                                  ; preds = %lor.lhs.false10
  %20 = load i32, i32* %cursor, align 4, !dbg !3261
  %idxprom17 = zext i32 %20 to i64, !dbg !3262
  %21 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3262
  %dataset18 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %21, i32 0, i32 9, !dbg !3263
  %22 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset18, align 8, !dbg !3263
  %arrayidx19 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %22, i64 %idxprom17, !dbg !3262
  %begin_position20 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx19, i32 0, i32 0, !dbg !3264
  %23 = load i64, i64* %begin_position20, align 8, !dbg !3264
  %24 = load i32, i32* %cursor, align 4, !dbg !3265
  %idxprom21 = zext i32 %24 to i64, !dbg !3266
  %25 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3266
  %dataset22 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %25, i32 0, i32 9, !dbg !3267
  %26 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset22, align 8, !dbg !3267
  %arrayidx23 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %26, i64 %idxprom21, !dbg !3266
  %total_size24 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx23, i32 0, i32 1, !dbg !3268
  %27 = load i64, i64* %total_size24, align 8, !dbg !3268
  %add25 = add nsw i64 %23, %27, !dbg !3269
  %sub = sub nsw i64 %add25, 1, !dbg !3270
  %28 = load i64, i64* %offset.addr, align 8, !dbg !3271
  %cmp26 = icmp sgt i64 %sub, %28, !dbg !3272
  br i1 %cmp26, label %if.then32, label %lor.lhs.false28, !dbg !3273

lor.lhs.false28:                                  ; preds = %lor.lhs.false16
  %29 = load i32, i32* %cursor, align 4, !dbg !3274
  %add29 = add i32 %29, 1, !dbg !3275
  %30 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3276
  %nodes = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %30, i32 0, i32 6, !dbg !3277
  %31 = load i32, i32* %nodes, align 8, !dbg !3277
  %cmp30 = icmp uge i32 %add29, %31, !dbg !3278
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !3279

if.then32:                                        ; preds = %lor.lhs.false28, %lor.lhs.false16, %lor.lhs.false10, %while.body
  br label %while.end, !dbg !3281

if.end33:                                         ; preds = %lor.lhs.false28
  %32 = load i32, i32* %cursor, align 4, !dbg !3282
  %idxprom34 = zext i32 %32 to i64, !dbg !3283
  %33 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3283
  %dataset35 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %33, i32 0, i32 9, !dbg !3284
  %34 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset35, align 8, !dbg !3284
  %arrayidx36 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %34, i64 %idxprom34, !dbg !3283
  %begin_position37 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx36, i32 0, i32 0, !dbg !3285
  %35 = load i64, i64* %begin_position37, align 8, !dbg !3285
  %36 = load i32, i32* %cursor, align 4, !dbg !3286
  %idxprom38 = zext i32 %36 to i64, !dbg !3287
  %37 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3287
  %dataset39 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %37, i32 0, i32 9, !dbg !3288
  %38 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset39, align 8, !dbg !3288
  %arrayidx40 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %38, i64 %idxprom38, !dbg !3287
  %total_size41 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx40, i32 0, i32 1, !dbg !3289
  %39 = load i64, i64* %total_size41, align 8, !dbg !3289
  %add42 = add nsw i64 %35, %39, !dbg !3290
  store i64 %add42, i64* %r, align 8, !dbg !3291
  %40 = load i64, i64* %r, align 8, !dbg !3292
  %41 = load i32, i32* %cursor, align 4, !dbg !3293
  %inc = add i32 %41, 1, !dbg !3293
  store i32 %inc, i32* %cursor, align 4, !dbg !3293
  %idxprom43 = zext i32 %inc to i64, !dbg !3294
  %42 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3294
  %dataset44 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %42, i32 0, i32 9, !dbg !3295
  %43 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset44, align 8, !dbg !3295
  %arrayidx45 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %43, i64 %idxprom43, !dbg !3294
  %begin_position46 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx45, i32 0, i32 0, !dbg !3296
  store i64 %40, i64* %begin_position46, align 8, !dbg !3297
  br label %while.body, !dbg !3298

while.end:                                        ; preds = %if.then32
  br label %while.body47, !dbg !3300

while.body47:                                     ; preds = %while.end, %if.end80
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3301
  %45 = load i32, i32* %cursor, align 4, !dbg !3303
  %call = call i32 @client_switch_proxy(%struct.archive_read_filter* %44, i32 %45), !dbg !3304
  %conv48 = sext i32 %call to i64, !dbg !3304
  store i64 %conv48, i64* %r, align 8, !dbg !3305
  %46 = load i64, i64* %r, align 8, !dbg !3306
  %cmp49 = icmp ne i64 %46, 0, !dbg !3308
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !3309

if.then51:                                        ; preds = %while.body47
  %47 = load i64, i64* %r, align 8, !dbg !3310
  store i64 %47, i64* %retval, align 8, !dbg !3311
  br label %return, !dbg !3311

if.end52:                                         ; preds = %while.body47
  %48 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3312
  %call53 = call i64 @client_seek_proxy(%struct.archive_read_filter* %48, i64 0, i32 2), !dbg !3314
  store i64 %call53, i64* %r, align 8, !dbg !3315
  %cmp54 = icmp slt i64 %call53, 0, !dbg !3316
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !3317

if.then56:                                        ; preds = %if.end52
  %49 = load i64, i64* %r, align 8, !dbg !3318
  store i64 %49, i64* %retval, align 8, !dbg !3319
  br label %return, !dbg !3319

if.end57:                                         ; preds = %if.end52
  %50 = load i64, i64* %r, align 8, !dbg !3320
  %51 = load i32, i32* %cursor, align 4, !dbg !3321
  %idxprom58 = zext i32 %51 to i64, !dbg !3322
  %52 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3322
  %dataset59 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %52, i32 0, i32 9, !dbg !3323
  %53 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset59, align 8, !dbg !3323
  %arrayidx60 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %53, i64 %idxprom58, !dbg !3322
  %total_size61 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx60, i32 0, i32 1, !dbg !3324
  store i64 %50, i64* %total_size61, align 8, !dbg !3325
  %54 = load i32, i32* %cursor, align 4, !dbg !3326
  %idxprom62 = zext i32 %54 to i64, !dbg !3328
  %55 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3328
  %dataset63 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %55, i32 0, i32 9, !dbg !3329
  %56 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset63, align 8, !dbg !3329
  %arrayidx64 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %56, i64 %idxprom62, !dbg !3328
  %begin_position65 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx64, i32 0, i32 0, !dbg !3330
  %57 = load i64, i64* %begin_position65, align 8, !dbg !3330
  %58 = load i32, i32* %cursor, align 4, !dbg !3331
  %idxprom66 = zext i32 %58 to i64, !dbg !3332
  %59 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3332
  %dataset67 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %59, i32 0, i32 9, !dbg !3333
  %60 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset67, align 8, !dbg !3333
  %arrayidx68 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %60, i64 %idxprom66, !dbg !3332
  %total_size69 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx68, i32 0, i32 1, !dbg !3334
  %61 = load i64, i64* %total_size69, align 8, !dbg !3334
  %add70 = add nsw i64 %57, %61, !dbg !3335
  %sub71 = sub nsw i64 %add70, 1, !dbg !3336
  %62 = load i64, i64* %offset.addr, align 8, !dbg !3337
  %cmp72 = icmp sgt i64 %sub71, %62, !dbg !3338
  br i1 %cmp72, label %if.then79, label %lor.lhs.false74, !dbg !3339

lor.lhs.false74:                                  ; preds = %if.end57
  %63 = load i32, i32* %cursor, align 4, !dbg !3340
  %add75 = add i32 %63, 1, !dbg !3341
  %64 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3342
  %nodes76 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %64, i32 0, i32 6, !dbg !3343
  %65 = load i32, i32* %nodes76, align 8, !dbg !3343
  %cmp77 = icmp uge i32 %add75, %65, !dbg !3344
  br i1 %cmp77, label %if.then79, label %if.end80, !dbg !3345

if.then79:                                        ; preds = %lor.lhs.false74, %if.end57
  br label %while.end95, !dbg !3347

if.end80:                                         ; preds = %lor.lhs.false74
  %66 = load i32, i32* %cursor, align 4, !dbg !3348
  %idxprom81 = zext i32 %66 to i64, !dbg !3349
  %67 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3349
  %dataset82 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %67, i32 0, i32 9, !dbg !3350
  %68 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset82, align 8, !dbg !3350
  %arrayidx83 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %68, i64 %idxprom81, !dbg !3349
  %begin_position84 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx83, i32 0, i32 0, !dbg !3351
  %69 = load i64, i64* %begin_position84, align 8, !dbg !3351
  %70 = load i32, i32* %cursor, align 4, !dbg !3352
  %idxprom85 = zext i32 %70 to i64, !dbg !3353
  %71 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3353
  %dataset86 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %71, i32 0, i32 9, !dbg !3354
  %72 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset86, align 8, !dbg !3354
  %arrayidx87 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %72, i64 %idxprom85, !dbg !3353
  %total_size88 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx87, i32 0, i32 1, !dbg !3355
  %73 = load i64, i64* %total_size88, align 8, !dbg !3355
  %add89 = add nsw i64 %69, %73, !dbg !3356
  store i64 %add89, i64* %r, align 8, !dbg !3357
  %74 = load i64, i64* %r, align 8, !dbg !3358
  %75 = load i32, i32* %cursor, align 4, !dbg !3359
  %inc90 = add i32 %75, 1, !dbg !3359
  store i32 %inc90, i32* %cursor, align 4, !dbg !3359
  %idxprom91 = zext i32 %inc90 to i64, !dbg !3360
  %76 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3360
  %dataset92 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %76, i32 0, i32 9, !dbg !3361
  %77 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset92, align 8, !dbg !3361
  %arrayidx93 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %77, i64 %idxprom91, !dbg !3360
  %begin_position94 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx93, i32 0, i32 0, !dbg !3362
  store i64 %74, i64* %begin_position94, align 8, !dbg !3363
  br label %while.body47, !dbg !3364

while.end95:                                      ; preds = %if.then79
  %78 = load i32, i32* %cursor, align 4, !dbg !3365
  %idxprom96 = zext i32 %78 to i64, !dbg !3366
  %79 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3366
  %dataset97 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %79, i32 0, i32 9, !dbg !3367
  %80 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset97, align 8, !dbg !3367
  %arrayidx98 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %80, i64 %idxprom96, !dbg !3366
  %begin_position99 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx98, i32 0, i32 0, !dbg !3368
  %81 = load i64, i64* %begin_position99, align 8, !dbg !3368
  %82 = load i64, i64* %offset.addr, align 8, !dbg !3369
  %sub100 = sub nsw i64 %82, %81, !dbg !3369
  store i64 %sub100, i64* %offset.addr, align 8, !dbg !3369
  %83 = load i64, i64* %offset.addr, align 8, !dbg !3370
  %cmp101 = icmp slt i64 %83, 0, !dbg !3372
  br i1 %cmp101, label %if.then110, label %lor.lhs.false103, !dbg !3373

lor.lhs.false103:                                 ; preds = %while.end95
  %84 = load i64, i64* %offset.addr, align 8, !dbg !3374
  %85 = load i32, i32* %cursor, align 4, !dbg !3376
  %idxprom104 = zext i32 %85 to i64, !dbg !3377
  %86 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3377
  %dataset105 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %86, i32 0, i32 9, !dbg !3378
  %87 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset105, align 8, !dbg !3378
  %arrayidx106 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %87, i64 %idxprom104, !dbg !3377
  %total_size107 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx106, i32 0, i32 1, !dbg !3379
  %88 = load i64, i64* %total_size107, align 8, !dbg !3379
  %cmp108 = icmp sgt i64 %84, %88, !dbg !3380
  br i1 %cmp108, label %if.then110, label %if.end111, !dbg !3381

if.then110:                                       ; preds = %lor.lhs.false103, %while.end95
  store i64 -30, i64* %retval, align 8, !dbg !3382
  br label %return, !dbg !3382

if.end111:                                        ; preds = %lor.lhs.false103
  %89 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3383
  %90 = load i64, i64* %offset.addr, align 8, !dbg !3385
  %call112 = call i64 @client_seek_proxy(%struct.archive_read_filter* %89, i64 %90, i32 0), !dbg !3386
  store i64 %call112, i64* %r, align 8, !dbg !3387
  %cmp113 = icmp slt i64 %call112, 0, !dbg !3388
  br i1 %cmp113, label %if.then115, label %if.end116, !dbg !3389

if.then115:                                       ; preds = %if.end111
  %91 = load i64, i64* %r, align 8, !dbg !3390
  store i64 %91, i64* %retval, align 8, !dbg !3391
  br label %return, !dbg !3391

if.end116:                                        ; preds = %if.end111
  br label %sw.epilog, !dbg !3392

sw.bb117:                                         ; preds = %if.end5
  store i32 0, i32* %cursor, align 4, !dbg !3393
  br label %while.body118, !dbg !3394

while.body118:                                    ; preds = %sw.bb117, %if.end138
  %92 = load i32, i32* %cursor, align 4, !dbg !3395
  %idxprom119 = zext i32 %92 to i64, !dbg !3398
  %93 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3398
  %dataset120 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %93, i32 0, i32 9, !dbg !3399
  %94 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset120, align 8, !dbg !3399
  %arrayidx121 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %94, i64 %idxprom119, !dbg !3398
  %begin_position122 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx121, i32 0, i32 0, !dbg !3400
  %95 = load i64, i64* %begin_position122, align 8, !dbg !3400
  %cmp123 = icmp slt i64 %95, 0, !dbg !3401
  br i1 %cmp123, label %if.then137, label %lor.lhs.false125, !dbg !3402

lor.lhs.false125:                                 ; preds = %while.body118
  %96 = load i32, i32* %cursor, align 4, !dbg !3403
  %idxprom126 = zext i32 %96 to i64, !dbg !3404
  %97 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3404
  %dataset127 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %97, i32 0, i32 9, !dbg !3405
  %98 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset127, align 8, !dbg !3405
  %arrayidx128 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %98, i64 %idxprom126, !dbg !3404
  %total_size129 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx128, i32 0, i32 1, !dbg !3406
  %99 = load i64, i64* %total_size129, align 8, !dbg !3406
  %cmp130 = icmp slt i64 %99, 0, !dbg !3407
  br i1 %cmp130, label %if.then137, label %lor.lhs.false132, !dbg !3408

lor.lhs.false132:                                 ; preds = %lor.lhs.false125
  %100 = load i32, i32* %cursor, align 4, !dbg !3409
  %add133 = add i32 %100, 1, !dbg !3410
  %101 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3411
  %nodes134 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %101, i32 0, i32 6, !dbg !3412
  %102 = load i32, i32* %nodes134, align 8, !dbg !3412
  %cmp135 = icmp uge i32 %add133, %102, !dbg !3413
  br i1 %cmp135, label %if.then137, label %if.end138, !dbg !3414

if.then137:                                       ; preds = %lor.lhs.false132, %lor.lhs.false125, %while.body118
  br label %while.end153, !dbg !3416

if.end138:                                        ; preds = %lor.lhs.false132
  %103 = load i32, i32* %cursor, align 4, !dbg !3417
  %idxprom139 = zext i32 %103 to i64, !dbg !3418
  %104 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3418
  %dataset140 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %104, i32 0, i32 9, !dbg !3419
  %105 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset140, align 8, !dbg !3419
  %arrayidx141 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %105, i64 %idxprom139, !dbg !3418
  %begin_position142 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx141, i32 0, i32 0, !dbg !3420
  %106 = load i64, i64* %begin_position142, align 8, !dbg !3420
  %107 = load i32, i32* %cursor, align 4, !dbg !3421
  %idxprom143 = zext i32 %107 to i64, !dbg !3422
  %108 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3422
  %dataset144 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %108, i32 0, i32 9, !dbg !3423
  %109 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset144, align 8, !dbg !3423
  %arrayidx145 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %109, i64 %idxprom143, !dbg !3422
  %total_size146 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx145, i32 0, i32 1, !dbg !3424
  %110 = load i64, i64* %total_size146, align 8, !dbg !3424
  %add147 = add nsw i64 %106, %110, !dbg !3425
  store i64 %add147, i64* %r, align 8, !dbg !3426
  %111 = load i64, i64* %r, align 8, !dbg !3427
  %112 = load i32, i32* %cursor, align 4, !dbg !3428
  %inc148 = add i32 %112, 1, !dbg !3428
  store i32 %inc148, i32* %cursor, align 4, !dbg !3428
  %idxprom149 = zext i32 %inc148 to i64, !dbg !3429
  %113 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3429
  %dataset150 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %113, i32 0, i32 9, !dbg !3430
  %114 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset150, align 8, !dbg !3430
  %arrayidx151 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %114, i64 %idxprom149, !dbg !3429
  %begin_position152 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx151, i32 0, i32 0, !dbg !3431
  store i64 %111, i64* %begin_position152, align 8, !dbg !3432
  br label %while.body118, !dbg !3433

while.end153:                                     ; preds = %if.then137
  br label %while.body154, !dbg !3434

while.body154:                                    ; preds = %while.end153, %if.end184
  %115 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3435
  %116 = load i32, i32* %cursor, align 4, !dbg !3437
  %call155 = call i32 @client_switch_proxy(%struct.archive_read_filter* %115, i32 %116), !dbg !3438
  %conv156 = sext i32 %call155 to i64, !dbg !3438
  store i64 %conv156, i64* %r, align 8, !dbg !3439
  %117 = load i64, i64* %r, align 8, !dbg !3440
  %cmp157 = icmp ne i64 %117, 0, !dbg !3442
  br i1 %cmp157, label %if.then159, label %if.end160, !dbg !3443

if.then159:                                       ; preds = %while.body154
  %118 = load i64, i64* %r, align 8, !dbg !3444
  store i64 %118, i64* %retval, align 8, !dbg !3445
  br label %return, !dbg !3445

if.end160:                                        ; preds = %while.body154
  %119 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3446
  %call161 = call i64 @client_seek_proxy(%struct.archive_read_filter* %119, i64 0, i32 2), !dbg !3448
  store i64 %call161, i64* %r, align 8, !dbg !3449
  %cmp162 = icmp slt i64 %call161, 0, !dbg !3450
  br i1 %cmp162, label %if.then164, label %if.end165, !dbg !3451

if.then164:                                       ; preds = %if.end160
  %120 = load i64, i64* %r, align 8, !dbg !3452
  store i64 %120, i64* %retval, align 8, !dbg !3453
  br label %return, !dbg !3453

if.end165:                                        ; preds = %if.end160
  %121 = load i64, i64* %r, align 8, !dbg !3454
  %122 = load i32, i32* %cursor, align 4, !dbg !3455
  %idxprom166 = zext i32 %122 to i64, !dbg !3456
  %123 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3456
  %dataset167 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %123, i32 0, i32 9, !dbg !3457
  %124 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset167, align 8, !dbg !3457
  %arrayidx168 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %124, i64 %idxprom166, !dbg !3456
  %total_size169 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx168, i32 0, i32 1, !dbg !3458
  store i64 %121, i64* %total_size169, align 8, !dbg !3459
  %125 = load i32, i32* %cursor, align 4, !dbg !3460
  %idxprom170 = zext i32 %125 to i64, !dbg !3461
  %126 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3461
  %dataset171 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %126, i32 0, i32 9, !dbg !3462
  %127 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset171, align 8, !dbg !3462
  %arrayidx172 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %127, i64 %idxprom170, !dbg !3461
  %begin_position173 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx172, i32 0, i32 0, !dbg !3463
  %128 = load i64, i64* %begin_position173, align 8, !dbg !3463
  %129 = load i32, i32* %cursor, align 4, !dbg !3464
  %idxprom174 = zext i32 %129 to i64, !dbg !3465
  %130 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3465
  %dataset175 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %130, i32 0, i32 9, !dbg !3466
  %131 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset175, align 8, !dbg !3466
  %arrayidx176 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %131, i64 %idxprom174, !dbg !3465
  %total_size177 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx176, i32 0, i32 1, !dbg !3467
  %132 = load i64, i64* %total_size177, align 8, !dbg !3467
  %add178 = add nsw i64 %128, %132, !dbg !3468
  store i64 %add178, i64* %r, align 8, !dbg !3469
  %133 = load i32, i32* %cursor, align 4, !dbg !3470
  %add179 = add i32 %133, 1, !dbg !3472
  %134 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3473
  %nodes180 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %134, i32 0, i32 6, !dbg !3474
  %135 = load i32, i32* %nodes180, align 8, !dbg !3474
  %cmp181 = icmp uge i32 %add179, %135, !dbg !3475
  br i1 %cmp181, label %if.then183, label %if.end184, !dbg !3476

if.then183:                                       ; preds = %if.end165
  br label %while.end190, !dbg !3477

if.end184:                                        ; preds = %if.end165
  %136 = load i64, i64* %r, align 8, !dbg !3478
  %137 = load i32, i32* %cursor, align 4, !dbg !3479
  %inc185 = add i32 %137, 1, !dbg !3479
  store i32 %inc185, i32* %cursor, align 4, !dbg !3479
  %idxprom186 = zext i32 %inc185 to i64, !dbg !3480
  %138 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3480
  %dataset187 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %138, i32 0, i32 9, !dbg !3481
  %139 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset187, align 8, !dbg !3481
  %arrayidx188 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %139, i64 %idxprom186, !dbg !3480
  %begin_position189 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx188, i32 0, i32 0, !dbg !3482
  store i64 %136, i64* %begin_position189, align 8, !dbg !3483
  br label %while.body154, !dbg !3484

while.end190:                                     ; preds = %if.then183
  br label %while.body191, !dbg !3485

while.body191:                                    ; preds = %while.end190, %if.end209
  %140 = load i64, i64* %r, align 8, !dbg !3486
  %141 = load i64, i64* %offset.addr, align 8, !dbg !3489
  %add192 = add nsw i64 %140, %141, !dbg !3490
  %142 = load i32, i32* %cursor, align 4, !dbg !3491
  %idxprom193 = zext i32 %142 to i64, !dbg !3492
  %143 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3492
  %dataset194 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %143, i32 0, i32 9, !dbg !3493
  %144 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset194, align 8, !dbg !3493
  %arrayidx195 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %144, i64 %idxprom193, !dbg !3492
  %begin_position196 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx195, i32 0, i32 0, !dbg !3494
  %145 = load i64, i64* %begin_position196, align 8, !dbg !3494
  %cmp197 = icmp sge i64 %add192, %145, !dbg !3495
  br i1 %cmp197, label %if.then199, label %if.end200, !dbg !3496

if.then199:                                       ; preds = %while.body191
  br label %while.end219, !dbg !3497

if.end200:                                        ; preds = %while.body191
  %146 = load i32, i32* %cursor, align 4, !dbg !3498
  %idxprom201 = zext i32 %146 to i64, !dbg !3499
  %147 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3499
  %dataset202 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %147, i32 0, i32 9, !dbg !3500
  %148 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset202, align 8, !dbg !3500
  %arrayidx203 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %148, i64 %idxprom201, !dbg !3499
  %total_size204 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx203, i32 0, i32 1, !dbg !3501
  %149 = load i64, i64* %total_size204, align 8, !dbg !3501
  %150 = load i64, i64* %offset.addr, align 8, !dbg !3502
  %add205 = add nsw i64 %150, %149, !dbg !3502
  store i64 %add205, i64* %offset.addr, align 8, !dbg !3502
  %151 = load i32, i32* %cursor, align 4, !dbg !3503
  %cmp206 = icmp eq i32 %151, 0, !dbg !3505
  br i1 %cmp206, label %if.then208, label %if.end209, !dbg !3506

if.then208:                                       ; preds = %if.end200
  br label %while.end219, !dbg !3507

if.end209:                                        ; preds = %if.end200
  %152 = load i32, i32* %cursor, align 4, !dbg !3508
  %dec = add i32 %152, -1, !dbg !3508
  store i32 %dec, i32* %cursor, align 4, !dbg !3508
  %153 = load i32, i32* %cursor, align 4, !dbg !3509
  %idxprom210 = zext i32 %153 to i64, !dbg !3510
  %154 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3510
  %dataset211 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %154, i32 0, i32 9, !dbg !3511
  %155 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset211, align 8, !dbg !3511
  %arrayidx212 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %155, i64 %idxprom210, !dbg !3510
  %begin_position213 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx212, i32 0, i32 0, !dbg !3512
  %156 = load i64, i64* %begin_position213, align 8, !dbg !3512
  %157 = load i32, i32* %cursor, align 4, !dbg !3513
  %idxprom214 = zext i32 %157 to i64, !dbg !3514
  %158 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3514
  %dataset215 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %158, i32 0, i32 9, !dbg !3515
  %159 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset215, align 8, !dbg !3515
  %arrayidx216 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %159, i64 %idxprom214, !dbg !3514
  %total_size217 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx216, i32 0, i32 1, !dbg !3516
  %160 = load i64, i64* %total_size217, align 8, !dbg !3516
  %add218 = add nsw i64 %156, %160, !dbg !3517
  store i64 %add218, i64* %r, align 8, !dbg !3518
  br label %while.body191, !dbg !3519

while.end219:                                     ; preds = %if.then208, %if.then199
  %161 = load i64, i64* %r, align 8, !dbg !3520
  %162 = load i64, i64* %offset.addr, align 8, !dbg !3521
  %add220 = add nsw i64 %161, %162, !dbg !3522
  %163 = load i32, i32* %cursor, align 4, !dbg !3523
  %idxprom221 = zext i32 %163 to i64, !dbg !3524
  %164 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3524
  %dataset222 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %164, i32 0, i32 9, !dbg !3525
  %165 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset222, align 8, !dbg !3525
  %arrayidx223 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %165, i64 %idxprom221, !dbg !3524
  %begin_position224 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx223, i32 0, i32 0, !dbg !3526
  %166 = load i64, i64* %begin_position224, align 8, !dbg !3526
  %sub225 = sub nsw i64 %add220, %166, !dbg !3527
  store i64 %sub225, i64* %offset.addr, align 8, !dbg !3528
  %167 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3529
  %168 = load i32, i32* %cursor, align 4, !dbg !3531
  %call226 = call i32 @client_switch_proxy(%struct.archive_read_filter* %167, i32 %168), !dbg !3532
  %conv227 = sext i32 %call226 to i64, !dbg !3532
  store i64 %conv227, i64* %r, align 8, !dbg !3533
  %cmp228 = icmp ne i64 %conv227, 0, !dbg !3534
  br i1 %cmp228, label %if.then230, label %if.end231, !dbg !3535

if.then230:                                       ; preds = %while.end219
  %169 = load i64, i64* %r, align 8, !dbg !3536
  store i64 %169, i64* %retval, align 8, !dbg !3537
  br label %return, !dbg !3537

if.end231:                                        ; preds = %while.end219
  %170 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3538
  %171 = load i64, i64* %offset.addr, align 8, !dbg !3539
  %call232 = call i64 @client_seek_proxy(%struct.archive_read_filter* %170, i64 %171, i32 0), !dbg !3540
  store i64 %call232, i64* %r, align 8, !dbg !3541
  %172 = load i64, i64* %r, align 8, !dbg !3542
  %cmp233 = icmp slt i64 %172, 0, !dbg !3544
  br i1 %cmp233, label %if.then235, label %if.end236, !dbg !3545

if.then235:                                       ; preds = %if.end231
  %173 = load i64, i64* %r, align 8, !dbg !3546
  store i64 %173, i64* %retval, align 8, !dbg !3547
  br label %return, !dbg !3547

if.end236:                                        ; preds = %if.end231
  br label %sw.epilog, !dbg !3548

sw.default:                                       ; preds = %if.end5
  store i64 -30, i64* %retval, align 8, !dbg !3549
  br label %return, !dbg !3549

sw.epilog:                                        ; preds = %if.end236, %if.end116
  %174 = load i32, i32* %cursor, align 4, !dbg !3550
  %idxprom237 = zext i32 %174 to i64, !dbg !3551
  %175 = load %struct.archive_read_client*, %struct.archive_read_client** %client, align 8, !dbg !3551
  %dataset238 = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %175, i32 0, i32 9, !dbg !3552
  %176 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset238, align 8, !dbg !3552
  %arrayidx239 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %176, i64 %idxprom237, !dbg !3551
  %begin_position240 = getelementptr inbounds %struct.archive_read_data_node, %struct.archive_read_data_node* %arrayidx239, i32 0, i32 0, !dbg !3553
  %177 = load i64, i64* %begin_position240, align 8, !dbg !3553
  %178 = load i64, i64* %r, align 8, !dbg !3554
  %add241 = add nsw i64 %178, %177, !dbg !3554
  store i64 %add241, i64* %r, align 8, !dbg !3554
  %179 = load i64, i64* %r, align 8, !dbg !3555
  %cmp242 = icmp sge i64 %179, 0, !dbg !3557
  br i1 %cmp242, label %if.then244, label %if.end246, !dbg !3558

if.then244:                                       ; preds = %sw.epilog
  %180 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3559
  %client_avail = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %180, i32 0, i32 20, !dbg !3561
  store i64 0, i64* %client_avail, align 8, !dbg !3562
  %181 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3563
  %avail = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %181, i32 0, i32 16, !dbg !3564
  store i64 0, i64* %avail, align 8, !dbg !3565
  %182 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3566
  %buffer = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %182, i32 0, i32 13, !dbg !3567
  %183 = load i8*, i8** %buffer, align 8, !dbg !3567
  %184 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3568
  %next = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %184, i32 0, i32 15, !dbg !3569
  store i8* %183, i8** %next, align 8, !dbg !3570
  %185 = load i64, i64* %r, align 8, !dbg !3571
  %186 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3572
  %position245 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %186, i32 0, i32 0, !dbg !3573
  store i64 %185, i64* %position245, align 8, !dbg !3574
  %187 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !3575
  %end_of_file = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %187, i32 0, i32 21, !dbg !3576
  store i8 0, i8* %end_of_file, align 8, !dbg !3577
  br label %if.end246, !dbg !3578

if.end246:                                        ; preds = %if.then244, %sw.epilog
  %188 = load i64, i64* %r, align 8, !dbg !3579
  store i64 %188, i64* %retval, align 8, !dbg !3580
  br label %return, !dbg !3580

return:                                           ; preds = %if.end246, %sw.default, %if.then235, %if.then230, %if.then164, %if.then159, %if.then115, %if.then110, %if.then56, %if.then51, %if.then4, %if.then
  %189 = load i64, i64* %retval, align 8, !dbg !3581
  ret i64 %189, !dbg !3581
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_filter_bytes(%struct.archive* %_a, i32 %n) #0 !dbg !372 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_read_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3582, metadata !401), !dbg !3583
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !3584, metadata !401), !dbg !3585
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %f, metadata !3586, metadata !401), !dbg !3587
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3588
  %1 = load i32, i32* %n.addr, align 4, !dbg !3589
  %call = call %struct.archive_read_filter* @get_filter(%struct.archive* %0, i32 %1), !dbg !3590
  store %struct.archive_read_filter* %call, %struct.archive_read_filter** %f, align 8, !dbg !3587
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3591
  %cmp = icmp eq %struct.archive_read_filter* %2, null, !dbg !3592
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3591

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !3593

cond.false:                                       ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3595
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 0, !dbg !3597
  %4 = load i64, i64* %position, align 8, !dbg !3597
  br label %cond.end, !dbg !3598

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ -1, %cond.true ], [ %4, %cond.false ], !dbg !3599
  ret i64 %cond, !dbg !3601
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_filter_code(%struct.archive* %_a, i32 %n) #0 !dbg !376 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_read_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3602, metadata !401), !dbg !3603
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !3604, metadata !401), !dbg !3605
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %f, metadata !3606, metadata !401), !dbg !3607
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3608
  %1 = load i32, i32* %n.addr, align 4, !dbg !3609
  %call = call %struct.archive_read_filter* @get_filter(%struct.archive* %0, i32 %1), !dbg !3610
  store %struct.archive_read_filter* %call, %struct.archive_read_filter** %f, align 8, !dbg !3607
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3611
  %cmp = icmp eq %struct.archive_read_filter* %2, null, !dbg !3612
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3611

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !3613

cond.false:                                       ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3615
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 12, !dbg !3617
  %4 = load i32, i32* %code, align 8, !dbg !3617
  br label %cond.end, !dbg !3618

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ -1, %cond.true ], [ %4, %cond.false ], !dbg !3619
  ret i32 %cond, !dbg !3621
}

; Function Attrs: nounwind uwtable
define internal i8* @_archive_filter_name(%struct.archive* %_a, i32 %n) #0 !dbg !377 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %f = alloca %struct.archive_read_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3622, metadata !401), !dbg !3623
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !3624, metadata !401), !dbg !3625
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %f, metadata !3626, metadata !401), !dbg !3627
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3628
  %1 = load i32, i32* %n.addr, align 4, !dbg !3629
  %call = call %struct.archive_read_filter* @get_filter(%struct.archive* %0, i32 %1), !dbg !3630
  store %struct.archive_read_filter* %call, %struct.archive_read_filter** %f, align 8, !dbg !3627
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3631
  %cmp = icmp ne %struct.archive_read_filter* %2, null, !dbg !3632
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3631

cond.true:                                        ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !3633
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 11, !dbg !3635
  %4 = load i8*, i8** %name, align 8, !dbg !3635
  br label %cond.end, !dbg !3636

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !3637

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %4, %cond.true ], [ null, %cond.false ], !dbg !3639
  ret i8* %cond, !dbg !3641
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_filter_count(%struct.archive* %_a) #0 !dbg !378 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %p = alloca %struct.archive_read_filter*, align 8
  %count = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3642, metadata !401), !dbg !3643
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !3644, metadata !401), !dbg !3645
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3646
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !3647
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !3645
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %p, metadata !3648, metadata !401), !dbg !3649
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3650
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 7, !dbg !3651
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !3651
  store %struct.archive_read_filter* %3, %struct.archive_read_filter** %p, align 8, !dbg !3649
  call void @llvm.dbg.declare(metadata i32* %count, metadata !3652, metadata !401), !dbg !3653
  store i32 0, i32* %count, align 4, !dbg !3653
  br label %while.cond, !dbg !3654

while.cond:                                       ; preds = %while.body, %entry
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %p, align 8, !dbg !3655
  %tobool = icmp ne %struct.archive_read_filter* %4, null, !dbg !3657
  br i1 %tobool, label %while.body, label %while.end, !dbg !3657

while.body:                                       ; preds = %while.cond
  %5 = load i32, i32* %count, align 4, !dbg !3658
  %inc = add nsw i32 %5, 1, !dbg !3658
  store i32 %inc, i32* %count, align 4, !dbg !3658
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %p, align 8, !dbg !3660
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 2, !dbg !3661
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !3661
  store %struct.archive_read_filter* %7, %struct.archive_read_filter** %p, align 8, !dbg !3662
  br label %while.cond, !dbg !3663

while.end:                                        ; preds = %while.cond
  %8 = load i32, i32* %count, align 4, !dbg !3665
  ret i32 %8, !dbg !3666
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_data_block(%struct.archive* %_a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3667, metadata !401), !dbg !3668
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !3669, metadata !401), !dbg !3670
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !3671, metadata !401), !dbg !3672
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !3673, metadata !401), !dbg !3674
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !3675, metadata !401), !dbg !3676
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3677
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !3678
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !3676
  br label %do.body, !dbg !3679

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3680, metadata !401), !dbg !3682
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3683
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 4, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.24, i32 0, i32 0)), !dbg !3683
  store i32 %call, i32* %magic_test, align 4, !dbg !3683
  %3 = load i32, i32* %magic_test, align 4, !dbg !3683
  %cmp = icmp eq i32 %3, -30, !dbg !3683
  br i1 %cmp, label %if.then, label %if.end, !dbg !3683

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3685
  br label %return, !dbg !3685

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3688

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3690
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 13, !dbg !3692
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !3692
  %read_data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 5, !dbg !3693
  %6 = load i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data, align 8, !dbg !3693
  %cmp1 = icmp eq i32 (%struct.archive_read*, i8**, i64*, i64*)* %6, null, !dbg !3694
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3695

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3696
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !3698
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.25, i32 0, i32 0)), !dbg !3699
  store i32 -30, i32* %retval, align 4, !dbg !3700
  br label %return, !dbg !3700

if.end3:                                          ; preds = %do.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3701
  %format4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 13, !dbg !3702
  %9 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format4, align 8, !dbg !3702
  %read_data5 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %9, i32 0, i32 5, !dbg !3703
  %10 = load i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)** %read_data5, align 8, !dbg !3703
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3704
  %12 = load i8**, i8*** %buff.addr, align 8, !dbg !3705
  %13 = load i64*, i64** %size.addr, align 8, !dbg !3706
  %14 = load i64*, i64** %offset.addr, align 8, !dbg !3707
  %call6 = call i32 %10(%struct.archive_read* %11, i8** %12, i64* %13, i64* %14), !dbg !3708
  store i32 %call6, i32* %retval, align 4, !dbg !3709
  br label %return, !dbg !3709

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !3710
  ret i32 %15, !dbg !3710
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_next_header(%struct.archive* %_a, %struct.archive_entry** %entryp) #0 !dbg !380 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %entryp.addr = alloca %struct.archive_entry**, align 8
  %ret = alloca i32, align 4
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3711, metadata !401), !dbg !3712
  store %struct.archive_entry** %entryp, %struct.archive_entry*** %entryp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry*** %entryp.addr, metadata !3713, metadata !401), !dbg !3714
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3715, metadata !401), !dbg !3716
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !3717, metadata !401), !dbg !3718
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3719
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !3720
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !3718
  %2 = load %struct.archive_entry**, %struct.archive_entry*** %entryp.addr, align 8, !dbg !3721
  store %struct.archive_entry* null, %struct.archive_entry** %2, align 8, !dbg !3722
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3723
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3724
  %entry1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 1, !dbg !3725
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !3725
  %call = call i32 @_archive_read_next_header2(%struct.archive* %3, %struct.archive_entry* %5), !dbg !3726
  store i32 %call, i32* %ret, align 4, !dbg !3727
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3728
  %entry2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 1, !dbg !3729
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !3729
  %8 = load %struct.archive_entry**, %struct.archive_entry*** %entryp.addr, align 8, !dbg !3730
  store %struct.archive_entry* %7, %struct.archive_entry** %8, align 8, !dbg !3731
  %9 = load i32, i32* %ret, align 4, !dbg !3732
  ret i32 %9, !dbg !3733
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_next_header2(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !381 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_read*, align 8
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3734, metadata !401), !dbg !3735
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3736, metadata !401), !dbg !3737
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !3738, metadata !401), !dbg !3739
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3740
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !3741
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !3739
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !3742, metadata !401), !dbg !3743
  store i32 0, i32* %r1, align 4, !dbg !3743
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !3744, metadata !401), !dbg !3745
  br label %do.body, !dbg !3746

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3747, metadata !401), !dbg !3749
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3750
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 6, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.26, i32 0, i32 0)), !dbg !3750
  store i32 %call, i32* %magic_test, align 4, !dbg !3750
  %3 = load i32, i32* %magic_test, align 4, !dbg !3750
  %cmp = icmp eq i32 %3, -30, !dbg !3750
  br i1 %cmp, label %if.then, label %if.end, !dbg !3750

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3752
  br label %return, !dbg !3752

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3755

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3757
  %call2 = call %struct.archive_entry* @archive_entry_clear(%struct.archive_entry* %4), !dbg !3758
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3759
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !3760
  call void @archive_clear_error(%struct.archive* %archive), !dbg !3761
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3762
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !3764
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 1, !dbg !3765
  %7 = load i32, i32* %state, align 4, !dbg !3765
  %cmp4 = icmp eq i32 %7, 4, !dbg !3766
  br i1 %cmp4, label %if.then5, label %if.end18, !dbg !3767

if.then5:                                         ; preds = %do.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3768
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !3770
  %call7 = call i32 @archive_read_data_skip(%struct.archive* %archive6), !dbg !3771
  store i32 %call7, i32* %r1, align 4, !dbg !3772
  %9 = load i32, i32* %r1, align 4, !dbg !3773
  %cmp8 = icmp eq i32 %9, 1, !dbg !3775
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !3776

if.then9:                                         ; preds = %if.then5
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3777
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !3778
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 5, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.27, i32 0, i32 0)), !dbg !3779
  br label %if.end11, !dbg !3779

if.end11:                                         ; preds = %if.then9, %if.then5
  %11 = load i32, i32* %r1, align 4, !dbg !3780
  %cmp12 = icmp eq i32 %11, 1, !dbg !3782
  br i1 %cmp12, label %if.then14, label %lor.lhs.false, !dbg !3783

lor.lhs.false:                                    ; preds = %if.end11
  %12 = load i32, i32* %r1, align 4, !dbg !3784
  %cmp13 = icmp eq i32 %12, -30, !dbg !3786
  br i1 %cmp13, label %if.then14, label %if.end17, !dbg !3787

if.then14:                                        ; preds = %lor.lhs.false, %if.end11
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3788
  %archive15 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !3790
  %state16 = getelementptr inbounds %struct.archive, %struct.archive* %archive15, i32 0, i32 1, !dbg !3791
  store i32 32768, i32* %state16, align 4, !dbg !3792
  store i32 -30, i32* %retval, align 4, !dbg !3793
  br label %return, !dbg !3793

if.end17:                                         ; preds = %lor.lhs.false
  br label %if.end18, !dbg !3794

if.end18:                                         ; preds = %if.end17, %do.end
  %14 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3795
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 7, !dbg !3796
  %15 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !3796
  %position = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %15, i32 0, i32 0, !dbg !3797
  %16 = load i64, i64* %position, align 8, !dbg !3797
  %17 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3798
  %header_position = getelementptr inbounds %struct.archive_read, %struct.archive_read* %17, i32 0, i32 9, !dbg !3799
  store i64 %16, i64* %header_position, align 8, !dbg !3800
  %18 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3801
  %file_count = getelementptr inbounds %struct.archive, %struct.archive* %18, i32 0, i32 7, !dbg !3802
  %19 = load i32, i32* %file_count, align 8, !dbg !3803
  %inc = add nsw i32 %19, 1, !dbg !3803
  store i32 %inc, i32* %file_count, align 8, !dbg !3803
  %20 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3804
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %20, i32 0, i32 13, !dbg !3805
  %21 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !3805
  %read_header = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %21, i32 0, i32 4, !dbg !3806
  %22 = load i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, %struct.archive_entry*)** %read_header, align 8, !dbg !3806
  %23 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3807
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3808
  %call19 = call i32 %22(%struct.archive_read* %23, %struct.archive_entry* %24), !dbg !3809
  store i32 %call19, i32* %r2, align 4, !dbg !3810
  %25 = load i32, i32* %r2, align 4, !dbg !3811
  switch i32 %25, label %sw.epilog [
    i32 1, label %sw.bb
    i32 0, label %sw.bb23
    i32 -20, label %sw.bb26
    i32 -10, label %sw.bb29
    i32 -30, label %sw.bb30
  ], !dbg !3812

sw.bb:                                            ; preds = %if.end18
  %26 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3813
  %archive20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 0, !dbg !3815
  %state21 = getelementptr inbounds %struct.archive, %struct.archive* %archive20, i32 0, i32 1, !dbg !3816
  store i32 16, i32* %state21, align 4, !dbg !3817
  %27 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3818
  %file_count22 = getelementptr inbounds %struct.archive, %struct.archive* %27, i32 0, i32 7, !dbg !3819
  %28 = load i32, i32* %file_count22, align 8, !dbg !3820
  %dec = add nsw i32 %28, -1, !dbg !3820
  store i32 %dec, i32* %file_count22, align 8, !dbg !3820
  br label %sw.epilog, !dbg !3821

sw.bb23:                                          ; preds = %if.end18
  %29 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3822
  %archive24 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !3823
  %state25 = getelementptr inbounds %struct.archive, %struct.archive* %archive24, i32 0, i32 1, !dbg !3824
  store i32 4, i32* %state25, align 4, !dbg !3825
  br label %sw.epilog, !dbg !3826

sw.bb26:                                          ; preds = %if.end18
  %30 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3827
  %archive27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %30, i32 0, i32 0, !dbg !3828
  %state28 = getelementptr inbounds %struct.archive, %struct.archive* %archive27, i32 0, i32 1, !dbg !3829
  store i32 4, i32* %state28, align 4, !dbg !3830
  br label %sw.epilog, !dbg !3831

sw.bb29:                                          ; preds = %if.end18
  br label %sw.epilog, !dbg !3832

sw.bb30:                                          ; preds = %if.end18
  %31 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3833
  %archive31 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 0, !dbg !3834
  %state32 = getelementptr inbounds %struct.archive, %struct.archive* %archive31, i32 0, i32 1, !dbg !3835
  store i32 32768, i32* %state32, align 4, !dbg !3836
  br label %sw.epilog, !dbg !3837

sw.epilog:                                        ; preds = %if.end18, %sw.bb30, %sw.bb29, %sw.bb26, %sw.bb23, %sw.bb
  %32 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3838
  %archive33 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 0, !dbg !3839
  call void @__archive_reset_read_data(%struct.archive* %archive33), !dbg !3840
  %33 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3841
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %33, i32 0, i32 5, !dbg !3842
  %cursor = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 7, !dbg !3843
  %34 = load i32, i32* %cursor, align 4, !dbg !3843
  %35 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3844
  %data_start_node = getelementptr inbounds %struct.archive_read, %struct.archive_read* %35, i32 0, i32 10, !dbg !3845
  store i32 %34, i32* %data_start_node, align 8, !dbg !3846
  %36 = load i32, i32* %r2, align 4, !dbg !3847
  %37 = load i32, i32* %r1, align 4, !dbg !3848
  %cmp34 = icmp slt i32 %36, %37, !dbg !3849
  br i1 %cmp34, label %cond.true, label %lor.lhs.false35, !dbg !3850

lor.lhs.false35:                                  ; preds = %sw.epilog
  %38 = load i32, i32* %r2, align 4, !dbg !3851
  %cmp36 = icmp eq i32 %38, 1, !dbg !3853
  br i1 %cmp36, label %cond.true, label %cond.false, !dbg !3854

cond.true:                                        ; preds = %lor.lhs.false35, %sw.epilog
  %39 = load i32, i32* %r2, align 4, !dbg !3855
  br label %cond.end, !dbg !3857

cond.false:                                       ; preds = %lor.lhs.false35
  %40 = load i32, i32* %r1, align 4, !dbg !3858
  br label %cond.end, !dbg !3860

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %39, %cond.true ], [ %40, %cond.false ], !dbg !3861
  store i32 %cond, i32* %retval, align 4, !dbg !3863
  br label %return, !dbg !3863

return:                                           ; preds = %cond.end, %if.then14, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !3864
  ret i32 %41, !dbg !3864
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_free(%struct.archive* %_a) #0 !dbg !382 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %p = alloca %struct.archive_read_passphrase*, align 8
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %slots = alloca i32, align 4
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  %r1 = alloca i32, align 4
  %np = alloca %struct.archive_read_passphrase*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3865, metadata !401), !dbg !3866
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !3867, metadata !401), !dbg !3868
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3869
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !3870
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !3868
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p, metadata !3871, metadata !401), !dbg !3872
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3873, metadata !401), !dbg !3874
  call void @llvm.dbg.declare(metadata i32* %n, metadata !3875, metadata !401), !dbg !3876
  call void @llvm.dbg.declare(metadata i32* %slots, metadata !3877, metadata !401), !dbg !3878
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3879, metadata !401), !dbg !3880
  store i32 0, i32* %r, align 4, !dbg !3880
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3881
  %cmp = icmp eq %struct.archive* %2, null, !dbg !3883
  br i1 %cmp, label %if.then, label %if.end, !dbg !3884

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3885
  br label %return, !dbg !3885

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !3886

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3887, metadata !401), !dbg !3889
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3890
  %call = call i32 @__archive_check_magic(%struct.archive* %3, i32 14594245, i32 65535, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.28, i32 0, i32 0)), !dbg !3890
  store i32 %call, i32* %magic_test, align 4, !dbg !3890
  %4 = load i32, i32* %magic_test, align 4, !dbg !3890
  %cmp1 = icmp eq i32 %4, -30, !dbg !3890
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3890

if.then2:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3892
  br label %return, !dbg !3892

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !3895

do.end:                                           ; preds = %if.end3
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3897
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !3899
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 1, !dbg !3900
  %6 = load i32, i32* %state, align 4, !dbg !3900
  %cmp4 = icmp ne i32 %6, 32, !dbg !3901
  br i1 %cmp4, label %land.lhs.true, label %if.end11, !dbg !3902

land.lhs.true:                                    ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3903
  %archive5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !3905
  %state6 = getelementptr inbounds %struct.archive, %struct.archive* %archive5, i32 0, i32 1, !dbg !3906
  %8 = load i32, i32* %state6, align 4, !dbg !3906
  %cmp7 = icmp ne i32 %8, 32768, !dbg !3907
  br i1 %cmp7, label %if.then8, label %if.end11, !dbg !3908

if.then8:                                         ; preds = %land.lhs.true
  %9 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3910
  %archive9 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !3911
  %call10 = call i32 @archive_read_close(%struct.archive* %archive9), !dbg !3912
  store i32 %call10, i32* %r, align 4, !dbg !3913
  br label %if.end11, !dbg !3914

if.end11:                                         ; preds = %if.then8, %land.lhs.true, %do.end
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3915
  %cleanup_archive_extract = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 15, !dbg !3917
  %11 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %cleanup_archive_extract, align 8, !dbg !3917
  %cmp12 = icmp ne i32 (%struct.archive_read*)* %11, null, !dbg !3918
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !3919

if.then13:                                        ; preds = %if.end11
  %12 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3920
  %cleanup_archive_extract14 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 15, !dbg !3921
  %13 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %cleanup_archive_extract14, align 8, !dbg !3921
  %14 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3922
  %call15 = call i32 %13(%struct.archive_read* %14), !dbg !3923
  store i32 %call15, i32* %r, align 4, !dbg !3924
  br label %if.end16, !dbg !3925

if.end16:                                         ; preds = %if.then13, %if.end11
  store i32 16, i32* %slots, align 4, !dbg !3926
  store i32 0, i32* %i, align 4, !dbg !3927
  br label %for.cond, !dbg !3929

for.cond:                                         ; preds = %for.inc, %if.end16
  %15 = load i32, i32* %i, align 4, !dbg !3930
  %16 = load i32, i32* %slots, align 4, !dbg !3933
  %cmp17 = icmp slt i32 %15, %16, !dbg !3934
  br i1 %cmp17, label %for.body, label %for.end, !dbg !3935

for.body:                                         ; preds = %for.cond
  %17 = load i32, i32* %i, align 4, !dbg !3936
  %idxprom = sext i32 %17 to i64, !dbg !3938
  %18 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3938
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 12, !dbg !3939
  %arrayidx = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 %idxprom, !dbg !3938
  %19 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3940
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 13, !dbg !3941
  store %struct.archive_format_descriptor* %arrayidx, %struct.archive_format_descriptor** %format, align 8, !dbg !3942
  %20 = load i32, i32* %i, align 4, !dbg !3943
  %idxprom18 = sext i32 %20 to i64, !dbg !3945
  %21 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3945
  %formats19 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 12, !dbg !3946
  %arrayidx20 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats19, i64 0, i64 %idxprom18, !dbg !3945
  %cleanup = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx20, i32 0, i32 8, !dbg !3947
  %22 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %cleanup, align 8, !dbg !3947
  %tobool = icmp ne i32 (%struct.archive_read*)* %22, null, !dbg !3945
  br i1 %tobool, label %if.then21, label %if.end27, !dbg !3948

if.then21:                                        ; preds = %for.body
  %23 = load i32, i32* %i, align 4, !dbg !3949
  %idxprom22 = sext i32 %23 to i64, !dbg !3950
  %24 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3950
  %formats23 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 12, !dbg !3951
  %arrayidx24 = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats23, i64 0, i64 %idxprom22, !dbg !3950
  %cleanup25 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %arrayidx24, i32 0, i32 8, !dbg !3952
  %25 = load i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)** %cleanup25, align 8, !dbg !3952
  %26 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3953
  %call26 = call i32 %25(%struct.archive_read* %26), !dbg !3954
  br label %if.end27, !dbg !3954

if.end27:                                         ; preds = %if.then21, %for.body
  br label %for.inc, !dbg !3955

for.inc:                                          ; preds = %if.end27
  %27 = load i32, i32* %i, align 4, !dbg !3956
  %inc = add nsw i32 %27, 1, !dbg !3956
  store i32 %inc, i32* %i, align 4, !dbg !3956
  br label %for.cond, !dbg !3958

for.end:                                          ; preds = %for.cond
  %28 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3959
  call void @__archive_read_free_filters(%struct.archive_read* %28), !dbg !3960
  store i32 16, i32* %n, align 4, !dbg !3961
  store i32 0, i32* %i, align 4, !dbg !3962
  br label %for.cond28, !dbg !3964

for.cond28:                                       ; preds = %for.inc47, %for.end
  %29 = load i32, i32* %i, align 4, !dbg !3965
  %30 = load i32, i32* %n, align 4, !dbg !3968
  %cmp29 = icmp slt i32 %29, %30, !dbg !3969
  br i1 %cmp29, label %for.body30, label %for.end49, !dbg !3970

for.body30:                                       ; preds = %for.cond28
  %31 = load i32, i32* %i, align 4, !dbg !3971
  %idxprom31 = sext i32 %31 to i64, !dbg !3974
  %32 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3974
  %bidders = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 6, !dbg !3975
  %arrayidx32 = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders, i64 0, i64 %idxprom31, !dbg !3974
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %arrayidx32, i32 0, i32 5, !dbg !3976
  %33 = load i32 (%struct.archive_read_filter_bidder*)*, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !3976
  %cmp33 = icmp ne i32 (%struct.archive_read_filter_bidder*)* %33, null, !dbg !3977
  br i1 %cmp33, label %if.then34, label %if.end46, !dbg !3978

if.then34:                                        ; preds = %for.body30
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !3979, metadata !401), !dbg !3981
  %34 = load i32, i32* %i, align 4, !dbg !3982
  %idxprom35 = sext i32 %34 to i64, !dbg !3983
  %35 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3983
  %bidders36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %35, i32 0, i32 6, !dbg !3984
  %arrayidx37 = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders36, i64 0, i64 %idxprom35, !dbg !3983
  %free38 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %arrayidx37, i32 0, i32 5, !dbg !3985
  %36 = load i32 (%struct.archive_read_filter_bidder*)*, i32 (%struct.archive_read_filter_bidder*)** %free38, align 8, !dbg !3985
  %37 = load i32, i32* %i, align 4, !dbg !3986
  %idxprom39 = sext i32 %37 to i64, !dbg !3987
  %38 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !3987
  %bidders40 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %38, i32 0, i32 6, !dbg !3988
  %arrayidx41 = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders40, i64 0, i64 %idxprom39, !dbg !3987
  %call42 = call i32 %36(%struct.archive_read_filter_bidder* %arrayidx41), !dbg !3989
  store i32 %call42, i32* %r1, align 4, !dbg !3981
  %39 = load i32, i32* %r1, align 4, !dbg !3990
  %40 = load i32, i32* %r, align 4, !dbg !3992
  %cmp43 = icmp slt i32 %39, %40, !dbg !3993
  br i1 %cmp43, label %if.then44, label %if.end45, !dbg !3994

if.then44:                                        ; preds = %if.then34
  %41 = load i32, i32* %r1, align 4, !dbg !3995
  store i32 %41, i32* %r, align 4, !dbg !3996
  br label %if.end45, !dbg !3997

if.end45:                                         ; preds = %if.then44, %if.then34
  br label %if.end46, !dbg !3998

if.end46:                                         ; preds = %if.end45, %for.body30
  br label %for.inc47, !dbg !3999

for.inc47:                                        ; preds = %if.end46
  %42 = load i32, i32* %i, align 4, !dbg !4000
  %inc48 = add nsw i32 %42, 1, !dbg !4000
  store i32 %inc48, i32* %i, align 4, !dbg !4000
  br label %for.cond28, !dbg !4002

for.end49:                                        ; preds = %for.cond28
  %43 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4003
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 16, !dbg !4004
  %first = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 0, !dbg !4005
  %44 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first, align 8, !dbg !4005
  store %struct.archive_read_passphrase* %44, %struct.archive_read_passphrase** %p, align 8, !dbg !4006
  br label %while.cond, !dbg !4007

while.cond:                                       ; preds = %while.body, %for.end49
  %45 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4008
  %cmp50 = icmp ne %struct.archive_read_passphrase* %45, null, !dbg !4009
  br i1 %cmp50, label %while.body, label %while.end, !dbg !4010

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %np, metadata !4011, metadata !401), !dbg !4013
  %46 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4014
  %next = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %46, i32 0, i32 1, !dbg !4015
  %47 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %next, align 8, !dbg !4015
  store %struct.archive_read_passphrase* %47, %struct.archive_read_passphrase** %np, align 8, !dbg !4013
  %48 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4016
  %passphrase = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %48, i32 0, i32 0, !dbg !4017
  %49 = load i8*, i8** %passphrase, align 8, !dbg !4017
  %50 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4018
  %passphrase51 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %50, i32 0, i32 0, !dbg !4019
  %51 = load i8*, i8** %passphrase51, align 8, !dbg !4019
  %call52 = call i64 @strlen(i8* %51) #9, !dbg !4020
  call void @llvm.memset.p0i8.i64(i8* %49, i8 0, i64 %call52, i32 1, i1 false), !dbg !4021
  %52 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4023
  %passphrase53 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %52, i32 0, i32 0, !dbg !4024
  %53 = load i8*, i8** %passphrase53, align 8, !dbg !4024
  call void @free(i8* %53) #7, !dbg !4025
  %54 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !4026
  %55 = bitcast %struct.archive_read_passphrase* %54 to i8*, !dbg !4026
  call void @free(i8* %55) #7, !dbg !4027
  %56 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %np, align 8, !dbg !4028
  store %struct.archive_read_passphrase* %56, %struct.archive_read_passphrase** %p, align 8, !dbg !4029
  br label %while.cond, !dbg !4030

while.end:                                        ; preds = %while.cond
  %57 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4032
  %archive54 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %57, i32 0, i32 0, !dbg !4033
  %error_string = getelementptr inbounds %struct.archive, %struct.archive* %archive54, i32 0, i32 10, !dbg !4034
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !4035
  %58 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4036
  %entry55 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %58, i32 0, i32 1, !dbg !4037
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry55, align 8, !dbg !4037
  call void @archive_entry_free(%struct.archive_entry* %59), !dbg !4038
  %60 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4039
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %60, i32 0, i32 0, !dbg !4040
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive56, i32 0, i32 0, !dbg !4041
  store i32 0, i32* %magic, align 8, !dbg !4042
  %61 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4043
  %archive57 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %61, i32 0, i32 0, !dbg !4044
  %call58 = call i32 @__archive_clean(%struct.archive* %archive57), !dbg !4045
  %62 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4046
  %client = getelementptr inbounds %struct.archive_read, %struct.archive_read* %62, i32 0, i32 5, !dbg !4047
  %dataset = getelementptr inbounds %struct.archive_read_client, %struct.archive_read_client* %client, i32 0, i32 9, !dbg !4048
  %63 = load %struct.archive_read_data_node*, %struct.archive_read_data_node** %dataset, align 8, !dbg !4048
  %64 = bitcast %struct.archive_read_data_node* %63 to i8*, !dbg !4046
  call void @free(i8* %64) #7, !dbg !4049
  %65 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4050
  %66 = bitcast %struct.archive_read* %65 to i8*, !dbg !4050
  call void @free(i8* %66) #7, !dbg !4051
  %67 = load i32, i32* %r, align 4, !dbg !4052
  store i32 %67, i32* %retval, align 4, !dbg !4053
  br label %return, !dbg !4053

return:                                           ; preds = %while.end, %if.then2, %if.then
  %68 = load i32, i32* %retval, align 4, !dbg !4054
  ret i32 %68, !dbg !4054
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_close(%struct.archive* %_a) #0 !dbg !383 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !4055, metadata !401), !dbg !4056
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !4057, metadata !401), !dbg !4058
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !4059
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !4060
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !4058
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4061, metadata !401), !dbg !4062
  store i32 0, i32* %r, align 4, !dbg !4062
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !4063, metadata !401), !dbg !4064
  store i32 0, i32* %r1, align 4, !dbg !4064
  br label %do.body, !dbg !4065

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !4066, metadata !401), !dbg !4068
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4069
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !4069
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 14594245, i32 65535, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.29, i32 0, i32 0)), !dbg !4069
  store i32 %call, i32* %magic_test, align 4, !dbg !4069
  %3 = load i32, i32* %magic_test, align 4, !dbg !4069
  %cmp = icmp eq i32 %3, -30, !dbg !4069
  br i1 %cmp, label %if.then, label %if.end, !dbg !4069

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !4071
  br label %return, !dbg !4071

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !4074

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4076
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !4078
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !4079
  %5 = load i32, i32* %state, align 4, !dbg !4079
  %cmp2 = icmp eq i32 %5, 32, !dbg !4080
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !4081

if.then3:                                         ; preds = %do.end
  store i32 0, i32* %retval, align 4, !dbg !4082
  br label %return, !dbg !4082

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4083
  %archive5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !4084
  call void @archive_clear_error(%struct.archive* %archive5), !dbg !4085
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4086
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !4087
  %state7 = getelementptr inbounds %struct.archive, %struct.archive* %archive6, i32 0, i32 1, !dbg !4088
  store i32 32, i32* %state7, align 4, !dbg !4089
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4090
  %call8 = call i32 @close_filters(%struct.archive_read* %8), !dbg !4091
  store i32 %call8, i32* %r1, align 4, !dbg !4092
  %9 = load i32, i32* %r1, align 4, !dbg !4093
  %10 = load i32, i32* %r, align 4, !dbg !4095
  %cmp9 = icmp slt i32 %9, %10, !dbg !4096
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !4097

if.then10:                                        ; preds = %if.end4
  %11 = load i32, i32* %r1, align 4, !dbg !4098
  store i32 %11, i32* %r, align 4, !dbg !4099
  br label %if.end11, !dbg !4100

if.end11:                                         ; preds = %if.then10, %if.end4
  %12 = load i32, i32* %r, align 4, !dbg !4101
  store i32 %12, i32* %retval, align 4, !dbg !4102
  br label %return, !dbg !4102

return:                                           ; preds = %if.end11, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !4103
  ret i32 %13, !dbg !4103
}

; Function Attrs: nounwind uwtable
define internal %struct.archive_read_filter* @get_filter(%struct.archive* %_a, i32 %n) #0 !dbg !373 {
entry:
  %retval = alloca %struct.archive_read_filter*, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %a = alloca %struct.archive_read*, align 8
  %f = alloca %struct.archive_read_filter*, align 8
  %last = alloca %struct.archive_read_filter*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !4104, metadata !401), !dbg !4105
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !4106, metadata !401), !dbg !4107
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !4108, metadata !401), !dbg !4109
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !4110
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !4111
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !4109
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %f, metadata !4112, metadata !401), !dbg !4113
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !4114
  %filter = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 7, !dbg !4115
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !4115
  store %struct.archive_read_filter* %3, %struct.archive_read_filter** %f, align 8, !dbg !4113
  %4 = load i32, i32* %n.addr, align 4, !dbg !4116
  %cmp = icmp eq i32 %4, -1, !dbg !4118
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !4119

land.lhs.true:                                    ; preds = %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4120
  %cmp1 = icmp ne %struct.archive_read_filter* %5, null, !dbg !4122
  br i1 %cmp1, label %if.then, label %if.end, !dbg !4123

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %last, metadata !4124, metadata !401), !dbg !4126
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4127
  store %struct.archive_read_filter* %6, %struct.archive_read_filter** %last, align 8, !dbg !4126
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4128
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 2, !dbg !4129
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !4129
  store %struct.archive_read_filter* %8, %struct.archive_read_filter** %f, align 8, !dbg !4130
  br label %while.cond, !dbg !4131

while.cond:                                       ; preds = %while.body, %if.then
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4132
  %cmp2 = icmp ne %struct.archive_read_filter* %9, null, !dbg !4134
  br i1 %cmp2, label %while.body, label %while.end, !dbg !4135

while.body:                                       ; preds = %while.cond
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4136
  store %struct.archive_read_filter* %10, %struct.archive_read_filter** %last, align 8, !dbg !4138
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4139
  %upstream3 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 2, !dbg !4140
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream3, align 8, !dbg !4140
  store %struct.archive_read_filter* %12, %struct.archive_read_filter** %f, align 8, !dbg !4141
  br label %while.cond, !dbg !4142

while.end:                                        ; preds = %while.cond
  %13 = load %struct.archive_read_filter*, %struct.archive_read_filter** %last, align 8, !dbg !4144
  store %struct.archive_read_filter* %13, %struct.archive_read_filter** %retval, align 8, !dbg !4145
  br label %return, !dbg !4145

if.end:                                           ; preds = %land.lhs.true, %entry
  %14 = load i32, i32* %n.addr, align 4, !dbg !4146
  %cmp4 = icmp slt i32 %14, 0, !dbg !4148
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !4149

if.then5:                                         ; preds = %if.end
  store %struct.archive_read_filter* null, %struct.archive_read_filter** %retval, align 8, !dbg !4150
  br label %return, !dbg !4150

if.end6:                                          ; preds = %if.end
  br label %while.cond7, !dbg !4151

while.cond7:                                      ; preds = %while.body10, %if.end6
  %15 = load i32, i32* %n.addr, align 4, !dbg !4152
  %cmp8 = icmp sgt i32 %15, 0, !dbg !4154
  br i1 %cmp8, label %land.rhs, label %land.end, !dbg !4155

land.rhs:                                         ; preds = %while.cond7
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4156
  %cmp9 = icmp ne %struct.archive_read_filter* %16, null, !dbg !4158
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond7
  %17 = phi i1 [ false, %while.cond7 ], [ %cmp9, %land.rhs ]
  br i1 %17, label %while.body10, label %while.end12, !dbg !4159

while.body10:                                     ; preds = %land.end
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4161
  %upstream11 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 2, !dbg !4163
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream11, align 8, !dbg !4163
  store %struct.archive_read_filter* %19, %struct.archive_read_filter** %f, align 8, !dbg !4164
  %20 = load i32, i32* %n.addr, align 4, !dbg !4165
  %dec = add nsw i32 %20, -1, !dbg !4165
  store i32 %dec, i32* %n.addr, align 4, !dbg !4165
  br label %while.cond7, !dbg !4166

while.end12:                                      ; preds = %land.end
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %f, align 8, !dbg !4168
  store %struct.archive_read_filter* %21, %struct.archive_read_filter** %retval, align 8, !dbg !4169
  br label %return, !dbg !4169

return:                                           ; preds = %while.end12, %if.then5, %while.end
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %retval, align 8, !dbg !4170
  ret %struct.archive_read_filter* %22, !dbg !4170
}

declare %struct.archive_entry* @archive_entry_clear(%struct.archive_entry*) #3

declare i32 @archive_read_close(%struct.archive*) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #5

declare void @archive_string_free(%struct.archive_string*) #3

declare void @archive_entry_free(%struct.archive_entry*) #3

declare i32 @__archive_clean(%struct.archive*) #3

; Function Attrs: noreturn
declare void @__archive_errx(i32, i8*) #6

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { noreturn }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!397, !398}
!llvm.ident = !{!399}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !292, globals: !394)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !122, !152, !24, !95, !52, !45, !291, !169, !80}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !6, line: 159, size: 20288, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !114, !158, !222, !223, !224, !225, !226, !227, !260, !262, !272, !273}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 160, baseType: !9, size: 1280, align: 64)
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
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!110 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 162, baseType: !30, size: 64, align: 64, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 165, baseType: !23, size: 32, align: 32, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 166, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 167, baseType: !52, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !5, file: !6, line: 170, baseType: !115, size: 576, align: 64, offset: 1536)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !6, line: 134, size: 576, align: 64, elements: !116)
!116 = !{!117, !123, !129, !135, !140, !143, !148, !149, !150, !151}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !115, file: !6, line: 135, baseType: !118, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !120)
!120 = !DISubroutineType(types: !121)
!121 = !{!23, !24, !122}
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !115, file: !6, line: 136, baseType: !124, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !32, line: 218, baseType: !126)
!126 = !DISubroutineType(types: !127)
!127 = !{!128, !24, !122, !64}
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !115, file: !6, line: 137, baseType: !130, size: 64, align: 64, offset: 128)
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !32, line: 226, baseType: !132)
!132 = !DISubroutineType(types: !133)
!133 = !{!134, !24, !122, !134}
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !115, file: !6, line: 138, baseType: !136, size: 64, align: 64, offset: 192)
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !32, line: 233, baseType: !138)
!138 = !DISubroutineType(types: !139)
!139 = !{!134, !24, !122, !134, !23}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !115, file: !6, line: 139, baseType: !141, size: 64, align: 64, offset: 256)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !120)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !115, file: !6, line: 140, baseType: !144, size: 64, align: 64, offset: 320)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !32, line: 249, baseType: !146)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !24, !122, !122}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !115, file: !6, line: 141, baseType: !13, size: 32, align: 32, offset: 384)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !115, file: !6, line: 142, baseType: !13, size: 32, align: 32, offset: 416)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !115, file: !6, line: 143, baseType: !52, size: 64, align: 64, offset: 448)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !115, file: !6, line: 144, baseType: !152, size: 64, align: 64, offset: 512)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !6, line: 129, size: 192, align: 64, elements: !154)
!154 = !{!155, !156, !157}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !153, file: !6, line: 130, baseType: !52, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !153, file: !6, line: 131, baseType: !52, size: 64, align: 64, offset: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !153, file: !6, line: 132, baseType: !122, size: 64, align: 64, offset: 128)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !5, file: !6, line: 173, baseType: !159, size: 6144, align: 64, offset: 2112)
!159 = !DICompositeType(tag: DW_TAG_array_type, baseType: !160, size: 6144, align: 64, elements: !220)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !6, line: 60, size: 384, align: 64, elements: !161)
!161 = !{!162, !163, !164, !211, !212, !216}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !160, file: !6, line: 62, baseType: !122, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !160, file: !6, line: 64, baseType: !80, size: 64, align: 64, offset: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !160, file: !6, line: 66, baseType: !165, size: 64, align: 64, offset: 128)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DISubroutineType(types: !167)
!167 = !{!23, !168, !169}
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!170 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !6, line: 82, size: 1408, align: 64, elements: !171)
!171 = !{!172, !173, !174, !175, !176, !180, !184, !188, !192, !193, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !170, file: !6, line: 83, baseType: !52, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !170, file: !6, line: 86, baseType: !168, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !170, file: !6, line: 87, baseType: !169, size: 64, align: 64, offset: 128)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !170, file: !6, line: 88, baseType: !4, size: 64, align: 64, offset: 192)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !170, file: !6, line: 90, baseType: !177, size: 64, align: 64, offset: 256)
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64, align: 64)
!178 = !DISubroutineType(types: !179)
!179 = !{!23, !169}
!180 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !170, file: !6, line: 92, baseType: !181, size: 64, align: 64, offset: 320)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DISubroutineType(types: !183)
!183 = !{!38, !169, !64}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !170, file: !6, line: 94, baseType: !185, size: 64, align: 64, offset: 384)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DISubroutineType(types: !187)
!187 = !{!52, !169, !52}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !170, file: !6, line: 96, baseType: !189, size: 64, align: 64, offset: 448)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DISubroutineType(types: !191)
!191 = !{!52, !169, !52, !23}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !170, file: !6, line: 98, baseType: !177, size: 64, align: 64, offset: 512)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !170, file: !6, line: 100, baseType: !194, size: 64, align: 64, offset: 576)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DISubroutineType(types: !196)
!196 = !{!23, !169, !13}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !170, file: !6, line: 102, baseType: !122, size: 64, align: 64, offset: 640)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !170, file: !6, line: 104, baseType: !80, size: 64, align: 64, offset: 704)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !170, file: !6, line: 105, baseType: !23, size: 32, align: 32, offset: 768)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !170, file: !6, line: 108, baseType: !95, size: 64, align: 64, offset: 832)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !170, file: !6, line: 109, baseType: !45, size: 64, align: 64, offset: 896)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !170, file: !6, line: 110, baseType: !95, size: 64, align: 64, offset: 960)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !170, file: !6, line: 111, baseType: !45, size: 64, align: 64, offset: 1024)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !170, file: !6, line: 112, baseType: !43, size: 64, align: 64, offset: 1088)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !170, file: !6, line: 113, baseType: !45, size: 64, align: 64, offset: 1152)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !170, file: !6, line: 114, baseType: !80, size: 64, align: 64, offset: 1216)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !170, file: !6, line: 115, baseType: !45, size: 64, align: 64, offset: 1280)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !170, file: !6, line: 116, baseType: !82, size: 8, align: 8, offset: 1344)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !170, file: !6, line: 117, baseType: !82, size: 8, align: 8, offset: 1352)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !170, file: !6, line: 118, baseType: !82, size: 8, align: 8, offset: 1360)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !160, file: !6, line: 69, baseType: !177, size: 64, align: 64, offset: 192)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !160, file: !6, line: 71, baseType: !213, size: 64, align: 64, offset: 256)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!23, !168, !80, !80}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !160, file: !6, line: 74, baseType: !217, size: 64, align: 64, offset: 320)
!217 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!218 = !DISubroutineType(types: !219)
!219 = !{!23, !168}
!220 = !{!221}
!221 = !DISubrange(count: 16)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !5, file: !6, line: 176, baseType: !169, size: 64, align: 64, offset: 8256)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !5, file: !6, line: 179, baseType: !23, size: 32, align: 32, offset: 8320)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !5, file: !6, line: 182, baseType: !52, size: 64, align: 64, offset: 8384)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !5, file: !6, line: 185, baseType: !13, size: 32, align: 32, offset: 8448)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !5, file: !6, line: 186, baseType: !13, size: 32, align: 32, offset: 8480)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !5, file: !6, line: 209, baseType: !228, size: 11264, align: 64, offset: 8512)
!228 = !DICompositeType(tag: DW_TAG_array_type, baseType: !229, size: 11264, align: 64, elements: !220)
!229 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !6, line: 196, size: 704, align: 64, elements: !230)
!230 = !{!231, !232, !233, !237, !241, !245, !249, !253, !257, !258, !259}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !229, file: !6, line: 197, baseType: !122, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !229, file: !6, line: 198, baseType: !80, size: 64, align: 64, offset: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !229, file: !6, line: 199, baseType: !234, size: 64, align: 64, offset: 128)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{!23, !4, !23}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !229, file: !6, line: 200, baseType: !238, size: 64, align: 64, offset: 192)
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!239 = !DISubroutineType(types: !240)
!240 = !{!23, !4, !80, !80}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !229, file: !6, line: 202, baseType: !242, size: 64, align: 64, offset: 256)
!242 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !243, size: 64, align: 64)
!243 = !DISubroutineType(types: !244)
!244 = !{!23, !4, !30}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !229, file: !6, line: 203, baseType: !246, size: 64, align: 64, offset: 320)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DISubroutineType(types: !248)
!248 = !{!23, !4, !64, !65, !66}
!249 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !229, file: !6, line: 204, baseType: !250, size: 64, align: 64, offset: 384)
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64, align: 64)
!251 = !DISubroutineType(types: !252)
!252 = !{!23, !4}
!253 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !229, file: !6, line: 205, baseType: !254, size: 64, align: 64, offset: 448)
!254 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !255, size: 64, align: 64)
!255 = !DISubroutineType(types: !256)
!256 = !{!52, !4, !52, !23}
!257 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !229, file: !6, line: 206, baseType: !250, size: 64, align: 64, offset: 512)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !229, file: !6, line: 207, baseType: !250, size: 64, align: 64, offset: 576)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !229, file: !6, line: 208, baseType: !250, size: 64, align: 64, offset: 640)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !5, file: !6, line: 210, baseType: !261, size: 64, align: 64, offset: 19776)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !5, file: !6, line: 215, baseType: !263, size: 64, align: 64, offset: 19840)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !6, line: 151, size: 192, align: 64, elements: !265)
!265 = !{!266, !267, !271}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !264, file: !6, line: 152, baseType: !24, size: 64, align: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !264, file: !6, line: 155, baseType: !268, size: 64, align: 64, offset: 64)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DISubroutineType(types: !270)
!270 = !{null, !122}
!271 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !264, file: !6, line: 156, baseType: !122, size: 64, align: 64, offset: 128)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !5, file: !6, line: 216, baseType: !250, size: 64, align: 64, offset: 19904)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !5, file: !6, line: 227, baseType: !274, size: 320, align: 64, offset: 19968)
!274 = !DICompositeType(tag: DW_TAG_structure_type, scope: !5, file: !6, line: 221, size: 320, align: 64, elements: !275)
!275 = !{!276, !282, !284, !285, !290}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !274, file: !6, line: 222, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !6, line: 146, size: 128, align: 64, elements: !279)
!279 = !{!280, !281}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !278, file: !6, line: 147, baseType: !95, size: 64, align: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !278, file: !6, line: 148, baseType: !277, size: 64, align: 64, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !274, file: !6, line: 223, baseType: !283, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !274, file: !6, line: 224, baseType: !23, size: 32, align: 32, offset: 128)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !274, file: !6, line: 225, baseType: !286, size: 64, align: 64, offset: 192)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !288)
!288 = !DISubroutineType(types: !289)
!289 = !{!80, !24, !122}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !274, file: !6, line: 226, baseType: !122, size: 64, align: 64, offset: 256)
!291 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !53, line: 134, baseType: !42)
!292 = !{!293, !296, !299, !302, !305, !308, !311, !314, !317, !320, !323, !324, !327, !328, !329, !330, !331, !334, !335, !336, !339, !342, !343, !346, !349, !352, !356, !360, !363, !366, !367, !368, !369, !372, !373, !376, !377, !378, !379, !380, !381, !382, !383, !384, !385, !386, !387, !388, !389, !390, !391, !392, !393}
!293 = distinct !DISubprogram(name: "archive_read_new", scope: !1, file: !1, line: 101, type: !294, isLocal: false, isDefinition: true, scopeLine: 102, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!294 = !DISubroutineType(types: !295)
!295 = !{!24}
!296 = distinct !DISubprogram(name: "archive_read_extract_set_skip_file", scope: !1, file: !1, line: 123, type: !297, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!297 = !DISubroutineType(types: !298)
!298 = !{null, !24, !52, !52}
!299 = distinct !DISubprogram(name: "archive_read_open", scope: !1, file: !1, line: 139, type: !300, isLocal: false, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!300 = !DISubroutineType(types: !301)
!301 = !{!23, !24, !122, !118, !124, !141}
!302 = distinct !DISubprogram(name: "archive_read_open2", scope: !1, file: !1, line: 154, type: !303, isLocal: false, isDefinition: true, scopeLine: 159, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!303 = !DISubroutineType(types: !304)
!304 = !{!23, !24, !122, !118, !124, !130, !141}
!305 = distinct !DISubprogram(name: "archive_read_set_open_callback", scope: !1, file: !1, line: 308, type: !306, isLocal: false, isDefinition: true, scopeLine: 310, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!306 = !DISubroutineType(types: !307)
!307 = !{!23, !24, !118}
!308 = distinct !DISubprogram(name: "archive_read_set_read_callback", scope: !1, file: !1, line: 319, type: !309, isLocal: false, isDefinition: true, scopeLine: 321, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!309 = !DISubroutineType(types: !310)
!310 = !{!23, !24, !124}
!311 = distinct !DISubprogram(name: "archive_read_set_skip_callback", scope: !1, file: !1, line: 330, type: !312, isLocal: false, isDefinition: true, scopeLine: 332, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!312 = !DISubroutineType(types: !313)
!313 = !{!23, !24, !130}
!314 = distinct !DISubprogram(name: "archive_read_set_seek_callback", scope: !1, file: !1, line: 341, type: !315, isLocal: false, isDefinition: true, scopeLine: 343, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!315 = !DISubroutineType(types: !316)
!316 = !{!23, !24, !136}
!317 = distinct !DISubprogram(name: "archive_read_set_close_callback", scope: !1, file: !1, line: 352, type: !318, isLocal: false, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!318 = !DISubroutineType(types: !319)
!319 = !{!23, !24, !141}
!320 = distinct !DISubprogram(name: "archive_read_set_switch_callback", scope: !1, file: !1, line: 363, type: !321, isLocal: false, isDefinition: true, scopeLine: 365, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!321 = !DISubroutineType(types: !322)
!322 = !{!23, !24, !144}
!323 = distinct !DISubprogram(name: "archive_read_set_callback_data", scope: !1, file: !1, line: 374, type: !120, isLocal: false, isDefinition: true, scopeLine: 375, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!324 = distinct !DISubprogram(name: "archive_read_set_callback_data2", scope: !1, file: !1, line: 380, type: !325, isLocal: false, isDefinition: true, scopeLine: 382, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!325 = !DISubroutineType(types: !326)
!326 = !{!23, !24, !122, !13}
!327 = distinct !DISubprogram(name: "archive_read_add_callback_data", scope: !1, file: !1, line: 413, type: !325, isLocal: false, isDefinition: true, scopeLine: 415, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!328 = distinct !DISubprogram(name: "archive_read_append_callback_data", scope: !1, file: !1, line: 447, type: !120, isLocal: false, isDefinition: true, scopeLine: 448, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = distinct !DISubprogram(name: "archive_read_prepend_callback_data", scope: !1, file: !1, line: 454, type: !120, isLocal: false, isDefinition: true, scopeLine: 455, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = distinct !DISubprogram(name: "archive_read_open1", scope: !1, file: !1, line: 460, type: !21, isLocal: false, isDefinition: true, scopeLine: 461, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!331 = distinct !DISubprogram(name: "archive_read_header_position", scope: !1, file: !1, line: 751, type: !332, isLocal: false, isDefinition: true, scopeLine: 752, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = !DISubroutineType(types: !333)
!333 = !{!134, !24}
!334 = distinct !DISubprogram(name: "archive_read_has_encrypted_entries", scope: !1, file: !1, line: 778, type: !21, isLocal: false, isDefinition: true, scopeLine: 779, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!335 = distinct !DISubprogram(name: "archive_read_format_capabilities", scope: !1, file: !1, line: 803, type: !21, isLocal: false, isDefinition: true, scopeLine: 804, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!336 = distinct !DISubprogram(name: "archive_read_data", scope: !1, file: !1, line: 824, type: !337, isLocal: false, isDefinition: true, scopeLine: 825, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!337 = !DISubroutineType(types: !338)
!338 = !{!128, !24, !122, !45}
!339 = distinct !DISubprogram(name: "__archive_reset_read_data", scope: !1, file: !1, line: 902, type: !340, isLocal: false, isDefinition: true, scopeLine: 903, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = !DISubroutineType(types: !341)
!341 = !{null, !24}
!342 = distinct !DISubprogram(name: "archive_read_data_skip", scope: !1, file: !1, line: 918, type: !21, isLocal: false, isDefinition: true, scopeLine: 919, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = distinct !DISubprogram(name: "archive_seek_data", scope: !1, file: !1, line: 946, type: !344, isLocal: false, isDefinition: true, scopeLine: 947, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = !DISubroutineType(types: !345)
!345 = !{!134, !24, !52, !23}
!346 = distinct !DISubprogram(name: "__archive_read_free_filters", scope: !1, file: !1, line: 1010, type: !347, isLocal: false, isDefinition: true, scopeLine: 1011, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!347 = !DISubroutineType(types: !348)
!348 = !{null, !4}
!349 = distinct !DISubprogram(name: "__archive_read_register_format", scope: !1, file: !1, line: 1181, type: !350, isLocal: false, isDefinition: true, scopeLine: 1193, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = !DISubroutineType(types: !351)
!351 = !{!23, !4, !122, !80, !234, !238, !242, !246, !250, !254, !250, !250, !250}
!352 = distinct !DISubprogram(name: "__archive_read_get_bidder", scope: !1, file: !1, line: 1231, type: !353, isLocal: false, isDefinition: true, scopeLine: 1233, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!353 = !DISubroutineType(types: !354)
!354 = !{!23, !4, !355}
!355 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!356 = distinct !DISubprogram(name: "__archive_read_ahead", scope: !1, file: !1, line: 1303, type: !357, isLocal: false, isDefinition: true, scopeLine: 1304, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!357 = !DISubroutineType(types: !358)
!358 = !{!43, !4, !45, !359}
!359 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!360 = distinct !DISubprogram(name: "__archive_read_filter_ahead", scope: !1, file: !1, line: 1309, type: !361, isLocal: false, isDefinition: true, scopeLine: 1311, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!361 = !DISubroutineType(types: !362)
!362 = !{!43, !169, !45, !359}
!363 = distinct !DISubprogram(name: "__archive_read_consume", scope: !1, file: !1, line: 1483, type: !364, isLocal: false, isDefinition: true, scopeLine: 1484, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!364 = !DISubroutineType(types: !365)
!365 = !{!52, !4, !52}
!366 = distinct !DISubprogram(name: "__archive_read_filter_consume", scope: !1, file: !1, line: 1489, type: !186, isLocal: false, isDefinition: true, scopeLine: 1491, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!367 = distinct !DISubprogram(name: "__archive_read_seek", scope: !1, file: !1, line: 1606, type: !255, isLocal: false, isDefinition: true, scopeLine: 1607, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!368 = distinct !DISubprogram(name: "__archive_read_filter_seek", scope: !1, file: !1, line: 1612, type: !190, isLocal: false, isDefinition: true, scopeLine: 1614, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!369 = distinct !DISubprogram(name: "archive_read_vtable", scope: !1, file: !1, line: 77, type: !370, isLocal: true, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!370 = !DISubroutineType(types: !371)
!371 = !{!16}
!372 = distinct !DISubprogram(name: "_archive_filter_bytes", scope: !1, file: !1, line: 1170, type: !70, isLocal: true, isDefinition: true, scopeLine: 1171, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!373 = distinct !DISubprogram(name: "get_filter", scope: !1, file: !1, line: 1131, type: !374, isLocal: true, isDefinition: true, scopeLine: 1132, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!374 = !DISubroutineType(types: !375)
!375 = !{!169, !24, !23}
!376 = distinct !DISubprogram(name: "_archive_filter_code", scope: !1, file: !1, line: 1156, type: !74, isLocal: true, isDefinition: true, scopeLine: 1157, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!377 = distinct !DISubprogram(name: "_archive_filter_name", scope: !1, file: !1, line: 1163, type: !78, isLocal: true, isDefinition: true, scopeLine: 1164, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!378 = distinct !DISubprogram(name: "_archive_filter_count", scope: !1, file: !1, line: 1026, type: !21, isLocal: true, isDefinition: true, scopeLine: 1027, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!379 = distinct !DISubprogram(name: "_archive_read_data_block", scope: !1, file: !1, line: 971, type: !62, isLocal: true, isDefinition: true, scopeLine: 973, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!380 = distinct !DISubprogram(name: "_archive_read_next_header", scope: !1, file: !1, line: 681, type: !56, isLocal: true, isDefinition: true, scopeLine: 682, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!381 = distinct !DISubprogram(name: "_archive_read_next_header2", scope: !1, file: !1, line: 617, type: !28, isLocal: true, isDefinition: true, scopeLine: 618, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!382 = distinct !DISubprogram(name: "_archive_read_free", scope: !1, file: !1, line: 1068, type: !21, isLocal: true, isDefinition: true, scopeLine: 1069, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = distinct !DISubprogram(name: "_archive_read_close", scope: !1, file: !1, line: 1042, type: !21, isLocal: true, isDefinition: true, scopeLine: 1043, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!384 = distinct !DISubprogram(name: "client_open_proxy", scope: !1, file: !1, line: 266, type: !178, isLocal: true, isDefinition: true, scopeLine: 267, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!385 = distinct !DISubprogram(name: "client_read_proxy", scope: !1, file: !1, line: 171, type: !182, isLocal: true, isDefinition: true, scopeLine: 172, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!386 = distinct !DISubprogram(name: "client_skip_proxy", scope: !1, file: !1, line: 180, type: !186, isLocal: true, isDefinition: true, scopeLine: 181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!387 = distinct !DISubprogram(name: "client_seek_proxy", scope: !1, file: !1, line: 230, type: !190, isLocal: true, isDefinition: true, scopeLine: 231, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!388 = distinct !DISubprogram(name: "client_close_proxy", scope: !1, file: !1, line: 247, type: !178, isLocal: true, isDefinition: true, scopeLine: 248, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!389 = distinct !DISubprogram(name: "client_switch_proxy", scope: !1, file: !1, line: 276, type: !195, isLocal: true, isDefinition: true, scopeLine: 277, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!390 = distinct !DISubprogram(name: "choose_filters", scope: !1, file: !1, line: 556, type: !251, isLocal: true, isDefinition: true, scopeLine: 557, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!391 = distinct !DISubprogram(name: "choose_format", scope: !1, file: !1, line: 696, type: !251, isLocal: true, isDefinition: true, scopeLine: 697, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!392 = distinct !DISubprogram(name: "close_filters", scope: !1, file: !1, line: 989, type: !251, isLocal: true, isDefinition: true, scopeLine: 990, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!393 = distinct !DISubprogram(name: "advance_file_pointer", scope: !1, file: !1, line: 1519, type: !186, isLocal: true, isDefinition: true, scopeLine: 1520, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!394 = !{!395, !396}
!395 = !DIGlobalVariable(name: "av", scope: !369, file: !1, line: 79, type: !17, isLocal: true, isDefinition: true, variable: %struct.archive_vtable* @archive_read_vtable.av)
!396 = !DIGlobalVariable(name: "inited", scope: !369, file: !1, line: 80, type: !23, isLocal: true, isDefinition: true, variable: i32* @archive_read_vtable.inited)
!397 = !{i32 2, !"Dwarf Version", i32 4}
!398 = !{i32 2, !"Debug Info Version", i32 3}
!399 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!400 = !DILocalVariable(name: "a", scope: !293, file: !1, line: 103, type: !4)
!401 = !DIExpression()
!402 = !DILocation(line: 103, column: 23, scope: !293)
!403 = !DILocation(line: 105, column: 29, scope: !293)
!404 = !DILocation(line: 105, column: 6, scope: !293)
!405 = !DILocation(line: 105, column: 4, scope: !293)
!406 = !DILocation(line: 106, column: 6, scope: !407)
!407 = distinct !DILexicalBlock(scope: !293, file: !1, line: 106, column: 6)
!408 = !DILocation(line: 106, column: 8, scope: !407)
!409 = !DILocation(line: 106, column: 6, scope: !293)
!410 = !DILocation(line: 107, column: 3, scope: !407)
!411 = !DILocation(line: 108, column: 2, scope: !293)
!412 = !DILocation(line: 108, column: 5, scope: !293)
!413 = !DILocation(line: 108, column: 13, scope: !293)
!414 = !DILocation(line: 108, column: 19, scope: !293)
!415 = !DILocation(line: 110, column: 2, scope: !293)
!416 = !DILocation(line: 110, column: 5, scope: !293)
!417 = !DILocation(line: 110, column: 13, scope: !293)
!418 = !DILocation(line: 110, column: 19, scope: !293)
!419 = !DILocation(line: 111, column: 33, scope: !293)
!420 = !DILocation(line: 111, column: 36, scope: !293)
!421 = !DILocation(line: 111, column: 13, scope: !293)
!422 = !DILocation(line: 111, column: 2, scope: !293)
!423 = !DILocation(line: 111, column: 5, scope: !293)
!424 = !DILocation(line: 111, column: 11, scope: !293)
!425 = !DILocation(line: 112, column: 22, scope: !293)
!426 = !DILocation(line: 112, column: 2, scope: !293)
!427 = !DILocation(line: 112, column: 5, scope: !293)
!428 = !DILocation(line: 112, column: 13, scope: !293)
!429 = !DILocation(line: 112, column: 20, scope: !293)
!430 = !DILocation(line: 114, column: 25, scope: !293)
!431 = !DILocation(line: 114, column: 28, scope: !293)
!432 = !DILocation(line: 114, column: 40, scope: !293)
!433 = !DILocation(line: 114, column: 2, scope: !293)
!434 = !DILocation(line: 114, column: 5, scope: !293)
!435 = !DILocation(line: 114, column: 17, scope: !293)
!436 = !DILocation(line: 114, column: 22, scope: !293)
!437 = !DILocation(line: 116, column: 11, scope: !293)
!438 = !DILocation(line: 116, column: 14, scope: !293)
!439 = !DILocation(line: 116, column: 2, scope: !293)
!440 = !DILocation(line: 117, column: 1, scope: !293)
!441 = !DILocation(line: 82, column: 7, scope: !442)
!442 = distinct !DILexicalBlock(scope: !369, file: !1, line: 82, column: 6)
!443 = !DILocation(line: 82, column: 6, scope: !369)
!444 = !DILocation(line: 83, column: 27, scope: !445)
!445 = distinct !DILexicalBlock(scope: !442, file: !1, line: 82, column: 15)
!446 = !DILocation(line: 84, column: 26, scope: !445)
!447 = !DILocation(line: 85, column: 26, scope: !445)
!448 = !DILocation(line: 86, column: 27, scope: !445)
!449 = !DILocation(line: 87, column: 30, scope: !445)
!450 = !DILocation(line: 88, column: 31, scope: !445)
!451 = !DILocation(line: 89, column: 32, scope: !445)
!452 = !DILocation(line: 90, column: 19, scope: !445)
!453 = !DILocation(line: 91, column: 20, scope: !445)
!454 = !DILocation(line: 92, column: 10, scope: !445)
!455 = !DILocation(line: 93, column: 2, scope: !445)
!456 = !DILocation(line: 94, column: 2, scope: !369)
!457 = !DILocalVariable(name: "_a", arg: 1, scope: !296, file: !1, line: 123, type: !24)
!458 = !DILocation(line: 123, column: 52, scope: !296)
!459 = !DILocalVariable(name: "d", arg: 2, scope: !296, file: !1, line: 123, type: !52)
!460 = !DILocation(line: 123, column: 64, scope: !296)
!461 = !DILocalVariable(name: "i", arg: 3, scope: !296, file: !1, line: 123, type: !52)
!462 = !DILocation(line: 123, column: 75, scope: !296)
!463 = !DILocalVariable(name: "a", scope: !296, file: !1, line: 125, type: !4)
!464 = !DILocation(line: 125, column: 23, scope: !296)
!465 = !DILocation(line: 125, column: 50, scope: !296)
!466 = !DILocation(line: 125, column: 27, scope: !296)
!467 = !DILocation(line: 127, column: 42, scope: !468)
!468 = distinct !DILexicalBlock(scope: !296, file: !1, line: 127, column: 6)
!469 = !DILocation(line: 127, column: 20, scope: !468)
!470 = !DILocation(line: 127, column: 17, scope: !468)
!471 = !DILocation(line: 127, column: 6, scope: !296)
!472 = !DILocation(line: 129, column: 3, scope: !468)
!473 = !DILocation(line: 130, column: 2, scope: !296)
!474 = !DILocation(line: 130, column: 5, scope: !296)
!475 = !DILocation(line: 130, column: 19, scope: !296)
!476 = !DILocation(line: 131, column: 21, scope: !296)
!477 = !DILocation(line: 131, column: 2, scope: !296)
!478 = !DILocation(line: 131, column: 5, scope: !296)
!479 = !DILocation(line: 131, column: 19, scope: !296)
!480 = !DILocation(line: 132, column: 21, scope: !296)
!481 = !DILocation(line: 132, column: 2, scope: !296)
!482 = !DILocation(line: 132, column: 5, scope: !296)
!483 = !DILocation(line: 132, column: 19, scope: !296)
!484 = !DILocation(line: 133, column: 1, scope: !296)
!485 = !DILocation(line: 133, column: 1, scope: !486)
!486 = !DILexicalBlockFile(scope: !296, file: !1, discriminator: 1)
!487 = !DILocalVariable(name: "a", arg: 1, scope: !299, file: !1, line: 139, type: !24)
!488 = !DILocation(line: 139, column: 35, scope: !299)
!489 = !DILocalVariable(name: "client_data", arg: 2, scope: !299, file: !1, line: 139, type: !122)
!490 = !DILocation(line: 139, column: 44, scope: !299)
!491 = !DILocalVariable(name: "client_opener", arg: 3, scope: !299, file: !1, line: 140, type: !118)
!492 = !DILocation(line: 140, column: 28, scope: !299)
!493 = !DILocalVariable(name: "client_reader", arg: 4, scope: !299, file: !1, line: 140, type: !124)
!494 = !DILocation(line: 140, column: 66, scope: !299)
!495 = !DILocalVariable(name: "client_closer", arg: 5, scope: !299, file: !1, line: 141, type: !141)
!496 = !DILocation(line: 141, column: 29, scope: !299)
!497 = !DILocation(line: 145, column: 33, scope: !299)
!498 = !DILocation(line: 145, column: 36, scope: !299)
!499 = !DILocation(line: 145, column: 2, scope: !299)
!500 = !DILocation(line: 146, column: 33, scope: !299)
!501 = !DILocation(line: 146, column: 36, scope: !299)
!502 = !DILocation(line: 146, column: 2, scope: !299)
!503 = !DILocation(line: 147, column: 34, scope: !299)
!504 = !DILocation(line: 147, column: 37, scope: !299)
!505 = !DILocation(line: 147, column: 2, scope: !299)
!506 = !DILocation(line: 148, column: 33, scope: !299)
!507 = !DILocation(line: 148, column: 36, scope: !299)
!508 = !DILocation(line: 148, column: 2, scope: !299)
!509 = !DILocation(line: 149, column: 28, scope: !299)
!510 = !DILocation(line: 149, column: 9, scope: !299)
!511 = !DILocation(line: 149, column: 2, scope: !299)
!512 = !DILocalVariable(name: "_a", arg: 1, scope: !305, file: !1, line: 308, type: !24)
!513 = !DILocation(line: 308, column: 48, scope: !305)
!514 = !DILocalVariable(name: "client_opener", arg: 2, scope: !305, file: !1, line: 309, type: !118)
!515 = !DILocation(line: 309, column: 28, scope: !305)
!516 = !DILocalVariable(name: "a", scope: !305, file: !1, line: 311, type: !4)
!517 = !DILocation(line: 311, column: 23, scope: !305)
!518 = !DILocation(line: 311, column: 50, scope: !305)
!519 = !DILocation(line: 311, column: 27, scope: !305)
!520 = !DILocation(line: 312, column: 2, scope: !305)
!521 = !DILocalVariable(name: "magic_test", scope: !522, file: !1, line: 312, type: !23)
!522 = distinct !DILexicalBlock(scope: !305, file: !1, line: 312, column: 2)
!523 = !DILocation(line: 312, column: 2, scope: !522)
!524 = !DILocation(line: 312, column: 2, scope: !525)
!525 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!526 = !DILocation(line: 312, column: 2, scope: !527)
!527 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 2)
!528 = distinct !DILexicalBlock(scope: !522, file: !1, line: 312, column: 2)
!529 = !DILocation(line: 312, column: 2, scope: !530)
!530 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 3)
!531 = !DILocation(line: 314, column: 21, scope: !305)
!532 = !DILocation(line: 314, column: 2, scope: !305)
!533 = !DILocation(line: 314, column: 5, scope: !305)
!534 = !DILocation(line: 314, column: 12, scope: !305)
!535 = !DILocation(line: 314, column: 19, scope: !305)
!536 = !DILocation(line: 315, column: 2, scope: !305)
!537 = !DILocation(line: 316, column: 1, scope: !305)
!538 = !DILocalVariable(name: "_a", arg: 1, scope: !308, file: !1, line: 319, type: !24)
!539 = !DILocation(line: 319, column: 48, scope: !308)
!540 = !DILocalVariable(name: "client_reader", arg: 2, scope: !308, file: !1, line: 320, type: !124)
!541 = !DILocation(line: 320, column: 28, scope: !308)
!542 = !DILocalVariable(name: "a", scope: !308, file: !1, line: 322, type: !4)
!543 = !DILocation(line: 322, column: 23, scope: !308)
!544 = !DILocation(line: 322, column: 50, scope: !308)
!545 = !DILocation(line: 322, column: 27, scope: !308)
!546 = !DILocation(line: 323, column: 2, scope: !308)
!547 = !DILocalVariable(name: "magic_test", scope: !548, file: !1, line: 323, type: !23)
!548 = distinct !DILexicalBlock(scope: !308, file: !1, line: 323, column: 2)
!549 = !DILocation(line: 323, column: 2, scope: !548)
!550 = !DILocation(line: 323, column: 2, scope: !551)
!551 = !DILexicalBlockFile(scope: !548, file: !1, discriminator: 1)
!552 = !DILocation(line: 323, column: 2, scope: !553)
!553 = !DILexicalBlockFile(scope: !554, file: !1, discriminator: 2)
!554 = distinct !DILexicalBlock(scope: !548, file: !1, line: 323, column: 2)
!555 = !DILocation(line: 323, column: 2, scope: !556)
!556 = !DILexicalBlockFile(scope: !548, file: !1, discriminator: 3)
!557 = !DILocation(line: 325, column: 21, scope: !308)
!558 = !DILocation(line: 325, column: 2, scope: !308)
!559 = !DILocation(line: 325, column: 5, scope: !308)
!560 = !DILocation(line: 325, column: 12, scope: !308)
!561 = !DILocation(line: 325, column: 19, scope: !308)
!562 = !DILocation(line: 326, column: 2, scope: !308)
!563 = !DILocation(line: 327, column: 1, scope: !308)
!564 = !DILocalVariable(name: "_a", arg: 1, scope: !317, file: !1, line: 352, type: !24)
!565 = !DILocation(line: 352, column: 49, scope: !317)
!566 = !DILocalVariable(name: "client_closer", arg: 2, scope: !317, file: !1, line: 353, type: !141)
!567 = !DILocation(line: 353, column: 29, scope: !317)
!568 = !DILocalVariable(name: "a", scope: !317, file: !1, line: 355, type: !4)
!569 = !DILocation(line: 355, column: 23, scope: !317)
!570 = !DILocation(line: 355, column: 50, scope: !317)
!571 = !DILocation(line: 355, column: 27, scope: !317)
!572 = !DILocation(line: 356, column: 2, scope: !317)
!573 = !DILocalVariable(name: "magic_test", scope: !574, file: !1, line: 356, type: !23)
!574 = distinct !DILexicalBlock(scope: !317, file: !1, line: 356, column: 2)
!575 = !DILocation(line: 356, column: 2, scope: !574)
!576 = !DILocation(line: 356, column: 2, scope: !577)
!577 = !DILexicalBlockFile(scope: !574, file: !1, discriminator: 1)
!578 = !DILocation(line: 356, column: 2, scope: !579)
!579 = !DILexicalBlockFile(scope: !580, file: !1, discriminator: 2)
!580 = distinct !DILexicalBlock(scope: !574, file: !1, line: 356, column: 2)
!581 = !DILocation(line: 356, column: 2, scope: !582)
!582 = !DILexicalBlockFile(scope: !574, file: !1, discriminator: 3)
!583 = !DILocation(line: 358, column: 21, scope: !317)
!584 = !DILocation(line: 358, column: 2, scope: !317)
!585 = !DILocation(line: 358, column: 5, scope: !317)
!586 = !DILocation(line: 358, column: 12, scope: !317)
!587 = !DILocation(line: 358, column: 19, scope: !317)
!588 = !DILocation(line: 359, column: 2, scope: !317)
!589 = !DILocation(line: 360, column: 1, scope: !317)
!590 = !DILocalVariable(name: "_a", arg: 1, scope: !323, file: !1, line: 374, type: !24)
!591 = !DILocation(line: 374, column: 48, scope: !323)
!592 = !DILocalVariable(name: "client_data", arg: 2, scope: !323, file: !1, line: 374, type: !122)
!593 = !DILocation(line: 374, column: 58, scope: !323)
!594 = !DILocation(line: 376, column: 41, scope: !323)
!595 = !DILocation(line: 376, column: 45, scope: !323)
!596 = !DILocation(line: 376, column: 9, scope: !323)
!597 = !DILocation(line: 376, column: 2, scope: !323)
!598 = !DILocalVariable(name: "_a", arg: 1, scope: !330, file: !1, line: 460, type: !24)
!599 = !DILocation(line: 460, column: 36, scope: !330)
!600 = !DILocalVariable(name: "a", scope: !330, file: !1, line: 462, type: !4)
!601 = !DILocation(line: 462, column: 23, scope: !330)
!602 = !DILocation(line: 462, column: 50, scope: !330)
!603 = !DILocation(line: 462, column: 27, scope: !330)
!604 = !DILocalVariable(name: "filter", scope: !330, file: !1, line: 463, type: !169)
!605 = !DILocation(line: 463, column: 30, scope: !330)
!606 = !DILocalVariable(name: "tmp", scope: !330, file: !1, line: 463, type: !169)
!607 = !DILocation(line: 463, column: 39, scope: !330)
!608 = !DILocalVariable(name: "slot", scope: !330, file: !1, line: 464, type: !23)
!609 = !DILocation(line: 464, column: 6, scope: !330)
!610 = !DILocalVariable(name: "e", scope: !330, file: !1, line: 464, type: !23)
!611 = !DILocation(line: 464, column: 12, scope: !330)
!612 = !DILocalVariable(name: "i", scope: !330, file: !1, line: 465, type: !13)
!613 = !DILocation(line: 465, column: 15, scope: !330)
!614 = !DILocation(line: 467, column: 2, scope: !330)
!615 = !DILocalVariable(name: "magic_test", scope: !616, file: !1, line: 467, type: !23)
!616 = distinct !DILexicalBlock(scope: !330, file: !1, line: 467, column: 2)
!617 = !DILocation(line: 467, column: 2, scope: !616)
!618 = !DILocation(line: 467, column: 2, scope: !619)
!619 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 1)
!620 = !DILocation(line: 467, column: 2, scope: !621)
!621 = !DILexicalBlockFile(scope: !622, file: !1, discriminator: 2)
!622 = distinct !DILexicalBlock(scope: !616, file: !1, line: 467, column: 2)
!623 = !DILocation(line: 467, column: 2, scope: !624)
!624 = !DILexicalBlockFile(scope: !616, file: !1, discriminator: 3)
!625 = !DILocation(line: 469, column: 23, scope: !330)
!626 = !DILocation(line: 469, column: 26, scope: !330)
!627 = !DILocation(line: 469, column: 2, scope: !330)
!628 = !DILocation(line: 471, column: 6, scope: !629)
!629 = distinct !DILexicalBlock(scope: !330, file: !1, line: 471, column: 6)
!630 = !DILocation(line: 471, column: 9, scope: !629)
!631 = !DILocation(line: 471, column: 16, scope: !629)
!632 = !DILocation(line: 471, column: 23, scope: !629)
!633 = !DILocation(line: 471, column: 6, scope: !330)
!634 = !DILocation(line: 472, column: 22, scope: !635)
!635 = distinct !DILexicalBlock(scope: !629, file: !1, line: 471, column: 32)
!636 = !DILocation(line: 472, column: 25, scope: !635)
!637 = !DILocation(line: 472, column: 3, scope: !635)
!638 = !DILocation(line: 474, column: 3, scope: !635)
!639 = !DILocation(line: 474, column: 6, scope: !635)
!640 = !DILocation(line: 474, column: 14, scope: !635)
!641 = !DILocation(line: 474, column: 20, scope: !635)
!642 = !DILocation(line: 475, column: 3, scope: !635)
!643 = !DILocation(line: 479, column: 6, scope: !644)
!644 = distinct !DILexicalBlock(scope: !330, file: !1, line: 479, column: 6)
!645 = !DILocation(line: 479, column: 9, scope: !644)
!646 = !DILocation(line: 479, column: 16, scope: !644)
!647 = !DILocation(line: 479, column: 23, scope: !644)
!648 = !DILocation(line: 479, column: 6, scope: !330)
!649 = !DILocation(line: 480, column: 8, scope: !650)
!650 = distinct !DILexicalBlock(scope: !644, file: !1, line: 479, column: 32)
!651 = !DILocation(line: 480, column: 11, scope: !650)
!652 = !DILocation(line: 480, column: 18, scope: !650)
!653 = !DILocation(line: 480, column: 27, scope: !650)
!654 = !DILocation(line: 480, column: 30, scope: !650)
!655 = !DILocation(line: 480, column: 39, scope: !650)
!656 = !DILocation(line: 480, column: 42, scope: !650)
!657 = !DILocation(line: 480, column: 49, scope: !650)
!658 = !DILocation(line: 480, column: 60, scope: !650)
!659 = !DILocation(line: 480, column: 7, scope: !650)
!660 = !DILocation(line: 480, column: 5, scope: !650)
!661 = !DILocation(line: 481, column: 7, scope: !662)
!662 = distinct !DILexicalBlock(scope: !650, file: !1, line: 481, column: 7)
!663 = !DILocation(line: 481, column: 9, scope: !662)
!664 = !DILocation(line: 481, column: 7, scope: !650)
!665 = !DILocation(line: 483, column: 8, scope: !666)
!666 = distinct !DILexicalBlock(scope: !667, file: !1, line: 483, column: 8)
!667 = distinct !DILexicalBlock(scope: !662, file: !1, line: 481, column: 15)
!668 = !DILocation(line: 483, column: 11, scope: !666)
!669 = !DILocation(line: 483, column: 18, scope: !666)
!670 = !DILocation(line: 483, column: 8, scope: !667)
!671 = !DILocation(line: 484, column: 12, scope: !672)
!672 = distinct !DILexicalBlock(scope: !673, file: !1, line: 484, column: 5)
!673 = distinct !DILexicalBlock(scope: !666, file: !1, line: 483, column: 26)
!674 = !DILocation(line: 484, column: 10, scope: !672)
!675 = !DILocation(line: 484, column: 17, scope: !676)
!676 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 1)
!677 = distinct !DILexicalBlock(scope: !672, file: !1, line: 484, column: 5)
!678 = !DILocation(line: 484, column: 21, scope: !676)
!679 = !DILocation(line: 484, column: 24, scope: !676)
!680 = !DILocation(line: 484, column: 31, scope: !676)
!681 = !DILocation(line: 484, column: 19, scope: !676)
!682 = !DILocation(line: 484, column: 5, scope: !676)
!683 = !DILocation(line: 485, column: 7, scope: !677)
!684 = !DILocation(line: 485, column: 10, scope: !677)
!685 = !DILocation(line: 485, column: 17, scope: !677)
!686 = !DILocation(line: 485, column: 26, scope: !677)
!687 = !DILocation(line: 485, column: 29, scope: !677)
!688 = !DILocation(line: 486, column: 28, scope: !677)
!689 = !DILocation(line: 486, column: 10, scope: !677)
!690 = !DILocation(line: 486, column: 13, scope: !677)
!691 = !DILocation(line: 486, column: 20, scope: !677)
!692 = !DILocation(line: 486, column: 31, scope: !677)
!693 = !DILocation(line: 485, column: 6, scope: !677)
!694 = !DILocation(line: 484, column: 39, scope: !695)
!695 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 2)
!696 = !DILocation(line: 484, column: 5, scope: !695)
!697 = !DILocation(line: 487, column: 4, scope: !673)
!698 = !DILocation(line: 488, column: 12, scope: !667)
!699 = !DILocation(line: 488, column: 4, scope: !667)
!700 = !DILocation(line: 490, column: 2, scope: !650)
!701 = !DILocation(line: 492, column: 11, scope: !330)
!702 = !DILocation(line: 492, column: 9, scope: !330)
!703 = !DILocation(line: 493, column: 6, scope: !704)
!704 = distinct !DILexicalBlock(scope: !330, file: !1, line: 493, column: 6)
!705 = !DILocation(line: 493, column: 13, scope: !704)
!706 = !DILocation(line: 493, column: 6, scope: !330)
!707 = !DILocation(line: 494, column: 3, scope: !704)
!708 = !DILocation(line: 495, column: 2, scope: !330)
!709 = !DILocation(line: 495, column: 10, scope: !330)
!710 = !DILocation(line: 495, column: 17, scope: !330)
!711 = !DILocation(line: 496, column: 2, scope: !330)
!712 = !DILocation(line: 496, column: 10, scope: !330)
!713 = !DILocation(line: 496, column: 19, scope: !330)
!714 = !DILocation(line: 497, column: 20, scope: !330)
!715 = !DILocation(line: 497, column: 2, scope: !330)
!716 = !DILocation(line: 497, column: 10, scope: !330)
!717 = !DILocation(line: 497, column: 18, scope: !330)
!718 = !DILocation(line: 498, column: 17, scope: !330)
!719 = !DILocation(line: 498, column: 20, scope: !330)
!720 = !DILocation(line: 498, column: 27, scope: !330)
!721 = !DILocation(line: 498, column: 38, scope: !330)
!722 = !DILocation(line: 498, column: 2, scope: !330)
!723 = !DILocation(line: 498, column: 10, scope: !330)
!724 = !DILocation(line: 498, column: 15, scope: !330)
!725 = !DILocation(line: 499, column: 2, scope: !330)
!726 = !DILocation(line: 499, column: 10, scope: !330)
!727 = !DILocation(line: 499, column: 15, scope: !330)
!728 = !DILocation(line: 500, column: 2, scope: !330)
!729 = !DILocation(line: 500, column: 10, scope: !330)
!730 = !DILocation(line: 500, column: 15, scope: !330)
!731 = !DILocation(line: 501, column: 2, scope: !330)
!732 = !DILocation(line: 501, column: 10, scope: !330)
!733 = !DILocation(line: 501, column: 15, scope: !330)
!734 = !DILocation(line: 502, column: 2, scope: !330)
!735 = !DILocation(line: 502, column: 10, scope: !330)
!736 = !DILocation(line: 502, column: 15, scope: !330)
!737 = !DILocation(line: 503, column: 2, scope: !330)
!738 = !DILocation(line: 503, column: 10, scope: !330)
!739 = !DILocation(line: 503, column: 16, scope: !330)
!740 = !DILocation(line: 504, column: 2, scope: !330)
!741 = !DILocation(line: 504, column: 10, scope: !330)
!742 = !DILocation(line: 504, column: 18, scope: !330)
!743 = !DILocation(line: 505, column: 2, scope: !330)
!744 = !DILocation(line: 505, column: 10, scope: !330)
!745 = !DILocation(line: 505, column: 15, scope: !330)
!746 = !DILocation(line: 506, column: 2, scope: !330)
!747 = !DILocation(line: 506, column: 10, scope: !330)
!748 = !DILocation(line: 506, column: 15, scope: !330)
!749 = !DILocation(line: 508, column: 2, scope: !330)
!750 = !DILocation(line: 508, column: 5, scope: !330)
!751 = !DILocation(line: 508, column: 12, scope: !330)
!752 = !DILocation(line: 508, column: 23, scope: !330)
!753 = !DILocation(line: 508, column: 38, scope: !330)
!754 = !DILocation(line: 509, column: 7, scope: !755)
!755 = distinct !DILexicalBlock(scope: !330, file: !1, line: 509, column: 6)
!756 = !DILocation(line: 509, column: 10, scope: !755)
!757 = !DILocation(line: 509, column: 17, scope: !755)
!758 = !DILocation(line: 509, column: 21, scope: !759)
!759 = !DILexicalBlockFile(scope: !755, file: !1, discriminator: 1)
!760 = !DILocation(line: 509, column: 24, scope: !759)
!761 = !DILocation(line: 509, column: 6, scope: !759)
!762 = !DILocation(line: 511, column: 15, scope: !763)
!763 = distinct !DILexicalBlock(scope: !755, file: !1, line: 510, column: 2)
!764 = !DILocation(line: 511, column: 3, scope: !763)
!765 = !DILocation(line: 511, column: 6, scope: !763)
!766 = !DILocation(line: 511, column: 13, scope: !763)
!767 = !DILocation(line: 513, column: 22, scope: !763)
!768 = !DILocation(line: 513, column: 7, scope: !763)
!769 = !DILocation(line: 513, column: 5, scope: !763)
!770 = !DILocation(line: 514, column: 7, scope: !771)
!771 = distinct !DILexicalBlock(scope: !763, file: !1, line: 514, column: 7)
!772 = !DILocation(line: 514, column: 9, scope: !771)
!773 = !DILocation(line: 514, column: 7, scope: !763)
!774 = !DILocation(line: 515, column: 4, scope: !775)
!775 = distinct !DILexicalBlock(scope: !771, file: !1, line: 514, column: 25)
!776 = !DILocation(line: 515, column: 7, scope: !775)
!777 = !DILocation(line: 515, column: 15, scope: !775)
!778 = !DILocation(line: 515, column: 21, scope: !775)
!779 = !DILocation(line: 516, column: 4, scope: !775)
!780 = !DILocation(line: 518, column: 2, scope: !763)
!781 = !DILocation(line: 522, column: 9, scope: !782)
!782 = distinct !DILexicalBlock(scope: !755, file: !1, line: 520, column: 2)
!783 = !DILocation(line: 522, column: 12, scope: !782)
!784 = !DILocation(line: 522, column: 7, scope: !782)
!785 = !DILocation(line: 523, column: 3, scope: !782)
!786 = !DILocation(line: 523, column: 10, scope: !787)
!787 = !DILexicalBlockFile(scope: !782, file: !1, discriminator: 1)
!788 = !DILocation(line: 523, column: 15, scope: !787)
!789 = !DILocation(line: 523, column: 3, scope: !787)
!790 = !DILocation(line: 524, column: 10, scope: !782)
!791 = !DILocation(line: 524, column: 15, scope: !782)
!792 = !DILocation(line: 524, column: 8, scope: !782)
!793 = !DILocation(line: 523, column: 3, scope: !794)
!794 = !DILexicalBlockFile(scope: !782, file: !1, discriminator: 2)
!795 = !DILocation(line: 525, column: 19, scope: !782)
!796 = !DILocation(line: 525, column: 3, scope: !782)
!797 = !DILocation(line: 525, column: 8, scope: !782)
!798 = !DILocation(line: 525, column: 17, scope: !782)
!799 = !DILocation(line: 528, column: 7, scope: !800)
!800 = distinct !DILexicalBlock(scope: !330, file: !1, line: 528, column: 6)
!801 = !DILocation(line: 528, column: 10, scope: !800)
!802 = !DILocation(line: 528, column: 6, scope: !330)
!803 = !DILocation(line: 530, column: 24, scope: !804)
!804 = distinct !DILexicalBlock(scope: !800, file: !1, line: 529, column: 2)
!805 = !DILocation(line: 530, column: 10, scope: !804)
!806 = !DILocation(line: 530, column: 8, scope: !804)
!807 = !DILocation(line: 531, column: 7, scope: !808)
!808 = distinct !DILexicalBlock(scope: !804, file: !1, line: 531, column: 7)
!809 = !DILocation(line: 531, column: 12, scope: !808)
!810 = !DILocation(line: 531, column: 7, scope: !804)
!811 = !DILocation(line: 532, column: 18, scope: !812)
!812 = distinct !DILexicalBlock(scope: !808, file: !1, line: 531, column: 17)
!813 = !DILocation(line: 532, column: 4, scope: !812)
!814 = !DILocation(line: 533, column: 4, scope: !812)
!815 = !DILocation(line: 533, column: 7, scope: !812)
!816 = !DILocation(line: 533, column: 15, scope: !812)
!817 = !DILocation(line: 533, column: 21, scope: !812)
!818 = !DILocation(line: 534, column: 4, scope: !812)
!819 = !DILocation(line: 536, column: 28, scope: !804)
!820 = !DILocation(line: 536, column: 17, scope: !804)
!821 = !DILocation(line: 536, column: 20, scope: !804)
!822 = !DILocation(line: 536, column: 3, scope: !804)
!823 = !DILocation(line: 536, column: 6, scope: !804)
!824 = !DILocation(line: 536, column: 13, scope: !804)
!825 = !DILocation(line: 537, column: 2, scope: !804)
!826 = !DILocation(line: 539, column: 2, scope: !330)
!827 = !DILocation(line: 539, column: 5, scope: !330)
!828 = !DILocation(line: 539, column: 13, scope: !330)
!829 = !DILocation(line: 539, column: 19, scope: !330)
!830 = !DILocation(line: 542, column: 22, scope: !330)
!831 = !DILocation(line: 542, column: 25, scope: !330)
!832 = !DILocation(line: 542, column: 2, scope: !330)
!833 = !DILocation(line: 543, column: 10, scope: !330)
!834 = !DILocation(line: 543, column: 2, scope: !330)
!835 = !DILocation(line: 544, column: 1, scope: !330)
!836 = !DILocalVariable(name: "a", arg: 1, scope: !302, file: !1, line: 154, type: !24)
!837 = !DILocation(line: 154, column: 36, scope: !302)
!838 = !DILocalVariable(name: "client_data", arg: 2, scope: !302, file: !1, line: 154, type: !122)
!839 = !DILocation(line: 154, column: 45, scope: !302)
!840 = !DILocalVariable(name: "client_opener", arg: 3, scope: !302, file: !1, line: 155, type: !118)
!841 = !DILocation(line: 155, column: 28, scope: !302)
!842 = !DILocalVariable(name: "client_reader", arg: 4, scope: !302, file: !1, line: 156, type: !124)
!843 = !DILocation(line: 156, column: 28, scope: !302)
!844 = !DILocalVariable(name: "client_skipper", arg: 5, scope: !302, file: !1, line: 157, type: !130)
!845 = !DILocation(line: 157, column: 28, scope: !302)
!846 = !DILocalVariable(name: "client_closer", arg: 6, scope: !302, file: !1, line: 158, type: !141)
!847 = !DILocation(line: 158, column: 29, scope: !302)
!848 = !DILocation(line: 162, column: 33, scope: !302)
!849 = !DILocation(line: 162, column: 36, scope: !302)
!850 = !DILocation(line: 162, column: 2, scope: !302)
!851 = !DILocation(line: 163, column: 33, scope: !302)
!852 = !DILocation(line: 163, column: 36, scope: !302)
!853 = !DILocation(line: 163, column: 2, scope: !302)
!854 = !DILocation(line: 164, column: 33, scope: !302)
!855 = !DILocation(line: 164, column: 36, scope: !302)
!856 = !DILocation(line: 164, column: 2, scope: !302)
!857 = !DILocation(line: 165, column: 33, scope: !302)
!858 = !DILocation(line: 165, column: 36, scope: !302)
!859 = !DILocation(line: 165, column: 2, scope: !302)
!860 = !DILocation(line: 166, column: 34, scope: !302)
!861 = !DILocation(line: 166, column: 37, scope: !302)
!862 = !DILocation(line: 166, column: 2, scope: !302)
!863 = !DILocation(line: 167, column: 28, scope: !302)
!864 = !DILocation(line: 167, column: 9, scope: !302)
!865 = !DILocation(line: 167, column: 2, scope: !302)
!866 = !DILocalVariable(name: "_a", arg: 1, scope: !311, file: !1, line: 330, type: !24)
!867 = !DILocation(line: 330, column: 48, scope: !311)
!868 = !DILocalVariable(name: "client_skipper", arg: 2, scope: !311, file: !1, line: 331, type: !130)
!869 = !DILocation(line: 331, column: 28, scope: !311)
!870 = !DILocalVariable(name: "a", scope: !311, file: !1, line: 333, type: !4)
!871 = !DILocation(line: 333, column: 23, scope: !311)
!872 = !DILocation(line: 333, column: 50, scope: !311)
!873 = !DILocation(line: 333, column: 27, scope: !311)
!874 = !DILocation(line: 334, column: 2, scope: !311)
!875 = !DILocalVariable(name: "magic_test", scope: !876, file: !1, line: 334, type: !23)
!876 = distinct !DILexicalBlock(scope: !311, file: !1, line: 334, column: 2)
!877 = !DILocation(line: 334, column: 2, scope: !876)
!878 = !DILocation(line: 334, column: 2, scope: !879)
!879 = !DILexicalBlockFile(scope: !876, file: !1, discriminator: 1)
!880 = !DILocation(line: 334, column: 2, scope: !881)
!881 = !DILexicalBlockFile(scope: !882, file: !1, discriminator: 2)
!882 = distinct !DILexicalBlock(scope: !876, file: !1, line: 334, column: 2)
!883 = !DILocation(line: 334, column: 2, scope: !884)
!884 = !DILexicalBlockFile(scope: !876, file: !1, discriminator: 3)
!885 = !DILocation(line: 336, column: 22, scope: !311)
!886 = !DILocation(line: 336, column: 2, scope: !311)
!887 = !DILocation(line: 336, column: 5, scope: !311)
!888 = !DILocation(line: 336, column: 12, scope: !311)
!889 = !DILocation(line: 336, column: 20, scope: !311)
!890 = !DILocation(line: 337, column: 2, scope: !311)
!891 = !DILocation(line: 338, column: 1, scope: !311)
!892 = !DILocalVariable(name: "_a", arg: 1, scope: !314, file: !1, line: 341, type: !24)
!893 = !DILocation(line: 341, column: 48, scope: !314)
!894 = !DILocalVariable(name: "client_seeker", arg: 2, scope: !314, file: !1, line: 342, type: !136)
!895 = !DILocation(line: 342, column: 28, scope: !314)
!896 = !DILocalVariable(name: "a", scope: !314, file: !1, line: 344, type: !4)
!897 = !DILocation(line: 344, column: 23, scope: !314)
!898 = !DILocation(line: 344, column: 50, scope: !314)
!899 = !DILocation(line: 344, column: 27, scope: !314)
!900 = !DILocation(line: 345, column: 2, scope: !314)
!901 = !DILocalVariable(name: "magic_test", scope: !902, file: !1, line: 345, type: !23)
!902 = distinct !DILexicalBlock(scope: !314, file: !1, line: 345, column: 2)
!903 = !DILocation(line: 345, column: 2, scope: !902)
!904 = !DILocation(line: 345, column: 2, scope: !905)
!905 = !DILexicalBlockFile(scope: !902, file: !1, discriminator: 1)
!906 = !DILocation(line: 345, column: 2, scope: !907)
!907 = !DILexicalBlockFile(scope: !908, file: !1, discriminator: 2)
!908 = distinct !DILexicalBlock(scope: !902, file: !1, line: 345, column: 2)
!909 = !DILocation(line: 345, column: 2, scope: !910)
!910 = !DILexicalBlockFile(scope: !902, file: !1, discriminator: 3)
!911 = !DILocation(line: 347, column: 21, scope: !314)
!912 = !DILocation(line: 347, column: 2, scope: !314)
!913 = !DILocation(line: 347, column: 5, scope: !314)
!914 = !DILocation(line: 347, column: 12, scope: !314)
!915 = !DILocation(line: 347, column: 19, scope: !314)
!916 = !DILocation(line: 348, column: 2, scope: !314)
!917 = !DILocation(line: 349, column: 1, scope: !314)
!918 = !DILocalVariable(name: "_a", arg: 1, scope: !320, file: !1, line: 363, type: !24)
!919 = !DILocation(line: 363, column: 50, scope: !320)
!920 = !DILocalVariable(name: "client_switcher", arg: 2, scope: !320, file: !1, line: 364, type: !144)
!921 = !DILocation(line: 364, column: 30, scope: !320)
!922 = !DILocalVariable(name: "a", scope: !320, file: !1, line: 366, type: !4)
!923 = !DILocation(line: 366, column: 23, scope: !320)
!924 = !DILocation(line: 366, column: 50, scope: !320)
!925 = !DILocation(line: 366, column: 27, scope: !320)
!926 = !DILocation(line: 367, column: 2, scope: !320)
!927 = !DILocalVariable(name: "magic_test", scope: !928, file: !1, line: 367, type: !23)
!928 = distinct !DILexicalBlock(scope: !320, file: !1, line: 367, column: 2)
!929 = !DILocation(line: 367, column: 2, scope: !928)
!930 = !DILocation(line: 367, column: 2, scope: !931)
!931 = !DILexicalBlockFile(scope: !928, file: !1, discriminator: 1)
!932 = !DILocation(line: 367, column: 2, scope: !933)
!933 = !DILexicalBlockFile(scope: !934, file: !1, discriminator: 2)
!934 = distinct !DILexicalBlock(scope: !928, file: !1, line: 367, column: 2)
!935 = !DILocation(line: 367, column: 2, scope: !936)
!936 = !DILexicalBlockFile(scope: !928, file: !1, discriminator: 3)
!937 = !DILocation(line: 369, column: 23, scope: !320)
!938 = !DILocation(line: 369, column: 2, scope: !320)
!939 = !DILocation(line: 369, column: 5, scope: !320)
!940 = !DILocation(line: 369, column: 12, scope: !320)
!941 = !DILocation(line: 369, column: 21, scope: !320)
!942 = !DILocation(line: 370, column: 2, scope: !320)
!943 = !DILocation(line: 371, column: 1, scope: !320)
!944 = !DILocalVariable(name: "_a", arg: 1, scope: !324, file: !1, line: 380, type: !24)
!945 = !DILocation(line: 380, column: 49, scope: !324)
!946 = !DILocalVariable(name: "client_data", arg: 2, scope: !324, file: !1, line: 380, type: !122)
!947 = !DILocation(line: 380, column: 59, scope: !324)
!948 = !DILocalVariable(name: "iindex", arg: 3, scope: !324, file: !1, line: 381, type: !13)
!949 = !DILocation(line: 381, column: 18, scope: !324)
!950 = !DILocalVariable(name: "a", scope: !324, file: !1, line: 383, type: !4)
!951 = !DILocation(line: 383, column: 23, scope: !324)
!952 = !DILocation(line: 383, column: 50, scope: !324)
!953 = !DILocation(line: 383, column: 27, scope: !324)
!954 = !DILocation(line: 384, column: 2, scope: !324)
!955 = !DILocalVariable(name: "magic_test", scope: !956, file: !1, line: 384, type: !23)
!956 = distinct !DILexicalBlock(scope: !324, file: !1, line: 384, column: 2)
!957 = !DILocation(line: 384, column: 2, scope: !956)
!958 = !DILocation(line: 384, column: 2, scope: !959)
!959 = !DILexicalBlockFile(scope: !956, file: !1, discriminator: 1)
!960 = !DILocation(line: 384, column: 2, scope: !961)
!961 = !DILexicalBlockFile(scope: !962, file: !1, discriminator: 2)
!962 = distinct !DILexicalBlock(scope: !956, file: !1, line: 384, column: 2)
!963 = !DILocation(line: 384, column: 2, scope: !964)
!964 = !DILexicalBlockFile(scope: !956, file: !1, discriminator: 3)
!965 = !DILocation(line: 387, column: 6, scope: !966)
!966 = distinct !DILexicalBlock(scope: !324, file: !1, line: 387, column: 6)
!967 = !DILocation(line: 387, column: 9, scope: !966)
!968 = !DILocation(line: 387, column: 16, scope: !966)
!969 = !DILocation(line: 387, column: 22, scope: !966)
!970 = !DILocation(line: 387, column: 6, scope: !324)
!971 = !DILocation(line: 390, column: 7, scope: !972)
!972 = distinct !DILexicalBlock(scope: !966, file: !1, line: 388, column: 2)
!973 = !DILocation(line: 389, column: 23, scope: !972)
!974 = !DILocation(line: 389, column: 3, scope: !972)
!975 = !DILocation(line: 389, column: 6, scope: !972)
!976 = !DILocation(line: 389, column: 13, scope: !972)
!977 = !DILocation(line: 389, column: 21, scope: !972)
!978 = !DILocation(line: 391, column: 7, scope: !979)
!979 = distinct !DILexicalBlock(scope: !972, file: !1, line: 391, column: 7)
!980 = !DILocation(line: 391, column: 10, scope: !979)
!981 = !DILocation(line: 391, column: 17, scope: !979)
!982 = !DILocation(line: 391, column: 25, scope: !979)
!983 = !DILocation(line: 391, column: 7, scope: !972)
!984 = !DILocation(line: 393, column: 23, scope: !985)
!985 = distinct !DILexicalBlock(scope: !979, file: !1, line: 392, column: 3)
!986 = !DILocation(line: 393, column: 26, scope: !985)
!987 = !DILocation(line: 393, column: 4, scope: !985)
!988 = !DILocation(line: 395, column: 4, scope: !985)
!989 = !DILocation(line: 397, column: 3, scope: !972)
!990 = !DILocation(line: 397, column: 6, scope: !972)
!991 = !DILocation(line: 397, column: 13, scope: !972)
!992 = !DILocation(line: 397, column: 19, scope: !972)
!993 = !DILocation(line: 398, column: 2, scope: !972)
!994 = !DILocation(line: 400, column: 6, scope: !995)
!995 = distinct !DILexicalBlock(scope: !324, file: !1, line: 400, column: 6)
!996 = !DILocation(line: 400, column: 15, scope: !995)
!997 = !DILocation(line: 400, column: 18, scope: !995)
!998 = !DILocation(line: 400, column: 25, scope: !995)
!999 = !DILocation(line: 400, column: 31, scope: !995)
!1000 = !DILocation(line: 400, column: 13, scope: !995)
!1001 = !DILocation(line: 400, column: 6, scope: !324)
!1002 = !DILocation(line: 402, column: 22, scope: !1003)
!1003 = distinct !DILexicalBlock(scope: !995, file: !1, line: 401, column: 2)
!1004 = !DILocation(line: 402, column: 25, scope: !1003)
!1005 = !DILocation(line: 402, column: 3, scope: !1003)
!1006 = !DILocation(line: 404, column: 3, scope: !1003)
!1007 = !DILocation(line: 406, column: 35, scope: !324)
!1008 = !DILocation(line: 406, column: 20, scope: !324)
!1009 = !DILocation(line: 406, column: 2, scope: !324)
!1010 = !DILocation(line: 406, column: 5, scope: !324)
!1011 = !DILocation(line: 406, column: 12, scope: !324)
!1012 = !DILocation(line: 406, column: 28, scope: !324)
!1013 = !DILocation(line: 406, column: 33, scope: !324)
!1014 = !DILocation(line: 407, column: 20, scope: !324)
!1015 = !DILocation(line: 407, column: 2, scope: !324)
!1016 = !DILocation(line: 407, column: 5, scope: !324)
!1017 = !DILocation(line: 407, column: 12, scope: !324)
!1018 = !DILocation(line: 407, column: 28, scope: !324)
!1019 = !DILocation(line: 407, column: 43, scope: !324)
!1020 = !DILocation(line: 408, column: 20, scope: !324)
!1021 = !DILocation(line: 408, column: 2, scope: !324)
!1022 = !DILocation(line: 408, column: 5, scope: !324)
!1023 = !DILocation(line: 408, column: 12, scope: !324)
!1024 = !DILocation(line: 408, column: 28, scope: !324)
!1025 = !DILocation(line: 408, column: 39, scope: !324)
!1026 = !DILocation(line: 409, column: 2, scope: !324)
!1027 = !DILocation(line: 410, column: 1, scope: !324)
!1028 = !DILocalVariable(name: "_a", arg: 1, scope: !327, file: !1, line: 413, type: !24)
!1029 = !DILocation(line: 413, column: 48, scope: !327)
!1030 = !DILocalVariable(name: "client_data", arg: 2, scope: !327, file: !1, line: 413, type: !122)
!1031 = !DILocation(line: 413, column: 58, scope: !327)
!1032 = !DILocalVariable(name: "iindex", arg: 3, scope: !327, file: !1, line: 414, type: !13)
!1033 = !DILocation(line: 414, column: 18, scope: !327)
!1034 = !DILocalVariable(name: "a", scope: !327, file: !1, line: 416, type: !4)
!1035 = !DILocation(line: 416, column: 23, scope: !327)
!1036 = !DILocation(line: 416, column: 50, scope: !327)
!1037 = !DILocation(line: 416, column: 27, scope: !327)
!1038 = !DILocalVariable(name: "p", scope: !327, file: !1, line: 417, type: !122)
!1039 = !DILocation(line: 417, column: 8, scope: !327)
!1040 = !DILocalVariable(name: "i", scope: !327, file: !1, line: 418, type: !13)
!1041 = !DILocation(line: 418, column: 15, scope: !327)
!1042 = !DILocation(line: 420, column: 2, scope: !327)
!1043 = !DILocalVariable(name: "magic_test", scope: !1044, file: !1, line: 420, type: !23)
!1044 = distinct !DILexicalBlock(scope: !327, file: !1, line: 420, column: 2)
!1045 = !DILocation(line: 420, column: 2, scope: !1044)
!1046 = !DILocation(line: 420, column: 2, scope: !1047)
!1047 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 1)
!1048 = !DILocation(line: 420, column: 2, scope: !1049)
!1049 = !DILexicalBlockFile(scope: !1050, file: !1, discriminator: 2)
!1050 = distinct !DILexicalBlock(scope: !1044, file: !1, line: 420, column: 2)
!1051 = !DILocation(line: 420, column: 2, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 3)
!1053 = !DILocation(line: 422, column: 6, scope: !1054)
!1054 = distinct !DILexicalBlock(scope: !327, file: !1, line: 422, column: 6)
!1055 = !DILocation(line: 422, column: 15, scope: !1054)
!1056 = !DILocation(line: 422, column: 18, scope: !1054)
!1057 = !DILocation(line: 422, column: 25, scope: !1054)
!1058 = !DILocation(line: 422, column: 13, scope: !1054)
!1059 = !DILocation(line: 422, column: 6, scope: !327)
!1060 = !DILocation(line: 423, column: 22, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !1054, file: !1, line: 422, column: 32)
!1062 = !DILocation(line: 423, column: 25, scope: !1061)
!1063 = !DILocation(line: 423, column: 3, scope: !1061)
!1064 = !DILocation(line: 425, column: 3, scope: !1061)
!1065 = !DILocation(line: 427, column: 14, scope: !327)
!1066 = !DILocation(line: 427, column: 17, scope: !327)
!1067 = !DILocation(line: 427, column: 24, scope: !327)
!1068 = !DILocation(line: 428, column: 9, scope: !327)
!1069 = !DILocation(line: 428, column: 12, scope: !327)
!1070 = !DILocation(line: 428, column: 19, scope: !327)
!1071 = !DILocation(line: 428, column: 6, scope: !327)
!1072 = !DILocation(line: 428, column: 5, scope: !327)
!1073 = !DILocation(line: 428, column: 3, scope: !327)
!1074 = !DILocation(line: 427, column: 6, scope: !327)
!1075 = !DILocation(line: 427, column: 4, scope: !327)
!1076 = !DILocation(line: 429, column: 6, scope: !1077)
!1077 = distinct !DILexicalBlock(scope: !327, file: !1, line: 429, column: 6)
!1078 = !DILocation(line: 429, column: 8, scope: !1077)
!1079 = !DILocation(line: 429, column: 6, scope: !327)
!1080 = !DILocation(line: 430, column: 22, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1077, file: !1, line: 429, column: 17)
!1082 = !DILocation(line: 430, column: 25, scope: !1081)
!1083 = !DILocation(line: 430, column: 3, scope: !1081)
!1084 = !DILocation(line: 432, column: 3, scope: !1081)
!1085 = !DILocation(line: 434, column: 55, scope: !327)
!1086 = !DILocation(line: 434, column: 22, scope: !327)
!1087 = !DILocation(line: 434, column: 2, scope: !327)
!1088 = !DILocation(line: 434, column: 5, scope: !327)
!1089 = !DILocation(line: 434, column: 12, scope: !327)
!1090 = !DILocation(line: 434, column: 20, scope: !327)
!1091 = !DILocation(line: 435, column: 11, scope: !1092)
!1092 = distinct !DILexicalBlock(scope: !327, file: !1, line: 435, column: 2)
!1093 = !DILocation(line: 435, column: 14, scope: !1092)
!1094 = !DILocation(line: 435, column: 21, scope: !1092)
!1095 = !DILocation(line: 435, column: 27, scope: !1092)
!1096 = !DILocation(line: 435, column: 9, scope: !1092)
!1097 = !DILocation(line: 435, column: 7, scope: !1092)
!1098 = !DILocation(line: 435, column: 32, scope: !1099)
!1099 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 1)
!1100 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 435, column: 2)
!1101 = !DILocation(line: 435, column: 36, scope: !1099)
!1102 = !DILocation(line: 435, column: 34, scope: !1099)
!1103 = !DILocation(line: 435, column: 43, scope: !1099)
!1104 = !DILocation(line: 435, column: 46, scope: !1105)
!1105 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 2)
!1106 = !DILocation(line: 435, column: 48, scope: !1105)
!1107 = !DILocation(line: 435, column: 2, scope: !1108)
!1108 = !DILexicalBlockFile(scope: !1092, file: !1, discriminator: 3)
!1109 = !DILocation(line: 436, column: 49, scope: !1110)
!1110 = distinct !DILexicalBlock(scope: !1100, file: !1, line: 435, column: 58)
!1111 = !DILocation(line: 436, column: 50, scope: !1110)
!1112 = !DILocation(line: 436, column: 31, scope: !1110)
!1113 = !DILocation(line: 436, column: 34, scope: !1110)
!1114 = !DILocation(line: 436, column: 41, scope: !1110)
!1115 = !DILocation(line: 436, column: 54, scope: !1110)
!1116 = !DILocation(line: 436, column: 21, scope: !1110)
!1117 = !DILocation(line: 436, column: 3, scope: !1110)
!1118 = !DILocation(line: 436, column: 6, scope: !1110)
!1119 = !DILocation(line: 436, column: 13, scope: !1110)
!1120 = !DILocation(line: 436, column: 24, scope: !1110)
!1121 = !DILocation(line: 436, column: 29, scope: !1110)
!1122 = !DILocation(line: 437, column: 21, scope: !1110)
!1123 = !DILocation(line: 437, column: 3, scope: !1110)
!1124 = !DILocation(line: 437, column: 6, scope: !1110)
!1125 = !DILocation(line: 437, column: 13, scope: !1110)
!1126 = !DILocation(line: 437, column: 24, scope: !1110)
!1127 = !DILocation(line: 437, column: 39, scope: !1110)
!1128 = !DILocation(line: 438, column: 21, scope: !1110)
!1129 = !DILocation(line: 438, column: 3, scope: !1110)
!1130 = !DILocation(line: 438, column: 6, scope: !1110)
!1131 = !DILocation(line: 438, column: 13, scope: !1110)
!1132 = !DILocation(line: 438, column: 24, scope: !1110)
!1133 = !DILocation(line: 438, column: 35, scope: !1110)
!1134 = !DILocation(line: 439, column: 2, scope: !1110)
!1135 = !DILocation(line: 435, column: 54, scope: !1136)
!1136 = !DILexicalBlockFile(scope: !1100, file: !1, discriminator: 4)
!1137 = !DILocation(line: 435, column: 2, scope: !1136)
!1138 = !DILocation(line: 440, column: 35, scope: !327)
!1139 = !DILocation(line: 440, column: 20, scope: !327)
!1140 = !DILocation(line: 440, column: 2, scope: !327)
!1141 = !DILocation(line: 440, column: 5, scope: !327)
!1142 = !DILocation(line: 440, column: 12, scope: !327)
!1143 = !DILocation(line: 440, column: 28, scope: !327)
!1144 = !DILocation(line: 440, column: 33, scope: !327)
!1145 = !DILocation(line: 441, column: 20, scope: !327)
!1146 = !DILocation(line: 441, column: 2, scope: !327)
!1147 = !DILocation(line: 441, column: 5, scope: !327)
!1148 = !DILocation(line: 441, column: 12, scope: !327)
!1149 = !DILocation(line: 441, column: 28, scope: !327)
!1150 = !DILocation(line: 441, column: 43, scope: !327)
!1151 = !DILocation(line: 442, column: 20, scope: !327)
!1152 = !DILocation(line: 442, column: 2, scope: !327)
!1153 = !DILocation(line: 442, column: 5, scope: !327)
!1154 = !DILocation(line: 442, column: 12, scope: !327)
!1155 = !DILocation(line: 442, column: 28, scope: !327)
!1156 = !DILocation(line: 442, column: 39, scope: !327)
!1157 = !DILocation(line: 443, column: 2, scope: !327)
!1158 = !DILocation(line: 444, column: 1, scope: !327)
!1159 = !DILocalVariable(name: "_a", arg: 1, scope: !328, file: !1, line: 447, type: !24)
!1160 = !DILocation(line: 447, column: 51, scope: !328)
!1161 = !DILocalVariable(name: "client_data", arg: 2, scope: !328, file: !1, line: 447, type: !122)
!1162 = !DILocation(line: 447, column: 61, scope: !328)
!1163 = !DILocalVariable(name: "a", scope: !328, file: !1, line: 449, type: !4)
!1164 = !DILocation(line: 449, column: 23, scope: !328)
!1165 = !DILocation(line: 449, column: 50, scope: !328)
!1166 = !DILocation(line: 449, column: 27, scope: !328)
!1167 = !DILocation(line: 450, column: 40, scope: !328)
!1168 = !DILocation(line: 450, column: 44, scope: !328)
!1169 = !DILocation(line: 450, column: 57, scope: !328)
!1170 = !DILocation(line: 450, column: 60, scope: !328)
!1171 = !DILocation(line: 450, column: 67, scope: !328)
!1172 = !DILocation(line: 450, column: 9, scope: !328)
!1173 = !DILocation(line: 450, column: 2, scope: !328)
!1174 = !DILocalVariable(name: "_a", arg: 1, scope: !329, file: !1, line: 454, type: !24)
!1175 = !DILocation(line: 454, column: 52, scope: !329)
!1176 = !DILocalVariable(name: "client_data", arg: 2, scope: !329, file: !1, line: 454, type: !122)
!1177 = !DILocation(line: 454, column: 62, scope: !329)
!1178 = !DILocation(line: 456, column: 40, scope: !329)
!1179 = !DILocation(line: 456, column: 44, scope: !329)
!1180 = !DILocation(line: 456, column: 9, scope: !329)
!1181 = !DILocation(line: 456, column: 2, scope: !329)
!1182 = !DILocalVariable(name: "self", arg: 1, scope: !384, file: !1, line: 266, type: !169)
!1183 = !DILocation(line: 266, column: 47, scope: !384)
!1184 = !DILocalVariable(name: "r", scope: !384, file: !1, line: 268, type: !23)
!1185 = !DILocation(line: 268, column: 7, scope: !384)
!1186 = !DILocation(line: 269, column: 6, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !384, file: !1, line: 269, column: 6)
!1188 = !DILocation(line: 269, column: 12, scope: !1187)
!1189 = !DILocation(line: 269, column: 21, scope: !1187)
!1190 = !DILocation(line: 269, column: 28, scope: !1187)
!1191 = !DILocation(line: 269, column: 35, scope: !1187)
!1192 = !DILocation(line: 269, column: 6, scope: !384)
!1193 = !DILocation(line: 270, column: 8, scope: !1187)
!1194 = !DILocation(line: 270, column: 14, scope: !1187)
!1195 = !DILocation(line: 270, column: 23, scope: !1187)
!1196 = !DILocation(line: 270, column: 30, scope: !1187)
!1197 = !DILocation(line: 271, column: 25, scope: !1187)
!1198 = !DILocation(line: 271, column: 31, scope: !1187)
!1199 = !DILocation(line: 271, column: 7, scope: !1187)
!1200 = !DILocation(line: 271, column: 40, scope: !1187)
!1201 = !DILocation(line: 271, column: 46, scope: !1187)
!1202 = !DILocation(line: 270, column: 7, scope: !1187)
!1203 = !DILocation(line: 270, column: 5, scope: !1187)
!1204 = !DILocation(line: 270, column: 3, scope: !1187)
!1205 = !DILocation(line: 272, column: 10, scope: !384)
!1206 = !DILocation(line: 272, column: 2, scope: !384)
!1207 = !DILocalVariable(name: "self", arg: 1, scope: !385, file: !1, line: 171, type: !169)
!1208 = !DILocation(line: 171, column: 47, scope: !385)
!1209 = !DILocalVariable(name: "buff", arg: 2, scope: !385, file: !1, line: 171, type: !64)
!1210 = !DILocation(line: 171, column: 66, scope: !385)
!1211 = !DILocalVariable(name: "r", scope: !385, file: !1, line: 173, type: !38)
!1212 = !DILocation(line: 173, column: 10, scope: !385)
!1213 = !DILocation(line: 174, column: 7, scope: !385)
!1214 = !DILocation(line: 174, column: 13, scope: !385)
!1215 = !DILocation(line: 174, column: 22, scope: !385)
!1216 = !DILocation(line: 174, column: 29, scope: !385)
!1217 = !DILocation(line: 174, column: 38, scope: !385)
!1218 = !DILocation(line: 174, column: 44, scope: !385)
!1219 = !DILocation(line: 174, column: 53, scope: !385)
!1220 = !DILocation(line: 175, column: 6, scope: !385)
!1221 = !DILocation(line: 175, column: 12, scope: !385)
!1222 = !DILocation(line: 175, column: 18, scope: !385)
!1223 = !DILocation(line: 174, column: 6, scope: !385)
!1224 = !DILocation(line: 174, column: 4, scope: !385)
!1225 = !DILocation(line: 176, column: 10, scope: !385)
!1226 = !DILocation(line: 176, column: 2, scope: !385)
!1227 = !DILocalVariable(name: "self", arg: 1, scope: !386, file: !1, line: 180, type: !169)
!1228 = !DILocation(line: 180, column: 47, scope: !386)
!1229 = !DILocalVariable(name: "request", arg: 2, scope: !386, file: !1, line: 180, type: !52)
!1230 = !DILocation(line: 180, column: 61, scope: !386)
!1231 = !DILocation(line: 182, column: 6, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !386, file: !1, line: 182, column: 6)
!1233 = !DILocation(line: 182, column: 14, scope: !1232)
!1234 = !DILocation(line: 182, column: 6, scope: !386)
!1235 = !DILocation(line: 183, column: 3, scope: !1232)
!1236 = !DILocation(line: 184, column: 6, scope: !1237)
!1237 = distinct !DILexicalBlock(scope: !386, file: !1, line: 184, column: 6)
!1238 = !DILocation(line: 184, column: 14, scope: !1237)
!1239 = !DILocation(line: 184, column: 6, scope: !386)
!1240 = !DILocation(line: 185, column: 3, scope: !1237)
!1241 = !DILocation(line: 187, column: 6, scope: !1242)
!1242 = distinct !DILexicalBlock(scope: !386, file: !1, line: 187, column: 6)
!1243 = !DILocation(line: 187, column: 12, scope: !1242)
!1244 = !DILocation(line: 187, column: 21, scope: !1242)
!1245 = !DILocation(line: 187, column: 28, scope: !1242)
!1246 = !DILocation(line: 187, column: 36, scope: !1242)
!1247 = !DILocation(line: 187, column: 6, scope: !386)
!1248 = !DILocalVariable(name: "skip_limit", scope: !1249, file: !1, line: 191, type: !52)
!1249 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 187, column: 45)
!1250 = !DILocation(line: 191, column: 11, scope: !1249)
!1251 = !DILocalVariable(name: "total", scope: !1249, file: !1, line: 192, type: !52)
!1252 = !DILocation(line: 192, column: 11, scope: !1249)
!1253 = !DILocation(line: 193, column: 3, scope: !1249)
!1254 = !DILocalVariable(name: "get", scope: !1255, file: !1, line: 194, type: !52)
!1255 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 193, column: 12)
!1256 = distinct !DILexicalBlock(scope: !1257, file: !1, line: 193, column: 3)
!1257 = distinct !DILexicalBlock(scope: !1249, file: !1, line: 193, column: 3)
!1258 = !DILocation(line: 194, column: 12, scope: !1255)
!1259 = !DILocalVariable(name: "ask", scope: !1255, file: !1, line: 194, type: !52)
!1260 = !DILocation(line: 194, column: 17, scope: !1255)
!1261 = !DILocation(line: 194, column: 23, scope: !1255)
!1262 = !DILocation(line: 195, column: 8, scope: !1263)
!1263 = distinct !DILexicalBlock(scope: !1255, file: !1, line: 195, column: 8)
!1264 = !DILocation(line: 195, column: 14, scope: !1263)
!1265 = !DILocation(line: 195, column: 12, scope: !1263)
!1266 = !DILocation(line: 195, column: 8, scope: !1255)
!1267 = !DILocation(line: 196, column: 11, scope: !1263)
!1268 = !DILocation(line: 196, column: 9, scope: !1263)
!1269 = !DILocation(line: 196, column: 5, scope: !1263)
!1270 = !DILocation(line: 197, column: 11, scope: !1255)
!1271 = !DILocation(line: 197, column: 17, scope: !1255)
!1272 = !DILocation(line: 197, column: 26, scope: !1255)
!1273 = !DILocation(line: 197, column: 33, scope: !1255)
!1274 = !DILocation(line: 198, column: 7, scope: !1255)
!1275 = !DILocation(line: 198, column: 13, scope: !1255)
!1276 = !DILocation(line: 198, column: 22, scope: !1255)
!1277 = !DILocation(line: 198, column: 31, scope: !1255)
!1278 = !DILocation(line: 198, column: 37, scope: !1255)
!1279 = !DILocation(line: 198, column: 43, scope: !1255)
!1280 = !DILocation(line: 197, column: 10, scope: !1255)
!1281 = !DILocation(line: 197, column: 8, scope: !1255)
!1282 = !DILocation(line: 199, column: 13, scope: !1255)
!1283 = !DILocation(line: 199, column: 10, scope: !1255)
!1284 = !DILocation(line: 200, column: 8, scope: !1285)
!1285 = distinct !DILexicalBlock(scope: !1255, file: !1, line: 200, column: 8)
!1286 = !DILocation(line: 200, column: 12, scope: !1285)
!1287 = !DILocation(line: 200, column: 17, scope: !1285)
!1288 = !DILocation(line: 200, column: 20, scope: !1289)
!1289 = !DILexicalBlockFile(scope: !1285, file: !1, discriminator: 1)
!1290 = !DILocation(line: 200, column: 27, scope: !1289)
!1291 = !DILocation(line: 200, column: 24, scope: !1289)
!1292 = !DILocation(line: 200, column: 8, scope: !1289)
!1293 = !DILocation(line: 201, column: 13, scope: !1285)
!1294 = !DILocation(line: 201, column: 5, scope: !1285)
!1295 = !DILocation(line: 202, column: 8, scope: !1296)
!1296 = distinct !DILexicalBlock(scope: !1255, file: !1, line: 202, column: 8)
!1297 = !DILocation(line: 202, column: 14, scope: !1296)
!1298 = !DILocation(line: 202, column: 12, scope: !1296)
!1299 = !DILocation(line: 202, column: 8, scope: !1255)
!1300 = !DILocation(line: 203, column: 5, scope: !1296)
!1301 = !DILocation(line: 204, column: 15, scope: !1255)
!1302 = !DILocation(line: 204, column: 12, scope: !1255)
!1303 = !DILocation(line: 193, column: 3, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1256, file: !1, discriminator: 1)
!1305 = !DILocation(line: 206, column: 13, scope: !1306)
!1306 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 206, column: 13)
!1307 = !DILocation(line: 206, column: 19, scope: !1306)
!1308 = !DILocation(line: 206, column: 28, scope: !1306)
!1309 = !DILocation(line: 206, column: 35, scope: !1306)
!1310 = !DILocation(line: 206, column: 42, scope: !1306)
!1311 = !DILocation(line: 207, column: 3, scope: !1306)
!1312 = !DILocation(line: 207, column: 6, scope: !1313)
!1313 = !DILexicalBlockFile(scope: !1306, file: !1, discriminator: 1)
!1314 = !DILocation(line: 207, column: 14, scope: !1313)
!1315 = !DILocation(line: 206, column: 13, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !1242, file: !1, discriminator: 1)
!1317 = !DILocalVariable(name: "before", scope: !1318, file: !1, line: 219, type: !52)
!1318 = distinct !DILexicalBlock(scope: !1306, file: !1, line: 207, column: 27)
!1319 = !DILocation(line: 219, column: 11, scope: !1318)
!1320 = !DILocation(line: 219, column: 20, scope: !1318)
!1321 = !DILocation(line: 219, column: 26, scope: !1318)
!1322 = !DILocalVariable(name: "after", scope: !1318, file: !1, line: 220, type: !52)
!1323 = !DILocation(line: 220, column: 11, scope: !1318)
!1324 = !DILocation(line: 220, column: 20, scope: !1318)
!1325 = !DILocation(line: 220, column: 26, scope: !1318)
!1326 = !DILocation(line: 220, column: 35, scope: !1318)
!1327 = !DILocation(line: 220, column: 42, scope: !1318)
!1328 = !DILocation(line: 221, column: 9, scope: !1318)
!1329 = !DILocation(line: 221, column: 15, scope: !1318)
!1330 = !DILocation(line: 221, column: 24, scope: !1318)
!1331 = !DILocation(line: 221, column: 33, scope: !1318)
!1332 = !DILocation(line: 221, column: 39, scope: !1318)
!1333 = !DILocation(line: 221, column: 45, scope: !1318)
!1334 = !DILocation(line: 220, column: 19, scope: !1318)
!1335 = !DILocation(line: 222, column: 7, scope: !1336)
!1336 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 222, column: 7)
!1337 = !DILocation(line: 222, column: 16, scope: !1336)
!1338 = !DILocation(line: 222, column: 25, scope: !1336)
!1339 = !DILocation(line: 222, column: 23, scope: !1336)
!1340 = !DILocation(line: 222, column: 13, scope: !1336)
!1341 = !DILocation(line: 222, column: 7, scope: !1318)
!1342 = !DILocation(line: 223, column: 4, scope: !1336)
!1343 = !DILocation(line: 224, column: 10, scope: !1318)
!1344 = !DILocation(line: 224, column: 18, scope: !1318)
!1345 = !DILocation(line: 224, column: 16, scope: !1318)
!1346 = !DILocation(line: 224, column: 3, scope: !1318)
!1347 = !DILocation(line: 226, column: 2, scope: !386)
!1348 = !DILocation(line: 227, column: 1, scope: !386)
!1349 = !DILocalVariable(name: "self", arg: 1, scope: !387, file: !1, line: 230, type: !169)
!1350 = !DILocation(line: 230, column: 47, scope: !387)
!1351 = !DILocalVariable(name: "offset", arg: 2, scope: !387, file: !1, line: 230, type: !52)
!1352 = !DILocation(line: 230, column: 61, scope: !387)
!1353 = !DILocalVariable(name: "whence", arg: 3, scope: !387, file: !1, line: 230, type: !23)
!1354 = !DILocation(line: 230, column: 73, scope: !387)
!1355 = !DILocation(line: 237, column: 6, scope: !1356)
!1356 = distinct !DILexicalBlock(scope: !387, file: !1, line: 237, column: 6)
!1357 = !DILocation(line: 237, column: 12, scope: !1356)
!1358 = !DILocation(line: 237, column: 21, scope: !1356)
!1359 = !DILocation(line: 237, column: 28, scope: !1356)
!1360 = !DILocation(line: 237, column: 35, scope: !1356)
!1361 = !DILocation(line: 237, column: 6, scope: !387)
!1362 = !DILocation(line: 238, column: 22, scope: !1363)
!1363 = distinct !DILexicalBlock(scope: !1356, file: !1, line: 237, column: 44)
!1364 = !DILocation(line: 238, column: 28, scope: !1363)
!1365 = !DILocation(line: 238, column: 37, scope: !1363)
!1366 = !DILocation(line: 238, column: 3, scope: !1363)
!1367 = !DILocation(line: 240, column: 3, scope: !1363)
!1368 = !DILocation(line: 242, column: 10, scope: !387)
!1369 = !DILocation(line: 242, column: 16, scope: !387)
!1370 = !DILocation(line: 242, column: 25, scope: !387)
!1371 = !DILocation(line: 242, column: 32, scope: !387)
!1372 = !DILocation(line: 242, column: 41, scope: !387)
!1373 = !DILocation(line: 242, column: 47, scope: !387)
!1374 = !DILocation(line: 242, column: 56, scope: !387)
!1375 = !DILocation(line: 243, column: 6, scope: !387)
!1376 = !DILocation(line: 243, column: 12, scope: !387)
!1377 = !DILocation(line: 243, column: 18, scope: !387)
!1378 = !DILocation(line: 243, column: 26, scope: !387)
!1379 = !DILocation(line: 242, column: 9, scope: !387)
!1380 = !DILocation(line: 242, column: 2, scope: !387)
!1381 = !DILocation(line: 244, column: 1, scope: !387)
!1382 = !DILocalVariable(name: "self", arg: 1, scope: !388, file: !1, line: 247, type: !169)
!1383 = !DILocation(line: 247, column: 48, scope: !388)
!1384 = !DILocalVariable(name: "r", scope: !388, file: !1, line: 249, type: !23)
!1385 = !DILocation(line: 249, column: 6, scope: !388)
!1386 = !DILocalVariable(name: "r2", scope: !388, file: !1, line: 249, type: !23)
!1387 = !DILocation(line: 249, column: 22, scope: !388)
!1388 = !DILocalVariable(name: "i", scope: !388, file: !1, line: 250, type: !13)
!1389 = !DILocation(line: 250, column: 15, scope: !388)
!1390 = !DILocation(line: 252, column: 6, scope: !1391)
!1391 = distinct !DILexicalBlock(scope: !388, file: !1, line: 252, column: 6)
!1392 = !DILocation(line: 252, column: 12, scope: !1391)
!1393 = !DILocation(line: 252, column: 21, scope: !1391)
!1394 = !DILocation(line: 252, column: 28, scope: !1391)
!1395 = !DILocation(line: 252, column: 35, scope: !1391)
!1396 = !DILocation(line: 252, column: 6, scope: !388)
!1397 = !DILocation(line: 253, column: 11, scope: !1391)
!1398 = !DILocation(line: 253, column: 3, scope: !1391)
!1399 = !DILocation(line: 254, column: 9, scope: !1400)
!1400 = distinct !DILexicalBlock(scope: !388, file: !1, line: 254, column: 2)
!1401 = !DILocation(line: 254, column: 7, scope: !1400)
!1402 = !DILocation(line: 254, column: 14, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1404, file: !1, discriminator: 1)
!1404 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 254, column: 2)
!1405 = !DILocation(line: 254, column: 18, scope: !1403)
!1406 = !DILocation(line: 254, column: 24, scope: !1403)
!1407 = !DILocation(line: 254, column: 33, scope: !1403)
!1408 = !DILocation(line: 254, column: 40, scope: !1403)
!1409 = !DILocation(line: 254, column: 16, scope: !1403)
!1410 = !DILocation(line: 254, column: 2, scope: !1403)
!1411 = !DILocation(line: 256, column: 9, scope: !1412)
!1412 = distinct !DILexicalBlock(scope: !1404, file: !1, line: 255, column: 2)
!1413 = !DILocation(line: 256, column: 15, scope: !1412)
!1414 = !DILocation(line: 256, column: 24, scope: !1412)
!1415 = !DILocation(line: 256, column: 31, scope: !1412)
!1416 = !DILocation(line: 257, column: 23, scope: !1412)
!1417 = !DILocation(line: 257, column: 29, scope: !1412)
!1418 = !DILocation(line: 257, column: 5, scope: !1412)
!1419 = !DILocation(line: 258, column: 35, scope: !1412)
!1420 = !DILocation(line: 258, column: 5, scope: !1412)
!1421 = !DILocation(line: 258, column: 11, scope: !1412)
!1422 = !DILocation(line: 258, column: 20, scope: !1412)
!1423 = !DILocation(line: 258, column: 27, scope: !1412)
!1424 = !DILocation(line: 258, column: 38, scope: !1412)
!1425 = !DILocation(line: 256, column: 8, scope: !1412)
!1426 = !DILocation(line: 256, column: 6, scope: !1412)
!1427 = !DILocation(line: 259, column: 7, scope: !1428)
!1428 = distinct !DILexicalBlock(scope: !1412, file: !1, line: 259, column: 7)
!1429 = !DILocation(line: 259, column: 11, scope: !1428)
!1430 = !DILocation(line: 259, column: 9, scope: !1428)
!1431 = !DILocation(line: 259, column: 7, scope: !1412)
!1432 = !DILocation(line: 260, column: 8, scope: !1428)
!1433 = !DILocation(line: 260, column: 6, scope: !1428)
!1434 = !DILocation(line: 260, column: 4, scope: !1428)
!1435 = !DILocation(line: 261, column: 2, scope: !1412)
!1436 = !DILocation(line: 254, column: 48, scope: !1437)
!1437 = !DILexicalBlockFile(scope: !1404, file: !1, discriminator: 2)
!1438 = !DILocation(line: 254, column: 2, scope: !1437)
!1439 = !DILocation(line: 262, column: 10, scope: !388)
!1440 = !DILocation(line: 262, column: 2, scope: !388)
!1441 = !DILocation(line: 263, column: 1, scope: !388)
!1442 = !DILocalVariable(name: "self", arg: 1, scope: !389, file: !1, line: 276, type: !169)
!1443 = !DILocation(line: 276, column: 49, scope: !389)
!1444 = !DILocalVariable(name: "iindex", arg: 2, scope: !389, file: !1, line: 276, type: !13)
!1445 = !DILocation(line: 276, column: 68, scope: !389)
!1446 = !DILocalVariable(name: "r1", scope: !389, file: !1, line: 278, type: !23)
!1447 = !DILocation(line: 278, column: 7, scope: !389)
!1448 = !DILocalVariable(name: "r2", scope: !389, file: !1, line: 278, type: !23)
!1449 = !DILocation(line: 278, column: 24, scope: !389)
!1450 = !DILocalVariable(name: "data2", scope: !389, file: !1, line: 279, type: !122)
!1451 = !DILocation(line: 279, column: 8, scope: !389)
!1452 = !DILocation(line: 282, column: 6, scope: !1453)
!1453 = distinct !DILexicalBlock(scope: !389, file: !1, line: 282, column: 6)
!1454 = !DILocation(line: 282, column: 12, scope: !1453)
!1455 = !DILocation(line: 282, column: 21, scope: !1453)
!1456 = !DILocation(line: 282, column: 28, scope: !1453)
!1457 = !DILocation(line: 282, column: 38, scope: !1453)
!1458 = !DILocation(line: 282, column: 35, scope: !1453)
!1459 = !DILocation(line: 282, column: 6, scope: !389)
!1460 = !DILocation(line: 283, column: 3, scope: !1453)
!1461 = !DILocation(line: 285, column: 33, scope: !389)
!1462 = !DILocation(line: 285, column: 2, scope: !389)
!1463 = !DILocation(line: 285, column: 8, scope: !389)
!1464 = !DILocation(line: 285, column: 17, scope: !389)
!1465 = !DILocation(line: 285, column: 24, scope: !389)
!1466 = !DILocation(line: 285, column: 31, scope: !389)
!1467 = !DILocation(line: 286, column: 40, scope: !389)
!1468 = !DILocation(line: 286, column: 46, scope: !389)
!1469 = !DILocation(line: 286, column: 55, scope: !389)
!1470 = !DILocation(line: 286, column: 62, scope: !389)
!1471 = !DILocation(line: 286, column: 10, scope: !389)
!1472 = !DILocation(line: 286, column: 16, scope: !389)
!1473 = !DILocation(line: 286, column: 25, scope: !389)
!1474 = !DILocation(line: 286, column: 32, scope: !389)
!1475 = !DILocation(line: 286, column: 70, scope: !389)
!1476 = !DILocation(line: 286, column: 8, scope: !389)
!1477 = !DILocation(line: 287, column: 6, scope: !1478)
!1478 = distinct !DILexicalBlock(scope: !389, file: !1, line: 287, column: 6)
!1479 = !DILocation(line: 287, column: 12, scope: !1478)
!1480 = !DILocation(line: 287, column: 21, scope: !1478)
!1481 = !DILocation(line: 287, column: 28, scope: !1478)
!1482 = !DILocation(line: 287, column: 37, scope: !1478)
!1483 = !DILocation(line: 287, column: 6, scope: !389)
!1484 = !DILocation(line: 289, column: 14, scope: !1485)
!1485 = distinct !DILexicalBlock(scope: !1478, file: !1, line: 288, column: 2)
!1486 = !DILocation(line: 289, column: 20, scope: !1485)
!1487 = !DILocation(line: 289, column: 29, scope: !1485)
!1488 = !DILocation(line: 289, column: 36, scope: !1485)
!1489 = !DILocation(line: 290, column: 23, scope: !1485)
!1490 = !DILocation(line: 290, column: 29, scope: !1485)
!1491 = !DILocation(line: 290, column: 5, scope: !1485)
!1492 = !DILocation(line: 290, column: 38, scope: !1485)
!1493 = !DILocation(line: 290, column: 44, scope: !1485)
!1494 = !DILocation(line: 290, column: 50, scope: !1485)
!1495 = !DILocation(line: 289, column: 13, scope: !1485)
!1496 = !DILocation(line: 289, column: 11, scope: !1485)
!1497 = !DILocation(line: 289, column: 6, scope: !1485)
!1498 = !DILocation(line: 291, column: 16, scope: !1485)
!1499 = !DILocation(line: 291, column: 3, scope: !1485)
!1500 = !DILocation(line: 291, column: 9, scope: !1485)
!1501 = !DILocation(line: 291, column: 14, scope: !1485)
!1502 = !DILocation(line: 292, column: 2, scope: !1485)
!1503 = !DILocation(line: 296, column: 7, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !1505, file: !1, line: 296, column: 7)
!1505 = distinct !DILexicalBlock(scope: !1478, file: !1, line: 294, column: 2)
!1506 = !DILocation(line: 296, column: 13, scope: !1504)
!1507 = !DILocation(line: 296, column: 22, scope: !1504)
!1508 = !DILocation(line: 296, column: 29, scope: !1504)
!1509 = !DILocation(line: 296, column: 36, scope: !1504)
!1510 = !DILocation(line: 296, column: 7, scope: !1505)
!1511 = !DILocation(line: 297, column: 10, scope: !1504)
!1512 = !DILocation(line: 297, column: 16, scope: !1504)
!1513 = !DILocation(line: 297, column: 25, scope: !1504)
!1514 = !DILocation(line: 297, column: 32, scope: !1504)
!1515 = !DILocation(line: 298, column: 24, scope: !1504)
!1516 = !DILocation(line: 298, column: 30, scope: !1504)
!1517 = !DILocation(line: 298, column: 6, scope: !1504)
!1518 = !DILocation(line: 298, column: 39, scope: !1504)
!1519 = !DILocation(line: 298, column: 45, scope: !1504)
!1520 = !DILocation(line: 297, column: 9, scope: !1504)
!1521 = !DILocation(line: 297, column: 7, scope: !1504)
!1522 = !DILocation(line: 297, column: 4, scope: !1504)
!1523 = !DILocation(line: 299, column: 16, scope: !1505)
!1524 = !DILocation(line: 299, column: 3, scope: !1505)
!1525 = !DILocation(line: 299, column: 9, scope: !1505)
!1526 = !DILocation(line: 299, column: 14, scope: !1505)
!1527 = !DILocation(line: 300, column: 7, scope: !1528)
!1528 = distinct !DILexicalBlock(scope: !1505, file: !1, line: 300, column: 7)
!1529 = !DILocation(line: 300, column: 13, scope: !1528)
!1530 = !DILocation(line: 300, column: 22, scope: !1528)
!1531 = !DILocation(line: 300, column: 29, scope: !1528)
!1532 = !DILocation(line: 300, column: 36, scope: !1528)
!1533 = !DILocation(line: 300, column: 7, scope: !1505)
!1534 = !DILocation(line: 301, column: 10, scope: !1528)
!1535 = !DILocation(line: 301, column: 16, scope: !1528)
!1536 = !DILocation(line: 301, column: 25, scope: !1528)
!1537 = !DILocation(line: 301, column: 32, scope: !1528)
!1538 = !DILocation(line: 302, column: 24, scope: !1528)
!1539 = !DILocation(line: 302, column: 30, scope: !1528)
!1540 = !DILocation(line: 302, column: 6, scope: !1528)
!1541 = !DILocation(line: 302, column: 39, scope: !1528)
!1542 = !DILocation(line: 302, column: 45, scope: !1528)
!1543 = !DILocation(line: 301, column: 9, scope: !1528)
!1544 = !DILocation(line: 301, column: 7, scope: !1528)
!1545 = !DILocation(line: 301, column: 4, scope: !1528)
!1546 = !DILocation(line: 304, column: 10, scope: !389)
!1547 = !DILocation(line: 304, column: 15, scope: !389)
!1548 = !DILocation(line: 304, column: 13, scope: !389)
!1549 = !DILocation(line: 304, column: 9, scope: !389)
!1550 = !DILocation(line: 304, column: 21, scope: !1551)
!1551 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 1)
!1552 = !DILocation(line: 304, column: 9, scope: !1551)
!1553 = !DILocation(line: 304, column: 26, scope: !1554)
!1554 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 2)
!1555 = !DILocation(line: 304, column: 9, scope: !1554)
!1556 = !DILocation(line: 304, column: 9, scope: !1557)
!1557 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 3)
!1558 = !DILocation(line: 304, column: 2, scope: !1557)
!1559 = !DILocation(line: 305, column: 1, scope: !389)
!1560 = !DILocalVariable(name: "a", arg: 1, scope: !390, file: !1, line: 556, type: !4)
!1561 = !DILocation(line: 556, column: 37, scope: !390)
!1562 = !DILocalVariable(name: "number_bidders", scope: !390, file: !1, line: 558, type: !23)
!1563 = !DILocation(line: 558, column: 6, scope: !390)
!1564 = !DILocalVariable(name: "i", scope: !390, file: !1, line: 558, type: !23)
!1565 = !DILocation(line: 558, column: 22, scope: !390)
!1566 = !DILocalVariable(name: "bid", scope: !390, file: !1, line: 558, type: !23)
!1567 = !DILocation(line: 558, column: 25, scope: !390)
!1568 = !DILocalVariable(name: "best_bid", scope: !390, file: !1, line: 558, type: !23)
!1569 = !DILocation(line: 558, column: 30, scope: !390)
!1570 = !DILocalVariable(name: "number_filters", scope: !390, file: !1, line: 558, type: !23)
!1571 = !DILocation(line: 558, column: 40, scope: !390)
!1572 = !DILocalVariable(name: "bidder", scope: !390, file: !1, line: 559, type: !168)
!1573 = !DILocation(line: 559, column: 37, scope: !390)
!1574 = !DILocalVariable(name: "best_bidder", scope: !390, file: !1, line: 559, type: !168)
!1575 = !DILocation(line: 559, column: 46, scope: !390)
!1576 = !DILocalVariable(name: "filter", scope: !390, file: !1, line: 560, type: !169)
!1577 = !DILocation(line: 560, column: 30, scope: !390)
!1578 = !DILocalVariable(name: "avail", scope: !390, file: !1, line: 561, type: !38)
!1579 = !DILocation(line: 561, column: 10, scope: !390)
!1580 = !DILocalVariable(name: "r", scope: !390, file: !1, line: 562, type: !23)
!1581 = !DILocation(line: 562, column: 6, scope: !390)
!1582 = !DILocation(line: 564, column: 22, scope: !1583)
!1583 = distinct !DILexicalBlock(scope: !390, file: !1, line: 564, column: 2)
!1584 = !DILocation(line: 564, column: 7, scope: !1583)
!1585 = !DILocation(line: 564, column: 27, scope: !1586)
!1586 = !DILexicalBlockFile(scope: !1587, file: !1, discriminator: 1)
!1587 = distinct !DILexicalBlock(scope: !1583, file: !1, line: 564, column: 2)
!1588 = !DILocation(line: 564, column: 42, scope: !1586)
!1589 = !DILocation(line: 564, column: 2, scope: !1586)
!1590 = !DILocation(line: 565, column: 18, scope: !1591)
!1591 = distinct !DILexicalBlock(scope: !1587, file: !1, line: 564, column: 82)
!1592 = !DILocation(line: 567, column: 12, scope: !1591)
!1593 = !DILocation(line: 568, column: 15, scope: !1591)
!1594 = !DILocation(line: 570, column: 12, scope: !1591)
!1595 = !DILocation(line: 570, column: 15, scope: !1591)
!1596 = !DILocation(line: 570, column: 10, scope: !1591)
!1597 = !DILocation(line: 571, column: 10, scope: !1598)
!1598 = distinct !DILexicalBlock(scope: !1591, file: !1, line: 571, column: 3)
!1599 = !DILocation(line: 571, column: 8, scope: !1598)
!1600 = !DILocation(line: 571, column: 15, scope: !1601)
!1601 = !DILexicalBlockFile(scope: !1602, file: !1, discriminator: 1)
!1602 = distinct !DILexicalBlock(scope: !1598, file: !1, line: 571, column: 3)
!1603 = !DILocation(line: 571, column: 19, scope: !1601)
!1604 = !DILocation(line: 571, column: 17, scope: !1601)
!1605 = !DILocation(line: 571, column: 3, scope: !1601)
!1606 = !DILocation(line: 572, column: 8, scope: !1607)
!1607 = distinct !DILexicalBlock(scope: !1608, file: !1, line: 572, column: 8)
!1608 = distinct !DILexicalBlock(scope: !1602, file: !1, line: 571, column: 50)
!1609 = !DILocation(line: 572, column: 16, scope: !1607)
!1610 = !DILocation(line: 572, column: 20, scope: !1607)
!1611 = !DILocation(line: 572, column: 8, scope: !1608)
!1612 = !DILocation(line: 573, column: 12, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1607, file: !1, line: 572, column: 29)
!1614 = !DILocation(line: 573, column: 20, scope: !1613)
!1615 = !DILocation(line: 573, column: 25, scope: !1613)
!1616 = !DILocation(line: 573, column: 33, scope: !1613)
!1617 = !DILocation(line: 573, column: 36, scope: !1613)
!1618 = !DILocation(line: 573, column: 11, scope: !1613)
!1619 = !DILocation(line: 573, column: 9, scope: !1613)
!1620 = !DILocation(line: 574, column: 9, scope: !1621)
!1621 = distinct !DILexicalBlock(scope: !1613, file: !1, line: 574, column: 9)
!1622 = !DILocation(line: 574, column: 15, scope: !1621)
!1623 = !DILocation(line: 574, column: 13, scope: !1621)
!1624 = !DILocation(line: 574, column: 9, scope: !1613)
!1625 = !DILocation(line: 575, column: 17, scope: !1626)
!1626 = distinct !DILexicalBlock(scope: !1621, file: !1, line: 574, column: 25)
!1627 = !DILocation(line: 575, column: 15, scope: !1626)
!1628 = !DILocation(line: 576, column: 20, scope: !1626)
!1629 = !DILocation(line: 576, column: 18, scope: !1626)
!1630 = !DILocation(line: 577, column: 5, scope: !1626)
!1631 = !DILocation(line: 578, column: 4, scope: !1613)
!1632 = !DILocation(line: 579, column: 3, scope: !1608)
!1633 = !DILocation(line: 571, column: 36, scope: !1634)
!1634 = !DILexicalBlockFile(scope: !1602, file: !1, discriminator: 2)
!1635 = !DILocation(line: 571, column: 46, scope: !1634)
!1636 = !DILocation(line: 571, column: 3, scope: !1634)
!1637 = !DILocation(line: 582, column: 7, scope: !1638)
!1638 = distinct !DILexicalBlock(scope: !1591, file: !1, line: 582, column: 7)
!1639 = !DILocation(line: 582, column: 19, scope: !1638)
!1640 = !DILocation(line: 582, column: 7, scope: !1591)
!1641 = !DILocation(line: 584, column: 32, scope: !1642)
!1642 = distinct !DILexicalBlock(scope: !1638, file: !1, line: 582, column: 28)
!1643 = !DILocation(line: 584, column: 35, scope: !1642)
!1644 = !DILocation(line: 584, column: 4, scope: !1642)
!1645 = !DILocation(line: 585, column: 8, scope: !1646)
!1646 = distinct !DILexicalBlock(scope: !1642, file: !1, line: 585, column: 8)
!1647 = !DILocation(line: 585, column: 14, scope: !1646)
!1648 = !DILocation(line: 585, column: 8, scope: !1642)
!1649 = !DILocation(line: 586, column: 33, scope: !1650)
!1650 = distinct !DILexicalBlock(scope: !1646, file: !1, line: 585, column: 19)
!1651 = !DILocation(line: 586, column: 5, scope: !1650)
!1652 = !DILocation(line: 587, column: 5, scope: !1650)
!1653 = !DILocation(line: 589, column: 34, scope: !1642)
!1654 = !DILocation(line: 589, column: 37, scope: !1642)
!1655 = !DILocation(line: 589, column: 45, scope: !1642)
!1656 = !DILocation(line: 589, column: 4, scope: !1642)
!1657 = !DILocation(line: 589, column: 7, scope: !1642)
!1658 = !DILocation(line: 589, column: 15, scope: !1642)
!1659 = !DILocation(line: 589, column: 32, scope: !1642)
!1660 = !DILocation(line: 590, column: 34, scope: !1642)
!1661 = !DILocation(line: 590, column: 37, scope: !1642)
!1662 = !DILocation(line: 590, column: 45, scope: !1642)
!1663 = !DILocation(line: 590, column: 4, scope: !1642)
!1664 = !DILocation(line: 590, column: 7, scope: !1642)
!1665 = !DILocation(line: 590, column: 15, scope: !1642)
!1666 = !DILocation(line: 590, column: 32, scope: !1642)
!1667 = !DILocation(line: 591, column: 4, scope: !1642)
!1668 = !DILocation(line: 595, column: 39, scope: !1591)
!1669 = !DILocation(line: 595, column: 9, scope: !1591)
!1670 = !DILocation(line: 595, column: 7, scope: !1591)
!1671 = !DILocation(line: 596, column: 7, scope: !1672)
!1672 = distinct !DILexicalBlock(scope: !1591, file: !1, line: 596, column: 7)
!1673 = !DILocation(line: 596, column: 14, scope: !1672)
!1674 = !DILocation(line: 596, column: 7, scope: !1591)
!1675 = !DILocation(line: 597, column: 4, scope: !1672)
!1676 = !DILocation(line: 598, column: 20, scope: !1591)
!1677 = !DILocation(line: 598, column: 3, scope: !1591)
!1678 = !DILocation(line: 598, column: 11, scope: !1591)
!1679 = !DILocation(line: 598, column: 18, scope: !1591)
!1680 = !DILocation(line: 599, column: 21, scope: !1591)
!1681 = !DILocation(line: 599, column: 3, scope: !1591)
!1682 = !DILocation(line: 599, column: 11, scope: !1591)
!1683 = !DILocation(line: 599, column: 19, scope: !1591)
!1684 = !DILocation(line: 600, column: 22, scope: !1591)
!1685 = !DILocation(line: 600, column: 25, scope: !1591)
!1686 = !DILocation(line: 600, column: 3, scope: !1591)
!1687 = !DILocation(line: 600, column: 11, scope: !1591)
!1688 = !DILocation(line: 600, column: 20, scope: !1591)
!1689 = !DILocation(line: 601, column: 15, scope: !1591)
!1690 = !DILocation(line: 601, column: 3, scope: !1591)
!1691 = !DILocation(line: 601, column: 6, scope: !1591)
!1692 = !DILocation(line: 601, column: 13, scope: !1591)
!1693 = !DILocation(line: 602, column: 8, scope: !1591)
!1694 = !DILocation(line: 602, column: 21, scope: !1591)
!1695 = !DILocation(line: 602, column: 27, scope: !1591)
!1696 = !DILocation(line: 602, column: 30, scope: !1591)
!1697 = !DILocation(line: 602, column: 7, scope: !1591)
!1698 = !DILocation(line: 602, column: 5, scope: !1591)
!1699 = !DILocation(line: 603, column: 7, scope: !1700)
!1700 = distinct !DILexicalBlock(scope: !1591, file: !1, line: 603, column: 7)
!1701 = !DILocation(line: 603, column: 9, scope: !1700)
!1702 = !DILocation(line: 603, column: 7, scope: !1591)
!1703 = !DILocation(line: 604, column: 32, scope: !1704)
!1704 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 603, column: 24)
!1705 = !DILocation(line: 604, column: 4, scope: !1704)
!1706 = !DILocation(line: 605, column: 4, scope: !1704)
!1707 = !DILocation(line: 607, column: 2, scope: !1591)
!1708 = !DILocation(line: 564, column: 64, scope: !1709)
!1709 = !DILexicalBlockFile(scope: !1587, file: !1, discriminator: 2)
!1710 = !DILocation(line: 564, column: 2, scope: !1709)
!1711 = !DILocation(line: 608, column: 21, scope: !390)
!1712 = !DILocation(line: 608, column: 24, scope: !390)
!1713 = !DILocation(line: 608, column: 2, scope: !390)
!1714 = !DILocation(line: 610, column: 2, scope: !390)
!1715 = !DILocation(line: 611, column: 1, scope: !390)
!1716 = !DILocalVariable(name: "a", arg: 1, scope: !391, file: !1, line: 696, type: !4)
!1717 = !DILocation(line: 696, column: 36, scope: !391)
!1718 = !DILocalVariable(name: "slots", scope: !391, file: !1, line: 698, type: !23)
!1719 = !DILocation(line: 698, column: 6, scope: !391)
!1720 = !DILocalVariable(name: "i", scope: !391, file: !1, line: 699, type: !23)
!1721 = !DILocation(line: 699, column: 6, scope: !391)
!1722 = !DILocalVariable(name: "bid", scope: !391, file: !1, line: 700, type: !23)
!1723 = !DILocation(line: 700, column: 6, scope: !391)
!1724 = !DILocalVariable(name: "best_bid", scope: !391, file: !1, line: 700, type: !23)
!1725 = !DILocation(line: 700, column: 11, scope: !391)
!1726 = !DILocalVariable(name: "best_bid_slot", scope: !391, file: !1, line: 701, type: !23)
!1727 = !DILocation(line: 701, column: 6, scope: !391)
!1728 = !DILocation(line: 703, column: 8, scope: !391)
!1729 = !DILocation(line: 704, column: 11, scope: !391)
!1730 = !DILocation(line: 705, column: 16, scope: !391)
!1731 = !DILocation(line: 708, column: 16, scope: !391)
!1732 = !DILocation(line: 708, column: 19, scope: !391)
!1733 = !DILocation(line: 708, column: 2, scope: !391)
!1734 = !DILocation(line: 708, column: 5, scope: !391)
!1735 = !DILocation(line: 708, column: 12, scope: !391)
!1736 = !DILocation(line: 709, column: 9, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !391, file: !1, line: 709, column: 2)
!1738 = !DILocation(line: 709, column: 7, scope: !1737)
!1739 = !DILocation(line: 709, column: 14, scope: !1740)
!1740 = !DILexicalBlockFile(scope: !1741, file: !1, discriminator: 1)
!1741 = distinct !DILexicalBlock(scope: !1737, file: !1, line: 709, column: 2)
!1742 = !DILocation(line: 709, column: 18, scope: !1740)
!1743 = !DILocation(line: 709, column: 16, scope: !1740)
!1744 = !DILocation(line: 709, column: 2, scope: !1740)
!1745 = !DILocation(line: 710, column: 7, scope: !1746)
!1746 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 710, column: 7)
!1747 = distinct !DILexicalBlock(scope: !1741, file: !1, line: 709, column: 43)
!1748 = !DILocation(line: 710, column: 10, scope: !1746)
!1749 = !DILocation(line: 710, column: 18, scope: !1746)
!1750 = !DILocation(line: 710, column: 7, scope: !1747)
!1751 = !DILocation(line: 711, column: 11, scope: !1752)
!1752 = distinct !DILexicalBlock(scope: !1746, file: !1, line: 710, column: 23)
!1753 = !DILocation(line: 711, column: 14, scope: !1752)
!1754 = !DILocation(line: 711, column: 22, scope: !1752)
!1755 = !DILocation(line: 711, column: 27, scope: !1752)
!1756 = !DILocation(line: 711, column: 30, scope: !1752)
!1757 = !DILocation(line: 711, column: 10, scope: !1752)
!1758 = !DILocation(line: 711, column: 8, scope: !1752)
!1759 = !DILocation(line: 712, column: 8, scope: !1760)
!1760 = distinct !DILexicalBlock(scope: !1752, file: !1, line: 712, column: 8)
!1761 = !DILocation(line: 712, column: 12, scope: !1760)
!1762 = !DILocation(line: 712, column: 8, scope: !1752)
!1763 = !DILocation(line: 713, column: 5, scope: !1760)
!1764 = !DILocation(line: 714, column: 8, scope: !1765)
!1765 = distinct !DILexicalBlock(scope: !1752, file: !1, line: 714, column: 8)
!1766 = !DILocation(line: 714, column: 11, scope: !1765)
!1767 = !DILocation(line: 714, column: 19, scope: !1765)
!1768 = !DILocation(line: 714, column: 28, scope: !1765)
!1769 = !DILocation(line: 714, column: 8, scope: !1752)
!1770 = !DILocation(line: 715, column: 25, scope: !1765)
!1771 = !DILocation(line: 715, column: 5, scope: !1765)
!1772 = !DILocation(line: 716, column: 9, scope: !1773)
!1773 = distinct !DILexicalBlock(scope: !1752, file: !1, line: 716, column: 8)
!1774 = !DILocation(line: 716, column: 15, scope: !1773)
!1775 = !DILocation(line: 716, column: 13, scope: !1773)
!1776 = !DILocation(line: 716, column: 25, scope: !1773)
!1777 = !DILocation(line: 716, column: 29, scope: !1778)
!1778 = !DILexicalBlockFile(scope: !1773, file: !1, discriminator: 1)
!1779 = !DILocation(line: 716, column: 43, scope: !1778)
!1780 = !DILocation(line: 716, column: 8, scope: !1778)
!1781 = !DILocation(line: 717, column: 16, scope: !1782)
!1782 = distinct !DILexicalBlock(scope: !1773, file: !1, line: 716, column: 49)
!1783 = !DILocation(line: 717, column: 14, scope: !1782)
!1784 = !DILocation(line: 718, column: 21, scope: !1782)
!1785 = !DILocation(line: 718, column: 19, scope: !1782)
!1786 = !DILocation(line: 719, column: 4, scope: !1782)
!1787 = !DILocation(line: 720, column: 3, scope: !1752)
!1788 = !DILocation(line: 721, column: 2, scope: !1747)
!1789 = !DILocation(line: 709, column: 26, scope: !1790)
!1790 = !DILexicalBlockFile(scope: !1741, file: !1, discriminator: 2)
!1791 = !DILocation(line: 709, column: 30, scope: !1790)
!1792 = !DILocation(line: 709, column: 33, scope: !1790)
!1793 = !DILocation(line: 709, column: 39, scope: !1790)
!1794 = !DILocation(line: 709, column: 2, scope: !1790)
!1795 = !DILocation(line: 727, column: 6, scope: !1796)
!1796 = distinct !DILexicalBlock(scope: !391, file: !1, line: 727, column: 6)
!1797 = !DILocation(line: 727, column: 20, scope: !1796)
!1798 = !DILocation(line: 727, column: 6, scope: !391)
!1799 = !DILocation(line: 728, column: 22, scope: !1800)
!1800 = distinct !DILexicalBlock(scope: !1796, file: !1, line: 727, column: 25)
!1801 = !DILocation(line: 728, column: 25, scope: !1800)
!1802 = !DILocation(line: 728, column: 3, scope: !1800)
!1803 = !DILocation(line: 730, column: 3, scope: !1800)
!1804 = !DILocation(line: 737, column: 6, scope: !1805)
!1805 = distinct !DILexicalBlock(scope: !391, file: !1, line: 737, column: 6)
!1806 = !DILocation(line: 737, column: 15, scope: !1805)
!1807 = !DILocation(line: 737, column: 6, scope: !391)
!1808 = !DILocation(line: 738, column: 22, scope: !1809)
!1809 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 737, column: 20)
!1810 = !DILocation(line: 738, column: 25, scope: !1809)
!1811 = !DILocation(line: 738, column: 3, scope: !1809)
!1812 = !DILocation(line: 740, column: 3, scope: !1809)
!1813 = !DILocation(line: 743, column: 10, scope: !391)
!1814 = !DILocation(line: 743, column: 2, scope: !391)
!1815 = !DILocation(line: 744, column: 1, scope: !391)
!1816 = !DILocalVariable(name: "a", arg: 1, scope: !392, file: !1, line: 989, type: !4)
!1817 = !DILocation(line: 989, column: 36, scope: !392)
!1818 = !DILocalVariable(name: "f", scope: !392, file: !1, line: 991, type: !169)
!1819 = !DILocation(line: 991, column: 30, scope: !392)
!1820 = !DILocation(line: 991, column: 34, scope: !392)
!1821 = !DILocation(line: 991, column: 37, scope: !392)
!1822 = !DILocalVariable(name: "r", scope: !392, file: !1, line: 992, type: !23)
!1823 = !DILocation(line: 992, column: 6, scope: !392)
!1824 = !DILocation(line: 994, column: 2, scope: !392)
!1825 = !DILocation(line: 994, column: 9, scope: !1826)
!1826 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!1827 = !DILocation(line: 994, column: 11, scope: !1826)
!1828 = !DILocation(line: 994, column: 2, scope: !1826)
!1829 = !DILocalVariable(name: "t", scope: !1830, file: !1, line: 995, type: !169)
!1830 = distinct !DILexicalBlock(scope: !392, file: !1, line: 994, column: 20)
!1831 = !DILocation(line: 995, column: 31, scope: !1830)
!1832 = !DILocation(line: 995, column: 35, scope: !1830)
!1833 = !DILocation(line: 995, column: 38, scope: !1830)
!1834 = !DILocation(line: 996, column: 8, scope: !1835)
!1835 = distinct !DILexicalBlock(scope: !1830, file: !1, line: 996, column: 7)
!1836 = !DILocation(line: 996, column: 11, scope: !1835)
!1837 = !DILocation(line: 996, column: 18, scope: !1835)
!1838 = !DILocation(line: 996, column: 21, scope: !1839)
!1839 = !DILexicalBlockFile(scope: !1835, file: !1, discriminator: 1)
!1840 = !DILocation(line: 996, column: 24, scope: !1839)
!1841 = !DILocation(line: 996, column: 30, scope: !1839)
!1842 = !DILocation(line: 996, column: 7, scope: !1839)
!1843 = !DILocalVariable(name: "r1", scope: !1844, file: !1, line: 997, type: !23)
!1844 = distinct !DILexicalBlock(scope: !1835, file: !1, line: 996, column: 39)
!1845 = !DILocation(line: 997, column: 8, scope: !1844)
!1846 = !DILocation(line: 997, column: 14, scope: !1844)
!1847 = !DILocation(line: 997, column: 17, scope: !1844)
!1848 = !DILocation(line: 997, column: 24, scope: !1844)
!1849 = !DILocation(line: 997, column: 13, scope: !1844)
!1850 = !DILocation(line: 998, column: 4, scope: !1844)
!1851 = !DILocation(line: 998, column: 7, scope: !1844)
!1852 = !DILocation(line: 998, column: 14, scope: !1844)
!1853 = !DILocation(line: 999, column: 8, scope: !1854)
!1854 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 999, column: 8)
!1855 = !DILocation(line: 999, column: 13, scope: !1854)
!1856 = !DILocation(line: 999, column: 11, scope: !1854)
!1857 = !DILocation(line: 999, column: 8, scope: !1844)
!1858 = !DILocation(line: 1000, column: 9, scope: !1854)
!1859 = !DILocation(line: 1000, column: 7, scope: !1854)
!1860 = !DILocation(line: 1000, column: 5, scope: !1854)
!1861 = !DILocation(line: 1001, column: 3, scope: !1844)
!1862 = !DILocation(line: 1002, column: 8, scope: !1830)
!1863 = !DILocation(line: 1002, column: 11, scope: !1830)
!1864 = !DILocation(line: 1002, column: 3, scope: !1830)
!1865 = !DILocation(line: 1003, column: 3, scope: !1830)
!1866 = !DILocation(line: 1003, column: 6, scope: !1830)
!1867 = !DILocation(line: 1003, column: 13, scope: !1830)
!1868 = !DILocation(line: 1004, column: 7, scope: !1830)
!1869 = !DILocation(line: 1004, column: 5, scope: !1830)
!1870 = !DILocation(line: 994, column: 2, scope: !1871)
!1871 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 2)
!1872 = !DILocation(line: 1006, column: 9, scope: !392)
!1873 = !DILocation(line: 1006, column: 2, scope: !392)
!1874 = !DILocalVariable(name: "_a", arg: 1, scope: !331, file: !1, line: 751, type: !24)
!1875 = !DILocation(line: 751, column: 46, scope: !331)
!1876 = !DILocalVariable(name: "a", scope: !331, file: !1, line: 753, type: !4)
!1877 = !DILocation(line: 753, column: 23, scope: !331)
!1878 = !DILocation(line: 753, column: 50, scope: !331)
!1879 = !DILocation(line: 753, column: 27, scope: !331)
!1880 = !DILocation(line: 754, column: 2, scope: !331)
!1881 = !DILocalVariable(name: "magic_test", scope: !1882, file: !1, line: 754, type: !23)
!1882 = distinct !DILexicalBlock(scope: !331, file: !1, line: 754, column: 2)
!1883 = !DILocation(line: 754, column: 2, scope: !1882)
!1884 = !DILocation(line: 754, column: 2, scope: !1885)
!1885 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 1)
!1886 = !DILocation(line: 754, column: 2, scope: !1887)
!1887 = !DILexicalBlockFile(scope: !1888, file: !1, discriminator: 2)
!1888 = distinct !DILexicalBlock(scope: !1882, file: !1, line: 754, column: 2)
!1889 = !DILocation(line: 754, column: 2, scope: !1890)
!1890 = !DILexicalBlockFile(scope: !1882, file: !1, discriminator: 3)
!1891 = !DILocation(line: 756, column: 10, scope: !331)
!1892 = !DILocation(line: 756, column: 13, scope: !331)
!1893 = !DILocation(line: 756, column: 2, scope: !331)
!1894 = !DILocation(line: 757, column: 1, scope: !331)
!1895 = !DILocalVariable(name: "_a", arg: 1, scope: !334, file: !1, line: 778, type: !24)
!1896 = !DILocation(line: 778, column: 52, scope: !334)
!1897 = !DILocalVariable(name: "a", scope: !334, file: !1, line: 780, type: !4)
!1898 = !DILocation(line: 780, column: 23, scope: !334)
!1899 = !DILocation(line: 780, column: 50, scope: !334)
!1900 = !DILocation(line: 780, column: 27, scope: !334)
!1901 = !DILocalVariable(name: "format_supports_encryption", scope: !334, file: !1, line: 781, type: !23)
!1902 = !DILocation(line: 781, column: 6, scope: !334)
!1903 = !DILocation(line: 781, column: 68, scope: !334)
!1904 = !DILocation(line: 781, column: 35, scope: !334)
!1905 = !DILocation(line: 782, column: 4, scope: !334)
!1906 = !DILocation(line: 784, column: 7, scope: !1907)
!1907 = distinct !DILexicalBlock(scope: !334, file: !1, line: 784, column: 6)
!1908 = !DILocation(line: 784, column: 10, scope: !1907)
!1909 = !DILocation(line: 784, column: 14, scope: !1910)
!1910 = !DILexicalBlockFile(scope: !1907, file: !1, discriminator: 1)
!1911 = !DILocation(line: 784, column: 6, scope: !1910)
!1912 = !DILocation(line: 786, column: 3, scope: !1913)
!1913 = distinct !DILexicalBlock(scope: !1907, file: !1, line: 784, column: 42)
!1914 = !DILocation(line: 790, column: 6, scope: !1915)
!1915 = distinct !DILexicalBlock(scope: !334, file: !1, line: 790, column: 6)
!1916 = !DILocation(line: 790, column: 9, scope: !1915)
!1917 = !DILocation(line: 790, column: 16, scope: !1915)
!1918 = !DILocation(line: 790, column: 19, scope: !1919)
!1919 = !DILexicalBlockFile(scope: !1915, file: !1, discriminator: 1)
!1920 = !DILocation(line: 790, column: 22, scope: !1919)
!1921 = !DILocation(line: 790, column: 30, scope: !1919)
!1922 = !DILocation(line: 790, column: 6, scope: !1919)
!1923 = !DILocation(line: 791, column: 11, scope: !1924)
!1924 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 790, column: 53)
!1925 = !DILocation(line: 791, column: 14, scope: !1924)
!1926 = !DILocation(line: 791, column: 22, scope: !1924)
!1927 = !DILocation(line: 791, column: 45, scope: !1924)
!1928 = !DILocation(line: 791, column: 10, scope: !1924)
!1929 = !DILocation(line: 791, column: 3, scope: !1924)
!1930 = !DILocation(line: 795, column: 2, scope: !334)
!1931 = !DILocation(line: 796, column: 1, scope: !334)
!1932 = !DILocalVariable(name: "_a", arg: 1, scope: !335, file: !1, line: 803, type: !24)
!1933 = !DILocation(line: 803, column: 50, scope: !335)
!1934 = !DILocalVariable(name: "a", scope: !335, file: !1, line: 805, type: !4)
!1935 = !DILocation(line: 805, column: 23, scope: !335)
!1936 = !DILocation(line: 805, column: 50, scope: !335)
!1937 = !DILocation(line: 805, column: 27, scope: !335)
!1938 = !DILocation(line: 806, column: 6, scope: !1939)
!1939 = distinct !DILexicalBlock(scope: !335, file: !1, line: 806, column: 6)
!1940 = !DILocation(line: 806, column: 8, scope: !1939)
!1941 = !DILocation(line: 806, column: 11, scope: !1942)
!1942 = !DILexicalBlockFile(scope: !1939, file: !1, discriminator: 1)
!1943 = !DILocation(line: 806, column: 14, scope: !1942)
!1944 = !DILocation(line: 806, column: 21, scope: !1942)
!1945 = !DILocation(line: 806, column: 24, scope: !1946)
!1946 = !DILexicalBlockFile(scope: !1939, file: !1, discriminator: 2)
!1947 = !DILocation(line: 806, column: 27, scope: !1946)
!1948 = !DILocation(line: 806, column: 35, scope: !1946)
!1949 = !DILocation(line: 806, column: 6, scope: !1946)
!1950 = !DILocation(line: 807, column: 11, scope: !1951)
!1951 = distinct !DILexicalBlock(scope: !1939, file: !1, line: 806, column: 55)
!1952 = !DILocation(line: 807, column: 14, scope: !1951)
!1953 = !DILocation(line: 807, column: 22, scope: !1951)
!1954 = !DILocation(line: 807, column: 42, scope: !1951)
!1955 = !DILocation(line: 807, column: 10, scope: !1951)
!1956 = !DILocation(line: 807, column: 3, scope: !1951)
!1957 = !DILocation(line: 809, column: 2, scope: !335)
!1958 = !DILocation(line: 810, column: 1, scope: !335)
!1959 = !DILocalVariable(name: "_a", arg: 1, scope: !336, file: !1, line: 824, type: !24)
!1960 = !DILocation(line: 824, column: 35, scope: !336)
!1961 = !DILocalVariable(name: "buff", arg: 2, scope: !336, file: !1, line: 824, type: !122)
!1962 = !DILocation(line: 824, column: 45, scope: !336)
!1963 = !DILocalVariable(name: "s", arg: 3, scope: !336, file: !1, line: 824, type: !45)
!1964 = !DILocation(line: 824, column: 58, scope: !336)
!1965 = !DILocalVariable(name: "a", scope: !336, file: !1, line: 826, type: !24)
!1966 = !DILocation(line: 826, column: 18, scope: !336)
!1967 = !DILocation(line: 826, column: 40, scope: !336)
!1968 = !DILocalVariable(name: "dest", scope: !336, file: !1, line: 827, type: !95)
!1969 = !DILocation(line: 827, column: 8, scope: !336)
!1970 = !DILocalVariable(name: "read_buf", scope: !336, file: !1, line: 828, type: !43)
!1971 = !DILocation(line: 828, column: 14, scope: !336)
!1972 = !DILocalVariable(name: "bytes_read", scope: !336, file: !1, line: 829, type: !45)
!1973 = !DILocation(line: 829, column: 10, scope: !336)
!1974 = !DILocalVariable(name: "len", scope: !336, file: !1, line: 830, type: !45)
!1975 = !DILocation(line: 830, column: 10, scope: !336)
!1976 = !DILocalVariable(name: "r", scope: !336, file: !1, line: 831, type: !23)
!1977 = !DILocation(line: 831, column: 7, scope: !336)
!1978 = !DILocation(line: 833, column: 13, scope: !336)
!1979 = !DILocation(line: 834, column: 17, scope: !336)
!1980 = !DILocation(line: 834, column: 7, scope: !336)
!1981 = !DILocation(line: 836, column: 2, scope: !336)
!1982 = !DILocation(line: 836, column: 9, scope: !1983)
!1983 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 1)
!1984 = !DILocation(line: 836, column: 11, scope: !1983)
!1985 = !DILocation(line: 836, column: 2, scope: !1983)
!1986 = !DILocation(line: 837, column: 7, scope: !1987)
!1987 = distinct !DILexicalBlock(scope: !1988, file: !1, line: 837, column: 7)
!1988 = distinct !DILexicalBlock(scope: !336, file: !1, line: 836, column: 16)
!1989 = !DILocation(line: 837, column: 10, scope: !1987)
!1990 = !DILocation(line: 837, column: 30, scope: !1987)
!1991 = !DILocation(line: 837, column: 7, scope: !1988)
!1992 = !DILocation(line: 838, column: 15, scope: !1993)
!1993 = distinct !DILexicalBlock(scope: !1987, file: !1, line: 837, column: 36)
!1994 = !DILocation(line: 838, column: 18, scope: !1993)
!1995 = !DILocation(line: 838, column: 13, scope: !1993)
!1996 = !DILocation(line: 839, column: 4, scope: !1993)
!1997 = !DILocation(line: 839, column: 7, scope: !1993)
!1998 = !DILocation(line: 839, column: 31, scope: !1993)
!1999 = !DILocation(line: 840, column: 29, scope: !1993)
!2000 = !DILocation(line: 840, column: 4, scope: !1993)
!2001 = !DILocation(line: 840, column: 7, scope: !1993)
!2002 = !DILocation(line: 840, column: 27, scope: !1993)
!2003 = !DILocation(line: 841, column: 32, scope: !1993)
!2004 = !DILocation(line: 842, column: 9, scope: !1993)
!2005 = !DILocation(line: 842, column: 12, scope: !1993)
!2006 = !DILocation(line: 842, column: 34, scope: !1993)
!2007 = !DILocation(line: 842, column: 37, scope: !1993)
!2008 = !DILocation(line: 841, column: 8, scope: !1993)
!2009 = !DILocation(line: 841, column: 6, scope: !1993)
!2010 = !DILocation(line: 843, column: 25, scope: !1993)
!2011 = !DILocation(line: 843, column: 4, scope: !1993)
!2012 = !DILocation(line: 843, column: 7, scope: !1993)
!2013 = !DILocation(line: 843, column: 23, scope: !1993)
!2014 = !DILocation(line: 844, column: 8, scope: !2015)
!2015 = distinct !DILexicalBlock(scope: !1993, file: !1, line: 844, column: 8)
!2016 = !DILocation(line: 844, column: 10, scope: !2015)
!2017 = !DILocation(line: 844, column: 8, scope: !1993)
!2018 = !DILocation(line: 845, column: 13, scope: !2015)
!2019 = !DILocation(line: 845, column: 5, scope: !2015)
!2020 = !DILocation(line: 851, column: 8, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !1993, file: !1, line: 851, column: 8)
!2022 = !DILocation(line: 851, column: 10, scope: !2021)
!2023 = !DILocation(line: 851, column: 8, scope: !1993)
!2024 = !DILocation(line: 852, column: 13, scope: !2021)
!2025 = !DILocation(line: 852, column: 12, scope: !2021)
!2026 = !DILocation(line: 852, column: 5, scope: !2021)
!2027 = !DILocation(line: 853, column: 3, scope: !1993)
!2028 = !DILocation(line: 855, column: 7, scope: !2029)
!2029 = distinct !DILexicalBlock(scope: !1988, file: !1, line: 855, column: 7)
!2030 = !DILocation(line: 855, column: 10, scope: !2029)
!2031 = !DILocation(line: 855, column: 29, scope: !2029)
!2032 = !DILocation(line: 855, column: 32, scope: !2029)
!2033 = !DILocation(line: 855, column: 27, scope: !2029)
!2034 = !DILocation(line: 855, column: 7, scope: !1988)
!2035 = !DILocation(line: 856, column: 22, scope: !2036)
!2036 = distinct !DILexicalBlock(scope: !2029, file: !1, line: 855, column: 57)
!2037 = !DILocation(line: 856, column: 4, scope: !2036)
!2038 = !DILocation(line: 858, column: 4, scope: !2036)
!2039 = !DILocation(line: 862, column: 7, scope: !2040)
!2040 = distinct !DILexicalBlock(scope: !1988, file: !1, line: 862, column: 7)
!2041 = !DILocation(line: 862, column: 10, scope: !2040)
!2042 = !DILocation(line: 862, column: 45, scope: !2040)
!2043 = !DILocation(line: 862, column: 34, scope: !2040)
!2044 = !DILocation(line: 863, column: 7, scope: !2040)
!2045 = !DILocation(line: 863, column: 10, scope: !2040)
!2046 = !DILocation(line: 862, column: 47, scope: !2040)
!2047 = !DILocation(line: 862, column: 7, scope: !1988)
!2048 = !DILocation(line: 864, column: 10, scope: !2049)
!2049 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 863, column: 28)
!2050 = !DILocation(line: 864, column: 8, scope: !2049)
!2051 = !DILocation(line: 865, column: 3, scope: !2049)
!2052 = !DILocation(line: 865, column: 14, scope: !2053)
!2053 = !DILexicalBlockFile(scope: !2054, file: !1, discriminator: 1)
!2054 = distinct !DILexicalBlock(scope: !2040, file: !1, line: 865, column: 14)
!2055 = !DILocation(line: 865, column: 17, scope: !2053)
!2056 = !DILocation(line: 866, column: 7, scope: !2054)
!2057 = !DILocation(line: 866, column: 10, scope: !2054)
!2058 = !DILocation(line: 865, column: 41, scope: !2053)
!2059 = !DILocation(line: 867, column: 19, scope: !2060)
!2060 = distinct !DILexicalBlock(scope: !2054, file: !1, line: 866, column: 28)
!2061 = !DILocation(line: 867, column: 22, scope: !2060)
!2062 = !DILocation(line: 868, column: 8, scope: !2060)
!2063 = !DILocation(line: 868, column: 11, scope: !2060)
!2064 = !DILocation(line: 867, column: 39, scope: !2060)
!2065 = !DILocation(line: 867, column: 8, scope: !2060)
!2066 = !DILocation(line: 869, column: 3, scope: !2060)
!2067 = !DILocation(line: 870, column: 8, scope: !2054)
!2068 = !DILocation(line: 873, column: 10, scope: !1988)
!2069 = !DILocation(line: 873, column: 19, scope: !1988)
!2070 = !DILocation(line: 873, column: 3, scope: !1988)
!2071 = !DILocation(line: 874, column: 8, scope: !1988)
!2072 = !DILocation(line: 874, column: 5, scope: !1988)
!2073 = !DILocation(line: 875, column: 33, scope: !1988)
!2074 = !DILocation(line: 875, column: 3, scope: !1988)
!2075 = !DILocation(line: 875, column: 6, scope: !1988)
!2076 = !DILocation(line: 875, column: 30, scope: !1988)
!2077 = !DILocation(line: 876, column: 11, scope: !1988)
!2078 = !DILocation(line: 876, column: 8, scope: !1988)
!2079 = !DILocation(line: 877, column: 17, scope: !1988)
!2080 = !DILocation(line: 877, column: 14, scope: !1988)
!2081 = !DILocation(line: 880, column: 7, scope: !2082)
!2082 = distinct !DILexicalBlock(scope: !1988, file: !1, line: 880, column: 7)
!2083 = !DILocation(line: 880, column: 9, scope: !2082)
!2084 = !DILocation(line: 880, column: 7, scope: !1988)
!2085 = !DILocation(line: 881, column: 10, scope: !2086)
!2086 = distinct !DILexicalBlock(scope: !2082, file: !1, line: 880, column: 14)
!2087 = !DILocation(line: 881, column: 13, scope: !2086)
!2088 = !DILocation(line: 881, column: 8, scope: !2086)
!2089 = !DILocation(line: 882, column: 8, scope: !2090)
!2090 = distinct !DILexicalBlock(scope: !2086, file: !1, line: 882, column: 8)
!2091 = !DILocation(line: 882, column: 14, scope: !2090)
!2092 = !DILocation(line: 882, column: 12, scope: !2090)
!2093 = !DILocation(line: 882, column: 8, scope: !2086)
!2094 = !DILocation(line: 883, column: 11, scope: !2090)
!2095 = !DILocation(line: 883, column: 9, scope: !2090)
!2096 = !DILocation(line: 883, column: 5, scope: !2090)
!2097 = !DILocation(line: 884, column: 11, scope: !2086)
!2098 = !DILocation(line: 884, column: 17, scope: !2086)
!2099 = !DILocation(line: 884, column: 20, scope: !2086)
!2100 = !DILocation(line: 884, column: 37, scope: !2086)
!2101 = !DILocation(line: 884, column: 4, scope: !2086)
!2102 = !DILocation(line: 885, column: 9, scope: !2086)
!2103 = !DILocation(line: 885, column: 6, scope: !2086)
!2104 = !DILocation(line: 886, column: 26, scope: !2086)
!2105 = !DILocation(line: 886, column: 4, scope: !2086)
!2106 = !DILocation(line: 886, column: 7, scope: !2086)
!2107 = !DILocation(line: 886, column: 23, scope: !2086)
!2108 = !DILocation(line: 887, column: 30, scope: !2086)
!2109 = !DILocation(line: 887, column: 4, scope: !2086)
!2110 = !DILocation(line: 887, column: 7, scope: !2086)
!2111 = !DILocation(line: 887, column: 27, scope: !2086)
!2112 = !DILocation(line: 888, column: 34, scope: !2086)
!2113 = !DILocation(line: 888, column: 4, scope: !2086)
!2114 = !DILocation(line: 888, column: 7, scope: !2086)
!2115 = !DILocation(line: 888, column: 31, scope: !2086)
!2116 = !DILocation(line: 889, column: 27, scope: !2086)
!2117 = !DILocation(line: 889, column: 4, scope: !2086)
!2118 = !DILocation(line: 889, column: 7, scope: !2086)
!2119 = !DILocation(line: 889, column: 24, scope: !2086)
!2120 = !DILocation(line: 890, column: 12, scope: !2086)
!2121 = !DILocation(line: 890, column: 9, scope: !2086)
!2122 = !DILocation(line: 891, column: 18, scope: !2086)
!2123 = !DILocation(line: 891, column: 15, scope: !2086)
!2124 = !DILocation(line: 892, column: 3, scope: !2086)
!2125 = !DILocation(line: 836, column: 2, scope: !2126)
!2126 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 2)
!2127 = !DILocation(line: 894, column: 2, scope: !336)
!2128 = !DILocation(line: 894, column: 5, scope: !336)
!2129 = !DILocation(line: 894, column: 29, scope: !336)
!2130 = !DILocation(line: 895, column: 2, scope: !336)
!2131 = !DILocation(line: 895, column: 5, scope: !336)
!2132 = !DILocation(line: 895, column: 25, scope: !336)
!2133 = !DILocation(line: 896, column: 10, scope: !336)
!2134 = !DILocation(line: 896, column: 2, scope: !336)
!2135 = !DILocation(line: 897, column: 1, scope: !336)
!2136 = !DILocalVariable(name: "a", arg: 1, scope: !339, file: !1, line: 902, type: !24)
!2137 = !DILocation(line: 902, column: 49, scope: !339)
!2138 = !DILocation(line: 904, column: 2, scope: !339)
!2139 = !DILocation(line: 904, column: 5, scope: !339)
!2140 = !DILocation(line: 904, column: 29, scope: !339)
!2141 = !DILocation(line: 905, column: 2, scope: !339)
!2142 = !DILocation(line: 905, column: 5, scope: !339)
!2143 = !DILocation(line: 905, column: 25, scope: !339)
!2144 = !DILocation(line: 906, column: 2, scope: !339)
!2145 = !DILocation(line: 906, column: 5, scope: !339)
!2146 = !DILocation(line: 906, column: 29, scope: !339)
!2147 = !DILocation(line: 907, column: 2, scope: !339)
!2148 = !DILocation(line: 907, column: 5, scope: !339)
!2149 = !DILocation(line: 907, column: 25, scope: !339)
!2150 = !DILocation(line: 910, column: 4, scope: !339)
!2151 = !DILocation(line: 910, column: 7, scope: !339)
!2152 = !DILocation(line: 910, column: 23, scope: !339)
!2153 = !DILocation(line: 911, column: 4, scope: !339)
!2154 = !DILocation(line: 911, column: 7, scope: !339)
!2155 = !DILocation(line: 911, column: 24, scope: !339)
!2156 = !DILocation(line: 912, column: 1, scope: !339)
!2157 = !DILocalVariable(name: "_a", arg: 1, scope: !342, file: !1, line: 918, type: !24)
!2158 = !DILocation(line: 918, column: 40, scope: !342)
!2159 = !DILocalVariable(name: "a", scope: !342, file: !1, line: 920, type: !4)
!2160 = !DILocation(line: 920, column: 23, scope: !342)
!2161 = !DILocation(line: 920, column: 50, scope: !342)
!2162 = !DILocation(line: 920, column: 27, scope: !342)
!2163 = !DILocalVariable(name: "r", scope: !342, file: !1, line: 921, type: !23)
!2164 = !DILocation(line: 921, column: 6, scope: !342)
!2165 = !DILocalVariable(name: "buff", scope: !342, file: !1, line: 922, type: !43)
!2166 = !DILocation(line: 922, column: 14, scope: !342)
!2167 = !DILocalVariable(name: "size", scope: !342, file: !1, line: 923, type: !45)
!2168 = !DILocation(line: 923, column: 9, scope: !342)
!2169 = !DILocalVariable(name: "offset", scope: !342, file: !1, line: 924, type: !52)
!2170 = !DILocation(line: 924, column: 10, scope: !342)
!2171 = !DILocation(line: 926, column: 2, scope: !342)
!2172 = !DILocalVariable(name: "magic_test", scope: !2173, file: !1, line: 926, type: !23)
!2173 = distinct !DILexicalBlock(scope: !342, file: !1, line: 926, column: 2)
!2174 = !DILocation(line: 926, column: 2, scope: !2173)
!2175 = !DILocation(line: 926, column: 2, scope: !2176)
!2176 = !DILexicalBlockFile(scope: !2173, file: !1, discriminator: 1)
!2177 = !DILocation(line: 926, column: 2, scope: !2178)
!2178 = !DILexicalBlockFile(scope: !2179, file: !1, discriminator: 2)
!2179 = distinct !DILexicalBlock(scope: !2173, file: !1, line: 926, column: 2)
!2180 = !DILocation(line: 926, column: 2, scope: !2181)
!2181 = !DILexicalBlockFile(scope: !2173, file: !1, discriminator: 3)
!2182 = !DILocation(line: 929, column: 6, scope: !2183)
!2183 = distinct !DILexicalBlock(scope: !342, file: !1, line: 929, column: 6)
!2184 = !DILocation(line: 929, column: 9, scope: !2183)
!2185 = !DILocation(line: 929, column: 17, scope: !2183)
!2186 = !DILocation(line: 929, column: 32, scope: !2183)
!2187 = !DILocation(line: 929, column: 6, scope: !342)
!2188 = !DILocation(line: 930, column: 8, scope: !2183)
!2189 = !DILocation(line: 930, column: 11, scope: !2183)
!2190 = !DILocation(line: 930, column: 19, scope: !2183)
!2191 = !DILocation(line: 930, column: 35, scope: !2183)
!2192 = !DILocation(line: 930, column: 7, scope: !2183)
!2193 = !DILocation(line: 930, column: 5, scope: !2183)
!2194 = !DILocation(line: 930, column: 3, scope: !2183)
!2195 = !DILocation(line: 932, column: 3, scope: !2196)
!2196 = distinct !DILexicalBlock(scope: !2183, file: !1, line: 931, column: 7)
!2197 = !DILocation(line: 932, column: 40, scope: !2198)
!2198 = !DILexicalBlockFile(scope: !2196, file: !1, discriminator: 1)
!2199 = !DILocation(line: 932, column: 43, scope: !2198)
!2200 = !DILocation(line: 932, column: 15, scope: !2198)
!2201 = !DILocation(line: 932, column: 13, scope: !2198)
!2202 = !DILocation(line: 934, column: 7, scope: !2196)
!2203 = !DILocation(line: 932, column: 3, scope: !2198)
!2204 = !DILocation(line: 932, column: 3, scope: !2205)
!2205 = !DILexicalBlockFile(scope: !2196, file: !1, discriminator: 2)
!2206 = !DILocation(line: 938, column: 6, scope: !2207)
!2207 = distinct !DILexicalBlock(scope: !342, file: !1, line: 938, column: 6)
!2208 = !DILocation(line: 938, column: 8, scope: !2207)
!2209 = !DILocation(line: 938, column: 6, scope: !342)
!2210 = !DILocation(line: 939, column: 5, scope: !2207)
!2211 = !DILocation(line: 939, column: 3, scope: !2207)
!2212 = !DILocation(line: 941, column: 2, scope: !342)
!2213 = !DILocation(line: 941, column: 5, scope: !342)
!2214 = !DILocation(line: 941, column: 13, scope: !342)
!2215 = !DILocation(line: 941, column: 19, scope: !342)
!2216 = !DILocation(line: 942, column: 10, scope: !342)
!2217 = !DILocation(line: 942, column: 2, scope: !342)
!2218 = !DILocation(line: 943, column: 1, scope: !342)
!2219 = !DILocalVariable(name: "_a", arg: 1, scope: !343, file: !1, line: 946, type: !24)
!2220 = !DILocation(line: 946, column: 35, scope: !343)
!2221 = !DILocalVariable(name: "offset", arg: 2, scope: !343, file: !1, line: 946, type: !52)
!2222 = !DILocation(line: 946, column: 47, scope: !343)
!2223 = !DILocalVariable(name: "whence", arg: 3, scope: !343, file: !1, line: 946, type: !23)
!2224 = !DILocation(line: 946, column: 59, scope: !343)
!2225 = !DILocalVariable(name: "a", scope: !343, file: !1, line: 948, type: !4)
!2226 = !DILocation(line: 948, column: 23, scope: !343)
!2227 = !DILocation(line: 948, column: 50, scope: !343)
!2228 = !DILocation(line: 948, column: 27, scope: !343)
!2229 = !DILocation(line: 949, column: 2, scope: !343)
!2230 = !DILocalVariable(name: "magic_test", scope: !2231, file: !1, line: 949, type: !23)
!2231 = distinct !DILexicalBlock(scope: !343, file: !1, line: 949, column: 2)
!2232 = !DILocation(line: 949, column: 2, scope: !2231)
!2233 = !DILocation(line: 949, column: 2, scope: !2234)
!2234 = !DILexicalBlockFile(scope: !2231, file: !1, discriminator: 1)
!2235 = !DILocation(line: 949, column: 2, scope: !2236)
!2236 = !DILexicalBlockFile(scope: !2237, file: !1, discriminator: 2)
!2237 = distinct !DILexicalBlock(scope: !2231, file: !1, line: 949, column: 2)
!2238 = !DILocation(line: 949, column: 2, scope: !2239)
!2239 = !DILexicalBlockFile(scope: !2231, file: !1, discriminator: 3)
!2240 = !DILocation(line: 952, column: 6, scope: !2241)
!2241 = distinct !DILexicalBlock(scope: !343, file: !1, line: 952, column: 6)
!2242 = !DILocation(line: 952, column: 9, scope: !2241)
!2243 = !DILocation(line: 952, column: 17, scope: !2241)
!2244 = !DILocation(line: 952, column: 27, scope: !2241)
!2245 = !DILocation(line: 952, column: 6, scope: !343)
!2246 = !DILocation(line: 953, column: 22, scope: !2247)
!2247 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 952, column: 36)
!2248 = !DILocation(line: 953, column: 25, scope: !2247)
!2249 = !DILocation(line: 953, column: 3, scope: !2247)
!2250 = !DILocation(line: 956, column: 3, scope: !2247)
!2251 = !DILocation(line: 959, column: 10, scope: !343)
!2252 = !DILocation(line: 959, column: 13, scope: !343)
!2253 = !DILocation(line: 959, column: 21, scope: !343)
!2254 = !DILocation(line: 959, column: 32, scope: !343)
!2255 = !DILocation(line: 959, column: 35, scope: !343)
!2256 = !DILocation(line: 959, column: 43, scope: !343)
!2257 = !DILocation(line: 959, column: 9, scope: !343)
!2258 = !DILocation(line: 959, column: 2, scope: !343)
!2259 = !DILocation(line: 960, column: 1, scope: !343)
!2260 = !DILocalVariable(name: "a", arg: 1, scope: !346, file: !1, line: 1010, type: !4)
!2261 = !DILocation(line: 1010, column: 50, scope: !346)
!2262 = !DILocation(line: 1013, column: 16, scope: !346)
!2263 = !DILocation(line: 1013, column: 2, scope: !346)
!2264 = !DILocation(line: 1015, column: 2, scope: !346)
!2265 = !DILocation(line: 1015, column: 9, scope: !2266)
!2266 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 1)
!2267 = !DILocation(line: 1015, column: 12, scope: !2266)
!2268 = !DILocation(line: 1015, column: 19, scope: !2266)
!2269 = !DILocation(line: 1015, column: 2, scope: !2266)
!2270 = !DILocalVariable(name: "t", scope: !2271, file: !1, line: 1016, type: !169)
!2271 = distinct !DILexicalBlock(scope: !346, file: !1, line: 1015, column: 28)
!2272 = !DILocation(line: 1016, column: 31, scope: !2271)
!2273 = !DILocation(line: 1016, column: 35, scope: !2271)
!2274 = !DILocation(line: 1016, column: 38, scope: !2271)
!2275 = !DILocation(line: 1016, column: 46, scope: !2271)
!2276 = !DILocation(line: 1017, column: 8, scope: !2271)
!2277 = !DILocation(line: 1017, column: 11, scope: !2271)
!2278 = !DILocation(line: 1017, column: 3, scope: !2271)
!2279 = !DILocation(line: 1018, column: 15, scope: !2271)
!2280 = !DILocation(line: 1018, column: 3, scope: !2271)
!2281 = !DILocation(line: 1018, column: 6, scope: !2271)
!2282 = !DILocation(line: 1018, column: 13, scope: !2271)
!2283 = !DILocation(line: 1015, column: 2, scope: !2284)
!2284 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 2)
!2285 = !DILocation(line: 1020, column: 1, scope: !346)
!2286 = !DILocalVariable(name: "a", arg: 1, scope: !349, file: !1, line: 1181, type: !4)
!2287 = !DILocation(line: 1181, column: 53, scope: !349)
!2288 = !DILocalVariable(name: "format_data", arg: 2, scope: !349, file: !1, line: 1182, type: !122)
!2289 = !DILocation(line: 1182, column: 11, scope: !349)
!2290 = !DILocalVariable(name: "name", arg: 3, scope: !349, file: !1, line: 1183, type: !80)
!2291 = !DILocation(line: 1183, column: 17, scope: !349)
!2292 = !DILocalVariable(name: "bid", arg: 4, scope: !349, file: !1, line: 1184, type: !234)
!2293 = !DILocation(line: 1184, column: 11, scope: !349)
!2294 = !DILocalVariable(name: "options", arg: 5, scope: !349, file: !1, line: 1185, type: !238)
!2295 = !DILocation(line: 1185, column: 11, scope: !349)
!2296 = !DILocalVariable(name: "read_header", arg: 6, scope: !349, file: !1, line: 1186, type: !242)
!2297 = !DILocation(line: 1186, column: 11, scope: !349)
!2298 = !DILocalVariable(name: "read_data", arg: 7, scope: !349, file: !1, line: 1187, type: !246)
!2299 = !DILocation(line: 1187, column: 11, scope: !349)
!2300 = !DILocalVariable(name: "read_data_skip", arg: 8, scope: !349, file: !1, line: 1188, type: !250)
!2301 = !DILocation(line: 1188, column: 11, scope: !349)
!2302 = !DILocalVariable(name: "seek_data", arg: 9, scope: !349, file: !1, line: 1189, type: !254)
!2303 = !DILocation(line: 1189, column: 15, scope: !349)
!2304 = !DILocalVariable(name: "cleanup", arg: 10, scope: !349, file: !1, line: 1190, type: !250)
!2305 = !DILocation(line: 1190, column: 11, scope: !349)
!2306 = !DILocalVariable(name: "format_capabilities", arg: 11, scope: !349, file: !1, line: 1191, type: !250)
!2307 = !DILocation(line: 1191, column: 11, scope: !349)
!2308 = !DILocalVariable(name: "has_encrypted_entries", arg: 12, scope: !349, file: !1, line: 1192, type: !250)
!2309 = !DILocation(line: 1192, column: 11, scope: !349)
!2310 = !DILocalVariable(name: "i", scope: !349, file: !1, line: 1194, type: !23)
!2311 = !DILocation(line: 1194, column: 6, scope: !349)
!2312 = !DILocalVariable(name: "number_slots", scope: !349, file: !1, line: 1194, type: !23)
!2313 = !DILocation(line: 1194, column: 9, scope: !349)
!2314 = !DILocation(line: 1196, column: 2, scope: !349)
!2315 = !DILocalVariable(name: "magic_test", scope: !2316, file: !1, line: 1196, type: !23)
!2316 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1196, column: 2)
!2317 = !DILocation(line: 1196, column: 2, scope: !2316)
!2318 = !DILocation(line: 1196, column: 2, scope: !2319)
!2319 = !DILexicalBlockFile(scope: !2316, file: !1, discriminator: 1)
!2320 = !DILocation(line: 1196, column: 2, scope: !2321)
!2321 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 2)
!2322 = distinct !DILexicalBlock(scope: !2316, file: !1, line: 1196, column: 2)
!2323 = !DILocation(line: 1196, column: 2, scope: !2324)
!2324 = !DILexicalBlockFile(scope: !2316, file: !1, discriminator: 3)
!2325 = !DILocation(line: 1200, column: 15, scope: !349)
!2326 = !DILocation(line: 1202, column: 9, scope: !2327)
!2327 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1202, column: 2)
!2328 = !DILocation(line: 1202, column: 7, scope: !2327)
!2329 = !DILocation(line: 1202, column: 14, scope: !2330)
!2330 = !DILexicalBlockFile(scope: !2331, file: !1, discriminator: 1)
!2331 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 1202, column: 2)
!2332 = !DILocation(line: 1202, column: 18, scope: !2330)
!2333 = !DILocation(line: 1202, column: 16, scope: !2330)
!2334 = !DILocation(line: 1202, column: 2, scope: !2330)
!2335 = !DILocation(line: 1203, column: 18, scope: !2336)
!2336 = distinct !DILexicalBlock(scope: !2337, file: !1, line: 1203, column: 7)
!2337 = distinct !DILexicalBlock(scope: !2331, file: !1, line: 1202, column: 37)
!2338 = !DILocation(line: 1203, column: 7, scope: !2336)
!2339 = !DILocation(line: 1203, column: 10, scope: !2336)
!2340 = !DILocation(line: 1203, column: 21, scope: !2336)
!2341 = !DILocation(line: 1203, column: 28, scope: !2336)
!2342 = !DILocation(line: 1203, column: 25, scope: !2336)
!2343 = !DILocation(line: 1203, column: 7, scope: !2337)
!2344 = !DILocation(line: 1204, column: 4, scope: !2336)
!2345 = !DILocation(line: 1205, column: 18, scope: !2346)
!2346 = distinct !DILexicalBlock(scope: !2337, file: !1, line: 1205, column: 7)
!2347 = !DILocation(line: 1205, column: 7, scope: !2346)
!2348 = !DILocation(line: 1205, column: 10, scope: !2346)
!2349 = !DILocation(line: 1205, column: 21, scope: !2346)
!2350 = !DILocation(line: 1205, column: 25, scope: !2346)
!2351 = !DILocation(line: 1205, column: 7, scope: !2337)
!2352 = !DILocation(line: 1206, column: 24, scope: !2353)
!2353 = distinct !DILexicalBlock(scope: !2346, file: !1, line: 1205, column: 34)
!2354 = !DILocation(line: 1206, column: 15, scope: !2353)
!2355 = !DILocation(line: 1206, column: 4, scope: !2353)
!2356 = !DILocation(line: 1206, column: 7, scope: !2353)
!2357 = !DILocation(line: 1206, column: 18, scope: !2353)
!2358 = !DILocation(line: 1206, column: 22, scope: !2353)
!2359 = !DILocation(line: 1207, column: 28, scope: !2353)
!2360 = !DILocation(line: 1207, column: 15, scope: !2353)
!2361 = !DILocation(line: 1207, column: 4, scope: !2353)
!2362 = !DILocation(line: 1207, column: 7, scope: !2353)
!2363 = !DILocation(line: 1207, column: 18, scope: !2353)
!2364 = !DILocation(line: 1207, column: 26, scope: !2353)
!2365 = !DILocation(line: 1208, column: 32, scope: !2353)
!2366 = !DILocation(line: 1208, column: 15, scope: !2353)
!2367 = !DILocation(line: 1208, column: 4, scope: !2353)
!2368 = !DILocation(line: 1208, column: 7, scope: !2353)
!2369 = !DILocation(line: 1208, column: 18, scope: !2353)
!2370 = !DILocation(line: 1208, column: 30, scope: !2353)
!2371 = !DILocation(line: 1209, column: 30, scope: !2353)
!2372 = !DILocation(line: 1209, column: 15, scope: !2353)
!2373 = !DILocation(line: 1209, column: 4, scope: !2353)
!2374 = !DILocation(line: 1209, column: 7, scope: !2353)
!2375 = !DILocation(line: 1209, column: 18, scope: !2353)
!2376 = !DILocation(line: 1209, column: 28, scope: !2353)
!2377 = !DILocation(line: 1210, column: 35, scope: !2353)
!2378 = !DILocation(line: 1210, column: 15, scope: !2353)
!2379 = !DILocation(line: 1210, column: 4, scope: !2353)
!2380 = !DILocation(line: 1210, column: 7, scope: !2353)
!2381 = !DILocation(line: 1210, column: 18, scope: !2353)
!2382 = !DILocation(line: 1210, column: 33, scope: !2353)
!2383 = !DILocation(line: 1211, column: 30, scope: !2353)
!2384 = !DILocation(line: 1211, column: 15, scope: !2353)
!2385 = !DILocation(line: 1211, column: 4, scope: !2353)
!2386 = !DILocation(line: 1211, column: 7, scope: !2353)
!2387 = !DILocation(line: 1211, column: 18, scope: !2353)
!2388 = !DILocation(line: 1211, column: 28, scope: !2353)
!2389 = !DILocation(line: 1212, column: 28, scope: !2353)
!2390 = !DILocation(line: 1212, column: 15, scope: !2353)
!2391 = !DILocation(line: 1212, column: 4, scope: !2353)
!2392 = !DILocation(line: 1212, column: 7, scope: !2353)
!2393 = !DILocation(line: 1212, column: 18, scope: !2353)
!2394 = !DILocation(line: 1212, column: 26, scope: !2353)
!2395 = !DILocation(line: 1213, column: 25, scope: !2353)
!2396 = !DILocation(line: 1213, column: 15, scope: !2353)
!2397 = !DILocation(line: 1213, column: 4, scope: !2353)
!2398 = !DILocation(line: 1213, column: 7, scope: !2353)
!2399 = !DILocation(line: 1213, column: 18, scope: !2353)
!2400 = !DILocation(line: 1213, column: 23, scope: !2353)
!2401 = !DILocation(line: 1214, column: 25, scope: !2353)
!2402 = !DILocation(line: 1214, column: 15, scope: !2353)
!2403 = !DILocation(line: 1214, column: 4, scope: !2353)
!2404 = !DILocation(line: 1214, column: 7, scope: !2353)
!2405 = !DILocation(line: 1214, column: 18, scope: !2353)
!2406 = !DILocation(line: 1214, column: 23, scope: !2353)
!2407 = !DILocation(line: 1215, column: 39, scope: !2353)
!2408 = !DILocation(line: 1215, column: 15, scope: !2353)
!2409 = !DILocation(line: 1215, column: 4, scope: !2353)
!2410 = !DILocation(line: 1215, column: 7, scope: !2353)
!2411 = !DILocation(line: 1215, column: 18, scope: !2353)
!2412 = !DILocation(line: 1215, column: 37, scope: !2353)
!2413 = !DILocation(line: 1216, column: 42, scope: !2353)
!2414 = !DILocation(line: 1216, column: 15, scope: !2353)
!2415 = !DILocation(line: 1216, column: 4, scope: !2353)
!2416 = !DILocation(line: 1216, column: 7, scope: !2353)
!2417 = !DILocation(line: 1216, column: 18, scope: !2353)
!2418 = !DILocation(line: 1216, column: 40, scope: !2353)
!2419 = !DILocation(line: 1217, column: 4, scope: !2353)
!2420 = !DILocation(line: 1219, column: 2, scope: !2337)
!2421 = !DILocation(line: 1202, column: 33, scope: !2422)
!2422 = !DILexicalBlockFile(scope: !2331, file: !1, discriminator: 2)
!2423 = !DILocation(line: 1202, column: 2, scope: !2422)
!2424 = !DILocation(line: 1221, column: 21, scope: !349)
!2425 = !DILocation(line: 1221, column: 24, scope: !349)
!2426 = !DILocation(line: 1221, column: 2, scope: !349)
!2427 = !DILocation(line: 1223, column: 2, scope: !349)
!2428 = !DILocation(line: 1224, column: 1, scope: !349)
!2429 = !DILocalVariable(name: "a", arg: 1, scope: !352, file: !1, line: 1231, type: !4)
!2430 = !DILocation(line: 1231, column: 48, scope: !352)
!2431 = !DILocalVariable(name: "bidder", arg: 2, scope: !352, file: !1, line: 1232, type: !355)
!2432 = !DILocation(line: 1232, column: 41, scope: !352)
!2433 = !DILocalVariable(name: "i", scope: !352, file: !1, line: 1234, type: !23)
!2434 = !DILocation(line: 1234, column: 6, scope: !352)
!2435 = !DILocalVariable(name: "number_slots", scope: !352, file: !1, line: 1234, type: !23)
!2436 = !DILocation(line: 1234, column: 9, scope: !352)
!2437 = !DILocation(line: 1236, column: 15, scope: !352)
!2438 = !DILocation(line: 1238, column: 9, scope: !2439)
!2439 = distinct !DILexicalBlock(scope: !352, file: !1, line: 1238, column: 2)
!2440 = !DILocation(line: 1238, column: 7, scope: !2439)
!2441 = !DILocation(line: 1238, column: 14, scope: !2442)
!2442 = !DILexicalBlockFile(scope: !2443, file: !1, discriminator: 1)
!2443 = distinct !DILexicalBlock(scope: !2439, file: !1, line: 1238, column: 2)
!2444 = !DILocation(line: 1238, column: 18, scope: !2442)
!2445 = !DILocation(line: 1238, column: 16, scope: !2442)
!2446 = !DILocation(line: 1238, column: 2, scope: !2442)
!2447 = !DILocation(line: 1239, column: 18, scope: !2448)
!2448 = distinct !DILexicalBlock(scope: !2449, file: !1, line: 1239, column: 7)
!2449 = distinct !DILexicalBlock(scope: !2443, file: !1, line: 1238, column: 37)
!2450 = !DILocation(line: 1239, column: 7, scope: !2448)
!2451 = !DILocation(line: 1239, column: 10, scope: !2448)
!2452 = !DILocation(line: 1239, column: 21, scope: !2448)
!2453 = !DILocation(line: 1239, column: 25, scope: !2448)
!2454 = !DILocation(line: 1239, column: 7, scope: !2449)
!2455 = !DILocation(line: 1240, column: 11, scope: !2456)
!2456 = distinct !DILexicalBlock(scope: !2448, file: !1, line: 1239, column: 34)
!2457 = !DILocation(line: 1240, column: 14, scope: !2456)
!2458 = !DILocation(line: 1240, column: 24, scope: !2456)
!2459 = !DILocation(line: 1240, column: 22, scope: !2456)
!2460 = !DILocation(line: 1240, column: 4, scope: !2456)
!2461 = !DILocation(line: 1241, column: 15, scope: !2456)
!2462 = !DILocation(line: 1241, column: 18, scope: !2456)
!2463 = !DILocation(line: 1241, column: 28, scope: !2456)
!2464 = !DILocation(line: 1241, column: 26, scope: !2456)
!2465 = !DILocation(line: 1241, column: 5, scope: !2456)
!2466 = !DILocation(line: 1241, column: 12, scope: !2456)
!2467 = !DILocation(line: 1242, column: 4, scope: !2456)
!2468 = !DILocation(line: 1244, column: 2, scope: !2449)
!2469 = !DILocation(line: 1238, column: 33, scope: !2470)
!2470 = !DILexicalBlockFile(scope: !2443, file: !1, discriminator: 2)
!2471 = !DILocation(line: 1238, column: 2, scope: !2470)
!2472 = !DILocation(line: 1246, column: 21, scope: !352)
!2473 = !DILocation(line: 1246, column: 24, scope: !352)
!2474 = !DILocation(line: 1246, column: 2, scope: !352)
!2475 = !DILocation(line: 1248, column: 2, scope: !352)
!2476 = !DILocation(line: 1249, column: 1, scope: !352)
!2477 = !DILocalVariable(name: "a", arg: 1, scope: !356, file: !1, line: 1303, type: !4)
!2478 = !DILocation(line: 1303, column: 43, scope: !356)
!2479 = !DILocalVariable(name: "min", arg: 2, scope: !356, file: !1, line: 1303, type: !45)
!2480 = !DILocation(line: 1303, column: 53, scope: !356)
!2481 = !DILocalVariable(name: "avail", arg: 3, scope: !356, file: !1, line: 1303, type: !359)
!2482 = !DILocation(line: 1303, column: 67, scope: !356)
!2483 = !DILocation(line: 1305, column: 38, scope: !356)
!2484 = !DILocation(line: 1305, column: 41, scope: !356)
!2485 = !DILocation(line: 1305, column: 49, scope: !356)
!2486 = !DILocation(line: 1305, column: 54, scope: !356)
!2487 = !DILocation(line: 1305, column: 10, scope: !356)
!2488 = !DILocation(line: 1305, column: 2, scope: !356)
!2489 = !DILocalVariable(name: "filter", arg: 1, scope: !360, file: !1, line: 1309, type: !169)
!2490 = !DILocation(line: 1309, column: 57, scope: !360)
!2491 = !DILocalVariable(name: "min", arg: 2, scope: !360, file: !1, line: 1310, type: !45)
!2492 = !DILocation(line: 1310, column: 12, scope: !360)
!2493 = !DILocalVariable(name: "avail", arg: 3, scope: !360, file: !1, line: 1310, type: !359)
!2494 = !DILocation(line: 1310, column: 26, scope: !360)
!2495 = !DILocalVariable(name: "bytes_read", scope: !360, file: !1, line: 1312, type: !38)
!2496 = !DILocation(line: 1312, column: 10, scope: !360)
!2497 = !DILocalVariable(name: "tocopy", scope: !360, file: !1, line: 1313, type: !45)
!2498 = !DILocation(line: 1313, column: 9, scope: !360)
!2499 = !DILocation(line: 1315, column: 6, scope: !2500)
!2500 = distinct !DILexicalBlock(scope: !360, file: !1, line: 1315, column: 6)
!2501 = !DILocation(line: 1315, column: 14, scope: !2500)
!2502 = !DILocation(line: 1315, column: 6, scope: !360)
!2503 = !DILocation(line: 1316, column: 7, scope: !2504)
!2504 = distinct !DILexicalBlock(scope: !2505, file: !1, line: 1316, column: 7)
!2505 = distinct !DILexicalBlock(scope: !2500, file: !1, line: 1315, column: 21)
!2506 = !DILocation(line: 1316, column: 7, scope: !2505)
!2507 = !DILocation(line: 1317, column: 5, scope: !2504)
!2508 = !DILocation(line: 1317, column: 11, scope: !2504)
!2509 = !DILocation(line: 1317, column: 4, scope: !2504)
!2510 = !DILocation(line: 1318, column: 3, scope: !2505)
!2511 = !DILocation(line: 1324, column: 2, scope: !360)
!2512 = !DILocation(line: 1332, column: 7, scope: !2513)
!2513 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 1332, column: 7)
!2514 = distinct !DILexicalBlock(scope: !2515, file: !1, line: 1324, column: 11)
!2515 = distinct !DILexicalBlock(scope: !2516, file: !1, line: 1324, column: 2)
!2516 = distinct !DILexicalBlock(scope: !360, file: !1, line: 1324, column: 2)
!2517 = !DILocation(line: 1332, column: 15, scope: !2513)
!2518 = !DILocation(line: 1332, column: 24, scope: !2513)
!2519 = !DILocation(line: 1332, column: 21, scope: !2513)
!2520 = !DILocation(line: 1332, column: 28, scope: !2513)
!2521 = !DILocation(line: 1332, column: 31, scope: !2522)
!2522 = !DILexicalBlockFile(scope: !2513, file: !1, discriminator: 1)
!2523 = !DILocation(line: 1332, column: 39, scope: !2522)
!2524 = !DILocation(line: 1332, column: 45, scope: !2522)
!2525 = !DILocation(line: 1332, column: 7, scope: !2522)
!2526 = !DILocation(line: 1333, column: 8, scope: !2527)
!2527 = distinct !DILexicalBlock(scope: !2528, file: !1, line: 1333, column: 8)
!2528 = distinct !DILexicalBlock(scope: !2513, file: !1, line: 1332, column: 50)
!2529 = !DILocation(line: 1333, column: 14, scope: !2527)
!2530 = !DILocation(line: 1333, column: 8, scope: !2528)
!2531 = !DILocation(line: 1334, column: 14, scope: !2527)
!2532 = !DILocation(line: 1334, column: 22, scope: !2527)
!2533 = !DILocation(line: 1334, column: 6, scope: !2527)
!2534 = !DILocation(line: 1334, column: 12, scope: !2527)
!2535 = !DILocation(line: 1334, column: 5, scope: !2527)
!2536 = !DILocation(line: 1335, column: 12, scope: !2528)
!2537 = !DILocation(line: 1335, column: 20, scope: !2528)
!2538 = !DILocation(line: 1335, column: 4, scope: !2528)
!2539 = !DILocation(line: 1342, column: 7, scope: !2540)
!2540 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 1342, column: 7)
!2541 = !DILocation(line: 1342, column: 15, scope: !2540)
!2542 = !DILocation(line: 1342, column: 31, scope: !2540)
!2543 = !DILocation(line: 1342, column: 39, scope: !2540)
!2544 = !DILocation(line: 1342, column: 54, scope: !2540)
!2545 = !DILocation(line: 1342, column: 62, scope: !2540)
!2546 = !DILocation(line: 1342, column: 52, scope: !2540)
!2547 = !DILocation(line: 1342, column: 28, scope: !2540)
!2548 = !DILocation(line: 1343, column: 7, scope: !2540)
!2549 = !DILocation(line: 1343, column: 10, scope: !2550)
!2550 = !DILexicalBlockFile(scope: !2540, file: !1, discriminator: 1)
!2551 = !DILocation(line: 1343, column: 18, scope: !2550)
!2552 = !DILocation(line: 1343, column: 33, scope: !2550)
!2553 = !DILocation(line: 1343, column: 41, scope: !2550)
!2554 = !DILocation(line: 1343, column: 31, scope: !2550)
!2555 = !DILocation(line: 1343, column: 50, scope: !2550)
!2556 = !DILocation(line: 1343, column: 47, scope: !2550)
!2557 = !DILocation(line: 1342, column: 7, scope: !2558)
!2558 = !DILexicalBlockFile(scope: !2514, file: !1, discriminator: 1)
!2559 = !DILocation(line: 1345, column: 28, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !2540, file: !1, line: 1343, column: 55)
!2561 = !DILocation(line: 1345, column: 36, scope: !2560)
!2562 = !DILocation(line: 1345, column: 4, scope: !2560)
!2563 = !DILocation(line: 1345, column: 12, scope: !2560)
!2564 = !DILocation(line: 1345, column: 25, scope: !2560)
!2565 = !DILocation(line: 1346, column: 27, scope: !2560)
!2566 = !DILocation(line: 1346, column: 35, scope: !2560)
!2567 = !DILocation(line: 1346, column: 4, scope: !2560)
!2568 = !DILocation(line: 1346, column: 12, scope: !2560)
!2569 = !DILocation(line: 1346, column: 24, scope: !2560)
!2570 = !DILocation(line: 1348, column: 4, scope: !2560)
!2571 = !DILocation(line: 1348, column: 12, scope: !2560)
!2572 = !DILocation(line: 1348, column: 18, scope: !2560)
!2573 = !DILocation(line: 1349, column: 19, scope: !2560)
!2574 = !DILocation(line: 1349, column: 27, scope: !2560)
!2575 = !DILocation(line: 1349, column: 4, scope: !2560)
!2576 = !DILocation(line: 1349, column: 12, scope: !2560)
!2577 = !DILocation(line: 1349, column: 17, scope: !2560)
!2578 = !DILocation(line: 1351, column: 8, scope: !2579)
!2579 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 1351, column: 8)
!2580 = !DILocation(line: 1351, column: 14, scope: !2579)
!2581 = !DILocation(line: 1351, column: 8, scope: !2560)
!2582 = !DILocation(line: 1352, column: 14, scope: !2579)
!2583 = !DILocation(line: 1352, column: 22, scope: !2579)
!2584 = !DILocation(line: 1352, column: 6, scope: !2579)
!2585 = !DILocation(line: 1352, column: 12, scope: !2579)
!2586 = !DILocation(line: 1352, column: 5, scope: !2579)
!2587 = !DILocation(line: 1353, column: 12, scope: !2560)
!2588 = !DILocation(line: 1353, column: 20, scope: !2560)
!2589 = !DILocation(line: 1353, column: 4, scope: !2560)
!2590 = !DILocation(line: 1357, column: 7, scope: !2591)
!2591 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 1357, column: 7)
!2592 = !DILocation(line: 1357, column: 15, scope: !2591)
!2593 = !DILocation(line: 1357, column: 22, scope: !2591)
!2594 = !DILocation(line: 1357, column: 30, scope: !2591)
!2595 = !DILocation(line: 1357, column: 20, scope: !2591)
!2596 = !DILocation(line: 1357, column: 37, scope: !2591)
!2597 = !DILocation(line: 1358, column: 7, scope: !2591)
!2598 = !DILocation(line: 1358, column: 15, scope: !2591)
!2599 = !DILocation(line: 1358, column: 22, scope: !2591)
!2600 = !DILocation(line: 1358, column: 20, scope: !2591)
!2601 = !DILocation(line: 1358, column: 28, scope: !2591)
!2602 = !DILocation(line: 1358, column: 36, scope: !2591)
!2603 = !DILocation(line: 1358, column: 45, scope: !2591)
!2604 = !DILocation(line: 1358, column: 53, scope: !2591)
!2605 = !DILocation(line: 1358, column: 43, scope: !2591)
!2606 = !DILocation(line: 1358, column: 26, scope: !2591)
!2607 = !DILocation(line: 1357, column: 7, scope: !2558)
!2608 = !DILocation(line: 1359, column: 8, scope: !2609)
!2609 = distinct !DILexicalBlock(scope: !2610, file: !1, line: 1359, column: 8)
!2610 = distinct !DILexicalBlock(scope: !2591, file: !1, line: 1358, column: 66)
!2611 = !DILocation(line: 1359, column: 16, scope: !2609)
!2612 = !DILocation(line: 1359, column: 22, scope: !2609)
!2613 = !DILocation(line: 1359, column: 8, scope: !2610)
!2614 = !DILocation(line: 1360, column: 13, scope: !2609)
!2615 = !DILocation(line: 1360, column: 21, scope: !2609)
!2616 = !DILocation(line: 1360, column: 29, scope: !2609)
!2617 = !DILocation(line: 1360, column: 37, scope: !2609)
!2618 = !DILocation(line: 1361, column: 9, scope: !2609)
!2619 = !DILocation(line: 1361, column: 17, scope: !2609)
!2620 = !DILocation(line: 1360, column: 5, scope: !2609)
!2621 = !DILocation(line: 1362, column: 19, scope: !2610)
!2622 = !DILocation(line: 1362, column: 27, scope: !2610)
!2623 = !DILocation(line: 1362, column: 4, scope: !2610)
!2624 = !DILocation(line: 1362, column: 12, scope: !2610)
!2625 = !DILocation(line: 1362, column: 17, scope: !2610)
!2626 = !DILocation(line: 1363, column: 3, scope: !2610)
!2627 = !DILocation(line: 1366, column: 7, scope: !2628)
!2628 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 1366, column: 7)
!2629 = !DILocation(line: 1366, column: 15, scope: !2628)
!2630 = !DILocation(line: 1366, column: 28, scope: !2628)
!2631 = !DILocation(line: 1366, column: 7, scope: !2514)
!2632 = !DILocation(line: 1367, column: 8, scope: !2633)
!2633 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 1367, column: 8)
!2634 = distinct !DILexicalBlock(scope: !2628, file: !1, line: 1366, column: 34)
!2635 = !DILocation(line: 1367, column: 16, scope: !2633)
!2636 = !DILocation(line: 1367, column: 8, scope: !2634)
!2637 = !DILocation(line: 1368, column: 9, scope: !2638)
!2638 = distinct !DILexicalBlock(scope: !2639, file: !1, line: 1368, column: 9)
!2639 = distinct !DILexicalBlock(scope: !2633, file: !1, line: 1367, column: 29)
!2640 = !DILocation(line: 1368, column: 15, scope: !2638)
!2641 = !DILocation(line: 1368, column: 9, scope: !2639)
!2642 = !DILocation(line: 1369, column: 7, scope: !2638)
!2643 = !DILocation(line: 1369, column: 13, scope: !2638)
!2644 = !DILocation(line: 1369, column: 6, scope: !2638)
!2645 = !DILocation(line: 1370, column: 5, scope: !2639)
!2646 = !DILocation(line: 1372, column: 18, scope: !2634)
!2647 = !DILocation(line: 1372, column: 26, scope: !2634)
!2648 = !DILocation(line: 1372, column: 32, scope: !2634)
!2649 = !DILocation(line: 1373, column: 9, scope: !2634)
!2650 = !DILocation(line: 1373, column: 17, scope: !2634)
!2651 = !DILocation(line: 1372, column: 17, scope: !2634)
!2652 = !DILocation(line: 1372, column: 15, scope: !2634)
!2653 = !DILocation(line: 1374, column: 8, scope: !2654)
!2654 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 1374, column: 8)
!2655 = !DILocation(line: 1374, column: 19, scope: !2654)
!2656 = !DILocation(line: 1374, column: 8, scope: !2634)
!2657 = !DILocation(line: 1375, column: 28, scope: !2658)
!2658 = distinct !DILexicalBlock(scope: !2654, file: !1, line: 1374, column: 24)
!2659 = !DILocation(line: 1375, column: 36, scope: !2658)
!2660 = !DILocation(line: 1375, column: 49, scope: !2658)
!2661 = !DILocation(line: 1375, column: 5, scope: !2658)
!2662 = !DILocation(line: 1375, column: 13, scope: !2658)
!2663 = !DILocation(line: 1375, column: 26, scope: !2658)
!2664 = !DILocation(line: 1377, column: 9, scope: !2658)
!2665 = !DILocation(line: 1377, column: 17, scope: !2658)
!2666 = !DILocation(line: 1377, column: 29, scope: !2658)
!2667 = !DILocation(line: 1376, column: 5, scope: !2658)
!2668 = !DILocation(line: 1376, column: 13, scope: !2658)
!2669 = !DILocation(line: 1376, column: 25, scope: !2658)
!2670 = !DILocation(line: 1378, column: 5, scope: !2658)
!2671 = !DILocation(line: 1378, column: 13, scope: !2658)
!2672 = !DILocation(line: 1378, column: 19, scope: !2658)
!2673 = !DILocation(line: 1379, column: 9, scope: !2674)
!2674 = distinct !DILexicalBlock(scope: !2658, file: !1, line: 1379, column: 9)
!2675 = !DILocation(line: 1379, column: 15, scope: !2674)
!2676 = !DILocation(line: 1379, column: 9, scope: !2658)
!2677 = !DILocation(line: 1380, column: 7, scope: !2674)
!2678 = !DILocation(line: 1380, column: 13, scope: !2674)
!2679 = !DILocation(line: 1380, column: 6, scope: !2674)
!2680 = !DILocation(line: 1381, column: 5, scope: !2658)
!2681 = !DILocation(line: 1383, column: 8, scope: !2682)
!2682 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 1383, column: 8)
!2683 = !DILocation(line: 1383, column: 19, scope: !2682)
!2684 = !DILocation(line: 1383, column: 8, scope: !2634)
!2685 = !DILocation(line: 1385, column: 9, scope: !2686)
!2686 = distinct !DILexicalBlock(scope: !2687, file: !1, line: 1385, column: 9)
!2687 = distinct !DILexicalBlock(scope: !2682, file: !1, line: 1383, column: 25)
!2688 = !DILocation(line: 1385, column: 17, scope: !2686)
!2689 = !DILocation(line: 1385, column: 26, scope: !2686)
!2690 = !DILocation(line: 1385, column: 33, scope: !2686)
!2691 = !DILocation(line: 1386, column: 11, scope: !2686)
!2692 = !DILocation(line: 1386, column: 19, scope: !2686)
!2693 = !DILocation(line: 1386, column: 28, scope: !2686)
!2694 = !DILocation(line: 1386, column: 35, scope: !2686)
!2695 = !DILocation(line: 1386, column: 41, scope: !2686)
!2696 = !DILocation(line: 1385, column: 40, scope: !2686)
!2697 = !DILocation(line: 1385, column: 9, scope: !2687)
!2698 = !DILocation(line: 1387, column: 30, scope: !2699)
!2699 = distinct !DILexicalBlock(scope: !2700, file: !1, line: 1387, column: 10)
!2700 = distinct !DILexicalBlock(scope: !2686, file: !1, line: 1386, column: 46)
!2701 = !DILocation(line: 1388, column: 10, scope: !2699)
!2702 = !DILocation(line: 1388, column: 18, scope: !2699)
!2703 = !DILocation(line: 1388, column: 27, scope: !2699)
!2704 = !DILocation(line: 1388, column: 34, scope: !2699)
!2705 = !DILocation(line: 1388, column: 41, scope: !2699)
!2706 = !DILocation(line: 1387, column: 10, scope: !2699)
!2707 = !DILocation(line: 1389, column: 10, scope: !2699)
!2708 = !DILocation(line: 1387, column: 10, scope: !2700)
!2709 = !DILocation(line: 1390, column: 7, scope: !2699)
!2710 = !DILocation(line: 1391, column: 5, scope: !2700)
!2711 = !DILocation(line: 1393, column: 28, scope: !2687)
!2712 = !DILocation(line: 1393, column: 36, scope: !2687)
!2713 = !DILocation(line: 1393, column: 49, scope: !2687)
!2714 = !DILocation(line: 1393, column: 5, scope: !2687)
!2715 = !DILocation(line: 1393, column: 13, scope: !2687)
!2716 = !DILocation(line: 1393, column: 26, scope: !2687)
!2717 = !DILocation(line: 1395, column: 9, scope: !2687)
!2718 = !DILocation(line: 1395, column: 17, scope: !2687)
!2719 = !DILocation(line: 1395, column: 29, scope: !2687)
!2720 = !DILocation(line: 1394, column: 5, scope: !2687)
!2721 = !DILocation(line: 1394, column: 13, scope: !2687)
!2722 = !DILocation(line: 1394, column: 25, scope: !2687)
!2723 = !DILocation(line: 1396, column: 5, scope: !2687)
!2724 = !DILocation(line: 1396, column: 13, scope: !2687)
!2725 = !DILocation(line: 1396, column: 25, scope: !2687)
!2726 = !DILocation(line: 1398, column: 9, scope: !2727)
!2727 = distinct !DILexicalBlock(scope: !2687, file: !1, line: 1398, column: 9)
!2728 = !DILocation(line: 1398, column: 15, scope: !2727)
!2729 = !DILocation(line: 1398, column: 9, scope: !2687)
!2730 = !DILocation(line: 1399, column: 15, scope: !2727)
!2731 = !DILocation(line: 1399, column: 23, scope: !2727)
!2732 = !DILocation(line: 1399, column: 7, scope: !2727)
!2733 = !DILocation(line: 1399, column: 13, scope: !2727)
!2734 = !DILocation(line: 1399, column: 6, scope: !2727)
!2735 = !DILocation(line: 1400, column: 5, scope: !2687)
!2736 = !DILocation(line: 1402, column: 27, scope: !2634)
!2737 = !DILocation(line: 1402, column: 4, scope: !2634)
!2738 = !DILocation(line: 1402, column: 12, scope: !2634)
!2739 = !DILocation(line: 1402, column: 25, scope: !2634)
!2740 = !DILocation(line: 1403, column: 27, scope: !2634)
!2741 = !DILocation(line: 1403, column: 35, scope: !2634)
!2742 = !DILocation(line: 1403, column: 4, scope: !2634)
!2743 = !DILocation(line: 1403, column: 12, scope: !2634)
!2744 = !DILocation(line: 1403, column: 25, scope: !2634)
!2745 = !DILocation(line: 1404, column: 26, scope: !2634)
!2746 = !DILocation(line: 1404, column: 34, scope: !2634)
!2747 = !DILocation(line: 1404, column: 4, scope: !2634)
!2748 = !DILocation(line: 1404, column: 12, scope: !2634)
!2749 = !DILocation(line: 1404, column: 24, scope: !2634)
!2750 = !DILocation(line: 1405, column: 3, scope: !2634)
!2751 = !DILocation(line: 1414, column: 8, scope: !2752)
!2752 = distinct !DILexicalBlock(scope: !2753, file: !1, line: 1414, column: 8)
!2753 = distinct !DILexicalBlock(scope: !2628, file: !1, line: 1405, column: 10)
!2754 = !DILocation(line: 1414, column: 14, scope: !2752)
!2755 = !DILocation(line: 1414, column: 22, scope: !2752)
!2756 = !DILocation(line: 1414, column: 12, scope: !2752)
!2757 = !DILocation(line: 1414, column: 8, scope: !2753)
!2758 = !DILocalVariable(name: "s", scope: !2759, file: !1, line: 1415, type: !45)
!2759 = distinct !DILexicalBlock(scope: !2752, file: !1, line: 1414, column: 35)
!2760 = !DILocation(line: 1415, column: 12, scope: !2759)
!2761 = !DILocalVariable(name: "t", scope: !2759, file: !1, line: 1415, type: !45)
!2762 = !DILocation(line: 1415, column: 15, scope: !2759)
!2763 = !DILocalVariable(name: "p", scope: !2759, file: !1, line: 1416, type: !95)
!2764 = !DILocation(line: 1416, column: 11, scope: !2759)
!2765 = !DILocation(line: 1419, column: 13, scope: !2759)
!2766 = !DILocation(line: 1419, column: 21, scope: !2759)
!2767 = !DILocation(line: 1419, column: 11, scope: !2759)
!2768 = !DILocation(line: 1419, column: 7, scope: !2759)
!2769 = !DILocation(line: 1420, column: 9, scope: !2770)
!2770 = distinct !DILexicalBlock(scope: !2759, file: !1, line: 1420, column: 9)
!2771 = !DILocation(line: 1420, column: 11, scope: !2770)
!2772 = !DILocation(line: 1420, column: 9, scope: !2759)
!2773 = !DILocation(line: 1421, column: 10, scope: !2770)
!2774 = !DILocation(line: 1421, column: 8, scope: !2770)
!2775 = !DILocation(line: 1421, column: 6, scope: !2770)
!2776 = !DILocation(line: 1422, column: 5, scope: !2759)
!2777 = !DILocation(line: 1422, column: 12, scope: !2778)
!2778 = !DILexicalBlockFile(scope: !2759, file: !1, discriminator: 1)
!2779 = !DILocation(line: 1422, column: 16, scope: !2778)
!2780 = !DILocation(line: 1422, column: 14, scope: !2778)
!2781 = !DILocation(line: 1422, column: 5, scope: !2778)
!2782 = !DILocation(line: 1423, column: 8, scope: !2783)
!2783 = distinct !DILexicalBlock(scope: !2759, file: !1, line: 1422, column: 21)
!2784 = !DILocation(line: 1424, column: 10, scope: !2785)
!2785 = distinct !DILexicalBlock(scope: !2783, file: !1, line: 1424, column: 10)
!2786 = !DILocation(line: 1424, column: 15, scope: !2785)
!2787 = !DILocation(line: 1424, column: 12, scope: !2785)
!2788 = !DILocation(line: 1424, column: 10, scope: !2783)
!2789 = !DILocation(line: 1426, column: 12, scope: !2790)
!2790 = distinct !DILexicalBlock(scope: !2785, file: !1, line: 1424, column: 18)
!2791 = !DILocation(line: 1426, column: 20, scope: !2790)
!2792 = !DILocation(line: 1426, column: 29, scope: !2790)
!2793 = !DILocation(line: 1425, column: 7, scope: !2790)
!2794 = !DILocation(line: 1430, column: 7, scope: !2790)
!2795 = !DILocation(line: 1430, column: 15, scope: !2790)
!2796 = !DILocation(line: 1430, column: 21, scope: !2790)
!2797 = !DILocation(line: 1431, column: 11, scope: !2798)
!2798 = distinct !DILexicalBlock(scope: !2790, file: !1, line: 1431, column: 11)
!2799 = !DILocation(line: 1431, column: 17, scope: !2798)
!2800 = !DILocation(line: 1431, column: 11, scope: !2790)
!2801 = !DILocation(line: 1432, column: 9, scope: !2798)
!2802 = !DILocation(line: 1432, column: 15, scope: !2798)
!2803 = !DILocation(line: 1432, column: 8, scope: !2798)
!2804 = !DILocation(line: 1433, column: 7, scope: !2790)
!2805 = !DILocation(line: 1435, column: 10, scope: !2783)
!2806 = !DILocation(line: 1435, column: 8, scope: !2783)
!2807 = !DILocation(line: 1422, column: 5, scope: !2808)
!2808 = !DILexicalBlockFile(scope: !2759, file: !1, discriminator: 2)
!2809 = !DILocation(line: 1438, column: 24, scope: !2759)
!2810 = !DILocation(line: 1438, column: 17, scope: !2759)
!2811 = !DILocation(line: 1438, column: 7, scope: !2759)
!2812 = !DILocation(line: 1439, column: 9, scope: !2813)
!2813 = distinct !DILexicalBlock(scope: !2759, file: !1, line: 1439, column: 9)
!2814 = !DILocation(line: 1439, column: 11, scope: !2813)
!2815 = !DILocation(line: 1439, column: 9, scope: !2759)
!2816 = !DILocation(line: 1441, column: 8, scope: !2817)
!2817 = distinct !DILexicalBlock(scope: !2813, file: !1, line: 1439, column: 20)
!2818 = !DILocation(line: 1441, column: 16, scope: !2817)
!2819 = !DILocation(line: 1441, column: 25, scope: !2817)
!2820 = !DILocation(line: 1440, column: 6, scope: !2817)
!2821 = !DILocation(line: 1444, column: 6, scope: !2817)
!2822 = !DILocation(line: 1444, column: 14, scope: !2817)
!2823 = !DILocation(line: 1444, column: 20, scope: !2817)
!2824 = !DILocation(line: 1445, column: 10, scope: !2825)
!2825 = distinct !DILexicalBlock(scope: !2817, file: !1, line: 1445, column: 10)
!2826 = !DILocation(line: 1445, column: 16, scope: !2825)
!2827 = !DILocation(line: 1445, column: 10, scope: !2817)
!2828 = !DILocation(line: 1446, column: 8, scope: !2825)
!2829 = !DILocation(line: 1446, column: 14, scope: !2825)
!2830 = !DILocation(line: 1446, column: 7, scope: !2825)
!2831 = !DILocation(line: 1447, column: 6, scope: !2817)
!2832 = !DILocation(line: 1450, column: 9, scope: !2833)
!2833 = distinct !DILexicalBlock(scope: !2759, file: !1, line: 1450, column: 9)
!2834 = !DILocation(line: 1450, column: 17, scope: !2833)
!2835 = !DILocation(line: 1450, column: 23, scope: !2833)
!2836 = !DILocation(line: 1450, column: 9, scope: !2759)
!2837 = !DILocation(line: 1451, column: 14, scope: !2833)
!2838 = !DILocation(line: 1451, column: 17, scope: !2833)
!2839 = !DILocation(line: 1451, column: 25, scope: !2833)
!2840 = !DILocation(line: 1451, column: 31, scope: !2833)
!2841 = !DILocation(line: 1451, column: 39, scope: !2833)
!2842 = !DILocation(line: 1451, column: 6, scope: !2833)
!2843 = !DILocation(line: 1452, column: 10, scope: !2759)
!2844 = !DILocation(line: 1452, column: 18, scope: !2759)
!2845 = !DILocation(line: 1452, column: 5, scope: !2759)
!2846 = !DILocation(line: 1453, column: 37, scope: !2759)
!2847 = !DILocation(line: 1453, column: 20, scope: !2759)
!2848 = !DILocation(line: 1453, column: 28, scope: !2759)
!2849 = !DILocation(line: 1453, column: 35, scope: !2759)
!2850 = !DILocation(line: 1453, column: 5, scope: !2759)
!2851 = !DILocation(line: 1453, column: 13, scope: !2759)
!2852 = !DILocation(line: 1453, column: 18, scope: !2759)
!2853 = !DILocation(line: 1454, column: 27, scope: !2759)
!2854 = !DILocation(line: 1454, column: 5, scope: !2759)
!2855 = !DILocation(line: 1454, column: 13, scope: !2759)
!2856 = !DILocation(line: 1454, column: 25, scope: !2759)
!2857 = !DILocation(line: 1455, column: 4, scope: !2759)
!2858 = !DILocation(line: 1459, column: 14, scope: !2753)
!2859 = !DILocation(line: 1459, column: 22, scope: !2753)
!2860 = !DILocation(line: 1459, column: 31, scope: !2753)
!2861 = !DILocation(line: 1459, column: 39, scope: !2753)
!2862 = !DILocation(line: 1459, column: 29, scope: !2753)
!2863 = !DILocation(line: 1460, column: 11, scope: !2753)
!2864 = !DILocation(line: 1460, column: 19, scope: !2753)
!2865 = !DILocation(line: 1460, column: 26, scope: !2753)
!2866 = !DILocation(line: 1460, column: 34, scope: !2753)
!2867 = !DILocation(line: 1460, column: 24, scope: !2753)
!2868 = !DILocation(line: 1460, column: 8, scope: !2753)
!2869 = !DILocation(line: 1459, column: 11, scope: !2753)
!2870 = !DILocation(line: 1462, column: 8, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2753, file: !1, line: 1462, column: 8)
!2872 = !DILocation(line: 1462, column: 17, scope: !2871)
!2873 = !DILocation(line: 1462, column: 25, scope: !2871)
!2874 = !DILocation(line: 1462, column: 15, scope: !2871)
!2875 = !DILocation(line: 1462, column: 33, scope: !2871)
!2876 = !DILocation(line: 1462, column: 31, scope: !2871)
!2877 = !DILocation(line: 1462, column: 8, scope: !2753)
!2878 = !DILocation(line: 1463, column: 14, scope: !2871)
!2879 = !DILocation(line: 1463, column: 20, scope: !2871)
!2880 = !DILocation(line: 1463, column: 28, scope: !2871)
!2881 = !DILocation(line: 1463, column: 18, scope: !2871)
!2882 = !DILocation(line: 1463, column: 12, scope: !2871)
!2883 = !DILocation(line: 1463, column: 5, scope: !2871)
!2884 = !DILocation(line: 1465, column: 8, scope: !2885)
!2885 = distinct !DILexicalBlock(scope: !2753, file: !1, line: 1465, column: 8)
!2886 = !DILocation(line: 1465, column: 17, scope: !2885)
!2887 = !DILocation(line: 1465, column: 25, scope: !2885)
!2888 = !DILocation(line: 1465, column: 15, scope: !2885)
!2889 = !DILocation(line: 1465, column: 8, scope: !2753)
!2890 = !DILocation(line: 1466, column: 14, scope: !2885)
!2891 = !DILocation(line: 1466, column: 22, scope: !2885)
!2892 = !DILocation(line: 1466, column: 12, scope: !2885)
!2893 = !DILocation(line: 1466, column: 5, scope: !2885)
!2894 = !DILocation(line: 1468, column: 11, scope: !2753)
!2895 = !DILocation(line: 1468, column: 19, scope: !2753)
!2896 = !DILocation(line: 1468, column: 26, scope: !2753)
!2897 = !DILocation(line: 1468, column: 34, scope: !2753)
!2898 = !DILocation(line: 1468, column: 24, scope: !2753)
!2899 = !DILocation(line: 1469, column: 8, scope: !2753)
!2900 = !DILocation(line: 1469, column: 16, scope: !2753)
!2901 = !DILocation(line: 1469, column: 29, scope: !2753)
!2902 = !DILocation(line: 1468, column: 4, scope: !2753)
!2903 = !DILocation(line: 1471, column: 27, scope: !2753)
!2904 = !DILocation(line: 1471, column: 4, scope: !2753)
!2905 = !DILocation(line: 1471, column: 12, scope: !2753)
!2906 = !DILocation(line: 1471, column: 24, scope: !2753)
!2907 = !DILocation(line: 1472, column: 28, scope: !2753)
!2908 = !DILocation(line: 1472, column: 4, scope: !2753)
!2909 = !DILocation(line: 1472, column: 12, scope: !2753)
!2910 = !DILocation(line: 1472, column: 25, scope: !2753)
!2911 = !DILocation(line: 1474, column: 21, scope: !2753)
!2912 = !DILocation(line: 1474, column: 4, scope: !2753)
!2913 = !DILocation(line: 1474, column: 12, scope: !2753)
!2914 = !DILocation(line: 1474, column: 18, scope: !2753)
!2915 = !DILocation(line: 1324, column: 2, scope: !2916)
!2916 = !DILexicalBlockFile(scope: !2515, file: !1, discriminator: 1)
!2917 = !DILocation(line: 1477, column: 1, scope: !360)
!2918 = !DILocalVariable(name: "a", arg: 1, scope: !363, file: !1, line: 1483, type: !4)
!2919 = !DILocation(line: 1483, column: 45, scope: !363)
!2920 = !DILocalVariable(name: "request", arg: 2, scope: !363, file: !1, line: 1483, type: !52)
!2921 = !DILocation(line: 1483, column: 56, scope: !363)
!2922 = !DILocation(line: 1485, column: 40, scope: !363)
!2923 = !DILocation(line: 1485, column: 43, scope: !363)
!2924 = !DILocation(line: 1485, column: 51, scope: !363)
!2925 = !DILocation(line: 1485, column: 10, scope: !363)
!2926 = !DILocation(line: 1485, column: 2, scope: !363)
!2927 = !DILocalVariable(name: "filter", arg: 1, scope: !366, file: !1, line: 1489, type: !169)
!2928 = !DILocation(line: 1489, column: 60, scope: !366)
!2929 = !DILocalVariable(name: "request", arg: 2, scope: !366, file: !1, line: 1490, type: !52)
!2930 = !DILocation(line: 1490, column: 13, scope: !366)
!2931 = !DILocalVariable(name: "skipped", scope: !366, file: !1, line: 1492, type: !52)
!2932 = !DILocation(line: 1492, column: 10, scope: !366)
!2933 = !DILocation(line: 1494, column: 6, scope: !2934)
!2934 = distinct !DILexicalBlock(scope: !366, file: !1, line: 1494, column: 6)
!2935 = !DILocation(line: 1494, column: 14, scope: !2934)
!2936 = !DILocation(line: 1494, column: 6, scope: !366)
!2937 = !DILocation(line: 1495, column: 3, scope: !2934)
!2938 = !DILocation(line: 1496, column: 6, scope: !2939)
!2939 = distinct !DILexicalBlock(scope: !366, file: !1, line: 1496, column: 6)
!2940 = !DILocation(line: 1496, column: 14, scope: !2939)
!2941 = !DILocation(line: 1496, column: 6, scope: !366)
!2942 = !DILocation(line: 1497, column: 3, scope: !2939)
!2943 = !DILocation(line: 1499, column: 33, scope: !366)
!2944 = !DILocation(line: 1499, column: 41, scope: !366)
!2945 = !DILocation(line: 1499, column: 12, scope: !366)
!2946 = !DILocation(line: 1499, column: 10, scope: !366)
!2947 = !DILocation(line: 1500, column: 6, scope: !2948)
!2948 = distinct !DILexicalBlock(scope: !366, file: !1, line: 1500, column: 6)
!2949 = !DILocation(line: 1500, column: 17, scope: !2948)
!2950 = !DILocation(line: 1500, column: 14, scope: !2948)
!2951 = !DILocation(line: 1500, column: 6, scope: !366)
!2952 = !DILocation(line: 1501, column: 11, scope: !2948)
!2953 = !DILocation(line: 1501, column: 3, scope: !2948)
!2954 = !DILocation(line: 1503, column: 6, scope: !2955)
!2955 = distinct !DILexicalBlock(scope: !366, file: !1, line: 1503, column: 6)
!2956 = !DILocation(line: 1503, column: 14, scope: !2955)
!2957 = !DILocation(line: 1503, column: 6, scope: !366)
!2958 = !DILocation(line: 1504, column: 11, scope: !2955)
!2959 = !DILocation(line: 1504, column: 3, scope: !2955)
!2960 = !DILocation(line: 1505, column: 21, scope: !366)
!2961 = !DILocation(line: 1505, column: 29, scope: !366)
!2962 = !DILocation(line: 1505, column: 38, scope: !366)
!2963 = !DILocation(line: 1508, column: 16, scope: !366)
!2964 = !DILocation(line: 1508, column: 35, scope: !366)
!2965 = !DILocation(line: 1505, column: 2, scope: !366)
!2966 = !DILocation(line: 1509, column: 2, scope: !366)
!2967 = !DILocation(line: 1510, column: 1, scope: !366)
!2968 = !DILocalVariable(name: "filter", arg: 1, scope: !393, file: !1, line: 1519, type: !169)
!2969 = !DILocation(line: 1519, column: 50, scope: !393)
!2970 = !DILocalVariable(name: "request", arg: 2, scope: !393, file: !1, line: 1519, type: !52)
!2971 = !DILocation(line: 1519, column: 66, scope: !393)
!2972 = !DILocalVariable(name: "bytes_skipped", scope: !393, file: !1, line: 1521, type: !52)
!2973 = !DILocation(line: 1521, column: 10, scope: !393)
!2974 = !DILocalVariable(name: "total_bytes_skipped", scope: !393, file: !1, line: 1521, type: !52)
!2975 = !DILocation(line: 1521, column: 25, scope: !393)
!2976 = !DILocalVariable(name: "bytes_read", scope: !393, file: !1, line: 1522, type: !38)
!2977 = !DILocation(line: 1522, column: 10, scope: !393)
!2978 = !DILocalVariable(name: "min", scope: !393, file: !1, line: 1523, type: !45)
!2979 = !DILocation(line: 1523, column: 9, scope: !393)
!2980 = !DILocation(line: 1525, column: 6, scope: !2981)
!2981 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1525, column: 6)
!2982 = !DILocation(line: 1525, column: 14, scope: !2981)
!2983 = !DILocation(line: 1525, column: 6, scope: !393)
!2984 = !DILocation(line: 1526, column: 3, scope: !2981)
!2985 = !DILocation(line: 1529, column: 6, scope: !2986)
!2986 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1529, column: 6)
!2987 = !DILocation(line: 1529, column: 14, scope: !2986)
!2988 = !DILocation(line: 1529, column: 20, scope: !2986)
!2989 = !DILocation(line: 1529, column: 6, scope: !393)
!2990 = !DILocation(line: 1530, column: 17, scope: !2991)
!2991 = distinct !DILexicalBlock(scope: !2986, file: !1, line: 1529, column: 25)
!2992 = !DILocation(line: 1530, column: 17, scope: !2993)
!2993 = !DILexicalBlockFile(scope: !2991, file: !1, discriminator: 1)
!2994 = !DILocation(line: 1530, column: 17, scope: !2995)
!2995 = !DILexicalBlockFile(scope: !2991, file: !1, discriminator: 2)
!2996 = !DILocation(line: 1530, column: 17, scope: !2997)
!2997 = !DILexicalBlockFile(scope: !2991, file: !1, discriminator: 3)
!2998 = !DILocation(line: 1530, column: 7, scope: !2997)
!2999 = !DILocation(line: 1531, column: 19, scope: !2991)
!3000 = !DILocation(line: 1531, column: 3, scope: !2991)
!3001 = !DILocation(line: 1531, column: 11, scope: !2991)
!3002 = !DILocation(line: 1531, column: 16, scope: !2991)
!3003 = !DILocation(line: 1532, column: 20, scope: !2991)
!3004 = !DILocation(line: 1532, column: 3, scope: !2991)
!3005 = !DILocation(line: 1532, column: 11, scope: !2991)
!3006 = !DILocation(line: 1532, column: 17, scope: !2991)
!3007 = !DILocation(line: 1533, column: 14, scope: !2991)
!3008 = !DILocation(line: 1533, column: 11, scope: !2991)
!3009 = !DILocation(line: 1534, column: 23, scope: !2991)
!3010 = !DILocation(line: 1534, column: 3, scope: !2991)
!3011 = !DILocation(line: 1534, column: 11, scope: !2991)
!3012 = !DILocation(line: 1534, column: 20, scope: !2991)
!3013 = !DILocation(line: 1535, column: 26, scope: !2991)
!3014 = !DILocation(line: 1535, column: 23, scope: !2991)
!3015 = !DILocation(line: 1536, column: 2, scope: !2991)
!3016 = !DILocation(line: 1539, column: 6, scope: !3017)
!3017 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1539, column: 6)
!3018 = !DILocation(line: 1539, column: 14, scope: !3017)
!3019 = !DILocation(line: 1539, column: 27, scope: !3017)
!3020 = !DILocation(line: 1539, column: 6, scope: !393)
!3021 = !DILocation(line: 1540, column: 17, scope: !3022)
!3022 = distinct !DILexicalBlock(scope: !3017, file: !1, line: 1539, column: 32)
!3023 = !DILocation(line: 1540, column: 17, scope: !3024)
!3024 = !DILexicalBlockFile(scope: !3022, file: !1, discriminator: 1)
!3025 = !DILocation(line: 1540, column: 17, scope: !3026)
!3026 = !DILexicalBlockFile(scope: !3022, file: !1, discriminator: 2)
!3027 = !DILocation(line: 1540, column: 17, scope: !3028)
!3028 = !DILexicalBlockFile(scope: !3022, file: !1, discriminator: 3)
!3029 = !DILocation(line: 1540, column: 7, scope: !3028)
!3030 = !DILocation(line: 1541, column: 26, scope: !3022)
!3031 = !DILocation(line: 1541, column: 3, scope: !3022)
!3032 = !DILocation(line: 1541, column: 11, scope: !3022)
!3033 = !DILocation(line: 1541, column: 23, scope: !3022)
!3034 = !DILocation(line: 1542, column: 27, scope: !3022)
!3035 = !DILocation(line: 1542, column: 3, scope: !3022)
!3036 = !DILocation(line: 1542, column: 11, scope: !3022)
!3037 = !DILocation(line: 1542, column: 24, scope: !3022)
!3038 = !DILocation(line: 1543, column: 14, scope: !3022)
!3039 = !DILocation(line: 1543, column: 11, scope: !3022)
!3040 = !DILocation(line: 1544, column: 23, scope: !3022)
!3041 = !DILocation(line: 1544, column: 3, scope: !3022)
!3042 = !DILocation(line: 1544, column: 11, scope: !3022)
!3043 = !DILocation(line: 1544, column: 20, scope: !3022)
!3044 = !DILocation(line: 1545, column: 26, scope: !3022)
!3045 = !DILocation(line: 1545, column: 23, scope: !3022)
!3046 = !DILocation(line: 1546, column: 2, scope: !3022)
!3047 = !DILocation(line: 1547, column: 6, scope: !3048)
!3048 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1547, column: 6)
!3049 = !DILocation(line: 1547, column: 14, scope: !3048)
!3050 = !DILocation(line: 1547, column: 6, scope: !393)
!3051 = !DILocation(line: 1548, column: 11, scope: !3048)
!3052 = !DILocation(line: 1548, column: 3, scope: !3048)
!3053 = !DILocation(line: 1551, column: 6, scope: !3054)
!3054 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1551, column: 6)
!3055 = !DILocation(line: 1551, column: 14, scope: !3054)
!3056 = !DILocation(line: 1551, column: 19, scope: !3054)
!3057 = !DILocation(line: 1551, column: 6, scope: !393)
!3058 = !DILocation(line: 1552, column: 20, scope: !3059)
!3059 = distinct !DILexicalBlock(scope: !3054, file: !1, line: 1551, column: 28)
!3060 = !DILocation(line: 1552, column: 28, scope: !3059)
!3061 = !DILocation(line: 1552, column: 34, scope: !3059)
!3062 = !DILocation(line: 1552, column: 42, scope: !3059)
!3063 = !DILocation(line: 1552, column: 19, scope: !3059)
!3064 = !DILocation(line: 1552, column: 17, scope: !3059)
!3065 = !DILocation(line: 1553, column: 7, scope: !3066)
!3066 = distinct !DILexicalBlock(scope: !3059, file: !1, line: 1553, column: 7)
!3067 = !DILocation(line: 1553, column: 21, scope: !3066)
!3068 = !DILocation(line: 1553, column: 7, scope: !3059)
!3069 = !DILocation(line: 1554, column: 4, scope: !3070)
!3070 = distinct !DILexicalBlock(scope: !3066, file: !1, line: 1553, column: 26)
!3071 = !DILocation(line: 1554, column: 12, scope: !3070)
!3072 = !DILocation(line: 1554, column: 18, scope: !3070)
!3073 = !DILocation(line: 1555, column: 12, scope: !3070)
!3074 = !DILocation(line: 1555, column: 4, scope: !3070)
!3075 = !DILocation(line: 1557, column: 23, scope: !3059)
!3076 = !DILocation(line: 1557, column: 3, scope: !3059)
!3077 = !DILocation(line: 1557, column: 11, scope: !3059)
!3078 = !DILocation(line: 1557, column: 20, scope: !3059)
!3079 = !DILocation(line: 1558, column: 26, scope: !3059)
!3080 = !DILocation(line: 1558, column: 23, scope: !3059)
!3081 = !DILocation(line: 1559, column: 14, scope: !3059)
!3082 = !DILocation(line: 1559, column: 11, scope: !3059)
!3083 = !DILocation(line: 1560, column: 7, scope: !3084)
!3084 = distinct !DILexicalBlock(scope: !3059, file: !1, line: 1560, column: 7)
!3085 = !DILocation(line: 1560, column: 15, scope: !3084)
!3086 = !DILocation(line: 1560, column: 7, scope: !3059)
!3087 = !DILocation(line: 1561, column: 12, scope: !3084)
!3088 = !DILocation(line: 1561, column: 4, scope: !3084)
!3089 = !DILocation(line: 1562, column: 2, scope: !3059)
!3090 = !DILocation(line: 1565, column: 2, scope: !393)
!3091 = !DILocation(line: 1566, column: 17, scope: !3092)
!3092 = distinct !DILexicalBlock(scope: !3093, file: !1, line: 1565, column: 11)
!3093 = distinct !DILexicalBlock(scope: !3094, file: !1, line: 1565, column: 2)
!3094 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1565, column: 2)
!3095 = !DILocation(line: 1566, column: 25, scope: !3092)
!3096 = !DILocation(line: 1566, column: 31, scope: !3092)
!3097 = !DILocation(line: 1566, column: 40, scope: !3092)
!3098 = !DILocation(line: 1566, column: 48, scope: !3092)
!3099 = !DILocation(line: 1566, column: 16, scope: !3092)
!3100 = !DILocation(line: 1566, column: 14, scope: !3092)
!3101 = !DILocation(line: 1567, column: 7, scope: !3102)
!3102 = distinct !DILexicalBlock(scope: !3092, file: !1, line: 1567, column: 7)
!3103 = !DILocation(line: 1567, column: 18, scope: !3102)
!3104 = !DILocation(line: 1567, column: 7, scope: !3092)
!3105 = !DILocation(line: 1568, column: 4, scope: !3106)
!3106 = distinct !DILexicalBlock(scope: !3102, file: !1, line: 1567, column: 23)
!3107 = !DILocation(line: 1568, column: 12, scope: !3106)
!3108 = !DILocation(line: 1568, column: 24, scope: !3106)
!3109 = !DILocation(line: 1569, column: 4, scope: !3106)
!3110 = !DILocation(line: 1569, column: 12, scope: !3106)
!3111 = !DILocation(line: 1569, column: 18, scope: !3106)
!3112 = !DILocation(line: 1570, column: 12, scope: !3106)
!3113 = !DILocation(line: 1570, column: 4, scope: !3106)
!3114 = !DILocation(line: 1573, column: 7, scope: !3115)
!3115 = distinct !DILexicalBlock(scope: !3092, file: !1, line: 1573, column: 7)
!3116 = !DILocation(line: 1573, column: 18, scope: !3115)
!3117 = !DILocation(line: 1573, column: 7, scope: !3092)
!3118 = !DILocation(line: 1574, column: 8, scope: !3119)
!3119 = distinct !DILexicalBlock(scope: !3120, file: !1, line: 1574, column: 8)
!3120 = distinct !DILexicalBlock(scope: !3115, file: !1, line: 1573, column: 24)
!3121 = !DILocation(line: 1574, column: 16, scope: !3119)
!3122 = !DILocation(line: 1574, column: 25, scope: !3119)
!3123 = !DILocation(line: 1574, column: 32, scope: !3119)
!3124 = !DILocation(line: 1575, column: 10, scope: !3119)
!3125 = !DILocation(line: 1575, column: 18, scope: !3119)
!3126 = !DILocation(line: 1575, column: 27, scope: !3119)
!3127 = !DILocation(line: 1575, column: 34, scope: !3119)
!3128 = !DILocation(line: 1575, column: 40, scope: !3119)
!3129 = !DILocation(line: 1574, column: 39, scope: !3119)
!3130 = !DILocation(line: 1574, column: 8, scope: !3120)
!3131 = !DILocation(line: 1576, column: 29, scope: !3132)
!3132 = distinct !DILexicalBlock(scope: !3133, file: !1, line: 1576, column: 9)
!3133 = distinct !DILexicalBlock(scope: !3119, file: !1, line: 1575, column: 45)
!3134 = !DILocation(line: 1577, column: 9, scope: !3132)
!3135 = !DILocation(line: 1577, column: 17, scope: !3132)
!3136 = !DILocation(line: 1577, column: 26, scope: !3132)
!3137 = !DILocation(line: 1577, column: 33, scope: !3132)
!3138 = !DILocation(line: 1577, column: 40, scope: !3132)
!3139 = !DILocation(line: 1576, column: 9, scope: !3132)
!3140 = !DILocation(line: 1578, column: 9, scope: !3132)
!3141 = !DILocation(line: 1576, column: 9, scope: !3133)
!3142 = !DILocation(line: 1579, column: 6, scope: !3132)
!3143 = !DILocation(line: 1580, column: 4, scope: !3133)
!3144 = !DILocation(line: 1581, column: 4, scope: !3120)
!3145 = !DILocation(line: 1581, column: 12, scope: !3120)
!3146 = !DILocation(line: 1581, column: 24, scope: !3120)
!3147 = !DILocation(line: 1582, column: 4, scope: !3120)
!3148 = !DILocation(line: 1582, column: 12, scope: !3120)
!3149 = !DILocation(line: 1582, column: 24, scope: !3120)
!3150 = !DILocation(line: 1583, column: 12, scope: !3120)
!3151 = !DILocation(line: 1583, column: 4, scope: !3120)
!3152 = !DILocation(line: 1586, column: 7, scope: !3153)
!3153 = distinct !DILexicalBlock(scope: !3092, file: !1, line: 1586, column: 7)
!3154 = !DILocation(line: 1586, column: 21, scope: !3153)
!3155 = !DILocation(line: 1586, column: 18, scope: !3153)
!3156 = !DILocation(line: 1586, column: 7, scope: !3092)
!3157 = !DILocation(line: 1588, column: 23, scope: !3158)
!3158 = distinct !DILexicalBlock(scope: !3153, file: !1, line: 1586, column: 30)
!3159 = !DILocation(line: 1588, column: 31, scope: !3158)
!3160 = !DILocation(line: 1588, column: 46, scope: !3158)
!3161 = !DILocation(line: 1588, column: 44, scope: !3158)
!3162 = !DILocation(line: 1587, column: 4, scope: !3158)
!3163 = !DILocation(line: 1587, column: 12, scope: !3158)
!3164 = !DILocation(line: 1587, column: 24, scope: !3158)
!3165 = !DILocation(line: 1589, column: 36, scope: !3158)
!3166 = !DILocation(line: 1589, column: 49, scope: !3158)
!3167 = !DILocation(line: 1589, column: 47, scope: !3158)
!3168 = !DILocation(line: 1589, column: 4, scope: !3158)
!3169 = !DILocation(line: 1589, column: 12, scope: !3158)
!3170 = !DILocation(line: 1589, column: 25, scope: !3158)
!3171 = !DILocation(line: 1590, column: 27, scope: !3158)
!3172 = !DILocation(line: 1590, column: 4, scope: !3158)
!3173 = !DILocation(line: 1590, column: 12, scope: !3158)
!3174 = !DILocation(line: 1590, column: 25, scope: !3158)
!3175 = !DILocation(line: 1591, column: 27, scope: !3158)
!3176 = !DILocation(line: 1591, column: 24, scope: !3158)
!3177 = !DILocation(line: 1592, column: 24, scope: !3158)
!3178 = !DILocation(line: 1592, column: 4, scope: !3158)
!3179 = !DILocation(line: 1592, column: 12, scope: !3158)
!3180 = !DILocation(line: 1592, column: 21, scope: !3158)
!3181 = !DILocation(line: 1593, column: 12, scope: !3158)
!3182 = !DILocation(line: 1593, column: 4, scope: !3158)
!3183 = !DILocation(line: 1596, column: 23, scope: !3092)
!3184 = !DILocation(line: 1596, column: 3, scope: !3092)
!3185 = !DILocation(line: 1596, column: 11, scope: !3092)
!3186 = !DILocation(line: 1596, column: 20, scope: !3092)
!3187 = !DILocation(line: 1597, column: 26, scope: !3092)
!3188 = !DILocation(line: 1597, column: 23, scope: !3092)
!3189 = !DILocation(line: 1598, column: 14, scope: !3092)
!3190 = !DILocation(line: 1598, column: 11, scope: !3092)
!3191 = !DILocation(line: 1565, column: 2, scope: !3192)
!3192 = !DILexicalBlockFile(scope: !3093, file: !1, discriminator: 1)
!3193 = !DILocation(line: 1600, column: 1, scope: !393)
!3194 = !DILocalVariable(name: "a", arg: 1, scope: !367, file: !1, line: 1606, type: !4)
!3195 = !DILocation(line: 1606, column: 42, scope: !367)
!3196 = !DILocalVariable(name: "offset", arg: 2, scope: !367, file: !1, line: 1606, type: !52)
!3197 = !DILocation(line: 1606, column: 53, scope: !367)
!3198 = !DILocalVariable(name: "whence", arg: 3, scope: !367, file: !1, line: 1606, type: !23)
!3199 = !DILocation(line: 1606, column: 65, scope: !367)
!3200 = !DILocation(line: 1608, column: 36, scope: !367)
!3201 = !DILocation(line: 1608, column: 39, scope: !367)
!3202 = !DILocation(line: 1608, column: 47, scope: !367)
!3203 = !DILocation(line: 1608, column: 55, scope: !367)
!3204 = !DILocation(line: 1608, column: 9, scope: !367)
!3205 = !DILocation(line: 1608, column: 2, scope: !367)
!3206 = !DILocalVariable(name: "filter", arg: 1, scope: !368, file: !1, line: 1612, type: !169)
!3207 = !DILocation(line: 1612, column: 56, scope: !368)
!3208 = !DILocalVariable(name: "offset", arg: 2, scope: !368, file: !1, line: 1612, type: !52)
!3209 = !DILocation(line: 1612, column: 72, scope: !368)
!3210 = !DILocalVariable(name: "whence", arg: 3, scope: !368, file: !1, line: 1613, type: !23)
!3211 = !DILocation(line: 1613, column: 9, scope: !368)
!3212 = !DILocalVariable(name: "client", scope: !368, file: !1, line: 1615, type: !3213)
!3213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!3214 = !DILocation(line: 1615, column: 30, scope: !368)
!3215 = !DILocalVariable(name: "r", scope: !368, file: !1, line: 1616, type: !52)
!3216 = !DILocation(line: 1616, column: 10, scope: !368)
!3217 = !DILocalVariable(name: "cursor", scope: !368, file: !1, line: 1617, type: !13)
!3218 = !DILocation(line: 1617, column: 15, scope: !368)
!3219 = !DILocation(line: 1619, column: 6, scope: !3220)
!3220 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1619, column: 6)
!3221 = !DILocation(line: 1619, column: 14, scope: !3220)
!3222 = !DILocation(line: 1619, column: 21, scope: !3220)
!3223 = !DILocation(line: 1619, column: 24, scope: !3224)
!3224 = !DILexicalBlockFile(scope: !3220, file: !1, discriminator: 1)
!3225 = !DILocation(line: 1619, column: 32, scope: !3224)
!3226 = !DILocation(line: 1619, column: 6, scope: !3224)
!3227 = !DILocation(line: 1620, column: 3, scope: !3220)
!3228 = !DILocation(line: 1621, column: 6, scope: !3229)
!3229 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1621, column: 6)
!3230 = !DILocation(line: 1621, column: 14, scope: !3229)
!3231 = !DILocation(line: 1621, column: 19, scope: !3229)
!3232 = !DILocation(line: 1621, column: 6, scope: !368)
!3233 = !DILocation(line: 1622, column: 3, scope: !3229)
!3234 = !DILocation(line: 1624, column: 13, scope: !368)
!3235 = !DILocation(line: 1624, column: 21, scope: !368)
!3236 = !DILocation(line: 1624, column: 30, scope: !368)
!3237 = !DILocation(line: 1624, column: 9, scope: !368)
!3238 = !DILocation(line: 1625, column: 10, scope: !368)
!3239 = !DILocation(line: 1625, column: 2, scope: !368)
!3240 = !DILocation(line: 1628, column: 13, scope: !3241)
!3241 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1625, column: 18)
!3242 = !DILocation(line: 1628, column: 21, scope: !3241)
!3243 = !DILocation(line: 1628, column: 10, scope: !3241)
!3244 = !DILocation(line: 1628, column: 3, scope: !3241)
!3245 = !DILocation(line: 1630, column: 10, scope: !3241)
!3246 = !DILocation(line: 1631, column: 3, scope: !3241)
!3247 = !DILocation(line: 1633, column: 24, scope: !3248)
!3248 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 1633, column: 8)
!3249 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1632, column: 3)
!3250 = !DILocation(line: 1633, column: 8, scope: !3248)
!3251 = !DILocation(line: 1633, column: 16, scope: !3248)
!3252 = !DILocation(line: 1633, column: 32, scope: !3248)
!3253 = !DILocation(line: 1633, column: 47, scope: !3248)
!3254 = !DILocation(line: 1633, column: 51, scope: !3248)
!3255 = !DILocation(line: 1634, column: 24, scope: !3248)
!3256 = !DILocation(line: 1634, column: 8, scope: !3248)
!3257 = !DILocation(line: 1634, column: 16, scope: !3248)
!3258 = !DILocation(line: 1634, column: 32, scope: !3248)
!3259 = !DILocation(line: 1634, column: 43, scope: !3248)
!3260 = !DILocation(line: 1634, column: 47, scope: !3248)
!3261 = !DILocation(line: 1635, column: 24, scope: !3248)
!3262 = !DILocation(line: 1635, column: 8, scope: !3248)
!3263 = !DILocation(line: 1635, column: 16, scope: !3248)
!3264 = !DILocation(line: 1635, column: 32, scope: !3248)
!3265 = !DILocation(line: 1636, column: 26, scope: !3248)
!3266 = !DILocation(line: 1636, column: 10, scope: !3248)
!3267 = !DILocation(line: 1636, column: 18, scope: !3248)
!3268 = !DILocation(line: 1636, column: 34, scope: !3248)
!3269 = !DILocation(line: 1635, column: 47, scope: !3248)
!3270 = !DILocation(line: 1636, column: 45, scope: !3248)
!3271 = !DILocation(line: 1636, column: 51, scope: !3248)
!3272 = !DILocation(line: 1636, column: 49, scope: !3248)
!3273 = !DILocation(line: 1636, column: 58, scope: !3248)
!3274 = !DILocation(line: 1637, column: 8, scope: !3248)
!3275 = !DILocation(line: 1637, column: 15, scope: !3248)
!3276 = !DILocation(line: 1637, column: 22, scope: !3248)
!3277 = !DILocation(line: 1637, column: 30, scope: !3248)
!3278 = !DILocation(line: 1637, column: 19, scope: !3248)
!3279 = !DILocation(line: 1633, column: 8, scope: !3280)
!3280 = !DILexicalBlockFile(scope: !3249, file: !1, discriminator: 1)
!3281 = !DILocation(line: 1638, column: 5, scope: !3248)
!3282 = !DILocation(line: 1639, column: 24, scope: !3249)
!3283 = !DILocation(line: 1639, column: 8, scope: !3249)
!3284 = !DILocation(line: 1639, column: 16, scope: !3249)
!3285 = !DILocation(line: 1639, column: 32, scope: !3249)
!3286 = !DILocation(line: 1640, column: 21, scope: !3249)
!3287 = !DILocation(line: 1640, column: 5, scope: !3249)
!3288 = !DILocation(line: 1640, column: 13, scope: !3249)
!3289 = !DILocation(line: 1640, column: 29, scope: !3249)
!3290 = !DILocation(line: 1639, column: 47, scope: !3249)
!3291 = !DILocation(line: 1639, column: 6, scope: !3249)
!3292 = !DILocation(line: 1641, column: 47, scope: !3249)
!3293 = !DILocation(line: 1641, column: 20, scope: !3249)
!3294 = !DILocation(line: 1641, column: 4, scope: !3249)
!3295 = !DILocation(line: 1641, column: 12, scope: !3249)
!3296 = !DILocation(line: 1641, column: 30, scope: !3249)
!3297 = !DILocation(line: 1641, column: 45, scope: !3249)
!3298 = !DILocation(line: 1631, column: 3, scope: !3299)
!3299 = !DILexicalBlockFile(scope: !3241, file: !1, discriminator: 1)
!3300 = !DILocation(line: 1643, column: 3, scope: !3241)
!3301 = !DILocation(line: 1644, column: 28, scope: !3302)
!3302 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1643, column: 13)
!3303 = !DILocation(line: 1644, column: 36, scope: !3302)
!3304 = !DILocation(line: 1644, column: 8, scope: !3302)
!3305 = !DILocation(line: 1644, column: 6, scope: !3302)
!3306 = !DILocation(line: 1645, column: 8, scope: !3307)
!3307 = distinct !DILexicalBlock(scope: !3302, file: !1, line: 1645, column: 8)
!3308 = !DILocation(line: 1645, column: 10, scope: !3307)
!3309 = !DILocation(line: 1645, column: 8, scope: !3302)
!3310 = !DILocation(line: 1646, column: 12, scope: !3307)
!3311 = !DILocation(line: 1646, column: 5, scope: !3307)
!3312 = !DILocation(line: 1647, column: 31, scope: !3313)
!3313 = distinct !DILexicalBlock(scope: !3302, file: !1, line: 1647, column: 8)
!3314 = !DILocation(line: 1647, column: 13, scope: !3313)
!3315 = !DILocation(line: 1647, column: 11, scope: !3313)
!3316 = !DILocation(line: 1647, column: 53, scope: !3313)
!3317 = !DILocation(line: 1647, column: 8, scope: !3302)
!3318 = !DILocation(line: 1648, column: 12, scope: !3313)
!3319 = !DILocation(line: 1648, column: 5, scope: !3313)
!3320 = !DILocation(line: 1649, column: 41, scope: !3302)
!3321 = !DILocation(line: 1649, column: 20, scope: !3302)
!3322 = !DILocation(line: 1649, column: 4, scope: !3302)
!3323 = !DILocation(line: 1649, column: 12, scope: !3302)
!3324 = !DILocation(line: 1649, column: 28, scope: !3302)
!3325 = !DILocation(line: 1649, column: 39, scope: !3302)
!3326 = !DILocation(line: 1650, column: 24, scope: !3327)
!3327 = distinct !DILexicalBlock(scope: !3302, file: !1, line: 1650, column: 8)
!3328 = !DILocation(line: 1650, column: 8, scope: !3327)
!3329 = !DILocation(line: 1650, column: 16, scope: !3327)
!3330 = !DILocation(line: 1650, column: 32, scope: !3327)
!3331 = !DILocation(line: 1651, column: 24, scope: !3327)
!3332 = !DILocation(line: 1651, column: 8, scope: !3327)
!3333 = !DILocation(line: 1651, column: 16, scope: !3327)
!3334 = !DILocation(line: 1651, column: 32, scope: !3327)
!3335 = !DILocation(line: 1650, column: 47, scope: !3327)
!3336 = !DILocation(line: 1651, column: 43, scope: !3327)
!3337 = !DILocation(line: 1651, column: 49, scope: !3327)
!3338 = !DILocation(line: 1651, column: 47, scope: !3327)
!3339 = !DILocation(line: 1651, column: 56, scope: !3327)
!3340 = !DILocation(line: 1652, column: 8, scope: !3327)
!3341 = !DILocation(line: 1652, column: 15, scope: !3327)
!3342 = !DILocation(line: 1652, column: 22, scope: !3327)
!3343 = !DILocation(line: 1652, column: 30, scope: !3327)
!3344 = !DILocation(line: 1652, column: 19, scope: !3327)
!3345 = !DILocation(line: 1650, column: 8, scope: !3346)
!3346 = !DILexicalBlockFile(scope: !3302, file: !1, discriminator: 1)
!3347 = !DILocation(line: 1653, column: 5, scope: !3327)
!3348 = !DILocation(line: 1654, column: 24, scope: !3302)
!3349 = !DILocation(line: 1654, column: 8, scope: !3302)
!3350 = !DILocation(line: 1654, column: 16, scope: !3302)
!3351 = !DILocation(line: 1654, column: 32, scope: !3302)
!3352 = !DILocation(line: 1655, column: 21, scope: !3302)
!3353 = !DILocation(line: 1655, column: 5, scope: !3302)
!3354 = !DILocation(line: 1655, column: 13, scope: !3302)
!3355 = !DILocation(line: 1655, column: 29, scope: !3302)
!3356 = !DILocation(line: 1654, column: 47, scope: !3302)
!3357 = !DILocation(line: 1654, column: 6, scope: !3302)
!3358 = !DILocation(line: 1656, column: 47, scope: !3302)
!3359 = !DILocation(line: 1656, column: 20, scope: !3302)
!3360 = !DILocation(line: 1656, column: 4, scope: !3302)
!3361 = !DILocation(line: 1656, column: 12, scope: !3302)
!3362 = !DILocation(line: 1656, column: 30, scope: !3302)
!3363 = !DILocation(line: 1656, column: 45, scope: !3302)
!3364 = !DILocation(line: 1643, column: 3, scope: !3299)
!3365 = !DILocation(line: 1658, column: 29, scope: !3241)
!3366 = !DILocation(line: 1658, column: 13, scope: !3241)
!3367 = !DILocation(line: 1658, column: 21, scope: !3241)
!3368 = !DILocation(line: 1658, column: 37, scope: !3241)
!3369 = !DILocation(line: 1658, column: 10, scope: !3241)
!3370 = !DILocation(line: 1659, column: 7, scope: !3371)
!3371 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1659, column: 7)
!3372 = !DILocation(line: 1659, column: 14, scope: !3371)
!3373 = !DILocation(line: 1660, column: 7, scope: !3371)
!3374 = !DILocation(line: 1660, column: 10, scope: !3375)
!3375 = !DILexicalBlockFile(scope: !3371, file: !1, discriminator: 1)
!3376 = !DILocation(line: 1660, column: 35, scope: !3375)
!3377 = !DILocation(line: 1660, column: 19, scope: !3375)
!3378 = !DILocation(line: 1660, column: 27, scope: !3375)
!3379 = !DILocation(line: 1660, column: 43, scope: !3375)
!3380 = !DILocation(line: 1660, column: 17, scope: !3375)
!3381 = !DILocation(line: 1659, column: 7, scope: !3299)
!3382 = !DILocation(line: 1661, column: 4, scope: !3371)
!3383 = !DILocation(line: 1662, column: 30, scope: !3384)
!3384 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1662, column: 7)
!3385 = !DILocation(line: 1662, column: 38, scope: !3384)
!3386 = !DILocation(line: 1662, column: 12, scope: !3384)
!3387 = !DILocation(line: 1662, column: 10, scope: !3384)
!3388 = !DILocation(line: 1662, column: 57, scope: !3384)
!3389 = !DILocation(line: 1662, column: 7, scope: !3241)
!3390 = !DILocation(line: 1663, column: 11, scope: !3384)
!3391 = !DILocation(line: 1663, column: 4, scope: !3384)
!3392 = !DILocation(line: 1664, column: 3, scope: !3241)
!3393 = !DILocation(line: 1667, column: 10, scope: !3241)
!3394 = !DILocation(line: 1668, column: 3, scope: !3241)
!3395 = !DILocation(line: 1669, column: 24, scope: !3396)
!3396 = distinct !DILexicalBlock(scope: !3397, file: !1, line: 1669, column: 8)
!3397 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1668, column: 13)
!3398 = !DILocation(line: 1669, column: 8, scope: !3396)
!3399 = !DILocation(line: 1669, column: 16, scope: !3396)
!3400 = !DILocation(line: 1669, column: 32, scope: !3396)
!3401 = !DILocation(line: 1669, column: 47, scope: !3396)
!3402 = !DILocation(line: 1669, column: 51, scope: !3396)
!3403 = !DILocation(line: 1670, column: 24, scope: !3396)
!3404 = !DILocation(line: 1670, column: 8, scope: !3396)
!3405 = !DILocation(line: 1670, column: 16, scope: !3396)
!3406 = !DILocation(line: 1670, column: 32, scope: !3396)
!3407 = !DILocation(line: 1670, column: 43, scope: !3396)
!3408 = !DILocation(line: 1670, column: 47, scope: !3396)
!3409 = !DILocation(line: 1671, column: 8, scope: !3396)
!3410 = !DILocation(line: 1671, column: 15, scope: !3396)
!3411 = !DILocation(line: 1671, column: 22, scope: !3396)
!3412 = !DILocation(line: 1671, column: 30, scope: !3396)
!3413 = !DILocation(line: 1671, column: 19, scope: !3396)
!3414 = !DILocation(line: 1669, column: 8, scope: !3415)
!3415 = !DILexicalBlockFile(scope: !3397, file: !1, discriminator: 1)
!3416 = !DILocation(line: 1672, column: 5, scope: !3396)
!3417 = !DILocation(line: 1673, column: 24, scope: !3397)
!3418 = !DILocation(line: 1673, column: 8, scope: !3397)
!3419 = !DILocation(line: 1673, column: 16, scope: !3397)
!3420 = !DILocation(line: 1673, column: 32, scope: !3397)
!3421 = !DILocation(line: 1674, column: 21, scope: !3397)
!3422 = !DILocation(line: 1674, column: 5, scope: !3397)
!3423 = !DILocation(line: 1674, column: 13, scope: !3397)
!3424 = !DILocation(line: 1674, column: 29, scope: !3397)
!3425 = !DILocation(line: 1673, column: 47, scope: !3397)
!3426 = !DILocation(line: 1673, column: 6, scope: !3397)
!3427 = !DILocation(line: 1675, column: 47, scope: !3397)
!3428 = !DILocation(line: 1675, column: 20, scope: !3397)
!3429 = !DILocation(line: 1675, column: 4, scope: !3397)
!3430 = !DILocation(line: 1675, column: 12, scope: !3397)
!3431 = !DILocation(line: 1675, column: 30, scope: !3397)
!3432 = !DILocation(line: 1675, column: 45, scope: !3397)
!3433 = !DILocation(line: 1668, column: 3, scope: !3299)
!3434 = !DILocation(line: 1677, column: 3, scope: !3241)
!3435 = !DILocation(line: 1678, column: 28, scope: !3436)
!3436 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1677, column: 13)
!3437 = !DILocation(line: 1678, column: 36, scope: !3436)
!3438 = !DILocation(line: 1678, column: 8, scope: !3436)
!3439 = !DILocation(line: 1678, column: 6, scope: !3436)
!3440 = !DILocation(line: 1679, column: 8, scope: !3441)
!3441 = distinct !DILexicalBlock(scope: !3436, file: !1, line: 1679, column: 8)
!3442 = !DILocation(line: 1679, column: 10, scope: !3441)
!3443 = !DILocation(line: 1679, column: 8, scope: !3436)
!3444 = !DILocation(line: 1680, column: 12, scope: !3441)
!3445 = !DILocation(line: 1680, column: 5, scope: !3441)
!3446 = !DILocation(line: 1681, column: 31, scope: !3447)
!3447 = distinct !DILexicalBlock(scope: !3436, file: !1, line: 1681, column: 8)
!3448 = !DILocation(line: 1681, column: 13, scope: !3447)
!3449 = !DILocation(line: 1681, column: 11, scope: !3447)
!3450 = !DILocation(line: 1681, column: 53, scope: !3447)
!3451 = !DILocation(line: 1681, column: 8, scope: !3436)
!3452 = !DILocation(line: 1682, column: 12, scope: !3447)
!3453 = !DILocation(line: 1682, column: 5, scope: !3447)
!3454 = !DILocation(line: 1683, column: 41, scope: !3436)
!3455 = !DILocation(line: 1683, column: 20, scope: !3436)
!3456 = !DILocation(line: 1683, column: 4, scope: !3436)
!3457 = !DILocation(line: 1683, column: 12, scope: !3436)
!3458 = !DILocation(line: 1683, column: 28, scope: !3436)
!3459 = !DILocation(line: 1683, column: 39, scope: !3436)
!3460 = !DILocation(line: 1684, column: 24, scope: !3436)
!3461 = !DILocation(line: 1684, column: 8, scope: !3436)
!3462 = !DILocation(line: 1684, column: 16, scope: !3436)
!3463 = !DILocation(line: 1684, column: 32, scope: !3436)
!3464 = !DILocation(line: 1685, column: 21, scope: !3436)
!3465 = !DILocation(line: 1685, column: 5, scope: !3436)
!3466 = !DILocation(line: 1685, column: 13, scope: !3436)
!3467 = !DILocation(line: 1685, column: 29, scope: !3436)
!3468 = !DILocation(line: 1684, column: 47, scope: !3436)
!3469 = !DILocation(line: 1684, column: 6, scope: !3436)
!3470 = !DILocation(line: 1686, column: 8, scope: !3471)
!3471 = distinct !DILexicalBlock(scope: !3436, file: !1, line: 1686, column: 8)
!3472 = !DILocation(line: 1686, column: 15, scope: !3471)
!3473 = !DILocation(line: 1686, column: 22, scope: !3471)
!3474 = !DILocation(line: 1686, column: 30, scope: !3471)
!3475 = !DILocation(line: 1686, column: 19, scope: !3471)
!3476 = !DILocation(line: 1686, column: 8, scope: !3436)
!3477 = !DILocation(line: 1687, column: 5, scope: !3471)
!3478 = !DILocation(line: 1688, column: 47, scope: !3436)
!3479 = !DILocation(line: 1688, column: 20, scope: !3436)
!3480 = !DILocation(line: 1688, column: 4, scope: !3436)
!3481 = !DILocation(line: 1688, column: 12, scope: !3436)
!3482 = !DILocation(line: 1688, column: 30, scope: !3436)
!3483 = !DILocation(line: 1688, column: 45, scope: !3436)
!3484 = !DILocation(line: 1677, column: 3, scope: !3299)
!3485 = !DILocation(line: 1690, column: 3, scope: !3241)
!3486 = !DILocation(line: 1691, column: 8, scope: !3487)
!3487 = distinct !DILexicalBlock(scope: !3488, file: !1, line: 1691, column: 8)
!3488 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1690, column: 13)
!3489 = !DILocation(line: 1691, column: 12, scope: !3487)
!3490 = !DILocation(line: 1691, column: 10, scope: !3487)
!3491 = !DILocation(line: 1692, column: 24, scope: !3487)
!3492 = !DILocation(line: 1692, column: 8, scope: !3487)
!3493 = !DILocation(line: 1692, column: 16, scope: !3487)
!3494 = !DILocation(line: 1692, column: 32, scope: !3487)
!3495 = !DILocation(line: 1691, column: 19, scope: !3487)
!3496 = !DILocation(line: 1691, column: 8, scope: !3488)
!3497 = !DILocation(line: 1693, column: 5, scope: !3487)
!3498 = !DILocation(line: 1694, column: 30, scope: !3488)
!3499 = !DILocation(line: 1694, column: 14, scope: !3488)
!3500 = !DILocation(line: 1694, column: 22, scope: !3488)
!3501 = !DILocation(line: 1694, column: 38, scope: !3488)
!3502 = !DILocation(line: 1694, column: 11, scope: !3488)
!3503 = !DILocation(line: 1695, column: 8, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !3488, file: !1, line: 1695, column: 8)
!3505 = !DILocation(line: 1695, column: 15, scope: !3504)
!3506 = !DILocation(line: 1695, column: 8, scope: !3488)
!3507 = !DILocation(line: 1696, column: 5, scope: !3504)
!3508 = !DILocation(line: 1697, column: 10, scope: !3488)
!3509 = !DILocation(line: 1698, column: 24, scope: !3488)
!3510 = !DILocation(line: 1698, column: 8, scope: !3488)
!3511 = !DILocation(line: 1698, column: 16, scope: !3488)
!3512 = !DILocation(line: 1698, column: 32, scope: !3488)
!3513 = !DILocation(line: 1699, column: 21, scope: !3488)
!3514 = !DILocation(line: 1699, column: 5, scope: !3488)
!3515 = !DILocation(line: 1699, column: 13, scope: !3488)
!3516 = !DILocation(line: 1699, column: 29, scope: !3488)
!3517 = !DILocation(line: 1698, column: 47, scope: !3488)
!3518 = !DILocation(line: 1698, column: 6, scope: !3488)
!3519 = !DILocation(line: 1690, column: 3, scope: !3299)
!3520 = !DILocation(line: 1701, column: 13, scope: !3241)
!3521 = !DILocation(line: 1701, column: 17, scope: !3241)
!3522 = !DILocation(line: 1701, column: 15, scope: !3241)
!3523 = !DILocation(line: 1701, column: 43, scope: !3241)
!3524 = !DILocation(line: 1701, column: 27, scope: !3241)
!3525 = !DILocation(line: 1701, column: 35, scope: !3241)
!3526 = !DILocation(line: 1701, column: 51, scope: !3241)
!3527 = !DILocation(line: 1701, column: 25, scope: !3241)
!3528 = !DILocation(line: 1701, column: 10, scope: !3241)
!3529 = !DILocation(line: 1702, column: 32, scope: !3530)
!3530 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1702, column: 7)
!3531 = !DILocation(line: 1702, column: 40, scope: !3530)
!3532 = !DILocation(line: 1702, column: 12, scope: !3530)
!3533 = !DILocation(line: 1702, column: 10, scope: !3530)
!3534 = !DILocation(line: 1702, column: 49, scope: !3530)
!3535 = !DILocation(line: 1702, column: 7, scope: !3241)
!3536 = !DILocation(line: 1703, column: 11, scope: !3530)
!3537 = !DILocation(line: 1703, column: 4, scope: !3530)
!3538 = !DILocation(line: 1704, column: 25, scope: !3241)
!3539 = !DILocation(line: 1704, column: 33, scope: !3241)
!3540 = !DILocation(line: 1704, column: 7, scope: !3241)
!3541 = !DILocation(line: 1704, column: 5, scope: !3241)
!3542 = !DILocation(line: 1705, column: 7, scope: !3543)
!3543 = distinct !DILexicalBlock(scope: !3241, file: !1, line: 1705, column: 7)
!3544 = !DILocation(line: 1705, column: 9, scope: !3543)
!3545 = !DILocation(line: 1705, column: 7, scope: !3241)
!3546 = !DILocation(line: 1706, column: 11, scope: !3543)
!3547 = !DILocation(line: 1706, column: 4, scope: !3543)
!3548 = !DILocation(line: 1707, column: 3, scope: !3241)
!3549 = !DILocation(line: 1710, column: 3, scope: !3241)
!3550 = !DILocation(line: 1712, column: 23, scope: !368)
!3551 = !DILocation(line: 1712, column: 7, scope: !368)
!3552 = !DILocation(line: 1712, column: 15, scope: !368)
!3553 = !DILocation(line: 1712, column: 31, scope: !368)
!3554 = !DILocation(line: 1712, column: 4, scope: !368)
!3555 = !DILocation(line: 1714, column: 6, scope: !3556)
!3556 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1714, column: 6)
!3557 = !DILocation(line: 1714, column: 8, scope: !3556)
!3558 = !DILocation(line: 1714, column: 6, scope: !368)
!3559 = !DILocation(line: 1732, column: 19, scope: !3560)
!3560 = distinct !DILexicalBlock(scope: !3556, file: !1, line: 1714, column: 14)
!3561 = !DILocation(line: 1732, column: 27, scope: !3560)
!3562 = !DILocation(line: 1732, column: 40, scope: !3560)
!3563 = !DILocation(line: 1732, column: 3, scope: !3560)
!3564 = !DILocation(line: 1732, column: 11, scope: !3560)
!3565 = !DILocation(line: 1732, column: 17, scope: !3560)
!3566 = !DILocation(line: 1733, column: 18, scope: !3560)
!3567 = !DILocation(line: 1733, column: 26, scope: !3560)
!3568 = !DILocation(line: 1733, column: 3, scope: !3560)
!3569 = !DILocation(line: 1733, column: 11, scope: !3560)
!3570 = !DILocation(line: 1733, column: 16, scope: !3560)
!3571 = !DILocation(line: 1734, column: 22, scope: !3560)
!3572 = !DILocation(line: 1734, column: 3, scope: !3560)
!3573 = !DILocation(line: 1734, column: 11, scope: !3560)
!3574 = !DILocation(line: 1734, column: 20, scope: !3560)
!3575 = !DILocation(line: 1735, column: 3, scope: !3560)
!3576 = !DILocation(line: 1735, column: 11, scope: !3560)
!3577 = !DILocation(line: 1735, column: 23, scope: !3560)
!3578 = !DILocation(line: 1736, column: 2, scope: !3560)
!3579 = !DILocation(line: 1737, column: 9, scope: !368)
!3580 = !DILocation(line: 1737, column: 2, scope: !368)
!3581 = !DILocation(line: 1738, column: 1, scope: !368)
!3582 = !DILocalVariable(name: "_a", arg: 1, scope: !372, file: !1, line: 1170, type: !24)
!3583 = !DILocation(line: 1170, column: 39, scope: !372)
!3584 = !DILocalVariable(name: "n", arg: 2, scope: !372, file: !1, line: 1170, type: !23)
!3585 = !DILocation(line: 1170, column: 47, scope: !372)
!3586 = !DILocalVariable(name: "f", scope: !372, file: !1, line: 1172, type: !169)
!3587 = !DILocation(line: 1172, column: 30, scope: !372)
!3588 = !DILocation(line: 1172, column: 45, scope: !372)
!3589 = !DILocation(line: 1172, column: 49, scope: !372)
!3590 = !DILocation(line: 1172, column: 34, scope: !372)
!3591 = !DILocation(line: 1173, column: 9, scope: !372)
!3592 = !DILocation(line: 1173, column: 11, scope: !372)
!3593 = !DILocation(line: 1173, column: 9, scope: !3594)
!3594 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 1)
!3595 = !DILocation(line: 1173, column: 26, scope: !3596)
!3596 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 2)
!3597 = !DILocation(line: 1173, column: 29, scope: !3596)
!3598 = !DILocation(line: 1173, column: 9, scope: !3596)
!3599 = !DILocation(line: 1173, column: 9, scope: !3600)
!3600 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 3)
!3601 = !DILocation(line: 1173, column: 2, scope: !3600)
!3602 = !DILocalVariable(name: "_a", arg: 1, scope: !376, file: !1, line: 1156, type: !24)
!3603 = !DILocation(line: 1156, column: 38, scope: !376)
!3604 = !DILocalVariable(name: "n", arg: 2, scope: !376, file: !1, line: 1156, type: !23)
!3605 = !DILocation(line: 1156, column: 46, scope: !376)
!3606 = !DILocalVariable(name: "f", scope: !376, file: !1, line: 1158, type: !169)
!3607 = !DILocation(line: 1158, column: 30, scope: !376)
!3608 = !DILocation(line: 1158, column: 45, scope: !376)
!3609 = !DILocation(line: 1158, column: 49, scope: !376)
!3610 = !DILocation(line: 1158, column: 34, scope: !376)
!3611 = !DILocation(line: 1159, column: 9, scope: !376)
!3612 = !DILocation(line: 1159, column: 11, scope: !376)
!3613 = !DILocation(line: 1159, column: 9, scope: !3614)
!3614 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 1)
!3615 = !DILocation(line: 1159, column: 26, scope: !3616)
!3616 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 2)
!3617 = !DILocation(line: 1159, column: 29, scope: !3616)
!3618 = !DILocation(line: 1159, column: 9, scope: !3616)
!3619 = !DILocation(line: 1159, column: 9, scope: !3620)
!3620 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 3)
!3621 = !DILocation(line: 1159, column: 2, scope: !3620)
!3622 = !DILocalVariable(name: "_a", arg: 1, scope: !377, file: !1, line: 1163, type: !24)
!3623 = !DILocation(line: 1163, column: 38, scope: !377)
!3624 = !DILocalVariable(name: "n", arg: 2, scope: !377, file: !1, line: 1163, type: !23)
!3625 = !DILocation(line: 1163, column: 46, scope: !377)
!3626 = !DILocalVariable(name: "f", scope: !377, file: !1, line: 1165, type: !169)
!3627 = !DILocation(line: 1165, column: 30, scope: !377)
!3628 = !DILocation(line: 1165, column: 45, scope: !377)
!3629 = !DILocation(line: 1165, column: 49, scope: !377)
!3630 = !DILocation(line: 1165, column: 34, scope: !377)
!3631 = !DILocation(line: 1166, column: 9, scope: !377)
!3632 = !DILocation(line: 1166, column: 11, scope: !377)
!3633 = !DILocation(line: 1166, column: 21, scope: !3634)
!3634 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 1)
!3635 = !DILocation(line: 1166, column: 24, scope: !3634)
!3636 = !DILocation(line: 1166, column: 9, scope: !3634)
!3637 = !DILocation(line: 1166, column: 9, scope: !3638)
!3638 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 2)
!3639 = !DILocation(line: 1166, column: 9, scope: !3640)
!3640 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 3)
!3641 = !DILocation(line: 1166, column: 2, scope: !3640)
!3642 = !DILocalVariable(name: "_a", arg: 1, scope: !378, file: !1, line: 1026, type: !24)
!3643 = !DILocation(line: 1026, column: 39, scope: !378)
!3644 = !DILocalVariable(name: "a", scope: !378, file: !1, line: 1028, type: !4)
!3645 = !DILocation(line: 1028, column: 23, scope: !378)
!3646 = !DILocation(line: 1028, column: 50, scope: !378)
!3647 = !DILocation(line: 1028, column: 27, scope: !378)
!3648 = !DILocalVariable(name: "p", scope: !378, file: !1, line: 1029, type: !169)
!3649 = !DILocation(line: 1029, column: 30, scope: !378)
!3650 = !DILocation(line: 1029, column: 34, scope: !378)
!3651 = !DILocation(line: 1029, column: 37, scope: !378)
!3652 = !DILocalVariable(name: "count", scope: !378, file: !1, line: 1030, type: !23)
!3653 = !DILocation(line: 1030, column: 6, scope: !378)
!3654 = !DILocation(line: 1031, column: 2, scope: !378)
!3655 = !DILocation(line: 1031, column: 8, scope: !3656)
!3656 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!3657 = !DILocation(line: 1031, column: 2, scope: !3656)
!3658 = !DILocation(line: 1032, column: 8, scope: !3659)
!3659 = distinct !DILexicalBlock(scope: !378, file: !1, line: 1031, column: 11)
!3660 = !DILocation(line: 1033, column: 7, scope: !3659)
!3661 = !DILocation(line: 1033, column: 10, scope: !3659)
!3662 = !DILocation(line: 1033, column: 5, scope: !3659)
!3663 = !DILocation(line: 1031, column: 2, scope: !3664)
!3664 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 2)
!3665 = !DILocation(line: 1035, column: 9, scope: !378)
!3666 = !DILocation(line: 1035, column: 2, scope: !378)
!3667 = !DILocalVariable(name: "_a", arg: 1, scope: !379, file: !1, line: 971, type: !24)
!3668 = !DILocation(line: 971, column: 42, scope: !379)
!3669 = !DILocalVariable(name: "buff", arg: 2, scope: !379, file: !1, line: 972, type: !64)
!3670 = !DILocation(line: 972, column: 18, scope: !379)
!3671 = !DILocalVariable(name: "size", arg: 3, scope: !379, file: !1, line: 972, type: !65)
!3672 = !DILocation(line: 972, column: 32, scope: !379)
!3673 = !DILocalVariable(name: "offset", arg: 4, scope: !379, file: !1, line: 972, type: !66)
!3674 = !DILocation(line: 972, column: 47, scope: !379)
!3675 = !DILocalVariable(name: "a", scope: !379, file: !1, line: 974, type: !4)
!3676 = !DILocation(line: 974, column: 23, scope: !379)
!3677 = !DILocation(line: 974, column: 50, scope: !379)
!3678 = !DILocation(line: 974, column: 27, scope: !379)
!3679 = !DILocation(line: 975, column: 2, scope: !379)
!3680 = !DILocalVariable(name: "magic_test", scope: !3681, file: !1, line: 975, type: !23)
!3681 = distinct !DILexicalBlock(scope: !379, file: !1, line: 975, column: 2)
!3682 = !DILocation(line: 975, column: 2, scope: !3681)
!3683 = !DILocation(line: 975, column: 2, scope: !3684)
!3684 = !DILexicalBlockFile(scope: !3681, file: !1, discriminator: 1)
!3685 = !DILocation(line: 975, column: 2, scope: !3686)
!3686 = !DILexicalBlockFile(scope: !3687, file: !1, discriminator: 2)
!3687 = distinct !DILexicalBlock(scope: !3681, file: !1, line: 975, column: 2)
!3688 = !DILocation(line: 975, column: 2, scope: !3689)
!3689 = !DILexicalBlockFile(scope: !3681, file: !1, discriminator: 3)
!3690 = !DILocation(line: 978, column: 6, scope: !3691)
!3691 = distinct !DILexicalBlock(scope: !379, file: !1, line: 978, column: 6)
!3692 = !DILocation(line: 978, column: 9, scope: !3691)
!3693 = !DILocation(line: 978, column: 17, scope: !3691)
!3694 = !DILocation(line: 978, column: 27, scope: !3691)
!3695 = !DILocation(line: 978, column: 6, scope: !379)
!3696 = !DILocation(line: 979, column: 22, scope: !3697)
!3697 = distinct !DILexicalBlock(scope: !3691, file: !1, line: 978, column: 36)
!3698 = !DILocation(line: 979, column: 25, scope: !3697)
!3699 = !DILocation(line: 979, column: 3, scope: !3697)
!3700 = !DILocation(line: 982, column: 3, scope: !3697)
!3701 = !DILocation(line: 985, column: 10, scope: !379)
!3702 = !DILocation(line: 985, column: 13, scope: !379)
!3703 = !DILocation(line: 985, column: 21, scope: !379)
!3704 = !DILocation(line: 985, column: 32, scope: !379)
!3705 = !DILocation(line: 985, column: 35, scope: !379)
!3706 = !DILocation(line: 985, column: 41, scope: !379)
!3707 = !DILocation(line: 985, column: 47, scope: !379)
!3708 = !DILocation(line: 985, column: 9, scope: !379)
!3709 = !DILocation(line: 985, column: 2, scope: !379)
!3710 = !DILocation(line: 986, column: 1, scope: !379)
!3711 = !DILocalVariable(name: "_a", arg: 1, scope: !380, file: !1, line: 681, type: !24)
!3712 = !DILocation(line: 681, column: 43, scope: !380)
!3713 = !DILocalVariable(name: "entryp", arg: 2, scope: !380, file: !1, line: 681, type: !58)
!3714 = !DILocation(line: 681, column: 70, scope: !380)
!3715 = !DILocalVariable(name: "ret", scope: !380, file: !1, line: 683, type: !23)
!3716 = !DILocation(line: 683, column: 6, scope: !380)
!3717 = !DILocalVariable(name: "a", scope: !380, file: !1, line: 684, type: !4)
!3718 = !DILocation(line: 684, column: 23, scope: !380)
!3719 = !DILocation(line: 684, column: 50, scope: !380)
!3720 = !DILocation(line: 684, column: 27, scope: !380)
!3721 = !DILocation(line: 685, column: 3, scope: !380)
!3722 = !DILocation(line: 685, column: 10, scope: !380)
!3723 = !DILocation(line: 686, column: 35, scope: !380)
!3724 = !DILocation(line: 686, column: 39, scope: !380)
!3725 = !DILocation(line: 686, column: 42, scope: !380)
!3726 = !DILocation(line: 686, column: 8, scope: !380)
!3727 = !DILocation(line: 686, column: 6, scope: !380)
!3728 = !DILocation(line: 687, column: 12, scope: !380)
!3729 = !DILocation(line: 687, column: 15, scope: !380)
!3730 = !DILocation(line: 687, column: 3, scope: !380)
!3731 = !DILocation(line: 687, column: 10, scope: !380)
!3732 = !DILocation(line: 688, column: 9, scope: !380)
!3733 = !DILocation(line: 688, column: 2, scope: !380)
!3734 = !DILocalVariable(name: "_a", arg: 1, scope: !381, file: !1, line: 617, type: !24)
!3735 = !DILocation(line: 617, column: 44, scope: !381)
!3736 = !DILocalVariable(name: "entry", arg: 2, scope: !381, file: !1, line: 617, type: !30)
!3737 = !DILocation(line: 617, column: 70, scope: !381)
!3738 = !DILocalVariable(name: "a", scope: !381, file: !1, line: 619, type: !4)
!3739 = !DILocation(line: 619, column: 23, scope: !381)
!3740 = !DILocation(line: 619, column: 50, scope: !381)
!3741 = !DILocation(line: 619, column: 27, scope: !381)
!3742 = !DILocalVariable(name: "r1", scope: !381, file: !1, line: 620, type: !23)
!3743 = !DILocation(line: 620, column: 6, scope: !381)
!3744 = !DILocalVariable(name: "r2", scope: !381, file: !1, line: 620, type: !23)
!3745 = !DILocation(line: 620, column: 23, scope: !381)
!3746 = !DILocation(line: 622, column: 2, scope: !381)
!3747 = !DILocalVariable(name: "magic_test", scope: !3748, file: !1, line: 622, type: !23)
!3748 = distinct !DILexicalBlock(scope: !381, file: !1, line: 622, column: 2)
!3749 = !DILocation(line: 622, column: 2, scope: !3748)
!3750 = !DILocation(line: 622, column: 2, scope: !3751)
!3751 = !DILexicalBlockFile(scope: !3748, file: !1, discriminator: 1)
!3752 = !DILocation(line: 622, column: 2, scope: !3753)
!3753 = !DILexicalBlockFile(scope: !3754, file: !1, discriminator: 2)
!3754 = distinct !DILexicalBlock(scope: !3748, file: !1, line: 622, column: 2)
!3755 = !DILocation(line: 622, column: 2, scope: !3756)
!3756 = !DILexicalBlockFile(scope: !3748, file: !1, discriminator: 3)
!3757 = !DILocation(line: 626, column: 22, scope: !381)
!3758 = !DILocation(line: 626, column: 2, scope: !381)
!3759 = !DILocation(line: 627, column: 23, scope: !381)
!3760 = !DILocation(line: 627, column: 26, scope: !381)
!3761 = !DILocation(line: 627, column: 2, scope: !381)
!3762 = !DILocation(line: 633, column: 6, scope: !3763)
!3763 = distinct !DILexicalBlock(scope: !381, file: !1, line: 633, column: 6)
!3764 = !DILocation(line: 633, column: 9, scope: !3763)
!3765 = !DILocation(line: 633, column: 17, scope: !3763)
!3766 = !DILocation(line: 633, column: 23, scope: !3763)
!3767 = !DILocation(line: 633, column: 6, scope: !381)
!3768 = !DILocation(line: 634, column: 32, scope: !3769)
!3769 = distinct !DILexicalBlock(scope: !3763, file: !1, line: 633, column: 46)
!3770 = !DILocation(line: 634, column: 35, scope: !3769)
!3771 = !DILocation(line: 634, column: 8, scope: !3769)
!3772 = !DILocation(line: 634, column: 6, scope: !3769)
!3773 = !DILocation(line: 635, column: 7, scope: !3774)
!3774 = distinct !DILexicalBlock(scope: !3769, file: !1, line: 635, column: 7)
!3775 = !DILocation(line: 635, column: 10, scope: !3774)
!3776 = !DILocation(line: 635, column: 7, scope: !3769)
!3777 = !DILocation(line: 636, column: 23, scope: !3774)
!3778 = !DILocation(line: 636, column: 26, scope: !3774)
!3779 = !DILocation(line: 636, column: 4, scope: !3774)
!3780 = !DILocation(line: 638, column: 7, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !3769, file: !1, line: 638, column: 7)
!3782 = !DILocation(line: 638, column: 10, scope: !3781)
!3783 = !DILocation(line: 638, column: 25, scope: !3781)
!3784 = !DILocation(line: 638, column: 28, scope: !3785)
!3785 = !DILexicalBlockFile(scope: !3781, file: !1, discriminator: 1)
!3786 = !DILocation(line: 638, column: 31, scope: !3785)
!3787 = !DILocation(line: 638, column: 7, scope: !3785)
!3788 = !DILocation(line: 639, column: 4, scope: !3789)
!3789 = distinct !DILexicalBlock(scope: !3781, file: !1, line: 638, column: 49)
!3790 = !DILocation(line: 639, column: 7, scope: !3789)
!3791 = !DILocation(line: 639, column: 15, scope: !3789)
!3792 = !DILocation(line: 639, column: 21, scope: !3789)
!3793 = !DILocation(line: 640, column: 4, scope: !3789)
!3794 = !DILocation(line: 642, column: 2, scope: !3769)
!3795 = !DILocation(line: 645, column: 23, scope: !381)
!3796 = !DILocation(line: 645, column: 26, scope: !381)
!3797 = !DILocation(line: 645, column: 34, scope: !381)
!3798 = !DILocation(line: 645, column: 2, scope: !381)
!3799 = !DILocation(line: 645, column: 5, scope: !381)
!3800 = !DILocation(line: 645, column: 21, scope: !381)
!3801 = !DILocation(line: 647, column: 4, scope: !381)
!3802 = !DILocation(line: 647, column: 8, scope: !381)
!3803 = !DILocation(line: 647, column: 2, scope: !381)
!3804 = !DILocation(line: 648, column: 8, scope: !381)
!3805 = !DILocation(line: 648, column: 11, scope: !381)
!3806 = !DILocation(line: 648, column: 19, scope: !381)
!3807 = !DILocation(line: 648, column: 32, scope: !381)
!3808 = !DILocation(line: 648, column: 35, scope: !381)
!3809 = !DILocation(line: 648, column: 7, scope: !381)
!3810 = !DILocation(line: 648, column: 5, scope: !381)
!3811 = !DILocation(line: 655, column: 10, scope: !381)
!3812 = !DILocation(line: 655, column: 2, scope: !381)
!3813 = !DILocation(line: 657, column: 3, scope: !3814)
!3814 = distinct !DILexicalBlock(scope: !381, file: !1, line: 655, column: 14)
!3815 = !DILocation(line: 657, column: 6, scope: !3814)
!3816 = !DILocation(line: 657, column: 14, scope: !3814)
!3817 = !DILocation(line: 657, column: 20, scope: !3814)
!3818 = !DILocation(line: 658, column: 5, scope: !3814)
!3819 = !DILocation(line: 658, column: 9, scope: !3814)
!3820 = !DILocation(line: 658, column: 3, scope: !3814)
!3821 = !DILocation(line: 659, column: 3, scope: !3814)
!3822 = !DILocation(line: 661, column: 3, scope: !3814)
!3823 = !DILocation(line: 661, column: 6, scope: !3814)
!3824 = !DILocation(line: 661, column: 14, scope: !3814)
!3825 = !DILocation(line: 661, column: 20, scope: !3814)
!3826 = !DILocation(line: 662, column: 3, scope: !3814)
!3827 = !DILocation(line: 664, column: 3, scope: !3814)
!3828 = !DILocation(line: 664, column: 6, scope: !3814)
!3829 = !DILocation(line: 664, column: 14, scope: !3814)
!3830 = !DILocation(line: 664, column: 20, scope: !3814)
!3831 = !DILocation(line: 665, column: 3, scope: !3814)
!3832 = !DILocation(line: 667, column: 3, scope: !3814)
!3833 = !DILocation(line: 669, column: 3, scope: !3814)
!3834 = !DILocation(line: 669, column: 6, scope: !3814)
!3835 = !DILocation(line: 669, column: 14, scope: !3814)
!3836 = !DILocation(line: 669, column: 20, scope: !3814)
!3837 = !DILocation(line: 670, column: 3, scope: !3814)
!3838 = !DILocation(line: 673, column: 29, scope: !381)
!3839 = !DILocation(line: 673, column: 32, scope: !381)
!3840 = !DILocation(line: 673, column: 2, scope: !381)
!3841 = !DILocation(line: 675, column: 23, scope: !381)
!3842 = !DILocation(line: 675, column: 26, scope: !381)
!3843 = !DILocation(line: 675, column: 33, scope: !381)
!3844 = !DILocation(line: 675, column: 2, scope: !381)
!3845 = !DILocation(line: 675, column: 5, scope: !381)
!3846 = !DILocation(line: 675, column: 21, scope: !381)
!3847 = !DILocation(line: 677, column: 10, scope: !381)
!3848 = !DILocation(line: 677, column: 15, scope: !381)
!3849 = !DILocation(line: 677, column: 13, scope: !381)
!3850 = !DILocation(line: 677, column: 18, scope: !381)
!3851 = !DILocation(line: 677, column: 21, scope: !3852)
!3852 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 1)
!3853 = !DILocation(line: 677, column: 24, scope: !3852)
!3854 = !DILocation(line: 677, column: 9, scope: !3852)
!3855 = !DILocation(line: 677, column: 42, scope: !3856)
!3856 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 2)
!3857 = !DILocation(line: 677, column: 9, scope: !3856)
!3858 = !DILocation(line: 677, column: 47, scope: !3859)
!3859 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 3)
!3860 = !DILocation(line: 677, column: 9, scope: !3859)
!3861 = !DILocation(line: 677, column: 9, scope: !3862)
!3862 = !DILexicalBlockFile(scope: !381, file: !1, discriminator: 4)
!3863 = !DILocation(line: 677, column: 2, scope: !3862)
!3864 = !DILocation(line: 678, column: 1, scope: !381)
!3865 = !DILocalVariable(name: "_a", arg: 1, scope: !382, file: !1, line: 1068, type: !24)
!3866 = !DILocation(line: 1068, column: 36, scope: !382)
!3867 = !DILocalVariable(name: "a", scope: !382, file: !1, line: 1070, type: !4)
!3868 = !DILocation(line: 1070, column: 23, scope: !382)
!3869 = !DILocation(line: 1070, column: 50, scope: !382)
!3870 = !DILocation(line: 1070, column: 27, scope: !382)
!3871 = !DILocalVariable(name: "p", scope: !382, file: !1, line: 1071, type: !277)
!3872 = !DILocation(line: 1071, column: 34, scope: !382)
!3873 = !DILocalVariable(name: "i", scope: !382, file: !1, line: 1072, type: !23)
!3874 = !DILocation(line: 1072, column: 6, scope: !382)
!3875 = !DILocalVariable(name: "n", scope: !382, file: !1, line: 1072, type: !23)
!3876 = !DILocation(line: 1072, column: 9, scope: !382)
!3877 = !DILocalVariable(name: "slots", scope: !382, file: !1, line: 1073, type: !23)
!3878 = !DILocation(line: 1073, column: 6, scope: !382)
!3879 = !DILocalVariable(name: "r", scope: !382, file: !1, line: 1074, type: !23)
!3880 = !DILocation(line: 1074, column: 6, scope: !382)
!3881 = !DILocation(line: 1076, column: 6, scope: !3882)
!3882 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1076, column: 6)
!3883 = !DILocation(line: 1076, column: 9, scope: !3882)
!3884 = !DILocation(line: 1076, column: 6, scope: !382)
!3885 = !DILocation(line: 1077, column: 3, scope: !3882)
!3886 = !DILocation(line: 1078, column: 2, scope: !382)
!3887 = !DILocalVariable(name: "magic_test", scope: !3888, file: !1, line: 1078, type: !23)
!3888 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1078, column: 2)
!3889 = !DILocation(line: 1078, column: 2, scope: !3888)
!3890 = !DILocation(line: 1078, column: 2, scope: !3891)
!3891 = !DILexicalBlockFile(scope: !3888, file: !1, discriminator: 1)
!3892 = !DILocation(line: 1078, column: 2, scope: !3893)
!3893 = !DILexicalBlockFile(scope: !3894, file: !1, discriminator: 2)
!3894 = distinct !DILexicalBlock(scope: !3888, file: !1, line: 1078, column: 2)
!3895 = !DILocation(line: 1078, column: 2, scope: !3896)
!3896 = !DILexicalBlockFile(scope: !3888, file: !1, discriminator: 3)
!3897 = !DILocation(line: 1080, column: 6, scope: !3898)
!3898 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1080, column: 6)
!3899 = !DILocation(line: 1080, column: 9, scope: !3898)
!3900 = !DILocation(line: 1080, column: 17, scope: !3898)
!3901 = !DILocation(line: 1080, column: 23, scope: !3898)
!3902 = !DILocation(line: 1081, column: 6, scope: !3898)
!3903 = !DILocation(line: 1081, column: 9, scope: !3904)
!3904 = !DILexicalBlockFile(scope: !3898, file: !1, discriminator: 1)
!3905 = !DILocation(line: 1081, column: 12, scope: !3904)
!3906 = !DILocation(line: 1081, column: 20, scope: !3904)
!3907 = !DILocation(line: 1081, column: 26, scope: !3904)
!3908 = !DILocation(line: 1080, column: 6, scope: !3909)
!3909 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 1)
!3910 = !DILocation(line: 1082, column: 27, scope: !3898)
!3911 = !DILocation(line: 1082, column: 30, scope: !3898)
!3912 = !DILocation(line: 1082, column: 7, scope: !3898)
!3913 = !DILocation(line: 1082, column: 5, scope: !3898)
!3914 = !DILocation(line: 1082, column: 3, scope: !3898)
!3915 = !DILocation(line: 1085, column: 6, scope: !3916)
!3916 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1085, column: 6)
!3917 = !DILocation(line: 1085, column: 9, scope: !3916)
!3918 = !DILocation(line: 1085, column: 33, scope: !3916)
!3919 = !DILocation(line: 1085, column: 6, scope: !382)
!3920 = !DILocation(line: 1086, column: 8, scope: !3916)
!3921 = !DILocation(line: 1086, column: 11, scope: !3916)
!3922 = !DILocation(line: 1086, column: 36, scope: !3916)
!3923 = !DILocation(line: 1086, column: 7, scope: !3916)
!3924 = !DILocation(line: 1086, column: 5, scope: !3916)
!3925 = !DILocation(line: 1086, column: 3, scope: !3916)
!3926 = !DILocation(line: 1089, column: 8, scope: !382)
!3927 = !DILocation(line: 1090, column: 9, scope: !3928)
!3928 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1090, column: 2)
!3929 = !DILocation(line: 1090, column: 7, scope: !3928)
!3930 = !DILocation(line: 1090, column: 14, scope: !3931)
!3931 = !DILexicalBlockFile(scope: !3932, file: !1, discriminator: 1)
!3932 = distinct !DILexicalBlock(scope: !3928, file: !1, line: 1090, column: 2)
!3933 = !DILocation(line: 1090, column: 18, scope: !3931)
!3934 = !DILocation(line: 1090, column: 16, scope: !3931)
!3935 = !DILocation(line: 1090, column: 2, scope: !3931)
!3936 = !DILocation(line: 1091, column: 28, scope: !3937)
!3937 = distinct !DILexicalBlock(scope: !3932, file: !1, line: 1090, column: 30)
!3938 = !DILocation(line: 1091, column: 17, scope: !3937)
!3939 = !DILocation(line: 1091, column: 20, scope: !3937)
!3940 = !DILocation(line: 1091, column: 3, scope: !3937)
!3941 = !DILocation(line: 1091, column: 6, scope: !3937)
!3942 = !DILocation(line: 1091, column: 13, scope: !3937)
!3943 = !DILocation(line: 1092, column: 18, scope: !3944)
!3944 = distinct !DILexicalBlock(scope: !3937, file: !1, line: 1092, column: 7)
!3945 = !DILocation(line: 1092, column: 7, scope: !3944)
!3946 = !DILocation(line: 1092, column: 10, scope: !3944)
!3947 = !DILocation(line: 1092, column: 21, scope: !3944)
!3948 = !DILocation(line: 1092, column: 7, scope: !3937)
!3949 = !DILocation(line: 1093, column: 16, scope: !3944)
!3950 = !DILocation(line: 1093, column: 5, scope: !3944)
!3951 = !DILocation(line: 1093, column: 8, scope: !3944)
!3952 = !DILocation(line: 1093, column: 19, scope: !3944)
!3953 = !DILocation(line: 1093, column: 28, scope: !3944)
!3954 = !DILocation(line: 1093, column: 4, scope: !3944)
!3955 = !DILocation(line: 1094, column: 2, scope: !3937)
!3956 = !DILocation(line: 1090, column: 26, scope: !3957)
!3957 = !DILexicalBlockFile(scope: !3932, file: !1, discriminator: 2)
!3958 = !DILocation(line: 1090, column: 2, scope: !3957)
!3959 = !DILocation(line: 1097, column: 30, scope: !382)
!3960 = !DILocation(line: 1097, column: 2, scope: !382)
!3961 = !DILocation(line: 1100, column: 4, scope: !382)
!3962 = !DILocation(line: 1101, column: 9, scope: !3963)
!3963 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1101, column: 2)
!3964 = !DILocation(line: 1101, column: 7, scope: !3963)
!3965 = !DILocation(line: 1101, column: 14, scope: !3966)
!3966 = !DILexicalBlockFile(scope: !3967, file: !1, discriminator: 1)
!3967 = distinct !DILexicalBlock(scope: !3963, file: !1, line: 1101, column: 2)
!3968 = !DILocation(line: 1101, column: 18, scope: !3966)
!3969 = !DILocation(line: 1101, column: 16, scope: !3966)
!3970 = !DILocation(line: 1101, column: 2, scope: !3966)
!3971 = !DILocation(line: 1102, column: 18, scope: !3972)
!3972 = distinct !DILexicalBlock(scope: !3973, file: !1, line: 1102, column: 7)
!3973 = distinct !DILexicalBlock(scope: !3967, file: !1, line: 1101, column: 26)
!3974 = !DILocation(line: 1102, column: 7, scope: !3972)
!3975 = !DILocation(line: 1102, column: 10, scope: !3972)
!3976 = !DILocation(line: 1102, column: 21, scope: !3972)
!3977 = !DILocation(line: 1102, column: 26, scope: !3972)
!3978 = !DILocation(line: 1102, column: 7, scope: !3973)
!3979 = !DILocalVariable(name: "r1", scope: !3980, file: !1, line: 1103, type: !23)
!3980 = distinct !DILexicalBlock(scope: !3972, file: !1, line: 1102, column: 35)
!3981 = !DILocation(line: 1103, column: 8, scope: !3980)
!3982 = !DILocation(line: 1103, column: 25, scope: !3980)
!3983 = !DILocation(line: 1103, column: 14, scope: !3980)
!3984 = !DILocation(line: 1103, column: 17, scope: !3980)
!3985 = !DILocation(line: 1103, column: 28, scope: !3980)
!3986 = !DILocation(line: 1103, column: 46, scope: !3980)
!3987 = !DILocation(line: 1103, column: 35, scope: !3980)
!3988 = !DILocation(line: 1103, column: 38, scope: !3980)
!3989 = !DILocation(line: 1103, column: 13, scope: !3980)
!3990 = !DILocation(line: 1104, column: 8, scope: !3991)
!3991 = distinct !DILexicalBlock(scope: !3980, file: !1, line: 1104, column: 8)
!3992 = !DILocation(line: 1104, column: 13, scope: !3991)
!3993 = !DILocation(line: 1104, column: 11, scope: !3991)
!3994 = !DILocation(line: 1104, column: 8, scope: !3980)
!3995 = !DILocation(line: 1105, column: 9, scope: !3991)
!3996 = !DILocation(line: 1105, column: 7, scope: !3991)
!3997 = !DILocation(line: 1105, column: 5, scope: !3991)
!3998 = !DILocation(line: 1106, column: 3, scope: !3980)
!3999 = !DILocation(line: 1107, column: 2, scope: !3973)
!4000 = !DILocation(line: 1101, column: 22, scope: !4001)
!4001 = !DILexicalBlockFile(scope: !3967, file: !1, discriminator: 2)
!4002 = !DILocation(line: 1101, column: 2, scope: !4001)
!4003 = !DILocation(line: 1110, column: 6, scope: !382)
!4004 = !DILocation(line: 1110, column: 9, scope: !382)
!4005 = !DILocation(line: 1110, column: 21, scope: !382)
!4006 = !DILocation(line: 1110, column: 4, scope: !382)
!4007 = !DILocation(line: 1111, column: 2, scope: !382)
!4008 = !DILocation(line: 1111, column: 9, scope: !3909)
!4009 = !DILocation(line: 1111, column: 11, scope: !3909)
!4010 = !DILocation(line: 1111, column: 2, scope: !3909)
!4011 = !DILocalVariable(name: "np", scope: !4012, file: !1, line: 1112, type: !277)
!4012 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1111, column: 20)
!4013 = !DILocation(line: 1112, column: 35, scope: !4012)
!4014 = !DILocation(line: 1112, column: 40, scope: !4012)
!4015 = !DILocation(line: 1112, column: 43, scope: !4012)
!4016 = !DILocation(line: 1115, column: 10, scope: !4012)
!4017 = !DILocation(line: 1115, column: 13, scope: !4012)
!4018 = !DILocation(line: 1115, column: 35, scope: !4012)
!4019 = !DILocation(line: 1115, column: 38, scope: !4012)
!4020 = !DILocation(line: 1115, column: 28, scope: !4012)
!4021 = !DILocation(line: 1115, column: 3, scope: !4022)
!4022 = !DILexicalBlockFile(scope: !4012, file: !1, discriminator: 1)
!4023 = !DILocation(line: 1116, column: 8, scope: !4012)
!4024 = !DILocation(line: 1116, column: 11, scope: !4012)
!4025 = !DILocation(line: 1116, column: 3, scope: !4012)
!4026 = !DILocation(line: 1117, column: 8, scope: !4012)
!4027 = !DILocation(line: 1117, column: 3, scope: !4012)
!4028 = !DILocation(line: 1118, column: 7, scope: !4012)
!4029 = !DILocation(line: 1118, column: 5, scope: !4012)
!4030 = !DILocation(line: 1111, column: 2, scope: !4031)
!4031 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 2)
!4032 = !DILocation(line: 1121, column: 23, scope: !382)
!4033 = !DILocation(line: 1121, column: 26, scope: !382)
!4034 = !DILocation(line: 1121, column: 34, scope: !382)
!4035 = !DILocation(line: 1121, column: 2, scope: !382)
!4036 = !DILocation(line: 1122, column: 21, scope: !382)
!4037 = !DILocation(line: 1122, column: 24, scope: !382)
!4038 = !DILocation(line: 1122, column: 2, scope: !382)
!4039 = !DILocation(line: 1123, column: 2, scope: !382)
!4040 = !DILocation(line: 1123, column: 5, scope: !382)
!4041 = !DILocation(line: 1123, column: 13, scope: !382)
!4042 = !DILocation(line: 1123, column: 19, scope: !382)
!4043 = !DILocation(line: 1124, column: 19, scope: !382)
!4044 = !DILocation(line: 1124, column: 22, scope: !382)
!4045 = !DILocation(line: 1124, column: 2, scope: !382)
!4046 = !DILocation(line: 1125, column: 7, scope: !382)
!4047 = !DILocation(line: 1125, column: 10, scope: !382)
!4048 = !DILocation(line: 1125, column: 17, scope: !382)
!4049 = !DILocation(line: 1125, column: 2, scope: !382)
!4050 = !DILocation(line: 1126, column: 7, scope: !382)
!4051 = !DILocation(line: 1126, column: 2, scope: !382)
!4052 = !DILocation(line: 1127, column: 10, scope: !382)
!4053 = !DILocation(line: 1127, column: 2, scope: !382)
!4054 = !DILocation(line: 1128, column: 1, scope: !382)
!4055 = !DILocalVariable(name: "_a", arg: 1, scope: !383, file: !1, line: 1042, type: !24)
!4056 = !DILocation(line: 1042, column: 37, scope: !383)
!4057 = !DILocalVariable(name: "a", scope: !383, file: !1, line: 1044, type: !4)
!4058 = !DILocation(line: 1044, column: 23, scope: !383)
!4059 = !DILocation(line: 1044, column: 50, scope: !383)
!4060 = !DILocation(line: 1044, column: 27, scope: !383)
!4061 = !DILocalVariable(name: "r", scope: !383, file: !1, line: 1045, type: !23)
!4062 = !DILocation(line: 1045, column: 6, scope: !383)
!4063 = !DILocalVariable(name: "r1", scope: !383, file: !1, line: 1045, type: !23)
!4064 = !DILocation(line: 1045, column: 22, scope: !383)
!4065 = !DILocation(line: 1047, column: 2, scope: !383)
!4066 = !DILocalVariable(name: "magic_test", scope: !4067, file: !1, line: 1047, type: !23)
!4067 = distinct !DILexicalBlock(scope: !383, file: !1, line: 1047, column: 2)
!4068 = !DILocation(line: 1047, column: 2, scope: !4067)
!4069 = !DILocation(line: 1047, column: 2, scope: !4070)
!4070 = !DILexicalBlockFile(scope: !4067, file: !1, discriminator: 1)
!4071 = !DILocation(line: 1047, column: 2, scope: !4072)
!4072 = !DILexicalBlockFile(scope: !4073, file: !1, discriminator: 2)
!4073 = distinct !DILexicalBlock(scope: !4067, file: !1, line: 1047, column: 2)
!4074 = !DILocation(line: 1047, column: 2, scope: !4075)
!4075 = !DILexicalBlockFile(scope: !4067, file: !1, discriminator: 3)
!4076 = !DILocation(line: 1049, column: 6, scope: !4077)
!4077 = distinct !DILexicalBlock(scope: !383, file: !1, line: 1049, column: 6)
!4078 = !DILocation(line: 1049, column: 9, scope: !4077)
!4079 = !DILocation(line: 1049, column: 17, scope: !4077)
!4080 = !DILocation(line: 1049, column: 23, scope: !4077)
!4081 = !DILocation(line: 1049, column: 6, scope: !383)
!4082 = !DILocation(line: 1050, column: 3, scope: !4077)
!4083 = !DILocation(line: 1051, column: 23, scope: !383)
!4084 = !DILocation(line: 1051, column: 26, scope: !383)
!4085 = !DILocation(line: 1051, column: 2, scope: !383)
!4086 = !DILocation(line: 1052, column: 2, scope: !383)
!4087 = !DILocation(line: 1052, column: 5, scope: !383)
!4088 = !DILocation(line: 1052, column: 13, scope: !383)
!4089 = !DILocation(line: 1052, column: 19, scope: !383)
!4090 = !DILocation(line: 1057, column: 21, scope: !383)
!4091 = !DILocation(line: 1057, column: 7, scope: !383)
!4092 = !DILocation(line: 1057, column: 5, scope: !383)
!4093 = !DILocation(line: 1058, column: 6, scope: !4094)
!4094 = distinct !DILexicalBlock(scope: !383, file: !1, line: 1058, column: 6)
!4095 = !DILocation(line: 1058, column: 11, scope: !4094)
!4096 = !DILocation(line: 1058, column: 9, scope: !4094)
!4097 = !DILocation(line: 1058, column: 6, scope: !383)
!4098 = !DILocation(line: 1059, column: 7, scope: !4094)
!4099 = !DILocation(line: 1059, column: 5, scope: !4094)
!4100 = !DILocation(line: 1059, column: 3, scope: !4094)
!4101 = !DILocation(line: 1061, column: 10, scope: !383)
!4102 = !DILocation(line: 1061, column: 2, scope: !383)
!4103 = !DILocation(line: 1062, column: 1, scope: !383)
!4104 = !DILocalVariable(name: "_a", arg: 1, scope: !373, file: !1, line: 1131, type: !24)
!4105 = !DILocation(line: 1131, column: 28, scope: !373)
!4106 = !DILocalVariable(name: "n", arg: 2, scope: !373, file: !1, line: 1131, type: !23)
!4107 = !DILocation(line: 1131, column: 36, scope: !373)
!4108 = !DILocalVariable(name: "a", scope: !373, file: !1, line: 1133, type: !4)
!4109 = !DILocation(line: 1133, column: 23, scope: !373)
!4110 = !DILocation(line: 1133, column: 50, scope: !373)
!4111 = !DILocation(line: 1133, column: 27, scope: !373)
!4112 = !DILocalVariable(name: "f", scope: !373, file: !1, line: 1134, type: !169)
!4113 = !DILocation(line: 1134, column: 30, scope: !373)
!4114 = !DILocation(line: 1134, column: 34, scope: !373)
!4115 = !DILocation(line: 1134, column: 37, scope: !373)
!4116 = !DILocation(line: 1137, column: 6, scope: !4117)
!4117 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1137, column: 6)
!4118 = !DILocation(line: 1137, column: 8, scope: !4117)
!4119 = !DILocation(line: 1137, column: 14, scope: !4117)
!4120 = !DILocation(line: 1137, column: 17, scope: !4121)
!4121 = !DILexicalBlockFile(scope: !4117, file: !1, discriminator: 1)
!4122 = !DILocation(line: 1137, column: 19, scope: !4121)
!4123 = !DILocation(line: 1137, column: 6, scope: !4121)
!4124 = !DILocalVariable(name: "last", scope: !4125, file: !1, line: 1138, type: !169)
!4125 = distinct !DILexicalBlock(scope: !4117, file: !1, line: 1137, column: 28)
!4126 = !DILocation(line: 1138, column: 31, scope: !4125)
!4127 = !DILocation(line: 1138, column: 38, scope: !4125)
!4128 = !DILocation(line: 1139, column: 7, scope: !4125)
!4129 = !DILocation(line: 1139, column: 10, scope: !4125)
!4130 = !DILocation(line: 1139, column: 5, scope: !4125)
!4131 = !DILocation(line: 1140, column: 3, scope: !4125)
!4132 = !DILocation(line: 1140, column: 10, scope: !4133)
!4133 = !DILexicalBlockFile(scope: !4125, file: !1, discriminator: 1)
!4134 = !DILocation(line: 1140, column: 12, scope: !4133)
!4135 = !DILocation(line: 1140, column: 3, scope: !4133)
!4136 = !DILocation(line: 1141, column: 11, scope: !4137)
!4137 = distinct !DILexicalBlock(scope: !4125, file: !1, line: 1140, column: 21)
!4138 = !DILocation(line: 1141, column: 9, scope: !4137)
!4139 = !DILocation(line: 1142, column: 8, scope: !4137)
!4140 = !DILocation(line: 1142, column: 11, scope: !4137)
!4141 = !DILocation(line: 1142, column: 6, scope: !4137)
!4142 = !DILocation(line: 1140, column: 3, scope: !4143)
!4143 = !DILexicalBlockFile(scope: !4125, file: !1, discriminator: 2)
!4144 = !DILocation(line: 1144, column: 11, scope: !4125)
!4145 = !DILocation(line: 1144, column: 3, scope: !4125)
!4146 = !DILocation(line: 1146, column: 6, scope: !4147)
!4147 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1146, column: 6)
!4148 = !DILocation(line: 1146, column: 8, scope: !4147)
!4149 = !DILocation(line: 1146, column: 6, scope: !373)
!4150 = !DILocation(line: 1147, column: 3, scope: !4147)
!4151 = !DILocation(line: 1148, column: 2, scope: !373)
!4152 = !DILocation(line: 1148, column: 9, scope: !4153)
!4153 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 1)
!4154 = !DILocation(line: 1148, column: 11, scope: !4153)
!4155 = !DILocation(line: 1148, column: 15, scope: !4153)
!4156 = !DILocation(line: 1148, column: 18, scope: !4157)
!4157 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 2)
!4158 = !DILocation(line: 1148, column: 20, scope: !4157)
!4159 = !DILocation(line: 1148, column: 2, scope: !4160)
!4160 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 3)
!4161 = !DILocation(line: 1149, column: 7, scope: !4162)
!4162 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1148, column: 29)
!4163 = !DILocation(line: 1149, column: 10, scope: !4162)
!4164 = !DILocation(line: 1149, column: 5, scope: !4162)
!4165 = !DILocation(line: 1150, column: 3, scope: !4162)
!4166 = !DILocation(line: 1148, column: 2, scope: !4167)
!4167 = !DILexicalBlockFile(scope: !373, file: !1, discriminator: 4)
!4168 = !DILocation(line: 1152, column: 10, scope: !373)
!4169 = !DILocation(line: 1152, column: 2, scope: !373)
!4170 = !DILocation(line: 1153, column: 1, scope: !373)
