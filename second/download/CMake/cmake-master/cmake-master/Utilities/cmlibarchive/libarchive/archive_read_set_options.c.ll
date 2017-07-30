; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_set_options.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }

@.str = private unnamed_addr constant [31 x i8] c"archive_read_set_format_option\00", align 1
@.str.1 = private unnamed_addr constant [31 x i8] c"archive_read_set_filter_option\00", align 1
@.str.2 = private unnamed_addr constant [24 x i8] c"archive_read_set_option\00", align 1
@.str.3 = private unnamed_addr constant [25 x i8] c"archive_read_set_options\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_format_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !292 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !306, metadata !307), !dbg !308
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !309, metadata !307), !dbg !310
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !311, metadata !307), !dbg !312
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !313, metadata !307), !dbg !314
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !315
  %1 = load i8*, i8** %m.addr, align 8, !dbg !316
  %2 = load i8*, i8** %o.addr, align 8, !dbg !317
  %3 = load i8*, i8** %v.addr, align 8, !dbg !318
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 14594245, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_format_option), !dbg !319
  ret i32 %call, !dbg !320
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @_archive_set_option(%struct.archive*, i8*, i8*, i8*, i32, i8*, i32 (%struct.archive*, i8*, i8*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_format_option(%struct.archive* %_a, i8* %m, i8* %o, i8* %v) #0 !dbg !300 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read*, align 8
  %i = alloca i64, align 8
  %r = alloca i32, align 4
  %rv = alloca i32, align 4
  %matched_modules = alloca i32, align 4
  %format = alloca %struct.archive_format_descriptor*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !321, metadata !307), !dbg !322
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !323, metadata !307), !dbg !324
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !325, metadata !307), !dbg !326
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !327, metadata !307), !dbg !328
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !329, metadata !307), !dbg !330
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !331
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !332
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !330
  call void @llvm.dbg.declare(metadata i64* %i, metadata !333, metadata !307), !dbg !334
  call void @llvm.dbg.declare(metadata i32* %r, metadata !335, metadata !307), !dbg !336
  call void @llvm.dbg.declare(metadata i32* %rv, metadata !337, metadata !307), !dbg !338
  store i32 -20, i32* %rv, align 4, !dbg !338
  call void @llvm.dbg.declare(metadata i32* %matched_modules, metadata !339, metadata !307), !dbg !340
  store i32 0, i32* %matched_modules, align 4, !dbg !340
  store i64 0, i64* %i, align 8, !dbg !341
  br label %for.cond, !dbg !343

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !344
  %cmp = icmp ult i64 %2, 16, !dbg !347
  br i1 %cmp, label %for.body, label %for.end, !dbg !348

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.archive_format_descriptor** %format, metadata !349, metadata !307), !dbg !351
  %3 = load i64, i64* %i, align 8, !dbg !352
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !353
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 12, !dbg !354
  %arrayidx = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 %3, !dbg !353
  store %struct.archive_format_descriptor* %arrayidx, %struct.archive_format_descriptor** %format, align 8, !dbg !351
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !355
  %options = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 3, !dbg !357
  %6 = load i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, i8*, i8*)** %options, align 8, !dbg !357
  %cmp1 = icmp eq i32 (%struct.archive_read*, i8*, i8*)* %6, null, !dbg !358
  br i1 %cmp1, label %if.then, label %lor.lhs.false, !dbg !359

lor.lhs.false:                                    ; preds = %for.body
  %7 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !360
  %name = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %7, i32 0, i32 1, !dbg !362
  %8 = load i8*, i8** %name, align 8, !dbg !362
  %cmp2 = icmp eq i8* %8, null, !dbg !363
  br i1 %cmp2, label %if.then, label %if.end, !dbg !364

if.then:                                          ; preds = %lor.lhs.false, %for.body
  br label %for.inc, !dbg !365

if.end:                                           ; preds = %lor.lhs.false
  %9 = load i8*, i8** %m.addr, align 8, !dbg !366
  %cmp3 = icmp ne i8* %9, null, !dbg !368
  br i1 %cmp3, label %if.then4, label %if.end9, !dbg !369

if.then4:                                         ; preds = %if.end
  %10 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !370
  %name5 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %10, i32 0, i32 1, !dbg !373
  %11 = load i8*, i8** %name5, align 8, !dbg !373
  %12 = load i8*, i8** %m.addr, align 8, !dbg !374
  %call = call i32 @strcmp(i8* %11, i8* %12) #4, !dbg !375
  %cmp6 = icmp ne i32 %call, 0, !dbg !376
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !377

if.then7:                                         ; preds = %if.then4
  br label %for.inc, !dbg !378

if.end8:                                          ; preds = %if.then4
  %13 = load i32, i32* %matched_modules, align 4, !dbg !379
  %inc = add nsw i32 %13, 1, !dbg !379
  store i32 %inc, i32* %matched_modules, align 4, !dbg !379
  br label %if.end9, !dbg !380

if.end9:                                          ; preds = %if.end8, %if.end
  %14 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !381
  %15 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !382
  %format10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 13, !dbg !383
  store %struct.archive_format_descriptor* %14, %struct.archive_format_descriptor** %format10, align 8, !dbg !384
  %16 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !385
  %options11 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %16, i32 0, i32 3, !dbg !386
  %17 = load i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, i8*, i8*)** %options11, align 8, !dbg !386
  %18 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !387
  %19 = load i8*, i8** %o.addr, align 8, !dbg !388
  %20 = load i8*, i8** %v.addr, align 8, !dbg !389
  %call12 = call i32 %17(%struct.archive_read* %18, i8* %19, i8* %20), !dbg !385
  store i32 %call12, i32* %r, align 4, !dbg !390
  %21 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !391
  %format13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 13, !dbg !392
  store %struct.archive_format_descriptor* null, %struct.archive_format_descriptor** %format13, align 8, !dbg !393
  %22 = load i32, i32* %r, align 4, !dbg !394
  %cmp14 = icmp eq i32 %22, -30, !dbg !396
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !397

if.then15:                                        ; preds = %if.end9
  store i32 -30, i32* %retval, align 4, !dbg !398
  br label %return, !dbg !398

if.end16:                                         ; preds = %if.end9
  %23 = load i32, i32* %r, align 4, !dbg !399
  %cmp17 = icmp eq i32 %23, 0, !dbg !401
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !402

if.then18:                                        ; preds = %if.end16
  store i32 0, i32* %rv, align 4, !dbg !403
  br label %if.end19, !dbg !404

if.end19:                                         ; preds = %if.then18, %if.end16
  br label %for.inc, !dbg !405

for.inc:                                          ; preds = %if.end19, %if.then7, %if.then
  %24 = load i64, i64* %i, align 8, !dbg !406
  %inc20 = add i64 %24, 1, !dbg !406
  store i64 %inc20, i64* %i, align 8, !dbg !406
  br label %for.cond, !dbg !408

for.end:                                          ; preds = %for.cond
  %25 = load i8*, i8** %m.addr, align 8, !dbg !409
  %cmp21 = icmp ne i8* %25, null, !dbg !411
  br i1 %cmp21, label %land.lhs.true, label %if.end24, !dbg !412

land.lhs.true:                                    ; preds = %for.end
  %26 = load i32, i32* %matched_modules, align 4, !dbg !413
  %cmp22 = icmp eq i32 %26, 0, !dbg !415
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !416

if.then23:                                        ; preds = %land.lhs.true
  store i32 -21, i32* %retval, align 4, !dbg !417
  br label %return, !dbg !417

if.end24:                                         ; preds = %land.lhs.true, %for.end
  %27 = load i32, i32* %rv, align 4, !dbg !418
  store i32 %27, i32* %retval, align 4, !dbg !419
  br label %return, !dbg !419

return:                                           ; preds = %if.end24, %if.then23, %if.then15
  %28 = load i32, i32* %retval, align 4, !dbg !420
  ret i32 %28, !dbg !420
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_filter_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !295 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !421, metadata !307), !dbg !422
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !423, metadata !307), !dbg !424
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !425, metadata !307), !dbg !426
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !427, metadata !307), !dbg !428
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !429
  %1 = load i8*, i8** %m.addr, align 8, !dbg !430
  %2 = load i8*, i8** %o.addr, align 8, !dbg !431
  %3 = load i8*, i8** %v.addr, align 8, !dbg !432
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 14594245, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.1, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_filter_option), !dbg !433
  ret i32 %call, !dbg !434
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_filter_option(%struct.archive* %_a, i8* %m, i8* %o, i8* %v) #0 !dbg !301 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read*, align 8
  %filter = alloca %struct.archive_read_filter*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %r = alloca i32, align 4
  %rv = alloca i32, align 4
  %matched_modules = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !435, metadata !307), !dbg !436
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !437, metadata !307), !dbg !438
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !439, metadata !307), !dbg !440
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !441, metadata !307), !dbg !442
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !443, metadata !307), !dbg !444
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !445
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !446
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !444
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter, metadata !447, metadata !307), !dbg !448
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !449, metadata !307), !dbg !450
  call void @llvm.dbg.declare(metadata i32* %r, metadata !451, metadata !307), !dbg !452
  call void @llvm.dbg.declare(metadata i32* %rv, metadata !453, metadata !307), !dbg !454
  store i32 -20, i32* %rv, align 4, !dbg !454
  call void @llvm.dbg.declare(metadata i32* %matched_modules, metadata !455, metadata !307), !dbg !456
  store i32 0, i32* %matched_modules, align 4, !dbg !456
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !457
  %filter1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 7, !dbg !459
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter1, align 8, !dbg !459
  store %struct.archive_read_filter* %3, %struct.archive_read_filter** %filter, align 8, !dbg !460
  br label %for.cond, !dbg !461

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !462
  %cmp = icmp ne %struct.archive_read_filter* %4, null, !dbg !465
  br i1 %cmp, label %for.body, label %for.end, !dbg !466

for.body:                                         ; preds = %for.cond
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !467
  %bidder2 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 1, !dbg !469
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder2, align 8, !dbg !469
  store %struct.archive_read_filter_bidder* %6, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !470
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !471
  %cmp3 = icmp eq %struct.archive_read_filter_bidder* %7, null, !dbg !473
  br i1 %cmp3, label %if.then, label %if.end, !dbg !474

if.then:                                          ; preds = %for.body
  br label %for.inc, !dbg !475

if.end:                                           ; preds = %for.body
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !476
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 4, !dbg !478
  %9 = load i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !478
  %cmp4 = icmp eq i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* %9, null, !dbg !479
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !480

if.then5:                                         ; preds = %if.end
  br label %for.inc, !dbg !481

if.end6:                                          ; preds = %if.end
  %10 = load i8*, i8** %m.addr, align 8, !dbg !482
  %cmp7 = icmp ne i8* %10, null, !dbg !484
  br i1 %cmp7, label %if.then8, label %if.end12, !dbg !485

if.then8:                                         ; preds = %if.end6
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !486
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 11, !dbg !489
  %12 = load i8*, i8** %name, align 8, !dbg !489
  %13 = load i8*, i8** %m.addr, align 8, !dbg !490
  %call = call i32 @strcmp(i8* %12, i8* %13) #4, !dbg !491
  %cmp9 = icmp ne i32 %call, 0, !dbg !492
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !493

if.then10:                                        ; preds = %if.then8
  br label %for.inc, !dbg !494

if.end11:                                         ; preds = %if.then8
  %14 = load i32, i32* %matched_modules, align 4, !dbg !495
  %inc = add nsw i32 %14, 1, !dbg !495
  store i32 %inc, i32* %matched_modules, align 4, !dbg !495
  br label %if.end12, !dbg !496

if.end12:                                         ; preds = %if.end11, %if.end6
  %15 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !497
  %options13 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %15, i32 0, i32 4, !dbg !498
  %16 = load i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options13, align 8, !dbg !498
  %17 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !499
  %18 = load i8*, i8** %o.addr, align 8, !dbg !500
  %19 = load i8*, i8** %v.addr, align 8, !dbg !501
  %call14 = call i32 %16(%struct.archive_read_filter_bidder* %17, i8* %18, i8* %19), !dbg !497
  store i32 %call14, i32* %r, align 4, !dbg !502
  %20 = load i32, i32* %r, align 4, !dbg !503
  %cmp15 = icmp eq i32 %20, -30, !dbg !505
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !506

if.then16:                                        ; preds = %if.end12
  store i32 -30, i32* %retval, align 4, !dbg !507
  br label %return, !dbg !507

if.end17:                                         ; preds = %if.end12
  %21 = load i32, i32* %r, align 4, !dbg !508
  %cmp18 = icmp eq i32 %21, 0, !dbg !510
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !511

if.then19:                                        ; preds = %if.end17
  store i32 0, i32* %rv, align 4, !dbg !512
  br label %if.end20, !dbg !513

if.end20:                                         ; preds = %if.then19, %if.end17
  br label %for.inc, !dbg !514

for.inc:                                          ; preds = %if.end20, %if.then10, %if.then5, %if.then
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !515
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %22, i32 0, i32 2, !dbg !517
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !517
  store %struct.archive_read_filter* %23, %struct.archive_read_filter** %filter, align 8, !dbg !518
  br label %for.cond, !dbg !519

for.end:                                          ; preds = %for.cond
  %24 = load i8*, i8** %m.addr, align 8, !dbg !520
  %cmp21 = icmp ne i8* %24, null, !dbg !522
  br i1 %cmp21, label %land.lhs.true, label %if.end24, !dbg !523

land.lhs.true:                                    ; preds = %for.end
  %25 = load i32, i32* %matched_modules, align 4, !dbg !524
  %cmp22 = icmp eq i32 %25, 0, !dbg !526
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !527

if.then23:                                        ; preds = %land.lhs.true
  store i32 -21, i32* %retval, align 4, !dbg !528
  br label %return, !dbg !528

if.end24:                                         ; preds = %land.lhs.true, %for.end
  %26 = load i32, i32* %rv, align 4, !dbg !529
  store i32 %26, i32* %retval, align 4, !dbg !530
  br label %return, !dbg !530

return:                                           ; preds = %if.end24, %if.then23, %if.then16
  %27 = load i32, i32* %retval, align 4, !dbg !531
  ret i32 %27, !dbg !531
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !296 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !532, metadata !307), !dbg !533
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !534, metadata !307), !dbg !535
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !536, metadata !307), !dbg !537
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !538, metadata !307), !dbg !539
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !540
  %1 = load i8*, i8** %m.addr, align 8, !dbg !541
  %2 = load i8*, i8** %o.addr, align 8, !dbg !542
  %3 = load i8*, i8** %v.addr, align 8, !dbg !543
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 14594245, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_option), !dbg !544
  ret i32 %call, !dbg !545
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !302 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !546, metadata !307), !dbg !547
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !548, metadata !307), !dbg !549
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !550, metadata !307), !dbg !551
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !552, metadata !307), !dbg !553
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !554
  %1 = load i8*, i8** %m.addr, align 8, !dbg !555
  %2 = load i8*, i8** %o.addr, align 8, !dbg !556
  %3 = load i8*, i8** %v.addr, align 8, !dbg !557
  %call = call i32 @_archive_set_either_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_format_option, i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_filter_option), !dbg !558
  ret i32 %call, !dbg !559
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_options(%struct.archive* %a, i8* %options) #0 !dbg !297 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %options.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !560, metadata !307), !dbg !561
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !562, metadata !307), !dbg !563
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !564
  %1 = load i8*, i8** %options.addr, align 8, !dbg !565
  %call = call i32 @_archive_set_options(%struct.archive* %0, i8* %1, i32 14594245, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.3, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_option), !dbg !566
  ret i32 %call, !dbg !567
}

declare i32 @_archive_set_options(%struct.archive*, i8*, i32, i8*, i32 (%struct.archive*, i8*, i8*, i8*)*) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

declare i32 @_archive_set_either_option(%struct.archive*, i8*, i8*, i8*, i32 (%struct.archive*, i8*, i8*, i8*)*, i32 (%struct.archive*, i8*, i8*, i8*)*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!303, !304}
!llvm.ident = !{!305}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_set_options.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !122}
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
!291 = !{!292, !295, !296, !297, !300, !301, !302}
!292 = distinct !DISubprogram(name: "archive_read_set_format_option", scope: !1, file: !1, line: 40, type: !293, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = !DISubroutineType(types: !294)
!294 = !{!23, !24, !80, !80, !80}
!295 = distinct !DISubprogram(name: "archive_read_set_filter_option", scope: !1, file: !1, line: 49, type: !293, isLocal: false, isDefinition: true, scopeLine: 51, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!296 = distinct !DISubprogram(name: "archive_read_set_option", scope: !1, file: !1, line: 58, type: !293, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!297 = distinct !DISubprogram(name: "archive_read_set_options", scope: !1, file: !1, line: 67, type: !298, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!298 = !DISubroutineType(types: !299)
!299 = !{!23, !24, !80}
!300 = distinct !DISubprogram(name: "archive_set_format_option", scope: !1, file: !1, line: 75, type: !293, isLocal: true, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!301 = distinct !DISubprogram(name: "archive_set_filter_option", scope: !1, file: !1, line: 112, type: !293, isLocal: true, isDefinition: true, scopeLine: 114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = distinct !DISubprogram(name: "archive_set_option", scope: !1, file: !1, line: 149, type: !293, isLocal: true, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!303 = !{i32 2, !"Dwarf Version", i32 4}
!304 = !{i32 2, !"Debug Info Version", i32 3}
!305 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!306 = !DILocalVariable(name: "a", arg: 1, scope: !292, file: !1, line: 40, type: !24)
!307 = !DIExpression()
!308 = !DILocation(line: 40, column: 48, scope: !292)
!309 = !DILocalVariable(name: "m", arg: 2, scope: !292, file: !1, line: 40, type: !80)
!310 = !DILocation(line: 40, column: 63, scope: !292)
!311 = !DILocalVariable(name: "o", arg: 3, scope: !292, file: !1, line: 40, type: !80)
!312 = !DILocation(line: 40, column: 78, scope: !292)
!313 = !DILocalVariable(name: "v", arg: 4, scope: !292, file: !1, line: 41, type: !80)
!314 = !DILocation(line: 41, column: 17, scope: !292)
!315 = !DILocation(line: 43, column: 29, scope: !292)
!316 = !DILocation(line: 43, column: 32, scope: !292)
!317 = !DILocation(line: 43, column: 35, scope: !292)
!318 = !DILocation(line: 43, column: 38, scope: !292)
!319 = !DILocation(line: 43, column: 9, scope: !292)
!320 = !DILocation(line: 43, column: 2, scope: !292)
!321 = !DILocalVariable(name: "_a", arg: 1, scope: !300, file: !1, line: 75, type: !24)
!322 = !DILocation(line: 75, column: 43, scope: !300)
!323 = !DILocalVariable(name: "m", arg: 2, scope: !300, file: !1, line: 75, type: !80)
!324 = !DILocation(line: 75, column: 59, scope: !300)
!325 = !DILocalVariable(name: "o", arg: 3, scope: !300, file: !1, line: 75, type: !80)
!326 = !DILocation(line: 75, column: 74, scope: !300)
!327 = !DILocalVariable(name: "v", arg: 4, scope: !300, file: !1, line: 76, type: !80)
!328 = !DILocation(line: 76, column: 17, scope: !300)
!329 = !DILocalVariable(name: "a", scope: !300, file: !1, line: 78, type: !4)
!330 = !DILocation(line: 78, column: 23, scope: !300)
!331 = !DILocation(line: 78, column: 50, scope: !300)
!332 = !DILocation(line: 78, column: 27, scope: !300)
!333 = !DILocalVariable(name: "i", scope: !300, file: !1, line: 79, type: !45)
!334 = !DILocation(line: 79, column: 9, scope: !300)
!335 = !DILocalVariable(name: "r", scope: !300, file: !1, line: 80, type: !23)
!336 = !DILocation(line: 80, column: 6, scope: !300)
!337 = !DILocalVariable(name: "rv", scope: !300, file: !1, line: 80, type: !23)
!338 = !DILocation(line: 80, column: 9, scope: !300)
!339 = !DILocalVariable(name: "matched_modules", scope: !300, file: !1, line: 80, type: !23)
!340 = !DILocation(line: 80, column: 28, scope: !300)
!341 = !DILocation(line: 82, column: 9, scope: !342)
!342 = distinct !DILexicalBlock(scope: !300, file: !1, line: 82, column: 2)
!343 = !DILocation(line: 82, column: 7, scope: !342)
!344 = !DILocation(line: 82, column: 14, scope: !345)
!345 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 1)
!346 = distinct !DILexicalBlock(scope: !342, file: !1, line: 82, column: 2)
!347 = !DILocation(line: 82, column: 16, scope: !345)
!348 = !DILocation(line: 82, column: 2, scope: !345)
!349 = !DILocalVariable(name: "format", scope: !350, file: !1, line: 83, type: !261)
!350 = distinct !DILexicalBlock(scope: !346, file: !1, line: 82, column: 65)
!351 = !DILocation(line: 83, column: 37, scope: !350)
!352 = !DILocation(line: 83, column: 58, scope: !350)
!353 = !DILocation(line: 83, column: 47, scope: !350)
!354 = !DILocation(line: 83, column: 50, scope: !350)
!355 = !DILocation(line: 85, column: 7, scope: !356)
!356 = distinct !DILexicalBlock(scope: !350, file: !1, line: 85, column: 7)
!357 = !DILocation(line: 85, column: 15, scope: !356)
!358 = !DILocation(line: 85, column: 23, scope: !356)
!359 = !DILocation(line: 85, column: 31, scope: !356)
!360 = !DILocation(line: 85, column: 34, scope: !361)
!361 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 1)
!362 = !DILocation(line: 85, column: 42, scope: !361)
!363 = !DILocation(line: 85, column: 47, scope: !361)
!364 = !DILocation(line: 85, column: 7, scope: !361)
!365 = !DILocation(line: 87, column: 4, scope: !356)
!366 = !DILocation(line: 88, column: 7, scope: !367)
!367 = distinct !DILexicalBlock(scope: !350, file: !1, line: 88, column: 7)
!368 = !DILocation(line: 88, column: 9, scope: !367)
!369 = !DILocation(line: 88, column: 7, scope: !350)
!370 = !DILocation(line: 89, column: 15, scope: !371)
!371 = distinct !DILexicalBlock(scope: !372, file: !1, line: 89, column: 8)
!372 = distinct !DILexicalBlock(scope: !367, file: !1, line: 88, column: 18)
!373 = !DILocation(line: 89, column: 23, scope: !371)
!374 = !DILocation(line: 89, column: 29, scope: !371)
!375 = !DILocation(line: 89, column: 8, scope: !371)
!376 = !DILocation(line: 89, column: 32, scope: !371)
!377 = !DILocation(line: 89, column: 8, scope: !372)
!378 = !DILocation(line: 90, column: 5, scope: !371)
!379 = !DILocation(line: 91, column: 4, scope: !372)
!380 = !DILocation(line: 92, column: 3, scope: !372)
!381 = !DILocation(line: 94, column: 15, scope: !350)
!382 = !DILocation(line: 94, column: 3, scope: !350)
!383 = !DILocation(line: 94, column: 6, scope: !350)
!384 = !DILocation(line: 94, column: 13, scope: !350)
!385 = !DILocation(line: 95, column: 7, scope: !350)
!386 = !DILocation(line: 95, column: 15, scope: !350)
!387 = !DILocation(line: 95, column: 23, scope: !350)
!388 = !DILocation(line: 95, column: 26, scope: !350)
!389 = !DILocation(line: 95, column: 29, scope: !350)
!390 = !DILocation(line: 95, column: 5, scope: !350)
!391 = !DILocation(line: 96, column: 3, scope: !350)
!392 = !DILocation(line: 96, column: 6, scope: !350)
!393 = !DILocation(line: 96, column: 13, scope: !350)
!394 = !DILocation(line: 98, column: 7, scope: !395)
!395 = distinct !DILexicalBlock(scope: !350, file: !1, line: 98, column: 7)
!396 = !DILocation(line: 98, column: 9, scope: !395)
!397 = !DILocation(line: 98, column: 7, scope: !350)
!398 = !DILocation(line: 99, column: 4, scope: !395)
!399 = !DILocation(line: 101, column: 7, scope: !400)
!400 = distinct !DILexicalBlock(scope: !350, file: !1, line: 101, column: 7)
!401 = !DILocation(line: 101, column: 9, scope: !400)
!402 = !DILocation(line: 101, column: 7, scope: !350)
!403 = !DILocation(line: 102, column: 7, scope: !400)
!404 = !DILocation(line: 102, column: 4, scope: !400)
!405 = !DILocation(line: 103, column: 2, scope: !350)
!406 = !DILocation(line: 82, column: 61, scope: !407)
!407 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 2)
!408 = !DILocation(line: 82, column: 2, scope: !407)
!409 = !DILocation(line: 106, column: 6, scope: !410)
!410 = distinct !DILexicalBlock(scope: !300, file: !1, line: 106, column: 6)
!411 = !DILocation(line: 106, column: 8, scope: !410)
!412 = !DILocation(line: 106, column: 16, scope: !410)
!413 = !DILocation(line: 106, column: 19, scope: !414)
!414 = !DILexicalBlockFile(scope: !410, file: !1, discriminator: 1)
!415 = !DILocation(line: 106, column: 35, scope: !414)
!416 = !DILocation(line: 106, column: 6, scope: !414)
!417 = !DILocation(line: 107, column: 3, scope: !410)
!418 = !DILocation(line: 108, column: 10, scope: !300)
!419 = !DILocation(line: 108, column: 2, scope: !300)
!420 = !DILocation(line: 109, column: 1, scope: !300)
!421 = !DILocalVariable(name: "a", arg: 1, scope: !295, file: !1, line: 49, type: !24)
!422 = !DILocation(line: 49, column: 48, scope: !295)
!423 = !DILocalVariable(name: "m", arg: 2, scope: !295, file: !1, line: 49, type: !80)
!424 = !DILocation(line: 49, column: 63, scope: !295)
!425 = !DILocalVariable(name: "o", arg: 3, scope: !295, file: !1, line: 49, type: !80)
!426 = !DILocation(line: 49, column: 78, scope: !295)
!427 = !DILocalVariable(name: "v", arg: 4, scope: !295, file: !1, line: 50, type: !80)
!428 = !DILocation(line: 50, column: 17, scope: !295)
!429 = !DILocation(line: 52, column: 29, scope: !295)
!430 = !DILocation(line: 52, column: 32, scope: !295)
!431 = !DILocation(line: 52, column: 35, scope: !295)
!432 = !DILocation(line: 52, column: 38, scope: !295)
!433 = !DILocation(line: 52, column: 9, scope: !295)
!434 = !DILocation(line: 52, column: 2, scope: !295)
!435 = !DILocalVariable(name: "_a", arg: 1, scope: !301, file: !1, line: 112, type: !24)
!436 = !DILocation(line: 112, column: 43, scope: !301)
!437 = !DILocalVariable(name: "m", arg: 2, scope: !301, file: !1, line: 112, type: !80)
!438 = !DILocation(line: 112, column: 59, scope: !301)
!439 = !DILocalVariable(name: "o", arg: 3, scope: !301, file: !1, line: 112, type: !80)
!440 = !DILocation(line: 112, column: 74, scope: !301)
!441 = !DILocalVariable(name: "v", arg: 4, scope: !301, file: !1, line: 113, type: !80)
!442 = !DILocation(line: 113, column: 17, scope: !301)
!443 = !DILocalVariable(name: "a", scope: !301, file: !1, line: 115, type: !4)
!444 = !DILocation(line: 115, column: 23, scope: !301)
!445 = !DILocation(line: 115, column: 50, scope: !301)
!446 = !DILocation(line: 115, column: 27, scope: !301)
!447 = !DILocalVariable(name: "filter", scope: !301, file: !1, line: 116, type: !169)
!448 = !DILocation(line: 116, column: 30, scope: !301)
!449 = !DILocalVariable(name: "bidder", scope: !301, file: !1, line: 117, type: !168)
!450 = !DILocation(line: 117, column: 37, scope: !301)
!451 = !DILocalVariable(name: "r", scope: !301, file: !1, line: 118, type: !23)
!452 = !DILocation(line: 118, column: 6, scope: !301)
!453 = !DILocalVariable(name: "rv", scope: !301, file: !1, line: 118, type: !23)
!454 = !DILocation(line: 118, column: 9, scope: !301)
!455 = !DILocalVariable(name: "matched_modules", scope: !301, file: !1, line: 118, type: !23)
!456 = !DILocation(line: 118, column: 28, scope: !301)
!457 = !DILocation(line: 120, column: 16, scope: !458)
!458 = distinct !DILexicalBlock(scope: !301, file: !1, line: 120, column: 2)
!459 = !DILocation(line: 120, column: 19, scope: !458)
!460 = !DILocation(line: 120, column: 14, scope: !458)
!461 = !DILocation(line: 120, column: 7, scope: !458)
!462 = !DILocation(line: 120, column: 27, scope: !463)
!463 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 1)
!464 = distinct !DILexicalBlock(scope: !458, file: !1, line: 120, column: 2)
!465 = !DILocation(line: 120, column: 34, scope: !463)
!466 = !DILocation(line: 120, column: 2, scope: !463)
!467 = !DILocation(line: 121, column: 12, scope: !468)
!468 = distinct !DILexicalBlock(scope: !464, file: !1, line: 120, column: 70)
!469 = !DILocation(line: 121, column: 20, scope: !468)
!470 = !DILocation(line: 121, column: 10, scope: !468)
!471 = !DILocation(line: 122, column: 7, scope: !472)
!472 = distinct !DILexicalBlock(scope: !468, file: !1, line: 122, column: 7)
!473 = !DILocation(line: 122, column: 14, scope: !472)
!474 = !DILocation(line: 122, column: 7, scope: !468)
!475 = !DILocation(line: 123, column: 4, scope: !472)
!476 = !DILocation(line: 124, column: 7, scope: !477)
!477 = distinct !DILexicalBlock(scope: !468, file: !1, line: 124, column: 7)
!478 = !DILocation(line: 124, column: 15, scope: !477)
!479 = !DILocation(line: 124, column: 23, scope: !477)
!480 = !DILocation(line: 124, column: 7, scope: !468)
!481 = !DILocation(line: 126, column: 4, scope: !477)
!482 = !DILocation(line: 127, column: 7, scope: !483)
!483 = distinct !DILexicalBlock(scope: !468, file: !1, line: 127, column: 7)
!484 = !DILocation(line: 127, column: 9, scope: !483)
!485 = !DILocation(line: 127, column: 7, scope: !468)
!486 = !DILocation(line: 128, column: 15, scope: !487)
!487 = distinct !DILexicalBlock(scope: !488, file: !1, line: 128, column: 8)
!488 = distinct !DILexicalBlock(scope: !483, file: !1, line: 127, column: 18)
!489 = !DILocation(line: 128, column: 23, scope: !487)
!490 = !DILocation(line: 128, column: 29, scope: !487)
!491 = !DILocation(line: 128, column: 8, scope: !487)
!492 = !DILocation(line: 128, column: 32, scope: !487)
!493 = !DILocation(line: 128, column: 8, scope: !488)
!494 = !DILocation(line: 129, column: 5, scope: !487)
!495 = !DILocation(line: 130, column: 4, scope: !488)
!496 = !DILocation(line: 131, column: 3, scope: !488)
!497 = !DILocation(line: 133, column: 7, scope: !468)
!498 = !DILocation(line: 133, column: 15, scope: !468)
!499 = !DILocation(line: 133, column: 23, scope: !468)
!500 = !DILocation(line: 133, column: 31, scope: !468)
!501 = !DILocation(line: 133, column: 34, scope: !468)
!502 = !DILocation(line: 133, column: 5, scope: !468)
!503 = !DILocation(line: 135, column: 7, scope: !504)
!504 = distinct !DILexicalBlock(scope: !468, file: !1, line: 135, column: 7)
!505 = !DILocation(line: 135, column: 9, scope: !504)
!506 = !DILocation(line: 135, column: 7, scope: !468)
!507 = !DILocation(line: 136, column: 4, scope: !504)
!508 = !DILocation(line: 138, column: 7, scope: !509)
!509 = distinct !DILexicalBlock(scope: !468, file: !1, line: 138, column: 7)
!510 = !DILocation(line: 138, column: 9, scope: !509)
!511 = !DILocation(line: 138, column: 7, scope: !468)
!512 = !DILocation(line: 139, column: 7, scope: !509)
!513 = !DILocation(line: 139, column: 4, scope: !509)
!514 = !DILocation(line: 140, column: 2, scope: !468)
!515 = !DILocation(line: 120, column: 52, scope: !516)
!516 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 2)
!517 = !DILocation(line: 120, column: 60, scope: !516)
!518 = !DILocation(line: 120, column: 50, scope: !516)
!519 = !DILocation(line: 120, column: 2, scope: !516)
!520 = !DILocation(line: 143, column: 6, scope: !521)
!521 = distinct !DILexicalBlock(scope: !301, file: !1, line: 143, column: 6)
!522 = !DILocation(line: 143, column: 8, scope: !521)
!523 = !DILocation(line: 143, column: 16, scope: !521)
!524 = !DILocation(line: 143, column: 19, scope: !525)
!525 = !DILexicalBlockFile(scope: !521, file: !1, discriminator: 1)
!526 = !DILocation(line: 143, column: 35, scope: !525)
!527 = !DILocation(line: 143, column: 6, scope: !525)
!528 = !DILocation(line: 144, column: 3, scope: !521)
!529 = !DILocation(line: 145, column: 10, scope: !301)
!530 = !DILocation(line: 145, column: 2, scope: !301)
!531 = !DILocation(line: 146, column: 1, scope: !301)
!532 = !DILocalVariable(name: "a", arg: 1, scope: !296, file: !1, line: 58, type: !24)
!533 = !DILocation(line: 58, column: 41, scope: !296)
!534 = !DILocalVariable(name: "m", arg: 2, scope: !296, file: !1, line: 58, type: !80)
!535 = !DILocation(line: 58, column: 56, scope: !296)
!536 = !DILocalVariable(name: "o", arg: 3, scope: !296, file: !1, line: 58, type: !80)
!537 = !DILocation(line: 58, column: 71, scope: !296)
!538 = !DILocalVariable(name: "v", arg: 4, scope: !296, file: !1, line: 59, type: !80)
!539 = !DILocation(line: 59, column: 17, scope: !296)
!540 = !DILocation(line: 61, column: 29, scope: !296)
!541 = !DILocation(line: 61, column: 32, scope: !296)
!542 = !DILocation(line: 61, column: 35, scope: !296)
!543 = !DILocation(line: 61, column: 38, scope: !296)
!544 = !DILocation(line: 61, column: 9, scope: !296)
!545 = !DILocation(line: 61, column: 2, scope: !296)
!546 = !DILocalVariable(name: "a", arg: 1, scope: !302, file: !1, line: 149, type: !24)
!547 = !DILocation(line: 149, column: 36, scope: !302)
!548 = !DILocalVariable(name: "m", arg: 2, scope: !302, file: !1, line: 149, type: !80)
!549 = !DILocation(line: 149, column: 51, scope: !302)
!550 = !DILocalVariable(name: "o", arg: 3, scope: !302, file: !1, line: 149, type: !80)
!551 = !DILocation(line: 149, column: 66, scope: !302)
!552 = !DILocalVariable(name: "v", arg: 4, scope: !302, file: !1, line: 150, type: !80)
!553 = !DILocation(line: 150, column: 17, scope: !302)
!554 = !DILocation(line: 152, column: 36, scope: !302)
!555 = !DILocation(line: 152, column: 39, scope: !302)
!556 = !DILocation(line: 152, column: 42, scope: !302)
!557 = !DILocation(line: 152, column: 45, scope: !302)
!558 = !DILocation(line: 152, column: 9, scope: !302)
!559 = !DILocation(line: 152, column: 2, scope: !302)
!560 = !DILocalVariable(name: "a", arg: 1, scope: !297, file: !1, line: 67, type: !24)
!561 = !DILocation(line: 67, column: 42, scope: !297)
!562 = !DILocalVariable(name: "options", arg: 2, scope: !297, file: !1, line: 67, type: !80)
!563 = !DILocation(line: 67, column: 57, scope: !297)
!564 = !DILocation(line: 69, column: 30, scope: !297)
!565 = !DILocation(line: 69, column: 33, scope: !297)
!566 = !DILocation(line: 69, column: 9, scope: !297)
!567 = !DILocation(line: 69, column: 2, scope: !297)
