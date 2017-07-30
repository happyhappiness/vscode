; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_raw.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.raw_info = type { i64, i64, i32 }
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }

@.str = private unnamed_addr constant [32 x i8] c"archive_read_support_format_raw\00", align 1
@.str.1 = private unnamed_addr constant [29 x i8] c"Can't allocate raw_info data\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"raw\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"data\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_raw(%struct.archive* %_a) #0 !dbg !301 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %info = alloca %struct.raw_info*, align 8
  %a = alloca %struct.archive_read*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !310, metadata !311), !dbg !312
  call void @llvm.dbg.declare(metadata %struct.raw_info** %info, metadata !313, metadata !311), !dbg !314
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !315, metadata !311), !dbg !316
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !317
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !318
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !316
  call void @llvm.dbg.declare(metadata i32* %r, metadata !319, metadata !311), !dbg !320
  br label %do.body, !dbg !321

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !322, metadata !311), !dbg !324
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !325
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str, i32 0, i32 0)), !dbg !325
  store i32 %call, i32* %magic_test, align 4, !dbg !325
  %3 = load i32, i32* %magic_test, align 4, !dbg !325
  %cmp = icmp eq i32 %3, -30, !dbg !325
  br i1 %cmp, label %if.then, label %if.end, !dbg !325

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !327
  br label %return, !dbg !327

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !330

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 24) #4, !dbg !332
  %4 = bitcast i8* %call1 to %struct.raw_info*, !dbg !333
  store %struct.raw_info* %4, %struct.raw_info** %info, align 8, !dbg !334
  %5 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !335
  %cmp2 = icmp eq %struct.raw_info* %5, null, !dbg !337
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !338

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !339
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !341
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.1, i32 0, i32 0)), !dbg !342
  store i32 -30, i32* %retval, align 4, !dbg !343
  br label %return, !dbg !343

if.end4:                                          ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !344
  %8 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !345
  %9 = bitcast %struct.raw_info* %8 to i8*, !dbg !345
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %7, i8* %9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @archive_read_format_raw_bid, i32 (%struct.archive_read*, i8*, i8*)* null, i32 (%struct.archive_read*, %struct.archive_entry*)* @archive_read_format_raw_read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @archive_read_format_raw_read_data, i32 (%struct.archive_read*)* @archive_read_format_raw_read_data_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @archive_read_format_raw_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !346
  store i32 %call5, i32* %r, align 4, !dbg !347
  %10 = load i32, i32* %r, align 4, !dbg !348
  %cmp6 = icmp ne i32 %10, 0, !dbg !350
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !351

if.then7:                                         ; preds = %if.end4
  %11 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !352
  %12 = bitcast %struct.raw_info* %11 to i8*, !dbg !352
  call void @free(i8* %12) #4, !dbg !353
  br label %if.end8, !dbg !353

if.end8:                                          ; preds = %if.then7, %if.end4
  %13 = load i32, i32* %r, align 4, !dbg !354
  store i32 %13, i32* %retval, align 4, !dbg !355
  br label %return, !dbg !355

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !356
  ret i32 %14, !dbg !356
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_raw_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !302 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !357, metadata !311), !dbg !358
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !359, metadata !311), !dbg !360
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !361
  %cmp = icmp slt i32 %0, 1, !dbg !363
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !364

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !365
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 1, i64* null), !dbg !367
  %cmp1 = icmp ne i8* %call, null, !dbg !368
  br i1 %cmp1, label %if.then, label %if.end, !dbg !369

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* %retval, align 4, !dbg !370
  br label %return, !dbg !370

if.end:                                           ; preds = %land.lhs.true, %entry
  store i32 -1, i32* %retval, align 4, !dbg !371
  br label %return, !dbg !371

return:                                           ; preds = %if.end, %if.then
  %2 = load i32, i32* %retval, align 4, !dbg !372
  ret i32 %2, !dbg !372
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_raw_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !303 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %info = alloca %struct.raw_info*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !373, metadata !311), !dbg !374
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !375, metadata !311), !dbg !376
  call void @llvm.dbg.declare(metadata %struct.raw_info** %info, metadata !377, metadata !311), !dbg !378
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !379
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !380
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !380
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !381
  %2 = load i8*, i8** %data, align 8, !dbg !381
  %3 = bitcast i8* %2 to %struct.raw_info*, !dbg !382
  store %struct.raw_info* %3, %struct.raw_info** %info, align 8, !dbg !383
  %4 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !384
  %end_of_file = getelementptr inbounds %struct.raw_info, %struct.raw_info* %4, i32 0, i32 2, !dbg !386
  %5 = load i32, i32* %end_of_file, align 8, !dbg !386
  %tobool = icmp ne i32 %5, 0, !dbg !384
  br i1 %tobool, label %if.then, label %if.end, !dbg !387

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !388
  br label %return, !dbg !388

if.end:                                           ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !389
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !390
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !391
  store i32 589824, i32* %archive_format, align 8, !dbg !392
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !393
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !394
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !395
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !396
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !397
  call void @archive_entry_set_pathname(%struct.archive_entry* %8, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0)), !dbg !398
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !399
  call void @archive_entry_set_filetype(%struct.archive_entry* %9, i32 32768), !dbg !400
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !401
  call void @archive_entry_set_perm(%struct.archive_entry* %10, i32 420), !dbg !402
  store i32 0, i32* %retval, align 4, !dbg !403
  br label %return, !dbg !403

return:                                           ; preds = %if.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !404
  ret i32 %11, !dbg !404
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_raw_read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !304 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %info = alloca %struct.raw_info*, align 8
  %avail = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !405, metadata !311), !dbg !406
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !407, metadata !311), !dbg !408
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !409, metadata !311), !dbg !410
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !411, metadata !311), !dbg !412
  call void @llvm.dbg.declare(metadata %struct.raw_info** %info, metadata !413, metadata !311), !dbg !414
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !415, metadata !311), !dbg !416
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !417
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !418
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !418
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !419
  %2 = load i8*, i8** %data, align 8, !dbg !419
  %3 = bitcast i8* %2 to %struct.raw_info*, !dbg !420
  store %struct.raw_info* %3, %struct.raw_info** %info, align 8, !dbg !421
  %4 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !422
  %unconsumed = getelementptr inbounds %struct.raw_info, %struct.raw_info* %4, i32 0, i32 1, !dbg !424
  %5 = load i64, i64* %unconsumed, align 8, !dbg !424
  %tobool = icmp ne i64 %5, 0, !dbg !422
  br i1 %tobool, label %if.then, label %if.end, !dbg !425

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !426
  %7 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !428
  %unconsumed1 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %7, i32 0, i32 1, !dbg !429
  %8 = load i64, i64* %unconsumed1, align 8, !dbg !429
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !430
  %9 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !431
  %unconsumed2 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %9, i32 0, i32 1, !dbg !432
  store i64 0, i64* %unconsumed2, align 8, !dbg !433
  br label %if.end, !dbg !434

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !435
  %end_of_file = getelementptr inbounds %struct.raw_info, %struct.raw_info* %10, i32 0, i32 2, !dbg !437
  %11 = load i32, i32* %end_of_file, align 8, !dbg !437
  %tobool3 = icmp ne i32 %11, 0, !dbg !435
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !438

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !439
  br label %return, !dbg !439

if.end5:                                          ; preds = %if.end
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !440
  %call6 = call i8* @__archive_read_ahead(%struct.archive_read* %12, i64 1, i64* %avail), !dbg !441
  %13 = load i8**, i8*** %buff.addr, align 8, !dbg !442
  store i8* %call6, i8** %13, align 8, !dbg !443
  %14 = load i64, i64* %avail, align 8, !dbg !444
  %cmp = icmp sgt i64 %14, 0, !dbg !446
  br i1 %cmp, label %if.then7, label %if.else, !dbg !447

if.then7:                                         ; preds = %if.end5
  %15 = load i64, i64* %avail, align 8, !dbg !448
  %16 = load i64*, i64** %size.addr, align 8, !dbg !450
  store i64 %15, i64* %16, align 8, !dbg !451
  %17 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !452
  %offset8 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %17, i32 0, i32 0, !dbg !453
  %18 = load i64, i64* %offset8, align 8, !dbg !453
  %19 = load i64*, i64** %offset.addr, align 8, !dbg !454
  store i64 %18, i64* %19, align 8, !dbg !455
  %20 = load i64*, i64** %size.addr, align 8, !dbg !456
  %21 = load i64, i64* %20, align 8, !dbg !457
  %22 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !458
  %offset9 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %22, i32 0, i32 0, !dbg !459
  %23 = load i64, i64* %offset9, align 8, !dbg !460
  %add = add i64 %23, %21, !dbg !460
  store i64 %add, i64* %offset9, align 8, !dbg !460
  %24 = load i64, i64* %avail, align 8, !dbg !461
  %25 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !462
  %unconsumed10 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %25, i32 0, i32 1, !dbg !463
  store i64 %24, i64* %unconsumed10, align 8, !dbg !464
  store i32 0, i32* %retval, align 4, !dbg !465
  br label %return, !dbg !465

if.else:                                          ; preds = %if.end5
  %26 = load i64, i64* %avail, align 8, !dbg !466
  %cmp11 = icmp eq i64 0, %26, !dbg !468
  br i1 %cmp11, label %if.then12, label %if.else15, !dbg !469

if.then12:                                        ; preds = %if.else
  %27 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !470
  %end_of_file13 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %27, i32 0, i32 2, !dbg !472
  store i32 1, i32* %end_of_file13, align 8, !dbg !473
  %28 = load i64*, i64** %size.addr, align 8, !dbg !474
  store i64 0, i64* %28, align 8, !dbg !475
  %29 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !476
  %offset14 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %29, i32 0, i32 0, !dbg !477
  %30 = load i64, i64* %offset14, align 8, !dbg !477
  %31 = load i64*, i64** %offset.addr, align 8, !dbg !478
  store i64 %30, i64* %31, align 8, !dbg !479
  store i32 1, i32* %retval, align 4, !dbg !480
  br label %return, !dbg !480

if.else15:                                        ; preds = %if.else
  %32 = load i64*, i64** %size.addr, align 8, !dbg !481
  store i64 0, i64* %32, align 8, !dbg !483
  %33 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !484
  %offset16 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %33, i32 0, i32 0, !dbg !485
  %34 = load i64, i64* %offset16, align 8, !dbg !485
  %35 = load i64*, i64** %offset.addr, align 8, !dbg !486
  store i64 %34, i64* %35, align 8, !dbg !487
  %36 = load i64, i64* %avail, align 8, !dbg !488
  %conv = trunc i64 %36 to i32, !dbg !489
  store i32 %conv, i32* %retval, align 4, !dbg !490
  br label %return, !dbg !490

return:                                           ; preds = %if.else15, %if.then12, %if.then7, %if.then4
  %37 = load i32, i32* %retval, align 4, !dbg !491
  ret i32 %37, !dbg !491
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_raw_read_data_skip(%struct.archive_read* %a) #0 !dbg !305 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %info = alloca %struct.raw_info*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !492, metadata !311), !dbg !493
  call void @llvm.dbg.declare(metadata %struct.raw_info** %info, metadata !494, metadata !311), !dbg !495
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !496
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !497
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !497
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !498
  %2 = load i8*, i8** %data, align 8, !dbg !498
  %3 = bitcast i8* %2 to %struct.raw_info*, !dbg !499
  store %struct.raw_info* %3, %struct.raw_info** %info, align 8, !dbg !495
  %4 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !500
  %unconsumed = getelementptr inbounds %struct.raw_info, %struct.raw_info* %4, i32 0, i32 1, !dbg !502
  %5 = load i64, i64* %unconsumed, align 8, !dbg !502
  %tobool = icmp ne i64 %5, 0, !dbg !500
  br i1 %tobool, label %if.then, label %if.end, !dbg !503

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !504
  %7 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !506
  %unconsumed1 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %7, i32 0, i32 1, !dbg !507
  %8 = load i64, i64* %unconsumed1, align 8, !dbg !507
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !508
  %9 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !509
  %unconsumed2 = getelementptr inbounds %struct.raw_info, %struct.raw_info* %9, i32 0, i32 1, !dbg !510
  store i64 0, i64* %unconsumed2, align 8, !dbg !511
  br label %if.end, !dbg !512

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !513
  %end_of_file = getelementptr inbounds %struct.raw_info, %struct.raw_info* %10, i32 0, i32 2, !dbg !514
  store i32 1, i32* %end_of_file, align 8, !dbg !515
  ret i32 0, !dbg !516
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_raw_cleanup(%struct.archive_read* %a) #0 !dbg !306 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %info = alloca %struct.raw_info*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !517, metadata !311), !dbg !518
  call void @llvm.dbg.declare(metadata %struct.raw_info** %info, metadata !519, metadata !311), !dbg !520
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !521
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !522
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !522
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !523
  %2 = load i8*, i8** %data, align 8, !dbg !523
  %3 = bitcast i8* %2 to %struct.raw_info*, !dbg !524
  store %struct.raw_info* %3, %struct.raw_info** %info, align 8, !dbg !525
  %4 = load %struct.raw_info*, %struct.raw_info** %info, align 8, !dbg !526
  %5 = bitcast %struct.raw_info* %4 to i8*, !dbg !526
  call void @free(i8* %5) #4, !dbg !527
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !528
  %format1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 13, !dbg !529
  %7 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format1, align 8, !dbg !529
  %data2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %7, i32 0, i32 0, !dbg !530
  store i8* null, i8** %data2, align 8, !dbg !531
  ret i32 0, !dbg !532
}

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

declare void @archive_entry_set_pathname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_perm(%struct.archive_entry*, i32) #2

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!307, !308}
!llvm.ident = !{!309}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !300)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_raw.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !291, !122, !297, !23}
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
!291 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !292, size: 64, align: 64)
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "raw_info", file: !1, line: 41, size: 192, align: 64, elements: !293)
!293 = !{!294, !295, !296}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !292, file: !1, line: 42, baseType: !52, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "unconsumed", scope: !292, file: !1, line: 43, baseType: !52, size: 64, align: 64, offset: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !292, file: !1, line: 44, baseType: !23, size: 32, align: 32, offset: 128)
!297 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !298, line: 70, baseType: !299)
!298 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!299 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!300 = !{!301, !302, !303, !304, !305, !306}
!301 = distinct !DISubprogram(name: "archive_read_support_format_raw", scope: !1, file: !1, line: 56, type: !21, isLocal: false, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = distinct !DISubprogram(name: "archive_read_format_raw_bid", scope: !1, file: !1, line: 97, type: !235, isLocal: true, isDefinition: true, scopeLine: 98, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!303 = distinct !DISubprogram(name: "archive_read_format_raw_read_header", scope: !1, file: !1, line: 108, type: !243, isLocal: true, isDefinition: true, scopeLine: 110, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!304 = distinct !DISubprogram(name: "archive_read_format_raw_read_data", scope: !1, file: !1, line: 127, type: !247, isLocal: true, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!305 = distinct !DISubprogram(name: "archive_read_format_raw_read_data_skip", scope: !1, file: !1, line: 168, type: !251, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!306 = distinct !DISubprogram(name: "archive_read_format_raw_cleanup", scope: !1, file: !1, line: 182, type: !251, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!307 = !{i32 2, !"Dwarf Version", i32 4}
!308 = !{i32 2, !"Debug Info Version", i32 3}
!309 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!310 = !DILocalVariable(name: "_a", arg: 1, scope: !301, file: !1, line: 56, type: !24)
!311 = !DIExpression()
!312 = !DILocation(line: 56, column: 49, scope: !301)
!313 = !DILocalVariable(name: "info", scope: !301, file: !1, line: 58, type: !291)
!314 = !DILocation(line: 58, column: 19, scope: !301)
!315 = !DILocalVariable(name: "a", scope: !301, file: !1, line: 59, type: !4)
!316 = !DILocation(line: 59, column: 23, scope: !301)
!317 = !DILocation(line: 59, column: 50, scope: !301)
!318 = !DILocation(line: 59, column: 27, scope: !301)
!319 = !DILocalVariable(name: "r", scope: !301, file: !1, line: 60, type: !23)
!320 = !DILocation(line: 60, column: 6, scope: !301)
!321 = !DILocation(line: 62, column: 2, scope: !301)
!322 = !DILocalVariable(name: "magic_test", scope: !323, file: !1, line: 62, type: !23)
!323 = distinct !DILexicalBlock(scope: !301, file: !1, line: 62, column: 2)
!324 = !DILocation(line: 62, column: 2, scope: !323)
!325 = !DILocation(line: 62, column: 2, scope: !326)
!326 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 1)
!327 = !DILocation(line: 62, column: 2, scope: !328)
!328 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 2)
!329 = distinct !DILexicalBlock(scope: !323, file: !1, line: 62, column: 2)
!330 = !DILocation(line: 62, column: 2, scope: !331)
!331 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 3)
!332 = !DILocation(line: 65, column: 28, scope: !301)
!333 = !DILocation(line: 65, column: 9, scope: !301)
!334 = !DILocation(line: 65, column: 7, scope: !301)
!335 = !DILocation(line: 66, column: 6, scope: !336)
!336 = distinct !DILexicalBlock(scope: !301, file: !1, line: 66, column: 6)
!337 = !DILocation(line: 66, column: 11, scope: !336)
!338 = !DILocation(line: 66, column: 6, scope: !301)
!339 = !DILocation(line: 67, column: 22, scope: !340)
!340 = distinct !DILexicalBlock(scope: !336, file: !1, line: 66, column: 20)
!341 = !DILocation(line: 67, column: 25, scope: !340)
!342 = !DILocation(line: 67, column: 3, scope: !340)
!343 = !DILocation(line: 69, column: 3, scope: !340)
!344 = !DILocation(line: 72, column: 37, scope: !301)
!345 = !DILocation(line: 73, column: 6, scope: !301)
!346 = !DILocation(line: 72, column: 6, scope: !301)
!347 = !DILocation(line: 72, column: 4, scope: !301)
!348 = !DILocation(line: 84, column: 6, scope: !349)
!349 = distinct !DILexicalBlock(scope: !301, file: !1, line: 84, column: 6)
!350 = !DILocation(line: 84, column: 8, scope: !349)
!351 = !DILocation(line: 84, column: 6, scope: !301)
!352 = !DILocation(line: 85, column: 8, scope: !349)
!353 = !DILocation(line: 85, column: 3, scope: !349)
!354 = !DILocation(line: 86, column: 10, scope: !301)
!355 = !DILocation(line: 86, column: 2, scope: !301)
!356 = !DILocation(line: 87, column: 1, scope: !301)
!357 = !DILocalVariable(name: "a", arg: 1, scope: !302, file: !1, line: 97, type: !4)
!358 = !DILocation(line: 97, column: 50, scope: !302)
!359 = !DILocalVariable(name: "best_bid", arg: 2, scope: !302, file: !1, line: 97, type: !23)
!360 = !DILocation(line: 97, column: 57, scope: !302)
!361 = !DILocation(line: 99, column: 6, scope: !362)
!362 = distinct !DILexicalBlock(scope: !302, file: !1, line: 99, column: 6)
!363 = !DILocation(line: 99, column: 15, scope: !362)
!364 = !DILocation(line: 99, column: 19, scope: !362)
!365 = !DILocation(line: 99, column: 43, scope: !366)
!366 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 1)
!367 = !DILocation(line: 99, column: 22, scope: !366)
!368 = !DILocation(line: 99, column: 55, scope: !366)
!369 = !DILocation(line: 99, column: 6, scope: !366)
!370 = !DILocation(line: 100, column: 3, scope: !362)
!371 = !DILocation(line: 101, column: 2, scope: !302)
!372 = !DILocation(line: 102, column: 1, scope: !302)
!373 = !DILocalVariable(name: "a", arg: 1, scope: !303, file: !1, line: 108, type: !4)
!374 = !DILocation(line: 108, column: 58, scope: !303)
!375 = !DILocalVariable(name: "entry", arg: 2, scope: !303, file: !1, line: 109, type: !30)
!376 = !DILocation(line: 109, column: 27, scope: !303)
!377 = !DILocalVariable(name: "info", scope: !303, file: !1, line: 111, type: !291)
!378 = !DILocation(line: 111, column: 19, scope: !303)
!379 = !DILocation(line: 113, column: 29, scope: !303)
!380 = !DILocation(line: 113, column: 32, scope: !303)
!381 = !DILocation(line: 113, column: 40, scope: !303)
!382 = !DILocation(line: 113, column: 9, scope: !303)
!383 = !DILocation(line: 113, column: 7, scope: !303)
!384 = !DILocation(line: 114, column: 6, scope: !385)
!385 = distinct !DILexicalBlock(scope: !303, file: !1, line: 114, column: 6)
!386 = !DILocation(line: 114, column: 12, scope: !385)
!387 = !DILocation(line: 114, column: 6, scope: !303)
!388 = !DILocation(line: 115, column: 3, scope: !385)
!389 = !DILocation(line: 117, column: 2, scope: !303)
!390 = !DILocation(line: 117, column: 5, scope: !303)
!391 = !DILocation(line: 117, column: 13, scope: !303)
!392 = !DILocation(line: 117, column: 28, scope: !303)
!393 = !DILocation(line: 118, column: 2, scope: !303)
!394 = !DILocation(line: 118, column: 5, scope: !303)
!395 = !DILocation(line: 118, column: 13, scope: !303)
!396 = !DILocation(line: 118, column: 33, scope: !303)
!397 = !DILocation(line: 119, column: 29, scope: !303)
!398 = !DILocation(line: 119, column: 2, scope: !303)
!399 = !DILocation(line: 120, column: 29, scope: !303)
!400 = !DILocation(line: 120, column: 2, scope: !303)
!401 = !DILocation(line: 121, column: 25, scope: !303)
!402 = !DILocation(line: 121, column: 2, scope: !303)
!403 = !DILocation(line: 123, column: 2, scope: !303)
!404 = !DILocation(line: 124, column: 1, scope: !303)
!405 = !DILocalVariable(name: "a", arg: 1, scope: !304, file: !1, line: 127, type: !4)
!406 = !DILocation(line: 127, column: 56, scope: !304)
!407 = !DILocalVariable(name: "buff", arg: 2, scope: !304, file: !1, line: 128, type: !64)
!408 = !DILocation(line: 128, column: 18, scope: !304)
!409 = !DILocalVariable(name: "size", arg: 3, scope: !304, file: !1, line: 128, type: !65)
!410 = !DILocation(line: 128, column: 32, scope: !304)
!411 = !DILocalVariable(name: "offset", arg: 4, scope: !304, file: !1, line: 128, type: !66)
!412 = !DILocation(line: 128, column: 47, scope: !304)
!413 = !DILocalVariable(name: "info", scope: !304, file: !1, line: 130, type: !291)
!414 = !DILocation(line: 130, column: 19, scope: !304)
!415 = !DILocalVariable(name: "avail", scope: !304, file: !1, line: 131, type: !38)
!416 = !DILocation(line: 131, column: 10, scope: !304)
!417 = !DILocation(line: 133, column: 29, scope: !304)
!418 = !DILocation(line: 133, column: 32, scope: !304)
!419 = !DILocation(line: 133, column: 40, scope: !304)
!420 = !DILocation(line: 133, column: 9, scope: !304)
!421 = !DILocation(line: 133, column: 7, scope: !304)
!422 = !DILocation(line: 136, column: 6, scope: !423)
!423 = distinct !DILexicalBlock(scope: !304, file: !1, line: 136, column: 6)
!424 = !DILocation(line: 136, column: 12, scope: !423)
!425 = !DILocation(line: 136, column: 6, scope: !304)
!426 = !DILocation(line: 137, column: 26, scope: !427)
!427 = distinct !DILexicalBlock(scope: !423, file: !1, line: 136, column: 24)
!428 = !DILocation(line: 137, column: 29, scope: !427)
!429 = !DILocation(line: 137, column: 35, scope: !427)
!430 = !DILocation(line: 137, column: 3, scope: !427)
!431 = !DILocation(line: 138, column: 3, scope: !427)
!432 = !DILocation(line: 138, column: 9, scope: !427)
!433 = !DILocation(line: 138, column: 20, scope: !427)
!434 = !DILocation(line: 139, column: 2, scope: !427)
!435 = !DILocation(line: 141, column: 6, scope: !436)
!436 = distinct !DILexicalBlock(scope: !304, file: !1, line: 141, column: 6)
!437 = !DILocation(line: 141, column: 12, scope: !436)
!438 = !DILocation(line: 141, column: 6, scope: !304)
!439 = !DILocation(line: 142, column: 3, scope: !436)
!440 = !DILocation(line: 145, column: 31, scope: !304)
!441 = !DILocation(line: 145, column: 10, scope: !304)
!442 = !DILocation(line: 145, column: 3, scope: !304)
!443 = !DILocation(line: 145, column: 8, scope: !304)
!444 = !DILocation(line: 146, column: 6, scope: !445)
!445 = distinct !DILexicalBlock(scope: !304, file: !1, line: 146, column: 6)
!446 = !DILocation(line: 146, column: 12, scope: !445)
!447 = !DILocation(line: 146, column: 6, scope: !304)
!448 = !DILocation(line: 148, column: 11, scope: !449)
!449 = distinct !DILexicalBlock(scope: !445, file: !1, line: 146, column: 17)
!450 = !DILocation(line: 148, column: 4, scope: !449)
!451 = !DILocation(line: 148, column: 9, scope: !449)
!452 = !DILocation(line: 149, column: 13, scope: !449)
!453 = !DILocation(line: 149, column: 19, scope: !449)
!454 = !DILocation(line: 149, column: 4, scope: !449)
!455 = !DILocation(line: 149, column: 11, scope: !449)
!456 = !DILocation(line: 150, column: 20, scope: !449)
!457 = !DILocation(line: 150, column: 19, scope: !449)
!458 = !DILocation(line: 150, column: 3, scope: !449)
!459 = !DILocation(line: 150, column: 9, scope: !449)
!460 = !DILocation(line: 150, column: 16, scope: !449)
!461 = !DILocation(line: 151, column: 22, scope: !449)
!462 = !DILocation(line: 151, column: 3, scope: !449)
!463 = !DILocation(line: 151, column: 9, scope: !449)
!464 = !DILocation(line: 151, column: 20, scope: !449)
!465 = !DILocation(line: 152, column: 3, scope: !449)
!466 = !DILocation(line: 153, column: 18, scope: !467)
!467 = distinct !DILexicalBlock(scope: !445, file: !1, line: 153, column: 13)
!468 = !DILocation(line: 153, column: 15, scope: !467)
!469 = !DILocation(line: 153, column: 13, scope: !445)
!470 = !DILocation(line: 155, column: 3, scope: !471)
!471 = distinct !DILexicalBlock(scope: !467, file: !1, line: 153, column: 25)
!472 = !DILocation(line: 155, column: 9, scope: !471)
!473 = !DILocation(line: 155, column: 21, scope: !471)
!474 = !DILocation(line: 156, column: 4, scope: !471)
!475 = !DILocation(line: 156, column: 9, scope: !471)
!476 = !DILocation(line: 157, column: 13, scope: !471)
!477 = !DILocation(line: 157, column: 19, scope: !471)
!478 = !DILocation(line: 157, column: 4, scope: !471)
!479 = !DILocation(line: 157, column: 11, scope: !471)
!480 = !DILocation(line: 158, column: 3, scope: !471)
!481 = !DILocation(line: 161, column: 4, scope: !482)
!482 = distinct !DILexicalBlock(scope: !467, file: !1, line: 159, column: 9)
!483 = !DILocation(line: 161, column: 9, scope: !482)
!484 = !DILocation(line: 162, column: 13, scope: !482)
!485 = !DILocation(line: 162, column: 19, scope: !482)
!486 = !DILocation(line: 162, column: 4, scope: !482)
!487 = !DILocation(line: 162, column: 11, scope: !482)
!488 = !DILocation(line: 163, column: 16, scope: !482)
!489 = !DILocation(line: 163, column: 11, scope: !482)
!490 = !DILocation(line: 163, column: 3, scope: !482)
!491 = !DILocation(line: 165, column: 1, scope: !304)
!492 = !DILocalVariable(name: "a", arg: 1, scope: !305, file: !1, line: 168, type: !4)
!493 = !DILocation(line: 168, column: 61, scope: !305)
!494 = !DILocalVariable(name: "info", scope: !305, file: !1, line: 170, type: !291)
!495 = !DILocation(line: 170, column: 19, scope: !305)
!496 = !DILocation(line: 170, column: 46, scope: !305)
!497 = !DILocation(line: 170, column: 49, scope: !305)
!498 = !DILocation(line: 170, column: 57, scope: !305)
!499 = !DILocation(line: 170, column: 26, scope: !305)
!500 = !DILocation(line: 173, column: 6, scope: !501)
!501 = distinct !DILexicalBlock(scope: !305, file: !1, line: 173, column: 6)
!502 = !DILocation(line: 173, column: 12, scope: !501)
!503 = !DILocation(line: 173, column: 6, scope: !305)
!504 = !DILocation(line: 174, column: 26, scope: !505)
!505 = distinct !DILexicalBlock(scope: !501, file: !1, line: 173, column: 24)
!506 = !DILocation(line: 174, column: 29, scope: !505)
!507 = !DILocation(line: 174, column: 35, scope: !505)
!508 = !DILocation(line: 174, column: 3, scope: !505)
!509 = !DILocation(line: 175, column: 3, scope: !505)
!510 = !DILocation(line: 175, column: 9, scope: !505)
!511 = !DILocation(line: 175, column: 20, scope: !505)
!512 = !DILocation(line: 176, column: 2, scope: !505)
!513 = !DILocation(line: 177, column: 2, scope: !305)
!514 = !DILocation(line: 177, column: 8, scope: !305)
!515 = !DILocation(line: 177, column: 20, scope: !305)
!516 = !DILocation(line: 178, column: 2, scope: !305)
!517 = !DILocalVariable(name: "a", arg: 1, scope: !306, file: !1, line: 182, type: !4)
!518 = !DILocation(line: 182, column: 54, scope: !306)
!519 = !DILocalVariable(name: "info", scope: !306, file: !1, line: 184, type: !291)
!520 = !DILocation(line: 184, column: 19, scope: !306)
!521 = !DILocation(line: 186, column: 29, scope: !306)
!522 = !DILocation(line: 186, column: 32, scope: !306)
!523 = !DILocation(line: 186, column: 40, scope: !306)
!524 = !DILocation(line: 186, column: 9, scope: !306)
!525 = !DILocation(line: 186, column: 7, scope: !306)
!526 = !DILocation(line: 187, column: 7, scope: !306)
!527 = !DILocation(line: 187, column: 2, scope: !306)
!528 = !DILocation(line: 188, column: 2, scope: !306)
!529 = !DILocation(line: 188, column: 5, scope: !306)
!530 = !DILocation(line: 188, column: 13, scope: !306)
!531 = !DILocation(line: 188, column: 18, scope: !306)
!532 = !DILocation(line: 189, column: 2, scope: !306)
