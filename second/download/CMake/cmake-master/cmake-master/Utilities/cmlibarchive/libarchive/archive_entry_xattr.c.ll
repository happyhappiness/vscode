; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_xattr.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_entry = type { %struct.archive*, i8*, i32, %struct.aest, i32, %struct.archive_mstring, i64, i64, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, i8, i8*, i64, %struct.archive_acl, %struct.ae_xattr*, %struct.ae_xattr*, %struct.ae_sparse*, %struct.ae_sparse*, %struct.ae_sparse*, [12 x i8] }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.aest = type { i64, i32, i64, i32, i64, i32, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, i64, i32, i64, i64, i64 }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.ae_xattr = type { %struct.ae_xattr*, i8*, i8*, i64 }
%struct.ae_sparse = type { %struct.ae_sparse*, i64, i64 }

@.str = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1

; Function Attrs: nounwind uwtable
define void @archive_entry_xattr_clear(%struct.archive_entry* %entry1) #0 !dbg !19 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %xp = alloca %struct.ae_xattr*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !228, metadata !229), !dbg !230
  call void @llvm.dbg.declare(metadata %struct.ae_xattr** %xp, metadata !231, metadata !229), !dbg !232
  br label %while.cond, !dbg !233

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !234
  %xattr_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 18, !dbg !236
  %1 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head, align 8, !dbg !236
  %cmp = icmp ne %struct.ae_xattr* %1, null, !dbg !237
  br i1 %cmp, label %while.body, label %while.end, !dbg !238

while.body:                                       ; preds = %while.cond
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !239
  %xattr_head2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 18, !dbg !241
  %3 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head2, align 8, !dbg !241
  %next = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %3, i32 0, i32 0, !dbg !242
  %4 = load %struct.ae_xattr*, %struct.ae_xattr** %next, align 8, !dbg !242
  store %struct.ae_xattr* %4, %struct.ae_xattr** %xp, align 8, !dbg !243
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !244
  %xattr_head3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 18, !dbg !245
  %6 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head3, align 8, !dbg !245
  %name = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %6, i32 0, i32 1, !dbg !246
  %7 = load i8*, i8** %name, align 8, !dbg !246
  call void @free(i8* %7) #5, !dbg !247
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !248
  %xattr_head4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 18, !dbg !249
  %9 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head4, align 8, !dbg !249
  %value = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %9, i32 0, i32 2, !dbg !250
  %10 = load i8*, i8** %value, align 8, !dbg !250
  call void @free(i8* %10) #5, !dbg !251
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !252
  %xattr_head5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %11, i32 0, i32 18, !dbg !253
  %12 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head5, align 8, !dbg !253
  %13 = bitcast %struct.ae_xattr* %12 to i8*, !dbg !252
  call void @free(i8* %13) #5, !dbg !254
  %14 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !255
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !256
  %xattr_head6 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %15, i32 0, i32 18, !dbg !257
  store %struct.ae_xattr* %14, %struct.ae_xattr** %xattr_head6, align 8, !dbg !258
  br label %while.cond, !dbg !259

while.end:                                        ; preds = %while.cond
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !261
  %xattr_head7 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %16, i32 0, i32 18, !dbg !262
  store %struct.ae_xattr* null, %struct.ae_xattr** %xattr_head7, align 8, !dbg !263
  ret void, !dbg !264
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_xattr_add_entry(%struct.archive_entry* %entry1, i8* %name, i8* %value, i64 %size) #0 !dbg !214 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %xp = alloca %struct.ae_xattr*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !265, metadata !229), !dbg !266
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !267, metadata !229), !dbg !268
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !269, metadata !229), !dbg !270
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !271, metadata !229), !dbg !272
  call void @llvm.dbg.declare(metadata %struct.ae_xattr** %xp, metadata !273, metadata !229), !dbg !274
  %call = call noalias i8* @malloc(i64 32) #5, !dbg !275
  %0 = bitcast i8* %call to %struct.ae_xattr*, !dbg !277
  store %struct.ae_xattr* %0, %struct.ae_xattr** %xp, align 8, !dbg !278
  %cmp = icmp eq %struct.ae_xattr* %0, null, !dbg !279
  br i1 %cmp, label %if.then, label %if.end, !dbg !280

if.then:                                          ; preds = %entry
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)) #6, !dbg !281
  unreachable, !dbg !281

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %name.addr, align 8, !dbg !282
  %call2 = call noalias i8* @strdup(i8* %1) #5, !dbg !284
  %2 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !285
  %name3 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %2, i32 0, i32 1, !dbg !286
  store i8* %call2, i8** %name3, align 8, !dbg !287
  %cmp4 = icmp eq i8* %call2, null, !dbg !288
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !289

if.then5:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)) #6, !dbg !290
  unreachable, !dbg !290

if.end6:                                          ; preds = %if.end
  %3 = load i64, i64* %size.addr, align 8, !dbg !291
  %call7 = call noalias i8* @malloc(i64 %3) #5, !dbg !293
  %4 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !294
  %value8 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %4, i32 0, i32 2, !dbg !295
  store i8* %call7, i8** %value8, align 8, !dbg !296
  %cmp9 = icmp ne i8* %call7, null, !dbg !297
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !298

if.then10:                                        ; preds = %if.end6
  %5 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !299
  %value11 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %5, i32 0, i32 2, !dbg !301
  %6 = load i8*, i8** %value11, align 8, !dbg !301
  %7 = load i8*, i8** %value.addr, align 8, !dbg !302
  %8 = load i64, i64* %size.addr, align 8, !dbg !303
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %6, i8* %7, i64 %8, i32 1, i1 false), !dbg !304
  %9 = load i64, i64* %size.addr, align 8, !dbg !305
  %10 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !306
  %size12 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %10, i32 0, i32 3, !dbg !307
  store i64 %9, i64* %size12, align 8, !dbg !308
  br label %if.end14, !dbg !309

if.else:                                          ; preds = %if.end6
  %11 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !310
  %size13 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %11, i32 0, i32 3, !dbg !311
  store i64 0, i64* %size13, align 8, !dbg !312
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then10
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !313
  %xattr_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 18, !dbg !314
  %13 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head, align 8, !dbg !314
  %14 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !315
  %next = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %14, i32 0, i32 0, !dbg !316
  store %struct.ae_xattr* %13, %struct.ae_xattr** %next, align 8, !dbg !317
  %15 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !318
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !319
  %xattr_head15 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %16, i32 0, i32 18, !dbg !320
  store %struct.ae_xattr* %15, %struct.ae_xattr** %xattr_head15, align 8, !dbg !321
  ret void, !dbg !322
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: noreturn
declare void @__archive_errx(i32, i8*) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define i32 @archive_entry_xattr_count(%struct.archive_entry* %entry1) #0 !dbg !217 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %xp = alloca %struct.ae_xattr*, align 8
  %count = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !323, metadata !229), !dbg !324
  call void @llvm.dbg.declare(metadata %struct.ae_xattr** %xp, metadata !325, metadata !229), !dbg !326
  call void @llvm.dbg.declare(metadata i32* %count, metadata !327, metadata !229), !dbg !328
  store i32 0, i32* %count, align 4, !dbg !328
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !329
  %xattr_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 18, !dbg !331
  %1 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head, align 8, !dbg !331
  store %struct.ae_xattr* %1, %struct.ae_xattr** %xp, align 8, !dbg !332
  br label %for.cond, !dbg !333

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !334
  %cmp = icmp ne %struct.ae_xattr* %2, null, !dbg !337
  br i1 %cmp, label %for.body, label %for.end, !dbg !338

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %count, align 4, !dbg !339
  %inc = add nsw i32 %3, 1, !dbg !339
  store i32 %inc, i32* %count, align 4, !dbg !339
  br label %for.inc, !dbg !340

for.inc:                                          ; preds = %for.body
  %4 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !341
  %next = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %4, i32 0, i32 0, !dbg !343
  %5 = load %struct.ae_xattr*, %struct.ae_xattr** %next, align 8, !dbg !343
  store %struct.ae_xattr* %5, %struct.ae_xattr** %xp, align 8, !dbg !344
  br label %for.cond, !dbg !345

for.end:                                          ; preds = %for.cond
  %6 = load i32, i32* %count, align 4, !dbg !346
  ret i32 %6, !dbg !347
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_xattr_reset(%struct.archive_entry* %entry1) #0 !dbg !220 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !348, metadata !229), !dbg !349
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !350
  %xattr_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 18, !dbg !351
  %1 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head, align 8, !dbg !351
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !352
  %xattr_p = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 19, !dbg !353
  store %struct.ae_xattr* %1, %struct.ae_xattr** %xattr_p, align 8, !dbg !354
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !355
  %call = call i32 @archive_entry_xattr_count(%struct.archive_entry* %3), !dbg !356
  ret i32 %call, !dbg !357
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_xattr_next(%struct.archive_entry* %entry1, i8** %name, i8** %value, i64* %size) #0 !dbg !221 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %value.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !358, metadata !229), !dbg !359
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !360, metadata !229), !dbg !361
  store i8** %value, i8*** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %value.addr, metadata !362, metadata !229), !dbg !363
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !364, metadata !229), !dbg !365
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !366
  %xattr_p = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 19, !dbg !368
  %1 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_p, align 8, !dbg !368
  %tobool = icmp ne %struct.ae_xattr* %1, null, !dbg !366
  br i1 %tobool, label %if.then, label %if.else, !dbg !369

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !370
  %xattr_p2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 19, !dbg !372
  %3 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_p2, align 8, !dbg !372
  %name3 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %3, i32 0, i32 1, !dbg !373
  %4 = load i8*, i8** %name3, align 8, !dbg !373
  %5 = load i8**, i8*** %name.addr, align 8, !dbg !374
  store i8* %4, i8** %5, align 8, !dbg !375
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !376
  %xattr_p4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 19, !dbg !377
  %7 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_p4, align 8, !dbg !377
  %value5 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %7, i32 0, i32 2, !dbg !378
  %8 = load i8*, i8** %value5, align 8, !dbg !378
  %9 = load i8**, i8*** %value.addr, align 8, !dbg !379
  store i8* %8, i8** %9, align 8, !dbg !380
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !381
  %xattr_p6 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 19, !dbg !382
  %11 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_p6, align 8, !dbg !382
  %size7 = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %11, i32 0, i32 3, !dbg !383
  %12 = load i64, i64* %size7, align 8, !dbg !383
  %13 = load i64*, i64** %size.addr, align 8, !dbg !384
  store i64 %12, i64* %13, align 8, !dbg !385
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !386
  %xattr_p8 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %14, i32 0, i32 19, !dbg !387
  %15 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_p8, align 8, !dbg !387
  %next = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %15, i32 0, i32 0, !dbg !388
  %16 = load %struct.ae_xattr*, %struct.ae_xattr** %next, align 8, !dbg !388
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !389
  %xattr_p9 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %17, i32 0, i32 19, !dbg !390
  store %struct.ae_xattr* %16, %struct.ae_xattr** %xattr_p9, align 8, !dbg !391
  store i32 0, i32* %retval, align 4, !dbg !392
  br label %return, !dbg !392

if.else:                                          ; preds = %entry
  %18 = load i8**, i8*** %name.addr, align 8, !dbg !393
  store i8* null, i8** %18, align 8, !dbg !395
  %19 = load i8**, i8*** %value.addr, align 8, !dbg !396
  store i8* null, i8** %19, align 8, !dbg !397
  %20 = load i64*, i64** %size.addr, align 8, !dbg !398
  store i64 0, i64* %20, align 8, !dbg !399
  store i32 -20, i32* %retval, align 4, !dbg !400
  br label %return, !dbg !400

return:                                           ; preds = %if.else, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !401
  ret i32 %21, !dbg !401
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind }
attributes #6 = { noreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!225, !226}
!llvm.ident = !{!227}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !18)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_xattr.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !15}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_xattr", file: !7, line: 38, size: 256, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !10, !13, !14}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !6, file: !7, line: 39, baseType: !5, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !6, file: !7, line: 41, baseType: !11, size: 64, align: 64, offset: 64)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !6, file: !7, line: 42, baseType: !4, size: 64, align: 64, offset: 128)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !6, file: !7, line: 43, baseType: !15, size: 64, align: 64, offset: 192)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !16, line: 62, baseType: !17)
!16 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!17 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!18 = !{!19, !214, !217, !220, !221}
!19 = distinct !DISubprogram(name: "archive_entry_xattr_clear", scope: !1, file: !1, line: 73, type: !20, isLocal: false, isDefinition: true, scopeLine: 74, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!20 = !DISubroutineType(types: !21)
!21 = !{null, !22}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !7, line: 73, size: 8640, align: 64, elements: !24)
!24 = !{!25, !119, !120, !121, !150, !151, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !199, !200, !201, !208, !209, !210}
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !23, file: !7, line: 74, baseType: !26, size: 64, align: 64)
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !28, line: 89, size: 1280, align: 64, elements: !29)
!28 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!29 = !{!30, !32, !33, !93, !94, !95, !96, !97, !98, !99, !100, !107, !108, !109, !110, !113, !114, !115, !116, !117, !118}
!30 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !27, file: !28, line: 96, baseType: !31, size: 32, align: 32)
!31 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !27, file: !28, line: 97, baseType: !31, size: 32, align: 32, offset: 32)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !27, file: !28, line: 103, baseType: !34, size: 64, align: 64, offset: 64)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !28, line: 63, size: 832, align: 64, elements: !36)
!36 = !{!37, !42, !43, !47, !48, !59, !65, !70, !71, !78, !79, !83, !87}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !35, file: !28, line: 64, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DISubroutineType(types: !40)
!40 = !{!41, !26}
!41 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !35, file: !28, line: 65, baseType: !38, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !35, file: !28, line: 66, baseType: !44, size: 64, align: 64, offset: 128)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DISubroutineType(types: !46)
!46 = !{!41, !26, !22}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !35, file: !28, line: 68, baseType: !38, size: 64, align: 64, offset: 192)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !35, file: !28, line: 69, baseType: !49, size: 64, align: 64, offset: 256)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!52, !26, !57, !15}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !53, line: 109, baseType: !54)
!53 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !55, line: 172, baseType: !56)
!55 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!56 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !35, file: !28, line: 71, baseType: !60, size: 64, align: 64, offset: 320)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!52, !26, !57, !15, !63}
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !64, line: 40, baseType: !56)
!64 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !35, file: !28, line: 74, baseType: !66, size: 64, align: 64, offset: 384)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DISubroutineType(types: !68)
!68 = !{!41, !26, !69}
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !35, file: !28, line: 76, baseType: !44, size: 64, align: 64, offset: 448)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !35, file: !28, line: 78, baseType: !72, size: 64, align: 64, offset: 512)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64, align: 64)
!73 = !DISubroutineType(types: !74)
!74 = !{!41, !26, !75, !76, !77}
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !35, file: !28, line: 81, baseType: !38, size: 64, align: 64, offset: 576)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !35, file: !28, line: 82, baseType: !80, size: 64, align: 64, offset: 640)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DISubroutineType(types: !82)
!82 = !{!63, !26, !41}
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !35, file: !28, line: 83, baseType: !84, size: 64, align: 64, offset: 704)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64, align: 64)
!85 = !DISubroutineType(types: !86)
!86 = !{!41, !26, !41}
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !35, file: !28, line: 84, baseType: !88, size: 64, align: 64, offset: 768)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!91, !26, !41}
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !12)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !27, file: !28, line: 105, baseType: !41, size: 32, align: 32, offset: 128)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !27, file: !28, line: 106, baseType: !91, size: 64, align: 64, offset: 192)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !27, file: !28, line: 108, baseType: !41, size: 32, align: 32, offset: 256)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !27, file: !28, line: 109, baseType: !91, size: 64, align: 64, offset: 320)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !27, file: !28, line: 112, baseType: !41, size: 32, align: 32, offset: 384)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !27, file: !28, line: 114, baseType: !41, size: 32, align: 32, offset: 416)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !27, file: !28, line: 115, baseType: !91, size: 64, align: 64, offset: 448)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !27, file: !28, line: 116, baseType: !101, size: 192, align: 64, offset: 512)
!101 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !102, line: 58, size: 192, align: 64, elements: !103)
!102 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!103 = !{!104, !105, !106}
!104 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !101, file: !102, line: 59, baseType: !11, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !101, file: !102, line: 60, baseType: !15, size: 64, align: 64, offset: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !101, file: !102, line: 61, baseType: !15, size: 64, align: 64, offset: 128)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !27, file: !28, line: 118, baseType: !11, size: 64, align: 64, offset: 704)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !27, file: !28, line: 119, baseType: !31, size: 32, align: 32, offset: 768)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !27, file: !28, line: 120, baseType: !31, size: 32, align: 32, offset: 800)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !27, file: !28, line: 121, baseType: !111, size: 64, align: 64, offset: 832)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !112, size: 64, align: 64)
!112 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !102, line: 70, flags: DIFlagFwdDecl)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !27, file: !28, line: 127, baseType: !91, size: 64, align: 64, offset: 896)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !27, file: !28, line: 128, baseType: !63, size: 64, align: 64, offset: 960)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !27, file: !28, line: 129, baseType: !63, size: 64, align: 64, offset: 1024)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !27, file: !28, line: 130, baseType: !15, size: 64, align: 64, offset: 1088)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !27, file: !28, line: 137, baseType: !12, size: 8, align: 8, offset: 1152)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !27, file: !28, line: 138, baseType: !15, size: 64, align: 64, offset: 1216)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "stat", scope: !23, file: !7, line: 96, baseType: !4, size: 64, align: 64, offset: 64)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "stat_valid", scope: !23, file: !7, line: 97, baseType: !41, size: 32, align: 32, offset: 128)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "ae_stat", scope: !23, file: !7, line: 129, baseType: !122, size: 1344, align: 64, offset: 192)
!122 = !DICompositeType(tag: DW_TAG_structure_type, name: "aest", file: !7, line: 99, size: 1344, align: 64, elements: !123)
!123 = !{!124, !125, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !138, !139, !140, !144, !145, !146, !147, !148, !149}
!124 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime", scope: !122, file: !7, line: 100, baseType: !63, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime_nsec", scope: !122, file: !7, line: 101, baseType: !126, size: 32, align: 32, offset: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !64, line: 51, baseType: !31)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime", scope: !122, file: !7, line: 102, baseType: !63, size: 64, align: 64, offset: 128)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime_nsec", scope: !122, file: !7, line: 103, baseType: !126, size: 32, align: 32, offset: 192)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime", scope: !122, file: !7, line: 104, baseType: !63, size: 64, align: 64, offset: 256)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime_nsec", scope: !122, file: !7, line: 105, baseType: !126, size: 32, align: 32, offset: 320)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime", scope: !122, file: !7, line: 106, baseType: !63, size: 64, align: 64, offset: 384)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime_nsec", scope: !122, file: !7, line: 107, baseType: !126, size: 32, align: 32, offset: 448)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "aest_gid", scope: !122, file: !7, line: 108, baseType: !63, size: 64, align: 64, offset: 512)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ino", scope: !122, file: !7, line: 109, baseType: !63, size: 64, align: 64, offset: 576)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "aest_nlink", scope: !122, file: !7, line: 110, baseType: !126, size: 32, align: 32, offset: 640)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "aest_size", scope: !122, file: !7, line: 111, baseType: !137, size: 64, align: 64, offset: 704)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !64, line: 55, baseType: !17)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "aest_uid", scope: !122, file: !7, line: 112, baseType: !63, size: 64, align: 64, offset: 768)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev_is_broken_down", scope: !122, file: !7, line: 121, baseType: !41, size: 32, align: 32, offset: 832)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev", scope: !122, file: !7, line: 122, baseType: !141, size: 64, align: 64, offset: 896)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !142, line: 44, baseType: !143)
!142 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !55, line: 124, baseType: !17)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devmajor", scope: !122, file: !7, line: 123, baseType: !141, size: 64, align: 64, offset: 960)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devminor", scope: !122, file: !7, line: 124, baseType: !141, size: 64, align: 64, offset: 1024)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev_is_broken_down", scope: !122, file: !7, line: 125, baseType: !41, size: 32, align: 32, offset: 1088)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev", scope: !122, file: !7, line: 126, baseType: !141, size: 64, align: 64, offset: 1152)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevmajor", scope: !122, file: !7, line: 127, baseType: !141, size: 64, align: 64, offset: 1216)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevminor", scope: !122, file: !7, line: 128, baseType: !141, size: 64, align: 64, offset: 1280)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "ae_set", scope: !23, file: !7, line: 131, baseType: !41, size: 32, align: 32, offset: 1536)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_text", scope: !23, file: !7, line: 145, baseType: !152, size: 832, align: 64, offset: 1600)
!152 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !102, line: 209, size: 832, align: 64, elements: !153)
!153 = !{!154, !155, !156, !164, !165}
!154 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !152, file: !102, line: 210, baseType: !101, size: 192, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !152, file: !102, line: 211, baseType: !101, size: 192, align: 64, offset: 192)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !152, file: !102, line: 212, baseType: !157, size: 192, align: 64, offset: 384)
!157 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !102, line: 64, size: 192, align: 64, elements: !158)
!158 = !{!159, !162, !163}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !157, file: !102, line: 65, baseType: !160, size: 64, align: 64)
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !16, line: 90, baseType: !41)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !157, file: !102, line: 66, baseType: !15, size: 64, align: 64, offset: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !157, file: !102, line: 67, baseType: !15, size: 64, align: 64, offset: 128)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !152, file: !102, line: 213, baseType: !101, size: 192, align: 64, offset: 576)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !152, file: !102, line: 218, baseType: !41, size: 32, align: 32, offset: 768)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_set", scope: !23, file: !7, line: 146, baseType: !17, size: 64, align: 64, offset: 2432)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_clear", scope: !23, file: !7, line: 147, baseType: !17, size: 64, align: 64, offset: 2496)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "ae_gname", scope: !23, file: !7, line: 148, baseType: !152, size: 832, align: 64, offset: 2560)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "ae_hardlink", scope: !23, file: !7, line: 149, baseType: !152, size: 832, align: 64, offset: 3392)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "ae_pathname", scope: !23, file: !7, line: 150, baseType: !152, size: 832, align: 64, offset: 4224)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "ae_symlink", scope: !23, file: !7, line: 151, baseType: !152, size: 832, align: 64, offset: 5056)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "ae_uname", scope: !23, file: !7, line: 152, baseType: !152, size: 832, align: 64, offset: 5888)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "ae_sourcepath", scope: !23, file: !7, line: 155, baseType: !152, size: 832, align: 64, offset: 6720)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "encryption", scope: !23, file: !7, line: 160, baseType: !12, size: 8, align: 8, offset: 7552)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata", scope: !23, file: !7, line: 162, baseType: !4, size: 64, align: 64, offset: 7616)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata_size", scope: !23, file: !7, line: 163, baseType: !15, size: 64, align: 64, offset: 7680)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "acl", scope: !23, file: !7, line: 166, baseType: !178, size: 448, align: 64, offset: 7744)
!178 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !179, line: 46, size: 448, align: 64, elements: !180)
!179 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!180 = !{!181, !184, !194, !195, !196, !197, !198}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !178, file: !179, line: 47, baseType: !182, size: 32, align: 32)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !142, line: 63, baseType: !183)
!183 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !55, line: 129, baseType: !31)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !178, file: !179, line: 48, baseType: !185, size: 64, align: 64, offset: 64)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !179, line: 37, size: 1024, align: 64, elements: !187)
!187 = !{!188, !189, !190, !191, !192, !193}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !186, file: !179, line: 38, baseType: !185, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !186, file: !179, line: 39, baseType: !41, size: 32, align: 32, offset: 64)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !186, file: !179, line: 40, baseType: !41, size: 32, align: 32, offset: 96)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !186, file: !179, line: 41, baseType: !41, size: 32, align: 32, offset: 128)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !186, file: !179, line: 42, baseType: !41, size: 32, align: 32, offset: 160)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !186, file: !179, line: 43, baseType: !152, size: 832, align: 64, offset: 192)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !178, file: !179, line: 49, baseType: !185, size: 64, align: 64, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !178, file: !179, line: 50, baseType: !41, size: 32, align: 32, offset: 192)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !178, file: !179, line: 51, baseType: !160, size: 64, align: 64, offset: 256)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !178, file: !179, line: 52, baseType: !11, size: 64, align: 64, offset: 320)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !178, file: !179, line: 53, baseType: !41, size: 32, align: 32, offset: 384)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_head", scope: !23, file: !7, line: 169, baseType: !5, size: 64, align: 64, offset: 8192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_p", scope: !23, file: !7, line: 170, baseType: !5, size: 64, align: 64, offset: 8256)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_head", scope: !23, file: !7, line: 173, baseType: !202, size: 64, align: 64, offset: 8320)
!202 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!203 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_sparse", file: !7, line: 46, size: 192, align: 64, elements: !204)
!204 = !{!205, !206, !207}
!205 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !203, file: !7, line: 47, baseType: !202, size: 64, align: 64)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !203, file: !7, line: 49, baseType: !63, size: 64, align: 64, offset: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !203, file: !7, line: 50, baseType: !63, size: 64, align: 64, offset: 128)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_tail", scope: !23, file: !7, line: 174, baseType: !202, size: 64, align: 64, offset: 8384)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_p", scope: !23, file: !7, line: 175, baseType: !202, size: 64, align: 64, offset: 8448)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "strmode", scope: !23, file: !7, line: 178, baseType: !211, size: 96, align: 8, offset: 8512)
!211 = !DICompositeType(tag: DW_TAG_array_type, baseType: !12, size: 96, align: 8, elements: !212)
!212 = !{!213}
!213 = !DISubrange(count: 12)
!214 = distinct !DISubprogram(name: "archive_entry_xattr_add_entry", scope: !1, file: !1, line: 89, type: !215, isLocal: false, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!215 = !DISubroutineType(types: !216)
!216 = !{null, !22, !91, !57, !15}
!217 = distinct !DISubprogram(name: "archive_entry_xattr_count", scope: !1, file: !1, line: 115, type: !218, isLocal: false, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!218 = !DISubroutineType(types: !219)
!219 = !{!41, !22}
!220 = distinct !DISubprogram(name: "archive_entry_xattr_reset", scope: !1, file: !1, line: 127, type: !218, isLocal: false, isDefinition: true, scopeLine: 128, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_entry_xattr_next", scope: !1, file: !1, line: 135, type: !222, isLocal: false, isDefinition: true, scopeLine: 137, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !DISubroutineType(types: !223)
!223 = !{!41, !22, !224, !75, !76}
!224 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!225 = !{i32 2, !"Dwarf Version", i32 4}
!226 = !{i32 2, !"Debug Info Version", i32 3}
!227 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!228 = !DILocalVariable(name: "entry", arg: 1, scope: !19, file: !1, line: 73, type: !22)
!229 = !DIExpression()
!230 = !DILocation(line: 73, column: 49, scope: !19)
!231 = !DILocalVariable(name: "xp", scope: !19, file: !1, line: 75, type: !5)
!232 = !DILocation(line: 75, column: 19, scope: !19)
!233 = !DILocation(line: 77, column: 2, scope: !19)
!234 = !DILocation(line: 77, column: 9, scope: !235)
!235 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 1)
!236 = !DILocation(line: 77, column: 16, scope: !235)
!237 = !DILocation(line: 77, column: 27, scope: !235)
!238 = !DILocation(line: 77, column: 2, scope: !235)
!239 = !DILocation(line: 78, column: 8, scope: !240)
!240 = distinct !DILexicalBlock(scope: !19, file: !1, line: 77, column: 36)
!241 = !DILocation(line: 78, column: 15, scope: !240)
!242 = !DILocation(line: 78, column: 27, scope: !240)
!243 = !DILocation(line: 78, column: 6, scope: !240)
!244 = !DILocation(line: 79, column: 8, scope: !240)
!245 = !DILocation(line: 79, column: 15, scope: !240)
!246 = !DILocation(line: 79, column: 27, scope: !240)
!247 = !DILocation(line: 79, column: 3, scope: !240)
!248 = !DILocation(line: 80, column: 8, scope: !240)
!249 = !DILocation(line: 80, column: 15, scope: !240)
!250 = !DILocation(line: 80, column: 27, scope: !240)
!251 = !DILocation(line: 80, column: 3, scope: !240)
!252 = !DILocation(line: 81, column: 8, scope: !240)
!253 = !DILocation(line: 81, column: 15, scope: !240)
!254 = !DILocation(line: 81, column: 3, scope: !240)
!255 = !DILocation(line: 82, column: 23, scope: !240)
!256 = !DILocation(line: 82, column: 3, scope: !240)
!257 = !DILocation(line: 82, column: 10, scope: !240)
!258 = !DILocation(line: 82, column: 21, scope: !240)
!259 = !DILocation(line: 77, column: 2, scope: !260)
!260 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 2)
!261 = !DILocation(line: 85, column: 2, scope: !19)
!262 = !DILocation(line: 85, column: 9, scope: !19)
!263 = !DILocation(line: 85, column: 20, scope: !19)
!264 = !DILocation(line: 86, column: 1, scope: !19)
!265 = !DILocalVariable(name: "entry", arg: 1, scope: !214, file: !1, line: 89, type: !22)
!266 = !DILocation(line: 89, column: 53, scope: !214)
!267 = !DILocalVariable(name: "name", arg: 2, scope: !214, file: !1, line: 90, type: !91)
!268 = !DILocation(line: 90, column: 14, scope: !214)
!269 = !DILocalVariable(name: "value", arg: 3, scope: !214, file: !1, line: 90, type: !57)
!270 = !DILocation(line: 90, column: 32, scope: !214)
!271 = !DILocalVariable(name: "size", arg: 4, scope: !214, file: !1, line: 90, type: !15)
!272 = !DILocation(line: 90, column: 46, scope: !214)
!273 = !DILocalVariable(name: "xp", scope: !214, file: !1, line: 92, type: !5)
!274 = !DILocation(line: 92, column: 19, scope: !214)
!275 = !DILocation(line: 94, column: 31, scope: !276)
!276 = distinct !DILexicalBlock(scope: !214, file: !1, line: 94, column: 6)
!277 = !DILocation(line: 94, column: 12, scope: !276)
!278 = !DILocation(line: 94, column: 10, scope: !276)
!279 = !DILocation(line: 94, column: 64, scope: !276)
!280 = !DILocation(line: 94, column: 6, scope: !214)
!281 = !DILocation(line: 95, column: 3, scope: !276)
!282 = !DILocation(line: 97, column: 25, scope: !283)
!283 = distinct !DILexicalBlock(scope: !214, file: !1, line: 97, column: 6)
!284 = !DILocation(line: 97, column: 18, scope: !283)
!285 = !DILocation(line: 97, column: 7, scope: !283)
!286 = !DILocation(line: 97, column: 11, scope: !283)
!287 = !DILocation(line: 97, column: 16, scope: !283)
!288 = !DILocation(line: 97, column: 32, scope: !283)
!289 = !DILocation(line: 97, column: 6, scope: !214)
!290 = !DILocation(line: 98, column: 3, scope: !283)
!291 = !DILocation(line: 100, column: 26, scope: !292)
!292 = distinct !DILexicalBlock(scope: !214, file: !1, line: 100, column: 6)
!293 = !DILocation(line: 100, column: 19, scope: !292)
!294 = !DILocation(line: 100, column: 7, scope: !292)
!295 = !DILocation(line: 100, column: 11, scope: !292)
!296 = !DILocation(line: 100, column: 17, scope: !292)
!297 = !DILocation(line: 100, column: 33, scope: !292)
!298 = !DILocation(line: 100, column: 6, scope: !214)
!299 = !DILocation(line: 101, column: 10, scope: !300)
!300 = distinct !DILexicalBlock(scope: !292, file: !1, line: 100, column: 42)
!301 = !DILocation(line: 101, column: 14, scope: !300)
!302 = !DILocation(line: 101, column: 21, scope: !300)
!303 = !DILocation(line: 101, column: 28, scope: !300)
!304 = !DILocation(line: 101, column: 3, scope: !300)
!305 = !DILocation(line: 102, column: 14, scope: !300)
!306 = !DILocation(line: 102, column: 3, scope: !300)
!307 = !DILocation(line: 102, column: 7, scope: !300)
!308 = !DILocation(line: 102, column: 12, scope: !300)
!309 = !DILocation(line: 103, column: 2, scope: !300)
!310 = !DILocation(line: 104, column: 3, scope: !292)
!311 = !DILocation(line: 104, column: 7, scope: !292)
!312 = !DILocation(line: 104, column: 12, scope: !292)
!313 = !DILocation(line: 106, column: 13, scope: !214)
!314 = !DILocation(line: 106, column: 20, scope: !214)
!315 = !DILocation(line: 106, column: 2, scope: !214)
!316 = !DILocation(line: 106, column: 6, scope: !214)
!317 = !DILocation(line: 106, column: 11, scope: !214)
!318 = !DILocation(line: 107, column: 22, scope: !214)
!319 = !DILocation(line: 107, column: 2, scope: !214)
!320 = !DILocation(line: 107, column: 9, scope: !214)
!321 = !DILocation(line: 107, column: 20, scope: !214)
!322 = !DILocation(line: 108, column: 1, scope: !214)
!323 = !DILocalVariable(name: "entry", arg: 1, scope: !217, file: !1, line: 115, type: !22)
!324 = !DILocation(line: 115, column: 49, scope: !217)
!325 = !DILocalVariable(name: "xp", scope: !217, file: !1, line: 117, type: !5)
!326 = !DILocation(line: 117, column: 19, scope: !217)
!327 = !DILocalVariable(name: "count", scope: !217, file: !1, line: 118, type: !41)
!328 = !DILocation(line: 118, column: 6, scope: !217)
!329 = !DILocation(line: 120, column: 12, scope: !330)
!330 = distinct !DILexicalBlock(scope: !217, file: !1, line: 120, column: 2)
!331 = !DILocation(line: 120, column: 19, scope: !330)
!332 = !DILocation(line: 120, column: 10, scope: !330)
!333 = !DILocation(line: 120, column: 7, scope: !330)
!334 = !DILocation(line: 120, column: 31, scope: !335)
!335 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 1)
!336 = distinct !DILexicalBlock(scope: !330, file: !1, line: 120, column: 2)
!337 = !DILocation(line: 120, column: 34, scope: !335)
!338 = !DILocation(line: 120, column: 2, scope: !335)
!339 = !DILocation(line: 121, column: 8, scope: !336)
!340 = !DILocation(line: 121, column: 3, scope: !336)
!341 = !DILocation(line: 120, column: 48, scope: !342)
!342 = !DILexicalBlockFile(scope: !336, file: !1, discriminator: 2)
!343 = !DILocation(line: 120, column: 52, scope: !342)
!344 = !DILocation(line: 120, column: 46, scope: !342)
!345 = !DILocation(line: 120, column: 2, scope: !342)
!346 = !DILocation(line: 123, column: 9, scope: !217)
!347 = !DILocation(line: 123, column: 2, scope: !217)
!348 = !DILocalVariable(name: "entry", arg: 1, scope: !220, file: !1, line: 127, type: !22)
!349 = !DILocation(line: 127, column: 50, scope: !220)
!350 = !DILocation(line: 129, column: 19, scope: !220)
!351 = !DILocation(line: 129, column: 26, scope: !220)
!352 = !DILocation(line: 129, column: 2, scope: !220)
!353 = !DILocation(line: 129, column: 9, scope: !220)
!354 = !DILocation(line: 129, column: 17, scope: !220)
!355 = !DILocation(line: 131, column: 35, scope: !220)
!356 = !DILocation(line: 131, column: 9, scope: !220)
!357 = !DILocation(line: 131, column: 2, scope: !220)
!358 = !DILocalVariable(name: "entry", arg: 1, scope: !221, file: !1, line: 135, type: !22)
!359 = !DILocation(line: 135, column: 49, scope: !221)
!360 = !DILocalVariable(name: "name", arg: 2, scope: !221, file: !1, line: 136, type: !224)
!361 = !DILocation(line: 136, column: 15, scope: !221)
!362 = !DILocalVariable(name: "value", arg: 3, scope: !221, file: !1, line: 136, type: !75)
!363 = !DILocation(line: 136, column: 34, scope: !221)
!364 = !DILocalVariable(name: "size", arg: 4, scope: !221, file: !1, line: 136, type: !76)
!365 = !DILocation(line: 136, column: 49, scope: !221)
!366 = !DILocation(line: 138, column: 6, scope: !367)
!367 = distinct !DILexicalBlock(scope: !221, file: !1, line: 138, column: 6)
!368 = !DILocation(line: 138, column: 13, scope: !367)
!369 = !DILocation(line: 138, column: 6, scope: !221)
!370 = !DILocation(line: 139, column: 11, scope: !371)
!371 = distinct !DILexicalBlock(scope: !367, file: !1, line: 138, column: 22)
!372 = !DILocation(line: 139, column: 18, scope: !371)
!373 = !DILocation(line: 139, column: 27, scope: !371)
!374 = !DILocation(line: 139, column: 4, scope: !371)
!375 = !DILocation(line: 139, column: 9, scope: !371)
!376 = !DILocation(line: 140, column: 12, scope: !371)
!377 = !DILocation(line: 140, column: 19, scope: !371)
!378 = !DILocation(line: 140, column: 28, scope: !371)
!379 = !DILocation(line: 140, column: 4, scope: !371)
!380 = !DILocation(line: 140, column: 10, scope: !371)
!381 = !DILocation(line: 141, column: 11, scope: !371)
!382 = !DILocation(line: 141, column: 18, scope: !371)
!383 = !DILocation(line: 141, column: 27, scope: !371)
!384 = !DILocation(line: 141, column: 4, scope: !371)
!385 = !DILocation(line: 141, column: 9, scope: !371)
!386 = !DILocation(line: 143, column: 20, scope: !371)
!387 = !DILocation(line: 143, column: 27, scope: !371)
!388 = !DILocation(line: 143, column: 36, scope: !371)
!389 = !DILocation(line: 143, column: 3, scope: !371)
!390 = !DILocation(line: 143, column: 10, scope: !371)
!391 = !DILocation(line: 143, column: 18, scope: !371)
!392 = !DILocation(line: 145, column: 3, scope: !371)
!393 = !DILocation(line: 147, column: 4, scope: !394)
!394 = distinct !DILexicalBlock(scope: !367, file: !1, line: 146, column: 9)
!395 = !DILocation(line: 147, column: 9, scope: !394)
!396 = !DILocation(line: 148, column: 4, scope: !394)
!397 = !DILocation(line: 148, column: 10, scope: !394)
!398 = !DILocation(line: 149, column: 4, scope: !394)
!399 = !DILocation(line: 149, column: 9, scope: !394)
!400 = !DILocation(line: 150, column: 3, scope: !394)
!401 = !DILocation(line: 152, column: 1, scope: !221)
