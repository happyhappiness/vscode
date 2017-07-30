; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_options.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }

@.str = private unnamed_addr constant [32 x i8] c"archive_write_set_format_option\00", align 1
@.str.1 = private unnamed_addr constant [32 x i8] c"archive_write_set_filter_option\00", align 1
@.str.2 = private unnamed_addr constant [25 x i8] c"archive_write_set_option\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"archive_write_set_options\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !192 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !206, metadata !207), !dbg !208
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !209, metadata !207), !dbg !210
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !211, metadata !207), !dbg !212
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !213, metadata !207), !dbg !214
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !215
  %1 = load i8*, i8** %m.addr, align 8, !dbg !216
  %2 = load i8*, i8** %o.addr, align 8, !dbg !217
  %3 = load i8*, i8** %v.addr, align 8, !dbg !218
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 -1329217314, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_format_option), !dbg !219
  ret i32 %call, !dbg !220
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @_archive_set_option(%struct.archive*, i8*, i8*, i8*, i32, i8*, i32 (%struct.archive*, i8*, i8*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_format_option(%struct.archive* %_a, i8* %m, i8* %o, i8* %v) #0 !dbg !200 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  %a = alloca %struct.archive_write*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !221, metadata !207), !dbg !222
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !223, metadata !207), !dbg !224
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !225, metadata !207), !dbg !226
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !227, metadata !207), !dbg !228
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !229, metadata !207), !dbg !230
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !231
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !232
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !230
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !233
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 15, !dbg !235
  %3 = load i8*, i8** %format_name, align 8, !dbg !235
  %cmp = icmp eq i8* %3, null, !dbg !236
  br i1 %cmp, label %if.then, label %if.end, !dbg !237

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %m.addr, align 8, !dbg !238
  %cmp1 = icmp eq i8* %4, null, !dbg !239
  %cond = select i1 %cmp1, i32 -25, i32 -21, !dbg !240
  store i32 %cond, i32* %retval, align 4, !dbg !241
  br label %return, !dbg !241

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %m.addr, align 8, !dbg !242
  %cmp2 = icmp ne i8* %5, null, !dbg !244
  br i1 %cmp2, label %land.lhs.true, label %if.end6, !dbg !245

land.lhs.true:                                    ; preds = %if.end
  %6 = load i8*, i8** %m.addr, align 8, !dbg !246
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !248
  %format_name3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 15, !dbg !249
  %8 = load i8*, i8** %format_name3, align 8, !dbg !249
  %call = call i32 @strcmp(i8* %6, i8* %8) #4, !dbg !250
  %cmp4 = icmp ne i32 %call, 0, !dbg !251
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !252

if.then5:                                         ; preds = %land.lhs.true
  store i32 -21, i32* %retval, align 4, !dbg !253
  br label %return, !dbg !253

if.end6:                                          ; preds = %land.lhs.true, %if.end
  %9 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !254
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 17, !dbg !256
  %10 = load i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !256
  %cmp7 = icmp eq i32 (%struct.archive_write*, i8*, i8*)* %10, null, !dbg !257
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !258

if.then8:                                         ; preds = %if.end6
  store i32 -20, i32* %retval, align 4, !dbg !259
  br label %return, !dbg !259

if.end9:                                          ; preds = %if.end6
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !260
  %format_options10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 17, !dbg !261
  %12 = load i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*, i8*, i8*)** %format_options10, align 8, !dbg !261
  %13 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !262
  %14 = load i8*, i8** %o.addr, align 8, !dbg !263
  %15 = load i8*, i8** %v.addr, align 8, !dbg !264
  %call11 = call i32 %12(%struct.archive_write* %13, i8* %14, i8* %15), !dbg !260
  store i32 %call11, i32* %retval, align 4, !dbg !265
  br label %return, !dbg !265

return:                                           ; preds = %if.end9, %if.then8, %if.then5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !266
  ret i32 %16, !dbg !266
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_filter_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !195 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !267, metadata !207), !dbg !268
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !269, metadata !207), !dbg !270
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !271, metadata !207), !dbg !272
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !273, metadata !207), !dbg !274
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !275
  %1 = load i8*, i8** %m.addr, align 8, !dbg !276
  %2 = load i8*, i8** %o.addr, align 8, !dbg !277
  %3 = load i8*, i8** %v.addr, align 8, !dbg !278
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 -1329217314, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.1, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_filter_option), !dbg !279
  ret i32 %call, !dbg !280
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_filter_option(%struct.archive* %_a, i8* %m, i8* %o, i8* %v) #0 !dbg !201 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  %a = alloca %struct.archive_write*, align 8
  %filter = alloca %struct.archive_write_filter*, align 8
  %r = alloca i32, align 4
  %rv = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !281, metadata !207), !dbg !282
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !283, metadata !207), !dbg !284
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !285, metadata !207), !dbg !286
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !287, metadata !207), !dbg !288
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !289, metadata !207), !dbg !290
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !291
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !292
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !290
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %filter, metadata !293, metadata !207), !dbg !294
  call void @llvm.dbg.declare(metadata i32* %r, metadata !295, metadata !207), !dbg !296
  call void @llvm.dbg.declare(metadata i32* %rv, metadata !297, metadata !207), !dbg !298
  store i32 -20, i32* %rv, align 4, !dbg !298
  %2 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !299
  %filter_first = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 12, !dbg !301
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter_first, align 8, !dbg !301
  store %struct.archive_write_filter* %3, %struct.archive_write_filter** %filter, align 8, !dbg !302
  br label %for.cond, !dbg !303

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !304
  %cmp = icmp ne %struct.archive_write_filter* %4, null, !dbg !307
  br i1 %cmp, label %for.body, label %for.end, !dbg !308

for.body:                                         ; preds = %for.cond
  %5 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !309
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %5, i32 0, i32 3, !dbg !312
  %6 = load i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !312
  %cmp1 = icmp eq i32 (%struct.archive_write_filter*, i8*, i8*)* %6, null, !dbg !313
  br i1 %cmp1, label %if.then, label %if.end, !dbg !314

if.then:                                          ; preds = %for.body
  br label %for.inc, !dbg !315

if.end:                                           ; preds = %for.body
  %7 = load i8*, i8** %m.addr, align 8, !dbg !316
  %cmp2 = icmp ne i8* %7, null, !dbg !318
  br i1 %cmp2, label %land.lhs.true, label %if.end5, !dbg !319

land.lhs.true:                                    ; preds = %if.end
  %8 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !320
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %8, i32 0, i32 9, !dbg !322
  %9 = load i8*, i8** %name, align 8, !dbg !322
  %10 = load i8*, i8** %m.addr, align 8, !dbg !323
  %call = call i32 @strcmp(i8* %9, i8* %10) #4, !dbg !324
  %cmp3 = icmp ne i32 %call, 0, !dbg !325
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !326

if.then4:                                         ; preds = %land.lhs.true
  br label %for.inc, !dbg !327

if.end5:                                          ; preds = %land.lhs.true, %if.end
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !328
  %options6 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 3, !dbg !329
  %12 = load i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*, i8*, i8*)** %options6, align 8, !dbg !329
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !330
  %14 = load i8*, i8** %o.addr, align 8, !dbg !331
  %15 = load i8*, i8** %v.addr, align 8, !dbg !332
  %call7 = call i32 %12(%struct.archive_write_filter* %13, i8* %14, i8* %15), !dbg !328
  store i32 %call7, i32* %r, align 4, !dbg !333
  %16 = load i32, i32* %r, align 4, !dbg !334
  %cmp8 = icmp eq i32 %16, -30, !dbg !336
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !337

if.then9:                                         ; preds = %if.end5
  store i32 -30, i32* %retval, align 4, !dbg !338
  br label %return, !dbg !338

if.end10:                                         ; preds = %if.end5
  %17 = load i8*, i8** %m.addr, align 8, !dbg !339
  %cmp11 = icmp ne i8* %17, null, !dbg !341
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !342

if.then12:                                        ; preds = %if.end10
  %18 = load i32, i32* %r, align 4, !dbg !343
  store i32 %18, i32* %retval, align 4, !dbg !344
  br label %return, !dbg !344

if.end13:                                         ; preds = %if.end10
  %19 = load i32, i32* %r, align 4, !dbg !345
  %cmp14 = icmp eq i32 %19, 0, !dbg !347
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !348

if.then15:                                        ; preds = %if.end13
  store i32 0, i32* %rv, align 4, !dbg !349
  br label %if.end16, !dbg !350

if.end16:                                         ; preds = %if.then15, %if.end13
  br label %for.inc, !dbg !351

for.inc:                                          ; preds = %if.end16, %if.then4, %if.then
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %filter, align 8, !dbg !352
  %next_filter = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 2, !dbg !354
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %next_filter, align 8, !dbg !354
  store %struct.archive_write_filter* %21, %struct.archive_write_filter** %filter, align 8, !dbg !355
  br label %for.cond, !dbg !356

for.end:                                          ; preds = %for.cond
  %22 = load i32, i32* %rv, align 4, !dbg !357
  %cmp17 = icmp eq i32 %22, -20, !dbg !359
  br i1 %cmp17, label %land.lhs.true18, label %if.end21, !dbg !360

land.lhs.true18:                                  ; preds = %for.end
  %23 = load i8*, i8** %m.addr, align 8, !dbg !361
  %cmp19 = icmp ne i8* %23, null, !dbg !363
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !364

if.then20:                                        ; preds = %land.lhs.true18
  store i32 -21, i32* %rv, align 4, !dbg !365
  br label %if.end21, !dbg !366

if.end21:                                         ; preds = %if.then20, %land.lhs.true18, %for.end
  %24 = load i32, i32* %rv, align 4, !dbg !367
  store i32 %24, i32* %retval, align 4, !dbg !368
  br label %return, !dbg !368

return:                                           ; preds = %if.end21, %if.then12, %if.then9
  %25 = load i32, i32* %retval, align 4, !dbg !369
  ret i32 %25, !dbg !369
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !196 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !370, metadata !207), !dbg !371
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !372, metadata !207), !dbg !373
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !374, metadata !207), !dbg !375
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !376, metadata !207), !dbg !377
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !378
  %1 = load i8*, i8** %m.addr, align 8, !dbg !379
  %2 = load i8*, i8** %o.addr, align 8, !dbg !380
  %3 = load i8*, i8** %v.addr, align 8, !dbg !381
  %call = call i32 @_archive_set_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 -1329217314, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_option), !dbg !382
  ret i32 %call, !dbg !383
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_set_option(%struct.archive* %a, i8* %m, i8* %o, i8* %v) #0 !dbg !202 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %m.addr = alloca i8*, align 8
  %o.addr = alloca i8*, align 8
  %v.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !384, metadata !207), !dbg !385
  store i8* %m, i8** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %m.addr, metadata !386, metadata !207), !dbg !387
  store i8* %o, i8** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %o.addr, metadata !388, metadata !207), !dbg !389
  store i8* %v, i8** %v.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %v.addr, metadata !390, metadata !207), !dbg !391
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !392
  %1 = load i8*, i8** %m.addr, align 8, !dbg !393
  %2 = load i8*, i8** %o.addr, align 8, !dbg !394
  %3 = load i8*, i8** %v.addr, align 8, !dbg !395
  %call = call i32 @_archive_set_either_option(%struct.archive* %0, i8* %1, i8* %2, i8* %3, i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_format_option, i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_filter_option), !dbg !396
  ret i32 %call, !dbg !397
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_options(%struct.archive* %a, i8* %options) #0 !dbg !197 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %options.addr = alloca i8*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !398, metadata !207), !dbg !399
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !400, metadata !207), !dbg !401
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !402
  %1 = load i8*, i8** %options.addr, align 8, !dbg !403
  %call = call i32 @_archive_set_options(%struct.archive* %0, i8* %1, i32 -1329217314, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i32 0, i32 0), i32 (%struct.archive*, i8*, i8*, i8*)* @archive_set_option), !dbg !404
  ret i32 %call, !dbg !405
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
!llvm.module.flags = !{!203, !204}
!llvm.ident = !{!205}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !191)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_options.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123}
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
!191 = !{!192, !195, !196, !197, !200, !201, !202}
!192 = distinct !DISubprogram(name: "archive_write_set_format_option", scope: !1, file: !1, line: 40, type: !193, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!193 = !DISubroutineType(types: !194)
!194 = !{!23, !24, !80, !80, !80}
!195 = distinct !DISubprogram(name: "archive_write_set_filter_option", scope: !1, file: !1, line: 49, type: !193, isLocal: false, isDefinition: true, scopeLine: 51, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!196 = distinct !DISubprogram(name: "archive_write_set_option", scope: !1, file: !1, line: 58, type: !193, isLocal: false, isDefinition: true, scopeLine: 60, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!197 = distinct !DISubprogram(name: "archive_write_set_options", scope: !1, file: !1, line: 67, type: !198, isLocal: false, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!198 = !DISubroutineType(types: !199)
!199 = !{!23, !24, !80}
!200 = distinct !DISubprogram(name: "archive_set_format_option", scope: !1, file: !1, line: 75, type: !193, isLocal: true, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!201 = distinct !DISubprogram(name: "archive_set_filter_option", scope: !1, file: !1, line: 92, type: !193, isLocal: true, isDefinition: true, scopeLine: 94, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!202 = distinct !DISubprogram(name: "archive_set_option", scope: !1, file: !1, line: 124, type: !193, isLocal: true, isDefinition: true, scopeLine: 126, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!203 = !{i32 2, !"Dwarf Version", i32 4}
!204 = !{i32 2, !"Debug Info Version", i32 3}
!205 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!206 = !DILocalVariable(name: "a", arg: 1, scope: !192, file: !1, line: 40, type: !24)
!207 = !DIExpression()
!208 = !DILocation(line: 40, column: 49, scope: !192)
!209 = !DILocalVariable(name: "m", arg: 2, scope: !192, file: !1, line: 40, type: !80)
!210 = !DILocation(line: 40, column: 64, scope: !192)
!211 = !DILocalVariable(name: "o", arg: 3, scope: !192, file: !1, line: 40, type: !80)
!212 = !DILocation(line: 40, column: 79, scope: !192)
!213 = !DILocalVariable(name: "v", arg: 4, scope: !192, file: !1, line: 41, type: !80)
!214 = !DILocation(line: 41, column: 17, scope: !192)
!215 = !DILocation(line: 43, column: 29, scope: !192)
!216 = !DILocation(line: 43, column: 32, scope: !192)
!217 = !DILocation(line: 43, column: 35, scope: !192)
!218 = !DILocation(line: 43, column: 38, scope: !192)
!219 = !DILocation(line: 43, column: 9, scope: !192)
!220 = !DILocation(line: 43, column: 2, scope: !192)
!221 = !DILocalVariable(name: "_a", arg: 1, scope: !200, file: !1, line: 75, type: !24)
!222 = !DILocation(line: 75, column: 43, scope: !200)
!223 = !DILocalVariable(name: "m", arg: 2, scope: !200, file: !1, line: 75, type: !80)
!224 = !DILocation(line: 75, column: 59, scope: !200)
!225 = !DILocalVariable(name: "o", arg: 3, scope: !200, file: !1, line: 75, type: !80)
!226 = !DILocation(line: 75, column: 74, scope: !200)
!227 = !DILocalVariable(name: "v", arg: 4, scope: !200, file: !1, line: 76, type: !80)
!228 = !DILocation(line: 76, column: 17, scope: !200)
!229 = !DILocalVariable(name: "a", scope: !200, file: !1, line: 78, type: !4)
!230 = !DILocation(line: 78, column: 24, scope: !200)
!231 = !DILocation(line: 78, column: 52, scope: !200)
!232 = !DILocation(line: 78, column: 28, scope: !200)
!233 = !DILocation(line: 80, column: 6, scope: !234)
!234 = distinct !DILexicalBlock(scope: !200, file: !1, line: 80, column: 6)
!235 = !DILocation(line: 80, column: 9, scope: !234)
!236 = !DILocation(line: 80, column: 21, scope: !234)
!237 = !DILocation(line: 80, column: 6, scope: !200)
!238 = !DILocation(line: 81, column: 11, scope: !234)
!239 = !DILocation(line: 81, column: 13, scope: !234)
!240 = !DILocation(line: 81, column: 10, scope: !234)
!241 = !DILocation(line: 81, column: 3, scope: !234)
!242 = !DILocation(line: 84, column: 6, scope: !243)
!243 = distinct !DILexicalBlock(scope: !200, file: !1, line: 84, column: 6)
!244 = !DILocation(line: 84, column: 8, scope: !243)
!245 = !DILocation(line: 84, column: 16, scope: !243)
!246 = !DILocation(line: 84, column: 26, scope: !247)
!247 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 1)
!248 = !DILocation(line: 84, column: 29, scope: !247)
!249 = !DILocation(line: 84, column: 32, scope: !247)
!250 = !DILocation(line: 84, column: 19, scope: !247)
!251 = !DILocation(line: 84, column: 45, scope: !247)
!252 = !DILocation(line: 84, column: 6, scope: !247)
!253 = !DILocation(line: 85, column: 3, scope: !243)
!254 = !DILocation(line: 86, column: 6, scope: !255)
!255 = distinct !DILexicalBlock(scope: !200, file: !1, line: 86, column: 6)
!256 = !DILocation(line: 86, column: 9, scope: !255)
!257 = !DILocation(line: 86, column: 24, scope: !255)
!258 = !DILocation(line: 86, column: 6, scope: !200)
!259 = !DILocation(line: 87, column: 3, scope: !255)
!260 = !DILocation(line: 88, column: 9, scope: !200)
!261 = !DILocation(line: 88, column: 12, scope: !200)
!262 = !DILocation(line: 88, column: 27, scope: !200)
!263 = !DILocation(line: 88, column: 30, scope: !200)
!264 = !DILocation(line: 88, column: 33, scope: !200)
!265 = !DILocation(line: 88, column: 2, scope: !200)
!266 = !DILocation(line: 89, column: 1, scope: !200)
!267 = !DILocalVariable(name: "a", arg: 1, scope: !195, file: !1, line: 49, type: !24)
!268 = !DILocation(line: 49, column: 49, scope: !195)
!269 = !DILocalVariable(name: "m", arg: 2, scope: !195, file: !1, line: 49, type: !80)
!270 = !DILocation(line: 49, column: 64, scope: !195)
!271 = !DILocalVariable(name: "o", arg: 3, scope: !195, file: !1, line: 49, type: !80)
!272 = !DILocation(line: 49, column: 79, scope: !195)
!273 = !DILocalVariable(name: "v", arg: 4, scope: !195, file: !1, line: 50, type: !80)
!274 = !DILocation(line: 50, column: 17, scope: !195)
!275 = !DILocation(line: 52, column: 29, scope: !195)
!276 = !DILocation(line: 52, column: 32, scope: !195)
!277 = !DILocation(line: 52, column: 35, scope: !195)
!278 = !DILocation(line: 52, column: 38, scope: !195)
!279 = !DILocation(line: 52, column: 9, scope: !195)
!280 = !DILocation(line: 52, column: 2, scope: !195)
!281 = !DILocalVariable(name: "_a", arg: 1, scope: !201, file: !1, line: 92, type: !24)
!282 = !DILocation(line: 92, column: 43, scope: !201)
!283 = !DILocalVariable(name: "m", arg: 2, scope: !201, file: !1, line: 92, type: !80)
!284 = !DILocation(line: 92, column: 59, scope: !201)
!285 = !DILocalVariable(name: "o", arg: 3, scope: !201, file: !1, line: 92, type: !80)
!286 = !DILocation(line: 92, column: 74, scope: !201)
!287 = !DILocalVariable(name: "v", arg: 4, scope: !201, file: !1, line: 93, type: !80)
!288 = !DILocation(line: 93, column: 17, scope: !201)
!289 = !DILocalVariable(name: "a", scope: !201, file: !1, line: 95, type: !4)
!290 = !DILocation(line: 95, column: 24, scope: !201)
!291 = !DILocation(line: 95, column: 52, scope: !201)
!292 = !DILocation(line: 95, column: 28, scope: !201)
!293 = !DILocalVariable(name: "filter", scope: !201, file: !1, line: 96, type: !137)
!294 = !DILocation(line: 96, column: 31, scope: !201)
!295 = !DILocalVariable(name: "r", scope: !201, file: !1, line: 97, type: !23)
!296 = !DILocation(line: 97, column: 6, scope: !201)
!297 = !DILocalVariable(name: "rv", scope: !201, file: !1, line: 97, type: !23)
!298 = !DILocation(line: 97, column: 9, scope: !201)
!299 = !DILocation(line: 99, column: 16, scope: !300)
!300 = distinct !DILexicalBlock(scope: !201, file: !1, line: 99, column: 2)
!301 = !DILocation(line: 99, column: 19, scope: !300)
!302 = !DILocation(line: 99, column: 14, scope: !300)
!303 = !DILocation(line: 99, column: 7, scope: !300)
!304 = !DILocation(line: 99, column: 33, scope: !305)
!305 = !DILexicalBlockFile(scope: !306, file: !1, discriminator: 1)
!306 = distinct !DILexicalBlock(scope: !300, file: !1, line: 99, column: 2)
!307 = !DILocation(line: 99, column: 40, scope: !305)
!308 = !DILocation(line: 99, column: 2, scope: !305)
!309 = !DILocation(line: 100, column: 7, scope: !310)
!310 = distinct !DILexicalBlock(scope: !311, file: !1, line: 100, column: 7)
!311 = distinct !DILexicalBlock(scope: !306, file: !1, line: 99, column: 79)
!312 = !DILocation(line: 100, column: 15, scope: !310)
!313 = !DILocation(line: 100, column: 23, scope: !310)
!314 = !DILocation(line: 100, column: 7, scope: !311)
!315 = !DILocation(line: 101, column: 4, scope: !310)
!316 = !DILocation(line: 102, column: 7, scope: !317)
!317 = distinct !DILexicalBlock(scope: !311, file: !1, line: 102, column: 7)
!318 = !DILocation(line: 102, column: 9, scope: !317)
!319 = !DILocation(line: 102, column: 17, scope: !317)
!320 = !DILocation(line: 102, column: 27, scope: !321)
!321 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 1)
!322 = !DILocation(line: 102, column: 35, scope: !321)
!323 = !DILocation(line: 102, column: 41, scope: !321)
!324 = !DILocation(line: 102, column: 20, scope: !321)
!325 = !DILocation(line: 102, column: 44, scope: !321)
!326 = !DILocation(line: 102, column: 7, scope: !321)
!327 = !DILocation(line: 103, column: 4, scope: !317)
!328 = !DILocation(line: 105, column: 7, scope: !311)
!329 = !DILocation(line: 105, column: 15, scope: !311)
!330 = !DILocation(line: 105, column: 23, scope: !311)
!331 = !DILocation(line: 105, column: 31, scope: !311)
!332 = !DILocation(line: 105, column: 34, scope: !311)
!333 = !DILocation(line: 105, column: 5, scope: !311)
!334 = !DILocation(line: 107, column: 7, scope: !335)
!335 = distinct !DILexicalBlock(scope: !311, file: !1, line: 107, column: 7)
!336 = !DILocation(line: 107, column: 9, scope: !335)
!337 = !DILocation(line: 107, column: 7, scope: !311)
!338 = !DILocation(line: 108, column: 4, scope: !335)
!339 = !DILocation(line: 110, column: 7, scope: !340)
!340 = distinct !DILexicalBlock(scope: !311, file: !1, line: 110, column: 7)
!341 = !DILocation(line: 110, column: 9, scope: !340)
!342 = !DILocation(line: 110, column: 7, scope: !311)
!343 = !DILocation(line: 111, column: 12, scope: !340)
!344 = !DILocation(line: 111, column: 4, scope: !340)
!345 = !DILocation(line: 113, column: 7, scope: !346)
!346 = distinct !DILexicalBlock(scope: !311, file: !1, line: 113, column: 7)
!347 = !DILocation(line: 113, column: 9, scope: !346)
!348 = !DILocation(line: 113, column: 7, scope: !311)
!349 = !DILocation(line: 114, column: 7, scope: !346)
!350 = !DILocation(line: 114, column: 4, scope: !346)
!351 = !DILocation(line: 115, column: 2, scope: !311)
!352 = !DILocation(line: 99, column: 58, scope: !353)
!353 = !DILexicalBlockFile(scope: !306, file: !1, discriminator: 2)
!354 = !DILocation(line: 99, column: 66, scope: !353)
!355 = !DILocation(line: 99, column: 56, scope: !353)
!356 = !DILocation(line: 99, column: 2, scope: !353)
!357 = !DILocation(line: 118, column: 6, scope: !358)
!358 = distinct !DILexicalBlock(scope: !201, file: !1, line: 118, column: 6)
!359 = !DILocation(line: 118, column: 9, scope: !358)
!360 = !DILocation(line: 118, column: 25, scope: !358)
!361 = !DILocation(line: 118, column: 28, scope: !362)
!362 = !DILexicalBlockFile(scope: !358, file: !1, discriminator: 1)
!363 = !DILocation(line: 118, column: 30, scope: !362)
!364 = !DILocation(line: 118, column: 6, scope: !362)
!365 = !DILocation(line: 119, column: 6, scope: !358)
!366 = !DILocation(line: 119, column: 3, scope: !358)
!367 = !DILocation(line: 120, column: 10, scope: !201)
!368 = !DILocation(line: 120, column: 2, scope: !201)
!369 = !DILocation(line: 121, column: 1, scope: !201)
!370 = !DILocalVariable(name: "a", arg: 1, scope: !196, file: !1, line: 58, type: !24)
!371 = !DILocation(line: 58, column: 42, scope: !196)
!372 = !DILocalVariable(name: "m", arg: 2, scope: !196, file: !1, line: 58, type: !80)
!373 = !DILocation(line: 58, column: 57, scope: !196)
!374 = !DILocalVariable(name: "o", arg: 3, scope: !196, file: !1, line: 58, type: !80)
!375 = !DILocation(line: 58, column: 72, scope: !196)
!376 = !DILocalVariable(name: "v", arg: 4, scope: !196, file: !1, line: 59, type: !80)
!377 = !DILocation(line: 59, column: 17, scope: !196)
!378 = !DILocation(line: 61, column: 29, scope: !196)
!379 = !DILocation(line: 61, column: 32, scope: !196)
!380 = !DILocation(line: 61, column: 35, scope: !196)
!381 = !DILocation(line: 61, column: 38, scope: !196)
!382 = !DILocation(line: 61, column: 9, scope: !196)
!383 = !DILocation(line: 61, column: 2, scope: !196)
!384 = !DILocalVariable(name: "a", arg: 1, scope: !202, file: !1, line: 124, type: !24)
!385 = !DILocation(line: 124, column: 36, scope: !202)
!386 = !DILocalVariable(name: "m", arg: 2, scope: !202, file: !1, line: 124, type: !80)
!387 = !DILocation(line: 124, column: 51, scope: !202)
!388 = !DILocalVariable(name: "o", arg: 3, scope: !202, file: !1, line: 124, type: !80)
!389 = !DILocation(line: 124, column: 66, scope: !202)
!390 = !DILocalVariable(name: "v", arg: 4, scope: !202, file: !1, line: 125, type: !80)
!391 = !DILocation(line: 125, column: 17, scope: !202)
!392 = !DILocation(line: 127, column: 36, scope: !202)
!393 = !DILocation(line: 127, column: 39, scope: !202)
!394 = !DILocation(line: 127, column: 42, scope: !202)
!395 = !DILocation(line: 127, column: 45, scope: !202)
!396 = !DILocation(line: 127, column: 9, scope: !202)
!397 = !DILocation(line: 127, column: 2, scope: !202)
!398 = !DILocalVariable(name: "a", arg: 1, scope: !197, file: !1, line: 67, type: !24)
!399 = !DILocation(line: 67, column: 43, scope: !197)
!400 = !DILocalVariable(name: "options", arg: 2, scope: !197, file: !1, line: 67, type: !80)
!401 = !DILocation(line: 67, column: 58, scope: !197)
!402 = !DILocation(line: 69, column: 30, scope: !197)
!403 = !DILocation(line: 69, column: 33, scope: !197)
!404 = !DILocation(line: 69, column: 9, scope: !197)
!405 = !DILocation(line: 69, column: 2, scope: !197)
