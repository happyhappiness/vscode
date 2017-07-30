; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_set_format.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
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

@.str = private unnamed_addr constant [5 x i8] c"7zip\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"ar\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"cab\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"cpio\00", align 1
@.str.4 = private unnamed_addr constant [8 x i8] c"iso9660\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"lha\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"mtree\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"rar\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"tar\00", align 1
@.str.9 = private unnamed_addr constant [4 x i8] c"xar\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"zip\00", align 1
@.str.11 = private unnamed_addr constant [30 x i8] c"Invalid format code specified\00", align 1
@.str.12 = private unnamed_addr constant [37 x i8] c"Internal error: Unable to set format\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_set_format(%struct.archive* %_a, i32 %code) #0 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %code.addr = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %slots = alloca i32, align 4
  %i = alloca i32, align 4
  %str = alloca [10 x i8], align 1
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !296, metadata !297), !dbg !298
  store i32 %code, i32* %code.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %code.addr, metadata !299, metadata !297), !dbg !300
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !301, metadata !297), !dbg !302
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !303, metadata !297), !dbg !304
  call void @llvm.dbg.declare(metadata i32* %slots, metadata !305, metadata !297), !dbg !306
  call void @llvm.dbg.declare(metadata i32* %i, metadata !307, metadata !297), !dbg !308
  call void @llvm.dbg.declare(metadata [10 x i8]* %str, metadata !309, metadata !297), !dbg !313
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !314, metadata !297), !dbg !315
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !316
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !317
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !315
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !318
  %3 = load i32, i32* %code.addr, align 4, !dbg !320
  %call = call i32 @archive_read_support_format_by_code(%struct.archive* %2, i32 %3), !dbg !321
  store i32 %call, i32* %r1, align 4, !dbg !322
  %cmp = icmp slt i32 %call, 0, !dbg !323
  br i1 %cmp, label %if.then, label %if.end, !dbg !324

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %r1, align 4, !dbg !325
  store i32 %4, i32* %retval, align 4, !dbg !326
  br label %return, !dbg !326

if.end:                                           ; preds = %entry
  store i32 0, i32* %r2, align 4, !dbg !327
  store i32 0, i32* %r1, align 4, !dbg !328
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !329
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 13, !dbg !331
  %6 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !331
  %tobool = icmp ne %struct.archive_format_descriptor* %6, null, !dbg !329
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !332

if.then1:                                         ; preds = %if.end
  store i32 -20, i32* %r2, align 4, !dbg !333
  br label %if.end2, !dbg !334

if.end2:                                          ; preds = %if.then1, %if.end
  %7 = load i32, i32* %code.addr, align 4, !dbg !335
  %and = and i32 %7, 16711680, !dbg !336
  switch i32 %and, label %sw.default [
    i32 917504, label %sw.bb
    i32 458752, label %sw.bb4
    i32 786432, label %sw.bb7
    i32 65536, label %sw.bb10
    i32 262144, label %sw.bb13
    i32 720896, label %sw.bb16
    i32 524288, label %sw.bb19
    i32 851968, label %sw.bb22
    i32 196608, label %sw.bb25
    i32 655360, label %sw.bb28
    i32 327680, label %sw.bb31
  ], !dbg !337

sw.bb:                                            ; preds = %if.end2
  %arraydecay = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !338
  %call3 = call i8* @strcpy(i8* %arraydecay, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0)) #5, !dbg !340
  br label %sw.epilog, !dbg !341

sw.bb4:                                           ; preds = %if.end2
  %arraydecay5 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !342
  %call6 = call i8* @strcpy(i8* %arraydecay5, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0)) #5, !dbg !343
  br label %sw.epilog, !dbg !344

sw.bb7:                                           ; preds = %if.end2
  %arraydecay8 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !345
  %call9 = call i8* @strcpy(i8* %arraydecay8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0)) #5, !dbg !346
  br label %sw.epilog, !dbg !347

sw.bb10:                                          ; preds = %if.end2
  %arraydecay11 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !348
  %call12 = call i8* @strcpy(i8* %arraydecay11, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0)) #5, !dbg !349
  br label %sw.epilog, !dbg !350

sw.bb13:                                          ; preds = %if.end2
  %arraydecay14 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !351
  %call15 = call i8* @strcpy(i8* %arraydecay14, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.4, i32 0, i32 0)) #5, !dbg !352
  br label %sw.epilog, !dbg !353

sw.bb16:                                          ; preds = %if.end2
  %arraydecay17 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !354
  %call18 = call i8* @strcpy(i8* %arraydecay17, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0)) #5, !dbg !355
  br label %sw.epilog, !dbg !356

sw.bb19:                                          ; preds = %if.end2
  %arraydecay20 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !357
  %call21 = call i8* @strcpy(i8* %arraydecay20, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0)) #5, !dbg !358
  br label %sw.epilog, !dbg !359

sw.bb22:                                          ; preds = %if.end2
  %arraydecay23 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !360
  %call24 = call i8* @strcpy(i8* %arraydecay23, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !361
  br label %sw.epilog, !dbg !362

sw.bb25:                                          ; preds = %if.end2
  %arraydecay26 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !363
  %call27 = call i8* @strcpy(i8* %arraydecay26, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #5, !dbg !364
  br label %sw.epilog, !dbg !365

sw.bb28:                                          ; preds = %if.end2
  %arraydecay29 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !366
  %call30 = call i8* @strcpy(i8* %arraydecay29, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i32 0, i32 0)) #5, !dbg !367
  br label %sw.epilog, !dbg !368

sw.bb31:                                          ; preds = %if.end2
  %arraydecay32 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !369
  %call33 = call i8* @strcpy(i8* %arraydecay32, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i32 0, i32 0)) #5, !dbg !370
  br label %sw.epilog, !dbg !371

sw.default:                                       ; preds = %if.end2
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !372
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !373
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.11, i32 0, i32 0)), !dbg !374
  store i32 -30, i32* %retval, align 4, !dbg !375
  br label %return, !dbg !375

sw.epilog:                                        ; preds = %sw.bb31, %sw.bb28, %sw.bb25, %sw.bb22, %sw.bb19, %sw.bb16, %sw.bb13, %sw.bb10, %sw.bb7, %sw.bb4, %sw.bb
  store i32 16, i32* %slots, align 4, !dbg !376
  %9 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !377
  %formats = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 12, !dbg !378
  %arrayidx = getelementptr inbounds [16 x %struct.archive_format_descriptor], [16 x %struct.archive_format_descriptor]* %formats, i64 0, i64 0, !dbg !377
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !379
  %format34 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 13, !dbg !380
  store %struct.archive_format_descriptor* %arrayidx, %struct.archive_format_descriptor** %format34, align 8, !dbg !381
  store i32 0, i32* %i, align 4, !dbg !382
  br label %for.cond, !dbg !384

for.cond:                                         ; preds = %for.inc, %sw.epilog
  %11 = load i32, i32* %i, align 4, !dbg !385
  %12 = load i32, i32* %slots, align 4, !dbg !388
  %cmp35 = icmp slt i32 %11, %12, !dbg !389
  br i1 %cmp35, label %for.body, label %for.end, !dbg !390

for.body:                                         ; preds = %for.cond
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !391
  %format36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 13, !dbg !394
  %14 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format36, align 8, !dbg !394
  %name = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %14, i32 0, i32 1, !dbg !395
  %15 = load i8*, i8** %name, align 8, !dbg !395
  %tobool37 = icmp ne i8* %15, null, !dbg !391
  br i1 %tobool37, label %lor.lhs.false, label %if.then43, !dbg !396

lor.lhs.false:                                    ; preds = %for.body
  %16 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !397
  %format38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 13, !dbg !399
  %17 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format38, align 8, !dbg !399
  %name39 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %17, i32 0, i32 1, !dbg !400
  %18 = load i8*, i8** %name39, align 8, !dbg !400
  %arraydecay40 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !401
  %call41 = call i32 @strcmp(i8* %18, i8* %arraydecay40) #6, !dbg !402
  %tobool42 = icmp ne i32 %call41, 0, !dbg !402
  br i1 %tobool42, label %if.end44, label %if.then43, !dbg !403

if.then43:                                        ; preds = %lor.lhs.false, %for.body
  br label %for.end, !dbg !404

if.end44:                                         ; preds = %lor.lhs.false
  br label %for.inc, !dbg !405

for.inc:                                          ; preds = %if.end44
  %19 = load i32, i32* %i, align 4, !dbg !406
  %inc = add nsw i32 %19, 1, !dbg !406
  store i32 %inc, i32* %i, align 4, !dbg !406
  %20 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !408
  %format45 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %20, i32 0, i32 13, !dbg !409
  %21 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format45, align 8, !dbg !410
  %incdec.ptr = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %21, i32 1, !dbg !410
  store %struct.archive_format_descriptor* %incdec.ptr, %struct.archive_format_descriptor** %format45, align 8, !dbg !410
  br label %for.cond, !dbg !411

for.end:                                          ; preds = %if.then43, %for.cond
  %22 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !412
  %format46 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 13, !dbg !414
  %23 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format46, align 8, !dbg !414
  %name47 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %23, i32 0, i32 1, !dbg !415
  %24 = load i8*, i8** %name47, align 8, !dbg !415
  %tobool48 = icmp ne i8* %24, null, !dbg !412
  br i1 %tobool48, label %lor.lhs.false49, label %if.then55, !dbg !416

lor.lhs.false49:                                  ; preds = %for.end
  %25 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !417
  %format50 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 13, !dbg !419
  %26 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format50, align 8, !dbg !419
  %name51 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %26, i32 0, i32 1, !dbg !420
  %27 = load i8*, i8** %name51, align 8, !dbg !420
  %arraydecay52 = getelementptr inbounds [10 x i8], [10 x i8]* %str, i32 0, i32 0, !dbg !421
  %call53 = call i32 @strcmp(i8* %27, i8* %arraydecay52) #6, !dbg !422
  %tobool54 = icmp ne i32 %call53, 0, !dbg !422
  br i1 %tobool54, label %if.then55, label %if.end57, !dbg !423

if.then55:                                        ; preds = %lor.lhs.false49, %for.end
  %28 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !424
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 0, !dbg !426
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive56, i32 22, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.12, i32 0, i32 0)), !dbg !427
  store i32 -30, i32* %r1, align 4, !dbg !428
  br label %if.end57, !dbg !429

if.end57:                                         ; preds = %if.then55, %lor.lhs.false49
  %29 = load i32, i32* %r1, align 4, !dbg !430
  %30 = load i32, i32* %r2, align 4, !dbg !431
  %cmp58 = icmp slt i32 %29, %30, !dbg !432
  br i1 %cmp58, label %cond.true, label %cond.false, !dbg !433

cond.true:                                        ; preds = %if.end57
  %31 = load i32, i32* %r1, align 4, !dbg !434
  br label %cond.end, !dbg !436

cond.false:                                       ; preds = %if.end57
  %32 = load i32, i32* %r2, align 4, !dbg !437
  br label %cond.end, !dbg !439

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %31, %cond.true ], [ %32, %cond.false ], !dbg !440
  store i32 %cond, i32* %retval, align 4, !dbg !442
  br label %return, !dbg !442

return:                                           ; preds = %cond.end, %sw.default, %if.then
  %33 = load i32, i32* %retval, align 4, !dbg !443
  ret i32 %33, !dbg !443
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @archive_read_support_format_by_code(%struct.archive*, i32) #2

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!293, !294}
!llvm.ident = !{!295}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_set_format.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
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
!291 = !{!292}
!292 = distinct !DISubprogram(name: "archive_read_set_format", scope: !1, file: !1, line: 38, type: !74, isLocal: false, isDefinition: true, scopeLine: 39, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = !{i32 2, !"Dwarf Version", i32 4}
!294 = !{i32 2, !"Debug Info Version", i32 3}
!295 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!296 = !DILocalVariable(name: "_a", arg: 1, scope: !292, file: !1, line: 38, type: !24)
!297 = !DIExpression()
!298 = !DILocation(line: 38, column: 41, scope: !292)
!299 = !DILocalVariable(name: "code", arg: 2, scope: !292, file: !1, line: 38, type: !23)
!300 = !DILocation(line: 38, column: 49, scope: !292)
!301 = !DILocalVariable(name: "r1", scope: !292, file: !1, line: 40, type: !23)
!302 = !DILocation(line: 40, column: 7, scope: !292)
!303 = !DILocalVariable(name: "r2", scope: !292, file: !1, line: 40, type: !23)
!304 = !DILocation(line: 40, column: 11, scope: !292)
!305 = !DILocalVariable(name: "slots", scope: !292, file: !1, line: 40, type: !23)
!306 = !DILocation(line: 40, column: 15, scope: !292)
!307 = !DILocalVariable(name: "i", scope: !292, file: !1, line: 40, type: !23)
!308 = !DILocation(line: 40, column: 22, scope: !292)
!309 = !DILocalVariable(name: "str", scope: !292, file: !1, line: 41, type: !310)
!310 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 80, align: 8, elements: !311)
!311 = !{!312}
!312 = !DISubrange(count: 10)
!313 = !DILocation(line: 41, column: 8, scope: !292)
!314 = !DILocalVariable(name: "a", scope: !292, file: !1, line: 42, type: !4)
!315 = !DILocation(line: 42, column: 24, scope: !292)
!316 = !DILocation(line: 42, column: 51, scope: !292)
!317 = !DILocation(line: 42, column: 28, scope: !292)
!318 = !DILocation(line: 44, column: 49, scope: !319)
!319 = distinct !DILexicalBlock(scope: !292, file: !1, line: 44, column: 7)
!320 = !DILocation(line: 44, column: 53, scope: !319)
!321 = !DILocation(line: 44, column: 13, scope: !319)
!322 = !DILocation(line: 44, column: 11, scope: !319)
!323 = !DILocation(line: 44, column: 60, scope: !319)
!324 = !DILocation(line: 44, column: 7, scope: !292)
!325 = !DILocation(line: 45, column: 12, scope: !319)
!326 = !DILocation(line: 45, column: 5, scope: !319)
!327 = !DILocation(line: 47, column: 11, scope: !292)
!328 = !DILocation(line: 47, column: 6, scope: !292)
!329 = !DILocation(line: 48, column: 7, scope: !330)
!330 = distinct !DILexicalBlock(scope: !292, file: !1, line: 48, column: 7)
!331 = !DILocation(line: 48, column: 10, scope: !330)
!332 = !DILocation(line: 48, column: 7, scope: !292)
!333 = !DILocation(line: 49, column: 8, scope: !330)
!334 = !DILocation(line: 49, column: 5, scope: !330)
!335 = !DILocation(line: 50, column: 11, scope: !292)
!336 = !DILocation(line: 50, column: 16, scope: !292)
!337 = !DILocation(line: 50, column: 3, scope: !292)
!338 = !DILocation(line: 53, column: 14, scope: !339)
!339 = distinct !DILexicalBlock(scope: !292, file: !1, line: 51, column: 3)
!340 = !DILocation(line: 53, column: 7, scope: !339)
!341 = !DILocation(line: 54, column: 7, scope: !339)
!342 = !DILocation(line: 56, column: 14, scope: !339)
!343 = !DILocation(line: 56, column: 7, scope: !339)
!344 = !DILocation(line: 57, column: 7, scope: !339)
!345 = !DILocation(line: 59, column: 14, scope: !339)
!346 = !DILocation(line: 59, column: 7, scope: !339)
!347 = !DILocation(line: 60, column: 7, scope: !339)
!348 = !DILocation(line: 62, column: 14, scope: !339)
!349 = !DILocation(line: 62, column: 7, scope: !339)
!350 = !DILocation(line: 63, column: 7, scope: !339)
!351 = !DILocation(line: 65, column: 14, scope: !339)
!352 = !DILocation(line: 65, column: 7, scope: !339)
!353 = !DILocation(line: 66, column: 7, scope: !339)
!354 = !DILocation(line: 68, column: 14, scope: !339)
!355 = !DILocation(line: 68, column: 7, scope: !339)
!356 = !DILocation(line: 69, column: 7, scope: !339)
!357 = !DILocation(line: 71, column: 14, scope: !339)
!358 = !DILocation(line: 71, column: 7, scope: !339)
!359 = !DILocation(line: 72, column: 7, scope: !339)
!360 = !DILocation(line: 74, column: 14, scope: !339)
!361 = !DILocation(line: 74, column: 7, scope: !339)
!362 = !DILocation(line: 75, column: 7, scope: !339)
!363 = !DILocation(line: 77, column: 14, scope: !339)
!364 = !DILocation(line: 77, column: 7, scope: !339)
!365 = !DILocation(line: 78, column: 7, scope: !339)
!366 = !DILocation(line: 80, column: 14, scope: !339)
!367 = !DILocation(line: 80, column: 7, scope: !339)
!368 = !DILocation(line: 81, column: 7, scope: !339)
!369 = !DILocation(line: 83, column: 14, scope: !339)
!370 = !DILocation(line: 83, column: 7, scope: !339)
!371 = !DILocation(line: 84, column: 7, scope: !339)
!372 = !DILocation(line: 86, column: 26, scope: !339)
!373 = !DILocation(line: 86, column: 29, scope: !339)
!374 = !DILocation(line: 86, column: 7, scope: !339)
!375 = !DILocation(line: 88, column: 7, scope: !339)
!376 = !DILocation(line: 91, column: 9, scope: !292)
!377 = !DILocation(line: 92, column: 17, scope: !292)
!378 = !DILocation(line: 92, column: 20, scope: !292)
!379 = !DILocation(line: 92, column: 3, scope: !292)
!380 = !DILocation(line: 92, column: 6, scope: !292)
!381 = !DILocation(line: 92, column: 13, scope: !292)
!382 = !DILocation(line: 93, column: 10, scope: !383)
!383 = distinct !DILexicalBlock(scope: !292, file: !1, line: 93, column: 3)
!384 = !DILocation(line: 93, column: 8, scope: !383)
!385 = !DILocation(line: 93, column: 15, scope: !386)
!386 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 1)
!387 = distinct !DILexicalBlock(scope: !383, file: !1, line: 93, column: 3)
!388 = !DILocation(line: 93, column: 19, scope: !386)
!389 = !DILocation(line: 93, column: 17, scope: !386)
!390 = !DILocation(line: 93, column: 3, scope: !386)
!391 = !DILocation(line: 94, column: 10, scope: !392)
!392 = distinct !DILexicalBlock(scope: !393, file: !1, line: 94, column: 9)
!393 = distinct !DILexicalBlock(scope: !387, file: !1, line: 93, column: 44)
!394 = !DILocation(line: 94, column: 13, scope: !392)
!395 = !DILocation(line: 94, column: 21, scope: !392)
!396 = !DILocation(line: 94, column: 26, scope: !392)
!397 = !DILocation(line: 94, column: 37, scope: !398)
!398 = !DILexicalBlockFile(scope: !392, file: !1, discriminator: 1)
!399 = !DILocation(line: 94, column: 40, scope: !398)
!400 = !DILocation(line: 94, column: 48, scope: !398)
!401 = !DILocation(line: 94, column: 54, scope: !398)
!402 = !DILocation(line: 94, column: 30, scope: !398)
!403 = !DILocation(line: 94, column: 9, scope: !398)
!404 = !DILocation(line: 95, column: 7, scope: !392)
!405 = !DILocation(line: 96, column: 3, scope: !393)
!406 = !DILocation(line: 93, column: 27, scope: !407)
!407 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 2)
!408 = !DILocation(line: 93, column: 31, scope: !407)
!409 = !DILocation(line: 93, column: 34, scope: !407)
!410 = !DILocation(line: 93, column: 40, scope: !407)
!411 = !DILocation(line: 93, column: 3, scope: !407)
!412 = !DILocation(line: 97, column: 8, scope: !413)
!413 = distinct !DILexicalBlock(scope: !292, file: !1, line: 97, column: 7)
!414 = !DILocation(line: 97, column: 11, scope: !413)
!415 = !DILocation(line: 97, column: 19, scope: !413)
!416 = !DILocation(line: 97, column: 24, scope: !413)
!417 = !DILocation(line: 97, column: 34, scope: !418)
!418 = !DILexicalBlockFile(scope: !413, file: !1, discriminator: 1)
!419 = !DILocation(line: 97, column: 37, scope: !418)
!420 = !DILocation(line: 97, column: 45, scope: !418)
!421 = !DILocation(line: 97, column: 51, scope: !418)
!422 = !DILocation(line: 97, column: 27, scope: !418)
!423 = !DILocation(line: 97, column: 7, scope: !418)
!424 = !DILocation(line: 99, column: 24, scope: !425)
!425 = distinct !DILexicalBlock(scope: !413, file: !1, line: 98, column: 3)
!426 = !DILocation(line: 99, column: 27, scope: !425)
!427 = !DILocation(line: 99, column: 5, scope: !425)
!428 = !DILocation(line: 101, column: 8, scope: !425)
!429 = !DILocation(line: 102, column: 3, scope: !425)
!430 = !DILocation(line: 104, column: 11, scope: !292)
!431 = !DILocation(line: 104, column: 16, scope: !292)
!432 = !DILocation(line: 104, column: 14, scope: !292)
!433 = !DILocation(line: 104, column: 10, scope: !292)
!434 = !DILocation(line: 104, column: 22, scope: !435)
!435 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 1)
!436 = !DILocation(line: 104, column: 10, scope: !435)
!437 = !DILocation(line: 104, column: 27, scope: !438)
!438 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 2)
!439 = !DILocation(line: 104, column: 10, scope: !438)
!440 = !DILocation(line: 104, column: 10, scope: !441)
!441 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 3)
!442 = !DILocation(line: 104, column: 3, scope: !441)
!443 = !DILocation(line: 105, column: 1, scope: !292)
