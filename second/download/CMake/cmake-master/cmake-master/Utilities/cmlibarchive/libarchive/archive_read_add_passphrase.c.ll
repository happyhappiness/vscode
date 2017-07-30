; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_add_passphrase.c'
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

@.str = private unnamed_addr constant [28 x i8] c"archive_read_add_passphrase\00", align 1
@.str.1 = private unnamed_addr constant [33 x i8] c"Empty passphrase is unacceptable\00", align 1
@.str.2 = private unnamed_addr constant [37 x i8] c"archive_read_set_passphrase_callback\00", align 1
@.str.3 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_add_passphrase(%struct.archive* %_a, i8* %passphrase) #0 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %passphrase.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read*, align 8
  %p = alloca %struct.archive_read_passphrase*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !317, metadata !318), !dbg !319
  store i8* %passphrase, i8** %passphrase.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %passphrase.addr, metadata !320, metadata !318), !dbg !321
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !322, metadata !318), !dbg !323
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !324
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !325
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !323
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p, metadata !326, metadata !318), !dbg !327
  br label %do.body, !dbg !328

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !329, metadata !318), !dbg !331
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !332
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0)), !dbg !332
  store i32 %call, i32* %magic_test, align 4, !dbg !332
  %3 = load i32, i32* %magic_test, align 4, !dbg !332
  %cmp = icmp eq i32 %3, -30, !dbg !332
  br i1 %cmp, label %if.then, label %if.end, !dbg !332

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !334
  br label %return, !dbg !334

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !337

do.end:                                           ; preds = %if.end
  %4 = load i8*, i8** %passphrase.addr, align 8, !dbg !339
  %cmp1 = icmp eq i8* %4, null, !dbg !341
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !342

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i8*, i8** %passphrase.addr, align 8, !dbg !343
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !343
  %6 = load i8, i8* %arrayidx, align 1, !dbg !343
  %conv = sext i8 %6 to i32, !dbg !343
  %cmp2 = icmp eq i32 %conv, 0, !dbg !345
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !346

if.then4:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !347
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !349
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.1, i32 0, i32 0)), !dbg !350
  store i32 -25, i32* %retval, align 4, !dbg !351
  br label %return, !dbg !351

if.end5:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !352
  %9 = load i8*, i8** %passphrase.addr, align 8, !dbg !353
  %call6 = call %struct.archive_read_passphrase* @new_read_passphrase(%struct.archive_read* %8, i8* %9), !dbg !354
  store %struct.archive_read_passphrase* %call6, %struct.archive_read_passphrase** %p, align 8, !dbg !355
  %10 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !356
  %cmp7 = icmp eq %struct.archive_read_passphrase* %10, null, !dbg !358
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !359

if.then9:                                         ; preds = %if.end5
  store i32 -30, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

if.end10:                                         ; preds = %if.end5
  %11 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !361
  %12 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !362
  call void @add_passphrase_to_tail(%struct.archive_read* %11, %struct.archive_read_passphrase* %12), !dbg !363
  store i32 0, i32* %retval, align 4, !dbg !364
  br label %return, !dbg !364

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !365
  ret i32 %13, !dbg !365
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal %struct.archive_read_passphrase* @new_read_passphrase(%struct.archive_read* %a, i8* %passphrase) #0 !dbg !304 {
entry:
  %retval = alloca %struct.archive_read_passphrase*, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %passphrase.addr = alloca i8*, align 8
  %p = alloca %struct.archive_read_passphrase*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !366, metadata !318), !dbg !367
  store i8* %passphrase, i8** %passphrase.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %passphrase.addr, metadata !368, metadata !318), !dbg !369
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p, metadata !370, metadata !318), !dbg !371
  %call = call noalias i8* @malloc(i64 16) #4, !dbg !372
  %0 = bitcast i8* %call to %struct.archive_read_passphrase*, !dbg !372
  store %struct.archive_read_passphrase* %0, %struct.archive_read_passphrase** %p, align 8, !dbg !373
  %1 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !374
  %cmp = icmp eq %struct.archive_read_passphrase* %1, null, !dbg !376
  br i1 %cmp, label %if.then, label %if.end, !dbg !377

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !378
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !380
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0)), !dbg !381
  store %struct.archive_read_passphrase* null, %struct.archive_read_passphrase** %retval, align 8, !dbg !382
  br label %return, !dbg !382

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %passphrase.addr, align 8, !dbg !383
  %call1 = call noalias i8* @strdup(i8* %3) #4, !dbg !384
  %4 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !385
  %passphrase2 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %4, i32 0, i32 0, !dbg !386
  store i8* %call1, i8** %passphrase2, align 8, !dbg !387
  %5 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !388
  %passphrase3 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %5, i32 0, i32 0, !dbg !390
  %6 = load i8*, i8** %passphrase3, align 8, !dbg !390
  %cmp4 = icmp eq i8* %6, null, !dbg !391
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !392

if.then5:                                         ; preds = %if.end
  %7 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !393
  %8 = bitcast %struct.archive_read_passphrase* %7 to i8*, !dbg !393
  call void @free(i8* %8) #4, !dbg !395
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !396
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !397
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0)), !dbg !398
  store %struct.archive_read_passphrase* null, %struct.archive_read_passphrase** %retval, align 8, !dbg !399
  br label %return, !dbg !399

if.end7:                                          ; preds = %if.end
  %10 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !400
  store %struct.archive_read_passphrase* %10, %struct.archive_read_passphrase** %retval, align 8, !dbg !401
  br label %return, !dbg !401

return:                                           ; preds = %if.end7, %if.then5, %if.then
  %11 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %retval, align 8, !dbg !402
  ret %struct.archive_read_passphrase* %11, !dbg !402
}

; Function Attrs: nounwind uwtable
define internal void @add_passphrase_to_tail(%struct.archive_read* %a, %struct.archive_read_passphrase* %p) #0 !dbg !307 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %p.addr = alloca %struct.archive_read_passphrase*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !403, metadata !318), !dbg !404
  store %struct.archive_read_passphrase* %p, %struct.archive_read_passphrase** %p.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p.addr, metadata !405, metadata !318), !dbg !406
  %0 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p.addr, align 8, !dbg !407
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !408
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 16, !dbg !409
  %last = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 1, !dbg !410
  %2 = load %struct.archive_read_passphrase**, %struct.archive_read_passphrase*** %last, align 8, !dbg !410
  store %struct.archive_read_passphrase* %0, %struct.archive_read_passphrase** %2, align 8, !dbg !411
  %3 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p.addr, align 8, !dbg !412
  %next = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %3, i32 0, i32 1, !dbg !413
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !414
  %passphrases1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 16, !dbg !415
  %last2 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases1, i32 0, i32 1, !dbg !416
  store %struct.archive_read_passphrase** %next, %struct.archive_read_passphrase*** %last2, align 8, !dbg !417
  %5 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p.addr, align 8, !dbg !418
  %next3 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %5, i32 0, i32 1, !dbg !419
  store %struct.archive_read_passphrase* null, %struct.archive_read_passphrase** %next3, align 8, !dbg !420
  ret void, !dbg !421
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_passphrase_callback(%struct.archive* %_a, i8* %client_data, i8* (%struct.archive*, i8*)* %cb) #0 !dbg !295 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %cb.addr = alloca i8* (%struct.archive*, i8*)*, align 8
  %a = alloca %struct.archive_read*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !422, metadata !318), !dbg !423
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !424, metadata !318), !dbg !425
  store i8* (%struct.archive*, i8*)* %cb, i8* (%struct.archive*, i8*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (%struct.archive*, i8*)** %cb.addr, metadata !426, metadata !318), !dbg !427
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !428, metadata !318), !dbg !429
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !430
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !431
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !429
  br label %do.body, !dbg !432

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !433, metadata !318), !dbg !435
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !436
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.2, i32 0, i32 0)), !dbg !436
  store i32 %call, i32* %magic_test, align 4, !dbg !436
  %3 = load i32, i32* %magic_test, align 4, !dbg !436
  %cmp = icmp eq i32 %3, -30, !dbg !436
  br i1 %cmp, label %if.then, label %if.end, !dbg !436

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !438
  br label %return, !dbg !438

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !441

do.end:                                           ; preds = %if.end
  %4 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %cb.addr, align 8, !dbg !443
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !444
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 16, !dbg !445
  %callback = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 3, !dbg !446
  store i8* (%struct.archive*, i8*)* %4, i8* (%struct.archive*, i8*)** %callback, align 8, !dbg !447
  %6 = load i8*, i8** %client_data.addr, align 8, !dbg !448
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !449
  %passphrases1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 16, !dbg !450
  %client_data2 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases1, i32 0, i32 4, !dbg !451
  store i8* %6, i8** %client_data2, align 8, !dbg !452
  store i32 0, i32* %retval, align 4, !dbg !453
  br label %return, !dbg !453

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !454
  ret i32 %8, !dbg !454
}

; Function Attrs: nounwind uwtable
define void @__archive_read_reset_passphrase(%struct.archive_read* %a) #0 !dbg !298 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !455, metadata !318), !dbg !456
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !457
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 16, !dbg !458
  %candidate = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 2, !dbg !459
  store i32 -1, i32* %candidate, align 8, !dbg !460
  ret void, !dbg !461
}

; Function Attrs: nounwind uwtable
define i8* @__archive_read_next_passphrase(%struct.archive_read* %a) #0 !dbg !301 {
entry:
  %retval = alloca i8*, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %p = alloca %struct.archive_read_passphrase*, align 8
  %passphrase = alloca i8*, align 8
  %cnt = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !462, metadata !318), !dbg !463
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p, metadata !464, metadata !318), !dbg !465
  call void @llvm.dbg.declare(metadata i8** %passphrase, metadata !466, metadata !318), !dbg !467
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !468
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 16, !dbg !470
  %candidate = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 2, !dbg !471
  %1 = load i32, i32* %candidate, align 8, !dbg !471
  %cmp = icmp slt i32 %1, 0, !dbg !472
  br i1 %cmp, label %if.then, label %if.else, !dbg !473

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %cnt, metadata !474, metadata !318), !dbg !476
  store i32 0, i32* %cnt, align 4, !dbg !476
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !477
  %passphrases1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 16, !dbg !479
  %first = getelementptr inbounds %struct.anon, %struct.anon* %passphrases1, i32 0, i32 0, !dbg !480
  %3 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first, align 8, !dbg !480
  store %struct.archive_read_passphrase* %3, %struct.archive_read_passphrase** %p, align 8, !dbg !481
  br label %for.cond, !dbg !482

for.cond:                                         ; preds = %for.inc, %if.then
  %4 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !483
  %cmp2 = icmp ne %struct.archive_read_passphrase* %4, null, !dbg !486
  br i1 %cmp2, label %for.body, label %for.end, !dbg !487

for.body:                                         ; preds = %for.cond
  %5 = load i32, i32* %cnt, align 4, !dbg !488
  %inc = add nsw i32 %5, 1, !dbg !488
  store i32 %inc, i32* %cnt, align 4, !dbg !488
  br label %for.inc, !dbg !489

for.inc:                                          ; preds = %for.body
  %6 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !490
  %next = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %6, i32 0, i32 1, !dbg !492
  %7 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %next, align 8, !dbg !492
  store %struct.archive_read_passphrase* %7, %struct.archive_read_passphrase** %p, align 8, !dbg !493
  br label %for.cond, !dbg !494

for.end:                                          ; preds = %for.cond
  %8 = load i32, i32* %cnt, align 4, !dbg !495
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !496
  %passphrases3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 16, !dbg !497
  %candidate4 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases3, i32 0, i32 2, !dbg !498
  store i32 %8, i32* %candidate4, align 8, !dbg !499
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !500
  %passphrases5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 16, !dbg !501
  %first6 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases5, i32 0, i32 0, !dbg !502
  %11 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first6, align 8, !dbg !502
  store %struct.archive_read_passphrase* %11, %struct.archive_read_passphrase** %p, align 8, !dbg !503
  br label %if.end31, !dbg !504

if.else:                                          ; preds = %entry
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !505
  %passphrases7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 16, !dbg !508
  %candidate8 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases7, i32 0, i32 2, !dbg !509
  %13 = load i32, i32* %candidate8, align 8, !dbg !509
  %cmp9 = icmp sgt i32 %13, 1, !dbg !510
  br i1 %cmp9, label %if.then10, label %if.else15, !dbg !505

if.then10:                                        ; preds = %if.else
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !511
  %passphrases11 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 16, !dbg !513
  %candidate12 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases11, i32 0, i32 2, !dbg !514
  %15 = load i32, i32* %candidate12, align 8, !dbg !515
  %dec = add nsw i32 %15, -1, !dbg !515
  store i32 %dec, i32* %candidate12, align 8, !dbg !515
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !516
  %call = call %struct.archive_read_passphrase* @remove_passphrases_from_head(%struct.archive_read* %16), !dbg !517
  store %struct.archive_read_passphrase* %call, %struct.archive_read_passphrase** %p, align 8, !dbg !518
  %17 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !519
  %18 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !520
  call void @add_passphrase_to_tail(%struct.archive_read* %17, %struct.archive_read_passphrase* %18), !dbg !521
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !522
  %passphrases13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 16, !dbg !523
  %first14 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases13, i32 0, i32 0, !dbg !524
  %20 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first14, align 8, !dbg !524
  store %struct.archive_read_passphrase* %20, %struct.archive_read_passphrase** %p, align 8, !dbg !525
  br label %if.end30, !dbg !526

if.else15:                                        ; preds = %if.else
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !527
  %passphrases16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 16, !dbg !530
  %candidate17 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases16, i32 0, i32 2, !dbg !531
  %22 = load i32, i32* %candidate17, align 8, !dbg !531
  %cmp18 = icmp eq i32 %22, 1, !dbg !532
  br i1 %cmp18, label %if.then19, label %if.else28, !dbg !527

if.then19:                                        ; preds = %if.else15
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !533
  %passphrases20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 16, !dbg !535
  %candidate21 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases20, i32 0, i32 2, !dbg !536
  store i32 0, i32* %candidate21, align 8, !dbg !537
  %24 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !538
  %passphrases22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 16, !dbg !540
  %first23 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases22, i32 0, i32 0, !dbg !541
  %25 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first23, align 8, !dbg !541
  %next24 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %25, i32 0, i32 1, !dbg !542
  %26 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %next24, align 8, !dbg !542
  %cmp25 = icmp ne %struct.archive_read_passphrase* %26, null, !dbg !543
  br i1 %cmp25, label %if.then26, label %if.end, !dbg !544

if.then26:                                        ; preds = %if.then19
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !545
  %call27 = call %struct.archive_read_passphrase* @remove_passphrases_from_head(%struct.archive_read* %27), !dbg !547
  store %struct.archive_read_passphrase* %call27, %struct.archive_read_passphrase** %p, align 8, !dbg !548
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !549
  %29 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !550
  call void @add_passphrase_to_tail(%struct.archive_read* %28, %struct.archive_read_passphrase* %29), !dbg !551
  br label %if.end, !dbg !552

if.end:                                           ; preds = %if.then26, %if.then19
  store %struct.archive_read_passphrase* null, %struct.archive_read_passphrase** %p, align 8, !dbg !553
  br label %if.end29, !dbg !554

if.else28:                                        ; preds = %if.else15
  store %struct.archive_read_passphrase* null, %struct.archive_read_passphrase** %p, align 8, !dbg !555
  br label %if.end29

if.end29:                                         ; preds = %if.else28, %if.end
  br label %if.end30

if.end30:                                         ; preds = %if.end29, %if.then10
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %for.end
  %30 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !556
  %cmp32 = icmp ne %struct.archive_read_passphrase* %30, null, !dbg !558
  br i1 %cmp32, label %if.then33, label %if.else35, !dbg !559

if.then33:                                        ; preds = %if.end31
  %31 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !560
  %passphrase34 = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %31, i32 0, i32 0, !dbg !561
  %32 = load i8*, i8** %passphrase34, align 8, !dbg !561
  store i8* %32, i8** %passphrase, align 8, !dbg !562
  br label %if.end54, !dbg !563

if.else35:                                        ; preds = %if.end31
  %33 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !564
  %passphrases36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %33, i32 0, i32 16, !dbg !566
  %callback = getelementptr inbounds %struct.anon, %struct.anon* %passphrases36, i32 0, i32 3, !dbg !567
  %34 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %callback, align 8, !dbg !567
  %cmp37 = icmp ne i8* (%struct.archive*, i8*)* %34, null, !dbg !568
  br i1 %cmp37, label %if.then38, label %if.else52, !dbg !569

if.then38:                                        ; preds = %if.else35
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !570
  %passphrases39 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %35, i32 0, i32 16, !dbg !572
  %callback40 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases39, i32 0, i32 3, !dbg !573
  %36 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %callback40, align 8, !dbg !573
  %37 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !574
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %37, i32 0, i32 0, !dbg !575
  %38 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !576
  %passphrases41 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %38, i32 0, i32 16, !dbg !577
  %client_data = getelementptr inbounds %struct.anon, %struct.anon* %passphrases41, i32 0, i32 4, !dbg !578
  %39 = load i8*, i8** %client_data, align 8, !dbg !578
  %call42 = call i8* %36(%struct.archive* %archive, i8* %39), !dbg !570
  store i8* %call42, i8** %passphrase, align 8, !dbg !579
  %40 = load i8*, i8** %passphrase, align 8, !dbg !580
  %cmp43 = icmp ne i8* %40, null, !dbg !582
  br i1 %cmp43, label %if.then44, label %if.end51, !dbg !583

if.then44:                                        ; preds = %if.then38
  %41 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !584
  %42 = load i8*, i8** %passphrase, align 8, !dbg !586
  %call45 = call %struct.archive_read_passphrase* @new_read_passphrase(%struct.archive_read* %41, i8* %42), !dbg !587
  store %struct.archive_read_passphrase* %call45, %struct.archive_read_passphrase** %p, align 8, !dbg !588
  %43 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !589
  %cmp46 = icmp eq %struct.archive_read_passphrase* %43, null, !dbg !591
  br i1 %cmp46, label %if.then47, label %if.end48, !dbg !592

if.then47:                                        ; preds = %if.then44
  store i8* null, i8** %retval, align 8, !dbg !593
  br label %return, !dbg !593

if.end48:                                         ; preds = %if.then44
  %44 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !594
  %45 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !595
  call void @insert_passphrase_to_head(%struct.archive_read* %44, %struct.archive_read_passphrase* %45), !dbg !596
  %46 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !597
  %passphrases49 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %46, i32 0, i32 16, !dbg !598
  %candidate50 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases49, i32 0, i32 2, !dbg !599
  store i32 1, i32* %candidate50, align 8, !dbg !600
  br label %if.end51, !dbg !601

if.end51:                                         ; preds = %if.end48, %if.then38
  br label %if.end53, !dbg !602

if.else52:                                        ; preds = %if.else35
  store i8* null, i8** %passphrase, align 8, !dbg !603
  br label %if.end53

if.end53:                                         ; preds = %if.else52, %if.end51
  br label %if.end54

if.end54:                                         ; preds = %if.end53, %if.then33
  %47 = load i8*, i8** %passphrase, align 8, !dbg !604
  store i8* %47, i8** %retval, align 8, !dbg !605
  br label %return, !dbg !605

return:                                           ; preds = %if.end54, %if.then47
  %48 = load i8*, i8** %retval, align 8, !dbg !606
  ret i8* %48, !dbg !606
}

; Function Attrs: nounwind uwtable
define internal %struct.archive_read_passphrase* @remove_passphrases_from_head(%struct.archive_read* %a) #0 !dbg !310 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %p = alloca %struct.archive_read_passphrase*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !607, metadata !318), !dbg !608
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p, metadata !609, metadata !318), !dbg !610
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !611
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 16, !dbg !612
  %first = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 0, !dbg !613
  %1 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first, align 8, !dbg !613
  store %struct.archive_read_passphrase* %1, %struct.archive_read_passphrase** %p, align 8, !dbg !614
  %2 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !615
  %cmp = icmp ne %struct.archive_read_passphrase* %2, null, !dbg !617
  br i1 %cmp, label %if.then, label %if.end, !dbg !618

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !619
  %next = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %3, i32 0, i32 1, !dbg !620
  %4 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %next, align 8, !dbg !620
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !621
  %passphrases1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 16, !dbg !622
  %first2 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases1, i32 0, i32 0, !dbg !623
  store %struct.archive_read_passphrase* %4, %struct.archive_read_passphrase** %first2, align 8, !dbg !624
  br label %if.end, !dbg !621

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p, align 8, !dbg !625
  ret %struct.archive_read_passphrase* %6, !dbg !626
}

; Function Attrs: nounwind uwtable
define internal void @insert_passphrase_to_head(%struct.archive_read* %a, %struct.archive_read_passphrase* %p) #0 !dbg !313 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %p.addr = alloca %struct.archive_read_passphrase*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !627, metadata !318), !dbg !628
  store %struct.archive_read_passphrase* %p, %struct.archive_read_passphrase** %p.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_passphrase** %p.addr, metadata !629, metadata !318), !dbg !630
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !631
  %passphrases = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 16, !dbg !632
  %first = getelementptr inbounds %struct.anon, %struct.anon* %passphrases, i32 0, i32 0, !dbg !633
  %1 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %first, align 8, !dbg !633
  %2 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p.addr, align 8, !dbg !634
  %next = getelementptr inbounds %struct.archive_read_passphrase, %struct.archive_read_passphrase* %2, i32 0, i32 1, !dbg !635
  store %struct.archive_read_passphrase* %1, %struct.archive_read_passphrase** %next, align 8, !dbg !636
  %3 = load %struct.archive_read_passphrase*, %struct.archive_read_passphrase** %p.addr, align 8, !dbg !637
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !638
  %passphrases1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 16, !dbg !639
  %first2 = getelementptr inbounds %struct.anon, %struct.anon* %passphrases1, i32 0, i32 0, !dbg !640
  store %struct.archive_read_passphrase* %3, %struct.archive_read_passphrase** %first2, align 8, !dbg !641
  ret void, !dbg !642
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!314, !315}
!llvm.ident = !{!316}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_add_passphrase.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!291 = !{!292, !295, !298, !301, !304, !307, !310, !313}
!292 = distinct !DISubprogram(name: "archive_read_add_passphrase", scope: !1, file: !1, line: 84, type: !293, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = !DISubroutineType(types: !294)
!294 = !{!23, !24, !80}
!295 = distinct !DISubprogram(name: "archive_read_set_passphrase_callback", scope: !1, file: !1, line: 107, type: !296, isLocal: false, isDefinition: true, scopeLine: 109, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!296 = !DISubroutineType(types: !297)
!297 = !{!23, !24, !122, !286}
!298 = distinct !DISubprogram(name: "__archive_read_reset_passphrase", scope: !1, file: !1, line: 125, type: !299, isLocal: false, isDefinition: true, scopeLine: 126, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!299 = !DISubroutineType(types: !300)
!300 = !{null, !4}
!301 = distinct !DISubprogram(name: "__archive_read_next_passphrase", scope: !1, file: !1, line: 135, type: !302, isLocal: false, isDefinition: true, scopeLine: 136, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = !DISubroutineType(types: !303)
!303 = !{!80, !4}
!304 = distinct !DISubprogram(name: "new_read_passphrase", scope: !1, file: !1, line: 63, type: !305, isLocal: true, isDefinition: true, scopeLine: 64, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!305 = !DISubroutineType(types: !306)
!306 = !{!277, !4, !80}
!307 = distinct !DISubprogram(name: "add_passphrase_to_tail", scope: !1, file: !1, line: 35, type: !308, isLocal: true, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!308 = !DISubroutineType(types: !309)
!309 = !{null, !4, !277}
!310 = distinct !DISubprogram(name: "remove_passphrases_from_head", scope: !1, file: !1, line: 44, type: !311, isLocal: true, isDefinition: true, scopeLine: 45, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!311 = !DISubroutineType(types: !312)
!312 = !{!277, !4}
!313 = distinct !DISubprogram(name: "insert_passphrase_to_head", scope: !1, file: !1, line: 55, type: !308, isLocal: true, isDefinition: true, scopeLine: 57, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!314 = !{i32 2, !"Dwarf Version", i32 4}
!315 = !{i32 2, !"Debug Info Version", i32 3}
!316 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!317 = !DILocalVariable(name: "_a", arg: 1, scope: !292, file: !1, line: 84, type: !24)
!318 = !DIExpression()
!319 = !DILocation(line: 84, column: 45, scope: !292)
!320 = !DILocalVariable(name: "passphrase", arg: 2, scope: !292, file: !1, line: 84, type: !80)
!321 = !DILocation(line: 84, column: 61, scope: !292)
!322 = !DILocalVariable(name: "a", scope: !292, file: !1, line: 86, type: !4)
!323 = !DILocation(line: 86, column: 23, scope: !292)
!324 = !DILocation(line: 86, column: 50, scope: !292)
!325 = !DILocation(line: 86, column: 27, scope: !292)
!326 = !DILocalVariable(name: "p", scope: !292, file: !1, line: 87, type: !277)
!327 = !DILocation(line: 87, column: 34, scope: !292)
!328 = !DILocation(line: 89, column: 2, scope: !292)
!329 = !DILocalVariable(name: "magic_test", scope: !330, file: !1, line: 89, type: !23)
!330 = distinct !DILexicalBlock(scope: !292, file: !1, line: 89, column: 2)
!331 = !DILocation(line: 89, column: 2, scope: !330)
!332 = !DILocation(line: 89, column: 2, scope: !333)
!333 = !DILexicalBlockFile(scope: !330, file: !1, discriminator: 1)
!334 = !DILocation(line: 89, column: 2, scope: !335)
!335 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 2)
!336 = distinct !DILexicalBlock(scope: !330, file: !1, line: 89, column: 2)
!337 = !DILocation(line: 89, column: 2, scope: !338)
!338 = !DILexicalBlockFile(scope: !330, file: !1, discriminator: 3)
!339 = !DILocation(line: 92, column: 6, scope: !340)
!340 = distinct !DILexicalBlock(scope: !292, file: !1, line: 92, column: 6)
!341 = !DILocation(line: 92, column: 17, scope: !340)
!342 = !DILocation(line: 92, column: 25, scope: !340)
!343 = !DILocation(line: 92, column: 28, scope: !344)
!344 = !DILexicalBlockFile(scope: !340, file: !1, discriminator: 1)
!345 = !DILocation(line: 92, column: 42, scope: !344)
!346 = !DILocation(line: 92, column: 6, scope: !344)
!347 = !DILocation(line: 93, column: 22, scope: !348)
!348 = distinct !DILexicalBlock(scope: !340, file: !1, line: 92, column: 51)
!349 = !DILocation(line: 93, column: 25, scope: !348)
!350 = !DILocation(line: 93, column: 3, scope: !348)
!351 = !DILocation(line: 95, column: 3, scope: !348)
!352 = !DILocation(line: 98, column: 26, scope: !292)
!353 = !DILocation(line: 98, column: 29, scope: !292)
!354 = !DILocation(line: 98, column: 6, scope: !292)
!355 = !DILocation(line: 98, column: 4, scope: !292)
!356 = !DILocation(line: 99, column: 6, scope: !357)
!357 = distinct !DILexicalBlock(scope: !292, file: !1, line: 99, column: 6)
!358 = !DILocation(line: 99, column: 8, scope: !357)
!359 = !DILocation(line: 99, column: 6, scope: !292)
!360 = !DILocation(line: 100, column: 3, scope: !357)
!361 = !DILocation(line: 101, column: 25, scope: !292)
!362 = !DILocation(line: 101, column: 28, scope: !292)
!363 = !DILocation(line: 101, column: 2, scope: !292)
!364 = !DILocation(line: 103, column: 2, scope: !292)
!365 = !DILocation(line: 104, column: 1, scope: !292)
!366 = !DILocalVariable(name: "a", arg: 1, scope: !304, file: !1, line: 63, type: !4)
!367 = !DILocation(line: 63, column: 42, scope: !304)
!368 = !DILocalVariable(name: "passphrase", arg: 2, scope: !304, file: !1, line: 63, type: !80)
!369 = !DILocation(line: 63, column: 57, scope: !304)
!370 = !DILocalVariable(name: "p", scope: !304, file: !1, line: 65, type: !277)
!371 = !DILocation(line: 65, column: 34, scope: !304)
!372 = !DILocation(line: 67, column: 6, scope: !304)
!373 = !DILocation(line: 67, column: 4, scope: !304)
!374 = !DILocation(line: 68, column: 6, scope: !375)
!375 = distinct !DILexicalBlock(scope: !304, file: !1, line: 68, column: 6)
!376 = !DILocation(line: 68, column: 8, scope: !375)
!377 = !DILocation(line: 68, column: 6, scope: !304)
!378 = !DILocation(line: 69, column: 22, scope: !379)
!379 = distinct !DILexicalBlock(scope: !375, file: !1, line: 68, column: 17)
!380 = !DILocation(line: 69, column: 25, scope: !379)
!381 = !DILocation(line: 69, column: 3, scope: !379)
!382 = !DILocation(line: 71, column: 3, scope: !379)
!383 = !DILocation(line: 73, column: 25, scope: !304)
!384 = !DILocation(line: 73, column: 18, scope: !304)
!385 = !DILocation(line: 73, column: 2, scope: !304)
!386 = !DILocation(line: 73, column: 5, scope: !304)
!387 = !DILocation(line: 73, column: 16, scope: !304)
!388 = !DILocation(line: 74, column: 6, scope: !389)
!389 = distinct !DILexicalBlock(scope: !304, file: !1, line: 74, column: 6)
!390 = !DILocation(line: 74, column: 9, scope: !389)
!391 = !DILocation(line: 74, column: 20, scope: !389)
!392 = !DILocation(line: 74, column: 6, scope: !304)
!393 = !DILocation(line: 75, column: 8, scope: !394)
!394 = distinct !DILexicalBlock(scope: !389, file: !1, line: 74, column: 29)
!395 = !DILocation(line: 75, column: 3, scope: !394)
!396 = !DILocation(line: 76, column: 22, scope: !394)
!397 = !DILocation(line: 76, column: 25, scope: !394)
!398 = !DILocation(line: 76, column: 3, scope: !394)
!399 = !DILocation(line: 78, column: 3, scope: !394)
!400 = !DILocation(line: 80, column: 10, scope: !304)
!401 = !DILocation(line: 80, column: 2, scope: !304)
!402 = !DILocation(line: 81, column: 1, scope: !304)
!403 = !DILocalVariable(name: "a", arg: 1, scope: !307, file: !1, line: 35, type: !4)
!404 = !DILocation(line: 35, column: 45, scope: !307)
!405 = !DILocalVariable(name: "p", arg: 2, scope: !307, file: !1, line: 36, type: !277)
!406 = !DILocation(line: 36, column: 37, scope: !307)
!407 = !DILocation(line: 38, column: 25, scope: !307)
!408 = !DILocation(line: 38, column: 3, scope: !307)
!409 = !DILocation(line: 38, column: 6, scope: !307)
!410 = !DILocation(line: 38, column: 18, scope: !307)
!411 = !DILocation(line: 38, column: 23, scope: !307)
!412 = !DILocation(line: 39, column: 25, scope: !307)
!413 = !DILocation(line: 39, column: 28, scope: !307)
!414 = !DILocation(line: 39, column: 2, scope: !307)
!415 = !DILocation(line: 39, column: 5, scope: !307)
!416 = !DILocation(line: 39, column: 17, scope: !307)
!417 = !DILocation(line: 39, column: 22, scope: !307)
!418 = !DILocation(line: 40, column: 2, scope: !307)
!419 = !DILocation(line: 40, column: 5, scope: !307)
!420 = !DILocation(line: 40, column: 10, scope: !307)
!421 = !DILocation(line: 41, column: 1, scope: !307)
!422 = !DILocalVariable(name: "_a", arg: 1, scope: !295, file: !1, line: 107, type: !24)
!423 = !DILocation(line: 107, column: 54, scope: !295)
!424 = !DILocalVariable(name: "client_data", arg: 2, scope: !295, file: !1, line: 107, type: !122)
!425 = !DILocation(line: 107, column: 64, scope: !295)
!426 = !DILocalVariable(name: "cb", arg: 3, scope: !295, file: !1, line: 108, type: !286)
!427 = !DILocation(line: 108, column: 34, scope: !295)
!428 = !DILocalVariable(name: "a", scope: !295, file: !1, line: 110, type: !4)
!429 = !DILocation(line: 110, column: 23, scope: !295)
!430 = !DILocation(line: 110, column: 50, scope: !295)
!431 = !DILocation(line: 110, column: 27, scope: !295)
!432 = !DILocation(line: 112, column: 2, scope: !295)
!433 = !DILocalVariable(name: "magic_test", scope: !434, file: !1, line: 112, type: !23)
!434 = distinct !DILexicalBlock(scope: !295, file: !1, line: 112, column: 2)
!435 = !DILocation(line: 112, column: 2, scope: !434)
!436 = !DILocation(line: 112, column: 2, scope: !437)
!437 = !DILexicalBlockFile(scope: !434, file: !1, discriminator: 1)
!438 = !DILocation(line: 112, column: 2, scope: !439)
!439 = !DILexicalBlockFile(scope: !440, file: !1, discriminator: 2)
!440 = distinct !DILexicalBlock(scope: !434, file: !1, line: 112, column: 2)
!441 = !DILocation(line: 112, column: 2, scope: !442)
!442 = !DILexicalBlockFile(scope: !434, file: !1, discriminator: 3)
!443 = !DILocation(line: 115, column: 28, scope: !295)
!444 = !DILocation(line: 115, column: 2, scope: !295)
!445 = !DILocation(line: 115, column: 5, scope: !295)
!446 = !DILocation(line: 115, column: 17, scope: !295)
!447 = !DILocation(line: 115, column: 26, scope: !295)
!448 = !DILocation(line: 116, column: 31, scope: !295)
!449 = !DILocation(line: 116, column: 2, scope: !295)
!450 = !DILocation(line: 116, column: 5, scope: !295)
!451 = !DILocation(line: 116, column: 17, scope: !295)
!452 = !DILocation(line: 116, column: 29, scope: !295)
!453 = !DILocation(line: 117, column: 2, scope: !295)
!454 = !DILocation(line: 118, column: 1, scope: !295)
!455 = !DILocalVariable(name: "a", arg: 1, scope: !298, file: !1, line: 125, type: !4)
!456 = !DILocation(line: 125, column: 54, scope: !298)
!457 = !DILocation(line: 128, column: 2, scope: !298)
!458 = !DILocation(line: 128, column: 5, scope: !298)
!459 = !DILocation(line: 128, column: 17, scope: !298)
!460 = !DILocation(line: 128, column: 27, scope: !298)
!461 = !DILocation(line: 129, column: 1, scope: !298)
!462 = !DILocalVariable(name: "a", arg: 1, scope: !301, file: !1, line: 135, type: !4)
!463 = !DILocation(line: 135, column: 53, scope: !301)
!464 = !DILocalVariable(name: "p", scope: !301, file: !1, line: 137, type: !277)
!465 = !DILocation(line: 137, column: 34, scope: !301)
!466 = !DILocalVariable(name: "passphrase", scope: !301, file: !1, line: 138, type: !80)
!467 = !DILocation(line: 138, column: 14, scope: !301)
!468 = !DILocation(line: 140, column: 6, scope: !469)
!469 = distinct !DILexicalBlock(scope: !301, file: !1, line: 140, column: 6)
!470 = !DILocation(line: 140, column: 9, scope: !469)
!471 = !DILocation(line: 140, column: 21, scope: !469)
!472 = !DILocation(line: 140, column: 31, scope: !469)
!473 = !DILocation(line: 140, column: 6, scope: !301)
!474 = !DILocalVariable(name: "cnt", scope: !475, file: !1, line: 142, type: !23)
!475 = distinct !DILexicalBlock(scope: !469, file: !1, line: 140, column: 36)
!476 = !DILocation(line: 142, column: 7, scope: !475)
!477 = !DILocation(line: 144, column: 12, scope: !478)
!478 = distinct !DILexicalBlock(scope: !475, file: !1, line: 144, column: 3)
!479 = !DILocation(line: 144, column: 15, scope: !478)
!480 = !DILocation(line: 144, column: 27, scope: !478)
!481 = !DILocation(line: 144, column: 10, scope: !478)
!482 = !DILocation(line: 144, column: 8, scope: !478)
!483 = !DILocation(line: 144, column: 34, scope: !484)
!484 = !DILexicalBlockFile(scope: !485, file: !1, discriminator: 1)
!485 = distinct !DILexicalBlock(scope: !478, file: !1, line: 144, column: 3)
!486 = !DILocation(line: 144, column: 36, scope: !484)
!487 = !DILocation(line: 144, column: 3, scope: !484)
!488 = !DILocation(line: 145, column: 7, scope: !485)
!489 = !DILocation(line: 145, column: 4, scope: !485)
!490 = !DILocation(line: 144, column: 49, scope: !491)
!491 = !DILexicalBlockFile(scope: !485, file: !1, discriminator: 2)
!492 = !DILocation(line: 144, column: 52, scope: !491)
!493 = !DILocation(line: 144, column: 47, scope: !491)
!494 = !DILocation(line: 144, column: 3, scope: !491)
!495 = !DILocation(line: 146, column: 30, scope: !475)
!496 = !DILocation(line: 146, column: 3, scope: !475)
!497 = !DILocation(line: 146, column: 6, scope: !475)
!498 = !DILocation(line: 146, column: 18, scope: !475)
!499 = !DILocation(line: 146, column: 28, scope: !475)
!500 = !DILocation(line: 147, column: 7, scope: !475)
!501 = !DILocation(line: 147, column: 10, scope: !475)
!502 = !DILocation(line: 147, column: 22, scope: !475)
!503 = !DILocation(line: 147, column: 5, scope: !475)
!504 = !DILocation(line: 148, column: 2, scope: !475)
!505 = !DILocation(line: 148, column: 13, scope: !506)
!506 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 1)
!507 = distinct !DILexicalBlock(scope: !469, file: !1, line: 148, column: 13)
!508 = !DILocation(line: 148, column: 16, scope: !506)
!509 = !DILocation(line: 148, column: 28, scope: !506)
!510 = !DILocation(line: 148, column: 38, scope: !506)
!511 = !DILocation(line: 150, column: 3, scope: !512)
!512 = distinct !DILexicalBlock(scope: !507, file: !1, line: 148, column: 43)
!513 = !DILocation(line: 150, column: 6, scope: !512)
!514 = !DILocation(line: 150, column: 18, scope: !512)
!515 = !DILocation(line: 150, column: 27, scope: !512)
!516 = !DILocation(line: 151, column: 36, scope: !512)
!517 = !DILocation(line: 151, column: 7, scope: !512)
!518 = !DILocation(line: 151, column: 5, scope: !512)
!519 = !DILocation(line: 152, column: 26, scope: !512)
!520 = !DILocation(line: 152, column: 29, scope: !512)
!521 = !DILocation(line: 152, column: 3, scope: !512)
!522 = !DILocation(line: 154, column: 7, scope: !512)
!523 = !DILocation(line: 154, column: 10, scope: !512)
!524 = !DILocation(line: 154, column: 22, scope: !512)
!525 = !DILocation(line: 154, column: 5, scope: !512)
!526 = !DILocation(line: 155, column: 2, scope: !512)
!527 = !DILocation(line: 155, column: 13, scope: !528)
!528 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 1)
!529 = distinct !DILexicalBlock(scope: !507, file: !1, line: 155, column: 13)
!530 = !DILocation(line: 155, column: 16, scope: !528)
!531 = !DILocation(line: 155, column: 28, scope: !528)
!532 = !DILocation(line: 155, column: 38, scope: !528)
!533 = !DILocation(line: 157, column: 3, scope: !534)
!534 = distinct !DILexicalBlock(scope: !529, file: !1, line: 155, column: 44)
!535 = !DILocation(line: 157, column: 6, scope: !534)
!536 = !DILocation(line: 157, column: 18, scope: !534)
!537 = !DILocation(line: 157, column: 28, scope: !534)
!538 = !DILocation(line: 158, column: 7, scope: !539)
!539 = distinct !DILexicalBlock(scope: !534, file: !1, line: 158, column: 7)
!540 = !DILocation(line: 158, column: 10, scope: !539)
!541 = !DILocation(line: 158, column: 22, scope: !539)
!542 = !DILocation(line: 158, column: 29, scope: !539)
!543 = !DILocation(line: 158, column: 34, scope: !539)
!544 = !DILocation(line: 158, column: 7, scope: !534)
!545 = !DILocation(line: 160, column: 37, scope: !546)
!546 = distinct !DILexicalBlock(scope: !539, file: !1, line: 158, column: 43)
!547 = !DILocation(line: 160, column: 8, scope: !546)
!548 = !DILocation(line: 160, column: 6, scope: !546)
!549 = !DILocation(line: 161, column: 27, scope: !546)
!550 = !DILocation(line: 161, column: 30, scope: !546)
!551 = !DILocation(line: 161, column: 4, scope: !546)
!552 = !DILocation(line: 162, column: 3, scope: !546)
!553 = !DILocation(line: 163, column: 5, scope: !534)
!554 = !DILocation(line: 164, column: 2, scope: !534)
!555 = !DILocation(line: 165, column: 5, scope: !529)
!556 = !DILocation(line: 167, column: 6, scope: !557)
!557 = distinct !DILexicalBlock(scope: !301, file: !1, line: 167, column: 6)
!558 = !DILocation(line: 167, column: 8, scope: !557)
!559 = !DILocation(line: 167, column: 6, scope: !301)
!560 = !DILocation(line: 168, column: 16, scope: !557)
!561 = !DILocation(line: 168, column: 19, scope: !557)
!562 = !DILocation(line: 168, column: 14, scope: !557)
!563 = !DILocation(line: 168, column: 3, scope: !557)
!564 = !DILocation(line: 169, column: 11, scope: !565)
!565 = distinct !DILexicalBlock(scope: !557, file: !1, line: 169, column: 11)
!566 = !DILocation(line: 169, column: 14, scope: !565)
!567 = !DILocation(line: 169, column: 26, scope: !565)
!568 = !DILocation(line: 169, column: 35, scope: !565)
!569 = !DILocation(line: 169, column: 11, scope: !557)
!570 = !DILocation(line: 173, column: 16, scope: !571)
!571 = distinct !DILexicalBlock(scope: !565, file: !1, line: 169, column: 44)
!572 = !DILocation(line: 173, column: 19, scope: !571)
!573 = !DILocation(line: 173, column: 31, scope: !571)
!574 = !DILocation(line: 173, column: 41, scope: !571)
!575 = !DILocation(line: 173, column: 44, scope: !571)
!576 = !DILocation(line: 174, column: 7, scope: !571)
!577 = !DILocation(line: 174, column: 10, scope: !571)
!578 = !DILocation(line: 174, column: 22, scope: !571)
!579 = !DILocation(line: 173, column: 14, scope: !571)
!580 = !DILocation(line: 175, column: 7, scope: !581)
!581 = distinct !DILexicalBlock(scope: !571, file: !1, line: 175, column: 7)
!582 = !DILocation(line: 175, column: 18, scope: !581)
!583 = !DILocation(line: 175, column: 7, scope: !571)
!584 = !DILocation(line: 176, column: 28, scope: !585)
!585 = distinct !DILexicalBlock(scope: !581, file: !1, line: 175, column: 27)
!586 = !DILocation(line: 176, column: 31, scope: !585)
!587 = !DILocation(line: 176, column: 8, scope: !585)
!588 = !DILocation(line: 176, column: 6, scope: !585)
!589 = !DILocation(line: 177, column: 8, scope: !590)
!590 = distinct !DILexicalBlock(scope: !585, file: !1, line: 177, column: 8)
!591 = !DILocation(line: 177, column: 10, scope: !590)
!592 = !DILocation(line: 177, column: 8, scope: !585)
!593 = !DILocation(line: 178, column: 5, scope: !590)
!594 = !DILocation(line: 179, column: 30, scope: !585)
!595 = !DILocation(line: 179, column: 33, scope: !585)
!596 = !DILocation(line: 179, column: 4, scope: !585)
!597 = !DILocation(line: 180, column: 4, scope: !585)
!598 = !DILocation(line: 180, column: 7, scope: !585)
!599 = !DILocation(line: 180, column: 19, scope: !585)
!600 = !DILocation(line: 180, column: 29, scope: !585)
!601 = !DILocation(line: 181, column: 3, scope: !585)
!602 = !DILocation(line: 182, column: 2, scope: !571)
!603 = !DILocation(line: 183, column: 14, scope: !565)
!604 = !DILocation(line: 185, column: 10, scope: !301)
!605 = !DILocation(line: 185, column: 2, scope: !301)
!606 = !DILocation(line: 186, column: 1, scope: !301)
!607 = !DILocalVariable(name: "a", arg: 1, scope: !310, file: !1, line: 44, type: !4)
!608 = !DILocation(line: 44, column: 51, scope: !310)
!609 = !DILocalVariable(name: "p", scope: !310, file: !1, line: 46, type: !277)
!610 = !DILocation(line: 46, column: 34, scope: !310)
!611 = !DILocation(line: 48, column: 6, scope: !310)
!612 = !DILocation(line: 48, column: 9, scope: !310)
!613 = !DILocation(line: 48, column: 21, scope: !310)
!614 = !DILocation(line: 48, column: 4, scope: !310)
!615 = !DILocation(line: 49, column: 6, scope: !616)
!616 = distinct !DILexicalBlock(scope: !310, file: !1, line: 49, column: 6)
!617 = !DILocation(line: 49, column: 8, scope: !616)
!618 = !DILocation(line: 49, column: 6, scope: !310)
!619 = !DILocation(line: 50, column: 26, scope: !616)
!620 = !DILocation(line: 50, column: 29, scope: !616)
!621 = !DILocation(line: 50, column: 3, scope: !616)
!622 = !DILocation(line: 50, column: 6, scope: !616)
!623 = !DILocation(line: 50, column: 18, scope: !616)
!624 = !DILocation(line: 50, column: 24, scope: !616)
!625 = !DILocation(line: 51, column: 10, scope: !310)
!626 = !DILocation(line: 51, column: 2, scope: !310)
!627 = !DILocalVariable(name: "a", arg: 1, scope: !313, file: !1, line: 55, type: !4)
!628 = !DILocation(line: 55, column: 48, scope: !313)
!629 = !DILocalVariable(name: "p", arg: 2, scope: !313, file: !1, line: 56, type: !277)
!630 = !DILocation(line: 56, column: 37, scope: !313)
!631 = !DILocation(line: 58, column: 12, scope: !313)
!632 = !DILocation(line: 58, column: 15, scope: !313)
!633 = !DILocation(line: 58, column: 27, scope: !313)
!634 = !DILocation(line: 58, column: 2, scope: !313)
!635 = !DILocation(line: 58, column: 5, scope: !313)
!636 = !DILocation(line: 58, column: 10, scope: !313)
!637 = !DILocation(line: 59, column: 25, scope: !313)
!638 = !DILocation(line: 59, column: 2, scope: !313)
!639 = !DILocation(line: 59, column: 5, scope: !313)
!640 = !DILocation(line: 59, column: 17, scope: !313)
!641 = !DILocation(line: 59, column: 23, scope: !313)
!642 = !DILocation(line: 60, column: 1, scope: !313)
