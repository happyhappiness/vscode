; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_program.c'
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
%struct.program_bidder = type { i8*, i8*, i8*, i64, i32 }
%struct.program_filter = type { %struct.archive_string, i32, i32, i32, i32, i32, i8*, i64 }
%union.anon = type { i32 }
%union.anon.0 = type { i32 }
%union.anon.1 = type { i32 }
%union.anon.2 = type { i32 }
%union.anon.3 = type { i32 }
%union.anon.4 = type { i32 }

@.str = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@__archive_read_program.out_buf_len = internal constant i64 65536, align 8
@.str.1 = private unnamed_addr constant [10 x i8] c"Program: \00", align 1
@.str.2 = private unnamed_addr constant [26 x i8] c"Can't allocate input data\00", align 1
@.str.3 = private unnamed_addr constant [52 x i8] c"Can't initialize filter; unable to run program \22%s\22\00", align 1
@.str.4 = private unnamed_addr constant [27 x i8] c"Child process exited badly\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"Child process exited with signal %d\00", align 1
@.str.6 = private unnamed_addr constant [36 x i8] c"Child process exited with status %d\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_program(%struct.archive* %a, i8* %cmd) #0 !dbg !315 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !349, metadata !350), !dbg !351
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !352, metadata !350), !dbg !353
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !354
  %1 = load i8*, i8** %cmd.addr, align 8, !dbg !355
  %call = call i32 @archive_read_support_filter_program(%struct.archive* %0, i8* %1), !dbg !356
  ret i32 %call, !dbg !357
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_program(%struct.archive* %a, i8* %cmd) #0 !dbg !321 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !358, metadata !350), !dbg !359
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !360, metadata !350), !dbg !361
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !362
  %1 = load i8*, i8** %cmd.addr, align 8, !dbg !363
  %call = call i32 @archive_read_support_filter_program_signature(%struct.archive* %0, i8* %1, i8* null, i64 0), !dbg !364
  ret i32 %call, !dbg !365
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_program_signature(%struct.archive* %a, i8* %cmd, i8* %signature, i64 %signature_len) #0 !dbg !318 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  %signature.addr = alloca i8*, align 8
  %signature_len.addr = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !366, metadata !350), !dbg !367
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !368, metadata !350), !dbg !369
  store i8* %signature, i8** %signature.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %signature.addr, metadata !370, metadata !350), !dbg !371
  store i64 %signature_len, i64* %signature_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %signature_len.addr, metadata !372, metadata !350), !dbg !373
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !374
  %1 = load i8*, i8** %cmd.addr, align 8, !dbg !375
  %2 = load i8*, i8** %signature.addr, align 8, !dbg !376
  %3 = load i64, i64* %signature_len.addr, align 8, !dbg !377
  %call = call i32 @archive_read_support_filter_program_signature(%struct.archive* %0, i8* %1, i8* %2, i64 %3), !dbg !378
  ret i32 %call, !dbg !379
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_program_signature(%struct.archive* %_a, i8* %cmd, i8* %signature, i64 %signature_len) #0 !dbg !322 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  %signature.addr = alloca i8*, align 8
  %signature_len.addr = alloca i64, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %state = alloca %struct.program_bidder*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !380, metadata !350), !dbg !381
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !382, metadata !350), !dbg !383
  store i8* %signature, i8** %signature.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %signature.addr, metadata !384, metadata !350), !dbg !385
  store i64 %signature_len, i64* %signature_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %signature_len.addr, metadata !386, metadata !350), !dbg !387
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !388, metadata !350), !dbg !389
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !390
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !391
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !389
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !392, metadata !350), !dbg !393
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %state, metadata !394, metadata !350), !dbg !395
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !396
  %call = call i32 @__archive_read_get_bidder(%struct.archive_read* %2, %struct.archive_read_filter_bidder** %bidder), !dbg !398
  %cmp = icmp ne i32 %call, 0, !dbg !399
  br i1 %cmp, label %if.then, label %if.end, !dbg !400

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !401
  br label %return, !dbg !401

if.end:                                           ; preds = %entry
  %call1 = call noalias i8* @calloc(i64 1, i64 40) #7, !dbg !402
  %3 = bitcast i8* %call1 to %struct.program_bidder*, !dbg !403
  store %struct.program_bidder* %3, %struct.program_bidder** %state, align 8, !dbg !404
  %4 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !405
  %cmp2 = icmp eq %struct.program_bidder* %4, null, !dbg !407
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !408

if.then3:                                         ; preds = %if.end
  br label %memerr, !dbg !409

if.end4:                                          ; preds = %if.end
  %5 = load i8*, i8** %cmd.addr, align 8, !dbg !410
  %call5 = call noalias i8* @strdup(i8* %5) #7, !dbg !411
  %6 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !412
  %cmd6 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %6, i32 0, i32 1, !dbg !413
  store i8* %call5, i8** %cmd6, align 8, !dbg !414
  %7 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !415
  %cmd7 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %7, i32 0, i32 1, !dbg !417
  %8 = load i8*, i8** %cmd7, align 8, !dbg !417
  %cmp8 = icmp eq i8* %8, null, !dbg !418
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !419

if.then9:                                         ; preds = %if.end4
  br label %memerr, !dbg !420

if.end10:                                         ; preds = %if.end4
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !421
  %10 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !422
  %11 = load i8*, i8** %signature.addr, align 8, !dbg !423
  %12 = load i64, i64* %signature_len.addr, align 8, !dbg !424
  %call11 = call i32 @set_bidder_signature(%struct.archive_read_filter_bidder* %9, %struct.program_bidder* %10, i8* %11, i64 %12), !dbg !425
  store i32 %call11, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

memerr:                                           ; preds = %if.then9, %if.then3
  %13 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !427
  call void @free_state(%struct.program_bidder* %13), !dbg !428
  %14 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !429
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str, i32 0, i32 0)), !dbg !430
  store i32 -30, i32* %retval, align 4, !dbg !431
  br label %return, !dbg !431

return:                                           ; preds = %memerr, %if.end10, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !432
  ret i32 %15, !dbg !432
}

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @set_bidder_signature(%struct.archive_read_filter_bidder* %bidder, %struct.program_bidder* %state, i8* %signature, i64 %signature_len) #0 !dbg !326 {
entry:
  %bidder.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %state.addr = alloca %struct.program_bidder*, align 8
  %signature.addr = alloca i8*, align 8
  %signature_len.addr = alloca i64, align 8
  store %struct.archive_read_filter_bidder* %bidder, %struct.archive_read_filter_bidder** %bidder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder.addr, metadata !433, metadata !350), !dbg !434
  store %struct.program_bidder* %state, %struct.program_bidder** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %state.addr, metadata !435, metadata !350), !dbg !436
  store i8* %signature, i8** %signature.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %signature.addr, metadata !437, metadata !350), !dbg !438
  store i64 %signature_len, i64* %signature_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %signature_len.addr, metadata !439, metadata !350), !dbg !440
  %0 = load i8*, i8** %signature.addr, align 8, !dbg !441
  %cmp = icmp ne i8* %0, null, !dbg !443
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !444

land.lhs.true:                                    ; preds = %entry
  %1 = load i64, i64* %signature_len.addr, align 8, !dbg !445
  %cmp1 = icmp ugt i64 %1, 0, !dbg !447
  br i1 %cmp1, label %if.then, label %if.end, !dbg !448

if.then:                                          ; preds = %land.lhs.true
  %2 = load i64, i64* %signature_len.addr, align 8, !dbg !449
  %3 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !451
  %signature_len2 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %3, i32 0, i32 3, !dbg !452
  store i64 %2, i64* %signature_len2, align 8, !dbg !453
  %4 = load i64, i64* %signature_len.addr, align 8, !dbg !454
  %call = call noalias i8* @malloc(i64 %4) #7, !dbg !455
  %5 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !456
  %signature3 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %5, i32 0, i32 2, !dbg !457
  store i8* %call, i8** %signature3, align 8, !dbg !458
  %6 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !459
  %signature4 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %6, i32 0, i32 2, !dbg !460
  %7 = load i8*, i8** %signature4, align 8, !dbg !460
  %8 = load i8*, i8** %signature.addr, align 8, !dbg !461
  %9 = load i64, i64* %signature_len.addr, align 8, !dbg !462
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %7, i8* %8, i64 %9, i32 1, i1 false), !dbg !463
  br label %if.end, !dbg !464

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %10 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !465
  %11 = bitcast %struct.program_bidder* %10 to i8*, !dbg !465
  %12 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder.addr, align 8, !dbg !466
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %12, i32 0, i32 0, !dbg !467
  store i8* %11, i8** %data, align 8, !dbg !468
  %13 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder.addr, align 8, !dbg !469
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %13, i32 0, i32 2, !dbg !470
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @program_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !471
  %14 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder.addr, align 8, !dbg !472
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %14, i32 0, i32 3, !dbg !473
  store i32 (%struct.archive_read_filter*)* @program_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !474
  %15 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder.addr, align 8, !dbg !475
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %15, i32 0, i32 4, !dbg !476
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !477
  %16 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder.addr, align 8, !dbg !478
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %16, i32 0, i32 5, !dbg !479
  store i32 (%struct.archive_read_filter_bidder*)* @program_bidder_free, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !480
  ret i32 0, !dbg !481
}

; Function Attrs: nounwind uwtable
define internal void @free_state(%struct.program_bidder* %state) #0 !dbg !332 {
entry:
  %state.addr = alloca %struct.program_bidder*, align 8
  store %struct.program_bidder* %state, %struct.program_bidder** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %state.addr, metadata !482, metadata !350), !dbg !483
  %0 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !484
  %tobool = icmp ne %struct.program_bidder* %0, null, !dbg !484
  br i1 %tobool, label %if.then, label %if.end, !dbg !486

if.then:                                          ; preds = %entry
  %1 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !487
  %cmd = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %1, i32 0, i32 1, !dbg !489
  %2 = load i8*, i8** %cmd, align 8, !dbg !489
  call void @free(i8* %2) #7, !dbg !490
  %3 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !491
  %signature = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %3, i32 0, i32 2, !dbg !492
  %4 = load i8*, i8** %signature, align 8, !dbg !492
  call void @free(i8* %4) #7, !dbg !493
  %5 = load %struct.program_bidder*, %struct.program_bidder** %state.addr, align 8, !dbg !494
  %6 = bitcast %struct.program_bidder* %5 to i8*, !dbg !494
  call void @free(i8* %6) #7, !dbg !495
  br label %if.end, !dbg !496

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !497
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @__archive_read_program(%struct.archive_read_filter* %self, i8* %cmd) #0 !dbg !323 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %cmd.addr = alloca i8*, align 8
  %state = alloca %struct.program_filter*, align 8
  %out_buf = alloca i8*, align 8
  %prefix = alloca i8*, align 8
  %child = alloca i32, align 4
  %l = alloca i64, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !498, metadata !350), !dbg !499
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !500, metadata !350), !dbg !501
  call void @llvm.dbg.declare(metadata %struct.program_filter** %state, metadata !502, metadata !350), !dbg !503
  call void @llvm.dbg.declare(metadata i8** %out_buf, metadata !504, metadata !350), !dbg !505
  call void @llvm.dbg.declare(metadata i8** %prefix, metadata !506, metadata !350), !dbg !507
  store i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.1, i32 0, i32 0), i8** %prefix, align 8, !dbg !507
  call void @llvm.dbg.declare(metadata i32* %child, metadata !508, metadata !350), !dbg !509
  call void @llvm.dbg.declare(metadata i64* %l, metadata !510, metadata !350), !dbg !511
  %0 = load i8*, i8** %prefix, align 8, !dbg !512
  %call = call i64 @strlen(i8* %0) #8, !dbg !513
  %1 = load i8*, i8** %cmd.addr, align 8, !dbg !514
  %call1 = call i64 @strlen(i8* %1) #8, !dbg !515
  %add = add i64 %call, %call1, !dbg !517
  %add2 = add i64 %add, 1, !dbg !518
  store i64 %add2, i64* %l, align 8, !dbg !519
  %call3 = call noalias i8* @calloc(i64 1, i64 64) #7, !dbg !520
  %2 = bitcast i8* %call3 to %struct.program_filter*, !dbg !521
  store %struct.program_filter* %2, %struct.program_filter** %state, align 8, !dbg !522
  %call4 = call noalias i8* @malloc(i64 65536) #7, !dbg !523
  store i8* %call4, i8** %out_buf, align 8, !dbg !524
  %3 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !525
  %cmp = icmp eq %struct.program_filter* %3, null, !dbg !527
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !528

lor.lhs.false:                                    ; preds = %entry
  %4 = load i8*, i8** %out_buf, align 8, !dbg !529
  %cmp5 = icmp eq i8* %4, null, !dbg !531
  br i1 %cmp5, label %if.then, label %lor.lhs.false6, !dbg !532

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %5 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !533
  %description = getelementptr inbounds %struct.program_filter, %struct.program_filter* %5, i32 0, i32 0, !dbg !534
  %6 = load i64, i64* %l, align 8, !dbg !535
  %call7 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %description, i64 %6), !dbg !536
  %cmp8 = icmp eq %struct.archive_string* %call7, null, !dbg !537
  br i1 %cmp8, label %if.then, label %if.end13, !dbg !538

if.then:                                          ; preds = %lor.lhs.false6, %lor.lhs.false, %entry
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !540
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 3, !dbg !542
  %8 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !542
  %archive9 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !543
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive9, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i32 0, i32 0)), !dbg !544
  %9 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !545
  %cmp10 = icmp ne %struct.program_filter* %9, null, !dbg !547
  br i1 %cmp10, label %if.then11, label %if.end, !dbg !548

if.then11:                                        ; preds = %if.then
  %10 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !549
  %description12 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %10, i32 0, i32 0, !dbg !551
  call void @archive_string_free(%struct.archive_string* %description12), !dbg !552
  %11 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !553
  %12 = bitcast %struct.program_filter* %11 to i8*, !dbg !553
  call void @free(i8* %12) #7, !dbg !554
  br label %if.end, !dbg !555

if.end:                                           ; preds = %if.then11, %if.then
  %13 = load i8*, i8** %out_buf, align 8, !dbg !556
  call void @free(i8* %13) #7, !dbg !557
  store i32 -30, i32* %retval, align 4, !dbg !558
  br label %return, !dbg !558

if.end13:                                         ; preds = %lor.lhs.false6
  %14 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !559
  %description14 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %14, i32 0, i32 0, !dbg !559
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %description14, i32 0, i32 1, !dbg !559
  store i64 0, i64* %length, align 8, !dbg !559
  %15 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !559
  %description15 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %15, i32 0, i32 0, !dbg !559
  %16 = load i8*, i8** %prefix, align 8, !dbg !559
  %17 = load i8*, i8** %prefix, align 8, !dbg !559
  %cmp16 = icmp eq i8* %17, null, !dbg !559
  br i1 %cmp16, label %cond.true, label %cond.false, !dbg !559

cond.true:                                        ; preds = %if.end13
  br label %cond.end, !dbg !560

cond.false:                                       ; preds = %if.end13
  %18 = load i8*, i8** %prefix, align 8, !dbg !561
  %call17 = call i64 @strlen(i8* %18) #8, !dbg !561
  br label %cond.end, !dbg !561

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call17, %cond.false ], !dbg !562
  %call18 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %description15, i8* %16, i64 %cond), !dbg !562
  %19 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !564
  %description19 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %19, i32 0, i32 0, !dbg !565
  %20 = load i8*, i8** %cmd.addr, align 8, !dbg !566
  %call20 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %description19, i8* %20), !dbg !567
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !568
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %21, i32 0, i32 12, !dbg !569
  store i32 4, i32* %code, align 8, !dbg !570
  %22 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !571
  %description21 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %22, i32 0, i32 0, !dbg !572
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %description21, i32 0, i32 0, !dbg !573
  %23 = load i8*, i8** %s, align 8, !dbg !573
  %24 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !574
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %24, i32 0, i32 11, !dbg !575
  store i8* %23, i8** %name, align 8, !dbg !576
  %25 = load i8*, i8** %out_buf, align 8, !dbg !577
  %26 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !578
  %out_buf22 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %26, i32 0, i32 6, !dbg !579
  store i8* %25, i8** %out_buf22, align 8, !dbg !580
  %27 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !581
  %out_buf_len = getelementptr inbounds %struct.program_filter, %struct.program_filter* %27, i32 0, i32 7, !dbg !582
  store i64 65536, i64* %out_buf_len, align 8, !dbg !583
  %28 = load i8*, i8** %cmd.addr, align 8, !dbg !584
  %29 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !585
  %child_stdin = getelementptr inbounds %struct.program_filter, %struct.program_filter* %29, i32 0, i32 4, !dbg !586
  %30 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !587
  %child_stdout = getelementptr inbounds %struct.program_filter, %struct.program_filter* %30, i32 0, i32 5, !dbg !588
  %call23 = call i32 @__archive_create_child(i8* %28, i32* %child_stdin, i32* %child_stdout), !dbg !589
  store i32 %call23, i32* %child, align 4, !dbg !590
  %31 = load i32, i32* %child, align 4, !dbg !591
  %cmp24 = icmp eq i32 %31, -1, !dbg !593
  br i1 %cmp24, label %if.then25, label %if.end30, !dbg !594

if.then25:                                        ; preds = %cond.end
  %32 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !595
  %out_buf26 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %32, i32 0, i32 6, !dbg !597
  %33 = load i8*, i8** %out_buf26, align 8, !dbg !597
  call void @free(i8* %33) #7, !dbg !598
  %34 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !599
  %description27 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %34, i32 0, i32 0, !dbg !600
  call void @archive_string_free(%struct.archive_string* %description27), !dbg !601
  %35 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !602
  %36 = bitcast %struct.program_filter* %35 to i8*, !dbg !602
  call void @free(i8* %36) #7, !dbg !603
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !604
  %archive28 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %37, i32 0, i32 3, !dbg !605
  %38 = load %struct.archive_read*, %struct.archive_read** %archive28, align 8, !dbg !605
  %archive29 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %38, i32 0, i32 0, !dbg !606
  %39 = load i8*, i8** %cmd.addr, align 8, !dbg !607
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive29, i32 22, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.3, i32 0, i32 0), i8* %39), !dbg !608
  store i32 -30, i32* %retval, align 4, !dbg !609
  br label %return, !dbg !609

if.end30:                                         ; preds = %cond.end
  %40 = load i32, i32* %child, align 4, !dbg !610
  %41 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !611
  %child31 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %41, i32 0, i32 1, !dbg !612
  store i32 %40, i32* %child31, align 8, !dbg !613
  %42 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !614
  %43 = bitcast %struct.program_filter* %42 to i8*, !dbg !614
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !615
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %44, i32 0, i32 10, !dbg !616
  store i8* %43, i8** %data, align 8, !dbg !617
  %45 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !618
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %45, i32 0, i32 5, !dbg !619
  store i64 (%struct.archive_read_filter*, i8**)* @program_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !620
  %46 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !621
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %46, i32 0, i32 6, !dbg !622
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !623
  %47 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !624
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %47, i32 0, i32 8, !dbg !625
  store i32 (%struct.archive_read_filter*)* @program_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !626
  store i32 0, i32* %retval, align 4, !dbg !627
  br label %return, !dbg !627

return:                                           ; preds = %if.end30, %if.then25, %if.end
  %48 = load i32, i32* %retval, align 4, !dbg !628
  ret i32 %48, !dbg !628
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare void @archive_string_free(%struct.archive_string*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare i32 @__archive_create_child(i8*, i32*, i32*) #2

; Function Attrs: nounwind uwtable
define internal i64 @program_filter_read(%struct.archive_read_filter* %self, i8** %buff) #0 !dbg !335 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %buff.addr = alloca i8**, align 8
  %state = alloca %struct.program_filter*, align 8
  %bytes = alloca i64, align 8
  %total = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !629, metadata !350), !dbg !630
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !631, metadata !350), !dbg !632
  call void @llvm.dbg.declare(metadata %struct.program_filter** %state, metadata !633, metadata !350), !dbg !634
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !635, metadata !350), !dbg !636
  call void @llvm.dbg.declare(metadata i64* %total, metadata !637, metadata !350), !dbg !638
  call void @llvm.dbg.declare(metadata i8** %p, metadata !639, metadata !350), !dbg !640
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !641
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !642
  %1 = load i8*, i8** %data, align 8, !dbg !642
  %2 = bitcast i8* %1 to %struct.program_filter*, !dbg !643
  store %struct.program_filter* %2, %struct.program_filter** %state, align 8, !dbg !644
  store i64 0, i64* %total, align 8, !dbg !645
  %3 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !646
  %out_buf = getelementptr inbounds %struct.program_filter, %struct.program_filter* %3, i32 0, i32 6, !dbg !647
  %4 = load i8*, i8** %out_buf, align 8, !dbg !647
  store i8* %4, i8** %p, align 8, !dbg !648
  br label %while.cond, !dbg !649

while.cond:                                       ; preds = %if.end6, %entry
  %5 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !650
  %child_stdout = getelementptr inbounds %struct.program_filter, %struct.program_filter* %5, i32 0, i32 5, !dbg !652
  %6 = load i32, i32* %child_stdout, align 8, !dbg !652
  %cmp = icmp ne i32 %6, -1, !dbg !653
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !654

land.rhs:                                         ; preds = %while.cond
  %7 = load i64, i64* %total, align 8, !dbg !655
  %8 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !657
  %out_buf_len = getelementptr inbounds %struct.program_filter, %struct.program_filter* %8, i32 0, i32 7, !dbg !658
  %9 = load i64, i64* %out_buf_len, align 8, !dbg !658
  %cmp1 = icmp ult i64 %7, %9, !dbg !659
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %10 = phi i1 [ false, %while.cond ], [ %cmp1, %land.rhs ]
  br i1 %10, label %while.body, label %while.end, !dbg !660

while.body:                                       ; preds = %land.end
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !662
  %12 = load i8*, i8** %p, align 8, !dbg !664
  %13 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !665
  %out_buf_len2 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %13, i32 0, i32 7, !dbg !666
  %14 = load i64, i64* %out_buf_len2, align 8, !dbg !666
  %15 = load i64, i64* %total, align 8, !dbg !667
  %sub = sub i64 %14, %15, !dbg !668
  %call = call i64 @child_read(%struct.archive_read_filter* %11, i8* %12, i64 %sub), !dbg !669
  store i64 %call, i64* %bytes, align 8, !dbg !670
  %16 = load i64, i64* %bytes, align 8, !dbg !671
  %cmp3 = icmp slt i64 %16, 0, !dbg !673
  br i1 %cmp3, label %if.then, label %if.end, !dbg !674

if.then:                                          ; preds = %while.body
  store i64 -30, i64* %retval, align 8, !dbg !675
  br label %return, !dbg !675

if.end:                                           ; preds = %while.body
  %17 = load i64, i64* %bytes, align 8, !dbg !676
  %cmp4 = icmp eq i64 %17, 0, !dbg !678
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !679

if.then5:                                         ; preds = %if.end
  br label %while.end, !dbg !680

if.end6:                                          ; preds = %if.end
  %18 = load i64, i64* %bytes, align 8, !dbg !681
  %19 = load i64, i64* %total, align 8, !dbg !682
  %add = add i64 %19, %18, !dbg !682
  store i64 %add, i64* %total, align 8, !dbg !682
  %20 = load i64, i64* %bytes, align 8, !dbg !683
  %21 = load i8*, i8** %p, align 8, !dbg !684
  %add.ptr = getelementptr inbounds i8, i8* %21, i64 %20, !dbg !684
  store i8* %add.ptr, i8** %p, align 8, !dbg !684
  br label %while.cond, !dbg !685

while.end:                                        ; preds = %if.then5, %land.end
  %22 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !687
  %out_buf7 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %22, i32 0, i32 6, !dbg !688
  %23 = load i8*, i8** %out_buf7, align 8, !dbg !688
  %24 = load i8**, i8*** %buff.addr, align 8, !dbg !689
  store i8* %23, i8** %24, align 8, !dbg !690
  %25 = load i64, i64* %total, align 8, !dbg !691
  store i64 %25, i64* %retval, align 8, !dbg !692
  br label %return, !dbg !692

return:                                           ; preds = %while.end, %if.then
  %26 = load i64, i64* %retval, align 8, !dbg !693
  ret i64 %26, !dbg !693
}

; Function Attrs: nounwind uwtable
define internal i32 @program_filter_close(%struct.archive_read_filter* %self) #0 !dbg !342 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.program_filter*, align 8
  %e = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !694, metadata !350), !dbg !695
  call void @llvm.dbg.declare(metadata %struct.program_filter** %state, metadata !696, metadata !350), !dbg !697
  call void @llvm.dbg.declare(metadata i32* %e, metadata !698, metadata !350), !dbg !699
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !700
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !701
  %1 = load i8*, i8** %data, align 8, !dbg !701
  %2 = bitcast i8* %1 to %struct.program_filter*, !dbg !702
  store %struct.program_filter* %2, %struct.program_filter** %state, align 8, !dbg !703
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !704
  %4 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !705
  %call = call i32 @child_stop(%struct.archive_read_filter* %3, %struct.program_filter* %4), !dbg !706
  store i32 %call, i32* %e, align 4, !dbg !707
  %5 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !708
  %out_buf = getelementptr inbounds %struct.program_filter, %struct.program_filter* %5, i32 0, i32 6, !dbg !709
  %6 = load i8*, i8** %out_buf, align 8, !dbg !709
  call void @free(i8* %6) #7, !dbg !710
  %7 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !711
  %description = getelementptr inbounds %struct.program_filter, %struct.program_filter* %7, i32 0, i32 0, !dbg !712
  call void @archive_string_free(%struct.archive_string* %description), !dbg !713
  %8 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !714
  %9 = bitcast %struct.program_filter* %8 to i8*, !dbg !714
  call void @free(i8* %9) #7, !dbg !715
  %10 = load i32, i32* %e, align 4, !dbg !716
  ret i32 %10, !dbg !717
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define internal i32 @program_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %upstream) #0 !dbg !329 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %upstream.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.program_bidder*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !718, metadata !350), !dbg !719
  store %struct.archive_read_filter* %upstream, %struct.archive_read_filter** %upstream.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %upstream.addr, metadata !720, metadata !350), !dbg !721
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %state, metadata !722, metadata !350), !dbg !723
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !724
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %0, i32 0, i32 0, !dbg !725
  %1 = load i8*, i8** %data, align 8, !dbg !725
  %2 = bitcast i8* %1 to %struct.program_bidder*, !dbg !724
  store %struct.program_bidder* %2, %struct.program_bidder** %state, align 8, !dbg !723
  call void @llvm.dbg.declare(metadata i8** %p, metadata !726, metadata !350), !dbg !727
  %3 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !728
  %signature_len = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %3, i32 0, i32 3, !dbg !730
  %4 = load i64, i64* %signature_len, align 8, !dbg !730
  %cmp = icmp ugt i64 %4, 0, !dbg !731
  br i1 %cmp, label %if.then, label %if.end10, !dbg !732

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream.addr, align 8, !dbg !733
  %6 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !735
  %signature_len1 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %6, i32 0, i32 3, !dbg !736
  %7 = load i64, i64* %signature_len1, align 8, !dbg !736
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %5, i64 %7, i64* null), !dbg !737
  store i8* %call, i8** %p, align 8, !dbg !738
  %8 = load i8*, i8** %p, align 8, !dbg !739
  %cmp2 = icmp eq i8* %8, null, !dbg !741
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !742

if.then3:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !743
  br label %return, !dbg !743

if.end:                                           ; preds = %if.then
  %9 = load i8*, i8** %p, align 8, !dbg !744
  %10 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !746
  %signature = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %10, i32 0, i32 2, !dbg !747
  %11 = load i8*, i8** %signature, align 8, !dbg !747
  %12 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !748
  %signature_len4 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %12, i32 0, i32 3, !dbg !749
  %13 = load i64, i64* %signature_len4, align 8, !dbg !749
  %call5 = call i32 @memcmp(i8* %9, i8* %11, i64 %13) #8, !dbg !750
  %cmp6 = icmp ne i32 %call5, 0, !dbg !751
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !752

if.then7:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !753
  br label %return, !dbg !753

if.end8:                                          ; preds = %if.end
  %14 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !754
  %signature_len9 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %14, i32 0, i32 3, !dbg !755
  %15 = load i64, i64* %signature_len9, align 8, !dbg !755
  %conv = trunc i64 %15 to i32, !dbg !756
  %mul = mul nsw i32 %conv, 8, !dbg !757
  store i32 %mul, i32* %retval, align 4, !dbg !758
  br label %return, !dbg !758

if.end10:                                         ; preds = %entry
  %16 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !759
  %inhibit = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %16, i32 0, i32 4, !dbg !761
  %17 = load i32, i32* %inhibit, align 8, !dbg !761
  %tobool = icmp ne i32 %17, 0, !dbg !759
  br i1 %tobool, label %if.then11, label %if.end12, !dbg !762

if.then11:                                        ; preds = %if.end10
  store i32 0, i32* %retval, align 4, !dbg !763
  br label %return, !dbg !763

if.end12:                                         ; preds = %if.end10
  %18 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !764
  %inhibit13 = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %18, i32 0, i32 4, !dbg !765
  store i32 1, i32* %inhibit13, align 8, !dbg !766
  store i32 2147483647, i32* %retval, align 4, !dbg !767
  br label %return, !dbg !767

return:                                           ; preds = %if.end12, %if.then11, %if.end8, %if.then7, %if.then3
  %19 = load i32, i32* %retval, align 4, !dbg !768
  ret i32 %19, !dbg !768
}

; Function Attrs: nounwind uwtable
define internal i32 @program_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !330 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %bidder_state = alloca %struct.program_bidder*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !769, metadata !350), !dbg !770
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %bidder_state, metadata !771, metadata !350), !dbg !772
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !773
  %bidder = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 1, !dbg !774
  %1 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !774
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %1, i32 0, i32 0, !dbg !775
  %2 = load i8*, i8** %data, align 8, !dbg !775
  %3 = bitcast i8* %2 to %struct.program_bidder*, !dbg !776
  store %struct.program_bidder* %3, %struct.program_bidder** %bidder_state, align 8, !dbg !777
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !778
  %5 = load %struct.program_bidder*, %struct.program_bidder** %bidder_state, align 8, !dbg !779
  %cmd = getelementptr inbounds %struct.program_bidder, %struct.program_bidder* %5, i32 0, i32 1, !dbg !780
  %6 = load i8*, i8** %cmd, align 8, !dbg !780
  %call = call i32 @__archive_read_program(%struct.archive_read_filter* %4, i8* %6), !dbg !781
  ret i32 %call, !dbg !782
}

; Function Attrs: nounwind uwtable
define internal i32 @program_bidder_free(%struct.archive_read_filter_bidder* %self) #0 !dbg !331 {
entry:
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %state = alloca %struct.program_bidder*, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !783, metadata !350), !dbg !784
  call void @llvm.dbg.declare(metadata %struct.program_bidder** %state, metadata !785, metadata !350), !dbg !786
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !787
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %0, i32 0, i32 0, !dbg !788
  %1 = load i8*, i8** %data, align 8, !dbg !788
  %2 = bitcast i8* %1 to %struct.program_bidder*, !dbg !789
  store %struct.program_bidder* %2, %struct.program_bidder** %state, align 8, !dbg !786
  %3 = load %struct.program_bidder*, %struct.program_bidder** %state, align 8, !dbg !790
  call void @free_state(%struct.program_bidder* %3), !dbg !791
  ret i32 0, !dbg !792
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i64 @child_read(%struct.archive_read_filter* %self, i8* %buf, i64 %buf_len) #0 !dbg !336 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %buf.addr = alloca i8*, align 8
  %buf_len.addr = alloca i64, align 8
  %state = alloca %struct.program_filter*, align 8
  %ret = alloca i64, align 8
  %requested = alloca i64, align 8
  %avail = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !793, metadata !350), !dbg !794
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !795, metadata !350), !dbg !796
  store i64 %buf_len, i64* %buf_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %buf_len.addr, metadata !797, metadata !350), !dbg !798
  call void @llvm.dbg.declare(metadata %struct.program_filter** %state, metadata !799, metadata !350), !dbg !800
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !801
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !802
  %1 = load i8*, i8** %data, align 8, !dbg !802
  %2 = bitcast i8* %1 to %struct.program_filter*, !dbg !801
  store %struct.program_filter* %2, %struct.program_filter** %state, align 8, !dbg !800
  call void @llvm.dbg.declare(metadata i64* %ret, metadata !803, metadata !350), !dbg !804
  call void @llvm.dbg.declare(metadata i64* %requested, metadata !805, metadata !350), !dbg !806
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !807, metadata !350), !dbg !808
  call void @llvm.dbg.declare(metadata i8** %p, metadata !809, metadata !350), !dbg !810
  %3 = load i64, i64* %buf_len.addr, align 8, !dbg !811
  %cmp = icmp ugt i64 %3, 9223372036854775807, !dbg !812
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !811

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !813

cond.false:                                       ; preds = %entry
  %4 = load i64, i64* %buf_len.addr, align 8, !dbg !815
  br label %cond.end, !dbg !817

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 9223372036854775807, %cond.true ], [ %4, %cond.false ], !dbg !818
  store i64 %cond, i64* %requested, align 8, !dbg !820
  br label %for.cond, !dbg !821

for.cond:                                         ; preds = %if.end81, %if.end38, %if.then22, %cond.end
  br label %do.body, !dbg !822

do.body:                                          ; preds = %land.end, %for.cond
  %5 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !826
  %child_stdout = getelementptr inbounds %struct.program_filter, %struct.program_filter* %5, i32 0, i32 5, !dbg !828
  %6 = load i32, i32* %child_stdout, align 8, !dbg !828
  %7 = load i8*, i8** %buf.addr, align 8, !dbg !829
  %8 = load i64, i64* %requested, align 8, !dbg !830
  %call = call i64 @read(i32 %6, i8* %7, i64 %8), !dbg !831
  store i64 %call, i64* %ret, align 8, !dbg !832
  br label %do.cond, !dbg !833

do.cond:                                          ; preds = %do.body
  %9 = load i64, i64* %ret, align 8, !dbg !834
  %cmp1 = icmp eq i64 %9, -1, !dbg !836
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !837

land.rhs:                                         ; preds = %do.cond
  %call2 = call i32* @__errno_location() #1, !dbg !838
  %10 = load i32, i32* %call2, align 4, !dbg !838
  %cmp3 = icmp eq i32 %10, 4, !dbg !840
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %11 = phi i1 [ false, %do.cond ], [ %cmp3, %land.rhs ]
  br i1 %11, label %do.body, label %do.end, !dbg !841

do.end:                                           ; preds = %land.end
  %12 = load i64, i64* %ret, align 8, !dbg !843
  %cmp4 = icmp sgt i64 %12, 0, !dbg !845
  br i1 %cmp4, label %if.then, label %if.end, !dbg !846

if.then:                                          ; preds = %do.end
  %13 = load i64, i64* %ret, align 8, !dbg !847
  store i64 %13, i64* %retval, align 8, !dbg !848
  br label %return, !dbg !848

if.end:                                           ; preds = %do.end
  %14 = load i64, i64* %ret, align 8, !dbg !849
  %cmp5 = icmp eq i64 %14, 0, !dbg !851
  br i1 %cmp5, label %if.then9, label %lor.lhs.false, !dbg !852

lor.lhs.false:                                    ; preds = %if.end
  %15 = load i64, i64* %ret, align 8, !dbg !853
  %cmp6 = icmp eq i64 %15, -1, !dbg !855
  br i1 %cmp6, label %land.lhs.true, label %if.end11, !dbg !856

land.lhs.true:                                    ; preds = %lor.lhs.false
  %call7 = call i32* @__errno_location() #1, !dbg !857
  %16 = load i32, i32* %call7, align 4, !dbg !857
  %cmp8 = icmp eq i32 %16, 32, !dbg !859
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !860

if.then9:                                         ; preds = %land.lhs.true, %if.end
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !861
  %18 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !862
  %call10 = call i32 @child_stop(%struct.archive_read_filter* %17, %struct.program_filter* %18), !dbg !863
  %conv = sext i32 %call10 to i64, !dbg !864
  store i64 %conv, i64* %retval, align 8, !dbg !865
  br label %return, !dbg !865

if.end11:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %19 = load i64, i64* %ret, align 8, !dbg !866
  %cmp12 = icmp eq i64 %19, -1, !dbg !868
  br i1 %cmp12, label %land.lhs.true14, label %if.end19, !dbg !869

land.lhs.true14:                                  ; preds = %if.end11
  %call15 = call i32* @__errno_location() #1, !dbg !870
  %20 = load i32, i32* %call15, align 4, !dbg !870
  %cmp16 = icmp ne i32 %20, 11, !dbg !872
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !873

if.then18:                                        ; preds = %land.lhs.true14
  store i64 -1, i64* %retval, align 8, !dbg !874
  br label %return, !dbg !874

if.end19:                                         ; preds = %land.lhs.true14, %if.end11
  %21 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !875
  %child_stdin = getelementptr inbounds %struct.program_filter, %struct.program_filter* %21, i32 0, i32 4, !dbg !877
  %22 = load i32, i32* %child_stdin, align 4, !dbg !877
  %cmp20 = icmp eq i32 %22, -1, !dbg !878
  br i1 %cmp20, label %if.then22, label %if.end25, !dbg !879

if.then22:                                        ; preds = %if.end19
  %23 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !880
  %child_stdin23 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %23, i32 0, i32 4, !dbg !882
  %24 = load i32, i32* %child_stdin23, align 4, !dbg !882
  %25 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !883
  %child_stdout24 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %25, i32 0, i32 5, !dbg !884
  %26 = load i32, i32* %child_stdout24, align 8, !dbg !884
  call void @__archive_check_child(i32 %24, i32 %26), !dbg !885
  br label %for.cond, !dbg !886

if.end25:                                         ; preds = %if.end19
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !887
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %27, i32 0, i32 2, !dbg !888
  %28 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !888
  %call26 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %28, i64 1, i64* %avail), !dbg !889
  store i8* %call26, i8** %p, align 8, !dbg !890
  %29 = load i8*, i8** %p, align 8, !dbg !891
  %cmp27 = icmp eq i8* %29, null, !dbg !893
  br i1 %cmp27, label %if.then29, label %if.end39, !dbg !894

if.then29:                                        ; preds = %if.end25
  %30 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !895
  %child_stdin30 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %30, i32 0, i32 4, !dbg !897
  %31 = load i32, i32* %child_stdin30, align 4, !dbg !897
  %call31 = call i32 @close(i32 %31), !dbg !898
  %32 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !899
  %child_stdin32 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %32, i32 0, i32 4, !dbg !900
  store i32 -1, i32* %child_stdin32, align 4, !dbg !901
  %33 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !902
  %child_stdout33 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %33, i32 0, i32 5, !dbg !903
  %34 = load i32, i32* %child_stdout33, align 8, !dbg !903
  %call34 = call i32 (i32, i32, ...) @fcntl(i32 %34, i32 4, i32 0), !dbg !904
  %35 = load i64, i64* %avail, align 8, !dbg !905
  %cmp35 = icmp slt i64 %35, 0, !dbg !907
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !908

if.then37:                                        ; preds = %if.then29
  %36 = load i64, i64* %avail, align 8, !dbg !909
  store i64 %36, i64* %retval, align 8, !dbg !910
  br label %return, !dbg !910

if.end38:                                         ; preds = %if.then29
  br label %for.cond, !dbg !911

if.end39:                                         ; preds = %if.end25
  br label %do.body40, !dbg !912

do.body40:                                        ; preds = %land.end50, %if.end39
  %37 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !913
  %child_stdin41 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %37, i32 0, i32 4, !dbg !915
  %38 = load i32, i32* %child_stdin41, align 4, !dbg !915
  %39 = load i8*, i8** %p, align 8, !dbg !916
  %40 = load i64, i64* %avail, align 8, !dbg !917
  %call42 = call i64 @write(i32 %38, i8* %39, i64 %40), !dbg !918
  store i64 %call42, i64* %ret, align 8, !dbg !919
  br label %do.cond43, !dbg !920

do.cond43:                                        ; preds = %do.body40
  %41 = load i64, i64* %ret, align 8, !dbg !921
  %cmp44 = icmp eq i64 %41, -1, !dbg !922
  br i1 %cmp44, label %land.rhs46, label %land.end50, !dbg !923

land.rhs46:                                       ; preds = %do.cond43
  %call47 = call i32* @__errno_location() #1, !dbg !924
  %42 = load i32, i32* %call47, align 4, !dbg !924
  %cmp48 = icmp eq i32 %42, 4, !dbg !925
  br label %land.end50

land.end50:                                       ; preds = %land.rhs46, %do.cond43
  %43 = phi i1 [ false, %do.cond43 ], [ %cmp48, %land.rhs46 ]
  br i1 %43, label %do.body40, label %do.end51, !dbg !926

do.end51:                                         ; preds = %land.end50
  %44 = load i64, i64* %ret, align 8, !dbg !928
  %cmp52 = icmp sgt i64 %44, 0, !dbg !930
  br i1 %cmp52, label %if.then54, label %if.else, !dbg !931

if.then54:                                        ; preds = %do.end51
  %45 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !932
  %upstream55 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %45, i32 0, i32 2, !dbg !934
  %46 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream55, align 8, !dbg !934
  %47 = load i64, i64* %ret, align 8, !dbg !935
  %call56 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %46, i64 %47), !dbg !936
  br label %if.end81, !dbg !937

if.else:                                          ; preds = %do.end51
  %48 = load i64, i64* %ret, align 8, !dbg !938
  %cmp57 = icmp eq i64 %48, -1, !dbg !941
  br i1 %cmp57, label %land.lhs.true59, label %if.else66, !dbg !942

land.lhs.true59:                                  ; preds = %if.else
  %call60 = call i32* @__errno_location() #1, !dbg !943
  %49 = load i32, i32* %call60, align 4, !dbg !943
  %cmp61 = icmp eq i32 %49, 11, !dbg !945
  br i1 %cmp61, label %if.then63, label %if.else66, !dbg !946

if.then63:                                        ; preds = %land.lhs.true59
  %50 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !947
  %child_stdin64 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %50, i32 0, i32 4, !dbg !949
  %51 = load i32, i32* %child_stdin64, align 4, !dbg !949
  %52 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !950
  %child_stdout65 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %52, i32 0, i32 5, !dbg !951
  %53 = load i32, i32* %child_stdout65, align 8, !dbg !951
  call void @__archive_check_child(i32 %51, i32 %53), !dbg !952
  br label %if.end80, !dbg !953

if.else66:                                        ; preds = %land.lhs.true59, %if.else
  %54 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !954
  %child_stdin67 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %54, i32 0, i32 4, !dbg !956
  %55 = load i32, i32* %child_stdin67, align 4, !dbg !956
  %call68 = call i32 @close(i32 %55), !dbg !957
  %56 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !958
  %child_stdin69 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %56, i32 0, i32 4, !dbg !959
  store i32 -1, i32* %child_stdin69, align 4, !dbg !960
  %57 = load %struct.program_filter*, %struct.program_filter** %state, align 8, !dbg !961
  %child_stdout70 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %57, i32 0, i32 5, !dbg !962
  %58 = load i32, i32* %child_stdout70, align 8, !dbg !962
  %call71 = call i32 (i32, i32, ...) @fcntl(i32 %58, i32 4, i32 0), !dbg !963
  %59 = load i64, i64* %ret, align 8, !dbg !964
  %cmp72 = icmp eq i64 %59, -1, !dbg !966
  br i1 %cmp72, label %land.lhs.true74, label %if.end79, !dbg !967

land.lhs.true74:                                  ; preds = %if.else66
  %call75 = call i32* @__errno_location() #1, !dbg !968
  %60 = load i32, i32* %call75, align 4, !dbg !968
  %cmp76 = icmp ne i32 %60, 32, !dbg !970
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !971

if.then78:                                        ; preds = %land.lhs.true74
  store i64 -1, i64* %retval, align 8, !dbg !972
  br label %return, !dbg !972

if.end79:                                         ; preds = %land.lhs.true74, %if.else66
  br label %if.end80

if.end80:                                         ; preds = %if.end79, %if.then63
  br label %if.end81

if.end81:                                         ; preds = %if.end80, %if.then54
  br label %for.cond, !dbg !973

return:                                           ; preds = %if.then78, %if.then37, %if.then18, %if.then9, %if.then
  %61 = load i64, i64* %retval, align 8, !dbg !975
  ret i64 %61, !dbg !975
}

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

; Function Attrs: nounwind uwtable
define internal i32 @child_stop(%struct.archive_read_filter* %self, %struct.program_filter* %state) #0 !dbg !339 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state.addr = alloca %struct.program_filter*, align 8
  %.compoundliteral = alloca %union.anon, align 4
  %.compoundliteral29 = alloca %union.anon.0, align 4
  %.compoundliteral40 = alloca %union.anon.1, align 4
  %.compoundliteral46 = alloca %union.anon.2, align 4
  %.compoundliteral54 = alloca %union.anon.3, align 4
  %.compoundliteral66 = alloca %union.anon.4, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !976, metadata !350), !dbg !977
  store %struct.program_filter* %state, %struct.program_filter** %state.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.program_filter** %state.addr, metadata !978, metadata !350), !dbg !979
  %0 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !980
  %child_stdin = getelementptr inbounds %struct.program_filter, %struct.program_filter* %0, i32 0, i32 4, !dbg !982
  %1 = load i32, i32* %child_stdin, align 4, !dbg !982
  %cmp = icmp ne i32 %1, -1, !dbg !983
  br i1 %cmp, label %if.then, label %if.end, !dbg !984

if.then:                                          ; preds = %entry
  %2 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !985
  %child_stdin1 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %2, i32 0, i32 4, !dbg !987
  %3 = load i32, i32* %child_stdin1, align 4, !dbg !987
  %call = call i32 @close(i32 %3), !dbg !988
  %4 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !989
  %child_stdin2 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %4, i32 0, i32 4, !dbg !990
  store i32 -1, i32* %child_stdin2, align 4, !dbg !991
  br label %if.end, !dbg !992

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !993
  %child_stdout = getelementptr inbounds %struct.program_filter, %struct.program_filter* %5, i32 0, i32 5, !dbg !995
  %6 = load i32, i32* %child_stdout, align 8, !dbg !995
  %cmp3 = icmp ne i32 %6, -1, !dbg !996
  br i1 %cmp3, label %if.then4, label %if.end8, !dbg !997

if.then4:                                         ; preds = %if.end
  %7 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !998
  %child_stdout5 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %7, i32 0, i32 5, !dbg !1000
  %8 = load i32, i32* %child_stdout5, align 8, !dbg !1000
  %call6 = call i32 @close(i32 %8), !dbg !1001
  %9 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1002
  %child_stdout7 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %9, i32 0, i32 5, !dbg !1003
  store i32 -1, i32* %child_stdout7, align 8, !dbg !1004
  br label %if.end8, !dbg !1005

if.end8:                                          ; preds = %if.then4, %if.end
  %10 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1006
  %child = getelementptr inbounds %struct.program_filter, %struct.program_filter* %10, i32 0, i32 1, !dbg !1008
  %11 = load i32, i32* %child, align 8, !dbg !1008
  %cmp9 = icmp ne i32 %11, 0, !dbg !1009
  br i1 %cmp9, label %if.then10, label %if.end18, !dbg !1010

if.then10:                                        ; preds = %if.end8
  br label %do.body, !dbg !1011

do.body:                                          ; preds = %land.end, %if.then10
  %12 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1013
  %child11 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %12, i32 0, i32 1, !dbg !1015
  %13 = load i32, i32* %child11, align 8, !dbg !1015
  %14 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1016
  %exit_status = getelementptr inbounds %struct.program_filter, %struct.program_filter* %14, i32 0, i32 2, !dbg !1017
  %call12 = call i32 @waitpid(i32 %13, i32* %exit_status, i32 0), !dbg !1018
  %15 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1019
  %waitpid_return = getelementptr inbounds %struct.program_filter, %struct.program_filter* %15, i32 0, i32 3, !dbg !1020
  store i32 %call12, i32* %waitpid_return, align 8, !dbg !1021
  br label %do.cond, !dbg !1022

do.cond:                                          ; preds = %do.body
  %16 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1023
  %waitpid_return13 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %16, i32 0, i32 3, !dbg !1025
  %17 = load i32, i32* %waitpid_return13, align 8, !dbg !1025
  %cmp14 = icmp eq i32 %17, -1, !dbg !1026
  br i1 %cmp14, label %land.rhs, label %land.end, !dbg !1027

land.rhs:                                         ; preds = %do.cond
  %call15 = call i32* @__errno_location() #1, !dbg !1028
  %18 = load i32, i32* %call15, align 4, !dbg !1028
  %cmp16 = icmp eq i32 %18, 4, !dbg !1030
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %19 = phi i1 [ false, %do.cond ], [ %cmp16, %land.rhs ]
  br i1 %19, label %do.body, label %do.end, !dbg !1031

do.end:                                           ; preds = %land.end
  %20 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1033
  %child17 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %20, i32 0, i32 1, !dbg !1034
  store i32 0, i32* %child17, align 8, !dbg !1035
  br label %if.end18, !dbg !1036

if.end18:                                         ; preds = %do.end, %if.end8
  %21 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1037
  %waitpid_return19 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %21, i32 0, i32 3, !dbg !1039
  %22 = load i32, i32* %waitpid_return19, align 8, !dbg !1039
  %cmp20 = icmp slt i32 %22, 0, !dbg !1040
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !1041

if.then21:                                        ; preds = %if.end18
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1042
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 3, !dbg !1044
  %24 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1044
  %archive22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 0, !dbg !1045
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive22, i32 -1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.4, i32 0, i32 0)), !dbg !1046
  store i32 -20, i32* %retval, align 4, !dbg !1047
  br label %return, !dbg !1047

if.end23:                                         ; preds = %if.end18
  %__in = bitcast %union.anon* %.compoundliteral to i32*, !dbg !1048
  %25 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1048
  %exit_status24 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %25, i32 0, i32 2, !dbg !1048
  %26 = load i32, i32* %exit_status24, align 4, !dbg !1048
  store i32 %26, i32* %__in, align 4, !dbg !1048
  %__i = bitcast %union.anon* %.compoundliteral to i32*, !dbg !1048
  %27 = load i32, i32* %__i, align 4, !dbg !1048
  %and = and i32 %27, 127, !dbg !1048
  %add = add nsw i32 %and, 1, !dbg !1048
  %conv = trunc i32 %add to i8, !dbg !1048
  %conv25 = sext i8 %conv to i32, !dbg !1048
  %shr = ashr i32 %conv25, 1, !dbg !1048
  %cmp26 = icmp sgt i32 %shr, 0, !dbg !1048
  br i1 %cmp26, label %if.then28, label %if.end45, !dbg !1050

if.then28:                                        ; preds = %if.end23
  %__in30 = bitcast %union.anon.0* %.compoundliteral29 to i32*, !dbg !1051
  %28 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1051
  %exit_status31 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %28, i32 0, i32 2, !dbg !1051
  %29 = load i32, i32* %exit_status31, align 4, !dbg !1051
  store i32 %29, i32* %__in30, align 4, !dbg !1051
  %__i32 = bitcast %union.anon.0* %.compoundliteral29 to i32*, !dbg !1051
  %30 = load i32, i32* %__i32, align 4, !dbg !1051
  %and33 = and i32 %30, 127, !dbg !1051
  %cmp34 = icmp eq i32 %and33, 13, !dbg !1054
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1055

if.then36:                                        ; preds = %if.then28
  store i32 0, i32* %retval, align 4, !dbg !1056
  br label %return, !dbg !1056

if.end37:                                         ; preds = %if.then28
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1057
  %archive38 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %31, i32 0, i32 3, !dbg !1058
  %32 = load %struct.archive_read*, %struct.archive_read** %archive38, align 8, !dbg !1058
  %archive39 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 0, !dbg !1059
  %__in41 = bitcast %union.anon.1* %.compoundliteral40 to i32*, !dbg !1060
  %33 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1060
  %exit_status42 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %33, i32 0, i32 2, !dbg !1060
  %34 = load i32, i32* %exit_status42, align 4, !dbg !1060
  store i32 %34, i32* %__in41, align 4, !dbg !1060
  %__i43 = bitcast %union.anon.1* %.compoundliteral40 to i32*, !dbg !1060
  %35 = load i32, i32* %__i43, align 4, !dbg !1060
  %and44 = and i32 %35, 127, !dbg !1060
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive39, i32 -1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i32 0, i32 0), i32 %and44), !dbg !1061
  store i32 -20, i32* %retval, align 4, !dbg !1062
  br label %return, !dbg !1062

if.end45:                                         ; preds = %if.end23
  %__in47 = bitcast %union.anon.2* %.compoundliteral46 to i32*, !dbg !1063
  %36 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1063
  %exit_status48 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %36, i32 0, i32 2, !dbg !1063
  %37 = load i32, i32* %exit_status48, align 4, !dbg !1063
  store i32 %37, i32* %__in47, align 4, !dbg !1063
  %__i49 = bitcast %union.anon.2* %.compoundliteral46 to i32*, !dbg !1063
  %38 = load i32, i32* %__i49, align 4, !dbg !1063
  %and50 = and i32 %38, 127, !dbg !1063
  %cmp51 = icmp eq i32 %and50, 0, !dbg !1063
  br i1 %cmp51, label %if.then53, label %if.end72, !dbg !1065

if.then53:                                        ; preds = %if.end45
  %__in55 = bitcast %union.anon.3* %.compoundliteral54 to i32*, !dbg !1066
  %39 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1066
  %exit_status56 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %39, i32 0, i32 2, !dbg !1066
  %40 = load i32, i32* %exit_status56, align 4, !dbg !1066
  store i32 %40, i32* %__in55, align 4, !dbg !1066
  %__i57 = bitcast %union.anon.3* %.compoundliteral54 to i32*, !dbg !1066
  %41 = load i32, i32* %__i57, align 4, !dbg !1066
  %and58 = and i32 %41, 65280, !dbg !1066
  %shr59 = ashr i32 %and58, 8, !dbg !1066
  %cmp60 = icmp eq i32 %shr59, 0, !dbg !1069
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !1070

if.then62:                                        ; preds = %if.then53
  store i32 0, i32* %retval, align 4, !dbg !1071
  br label %return, !dbg !1071

if.end63:                                         ; preds = %if.then53
  %42 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1072
  %archive64 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %42, i32 0, i32 3, !dbg !1073
  %43 = load %struct.archive_read*, %struct.archive_read** %archive64, align 8, !dbg !1073
  %archive65 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 0, !dbg !1074
  %__in67 = bitcast %union.anon.4* %.compoundliteral66 to i32*, !dbg !1075
  %44 = load %struct.program_filter*, %struct.program_filter** %state.addr, align 8, !dbg !1075
  %exit_status68 = getelementptr inbounds %struct.program_filter, %struct.program_filter* %44, i32 0, i32 2, !dbg !1075
  %45 = load i32, i32* %exit_status68, align 4, !dbg !1075
  store i32 %45, i32* %__in67, align 4, !dbg !1075
  %__i69 = bitcast %union.anon.4* %.compoundliteral66 to i32*, !dbg !1075
  %46 = load i32, i32* %__i69, align 4, !dbg !1075
  %and70 = and i32 %46, 65280, !dbg !1075
  %shr71 = ashr i32 %and70, 8, !dbg !1075
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive65, i32 -1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.6, i32 0, i32 0), i32 %shr71), !dbg !1076
  store i32 -20, i32* %retval, align 4, !dbg !1077
  br label %return, !dbg !1077

if.end72:                                         ; preds = %if.end45
  store i32 -20, i32* %retval, align 4, !dbg !1078
  br label %return, !dbg !1078

return:                                           ; preds = %if.end72, %if.end63, %if.then62, %if.end37, %if.then36, %if.then21
  %47 = load i32, i32* %retval, align 4, !dbg !1079
  ret i32 %47, !dbg !1079
}

declare void @__archive_check_child(i32, i32) #2

declare i32 @close(i32) #2

declare i32 @fcntl(i32, i32, ...) #2

declare i64 @write(i32, i8*, i64) #2

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

declare i32 @waitpid(i32, i32*, i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!346, !347}
!llvm.ident = !{!348}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !314, globals: !343)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_program.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !291, !122, !299, !95, !23, !313}
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
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "program_bidder", file: !1, line: 90, size: 320, align: 64, elements: !293)
!293 = !{!294, !295, !296, !297, !298}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "description", scope: !292, file: !1, line: 91, baseType: !95, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "cmd", scope: !292, file: !1, line: 92, baseType: !95, size: 64, align: 64, offset: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "signature", scope: !292, file: !1, line: 93, baseType: !122, size: 64, align: 64, offset: 128)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "signature_len", scope: !292, file: !1, line: 94, baseType: !45, size: 64, align: 64, offset: 192)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "inhibit", scope: !292, file: !1, line: 95, baseType: !23, size: 32, align: 32, offset: 256)
!299 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !300, size: 64, align: 64)
!300 = !DICompositeType(tag: DW_TAG_structure_type, name: "program_filter", file: !1, line: 106, size: 512, align: 64, elements: !301)
!301 = !{!302, !303, !307, !308, !309, !310, !311, !312}
!302 = !DIDerivedType(tag: DW_TAG_member, name: "description", scope: !300, file: !1, line: 107, baseType: !91, size: 192, align: 64)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "child", scope: !300, file: !1, line: 111, baseType: !304, size: 32, align: 32, offset: 192)
!304 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !305, line: 61, baseType: !306)
!305 = !DIFile(filename: "/usr/include/signal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !41, line: 133, baseType: !23)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "exit_status", scope: !300, file: !1, line: 113, baseType: !23, size: 32, align: 32, offset: 224)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "waitpid_return", scope: !300, file: !1, line: 114, baseType: !23, size: 32, align: 32, offset: 256)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "child_stdin", scope: !300, file: !1, line: 115, baseType: !23, size: 32, align: 32, offset: 288)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "child_stdout", scope: !300, file: !1, line: 115, baseType: !23, size: 32, align: 32, offset: 320)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "out_buf", scope: !300, file: !1, line: 117, baseType: !95, size: 64, align: 64, offset: 384)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "out_buf_len", scope: !300, file: !1, line: 118, baseType: !45, size: 64, align: 64, offset: 448)
!313 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!314 = !{!315, !318, !321, !322, !323, !326, !329, !330, !331, !332, !335, !336, !339, !342}
!315 = distinct !DISubprogram(name: "archive_read_support_compression_program", scope: !1, file: !1, line: 65, type: !316, isLocal: false, isDefinition: true, scopeLine: 66, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!316 = !DISubroutineType(types: !317)
!317 = !{!23, !24, !80}
!318 = distinct !DISubprogram(name: "archive_read_support_compression_program_signature", scope: !1, file: !1, line: 71, type: !319, isLocal: false, isDefinition: true, scopeLine: 73, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!319 = !DISubroutineType(types: !320)
!320 = !{!23, !24, !80, !43, !45}
!321 = distinct !DISubprogram(name: "archive_read_support_filter_program", scope: !1, file: !1, line: 80, type: !316, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!322 = distinct !DISubprogram(name: "archive_read_support_filter_program_signature", scope: !1, file: !1, line: 149, type: !319, isLocal: false, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!323 = distinct !DISubprogram(name: "__archive_read_program", scope: !1, file: !1, line: 397, type: !324, isLocal: false, isDefinition: true, scopeLine: 398, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!324 = !DISubroutineType(types: !325)
!325 = !{!23, !169, !80}
!326 = distinct !DISubprogram(name: "set_bidder_signature", scope: !1, file: !1, line: 127, type: !327, isLocal: true, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!327 = !DISubroutineType(types: !328)
!328 = !{!23, !168, !291, !43, !45}
!329 = distinct !DISubprogram(name: "program_bidder_bid", scope: !1, file: !1, line: 206, type: !166, isLocal: true, isDefinition: true, scopeLine: 208, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = distinct !DISubprogram(name: "program_bidder_init", scope: !1, file: !1, line: 466, type: !178, isLocal: true, isDefinition: true, scopeLine: 467, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!331 = distinct !DISubprogram(name: "program_bidder_free", scope: !1, file: !1, line: 180, type: !218, isLocal: true, isDefinition: true, scopeLine: 181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = distinct !DISubprogram(name: "free_state", scope: !1, file: !1, line: 189, type: !333, isLocal: true, isDefinition: true, scopeLine: 190, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!333 = !DISubroutineType(types: !334)
!334 = !{null, !291}
!335 = distinct !DISubprogram(name: "program_filter_read", scope: !1, file: !1, line: 475, type: !182, isLocal: true, isDefinition: true, scopeLine: 476, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!336 = distinct !DISubprogram(name: "child_read", scope: !1, file: !1, line: 307, type: !337, isLocal: true, isDefinition: true, scopeLine: 308, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!337 = !DISubroutineType(types: !338)
!338 = !{!38, !169, !95, !45}
!339 = distinct !DISubprogram(name: "child_stop", scope: !1, file: !1, line: 239, type: !340, isLocal: true, isDefinition: true, scopeLine: 240, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = !DISubroutineType(types: !341)
!341 = !{!23, !169, !299}
!342 = distinct !DISubprogram(name: "program_filter_close", scope: !1, file: !1, line: 504, type: !178, isLocal: true, isDefinition: true, scopeLine: 505, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = !{!344}
!344 = !DIGlobalVariable(name: "out_buf_len", scope: !323, file: !1, line: 400, type: !345, isLocal: true, isDefinition: true, variable: i64* @__archive_read_program.out_buf_len)
!345 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!346 = !{i32 2, !"Dwarf Version", i32 4}
!347 = !{i32 2, !"Debug Info Version", i32 3}
!348 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!349 = !DILocalVariable(name: "a", arg: 1, scope: !315, file: !1, line: 65, type: !24)
!350 = !DIExpression()
!351 = !DILocation(line: 65, column: 58, scope: !315)
!352 = !DILocalVariable(name: "cmd", arg: 2, scope: !315, file: !1, line: 65, type: !80)
!353 = !DILocation(line: 65, column: 73, scope: !315)
!354 = !DILocation(line: 67, column: 45, scope: !315)
!355 = !DILocation(line: 67, column: 48, scope: !315)
!356 = !DILocation(line: 67, column: 9, scope: !315)
!357 = !DILocation(line: 67, column: 2, scope: !315)
!358 = !DILocalVariable(name: "a", arg: 1, scope: !321, file: !1, line: 80, type: !24)
!359 = !DILocation(line: 80, column: 53, scope: !321)
!360 = !DILocalVariable(name: "cmd", arg: 2, scope: !321, file: !1, line: 80, type: !80)
!361 = !DILocation(line: 80, column: 68, scope: !321)
!362 = !DILocation(line: 82, column: 56, scope: !321)
!363 = !DILocation(line: 82, column: 59, scope: !321)
!364 = !DILocation(line: 82, column: 10, scope: !321)
!365 = !DILocation(line: 82, column: 2, scope: !321)
!366 = !DILocalVariable(name: "a", arg: 1, scope: !318, file: !1, line: 71, type: !24)
!367 = !DILocation(line: 71, column: 68, scope: !318)
!368 = !DILocalVariable(name: "cmd", arg: 2, scope: !318, file: !1, line: 72, type: !80)
!369 = !DILocation(line: 72, column: 17, scope: !318)
!370 = !DILocalVariable(name: "signature", arg: 3, scope: !318, file: !1, line: 72, type: !43)
!371 = !DILocation(line: 72, column: 34, scope: !318)
!372 = !DILocalVariable(name: "signature_len", arg: 4, scope: !318, file: !1, line: 72, type: !45)
!373 = !DILocation(line: 72, column: 52, scope: !318)
!374 = !DILocation(line: 74, column: 55, scope: !318)
!375 = !DILocation(line: 75, column: 6, scope: !318)
!376 = !DILocation(line: 75, column: 11, scope: !318)
!377 = !DILocation(line: 75, column: 22, scope: !318)
!378 = !DILocation(line: 74, column: 9, scope: !318)
!379 = !DILocation(line: 74, column: 2, scope: !318)
!380 = !DILocalVariable(name: "_a", arg: 1, scope: !322, file: !1, line: 149, type: !24)
!381 = !DILocation(line: 149, column: 63, scope: !322)
!382 = !DILocalVariable(name: "cmd", arg: 2, scope: !322, file: !1, line: 150, type: !80)
!383 = !DILocation(line: 150, column: 17, scope: !322)
!384 = !DILocalVariable(name: "signature", arg: 3, scope: !322, file: !1, line: 150, type: !43)
!385 = !DILocation(line: 150, column: 34, scope: !322)
!386 = !DILocalVariable(name: "signature_len", arg: 4, scope: !322, file: !1, line: 150, type: !45)
!387 = !DILocation(line: 150, column: 52, scope: !322)
!388 = !DILocalVariable(name: "a", scope: !322, file: !1, line: 152, type: !4)
!389 = !DILocation(line: 152, column: 23, scope: !322)
!390 = !DILocation(line: 152, column: 50, scope: !322)
!391 = !DILocation(line: 152, column: 27, scope: !322)
!392 = !DILocalVariable(name: "bidder", scope: !322, file: !1, line: 153, type: !168)
!393 = !DILocation(line: 153, column: 37, scope: !322)
!394 = !DILocalVariable(name: "state", scope: !322, file: !1, line: 154, type: !291)
!395 = !DILocation(line: 154, column: 25, scope: !322)
!396 = !DILocation(line: 159, column: 32, scope: !397)
!397 = distinct !DILexicalBlock(scope: !322, file: !1, line: 159, column: 6)
!398 = !DILocation(line: 159, column: 6, scope: !397)
!399 = !DILocation(line: 159, column: 44, scope: !397)
!400 = !DILocation(line: 159, column: 6, scope: !322)
!401 = !DILocation(line: 160, column: 3, scope: !397)
!402 = !DILocation(line: 165, column: 35, scope: !322)
!403 = !DILocation(line: 165, column: 10, scope: !322)
!404 = !DILocation(line: 165, column: 8, scope: !322)
!405 = !DILocation(line: 166, column: 6, scope: !406)
!406 = distinct !DILexicalBlock(scope: !322, file: !1, line: 166, column: 6)
!407 = !DILocation(line: 166, column: 12, scope: !406)
!408 = !DILocation(line: 166, column: 6, scope: !322)
!409 = !DILocation(line: 167, column: 3, scope: !406)
!410 = !DILocation(line: 168, column: 22, scope: !322)
!411 = !DILocation(line: 168, column: 15, scope: !322)
!412 = !DILocation(line: 168, column: 2, scope: !322)
!413 = !DILocation(line: 168, column: 9, scope: !322)
!414 = !DILocation(line: 168, column: 13, scope: !322)
!415 = !DILocation(line: 169, column: 6, scope: !416)
!416 = distinct !DILexicalBlock(scope: !322, file: !1, line: 169, column: 6)
!417 = !DILocation(line: 169, column: 13, scope: !416)
!418 = !DILocation(line: 169, column: 17, scope: !416)
!419 = !DILocation(line: 169, column: 6, scope: !322)
!420 = !DILocation(line: 170, column: 3, scope: !416)
!421 = !DILocation(line: 172, column: 30, scope: !322)
!422 = !DILocation(line: 172, column: 38, scope: !322)
!423 = !DILocation(line: 172, column: 45, scope: !322)
!424 = !DILocation(line: 172, column: 56, scope: !322)
!425 = !DILocation(line: 172, column: 9, scope: !322)
!426 = !DILocation(line: 172, column: 2, scope: !322)
!427 = !DILocation(line: 174, column: 13, scope: !322)
!428 = !DILocation(line: 174, column: 2, scope: !322)
!429 = !DILocation(line: 175, column: 20, scope: !322)
!430 = !DILocation(line: 175, column: 2, scope: !322)
!431 = !DILocation(line: 176, column: 2, scope: !322)
!432 = !DILocation(line: 177, column: 1, scope: !322)
!433 = !DILocalVariable(name: "bidder", arg: 1, scope: !326, file: !1, line: 127, type: !168)
!434 = !DILocation(line: 127, column: 57, scope: !326)
!435 = !DILocalVariable(name: "state", arg: 2, scope: !326, file: !1, line: 128, type: !291)
!436 = !DILocation(line: 128, column: 28, scope: !326)
!437 = !DILocalVariable(name: "signature", arg: 3, scope: !326, file: !1, line: 128, type: !43)
!438 = !DILocation(line: 128, column: 47, scope: !326)
!439 = !DILocalVariable(name: "signature_len", arg: 4, scope: !326, file: !1, line: 128, type: !45)
!440 = !DILocation(line: 128, column: 65, scope: !326)
!441 = !DILocation(line: 131, column: 6, scope: !442)
!442 = distinct !DILexicalBlock(scope: !326, file: !1, line: 131, column: 6)
!443 = !DILocation(line: 131, column: 16, scope: !442)
!444 = !DILocation(line: 131, column: 24, scope: !442)
!445 = !DILocation(line: 131, column: 27, scope: !446)
!446 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!447 = !DILocation(line: 131, column: 41, scope: !446)
!448 = !DILocation(line: 131, column: 6, scope: !446)
!449 = !DILocation(line: 132, column: 26, scope: !450)
!450 = distinct !DILexicalBlock(scope: !442, file: !1, line: 131, column: 46)
!451 = !DILocation(line: 132, column: 3, scope: !450)
!452 = !DILocation(line: 132, column: 10, scope: !450)
!453 = !DILocation(line: 132, column: 24, scope: !450)
!454 = !DILocation(line: 133, column: 29, scope: !450)
!455 = !DILocation(line: 133, column: 22, scope: !450)
!456 = !DILocation(line: 133, column: 3, scope: !450)
!457 = !DILocation(line: 133, column: 10, scope: !450)
!458 = !DILocation(line: 133, column: 20, scope: !450)
!459 = !DILocation(line: 134, column: 10, scope: !450)
!460 = !DILocation(line: 134, column: 17, scope: !450)
!461 = !DILocation(line: 134, column: 28, scope: !450)
!462 = !DILocation(line: 134, column: 39, scope: !450)
!463 = !DILocation(line: 134, column: 3, scope: !450)
!464 = !DILocation(line: 135, column: 2, scope: !450)
!465 = !DILocation(line: 140, column: 17, scope: !326)
!466 = !DILocation(line: 140, column: 2, scope: !326)
!467 = !DILocation(line: 140, column: 10, scope: !326)
!468 = !DILocation(line: 140, column: 15, scope: !326)
!469 = !DILocation(line: 141, column: 2, scope: !326)
!470 = !DILocation(line: 141, column: 10, scope: !326)
!471 = !DILocation(line: 141, column: 14, scope: !326)
!472 = !DILocation(line: 142, column: 2, scope: !326)
!473 = !DILocation(line: 142, column: 10, scope: !326)
!474 = !DILocation(line: 142, column: 15, scope: !326)
!475 = !DILocation(line: 143, column: 2, scope: !326)
!476 = !DILocation(line: 143, column: 10, scope: !326)
!477 = !DILocation(line: 143, column: 18, scope: !326)
!478 = !DILocation(line: 144, column: 2, scope: !326)
!479 = !DILocation(line: 144, column: 10, scope: !326)
!480 = !DILocation(line: 144, column: 15, scope: !326)
!481 = !DILocation(line: 145, column: 2, scope: !326)
!482 = !DILocalVariable(name: "state", arg: 1, scope: !332, file: !1, line: 189, type: !291)
!483 = !DILocation(line: 189, column: 35, scope: !332)
!484 = !DILocation(line: 192, column: 6, scope: !485)
!485 = distinct !DILexicalBlock(scope: !332, file: !1, line: 192, column: 6)
!486 = !DILocation(line: 192, column: 6, scope: !332)
!487 = !DILocation(line: 193, column: 8, scope: !488)
!488 = distinct !DILexicalBlock(scope: !485, file: !1, line: 192, column: 13)
!489 = !DILocation(line: 193, column: 15, scope: !488)
!490 = !DILocation(line: 193, column: 3, scope: !488)
!491 = !DILocation(line: 194, column: 8, scope: !488)
!492 = !DILocation(line: 194, column: 15, scope: !488)
!493 = !DILocation(line: 194, column: 3, scope: !488)
!494 = !DILocation(line: 195, column: 8, scope: !488)
!495 = !DILocation(line: 195, column: 3, scope: !488)
!496 = !DILocation(line: 196, column: 2, scope: !488)
!497 = !DILocation(line: 197, column: 1, scope: !332)
!498 = !DILocalVariable(name: "self", arg: 1, scope: !323, file: !1, line: 397, type: !169)
!499 = !DILocation(line: 397, column: 52, scope: !323)
!500 = !DILocalVariable(name: "cmd", arg: 2, scope: !323, file: !1, line: 397, type: !80)
!501 = !DILocation(line: 397, column: 70, scope: !323)
!502 = !DILocalVariable(name: "state", scope: !323, file: !1, line: 399, type: !299)
!503 = !DILocation(line: 399, column: 25, scope: !323)
!504 = !DILocalVariable(name: "out_buf", scope: !323, file: !1, line: 401, type: !95)
!505 = !DILocation(line: 401, column: 8, scope: !323)
!506 = !DILocalVariable(name: "prefix", scope: !323, file: !1, line: 402, type: !80)
!507 = !DILocation(line: 402, column: 14, scope: !323)
!508 = !DILocalVariable(name: "child", scope: !323, file: !1, line: 403, type: !304)
!509 = !DILocation(line: 403, column: 8, scope: !323)
!510 = !DILocalVariable(name: "l", scope: !323, file: !1, line: 404, type: !45)
!511 = !DILocation(line: 404, column: 9, scope: !323)
!512 = !DILocation(line: 406, column: 13, scope: !323)
!513 = !DILocation(line: 406, column: 6, scope: !323)
!514 = !DILocation(line: 406, column: 30, scope: !323)
!515 = !DILocation(line: 406, column: 23, scope: !516)
!516 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 1)
!517 = !DILocation(line: 406, column: 21, scope: !323)
!518 = !DILocation(line: 406, column: 35, scope: !323)
!519 = !DILocation(line: 406, column: 4, scope: !323)
!520 = !DILocation(line: 407, column: 35, scope: !323)
!521 = !DILocation(line: 407, column: 10, scope: !323)
!522 = !DILocation(line: 407, column: 8, scope: !323)
!523 = !DILocation(line: 408, column: 20, scope: !323)
!524 = !DILocation(line: 408, column: 10, scope: !323)
!525 = !DILocation(line: 409, column: 6, scope: !526)
!526 = distinct !DILexicalBlock(scope: !323, file: !1, line: 409, column: 6)
!527 = !DILocation(line: 409, column: 12, scope: !526)
!528 = !DILocation(line: 409, column: 20, scope: !526)
!529 = !DILocation(line: 409, column: 23, scope: !530)
!530 = !DILexicalBlockFile(scope: !526, file: !1, discriminator: 1)
!531 = !DILocation(line: 409, column: 31, scope: !530)
!532 = !DILocation(line: 409, column: 39, scope: !530)
!533 = !DILocation(line: 410, column: 29, scope: !526)
!534 = !DILocation(line: 410, column: 36, scope: !526)
!535 = !DILocation(line: 410, column: 49, scope: !526)
!536 = !DILocation(line: 410, column: 6, scope: !526)
!537 = !DILocation(line: 410, column: 52, scope: !526)
!538 = !DILocation(line: 409, column: 6, scope: !539)
!539 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 2)
!540 = !DILocation(line: 411, column: 22, scope: !541)
!541 = distinct !DILexicalBlock(scope: !526, file: !1, line: 410, column: 61)
!542 = !DILocation(line: 411, column: 28, scope: !541)
!543 = !DILocation(line: 411, column: 37, scope: !541)
!544 = !DILocation(line: 411, column: 3, scope: !541)
!545 = !DILocation(line: 413, column: 7, scope: !546)
!546 = distinct !DILexicalBlock(scope: !541, file: !1, line: 413, column: 7)
!547 = !DILocation(line: 413, column: 13, scope: !546)
!548 = !DILocation(line: 413, column: 7, scope: !541)
!549 = !DILocation(line: 414, column: 25, scope: !550)
!550 = distinct !DILexicalBlock(scope: !546, file: !1, line: 413, column: 22)
!551 = !DILocation(line: 414, column: 32, scope: !550)
!552 = !DILocation(line: 414, column: 4, scope: !550)
!553 = !DILocation(line: 415, column: 9, scope: !550)
!554 = !DILocation(line: 415, column: 4, scope: !550)
!555 = !DILocation(line: 416, column: 3, scope: !550)
!556 = !DILocation(line: 417, column: 8, scope: !541)
!557 = !DILocation(line: 417, column: 3, scope: !541)
!558 = !DILocation(line: 418, column: 3, scope: !541)
!559 = !DILocation(line: 420, column: 2, scope: !323)
!560 = !DILocation(line: 420, column: 2, scope: !516)
!561 = !DILocation(line: 420, column: 2, scope: !539)
!562 = !DILocation(line: 420, column: 2, scope: !563)
!563 = !DILexicalBlockFile(scope: !323, file: !1, discriminator: 3)
!564 = !DILocation(line: 421, column: 18, scope: !323)
!565 = !DILocation(line: 421, column: 25, scope: !323)
!566 = !DILocation(line: 421, column: 38, scope: !323)
!567 = !DILocation(line: 421, column: 2, scope: !323)
!568 = !DILocation(line: 423, column: 2, scope: !323)
!569 = !DILocation(line: 423, column: 8, scope: !323)
!570 = !DILocation(line: 423, column: 13, scope: !323)
!571 = !DILocation(line: 424, column: 15, scope: !323)
!572 = !DILocation(line: 424, column: 22, scope: !323)
!573 = !DILocation(line: 424, column: 34, scope: !323)
!574 = !DILocation(line: 424, column: 2, scope: !323)
!575 = !DILocation(line: 424, column: 8, scope: !323)
!576 = !DILocation(line: 424, column: 13, scope: !323)
!577 = !DILocation(line: 426, column: 19, scope: !323)
!578 = !DILocation(line: 426, column: 2, scope: !323)
!579 = !DILocation(line: 426, column: 9, scope: !323)
!580 = !DILocation(line: 426, column: 17, scope: !323)
!581 = !DILocation(line: 427, column: 2, scope: !323)
!582 = !DILocation(line: 427, column: 9, scope: !323)
!583 = !DILocation(line: 427, column: 21, scope: !323)
!584 = !DILocation(line: 429, column: 33, scope: !323)
!585 = !DILocation(line: 429, column: 39, scope: !323)
!586 = !DILocation(line: 429, column: 46, scope: !323)
!587 = !DILocation(line: 430, column: 7, scope: !323)
!588 = !DILocation(line: 430, column: 14, scope: !323)
!589 = !DILocation(line: 429, column: 10, scope: !323)
!590 = !DILocation(line: 429, column: 8, scope: !323)
!591 = !DILocation(line: 431, column: 6, scope: !592)
!592 = distinct !DILexicalBlock(scope: !323, file: !1, line: 431, column: 6)
!593 = !DILocation(line: 431, column: 12, scope: !592)
!594 = !DILocation(line: 431, column: 6, scope: !323)
!595 = !DILocation(line: 432, column: 8, scope: !596)
!596 = distinct !DILexicalBlock(scope: !592, file: !1, line: 431, column: 19)
!597 = !DILocation(line: 432, column: 15, scope: !596)
!598 = !DILocation(line: 432, column: 3, scope: !596)
!599 = !DILocation(line: 433, column: 24, scope: !596)
!600 = !DILocation(line: 433, column: 31, scope: !596)
!601 = !DILocation(line: 433, column: 3, scope: !596)
!602 = !DILocation(line: 434, column: 8, scope: !596)
!603 = !DILocation(line: 434, column: 3, scope: !596)
!604 = !DILocation(line: 435, column: 22, scope: !596)
!605 = !DILocation(line: 435, column: 28, scope: !596)
!606 = !DILocation(line: 435, column: 37, scope: !596)
!607 = !DILocation(line: 437, column: 7, scope: !596)
!608 = !DILocation(line: 435, column: 3, scope: !596)
!609 = !DILocation(line: 438, column: 3, scope: !596)
!610 = !DILocation(line: 453, column: 17, scope: !323)
!611 = !DILocation(line: 453, column: 2, scope: !323)
!612 = !DILocation(line: 453, column: 9, scope: !323)
!613 = !DILocation(line: 453, column: 15, scope: !323)
!614 = !DILocation(line: 456, column: 15, scope: !323)
!615 = !DILocation(line: 456, column: 2, scope: !323)
!616 = !DILocation(line: 456, column: 8, scope: !323)
!617 = !DILocation(line: 456, column: 13, scope: !323)
!618 = !DILocation(line: 457, column: 2, scope: !323)
!619 = !DILocation(line: 457, column: 8, scope: !323)
!620 = !DILocation(line: 457, column: 13, scope: !323)
!621 = !DILocation(line: 458, column: 2, scope: !323)
!622 = !DILocation(line: 458, column: 8, scope: !323)
!623 = !DILocation(line: 458, column: 13, scope: !323)
!624 = !DILocation(line: 459, column: 2, scope: !323)
!625 = !DILocation(line: 459, column: 8, scope: !323)
!626 = !DILocation(line: 459, column: 14, scope: !323)
!627 = !DILocation(line: 462, column: 2, scope: !323)
!628 = !DILocation(line: 463, column: 1, scope: !323)
!629 = !DILocalVariable(name: "self", arg: 1, scope: !335, file: !1, line: 475, type: !169)
!630 = !DILocation(line: 475, column: 49, scope: !335)
!631 = !DILocalVariable(name: "buff", arg: 2, scope: !335, file: !1, line: 475, type: !64)
!632 = !DILocation(line: 475, column: 68, scope: !335)
!633 = !DILocalVariable(name: "state", scope: !335, file: !1, line: 477, type: !299)
!634 = !DILocation(line: 477, column: 25, scope: !335)
!635 = !DILocalVariable(name: "bytes", scope: !335, file: !1, line: 478, type: !38)
!636 = !DILocation(line: 478, column: 10, scope: !335)
!637 = !DILocalVariable(name: "total", scope: !335, file: !1, line: 479, type: !45)
!638 = !DILocation(line: 479, column: 9, scope: !335)
!639 = !DILocalVariable(name: "p", scope: !335, file: !1, line: 480, type: !95)
!640 = !DILocation(line: 480, column: 8, scope: !335)
!641 = !DILocation(line: 482, column: 35, scope: !335)
!642 = !DILocation(line: 482, column: 41, scope: !335)
!643 = !DILocation(line: 482, column: 10, scope: !335)
!644 = !DILocation(line: 482, column: 8, scope: !335)
!645 = !DILocation(line: 484, column: 8, scope: !335)
!646 = !DILocation(line: 485, column: 6, scope: !335)
!647 = !DILocation(line: 485, column: 13, scope: !335)
!648 = !DILocation(line: 485, column: 4, scope: !335)
!649 = !DILocation(line: 486, column: 2, scope: !335)
!650 = !DILocation(line: 486, column: 9, scope: !651)
!651 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 1)
!652 = !DILocation(line: 486, column: 16, scope: !651)
!653 = !DILocation(line: 486, column: 29, scope: !651)
!654 = !DILocation(line: 486, column: 35, scope: !651)
!655 = !DILocation(line: 486, column: 38, scope: !656)
!656 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 2)
!657 = !DILocation(line: 486, column: 46, scope: !656)
!658 = !DILocation(line: 486, column: 53, scope: !656)
!659 = !DILocation(line: 486, column: 44, scope: !656)
!660 = !DILocation(line: 486, column: 2, scope: !661)
!661 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 3)
!662 = !DILocation(line: 487, column: 22, scope: !663)
!663 = distinct !DILexicalBlock(scope: !335, file: !1, line: 486, column: 66)
!664 = !DILocation(line: 487, column: 28, scope: !663)
!665 = !DILocation(line: 487, column: 31, scope: !663)
!666 = !DILocation(line: 487, column: 38, scope: !663)
!667 = !DILocation(line: 487, column: 52, scope: !663)
!668 = !DILocation(line: 487, column: 50, scope: !663)
!669 = !DILocation(line: 487, column: 11, scope: !663)
!670 = !DILocation(line: 487, column: 9, scope: !663)
!671 = !DILocation(line: 488, column: 7, scope: !672)
!672 = distinct !DILexicalBlock(scope: !663, file: !1, line: 488, column: 7)
!673 = !DILocation(line: 488, column: 13, scope: !672)
!674 = !DILocation(line: 488, column: 7, scope: !663)
!675 = !DILocation(line: 491, column: 4, scope: !672)
!676 = !DILocation(line: 492, column: 7, scope: !677)
!677 = distinct !DILexicalBlock(scope: !663, file: !1, line: 492, column: 7)
!678 = !DILocation(line: 492, column: 13, scope: !677)
!679 = !DILocation(line: 492, column: 7, scope: !663)
!680 = !DILocation(line: 494, column: 4, scope: !677)
!681 = !DILocation(line: 495, column: 12, scope: !663)
!682 = !DILocation(line: 495, column: 9, scope: !663)
!683 = !DILocation(line: 496, column: 8, scope: !663)
!684 = !DILocation(line: 496, column: 5, scope: !663)
!685 = !DILocation(line: 486, column: 2, scope: !686)
!686 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 4)
!687 = !DILocation(line: 499, column: 10, scope: !335)
!688 = !DILocation(line: 499, column: 17, scope: !335)
!689 = !DILocation(line: 499, column: 3, scope: !335)
!690 = !DILocation(line: 499, column: 8, scope: !335)
!691 = !DILocation(line: 500, column: 10, scope: !335)
!692 = !DILocation(line: 500, column: 2, scope: !335)
!693 = !DILocation(line: 501, column: 1, scope: !335)
!694 = !DILocalVariable(name: "self", arg: 1, scope: !342, file: !1, line: 504, type: !169)
!695 = !DILocation(line: 504, column: 50, scope: !342)
!696 = !DILocalVariable(name: "state", scope: !342, file: !1, line: 506, type: !299)
!697 = !DILocation(line: 506, column: 25, scope: !342)
!698 = !DILocalVariable(name: "e", scope: !342, file: !1, line: 507, type: !23)
!699 = !DILocation(line: 507, column: 6, scope: !342)
!700 = !DILocation(line: 509, column: 35, scope: !342)
!701 = !DILocation(line: 509, column: 41, scope: !342)
!702 = !DILocation(line: 509, column: 10, scope: !342)
!703 = !DILocation(line: 509, column: 8, scope: !342)
!704 = !DILocation(line: 510, column: 17, scope: !342)
!705 = !DILocation(line: 510, column: 23, scope: !342)
!706 = !DILocation(line: 510, column: 6, scope: !342)
!707 = !DILocation(line: 510, column: 4, scope: !342)
!708 = !DILocation(line: 513, column: 7, scope: !342)
!709 = !DILocation(line: 513, column: 14, scope: !342)
!710 = !DILocation(line: 513, column: 2, scope: !342)
!711 = !DILocation(line: 514, column: 23, scope: !342)
!712 = !DILocation(line: 514, column: 30, scope: !342)
!713 = !DILocation(line: 514, column: 2, scope: !342)
!714 = !DILocation(line: 515, column: 7, scope: !342)
!715 = !DILocation(line: 515, column: 2, scope: !342)
!716 = !DILocation(line: 517, column: 10, scope: !342)
!717 = !DILocation(line: 517, column: 2, scope: !342)
!718 = !DILocalVariable(name: "self", arg: 1, scope: !329, file: !1, line: 206, type: !168)
!719 = !DILocation(line: 206, column: 55, scope: !329)
!720 = !DILocalVariable(name: "upstream", arg: 2, scope: !329, file: !1, line: 207, type: !169)
!721 = !DILocation(line: 207, column: 33, scope: !329)
!722 = !DILocalVariable(name: "state", scope: !329, file: !1, line: 209, type: !291)
!723 = !DILocation(line: 209, column: 25, scope: !329)
!724 = !DILocation(line: 209, column: 33, scope: !329)
!725 = !DILocation(line: 209, column: 39, scope: !329)
!726 = !DILocalVariable(name: "p", scope: !329, file: !1, line: 210, type: !80)
!727 = !DILocation(line: 210, column: 14, scope: !329)
!728 = !DILocation(line: 213, column: 6, scope: !729)
!729 = distinct !DILexicalBlock(scope: !329, file: !1, line: 213, column: 6)
!730 = !DILocation(line: 213, column: 13, scope: !729)
!731 = !DILocation(line: 213, column: 27, scope: !729)
!732 = !DILocation(line: 213, column: 6, scope: !329)
!733 = !DILocation(line: 214, column: 35, scope: !734)
!734 = distinct !DILexicalBlock(scope: !729, file: !1, line: 213, column: 32)
!735 = !DILocation(line: 215, column: 7, scope: !734)
!736 = !DILocation(line: 215, column: 14, scope: !734)
!737 = !DILocation(line: 214, column: 7, scope: !734)
!738 = !DILocation(line: 214, column: 5, scope: !734)
!739 = !DILocation(line: 216, column: 7, scope: !740)
!740 = distinct !DILexicalBlock(scope: !734, file: !1, line: 216, column: 7)
!741 = !DILocation(line: 216, column: 9, scope: !740)
!742 = !DILocation(line: 216, column: 7, scope: !734)
!743 = !DILocation(line: 217, column: 4, scope: !740)
!744 = !DILocation(line: 219, column: 14, scope: !745)
!745 = distinct !DILexicalBlock(scope: !734, file: !1, line: 219, column: 7)
!746 = !DILocation(line: 219, column: 17, scope: !745)
!747 = !DILocation(line: 219, column: 24, scope: !745)
!748 = !DILocation(line: 219, column: 35, scope: !745)
!749 = !DILocation(line: 219, column: 42, scope: !745)
!750 = !DILocation(line: 219, column: 7, scope: !745)
!751 = !DILocation(line: 219, column: 57, scope: !745)
!752 = !DILocation(line: 219, column: 7, scope: !734)
!753 = !DILocation(line: 220, column: 4, scope: !745)
!754 = !DILocation(line: 221, column: 16, scope: !734)
!755 = !DILocation(line: 221, column: 23, scope: !734)
!756 = !DILocation(line: 221, column: 11, scope: !734)
!757 = !DILocation(line: 221, column: 37, scope: !734)
!758 = !DILocation(line: 221, column: 3, scope: !734)
!759 = !DILocation(line: 225, column: 6, scope: !760)
!760 = distinct !DILexicalBlock(scope: !329, file: !1, line: 225, column: 6)
!761 = !DILocation(line: 225, column: 13, scope: !760)
!762 = !DILocation(line: 225, column: 6, scope: !329)
!763 = !DILocation(line: 226, column: 3, scope: !760)
!764 = !DILocation(line: 227, column: 2, scope: !329)
!765 = !DILocation(line: 227, column: 9, scope: !329)
!766 = !DILocation(line: 227, column: 17, scope: !329)
!767 = !DILocation(line: 228, column: 2, scope: !329)
!768 = !DILocation(line: 229, column: 1, scope: !329)
!769 = !DILocalVariable(name: "self", arg: 1, scope: !330, file: !1, line: 466, type: !169)
!770 = !DILocation(line: 466, column: 49, scope: !330)
!771 = !DILocalVariable(name: "bidder_state", scope: !330, file: !1, line: 468, type: !291)
!772 = !DILocation(line: 468, column: 27, scope: !330)
!773 = !DILocation(line: 470, column: 42, scope: !330)
!774 = !DILocation(line: 470, column: 48, scope: !330)
!775 = !DILocation(line: 470, column: 56, scope: !330)
!776 = !DILocation(line: 470, column: 17, scope: !330)
!777 = !DILocation(line: 470, column: 15, scope: !330)
!778 = !DILocation(line: 471, column: 33, scope: !330)
!779 = !DILocation(line: 471, column: 39, scope: !330)
!780 = !DILocation(line: 471, column: 53, scope: !330)
!781 = !DILocation(line: 471, column: 10, scope: !330)
!782 = !DILocation(line: 471, column: 2, scope: !330)
!783 = !DILocalVariable(name: "self", arg: 1, scope: !331, file: !1, line: 180, type: !168)
!784 = !DILocation(line: 180, column: 56, scope: !331)
!785 = !DILocalVariable(name: "state", scope: !331, file: !1, line: 182, type: !291)
!786 = !DILocation(line: 182, column: 25, scope: !331)
!787 = !DILocation(line: 182, column: 58, scope: !331)
!788 = !DILocation(line: 182, column: 64, scope: !331)
!789 = !DILocation(line: 182, column: 33, scope: !331)
!790 = !DILocation(line: 184, column: 13, scope: !331)
!791 = !DILocation(line: 184, column: 2, scope: !331)
!792 = !DILocation(line: 185, column: 2, scope: !331)
!793 = !DILocalVariable(name: "self", arg: 1, scope: !336, file: !1, line: 307, type: !169)
!794 = !DILocation(line: 307, column: 40, scope: !336)
!795 = !DILocalVariable(name: "buf", arg: 2, scope: !336, file: !1, line: 307, type: !95)
!796 = !DILocation(line: 307, column: 52, scope: !336)
!797 = !DILocalVariable(name: "buf_len", arg: 3, scope: !336, file: !1, line: 307, type: !45)
!798 = !DILocation(line: 307, column: 64, scope: !336)
!799 = !DILocalVariable(name: "state", scope: !336, file: !1, line: 309, type: !299)
!800 = !DILocation(line: 309, column: 25, scope: !336)
!801 = !DILocation(line: 309, column: 33, scope: !336)
!802 = !DILocation(line: 309, column: 39, scope: !336)
!803 = !DILocalVariable(name: "ret", scope: !336, file: !1, line: 310, type: !38)
!804 = !DILocation(line: 310, column: 10, scope: !336)
!805 = !DILocalVariable(name: "requested", scope: !336, file: !1, line: 310, type: !38)
!806 = !DILocation(line: 310, column: 15, scope: !336)
!807 = !DILocalVariable(name: "avail", scope: !336, file: !1, line: 310, type: !38)
!808 = !DILocation(line: 310, column: 26, scope: !336)
!809 = !DILocalVariable(name: "p", scope: !336, file: !1, line: 311, type: !80)
!810 = !DILocation(line: 311, column: 14, scope: !336)
!811 = !DILocation(line: 316, column: 14, scope: !336)
!812 = !DILocation(line: 316, column: 22, scope: !336)
!813 = !DILocation(line: 316, column: 14, scope: !814)
!814 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 1)
!815 = !DILocation(line: 316, column: 48, scope: !816)
!816 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 2)
!817 = !DILocation(line: 316, column: 14, scope: !816)
!818 = !DILocation(line: 316, column: 14, scope: !819)
!819 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 3)
!820 = !DILocation(line: 316, column: 12, scope: !819)
!821 = !DILocation(line: 318, column: 2, scope: !336)
!822 = !DILocation(line: 319, column: 3, scope: !823)
!823 = distinct !DILexicalBlock(scope: !824, file: !1, line: 318, column: 11)
!824 = distinct !DILexicalBlock(scope: !825, file: !1, line: 318, column: 2)
!825 = distinct !DILexicalBlock(scope: !336, file: !1, line: 318, column: 2)
!826 = !DILocation(line: 341, column: 15, scope: !827)
!827 = distinct !DILexicalBlock(scope: !823, file: !1, line: 319, column: 6)
!828 = !DILocation(line: 341, column: 22, scope: !827)
!829 = !DILocation(line: 341, column: 36, scope: !827)
!830 = !DILocation(line: 341, column: 41, scope: !827)
!831 = !DILocation(line: 341, column: 10, scope: !827)
!832 = !DILocation(line: 341, column: 8, scope: !827)
!833 = !DILocation(line: 342, column: 3, scope: !827)
!834 = !DILocation(line: 342, column: 12, scope: !835)
!835 = !DILexicalBlockFile(scope: !823, file: !1, discriminator: 1)
!836 = !DILocation(line: 342, column: 16, scope: !835)
!837 = !DILocation(line: 342, column: 22, scope: !835)
!838 = !DILocation(line: 342, column: 25, scope: !839)
!839 = !DILexicalBlockFile(scope: !823, file: !1, discriminator: 2)
!840 = !DILocation(line: 342, column: 31, scope: !839)
!841 = !DILocation(line: 342, column: 3, scope: !842)
!842 = !DILexicalBlockFile(scope: !827, file: !1, discriminator: 3)
!843 = !DILocation(line: 344, column: 7, scope: !844)
!844 = distinct !DILexicalBlock(scope: !823, file: !1, line: 344, column: 7)
!845 = !DILocation(line: 344, column: 11, scope: !844)
!846 = !DILocation(line: 344, column: 7, scope: !823)
!847 = !DILocation(line: 345, column: 12, scope: !844)
!848 = !DILocation(line: 345, column: 4, scope: !844)
!849 = !DILocation(line: 346, column: 7, scope: !850)
!850 = distinct !DILexicalBlock(scope: !823, file: !1, line: 346, column: 7)
!851 = !DILocation(line: 346, column: 11, scope: !850)
!852 = !DILocation(line: 346, column: 16, scope: !850)
!853 = !DILocation(line: 346, column: 20, scope: !854)
!854 = !DILexicalBlockFile(scope: !850, file: !1, discriminator: 1)
!855 = !DILocation(line: 346, column: 24, scope: !854)
!856 = !DILocation(line: 346, column: 30, scope: !854)
!857 = !DILocation(line: 346, column: 33, scope: !858)
!858 = !DILexicalBlockFile(scope: !850, file: !1, discriminator: 2)
!859 = !DILocation(line: 346, column: 39, scope: !858)
!860 = !DILocation(line: 346, column: 7, scope: !858)
!861 = !DILocation(line: 349, column: 23, scope: !850)
!862 = !DILocation(line: 349, column: 29, scope: !850)
!863 = !DILocation(line: 349, column: 12, scope: !850)
!864 = !DILocation(line: 349, column: 11, scope: !850)
!865 = !DILocation(line: 349, column: 4, scope: !850)
!866 = !DILocation(line: 350, column: 7, scope: !867)
!867 = distinct !DILexicalBlock(scope: !823, file: !1, line: 350, column: 7)
!868 = !DILocation(line: 350, column: 11, scope: !867)
!869 = !DILocation(line: 350, column: 17, scope: !867)
!870 = !DILocation(line: 350, column: 20, scope: !871)
!871 = !DILexicalBlockFile(scope: !867, file: !1, discriminator: 1)
!872 = !DILocation(line: 350, column: 26, scope: !871)
!873 = !DILocation(line: 350, column: 7, scope: !871)
!874 = !DILocation(line: 351, column: 4, scope: !867)
!875 = !DILocation(line: 353, column: 7, scope: !876)
!876 = distinct !DILexicalBlock(scope: !823, file: !1, line: 353, column: 7)
!877 = !DILocation(line: 353, column: 14, scope: !876)
!878 = !DILocation(line: 353, column: 26, scope: !876)
!879 = !DILocation(line: 353, column: 7, scope: !823)
!880 = !DILocation(line: 355, column: 26, scope: !881)
!881 = distinct !DILexicalBlock(scope: !876, file: !1, line: 353, column: 33)
!882 = !DILocation(line: 355, column: 33, scope: !881)
!883 = !DILocation(line: 356, column: 8, scope: !881)
!884 = !DILocation(line: 356, column: 15, scope: !881)
!885 = !DILocation(line: 355, column: 4, scope: !881)
!886 = !DILocation(line: 357, column: 4, scope: !881)
!887 = !DILocation(line: 361, column: 35, scope: !823)
!888 = !DILocation(line: 361, column: 41, scope: !823)
!889 = !DILocation(line: 361, column: 7, scope: !823)
!890 = !DILocation(line: 361, column: 5, scope: !823)
!891 = !DILocation(line: 362, column: 7, scope: !892)
!892 = distinct !DILexicalBlock(scope: !823, file: !1, line: 362, column: 7)
!893 = !DILocation(line: 362, column: 9, scope: !892)
!894 = !DILocation(line: 362, column: 7, scope: !823)
!895 = !DILocation(line: 363, column: 10, scope: !896)
!896 = distinct !DILexicalBlock(scope: !892, file: !1, line: 362, column: 18)
!897 = !DILocation(line: 363, column: 17, scope: !896)
!898 = !DILocation(line: 363, column: 4, scope: !896)
!899 = !DILocation(line: 364, column: 4, scope: !896)
!900 = !DILocation(line: 364, column: 11, scope: !896)
!901 = !DILocation(line: 364, column: 23, scope: !896)
!902 = !DILocation(line: 365, column: 10, scope: !896)
!903 = !DILocation(line: 365, column: 17, scope: !896)
!904 = !DILocation(line: 365, column: 4, scope: !896)
!905 = !DILocation(line: 366, column: 8, scope: !906)
!906 = distinct !DILexicalBlock(scope: !896, file: !1, line: 366, column: 8)
!907 = !DILocation(line: 366, column: 14, scope: !906)
!908 = !DILocation(line: 366, column: 8, scope: !896)
!909 = !DILocation(line: 367, column: 13, scope: !906)
!910 = !DILocation(line: 367, column: 5, scope: !906)
!911 = !DILocation(line: 368, column: 4, scope: !896)
!912 = !DILocation(line: 371, column: 3, scope: !823)
!913 = !DILocation(line: 372, column: 16, scope: !914)
!914 = distinct !DILexicalBlock(scope: !823, file: !1, line: 371, column: 6)
!915 = !DILocation(line: 372, column: 23, scope: !914)
!916 = !DILocation(line: 372, column: 36, scope: !914)
!917 = !DILocation(line: 372, column: 39, scope: !914)
!918 = !DILocation(line: 372, column: 10, scope: !914)
!919 = !DILocation(line: 372, column: 8, scope: !914)
!920 = !DILocation(line: 373, column: 3, scope: !914)
!921 = !DILocation(line: 373, column: 12, scope: !835)
!922 = !DILocation(line: 373, column: 16, scope: !835)
!923 = !DILocation(line: 373, column: 22, scope: !835)
!924 = !DILocation(line: 373, column: 25, scope: !839)
!925 = !DILocation(line: 373, column: 31, scope: !839)
!926 = !DILocation(line: 373, column: 3, scope: !927)
!927 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 3)
!928 = !DILocation(line: 375, column: 7, scope: !929)
!929 = distinct !DILexicalBlock(scope: !823, file: !1, line: 375, column: 7)
!930 = !DILocation(line: 375, column: 11, scope: !929)
!931 = !DILocation(line: 375, column: 7, scope: !823)
!932 = !DILocation(line: 377, column: 34, scope: !933)
!933 = distinct !DILexicalBlock(scope: !929, file: !1, line: 375, column: 16)
!934 = !DILocation(line: 377, column: 40, scope: !933)
!935 = !DILocation(line: 377, column: 50, scope: !933)
!936 = !DILocation(line: 377, column: 4, scope: !933)
!937 = !DILocation(line: 378, column: 3, scope: !933)
!938 = !DILocation(line: 378, column: 14, scope: !939)
!939 = !DILexicalBlockFile(scope: !940, file: !1, discriminator: 1)
!940 = distinct !DILexicalBlock(scope: !929, file: !1, line: 378, column: 14)
!941 = !DILocation(line: 378, column: 18, scope: !939)
!942 = !DILocation(line: 378, column: 24, scope: !939)
!943 = !DILocation(line: 378, column: 27, scope: !944)
!944 = !DILexicalBlockFile(scope: !940, file: !1, discriminator: 2)
!945 = !DILocation(line: 378, column: 33, scope: !944)
!946 = !DILocation(line: 378, column: 14, scope: !944)
!947 = !DILocation(line: 380, column: 26, scope: !948)
!948 = distinct !DILexicalBlock(scope: !940, file: !1, line: 378, column: 44)
!949 = !DILocation(line: 380, column: 33, scope: !948)
!950 = !DILocation(line: 381, column: 8, scope: !948)
!951 = !DILocation(line: 381, column: 15, scope: !948)
!952 = !DILocation(line: 380, column: 4, scope: !948)
!953 = !DILocation(line: 382, column: 3, scope: !948)
!954 = !DILocation(line: 384, column: 10, scope: !955)
!955 = distinct !DILexicalBlock(scope: !940, file: !1, line: 382, column: 10)
!956 = !DILocation(line: 384, column: 17, scope: !955)
!957 = !DILocation(line: 384, column: 4, scope: !955)
!958 = !DILocation(line: 385, column: 4, scope: !955)
!959 = !DILocation(line: 385, column: 11, scope: !955)
!960 = !DILocation(line: 385, column: 23, scope: !955)
!961 = !DILocation(line: 386, column: 10, scope: !955)
!962 = !DILocation(line: 386, column: 17, scope: !955)
!963 = !DILocation(line: 386, column: 4, scope: !955)
!964 = !DILocation(line: 390, column: 8, scope: !965)
!965 = distinct !DILexicalBlock(scope: !955, file: !1, line: 390, column: 8)
!966 = !DILocation(line: 390, column: 12, scope: !965)
!967 = !DILocation(line: 390, column: 18, scope: !965)
!968 = !DILocation(line: 390, column: 21, scope: !969)
!969 = !DILexicalBlockFile(scope: !965, file: !1, discriminator: 1)
!970 = !DILocation(line: 390, column: 27, scope: !969)
!971 = !DILocation(line: 390, column: 8, scope: !969)
!972 = !DILocation(line: 391, column: 5, scope: !965)
!973 = !DILocation(line: 318, column: 2, scope: !974)
!974 = !DILexicalBlockFile(scope: !824, file: !1, discriminator: 1)
!975 = !DILocation(line: 394, column: 1, scope: !336)
!976 = !DILocalVariable(name: "self", arg: 1, scope: !339, file: !1, line: 239, type: !169)
!977 = !DILocation(line: 239, column: 40, scope: !339)
!978 = !DILocalVariable(name: "state", arg: 2, scope: !339, file: !1, line: 239, type: !299)
!979 = !DILocation(line: 239, column: 69, scope: !339)
!980 = !DILocation(line: 242, column: 6, scope: !981)
!981 = distinct !DILexicalBlock(scope: !339, file: !1, line: 242, column: 6)
!982 = !DILocation(line: 242, column: 13, scope: !981)
!983 = !DILocation(line: 242, column: 25, scope: !981)
!984 = !DILocation(line: 242, column: 6, scope: !339)
!985 = !DILocation(line: 243, column: 9, scope: !986)
!986 = distinct !DILexicalBlock(scope: !981, file: !1, line: 242, column: 32)
!987 = !DILocation(line: 243, column: 16, scope: !986)
!988 = !DILocation(line: 243, column: 3, scope: !986)
!989 = !DILocation(line: 244, column: 3, scope: !986)
!990 = !DILocation(line: 244, column: 10, scope: !986)
!991 = !DILocation(line: 244, column: 22, scope: !986)
!992 = !DILocation(line: 245, column: 2, scope: !986)
!993 = !DILocation(line: 246, column: 6, scope: !994)
!994 = distinct !DILexicalBlock(scope: !339, file: !1, line: 246, column: 6)
!995 = !DILocation(line: 246, column: 13, scope: !994)
!996 = !DILocation(line: 246, column: 26, scope: !994)
!997 = !DILocation(line: 246, column: 6, scope: !339)
!998 = !DILocation(line: 247, column: 9, scope: !999)
!999 = distinct !DILexicalBlock(scope: !994, file: !1, line: 246, column: 33)
!1000 = !DILocation(line: 247, column: 16, scope: !999)
!1001 = !DILocation(line: 247, column: 3, scope: !999)
!1002 = !DILocation(line: 248, column: 3, scope: !999)
!1003 = !DILocation(line: 248, column: 10, scope: !999)
!1004 = !DILocation(line: 248, column: 23, scope: !999)
!1005 = !DILocation(line: 249, column: 2, scope: !999)
!1006 = !DILocation(line: 251, column: 6, scope: !1007)
!1007 = distinct !DILexicalBlock(scope: !339, file: !1, line: 251, column: 6)
!1008 = !DILocation(line: 251, column: 13, scope: !1007)
!1009 = !DILocation(line: 251, column: 19, scope: !1007)
!1010 = !DILocation(line: 251, column: 6, scope: !339)
!1011 = !DILocation(line: 253, column: 3, scope: !1012)
!1012 = distinct !DILexicalBlock(scope: !1007, file: !1, line: 251, column: 25)
!1013 = !DILocation(line: 255, column: 18, scope: !1014)
!1014 = distinct !DILexicalBlock(scope: !1012, file: !1, line: 253, column: 6)
!1015 = !DILocation(line: 255, column: 25, scope: !1014)
!1016 = !DILocation(line: 255, column: 33, scope: !1014)
!1017 = !DILocation(line: 255, column: 40, scope: !1014)
!1018 = !DILocation(line: 255, column: 10, scope: !1014)
!1019 = !DILocation(line: 254, column: 4, scope: !1014)
!1020 = !DILocation(line: 254, column: 11, scope: !1014)
!1021 = !DILocation(line: 255, column: 8, scope: !1014)
!1022 = !DILocation(line: 256, column: 3, scope: !1014)
!1023 = !DILocation(line: 256, column: 12, scope: !1024)
!1024 = !DILexicalBlockFile(scope: !1012, file: !1, discriminator: 1)
!1025 = !DILocation(line: 256, column: 19, scope: !1024)
!1026 = !DILocation(line: 256, column: 34, scope: !1024)
!1027 = !DILocation(line: 256, column: 40, scope: !1024)
!1028 = !DILocation(line: 256, column: 43, scope: !1029)
!1029 = !DILexicalBlockFile(scope: !1012, file: !1, discriminator: 2)
!1030 = !DILocation(line: 256, column: 49, scope: !1029)
!1031 = !DILocation(line: 256, column: 3, scope: !1032)
!1032 = !DILexicalBlockFile(scope: !1014, file: !1, discriminator: 3)
!1033 = !DILocation(line: 260, column: 3, scope: !1012)
!1034 = !DILocation(line: 260, column: 10, scope: !1012)
!1035 = !DILocation(line: 260, column: 16, scope: !1012)
!1036 = !DILocation(line: 261, column: 2, scope: !1012)
!1037 = !DILocation(line: 263, column: 6, scope: !1038)
!1038 = distinct !DILexicalBlock(scope: !339, file: !1, line: 263, column: 6)
!1039 = !DILocation(line: 263, column: 13, scope: !1038)
!1040 = !DILocation(line: 263, column: 28, scope: !1038)
!1041 = !DILocation(line: 263, column: 6, scope: !339)
!1042 = !DILocation(line: 265, column: 22, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !1038, file: !1, line: 263, column: 33)
!1044 = !DILocation(line: 265, column: 28, scope: !1043)
!1045 = !DILocation(line: 265, column: 37, scope: !1043)
!1046 = !DILocation(line: 265, column: 3, scope: !1043)
!1047 = !DILocation(line: 267, column: 3, scope: !1043)
!1048 = !DILocation(line: 271, column: 6, scope: !1049)
!1049 = distinct !DILexicalBlock(scope: !339, file: !1, line: 271, column: 6)
!1050 = !DILocation(line: 271, column: 6, scope: !339)
!1051 = !DILocation(line: 279, column: 7, scope: !1052)
!1052 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 279, column: 7)
!1053 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 271, column: 39)
!1054 = !DILocation(line: 279, column: 36, scope: !1052)
!1055 = !DILocation(line: 279, column: 7, scope: !1053)
!1056 = !DILocation(line: 280, column: 4, scope: !1052)
!1057 = !DILocation(line: 282, column: 22, scope: !1053)
!1058 = !DILocation(line: 282, column: 28, scope: !1053)
!1059 = !DILocation(line: 282, column: 37, scope: !1053)
!1060 = !DILocation(line: 284, column: 7, scope: !1053)
!1061 = !DILocation(line: 282, column: 3, scope: !1053)
!1062 = !DILocation(line: 285, column: 3, scope: !1053)
!1063 = !DILocation(line: 289, column: 6, scope: !1064)
!1064 = distinct !DILexicalBlock(scope: !339, file: !1, line: 289, column: 6)
!1065 = !DILocation(line: 289, column: 6, scope: !339)
!1066 = !DILocation(line: 290, column: 7, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 290, column: 7)
!1068 = distinct !DILexicalBlock(scope: !1064, file: !1, line: 289, column: 37)
!1069 = !DILocation(line: 290, column: 39, scope: !1067)
!1070 = !DILocation(line: 290, column: 7, scope: !1068)
!1071 = !DILocation(line: 291, column: 4, scope: !1067)
!1072 = !DILocation(line: 293, column: 22, scope: !1068)
!1073 = !DILocation(line: 293, column: 28, scope: !1068)
!1074 = !DILocation(line: 293, column: 37, scope: !1068)
!1075 = !DILocation(line: 296, column: 7, scope: !1068)
!1076 = !DILocation(line: 293, column: 3, scope: !1068)
!1077 = !DILocation(line: 297, column: 3, scope: !1068)
!1078 = !DILocation(line: 300, column: 2, scope: !339)
!1079 = !DILocation(line: 301, column: 1, scope: !339)
